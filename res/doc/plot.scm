;; create empty plot window, then Control-click in window to add points

(plot )

;; export window's plot data and store in a variable

(define mydata (plot-data "Untitled Plot"))

;; create a titled plot

(plot :title "Hi Ho!" '(0 0 .25 1 .75 1 1 0))

;; create a plot with two layers of points

(plot '(0 0 .25 1 .75 1 1 0) '(0 0 1 1))

;; customize axes, add three named layers of points

(plot :title "My envelopes"
      :xaxis 'percent 
      :yaxis 'unit
      '(0 0 25 .9 75 .9 100 0) :title "ramp"	
      '(0 1 5 .5 10 .1 100 0) :title "expt" 
      '(0 0 50 1 100 0) :title "updown"
      )

;; pass only Y values to plot 

(plot :title "Random numbers" 
      :yaxis 'unit
      :style :histogram
      :values :y
      (loop repeat 20 collect (random 1.0)))

(plot :title "Hidy Ho!"
      :xaxis :percent 
      :yaxis :unit
      '(0 0 25 .9 80 .5 100 0) :style :envelope
      (loop for i to 100 by 10 collect i collect (random 1.0))
      :style :points)

;; Plot three fields of data, with duration sharing same axis as time.

(plot :title "Random Notes"
      :fields '((time seconds) (keynumber notes 60 96) (duration time))
      :style :hbox
      (loop repeat 20 
            for beg = 0 then (+ beg (random 1.0))
            for dur = (pick .1 .2 .3)
            for key = (between 60 96)
            collect (list beg key dur)))

;; compute layers on the fly

(plot (loop for x from 0 to 1 by .2
            for y = (random 1.0)
            collect x collect y)
      (loop for x from 0 to 1 by .1
            for y from 0 to 1 by .1
            collect x collect y)
      (loop for x from 0 to 1 by .25
            for y = (expt 10 (- x))
            collect x collect y))

;; plot a 'mean distribution' and its histogram in the same window

(let* ((maxh 0)
       (hist (make-list 100 0))
       (rans (loop for x from 0 below 100
                   for y = (floor (* (+ (random 100)
                                        (random 100) )
                                     .5))
                   collect x collect y
                   do
                   (let ((tail (list-tail hist y)))
                     (set-car! tail (+ 1 (car tail)))
                     (set! maxh (max (car tail) maxh)))))
       (bars (loop for y in hist for x from 0
                   when (> y 0) collect x
                   and collect (* (/ y maxh) 100)))
       )
  (plot :title "Mean distribution and histogram"
        :x-axis :percentage
        :y-axis :percentage
        rans :style 'point
        bars :style 'impulse
  ))

;; plot a sampled sine wave

(plot :x-axis (list 0 (* 2 pi) (/ pi 2) 2)
      :y-axis '(-1 1 .5)
      (loop for x from 0 to 1 by .01
	           for r = (* 2 pi x)
       	    collect r collect (sin r))
      :style 'line
      (loop for x from 0 to 1 by .05
            for r = (* 2 pi x)
            collect r collect (sin r))
      :style 'vlineandpoint
      )



