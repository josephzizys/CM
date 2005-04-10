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

(define (use-package . args) #t)

(define (read-macro-set! char fn) #f)

(define pprint write)

;; File system

(define (pwd)
  (current-directory))

(define (cd . args)
  (if (null? args)
    (current-directory (home-directory))
    (current-directory (car args)))
  (pwd))

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
  (hash-table-put table key value))

(define (hash-remove! table key)
  (hash-table-delete! table key))

(define (hash-fold fn x table)
  (hash-table-fold table fn x))
    
  
;; Keywords. Gauche keywords are cltl keywords, Yay! 
;; 

(define (symbol->keyword sym)
  (make-keyword (symbol->string sym)))

(define *random-state* default-random-source)

(define (random n . args)
  (if (exact? n)
    (random-integer n)
    (if (inexact? n)
      (if (= n 1.0)
          (random-real 1.0)
          (* (random-real 1.0) n))
      (errorf "random bounds not integer or real: ~s." n))))


; API
;(make class . args)
;(initialize class inits)
;(write-object obj port)
;(class-of obj)
;(is-a? obj class)
;(slot-ref obj slot)
;(slot-set obj slot val)

; MOP
;(class-name class)
;(class-precedence-list class)
;(class-slots class)
;(class-direct-subclasses class)
;(slot-definition-name slot)
;(slot-definition-accessor slot)

;IMPLEMENT:

(define (slot-definition-initargs slot)
  (do ((opts (slot-definition-options slot) (cddr opts))
       (args (list)))
      ((null opts)
       (reverse! args))
    (if (eq? (car opts) ':init-keyword)
      (set! args (cons (cadr opts) args)))))

; (define (class-subclasses class)  #f)

;;; Gauche's write and display function call a generic function
;;; write-object when they encounter an instance they don't know how
;;; to print. You can define its method specialized to your class to
;;; customize how the instance is printed.

;;; CM OOP functions that must be provided:

(define (slot-getter-form obj slot)
  `(slot-ref ,obj ',slot))

(define (slot-setter-form obj slot val)
  `(slot-set! ,obj ',slot ,val))

(define-macro (define-generic* . args)
  `(define-generic ,(car args)))

;; for Gauche define-class* will have set the class' name after the
;; class is created, ie
;; (begin (define-class <foo> ... :name 'foo) 
;;        (slot-set! <foo> 'name 'foo))

(define-macro (define-class* class supers slots . options)
 `(define-class ,class ,supers ,slots))

(define-macro (define-method* formals . body)
  `(define-method ,formals ,@body))

