;;; spectral modeling (SMS)

(definstrument (pins beg dur file amp
		     (transposition 1.0) ; this can be used to transpose the sound
			  (time-scaler 1.0)    ; this can make things happen faster (< 1.0)/slower (> 1.0) in the output
			  (fftsize 256)        ; should be a power of 2
			  ;; at 22050 srate, this is ok for sounds above 300Hz or so, below that you need 512 or 1024,
			  ;; at 44100, probably best to double these sizes -- it takes some searching sometimes.
			  (highest-bin 128)    ; how high in fft data should we search for peaks
			  (max-peaks 16)       ; how many spectral peaks to track at the maximum
			  attack)	       ; whether to use original attack via time domain splice
  ;; do the sliding fft shuffle, translate to polar coordinates, find spectral peaks,
  ;;   match with current, do some interesting transformation, resynthesize using oscils
  ;;   All the envelopes are created on the fly.  max-peaks is how many of these peaks
  ;;   we are willing to track at any given time.
  (let* ((max-peaks-1 max-peaks)
	 (fftsize-1 fftsize)
	 (highest-bin-1 highest-bin)
	 (start (seconds->samples beg))
	 (end (+ start (seconds->samples dur)))
	 (fil (make-file->sample file))
	 (fdr (make-vct fftsize-1))
	 (fdi (make-vct fftsize-1))
	 (window (make-fft-window blackman2-window fftsize-1))
	 (fftamps (make-vct fftsize-1))
	 (max-oscils (* 2 max-peaks-1))
	 (current-peak-freqs (make-vct max-oscils))
	 (last-peak-freqs (make-vct max-oscils))
	 (current-peak-amps (make-vct max-oscils))
	 (last-peak-amps (make-vct max-oscils))
	 (peak-amps (make-vct max-peaks-1))
	 (peak-freqs (make-vct max-peaks-1))
	 (resynth-oscils (make-vector max-oscils))
	 (amps (make-vct max-oscils))	;run-time generated amplitude and frequency envelopes
	 (rates (make-vct max-oscils))
	 (freqs (make-vct max-oscils))
	 (sweeps (make-vct max-oscils))
	 (lowest-magnitude .001)
	 (hop (floor (/ fftsize-1 4)))
	 (outhop (floor (* time-scaler hop)))
	 (ifreq (/ 1.0 outhop))
	 (ihifreq (hz->radians ifreq))
	 (fftscale (/ 1.0 (* fftsize-1 .42323))) ;integrate Blackman-Harris window = .42323*window width and shift by fftsize-1
	 (fft-mag (/ (mus-srate) fftsize-1))
	 (furthest-away-accepted .1)
	 (filptr 0)
	 (trigger 0)
	 (sum 0.0)
	 (log10 (log 10.0))
	 (cur-oscils max-oscils)
	 (ramped (or attack 0))
	 (splice-attack (number? attack))
	 (attack-size (or attack 1))
	 (ramp-ind 0)
	 (ramped-attack (make-vct attack-size)))

    (do ((i 0 (+ i 1)))
	((= i max-oscils))
      (set! (resynth-oscils i) (make-oscil 0)))
    (set! trigger outhop)
    (vct-scale! window fftscale)
    (run
     (do ((i start (+ i 1)))
	 ((= i end))
       (if splice-attack
	   (let ((ramp (/ 1.0 attack-size)))
	     ;; my experience in translating SMS, and rumor via Greg Sandell leads me to believe that
	     ;; there is in fact no way to model some attacks successfully in this manner, so this block
	     ;; simply splices the original attack on to the rest of the note.  "attack" is the number
	     ;; of samples to include bodily.
	     (outa i (* amp (file->sample fil filptr)))
	     (set! filptr (+ 1 filptr))
	     (if (> filptr attack-size)
		 (let ((mult 1.0))
		   (do ((k 0 (+ 1 k)))
		       ((= k attack-size))
		     (set! (ramped-attack k) (* mult (file->sample fil (+ filptr k))))
		     (set! mult (- mult ramp)))
		   (set! splice-attack #f))))
	   (begin
	     (if (>= trigger outhop)
		 (let ((peaks 0))
		   ;; get next block of data and apply window to it
		   (set! trigger 0)
		   (do ((k 0 (+ 1 k)))
		       ((= k fftsize-1))
		     (set! (fdr k) (* (window k) (file->sample fil filptr)))
		     (set! filptr (+ 1 filptr)))
		   (vct-fill! fdi 0.0)
		   (set! filptr (- filptr (- fftsize-1 hop)))
		   ;; get the fft 
		   (mus-fft fdr fdi fftsize-1 1)
		   ;; change to polar coordinates (ignoring phases)
		   (do ((k 0 (+ 1 k)))
		       ((= k highest-bin-1))	;no need to paw through the upper half (so (<= highest-bin-1 (floor fft-size 2)))
		     (let ((x (fdr k))
			   (y (fdi k)))
		       (set! (fftamps k) (* 2 (sqrt (+ (* x x) (* y y)))))))
		   (do ((k 0 (+ 1 k)))
		       ((= k max-oscils))
		     (set! (last-peak-freqs k) (current-peak-freqs k))
		     (set! (last-peak-amps k) (current-peak-amps k))
		     (set! (current-peak-amps k) 0.0))
		   (vct-fill! peak-amps 0.0)
		   (let ((ra (fftamps 0))
			 (la 0.0)
			 (ca 0.0))
		     ;; search for current peaks following Xavier Serra's recommendations in
		     ;; "A System for Sound Analysis/Transformation/Synthesis 
		     ;;      Based on a Deterministic Plus Stochastic Decomposition"
		     (do ((k 0 (+ 1 k)))
			 ((= k highest-bin-1))
		       (set! la ca)
		       (set! ca ra)
		       (set! ra (fftamps k))
		       (if (and (> ca lowest-magnitude)
				(> ca ra)
				(> ca la))
			   ;; found a local maximum above the current threshold (its bin number is k-1)
			   (let* ((logla (/ (log la) log10))
				  (logca (/ (log ca) log10)) 
				  (logra (/ (log ra) log10))
				  (offset (/ (* .5 (- logla logra)) (+ logla (* -2 logca) logra))) ; isn't logca always 0?
				  (amp (expt 10.0 (- logca (* .25 (- logla logra) offset))))
				  (freq (* fft-mag (+ k offset -1))))
			     (if (= peaks max-peaks-1)
				 ;; gotta either flush this peak, or find current lowest and flush him
				 (let ((minp 0)
				       (minpeak (peak-amps 0)))
				   (do ((j 1 (+ 1 j)))
				       ((= j max-peaks-1))
				     (if (< (peak-amps j) minpeak)
					 (begin
					   (set! minp j)
					   (set! minpeak (peak-amps j)))))
				   (if (> amp minpeak)
				       (begin
					 (set! (peak-freqs minp) freq)
					 (set! (peak-amps minp) amp))))
				 (begin
				   (set! (peak-freqs peaks) freq)
				   (set! (peak-amps peaks) amp)
				   (set! peaks (+ 1 peaks))))))))
		   ;; now we have the current peaks -- match them to the previous set and do something interesting with the result
		   ;; the end results are reflected in the updated values in the rates and sweeps arrays.
		   ;; search for fits between last and current, set rates/sweeps for those found
		   ;;   try to go by largest amp first 
		   (do ((k 0 (+ 1 k)))
		       ((= k peaks))
		     (let ((maxp 0)
			   (maxpk (peak-amps 0)))
		       (do ((j 1 (+ 1 j)))
			   ((= j max-peaks-1))
			 (if (> (peak-amps j) maxpk)
			     (begin
			       (set! maxp j)
			       (set! maxpk (peak-amps j)))))
		       ;; now maxp points to next largest unmatched peak
		       (if (> maxpk 0.0)
			   (let* ((closestp -1)
				  (closestamp 10.0)
				  (current-freq (peak-freqs maxp))
				  (icf (/ 1.0 current-freq)))
			     (do ((j 0 (+ 1 j)))
				 ((= j max-peaks-1))
			       (if (> (last-peak-amps j) 0.0)
				   (let ((closeness (* icf (abs (- (last-peak-freqs j) current-freq)))))
				     (if (< closeness closestamp)
					 (begin
					   (set! closestamp closeness)
					   (set! closestp j))))))
			     (if (< closestamp furthest-away-accepted)
				 (begin
				   ;; peak-amp is transferred to appropriate current-amp and zeroed,
				   (set! (current-peak-amps closestp) (peak-amps maxp))
				   (set! (peak-amps maxp) 0.0)
				   (set! (current-peak-freqs closestp) current-freq)))))))
		   (do ((k 0 (+ 1 k)))
		       ((= k max-peaks-1))
		     (if (> (peak-amps k) 0.0)
			 ;; find a place for a new oscil and start it up
			 (let ((new-place -1))
			   (do ((j 0 (+ 1 j)))
			       ((or (not (= new-place -1))
				    (= j max-oscils)))
			     (if (and (= (last-peak-amps j) 0.0) 
				      (= (current-peak-amps j) 0.0))
				 (set! new-place j)))
			   (set! (current-peak-amps new-place) (peak-amps k))
			   (set! (peak-amps k) 0.0)
			   (set! (current-peak-freqs new-place) (peak-freqs k))
			   (set! (last-peak-freqs new-place) (peak-freqs k))
			   (set! (mus-frequency (resynth-oscils new-place)) (* transposition (peak-freqs k))))))
		   (set! cur-oscils 0)
		   (do ((k 0 (+ 1 k)))
		       ((= k max-oscils))
		     (set! (rates k) (* ifreq (- (current-peak-amps k) (last-peak-amps k))))
		     (if (or (not (= (current-peak-amps k) 0.0))
			     (not (= (last-peak-amps k) 0.0)))
			 (set! cur-oscils k))
		     (set! (sweeps k) (* ihifreq transposition (- (current-peak-freqs k) (last-peak-freqs k)))))
		   (set! cur-oscils (+ 1 cur-oscils))
		   ))
	     ;; run oscils, update envelopes
	     (set! trigger (+ 1 trigger))
	     (if (= ramped 0)
		 (set! sum 0.0)
		 (begin
		   (set! sum (ramped-attack ramp-ind))
		   (set! ramp-ind (+ 1 ramp-ind))
		   (if (= ramp-ind ramped) (set! ramped 0))))
	     (do ((k 0 (+ 1 k)))
		 ((= k cur-oscils))
	       (set! sum (+ sum (* (amps k) (oscil (resynth-oscils k) (freqs k)))))
	       (set! (amps k) (+ (amps k) (rates k)))
	       (set! (freqs k) (+ (freqs k) (sweeps k))))
	     (outa i (* amp sum))))))))
