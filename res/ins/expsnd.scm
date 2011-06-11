(definstrument (exp-snd file beg dur amp (exp-amt 1.0) (ramp .4) (seglen .15) (sr 1.0) (hop .05) ampenv)
  ;; granulate with envelopes on the expansion amount, segment envelope shape,
  ;; segment length, hop length, and input file resampling rate
  (let* ((st (seconds->samples beg))
	 (nd (+ st (seconds->samples dur)))
	 (f0 (make-readin file 0))
	 (expenv (make-env (if (list? exp-amt) 
					 (or exp-amt (list 0 1 1 1)) 
					 (list 0 exp-amt 1 exp-amt))
			   :duration dur))
	 (lenenv (make-env (if (list? seglen) 
					 (or seglen (list 0 .15 1 .15)) 
					 (list 0 seglen 1 seglen))
			   :duration dur))
	 (max-seg-len (if seglen (if (list? seglen) (max-envelope seglen) seglen) .15))
	 (initial-seg-len (if seglen (if (list? seglen) (cadr seglen) seglen) .15))
	 (scaler-amp (if (> max-seg-len .15) (/ (* 0.6 .15) max-seg-len) 0.6))
	 (srenv  (make-env (if (list? sr) 
					 (or sr (list 0 1 1 1)) 
					 (list 0 sr 1 sr))
			   :duration dur))
	 (rampdata (if (list? ramp) 
		       (or ramp (list 0 .4 1 .4))
		       (list 0 ramp 1 ramp)))
	 (rampenv (make-env rampdata :duration dur))
	 (initial-ramp-time (if ramp (if (list? ramp) (cadr ramp) ramp) .4))
	 (hopenv (make-env (if (list? hop) 
					 (or hop (list 0 .05 1 .05)) 
					 (list 0 hop 1 hop))
			   :duration dur))
	 (max-out-hop (if hop (if (list? hop) (max-envelope hop) hop) .05))
	 (initial-out-hop (if hop (if (list? hop) (cadr hop) hop) .05))
	 (min-exp-amt (if exp-amt (if (list? exp-amt) (min-envelope exp-amt) exp-amt) 1.0))
	 (initial-exp-amt (if exp-amt (if (list? exp-amt) (cadr exp-amt) exp-amt) 1.0))
	 (max-in-hop (/ max-out-hop min-exp-amt))
	 (max-len (seconds->samples (+ (max max-out-hop max-in-hop) max-seg-len)))
	 (ampe (make-env (or ampenv (list 0 0 .5 1 1 0)) :scaler amp :duration dur))
	 (exA (make-granulate :expansion initial-exp-amt
			      :input f0
			      :max-size max-len
			      :ramp initial-ramp-time 
			      :hop initial-out-hop
			      :length initial-seg-len 
			      :scaler scaler-amp))
	 (ex-samp 0.0)
	 (next-samp 0.0)
	 (vol (env ampe))
	 (valA0 (* vol (granulate exA)))
	 (valA1 (* vol (granulate exA))))
    (if (or (<= (min-envelope rampdata) 0.0)
	    (>= (max-envelope rampdata) 0.5))
	(format #t "ramp argument to exp-snd must always be between 0.0 and 0.5: ~A" ramp)
	(run
	 (do ((i st (+ i 1)))
	     ((= i nd))
	   (let* ((expa (env expenv)) ;current expansion amount
		  (segl (env lenenv)) ;current segment length
		  (resa (env srenv)) ;current resampling increment
		  (rmpl (env rampenv)) ;current ramp length (0 to .5)
		  (hp (env hopenv)) ;current hop size
		  ;; now we set the granulate generator internal state to reflect all these envelopes
		  (sl (seconds->samples segl))
		  (rl (floor (* rmpl sl))))
	     (set! vol (env ampe))
	     (set! (mus-length exA) sl)
	     (set! (mus-ramp exA) rl)
	     (set! (mus-frequency exA) hp)
	     (set! (mus-increment exA) expa)
	     (set! next-samp (+ next-samp resa))
	     (if (> next-samp (+ 1 ex-samp))
		 (let ((samps (floor (- next-samp ex-samp))))
		   (do ((k 0 (+ 1 k)))
		       ((= k samps))
		     (set! valA0 valA1)
		     (set! valA1 (* vol (granulate exA)))
		     (set! ex-samp (+ 1 ex-samp)))))
	     (if (= next-samp ex-samp)
		 (outa i valA0)
		 (outa i (+ valA0 (* (- next-samp ex-samp) (- valA1 valA0)))))))))))

;;; (with-sound () (exp-snd "fyow.snd" 0 3 1 '(0 1 1 3) 0.4 .15 '(0 2 1 .5) 0.05))
;;; (with-sound () (exp-snd "oboe.snd" 0 3 1 '(0 1 1 3) 0.4 .15 '(0 2 1 .5) 0.2))

