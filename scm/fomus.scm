;;; **********************************************************************
;;; Copyright (C) 2009, Rick Taube and David Psenicka
;;; This program is free software; you can redistribute it and/or modify
;;; it under the terms of the Lisp Lesser Gnu Public License. The text of
;;; this agreement is available at http://www.cliki.net/LLGPL            
;;; **********************************************************************

;; the following FFI function are defined (see CmSupport.cpp, genffi.scm)
;;    (ffi_fms_init )
;;    (ffi_fms_new  )
;;    (ffi_fms_free )
;;    (ffi_fms_clear )
;;    (ffi_fms_ival int int int)
;;    (ffi_fms_rval int int int int)
;;    (ffi_fms_mval int int int int int)
;;    (ffi_fms_fval int int double)
;;    (ffi_fms_sval int int c-string)
;;    (ffi_fms_act  int int)
;;    (ffi_fms_load c-string)
;;    (ffi_fms_run )
;;    (ffi_fms_xml  c-string)

(define (fms:writeXml port expect tag  val)
  (display "<" port)
  (display tag port)
  (display ">" port)
  (cond ((and (number? val) (eq? expect 'number))
	 (write val port))
	((and (symbol? val) (eq? expect 'string))
	 (write val port))
	((and (string? val) (eq? expect 'string))
	 (display val port))
	((list? val)
	 (do ((tail val (cdr tail))
	      (delim #f #t))
	     ((null? tail)
	      #f)
	   (if delim (display " " port))
	   (display (car tail) port)))
	((and (boolean? val) (eq? expect 'boolean))
	 (display (if val "true" "false") port))
	(else
	 (let ((msg (format #f "~A: expected ~A but got" 
			    tag expect)))
	   (error msg val))))
  (display "</" port)
  (display tag port)
  (display ">" port))

;;;
;;; user functions
;;;

; (fms:note 0 1 60 :marks '(staccato fff))

;; time, dur, note and dyn are numbers (any type)
;; part is a symbol or string.
;; grtime is grace-note time (any type of number) or false
;; voice an integer or a list (it has to allow a list)
;; marks is like the old marks list ("accent" ("text" "arco")) 
;; settings lists are just like marks lists. 

(define (fms:note . args) 
  (with-optkeys (args time dur note (part "default") (voice 1) (dyn 0)
		      grtime (marks '()) (settings '()))
    (let ((port (open-output-string)))
      (display "<fms:note>" port)
      (fms:writeXml port 'number "time" time )
      (fms:writeXml port 'number "dur" dur )
      (fms:writeXml port 'number "note" note )
      (if part (fms:writeXml port 'string "part" part ))
      (if (list? voice)
	  (fms:writeXml port 'list "voices" voice )
	  (if voice (fms:writeXml port 'number "voice" voice )))
      (if dyn (fms:writeXml port 'number "dyn" dyn))
      (if grtime (fms:writeXml port 'number "grtime" grtime))
      (cond ((pair? marks)
	     (display "<marks>" port)
	     (do ((tail marks (cdr tail)))
		 ((null? tail) #f)
	       (fms:writeXml port (if (list? (car tail)) 'list
				      'string)
			     "mark"
			     (car tail)))
	     (display "</marks>" port))
	    ((not (null? marks))
	     (error "Marks: expected a list but got" marks)))
      (cond ((pair? settings)
	     (display "<settings>" port)
	     (do ((tail settings (cdr tail)))
		 ((null? tail) #f)
	       (fms:writeXml port (if (list? (car tail)) 'list
				      'string)
			     "setting"
			     (car tail)))
	     (display "</settings>" port))
	    ((not (null? settings))
	     (error "Settings: expected a list but got" settings)))
      (display "</fms:note>" port)
      (ffi_fms_xml (get-output-string port))
      (void))))

(define (fms:rest . args) 
  (with-optkeys (args time dur note (part "default") (voice 1)
		      grtime (marks '()) (settings '()))
    (void)))

(define (fms:mark . args) 
  (with-optkeys (args time dur note (part "default") (voice 1)
		      grtime (marks '()) (settings '()))
    (void)))

(define (fms:meas time dur . keyargs)
  (void))

(define (fms:measattr . keyargs)
  (void))

(define (fms:part . keyargs)
  (void))

(define (fms:metapart . keyargs)
  (void))

(define (fms:partsref . keyargs)
  (void))

(define (fms:inst . keyargs)
  (void))

(define (fms:percinst . keyargs)
  (void))

(define (fms:setting id value . appnd)
  (void))

;;
;; score messages
;;

(define (fms:load arg)
  (void))

(define (fms:newscore name . filename)
  (void))

(define (fms:clearscore)
  (void))

(define (fms:deletescore)
  (void))

;;
;; send
;;




