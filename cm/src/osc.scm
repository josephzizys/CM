;;; **********************************************************************
;;; Copyright (C) 2005 Todd Ingalls, Heinrich Taube
;;; 
;;; This program is free software; you can redistribute it and/or
;;; modify it under the terms of the Lisp Lesser Gnu Public License.
;;; See http://www.cliki.net/LLGPL for the terms of this agreement.
;;; **********************************************************************

;;; $Name$
;;; $Revision$
;;; $Date$

(define-method* (make-byte-vector (int <integer>))
  (u8vector (ash (logand int #xff000000) -24) 
            (ash (logand int #xff0000) -16) 
            (ash (logand int #xff00) -8)
            (logand int #xff)))


; (make-byte-vector #x4030201)
; #(4 3 2 1)

(define-method* (make-byte-vector (flo <real>))
  (if (zero? flo)
    (make-u8vector 4 0)
    (multiple-value-bind (signif expon sign)
                         (integer-decode-float flo)
                         (let ((sign-bit (if (< sign 0) #x80000000 0))
                               (exponent (+ expon 23 127))
                               (fraction (logand (inexact->exact signif) #x7fffff)))
                           (make-byte-vector (logior sign-bit (ash exponent 23) fraction))))))

; (define foo '(2353.4402 19497.84 1709.3262 1157.6047 786.9287 -8034.8916 -6878.1816 6363.0913 -10773.487 -16749.674))
; (loop for x in foo collect (make-byte-vector x))
; (#(57 19 23 11) #(58 152 83 174) #(56 213 170 112) #(56 144 179 90) #(56 68 187 112) #(185 251 23 34) #(185 214 241 116) #(57 198 216 187) #(186 40 85 243) #(186 130 219 89))

(define-method* (make-byte-vector (str <string>))
  (let* ((len (string-length str))
	 (pad (- 4 (modulo len 4)))
	 (vec (make-u8vector (+ len pad) 0)))
    (do ((i 0 (+ i 1)))
        ((= i len) vec)
      (u8vector-set! vec i (char->integer (string-ref str i))))))

; (make-byte-vector "Hello, world!")
;#(72 101 108 108 111 44 32 119 111 114 108 100 33 0 0 0)

(define-method* (make-byte-vector (sym <symbol>))
  (let ((str (string-downcase (symbol->string sym))))
    (make-byte-vector str)))

; (make-byte-vector 'zippy)
; #(122 105 112 112 121 0 0 0)

;;; for osc files. don't care about universal time

(define (make-file-timetag offset)
  (multiple-value-bind (int rem) (clfloor offset)
    (u8vector-append (make-byte-vector int)
                     (make-byte-vector
                      (inexact->exact (floor (* rem #xffffffff)))))))

;;as part of an OSC message the types of each token are sent

(define-method* (return-type-code (int <integer>))
  (char->integer #\i))

(define-method* (return-type-code (flo <real>))
  (char->integer #\f))

(define-method* (return-type-code (str <string>))
  (char->integer #\s))

(define-method* (return-type-code (sym <symbol>))
  (char->integer #\s))

; (loop for x in '(1 1.0 "foo" foo) collect (return-type-code x))
; (105 102 115 115)

(define (make-type-array message)
  (let* ((mes (cdr message))
         (len (length mes))
         (pad (- 4 (mod len 4)))
         (vec (make-u8vector (+ len (if (= pad 1) (+ pad 4) pad)))))
    (u8vector-set! vec 0 (char->integer #\,))
    (do ((i 0 (+ i 1)))
        ((= i len) vec)
      (u8vector-set! vec (+ i 1)
                     (return-type-code (list-ref mes i))))))

; (make-type-array (list "/c_fill" 1 2.0 'z))
; #(44 105 102 115 0 0 0 0)

;;;;the first token in an osc message is always a string. the following
;;;;methods convert tokens to a string and then to a byte vector

(define-method* (get-first-obj (num <number>))
  (make-byte-vector (format #f "~s" num)))

(define-method* (get-first-obj (str <string>))
  (make-byte-vector str))

(define-method* (get-first-obj (sym <symbol>))
  (make-byte-vector (string-downcase (symbol->string sym))))

;;; formatting for standard OSC message. concatenates each separate
;;; byte vector for each token and returns array and array length as
;;; values

(define (format-osc message)
  (let ((arr (apply (function u8vector-append)
                    (get-first-obj (car message))
                    (make-type-array message)
                    (loop for m in (cdr message) 
                       collect (make-byte-vector m)))))
    (values arr (u8vector-length arr))))


;;;
;;; osc udp stream class and methods
;;;

;;; each implementation needs a make-osc-timetag function
;;; need a send-osc function
;;; also need osc-vector->osc-message parse-osc function and 
;;; u8vector->double
(define-class* <osc-stream> (<rt-stream>)
  ((remote-port :init-value #f :init-keyword :remote-port)
   (remote-host :init-value #f :init-keyword :remote-host)
   (local-port :init-value #f :init-keyword :local-port)
   ;; data list: (<thread> #'stopper )
   (receive-data :init-value (list #f #f) 
                 :accessor rt-stream-receive-data)
   (receive-mode :init-value :message :init-keyword :receive-mode
                 :accessor rt-stream-receive-mode)
   (latency :init-value 0.0 :init-keyword :latency)
   (buffer-size :init-value 512 :init-keyword :buffer-size)
   (socket :init-value #f))
  :name 'osc-stream
  :metaclass <io-class>)

(define-method* (open-io (obj <osc-stream>) dir . args)
  dir
  (let ((rh #f) (rp #f) (lp #f))
    (if (pair? args)
        (begin
          (when (> (length args) 0)
            (set! rh (list-ref args 0)))
          (when (> (length args) 1)
            (set! rp (list-ref args 1)))
          (when (> (length args) 2)
            (set! lp (list-ref args 2)))))
    (unless (io-open obj)
      (slot-set! obj 'socket
                 (make-udp-socket
                  (if rh rh (slot-ref obj 'remote-host))
                  (if rp rp (slot-ref obj 'remote-port))
                  (if lp lp (slot-ref obj 'local-port))))
      (slot-set! obj 'open #t))
    (set! *out* obj)))

(define-method* (close-io (obj <osc-stream>) . mode)
  mode
  (when (io-open obj)
    (udp-socket-close (slot-ref obj 'socket))
    ;(udp-socket-shutdown (slot-ref obj 'socket) 2)
    (slot-set! obj 'open #f))
  (set! *out* #f))

;;; send-msg
;;; (send-msg <list> <osc-stream>)
;;; (send-msg '("foo" 1 2 3 4 5) *osc*)


(define-method* (send-msg message (io <osc-stream>))
  (multiple-value-bind (mess len)
    (format-osc message)
  (send-osc mess io len)))

;;;send-bundle
;;; (send-bundle <time> <list> <osc-stream>)
;;; (send-bundle 1.5 '("foo" 1 2 3 4 'a) *osc*)
;;; can also nest messages
;;; (send-bundle 1.5 '(("foo" 1 2 3 4) ("baz" 1 2 3 4 5 'b)))


(define-method* (send-bundle offset message (io <osc-stream>))
  (let ((arr (make-byte-vector "#bundle"))
        (mess-len 0))
    (set! arr (u8vector-append arr (make-osc-timetag offset io)))
    ;;this should be smarter
    (if (list? (list-ref message 0))
        (begin
          (dolist (bundle-mess message)
            (multiple-value-bind (mess len)
              (format-osc bundle-mess)
              (set! arr
                    (u8vector-append arr
                                     (make-byte-vector len)
                                     mess))
              (set! mess-len (+ mess-len len))))
          (set! mess-len (+ mess-len 24))
          (send-osc arr io mess-len))
      (multiple-value-bind (mess len)
        (format-osc message)
        (set! arr
              (u8vector-append arr
                               (make-byte-vector len)
                               mess))
        (set! mess-len (+ len 8 8 4))
        (send-osc arr io mess-len)))))



(define-method* (set-receive-mode! (str <osc-stream>) mode)
  (unless (member mode '(:message :raw))
    (err "receive: ~s is not a osc receive mode." mode))
  (slot-set! str 'receive-mode mode))


(define-method* (receive (str <osc-stream>) . args)
  (let* ((n 0)
        (in #f)
        (hook (if (pair? args) (pop args) #f))
        (mode (if (pair? args) (pop args) #f))
        (rm (if (not mode) #t (eq? mode ':message)))
        (fn #f)
        (res #f))
    (if (io-open str)
        (set! in str))
    (if in
        (begin
          (set! n (udp-socket-recv (slot-ref in 'socket) (slot-ref str 'buffer-size)))
          (if n
              (begin
                (if hook
                    (begin
                      (set! fn (lambda (mm)
                                 (hook (osc-vector->osc-message mm))))
                      (if rm (funcall fn n)
                        (hook n))
                      (set! res #t))
                  (begin
                    (if rm
                        (set! res (osc-vector->osc-message n))
                      (set! res n))))))
          res)
      (err "osc stream ~s not open" str))))

(define-method* (init-receiver (str <osc-stream>) type)
  type
  (unless (io-open str)
    (open-io str :input)))

(define-method* (deinit-receiver (str <osc-stream>) type)
  type
  (let ((data (rt-stream-receive-data str)))
    (when (io-open str)
      (close-io str))
    (list-set! data 0 #f)
    (list-set! data 1 #f)))


(define-method* (stream-receiver hook (str <osc-stream>) type)
  ;; hook is 2arg lambda or nil, type is :threaded or :periodic
  (let* ((data (rt-stream-receive-data str)) ; (<thread> <stop> )
         (mode (rt-stream-receive-mode str))
         (stop #f)) 
    ;; can receive either message or raw buffer
    (unless (member mode '(:message :raw))
      (err "receive: ~s is not a osc receive mode." mode))
    ;; the receiving thread's do loop terminates as soon as the stop
    ;; flag is #t. to stop we call the cached "stopper" closure that
    ;; sets the var to #t.
    (cond ((not (procedure? hook))
           (err "Receive: hook is not a function: ~s" hook))
          ((first data)
           (err "Can't set input hook: another hook is running!"))
          (else
           ;; ready to go
           (let* ((in str)
                  (rm (eq? mode ':message))
                  (th #f) ; thread
                  (st #f) ; thread stopper
                  (fn #f) ; mapper
                  (ra (rt-stream-receive-rate str))
                  )
             (set! fn (lambda (mm)
                        ( hook (osc-vector->osc-message mm))))
             (case type
               ((:threaded )
                (set! th
                      (make-thread
                       (lambda ()
                         (do ((n #f))
                             (stop  
                              #f)
                           (set! n (udp-socket-recv (slot-ref in 'socket)
                                                    (slot-ref str 'buffer-size)))
                           (if n
                               (if rm
                                   (funcall fn n)
                                 ( hook n))
                             ;; only sleep if no message??
                             (thread-sleep! ra))))))
                (set! st (lambda () (set! stop #t))))
               ((:periodic )
                (set! th
                      (lambda () 
                        (let ((n 0))
                          (set! n (udp-socket-recv (slot-ref in 'socket)
                                                   (slot-ref str 'buffer-size)))
                          (if n
                              (if rm
                                  (funcall fn n)
                                ( hook n))))))
                (set! st (lambda ()
                           (remove-periodic-task! :receive))))
               )
             ;; cache the stuff
             (list-set! data 0 th)
             (list-set! data 1 st)
             th)))))