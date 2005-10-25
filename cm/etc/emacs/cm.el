;; load this file into Emacs or Xemacs to load customizations
;; for running CLM, CM, CMN
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

;(put 'if 'common-lisp-indent-function 1)
(put 'new 'common-lisp-indent-function 1)
(put 'io 'common-lisp-indent-function 1)
(put 'defobject 'common-lisp-indent-function 'defun)
(put 'process 'common-lisp-indent-function 0)
(put 'defprocess 'common-lisp-indent-function 'defun)
(put 'with-sound 'common-lisp-indent-function 1)
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

;;;
;;;
;;;

(defvar inferior-lisp-init nil)

(defun cm ()
  (interactive )
  (lisp-listener inferior-lisp-program "(cm)"))

;;;
;;; Slime-aware Lisp listener.
;;;

;;; if listener-own-frame is true then slime starts in a new frame
;;; otherwise it starts in the current frame.

(defvar listener-own-frame (if (member 'slime features) nil t))

(defun lisp-listener (cmd &optional expr)
  (interactive (list (or inferior-lisp-program
			 (read-string "Shell command to start Lisp: "))))
  (if (not listener-own-frame)
      (if (not (slime-connected-p))
          (let (hook)
            (when expr
              (setq hook `(lambda () (slime-repl-send-string ,expr)))
              (add-hook 'slime-connected-hook hook))
            (slime cmd)
            )
        (switch-to-buffer (slime-repl-buffer nil)))
    (if (not (slime-connected-p))
        (let (hook)
          ;; this crock is needed because slime's repl
          ;; forces the user into the cl-user package
          (when expr
            (setq hook `(lambda () (slime-repl-send-string ,expr)))
            (add-hook 'slime-connected-hook hook))
          (switch-to-buffer-other-frame (current-buffer))
          (slime cmd)
          )
      (switch-to-buffer-other-frame (slime-repl-buffer nil)))))

;(global-set-key "\C-x\l" 'lisp-listener) 

(cond ((member 'slime features)
       (if (equal system-type 'darwin)
           (define-key slime-mode-map [(alt e)] 'slime-eval-at-mouse)))
      (t
       (load "listener.el")))

(defun slime-eval-at-mouse ()
  ;; a slime eval function that prints to the repl instead of the mini
  ;; buffer and handles all types of evaluation: (point) after expr,
  ;; (point) on expr start or end, (point) to (mark) region, (point)
  ;; inside/on symbols. if called on on white space it does an eval
  ;; toplevel form.
  (interactive)
  (save-excursion
    (let ((bag '(?\   ?\t ?\r ?\n))
          beg end pos)
      (cond ((and mark-active (not (null (mark))))
             ;; region active, parse each sexp and send
             ;(slime-eval-region (region-beginning) (region-end))
             (setq beg (region-beginning))
             (setq end (region-end))
             (goto-char beg)
             (while (< beg end)
               (while (and (< beg end)
                           (member (char-after) bag))
                 (setq beg (+ beg 1))
                 (forward-char 1))
               (goto-char beg)
               (when (< beg end)
                 (setq pos (bounds-of-thing-at-point 'sexp))
                 (cond ((not pos)
                        (setq beg end))
                       (t
                        (slime-repl-send-string
                         (buffer-substring-no-properties (car pos)
                                                         (cdr pos)))
                        (setq beg (+ (cdr pos) 1))
                        (goto-char beg))))))
            ((or (looking-at "\\s\)")
                 (save-excursion (backward-char 1)
                                 (looking-at "\\s\)")))
             (if (not (looking-at "\\s\)")) (backward-char 1))
             (setq pos (bounds-of-thing-at-point 'sexp))
             (when pos
               (slime-repl-send-string
                (buffer-substring-no-properties (car pos) 
                                                (cdr pos)))))
            ((or (looking-at "\\s\(")
                 (save-excursion (forward-char 1)
                                 (looking-at "\\s\(")))
             (if (not (looking-at "\\s\(")) (forward-char 1))
             (if pos (forward-char 1))
             (setq pos (bounds-of-thing-at-point 'sexp))
             (when pos
               (slime-repl-send-string
                (buffer-substring-no-properties (car pos)
                                                (cdr pos)))))
            ;; if on whitespace, find nominal end of expr and if it
            ;; closes a list then eval it
            ((member (char-after) bag) ;(looking-at "[$ 	]")
             (beginning-of-defun)
             (when (looking-at "\\s\(")
               (setq pos (bounds-of-thing-at-point 'sexp))
               (when pos
                 (slime-repl-send-string
                  (buffer-substring-no-properties (car pos) (cdr pos))))))
            (t
             ;; else we are not on whitespace, get surrounding sexp and send
             (setq pos (bounds-of-thing-at-point 'sexp))
             (when pos
               (slime-repl-send-string
                (buffer-substring-no-properties (car pos)
                                                (cdr pos)))))))))

;;;
;;; Claim virgin scratch buffer for Lisp mode if its empty.

(let ((scratch (get-buffer "*scratch*")))
  (if scratch
      (if (not (buffer-modified-p scratch))
          (with-current-buffer scratch
            (lisp-mode)))))








