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

(pushnew ':metaclasses *features*)

(import '(clos:slot-definition-name 
          clos:slot-definition-initargs 
          clos:slot-definition-initform 
          clos:class-direct-superclasses
          clos:class-direct-subclasses
          hcl:class-slots
          hcl:class-direct-slots
          hcl:validate-superclass
          ))

;; pkg.lisp blocked these symbols so CM does not inherit Lispworks
;; classes RANDOM and FUNCALL. THere must be a better way to do
;; this...

(defun random (ub &optional (state *random-state*))
  (cl:random ub state))

(defun funcall (fn &rest args) (apply #'cl:funcall fn args))

(defun finalize-class (class) class (values))

(defun shell (cmd &key (output t) (wait t))
  (if output
    (sys:call-system-showing-output cmd :wait wait)
    (sys:call-system cmd :wait wait)))

(defun quit () (lw:quit))

(defun exit () (quit))

(defun cd (&optional (dir (user-homedir-pathname )))
  (hcl:change-directory dir))

(defun pwd ()
  (hcl:get-working-directory))

(defun env-var (var)
  (hcl:getenv var))

(defun cm-image-dir ()
  ;; system:*line-arguments-list*
  (pathname-directory (lw:lisp-image-name)))

#+lispworks-personal-edition
(defun save-image (&rest args)
  args
  (error "Lispworks Personal Edition does not support save-image."))

#-lispworks-personal-edition
(defun save-cm (path &rest args)
  path args
  (hcl:save-image path 
                  :restart-function
                  #'(lambda ()
                      (declare (special *cm-readtable*))
                      (setf *package* (find-package :cm))
                      (setf *readtable* *cm-readtable*)
                      (load-cminit)
                      (cm-logo))))


