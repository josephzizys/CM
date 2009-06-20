;;; **********************************************************************

(define (plot . args)
  (let ((global #t)
	(debug #f)
	(title #f)
	(axes (list #f #f #f))
	(points #f)
	(fmat #f)
	(plots (list))
	(style #f))
    (define (setplotstyle pl sty) (set-car! (list-tail pl 1) sty))
    (define (setplotcolor pl col) (set-car! (list-tail pl 2) col))
    (define (setplottitle pl tit) (set-car! (list-tail pl 3) tit))
    (do ((tail args (cdr tail)))
	((null? tail)
	 (set! plots (reverse plots)))
      (case (car tail)
	((#:title)
	 (if (null? (cadr tail))
	     (error "missing title value"))
	 (if global
	     (set! title (cadr tail))
	     (setplottitle (car plots) (cadr tail)))
	 (set! tail (cdr tail)))
	((#:fields)
	 (if (not global)
	     (error "axes is a global setting"))
	 (if (null? (cdr tail))
	     (error "missing axes value"))
	 (set! axes (cadr tail))
	 (if (not (pair? axes))
	     (error "fields is not a list" axes))
	 (if (< (length axes) 2)
	     (error "too few fields" axes))
	 (set! tail (cdr tail)))
	((#:values )
	 (if (not global)
	     (error "format is a global setting"))
	 (if (null? (cdr tail))
	     (error "missing format value"))
	 (set! fmat (cadr tail))
	 (set! tail (cdr tail)))
	((#:x-axis #:xaxis)
	 (let ((axis (if (null? (cdr tail)) (error "missing x-axis value")
		     (cadr tail))))
	   (if (not global) (error "found non-global x-axis" axis))
	   (set! axis (if (pair? axis) (cons 'x axis) (list 'x axis)))
	   (set-car! axes axis)
	   (set! tail (cdr tail))))
	((#:y-axis #:yaxis)
	 (let ((axis (if (null? (cdr tail)) (error "missing y-axis value")
		     (cadr tail))))
	   (if (not global) (error "found non-global y-axis" axis))
	   (set! axis (if (pair? axis) (cons 'y axis) (list 'y axis)))
	   (set-car! (cdr axes) axis)
	   (set! tail (cdr tail))))
	((#:z-axis #:zaxis)
	 (let ((axis (if (null? (cdr tail)) (error "missing z-axis value")
		     (cadr tail))))
	   (if (not global) (error "found non-global z-axis" (car tail)))
	   (set! axis (if (pair? axis) (cons 'z axis) (list 'z axis)))
	   (set-car! (cddr axes) axis)
	   (set! tail (cdr tail))))
	((#:style)
	 (if (null? (cdr tail))
	     (error "missing style value"))
	 (cond ((not global)
		(setplotstyle (car plots) (cadr tail)))
	       (else
		(set! style (cadr tail))))
	 (set! tail (cdr tail)))
	((#:color)
	 (if (null? (cdr tail))
	     (error "missing color value"))
	 (if (not global)
	     (setplotcolor (car plots) (cadr tail))
	     (error "color is not a global plot option"))
	 (set! tail (cdr tail)))
	((#:debug)
	 (if (null? (cdr tail)) (error "missing debug value")
	     (set! debug (cadr tail)))
	 (set! tail (cdr tail)))
	(else
	 (if (pair? (car tail))
	     (let ((pdata (car tail)))
	       ;; plot is ((x y...) style color title)
	       (set! plots (cons (list pdata style #f #f) plots)))
	     (error "unknown plot setting" (car tail)))
	 (set! global #f) ; all done with global settings
	 ))
      ) ; end do

     (let ((port (if debug #t (open-output-string))))
      (format port "<plot")
      (if title (format port " title=\"~a\"" title))
      (format port ">") ; end <plot>
      ;; insure we have appropriate axis
      (do ((tail axes (cdr tail))
	   (indx 0 (+ indx 1)))
	  ((null? tail) #f)
	(axis->xml port (car tail) indx fmat))
      (unless (null? plots)
	(unless fmat (set! fmat (guess-data-format (caar plots))))
	(do ((tail plots (cdr tail)))
	    ((null? tail) #f)
	  (points->xml port (car tail) fmat)))
      (format port "</plot>")
      (if (not debug)
	  (ffi_plot_xml (get-output-string port)))
      (void))))

; (plot )
; (plot :x-axis '(0 123) '(0 0 1 1) )
; (plot :style "lineandpoint" :x-axis '(0 123) '(0 0 1 1) )
; (plot :style "histogram" :x-axis '(0 123) '(0 0 1 1) :style "line"  '(0 0 2 2) :style "point" :color "red")

(define (axis->xml port axis indx fmat)
  (define (tostring x)
    (if (keyword? x) (keyword->string x) (format #f "~a" x)))	    
  (cond ((or (symbol? axis) (string? axis) (keyword? axis))
	 (format port "<axis name=\"~a\"/>" (tostring axis)))
	((pair? axis)
	 (let ((save axis)
	       (name (car axis)))
	   (format port "<axis name=\"~a\"" (tostring name))
	   (set! axis (cdr axis))
	   (unless (null? axis)
	     (do ((tail axis (cdr tail))
		  (delim " range=\"" " "))
		 ((null? tail)
		  (format port "\"/>") )
	       (display delim port)
	       (display (tostring (car tail)) port))
	     )))
	((and (not axis) (= indx 0))
	 ;; if y data set unspecified x axis to ordinal
	 (if (member fmat '(:y y))
	     (format port "<axis name=\"x\" range=\"ordinal\"/>")
	     (format port "<axis name=\"x\" range=\"unspecified\"/>")))
	((and (not axis) (= indx 1))
	 (format port "<axis name=\"y\" range=\"unspecified\"/>"))
	((not axis)
	 ;;(format port "<axis name=\"Field ~A\" range=\"unspecified\">"
	 ;;        indx)
	 )
	(else
	 (error "illegal axis" axis)
	 ))
  (void))

; (axis->xml #t 'x)
; (axis->xml #t '(z x))
; (axis->xml #t '(x 0 1))
; (axis->xml #t '(x 1))
; (axis->xml #t '(x 1 0))
; (axis->xml #t '(x -1 1 .5))
; (axis->xml #t '(x 10 1000 -2))

(define (points->xml port plot fmat)
  ;; plot = (pointdata ptype style color)
  (let ((data (car plot))
	(styl (cadr plot))
	(colr (caddr plot))
	(titl (cadddr plot)))
    (define (tostring x)
      (if (keyword? x) (keyword->string x) (format #f "~a" x)))	    
    (format port "<points")
    (if styl
	(format port " style=\"~a\"" (tostring styl))
	(if (equal? fmat #:y)
	    (format port " style=\"impulses\""))
	)
    (if colr (format port " color=\"~a\"" (tostring colr)))
    (if titl (format port " title=\"~a\"" (tostring titl)))
    (format port ">")
    (cond ((pair? (car data))
	   ;; each sublist is a point record (single line )
	   (do ((tail data (cdr tail)))
	       ((null? tail) #f)
	     (format port "<point>")
	     (do ((e (car tail) (cdr e))
		  (d "" " "))
		 ((null? e) #f)
	       (format port d)
	       (format port "~s" (car e)))
	     (format port "</point>")))
	  ((member fmat '(#:y y))
	   (do ((num 0 (+ num 1))
		(tail data (cdr tail)))
	       ((null? tail) #f)
	     (format port "<point>~s ~s</point>" num (car tail))))
	  ((member fmat '(#:xy xy))
	   (do ((tail data (cddr tail)))
	       ((null? tail) #f)
	     (format port "<point>~s ~s</point>" (car tail) (cadr tail))))
	  (else
	   (error "unknown point format" fmat)
	   )
	  )
    (format port "</points>")))

;; (plot->xml #t '((.1 .3 .4) #:y "lineandpoint" #f) )
;; (plot->xml #t '((0 .1 .5 -.3 1 .4) #:xy #f "red") )
;; (plot->xml #t '((.1 .3 .4) #:y "lineandpoint" #f) )
;; (plot->xml #t '((0 .1 .9 .5 .3 .9 1 .4 .9) 3 "box" "red") )

(define (guess-data-format dat)
  (let ((a (car dat)))
    (cond ((number? a)
	   (do ((l dat (cdr l))
		(i 0 (+ i 1))
		(x (+ most-negative-fixnum 1)) ; 7 bug!
		(f #f))
	       ((or (null? l) f)
		(if (not f)
		    (if (even? i) #:xy)
		    f))
	     (if (even? i) 
		 (if (>= (car l) x)
		     (set! x (car l))
		     (set! f #:y)))))
	  ((pair? a) #:record)
	  (else 
	   (error "unknown point format" dat)
	   ))))

; (begin (define foo '(0 0 25 .9 75 .9 100 0)) (define bar (loop repeat 6 collect (random 1.0))))
; (guess-data-format foo)
; (guess-data-format bar)
; (guess-data-format (list '(0 0)))

(define (plot-data title . arg)
  ;; #f = focus #t = all num = layer number
  (let ((layer (if (null? arg) -1
		   (if (eq? (car arg) #f) -1
		       (if (eq? (car arg) #t) -2
			   (if (number? arg) arg
			       (error "plot layer not #f #t or number" 
				      (car arg))))))))
    (let ((str (ffi_plot_data title layer)))
      (read-from-string str))
    ))
  