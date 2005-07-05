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
    `(let* ((,fn ,(cons 'process body))
            (,th (thread-alloc
                  (lambda ()
                    (do ((,ok (funcall , fn ))) 
                        ((not ,ok)
                         (thread-dealloc ,th))
                      (set! ,ok (funcall , fn )))))))
       ,th)))

;;;
;;; model 2: scheduler as thread
;;;

;(define *rts-lock* (make-mutex "*rts-lock"))
(define *rts-stop* #f)
(define *rts-time* #f)

(define (rts-stop) (setq *rts-stop* #t))

(define (rts-time ) *rts-time*)

(define (rts object to . at)
  (let* ((ahead (if (pair? at) (car at) 0)))
    (set! *out* to)
    (set! *rts-stop* #f)
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
    ;; not sure about this
    (if (pair? ahead) (set! ahead (apply (function min) ahead)))
    (set! *rts-time* ahead)
    (thread-start!
     (thread-alloc
      (lambda ()
        (if (> ahead 0) (thread-sleep! ahead))
        (do ((mapfn (lambda (e s) (write-event e *out* s)))
             (entry #f)
             (qtime #f)
             (start #f)
             (thing #f)
             (wait? #f)
             (none? (null? (%q-head *queue*))))
            ((or none? *rts-stop*)
             (unless none? (%q-flush *queue*))
             (unschedule-object object #t)
             (set! *rts-stop* #f)
             (set! *queue* #f)
             (set! *rts-time* #f))
          (without-interrupts
              (do ()
                  ((or none? (> (%qe-time (%q-peek *queue*)) ahead))
                   (if none?
                       (set! wait? #f)
                       (let* ((next (%qe-time (%q-peek *queue*))))
                         (set! wait? (- next ahead))
                         (set! ahead next)
                         (set! *rts-time* ahead)
                         )))
                (set! entry (%q-pop *queue*))
                (set! qtime (%qe-time entry))
                (set! start (%qe-start entry))
                (set! thing (%qe-object entry))
                (%qe-dealloc *queue* entry)
                (process-events thing qtime start mapfn)
                (set! none? (null? (%q-head *queue*)))
                ))
          (if wait? (thread-nanosleep! wait?))
          ))))))

;; 

;(define-method* (rts-sprout obj &key at ahead out)
;  )
  

;;;
;;; tests

#|

(pprint
 (macroexpand '(thread for i below 10 do (print i) wait .1)))

(define rtstimes (list))

(defun gettim (&optional pm)
  pm
  #+portmidi (if pm (pm:TimerTime) (get-internal-real-time))
  #-portmidi (get-internal-real-time))

#+portmidi
(progn (pm:portmidi) (pm:TimerStart))

(define (rtstim len wai pm?)
  (process with tim and inc
    for i below len
    do (if (not tim)
           (begin (set! tim (gettim pm?))
                  (set! inc 0))
           (let ((irt (gettim pm?)))
            (set! inc (- irt tim))
            (set! tim irt)))
    (push inc rtstimes)
    wait wai
    finally
    (begin (print :done!)
           (print (reverse! rtstimes)))))

(begin (set! rtstimes (list))
       (rts (rtstim 100 .1 nil) nil 0)
       )

|#











