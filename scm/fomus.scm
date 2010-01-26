;;; **********************************************************************
;;; Copyright (C) 2009, Rick Taube and David Psenicka
;;; This program is free software; you can redistribute it and/or modify
;;; it under the terms of the Lisp Lesser Gnu Public License. The text of
;;; this agreement is available at http://www.cliki.net/LLGPL            
;;; **********************************************************************

(define-constant fomus_par_none 0)
(define-constant fomus_par_entry 1)
(define-constant fomus_par_list 2)
(define-constant fomus_par_setting 3)
(define-constant fomus_par_settingval 4)
(define-constant fomus_par_locfile 5)
(define-constant fomus_par_locline 6)
(define-constant fomus_par_loccol 7)
(define-constant fomus_par_import 8)
(define-constant fomus_par_import_settingval 9)
(define-constant fomus_par_export 10)
(define-constant fomus_par_export_settingval 11)
(define-constant fomus_par_clef 12)
(define-constant fomus_par_clef_settingval 13)
(define-constant fomus_par_staff 14)
(define-constant fomus_par_staff_clefs 15)
(define-constant fomus_par_staff_settingval 16)
(define-constant fomus_par_percinst 17)
(define-constant fomus_par_percinst_template 18)
(define-constant fomus_par_percinst_id 19)
(define-constant fomus_par_percinst_imports 20)
(define-constant fomus_par_percinst_export 21)
(define-constant fomus_par_percinst_settingval 22)
(define-constant fomus_par_inst 23)
(define-constant fomus_par_inst_template 24)
(define-constant fomus_par_inst_id 25)
(define-constant fomus_par_inst_staves 26)
(define-constant fomus_par_inst_imports 27)
(define-constant fomus_par_inst_export 28)
(define-constant fomus_par_inst_percinsts 29)
(define-constant fomus_par_inst_settingval 30)
(define-constant fomus_par_part 31)
(define-constant fomus_par_part_id 32)
(define-constant fomus_par_part_inst 33)
(define-constant fomus_par_part_settingval 34)
(define-constant fomus_par_partmap 35)
(define-constant fomus_par_partmap_part 36)
(define-constant fomus_par_partmap_metapart 37)
(define-constant fomus_par_partmap_settingval 38)
(define-constant fomus_par_metapart 39)
(define-constant fomus_par_metapart_id 40)
(define-constant fomus_par_metapart_partmaps 41)
(define-constant fomus_par_metapart_settingval 42)
(define-constant fomus_par_measdef 43)
(define-constant fomus_par_measdef_id 44)
(define-constant fomus_par_measdef_settingval 45)
(define-constant fomus_par_list_percinsts 46)
(define-constant fomus_par_list_insts 47)
(define-constant fomus_par_settingval_percinsts 48)
(define-constant fomus_par_settingval_insts 49)
(define-constant fomus_par_region 50)
(define-constant fomus_par_region_voice 51)
(define-constant fomus_par_region_voicelist 52)
(define-constant fomus_par_region_time 53)
(define-constant fomus_par_region_gracetime 54)
(define-constant fomus_par_region_duration 55)
(define-constant fomus_par_region_pitch 56)
(define-constant fomus_par_region_dynlevel 57)
(define-constant fomus_par_region_mark 58)
(define-constant fomus_par_region_settingval 59)
(define-constant fomus_par_time 60)
(define-constant fomus_par_gracetime 61)
(define-constant fomus_par_duration 62)
(define-constant fomus_par_pitch 63)
(define-constant fomus_par_dynlevel 64)
(define-constant fomus_par_voice 65)
(define-constant fomus_par_note_settingval 66)
(define-constant fomus_par_meas 67)
(define-constant fomus_par_meas_measdef 68)
(define-constant fomus_par_markid 69)
(define-constant fomus_par_markval 70)
(define-constant fomus_par_mark 71)
(define-constant fomus_par_noteevent 72)
(define-constant fomus_par_restevent 73)
(define-constant fomus_par_markevent 74)
(define-constant fomus_par_events 75)

(define-constant fomus_act_none 0)
(define-constant fomus_act_set 1)
(define-constant fomus_act_inc 2)
(define-constant fomus_act_dec 3)
(define-constant fomus_act_mult 4)
(define-constant fomus_act_div 5)
(define-constant fomus_act_start 6)
(define-constant fomus_act_append 7)
(define-constant fomus_act_add 8)
(define-constant fomus_act_remove 9)
(define-constant fomus_act_end 10)
(define-constant fomus_act_clear 11)
(define-constant fomus_act_queue 12)
(define-constant fomus_act_cancel 13)
(define-constant fomus_act_resume 14)

;; for 
;; (define-macro (fms:errwrap body)
;;   `(begin ,body (when (ffi_fms_err) (error ">>> Error: FOMUS error"))))

;; (define-macro (fms:with-optkeys llst . body)
;;   (let ((args (if (list? (car llst)) (caar llst) (car llst)))
;; 	(ins (if (list? (car llst)) (cadar llst) #f))
;; 	(oth (cadr llst))
;; 	(keys (cddr llst)))
;;     `(let ,(do ((l keys (cdr l))
;; 		(r '()))
;; 	       ((null? l) (reverse! (cons `(,oth (quote ())) r)))
;; 	     (push (let ((x (car l))) (if (pair? x) x (list x #f))) r))
;;        ,@(if ins (list ins) '())
;;        (do ((l ,args (cddr l)))
;; 	   ((null? l))
;; 	 (let ((s (car l)))
;; 	   (unless (keyword? s) (ffi_fms_err) (error "invalid keyword argument ~S" s))
;; 	   (when (null? (cdr l)) (ffi_fms_err) (error "missing keyword value for ~S" s))
;; 	   (let ((v (cadr l)))
;; 	     (cond ,@(do ((k keys (cdr k))
;; 			  (r '()))
;; 			 ((null? k) (reverse! (cons `(else (set! ,oth (cons s (cons v ,oth)))) r)))
;; 		       (let ((y (let ((w (car k))) (if (pair? w) (car w) w)))) (push `((eq? s ,(symbol->keyword y)) (set! ,y v)) r)))))))
;;        ,@body)))

(define (fms:trim-colon str)
  (if (char=? (string-ref str 0) #\:) (substring str 1) str))
(define (fms:string-downcase str)
  (do ((i 0 (1+ i)) (x (copy str)))
      ((>= i (string-length str)) x)
    (string-set! x i (char-downcase (string-ref x i)))))
(define (fms:force-list thing)
  (if (list? thing) thing (list thing)))
(define (fms:force-dlist thing) ; for object definitions, already expects list
  (if (pair? thing) (if (list? (car thing)) thing (list thing)) thing))

(define (fms:make-import . args)
  (vector 'import
	  args))
(define (fms:make-export . args)
  (vector 'export
	  args))
(define (fms:make-clef . args)
  (vector 'clef
	  args))
(define (fms:make-staff . args)
  (with-optkeys (args (clefs '()) &allow-other-keys)
		(vector 'staff
			(map (lambda (x) (apply fms:make-clef x)) clefs) ; 1
			&allow-other-keys)))
(define (fms:make-measdef . args)
  (with-optkeys (args id &allow-other-keys)
		(vector 'measdef
			id ; 1
			&allow-other-keys)))
(define (fms:make-percinst . args)
  (with-optkeys (args template id (imports '()) export &allow-other-keys)
		(vector 'percinst
			template ; 1
			id ; 2
			(map (lambda (x) (apply fms:make-import x)) imports) ; 3
			(if (list? export) (apply fms:make-export export) export) ; 4
			&allow-other-keys)))
(define (fms:make-inst . args)
  (with-optkeys (args template id (staves '()) (imports '()) export (percinsts '()) &allow-other-keys)
		(vector 'inst
			template ; 1
			id ; 2
			(map (lambda (x) (apply fms:make-staff x)) staves) ; 3
			(map (lambda (x) (apply fms:make-import x)) imports) ; 4
			(if (list? export) (apply fms:make-export export) export) ; 5
			(map (lambda (x) (if (list? x) (apply fms:make-percinst x) x)) percinsts) ; 6
			&allow-other-keys)))
(define (fms:make-part . args)
  (with-optkeys (args id inst &allow-other-keys)
		(vector 'part
			id ; 1
			(if (list? inst) (apply fms:make-inst inst) inst) ; 2
			&allow-other-keys)))
(define (fms:make-partmap . args)
  (with-optkeys (args part metapart &allow-other-keys)
		(vector 'partmap
			(if (list? part) (apply fms:make-part part) part) ; 2
			(if (list? metapart) (apply fms:make-metapart metapart) metapart) ; 3
			&allow-other-keys)))
(define (fms:make-metapart . args)
  (with-optkeys (args id (parts '()) &allow-other-keys)
		(vector 'metapart
			id ; 1
			(map (lambda (x) (if (list? x) (apply fms:make-partmap x) x)) parts) ; 2
			&allow-other-keys)))

(define (fms:send par act val)
  (letrec ((sendmult (lambda (lpar lact lval) ; if a list, "send" everything IN the list without actually sending a list
		       (do ((e (if (list? lval) lval (list lval)) (cdr e)))
			   ((null? e))
			 (fms:send lpar lact (car e)))))
	   (sendstr (lambda (strval valpar)
		      (do ((e strval (cddr e)))
			  ((null? e))
			(fms:send fomus_par_setting fomus_act_set (car e))
			(fms:send valpar fomus_act_set (let ((b (cadr e))) (case b ((#f) "no") ((#t) "yes") (else b))))))))
    (cond
     ((not val) (ffi_fms_act par act))
     ((integer? val) (ffi_fms_ival par act val))
     ((rational? val) (ffi_fms_rval par act (numerator val) (denominator val)))
     ((real? val) (ffi_fms_fval par act val))
     ((symbol? val) (ffi_fms_sval par act (fms:trim-colon (symbol->string val))))
     ((string? val) (ffi_fms_sval par act val))
     ((list? val)
      (ffi_fms_act fomus_par_list fomus_act_start)
      (do ((e val (cdr e)))
	  ((null? e))
	(fms:send fomus_par_list fomus_act_add (car e)))
      (ffi_fms_act fomus_par_list fomus_act_end)
      (ffi_fms_act par act))
     ((vector? val)
      (case (vector-ref val 0)
	((measdef) ; ids, names, and other things are sent separately because they don't behave like normal settings
	 (when (vector-ref val 1) (fms:send fomus_par_measdef_id fomus_act_set (vector-ref val 1)))
	 (sendstr (vector-ref val 2) fomus_par_measdef_settingval)
	 (ffi_fms_act par act))
	((part)
	 (when (vector-ref val 1) (fms:send fomus_par_part_id fomus_act_set (vector-ref val 1)))
	 (when (vector-ref val 2) (fms:send fomus_par_part_inst fomus_act_set (vector-ref val 2)))
	 (sendstr (vector-ref val 3) fomus_par_part_settingval)
	 (ffi_fms_act par act))
	((metapart)
	 (when (vector-ref val 1) (fms:send fomus_par_metapart_id fomus_act_set (vector-ref val 1)))
	 (when (vector-ref val 2) (sendmult fomus_par_metapart_partmaps fomus_act_add (vector-ref val 2)))
	 (sendstr (vector-ref val 3) fomus_par_metapart_settingval)
	 (ffi_fms_act par act))
	((inst)
	 (when (vector-ref val 1) (fms:send fomus_par_inst_template fomus_act_set (vector-ref val 1)))
	 (when (vector-ref val 2) (fms:send fomus_par_inst_id fomus_act_set (vector-ref val 2)))
	 (when (vector-ref val 3) (sendmult fomus_par_inst_staves fomus_act_add (vector-ref val 3)))
	 (when (vector-ref val 4) (sendmult fomus_par_inst_imports fomus_act_add (vector-ref val 4)))
	 (when (vector-ref val 5) (fms:send fomus_par_inst_export fomus_act_set (vector-ref val 5)))
	 (when (vector-ref val 6) (sendmult fomus_par_inst_percinsts fomus_act_add (vector-ref val 6)))
	 (sendstr (vector-ref val 7) fomus_par_inst_settingval)
	 (ffi_fms_act par act))
	((percinst)
	 (when (vector-ref val 1) (fms:send fomus_par_percinst_template fomus_act_set (vector-ref val 1)))
	 (when (vector-ref val 2) (fms:send fomus_par_percinst_id fomus_act_set (vector-ref val 2)))
	 (when (vector-ref val 3) (sendmult fomus_par_percinst_imports fomus_act_add (vector-ref val 3)))
	 (when (vector-ref val 4) (fms:send fomus_par_percinst_export fomus_act_set (vector-ref val 4)))
	 (sendstr (vector-ref val 5) fomus_par_percinst_settingval)
	 (ffi_fms_act par act))
	((partmap)
	 (when (vector-ref val 1) (fms:send fomus_par_partmap_part fomus_act_set (vector-ref val 1)))
	 (when (vector-ref val 2) (fms:send fomus_par_partmap_metapart fomus_act_set (vector-ref val 2)))
	 (sendstr (vector-ref val 3) fomus_par_partmap_settingval)
	 (ffi_fms_act par act))
	((clef)
	 (sendstr (vector-ref val 1) fomus_par_clef_settingval)
	 (ffi_fms_act par act))
	((staff)
	 (when (vector-ref val 1) (sendmult fomus_par_staff_clefs fomus_act_add (vector-ref val 1)))
	 (sendstr (vector-ref val 2) fomus_par_staff_settingval)
	 (ffi_fms_act par act))
	((import)
	 (sendstr (vector-ref val 1) fomus_par_import_settingval)
	 (ffi_fms_act par act))
	((export)
	 (sendstr (vector-ref val 1) fomus_par_export_settingval)
	 (ffi_fms_act par act))))
     (else (ffi_fms_err) (error "invalid FOMUS input")))))

(define (fms:entry time dur part voice grace marks sets)
  (fms:send fomus_par_time fomus_act_set time)
  (fms:send fomus_par_duration fomus_act_set dur)
  (when part (fms:send fomus_par_part fomus_act_set part))
  (fms:send fomus_par_voice fomus_act_set voice)
  (when grace (fms:send fomus_par_gracetime fomus_act_set grace))
  (when marks
	(do ((e (fms:force-list marks) (cdr e)))
	    ((null? e))
	  (let ((args (fms:force-list (car e))))
	    (unless (or (string? (car args)) (symbol? (car args))) (ffi_fms_err) (error "expected a string or symbol for mark id"))
	    (fms:send fomus_par_markid fomus_act_set (pop args))
	    (unless (null? args)
		    (unless (or (number? (car args)) (string? (car args)) (symbol (car args)))
			    (ffi_fms_err) (error "expected a number, string or symbol for first mark argument"))
		    (fms:send fomus_par_markval fomus_act_add (pop args)))
	    (unless (null? args)
		    (unless (or (number? (car args)) (string? (car args)) (symbol (car args)))
			    (ffi_fms_err) (error "expected a number, string or symbol for second mark argument"))
		    (fms:send fomus_par_markval fomus_act_add (pop args)))
	    (fms:send fomus_par_mark fomus_act_add #f))))
  (when sets
	(do ((e sets (cddr e)))
	    ((null? e))
	  (unless (or (string? (car e)) (symbol? (car e))) (ffi_fms_err) (error "expected a string or symbol for filename argument"))
	  (fms:send fomus_par_setting fomus_act_set (car e))
	  (fms:send fomus_par_note_settingval fomus_act_set (cadr e)))))

(define (fms:note . args)
  (with-optkeys (args (time 0) (dur 1) (pitch 60) part (voice 1) (dyn 0.5) grace (marks '()) (sets '()) &allow-other-keys)
		(unless (number? time) (ffi_fms_err) (error "expected a number for time argument"))
		(unless (number? dur) (ffi_fms_err) (error "expected a number for dur argument"))
		(unless (or (number? pitch) (string? pitch) (symbol? pitch)) (ffi_fms_err) (error "expected a number or string for pitch argument"))
		(unless (or (string? part) (symbol? part) (eq? part #f)) (ffi_fms_err) (error "expected a string or symbol for part argument"))
		(unless (or (number? voice) (list? voice)) (ffi_fms_err) (error "expected a number or list of numbers for voice argument"))
		(unless (number? dyn) (ffi_fms_err) (error "expected a number for dyn argument"))
		(unless (or (number? grace) (eq? grace #f)) (ffi_fms_err) (error "expected a number for grace argument"))
		(unless (or (list? marks) (eq? marks #f) (string? marks) (symbol? marks)) (ffi_fms_err) (error "expected a list for marks argument"))
		(unless (list? sets) (ffi_fms_err) (error "expected a list for sets argument"))
		(fms:send fomus_par_pitch fomus_act_set pitch)
		(when dyn (fms:send fomus_par_dynlevel fomus_act_set dyn))
		(fms:entry time dur part voice grace marks (append &allow-other-keys sets))
		(fms:send fomus_par_noteevent fomus_act_add #f))
  #t)

(define (fms:rest . args)
  (with-optkeys (args (time 0) (dur 1) part (voice 1) grace (marks '()) (sets '()) &allow-other-keys)
		(unless (number? time) (ffi_fms_err) (error "expected a number for time argument"))
		(unless (number? dur) (ffi_fms_err) (error "expected a number for dur argument"))
		(unless (or (string? part) (symbol? part) (eq? part #f)) (ffi_fms_err) (error "expected a string or symbol for part argument"))
		(unless (or (number? voice) (list? voice)) (ffi_fms_err) (error "expected a number or list of numbers for voice argument"))
		(unless (or (number? grace) (eq? grace #f)) (ffi_fms_err) (error "expected a number for grace argument"))
		(unless (or (list? marks) (eq? marks #f) (string? marks) (symbol? marks)) (ffi_fms_err) (error "expected a list for marks argument"))
		(unless (list? sets) (ffi_fms_err) (error "expected a list for sets argument"))
		(fms:entry time dur part voice grace marks (append &allow-other-keys sets))
		(fms:send fomus_par_restevent fomus_act_add #f))
  #t)

(define (fms:mark . args)
  (with-optkeys (args (time 0) (dur 1) part (voice 1) grace (marks '()) (sets '()) &allow-other-keys)
		(unless (number? time) (ffi_fms_err) (error "expected a number for time argument"))
		(unless (number? dur) (ffi_fms_err) (error "expected a number for dur argument"))
		(unless (or (string? part) (symbol? part) (eq? part #f)) (ffi_fms_err) (error "expected a string or symbol for part argument"))
		(unless (or (number? voice) (list? voice)) (ffi_fms_err) (error "expected a number or list of numbers for voice argument"))
		(unless (or (number? grace) (eq? grace #f)) (ffi_fms_err) (error "expected a number for grace argument"))
		(unless (or (list? marks) (eq? marks #f) (string? marks) (symbol? marks)) (ffi_fms_err) (error "expected a list for marks argument"))
		(unless (list? sets) (ffi_fms_err) (error "expected a list for sets argument"))
		(fms:entry time dur part voice grace marks (append &allow-other-keys sets))
		(fms:send fomus_par_markevent fomus_act_add #f))
  #t)

(define (fms:meas . args)
  (with-optkeys (args (time 0) (dur 1) (sets '()) &allow-other-keys)
		(unless (number? time) (ffi_fms_err) (error "expected a number for time argument"))
		(unless (number? dur) (ffi_fms_err) (error "expected a number for dur argument"))
		(unless (list? sets) (ffi_fms_err) (error "expected a list for sets argument"))
		(when time (fms:send fomus_par_time fomus_act_set time))
		(when dur (fms:send fomus_par_duration fomus_act_set dur))
		(let ((s (append &allow-other-keys sets)))
		  (when s (fms:send fomus_par_meas_measdef fomus_act_set (apply fms:make-measdef s))))
		(fms:send fomus_par_meas fomus_act_add #f))
  #t)

(define (fms:measdef . args)
  (with-optkeys (args (sets '()) &allow-other-keys)
		(unless (list? sets) (ffi_fms_err) (error "expected a list for sets argument"))
		(fms:send fomus_par_measdef fomus_act_add (apply fms:make-measdef (append &allow-other-keys sets))))
  #t)

(define (fms:part . args) 
  (with-optkeys (args (sets '()) &allow-other-keys)
		(unless (list? sets) (ffi_fms_err) (error "expected a list for sets argument"))
		(fms:send fomus_par_part fomus_act_add (apply fms:make-part (append &allow-other-keys sets))))
  #t)

(define (fms:metapart . args) 
  (with-optkeys (args (sets '()) &allow-other-keys)
		(unless (list? sets) (ffi_fms_err) (error "expected a list for sets argument"))
		(fms:send fomus_par_metapart fomus_act_add (apply fms:make-metapart (append &allow-other-keys sets))))
  #t)

(define (fms:inst . args) 
  (with-optkeys (args (sets '()) &allow-other-keys)
		(unless (list? sets) (ffi_fms_err) (error "expected a list for sets argument"))
		(fms:send fomus_par_inst fomus_act_add (apply fms:make-inst (append &allow-other-keys sets))))
  #t)

(define (fms:percinst . args) 
  (with-optkeys (args (sets '()) &allow-other-keys)
		(unless (list? sets) (ffi_fms_err) (error "expected a list for sets argument"))
		(fms:send fomus_par_percinst fomus_act_add (apply fms:make-percinst (append &allow-other-keys sets))))
  #t)

(define (fms:setting set val . append)
  (unless (or (string? set) (symbol? set)) (ffi_fms_err) (error "expected a string or symbol for set argument"))
  (unless (member append '(() (#t) (#f))) (ffi_fms_err) (error "expected a boolean for append argument"))
  (fms:send fomus_par_setting fomus_act_set set)
  (fms:send fomus_par_settingval (if (member append '(() (#f))) fomus_act_set fomus_act_append) (case val ((#f) "no") ((#t) "yes") (else val)))
  #t)

(define (fms:load-score filename)
  (unless (string? filename) (error "expected a string for filename argument"))
  (ffi_fms_load filename)
  #t)

(define (fms:new-score filename)
  (unless (string? filename) (error "expected a string for filename argument"))
  (ffi_fms_new filename)
  #t)

(define (fms:select-score filename)
  (unless (string? filename) (error "expected a string for filename argument"))
  (ffi_fms_select filename)
  #t)

(define (fms:clear-score)
  (ffi_fms_clear)
  #t)

(define (fms:run)
  (ffi_fms_run)
  #t)

(define (fms:save-score filename)
  (unless (string? filename) (error "expected a string for filename argument"))
  (ffi_fms_save filename)
  #t)

(define (fms:delete-score)
  (ffi_fms_free)
  #t)

(define (fms:open-score filename . args)
  (unless (string? filename) (error "expected a string for filename argument"))
  (with-optkeys (args (percinsts '()) (insts '()) (parts '()) (metaparts '()) (measdefs '()) (sets '()) (clear #t) (new #t) (run #t) &allow-other-keys)
		(unless (list? percinsts) (error "expected a list for percinsts argument"))
		(unless (list? insts) (error "expected a list for insts argument"))
		(unless (list? parts) (error "expected a list for parts argument"))
		(unless (list? metaparts) (error "expected a list for metaparts argument"))
		(unless (list? measdefs) (error "expected a list for measdefs argument"))
		(unless (list? sets) (error "expected a list for sets argument"))
		(unless (boolean? clear) (error "expected a boolean for clear argument"))
		(unless (boolean? new) (error "expected a boolean for new argument"))
		(unless (boolean? run) (error "expected a boolean for run argument"))
		(let ((f (member (fms:string-downcase filename) '("" "fomus"))))
		  (if new
		      (if f (fms:new-score "") (fms:new-score filename))
		      (unless f (fms:select-score filename))))
		(when clear (fms:clear-score))
		(do ((a (append &allow-other-keys sets) (cddr a)))
		    ((null? a))
		  (fms:setting (car a) (cadr a)))
		(map (lambda (x) (apply fms:percinst x)) (fms:force-dlist percinsts))
		(map (lambda (x) (apply fms:inst x)) (fms:force-dlist insts))
		(map (lambda (x) (apply fms:part x)) (fms:force-dlist parts))
		(map (lambda (x) (apply fms:metapart x)) (fms:force-dlist metaparts))
		(map (lambda (x) (apply fms:measdef x)) (fms:force-dlist measdefs))
		(ffi_fms_open_score run))
  #t)

(define-macro (with-fomus args . body)
  (unless (list? args) (error "expected a list for args argument"))
  `(begin
     (fms:open-score ,@args)
     ,@body
     (ffi_fms_close_score)))
