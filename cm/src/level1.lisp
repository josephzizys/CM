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

(in-package :cm)

;;;
;;; cm-directory is parent directory of src/
;;;

(defparameter cm-directory
  (namestring (make-pathname 
               :directory 
               (butlast
                (pathname-directory *load-pathname*)))))

;;;
;;; level1 provodes support routines that are common to
;;; all cltl2 implementations. after this file is loaded
;;; the scheme and cltlt implementatoin should be "equal"
;;;

;;; these are provided in scheme and cltl so that source
;;; examples can be "dialect independant".

(defvar true t)
(defvar false nil)

;;;
;;; a few scheme functions i require in the sources
;;;

(defun get-current-time ()
  (multiple-value-bind (sec min hour day mo year)
                       (get-decoded-time)
    (vector sec min hour day (- mo 1) year)))

(defun filename->url (file)
  (let* ((norm (truename file))
	 (host (pathname-host norm))
	 (dirs (pathname-directory norm))
	 (name (pathname-name norm))
	 (type (pathname-type norm)))
    (unless (eql (first dirs) :absolute)
      (error "Filename ~a not absolute." file))
    (format nil "file://~a~{/~a~}/~a.~a"
	    (if (stringp host) host "")
	    (cdr dirs) name type)))

#+no-scheme
(progn
  
  (defun string->symbol (string)
    (intern string))
  
  (defun symbol->string (symbol)
    (symbol-name symbol))
  
  (defun string-append (&rest strs)
    (apply #'concatenate 'string strs))
  
  (defmacro define (form &rest def)
    (flet ((expand-scheme-defun (spec body)
             (let ((args '()))
               (loop for i from 0
                     until (null spec)
                     do
                     (cond ((consp spec)
                            (unless (and (car spec)
                                         (symbolp (car spec)))
                              (error "Define: bad function ~
                                      ~:[name~;parameter~]: ~s."
                                     (> i 0) (car spec)))
                            (push (car spec) args)
                            (setf spec (cdr spec)))
                           ((and spec (symbolp spec))
                            (push '&rest args)
                            (push spec args)
                            (setf spec '()))
                           (t
                            (error "Define: bad function ~
                                    ~:[name~;parameter~]: ~s."
                                   (> i 0) spec))))
               (setf args (reverse args))
               `(progn
                  (defun ,(pop args) ,args ,@body)
                  (values)))))
      (if (symbolp form)
        (if (null def)
          (error "Define: missing value." )
          (if (null (cdr def))
            `(progn (defparameter ,form ,(car def))
                    (values ))
            (error "Define: too many values: ~s" def)))
        (if (and (consp form)
                 (symbolp (car form)))
          (if (null def)
            (error "Define: missing body of function define.")
            (expand-scheme-defun form def))
          (error "Define: ~S not a variable or ~
                  function specification."
                 form)))))
  )

;;;
;;; functionality i had to add to scheme that is not exactly
;;; defined in cltl either...
;;;

(defun log2 (n) (log n 2))

(defun log10 (n) (log n 10))

(defmacro define-list-struct (name &body slots)
  (let ((setters
         (loop for x in slots
               for s = (if (consp x) (car x) x)
               collect
               `(defun ,(intern (concatenate 'string 
                                             (string name)
                                             "-"
                                             (string s)
                                             "-"
                                             ;; case sensitivity
                                             (symbol-name 'set!)))
                       (,name value)
                  (setf (,(intern (concatenate 'string 
                                               (string name)
                                               "-"
                                               (string s)))
                         ,name)
                        value)))))
    `(progn
       (defstruct (,name (:type list))
         ,@slots)
       ,@setters)))

;;;
;;; readtable hackery
;;;

(defvar *cm-readtable* (copy-readtable))

(defun read-macro-set! (char func)
  (set-dispatch-macro-character 
   #\# char #'(lambda (stream a b) 
                (declare (ignore a b))
                (funcall func (read stream)))
   *cm-readtable*))

(read-macro-set! #\! (lambda (form) `(find-object ',form t)))

;;;
;;; hash-table
;;;

(defun hash-fold (func prev table)
  (maphash #'(lambda (key val)
               (setf prev (funcall func key val prev)))
           table)
  prev)

;;;
;;; symbols and keywords
;;;

(defun keyword? (x) (typep x 'keyword))

(defun symbol->keyword (sym)
  (let ((str (symbol-name sym)))
    (or (find-symbol str ':keyword)
        (intern str :keyword))))

(defun keyword->symbol (keyword)
  (let ((name (symbol-name keyword)))
    (or (find-symbol name)
        (intern name))))

;;;
;;; filename twiddling. these always return strings.
;;;

(defun filename (file) (namestring file))

(defun filename-directory (file)
  (let ((dir (pathname-directory file)))
    (if dir
      (namestring (make-pathname :directory dir))
      nil)))

(defun filename-name (file) (pathname-name file))

(defun filename-type (file) (pathname-type file))

(defun merge-filenames (file1 file2) 
  (namestring (merge-pathnames file1 file2)))

;;;
;;; file opening and closing.
;;;

(defun open-file (file direction &optional (type :char))
  (let ((etyp (ecase type
                ((:byte :byte8 ) '(unsigned-byte 8))
                ((:byte32 ) '(unsigned-byte 32))
                ((:char ) 'character))))
    (if (eq direction :output)
      (open file :direction :output
            :if-does-not-exist :create
            :if-exists :supersede
            :element-type etyp)
      (open file :direction :input
            :element-type etyp))))

(defun close-file (fp dir)
  (declare (ignore dir))
  (close fp))

;(defun open-output-file (file)
;  (open file :direction :output
;        :if-does-not-exist :create
;        :if-exists :supersed))
;
;(defun open-input-file (file)
;  (open file :direction :input))
;
;(defmacro with-open-output-file ((var file) &body body)
;  `(with-open-file (,var ,file :direction :output
;                         :if-does-not-exist :create
;                         :if-exists :supersed)
;     ,@body))
;
;(defmacro with-open-input-file ((var file) &body body)
;  `(with-open-file (,var ,file :direction :input)
;     ,@body))

;;;
;;; defobject expansion for cltl
;;;

(defun expand-defobject (name gvar supers slots pars methods)
  `(progn
     (defclass ,name ,supers 
       ,(loop for x in slots
              when (consp x)
              collect
              (let* ((slot (first x))
                     (inits (list slot))
                     (keyword (symbol->keyword slot))
                     (key? nil)
                     (acc? ':default))
                (loop for (key val) on (cdr x) by #'cddr
                      do 
                      (cond ((eq key ':initarg) 
                             (if (eq val keyword) (setf key? t)))
                            ((eq key ':accessor)
                             (setf acc? val))
                            (t (push key inits)
                               (push val inits))))
                (unless key?
                  (push ':initarg inits)
                  (push keyword inits))
                (when acc?
                  (if (eql acc? ':default)
                    (setf acc? (intern (format nil "~a-~a" name slot))))
                  (push ':accessor inits)
                  (push acc? inits)) 
                (nreverse inits))
              else 
              collect 
              (list x ':initarg (symbol->keyword x)
                    ':accessor (intern (format nil "~a-~a" name x))))
       ,@(if (and pars (find ':metaclasses *features*))
           (list '(:metaclass parameterized-class))
           '()))
     
     ;; define a global variable for the class object
     (defparameter ,gvar (find-class ',name))

     ;; sigh. some CLOS make me do this.
     (finalize-class ,gvar)

     ;; define a load-form method
     ,(make-load-form-method name gvar)

     ;; define a #i print-object method
     (defmethod print-object ((obj ,name) port)
       (if *print-instance*
         (print-instance obj port)
         (call-next-method)))

     ;; set class parameters if apropriate.
     ,@(if pars (list `(setf (class-parameters ,gvar)
                             (quote ,pars))))

     ;; splice in any output methods.
     ,@methods

     ;; expansion returns no values.
     (values)))

;;;
;;; cltl expansion for make-load-form
;;;

(defun make-load-form-method (classname classvar)
  `(defmethod make-load-form ((obj ,classname))
     (list* 'make-instance ',classvar
            (slot-init-forms obj :eval t))))

;;;
;;; cltl expansion for write-event
;;;

(defun define-output-method (objclassname objclassvar objvar
                                          fileclassname fileclassvar
                                          filevar timevar body)
  (declare (ignore objclassvar fileclassvar))
  `(defmethod write-event ((,objvar ,objclassname)
                           (,filevar ,fileclassname)
                           ,timevar)
     ,@body))

;;;
;;; CLTL expansion for process macro
;;;

(defun process-stop (expr)
  (declare (ignore expr))
  '(return-from :process ':stop))

(defun expand-process (forms ops)
  (let ((parsed (parse-iteration 'process forms ops))
        (code '())
        (func nil)
        (tests '())
        (done nil))
    
    (setf tests (loop-end-tests parsed))
    (setf done (process-stop nil))
    (if (not (null tests))
      (progn
        (if (null (cdr tests))
          (setf tests (car tests))
          (setf tests (cons 'or tests)))
        (setf tests `((if ,tests ,done))))
      (unless (process-code-terminates? (loop-looping parsed)
                                        (process-stop nil))
        ;(or (member 'while (loop-operator parsed))
        ;          (member 'until (loop-operator parsed)))
        (warn
         "A non-terminating process may have been defined.~%~
          You can use REPEAT, WHILE or UNTIL to limit iteration.")))
    (setf code
          `(block :process
             ,@ tests
                ,@ (loop-looping parsed)
                   ,@ (loop-stepping parsed)
                      (enqueue *process* *qnext* *qstart*)))
    ;; if there is a finally clause wrap the block
    ;; in a test for :STOP. when true do the 
    ;; finally actions.
    (when (loop-finally parsed)
      (setf code
            `(when (eq ':stop ,code)
               ,@ (loop-finally parsed))))
    (setf func `(function (lambda () ,code)))
    (if (and (null (loop-bindings parsed))
             (null (loop-initially parsed)))
      func
      ;; use let* sequential binding
      `(let* ,(loop-bindings parsed)
         ,@(loop-initially parsed)
         ,func))))

(defun expand-defprocess (forms)
  `(defun ,(first forms) ,(second forms) ,@(cddr forms)))

;;;
;;; cltl expansion for define-midi-message-set! 
;;;

(defun make-midi-message-set! (getter bytespec)
  (let ((setter (intern
                 (concatenate 'string
                              (string getter)
                              (string '-set!)))))
    `(defmacro ,setter (message value)
       (if (symbolp message)
         (let ((val (gensym)))
           `(let ((,val ,value )) ;
              (setf ,message (dpb ,val ,',bytespec ,message))
              ,val))
         `(dpb ,value ,',bytespec ,message)))))


(defun set-file-position (file pos set?)
  (if (= pos 0)
    (file-position file)
    (if set?
      (file-position file pos)
      (file-position file 
                     (+ (file-position file) pos)))))


;;;
;;;
;;;

(defun load-cminit ()
  ;; try to load cminit.lisp as dynamically as possible: if the lisp
  ;; implementation lets us determine the directory that the image
  ;; file is in, then look in this dir first for cminit.lisp. if its
  ;; not there then look for {imgdir}/../lib/cminit.lisp. otherwise
  ;; (the image dir cant be determined) then try use the shell
  ;; variable 'cmlibdir' that cm.sh sets. otherwise use the value of
  ;; cl-user::cm-lib-dir set by make.lisp when the image was saved.
  (let* ((dir (cm-image-dir))
         (init (and dir (merge-pathnames init "cminit.lisp"))))
    (unless init
      (if dir
        (setf init (make-pathname
                    :directory (append (butlast
                                        (pathname-directory dir))
                                       (list "lib"))
                    :name "cminit" :type "lisp"
                    :defaults dir))
        (progn
          (setf dir (or (env-var 'cmlibdir)
                        (symbol-value (find-symbol (string :cm-lib-dir)
                                                   :cl-user))))
          (setf init (concatenate 'string dir
                                  #+(or osx linux) "/"
                                  #+digitool ":"
                                  #+win32 "\\"
                                  "cminit.lisp")))))
    (when (probe-file init)
      (load init :verbose nil))
    ))