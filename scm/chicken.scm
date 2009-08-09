;;; **********************************************************************
;;; Copyright (C) 2008, 2009 Rick Taube.
;;; This program is free software; you can redistribute it and/or modify
;;; it under the terms of the Lisp Lesser Gnu Public License. The text of
;;; this agreement is available at http://www.cliki.net/LLGPL            
;;; **********************************************************************

;; loading this file ensures implementation features that are either
;; not provided or unevenly provided in scheme implementations. see
;; readme.txt for the list of features.

;; CLtL error style (error formatstr ...)
(define chicken-error error)
(define (error str . args)
  (chicken-error (apply format #f str args)))

(define-for-syntax (ash a b) (arithmetic-shift a b))
(define-for-syntax (logand . args ) (apply bitwise-and args))
(define-for-syntax (lognot . args) (apply bitwise-not args))
(define-for-syntax (logxor . args) (apply bitwise-xor args))
(define-for-syntax (logior . args) (apply bitwise-ior args))

(define (logtest a b)
  (not (zero? (logand a b))))

(define most-positive-fixnum #x3fffffff)

(define most-negative-fixnum (- #x3fffffff))

(define pi 3.141592653589793)

(define (list-set! lis pos val)
  (set-car! (list-tail lis pos) val)
  val)

;; hash tables

(define (make-equal-hash-table)
  (make-hash-table equal?))

(define (make-eq-hash-table)
  (make-hash-table eq?))

(define hash-set! hash-table-set!)

(define (hash-ref tab val)
  (hash-table-ref/default tab val #f))

(define (read-from-string str)
  (call-with-input-string str read))

(define (object->string x)
  (format #f "~S" x))

;; implementation specific expansion of the code that ensures error
;; protection under process callback and input hooks

(define (error-protected-process-code forms )
  (let ((errvar (gensym "errvar")))
    `(call-with-current-continuation
      (lambda (throw)  ; <- (throw x) exit
	(with-exception-handler
	 (lambda (,errvar)
	   (print-error-message ,errvar (current-error-port)
				">>> Error (run)")
	   (throw -2)  ; -2 = stop with error
	   )
	 (lambda () ,@ forms ))))
    ))

(define (error-protected-inhook $hook$ )
  (lambda ($op$ $ch$ $d1$ $d2$)
    (call-with-current-continuation
     (lambda (%cont)
       (with-exception-handler
	(lambda ($errarg$)
	  (print-error
	   (sprintf ">>> Error: ~A~%    Aborting MIDI inhook.~%"
		    ((condition-property-accessor 'exn 'message) 
		     $errarg$)
		    ))
	  (%cont -1)  ; -1 means error
	  )
	(lambda () 
	  ;; call users hook with the received message
	  ($hook$ $op$ $ch$ $d1$ $d2$)
	  0
	  ))))))

;; turn off warnings that ratio notation causes because we dont load
;; the ratio package. unfortunately this turns off ALL chicken
;; warnings but since i havent seen any other warnings in two years of
;; use this is probably an ok thing to do

(enable-warnings #f)


