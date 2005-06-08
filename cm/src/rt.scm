;(load "/Users/toddingalls/Development/cm/06-08-05/cm/src/cm.scm")


(define-method* (rt-now (io <sc-stream>))
  0)

;; (define-method* (rt-now (io <midi-port>))
;;   (ms:MidiGetTime))
                        

(define (now . args)
  (with-args (args &optional abs-time)
    (if *queue*
      (if (not abs-time)
        (- *qtime* *qstart*)
        *qtime*)
      (if *out*
          (rt-now *out*)))))

(define-method* (rt-wait delta (io <sc-stream>))
  (let ((start (time->seconds (current-time))))
    (thread-sleep! (seconds->time (+ delta start)))))


;;;should there be an rt-wait for midi?



(define (wait delta)
  (if *queue*
      (set! *qnext* (+ *qnext* (abs delta)))
    (if *out*
        (rt-wait delta *out*))))

(define (wait-until time)
  (if *queue*
      (set! *qnext* (+ *qstart* time))
    (if *out*
        (rt-wait delta *out*))))


(define-method* (rt-output event (out <sc-stream>) . args)
  args
  (write-event event out (slot-ref event 'time))
  (values))

;; (define-method* (rt-output ev (out <midi-port> . args))
;;   out
;;   (with-args (args &optional ahead)
;;     (if ahead
;;       (ms:MidiSendAt *mp* ev (+ ahead (ms:MidiGetTime)))
;;       (ms:MidiSendIm *mp* ev))
;;     (values))


(define (output event . args)
  (with-args (args &optional out)
    (if *queue*
      (let ((sav *out*))
        (if out (set! *out* out))
        (if (pair? event)
          (dolist (e event)
            (let ((n (+ *qstart* (object-time e))))
              (if (early? n)
                (enqueue e n #f)
                (funcall *handler* e n))))
          (let ((n (+ *qstart* (object-time event))))
            (if (early? n)
              (enqueue event n #f)
              (funcall *handler* event n))))
        (set! *out* sav) 
        (values))
      (if out
          (rt-output event out)
        (if *out*
            (rt-output event *out*))))
    (values)))

(define (schedule-ahead thunk ahead)
  (let ((thread (make-thread
                 (lambda ()
                   (begin
                     (thread-sleep! thunk)
                     (funcall thunk))))))
    (thread-start! thread)))

(define-method* (rt-sprout (obj <object>) ahead (out <sc-stream>))
  (if (and ahead (not (= ahead 0)))
      (schedule-ahead (output obj out) time)
    (output obj out)))


(define-method* (sprout (obj <object>) . args)
  (with-args (args &optional time out)
    time
    (if *queue*
        (schedule-object obj *qstart*)
      (if out
          (if (> time 0)
              (rt-sprout obj time out)
            (output obj out))
        (if *out*
            (if (> time 0)
                (rt-sprout obj time *out*)
              (output obj *out*)))))))

(define-method* (rt-sprout (obj <procedure>) ahead (out <sc-stream>))
  (set! *out* out)
  (let ((proc (make-thread
               (lambda ()
                 (if (and ahead (not (= ahead 0)))
                     (thread-sleep! ahead))
                 (do ((i 0))
                     ((not (funcall obj))))))))
    (thread-start! proc))
  (values))

(define-method* (sprout (obj <procedure>) . args)
  (with-args (args &optional time out)
    (if *queue*
        (enqueue obj (+ *qstart* time) (+ *qstart* time))
      (if out
          (rt-sprout obj time out)
        (if *out*
            (rt-sprout obj time *out*))))))

(define-method* (sprout (obj <pair>) . args)
  (with-args (args &optional time out)
    time
    (if *queue*
      (dolist (o obj) (sprout o time))
      (if out
          (dolist (o obj) (sprout o time out))
        (if *out*
            (dolist (o obj) (sprout o time *out*)))))))


(define (rt-events object to . args)
  (let ((ahead (if (and (pair? args)
			(or (pair? (car args))
			    (number? (car args))))
                 (pop args)
                 0))
        (err? ':error))
    (when (odd? (length args))
      (err "Uneven initialization list: ~s." args))
    (when to
      (set! *out* (open-io (apply (function init-io) to args)
                           ':output))
      (initialize-io *out*))
    (if ahead
        (if (list? ahead)
            (dolist (obj object)
              (sprout obj (pop ahead) *out*))
          (sprout object ahead)))
    *out*))


;;;;;;
;;;;; examples
;;;;;


;; first fire up SuperCollider.app and boot the localhost server

;;;next use (sc-open) to open connection. it defaults to connecting to "127.0.0.1" and port 57110 which is the
;;;default SC connection

(sc-open)

;;is sc open
(sc-open?)

;;; (dump-osc #t) will turn on printing in the SC window showing what events have been received. (dump-osc #f) turns this off

(dump-osc #t)

;;;this is a simple example

(defobject simple (scsynth)
  ((freq :initform 440)
   (dur :initform 1)
   (amp :initform .2)
   (pan :initform 0))
  (:parameters freq dur amp pan time))


(define (sc-simple-6 num)
  (process repeat num
	   output (new simple :time (now)
		       :freq (between 200 700)
		       :dur (between 7 10)
		       :amp .1
		       :pan (pickl '(-1.0 0 1.0)))
           wait 3))


;;;
;;; it is possible to use sprout to run the cm process. the default out is the sc connection created by (sc-open)
;;;

(sprout (sc-simple-6 3))

;;;
;;; (rt-events) can also be used. similar to (events...)
;;;

(rt-events (sc-simple-6 10) "sc.udp")

;;;
;;; rt-events can also be used to schedule cm processes for a future time.
;;;

(rt-events (list (sc-simple-6 3) (sc-simple-6 3)) "sc.udp" '(1 20) )


;;;
;;; there are two ways to think about scheduling events. one way uses cm
;;; the other uses sc to schedule events by making the time of the 
;;; event something other that (now)

;;;here is an example using cm to schedule some grains

(define (grain-notes1 center num)
  (process repeat num for i from 0
           output (new simple :time (now)
                       :freq (between (- (hertz center)  50) (+ (hertz center)  50))
                       :dur 1
                       :amp .03)
           wait .01))

(rt-events (list (grain-notes1 70 30)
                 (grain-notes1 65 30)
                 (grain-notes1 72 30)) "sc.udp" '(0 4 8))

;;;here is a second way based on the sc server scheduling events
;;; this could be particularly important if many events are happening
;;; in a small time span.

(define (grain-notes2 center num)
  (process repeat num for i from 0
           output (new simple :time (+ (now) (* .01 (/ i num)))
                       :freq (between (- (hertz center)  50) (+ (hertz center)  50))
                       :dur 1
                       :amp .03)))

(rt-events (list (grain-notes2 70 30)
                 (grain-notes2 65 30)
                 (grain-notes2 72 30)) "sc.udp" '(0 4 8))

;;;here is another example

(define (arps1 num)
  (process repeat num
           with base = 60
           sprout (process repeat 7
                           with arp = (new cycle :of '(0 4 7 12 7 4 0))
                           output (new simple :freq (hertz (+ base (next arp)))
                                       :dur .25
                                       :amp .4
                                       :time (now))
                           wait .15)
           set base = (between 50 70)
           wait 1))
           
(rt-events (arps1 10) "sc.udp")

(define (arps2 num)
  (process repeat num
           with base = 60
           sprout (process repeat 7 for j from 0
                           with arp = (new cycle :of '(0 4 7 12 7 4 0))
                           output (new simple :freq (hertz (+ base (next arp)))
                                       :dur .25
                                       :amp .4
                                       :time (+ (now) (* 1.05 (/ j 7)))))
           set base = (between 50 70)
           wait 1))

(rt-events (arps2 10) "sc.udp")


;;; (sc-flush) can be used to clear the sc server scheduler and also free all nodes

(sc-flush)


;;; all the examples in sc.cm seem to be running properly in realtime.
;;; just use rt-events instead of events

(rt-events (sc-simple-1 10) "sc.udp")

(rt-events (sc-fm-2 10) "sc.udp")

(rt-events (random-play-no-loop  10) "sc.udp")

(rt-events (granure 5) "sc.udp")

(rt-events (wt2 10) "sc.udp")

;;; turn of printing of messages in SC
(dump-sc #f)

;;; close sc.udp
(sc-close)
