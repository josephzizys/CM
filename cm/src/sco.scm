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

(define (sco-par-print par objv filv timv)
  ;; return a form that prints par to a .sco file. passed the
  ;; object, port and scoretime variables. the only real oddity
  ;; is that the scoretime variable currently substitutes for
  ;; the object-time accessor.
  (let* ((raw (if (parameter-time? par)
		timv
		(slot-getter-form objv (parameter-slot par))))
	 (acc (if (parameter-decimals par)
		`(decimals ,raw ,(parameter-decimals par))
		raw))
	 (delim #\space))
    (case (parameter-type par)
      ((required optional key)
       `(begin
         (write-char ,delim ,filv)
         (write ,acc ,filv)))
      ((rest )
       (let ((v (gensym)))
	 `(if (slot-bound? ,objv ',(parameter-slot par))
	    (do ((,v ,(slot-getter-form objv (parameter-slot par))
                     (cdr ,v)))
	        ((null? ,v) #f)
	      (write-char ,delim ,filv)
	      (write (car ,v) ,filv))))))))      

(define (make-sco-writer objclassname objclassvar pars supers sdecl)
  ;; define-output-method in level1.
  sdecl supers   ; gag 'unused var' message from cltl compilers
  (define-output-method objclassname objclassvar 'obj
    'sco-stream '<sco-stream> 'io 'scoretime
    (list `(let ((fp (io-open io)))
             (display (object-name obj) fp)
             ,@ (map (lambda (p) (sco-par-print p 'obj 'fp 'scoretime))
                     pars) 
                (newline fp)
                (values)))))

(define-class <sco-stream> (<event-stream>)
  (header :init-value #f :init-keyword :header
	  :accessor sco-stream-header)
  (userargs :accessor sco-userargs
            :init-value '())
  :name 'sco-stream
  :metaclass <io-class>
  :mime-type "text/x-csound-score"
  :file-types '("*.sco")
  :definer (function make-sco-writer))

(define-method (io-handler-args? (io <sco-stream>))
  io
  #t)

(define-method (io-handler-args (io <sco-stream>))
  (sco-userargs io))

(define-method (set-io-handler-args! (io <sco-stream>) args)
  (set! (sco-userargs io) args)
  (values))

(define (set-sco-output-hook! fn)
  (unless (or (not fn) (procedure? fn))
    (err "Not a sco hook: ~s" fn))
  (set! (io-class-output-hook <sco-stream>) fn)
  (values))

(define *csound* "/usr/local/bin/csound")

(define (play-sco-file file . args)
  (with-args (args &key orchestra options output play)
    (let ((cmd *csound*))
      (when options
        (set! cmd (string-append cmd " " options)))
      (when output
        (set! cmd (string-append cmd " -o" output)))
      (set! cmd (string-append cmd " " orchestra))
      (set! cmd (string-append cmd " " file))
      (shell cmd)
      ;; dont play if output is piped     
      (when (and play (not (member output 
                                   '("devaudio" "dac" "stdout"))))
        (shell "/usr/bin/play ~a" output)))))

(define (set-sco-file-versions! val)
  (set! (io-class-file-versions <sco-stream>) val)
  (values))

;(defobject i1 ()
;  ((time :accessor object-time)
;    dur
;    frq
;    amp)
;  (:parameters time dur frq amp))

(define-method (initialize-io (io <sco-stream>))
  (format (io-open io)
	  "; ~a output on ~a~%"
	  (cm-version)
	  (date-and-time))
  (let ((header (sco-stream-header io)))
    (cond ((pair? header)
	   (dolist (h header) (format (io-open io) "~a~%" h)))
	  ((string? header)
	   (format (io-open io) "~a~%" header))
	  ((not header)
	   #f)
	  (else
	   (err "Bad .sco file header: ~s" header)))))

;;;
;;; added back i and f for easy subclassing
;;;

(defobject i (event) 
           (ins dur)
  (:parameters time dur)
  (:writers )            ; dont define output methods
  )

(define-method (object-name (obj <i>))
  ;; if ins slot is bound use it, otherwise use class name
  (if (slot-bound? obj 'ins)
    (format #f "i~a" (slot-ref obj 'ins))
    (let ((n (symbol->string (class-name (class-of obj)))))
      (if (char-lower-case? (string-ref n 0))
        n
        (string-downcase n)))))

(defobject f (event) 
           (num size gen)
  (:parameters time size gen)
  (:writers )            ; dont define output methods
  )

(define-method (object-name (obj <f>))
  ;; if num slot is bound use it, otherwise use class name
  (if (slot-bound? obj 'num)
    (format #f "f~a" (slot-ref obj 'num))
    (let ((n (symbol->string (class-name (class-of obj)))))
      (if (char-lower-case? (string-ref n 0))
        n
        (string-downcase n)))))

; (defobject i1 (i) (time dur freq amp) (:parameters time dur freq amp))

; (defobject f1 (f) ((env :initform '())) (:parameters time size gen &rest env))


