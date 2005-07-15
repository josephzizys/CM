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
;;;

(define *rts-scheduling* #f)

(cond-expand
 (cmu (set! *rts-scheduling* ':periodic))
 (sbcl (set! *rts-scheduling* ':periodic))
 (gauche (set! *rts-scheduling* ':threaded))
 (openmcl (set! *rts-scheduling* ':threaded))
 (else #f))

(define (rts-scheduling )
  *rts-scheduling*)

(define (set-rts-scheduling! type)
  (case type
    (( :periodic ) (set! *rts-scheduling* type))
    (( :threaded ) (set! *rts-scheduling* type))
    (else
     (if (not type)
         (set! *rts-scheduling* type)
         (err "set-rts-scheduling!: Not a scheduling type ~s."
              type)))))

(define *rts-run* #f)
(define *rts-now* #f)
(define *rts-lock* #f)

(define (rts-reset) 
  (when (and *queue* (not (null? (%q-head *queue*))))
    (%q-flush *queue*))
  (set! *queue* #f)
  (set! *scheduler* #f)
  (set! *rts-run* #f)
  (set! *rts-now* #f))

(define (rts-running? )
  *rts-run*)

(define (rts-now )
  *rts-now*)

(define (rts-stop) 
  (set! *rts-run* #f))

(define (rts-pause )
  (err "rts-pause: not implemented."))

(define (rts-continue )
  (err "rts-continue: not implemented."))

(define (rts object to . args)
  ;; rts real time scheduler. attempts to be adaptive to fluctuations
  ;; using a targettime to calculate sleep time
  (if (rts-running?) (err "rts: already running."))
  (if (not *rts-lock*)
      (set! *rts-lock* (make-mutex)))
  (let* ((ahead (if (pair? args) (pop args) 0))   ; optional start time
         (endat (if (pair? args) (pop args) #f))  ; optional end time
         (ttime #f))  ; target time tries to control time disturbances
    (set! *queue* %q)
    (set! *scheduler* #t)
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
            (schedule-object object ahead)))
    (set! *out* to)
    (set! *rts-run* #t)
    ;; not sure about this
    (if (pair? ahead) (set! ahead (apply (function min) ahead)))
    (set! *rts-now* ahead)
    (setf ttime (+ *rts-now* (thread-current-time)))
    (thread-start!
     (make-thread
      (lambda ()
        (if (> *rts-now* 0) 
            (thread-sleep! *rts-now*))
        (do ((entry #f)
             (qtime #f)
             (start #f)
             (thing #f)
             (wait? #f)
             (none? (null? (%q-head *queue*))))
            ((or none? (not *rts-run*)
                 (and endat (> (%qe-time (%q-peek *queue*)) endat)))
             (unless none? (%q-flush *queue*))
             (unschedule-object object #t)
             (set! *rts-run* #f)
             (set! *queue* #f)
             (set! *scheduler* #f)
             (set! *rts-now* #f))
          (mutex-lock! *rts-lock*)   ; is this necessary? i think with
          (without-interrupts
              (do ()
                  ((or none? 
                       (> (%qe-time (%q-peek *queue*)) *rts-now*))
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
                (process-events thing qtime start *out*)
                (set! none? (null? (%q-head *queue*)))))
          (mutex-unlock! *rts-lock*)    ; is this necessary?
          (if wait? 
              (begin 
               (setf ttime (+ ttime wait?))
               (thread-sleep!
                (- ttime (thread-current-time)))))))))))

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

(define (newrts object to . args)
  (if (rts-running?) (err "rts: already running."))
  (let* ((ahead (if (pair? args) (pop args) 0))   ; optional start time
         (rtimp (rts-scheduling ))
         (endat (if (pair? args) (pop args) #f)))  ; optional end time
    (set! *queue* %q)
    (set! *scheduler* #t)
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
            (schedule-object object ahead)))
    (set! *out* to)
    (set! *rts-run* #t)
    ;; not sure about this
    (if (pair? ahead) (set! ahead (apply (function min) ahead)))
    (set! *rts-now* ahead)
    (case rtimp
      (( :threaded )
       )
      (( :periodic )
       (set-periodic-task-rate! 1 :ms)
       (add-periodic-task! :rts (rts-periodic-thunk object ahead endat)))
      (else (err "rts: not an rts method type: ~s" rtimp)))))

(define (rts-periodic-thunk object ahead endat)
  ;; the only hope for this method is if periodic polling at 1ms rate
  ;; is rock-solid
  (let ((wait? (if (> ahead 0)
                   (inexact->exact
                    (round (* ahead 1000.0)))
                   0)))
    (lambda ()
      (if (> wait? 0)
          (set! wait? (- wait? 10))  ;FUCK! this should be 1. where am
                                     ;i getting off???
          (let ((entry #f)
                (qtime #f)
                (start #f)
                (thing #f)
                (none? (null (%q-head *queue*))))
            (cond ((or none?
                       (not *rts-run*)
                       (and endat (> (%qe-time (%q-peek *queue*)) endat)))
                   (unless none? (%q-flush *queue*))
                   (unschedule-object object #t)
                   (set! *rts-run* #f)
                   (set! *queue* #f)
                   (set! *scheduler* #f)
                   (set! *rts-now* #f)
                   (remove-periodic-task! :rts))
                  (t
                   (do ()
                       ((or none?
                            (> (%qe-time (%q-peek *queue*)) *rts-now*))
                        (if none?
                            (set! wait? 0)
                            (let* ((next (%qe-time (%q-peek *queue*))))
                              (set! wait? (- next *rts-now*))
                              (set! *rts-now* next))))
                     (set! entry (%q-pop *queue*))
                     (set! qtime (%qe-time entry))
                     (set! start (%qe-start entry))
                     (set! thing (%qe-object entry))
                     (%qe-dealloc *queue* entry)
                     (process-events thing qtime start *out*)
                     (set! none? (null (%q-head *queue*))))
                   (or (eq? wait? 0)
                       (set! wait? (inexact->exact
                                   (round (* wait? 1000.0))))))))))))

; (set-rts-scheduling! :periodic)
; (defun foo (len wai) (process repeat len do (print (now)) wait wai))
; (newrts (foo 10 .5) nil)


