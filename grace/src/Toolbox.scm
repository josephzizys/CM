#>

#include "Toolbox.h"

<#

;;;
;;; FFI
;;;

(define tb:rescale
  (foreign-lambda float "Toolbox::rescale" float float float float float float))
(define tb:discrete
  (foreign-lambda int "Toolbox::discrete" float float float int int float))
(define tb:int
  (foreign-lambda int "Toolbox::float_to_fixnum" float))
(define tb:decimals
  (foreign-lambda float "Toolbox::decimals" float int))
(define tb:quantize
  (foreign-lambda float "Toolbox::quantize" float float))
(define tb:rhythm->seconds
  (foreign-lambda float "Toolbox::rhythm_to_seconds" float float float))
(define tb:cents->scaler
  (foreign-lambda float "Toolbox::cents_to_scaler" int))
(define tb:scaler->cents
  (foreign-lambda int "Toolbox::scaler_to_cents" float))
(define tb:keynum->hertz
  (foreign-lambda float "Toolbox::keynum_to_hertz" float))
(define tb:keynum->pc
  (foreign-lambda int "Toolbox::keynum_to_pc" float))
(define tb:hertz->keynum
  (foreign-lambda float "Toolbox::hertz_to_keynum" float))

(define tb:ran-set!
  (foreign-lambda void "Toolbox::ranstate_set" integer64))
(define tb:rani
  (foreign-lambda int "Toolbox::ran" int))
(define tb:ranf
  (foreign-lambda float "Toolbox::ran" float))
(define tb:beti
  (foreign-lambda int "Toolbox::ran" int int))
(define tb:betf
  (foreign-lambda float "Toolbox::ran" float float))

;;
;; API
;;

(define (rescale x x1 x2 y1 y2 . b)
  (if (null? b)
      (tb:rescale x x1 x2 y1 y2 1)
      (tb:rescale x x1 x2 y1 y2 (car b))))

(define (discrete x x1 x2 i1 i2 . b)
  (if (null? b)
      (tb:discrete x x1 x2 i1 i2 1)
      (tb:discrete x x1 x2 i1 i2 (car b))))

(define (int f)
  (tb:int f))

(define (quantize num steps)
  (tb:quantize num steps))

(define (decimals num digits)
  (tb:decimals num digits))

(define (rhythm->seconds beats . args)
  (let-optionals args ((tempo 60.0)
		       (beat .25))
		 (tb:rhythm->seconds beats tempo beat)))

(define (cents->scaler cents)
  (tb:cents->scaler cents))

(define (scaler->cents num)
  (tb:scaler->cents num))

(define (keynum->hertz k)
  (tb:keynum->hertz k))

(define (keynum->pc k)
  (tb:keynum->pc k))

(define (hertz->keynum hz)
  (tb:hertz->keynum hz))

(define (interpl x coords . base)
  (let* ((x1 (if (null? coords)
		 (error "not an x y coordinate list:" coords)
		 (car coords)))
	 (y1 (if (null? (cdr coords))
		 (err "not an x y coordinate list:" coords)
		 (cadr coords)))
	 (x2 x1)
	 (y2 y1)
	 (b (if (null? base) 1 (car base))))
    (do ((tail (cddr coords) (cddr tail)))
	((or (null? tail) (> x2 x))
	 (tb:rescale x x1 x2 y1 y2 b))
      (set! x1 x2)
      (set! y1 y2 )
      (set! x2 (car tail)) 
      (if (null? (cdr tail))
	  (error "not an x y coordinate list:" coords)
	  (set! y2 (cadr tail))))))

(define (interp x . args)
  (interpl x args))

(define (ran-set! seed)
  (tb:ran-set! seed))

(define (ran n . n2)
  (if (null? n2)
      (if (fixnum? n) (tb:rani n) (tb:ranf n))
      (if (and (fixnum? n) (fixnum? (car n2)))
	  (tb:beti n (car n2))
	  (tb:betf n (car n2)))))

(define (odds n . args)
  (let-optionals args ((true #t)
		       (false #f))
    (if (< (tb:ranf 1) n) true false)))

(define (pickl args)
  (if (null? args)
      (error "cannot pick from empty list: " args)
      (list-ref args (tb:rani (length args)))))

(define (pick . args)
  (pickl args))

