#>
#include "Toolbox.h"
<#

;;;
;;
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
(define tb:ranlow
  (foreign-lambda float "Toolbox::ranlow" ))
(define tb:ranhigh
  (foreign-lambda float "Toolbox::ranhigh" ))
(define tb:ranmiddle
  (foreign-lambda float "Toolbox::ranmiddle" ))
(define tb:rangauss
  (foreign-lambda float "Toolbox::rangauss" float float))
(define tb:ranexp
  (foreign-lambda float "Toolbox::ranexp" float))
;;(define tb:ranexp2
;  (foreign-lambda float "Toolbox::ranexp2" float))
(define tb:ranbeta
  (foreign-lambda float "Toolbox::ranbeta" float float))
(define tb:rangamma
  (foreign-lambda float "Toolbox::rangamma" float))
(define tb:rancauchy
  (foreign-lambda float "Toolbox::rancauchy" ))
(define tb:ranpoisson
  (foreign-lambda int "Toolbox::ranpoisson" float))
(define tb:ranpink
  (foreign-lambda double "Toolbox::ranpink" ))
(define tb:ranbrown
  (foreign-lambda double "Toolbox::ranbrown" ))

;;
;; API
;;

(define (rescale x x1 x2 y1 y2 . b)
  (if (list? x)
      (map (lambda (z) (apply rescale z x1 x2 y1 y2 b)) x)
      (if (null? b)
	  (tb:rescale x x1 x2 y1 y2 1)
	  (tb:rescale x x1 x2 y1 y2 (car b)))))

;;(define (discrete x x1 x2 i1 i2 . b)
;;  (if (null? b)
;;      (tb:discrete x x1 x2 i1 i2 1)
;;      (tb:discrete x x1 x2 i1 i2 (car b))))

;(define (discrete x x1 x2 i1 . args)
;  (if (pair? i1 )
;      (list-ref i1
;		(if (null? args)
;		    (tb:discrete x x1 x2 0 (length i1) 1)
;		    (if (null? (cdr args))
;			(tb:discrete x x1 x2 0 (car args) 1)
;			(tb:discrete x x1 x2 0 (car args)
;				     (cadr args)))))
;      (if (null? (cdr args))
;	  (tb:discrete x x1 x2 i1 (car args) 1)
;	  (tb:discrete x x1 x2 i1 (car args) (cadr args)))))

(define (discrete x x1 x2 i1 . args)
  ;; formals1: x x1 x2 i1   . i2  exp)
  ;; formals2: x x1 x2 list . len exp)
  (let ((i2 #f)
	(seq #f)
	(exp 1)) 
    (cond ((pair? i1)
	   (set! seq i1)
	   (if (null? args)
	       (set! i2 (length seq))
	       (begin (set! i2 (car args))
		      (if (not? (null? (cdr args)))
			  (set! exp (cadr args))))))
	  (else
	   (set! i2 (car args))
	   (if (not (null? (cdr args)))
	       (set! exp (cadr args)))))
    (if seq
	(if (list? x)
	    (map (lambda (z) (list-ref seq (tb:discrete z x1 x2 0 i2 exp))) x)
	    (list-ref seq (tb:discrete x x1 x2 0 i2 exp)))
	(if (list? x) 
	    (map (lambda (z) (tb:discrete z x1 x2 i1 i2 exp)) x)
	    (tb:discrete x x1 x2 i1 i2 exp)))))

(define (int f)
  (if (list? f) (map tb:int f)  (tb:int f)))

;; equivalents for use in SAL

(define (plus . args)
  (if (null? args) 
      0
      (if (null? (cdr args))
	  (if (list? (car args))
	      (apply + (car args))
	      (apply + args))
	  (apply + args))))

(define (minus arg . args)
  (if (null? args)
      (if (list? arg)
	  (apply - arg)
	  (- arg))
      (apply - arg args)))

(define times *)
(define divide /)

(define (quantize num steps)
  (if (list? num)
      (map (lambda (n) (tb:quantize n steps)) num)
      (tb:quantize num steps)))

(define (decimals num . digits)
  (if (null? digits)
      (tb:decimals num 3)
      (tb:decimals num (car digits))))

(define (rhythm->seconds beats . args)
  (with-optkeys (args (tempo 60.0) (beat .25))
    (if (list? beats)
	(map (lambda (x) (tb:rhythm->seconds x tempo beat)) beats)
	(tb:rhythm->seconds beats tempo beat))))

(define (cents->ratio cents)
  (if (list? cents)
      (map tb:cents->scaler cents)
      (tb:cents->scaler cents)))

(define (ratio->cents num)
  (if (list? num)
      (map tb:scaler->cents num)
      (tb:scaler->cents num)))

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
  (if (pair? (car args))
      (apply interpl x (car args) (cdr args))
      (interpl x args)))

;; transformations

(define (scale len keynum . args)
  (let ((head (list #t)))
    ;; args are steps... or list of steps
    (if (null? (cdr args)) (set! args (car args)))
    (do ((i 0 (+ i 1))
         (k keynum)
         (l (length args))
         (t head))
        ((not (< i len)) (cdr head))
      (set-cdr! t (list k))
      (set! t (cdr t))
      (set! k (+ k (list-ref args (modulo i l)))))))

;;; randomnesss

(define ran-set! tb:ran-set!)

(define (ran . num)
  (if (null? num) 
      (set! num 1)
      (set! num (car num)))
  (if (> num 1)
      (if (fixnum? num) (tb:rani num)
	  (tb:ranf num))
      (tb:ranf num)))

(define (between a b)
  (if (and (fixnum? a) (fixnum? b))
      (tb:beti a b)
      (tb:betf a b)))

(define (pick . args)
  (if (null? (cdr args))
      (list-ref (car args) (tb:rani (length (car args))))
      (list-ref args (tb:rani (length args)))))

(define (odds n . args)
  (with-optkeys (args (true #t) (false #f))
    (if (< (tb:ranf 1.0) n) true false)))

;; non-uniform distibutions

(define ranlow tb:ranlow)

(define ranhigh tb:ranhigh)

(define ranmiddle tb:ranmiddle)

(define (ranbeta . args)
  ;; args: a b
  (with-optkeys (args (a .5) b)
    (if (not b) (set! b a))
    (tb:ranbeta a b)))

(define (ranexp . args)
  ;; args: lambda
  (if (null? args)
      (tb:ranexp 1)
      (tb:ranexp (car args))))

(define (rangauss . args)
  ;; args: sigma mu
  (if (null? args)
      (tb:rangauss 1 0)
      (if (null? (cdr args))
	  (tb:rangauss (car args) 0)
	  (tb:rangauss (car args) (cdr args)))))

(define rancauchy tb:rancauchy)

(define (ranpoisson . args)
  ;; args: lambda
  (if (null? arg)
      (tb:ranpoisson 1)
      (tb:ranpoisson (car args))))

(define (rangamma . args)
  ;; args: k
  (if (null? args)
      (tb:rangamma 1)
      (tb:rangamma (car args))))

(define ranbrown tb:ranbrown)

(define ranpink tb:ranpink)


;*************************************************************************
(define *notes* (make-hash-table equal?))

(begin ;define (create-note-entries )
  (let ((degrees '(("c" "bs" ) ("df" "cs") ("d"  ) ("ef" "ds" )
		   ("e"  "ff") ("f" "es" ) ("fs" "gf" ) ("g"  )
		   ("af" "gs") ("a" ) ("bf" "as" ) ("b" "cf" )))
	(octaves '("00" "0" "1" "2" "3" "4" "5" "6"
		   "7" "8" "9"))
	(entries '()))
    (do ((key 0 (+ key 1))
;;	 (low (* 6.875 (expt 2 .25)))
	 ) ; C = A * 2^(3/12)
	((= key 128) 
	 (let ((r (list "r" -1 0.0 #f #f)))
	   (hash-table-set! *notes* "r" r)
	   (hash-table-set! *notes* -1 r))
	 #t)
      (set! entries (list-ref degrees (modulo key 12)))
      (do ((d entries (cdr d))
	   (k key)
	   (p (modulo key 12))
	   (k< (- key .5))
	   (k> (+ key .5))
;;	   (f (* low (expt 2 (/ key 12))))
;;	   (f> (* low (expt 2 (/ (+ key .5) 12))))
;;	   (f< (* low (expt 2 (/ (- key .5) 12))))
	   (f (tb:keynum->hertz key))
	   (f> (tb:keynum->hertz (+ key .5)))
	   (f< (tb:keynum->hertz (- key .5)))
	   (o (inexact->exact (floor (/ key 12))))
	   (x #f)
	   (n #f)
	   (e #f))
	  ((null? d) #f)
	(unless (and (= k 0) (string=? (car d) "bs"))
	  (if (string=? (car d) "bs") (set! o (- o 1))
	      (if (string=? (car d) "cf") (set! o (+ o 1))))
	  ;; note entry: (<str> <key> <hz> <pc> <"oct">)
	  (set! x (list-ref octaves o))
	  (set! n (string-append (car d) x))
	  (set! e (list n k f p x))
	  (hash-table-set! *notes* n e)
	  (when (eq? d entries) ; add keynum->note hash
	    (hash-table-set! *notes* k e))
	  ;; add <quarter tone entries
	  (set! n (string-append (car d) "<" x))
	  (set! e (list n k< f< #f x))
	  (hash-table-set! *notes* n e)
	  (when (eq? d entries) ; add only one keynum->note hash
	    (hash-table-set! *notes* k< e))
	  ;; add >quarter tone entries
	  (set! n (string-append (car d) ">" x))
	  (set! e (list n k> f> #f x))
	  (hash-table-set! *notes* n e)
	  (when (eq? d entries) ; add only one keynum->note hash
	    (hash-table-set! *notes* k> e))
	  )))))

; (create-note-entries)

(define (string->note-entry str oct err)
  ;; note entry: (<str> <key> <hz> <pc> <"oct">)
  (let ((entry (hash-table-ref *notes* str (lambda () #f))))
    (if (not entry)
	(if oct
	    (hash-table-ref *notes* 
			    (string-append str oct) 
			    (lambda () 
			      (and err (error "Not a note or key" str))))
	    (and err (error "Not a note or key" str)))
	entry)))

;;(define (number->note-entry num err)
;;  (let ((fix (if (exact? num) num
;;		 (inexact->exact (round num)))))
;;    (hash-table-ref *notes* fix
;;		    (lambda () 
;;		      (and err (error "Not a note or key" num))))))

(define (number->note-entry num err)
  (if (exact? num) 
      (hash-table-ref *notes* num
		    (lambda () 
		      (and err (error "Not a note or key" num))))
      (let* ((int (inexact->exact (floor num)))
	     (rem (- num int)))
	(hash-table-ref *notes*
			(if (< rem 0.333333333333333) int
			    (if (< rem 0.666666666666667)
				(+ int .5)
				(+ int 1)))
			(lambda () 
			  (and err (error "Not a note or key" num)))))))

(define (note-aux freq doct err?)
  ;; if doct (default octave string) we are parsing a note list
  (cond ((number? freq)
	 (number->note-entry freq err?))
	((symbol? freq)
	 (string->note-entry (symbol->string freq) doct err?))
	((string? freq)
	 (string->note-entry freq doct err?))
	((keyword? freq)
	 (string->note-entry (keyword->string freq) doct err?))	
	((and err?)
	 (error "Not a note or key" freq))
	(else
	 #f)))

(define (note freq)
  (if (list? freq)
      (let ((head (list #f)))
	(do ((tail freq (cdr tail))
	     (defo "4")
	     (this #f)
	     (resl head))
	    ((null? tail) (cdr head))
	  (if (list? (car tail)) ; allow sublists...
	      (begin
		(set! this (note (car tail) ))
		(set-cdr! resl (list this)))
	      (begin
		(set! this (note-aux (car tail) defo #t))
		;; note entry: (<str> <key> <hz> <pc> <"oct">)
		(set! defo (car (cddddr this)))
		(set-cdr! resl (list (car this)))))
	  (set! resl (cdr resl))))
      (car (note-aux freq #f #t))))

;; (note '(c5 d e f))
;; (note '(60 50 70 32 ))
;; (note 60.45)
;; (note #:c5)
;; (note "cs6")
;; (note "cs")
;; (note '(c d e5 (f b) g))
;; (note (key 440))

;;(define-constant +loga+ (log 6.875))
;;(define-constant +log2+ (log 2))

(define (key freq)
  (cond ((list? freq)
	 (let ((head (list #f)))
	   (do ((tail freq (cdr tail))
		(defo "4")
		(this #f)
		(resl head))
	       ((null? tail) (cdr head))
	     (if (or (list? (car tail))
		     (number? (car tail)))
		 (begin
		   (set! this (key (car tail) ))
		   (set-cdr! resl (list this)))
		 (begin
		   (set! this (note-aux (car tail) defo #t))
		   ;; note entry: (<str> <key> <hz> <pc> <"oct">)
		   (set-cdr! resl (list (cadr this)))
		   (set! defo (car (cddddr this)))))
	     (set! resl (cdr resl)))))
	((number? freq)
	 (if (> freq 0)
;;	     (- (* (/ (- (log freq) +loga+) +log2+) 12) 3)
	     (tb:hertz->keynum freq)
	     -1))
	(else
	 (cadr (note-aux freq #f #t)))))

;; (key 440)
;; (key 'c4)
;; (key '(c4 d e2 f))
;; (key 'c)

(define (hz freq)
  (cond ((list? freq)
	 (let ((head (list #f)))
	   (do ((tail freq (cdr tail))
		(defo "4")
		(this #f)
		(resl head))
	       ((null? tail) (cdr head))
	     (if (or (number? (car tail))
		     (list? (car tail)))
		 (begin
		   (set! this (hz (car tail) ))
		   (set-cdr! resl (list this)))
		 (begin
		   (set! this (note-aux (car tail) defo #t))
		   (set-cdr! resl (list (caddr this)))
		   (set! defo (car (cddddr this)))))
	     (set! resl (cdr resl)))))
	((number? freq)
;;	 (* 6.875 (expt 2 (/ (+ freq 3) 12)))
	 (tb:keynum->hertz freq)
	 )
	(else
	 (caddr (note-aux freq #f #t)))))

;; (hz 'c4)
;; (hz 69)
;; (hz '(c4 d e2 f g4 a))
;; (hz '(20 60 87 33))
;; (hz '(cs4 d e2 f g4 a))

(define (pc x)
  ;; returns the pitch class (0-11) of a key, note or list of the same
  (if (number? x)
      (modulo x 12)
      (if (pair? x)
	  (if (number? (car x))
	      (map pc x)
	      (map pc (key x)))
	  (modulo (key x) 12))))

;; (pc 60)
;; (pc 'cs4)
;; (pc 'cs>4)
;; (pc 'cs4)
;; (pc '(d4 c f bf3))
;; (pc '(50 30 12 22))

(define (invert x)
  (cond ((number? x)
	 (if (< x 12)
	     (modulo (- 12 x) 12)
	     (error "No inversion for" x)))
	((pair? x)
	 (let ((invkeys
		(lambda (keys) 
		  ;; invert list of keys around first key in list
		  (let* ((orig (car keys)) 
			 (head (list orig)))
		    (do ((tail (cdr keys) (cdr tail))
			 (last head))
			((null? tail)
			 head)
		      (set-cdr! last (list (- orig (- (car tail) orig))))
		      (set! last (cdr last)))))))
	   ;; check list for pcs, keynums or notes
	   (if (number? (car x))
	       (if (< (car x) 12)
		   (map (lambda (z) (modulo (- 12 z) 12)) x)
		   (invkeys x))
	       (note (invkeys (key x))))))
	(else
	 (error "No inversion for" x))))

; (invert '(60 62 64 ))
; (invert  7)
; (invert '(0 7 2 1))
; (invert 60) ; err!
; (invert '(bf3 df4 f))

(define (transpose x y)
  (cond ((number? x)
	 (if (number? y)
	     (if (and (< x 12) (< y 12))
		 (modulo (+ x y) 12)
		 (+ x y))
	     (note (+ x (key y)))))
	((pair? x)
	 (let ((transpkeys
		(lambda (keys orig) 
		  ;; transpose a list of pcs keys or notes
		  (let ((head (list #f)))
		    (do ((tail keys (cdr tail))
			 (last head))
			((null? tail)
			 (cdr head))
		      (set-cdr! last (list (+ orig (car tail))))
		      (set! last (cdr last))))))
	       (orig (if (number? y) y (key y))))
	   ;; check first in list for pc
	   (if (number? (car x))
	       (if (and (< (car x) 12) (< orig 12))
		   (map (lambda (z) (modulo (+ z orig) 12)) x)
		   (transpkeys x orig))
	       (note (transpkeys (key x) orig)))))
	(else
	 (error "No transposion for" x))))

; (transpose 7 7)
; (transpose '(0 1 2 3 4 5 6 7 8 9 10 11) 7)
; (invert '(0 1 2 3 4 5 6 7 8 9 10 11))
; (transpose '(0 3 7) 'c4)
; (transpose '(0 3 7) 11)
; (transpose '(c4 e g) 12)

;(define (matrix row)
;  (map (lambda (i) (transpose row i))
;       (invert row)))
;
;(matrix '(0 1 2 3 4 5 6 7 8 9 10 11))

(define retrograde reverse)

(define (scale-order scale . mode)
  (if (null? mode) (set! mode 1)
      (set! mode (car mode)))
  (if (eq? mode 1)
      (sort scale (lambda (a b)
		    (if (number? a)
			(if (number? b)
			    (< a b)
			    (< a (key b)))
			(if (number? b)
			    (< (key a) b)
			    (< (key a) (key b))))))
  (if (eq? mode -1)
      (sort scale (lambda (a b)
		    (if (number? a)
			(if (number? b)
			    (> a b)
			    (> a (key b)))
			(if (number? b)
			    (> (key a) b)
			    (> (key a) (key b))))))
      (if (eq? mode 0)
	  (shuffle scale)
	  (error "not a mode" mode)))))
