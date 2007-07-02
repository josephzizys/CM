;;; **********************************************************************
;;; Copyright (C) 2007 Todd Ingalls, Rick Taube.
;;; This program is free software; you can redistribute it and/or modify
;;; it under the terms of the Lisp Lesser Gnu Public License. The text of
;;; this agreement is available at http://www.cliki.net/LLGPL            
;;; **********************************************************************

;;; $Name$
;;; $Revision$
;;; $Date$

(in-package :grace)

(defmethod asdf:perform :after ((a asdf:load-op) (b asdf:system))
  ;; notify grace of newly loaded system if connected
  (let ((con (grace-connection)))
    (when (and con (connection-open? con))
      (connection-send con +msgLoadSystem+
		       (asdf:component-name b)))
    ))

(defmethod asdf:perform :after ((a t)(b t))
  ;; flush tyo or warnings during file loading/compiling
  (force-output *standard-output*)
  (force-output *error-output*)
  ) 

(pushnew ':grace *features*)

;;;
;;; eof
;;;
