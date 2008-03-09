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
  int i=0;
  for ( ; C_SCHEME_END_OF_LIST != lyst; lyst = C_u_i_cdr( lyst ) ) {
    if (i==len) break;
    C_word w = C_u_i_car( lyst );
    if ( C_immediatep(w) ) {
      if ( C_truep(C_fixnump(w)) ) {
	// printf("FIX: buf[%d]=%d\n", i, C_unfix(w) );
	buf[i++] = (MYFLT)C_unfix(w);
      }
      else
        buf[i++] = 0.0;
    }
    else if ( C_truep(C_blockp(w)) && C_truep( C_flonump( w ) )) {
      // printf("FLO: buf[%d]=%f\n", i, (float)C_flonum_magnitude( w ));
      buf[i++] = (MYFLT)C_flonum_magnitude( w );
    }
    else {
      buf[i++] = 0.0;
    }
  }
  ((GraceApp *)GraceApp::getInstance())->getCsoundPort()->sendScoreEvent( ((type==2) ? 'f' : 'i'), len, buf);  
}

void cs_clear_score () {
  ((GraceApp *)GraceApp::getInstance())->getCsoundPort()->clearScore();
}

<#

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

;(define (cs:print . args)
;  (let ((beg 0)
;	(end 31536000))
;    (when (not (null? args))
;      (if (not (null? (cdr args)))
;	  (if (number? (cadr args)) (set! end (cadr args))
;	      (error "end time not a number:" (cadr args))))
;      (if (not (null? (car args)))
;	  (if (number? (car args)) (set! beg (car args))
;	      (error "start time not a number:" (car args)))))
;    ((foreign-lambda void "cs_print_score" float float) beg end)
;    (values)))

(define (cs:clear)
  ( (foreign-lambda void "cs_clear_score" ) )
  )

;(define (cs:write)
;  ( (foreign-lambda void "cs_write_score" ) )
;  )

;(define cs:note cs:i)
;(define cs:func cs:f)
;(define-send-message cs:print ((#:from 0) (#:to 31536000)))
;(define-send-message cs:write ())

(define-send-message cs:i (&rest))
(define-send-message cs:f (&rest))
(define-send-message cs:clear ())

;;; EOF
