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
  (namestring (make-pathname :name nil :type nil
                             :defaults *load-pathname*)))

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
    #+(or (and allegro microsoft-32) (and clisp win32))
    "windows-i686"
    #+cmu
    (or (cdr (assoc ':cm_platform ext:*environment-list*))
        (stdout
         (ext:process-output
          (ext:run-program (cm.sh) '("-q") :output :stream))))
    #+lispworks
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
      (sb-ext:run-program (cm.sh) '("-q") :output :stream)))))
           
; (setq foo (os-arch))
;; (lisp-implementation-version)
;; "2.35 (2005-08-29) (built on pomajxego.local [192.168.1.40])"
;; "Version 1.0 (DarwinPPC32)"
;; "19b-pre1 (19B)"
;; "0.9.4"
;; "4.4.5"
;; "6.2 [Mac OS X] (Jun 26, 2002 11:22)"
;; "Snapshot 2004-11"
;; "2.33.2 (2004-06-02) (built on build.ccrma.stanford.edu [127.0.0.1])"
;; "5.0.beta [Linux/X86] (6/11/98 14:45)"
;; "Version (Beta: Darwin) 0.14.3"

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

#-(or sbcl lispworks)
(defun ensure-sys-features () )

#+sbcl
(defun ensure-sys-features ()
  ;; these should be part of sbcl.lisp but sbcl signals error if the
  ;; requires are in the file...
  (require :sb-posix)
  (require :sb-bsd-sockets))

#+lispworks
(defun ensure-sys-features ()
  ;; this is necessary to set at read time or lispworks stack is too
  ;; small to load this file!
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
  (ensure-sys-features)
  (ensure-bin-directory)
  (savevars cm '*compile-print* '*compile-verbose* 
            '*load-verbose* '*load-print*)
  (setq *compile-print* nil *compile-verbose* nil
        *load-verbose* nil *load-print* nil)
  (format t "~%; Common Music install directory: ~S" *cm-directory*))

(defmethod asdf:perform  ((op finalize-op) cm)
  (let ((init (merge-pathnames ".cminit.lisp"
                               (user-homedir-pathname))))
    (if (probe-file init) (load init )))
  (restorevars cm)
  ;(terpri)
  ;(funcall (find-symbol (string :cm) :cm))
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
              ;;:serial t
              :default-component-class cm-source-file
              :components (
                           (:file "pkg")
                           #+allegro (:file "acl" :depends-on ("pkg"))
                           #+clisp (:file "clisp" :depends-on ("pkg"))
                           #+cmu (:file "cmu" :depends-on ("pkg"))
                           #+lispworks (:file "lispworks" :depends-on ("pkg"))
                           #+(and mcl (not openmcl)) (:file "mcl" :depends-on ("pkg"))
                           #+openmcl (:file "openmcl" :depends-on ("pkg"))
                           #+sbcl (:file "sbcl" :depends-on ("pkg"))
                           (:file "iter" :scheme "loop" :depends-on ("pkg"))
                           (:file "level1" 
                                  :depends-on ("pkg" #+allegro "acl"
                                                     #+clisp "clisp"
                                                     #+cmu "cmu"
                                                     #+lispworks "lispworks"
                                                     #+(and mcl (not openmcl)) "mcl"
                                                     #+openmcl "openmcl"
                                                     #+sbcl "sbcl"))
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
                           (:file "sc" :scheme t :depends-on ("osc"))
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

;; (load "/Lisp/cm/cm.asd")
;; (asdf:operate 'asdf:load-op :cm)
