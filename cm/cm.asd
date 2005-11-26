(in-package :cl-user)

#-(or allegro clisp cmu lispworks openmcl sbcl)
(error "Sorry, Common Music does not run in this Lisp.")

(require :asdf
         #-(or sbcl openmcl)
         (make-pathname :name "asdf" :type "lisp"
                        :directory (append (pathname-directory *load-pathname*)
                                           '("src"))
                        :defaults *load-pathname*))

(defvar *cm-directory* 
  (namestring
   (truename (make-pathname :name nil :type nil
                            :defaults *load-pathname*))))

(eval-when (:load-toplevel :execute)
  (pushnew *cm-directory* asdf:*central-registry* :test #'equal))

(defun cm-directory (&rest subs)
  (namestring
   (make-pathname :name nil :type nil
                  :directory (append (pathname-directory *cm-directory*)
                                     subs)
                  :defaults *cm-directory*)))

(defun os-arch ()
  ;; exec "cm.sh -q" to keep cm.sh and lisp's bin dir names in sync
  (flet ((stdout (stream)
           ;; read a line from shell stream
           (let ((res (read-line stream nil)))
             (if (or (null res) (equal res "")) nil
                 res)))
         (cm.sh (&optional args)
           (format nil "~acm.sh~@[ ~a~]" (cm-directory "bin")
                   args)))
    #+(and allegro (not microsoft-32))
    (or (sys:getenv "CM_PLATFORM")
        (stdout
         (excl:run-shell-command (cm.sh "-q") :output :stream :wait nil)))
    #+(and clisp (not win32))
    (or (ext:getenv "CM_PLATFORM")
        (stdout
         (run-shell-command (cm.sh "-q") :output :stream :wait t)))
    #+cmu
    (or (cdr (assoc ':cm_platform ext:*environment-list*))
        (stdout
         (ext:process-output
          (ext:run-program (cm.sh) '("-q") :output :stream))))
    #+(and lispworks (not win32))
    (stdout
     (sys:run-shell-command (cm.sh "-q") :wait nil :output :stream))
    #+openmcl
    (or (ccl::getenv "CM_PLATFORM")
        (stdout
         (ccl:external-process-output-stream
          (ccl:run-program (cm.sh) '("-q" ) :wait nil :output :stream))))
    #+sbcl
    (stdout
     (sb-ext:process-output
      (sb-ext:run-program (cm.sh) '("-q") :output :stream)))
    #+(or microsoft-32 win32)
    "windows-i686"
    ))
           
(defun lisp-vers (&optional str)
  (let* ((str (or str (lisp-implementation-version)))
         (beg (position-if #'digit-char-p str)))
    (if (not beg) (error "Fix lisp-vers for this lisp.")
        (let ((end (position-if-not #'(lambda (c)
                                        (or (alphanumericp c)
                                            (member c '(#\. #\- #\_))))
                                    str :start beg)))
          (concatenate 'string
                       #+allegro "allegro"
                       #+clisp "clisp"
                       #+cmu "cmucl"
                       #+lispworks "lispworks"
                       #+openmcl "openmcl"
                       #+sbcl "sbcl"
                       "_"
                       (subseq str beg end))))))

(defvar *cm-bin-directory*
  (cm-directory "bin" (concatenate 'string (lisp-vers) "_" 
                                   (os-arch))))

(defun isdir (dir)
  ;; return true if dir exists.
  ;; cribbed from file utils by sam steingold
  #+allegro (excl::probe-directory dir)
  #+clisp (values
           (ignore-errors
             (#+lisp=cl ext:probe-directory #-lisp=cl lisp:probe-directory
                        dir)))
  #+cmu (eq :directory (unix:unix-file-kind (namestring dir)))
  #+lispworks (lw:file-directory-p dir)
  #+sbcl (eq :directory (sb-unix:unix-file-kind (namestring dir)))
  #-(or allegro clisp cmu lispworks sbcl)
  (probe-file (make-pathname :directory dir)))

(defun mkdir (dir)
  ;; create dir
  ;; cribbed from file utils by sam steingold
  #+allegro (excl:make-directory dir)
  #+clisp (#+lisp=cl ext:make-dir #-lisp=cl lisp:make-dir dir)
  #+cmu (unix:unix-mkdir (namestring dir) #o777)
  #+lispworks (system:make-directory dir)
  #+sbcl (sb-unix:unix-mkdir (namestring dir) #o777)
  #+openmcl (ccl:create-directory dir))

(defun ensure-bin-directory ()
  (unless (isdir *cm-bin-directory*)
    (mkdir *cm-bin-directory*)))

(defun fasl-pathname (file)
  (make-pathname :directory (pathname-directory *cm-bin-directory*)
                 :type (pathname-type (compile-file-pathname file))
                 :defaults file))

#-(or sbcl lispworks allegro)
(defun ensure-sys-features (sys) sys)

#+allegro
(defun ensure-sys-features (sys) 
  (savevars sys 'comp:*cltl1-compile-file-toplevel-compatibility-p*)
  (setq comp:*cltl1-compile-file-toplevel-compatibility-p* t))

#+sbcl
(defun ensure-sys-features (sys)
  sys
  ;; these should actually be part of sbcl.lisp but sbcl signals error
  ;; if the requires are in the file...
  (require :sb-posix)
  (require :sb-bsd-sockets))

#+lispworks
(defun ensure-sys-features (sys)
  sys
  ;; unfortunately it is necessary to set this variable at READ time
  ;; or else lispwork's stack is too small to load this file!
  #.(setq system:*stack-overflow-behaviour* :warn))

;;;
;;; CM system definition with pre and post-loading ops
;;;

(defclass cm-application (asdf:system) ())
(defclass initialize-op (asdf:operation) ())
(defclass finalize-op (asdf:operation) ())

(defun savevars (cm &rest vars)
  ;; save global var bindings so they can be restored after load
  (dolist (v vars)
    (push (cons v (symbol-value v))
          (asdf:component-property cm 'vars))))

(defun restorevars (cm)
  (dolist (b (asdf:component-property cm 'vars))
    (set (car b) (cdr b))))

(defmethod asdf:perform  ((op initialize-op) cm)
  (ensure-sys-features cm)
  (ensure-bin-directory)
  (savevars cm '*compile-print* '*compile-verbose* 
            '*load-verbose* '*load-print*)
  (setq *compile-print* nil *compile-verbose* nil
        *load-verbose* nil *load-print* nil)
  (format t "~%; CM install directory: ~S" *cm-directory*))

(defmethod asdf:perform  ((op finalize-op) cm)
  (let ((init (merge-pathnames ".cminit.lisp"
                               (user-homedir-pathname))))
    (if (probe-file init) (load init )))
  (restorevars cm)
  )

(defmethod asdf::traverse :around ((op asdf:load-op) 
                                   (sys cm-application))
  ;; add the initialize and finalize ops to list of operations
  (let ((init (make-instance 'initialize-op))
        (last (make-instance 'finalize-op)))
    (nconc (list (cons init sys))
           (call-next-method)
           (list (cons last sys)))))

;;;
;;; CM source file has potential dependancy on scheme file
;;;

(defclass cm-source-file (asdf:cl-source-file) 
  ((scm :initform nil :initarg :scheme :accessor scm-source-file)))

(defmethod asdf:output-files ((operation asdf:compile-op) (f cm-source-file))
  ;; make compile pathnames include the bin directory
  (list (fasl-pathname (asdf:component-pathname f))))
  
(defmethod asdf:input-files ((operation asdf:compile-op) (f cm-source-file))
  ;; include scheme dependancies
  (let ((lsp (asdf:component-pathname f))
        (scm (scm-source-file f)))
    (if scm
        (list (make-pathname :name (if (stringp scm) scm
                                       (pathname-name lsp))
                             :type "scm" :defaults lsp)
              lsp)
        (list lsp))))

(defmethod asdf:perform :before ((operation asdf:compile-op) (f cm-source-file))
  ;; generate scheme sources if necessary
  (let ((scheme (scm-source-file f)))
    (if scheme
        (let* ((lsp (asdf:component-pathname f))
               (scm (make-pathname :name (if (stringp scheme) scheme
                                             (pathname-name lsp))
                                   :type "scm" :defaults lsp)))
          (if (probe-file scm)
              (when (or (not (probe-file lsp))
                        (> (file-write-date (truename scm))
                           (file-write-date (truename lsp))))
                (unless (boundp 'toplevel-translations)
                  (load (merge-pathnames "stocl" lsp) :verbose nil))
                (format t "~%; Generating ~S"
                        (enough-namestring lsp *cm-directory*))
                (funcall 'stocl scm :file lsp :verbose nil))
              (error "Scheme source ~S not found."
                     (namestring scm)))))
    (format t "~%; Compiling ~S"
            (enough-namestring (asdf:component-pathname f)
                               *cm-directory*))))

(defmethod asdf:perform :before ((op asdf:load-op) (f cm-source-file))
  (format t "~%; Loading ~S"
          (enough-namestring (fasl-pathname
                              (asdf:component-pathname f))
                             *cm-directory*)))

;;;
;;; system definition
;;;

(asdf:defsystem :cm
    :description "Common Music"
    :class cm-application
    :version "2.7.0"
    :author "Rick Taube <taube (at) uiuc.edu>"
    :licence "LLGPL"
    :components
    ((:module "src"
              :default-component-class cm-source-file
              :components (
                           (:file "pkg")
                           #+allegro (:file "acl" :depends-on ("pkg"))
                           #+clisp (:file "clisp" :depends-on ("pkg"))
                           #+cmu (:file "cmu" :depends-on ("pkg"))
                           #+lispworks (:file "lispworks" :depends-on ("pkg"))
                           #+(and mcl (not openmcl)) (:file "mcl" 
                                                            :depends-on ("pkg"))
                           #+openmcl (:file "openmcl" :depends-on ("pkg"))
                           #+sbcl (:file "sbcl" :depends-on ("pkg"))
                           (:file "iter" :scheme "loop" :depends-on ("pkg"))
                           (:file "level1" 
                                  :depends-on ("pkg" #+allegro "acl"
                                                     #+clisp "clisp"
                                                     #+cmu "cmu"
                                                     #+lispworks "lispworks"
                                                     #+(and mcl (not openmcl)) 
                                                     "mcl"
                                                     #+openmcl "openmcl"
                                                     #+sbcl "sbcl"
                                                     "iter"))
                           (:file "clos" :depends-on ("level1"))
                           #-no-scheme (:file "scheme" :depends-on ("pkg"))
                           (:file "utils" :scheme t
                                  :depends-on ("level1"))
                           (:file "mop" :scheme t
                                  :depends-on ("clos" "utils"))
                           (:file "objects" :scheme t 
                                  :depends-on ("mop" "iter" "utils"))
                           (:file "data" :scheme t 
                                  :depends-on ("utils"))
                           (:file "scales" :scheme t
                                  :depends-on ("data" "objects"))
                           (:file "spectral" :scheme t
                                  :depends-on ("data"))
                           (:file "patterns" :scheme t
                                  :depends-on ("scales"))
                           (:file "io" :scheme t
                                  :depends-on ("objects"))
                           (:file "scheduler" :scheme t 
                                  :depends-on ("io"))
                           (:file "sco" :scheme t
                                  :depends-on ("io"))
                           (:file "clm" :scheme t
                                  :depends-on ("io"))
                           (:file "midi1" :scheme t
                                  :depends-on ("objects" "data"))
                           (:file "midi2" :scheme t 
                                  :depends-on ("midi1" "io" "scheduler"))
                           (:file "midi3" :scheme t
                                  :depends-on ("midi2" "scales"))
                           (:file "cmn" :scheme t
                                  :depends-on ("io" "midi3" "scales"))
                           (:file "fomus" :scheme t 
                                  :depends-on ("io" "midi3" "scales"))
                           (:file "osc" :scheme t :depends-on ("io"))
                           (:file "midishare" :scheme t 
                                  :depends-on ("io" "midi3" "scales"))
                           (:file "player" :scheme t 
                                  :depends-on ("midishare"))
                           (:file "sc" :scheme t :depends-on ("osc"))
                           (:file "pm" :scheme t :depends-on ("io" "midi3"))
                           #+openmcl (:file "openmcl-rt"
                                            :depends-on ("pkg" "scheduler"))
                           #+sbcl (:file "sbcl-rt"
                                         :depends-on ("pkg" "scheduler"))
                           (:file "rt" :scheme t 
                                  :depends-on ("scheduler" "midi3"))
                           (:file "rt-sc" :scheme t 
                                  :depends-on ("rt" "sc"))
                           )))
    )

;;;

(defun cm ()
  (flet ((cmcall (fn &rest args)
           (apply (find-symbol (string fn) :cm) args))
         (cmvar (var)
           (symbol-value (find-symbol (string var) :cm))))
    ;; add slime readtable mapping...
    (setf *package* (find-package :cm))
    (setf *readtable* (cmvar :*cm-readtable*))
    (let ((swank-pkg (find-package :swank)))
      (when swank-pkg
        (let ((sym (intern (symbol-name :*readtable-alist*) swank-pkg)))
          (setf (symbol-value sym)
                (cons (cons (symbol-name :cm) (cmvar :*cm-readtable*))
                      (symbol-value sym))))))
    (cmcall :cm-logo)))

(defun use-system (sys &key directory (verbose t) warnings )
  ;; load system from either:
  ;;  (1) user supplied dir
  ;;  (2) entry in asdf:*central-registry*
  ;;  (3) search under parent directory of CM.
  (let* ((name (string-downcase (string sys)))
         (root *cm-directory*)
         (reg? nil)
         (file nil))
    (when directory
      (setq file (make-pathname :name name :type "asd"
                                :defaults directory))
      (unless (probe-file file)
        (format t "Can't locate system file: ~S."
                (namestring file))
        (return-from use-system nil))
      (setq reg? t))
    (unless (or file (setq file (asdf:system-definition-pathname sys)))
      ;; probe for file under parent dir of cm
      (let* ((path (make-pathname
                    :directory (append (butlast
                                        (pathname-directory root))
                                       '(:wild))
                    :name name :type "asd" :defaults root))
             (test (first (directory path))))
        (unless test
          (format t "Can't locate system file \"~a.asd\" in asdf:*central-registry* or under ~s. Specify location using :directory arg to use-system." 
                  name (namestring path))
          (return-from use-system nil))
        (setq reg? t)
        (setq file test)))
    (when reg?
      (pushnew (make-pathname :name nil :type nil :defaults file)
               asdf:*central-registry* :test #'equal))
    (let ((*compile-print* *compile-print*)
          (*compile-verbose* *compile-verbose* )
          (*load-print* *load-print* )
          (*load-verbose* *load-verbose*)
          (loading-op 'asdf:load-op))
      (cond ((eql verbose nil)
             (setq *compile-print* nil *compile-verbose* nil
                   *load-print* nil *load-verbose* nil))
            ((eql verbose t)
             (setq *compile-print* nil *compile-verbose* t
                   *load-print* nil *load-verbose* t))
            ((eql verbose ':trace)
             (setq *compile-print* t *compile-verbose* t
                   *load-print* t *load-verbose* t)))
      ;; have to handle clm and cmn specially since asdf:load-op will
      ;; not work with them. Ill fix this later by adding a property
      ;; to their system defintions that tells use-system what class
      ;; to pass to asdf:operate
      (when (member name '("clm" "cmn") :test #'equal)
        (setq loading-op 'asdf:load-source-op))
      (if warnings
          (asdf:operate loading-op sys)
          (handler-bind ((style-warning  #'muffle-warning)
                         (warning #'muffle-warning)
                         #+sbcl (sb-ext:compiler-note #'muffle-warning)
                         #+sbcl (sb-ext:code-deletion-note #'muffle-warning))
            (asdf:operate loading-op sys))))
    (asdf:find-system sys)))

(export '(cm use-system) :cl-user)

;; (load "/Lisp/cm/cm.asd")
;; (asdf:operate 'asdf:load-op :cm)
