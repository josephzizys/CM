;;; **********************************************************************
;;; Copyright (C) 2003 Heinrich Taube (taube@uiuc.edu) 
;;; 
;;; This program is free software; you can redistribute it and/or
;;; modify it under the terms of the GNU General Public License
;;; as published by the Free Software Foundation; either version 2
;;; of the License, or (at your option) any later version.
;;; 
;;; This program is distributed in the hope that it will be useful,
;;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;;; GNU General Public License for more details.
;;; 
;;; **********************************************************************

;;; $Name$
;;; $Revision$
;;; $Date$

(in-package :cl-user)

(unless (boundp 'cm-src-directory)
  (defparameter cm-src-directory
    (namestring (make-pathname 
                 :directory 
                 (pathname-directory 
                  #+mcl ccl:*loading-file-source-file*
                  #-mcl *load-pathname*)))))

(unless (boundp 'cm-bin-directory)
  (defparameter cm-bin-directory 
    (namestring (make-pathname 
                 :directory 
                 (let ((here (pathname-directory 
                              cm-src-directory))
                       (there '("bin")))
                   (dolist (d (cdr (reverse here)))
                     (push d there))
                   there)))))

;;;
;;; Check features before building.
;;; CM pushes the following features:  
;;;  :metaclasses :loop :osx :linux :win32

#-(or mcl openmcl excl clisp cmu)
(error "~%Common Music runs in Guile, MCL, OpenMCL, ACL, CLISP, CMUCL")

;;; normalize the operating system names in *features*.
;;; CM checks for :linux :win32 :osx :macos

#+(and excl microsoft-32) 
(pushnew ':win32 *features*)

#+(and excl macosx)
(pushnew ':osx *features*)

#+openmcl
(if (find ':darwin *features*)
  (pushnew ':osx *features*)
  (if (find ':linuxppc *features*)
    (pushnew ':linux *features*)))

;; clisp on windows, linux and on osx. the
;; osx port has no feature, uname idea from tobias.
#+(and clisp unix)
(if (find ':pc386 *features*)
  (pushnew ':linux *features*)
  (let ((tok (read (run-shell-command "uname"
                                      :output :stream))))
    (ecase tok
      (darwin (pushnew ':osx *features*))
      (linux  (pushnew ':linux *features*)))))

;;; MCL runs on macos and osx
#+digitool 
(if (find :carbon-compat *features*)
  (pushnew ':osx *features*)
  (pushnew ':macos *features*))

;;; check to see that there is an OS symbol on features.
(unless (or (find ':linux *features*)
            (find ':osx *features*)
            (find ':win32 *features*)
            (find ':macos *features*))
  (error "~%Common Music runs under Linux, MacOs, OSX, or Windows."))

(let ((compiled? nil)
      #+mcl (ccl:*warn-if-redefine-kernel* nil)
      ;; fixes clisp bug when :verose is nil
      #+clisp (system::*c-listing-output* nil)
      (fasl-name  #+mcl (pathname-type ccl:*.fasl-pathname*)
                  #+excl excl:*fasl-default-type*
                  #+clisp "fas"
                  #+cmu (c:backend-fasl-file-type c:*backend*)))
  (flet ((cload (&rest path
                       &aux
                       (f (first (last path)))
                       (d '()))
           (do ((l path (cdr l)))
               ((eq (car l) f)
                (setf d (append (pathname-directory cm-src-directory)
                                (nreverse d))))
             (push (car l) d))
           (let ((sf (namestring (merge-pathnames 
                                  (format nil "~a.lisp" f)
                                  (make-pathname :directory d))))
                 ;; avoid bin/ subdirs!
                 (bf (namestring (merge-pathnames
                                  (format nil "~a.~a"
                                          (pathname-name f) 
                                          fasl-name)
                                  cm-bin-directory))))
             (if (or (not (probe-file bf))
                     (< (file-write-date bf) (file-write-date sf)))
               (progn
                 (format t "~%; Compiling ~s." sf)
                 (compile-file sf :output-file bf :verbose nil)
                 (setf compiled? t)))
             (format t "~%; Loading ~s." bf)
             (load bf :verbose nil))))
    
    ;; Load Midishare Interface if Midishare is installed.
    ;; Currently supported in Openmcl, MCL-4, MCL-5 and CMUCL
    
    (if #+(and openmcl darwin)
        (and (probe-file "ccl:darwin-headers;midishare;")
             (probe-file
              "/System/Library/Frameworks/MidiShare.framework/MidiShare"))
        #+(and digitool ccl-5.0)
        (probe-file
         "Macintosh HD:System:Library:Frameworks:MidiShare.framework:MidiShare")
        #+(and digitool ccl-4 (not ccl-5.0))
        (directory (merge-pathnames "Midishare*" 
                                    (ccl::findfolder -1 :|ctrl|)))
        #+cmu
        (probe-file "/usr/lib/libMidiShare.so")
        (cload "midishare" "MidiShare-Interface")
        (warn "No real-time MIDI support: Midishare not installed."))
    
    ;; Load optional Player interface if midishare is installed.
    (when (find ':midishare *features*)
      (if #+(and digitool ccl-4 (not ccl-5.0))
        (ccl::get-shared-library-descriptor "PlayerSharedPPC")
        #+(and openmcl darwin)
        (probe-file
         "/System/Library/Frameworks/Player.framework/Player")
        #+(and digitool ccl-5.0)
        (probe-file
         "Macintosh HD:System:Library:Frameworks:Player.framework:Player")
        #+cmu
        (probe-file "/usr/lib/libPlayer.so"   )
        (cload "midishare" "Player-Interface")
        (warn "No MIDI sequencer support: Player not installed.")))
    
    ;; level 0 loading
    ;;
    
    (cload "pkg")
    
    #+openmcl
    (progn
      ; LOOP may already be added by clm or cmn
      (unless (find ':loop *features*) 
        (load "ccl:library;loop" :verbose nil)
        (pushnew ':loop *features*))
      (cload "openmcl"))
    #+(and mcl (not openmcl))
    (progn
      ; LOOP may already be added by clm or cmn
      (unless (find ':loop *features*) 
        (load "ccl:library;loop" :verbose nil)
        (pushnew ':loop *features*))
      
      ;; Stop MCL from calling this the home directory.
      ;; otherwise meta-. info is screwed up...
      (ccl::replace-base-translation "home:"
                                     (ccl::startup-directory))
      (cload "mcl")
      (unless (eql (ccl::mac-file-creator 
                    (merge-pathnames "mcl.lisp" cm-src-directory))
                   ':ccl2)
        (let ((top (namestring
                    (make-pathname
                     :directory
                     (butlast 
                      (pathname-directory cm-src-directory))))))
          (funcall (find-symbol (string 'macify-cm) :cm) 
                   top))))
    
    #+excl
    (progn
      ;(excl:set-case-mode :case-insensitive-upper)
      (setf excl:*cltl1-in-package-compatibility-p* t)
      (setf comp:*cltl1-compile-file-toplevel-compatibility-p* t)
      (setf (excl:package-definition-lock (find-package "COMMON-LISP"))
            nil)
      (require :loop)
      (cload "acl"))
    
    #+clisp
    (progn 
      (when t ;(fboundp 'ext::package-lock) ; clisp-2.28
        (setf (ext::package-lock "LISP") nil)
        (setf (ext::package-lock "CLOS") nil))
      ;; fix clisp-2.28 bug when compile-file :vebose is nil
      
      
      (handler-bind ((t #'(lambda (c)
			    (when (find-restart 'continue)
			      (invoke-restart 'continue)))))
        (cload "loop"))
      
      (cload "clisp"))
    
    #+cmu
    (progn
      (declaim (optimize (extensions:inhibit-warnings 3)))
      (setf extensions::*gc-verbose* nil)
      (cload "cmu"))
    
    ;; level 1 loading
    ;;
    
    (cload "clos")
    (cload "iter")
    (cload "level1")
    (unless (find :no-scheme *features*)
      (cload "scheme"))
    (cload "utils")
    (cload "mop")
    (cload "objects")
    (cload "io")
    (cload "scheduler")
    (cload "sco")
    (cload "clm")
    ;; methods in clm2 will have to change for clm-in-scheme
    (if (find :clm *features*)
      (cload "clm2"))
    (cload "midi1")
    (cload "midi2")
    (cload "midi3")
    (when (find ':midishare *features*)
      (cload "midishare" "midishare")
      (when (find ':player *features*)
        (cload "midishare" "player")))
    (if (find ':cmn *features*)
      (cload "cmn"))
    (cload "data")
    (cload "scales")
    (cload "spectral")
    (cload "patterns")
    
    ;; level 2 (not added yet...)
    ;;
    
    ;#+(and mcl (not openmcl))
    ;(dolist (f '("draw" "plot" "menu-view"
    ;             "focus-view" "selection" "axis-view" 
    ;             "plot-view" "mouse-key" 
    ;             "dialogs" "undo" "plotter" ))
    ;  (cload (format nil ":plotter:~A"f)))
    
    ;; image and script saving. 
    ;;
    (if compiled?
      (progn
	(format
         t
         "~%~%; Sources were compiled. To save Common Music,~%")
	(format      
         t
         "; quit and restart Lisp, then reload cm.lisp.~%"))
      ;; else
      (let* ((el (namestring
                  (make-pathname
                   :name "listener"
                   :type "el"
                   :defaults cm-src-directory
                   :directory
                   (append
                    (butlast 
                     (pathname-directory cm-src-directory))
                    '("etc" "xemacs")))))
             (init (namestring
                    (merge-pathnames "cminit.lisp" 
                                     cm-bin-directory)))
             (cms1 (namestring
                    (merge-pathnames "cm" cm-bin-directory)))
             (cms2 (namestring
                    (merge-pathnames "xcm" cm-bin-directory)))
             lisp heap exec impl)
        #+excl 
        (setf lisp (system:command-line-argument 0)
              impl "acl"
              heap "cm.dxl"
              exec "~a -I ~a -L ~a")
        #+cmu
        (setf lisp (first ext:*command-line-strings*)
              impl "cmucl"
              heap "cm.image"
              exec "~a -core ~a -init ~a")
        #+openmcl 
        (setf lisp (first (ccl::command-line-arguments))
              impl "openmcl"
              heap "cm.image"
              exec "~a -I ~a -l ~a")
        #+clisp
        (progn
          ;; goddam clisp -- you can't determine
          ;; the command that invoked it.
          (if (find :win32 *features*)
            (let ((try
                   (merge-pathnames
                    "lisp.exe"
                    (system::lib-directory))))
              (setf lisp
                    (if (probe-file try)
                      (namestring try)
                      "clisp")))
            (let ((try (read-line
                        (ext:run-shell-command
                         "which clisp" :output :stream))))
              (setf lisp
                    (if (probe-file try)
                      (namestring try)
                      (progn
                        (setf try
                              (merge-pathnames
                               "base/lisp.run"
                               (system::lib-directory)))
                        (if (probe-file try)
                          (namestring try)
                          "clisp"))))))
          (setf impl "clisp"
                heap "cm.mem"
                exec "~a -I -M ~a -i ~a"))
        #+(and mcl (not openmcl))
        (setf lisp nil
              impl "mcl"
              heap "Common Music"
              exec nil)
        
        (setf heap (namestring
                    (merge-pathnames heap cm-bin-directory)))
        #-(and mcl (not openmcl))
        (let ((os (if (find :win32 *features*)
                    :win32
                    (if (find :linux *features*)
                      :linux
                      (if (find :osx *features*)
                        :osx)))))
          (setf exec (format nil exec lisp heap init))
          (format t "~%; Saving startup script: ~S" cms1)
          (force-output)
          (funcall (find-symbol (string 'write-cm-script) 
                                :cm)
                   os cms1 exec)
          (format t "~%; Saving Xemacs startup script: ~S" cms2)
          (force-output)
          (funcall (find-symbol (string 'write-xcm-script)
                                :cm)
                   os impl cms2 exec el))
        
	;; maybe copy default cminit.lisp to bin directory
        
        (unless (probe-file init)
	  (let ((old (make-pathname
                      :name "cminit"
                      :type "lisp"
                      :defaults cm-src-directory
                      :directory
                      (append
                       (butlast 
                        (pathname-directory cm-src-directory))
                       '("etc" )))))
	    (with-open-file (n init :direction :output
			       :if-does-not-exist :create)
	      (with-open-file (o old :direction :input)
		(do ((l (read-line o nil ':eof)
			(read-line o nil ':eof)))
		    ((eq l ':eof) nil)
		  (write-line l n))))))
        
        (unless (and (boundp 'save-cm)
                     (null (symbol-value 'save-cm)))
          (unless (and (boundp 'delete-fasls)
                       (null (symbol-value 'delete-fasls)))
            (format t "~%; Removing ~a*.~a" cm-bin-directory 
                    fasl-name)
            (force-output)
            (dolist (f (directory (format nil "~A*.~A"
                                          cm-bin-directory 
                                          fasl-name)))
              (delete-file f))
          (funcall (find-symbol (string 'save-cm) :cm) 
                   heap))) ))
    (values)))

;;;
;;; eof
;;;


