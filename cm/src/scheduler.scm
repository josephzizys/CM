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
           (if (< (OR (%qe-time ,e) (err "%q-insert: (a) %qe-time is nil!"

                                         ))
                  (OR (%qe-time (%q-head ,q)) (err "%q-insert: (b) %qe-time is nil!"))
                  )
               (begin 
                ;; prepend to queue
                (%qe-next-set! ,e (%q-head ,q))
                (%q-head-set! ,q ,e))
               (if (< (OR (%qe-time ,e) (err "%q-insert: (c) %qe-time is nil!"))
                      (OR (%qe-time (%q-last ,q))
                          (err "%q-insert: (d) %qe-time is nil!"))
                      )
                   ;; insert in queue
                   (do ((,h (%q-head ,q)) ; could be next one
                        (,l '()))
                       ((or (null? ,h)
                            (> (OR (%qe-time ,h)
                                   (err "%q-insert: (e) %qe-time is nil!"))
                               (OR (%qe-time ,e)
                                   (err "%q-insert: (f) %qe-time is nil!"))
                               ))
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
          ;; if threaded rts is running and we are sprouting from
          ;; outside the rts process then block until the queue is
          ;; available. *pstart* is false except in the body of a
          ;; process defintion (which is evaluated in the rts thread).
          (if (and (not *pstart*) (or (eq? *scheduler* ':threaded)
                                      (eq? *scheduler* ':specific)))
              (with-mutex-grabbed (*qlock*)
                 (cond ((pair? obj)
                        (dolist (o obj) (sprout o :at at :ahead ahead)))
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
                        (schedule-object obj (or *pstart* 0)))))
             (cond ((pair? obj)
                    (dolist (o obj) (sprout o :at at :ahead ahead)))
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
                    (schedule-object obj (or *pstart* 0))))))
          (err "sprout: scheduler not running."))
      (values)))

;;;
