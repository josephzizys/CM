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

(eval-when (:compile-toplevel :load-toplevel :execute)
  (ccl::open-shared-library "Carbon.framework/Carbon")
  (ccl::use-interface-dir :carbon)
  (require :pascal-strings)
  )

(pushnew :metaclasses *features*)

(import '(ccl:slot-definition-name 
          ccl:slot-definition-initargs 
          ccl:slot-definition-initform 
          ccl:class-direct-superclasses
          ccl:class-direct-subclasses
          ccl:open-shared-library ; needed if loading clm into cm.
          ccl:without-interrupts ; for testing realtime
          ;ccl:process-run-function
          ;ccl:process-kill
          ;ccl:defcallback
          #+:openmcl-partial-mop
          ccl:class-slots
          #+:openmcl-partial-mop
          ccl:class-direct-slots
          #+:openmcl-partial-mop
          ccl:validate-superclass
          ))

#-:openmcl-partial-mop
(progn
  (defun class-slots (class) 
    (ccl::class-instance-slots class))
  (defun class-direct-slots (class)
    (ccl:class-direct-instance-slots class))
  (defmethod validate-class ((class t) (superclass t))
    ;; this is a no-op except in OpenMCL 014
    t)
  )

(defun finalize-class (class) class t)

(defmethod make-load-form (obj) (cl:make-load-form obj))

(defun slot-definition-reader (slot) slot nil)

;;;
;;; misc stuff
;;;

(defun quit () (ccl:quit))

(defun exit () (quit))

(defun object-address (x)
  (ccl:%address-of x))

(defun generic-function-name (fn)
  (ccl::function-name fn))

;(defun cd (&optional dir)
;  (if (null dir)
;    (namestring (ccl::mac-default-directory))
;    (ccl::cwd dir)))

(defun cd (&optional (dir (user-homedir-pathname )))
  (ccl::cwd dir))

(defun pwd ()
  (namestring (ccl::mac-default-directory)))

(defun explode-string (str)
  ;; parse str into a list of tokens
  ;; delimited by whitespace
  (let ((white '(#\space #\tab))
	(slen (length str))
	(args '()))

    (loop with i = 0 and b and s and l
	  while (< i slen)
	  do
	  ;; flush whitespace
	  (loop while (and (< i slen)
			   (member (elt str i) white))
	    do (incf i))
	  (unless (< i slen)
	    (return))
	  (setf b i)
	  (setf s nil)
	  (setf l #\null)
	  ;; read until next undelimited whitspace
	  (loop while (and (< i slen)
			   (or (not (member (elt str i) white))
			       (char= l #\\)
			       s))
	    do
	    (if (char= (elt str i) #\")
	      (setf s (not s)))
	    (setf l (elt str i))
	    (incf i))
	  (push (subseq str b i) args))
    (nreverse args)))

(defun shell (cmd &key (output t) (wait t))
  (ccl:run-program "/bin/csh" (list "-fc" cmd)
                   :output output :wait wait))

(defparameter *browser* nil)

(defun open-url (url &key (browser *browser*))
  (ccl:run-program "open" (list "-a" browser url))
  (values))

(defconstant directory-delimiter #\/)

;;;
;;; cm application class
;;; 

(defclass cm-application (ccl::lisp-development-system) ())

(defparameter *cm-application-class* (find-class 'cm-application))

(defmethod initialize-instance :after ((obj cm-application) &rest args)
  args
  (setf (slot-value obj 'ccl::command-line-arguments)
	(list ccl::*standard-help-argument*
	      (ccl::make-command-line-argument
	       :option-char #\I
	       :long-name "image-name"
	       :keyword :image-name
	       :help-string "image-name <file>"
	       :may-take-operand t
	       :allow-multiple nil)
	      (ccl::make-command-line-argument
	       :option-char #\l
	       :long-name "load"
	       :keyword :load
	       :help-string "load <file>"
	       :may-take-operand t
	       :allow-multiple t)
	      (ccl::make-command-line-argument
	       :option-char #\e
	       :long-name "eval"
	       :keyword :eval
	       :help-string "evaluate <form> (may need to quote <form> in shell)"
	       :may-take-operand t
	       :allow-multiple t))))

(defmethod ccl:application-name ((app cm-application)) "Common Music")

(defparameter *cm-swank-port* nil)

(defmethod ccl::run-application ((app cm-application) &key &allow-other-keys)
  (when (and *cm-swank-port* (find-package ':swank))
    (funcall (find-symbol "CREATE-SERVER" ':swank)
             :port *cm-swank-port*))
  (ccl::with-pstrs ((msg "Hello from CM!"))
    (#_StandardAlert #$kAlertNoteAlert msg
                     (ccl:%null-ptr) (ccl:%null-ptr) (ccl:%null-ptr)))
  (#_RunApplicationEventLoop)
  (ccl:quit))

(defmethod ccl:toplevel-function ((app cm-application) init-file)
  (declare (ignore init-file) (special *cm-readtable*))
  (setf *package* (find-package :cm))
  (setf *readtable* *cm-readtable*)
  (load-cminit)
  (cm-logo)
  (ccl::run-application app))

;;;
;;; save cm
;;;

(defun cm-image-dir ()
  (namestring
   (make-pathname
    :directory (pathname-directory ccl::*heap-image-name*))))

(defun env-var (var)
  (ccl::getenv (string var)))

(defun set-env-var (var val)
  (ccl::setenv (string var) val))

(defun save-cm (&optional path &rest args &key slime-directory 
			  swank-port)
  ;; if user calls this function, path is path directory to save app in.
  ;; else (called by make-cm) path is  cm/bin/openmcl*/cm.image
  (declare (ignore args) (special *cm-readtable*))
  (let* ((appdir (cond ((and (not path)
                             (boundp 'cl-user::binary-dir))
                        (symbol-value 'cl-user::binary-dir))
                       ((ccl:directoryp path)
                        (probe-file path))
                       ((equal (pathname-type path) "image")
                        (make-pathname :name nil :type nil
                                       :defaults path))
                       (t
                        (error "save-cm: ~s is not a directory." 
                               path))))
         (bundle (merge-pathnames "CM.app/" appdir))
         (resdir (merge-pathnames "Contents/Resources/" bundle))
         (exedir (merge-pathnames "Contents/MacOS/" bundle)))
    (unless (probe-file bundle)
      (ccl:create-directory bundle)
      (ccl:create-directory resdir)
      (ccl:create-directory exedir)
      (create-info-plist (make-pathname :name "info" :type "plist"
                                        :defaults bundle)))
    (ccl::copy-file (car ccl::*command-line-argument-list*)
                    (merge-pathnames "cm" exedir)
                    :if-exists :supersede)
    (when slime-directory
      (if (ccl:directoryp slime-directory) ; ensure / at end
	  (setf slime-directory (probe-file slime-directory))
	(error "save-cm: :slime-directory ~s is not a directory."
	       slime-directory))
      (let ((files '("swank-backend" "nregex" "metering" "swank-openmcl" "swank-gray"
		     "swank")))
	(dolist (f files)
	  (load (merge-pathnames f slime-directory)))))
    (when swank-port
      (unless (find-package :swank)
	(error "save-cm: :swank-port specified but swank is not loaded. Specify :slime-directory to load it.")
	(setf *cm-swank-port* swank-port)))
    (setf ccl::*inhibit-greeting* t)
    (ccl:save-application (merge-pathnames "cm.image" exedir)
                          :application-class *cm-application-class*)))

(defun create-info-plist (path)
  (with-open-file (fil path :direction :output :if-does-not-exist :create
                       :if-exists :supersede)
    (format fil
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<!DOCTYPE plist PUBLIC \"-//Apple Computer//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">
<plist version=\"1.0\">
<dict>
	<key>CFBundleDevelopmentRegion</key>
	<string>English</string>
	<key>CFBundleExecutable</key>
	<string>cm</string>
	<key>CFBundleInfoDictionaryVersion</key>
	<string>6.0</string>
	<key>CFBundlePackageType</key>
	<string>APPL</string>
	<key>CFBundleSignature</key>
	<string>????</string>
	<key>CFBundleVersion</key>
	<string>0.2</string>
	<key>NSMainNibFile</key>
	<string>MainMenu</string>
</dict>
</plist>
")))

;;;
;;; midishare callbacks moved here.
;;;

(ccl:defcallback run-proc (:unsigned-fullword date :unsigned-halfword refnum
                                              :unsigned-fullword indx
                                              :unsigned-fullword arg1
                                              :unsigned-fullword arg2)
  (declare (ignore arg1 arg2)
           (function rem-proc)
           (special *qstart* *qtime* *qnext* *proctable*))
  (setf *qstart* 0)                     ; unused here
  (setf *qtime* date)                   ; current time
  (setf *qnext* date)                   ; 'wait' sets this ahead.
  ;; funcall the process fn until its next run time is
  ;; in the future or the process is dead (returned nil)
  (do ((proc (elt *proctable* indx))
       (alive t))
      ((or (not alive)                 ; stop if process killed itself
           (> *qnext* *qtime*))        ; or need to reschedule
       (if alive
         (ms:MidiTask run-proc *qnext* refnum indx 0 0)
         (rem-proc indx))
       (values))
    (setq alive (funcall proc))))

(ccl:defcallback midi-receive-hook (:unsigned-halfword refnum)
  (declare (special *receive-hook* *mp*))
  (restart-case
      (handler-bind ((error
                      #'(lambda (c)
                          (declare (ignore c))
                          (invoke-restart 'callback-error-exit))))
        ;;; the receive loop...
        (do ((go t)
             (ev (ms:MidiGetEv refnum) (ms:MidiGetEv refnum)))
            ((or (not go) (ms:nullptrp ev))
             (values))
          (if *receive-hook*
            (funcall *receive-hook* ev)
            (setf go nil))))
    (callback-error-exit () 
      (format t "~&Caught error under MIDI callback! Exiting receive.~&")
      ;;(ms:MidiFreeEv e)
      (ms:MidiFlushEvs *mp*)
      (setf *receive-hook* nil)
      (ms:MidiSetRcvAlarm *mp* (ms:nullptr))
      (values))))

(defun thread-current-time ()
  (#_CFAbsoluteTimeGetCurrent))

;;; beginning thread support a la SRFI-18
;;; 

(defclass thread (ccl::process) ())

(defun current-thread ()
  ccl::*current-process*)

(defun thread? (obj)
  (equal (find-class 'ccl::process)
	 (class-of obj)))

(defun make-thread (thunk &optional name)
  (let ((proc-name)
	(proc))
    (if name 
	(setf proc-name name)
      (setf proc-name (format nil "rt-thread-~S" (gensym))))
    (setf proc (ccl::make-process proc-name))
    (ccl::process-preset proc thunk)))

(defun thread-name (obj)
  (slot-value obj 'ccl::name))

(defun thread-start! (obj)
  (ccl::process-enable obj))

(defun thread-sleep! (wait-time)
  (multiple-value-bind (q r) (floor wait-time)
    (ccl::%nanosleep q (floor (* r 1000000000)))))

(defun mutex? (obj)
  (typep obj 'ccl::recursive-lock))

(defun make-mutex (&optional name)
  (ccl::make-lock name))

(defun mutex-name (obj)
  (error "Dont know how to access name of ~s." obj))

(defun mutex-lock! (obj)
  (ccl::grab-lock obj))

(defun mutex-unlock! (obj)
  (ccl::release-lock obj))

;;;time object from srfi-18
;;;

(defclass time ()
  ((type :initform 'native :accessor time-type)
   (second :accessor time-second)
   (millisecond :accessor time-millisecond)))


(defun current-time ()
  (let ((obj (make-instance 'time)))
    (multiple-value-bind (utime ms)
 	(truncate (get-internal-real-time) 1000)
      (setf (slot-value obj 'second) utime)
      (setf (slot-value obj 'millisecond) ms))
    obj))

(defun time? (obj)
  (equal (find-class 'time) (class-of obj)))
    
(defun time->seconds (obj)
  (if (time? obj)
      (+ (slot-value obj 'second)
	 (* (slot-value obj 'millisecond) .001D0))
    nil))

(defun seconds->time (sec)
  (let ((obj (make-instance 'time)))
    (multiple-value-bind (utime ms)
	(floor sec)
      (setf (slot-value obj 'second) utime)
      (setf (slot-value obj 'millisecond) (floor (* 1000 (float ms)))))
    obj))

;;; sleeping...

;;(defmethod thread-sleep! ((abs-time time))
;;  (let ((target-time (time->seconds abs-time)))
;;    (ccl::process-wait "waiting"
;;		       #'(lambda (x) (> (time->seconds (current-time))  x))
;;			   target-time)))

;;(defmethod thread-sleep! ((wait-time number))
;;  (let ((start-time (time->seconds (current-time))))
;;    (ccl::process-wait "waiting"
;;		       #'(lambda (x) (> (- (time->seconds (current-time)) start-time) x))
;;			   wait-time)))

;;;
;;; socket/udp support
;;;

(defun make-udp-socket (host port local-port)
  (ccl:make-socket :type :datagram :remote-port port :remote-host host
			 :local-port local-port
			 :format :binary))

(defun socket-close (sock)
  (ccl::close sock))

(defun socket-shutdown (sock &rest args)
  args
  (ccl::shutdown sock))

(defun socket-recv (sock bytes &optional flags)
  flags
  (ccl::receive-from sock bytes))

(defun socket-recvfrom (sock bytes &optional flags)
  flags
  (multiple-value-bind (buf num-bytes ip port)
      (ccl::receive-from sock bytes)
    num-bytes
    port
    (values buf ip)))

(defun send-osc (mess sc-stream len)
  (ccl::send-to (slot-value sc-stream 'socket) mess len))

(defun modf (num)
  (multiple-value-bind (int rem)
      (floor num)
    int
    rem))

(defun make-osc-timetag (offset out)
  (let* ((now (current-time))
         (offset-time (seconds->time offset))
         (target-time (seconds->time (+ (time->seconds now)
                                        (time->seconds offset-time) 
                                        (slot-value out 'latency))))
         (vec nil))
    (setf vec (make-byte-vector (+ 2208988800
                                   (slot-value target-time 'second))))
    (u8vector-append
     vec (make-byte-vector (inexact->exact
                            (* (modf (time->seconds target-time))
                               #xffffffff))))))

;;; new periodic-task support

(defvar *periodic-tasks*
  ;; a list ((<owner> . <task-thunk>) ...) where <owner> is whatever
  ;; the <task-thunk> is associated with.
  (list ))
(defparameter *periodic-task-rate* 1)
(defparameter *periodic-polling-timer* nil)
(defparameter *periodic-polling-thread* nil)
(defparameter *periodic-polling-callback* nil)

(defun %string->cfstringref (string)
  (ccl::with-cstrs ((str string))
    (#_CFStringCreateWithCString (ccl::%null-ptr) str
                                 #$kCFStringEncodingMacRoman)))

(defun %release-cfstring (string)
  (#_CFRelease string))

(defun run-periodic-task ()
  (let ((timer-context (%string->cfstringref "cm-periodic")))
    (ccl::defcallback *periodic-polling-callback*
        (:<CFR>un<L>oop<T>imer<R>ef timer (:* t) info)
      (declare (ignore timer info))
      (if *periodic-tasks*
          (run-periodic-tasks)
	(progn
	  (when *periodic-polling-timer*
	    (#_CFRunLoopStop (#_CFRunLoopGetCurrent)))
	  (when *periodic-polling-thread*
	    (ccl::process-kill *periodic-polling-thread*)))))
    (setf *periodic-polling-thread*
	  (ccl::process-run-function "periodic-polling-thread"
	    (lambda ()
	      (setf *periodic-polling-timer*
		    (#_CFRunLoopTimerCreate (ccl::%null-ptr)
                                            (#_CFAbsoluteTimeGetCurrent)
					    (* .001D0 *periodic-task-rate*)
                                            0
                                            0
                                            *periodic-polling-callback*
                                            (ccl::%null-ptr)))
	      (#_CFRunLoopAddTimer (#_CFRunLoopGetCurrent)
                                   *periodic-polling-timer* timer-context)
	      (#_CFRunLoopRunInMode timer-context 10000000.D0 #$false)
	      (#_CFRunLoopTimerInvalidate *periodic-polling-timer*)
	      (#_CFRelease *periodic-polling-timer*)
	      (%release-cfstring timer-context))))))

(defun set-periodic-task-rate! (ms)
  ;; set periodic time but only if tasks are not running
  (if *periodic-tasks*
      (error "set-periodic-task-rate!: Periodic tasks currently running.")
      (setf *periodic-task-rate* ms)))

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
	 (run-periodic-task ))
        ((assoc owner *periodic-tasks* :test #'eq)
         (error "add-periodic-task!: task already running for ~s."
                owner))
        (t
         (push (cons owner task) *periodic-tasks*)))
  (values))

(defun remove-periodic-task! (owner)
  (if (eq owner t)
      (setf *periodic-tasks* (list))
      (let ((e (assoc owner *periodic-tasks* :test #'eq)))
        (cond ((null e)
               (error "remove-periodic-task!: No task for owner ~s."
                      owner))
              (t
               (setf *periodic-tasks* (delete e *periodic-tasks*))))))
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


;(defun set-periodic-task! (thunk &key (period 1) (mode ':set))
;  ;;period is in milliseconds
;  (declare (ignore mode))
;  (cond ((not thunk) 
;	 (setf *periodic-polling-function* nil))
;	((not (null *periodic-polling-function*))
;	 (error "set-periodic-task!: Periodic task already running!"))
;	(t
;	 (setf *periodic-polling-function* thunk)
;	 (run-periodic-task period)))
;  (values))


#|
(defun cf-runloop-now ()
  (#_CFAbsoluteTimeGetCurrent))

(defun cf-runloop-wait (abs-time timer)
  (#_CFRunLoopTimerSetNextFireDate timer abs-time))


(defun rts3 (object to &optional (at 0) &key end-time)
  (declare (special rts-callback))
  (if (rts-running?)
      (error "rts: already running."))
  (let ((ahead (if (consp at)
		   (car at) at)))
    (setf *queue* %q)
    (setf *scheduler* t)
    (if (consp object)
        (dolist (o object)
          (schedule-object o
			   (if (consp ahead)
			       (if (consp (cdr ahead)) (pop ahead) (car ahead))
			     ahead)))
      (if (consp ahead)
	  (schedule-object object (car ahead))
	(schedule-object object ahead)))
    (setf *out* to)
    (setf *rts-run* t)
    (if (consp ahead)
	(setf ahead (apply #'min ahead)))
    (setf *rts-now* ahead)

    (let ((target-time nil)
	  (entry nil)
	  (qtime nil)
	  (start nil)
	  (thing nil)
	  (wait? nil)
	  (none? (null (%q-head *queue*))))
      (ccl::defcallback rts-callback (:<CFR>un<L>oop<T>imer<R>ef timer (:* t) info)
	(declare (ignore info))
	(if (not target-time)
	    (setf target-time (+ *rts-now* (#_CFAbsoluteTimeGetCurrent))))
	(if (and (not none?) *rts-run*)
	    (progn
	      (do ()
		  ((or none? (> (%qe-time (%q-peek *queue*)) *rts-now*))
		   (if none?
		       (setf wait? nil)
		     (let* ((next (%qe-time (%q-peek *queue*))))
		       (setf wait? (- next *rts-now*))
		       (setf *rts-now* next))))
		(setf entry (%q-pop *queue*))
		(setf qtime (%qe-time entry))
		(setf start (%qe-start entry))
		(setf thing (%qe-object entry))
		(%qe-dealloc *queue* entry)
		(process-events thing qtime start *out*)
		(setf none? (null (%q-head *queue*))))
	      (if  wait?
		  (cf-runloop-wait (setf target-time (+ target-time wait?)) timer)
		(cf-runloop-wait target-time timer)))
	  (progn
	    (unless none?
	      (%q-flush *queue*))
	    (unschedule-object object t)
	    (#_CFRunLoopStop (#_CFRunLoopGetCurrent)))))
      (ccl::process-run-function "rts-thread"
	(lambda ()
	  (without-interrupts
	   (ccl::external-call "_CFRunLoopGetCurrent" :address)
	   (ccl::external-call
	    "__CFRunLoopSetCurrent"
	    :address (ccl::external-call "_CFRunLoopGetMain" :Address))
	   (ccl::%stack-block ((psn 8))
	      (ccl::external-call "_GetCurrentProcess" :address psn)
	      (ccl::with-cstrs ((name "cm rt"))
		(ccl::external-call "_CPSSetProcessName" :address psn :address name))))
	  (let ((rts-timer (#_CFRunLoopTimerCreate (ccl::%null-ptr)
						   (+ (#_CFAbsoluteTimeGetCurrent) *rts-now*) 10000000.D0
						   0 0 rts-callback
						   (ccl::%null-ptr)))
		(timer-context (%string->cfstringref "cm-rts")))
	    (#_CFRunLoopAddTimer (#_CFRunLoopGetCurrent) rts-timer timer-context)
	     (#_CFRunLoopRunInMode timer-context (if end-time (coerce end-time 'double-float) 10000000.D0) #$false)
	     (#_CFRunLoopTimerInvalidate rts-timer)
	     (#_CFRelease rts-timer)
	     (%q-flush *queue*)
	     (setf *rts-run* nil)
	     (setf *queue* nil)
	     (setf *scheduler* nil)
	     (setf *rts-now* nil)
	     (%release-cfstring timer-context)
	     (ccl::process-kill ccl::*current-process*)))))))





;;; fix :output for your machine, call (pm:GetDeviceDescriptions)

(defparameter *pm* (portmidi-open :output 3 :latency 0))

(defun foo (num dur)
  (let ((ev (new midi :duration 1 :amplitude .5 :keynum 60)))
    (process repeat num for i from 0
             do (sv ev :time (now))
             output ev
             wait dur)))

(rts (foo 100 .1) *pm*) 
(rts3 (foo 100 .1) *pm*)

(rts (foo 100 .1) *pm* 3) 
(rts3 (foo 100 .1) *pm* 3)

(rts (foo 100 .1) *pm* 0 2)
(rts3 (foo 100 .1) *pm* 0 :end-time 2)

(rts3 (foo 1000 .1) *pm*)

(defun fluff1 (num dur)
  (process repeat num for i from 0 
	   output (new midi :time (now) :duration (* 2 dur) :amplitude .5 :keynum 
		       (pickl '(60 62 64 67 72 65 69 48 50)))
	   wait (pickl (list dur (/ dur 2) (/ dur 4)))
	   when (= i (1- num))
	   sprout (process repeat 4
			   output (new midi :time (now) :duration 5 :amplitude .5 :keynum 
				       (pickl '(62 64 67 72 65 69  50))))
	   and
	   sprout (process repeat 4
			   output (new midi :time (now) :duration 5 :amplitude .5 :keynum 
				       (pickl '(60 64 67 72 69 48 50))))
	   at (+ (now) 2)))


(rts3 (fluff1 30 1) *pm*)


;; having time of midi > (now)
;; also seems to work (see last sprout)
;;

(defun fluff2 (num dur)
  (process repeat num for i from 0 
	   output (new midi :time (now) :duration (* 2 dur) :amplitude .5 :keynum 
		       (pickl '(60 62 64 67 72 65 69 48 50)))
	   wait (pickl (list dur (/ dur 2) (/ dur 4)))
	   when (= i (1- num))
	   sprout (process repeat 4
			   output (new midi :time (now) :duration 5 :amplitude .5 :keynum 
				       (pickl '(62 64 67 72 65 69  50))))
	   and
	   sprout (process repeat 4
			   output (new midi :time (+ (now) 2) :duration 5 :amplitude .5 :keynum 
				       (pickl '(60 64 67 72 69 48 50))))))
(rts3 (fluff2 30 1) *pm*)


(defun endless-fluff (num dur)
  (process repeat num for i from 0 
	   output (new midi :time (now) :duration (* 2 dur) :amplitude .5 :keynum 
		       (pickl '(60 62 64 67 72 65 69 48 50)))
	   wait (pickl (list dur (/ dur 2) (/ dur 4)))
	   when (= i (1- num))
	   sprout (process repeat 4
			   output (new midi :time (now) :duration 5 :amplitude .5 :keynum 
				       (pickl '(62 64 67 72 65 69  50))))
	   and
	   sprout (endless-fluff 30 1)))

(rts3 (endless-fluff 30 1) *pm* 2)
(rts-stop)

|#
