(definstrument (cnvrev file impulse (rev-amt .1))
  (let* ((file-len (mus-sound-frames file))
	 (filter-len (mus-sound-frames impulse))
	 (filter-chan0 (make-vct filter-len))
	 (filter-chan1 (and (= (mus-channels *output*) 2) 
			    (> (mus-sound-chans impulse) 1)
			    (make-vct filter-len))))
    (file->array impulse 0 0 filter-len filter-chan0)
    (if filter-chan1
	(file->array impulse 1 0 filter-len filter-chan1)
      (set! filter-chan1 filter-chan0))
    (let* ((fd (make-readin file))
	   (fd1 (and (= (mus-channels *output*) 2) 
		     (> (mus-sound-chans file) 1)
		     (make-readin file :channel 1)))
	   (ff0 (make-convolve :input fd :filter filter-chan0))
	   (ff1 (and (= (mus-channels *output*) 2) 
		     (> (mus-sound-chans file) 1)
		     (make-convolve :input fd1 :filter filter-chan1)))
	   (end (+ file-len filter-len)))
      (run
       (do ((i 0 (+ i 1)))
	   ((= i end))
	 (outa i (* rev-amt (convolve ff0)))
	 (if (and (= (mus-channels *output*) 2) 
		  ff1) 
	     (outb i (* rev-amt (convolve ff1)))))))))


#|
 (with-sound (:statistics #t :scaled-to .5 :srate 44100 :channels 1) 
   (cnvrev "oboe.snd" "fyow.snd"))
|#


