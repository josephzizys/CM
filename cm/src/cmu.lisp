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

(defun nothreads ()
  (error "CMUCL user threads are not support in this OS."))

(defun current-thread ()
  #+x86 mp:*current-process*
  #-x86 (nothreads))

(defun thread? (obj)
  #+x86 (mp:processp obj)
  #-x86 (nothreads))

(defun make-thread (thunk &optional name)
  #+x86
  (let* ((n (or name (format nil "CM-~A" (gentemp "THREAD"))))
         (p (mp:make-process thunk :name n)))
    (mp:disable-process p)
    p)
  #-x86 (nothreads))

(defun thread-name (thread) 
  #+x86 (mp:process-name thread)
  #-x86 (nothreads))

;(thread-specific thread)
;(thread-specific-set! thread obj)

(defun thread-start! (thread)
  #+x86 (mp:enable-process thread)
  #-x86 (nothreads))

(defun thread-yield! ()
  #+x86 (mp:process-yield)
  #-x86 (nothreads))

(defun thread-sleep! (timeout)
  #+x86 (sleep timeout)
  #-x86 (nothreads))

(defun thread-terminate! (thread)
  #+x86 (mp:destroy-process thread)
  #-x86 (nothreads))

;(thread-join! thread [timeout [timeout-val]])

(defun mutex? (obj)
  #+x86 (typep obj 'mp:lock)
  #-x86 (nothreads))

(defun make-mutex (&optional name)
  #+x86 (mp:make-lock name)
  #-x86 (nothreads))

(defun mutex-name (mutex)
  #+x86 (slot-value mutex 'mp::name)
  #-x86 (nothreads))

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
  (get-internal-real-time))

(defun time? (obj)
  (and (integerp obj) (> obj 0)))

(defun time->seconds (time) 
  (/ time #.(coerce internal-time-units-per-second 'float)))

(defun seconds->time (sec)
  (truncate (* sec internal-time-units-per-second)))

;(current-exception-handler)
;(with-exception-handler handler thunk)
;(raise obj)
;(join-timeout-exception? obj)
;(abandoned-mutex-exception? obj)
;(terminated-thread-exception? obj)
;(uncaught-exception? obj)
;(uncaught-exception-reason exc)

;;;
;;; period task support
;;;

(defun set-periodic-task! (thunk &key (period 1) (mode ':set))
  ;; period is in milliseconds
  (declare (ignore mode))
  (cond ((not thunk)
         (setf lisp::*max-event-to-sec* 1)
         (setf lisp::*max-event-to-usec* 0)
         (setf lisp::*periodic-polling-function* nil))
        ((not (null lisp::*periodic-polling-function*))
         (error "set-periodic-task!: Periodic task already running!"))
        (t
         (let (sec mil)
           (if (< period 1000)
               (setf sec 0 mil period)
               (multiple-value-setq (sec mil) (floor period 1000)))
           (setf lisp::*max-event-to-sec* sec)
           (setf lisp::*max-event-to-usec* (* mil 1000))
           (setf lisp::*periodic-polling-function* thunk))))
  (values))

; (set-periodic-task! (lambda () (print ':hiho!)) :period 2000)
; (set-periodic-task! (lambda () (print ':hiho!)) :period 1000)
; (set-periodic-task! (lambda () (print ':hiho!)) :period 500)
; (set-periodic-task! (lambda () (print ':hiho!)) :period 999)
; (set-periodic-task! nil)
