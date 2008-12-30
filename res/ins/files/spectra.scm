

(definstrument (spectra start-time duration frequency amplitude
		         :optional (partials '(1 1 2 0.5))
			           (amp-envelope '(0 0 50 1 100 0))
			           (vibrato-amplitude 0.005)
			           (vibrato-speed 5.0)
			           (degree 0.0)
			           (distance 1.0)
			           (reverb-amount 0.005))
  (let* ((beg (seconds->samples start-time))
	 (end (+ beg (seconds->samples duration)))
	 (waveform (partials->wave partials))
	 (freq (hz->radians frequency))
	 (s (make-table-lookup :frequency frequency :wave waveform))
	 (amp-env (make-env :envelope amp-envelope :scaler amplitude :duration duration))
	 (per-vib (make-triangle-wave :frequency vibrato-speed
				      :amplitude (* vibrato-amplitude freq)))
	 (loc (make-locsig degree distance reverb-amount))
	 (ran-vib (make-rand-interp :frequency (+ vibrato-speed 1.0)
				    :amplitude (* vibrato-amplitude freq))))
    (ws-interrupt?)
    (run 
     (lambda ()
       (do ((i beg (1+ i)))
	   ((= i end))
	 (locsig loc i (* (env amp-env) 
			  (table-lookup s (+ (triangle-wave per-vib)
					     (rand-interp ran-vib))))))))))

;    (with-sound ()
;      (spectra 0 1 440.0 .1 '(1.0 .4 2.0 .2 3.0 .2 4.0 .1 6.0 .1) 
;               '(0.0 0.0 1.0 1.0 5.0 0.9 12.0 0.5 25.0 0.25 100.0 0.0)))


