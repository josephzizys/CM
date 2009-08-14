;;; **********************************************************************
;;; Copyright (C) 2009, Rick Taube and David Psenicka
;;; This program is free software; you can redistribute it and/or modify
;;; it under the terms of the Lisp Lesser Gnu Public License. The text of
;;; this agreement is available at http://www.cliki.net/LLGPL            
;;; **********************************************************************

;; slow, but since we're parsing XML it doesn't matter
;; should be accurate w/ any floating point precision
(define (fms:toFloatHex a)
  (if (zero? a) "0x0p0"
      (let ((x (abs a)) (e 0) (f "p"))
        (do () ((= x (truncate x))) (set! x (* x 2)) (set! e (- e 1))) ; move the point until we have an integer
        (set! x (truncate x))
        (do () ((odd? x)) (set! x (quotient x 2)) (set! e (+ e 1)))
        (do () ((= x 0))
          (set! f (string-append (string (string-ref "0123456789abcdef" (modulo x 16))) f))
          (set! x (quotient x 16)))
        (string-append (if (negative? a) "-0x" "0x") f (number->string e)))))

;; (fms:toFloatHex 0)
;; (fms:toFloatHex 1)
;; (fms:toFloatHex 2)
;; (fms:toFloatHex 3)
;; (fms:toFloatHex 4)
;; (fms:toFloatHex 0.5)
;; (fms:toFloatHex 1.5)
;; (fms:toFloatHex 100.0)
;; (fms:toFloatHex -100.0)
;; (fms:toFloatHex 0.3)

(define (fms:toXmlString str)
  (let ((end (string-length str)))
    (letrec ((aux (lambda (pos)
                    (if (< pos end)
                        (string-append
                         (let ((c (string-ref str pos)))
                           (case c
                             ((#\&) "&amp;")
                             ((#\') "&apos;")
                             ((#\") "&quot;")
                             ((#\>) "&gt;")
                             ((#\<) "&lt;")        
                             (else (string c))))
                         (aux (+ pos 1)))
                        ""))))
      (aux 0))))

(define (fms:writeXml port tag val)
  (letrec ((aux (lambda (val)
                  (cond ((integer? val) (display "<i>" port) (write val port) (display "</i>" port))
                        ((rational? val)
                         (display "<r><n>" port)
                         (write (numerator val) port)
                         (display "</n><d>" port)
                         (write (denominator val) port)
                         (display "</d></r>" port))
                        ((real? val) (display "<f>" port) (display (fms:toFloatHex val) port) (display "</f>" port))
                        ((symbol? val) (display "<s>" port) (display (fms:toXmlString (symbol->string val)) port) (display "</s>" port))
                        ((string? val) (display "<s>" port) (display (fms:toXmlString val) port) (display "</s>" port))
                        ((list? val)
                         (display "<l>" port)
                         (do ((tail val (cdr tail)))
                             ((null? tail)) 
                           (aux (car tail)))
                         (display "</l>" port))
                        ((boolean? val) (display "<b>" port) (display (if val "true" "false") port) (display "</b>" port))
                        (else
			 (error "~S is not valid input to Fomus"  val))))))
    (if tag (begin (display "<" port) (display tag port) (display ">" port)))
    (aux val)
    (if tag (begin (display "</" port) (display tag port) (display ">" port)))))

;;;
;;; user functions
;;;

;; (fms:note 0 1 60 :marks '(staccato fff))

;; time, dur, note and dyn are numbers (any type)
;; part is a symbol or string.
;; grtime is grace-note time (any type of number) or false
;; voice an integer or a list (it has to allow a list)
;; marks is like the old marks list ("accent" ("text" "arco")) 
;; settings lists are just like marks lists. 

(define (fms:entry port time dur part voice grtime marks sets)
  ;; if we are being called inside a running process then time 0 is
  ;; relative to the start of the process. in this case we take the
  ;; note's time value to be an 'ahead' factor that we must increment
  ;; by the actual current score time. otherwise (i.e. we are not
  ;; being called under a process but rather sending notes 'by hand'
  ;; in the repl) we take the time stamp to be the absolute score time
  ;; for the event.  ffi_sched_score_time returns 0 if not called
  ;; under a running process
  ;;(set! time (+ time (ffi_sched_score_time))) 
  (fms:writeXml port "time" time)
  (fms:writeXml port "dur" dur)
  (if part (fms:writeXml port "part" (format #f "~A" part)))
  (if voice (fms:writeXml port "voice" voice))
  (if grtime (fms:writeXml port "grtime" grtime))
  (if marks (fms:writeXml port "marks" marks))
  (if sets (fms:writeXml port "sets" sets)) 
  ;;(get-output-string port)
  )

;; these functions should get called from cm's `new' 
(define (fms:note . args) 
  (with-optkeys (args (time 0) dur pitch (part #f) (voice 1) (dyn 0) grtime (marks '()) (sets '()) &allow-other-keys)
                (let ((port (open-output-string)))
                  (display "<note>" port)
                  (fms:writeXml port "pitch" pitch )
                  (if dyn (fms:writeXml port "dyn" dyn))
                  (fms:entry port time dur part voice grtime marks (append sets &allow-other-keys))
                  (display "</note>" port)
                  (ffi_fms_xml (get-output-string port))
		  (close-output-port port)
                  #t)))

(define (fms:rest . args) 
  (with-optkeys (args (time 0) dur (part #f) (voice 1) grtime (marks '()) (sets '()) &allow-other-keys)
                (let ((port (open-output-string)))
                  (display "<rest>" port)
                  (fms:entry port time dur part voice grtime marks (append sets &allow-other-keys))
                  (display "</rest>" port)
                  (ffi_fms_xml (get-output-string port))
		  (close-output-port port)
                  #t)))

(define (fms:mark . args) 
  (with-optkeys (args (time 0) dur (part #f) (voice 1) grtime (marks '()) (sets '()) &allow-other-keys)
                (let ((port (open-output-string)))
                  (display "<mark>" port)
                  (fms:entry port time dur part voice grtime marks (append sets &allow-other-keys))
                  (display "</mark>" port)
                  (ffi_fms_xml (get-output-string port))
		  (close-output-port port)
                  #t)))

(define (fms:meas-aux args)
  (with-optkeys (args (time 0) dur (sets '()) &allow-other-keys)
		(let ((port (open-output-string)))
		  (display "<meas>" port) ; fms- XML tags are top level
		  (fms:writeXml port "time" time)
		  (if dur (fms:writeXml port "dur" dur))
		  (fms:writeXml port "sets" (append sets &allow-other-keys))
		  (display "</meas>" port)
		  (let ((text (get-output-string port)))
		    (close-output-port port)
		    text))))

(define (fms:meas . args)
  (ffi_fms_xml (fms:meas-aux args))
  #t)

(define (fms:measdef-aux args)
  (with-optkeys (args (sets '()) &allow-other-keys)
		(let ((port (open-output-string)))
		  (display "<measdef>" port)
		  (fms:writeXml port #f (append sets &allow-other-keys))
		  (display "</measdef>" port)
		  (let ((text (get-output-string port)))
		    (close-output-port port)
		    text))))

(define (fms:measdef . args)
  (ffi_fms_xml (fms:measdef-aux args))
  #t)

(define (fms:part-aux args)
  (with-optkeys (args (sets '()) &allow-other-keys)
		(let ((port (open-output-string)))
		  (display "<part>" port)
		  (fms:writeXml port #f (append sets &allow-other-keys))
		  (display "</part>" port)
		  (let ((text (get-output-string port)))
		    (close-output-port port)
		    text))))

(define (fms:part . args)
  (ffi_fms_xml (fms:part-aux args))
  #t)

(define (fms:metapart-aux args)
  (with-optkeys (args (sets '()) &allow-other-keys)
		(let ((port (open-output-string)))
		  (display "<metapart>" port)
		  (fms:writeXml port #f (append sets &allow-other-keys))
		  (display "</metapart>" port)
		  (let ((text (get-output-string port)))
		    (close-output-port port)
		    text))))

(define (fms:metapart . args)
  (ffi_fms_xml (fms:metapart-aux args))
  #t)

(define (fms:inst-aux args)
  (with-optkeys (args (sets '()) &allow-other-keys)
		(let ((port (open-output-string)))
		  (display "<inst>" port)
		  (fms:writeXml port #f (append sets &allow-other-keys))
		  (display "</inst>" port)
		  (let ((text (get-output-string port)))
		    (close-output-port port)
		    text))))

(define (fms:inst . args)
  (ffi_fms_xml (fms:inst-aux args))
  #t)

(define (fms:percinst-aux args)
  (with-optkeys (args (sets '()) &allow-other-keys)
		(let ((port (open-output-string)))
		  (display "<percinst>" port)
		  (fms:writeXml port #f (append sets &allow-other-keys))
		  (display "</percinst>" port)
		  (let ((text (get-output-string port)))
		    (close-output-port port)
		    text))))

(define (fms:percinst . args)
  (ffi_fms_xml (fms:percinst-aux args))
  #t)

(define (fms:setting-aux sets)
  (let ((port (open-output-string)))
    (display "<set>" port)
    (fms:writeXml port #f sets)
    ;;(if apnd (display "<app/>" port))
    (display "</set>" port)
    (let ((text (get-output-string port)))
      (close-output-port port)
      text)))

(define (fms:setting . sets)
  (ffi_fms_xml (fms:setting-aux sets))
  #t)

;;
;; score messages
;;

(define (fms:load-score filename)
  (ffi_fms_load filename)
  #t)

(define (fms:new-score filename)
  (ffi_fms_new filename)
  #t)

(define (fms:select-score filename)
  (ffi_fms_select filename)
  #t)

(define (fms:clear-score)
  (ffi_fms_clear)
  #t)

(define (fms:run)
  (ffi_fms_run)
  #t)

(define (fms:save-score filename)
  (ffi_fms_save filename)
  #t)

(define (fms:delete-score)
  (ffi_fms_free)
  #t)

(define (fms:open-score scorename . args)
  
  (define (argl->xml argn argl func nlsts)
    (if (not (pair? argl))
	(error "~S is not a ~A list" argl argn))
    (if nlsts
	(do ((tail argl (cdr tail))
	     (xml "" )
	     (delim "" " "))
	    ((null? tail) xml)
	  (if (not (pair? (car tail)))
	      (error "~S is not a list" (car tail)))
	  (set! xml (string-append xml delim (format #f "~S" (func (car tail))))))
	(format #f "~S" (func argl))))
  
  (do ((tail args)
       (save args)
       (argstr #f)
       (scoreargs "")
       (delimiter "" " "))
      ((null? tail)
       (if (!= (ffi_fms_open_score scorename scoreargs) 0)
	   (error "invalid score argument(s) in ~S" args)
	   #t)
       )
    (cond ((eq? (car tail) #:parts)
	   (if (null? (cdr tail)) (error "missing parts in ~S" args))
	   (set! argstr (argl->xml #:parts (cadr tail) fms:part-aux #t))
	   (set! tail (cddr tail)))
	  ((eq? (car tail) #:metaparts)
	   (if (null? (cdr tail)) (error "missing metaparts in ~S" args))
	   (set! argstr (argl->xml #:metaparts (cadr tail) fms:metapart-aux #t))
	   (set! tail (cddr tail)))
	  ((eq? (car tail) #:insts)
	   (if (null? (cdr tail)) (error "missing insts in ~S" args))
	   (set! argstr (argl->xml #:insts (cadr tail) fms:inst-aux #t))
	   (set! tail (cddr tail)))
	  ((eq? (car tail) #:percinsts)
	   (if (null? (cdr tail)) (error "missing percinsts in ~S" args))
	   (set! argstr (argl->xml #:percinsts (cadr tail) fms:percinst-aux #t))
	   (set! tail (cddr tail)))
	  ((eq? (car tail) #:measdefs)
	   (if (null? (cdr tail)) (error "missing measdefs in ~S" args))
	   (set! argstr (argl->xml #:measdefs (cadr tail) fms:measdef-aux #t))
	   (set! tail (cddr tail)))
	  ((eq? (car tail) #:settings)
	   (if (null? (cdr tail)) (error "missing settings in ~S" args))
	   (set! argstr (argl->xml #:settings (cadr tail) fms:setting-aux #f))
	   (set! tail (cddr tail)))
	  ((member (car tail) '(#:clear #:new #:run #t #f))
	   (set! argstr (format #f "~S" (car tail)))
	   (set! tail (cdr tail)))
	  (else
	   (set! argstr ":err")
	   (set! tail (cdr tail)))
	  )
    (set! scoreargs (string-append scoreargs delimiter argstr))
    ))
