;;; taken from Perry Cook's stkv1.tar.Z (Synthesis Toolkit), but I was
;;; in a bit of a hurry and may not have made slavishly accurate translations.
;;; Please let me know of any errors.

(definstrument (tubebell beg dur freq amp (base 32.0))
  ;; from Perry Cook's TubeBell.cpp
  (let* ((osc0 (make-oscil (* freq 0.995)))
	 (osc1 (make-oscil (* freq 1.414 0.995)))
	 (osc2 (make-oscil (* freq 1.005)))
	 (osc3 (make-oscil (* freq 1.414)))
	 (ampenv1 (make-env (list 0 0 .005 1 dur 0) :base base :duration dur))
	 (ampenv2 (make-env (list 0 0 .001 1 dur 0) :base (* 2 base) :duration dur))
	 (ampmod (make-oscil 2.0))
	 (g0 (* .5 amp .707))
	 (g1 .203)
	 (g2 (* .5 amp 1.0))
	 (g3 .144)
	 (st (seconds->samples beg))
	 (nd (+ st (seconds->samples dur))))
    (run
     (do ((i st (+ i 1)))
	 ((= i nd))
       (outa i (* (+ (* .007 (oscil ampmod)) .993)
		  (+ (* g0 (env ampenv1) (oscil osc0 (* g1 (oscil osc1))))
		     (* g2 (env ampenv2) (oscil osc2 (* g3 (oscil osc3)))))))))))

