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
  (system (apply format #f cmd args)))

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

;(defmacro time (form)
;  `(let ((s (get-internal-real-time)))
;    ,form
;    (/ (- (get-internal-real-time) s) 100)))

;;;
;;;
;;;

(use-modules (oop goops))
(use-modules (ice-9 rdelim))
(use-modules (ice-9 pretty-print)) ; remove  at some point...

(define pprint pretty-print)

(define (read-from-string str)
  (call-with-input-string str read))

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

