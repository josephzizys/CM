;;; **********************************************************************
;;; Copyright (C) 2008 Rick Taube
;;; This program is free software; you can redistribute it and/or   
;;; modify it under the terms of the Lisp Lesser Gnu Public License.
;;; See http://www.cliki.net/LLGPL for the text of this agreement.
;;; **********************************************************************

(require 'font-lock)

;(when (featurep 'xemacs) (require 'overlay))

(when (member 'aquamacs features)
  (add-to-list 'aquamacs-known-major-modes '(sal-mode . "SAL"))
  )

(add-to-list 'auto-mode-alist '("\\.sal$" . sal-mode))

;; Top level SAL statements (commands) start at column 0.  when the
;; user presses Command-Enter, we get the command starting before
;; point and send that string to lisp. forcing the column 0
;; restriction for commands is reasonable beacuse it makes things easy
;; to parse without implementing sal's parser in emacs lisp!

(defvar sal-commands
  '("begin" "chdir" "define" "exec" "if" "load" "loop"  
    "print" "set" "send" "sprout" ))

;; add non-top-level statements

(defvar sal-statements
  (append sal-commands 
	  '("run" "return" "unless" "wait" "when" "with")))

;; add literals that are not statements.

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
    (cons (regexp-opt '("#t" "#f" "#?") t) font-lock-constant-face)
    ;; if expr. why doesnt this work?
    ;;(cons "\\W\\?\\W" font-lock-constant-face)
;    (cons "[\\s-,]\\?[\\s-]*" font-lock-constant-face)
    ;; keywords
    (cons "[A-Za-z0-9\-]+:" font-lock-builtin-face))))

(defvar sal-font-lock-keywords sal-font-lock-keywords-3)


(when (not (featurep 'xemacs))
  (defun region-exists-p ()
    (and mark-active ; simple.el
	 (not (null (mark))))))

(defun cm-running-p ()
  (and (get-buffer "*scheme*")
       (comint-check-proc "*scheme*")))

(defun sal-enter (arg)
  (interactive "P") ; prefix arg = macroexpand
  (if (not (cm-running-p))
      (message "CM not running.")
    (let ((left 0) 
	  (right 0)
	  (expand arg)
	  (cmd nil)
	  (multi nil))
      (cond ((region-exists-p)
	     (setq left (region-beginning))
	     (setq right (region-end))
	     (setq multi t))
	    ((or (= (point) (point-max))
		 (looking-at "[ \t]*$"))
	     ;;(setq left (save-excursion (beginning-of-line) (point)))
	     (setq left (backwards-sal-statement 
			 sal-command-start-regexp ))
	     (setq right (point))))
      (if (and left right (< left right))
	  (let ((cmd (buffer-substring-no-properties left right)))
	    ;; send a call to sal
	    (when cmd
	      (if multi	(setq cmd (concat "begin\n" cmd "\nend")))
	      (comint-send-string 
	       (scheme-proc)
	       (concat "(sal " 
		       (prin1-to-string cmd)
		       " (quote ())"
		       (if expand " #t" " #f")
		       ")\n"
		       ))))))))

(defun sal-lookup-doc-at-point ()
  ;; help for symbol at point
  (interactive)
  (let ((cell (bounds-of-thing-at-point 'symbol)))
    (if cell
	(let ((word (buffer-substring-no-properties (car cell)
						    (cdr cell))))
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
			   (setq cur-indent
				 (statement-arg-indent (point)))
			 ;; increase indent level
			 (if (looking-at 
			      sal-indenting-substatements-regexp)
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

;;;
;;; sal-mode definition
;;;

(defvar sal-mode-syntax-table
  (make-syntax-table))

(defvar sal-mode-map
  (let ((map (make-sparse-keymap)))
    map)
  "Keymap for SAL major mode")

(define-key sal-mode-map (kbd "<A-return>") 'sal-enter)
(define-key sal-mode-map "\C-x\C-e" 'sal-enter)
(define-key sal-mode-map (kbd "<C-return>")  'sal-enter)
(define-key sal-mode-map (kbd "<A-d>") 'sal-lookup-doc-at-point)

(defvar sal-mode-hook nil)

;(add-hook 'sal-mode-hook
;          (defun sal-add-easy-menu ()
;            (easy-menu-add sal-easy-menu 'sal-mode-map)))

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
  (set (make-local-variable 'fill-paragraph-function)
       'lisp-fill-paragraph)  
  (set (make-local-variable 'comment-start) ";")
;  (set (make-local-variable 'paragraph-ignore-fill-prefix) t)

  ;(set (make-local-variable 'adaptive-fill-function)
  ;     (lambda () (if (looking-at "\\s-+\"[^\n\"]+\"\\s-*$") "")))

  (setq major-mode 'sal-mode)
  (setq mode-name "SAL")
  (run-hooks 'sal-mode-hook))

;(with-syntax-table sal-mode-syntax-table (string (char-syntax ?-)))
	    
(provide 'sal-mode)

