;;; FM TRUMPET ---------------------------------------------------

;;; Dexter Morrill's FM-trumpet:
;;; from CMJ feb 77 p51

(definstrument (fm-trumpet startime dur
			   :key (frq1 250.0)
			   (frq2 1500.0)
			   (amp1 0.5)
			   (amp2 0.1)
			   (ampatt1 0.03)
			   (ampdec1 0.35)
			   (ampatt2 0.03)
			   (ampdec2 0.3)
			   (modfrq1 250.0)
			   (modind11 0.0)
			   (modind12 2.66)
			   (modfrq2 250.0)
			   (modind21 0.0)
			   (modind22 1.8)
			   (rvibamp 0.007)
			   (rvibfrq 125.0)
			   (vibamp 0.007)
			   (vibfrq 7.0)
			   (vibatt 0.6)
			   (vibdec 0.2)
			   (frqskw 0.03)
			   (frqatt 0.06)
			   (ampenv1 '(0 0  25 1  75 .9  100 0))
			   (ampenv2 '(0 0  25 1  75 .9  100 0))
			   (indenv1 '(0 0  25 1  75 .9  100 0))
			   (indenv2 '(0 0  25 1  75 .9  100 0))
			   (degree 0.0)
			   (distance 1.0)
			   (reverb-amount 0.005))
  (let* ((beg (seconds->samples startime))
	 (end (+ beg (seconds->samples dur)))
	 (loc (make-locsig degree distance reverb-amount))
	 (per-vib-f (make-env :envelope (stretch-envelope '(0 1  25 .1  75 0  100 0)
							  25 (min (* 100 (/ vibatt dur)) 45)
							  75 (max (* 100 (- 1.0 (/ vibdec dur))) 55))
			      :scaler vibamp :duration dur))
	 (ran-vib (make-rand-interp :frequency rvibfrq :amplitude rvibamp))
	 (per-vib (make-oscil :frequency vibfrq))
	 (dec-01 (max 75 (* 100 (- 1.0 (/ .01 dur)))))
	 (frq-f (make-env :envelope (stretch-envelope '(0 0  25 1  75 1  100 0)
						      25 (min 25 (* 100 (/ frqatt dur)))
						      75 dec-01)
			  :scaler frqskw :duration dur))
	 (ampattpt1 (min 25 (* 100 (/ ampatt1 dur))))
	 (ampdecpt1 (max 75 (* 100 (- 1.0 (/ ampdec1 dur)))))
	 (ampattpt2 (min 25 (* 100 (/ ampatt2 dur))))
	 (ampdecpt2 (max 75 (* 100 (- 1.0 (/ ampdec2 dur)))))
	 
	 (mod1-f (make-env :envelope (stretch-envelope indenv1 25 ampattpt1 75 dec-01)
			   :scaler (* modfrq1 (- modind12 modind11)) :duration dur))
	 (mod1 (make-oscil :frequency 0.0))
	 (car1 (make-oscil :frequency 0.0))
	 ;; set frequency to zero here because it is handled multiplicatively below
	 (car1-f (make-env :envelope (stretch-envelope ampenv1 25 ampattpt1 75 ampdecpt1)
			   :scaler amp1 :duration dur))
	 
	 (mod2-f (make-env :envelope (stretch-envelope indenv2 25 ampattpt2 75 dec-01)
			   :scaler (* modfrq2 (- modind22 modind21)) :duration dur))
	 (mod2 (make-oscil :frequency 0.0))
	 (car2 (make-oscil :frequency 0.0))
	 (car2-f (make-env :envelope (stretch-envelope ampenv2 25 ampattpt2 75 ampdecpt2)
			   :scaler amp2 :duration dur)))
    (ws-interrupt?)
    (run
     (lambda ()
       (do ((i beg (1+ i)))
	   ((= i end))
	 (let ((frq-change (hz->radians (* (+ 1.0 (rand-interp ran-vib))
					   (+ 1.0 (* (env per-vib-f) (oscil per-vib)))
					   (+ 1.0 (env frq-f))))))
	   (locsig loc i (+ (* (env car1-f) 
			       (oscil car1 (* frq-change 
					      (+ frq1 (* (env mod1-f) 
							 (oscil mod1 (* modfrq1 frq-change)))))))
			    (* (env car2-f) 
			       (oscil car2 (* frq-change 
					      (+ frq2 (* (env mod2-f) 
							 (oscil mod2 (* modfrq2 frq-change)))))))))))))))





