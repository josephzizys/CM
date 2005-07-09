;;; **********************************************************************
;;; Copyright (C) 2002 Heinrich Taube (taube@uiuc.edu) 
;;; This program is free software; you can redistribute it and/or
;;; modify it under the terms of the GNU General Public License
;;; as published by the Free Software Foundation; either version 2
;;; of the License, or (at your option) any later version.
;;; 
;;; This program is distributed in the hope that it will be useful,
;;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;;; GNU General Public License for more details.
;;; **********************************************************************

;;; $Name$
;;; $Revision$
;;; $Date$

(define-class* <event-stream> (<container>)
  ((time :accessor object-time)
   (open :init-value #f :accessor io-open)
   (stream :init-value #f :init-keyword :stream
           :accessor event-stream-stream)
   (args :init-value '() :accessor event-stream-args)
   (direction :init-value #f :accessor io-direction))
  :name 'event-stream)

(define-class* <event-file> (<event-stream>)
  ((version :init-value 0 :accessor event-file-version
            :init-keyword :version)
   (versioning :init-value #f :init-keyword :versioning
               :accessor event-file-versioning)
   (elt-type :init-value :char :accessor file-elt-type
             :init-keyword :elt-type))
  :name 'event-file)

(define (io-classes )
  (class-subclasses <event-stream>))

(define (io-filename io)
  (object-name io))

(define-generic* init-io)
(define-generic* open-io)
(define-generic* close-io)
(define-generic* initialize-io)
(define-generic* deinitialize-io)
;(define-generic* play)
(define-generic* write-event)
(define-generic* import-events)

;;;
;;;
;;;

(define (write-event-streams class)
  ;; return the event stream classes for class or
  ;; any of its superclasses.
  (cond ((null? class)
         (list))
        ((pair? class)
         (let ((strs (write-event-streams (car class))))
           (if (null? strs)
             (write-event-streams (cdr class))
             strs)))
        (else ;(is-a? class <parameterized-class>)
         (let ((strs (class-event-streams class)))
           (if (null? strs)
             (write-event-streams (class-direct-superclasses class))
             strs)))))

(define (io-stream-classes )
  ;; return a list of all classes that handle file/port io.
  (do ((l (io-classes ) (cdr l))
       (r '()))
      ((null? l) (reverse r))
    (let ((h (io-class-file-types (car l))))
      (if h (push (car l) r)))))

(define (filename->event-class path)
  ;; returns an io class given a "name.type" namestring. if
  ;; name  is not "*" an exact match is required. othewise 
  ;; if the types are the same its a match.
  (let ((name (filename-name path))
        (type (filename-type path)))
    (if type
      (let ((matchone
	     (lambda (key name type) ; "*.midi" "test" "midi"
               (let ((nam (filename-name key))
		     (ext (filename-type key)))
                 (when (or (eq? nam :wild)  ; cltl...
			   (string=? nam "*"))
                   (set! nam #f))
                 (if nam
                   (if (string=? nam name)
                     (if (string=? ext type) #t #f)
                     #f)
                   (if (string=? ext type) #t #f))))))
        (do ((l (io-stream-classes ) (cdr l))
             (c #f))
            ((or (null? l) c)
             (or c (err "No file or port class for ~s." path)))
          (do ((x (io-class-file-types (car l)) (cdr x)))
              ((or (null? x) c) c)
            (if (matchone (car x) name type)
              (set! c (car l))))))
      (err "Missing .ext in file or port specification: ~s"
	   path))))
      
; (filename->event-class "test.clm")
; (filename->event-class "test.sco")
; (filename->event-class "test.wav")
; (filename->event-class "test")

;;;
;;; init-io called on file/port names or objects to initialize slots.
;;;

(define-macro (io str . args)
  `(init-io ,str ,@ args))

(define-method* (init-io io . inits)
  inits  ; gag 'unused var' warning from cltl compilers
  io)

(define-method* (init-io (string <string>) . inits)
  (let ((io (find-object string))) ; no type filter
    (if io
      (apply (function init-io) io inits)
      (let ((class (filename->event-class string)))
        (if class  ; allow class to specify maker
          (multiple-value-bind (init args)
                               (expand-inits class inits #t #t)
            (let ((n (apply (function make) class 
                            ':name string init )))
              (if (not (null? args ))
                (if #t ;(io-handler-args? n)
                  (set! (event-stream-args n) args)
                  (err "Not initializations for ~s: ~s."
                       (class-name class) args)))
              n))
          (err "~s is not a valid port or file name." string))))))

(define-method* (init-io (io <event-stream>) . inits)
  (unless (null? inits)
    (multiple-value-bind (init args)
                         (expand-inits (class-of io) inits #f #t)
      (dopairs (s v init)
	(slot-set! io s v))
      (if (not (null? args))
        (if #t ;(io-handler-args? io)
          (set! (event-stream-args io) args)
          (err "Not initializations for ~s: ~s."
               (class-name (class-of io)) args)))))
  io)

(define (bump-version stream)
  (if (event-file-versioning stream)
    (let ((vers (+ (event-file-version stream) 1)))
      (set! (event-file-version stream) vers)
      vers)
    #f))

(define (file-output-filename file)
  ;; if versioning return filename with version number
  ;; added otherwise return the file name.
  (let ((v (if (event-file-versioning file)
             (event-file-version file)
             #f))
	(n (object-name file)))
    (if (integer? v)
      (string-append (or (filename-directory n) "")
		     (filename-name n)
		     "-"
		     (number->string v)
		     "."
		     (filename-type n))
      n)))


(define-method* (open-io (obj <string>) dir . args)
  ;; default method assumes obj is string or filename
  (let ((io (apply (function init-io) obj args)))
    (apply (function open-io) io dir args)))

(define-method* (open-io (obj <event-file>) dir . args)
    args                ; gag 'unused var' warning from cltl compilers
  (let ((file #f)
	(name #f))
    (if (eq? dir :output)
      (cond ((event-stream-stream obj)
             (set! file (event-stream-stream obj)))
            (else 
             ;; mayby increment file version. done before writeing so
             ;; output name is constant until next time opened for
             ;; output
             (bump-version obj)
             (set! name (file-output-filename obj))
             ;; in scheme opening existing file is undefined...
             (if (file-exists? name) (delete-file name))
             (set! file (open-file name dir (file-elt-type obj)))))
      (if (eq? dir :input)
	(if (event-stream-stream obj)
          (set! file (event-stream-stream obj))
          (set! file (open-file (object-name obj) 
                                dir (file-elt-type obj))))
	(err "Direction not :input or :output: ~s" dir)))
    (set! (io-direction obj) dir)
    (set! (io-open obj) file)
    obj))

(define-method* (open-io (obj <seq>) dir . args)
  dir args  ; gag 'unused var' warnings from cltl compilers
  (remove-subobjects obj)
  obj)

;;;
;;; close-io
;;;

(define-method* (close-io io .  mode)
  mode  ; gag 'unused var' warnings from cltl compilers
  io)

(define-method* (close-io (io <event-file>) . mode)
  mode  ; gag 'unused var' warnings from cltl compilers
  (when (io-open io)
    (unless (event-stream-stream io)
      (close-file (io-open io) (io-direction io)))
    (set! (io-open io) #f))
  io)

;;;
;;; initalize-io and deinitialize-io. default methods do nothing.
;;;

(define-method* (initialize-io obj)
  obj)

(define-method* (deinitialize-io obj)
  obj)

(define (io-open? io)
  (io-open io))

(define-macro (with-open-io args . body)
  (let ((io (pop args))
	(path (pop args))
	(dir (pop args))
	(err? (gensym))
        (val (gensym)))
    `(let ((,io #f)
	   (,err? ':error))
      (dynamic-wind
       (lambda () #f)
       (lambda ()
	 (let ((,val #f)) 
           (set! ,io (open-io ,path ,dir ,@args))
           ,@ (if (eq? dir ':output)
                `((initialize-io ,io))
                (list))
           (set! ,val (begin ,@body))
           (set! ,err? #f)
           (if ,err? #f ,val)))
       (lambda ()
         (when ,io
           ,@ (if (eq? dir ':output)
                `((deinitialize-io ,io))
                (list))
           (close-io ,io ,err?)))))))

;;;
;;; current input and output streams
;;;

(define *in* #f)
(define *out* #f)
(define *last-output-file* #f)

(define (current-input-stream)
  *in*)

(define (current-output-stream)
  *out*)

(define (set-current-input-stream! stream)
  ;; dont insist that stream be an event-stream
  (unless (or (null? stream) 
              (is-a? <object> stream))
    (err "set-current-input-stream: ~s not a stream." stream))
  (set! *in* stream)
  stream)

(define (set-current-output-stream stream)
  ;; dont insist that stream be an event-stream
  (unless (or (null? stream) 
              (is-a? <object> stream))
    (err "set-current-output-stream: ~s not a stream." stream))
  (set! *out* stream)
  stream)

;;;
;;; events
;;;

(define (events object . args)
  ;; args are &key pairs or an optional time offset
  ;; followed by &key pairs.
  (let* ((to (if (and (pair? args)
                      (or (string? (car args))
                          (eq? (car args) #f)
                          (is-a? <object> (car args))))
                 (pop args)
                 (current-output-stream)))
         (ahead (if (and (pair? args)
                         (or (pair? (car args))
                             (number? (car args))))
                    (pop args)
                    0))
        (err? ':error))
    (when (odd? (length args))
      (err "Uneven initialization list: ~s." args))
    (dynamic-wind
     (lambda () #f)
     (lambda ()
       (let ((getobj
	      (lambda (x)
		(if (not (null? x))
		  (if (or (string? x) (symbol? x))
		    (find-object x)
		    x)
		  (err "Not an object specification: ~s." x)))))
	 (if (not to)
             (set! *out* #f)
             (begin
              (set! *out* (open-io (apply (function init-io) to args)
                                   ':output))
              (initialize-io *out*)))
	 (schedule-events *out* ;(lambda (e s) (write-event e *out* s))
			  (if (pair? object) 
			    (map (function getobj) object)
			    (getobj object))
			  ahead)
	 (set! err? #f)))
     (lambda ()
       (when *out*
	 (deinitialize-io *out*)
	 (close-io *out* err?))))
    (if (or err? (not *out*)) 
      #f
      (if (is-a? *out* <event-file>)
	(let ((path (file-output-filename *out*))
              (args (if #t
                      (event-stream-args *out*)
                      '()))
	      (hook (io-class-output-hook (class-of *out*))))
	  (when hook 
	    (apply hook path args))		; funcall
	  path)
	*out*))))



;;;
;;; write-event
;;;

(define-method* (write-event obj io time)
  obj io time ; gag 'unused var' warnings from cltl compilers
  )
           
(define-method* (write-event obj (io <seq>) time)
  (set! (object-time obj) time)
  (insert-object obj io))

;;;
;;; import-events
;;;

(define-method* (import-events (file <string>) . args )
  (let ((io (init-io file)))
    (apply (function import-events) io args)))

;;;
;;; play
;;;

(define (play file . args)
  (let* ((meta (filename->event-class file))
         (hook (io-class-output-hook meta)))
    (if hook
      (if (file-exists? file)
        (let* ((obj (find-object file #f))
               (old (if obj (event-stream-args obj) (list))))
          ;; let local args shadow any older args but force play
          ;; even if args in file say not too.
          (apply hook file :play #t (append args old))
          file)
        #f)
      #f)))

;;;
;;; receive
;;;

(define *receive-mode* #f)

(cond-expand
 (openmcl (set! *receive-mode* ':threaded))
 (gauche (set! *receive-mode* ':threaded))
 (cmu (set! *receive-mode* ':periodic))
 (sbcl (set! *receive-mode* ':periodic))
 (else (set! *receive-mode* #f)))

;(define-method* receive (hook stream . args)                )




;(define-method* (threaded-receive hook stream . args)
;  (with-args (args &key resolution)
;    hook resolution
;    (err "threaded-receive: no method defined in ~a for ~s."
;         (lisp-implementation-type) stream)))
;
;(define-method* (periodic-receive hook stream . args)
;  (with-args (args &key resolution)
;    hook resolution
;    (err "threaded-receive: no method defined in ~a for ~s."
;         (lisp-implementation-type) stream)))
;
;(define-method* (callback-receive hook stream . args)
;  (with-args (args &key resolution)
;    hook resolution
;    (err "threaded-receive: no method defined in ~a for ~s."
;         (lisp-implementation-type) stream)))


