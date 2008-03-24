;;; **********************************************************************
;;; Copyright (C) 2007, 2008 Todd Ingalls, Rick Taube.
;;; This program is free software; you can redistribute it and/or modify
;;; it under the terms of the Lisp Lesser Gnu Public License. The text of
;;; this agreement is available at http://www.cliki.net/LLGPL            
;;; **********************************************************************

;;;
;;; basic non-r5rs utilities that are not scheme implementation specific     
;;;

;; Chicken gives us first-fourth
;;(define first car)
;;(define second cadr)
;;(define third caddr)
;;(define fourth cadddr)
(define fifth (lambda (l) (car (cddddr l))))
(define sixth (lambda (l) (cadr (cddddr l))))
(define seventh (lambda (l) (caddr (cddddr l))))
(define eighth (lambda (l) (cadddr (cddddr l))))
(define ninth (lambda (l) (car (cddddr (cddddr l)))))
(define tenth (lambda (l) (cadr (cddddr (cddddr l)))))
(define nth list-ref)

(define (rest l) (cdr l))

;;(define (tail l) (if (null? (cdr l)) l (tail (cdr l))))

(define (last l) (if (null? (cdr l)) (car l) (last (cdr l))))

(define (butlast l)
  (cond ((null? (cdr l)) (list))
	((null? (cddr l)) (list (car l)))
	(else
	 (cons (car l) (butlast (cdr l))))))

(define (list* . args)
  (cond ((null? args)
	 (error ">>> Error: too few arguments to list*."))
        ((null? (cdr args))
	 (car args))
        (else
          (cons (car args)
                (apply list* (cdr args))))))

(define (list-set! lis pos val)
  (set-car! (list-tail lis pos) val)
  val)

(define (make-list n . obj)
  (if (< n 0) (error "Negative length to make-list" n)
      (letrec ((mk (lambda (a b)
		     (if (= a 0) (list)
			 (cons b (mk (- a 1) b))))))
	(mk n (if (null? obj) #f (car obj))))))

;;(define (find-if f l)
;;  (call/cc (lambda (r) 
;;	     (do ((tail l (cdr tail)))
;;		 ((null? tail) #f)
;;	       (if ( f (car tail)) (r (car tail)))))))

(define (list-prop lis prop . def)
  (if (null? lis)
      (if (null? def) #f (car def))
      (if (eq? (car lis) prop)
          (cadr lis)
          (apply list-prop (cddr lis) prop def))))

(define (list-prop-set! lis prop val)
  (if (eq? (car lis) prop)
      (set-car! (cdr lis) val)
      (if (null? (cddr lis))
          (set-cdr! (cdr lis) (list prop val))
          (list-prop-set! (cddr lis) prop val))))

(define (bitwise-test a b)
  ;; true if every bit in b is in a
  (do ((f #f))
      ((= b 0) f)
    (if (bit-set? b 0)
	(if (bit-set? a 0)
	    (set! f #t)
	    (begin (set! f #f)
		   (set! b 0))))
    (set! a (arithmetic-shift a -1))
    (set! b (arithmetic-shift b -1))))

