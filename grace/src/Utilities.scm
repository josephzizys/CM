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

(define (last l) (if (null? (cdr l)) (car l) (last (cdr l))))

(define (butlast l)
  (cond ((null? (cdr l)) (list))
	((null? (cddr l)) (list (car l)))
	(else
	 (cons (car l) (butlast (cdr l))))))

(define (tail l) (if (null? (cdr l)) l (tail (cdr l))))

(define (unique l)
  (if (null? l) (list)
      (let* ((head (list #f))
	     (tail head))
	(do ((cdrs l (cdr cdrs)))
	    ((null? cdrs) (cdr head))
	  (if (not ( member (car cdrs) (cdr head)))
	      (begin (set-cdr! tail (list (car cdrs)))
		     (set! tail (cdr tail))))))))

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

(define (reverse! l)
  (let ((s (length l)))
    (do ((i 0 (+ i 1))
	 (j (- s 1) (- j 1))
	 (t l (cdr t)))
	((not (< i j)) l)
      (let ((x (car t))
	    (z (list-tail t (- j i ))))
	;;(print (list (car t) (car z)))
	(set-car! t (car z))
	(set-car! z x)))))

(define (make-list n . obj)
  (if (< n 0)
      (error "Negative length to make-list" n))
      (letrec ((l1 (lambda (a b)
		     (if (= a 0) (list)
			 (cons b (l1 (- a 1) b)))))
	       (l2 (lambda (a b)
		     ;; b is (<func> . args)
		     (if (= a 0) (list)
			 (cons ( apply (car b) (cdr b) )
			       (l2 (- a 1) b))))))
	(if (null? obj)
	    (l1 n #f)
	    (if (procedure? (car obj))
		(l2 n obj)
		(l1 n (car obj))))))

(define (list-index p l)
  (do ((tail l (cdr tail))
       (i 0  (+ i 1))
       (f #f))
      ((or f (null? tail ))
       f)
    (if ( p (car tail)) (set! f i))))

(define (list-find p l)
  (do ((tail l (cdr tail))
       (x #f)
       (f #f))
      ((or f (null? tail ))
       f)
    (if ( p (car tail)) (set! f (car tail)))))

(define (every? f l)
  (do ((tail l (cdr tail))
       (flag #t))
      ((or (not flag) (null? tail))
       flag)
    (if (f (car tail)) #f (set! flag #f))))


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

