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

#+sbcl (require :sb-bsd-sockets)
#+sbcl (require :sb-posix)

(defclass connection ()
  ((serve? :initarg :serve? :accessor connection-serve?)
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

(defun connection-eval (connection form)
  (let* ((io (connection-stream connection))
         (*standard-input* io)
         (*standard-output* io)
         (*trace-output* io)
         (*debug-io* io)
         (*query-io* io)
         (*terminal-io* io))
    (eval form)))

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
  (unwind-protect
       (catch :socket-server
	 (let (sexpr value)
	   (loop 
	      (setq sexpr (funcall (connection-reader connection)
				   connection))
	      ;; this needs multiple-value-list!
	      (setq value (funcall (connection-evaler connection)
				   connection sexpr))
	      (setf +++ ++ ++ + + sexpr)
	      (setf *** ** ** * * value)
	      (funcall (connection-sender connection)
		       connection value))))
    (close-connection connection)
    (format t "; Connection closed.~%")
    (force-output t)))
  
(defun start-server (port &key bin)
  (let ((con (open-server-connection port :bin bin)))
    (format t "; started socket server: port=~d, pid=~d~%"
	    (connection-local-port con) (getpid))
    (force-output t)
    (serve-connection con)))

(defun stop-server () (throw :socket-server ':quit))

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
  #+openmcl
  (let ((soc (ccl:make-socket :remote-host host :remote-port port
			      :format (if bin :binary :text))))
    (make-instance 'connection :socket soc :stream soc))
  #+sbcl
  (let ((sock (make-instance 'sb-bsd-sockets:inet-socket
			       :type :stream :protocol :tcp)))
    (sb-bsd-sockets:socket-connect sock
				   (sb-bsd-sockets::host-ent-address
				    (sb-bsd-sockets:get-host-by-name host))
				   port)
    (make-instance 'connection 
		   :serve? nil
		   :reader (function connection-read)
		   :sender (function connection-print)
		   :evaler (function connection-eval)
		   :stream (sb-bsd-sockets:socket-make-stream 
			    sock :input t :output t
			    :buffering (if bin :none :line)
			    :element-type
			    (if bin '(unsigned-byte 8) 'character))
     
		   :socket sock)))

(defmacro servlisp (c form) 
  `(progn (format t "<- ~S~%" ',form)
	  (connection-print ,c ',form)
	  (let ((ans (connection-read ,c)))
	    (format t "-> ~S~%" ans))
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


