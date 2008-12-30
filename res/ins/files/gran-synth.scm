
(definstrument (gran-synth start-time duration audio-freq grain-dur grain-interval amp)
  (let* ((beg (seconds->samples start-time))
	 (end (+ beg (seconds->samples duration)))
	 (grain-env (make-env :envelope '(0 0 25 1 75 1 100 0) :duration grain-dur))
	 (carrier (make-oscil :frequency audio-freq))
	 (grain-size (inexact->exact (ceiling (* (max grain-dur grain-interval) (mus-srate)))))
	 (grains (make-wave-train :size grain-size :frequency (/ 1.0 grain-interval)))
	 (grain (mus-data grains)))
    (do ((i 0 (1+ i)))
	((= i grain-size))
      (vct-set! grain i (* (env grain-env) (oscil carrier))))
    (ws-interrupt?)
    (run
     (lambda ()
       (do ((i beg (1+ i)))
	   ((= i end))
	 (outa i (* amp (wave-train grains))))))))
	 
;;; (with-sound () (gran-synth 0 2 100 .0189 .02 .4))


