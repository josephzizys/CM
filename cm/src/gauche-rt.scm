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

;;;
;;; porting code for Gauche Scheme:
;;; http://www.shiro.dreamhost.com/scheme/gauche/index.html
;;;


(use gauche.threads) ; for rt threads
(use gauche.net) ; needed for socket communication
(use gauche.fcntl) ;need to set socket to non-blocking
(use gauche.sequence)



;;gauche specific stuff for sending osc messages over udp sockets.

(define (u8vector->byte-string vec)
  (let* ((vec-len (u8vector-length vec))
         (byte-string (make-byte-string vec-len)))
    (do ((i 0 (+ i 1)))
        ((= i vec-len))
      (string-byte-set! byte-string i (u8vector-ref vec i)))
    byte-string))

;;;
;;; threads
;;;
(define thread-alive?
  (let ((unique (list 'unique)))
    (lambda (thread)
      (eq? (thread-join! thread 0 unique) unique))))

(define (thread-current-time )
  (time->seconds (current-time)))
;;;
;;; socket/udp support
;;;

;; because i want to use sendto on a unconnected socket
;; i want to encapsulate the remote host and port
;; information along with the socket.
;; udp-socket class does this .
;;
;; functions/methods needed
;; (make-udp-socket host port local-port) x
;; (udp-socket-close sock) x
;; (udp-socket-shutdown sock &optional) x
;; (udp-socket-recv sock bytes &optional flags) x
;; (udp-socket-send sock mess len) x
;; (send-osc mess osc-stream len) x
;; (make-osc-timetag offset out) x
;; (u8vector->double vec) 
;; (osc-bundle? vec) x
;; (osc-parse-timestamp vec) 
;; (osc-parse-contents vec) x
;; (osc-parse-message vec) x
;; (osc-parse-bundle vec) x
;; (osc-vector->osc-message vec) x
;;

(define-class* <udp-socket> ()
  ((socket :init-value #f)
   (remote-port :init-value #f :init-keyword :remote-port)
   (remote-host :init-value #f :init-keyword :remote-host)
   (local-port :init-value #f :init-keyword :local-port))
  :name 'udp-socket)

 (define (make-udp-socket host port local-port)
   (let ((usock (make <udp-socket> :remote-host host :remote-port port :local-port local-port)))
     (slot-set! usock 'socket (make-socket PF_INET SOCK_DGRAM))
     (sys-fcntl (socket-fd (slot-ref usock 'socket)) F_SETFL O_NONBLOCK)
     (socket-bind (slot-ref usock 'socket) (make <sockaddr-in> :host "127.0.0.1" :port local-port))
     usock))



(define (udp-socket-close sock)
  (socket-close (slot-ref sock 'socket)))
                          

;; is this even needed?? since
;; socket is not connection orientated
(define (udp-socket-shutdown sock . args)
  (with-args (args &optional how)
    (unless how
      (set! how 2))
    (socket-shutdown (slot-ref sock 'socket) how)))

;; this does a recvfrom on socket, however must
;; handle EAGAIN error since this indicates
;; the socket is non-blocking and no data
;; is waiting. in this case, return #f

(define (udp-socket-recv sock bytes . args)
   (with-args (args &optional flags)
     (unless flags
       (set! flags 0))
     (guard (exc ((<system-error> exc) (if (= 35 (slot-ref exc 'errno)) #f (err exc))))
            (string->u8vector (socket-recvfrom (slot-ref sock 'socket) bytes flags)))))

(define (udp-socket-send sock mess bytes)
  bytes
  (socket-sendto (slot-ref sock 'socket) (u8vector->byte-string mess)
                 (make <sockaddr-in> :host (slot-ref sock 'remote-host)
                       :port (slot-ref sock 'remote-port))))

;;test
;; (define *send-socket* (make-udp-socket "127.0.0.1" 9000 22011))
;; (define *recv-socket* (make-udp-socket "127.0.0.1" 22011 9000))
;; (let ((mess (make-u8vector 64 2)))
;;   (udp-socket-send *send-socket* mess 64))

;; (udp-socket-recv *recv-socket* 128)
;; (udp-socket-close *send-socket*)
;; (udp-socket-close *recv-socket*)


(define (send-osc mess osc-stream len)
   len
   (udp-socket-send (slot-ref osc-stream 'socket) mess len))


(define (make-osc-timetag offset out)
  (let* ((now (current-time))
         (offset-time (seconds->time offset))
         (target-time (seconds->time (+ (time->seconds now) (time->seconds offset-time) (slot-ref out 'latency))))
         (vec #f))
    (set! vec (make-byte-vector (+ 2208988800 (slot-ref target-time 'second))))
    (u8vector-append vec (make-byte-vector (inexact->exact (* (modf (time->seconds target-time)) #xffffffff))))))


(define (u8vector->double vec)
  (let ((dv (uvector-alias <f64vector> vec)))
    (f64vector-ref dv 0)))

(define *bundle-header-bytes* #u8(35 98 117 110 100 108 101 0))

(define (osc-bundle? vec)
  (let ((res #t))
    (if (u8vector? vec)
        (dotimes (i 8)
          (when (not (= (u8vector-ref vec i) (u8vector-ref *bundle-header-bytes* i)))
            (set! res #f)))
      (set! res #f))
    res))
          
(define (osc-parse-timestamp vec)
  (let ((ts #f))
    (setf ts (u8vector->uint (u8vector-subseq arr 0 4)))
    (setf ts (+ ts
             (exact->inexact
              (/ (u8vector->uint (u8vector-subseq arr 4 8))
                 4294967295))))))

(find-index (lambda (x) (= x 0)) *bundle-header-bytes*)

(define (osc-parse-contents arr)
  (let ((lst (list))
	(mess #f)
	(pos #f)
	(sym-vector #f)
	(sym #f)
	(sym-len 0)
	(first-token-len #f)
	(type-list #f)
	(type-list-len #f))
    (set! first-token-len (find-index (lambda (x) (= x 0)) arr))
    (if first-token-len
	(begin
	  (set! lst (append! lst (list (string->symbol
                                        (string-upcase (u8vector->string (u8vector-subseq arr 0 first-token-len)))))))
	  (set! mess (u8vector-subseq arr (find-index (lambda (x) (= x 44))  arr)))
	  (set! type-list (loop for i across (subseq mess 0 (position 0 mess))
				collect (code-char i)))
	  (set! type-list-len (length type-list))
	  (set! mess (u8vector-subseq mess (+ type-list-len (- 4 (mod type-list-len 4)))))
	  (set! pos 0)
	  (dolist (j type-list)
            (cond ((eq? j #\i)
                   (set! lst (append! lst (list (u8vector->int (u8vector-subseq mess pos (+ pos 4))))))
                   (set! pos (+ pos 4)))
                  ((eq? j #\f)
                   (set! lst (append! lst (list (u8vector->float (u8vector-subseq mess pos (+ pos 4))))))
                   (set! pos (+ pos 4)))
                  ((eq? j #\d)
                   (set! lst (append! lst (list (u8vector->double (u8vector-subseq mess pos (+ pos 8))))))
                   (set! pos (+ pos 8)))
                  ((eq? j #\s)
                   (set! sym-vector (u8vector-subseq mess pos))
                   (set! sym (u8vector->string sym-vector))
                   (set! lst (append! lst (list (string-trim-right sym #\newline) #\/)))
                   (set! sym-len (string-length sym))
                   (if (= 0 (mod sym-len 4))
                       (set! pos (+ pos sym-len))
                     (set! pos (+ (+ sym-len (- 4 (mod sym-len 4))) pos)))))))
      (set! lst (append! lst (list (string->symbol (u8vector->string arr))))))
    lst))

(define (osc-parse-message vec)
  (osc-parse-contents vec))

(define (osc-parse-bundle arr)
  (let ((msg-len #f)
        (pos 0)
        (arr-len (u8vector-length arr))
        (bundle (list)))
    (do ()
        ((>= pos arr-len))
      (set! msg-len (u8vector->int (u8vector-subseq arr pos 4)))
      (set! pos (+ pos 4))
      (setf bundle (append! bundle (osc-parse-contents (u8vector-subseq arr pos (+ pos msg-len)))))
      (set! pos (+ pos msg-len)))
    bundle))

(define (osc-vector->osc-message arr)
  (let ((timestamp #f)
	(msg #f))
    (if (osc-bundle? arr)
	(begin 
	  (set! timestamp (osc-parse-timestamp (u8vector-subseq arr 8 16)))
	  (set! msg (osc-parse-bundle (u8vector-subseq arr 16))))
      (set! msg (osc-parse-contents arr)))
    (list msg timestamp)))


(define-macro (with-mutex-grabbed args . body)
  (let ((mutex (car args)))
    `(with-locking-mutex ,mutex (lambda () ,@body))))


(define-macro (without-interrupts . body)
  `(begin
     ,@body))




