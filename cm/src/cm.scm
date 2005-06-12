;;; $Name$
;;; $Revision$
;;; $Date$
;;;
;;; (load "/Lisp/cm/src/cm.scm")

(cond-expand
 ;; gag stklos read warnings about symbols used by other schemes.
 (stklos
  (define cd #f)
  (define pwd #f)
  (define force-output #f)
  (define port-name #f)
  (define port-filename #f)
  (define %load-path #f)
  (define current-load-port #f))
 (else #f))

(let ((this-file #f)
      (load-path "")
      (file-list '("loop" "level1" "utils" "mop" "objects"
                   "io" "scheduler" "sco" "clm" "clm2"
                   "midi1" "midi2" "midi3" "data" "scales" "spectral"
                   "patterns" "osc"
                   "sc" "rt" "rt-sc"
                   )))
  (cond-expand
   (stklos
    (set! this-file (current-loading-file))
    (set! file-list (cons "stklos" file-list))
    )
   (guile
    (set! this-file (port-filename (current-load-port)))
    (set! file-list (cons "guile" file-list)))
   (gauche
    (set! this-file (port-name (current-load-port)))
    (set! file-list (cons "gauche" file-list)))
;;  (chicken
;;   (set! this-file 
;;   (eval (with-input-from-string "##sys#current-load-file" read)))
;;   (set! file-list (list "chicken" "loop"))
;;   (load-verbose #f))
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
    (set! load-path ""))
   (gauche 
    (set! *load-path* (cons load-path *load-path*))
    (set! load-path ""))
   (stklos
    (set! *load-path* (cons load-path *load-path*))
    (set! load-path "")))

  (let loadcm ((tail file-list))
       (if (null? tail) 
           #f
           (let ((file (string-append load-path (car tail) ".scm")))
             (display (string-append "; loading " file))
             (cond-expand
              (guile (force-output))
              (else #f))
             (newline)
             (load file)
             (loadcm (cdr tail)))))

  ;; load user init file if it exists
  (let* ((this (pwd))
         (home (cd))
         (init (string-append home "/.cminit.lisp")))
    (if (file-exists? init)
        (load init))
    (cd this))

  )                                     ; end let

