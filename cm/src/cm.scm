;;; $Name$
;;; $Revision$
;;; $Date$

;;;
;;; load script for cm in guile.
;;;

(if (< (string->number (minor-version) ) 5)
  (error "CM runs in guile-1.5.0 or higher."))

;;; user defined cm-directory or default to current 

(if (not (module-bound? (current-module) 'cm-directory))
  (begin
   (define cm-directory #f)

   ;; courtesy of bil, removed %load-hook
   (let ((curfile (port-filename (current-load-port)))
         (last-slash 0)
         (parent-slash #f))
     (do ((i 0 (1+ i)))
         ((= i (string-length curfile)))
       (if (char=? (string-ref curfile i) #\/)
         (begin (set! parent-slash last-slash)
                (set! last-slash i))))
     (set! cm-directory (substring curfile 0 (1+ parent-slash)))
     (let ((new-path (substring curfile 0 last-slash)))
       (if (not (member new-path %load-path))
         (set! %load-path (cons new-path %load-path)))))))

;;; user specified cm-bin-directory or default

(if (not (module-bound? (current-module) 'cm-bin-directory))
  (define cm-bin-directory
    (string-append cm-directory "bin/")))

(do ((files '("guile"
	      "goops"
              "level1"
	      "loop"
	      "utils"
	      "mop"
	      "objects" 
	      "io"
	      "scheduler"
	      "sco"
	      "clm"
	      "clm2"
	      "midi1"
	      "midi2"
	      "midi3"
              ;; "midishare/midishare.scm"
              ;; "midishare/player.scm"
              ;; "cmn"
	      "data"
	      "scales"
	      "spectral"
	      "patterns"
              )
            (cdr files)))
    ((null? files) #f)
  (let* ((f (string-append (car files) ".scm")))
    (display (string-append "; Loading: " cm-directory
			    "src/" f))
    (newline)
    (load (string-append (car files) ".scm"))))

;;; install default cminit.lisp file in bin directory

(let ((init (string-append cm-bin-directory "cminit.lisp"))
      (orig (string-append cm-directory "src/cminit.lisp")))
 (if (not (file-exists? init))
   (if (file-exists? orig)
     (copy-file orig init)
     (format #t "; Help! Can't copy ~s -> ~s."
	     orig init))))

;;; install cm scripts in bin directory

(let ((scr1 (string-append cm-bin-directory "cm"))
      (scr2 (string-append cm-bin-directory "xcm")))
  (let ((exec
         (format #f "~a -c '~s'"
                 (first (command-line))
                 `(begin
                   (define cm-bin-directory , cm-bin-directory)
                   (load , (string-append cm-directory "src/cm.scm"))
                   (load , (string-append cm-bin-directory
                                          "cminit.lisp"))
                   (top-repl)))))
    (if (not (file-exists? scr1))
      (begin
       (format #t "~%; Saving startup script: ~S" scr1)
       (write-cm-script :linux scr1 exec)))
    (if (not (file-exists? scr2))
      (let ((el (string-append cm-directory
                               "etc/xemacs/listener.el")))
       (format #t "~%; Saving startup script: ~S" scr2)       
       (write-xcm-script :linux "guile" scr2 scr1 el)
       (format #t "~%")))))





