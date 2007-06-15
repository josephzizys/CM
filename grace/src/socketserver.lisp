; TERMINAL #1:
;   sbcl --load "socketserver" --eval '(start-server 8000)'

; TERMINAL #2: (first wait a bit because sbcl requires lib loading...)
;   openmcl --load "socketserver" --eval '(defparameter c (open-connection "localhost" 8000))'
;   (servlisp c (list 1 2 3))
;   (servlisp c (+ 3 4 5))
;   (servlisp c (defun foo (a) (* a a)))
;   (servlisp c (foo 33))
;   (connection-send c '(stop-server))
;   (close-connection c)

(in-package cl-user)


;;; messags types
(defparameter *msgString* 0)
(defparameter *msgBinaryData* 1)
(defparameter *msgError* 2)
(defparameter *msgWarning* 3)
(defparameter *msgPrintout* 4)


;;; capture these if we want to explicitly send to them
;;; for debugging

(defparameter *lisp-standard-input* *standard-input*)
(defparameter *lisp-standard-output* *standard-output*)
(defparameter *lisp-terminal-io* *terminal-io*)
(defparameter *lisp-debug-io* *debug-io*)
(defparameter *lisp-error-output* *error-output*)
(defparameter *lisp-query-io* *query-io*)

;;

#+sbcl (require :sb-bsd-sockets)
#+sbcl (require :sb-posix)

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



(defclass connection ()
  ((serve? :initarg :serve? :accessor connection-serve?)
   (binary? :initarg :binary? :accessor connection-binary?)
   (stream :initarg :stream :accessor connection-stream)
   (socket :initarg :socket :accessor connection-socket)
   (reader :initarg :reader :accessor connection-reader)
   (evaler :initarg :evaler :accessor connection-evaler)
   (sender :initarg :sender :accessor connection-sender)
   ))

(defgeneric close-connection (obj))
(defgeneric connection-open? (con))

(defun ipaddr->dotted (addr)
  #+openmcl (ccl:ipaddr-to-dotted addr)
  #+sbcl (format nil "~d.~d.~d.~d" (aref addr 0) (aref addr 1)
		 (aref addr 2) (aref addr 3))
  #-(or openmcl sbcl)
  (format nil "~d.~d.~d.~d"
          (logand #xff (ash addr -24)) (logand #xff (ash addr -16))
          (logand #xff (ash addr -8)) (logand #xff addr)))

(defun getpid () 
  #+openmcl (ccl::getpid)
  #+sbcl (sb-posix:getpid)
  #+(and clisp (not win32))
  (system::process-id)
  #+(and clisp win32)
  (win32::GetCurrentProcessId)
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
    #+openmcl (ccl:local-port sock)
    #+sbcl (multiple-value-bind (lh lp)	
	       (sb-bsd-sockets:socket-name sock)
	     lh lp)))

(defmethod connection-remote-port ((obj connection))
  (let ((sock (connection-socket obj)))
    #+openmcl (ccl:remote-port sock)
    #+sbcl (multiple-value-bind (rh rp)	
	       (sb-bsd-sockets:socket-peername sock)
	     rh rp)))

(defmethod connection-remote-host ((obj connection))
  (let ((sock (connection-socket obj)))
    #+openmcl
    (ipaddr->dotted (ccl:remote-host sock))
    #+sbcl (multiple-value-bind (rh rp)	
	       (sb-bsd-sockets:socket-peername sock)
	     rp 
	     (ipaddr->dotted rh))))

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
	(if (connection-serve? obj)
	    (format stream "#<server connection [port ~d]>" lp)
	    (format stream
		    "#<client connection [localhost ~a port ~d] [remotehost ~a port ~d]>"
		    (ipaddr->dotted lh) lp (ipaddr->dotted rh) rp)))
      (format stream "#<connection [closed]>")))

;;
;; these routines read and write to open connecton. they need error
;; handlers that trap errors and return error messages back to grace
;;

(defun connection-format (connection fmat &rest args)
  (let ((stream (connection-stream connection)))
    (apply #'format (connection-stream connection) fmat args)
    ;;(finish-output stream) ; is this what i should use?
    (force-output stream)
    (values)))

(defun connection-error (connection fmat &rest args)
  (let ((stream (connection-stream connection)))
    (apply #'format stream fmat args)
    (force-output stream)
    (values)))

(defun connection-print (connection form)
  (let* ((*print-case* ':downcase)
	 (message (prin1-to-string form))
	 (stream (connection-stream connection)))
    (write-string message stream)
    (terpri stream)
    (force-output stream)))

(defun connection-send (connection form)
  ;; at some point this will do binary too??
  (connection-print connection form))

(defun connection-read-chars (connection nchars)
  (let ((string (make-string nchars))
	(stream (connection-stream connection)))
    (dotimes (i nchars)
      (setf (aref string i) (read-char stream)))
    string))

(defun connection-read-line (connection)
  (let ((stream (connection-stream connection)))
    (read-line stream)))

(defun connection-read (connection)
  (let* ((io (connection-stream connection))
         (*standard-input* io))
    (read io)))


(defun connection-eval (stdout warn error form)
  ;;char-output-stream should be same as *standard-output*
  ;;but let's make it explicit
  (setf *standard-output* stdout)
  (handler-case (print (eval form))
    (warning () 
      (progn
	(format warn "Warning: something isn't quite right with ~S~%" form)
	(force-output warn)))
    (serious-condition () 
      (progn
	(format error "Error: wow really bad error in ~S~%" form)
	(force-output error))))
  (force-output stdout))
    


;;; this is a gray stream for standard output to send back to grace
;;; this merely wraps around the instance of stream in connection 
(defclass connection-character-output-stream (fundamental-character-output-stream)
  ((binary-stream :initform nil :initarg :binary-stream :accessor binary-stream)
   (byte-buffer :initform (make-array 8192 :element-type '(unsigned-byte 8)) :accessor byte-buffer)
   (buffer-index :initform 0 :accessor buffer-index)))

(defmethod send-output-buffer ((stream connection-character-output-stream))
  (let ((binary-stream (binary-stream stream))
	(length (buffer-index stream)))
    (write-u32 *msgPrintout* binary-stream)
    (write-u32 length binary-stream)
    (loop for i below length
       do (write-byte (aref (byte-buffer stream) i) binary-stream))
    (setf (buffer-index stream) 0)))


(defmethod stream-write-char ((stream connection-character-output-stream) char)
  (setf (aref (byte-buffer stream) (buffer-index stream)) (char-code char))
  (incf (buffer-index stream))
  char)

(defmethod stream-line-column ((stream connection-character-output-stream))
  nil)

(defmethod stream-start-line-p ((stream connection-character-output-stream))
  nil)

(defmethod stream-write-string ((stream connection-character-output-stream) string 
				&optional start end)
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

(defmethod stream-finish-output  ((stream connection-character-output-stream))
  (force-output stream)
  nil)

(defmethod stream-advance-to-column ((stream connection-character-output-stream) column)
  nil)

(defmethod stream-clear-output  ((stream connection-character-output-stream))
  (let ((binary-stream (binary-stream stream)))
    (clear-output binary-stream)
    (setf (buffer-index stream) 0)
    nil))


;;; subclass of connection-character-output-stream used for errors 
;;;

(defclass connection-error-output-stream (connection-character-output-stream)
  ((binary-stream :initform nil :initarg :binary-stream :accessor binary-stream)
   (byte-buffer :initform (make-array 8192 :element-type '(unsigned-byte 8)) :accessor byte-buffer)
   (buffer-index :initform 0 :accessor buffer-index)))

(defmethod send-output-buffer ((stream connection-error-output-stream))
  (let ((binary-stream (binary-stream stream))
	(length (buffer-index stream)))
    (write-u32 *msgError* binary-stream)
    (write-u32 length binary-stream)
    (loop for i below length
       do (write-byte (aref (byte-buffer stream) i) binary-stream))
    (setf (buffer-index stream) 0)))

;;; subclass of connection-character-output-stream used for warnings
;;;

(defclass connection-warn-output-stream (connection-character-output-stream)
  ((binary-stream :initform nil :initarg :binary-stream :accessor binary-stream)
   (byte-buffer :initform (make-array 8192 :element-type '(unsigned-byte 8)) :accessor byte-buffer)
   (buffer-index :initform 0 :accessor buffer-index)))

(defmethod send-output-buffer ((stream connection-warn-output-stream))
  (let ((binary-stream (binary-stream stream))
	(length (buffer-index stream)))
    (write-u32 *msgWarning* binary-stream)
    (write-u32 length binary-stream)
    (loop for i below length
       do (write-byte (aref (byte-buffer stream) i) binary-stream))
    (setf (buffer-index stream) 0)))

;;;


(defun open-server-connection (port &key bin)
  ;; open socket/stream on port and wait for client to connect,
  ;; return a connection object holding stream and socket
  (let (socket stream)
    #+openmcl
    (progn
      (setq socket (ccl:make-socket :connect ':passive :type ':stream
				    :reuse-address t :local-port port
				    :format (if bin :binary :text)))
      (setq stream (ccl:accept-connection socket :wait t)))
    #+sbcl
    (progn
      (setq socket (make-instance 'sb-bsd-sockets:inet-socket :type ':stream
				  :protocol ':tcp))
      (setf (sb-bsd-sockets:sockopt-reuse-address socket) t)
      ;; server host is loopback?
      (sb-bsd-sockets:socket-bind socket #(127 0 0 1) port)
      (sb-bsd-sockets:socket-listen socket 5)
      (setq stream (sb-bsd-sockets:socket-make-stream
		    (sb-bsd-sockets:socket-accept socket) 
		    :input t :output t :buffering (if bin :none :line)
		    :element-type (if bin '(unsigned-byte 8) 'character))))

    ;; at this point a socket connection has been made
    (make-instance 'connection
		   :serve? t
		   :reader (function connection-read)
		   :sender (function connection-print)
		   :evaler (function connection-eval)
		   :stream stream
		   :socket socket)))

(defmethod connection-open? ((obj connection))
  (open-stream-p (connection-stream obj)))



;; the stupidest server ever!



(defun serve-connection (connection)
  (let* ((stream (connection-stream connection))
	 (char-output-stream (make-instance 'connection-character-output-stream :binary-stream stream))
	 (error-output-stream (make-instance 'connection-error-output-stream :binary-stream stream))
	 (warn-output-stream (make-instance 'connection-warn-output-stream :binary-stream stream)))
    (setf *standard-output* char-output-stream)
    (setf *error-output* error-output-stream)

    (flet ((serve ()
	     (catch :socket-server
	       (let* ((binary-confirmation-message (loop for i across "binary message" collect (char-code i)))
		      (confirmation-bytes (make-array (length binary-confirmation-message)
						      :initial-contents binary-confirmation-message
						      :element-type '(unsigned-byte 8)))
		      message-type length string sexpr value byte-vector)
		 message-type length string sexpr value byte-vector
		 (loop 
		    (setq message-type (read-u32 stream ))
		    (setq length (read-u32 stream ))
		    (FORMAT *lisp-standard-output* "lisp receiving: message-type=~S, length=~S~%" message-type length)
		    (cond 
		      ((= message-type *msgString*)
		       (progn
			 (setq string (make-string length))
		       (loop for i below length
			  do (setf (elt string i)
				   (code-char (read-byte stream))))
		       (setq sexpr (read-from-string string))
		       (format *lisp-standard-output* "Lisp received string: '~S'~%" sexpr)
		       (funcall (connection-evaler connection) char-output-stream warn-output-stream error-output-stream sexpr)))
		      
		      ((= message-type *msgBinaryData*)
		       (progn
			 (setq byte-vector (make-array length :element-type '(unsigned-byte 8)))
			 (loop for i below length
			    do (setf (aref byte-vector i) (read-byte stream)))
		       (format *lisp-standard-output* "Lisp received binary message: '~S'~%" byte-vector)
		       (format *lisp-standard-output* "Lisp sending binary confirmation bytes: '~S'~%" confirmation-bytes)
		       (setq length (length confirmation-bytes))
		       (write-u32 *msgBinaryData* stream)
		       (write-u32 length stream)
		       (write-sequence confirmation-bytes stream)
		       (force-output stream)))
		      (t (format *lisp-standard-output* "Lisp received unknown message-type with id: '~S'~%" 
				 message-type))))))))
	   (let (res)
	     (unwind-protect
		  (setq res (serve ))
	       ;;set outputs back to lisp
	       (setf *standard-output* *lisp-standard-output*)
	       (setf *error-output* *lisp-error-output*)
	       (close-connection connection)
	       ;close streams
	       (close char-output-stream)
	       (close error-output-stream)
	       (close warn-output-stream)
	       (format t "; Connection closed.~%")
	       (force-output t)
	       (if (eql res ':kill)
		   (kill-lisp)))))))

(defun serve-text-connection (connection)
  (flet ((serve ()
	   (catch :socket-server
	       (loop with sexpr and value
		  do 
		    (setq sexpr (funcall (connection-reader connection)
					 connection))
		  ;; this needs multiple-value-list!
		    (setq value (funcall (connection-evaler connection)
					 connection sexpr))
		    (setf +++ ++ ++ + + sexpr)
		    (setf *** ** ** * * value)
		    (funcall (connection-sender connection)
			     connection value)
		    ))))
    (let (res)
      (unwind-protect
	   (setq res (serve ))
	(close-connection connection)
	(format t "; Connection closed.~%")
	(force-output t)
	(if (eql res ':kill)
	    (kill-lisp))))))
       
(defun start-server (port &key bin)
  (let ((con (open-server-connection port :bin bin)))
    (format *lisp-standard-output* "; started socket server: port=~d, pid=~d~%"
	    (connection-local-port con) (getpid))
    (force-output t)
    (serve-connection con)))

(defun stop-server () (throw :socket-server ':quit))
(defun kill-server () (throw :socket-server ':kill))

(defun close-socket (socket)
  ;; do i need this? (sb-sys:invalidate-descriptor (socket-fd socket))
  #+sbcl (sb-bsd-sockets:socket-close socket)
  #+openmcl (close socket)
  (values))

(defmethod close-connection ((obj connection))
  (close (connection-stream obj))
  ;; openmcl client: stream and socket are the same but recolsing
  ;; doesnt hurt
  (close-socket (connection-socket obj))
  (values))


;;
;;
;; client side (used for testing)

(defun open-connection (host port &optional bin)
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
				    (sb-bsd-sockets:get-host-by-name host))
				   port)
    (setq stream (sb-bsd-sockets:socket-make-stream 
			    socket :input t :output t
			    :buffering (if bin :none :line)
			    :element-type
			    (if bin '(unsigned-byte 8) 'character))))
  (make-instance 'connection 
		 :serve? nil
		 :reader (function connection-read)
		 :sender (function connection-print)
		 :evaler (function connection-eval)
		 :stream stream :socket socket)))

(defmacro servlisp (c form) 
  `(progn (format *lisp-standard-output* "<- ~S~%" ',form)
	  (connection-print ,c ',form)
	  (let ((ans (connection-read ,c)))
	    (format *lisp-standard-output* "-> ~S~%" ans))
	  (values)))

; SERVER: (this waits until client does open-socket-stream...)
; (defparameter c (open-server-connection 8000))

; CLIENT:
; (defparameter c (open-connection "localhost" 8000))
;
; (connection-format c "Hello, world!~%")

; SERVER:
; (connection-read-line c)
; (connection-format c "Are you talkin to me?~%")

; CLIENT:
; (connection-read-line c)

; SERVER:
; (serve-connection c)

; CLIENT:
; (servlisp c (list 1 2 3))
; (servlisp c (+ 3 4 5))
; (servlisp c (defun foo (a) (* a a)))
; (servlisp c (foo 33))
; (connection-print c '(stop-server))
; (close-connection c)


