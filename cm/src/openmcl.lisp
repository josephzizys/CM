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

#|
(export '(ccl::set-mac-file-creator ccl::set-mac-file-type) :ccl)

(defun ccl::set-mac-file-type (file type)
  (unless (stringp type)
    (setf type (string type)))
  (unless (probe-file "/Developer/Tools/SetFile")
    (error "Can't set mac file type because~%~
           /Developer/Tools/SetFile~%does not exist."))
  (ccl:run-program "/Developer/Tools/SetFile"
		   (list "-t" type file))
  (values))

(defun ccl::set-mac-file-creator (file creator)
  (unless (stringp creator)
    (setf creator (string creator)))
  (unless (probe-file "/Developer/Tools/SetFile")
    (error "Can't set mac file type because~%~
           /Developer/Tools/SetFile~%does not exist."))
  (ccl:run-program "/Developer/Tools/SetFile"
		   (list "-c" creator file))
  (values))
|#

(in-package :cm)

(pushnew :metaclasses *features*)

(import '(ccl:slot-definition-name 
          ccl:slot-definition-initargs 
          ccl:slot-definition-initform 
          ccl:class-direct-superclasses
          ccl:class-direct-subclasses
          ccl:open-shared-library ; needed if loading clm into cm.
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

(defun shell (str &rest args)
  (let* ((raw (apply #'format nil str args))
	 (lst (explode-string raw)))
    (ccl:run-program (car lst) (cdr lst) :output t)
    (values)))

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
  var
  nil)

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
                          ))))
  (ccl:save-application path :application-class (find-class 'cm)))




