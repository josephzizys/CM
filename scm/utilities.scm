;;; **********************************************************************
;;; Copyright (C) 2007, 2008 Todd Ingalls, Rick Taube.
;;; This program is free software; you can redistribute it and/or modify
;;; it under the terms of the Lisp Lesser Gnu Public License. The text of
;;; this agreement is available at http://www.cliki.net/LLGPL            
;;; **********************************************************************

;;;
;;; non-r5rs utilities that are not scheme implementation specific
;;;

(define (quit) 
  (ffi_quit))

; moved to c
;(define (cm-version )  (ffi_version ))
;(define (cm-logo ) (ffi_print_output (ffi_logo )))

(define (print-error msg)
   (ffi_print_error msg))

(define (print-output msg . quo)
  (if (or (null? quo)
	  (not (car quo)))
      (ffi_print_output msg #f)
      (ffi_print_output msg #t)))

(define (print-values msg )
  (ffi_print_value msg))

(define (shell str)
  (ffi_shell str))

(define first car)
(define second cadr)
(define third caddr)
(define fourth cadddr)
(define fifth (lambda (l) (car (cddddr l))))
(define sixth (lambda (l) (cadr (cddddr l))))
(define seventh (lambda (l) (caddr (cddddr l))))
(define eighth (lambda (l) (cadddr (cddddr l))))
(define ninth (lambda (l) (car (cddddr (cddddr l)))))
(define tenth (lambda (l) (cadr (cddddr (cddddr l)))))
(define nth list-ref)

(define (rest l) (cdr l))

; this is not cltl's last!
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

; joins args into a list, args can be atoms or lists
(define (concat . args)
  (let* ((head (list #f))
	 (tail head))
    (do ((a args (cdr a)))
	((null? a) 
	 (cdr head))
      (cond ((null? (car a))
	     )
	    ((pair? (car a))
	     (do ((t (car a) (cdr t)))
		 ((null? t) #f)
	       (set-cdr! tail (list (car t)))
	       (set! tail (cdr tail))))
	    (else
	     (set-cdr! tail (list (car a)))
	     (set! tail (cdr tail)))))))

(define (reverse! l)
  (let ((s (length l)))
    (do ((i 0 (+ i 1))
	 (j (- s 1) (- j 1))
	 (t l (cdr t)))
	((not (< i j)) l)
      (let ((x (car t))
	    (z (list-tail t (- j i ))))
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

(define (list-prop lis prop . def)
  (if (null? lis)
      (if (null? def) #f (car def))
      (if (eqv? (car lis) prop)
          (cadr lis)
          (apply list-prop (cddr lis) prop def))))

(define (list-prop-set! lis prop val)
  (if (eqv? (car lis) prop)
      (set-car! (cdr lis) val)
      (if (null? (cddr lis))
          (set-cdr! (cdr lis) (list prop val))
          (list-prop-set! (cddr lis) prop val))))

;; sequence mapping.

(define (%mapseq func seq elements? start end)
  ;; this is the workhorse, if elements is true it returns elements
  ;; else positions
  (let ((seqlen #f)
	(getter #f))
    (cond ((list? seq)
	   (set! getter list-ref)
	   (set! seqlen length))
	  ((string? seq)
	   (set! getter string-ref)
	   (set! seqlen string-length))
	  ((vector? seq)
	   (set! getter vector-ref)
	   (set! seqlen vector-length))
	  (else
	   (error "not a list, string or vector" seq)))
    (do ((i start (+ i 1))
	 (l (or end (seqlen seq)))
	 (e #f)
	 (f #f)
	 (r #f))
	((or (>= i l) f)
	 r)
      (set! e (getter seq i))
      (if (func e)
	  (begin (set! r (if elements? e i))
		 (set! f #t))))))

(define (find x seq . args)
  (with-optkeys (args (key #f) (start 0) (end #f))
    (%mapseq (if key
		 (lambda (a) (equal? (key a) x))
		 (lambda (a) (equal? a x)))
	     seq
	     #t
	     start
	     end)))

(define (position x seq . args)
  (with-optkeys (args (key #f) (start 0) (end #f))
    (%mapseq (if key
		 (lambda (a) (equal? (key a) x))
		 (lambda (a) (equal? a x)))
	     seq
	     #f
	     start
	     end)))

;;; (opt/key) parameter support. Uses define-for-syntax because
;;; chicken compiler needs the expansion at compile time

(define-for-syntax (expand-optkeys user spec body)
  (define (key-parse-clause info mode args user)
    ;; return a case clause that parses one keyword
    ;; info for each var: (<got> <var> <val>)
    (let* ((got (car info))
	   (var (cadr info))
	   (key (string->keyword (symbol->string var)))
	   )
      `(( ,key )
	(if ,got (error "Redundant keyword" , key))
	(set! ,var (if (null? (cdr ,args))
		       (error "Missing keyword value in" 
			      , user)
		       (cadr ,args)))
	(set! ,got #t) ; mark that we have a value for this param
	(set! ,mode #t) ; mark that we are now parsing keywords
	(set! ,args (cddr ,args)))))
  (define (opt-parse-clause info mode pars user)
    (let ((got (car info))
	  (var (cadr info)))
      `(else
	(when ,mode (error "Positional after keywords" 
			   ,user))
	(set! ,var (car ,pars))
	(when (keyword? ,var) (error "Unknown keyword",  var))
	(set! ,got #t) ; mark that we have a value for this param
	(set! ,pars (cdr ,pars)))))
  (define (parse-optkey info data mode args user keyc)
    ;; return a complete parsing clause for one optkey variable. keyc
    ;; holds all the key parsing clauses used by each case statement
    `(unless (null? ,args)
       (case (car ,args)
	 ;; generate all keyword clauses
	 ,@ keyc
	    , (opt-parse-clause info mode args user))))
  (let* ((data (map (lambda (v)
		      ;; for each optkey variable v return a list
		      ;; (<got> <var> <val>) where the <got> variable
		      ;; indicates that <var> has been set, <var> is
		      ;; the optkey variable and <val> is its default
		      ;; value
		      (if (pair? v)
			  (cons (gensym (symbol->string (car v))) v)
			  (list (gensym (symbol->string v)) v #f)))
		    spec))
	 (args (gensym "args")) ; holds arg data as its parsed
	 (mode (gensym "keyp")) ; true if parsing keywords
	 ;; the case clauses parsing each keyword
	 (keyc (map (lambda (i) (key-parse-clause i mode args user))
		 data)))
    `(let* ,(map cdr data) ; bind optkey variables with default values
       ;; bind status and parsing vars
       (let ,(append (map (lambda (i) (list (car i) #f)) data)
		     `((,args ,user)
		       (,mode #f)))
	 ;; generate a parsing expression for each optkey variable
	 ,@ (map (lambda (i)
		   (parse-optkey i data mode args user keyc))
		 data)
	 ;; add a check to make sure no dangling args.
	    (unless (null? ,args)
	      (error "Too many arguments" , user))
	    ,@ body))))

(define-macro (with-optkeys spec . body)
  (expand-optkeys (car spec) (cdr spec) body))
