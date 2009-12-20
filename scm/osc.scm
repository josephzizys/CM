;;; **********************************************************************
;;; Copyright (C) 2009, Rick Taube
;;; This program is free software; you can redistribute it and/or modify
;;; it under the terms of the Lisp Lesser Gnu Public License. The text of
;;; this agreement is available at http://www.cliki.net/LLGPL            
;;; **********************************************************************

(define (osc:open port target)
  (define (checkport port checktarg)
    (cond ((integer? port)
           (if (not (> port 0))
               (error "invalid port number: ~A" port))
           (number->string port))
          ((string? port)
           (if (and checktarg (position #\: port))
               (let ((p (position #\: port)))
                 (unless (and (> p 0) (< p (- (length port) 1)))
                   (error "invalid host:port string: ~S" port))
                 (checkport (substring port (+ p 1)) #f)
                 target)
               (let ((p (string->number port)))
                 (if (or (not p)
                         (not (integer? p))
                         (not (> p 0)))
                     (error "invalid port number: ~A" port))
                 port)))
          (else
           (error "invalid port number: ~S" port))))

  (let ((f (ffi_osc_open (checkport port #f) (checkport target #t))))
    (if (< f 0)
        (error "osc:open failed with error code ~D" f)
        #t)))

; (osc:open 100 "goo:900")
; (osc:open 100 "goo:900")
; (osc:open 100 ":900")
; (osc:open 100 "aaa:")

(define (osc:open? )
  (ffi_osc_open_p))
 
(define (osc:message path . data)
  (if (not (string? path))
      (error "osc:message path not a string ~S" path))
  (let ((f (ffi_osc_send path data #f)))
    (if (< f 0)
        (error "osc:message failed with error code ~D" f)
        (void))))

(define (osc:message path . data)
  (if (null? data)
      (if (string? path)
          (ffi_osc_send_message path data)
          (if (pair? path)
              (if (string? (car path))
                  (ffi_osc_send_message (car path) (cdr path))
                  (error "not an OSC message: ~S" path))
              (error "not an OSC message: ~S" path)))
      (if (string? path)
          (ffi_osc_send_message path data)
          (error "not an OSC path: ~S" path))
      ))

; (osc:message "/hi" 1 2)
; (osc:message '("/hi" 1 2))

; (osc:bundle 100 '("/hi" 1) '("/ho" 2))
; (osc:bundle 100 '(("/hi" 1) ("/ho" 2)))
; (osc:bundle '(100 ("/hi" 1) ("/ho" 2)))
; (osc:bundle '(100 (("/hi" 1) ("/ho" 2))))

;data ( ("/hi" 1) ("/ho" 2)))
;data ( (("/hi" 1) ("/ho" 2))))
;(OSC:BUNDLE 100 (("/hi" 1) ("/ho" 2)))

(define (osc:bundle time . data)
  (if (null? data)
      (if (pair? time)
          (begin (set! data (cdr time))
                 (set! time (car time)))
          (error "not an OSC bundle: ~S" time)))
  (if (number? time)
      (if (pair? (car data)) ; data must be a message or list of messages
          (if (pair? (caar data)) ; messages passed as single list
              (if (null? (cdr data))
                  (ffi_osc_send_bundle time (car data))
                  (error "not an OSC bundle: ~S" (car data)))
              (ffi_osc_send_bundle time data))
          (error "not an OSC message: ~S" (car data)))
      (error "not an OSC time tag: ~S" time)))

(define (osc:close)
  (let ((f (ffi_osc_close)))
    (if (< f 0)
        (error "osc:close failed with error code ~D" f)
        #t)))

(define (osc:hook func)
  ;; wrap user's hook in a function that returns true. if an error
  ;; occurs while hook is execting the return value will be (void) not
  ;; #t and the C callback can clear the hook.
  (ffi_osc_set_hook func)
  func)

