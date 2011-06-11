
(definstrument (rhodey beg dur freq amp (base .5))
  ;; from Perry Cook's Rhodey.cpp
  (let* ((osc0 (make-oscil freq))
	 (osc1 (make-oscil (* freq 0.5)))
	 (osc2 (make-oscil freq))
	 (osc3 (make-oscil (* freq 15.0)))
	 (ampenv1 (make-env (list 0 0 .005 1 dur 0) :base base :duration dur))
	 (ampenv2 (make-env (list 0 0 .001 1 dur 0) :base (* base 1.5) :duration dur))
	 (ampenv3 (make-env (list 0 0 .001 1 .25 0 (max dur .26) 0) :base (* base 4) :duration dur))
	 (g0 (* .5 amp))
	 (g1 .535)
	 (g2 (* .5 amp))
	 (g3 .109)
	 (st (seconds->samples beg))
	 (nd (+ st (seconds->samples dur))))
    (run
     (do ((i st (+ i 1)))
	 ((= i nd))
       (outa i (+ (* g0 (env ampenv1) (oscil osc0 (* g1 (oscil osc1))))
		  (* g2 (env ampenv2) (oscil osc2 (* (env ampenv3) g3 (oscil osc3))))))))))

