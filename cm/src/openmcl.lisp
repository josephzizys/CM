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
  (require "pascal-strings")
  )

(pushnew :metaclasses *features*)

(import '(ccl:slot-definition-name 
          ccl:slot-definition-initargs 
          ccl:slot-definition-initform 
          ccl:class-direct-superclasses
          ccl:class-direct-subclasses
          ccl:open-shared-library ; needed if loading clm into cm.
          ccl:without-interrupts ; for testing realtime
	  ;ccl::pref ;for openmcl ffi
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

(defun env-var (var)
  (ccl::getenv (string var)))

(defun set-env-var (var val)
  (ccl::setenv (string var) val))

;;;
;;; cm application classes
;;; 

(defclass cm-application (ccl::lisp-development-system) ())
(defclass cm-carbon-application (cm-application) ())

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

(defmethod ccl::application-version-string ((a cm-application))
  (cm-version))

(defmethod ccl:toplevel-function ((app cm-application) init-file)
  (declare (ignore init-file))
  (call-next-method))

(defparameter *cm-swank-port* nil)

(defmethod ccl:toplevel-function ((app cm-carbon-application) init-file)
  (declare (ignore init-file) (special *cm-readtable*))
;;  (setf *package* (find-package :cm))
;;  (setf *readtable* *cm-readtable*)
;;  (load-cminit)
;;  (cm-logo)
  (when (and *cm-swank-port* (find-package ':swank))
    (funcall (find-symbol "CREATE-SERVER" ':swank)
             :port *cm-swank-port*))
  (ccl::with-pstrs ((msg "Hello from CM!"))
    (#_StandardAlert #$kAlertNoteAlert msg
                     (ccl:%null-ptr) (ccl:%null-ptr) (ccl:%null-ptr)))
  (#_RunApplicationEventLoop)
  (ccl:quit))

(defun cm-image-dir ()
  (namestring
   (make-pathname
    :directory (pathname-directory ccl::*heap-image-name*))))

(defun save-cm (&optional path &rest args &key carbon slime-directory 
			  swank-port)
  ;; if user calls this function, path is path directory to save app in.
  ;; else (called by make-cm) path is  cm/bin/openmcl*/cm.image
  (declare (ignore args) (special *cm-readtable*))
  (let* ((cmroot (symbol-value 'cl-user::*cm-root*))
         (appdir (cond ((and (not path)
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
         (etcdir (merge-pathnames "Contents/Resources/etc/" bundle))
         (libdir (merge-pathnames "Contents/Resources/lib/" bundle))
         (exedir (merge-pathnames "Contents/MacOS/" bundle)))
    (unless (probe-file bundle)
      (ccl:create-directory bundle)
      (ccl:create-directory resdir)
      (ccl:create-directory exedir)
      (ccl:create-directory libdir)
      (ccl:create-directory etcdir))
    ;; CM.app/info.plist
    (create-info.plist (merge-pathnames "Contents/Info.plist" bundle)
                       carbon)
    ;; cm/etc/xemacs -> Contents/Resources/etc/*.el
    (ccl:copy-file (merge-pathnames "etc/xemacs/listener.el" cmroot)
                   (merge-pathnames "listener.el" etcdir)
                   :if-exists :supersede)
    (ccl:copy-file (merge-pathnames "etc/xemacs/cm.el" cmroot)
                   (merge-pathnames "cm.el" etcdir)
                   :if-exists :supersede)
    ;; dppccl->MacOS/cm
    (ccl:copy-file (car ccl::*command-line-argument-list*)
                   (merge-pathnames "cm" exedir)
                   :if-exists :supersede)
    (create-cm.sh (merge-pathnames "cm.sh" exedir))
    (if carbon
      (carbon-setup slime-directory swank-port)
      (normal-setup))
    (ccl:save-application (merge-pathnames "cm.image" exedir)
                          :application-class *cm-application-class*)))

(defun normal-setup ()
  (setf ccl::*inhibit-greeting* t)
    (setf ccl:*lisp-startup-functions*
        (append ccl:*lisp-startup-functions*
                (list #'(lambda ()
                          (declare (special *cm-readtable*))
                          (setf *package* (find-package :cm))
                          (setf *readtable* *cm-readtable*)
                          (load-cminit)
                          (cm-logo) )))))

(defun carbon-setup (slime-directory swank-port)
  (setf *cm-application-class* (find-class 'cm-carbon-application))
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
      (error "save-cm: :swank-port specified but swank is not loaded. Specify :slime-directory to load it."))
    (setf *cm-swank-port* swank-port)))

(defun create-info.plist (path carbon?)
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
	<string>~A</string>
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
" (if carbon? "cm" "cm.sh"))))

(defun create-cm.sh (path)
  (with-open-file (fil path :direction :output :if-does-not-exist :create
                       :if-exists :supersede)
    (format fil
"#!/bin/sh 
CWD=\"`(cd \\\"\\`dirname \\\\\\\"$0\\\\\\\"\\`\\\"; echo $PWD)`\"
RES=\"`dirname \\\"$CWD\\\"`/Resources\"
EDITOR=`defaults read -app CM editor 2>/dev/null`
export \"DISPLAY=:0.0\"
if [[ ! $EDITOR || $EDITOR == Emacs ]] ; then
    EDITOR=\"/Applications/Emacs.app/Contents/MacOS/Emacs\"
fi

if [ -f \"$EDITOR\" ] ; then
    \"$EDITOR\" -l \"${RES}/etc/listener.el\" -l \"${RES}/etc/cm.el\" --eval \"(lisp-listener \\\"${CWD}/cm --image-name ${CWD}/cm.image\\\" )\"
else
    open -a Terminal \"${CWD}/cm\"
fi

#EOF
"))
  (shell (format nil "chmod a+x ~A" (namestring path)))
  )

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


;; current receive-from in openmcl will block until 
;; it receives data. this method will return nil
;; if no data ready.
(defmethod receive-from-no-block ((socket ccl::udp-socket) size &key buffer extract offset)
  (let ((fd (ccl::socket-device socket))
	(vec-offset offset)
	(vec buffer)
	(ret-size -1))
    (when vec
      (multiple-value-setq (vec vec-offset)
	(ccl::verify-socket-buffer vec vec-offset size)))
    (ccl::rlet ((sockaddr :sockaddr_in)
	   (namelen :signed))
      (setf (ccl::pref sockaddr :sockaddr_in.sin_family) #$AF_INET)
      (setf (ccl::pref sockaddr :sockaddr_in.sin_addr.s_addr) #$INADDR_ANY)
      (setf (ccl::pref sockaddr :sockaddr_in.sin_port) 0)
      (setf (ccl::pref namelen :signed) (ccl::record-length :sockaddr_in))
      (ccl::%stack-block ((bufptr size))
	(setq ret-size (#_recvfrom fd bufptr size 0 sockaddr namelen))
	(print ret-size)
	(when (> ret-size 0)
	  (unless vec
	    (setq vec (make-array ret-size
				  :element-type
				  (ecase (ccl::socket-format socket)
				    ((:text) 'base-character)
				    ((:binary :bivalent) '(unsigned-byte 8))))
		  vec-offset 0))
	  (ccl::%copy-ptr-to-ivector bufptr 0 vec vec-offset ret-size)))
      (if (> ret-size 0)
	  (values (cond ((null buffer)
			 vec)
			((or (not extract)
			     (and (eql 0 (or offset 0))
				  (eql ret-size (length buffer))))
			 buffer)
			(t 
			 (subseq vec vec-offset (+ vec-offset ret-size))))
		  ret-size
		  (#_ntohl (ccl::pref sockaddr :sockaddr_in.sin_addr.s_addr))
		  (#_ntohs (ccl::pref sockaddr :sockaddr_in.sin_port)))
	(values nil nil nil nil)))))

(defun socket-recv (sock bytes &optional flags)
  flags
  (receive-from-no-block sock bytes))

(defun socket-recvfrom (sock bytes &optional flags)
  flags
  (multiple-value-bind (buf num-bytes ip port)
      (receive-from-no-block sock bytes)
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

(defvar *periodic-tasks* (list ))
(defparameter *max-event-to-sec*  0)
(defparameter *max-event-to-usec* 1000)
(defparameter *periodic-polling-function* nil)
(defparameter *periodic-polling-timer* nil)
(defparameter *periodic-polling-thread* nil)
(defparameter *periodic-polling-callback* nil)

(defun %string->cfstringref (string)
  (ccl::with-cstrs ((str string))
    (#_CFStringCreateWithCString (ccl::%null-ptr) str
                                 #$kCFStringEncodingMacRoman)))

(defun %release-cfstring (string)
  (#_CFRelease string))

(defun set-periodic-task-rate! (rate meas)
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
	(setf *max-event-to-sec* sec)
        (setf *max-event-to-usec* (floor (* rem (/ 1000000 divs)))))
      (values))))

(defun periodic-task-rate ()
  (+ (* *max-event-to-sec* 1000000)
     *max-event-to-usec*))

(defun run-periodic-tasks ()
  (dolist (e *periodic-tasks*) (funcall (cdr e)))
  (values))


(defun run-periodic-tasks ()
  (let ((timer-context (%string->cfstringref "cm-periodic")))
    (ccl::defcallback *periodic-polling-callback*
      (:<CFR>un<L>oop<T>imer<R>ef timer (:* t) info)
      (declare (ignore timer info))
      (if *periodic-tasks*
          (dolist (e *periodic-tasks*) (funcall (cdr e)))
	(progn
	  (#_CFRunLoopStop (#_CFRunLoopGetCurrent))
	  (ccl::process-kill *periodic-polling-thread*))))
    (setf *periodic-polling-thread*
	  (ccl::process-run-function "periodic-polling-thread"
	    (lambda ()
	      (ccl::external-call "_CFRunLoopGetCurrent" :address)
	      (ccl::external-call "__CFRunLoopSetCurrent" :address (ccl::external-call "_CFRunLoopGetMain" :Address)) 
	      (ccl::%stack-block ((psn 8))
				 (ccl::external-call "_GetCurrentProcess" :address psn)
				 (ccl::with-cstrs ((name "cm rt"))
				   (ccl::external-call "_CPSSetProcessName" :address psn :address name)))
	      
	      (setf *periodic-polling-timer*
		    (#_CFRunLoopTimerCreate (ccl::%null-ptr) (#_CFAbsoluteTimeGetCurrent) 
					    (coerce (+ *max-event-to-sec* (/ *max-event-to-usec* 1000000)) 'double-float)
                                            0 0 *periodic-polling-callback* (ccl::%null-ptr)))
	      (#_CFRunLoopAddTimer (#_CFRunLoopGetCurrent)
                                   *periodic-polling-timer* timer-context)
	      (#_CFRunLoopRunInMode timer-context 10000000.D0 #$false)
	      (#_CFRunLoopTimerInvalidate *periodic-polling-timer*)
	      (#_CFRelease *periodic-polling-timer*)
	      (%release-cfstring timer-context))))))

(defun periodic-task-running? (&optional owner)
  (if *periodic-tasks*
      (if owner 
	  (and (assoc owner *periodic-tasks* :test #'eq) t)
	t)
    nil))

(defun add-periodic-task! (owner task)
  (cond ((null *periodic-tasks*)
         (push (cons owner task) *periodic-tasks*)
         (setf *periodic-polling-function* #'run-periodic-tasks)
	 (funcall *periodic-polling-function* ))
        ((assoc owner *periodic-tasks* :test #'eq)
         (error "add-periodic-task!: task already running for ~s."
                owner))
        (t
         (push (cons owner task) *periodic-tasks*)))
  (values))

(defun remove-periodic-task! (owner)
  (if (eq owner t)
      (setf *periodic-polling-function* nil
            *periodic-tasks* (list))
      (let ((e (assoc owner *periodic-tasks* :test #'eq)))
        (cond ((null e)
               (error "remove-periodic-task!: No task for owner ~s."
                      owner))
              (t
               (setf *periodic-tasks* (delete e *periodic-tasks*))
               (if (null *periodic-tasks*)
                   (setf *periodic-polling-function* nil))))))
  (values))
  

#|
(periodic-task-running?)
(set-periodic-task-rate! 1000 :ms) ; milliseconds
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

(defun u8vector->double (vec)
  (ccl::%stack-block ((d 8))
     (dotimes (i 8)
      (ccl::%put-byte d (aref vec i) i))
    (ccl::%get-double-float d)))


(defun parse-osc (arr)
  (let ((lst (list))
	(pos nil)
	(first-token-len nil)
	(type-list-len nil)
	(sym-vector nil)
	(sym nil)
	(sym-len 0)
	(type-list (list)))
    (setf first-token-len (position 0 arr))
    (if first-token-len
	(let ((mess (list)))
	  (setf lst (append lst (list 
				 (intern 
				       (string-upcase 
					       (string-trim "/" (coerce (loop for i across (subseq arr 0 first-token-len)
							       collect (code-char i)) 'string))) :cm))))
	  (setf mess (subseq arr (position 44 arr)))
	  (setf type-list (mapcar #'code-char (coerce (subseq mess 0 (position 0 mess)) 'list)))
	  (setf type-list-len (length type-list))
	  (setf mess (subseq mess (+ type-list-len (- 4 (mod type-list-len 4)))))
	  (setf pos 0)
	  (dolist (j type-list)
	    (cond ((eq j #\i)
		   (setf lst (append lst (list (subseq mess pos (+ pos 4)))))
		   (setf pos (+ pos 4)))
		  ((eq j #\f)
		   (setf lst (append lst (list (subseq mess pos (+ pos 4)))))
		   (setf pos (+ pos 4)))
		  ((eq j #\d)
		   (setf lst (append lst (list (subseq mess pos (+ pos 8)))))
		   (setf pos (+ pos 8)))
		  ((eq j #\s)
		   (setf sym-vector (subseq mess pos))
		   (setf sym-vector (subseq sym-vector pos (position 0 sym-vector)))
		   (print (list sym-vector (subseq mess pos)))
                   (setf sym (coerce (loop for i across sym-vector collect (code-char i)) 'string))
                   (setf lst (append lst (list (string-trim "/" (string-right-trim '(#\newline) sym)))))
                   (setf sym-len (length sym))
                   (if (= 0 (mod sym-len 4))
                       (setf pos (+ pos sym-len))
                     (setf pos (+ (+ sym-len (- 4 (mod sym-len 4))) pos)))))))
      (setf lst (append lst (list 
				 (intern 
				       (string-upcase 
					       (string-trim "/" (coerce (loop for i across (subseq arr 0 first-token-len)
									      collect (code-char i)) 'string))) :cm)))))
    lst))


(defmacro with-mutex-grabbed ((mutex) &body body)
  `(ccl::with-lock-grabbed (,mutex)
			   ,@body))

