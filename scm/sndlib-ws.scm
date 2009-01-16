;;; with-sound for a sndlib-only context (no Snd editor)

(provide 'sndlib-ws.scm)

(define *clm-srate* 44100)
(define *clm-file-name* "test.snd")
(define *clm-channels* 1)
(define *clm-data-format* mus-lfloat)
(define *clm-header-type* mus-next)
(define *clm-verbose* #f)
(define *clm-play* #f)
(define *clm-statistics* #f)
(define *clm-reverb* #f)
(define *clm-reverb-channels* 1)
(define *clm-reverb-data* '())
(define *clm-table-size* 512)
(define *clm-file-buffer-size* 65536)
(define *clm-locsig-type* mus-interp-linear)
(define *clm-clipped* #t)
(define *clm-array-print-length* 12)
(define *clm-player* #f) 
(define *clm-notehook* #f)
(define *clm-with-sound-depth* 0) ; for CM, not otherwise used
(define *clm-default-frequency* 0.0)
(define *clm-safety* (run-safety)); slightly different from CL/CLM but has similar effect
(define *clm-delete-reverb* #f)   ; should with-sound clean up reverb stream
(define *clm-threads* 4)
(define *clm-output-safety* 0)    ; if 1, assume output buffers will not need to be flushed except at the very end


(define (times->samples beg dur) 
  "(times->samples beg dur) converts beg and (+ beg dur) to samples, returning both in a list"
  (list (seconds->samples beg) (seconds->samples (+ beg dur))))


;;; -------- definstrument --------

;(define definstrument define*) -- old form 2-Nov-05

(define *definstrument-hook* #f) ; for CM

(defmacro definstrument (args . body)
  (let* ((name (car args))
	 (targs (cdr args))
	 (utargs (let ((arg-names '()))
		   (for-each
		    (lambda (a)
		      (if (not (keyword? a))
			  (if (symbol? a)
			      (set! arg-names (cons a arg-names))
			      (set! arg-names (cons (car a) arg-names)))))
		    targs)
		   (reverse arg-names)))
	 (doc (if (string? (car body))
		  (let ((val (car body)))
		    (set! body (cdr body))
		    val)
		  "no help")))
  `(begin 
     (define* (,name ,@targs)
       ,doc
       (if *clm-notehook*
	   (*clm-notehook* (symbol->string ',name) ,@utargs))
       ((lambda () ; for inner defines, if any
	  ,@body)))
     ,@(if *definstrument-hook*
           (list (*definstrument-hook* name targs))
           (list)))))



;;; -------- with-sound --------

(define* (with-sound-helper thunk 
			    :key (srate *clm-srate*) 
			          (output *clm-file-name*) 
				  (channels *clm-channels*)
				  (header-type *clm-header-type*)
				  (data-format *clm-data-format*)
				  (comment #f)
				  (verbose *clm-verbose*)
				  (reverb *clm-reverb*)
				  (revfile "test.rev")
				  (reverb-data *clm-reverb-data*)
				  (reverb-channels *clm-reverb-channels*)
				  (continue-old-file #f)
				  (statistics *clm-statistics*)
				  (scaled-to #f)
				  (play *clm-play*)
				  (clipped 'unset)
				  (notehook *clm-notehook*)               ; (with-sound (:notehook (lambda args (display args))) (fm-violin 0 1 440 .1))
				  (scaled-by #f)
				  (ignore-output #f)
				  (thread-output #f)
				  (thread-reverb #f)
				  (output-safety *clm-output-safety*))
  "with-sound-helper is the business portion of the with-sound macro"
  (let* ((old-srate (mus-srate))
	 (old-*output* *output*)
	 (old-*reverb* *reverb*)
	 (in-debugger #f)
	 (old-notehook *clm-notehook*)
	 (old-verbose *clm-verbose*)
	 (output-1 output)                    ; protect during nesting
	 (output-to-file (string? output))
	 (reverb-1 revfile)
	 (reverb-to-file (and reverb (string? revfile))))

    (if ignore-output
	(begin
	  (set! output-1 *clm-file-name*)
	  (set! output-to-file (string? output-1))))

    (dynamic-wind 

     (lambda () 
       (set! *clm-verbose* verbose)
       (set! *clm-notehook* notehook)
       (set! (clm-table-size) *clm-table-size*)
       (set! (clm-default-frequency) *clm-default-frequency*)
       (set! (mus-file-buffer-size) *clm-file-buffer-size*)
       (set! (locsig-type) *clm-locsig-type*)
       (set! (mus-array-print-length) *clm-array-print-length*)
       (if (equal? clipped 'unset)
	   (if (and (or scaled-by scaled-to)
		    (member data-format (list mus-bfloat mus-lfloat mus-bdouble mus-ldouble)))
	       (set! (mus-clipping) #f)
	       (set! (mus-clipping) *clm-clipped*))
	   (set! (mus-clipping) clipped))
       (set! (mus-srate) srate))

     (lambda ()
       (if (not thread-output)
	   (begin
	     
	     (if output-to-file
		 (begin
		   (if continue-old-file
		       (begin
			 (set! *output* (continue-sample->file output-1))
			 (set! (mus-srate) (mus-sound-srate output-1)))
		       (begin
			 (if (file-exists? output-1) 
			     (delete-file output-1))
			 (set! *output* (make-sample->file output-1 channels data-format header-type comment))))
		   (set! (mus-safety *output*) output-safety))
		 (begin
		   (if (not continue-old-file)
		       (if (vct? output-1)
			   (vct-fill! output-1 0.0)
			   (if (sound-data? output-1)
			       (sound-data-fill! output-1 0.0))))
		   (set! *output* output-1)))

	     (if reverb
		 (if reverb-to-file
		     (begin
		       (if continue-old-file
			   (set! *reverb* (continue-sample->file reverb-1))
			   (begin
			     (if (file-exists? reverb-1) 
				 (delete-file reverb-1))
			     (set! *reverb* (make-sample->file reverb-1 reverb-channels data-format header-type))))
		       (set! (mus-safety *reverb*) output-safety))
		     (begin
		       (if (not continue-old-file)
			   (if (vct? reverb-1)
			       (vct-fill! reverb-1 0.0)
			       (if (sound-data? reverb-1)
				   (sound-data-fill! reverb-1 0.0))))
		       (set! *reverb* reverb-1)))))

	   ;; else thread-output
	   (begin
	     (if (file-exists? output-1) 
		 (delete-file output-1))
	     (set! (thread-output) (make-sample->file output-1 channels data-format header-type comment))
	     (if thread-reverb
		 (begin
		   (if (file-exists? reverb-1) 
		       (delete-file reverb-1))
		   (set! (thread-reverb) (make-sample->file reverb-1 reverb-channels data-format header-type))))
	     (set! statistics #f)
	     ))

       (let ((start (if statistics (get-internal-real-time)))
	     (flush-reverb #f)
	     (cycles 0)
	     (revmax #f))

	 (catch 'mus-error
		thunk
		(lambda args
		  (display (format #f ";~%with-sound mus-error: ~{~A~^ ~}~%" (cdr args)))
		  (set! flush-reverb #t)))
		  
	 (if (and reverb 
		  (not flush-reverb)) ; i.e. not interrupted by error and trying to jump out
	     (begin
	       (if thread-reverb
		   (mus-close (thread-reverb))
		   (if reverb-to-file
		       (mus-close *reverb*)))
	       (if statistics 
		   (if reverb-to-file
		       (set! revmax (cadr (mus-sound-maxamp reverb-1)))
		       (if (vct? reverb-1)
			   (set! revmax (vct-peak reverb-1))
			   (if (sound-data? reverb-1)
			       (set! revmax (sound-data-peak reverb-1))))))
	       (if (not thread-reverb)
		   (begin
		     (if reverb-to-file
			 (set! *reverb* (make-file->sample reverb-1)))
		     (apply reverb reverb-data)
		     (if reverb-to-file
			 (mus-close *reverb*))
		     (if (and reverb-to-file *clm-delete-reverb*)
			 (delete-file reverb-1))))))

	 (if thread-output
	     (mus-close (thread-output))
	     (if output-to-file
		 (mus-close *output*)))

	 (let ((snd-output #f)
	       (cur-sync #f))
	   (if statistics
	       (begin
		 (set! cycles (exact->inexact (/ (- (get-internal-real-time) start) internal-time-units-per-second)))
		 (display (format #f "~%;~A:~%  maxamp~A:~{ ~,4F~}~%~A  compute time: ~,3F~%"
				  (if output-to-file
				      output-1
				      (if (vct? output-1) "vct" 
					  (if (sound-data? output-1) "sound-data"
					      (if (procedure? output-1) "function" 
						  "flush"))))
				  (if (or scaled-to scaled-by) 
				      " (before scaling)" 
				      "")
				  (if output-to-file
				      (let ((lst (mus-sound-maxamp output-1)))
					(do ((i 0 (+ i 2)))
					    ((>= i (length lst)))
					  (list-set! lst i (/ (list-ref lst i) (mus-srate))))
					lst)
				      (if (vct? output-1)
					  (list (vct-peak output-1))
					  (if (sound-data? output-1)
					      (sound-data-maxamp output-1)
					      0.0)))
				  (if revmax (format #f "  rev max: ~,4F~%" revmax) "")
				  cycles))))

	   (if (or scaled-to scaled-by)
	       (if output-to-file
		   ;; TODO scale the output
		   (display "can't scale output yet")
		   (if (vct? output-1)
		       (if scaled-to
			   (let ((pk (vct-peak output-1)))
			     (if (> pk 0.0)
				 (vct-scale! output-1 (/ scaled-to pk))))
			   (vct-scale! output-1 scaled-by))
		       (if (sound-data? output-1)
			   (if scaled-to
			       (let ((pk (sound-data-peak output-1)))
				 (if (> pk 0.0)
				     (sound-data-scale! output-1 (/ scaled-to pk))))
			       (sound-data-scale! output-1 scaled-by))))))

	   (if (and *clm-player* play output-to-file)
	       (*clm-player* output-1)))

	 output-1))

     (lambda () 
       (set! *clm-verbose* old-verbose)
       (set! *clm-notehook* old-notehook)
       (if *reverb*
	   (begin
	     (if thread-reverb
		 (mus-close (thread-reverb))
		 (mus-close *reverb*))
	     (set! *reverb* old-*reverb*)))
       (if *output*
	   (begin
	     (if thread-output
		 (mus-close (thread-output))
		 (if (mus-output? *output*)
		     (mus-close *output*)))
	     (set! *output* old-*output*)))
       (set! (mus-srate) old-srate)))))


(defmacro with-sound (args . body)
  `(with-sound-helper (lambda () ,@body) ,@args))



;;; -------- with-temp-sound --------

(defmacro with-temp-sound (args . body)
  `(let ((old-file-name *clm-file-name*))
     ;; with-sound but using tempnam for output (can be over-ridden by explicit :output)
     (dynamic-wind
	 (lambda () 
	   (set! *clm-file-name* (snd-tempnam)))
	 (lambda ()
	   (with-sound-helper (lambda () ,@body) ,@args)) ; dynamic-wind returns this as its result
	 (lambda ()
	   (set! *clm-file-name* old-file-name)))))


;;; -------- clm-load --------
;;;
;;; CM wants this to be a function so that it can use apply

(define (clm-load file . args) 
  "(clm-load file . args) loads 'file' in the context of with-sound"
  (apply with-sound-helper (lambda () (load file)) args))



;;; -------- sound-let --------
;;;
;;; (with-sound () (sound-let ((a () (fm-violin 0 .1 440 .1))) (mus-mix "test.snd" a)))

(defmacro sound-let (snds . body) 
  `(let ((temp-files '()))
     (begin
       (let ((val (let ,(map (lambda (arg) 
			       (if (> (length arg) 2)
				   `(,(car arg) (with-temp-sound ,(cadr arg) ,@(cddr arg)))
				   arg))
			     snds)
		    ,@body)))                         ; sound-let body
	 (for-each (lambda (file)                     ; clean up all local temps
		     (if (and (string? file)          ; is it a file? (might be a vct or sound-data object)
			      (file-exists? file))
			 (delete-file file)))
		   temp-files)
	 val))))                                      ; return body result



;;; -------- Common Music --------

(define* (init-with-sound
	  :key (srate *clm-srate*) 
	  (output *clm-file-name*) 
	  (channels *clm-channels*)
	  (header-type *clm-header-type*)
	  (data-format *clm-data-format*)
	  (comment #f)
	  ;(verbose *clm-verbose*) ; why is this commented out?
	  (reverb *clm-reverb*)
	  (revfile "test.rev")
	  (reverb-data *clm-reverb-data*)
	  (reverb-channels *clm-reverb-channels*)
	  (continue-old-file #f)
	  (statistics *clm-statistics*)
	  (scaled-to #f)
	  (play *clm-play*)
	  (scaled-by #f))
  "(init-with-sound . args) is the first half of with-sound; it sets up the CLM output choices, reverb, etc. Use \
finish-with-sound to complete the process."
  (let ((old-srate (mus-srate))
	(start (if statistics (get-internal-real-time)))
	(output-to-file (string? output))
	(reverb-to-file (and reverb (string? revfile))))
    (if output-to-file
	(if continue-old-file
	    (begin
	      (set! *output* (continue-sample->file output))
	      (set! (mus-srate) (mus-sound-srate output)))
	    (begin
	      (if (file-exists? output) 
		  (delete-file output))
	      (set! *output* (make-sample->file output channels data-format header-type comment))))
	(begin
	  (if (not continue-old-file)
	      (if (vct? output)
		  (vct-fill! output 0.0)
		  (sound-data-fill! output 0.0)))
	  (set! *output* output)))

    (if reverb
	(if reverb-to-file
	    (if continue-old-file
		(set! *reverb* (continue-sample->file revfile))
		(begin
		  (if (file-exists? revfile) 
		      (delete-file revfile))
		  (set! *reverb* (make-sample->file revfile reverb-channels data-format header-type))))
	    (begin
	      (if (not continue-old-file)
		  (if (vct? revfile)
		      (vct-fill! revfile 0.0)
		      (sound-data-fill! revfile 0.0)))
	      (set! *reverb* revfile))))

    (list 'with-sound-data
	  output
	  reverb
	  revfile
	  old-srate
	  statistics
	  #f ;to-snd
	  scaled-to
	  scaled-by
	  play
	  reverb-data
	  start)))

(define (finish-with-sound wsd)
  "(finish-with-sound wsd) closes the notelist process started by init-with-sound"
  (if (eq? (car wsd) 'with-sound-data)
      (let ((cycles 0)
	    (output (list-ref wsd 1))
	    (reverb (list-ref wsd 2))
	    (revfile (list-ref wsd 3))
	    (old-srate (list-ref wsd 4))
	    (statistics (list-ref wsd 5))
	    ;(to-snd (list-ref wsd 6))
	    (scaled-to (list-ref wsd 7))
	    (scaled-by (list-ref wsd 8))
	    (play (list-ref wsd 9))
	    (reverb-data (list-ref wsd 10))
	    (start (list-ref wsd 11)))

	(if reverb
	    (begin
	      (mus-close *reverb*)
	      (if (string? revfile)
		  (set! *reverb* (make-file->sample revfile))
		  (set! *reverb* revfile))
	      (apply reverb reverb-data)
	      (mus-close *reverb*)))
	(if (mus-output? *output*)
	    (mus-close *output*))

	(if statistics
	    (set! cycles (/ (- (get-internal-real-time) start) 100)))
	(set! (mus-srate) old-srate)
	output)
      (throw 'wrong-type-arg
	     (list "finish-with-sound" wsd))))


(define wsdat-play ; for cm
  (make-procedure-with-setter
   (lambda (w)
     "accessor for play field of init-with-sound struct"
     (list-ref w 9))
   (lambda (w val)
     (list-set! w 9 val))))




;;; -------- def-optkey-fun --------
;;;
;;; this is a translation of CLM's def-optkey-fun

(defmacro def-optkey-fun (decls . body)
  (let ((func-name (car decls))
	(func-args (cdr decls)))
    (if (null? func-args)
	`(define (,func-name) ,@body)
	(let ((args (map (lambda (arg)
			   (symbol->keyword (if (list? arg) (car arg) arg)))
			 func-args))
	      (key-name (string->symbol (string-append (symbol->string func-name) "-1"))))
	  (if (= (length func-args) 1)
	      `(begin
		 (define* (,key-name :key ,@func-args) ,@body)
		 (define* (,func-name :rest passed-args)
		   (if (or (null? passed-args)
			   (keyword? (car passed-args)))
		       (apply ,key-name passed-args)
		       (apply ,key-name ,(car args) passed-args))))
	      `(begin
		 (define* (,key-name :key ,@func-args) ,@body)
		 (define* (,func-name :rest passed-args)
		   (if (or (null? passed-args)
			   (keyword? (car passed-args)))
		       (apply ,key-name passed-args)
		       (let ((arglen (length passed-args)))
			 (if (or (= arglen 1) 
				 (and (> arglen 2) 
				      (keyword? (cadr passed-args))))
			     (apply ,key-name ,(car args) (car passed-args) (cdr passed-args))
			     (if (or (= arglen 2) 
				     (and (> arglen 3) 
					  (keyword? (caddr passed-args))))
				 (apply ,key-name 
					,(car args) (car passed-args) 
					,(cadr args) (cadr passed-args) 
					(cddr passed-args))
				 (let ((allargs (call-with-exit
						 (lambda (break)
						   (let ((arglist '())
							 (pa passed-args)
							 (na ',args))
						     (do ((k 0 (1+ k)))
							 ((= k arglen) arglist)
						       (if (keyword? (car pa))
							   (break (append arglist pa))
							   (begin
							     (set! arglist (append arglist (list (car na) (car pa))))
							     (set! pa (cdr pa))
							     (set! na (cdr na))))))))))
				   (apply ,key-name allargs)))))))))))))

(defmacro def-optkey-instrument (args . body)
  (let* ((name (car args))
	 (targs (cdr args))
	 (utargs (let ((arg-names '()))
		   (for-each
		    (lambda (a)
		      (if (not (keyword? a))
			  (if (symbol? a)
			      (set! arg-names (cons a arg-names))
			      (set! arg-names (cons (car a) arg-names)))))
		    targs)
		   (reverse arg-names))))
  `(begin 
     (def-optkey-fun (,name ,@targs)
       (if *clm-notehook*
	   (*clm-notehook* (symbol->string ',name) ,@utargs))
       ((lambda () ; for inner defines, if any
	  ,@body)))
     ,@(if *definstrument-hook*
           (list (*definstrument-hook* name targs))
           (list)))))


(define ->frequency
  (let ((main-pitch (/ 440.0 (expt 2.0 (/ 57 12)))) ; a4 = 440Hz is pitch 57 in our numbering
	(last-octave 0)                             ; octave number can be omitted
	(ratios (vector 1.0 256/243 9/8 32/27 81/64 4/3 1024/729 3/2 128/81 27/16 16/9 243/128 2.0)))
    (lambda* (pitch :optional pythagorean)          ; pitch can be pitch name or actual frequency
      "(->frequency pitch :optional pythagorean) returns the frequency (Hz) of the 'pitch', a CLM/CM style note name as a \
symbol: 'e4 for example.  If 'pythagorean', the frequency calculation uses small-integer ratios, rather than equal-tempered tuning."
      (if (symbol? pitch)
	  (let* ((name (string-downcase (symbol->string pitch)))
		 (base-char (string-ref name 0))
		 (sign-char (and (> (string-length name) 1)
				 (not (char-numeric? (string-ref name 1)))
				 (not (char=? (string-ref name 1) #\n))
				 (string-ref name 1)))
		 (octave-char (if (and (> (string-length name) 1)
				       (char-numeric? (string-ref name 1))) 
				  (string-ref name 1)
				  (if (and (> (string-length name) 2) 
					   (char-numeric? (string-ref name 2)))
				      (string-ref name 2)
				      #f)))
		 (base (modulo (+ 5 (- (char->integer base-char) (char->integer #\a))) 7)) ; c-based (diatonic) octaves
		 (sign (if (not sign-char) 0 (if (char=? sign-char #\f) -1 1)))
		 (octave (if octave-char (- (char->integer octave-char) (char->integer #\0)) last-octave))
		 (base-pitch (+ sign (case base ((0) 0) ((1) 2) ((2) 4) ((3) 5) ((4) 7) ((5) 9) ((6) 11))))
		 (et-pitch (+ base-pitch (* 12 octave))))
	    (set! last-octave octave)
	    (if pythagorean
		(* main-pitch (expt 2 octave) (vector-ref ratios base-pitch))
		(* main-pitch (expt 2.0 (/ et-pitch 12)))))
	  pitch))))


(define (->sample beg)
  "(->sample time-in-seconds) -> time-in-samples"
  (inexact->exact (round (* (if (not (null? (sounds))) (srate) (mus-srate)) beg))))



;;; -------- def-clm-struct --------

(if (not (defined? 'add-clm-type)) (define (add-clm-type . args) #f)) ; these are in run
(if (not (defined? 'add-clm-field)) (define (add-clm-field . args) #f))
(if (not (defined? 'snd-error)) (define snd-error display))

;;;  :(def-clm-struct (osc :make-wrapper (lambda (gen) (set! (osc-freq gen) (hz->radians (osc-freq gen))) gen)) freq phase)
;;;  #<unspecified>
;;;  :(define hi (make-osc 440.0 0.0))
;;;  #<unspecified>
;;;  :hi
;;;  (osc 0.125378749798983 0.0)

;;; besides setting up the list accessors, the make function, and the type predicate, this
;;;   calls add-clm-type to make sure run knows about the struct and, on each field,
;;;   add-clm-field to tell run the type of each list element (only actually needed if
;;;   there are different types in use)
;;;
;;; see defgenerator in generators.scm for an extension that adds various methods such as mus-describe

(defmacro def-clm-struct (struct-name . fields)
  (let* ((name (if (list? struct-name) (car struct-name) struct-name))
	 (wrapper (or (and (list? struct-name)
			   (or (and (> (length struct-name) 2)
				    (equal? (list-ref struct-name 1) :make-wrapper)
				    (list-ref struct-name 2))
			       (and (= (length struct-name) 5)
				    (equal? (list-ref struct-name 3) :make-wrapper)
				    (list-ref struct-name 4))))
		      (lambda (gen) gen)))
	 (methods (and (list? struct-name)
		       (or (and (> (length struct-name) 2)
				(equal? (list-ref struct-name 1) :methods)
				(list-ref struct-name 2))
			   (and (= (length struct-name) 5)
				(equal? (list-ref struct-name 3) :methods)
				(list-ref struct-name 4)))))
	 (sname (if (string? name) name (symbol->string name)))
	 (field-names (map (lambda (n)
			     (symbol->string (if (list? n) (car n) n)))
			   fields))
	 (field-types (map (lambda (n)
			     (if (and (list? n) (cadr n) (eq? (cadr n) :type)) 
				 (snd-error (format #f ":type indication for def-clm-struct (~A) field (~A) should be after the default value" name n)))
			     (if (and (list? n)
				      (= (length n) 4)
				      (eq? (list-ref n 2) :type))
				 (list-ref n 3)
				 (if (and (list? n)
					  (= (length n) 2))
				     (if (number? (cadr n))
					 (if (exact? (cadr n))
					     'int
					     'float)
					 (if (string? (cadr n))
					     'string
					     (if (char? (cadr n))
						 'char
						 (if (or (equal? (cadr n) #t)
							 (equal? (cadr n) #f))
						     'boolean
						     'float))))
				     'float)))
			   fields)))
    `(begin
       (define ,(string->symbol (string-append sname "?"))
	 (lambda (obj)
	   "clm struct type check"
	   (and (list? obj)
		(eq? (car obj) ',(string->symbol sname)))))
       (define ,(string->symbol (string-append sname "-methods"))
	 (lambda ()
	   "clm struct local method list accessor"
	   ,methods))
       (def-optkey-fun (,(string->symbol (string-append "make-" sname))
		        ,@(map (lambda (n)
				(if (and (list? n)
					 (>= (length n) 2))
				    (list (car n) (cadr n))
				    (list n 0.0)))
			      fields))
	 (,wrapper (if (list? ,methods)
		       (list ',(string->symbol sname)
			     ,@(map string->symbol field-names)
			     ,methods)
		       (list ',(string->symbol sname)
			     ,@(map string->symbol field-names)))))
       ,@(map (let ((ctr 1))
		(lambda (n type)
		  (let ((val `(define ,(string->symbol (string-append sname "-" n))
				(make-procedure-with-setter
				 (lambda (arg)
				   "clm struct field accessor"
				   (list-ref arg ,ctr))
				 (lambda (arg val)
				   (list-set! arg ,ctr val))))))
		    (add-clm-field sname (string-append sname "-" n) ctr type)
		    (set! ctr (1+ ctr))
		    val)))
	      field-names field-types))))


(if (not (defined? 'ws-interrupt?)) (define (ws-interrupt? . args) #f))