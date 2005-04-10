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
;;; file system and OS interface.
;;;

(use-modules (oop goops))
(use-modules (ice-9 rdelim))
(use-modules (ice-9 pretty-print)) ; remove  at some point...
(use-modules (srfi srfi-1))

(define directory-delimiter #\/)

(define (cd . args)
  (let ((dir (if (null? args)
               (passwd:dir (getpw (getlogin)))
               (car args))))
    (chdir dir)
    (getcwd)))

(define (pwd )
  (getcwd))

(define (shell cmd . args)
  (system cmd))

(define (set-file-position file pos set?)
  (if (= pos 0)
    (seek file 0 SEEK_CUR)
    (if set?
      (seek file pos SEEK_SET)
      (seek file pos SEEK_CUR))))

(define (get-current-time)
  (let ((vec (localtime (current-time))))
    (vector-set! vec 5
                 (+ 1900 (vector-ref vec 5)))
    vec))

;(define-macro (time form)
;  `(let ((s (get-internal-real-time)))
;    ,form
;    (/ (- (get-internal-real-time) s) 100)))

;;;
;;;
;;;

(define (string-read str . args)
  ;; args is: start eoftok
  (let ((len (string-length str))
        (beg (if (null? args) 0 (car args)))
        (eof (if (or (null? args) (null? (cdr args)))
               ':eof
               (car (cdr args)))))
    (call-with-input-string 
     str
     (lambda (sp) ; string port
       ;; advance to starting pos
       (do ((p 0 (+ p 1)))
           ((not (< p beg)) #f)
         (read-char sp))
       (if (not (< beg len))
         (values eof 0)
         (let ((val (read sp)))
           (values (if (eof-object? val) eof val)
                   (ftell sp))))))))

(define (err msg . args)
  (let ((str (apply format #f msg args)))
    (error str)))

;;;
;;; module/symbol stuff
;;;

(define (in-package pkg)
  ;; at some point this could hook into the module system.
  #t)

(define (bound? sym)
  (module-bound? (current-module) sym))

(define (symbol-value sym)
  (module-symbol-binding (current-module) sym))

(define (symbol-function sym)
  (let ((val (symbol-value sym)))
    (if (procedure? val)
      val
      (error "not a function:" sym))))

;;;
;;; reader hackery
;;; 
;;;

(read-set! keywords 'prefix)

(define (read-macro-set! char func)
  (read-hash-extend char
                    (lambda (arg port)
                      (func (read port)))))

;;;

(define (make-equal?-hash-table  size)
  (make-hash-table size))

;;;
;;; printing hacks
;;;

(define pprint pretty-print)

;;;
;;; OOP functions
;;;

(define (find-class name . root)
  ;; returns a class given its name or #f. optional
  ;; root class defaults to <top>.
  (letrec ((fc
	    (lambda (name class)
	      (if (null? class)
		#f
		(if (pair? class)
		  (or (fc name (car class))
		      (fc name (cdr class)))
		  (if (and (slot-bound? class 'name)
			   (eq? name (class-name class)))
		    class
		    (fc name (class-direct-subclasses class))))))))
    (fc name (if (null? root) <top> (car root)))))

(define slot-definition-initform slot-definition-init-value)

(define (slot-definition-initargs slotd)
  (let* ((inits (list #f))
	 (tail inits))
    (do ((l (cdr slotd) (cddr l)))
	((null? l) (cdr inits))
      (if (eq? (car l) ':init-keyword)
	(begin (set-cdr! tail (list (cadr l)))
	       (set! tail (cdr tail)))))))

(define (finalize-class class) #t)

;;;
;;; CM OOP functions that must be defined:

(define-macro (define-class* name supers slots . options)
  `(define-class ,name ,supers ,@ (append slots options)))

(define-macro (define-method* formals . body)
  `(define-method ,formals ,@ body))

(define-macro (define-generic* formals)
  (if (pair? formals)
    `(define-generic ,(car formals))
    `(define-generic ,formals)))

(define (slot-getter-form obj slot)
  `(slot-ref ,obj ',slot))

(define (slot-setter-form obj slot val)
  `(slot-set! ,obj ',slot ,val))




