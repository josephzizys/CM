(in-package :cl-user)

#-(or allegro clisp cmu lispworks openmcl sbcl)
(error "Sorry, Common Music does not run in this Lisp.")

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
  (let ((cm.sh (concatenate 'string (cm-directory "bin") "cm.sh -q")))
    #+clisp
    (read-line (ext:run-shell-command cm.sh :output :stream :wait t) nil)
    #-clisp
    (let ((str (with-output-to-string (s)
                 (let ((asdf::*verbose-out* s) )
                   (asdf:run-shell-command cm.sh))
                 s))
          (pos 0))
      ;; asdf:run-shell-command adds comment line
;      (when (char= (elt str pos) #\;)
;        (setq pos (position #\Newline str)))
;      (delete #\Newline (subseq str pos))
     str )))


(setq foo "; $ /Lisp/cm/bin/cm.sh -q
; /Lisp/cm/bin/cm.sh -q
; darwin-powerpc
"
)


(position-if #'alpha-char-p
             foo
             :start
             (or  0))
(subseq foo (position #\Newline foo :from-end t))
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

(defun ensure-bin-directory ()
  (asdf:run-shell-command "mkdir ~A" *cm-bin-directory*))

(defun fasl-pathname (file)
  (make-pathname :directory (pathname-directory *cm-bin-directory*)
                 :type (pathname-type (compile-file-pathname file))
                 :defaults file))

;;;
;;;
;;;

(defclass cm-application (asdf:system) ())

(defclass cm-source-file (asdf:cl-source-file) 
  ((scm :initform nil :initarg :scheme :accessor scm-source-file)))

(defmethod asdf:output-files ((operation asdf:compile-op) (f cm-source-file))
   (list (fasl-pathname (asdf:component-pathname f))))
  
(defmethod asdf:perform :before ((operation asdf:compile-op) (f cm-source-file))
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
                (funcall 'stocl scm :file lsp :verbose nil))
              (error "Scheme source file ~A not found!" scm))))))

#-(or sbcl lispworks)
(defun ensure-sys-features () )

#+sbcl
(defun ensure-sys-features ()
  ;;(print :requiring-posix...)
  (require :sb-posix)
  ;;(print :requiring-sockets...)
  (require :sb-bsd-sockets))

#+lispworks
(defun ensure-sys-features ()
  #.(setq system:*stack-overflow-behaviour* :warn))

;;(eval-when (:load-toplevel :execute)
;;  (ensure-sys-features)
;;  (ensure-bin-directory ))

(defclass initialize-op (asdf:operation) ())
(defclass finalize-op (asdf:operation) ())

(defmethod asdf:perform  ((op initialize-op) x)
  (print :initialize!)
  (ensure-sys-features)
  (ensure-bin-directory )
  )

(defmethod asdf:perform  ((op finalize-op) x)
  (print :finalize!)
  )

(defmethod asdf::traverse :around ((op asdf:load-op) (sys cm-application))
  (let ((init (make-instance 'initialize-op))
        (last (make-instance 'finalize-op)))
    (nconc (list (cons init sys))
           (call-next-method)
           (list (cons last sys)))))

(asdf:defsystem "cm"
    :description "Common Music"
    :class cm-application
    :version "2.7.0"
    :author "Rick Taube <taube (at) uiuc.edu>"
    :licence "LLGPL"
    :components
    ((:module "src"
              :serial t
              :default-component-class cm-source-file
              :components (
                           ;; stub unloaded system
                           #-clm (:file "clm-stubs")
                           #-cmn (:file "cmn-stubs")
                           #-fomus (:file "fomus-stubs")
                           #-midishare (:file "midishare-stubs")
                           #-player (:file "player-stubs")
                           #-portmidi (:file "portmidi-stubs")
                           (:file "pkg" :depends-on (
                                                     #-clm "clm-stubs"
                                                     #-cmn "cmn-stubs"
                                                     #-fomus "fomus-stubs"
                                                     #-midishare "midishare-stubs"
                                                     #-player "player-stubs"
                                                     #-portmidi "portmidi-stubs"))
                           #+allegro (:file "acl")
                           #+clisp (:file "clisp")
                           #+cmu (:file "cmu")
                           #+lispworks (:file "lispworks")
                           #+(and mcl (not openmcl)) (:file "mcl")
                           #+openmcl (:file "openmcl")
                           #+sbcl (:file "sbcl")

                           (:file "clos")
                           (:file "iter" :scheme "loop")
                           (:file "level1")
                           #-no-scheme (:file "scheme")
                           (:file "utils" :scheme t)
                           (:file "mop" :scheme t)
                           (:file "objects" :scheme t)
                           (:file "data" :scheme t)
                           (:file "scales" :scheme t)
                           (:file "spectral" :scheme t)
                           (:file "patterns" :scheme t)
                           (:file "io" :scheme t)
                           (:file "scheduler" :scheme t)
                           (:file "sco" :scheme t)
                           (:file "clm" :scheme t)
                           (:file "clm2" :scheme t)
                           (:file "midi1" :scheme t)
                           (:file "midi2" :scheme t)
                           (:file "midi3" :scheme t)
                           ;;(:file "midishare" :scheme t")
                           ;;(:file "player" :scheme t)
                           (:file "cmn" :scheme t)
                           (:file "fomus" :scheme t)
                           (:file "osc" :scheme t)
                           (:file "sc" :scheme t)
                           #+openmcl (:file "openmcl-rt")
                           #+sbcl (:file "sbcl-rt")
                           (:file "rt" :scheme t)
                           (:file "rt-sc" :scheme t)
                           )))
     )

;; (progn #+sbcl (require :asdf) #-sbcl (load "/Lisp/cm/src/asdf"))
;; (load "/Lisp/cm/cm.asd")
;; (setq asdf::*verbose-out* nil)
;; (asdf:operate 'asdf:load-op :cm)
