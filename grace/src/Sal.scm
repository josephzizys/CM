;;; **********************************************************************
;;; Copyright (C) 2006 Rick Taube
;;; This program is free software; you can redistribute it and/or   
;;; modify it under the terms of the Lisp Lesser Gnu Public License.
;;; See http://www.cliki.net/LLGPL for the text of this agreement.
;;; **********************************************************************

;;; $Revision: 1364 $
;;; $Date: 2007-08-07 09:39:39 -0500 (Tue, 07 Aug 2007) $

(begin
  (define first car)
  (define second cadr)
  (define third caddr)
  (define fourth cadddr)
  (define fifth (lambda (l) (cadddr (cdr l))))
  (define sixth (lambda (l) (cadddr (cddr l)))))

;

(define *input* (list))
(define *tokens* (list))
(define *rule* #f)

(define (sal str toks)
  (set! *input* toks)
  (set! *tokens* (tokenize toks))
  (if *rule*
      (parse *rule* *tokens* #f 0 #f #f)
      *input*))

;
;;; Tokens
;
 
(define-record token type string location)

(define-record-printer (token t p)
  (fprintf p "#<t x~X ~S>" (token-type t) (token-string t)))

(define (list->token l)
  (if (eq? (car l) 't) 
      (apply make-token (cdr l))
      (apply make-token l)))

(define (tokenize l) (map list->token l))

(define (tokens->string toks)
  (apply string-append (map token-string toks)))

(define (token=? tok patval) ; is pat always a pattern value?
  (if (not (number? patval)) 
      (error "fix token=? : not a number" patval))
  (if (token? tok)
      (SalType=? (token-type tok) patval)
      (error "fix token=? : not a token" tok)))

(define (first-token toks) (car toks))
(define (rest-tokens toks) (cdr toks))
(define (null-tokens? toks) (null? toks))

;(define (first-token toks) toks)
;(define (rest-tokens toks) (toks-next toks))
;(define (null-tokens? toks) (eq? toks #f))

;
;;; Rules
;

(define *rules* (make-hash-table eq?))

(define-record rule name type pattern parser emiter)

(define-record-printer (rule r p)
  (fprintf p "#<r ~A>" (rule-name r)))

(define-macro (defrule typ pat . args)
  (letrec ((ppat (lambda (p)
		   (cond ((null? p) '(list))
			 ((pair? p)
			  `(cons ,(ppat (car p))
				 ,(ppat (cdr p))))
			 ((member p '(+ * @ and or))
			  `(quote ,p))
			 (else p)))))
    `(let ((ruleid ,typ))
       (hash-table-set! *rules* ruleid
			(make-rule ,(symbol->string typ)
				   ruleid 
				   ,(ppat pat)
				   ,(if (null? args)
					#f 
					(car args))
				   ,(if (or (null? args)
					    (null? (cdr args)))
					#f
					(cadr args)))))))

(define (get-rule typ . def) 
  (if (null? def)
      (hash-table-ref *rules* typ)
      (hash-table-ref/default *rules* def)))

;
;;; patterns
;

(define (pattern-value? x) (number? x))
(define (pattern-value x) x)
(define (pattern-clause? x) (pair? x))
(define (pattern-clause x) (car x))
(define (pattern-subs x) (cdr x))
(define (pattern-nsubs x) (length (pattern-subs x)))
(define (pattern-sub x i) (list-ref (pattern-subs x) i))
(define (pattern-and? x) (and (pattern-clause? x) (eq? (car x) 'and)))
(define (pattern-or? x) (and (pattern-clause? x) (eq? (car x) 'or)))
(define (pattern-one-or-more? x) (and (pattern-clause? x) (eq? (car x) '+)))
(define (pattern-zero-or-more? x) (and (pattern-clause? x) (eq? (car x) '*)))
(define (pattern-optional? x) (and (pattern-clause? x) (eq? (car x) '@)))

;
;;; parse errors
;

(define-record parse-error string pos)
(define-record-printer (parse-error e p)
  (fprintf p "#<parse-error ~S (pos ~S)>"
	   (parse-error-string e)
	   (parse-error-pos e)))

;
;; parse units
;

(define-record parse-unit type parsed postion)

(define-record-printer (parse-unit u p)
  (let ((typ (parse-unit-type u)))
    (if (SalRuleType? typ)
	(fprintf p "#<u ~A>" (rule-name (get-rule typ)))
	(fprintf p "#<u x~X>" typ))))

(define (token-unit? x)
  (and (parse-unit? x)
       (SalTokenType? (parse-unit-type x))))

(define (token-unit-type=? x typ) 
  (and (token-unit? x)
       (SalType=? (parse-unit-type x) typ)))

(define (rule-unit? x)
  (and (parse-unit? x)
       (SalRuleType? (parse-unit-type x))))

;; emit methods

(define (add-emit-info name data info)
  (cons (cons name data) info))

(define (get-emit-info name info)
  (let ((x (assoc name info)))
    (and x (cdr x))))

(define (emit x info errf)
  (cond ((token-unit? x)
	 (emit-token-unit x info errf))
	((rule-unit? x)
	 (emit-rule-unit x info errf))
	;; check list? last since tokens and units are lists...
	((list? x)
	 (emit-list x info errf))
	(else
	 (error "emit: dont know how to emit" x))))

(define (emit-list lis info errf)
  (if (null? lis)
      (list)
      (cons (emit (car lis) info errf)
	    (emit-list (cdr lis) info errf))))

; FIX!

(define (!= . nums) (not (apply = nums)))

(define (emit-token-unit unit info errf)
  ;; token units have the string in their parsed slot
  (let ((typ (parse-unit-type unit))
	(str (parse-unit-parsed unit))
	)
    (cond ((SalNumberType? typ)
	   (string->number str))
	  ((SalLiteralType? typ)
	   (string->symbol str))
	  ((SalOpType? typ)
	   (cond ((SalType=? typ SalMod) 'modulo)
		 ((SalType=? typ SalExpt) 'expt)
		 ((SalType=? typ SalGeneralEqual) 'equal)
		 ((SalType=? typ SalAnd) 'and)
		 ((SalType=? typ SalOr) 'or)
		 ((SalType=? typ SalNot) 'not)
		 (else
		  (string->symbol str))))
	  ((SalBoolType? typ)
	   (if (SalType=? typ SalTrue) #t #f))
	  ((SalType=? typ SalString )
	   str)
	  ((SalType=? typ SalKeyparam )
	   (string->keyword str))
	  ((SalType=? typ SalKeyword )
	   (string->keyword str))
	  ((SalType=? typ SalClass)
	   (string->symbol str))
	  ((SalType=? typ SalSlotRef )
	   (error "emit-token-unit: dont know how to emit slotref token "
		  unit))
	  ((SalType=? typ SalIdentifier )
	   (string->symbol str) )
	  (else
	   (error "emit-token-unit: dont know how to emit " 
		  unit)
	   ))))	

(define (emit-rule-unit unit info errf)
  ;; look up the rule and apply its emit method
  ;; if there is no emit method call emit on the parsed units
  (let ((rule (get-rule (parse-unit-type unit))))
    (let ((meth (rule-emiter rule)))
      (if (not meth)
	  (emit (parse-unit-parsed unit) info errf)
	  ( meth unit info errf)))))

;
;;; the parser
;

(define (parse pattern tokens . args)
  ;; returns a lisp expression or a parse-error
  (let ((junk-allowed #f)
	(trace #f)
	(info (list)))
    (call/cc
     (lambda (err)
       (call-with-values 
	   (lambda ()
	     (parser pattern tokens #f 0 trace 
		     (lambda (e) (err e))))
	 (lambda (success results remains) 
	   (if (and success (or (null? remains) junk-allowed)) 
	       (emit results
		     ;; top-level info is syntax to emit
		     (add-emit-info #:syntax #:scheme info)
		     (lambda (e) (err e)))
	       (make-parse-error "Unparsable input: "
				 (if (null? remains) -1
				     (token-location
				      (car remains)))))))))))

(define (parser pat tokens force-and level trace errf)
  (if trace (printf "~%parse[~A]: pattern=~S tokens=~S" level pat tokens))
  (cond	((pattern-value? pat)
	 ;; pattern value: is either a TokenType or RuleType
	 (let ((typ (pattern-value pat)))
	   (cond ((SalTokenType? typ)
		  (if (null-tokens? tokens) 
		      (values #f #f (list))
		      (let ((tok (first-token tokens)))
			(if (SalType=? (token-type tok) typ)
			    ;; token = patten, return token unit
			    (values #t
				    (make-parse-unit (token-type tok)
						     (token-string tok)
						     (token-location tok))
				    (rest-tokens tokens))
			    (values #f #f tokens)))))
		 ((SalRuleType? typ)
		  (let* ((rule (get-rule typ))
			 (test (rule-pattern rule))
			 (func (rule-parser rule)
			       ))
		    (call-with-values
			(lambda () (parser test tokens #f 
					   (+ level 1) trace errf) )
		      (lambda (a b c) 
			(if a
			    (values a 
				    (if func ( func b errf) b)
				    c)
			    (values #f #f c))))))
		 (else
		  (error "Not a token type or rule type" typ))
		 )))
	((pattern-clause? pat)
	 (cond ((or (pattern-and? pat) force-and)
		(let ((p #f)
		      (l tokens)
		      (r (list))
		      (s #f)
		      (n (pattern-nsubs pat))
		      (f #f)) ; fail flag
		  (do ((i 0 (+ i 1)))
		      ((or (= i n) f) #f)
		    (call-with-values 
			(lambda () 
			  (parser (pattern-sub pat i) l #f 
				  (+ level 1) trace errf))
		      (lambda (a b c) (set! p a) (set! s b) (set! l c)))
		    (if (not p)
			(set! f #t) ; subpattern failed
			(set! r (cons s r)))) ; else collect result
		  ;; if failed return tokens as they were else return
		  ;; only the tokens that remain after the parse
		  (if f
		      (begin (set! p #f)
			     (set! r (list))
			     (set! l tokens))
		      (begin (set! p #t)
			     (set! r (reverse r)) ))
		  (values p r l)
		  ))
	       ((pattern-or? pat)
		;; 'or' finds first true match. terms are independant
		;; and are given all tokens passed in
		(let ((p #f)
		      (s #f)
		      (l (list))
		      (n (pattern-nsubs pat)))
		  (do ((i 0 (+ i 1)) )
		      ((or p (= i n)) #f)
		    (call-with-values
			(lambda () 
			  (parser (pattern-sub pat i) tokens #f
				  (+ level 1) trace errf))
		      (lambda (a b c) (set! p a) (set! s b) (set! l c))))
		  (if p (values p s l )
		      (values #f (list) tokens))
		  ))
	       ((or (pattern-zero-or-more? pat)
		    (pattern-one-or-more? pat))
		;; '*' and '+' consume tokens while true, where entire
		;; clause must match to be true. * is zero or more, +
		;; is 1 or more
		(let ((p #t)
		      (s #f)
		      (l tokens)
		      (r (list))
		      (n 0))
		  ;; iterativly match pattern against tokens, stop on
		  ;; first fail or end of tokens
		  (do ()
		      ((or (not p) (null-tokens? l)) #f)
		    ;; call parser again with whole pattern forcing
		    ;; 'and' check
		    (call-with-values
			(lambda ()
			  (parser pat l #t level trace errf))
		      (lambda (a b c) (set! p a) (set! s b) (set! l c)))
		    ;; if we had a match update tokens and save
		    ;; results
		    (when p
	              (set! r (append r s))
		      (set! tokens l)
		      (set! n (+ n 1)))
		    )
		  (if (or (pattern-zero-or-more? pat)
			  (> n 0))
		      (set! p #t)
		      (begin (set! p #f) (set! r (list))))
		  (values p r tokens)))
	       ((pattern-optional? pat)
		(let ((p #f)
		      (s (list))
		      (l (list)))
		  ;; recall parser forcing 'and' test of whole pattern
		(call-with-values
		    (lambda ()
		      ;; dont bump level
		      (parser pat tokens #t level trace
			      errf))
		  (lambda (a b c) (set! p a) (set! s b) (set! l c)))
		;; ... if successful then return true with remaining
		;; tokens otherwise return true with tokens passed in
		(if p (values p s l)
		    (values #t #f tokens))))
	       (else
		(error "Pattern opr not one of and, or, *, +, @"
		       (pattern-clause pat))))
	 )
	(else
	 (error "Not a pattern value or pattern operator" pat))
	))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; SAL language definition
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;
; SalTypes identify tokens and rules. the parser attempts to match
; types in rule patterns against the (typed) tokens in the stream its
; parsing. the lower eight bits are ignored by the comparison function
; and may store additional infomation about the typed entity.
; 

(begin
  ;; generated by (sal-salenums)
  (define SalUntyped #x0)
  (define SAL_TOKEN_BEG #x0)
  (define SAL_DELIM_BEG #x0)
  (define SalComma #x100)
  (define SalLParen #x200)
  (define SalRParen #x300)
  (define SalLCurly #x400)
  (define SalRCurly #x500)
  (define SalLBrace #x600)
  (define SalRBrace #x700)
  (define SAL_DELIM_END #x800)
  (define SAL_DATA_BEG #x800)
  (define SalString #x900)
  (define SAL_NUMBER_BEG #xa00)
  (define SalInteger #xb00)
  (define SalRatio #xc00)
  (define SalFloat #xd00)
  (define SAL_NUMBER_END #xe00)
  (define SalKeyword #xf00)
  (define SAL_BOOL_BEG #x1000)
  (define SAL_HASH_BEG #x1000)
  (define SalTrue #x1100)
  (define SalFalse #x1200)
  (define SAL_BOOL_END #x1300)
  (define SalQMark #x1400)
  (define SAL_HASH_END #x1500)
  (define SAL_DATA_END #x1500)
  (define SalKeyparam #x1600)
  (define SalClass #x1700)
  (define SAL_OP_BEG #x1800)
  (define SalPlus #x1905)
  (define SalMinus #x1a05)
  (define SalTimes #x1b06)
  (define SalDivide #x1c06)
  (define SalMod #x1d05)
  (define SalExpt #x1e07)
  (define SalAnd #x1f02)
  (define SalOr #x2001)
  (define SalNot #x2103)
  (define SAL_RELATION_BEG #x2200)
  (define SalLess #x2304)
  (define SalGreater #x2404)
  (define SalNotEqual #x2504)
  (define SalGeneralEqual #x2604)
  (define SAL_ASSIGNMENT_BEG #x2700)
  (define SalEqual #x2804)
  (define SalLessEqual #x2904)
  (define SalGreaterEqual #x2a04)
  (define SAL_RELATION_END #x2b00)
  (define SAL_OP_END #x2b00)
  (define SalInc #x2c00)
  (define SalMul #x2d00)
  (define SalCol #x2e00)
  (define SalPre #x2f00)
  (define SalApp #x3000)
  (define SAL_ASSIGNMENT_END #x3100)
  (define SAL_LITERAL_BEG #x3100)
  (define SAL_STATEMENT_BEG #x3100)
  (define SAL_COMMAND_BEG #x3100)
  (define SalBegin #x3210)
  (define SalChdir #x3300)
  (define SalDefine #x3400)
  (define SalExec #x3500)
  (define SalIf #x3600)
  (define SalLoad #x3700)
  (define SalLoop #x3810)
  (define SalOpen #x3900)
  (define SalPlay #x3a00)
  (define SalPlot #x3b00)
  (define SalPrint #x3c00)
  (define SalRun #x3d10)
  (define SalSend #x3e00)
  (define SalSet #x3f00)
  (define SalSprout #x4000)
  (define SalSystem #x4100)
  (define SalUse #x4200)
  (define SAL_COMMAND_END #x4300)
  (define SAL_CONSTITUENT_BEG #x4300)
  (define SalElse #x4400)
  (define SalEnd #x4511)
  (define SalOutput #x4600)
  (define SalReturn #x4700)
  (define SalThen #x4800)
  (define SalUnless #x4900)
  (define SalUntil #x4a00)
  (define SalWait #x4b00)
  (define SalWhen #x4c00)
  (define SalWhile #x4d00)
  (define SalWith #x4e00)
  (define SAL_CONSTITUENT_END #x4f00)
  (define SAL_STATEMENT_END #x4f00)
  (define SAL_CLAUSAL_BEG #x4f00)
  (define SalAbove #x5000)
  (define SalBelow #x5100)
  (define SalBy #x5200)
  (define SalDownto #x5300)
  (define SalFinally #x5400)
  (define SalFor #x5500)
  (define SalFrom #x5600)
  (define SalIn #x5700)
  (define SalOver #x5800)
  (define SalRepeat #x5900)
  (define SalTo #x5a00)
  (define SAL_CLAUSAL_END #x5b00)
  (define SAL_LITERAL_END #x5b00)
  (define SAL_DEFINE_BEG #x5b00)
  (define SalFunction #x5c00)
  (define SalProcess #x5d00)
  (define SalVariable #x5e00)
  (define SAL_DEFINE_END #x5f00)
  (define SAL_IDENTIFIER_BEG #x5f00)
  (define SalIdentifier #x6000)
  (define SalSlotRef #x6100)
  (define SAL_IDENTIFIER_END #x6200)
  (define SAL_TOKEN_END #x6200)
  (define SAL_RULE_BEG #x6200)
  (define SalNumberRule #x6300)
  (define SalBoolRule #x6400)
  (define SalAtomRule #x6500)
  (define SalListRule #x6600)
  (define SalEltRule #x6700)
  (define SalArefRule #x6800)
  (define SalIfExprRule #x6900)
  (define SalFuncallRule #x6a00)
  (define SalFunargsRule #x6b00)
  (define SalPargsRule #x6c00)
  (define SalKargsRule #x6d00)
  (define SalOpRule #x6e00)
  (define SalMexprRule #x6f00)
  (define SalTermRule #x7000)
  (define SalSexprRule #x7100)
  (define SalBindingsRule #x7200)
  (define SalBindRule #x7300)
  (define SalAssignmentRule #x7400)
  (define SalAssignRule #x7500)
  (define SalAssignerRule #x7600)
  (define SalSetRule #x7700)
  (define SalFunctionReturnRule #x7800)
  (define SalProcessWaitRule #x7900)
  (define SalBlockRule #x7a00)
  (define SalConditionalRule #x7b00)
  (define SalLoopStatementRule #x7c00)
  (define SalRunStatementRule #x7d00)
  (define SalSteppingRule #x7e00)
  (define SalTerminationRule #x7f00)
  (define SalPrintStatementRule #x8000)
  (define SalExecStatementRule #x8100)
  (define SalOpenStatementRule #x8200)
  (define SalSendStatementRule #x8300)
  (define SalSproutStatementRule #x8400)
  (define SalOutputStatementRule #x8500)
  (define SalLoadStatementRule #x8600)
  (define SalSystemStatementRule #x8700)
  (define SalChdirStatementRule #x8800)
  (define SalPlayStatementRule #x8900)
  (define SalPlotStatementRule #x8a00)
  (define SalDefineStatementRule #x8b00)
  (define SalStatementRule #x8c00)
  (define SalStatementSequenceRule #x8d00)
  (define SalDeclarationRule #x8e00)
  (define SalVarDeclRule #x8f00)
  (define SalFunDeclRule #x9000)
  (define SalProcDeclRule #x9100)
  (define SalProcessBodyRule #x9200)
  (define SAL_RULE_END #x9300)
  (define SAL_TYPE_END #x9300)
  )

(define (SalType? x) (and (<= #x100 x) (< x SAL_TYPE_END)))

(define (SalTokenType? i) 
  (and (< SAL_TOKEN_BEG i) (< i SAL_TOKEN_END)))

(define (SalDelimType? i) 
  (and (< SAL_DELIM_BEG i) (< i SAL_DELIM_END)))

(define (SalNumberType? i) 
  (and (< SAL_NUMBER_BEG i) (< i SAL_NUMBER_END)))

(define (SalBoolType? i) 
  (and (< SAL_BOOL_BEG i) (< i SAL_BOOL_END)))

(define (SalOpType? i) 
  (and (< SAL_OP_BEG i) (< i SAL_OP_END)))

(define (SalOpWeight i) 
  (bitwise-and i #xFF))

(define (SalRelationType? i) 
  (and (< SAL_RELATION_BEG i) (< i SAL_RELATION_END)))

(define (SalAssignmentType? i) 
  (and (< SAL_ASSIGNMENT_BEG i) (< i SAL_ASSIGNMENT_END)))

(define (SalLiteralType? i) 
  (and (< SAL_LITERAL_BEG i) (< i SAL_LITERAL_END)))

(define (SalStatementType? i) 
  (and (< SAL_STATEMENT_BEG i) (< i SAL_STATEMENT_END)))

(define (SalCommandType? i) 
  (and (< SAL_COMMAND_BEG i) (< i SAL_COMMAND_END)))

(define (SalConstituentType? i) 
  (and (< SAL_CONSTITUENT_BEG i) (< i SAL_CONSTITUENT_END)))

(define (SalClausalType? i) 
  (and (< SAL_CLAUSAL_BEG i) (< i SAL_CLAUSAL_END)))

(define (SalRuleType? i) 
  (and (< SAL_RULE_BEG i) (< i SAL_RULE_END)))

(define (SalType=? typ1 typ2)
  ;; ignore the lower 8 (data) bits when comparing SalTypes
  (= (arithmetic-shift typ1 -8)
     (arithmetic-shift typ2 -8)))

(define (SalType->index typ)
  ;; shift SalType to 0
  (arithmetic-shift typ -8))

;
;; grammer rules
;

(defrule SalNumberRule (or SalInteger SalFloat SalRatio)
  #f
  #f)

(defrule SalBoolRule (or SalTrue SalFalse)
  #f
  #f)

(defrule SalAtomRule (or SalInteger SalFloat SalRatio SalKeyword
			 SalIdentifier SalTrue SalFalse)
  #f
  #f)

(defrule SalListRule (and SalLCurly (* SalEltRule) SalRCurly)
  (lambda (args errf) 
    (make-parse-unit SalListRule (cadr args) #f))
  (lambda ( unit info errf)
    (let ((lev (get-emit-info #:list info)) ; t if we are sublist
	  (sub (parse-unit-parsed unit)))
      (if (not lev) 
	  ;; we are at top level of a list.  make a null
	  ;; top-level {} call (list) to create the list.
	  (if (null? sub)
	      (list 'list)
	      (let ((l (emit sub (add-emit-info #:list #t info) errf)))
		;; if in a bindings copy the constant list to avoid user
		;; side effecting constant (quoted) data.
		(if (get-emit-info #:bindings info)
		    `(append (quote ,l) (list))
		    `(quote ,l))))
	  (emit sub info errf))))
  )

(defrule SalEltRule (or SalAtomRule SalListRule SalString)
  #f
  #f)

(defrule SalArefRule (and SalIdentifier SalLBrace SalSexprRule SalRBrace)
  ;; NEW: only 1 index allowed: [ index ]
  (lambda (args errf)
    ;; <id> <lb> <parg> <rb> 
    (make-parse-unit SalArefRule (list (first args) (third args)) #f))
  (lambda (unit info errf)
    (cons 'list-ref (emit (parse-unit-parsed unit) info errf)))
  )

(defrule SalIfExprRule (and SalQMark SalLParen SalSexprRule SalComma
			    SalSexprRule
			    (@ SalComma SalSexprRule) SalRParen)
  (lambda (args errf)
    ;; #? ( <sexpr> , <sexpr> [, <sexpr>])
    (let ((elseclause (sixth args)))
      (make-parse-unit SalIfExprRule
		       (list (third args)
			     (fifth args)
			     (if (pair? elseclause)
				 (second elseclause)
				 #f))
		       #f)))
  (lambda (unit info errf)
    (let* ((subs (parse-unit-parsed unit))
	   (test (emit (first subs) info errf))
	   (then (emit (second subs) info errf))
	   (else (third subs)))
      (if else
	  (list 'if test then (emit else info errf))
	  (list 'if test then #f)))))

(define (remove-token-type toks typ)
  ;; remove all comma to
  (let* ((head (list #t))
	 (tail head))
    (do ((toks toks (cdr toks)))
	((null? toks) (cdr head))
      (if (token-unit-type=? (car toks) typ)
	  #f
	  (begin
	    (set-cdr! tail (list (car toks)))
	    (set! tail (cdr tail)))))))
		      
; this could be (and sexpr (@ comma sexpr))
(defrule SalPargsRule (or (and SalSexprRule (+ SalComma SalSexprRule))
			  SalSexprRule)
  (lambda (args errf)
    ;; args is 1 arg or (arg (:co arg ...))
    ;;(print (list #:pargs-> args))
    (if (not (pair? args))
	(list args)
	(if (and (pair? (cdr args))
		 (pair? (cadr args))
		 (token-unit-type=? (car (cadr args)) SalComma))
	    (cons (car args)
		  (remove-token-type (cadr args) SalComma))
	    (list args))))
  #f)

; this could be (and key sexpr (@ comma key sexpr))
(defrule SalKargsRule (or (and SalKeyparam SalSexprRule
			       (+ SalComma SalKeyparam SalSexprRule))
			  (and SalKeyparam SalSexprRule))
  (lambda (args errf)
    (cons (car args)
	  (cons (cadr args)
		(if (and (pair? (cddr args))
			 (pair? (caddr args))
			 (token-unit-type=? (car (caddr args)) SalComma))
		    (remove-token-type (caddr args) SalComma)
		    (list)))))
  #f)

(defrule SalFunargsRule (or (and SalLParen SalRParen)
			    (and SalLParen SalPargsRule SalRParen)
			    (and SalLParen SalKargsRule SalRParen)
			    (and SalLParen SalPargsRule SalComma 
				 SalKargsRule SalRParen))
  (lambda (args errf) 
    ;; args is (:lp ... :rp) where ... are pargs and/or kargs with :co
    ;; separater. omit lp/rp tokens 
    ;;(print (list :funargs-> args))
    (set! args (cdr args)) ; remove :lp
    (let ((args1 (car args)))
      (set! args (cdr args)) ; pop args
      (if (token-unit-type=? args1 SalRParen)
	  (list)
	  (if (token-unit-type=? (car args) SalComma)
	      (append args1 (cadr args))
	      args1))))
  #f)

(define *sal-special-forms*
  '((make emit-make)
    (send emit-send)))

(defrule SalFuncallRule (and SalIdentifier SalFunargsRule)
  (lambda (args errf)
    ;; args is (<id> (<arg>...))
    (make-parse-unit SalFuncallRule
		     (cons (car args) (cadr args))
		     #f))
  (lambda (unit info errf)
    (let* ((form (parse-unit-parsed unit))
	   (func (emit (car form) info errf))
	   ;;(spec (assoc func *special-forms* ))
	   (spec #f))
    (if spec
	( (second spec) form info errf)
	(cons func (emit (cdr form) info errf)))))
  )

(define (is-op? x)
  (if (token-unit? x)
      (let ((typ (parse-unit-type x)))
	(and (SalOpType? typ )
	     (SalOpWeight typ)))
      #f))

(define (inf->pre inf)
  ;; this does NOT rewrite subexpressions because parser applies rules
  ;; depth-first so subexprs are already processed
  (let ((op #f)
	(lh #f)
	(rh #f)
	(w1 #f)
	)
    (if (pair? inf)
	(do ()
	    ((null? inf) lh)
	  (set! op (car inf))	  ; look at each element of inf
	  (set! inf (cdr inf))
	  (set! w1 (is-op? op))
	  (cond ((number? w1)	  ; found op
		 (do ((w2 #f)
		      (ok #t)
		      (li (list)))
		     ((or (null? inf) (not ok))
		      (set! rh (inf->pre (reverse li)))
		      (set! lh (if lh (list op lh rh)
				   (list op rh #f))))
		   (set! w2 (is-op? (car inf)))
		   (if (and w2 (<= w2 w1))
		       (set! ok #f)
		       (let ((i (car inf)))
			 (set! inf (cdr inf))
			 (set! li (cons i li))))))
		(else
		 (set! lh op))))
	inf)))

(defrule SalOpRule (or SalPlus SalMinus SalTimes SalDivide
		       SalMod SalExpt SalEqual SalNotEqual
		       SalLess SalGreater SalLessEqual SalGreaterEqual
		       SalGeneralEqual SalNot SalAnd SalOr)
  #f
  #f)

(defrule SalMexprRule (and SalTermRule (* SalOpRule SalTermRule))
  (lambda (args errf)
    (if (and (pair? (cadr args))
	     (is-op? (car (cadr args))))
	(let ((infix (cons (car args) (cadr args))))
	  (inf->pre infix))
	(car args)))
  #f)

(defrule SalTermRule (or (and SalMinus SalTermRule)
			 (and SalNot SalTermRule)
			 (and SalLParen SalMexprRule SalRParen)
			 SalIfExprRule SalFuncallRule SalArefRule
			 SalAtomRule SalListRule SalString)
  (lambda (args errf) 
    ;;(print (list #:term-> args))
    ;; "tag" terms so mexpr can tell the difference between funcalls
    ;; and mexprs
    (make-parse-unit SalTermRule
		     (if (pair? args)
			 (if (token-unit-type=? (car args) SalLParen )
			     (second args)
			     args)
			 args)
		     #f))
  (lambda (unit info errf)
    (emit (parse-unit-parsed unit) info errf))
  )

(defrule SalSexprRule (or SalMexprRule SalIfExprRule SalFuncallRule
			  SalArefRule SalListRule SalString
			  SalClass SalAtomRule))

;
;; Statements
;

(defrule SalPrintStatementRule
  (and SalPrint SalSexprRule (* SalComma SalSexprRule))
  (lambda (args errf)
    ;; args = (<print> <sexpr> ({<,> <sexpr>}*)
    (make-parse-unit SalPrintStatementRule
		     (cons (cadr args)
			   (remove-token-type (caddr args) SalComma))
		     #f))
  (lambda (unit info errf) 
    (let* ((form (list 'sal:print))
	   (tail form))
      (do ((args (parse-unit-parsed unit) (cdr args)) )
	  ((null? args)
	   form)
	(set-cdr! tail (list (emit (car args) info errf)))
	(set! tail (cdr tail))))))

(defrule SalSproutStatementRule 
  (and SalSprout SalSexprRule (@ SalComma SalSexprRule))
  (lambda (args errf)
    ;; args (<sprout> <sexpr> { #f | (<,> <sexpr>) } )
    ;;(print (list #:args-> args))
    (let ((opt (if (caddr args)
		   (remove-token-type (caddr args) SalComma)
		   #f)))
      (make-parse-unit SalSproutStatementRule
		       (list (cadr args) opt)
		       #f)))
  (lambda (unit info errf)
    (let ((subs (parse-unit-parsed unit)))
      (if (cadr subs)
	  `(sprout ,(emit (car subs) info errf)
		   ,(emit (cadr subs) info errf))
	  `(sprout ,(emit (car subs) info errf)))))
  )

(defrule SalSendStatementRule
  (and SalSend (or SalString SalIdentifier)
       (@ SalComma (or (and SalPargsRule SalComma SalKargsRule) 
		       SalPargsRule SalKargsRule )))
  (lambda (args errf)
    (print #:args-> args)
    ;; (<send> <msg> #f)
    ;; (<send> <msg> ( <,> (...)))
    (let ((rest (third args)))
      (if (not rest)
	  (set! rest (list))
	  (begin
	    (set! rest (second rest))
	    ;; (<arg> <arg2> ...)
	    ;; (<key> <arg> <key2> <arg2>)
	    ;; ((<arg> ...) <,> (<key> <arg> ...) )
	    (if (pair? (first rest)) ; positionals AND keys
		;; remove <,>
		(set! rest (append (first rest) (third rest))))))
      (make-parse-unit SalSendStatementRule
		       (cons (first args) (cons (second args) rest))
		       #f)))
  (lambda (unit info errf) 
    (map (lambda (e) (emit e info errf)) (parse-unit-parsed unit)))
  )

; (parse SalSendStatementRule (tokenize `((, SalSend "send" 0) (#x900 "mp:note" 24))) #f 0 #f display)
; (parse SalSendStatementRule (tokenize `((, SalSend "send" 0) (#x900 "mp:note" 24) (#x100 "," 22) (#xb00 "1" 6))) #f 0 #f display)
; (parse SalSendStatementRule (tokenize `((, SalSend "send" 0) (#x900 "mp:note" 24) (#x100 "," 22) (#xb00 "1" 6) (#x100 "," 22) (#xb00 "-99" 6))) #f 0 #f display)
; (parse SalSendStatementRule (tokenize `((, SalSend "send" 0) (#x900 "mp:note" 24) (#x100 "," 22) (#x1600 "ziz" 13) (#xb00 "1" 6) (#x100 "," 22) (#x1600 "pif" 13) (#xb00 "-99" 6))) #f 0 #f display)
; (parse SalSendStatementRule (tokenize `((, SalSend "send" 0) (#x900 "mp:note" 24) (#x100 "," 22) (#xb00 "1000" 6) (#x100 "," 22) (#x1600 "ziz" 13) (#xb00 "1" 6) (#x100 "," 22) (#x1600 "pif" 13) (#xb00 "-99" 6))) #f 0 #f display)

(defrule SalBindRule (or (and SalIdentifier SalEqual SalSexprRule)
			 SalIdentifier)
  (lambda (args errf)
     (if (pair? args)
	 (make-parse-unit SalBindRule
			  (list (first args) (third args))
			  #f)
	 (make-parse-unit SalBindRule
			  (list args 
				(make-parse-unit SalFalse "#f" #f)
				)
			  #f)))
  (lambda (unit info errf) 
    (map (lambda (e) (emit e info errf))
	 (parse-unit-parsed unit))))

;; "with ..." is NOT a statement

(defrule SalBindingsRule
  (and SalWith SalBindRule (* SalComma SalBindRule))
  (lambda (args errf)
    ;; remove WITH token
    (if (not (third args))
	(make-parse-unit SalBindingsRule
			 (list (second args))
			 #f)
	(make-parse-unit SalBindingsRule
			 (cons (second args)
			       (remove-token-type (third args)
						  SalComma))
			 #f)))
  (lambda (unit info errf) 
    ;; tell subforms that the context is a let bindings
    (let ((i (add-emit-info #:bindings #t info)))
      (map (lambda (e) (emit e i errf))
	   (parse-unit-parsed unit)))))

; (parse SalBindingsRule (tokenize `((, SalWith "with" 0) (,SalIdentifier "aaa" 24) )) #f 0 #f display)

; (parse SalBindingsRule (tokenize `((, SalWith "with" 0) (,SalIdentifier "aaa" 24)  (#x2804 "=" 12) (#xb00 "3" 14))) #f 0 #f display)

; (parse SalBindingsRule (tokenize `((, SalWith "with" 0) (,SalIdentifier "aaa" 24)  (#x2804 "=" 12) (#xb00 "3" 14) (#x100 "," 22) (,SalIdentifier "bbb" 24) (#x2804 "=" 12) (,SalIdentifier "aaa" 24) (#x1905 "+" 12) (#xb00 "3" 10))) #f 0 #f display)

;;;
;;; assignment (set)
;;;

(defrule SalAssignRule
  (and (or SalArefRule SalIdentifier)
       (or SalEqual SalLessEqual SalGreaterEqual
	   SalInc SalMul SalCol SalPre SalApp)
       SalSexprRule)
  (lambda (args errf)
    (make-parse-unit SalAssignRule args #f))
  )

(defrule SalAssignmentRule
  (and SalSet SalAssignRule (* SalComma SalAssignRule))
  (lambda (args errf)
    (if (not (third args))
	(make-parse-unit SalAssignmentRule
			 (list (second args))
			 #f)
	(make-parse-unit SalAssignmentRule
			 (cons (second args)
			       (remove-token-type (third args)
						  SalComma))
			 #f)))
  (lambda (unit info errf)
    (let ((assigns (parse-unit-parsed unit)))
      ;;(print (list #:emit-assignment assigns))
      (let* ((head (list 'begin ))
	     (tail head))
	(do ((iter assigns (cdr iter)))
	    ((null? iter)
	     ;; remove surrounding begin if only one form
	     (if (null? (cddr head)) 
		 (cadr head)
		 head))
	  (let* ((asgn (parse-unit-parsed (car iter)) )
		 (vref (emit (first asgn) info errf))
		 ;; dont emit the operator just check its type
		 (oper (parse-unit-type (second asgn)))
		 (expr (emit (third asgn) info errf))
		 (form #f))
	    ;;(print (list #:assignment asgn))
	    (cond ((SalType=? oper SalEqual)
		   (set! form expr))
		  ((SalType=? oper SalInc)
		   (set! form `(+ ,vref ,expr)))
		  ((SalType=? oper SalMul)
		   (set! form `(* ,vref ,expr)))
		  ((SalType=? oper SalCol)
		   (set! form `(append ,vref (list ,expr))))
		  ((SalType=? oper SalPre)
		   (set! form `(cons ,expr ,vref)))
		  ((SalType=? oper SalApp)
		   (set! form `(append ,vref ,expr)))
		  ((SalType=? oper SalLessEqual)
		   (set! form `(min ,vref ,expr)))
		  ((SalType=? oper SalGreaterEqual)
		   (set! form `(max ,vref ,expr))))
	    ;; if we are setting a list location then have to rewrite
	    ;; as a list setter. this WON'T work for AREFS...
	    (if (and (pair? vref) (eq? (first vref) 'list-ref))
		(set! form `(set-car! (list-tail ,(second vref)
						 ,(third vref))
				      ,form))
		(set! form `(set! ,vref ,form)))
	    (set-cdr! tail (list form))
	    (set! tail (cdr tail))
	    ))))))

; (parse SalAssignmentRule (tokenize '((16128 "set" 0) (24576 "foo" 4) (10244 "=" 8) (2816 "123" 10))) #f 0 #f #f)

; (parse SalAssignmentRule (tokenize '((16128 "set" 0) (24576 "foo" 4) (10244 "=" 8) (2816 "1" 10) (6405 "+" 12) (2816 "2" 14) (6405 "+" 16) (2816 "3" 18) (256 "," 19) (24576 "bar" 21) (11264 "+=" 25) (2816 "2" 28) (7174 "/" 30) (2816 "5" 32) (256 "," 33) (24576 "baz" 35) (12032 "*=" 39) (2816 "3" 42) (256 "," 43) (24576 "bif" 45) (11776 "&=" 49) (2816 "3" 52) (256 "," 53) (24576 "bof" 55) (12032 "*=" 59) (2816 "4" 62) (256 "," 63) (24576 "buf" 65) (12288 "^=" 69) (24576 "list" 72) (512 "(" 76) (2816 "9" 77) (768 ")" 78) (256 "," 79) (24576 "zuz" 81) (10500 "<=" 85) (2816 "4" 88) (256 "," 89) (24576 "zaz" 91) (10756 ">=" 95) (2816 "3" 98) ))  #f 0 #f #f)

(defrule SalBlockRule
  (and SalBegin (@ SalBindingsRule) (* SalStatementRule) SalEnd)
  (lambda (args errf)
    ;; args: (BEGIN [(<bindings>)] (...) END)
    ;;(print (list #:block-> args))
    (let ((vars (second args))
	  (body (third args)))
      (if (not vars) #f (set! vars (first vars)))
      (make-parse-unit SalBlockRule
		       (cons vars body)
		       #f)))
  (lambda (unit info errf)
    ;; ( <bindings> . <statements>)
    (let ((bloc (parse-unit-parsed unit)))
      (let ((vars (car bloc)) ; #<bindings> or #f
	    (body (emit (cdr bloc) info errf)))
	;; at some point this could pass var decls into (emit body) to
	;; catch unknown variable errors etc.
	;;(print (list #:vars-> vars))
	(if (not vars)
	    `(begin ,@body)
	    `(let* ,(emit vars info errf)
	       ,@body)))))
  )

;; FIX: Should WHEN and UNLESS be Commands ??

(defrule SalConditionalRule 
  (or (and SalIf SalSexprRule SalThen (@ SalStatementRule)
	   (@ SalElse SalStatementRule))
      (and SalWhen SalSexprRule SalStatementRule)
      (and SalUnless SalSexprRule SalStatementRule))
  (lambda (args errf)
    ;;(print (list #:if-> args))
    (let ((oper (first args))
	  (test (second args))
	  (data (list)))
      (if (token-unit-type=? oper SalIf)
	  (let ((clause (fourth args))
		(then #f)
		(else #f))
	    (if (not clause)
		(set! then (make-parse-unit SalFalse "#f" #f))
		(set! then (first clause)))
	    (set! clause (fifth args))
	    (if (not clause)
		(set! else (make-parse-unit SalFalse "#f" #f))
		(set! else (cadr clause)))
	    (set! data (list oper test then else))
	    )
	  (set! data (list oper test (third args))))
      (make-parse-unit SalConditionalRule data #f)))
  (lambda (unit info errf)
    ;; THIS METHOD CAN BE REMOVED...
    (let ((data (parse-unit-parsed unit)))
      ;;(print (list #:data-> data))
      (emit data info errf))))

;;;
;;;
;;;

(defrule SalStatementRule
  (or SalBlockRule 
      SalPrintStatementRule
      SalSproutStatementRule
      SalSendStatementRule
      SalAssignmentRule
      )
  #f
  #f)

#|
;; RENAME:
;; SalBindingsRule -> SalWithStatementRule
;; SalAssignmentRule -> SalSetStatementRule
;; SalBlockRule -> SalBeginEndStatementRule
;; DELETE: SalAssignerRule SalSetRule

(define SalTypes
  `((SalUntyped 0)
    (SAL_TOKEN_BEG *)
    (SAL_DELIM_BEG *)
    SalComma
    SalLParen
    SalRParen
    SalLCurly
    SalRCurly
    SalLBrace
    SalRBrace
    SAL_DELIM_END
    ;; Data
    (SAL_DATA_BEG *)
    SalString
    SAL_NUMBER_BEG
    SalInteger
    SalRatio
    SalFloat
    SAL_NUMBER_END
    SalKeyword
    SAL_BOOL_BEG
    ;; Special (hash) Notations
    (SAL_HASH_BEG *)
    SalTrue
    SalFalse
    SAL_BOOL_END
    SalQMark
    SAL_HASH_END
    (SAL_DATA_END *)
    ;; Named Parameters
    SalKeyparam
    ;; Classes
    SalClass
    ;; Operators... (data: op_weight)
    SAL_OP_BEG
    (SalPlus + 5)
    (SalMinus + 5)
    (SalTimes + 6)
    (SalDivide + 6)
    (SalMod + 5)
    (SalExpt + 7)
    (SalAnd + 2)
    (SalOr  + 1)
    (SalNot + 3)
    ;; ...relations
    SAL_RELATION_BEG
    (SalLess + 4)
    (SalGreater + 4)
    (SalNotEqual + 4)
    (SalGeneralEqual + 4)
    SAL_ASSIGNMENT_BEG
    (SalEqual + 4)
    (SalLessEqual  + 4)
    (SalGreaterEqual  + 4)
    SAL_RELATION_END
    (SAL_OP_END *)
    ;; ...assignment (starts at SalEqual)
    SalInc
    SalMul
    SalCol
    SalPre
    SalApp
    SAL_ASSIGNMENT_END
    ;; Literals... (data: command=110, statement=010 clausal=001)
    (SAL_LITERAL_BEG *)
    (SAL_STATEMENT_BEG *)
    (SAL_COMMAND_BEG *)
    ;; commands (statement starting word)
    (SalBegin  + 16)  ; 16 = SallockOpen
    SalChdir
    SalDefine
    SalExec
    SalIf
    SalLoad
    (SalLoop  + 16)
    SalOpen
    SalPlay
    SalPlot
    SalPrint
    (SalRun  + 16)
    SalSend
    SalSet
    SalSprout
    SalSystem
    SalUse
    SAL_COMMAND_END
    (SAL_CONSTITUENT_BEG *)
    ;; ...statement constituent parts
    SalElse
    (SalEnd    + 17) ; 17 = blockClose
    SalOutput
    SalReturn
    SalThen
    SalUnless
    SalUntil
    SalWait
    SalWhen
    SalWhile
    SalWith
    SAL_CONSTITUENT_END
    (SAL_STATEMENT_END *)
    (SAL_CLAUSAL_BEG *)
    ;; ...clausals
    SalAbove
    SalBelow
    SalBy
    SalDownto
    SalFinally
    SalFor
    SalFrom
    SalIn
    SalOver
    SalRepeat
    SalTo
    SAL_CLAUSAL_END
    (SAL_LITERAL_END *)
    ;; ...define types
    (SAL_DEFINE_BEG *)
    SalFunction
    SalProcess
    SalVariable
    SAL_DEFINE_END
    ;; Identifiers (variables, functions, obj.slot)
    (SAL_IDENTIFIER_BEG *)
    SalIdentifier
    SalSlotRef
    SAL_IDENTIFIER_END
    (SAL_TOKEN_END *)
    ;; RULES
    (SAL_RULE_BEG *)
    SalNumberRule
    SalBoolRule
    SalAtomRule
    SalListRule
    SalEltRule
    SalArefRule
    SalIfExprRule
    SalFuncallRule
    SalFunargsRule
    SalPargsRule
    SalKargsRule
    SalOpRule
    SalMexprRule
    SalTermRule
    SalSexprRule
    SalBindingsRule
    SalBindRule
    SalAssignmentRule
    SalAssignRule
    SalAssignerRule
    SalSetRule
    SalFunctionReturnRule
    SalProcessWaitRule
    SalBlockRule
    SalConditionalRule
    SalLoopStatementRule
    SalRunStatementRule
    SalSteppingRule
    SalTerminationRule
    SalPrintStatementRule
    SalExecStatementRule
    SalOpenStatementRule
    SalSendStatementRule
    SalSproutStatementRule
    SalOutputStatementRule
    SalLoadStatementRule
    SalSystemStatementRule
    SalChdirStatementRule
    SalPlayStatementRule
    SalPlotStatementRule
    SalDefineStatementRule
    SalStatementRule
    SalStatementSequenceRule
    SalDeclarationRule
    SalVarDeclRule
    SalFunDeclRule
    SalProcDeclRule
    SalProcessBodyRule
    ;; ...
    SAL_RULE_END
    (SAL_TYPE_END *)
 )
)

(define (sal-enums enum spec c?)
  (let ((num #f)
	(nam #f)
	(lsh #f))
    (cond ((pair? enum)
	   (set! nam (car enum))
	   (set! lsh (cadr enum)))
	  (else 
	   (set! nam enum)
	   (set! lsh 0)))
    (if c?
	(printf "~%  enum ~A {~%    // generated by (sal-enums )~%" nam)
	(printf "~%(begin~%  ;; generated by (sal-enums)~%"))
    (do ((tail spec (cdr tail))
	 (this #f)
	 (name #f)
	 (data #f)
	 (enum #f))
	((null? tail)
	 #f)
      (set! this (car tail))
      (if (pair? this)
	  (begin (set! name (car this))
		 (cond ((number? (cadr this))
			(set! num (cadr this)))
		       ((eq? (cadr this) '+)
			(set! num (+ num 1)))
		       ((eq? (cadr this) '*)
			(set! num num))
		       (else (error "second element not num * or +")))
		 (if (not (null? (cddr this)))
		     (set! data (caddr this))
		     (set! data 0)))
	  (begin
	    (set! name this)
	    (set! num (+ num 1))
	    (set! data 0)))
      (set! enum (+ (arithmetic-shift num lsh) data))
      (if (not c?)
	  (printf "  (define ~A #x~X)~%" name enum)
	  (begin 
	    (printf "    ~A = 0x~X" name enum)
	    (if (not (null? (cdr tail))) (printf ","))
	    (printf "~%"))))
    (if c? (printf "  };~%")
	(printf "  )~%"))
    )
  )
      
(sal-enums 'SalDataTags '((SalBlockOpen 16) SalBlockClose) #f)
(sal-enums 'SalDataTags '((SalBlockOpen 16) SalBlockClose) #t)
(sal-enums '(SalTypes 8) SalTypes #)
(sal-enums '(SalTypes 8) SalTypes #t)
(begin
  (keyword-style 'prefix)
  (define saltests (read-file "~/saltests"))
  (define (runtests rule tests nums)
    (do ((tail tests (cdr tail))
	 (i 0 (+ i 1)))
	((null? tail) (values))
      (if (or (null? nums) (member (+ i 1) nums))
	  (let* ((test (car tail))
		 (name (car test))
		 (toks (tokenize (cdr test))))
	    (printf "~%test[~A] ~S :~%" (+ i 1) name)
	    (let ((form (parse rule toks #f 0 #f #f)))
	      (if (parse-error? form)
		  (printf "ERROR ~S~%" form)
		  (printf "=> ~S~%" form)))))))
  (define (gettest n) (list-ref saltests (- n 1)))
  (define (testsal . args) (runtests SalPrintStatementRule saltests args ))
  (testsal)
  )

|#

