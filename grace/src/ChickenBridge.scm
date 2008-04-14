;;; **********************************************************************
;;; Copyright (C) 2007, 2008 Todd Ingalls, Rick Taube.
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
#include "Syntax.h"
#include "Midi.h"
#include <juce.h>

//
// Console Window code
//

void print_message(char * st) {
  // attempt at buffering: if string ends with #\Return, send string
  // AND trigger update else send string without triggering update
  String s=String(st);
  if ( s.endsWithChar('\n') )
    ((GraceApp *)GraceApp::getInstance())->getConsole()->postConsoleTextMessage(s, ConsoleMessage::TEXT, true);
  else
    ((GraceApp *)GraceApp::getInstance())->getConsole()->postConsoleTextMessage(s, ConsoleMessage::TEXT, false);
}

void print_error(char * st) {
  // attempt at buffering: if string ends with #\Return, send string
  // AND trigger update else send string without triggering update

printf("in print_error\n");
printf("  str='%s'\n",st);

  String s=String(st);
  if ( s.endsWithChar('\n') )
    ((GraceApp *)GraceApp::getInstance())->getConsole()->postConsoleTextMessage(s, ConsoleMessage::ERROR, true);
  else
    ((GraceApp *)GraceApp::getInstance())->getConsole()->postConsoleTextMessage(s, ConsoleMessage::ERROR, false);
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
  ((GraceApp *)GraceApp::getInstance())->midiOutPort->clear();
}

bool scheduler_is_time_milliseconds () {
  ((GraceApp *)GraceApp::getInstance())->schemeProcess->isTimeMilliseconds();
}
 
void scheduler_set_time_milliseconds (bool b) {
  ((GraceApp *)GraceApp::getInstance())->schemeProcess->setTimeMilliseconds(b);
}

//void print_current_directory() {
//  String s=File::getCurrentWorkingDirectory().getFullPathName().quoted() + T("\n");
//  ((GraceApp *)GraceApp::getInstance())->getConsole()->postConsoleTextMessage(s, ConsoleMessage::TEXT, true);
//}

char *get_current_directory() {
  return (char *)File::getCurrentWorkingDirectory().getFullPathName().toUTF8();
}

void set_current_directory (char *path) {
  File dir=File(String(path));
  if ( dir.isDirectory() ) {
    dir.setAsCurrentWorkingDirectory();
    //print_working_directory();
  }
  else {
    String s=T(">>> Error: ") + dir.getFullPathName().quoted() + T(" is not a directory.\n");
    ((GraceApp *)GraceApp::getInstance())->getConsole()->postConsoleTextMessage(s, ConsoleMessage::ERROR, true);
  }			 
}

void load_sal_file(char *path) {
  SalSyntax::getInstance()->loadFile( String(path) );  
}

<#

(declare
 (unit grace)
 (run-time-macros)
 (uses extras )
 (usual-integrations)
 (export print-message print-error 
	 ;; MIDI
	 mm:off mm:on mm:touch mm:ctrl mm:prog mm:press mm:bend
	 mm:make-on mm:make-off mm:make-touch mm:make-ctrl
	 mm:make-prog mm:make-press mm:make-bend
	 mm:on? mm:off? mm:touch? mm:ctrl? mm:prog? mm:press? mm:end?
	 mm:free mm:copy 
	 mm:time mm:time-set! mm:chan mm:chan-set!
	 mm:key mm:key-set! mm:vel mm:vel-set!
	 mm:val mm:val-set! mm:num mm:num-set!

         mp:midi mp:note mp:off mp:on mp:touch mp:ctrl mp:prog 
	 mp:press mp:bend
	 mp:mm mp:inhook 

	 ;; Csound
	 cs:i cs:f cs:clear

	 *messages* send expand-send 
	 define-process run ;go
	 current-time-milliseconds current-time-seconds
	 now time-format
	 sprout stop hush pause paused? cont
	 ;; toolbox

	 note key hz pc transpose invert retrograde
	 scale scale-order scale-order!

	 rescale discrete fit int quantize decimals
	 plus minus times divide
	 cents->ratio ratio->cents
	 rhythm->seconds interp

	 between pick odds shuffle shuffle! vary segs tendency 
	 ran ran-set! ranlow ranhigh ranmiddle rangauss ranexp
	 ranbeta rangamma rancauchy ranpoisson ranpink ranbrown

	 rm-spectrum fm-spectrum import-spear-frames spectrum-copy
	 spectrum-time spectrum-size spectrum-freqs spectrum-amps
	 spectrum-keys spectrum-pairs
	 spectrum-minfreq spectrum-maxfreq spectrum-minamp
	 spectrum-maxamp spectrum-add! spectrum-flip!
	 spectrum-rescale!

	 ;; sal
	 sal sal:print sal:chdir sal:load sal:open sal:output
	 load-sal-file *sal-trace-input*
	 ;; utilities
	 loop
	 cwd chdir cm-logo

	 first second third fourth fifth sixth seventh eighth
	 ninth tenth last nth butlast rest list* 
	 make-list list-find list-index tail
	 list-set! reverse! every?

	 with-optkeys expand-optkeys

	 make-cycle make-line make-palindrome make-heap make-rotation 
	 make-weighting make-markov make-graph markov-analyze
	 next eop? eod?
	 ))

;;;  (opt/key) parameter support:

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

(define (expand-send mesg data errf)
  ;; errf is an error continuation if called from sal
  (let* ((ferror (or errf (lambda (str . args)
			    (error (apply sprintf str args)))))
	 (sal? errf)
	 ;; show sal style keywords if called from sal
	 (keyname (if sal?
		      (lambda (k) (sprintf "~A:" (keyword->string k)))
		      (lambda (k) k)))
	 (mess (if (symbol? mesg) (symbol->string mesg) mesg))
	 (entry (hash-table-ref *messages* mess	(lambda () #f))))
    (if (not entry) (ferror "~S is an invalid message" mess) )
    (let* ((save data)
	   (func (car entry))
	   (info (cdr entry))
	   (keys? #f)
	   (argn (length info))
	   )
      ;; loop over data setting args to values from data.  data can be
      ;; mixture of positionals and keyword/value pairs.  once a
      ;; keyword is found the remaining data must be keyword/value
      ;; pairs
      (if (and (= argn 1) (eq? (car info) '&rest))
	  (cons func data)
	  (do (;; set args equal to info then replace with data
	       (args (append info (list)))
	       (key #f)
	       (arg #f)
	       (pos 0))
	      ((null? data) 
	       ;; remap args replacing unspecified args with default data
	       (do ((tail args (cdr tail)))
		   ((null? tail)
		    ;; quote this for now...
		    ;;`(quote ,(cons func args))
		    (cons func args)
		    )
		 (if (member (car tail) info)
		     (set-car! tail (cadr (car tail))))))
	    (cond ((and (not keys?)
			(keyword? (car data)))
		   ;; maybe this clause should test if keyword is actually
		   ;; valid for the message and only switch to keyword
		   ;; style if (car data) is a keyword of the
		   ;; message. currently any keyword switches to keyword
		   ;; style which means you cant pass keywords as
		   ;; positional values to the underlying functions.
		   (set! keys? #t)
		   )
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
			  (ferror "~S missing value for keyword '~A'" 
				  mess (keyname key)))
			 ((not arg)
			  (ferror
			   "~S invalid keyword '~A'~%Available keywords: ~A"
			   mess key (map (lambda (x) (keyname (car x)))
					 info))))
		   ;; replace key's arg in data with val. if arg is
		   ;; already replaced then keyword was specified twice
		   (let ((tail (member arg args)))
		     (if (not tail)
			 (ferror "~S duplicate keyword '~S'"
				 mess (keyname key)))
		     (set-car! tail (car data)))
		   (set! data (cdr data))))))
      )))

(define-macro (send mess . data)
  (expand-send mess data #f))


;; imlementation specific utilities 

(define-constant most-positive-fixnum #x3fffffff)

(define-constant most-negative-fixnum (- #x3fffffff))

(define (cwd )
  ((foreign-lambda c-string "get_current_directory" )))

(define (chdir . dir)
  ((foreign-lambda void "set_current_directory" c-string)
   (if (null? dir) "~/" (car dir))))

;;
;; THE API
;;

(include "Utilities.scm")
(include "Toolbox.scm")
(include "Spectral.scm")
(include "Patterns.scm")
(include "Sal.scm")
(include "Loop.scm")
(include "Midi.scm")
(include "Csound.scm")

;; Environment

(define (cm-logo vers) 
  ;; vers: nn.nn.nn
  (define (cm-version vers)
    (let ((a 0) (b 0) (c 0))
      (set! a (inexact->exact (floor (/ vers 10000))))
      (set! vers (modulo vers 10000))
      (set! b (inexact->exact (floor (/ vers 100))))
      (set! c (modulo vers 100))
      (string-append "Common Music " (number->string a)
		     "." (number->string b)
		     "." (number->string c))))
  (do ((e "~%")
       (v (make-string 15))
       (y 0 (+ y 1)))
      ((= y 7) #f)
    (if (= y 0) (printf e))
    (printf (do ((x 0 (+ x 1)))
		((= x 15)
		 (if (= y 3)
		     (string-append v " " (cm-version vers) "")
		     (string-append v "")))
	      (string-set! v x
			   (if (<= 2 (- x y) 4) #\\
			       (if (= (- x (- 4 (modulo (+ 13 y) 15))) 1)
				   #\/
				   (if (<= 1 y 5) #\-
				       (if (= (* (- x 6) (- y 3)) 15) #\/
					   #\space)))))))
    (printf e))
  (values))

;; (cm-logo 30001)

;; Console window

(define print-message
  (foreign-lambda void "print_message" c-string))

(define print-error
  (foreign-lambda void "print_error" c-string))

;;(define-external (run_process (scheme-object closure) (double elapsed)) double
;;  ( closure  elapsed))
;;
;;(define current-time-hi-res
;;  (foreign-lambda* double ()
;;     " C_return(Time::getMillisecondCounterHiRes());"))

;; Time

(define current-time-milliseconds
  (foreign-lambda* double ()
     " C_return( Time::getMillisecondCounterHiRes());"))

(define current-time-seconds
  (foreign-lambda* double ()
     " C_return( (Time::getMillisecondCounterHiRes() / 1000.0) );"))
  
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

;; OS interface

(define (load-sal-file file)
  ((foreign-lambda void "load_sal_file" c-string) file))

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
     ;; arrrg! for some reason scheduler-sprout assumes milliseconds
     (cond ((pair? proc)
	    (do ((p proc (cdr p)))
		((null? p) proc)
	      (scheduler-sprout (car p) (* (nextstart) 1000)
				(nextid))))
	   (else
	    (scheduler-sprout proc (* (nextstart) 1000) (nextid))
	    proc))
     ;; if return proc would chicken put it in a History list and so
     ;; never get gc'd?
     (values))))

;;(define now current-time-milliseconds)

(define now current-time-seconds)

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

;;; RUN macro

;; *process-stop* holds the stopping form: %%stopproc%% is the
;; continuation call and -1 is the value returned to the scheduler.

(define *process-stop* '(%%stopproc%% -1))

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
	(eq? code (car stop)))))

(define (run-loop forms ops)
  (let* ((parsed (parse-iteration 'run forms ops))
	 (code '())
	 (func #f)
	 (tests '())
	 ;; *process-stop* is form that gets exectuted to stop
	 ;; the process
	 (done *process-stop*)
	 (CONT (car done)) ; continution
	 (TIME (gensym "time"))
	 (WAIT (gensym "wait"))
	 (ERRV (gensym "err"))
	)
    (set! tests (loop-end-tests parsed))
    (if (loop-finally parsed)
      (set! done `(begin ,@(loop-finally parsed) ,done)))
    (if (not (null? tests))
      (begin
       (if (null? (cdr tests))
	 (set! tests (car tests))
	 (set! tests (cons 'or tests)))
       (set! tests `((if ,tests ,done))))
      (unless (process-code-terminates?
	       (loop-looping parsed) done)
	(printf "Warning: possible non-terminating process.")
        ))
    (set! func 
	  `(lambda (,TIME )
	     (let* ((,WAIT 0)
		    (elapsed (lambda () ,TIME))
		    (wait (lambda (x) (set! ,WAIT x))))
	       ;; this continuation is the error handler
	       (call-with-current-continuation
		(lambda (,CONT)
		  (with-exception-handler
		   (lambda (,ERRV)
		     (print-error-message ,ERRV (current-error-port)
					  ">>> Error (run)")
		     ;;(print-call-chain (current-error-port))
		     (,CONT -2)  ; -2 signifies stop with error
		     )
		   (lambda ()
		     ,@ tests
			,@ (loop-looping parsed)
			   ,@ (loop-stepping parsed)
			      , WAIT
				)))))))

    (if (and (null? (loop-bindings parsed))
	     (null? (loop-initially parsed)))
      func
      ;; use let* sequential binding
      `(let* ,(loop-bindings parsed)
	 ,@(loop-initially parsed)
	 ,func))))

(define-macro (run . args)
  (run-loop args *run-operators*))

(define-macro (define-process formals . body)
  (unless (and (pair? formals)(symbol? (car formals)))
    (error "Illegal process formals" formals))
  `(define ,formals ,@ body))

;;;
;;; GO macro
;;;

#|
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
		       (print-error
			(sprintf ">>> Error: ~A~%    Aborting process at time ~S~%"
				 ((condition-property-accessor 'exn 'message) ,errorvar)
				 ,paramvar
				 ))
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
|#

(return-to-host)

;; csc -c++ -embedded -t ChickenBridge.scm

