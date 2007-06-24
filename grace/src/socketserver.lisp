;;; **********************************************************************
;;; Copyright (C) 2007 Todd Ingalls, Rick Taube.
;;; This program is free software; you can redistribute it and/or modify
;;; it under the terms of the Lisp Lesser Gnu Public License. The text of
;;; this agreement is available at http://www.cliki.net/LLGPL            
;;; **********************************************************************

;;; $Name$
;;; $Revision$
;;; $Date$

(in-package cl-user)

;;;
;;; message constants, must be same as Lisp.cpp !!
;;;

(defconstant +msgBinaryData+ 0)
(defconstant +msgLispEval+ 1)
(defconstant +msgSalEval+ 2)
(defconstant +msgError+ 3)
(defconstant +msgWarning+ 4)
(defconstant +msgPrintout+ 5)
(defconstant +msgValues+ 6)
(defconstant +msgKillLisp+ 7)

;;; capture these if we want to explicitly send to them
;;; for debugging

(defparameter *lisp-standard-input* *standard-input*)
(defparameter *lisp-standard-output* *standard-output*)
(defparameter *lisp-terminal-io* *terminal-io*)
(defparameter *lisp-debug-io* *debug-io*)
(defparameter *lisp-error-output* *error-output*)
(defparameter *lisp-query-io* *query-io*)

;;

#+sbcl
(eval-when (:compile-toplevel :load-toplevel :execute)
  (require :sb-bsd-sockets)
  (require :sb-posix))

(defun read-u32 (stream)
  (let ((u 0))
    ;; this will suffer from os/endian nonsense.
    (loop  for i from 0 to 3
       do (setq u (+ u (ash (read-byte stream) (* 8 i)))))
    u))
  
(defun write-u32 (u32 stream)
  (loop for i from 0 to 3
     do (write-byte (ldb (byte 8 (* i 8)) u32)
		    stream))
  u32)

;;;
;;; 
;;;

(defclass connection ()
  ((serve? :initarg :serve? :accessor connection-serve?)
   (binary? :initarg :binary? :accessor connection-binary?)
   (stream :initarg :stream :accessor connection-stream)
   (socket :initarg :socket :accessor connection-socket)
;;   (reader :initarg :reader :accessor connection-reader)
;;   (evaler :initarg :evaler :accessor connection-evaler)
;;   (sender :initarg :sender :accessor connection-sender)
   ))

(defgeneric close-connection (obj))
(defgeneric connection-open? (con))

(defun ipaddr->dotted (addr)
  #+openmcl (ccl:ipaddr-to-dotted addr)
  #+sbcl (format nil "~d.~d.~d.~d" (aref addr 0) (aref addr 1)
		 (aref addr 2) (aref addr 3))
  #-(or openmcl sbcl)
  (if (numberp addr)
      (format nil "~d.~d.~d.~d"
	      (logand #xff (ash addr -24))
	      (logand #xff (ash addr -16))
	      (logand #xff (ash addr -8))
	      (logand #xff addr))
      addr))

(defun getpid () 
  #+openmcl (ccl::getpid)
  #+sbcl (sb-posix:getpid)
  #+(and clisp (not win32))
  (system::process-id)
  #+(and clisp win32) 
  (funcall (find-symbol "GetCurrentProcessId" :win32))
  )


(defun kill-lisp ()
  #+sbcl (sb-ext:quit)
  #+openmcl (ccl:quit)
  #+clisp (ext:quit))

(defgeneric connection-local-port (obj))
(defgeneric connection-remote-port (obj))
(defgeneric connection-remote-host (obj))

(defmethod connection-local-port ((obj connection))
  (let ((sock (connection-socket obj)))
    sock
    #+openmcl (ccl:local-port sock)
    #+sbcl (multiple-value-bind (lh lp)	
	       (sb-bsd-sockets:socket-name sock)
	     lh lp)
    #+clisp
    (socket:socket-stream-port (connection-stream obj))))

(defmethod connection-remote-port ((obj connection))
  (let ((sock (connection-socket obj)))
    #+openmcl (ccl:remote-port sock)
    #+sbcl (multiple-value-bind (rh rp)	
	       (sb-bsd-sockets:socket-peername sock)
	     rh rp)
    #+clisp (multiple-value-bind (rh rp)
		(socket:socket-stream-peer (connection-stream obj))
	      sock
	      rh rp)
    ))

(defmethod connection-remote-host ((obj connection))
  (let ((sock (connection-socket obj)))
    #+openmcl
    (ipaddr->dotted (ccl:remote-host sock))
    #+sbcl (multiple-value-bind (rh rp)	
	       (sb-bsd-sockets:socket-peername sock)
	     rp 
	     (ipaddr->dotted rh))
    #+clisp
    (multiple-value-bind (rh rp)
	(socket:socket-stream-peer (connection-stream obj))
      sock
      rp rh)
    ))

(defmethod print-object ((obj connection) stream)
  (if (slot-boundp obj 'socket)
      (let (lh lp rh rp)
	#+openmcl
	(let ((sock (connection-socket obj)))
	  (setq lh (ccl:local-host sock)
		lp (ccl:local-port sock)
		rh (ccl:remote-host sock)
		rp (ccl:remote-port sock)))
	#+sbcl
	(let ((sock (connection-socket obj) ))
	  (multiple-value-setq (lh lp)
	    (sb-bsd-sockets:socket-name sock))
	  (if (not (connection-serve? obj))
	      (multiple-value-setq (rh rp)
		(sb-bsd-sockets:socket-peername sock))))
	#+clisp
	(let ((sock (connection-stream obj)))
	  (setq lh (socket:socket-stream-host sock))
	  (setq lp (socket:socket-stream-port sock))
	  (setq rh 0 rp 0))
	(if (connection-serve? obj)
	    (format stream "#<server [port ~d]>" lp)
	    (format stream
		    "#<client ~a:~d -> ~a:~d]>"
		    (ipaddr->dotted lh) lp (ipaddr->dotted rh) rp)))
      (format stream "#<connection [closed]>")))

(defun connection-read (standard-out warn-out error-out string errform)
  (let (form)
    warn-out standard-out
 ;;   (setf *standard-output* standard-out)
 ;;   (setf *error-output* warn-out) ; really where warn goes
    (handler-case
	(progn
	  (FORMAT *lisp-standard-output* "reading: ~S~%" string)
	  (FORCE-OUTPUT *lisp-standard-output*)	  
	  (setq form (read-from-string string)))
      (error (c)
	(progn
	  (format error-out ">>> Lisp error (READ) :~%    ~A"
		  c)
	  (force-output error-out)
	  (setq form errform))))
    (FORMAT *lisp-standard-output* "form: ~S~%" form)
    (FORCE-OUTPUT *lisp-standard-output*)
    form))

#|
DOESNTWORK
(defun connection-eval (standard-out warn-out error-out values-out form)
  (let (vals)
    ;;standard-output-stream should be same as *standard-output*
    ;;but let's make it explicit
    warn-out standard-out
;;    (setf *standard-output* standard-out)
;;    (setf *error-output* warn-out) ; really where warn goes

    (FORMAT *lisp-standard-output* "evaling: ~S~%" form)
    (FORCE-OUTPUT *lisp-standard-output*)
    (handler-bind ((error (lambda (c)
			    (let ((str (format nil "Lisp error (EVAL): ~s~%" c))
				  )
			      (FORMAT *lisp-standard-output* "caught error: ~a~%" c)
			      (FORCE-OUTPUT *lisp-standard-output*)
			      (FORMAT *lisp-standard-output* "error-out: ~s~%" error-out)
			      (format error-out str)
			      (force-output error-out)))))
      (setq +++ ++ ++ + + form)
      (setq vals (multiple-value-list (eval form)))
      (setq *** ** ** * * (car vals))
      (force-output standard-out)
      (force-output warn-out)
      (when vals
	(FORMAT *lisp-standard-output* "sending: ~S~%" vals)
	(FORCE-OUTPUT *lisp-standard-output*)
	(dolist (v vals) (pprint v values-out))
	(force-output values-out)
	))
    (values)))
|#

	   
(defun connection-eval (standard-out warn-out error-out values-out form)
  (let ()
    ;;standard-output-stream should be same as *standard-output*
    ;;but let's make it explicit
    warn-out standard-out
    (FORMAT *lisp-standard-output* "evaling: ~S~%" form)
    (FORCE-OUTPUT *lisp-standard-output*)
    (handler-case (multiple-value-list (eval form))
      (error (c)
	(let ((str (format nil ">>> Lisp error (EVAL): ~A~%" c))
	      )
	  (FORMAT *lisp-standard-output* "caught error: ~a~%" c)
	  (FORCE-OUTPUT *lisp-standard-output*)
	  (format error-out str)
	  (force-output error-out)))
      (:no-error (vals)
	(setq +++ ++ ++ + + form)
	(setq *** ** ** * * (car vals))
	(force-output standard-out)
	(force-output warn-out)
	(when vals
	  (FORMAT *lisp-standard-output* "sending: ~S~%" vals)
	  (FORCE-OUTPUT *lisp-standard-output*)
	  (dolist (v vals) (pprint v values-out))
	  (force-output values-out)
	  ))
      )
    ))

; (progn (defparameter *lisp-standard-output* *standard-output*)(defparameter s *standard-output*))
; (connection-eval s s s s '(define asd ()))



;;; this is a gray stream for standard output to send back to grace
;;; this merely wraps around the instance of stream in connection 

(defclass connection-character-output-stream
    (fundamental-character-output-stream)
  ((binary-stream :initform nil :initarg :binary-stream 
		  :accessor binary-stream)
   (message-type :initarg :message-type :accessor message-type)
   (byte-buffer :initform (make-array 8192 :element-type
				      '(unsigned-byte 8)) 
		:accessor byte-buffer)
   (buffer-index :initform 0 :accessor buffer-index)))

(defgeneric send-output-buffer (stream))

(defmethod send-output-buffer ((stream connection-character-output-stream))
  (let ((binary-stream (binary-stream stream))
	(length (buffer-index stream)))
    (write-u32 (message-type stream) binary-stream)
    (write-u32 length binary-stream)
    (loop for i below length
       do (write-byte (aref (byte-buffer stream) i) binary-stream))
    (setf (buffer-index stream) 0)))

(defmethod stream-write-char ((stream connection-character-output-stream)
			      char)
  (setf (aref (byte-buffer stream) (buffer-index stream)) 
	(char-code char))
  (incf (buffer-index stream))
  char)

(defmethod stream-line-column ((stream connection-character-output-stream))
  nil)

(defmethod stream-start-line-p ((stream connection-character-output-stream))
  nil)

(defmethod stream-write-string ((stream connection-character-output-stream) 
				string &optional start (end (length string)))
  (loop for i from start below end
       do
       (stream-write-char stream (elt string i)))
  string)

(defmethod stream-terpri ((stream connection-character-output-stream))
  (stream-write-char stream #\newline)
  nil)

(defmethod stream-fresh-line  ((stream connection-character-output-stream))
  (stream-write-char stream #\newline)
  nil)

(defmethod stream-force-output ((stream connection-character-output-stream))
  (let ((binary-stream (binary-stream stream)))
    (send-output-buffer stream)
    (force-output binary-stream)
    (setf (buffer-index stream) 0)
  nil))

(defmethod stream-finish-output
    ((stream connection-character-output-stream))
  (force-output stream)
  nil)

(defmethod stream-advance-to-column
    ((stream  connection-character-output-stream) column)
  column
  nil)

(defmethod stream-clear-output
    ((stream connection-character-output-stream))
  (let ((binary-stream (binary-stream stream)))
    (clear-output binary-stream)
    (setf (buffer-index stream) 0)
    nil))

#|
;;; subclass of connection-character-output-stream used for errors 
;;; really doesn't need to be a subclass at this point. could
;;; set message-type with slot, but could be useful in future
(defclass connection-error-output-stream 
    (connection-character-output-stream)
  ((binary-stream :initform nil :initarg :binary-stream 
		  :accessor binary-stream)
   (byte-buffer :initform (make-array 8192 :element-type
				      '(unsigned-byte 8))
		:accessor byte-buffer)
   (buffer-index :initform 0 :accessor buffer-index)))
(defmethod send-output-buffer ((stream connection-error-output-stream))
  (let ((binary-stream (binary-stream stream))
	(length (buffer-index stream)))
    (write-u32 +msgError+ binary-stream)
    (write-u32 length binary-stream)
    (loop for i below length
       do (write-byte (aref (byte-buffer stream) i) binary-stream))
    (setf (buffer-index stream) 0)))
;;; subclass of connection-character-output-stream used for warnings
(defclass connection-warn-output-stream (connection-character-output-stream)
  ((binary-stream :initform nil :initarg :binary-stream 
		  :accessor binary-stream)
   (byte-buffer :initform 
		(make-array 8192 :element-type '(unsigned-byte 8))
		:accessor byte-buffer)
   (buffer-index :initform 0 :accessor buffer-index)))
(defmethod send-output-buffer ((stream connection-warn-output-stream))
  (let ((binary-stream (binary-stream stream))
	(length (buffer-index stream)))
    (write-u32 +msgWarning+ binary-stream)
    (write-u32 length binary-stream)
    (loop for i below length
       do (write-byte (aref (byte-buffer stream) i) binary-stream))
    (setf (buffer-index stream) 0)))
|#

(defun open-server-connection (port &key (bin t))
  ;; tell (local) caller we are ready to connect. open socket/stream
  ;; on port and wait for client, return a connection object holding
  ;; stream and socket
  (let (socket stream)
    #+openmcl
    (progn
      (setq socket (ccl:make-socket :connect ':passive :type ':stream
				    :reuse-address t :local-port port
				    :format (if bin :binary :text)))
      (setq stream (ccl:accept-connection socket :wait t)))
    #+sbcl
    (progn
      (setq socket (make-instance 'sb-bsd-sockets:inet-socket
				  :type ':stream
				  :protocol ':tcp))
      (setf (sb-bsd-sockets:sockopt-reuse-address socket) t)
      ;; server host is loopback?
      (sb-bsd-sockets:socket-bind socket #(127 0 0 1) port)
      (sb-bsd-sockets:socket-listen socket 5)
      (setq stream (sb-bsd-sockets:socket-make-stream
		    (sb-bsd-sockets:socket-accept socket) 
		    :input t :output t :buffering (if bin :none :line)
		    :element-type
		    (if bin '(unsigned-byte 8) 'character))))
    #+clisp
    (progn
      (setq socket (socket:socket-server port :interface "127.0.0.1"))
      (socket:socket-wait socket)
      (setq stream (socket:socket-accept socket 
					 :element-type
					 (if bin '(unsigned-byte 8) 
					     'character))))
    ;; at this point a socket connection has been made
    (make-instance 'connection
		   :serve? t
		   :stream stream
		   :socket socket)))

(defmethod connection-open? ((obj connection))
  (open-stream-p (connection-stream obj)))

(defun stop-server () (throw :socket-server ':quit))
(defun kill-server () (throw :socket-server ':kill))

(defun serve-connection (connection)
  ;; TODO: fix for threaded lisps like openmcl and sbcl/linux!!
  (let* ((stream (connection-stream connection))
	 (standard-output-stream
	  (make-instance 'connection-character-output-stream 
			 :message-type +msgPrintout+
			 :binary-stream stream))
	 (error-output-stream
	  (make-instance 'connection-character-output-stream
			 :message-type +msgError+
			 :binary-stream stream))
	 (warn-output-stream
	  (make-instance 'connection-character-output-stream
			 :message-type +msgWarning+
			 :binary-stream stream))
	 (values-output-stream
	  (make-instance 'connection-character-output-stream
			 :message-type +msgValues+
			 :binary-stream stream))
	 )
;;    (setf *error-output* error-output-stream)
;;    (setf *standard-output* standard-output-stream)
    (flet ((serve ()
	     (catch :socket-server
	       (let* ((binary-confirmation-message 
		       (loop for i across "binary message" 
			  collect (char-code i)))
		      (confirmation-bytes 
		       (make-array (length binary-confirmation-message)
				   :initial-contents 
				   binary-confirmation-message
				   :element-type '(unsigned-byte 8)))
		      (error-value (gensym))
		      (*error-output* warn-output-stream)
		      (*standard-output* standard-output-stream)
		      message-type length string sexpr value byte-vector)
		 message-type length string sexpr value byte-vector
		 (format *lisp-standard-output* "standard-output: ~s~%error-output: ~s~%warn-output: ~s~%values-output: ~s~%" standard-output-stream error-output-stream warn-output-stream
			 values-output-stream)
		 (force-output *lisp-standard-output*)
		 (loop 
		    (handler-case
			;; handle broken connection
			(progn
			  (setq message-type (read-u32 stream))
			  (setq length (read-u32 stream)))
		      (error (c) 
			(format *lisp-standard-output*
				"; Unexpected stream error or EOF: ~A."
				c)
			(kill-server)))
		    (format *lisp-standard-output*
			    "lisp receiving: message-type=~S, length=~S~%"
			    message-type length)
		    (cond 
		      ((= message-type +msgLispEval+)
		       (setq string (make-string length))
		       (loop for i below length
			  do (setf (elt string i)
				   (code-char (read-byte stream))))
		       (setq sexpr (connection-read standard-output-stream
						    warn-output-stream
						    error-output-stream
						    string
						    error-value))
		       (unless (eql sexpr error-value)
			 (connection-eval standard-output-stream 
					  warn-output-stream 
					  error-output-stream
					  values-output-stream
					  sexpr)))
		      ((= message-type +msgSalEval+)
		       )
		      ((= message-type +msgBinaryData+)
		       (progn
			 (setq byte-vector 
			       (make-array length :element-type 
					   '(unsigned-byte 8)))
			 (loop for i below length
			    do (setf (aref byte-vector i)
				     (read-byte stream)))
			 (format *lisp-standard-output* 
			       "Lisp received binary message: '~S'~%"
			       byte-vector)
			 (format *lisp-standard-output* 
			       "Lisp sending confirmation bytes: '~S'~%"
			       confirmation-bytes)
		       (setq length (length confirmation-bytes))
		       (write-u32 +msgBinaryData+ stream)
		       (write-u32 length stream)
		       (write-sequence confirmation-bytes stream)
		       (force-output stream)))
		      ((= message-type +msgKillLisp+)
		       (format *lisp-standard-output* "KILLING LISP.~%")
		       (kill-server))
		      (t (format *lisp-standard-output*
				 "Lisp unknown message-type: '~S'~%" 
				 message-type))))))))
	   (let (res)
	     (unwind-protect
		  (setq res (serve ))
	       ;;set outputs back to lisp
;;	       (setf *standard-output* *lisp-standard-output*)
;;	       (setf *error-output* *lisp-error-output*)
	       ;close streams
	       (close standard-output-stream)
	       (close error-output-stream)
	       (close warn-output-stream)
	       (close values-output-stream)

	       (close-connection connection)

	       (format *lisp-standard-output* "; Connection closed.~%")
	       (force-output t)
	       (if (eql res ':kill)
		   (kill-lisp)))))))

(defun start-server (port pollfile)
  ;; write polling file to tell (localhost) caller that connection is
  ;; ready.
  (with-open-file (s pollfile :direction :output
                     :if-exists :error :if-does-not-exist :create)
    (format s "~S~{ ~S~}~%" (getpid) *features*))
  (let ((con (open-server-connection port)))
    (format *lisp-standard-output*
	    "; started socket server: port=~d, pid=~d~%"
	    (connection-local-port con) (getpid))
    (force-output t)
    (serve-connection con)))


(defun close-socket (socket)
  ;; do i need this? (sb-sys:invalidate-descriptor (socket-fd socket))
  #+sbcl
  (sb-bsd-sockets:socket-close socket)
  #+openmcl
  (close socket)
  #+clisp
  (socket:socket-server-close socket)
  (values))

(defmethod close-connection ((obj connection))
  (close (connection-stream obj))
  ;; openmcl client: stream and socket are the same but recolsing
  ;; doesnt hurt
  (close-socket (connection-socket obj))
  #+clisp
  (if (connection-serve? obj)
      (close-socket (connection-socket obj)))
  (values))

;;;
;;; client side (used for testing)
;;;

(defun open-connection (host port &optional (bin t))
  ;; open connection to (server) host on port
  (let (socket stream)
  #+openmcl
  (progn
    (setq socket (ccl:make-socket :remote-host host :remote-port port
				  :format (if bin :binary :text)))
    (setq stream socket))
  #+sbcl
  (progn
    (setq socket (make-instance 'sb-bsd-sockets:inet-socket
				:type :stream :protocol :tcp))
    (sb-bsd-sockets:socket-connect socket 
				   (sb-bsd-sockets::host-ent-address
				    (sb-bsd-sockets:get-host-by-name
				     host))
				   port)
    (setq stream (sb-bsd-sockets:socket-make-stream 
			    socket :input t :output t
			    :buffering (if bin :none :line)
			    :element-type
			    (if bin '(unsigned-byte 8) 'character))))
  #+clisp
  (progn 
    (setq socket (socket:socket-connect port host
					:element-type
					(if bin '(unsigned-byte 8)
					    'character)))
    (setq stream socket))
  (make-instance 'connection 
		 :serve? nil
;;		 :reader (function connection-read)
;;		 :sender (function connection-print)
;;		 :evaler (function connection-eval)
		 :stream stream :socket socket)))



