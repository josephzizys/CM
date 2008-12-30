(definstrument (scratch start file src-ratio turnaroundlist)
  (let* ((f (make-file->sample file))
         (beg (seconds->samples start))
	 (turntable (list->vct turnaroundlist))
	 (turn-i 1)
	 (turns (length turnaroundlist))
	 (cur-sample (seconds->samples (vct-ref turntable 0)))
         (turn-sample (seconds->samples (vct-ref turntable turn-i)))
	 (turning 0)
	 (last-val 0.0)
	 (last-val2 0.0)
         (rd (make-src :srate src-ratio))
	 (forwards (> src-ratio 0.0)))
    (if (and forwards (< turn-sample cur-sample))
	(set! (mus-increment rd) (- src-ratio)))
    (ws-interrupt?)
    (run
     (lambda ()
       (do ((i beg (1+ i)))
	   ((>= turn-i turns))
	 (let ((val (src rd 0.0
			 (lambda (dir)
			   (let ((inval (file->sample f cur-sample)))
			     (set! cur-sample (+ cur-sample dir))
			     inval)))))
	   (if (= turning 0)
	       (if (and forwards (>= cur-sample turn-sample)) ;; we past turn point going forwards
		   (set! turning 1)
		   (if (and (not forwards) (<= cur-sample turn-sample)) ;; we past turn point going backwards
		       (set! turning -1)))
	       ;; wait for an inflection...
	       (if (or (and (<= last-val2 last-val) (>= last-val val))
		       (and (>= last-val2 last-val) (<= last-val val)))
		   (begin
		     (set! turn-i (1+ turn-i))
		     (if (< turn-i turns)
			 (begin
			   (set! turn-sample (seconds->samples (vct-ref turntable turn-i)))
			   (set! forwards (not forwards))
			   (set! (mus-increment rd) (- (mus-increment rd)))))
		     (set! turning 0))))
	   (set! last-val2 last-val)
	   (set! last-val val)
	   (outa i val)))))))

;;; (with-sound () (scratch 0.0 "now.snd" 1.5 '(0.0 .5 .25 1.0)))

