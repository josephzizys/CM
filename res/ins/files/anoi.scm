(definstrument (anoi infile start dur :optional (fftsize 128) (amp-scaler 1.0) (r (* 2.0 pi)))
  ;; a kind of noise reduction -- on-going average spectrum is squelched to some extent
  ;; obviously aimed at intermittent signal in background noise
  ;; this is based on Perry Cook's Scrubber.m
  (let* ((freq-inc (inexact->exact (floor (/ fftsize 2))))
	 (fdi (make-vct fftsize))
	 (fdr (make-vct fftsize))
	 (spectr (make-vct freq-inc 1.0))
	 (scales (make-vct freq-inc 1.0))
	 (diffs (make-vct freq-inc))
	 (win (make-fft-window blackman2-window fftsize))
	 (k 0)
	 (amp 0.0)
	 (incr (/ (* amp-scaler 4) (mus-srate)))
	 (beg (seconds->samples start))
	 (end (+ beg (seconds->samples dur)))
	 (file (make-file->sample infile))
	 (radius (- 1.0 (/ r fftsize)))
	 (bin (/ (mus-srate) fftsize))
	 (fs (make-vector freq-inc))
	 (samp 0))
    (do ((ctr 0 (1+ ctr)))
	((= ctr freq-inc))
      (vector-set! fs ctr (make-formant (* ctr bin) radius)))
    (ws-interrupt?)
    (run 
     (lambda ()
       (do ((i beg (1+ i)))
	   ((= i end))
	 (let ((inval (file->sample file samp)))
	   (set! samp (1+ samp))
	   (vct-set! fdr k inval)
	   (set! k (1+ k))
	   (if (< amp amp-scaler) (set! amp (+ amp incr)))
	   (if (>= k fftsize)
	       (begin
		 (set! k 0)
		 (spectrum fdr fdi win 1)
		 (do ((ctr 0 (1+ ctr)))
		     ((= ctr freq-inc))
		   (vct-set! spectr ctr (+ (* .9 (vct-ref spectr ctr)) (* .1 (vct-ref fdr ctr))))
		   (if (>= (vct-ref spectr ctr) (vct-ref fdr ctr)) 
		       (vct-set! diffs ctr 
				 (/ (vct-ref scales ctr) (- fftsize)))
		       (vct-set! diffs ctr
				 (/ (- (/ (- (vct-ref fdr ctr) (vct-ref spectr ctr)) 
					  (vct-ref fdr ctr)) 
				       (vct-ref scales ctr))
				    fftsize))))))
	   (let ((outval 0.0))
	     (do ((ctr 1 (1+ ctr)))
		 ((= ctr freq-inc))
	       (let ((cur-scale (vct-ref scales ctr)))
		 (set! outval (+ outval (* cur-scale (formant (vector-ref fs ctr) inval))))
		 (vct-set! scales ctr (+ (vct-ref scales ctr) (vct-ref diffs ctr)))))
	     (outa i (* amp outval)))))))))


#|
Date: Fri, 25 Sep 1998 09:56:41 +0300
From: Matti Koskinen <mjkoskin@sci.fi>
To: linux-audio-dev@ginette.musique.umontreal.ca
Subject: [linux-audio-dev] Announce: alpha version of denoising
[...]
	I wrote a simple denoiser called anoi after it's parent
	clm-instrument anoi.ins.

	anoi tries to remove white noise like tape hiss from wav-
	files. Removing of noise succeeds ok, but depending of the
	original sound, some distortion can be audible.

	If someone is interested, http://www.sci.fi/~mjkoskin
	contains tarred and gzipped file.

	Now only monophonic wav-files can be denoised, but adding
	others isn't too difficult. 

-matti
mjkoskin@sci.fi
|#

