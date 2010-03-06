;; A simple fm instrument with envelopes

(definstrument (fm time duration frequency amplitude
                   (ampenv '(0 0 25 1 75 1 100 0))
                   (cmratio 1) (index 1) (indenv '(0 1 100 1))
                   (degree 0) (distance 0) (reverb 0))
  "fm (time duration frequency amplitude
            (ampenv '(0 0 10 1 90 1 100 0))
            (cmratio 1)
            (index 1)
            (indenv '(0 0 100 0))
            (degree 0)
            (distance 0)
            (reverb 0))
 A simple fm instrument with envelope controls.
 (with-sound () (fm 0 1 440 .1))"
  (let* ((beg (seconds->samples time))
         (end (seconds->samples (+ time duration)))
         (car (make-oscil :frequency frequency))
         (mod (make-oscil :frequency (* frequency cmratio)))
         (ampf (make-env ampenv :scaler amplitude 
                         :duration duration))
         (devf (make-env indenv :duration duration
                         :scaler (hz->radians (* frequency cmratio index))))
         (loc (make-locsig :degree degree :distance distance 
                           :reverb reverb)))
    (run
     (lambda ()
       (do ((i beg (+ i 1)))
	   ((= i end) #t)
	 (locsig loc i (* (env ampf) 
			  (oscil car (* (env devf) 
					(oscil mod))))))))))

