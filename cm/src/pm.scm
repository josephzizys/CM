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

(define *portmidi-default-input* #f)
(define *portmidi-default-output* #f)
(define *portmidi-default-latency* 100)
(define *portmidi-default-inbuf-size* 512)
(define *portmidi-default-outbuf-size* 2048)
(define *portmidi-default-filter* 0)
(define *portmidi-default-mask* 0)

(define-class* <portmidi-stream> (<rt-stream> <midi-stream-mixin>)
  ((input :init-value *portmidi-default-input* :init-keyword :input
         :accessor portmidi-input)
   (output :init-value *portmidi-default-output* :init-keyword :output
           :accessor portmidi-output)
   (latency :init-value *portmidi-default-latency* :init-keyword :latency
            :accessor rt-stream-latency)
   (inbufsize :init-value *portmidi-default-inbuf-size*
              :init-keyword :inbuf-size
              :accessor portmidi-inbuf-size)
   (outbufsize :init-value *portmidi-default-outbuf-size* 
               :init-keyword :outbuf-size
               :accessor portmidi-outbuf-size)
   ;; data list: (<thread> #'stopper <evbuf> <len>)
   (receive-data :init-value (list #f #f #f #f)
            :accessor rt-stream-receive-data)
   (receive-mode :init-value :message :init-keyword :receive-mode
            :accessor rt-stream-receive-mode)
   (filter :init-value *portmidi-default-filter* :init-keyword :filter
           :accessor portmidi-filter)
   (mask :init-value *portmidi-default-mask* :init-keyword :channel-mask
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
                    ;; return device description of user spec (string or int)
                    (cond ((not i) #f)
                          ((eq? i #t)
                           ;; default
                           (pm:GetDeviceDescription
                            (if (eq? d ':input)
                                (pm:GetDefaultInputDeviceID)
                                (pm:GetDefaultOutputDeviceID)))
                           )
                          ((not (eq? d (list-prop l ':type))) #f)
                          ((string? i)
                           (if (string-ci=? i (list-prop l ':name))
                               l ;(list-prop l :id)
                               #f))
                          ((integer? i)
                           (if (eq? (list-prop l ':id) i)
                               l ;i
                               #f))
                          (else #f))))
            (devs (pm:GetDeviceDescriptions) )
            (bsiz (portmidi-outbuf-size obj))
            (idev #f)
            (odev #f)
            (pids (list #f #f))
            (data (list #f #f)))
        (do ((tail devs (cdr tail))
             (i (portmidi-input obj))
             (o (portmidi-output obj)))
            ((null? tail) #f)
          (if (and i (not idev))
              (set! idev ( getd i ':input (car tail))))
          (if (and o (not odev))
              (set! odev ( getd o ':output (car tail)))))
        ;; error checks: no devices, device already open, missing
        ;; devices
        (cond ((null? devs)
               (err "open-io: no portmidi devices available."))
              ((and idev (list-prop idev ':open))
               (err "open-io: portmidi input device ~D (~S) is already open."
                    (list-prop idev ':id) (list-prop idev ':name)))
              ((and odev (list-prop odev ':open))
               (err "open-io: portmidi output device ~D (~S) is already open."
                    (list-prop odev ':id) (list-prop odev ':name)))
              ((and (not idev) (not odev))
               (err "open-io: no portmidi :input or :output device was specified.")))
        (pm:TimeStart)
        (set! (object-time obj) 0)
        (when idev
          (set! idev (list-prop idev ':id))
          (set-car! pids idev)
          (set-car! data 
                    (pm:OpenInputStream
                     idev (if (pair? bsiz) (car bsiz) bsiz))))
        (when odev
          (set! odev (list-prop odev ':id))
          (set-car! (cdr pids) odev)
          (set-car! (cdr data) 
                    (pm:OpenOutputStream
                     odev (if (pair? bsiz) (cadr bsiz) bsiz)
                     (rt-stream-latency obj))))
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
  (let ((io (io-open obj))
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
        (let* ((a (rts?))
               (b (receiver?))
               (c (and a b)))
          (cond ((or a b)
                 (err "portmidi-close: Can't close port because ~a running."
                      (if c "rts and a receiver are"
                          (if b "a receiver is" "rts is"))))
                (else
                 (close-io port ':force)
                 port)))
        port)))

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
          ;; if we are running under a scheudler, add in time offset of stream
          ;; this should check latency...
          ;; else user is keeping track of it
          ;;          (if *scheduler*
          ;;              (+ (inexact->exact (round (* scoretime 1000)))
          ;;                 (portmidi-offset str))
          ;;              scoretime)
          (cond ((eq? *scheduler* ':asap)
                 (+ (inexact->exact (round (* scoretime 1000)))
                    (portmidi-offset str)))
                ((not *scheduler*) scoretime)
                (t ;; :threaded :periodic :specific
                 0))
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

;;;
;;; message receiving
;;;

(define-method* (set-receive-mode! (str <portmidi-stream>) mode)
  (unless (member mode '(:message :raw))
    (err "receive: ~s is not a portmidi receive mode." mode))
  (slot-set! str 'receive-mode mode))

(define-method* (init-receiver (str <portmidi-stream>) type)
  ;; called by set-receiver before hook is activated.
  ;; flush any messages already in input buffer
  (when (eq? type ':periodic)
    (unless (periodic-task-running? )
      (set-periodic-task-rate! (rt-stream-receive-rate str) :seconds)))
  (let ((idev (first (io-open str)))
        (data (rt-stream-receive-data str)))
    (when (pm:StreamPoll idev)
      (pm:StreamRead idev (third data) (fourth data)))))

(define-method* (deinit-receiver (str <portmidi-stream>) type)
  type
  ;;  called by remove-receiver after the periodic task has been withdrawn
  (let ((data (rt-stream-receive-data str))) ; (<thread> <stop> <buf> <len>)
    (when (first data)
      (list-set! data 0 #f)
      (list-set! data 1 #f))))

(define-method* (stream-receiver hook (str <portmidi-stream>) type)
  ;; hook is 2 arg lambda or nil, type is :threaded or :periodic
  (let* ((data (rt-stream-receive-data str)) ; (<thread> <stop> <buf> <len>)
         (mode (rt-stream-receive-mode str))
         (stop #f)) 
    ;; can receive either message/times or raw buffer/count
    (unless (member mode '(:message :raw))
      (err "receive: ~s is not a portmidi receive mode." mode))
    ;; the receiving thread's do loop terminates as soon as the stop
    ;; flag is #t. to stop we call the cached "stopper" closure that
    ;; sets the var to #t.
    (cond ((not (procedure? hook))
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
                  (rm (eq? mode ':message))
                  (th #f) ; thread
                  (st #f) ; thread stopper
                  (fn #f) ; mapper
                  (ra (rt-stream-receive-rate str))
                  )
             ;; see if we have to free old buffer
             (when (and bf (not (eq? sz so)))
               (pm:EventBufferFree bf)
               (set! bf #f))
             (unless bf
               (set! bf (pm:EventBufferNew sz)))
             (set! fn (lambda (mm ms)
                        ( hook (pm-message->midi-message mm) ms)))
             (case type
               ((:threaded )
                (set! th
                      (make-thread
                       (lambda ()
                         (do ((n #f))
                             (stop  
                              #f)
                           (cond ((pm:StreamPoll in)
                                  (set! n (pm:StreamRead in bf sz))
                                  (when (> n 0)
                                    (if rm (pm:EventBufferMap fn bf n)
                                        ( hook bf n))))
                                 (else
                                  ;; only sleep if no message??
                                  (thread-sleep! ra)))))))
                (set! st (lambda () (set! stop #t))))
               ((:periodic )
                (set! th
                      (lambda () 
                        (let ((n 0))
                          (when (pm:StreamPoll in)
                            (set! n (pm:StreamRead in bf sz))
                            (when (> n 0)
                              (if rm (pm:EventBufferMap fn bf n)
                                  ( hook bf n)))))))
                (set! st (lambda ()
                           (remove-periodic-task! :receive))))
               )
             ;; cache the stuff
             (list-set! data 0 th)
             (list-set! data 1 st)
             (list-set! data 2 bf)
             (list-set! data 3 sz)
             th)))))

(define-method* (receive (str <portmidi-stream>) . args)
  (let* ((n 0)
        (in (first (io-open str)))
        (bf (third (rt-stream-receive-data str)))
        (sz (portmidi-inbuf-size str))
        (hook (if (pair? args) (pop args) #f))
        (mode (if (pair? args) (pop args) #f))
        (rm (if (not mode) #t (eq? mode ':message)))
        (fn #f)
        (res #f))
    (cond ((pm:StreamPoll in)
           (if hook
               (begin
                 (set! fn (lambda (mm ms)
                            (hook (pm-message->midi-message mm) ms)))
                 (set! n (pm:StreamRead in bf sz))
                 (when (> n 0)
                   (if rm (pm:EventBufferMap fn bf n)
                     (hook bf n))
                   (set! res #t)))
             
             (begin
               (set! res '())
               (if rm
                   (set! fn (lambda (mm ms)
                              ms
                              (set! res (append! res (list (pm-message->midi-message mm))))))
                 (set! fn (lambda (mm ms)
                            ms
                            (set! res (append! res (list mm))))))
               (set! n (pm:StreamRead in bf sz))
               (when (> n 0)
                 (pm:EventBufferMap fn bf n))))))
    res))

;;;
;;; midi recording
;;;

(define (portmidi-record! seq . mp)
  (let* ((str (if (pair? mp) (car mp)
                  (find-object "midi-port.pm" )))
         (opn (if (null? str) #f
                  (portmidi-open? str))))
    (cond ((not opn)
           (err "portmidi-record!: requires portmidi stream open for input."))
          ((eq? opn ':out)
           (err "portmidi-record!: ~s is only open for output." str))
          (else
           ;; otherwise set true if we also perform midi thru
           (set! opn (if (eq? opn :inout) #t #f))))
    (if (not seq)
        (remove-receiver! str)
        (let ((ins (if (subobjects seq) #t #f)) ; insert into existing seq
              (off #f)                          ; time offset
              (map (make-list 16 (list)))) ; channel map for on/off pairing
          (if (receiver? str)
              (err "portmidi-record!: a portmidi receiver is already active."))
          (set-receiver!
           (lambda (mm ms)
             (if opn (write-event mm str ms)) ; midi thru 
             (if (not off) (set! off ms)) ; cache time of first recorded message
             (cond ((or (note-off-p mm)
                        (and (note-on-p mm) (= 0 (note-on-velocity mm))))
                    (let* ((chn (note-off-channel mm))
                           (key (note-off-key mm))
                           (ons (list-ref map chn)))
                      ;; ons is time ordered list ((<on> . <ms>) ...)
                      (when (pair? ons) ; have on to pair with
                        (let ((aon #f)  ; pair with earliest on
                              (obj #f))
                          (cond ((= (note-on-key (car (car ons))) key)
                                 (set! aon (car ons))
                                 (list-set! map chn (cdr ons)))
                                (else
                                 ;; search for corresponding on and splice out
                                 (do ()
                                     ((or (null? (cdr ons)) aon)
                                      #f)
                                   (if (= key (note-on-key (car (car (cdr ons)))))
                                       (begin (set! aon (car (cdr ons)))
                                              (set-cdr! ons (cddr ons)))
                                       (set! ons (cdr ons))))))
                          ;; aon is (<msg> . <ms>)
                          (when aon
                            (set! obj (make-instance <midi> 
                                                     :time (/ (- (cdr aon) off) 1000.0)
                                                     :duration (/ (- ms (cdr aon)) 1000.0)
                                                     :keynum (note-on-key (car aon))
                                                     :amplitude (/ (note-on-velocity
                                                                    (car aon))
                                                                   127.0)
                                                     :channel (note-on-channel (car aon))))
                            ;; insert if seq contained objects else append
                            (if ins (insert-object seq obj)
                                (append-object obj seq)))))))
                   ((note-on-p mm)
                    (let* ((chn (note-on-channel mm))
                           (ons (list-ref map chn)))
                      ;; append mm to time ordered ons ((<on> . <ms>) ...)
                      (if (null? ons)
                          (list-set! map chn (list (cons mm ms)))
                          (append! ons (list (cons mm ms))))))
                   ((channel-message-p mm)
                    (midi-message->midi-event mm :time (/ (- ms off) 1000.0)))))
           str)))))
