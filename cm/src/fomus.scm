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
   (timesigs :init-keyword :timesigs :init-value '()
            :accessor fomus-stream-timesigs)
   (keysigs :init-keyword :keysigs :init-value '()
            :accessor fomus-stream-keysigs))
  :name 'fomus-stream
  :metaclass <io-class>
  :file-types '("*.fms" "*.ly")) ;; add Enigma and MusicXML...
         
(define-method* (object-time (obj <base-event>))
  (event-off obj))

(define-method* (open-io (io <fomus-stream>) dir . args)
  args
  (when (eq? dir ':output)
    (let ((parts (fomus-stream-parts io))
          (tsigs (fomus-stream-timesigs io))
          (ksigs (fomus-stream-keysigs io)))
      ;; check for singles
      (unless (list? parts)
        (set! (fomus-stream-parts io) 
              (if parts (list parts) (list))))
      (unless (list? tsigs)
        (set! (fomus-stream-timesigs io) 
              (if tsigs (list tsigs) (list))))
      (unless (list? ksigs)
        (set! (fomus-stream-keysigs io) 
              (if ksigs (list ksigs) (list))))
      ;; flush any existing events
      (for-each (lambda (p) (set! (part-events p) (list)))
                (fomus-stream-parts io))
      (set! (io-open io) #t))))
    
(define-method* (close-io (io <fomus-stream>) . mode)
  (let ((err? (and (not (null? mode))
                   (eq? (car mode) ':error))))
    (set! (io-open io) #f)
    (unless err?
      (apply (function fomus)
             ;; IS THIS HOW TO SPECIFY the OUTPUT FILE??
             :base-filename (io-filename io)
             :parts (fomus-stream-parts io)
             :timesigs (fomus-stream-timesigs io)
             :keysigs (fomus-stream-keysigs io)
             (event-stream-args io)))))

(define-method* (write-event (obj <base-event>) (fil <fomus-stream>) scoretime)
  (let* ((parts (fomus-stream-parts fil))
         (theid (event-id obj))
         (part? (do ((tail parts (cdr tail))
                     (flag #f))
                    ((or (null? tail) flag) flag)
                  (if (eq? theid (part-id (car tail)))
                      (set! flag (car tail))))))
    (cond ((not part?)
           (set! part? (fomus-newpart theid))
           (set! (fomus-stream-parts fil)
                 (cons part? parts)))
          (else
           (set! part? (car part?))))
    ;; use score time not local time.
    (set! (event-off obj) scoretime)
    (set! (part-events part?)
          (cons obj (part-events part?)))
    obj))

(define-method* (write-event (obj <timesig>) (fil <fomus-stream>) scoretime)
  ;; use score time not local time.
  (set! (event-off obj) scoretime)
  (set! (fomus-stream-timesigs fil)
        (cons obj (fomus-stream-timesigs fil)))
  )

(define-method* (write-event (obj <keysig>) (fil <fomus-stream>) scoretime)
  ;; use score time not local time.
  (set! (event-off obj) scoretime)
  (set! (fomus-stream-keysigs fil)
        (cons obj (fomus-stream-keysigs fil)))
  )

;;; Todo: add write-event method for <midi> as well...



    
