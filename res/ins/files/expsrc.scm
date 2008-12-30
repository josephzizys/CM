(define* (clm-expsrc beg dur input-file exp-ratio src-ratio amp :optional rev start-in-file)
  (let* ((st (seconds->samples beg))
	 (stf (inexact->exact (floor (* (or start-in-file 0) (mus-sound-srate input-file)))))
	 (fdA (make-readin input-file :channel 0 :start stf))
	 (exA (make-granulate :expansion exp-ratio))
	 (two-chans (and (= (mus-sound-chans input-file) 2) (= (mus-channels *output*) 2)))
	 (fdB (and two-chans (make-readin input-file :channel 1 :start stf)))
	 (exB (and two-chans (make-granulate :expansion exp-ratio)))
	 (srcA (make-src :srate src-ratio))
	 (srcB (and two-chans (make-src :srate src-ratio)))
	 (revit (and *reverb* rev))
	 (rev-amp (if revit (if two-chans (* rev .5) rev) 0.0))
	 (nd (+ st (seconds->samples dur))))
    (run
     (lambda ()
       (do ((i st (1+ i))) ((= i nd))
	 (let ((valA               (* amp (src srcA 0.0 (lambda (dir) (granulate exA (lambda (dir) (readin fdA)))))))
	       (valB (if two-chans (* amp (src srcB 0.0 (lambda (dir) (granulate exB (lambda (dir) (readin fdB)))))) 0.0)))
	 (out-any i valA 0)
	 (if two-chans (out-any i valB 1))
	 (if revit (out-any i (* rev-amp (+ valA valB)) 0 *reverb*))))))))



