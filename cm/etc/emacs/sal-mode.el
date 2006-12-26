;;; **********************************************************************
;;; Copyright (C) 2006 Rick Taube
;;; This program is free software; you can redistribute it and/or   
;;; modify it under the terms of the Lisp Lesser Gnu Public License.
;;; See http://www.cliki.net/LLGPL for the text of this agreement.
;;; **********************************************************************
;;; $Revision$
;;; $Date$

;; add-to-list load-path "/Lisp/sal/"

(require 'font-lock)
;(require 'slime)

(when (member 'aquamacs features)
  (setq aquamacs-known-major-modes
	(add-to-list 'aquamacs-known-major-modes '(sal-mode . "SAL")
		     )))

(unless (boundp 'cm-program)
  (defvar cm-program "cm -s sal"))

(defvar sal-mode-hook nil)

(defvar sal-mode-map
  (let ((map (make-sparse-keymap)))
    map)
  "Keymap for SAL major mode")

(defvar sal-easy-menu
  (let ((con '(slime-connected-p)))
    `("SAL"
      [ "Start CM" start-sal :visible (not ,con) ]
      [ "Kill CM" stop-sal :visible ,con ]
      [ "Show REPL" slime-switch-to-output-buffer :active ,con]
      "--"
      [ "Execute" sal-enter ,con]
      [ "Trace" toggle-trace :active NIL :style toggle
	:selected *sal-trace*]
      "---"
      ("Systems"
       ["CLM" (load-system :clm) (and ,con (system-unloaded-p :clm))]
       ["Fomus" (load-system :fomus)
	(and ,con (system-unloaded-p :fomus))]
       ["Portmidi" (load-system :portmidi)
	(and ,con (system-unloaded-p :portmidi))]
       ["RTS" (load-system :rts)
	(and ,con (system-unloaded-p :rts))]
       )
      ["Current Directory" sal-get-directory ,con]
      ["Set Directory..." sal-set-directory ,con]
      ["Load File..." sal-load-file ,con]
      ["Compile File..." sal-compile-file nil]
      ["Import File..." sal-import-file nil]
      ["Play File..." sal-play-file ,con]
      "---"
      ("Help"
       [ "SAL Manual"
	 (browse-url "http://commonmusic.sf.net/doc/dict/sal-topic.html")]
       [ "CM Dictionary"
	 (browse-url "http://commonmusic.sf.net/doc/dict/index.html")]
       [ "Lookup symbol" sal-lookup-doc-at-point])
      )))


  

(defun sal-load-system ()
  )

(defun start-sal ()
  (interactive)
  (cond ((boundp 'cm-systems) ; cm.el loaded...
	 (let ((cm-systems (add-to-list 'cm-systems 'sal)))
	   (cm cm-program)))
	(t
	 (slime-start :program cm-program))))

(defun stop-sal ()
  "Kill *slime-repl* and all associated buffers."
  (interactive)
  (slime-repl-sayoonara))

(easy-menu-define menubar-sal sal-mode-map "SAL" sal-easy-menu)

(define-key sal-mode-map (kbd "<kp-enter>")
  'sal-enter)

(define-key sal-mode-map (kbd "<help>")
  'sal-lookup-doc-at-point)

(defun sal-get-directory ()
  (interactive )
  (let ((cur (slime-eval '(cm::pwd) "CM")))
    (message (format "Current directory: %s" cur))))

(defun sal-set-directory ()
  (interactive )
  (let ((cur (slime-eval '(cm::pwd) "CM")))
    (if (stringp cur)
	(let ((dir (read-directory-name "Set Output Directory"
					nil cur nil)))
	  (progn 
	    (message (format "Directory set to %S" dir))
	    (slime-eval-async `(cl::progn (cm::cd ,dir) (cl::values))
			      nil "CM"))))))

(defun sal-play-file ()
  (interactive )
  (let ((cur (slime-eval '(cm::pwd) "CM")))
    (if (stringp cur)
	(let ((fil (read-file-name "Play file" cur nil t)))
	  (if (string-match "\\.\\(aiff\\|wav\\|mid\\)\\'"
			    fil)
	      (progn (message (format "Playing %S" fil))
		     (slime-eval-async `(cm::play ,fil) nil "CM"))
	    (message (format "Don't know how to play %s" fil)))))))

(defun sal-load-file ()
  (interactive )
  (let ((cur (slime-eval '(cm::pwd) "CM")))
    (if (stringp cur)
	(let ((fil (read-file-name "Load file" cur nil t)))
	  (if (string-match "\\.\\(lisp\\|sal\\|cm\\)\\'"
			    fil)
	      (progn (message (format "Loading %S" fil))
		     (slime-eval-async `(cm::sal-load, fil) nil "CM"))
	    (message (format "Don't know how to load %s" fil)))))))

(defvar sal-mode-syntax-table (make-syntax-table))

(add-to-list 'auto-mode-alist '("\\.sal$" . sal-mode))

;; commands are SAL statements allowed at top-level, i.e. starting in
;; column 0.  at some point this list will have to allow new commands
;; to be added during the editing session

(defvar sal-commands 
  '("begin" "chdir" "define" "if" "load" "loop" "open" "play" "print" 
    "rts" "set"  "sprout" "system"))

;; add non-top-level statements

(defvar sal-statements
  (append sal-commands 
	  '("run" "exec" "output" "return" "unless" "wait" "when" "with")))

;; add literals that are not statments.

(defvar sal-reserved
  (append sal-statements
	  '("above" "below" "by" "collect" "downto" "else"
	    "end"  "finally" "for" "from" "in" "over" "repeat" "return" 
	    "then" "to" "unless" "until" "wait" "when" "while" "with")))

;; for sanity's sake we insist that commands start in the zero'th
;; column otherwise command parsing will be a nightmare.

(defvar sal-command-start-regexp
  (concat "^" (regexp-opt sal-commands t) "\\b"))

(defvar sal-statement-start-regexp
  ;; matches a line starting with any sort of sal statement
  (concat "^[ \t]*" (regexp-opt sal-statements t) "\\b"))

(defvar sal-indenting-substatements-regexp
  ;; matchs a line that indents its sub statmenets
  (concat "^[ \t]*"
	  (regexp-opt '("define" "begin"  "loop" "run" "if" "else") t)
	  "\\b"))

;;; syntax coloring

(defvar sal-font-lock-keywords-0
  (list (cons sal-command-start-regexp font-lock-function-name-face)
	(cons "^end\\b" font-lock-function-name-face)
	))

(defvar sal-font-lock-keywords-1
  (append
   sal-font-lock-keywords-0
   (list
    (cons (concat "\\<" (regexp-opt sal-reserved t) "\\>")
	  font-lock-keyword-face))))

(defvar sal-font-lock-keywords-2
  (append
   sal-font-lock-keywords-1
   (list
    (cons "<[A-Za-z0-9\-]+\\(:[A-Za-z0-9\-]+\\)?>" font-lock-type-face)
    (cons (regexp-opt '("variable" "function" "process") 'words)
	  font-lock-type-face))))

(defvar sal-font-lock-keywords-3
  (append
   sal-font-lock-keywords-2
   (list
    ;; boolean
    (cons (regexp-opt '("#t" "#f" "#a") t) font-lock-constant-face)
    ;; keywords
    (cons "[A-Za-z0-9\-]+:" font-lock-builtin-face))))

(defvar sal-font-lock-keywords sal-font-lock-keywords-3)

;;; sal editing commmands

(defvar *sal-trace* nil)
(defvar *sal-debug* nil) ; this

(defun toggle-trace ()
  (interactive )
  (if *sal-debug*
      (message "Cannot toggle trace while Debug is ON.")
    (progn
      (setq *sal-trace* (not *sal-trace*))
      (slime-eval-async
       `(common-lisp::setq cm::*sal-trace* ,*sal-trace* ) nil "CM")
      (message (if *sal-trace* "Trace ON" "Trace OFF")))))

(defun toggle-debug ()
  (interactive)
  (if *sal-trace*
      (message "Cannot toggle debug while Trace in ON.")
    (let ((forms (list)))
      (setq *sal-debug* (not *sal-debug*))
      (cond ((not *sal-debug*)
	     (setq forms `(common-lisp::setq cm::*sal-eval* t
					     cm::*sal-trace* nil)))
	    (t 
	     (setq forms `(common-lisp::setq cm::*sal-eval* nil
					     cm::*sal-trace* t))))
      (slime-eval-async forms nil "CM")
      (message (if *sal-debug* "Debug ON" "Debug OFF")))))

(defun this-line ()
  "Return the vertical position of point..."
  (+ (count-lines (point-min) (point))
     (if (= (current-column) 0) 1 0)))

;; system loading

(defun system-loaded-p (sys)
  ;; true if system is already loaded in running cm. this fast method
  ;; only works if the system pushes its name onto features, but this
  ;; is true in all cases so far...
  (slime-eval `(cl:find ,sys cl:*features*) "CL-USER"))

(defun system-unloaded-p (sys)
  (not (system-loaded-p sys)))

(defun load-system (sys)
  ;; the progn is to stop slime attempting to return the actual asdf
  ;; struct returned by use-system back to emacs, which causes weird
  ;; things to happen :)
  (slime-eval-async `(cl:progn (cl-user:use-system ,sys) t) nil "CM"))

(defvar sal-loaded-p nil)

(defun sal-loaded-p ()
  ;; true if sal is loaded in running cm.
  (if (not sal-loaded-p)
      (if (system-loaded-p :sal)
	  (progn (setq sal-loaded-p t)
		 t)
	nil)
    t))

(defun sal-enter ()
  (interactive)
  (if (not (slime-connected-p ))
      (message "CM not running. Select 'Start CM' from the SAL menu.")
    ;; THIS HAS TO BE CLEARED WHEN CM IS KILLED
    (if (not (sal-loaded-p))
	(if (y-or-n-p "SAL system not loaded. Attempt to load SAL? ")
	    (slime-eval-async '(cl:progn (cl-user:use-system :sal) t) nil "CM"))
      (let ((left 0) 
	    (right 0)
	    (cmd nil)
	    (multi nil))
	(cond ((and mark-active (not (null (mark))))
	       (setq left (region-beginning))
	       (setq right (region-end))
	       (setq multi t))
	      ((or (= (point) (point-max))
		   (looking-at "[ \t]*$"))
	       ;;(setq left (save-excursion (beginning-of-line) (point)))
	       (setq left (backwards-sal-statement sal-command-start-regexp ))
	       (setq right (point))))
	(if (and left right (< left right))
	    (let ((cmd (buffer-substring-no-properties left right)))
	      (when cmd
		;; (message cmd)
		(if multi
		    (slime-eval-async
		     `(cm::sal ,cmd :pattern :command-sequence) nil "CM")
		  (slime-eval-async `(cm::sal ,cmd ) nil "CM")))))))))

(defun sal-lookup-doc-at-point ()
  ;; help for symbol at point
  (interactive)
  (let ((cell (bounds-of-thing-at-point 'symbol)))
    (if cell
	(let ((word (buffer-substring-no-properties (car cell) (cdr cell))))
	  (if (member word sal-statements)
	      (progn
		(when (equal word "define")
		  (save-excursion
		    (forward-word)
		    (skip-syntax-forward " ")
		    (cond ((looking-at "variable")
			   (setq word "define_variable"))
			  ((looking-at "function")
			   (setq word "define_function"))
			  ((looking-at "process")
			   (setq word "define_process"))
			  )))
	      (let ((url (concat
			  "http://commonmusic.sf.net/doc/dict/sal-topic.html#"
			  word)))
		(browse-url url)))
	    (message "No help for thing at point.")
	    ))
      (message "No help for thing at point.")
      )))

(defun backwards-sal-statement (match)
  ;; find the start of the match statement/command
  (save-excursion
    (beginning-of-line)
    (let ((regexp match)
	  (cmdline nil)
	  (search t))
      (while (and (not cmdline) search )
	(cond ((looking-at regexp)
	       (setq search nil)
	       (setq cmdline (point)))
	      ((and (not (eq regexp sal-command-start-regexp))
		    (looking-at sal-command-start-regexp))
	       (setq search nil)
	       (setq cmdline nil))
	      (t
	       (if (= -1 (forward-line -1)) (setq search nil))
	       )))
      cmdline)))

;(defun read-white-delimited (beg end &optional (skip t))
;  (let ((wspace '(?\  ?\t ?\r ?\n))
;	(char nil))
;    (if skip (setq beg (+ beg (skip-syntax-forward " " end))))
;    (if (< beg end)
;	(progn (setq end (+ beg (skip-syntax-forward "^ " end)))
;	       (if (< beg end) (buffer-substring beg end) nil))
;      nil)))

;;; this is really broken, must fix at some point...

(defun sal-indent-line ()
  (interactive)
  (beginning-of-line)
  (if (bobp)
      (indent-line-to 0)
   (let ((not-indented t)
	 (indent-width 2)
	 (extent (point))
	 (statementp nil)
	 cur-indent)
      (cond ((looking-at "^[ \t]*end")
	     (save-excursion
	       (forward-line -1)
	       (setq cur-indent (- (current-indentation) indent-width)))
	     (if (< cur-indent 0)
		 (setq cur-indent 0)))
	    ((looking-at "^[ \t]*else")
	     (let ((pos (backwards-sal-statement "^[ t]*if")))
	       (when pos
		 (save-excursion
		   (goto-char pos) ; start of line
		   (setq cur-indent (forward-to-indentation 0))))))
	    ((looking-at sal-command-start-regexp)
	     (setq cur-indent 0))
	    (t
	     (save-excursion 
	       (while not-indented
		 ;; point moved to beginning of previous lines
		 (forward-line -1)
		 (cond ((looking-at "^[ \t]*end")
			(setq cur-indent (current-indentation))
			(setq not-indented nil))
		       ((looking-at sal-statement-start-regexp)
			(setq statementp t)
			(setq cur-indent (current-indentation))
			(setq not-indented nil))
		       ((bobp )
			(setq cur-indent 0)
			(setq not-indented nil))))
	       (when statementp
		 ;; have statement, default indent is current level.
		 ;; point is at beginning of last command line. check
		 ;; to see if there is an open sexpr, if so move to
		 ;; its column
		 (let ((pos (unbalanced-sexpr-indent (point) extent)))
		   (if pos (setq cur-indent pos)
		     (progn
		       ;; last command has balanced exprs, but it may
		       ;; be incomlete, ie previous line ends in ","
		       ;; if so, indent to arg column of continued
		       ;; command
		       (if (incomplete-statementp extent)
			   (setq cur-indent (statement-arg-indent (point)))
			 ;; increase indent level
			 (if (looking-at sal-indenting-substatements-regexp)
			     (setq cur-indent (+ (current-indentation)
						 indent-width))))
		       )))))))
      ;; If we didn't see an indentation hint, then allow no
      ;; indentation
      (if cur-indent
          (indent-line-to cur-indent)
        (indent-line-to 0)))))

(defun incomplete-statementp (extent)
  ;; if this function is called our current positino (extent) is after
  ;; a command with balanced statemnts. but the command may be
  ;; incomplete, ie the last line may end with a comma. in this case
  ;; we intent to the level of the first arg of the command
  (save-excursion
    (goto-char extent)
    (forward-line -1) ; this isnt right -- it should skip blank and
		      ; comment lines
    (end-of-line)
    (skip-syntax-backward " ")
    (if (char-equal (char-before ) ?\, )
	t
      nil)))

(defun statement-arg-indent (line)
  ;; line is beginning of line with command on it. move to colum start
  ;; of first arg after command name
  (save-excursion
    (goto-char line)
    (beginning-of-line)
    (skip-syntax-forward " ") ; move initatiion
    (skip-syntax-forward "^ ") ; move over command name
    (skip-syntax-forward " ") ; move to first arg
    (- (point ) line )))

(defun unbalanced-sexpr-indent (beg end)
  ;; return indentation of expr after the furthest right unmatched {([
  ;; beg is line start position
  (save-excursion
    (let* ((pos beg)
	   (char nil)
	   (lppos (list))
	   (lbpos (list))
	   (lcpos (list)))
      (goto-char pos) 
      (while (< pos end)
	(setq char (char-after ))
	(cond ((char-equal char ?\;)
	       (end-of-line)
	       (setq pos (point)))
	      ((char-equal char ?\() (setq lppos (cons pos lppos)))
	      ((char-equal char ?\)) (setq lppos (cdr lppos)) )
	      ((char-equal char ?\{) (setq lcpos (cons pos lcpos)))
	      ((char-equal char ?\}) (setq lcpos (cdr lcpos)) )
	      ((char-equal char ?\[) (setq lbpos (cons pos lbpos)))
	      ((char-equal char ?\]) (setq lbpos (cdr lbpos))))
	(forward-char)
	(setq pos (+ pos 1)))
      ;; if we have open ({[ find start of expr after it
      (if (or (car lppos) (car lcpos) (car lbpos))
	  (let ((open (apply #'max (append lppos lcpos lbpos))))
	    (goto-char open)
	    (setq char (char-after))
	    (if (char-equal char ?\[)
		(if (> open (+ beg 2))
		    (progn
		      (backward-char 2)
		      (if (looking-at "#a")
			  (skip-syntax-forward "^ ")
			(forward-char 3)))
		  (forward-char))
	      (forward-char))
	    (when (<  (point) end)
	      (skip-syntax-forward " "))
	    (setq here (point))
	    (beginning-of-line)
	    (- here (point)))
	nil))))

(defun sal-mode ()
  "Major mode for editing SAL files"
  (interactive)
  (kill-all-local-variables)
  (modify-syntax-entry ?\; "<" sal-mode-syntax-table)
  (modify-syntax-entry ?\n ">" sal-mode-syntax-table)
  ;; make hyphen and ops word constituents
  (dolist (c '(?- ?+ ?* ?/ ?^ ?%))
    (modify-syntax-entry c "w   " sal-mode-syntax-table))

  (set-syntax-table sal-mode-syntax-table)
  (setq indent-tabs-mode nil)
  (use-local-map sal-mode-map)
  (set (make-local-variable 'font-lock-defaults)
       '(sal-font-lock-keywords nil))
  (set (make-local-variable 'indent-line-function) 'sal-indent-line)  
  (set (make-local-variable 'fill-paragraph-function) 'lisp-fill-paragraph)  
  (set (make-local-variable 'comment-start) ";")
;  (set (make-local-variable 'paragraph-ignore-fill-prefix) t)

  ;(set (make-local-variable 'adaptive-fill-function)
  ;     (lambda () (if (looking-at "\\s-+\"[^\n\"]+\"\\s-*$") "")))

  (setq major-mode 'sal-mode)
  (setq mode-name "SAL")
  (run-hooks 'sal-mode-hook))

;(with-syntax-table sal-mode-syntax-table (string (char-syntax ?-)))
	    
(provide 'sal-mode)





