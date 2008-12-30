(definstrument (wave time duration frequency amplitude
		     :key 
		     (ampenv '(0 0 10 1 90 1 100 0))
		     (location 0)
		     (distance 0)
		     (reverb 0)
		     (glissando 1)
		     (glissenv '(0 0 100 0)))
  "wave (time duration frequency amplitude
            :key 
            (ampenv '(0 0 10 1 90 1 100 0))
            (location 0)
            (distance 0)
            (reverb 0)
            (glissando 1)
            (glissenv '(0 0 100 0)))
 A simple sine wave instrument with envelope and glissando controls.
 (with-sound () (wave 0 1 440 .1))"
  (let* ((beg (seconds->samples time))
         (end (seconds->samples (+ time duration)))
         (osc (make-oscil frequency))
         (env (make-env ampenv :scaler amplitude
                        :duration duration ))
         (sig (make-locsig :degree location
                           :distance distance
                           :reverb reverb))
         (gls (make-env glissenv 
                        :duration duration
                        :scaler (hz->radians 
                                 (- (* frequency glissando)
                                    frequency)))))
    (run
     (lambda ()
       (do ((i beg (+ i 1)))
	   ((= i end) #t)
	 (locsig sig i (* (env env)
			  (oscil osc (env gls))))))
     )))

;; (with-sound () (wave 0 1 440 .1))
;; (with-sound () (wave 0 4 (hz 'c4) .8 :glissando 1.5 :ampenv '(0 0 2 1 99 1 100 0) :glissenv '(0 0 25 0 75 1 100 1)))

