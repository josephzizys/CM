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

(define (string! x)
  (cond ((string? x) x)
	((keyword? x) (string-downcase (keyword->string x)))
	((symbol? x) (string-downcase (symbol->string x)))
	(else
	 (string-downcase (format #f "~a" x)))))

(define gnuplot-special-settings
  (list 
   (list ':title 
	 (lambda (f v) (format f " ~s" (string! v))))
   (list '(:origin :size)
	 (lambda (f v)
	   (format f " ~a,~a"  
		   (string! (car v)) (string! (cadr v)))))
   (list '(:xrange :yrange :zrange)
	 (lambda (f v) 
	   (format f " [~a:~a]" (string! (car v)) (string! (cadr v)))))))

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
	(format f " ~a" (string! k))
	(cond (s
	       ;; call special formatter
	       ( (cadr s) f v))
	      ((eq? v #t)
	       ;; simply print the setting
	       #f)
	      ((string? v)
	       (format f " ~a" (string! v)))
	      ((pair? v)
	       (do ((tail v (cdr tail)))
		   ((null? tail) #f)
		 (format f " ~a" (string! (car tail)))))
	      (else
	       (format f " ~a" (string! v))))
	(if (null? p) (format f "~%"))
	#f)))

; (setq foo '(0 0 25 .9 75 .9 100 0) bar (loop repeat 6 collect (random 1.0)))
; (guess-data-format foo)
; (guess-data-format bar)
; (guess-data-format (list (new midi)))

(define (guess-data-format dat)
  (let ((a (first dat)))
    (cond ((number? a)
	   (do ((l list (cdr l))
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

; (gnuplot t :title "asdf" :margin 1 :xrange '(-pi pi))
; (gnuplot t :title "asdf" :margin 1 )

(define (gnuplot file . args)
  (let ((plots (list))
	(infos (list :view #t :data #f)))
    ;; handle file settings first
    (do ((tail args (cddr tail)))
	((or (null? tail)
	     (not (keyword? (car tail))))
	 (set! args tail))
      (cond ((null? (cdr tail))
	     (err "Missing value for keyword ~s." (car tail)))
	    ((member (car tail) gnuplot-non-settings)
	     ;; update default infos with user's info
	     (set-car! (cdr (member (car tail) infos))
		       (cadr tail)))
	    (else
	     (print-gnuplot-setting file (car tail) (cadr tail)))))
    ;; rest of args are {{plot} {keys/vals}}+
    (do ((plot #f))
	((null? args)
	 (set! plots (reverse! plots)))
      (if (or (pair? (car args))
	      (type-of (car arg) 'seq))
	  (begin (setq plot (list (car args)
				  (list :trange #f :xrange #f :yrange #f)))
		 (push plot plots))
	  (err "Not list or seq of plot data: ~s" (car args)))
      ;; gather keyargs for current plot. ranges are handled
      ;; specially since these must appear at front of plot command
      (do ((tail (cdr args) (cddr tail)))
	  ((or (null? tail)
	       (not (keyword? (car tail)))))
	(if (null? (cdr tail))
	    (err "Missing value for keyword ~s." (car tail))
	    (let ((rng (member (car tail) (second plot))))
	      (if (not rng)
		  (append! plot (list (car tail) (cadr tail)))
		  (list-set! plot (cadr rng) (cadr tail))))))
      ;; plots now list of (plot args...)
      ;; print plot command and args for each plot. 
      (unless (null? plots)
	;; print plot command
	(format f "plot")
	;; print clause for each plot...
        (do ((tail plots (cdr tail)))
	    ((null? tail) #f)
	  (let* ((plot (car tail))
		 (dataf (member :data (cdr plot))))
	    ;; print plot ranges...
	    (do ((tail (second plot) (cddr tail))
		 (func (find-gnuplot-setting :xrange)))
		((null? tail) #f)
	      (if (second tail)
		  ( func f (second tail))))
	    (format f " '-'")

	    ;; print various options
	    (do ((tail (cddr plot) (cddr tail)))
		((null? tail) #f)
	      (print-gnuplot-setting file (car tail) (cadr tail) t))))

	;; print data blocks
	(do ((tail plots (cdr tail)))
	    ((null? tail) #f)
	  (print
    ))))))

;;;
;;; eof
;;;









