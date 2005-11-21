;;; **********************************************************************

(in-package :cl-user)


(load 
 (make-pathname :name "cm" :type "asd"
                :directory (butlast (pathname-directory *load-pathname*))
                :defaults *load-pathname*))


(use-system :cm)


