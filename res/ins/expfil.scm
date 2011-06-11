(defgenerator grn 
  (rampval 0.0 :type float) 
  (rampinc 0.0 :type float)
  (loc 0 :type int) 
  (segctr 0 :type int)
  (whichseg 0 :type int)
  (ramplen 0 :type int)
  (steadylen 0 :type int)
  (trigger 0 :type int))

(definstrument (expfil start duration hopsecs rampsecs steadysecs file1 file2)
  (let* ((fil1 (make-file->sample file1))
	 (fil2 (make-file->sample file2))
	 (hop (seconds->samples hopsecs))
	 (ramplen (seconds->samples rampsecs))
	 (steadylen (seconds->samples steadysecs))
	 (grn1 (make-grn :rampval 0.0 :rampinc (/ 1.0 ramplen) :loc 0 :segctr 0 :whichseg 0 :ramplen ramplen :steadylen steadylen :trigger 0))
	 (grn2 (make-grn :rampval 0.0 :rampinc (/ 1.0 ramplen) :loc 0 :segctr 0 :whichseg 0 :ramplen ramplen :steadylen steadylen :trigger 0))
	 (beg (seconds->samples start))
	 (end (+ beg (seconds->samples duration)))
	 (out1 beg)
	 (out2 (+ hop beg)))
    (run
     (do ((i beg (+ i 1)))
	 ((= i end))
       (let ((val 0.0))
	 (if (= i out1)
	     (let ((inval (ina (grn-loc grn1) fil1)))
	       (set! (grn-loc grn1) (+ 1 (grn-loc grn1)))
	       (if (= (grn-whichseg grn1) 0)	;ramp-up
		   (begin
		     (set! inval (* inval (grn-rampval grn1)))
		     (set! (grn-rampval grn1) (+ (grn-rampval grn1) (grn-rampinc grn1)))
		     (set! (grn-segctr grn1) (+ 1 (grn-segctr grn1)))
		     (if (= (grn-segctr grn1) (grn-ramplen grn1))
			 (begin
			   (set! (grn-segctr grn1) 0)
			   (set! (grn-whichseg grn1) (+ 1 (grn-whichseg grn1))))))
		   (if (= (grn-whichseg grn1) 1)		;steady-state
		       (begin
			 (set! (grn-segctr grn1) (+ 1 (grn-segctr grn1)))
			 (if (= (grn-segctr grn1) (grn-steadylen grn1))
			     (begin
			       (set! (grn-segctr grn1) 0)
			       (set! (grn-whichseg grn1) (+ 1 (grn-whichseg grn1))))))
		       (begin				;ramp-down
			 (set! inval (* inval (grn-rampval grn1)))
			 (set! (grn-segctr grn1) (+ 1 (grn-segctr grn1)))
			 (set! (grn-rampval grn1) (- (grn-rampval grn1) (grn-rampinc grn1)))
			 (if (= (grn-segctr grn1) (grn-ramplen grn1))
			     (begin
			       (set! (grn-segctr grn1) 0)
			       (set! (grn-trigger grn1) 1)
			       (set! (grn-whichseg grn1) 0)
			       (set! (grn-rampval grn1) 0.0))))))
	       (set! val inval)
	       (set! out1 (+ 1 out1))
	       (if (= (grn-trigger grn1) 1)
		   (begin
		     (set! (grn-trigger grn1) 0)
		     (set! out1 (+ out1 hop))))))
	 (if (= i out2)
	     (let ((inval (ina (grn-loc grn2) fil2)))
	       (set! (grn-loc grn2) (+ 1 (grn-loc grn2)))
	       (if (= (grn-whichseg grn2) 0)	;ramp-up
		   (begin
		     (set! inval (* inval (grn-rampval grn2)))
		     (set! (grn-rampval grn2) (+ (grn-rampval grn2) (grn-rampinc grn2)))
		     (set! (grn-segctr grn2) (+ 1 (grn-segctr grn2)))
		     (if (= (grn-segctr grn2) (grn-ramplen grn2))
			 (begin
			   (set! (grn-segctr grn2) 0)
			   (set! (grn-whichseg grn2) (+ 1 (grn-whichseg grn2))))))
		   (if (= (grn-whichseg grn2) 1)		;steady-state
		       (begin
			 (set! (grn-segctr grn2) (+ 1 (grn-segctr grn2)))
			 (if (= (grn-segctr grn2) (grn-steadylen grn2))
			     (begin
			       (set! (grn-segctr grn2) 0)
			       (set! (grn-whichseg grn2) (+ 1 (grn-whichseg grn2))))))
		       (begin				;ramp-down
			 (set! inval (* inval (grn-rampval grn2)))
			 (set! (grn-segctr grn2) (+ 1 (grn-segctr grn2)))
			 (set! (grn-rampval grn2) (- (grn-rampval grn2) (grn-rampinc grn2)))
			 (if (= (grn-segctr grn2) (grn-ramplen grn2))
			     (begin
			       (set! (grn-segctr grn2) 0)
			       (set! (grn-trigger grn2) 1)
			       (set! (grn-whichseg grn2) 0)
			       (set! (grn-rampval grn2) 0.0))))))
	       (set! val (+ val inval))
	       (set! out2 (+ 1 out2))
	       (if (= (grn-trigger grn2) 1)
		   (begin
		     (set! (grn-trigger grn2) 0)
		     (set! out2 (+ out2 hop))))))
	 (outa i val))))))

;;; (with-sound () (expfil 0 2 .2 .01 .1 "oboe.snd" "fyow.snd"))

