;;; **********************************************************************
;;; Copyright (C) 2005 Heinrich Taube
;;; 
;;; This program is free software; you can redistribute it and/or
;;; modify it under the terms of the Lisp Lesser Gnu Public License.
;;; See http://www.cliki.net/LLGPL for the terms of this agreement.
;;; **********************************************************************

;;; $Name$
;;; $Revision$
;;; $Date$

(in-package :cm)

(define-class* <portmidi-stream> (<event-stream> <midi-stream-mixin>)
  ((input :init-value #t :init-keyword :input
         :accessor portmidi-input)
   (output :init-value #t :init-keyword :output
           :accessor portmidi-output)
   (latency :init-value 1000 :init-keyword :latency
            :accessor portmidi-latency)
   (bufsize :init-value 256 :init-keyword :bufsize
            :accessor portmidi-bufsize)
   (receiver :init-value #f :init-keyword :receiver
             :accessor portmidi-receiver))
  :name 'portmidi-stream
  :metaclass <io-class>
  :file-types '("*.pm"))

(define-method* (open-io (obj <portmidi-stream>) dir . args)
  dir args
  (when (not (io-open obj)) ; already open...
    (unless (pm:portmidi)
      (err "Can't open MidiShare connection: MidiShare not loaded."))
    (unless (event-stream-stream obj)
      (let ((getd (lambda (i d l)
                    ;; return device ID of user spec (string or int)
                    (cond ((not i) #f)
                          ((eq? i #t)
                           ;; default
                           (if (eq? d ':input)
                               (pm:GetDefaultInputDeviceID)
                               (pm:GetDefaultOutputDeviceID)))
                          ((not (eq? d (second l))) #f)
                          ((string? i)
                           (if (string-ci=? i (first l))
                               (third l)
                               #f))
                          ((integer? i)
                           (if (eql (third l) i)
                               (third l)
                               #f))
                          (else #f))))
            (bsiz (portmidi-bufsize obj))
            (idev #f)
            (odev #f)
            (data (list #f #f)))
        (do ((tail (pm:GetDeviceDescriptions) (cdr tail))
             (i (portmidi-input obj))
             (o (portmidi-output obj)))
            ((null? tail) #f)
          (if (and i (not idev))
              (set! idev ( getd i ':input (car tail))))
          (if (and o (not odev))
              (set! odev ( getd i ':output (car tail)))))
        (pm:TimerStart)
        (set! (object-time obj) 0)
        (when idev
          (set-car! data 
                    (pm:OpenInput idev 
                                  (if (pair? bsiz) (car bsiz) bsiz))))
        (when odev
          (set-car! (cdr data) 
                    (pm:OpenOutput odev
                                   (if (pair? bsiz) (cadr bsiz) bsiz)
                                   (portmidi-latency obj))))
        (set! (event-stream-stream obj) data)
        (set! (io-open obj) data))))
  obj)

(define-method* (close-io (obj <portmidi-stream>) . mode)
  (when (and (eq? (car mode) ':force)
             (io-open obj))
    (let ((data (io-open obj)))
      (if (car data)
          (pm:close (car data)))
      (if (cadr data)
          (pm:close (cadr data)))
      (set! (event-stream-stream obj) #f)
      (set! (io-open obj) #f)))
  (values))

(define-method* (initialize-io (obj <portmidi-stream>))
  ;; cache current time offset
  (set! (object-time obj) (pm:TimerTime))
  (channel-tuning-init obj))

(define-method* (deinitialize-io (obj <portmidi-stream>))
  ;; uncache current time offset
  (set! (object-time obj) 0))

(define (portmidi-open . args)
  (apply #'open-io "midiport.pm" #t args))

(define (portmidi-open? io)
  (if (io-open io) #t #f))

(define-method* (write-event (obj <integer> ) (str <portmidi-stream>)
                             scoretime)
  (cond ((sysex-p obj)
         ;; add in later..
         )
        ((or (channel-message-p obj)
             (system-message-p obj))
         (pm:WriteShort 
          (second (io-open str))        ; output stream
          (+ (inexact->exact (round (* scoretime 1000)))
             (object-time str))
          (pm:Message (logior (ash (midimsg-upper-status obj) 4)
                              (midimsg-lower-status obj))
                      (channel-message-data1 obj)
                      (channel-message-data2 obj))))
        (else #f)))

;;;
;;; portmidi behaves almost like a midi-file in that it (1) handles
;;; only true midi data (ie no durations); (2) data must be sent in
;;; time-increasing order; (3) messages are really just bytes. so it
;;; would be nice if there were a single stream that handled this. the
;;; essential difference between portmidi and midi-files is that times
;;; in midi-files are deltas but are absolute in portmidi.

(define-method* (write-event (obj <midi> ) (str <portmidi-stream>)
                             scoretime)
  obj str scoretime
  )

(define-method* (write-event (obj <midi-event>) (str <portmidi-stream>)
                             scoretime)
  (write-event (midi-event->midi-message obj) str scoretime))






; (setq foo (portmidi-open ))
; (describe foo)
; (write-event (make-note-on 0 60 100) foo 0)
; (write-event (make-note-off 0 60 100) foo 0)

