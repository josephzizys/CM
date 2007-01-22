(in-package cm)

;;; **********************************************************************
;;; Copyright (C) 2005 Heinrich Taube, <taube (at) uiuc (dot) edu>
;;;
;;; This program is free software; you can redistribute it and/or
;;; modify it under the terms of the Lisp Lesser Gnu Public License.
;;; See http://www.cliki.net/LLGPL for the text of this agreement.
;;; **********************************************************************

;;; $Name$
;;; $Revision$
;;; $Date$

(define (the-string x)
  (cond ((string? x) x)
	((keyword? x) (string-downcase (keyword->string x)))
	((symbol? x) (string-downcase (symbol->string x)))
	(else
	 (string-downcase (format #f "~a" x)))))

(define gnuplot-special-settings
  (list 
   (list ':title 
	 (lambda (f v) (format f " ~s" (the-string v))))
   (list '(:origin :size)
	 (lambda (f v)
	   (format f " ~a,~a"  
		   (the-string (car v)) (the-string (cadr v)))))
   (list '(:xrange :yrange :zrange)
	 (lambda (f v) 
	   (format f " [~a:~a]" (the-string (car v)) (the-string (cadr v)))))))

(define gnuplot-non-settings
  '(:view :data))

(define (find-gnuplot-setting k )
  (do ((tail gnuplot-special-settings (cdr tail))
       (spec #f))
      ((or (null? tail) spec)
       spec)
    (if (or (and (pair? (caar tail))
		 (member k (caar tail)))
	    (eq? k (caar tail)))
	(set! spec (car tail)))))

(define (print-gnuplot-setting f k v . p)
  ;; print file or plot settings depending on p
  (if (or (not v) (null? v) (member k gnuplot-non-settings)) #f
      (let ((s (find-gnuplot-setting k)))
	(if (null? p) (format f "set"))
	(format f " ~a" (the-string k))
	(cond (s
	       ;; call special formatter
	       ( (cadr s) f v))
	      ((eq? v #t)
	       ;; simply print the setting
	       #f)
	      ((string? v)
	       (format f " ~a" (the-string v)))
	      ((pair? v)
	       (do ((tail v (cdr tail)))
		   ((null? tail) #f)
		 (format f " ~a" (the-string (car tail)))))
	      (else
	       (format f " ~a" (the-string v))))
	(if (null? p) (format f "~%"))
	#f)))

; (setq foo '(0 0 25 .9 75 .9 100 0) bar (loop repeat 6 collect (random 1.0)))
; (guess-data-format foo)
; (guess-data-format bar)
; (guess-data-format (list (new midi)))

(define (guess-data-format dat)
  (let ((a (first dat)))
    (cond ((number? a)
	   (do ((l dat (cdr l))
		(i 0 (+ i 1))
		(x most-negative-fixnum)
		(f #f))
	       ((or (null? l) f)
		(if (not f)
		    (if (even? i) ':xy)
		    f))
	     (if (even? i) 
		 (if (>= (car l) x)
		     (set! x (car l))
		     (set! f ':y)))))
	  ((is-a? a <object>)
	   (let ((xslot #f)
		 (yslot #f)
		 (xtest '(time beg start startime begin begin-time start-time 
			  onset off x))
		 (ytest '(keynum frequency freq pitch frq note y)))
	     (do ((l xtest (cdr l)))
		 ((or (null? l) xslot) #f)
	       (if (slot-exists? a (car l)) (set! xslot (car l))))
	     (do ((l ytest (cdr l)))
		 ((or (null? l) yslot) #f)
	       (if (slot-exists? a (car l)) (set! yslot (car l))))
	     (if xslot
		 (if yslot (list xslot yslot)
		     xslot)
		 yslot)))
	  (else #f))))

; (slot-data? (new midi) '(keynum amplitude))

(define (slot-data? x sl)
  ;; test object x for valid slots
  (cond ((null? sl) #t)
	((pair? sl) 
	 (and (slot-data? (car sl))
	      (slot-data? (cdr sl))))
	(else
	 (and (slot-exists? x sl)
	      (slot-bound? x sl)
	      (number? (slot-ref x sl))))))

(define (print-gnuplot-slot-data f x sl)
  (do ((tail sl (cdr tail)))
      ((null? tail) #f)
    (format f " ~s" (slot-ref x (car tail)))))

; (gnuplot t :title "asdf" :margin 1 :xrange '(-pi pi))
; (gnuplot t :title "asdf" :margin 1 )

(define (gnuplot file . args)
  (let ((plots (list))
	(infos (list :view #t :data #f)))
    ;; handle global file settings until first plot
    (do ((tail args (cddr tail)))
	((or (null? tail)
	     (not (keyword? (car tail))))
	 (if (null? tail)
	     (err "Missing plot data in: ~s" args)
	     (set! args tail)))
      (cond ((null? (cdr tail))
	     (err "Missing value for keyword ~s." (car tail)))
	    ((member (car tail) gnuplot-non-settings)
	     ;; update default infos with user's info
	     (set-car! (cdr (member (car tail) infos))
		       (cadr tail)))
	    (else
	     (print-gnuplot-setting file (car tail) (cadr tail)))))
    ;; args now series of plot specs: ({<plotdata> {key val}*}+ )
    (do ((plotd #f))
	((null? args)
	 (set! plots (reverse! plots)))
      ;; plot data can be list or seq
      (set! plotd (if (is-a? (car args) <seq>)
		      (subobjects (car args))
		      (car args)))
      (unless (and (pair? plotd)
                   (or (number? (car plotd))  ; env/data list
		       (and (pair? (car plotd)) ; point records
			    (number? (caar plotd)))
                       (is-a? (car plotd) <object>))) ; objects
        (err "Not a list or seq containing plot data: ~s" (car args)))
      ;; plotd is: (<plotdata> <format> (ranges..) settings...)
      (setq plotd (list plotd
			(list-prop infos ':data)
			(list :trange #f :xrange #f :yrange #f)
			))
      ;; gather keyargs for current plot until next plot. ranges and
      ;; data args are handled specially
      (do ((tail (cdr args) (cddr tail)))
	  ((or (null? tail)
	       (not (keyword? (car tail)))))
	(cond ((null? (cdr tail))
	       (err "Missing value for keyword ~s." (car tail)))
	      ((eq? (car tail) ':data)
	       ;; update plot-specific data format
	       (list-set! plotd 1 (cadr tail)))
	      (else
	       (let ((rng (member (car tail) (third plotd))))
		 (if (not rng)
		     (append! plotd (list (car tail) (cadr tail)))
		     (set-car! (cdr rng) (cadr tail))))))
	)
      ;; if data is point data (lists) ignore :data spec else try to
      ;; guess data format if not explicitly provided.
      (cond ((pair? (caar plotd))
	     (list-set! plotd 1 #t))
	    ((not (second plotd)) ; user did not indicate format
	     (list-set! plotd 1 (guess-data-format (car plotd)))))
      (push plotd plots)
      )
      ;; plots now list of (<plotdata> <format> (ranges..) settings...)
      ;; print plot command and args for each plot. 
      (format f "plot")
      ;; print settings for each plot...
      (do ((tail plots (cdr tail)))
	  ((null? tail) 
	   (format f "~%"))
	(let* ((plotd (car tail))
	       (dataf (list-ref plotd 1))
	       (range (list-ref plotd 2)))
	  ;; , separates individual plot clauses
	  (unless (eq? tail plots)
	    (format f ","))
	  ;; print plot ranges...
	  (do ((tail range (cddr tail))
	       (func (find-gnuplot-setting :xrange)))
	      ((null? tail) #f)
	      (if (second tail)
		  ( func f (second tail))))
	  (format f " '-'")
	  ;; map over and print plot-specific settings
	  (do ((tail (nth-tail plotd 3) (cddr tail)))
	      ((null? tail) #f)
	    (print-gnuplot-setting file (car tail) (cadr tail) #t))))
	;; print individual data blocks
	(do ((tail plots (cdr tail)))
	    ((null? tail) #f)
	  (let* ((plotd (first tail))
		 (pdata (first plotd))
		 (dataf (second plotd)))
	    (print-gnuplot-plot f pdata dataf)))
      )
	    


;;;
;;; eof
;;;








; plot hooke(), data: :y
