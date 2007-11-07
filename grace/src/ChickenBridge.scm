;;; **********************************************************************
;;; Copyright (C) 2007 Todd Ingalls, Rick Taube.
;;; This program is free software; you can redistribute it and/or modify
;;; it under the terms of the Lisp Lesser Gnu Public License. The text of
;;; this agreement is available at http://www.cliki.net/LLGPL            
;;; **********************************************************************

#>

/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

#include "Grace.h"
#include "Scheme.h"
#include "OutputQueue.h"

//
// Console Window code
//

void print_mess(char * st)
{
// ((GraceApp *)GraceApp::getInstance())->getConsole()->printMessage( String(st));
   printf("%s", st);
}

void print_error(char * st)
{
// ((GraceApp *)GraceApp::getInstance())->getConsole()->printError( String(st));
   printf("%s", st);
}

//
// MIDI Port code
//

void mp_note(double time, double dur, float k, float v, float c) {
 float on[3];
 float off[3];
 on[0] =  off[0] = k;
 on[1] = v;
 off[1] = 0.0;
 on[2] = off[2] =  c;
 ((GraceApp *)GraceApp::getInstance())->outputQueue->outputNodes.lockArray();
 ((GraceApp *)GraceApp::getInstance())->outputQueue->addNode(time, on, 3);
 ((GraceApp *)GraceApp::getInstance())->outputQueue->addNode(time+dur, off, 3); 
 ((GraceApp *)GraceApp::getInstance())->outputQueue->outputNodes.unlockArray();
}

void mp_on(double time, float k, float v, float c) {
 float vals[3];
 vals[0] = k;
 vals[1] = v;
 vals[2] = c;
 ((GraceApp *)GraceApp::getInstance())->outputQueue->outputNodes.lockArray();
 ((GraceApp *)GraceApp::getInstance())->outputQueue->addNode(time, vals, 3);
 ((GraceApp *)GraceApp::getInstance())->outputQueue->outputNodes.unlockArray();
}

//
// Scheduler code
//

void scheduler_sprout( C_word proc, double time, int id)
{
  ((GraceApp *)
   GraceApp::getInstance())->schemeProcess->addNode(0, time, proc, id);
}

bool scheduler_is_paused () {
  ((GraceApp *)GraceApp::getInstance())->schemeProcess->isPaused();
}

void scheduler_pause() {
  ((GraceApp *)GraceApp::getInstance())->schemeProcess->setPaused(true);
}

void scheduler_cont () {
  ((GraceApp *)GraceApp::getInstance())->schemeProcess->setPaused(false);
}

void scheduler_stop (int id) {
  ((GraceApp *)GraceApp::getInstance())->schemeProcess->stop(id);
}

void scheduler_hush () {
  ((GraceApp *)GraceApp::getInstance())->schemeProcess->stop(-1);
  ((GraceApp *)GraceApp::getInstance())->outputQueue->clear();
}

bool scheduler_is_time_milliseconds () {
  ((GraceApp *)GraceApp::getInstance())->schemeProcess->isTimeMilliseconds();
}
 
void scheduler_set_time_milliseconds (bool b) {
  ((GraceApp *)GraceApp::getInstance())->schemeProcess->setTimeMilliseconds(b);
}

<#

(declare
 (unit grace)
 (run-time-macros)
 (uses extras)
 (usual-integrations)
 (export print-message print-error 
         mp:note mp:on mp:off mp:prog
         mp:ctrl mp:alloff mp:micro mp:inhook 
	 send go
	 now time-format
	 sprout stop hush pause paused? cont
	 ))

;;;
;;; FFI glue code
;;;

;; Console window

(define print-message
  (foreign-lambda void "print_mess" c-string))

(define print-error
  (foreign-lambda void "print_error" c-string))

;; MIDI Port

(define mp-note
  (foreign-safe-lambda void "mp_note" double double float float float));

;;(define-external (run_process (scheme-object closure) (double elapsed)) double
;;  ( closure  elapsed))
;;
;;(define current-time-hi-res
;;  (foreign-lambda* double ()
;;     " C_return(Time::getMillisecondCounterHiRes());"))

;; Time

(define current-time-milliseconds
  (foreign-lambda* int ()
     " C_return( (int) Time::getMillisecondCounterHiRes());"))

(define current-time-seconds
  (foreign-lambda* float ()
     " C_return( (float) (Time::getMillisecondCounterHiRes() / 1000.0));"))
  
(define scheduler-is-time-milliseconds
  (foreign-safe-lambda bool "scheduler_is_time_milliseconds" )  )

(define scheduler-set-time-milliseconds
  (foreign-safe-lambda void "scheduler_set_time_milliseconds" bool))

;; Scheduler API

(define scheduler-sprout
  (foreign-safe-lambda void "scheduler_sprout" scheme-object double int))

(define scheduler-paused?
  (foreign-safe-lambda bool "scheduler_is_paused" ))

(define scheduler-pause
  (foreign-safe-lambda void "scheduler_pause"))

(define scheduler-cont
  (foreign-safe-lambda void "scheduler_cont" ))

(define scheduler-stop
  (foreign-safe-lambda void "scheduler_stop" int))

(define scheduler-hush
  (foreign-safe-lambda void "scheduler_hush" ))

;;;
;;; top level scheme code
;;;

(define (sprout proc . args)
  ;; (sprout {proc|list} [ahead|list] [id|list])
  (let-optionals
   args ((start 0)
	 (id -1))
   (let ((nextstart (lambda ()
		      (if (pair? start)
			  (let ((v (car start)))
			    (set! start (if (null? (cdr start))
					    (car start) (cdr start)))
			    v)
			  start)))
	 (nextid (lambda ()
		   (if (pair? id)
			(let ((v (car id)))
			  (set! id (if (null? (cdr id))
				       (car id) (cdr id)))
			  v)
			id))))
     (cond ((pair? proc)
	    (do ((p proc (cdr p)))
		((null? p) proc)
	      (scheduler-sprout (car p) (nextstart) (nextid))))
	   (else
	    (scheduler-sprout proc (nextstart) (nextid))
	    proc))
     ;; if return proc would chicken put it in a History list and so
     ;; never get gc'd?
     (values))))

(define now current-time-milliseconds)

(define (time-format . arg)
  (if (null? arg)
      (if (scheduler-is-time-milliseconds ) 1000 1.0)
      (case (car arg)
	((1.0 1 s)
	 (set! now current-time-seconds)
	 (scheduler-set-time-milliseconds #f)
	 )
	((1000 m)
	 (set! now current-time-milliseconds)
	 (scheduler-set-time-milliseconds #t)
	 )
	(else
	 (error "not a time-format" (car arg))))))

(define (pause )
  (scheduler-pause )
  (values))

(define (paused? )
  (scheduler-paused?))

(define (cont )
  (scheduler-cont )
  (values))

(define (stop . procid)
  (if (null? procid)
      (scheduler-stop -1)
      (do ((tail procid (cdr tail)))
	  ((null? tail) #f)
	(if (fixnum? (car tail))
	    (scheduler-stop (car tail))
	    (error "Not an integer id" (car tail)))))
  (values))

(define (hush )
  (scheduler-hush)
  (values))

;;;
;;; send macro
;;;

(define *messages* (make-hash-table equal?))

(define-macro (define-send-message func info)
  (let ((name #f))
    (cond ((pair? func)
	   (set! name (car func))
	   (set! func (cadr func)))
	  ((string? func)
	   (set! name func)
	   (set! func (string->symbol func)))
	  ((symbol? func)
	   (set! name (symbol->string func)))
	  (else
	   (error "message function not string, symbol or list of both")))
    `(hash-table-set! *messages* ,name (quote ,(cons func info)))))

(define (ferror str  . args)
  (error (apply sprintf str args)))

(define (expand-send mesg data)
  (let* ((mess (if (symbol? mesg) (symbol->string mesg) mesg))
	 (entry (hash-table-ref *messages* mess	(lambda () #f))))
    (if (not entry) (ferror "~S is an invalid message" mess) )
    (let* ((save data)
	   (func (car entry))
	   (info (cdr entry))
	   (keys? #f)
	   (argn (length info))
	   ;; set args equal to info then replace with data
	   (args (append info (list)))
	   )
      ;; loop over data setting args to values from data.  data can be
      ;; mixture of positionals and keyword/value pairs.  once a
      ;; keyword is found the remaining data must be keyword/value
      ;; pairs
      (do ((key #f)
	   (arg #f)
	   (pos 0))
	  ((null? data) #f )
	(cond ((and (not keys?)
		    (keyword? (car data)))
	       ;; maybe this clause should test if keyword is actually
	       ;; valid for the message and only switch to keyword
	       ;; style if (car data) is a keyword of the
	       ;; message. currently any keyword switches to keyword
	       ;; style which means you cant pass keywords as
	       ;; positional values to the underlying functions.
	       (set! keys? #t))
	      ((not keys?)
	       (if (= pos argn) 
		   (ferror "~S expected ~A arguments but got ~A"
			   mess argn (length save)))
	       (set-car! (list-tail args pos)
			 (car data))
	       (set! data (cdr data))
	       (set! pos (+ pos 1)))
	      (else
	       (set! key (car data))
	       (set! arg (assoc key info))
	       (set! data (cdr data))
	       (cond ((not (keyword? key))
		      (ferror "~S expected keyword but got '~S'"
			      mess key))
		     ((null? data)
		      (ferror "~S missing value for keyword '~S'" 
			      mess key))
		     ((not arg)
		      (ferror
		       "~S found invalid keyword '~S'~%Available keywords: ~S"
			      mess key (map car info))))
	       ;; replace key's arg in data with val. if arg is
	       ;; already replaced then keyword was specified twice
	       (let ((tail (member arg args)))
		 (if (not tail)
		     (ferror "~S found duplicate keyword '~S' in ~S"
			     mess key save))
		 (set-car! tail (car data)))
	       (set! data (cdr data)))))
      ;; remap args replacing remaining args with default data
      (do ((tail args (cdr tail)))
	  ((null? tail)
	   ;; quote this for now...
	   ;;`(quote ,(cons func args))
	   (cons func args)
	   )
	(if (member (car tail) info)
	    (set-car! tail (cadr (car tail)))))
      )))

(define-macro (send mess . data)
  (expand-send mess data))

;; port:method defintions
;; DO THESE NEED ERROR HANDLING AROUND ARGS?

(define (mp:note time dur key amp chan)
  (mp-note time dur key amp chan)
  )

(define (mp:on time key vel chan)
  (error "message function not implemented."))
(define (mp:off time key vel chan)
  (error "message function not implemented."))
(define (mp:prog time prog chan)
  (error "message function not implemented."))
(define (mp:ctrl time ctrl val chan)
  (error "message function not implemented."))
(define (mp:alloff )
  (error "message function not implemented."))
(define (mp:micro divs)
  (error "message function not implemented."))
(define (mp:inhook func)
  (error "message function not implemented."))

;; message definitions

(define-send-message mp:note ((#:time 0) (#:dur .5) (#:key 60) (#:amp 127) (#:chan 1)))
(define-send-message mp:on   ((#:time 0) (#:key 60) (#:vel 64) (#:chan 1)))
(define-send-message mp:off  ((#:time 0) (#:key 60) (#:vel 64) (#:chan 1)))
(define-send-message mp:prog ((#:time 0) (#:prog 60) (#:chan 0)))
(define-send-message mp:ctrl ((#:time 0) (#:ctrl 60) (#:val 0) (#:chan 1)))
(define-send-message mp:alloff ())
(define-send-message mp:micro ((#:divs 1)))
(define-send-message mp:inhook ((#:func #f)))


;;;
;;; GO macro
;;;

(define-macro (go bindings terminate . body)
  (expand-go bindings terminate body)
  )

(define (expand-go bindings terminate body)
  (let ((bind (list))
	(init (list))
	(step (list)))
    (if (not (list? bindings))
	(error "go bindings not a list" bindings))
    (if (not (list? terminate))
	(error "go stopping clause not a list" terminate)
	(if (null? terminate)
	    (error "go stopping clause missing test form")))
    (do ((tail bindings (cdr tail)))
	((null? tail ) #f)
      (if (and (pair? (car tail)) 
	       (< 0 (length (car tail)) 4)
	       (symbol? (car (car tail))))
	  (let* ((v (car (car tail)))
		 (i (cadr (car tail)))
		 (s (if (null? (cddr (car tail))) 
			#:null
			(caddr (car tail))
			)))
	    (set! bind (append bind (list v)))
	    (set! init (append init (list i)))
	    (set! step (append step
			       (if (eq? s #:null) (list)
				   (list `(set! ,v , s))))))
	  (error "binding clause not list (var init [step])" 
		 (car tail))))
    (let ((paramvar (gensym)) ; callback param receives time from C
	  (deltavar (gensym))
	  (errorvar (gensym))
	  (contvar (gensym))
	  (safety #t)
	  (procbody '()))
      ;; optional (declare ...) can be first form in body
      (if (and (pair? body)
	       (pair? (car body))
	       (eq? (caar body) 'declare))
	  (do ((decl (cdar body) (cdr decl)))
	      ((null? decl) 
	       (set! body (cdr body))) ; remove decl from body
	    (if (and (pair? (car decl))
		     (pair? (cdar decl)))
		(case (caar decl)
		  ((safety )
		   (if (not (car (cdar decl)))
		       (set! safety #f)))
		  (else
		   (error "unknown declaration" (car decl))))
		(error "declaration not list (decl val)" (car decl)))))

      (set! procbody
	    `(cond (,(car terminate) ,@(cdr terminate)
		    -1)  ; -1 = stop 
		   (else ,@body  ; users code
			 ,@step ; stepping forms
			 ,deltavar)))  ; return delta
      (if safety
	  (set! procbody
; this works with (require-extension chicken-more-macros)
;		`(condition-case
;		  ,procbody
;		  (,errorvar 
;		   (exn)
;		   (printf ">>> Aborting process at time ~S:~%    Error: ~S" 
;			   ,paramvar
;			   ( (condition-property-accessor 'exn 'message) 
;			     ,errorvar))
;		   -2))
		`(call-with-current-continuation
		  (lambda (,contvar)
		    (with-exception-handler
		     (lambda (,errorvar)
		       (printf ">>> Aborting process at time ~S:~%    Error: ~S"
			       ,paramvar
			       ((condition-property-accessor 'exn 'message)
			       ,errorvar))
		       (,contvar -2))
		     (lambda () ,procbody))
		    ))
		))
      `((lambda (,@bind)
	  (lambda (,paramvar )
	    (let* ((,deltavar 0)
		   (elapsed (lambda () ,paramvar))
                   (wait (lambda (x)
                           (set! ,deltavar x)))
		   )
	      ,procbody
	      )))
	,@init)
      )))

(return-to-host)

;; csc -c++ -embedded -t ChickenBridge.scm

