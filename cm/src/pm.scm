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

;;; each midiport stream can handle 1 input and/or 1 output
;;; connection.  open streams are held as a list: (<input><output>)
;;; where either value can be a pointer to an open PortMidiStream or
;;; #f

(define-class* <portmidi-stream> (<event-stream> <midi-stream-mixin>)
  ((input :init-value #t :init-keyword :input
         :accessor portmidi-input)
   (output :init-value #t :init-keyword :output
           :accessor portmidi-output)
   (latency :init-value 100 :init-keyword :latency
            :accessor portmidi-latency)
   (inbufsize :init-value 64 :init-keyword :inbuf-size
              :accessor portmidi-inbuf-size)
   (outbufsize :init-value 256 :init-keyword :outbuf-size
               :accessor portmidi-outbuf-size)
   ;; data list: (<thread> #'stopper <evbuf> <len>)
   (receive :init-value (list #f #f #f #f)
            :accessor portmidi-receive)
   (filter :init-value 0 :init-keyword :filter
           :accessor portmidi-filter)
   (mask :init-value 0 :init-keyword :channel-mask
         :accessor portmidi-channel-mask)
   (offset :init-value 0 :init-keyword :offset 
           :accessor portmidi-offset))
  :name 'portmidi-stream
  :metaclass <io-class>
  :file-types '("*.pm"))

(define-object-printer* ((obj <portmidi-stream>) port)
  (let ((name (object-name obj))
        (pids (event-stream-stream obj))
        (*print-case* ':downcase)) ; noop in scheme
    (set! name
          (if name 
              (format nil "~a \"~a\"" (class-name (class-of obj)) name)
              (format nil "~a" (class-name (class-of obj)))))
    (if pids
        (if (car pids)
            (if (cadr pids)
                (format port "#<~a (in:~d out:~d)>"
                        name (car pids) (cadr pids))
                (format port "#<~a (in:~d)>"
                        name (car pids)))
            (if (cadr pids)
                (format port "#<~a (out:~d)>" 
                        name (cadr pids))
                (format port "#<~a>" name)))
        (format port "#<~a>" name))))
            
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
                          ((not (eq? d (list-prop l :type))) #f)
                          ((string? i)
                           (if (string-ci=? i (list-prop l :name))
                               (list-prop l :id)
                               #f))
                          ((integer? i)
                           (if (eq? (list-prop l :id) i)
                               i
                               #f))
                          (else #f))))
            (bsiz (portmidi-outbuf-size obj))
            (idev #f)
            (odev #f)
            (pids (list #f #f))
            (data (list #f #f)))
        (do ((tail (pm:GetDeviceDescriptions) (cdr tail))
             (i (portmidi-input obj))
             (o (portmidi-output obj)))
            ((null? tail) #f)
          (if (and i (not idev))
              (set! idev ( getd i ':input (car tail))))
          (if (and o (not odev))
              (set! odev ( getd o ':output (car tail)))))
        (pm:TimeStart)
        (set! (object-time obj) 0)
        (when idev
          (set-car! pids idev)
          (set-car! data 
                    (pm:OpenInputStream
                     idev (if (pair? bsiz) (car bsiz) bsiz))))
        (when odev
          (set-car! (cdr pids) odev)
          (set-car! (cdr data) 
                    (pm:OpenOutputStream
                     odev (if (pair? bsiz) (cadr bsiz) bsiz)
                     (portmidi-latency obj))))
        (set! (event-stream-stream obj) pids)
        (set! (io-open obj) data))))
  obj)

(define-method* (close-io (obj <portmidi-stream>) . mode)
  (when (and (eq? (car mode) ':force)
             (io-open obj))
    (let ((data (io-open obj)))
      (if (car data)
          (pm:StreamClose (car data)))
      (if (cadr data)
          (pm:StreamClose (cadr data)))
      (set! (event-stream-stream obj) #f)
      (set! (io-open obj) #f)))
  (values))

(define-method* (initialize-io (obj <portmidi-stream>))
  ;; this method will have to distinguish between rt and non-rt
  ;; scheduling and also input vs output.
  (let ((io (car (io-open obj)))
        (fn (lambda (o s)
              (let ((f (portmidi-filter o))
                    (m (portmidi-channel-mask o)))
                (if (pair? f)
                    (apply (function pm:StreamSetFilter) s f)
                    (pm:StreamSetFilter s f))
                (pm:StreamSetChannelMask s m)))))
    ;; input stream
    (if (car io) ( fn obj (car io)))
    ;; output stream
    (if (cadr io) ( fn obj (cadr io)))
    ;;cache current MILLISECOND time offset
    (set! (portmidi-offset obj) (pm:Time))
    ;; stream's time is kept in seconds. maybe stream should have a
    ;; scaler like midi-file so user could work with whatever quanta
    ;; they wanted...
    (set! (object-time obj) 0)
    (channel-tuning-init obj)))

;; a "midi.port" convenience for working with just one stream...

(define (portmidi-open . args)
  (apply #'open-io "midi-port.pm" #t args))

(define (portmidi-open? . args)
  (with-args (args &optional (port (find-object "midi-port.pm" )))
    (if port 
        (let ((io (io-open port)))
          (if io
              (if (car io)
                  (if (cadr io) :inout :in)
                  (if (cadr io) :out #f))
              #f))
        #f)))

(define (portmidi-close . args)
  (with-args (args &optional (port (find-object "midi-port.pm" )))
    (if (portmidi-open? port)
        (begin (close-io port ':force) #t)
        #f)))

;;;
;;; message format conversion
;;;

(define (pm-message->midi-message pmm)
  (let ((status (pm:Message.status pmm)))
    (if (< status #xf0)                 ; channel message
        (if (logtest status #b10000000) ; normal status
            (let ((stat (ash (logand status #xf0) -4))
                  (dat2 (pm:Message.data2 pmm)))
              (when (and (= stat +ml-note-on-opcode+)
                         (= 0 dat2))
                (set! stat +ml-note-off-opcode+)
                (set! dat2 127))
              (make-channel-message stat
                                    (logand status #x0f)
                                    (pm:Message.data1 pmm)
                                    dat2))
            (err "pm-message->midi-message: running status :("))
        (if (= status #xff)
            (err "pm-message->midi-message: meta message??!")
            (let ((type (logand status #x0f)))
              (if (= type 0)            ; sysex
                  (err "pm-message->midi-message: sysex :(")
                  (make-system-message (logior (ash type 4) #xf)
                                       0 
                                       (pm:Message.data1 pmm)
                                       (pm:Message.data2 pmm))))))))

(define (midi-message->pm-message mm)
  (pm:Message (logior (ash (midimsg-upper-status mm) 4)
                      (midimsg-lower-status mm))
              (channel-message-data1 mm)
              (channel-message-data2 mm)))

(define-method* (midi-write-message (obj <integer> )
                                    (str <portmidi-stream>)
                                    scoretime data)
  data
  (cond ((sysex-p obj)
         ;; add in later..
         )
        ((or (channel-message-p obj)
             (system-message-p obj))
         (pm:StreamWriteShort 
          (second (io-open str))        ; output stream
          ;; add in time offset in stream. this should check latency...
          (+ (inexact->exact (round (* scoretime 1000)))
             (portmidi-offset str))
          (midi-message->pm-message obj)))
        (else #f)))

;;;
;;; message writing
;;; portmidi behaves almost like a midi-file: (1) handles only true
;;; midi messages (ie no durations); (2) data must always be sent in
;;; time-increasing order; (3) messages are just bytes. the only real
;;; difference between writing to portmidi vs midi-files is that
;;; midi-file time is delta but portmidi time is absolute.
;;;

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
      (midi-write-message (make-note-on chan keyn ampl)
                          str
                          scoretime
                          #f)
      ;; enqueue a note off in scheduler's queue
      (enqueue (make-note-off chan keyn 127)
               (+ scoretime (midi-duration obj))
               #f))
    (values)))

(define-method* (write-event (obj <midi-event>) (str <portmidi-stream>)
                             scoretime)
  (midi-write-message (midi-event->midi-message obj) str scoretime #f))


(define-method* (write-event (obj <integer>) (str <portmidi-stream>)
                             scoretime)
  (midi-write-message obj str scoretime #f) )

;
; (pm:GetDeviceDescriptions)
; (setq foo (portmidi-open :input nil :output 3))
; (events (loop for d from 0 to 6 by .5
;             for k from 60
;             collect (new midi :time d :duration .1 
;                          :keynum k :amplitude .9))
;        foo)


;;;
;;; message receiving
;;;

;(define-method* (receive? (str <portmidi-stream>))
;  (if (portmidi-receive str) #t #f))

(define-method* (receive! (str <portmidi-stream>) hook)
  (let* ((data (portmidi-receive str)) ; (<thread> <stop> <buf> <len>)
         (stop #f)) 
    ;; the receiving thread's do loop terminates as soon as the stop
    ;; flag is #t. to stop we call the cached "stopper" closure that
    ;; sets the var to #t.
    (cond ((not hook) 
           ;; stop receiving if thread active
           (when (first data)
             (let ((stopper (second data)))
               ;; call cached stopper to set the stop flag. 
               ( stopper ))
             (list-set! data 0 #f)
             (list-set! data 1 #f))
           #f)
          ((not (procedure? hook))
           (err "Receive: hook is not a function: ~s" hook))
          ((not (member (portmidi-open? str) '(:in :inout)))
           (err "Stream not open for input: ~S." str))
          ((first data)
           (err "Can't set input hook: another hook is running!"))
          (else
           ;; ready to go
           (let* ((in (first (io-open str))) ; pm stream
                  (sz (portmidi-inbuf-size str)) ; bufsiz
                  (bf (third data))  ; old buffer
                  (so (fourth data)) ; old bufsiz
                  (th #f) ; thread
                  (st #f) ; thread stopper
                  (fn #f) ; mapper
                  )
             ;; see if we have to free old buffer
             (when (and bf (not (eq? sz so)))
               (pm:EventBufferFree bf)
               (set! bf #f))
             (unless bf
               (set! bf (pm:EventBufferNew sz)))
             (set! fn (lambda (mm ms)
                        ( hook (pm-message->midi-message mm) ms)))
             (set! th
                   (make-thread
                    (lambda ()
                      (do ((n #f))
                          (stop  
                           #f)
                        (when (pm:StreamPoll in)
                          (set! n (pm:StreamRead in bf sz))
                          (when (> n 0)
                            (pm:EventBufferMap fn bf n)))))))
             (set! st (lambda () (set! stop #t)))
             (list-set! data 0 th)
             (list-set! data 1 st)
             (list-set! data 2 bf)
             (list-set! data 3 sz)
             (thread-start! th)
             #t)))))

;
; input test:
; (pprint (pm:GetDeviceDescriptions))
; (setq a (portmidi-open :input 1 :output nil))
; (defun prinm (mm mt) (midi-print-message mm mt) (terpri))
; (receive! a #'prinm)
; ...play keyboard...
; (receive! a #f)
