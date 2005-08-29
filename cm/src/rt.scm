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
;;; real time scheduling (rts)
;;;

(define *rts-type* #f) ; see also *receive-type*

(cond-expand
 (cmu (set! *rts-type* ':periodic))
 (sbcl (set! *rts-type* 
             (if (eq? (os-name ) 'linux) ':threaded
                 :periodic)))
 (gauche (set! *rts-type* ':threaded))
 (openmcl (set! *rts-type* ':specific))
 (else #f))

(define (set-rts-method! type)
  (if (member type '(:periodic :threaded :specific))
      (set! *rts-type* type)
      (err "set-rts-method!: ~s is not :periodic, :threaded or :specific."
           type)))
      
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
    (set! *qtime* (thread-current-time))
    (if (pair? object)
        (dolist (o object)
          (schedule-object o
                           (+ *qtime* (if (pair? ahead)
                                          (if (pair? (cdr ahead))
                                              (pop ahead)
                                              (car ahead))
                                          ahead))))
        (if (pair? ahead)
            (schedule-object object (+ *qtime* (car ahead)))
            (if object
                (schedule-object object (+ *qtime* ahead)))))
    ;; not sure about this
    (if (pair? ahead) (set! ahead (apply (function min) ahead)))
    (set! *out* to)
    (set! *rts-run* #t)
    (set! *qtime* (+ *qtime* ahead))
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
      (( :specific )
       (set! *scheduler* ':specific)
       (rts-run-specific object ahead end))
      (else (err "rts: not an rts scheduling type: ~s" *rts-type*)))
    (values)))

(define (rts-run-threaded object ahead end)
  ;; rts threaded run function. attempts to be adaptive to
  ;; fluctuations using a target time (ttime) to calculate sleep time
  (lambda ()
    (if (number? end) (set! end (+ end *qtime*)))
    (if (> ahead 0) 
        (thread-sleep! ahead))
    (do ((entry #f)
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
      ;; update current time
      (set! *qtime* (thread-current-time))
      (with-mutex-grabbed (*qlock*)
        (without-interrupts
          (do ()
              ((or (%q-empty? *queue*)
                   (> (%qe-time (%q-peek *queue*)) *qtime*))
               (if (%q-empty? *queue*)
                   (set! wait? #f)
                 (set! wait? #t)))
            (set! entry (%q-pop *queue*))
            ;;(set! *qtime* (%qe-time entry))
            (set! start (%qe-start entry))
            (set! thing (%qe-object entry))
            (%qe-dealloc *queue* entry)
            (process-events thing *qtime* start *out*))))
      (if wait? 
          ;; wait? is true if something is in the queue with a time > *qtime*
          ;; in this case sleep MIN next run time and idle rate
          (let ((delta (- (%qe-time (%q-peek *queue*)) 
                          (thread-current-time))))
            ;; delta can be < 0 if the process evaluation took more time
            ;; than the wait increment. [is this true?]
            ;(print delta)
            (if (> delta 0) 
                (thread-sleep! (min delta *rts-idle-rate*))))
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
              (begin (thread-sleep! *rts-idle-rate*)))))))

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

;(define-generic* (set-receive-mode! str mode))


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
                          (deinit-receiver r *receive-type*))
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
         (err "set-receiver!: receiving is not implemented in this Lisp/OS."))
        ((not (member *receive-type* '(:threaded :periodic)))
         (err "set-receiver!: ~s is not a receive type."
              *receive-type*))
        ((eq? stream #t)                ; generic receive
         (let ((wrapper (generic-receive hook *receive-type*)))
           (case *receive-type*
             ((:threaded) (thread-start! wrapper))
             ((:periodic) (add-periodic-task! :receive wrapper)))))
        (else
         (let ((wrapper (stream-receiver hook stream *receive-type*)))
           (init-receiver stream *receive-type*)
           (case *receive-type*
             ((:threaded) (thread-start! wrapper))
             ((:periodic) (add-periodic-task! stream wrapper))))))
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

(define-method* (stream-receiver hook stream type)
  hook stream type
  (err "stream-receiver: ~s does not support receiving." stream))




