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


(define (schedule-ahead thunk ahead)
  (let ((thread (make-thread
                 (lambda ()
                   (begin
                     (thread-sleep! ahead)
                     (funcall thunk))))))
    (thread-start! thread)))


(define (rt-events object to . args)
  (let ((ahead (if (and (pair? args)
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
          (sprout object ahead)))
    *out*))