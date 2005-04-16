;;; **********************************************************************
;;; Copyright (C) 2002 Heinrich Taube (taube@uiuc.edu) 
;;; This program is free software; you can redistribute it and/or
;;; modify it under the terms of the GNU General Public License
;;; as published by the Free Software Foundation; either version 2
;;; of the License, or (at your option) any later version.
;;; This program is distributed in the hope that it will be useful,
;;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;;; GNU General Public License for more details.
;;; **********************************************************************

;;; $Name$
;;; $Revision$
;;; $Date$

;;;
;;; an -- as yet incomplete -- port of CM to Gauche Scheme:
;;; http://www.shiro.dreamhost.com/scheme/gauche/index.html
;;;

(use srfi-1)     ; list library
(use srfi-27)    ; random bits
(use file.util)  ; current-directory, home-directory

;; Lisp environment

(define (lisp-version )
  (string-append "Gauche " (gauche-version)))

(define quit exit)  

(define err errorf)

(define (i-package name) #t)

(define (read-macro-set! char fn) #f)

(define pprint write)

;; Directories, files and ports

(define (pwd)
  (current-directory))

(define (cd . args)
  (if (null? args)
    (current-directory (home-directory))
    (current-directory (car args)))
  (pwd))

(define (set-file-position fil pos set?)
  (if (= pos 0)
    (port-seek fil 0 SEEK_CUR) ; return the current position
    (if set?
      (port-seek fil pos SEEK_SET)
      (port-seek fil pos SEEK_CUR))))

(define (delete-file f)  (sys-unlink f))

;; System calls

(define (shell . args)
  (sys-system (car args)))

(define (get-current-time)
  (let ((now (sys-localtime (sys-gettimeofday))))
    (vector (slot-ref now 'sec)
            (slot-ref now 'min)
            (slot-ref now 'hour)
            (slot-ref now 'mday)
            (slot-ref now 'mon)
            (+ 1900 (slot-ref now 'year)))))

;;; Hashtables

(define (make-equal?-hash-table size)
  (make-hash-table 'equal?))

(define (hash-ref table key)
  (hash-table-get table key #f))

(define (hash-set! table key value)
  (hash-table-put! table key value))

(define (hash-remove! table key)
  (hash-table-delete! table key))

(define (hash-fold fn x table)
  (hash-table-fold table fn x))    
  
;;; Strings

(define (string-downcase str)
  (let* ((len (string-length str))
         (new (make-string len)))
    (do ((i 0 (+ i 1)))
        ((= i len) new)
      (string-set! new i (char-downcase (string-ref str i))))))

;;; Keywords. Gauche keywords are cltl keywords, Yay! 

(define (symbol->keyword sym)
  (make-keyword (symbol->string sym)))

;; numbers

(define most-positive-fixnum (- (expt 2 29) 1))

(define most-negative-fixnum (- (expt 2 29)))

(define *random-state* default-random-source)

(define (random n . args)
  (if (exact? n)
    (random-integer n)
    (if (inexact? n)
      (if (= n 1.0)
          (random-real)
          (* (random-real) n))
      (errorf "random bounds not integer or real: ~s." n))))

;                                   Chicken Gauche  Guile  Stklos
;(make class . args)                        y       y       
;(initialize class inits)                   y       y
;(class-of obj)                             y       y       y
;(is-a? obj class)                          y       y       y
;(slot-ref obj slot)                        y       y       y
;(slot-set obj slot val)                    y       y       y
;(class-name class)                         y       y       y
;(class-slots class)                        y       y
;(class-direct-subclasses class)            y       y
;(find-class name)                          n       n       y
;(slot-definition-name slot)                y       y

;ALL SCHEME MUST ALSO IMPLEMENT THESE CLOS METHODS:

;(slot-definition-initargs slot) 
;(slot-definition-initform slot) 
;(class-subclasses class) 

;AND THESE EXPANSIONS FOR CM:
;(slot-getter-form obj slot)
;(slot-setter-form obj slot val)

;;; Gauche's write and display function call a generic function
;;; write-object when they encounter an instance they don't know how
;;; to print. You can define its method specialized to your class to
;;; customize how the instance is printed.

(define-macro (define-generic* . args)
  `(define-generic ,(car args)))

;;; Gauche methods are like Guile methods, inclusing next-

(define-macro (define-method* formals . body)
  `(define-method ,(car formals) ,(cdr formals) ,@body))

;;; define-class* expansion for Gauche.
;;; Gauche macroexpands define-class into a really hairy expr.  rather
;;; than try to figure out how to work with it, the macro expansion of
;;; define-class* will simply set! the class name after the class has
;;; been defined, ie  (define-class* <foo> ... :name 'foo) becomes:

;;; (begin (define-class <foo> ...)
;;;        (slot-set! <foo> 'name 'foo))
;;; The superclass list for Gauche define-class are variables, not
;;; names.

(define (make-instance class . inits)
  (apply make class inits))

(define *named-classes* (make-hash-table 'eq?))

(define-macro (define-class* class supers slots . options)
  (let ((cname #f)
        (metac #f)
        (csets (list)))
    (do ((tail options (cddr tail)))
        ((null? tail) #f)
      (case (car tail)
        ((:name) (set! cname (cadr tail)))
        ((:metaclass) (set! metac (cadr tail)))
        ((:file-types )
         (set! csets (cons* `(slot-set! ,class 'handles ,(cadr tail)) csets)))
        ((:output-hook)
         (set! csets (cons* `(slot-set! ,class 'output-hook ,(cadr tail)) csets)))
        ((:definer)
         (set! csets (cons* `(slot-set! ,class 'definer ,(cadr tail)) csets)))
        ((:versions)
         (set! csets (cons* `(slot-set! ,class 'versions ,(cadr tail)) csets)))
        ))
    `(begin
      (define-class ,class ,supers ,slots
                    ,@ (if metac (list :metaclass metac) (list)))
      (slot-set! ,class 'name ,cname)
      ;; add named class to the table
      (hash-table-put! *named-classes* ,cname ,class)
      ;; set slots from metaclass
      ,@csets)))
      
(define (find-class name . args)
  (hash-table-get *named-classes* name #f))

;(define (class-subclasses cls)
;  (let ((subs (class-direct-subclasses cls)))
;    (append subs
;            (loop for s in (class-direct-subclasses cls)
;                  append (class-subclasses s)))))

(define (class-subclasses cls)
  (let ((subs (class-direct-subclasses cls)))
    (do ((tail subs (cdr tail)))
        ((null? tail) subs)
      (set! subs (append subs (class-subclasses (car tail)))))))

;;; implement clos slot mop accessors

(define (slot-definition-initargs slot)
  (do ((opts (slot-definition-options slot) (cddr opts))
       (args (list)))
      ((null? opts)
       (reverse! args))
    (if (eq? (car opts) ':init-keyword)
      (set! args (cons (cadr opts) args)))))

(define (slot-definition-initform slot)
  (list-prop (slot-definition-options slot) ':init-value))

; (define-class* <foo> () ((a :init-value 1)) :name 'foo)
; (find-class 'foo)
; (make <foo>)
; (class-name <foo>)
;; test if supers list holds names or variables:
;      (define-class <bar> (freddy) ((b :init-value 2)))
; (define-class <bar> (<foo>) ((b :init-value 2)))
; (describe <bar>)
; (describe (make <bar>))

; (define-class* <foo> () ((a :init-value 1 :init-keyword :a :accessor foo-a)) :name 'foo)
; (define-class* <bar> (<foo>) ((b :init-value 2 :init-keyword :b :accessor bar-b) (c :init-value 3 :accessor bar-c :init-keyword :c :init-keyword :cc)) :name 'bar)
; (find-class 'foo)
; (find-class 'bar)
; (class-direct-subclasses (find-class 'foo))
; (class-slots <bar>)
; (define sd (find (lambda (x) (eq? 'c (slot-definition-name x) )) (class-slots <bar>)))
; (apropos 'slot-definition)
; (slot-definition-initargs sd)
; (slot-definition-initform sd)

;;; CM functions for expanding slot access in write-event methods.

(define (slot-getter-form obj slot)
  `(slot-ref ,obj ',slot))

(define (slot-setter-form obj slot val)
  `(slot-set! ,obj ',slot ,val))


