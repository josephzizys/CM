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

;;(defun shell (str &rest args)
;;  (let* ((raw (apply #'format nil str args))
;;	 (lst (explode-string raw)))
;;    (ccl:run-program (car lst) (cdr lst) :output t)
;;    (values)))

#|
(defun shell (str &rest args)
  (let* ((raw (apply #'format nil str args))
	 (lst (explode-string raw)))
    (ccl:run-program "/bin/sh"
		     (cons "-c" lst)
		     :output t)
    (values)))
|#

(defparameter *browser*
  "/Applications/Networking/Internet\\ Explorer.app"  )


(defun open-url (url &key (browser *browser*))
  (ccl:run-program "open" (list "-a" browser url))
  (values))

(defconstant directory-delimiter #\/)

;; open midi file in QuickTime on OSX from Michael Klingbeil

;(defun osx-play-midi-file (file &rest args)
;   (declare (ignore args))
;   (setf file (namestring (truename file)))
;   ;; set file types need the developer tools
;   ;; installed for the SetType command
;   ;(ccl:run-program "/Developer/Tools/SetFile"
;   ;(list "-t" "Midi" "-c" "TVOD" file))
;   ;(ccl::set-mac-file-type file "Midi")
;   ;(ccl::set-mac-file-creator file "TVOD")
;   (ccl:run-program "/usr/bin/open" (list file)))

;;;
;;; cm application class
;;; 

(defclass cm (ccl::lisp-development-system) ())

(defmethod initialize-instance :after ((obj cm) &rest args)
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

(defmethod ccl:application-name ((app cm)) "Common Music")

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

(defun save-cm (path &rest args)
  (declare (ignore args) (special *cm-readtable*))
  (setf ccl::*inhibit-greeting* t)
  (setf ccl:*lisp-startup-functions*
        (append ccl:*lisp-startup-functions*
                (list #'(lambda ()
                          (declare (special *cm-readtable*))
                          (setf *package* (find-package :cm))
                          (setf *readtable* *cm-readtable*)
                          (load-cminit)
                          (cm-logo)
                          ))))
  (ccl:save-application path :application-class (find-class 'cm)))

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

(defun thread-nanosleep! (wait-time)
  (multiple-value-bind (q r) (floor wait-time)
    (ccl::%nanosleep q (floor (* r 1000000000)))))

;;if thread-sleep! is passed a time object this is absolute time
;;if a number it is time to wait

(defmethod thread-sleep! ((abs-time time))
  (let ((target-time (time->seconds abs-time)))
    (ccl::process-wait "waiting"
		       #'(lambda (x) (> (time->seconds (current-time))  x))
			   target-time)))

(defmethod thread-sleep! ((wait-time number))
  (let ((start-time (time->seconds (current-time))))
    (ccl::process-wait "waiting"
		       #'(lambda (x) (> (- (time->seconds (current-time)) start-time) x))
			   wait-time)))


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
         (target-time (seconds->time (+ (time->seconds now) (time->seconds offset-time) (slot-value out 'latency))))
         (vec nil))
    (setf vec (make-byte-vector (+ 2208988800 (slot-value target-time 'second))))
    (u8vector-append vec (make-byte-vector (inexact->exact (* (modf (time->seconds target-time)) #xffffffff))))))


;;; new periodic-task support

(defparameter *periodic-polling-function* nil)
(defparameter *periodic-polling-timer* nil)
(defparameter *periodic-polling-thread* nil)
(defparameter *periodic-polling-callback* nil)

(eval-when (:compile-toplevel :load-toplevel :execute)
  (ccl::use-interface-dir :CARBON))

(eval-when (:compile-toplevel :load-toplevel :execute)
  (ccl::open-shared-library "Carbon.framework/Carbon"))

(defun %string->cfstringref (string)
  (ccl::with-cstrs ((str string))
    (#_CFStringCreateWithCString (ccl::%null-ptr)  str #$kCFStringEncodingMacRoman)))

(defun %release-cfstring (string)
  (#_CFRelease string))

(defmacro run-polling-function (func time-period)
  (let ((timer-callback (string->symbol (format nil "timer-callback-~s" (gensym))))
	(thread-name (format nil "thread-test-~s" (gensym)))
	(run-time (coerce time-period 'double-float)))
    `(let ((pname ,func))
       (setf *stop* nil)
       (ccl::defcallback ,timer-callback (:<CFR>un<L>oop<T>imer<R>ef timer (:* t) info)
	 timer info
	 (if *stop*
	     (progn
	       (#_CFRunLoopStop (#_CFRunLoopGetCurrent))
	       (ccl::process-kill ccl::*current-process*))
	   (funcall pname)))
       (ccl::process-run-function ,thread-name
	 (lambda ()
	   (progn
	     (let ((my-timer
		    (#_CFRunLoopTimerCreate (ccl::%null-ptr) (#_CFAbsoluteTimeGetCurrent)
					    1000000000.D0 0 0 ,timer-callback (ccl::%null-ptr))))
	       (setf *global-timer* my-timer)
	       (#_CFRunLoopAddTimer (#_CFRunLoopGetCurrent) my-timer (string->cfstringref "cm"))
	       (#_CFRunLoopRunInMode (string->cfstringref "cm") ,run-time #$false)
	       (#_CFRunLoopTimerInvalidate my-timer)
	       (#_CFRelease my-timer))))))))

(defun run-periodic-task (period)
  (let ((timer-context (%string->cfstringref "cm-periodic")))
    (ccl::defcallback *periodic-polling-callback* (:<CFR>un<L>oop<T>imer<R>ef timer (:* t) info)
      (declare (ignore timer info))
      (if *periodic-polling-function*
	  (funcall *periodic-polling-function*)
	(progn
	  (when *periodic-polling-timer*
	    (#_CFRunLoopStop (#_CFRunLoopGetCurrent)))
	  (when *periodic-polling-thread*
	    (ccl::process-kill *periodic-polling-thread*)))))
    (setf *periodic-polling-thread*
	  (ccl::process-run-function "periodic-polling-thread"
	    (lambda ()
	      (setf *periodic-polling-timer*
		    (#_CFRunLoopTimerCreate (ccl::%null-ptr) (#_CFAbsoluteTimeGetCurrent)
					    (* .001D0 period)  0 0 *periodic-polling-callback* (ccl::%null-ptr)))
	      (#_CFRunLoopAddTimer (#_CFRunLoopGetCurrent) *periodic-polling-timer* timer-context)
	      (#_CFRunLoopRunInMode timer-context 10000000.D0 #$false)
	      (#_CFRunLoopTimerInvalidate *periodic-polling-timer*)
	      (#_CFRelease *periodic-polling-timer*)
	      (%release-cfstring timer-context))))))


(defun set-periodic-task! (thunk &key (period 1) (mode ':set))
  ;;period is in milliseconds
  (declare (ignore mode))
  (cond ((not thunk) 
	 (setf *periodic-polling-function* nil))
	((not (null *periodic-polling-function*))
	 (error "set-periodic-task!: Periodic task already running!"))
	(t
	 (setf *periodic-polling-function* thunk)
	 (run-periodic-task period)))
  (values))
#|
(set-periodic-task! #'(lambda () (print (get-internal-real-time))) :period 1000)
(set-periodic-task! nil)
(set-periodic-task! #'(lambda () (print (get-internal-real-time))) :period 100)
(set-periodic-task! nil)
(set-periodic-task! #'(lambda () (print (get-internal-real-time))) :period 10)
;generate error
(set-periodic-task! #'(lambda () (print (get-internal-real-time))) :period 1)
(set-periodic-task! nil)
(set-periodic-task! #'(lambda () (print (get-internal-real-time))) :period 1)

|#




    
	     
	
  

