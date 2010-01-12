;;; **********************************************************************
;;; Copyright (C) 2008-2010 Rick Taube.
;;; This program is free software; you can redistribute it and/or modify
;;; it under the terms of the Lisp Lesser Gnu Public License. The text of
;;; this agreement is available at http://www.cliki.net/LLGPL            
;;; **********************************************************************

;; loading this file ensures implementation features that are either
;; not provided or unevenly provided in scheme implementations. see
;; readme.txt for the list of features.

(define *error-trace* #f)

(define (s7-error-hook tag args)
  ;; report scheme errors to Grace's console window in the same format
  ;; as C-side errors.
  (let ((port (open-output-string)))
    (format port ">>> Error: ")
    ;; if the error is triggered by s7 then args can be a string,
    ;; otherwise when cm triggers an error args is always a list of
    ;; args, if more than one arg then the first is a format string
    ;; and the others are args for format
    (if (pair? args)
        (if (null? (cdr args)) ;; a constant string error message
            (display (car args) port)
            (apply format port args)) ;; a format string plus args
        (display args port))
    (format port "~%")
    (if *error-trace* 
        (begin
          (format port "Error trace:~%")
          (stacktrace)
          (format port "~%")
          ))
  (let ((str (get-output-string port)))
    (close-output-port port)
    (ffi_print_error str))
  ;; +s7-error+ is a C-defined constant that Scheme returns to signal
  ;; the C side that an error has occured during evaluation
  +s7-error+
  ))

(set! *error-hook* s7-error-hook)  ; s7's error hook variable 

;; a version of (load file) that will load instrument files from the
;; embedded sources if (1) the file has no directory component, (2)
;; the file does not exist in the current working directory and (3)
;; the *load-path* variable is null

(define s7-load load)
(define load ffi_load)

(define (interaction-environment ) (global-environment))

(define-macro (define-record . args) (values)) ; records in s7Foreign

(define-macro (unless arg . body) 
  `(if (not ,arg) (begin ,@ body)))

(define-macro (when arg . body) 
  `(if ,arg (begin ,@ body)))

;; keywords

(define (string->keyword s)
  (make-keyword s))

(define (keyword->string k)
  (symbol->string (keyword->symbol k)))

(define (fixnum? x)
  (integer? x))

(define (logtest a b)
  (not (zero? (logand a b))))

;; hash tables

(define (make-equal-hash-table)
  (make-hash-table))

(define (make-eq-hash-table)
  (make-hash-table))

(define hash-set! hash-table-set!)

(define hash-ref hash-table-ref)

;; strings

(define (read-from-string str)
  (call-with-input-string str read))

;; bill sez: "sort! copies lists, but does change vectors (it's really vector-sort!
;; with list->vector and vector->list if it gets a list argument"
;; adapted for lists as well as vectors from
;; http://www.math.grin.edu/~stone/events/scheme-workshop/quicksort.html

(define sort sort!)

