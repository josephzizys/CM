;;; $Name$
;;; $Revision$
;;; $Date$

;;; intermediate conversion, trying to support guile gauche stklos and
;;; (possibly) chicken
;;; (load "/Lisp/scm/src/cm.scm")

(let ((this-file #f)
      (load-path "")
      (file-list '("loop" "level1" "utils" "mop" "objects"
                   "io" "scheduler" "sco" "clm" "clm2"
                   "midi1" "midi2" "midi3" "data" "scales" "spectral"
                   "patterns")))
  (cond-expand
   (guile
    (set! this-file (port-filename (current-load-port)))
    (set! file-list (cons "guile" file-list)))
   (gauche
    (define (force-output) #f)
    (set! this-file (port-name (current-load-port)))
    (set! file-list (cons "gauche" file-list)))
   (chicken
    (set! this-file 
          (eval (with-input-from-string "##sys#current-load-file" read)))
    (set! file-list (list "chicken" "loop"))
    (load-verbose #f))
   (stklos
    #f)
   )
  
  (do ((last-slash #f)
       (i 0 (+ i 1))
       (l (string-length this-file)))
      ((= i l) 
       (if last-slash
         (set! load-path (substring this-file 0 (+ last-slash 1)))))
    (if (char=? (string-ref this-file i) #\/)
      (set! last-slash i)))

   (cond-expand
    (guile
     (set! %load-path (cons load-path %load-path))
     (set! load-path "")
     )
    (gauche 
     (set! *load-path* (cons load-path *load-path*))
     (set! load-path "")
     )
    (chicken
     #f))

   (let loadem ((tail file-list))
        (cond ((null? tail) #f)
              (else
               (let ((file (string-append load-path (car tail) ".scm")))
                 (display (string-append "; loading " file))
                 (force-output)
                 (newline)
                 (load file)
                 (loadem (cdr tail))
                 ))))
   ;; load user init file if it exists
   (let* ((this (pwd))
          (home (cd))
          (init (string-append home "/.cminit.lisp")))
     (if (file-exists? init)
       (load init))
     (cd this))

   ) ; end let

