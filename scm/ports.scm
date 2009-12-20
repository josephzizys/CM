;;; **********************************************************************
;;; Copyright (C) 2008, 2009 Rick Taube.
;;; This program is free software; you can redistribute it and/or modify
;;; it under the terms of the Lisp Lesser Gnu Public License. The text of
;;; this agreement is available at http://www.cliki.net/LLGPL            
;;; **********************************************************************

(define (ports )
  (let ((str (ffi_port_info)))
    ;; return port info as lisp list
    (read-from-string str)))

(define (play file)
  (if (string? file)
      (ffi_play file))
  (void))

;; see ScoreTypes in Enumerations.h

(define *score-type-midi* 1)
(define *score-type-sndlib* 2)
(define *score-type-csound* 3)
(define *score-type-fomus* 4)

(define (open-file str . args)
  ;; open a file or signal an error
  (let ((type (ffi_pathname_type str)))
    (let ((mode 0))
      ;; don't allow files to be opened if the scheuler is
      ;; currently busy. this stops sprouting files if other files
      ;; are in progress or switching to score mode while the
      ;; scheduler is busy running real time processes
      (if (ffi_sched_busy_p)
	  (error "Scheduler busy, cannot open ~S" str))
      (if (not (ffi_pathname_writable_p str))
	  (error "file ~S is not writable" str))
      (cond ((string=? type "mid")
	     (apply mp:open-output-file str args)
	     (set! mode *score-type-midi*)
	     )
	    ((member type '("aiff" "snd" "wav"))
	     (apply snd:open-output-file str args)
	     (set! mode *score-type-sndlib*)
	     )
	    ((member type '("sco"))
	     (apply cs:open-output-file str args)
	     (set! mode *score-type-csound*)
	     )
	    ;;(member type '("ly" "fms" "xml"))
	    ((or (not (= (ffi_fms_isfiletype type) 0))
		 (and (string=? type "") (string=? str "fomus")))
	     (apply fms:open-score str args)
	     (set! mode *score-type-fomus*)
	     )
	    (else
	     (error "don't know how to open ~S" str)))
      ;; this function is being called under sprout: put the
      ;; schedulder in score mode
      (ffi_sched_set_score_mode mode)
      str)))

;;
;; Midi ports
;;

;; see MidiTypes in Enumerations.h

(define mm:off    #x8)
(define mm:on     #x9)
(define mm:touch  #xA)
(define mm:ctrl   #xB)
(define mm:prog   #xC)
(define mm:press  #xD)
(define mm:bend   #xE)

(define (mp:open . args)
  (with-optkeys (args (out #f) (in #f))
    (cond ((and out in)
	   (list (mp:open-output out)
		 (mp:open-input in)))
	  (out
	   (mp:open-output out))
	  (in
	   (mp:open-input in)))))

(define (mp:open-output . dev)
  (if (and (pair? dev)
	   (null? (cdr dev))
	   (integer? (car dev))
	   (>= (car dev) 0)
	   (ffi_mp_open_output (car dev)))
      (car dev)
      (error "~S is not a midi device number" dev)))

(define (mp:open-input . dev)
  (if (and (pair? dev)
	   (null? (cdr dev))
	   (integer? (car dev))
	   (>= (car dev) 0)
	   (ffi_mp_open_input (car dev)))
      (car dev)
      (error "~S is not a midi device number" dev)))

(define (mp:close-output . dev)
  (if (and (pair? dev)
	   (null? (cdr dev))
	   (integer? (car dev)) 
	   (>= (car dev) 0))
      (ffi_mp_close_output (car dev))
      (error "~S is not a midi device number" dev)))

(define (mp:close-input . dev)
  (if (and (pair? dev)
	   (null? (cdr dev))
	   (integer? (car dev)) 
	   (>= (car dev) 0))
      (ffi_mp_close_input (car dev))
      (error "~S is not a midi device number" dev)))

(define (mp:open-output-file path . args)
  (ffi_mp_set_output_file path)
  )

(define (mp:midi . args)
  (with-optkeys (args (time 0) (dur .5) (key 60) (amp .5) (chan 0))
    (ffi_mp_send_note time dur key amp chan)))

(define (mp:off . args)
  (with-optkeys (args (time 0) (key 60) (chan 0))
    (ffi_mp_send_data mm:off time chan key 0)))

(define (mp:on . args)
  (with-optkeys (args (time 0) (key 60) (vel 64) (chan 0))
    (ffi_mp_send_data mm:on time chan key vel)))

(define (mp:touch . args)
  (with-optkeys (args (time 0) (key 0) (val 0) (chan 0))
    (ffi_mp_send_data mm:touch time chan key val)))

(define (mp:ctrl . args)
  (with-optkeys (args (time 0) (num 0) (val 0) (chan 0))
    (ffi_mp_send_data mm:ctrl time chan num val)))

(define (mp:prog . args)
  (with-optkeys (args (time 0) (val 0) (chan 0))
    (ffi_mp_send_data mm:prog time chan val 0)))

(define (mp:press . args)
  (with-optkeys (args (time 0) (val 0) (chan 0))
    (ffi_mp_send_data mm:press time chan val 0)))

(define (mp:bend . args)
  (with-optkeys (args (time 0) (val 8192) (chan 0))
    (ffi_mp_send_data mm:bend time chan val 0)))

(define (mp:tuning . args)
  (let ((arg (if (null? args) 1 (car args))))
    (if (and (integer? arg)
	     (< 0 arg 17))
	(ffi_mp_set_tuning arg)
	(error "~S is not a tuning division 1 to 16" arg))))

(define (mp:instruments . args)
  (do ((tail args (cdr tail))
       (argn 0 (+ argn 1))
       (prog #f)
       (a -1) (b -1) (c -1) (d -1) (e -1) (f -1) (g -1) (h -1)
       (i -1) (j -1) (k -1) (l -1) (m -1) (n -1) (o -1) (p -1))
      ((null? tail)
       (ffi_mp_set_instruments a b c d e f g h i j k l m n o p))
    (if (not (car tail)) (set! prog -1)
	(if (and (integer? (car tail)) (<= 0 (car tail) 127))
	    (set! prog (car tail))
	    (error "~S is not a program change 0 to 127 or #f" (car tail))))
    (cond ((= argn 0) (set! a prog))
	  ((= argn 1) (set! b prog))
	  ((= argn 2) (set! c prog))
	  ((= argn 3) (set! d prog))
	  ((= argn 4) (set! e prog))
	  ((= argn 5) (set! f prog))
	  ((= argn 6) (set! g prog))
	  ((= argn 7) (set! h prog))
	  ((= argn 8) (set! i prog))
	  ((= argn 9) (set! j prog))
	  ((= argn 10) (set! k prog))
	  ((= argn 11) (set! l prog))
	  ((= argn 12) (set! m prog))
	  ((= argn 13) (set! n prog))
	  ((= argn 14) (set! o prog))
	  ((= argn 15) (set! p prog))
	  (else
	   (error "more than 16 program changes in ~S" tail))))
  )

(define (mp:playseq)
  (ffi_mp_play_seq))

(define (mp:saveseq)
  (ffi_mp_save_seq))

(define (mp:copyseq)
  (ffi_mp_copy_seq))

(define (mp:plotseq)
  (ffi_mp_plot_seq))

(define (mp:clearseq)
  (ffi_mp_clear_seq))

(define (mp:recordseq . args)
  (let ((rec (if (null? args) #f (car args))))
    (ffi_mp_set_record_seq rec)))

;; input port

(define (mp:inhook hook)
  (if (procedure? hook)
      ( ffi_mp_set_midi_input_hook hook )
      ( ffi_mp_clear_midi_input_hook ))
  hook)

(define (mp:hook op hook)
  ( ffi_mp_hook op hook )
  hook)

(define (mp:inchans . args)
  (let ((val 0))
    (cond ((null? args)
	   (error "missing channel 0 to 15 in ~S" args))
	  ((and (null? (cdr args)) (eq? (car args) #f))
	   (set! val 0))
	  ((and (null? (cdr args)) (eq? (car args) #t))
	   (set! val #xFFFF))
	  (else
	   (do ((a args (cdr a)))
	       ((null? a)
		#f)
	     (if (<= 0 (car a) 15)
		 (set! val (logior val (ash 1 (car a))))
		 (error "~S is not a channel 0 to 15" (car a))))))
    (ffi_mp_set_channel_mask val)))

(define (mp:inops . args)
  (let ((val 0))
    (cond ((null? args)
	   (error "missing message type (mm:off to mm:bend) in ~S" args))
	  ((and (null? (cdr args)) (eq? (car args) #f))
	   (set! val 0))
	  ((and (null? (cdr args)) (eq? (car args) #t))
	   (set! val #x7F))
	  (else
	   (do ((a args (cdr a)))
	       ((null? a)
		#f)
	     (if (<= mm:off (car a) mm:bend)
		 (set! val (logior val (ash 1 (- (car a) mm:off))))
		 (error "~S is not a message type mm:off to mm:bend"
			(car a))))))
    (ffi_mp_set_message_mask val)
    ))


;;
;; sndlib's open/close in lisp for now.
;; 

(define *sndfileinfo* #f)

(define (default-header-type type)
  (cond ((string=? type "aiff")
	 (list #:header-type mus-aifc))
	((string=? type "wav")
	 (list #:header-type mus-riff))
	((string=? type "snd")
	 (list #:header-type mus-next))
	(else (list))))

(define (default-data-format type)
  (cond	((string=? type "aiff")
	 (list #:data-format mus-bshort))
	((string=? type "wav")
	 (list #:data-format mus-lshort))
	((string=? type "snd")
	 (list #:data-format mus-bshort))
	(else (list))))

(define (snd:open-output-file file . args)
  (set! file (full-pathname file))
  (set! *sndfileinfo* #f)
  ;; add header and format types for file type
  (let ((type (pathname-type file)))
    (if (not (list-prop args #:data-format))
	(set! args (append args (default-data-format type))))
    (if (not (list-prop args #:header-type))
	(set! args (append args (default-header-type type))))
    )

  (let ((wsdat (apply init-with-sound #:output file
		      args)))
    (set! *sndfileinfo*
	  (append wsdat (list
			 (list-prop args #:channels *clm-channels*))))
    *sndfileinfo*))

(define (snd:close-output-file )
  (if *sndfileinfo*
      (let ((wsdat *sndfileinfo*))
	(set! *sndfileinfo* #f)
	(finish-with-sound wsdat)
	(format #t "~%Soundfile: ~S~%Channels: ~S~%Srate: ~S~%"
		(list-ref wsdat 1)
		(car (tail wsdat)) ; added chans to end of wsdat
		(list-ref wsdat 4)
		)
	(if (and (wsdat-play wsdat) (procedure? *clm-player*))
	    (*clm-player* (list-ref wsdat 1)))
	))
  (void))

;;;
;;; Csound is scorefile only
;;;

(define (cs:open-output-file path . args)
  (let ((opts (string-append "\"" path "\"")))
    (unless (even? (length args))
      (error "uneven options list ~S" args))
    (do ((tail args (cddr tail))
	 (argn #f))
	((null? tail) 
	 (ffi_cs_init_score opts)
	 )
      (set! argn (cadr tail))
      (case (car tail)
	((#:play )
	 (set! opts (string-append opts " :play " 
				   (if (cadr tail) "#t" "#f"))))
	((#:write )
	 (set! opts (string-append opts " :write "
				   (if (cadr tail) "#t" "#f"))))
	((#:options )
	 (if (not (string? argn))
	     (error "options ~S is not a string" argn))
	 (set! opts (string-append opts " :options \""
				   (cadr tail) "\"")))
	((#:header)
	 (if (not (string? argn))
	     (error "header ~S is not a string" argn))
	 (set! opts (string-append opts " :header \""
				   (cadr tail) "\"")))
	((#:orchestra)
	 (if (not (string? argn))
	     (error "orchestra ~S is not a string" argn))
	 (set! opts (string-append opts " :orchestra \""
				   (cadr tail) "\"")))
	(else
	 (error "unknown Csound option ~S" (car tail)))))))

; (cs:open-output-file "test.sco" #:write #t #:play #f)

;; see Csound.h

(define cs:i_statement 1)
(define cs:e_statement 2)

(define (cs:send type args)
  ;; args can 1 or more values, or one list.
  (let ((inst #f)
	(time #f)
	(data ""))
    (cond ((null? args)
	   (error "missing pfield data in ~S" args))
	  ((and (null? (cdr args))
		(pair? (car args)))
	   (set! args (car args))))
    ;; parse out i value
    (cond ((integer? (car args))
	   (set! inst (car args))
	   (set! args (cdr args)))
	  (else
	   (error "pfield 1 value ~S not an integer" (car args))))
    ;; parse out time value
    (cond ((null? args)
	   (error "missing pfield 2 (time) in ~S" args))
	  ((number? (car args))
	   (set! time (car args))
	   (set! args (cdr args)))
	  (else
	   (error "pfield 2 value ~S not a number" (car args))))
    ;; convert remaining to string
    (do ((tail args (cdr tail))
	 (delm "" " "))
	((null? tail)
	 (ffi_cs_send_score (if (eqv? type 'i)
				cs:i_statement
				cs:f_statement) 
			    inst time data))
      (cond ((number? (car tail))
	     (set! data (string-append data delm
				       (number->string (car tail)))))
	    ((string? (car tail))
	     (set! data (string-append data delm
				       (car tail))))
	    ((symbol? (car tail))
	     (set! data (string-append data delm
				       (symbol->string (car tail)))))
	    (else
	     (error "pfield value ~A not number, string or symbol"
		    (car tail)))))))

(define (cs:i . args)
  (cs:send 'i args ))

(define (cs:f . args)
  (cs:send 'f args))

(define (cs:ev args)
  (cond ((pair? args)
	 (let ((type (car args)))
	   (if (or (eqv? type 'i)
		   (eqv? type 'f))
	       (cs:send type args)
	       (error "~S is not a Csound statement type" type))))
	(else
	 (error "pfield data ~S not a list" args))))

; (cs:send 1 '(99 0 1 440 .1))
; (cs:i 1 0 1 2 3 4)
; (cs:i 1 10)
; (cs:i 1 22 1 55)

;;;
;;; send macro
;;;

(define-expansion (send place . args)
  (expand-send place args))

(define *messages* (make-equal-hash-table))

(define-macro (define-send-message msg pars)
  ;; (<parser> . paramdecls)
  (let ((var (gensym "temp")))
    `(let ((,var ,pars))
       (hash-set! *messages* ,msg
		  (cons (make-message-parser ,var) ,var)))))

(define (expand-send place args . errcont)
  ;; if called from sal then errcont is the error continuation to call
  (if (not (null? errcont))
      (set! errcont (car errcont))
      (set! errcont error))
  (cond ((string? place)
	 (let ((data (hash-ref *messages* place)))
	   ;; no message registered, expand funcall and hope for the best
	   (if (not data)
	       (cons (string->symbol place) args)
	       ;; call the parser. if it returns true then args are ok
	       ;; and qw exapand the macro otherwise it returns the
	       ;; string to print
	       (let ((res ( (car data) args)))
		 (if (string? res)
		     (errcont res)
		     (cons (string->symbol place) args))))))
	((symbol? place)
	 (cons place args))
	(else
	 (error "~S is not a send message" place))
	))

; (define foo (make-message-parser '(a b c )))
; (foo '(1 2 3))
; (foo '(1 2))
; (foo '(1 2 3 4))
; (define foo (make-message-parser '(#:optkey a b c d )))
; (foo '( ))
; (foo '(1 2 3 4))
; (foo '(6 #:b 33))
; (foo '(6 #:x 33))
; (foo '(6 #:d 33 99))

(define (make-message-parser template)
  ;; return a parser that is passed the args to (send ...) if it
  ;; returns #t then its ok to expand the send into a function call
  ;; otherwise it returns the error string to signal
  (let ((reqs '())
	(opts '())
	(keys '())
	(optkeys '())
	(&rest #f)
	)
  (do ((tail template (cdr tail))
       (mode #f))
      ((null? tail) #f)
    (cond ((keyword? (car tail))
	   (if (member (car tail) '(#:opt #:key #:optkey #:rest))
	       (set! mode (car tail))
	       (error "~S is not a valid message argument" mode)))
	  ((eqv? mode #:key)
	   (let ((x (if (pair? (car tail))
			(caar tail) (car tail))))
	     (set! keys
		   (cons (string->keyword (symbol->string x)) keys))))
	  ((eqv? mode #:optkey)
	   (set! optkeys
		 (cons (string->keyword (symbol->string (car tail)))
		       optkeys)))
	  ((eqv? mode #:optional)
	   (set! opts (cons (car tail) opts)))
	  ((eqv? mode #:rest)
	   (set! &rest (car tail)))
	  ((not mode)
	   ;;(format #t "req is ~S~%" (car tail))
	   (set! reqs (cons (car tail) reqs)))
	  (else
	   (error "in make-message-parser, ~S shouldn't happen!"
		  mode))
	  ))
  (set! reqs (reverse reqs))
  (set! opts (reverse opts))
  (set! keys (reverse keys))
  (set! optkeys (reverse optkeys))
  ;; return the parser to register with the message
  (lambda (args)
    (call-with-current-continuation
     (lambda (return)
       (let ((err #f)
	     (sav args))
	 (if &rest (return #t))
	 ;; check required
	 (do ((tail reqs (cdr tail)))
	     ((null? tail)
	      #f)
	   (if (null? args)
	       (return
		(format #f "send missing required arguments in ~S"
			sav))
	       (if (and (keyword? (car args))
			(or (member (car args) keys)
			    (member (car args) optkeys)))
		   (return 
		    (format #f "send missing required arguments in ~S"
			    sav)
		    )))
	   (set! args (cdr args)))
	 ;; check optionals
	 (if (and (not (null? args))
		  (not (null? opts)))
	     (do ()
		 ((or (null? args)
		      (keyword? (car args)))
		  #f)
	       (set! args (cdr args))))
 	 ;; check optional optkeys
	 (if (and (not (null? args))
		  (not (null? optkeys)))
	     (do ()
		 ((or (null? args)
		      (keyword? (car args)))
		  #f)
	       (set! args (cdr args))))
	 ;; check keywords
	 (if (or (not (null? keys))
		 (not (null? optkeys)))
	     (do ((check (if (null? keys) optkeys keys)))
		 ((null? args)
		  #f)
	       (cond ((keyword? (car args))
		      (if (not (member (car args) check))
			  (return
			   (format #f
				   "~A not a valid keyword argument in ~S"
				   (car args) sav)))
		      (set! args (cdr args))
		      (if (null? args)
			  (return
			   (format #f "Uneven keyword arguments in ~S"
				   sav)))
		      (set! args (cdr args)))
		     (else
		      (return (format #f "~A not a keyword argument"
				      (car args)
				      ))))))
	 (if (not (null? args))
	     (return (format #f "too many arguments in ~S" 
			     sav
			     ))
	     #t)))))))

(define-send-message "mp:open" '(#:optkey out in))
(define-send-message "mp:midi" '(#:optkey time dur key amp chan))
(define-send-message "mp:off" '(#:optkey time key chan))
(define-send-message "mp:on" '(#:optkey time key vel chan))
(define-send-message "mp:touch" '(#:optkey time key val chan))
(define-send-message "mp:ctrl" '(#:optkey time num val chan))
(define-send-message "mp:prog" '(#:optkey time val chan))
(define-send-message "mp:press" '(#:optkey time val chan))
(define-send-message "mp:bend" '(#:optkey time val chan))
(define-send-message "mp:mm"  '(#:optkey mm ))
(define-send-message "mp:inhook" '(#:optkey func))
(define-send-message "mp:tuning" '(#:optkey div ))
(define-send-message "mp:instruments" '(#:rest args ))
(define-send-message "mp:recordseq" '(#:optkey rec ))
(define-send-message "mp:playseq" '())
(define-send-message "mp:saveseq" '())
(define-send-message "mp:copyseq" '())
(define-send-message "mp:clearseq" '())
(define-send-message "mp:inchans" '(#:rest args))
(define-send-message "mp:inops" '(#:rest args))
(define-send-message "cs:i" '(#:rest args))
(define-send-message "cs:f" '(#:rest args))
(define-send-message "cs:data" '(arg))
; this needs to be here or eval-from-string compains about the last
; macro
#f



