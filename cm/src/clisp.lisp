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

(pushnew :metaclasses *features*)

(import '(clos::class-direct-subclasses
          clos::class-direct-superclasses
          clos::class-direct-slots
          clos:slot-definition-initargs
          clos:slot-definition-initform
          clos:slot-definition-name
          clos:class-slots
          clos:generic-function-name
          ))

(defun exit () (ext::exit))
(defun quit () (exit))
(defun lisp-version ()
  (let* ((s (lisp-implementation-version))
         (p (position-if #'digit-char-p s)))
    (concatenate 'string "CLISP "
                 (subseq s p (position #\space s :start p)))))

(setf clos::*allow-mixing-metaclasses* T)

;(defun slot-definition-initargs (slot)
;  (clos::slotdef-initargs slot))
;
;(defun slot-definition-initform (slot)
;  (cdr (clos::slotdef-initer slot)))
;
;(defun slot-definition-name (slot)
;  (clos::slotdef-name slot))
;
;(defun slod-definition-reader (slot)
;  slot
;  nil)
;
;(defun class-slots (class)
;  (clos::class-slots class))
;
;(defun generic-function-name (class)
;  (error "generic-function-name not implmented in clisp."))
  
(defun finalize-class (class) (values))

(defmethod validate-class ((class t) (superclass t))
  ;; this is a no-op except in OpenMCL 014
  t)

(defmethod make-load-form (obj)
  (error "no make-load-form method for ~s." obj))

(setf clos::*warn-if-gf-already-called* NIL)
(setf custom:*warn-on-floating-point-contagion* nil)

;;;
;;;  misc. stuff
;;;

;(defun object-address (x) (sys::address-of x))

(defun shell (cmd &key (output t) (wait t))
  (ext:run-shell-command cmd :output (if output :terminal nil)
                         :wait wait))

(defconstant directory-delimiter #\/)

;(defun cd (&optional dir)
;  (if dir (setf (ext:default-directory) dir)
;      (ext:default-directory)))
;

(defun cd (&optional (dir (user-homedir-pathname )))
  (setf (ext:default-directory) dir))

(defun pwd ()
  (namestring (ext:default-directory)))

(defun env-var (var)
  (ext::getenv var))

(defun set-env-var (var val)
  (system::setenv var val))

(defun cm-image-dir ()
  ;; clisp's ext:argv only appears in 2.32
  (let* ((v (ext:argv))
         (l (length v))
         (i (position "-M" v :test #'string-equal))
         )
    (if (and i (< i (- l 1)))
      (let ((img (elt v (+ i 1)) ))
        (enough-namestring img
                           (concatenate 'string (pathname-name img)
                                        "." (pathname-type img))))
      nil)))

(defun save-cm (path &rest args)
  (declare (ignore args))
  (ext:saveinitmem path :quiet t
                   :init-function
                   #'(lambda ()
                       (declare (special *cm-readtable*))
                       (setf *package* (find-package :cm))
                       (setf *readtable* *cm-readtable*)
                       (load-cminit)
                       (cm-logo)
                       )))

;;;
;;; thread support
;;;

(defun nothreads ()
  (error "Threads are not supported in CLISP."))

(defun current-thread ()
  (nothreads))

(defun thread? (obj)
  obj
  (nothreads))

(defun make-thread (thunk &optional name)
 (nothreads))

(defun thread-name (thread) 
  thread
  (nothreads))

;(thread-specific thread)
;(thread-specific-set! thread obj)

(defun thread-start! (thread)
  thread
  (nothreads))

(defun thread-yield! ()
  (nothreads))

(defun thread-sleep! (timeout)
  timeout
  (nothreads))

(defun thread-terminate! (thread)
  thread
  (nothreads))

;(thread-join! thread [timeout [timeout-val]])

(defun mutex? (obj)
  obj
  (nothreads))

(defun make-mutex (&optional name)
  name
  (nothreads))

(defun mutex-name (mutex)
  mutex
  (nothreads))

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

(defun current-time ()
  (nothreads))

(defun time? (obj)
  obj
  (nothreads))

(defun time->seconds (time) 
  time
  (nothreads))

(defun seconds->time (sec)
  sec
  (nothreads))

;(current-exception-handler)
;(with-exception-handler handler thunk)
;(raise obj)
;(join-timeout-exception? obj)
;(abandoned-mutex-exception? obj)
;(terminated-thread-exception? obj)
;(uncaught-exception? obj)
;(uncaught-exception-reason exc)

;;;
;;; periodic task support
;;;

(defun set-periodic-task! (&rest args)
  args
  (error "set-periodic-task!: no periodic tasks in CLISP."))

