;;; various envelope functions
;;;
;;; envelope-interp (x env (base 1.0)) -> value of env at x (base controls connecting segment type)
;;; window-envelope (beg end env) -> portion of env lying between x axis values beg and end
;;; map-envelopes (func env1 env2) maps func over the breakpoints in env1 and env2 returning a new envelope
;;;   multiply-envelopes (env1 env2) multiplies break-points of env1 and env2 returning a new envelope
;;;   add-envelopes (env1 env2) adds break-points of env1 and env2 returning a new envelope
;;; max-envelope (env) -> max y value in env, min-envelope
;;; integrate-envelope (env) -> area under env
;;; envelope-last-x (env) -> max x axis break point position
;;; stretch-envelope env old-attack new-attack old-decay new-decay -> divseg-like envelope mangler
;;; scale-envelope (env scaler offset) scales y axis values by 'scaler' and optionally adds 'offset'
;;; reverse-envelope (env) reverses the breakpoints in 'env'
;;; concatenate-envelopes (:rest envs) concatenates its arguments into a new envelope
;;; repeat-envelope env repeats (reflected #f) (normalized #f) repeats an envelope
;;; power-env: generator for extended envelopes (each segment has its own base)
;;; envelope-exp: interpolate segments into envelope to give exponential curves
;;; rms-envelope
;;; normalize-envelope
;;; simplify-envelope

(provide 'snd-env.scm)

;;; -------- envelope-interp

(define* (envelope-interp x env base)   ;env is list of x y breakpoint pairs, interpolate at x returning y
  "(envelope-interp x env (base 1.0)) -> value of env at x; base controls connecting segment 
type: (envelope-interp .3 '(0 0 .5 1 1 0) -> .6"
  (cond ((null? env) 0.0)		;no data -- return 0.0
	((or (<= x (car env))	        ;we're sitting on x val (or if < we blew it)
	     (null? (cddr env)))	;or we're at the end of the list
	 (cadr env))		        ;so return current y value
	((> (caddr env) x)		;x <= next env x axis value
	 (if (or (= (cadr env) (cadddr env))
		 (and base (= base 0.0)))
	     (cadr env)		;y1=y0, so just return y0 (avoid endless calculations below)
	     (if (or (not base) (= base 1.0))
		 (+ (cadr env)	;y0+(x-x0)*(y1-y0)/(x1-x0)
		    (* (- x (car env))
		       (/ (- (cadddr env) (cadr env))
			  (- (caddr env) (car env)))))
		 (+ (cadr env) ; this does not exactly match xramp-channel
		    (* (/ (- (cadddr env) (cadr env))
			  (- base 1.0))
		       (- (expt base (/ (- x (car env))
					(- (caddr env) (car env))))
			  1.0))))))
	(else (envelope-interp x (cddr env) base)))) ;go on looking for x segment


;;; -------- window-envelope (a kinda brute-force translation from the CL version in env.lisp)

(define (window-envelope beg end env)
  "(window-envelope beg end env) -> portion of env lying between x axis values beg and 
end: (window-envelope 1.0 3.0 '(0.0 0.0 5.0 1.0)) -> '(1.0 0.2 3.0 0.6)"
  (let ((nenv '())
	(lasty (if env (cadr env) 0.0))
	(len (length env)))
    (call-with-exit
     (lambda (return-early)               
       (do ((i 0 (+ i 2)))
	   ((>= i len))
	 (let ((x (env i))
	       (y (env (+ i 1))))
	   (set! lasty y)
	   (if (null? nenv)
	       (if (>= x beg)
		   (begin
		     (set! nenv (append nenv (list beg (envelope-interp beg env))))
		     (if (not (= x beg))
			 (if (>= x end)
			     (return-early (append nenv (list end (envelope-interp end env))))
			     (set! nenv (append nenv (list x y)))))))
	       (if (<= x end)
		   (begin
		     (set! nenv (append nenv (list x y)))
		     (if (= x end)
			 (return-early nenv)))
		   (if (> x end)
		       (return-early (append nenv (list end (envelope-interp end env)))))))))
       (append nenv (list end lasty))))))


;;; -------- map-envelopes like map-across-envelopes in env.lisp

(define (map-envelopes op e1 e2)
  "(map-envelopes func env1 env2) maps func over the breakpoints in env1 and env2 returning a new envelope"
  (let ((xs '()))
    (letrec ((at0 
	      (lambda (e)
		(let* ((diff (car e))
		       (len (length e))
		       (lastx (e (- len 2)))
		       (newe (copy e)))
		  (do ((i 0 (+ i 2)))
		      ((>= i len) newe)
		    (let ((x (/ (- (newe i) diff) lastx)))
		      (set! xs (cons x xs))
		      (set! (newe i) x))))))
	     (remove-duplicates
	      (lambda (lst)
		(letrec ((rem-dup
			  (lambda (lst nlst)
			    (cond ((null? lst) nlst)
				  ((member (car lst) nlst) (rem-dup (cdr lst) nlst))
				  (else (rem-dup (cdr lst) (cons (car lst) nlst)))))))
		  (rem-dup lst '())))))

      (if (null? e1)
	  (at0 e2)
	  (if (null? e2)
	      (at0 e1)
	      (let ((ee1 (at0 e1))
		    (ee2 (at0 e2))
		    (newe '()))
		(set! xs (sort! (remove-duplicates xs) <))
		(let ((len (length xs)))
		  (do ((i 0 (+ 1 i)))
		      ((= i len))
		    (let ((x (xs i)))
		      (set! newe (append newe (list x (op (envelope-interp x ee1) (envelope-interp x ee2)))))))
		  newe)))))))


;;; -------- multiply-envelopes, add-envelopes

(define (multiply-envelopes e1 e2)
  "(multiply-envelopes env1 env2) multiplies break-points of env1 and env2 returning a new 
envelope: (multiply-envelopes '(0 0 2 .5) '(0 0 1 2 2 1)) -> '(0 0 0.5 0.5 1.0 0.5)"
  (map-envelopes * e1 e2))

(define (add-envelopes e1 e2)
  "(add-envelopes env1 env2) adds break-points of env1 and env2 returning a new envelope"
  (map-envelopes + e1 e2))


;;; -------- max-envelope

(define (max-envelope env)
  "(max-envelope env) -> max y value in env"
  (define (max-envelope-1 e mx)
    (if (null? e)
	mx
	(max-envelope-1 (cddr e) (max mx (cadr e)))))
  (max-envelope-1 (cddr env) (cadr env)))


;;; -------- min-envelope

(define (min-envelope env)
  "(min-envelope env) -> min y value in env"
  (define (min-envelope-1 e mx)
    (if (null? e)
	mx
	(min-envelope-1 (cddr e) (min mx (cadr e)))))
  (min-envelope-1 (cddr env) (cadr env)))


;;; -------- integrate-envelope

(define (integrate-envelope env)
  "(integrate-envelope env) -> area under env"
  (define (integrate-envelope-1 e sum)
    (if (or (null? e) (null? (cddr e)))
	sum
	(integrate-envelope-1 (cddr e) (+ sum (* (+ (cadr e) (cadddr e)) .5 (- (caddr e) (car e)))))))
  (integrate-envelope-1 env 0.0))


;;; -------- envelope-last-x

(define (envelope-last-x e)
  "(envelope-last-x env) -> max x axis break point position"
  (if (null? (cddr e))
      (car e)
      (envelope-last-x (cddr e))))


;;; -------- stretch-envelope

(define* (stretch-envelope fn old-att new-att old-dec new-dec)

  "(stretch-envelope env old-attack new-attack old-decay new-decay) takes 'env' and 
returns a new envelope based on it but with the attack and optionally decay portions stretched 
or squeezed; 'old-attack' is the original x axis attack end point, 'new-attack' is where that 
section should end in the new envelope.  Similarly for 'old-decay' and 'new-decay'.  This mimics 
divseg in early versions of CLM and its antecedents in Sambox and Mus10 (linen).
  (stretch-envelope '(0 0 1 1) .1 .2) -> (0 0 0.2 0.1 1.0 1) 
  (stretch-envelope '(0 0 1 1 2 0) .1 .2 1.5 1.6) -> (0 0 0.2 0.1 1.1 1 1.6 0.5 2.0 0)"

  (let ()
    (if (and old-att
	     (not new-att))
	(throw 'wrong-number-of-args (list "stretch-envelope" 
					   old-att
					   "old-attack but no new-attack?"))
	(if (not new-att)
	    fn
	    (if (and old-dec
		     (not new-dec))
		(throw 'wrong-number-of-args (list "stretch-envelope" 
						   old-att new-att old-dec
						   "old-decay but no new-decay?"))
		(let* ((x0 (car fn))
		       (new-x x0)
		       (last-x (fn (- (length fn) 2)))
		       (y0 (cadr fn))
		       (new-fn (list y0 x0))
		       (scl (/ (- new-att x0) (max .0001 (- old-att x0)))))
		  (define (stretch-envelope-1 new-fn old-fn)
		    (if (null? old-fn)
			new-fn
			(let ((x1 (car old-fn))
			      (y1 (cadr old-fn)))
			  (if (and (< x0 old-att)
				   (>= x1 old-att))
			      (begin
				(if (= x1 old-att)
				    (set! y0 y1)
				    (set! y0 (+ y0 (* (- y1 y0) (/ (- old-att x0) (- x1 x0))))))
				(set! x0 old-att)
				(set! new-x new-att)
				(set! new-fn (cons new-x new-fn))
				(set! new-fn (cons y0 new-fn))
				(set! scl (if old-dec 
					      (/ (- new-dec new-att) (- old-dec old-att))
					      (/ (- last-x new-att) (- last-x old-att))))))
			  (if (and old-dec
				   (< x0 old-dec)
				   (>= x1 old-dec))
			      (begin
				(if (= x1 old-dec)
				    (set! y0 y1)
				    (set! y0 (+ y0 (* (- y1 y0) (/ (- old-dec x0) (- x1 x0))))))
				(set! x0 old-dec)
				(set! new-x new-dec)
				(set! new-fn (cons new-x new-fn))
				(set! new-fn (cons y0 new-fn))
				(set! scl (/ (- last-x new-dec) (- last-x old-dec)))))
			  (if (not (= x0 x1))
			      (begin
				(set! new-x (+ new-x (* scl (- x1 x0))))
				(set! new-fn (cons new-x new-fn))
				(set! new-fn (cons y1 new-fn))
				(set! x0 x1)
				(set! y0 y1)))
			  (stretch-envelope-1 new-fn (cddr old-fn)))))
		  
		  (if (and old-dec 
			   (= old-dec old-att)) 
		      (set! old-dec (* .000001 last-x)))
		  (reverse (stretch-envelope-1 new-fn (cddr fn)))))))))

    
;;; -------- scale-envelope

(define* (scale-envelope e scl (offset 0))
  "(scale-envelope env scaler (offset 0)) scales y axis values by 'scaler' and optionally adds 'offset'"
  (if (null? e)
      '()
      (append (list (car e) (+ offset (* scl (cadr e))))
	      (scale-envelope (cddr e) scl offset))))


;;; -------- reverse-envelope

(define (reverse-envelope e)
  "(reverse-envelope env) reverses the breakpoints in 'env'"
  (define (reverse-env-1 e newe xd)
    (if (null? e)
	newe
	(reverse-env-1 (cddr e)
		       (cons (- xd (car e))
			     (cons (cadr e)
				   newe))
		       xd)))
  (let ((len (length e)))
    (if (or (= len 0) (= len 2))
	e
	(let ((xmax (e (- len 2))))
	  (reverse-env-1 e '() xmax)))))


;;; -------- concatenate-envelopes

(define (concatenate-envelopes . envs)
  "(concatenate-envelopes :rest envs) concatenates its arguments into a new envelope"
  (define (cat-1 e newe xoff x0)
    (if (null? e)
	newe
	(cat-1 (cddr e)
	       (cons (cadr e)
		     (cons (+ (- (car e) x0) xoff)
			   newe))
	       xoff
	       x0)))
  (let ((ne '())
	(xoff 0.0))
    (for-each 
     (lambda (e)
       (if (and (not (null? ne))
		(= (car ne) (cadr e)))
	   (begin
	     (set! xoff (- xoff .01))
	     (set! ne (cat-1 (cddr e) ne xoff (car e))))
	   (set! ne (cat-1 e ne xoff (car e))))
       (set! xoff (+ xoff .01 (cadr ne))))
     envs)
    (reverse ne)))


(define* (repeat-envelope ur-env repeats (reflected #f) (normalized #f))
    "(repeat-envelope env repeats (reflected #f) (normalized #f)) repeats 'env' 'repeats' 
times.  (repeat-envelope '(0 0 100 1) 2) -> (0 0 100 1 101 0 201 1). 
If the final y value is different from the first y value, a quick ramp is 
inserted between repeats. 'normalized' causes the new envelope's x axis 
to have the same extent as the original's. 'reflected' causes every other 
repetition to be in reverse."
  (let* ((times (if reflected (floor (/ repeats 2)) repeats))
	 (e (if reflected
		(let ((lastx (ur-env (- (length ur-env) 2)))
		      (rev-env (cddr (reverse ur-env)))
		      (new-env (reverse ur-env)))
		  (while (not (null? rev-env))
			 (set! new-env (cons (+ lastx (- lastx (cadr rev-env))) new-env))
			 (set! new-env (cons (car rev-env) new-env))
			 (set! rev-env (cddr rev-env)))
		  (reverse new-env))
		ur-env))
	 (first-y (cadr e))
	 (x-max (e (- (length e) 2)))
	 (x (car e))
	 (first-y-is-last-y (= first-y (e (- (length e) 1))))
	 (new-env (list first-y x))
	 (len (length e)))
    (do ((i 0 (+ 1 i)))
	((= i times))
      (do ((j 2 (+ j 2)))
	  ((>= j len))
	(set! x (+ x (- (e j) (e (- j 2)))))
	(set! new-env (cons x new-env))
	(set! new-env (cons (e (+ j 1)) new-env)))
      (if (and (< i (- times 1)) (not first-y-is-last-y))
	  (begin
	    (set! x (+ x (/ x-max 100.0)))
	    (set! new-env (cons x new-env))
	    (set! new-env (cons first-y new-env)))))
    (set! new-env (reverse new-env))
    (if normalized
	(let ((scl (/ x-max x))
	      (new-len (length new-env)))
	  (do ((i 0 (+ i 2)))
	      ((>= i new-len))
	    (set! (new-env i) (* scl (new-env i))))))
    new-env))


;;; -------- power-env 
;;;
;;; (this could also be done using multi-expt-env (based on env-any) in generators.scm)

(if (not (provided? 'snd-ws.scm)) (load "ws.scm"))

(defgenerator penv (envs #f :type clm-vector) (total-envs 0 :type int) (current-env 0 :type int) (current-pass 0 :type int))

(define (power-env pe)
  (let ((val (env (vector-ref (penv-envs pe) (penv-current-env pe)))))
    (set! (penv-current-pass pe) (- (penv-current-pass pe) 1))
    (if (= (penv-current-pass pe) 0)
      (if (< (penv-current-env pe) (- (penv-total-envs pe) 1))
	  (begin
	    (set! (penv-current-env pe) (+ 1 (penv-current-env pe)))
	    (set! (penv-current-pass pe) (- (length (vector-ref (penv-envs pe) (penv-current-env pe))) 1)))))
    val))

(define* (make-power-env envelope (scaler 1.0) (offset 0.0) duration)
  (let* ((len (- (floor (/ (length envelope) 3)) 1))
	 (pe (make-penv :envs (make-vector len)
			:total-envs len
			:current-env 0
			:current-pass 0))
	 (xext (- (envelope (- (length envelope) 3)) (car envelope))))
    (do ((i 0 (+ 1 i))
	 (j 0 (+ j 3)))
	((= i len))
      (let ((x0 (envelope j))
	    (x1 (envelope (+ j 3)))
	    (y0 (envelope (+ j 1)))
	    (y1 (envelope (+ j 4)))
	    (base (envelope (+ j 2))))
	(vector-set! (penv-envs pe) i (make-env (list 0.0 y0 1.0 y1) 
						:base base :scaler scaler :offset offset 
						:duration (* duration (/ (- x1 x0) xext))))))
    (set! (penv-current-pass pe) (- (length (vector-ref (penv-envs pe) 0)) 1))
    pe))

(define* (power-env-channel pe (beg 0) dur snd chn edpos (edname "power-env-channel"))
  ;; split into successive calls on env-channel
  (let ((curbeg beg)) ; sample number
    (as-one-edit
     (lambda ()
       (do ((i 0 (+ 1 i)))
	   ((= i (penv-total-envs pe)))
	 (let* ((e (vector-ref (penv-envs pe) i))
		(len (length e)))
	   (env-channel e curbeg len snd chn edpos)
	   (set! curbeg (+ curbeg len)))))
     edname)))


;;; here's a simpler version that takes the breakpoint list, rather than the power-env structure:

(define* (powenv-channel envelope (beg 0) dur snd chn edpos)
  "(powenv-channel envelope (beg 0) dur snd chn edpos) returns an envelope with a separate base for \
each segment: (powenv-channel '(0 0 .325  1 1 32.0 2 0 32.0))"
  (let* ((curbeg beg)
	 (fulldur (or dur (frames snd chn edpos)))
	 (len (length envelope))
	 (x1 (car envelope))
	 (xrange (- (envelope (- len 3)) x1))
	 (y1 (cadr envelope))
	 (base (caddr envelope))
	 (x0 0.0)
	 (y0 0.0))
    (if (= len 3)
	(scale-channel y1 beg dur snd chn edpos)
	(as-one-edit
	 (lambda ()
	   (do ((i 3 (+ i 3)))
	       ((= i len))
	     (set! x0 x1)
	     (set! y0 y1)
	     (set! x1 (envelope i))
	     (set! y1 (envelope (+ i 1)))
	     (let ((curdur (round (* fulldur (/ (- x1 x0) xrange)))))
	       (xramp-channel y0 y1 base curbeg curdur snd chn edpos)
	       (set! curbeg (+ curbeg curdur)))
	     (set! base (envelope (+ i 2)))))))))


;;; by Anders Vinjar:
;;;
;;; envelope-exp can be used to create exponential segments to include in
;;; envelopes.  Given 2 or more breakpoints, it approximates the
;;; curve between them using 'xgrid linesegments and 'power as the
;;; exponent. 
;;; 
;;; env is a list of x-y-breakpoint-pairs,
;;; power applies to whole envelope,
;;; xgrid is how fine a solution to sample our new envelope with.

(define* (envelope-exp e (power 1.0) (xgrid 100))
  "(envelope-exp e (power 1.0) (xgrid 100)) approximates an exponential curve connecting the breakpoints"
  (let* ((mn (min-envelope e))
	 (largest-diff (* 1.0 (- (max-envelope e) mn)))
	 (x-min (car e))
	 (len (length e))
	 (x-max (e (- len 2)))
	 (x-incr (* 1.0 (/ (- x-max x-min) xgrid)))
	 (new-e '()))
    (do ((x x-min (+ x x-incr)))
	((>= x x-max))
      (let ((y (envelope-interp x e)))
	(set! new-e (cons x new-e))
	(set! new-e (cons (if (= largest-diff 0.0)
			      y
			      (+ mn
				 (* largest-diff
				    (expt (/ (- y mn) largest-diff) power))))
			  new-e))))
    (reverse new-e)))


;;; rms-envelope

(define* (rms-envelope file (beg 0.0) (dur #f) (rfreq 30.0) (db #f))
  "(rms-envelope file (beg 0.0) (dur #f) (rfreq 30.0) (db #f)) returns an envelope of RMS values in 'file'"
  ;; based on rmsenv.ins by Bret Battey
  (let* ((e '())
	 (incr (/ 1.0 rfreq))
	 (fsr (srate file))
	 (incrsamps (round (* incr fsr)))
	 (start (round (* beg fsr)))
	 (reader (make-sampler start file))
	 (end (if dur (min (* 1.0 (+ start (round (* fsr dur))))
			   (mus-sound-frames file))
		  (mus-sound-frames file)))
	 (rms (make-moving-average incrsamps))) ; this could use make-moving-rms from dsp.scm
    (do ((i 0 (+ i incrsamps)))
	((>= i end) 
	 (reverse e))
      (let ((rms-val 0.0))
	(do ((j 0 (+ 1 j)))
	    ((= j incrsamps))
	  (let ((val (reader)))
	    (set! rms-val (moving-average rms (* val val)))))
	(set! e (cons (* 1.0 (/ i fsr)) e))
	(set! rms-val (sqrt rms-val))
	(if db 
	    (if (< rms-val .00001)
		(set! e (cons -100.0 e))
		(set! e (cons (* 20.0 (/ (log rms-val) (log 10.0))) e)))
	    (set! e (cons rms-val e)))))))


(define* (normalize-envelope env (new-max 1.0))
  (define (abs-max-envelope-1 e mx)
    (if (null? e)
	mx
	(abs-max-envelope-1 (cddr e) (max mx (abs (cadr e))))))
  (let ((peak (abs-max-envelope-1 (cddr env) (abs (cadr env)))))
    (scale-envelope env (/ new-max peak))))


;;; simplify-envelope
;;;
;;; this is not very good...

(define* (simplify-envelope env (ygrid 10) (xgrid 100))

  ;; grid = how fine a fluctuation we will allow.
  ;; the smaller the grid, the less likely a given bump will get through
  ;; original x and y values are not changed, just sometimes omitted.

  (define (point-on-line? px py qx qy tx ty)

    ;; is point tx ty on line defined by px py and qx qy --
    ;; #f if no, :before if on ray from p, :after if on ray from q, :within if between p and q
    ;; (these are looking at the "line" as a fat vector drawn on a grid)
    ;; taken from "Graphics Gems" by Glassner, code by A Paeth

    (if (or (= py qy ty) 
	    (= px qx tx))
	:within
	(if (< (abs (- (* (- qy py) (- tx px))
		       (* (- ty py) (- qx px))))
	       (max (abs (- qx px))
		    (abs (- qy py))))
	    (if (or (and (< qx px) (< px tx))
		    (and (< qy py) (< py ty)))
		:before
		(if (or (and (< tx px) (< px qx))
			(and (< ty py) (< py qy)))
		    :before
		    (if (or (and (< px qx) (< qx tx))
			    (and (< py qy) (< qy ty)))
			:after
			(if (or (and (< tx qx) (< qx px))
				(and (< ty qy) (< qy py)))
			    :after
			    :within))))
	    #f)))

  (if (and env
	   (> (length env) 4))
      (let ((new-env (list (cadr env) (car env)))
	    (ymax (max-envelope env))
	    (ymin (min-envelope env))
	    (xmax (env (- (length env) 2)))
	    (xmin (car env)))
	(if (= ymin ymax)
	    (list xmin ymin xmax ymax)
	  (let ((y-scl (/ ygrid (- ymax ymin)))
		(x-scl (/ (or xgrid ygrid) (- xmax xmin)))
		(px #f) (py #f)
		(qx #f) (qy #f) 
		(tx #f) (ty #f) 
		(qtx #f) (qty #f))
	    (do ((i 0 (+ i 2)))
		((>= i (length env)))
	      (let ((ttx (env i))
		    (tty (env (+ i 1))))
		(set! tx (round (* ttx x-scl)))
		(set! ty (round (* tty y-scl)))
		(if px
		    (if (not (point-on-line? px py qx qy tx ty))
			(begin
			  (set! new-env (cons qtx new-env))
			  (set! new-env (cons qty new-env))
			  (set! px qx)
			  (set! py qy)))
		    (begin
		      (set! px qx)
		      (set! py qy)))
		(set! qx tx)
		(set! qy ty)
		(set! qtx ttx)
		(set! qty tty)))
	    (set! new-env (cons qtx new-env))
	    (set! new-env (cons qty new-env))
	    (reverse new-env))))
      env))
