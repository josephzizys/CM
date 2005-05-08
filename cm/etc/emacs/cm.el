;; load this file into Emacs or Xemacs to load customizations
;; for Common Music running
;;;
;;; Add CM/CLM/CMN extensions to automode.

(setq auto-mode-alist
      (append '(("\\.clm$"  . lisp-mode)
		("\\.cm$"   . lisp-mode)
		("\\.cmn$"  . lisp-mode)
		("\\.ins$"  . lisp-mode)
		("\\.scm$"  . lisp-mode))
	      auto-mode-alist))
;;;
;;; ignore midi and sound files for autocompletion.

(setq completion-ignored-extensions
        (append (list ".midi" ".mid" ".snd" ".aiff" ".wav" ".osc")
	        completion-ignored-extensions))

;;;
;;; Indent CM/CLM/CMN forms properly

(put 'if 'common-lisp-indent-function 1)
(put 'new 'common-lisp-indent-function 1)
(put 'io 'common-lisp-indent-function 1)
(put 'defobject 'common-lisp-indent-function 'defun)
(put 'process 'common-lisp-indent-function 0)
(put 'with-sound 'common-lisp-indent-function 'defun)
(put 'definstrument 'common-lisp-indent-function 'defun)
(put 'dopairs 'common-lisp-indent-function  1)

;;
;; Do scheme too...

(put 'define 'common-lisp-indent-function 1)
(put 'define-class 'common-lisp-indent-function 2)
(put 'define-method 'common-lisp-indent-function 1)
(put 'letrec 'common-lisp-indent-function 1)

;; dont indent with Tab or evaluation in CLISP has problems.

(setq-default indent-tabs-mode nil)

;; pending delete mode for DWIM region editing

(pending-delete-mode 1)

(defun lisp-listener (cmd)
  (interactive (list (or inferior-lisp-program
			 (read-string "Shell command to start Lisp: "))))
  (cond ((not (slime-connected-p))
         (switch-to-buffer-other-frame (current-buffer))
         (slime cmd))
        (t
         (switch-to-buffer-other-frame (slime-repl-buffer nil)))))

(global-set-key "\C-x\l" 'lisp-listener) 

(cond ((member 'slime features)
       (add-hook 'slime-connected-hook
                 (lambda () (slime-repl-send-string "(cm)")))
       (define-key slime-mode-map "\C-x\C-e" 'slime-eval-at-mouse))
      (t
       (load "listener.el")))

(defun slime-eval-at-mouse ()
  ;; a better c-x c-e function for slime. is completely transparent,
  ;; ie if evaling at end of expr it behaves like slime's
  ;; eval-last-expression, otherwise it evals at point, whole region,
  ;; inside symbols and in whitespace (whole defun). if not at end of
  ;; expr it sends its contents to repl so its printed there instead
  ;; of the minibuffer.
  (interactive)
  (cond ((and mark-active (not (null (mark))))
         (slime-eval-region (region-beginning) (region-end)))
        ((or (looking-at "\\s\)")
             (save-excursion
               (backward-char 1)
               (looking-at "\\s\)")))
         (if (looking-at "\\s\)")
             (forward-char 1)) 
         (slime-eval-last-expression))
        ((or (looking-at "\\s\(")
             (save-excursion (forward-char 1) (looking-at "\\s\(")))
         (let ((b (bounds-of-thing-at-point 'sexp)))
           (if b
               (slime-repl-send-string
                (buffer-substring-no-properties (car b) (cdr b))))))
        ;; if on eol, space or tab find nominal end of expr and if it
        ;; closes a list then eval it
        ((looking-at "[$ 	]")
         (save-excursion
           (let (beg end)
             (end-of-defun)
             (backward-char 1)
             (if (looking-at "\\s\)")
                 (progn 
                   (forward-char 1)
                   (setq end (point))
                   (beginning-of-defun)
                   (setq beg (point))
                   (slime-repl-send-string
                    (buffer-substring-no-properties beg end)))))))
        (t
         ;; else we are not on whitespace, get surrounding sexp and send
         (save-excursion
           (let ((b (bounds-of-thing-at-point 'sexp)))
             (if b
                 (slime-repl-send-string
                  (buffer-substring-no-properties (car b) (cdr b)))))))
        ))



;;;
;;; Claim scratch buffer for Lisp mode if its empty.

(let ((scratch (get-buffer "*scratch*")))
  (if scratch
      (if (not (buffer-modified-p scratch))
          (with-current-buffer scratch
            (lisp-mode)))))








