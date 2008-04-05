;;; **********************************************************************
;;; Copyright (C) 2007, 2008 Todd Ingalls, Rick Taube.
;;; This program is free software; you can redistribute it and/or modify
;;; it under the terms of the Lisp Lesser Gnu Public License. The text of
;;; this agreement is available at http://www.cliki.net/LLGPL            
;;; **********************************************************************

;;; uses: with-optkey, first, second, tb:bess-jn, shuffle! reverse!

(define-record spektrum time size freqs amps)

(define-record-printer (spektrum obj port)
  (fprintf port "#<spectrum ~S>" (spektrum-freqs obj)))

(define (make-spectrum freqs . args)
  (let ((amps (if (null? args) #f (list->vector (car args))))
	(size (length freqs)))
    (make-spektrum #f size (list->vector freqs)
		   amps)))

(define spectrum-size spektrum-size)

(define spectrum-freqs spektrum-freqs)

(define spectrum-amps spektrum-amps)

(define spectrum-time spektrum-time)

(define (spectrum-pairs spectrum)
  (let* ((head (list #f))
	 (tail head)
	 (freqs (spektrum-freqs spectrum))
	 (ampls (spektrum-amps spectrum))
	 (size (spektrum-size spectrum)))
    (do ((i 0 (+ i 1)))
	((= i size) (cdr head))
      (set-cdr! tail (list (list-ref freqs i) 
			   (if ampls (list-ref ampls i) 0.0)))
      (set! tail (cddr tail)))))

(define (spectrum-minfreq spectrum)
  (car (spectrum-freqs spectrum)))

(define (spectrum-maxfreq spectrum)
  (list-ref (spectrum-freqs spectrum)
	    (- (spectrum-size spectrum) 1)))

(define (spectrum-minamp spectrum)
  (let ((amp #f)
	(amps (spectrum-amps spectrum)))
    (if (not amps) 0.0
	(begin (for-each (lambda (a)
			   (if (or (not amp) (< a amp)) (set! amp a)))
			 amps)
	       amp))))

(define (spectrum-maxamp spectrum)
  (let ((amp 0.0)
	(amps (spectrum-amps spectrum)))
    (if (not amps) amp
	(begin (for-each (lambda (a) (if (> a amp) (set! amp a)))
			 amps)
	       amp))))

(define (spectrum->keys spectrum order thresh quant unique)
  (if (eq? unique #t) (set! unique 1))
  (letrec ((head (list #f))
	   (tail head)
	   (freqs (spectrum-freqs spectrum))
	   (ampls (spectrum-amps spectrum))
	   (add (lambda (x)
		  (cond ((eq? order -1)
			 (let ((z (list x)))
			   (set-cdr! z (cdr head))
			   (set-cdr! head z)))
			(else
			 (set-cdr! tail (list x))
			 (set! tail (cdr tail))))))
	   (in? (lambda (x) (member x (cdr head))))
	   (addkey (lambda (h) (add (key h))))
	   (addquantkey (lambda (h) (add (quantize (key h) quant))))
	   (adduniquekey (lambda (h) 
			   (let ((k (key h)))
			     (unless (in? k) (add k)))))
	   (adduniquequantkey (lambda (h) 
				(let ((k (quantize (key h) quant)))
				  (unless (in? k) (add k))))))
    (if (or (not thresh) (not ampls))
	(if quant
	    (if unique 
		(for-each adduniquequantkey freqs)
		(for-each addquantkey freqs))
	    (if unique
		(for-each adduniquekey freqs)
		(for-each addkey freqs)))
	(if quant
	    (if unique
		(for-each (lambda (a b) 
			    (if (>= b thresh) (adduniquequantkey a)))
			  freqs ampls)
		(for-each (lambda (a b)
			    (if (>= b thresh) (addquantkey a)))
			  freqs ampls))
	    (if unique
		(for-each (lambda (a b)
			    (if (>= b thresh) (adduniquekey a)))
			  freqs ampls)
		(for-each (lambda (a b)
			    (if (>= b thresh) (addkey a)))
			  freqs ampls))))
    (let ((keys (cdr head)))
      (if (eq? order 0) (shuffle! keys) keys))))

(define (spectrum-keys spectrum . args)
  (with-optkeys (args (order 1) (thresh #f) (quant #f) (unique #f))
    (spectrum->keys spectrum order thresh quant unique)))
      
; (define aaa (fm-spectrum1 100 1.4 3))
; (spectrum-time aaa)
; (spectrum-size aaa)
; (spectrum-freqs aaa)
; (spectrum-amps aaa)
; (spectrum-pairs aaa)
; (spectrum-maxfreq aaa)
; (spectrum-minfreq aaa)
; (spectrum-maxamp aaa)
; (spectrum-minamp aaa)
; (spectrum-keys aaa)

; (spectrum->keys aaa 1 .5 #f #f)
; (spectrum->keys aaa 1 #f #f #f)
; (spectrum->keys aaa -1 #f #f #f)
; (spectrum-keys aaa 1 .5)
; (spectrum-keys aaa -1 .5)
; (spectrum-keys aaa 0 .5)
; (spectrum-keys aaa 0 int: #t unique: #t)

;;;--------------------------------------------------------------------

(define (fm-spectrum carrier mratio index)
  (let ((mfreq (* carrier mratio))
        (nsides (+ (inexact->exact (round index)) 1) )
        (spectrum '()))
    ;; spectrum is a list of sidebands, each sideband is (freq amp)
    (let* ((head (list #f))
	   (tail head))
      (do ((k (- nsides) (+ k 1))
	   (a #f))
	  ((> k nsides)
	   (set! spectrum (cdr head)))
	(set! a (tb:bes-jn k index))
	(if (not (= a 0.0))
	    (begin
	      (set-cdr! tail (list (list (+ carrier (* mfreq k)) a)))
	      (set! tail (cdr tail))))))
    ;; fold negative freqs into positive side, combine sideband amps
    (do ((neg #f)
	 (pos #f))
	((not (negative? (caar spectrum))) #f)
      (set! neg (car spectrum)) ; pop
      (set! spectrum (cdr spectrum))
      (set! pos (abs (first neg)))
      ;; wrap around to positive freq, invert phase
      (set-car! neg pos)
      (set-car! (cdr neg) (- (second neg)))
      ;; combine with existing sideband or insert at freq position.
      (let ((side (assoc (first neg) spectrum)))
	(if side
            (set-car! (cdr side)
                      (+ (cadr side) 
                         (second neg)))
            (let ((p (do ((i (- (length spectrum) 1) (- i 1))
                          (f #f)
                          (x #f))
                         ((or f (< i 0)) f)
                       (set! x (car (list-ref spectrum i)))
                       (if (< x pos) (set! f i)))))
              (if (not p)
		  (set! spectrum (cons neg spectrum)  )
		  (let ((tail (list-tail spectrum p)))
		    (set! neg (list neg))
		    (set-cdr! neg (cdr tail))
		    (set-cdr! tail neg)))))))
    ;; create the lists of freqs and amps, reusing cons cells in
    ;; spectrum, ie ((a 1) (b 2) (c 3)) => (a b c) (1 2 3). outer list
    ;; reused as freqs list, cdrs of inner lists nconced together for
    ;; amps list.
    (let* ((freqs spectrum)
	   (ampls (car spectrum))) ; (a 1)
      (do ((tail spectrum (cdr tail))
	   (size 0 (+ size 1))
	   (ampl ampls))
	  ((null? tail)
	   (make-spektrum #f size freqs (cdr ampls)))
	(let* ((entry (car tail))
	       (f (car entry)))
	  ;; no negative amps
	  (set-car! (cdr entry) (abs (cadr entry)))
	  (set-cdr! ampl (cdr entry))
	  (set! ampl (cdr ampl))
	  (set! (car tail) f))))))

; (fm-spectrum1 100 1.4 3)
; (fm-spectrum 100 1.4 3 )
; (fm-spectrum 100 1.4 3 :amplitudes #f)
; (fm-spectrum 100 1.4 3 :spectrum :hertz)
; (fm-spectrum 100 1.4 3 :spectrum :hertz :amplitudes #t)

