;;; **********************************************************************
;;; Copyright (C) 2007 Todd Ingalls, Rick Taube.
;;; This program is free software; you can redistribute it and/or modify
;;; it under the terms of the Lisp Lesser Gnu Public License. The text of
;;; this agreement is available at http://www.cliki.net/LLGPL            
;;; **********************************************************************

;;; $Name$
;;; $Revision$
;;; $Date$

(in-package grace)

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

