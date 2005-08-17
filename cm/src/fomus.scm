;;; **********************************************************************
;;; Copyright (C) 2005 Heinrich Taube
;;; 
;;; This program is free software; you can redistribute it and/or
;;; modify it under the terms of the GNU General Public License
;;; as published by the Free Software Foundation; either version 2
;;; of the License, or (at your option) any later version.
;;; 
;;; This program is distributed in the hope that it will be useful,
;;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;;; GNU General Public License for more details.
;;; 
;;; **********************************************************************

;;; $Name$
;;; $Revision$
;;; $Date$

;;;
;;; Interface to David Psenicka's Fomus notation package.
;;;

(in-package :cm)

(define-class* <fomus-file> (<event-stream>)
  ((parts :init-keyword :parts :init-value '()
          :accessor fomus-file-parts)
   (global :init-keyword :global :init-value '()
           :accessor fomus-file-global)
   (view :init-keyword :view :init-value #f :accessor fomus-file-view)
   )
  :name 'fomus-file
  :metaclass <io-class>
  :file-types '("*.fms" "*.xml" "*.ly")) 
         
(define-method* (object-time (obj <event-base>))
  (event-off obj))

(define-method* (open-io (io <fomus-file>) dir . args)
  args
  (when (eq? dir ':output)
    (let ((parts (fomus-file-parts io))
          (globs (fomus-file-global io)))
      ;; check for singles
      (unless (list? parts)
        (set! (fomus-file-parts io) 
              (if parts (list parts) (list))))
      (unless (list? globs)
        (set! (fomus-file-global io) 
              (if globs (list globs) (list))))
      ;; flush existing data from parts
      (for-each (lambda (p)
                  (set! (obj-id p) #f)
                  (set! (part-events p) (list)))
                (fomus-file-parts io))
      (set! (io-open io) #t)))
  io)
    
(define-method* (close-io (io <fomus-file>) . mode)
  (let ((err? (and (not (null? mode))
                   (eq? (car mode) ':error))))
    (set! (io-open io) #f)
    (unless err?
      (let* ((args (event-stream-args io))
             (bend (list-prop args ':backend)))
        (unless bend
          (let* ((file (io-filename io))
                 (type (filename-type file)))
            (cond ((equal? type "ly")
                   (set! bend ':lilypond))
                  ((equal? type "xml")
                   (set! bend ':xml))
                  (else
                   (set! bend ':fms)))
            (set! args (cons* ':backend
                              (list bend :filename file
                                    :view (fomus-file-view io))
                              args))))
        (apply (function fomus)
               :parts (fomus-file-parts io)
               :global (fomus-file-global io)
               args)))))

(define (fomus-file-part stream id)
  (do ((tail (fomus-file-parts stream) (cdr tail))
       (part #f))
      ((or (null? tail) part) 
       (when (not part)
         (set! part (make-part :partid id :instr (if (keyword? id) id #f)))
         (set! (fomus-file-parts stream)
               (cons part (fomus-file-parts stream))))
       part)
    (if (eq? id (obj-partid (car tail)))
        (set! part (car tail)))))

(define-method* (write-event (obj <event-base>) (fil <fomus-file>) scoretime)
  (let ((part (fomus-file-part fil (obj-partid obj))))
    ;; use score time not local time.
    (set! (event-off obj) scoretime)
    (set! (part-events part)
          (cons obj (part-events part)))
    obj))

(define-method* (write-event (obj <midi>) (fil <fomus-file>) scoretime)
  (let* ((myid (midi-channel obj))
         (part (fomus-file-part fil myid))
         ;(ampl (midi-amplitude obj))
         (marks '()))
    ;; add dynamic if not same as last note.
;;     (when (<= 0 ampl 1)
;;       (let ((this (list-ref '(:pppp :ppp :pp :p :mp 
;;                               :mf :f :ff :fff :ffff :fffff)
;;                             (inexact->exact
;;                              (floor (/ ampl .1))))))
;;           (unless (eq? this (obj-id part))
;;             (set! marks (list this))
;;             (set! (obj-id part) this))))
    (set! (part-events part)
          (cons (make-note :partid myid
                           :off scoretime
                           :note (midi-keynum obj)
                           :dur (midi-duration obj)
                           :marks marks)
                (part-events part)))))

(define (partid->part pid)
  (loop for p in *parts* thereis (eq? pid (obj-partid p))))

(define-method* (write-event (obj <event-base>) (fil <midi-file>) scoretime)
  (let* ((myid (obj-partid obj))
         (part (partid->part myid))
         (opts (if (not part) (list) (part-opts part)))
         (chan #f)
         (ampl 64))
    (do ((tail opts (cddr tail)))
        ((null? tail) #f)
      (case (car tail)
        ;; figure this out later
        (( :midi-chan ) (set! chan (cadr tail)))
        (( :midi-vel ) (set! ampl (cadr tail)))
        (( :midi-min-stacatto-dur ) #f)
        (( :midi-stacatto-durratio ) #f)
        (( :midi-trill-dur ) #f)
        (( :midi-trill-vel ) #f)
        (( :midi-min-grace-dur ) #f)
        (( :midi-max-grace-dur ) #f)
        (( :midi-grace-durratio ) #f)        
        (( :midi-accent-velratio ) #f)
        (( :midi-marcato-vel ) #f)
        (( :midi-slur-overlap-dur ) #f)
        (( :midi-tenuto-dur ) #f)
        (( :midi-fermata-durratio ) #f)
        (( :midi-breath-dur ) #f)
        (( :midi-harmonic-prog ) #f)
        (( :midi-pizz-prog ) #f)
        (else #f)))
    ;; use id as default chan if its an integer 
    (unless chan (set! chan (if (integer? myid) myid 0)))
    ;; add dynamic if not same as last note.
    (write-event (make <midi> :time (event-off obj)
                       :amplitude ampl
                       :keynum (event-note obj)
                       :duration (event-dur obj)
                       :channel chan)
                 fil scoretime)))



