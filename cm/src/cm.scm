;;; $Name$
;;; $Revision$
;;; $Date$

;;; intermediate conversion, trying to support guile gauche stklos and
;;; (possibly) chicken

(let ((this-file #f)
      (file-list '())
      (load-path ""))

  (cond-expand
   (guile
    (set! this-file (port-filename (current-load-port)))
    (set! file-list (cons "guile"
                          '("loop" "level1" "utils" "mop"
                            "objects" "io" "scheduler" "sco" "clm" "clm2"
                            "midi1" "midi2" "midi3" "data" "scales" "spectral"
                            "patterns"))))
   (gauche
    (set! this-file (port-name (current-load-port)))
    (set! file-list (cons "gauche" '("loop" "level1" ))))
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

   ;; load source files
   (do ((tail file-list (cdr tail))
        (file #f))
       ((null? tail) #f)

     (set! file (string-append load-path (car tail) ".scm"))
     (display (string-append "; loading " file))
     (newline)
     (load file)
     )

   ;; load user init file if it exists
   (let* ((this (pwd))
          (home (cd))
          (init (string-append home "/.cminit.cm")))
     (if (file-exists? init)
       (load init))
     (cd this))

   ) ; end let

