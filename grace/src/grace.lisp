;;; **********************************************************************
;;; Copyright (C) 2007 Todd Ingalls, Rick Taube.
;;; This program is free software; you can redistribute it and/or modify
;;; it under the terms of the Lisp Lesser Gnu Public License. The text of
;;; this agreement is available at http://www.cliki.net/LLGPL            
;;; **********************************************************************

;;; $Name$
;;; $Revision$
;;; $Date$

(in-package :grace)

(defun insure-cm-version (vers)
  (let ((sym (and (find-package :CM)
		  (find-symbol "%CM-VERSION%" :CM))))
    (when (and sym (< (symbol-value sym) vers))
      (defparameter cl-user::%error-disconnect t)
      (let ((num (format nil "~a.~a.~a" (ldb (byte 4 8) vers)
			 (ldb (byte 4 4) vers) (ldb (byte 4 0) vers))))
	(error "Attempting to load a version of Common Music that will not work correctly in Grace. To fix the problem please upgrade your Common Music sources in '~a' to version ~A (or higher) and start Lisp again.~%"
	       (funcall (find-symbol "CM-DIRECTORY" :CL-USER))
	       num)))
    (values)))

#+(and sbcl darwin)
(eval-when (:load-toplevel :execute)
  (let* ((path (sb-posix::getenv "PATH"))
	 (dirs path))
   (if (null path)
       (setf dirs "/usr/local/bin:/bin:/sbin:/usr/bin:/usr/sbin")
       (progn
	 (unless (search "/usr/local/bin" path)
	   (setf dirs (concatenate 'string path ":/usr/local/bin")))
	 (unless (search ":/usr/bin" path)
	   (setf dirs (concatenate 'string path ":/usr/bin")))
	 (unless (search ":/usr/sbin" path)
	   (setf dirs (concatenate 'string path ":/usr/sbin")))
	 (unless (search ":/bin" path)
	   (setf dirs (concatenate 'string path ":/bin")))
	 (unless (search ":/sbin" path)
	   (setf dirs (concatenate 'string path ":/sbin")))))
   (unless (equal path dirs)
     (sb-posix::putenv (format nil "PATH=~A" dirs)))))

(defun grace-connection (&optional arg)
  (declare (ignore arg))
  (car *connections*))

(defun report-error (text)
  (connection-send-error (grace-connection) text))

;; Grace menubar command IDS are organized in "menubar blocks". each
;; id has its lower 7 bits available for encoding command
;; information. each menubar block has max 128 commands. Use this lisp
;; code to generate the enum definition for a menubar:

(defun enums (block enumname &rest names)
  (let* ((cmdinfo #xFF)
         (blockwidth (* 128 cmdinfo))
	 (blockstart (* blockwidth block)))
  (format t "  enum ~A {~%" enumname)
  (loop with m = (length names)
     for n in names for i from 1
     do (if (= i 128) (error "too many commands, block size = 128"))
     (format t "    cmd~A = ~D~:[,~;};~]~%" n
	     (+ (ash i 8) blockstart)
	     (= i m)))))
#||

;; Console menu enums [Console.h]

(enums 1 "ConsoleCommand" "GraceEditorNew" "GracePlotterNew"
         "GraceOpenFile" "GraceOpenRecentFile" "GraceClearRecentFiles"
	 "GracePreferences" "GraceQuit"
	 "EditCopy" "EditSelectAll"
	 "ViewClearText" "ViewFontSize"  "ViewThemes" "ViewOpacity"
	 "PortsMidiOutputOpen" "PortsMidiOutputTest" "PortsMidiOutputHush"
	 "PortsMidiOutputTuning" "PortsMidiOutputInstruments"
	 "PortsMidiInputOpen" "PortsMidiInputHook"
	 "PortsAudioSetup"
	 "LispConnect" 
	 "LispLoadSystem" "LispLoadRecentSystem" "LispClearRecentSystems"
	 "LispLoadFile" "LispLoadRecentFile" "LispClearRecentLoaded"
	 "LispConfigure" )

;; Editor/Buffer menu enums. [Buffer.h]
(enums 2 "EditorCommand"
       "FileNewSal" "FileNewLisp" "FileNewText" "FileOpen"
       "FileOpenRecent"
       "FileClearRecent" "FileSave" "FileSaveAs" "FileRevert"
       "FileClose"
       "EditUndo" "EditRedo" "EditCut" "EditCopy" "EditPaste"
       "EditSelectAll" "EditImport"

       "ViewFontList" "ViewFontSize" "ViewThemes"

       "OptionsHiliting" "OptionsParens" "OptionsEmacsMode"

       "LispEval" "LispSetPackage"
       "SalEval" "SymbolHelp"

       "CharForward" "CharBackward" "WordForward" 
       "WordBackward" "SexprForward" "SexprBackward"
       "LineForward" "LineBackward" "PageForward"
       "PageBackward" "GotoEOL" "GotoBOL" "GotoEOB"
       "GotoBOB" "GotoColumn" "GotoLine"  "Backspace"
       "Delete" "KillWord" "KillSexpr" "KillWhite"
       "KillLine" "InsertChar" "InsertLine" "OpenLine"
       "Complete" "Indent"  "ToggleReadWrite" )

;; Plotter menu enums [Plotter.h]
(enums 3 "PlotterCommand" "PlotterNew" "PlotterOpen" "PlotterSave" 
         "PlotterSaveAs" "PlotterImport" "PlotterExport"
	 "EditUndo" "EditRedo" "EditCut" "EditCopy" "EditPaste"
	 "EditSelectAll" "EditClear" "EditFind"
         "LayerAdd" "LayerDelete" "LayerSelect"
         "ViewStyle" "ViewVertical" "ViewBgStyle" 
         "ViewBgColor" "ViewBgPlotting"
	 "ViewBgMousing" "ViewMouseGuide" 
	 "ComposeDistributions" "ComposeGenerate"
	 "AnalyzeHistogram" "AnalyzeDeviation"
	 )

;; Items shared across different menubars. [Resource.h]
(enums 4 "SharedCommand" "WindowSelect" "WindowNative" 
       "WindowConsole" 
       "HelpWindow" "HelpSalTutorial" "HelpURL"
       "HelpAboutGrace")

||#














(defmethod asdf:perform :after ((a asdf:load-op) (b asdf:system))
  ;; notify grace of newly loaded system if connected
  (let ((con (grace-connection)))
    (when (and con (connection-open? con))
      (connection-send con +msgLoadSystem+
		       (asdf:component-name b)))
    ))

(defmethod asdf:perform :after ((a t)(b t))
  ;; flush tyo or warnings during file loading/compiling
  (force-output *standard-output*)
  (force-output *error-output*)
  ) 

(pushnew ':grace *features*)

;;;
;;; eof
;;;
