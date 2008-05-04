;;; **********************************************************************
;;; Copyright (C) 2007, 2008 Todd Ingalls, Rick Taube.
;;; This program is free software; you can redistribute it and/or modify
;;; it under the terms of the Lisp Lesser Gnu Public License. The text of
;;; this agreement is available at http://www.cliki.net/LLGPL            
;;; **********************************************************************

;;#ifdef PORTCSOUND
;;#include <CsoundLib/csound.h> 
;;#else
;;typedef double MYFLT;
;;#endif

#>
#include "Csound.h"

void cs_send_score_event (int type, int len, C_word lyst) {
  MYFLT buf[len];
  char typ = (type==2) ? 'f' : 'i';
  String str = String::empty;
  int pos=-1;
  int i=0;
  for ( ; C_SCHEME_END_OF_LIST != lyst; lyst = C_u_i_cdr( lyst ) ) {
    if (i==len) break;
    C_word w = C_u_i_car( lyst );
    if ( C_immediatep(w) ) {
      if ( C_truep(C_fixnump(w)) ) {
	buf[i++] = (MYFLT)C_unfix(w);
      }
      else
        buf[i++] = 0.0;
    }
    else if ( C_truep(C_blockp(w)) && C_truep( C_flonump( w ) )) {
      buf[i++] = (MYFLT)C_flonum_magnitude( w );
    }
    else if ( C_truep(C_blockp(w)) && C_truep( C_stringp( w ) )) {
      pos=i;  // position of string parameter
      str = String(C_c_string(w), C_header_size(w));
      buf[i++] = 0.0; // pad the pars values
      printf("stringpar=%s\n", str.toUTF8());
    }								  
    else {
      buf[i++] = 0.0;
    }
  }
  CsoundScoreEv* ev=new CsoundScoreEv(typ,len,buf,str,pos);
  ((GraceApp *)GraceApp::getInstance())->getCsoundPort()->sendScoreEvent( ev);
}

void cs_score_mode(bool b) {
  ((GraceApp *)GraceApp::getInstance())->getCsoundPort()->setScoreMode(b);
}

void cs_record_mode(bool b) {
  ((GraceApp *)GraceApp::getInstance())->getCsoundPort()->setRecordMode(b);
}

void cs_record_start(float f) {
  ((GraceApp *)GraceApp::getInstance())->getCsoundPort()->setRecordStart(f);
}

void cs_trace_mode(bool b) {
  ((GraceApp *)GraceApp::getInstance())->getCsoundPort()->setTraceMode(b);
}

void cs_clear_score() {
  ((GraceApp *)GraceApp::getInstance())->getCsoundPort()->clearScore();
}

void cs_print_score(float start, float end) {
  ((GraceApp *)GraceApp::getInstance())->getCsoundPort()->printScore(start,end);
}

void cs_play_score(float start, float end, float shift) {
  ((GraceApp *)GraceApp::getInstance())->getCsoundPort()->playScore(start,end,shift);
}

<#

(define (cs:score val) ((foreign-lambda void "cs_score_mode" bool) val))

(define (cs:record val) 
  (if (boolean? val)
      ((foreign-lambda void "cs_record_mode" bool) val)
      (if (and (number? val) (>= val 0))
	  (begin
	    ((foreign-lambda void "cs_record_start" float) val)
	    ((foreign-lambda void "cs_record_mode" bool) #t))
	  (error "value not boolean or number > 0" val))))

(define (cs:trace val) ((foreign-lambda void "cs_trace_mode" bool) val))

(define (cs:clear) ((foreign-lambda void "cs_clear_score") ))

(define (cs:i . args)
  ;; args can 1 or more values, or exacly one argument that is a list.
  (if (not (null? args))
      (begin (if (and (null? (cdr args))
		      (pair? (car args)))
		 (set! args (car args)))
	     ((foreign-lambda void "cs_send_score_event" 
			      int int scheme-object)
	      1
	      (length args)
	      args)))
  (values))

(define (cs:f . args) 
  (if (not (null? args))
      (begin (if (and (null? (cdr args))
		      (pair? (car args)))
		 (set! args (car args)))
	     ((foreign-lambda void "cs_send_score_event"
			      int int scheme-object)
	      2
	      (length args)
	      args)))
  (values))

(define (cs:print . args)
  (with-optkeys (args (start 0) (end #f))
    (if (not end) (set! end -1))
    ( (foreign-lambda void "cs_print_score" float float)
      start end)))

(define (cs:play . args)
  (with-optkeys (args (start 0) (end #f) (shift 0))
    (if (not end) (set! end -1))
    ( (foreign-lambda void "cs_play_score" float float float)
      start end shift)))

(define-send-message cs:i (&rest))
(define-send-message cs:f (&rest))
(define-send-message cs:score (&rest))
(define-send-message cs:record (&rest))
(define-send-message cs:trace  (&rest))
(define-send-message cs:clear ())
(define-send-message cs:print (&rest))
(define-send-message cs:play (&rest))

;;; EOF

