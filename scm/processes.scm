;;; **********************************************************************
;;; Copyright (C) 2008, 2009 Rick Taube.
;;; This program is free software; you can redistribute it and/or modify
;;; it under the terms of the Lisp Lesser Gnu Public License. The text of
;;; this agreement is available at http://www.cliki.net/LLGPL            
;;; **********************************************************************

;; *process-stop* is the code that a process executes to return the
;; 'stop value' back to C to signals no more scheduling. -1 is a
;; normal exit, -2 is an error exit.  the call to (throw ) has to be
;; implemented in the scheme we are running in. in chicken scheme it
;; is a call/cc exit, in s7 it is a call to (error )

(define *process-stop* '(throw -1))

(define (run-while-until forms clauses ops)
  (let ((head forms)
        (oper (pop forms))
        (test #f)
        (stop *process-stop*))
    (when (null? forms)
      (loop-error ops head "Missing '" oper "' expression."))
    (case oper
      ((until) (set! test (pop forms)))
      ((while) (set! test `(not ,(pop forms)))))
    (values (make-loop-clause 'operator oper 'looping
             (list `(if ,test ,stop)))
            forms)))

(define *run-operators*
  (let* ((omit '(collect append nconc sum count
			 minimize maximize thereis
			 always never return
			 while until))
	 (head (list #f))
	 (tail head))
    (do ((ops *loop-operators* (cdr ops)))
	((null? ops)
	 (set-cdr! 
	  tail (list (list 'while (function run-while-until) #f )
		     (list 'until (function run-while-until) #f )))
	 (cdr head))
      (unless (member (car (car ops)) omit)
	(set-cdr! tail (list (car ops)))
	(set! tail (cdr tail))))))

;; (pprint  *run-operators*)

(define (process-code-terminates? code stop)
  ;; see if the stop form is anywhere in the expansions, if not issue
  ;; a warning.  FIX: this should be a call/cc
  (if (null? code) #f
      (if (pair? code)
	(or (process-code-terminates? (car code) stop)
	    (process-code-terminates? (cdr code) stop))
	(equal? code (car stop)))))

(define (expand-process forms )
  ;; if called from sal forms contains the already parsed information
  (let* ((parsed (if (vector? forms) 
		     forms
		     (parse-iteration 'process forms *run-operators*)))
	 (code '())
	 (func #f)
	 (tests '())
	 ;; *process-stop* is form that gets executed to stop
	 ;; the process
	 (done *process-stop*)
	 (TIME (gensym "time"))
	 (WAIT (gensym "wait"))
	)
    ;;(format #t "parsed=~S~%" (vector->list parsed))
    (set! tests (loop-end-tests parsed))
    (if (not (null? (loop-finally parsed)))
      (set! done `(begin ,@(loop-finally parsed) ,done)))
    (if (not (null? tests))
      (begin
       (if (null? (cdr tests))
	 (set! tests (car tests))
	 (set! tests (cons 'or tests)))
       (set! tests `((if ,tests ,done))))
      (unless (process-code-terminates?
	       (loop-looping parsed) done)
	(print-output "Warning: possible non-terminating process.")
        ))
    (set! func 
	  `(lambda (,TIME )
	     (let* ((,WAIT 0)
		    (elapsed (lambda args
			       (if (null? args)
				   ,TIME
				   (if (and (car args)
					    (ffi_sched_score_mode_p))
				       (ffi_sched_score_time)
				       ,TIME))))
		    (wait (lambda (x) (set! ,WAIT x))))
	       ;; the implementation specific expansion that protects
	       ;; against runtime errors under the callback
	       ,(error-protected-process-code
		 (append tests 
			 (loop-looping parsed)
			 (loop-stepping parsed)
			 (list WAIT)))

;	       (catch #t
;		      (lambda ()
;			,@ tests
;			   ,@ (loop-looping parsed)
;			      ,@ (loop-stepping parsed)
;				 , WAIT)
;		      (lambda %%args
;			;; arrrg this func gets called if anything is
;			;; thrown, including our -1 to stop the
;			;; process
;			(cond ((equal? (car %%args) -1)
;			       -1)
;			      (else
;			       (print-error
;				(format #f "Error >>> ~S~%" %%args))
;			       -2)
;			    )))

	       )))
    (if (and (null? (loop-bindings parsed))
	     (null? (loop-initially parsed)))
	func
	;; use let* sequential binding
	`(let* ,(loop-bindings parsed)
	   ,@(loop-initially parsed)
	   ,func))))

(define-macro (process . args)
  (expand-process args ))

(define-macro (define-process formals . body)
  (unless (and (pair? formals)(symbol? (car formals)))
    (error "illegal process formals ~S" formals))
  `(define ,formals ,@ body))


; (define foo (process for i below 3 do (display i) ))
; (foo 0)

;;;
;;; scheduler api
;;;

; (sprout aaa 0 "test.snd" ...)


(define (sprout proc . args)
  ;; (sprout {proc|list} [ahead|list] [id|list|file] ...)
  (let ((start 0)
	(id -1)
	(file #f))
    ;; parse args and check for illegal values before sprouting
    ;; anything. first make sure all procs are really procedures...
    (or (procedure? proc)
	(and (pair? proc)
	     (do ((tail proc (cdr tail)))
		 ((null? tail) #t)
	       (if (not (procedure? (car tail)))
		   (error "~S is not a process" proc))))
	(error "~S is not a process" proc)	)
    ;; parse args until file info...
    (do ((tail args (cdr tail))
	 (argn 0 (+ argn 1)))
	((or (null? tail) file)
	 (set! args tail))
      (cond ((string? (car tail))
	     (set! file (car tail)))
	    ((= argn 0)
	     (set! start (car tail)))
	    ((= argn 1)
	     (set! id (car tail)))
	    (else
	     (error "illegal sprout arguments ~S" args))))
    ;; make sure all starts are valid start times...
    (or (and (number? start) (>= start 0))
	(and (pair? start)
	     (do ((tail start (cdr tail)))
		 ((null? tail) #t)
	       (if (or (not (number? (car tail)))
		       (< (car tail) 0))
		   (error "~S is not a process start time for sprout"
			  (car tail)))))
	(error "~S is not a process start time for sprout" start))
    ;; make sure all ids are integers
    (or (integer? id)
	(and (pair? id)
	     (do ((tail id (cdr tail)))
		 ((null? tail) #t)
	       (if (not (integer? (car tail)))
		   (error "~S is not a process id for sprout"
			  (car tail)))))
	(error "~S is not a process id" id))
    ;; open output file or signal error
    (if file (set! file (apply open-file file args)))
    ;; everything ok, do process sprouting!
    (let ((nextstart
	   (lambda ()
	     (if (pair? start)
		 (let ((v (car start)))
		   (set! start (if (null? (cdr start))
				   (car start) (cdr start)))
		   v)
		 start)))
	  (nextid 
	   (lambda ()
	     (if (pair? id)
		 (let ((v (car id)))
		   (set! id (if (null? (cdr id))
				(car id) (cdr id)))
		   v)
		 id))))
      (if (pair? proc)
	  (do ((p proc (cdr p)))
	      ((null? p) proc)
	    (ffi_sched_sprout (car p) (nextstart)
			      (nextid)))
	  (ffi_sched_sprout proc (nextstart) (nextid)))
      (void))))

(define (now )
  (ffi_now))

;(define (score-time)
;  (ffi_score_time ))
;
;(define (score-mode? )
;  (ffi_score_mode_p))

(define (pause )
  (ffi_sched_pause ))

(define (paused? )
  (ffi_sched_paused_p))

(define (continue )
  (ffi_sched_continue ))

(define (stop . procid)
  (if (null? procid)
      (ffi_sched_stop -1)
      (do ((tail procid (cdr tail)))
	  ((null? tail) #f)
	(if (fixnum? (car tail))
	    (ffi_sched_stop (car tail))
	    (error "~S is not a process id" (car tail)))))
  (void))

;(define (hush )
;  (ffi_sched_hush))

(define (busy? )
  (ffi_sched_busy_p))

