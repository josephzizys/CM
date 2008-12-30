(definstrument (drone startime dur frequency amp ampfun synth ampat ampdc amtrev deg dis rvibamt rvibfreq)
  (let* ((beg (seconds->samples startime))
	 (end (+ beg (seconds->samples dur)))
	 (waveform (partials->wave synth))
	 (amplitude (* amp .25))
	 (freq (hz->radians frequency))
	 (s (make-table-lookup :frequency frequency :wave waveform))
	 (amp-env (make-env :envelope (stretch-envelope ampfun 25 (* 100 (/ ampat dur)) 75 (- 100 (* 100 (/ ampdc dur))))
			    :scaler amplitude :duration dur))
	 (ran-vib (make-rand :frequency rvibfreq 
			     :amplitude (* rvibamt freq)))
	 (loc (make-locsig deg dis amtrev)))
    (ws-interrupt?)
    (run 
     (lambda ()
       (do ((i beg (1+ i)))
	   ((= i end))
	 (locsig loc i (* (env amp-env) (table-lookup s (+ (rand ran-vib))))))))))


(definstrument (canter beg dur pitch amp-1 deg dis pcrev ampfun ranfun skewfun
		       skewpc ranpc ranfreq indexfun atdr dcdr
		       ampfun1 indfun1 fmtfun1
		       ampfun2 indfun2 fmtfun2
		       ampfun3 indfun3 fmtfun3
		       ampfun4 indfun4 fmtfun4)
  (let* ((start (seconds->samples beg))
	 (end (+ start (seconds->samples dur)))
	 (amp (* amp-1 .25))		;pvc's amplitudes in bag.clm are very high (overflows)
	 (rangetop 910.0)
	 (rangebot 400.0)
	 (k (inexact->exact (floor (* 100 (/ (log (/ pitch rangebot)) (log (/ rangetop rangebot)))))))
	 (atpt (* 100 (/ atdr dur)))
	 (dcpt (- 100 (* 100 (/ dcdr dur))))
	 (lfmt1 (envelope-interp k fmtfun1))
	 (harm1 (inexact->exact (floor (+ .5 (/ lfmt1 pitch)))))
	 (dev11 (hz->radians (* (envelope-interp k indfun1) pitch)))
	 (dev01 (* dev11 .5))
	 (lamp1 (* (envelope-interp k ampfun1) amp (- 1 (abs (- harm1 (/ lfmt1 pitch))))))
	 (lfmt2 (envelope-interp k fmtfun2))
	 (harm2 (inexact->exact (floor (+ .5 (/ lfmt2 pitch)))))
	 (dev12 (hz->radians (* (envelope-interp k indfun2) pitch)))
	 (dev02 (* dev12 .5))
	 (lamp2 (* (envelope-interp k ampfun2) amp (- 1 (abs (- harm2 (/ lfmt2 pitch))))))
	 (lfmt3 (envelope-interp k fmtfun3))
	 (harm3 (inexact->exact (floor (+ .5 (/ lfmt3 pitch)))))
	 (dev13 (hz->radians (* (envelope-interp k indfun3) pitch)))
	 (dev03 (* dev13 .5))
	 (lamp3 (* (envelope-interp k ampfun3) amp (- 1 (abs (- harm3 (/ lfmt3 pitch))))))
	 (lfmt4 (envelope-interp k fmtfun4))
	 (harm4 (inexact->exact (floor (+ .5 (/ lfmt4 pitch)))))
	 (dev14 (hz->radians (* (envelope-interp k indfun4) pitch)))
	 (dev04 (* dev14 .5))
	 (lamp4 (* (envelope-interp k ampfun4) amp (- 1 (abs (- harm4 (/ lfmt4 pitch))))))
	 (tampfun (make-env :envelope (stretch-envelope ampfun 25 atpt 75 dcpt) :duration dur))
	 (tskwfun (make-env :envelope (stretch-envelope skewfun 25 atpt 75 dcpt) :scaler (hz->radians (* pitch skewpc)) :duration dur))
	 (tranfun (make-env :envelope (stretch-envelope ranfun 25 atpt 75 dcpt) :duration dur))
	 (tidxfun (make-env :envelope (stretch-envelope indexfun 25 atpt 75 dcpt) :duration dur))
	 (modgen (make-oscil :frequency pitch))
	 (gen1 (make-oscil :frequency (* pitch harm1)))
	 (gen2 (make-oscil :frequency (* pitch harm2)))
	 (gen3 (make-oscil :frequency (* pitch harm3)))
	 (gen4 (make-oscil :frequency (* pitch harm4)))
	 (ranvib (make-rand :frequency ranfreq :amplitude (hz->radians (* ranpc pitch))))
	 (loc (make-locsig deg dis pcrev)))
    (ws-interrupt?)
    (run
     (lambda ()
       (do ((i start (1+ i)))
	   ((= i end))
	 (let* ((frqval (+ (env tskwfun) (* (env tranfun) (rand ranvib))))
		(modval (oscil modgen frqval))
		(ampval (env tampfun))
		(indval (env tidxfun)))
	   (locsig loc i 
		   (+ (* lamp1 ampval (oscil gen1 (* (+ (* (+ dev01 (* indval dev11)) modval) frqval) harm1)))
		      (* lamp2 ampval (oscil gen2 (* (+ (* (+ dev02 (* indval dev12)) modval) frqval) harm2)))
		      (* lamp3 ampval (oscil gen3 (* (+ (* (+ dev03 (* indval dev13)) modval) frqval) harm3)))
		      (* lamp4 ampval (oscil gen4 (* (+ (* (+ dev04 (* indval dev14)) modval) frqval) harm4)))))))))))

