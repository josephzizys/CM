;;; -------- PQW

(definstrument (pqw start dur spacing-freq carrier-freq amplitude ampfun indexfun partials
		    :key (degree 0.0)
			 (distance 1.0)
			 (reverb-amount 0.005))
  ;; phase-quadrature waveshaping used to create asymmetric (i.e. single side-band) spectra.
  ;; The basic idea here is a variant of sin x sin y - cos x cos y = cos (x + y)

  (let* ((normalized-partials (normalize-partials partials))
	 (spacing-cos (make-oscil :frequency spacing-freq :initial-phase (/ pi 2.0)))
	 (spacing-sin (make-oscil :frequency spacing-freq))
	 (carrier-cos (make-oscil :frequency carrier-freq :initial-phase (/ pi 2.0)))
	 (carrier-sin (make-oscil :frequency carrier-freq))
	 (sin-coeffs (partials->polynomial normalized-partials mus-chebyshev-second-kind))
	 (cos-coeffs (partials->polynomial normalized-partials mus-chebyshev-first-kind))
	 (amp-env (make-env :envelope ampfun :scaler amplitude :duration dur))
	 (ind-env (make-env :envelope indexfun :duration dur))
	 (loc (make-locsig degree distance reverb-amount))
	 (r (/ carrier-freq spacing-freq))
	 (tr (make-triangle-wave :frequency 5 :amplitude (hz->radians (* .005 spacing-freq))))
	 (rn (make-rand-interp :frequency 12 :amplitude (hz->radians (* .005 spacing-freq))))
	 (beg (seconds->samples start))
	 (end (+ beg (seconds->samples dur))))
    (ws-interrupt?)
    (run
     (lambda ()
       (do ((i beg (1+ i)))
	   ((= i end))
	 (let* ((vib (+ (triangle-wave tr) (rand-interp rn)))
		(ax (* (min 1.0 (env ind-env)) (oscil spacing-cos vib)))
		(fax (polynomial cos-coeffs ax))
		(yfax (* (oscil spacing-sin vib) (polynomial sin-coeffs ax))))
	   (locsig loc i (* (env amp-env)
			    (- (* (oscil carrier-sin (* vib r)) yfax) 
			       (* (oscil carrier-cos (* vib r)) fax))))))))))

; (pqw 0 .5 200 1000 .2 '(0 0 25 1 100 0) '(0 1 100 0) '(2 .1 3 .3 6 .5))
; to see the asymmetric spectrum most clearly, set the index function above to '(0 1 100 1)

