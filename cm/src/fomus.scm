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

(define-class* <fomus-stream> (<event-stream>)
  ((parts :init-keyword :parts :init-value '()
          :accessor fomus-stream-parts)
   (global :init-keyword :global :init-value '()
           :accessor fomus-stream-global)
   (view :init-keyword :view :init-value #f :accessor fomus-stream-view)
   )
  :name 'fomus-stream
  :metaclass <io-class>
  :file-types '("*.fms" "*.xml" "*.ly")) 
         
(define-method* (object-time (obj <event-base>))
  (event-off obj))

(define-method* (open-io (io <fomus-stream>) dir . args)
  args
  (when (eq? dir ':output)
    (let ((parts (fomus-stream-parts io))
          (globs (fomus-stream-global io)))
      ;; check for singles
      (unless (list? parts)
        (set! (fomus-stream-parts io) 
              (if parts (list parts) (list))))
      (unless (list? globs)
        (set! (fomus-stream-global io) 
              (if globs (list globs) (list))))
      ;; flush existing data from parts
      (for-each (lambda (p)
                  (set! (obj-id p) #f)
                  (set! (part-events p) (list)))
                (fomus-stream-parts io))
      (set! (io-open io) #t)))
  io)
    
(define-method* (close-io (io <fomus-stream>) . mode)
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
                                    :view (fomus-stream-view io))
                              args))))
        (apply (function fomus)
               :parts (fomus-stream-parts io)
               :global (fomus-stream-global io)
               args)))))

(define (fomus-stream-part stream id)
  (do ((tail (fomus-stream-parts stream) (cdr tail))
       (part #f))
      ((or (null? tail) part) 
       (when (not part)
         (set! part (make-part :partid id))
         (set! (fomus-stream-parts stream)
               (cons part (fomus-stream-parts stream))))
       part)
    (if (eq? id (obj-partid (car tail)))
        (set! part (car tail)))))

(define-method* (write-event (obj <event-base>) (fil <fomus-stream>) scoretime)
  (let ((part (fomus-stream-part fil (obj-partid obj))))
    ;; use score time not local time.
    (set! (event-off obj) scoretime)
    (set! (part-events part)
          (cons obj (part-events part)))
    obj))

(define-method* (write-event (obj <midi>) (fil <fomus-stream>) scoretime)
  (let* ((myid (midi-channel obj))
         (part (fomus-stream-part fil myid))
         (ampl (midi-amplitude obj))
         (marks '()))
    ;; add dynamic if not same as last note.
    (when (<= 0 ampl 1)
      (let ((this (list-ref '(:pppp :ppp :pp :p :mp 
                              :mf :f :ff :fff :ffff :fffff)
                            (inexact->exact
                             (floor (/ ampl .1))))))
          (unless (eq? this (obj-id part))
            (set! marks (list this))
            (set! (obj-id part) this))))
    (set! (part-events part)
          (cons (make-note :partid myid
                           :off scoretime
                           :note (midi-keynum obj)
                           :dur (midi-duration obj)
                           :marks marks)
                (part-events part)))))


