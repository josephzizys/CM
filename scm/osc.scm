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

(define (osc:close)
  (let ((f (ffi_osc_close)))
    (if (< f 0)
        (error "osc:close failed with error code ~D" f)
        #t)))

(define *osc-hook* #f)

(define (osc:hook func)
  (cond ((not func)
         (set! *osc-hook* #f)
         (ffi_osc_set_hook #f)
         )
        ((procedure? func)
         (set! *osc-hook* func)
         (ffi_osc_set_hook #t)
         )
        (else
         (error "osc:hook not a function or #f: ~S" func)))
  func)

(define (osc:call-hook data)
  (if *osc-hook* (*osc-hook* data))
  (void))



