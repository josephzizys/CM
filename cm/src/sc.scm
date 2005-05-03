(define (return-init-args class)
  (map (function slot-definition-name) (class-slots (class-of class))))

(define *sc-directory* "/Applications/SuperCollider3/")

(define *play* "/usr/local/bin/sndplay")

(define-class* <sc-file> (<event-file>)
  ((elt-type :init-value :byte :init-keyword :elt-type
             :accessor file-elt-type))
  :name 'sc-file
  :metaclass <io-class>
  :file-types '("*.osc" ))  

(define-method* (close-io (io <sc-file>) . mode)
  mode
  (let ((pad (list-prop (event-stream-args io) ':pad))
        (fp (io-open io)))
    (if pad
      (write-bundle (+ pad (object-time io)) '("/c_set" 0 0) fp)
      (write-bundle (+ 5 (object-time io)) '("/c_set" 0 0) fp)))
  (next-method))

(define (set-sc-output-hook! fn)
  (unless (or (not fn) (procedure? fn))
    (err "Not a supercollider file hook: ~s" fn))
  (set! (io-class-output-hook <sc-file>) fn)
  (values))

(define *sc-audio-format-types*
  (list :int8 "int8" :int16 "int16" :int32 "int32" :float "float" 
        :double "double" :ulaw "ulaw" :alaw "alaw"))

(define *sc-audio-header-types*
  (list :aiff "AIFF" :wav "WAV" :sun "SUN" :ircam "IRCAM" :raw "RAW"))

(define (play-sc-file file . args)
  (let* ((output (list-prop args ':output))
         (channels (list-prop args ':channels 2))
         (playit (list-prop args ':play #t))
         (fmat (list-prop args ':format ':int16))
         (header #f)
         (srate (list-prop args ':srate))
         (verbose (list-prop args ':verbose ))
         (wait (list-prop args ':wait playit))
         (synthdef-path (string-append *sc-directory* "synthdefs"))
         (plugin-path (string-append *sc-directory* "plugins"))
         (scsynth (string-append *sc-directory* "scsynth"))
         (osc-file file )   ; no truename in scheme
         (output-file #f)
         (command #f))
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
      ;; set :header the same as output file-type
      (do ((l (length *sc-audio-header-types*))
           (f (filename-type output-file))
           (i 1 (+ i 2))
           (x #f))
          ((or header (not (< i l)))
           (unless header
             (err "Output file type ~s not one of ~s."
                  f  *sc-audio-header-types*)))
        (set! x (list-ref *sc-audio-header-types* i))
        (if (string-ci=? f x) (set! header x)))

      ;;if can't find sc environment variable set them
      (if (not (env-var  "SC_SYNTHDEF_PATH"))
	(set-env-var "SC_SYNTHDEF_PATH" synthdef-path))
      (if (not (env-var  "SC_PLUGIN_PATH"))
	(set-env-var "SC_PLUGIN_PATH" plugin-path))
      ;; cobble up command to print/exec
      (set! command (format #f
                            "~S -N ~S _ ~S ~S ~A ~A -o ~S"
                            scsynth
                            osc-file
                            output-file
                            srate
                            header
                            (list-prop *sc-audio-format-types* fmat)
                            channels))
      (if verbose (format #t "~%; ~a" command))
      (shell command :wait wait :output #f)
      (if playit (play output-file :wait #f))
      file))

(set-sc-output-hook! (function play-sc-file))

(define-class* <scsynth> (<event>)
  ((node :init-value -1 :init-keyword :node)
   (add-action :init-value 1 :init-keyword :add-action)
   (target :init-value 0 :init-keyword :target))
  :name 'scsynth
  )

(define-method* (write-event (obj <scsynth>) (io <sc-file>) time)
  (let ((fp (io-open io)))
    (let ((synthname (symbol->string (class-name (class-of obj))))
	  (slots (return-init-args obj)))
      (set! (object-time io) time)
      (write-bundle time (append!
			  (list "/s_new" synthname
                                (slot-ref obj 'node)
                                (slot-ref obj 'add-action)
                                (slot-ref obj 'target))
			  (loop for i in slots
				unless (member i '(node add-action target time))
				collect (keyword->string i)
				and collect (slot-ref obj i)))
                    fp))))

(define-method* (import-set-slots (obj <scsynth>) lst)
  (slot-set! obj 'node (pop lst))
  (slot-set! obj 'add-action (pop lst))
  (slot-set! obj 'target (pop lst))
  (let ((len (length lst)))
    (do ((i 0 (+ i 2)))
	((= i len))
      (slot-set! obj (string->expr (list-ref lst i)) 
                 (list-ref lst (+ 1 i))))))

(eval-when (:compile-toplevel :load-toplevel :execute)
  (define-class* <sc-cmd> (<event>) 
    ()
    :name 'sc-cmd)
  )

(defobject load-synthdef (sc-cmd)
  ((path :initform #f)) 
  (:parameters path)
  (:event-streams))

(define (load-synthdef path) 
  (list "/d_load" path))

(define-method* (write-event (obj <load-synthdef>) (io <sc-file>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (load-synthdef (slot-ref obj 'path)) fp)))

(define-method* (import-set-slots (obj <load-synthdef>) l)
  (slot-set! obj 'path (first l)))

(defobject load-synthdef-dir (sc-cmd)
  ((path :initform #f))
  (:parameters path)
  (:event-streams))

(define (load-synthdef-dir path) 
  (list "/d_loadDir" path))

(define-method* (write-event (obj <load-synthdef-dir>) (io <sc-file>)
                        time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (load-synthdef-dir (slot-ref obj 'path))
     fp)))

(define-method* (import-set-slots (obj <load-synthdef-dir>) l)
  (slot-set! obj 'path (pop l)))

(defobject node-free (sc-cmd) 
  ((node :initform #f))
 (:parameters node)
 (:event-streams))

(define (node-free nodes)
  (let ((msg #f))
    (cond ((number? nodes)
           (set! msg (list "n_free" nodes)))
          ((pair? nodes)
           (set! msg (append '("n_free") nodes)))
          (else
           (err "node-free: expect number or list but got ~s instead."
                nodes)))
    msg))

(define-method* (write-event (obj <node-free>) (io <sc-file>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (node-free (slot-ref obj 'node)) fp)))

(define-method* (import-set-slots (obj <node-free>) lst)
  (let ((len (length lst)))
    (if (= len 1)
      (slot-set! obj 'node (pop lst))
      (slot-set! obj 'node lst))))

(defobject node-run (sc-cmd)
  ((node :initform #f)
   (flag :initform #f))
  (:parameters node flag)
  (:event-streams))

(define (node-run node flag)
  (let ((msg #f))
    (if (pair? node)
	(begin
	  (set! msg (list "/n_run"))
	  (dotimes (i (length node))
	    (set! msg (append! msg (list (list-ref node i) 
                                         (if (list-ref flag i) 1 0))))))
      (set! msg (list "/n_run" node (if flag 1 0))))
    msg))

(define-method* (write-event (obj <node-run>) (io <sc-file>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (node-run (slot-ref obj 'node)
                                 (slot-ref obj 'flag))
                  fp)))

(define-method* (import-set-slots (obj <node-run>) lst)
  (let ((len (length lst)))
    (if (= len 2)
	(begin 
         (slot-set! obj 'node (pop lst))
         (slot-set! obj 'flag (pop lst)))
      (do ((i 0 (+ i 2)))
	  ((= i len))
        (slot-set! obj 'node (append! (slot-ref obj 'node)
                                      (list (list-ref lst i))))
        (slot-set! obj 'flag (append! (slot-ref obj 'flag)
                                      (list (list-ref lst (+ 1 i)))))))))


;;;changed control-values to controlS-values
(defobject node-set (sc-cmd)
  ((node :initform #f)
   (controls-values :initform #f))
  (:parameters node controls-values)
  (:event-streams))

(define (node-set node ctrl-values)
  (let ((msg #f))
    (set! msg (list "/n_set" node))
    (dolist (i ctrl-values)
      (if (keyword? i)
          (set! msg (append! msg (list (keyword->string i))))
	(set! msg (append! msg (list (exact->inexact i))))))
    msg))

(define-method* (write-event (obj <node-set>) (io <sc-file>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time
		  (node-set (slot-ref obj 'node)
	       (slot-ref obj 'controls-values))
     fp)))

(define-method* (import-set-slots (obj <node-set>) lst)
  (let ((cv #f) (len 0))
    (slot-set! obj 'node (pop lst))
    (set! len (length lst))
    (do ((i 0 (+ i 2)))
	((= i len))
      (set! cv (append! cv (list (string->keyword (list-ref lst i)) (list-ref lst (+ 1 i ))))))
    (slot-set! obj 'controls-values cv)))


(defobject node-setn (sc-cmd)
  ((node :initform #f)
   (controls-values :initform #f))
  (:parameters node controls-values)
  (:event-streams))

(define (node-setn node ctrl-values)
  (let ((msg #f))
    (set! msg (list "/n_set" node))
    (dolist (i ctrl-values)
      (if (keyword? i)
          (set! msg (append! msg (list (keyword->string i))))
	(if (pair? i)
	    (begin
	      (set! msg (append! msg (list (length i))))
	      (dolist (j i)
		(set! msg (append! msg (list (exact->inexact j))))))
	  (set! msg (append! msg (list (exact->inexact i)))))))
    msg))

(define-method* (write-event (obj <node-setn>) (io <sc-file>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time
     (node-set (slot-ref obj 'node)
	       (slot-ref obj 'controls-values))
     fp)))

(define-method* (import-set-slots (obj <node-setn>) lst)
  (let ((cv #f) (len 0) (num-vals 0))
    (slot-set! obj 'node (pop lst))
    (set! len (length lst))
    (do ((i 0))
	((= i len))
      (set! cv (append! cv (list (string->keyword (list-ref lst i)))))
      (set! num-vals (list-ref lst (incf i)))
      (dotimes (j num-vals)
	(set! cv (append! cv (list (list-ref lst (incf i))))))
      (incf i))
    (slot-set! obj 'controls-values cv)))


(defobject node-fill (sc-cmd)
  ((node :initform #f)
   (control :initform #f)
   (num-controls :initform #f)
   (value :initform #f))
  (:parameters node control num-controls value)
  (:event-streams))

(define (node-fill node control num-controls val)
  (let ((msg #f))
    (set! msg (list "/n_fill" node))
    (if (pair? control)
	(begin 
	  (dotimes (i (length control))
	    (set! msg (append! msg (list (keyword->string (list-ref control i))
				       (list-ref num-controls i) 
				       (exact->inexact (list-ref val i)))))))
      (set! msg (list "/n_fill" node (keyword->string control)
                      num-controls (exact->inexact val))))
    msg))

(define-method* (write-event (obj <node-fill>) (io <sc-file>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time
		  (node-fill (slot-ref obj 'node) 
                             (slot-ref obj 'control) 
			     (slot-ref obj 'num-controls)
                             (slot-ref obj 'value))
		  fp)))

(define-method* (import-set-slots (obj <node-fill>) lst)
  (let ((len 0))
    (slot-set! obj 'node (pop lst))
    (set! len (length lst))
    (if (= len 3)
	(begin
         (slot-set! obj 'control (string->keyword (pop lst)))
         (slot-set! obj 'num-controls (pop lst))
         (slot-set! obj 'value (pop lst)))
      (do ((i 0 (+ i 3)))
	  ((= i len))
        (slot-set! obj 'control (append! (slot-ref obj 'control) 
                                         (list (list-ref lst i))))
        (slot-set! obj 'num-controls (append! (slot-ref obj 'num-controls)
                                              (list (list-ref lst (+ 1 i)))))
        (slot-set! obj 'value (append! (slot-ref obj 'value)
                                       (list (list-ref lst (+ 2 i)))))))))


(defobject node-map (sc-cmd)
  ((node :initform #f)
   (controls-buses :initform #f))
  (:parameters node controls-buses)
  (:event-streams))

(define (node-map node ctrl-buses)
  (let ((msg #f))
    (set! msg (list "/n_map" node))
    (dolist (i ctrl-buses)
      (if (keyword? i)
          (set! msg (append! msg (list (keyword->string i))))
          (set! msg (append! msg (list i)))))
    msg))

(define-method* (write-event (obj <node-map>) (io <sc-file>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time
     (node-map (slot-ref obj 'node)
      (slot-ref obj 'controls-buses))
     fp)))

(define-method* (import-set-slots (obj <node-map>) lst)
  (let ((cb #f) (len 0))
    (slot-set! obj 'node (pop lst))
    (set! len (length lst))
    (do ((i 0 (+ i 2)))
	((= i len))
      (set! cb (append! cb (list (string->keyword (list-ref lst i)) 
                                 (list-ref lst (+ 1 i ))))))
    (slot-set! obj 'controls-buses cb)))


(defobject node-mapn (sc-cmd)
  ((node :initform #f)
   (control :initform #f)
   (bus :initform #f)
   (num-controls :initform #f))
  (:parameters node control bus num-controls)
  (:event-streams))

(define (node-mapn node control bus num-controls)
  (let ((msg #f))
    (set! msg (list "/n_mapn" node))
    (if (pair? control)
	(begin 
	  (dotimes (i (length control))
	    (set! msg (append! msg (list (keyword->string (list-ref control i))
				       (list-ref bus i) 
				       (list-ref num-controls i))))))
      (set! msg (list "/n_fill" node (keyword->string control)
                      bus num-controls)))))

(define-method* (write-event (obj <node-mapn>) (io <sc-file>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time
		  (node-mapn (slot-ref obj 'node) (slot-ref obj 'control) 
			     (slot-ref obj 'value)
			     (slot-ref obj 'num-controls))
		  fp)))

(define-method* (import-set-slots (obj <node-mapn>) lst)
  (let ((len 0))
    (slot-set! obj 'node (pop lst))
    (set! len (length lst))
    (if (= len 3)
	(begin
         (slot-set! obj 'control (string->keyword (pop lst)))
         (slot-set! obj 'bus (pop lst))
         (slot-set! obj 'num-controls (pop lst)))
      (do ((i 0 (+ i 3)))
	  ((= i len))
        (slot-set! obj 'control (append! (slot-ref obj 'control)
                                         (list (list-ref lst i))))
        (slot-set! obj 'bus (append! (slot-ref obj 'bus)
                                     (list (list-ref lst (+ 1 i)))))
        (slot-set! obj 'num-controls
                   (append! (slot-ref obj 'num-controls) 
                            (list (list-ref lst (+ 2 i)))))))))


(defobject node-before (sc-cmd)
 ((node :initform #f)
  (before :initform #f))
 (:parameters node before)
 (:event-streams))

(define (node-before node before-node)
  (let ((msg #f))
    (if (pair? node)
	(begin
	  (set! msg (list "/n_before"))
	  (dotimes (i (length node))
	    (set! msg (append! msg (list (list-ref node i)
                                         (list-ref before-node i))))))
      (set! msg (list "/n_before" node before-node)))
    msg))

(define-method* (write-event (obj <node-before>) (io <sc-file>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time
     (node-before (slot-ref obj 'node) (slot-ref obj 'before))
     fp)))

(define-method* (import-set-slots (obj <node-before>) lst)
  (let ((len 0))
    (set! len (length lst))
    (if (= len 2)
	(begin
         (slot-set! obj 'node (pop lst))
         (slot-set! obj 'before (pop lst)))
      (do ((i 0 (+ i 2)))
	  ((= i len))
        (slot-set! obj 'node (append! (slot-ref obj 'node)
                                      (list (list-ref lst i))))
        (slot-set! obj 'before (append! (slot-ref obj 'before)
                                        (list (list-ref lst (+ 1 i)))))))))
  

(defobject node-after (sc-cmd)
  ((node :initform #f)
   (after :initform #f))
  (:parameters node after)
  (:event-streams))

(define (node-after node after-node)
  (let ((msg #f))
    (if (pair? node)
	(begin 
	  (set! msg (list "/n_after"))
	  (dotimes (i (length node))
	    (set! msg (append! msg (list (list-ref node i)
                                         (list-ref after-node i))))))
      (set! msg (list "/n_after" node after-node)))
    msg))

(define-method* (write-event (obj <node-after>) (io <sc-file>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time
     (node-after (slot-ref obj 'node) (slot-ref obj 'after)) fp)))

(define-method* (import-set-slots (obj <node-after>) lst)
  (let ((len 0))
    (set! len (length lst))
    (if (= len 2)
	(begin
         (slot-set! obj 'node (pop lst))
         (slot-set! obj 'after (pop lst)))
      (do ((i 0 (+ i 2)))
	  ((= i len))
        (slot-set! obj 'node (append! (slot-ref obj 'node)
                                      (list (list-ref lst i))))
        (slot-set! obj 'after (append! (slot-ref obj 'after)
                                       (list (list-ref lst (+ 1 i)))))))))


(defobject group-new (sc-cmd)
  ((id :initform #f)
   (add-action :initform 0)
   (target))
  (:parameters id add-action target)
  (:event-streams))

(define (group-new new-id action target)
  (let ((msg #f))
    (if (pair? new-id)
	(begin
	  (set! msg (list "/g_new"))
	  (dotimes (i (length new-id))
	    (set! msg (append! msg (list (list-ref new-id i)
                                         (list-ref action i) 
                                         (list-ref target i))))))
      (set! msg (list "/g_new" new-id action target)))
    msg))

(define-method* (write-event (obj <group-new>) (io <sc-file>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time
     (group-new (slot-ref obj 'id) (slot-ref obj 'add-action) 
                (slot-ref obj 'target)) fp)))

(define-method* (import-set-slots (obj <group-new>) lst)
  (let ((len 0))
    (set! len (length lst))
    (if (= len 3)
	(begin
         (slot-set! obj 'id (pop lst))
         (slot-set! obj 'add-action (pop lst))
         (slot-set! obj 'target (pop lst)))
      (do ((i 0 (+ i 3)))
	  ((= i len))
        (slot-set! obj 'id (append! (slot-ref obj 'id)
                                    (list (list-ref lst i))))
        (slot-set! obj 'add-action (append! (slot-ref obj 'add-action)
                                            (list (list-ref lst (+ 1 i)))))
        (slot-set! obj 'target (append! (slot-ref obj 'target)
                                        (list (list-ref lst (+ 2 i)))))))))


(defobject group-head (sc-cmd)
  ((node :initform #f)
   (group :initform #f))
  (:parameters node group)
  (:event-streams))

(define (group-head group node) 
  (let ((msg #f))
    (if (pair? group)
	(begin
	  (set! msg (list "/g_head"))
	  (dotimes (i (length group))
	    (set! msg (append! msg (list (list-ref group i) 
                                         (list-ref node i))))))
      (set! msg (list "/g_head" group node)))
    msg))

(define-method* (write-event (obj <group-head>) (io <sc-file>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (group-head (slot-ref obj 'group) 
                                   (slot-ref obj 'node)) fp)))

(define-method* (import-set-slots (obj <group-head>) lst)
  (let ((len (length lst)))
    (if (= len 2)
	(begin
         (slot-set! obj 'node (pop lst))
         (slot-set! obj 'group (pop lst)))
      (do ((i 0 (+ i 2)))
	  ((= i len))
        (slot-set! obj 'node (append! (slot-ref obj 'node)
                                      (list (list-ref lst i))))
        (slot-set! obj 'group (append! (slot-ref obj 'group)
                                       (list (list-ref lst (+ 1 i)))))))))


(defobject group-tail (sc-cmd)
 ((node :initform #f)
  (group :initform #f))
 (:parameters node group)
 (:event-streams))

(define (group-tail group node) 
  (let ((msg #f))
    (if (pair? group)
	(begin
	  (set! msg (list "/g_tail"))
	  (dotimes (i (length group))
	    (set! msg (append! msg (list (list-ref group i) 
                                         (list-ref node i))))))
      (set! msg (list "/g_tail" group node)))
    msg))

(define-method* (write-event (obj <group-tail>) (io <sc-file>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (group-tail (slot-ref obj 'group)
                                   (slot-ref obj 'node)) fp)))

(define-method* (import-set-slots (obj <group-tail>) lst)
  (let ((len (length lst)))
    (if (= len 2)
	(begin
         (slot-set! obj 'node (pop lst))
         (slot-set! obj 'group (pop lst)))
      (do ((i 0 (+ i 2)))
	  ((= i len))
        (slot-set! obj 'node (append! (slot-ref obj 'node) 
                                      (list (list-ref lst i))))
        (slot-set! obj 'group (append! (slot-ref obj 'group) 
                                       (list (list-ref lst (+ 1 i)))))))))


(defobject group-free-all (sc-cmd) 
  ((group :initform #f))
 (:parameters group)
 (:event-streams))

(define (group-free-all group)
  (let ((msg #f))
    (if (pair? group)
	(set! msg (append! (list "/g_freeAll") group))
      (set! msg (list "/g_freeAll" group)))
    msg))

(define-method* (write-event (obj <group-free-all>) (io <sc-file>)
                        time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (group-free-all (slot-ref obj 'group)) fp)))

(define-method* (import-set-slots (obj <group-free-all>) lst)
  (let ((len (length lst)))
    (if (= len 1)
      (slot-set! obj 'group (pop lst))
      (slot-set! obj 'group lst))))


(defobject group-deep-free (sc-cmd) 
  ((group :initform #f))
 (:parameters group)
 (:event-streams))

(define (group-deep-free group)
  (let ((msg #f))
    (if (pair? group)
	(set! msg (append! (list "/g_deepFree") group))
      (set! msg (list "/g_deepFree" group)))
    msg))

(define-method* (write-event (obj <group-deep-free>) (io <sc-file>)
                        time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (group-deep-free (slot-ref obj 'group)) fp)))

(define-method* (import-set-slots (obj <group-deep-free>) lst)
  (let ((len (length lst)))
    (if (= len 1)
      (slot-set! obj 'group (pop lst))
      (slot-set! obj 'group lst))))


(defobject ugen-command (sc-cmd)
 ((node :initform #f)
  (ugen-index :initform #f)
  (command-name :initform #f)
  (args :initform #f))
 (:parameters node ugen-index command-name args)
 (:event-streams))

(define (ugen-command node ugen-index command-name rest)
  (let ((msg #f))
    (set! msg (list "/u_cmd" node ugen-index command-name))
    (set! msg (append msg rest))
    msg))

(define-method* (write-event (obj <ugen-command>) (io <sc-file>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time
     (ugen-command (slot-ref obj 'node)
      (slot-ref obj 'ugen-index) 
      (slot-ref obj 'command-name)
      (slot-ref obj 'args))
     fp)))

(define-method* (import-set-slots (obj <ugen-command>) lst)
  (slot-set! obj 'node (pop lst))
  (slot-set! obj 'ugen-index (pop lst))
  (slot-set! obj 'command-name (pop lst))
  (slot-set! obj 'args (pop lst)))


(defobject buffer-alloc (sc-cmd)
 ((bufnum :initform #f)
  (frames :initform #f)
  (channels :initform 1))
 (:parameters bufnum frames channels)
 (:event-streams))

(define (buffer-alloc buf-num num-frames num-chans)
  (list "/b_alloc" buf-num num-frames num-chans))

(define-method* (write-event (obj <buffer-alloc>) (io <sc-file>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time
     (buffer-alloc (slot-ref obj 'bufnum) 
		   (slot-ref obj 'frames)
		   (slot-ref obj 'channels))
     fp)))

(define-method* (import-set-slots (obj <buffer-alloc>) lst)
  (slot-set! obj 'bufnum (pop lst))
  (slot-set! obj 'frames (pop lst))
  (slot-set! obj 'channels (pop lst)))


(defobject buffer-alloc-read (sc-cmd)
 ((bufnum :initform #f)
  (file :initform #f)
  (start-frame :initform 0)
  (frames :initform 0))
 (:parameters bufnum frames start-frame file)
 (:event-streams))

(define (buffer-alloc-read buf-num file start-frame num-frames)
  (let ((msg #f))
    (set! msg
          (list "/b_allocRead" buf-num file start-frame num-frames))
    msg))

(define-method* (write-event (obj <buffer-alloc-read>) (io <sc-file>)
                        time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time
     (buffer-alloc-read (slot-ref obj 'bufnum)
      (slot-ref obj 'file) (slot-ref obj 'start-frame)
      (slot-ref obj 'frames))
     fp)))

(define-method* (import-set-slots (obj <buffer-alloc-read>) lst)
  (slot-set! obj 'bufnum (pop lst))
  (slot-set! obj 'file (pop lst))
  (slot-set! obj 'start-frame (pop lst))
  (slot-set! obj 'frames (pop lst)))


(defobject buffer-read (sc-cmd)
  ((bufnum :initform #f)
   (file :initform #f)
   (start-frame :initform 0)
   (frames :initform -1)
   (buffer-start-frame :initform 0)
   (leave-open? :initform #f))
  (:parameters bufnum file start-frame frames buffer-start-frame
               leave-open?)
  (:event-streams))

(define (buffer-read buf-num file start-frame num-frames
                    buf-start-frame leave-open?)
  (let ((msg #f))
    (set! msg
          (list "/b_read"
                buf-num
                file
                start-frame
                num-frames
                buf-start-frame
                (if leave-open? 1 0)))
    msg))

(define-method* (write-event (obj <buffer-read>) (io <sc-file>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time
     (buffer-read (slot-ref obj 'bufnum) (slot-ref obj 'file)
      (slot-ref obj 'start-frame) (slot-ref obj 'frames)
      (slot-ref obj 'buffer-start-frame)
      (slot-ref obj 'leave-open?))
     fp)))

(define-method* (import-set-slots (obj <buffer-read>) lst)
  (slot-set! obj 'bufnum (pop lst))
  (slot-set! obj 'file (pop lst))
  (slot-set! obj 'start-frame (pop lst))
  (slot-set! obj 'frames (pop lst))
  (slot-set! obj 'buffer-start-frame (pop lst))
  (slot-set! obj 'leave-open? (pop lst)))


(defobject buffer-write (sc-cmd)
 ((bufnum :initform #f)
  (file :initform #f)
  (header :initform #f)
  (sample-format :initform #f)
  (frames :initform #f)
  (start-frame :initform #f)
  (leave-open? :initform #f))
 (:parameters bufnum file start-frame frames start-frame leave-open?)
 (:event-streams))

(define (buffer-write buf-num file header-format sample-format
                     num-frames start-frame leave-open?)
  (let ((msg #f))
    (set! msg
          (list "/b_write"
                buf-num
                file
                (if (keyword? header-format) 
                  (list-prop *sc-audio-header-types* header-format)
                  header-format)
		(if (keyword? sample-format)
                  (list-prop *sc-audio-format-types* sample-format)
                  sample-format)
                sample-format
                num-frames
                start-frame
                leave-open?))
    msg))

(define-method* (write-event (obj <buffer-write>) (io <sc-file>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time
     (buffer-write (slot-ref obj 'bufnum) (slot-ref obj 'file)
      (slot-ref obj 'header) (slot-ref obj 'sample-format)
      (slot-ref obj 'frames) (slot-ref obj 'start-frame)
      (slot-ref obj 'leave-open?))
     fp)))

(define-method* (import-set-slots (obj <buffer-write>) lst)
  (slot-set! obj 'bufnum (pop lst))
  (slot-set! obj 'file (pop lst))
  (slot-set! obj 'header (pop lst))
  (slot-set! obj 'sample-format (pop lst))
  (slot-set! obj 'frames (pop lst))
  (slot-set! obj 'start-frame (pop lst))
  (slot-set! obj 'leave-open? (pop lst)))


(defobject buffer-free (sc-cmd) 
  ((bufnum :initform #f))
  (:parameters bufnum)
  (:event-streams))

(define (buffer-free buf-num) 
  (list "/b_free" buf-num))

(define-method* (write-event (obj <buffer-free>) (io <sc-file>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (buffer-free (slot-ref obj 'bufnum)) fp)))

(define-method* (import-set-slots (obj <buffer-free>) lst)
  (slot-set! obj 'bufnum (pop lst)))


(defobject buffer-zero (sc-cmd) 
  ((bufnum :initform #f))
 (:parameters bufnum)
 (:event-streams))

(define (buffer-zero buf-num) 
  (list "/b_zero" buf-num))

(define-method* (write-event (obj <buffer-zero>) (io <sc-file>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (buffer-zero (slot-ref obj 'bufnum)) fp)))

(define-method* (import-set-slots (obj <buffer-zero>) lst)
  (slot-set! obj 'bufnum (pop lst)))


(defobject buffer-set (sc-cmd)
 ((bufnum :initform #f)
  (samples-values :initform #f))
 (:parameters bufnum samples-values)
 (:event-streams))

(define (buffer-set buf-num sample-values)
  (let ((msg #f))
    (set! msg (list "/b_set" buf-num))
    (dolist (i sample-values) 
      (set! msg (append! msg i)))
    msg))

(define-method* (write-event (obj <buffer-set>) (io <sc-file>)
time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (buffer-set (slot-ref obj 'bufnum)
                                   (slot-ref obj 'sample-values))
     fp)))

(define-method* (import-set-slots (obj <buffer-set>) lst)
  (slot-set! obj 'bufnum (pop lst))
  (slot-set! obj 'samples-values lst))
	  

(defobject buffer-setn (sc-cmd)
 ((bufnum :initform #f)
  (samples-values :initform #f))
 (:parameters bufnum samples-values)
 (:event-streams))

(define (buffer-setn buf-num samples-values)
  (let ((msg #f))
    (set! msg (list "/b_set" buf-num))
    (dolist (i samples-values)
      (if (pair? i)
	  (begin
	    (set! msg (append! msg (list (length i))))
	    (dolist (j i)
	      (set! msg (append! msg (list j)))))
	(set! msg (append! msg (list i)))))
    msg))

(define-method* (write-event (obj <buffer-setn>) (io <sc-file>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (buffer-set (slot-ref obj 'bufnum)
                                   (slot-ref obj 'sample-values))
     fp)))

(define-method* (import-set-slots (obj <buffer-setn>) lst)
  (let ((bv #f) (len 0) (num-vals 0) (s-vals))
    (slot-set! obj 'bufnum (pop lst))
    (set! len (length lst))
    (do ((i 0))
	((= i len))
      (set! s-vals #f)
      (set! bv (append! bv (list (list-ref lst i))))
      (set! num-vals (list-ref lst (incf i)))
      (dotimes (j num-vals)
	(set! s-vals (append! s-vals (list (list-ref lst (incf i))))))
      (set! bv (append! bv (list s-vals)))
      (incf i))
    (slot-set! obj 'samples-values bv)
    obj))


(defobject buffer-fill (sc-cmd)
 ((bufnum :initform #f)
  (start-sample :initform 0)
  (num-samples :initform #f)
  (value :initform #f))
 (:parameters bufnum start-sample num-samples value)
 (:event-streams))

(define (buffer-fill buf-num start-sample num-samples val)
  (let ((msg (list "/b_fill" buf-num )))
    (if (pair? start-sample)
	(dotimes (i (length start-sample))
	  (set! msg (append! msg (list (list-ref start-sample i)
                                       (list-ref num-samples i) 
                                       (list-ref val i)))))
      (set! msg (append! msg (list start-sample num-samples val))))
    msg))

(define-method* (write-event (obj <buffer-fill>) (io <sc-file>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time
     (buffer-fill (slot-ref obj 'bufnum)
      (slot-ref obj 'start-sample) (slot-ref obj 'num-samples)
      (slot-ref obj 'value))
     fp)))

(define-method* (import-set-slots (obj <buffer-fill>) lst)
  (let ((len 0))
    (slot-set! obj 'bufnum (pop lst))
    (set! len (length lst))
    (if (= len 3)
	(begin
         (slot-set! obj 'start-sample (pop lst))
         (slot-set! obj 'num-samples (pop lst))
         (slot-set! obj 'value (pop lst)))
      (do ((i 0 (+ i 3)))
	  ((= i len))
        (slot-set! obj 'start-sample (append! (slot-ref obj 'start-sample) 
                                              (list (list-ref lst i))))
        (slot-set! obj 'num-samples (append! (slot-ref obj 'num-samples)
                                             (list (list-ref lst (+ 1 i)))))
        (slot-set! obj 'value (append! (slot-ref obj 'value)
                                       (list (list-ref lst (+ 2 i)))))))))


(defobject buffer-close (sc-cmd) 
  ((bufnum :initform #f))
 (:parameters bufnum)
 (:event-streams))

(define (buffer-close buf-num) 
  (list "b_close" buf-num))

(define-method* (write-event (obj <buffer-close>) (io <sc-file>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time (buffer-close (slot-ref obj 'bufnum)) fp)))

(define-method* (import-set-slots (obj <buffer-close>) lst)
  (slot-set! obj 'bufnum (pop lst)))


(define *buffer-gen-flags* 
  (list :normalize 1 :wavetable 2 :clear 4))

(define *buffer-gen-commands*
  (list :sine1 "sine1" :sine2 "sine2" :sine3 "sine3" :cheby "cheby"))

(defobject buffer-gen (sc-cmd)
 ((bufnum :initform #f)
  (command :initform #f)
  (flags :initform #f)
  (args :initform #f))
 (:parameters bufnum command flags args)
 (:event-streams))

(define (buffer-gen bufnum command flags args)
  (append (list "/b_gen"
                bufnum
		(list-prop *buffer-gen-commands* command)
                (if (pair? flags)
                    (do ((tail flags (cdr tail)) (bits 0))
                        ((null tail) bits)
                      (set! bits
                            (logior bits
                                    (list-prop
                                     *buffer-gen-flags*
                                     (car tail)))))
                    (list-prop *buffer-gen-flags* flags)))
          args))

(define-method* (write-event (obj <buffer-gen>) (io <sc-file>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time
     (buffer-gen (slot-ref obj 'bufnum) (slot-ref obj 'command)
      (slot-ref obj 'flags) (slot-ref obj 'args))
     fp)))

(define-method* (import-set-slots (obj <buffer-gen>) lst)
  (slot-set! obj 'bufnum (pop lst))
  (slot-set! obj 'command (pop lst))
  (slot-set! obj 'flags (pop lst)) ;    should return keywords
  (slot-set! obj 'args lst))


(defobject control-set (sc-cmd)
 ((bus :initform #f)
  (value :initform #f))
 (:parameters bus value)
 (:event-streams))

(define (control-set bus-index control-value)
  (let ((msg #f))
    (if (pair? bus-index)
	(begin
	  (set! msg (list "/c_set"))
	  (dotimes (i (length bus-index))
	    (set! msg (append! msg (list (list-ref bus-index i) 
                                         (list-ref control-value i))))))
      (set! msg (list "/c_set" bus-index control-value)))
    msg))

(define-method* (write-event (obj <control-set>) (io <sc-file>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time
     (control-set (slot-ref obj 'bus) (slot-ref obj 'value)) fp)))

(define-method* (import-set-slots (obj <control-set>) lst)
  (slot-set! obj 'bus (pop lst))
  (slot-set! obj 'value (pop lst)))


(defobject control-setn (sc-cmd)
  ((bus :initform #f)
   (value :initform #f))
  (:parameters bus value)
  (:event-streams))

(define (control-setn bus val)
  (let ((msg #f))
    (if (pair? bus)
	(begin 
	  (set! msg (list "/c_setn"))
	  (dotimes (i (length bus))
	    (set! msg (append! msg (list (list-ref bus i))))
	    (set! msg (append! msg (list (if (pair? (list-ref val i)) 
                                           (length (list-ref val i))
                                           1))))
	    (set! msg (append! msg (if (pair? (list-ref val i))
                                     (list-ref val i)
                                     (list (list-ref val i)))))))
      (begin
	(set! msg (list "/c_setn" bus (length val)))
	(set! msg (append! msg (if (pair? val) val (list val))))))
    msg))

(define-method* (write-event (obj <control-setn>) (io <sc-file>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time
		  (control-setn (slot-ref obj 'bus)
				(slot-ref obj 'value))
		  fp)))

(define-method* (import-set-slots (obj <control-setn>) lst)
  (let ((len (length lst)) (num-vals 0) (s-vals))
    (if (= len 3)
	(begin
         (slot-set! obj 'bus (pop lst))
	  (set! num-vals (pop lst))
          (slot-set! obj 'value (pop lst)))
      (do ((i 0))
	  ((= i len))
	(set! s-vals #f)
        (slot-set! obj 'bus (append! (slot-ref obj 'bus)
                                     (list (list-ref lst i))))
	(set! num-vals (list-ref lst (incf i)))
	(dotimes (j num-vals)
	  (set! s-vals (append! s-vals (list (list-ref lst (incf i))))))
        (slot-set! obj 'value (append! (slot-ref obj 'value) (list s-vals)))
	(incf i)))))


(defobject control-fill (sc-cmd)
  ((bus :initform #f)
   (num-buses :initform #f)
   (value :initform #f))
  (:parameters bus num-buses value)
  (:event-streams))

(define (control-fill bus-index num-buses val)
  (let ((msg #f))
    (if (pair? bus-index)
	(begin 
	  (set! msg (list "/c_fill"))
	  (dotimes (i (length bus-index))
	    (set! msg (append! msg (list (list-ref bus-index i)
                                         (list-ref num-buses i)
                                         (exact->inexact (list-ref val i)))))))
      (set! msg (list "/c_fill" bus-index num-buses (exact->inexact val))))
    msg))

(define-method* (write-event (obj <control-fill>) (io <sc-file>) time)
  (let ((fp (io-open io)))
    (set! (object-time io) time)
    (write-bundle time
     (control-fill (slot-ref obj 'bus) (slot-ref obj 'num-buses)
      (slot-ref obj 'value))
     fp)))

(define-method* (import-set-slots (obj <control-fill>) lst)
  (let ((len (length lst)))
    (if (= len 3)
	(begin
         (slot-set! obj 'bus (pop lst))
         (slot-set! obj 'num-buses (pop lst))
         (slot-set! obj 'value (pop lst)))
      (do ((i 0 (+ i 3)))
	  ((= i len))
        (slot-set! obj 'bus (append! (slot-ref obj 'bus)
                                     (list (list-ref lst i))))
        (slot-set! obj 'num-samples (append! (slot-ref obj 'num-buses) 
                                             (list (list-ref lst (+ 1 i)))))
        (slot-set! obj 'value (append! (slot-ref obj 'value)
                                       (list (list-ref lst (+ 2 i)))))))))

;;;import events stuff

(define (sc-read-bytes str num)
  (let ((vec (make-u8vector num))
	(b #f))
    (dotimes (j num)
      (set! b (read-byte str #f #f))
      (if b 
	  (set! (aref vec j) b)
	(set! vec #f)))
    vec))

(define *sc-command-object-mappings* 
  (list "/d_load" 'load-synthdef 
	"/d_loadDir" 'load-synthdef-dir
	"/n_free" 'node-free
	"/n_set" 'node-set
	"/n_setn" 'node-setn
	"/n_map" 'node-map
	"/n_before" 'node-before
	"/n_after" 'node-after
	"/g_new" 'group-new
	"/g_head" 'group-head
	"/g_tail" 'group-tail
	"/g_freeAll" 'group-free-all
	"/g_deepFree" 'group-deep-free
	"/u_cmd" 'ugen-command
	"/b_alloc" 'buffer-alloc
	"/b_allocRead" 'buffer-alloc-read
	"/b_read" 'buffer-read
	"/b_write" 'buffer-write
	"/b_free" 'buffer-free
	"/b_zero" 'buffer-zero
	"/b_set" 'buffer-set
	"/b_fill" 'buffer-fill
	"/b_close" 'buffer-close
	"/b_gen" 'buffer-gen
	"/b_get" 'buffer-get
	"/b_getn" 'buffer-getn
	"/c_set" 'control-set
	"/c_setn" 'control-setn
	"/c_fill" 'control-fill))

(define (return-sc-class-symbol strg)
  (let ((pos (position strg *sc-command-object-mappings* :test #'equalp)))
    (if pos
	(list-ref *sc-command-object-mappings* (+ 1 pos))
      #f)))

(define (collect-type-list vec)
  (loop for i across vec
	until (= i 0)
	collect (code-char i)))

(define (parse-osc-vec vec)
  (let ((cmd #f)
        (pos 0)
        (timestamp #f)
        (typelist #f)
        (obj #f)
        (cmd-args #f))

    (if (not (equal (u8vector->string (u8vector-subseq vec 0 7)) "#bundle"))
	(err "bad file")
      (begin
	(set! timestamp (u8vector->uint (u8vector-subseq vec 8 12)))
	(set! timestamp
              (+ timestamp (exact->inexact (/ (u8vector->uint
                                               (u8vector-subseq vec 12 16))
                                              16777215))))
	(set! cmd (u8vector->string (u8vector-subseq vec 20)))
	(set! pos (+ 20 (length cmd)))
	
	(set! pos (+ pos (- 4 (mod pos 4))))
	(set! typelist (collect-type-list (u8vector-subseq vec pos)))
	(set! pos (+ (length typelist) pos))
	(set! pos (+ pos (- 4 (mod pos 4))))
	(set! cmd-args
              (loop for i in (rest typelist) with x = 0
                   do
                   (cond ((char= i #\s)
                          (set! x (u8vector->string (u8vector-subseq vec pos)))
                          (incf pos (+ (length x) (- 4 (mod (length x) 4)))))
                         ((char= i #\i)
                          (set! x (u8vector->int
                                   (u8vector-subseq vec pos (incf pos 4)))))
                         ((char= i #\f)
                          (set! x (u8vector->float 
                                   (u8vector-subseq vec pos (incf pos 4))))))
                 collect x))
	(if (equal cmd "/s_new")
          (begin
           (set! obj (make (find-class* (string->expr (first cmd-args)))
                           :time timestamp))
           (import-set-slots obj (rest cmd-args)))
	  (begin
	    (let ((class-symbol (return-sc-class-symbol cmd)))
	      (if class-symbol
		  (begin
		    (set! obj (make (find-class* class-symbol)
                                    :time timestamp))
		    (import-set-slots obj  cmd-args))))))
	obj))))

(define (read-osc-file fd)
  (let ((seq))
    (with-open-file (str fd :direction :input :element-type '(unsigned-byte 8))
      (set! seq (loop for i from 0 
		      with len = 0
		      with mess = #f
		      until (not len)
		      do
		      (set! len (sc-read-bytes str 4))
		      (if len
			  (begin
			    (set! len (u8vector->int len))
			    (set! mess (sc-read-bytes str len))))
		      collect (parse-osc-vec mess)))
      (set! seq (butlast seq 2)) ;kludge
      (make <seq> :subobjects seq))))

