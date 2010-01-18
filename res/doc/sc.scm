;; This example assumes you have "wavesc.rtf" open and running inside
;; SuperCollider. If not, use "Audio>Export Instruments..." to restore
;; the file, open it in SC, choose Select All and then hit the Enter
;; key (NOT the Return key...). Once you see a 'running' status in
;; SC's localhost server window you can start evalling these examples.

;; First open the OSC port to communicate with the running
;; SuperCollider app

(osc:open 57121 57110)

;; load a simple sinewave instrument from the embedded distribution:

(load "wavesc.scm")

;; try it out:

(sc:wave 0 1 440 .1)

(sc:wave 0 .5 (between 220 440) .2 :ampenv '(0 1 15 .5 50 .1 100 0))

;; send waves in the future:

(loop for x from 0 to 4 by .2 
      for g =  (pick .5 2 1.5 .666 1.059 .943)
      do
      (sc:wave x .2 (between 220 440) .1 :ampenv '(0 1 .3 15 100 0)
               :skew (list 0 1 80 g 100 g)))

;; try a process

(define (gong num dur freq amp deg )
  (process repeat num
           for frq = (between freq (* freq 3))
           do
           (sc:wave 0 dur frq amp
                    :ampenv '(0 0 1 1 10 .5 40 .2 100 0)
                    :degree deg)))

(sprout (gong 2 2 440 .1 45 ))

(sprout (gong 8 2 440 .1 45 ))

;; try a process that sprouts gongs

(define (gongalong num rate dur freqenv)
  (process for i below num
           do (sprout (gong (pick 2 3) dur (interp (/ i num) freqenv)
                            .05
                            (between 10 81)))
           (wait rate)))

(sprout (gongalong 20 .5 2 '(0 440 1 300)))

;; if you have a midi keyboard hooked up you can play gongs:

(define (midigong msg)
  (let ((frq (hz (second msg)))
        (amp (rescale (third msg) 0 127 0.01 .75))
        (dur (pick .5 1 1.5)))
    (loop repeat (between 3 9)
          for f = (between frq (* frq 3))
          do
          (sc:wave 0 dur f amp
                   :ampenv '(0 0 1 1 10 .5 40 .2 100 0)))))

;; start receiving note on messages from your Audio>MidiIn device.

(mp:receive mm:on midigong)

;; stop receiving...

(mp:receive ) 

