
(definstrument (za time dur freq amp length1 length2 feedback feedforward)
  (let* ((beg (seconds->samples time))
	 (end (+ beg (seconds->samples dur)))
	 (s (make-pulse-train :frequency freq))
	 (d0 (make-all-pass feedback feedforward :size length1 :max-size (1+ (max length1 length2))))
	 (zenv (make-env :envelope '(0 0 1 1) :scaler (- length2 length1) :duration dur)))
    (ws-interrupt?)
    (run
     (lambda ()
       (do ((i beg (1+ i)))
	   ((= i end))
	 (outa i (all-pass d0 (* amp (pulse-train s)) (env zenv))))))))

;;(with-sound () (za 0 1 100 .1 20 100 .95 .95) (za 1.5 1 100 .1 100 20 .95 .95))
