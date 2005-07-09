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

(import '(sb-ext::load-foreign
          sb-pcl:slot-definition-initargs
          sb-pcl:slot-definition-initform
          sb-pcl:slot-definition-name
          sb-pcl:class-direct-slots
          sb-pcl:class-slots
          sb-pcl:class-direct-superclasses
          sb-pcl:generic-function-name
          sb-mop:class-direct-subclasses
          sb-mop:validate-superclass
          )
        :cm)

(require :sb-posix)
(import '(sb-posix:chdir) :cm)

(defun quit () (sb-ext:quit))
(defun exit () (quit))

;(defun class-subclasses (c)
;  (let ((subs (sb-pcl:class-direct-subclasses c)))
;    (if (null subs)
;	'()
;      (loop for s in subs
;	append (cons s (class-subclasses s))))))
	  
(defun finalize-class (class) 
  (sb-pcl:finalize-inheritance class))

;(defgeneric validate-class (obj1 obj2))
;(defmethod validate-class ((class t) (superclass t))
;  ;; this is a no-op except in OpenMCL 014
;  t)

(defun slot-defintion-reader (slot) slot nil)

;;;
;;; misc. stuff
;;;

(defun arglist (function)
  (sb-kernel:%simple-fun-arglist function))

(defun object-address (thing)
  (sb-kernel:get-lisp-obj-address thing))

(defconstant directory-delimiter #\/)

;;(defun shell (format &rest strings) 
;;  (let ((str (apply #'format nil format strings)))
;;    (sb-ext:run-program "/bin/csh" (list "-fc" str) :output t)))

(defun shell (cmd &key (wait t) (output t))
  (sb-ext:run-program "/bin/csh" (list "-fc" cmd)
                      :output output :wait wait))

(defun cd (&optional (dir (user-homedir-pathname )))
  (sb-posix:chdir dir)
  (let ((host (pathname-host dir))
        (name (pathname-name dir))
        (path (pathname-directory dir)))
    ;; allow dirs without ending delim "/tmp"
    (when name
      (setq path (append path (list name))))
    (setq *default-pathname-defaults*
          (make-pathname :host host :directory path))
    (namestring *default-pathname-defaults*)))

(defun pwd ()
  (namestring
   (make-pathname :host (pathname-host *default-pathname-defaults*)
                  :directory (pathname-directory
                              *default-pathname-defaults*))))

(defun env-var (var)
  (sb-posix::getenv var))

(defun set-env-var (var val)
  (sb-posix::putenv (format nil "~a=~a" var val)))

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

;;
;;; arrrrg a pox on frigging style warnings!!

(defgeneric make-byte-vector (obj))
(defgeneric return-type-code (obj))
(defgeneric get-first-obj (obj))
(defgeneric class-parameters (obj))
(defgeneric (setf class-parameters) (val obj))
(defgeneric io-class-file-types (obj))
(defgeneric (setf io-class-file-types) (val obj))
;(defgeneric io-class-mime-type (obj))
;(defgeneric (setf io-class-mime-type) (val obj))
(defgeneric io-class-output-hook (obj))
(defgeneric (setf io-class-output-hook) (val obj))
(defgeneric io-class-definer (obj))
(defgeneric (setf io-class-definer) (val obj))
(defgeneric io-class-file-versions (obj))
(defgeneric (setf io-class-file-versions) (val obj))
;(defgeneric validate-superclass (obj1 obj2))
(defgeneric make-load-form (obj))
(defgeneric fill-object (obj1 obj2))
(defgeneric rename-object (obj1 name &rest args))
(defgeneric copy-object (obj))
(defgeneric subcontainers (obj))

(defgeneric insert-object (obj1 obj2))
(defgeneric append-object (obj1 obj2))
(defgeneric remove-object (obj1 obj2))
(defgeneric remove-subobjects (obj))
;(defgeneric list-subobjects (obj  &key start end start-time end-time))
(defgeneric amplitude (amp &optional softest loudest power))
(defgeneric rhythm (rhy &optional tempo beat))
(defgeneric tuning->mode (mode keynum force?))
(defgeneric mode->tuning (mode keynum return))
(defgeneric tuning-hertz->keynum (obj hz))
(defgeneric tuning-hertz->note (scale hz acci err?))
(defgeneric tuning-keynum->hertz (obj knum))
(defgeneric tuning-keynum->note (obj knum acci err?))
(defgeneric tuning-note->hertz (obj note err?))
(defgeneric tuning-note->keynum (obj note err?))
(defgeneric tuning-note->note (obj note acci err?))
(defgeneric scale-mod (freq modulus &key offset in accidental))
(defgeneric note-in-scale? (note scale))
(defgeneric transpose (note int &optional scale))
(defgeneric invert (ref &optional pc?))
(defgeneric interval (int &optional int2))

(defgeneric canonicalize-pattern-data (obj data parser inits))
(defgeneric pattern-external-inits (obj))
(defgeneric pattern-period-length (obj))
(defgeneric default-period-length (obj))
(defgeneric pattern? (obj))
(defgeneric eop? (obj))
(defgeneric eod? (obj))
(defgeneric next-1 (obj))
(defgeneric skip-datum? (obj))
(defgeneric reset-period (obj))
(defgeneric next-in-pattern (obj))
(defgeneric map-pattern-data (fn obj))

(defgeneric io-handler-args (obj))
(defgeneric io-handler-args? (obj))
(defgeneric set-io-handler-args! (obj args))
(defgeneric init-io (obj &rest inits))
(defgeneric open-io (obj dir &rest args))
(defgeneric close-io (obj &rest mode))
(defgeneric initialize-io (obj))
(defgeneric deinitialize-io (obj))
(defgeneric write-event (obj io time))
(defgeneric import-events (obj &rest args))

(defgeneric schedule-object (obj start))
(defgeneric unschedule-object (obj &rest recurse))
(defgeneric process-events (obj time start func))
(defgeneric sprout (obj &optional time dest))


(defgeneric midi-event-data1 (obj))
(defgeneric midi-event-data2 (obj))
(defgeneric midi-event->midi-message (obj))

(defgeneric midi-write-message (msg mf time data))

(defgeneric object->midi (obj))

(defgeneric midishare-stream-refnum (obj))
(defgeneric open-midishare-client (obj name))
(defgeneric close-midishare-client (obj))

(defgeneric player-play (obj))
(defgeneric player-set-sync (obj sync))
(defgeneric player-set-tempo (obj tempo))
(defgeneric player-start (obj))
(defgeneric player-stop (obj))
(defgeneric player-pause (obj))
(defgeneric player-cont (obj))
(defgeneric player-mute (obj track))
(defgeneric player-unmute (obj track))
(defgeneric player-solo (obj track))
(defgeneric player-unsolo (obj track))
(defgeneric player-load-midifile (obj fil))
(defgeneric player-save-midifile (obj fil))

(defgeneric object->cmn (obj))

(defgeneric import-set-slots (obj list))  ; sc.scm
(defgeneric sc-env->list (obj))
(defgeneric rt-output (obj dest &optional time))
(defgeneric write-bundle (offset message io))
;; bug??: sprout has 2 optionals but rt-sprout has them required
(defgeneric rt-sprout (obj time dest))
(defgeneric rt-now (io))
(defgeneric receive! (stream hook))

;;;
;;; thread support
;;;

(defun nothreads ()
  (error "SBCL threads are not supported in this OS."))

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
;;; period task support
;;;

(defun set-periodic-task! (thunk &key (period 1) (mode ':set))
  ;; period is in milliseconds
  (declare (ignore mode))
  (cond ((not thunk)
         (setf sb-impl::*max-event-to-sec* 1)
         (setf sb-impl::*max-event-to-usec* 0)
         (setf sb-impl::*periodic-polling-function* nil))
        ((not (null sb-impl::*periodic-polling-function*))
         (error "set-periodic-task!: Periodic task already running!"))
        (t
         (let (sec mil)
           (if (< period 1000)
               (setf sec 0 mil period)
               (multiple-value-setq (sec mil) (floor period 1000)))
           (setf sb-impl::*max-event-to-sec* sec)
           (setf sb-impl::*max-event-to-usec* (* mil 1000))
           (setf sb-impl::*periodic-polling-function* thunk))))
  (values))

; (set-periodic-task! (lambda () (print ':hiho!)) :period 2000)
; (set-periodic-task! (lambda () (print ':hiho!)) :period 1000)
; (set-periodic-task! (lambda () (print ':hiho!)) :period 500)
; (set-periodic-task! (lambda () (print ':hiho!)) :period 999)
; (set-periodic-task! nil)

