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

(import '(ext::load-foreign
          pcl:slot-definition-initargs
          pcl:slot-definition-initform
          pcl:slot-definition-name
          pcl:class-direct-slots
          pcl:class-slots
          ;pcl::class-direct-subclasses
          pcl::class-direct-superclasses
          pcl:generic-function-name
          )
	:cm)

(defun quit () (ext::quit))
(defun exit () (quit))

#+cmu19
(defun class-subclasses (c)
  (let ((subs (pcl::class-direct-subclasses c)))
    (if (null subs)
	'()
      (loop for s in subs
	append (cons s (class-subclasses s))))))
	  
#+cmu18
(defun class-subclasses (class)
  (let ((tbl (kernel:class-subclasses class))
        (sub '()))
    (maphash (lambda (k v) v (push k sub)) tbl)
    (nreverse sub)))

#-(or cmu19 cmu18)
(error "Fix class-subclasses for this version of cmu.")

;(defun make-load-form (obj)
;  (pcl::make-load-form obj))

(defun finalize-class (class) 
  ;(pcl::finalize-inheritance class)
  )

(defmethod validate-class ((class t) (superclass t))
  ;; this is a no-op except in OpenMCL 014
  t)

(defun slot-defintion-reader (slot) slot nil)

;;;
;;; misc. stuff
;;;

(defun object-address (thing)
  (kernel:get-lisp-obj-address thing))

(defconstant directory-delimiter #\/)

;(defun cd (&optional dir)
;  (if dir
;    (progn (setf (ext:default-directory) dir)
;	   (namestring (ext:default-directory)))
;    (namestring (ext:default-directory))))

(defun cd (&optional (dir (user-homedir-pathname )))
  (setf (ext:default-directory) dir)
  (namestring (ext:default-directory)))

(defun pwd ()
  (namestring (ext:default-directory)))

;;(defun shell (format &rest strings) 
;;  (let ((str (apply #'format nil format strings)))
;;    (extensions:run-program "/bin/csh" (list "-fc" str) :output t)))

(defun shell (cmd &key (wait t) (output t))
  (extensions:run-program "/bin/csh" (list "-fc" cmd)
                          :output output :wait wait))

(defun env-var (var)
  (let ((x (assoc var ext:*environment-list*
                  :test #'string=)))
    (and x (cdr x) )))

(defun set-env-var (name value)
  (let ((cell (assoc (string name) ext:*environment-list* :test #'equalp
                     :key #'string)))
    (if cell
        (setf (cdr cell) (string value))
      (push (cons (intern (string name) "KEYWORD") (string value))
	    ext:*environment-list*))))

(defun cm-image-dir ()
  (let ((img (member "-core" ext:*command-line-strings*)))
    (if img
	(namestring
	 (make-pathname
	  :directory (pathname-directory (cadr img))))
      nil)))

(defun save-cm (path &rest args)
  (declare (ignore args))
  (extensions:save-lisp path :print-herald NIL
                        :init-function
                        #'(lambda ()
                            (declare (special *cm-readtable*))
                            (setf *readtable* *cm-readtable*)
                            (setf *package* (find-package :cm))
                            (load-cminit)                            
                            (cm-logo)
                            (lisp::%top-level))))

;;; attempt thread support on x86 using cmucl's "multiprocessing"
;;; package. mp is NOT based on native threads so this is unlikely to
;;; work well. decisecond time precision is really bad too.

#+x86
(progn
(defun current-thread () mp:*current-process*)
(defun thread? (obj) (mp:processp obj))
(defun make-thread (thunk &optional name)
  (if name 
      (mp:make-process thunk :name (format nil "~a" name))
      (mp:make-process thunk)))
(defun thread-name (thread) 
  (mp:process-name thread))
;(thread-specific thread)
;(thread-specific-set! thread obj)
(defun thread-start! (thread)
  (mp:enable-process thread) )
(defun thread-yield! ()
  (mp:process-yield))
(defun thread-sleep! (timeout)
  (sleep timeout))
(defun thread-terminate! (thread)
  (mp:destroy-process thread))
;(thread-join! thread [timeout [timeout-val]])
(defun mutex? (obj)
  (typep obj 'mp:lock))
(defun make-mutex (&optional name)
  (mp:make-lock name))
(defun mutex-name (mutex)
  (slot-value mutex 'mp::name))
;(mutex-specific mutex)
;(mutex-specific-set! mutex obj)
;(mutex-state mutex)
;(mutex-lock! mutex [timeout [thread]])
;(mutex-unlock! mutex [condition-variable [timeout]])
;(condition-variable? obj)
;(make-condition-variable [name])
;(condition-variable-name condition-variable)
;(condition-variable-specific condition-variable)
;(condition-variable-specific-set! condition-variable obj)
;(condition-variable-signal! condition-variable)
;(condition-variable-broadcast! condition-variable)
(defun current-time () (get-internal-real-time))
(defun time? (obj) (and (integerp obj) (> obj 0)))
(defun time->seconds (time) 
  (/ time #.(coerce internal-time-units-per-second 'float)))
(defun seconds->time (x)
  (truncate (* time internal-time-units-per-second)))
;(current-exception-handler)
;(with-exception-handler handler thunk)
;(raise obj)
;(join-timeout-exception? obj)
;(abandoned-mutex-exception? obj)
;(terminated-thread-exception? obj)
;(uncaught-exception? obj)
;(uncaught-exception-reason exc)
)
