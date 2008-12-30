;;; **********************************************************************
;;; Copyright (C) 2008, Rick Taube.
;;; This program is free software; you can redistribute it and/or modify
;;; it under the terms of the Lisp Lesser Gnu Public License. The text of
;;; this agreement is available at http://www.cliki.net/LLGPL            
;;; **********************************************************************

;; loading this file ensures implementation features that are either
;; not provided or unevenly provided in scheme implementations. see
;; readme.txt for the list of features.

(define (interaction-environment ) (global-environment))

(define-macro (define-record . args) (values)) ; records in s7Foreign

(define-macro (define-for-syntax . args) ; needed for chicken...
  `(define ,@ args))

(define-macro (unless arg . body) 
  `(if (not ,arg) (begin ,@ body)))

(define-macro (when arg . body) 
  `(if ,arg (begin ,@ body)))

;; keywords

(define (string->keyword s)
  (make-keyword s))

(define (keyword->string k)
  (symbol->string (keyword->symbol k)))

(define (fixnum? x)
  (integer? x))

(define (logtest a b)
  (not (zero? (logand a b))))

;; hash tables

(define (make-equal-hash-table)
  (make-hash-table))

(define (make-eq-hash-table)
  (make-hash-table))

(define hash-set! hash-table-set!)

(define hash-ref hash-table-ref)

;; strings

(define (read-from-string str)
  (call-with-input-string str read))

;; adapted for lists as well as vectors from
;; http://www.math.grin.edu/~stone/events/scheme-workshop/quicksort.html

(define (sort! seq . opt)
  (let ((precedes? (if (null? opt) < (car opt)))
	(getlen #f)
	(getter #f)
	(setter #f))
    (cond ((list? seq)
	   (set! getlen length)
	   (set! getter list-ref)
	   (set! setter (lambda (l i x) 
			  (set-car! (list-tail l i) x))))
	  ((vector? seq)
	   (set! getlen vector-length)
	   (set! getter vector-ref)
	   (set! setter vector-set!))
	  (else
	   (error "not a list or vector" seq)))
    (define (swapper seq a b)
      (let ((x (getter seq a)))
	(setter seq a (getter seq b))
	(setter seq b x)))
    (define (partition! start stop pivot)
      (define (rightwards current)
        (if (and (< current stop)
                 (precedes? (getter seq current)
                            pivot))
            (rightwards (+ current 1))
            current))
      (define (leftwards current)
        (if (or (< current start)
                (precedes? (getter seq current)
                           pivot))
            current
            (leftwards (- current 1))))
      ;; body of partition!
      (let loop ((left-pointer (rightwards start))
                 (right-pointer (leftwards (- stop 1))))
        (if (< left-pointer right-pointer)
            (begin
              (swapper seq left-pointer right-pointer)
              (loop (rightwards (+ left-pointer 1))
                    (leftwards (- right-pointer 1))))
            left-pointer)))
    ; body of quicksort!
    (let qs ((start 0)
             (stop (- (getlen seq) 1)))
      (if (< start stop)
          (let* ((pivot (getter seq stop))
                 (break (partition! start stop pivot)))
            (swapper seq break stop)
            (if (<= (- break start)
                    (- stop break))
                (begin
                  (qs start (- break 1))
                  (qs (+ break 1) stop))
                (begin
                  (qs (+ break 1) stop)
                  (qs start (- break 1)))))))
    seq))

(define (sort seq . opt)
  (cond ((list? seq)
	 (set! seq (append seq (list))))
	((vector? seq)
	 (let* ((l (vector-length seq))
		(v (make-vector l)))
	   (do ((i 0 (+ i 1)))
	       ((= i l) (set! seq v))
	     (vector-set! v i (vector-ref seq i)))))
	(else
	 (error "not a vector or list" seq)))
  (sort! seq (if (null? opt) < (car opt))))

; (sort! (list 8 7 9 5 6 2 3 1 4) <)
; (sort! (list 8 7 9 5 6 2 3 1 4) >)
; (sort! (vector 8 7 9 5 6 2 3 1 4) <)
; (sort! (vector 8 7 9 5 6 2 3 1 4) >)

(define (error-protected-process-code  forms )
  (let ((catcharg (gensym "caught")))
    `(catch #t
	    (lambda () ,@ forms )
	    (lambda , catcharg
	      ;; this error handler gets called if anything is thrown,
	      ;; including our normal -1 to stop the process
	      (cond ((equal? (car , catcharg) -1)
		     -1)
		    (else
		     ;; s7 errors look like
		     ;; (<condition_sym> (<format_str> . <format_args>))
		     (if (and (= (length ,catcharg) 2)
			      (symbol? (car ,catcharg))
			      (pair? (cadr ,catcharg))
			      (string? (car (cadr ,catcharg)))
			      )
			 (print-error
			  (apply format #f (cadr ,catcharg))))
		     -2)
		    )))))

(define throw error)


  