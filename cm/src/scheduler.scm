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

;;;
;;; low level queue definitions for events and rts scheduling
;;;

;;; entry types,  (see rts/scheduler.h)

(define *qentry-unknown* 0)
(define *qentry-process* 1)
(define *qentry-seq*     2)
(define *qentry-object*  3)
(define *qentry-message* 4)
(define *qentry-pointer* 5)

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

(define-macro (%qe-datum qe)
  ;; the datum
  `(cadddr ,qe))

(define-macro (%qe-datum-set! qe obj)
  `(set-car! (cdddr ,qe) ,obj))

(define-macro (%qe-next qe)
  ;; pointer to next entry
  `(cddddr ,qe))

(define-macro (%qe-next-set! qe nxt)
  `(set-cdr! (cdddr ,qe) ,nxt))

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

(define-macro (%qe-alloc queue time start object type)
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
	 (%qe-datum-set! ,e ,type)
         ,e)))))
               
(define-macro (%qe-dealloc queue entry)
  (let ((q (gensym))
	(e (gensym)))
    `(let ((,q ,queue)
	   (,e ,entry))
      (%qe-time-set! ,e #f)
      (%qe-start-set! ,e #f)
      (%qe-object-set! ,e #f)
      (%qe-datum-set! ,e #f)
      (%qe-next-set! ,e (cycl-data ,q))
      (cycl-data-set! ,q ,e)
      (values))))

(define %q (make-cycl))

;;; initialize queue with 50 entries
(dotimes (i 50) (%qe-dealloc %q (list #f #f #f #f)))

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
                  (%qe-time (%q-head ,q))
                  )
               (begin 
                ;; prepend to queue
                (%qe-next-set! ,e (%q-head ,q))
                (%q-head-set! ,q ,e))
               (if (< (%qe-time ,e) 
                      (%qe-time (%q-last ,q)))
                   ;; insert in queue
                   (do ((,h (%q-head ,q)) ; could be next one
                        (,l '()))
                       ((or (null? ,h)
                            (> (%qe-time ,h) 
                               (%qe-time ,e)))
                        (%qe-next-set! ,e (%qe-next ,l))
                        (%qe-next-set! ,l ,e))
                     (set! ,l ,h)
                     (set! ,h (%qe-next ,h)))
                   (begin
                    ;; append to queue
                    (%qe-next-set! (%q-last ,q) ,e)
                    (%q-last-set! ,q ,e))))))))

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

(define (scheduling? ) *scheduler*)

(define (schedule-events stream object . args)
  ;; removed rt
  (let* ((ahead (if (pair? args) (car args) 0))
	 (noerr #f)
	 (entry #f)
         (start #f)
	 (datum #f)
	 (etype #f)
	 (thing #f)
	 )
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
	 (set! datum (%qe-datum entry) ) ; holds type info
	 (%qe-dealloc *queue* entry)
	 ;(process-events thing *qtime* start stream)
	 (set! etype (logand datum #xF))
	 (cond ((eq? etype *qentry-process*)
		(scheduler-do-process thing *qtime* start
				      stream datum))
	       ((eq? etype *qentry-seq*)
		(scheduler-do-seq thing *qtime* start
				  stream datum))
	       (else
		(write-event thing stream *qtime*)))
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

(define (enqueue type object time start)
  ;; CHANGE: enqueue now take a qentry type that is passed to rts and
  ;; ignored by events
  ;; CHANGE: enqueue now calls rts:enqueue if not running under events
  ;; start is #f if object is not a container
  (if (eq? *scheduler* ':asap)
      (%q-insert (%qe-alloc *queue* time start object type) *queue*)
      (rts:enqueue type object time start)
      ))

(define (early? tim)
  ;; #t if time is later than next entry in queue.
  ;; CHANGE: rts has no check for early
  (if (eq? *scheduler* ':asap)
      (if (null? (%q-head *queue*)) #f
	  (> tim (%qe-time (%q-head *queue*))))
      #f))

;;;
;;; schedule-object inserts object into queue
;;;

(define-method* (schedule-object (obj <object>) start)
  ;; this was defined for EVENT. now works on any
  ;; object that has an object-time accessor.
  ;; start is the score time of the parent container
  (enqueue *qentry-object* obj (+ start (object-time obj)) #f))

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
  (enqueue *qentry-process* obj start start))

(define-method* (schedule-object (obj <integer>) start)
  (enqueue *qentry-message* obj start start))

(define-method* (schedule-object (obj <pair>) start)
  ;; CHANGE: this now calls its self recursivly as it should
  (dolist (o obj) (schedule-object o start start)))

(define-method* (schedule-object (obj <seq>) start)
  ;; CHANGE: this conses seq onto head of subobjects
  ;; so list can maintain identity during scheduling
  ;; start is the score time of the parent container
  ;; the seq enqueues its list of subobjects thus
  ;; allowing multiple enqueues of the same seq.
  (let ((mystart (+ start (object-time obj))))
    (enqueue *qentry-seq*
	     ;; we add the seq onto the subobjects so that
	     ;; the entries maintain their identity during scheduling
	     (cons obj (container-subobjects obj))
	     mystart mystart)
    ;; schedule all subcontainers of seq
    (dolist (sub (subcontainers obj))
      (schedule-object sub mystart))))
;;;
;;; unschedule-object, currently a noop.
;;;

(define-method* (unschedule-object obj . recurse)
  obj recurse
  #f)

;;;
;;; processing queue entries
;;;

(define (scheduler-do-seq entry time start stream type)
  ;; the entry is (<seq> . subs).
  ;;type has *qentry-seq* in the nibble
  time
  (let ((head (cdr entry))
	(event #f)
        (next #f))
    ;; get the next non-container in the list. this is not
    ;; the same as the original which explicitly looked 
    ;; for the event class:
    (do ()
	((or event (null? head)) #f)
      (set! next (pop head))
      (unless (is-a? next <container>)
	(set! event next)))
    ;; cdr entry may be nil now
    (set-cdr! entry head)
    (if event
      (begin
       ;; event's score time = seq_start + event_time
       (set! next (+ start (object-time event)))
       (if (early? next) 
	 (enqueue *qentry-object* event next start)
	 (write-event event stream next))
       (if (null? head)
	 #f
	 (enqueue type entry next start)))
      #f)))

;;;
;;; process functions need to access the current queue time,
;;; the queue start and the hander function.  for now i am using
;;; specials to avoid codewaking. the alternative would be to pass
;;; everything as parameters to the process function and then
;;; walk the code rewriting "special forms" like WAIT, etc, in terms
;;; of lexically scoped variables. but this requires at a minimum
;;; an implementation of MACROEXPAND-ALL (walk.lisp). 
;;;

(define-method* (scheduler-do-process (func <procedure>) qtime pstart stream type)
  ;; type has *qentry-process* in the lower nibble
  stream
  ;; *pstarts* is the scoretime that the process originally started at.
  ;; it is not null only during process funcall. for this reason some
  ;; code tests it to see if code is being called in the process.
  (set! *pstart* pstart)
  ;; *qnext* is advanced by (wait ...)
  (set! *qnext* qtime)
  ;; reschedule if process function returns non-nil
  (if (funcall func)
      (enqueue type func *qnext* *pstart*))
  (set! *pstart* #f))

(define (output event . args)
  ;; used in processes to write events to the current output stream.
  ;; checks to see if event's time is in future later than next event
  ;; in queue. if so it enqueues rather than outputs. if event is
  ;; written to file, ahead is added to scoretime stream's destination
  ;; can manage future scheduling
  (with-args (args &key (to *out*) at (ahead 0))
    (cond ((eq? *scheduler* ':asap)
	   (if (pair? event)
	       (dolist (e event)
	         ;; if called from process at relative to process start
                 ;; time
                 (let ((n (+ (or *pstart* 0) (or at (object-time e)))))
                   (if (early? n)
                     (enqueue (if (integer? e) *qentry-message*
                                  *qentry-object*)
                               e n #f)
                   (write-event e to (+ n ahead)))))
               (let ((n (+ (or *pstart* 0) (or at (object-time event)))))
                 (if (early? n)
                   (enqueue (if (integer? event) *qentry-message*
                                *qentry-object*) 
                            event n #f)
                   (write-event event to (+ n ahead))))))
          ((eq? *scheduler* ':rts)
           (write-event event to (+ (or at *qtime* 0) ahead)))
          (else
           (write-event event to (+ (or at 0) ahead))))
    (values)))

(define (now . args)
  ;; now can only be called from (process ) or from the repl
  (with-args (args &optional abs-time)
    ;; CHANGE: under rts scheduler this code is returning the time of
    ;; the datum stored in scheduling queue, NOT the scheduler's
    ;; current clock time. im not sure this is correct or not -- it
    ;; will be off by some microseconds.  

    ;; *pstart* will be #f if ;; called outside process
    (if *pstart*
      (if abs-time *qtime* (- *qtime* *pstart*))
      (rts:scheduler-time))))

(define (wait time)
  ;; CHANGE: allow optional time unit for RTS scheduling
  ;; wait can only be called under scheduler
  (let ((delta (if *scheduler* (abs time)
		   (err "wait: scheduler not running."))))
    (set! *qnext* (+ *qnext* delta))))

;;
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
  (with-args (args &key to at)
    to 
    ;; CHANGE: determine true time to insert in queue using time units
    ;; of destination scheduler.  if *pstart* is not null then the
    ;; sprout was called inside process under scheduling, in this case
    ;; at or at-msec is relative to process start time
    (if (pair? obj)
	(dolist (o obj) (sprout o :at at :to to))
	(begin
	  (if *pstart*
	      (if at 
		  (if (eq? *scheduler* ':asap)
		      (set! at (+ at *pstart*))
		      (set! at (+ at *pstart*)))
		  ;; else get current time
		  (set! at (now)))
	      ;; else sprout was called from REPL to insert in rts
	      (if at
		  #f
		  (set! at 0)))
	  (cond ((procedure? obj)
		 (enqueue *qentry-process* obj at at))
		((integer? obj)
		 (enqueue *qentry-message* obj at #f))
		((is-a? obj <object>)
		 ;; schedule-object will add in object's time value
		 (schedule-object obj (or *pstart* at)))
		(else
		 (enqueue *qentry-unknown* obj at #f)
		))))
    (values)))

;;;
;;; time unit conversion
;;;

(define (sec val fmat)
  (case fmat
    (( :sec ) val)
    (( :msec ) (/ val 1000.0))
    (( :usec ) (/ val 1000000.0))
    (else (err "sec: time format ~s not :sec :msec or :usec."
	       fmat))))

(define (msec val fmat)
  (case fmat
    (( :sec ) (values (inexact->exact (floor (* val 1000)))))
    (( :msec ) val)
    (( :usec ) (values (inexact->exact (floor val 1000))))
    (else (err "msec: time format ~s not :sec :msec or :usec."
	       fmat))))

(define (usec val fmat)
  (case fmat
    (( :sec ) (values (inexact->exact (floor (* val 1000000)))))
    (( :msec ) (values (inexact->exact (floor (* val 1000)))))
    (( :usec ) val)
    (else (err "usec: time format ~s not :sec :msec or :usec."
	       fmat))))
