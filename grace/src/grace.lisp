(in-package :cl-user)

#-(or sbcl openmcl clisp)
(error "Attempt to load grace.lisp into an unknown lisp implementation.")

(defvar *grace-source-directory* 
  (make-pathname :name nil :type nil
                 :defaults (or *load-pathname*
			       *default-pathname-defaults*))
  "The directory containing Grace lisp runtime sources.")

(defvar *grace-fasl-directory* *grace-source-directory*
  "The directory containing Grace runtime compiled files.")

(flet ((compload (f)
	 (let ((s (merge-pathnames f *grace-source-directory*))
	       (c (compile-file-pathname
		   (merge-pathnames f *grace-fasl-directory*))))

	   (if (or (not (probe-file c))
		   (> (file-write-date s) (file-write-date c)))
	       (setq c (compile-file s)))
	   (load c))))
  #+sbcl(require :asdf)
  #+openmcl(require :asdf)
  #+clisp (compload "asdf.lisp")
  (compload "socketserver.lisp")
  ;; add grace as a feature
  (pushnew ':grace *features*)
  )



