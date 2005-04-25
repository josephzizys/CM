;;; need to set to the directory where scsynth lives

(define *sc-directory* "/Applications/SuperCollider3/")

;;; executable to play sound files
(define *play* "/usr/local/bin/sndplay")

(define-class* <sc-file-stream> (<event-stream>)
  ((userargs :accessor sc-file-userargs :init-value '(:pad 5))
   (elt-type :init-value :byte :init-keyword :elt-type :accessor
             file-elt-type))
  :name 'sc-file-stream
  :metaclass <io-class>
  :file-types '("*.osc" ))

(define-method* (close-io (io <sc-file-stream>) . mode)
  mode
  (let ((pad (list-prop (sc-file-userargs io) :pad))
        (fp (io-open io)))
    (if pad
      (write-bundle (+ pad (object-time io)) '("c_set" 0 0) fp)
      (write-bundle (+ 5 (object-time io)) '("c_set" 0 0) fp)))
  (next-method))

(define (set-sc-output-hook! fn)
  (unless (or (not fn) (functionp fn))
    (error "Not a supercollider file hook: ~s" fn))
  (set! (io-class-output-hook <sc-file-stream>) fn)
  (values))

(define-method* (io-handler-args? (io <sc-file-stream>))
  #t)

(define-method* (io-handler-args (io <sc-file-stream>))
  (sc-file-userargs io))

(define-method* (set-io-handler-args! (io <sc-file-stream>) args)
  (set! (sc-file-userargs io) args)
  (values))

(define (set-sc-output-hook! fn)
  (unless (or (not fn) (functionp fn))
    (error "Not a supercollider file hook: ~s" fn))
  (set! (io-class-output-hook <sc-file-stream>) fn)
  (values))

;;; i use the carbon version of emacs. when launched as
;;; double-clickable app (as opposed to running from command line) it
;;; will not read environment variables unless one has them set up in
;;; ~/.MacOSX/environment.plist (read
;;; http://developer.apple.com/qa/qa2001/qa1067.html). to get around
;;; this I am using ccl::setenv if to set up the proper environment
;;; variables that scsynth seems to need to run correctly if
;;; (ccl::getenv "SC_SYNTHDEF_PATH") and/or (ccl::getenv
;;; "SC_PLUGIN_PATH") return #f

(define (play-sc-file file . arg)
  (with-args (args &key output (channels 2) play? &allow-other-keys)
    (let* ((synthdef-path (string-append *sc-directory* "synthdefs"))
           (plugin-path (string-append *sc-directory* "plugins"))
           (scsynth (string-append *sc-directory* "scsynth"))
           (osc-file file )   ; no truename in scheme
           (output-file #f))
      ;; if output is specified with a path, output to that location
      ;; if output is specified and is just file name with no path,
      ;; output to same directory as *.osc file if output is not
      ;; specified, output to "test.aiff" in same directory as *.osc
      ;; file
      (if output
	(if (filename-directory output)
          (set! output-file output)
	  (set! output-file
                (string-append (or (filename-directory osc-file) "")
                               output)))
        (set! output-file (string-append (or (filename-directory osc-file) "")
                                         "test.aiff")))
      ;;if can't find sc environment variable set them
      (if (not (env-var  "SC_SYNTHDEF_PATH"))
	(set-env-var "SC_SYNTHDEF_PATH" synthdef-path))
      (if (not (env-var  "SC_PLUGIN_PATH"))
	(set-env-var "SC_PLUGIN_PATH" plugin-path))

      ;;run command
      (shell (format #f "~S -N ~S _ ~S 44100 AIFF int16 -o ~S" 
                     scsynth osc-file
                     output-file channels) :output #t)
      ;;play sound file?
      (when play?
        (shell (format #f "~a ~a" *play* output-file))))))

(set-sc-output-hook! (function play-sc-file))

;;;;;
;;;;;
;;;;; SC COMMANDS 
;;;;;
;;;;;

(define (return-init-args class)
  (map (function slot-definition-name) (class-slots (class-of class))))

; hkt: defined by scheme and added in level1.lisp
;(define (keyword->string kw)
;  (string-downcase (symbol-name kw)))

; hkt: dont inherit from event or else object-time has two slots.
(defobject scsynth () 
  ((beg :initform 0 :accessor object-time)
   (node :initform -1 :accessor node)
   (add-action :initform 1 :accessor add-action)
   (target :initform 0 :accessor target)

   (arg-list :initform '() :accessor arg-list))
  (:parameters node add-action target beg)
  (:writers ))

; hkt: a sc-writer function could generate all write-event methods for
; subclasses of scsynth and remove the runtime consing of this
; initialize function

(define-method* (initialize (obj <scsynth>) initargs)
  (next-method)
  (let ((slots (return-init-args obj))
        (args (list #f))) ; cdr holds arg data
    (do ((head slots (cdr head))
         (tail args)
         (slot #f)) 
        ((null? head)
         (set! (arg-list obj)
               (cdr args)))
      (set! slot (car head))
      (unless (member slot '(arg-list beg time))
        (cond ((member slot '(node add-action target))
               ;; hand-coded 'collects' is done
               (set-cdr! tail (list (slot-ref obj slot)))
               (set! tail (cdr tail)))
              (else
               (set-cdr! tail (list (keyword->string slot)
                                    (slot-ref obj slot)))
               (set! tail (cddr tail))))))))

(define-method* (write-event (obj <scsynth>) (io <sc-file-stream>) time)
  (let ((fp (io-open io)))
    (let* ((synthname (string-downcase
                       (symbol-name (class-name (class-of obj))))))
      (set! (object-time io) time)
      (write-bundle time (append (list "/s_new" synthname)
                                 (arg-list obj))
                    fp))))

;;; hkt: sc-command has to be defined before dependant defobjects are
;;; expanded.

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defobject sc-cmd () ; no event
    ((beg :initform 0 :accessor object-time))
    (:parameters beg)
    (:writers )
    ))

;;;
;;; Loads a file of synth definitions. Resident definitions with the
;;; same names are overwritten.

(defobject load-synthdef (sc-cmd)
  ((path :initform '() :accessor path))
  (:parameters path beg)
  (:writers )
  )

(define (load-synthdef path)
  (list "/d_load" path))

(define-method* (write-event (obj <load-synthdef>) (io <sc-file-stream>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (load-synthdef (slot-ref obj 'path))
                  fp)))

;;; Loads a directory of synth definitions files. Resident definitions
;;; with the same names are overwritten.

(defobject load-synthdef-dir (sc-cmd)
  ((path :accessor path))
  (:parameters path beg)
  (:writers ))

(define (load-synthdef-dir path)
  (list "d_loadDir" path))

(define-method* (write-event (obj <load-synthdef-dir>) (io <sc-file-stream>)
                             time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (load-synthdef-dir (slot-ref obj 'path))
                  fp)))

;;;;;

(defobject node-free (sc-cmd)
  ((node :accessor node))
  (:parameters node beg)
  (:writers ))

(define (node-free nodes)
  (let ((msg #f))
    (typecase nodes 
      (number
       (set! msg (list "n_free" nodes)))
      (sequence
       (set! msg (append '("n_free") nodes))))
    msg))

(define-method* (write-event (obj <node-free>) (io <sc-file-stream>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (node-free (slot-ref obj 'node))
                  fp)))

;;;;;;;;;;

(defobject node-set (sc-cmd)
  ((node :accessor node)
   (control-values :accessor control-values)
   (beg :accessor object-time))
  (:parameters beg node control-values)
  (:writers ))

(define (node-set node ctrl-values)
  (let ((msg #f))
    (set! msg (list "/n_set" node))
    (dolist (i ctrl-values)
      (if (keyword? i)
        (set! msg (append! msg (list (keyword->string i))))
        (set! msg (append! msg (list i)))))
    msg))

(define-method* (write-event (obj <node-set>) (io <sc-file-stream>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (node-set (slot-ref obj 'node)
                                 (slot-ref obj 'control-values))
                  fp)))

;;;;;;;;;;

(defobject node-map (sc-cmd)
  ((node :accessor node )
   (control-buses :accessor control-buses))
  (:parameters node control-buses beg )
  (:writers ))

(define (node-map node ctrl-buses)
  (let ((msg #f))
    (set! msg (list "/n_map" node))
    (dolist (i ctrl-buses)
      (if (keyword? i)
        (set! msg (append! msg (list (keyword->string i))))
        (set! msg (append! msg (list i)))))
    msg))

(define-method* (write-event (obj <node-map>) (io <sc-file-stream>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (node-map (slot-ref obj 'node)
                                 (slot-ref obj 'control-buses))
                  fp)))

;;;;;;

(defobject node-before (sc-cmd)
  ((node :accessor node)
   (before :accessor before))
  (:parameters node before beg)
  (:writers ))

(define (node-before node before-node)
  (list "/n_before" node before-node))

(define-method* (write-event (obj <node-before>) (io <sc-file-stream>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (node-before (slot-ref obj 'node)
                                    (slot-ref obj 'before)) 
                  fp)))

;;;;;;

(defobject node-after (sc-cmd)
  ((node :accessor node)
   (after :accessor after))
  (:parameters node after beg)
  (:writers ))

(define (node-after node after-node)
  (list "/n_before" node after-node))

(define-method* (write-event (obj <node-after>) (io <sc-file-stream>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (node-after (slot-ref obj 'node) 
                                   (slot-ref obj 'after))
                  fp)))


;;;GROUP COMMANDS

(defobject group-new (sc-cmd)
  ((id :accessor id)
   (add-action :initform 0 :accessor add-action)
   (target :accessor target))
  (:parameters id add-action target beg)
  (:writers ))

(define (group-new new-id action target)
  (list "/g_new" new-id action target))

(define-method* (write-event (obj <group-new>) (io <sc-file-stream>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (group-new (id obj) (add-action obj) (target obj)) fp)))

;;;;

(defobject group-head (sc-cmd)
  ((node :accessor node)
   (group :accessor group))
  (:parameters node group beg)
  (:writers ))

(define (group-head group node)
  (list "/g_head" group node))

(define-method* (write-event (obj <group-head>) (io <sc-file-stream>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (group-head (group obj) (node obj)) fp)))

;;;;;;

(defobject group-tail (sc-cmd)
  ((node :accessor node)
   (group :accessor group))
  (:parameters node group beg)
  (:writers ))

(define (group-tail group node)
  (list "/g_tail" group node))

(define-method* (write-event (obj <group-tail>) (io <sc-file-stream>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (group-tail (group obj) (node obj)) fp)))
    

;;;;;

(defobject group-free-all (sc-cmd)
  ((group :accessor group))
  (:parameters group beg)
  (:writers ))

(define (group-free-all group)
  (list "/g_freeAll" group))

(define-method* (write-event (obj <group-free-all>) (io <sc-file-stream>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (group-free-all (group obj)) fp)))

;;;;

(defobject group-deep-free (sc-cmd)
  ((group :accessor group))
  (:parameters group beg)
  (:writers ))

(define (group-deep-free group)
  (list "/g_deepFree" group))
    
(define-method* (write-event (obj <group-free-all>) (io <sc-file-stream>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (group-deep-free (group obj)) fp)))


;;;;;;

(defobject ugen-command (sc-cmd)
  ((node :accessor node)
   (ugen-index :accessor ugen-index)
   (command-name :accessor command-name)
   (args :accessor args))
  (:parameters node ugen-index command-name args beg)
  (:writers ))

(define (ugen-command node ugen-index command-name rest)
  (let ((msg #f))
    (set! msg (list "/u_cmd" node ugen-index command-name))
    (set! msg (append msg rest))
    msg))

(define-method* (write-event (obj <ugen-command>) (io <sc-file-stream>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (ugen-command (slot-ref obj 'node)
                                     (slot-ref obj 'ugen-index)
                                     (slot-ref obj 'command-name)
                                     (slot-ref obj 'args))
                  fp)))


;;;;;;;;;;;

(defobject buffer-alloc (sc-cmd)
  ((bufnum :accessor bufnum)
   (frames :accessor frames)
   (channels :accessor channels :initform 1))
  (:parameters bufnum frames channels beg)
  (:writers ))

(define (buffer-alloc buf-num num-frames num-chans)
  (list "/b_alloc" buf-num num-frames num-chans))

(define-method* (write-event (obj <buffer-alloc>) (io <sc-file-stream>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (buffer-alloc (slot-ref obj 'bufnum)
                                     (slot-ref obj 'frames)
                                     (slot-ref obj 'channels))
                  fp)))
    
;;;;

(defobject buffer-alloc-read (sc-cmd)
  ((bufnum :accessor bufnum)
   (file :accessor file)
   (start-frame :initform 0 :accessor start-frame)
   (frames :initform 0 :accessor frames))
  (:parameters bufnum frames start-frame file beg)
  (:writers ))

(define (buffer-alloc-read buf-num file start-frame num-frames)
  (let ((msg #f))
    (set! msg (list "/b_allocRead" buf-num file start-frame num-frames))
    msg))

(define-method* (write-event (obj <buffer-alloc-read>)
                             (io <sc-file-stream>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (buffer-alloc-read (slot-ref obj 'bufnum)
                                          (slot-ref obj 'file)
                                          (slot-ref obj 'start-frame)
                                          (slot-ref obj 'frames)) 
                  fp)))

;;;;;;;

(defobject buffer-read (sc-cmd)
  ((bufnum :accessor bufnum)
   (file :accessor file)
   (start-frame :initform 0 :accessor start-frame)
   (frames :initform -1 :accessor frames)
   (buffer-start-frame :initform 0 :accessor buffer-start-frame)
   (leave-open? :initform '() :accessor leave-open?))
  (:parameters bufnum file start-frame frames
               buffer-start-frame leave-open? beg)
  (:writers ))

(define (buffer-read buf-num file start-frame num-frames buf-start-frame leave-open?)
  (let ((msg #f))
    (set! msg (list "/b_read" buf-num file start-frame num-frames buf-start-frame (if leave-open? 1 0)))
    msg))

(define-method* (write-event (obj <buffer-read>) (io <sc-file-stream>) time)
    (let ((fp (io-open io)))
      (set! (object-time io) time)
      (write-bundle time (buffer-read (slot-ref obj 'bufnum)
                                      (slot-ref obj 'file)
                                      (slot-ref obj 'start-frame)
                                      (slot-ref obj 'frames)
                                      (slot-ref obj 'buffer-start-frame)
                                      (slot-ref obj 'leave-open?)) 
                    fp)))

;;;;;;

(defobject buffer-write (sc-cmd)
  ((bufnum :accessor bufnum)
   (file :accessor file)
   (header :accessor header)
   (sample-format :accessor sample-format)
   (frames :accessor frames)
   (start-frame :accessor start-frame)
   (leave-open? :accessor leave-open?))
  (:parameters bufnum file start-frame frames start-frame leave-open? beg)
  (:writers ))

(define (buffer-write buf-num file header-format sample-format num-frames
                      start-frame leave-open?)
  (let ((msg #f))
    (set! msg (list "/b_write" buf-num file header-format sample-format 
		    num-frames start-frame leave-open?))
    msg))

(define-method* (write-event (obj <buffer-write>) (io <sc-file-stream>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (buffer-write (slot-ref obj 'bufnum)
                                     (slot-ref obj 'file)
                                     (slot-ref obj 'header)
                                     (slot-ref obj 'sample-format)
                                     (slot-ref obj 'frames)
                                     (slot-ref obj 'start-frame)
                                     (slot-ref obj 'leave-open?))
                    fp)))
;;;;;

(defobject buffer-free (sc-cmd)
  ((bufnum :accessor bufnum))
  (:parameters bufnum beg)
  (:writers ))

(define (buffer-free buf-num)
  (list "/b_free" buf-num))

(define-method* (write-event (obj <buffer-free>) (io <sc-file-stream>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (buffer-free (bufnum obj)) fp)))


;;;;;;;;;;

(defobject buffer-zero (sc-cmd)
  ((bufnum :accessor bufnum))
  (:parameters bufnum beg)
  (:writers ))

(define (buffer-zero buf-num)
  (list "/b_zero" buf-num))

(define-method* (write-event (obj <buffer-zero>) (io <sc-file-stream>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (buffer-zero (bufnum obj)) fp)))


;;;;;;

(defobject buffer-set (sc-cmd)
  ((bufnum :accessor bufnum)
   (sample-values :accessor sample-values))
  (:parameters bufnum sample-values beg)
  (:writers ))

(define (buffer-set buf-num sample-values)
  (let ((msg #f))
    (set! msg (list "/b_set" buf-num))
    (dolist (i sample-values)
      (set! msg (append! msg i)))
    msg))

(define-method* (write-event (obj <buffer-set>) (io <sc-file-stream>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (buffer-set (bufnum obj) (sample-values obj)) fp)))
    
;;;;;;;;

(defobject buffer-fill (sc-cmd)
  ((bufnum :accessor bufnum)
   (start-sample :accessor start-sample)
   (num-samples :accessor num-samples)
   (value :accessor value))
  (:parameters bufnum start-sample num-samples value beg)
  (:writers ))

(define (buffer-fill buf-num start-sample num-samples val)
  (list "/b_fill" buf-num start-sample num-samples val))

(define-method* (write-event (obj <buffer-fill>) (io <sc-file-stream>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (buffer-fill (slot-ref obj 'bufnum) 
                                    (slot-ref obj 'start-sample)
                                    (slot-ref obj 'num-samples)
                                    (slot-ref obj 'value)) 
                  fp)))

;;;;;

(defobject buffer-close (sc-cmd)
  ((bufnum :accessor bufnum))
  (:parameters bufnum beg)
  (:writers ))

(define (buffer-close buf-num)
  (list "b_close" buf-num))

(define-method* (write-event (obj <buffer-close>) (io <sc-file-stream>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (buffer-close (slot-ref obj 'bufnum)) 
                  fp)))

;;;;;

(define *buffer-gen-flags*
  (list :normalize 1 :wavetable 2 :clear 4))

(defobject buffer-gen (sc-cmd)
  ((bufnum :accessor bufnum)
   (command :accessor command)
   (flags :accessor flags)
   (args :accessor args))
  (:parameters bufnum command flags args beg)
  (:writers ))
   
(define (buffer-gen bufnum command flags args)
  (append (list "/b_gen" bufnum command 
		(if (pair? flags) 
                  (do ((tail flags (cdr tail))
                       (bits 0))
                      ((null? tail) bits)
                    (set! bits (logior bits (list-prop *buffer-gen-flags* 
                                                       (car tail)))))
                  (list-prop *buffer-gen-flags* flags)))
          args))

(define-method* (write-event (obj <buffer-gen>) (io <sc-file-stream>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (buffer-gen (slot-ref obj 'bufnum)
                                   (slot-ref obj 'command)
                                   (slot-ref obj 'flags)
                                   (slot-ref obj 'args))
                  fp)))

;;;;;

(defobject control-set (sc-cmd)
  ((bus :accessor bus)
   (value :accessor value))
  (:parameters bus value beg)
  (:writers ))

(define (control-set bus-index control-value)
  (list "/c_set" bus-index control-value))

(define-method* (write-event (obj <control-set>) (io <sc-file-stream>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (control-set (slot-ref obj 'bus)
                                    (slot-ref obj 'value))
                  fp)))

;;;;;;;;;;;

(defobject control-fill (sc-cmd)
  ((bus :accessor bus)
   (num-buses :accessor num-buses)
   (value :accessor value))
  (:parameters bus num-buses value beg)
  (:writers ))

(define (control-fill bus-index num-buses val)
  (list "/c_fill" bus-index num-buses val))

(define-method* (write-event (obj <control-fill>) (io <sc-file-stream>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (control-fill (slot-ref obj 'bus) 
                                     (slot-ref obj 'num-buses)
                                     (slot-ref obj 'value))
                  fp)))


