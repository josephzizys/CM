(definstrument (metal beg dur freq amp)
  ;; from Perry Cook's HeavyMtl.cpp
  (let* ((osc0 (make-oscil freq))
	 (osc1 (make-oscil (* freq 4.0 0.999)))
	 (osc2 (make-oscil (* freq 3.0 1.001)))
	 (osc3 (make-oscil (* freq 0.50 1.002)))
	 (ampenv0 (make-env (list 0 0 .001 1 (- dur .002) 1 dur 0) :duration dur))
	 (ampenv1 (make-env (list 0 0 .001 1 (- dur .011) 1 dur 0) :duration dur))
	 (ampenv2 (make-env (list 0 0 .01 1 (- dur .015) 1 dur 0) :duration dur))
	 (ampenv3 (make-env (list 0 0 .03 1 (- dur .040) 1 dur 0) :duration dur))
	 (g0 (* .615 amp))
	 (g1 .202)
	 (g2 .574)
	 (g3 .116)
	 (st (seconds->samples beg))
	 (nd (+ st (seconds->samples dur))))
    (run
     (do ((i st (+ i 1)))
	 ((= i nd))
       (outa i (* g0 (env ampenv0) 
		  (oscil osc0 
			 (+ (* g1 (env ampenv1) 
			       (oscil osc1 
				      (* g2 (env ampenv2) 
					 (oscil osc2))))
			    (* g3 (env ampenv3) 
			       (oscil osc3))))))))))

