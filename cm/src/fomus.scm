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
         
(define-method* (object-time (obj <event-base*>))
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
      (let* ((args (event-stream-args io))
             (bend (list-prop args ':backend)))
        (unless bend
          (let* ((file (io-filename io))
                 (type (filename-type io)))
            (cond ((equal? type "ly")
                   (set! bend ':lilypond))
                  ((equal? type "etf")
                   (set! bend ':etf))
                  ((equal? type "xml")
                   (set! bend ':xml))
                  (else
                   (set! bend ':fms)))
            (set! args (cons* ':backend bend :filename file 
                              args))))
      (apply (function fomus)
             :parts (fomus-stream-parts io)
             :timesigs (fomus-stream-timesigs io)
             :keysigs (fomus-stream-keysigs io)
             args)))))

(define-method* (write-event (obj <event-base*>) (fil <fomus-stream>) scoretime)
  (let* ((parts (fomus-stream-parts fil))
         (theid (obj-partid obj))
         (part? (do ((tail parts (cdr tail))
                     (flag #f))
                    ((or (null? tail) flag) flag)
                  (if (eq? theid (obj-partid (car tail)))
                      (set! flag (car tail))))))
    (when (not part?)
      (set! part? (fomus-newpart theid))
      (set! (fomus-stream-parts fil)
            (cons part? parts)))
    ;; use score time not local time.
    (set! (event-off obj) scoretime)
    (set! (part-events part?)
          (cons obj (part-events part?)))
    obj))


(define-method* (write-event (obj <midi>) (file <fomus-stream>) scoretime)
  (write-event (fomus-newnote :partid (midi-channel obj)
                              :note (midi-keynum obj)
                              :dur (midi-duration obj)
                              :marks
                              (let ((amp (midi-amplitude obj)))
                                (if (<= 0 amp 1)
                                    (list-ref '(:pppp :ppp :pp :p :mp 
                                                :mf :f :ff :fff :ffff)
                                              (inexact->exact
                                               (floor (/ amp .1))))
                                    #f)))
               file scoretime))


;0    1   2  3  4 5  6 7  8   9
;pppp ppp pp p mp mf f ff fff ffff
;(floor 1 .1)




    
