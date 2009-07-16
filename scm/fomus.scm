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
;;    (ffi_fms_ival int int long)
;;    (ffi_fms_rval int int long long)
;;    (ffi_fms_mval int int long long long)
;;    (ffi_fms_fval int int double)
;;    (ffi_fms_sval int int c-string)
;;    (ffi_fms_act  int int)
;;    (ffi_fms_load c-string)
;;    (ffi_fms_run )
;;    (ffi_fms_xml  c-string)

(define (fms:open-score scorename . args)
  ;; bundle up user args and pass to fomus?
  (do ((tail args (cdr tail))
       (scoreargs "")
       (delimiter "" " "))
      ((null? tail)
       (ffi_fms_open_score scorename scoreargs))
    (set! scoreargs (string-append scoreargs delimiter
				   (format #f "~S" (car tail)))))
  )

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
                        (else (let ((msg (format #f "~A: invalid value" tag val))) (error msg val)))))))
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
  (set! time (+ time (ffi_sched_score_time))) 
  (fms:writeXml port "time" time)
  (fms:writeXml port "dur" dur)
  (if part (fms:writeXml port "part" part))
  (if voice (fms:writeXml port "voice" voice))
  (if grtime (fms:writeXml port "grtime" grtime))
  (if marks (fms:writeXml port "marks" marks))
  (if sets (fms:writeXml port "sets" sets)) 
  (get-output-string port))

;; these functions should get called from cm's `new' 
(define (fms:note time dur note . args) 
  (with-optkeys (args (part #f) (voice 1) (dyn 0) grtime (marks '()) (sets '()))
                (let ((port (open-output-string)))
                  (display "<note>" port)
                  (fms:writeXml port "note" note )
                  (if dyn (fms:writeXml port "dyn" dyn))
                  (fms:entry port time dur part voice grtime marks sets)
                  (display "</note>" port)
                  (ffi_fms_xml (get-output-string port))
                  (void))))

(define (fms:rest time dur . args) 
  (with-optkeys (args (part #f) (voice 1) grtime (marks '()) (sets '()))
                (let ((port (open-output-string)))
                  (display "<rest>" port)
                  (fms:entry port time dur part voice grtime marks sets)
                  (display "</rest>" port)
                  (ffi_fms_xml (get-output-string port))
                  (void))))

(define (fms:mark time dur . args) 
  (with-optkeys (args (part #f) (voice 1) grtime (marks '()) (sets '()))
                (let ((port (open-output-string)))
                  (display "<mark>" port)
                  (fms:entry port time dur part voice grtime marks sets)
                  (display "</mark>" port)
                  (ffi_fms_xml (get-output-string port))
                  (void))))

(define (fms:meas time dur . sets)
  (let ((port (open-output-string)))
    (display "<meas>" port) ; fms- XML tags are top level
    (fms:writeXml port "time" time)
    (if dur (fms:writeXml port "dur" dur))
    (fms:writeXml port "sets" sets)
    (display "</meas>" port)
    (ffi_fms_xml (get-output-string port))
    (void)))

(define (fms:measdef . sets)
  (let ((port (open-output-string)))
    (display "<measdef>" port)
    (fms:writeXml port #f sets)
    (display "</measdef>" port)
    (ffi_fms_xml (get-output-string port))
    (void)))

(define (fms:part . sets)
  (let ((port (open-output-string)))
    (display "<part>" port)
    (fms:writeXml port #f sets)
    (display "</part>" port)
    (ffi_fms_xml (get-output-string port))
    (void)))

(define (fms:metapart . sets)
  (let ((port (open-output-string)))
    (display "<metapart>" port)
    (fms:writeXml port #f sets)
    (display "</metapart>" port)
    (ffi_fms_xml (get-output-string port))
    (void)))

(define (fms:partsref . sets)
  (let ((port (open-output-string)))
    (display "<partsref>" port)
    (fms:writeXml port #f sets)
    (display "</partsref>" port)
    (ffi_fms_xml (get-output-string port))
    (void)))

(define (fms:inst . sets)
  (let ((port (open-output-string)))
    (display "<inst>" port)
    (fms:writeXml port #f sets)
    (display "</inst>" port)
    (ffi_fms_xml (get-output-string port))
    (void)))

(define (fms:percinst . sets)
  (let ((port (open-output-string)))
    (display "<percinst>" port)
    (fms:writeXml port #f sets)
    (display "</percinst>" port)
    (ffi_fms_xml (get-output-string port))
    (void)))

(define (fms:setting id value . appnd)
  (let ((port (open-output-string)))
    (display "<set>" port)
    (fms:writeXml port "sets" (list id value))
    (if (pair? appnd) (fms:writeXml port "app" (car appnd)))
    (display "</set>" port)
    (ffi_fms_xml (get-output-string port))
    (void)))

;; these are meant to go inside a "parent" definition (or `' call)
;; they are just quoted and converted to XML for the C code to parse
;; (define (fms:measattr . sets) (cons 'measattr sets))
;; (define (fms:part . sets) (cons 'part sets))
;; (define (fms:metapart . sets) (cons 'metapart sets))
;; (define (fms:partsref . sets) (cons 'partsref sets))
;; (define (fms:inst . sets) (cons 'inst sets))
;; (define (fms:percinst . sets) (cons 'percinst sets))
;; (define (fms:partmap . sets) (cons 'partmap sets))
;; (define (fms:clef . sets) (cons 'clef sets))
;; (define (fms:staff . sets) (cons 'staff sets))
;; (define (fms:import . sets) (cons 'import sets))
;; (define (fms:export . sets) (cons 'export sets))

;;
;; score messages
;;

(define (fms:load arg)
  (ffi_fms_load arg)
  (void))

;; (define (fms:newscore name . filename)
(define (fms:newscore)
  (ffi_fms_new)
  (void))

(define (fms:clearscore)
  (ffi_fms_clear)
  (void))

(define (fms:deletescore)
  (ffi_fms_free)
  (void))

;; test

;; (fms:part :id "asdf")
;; (fms:meas 2.0 2.0)
;; (fms:note 1.5 1.5 60)

;; (fms:note 3 1.5 1.5)

;; (fms:part :id "1" :inst "piano")
;; (fms:note 0.333333 0.333333 60)
;; (fms:note 0.666667 0.333333 61)
