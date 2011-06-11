(definstrument (resflt start dur driver 
	       ranfreq noiamp noifun cosamp cosfreq1 cosfreq0 cosnum
	       ampcosfun freqcosfun 
	       frq1 r1 g1 frq2 r2 g2 frq3 r3 g3
	       (degree 0.0)
		    (distance 1.0)
		    (reverb-amount 0.005))
  ;; driver=0 -- use sum of cosines to drive the filter,
  ;; driver=1 -- use white noise
  ;; if noise used, ranfreq=frequency of random number generator,
  ;;                noiamp=amplitude thereof,
  ;;                noifun=amplitude envelope on white noise
  ;; if ncos (i.e. a band-limited pulse train),
  ;;                cosamp=amplitude of pulse train,
  ;;                cosfreq1=top frequency (given freqcosfun) (i.e. pulse frequency)
  ;;                cosfreq0=bottom frequency,
  ;;                cosnum=number of cosines in the pulse,
  ;;                ampcosfun=amplitude envelope on pulse train
  ;;                freqcosfun=frequency envelope on pulse train
  ;; There are then 3 resonators, centered at frq1, frq2, frq3,
  ;; with pole-radius r1, r2, and r3 respectively, and
  ;; with gains of g1, g2, and g3.

  (let* ((beg (seconds->samples start))
	 (end (+ beg (seconds->samples dur)))
	 (f1 (make-two-pole :radius r1 :frequency frq1))
	 (f2 (make-two-pole :radius r2 :frequency frq2))
	 (f3 (make-two-pole :radius r3 :frequency frq3))
	 (with-noise (= driver 1))
	 (loc (make-locsig degree distance reverb-amount))
	 (frqf (if (not with-noise)
		   (make-env freqcosfun  :duration dur
			      :scaler (hz->radians (- cosfreq1 cosfreq0)))
		   #f))
	 (ampf (if with-noise
		   (make-env noifun :scaler noiamp :duration dur)
		   (make-env ampcosfun :scaler cosamp :duration dur)))
	 (rn (if with-noise
		 (make-rand :frequency ranfreq)
		 #f))
	 (cn (if (not with-noise)
		 (make-ncos cosfreq0 cosnum)
		 #f)))
    (run
     (do ((i beg (+ i 1)))
	 ((= i end))
       (let ((input1 (if with-noise
			 (* (env ampf) (rand rn))
			 (* (env ampf) (ncos cn (env frqf))))))
	 (locsig loc i (+ (two-pole f1 (* input1 g1))
			  (two-pole f2 (* input1 g2))
			  (two-pole f3 (* input1 g3)))))))))


;  (resflt 0 1.0 0 0 0 #f .1 200 230 10 '(0 0 50 1 100 0) '(0 0 100 1) 500 .995 .1 1000 .995 .1 2000 .995 .1)
;  (resflt 0 1.0 1 10000 .01 '(0 0 50 1 100 0) 0 0 0 0 #f #f 500 .995 .1 1000 .995 .1 2000 .995 .1)

