(use-modules (ice-9 optargs))

(provide 'snd-jcrev.scm)

(if (and (not (provided? 'snd-ws.scm)) 
	 (not (provided? 'sndlib-ws.scm)))
    (load-from-path "ws.scm"))


(definstrument (jc-reverb :optional (low-pass #f) (volume 1.0) (amp-env #f))
  "(jc-reverb (low-pass #f) (volume 1.0) (amp-env #f)) -- Chowning reverb"
  (let* ((allpass1 (make-all-pass -0.700 0.700 1051))
	 (allpass2 (make-all-pass -0.700 0.700  337))
	 (allpass3 (make-all-pass -0.700 0.700  113))
	 (comb1 (make-comb 0.742 4799))
	 (comb2 (make-comb 0.733 4999))
	 (comb3 (make-comb 0.715 5399))
	 (comb4 (make-comb 0.697 5801))
	 (chns (mus-channels *output*))
	 (outdel1 (make-delay (seconds->samples .013)))
	 (outdel2 (if (> chns 1) (make-delay (seconds->samples .011)) #f))
	 (comb-sum 0.0)
	 (comb-sum-1 0.0)
	 (comb-sum-2 0.0)
	 (all-sums 0.0)
	 (delA 0.0)
	 (delB 0.0)
	 (file-dur (mus-length *reverb*))
	 (decay-dur (mus-srate))
	 (len (floor (+ decay-dur file-dur)))
	 (envA (if amp-env (make-env :envelope amp-env :scaler volume :duration (exact->inexact (/ len (mus-srate)))) #f))
	 (scl volume))
    (ws-interrupt?)
    (if (or amp-env low-pass)
	(run
	 (lambda ()
	   (do ((i 0 (+ 1 i)))
	       ((= i len))
	     (let* ((inval (ina i *reverb*))
		    (allpass-sum (all-pass allpass3 (all-pass allpass2 (all-pass allpass1 inval))))
		    (amp (if envA (env envA) 1.0)))
	       (set! comb-sum-2 comb-sum-1)
	       (set! comb-sum-1 comb-sum)
	       (set! comb-sum 
		     (+ (comb comb1 allpass-sum)
			(comb comb2 allpass-sum)
			(comb comb3 allpass-sum)
			(comb comb4 allpass-sum)))
	       (if low-pass
		   (set! all-sums (+ (* .25 (+ comb-sum comb-sum-2)) (* .5 comb-sum-1)))
		   (set! all-sums comb-sum))
	       (outa i (* amp (delay outdel1 all-sums)))
	       (if (> chns 1) (outb i (* amp (delay outdel2 all-sums))))))))
	(run
	 (lambda ()
	   (do ((i 0 (+ 1 i)))
	       ((= i len))
	     (let ((allpass-sum (all-pass allpass3 (all-pass allpass2 (all-pass allpass1 (ina i *reverb*))))))
	       (set! comb-sum 
		     (+ (comb comb1 allpass-sum)
			(comb comb2 allpass-sum)
			(comb comb3 allpass-sum)
			(comb comb4 allpass-sum)))
	       (outa i (* scl (delay outdel1 comb-sum)))
	       (if (> chns 1) (outb i (* scl (delay outdel2 comb-sum)))))))))))

;;; (with-sound (:reverb jc-reverb) (fm-violin 0 .1 440 .1 :reverb-amount .3))
