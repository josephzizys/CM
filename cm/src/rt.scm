;;; **********************************************************************
;;; Copyright (C) 2005 Todd Ingalls, Heinrich Taube
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
;;; this file contains experimental code for attempting "realtime"
;;; processes and scheduling based on the srfi-18 multithreading
;;; api: http://srfi.schemers.org/srfi-18/
;;;
;;;
;;; model 1: processes as threads
;;;

(define *threads* '())

(define (thread-alloc . args)
  (apply (function make-thread) args))

(define (thread-dealloc th)
  th
  (values))

(define (rt-events object to . args)
  (let ((proc-list '())
        (ahead (if (and (pair? args)
			(or (pair? (car args))
			    (number? (car args))))
                 (pop args)
                 0)))
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
          (push (sprout object ahead) proc-list)))
    proc-list))

(define-method* (rt-now io)
  io
  0)

(define-method* (rt-wait delta io)
  io
  (let ((start (time->seconds (current-time))))
    (thread-sleep! (seconds->time (+ delta start)))))

(define-method* (rt-output event out  . args)
  (with-args (args &optional ahead)
    ahead
    (write-event event out (object-time event))
    (values)))

(define-method* (rt-sprout (obj <object>) ahead out)
  (set! *out* out)
  (if (and ahead (not (= ahead 0)))
      (schedule-ahead (output obj out) ahead)
    (output obj out)))

(define-method* (rt-sprout (obj <thread>) ahead out)
  ahead out
  (thread-start! obj))

(define-method* (rt-sprout (obj <procedure>) ahead out)
  ahead
  (set! *out* out)
  (let ((proc (thread-alloc
               (lambda ()
                 (loop until
                       (not (funcall obj)))))))
    (thread-start! proc)
    proc))

(define (schedule-ahead thunk ahead)
  (let ((thread (thread-alloc
                 (lambda ()
                   (begin
                     (thread-sleep! ahead)
                     (funcall thunk))))))
    (thread-start! thread)))

(define-macro (thread . body)
  (let ((fn (gensym))
        (th (gensym))
        (ok (gensym)))
    `(let ((,th (thread-alloc
                 (lambda ()
                   (let ((fn , (expand-process body *process-operators*)))
                     (do ((,ok (funcall , fn ))) 
                         ((not ,ok)
                          (thread-dealloc ,th))
                       (set! ,ok (funcall , fn ))))))))
       ,th)))

;;;
;;; model 2: scheduler as thread
;;;

(define *rts-run* #f)
(define *rts-now* #f)
(define *rts-lock* (make-mutex))

(define (rts-reset) 
  (when (and *queue* (not (null? (%q-head *queue*))))
    (%q-flush *queue*))
  (set! *queue* #f)
  (set! *rts-run* #f)
  (set! *rts-now* #f))
(define (rts-running? ) *rts-run*)
(define (rts-now ) *rts-now*)
(define (rts-stop) (set! *rts-run* #f))
(define (rts-pause ) (err "rts-pause: not implemented."))
(define (rts-continue ) (err "rts-continue: not implemented."))

(define (rts object to . at)
  (if (rts-running?) (err "rts: already running."))
  (let ((ahead (if (pair? at) (car at) 0)))
    (set! *queue* %q)
    (if (consp object)
        (dolist (o object)
          (schedule-object o
                           (if (consp ahead)
                               (if (consp (cdr ahead))
                                   (pop ahead)
                                   (car ahead))
                               ahead)))
        (if (consp ahead)
            (schedule-object object (car ahead))
            (schedule-object object ahead)))
    (set! *out* to)
    (set! *rts-run* #t)
    ;; not sure about this
    (if (pair? ahead) (set! ahead (apply (function min) ahead)))
    (set! *rts-now* ahead)
    (thread-start!
     (thread-alloc
      (lambda ()
        (if (> *rts-now* 0) (thread-sleep! *rts-now*))
        (do ((mapfn (lambda (e s) (write-event e *out* s)))
             (entry #f)
             (qtime #f)
             (start #f)
             (thing #f)
             (wait? #f)
             (none? (null? (%q-head *queue*))))
            ((or none? (not *rts-run*))
             (unless none? (%q-flush *queue*))
             (unschedule-object object #t)
             (set! *rts-run* #f)
             (set! *queue* #f)
             (set! *rts-now* #f))
          (mutex-lock! *rts-lock*) ; is this necessary? i think with
          (without-interrupts
              (do ()
                  ((or none? (> (%qe-time (%q-peek *queue*)) *rts-now*))
                   (if none?
                       (set! wait? #f)
                       (let* ((next (%qe-time (%q-peek *queue*))))
                         (set! wait? (- next *rts-now*))
                         (set! *rts-now* next))))
                (set! entry (%q-pop *queue*))
                (set! qtime (%qe-time entry))
                (set! start (%qe-start entry))
                (set! thing (%qe-object entry))
                (%qe-dealloc *queue* entry)
                (process-events thing qtime start mapfn)
                (set! none? (null? (%q-head *queue*)))
                ))
          (mutex-unlock! *rts-lock*) ; is this necessary?
          (if wait? (thread-nanosleep! wait?))
          ))))))

;; 

(define-method* (rts-sprout obj &key to at ahead)
  ;; im not sure if i need a locking mechanism here or not. rts wraps
  ;; a without-interrupts around the points where its thread accesses
  ;; the queue, presumably that will keep this code -- which is called
  ;; from the repl process -- from side-effecting the queue during as
  ;; the scheduler uses it.
  to
  (unless (rts-running?) 
    (err "rts-sprout: rts not running."))
  (mutex-lock! *rts-lock*)
  (if at
      (schedule-object obj at)
      (if ahead
          (schedule-object obj (+ ahead (rts-now)))
          (schedule-object obj (object-time obj)) ; ???
          ))
  (mutex-unlock! *rts-lock*)
  (values))

;;;
;;; tests

#|
(defparameter *pm*
  (portmidi-open :input nil :output 3 :latency 0))

(define (zzz len lb ub wai amp)
  (process repeat len
    output (new midi :time 0
            :duration .1 :amplitude amp
            :keynum (between lb ub))
    wait wai))

;; fire it up
(rts (list (zzz 100 60 90 .25 .5)
           (zzz 50 20 50 .5 .5))
     *pm* 0)

;; now eval this whenever...
(let ((k (between 20 100)))
  (rts-sprout (zzz 15 k (+ k 7) 1/5 .75) :ahead 0))

|#











