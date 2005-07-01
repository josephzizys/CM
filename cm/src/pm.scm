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
             :accessor portmidi-receiver)
   (filter :init-value #f :init-keyword :filter
           :accessor portmidi-filter)
   (offset :init-value 0 :init-keyword :offset 
           :accessor portmidi-offset))
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
                           (if (eq? (third l) i)
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
              (set! odev ( getd o ':output (car tail)))))
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
  ;; this method will have to distinguish between rt and non-rt
  ;; scheduling and also input vs output.

  (let ((in (car (io-open obj))))
    (when in
      (let ((filt (or (portmidi-filter obj)
                      0)))
        (if (pair? filt)
            (apply (function pm:SetFilter) in filt)
            (pm:SetFilter in filt)))))

  ;;cache current MILLISECOND time offset
  (set! (portmidi-offset obj) (pm:TimerTime))
  ;; stream's time is kept in seconds. maybe stream should have a
  ;; scaler like midi-file so user could work with whatever quanta
  ;; they wanted...
  (set! (object-time obj) 0)
  (channel-tuning-init obj))

;; THIS SHOULD BE MERGED WITH 
(define (flush-pending-offs2 mf at)
  (let ((time (or at most-positive-fixnum)))
    (do ((qe (%q-peek %offs) (%q-peek %offs)))
	((or (null? qe) (> (%qe-time qe) time))
	 #f)
      (%q-pop %offs)      
;      (format t "~%flushing ~S" (%qe-time qe))
      (midi-write-message (%qe-object qe) 
			  mf
                          (%qe-time qe)
			  #f)
      (%qe-dealloc %offs qe))))

(define-method* (deinitialize-io (obj <portmidi-stream>))
  ;; uncache current time offset
  (flush-pending-offs2 obj #f))

;;; midi.pm

(define (portmidi-open . args)
  (apply #'open-io "midi.pm" #t args))

(define (portmidi-open? . args)
  (with-args (args &optional (port (find-object "midi.pm" )))
    (if (and port (io-open port))
        #t
        #f)))

(define (portmidi-close . args)
  (with-args (args &optional (port (find-object "midi.pm" )))
    (if (portmidi-open? port)
        (begin (close-io port ':force) #t)
        #f)))

(define-method* (midi-write-message (obj <integer> )
                                    (str <portmidi-stream>)
                                    scoretime data)
  data
  (cond ((sysex-p obj)
         ;; add in later..
         )
        ((or (channel-message-p obj)
             (system-message-p obj))
;         (terpri)
;         (midi-print-message 
;          obj (inexact->exact (round (* scoretime 1000))))
         (pm:WriteShort 
          (second (io-open str))        ; output stream
          ;; add in time offset in stream
          (+ (inexact->exact (round (* scoretime 1000)))
             (portmidi-offset str))
          (pm:Message (logior (ash (midimsg-upper-status obj) 4)
                              (midimsg-lower-status obj))
                      (channel-message-data1 obj)
                      (channel-message-data2 obj)))
         )
        (else #f)))

;;; portmidi behaves almost like a midi-file: (1) handles only true
;;; midi messages (ie no durations); (2) data must be sent over in
;;; time-increasing order; (3) messages are just bytes. the only real
;;; difference between outputting to portmidi vs midi-files is that
;;; times in midi-files are deltas but portmidi uses absolute.

(define-method* (write-event (obj <midi> ) (str <portmidi-stream>)
                             scoretime)
  (let ((keyn (midi-keynum obj))
        (chan (midi-channel obj))
        (ampl (midi-amplitude obj)))
    ;; if amplitude is zero then don't output anything
    (ensure-velocity ampl keyn)
    (ensure-microtuning keyn chan str)
    ;; if "resting" then dont update anything
    (unless (< keyn 0)                  ; rest
      (unless (null? (%q-head %offs))
        (flush-pending-offs2 str scoretime))
      (midi-write-message (make-note-on chan keyn ampl)
                          str
                          scoretime
                          #f)
      (%q-insert (%qe-alloc %offs
                            (+ scoretime (midi-duration obj))
                            #f
                            (make-note-off chan keyn 127))
                 %offs))
    (values)))

(define-method* (write-event (obj <midi-event>) (str <portmidi-stream>)
                             scoretime)
  ;; flush here too?
  (unless (null? (%q-head %offs))
    (flush-pending-offs2 str scoretime))
  (midi-write-message (midi-event->midi-message obj) str scoretime #f))

(define-method* (write-event (obj <integer>) (str <portmidi-stream>)
                             scoretime)
  ;; flush here too?
  (unless (null? (%q-head %offs))
    (flush-pending-offs2 str scoretime))
  (midi-write-message obj str scoretime #f) )


;;; real-time support. have to think about this...

(define-method* (rt-output ev (out <portmidi-stream>) . args)
  ;; output ev to Midishare
  (with-args (args &optional ahead)
    (if ahead
      (write-event ev out (+ ahead (pm:TimerTime)))
      (write-event ev out 0))
    (values)))

(define-method* (rt-now (io <portmidi-stream>))
  (pm:TimerTime))

;;; (pm:GetDeviceDescriptions)
;;; (setq foo (portmidi-open :input nil :output 3))
;;; (events (loop for d from 0 to 8 by .5
;;;             for k from 60
;;;             collect (new midi :time d :duration 1 
;;;                          :keynum k
;;;                          :amplitude .9))
;;;        foo)


