(definstrument (fullmix in-file :optional beg outdur inbeg matrix srate reverb-amount)
  ;; "matrix" can be a simple amplitude or a list of lists
  ;;     each inner list represents one input channel's amps into one output channel
  ;;     each element of the list can be a number, a list (turned into an env) or an env
  (let* ((st (seconds->samples (or beg 0.0)))
	 (dur (or outdur
		  (/ (- (mus-sound-duration in-file) (or inbeg 0.0))
		     (or (and srate (abs srate)) 1.0))))
	 (samps (seconds->samples dur))
	 (nd (+ st samps))
	 (in-chans (mus-sound-chans in-file))
	 (inloc (inexact->exact (floor (* (or inbeg 0.0) (mus-sound-srate in-file)))))
	 (file (if (not srate) 
		   (make-file->frame in-file)
		   (let ((vect (make-vector in-chans)))
		     (do ((i 0 (+ i 1)))
			 ((= i in-chans))
		       (vector-set! vect i (make-readin in-file i inloc)))
		     vect)))
	 (out-chans (mus-channels *output*))
	 (mx (if matrix
		 (make-mixer (max in-chans out-chans))
		 (make-scalar-mixer (max in-chans out-chans) 1.0)))
	 (rev-mx (if (and *reverb* reverb-amount (> reverb-amount 0.0))
		     (let ((rmx (make-mixer in-chans)))
		       (do ((i 0 (+ i 1)))
			   ((= i in-chans))
			 (mixer-set! rmx i 0 reverb-amount)) ; 0->assume 1 chan reverb stream, I think
		       rmx)
		     #f))
	 (revframe (if rev-mx (make-frame 1) #f))
	 (envs #f))
    (if matrix
	(begin
	  (if (list? matrix) ; matrix is list of scalers, envelopes (lists), or env gens
	      (do ((inp 0 (+ 1 inp)))
		  ((= inp in-chans))
		(let ((inlist (list-ref matrix inp)))
		  (do ((outp 0 (+ 1 outp)))
		      ((= outp out-chans))
		    (let ((outn (list-ref inlist outp)))
		      (if outn
			  (if (number? outn)
			      (mixer-set! mx inp outp outn)
			      (if (or (env? outn)
				      (list? outn))
				  (begin
				    (if (not envs)
					(begin
					  (set! envs (make-vector in-chans))
					  (do ((i 0 (+ i 1)))
					      ((= i in-chans))
					    (vector-set! envs i (make-vector out-chans #f)))))
				    (if (env? outn)
					(vector-set! (vector-ref envs inp) outp outn)
					(vector-set! (vector-ref envs inp) outp (make-env outn :duration dur))))
				  (snd-warning (format #f "unknown element in matrix: ~A" outn)))))))))
	      (do ((inp 0 (+ 1 inp))) ; matrix is a number in this case (a global scaler)
		  ((= inp in-chans))
		(if (< inp out-chans)
		    (mixer-set! mx inp inp matrix))))))
    (if (not srate)
	;; no src
	(begin
	  (mus-mix *output* file st samps inloc mx envs)
	  (if rev-mx (mus-mix *reverb* revframe st samps inloc rev-mx #f)))
	;; with src
	(let* ((inframe (make-frame in-chans))
	       (outframe (make-frame out-chans))
	       (srcs (make-vector in-chans #f)))
	  (do ((inp 0 (+ 1 inp)))
	      ((= inp in-chans))
	    (vector-set! srcs inp (make-src :srate srate)))
	  ;; can't use run here yet because 2-dim vect and #f elements
	  (if envs
	      (run 
	       (lambda ()
		 (do ((i st (+ i 1)))
		     ((= i nd))
		   (do ((inp 0 (+ 1 inp)))
		       ((= inp in-chans))
		     (do ((outp 0 (+ 1 outp)))
			 ((= outp out-chans))
		       (if (and (vector-ref envs inp)
				(env? (vector-ref (vector-ref envs inp) outp)))
			   (mixer-set! mx inp outp (env (vector-ref (vector-ref envs inp) outp)))))))
		 (do ((inp 0 (+ 1 inp)))
		     ((= inp in-chans))
		   (frame-set! inframe inp (src (vector-ref srcs inp) 0.0 (lambda (dir) (readin (vector-ref file inp))))))
		 (frame->file *output* i (frame->frame inframe mx outframe))
		 (if rev-mx (frame->file *reverb* i (frame->frame inframe rev-mx revframe)))))
	      ;; no envs
	      (run 
	       (lambda ()
		 (do ((i st (+ i 1)))
		     ((= i nd))
		   (do ((inp 0 (+ 1 inp)))
		       ((= inp in-chans))
		     (frame-set! inframe inp (src (vector-ref srcs inp) 0.0 (lambda (dir) (readin (vector-ref file inp))))))
		   (frame->file *output* i (frame->frame inframe mx outframe))
		   (if rev-mx (frame->file *reverb* i (frame->frame inframe rev-mx revframe)))))))))))


#|
  (with-sound (:channels 2 :statistics #t)
    (fullmix "pistol.snd")
    (fullmix "oboe.snd" 1 2 0 (list (list .1 (make-env '(0 0 1 1) :duration 2 :scaler .5)))))
|#
