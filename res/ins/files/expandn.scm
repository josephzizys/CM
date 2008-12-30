;;; multi-channel sound file expansion with srate and reverb.
;;; michael klingbeil (michael@klingbeil.com)
;;;
;;; clm-4 and scheme 12-May-08 bil

(definstrument (expandn time duration filename amplitude
			:key (expand 1.0)
			(matrix #f)
			(ramp 0.4)
			(seglen 0.15)
			(srate 1.0)
			(hop .05)
			(amp-env '(0 0 50 1 100 0))
			(input-start 0.0)
			(grain-amp 0.8)
			(reverb #f))

  (let ((fnam (mus-expand-filename filename)))
    (if (not (file-exists? fnam))
	(throw 'no-such-file (list 'expandn filename))

	(let* ((beg (seconds->samples time))
	       (end (+ beg (seconds->samples duration)))
	       (in-chans (mus-sound-chans fnam))
	       (out-chans (mus-channels *output*))
	       (inframe (make-frame in-chans))
	       (outframe (make-frame out-chans))
	       (mx (if matrix
		       (make-mixer (max in-chans out-chans))
		       (make-scalar-mixer (max in-chans out-chans) 1.0)))
	       (rev-chans (if *reverb* (mus-channels *reverb*) 0))
	       (rev-mx (if (and *reverb* reverb (> reverb 0.0))
			   (let ((rmx (make-mixer (max out-chans rev-chans))))
			     (do ((i 0 (+ i 1)))
				 ((= i (max out-chans rev-chans)))
			       (mixer-set! rmx (modulo i out-chans) (modulo i rev-chans) reverb))
			     rmx)
			   #f))
	       (revframe (if rev-mx (make-frame (max out-chans rev-chans)) #f))
	       (update-env (or (list? expand)
			       (list? seglen)
			       (list? ramp)
			       (list? hop)))
	       (update-rate 100)
	       (expenv (make-env (if (list? expand) expand (list 0 expand 1 expand))
				 :duration (/ duration update-rate)))
	       (lenenv (make-env (if (list? seglen) seglen (list 0 seglen 1 seglen))
				 :duration (/ duration update-rate)))
	       (max-seg-len (if (list? seglen) (max-envelope seglen) seglen))
	       (segment-scaler (if (> max-seg-len .15)
				   (/ (* grain-amp .15) max-seg-len)
				   grain-amp))
	       (srenv (if (list? srate) (make-env srate :duration duration) #f))
	       (resa (exact->inexact (if (list? srate) (cadr srate) srate)))
	       (rampdata (if (list? ramp) ramp (list 0 ramp 1 ramp)))
	       (rampenv (make-env rampdata :duration (/ duration update-rate)))
	       (minramp-bug (<= (min-envelope rampdata) 0.0))
	       (maxramp-bug (>= (max-envelope rampdata) 0.5))
	       (hopenv (make-env (if (list? hop) hop (list 0 hop 1 hop))
				 :duration (/ duration update-rate)))
	       (ampenv (make-env amp-env :duration duration :scaler amplitude))
	       (ex-array (make-vector in-chans #f))
	       (start (inexact->exact (floor (* input-start (mus-sound-srate fnam)))))
	       (max-out-hop (if (list? hop) (max-envelope hop) hop))
	       (min-exp-amt (if (list? expand) (min-envelope expand) expand))
	       (max-in-hop (/ max-out-hop min-exp-amt))
	       (max-len (inexact->exact (ceiling (* (mus-srate)
						    (+ (max max-out-hop max-in-hop)
						       max-seg-len)))))
	       (ex-samp -1.0)
	       ;; these vars used for in-line resampling (rather than use resample generator)
	       (next-samp 0.0)
	       (samples-0 (make-vct in-chans))
	       (samples-1 (make-vct in-chans)))
	  
	  (if (or minramp-bug maxramp-bug)
	      (throw 'out-of-range (list expand 
					 "ramp argument to expsnd must always be "
					 (if (and minramp-bug maxramp-bug) "between 0.0 and 0.5"
					     (if minramp-bug "greater than 0.0"
						 "less than 0.5")))))

	  ;; setup granulate generators
	  (do ((i 0 (+ i 1)))
	      ((= i in-chans))
	    (vector-set! ex-array i (make-granulate :input (make-readin fnam :start start :channel i)
						    :expansion (if (list? expand) (cadr expand) expand)
						    :max-size max-len
						    :ramp (if (list? ramp) (cadr ramp) ramp)
						    :hop (if (list? hop) (cadr hop) hop)
						    :length (if (list? seglen) (cadr seglen) seglen)
						    :scaler segment-scaler)))
	  (if matrix
	      (begin
		(do ((inp 0 (+ 1 inp)))
		    ((= inp in-chans))
		  (let ((inlist (list-ref matrix inp)))
		    (do ((outp 0 (+ 1 outp)))
			((= outp out-chans))
		      (let ((outn (list-ref inlist outp)))
			(mixer-set! mx inp outp outn)))))))

	  (run
	   (lambda ()
	     (do ((i beg (+ i 1)))
		 ((= i end))
	       (declare (ex-array clm-vector))
	       (let ((vol (env ampenv)))
		 (if srenv (set! resa (env srenv)))

		 ;; should be (mod (- i beg) update-rate) but i is ok
		 ;; since we set the initial values when we constructed
		 ;; the unit generators
		 (if (and update-env (= 0 (modulo (- i beg) update-rate)))
		     (let* ((expa (env expenv)) ;current expansion amount
			    (segl (env lenenv)) ;current segment length
			    (rmpl (env rampenv)) ;current ramp length (0 to .5)
			    (hp (env hopenv)) ;current hop size
			    ;; now we set the granulate generator internal
			    ;; state to reflect all these envelopes
			    (sl (inexact->exact (floor (* segl (mus-srate)))))
			    (rl (inexact->exact (floor (* rmpl sl)))))
		       ;; declare types
		       (do ((ix 0 (+ 1 ix)))
			   ((= ix in-chans))
			 (let ((gen (vector-ref ex-array ix)))
			   (set! (mus-length gen) sl)
			   (set! (mus-ramp gen) rl)
			   (set! (mus-frequency gen) hp)
			   (set! (mus-increment gen) expa)))))

		 (if (negative? ex-samp)
		     (begin
		       (do ((ix 0 (+ 1 ix)))
			   ((= ix in-chans))
			 (let ((gen (vector-ref ex-array ix)))
			   (vct-set! samples-0 ix (* vol (granulate gen)))
			   (vct-set! samples-1 ix (* vol (granulate gen)))))
		       (set! ex-samp (+ 1 ex-samp))
		       (set! next-samp ex-samp))
		     (begin
		       (set! next-samp (+ next-samp resa))
		       (if (> next-samp (+ 1 ex-samp))
			   (let ((samps (inexact->exact (floor (- next-samp ex-samp)))))
			     (do ((k 0 (+ 1 k)))
				 ((= k samps))
			       (do ((ix 0 (+ 1 ix)))
				   ((= ix in-chans))
				 (let ((gen (vector-ref ex-array ix)))
				   (vct-set! samples-0 ix (vct-ref samples-1 ix))
				   (vct-set! samples-1 ix (* vol (granulate gen)))))
			       (set! ex-samp (+ 1 ex-samp)))))))

		 (if (= next-samp ex-samp)
		     ;; output actual samples
		     (do ((ix 0 (+ 1 ix)))
			 ((= ix in-chans))
		       (let ((samp (vct-ref samples-0 ix)))
			 (frame-set! inframe ix samp)))
		     ;; output interpolated samples
		     (do ((ix 0 (+ 1 ix)))
			 ((= ix in-chans))
		       (let* ((v0 (vct-ref samples-0 ix))
			      (v1 (vct-ref samples-1 ix))
			      (samp (+ v0 (* (- next-samp ex-samp)
					     (- v1 v0)))))
			 (frame-set! inframe ix samp))))

		 ;; output mixed result
		 (frame->file *output* i (frame->frame inframe mx outframe))
		 ;; if reverb is turned on, output to the reverb streams
		 (if rev-mx
		     (frame->file *reverb* i (frame->frame outframe rev-mx revframe)))))))))))


