
#>
#include "Grace.h"
#include "Scheme.h"
#include "Nodes.h"

void print_mess(char * st)
{

  ((GraceApp *)GraceApp::getInstance())->getConsole()->printMessage( String(st));
}

void print_error(char * st)
{

  ((GraceApp *)GraceApp::getInstance())->getConsole()->printError( String(st));
}

void insert_midi_note(double time, float k, float v, float c)
{
 float *vals = new float[3];
 vals[0] = k;
 vals[1] = v;
 vals[2] = c;
 ((GraceApp *)GraceApp::getInstance())->queue->addNode(0, time, vals, 3, 0);

}

void insert_process( double time, C_word proc )
{
  ((GraceApp *)GraceApp::getInstance())->queue->addNode(1, time, 0, 0, proc);
}

void insert_closure( double time, C_word proc )
{
  ((GraceApp *)GraceApp::getInstance())->queue->addNode(2, time, 0, 0, proc);
}

 
<#

(declare
 (unit grace)
 (run-time-macros)
 (uses extras)
 (export print-message print-error insert-process make-process
         insert-closure insert-midi-note
         make-note-on make-note-off expand-send
         mp:note mp:on mp:off mp:prog
         mp:ctrl mp:alloff mp:micro mp:inhook send
         runran runproc expand-go go ))




(define print-message
  (foreign-lambda void "print_mess" c-string))

(define print-error
  (foreign-lambda void "print_error" c-string))

(define insert-process
  (foreign-safe-lambda void "insert_process" double scheme-object))

(define insert-closure
  (foreign-safe-lambda void "insert_closure" double scheme-object))

(define insert-midi-note
  (foreign-safe-lambda void "insert_midi_note" double float float float));

(define make-note-on
  (lambda (t k v c)
    (insert-midi-note t k v c)))

(define make-note-off
  (lambda (t k c)
    (insert-midi-note t k 0.0 c)))
#|
(define now
  (foreign-lambda* double ()
     " C_return(Time::getMillisecondCounterHiRes());"))
|#



(define (make-process p num interval)
  (let ((t interval) (c 0))
    (lambda ()
      (apply p '())
      (set! c (+ c 1))
      (if (> c num)
          (set! t -1.0))
      t)))


(define (runran n d)
  (let ((r 0.0))
    (do ((i 0 (+ i 1)))
        ((> i n))
      (insert-midi-note r 60 100)
      (insert-midi-note (+ 200 r) 60  0)
      (set! r (+ r d)))))

(define (runproc k n d)
  (let ((proc (make-process
               (lambda ()
                 (insert-midi-note 0.0 k 100)
                 (insert-midi-note 90.0 k 0))
               n d)))
    (insert-process 0.0 proc)))



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

(define (mp:note time dur key amp chan)
  (make-note-on time key amp chan)
  (make-note-off (+ time dur) key chan))

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





#|
; tests
(send mp:note)
(send mp:note #:chan 2)
(send mp:note (now) 1)
(send mp:note (now) 1 #:chan 3 #:key 44)
; ERRORS
(send mp:Note 5 6)
(send mp:note 1 2 3 4 5 6)
(send mp:note 1 #:chan 2 (now) 4)
(send mp:note 1 #:key 33 #:foo 2 )
(send mp:note 1 #:key 33 #:key 2 )
|#



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
	  (error "binding clause not a list (var init [step])" 
		 (car tail))))
    (let ((now (gensym)) ; param that receives now() from C
	  (elapsed (gensym)) ; param that receives elapsed from C
	  (delta (gensym)))
      `((lambda (,@bind)
	  (lambda (,now ,elapsed)
	    (let* ((,delta 0)
		   (now (lambda () ,now))
		   (wait (lambda (n) (set! ,delta n)))
		   (elapsed (lambda () ,elapsed)))
	      (cond (,(car terminate)
		     ,@(cdr terminate)
		     -1)
		    (else
		     ,@body
		     ,@step
		     ,delta)))))
	,@init))))


(return-to-host)


#|

(define (foo )
  (go ((i 0 (+ i 1))
       (k 60 (+ 60 (random 60))))
      ((= i 10) )
    (print i)
    (wait 100)))
(insert-process 0.0 (foo))


(define (foo )
  (go ((i 0 (+ i 1))
       (k 60 (+ 60 (random 60))))
      ((= i 200) )

    (wait 100)))
(insert-process 0.0 (foo))


(Sprout (foo))
|#

;;csc -c++ -embedded -t ChickenBridge.scm
