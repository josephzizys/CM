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

(import '(sb-ext::load-foreign
          sb-pcl:slot-definition-initargs
          sb-pcl:slot-definition-initform
          sb-pcl:slot-definition-name
          sb-pcl:class-direct-slots
          sb-pcl:class-slots
          sb-pcl:class-direct-superclasses
          sb-pcl:generic-function-name
          )
        :cm)

(defun quit () (sb-ext:quit))
(defun exit () (quit))

(defun class-subclasses (c)
  (let ((subs (sb-pcl:class-direct-subclasses c)))
    (if (null subs)
	'()
      (loop for s in subs
	append (cons s (class-subclasses s))))))
	  
(defun finalize-class (class) 
  (sb-pcl:finalize-inheritance class))

(defmethod validate-class ((class t) (superclass t))
  ;; this is a no-op except in OpenMCL 014
  t)

(defun slot-defintion-reader (slot) slot nil)

;;;
;;; misc. stuff
;;;

(defun arglist (function)
  (sb-kernel:%simple-fun-arglist function))

(defun object-address (thing)
  (sb-kernel:get-lisp-obj-address thing))

(defconstant directory-delimiter #\/)

(defun shell (format &rest strings) 
  (let ((str (apply #'format nil format strings)))
    (sb-ext:run-program "/bin/csh" (list "-fc" str) :output t)))

(defun cd (&optional (dir (user-homedir-pathname )))
  ;(setf (ext:default-directory) dir)
  ;(namestring (ext:default-directory))
  )

(defun pwd ()
  ;(sb-ext:run-program "/bin/pwd" nil :output t)
  )

(defun env-var (var)
  ;(let ((x (assoc var ext:*environment-list*
  ;                  :test #'string=)))
  ;  (and x (cdr x) ))
  )

(defun cm-image-dir ()
  (let ((img (second (member "--core" sb-ext:*posix-argv*
                             :test #'string=))))
    (if img
      (namestring
       (make-pathname :directory (pathname-directory img)))
      nil)))

(defun save-cm (pathname &rest args)
  (declare (ignore args))
  (sb-ext:save-lisp-and-die (namestring pathname)
                            :toplevel
                            #'(lambda ()
                                (declare (special *cm-readtable*))
                                (setf *readtable* *cm-readtable*)
                                (setf *package* (find-package :cm))
                                (load-cminit)                            
                                (cm-logo)
                                (sb-impl::toplevel-init)
                                )))