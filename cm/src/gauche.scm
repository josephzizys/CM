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

(use srfi-1)     ; list library
(use srfi-4)     ; u8vector
(use srfi-13)     ; extra string support
(use srfi-27)    ; random bits
(use file.util)  ; current-directory, home-directory
(use gauche.threads) ; for rt threads
(use gauche.net) ; needed for socket communication
(use gauche.fcntl) ;need to set socket to non-blocking
(use gauche.sequence)

;; Lisp environment normalization

(define (lisp-version )
  (string-append "Gauche " (gauche-version)))

(define quit exit)  

(define err errorf)

(define (read-macro-set! char fn) #f)

;; Directories, files and ports

(define (pwd)
  (current-directory))

(define (cd . args)
  (if (null? args)
    (current-directory (home-directory))
    (current-directory (car args)))
  (pwd))

(define (set-file-position fil pos set?)
  (if (= pos 0)
    (port-seek fil 0 SEEK_CUR) ; return the current position
    (if set?
      (port-seek fil pos SEEK_SET)
      (port-seek fil pos SEEK_CUR))))

(define (delete-file f)  (sys-unlink f))

(define file-byte read-byte)

(define (port-position prt)
  (port-tell prt))


;; System calls

(define (os-name )
  (string->symbol (string-downcase (car (sys-uname )))))

(define (env-var var)
  (sys-getenv var))

(define (set-env-var var val)
  (sys-putenv var val))

(define (shell . args)
  (sys-system (car args)))

(define (get-current-time)
  (let ((now (sys-localtime (sys-gettimeofday))))
    (vector (slot-ref now 'sec)
            (slot-ref now 'min)
            (slot-ref now 'hour)
            (slot-ref now 'mday)
            (slot-ref now 'mon)
            (+ 1900 (slot-ref now 'year)))))

;;; lists

(define (list-set! lis pos val)
  (set-car! (list-tail lis pos) val)
  val)

;;; Hashtables

(define (make-equal?-hash-table size)
  (make-hash-table 'equal?))

(define (hash-ref table key)
  (hash-table-get table key #f))

(define (hash-set! table key value)
  (hash-table-put! table key value))

(define (hash-remove! table key)
  (hash-table-delete! table key))

(define (hash-fold fn x table)
  (hash-table-fold table fn x))    
  
;;; Strings

(define (string-downcase str)
  (let* ((len (string-length str))
         (new (make-string len)))
    (do ((i 0 (+ i 1)))
        ((= i len) new)
      (string-set! new i (char-downcase (string-ref str i))))))

(define (string-read str . args)
  (if (null? args)
      (read-from-string str)
      (read-from-string str (car args))))

(define (string-trim-both str fn)
  (let ((len (string-length str))
        (beg #f)
        (end #f))
    (do ((i 0 (+ i 1)))
        ((not (< i len)) #f)
      (if ( fn (string-ref str i))
          (set! beg (+ i 1))
          (set! i len)))
    (do ((i (- len 1) (- i 1)))
        ((< i 0) #f)
      (if ( fn (string-ref str i))
          (set! end i)
          (set! i -1)))
    (if beg
        (if (= beg len)
            ""
            (if end (substring str beg end)
                (substring str beg len)))
        (if end (substring str 0 end)
            str))))


;;; Keywords. Gauche keywords are cltl keywords, Yay! 

(define (keyword->symbol kw)
  (string->symbol (keyword->string kw)))

(define (symbol->keyword sym)
  (make-keyword (symbol->string sym)))

(define (string->keyword s)
  (make-keyword s))

;; numbers

(define most-positive-fixnum (- (expt 2 29) 1))

(define most-negative-fixnum (- (expt 2 29)))

(define *random-state* default-random-source)

(define (random n . args)
  (if (exact? n)
    (random-integer n)
    (if (inexact? n)
      (if (= n 1.0)
          (random-real)
          (* (random-real) n))
      (errorf "random bounds not integer or real: ~s." n))))

(define (integer-decode-float num)
  (if (zero? num) 
    (values 0 0 1)
    (let ((base 2)
          (mant-size 23)
          (exp-size 8)
          (sign 1))
      (if (negative? num) 
        (begin (set! sign -1) (set! num (- num))))
      (let* ((bot (expt base mant-size))
             (top (* base bot)))
        (let loopy ((n num) (e 0))
             (cond
               ((>= n top)
                (loopy (quotient n base) (+ e 1)))
               ((< n bot)
                (loopy (* n base) (- e 1)))
               (else
                (values (inexact->exact (round n)) 
                        e sign))))))))

;                                   Chicken Gauche  Guile  Stklos
;(make class . args)                        y       y       y
;(initialize class inits)                   y       y       y
;(class-of obj)                             y       y       y
;(is-a? obj class)                          y       y       y
;(slot-ref obj slot)                        y       y       y
;(slot-set obj slot val)                    y       y       y
;(class-name class)                         y       y       y
;(class-slots class)                        y       y       x
;(class-direct-subclasses class)            y       y       y
;(class-direct-superclasses class)          *       y       *
;(slot-definition-name slot)                y       y       y
;(slot-definition-initargs slot)            n       n       n
;(slot-definition-initform slot)            n       n       n

; SCHEMES MUST PROVIDE THESE OOP METHODS, starred methods are to
; avoid overriding an existing implementation and/or normalize syntax
; issues between schemes
;
;(define-class* ...)
;(define-method* ...)
;(define-generic* ...)
;(find-class* name)                
;(define-object-printer* object port)
;(class-subclasses class) 
;(slot-getter-form obj slot)
;(slot-setter-form obj slot val)

(define-macro (define-generic* . args)
  `(define-generic ,(car args)))

;;; Gauche methods are like Guile methods, inclusing next-

(define-macro (define-method* formals . body)
  `(define-method ,(car formals) ,(cdr formals) ,@body))

;;; define-class* expansion for Gauche.  Gauche expands define-class
;;; into a really hairy expr.  rather than try to deal with that, the
;;; current macro expansion simply re-sets the class name after the
;;; class has been defined, ie (define-class* <foo> ... :name 'foo)
;;; becomes: (begin (define-class <foo> ...) (slot-set! <foo> 'name
;;; 'foo)) Luckily, the superclass list for Gauche's define-class
;;; expects variables, not names.

(define *named-classes* (make-hash-table 'eq?))

(define-macro (define-class* class supers slots . options)
  (let ((cname #f)
        (metac #f)
        (csets (list)))
    (do ((tail options (cddr tail)))
        ((null? tail) #f)
      (case (car tail)
        ((:name) (set! cname (cadr tail)))
        ((:metaclass) (set! metac (cadr tail)))
        ((:file-types )  ; cm metaclass slot
         (set! csets (cons* `(slot-set! ,class 'handles
                                        ,(cadr tail)) csets)))
        ((:output-hook) ; cm metaclass slot
         (set! csets (cons* `(slot-set! ,class 'output-hook
                                        ,(cadr tail)) csets)))
        ((:definer) ; cm metaclass slot
         (set! csets (cons* `(slot-set! ,class 'definer
                                        ,(cadr tail)) csets)))
        ((:versions) ; cm metaclass slot
         (set! csets (cons* `(slot-set! ,class 'versions
                                        ,(cadr tail)) csets)))
        ))
    `(begin
      (define-class ,class ,supers ,slots
                    ,@ (if metac (list :metaclass metac) (list)))
      (slot-set! ,class 'name ,cname)
      ;; add named class to the table
      (hash-table-put! *named-classes* ,cname ,class)
      ;; set slots from metaclass
      ,@csets)))
      
(define (find-class* name . args)
  (hash-table-get *named-classes* name #f))

;; default method for instances.
;(define-method write-object ((obj <object>) port)
;  (format port "~s" obj))

(define-macro (define-object-printer* args . body)
  `(define-method write-object , args ,@ body))

(define (class-subclasses cls)
  (let ((subs (class-direct-subclasses cls)))
    (do ((tail subs (cdr tail)))
        ((null? tail) subs)
      (set! subs (append subs (class-subclasses (car tail)))))))

;;; implement clos slot mop accessors

(define (slot-definition-initargs slot)
  (do ((opts (slot-definition-options slot) (cddr opts))
       (args (list)))
      ((null? opts)
       (reverse! args))
    (if (eq? (car opts) ':init-keyword)
      (set! args (cons (cadr opts) args)))))

(define class-direct-superclasses class-direct-supers)

(define (slot-definition-initform slot)
  (list-prop (slot-definition-options slot) ':init-value))

;;; CM functions for expanding slot access in write-event methods.

(define (slot-getter-form obj slot)
  `(slot-ref ,obj ',slot))

(define (slot-setter-form obj slot val)
  `(slot-set! ,obj ',slot ,val))

; (define-class* <foo> () ((a :init-value 1)) :name 'foo)
; (find-class* 'foo)
; (make <foo>)
; (class-name <foo>)
;; test if supers list holds names or variables:
;      (define-class <bar> (freddy) ((b :init-value 2)))
; (define-class <bar> (<foo>) ((b :init-value 2)))
; (describe <bar>)
; (describe (make <bar>))

; (define-class* <foo> () ((a :init-value 1 :init-keyword :a :accessor foo-a)) :name 'foo)
; (define-class* <bar> (<foo>) ((b :init-value 2 :init-keyword :b :accessor bar-b) (c :init-value 3 :accessor bar-c :init-keyword :c :init-keyword :cc)) :name 'bar)
; (find-class* 'foo)
; (find-class* 'bar)
; (class-direct-subclasses (find-class* 'foo))
; (class-slots <bar>)
; (define sd (find (lambda (x) (eq? 'c (slot-definition-name x) )) (class-slots <bar>)))
; (apropos 'slot-definition)
; (slot-definition-initargs sd)
; (slot-definition-initform sd)


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
