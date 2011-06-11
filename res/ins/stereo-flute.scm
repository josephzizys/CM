;;; -------- STEREO-FLUTE

(definstrument (stereo-flute start dur freq flow 
			     (flow-envelope '(0  1 100 1))
			     (decay 0.01) 		; additional time for instrument to decay
			     (noise 0.0356) 
			     (embouchure-size 0.5)
			     (fbk-scl1 0.5)		; these two are crucial for good results
			     (fbk-scl2 0.55)
			     (offset-pos 0.764264) ; from 0.0 to 1.0 along the bore
			     (out-scl 1.0)
			     (a0 0.7) (b1 -0.3)	 ; filter coefficients
			     (vib-rate 5) (vib-amount 0.03)
			     (ran-rate 5) (ran-amount 0.03))
  "(stereo-flute dur freq flow 
     (flow-envelope '(0  1 100 1)) (decay 0.01)
	   (noise 0.0356) (embouchure-size 0.5) (fbk-scl1 0.5)
	   (fbk-scl2 0.55) (offset-pos 0.764264) (out-scl 1.0)
	   (a0 0.7) (b1 -0.3) (vib-rate 5) (vib-amount 0.03)
           (ran-rate 5) (ran-amount 0.03))
is a physical model of a flute:
  (stereo-flute 0 1 440 .55 :flow-envelope '(0 0 1 1 2 1 3 0))"

  (let* ((current-excitation 0.0)
	 (current-difference 0.0)
	 (current-flow 0.0)
	 (out-sig 0.0)
	 (tap-sig 0.0)
	 (previous-out-sig 0.0)
	 (previous-tap-sig 0.0)
	 (dc-blocked-a 0.0)
	 (dc-blocked-b 0.0)
	 (previous-dc-blocked-a 0.0)
	 (previous-dc-blocked-b 0.0) 
	 (delay-sig 0.0)
	 (emb-sig 0.0)
	 (beg (seconds->samples start))
	 (len (seconds->samples dur))
	 (end (+ beg len))
	 (flowf (make-env flow-envelope 
			  :scaler flow 
			  :duration (- dur decay)))
	 (periodic-vibrato (make-oscil vib-rate))
	 (random-vibrato (make-rand-interp :frequency ran-rate))
	 (breath (make-rand :frequency (/ (mus-srate) 2) :amplitude 1))
	 (period-samples (floor (/ (mus-srate) freq)))
	 (embouchure-samples (floor (* embouchure-size period-samples)))
	 (embouchure (make-delay embouchure-samples :initial-element 0.0))
	 (bore (make-delay period-samples))
	 (offset (floor (* period-samples offset-pos)))
	 (reflection-lowpass-filter (make-one-pole a0 b1)))
    (run
     (do ((i beg (+ i 1)))
	 ((= i end))
       (set! delay-sig (delay bore out-sig))
       (set! emb-sig (delay embouchure current-difference))
       (set! current-flow (+ (* vib-amount (oscil periodic-vibrato)) 
			     (* ran-amount (rand-interp random-vibrato)) 
			     (env flowf)))
       (set! current-difference 
	     (+ current-flow 
		(* noise current-flow (rand breath))
		(* fbk-scl1 delay-sig)))
       (set! current-excitation (- emb-sig (* emb-sig emb-sig emb-sig)))
       (set! out-sig (one-pole reflection-lowpass-filter 
			       (+ current-excitation (* fbk-scl2 delay-sig))))
       (set! tap-sig (tap bore offset))
       ;; NB the DC blocker is not in the cicuit. It is applied to the out-sig 
       ;; but the result is not fed back into the system.
       (set! dc-blocked-a (+ (- out-sig previous-out-sig) (* 0.995 previous-dc-blocked-a)))
       (set! dc-blocked-b (+ (- tap-sig previous-tap-sig) (* 0.995 previous-dc-blocked-b)))
       (outa i (* out-scl dc-blocked-a))
       (outb i (* out-scl dc-blocked-b))
       (set! previous-out-sig out-sig)
       (set! previous-dc-blocked-a dc-blocked-a)
       (set! previous-tap-sig tap-sig)
       (set! previous-dc-blocked-b dc-blocked-b)))))
