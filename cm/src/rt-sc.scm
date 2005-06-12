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


(define-class* <sc-stream> (<event-stream>)
  ((port :init-value 57110 :init-keyword :port)
   (host :init-value "127.0.0.1" :init-keyword :host)
   (local-port :init-value 57100 :init-keyword :local-port)
   (socket :init-value #f)
   (latency :init-value 0.05 :init-keyword :latency)
   (notify :init-value #f))
  :name 'sc-stream
  :metaclass <io-class>
  :file-types '("sc.udp" ))

(define-method* (send-msg message (io <sc-stream>))
  (multiple-value-bind (mess len)
    (format-osc message)
  (send-osc mess io len)))

(define-method* (send-bundle offset message (io <sc-stream>))
  (let ((arr (make-byte-vector "#bundle"))
        (mess-len 0))
    (set! arr (u8vector-append arr (make-osc-timetag offset io)))
    ;;this should be smarter
    (if (list? (list-ref message 0))
        (begin
          (dolist (bundle-mess message)
            (multiple-value-bind (mess len)
              (format-osc bundle-mess)
              (set! arr
                    (u8vector-append arr
                                     (make-byte-vector len)
                                     mess))
              (set! mess-len (+ mess-len len))))
          (set! mess-len (+ mess-len 20))
          (send-osc arr io mess-len))
      (multiple-value-bind (mess len)
        (format-osc message)
        (set! arr
              (u8vector-append arr
                               (make-byte-vector len)
                               mess))
        (set! mess-len (+ len 8 8 4))
        (send-osc arr io mess-len)))))


(define-method* (open-io (obj <sc-stream>) dir . args)
  dir
  args
  (unless (io-open obj)
    (slot-set! obj 'socket
               (make-udp-socket
                (slot-ref obj 'host)
                (slot-ref obj 'port)
                (slot-ref obj 'local-port)))
    (slot-set! obj 'open #t))
  (set! *out* obj))

(define-method* (close-io (obj <sc-stream>) . mode)
  mode
  (when (io-open obj)
    (socket-close (slot-ref obj 'socket))
    (socket-shutdown (slot-ref obj 'socket) 2)
    (slot-set! obj 'open #f))
  (set! *out* #f))

(define-method* (write-event (obj <scsynth>) (io <sc-stream>) time)
  (let* ((node-set-list #f)
         (synthname (symbol->string (class-name (class-of obj))))
         (slots (instance-slots obj))
         (inits (list #F))
         (msg (cons* "/s_new"
                     (string-downcase synthname)
                     (slot-ref obj 'node)
                     (slot-ref obj 'add-action)
                     (slot-ref obj 'target)
                     (do ((tail slots (cdr tail))
                          (args inits))
                         ((null? tail)
                          (cdr inits))
                       (unless (member (car tail)
                                       '(node add-action 
                                              target time))
                         (cond ((list? (slot-ref obj (car tail)))
                                (begin
                                  (set! node-set-list (append! node-set-list (list (string-downcase (symbol->string (car tail))))))
                                  (let ((mess-list (sc-env->list (slot-ref obj (car tail)))))
                                    (set! node-set-list (append! node-set-list (list (length mess-list))))
                                    (set! node-set-list (append! node-set-list mess-list)))))
                               ((equal? (find-class* 'sc-env) (class-of (slot-ref obj (car tail))))
                                (set! node-set-list (append! node-set-list (list (string-downcase (symbol->string (car tail))))))
                                (let ((mess-list (sc-env->list (slot-ref obj (car tail)))))
                                  (set! node-set-list (append! node-set-list (list (length mess-list))))
                                  (set! node-set-list (append! node-set-list mess-list))))
                               (else
                                (set-cdr! args 
                                          (list
                                           (string-downcase
                                            (symbol->string (car tail)))
                                           (slot-ref obj (car tail))))
                                (set! args (cddr args)))))))))
    (if node-set-list
        (send-bundle time (list msg (append! (list "/n_setn" (slot-ref obj 'node)) node-set-list)) io)
      (if (= time 0)
          (send-msg msg io)
        (send-bundle time msg io)))))



(define-method* (write-event (obj <load-synthdef>) (io <sc-stream>) time)
  (let ((msg (load-synthdef (slot-ref obj 'path))))
    (if (> time 0)
        (send-bundle time  msg io)
      (send-msg msg io))))

(define-method* (write-event (obj <load-synthdef-dir>) (io <sc-stream>) time)
  (let ((msg (load-synthdef-dir (slot-ref obj 'path))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg time msg io))))

(define-method* (write-event (obj <node-free>) (io <sc-stream>) time)
  (let ((msg (node-free (slot-ref obj 'node))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg msg io))))

(define-method* (write-event (obj <node-run>) (io <sc-stream>) time)
  (let ((msg (node-run (slot-ref obj 'node) (slot-ref obj 'flag))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg msg io))))

(define-method* (write-event (obj <node-set>) (io <sc-stream>) time)
  (let ((msg (node-set (slot-ref obj 'node) (slot-ref obj 'controls-values))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg msg io))))

(define-method* (write-event (obj <node-setn>) (io <sc-stream>) time)
  (let ((msg (node-setn (slot-ref obj 'node) (slot-ref obj 'controls-values))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg msg io))))

(define-method* (write-event (obj <node-fill>) (io <sc-stream>) time)
  (let ((msg (node-fill (slot-ref obj 'node) 
                        (slot-ref obj 'control) 
                        (slot-ref obj 'num-controls)
                        (slot-ref obj 'value))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg msg io))))

(define-method* (write-event (obj <node-map>) (io <sc-stream>) time)
  (let ((msg (node-map (slot-ref obj 'node) (slot-ref obj 'controls-buses))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg msg io))))

(define-method* (write-event (obj <node-mapn>) (io <sc-stream>) time)
  (let ((msg (node-mapn (slot-ref obj 'node)
                        (slot-ref obj 'control)
                        (slot-ref obj 'value)
                        (slot-ref obj 'num-controls))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg msg io))))

(define-method* (write-event (obj <node-before>) (io <sc-stream>) time)
  (let ((msg (node-before (slot-ref obj 'node) (slot-ref obj 'before))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg msg io))))

(define-method* (write-event (obj <node-after>) (io <sc-stream>) time)
  (let ((msg (node-after (slot-ref obj 'node) (slot-ref obj 'after))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg msg io))))

(define-method* (write-event (obj <group-new>) (io <sc-stream>) time)
  (let ((msg (group-new (slot-ref obj 'id) (slot-ref obj 'add-action) (slot-ref obj 'target))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg msg io))))

(define-method* (write-event (obj <group-head>) (io <sc-stream>) time)
  (let ((msg (group-head (slot-ref obj 'group) (slot-ref obj 'node))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg msg io))))

(define-method* (write-event (obj <group-tail>) (io <sc-stream>) time)
  (let ((msg (group-tail (slot-ref obj 'group) (slot-ref obj 'node))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg msg io))))

(define-method* (write-event (obj <group-free-all>) (io <sc-stream>) time)
  (let ((msg (group-free-all (slot-ref obj 'group))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg msg io))))

(define-method* (write-event (obj <group-deep-free>) (io <sc-stream>) time)
  (let ((msg (group-deep-free (slot-ref obj 'group))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg msg io))))

(define-method* (write-event (obj <ugen-command>) (io <sc-stream>) time)
  (let ((msg (ugen-command (slot-ref obj 'node)
                           (slot-ref obj 'ugen-index) 
                           (slot-ref obj 'command-name)
                           (slot-ref obj 'args))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg msg io))))

(define-method* (write-event (obj <buffer-alloc>) (io <sc-stream>) time)
  (let ((msg (buffer-alloc (slot-ref obj 'bufnum) 
                           (slot-ref obj 'frames)
                           (slot-ref obj 'channels))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg msg io))))

(define-method* (write-event (obj <buffer-alloc-read>) (io <sc-stream>) time)
  (let ((msg (buffer-alloc-read (slot-ref obj 'bufnum)
                                (slot-ref obj 'file) (slot-ref obj 'start-frame)
                                (slot-ref obj 'frames))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg msg io))))

(define-method* (write-event (obj <buffer-read>) (io <sc-stream>) time)
  (let ((msg (buffer-read (slot-ref obj 'bufnum) (slot-ref obj 'file)
                          (slot-ref obj 'start-frame) (slot-ref obj 'frames)
                          (slot-ref obj 'buffer-start-frame)
                          (slot-ref obj 'leave-open?))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg msg io))))

(define-method* (write-event (obj <buffer-write>) (io <sc-stream>) time)
  (let ((msg (buffer-write (slot-ref obj 'bufnum) (slot-ref obj 'file)
                           (slot-ref obj 'header) (slot-ref obj 'sample-format)
                           (slot-ref obj 'frames) (slot-ref obj 'start-frame)
                           (slot-ref obj 'leave-open?))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg msg io))))

(define-method* (write-event (obj <buffer-free>) (io <sc-stream>) time)
  (let ((msg (buffer-free (slot-ref obj 'bufnum))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg msg io))))

(define-method* (write-event (obj <buffer-set>) (io <sc-stream>) time)
  (let ((msg (buffer-set (slot-ref obj 'bufnum)
                         (slot-ref obj 'sample-values))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg msg io))))

(define-method* (write-event (obj <buffer-setn>) (io <sc-stream>) time)
  (let ((msg (buffer-setn (slot-ref obj 'bufnum)
                          (slot-ref obj 'samples-values))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg msg io))))

(define-method* (write-event (obj <buffer-fill>) (io <sc-stream>) time)
  (let ((msg (buffer-fill (slot-ref obj 'bufnum)
                          (slot-ref obj 'start-sample) (slot-ref obj 'num-samples)
                          (slot-ref obj 'value))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg msg io))))

(define-method* (write-event (obj <buffer-close>) (io <sc-stream>) time)
  (let ((msg (buffer-close (slot-ref obj 'bufnum))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg msg io))))

(define-method* (write-event (obj <buffer-gen>) (io <sc-stream>) time)
  (let ((msg (buffer-gen (slot-ref obj 'bufnum) (slot-ref obj 'command)
                         (slot-ref obj 'flags) (slot-ref obj 'args))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg msg io))))

(define-method* (write-event (obj <control-set>) (io <sc-stream>) time)
  (let ((msg (control-set (slot-ref obj 'bus) (slot-ref obj 'value))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg msg io))))

(define-method* (write-event (obj <control-setn>) (io <sc-stream>) time)
  (let ((msg (control-setn (slot-ref obj 'bus)
                           (slot-ref obj 'value))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg msg io))))

(define-method* (write-event (obj <control-fill>) (io <sc-file>) time)
  (let ((msg (control-fill (slot-ref obj 'bus) (slot-ref obj 'num-buses)
                           (slot-ref obj 'value))))
    (if (> time 0)
        (send-bundle time msg io)
      (send-msg msg io))))


(define-method* (write-event (obj <sc-buffer>) (io <sc-stream>) time)
  (cond ((slot-ref obj 'with-file)
         (write-event (make <buffer-alloc-read> :bufnum (slot-ref obj 'bufnum) :file (slot-ref obj 'with-file) :frames (slot-ref obj 'frames)
                            :start-frame (slot-ref obj 'starting-at)) io time))
        ((list? (slot-ref obj 'with-values))
         (write-event (make <buffer-alloc> :bufnum (slot-ref obj 'bufnum) :frames (slot-ref obj 'frames) :channels 1) io time)
         (write-event (make <buffer-setn> :bufnum (slot-ref obj 'bufnum)
                            :samples-values (list (slot-ref obj 'starting-at) (slot-ref obj 'with-values))) io time))
        ((number? (slot-ref obj 'with-values))
         (write-event (make <buffer-alloc> :bufnum (slot-ref obj 'bufnum) :frames (slot-ref obj 'frames) :channels 1) io time)
         (write-event (make <buffer-fill> :bufnum (slot-ref obj 'bufnum) :num-samples (- (slot-ref obj 'frames) (slot-ref obj 'starting-at))
                            :value (slot-ref obj 'with-values)) io time))
        ((procedure? (slot-ref obj 'with-values))
         (let ((vals '()))
           (dotimes (i (- (slot-ref obj 'frames) (slot-ref obj 'starting-at)))
             (set! vals (append! vals (list (apply (slot-ref obj 'with-values) '())))))
           (write-event (make <buffer-alloc> :bufnum (slot-ref obj 'bufnum) :frames (slot-ref obj 'frames) :channels 1) io time)
           (write-event (make <buffer-setn> :bufnum (slot-ref obj 'bufnum) :samples-values (list (slot-ref obj 'starting-at) vals)) io time)))
        ((slot-ref obj 'with-gen)
         (write-event (make <buffer-alloc> :bufnum (slot-ref obj 'bufnum) :frames (slot-ref obj 'frames) :channels 1) io time)
         (write-event (make <buffer-gen> :bufnum (slot-ref obj 'bufnum) :flags :wavetable :command (car (slot-ref obj 'with-gen))
                            :args (car (cdr (slot-ref obj 'with-gen)))) io time))))

(define (sc-quit . args)
  (with-args (args &optional out)
    (let ((msg '("/quit")))
      (if out
        (send-msg msg out)
        (if *out*
            (send-msg msg *out*))))))

(define (dump-osc bool . args)
  (with-args (args &optional out)
    (let ((msg (list "/dumpOSC" (if bool 1 0))))
      (if out
          (send-msg msg out)
        (if *out*
            (send-msg msg *out*))))))

(define (clear-sched . args)
  (with-args (args &optional out)
    (let ((msg '("/clearSched")))
      (if out
          (send-msg msg out)
        (if *out*
            (send-msg msg *out*))))))

(define (sc-open . args)
  (set! *out* (apply (function open-io) "sc.udp" #t args)))

(define (sc-open?)
  (let ((sc (find-object "sc.udp")))
    (and sc (io-open sc) sc)))

(define (sc-close)
  (if (sc-open?)
      (begin
        (clear-sched)
        (close-io (find-object "sc.udp")))
    #f))

(define (sc-flush)
  (clear-sched (sc-open?))
  (write-event (make <group-free-all> :group 0) (sc-open?) 0))



(define-method* (rt-now (io <sc-stream>))
  0)


(define-method* (rt-wait delta (io <sc-stream>))
  (let ((start (time->seconds (current-time))))
    (thread-sleep! (seconds->time (+ delta start)))))

(define-method* (rt-output event (out <sc-stream>) . args)
  (with-args (args &optional ahead)
    ahead
    (write-event event out (slot-ref event 'time))
    (values)))

(define-method* (rt-sprout (obj <object>) ahead (out <sc-stream>))
  (set! *out* out)
  (if (and ahead (not (= ahead 0)))
      (schedule-ahead (output obj out) ahead)
    (output obj out)))

(define-method* (rt-sprout (obj <procedure>) ahead (out <sc-stream>))
  (set! *out* out)
  (let ((proc (make-thread
               (lambda ()
                 (if (and ahead (not (= ahead 0)))
                     (thread-sleep! ahead))
                 (loop until
                       (not (funcall obj)))))))
    (thread-start! proc)
    proc))
;
;(values))
