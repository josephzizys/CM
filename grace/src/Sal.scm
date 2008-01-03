;;; **********************************************************************
;;; Copyright (C) 2006 Rick Taube
;;; This program is free software; you can redistribute it and/or   
;;; modify it under the terms of the Lisp Lesser Gnu Public License.
;;; See http://www.cliki.net/LLGPL for the text of this agreement.
;;; **********************************************************************

;;; $Revision: 1364 $
;;; $Date: 2007-08-07 09:39:39 -0500 (Tue, 07 Aug 2007) $

;
;;; Tokens
;
 
(define-record token type string position)

(define-record-printer (token t p)
  (fprintf p "#<t x~X ~S>" (token-type t) (token-string t)))

(define (list->token l)
  (if (eq? (car l) 't) 
      (apply make-token (cdr l))
      (apply make-token l)))

(define (tokenize l) (map list->token l))
(define (first-token toks) (car toks))
(define (rest-tokens toks) (cdr toks))
(define (null-tokens? toks) (null? toks))

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

(define-record parse-error string position)
(define-record-printer (parse-error e p)
  (fprintf p "#<parse-error ~S (@ ~S)>"
	   (parse-error-string e)
	   (parse-error-position e)))

;
;; parse units
;

(define-record parse-unit type parsed position)

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

;; emit methods can access/pass information up/down the emit subcall
;; chain by adding things to the info parameter.

(define (get-emit-info name info)
  (let ((x (assoc name info)))
    (and x (cdr x))))

(define (add-emit-info name data info)
  (cons (cons name data) info))

(define (set-emit-info! name data info)
  ;; nconc data to end of info. this allows subforms to pass info back
  ;; up to calling forms.
  (let ((i (assoc name info)))
    (if (not i) (error "no info for " name))
    (set-cdr! i data)))

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

(define (simple-unit-parser type)
  ;; return a parse unit that simply holds its subforms
  (lambda (args errf)
    (make-parse-unit type args #f)))

(define (simple-unit-emitter func)
  ;; return an emitter that emits a lisp form for each subunit with
  ;; the name of the statement optionally replaced by func name
  (lambda (unit info errf)
    ;; create an identical list and then modify
    (let* ((data (append (parse-unit-parsed unit) (list)))
	   (head data))	
      ;; replace sal statement name with function name
      (if func 
	  (begin (set-car! data func)
		 (set! data (cdr data))))
      ;; replace each unit by its emitted lisp expression
      (do ((tail data (cdr tail)))
	  ((null? tail) head)
	(set-car! tail (emit (car tail) info errf))))))

;
;;; the parser
;

(define *maxtokpos* #f)

(define (parse pattern tokens . args)
  ;; returns a lisp expression or a parse-error
  (let ((junk-allowed #f)
	(trace #f)
	(info (list)))
    (call/cc
     (lambda (errf)
       (call-with-values 
	   (lambda ()
	     (set! *maxtokpos* 0)
	     (parser pattern tokens #f 0 trace errf))
	 (lambda (success results remains) 
	   (if (and success (or (null? remains) junk-allowed)) 
	       (emit results
		     ;; top-level info is syntax to emit
		     (add-emit-info #:syntax #:scheme info)
		     errf)
	       (make-parse-error "Illegal statement: "
				 *maxtokpos*))))))))

(define (parser pat tokens force-and level trace errf)
  (if trace (printf "~%parse[~A]: pattern=~S tokens=~S" level pat tokens))
  (or (null-tokens? tokens)
      (set! *maxtokpos* (max *maxtokpos* (token-position (first-token tokens)))))
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
						     (token-position tok))
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


;;; The parser attempts to match rule patterns against (typed) tokens
;;; in the stream its parsing. the lower eight bits are ignored by the
;;; comparison function and may store info about the typed entity.

(begin
  ;; generated by (sal-enums)
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
  (define SalUnquote #x1500)
  (define SalSplice #x1600)
  (define SAL_HASH_END #x1700)
  (define SAL_DATA_END #x1700)
  (define SalKeyparam #x1800)
  (define SalClass #x1900)
  (define SAL_OP_BEG #x1a00)
  (define SalPlus #x1b05)
  (define SalMinus #x1c05)
  (define SalTimes #x1d06)
  (define SalDivide #x1e06)
  (define SalMod #x1f05)
  (define SalExpt #x2007)
  (define SalAnd #x2102)
  (define SalOr #x2201)
  (define SalNot #x2303)
  (define SAL_RELATION_BEG #x2400)
  (define SalLess #x2504)
  (define SalGreater #x2604)
  (define SalNotEqual #x2704)
  (define SalGeneralEqual #x2804)
  (define SAL_ASSIGNMENT_BEG #x2900)
  (define SalEqual #x2a04)
  (define SalLessEqual #x2b04)
  (define SalGreaterEqual #x2c04)
  (define SAL_RELATION_END #x2d00)
  (define SAL_OP_END #x2d00)
  (define SalInc #x2e00)
  (define SalMul #x2f00)
  (define SalCol #x3000)
  (define SalPre #x3100)
  (define SalApp #x3200)
  (define SAL_ASSIGNMENT_END #x3300)
  (define SAL_LITERAL_BEG #x3300)
  (define SAL_STATEMENT_BEG #x3300)
  (define SAL_COMMAND_BEG #x3300)
  (define SalBegin #x3410)
  (define SalChdir #x3500)
  (define SalDefine #x3600)
  (define SalExec #x3700)
  (define SalIf #x3800)
  (define SalLoad #x3900)
  (define SalLoop #x3a10)
  (define SalOpen #x3b00)
  (define SalPlay #x3c00)
  (define SalPlot #x3d00)
  (define SalPrint #x3e00)
  (define SalRun #x3f10)
  (define SalSend #x4000)
  (define SalSet #x4100)
  (define SalSprout #x4200)
  (define SalSystem #x4300)
  (define SalUse #x4400)
  (define SAL_COMMAND_END #x4500)
  (define SAL_CONSTITUENT_BEG #x4500)
  (define SalElse #x4600)
  (define SalEnd #x4711)
  (define SalOutput #x4800)
  (define SalReturn #x4900)
  (define SalThen #x4a00)
  (define SalUnless #x4b00)
  (define SalUntil #x4c00)
  (define SalWait #x4d00)
  (define SalWhen #x4e00)
  (define SalWhile #x4f00)
  (define SalWith #x5000)
  (define SAL_CONSTITUENT_END #x5100)
  (define SAL_STATEMENT_END #x5100)
  (define SAL_CLAUSAL_BEG #x5100)
  (define SalAbove #x5200)
  (define SalBelow #x5300)
  (define SalBy #x5400)
  (define SalDownto #x5500)
  (define SalFinally #x5600)
  (define SalFor #x5700)
  (define SalFrom #x5800)
  (define SalIn #x5900)
  (define SalOver #x5a00)
  (define SalRepeat #x5b00)
  (define SalTo #x5c00)
  (define SAL_CLAUSAL_END #x5d00)
  (define SAL_LITERAL_END #x5d00)
  (define SAL_DEFINE_BEG #x5d00)
  (define SalFunction #x5e00)
  (define SalProcess #x5f00)
  (define SalVariable #x6000)
  (define SAL_DEFINE_END #x6100)
  (define SAL_IDENTIFIER_BEG #x6100)
  (define SalIdentifier #x6200)
  (define SalSlotRef #x6300)
  (define SAL_IDENTIFIER_END #x6400)
  (define SAL_TOKEN_END #x6400)
  (define SAL_RULE_BEG #x6400)
  (define SalNumberRule #x6500)
  (define SalBoolRule #x6600)
  (define SalAtomRule #x6700)
  (define SalListRule #x6800)
  (define SalEltRule #x6900)
  (define SalArefRule #x6a00)
  (define SalIfExprRule #x6b00)
  (define SalUnquoteRule #x6c00)
  (define SalFuncallRule #x6d00)
  (define SalFunargsRule #x6e00)
  (define SalPargsRule #x6f00)
  (define SalKargsRule #x7000)
  (define SalOpRule #x7100)
  (define SalMexprRule #x7200)
  (define SalTermRule #x7300)
  (define SalSexprRule #x7400)
  (define SalBindingsRule #x7500)
  (define SalBindRule #x7600)
  (define SalAssignmentRule #x7700)
  (define SalAssignRule #x7800)
  (define SalAssignerRule #x7900)
  (define SalSetRule #x7a00)
  (define SalFunctionReturnRule #x7b00)
  (define SalProcessWaitRule #x7c00)
  (define SalBlockRule #x7d00)
  (define SalConditionalRule #x7e00)
  (define SalLoopStatementRule #x7f00)
  (define SalRunStatementRule #x8000)
  (define SalSteppingRule #x8100)
  (define SalTerminationRule #x8200)
  (define SalPrintStatementRule #x8300)
  (define SalExecStatementRule #x8400)
  (define SalOpenStatementRule #x8500)
  (define SalSendStatementRule #x8600)
  (define SalSproutStatementRule #x8700)
  (define SalOutputStatementRule #x8800)
  (define SalLoadStatementRule #x8900)
  (define SalSystemStatementRule #x8a00)
  (define SalChdirStatementRule #x8b00)
  (define SalPlayStatementRule #x8c00)
  (define SalPlotStatementRule #x8d00)
  (define SalDefineStatementRule #x8e00)
  (define SalStatementRule #x8f00)
  (define SalStatementSequenceRule #x9000)
  (define SalDeclarationRule #x9100)
  (define SalVarDeclRule #x9200)
  (define SalFunDeclRule #x9300)
  (define SalProcDeclRule #x9400)
  (define SalProcessBodyRule #x9500)
  (define SAL_RULE_END #x9600)
  (define SAL_TYPE_END #x9600)
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
	      (let* ((i (add-emit-info #:list #t info))
		     (l (emit sub i errf))
		     (q #f))	
		(if (eq? (get-emit-info #:list i)  #:unquote)
		    (set! q (list 'quasiquote l))
		    (set! q (list 'quote l)))
		;; if in a bindings copy the constant list to avoid user
		;; side effecting constant (quoted) data.
		(if (get-emit-info #:bindings info)
		    `(append ,q (list))
		    q)))
	  (emit sub info errf))))
  )

(defrule SalUnquoteRule (and (or SalUnquote SalSplice) SalSexprRule)
  (simple-unit-parser SalUnquoteRule)
  (lambda (unit info errf)
    (let* ((subs (parse-unit-parsed  unit))
	   (unq? (token-unit-type=? (car subs) SalUnquote))
	   (lis? (get-emit-info #:list info)))
      (if (not lis?) 
	  ( errf (make-parse-error
		  (if unq? "#$ outside of list." 
		      "#^ outside of list." )
		  (parse-unit-position (car subs)))))
      (let ((expr (emit (second subs) info errf)))
	;; tell superior list that we have an unquote
	(set-emit-info! #:list #:unquote info)
	(if unq?
	    (list 'unquote expr)
	    (list 'unquote-splicing expr))))))

(defrule SalEltRule (or SalAtomRule SalListRule SalString SalUnquoteRule)
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
			  SalClass SalAtomRule)
  #f
  #f)

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
		       SalPargsRule
		       SalKargsRule)))
  (lambda (args errf)
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
		       (cons (second args) rest)
		       (parse-unit-position (car args))
		       )))
  (lambda (unit info errf) 
    (let* ((data (emit (parse-unit-parsed unit) info errf))
	   (mesg (first data)))
      ;; check args for mesg
      (expand-send (car data) (cdr data)
		   (lambda (str . args)
		     ( errf (make-parse-error
			     (apply sprintf str args)
			     (parse-unit-position unit))))))))

(defrule SalExecStatementRule (and SalExec SalSexprRule)
  (lambda (args errf) (second args))
  #f)

(defrule SalLoadStatementRule (and SalLoad SalSexprRule)
  (simple-unit-parser SalLoadStatementRule)
  (simple-unit-emitter 'sal:load))

(defrule SalChdirStatementRule (and SalChdir SalSexprRule)
  (simple-unit-parser SalChdirStatementRule)
  (simple-unit-emitter 'sal:chdir))

(defrule SalSystemStatementRule (and SalSystem SalSexprRule)
  (simple-unit-parser SalSystemStatementRule)
  (simple-unit-emitter 'sal:system))

(defrule SalOutputStatementRule (and SalOutput SalSexprRule)
  (simple-unit-parser SalOutputStatementRule)
  (simple-unit-emitter 'sal:output))

(defrule SalPlotStatementRule
  (and SalPlot (or (and SalKeyparam SalSexprRule) SalSexprRule)
       (* SalComma (or (and SalKeyparam SalSexprRule)
		       SalSexprRule)))
  (lambda (args errf)
    (make-parse-unit
     SalPlotStatementRule
     (cons (first args)
	   (cons (second args)
		 (remove-token-type (third args)
				    SalComma)))
     #f))
  (lambda (unit info errf)
    '(fix-me plot))
  )

(defrule SalProcessWaitRule (and SalWait SalSexprRule)
  (simple-unit-parser SalProcessWaitRule)
  (lambda (unit info errf)
    (let ((data (parse-unit-parsed unit)))
      (if (not (get-emit-info #:run info))
	  ( errf (make-parse-error "wait statement outside run block"
				   (parse-unit-position
				    (car data)))))
      (emit data info errf))))


(defrule SalFunctionReturnRule
  (and SalReturn SalSexprRule)
  (simple-unit-parser SalFunctionReturnRule)
  (lambda (unit info errf)
    (let ((data (parse-unit-parsed unit)))
      (if (not (get-emit-info #:function info))
	  ( errf (make-parse-error "return statement outside function"
				   (parse-unit-position
				    (car data)))))
      ;; tell calling function that we have a return statemen
      (set-emit-info! #:function #:return info)
      (emit data info errf))))

;;
;; WITH variable bindings (not a statement)
;;

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

;;
;; iteration
;;

(define (sal-parse-stepping args errf)
  ;; return a stepping clause used by loop and run.  each clause is
  ;; represented by one or more five element lists:
  ;; (<var> <bind> <loop> <step> <stop>)
  ;; when <var> is a variable to bind, <bind> is its binding list
  ;; value, <loop> is its assignment statement at the top of the loop,
  ;; <step> is its incrementing expression at the bottom of the loop,
  ;; and <stop> is an expression that, if true, stops the iteration.
  (let ((data (list))
	(user #f)
	(expr #f)
	(temp #f)
	(stop #f)
	(then #f)
	(bool #f)
	(tail #f)
	(loop #f)
	(size #f)
	(mode #f)
	(goal #f)
	(from #f)
	(step #f))
    (cond ((token-unit-type=? (first args) SalRepeat)
	   ;; (repeat <expr>)
	   (set! expr (emit (second args) (list) errf))
	   (set! temp (gensym "temp"))
	   (set! stop (gensym "stop"))
	   (set! data (list (list stop expr #f #f #f)
			    (list temp 0 #f
				  `(set! ,temp (+ ,temp 1))
				  `(>= ,temp ,stop)))))
	  ((token-unit-type=? (third args) SalEqual)
	   ;; (for <v> = <expr> #f)
	   ;; (for <v> = <expr> (then <expr>))
	   (set! user (emit (second args) (list) errf))
	   (set! expr (emit (fourth args) (list) errf))
	   (set! then (fifth args))
	   (if then
	       (begin
		 (set! then (emit (cadr then) (list) errf))
		 (set! bool (gensym "bool"))
		 (set! loop `(if ,bool
				 (begin (set! ,bool #f) 
					(set! ,user ,expr))
				 (set! ,user ,then)))
		 (set! data (list (list bool #t #f #f #f))))
	       (set! loop `(set! ,user ,expr)))
	   (set! data (append data (list (list user #f loop #f #f)))))
	  ((token-unit-type=? (third args) SalIn)
	   ;; (for <v> in <expr>)
	   (set! user (emit (second args) (list) errf))
	   (set! expr (emit (fourth args) (list) errf))
	   (set! tail (gensym "tail"))
	   (set! data (list (list tail expr #f 
				  `(set! ,tail (cdr ,tail))
				  `(null? ,tail))
			    (list user #f `(set! ,user (car ,tail)) 
				  #f #f))))
	  (else
	   (set! size (length args))
	   (set! user (emit (second args) (list) errf))
	   ;; the LAST element always #f or (by <expr>)
	   (set! step (list-ref args (- size 1)))
	   (if step
	       (set! step (emit (cadr step) (list) errf))
	       (set! step 1))
	   (cond ((= size 6)
		  ;; (for <var> from <expr> (LIMIT <expr>) (by <expr>))
		  ;; (for <var> from <expr> (LIMIT <expr>) #f)
		  ;; (for <var> from <expr> #f #f)
		  (set! from (emit (fourth args) (list) errf))
		  (if (fifth args)
		      (begin (set! mode (car (fifth args)))
			     (set! goal (emit (cadr (fifth args))
					      (list) errf)))
		      (begin (set! mode #f)
			     (set! goal #f))))
		 (else
		  ;; (for <var> LIMIT <expr> (by <expr>))
		  ;; (for <var> LIMIT <expr> #f)
		  (set! from 0)
		  (set! mode (third args))
		  (set! goal (emit (fourth args) (list) errf))))
	   (if (not (number? step))
	       (let ((var (gensym "step")))
		 (set! data (append data (list (list var step #f #f #f))))
		 (set! step var)))
	   (if (not (number? from))
	       (let ((var (gensym "from")))
		 (set! data (append data (list (list var from #f #f #f))))
		 (set! from var)))
	   (if goal
	       (if (not (number? goal))
		   (let ((var (gensym "goal")))
		     (set! data (append data 
					(list (list var goal #f #f #f))))
		     (set! goal var))))
	   (if (not mode)
	       (set! step `(set! ,user (+ ,user ,step)))
	       (cond ((token-unit-type=? mode SalBelow)
		      (set! stop `(>= ,user ,goal))
		      (set! step `(set! ,user (+ ,user ,step))))
		     ((token-unit-type=? mode SalTo)
		      (set! stop `(> ,user ,goal))
		      (set! step `(set! ,user (+ ,user ,step))))
		     ((token-unit-type=? mode SalAbove)
		      (set! stop `(<= ,user ,goal))
		      (set! step `(set! ,user (- ,user ,step))))
		     ((token-unit-type=? mode SalDownto)
		      (set! stop `(< ,user ,goal))
		      (set! step `(set! ,user (- ,user ,step))))))
	   (set! data (append data 
			      (list (list user from #f step stop))))))
    (make-parse-unit SalSteppingRule data #f)))

(defrule SalSteppingRule
  (or (and SalRepeat SalSexprRule)
      (and SalFor SalIdentifier SalEqual SalSexprRule 
	   (@ SalThen SalSexprRule))
      (and SalFor SalIdentifier SalIn SalSexprRule)
      ;;(and SalFor SalIdentifier SalOver SalSexprRule (@ SalBy SalSexprRule))
      (and SalFor SalIdentifier SalFrom SalSexprRule
	   (@ (or SalBelow SalTo SalAbove SalDownto) SalSexprRule)
	   (@ SalBy SalSexprRule))
      (and SalFor SalIdentifier 
	   (or SalBelow SalTo SalAbove SalDownto) SalSexprRule
	   (@ SalBy SalSexprRule)))
  sal-parse-stepping
  #f)

(defrule SalTerminationRule
  (or (and SalWhile SalSexprRule) (and SalUntil SalSexprRule))
  (simple-unit-parser SalTerminationRule)
  #f)

(define (sal-emit-iteration unit info errf)
    ;; DATA: (<loop|run> <with> (<stepping>) (<stop>) (<actions>) <finally>)
  (let* ((data (parse-unit-parsed unit))
	 (run? #f)
	 ;; forms
	 (bind (list))
	 (loop (list))
	 (step (list))
	 (stop (list))
	 (done (list))
	 )
    ;(print (list #:sal-emit-iteration data))
    ;; tell subforms what type of iteration we are
    (cond ((token-unit-type=? (car data) SalLoop)
	   (set! info (add-emit-info #:loop #t info)))
	  (else
	   (if (not (get-emit-info #:process info))
	       ( errf (make-parse-error "run statement outside process" 
					(parse-unit-position
					 (car data))) ))
	   (set! info (add-emit-info #:run #t info))
	   (set! run? #t)))
    ;; pop loop|run tag off data
    (set! data (cdr data))
    ;; add user's with variables to binding list
    (if (first data)
	(set! bind (append bind (emit (first data) info errf))))
    ;; map over the stepping clauses adding iteration forms
    (do ((tail (second data) (cdr tail)))
	((null? tail) #f)
      ;; each stepping clause contains a list of 5-element lists:
      ;; ( (<var> <bind> <loop> <step> <stop>) ...)
      (do ((clauses (parse-unit-parsed (car tail)) (cdr clauses)))
	  ((null? clauses) #f)
	(let ((clause (first clauses)))
	  ;; add stepping vars to binding list
	  ;;(print (list #:clause-> clause))
	  (set! bind (append bind (list (list (first clause) 
					      (second clause)))))
	  (if (third clause)
	      (set! loop (append loop (list (third clause)))))
	  (if (fourth clause)
	      (set! step (append step (list (fourth clause)))))
	  (if (fifth clause)
	      (set! stop (append stop (list (fifth clause))))))))
    ;; add user's body statements to loop forms
    (do ((tail (fourth data) (cdr tail)))
	((null? tail) #f)
      (set! loop (append loop (list (emit (car tail) info errf)))))
    ;; add stepping forms after all the user's actions.
    (set! loop (append loop step))
    ;; add user's termination clauses to stop forms
    (do ((tail (third data) (cdr tail)))
	((null? tail) #f)
      ;; data is (<while until> <statement>)
      (let* ((data (parse-unit-parsed (car tail)))
	     (form (emit (second data) info errf)))
	(if (token-unit-type=? (car data) SalWhile)
	    (set! form `(not , form)))
	(set! stop (append stop (list form)))))
    ;; turn all stop forms into one valid lisp expression
    (if (pair? stop)
	(if (null? (cdr stop))
	    (set! stop (car stop)) ; only one
	    (set! stop (cons 'or stop))) ; or together
	(begin
	  ;;(warn "A (possibly) non-terminating iteration is being defined.")
	  (set! stop #f)))
    ;; add finally clause, defaults to #f
    (if (fifth data)
	(set! done (emit (fifth data) info errf))
	(set! done #f))
    
    (if (not run?)
	`(let* ,bind (do () (,stop , done) ,@loop))
	(let* ((timevar (gensym "time"))
	       (waitvar (gensym "wait"))
	       (errorvar (gensym "error"))
	       (abortvar (gensym "abort")))
	  `(let* ,bind
	     ;; the process closure
	     (lambda (,timevar)
	       (let* ((,waitvar 0)
		      (elapsed (lambda () ,timevar))
		      (wait (lambda (x) (set! ,waitvar x))))
		 ;; wrap run statement in error handler
		 (call-with-current-continuation
		  (lambda (,abortvar)
		    (with-exception-handler
		     (lambda (,errorvar)
		       (print-error
			(sprintf 
			 ">>> Error: ~A~%    process aborted at time ~S~%"
			 ((condition-property-accessor 'exn 'message) 
			  ,errorvar)
			 ,timevar
			 ))
		       (,abortvar -2)  ;; abort and remove process
		       )
		     ;; the run statements
		     (lambda ()
		       (cond (,stop ,done -1)
			     (else ,@loop ,waitvar)))))))))
	  ))))

(defrule SalLoopStatementRule
  (and (or SalLoop SalRun)
       (@ SalBindingsRule)
       (* SalSteppingRule )
       (* SalTerminationRule)
       (+ SalStatementRule)
       (@ SalFinally SalStatementRule)
       SalEnd)
  (lambda (args errf)
    (let ((type (first args))
	  (vars (second args))
	  (step (third args))
	  (stop (fourth args))
	  (body (fifth args))
	  (done (sixth args)))
      ;; #f or (<bindings)
      (if vars (set! vars (car vars)))
      (if done (set! done (cadr done)))
      (make-parse-unit SalLoopStatementRule
		       (list type vars step stop body done)
		       (parse-unit-position type))))
  (lambda (unit info errf)
    (sal-emit-iteration unit info errf ))
  )

;;;

(defrule SalFunDeclRule
  (and SalIdentifier
       (or (and SalLParen SalRParen)
	   (and SalLParen 
		SalIdentifier (* SalComma SalIdentifier)
		SalRParen))
       SalStatementRule)
  (lambda (args errf)
    ;;(print (list #:funcdecl-> args))
    (let ((name (first args))
	  (pars (second args))
	  (body (third args)))
      (if (= (length pars) 2)
	  ;; pars: ( <(>  <)> )
	  (set! pars (list))
	  ;; pars: ( <(> <sym> (<,> <sym> ...) <)> )
	  (set! pars (cons (second pars)
			   (remove-token-type (third pars) SalComma))))
      (make-parse-unit SalFunDeclRule (list name pars body) #f)) ))

(defrule SalDefineStatementRule
  (and SalDefine
       (or (and SalVariable SalBindRule (* SalComma SalBindRule))
	   (and SalFunction SalFunDeclRule)
	   (and SalProcess SalFunDeclRule)))
  (lambda (args errf)
    ;; args: (<define> (<TYPE> ...))
;    (print (list #:define-args-> args))
    ;; flush <define> and set args to (<TYPE> ...)
    (set! args (second args)) ; 
    (let ((type (first args)))
      (if (token-unit-type=? type SalVariable)
	  ;; flatten args to (<type> <bind> ...)
	  (set! args
		(cons type (cons (second args)
				 (remove-token-type (third args)
						    SalComma)))))
      (make-parse-unit SalDefineStatementRule args #f)))
  (lambda (unit info errf)
    (let* ((data (parse-unit-parsed unit))
	   (type (first data))
	   (head (list 'begin))
	   (tail head))
      ;; data: (<variable> <bind> ....) OR (<function> <fundecl>)
      (cond ((token-unit-type=? type SalVariable)
	     ;; rest of data is list of bindings
	     (do ((rest (cdr data) (cdr rest)))
		 ((null? rest) #f)
	       (let* ((bind (emit (car rest) info errf))
		      (var (car bind))
		      (str (sprintf "Variable: ~A = " var)))
	       (set-cdr! tail (list (cons 'define bind)
				    `(sal:print ,str ,var)))
	       (set! tail (cddr tail)))))
	    (else ;; function or process. second element is
		  ;; <SalFunDeclRule>: (<name> <params> <body>)
	     (let* ((data (parse-unit-parsed (second data)))
		    (name (emit (first data) info errf))
		    (pars (emit (second data) info errf))
		    ;; copy pars for possible sideeffect
		    (decl (cons name (append pars (list))))
		    (body (third data))
		    (mesg #f)
		    (form #f)
		    )
;	       (print (list #:procdata-> name pars body))

	       ;; decl is (funcname {arg}*). if last arg contains
	       ;; "..." then its an &rest arg: replace last cdr of
	       ;; decl with arg minus the "..."
	       (if (not (null? (cdr decl)))
		   (let* ((tail (list-tail decl (- (length decl) 2)))
			  (name (symbol->string (cadr tail)))
			  (size (string-length name)))
		     (if (and (> size 3)
			      (string=? (substring name (- size 3)) 
					"..."))
			 (set-cdr! tail
				   (string->symbol
				    (substring name 0 (- size 3)))))))
	       (cond ((token-unit-type=? type SalFunction)
		      (set! info (add-emit-info #:function #t info))
		      (set! form (emit body info errf))
		      ;(print (list #:after-emitinfo-> info))
		      (if (eq? #:return (get-emit-info #:function info))
			  (set! form
				`(call-with-current-continuation
				  (lambda (return) ,form))))
		      (set! form (list 'define decl form))
		      (set! mesg "Function: "))
		     ((token-unit-type=? type SalProcess)
		      (set! info (add-emit-info #:process #t info))
		      (set! form (emit body info errf))
		      (set! form (list 'define decl form))
		      (set! mesg "Process: ")))
	       (do ((args (string-append mesg (symbol->string name) " ("))
		    (tail pars (cdr tail)))
		   ((null? tail)
		    (set! mesg `(print-message
				 ,(string-append args ")\n"))))
		 (set! args (string-append args
					   (symbol->string (car tail))))
		 (if (not (null? (cdr tail)))
		     (set! args (string-append args ", "))))
	       ;; message printed before definition to help track
	       ;; compiler warnings
	       (set-cdr! head (list mesg form))
	       )))
      head))
  )

;;;
;;;
;;;

(defrule SalStatementRule
  (or SalDefineStatementRule
      SalBlockRule 
      SalPrintStatementRule
      SalSproutStatementRule
      SalSendStatementRule
      SalAssignmentRule
      SalConditionalRule
      SalLoopStatementRule
      SalProcessWaitRule
      SalFunctionReturnRule
      SalSystemStatementRule
      SalOutputStatementRule
      SalPlotStatementRule
      SalLoadStatementRule
      SalChdirStatementRule
      SalExecStatementRule
      )
  #f
  #f)

(defrule SalStatementSequenceRule (+ SalStatementRule)
  (lambda (args errf)
    (make-parse-unit SalStatementSequenceRule
		     args (parse-unit-position (first args))))
  (lambda (unit info errf)
    (cons 'begin (emit (parse-unit-parsed unit) info errf))))

;;;
;;; Sal Runtime Support
;;;
    
(define *sal-string* #f)
(define *sal-tokens* #f)
(define *sal-output* #f)
(define *sal-parse* SalStatementRule)

(define (sal string rule tokens trace?)
  (set! *sal-string* string)
  (set! *sal-tokens* (tokenize tokens))
  (if (= rule 0)
      (set! rule *sal-parse*)
      #f)
  (set! *sal-output* (parse rule *sal-tokens* #f 0 #f #f))
  (cond ((parse-error? *sal-output*)
	 (print-sal-error *sal-string* *sal-output*))
	(trace?
	 (pp *sal-output*)
	 )
	(else
	 (eval *sal-output*)
	 ))
  (values))

(define (print-sal-error str err)
  (let* ((len (string-length str))
	 (pos (parse-error-position err))
	 (beg (- pos 1))
	 (end 0)
	 )
    ;; isolate line containing error position
    (do ((f #f))
	((or f (= beg -1)) #f)
      (if (char=? (string-ref str beg) #\newline)
	  (set! f #t)
	  (set! beg (- beg 1))))
    ;; beg now 1+ nearest leftward #\Return or at 0
    (set! beg (+ beg 1))
    ;; find end of error line
    (set! end pos)
    (do ((f #f))
	((or f (= end len)) #f)
      (if (char=? (string-ref str end) #\newline)
	  (set! f #t)
	  (set! end (+ end 1))))
    (print-error
     (string-append ">>> Error: " 
		    (parse-error-string err)
		    (make-string 1 #\newline)
		    (substring str beg end) 
		    (make-string 1 #\newline)
		    (let* ((siz (- pos beg))
			   (pad (make-string (+ siz 2) #\space)))
		      (string-set! pad siz #\^)
		      (string-set! pad (+ siz 1) #\newline)
		      pad)))
    (values)))


(define *print-decimals* 3)

(define (sal:print . args)
  (letrec ((printer 
	    (lambda (thing)
	      (cond ((not thing)
		     (print-message "#f") )
		    ((null? thing)
		     (print-message "{}"))
		    ((pair? thing) 
		     (print-message "{" )
		     (do ((tail thing (cdr tail)))
			 ((null? tail) #f)
		       (printer (car tail)) 
		       (if (not (null? (cdr tail)))
			   (print-message " ")))
		     (print-message "}" ))
		    ((eq? thing #t)
		     (print-message "#t" ))
		    ((number? thing)
		     (if (inexact? thing)
			 (if (eq? *print-decimals* #t)
			     (print-message (number->string thing))
			     (print-message (number->string
					     (decimals thing *print-decimals*))))
			 (print-message (number->string thing))))
		    ((string? thing)
		     (print-message thing))
		    (else
		     (print-message (sprintf "~S" thing)))))))
    (do ((tail args (cdr tail)))
	((null? tail)
	 (print-message "\n"))
      (printer (car tail)))
    (values)))

(define (sal:chdir path)
  (change-directory path)
  (values))

(define (sal:load file)
  (let ((f (file-exists? file)))
    (if (not f)
	(print-error (string-append ">>> Error: file \""
				    file
				    "\"does not exist\n"))
	(let ((l (string-length file)))
	  (if (and (> l 4) (substring=? file ".sal" (- l 4)))
	      (load-sal-file file)
	      (load file))))
    (values)))

(define (sal:open . args)
  (print-error ">>> Error: open command not implemented.\n"))

(define (sal:output . args)
  (print-error ">>> Error: output command not implemented.\n"))

(define (sal:plot . args)
  (print-error ">>> Error: plot command not implemented.\n"))

(define (sal:system . args)
  (print-error ">>> Error: system command not implemented.\n"))

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
    SalUnquote
    SalSplice
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
    SalUnquoteRule
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
(Sal-enums 'SalDataTags '((SalBlockOpen 16) SalBlockClose) #t)
(sal-enums '(SalTypes 8) SalTypes #f)
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

