;
;; Create empty plot window, then Control-click in window to add points
;

(plot )

; Export window's plot data and store in a variable

(define mydata (plot-data "Untitled Plot"))

mydata

;
;; Create a titled plot
;

(plot :title "Hi Ho!" '(0 0 .25 1 .75 1 1 0))

;
;; Create a plot with two layers of points
;

(plot '(0 0 .25 1 .75 1 1 0) '(0 0 1 1))

;
;; Customize axes, add three named layers of points
;

(plot :title "My envelopes"
      :xaxis 'percent 
      :yaxis 'unit
      '(0 0 25 .9 75 .9 100 0) :title "ramp"	
      '(0 1 5 .5 10 .1 100 0) :title "expt" 
      '(0 0 50 1 100 0) :title "updown"
      )

;
;; a two layered plot, each layer with its own style 
;

(plot :title "Hidy Ho!"
      :xaxis :percent 
      :yaxis :unit
      '(0 0 25 .9 80 .5 100 0) :style :envelope
      (loop for i to 100 by 10 collect i collect (random 1.0))
      :style :points)

;
;; Piano roll plot of 5-field note data with duration on time axis
;; and a constrained keynum axis
;

(plot :title "My Notes"
      :fields '((time seconds) (dur time) (pitch keynum 60 96)
                (amplitude unit) (chan 0 15))
      :xaxis '(time dur)
      :yaxis 'pitch
      :style 'hbox
      (loop repeat 20 with amp = .7
            for beg = 0 then (+ beg (random 1.0))
            for dur = (pick .1 .2 .3)
            for key = (between 60 96)
            for chan = (random 16)
            collect (list beg dur key amp chan)))

;
;; Compute some layers on the fly
;

(plot (loop for x from 0 to 1 by .2
            for y = (random 1.0)
            collect x collect y)
      (loop for x from 0 to 1 by .1
            for y from 0 to 1 by .1
            collect x collect y)
      (loop for x from 0 to 1 by .25
            for y = (expt 10 (- x))
            collect x collect y))

;
;; Plot a 'mean distribution' and its histogram in the same window
;

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

;
;; plot a pretty picture of a "sampled sine wave"
;

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

;
;; michael klingbeil's stretched harmonics example
;

(define (arpeggiate-exprhy keynums offset duration rate midpoint-frac
                           amplow amphi legato bass-legato
                           bass-cutoff last-legato)
  (let* ((segn (length keynums))
         (last (- segn 1))
         (midpoint (floor (* segn midpoint-frac)))
         ;; deltas below midpoint follow one curve, above another.
         (deltas (append (segs midpoint (* midpoint-frac duration) 1 rate)
                         (segs (- segn midpoint) 
                               (* (- 1 midpoint-frac) duration)
			                            1 
                               (/ 1 rate)))))
    (loop with time = 0
          for i from 0
          for k in keynums
          for d in deltas
          for r = (if (< k bass-cutoff)
                      bass-legato
                      (if (= i last)
                          (* last-legato d)
                          (* legato d)))
          for a = (between 0.45 0.5)
          collect (list (+ offset time)
                        k
                        r
                        a)
       	  do (set! time (+ time d)))))

(define (distort-harmonics fund distort)
  (loop for h from 1 below (floor (/ 25.0 distort)) 
        if (odds (* 0.9 distort))
        collect (key (* fund (expt h distort)))))

(define (arpa-harmonic note dur gap)
  ;; spawn overlapping arpeggios with mean duration of dur and mean
  ;; gap between arpeggio starts of gap seconds. each arpeggio is
  ;; upward with the general direction of arpeggio starting notes
  ;; moving downward
  (let ((result (list)))
    (loop with fund = (hz note) and time = 0
          for distort from 0.7 below 1.05 by 0.05
          for notes = (distort-harmonics fund distort)
          for arpa = (arpeggiate-exprhy notes
                                        time (* (vary dur 0.1) distort)
                                        (between 4.0 0.25)
                                        (between 0.3 0.6)
                                        0.3  ; amplow
                                        0.8  ; amphi
                                        (* dur distort 0.7) ; bass legato
                                        2.0   ; legato 
                                        59    ; bass cutoff
                                        1.0)
          do
       	  (set! result (sort! (append result arpa) 
                     	      (lambda (a b) (< (car a) (car b)))))
       	  (set! time (+ time (vary gap 0.4))))
    result))

; now create two layers of harmonically generated notes

(plot :title "Arpa Harmonic"
      :style :hbox
      :fields '((start seconds) (keyn note) (dur start) (amp unit))
      (arpa-harmonic 'g1 7.0 5.0)
      (arpa-harmonic 'g1 7.0 5.0))

;
;; plot hooks. first open a new window to plot keynum points
;

(plot :title "FM Chords" :style 'points 
      :xaxis '(seconds 0 10) :yaxis 'keynum)

; next define a hook that will return fm "chords" whenever we perform
; Control-Option-Mouseclick in our window. X will get the mouse down
; horizontal value, y gets its vertical value. rat and ind values are
; extra fm ratio and index values we will associate with the hook.

(define (fmkeys x y rat ind)
  (let ((spec (fm-spectrum (hz y) 
                           (between 1.0 rat)
                           (vary ind .9)
                           )))
    (loop for k in (spectrum-keys spec :unique #t :min 20 :max 120)
          collect (list x k))))

; set the hook for the "FM Chords" plot window. hook will be called with
; X Y pi and 3 whenever we press Control-Option-Mouseclick.

(plot-hook "FM Chords" fmkeys pi 3)

; after adding some points use #f to clear the hook

(plot-hook "FM Chords" #f)






