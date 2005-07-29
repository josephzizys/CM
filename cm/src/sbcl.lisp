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
	  sb-sys:without-interrupts
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
;(defgeneric sprout (obj &optional time dest))
(defgeneric stream-receiver (hook stream type))
(defgeneric deinit-receiver (stream type))
(defgeneric init-receiver (stream type))
(defgeneric receive (stream &rest args))
(defgeneric receive? (stream))


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
;(defgeneric rt-sprout (obj time dest))
;(defgeneric rt-now (io))

;;;
;;; thread support
;;;

#+sb-thread
(progn

(defun thread-current-time ()
  (/ (get-internal-real-time)
     #.(coerce internal-time-units-per-second 'float)))

(defun make-thread (thunk)
  (let ((id (sb-thread:make-thread thunk)))
    (sb-thread::suspend-thread id)
    id))

(defun thread-start! (id)
  (sb-thread::resume-thread id))

(defun thread-sleep! (sec)
  (sleep sec))

(defun make-mutex (&key name)
  (if name (sb-thread:make-mutex :name (string name))
    (sb-thread:make-mutex )))

(defmacro with-mutex-grabbed ((var) &body body)
  `(sb-thread:with-mutex (,var :wait-p t) ,@body))

(defun mutex-lock! (mutex)
  (sb-thread:get-mutex mutex :wait-p t))

(defun mutex-unlock! (mutex)
  (sb-thread:release-mutex mutex))

)


#-sb-thread
(progn

(defun nothreads ()
  (error "SBCL threads are not supported in this OS."))

(defun thread-current-time ()
  (nothreads))

(defun make-thread (thunk &optional name)
  thunk name
  (nothreads))

(defun thread-start! (thread)
  thread
  (nothreads))

(defun thread-sleep! (timeout)
  timeout
  (nothreads))

(defun thread-terminate! (thread)
  thread
  (nothreads))

(defun mutex? (obj)
  obj
  (nothreads))

(defun make-mutex (&optional name)
  name
  (nothreads))

)


;;;
;;; period task support
;;;

(defvar *periodic-tasks* (list ))

(defun set-periodic-task-rate! (rate meas)
  ;; set periodic time but only if tasks are not running
  (if *periodic-tasks*
      (error "set-periodic-task-rate!: Periodic tasks currently running.")
      (let (divs)
        (ecase meas
          ((:second :seconds :sec :s)
           (setf divs 1))
          ((:millisecond :milliseconds :ms :m)
           (setf divs 1000))
          ((:nanosecond :nanoseconds :usec :usecs :u)
           (setf divs 1000000)))
        (multiple-value-bind (sec rem)
            (floor rate divs)
          ;;(print (list sec (* rem (/ 1000000 divs))))
          (setf sb-impl::*max-event-to-sec* sec)
          (setf sb-impl::*max-event-to-usec*
                (floor (* rem (/ 1000000 divs)))))
        (values))))

(defun periodic-task-rate ()
  ;; always return in usec
  (+ (* sb-impl::*max-event-to-sec* 1000000)
     sb-impl::*max-event-to-usec*))

;; (defun set-periodic-task-rate! (milli)
;;   ;; set periodic time but only if tasks are not running
;;   (if *periodic-tasks*
;;       (error "set-periodic-task-rate!: Periodic tasks currently running.")
;;       (let (sec mil)
;;         (if (< milli 1000)
;;             (setf sec 0 mil milli)
;;             (multiple-value-setq (sec mil)
;;               (floor milli 1000)))
;;         (setf sb-impl::*max-event-to-sec* sec)
;;         (setf sb-impl::*max-event-to-usec* (* mil 1000))
;;         milli)))

(defun run-periodic-tasks ()
  ;; this is the polling function, it just funcalls thunks on the list
  (dolist (e *periodic-tasks*) (funcall (cdr e)))
  (values))

(defun periodic-task-running? (&optional owner)
  (if *periodic-tasks*
      (if owner 
          (and (assoc owner *periodic-tasks* :test #'eq) t)
          t)
      nil))

(defun add-periodic-task! (owner task)
  (cond ((null *periodic-tasks*)
         (push (cons owner task) *periodic-tasks*)
         (setf sb-impl::*periodic-polling-function* #'run-periodic-tasks))
        ((assoc owner *periodic-tasks* :test #'eq)
         (error "add-periodic-task!: task already running for ~s."
                owner))
        (t
         (push (cons owner task) *periodic-tasks*)))
  (values))

(defun remove-periodic-task! (owner)
  (if (eq owner t)
      (setf sb-impl::*periodic-polling-function* nil
            *periodic-tasks* (list))
      (let ((e (assoc owner *periodic-tasks* :test #'eq)))
        (cond ((null e)
               (error "remove-periodic-task!: No task for owner ~s."
                      owner))
              (t
               (setf *periodic-tasks* (delete e *periodic-tasks*))
               (if (null *periodic-tasks*)
                   (setf sb-impl::*periodic-polling-function* nil))))))
  (values))

#|
(periodic-task-running?)
(set-periodic-task-rate! 1000) ; milliseconds
(defun moe () (print :you-moron))
(defun larry () (print :ow-ow-ow))
(defun curly () (print :nyuk-nyuk))
(periodic-task-running? :moe)
(add-periodic-task! :moe #'moe)
(add-periodic-task! :larry #'larry)
(remove-periodic-task! :moe)
(add-periodic-task! :curly #'curly)
(add-periodic-task! :moe #'moe)
(remove-periodic-task! :larry)
*periodic-tasks*
(remove-periodic-task! t)
|#




