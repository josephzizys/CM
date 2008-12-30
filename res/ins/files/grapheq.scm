#|
From: Marco Trevisani <marco@ccrma.Stanford.EDU>

This should work like a Graphic Equalizer....
Very easy to use. Just some note:

"amp" & "amp-env" apply an enveloppe to the final result of the
filtering.  

"dur" as ""standard"" in my instruments, when dur = 0 it will take the length of the
sndfile input, otherwise the duration in seconds.

"gain-freq-list" is a list of gains and frequencies to
filter --in this order gain and frequencies--. There is no limit to
the size of the list. Gain can be a number or an
envelope. Unfortunatelly in this version they cant alternate, one
should chose, all envelopes or all numbers i.e.: 
case 1 -> '( .1 440.0 .3 1500.0 .2 330.0 ...etc) or 
case 2 -> '((0 .1 1 .5) 440.0 (0 1 1 .01) 1500 (0 .3 1 .5) 330.0 ...etc) 
'( .1 440.0 (0 1 1 .01) 1500 ..etc) <<< again, this is not allowed ..

"offset-gain" This apply to all the gains if case 1. It adds or
subtracts an offset to all the gains in the list. This number can be positive or
negative. In case the result is a negative number --let's say offset =
-.4 and, like in case 1, the first gain is .1, the result would be
-.3 -- the instrument will pass a gain equal to 0.  

"filt-gain-scale" & "filt-gain-base" will apply to the elements of the
envelopes if we are in case 2, gains are envelopes.

"stats" if #t --default-- prints the number of seconds processed, if
nil doesnt print anything, which will speed up a bit the process.
|#

(definstrument (graphEq file :key (beg 0) (dur 0) (or-beg 0) (amp 1) (amp-env '(0 1 .8 1 1 0)) (amp-base 1) 
	(offset-gain 0)  
	(gain-freq-list '((0 1 1 0) 440 (0 0 1 1) 660))      
	(filt-gain-scale 1)                   
	(filt-gain-base 1)                    
	(a1 .99)
	(stats #t))                      
  (let* ((st (seconds->samples beg))
	 (durata (if (= 0 dur) (mus-sound-duration file) dur))
	 (nd (+ st (seconds->samples durata)))
	 (or-start (inexact->exact (round (* or-beg (mus-sound-srate file)))))
	 (RdA (make-readin :file file :start or-start))
	 (half-list (/ (length gain-freq-list) 2))
	 (ampenv (make-env :envelope amp-env :scaler amp :duration durata :base amp-base))
	 (gain-list (let ((lst '())
			  (len (length gain-freq-list)))
		      (do ((i (- len 2) (- i 2)))
			  ((< i 0))
			(set! lst (cons (list-ref gain-freq-list i) lst)))
		      lst))
	 (freq-list (let ((lst '())
			  (len (length gain-freq-list)))
		      (do ((i (- len 1) (- i 2)))
			  ((<= i 0))
			(set! lst (cons (list-ref gain-freq-list i) lst)))
		      lst))
	 (env-size (if (list? (car gain-list))
		       (make-vector (length freq-list))
		       #f))
	 (if-list-in-gain (list? (car gain-list)))
	 (frm-size (make-vector (length freq-list)))
	 (gains (make-vct (length freq-list) 1.0))
	 (samp -1))

    (do ((k 0 (1+ k)))
	((= k half-list))
      (let ((gval (list-ref gain-list k))
	    (fval (list-ref freq-list k)))
	(if (list? gval)
	  (begin
	    (vector-set! env-size k (make-env :envelope gval
					      :scaler filt-gain-scale
					      :duration durata :base filt-gain-base))
	    (vector-set! frm-size k (make-formant fval a1)))
	  (begin
	    (vector-set! frm-size k (make-formant fval a1))
	    (vct-set! gains k (if (< (+ offset-gain gval) 0) 
				  0
				  (+ offset-gain gval)))))))
    (ws-interrupt?)
    (run
     (lambda ()
       (do ((i st (1+ i)))
	   ((= i nd))
	 (if stats 
	     (begin
	       (set! samp (1+ samp))
	       (if (= samp (mus-srate))
		   (begin
		     (snd-print (format #f "~% ~F" (/ i (mus-srate))))
		     (set! samp 0)))))
	 (let ((outval 0.0)
	       (inval (readin RdA)))
	   (do ((k 0 (1+ k)))
	       ((= k half-list))
	     (if if-list-in-gain
		 (vct-set! gains k (* (env (vector-ref env-size k)) (- 1.0 a1))))
	     (set! outval (+ outval (* (vct-ref gains k)
				       (formant (vector-ref frm-size k) inval)))))
	   (outa i (* (env ampenv) outval))))))))


