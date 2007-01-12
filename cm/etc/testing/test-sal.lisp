;;; **********************************************************************
;;; Copyright (C) 2006 Rick Taube
;;; This program is free software; you can redistribute it and/or   
;;; modify it under the terms of the Lisp Lesser Gnu Public License.
;;; See http://www.cliki.net/LLGPL for the text of this agreement.
;;; **********************************************************************

;;; $Revision$
;;; $Date$

(in-package cm)

(eval-when (:load-toplevel :compile-toplevel :execute)
  (defmacro saltest (pat str &optional res &rest args)
    (if (not res)
	`(parse *sal-grammer* ,pat ,str ,@args)	
	`(let ((r (quote ,res))
	       a b c x)
	   (multiple-value-setq (a b c)
	     (parse *sal-grammer* ,pat  ,str ,@args))
	   c
	   (cond ((not a)
		  (if (typep b 'sal-error)
		      (if (eql r ':error)
			  (setq x t)
			  (setq x nil))
		      (setq x nil)))
		 ((equal b r)
		  (setq x t))
		 (t
		  (setq x nil)))
	   (if (not x)
	       (let ((*print-case* ':downcase))
		 (format t "~&~&>>>>>>>> Test ~S ~S failed,~&>>>>>>>> value:  ~S~&>>>>>>>> result: ~S" 
			 ,pat ,str r b)
		 nil)
	       t)))))

(saltest :list "{}" (list))
(saltest :list "{{}}" '(nil))
(saltest :list "{{}" :error)
(saltest :list "{}}" :error)
(saltest :list "{{{{{{}}}}}}" '(((((nil))))))
(saltest :list "{{{}{}}{{}{}}}" '((nil nil) (nil nil)))
(saltest :list "{1}" '(1))
(saltest :list "{1 {2 3}}" '(1 (2 3)))

(saltest :aref "a[1]" (elt a 1)
(saltest :aref "a[1,2]" (elt a 1 2))
(saltest :aref "a[random(10)]" (elt a (random 10)))

(saltest :sexpr "foo" foo)
(saltest :funcall "foo()" (foo))
(saltest :funcall "foo ()" (foo))
(saltest :funcall "foo(1)" (foo 1))
(saltest :funcall "foo(1, 2)" (foo 1 2))
(saltest :funcall "foo(hi: 1)" (foo :hi 1))
(saltest :funcall "foo(hi: 1, ho: 33)" (foo :hi 1 :ho 33))
(saltest :funcall "foo(1,2,hi: 1, ho: 33)" (foo 1 2 :hi 1 :ho 33))
(saltest :funcall "foo(bar())" (foo (bar)))
(saltest :funcall "foo(bar(1))" (foo (bar 1)))


(saltest :funcall "foo(1, hi: bar(2), ho: 3)" (foo 1 :hi (bar 2) :ho 3))
(saltest :sexpr "foo(bar(baz(1),2),3)" (foo (bar (baz 1) 2) 3))
(saltest :funcall "foo(1,1/2)" (foo 1 1/2))
(saltest :funcall "foo(1, {1 2 3})" (foo 1 '(1 2 3)))
(saltest :funcall "foo(1,1/2, .1)" (foo 1 1/2 0.1))
(saltest :funcall "foo(1,.1,\"hiho\")" (foo 1 0.1 "hiho"))
(saltest :funcall "foo(hiho: 2)" (foo :hiho 2))
(saltest :funcall "foo(hi: 2, ho: .3)" (foo :hi 2 :ho 0.3))
(saltest :funcall "foo(hi: 2, ho: .3, hee: \"zuz\")" 
	 (foo :hi 2 :ho 0.3 :hee "zuz"))
(saltest :funcall "foo(1,2,hi: 2, ho: .3, hee: -1/3)" 
	 (foo 1 2 :hi 2 :ho 0.3 :hee -1/3))
(saltest :funcall "foo(1, 2.2, hi: 2/3, ho: \"zuz\")"
	 (foo 1 2.2 :hi 2/3 :ho "zuz"))
(saltest :funcall "foo(1,2,hi: 2, ho: .3, hee: -1/3)"
	 (foo 1 2 :hi 2 :ho 0.3 :hee -1/3))
(saltest :funcall "foo(1, bar(-99,88), 3)" (foo 1 (bar -99 88) 3))
(saltest :funcall "foo(1, bar(-99,baz(1000)), 3)" 
	 (foo 1 (bar -99 (baz 1000)) 3))
(saltest :sexpr "1 + 3 + 4" (+ (+ 1 3) 4))
(saltest :sexpr "- 1" (- 1))
(saltest :sexpr "1 + - 3 + 4" (+ (+ 1 (- 3)) 4))
(saltest :sexpr "1" 1)
(saltest :sexpr "1 + 2" (+ 1 2))
(saltest :sexpr "1 + foo(100)" (+ 1 (foo 100)))
(saltest :sexpr "foo(100) + 1" (+ (foo 100) 1))
(saltest :sexpr "foo(1 + 2)" (foo (+ 1 2)))
(saltest :sexpr "100 * interp(i, { 0 0 1 100})" 
	 (* 100 (interp i '(0 0 1 100))))
(saltest :sexpr "1 + (100 * interp(i, { 0 0 1 100}))"
	 (+ 1 (* 100 (interp i '(0 0 1 100)))))
(saltest :sexpr "foo(1 + 2, 3)" (foo (+ 1 2) 3))
(saltest :sexpr "foo(1, 2 + 3)" (foo 1 (+ 2 3)))
(saltest :sexpr "foo(1 * 2, 2 + 3, - 4)" (foo (* 1 2) (+ 2 3) (- 4)))
(saltest :sexpr "foo()" (foo))
(saltest :sexpr "foo(1) + bar(33)" (+ (foo 1) (bar 33)))
(saltest :sexpr "foo(1) + bar(33) * zuz(88)"
	 (+ (foo 1) (* (bar 33) (zuz 88))))
(saltest :sexpr "foo(1, 2 + bar(33))"
	 (foo 1 (+ 2 (bar 33))))
(saltest :sexpr "foo(1, 2 + bar(33 - xxx))" 
	 (foo 1 (+ 2 (bar (- 33 xxx)))))
(saltest :sexpr "bar(33 - xxx)" (bar (- 33 xxx)))
(saltest :sexpr "33 - xxx" (- 33 xxx))
(saltest :sexpr "- 33" (- 33))
(saltest :sexpr "1 - 33" (- 1 33))
(saltest :sexpr "1 - - 33" (- 1 (- 33)))
(saltest :sexpr "220 * expt(2, 1/12)" (* 220 (expt 2 1/12)))
(saltest :sexpr "times(2,3,4) / 3" (/ (times 2 3 4) 3))
(saltest :sexpr "(2 * 3 * 4) / 3" (/ (* (* 2 3) 4) 3))
(saltest :sexpr "foo / bar" (/ foo bar))
(saltest :sexpr "foo / bar(ziz * 5)" (/ foo (bar (* ziz 5))))
(saltest :sexpr "foo / bar(33)" (/ foo (bar 33)))
(saltest :sexpr "bar(33) / foo" (/ (bar 33) foo))
(saltest :sexpr "1 + 2 * 3" (+ 1 (* 2 3)))
(saltest :sexpr "(1 + 2) * 3" (* (+ 1 2) 3))
(saltest :sexpr "1 + foo(-2) * 3" (+ 1 (* (foo -2) 3)))
(saltest :sexpr "(1 + foo(-2)) * 3" (* (+ 1 (foo -2)) 3))
(saltest :sexpr "foo(-2) " (foo -2))
(saltest :sexpr "cl-user:zyz" common-lisp-user::zyz)
(saltest :sexpr "cl-zz:zyz" :error)
(saltest :sexpr "<midi>" #.<midi>)
(saltest :bindings "x" ((x nil)))
(saltest :bindings "x, y" ((x nil) (y nil)))
(saltest :bindings "x = 3" ((x 3)))
(saltest :bindings "x = 3, c, vv = x" ((x 3) (c nil) (vv x)))
(saltest :loop-statement "loop for i from 1 to 10 print i end"
	 (loop for i from 1 to 10 do (sal-print i)))
(saltest :loop-statement "loop for i from 1 print i end" 
	 (loop for i from 1 do (sal-print i)))
(saltest :loop-statement "loop for i to 2 print i end"
	 (loop for i to 2 do (sal-print i)))
(saltest :loop-statement "loop for i below 10 print i end" 
	 (loop for i below 10 do (sal-print i)))
(saltest :loop-statement "loop for i from 1 to 10 by 10 print i end" 
	 (loop for i from 1 to 10 by 10 do (sal-print i)))
(saltest :loop-statement 
	 "loop repeat 10 for x = 1 then 2 for i from 3 print i, x end" 
	 (loop repeat 10 for x = 1 then 2 for i from 3
	    do (sal-print i x)))

;; operator tests
(saltest :sexpr "x % y" (mod x y)
(saltest :sexpr "y ^ z" (expt y z))
(saltest :sexpr "a = b | c < d | e >= f"
	 (or (or (= a b) (< c d)) (>= e f)))
(saltest :sexpr "x + y * z" (+ x (* y z)))
(saltest :sexpr "x - - y ^ z" (- x (expt (- y) z)))


; (saltest-pattern-constructor "cycle 1 2 3 4 5")
; (saltest-pattern-constructor "cycle {1 2} 3 4 5")
; (saltest-pattern-constructor "heap 1 2 3 for 4")
; (saltest-pattern-constructor "heap of notes c4 d e for 4")
; (saltest-pattern-constructor "weighting 1 2 3 for x")
; (saltest-pattern-constructor "weighting {1 weight 3} 2 for x")
; (saltest-pattern-constructor "markov {1 2 -> 3 4}")
; (saltest-pattern-constructor "markov {1 2 -> {3 .1} 4}")

(saltest :procdecl
	 "process foo ()
  run repeat 10
    print now()
  end"
	 (defprocess foo nil (process repeat 10 do (sal-print (now))))
	 :info '((:definition . :process)))

(saltest :fundecl "function foo () begin print 123 end"
	 (defun foo nil (progn (sal-print 123)) (values)))

(saltest :vardecl "variable foo = 1" (defparameter foo 1))

(saltest :procdecl "process foo () run repeat 10 print 123 end"  
	 (defprocess foo nil (process repeat 10 do (sal-print 123)))
	 :info '((:definition . :process)))
