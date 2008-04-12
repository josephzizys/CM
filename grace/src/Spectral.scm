;;; **********************************************************************
;;; Copyright (C) 2007, 2008 Todd Ingalls, Rick Taube.
;;; This program is free software; you can redistribute it and/or modify
;;; it under the terms of the Lisp Lesser Gnu Public License. The text of
;;; this agreement is available at http://www.cliki.net/LLGPL            
;;; **********************************************************************

;;; uses: with-optkey, first, second, tb:bess-jn, shuffle! reverse!

(define-record spectrum time size freqs amps)

(define-record-printer (spectrum obj port)
  (fprintf port "#<spectrum ~S ~S>"
	   (spectrum-freqs obj)
	   (spectrum-amps obj)
	   ))

;(define (make-spectrum freqs . args)
;  (let ((amps (if (null? args) #f (list->vector (car args))))
;	(size (length freqs)))
;    (make-spektrum #f size (list->vector freqs)
;		   amps)))
;(define spectrum-size spektrum-size)
;(define spectrum-freqs spektrum-freqs)
;(define spectrum-amps spektrum-amps)
;(define spectrum-time spektrum-time)

(define (spectrum-copy spectrum)
  (make-spectrum (spectrum-time spectrum)
		 (spectrum-size spectrum)
		 (append (spectrum-freqs spectrum) (list))
		 (append (spectrum-amps spectrum) (list))))

(define (spectrum-pairs spectrum)
  (let* ((head (list #f))
	 (tail head)
	 (freqs (spectrum-freqs spectrum))
	 (ampls (spectrum-amps spectrum))
	 (size (spectrum-size spectrum)))
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

(define (spectrum->keys spectrum order thresh quant unique
			mink maxk)
  (if (eq? unique #t) (set! unique 1))
  (letrec ((head (list #f))
	   (tail head)
	   (freqs (spectrum-freqs spectrum))
	   (ampls (spectrum-amps spectrum))
	   (getkey 
	    (lambda (h)
	      (let ((k (if quant (quantize (key h) quant) (key h))))
		(cond ((and mink (< k mink))
		       (do () ((>= k mink) k) (set! k (+ k 12))))
		      ((and maxk (> k maxk))
		       (do () ((<= k maxk) k) (set! k (- k 12))))
		      (else k)))))
	   (add (lambda (k)
		  (cond ((eq? order -1)
			 (let ((z (list k)))
			   (set-cdr! z (cdr head))
			   (set-cdr! head z)))
			(else
			 (set-cdr! tail (list k))
			 (set! tail (cdr tail))))))
	   (addkey (lambda (h) (add (getkey h))))
	   (adduniquekey (lambda (h) 
			   (let ((k (getkey h)))
			     (unless (member k (cdr head)) (add k))))))
    (if (or (not thresh) (not ampls))
	(if unique
	    (for-each adduniquekey freqs)
	    (for-each addkey freqs))
	(if unique
	    (for-each (lambda (a b)
			(if (>= b thresh) (adduniquekey a)))
		      freqs ampls)
	    (for-each (lambda (a b)
			(if (>= b thresh) (addkey a)))
		      freqs ampls)))
    (let ((keys (cdr head)))
      (if (eq? order 0) (shuffle! keys) keys))))

(define (spectrum-keys spectrum . args)
  (with-optkeys (args (order 1) (thresh #f) (quant #f) (unique #f)
		      (min #f) (max #f) )
    (spectrum->keys spectrum order thresh quant unique
		    min max)))
      
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
	   (f #f)
	   (a #f))
	  ((> k nsides)
	   (set! spectrum (cdr head)))
	(set! f (+ carrier (* mfreq k)))
	(set! a (tb:bes-jn k index))
	(if (not (or (= a 0.0) (= f 0.0)))
	    (begin
	      (set-cdr! tail (list (list f a)))
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
	   (make-spectrum #f size freqs (cdr ampls)))
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

;         50
;(10 30 40 50)
;         44
;(10 30 40 50)
;             60
;(10 30 40 50)

(define (spectrum-add! spec freq amp)
  (do ((freqs (spectrum-freqs spec) (cdr freqs))
       (amps (spectrum-amps spec) (cdr amps))
       (lastf '() freqs)
       (lasta '() amps) )
      ;; search freqs for insertion point, ie point where car is equal
      ;; or greater then freq
      ((or (null? freqs) (>= (car freqs) freq ))
       (cond ((null? freqs)
	      ;; empty freqs or freq is higher than any in list
	      (if (null? lastf)
		  (begin
		    (spectrum-freqs-set! spec (list freq))
		    (spectrum-amps-set! spec (list amp))
		    (spectrum-size-set! spec 1))
		  (begin
		    (set-cdr! lastf (list freq))
		    (set-cdr! lasta (list amp))
		    (spectrum-size-set! spec (+ (spectrum-size spec)
						1)))))
	     ((= (car freqs) freq) 
	      ;; freq already present just update amp
	      (set-car! amps (+ (car amps) amp)))
	     ((null? lastf)
	      ;; freq is lower than any in list
	      (spectrum-freqs-set! spec (cons freq freqs))
	      (spectrum-amps-set! spec (cons amp amps))
	      (spectrum-size-set! spec (+ (spectrum-size spec) 1)) )
	     (else   ;; insert before car of freqs
	      (let ((f (list freq))
		    (a (list amp)))
		(set-cdr! f freqs)
		(set-cdr! lastf f)
		(set-cdr! a amps)
		(set-cdr! lasta a)
		(spectrum-size-set! spec
				    (+ (spectrum-size spec) 1)))))
       spec)))

; (define aaa (make-spectrum 0 1 (list 100) (list .1)))
; (print aaa)
; (spectrum-add! aaa 200 .2)
; (spectrum-add! aaa 10 .1)
; (spectrum-add! aaa 50 .5)
; (spectrum-add! aaa 300 .3)
; (spectrum-add! aaa 150 .15)
; (spectrum-add! aaa 1999 .19)

(define (rm-spectrum spec1 spec2 )
  (let ((getfreqs 
	 (lambda (s)
	   (cond ((spectrum? s) (spectrum-freqs s))
		 ((pair? s) s)
		 (else s))))
	(getamps
	 (lambda (s)	     
	   (cond ((spectrum? s) (spectrum-amps s))
		 ((pair? s) 0.0)
		 (else 0.0))))
	(sums-and-diffs 
	 (lambda (s f1 a1 f2 a2)
	   (if (not (= f1 f2) )
	       (begin (spectrum-add! s (+ f1 f2) 
				     0.0)
		      (spectrum-add! s (abs (- f1 f2))
				     0.0))))))
    (let ((freq1 (getfreqs spec1))
	  (freq2 (getfreqs spec2))
	  (amps1 (getamps spec1))
	  (amps2 (getamps spec2))
	  (spect (make-spectrum #f 0 (list) (list))))
      (if (pair? freq1)
	  (if (pair? freq2)
	      (do ((l2 freq2 (cdr l2)))
		  ((null? l2) #f)
		(do ((l1 freq1 (cdr l1)))
		    ((null? l1) #f)
		  (sums-and-diffs spect (car l1) 0.0
				  (car l2) 0.0)))
	      (do ((l1 freq1 (cdr l1)))
		  ((null? l1) #f)
		(sums-and-diffs spect (car l1) 0.0 freq2 0.0)))
	  (if (pair? freq2)
	      (do ((s2 freq2 (car s2)))
		  ((null? s2) #f)
		(sums-and-diffs spect freq1 0.0 (car s2) 0.0))
	      (sums-and-diffs spect freq1 0.0 freq2 0.0)))
      spect)))


      
;; interp key note every

(define (spectrum-rescale spec mode . args)
  (let ((scaling #f) 
	(modifier #f)
	(modified #f)
	(minimum #f)
	(maximum #f))
    (if (null? args)
	(error "Need a scaler, envelope or x y values")
	(if (null? (cdr args))
	    (set! args (if (or (pair? (car args))
			       (number? (car args)))
			   (car args)
			   (error "Not a number or pair"
				  (car args))))))
    (if (not (<= 1 mode 8))
	(error "Mode not 1-8" mode)
	(set! mode (- mode 1))) ; convert 1-8 to 0-7
    (if (bit-set? mode 2) ; is 4's bit on
	(set! modified (spectrum-amps spec))
	(set! modified (spectrum-freqs spec)))
    (if (bit-set? mode 1) ; is 2's bit on?
	(set! modifier (spectrum-amps spec))
	(set! modifier (spectrum-freqs spec)))
    (if (bit-set? mode 0)
	(set! scaling #t)
	(set! scaling #f))
    (cond ((number? args); value
	   (if scaling
	       (do ((tail modified (cdr tail)))
		   ((null? tail) #f)
		 (set-car! tail (* (car tail) args)))
	       (do ((tail modified (cdr tail)))
		   ((null? tail) #f)
		 (set-car! tail args))))
	  (else
	   (if (not (every? number? args))
	       ;; replace #f and #t with appropriate min max values
	       (let ((xmin #f) (xmax #f) (ymin #f) (ymax #f))
		 (if (bit-set? mode 1) ; env x is amp
		     (begin (set! xmax (spectrum-maxamp spec))
			    (set! xmin (spectrum-minamp spec)))
		     (begin (set! xmax (spectrum-maxfreq spec))
			    (set! xmin (spectrum-minfreq spec))))
		 (if (bit-set? mode 2) ; env y is amp
		     (begin (set! ymin (spectrum-minamp spec))
			    (set! ymax (spectrum-maxamp spec)))
		     (begin (set! ymin (spectrum-minfreq spec))
			    (set! ymax (spectrum-maxfreq spec))))
		 (set! args (append args (list))) ; side effect copy!
		 (do ((tail args (cddr tail)))
		     ((null? tail) #f)
		   (cond ((eq? (car tail) #f) 
			  (set-car! tail xmin))
			 ((eq? (car tail) #t) 
			  (set-car! tail xmax)))
		   (cond (scaling
			  (error "Non-numerical y can't be scaler"
				 (cadr tail)))
			 ((eq? (cadr tail) #f) 
			  (set-car! (cdr tail) ymin))
			 ((eq? (cadr tail) #t) 
			  (set-car! (cdr tail) ymax))))))
	   ;; now have valid envelope
	   (if scaling
	       (do ((tail modified (cdr tail)))
		   ((null? tail) #f)
		 (set-car! tail (* (car tail) 
				   (interp (car tail) args))))
	       (do ((tail modified (cdr tail)))
		   ((null? tail) #f)
		 (set-car! tail (interp (car tail) args))))))
    spec))
