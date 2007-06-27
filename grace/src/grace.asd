;;; **********************************************************************
;;; Copyright (C) 2007 Todd Ingalls, Rick Taube.
;;; This program is free software; you can redistribute it and/or modify
;;; it under the terms of the Lisp Lesser Gnu Public License. The text of
;;; this agreement is available at http://www.cliki.net/LLGPL            
;;; **********************************************************************

;;; $Revision$
;;; $Date$

(in-package :cl-user)

#-(or openmcl sbcl clisp)
(error "Sorry, this Lisp is not yet supported.")

#+(and clisp (not asdf))
(load (merge-pathnames "asdf.lisp" (truename *load-pathname*)))

#+(and sbcl (not asdf)) (require :asdf)

#+(and openmcl (not asdf)) (require :asdf)

(asdf:defsystem :grace
  :description "Grace support code"
  :author "Todd Ingalls, Rick Taube"
  :licence "LLGPL"
  :serial t
  :components (
	       (:file "grace")
	       (:file "socketserver")
  	      ))


