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

(in-package :cm)

(import '(ext::quit ext::exit))

(setf clos::*allow-mixing-metaclasses* T)

(defun class-subclasses (class)
  ;; CLISP's clos.lisp poses the question...
  ;;   Durch alle Symbole durchlaufen, um die Unterklassen abzugrasen.
  ;;   Sollte eleganter gehen??
  ;; to which I answer SURE. TRY IMPLEMENTING CLASS-DIRECT-SUBCLASSES
  ;; LIKE EVERY OTHER LISP.
  (let ((subclasses (list )))
    (do-symbols (sym :cm)
      (let ((c (get sym 'clos::closclass)))
	(when (and c (clos::subclassp c class)
                   (not (eq c class)))
	  (pushnew c subclasses))))
    (nreverse subclasses)))

(defun slot-definition-initargs (slot)
  (clos::slotdef-initargs slot))

(defun slod-definition-initform (slot)
  (cdr (clos::slotd-initer)))

(defun slot-definition-name (slot)
  (clos::slotdef-name slot))

(defun slod-definition-reader (slot)
  slot
  nil)

(defun class-direct-superclasses (class)
  (clos::class-direct-superclasses class))

(defun class-direct-subclasses (x)
  (declare (ignore x))
  (error "class-direct-subclasses not implemented in clisp."))

(defun class-slots (class)
  (clos::class-slots class))

(defun class-direct-slots (class)
  (clos::class-direct-slots class))

(defun generic-function-name (class)
  (error "generic-function-name not implmented in clisp."))
  
(defun finalize-class (class) (values))

(defmethod make-load-form (obj)
  (error "no make-load-form method for ~s." obj))

(setf clos::*warn-if-gf-already-called* NIL)
(setf custom:*warn-on-floating-point-contagion* nil)

;;;
;;;  misc. stuff
;;;

;(defun quit () (ext:quit))

;(defun exit () (quit))

(defun object-address (x)
  (sys::address-of x))

(defun shell (format &rest strings) 
  (ext:shell (apply #'format nil format strings)))

(defparameter *browser*
  "/Applications/Networking/Internet\\ Explorer.app"  )

(defun open-url (url &key (browser *browser*))
  (shell "open -a ~a ~a" browser url)
  (values))

(defconstant directory-delimiter #\/)

;(defun cd (&optional dir)
;  (if dir (setf (ext:default-directory) dir)
;      (ext:default-directory)))
;

(defun cd (&optional (dir (user-homedir-pathname )))
  (setf (ext:default-directory) dir))

(defun pwd ()
  (namestring (ext:default-directory)))

(defun save-cm (path &rest args)
  (declare (ignore args))
  (ext:saveinitmem path :quiet t
                   :init-function
                   #'(lambda ()
                       (declare (special *cm-readtable*))
                       (setf *package* (find-package :cm))
                       (setf *readtable* *cm-readtable*))))










