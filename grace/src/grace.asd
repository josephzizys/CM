;;; **********************************************************************
;;; Copyright (C) 2007 Todd Ingalls, Rick Taube.
;;; This program is free software; you can redistribute it and/or modify
;;; it under the terms of the Lisp Lesser Gnu Public License. The text of
;;; this agreement is available at http://www.cliki.net/LLGPL            
;;; **********************************************************************

;;; $Revision$
;;; $Date$

(in-package cl-user)

#-(or openmcl sbcl clisp)
(error "Sorry, this Lisp is not supported.")

#+(and clisp (not asdf))
(load (merge-pathnames "asdf.lisp" (truename *load-pathname*)))

#+(and sbcl (not asdf)) (require :asdf)

#+(and openmcl (not asdf)) (require :asdf)

(defpackage :grace
  (:use :common-lisp)
  (:export :start-server :kill-server :*connections*
	   :connection-send :connection-send-error
           :connection-read
           :grace-connection :report-error :ensure-cm-version
	   )
  #+sbcl (:use :sb-gray)
  #+clisp (:use :gray)
  #+openmcl
  (:import-from :ccl
		:fundamental-character-output-stream
		:stream-write-char :stream-line-column
		:stream-start-line-p :stream-write-string
		:stream-terpri :stream-fresh-line
		:stream-force-output :stream-finish-output
		:stream-advance-to-column :stream-clear-output)
  )

(in-package :grace)

(asdf:defsystem :grace
  :description "Graphical Realtime Algorithmic Composition Environment"
  :author "Todd Ingalls <testcase@asu.edu>, Rick Taube <taube@uiuc.edu>"
  :version "0.0.0"
  :licence "LLGPL"
  :serial t
  :components (
	       (:file "gray")
	       (:file "socketserver")
	       (:file "grace")
  	      ))

;;;
;;; eof
;;;
