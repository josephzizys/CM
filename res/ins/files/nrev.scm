(definstrument (nrev :key (reverb-factor 1.09) (lp-coeff 0.7) (volume 1.0))
  ;; reverb-factor controls the length of the decay -- it should not exceed (/ 1.0 .823)
  ;; lp-coeff controls the strength of the low pass filter inserted in the feedback loop
  ;; output-scale can be used to boost the reverb output
  (define (prime? val)
    (or (= val 2)
	(and (odd? val)
	     (do ((i 3 (+ i 2))
		  (lim (sqrt val)))
		 ((or (= 0 (modulo val i)) (> i lim))
		  (> i lim))))))
  (define (next-prime val)
    (if (prime? val)
	val
	(next-prime (+ val 2))))
       
  (let* ((srscale (/ (mus-srate) 25641))
	 (val 0)
	 (dly-len (list 1433 1601 1867 2053 2251 2399 347 113 37 59 53 43 37 29 19)))
    (do ((i 0 (1+ i)))
	((= i 15))
      (let ((val (inexact->exact (floor (* srscale (list-ref dly-len i))))))
	(if (even? val) (set! val (1+ val)))
	(list-set! dly-len i (next-prime val))))

    (let* ((len (+ (mus-srate) (mus-length *reverb*)))
	   (comb1 (make-comb (* .822 reverb-factor) (list-ref dly-len 0)))
	   (comb2 (make-comb (* .802 reverb-factor) (list-ref dly-len 1)))
	   (comb3 (make-comb (* .773 reverb-factor) (list-ref dly-len 2)))
	   (comb4 (make-comb (* .753 reverb-factor) (list-ref dly-len 3)))
	   (comb5 (make-comb (* .753 reverb-factor) (list-ref dly-len 4)))
	   (comb6 (make-comb (* .733 reverb-factor) (list-ref dly-len 5)))
	   (low (make-one-pole lp-coeff (- lp-coeff 1.0)))
	   (chan2 (> (mus-channels *output*) 1))
	   (chan4 (= (mus-channels *output*) 4))
	   (allpass1 (make-all-pass -0.700 0.700 (list-ref dly-len 6)))
	   (allpass2 (make-all-pass -0.700 0.700 (list-ref dly-len 7)))
	   (allpass3 (make-all-pass -0.700 0.700 (list-ref dly-len 8)))
	   (allpass4 (make-all-pass -0.700 0.700 (list-ref dly-len 9))) ; 10 for quad
	   (allpass5 (make-all-pass -0.700 0.700 (list-ref dly-len 11)))
	   (allpass6 (if chan2 (make-all-pass -0.700 0.700 (list-ref dly-len 12)) #f))
	   (allpass7 (if chan4 (make-all-pass -0.700 0.700 (list-ref dly-len 13)) #f))
	   (allpass8 (if chan4 (make-all-pass -0.700 0.700 (list-ref dly-len 14)) #f)))
      (ws-interrupt?)
      (run
       (lambda ()
	 (do ((i 0 (1+ i)))
	     ((= i len))
	   (let* ((rev (* volume (ina i *reverb*)))
		  (outrev (all-pass allpass4
				    (one-pole low
					      (all-pass allpass3
							(all-pass allpass2
								  (all-pass allpass1
									    (+ (comb comb1 rev)
									       (comb comb2 rev)
									       (comb comb3 rev)
									       (comb comb4 rev)
									       (comb comb5 rev)
									       (comb comb6 rev)))))))))
	     (outa i (all-pass allpass5 outrev))
	     (if chan2 (outb i (all-pass allpass6 outrev)))
	     (if chan4 (outc i (all-pass allpass7 outrev)))
	     (if chan4 (outd i (all-pass allpass8 outrev))))))))))