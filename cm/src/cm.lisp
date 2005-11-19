;;; **********************************************************************

(in-package :cl-user)

;(load (merge-pathnames "make.lisp" *load-pathname*) :verbose nil)
;(make-cm)

(let ((*load-verbose* nil)
      (*load-print* nil)
      (file (make-pathname :name "cm" :type "asd"
                           :directory
                           (butlast
                            (pathname-directory *load-pathname*))
                           :defaults *load-pathname*)))
  (load file)
  (funcall (find-symbol "OPERATE" :asdf)
           (find-symbol "LOAD-OP" :asdf)
           :cm))

