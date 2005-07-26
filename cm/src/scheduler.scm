;;; **********************************************************************
;;; 
;;; Copyright (C) 2002 Heinrich Taube (taube@uiuc.edu) 
;;; 
;;; This program is free software; you can redistribute it and/or
;;; modify it under the terms of the GNU General Public License
;;; as published by the Free Software Foundation; either version 2
;;; of the License, or (at your option) any later version.
;;; 
;;; This program is distributed in the hope that it will be useful,
;;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;;; GNU General Public License for more details.
;;; 
;;; **********************************************************************

;;; $Name$
;;; $Revision$
;;; $Date$

;;; a queue entry consists of three cons cells: 
;;;           (<time> <start> <object> . <next>)
;;; <time> is the current process (score) time of <object>, if <object>
;;; is a container, then <start> is the container's local time offset
;;; converted to absolute score time. if <object> is an event then <start>
;;; is nil. this means that a queue entry with a null <start> must be an
;;; event and is never reenqueued once it is popped from the queue. 

(define-macro (%qe-time qe)
  ;; clocktime of entry
  `(car ,qe))

(define-macro (%qe-time-set! qe time)
  `(set-car! ,qe ,time))

(define-macro (%qe-start qe)
  ;; initial time of entry for container, #f for events.
  `(cadr ,qe))

(define-macro (%qe-start-set! qe start)
  ;; initial time of entry for container, #f for events.
  `(set-car! (cdr ,qe) ,start))

(define-macro (%qe-object qe)
  ;; the datum
  `(caddr ,qe))

(define-macro (%qe-object-set! qe obj)
  `(set-car! (cddr ,qe) ,obj))

(define-macro (%qe-next qe)
  ;; pointer to next entry
  `(cdddr ,qe))

(define-macro (%qe-next-set! qe nxt)
  `(set-cdr! (cddr ,qe) ,nxt))

;;;
;;; the system queue is simply a cycl. the active queue is the
;;; cycl's tail; queue entries are resourced in the cycl's data.
;;;

(define-macro (%q-head q)
  `(cycl-tail ,q))

(define-macro (%q-head-set! q e)
  `(cycl-tail-set! ,q ,e))

(define-macro (%q-last q)
  `(cycl-last ,q))

(define-macro (%q-last-set! q e)
  `(cycl-last-set! ,q ,e))

(define-macro (%q-peek q)
  `(%q-head ,q))

(define-macro (%q-empty? q)
  `(null? (%q-head ,q)))

(define-macro (%q-pop queue)
  (let ((q (gensym))
	(e (gensym)))
    `(let* ((,q ,queue)
	    (,e (%q-head ,q)))
      (if (null? ,e)
	'()
	(begin
	 (%q-head-set! ,q (%qe-next ,e))
	 (%qe-next-set! ,e '())
	 (if (null? (%q-head ,q))
	   (%q-last-set! ,q '()))
	 ,e)))))

(define-macro (%qe-alloc queue time start object )
  (let ((q (gensym))
	(e (gensym)))
    `(let* ((,q ,queue)
	    (,e (cycl-data ,q)))
      (if (null? ,e)
	(list ,time ,start ,object)
	(begin
	 (cycl-data-set! ,q (%qe-next (cycl-data ,q)))
	 (%qe-next-set! ,e '())
	 (%qe-time-set! ,e ,time)
	 (%qe-start-set! ,e ,start)
	 (%qe-object-set! ,e ,object)
         ,e)))))
               
(define-macro (%qe-dealloc queue entry)
  (let ((q (gensym))
	(e (gensym)))
    `(let ((,q ,queue)
	   (,e ,entry))
      (%qe-time-set! ,e #f)
      (%qe-start-set! ,e #f)
      (%qe-object-set! ,e #f)
      (%qe-next-set! ,e (cycl-data ,q))
      (cycl-data-set! ,q ,e)
      (values))))

(define %q (make-cycl))

;;; initialize queue with 50 entries
(dotimes (i 50) (%qe-dealloc %q (list #f #f #f)))

(define-macro (%q-insert entry queue)
  (let ((q (gensym))
	(e (gensym))
	(h (gensym))
	(l (gensym)))
    `(let ((,q ,queue)
	   (,e ,entry))
      ;(format t "~%inserting ~S" ,e)
      (if (null? (%q-head ,q))
	(begin
	 (%q-head-set! ,q ,e)
	 (%q-last-set! ,q ,e))
	(if (< (%qe-time ,e)
	       (%qe-time (%q-head ,q)) )
	  (begin 
	   ;; prepend to queue
	   (%qe-next-set! ,e (%q-head ,q))
	   (%q-head-set! ,q ,e))
	  (if (< (%qe-time ,e)
		 (%qe-time (%q-last ,q)))
	    ;; insert in queue
	    (do ((,h (%q-head ,q))	; could be next one
		 (,l '()))
		((or (null? ,h)
		     (> (%qe-time ,h) (%qe-time ,e)))
		 (%qe-next-set! ,e (%qe-next ,l))
		 (%qe-next-set! ,l ,e))
	      (set! ,l ,h)
	      (set! ,h (%qe-next ,h)))
	    (begin
	     ;; append to queue
	     (%qe-next-set! (%q-last ,q) ,e)
	     (%q-last-set! ,q ,e)
	     )))))))

(define (pq . args)
  (let* ((q (if (null? args) %q (car args)))
	 (h (%q-head q))
	 (z most-negative-fixnum))
    (format #t "~s entries:~%" (/ (length (%q-head q)) 3))
    (loop for i from 0 
          until (null?  h)
          do 
	  (if (> z (car h))
	    (err "Out of order: ~s ~s ~s" z (car h) (%q-head q)))
	  (set! z (car h))
          (format #t "~s. (~s ~s ~s)" 
                  i (car h) (cadr h) (caddr h))
	  (newline)
          (set! h (%qe-next h)))))

(define (%q-flush q)
  (loop for e = (%q-pop q) until (null? e) do (%qe-dealloc q e)))


;(loop repeat 50
;  do (let ((qe (%qe-alloc %q (random 100) '- '*)))
;      (%q-insert qe %q)))
;(pq)
;(%q-pop %q)
;(pq)
;(%q-pop %q)
;(%q-flush %q)

;(define %q (make-cycl))
;(dotimes (i 50) (%qe-dealloc %q (list #f #f #f))))

;(define (testq n)
;(dotimes (i n)
;  (let ((r (1+ (random 49))))
;    (dotimes (j r)
;      (%q-insert (%qe-alloc %q (random 1000) ':a ':z)  %q ))
;    (let* ((l (%q-head %q))
;	   (h (%qe-next l)))
;      (do ()
;	  ((null? h) #f)
;	(unless (<= (%qe-time l) (%qe-time h))
;	  (format #t "Entries out of order: ~s ~s"
;		  (%qe-time l) (%qe-time h) )
;	  (newline))
;	(set! l h)
;	(set! h (%qe-next h))))
;    (dotimes (j r) (%qe-dealloc %q (%q-pop %q ))))))

;(testq 50)

;;;
;;; The scheduling loop. Calls schedule-object on whatever is passed
;;; in and loops until the queue is empty.  Most of the work is done
;;; by process-events, which is called on each entry as it is popped.
;;;

(define *queue* #f) ; system queue
(define *scheduler* #f)
(define *pstart* #f) ; start time of process in score or 0
(define *qtime* #f)  ; current run time (score time)
(define *qnext* #f)  ; next runttime
(define *qlock* #f)  ; lock for threaded scheduler

(define (schedule-events stream object . args)
  ;; removed rt
  (let* ((ahead (if (pair? args) (car args) 0))
	 (noerr #f)
	 (entry #f)
         (start #f)
	 (thing #f))
    (set! *queue* %q)
    (set! *scheduler* ':asap)
    ;; enque all objects at their score times
    ;; object and ahead can be a single values or lists
    (if (pair? object)
      (dolist (o object)
	;; allow fewer aheads than objects. last one is sticky.
	(schedule-object o (if (pair? ahead)
			     (if (pair? (cdr ahead))
			       (pop ahead) (car ahead))
			     ahead)))
      (if (pair? ahead)
        (schedule-object object (car ahead))
        (schedule-object object ahead)))
    (dynamic-wind
     (lambda () #f)
     (lambda ()
       (do ()
	   ((null? (%q-head *queue*))
	    (set! noerr #t))
	 (set! entry (%q-pop *queue*))
	 (set! *qtime* (%qe-time entry))
	 (set! start (%qe-start entry))
	 (set! thing (%qe-object entry))
	 (%qe-dealloc *queue* entry)
	 (process-events thing *qtime* start stream)
	 ))
     (lambda ()
       (unless noerr
	 ;; if we got an error flush remaining queue entries.
	 ;(warning "Flushing queue.")
	 (%q-flush *queue*)
	 (unschedule-object object #t))
       ;; toplevel #f for interactive midi.
       (set! *scheduler* #f)
       (set! *pstart* #f)
       (set! *qtime* #f)
       (set! *qlock* #f)
       (set! *queue* #f)))))

(define (enqueue object time start)
  ;; start is #f if object is not a container
  (%q-insert (%qe-alloc *queue* time start object) *queue*))

(define (early? tim)
  ;; #t if time is later than next entry in queue.
  (if (null? (%q-head *queue*)) #f
      (> tim (%qe-time (%q-head *queue*)))))

;;;
;;; schedule-object inserts object into queue
;;;

(define-method* (schedule-object (obj <object>) start)
  ;; this was defined for EVENT. now works on any
  ;; object that has an object-time accessor.
  ;; start is the score time of the parent container
  (enqueue obj (+ start (object-time obj)) #f))

;(define-method* (schedule-object (obj <process>) start)
;  (let ((mystart (+ start (object-time obj)))
;	;; call closure to produce process funcs
;        (procs ( (process-closure obj)
;		 (process-args obj))))
;    (if (pair? procs)
;      (dolist (p procs)
;        (enqueue p mystart mystart))
;      (enqueue procs mystart mystart))))

(define-method* (schedule-object (obj <procedure>) start)
  (enqueue obj start start))

(define-method* (schedule-object (obj <integer>) start)
  (enqueue obj start start))

(define-method* (schedule-object (obj <pair>) start)
  ;; THIS IS WRONG. IT SHOULD RECURSE
  (dolist (o obj) (enqueue o start start)))

(define-method* (schedule-object (obj <seq>) start)
  ;; start is the score time of the parent container
  ;; the seq enqueues its list of subobjects thus
  ;; allowing multiple enqueues of the same seq.
  (let ((mystart (+ start (object-time obj))))
    (enqueue (container-subobjects obj)
	     mystart mystart)
    ;; schedule all subcontainers of seq
    (dolist (sub (subcontainers obj))
      (schedule-object sub mystart))))
;;;
;;; unschedule-object, currently a noop.
;;;

(define-method* (unschedule-object obj . recurse)
  obj recurse ; gag 'unused var' warning from cltl compilers
  #f)

;;;
;;; process-events
;;;

(define-method* (process-events obj time start stream)
  ;; call the function on the time and start
  start ; gag 'unused var' warning from cltl compilers
  (write-event obj stream time))

(define-method* (process-events (head <pair>) time start stream)
  time   ; gag 'unused var' warning from cltl compilers
  (let ((event #f)
        (next #f))
    ;; get the next non-container in the list. this is not
    ;; the same as the original which explicitly looked 
    ;; for the event class:
    (do ()
	((or event (null? head)) #f)
      (set! next (pop head))
      (unless (is-a? next <container>)
	(set! event next)))
    (if event
      (begin
       ;; event's score time = seq_start + event_time
       (set! next (+ start (object-time event)))
       (if (early? next) 
	 (enqueue event next start)
	 (write-event event stream next))
       (if (null? head)
	 #f
	 (enqueue head next start)))
      #f)))


;(set! *print-object-terse* #t)
;
;(define-method* (write-event (e <midi>) io time)
;  (write (list 'hiho time  e))
;  (newline))
;
;(schedule-events (lambda (ev st) (write-event ev #t st))
;		 (loop for i below 5
;		       collect (new midi time i))
;		 10)
;----------------------------------------------------
;(new seq name 'foo
;     time 0
;     subobjects (loop for i below 10 
;		      collect (new midi time i)))
;(schedule-events (lambda (ev st) (write (list ev st)) (newline))
;		 (list #$foo #$foo)
;		 '(100 100.5))

;;;
;;; process functions need to access the current queue time,
;;; the queue start and the hander function.  for now i am using
;;; specials to avoid codewaking. the alternative would be to pass
;;; everything as parameters to the process function and then
;;; walk the code rewriting "special forms" like WAIT, etc, in terms
;;; of lexically scoped variables. but this requires at a minimum
;;; an implementation of MACROEXPAND-ALL (walk.lisp). 
;;;

(define-method* (process-events (func <procedure>) qtime pstart stream)
  stream
  ;; scoretime process originally started at only valid during funcall
  (set! *pstart* pstart)
  ;; *qnext* is advanced by (wait ...)
  (set! *qnext* qtime)
  ;; reschedule if process function returns non-nil
  (if (funcall func) (enqueue func *qnext* *pstart*))
  (set! *pstart* #f))

(define (output event . args)
  ;; used in processes to write events to the current output stream.
  ;; checks to see if event's time is in future later than next event
  ;; in queue. if so it enqueues rather than outputs. if event is
  ;; written to file, ahead is added to scoretime stream's destination
  ;; can manage future scheduling
  (with-args (args &key (to *out*) at (ahead 0))
    (if *scheduler*
        (begin
         (if (pair? event)
             (dolist (e event)
               ;; if called from process at relative to process start
               ;; time
               (let ((n (+ (or *pstart* 0) (or at (object-time e)))))
                 (if (early? n)
                     (enqueue e n #f)
                     (write-event e to (+ n ahead)))))
             (let ((n (+ (or *pstart* 0) (or at (object-time event)))))
               (if (early? n)
                   (enqueue event n #f)
                   (write-event event to (+ n ahead))))))
        (write-event event to (+ (or at 0) ahead)))
    (values)))

(define (now . args)
  ;; now can only be called from (process ) or from the repl
  (with-args (args &optional abs-time)
    ;; *pstart* will be #f if called outside process
    (if *scheduler*
      (if (not abs-time)
        (- *qtime* (or *pstart* 0))
        *qtime*)
      (err "now: scheduler not running."))))

(define (wait delta)
  ;; should this check *pstart* ??
  (if *scheduler*
      (set! *qnext* (+ *qnext* (abs delta)))
      (err "wait: scheduler not running.")))

;; (define-method* (sprout (obj <object>) . args)
;;   (with-args (args &optional time ahead)
;;     ahead
;;     (if *scheduler*
;;         (schedule-object obj *qstart*)
;;         (err "sprout: scheduler not running."))))
;; (define-method* (sprout (obj <procedure>) . args)
;;   (with-args (args &optional time ahead)
;;     ahead
;;     (if *scheduler*
;;         (enqueue obj (+ *qstart* time) (+ *qstart* time))
;;         (err "sprout: scheduler not running."))))
;; (define-method* (sprout (obj <pair>) . args)
;;   (with-args (args &optional time ahead)
;;     (if *scheduler*
;;       (dolist (o obj) (sprout o time ahead))
;;       (err "sprout: scheduler not running."))))

(define (sprout obj . args)
  (with-args (args &key to at ahead)
    to
    (if *scheduler*
        (let ((tt (if at
                      (if *pstart*
                          (+ at *pstart*)
                          at)
                      (now))))
          ;; tt is true time to insert in queue. if sprouting from a
          ;; process then at value is relative to process start time
          ;; *pstart*. else sprout is being called from the repl, time
          ;; is relative to 0.
          (if ahead (set! tt (+ tt ahead)))
          ;; im not sure if i need a locking mechanism here or not. rts
          ;; wraps a without-interrupts around the points where its
          ;; thread accesses the queue, maybe that would keep this code
          ;; from simultaneous side-effecting the queue from another
          ;; process
          (if (eq? *scheduler* ':threaded) (mutex-lock! *qlock*))
          (cond ((pair? obj)
                 (dolist (o obj) (sprout o at ahead)))
                ((procedure? obj)       ; process
                 ;; add sprouted process at time relative to start of
                 ;; sprouter
                 (enqueue obj tt tt) )
                ((integer? obj)         ; midi message
                 ;; add midi message relatice to true scoretime
                 (enqueue obj tt #f) )
                (else                   ; object
                 ;; else the object has a method on object-time and
                 ;; schedule-object will enqueue at object-time PLUS
                 ;; start time of process that sprouted it
                 (schedule-object obj (or *pstart* 0))))
          (if (eq? *scheduler* ':threaded) (mutex-unlock! *qlock*)))
        (err "sprout: scheduler not running."))
    (values)))

;;;
;;; real time scheduling (rts)
;;;

(define *rts-type* #f) ; see also *receive-type*

(cond-expand
 (cmu (set! *rts-type* ':periodic))
 (sbcl (set! *rts-type* ':periodic))
 (gauche (set! *rts-type* ':threaded))
 (openmcl (set! *rts-type* ':threaded))
 (else #f))

(define *rts-run* #f)
(define *rts-idle-rate* .001) ; time out slice if no pending events

(define (rts-reset) 
  ;; call this after an error
  (when (and *queue* (not (null? (%q-head *queue*))))
    (%q-flush *queue*))
  (set! *queue* #f)
  (set! *scheduler* #f)
  (set! *rts-run* #f)
  (set! *pstart* #f)
  (set! *qnext* #f)
  (set! *qtime* #f))

(define (rts? )
  *rts-run*)

(define (rts-stop) 
  (set! *rts-run* #f)
  (values))

(define (rts-pause )
  (err "rts-pause: not implemented."))

(define (rts-continue )
  (err "rts-continue: not implemented."))

(define (rts . args)
  (if (rts?) 
      (err "rts: scheduler already running or (rts-reset) was not called after error."))
  (let* ((object (if (pair? args) (pop args) #f)) ; object(s) to run
         (to (if (pair? args) (pop args)          ; output stream
                 (current-output-stream)))   
         (ahead (if (pair? args) (or (pop args) 0) 0)) ; start time offset
         (end (if (pair? args) (pop args) 
                  (if object #t #f))))
    (if (and (not object) (or (pair? ahead ) (> ahead 0)))
        (err "rts: ahead must be 0 when starting rts without objects."))
    (set! *queue* %q)
    (if (pair? object)
        (dolist (o object)
          (schedule-object o
                           (if (pair? ahead)
                               (if (pair? (cdr ahead))
                                   (pop ahead)
                                   (car ahead))
                               ahead)))
        (if (pair? ahead)
            (schedule-object object (car ahead))
            (if object
                (schedule-object object ahead))))
    ;; not sure about this
    (if (pair? ahead) (set! ahead (apply (function min) ahead)))
    (set! *out* to)
    (set! *rts-run* #t)
    (set! *qtime* ahead)
    (case *rts-type*
      (( :threaded )
       (if (not *qlock*) (set! *qlock* (make-mutex)))
       (set! *scheduler* ':threaded)
       (thread-start!
        (make-thread (rts-run-threaded object ahead end))))
      (( :periodic )
       (set! *scheduler* ':periodic)
       (set-periodic-task-rate! 1 :ms)
       (add-periodic-task! :rts (rts-run-periodic object ahead end)))
      (else (err "rts: not an rts scheduling type: ~s" *rts-type*)))
    (values)))

(define (rts-run-threaded object ahead end)
  ;; rts threaded run function. attempts to be adaptive to
  ;; fluctuations using a target time (ttime) to calculate sleep time
  ahead ; same as *qtime* 
  (lambda ()
    (if (> *qtime* 0) 
        (thread-sleep! *qtime*))
    (do ((ttime (thread-current-time))
         (entry #f)
         (thing #f)
         (start #f)
         (wait? #f))
        ((or (not *rts-run*)
             (if (eq? end #t) (%q-empty? *queue*)
                 (if (eq? end #f) #f
                     (or (%q-empty? *queue*) 
                         (> (%qe-time (%q-peek *queue*)) 
                            end)))))
         (if object (unschedule-object object #t))
         (rts-reset))
      (mutex-lock! *qlock*)
      (without-interrupts
          (do ()
              ((or (%q-empty? *queue*)
                   (> (%qe-time (%q-peek *queue*)) *qtime*))
               (if (%q-empty? *queue*)
                   (set! wait? #f)
                   (let* ((next (%qe-time (%q-peek *queue*))))
                     (set! wait? (- next *qtime*))
                     ;; not sure if this should really be
                     ;; incremented here. maybe the time shouldnt be
                     ;; advanced until after the sleep??
                     (set! *qtime* next))))
            (set! entry (%q-pop *queue*))
            (set! *qtime* (%qe-time entry))
            (set! start (%qe-start entry))
            (set! thing (%qe-object entry))
            (%qe-dealloc *queue* entry)
            (process-events thing *qtime* start *out*)))
      (mutex-unlock! *qlock*)
      (if wait? 
          (begin 
           (setf ttime (+ ttime wait?))
           (thread-sleep!
            (- ttime (thread-current-time))))
          ;; we only get here if queue is currently empty but user
          ;; wants scheduler to keepp running even though it has
          ;; nothing to do.  in this case the do loop will spin
          ;; without sleeping and cpu% goes through the roof. so the
          ;; scheduler either needs to block until queue has something
          ;; in it or else "yeild" somehow. I think blocking is the
          ;; right way to do this but i dont understand how to
          ;; implement this using mcl's locking mechanism.  similarly
          ;; openmcl's process-allow-scheduling doesnt seem to work
          ;; for yielding so we just sleep a tiny amount.
          (if (not end)
              (begin (thread-sleep! *rts-idle-rate*)
                     (set! ttime (thread-current-time))))))))

(define (rts-run-periodic object ahead end)
  ;; rts periodic run function.  the only hope for this method is if
  ;; the host's periodic polling at 1ms rate is rock-solid and all
  ;; tasks (including any receives) complete in under 1ms...
  (let ((wait? (if (> ahead 0)
                   (inexact->exact
                    (round (* ahead 1000.0)))
                   0)))
    (lambda ()
      (if (> wait? 0)
          (set! wait? (- wait? 1)) ; periodic "sleep"...
          (let ((entry #f)
                (thing #f)
                (start #f)
                (none? (null (%q-head *queue*))))
            (cond ((or (not *rts-run*)
                       (if (eq? end #t) none?
                           (if (eq? end #f) #f
                               (if none? #t
                                   (> (%qe-time (%q-peek *queue*)) 
                                      end)))))
                   (if object (unschedule-object object #t))
                   (rts-reset)
                   (remove-periodic-task! :rts))
                  (t
                   (do ()
                       ((or none?
                            (> (%qe-time (%q-peek *queue*)) *qtime*))
                        (if none?
                            (set! wait? 0)
                            (let* ((next (%qe-time (%q-peek *queue*))))
                              (set! wait? (- next *qtime*))
                              ;; not sure if this should really be
                              ;; incremented here. maybe the time shouldnt be
                              ;; advanced until after the sleep??
                              (set! *qtime* next))))
                     (set! entry (%q-pop *queue*))
                     (set! *qtime* (%qe-time entry))
                     (set! start (%qe-start entry))
                     (set! thing (%qe-object entry))
                     (%qe-dealloc *queue* entry)
                     (process-events thing *qtime* start *out*)
                     (set! none? (null (%q-head *queue*))))
                   (or (eq? wait? 0)
                       (set! wait? (inexact->exact
                                   (round (* wait? 1000.0))))))))))))

;;;
;;; receive
;;;

(define *receive-type* #f)

(cond-expand
 (cmu (set! *receive-type* ':periodic))
 (sbcl (set! *receive-type* ':periodic))
 (gauche (set! *receive-type* ':threaded))
 (openmcl (set! *receive-type* ':periodic))
 (else #f))

(define *generic-receive* (list #f #f))
(define *generic-receive-rate .001)

(define (map-receivers fn )
  (do ((tail *periodic-tasks* (cdr tail)))
      ((null? tail)
       #f)
    (if (or (eq? (car (car tail)) ':receive)
            (is-a? (car (car tail)) <event-stream>))
        ( fn (car (car tail))))))

(define (remove-receiver! . stream)
  (map-receivers (lambda (r)
                   (cond ((and (eq? r :receive)
                               (or (null? stream)
                                   (eq? (car stream) #t)))
                          (remove-periodic-task! ':receive)
                          (list-set! *generic-receive* 0 #f))
                         ((and (or (null? stream)
                                   (eq? r (car stream)))
                               (is-a? r <event-stream>))
                          (remove-periodic-task! r)
                          (stream-stop-receiver r))
                         ((not (null? stream))
                          (err "remove-receiver!: no receiver for stream ~s."
                               (car stream))))))
  (values))

(define (receiver? . stream)
  (let ((flag #f))
    (map-receivers (lambda (r)
                     (if (or (null? stream)
                             (eq? r (car stream))
                             (and (eq? r ':receive)
                                  (eq? (car stream) #t)))
                         (set! flag #t))))
    flag))

(define (set-receiver! hook stream)
  (cond ((not *receive-type*)
         (err "set-receive!: receiving is not implemented in this Lisp/OS."))
        ((not (member *receive-type* '(:threaded :periodic)))
         (err "set-receive!: ~s is not a receive type."
              *receive-type*))
        ((eq? stream #t) ; generic receive
         (let ((wrapper (generic-receive hook *receive-type*)))
           (case *receive-type*
             (:threaded (thread-start! wrapper))
             (:periodic (add-periodic-task! :receive wrapper)))))
        (else
         (let ((wrapper (stream-receiver hook stream *receive-type*)))
           (case *receive-type*
             (:threaded (thread-start! wrapper))
             (:periodic (add-periodic-task! stream wrapper))))))
  (values))

(define (generic-receive hook type)
  (let ((data *generic-receive*)
        (stop #f))
    (cond ((not (procedure? hook))
           (err "Receive: hook is not a function: ~s" hook))
          ((first data)
           (err "Can't set input hook: another hook is running!"))
          (else
           (let ((th #f)
                 (st #f))
             (case type
               ((:threaded)
                (set! th (make-thread (lambda ()
                                        (do ()
                                            (stop #f)
                                          (hook)
                                          (thread-sleep! *generic-receive-rate)))))
                (set! st (lambda () (set! stop #t))))
               ((:periodic)
                (set! th (lambda ()
                           (hook)))
                (set! st (lambda ()
                           (remove-periodic-task! :receive)))))
           (list-set! *generic-receive* 0 th)
           (list-set! *generic-receive* 1 st)
           th)))))

(define-generic* receive)
(define-generic* stream-receiver) 
(define-generic* stream-stop-receiver) ; cleanup

(define-method* (stream-receiver hook stream type)
  hook stream type
  (err "stream-receive: ~s does not support receiving." stream))



