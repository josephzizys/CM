;;; **********************************************************************
;;; Copyright (C) 2002 Heinrich Taube (taube@uiuc.edu) 
;;; This program is free software; you can redistribute it and/or
;;; modify it under the terms of the GNU General Public License
;;; as published by the Free Software Foundation; either version 2
;;; of the License, or (at your option) any later version.
;;; This program is distributed in the hope that it will be useful,
;;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;;; GNU General Public License for more details.
;;; **********************************************************************

;;; $Name$
;;; $Revision$
;;; $Date$

(define-class <cmn-stream> (<event-stream>)
  (cmnargs :init-value '() :accessor cmn-args)
  (exact :init-value #f :init-keyword :exact-rhythms )
  (staffing :init-value '() :accessor cmn-staffing
            :init-keyword :staffing)
  :name 'cmn-stream
  :metaclass <io-class>
  :file-types '("*.cmn" "*.eps"))


(define (set-cmn-output-hook! fn)
  (unless (or (not fn) (procedure? fn))
    (err "Not a cmn output hook: ~s" fn))
  (set! (io-class-output-hook <cmn-stream>) fn)
  (values))

(define (set-cmn-stream-versions! val)
  (set! (io-class-file-versions <cmn-stream>) val)
  (values))

;;;
;;; enabling 'handler args' lets people set cmn score inits in the
;;; file without actually being slot initializations for the file.
;;; these are passed on to cmn.
;;;

(define-method (io-handler-args? (io <cmn-stream>)) io #t)

(define-method (io-handler-args (io <cmn-stream>))
  (cmn-args io))

(define-method (set-io-handler-args! (io <cmn-stream>) args)
  (set! (cmn-args io) args)
  (values))

;;;
;;; entries in table are (id <cmnstaff> "staffname" clef meter)
;;; the second element is created each time output happens.
;;;

(define *cmn-staves* (make-hash-table 31))

(define (make-staffing id . args)
  (with-args (args &key name clef meter)
    (list id #f (or name (format #f "staff-~a" id))
          clef meter)))

(define-method (close-io (io <cmn-stream>) . mode)
  mode
  (set! (io-open io) #f))

(define-method (open-io (io <cmn-stream>) dir . args)
  args
  (when (eq? dir ':output)
    (set! (io-open io)
          (init-clm-input 
           ;; FIX: find-class for scheme!
           (apply #'make-instance (find-class 'score)
                  :output-file 
                  (file-output-filename io)
                  (cmn-args io))))
    (set! *exact-rhythms* (slot-value io 'exact)))
  io)

(define-method (initialize-io (io <cmn-stream>))
  ;; copy staffing infor each user specifed staff
  ;; and add a cmn staff object to it.
  (let ((score (io-open io)))
    (hash-clear! *cmn-staves*)
    (loop for s in (cmn-staffing io)
          for c = (apply #'make-staffing s)
          do
          (set-car! (cdr c) 
                    (add-staff score (third c) '()))
          (hash-set! *cmn-staves* (first c) c))
    (values)))

(define (set-staff-meter staff meter)
  (if (pair? meter)
    (unless (eq? (first meter) 'meter)
      (push 'meter meter))
    (err "meter should be list like: (meter 3 4)"))
  (let ((stfd (find staff staff-descriptors 
                    :key #'stfdat-staff)))
    (set! (staff-data (stfdat-staff stfd))
          (append (staff-data (stfdat-staff stfd))
                  (list (cmn-eval meter))))))

(define-method (deinitialize-io (io <cmn-stream>))
  (let ((get-active-staff-stuff
         (lambda (score) 
           (let ((ids '())
                 (data '()))
             score
             ;; collect ids in order...
             (set! data 
                   (hash-fold  
                    (lambda (k v p) v (cons k p))
                    '()
                    *cmn-staves*))
             (set! ids (sort! ids #'<))
             (dolist (id ids)
               (let* ((desc (hash-ref *cmn-staves*  id))
                      (staff (second desc)) 
                      (label (third desc))
                      (clefs (fourth desc))
                      (meter (list-ref desc 4)) ; fifth...
                      (count #f))
                 ;; dont collect data unless staff really has data
                 ;; because cmn flushes empty staves and those
                 ;; commands will then act on null references.
                 
                 (when (staff-data staff)
                   (if (not (list? clefs))
                     (set! clefs (list clefs)))
                   (set! meter (list-ref desc 4)) ; fifth
                   (set! count (if (member ':both clefs) 2 1))
                   (push (list 'set-staff-number label count)
                         data)
                   (when clefs 
                     (push (list* 'set-staff-clef label clefs)
                           data))
                   (when meter
                     (push (list 'set-staff-meter label meter)
                           data)))))
             (reverse! data)))))
    (let* ((score (io-open io))
           (path (file-output-filename io))
           (type (if (string=? (filename-type path) "cmn") 
                   :cmn #f))
           (staves '()))
      (unless (eq? type ':cmn)
        (format #t "~%Manuscripting ~a..." path))
      (set! staves (get-active-staff-stuff score ))
      (apply #'finish-clm-input score type #f staves))))

;;;
;;; we cant know beforehand which internal CMN symbols a user will use
;;; so this hairball insures that a cmn variable or function call gets
;;; evaled in the cmn package, regardless of what package the symbols
;;; are actually in. so we can type (meter 2 4) in cm (or any other
;;; package), and the form will be evaluated as if it were typed in
;;; the cmn package.
;;;

(define (cmn-eval form)
  ;; FIX for scheme: find-symbol fboundp boundp constantp
  (let ((cmnfun
         (lambda (sym)
           (let ((fun (find-symbol (symbol->string sym) :cmn)))
             (unless (and fun (fboundp fun))
               (err "~S is not a cmn function!" sym))
             fun)))
        (cmnvar 
         (lambda (sym)
           (let ((var (find-symbol (symbol->string sym) :cmn)))
             (unless (and var (bound? var))
               (err "~S is not a cmn variable." sym))
             (symbol-value var)))))
    (cond ((pair? form) 
           (apply (cmnfun (car form))
                  (map #'cmn-eval (cdr form))))
          ((constantp form) 
           form)
          (form 
           (cmnvar form))
          (else #f))))

;;;
;;; override the main open/close methods because cmn manages io itself.
;;;

(define (add-default-staff id score)
  (let* ((entry (make-staffing id))
         (sname (third entry))
         (staff (or (find-staff score sname)
                    (add-staff score sname '()))))
    (set-car! (cdr entry) staff) ; setf second
    entry))

(define-method (write-event (obj <standard-object>) (io <cmn-stream>)
                            scoretime)
  (let ((score (io-open io))
        (data (object->cmn obj))
        (entry #f)
        (staff #f))

    (unless (pair? data)
      (err "object->cmn did not return a list: ~s.:" data))
    (set! entry (hash-ref *cmn-staves* (first data)))
    (unless entry
      (set! entry (add-default-staff (first data) score)))
    
    (set! staff (second entry))
    
    (if (= (length data) 2)
      (add-data-1 score staff (cmn-eval (second data)))
      (let ((dur (second data))
            (note (third data))
            (args (loop for i in (cdddr data) 
                        collect (cmn-eval i))))
        (unless (rest? note)
          (apply #'add-note-to-staff 
                 score 
                 staff
                 scoretime
                 dur
                 (cmn-eval note)
                 args))))))
        
;;;
;;;
;;;

(define-method (object->cmn (obj <midi>))
  (list (midi-channel obj)
        (midi-duration obj)
        (note (midi-keynum obj))))

; (clear-cmn-staves!)
; (set-cmn-staff! 0 :name "Banjo" :clef ':treble)
; (set-cmn-output-hook! #'load)
;(define (testit )
;  (let ((pat (new cycle :notes '(c4 d d ef f ))))
;    (process repeat 4
;             for n = (next pat)
;             output (new midi :time (now)
;                         :duration 1
;                         :keynum n)
;             wait 1)))
;  (io "test.cmn" :exact-rhythms #t :size 24 :title "Hiho!")
; (describe #!"test.cmn")
; (events (testit) "test.cmn")

