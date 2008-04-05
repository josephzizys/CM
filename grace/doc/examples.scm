;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Creating and manipulating lists of data

;; a 10 element list
(make-list 10)

;; a list filled with zeros

(make-list 10 0)

;; a list with 10 random numbers 0-1
(make-list 10 ran)

;; a list of 10 random numbers 0-10.0
(make-list 10 ran 10.0)

;; a list of 10 integers between 60 and 90
(make-list 10 between 60 90)

;; a list of 10 pinkish values (-1 to 1)
(make-list 10 ranpink)

;; a list of 10 pinkish keys between 60 and 90
(rescale (make-list 10 ranpink) -1 1 60 90)

;; a list of 10 pinkish int keys between 60 and 90
(discrete (make-list 10 ranpink) -1 1 60 90)

;; summing 10 random numbers 0-10.0
(plus (make-list 10 ran 10.0))

;; a list of 10 random numbers quantized to .25
(quantize (make-list 10 ran 10.0) .25)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Note, key and pc

;; note quantizes to quarter tone resolution
(note 60.1)

(note 60.6)

;; note key pc and hz all accept lists of data
(note (make-list 10 between 60.0 80.0))

;; lowest octave is 00 highest is 9
(note '(0 127))

;; octave numbers are sticky in note lists
(key '(c4 d e f g a b c5 d e f g a b c6))

;; 10 pinkish notes beween 60 and 90
(note (discrete (make-list 10 ranpink) -1 1 60 90))

;; 10 pinkish pitch classes 
(pc (discrete (make-list 10 ranpink) -1 1 60 90))

;; transpose and invert work with notes, keys and pcs
(transpose '(c4 e g) 12)

(transpose 7 7)

(invert '(c4 e g))

(invert 11)

;; marix generator
(let ((row (shuffle '(0 1 2 3 4 5 6 7 8 9 10 11))))
  (loop for i in (invert row)
        collect (transpose row i)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Scales and interval cycles

(scale 16 60 2 1 2 2 1 2 2)

;; octatonic with just whole and half steps
(scale 16 60 2.04 1.12)

;; scale goes either direction
(scale 16 60 -2 -1 -2 -2 -1 -2 -2)

;; does not assume octave repetiion
(scale 16 60 2 1 2 1 1)

;; scale accepts lists of intervals
(scale 16 60 '(1 2 3))

;; can give it a boundary for wrapping
(note (scale 24 60 '(7 1 7 -1) 84))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; A markov harmonizer

;; a 1st order markov pattern generates steps between chord tones

(define mark
  (make-markov '((1 -> (1 .25) (2 2) (3 .5) (4 .4) (5 .3) (6 .1))
                 (2 -> (3 1) (4 .5) (5 .3) (6 .2))
                 (3 -> (1 .2) (2 1) (4 .5) (5 .3 (6 .2)))
                 (4 -> (1 .2) (2 1) (3 .4) (4 .3) (6 .2))
                 (5 -> (1 1) (2 1) (3 .5) (4 .5) (5 .5) (6 .5))
                 (6 -> (1 1) (2 1) (3 .5) (4 .5) (5 .5) ))))

;; try it out 

(let ((n 5))
  (note (scale n 60 (next mark (- n 1)))))

;; define a player for chords

(define (playchord ch d a)
  (loop for c in ch
        do (send "mp:midi" key: c dur: d amp: a)))

;; try out the player

(let ((n 5))
  (playchord (scale n 60 (next mark (- n 1)) 1 .7)))

;; define a midi hook. The louder the note the more chord tones are
;; added

(define (chordhook mm)
  (if (mm:on? mm)
    ;; interp returns a float
    (let ((n (int (interp (mm:vel mm) 20 2 100 6))))
      ;; the louder we play the more notes are added
      (playchord (scale n (mm:key mm)
                        (next mark (- n 1)))
                 .5
                 (mm:vel mm)))))

;; Set the inhook. First make sure to turn off active senseing on the
;; Midi In port!

(send "mp:inhook" chordhook)

;; clear the hook when you are done

(send "mp:inhook" #f)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Musical proceses 
;;

(define-process (pinkscale len scale)
  (run repeat len
       do
       (send "mp:midi" key: (discrete (ranpink) -1 1 scale))
       (wait .125)))

(define dorian (scale 50 20 2 1 2 2 2 1 2))

(sprout (pinkscale 60 dorian))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Using ids to selectively stop processes 
;;

(define-process (chopin n r d k)
  (run repeat n
       do
       (send "mp:midi" dur: d key: k)
       (wait r)))

;; sprout D# minor chord with ids

(begin 
  (sprout (chopin 100 .5 .25 63) 0 1)
  (sprout (chopin 100 .5 .25 66) 0 2)
  (sprout (chopin 100 .5 .25 70) 0 3)
  (sprout (chopin 100 .5 .25 75) 0 1)
  )

;; first stop F#, then A# then the D# octave

(stop 2)
(stop 3)
(stop 1)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Pentatonic wind chimes with amp envelope and exponential decay
;;

(define-process (chimes n)
  (run with l = '(0 2 5 7 9 12)
       and k = (+ 37 (* 12 (ran 5)))
       for i below n
       do
       (send "mp:midi" 0 (between 2.0 4.0)
             (+ k (nth l (ran 6)))
             (interp i 0 90 n 30))
       (wait (rescale i 0 n .1 (between 1.5 2.0) 50))))

(sprout (chimes 20 ) )

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Triggering real-time processes via a MIDI input hook
;;

;; define a process thats plays a major or minor scale based on a
;; given key

(define-process (playscale key dur)
  (let* ((scl (if (odds .5)
                (scale 15 key 2 2 1 2 2 2 1)
                (scale 17 key 2 1 )))
         (len (length scl)))
    (run for i below len
         do
         (send "mp:midi" key: (nth scl i) 
               dur: .5 amp: (interp i 0 .9 len .5))
         (wait (/ dur len)))))

;; test the process
  
(sprout (playscale 60 1.2))

;; define a hook to play a scale based on a key you press...

(define (myhook m)
  (if (mm:on? m )
    (let ((k (mm:key m)))
      (sprout (playscale k 1.2)))))

;; set hook ...

(send "mp:inhook" myhook)

;; now play your MIDI keyboard ...  then clear your hook when done

(send "mp:inhook" #f)

;; test the process
  
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Sending to the Csound port
;;

;; To run this example your Ports menu must have a Csound port
;; available and you must have Csound 5 installed on your machine. The
;; i1 instrument used here is defined in "grace.orc" in the
;; application resource directory. To run the example first use the
;; Ports>Csound>Open... menu item to open the Csound port with the
;; default orchestra file ("grace.orc") selected in the dialog box.

(define-process (rani1 len rhy lb ub amp)
  (run repeat len
       for dur = (* rhy 2)
       for k = lb then (between lb ub)
       do
       (send "cs:i" 1 0 dur key amp)
       (wait rhy)))

(sprout (rani1 10 .2 60 72 1000))

