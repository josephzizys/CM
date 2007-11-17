/* Generated from ChickenBridge.scm by the CHICKEN compiler
   http://www.call-with-current-continuation.org
   2007-11-16 14:22
   Version 2.731 - macosx-unix-gnu-ppc - [ manyargs dload ptables applyhook ]
(c)2000-2007 Felix L. Winkelmann | compiled 2007-10-29 on galen.local (Darwin)
   command line: ChickenBridge.scm -output-file ChickenBridge.cpp -quiet
   unit: grace
*/

#include "chicken.h"



/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

#include "Grace.h"
#include "Scheme.h"
#include "Midi.h"

//
// Console Window code
//

void print_message(char * st)
{
// ((GraceApp *)GraceApp::getInstance())->getConsole()->printMessage( String(st), true);
   printf("%s", st);
}

void print_error(char * st)
{
// ((GraceApp *)GraceApp::getInstance())->getConsole()->printError( String(st), true);
   printf("%s", st);
}

//
// MIDI Port code
//

void mp_note(double time, double dur, float k, float v, float c) {
 ((GraceApp *)GraceApp::getInstance())->midiport->sendNote(time, dur, k, v, c); 
}

void mp_on(double time, float k, float v, float c) {
 ((GraceApp *)GraceApp::getInstance())->midiport->sendOn(time, k, v, c);
}

void mp_off(double time, float k, float v, float c) {
 ((GraceApp *)GraceApp::getInstance())->midiport->sendOff(time, k, v, c);
}

void mp_prog(double time, float p, float c) {
 ((GraceApp *)GraceApp::getInstance())->midiport->sendProg(time, p, c);
}

void mp_ctrl(double time, float n, float v, float c) {
 ((GraceApp *)GraceApp::getInstance())->midiport->sendCtrl(time, n, v, c);
}

//
// Scheduler code
//

void scheduler_sprout( C_word proc, double time, int id)
{
  ((GraceApp *)
   GraceApp::getInstance())->schemeProcess->addNode(0, time, proc, id);
}

bool scheduler_is_paused () {
  ((GraceApp *)GraceApp::getInstance())->schemeProcess->isPaused();
}

void scheduler_pause() {
  ((GraceApp *)GraceApp::getInstance())->schemeProcess->setPaused(true);
}

void scheduler_cont () {
  ((GraceApp *)GraceApp::getInstance())->schemeProcess->setPaused(false);
}

void scheduler_stop (int id) {
  ((GraceApp *)GraceApp::getInstance())->schemeProcess->stop(id);
}

void scheduler_hush () {
  ((GraceApp *)GraceApp::getInstance())->schemeProcess->stop(-1);
  ((GraceApp *)GraceApp::getInstance())->midiport->clear();
}

bool scheduler_is_time_milliseconds () {
  ((GraceApp *)GraceApp::getInstance())->schemeProcess->isTimeMilliseconds();
}
 
void scheduler_set_time_milliseconds (bool b) {
  ((GraceApp *)GraceApp::getInstance())->schemeProcess->setTimeMilliseconds(b);
}




#include "Toolbox.h"



static C_PTABLE_ENTRY *create_ptable(void);
C_noret_decl(C_library_toplevel)
C_externimport void C_ccall C_library_toplevel(C_word c,C_word d,C_word k) C_noret;
C_noret_decl(C_eval_toplevel)
C_externimport void C_ccall C_eval_toplevel(C_word c,C_word d,C_word k) C_noret;
C_noret_decl(C_extras_toplevel)
C_externimport void C_ccall C_extras_toplevel(C_word c,C_word d,C_word k) C_noret;
C_noret_decl(C_extras_toplevel)
C_externimport void C_ccall C_extras_toplevel(C_word c,C_word d,C_word k) C_noret;

static C_TLS C_word lf[257];


/* from k1569 in hush in k574 in k571 in k568 in k565 */
C_noret_decl(stub349)
static void C_ccall stub349(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub349(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_hush();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1563 */
C_noret_decl(stub344)
static void C_ccall stub344(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0) C_noret;
static void C_ccall stub344(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_unfix(C_a0);
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_stop(t0);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1547 in cont in k574 in k571 in k568 in k565 */
C_noret_decl(stub339)
static void C_ccall stub339(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub339(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_cont();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1538 in pause in k574 in k571 in k568 in k565 */
C_noret_decl(stub335)
static void C_ccall stub335(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub335(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_pause();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1529 in paused? in k574 in k571 in k568 in k565 */
C_noret_decl(stub331)
static void C_ccall stub331(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub331(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
C_r=C_mk_bool(scheduler_is_paused());
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1523 */
C_noret_decl(stub324)
static void C_ccall stub324(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2) C_noret;
static void C_ccall stub324(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
C_word t0=(C_word )(C_a0);
double t1=(double )C_c_double(C_a1);
int t2=(int )C_unfix(C_a2);
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_sprout(t0,t1,t2);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1503 in scheduler-set-time-milliseconds in k574 in k571 in k568 in k565 */
C_noret_decl(stub316)
static void C_ccall stub316(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0) C_noret;
static void C_ccall stub316(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_truep(C_a0);
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_set_time_milliseconds(t0);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1494 in time-format in k574 in k571 in k568 in k565 */
C_noret_decl(stub311)
static void C_ccall stub311(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub311(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
C_r=C_mk_bool(scheduler_is_time_milliseconds());
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from current-time-seconds in k574 in k571 in k568 in k565 */
#define return(x) C_cblock C_r = (C_flonum(&C_a,(x))); goto C_ret; C_cblockend
static C_word C_fcall stub308(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub308(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
 C_return( (Time::getMillisecondCounterHiRes() / 1000.0) );
C_ret:
#undef return

return C_r;}

/* from current-time-milliseconds in k574 in k571 in k568 in k565 */
#define return(x) C_cblock C_r = (C_flonum(&C_a,(x))); goto C_ret; C_cblockend
static C_word C_fcall stub305(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub305(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
 C_return( Time::getMillisecondCounterHiRes());
C_ret:
#undef return

return C_r;}

/* from k1482 */
C_noret_decl(stub296)
static void C_ccall stub296(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2,C_word C_a3,C_word C_a4) C_noret;
static void C_ccall stub296(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2,C_word C_a3,C_word C_a4){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
double t0=(double )C_c_double(C_a0);
double t1=(double )C_c_double(C_a1);
float t2=(float )C_c_double(C_a2);
float t3=(float )C_c_double(C_a3);
float t4=(float )C_c_double(C_a4);
int C_level=C_save_callback_continuation(&C_a,C_k);
mp_note(t0,t1,t2,t3,t4);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1446 in print-error in k574 in k571 in k568 in k565 */
static C_word C_fcall stub286(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub286(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_error(t0);
return C_r;}

/* from k1432 in print-message in k574 in k571 in k568 in k565 */
static C_word C_fcall stub280(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub280(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_message(t0);
return C_r;}

/* from tb:ranbrown */
static C_word C_fcall stub148(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub148(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
C_r=C_flonum(&C_a,Toolbox::ranbrown());
return C_r;}

/* from tb:ranpink */
static C_word C_fcall stub145(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub145(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
C_r=C_flonum(&C_a,Toolbox::ranpink());
return C_r;}

/* from k801 */
static C_word C_fcall stub142(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub142(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_fix((C_word)Toolbox::ranpoisson(t0));
return C_r;}

/* from tb:rancauchy */
static C_word C_fcall stub138(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub138(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
C_r=C_flonum(&C_a,Toolbox::rancauchy());
return C_r;}

/* from k791 */
static C_word C_fcall stub134(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub134(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::rangamma(t0));
return C_r;}

/* from k784 */
static C_word C_fcall stub128(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub128(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
C_r=C_flonum(&C_a,Toolbox::ranbeta(t0,t1));
return C_r;}

/* from k773 */
static C_word C_fcall stub122(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub122(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::ranexp(t0));
return C_r;}

/* from k766 */
static C_word C_fcall stub116(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub116(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
C_r=C_flonum(&C_a,Toolbox::rangauss(t0,t1));
return C_r;}

/* from tb:ranmiddle */
static C_word C_fcall stub111(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub111(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
C_r=C_flonum(&C_a,Toolbox::ranmiddle());
return C_r;}

/* from tb:ranhigh */
static C_word C_fcall stub108(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub108(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
C_r=C_flonum(&C_a,Toolbox::ranhigh());
return C_r;}

/* from tb:ranlow */
static C_word C_fcall stub105(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub105(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
C_r=C_flonum(&C_a,Toolbox::ranlow());
return C_r;}

/* from k746 */
static C_word C_fcall stub100(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub100(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
C_r=C_flonum(&C_a,Toolbox::ran(t0,t1));
return C_r;}

/* from k735 */
static C_word C_fcall stub94(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub94(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_unfix(C_a0);
int t1=(int )C_unfix(C_a1);
C_r=C_fix((C_word)Toolbox::ran(t0,t1));
return C_r;}

/* from k724 */
static C_word C_fcall stub88(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub88(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::ran(t0));
return C_r;}

/* from k717 */
static C_word C_fcall stub84(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub84(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_unfix(C_a0);
C_r=C_fix((C_word)Toolbox::ran(t0));
return C_r;}

/* from tb:ran-set! */
static C_word C_fcall stub80(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub80(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
C_s64 t0=(C_s64 )C_num_to_int64(C_a0);
Toolbox::ranstate_set(t0);
return C_r;}

/* from k707 */
static C_word C_fcall stub75(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub75(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::hertz_to_keynum(t0));
return C_r;}

/* from k700 */
static C_word C_fcall stub71(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub71(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_fix((C_word)Toolbox::keynum_to_pc(t0));
return C_r;}

/* from k693 */
static C_word C_fcall stub66(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub66(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::keynum_to_hertz(t0));
return C_r;}

/* from k686 */
static C_word C_fcall stub62(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub62(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_fix((C_word)Toolbox::scaler_to_cents(t0));
return C_r;}

/* from k679 */
static C_word C_fcall stub57(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub57(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_unfix(C_a0);
C_r=C_flonum(&C_a,Toolbox::cents_to_scaler(t0));
return C_r;}

/* from k672 */
static C_word C_fcall stub50(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2) C_regparm;
C_regparm static C_word C_fcall stub50(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
float t2=(float )C_c_double(C_a2);
C_r=C_flonum(&C_a,Toolbox::rhythm_to_seconds(t0,t1,t2));
return C_r;}

/* from k657 */
static C_word C_fcall stub42(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub42(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
C_r=C_flonum(&C_a,Toolbox::quantize(t0,t1));
return C_r;}

/* from k646 */
static C_word C_fcall stub35(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub35(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
int t1=(int )C_unfix(C_a1);
C_r=C_flonum(&C_a,Toolbox::decimals(t0,t1));
return C_r;}

/* from k635 */
static C_word C_fcall stub30(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub30(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_fix((C_word)Toolbox::float_to_fixnum(t0));
return C_r;}

/* from k628 */
static C_word C_fcall stub21(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2,C_word C_a3,C_word C_a4,C_word C_a5) C_regparm;
C_regparm static C_word C_fcall stub21(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2,C_word C_a3,C_word C_a4,C_word C_a5){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
float t2=(float )C_c_double(C_a2);
int t3=(int )C_unfix(C_a3);
int t4=(int )C_unfix(C_a4);
float t5=(float )C_c_double(C_a5);
C_r=C_fix((C_word)Toolbox::discrete(t0,t1,t2,t3,t4,t5));
return C_r;}

/* from k601 */
static C_word C_fcall stub6(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2,C_word C_a3,C_word C_a4,C_word C_a5) C_regparm;
C_regparm static C_word C_fcall stub6(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2,C_word C_a3,C_word C_a4,C_word C_a5){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
float t2=(float )C_c_double(C_a2);
float t3=(float )C_c_double(C_a3);
float t4=(float )C_c_double(C_a4);
float t5=(float )C_c_double(C_a5);
C_r=C_flonum(&C_a,Toolbox::rescale(t0,t1,t2,t3,t4,t5));
return C_r;}

C_noret_decl(C_grace_toplevel)
C_externexport void C_ccall C_grace_toplevel(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_567)
static void C_ccall f_567(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_570)
static void C_ccall f_570(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_573)
static void C_ccall f_573(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_576)
static void C_ccall f_576(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1900)
static void C_ccall f_1900(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2686)
static void C_ccall f_2686(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_2733)
static void C_ccall f_2733(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2723)
static void C_ccall f_2723(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2690)
static void C_ccall f_2690(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1903)
static void C_ccall f_1903(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2680)
static void C_ccall f_2680(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_2680)
static void C_ccall f_2680r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_1919)
static void C_ccall f_1919(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2132)
static void C_ccall f_2132(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1922)
static void C_ccall f_1922(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1925)
static void C_ccall f_1925(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1937)
static void C_ccall f_1937(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1985)
static void C_fcall f_1985(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_2001)
static void C_ccall f_2001(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2011)
static void C_ccall f_2011(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2110)
static void C_ccall f_2110(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2106)
static void C_ccall f_2106(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2055)
static void C_ccall f_2055(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2061)
static void C_ccall f_2061(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1995)
static void C_fcall f_1995(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1940)
static void C_ccall f_1940(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1945)
static void C_fcall f_1945(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1958)
static void C_fcall f_1958(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2142)
static void C_ccall f_2142(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2193)
static void C_ccall f_2193(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2196)
static void C_ccall f_2196(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2199)
static void C_ccall f_2199(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2202)
static void C_ccall f_2202(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2205)
static void C_ccall f_2205(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2208)
static void C_ccall f_2208(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2211)
static void C_ccall f_2211(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2214)
static void C_ccall f_2214(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2674)
static void C_ccall f_2674(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_2674)
static void C_ccall f_2674r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_2232)
static void C_ccall f_2232(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2235)
static void C_ccall f_2235(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2509)
static void C_fcall f_2509(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2617)
static void C_ccall f_2617(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2529)
static void C_fcall f_2529(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2538)
static void C_fcall f_2538(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2542)
static void C_ccall f_2542(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2546)
static void C_ccall f_2546(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2554)
static void C_fcall f_2554(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2550)
static void C_ccall f_2550(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2519)
static void C_ccall f_2519(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2238)
static void C_ccall f_2238(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2241)
static void C_ccall f_2241(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2244)
static void C_ccall f_2244(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2247)
static void C_ccall f_2247(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2250)
static void C_ccall f_2250(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2503)
static void C_ccall f_2503(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2402)
static void C_fcall f_2402(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2409)
static void C_ccall f_2409(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2411)
static void C_fcall f_2411(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2483)
static void C_ccall f_2483(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2435)
static void C_fcall f_2435(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2438)
static void C_ccall f_2438(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2459)
static void C_ccall f_2459(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2425)
static void C_ccall f_2425(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2253)
static void C_ccall f_2253(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2391)
static void C_ccall f_2391(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2379)
static void C_ccall f_2379(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2375)
static void C_ccall f_2375(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2260)
static void C_fcall f_2260(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2217)
static void C_ccall f_2217(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2672)
static void C_ccall f_2672(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2186)
static void C_ccall f_2186(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2180)
static void C_ccall f_2180(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2174)
static void C_ccall f_2174(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2168)
static void C_ccall f_2168(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_2162)
static void C_ccall f_2162(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_2156)
static void C_ccall f_2156(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_2150)
static void C_ccall f_2150(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_2144)
static void C_ccall f_2144(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_1461)
static void C_ccall f_1461(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1905)
static void C_fcall f_1905(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1913)
static void C_ccall f_1913(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1889)
static void C_ccall f_1889(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1571)
static void C_ccall f_1571(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1893)
static void C_ccall f_1893(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1831)
static void C_ccall f_1831(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1831)
static void C_ccall f_1831r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1849)
static void C_fcall f_1849(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1859)
static void C_ccall f_1859(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1835)
static void C_ccall f_1835(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1822)
static void C_ccall f_1822(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1549)
static void C_ccall f_1549(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1826)
static void C_ccall f_1826(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1816)
static void C_ccall f_1816(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1531)
static void C_ccall f_1531(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1807)
static void C_ccall f_1807(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1540)
static void C_ccall f_1540(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1811)
static void C_ccall f_1811(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1744)
static void C_ccall f_1744(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1744)
static void C_ccall f_1744r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1769)
static void C_fcall f_1769(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1496)
static void C_ccall f_1496(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1757)
static void C_ccall f_1757(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1576)
static void C_ccall f_1576(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_1576)
static void C_ccall f_1576r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_1695)
static void C_fcall f_1695(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1690)
static void C_fcall f_1690(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1578)
static void C_fcall f_1578(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_1685)
static void C_ccall f_1685(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1689)
static void C_ccall f_1689(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1681)
static void C_ccall f_1681(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1649)
static void C_fcall f_1649(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1674)
static void C_ccall f_1674(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1678)
static void C_ccall f_1678(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1659)
static void C_ccall f_1659(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1638)
static void C_ccall f_1638(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1608)
static void C_fcall f_1608(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1580)
static void C_fcall f_1580(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1554)
static void C_fcall f_1554(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1558)
static void C_ccall f_1558(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1510)
static void C_fcall f_1510(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_1514)
static void C_ccall f_1514(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1501)
static void C_fcall f_1501(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1505)
static void C_ccall f_1505(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1489)
static void C_ccall f_1489(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1486)
static void C_ccall f_1486(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1443)
static void C_ccall f_1443(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1448)
static void C_ccall f_1448(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1429)
static void C_ccall f_1429(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1434)
static void C_ccall f_1434(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1423)
static void C_ccall f_1423(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1417)
static void C_ccall f_1417(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1398)
static void C_ccall f_1398(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1398)
static void C_ccall f_1398r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1379)
static void C_ccall f_1379(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1379)
static void C_ccall f_1379r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1373)
static void C_ccall f_1373(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1333)
static void C_ccall f_1333(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1333)
static void C_ccall f_1333r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1314)
static void C_ccall f_1314(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1314)
static void C_ccall f_1314r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1270)
static void C_ccall f_1270(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1270)
static void C_ccall f_1270r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1264)
static void C_ccall f_1264(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1258)
static void C_ccall f_1258(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1252)
static void C_ccall f_1252(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1246)
static void C_ccall f_1246(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1246)
static void C_ccall f_1246r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1223)
static void C_ccall f_1223(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1240)
static void C_ccall f_1240(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1165)
static void C_ccall f_1165(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_1165)
static void C_ccall f_1165r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_1217)
static void C_ccall f_1217(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1201)
static void C_ccall f_1201(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1182)
static void C_ccall f_1182(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1077)
static void C_ccall f_1077(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1077)
static void C_ccall f_1077r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1123)
static void C_fcall f_1123(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1071)
static void C_ccall f_1071(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1065)
static void C_ccall f_1065(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_1065)
static void C_ccall f_1065r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_970)
static void C_ccall f_970(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_970)
static void C_ccall f_970r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_974)
static void C_ccall f_974(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_977)
static void C_ccall f_977(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_989)
static void C_fcall f_989(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1011)
static void C_ccall f_1011(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_964)
static void C_ccall f_964(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_958)
static void C_ccall f_958(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_952)
static void C_ccall f_952(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_946)
static void C_ccall f_946(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_940)
static void C_ccall f_940(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_880)
static void C_ccall f_880(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_880)
static void C_ccall f_880r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_892)
static void C_fcall f_892(C_word t0,C_word t1) C_noret;
C_noret_decl(f_887)
static void C_fcall f_887(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_882)
static void C_fcall f_882(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_861)
static void C_ccall f_861(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_861)
static void C_ccall f_861r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_855)
static void C_ccall f_855(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_849)
static void C_ccall f_849(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_830)
static void C_ccall f_830(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,...) C_noret;
C_noret_decl(f_830)
static void C_ccall f_830r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t8) C_noret;
C_noret_decl(f_811)
static void C_ccall f_811(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,...) C_noret;
C_noret_decl(f_811)
static void C_ccall f_811r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t8) C_noret;
C_noret_decl(f_798)
static void C_fcall f_798(C_word t0,C_word t1) C_noret;
C_noret_decl(f_788)
static void C_fcall f_788(C_word t0,C_word t1) C_noret;
C_noret_decl(f_777)
static void C_fcall f_777(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_770)
static void C_fcall f_770(C_word t0,C_word t1) C_noret;
C_noret_decl(f_759)
static void C_fcall f_759(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_721)
static void C_fcall f_721(C_word t0,C_word t1) C_noret;
C_noret_decl(f_714)
static void C_fcall f_714(C_word t0,C_word t1) C_noret;
C_noret_decl(f_639)
static void C_fcall f_639(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_605)
static void C_fcall f_605(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_578)
static void C_fcall f_578(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;

C_noret_decl(trf_1985)
static void C_fcall trf_1985(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1985(void *dummy){
C_word t4=C_pick(0);
C_word t3=C_pick(1);
C_word t2=C_pick(2);
C_word t1=C_pick(3);
C_word t0=C_pick(4);
C_adjust_stack(-5);
f_1985(t0,t1,t2,t3,t4);}

C_noret_decl(trf_1995)
static void C_fcall trf_1995(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1995(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1995(t0,t1);}

C_noret_decl(trf_1945)
static void C_fcall trf_1945(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1945(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1945(t0,t1,t2);}

C_noret_decl(trf_1958)
static void C_fcall trf_1958(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1958(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1958(t0,t1);}

C_noret_decl(trf_2509)
static void C_fcall trf_2509(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2509(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_2509(t0,t1,t2);}

C_noret_decl(trf_2529)
static void C_fcall trf_2529(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2529(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2529(t0,t1);}

C_noret_decl(trf_2538)
static void C_fcall trf_2538(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2538(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2538(t0,t1);}

C_noret_decl(trf_2554)
static void C_fcall trf_2554(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2554(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2554(t0,t1);}

C_noret_decl(trf_2402)
static void C_fcall trf_2402(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2402(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2402(t0,t1);}

C_noret_decl(trf_2411)
static void C_fcall trf_2411(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2411(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_2411(t0,t1,t2);}

C_noret_decl(trf_2435)
static void C_fcall trf_2435(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2435(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2435(t0,t1);}

C_noret_decl(trf_2260)
static void C_fcall trf_2260(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2260(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2260(t0,t1);}

C_noret_decl(trf_1905)
static void C_fcall trf_1905(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1905(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1905(t0,t1,t2);}

C_noret_decl(trf_1849)
static void C_fcall trf_1849(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1849(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1849(t0,t1,t2);}

C_noret_decl(trf_1769)
static void C_fcall trf_1769(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1769(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1769(t0,t1);}

C_noret_decl(trf_1695)
static void C_fcall trf_1695(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1695(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1695(t0,t1);}

C_noret_decl(trf_1690)
static void C_fcall trf_1690(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1690(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1690(t0,t1,t2);}

C_noret_decl(trf_1578)
static void C_fcall trf_1578(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1578(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_1578(t0,t1,t2,t3);}

C_noret_decl(trf_1649)
static void C_fcall trf_1649(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1649(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1649(t0,t1,t2);}

C_noret_decl(trf_1608)
static void C_fcall trf_1608(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1608(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1608(t0,t1);}

C_noret_decl(trf_1580)
static void C_fcall trf_1580(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1580(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1580(t0,t1);}

C_noret_decl(trf_1554)
static void C_fcall trf_1554(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1554(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1554(t0,t1);}

C_noret_decl(trf_1510)
static void C_fcall trf_1510(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1510(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_1510(t0,t1,t2,t3);}

C_noret_decl(trf_1501)
static void C_fcall trf_1501(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1501(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1501(t0,t1);}

C_noret_decl(trf_1123)
static void C_fcall trf_1123(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1123(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1123(t0,t1);}

C_noret_decl(trf_989)
static void C_fcall trf_989(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_989(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_989(t0,t1,t2);}

C_noret_decl(trf_892)
static void C_fcall trf_892(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_892(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_892(t0,t1);}

C_noret_decl(trf_887)
static void C_fcall trf_887(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_887(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_887(t0,t1,t2);}

C_noret_decl(trf_882)
static void C_fcall trf_882(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_882(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_882(t0,t1,t2,t3);}

C_noret_decl(trf_798)
static void C_fcall trf_798(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_798(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_798(t0,t1);}

C_noret_decl(trf_788)
static void C_fcall trf_788(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_788(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_788(t0,t1);}

C_noret_decl(trf_777)
static void C_fcall trf_777(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_777(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_777(t0,t1,t2);}

C_noret_decl(trf_770)
static void C_fcall trf_770(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_770(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_770(t0,t1);}

C_noret_decl(trf_759)
static void C_fcall trf_759(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_759(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_759(t0,t1,t2);}

C_noret_decl(trf_721)
static void C_fcall trf_721(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_721(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_721(t0,t1);}

C_noret_decl(trf_714)
static void C_fcall trf_714(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_714(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_714(t0,t1);}

C_noret_decl(trf_639)
static void C_fcall trf_639(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_639(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_639(t0,t1,t2);}

C_noret_decl(trf_605)
static void C_fcall trf_605(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_605(void *dummy){
C_word t6=C_pick(0);
C_word t5=C_pick(1);
C_word t4=C_pick(2);
C_word t3=C_pick(3);
C_word t2=C_pick(4);
C_word t1=C_pick(5);
C_word t0=C_pick(6);
C_adjust_stack(-7);
f_605(t0,t1,t2,t3,t4,t5,t6);}

C_noret_decl(trf_578)
static void C_fcall trf_578(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_578(void *dummy){
C_word t6=C_pick(0);
C_word t5=C_pick(1);
C_word t4=C_pick(2);
C_word t3=C_pick(3);
C_word t2=C_pick(4);
C_word t1=C_pick(5);
C_word t0=C_pick(6);
C_adjust_stack(-7);
f_578(t0,t1,t2,t3,t4,t5,t6);}

C_noret_decl(tr7)
static void C_fcall tr7(C_proc7 k) C_regparm C_noret;
C_regparm static void C_fcall tr7(C_proc7 k){
C_word t6=C_pick(0);
C_word t5=C_pick(1);
C_word t4=C_pick(2);
C_word t3=C_pick(3);
C_word t2=C_pick(4);
C_word t1=C_pick(5);
C_word t0=C_pick(6);
C_adjust_stack(-7);
(k)(7,t0,t1,t2,t3,t4,t5,t6);}

C_noret_decl(tr5)
static void C_fcall tr5(C_proc5 k) C_regparm C_noret;
C_regparm static void C_fcall tr5(C_proc5 k){
C_word t4=C_pick(0);
C_word t3=C_pick(1);
C_word t2=C_pick(2);
C_word t1=C_pick(3);
C_word t0=C_pick(4);
C_adjust_stack(-5);
(k)(5,t0,t1,t2,t3,t4);}

C_noret_decl(tr6)
static void C_fcall tr6(C_proc6 k) C_regparm C_noret;
C_regparm static void C_fcall tr6(C_proc6 k){
C_word t5=C_pick(0);
C_word t4=C_pick(1);
C_word t3=C_pick(2);
C_word t2=C_pick(3);
C_word t1=C_pick(4);
C_word t0=C_pick(5);
C_adjust_stack(-6);
(k)(6,t0,t1,t2,t3,t4,t5);}

C_noret_decl(tr3)
static void C_fcall tr3(C_proc3 k) C_regparm C_noret;
C_regparm static void C_fcall tr3(C_proc3 k){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
(k)(3,t0,t1,t2);}

C_noret_decl(tr4)
static void C_fcall tr4(C_proc4 k) C_regparm C_noret;
C_regparm static void C_fcall tr4(C_proc4 k){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
(k)(4,t0,t1,t2,t3);}

C_noret_decl(tr2)
static void C_fcall tr2(C_proc2 k) C_regparm C_noret;
C_regparm static void C_fcall tr2(C_proc2 k){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
(k)(2,t0,t1);}

C_noret_decl(tr2r)
static void C_fcall tr2r(C_proc2 k) C_regparm C_noret;
C_regparm static void C_fcall tr2r(C_proc2 k){
int n;
C_word *a,t2;
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
n=C_rest_count(0);
a=C_alloc(n*3);
t2=C_restore_rest(a,n);
(k)(t0,t1,t2);}

C_noret_decl(tr4r)
static void C_fcall tr4r(C_proc4 k) C_regparm C_noret;
C_regparm static void C_fcall tr4r(C_proc4 k){
int n;
C_word *a,t4;
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
n=C_rest_count(0);
a=C_alloc(n*3);
t4=C_restore_rest(a,n);
(k)(t0,t1,t2,t3,t4);}

C_noret_decl(tr3r)
static void C_fcall tr3r(C_proc3 k) C_regparm C_noret;
C_regparm static void C_fcall tr3r(C_proc3 k){
int n;
C_word *a,t3;
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
n=C_rest_count(0);
a=C_alloc(n*3);
t3=C_restore_rest(a,n);
(k)(t0,t1,t2,t3);}

C_noret_decl(tr7rv)
static void C_fcall tr7rv(C_proc7 k) C_regparm C_noret;
C_regparm static void C_fcall tr7rv(C_proc7 k){
int n;
C_word *a,t7;
C_word t6=C_pick(0);
C_word t5=C_pick(1);
C_word t4=C_pick(2);
C_word t3=C_pick(3);
C_word t2=C_pick(4);
C_word t1=C_pick(5);
C_word t0=C_pick(6);
C_adjust_stack(-7);
n=C_rest_count(0);
a=C_alloc(n+1);
t7=C_restore_rest_vector(a,n);
(k)(t0,t1,t2,t3,t4,t5,t6,t7);}

C_noret_decl(tr3rv)
static void C_fcall tr3rv(C_proc3 k) C_regparm C_noret;
C_regparm static void C_fcall tr3rv(C_proc3 k){
int n;
C_word *a,t3;
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
n=C_rest_count(0);
a=C_alloc(n+1);
t3=C_restore_rest_vector(a,n);
(k)(t0,t1,t2,t3);}

C_noret_decl(tr4rv)
static void C_fcall tr4rv(C_proc4 k) C_regparm C_noret;
C_regparm static void C_fcall tr4rv(C_proc4 k){
int n;
C_word *a,t4;
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
n=C_rest_count(0);
a=C_alloc(n+1);
t4=C_restore_rest_vector(a,n);
(k)(t0,t1,t2,t3,t4);}

C_noret_decl(tr2rv)
static void C_fcall tr2rv(C_proc2 k) C_regparm C_noret;
C_regparm static void C_fcall tr2rv(C_proc2 k){
int n;
C_word *a,t2;
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
n=C_rest_count(0);
a=C_alloc(n+1);
t2=C_restore_rest_vector(a,n);
(k)(t0,t1,t2);}

/* toplevel */
static C_TLS int toplevel_initialized=0;
C_noret_decl(toplevel_trampoline)
static void C_fcall toplevel_trampoline(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall toplevel_trampoline(void *dummy){
C_grace_toplevel(2,C_SCHEME_UNDEFINED,C_restore);}

void C_ccall C_grace_toplevel(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
if(toplevel_initialized) C_kontinue(t1,C_SCHEME_UNDEFINED);
else C_toplevel_entry(C_text("grace_toplevel"));
C_check_nursery_minimum(3);
if(!C_demand(3)){
C_save(t1);
C_reclaim((void*)toplevel_trampoline,NULL);}
toplevel_initialized=1;
if(!C_demand_2(1526)){
C_save(t1);
C_rereclaim2(1526*sizeof(C_word), 1);
t1=C_restore;}
a=C_alloc(3);
C_initialize_lf(lf,257);
lf[1]=C_static_string(C_heaptop,27,"too many optional arguments");
lf[3]=C_static_lambda_info(C_heaptop,40,"(tb:rescale a58 a49 a310 a211 a112 a013)");
lf[5]=C_static_lambda_info(C_heaptop,49,"(tb:discrete a2023 a1924 a1825 a1726 a1627 a1528)");
lf[7]=C_static_lambda_info(C_heaptop,25,"(tb:decimals a3437 a3338)");
lf[9]=C_static_lambda_info(C_heaptop,15,"(tb:rani a8386)");
lf[11]=C_static_lambda_info(C_heaptop,15,"(tb:ranf a8790)");
lf[13]=C_static_lambda_info(C_heaptop,29,"(tb:rangauss a115118 a114119)");
lf[15]=C_static_lambda_info(C_heaptop,19,"(tb:ranexp a121124)");
lf[17]=C_static_lambda_info(C_heaptop,28,"(tb:ranbeta a127130 a126131)");
lf[19]=C_static_lambda_info(C_heaptop,21,"(tb:rangamma a133136)");
lf[21]=C_static_lambda_info(C_heaptop,23,"(tb:ranpoisson a141144)");
lf[22]=C_h_intern(&lf[22],7,"rescale");
lf[23]=C_static_lambda_info(C_heaptop,45,"(rescale x151 x1152 x2153 y1154 y2155 . b156)");
lf[24]=C_h_intern(&lf[24],8,"discrete");
lf[25]=C_static_lambda_info(C_heaptop,46,"(discrete x157 x1158 x2159 i1160 i2161 . b162)");
lf[26]=C_h_intern(&lf[26],3,"int");
lf[27]=C_static_lambda_info(C_heaptop,10,"(int f163)");
lf[28]=C_h_intern(&lf[28],8,"quantize");
lf[29]=C_static_lambda_info(C_heaptop,26,"(quantize num164 steps165)");
lf[30]=C_h_intern(&lf[30],8,"decimals");
lf[31]=C_static_lambda_info(C_heaptop,29,"(decimals num166 . digits167)");
lf[32]=C_h_intern(&lf[32],15,"rhythm->seconds");
lf[33]=C_static_lambda_info(C_heaptop,26,"(body172 tempo178 beat179)");
lf[34]=C_flonum(C_heaptop,0.25);
lf[35]=C_static_lambda_info(C_heaptop,26,"(def-beat175 %tempo170181)");
lf[36]=C_flonum(C_heaptop,60.0);
lf[37]=C_static_lambda_info(C_heaptop,14,"(def-tempo174)");
lf[38]=C_h_intern(&lf[38],9,"\003syserror");
lf[39]=C_static_lambda_info(C_heaptop,36,"(rhythm->seconds beats168 . args169)");
lf[40]=C_h_intern(&lf[40],13,"cents->scaler");
lf[41]=C_static_lambda_info(C_heaptop,24,"(cents->scaler cents188)");
lf[42]=C_h_intern(&lf[42],13,"scaler->cents");
lf[43]=C_static_lambda_info(C_heaptop,22,"(scaler->cents num189)");
lf[44]=C_h_intern(&lf[44],13,"keynum->hertz");
lf[45]=C_static_lambda_info(C_heaptop,20,"(keynum->hertz k190)");
lf[46]=C_h_intern(&lf[46],10,"keynum->pc");
lf[47]=C_static_lambda_info(C_heaptop,17,"(keynum->pc k191)");
lf[48]=C_h_intern(&lf[48],13,"hertz->keynum");
lf[49]=C_static_lambda_info(C_heaptop,21,"(hertz->keynum hz192)");
lf[50]=C_h_intern(&lf[50],7,"interpl");
lf[51]=C_h_intern(&lf[51],5,"error");
lf[52]=C_static_string(C_heaptop,27,"not an x y coordinate list:");
lf[53]=C_static_lambda_info(C_heaptop,15,"(do201 tail203)");
lf[54]=C_h_intern(&lf[54],3,"err");
lf[55]=C_static_string(C_heaptop,27,"not an x y coordinate list:");
lf[56]=C_static_string(C_heaptop,27,"not an x y coordinate list:");
lf[57]=C_static_lambda_info(C_heaptop,34,"(interpl x193 coords194 . base195)");
lf[58]=C_h_intern(&lf[58],6,"interp");
lf[59]=C_static_lambda_info(C_heaptop,23,"(interp x211 . args212)");
lf[60]=C_h_intern(&lf[60],8,"ran-set!");
lf[61]=C_static_lambda_info(C_heaptop,18,"(ran-set! seed213)");
lf[62]=C_h_intern(&lf[62],3,"ran");
lf[63]=C_flonum(C_heaptop,1.0);
lf[64]=C_static_lambda_info(C_heaptop,15,"(ran . args214)");
lf[65]=C_h_intern(&lf[65],4,"odds");
lf[66]=C_flonum(C_heaptop,1.0);
lf[67]=C_flonum(C_heaptop,1.0);
lf[68]=C_flonum(C_heaptop,1.0);
lf[69]=C_static_lambda_info(C_heaptop,21,"(odds n215 . args216)");
lf[70]=C_h_intern(&lf[70],5,"pickl");
lf[71]=C_static_string(C_heaptop,29,"cannot pick from empty list: ");
lf[72]=C_static_lambda_info(C_heaptop,15,"(pickl args217)");
lf[73]=C_h_intern(&lf[73],4,"pick");
lf[74]=C_static_lambda_info(C_heaptop,16,"(pick . args218)");
lf[75]=C_h_intern(&lf[75],6,"ranlow");
lf[76]=C_static_lambda_info(C_heaptop,8,"(ranlow)");
lf[77]=C_h_intern(&lf[77],7,"ranhigh");
lf[78]=C_static_lambda_info(C_heaptop,9,"(ranhigh)");
lf[79]=C_h_intern(&lf[79],9,"ranmiddle");
lf[80]=C_static_lambda_info(C_heaptop,11,"(ranmiddle)");
lf[81]=C_h_intern(&lf[81],7,"ranbeta");
lf[82]=C_flonum(C_heaptop,0.5);
lf[83]=C_flonum(C_heaptop,0.5);
lf[84]=C_static_lambda_info(C_heaptop,19,"(ranbeta . args219)");
lf[85]=C_h_intern(&lf[85],6,"ranexp");
lf[86]=C_static_lambda_info(C_heaptop,18,"(ranexp . args220)");
lf[87]=C_h_intern(&lf[87],8,"rangauss");
lf[88]=C_static_lambda_info(C_heaptop,20,"(rangauss . args221)");
lf[89]=C_h_intern(&lf[89],9,"rancauchy");
lf[90]=C_static_lambda_info(C_heaptop,11,"(rancauchy)");
lf[91]=C_h_intern(&lf[91],10,"ranpoisson");
lf[92]=C_h_intern(&lf[92],3,"arg");
lf[93]=C_static_lambda_info(C_heaptop,22,"(ranpoisson . args222)");
lf[94]=C_h_intern(&lf[94],8,"rangamma");
lf[95]=C_static_lambda_info(C_heaptop,20,"(rangamma . args223)");
lf[96]=C_h_intern(&lf[96],8,"ranbrown");
lf[97]=C_static_lambda_info(C_heaptop,10,"(ranbrown)");
lf[98]=C_h_intern(&lf[98],7,"ranpink");
lf[99]=C_static_lambda_info(C_heaptop,9,"(ranpink)");
lf[100]=C_h_intern(&lf[100],13,"print-message");
lf[101]=C_h_intern(&lf[101],17,"\003sysmake-c-string");
lf[102]=C_static_lambda_info(C_heaptop,23,"(print-message a279283)");
lf[103]=C_h_intern(&lf[103],11,"print-error");
lf[104]=C_static_lambda_info(C_heaptop,21,"(print-error a285289)");
lf[105]=C_h_intern(&lf[105],25,"current-time-milliseconds");
lf[106]=C_static_lambda_info(C_heaptop,27,"(current-time-milliseconds)");
lf[107]=C_h_intern(&lf[107],20,"current-time-seconds");
lf[108]=C_static_lambda_info(C_heaptop,22,"(current-time-seconds)");
lf[110]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[111]=C_h_intern(&lf[111],6,"\003sysgc");
lf[112]=C_static_lambda_info(C_heaptop,41,"(scheduler-set-time-milliseconds a315318)");
lf[114]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[115]=C_static_lambda_info(C_heaptop,42,"(scheduler-sprout a323326 a322327 a321328)");
lf[117]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[118]=C_static_lambda_info(C_heaptop,24,"(scheduler-stop a343346)");
lf[119]=C_h_intern(&lf[119],6,"sprout");
lf[120]=C_static_lambda_info(C_heaptop,11,"(nextstart)");
lf[121]=C_static_lambda_info(C_heaptop,8,"(nextid)");
lf[122]=C_static_lambda_info(C_heaptop,12,"(do371 p373)");
lf[123]=C_static_lambda_info(C_heaptop,24,"(body357 start363 id364)");
lf[124]=C_static_lambda_info(C_heaptop,24,"(def-id360 %start355379)");
lf[125]=C_static_lambda_info(C_heaptop,14,"(def-start359)");
lf[126]=C_static_lambda_info(C_heaptop,26,"(sprout proc353 . args354)");
lf[127]=C_h_intern(&lf[127],3,"now");
lf[128]=C_h_intern(&lf[128],11,"time-format");
lf[129]=C_flonum(C_heaptop,1.0);
lf[130]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[131]=C_flonum(C_heaptop,1.0);
lf[132]=C_h_intern(&lf[132],1,"m");
lf[133]=C_static_string(C_heaptop,17,"not a time-format");
lf[134]=C_h_intern(&lf[134],1,"s");
lf[135]=C_static_lambda_info(C_heaptop,22,"(time-format . arg385)");
lf[136]=C_h_intern(&lf[136],5,"pause");
lf[137]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[138]=C_static_lambda_info(C_heaptop,7,"(pause)");
lf[139]=C_h_intern(&lf[139],7,"paused\077");
lf[140]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[141]=C_static_lambda_info(C_heaptop,9,"(paused\077)");
lf[142]=C_h_intern(&lf[142],4,"cont");
lf[143]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[144]=C_static_lambda_info(C_heaptop,6,"(cont)");
lf[145]=C_h_intern(&lf[145],4,"stop");
lf[146]=C_static_string(C_heaptop,17,"Not an integer id");
lf[147]=C_static_lambda_info(C_heaptop,15,"(do399 tail401)");
lf[148]=C_static_lambda_info(C_heaptop,18,"(stop . procid398)");
lf[149]=C_h_intern(&lf[149],4,"hush");
lf[150]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[151]=C_static_lambda_info(C_heaptop,6,"(hush)");
lf[154]=C_h_intern(&lf[154],7,"sprintf");
lf[155]=C_static_lambda_info(C_heaptop,23,"(ferror str412 args413)");
lf[156]=C_h_intern(&lf[156],7,"mp:note");
lf[157]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[158]=C_static_lambda_info(C_heaptop,46,"(mp:note time450 dur451 key452 amp453 chan454)");
lf[159]=C_h_intern(&lf[159],5,"mp:on");
lf[160]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[161]=C_static_lambda_info(C_heaptop,37,"(mp:on time455 key456 vel457 chan458)");
lf[162]=C_h_intern(&lf[162],6,"mp:off");
lf[163]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[164]=C_static_lambda_info(C_heaptop,38,"(mp:off time459 key460 vel461 chan462)");
lf[165]=C_h_intern(&lf[165],7,"mp:prog");
lf[166]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[167]=C_static_lambda_info(C_heaptop,33,"(mp:prog time463 prog464 chan465)");
lf[168]=C_h_intern(&lf[168],7,"mp:ctrl");
lf[169]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[170]=C_static_lambda_info(C_heaptop,40,"(mp:ctrl time466 ctrl467 val468 chan469)");
lf[171]=C_h_intern(&lf[171],9,"mp:alloff");
lf[172]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[173]=C_static_lambda_info(C_heaptop,11,"(mp:alloff)");
lf[174]=C_h_intern(&lf[174],8,"mp:micro");
lf[175]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[176]=C_static_lambda_info(C_heaptop,18,"(mp:micro divs470)");
lf[177]=C_h_intern(&lf[177],9,"mp:inhook");
lf[178]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[179]=C_static_lambda_info(C_heaptop,19,"(mp:inhook func471)");
lf[180]=C_h_intern(&lf[180],14,"return-to-host");
lf[181]=C_h_intern(&lf[181],4,"else");
lf[182]=C_h_intern(&lf[182],4,"cond");
lf[183]=C_h_intern(&lf[183],6,"lambda");
lf[184]=C_h_intern(&lf[184],7,"elapsed");
lf[185]=C_h_intern(&lf[185],1,"x");
lf[186]=C_h_intern(&lf[186],4,"set!");
lf[187]=C_h_intern(&lf[187],4,"wait");
lf[188]=C_h_intern(&lf[188],4,"let*");
lf[189]=C_h_intern(&lf[189],5,"quote");
lf[190]=C_h_intern(&lf[190],3,"exn");
lf[191]=C_h_intern(&lf[191],7,"message");
lf[192]=C_h_intern(&lf[192],27,"condition-property-accessor");
lf[193]=C_h_intern(&lf[193],6,"printf");
lf[194]=C_static_string(C_heaptop,47,">>> Aborting process at time ~S:~%    Error: ~S");
lf[195]=C_h_intern(&lf[195],22,"with-exception-handler");
lf[196]=C_h_intern(&lf[196],30,"call-with-current-continuation");
lf[197]=C_h_intern(&lf[197],10,"\003sysappend");
lf[198]=C_h_intern(&lf[198],6,"safety");
lf[199]=C_h_intern(&lf[199],4,"cdar");
lf[200]=C_static_string(C_heaptop,19,"unknown declaration");
lf[201]=C_h_intern(&lf[201],4,"caar");
lf[202]=C_static_string(C_heaptop,31,"declaration not list (decl val)");
lf[203]=C_static_lambda_info(C_heaptop,15,"(do497 decl499)");
lf[204]=C_h_intern(&lf[204],7,"declare");
lf[205]=C_h_intern(&lf[205],6,"gensym");
lf[206]=C_h_intern(&lf[206],6,"append");
lf[207]=C_h_intern(&lf[207],5,"\000null");
lf[208]=C_static_string(C_heaptop,41,"binding clause not list (var init [step])");
lf[209]=C_static_lambda_info(C_heaptop,15,"(do481 tail483)");
lf[210]=C_static_string(C_heaptop,36,"go stopping clause missing test form");
lf[211]=C_static_string(C_heaptop,29,"go stopping clause not a list");
lf[212]=C_static_string(C_heaptop,22,"go bindings not a list");
lf[213]=C_static_lambda_info(C_heaptop,42,"(a2673 bindings472 terminate473 . body474)");
lf[214]=C_h_intern(&lf[214],18,"\003sysregister-macro");
lf[215]=C_h_intern(&lf[215],2,"go");
lf[216]=C_h_intern(&lf[216],15,"hash-table-set!");
lf[217]=C_static_string(C_heaptop,9,"mp:inhook");
tmp=C_intern(C_heaptop,9,"mp:inhook");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000func");
C_save(tmp);
tmp=C_SCHEME_FALSE;
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[218]=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
lf[219]=C_static_string(C_heaptop,8,"mp:micro");
tmp=C_intern(C_heaptop,8,"mp:micro");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000divs");
C_save(tmp);
tmp=C_fix(1);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[220]=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
lf[221]=C_static_string(C_heaptop,9,"mp:alloff");
tmp=C_intern(C_heaptop,9,"mp:alloff");
C_save(tmp);
tmp=C_SCHEME_END_OF_LIST;
lf[222]=C_h_pair(C_restore,tmp);
lf[223]=C_static_string(C_heaptop,7,"mp:ctrl");
tmp=C_intern(C_heaptop,7,"mp:ctrl");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000time");
C_save(tmp);
tmp=C_fix(0);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000ctrl");
C_save(tmp);
tmp=C_fix(60);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,4,"\000val");
C_save(tmp);
tmp=C_fix(0);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000chan");
C_save(tmp);
tmp=C_fix(1);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[224]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[225]=C_static_string(C_heaptop,7,"mp:prog");
tmp=C_intern(C_heaptop,7,"mp:prog");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000time");
C_save(tmp);
tmp=C_fix(0);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000prog");
C_save(tmp);
tmp=C_fix(60);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000chan");
C_save(tmp);
tmp=C_fix(0);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[226]=C_h_list(4,C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(4);
lf[227]=C_static_string(C_heaptop,6,"mp:off");
tmp=C_intern(C_heaptop,6,"mp:off");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000time");
C_save(tmp);
tmp=C_fix(0);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,4,"\000key");
C_save(tmp);
tmp=C_fix(60);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,4,"\000vel");
C_save(tmp);
tmp=C_fix(64);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000chan");
C_save(tmp);
tmp=C_fix(1);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[228]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[229]=C_static_string(C_heaptop,5,"mp:on");
tmp=C_intern(C_heaptop,5,"mp:on");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000time");
C_save(tmp);
tmp=C_fix(0);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,4,"\000key");
C_save(tmp);
tmp=C_fix(60);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,4,"\000vel");
C_save(tmp);
tmp=C_fix(64);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000chan");
C_save(tmp);
tmp=C_fix(1);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[230]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[231]=C_static_string(C_heaptop,7,"mp:note");
tmp=C_intern(C_heaptop,7,"mp:note");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000time");
C_save(tmp);
tmp=C_fix(0);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,4,"\000dur");
C_save(tmp);
tmp=C_flonum(C_heaptop,0.5);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,4,"\000key");
C_save(tmp);
tmp=C_fix(60);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,4,"\000amp");
C_save(tmp);
tmp=C_fix(127);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000chan");
C_save(tmp);
tmp=C_fix(1);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[232]=C_h_list(6,C_pick(5),C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(6);
lf[233]=C_static_lambda_info(C_heaptop,15,"(do441 tail443)");
lf[234]=C_static_string(C_heaptop,37,"~S found duplicate keyword \047~S\047 in ~S");
lf[235]=C_static_string(C_heaptop,33,"~S missing value for keyword \047~S\047");
lf[236]=C_static_string(C_heaptop,53,"~S found invalid keyword \047~S\047~%Available keywords: ~S");
lf[237]=C_h_intern(&lf[237],7,"\003sysmap");
lf[238]=C_h_intern(&lf[238],3,"car");
lf[239]=C_static_string(C_heaptop,32,"~S expected keyword but got \047~S\047");
lf[240]=C_h_intern(&lf[240],8,"keyword\077");
lf[241]=C_static_string(C_heaptop,35,"~S expected ~A arguments but got ~A");
lf[242]=C_static_lambda_info(C_heaptop,28,"(do424 key426 arg427 pos428)");
lf[243]=C_static_string(C_heaptop,24,"~S is an invalid message");
lf[244]=C_static_lambda_info(C_heaptop,7,"(a2131)");
lf[245]=C_h_intern(&lf[245],14,"hash-table-ref");
lf[246]=C_h_intern(&lf[246],14,"symbol->string");
lf[247]=C_static_lambda_info(C_heaptop,25,"(a2679 mess448 . data449)");
lf[248]=C_h_intern(&lf[248],4,"send");
lf[249]=C_h_intern(&lf[249],10,"*messages*");
lf[250]=C_h_intern(&lf[250],14,"string->symbol");
lf[251]=C_static_string(C_heaptop,51,"message function not string, symbol or list of both");
lf[252]=C_static_lambda_info(C_heaptop,23,"(a2685 func406 info407)");
lf[253]=C_h_intern(&lf[253],19,"define-send-message");
lf[254]=C_h_intern(&lf[254],15,"make-hash-table");
lf[255]=C_h_intern(&lf[255],6,"equal\077");
lf[256]=C_static_lambda_info(C_heaptop,10,"(toplevel)");
C_register_lf2(lf,257,create_ptable());
t2=C_mutate(&lf[0],lf[1]);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_567,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_library_toplevel(2,C_SCHEME_UNDEFINED,t3);}

/* k565 */
static void C_ccall f_567(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_567,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_570,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_eval_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k568 in k565 */
static void C_ccall f_570(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_570,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_573,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k571 in k568 in k565 */
static void C_ccall f_573(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_573,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_576,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k574 in k571 in k568 in k565 */
static void C_ccall f_576(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word t12;
C_word t13;
C_word t14;
C_word t15;
C_word t16;
C_word t17;
C_word t18;
C_word t19;
C_word t20;
C_word t21;
C_word t22;
C_word t23;
C_word t24;
C_word t25;
C_word t26;
C_word t27;
C_word t28;
C_word t29;
C_word t30;
C_word t31;
C_word t32;
C_word t33;
C_word t34;
C_word t35;
C_word t36;
C_word t37;
C_word t38;
C_word t39;
C_word t40;
C_word t41;
C_word t42;
C_word t43;
C_word t44;
C_word t45;
C_word t46;
C_word t47;
C_word t48;
C_word t49;
C_word t50;
C_word t51;
C_word t52;
C_word t53;
C_word t54;
C_word t55;
C_word t56;
C_word t57;
C_word ab[162],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_576,2,t0,t1);}
t2=C_mutate(&lf[2],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_578,a[2]=lf[3],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate(&lf[4],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_605,a[2]=lf[5],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate(&lf[6],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_639,a[2]=lf[7],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate(&lf[8],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_714,a[2]=lf[9],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate(&lf[10],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_721,a[2]=lf[11],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate(&lf[12],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_759,a[2]=lf[13],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate(&lf[14],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_770,a[2]=lf[15],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate(&lf[16],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_777,a[2]=lf[17],tmp=(C_word)a,a+=3,tmp));
t10=C_mutate(&lf[18],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_788,a[2]=lf[19],tmp=(C_word)a,a+=3,tmp));
t11=C_mutate(&lf[20],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_798,a[2]=lf[21],tmp=(C_word)a,a+=3,tmp));
t12=C_mutate((C_word*)lf[22]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_811,a[2]=lf[23],tmp=(C_word)a,a+=3,tmp));
t13=C_mutate((C_word*)lf[24]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_830,a[2]=lf[25],tmp=(C_word)a,a+=3,tmp));
t14=C_mutate((C_word*)lf[26]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_849,a[2]=lf[27],tmp=(C_word)a,a+=3,tmp));
t15=C_mutate((C_word*)lf[28]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_855,a[2]=lf[29],tmp=(C_word)a,a+=3,tmp));
t16=C_mutate((C_word*)lf[30]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_861,a[2]=lf[31],tmp=(C_word)a,a+=3,tmp));
t17=C_mutate((C_word*)lf[32]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_880,a[2]=lf[39],tmp=(C_word)a,a+=3,tmp));
t18=C_mutate((C_word*)lf[40]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_940,a[2]=lf[41],tmp=(C_word)a,a+=3,tmp));
t19=C_mutate((C_word*)lf[42]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_946,a[2]=lf[43],tmp=(C_word)a,a+=3,tmp));
t20=C_mutate((C_word*)lf[44]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_952,a[2]=lf[45],tmp=(C_word)a,a+=3,tmp));
t21=C_mutate((C_word*)lf[46]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_958,a[2]=lf[47],tmp=(C_word)a,a+=3,tmp));
t22=C_mutate((C_word*)lf[48]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_964,a[2]=lf[49],tmp=(C_word)a,a+=3,tmp));
t23=C_mutate((C_word*)lf[50]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_970,a[2]=lf[57],tmp=(C_word)a,a+=3,tmp));
t24=C_mutate((C_word*)lf[58]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1065,a[2]=lf[59],tmp=(C_word)a,a+=3,tmp));
t25=C_mutate((C_word*)lf[60]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1071,a[2]=lf[61],tmp=(C_word)a,a+=3,tmp));
t26=C_mutate((C_word*)lf[62]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1077,a[2]=lf[64],tmp=(C_word)a,a+=3,tmp));
t27=C_mutate((C_word*)lf[65]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1165,a[2]=lf[69],tmp=(C_word)a,a+=3,tmp));
t28=C_mutate((C_word*)lf[70]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1223,a[2]=lf[72],tmp=(C_word)a,a+=3,tmp));
t29=C_mutate((C_word*)lf[73]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1246,a[2]=lf[74],tmp=(C_word)a,a+=3,tmp));
t30=C_mutate((C_word*)lf[75]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1252,a[2]=lf[76],tmp=(C_word)a,a+=3,tmp));
t31=C_mutate((C_word*)lf[77]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1258,a[2]=lf[78],tmp=(C_word)a,a+=3,tmp));
t32=C_mutate((C_word*)lf[79]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1264,a[2]=lf[80],tmp=(C_word)a,a+=3,tmp));
t33=C_mutate((C_word*)lf[81]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1270,a[2]=lf[84],tmp=(C_word)a,a+=3,tmp));
t34=C_mutate((C_word*)lf[85]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1314,a[2]=lf[86],tmp=(C_word)a,a+=3,tmp));
t35=C_mutate((C_word*)lf[87]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1333,a[2]=lf[88],tmp=(C_word)a,a+=3,tmp));
t36=C_mutate((C_word*)lf[89]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1373,a[2]=lf[90],tmp=(C_word)a,a+=3,tmp));
t37=C_mutate((C_word*)lf[91]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1379,a[2]=lf[93],tmp=(C_word)a,a+=3,tmp));
t38=C_mutate((C_word*)lf[94]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1398,a[2]=lf[95],tmp=(C_word)a,a+=3,tmp));
t39=C_mutate((C_word*)lf[96]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1417,a[2]=lf[97],tmp=(C_word)a,a+=3,tmp));
t40=C_mutate((C_word*)lf[98]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1423,a[2]=lf[99],tmp=(C_word)a,a+=3,tmp));
t41=C_mutate((C_word*)lf[100]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1429,a[2]=lf[102],tmp=(C_word)a,a+=3,tmp));
t42=C_mutate((C_word*)lf[103]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1443,a[2]=lf[104],tmp=(C_word)a,a+=3,tmp));
t43=C_mutate((C_word*)lf[105]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1486,a[2]=lf[106],tmp=(C_word)a,a+=3,tmp));
t44=C_mutate((C_word*)lf[107]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1489,a[2]=lf[108],tmp=(C_word)a,a+=3,tmp));
t45=C_mutate(&lf[109],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1501,a[2]=lf[112],tmp=(C_word)a,a+=3,tmp));
t46=C_mutate(&lf[113],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1510,a[2]=lf[115],tmp=(C_word)a,a+=3,tmp));
t47=C_mutate(&lf[116],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1554,a[2]=lf[118],tmp=(C_word)a,a+=3,tmp));
t48=C_mutate((C_word*)lf[119]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1576,a[2]=lf[126],tmp=(C_word)a,a+=3,tmp));
t49=C_mutate((C_word*)lf[127]+1,*((C_word*)lf[105]+1));
t50=C_mutate((C_word*)lf[128]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1744,a[2]=lf[135],tmp=(C_word)a,a+=3,tmp));
t51=C_mutate((C_word*)lf[136]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1807,a[2]=lf[138],tmp=(C_word)a,a+=3,tmp));
t52=C_mutate((C_word*)lf[139]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1816,a[2]=lf[141],tmp=(C_word)a,a+=3,tmp));
t53=C_mutate((C_word*)lf[142]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1822,a[2]=lf[144],tmp=(C_word)a,a+=3,tmp));
t54=C_mutate((C_word*)lf[145]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1831,a[2]=lf[148],tmp=(C_word)a,a+=3,tmp));
t55=C_mutate((C_word*)lf[149]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1889,a[2]=lf[151],tmp=(C_word)a,a+=3,tmp));
t56=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1900,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 268  make-hash-table");
t57=C_retrieve(lf[254]);
((C_proc3)C_retrieve_proc(t57))(3,t57,t56,*((C_word*)lf[255]+1));}

/* k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_1900(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1900,2,t0,t1);}
t2=C_mutate(&lf[152],t1);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1903,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2686,a[2]=lf[252],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 270  ##sys#register-macro");
t5=C_retrieve(lf[214]);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,lf[253],t4);}

/* a2685 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2686(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word t12;
C_word t13;
C_word t14;
C_word t15;
C_word ab[18],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_2686,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_2690,a[2]=t6,a[3]=t1,a[4]=t3,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t4)[1]))){
t8=(C_word)C_i_car(((C_word*)t4)[1]);
t9=C_set_block_item(t6,0,t8);
t10=(C_word)C_i_cadr(((C_word*)t4)[1]);
t11=C_set_block_item(t4,0,t10);
t12=t7;
f_2690(2,t12,t11);}
else{
if(C_truep((C_word)C_i_stringp(((C_word*)t4)[1]))){
t8=C_set_block_item(t6,0,((C_word*)t4)[1]);
t9=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2723,a[2]=t7,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 277  string->symbol");
t10=*((C_word*)lf[250]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)t4)[1]);}
else{
if(C_truep((C_word)C_i_symbolp(((C_word*)t4)[1]))){
t8=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2733,a[2]=t7,a[3]=t6,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 279  symbol->string");
t9=*((C_word*)lf[246]+1);
((C_proc3)C_retrieve_proc(t9))(3,t9,t8,((C_word*)t4)[1]);}
else{
C_trace("ChickenBridge.scm: 281  error");
t8=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,lf[251]);}}}}

/* k2731 in a2685 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2733(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_2690(2,t3,t2);}

/* k2721 in a2685 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2723(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_2690(2,t3,t2);}

/* k2688 in a2685 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2690(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2690,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[4]);
t3=(C_word)C_a_i_list(&a,2,lf[189],t2);
t4=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_a_i_list(&a,4,lf[216],lf[249],((C_word*)((C_word*)t0)[2])[1],t3));}

/* k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_1903(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1903,2,t0,t1);}
t2=C_mutate(&lf[153],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1905,a[2]=lf[155],tmp=(C_word)a,a+=3,tmp));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2142,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2680,a[2]=lf[247],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 357  ##sys#register-macro");
t5=C_retrieve(lf[214]);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,lf[248],t4);}

/* a2679 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2680(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+6)){
C_save_and_reclaim((void*)tr3r,(void*)f_2680r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_2680r(t0,t1,t2,t3);}}

static void C_ccall f_2680r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a=C_alloc(6);
t4=t3;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1919,a[2]=t1,a[3]=t5,tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_symbolp(t2))){
C_trace("ChickenBridge.scm: 288  symbol->string");
t7=*((C_word*)lf[246]+1);
((C_proc3)C_retrieve_proc(t7))(3,t7,t6,t2);}
else{
t7=t6;
f_1919(2,t7,t2);}}

/* k1917 in a2679 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_1919(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1919,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1922,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2132,a[2]=lf[244],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 289  hash-table-ref");
t4=*((C_word*)lf[245]+1);
((C_proc5)C_retrieve_proc(t4))(5,t4,t2,lf[152],t1,t3);}

/* a2131 in k1917 in a2679 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2132(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2132,2,t0,t1);}
t2=t1;
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}

/* k1920 in k1917 in a2679 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_1922(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1922,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_1925,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=t1;
if(C_truep(t3)){
t4=t2;
f_1925(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 290  ferror");
f_1905(t2,lf[243],(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]));}}

/* k1923 in k1920 in k1917 in a2679 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_1925(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1925,2,t0,t1);}
t2=((C_word*)((C_word*)t0)[5])[1];
t3=(C_word)C_i_car(((C_word*)t0)[4]);
t4=(C_word)C_i_cdr(((C_word*)t0)[4]);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(C_word)C_i_length(t4);
t8=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_1937,a[2]=t7,a[3]=t2,a[4]=((C_word*)t0)[2],a[5]=t6,a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[3],a[8]=t4,a[9]=t3,tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 297  append");
t9=*((C_word*)lf[206]+1);
((C_proc4)C_retrieve_proc(t9))(4,t9,t8,t4,C_SCHEME_END_OF_LIST);}

/* k1935 in k1923 in k1920 in k1917 in a2679 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_1937(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[19],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1937,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_1940,a[2]=((C_word*)t0)[7],a[3]=((C_word*)t0)[8],a[4]=t1,a[5]=((C_word*)t0)[9],tmp=(C_word)a,a+=6,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_1985,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[5],a[8]=t4,a[9]=((C_word*)t0)[6],a[10]=lf[242],tmp=(C_word)a,a+=11,tmp));
t6=((C_word*)t4)[1];
f_1985(t6,t2,C_SCHEME_FALSE,C_SCHEME_FALSE,C_fix(0));}

/* do424 in k1935 in k1923 in k1920 in k1917 in a2679 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_fcall f_1985(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word t12;
C_word ab[26],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1985,NULL,5,t0,t1,t2,t3,t4);}
t5=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[9])[1]))){
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,C_SCHEME_FALSE);}
else{
t8=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_1995,a[2]=t7,a[3]=t6,a[4]=t5,a[5]=t1,a[6]=((C_word*)t0)[8],tmp=(C_word)a,a+=7,tmp);
t9=(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_2001,a[2]=((C_word*)t0)[2],a[3]=t7,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=t6,a[8]=((C_word*)t0)[6],a[9]=t5,a[10]=((C_word*)t0)[9],a[11]=t8,a[12]=((C_word*)t0)[7],tmp=(C_word)a,a+=13,tmp);
t10=((C_word*)((C_word*)t0)[7])[1];
if(C_truep(t10)){
t11=t9;
f_2001(2,t11,C_SCHEME_FALSE);}
else{
t11=(C_word)C_i_car(((C_word*)((C_word*)t0)[9])[1]);
C_trace("ChickenBridge.scm: 308  keyword?");
t12=C_retrieve(lf[240]);
((C_proc3)C_retrieve_proc(t12))(3,t12,t9,t11);}}}

/* k1999 in do424 in k1935 in k1923 in k1920 in k1917 in a2679 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2001(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word t12;
C_word t13;
C_word t14;
C_word ab[32],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2001,2,t0,t1);}
if(C_truep(t1)){
t2=C_set_block_item(((C_word*)t0)[12],0,C_SCHEME_TRUE);
t3=((C_word*)t0)[11];
f_1995(t3,t2);}
else{
t2=((C_word*)((C_word*)t0)[12])[1];
if(C_truep(t2)){
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[10])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[9])+1,t3);
t5=(C_word)C_i_assoc(((C_word*)((C_word*)t0)[9])[1],((C_word*)t0)[8]);
t6=C_mutate(((C_word *)((C_word*)t0)[7])+1,t5);
t7=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[10])[1]);
t8=C_mutate(((C_word *)((C_word*)t0)[10])+1,t7);
t9=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_2055,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[9],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[11],a[6]=((C_word*)t0)[10],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t10=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_2110,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[9],a[5]=((C_word*)t0)[5],a[6]=t9,a[7]=((C_word*)t0)[10],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 328  keyword?");
t11=C_retrieve(lf[240]);
((C_proc3)C_retrieve_proc(t11))(3,t11,t10,((C_word*)((C_word*)t0)[9])[1]);}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_2011,a[2]=((C_word*)t0)[11],a[3]=((C_word*)t0)[10],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[6],tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_nequalp(((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]))){
t4=(C_word)C_i_length(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 318  ferror");
f_1905(t3,lf[241],(C_word)C_a_i_list(&a,3,((C_word*)t0)[5],((C_word*)t0)[2],t4));}
else{
t4=t3;
f_2011(2,t4,C_SCHEME_UNDEFINED);}}}}

/* k2009 in k1999 in do424 in k1935 in k1923 in k1920 in k1917 in a2679 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2011(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2011,2,t0,t1);}
t2=(C_word)C_i_list_tail(((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]);
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
t4=(C_word)C_i_set_car(t2,t3);
t5=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[3])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t5);
t7=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[4])[1],C_fix(1));
t8=C_mutate(((C_word *)((C_word*)t0)[4])+1,t7);
t9=((C_word*)t0)[2];
f_1995(t9,t8);}

/* k2108 in k1999 in do424 in k1935 in k1923 in k1920 in k1917 in a2679 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2110(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2110,2,t0,t1);}
if(C_truep(t1)){
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[7])[1]))){
C_trace("ChickenBridge.scm: 332  ferror");
f_1905(((C_word*)t0)[6],lf[235],(C_word)C_a_i_list(&a,2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]));}
else{
t2=((C_word*)((C_word*)t0)[3])[1];
if(C_truep(t2)){
t3=((C_word*)t0)[6];
f_2055(2,t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2106,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
C_trace("map");
t4=*((C_word*)lf[237]+1);
((C_proc4)(void*)(*((C_word*)t4+1)))(4,t4,t3,*((C_word*)lf[238]+1),((C_word*)t0)[2]);}}}
else{
C_trace("ChickenBridge.scm: 329  ferror");
f_1905(((C_word*)t0)[6],lf[239],(C_word)C_a_i_list(&a,2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]));}}

/* k2104 in k2108 in k1999 in do424 in k1935 in k1923 in k1920 in k1917 in a2679 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2106(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2106,2,t0,t1);}
C_trace("ChickenBridge.scm: 335  ferror");
f_1905(((C_word*)t0)[4],lf[236],(C_word)C_a_i_list(&a,3,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1));}

/* k2053 in k1999 in do424 in k1935 in k1923 in k1920 in k1917 in a2679 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2055(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[14],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2055,2,t0,t1);}
t2=(C_word)C_i_member(((C_word*)((C_word*)t0)[8])[1],((C_word*)t0)[7]);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2061,a[2]=((C_word*)t0)[5],a[3]=t2,a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
if(C_truep(t2)){
t4=t3;
f_2061(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 342  ferror");
f_1905(t3,lf[234],(C_word)C_a_i_list(&a,3,((C_word*)t0)[4],((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]));}}

/* k2059 in k2053 in k1999 in do424 in k1935 in k1923 in k1920 in k1917 in a2679 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2061(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word *a;
t2=(C_word)C_i_car(((C_word*)((C_word*)t0)[4])[1]);
t3=(C_word)C_i_set_car(((C_word*)t0)[3],t2);
t4=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[4])[1]);
t5=C_mutate(((C_word *)((C_word*)t0)[4])+1,t4);
t6=((C_word*)t0)[2];
f_1995(t6,t5);}

/* k1993 in do424 in k1935 in k1923 in k1920 in k1917 in a2679 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_fcall f_1995(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[6])[1];
f_1985(t2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k1938 in k1935 in k1923 in k1920 in k1917 in a2679 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_1940(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1940,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_1945,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=lf[233],tmp=(C_word)a,a+=7,tmp));
t5=((C_word*)t3)[1];
f_1945(t5,((C_word*)t0)[2],((C_word*)t0)[4]);}

/* do441 in k1938 in k1935 in k1923 in k1920 in k1917 in a2679 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_fcall f_1945(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1945,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[5],((C_word*)t0)[4]));}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1958,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_member(t4,((C_word*)t0)[2]))){
t5=(C_word)C_i_car(t2);
t6=(C_word)C_i_cadr(t5);
t7=t3;
f_1958(t7,(C_word)C_i_set_car(t2,t6));}
else{
t5=t3;
f_1958(t5,C_SCHEME_UNDEFINED);}}}

/* k1956 in do441 in k1938 in k1935 in k1923 in k1920 in k1917 in a2679 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_fcall f_1958(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_1945(t3,((C_word*)t0)[2],t2);}

/* k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2142(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word ab[27],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2142,2,t0,t1);}
t2=C_mutate((C_word*)lf[156]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2144,a[2]=lf[158],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[159]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2150,a[2]=lf[161],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate((C_word*)lf[162]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2156,a[2]=lf[164],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate((C_word*)lf[165]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2162,a[2]=lf[167],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[168]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2168,a[2]=lf[170],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate((C_word*)lf[171]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2174,a[2]=lf[173],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate((C_word*)lf[174]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2180,a[2]=lf[176],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate((C_word*)lf[177]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2186,a[2]=lf[179],tmp=(C_word)a,a+=3,tmp));
t10=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2193,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 384  hash-table-set!");
t11=C_retrieve(lf[216]);
((C_proc5)C_retrieve_proc(t11))(5,t11,t10,lf[152],lf[231],lf[232]);}

/* k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2193(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2193,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2196,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 385  hash-table-set!");
t3=C_retrieve(lf[216]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[152],lf[229],lf[230]);}

/* k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2196(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2196,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2199,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 386  hash-table-set!");
t3=C_retrieve(lf[216]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[152],lf[227],lf[228]);}

/* k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2199(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2199,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2202,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 387  hash-table-set!");
t3=C_retrieve(lf[216]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[152],lf[225],lf[226]);}

/* k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2202(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2202,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2205,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 388  hash-table-set!");
t3=C_retrieve(lf[216]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[152],lf[223],lf[224]);}

/* k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2205(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2205,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2208,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 389  hash-table-set!");
t3=C_retrieve(lf[216]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[152],lf[221],lf[222]);}

/* k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2208(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2208,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2211,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 390  hash-table-set!");
t3=C_retrieve(lf[216]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[152],lf[219],lf[220]);}

/* k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2211(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2211,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2214,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 391  hash-table-set!");
t3=C_retrieve(lf[216]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[152],lf[217],lf[218]);}

/* k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2214(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2214,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2217,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2674,a[2]=lf[213],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 398  ##sys#register-macro");
t4=C_retrieve(lf[214]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,lf[215],t3);}

/* a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2674(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+17)){
C_save_and_reclaim((void*)tr4r,(void*)f_2674r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest(a,C_rest_count(0));
f_2674r(t0,t1,t2,t3,t4);}}

static void C_ccall f_2674r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word t12;
C_word t13;
C_word t14;
C_word *a=C_alloc(17);
t5=t4;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=C_SCHEME_END_OF_LIST;
t8=(*a=C_VECTOR_TYPE|1,a[1]=t7,tmp=(C_word)a,a+=2,tmp);
t9=C_SCHEME_END_OF_LIST;
t10=(*a=C_VECTOR_TYPE|1,a[1]=t9,tmp=(C_word)a,a+=2,tmp);
t11=C_SCHEME_END_OF_LIST;
t12=(*a=C_VECTOR_TYPE|1,a[1]=t11,tmp=(C_word)a,a+=2,tmp);
t13=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_2232,a[2]=t2,a[3]=t12,a[4]=t6,a[5]=t10,a[6]=t1,a[7]=t8,a[8]=t3,tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(t2))){
t14=t13;
f_2232(2,t14,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 407  error");
t14=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t14))(4,t14,t13,lf[212],t2);}}

/* k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2232(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2232,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_2235,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(((C_word*)t0)[8]))){
if(C_truep((C_word)C_i_nullp(((C_word*)t0)[8]))){
C_trace("ChickenBridge.scm: 411  error");
t3=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,lf[210]);}
else{
t3=t2;
f_2235(2,t3,C_SCHEME_UNDEFINED);}}
else{
C_trace("ChickenBridge.scm: 409  error");
t3=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t2,lf[211],((C_word*)t0)[8]);}}

/* k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2235(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2235,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_2238,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],tmp=(C_word)a,a+=8,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_2509,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[7],a[5]=t4,a[6]=lf[209],tmp=(C_word)a,a+=7,tmp));
t6=((C_word*)t4)[1];
f_2509(t6,t2,((C_word*)t0)[2]);}

/* do481 in k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_fcall f_2509(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[16],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2509,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2519,a[2]=t1,a[3]=((C_word*)t0)[5],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_2529,a[2]=t3,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=t2,tmp=(C_word)a,a+=7,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2617,a[2]=t4,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t7=(C_word)C_i_car(t2);
t8=(C_word)C_i_length(t7);
C_trace("ChickenBridge.scm: 415  <");
C_lessp(5,0,t6,C_fix(0),t8,C_fix(4));}
else{
t6=t4;
f_2529(t6,C_SCHEME_FALSE);}}}

/* k2615 in do481 in k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2617(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=(C_word)C_i_car(t2);
t4=((C_word*)t0)[2];
f_2529(t4,(C_word)C_i_symbolp(t3));}
else{
t2=((C_word*)t0)[2];
f_2529(t2,C_SCHEME_FALSE);}}

/* k2527 in do481 in k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_fcall f_2529(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2529,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[6]);
t3=(C_word)C_i_car(t2);
t4=(C_word)C_i_car(((C_word*)t0)[6]);
t5=(C_word)C_i_cadr(t4);
t6=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_2538,a[2]=t5,a[3]=t3,a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[5],tmp=(C_word)a,a+=8,tmp);
t7=(C_word)C_i_car(((C_word*)t0)[6]);
t8=(C_word)C_i_cddr(t7);
if(C_truep((C_word)C_i_nullp(t8))){
t9=t6;
f_2538(t9,lf[207]);}
else{
t9=(C_word)C_i_car(((C_word*)t0)[6]);
t10=t6;
f_2538(t10,(C_word)C_i_caddr(t9));}}
else{
t2=(C_word)C_i_car(((C_word*)t0)[6]);
C_trace("ChickenBridge.scm: 428  error");
t3=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[2],lf[208],t2);}}

/* k2536 in k2527 in do481 in k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_fcall f_2538(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2538,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_2542,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t3=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 423  append");
t4=*((C_word*)lf[206]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,((C_word*)((C_word*)t0)[7])[1],t3);}

/* k2540 in k2536 in k2527 in do481 in k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2542(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2542,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_2546,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
t4=(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 424  append");
t5=*((C_word*)lf[206]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,((C_word*)((C_word*)t0)[7])[1],t4);}

/* k2544 in k2540 in k2536 in k2527 in do481 in k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2546(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[20],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2546,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2550,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2554,a[2]=((C_word*)t0)[5],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_eqp(((C_word*)t0)[3],lf[207]);
if(C_truep(t5)){
t6=t4;
f_2554(t6,C_SCHEME_END_OF_LIST);}
else{
t6=(C_word)C_a_i_list(&a,3,lf[186],((C_word*)t0)[2],((C_word*)t0)[3]);
t7=t4;
f_2554(t7,(C_word)C_a_i_list(&a,1,t6));}}

/* k2552 in k2544 in k2540 in k2536 in k2527 in do481 in k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_fcall f_2554(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 425  append");
t2=*((C_word*)lf[206]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k2548 in k2544 in k2540 in k2536 in k2527 in do481 in k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2550(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_2519(2,t3,t2);}

/* k2517 in do481 in k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2519(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_2509(t3,((C_word*)t0)[2],t2);}

/* k2236 in k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2238(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2238,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_2241,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 430  gensym");
t3=C_retrieve(lf[205]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k2239 in k2236 in k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2241(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2241,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_2244,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 431  gensym");
t3=C_retrieve(lf[205]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k2242 in k2239 in k2236 in k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2244(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2244,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_2247,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 432  gensym");
t3=C_retrieve(lf[205]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k2245 in k2242 in k2239 in k2236 in k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2247(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2247,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_2250,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],a[10]=((C_word*)t0)[9],tmp=(C_word)a,a+=11,tmp);
C_trace("ChickenBridge.scm: 433  gensym");
t3=C_retrieve(lf[205]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k2248 in k2245 in k2242 in k2239 in k2236 in k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2250(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word ab[26],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2250,2,t0,t1);}
t2=C_SCHEME_TRUE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_SCHEME_END_OF_LIST;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_2253,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=t3,a[7]=((C_word*)t0)[5],a[8]=((C_word*)t0)[6],a[9]=((C_word*)t0)[7],a[10]=((C_word*)t0)[8],a[11]=((C_word*)t0)[9],a[12]=t5,a[13]=((C_word*)t0)[10],tmp=(C_word)a,a+=14,tmp);
t7=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2402,a[2]=t6,a[3]=t3,a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)((C_word*)t0)[3])[1]))){
t8=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
if(C_truep((C_word)C_i_pairp(t8))){
t9=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2503,a[2]=t7,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 439  caar");
t10=*((C_word*)lf[201]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)((C_word*)t0)[3])[1]);}
else{
t9=t7;
f_2402(t9,C_SCHEME_FALSE);}}
else{
t8=t7;
f_2402(t8,C_SCHEME_FALSE);}}

/* k2501 in k2248 in k2245 in k2242 in k2239 in k2236 in k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2503(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_2402(t2,(C_word)C_eqp(t1,lf[204]));}

/* k2400 in k2248 in k2245 in k2242 in k2239 in k2236 in k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_fcall f_2402(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2402,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2409,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 440  cdar");
t3=*((C_word*)lf[199]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)((C_word*)t0)[4])[1]);}
else{
t2=((C_word*)t0)[2];
f_2253(2,t2,C_SCHEME_UNDEFINED);}}

/* k2407 in k2400 in k2248 in k2245 in k2242 in k2239 in k2236 in k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2409(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2409,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_2411,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=lf[203],tmp=(C_word)a,a+=6,tmp));
t5=((C_word*)t3)[1];
f_2411(t5,((C_word*)t0)[2],t1);}

/* do497 in k2407 in k2400 in k2248 in k2245 in k2242 in k2239 in k2236 in k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_fcall f_2411(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[13],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2411,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[4])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[4])+1,t3);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,t4);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2425,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2435,a[2]=t2,a[3]=((C_word*)t0)[2],a[4]=t3,tmp=(C_word)a,a+=5,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2483,a[2]=t4,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 444  cdar");
t7=*((C_word*)lf[199]+1);
((C_proc3)C_retrieve_proc(t7))(3,t7,t6,t2);}
else{
t6=t4;
f_2435(t6,C_SCHEME_FALSE);}}}

/* k2481 in do497 in k2407 in k2400 in k2248 in k2245 in k2242 in k2239 in k2236 in k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2483(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_2435(t2,(C_word)C_i_pairp(t1));}

/* k2433 in do497 in k2407 in k2400 in k2248 in k2245 in k2242 in k2239 in k2236 in k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_fcall f_2435(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2435,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2438,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 445  caar");
t3=*((C_word*)lf[201]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)t0)[2]);}
else{
t2=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 451  error");
t3=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[4],lf[202],t2);}}

/* k2436 in k2433 in do497 in k2407 in k2400 in k2248 in k2245 in k2242 in k2239 in k2236 in k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2438(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2438,2,t0,t1);}
t2=(C_word)C_eqp(t1,lf[198]);
if(C_truep(t2)){
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2459,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 447  cdar");
t4=*((C_word*)lf[199]+1);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)t0)[2]);}
else{
t3=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 450  error");
t4=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,((C_word*)t0)[4],lf[200],t3);}}

/* k2457 in k2436 in k2433 in do497 in k2407 in k2400 in k2248 in k2245 in k2242 in k2239 in k2236 in k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2459(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep((C_word)C_i_car(t1))){
t2=((C_word*)t0)[3];
f_2425(2,t2,C_SCHEME_UNDEFINED);}
else{
t2=C_set_block_item(((C_word*)t0)[2],0,C_SCHEME_FALSE);
t3=((C_word*)t0)[3];
f_2425(2,t3,t2);}}

/* k2423 in do497 in k2407 in k2400 in k2248 in k2245 in k2242 in k2239 in k2236 in k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2425(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_2411(t3,((C_word*)t0)[2],t2);}

/* k2251 in k2248 in k2245 in k2242 in k2239 in k2236 in k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2253(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2253,2,t0,t1);}
t2=(C_word)C_i_car(((C_word*)t0)[13]);
t3=(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_2391,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],a[10]=((C_word*)t0)[10],a[11]=((C_word*)t0)[11],a[12]=((C_word*)t0)[12],a[13]=t2,tmp=(C_word)a,a+=14,tmp);
t4=(C_word)C_i_cdr(((C_word*)t0)[13]);
t5=(C_word)C_a_i_list(&a,1,C_fix(-1));
C_trace("ChickenBridge.scm: 402  ##sys#append");
t6=*((C_word*)lf[197]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t3,t4,t5);}

/* k2389 in k2251 in k2248 in k2245 in k2242 in k2239 in k2236 in k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2391(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2391,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[13],t1);
t3=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_2375,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],a[8]=((C_word*)t0)[10],a[9]=((C_word*)t0)[11],a[10]=((C_word*)t0)[12],a[11]=t2,tmp=(C_word)a,a+=12,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2379,a[2]=((C_word*)t0)[3],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_a_i_list(&a,1,((C_word*)t0)[10]);
C_trace("ChickenBridge.scm: 402  ##sys#append");
t6=*((C_word*)lf[197]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t4,((C_word*)((C_word*)t0)[2])[1],t5);}

/* k2377 in k2389 in k2251 in k2248 in k2245 in k2242 in k2239 in k2236 in k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2379(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 402  ##sys#append");
t2=*((C_word*)lf[197]+1);
((C_proc4)(void*)(*((C_word*)t2+1)))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k2373 in k2389 in k2251 in k2248 in k2245 in k2242 in k2239 in k2236 in k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2375(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word t12;
C_word t13;
C_word t14;
C_word t15;
C_word t16;
C_word t17;
C_word t18;
C_word t19;
C_word t20;
C_word ab[116],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2375,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,lf[181],t1);
t3=(C_word)C_a_i_list(&a,3,lf[182],((C_word*)t0)[11],t2);
t4=C_mutate(((C_word *)((C_word*)t0)[10])+1,t3);
t5=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_2260,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],a[5]=((C_word*)t0)[10],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],tmp=(C_word)a,a+=8,tmp);
if(C_truep(((C_word*)((C_word*)t0)[4])[1])){
t6=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
t7=(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]);
t8=(C_word)C_a_i_list(&a,2,lf[189],lf[190]);
t9=(C_word)C_a_i_list(&a,2,lf[189],lf[191]);
t10=(C_word)C_a_i_list(&a,3,lf[192],t8,t9);
t11=(C_word)C_a_i_list(&a,2,t10,((C_word*)t0)[2]);
t12=(C_word)C_a_i_list(&a,4,lf[193],lf[194],((C_word*)t0)[9],t11);
t13=(C_word)C_a_i_list(&a,2,((C_word*)t0)[3],C_fix(-2));
t14=(C_word)C_a_i_list(&a,4,lf[183],t7,t12,t13);
t15=(C_word)C_a_i_list(&a,3,lf[183],C_SCHEME_END_OF_LIST,((C_word*)((C_word*)t0)[10])[1]);
t16=(C_word)C_a_i_list(&a,3,lf[195],t14,t15);
t17=(C_word)C_a_i_list(&a,3,lf[183],t6,t16);
t18=(C_word)C_a_i_list(&a,2,lf[196],t17);
t19=C_mutate(((C_word *)((C_word*)t0)[10])+1,t18);
t20=t5;
f_2260(t20,t19);}
else{
t6=t5;
f_2260(t6,C_SCHEME_UNDEFINED);}}

/* k2258 in k2373 in k2389 in k2251 in k2248 in k2245 in k2242 in k2239 in k2236 in k2233 in k2230 in a2673 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_fcall f_2260(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word t12;
C_word t13;
C_word t14;
C_word ab[90],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2260,NULL,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,((C_word*)t0)[7]);
t3=(C_word)C_a_i_list(&a,2,((C_word*)t0)[6],C_fix(0));
t4=(C_word)C_a_i_list(&a,3,lf[183],C_SCHEME_END_OF_LIST,((C_word*)t0)[7]);
t5=(C_word)C_a_i_list(&a,2,lf[184],t4);
t6=(C_word)C_a_i_list(&a,1,lf[185]);
t7=(C_word)C_a_i_list(&a,3,lf[186],((C_word*)t0)[6],lf[185]);
t8=(C_word)C_a_i_list(&a,3,lf[183],t6,t7);
t9=(C_word)C_a_i_list(&a,2,lf[187],t8);
t10=(C_word)C_a_i_list(&a,3,t3,t5,t9);
t11=(C_word)C_a_i_list(&a,3,lf[188],t10,((C_word*)((C_word*)t0)[5])[1]);
t12=(C_word)C_a_i_list(&a,3,lf[183],t2,t11);
t13=(C_word)C_a_i_list(&a,3,lf[183],((C_word*)((C_word*)t0)[4])[1],t12);
t14=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t14+1)))(2,t14,(C_word)C_a_i_cons(&a,2,t13,((C_word*)((C_word*)t0)[2])[1]));}

/* k2215 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2217(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2217,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2672,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 495  return-to-host");
t3=C_retrieve(lf[180]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k2670 in k2215 in k2212 in k2209 in k2206 in k2203 in k2200 in k2197 in k2194 in k2191 in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2672(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_UNDEFINED);}

/* mp:inhook in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2186(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2186,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 380  error");
t3=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[178]);}

/* mp:micro in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2180(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2180,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 378  error");
t3=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[175]);}

/* mp:alloff in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2174(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2174,2,t0,t1);}
C_trace("ChickenBridge.scm: 376  error");
t2=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,t1,lf[172]);}

/* mp:ctrl in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2168(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_2168,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 374  error");
t6=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[169]);}

/* mp:prog in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2162(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_2162,5,t0,t1,t2,t3,t4);}
C_trace("ChickenBridge.scm: 372  error");
t5=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t5))(3,t5,t1,lf[166]);}

/* mp:off in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2156(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_2156,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 370  error");
t6=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[163]);}

/* mp:on in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2150(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_2150,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 368  error");
t6=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[160]);}

/* mp:note in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_2144(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
C_word tmp;
C_word t7;
C_word t8;
C_word ab[8],*a=ab;
if(c!=7) C_bad_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr7,(void*)f_2144,7,t0,t1,t2,t3,t4,t5,t6);}
t7=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_1461,a[2]=t1,a[3]=t6,a[4]=t5,a[5]=t4,a[6]=t3,a[7]=t2,tmp=(C_word)a,a+=8,tmp);
C_trace("##sys#gc");
t8=C_retrieve(lf[111]);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,C_SCHEME_FALSE);}

/* k1459 in mp:note in k2140 in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_1461(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1461,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[7]);
t4=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[6]);
t5=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[5]);
t6=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[4]);
t7=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[3]);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub296,a[2]=lf[157],tmp=(C_word)a,a+=3,tmp);
((C_proc8)C_retrieve_proc(t8))(8,t8,((C_word*)t0)[2],t2,t3,t4,t5,t6,t7);}

/* ferror in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_fcall f_1905(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1905,NULL,3,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1913,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_apply(5,0,t4,C_retrieve(lf[154]),t2,t3);}

/* k1911 in ferror in k1901 in k1898 in k574 in k571 in k568 in k565 */
static void C_ccall f_1913(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 285  error");
t2=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* hush in k574 in k571 in k568 in k565 */
static void C_ccall f_1889(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1889,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1893,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1571,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[111]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k1569 in hush in k574 in k571 in k568 in k565 */
static void C_ccall f_1571(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1571,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub349,a[2]=lf[150],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k1891 in hush in k574 in k571 in k568 in k565 */
static void C_ccall f_1893(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 262  values");
C_values(2,0,((C_word*)t0)[2]);}

/* stop in k574 in k571 in k568 in k565 */
static void C_ccall f_1831(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+9)){
C_save_and_reclaim((void*)tr2r,(void*)f_1831r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_1831r(t0,t1,t2);}}

static void C_ccall f_1831r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a=C_alloc(9);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1835,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 252  scheduler-stop");
f_1554(t3,C_fix(-1));}
else{
t4=C_SCHEME_UNDEFINED;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_set_block_item(t5,0,(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1849,a[2]=t5,a[3]=lf[147],tmp=(C_word)a,a+=4,tmp));
t7=((C_word*)t5)[1];
f_1849(t7,t3,t2);}}

/* do399 in stop in k574 in k571 in k568 in k565 */
static void C_fcall f_1849(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1849,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1859,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_fixnump(t4))){
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 256  scheduler-stop");
f_1554(t3,t5);}
else{
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 257  error");
t6=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t3,lf[146],t5);}}}

/* k1857 in do399 in stop in k574 in k571 in k568 in k565 */
static void C_ccall f_1859(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_1849(t3,((C_word*)t0)[2],t2);}

/* k1833 in stop in k574 in k571 in k568 in k565 */
static void C_ccall f_1835(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 258  values");
C_values(2,0,((C_word*)t0)[2]);}

/* cont in k574 in k571 in k568 in k565 */
static void C_ccall f_1822(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1822,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1826,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1549,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[111]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k1547 in cont in k574 in k571 in k568 in k565 */
static void C_ccall f_1549(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1549,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub339,a[2]=lf[143],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k1824 in cont in k574 in k571 in k568 in k565 */
static void C_ccall f_1826(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 248  values");
C_values(2,0,((C_word*)t0)[2]);}

/* paused? in k574 in k571 in k568 in k565 */
static void C_ccall f_1816(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1816,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1531,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t3=C_retrieve(lf[111]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,C_SCHEME_FALSE);}

/* k1529 in paused? in k574 in k571 in k568 in k565 */
static void C_ccall f_1531(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1531,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub331,a[2]=lf[140],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* pause in k574 in k571 in k568 in k565 */
static void C_ccall f_1807(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1807,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1811,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1540,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[111]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k1538 in pause in k574 in k571 in k568 in k565 */
static void C_ccall f_1540(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1540,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub335,a[2]=lf[137],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k1809 in pause in k574 in k571 in k568 in k565 */
static void C_ccall f_1811(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 241  values");
C_values(2,0,((C_word*)t0)[2]);}

/* time-format in k574 in k571 in k568 in k565 */
static void C_ccall f_1744(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+11)){
C_save_and_reclaim((void*)tr2rv,(void*)f_1744r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_1744r(t0,t1,t2);}}

static void C_ccall f_1744r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word *a=C_alloc(11);
if(C_truep((C_word)C_vemptyp(t2))){
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1757,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1496,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t5=C_retrieve(lf[111]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,C_SCHEME_FALSE);}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
t4=(C_word)C_i_eqvp(t3,lf[131]);
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1769,a[2]=t2,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
if(C_truep(t4)){
t6=t5;
f_1769(t6,t4);}
else{
t6=(C_word)C_eqp(t3,C_fix(1));
t7=t5;
f_1769(t7,(C_truep(t6)?t6:(C_word)C_eqp(t3,lf[134])));}}}

/* k1767 in time-format in k574 in k571 in k568 in k565 */
static void C_fcall f_1769(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a;
if(C_truep(t1)){
t2=C_mutate((C_word*)lf[127]+1,*((C_word*)lf[107]+1));
C_trace("ChickenBridge.scm: 230  scheduler-set-time-milliseconds");
f_1501(((C_word*)t0)[4],C_SCHEME_FALSE);}
else{
t2=(C_word)C_eqp(((C_word*)t0)[3],C_fix(1000));
t3=(C_truep(t2)?t2:(C_word)C_eqp(((C_word*)t0)[3],lf[132]));
if(C_truep(t3)){
t4=C_mutate((C_word*)lf[127]+1,*((C_word*)lf[105]+1));
C_trace("ChickenBridge.scm: 234  scheduler-set-time-milliseconds");
f_1501(((C_word*)t0)[4],C_SCHEME_TRUE);}
else{
t4=(C_word)C_i_vector_ref(((C_word*)t0)[2],C_fix(0));
C_trace("ChickenBridge.scm: 237  error");
t5=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,((C_word*)t0)[4],lf[133],t4);}}}

/* k1494 in time-format in k574 in k571 in k568 in k565 */
static void C_ccall f_1496(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1496,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub311,a[2]=lf[130],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k1755 in time-format in k574 in k571 in k568 in k565 */
static void C_ccall f_1757(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_truep(t1)?C_fix(1000):lf[129]));}

/* sprout in k574 in k571 in k568 in k565 */
static void C_ccall f_1576(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+12)){
C_save_and_reclaim((void*)tr3r,(void*)f_1576r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_1576r(t0,t1,t2,t3);}}

static void C_ccall f_1576r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word *a=C_alloc(12);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1578,a[2]=t2,a[3]=lf[123],tmp=(C_word)a,a+=4,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1690,a[2]=t4,a[3]=lf[124],tmp=(C_word)a,a+=4,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1695,a[2]=t5,a[3]=lf[125],tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("def-start359380");
t7=t6;
f_1695(t7,t1);}
else{
t7=(C_word)C_i_car(t3);
t8=(C_word)C_i_cdr(t3);
if(C_truep((C_word)C_i_nullp(t8))){
C_trace("def-id360378");
t9=t5;
f_1690(t9,t1,t7);}
else{
t9=(C_word)C_i_car(t8);
t10=(C_word)C_i_cdr(t8);
if(C_truep((C_word)C_i_nullp(t10))){
C_trace("body357362");
t11=t4;
f_1578(t11,t1,t7,t9);}
else{
C_trace("##sys#error");
t11=*((C_word*)lf[38]+1);
((C_proc4)(void*)(*((C_word*)t11+1)))(4,t11,t1,lf[0],t10);}}}}

/* def-start359 in sprout in k574 in k571 in k568 in k565 */
static void C_fcall f_1695(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1695,NULL,2,t0,t1);}
C_trace("def-id360378");
t2=((C_word*)t0)[2];
f_1690(t2,t1,C_fix(0));}

/* def-id360 in sprout in k574 in k571 in k568 in k565 */
static void C_fcall f_1690(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1690,NULL,3,t0,t1,t2);}
C_trace("body357362");
t3=((C_word*)t0)[2];
f_1578(t3,t1,t2,C_fix(-1));}

/* body357 in sprout in k574 in k571 in k568 in k565 */
static void C_fcall f_1578(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word t12;
C_word t13;
C_word t14;
C_word ab[33],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1578,NULL,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1580,a[2]=t4,a[3]=lf[120],tmp=(C_word)a,a+=4,tmp);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1608,a[2]=t5,a[3]=lf[121],tmp=(C_word)a,a+=4,tmp);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1638,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t0)[2]))){
t9=C_SCHEME_UNDEFINED;
t10=(*a=C_VECTOR_TYPE|1,a[1]=t9,tmp=(C_word)a,a+=2,tmp);
t11=C_set_block_item(t10,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_1649,a[2]=t6,a[3]=t7,a[4]=t10,a[5]=((C_word*)t0)[2],a[6]=lf[122],tmp=(C_word)a,a+=7,tmp));
t12=((C_word*)t10)[1];
f_1649(t12,t8,((C_word*)t0)[2]);}
else{
t9=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1681,a[2]=((C_word*)t0)[2],a[3]=t8,tmp=(C_word)a,a+=4,tmp);
t10=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1685,a[2]=t7,a[3]=((C_word*)t0)[2],a[4]=t9,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 216  nextstart");
t11=t6;
f_1580(t11,t10);}}

/* k1683 in body357 in sprout in k574 in k571 in k568 in k565 */
static void C_ccall f_1685(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1685,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1689,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 216  nextid");
t3=((C_word*)t0)[2];
f_1608(t3,t2);}

/* k1687 in k1683 in body357 in sprout in k574 in k571 in k568 in k565 */
static void C_ccall f_1689(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 216  scheduler-sprout");
f_1510(((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k1679 in body357 in sprout in k574 in k571 in k568 in k565 */
static void C_ccall f_1681(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
f_1638(2,t2,((C_word*)t0)[2]);}

/* do371 in body357 in sprout in k574 in k571 in k568 in k565 */
static void C_fcall f_1649(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1649,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,((C_word*)t0)[5]);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1659,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1674,a[2]=((C_word*)t0)[3],a[3]=t4,a[4]=t3,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 214  nextstart");
t6=((C_word*)t0)[2];
f_1580(t6,t5);}}

/* k1672 in do371 in body357 in sprout in k574 in k571 in k568 in k565 */
static void C_ccall f_1674(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1674,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1678,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 214  nextid");
t3=((C_word*)t0)[2];
f_1608(t3,t2);}

/* k1676 in k1672 in do371 in body357 in sprout in k574 in k571 in k568 in k565 */
static void C_ccall f_1678(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 214  scheduler-sprout");
f_1510(((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k1657 in do371 in body357 in sprout in k574 in k571 in k568 in k565 */
static void C_ccall f_1659(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_1649(t3,((C_word*)t0)[2],t2);}

/* k1636 in body357 in sprout in k574 in k571 in k568 in k565 */
static void C_ccall f_1638(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 220  values");
C_values(2,0,((C_word*)t0)[2]);}

/* nextid in body357 in sprout in k574 in k571 in k568 in k565 */
static void C_fcall f_1608(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1608,NULL,2,t0,t1);}
if(C_truep((C_word)C_i_pairp(((C_word*)((C_word*)t0)[2])[1]))){
t2=(C_word)C_i_car(((C_word*)((C_word*)t0)[2])[1]);
t3=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[2])[1]);
t4=(C_word)C_i_nullp(t3);
t5=(C_truep(t4)?(C_word)C_i_car(((C_word*)((C_word*)t0)[2])[1]):(C_word)C_i_cdr(((C_word*)((C_word*)t0)[2])[1]));
t6=C_mutate(((C_word *)((C_word*)t0)[2])+1,t5);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,t2);}
else{
t2=t1;
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,((C_word*)((C_word*)t0)[2])[1]);}}

/* nextstart in body357 in sprout in k574 in k571 in k568 in k565 */
static void C_fcall f_1580(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1580,NULL,2,t0,t1);}
if(C_truep((C_word)C_i_pairp(((C_word*)((C_word*)t0)[2])[1]))){
t2=(C_word)C_i_car(((C_word*)((C_word*)t0)[2])[1]);
t3=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[2])[1]);
t4=(C_word)C_i_nullp(t3);
t5=(C_truep(t4)?(C_word)C_i_car(((C_word*)((C_word*)t0)[2])[1]):(C_word)C_i_cdr(((C_word*)((C_word*)t0)[2])[1]));
t6=C_mutate(((C_word *)((C_word*)t0)[2])+1,t5);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,t2);}
else{
t2=t1;
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,((C_word*)((C_word*)t0)[2])[1]);}}

/* scheduler-stop in k574 in k571 in k568 in k565 */
static void C_fcall f_1554(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1554,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1558,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[111]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k1556 in scheduler-stop in k574 in k571 in k568 in k565 */
static void C_ccall f_1558(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1558,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_fixnum_argumentp(((C_word*)t0)[3]);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub344,a[2]=lf[117],tmp=(C_word)a,a+=3,tmp);
((C_proc4)C_retrieve_proc(t4))(4,t4,((C_word*)t0)[2],t2,t3);}

/* scheduler-sprout in k574 in k571 in k568 in k565 */
static void C_fcall f_1510(C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1510,NULL,4,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_1514,a[2]=t2,a[3]=t1,a[4]=t4,a[5]=t3,tmp=(C_word)a,a+=6,tmp);
C_trace("##sys#gc");
t6=C_retrieve(lf[111]);
((C_proc3)C_retrieve_proc(t6))(3,t6,t5,C_SCHEME_FALSE);}

/* k1512 in scheduler-sprout in k574 in k571 in k568 in k565 */
static void C_ccall f_1514(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1514,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[5]);
t4=(C_word)C_i_foreign_fixnum_argumentp(((C_word*)t0)[4]);
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub324,a[2]=lf[114],tmp=(C_word)a,a+=3,tmp);
((C_proc6)C_retrieve_proc(t5))(6,t5,((C_word*)t0)[3],t2,((C_word*)t0)[2],t3,t4);}

/* scheduler-set-time-milliseconds in k574 in k571 in k568 in k565 */
static void C_fcall f_1501(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1501,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1505,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[111]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k1503 in scheduler-set-time-milliseconds in k574 in k571 in k568 in k565 */
static void C_ccall f_1505(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1505,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub316,a[2]=lf[110],tmp=(C_word)a,a+=3,tmp);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[3],t2,((C_word*)t0)[2]);}

/* current-time-seconds in k574 in k571 in k568 in k565 */
static void C_ccall f_1489(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1489,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub308(t2));}

/* current-time-milliseconds in k574 in k571 in k568 in k565 */
static void C_ccall f_1486(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1486,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub305(t2));}

/* print-error in k574 in k571 in k568 in k565 */
static void C_ccall f_1443(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1443,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1448,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[101]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_1448(2,t4,C_SCHEME_FALSE);}}

/* k1446 in print-error in k574 in k571 in k568 in k565 */
static void C_ccall f_1448(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub286(C_SCHEME_UNDEFINED,t1));}

/* print-message in k574 in k571 in k568 in k565 */
static void C_ccall f_1429(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1429,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1434,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[101]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_1434(2,t4,C_SCHEME_FALSE);}}

/* k1432 in print-message in k574 in k571 in k568 in k565 */
static void C_ccall f_1434(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub280(C_SCHEME_UNDEFINED,t1));}

/* ranpink in k574 in k571 in k568 in k565 */
static void C_ccall f_1423(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1423,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub145(t2));}

/* ranbrown in k574 in k571 in k568 in k565 */
static void C_ccall f_1417(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1417,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub148(t2));}

/* rangamma in k574 in k571 in k568 in k565 */
static void C_ccall f_1398(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2rv,(void*)f_1398r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_1398r(t0,t1,t2);}}

static void C_ccall f_1398r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
if(C_truep((C_word)C_vemptyp(t2))){
C_trace("ChickenBridge.scm: 102  tb:rangamma");
f_788(t1,C_fix(1));}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
C_trace("ChickenBridge.scm: 102  tb:rangamma");
f_788(t1,t3);}}

/* ranpoisson in k574 in k571 in k568 in k565 */
static void C_ccall f_1379(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2rv,(void*)f_1379r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_1379r(t0,t1,t2);}}

static void C_ccall f_1379r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
if(C_truep((C_word)C_i_nullp(C_retrieve(lf[92])))){
C_trace("ChickenBridge.scm: 102  tb:ranpoisson");
f_798(t1,C_fix(1));}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
C_trace("ChickenBridge.scm: 102  tb:ranpoisson");
f_798(t1,t3);}}

/* rancauchy in k574 in k571 in k568 in k565 */
static void C_ccall f_1373(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1373,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub138(t2));}

/* rangauss in k574 in k571 in k568 in k565 */
static void C_ccall f_1333(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2r,(void*)f_1333r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_1333r(t0,t1,t2);}}

static void C_ccall f_1333r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 102  tb:rangauss");
f_759(t1,C_fix(1),C_fix(0));}
else{
t3=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 102  tb:rangauss");
f_759(t1,t4,C_fix(0));}
else{
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cdr(t2);
C_trace("ChickenBridge.scm: 102  tb:rangauss");
f_759(t1,t4,t5);}}}

/* ranexp in k574 in k571 in k568 in k565 */
static void C_ccall f_1314(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2rv,(void*)f_1314r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_1314r(t0,t1,t2);}}

static void C_ccall f_1314r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
if(C_truep((C_word)C_vemptyp(t2))){
C_trace("ChickenBridge.scm: 102  tb:ranexp");
f_770(t1,C_fix(1));}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
C_trace("ChickenBridge.scm: 102  tb:ranexp");
f_770(t1,t3);}}

/* ranbeta in k574 in k571 in k568 in k565 */
static void C_ccall f_1270(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2r,(void*)f_1270r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_1270r(t0,t1,t2);}}

static void C_ccall f_1270r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 102  tb:ranbeta");
f_777(t1,lf[82],lf[83]);}
else{
t3=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 102  tb:ranbeta");
f_777(t1,t4,t5);}
else{
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cadr(t2);
C_trace("ChickenBridge.scm: 102  tb:ranbeta");
f_777(t1,t4,t5);}}}

/* ranmiddle in k574 in k571 in k568 in k565 */
static void C_ccall f_1264(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1264,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub111(t2));}

/* ranhigh in k574 in k571 in k568 in k565 */
static void C_ccall f_1258(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1258,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub108(t2));}

/* ranlow in k574 in k571 in k568 in k565 */
static void C_ccall f_1252(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1252,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub105(t2));}

/* pick in k574 in k571 in k568 in k565 */
static void C_ccall f_1246(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2r,(void*)f_1246r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_1246r(t0,t1,t2);}}

static void C_ccall f_1246r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_trace("ChickenBridge.scm: 102  pickl");
t3=*((C_word*)lf[70]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,t2);}

/* pickl in k574 in k571 in k568 in k565 */
static void C_ccall f_1223(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1223,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 102  error");
t3=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t1,lf[71],t2);}
else{
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1240,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
t4=(C_word)C_i_length(t2);
C_trace("ChickenBridge.scm: 102  tb:rani");
f_714(t3,t4);}}

/* k1238 in pickl in k574 in k571 in k568 in k565 */
static void C_ccall f_1240(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_i_list_ref(((C_word*)t0)[2],t1));}

/* odds in k574 in k571 in k568 in k565 */
static void C_ccall f_1165(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+14)){
C_save_and_reclaim((void*)tr3r,(void*)f_1165r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_1165r(t0,t1,t2,t3);}}

static void C_ccall f_1165r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word *a=C_alloc(14);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1182,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 102  tb:ranf");
f_721(t4,lf[66]);}
else{
t4=(C_word)C_i_cdr(t3);
if(C_truep((C_word)C_i_nullp(t4))){
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1201,a[2]=t3,a[3]=t1,a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 102  tb:ranf");
f_721(t5,lf[67]);}
else{
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1217,a[2]=t3,a[3]=t1,a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 102  tb:ranf");
f_721(t5,lf[68]);}}}

/* k1215 in odds in k574 in k571 in k568 in k565 */
static void C_ccall f_1217(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_lessp(t1,((C_word*)t0)[4]);
t3=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_truep(t2)?(C_word)C_i_car(((C_word*)t0)[2]):(C_word)C_i_cadr(((C_word*)t0)[2])));}

/* k1199 in odds in k574 in k571 in k568 in k565 */
static void C_ccall f_1201(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_lessp(t1,((C_word*)t0)[4]);
t3=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_truep(t2)?(C_word)C_i_car(((C_word*)t0)[2]):C_SCHEME_FALSE));}

/* k1180 in odds in k574 in k571 in k568 in k565 */
static void C_ccall f_1182(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_lessp(t1,((C_word*)t0)[3]);
t3=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_truep(t2)?C_SCHEME_TRUE:C_SCHEME_FALSE));}

/* ran in k574 in k571 in k568 in k565 */
static void C_ccall f_1077(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+4)){
C_save_and_reclaim((void*)tr2r,(void*)f_1077r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_1077r(t0,t1,t2);}}

static void C_ccall f_1077r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word *a=C_alloc(4);
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 102  tb:ranf");
f_721(t1,lf[63]);}
else{
t3=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_fixnump(t4))){
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 102  tb:rani");
f_714(t1,t5);}
else{
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 102  tb:ranf");
f_721(t1,t5);}}
else{
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1123,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_fixnump(t5))){
t6=(C_word)C_i_cadr(t2);
t7=t4;
f_1123(t7,(C_word)C_fixnump(t6));}
else{
t6=t4;
f_1123(t6,C_SCHEME_FALSE);}}}}

/* k1121 in ran in k574 in k571 in k568 in k565 */
static void C_fcall f_1123(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word t12;
C_word t13;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1123,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=(C_word)C_i_cadr(((C_word*)t0)[3]);
t4=((C_word*)t0)[2];
t5=(C_word)C_i_foreign_fixnum_argumentp(t2);
t6=(C_word)C_i_foreign_fixnum_argumentp(t3);
t7=t4;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub94(C_SCHEME_UNDEFINED,t5,t6));}
else{
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=(C_word)C_i_cadr(((C_word*)t0)[3]);
t4=((C_word*)t0)[2];
t5=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t6=(C_word)C_i_foreign_flonum_argumentp(t2);
t7=(C_word)C_i_foreign_flonum_argumentp(t3);
t8=t4;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,(C_word)stub100(t5,t6,t7));}}

/* ran-set! in k574 in k571 in k568 in k565 */
static void C_ccall f_1071(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1071,3,t0,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub80(C_SCHEME_UNDEFINED,t2));}

/* interp in k574 in k571 in k568 in k565 */
static void C_ccall f_1065(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr3r,(void*)f_1065r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_1065r(t0,t1,t2,t3);}}

static void C_ccall f_1065r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_trace("ChickenBridge.scm: 102  interpl");
t4=*((C_word*)lf[50]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t1,t2,t3);}

/* interpl in k574 in k571 in k568 in k565 */
static void C_ccall f_970(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+6)){
C_save_and_reclaim((void*)tr4rv,(void*)f_970r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest_vector(a,C_rest_count(0));
f_970r(t0,t1,t2,t3,t4);}}

static void C_ccall f_970r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word *a=C_alloc(6);
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_974,a[2]=t1,a[3]=t2,a[4]=t3,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("ChickenBridge.scm: 102  error");
t6=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t5,lf[56],t3);}
else{
t6=t5;
f_974(2,t6,(C_word)C_i_car(t3));}}

/* k972 in interpl in k574 in k571 in k568 in k565 */
static void C_ccall f_974(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_974,2,t0,t1);}
t2=t1;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_977,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=t3,tmp=(C_word)a,a+=7,tmp);
t5=(C_word)C_i_cdr(((C_word*)t0)[4]);
if(C_truep((C_word)C_i_nullp(t5))){
C_trace("ChickenBridge.scm: 102  err");
t6=C_retrieve(lf[54]);
((C_proc4)C_retrieve_proc(t6))(4,t6,t4,lf[55],((C_word*)t0)[4]);}
else{
t6=t4;
f_977(2,t6,(C_word)C_i_cadr(((C_word*)t0)[4]));}}

/* k975 in k972 in interpl in k574 in k571 in k568 in k565 */
static void C_ccall f_977(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word t12;
C_word t13;
C_word t14;
C_word ab[19],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_977,2,t0,t1);}
t2=t1;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=((C_word*)((C_word*)t0)[6])[1];
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=((C_word*)t3)[1];
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=(C_word)C_vemptyp(((C_word*)t0)[5]);
t9=(C_truep(t8)?C_fix(1):(C_word)C_i_vector_ref(((C_word*)t0)[5],C_fix(0)));
t10=(C_word)C_i_cddr(((C_word*)t0)[4]);
t11=C_SCHEME_UNDEFINED;
t12=(*a=C_VECTOR_TYPE|1,a[1]=t11,tmp=(C_word)a,a+=2,tmp);
t13=C_set_block_item(t12,0,(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_989,a[2]=((C_word*)t0)[4],a[3]=t12,a[4]=t9,a[5]=t7,a[6]=t3,a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[3],a[9]=t5,a[10]=lf[53],tmp=(C_word)a,a+=11,tmp));
t14=((C_word*)t12)[1];
f_989(t14,((C_word*)t0)[2],t10);}

/* do201 in k975 in k972 in interpl in k574 in k571 in k568 in k565 */
static void C_fcall f_989(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word t12;
C_word t13;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_989,NULL,3,t0,t1,t2);}
t3=(C_word)C_i_nullp(t2);
t4=(C_truep(t3)?t3:(C_word)C_i_greaterp(((C_word*)((C_word*)t0)[9])[1],((C_word*)t0)[8]));
if(C_truep(t4)){
C_trace("ChickenBridge.scm: 102  tb:rescale");
f_578(t1,((C_word*)t0)[8],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[9])[1],((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[4]);}
else{
t5=C_mutate(((C_word *)((C_word*)t0)[7])+1,((C_word*)((C_word*)t0)[9])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[6])+1,((C_word*)((C_word*)t0)[5])[1]);
t7=(C_word)C_i_car(t2);
t8=C_mutate(((C_word *)((C_word*)t0)[9])+1,t7);
t9=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1011,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t10=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t10))){
C_trace("ChickenBridge.scm: 102  error");
t11=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t11))(4,t11,t9,lf[52],((C_word*)t0)[2]);}
else{
t11=(C_word)C_i_cadr(t2);
t12=C_mutate(((C_word *)((C_word*)t0)[5])+1,t11);
t13=t9;
f_1011(2,t13,t12);}}}

/* k1009 in do201 in k975 in k972 in interpl in k574 in k571 in k568 in k565 */
static void C_ccall f_1011(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cddr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_989(t3,((C_word*)t0)[2],t2);}

/* hertz->keynum in k574 in k571 in k568 in k565 */
static void C_ccall f_964(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_964,3,t0,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub75(t3,t4));}

/* keynum->pc in k574 in k571 in k568 in k565 */
static void C_ccall f_958(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_958,3,t0,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub71(C_SCHEME_UNDEFINED,t3));}

/* keynum->hertz in k574 in k571 in k568 in k565 */
static void C_ccall f_952(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_952,3,t0,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub66(t3,t4));}

/* scaler->cents in k574 in k571 in k568 in k565 */
static void C_ccall f_946(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_946,3,t0,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub62(C_SCHEME_UNDEFINED,t3));}

/* cents->scaler in k574 in k571 in k568 in k565 */
static void C_ccall f_940(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_940,3,t0,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_fixnum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub57(t3,t4));}

/* rhythm->seconds in k574 in k571 in k568 in k565 */
static void C_ccall f_880(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+12)){
C_save_and_reclaim((void*)tr3r,(void*)f_880r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_880r(t0,t1,t2,t3);}}

static void C_ccall f_880r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word *a=C_alloc(12);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_882,a[2]=t2,a[3]=lf[33],tmp=(C_word)a,a+=4,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_887,a[2]=t4,a[3]=lf[35],tmp=(C_word)a,a+=4,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_892,a[2]=t5,a[3]=lf[37],tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("def-tempo174182");
t7=t6;
f_892(t7,t1);}
else{
t7=(C_word)C_i_car(t3);
t8=(C_word)C_i_cdr(t3);
if(C_truep((C_word)C_i_nullp(t8))){
C_trace("def-beat175180");
t9=t5;
f_887(t9,t1,t7);}
else{
t9=(C_word)C_i_car(t8);
t10=(C_word)C_i_cdr(t8);
if(C_truep((C_word)C_i_nullp(t10))){
C_trace("body172177");
t11=t4;
f_882(t11,t1,t7,t9);}
else{
C_trace("##sys#error");
t11=*((C_word*)lf[38]+1);
((C_proc4)(void*)(*((C_word*)t11+1)))(4,t11,t1,lf[0],t10);}}}}

/* def-tempo174 in rhythm->seconds in k574 in k571 in k568 in k565 */
static void C_fcall f_892(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_892,NULL,2,t0,t1);}
C_trace("def-beat175180");
t2=((C_word*)t0)[2];
f_887(t2,t1,lf[36]);}

/* def-beat175 in rhythm->seconds in k574 in k571 in k568 in k565 */
static void C_fcall f_887(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_887,NULL,3,t0,t1,t2);}
C_trace("body172177");
t3=((C_word*)t0)[2];
f_882(t3,t1,t2,lf[34]);}

/* body172 in rhythm->seconds in k574 in k571 in k568 in k565 */
static void C_fcall f_882(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_882,NULL,4,t0,t1,t2,t3);}
t4=((C_word*)t0)[2];
t5=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t6=(C_word)C_i_foreign_flonum_argumentp(t4);
t7=(C_word)C_i_foreign_flonum_argumentp(t2);
t8=(C_word)C_i_foreign_flonum_argumentp(t3);
t9=t1;
((C_proc2)(void*)(*((C_word*)t9+1)))(2,t9,(C_word)stub50(t5,t6,t7,t8));}

/* decimals in k574 in k571 in k568 in k565 */
static void C_ccall f_861(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr3rv,(void*)f_861r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest_vector(a,C_rest_count(0));
f_861r(t0,t1,t2,t3);}}

static void C_ccall f_861r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
if(C_truep((C_word)C_vemptyp(t3))){
C_trace("ChickenBridge.scm: 102  tb:decimals");
f_639(t1,t2,C_fix(3));}
else{
t4=(C_word)C_i_vector_ref(t3,C_fix(0));
C_trace("ChickenBridge.scm: 102  tb:decimals");
f_639(t1,t2,t4);}}

/* quantize in k574 in k571 in k568 in k565 */
static void C_ccall f_855(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_855,4,t0,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_flonum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub42(t4,t5,t6));}

/* int in k574 in k571 in k568 in k565 */
static void C_ccall f_849(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_849,3,t0,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub30(C_SCHEME_UNDEFINED,t3));}

/* discrete in k574 in k571 in k568 in k565 */
static void C_ccall f_830(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,...){
C_word tmp;
C_word t7;
va_list v;
C_word *a,c2=c;
C_save_rest(t6,c2,7);
if(c<7) C_bad_min_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr7rv,(void*)f_830r,7,t0,t1,t2,t3,t4,t5,t6);}
else{
a=C_alloc((c-7)*3);
t7=C_restore_rest_vector(a,C_rest_count(0));
f_830r(t0,t1,t2,t3,t4,t5,t6,t7);}}

static void C_ccall f_830r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
C_word tmp;
C_word t8;
C_word t9;
if(C_truep((C_word)C_vemptyp(t7))){
C_trace("ChickenBridge.scm: 102  tb:discrete");
f_605(t1,t2,t3,t4,t5,t6,C_fix(1));}
else{
t8=(C_word)C_i_vector_ref(t7,C_fix(0));
C_trace("ChickenBridge.scm: 102  tb:discrete");
f_605(t1,t2,t3,t4,t5,t6,t8);}}

/* rescale in k574 in k571 in k568 in k565 */
static void C_ccall f_811(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,...){
C_word tmp;
C_word t7;
va_list v;
C_word *a,c2=c;
C_save_rest(t6,c2,7);
if(c<7) C_bad_min_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr7rv,(void*)f_811r,7,t0,t1,t2,t3,t4,t5,t6);}
else{
a=C_alloc((c-7)*3);
t7=C_restore_rest_vector(a,C_rest_count(0));
f_811r(t0,t1,t2,t3,t4,t5,t6,t7);}}

static void C_ccall f_811r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
C_word tmp;
C_word t8;
C_word t9;
if(C_truep((C_word)C_vemptyp(t7))){
C_trace("ChickenBridge.scm: 102  tb:rescale");
f_578(t1,t2,t3,t4,t5,t6,C_fix(1));}
else{
t8=(C_word)C_i_vector_ref(t7,C_fix(0));
C_trace("ChickenBridge.scm: 102  tb:rescale");
f_578(t1,t2,t3,t4,t5,t6,t8);}}

/* tb:ranpoisson in k574 in k571 in k568 in k565 */
static void C_fcall f_798(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_798,NULL,2,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub142(C_SCHEME_UNDEFINED,t3));}

/* tb:rangamma in k574 in k571 in k568 in k565 */
static void C_fcall f_788(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_788,NULL,2,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub134(t3,t4));}

/* tb:ranbeta in k574 in k571 in k568 in k565 */
static void C_fcall f_777(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_777,NULL,3,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_flonum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub128(t4,t5,t6));}

/* tb:ranexp in k574 in k571 in k568 in k565 */
static void C_fcall f_770(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_770,NULL,2,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub122(t3,t4));}

/* tb:rangauss in k574 in k571 in k568 in k565 */
static void C_fcall f_759(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_759,NULL,3,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_flonum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub116(t4,t5,t6));}

/* tb:ranf in k574 in k571 in k568 in k565 */
static void C_fcall f_721(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_721,NULL,2,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub88(t3,t4));}

/* tb:rani in k574 in k571 in k568 in k565 */
static void C_fcall f_714(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_714,NULL,2,t1,t2);}
t3=(C_word)C_i_foreign_fixnum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub84(C_SCHEME_UNDEFINED,t3));}

/* tb:decimals in k574 in k571 in k568 in k565 */
static void C_fcall f_639(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_639,NULL,3,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_fixnum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub35(t4,t5,t6));}

/* tb:discrete in k574 in k571 in k568 in k565 */
static void C_fcall f_605(C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
C_word tmp;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word t12;
C_word t13;
C_word t14;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_605,NULL,7,t1,t2,t3,t4,t5,t6,t7);}
t8=(C_word)C_i_foreign_flonum_argumentp(t2);
t9=(C_word)C_i_foreign_flonum_argumentp(t3);
t10=(C_word)C_i_foreign_flonum_argumentp(t4);
t11=(C_word)C_i_foreign_fixnum_argumentp(t5);
t12=(C_word)C_i_foreign_fixnum_argumentp(t6);
t13=(C_word)C_i_foreign_flonum_argumentp(t7);
t14=t1;
((C_proc2)(void*)(*((C_word*)t14+1)))(2,t14,(C_word)stub21(C_SCHEME_UNDEFINED,t8,t9,t10,t11,t12,t13));}

/* tb:rescale in k574 in k571 in k568 in k565 */
static void C_fcall f_578(C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
C_word tmp;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word t12;
C_word t13;
C_word t14;
C_word t15;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_578,NULL,7,t1,t2,t3,t4,t5,t6,t7);}
t8=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t9=(C_word)C_i_foreign_flonum_argumentp(t2);
t10=(C_word)C_i_foreign_flonum_argumentp(t3);
t11=(C_word)C_i_foreign_flonum_argumentp(t4);
t12=(C_word)C_i_foreign_flonum_argumentp(t5);
t13=(C_word)C_i_foreign_flonum_argumentp(t6);
t14=(C_word)C_i_foreign_flonum_argumentp(t7);
t15=t1;
((C_proc2)(void*)(*((C_word*)t15+1)))(2,t15,(C_word)stub6(t8,t9,t10,t11,t12,t13,t14));}

#ifdef C_ENABLE_PTABLES
static C_PTABLE_ENTRY ptable[178] = {
{"toplevelChickenBridge.scm",(void*)C_grace_toplevel},
{"f_567ChickenBridge.scm",(void*)f_567},
{"f_570ChickenBridge.scm",(void*)f_570},
{"f_573ChickenBridge.scm",(void*)f_573},
{"f_576ChickenBridge.scm",(void*)f_576},
{"f_1900ChickenBridge.scm",(void*)f_1900},
{"f_2686ChickenBridge.scm",(void*)f_2686},
{"f_2733ChickenBridge.scm",(void*)f_2733},
{"f_2723ChickenBridge.scm",(void*)f_2723},
{"f_2690ChickenBridge.scm",(void*)f_2690},
{"f_1903ChickenBridge.scm",(void*)f_1903},
{"f_2680ChickenBridge.scm",(void*)f_2680},
{"f_1919ChickenBridge.scm",(void*)f_1919},
{"f_2132ChickenBridge.scm",(void*)f_2132},
{"f_1922ChickenBridge.scm",(void*)f_1922},
{"f_1925ChickenBridge.scm",(void*)f_1925},
{"f_1937ChickenBridge.scm",(void*)f_1937},
{"f_1985ChickenBridge.scm",(void*)f_1985},
{"f_2001ChickenBridge.scm",(void*)f_2001},
{"f_2011ChickenBridge.scm",(void*)f_2011},
{"f_2110ChickenBridge.scm",(void*)f_2110},
{"f_2106ChickenBridge.scm",(void*)f_2106},
{"f_2055ChickenBridge.scm",(void*)f_2055},
{"f_2061ChickenBridge.scm",(void*)f_2061},
{"f_1995ChickenBridge.scm",(void*)f_1995},
{"f_1940ChickenBridge.scm",(void*)f_1940},
{"f_1945ChickenBridge.scm",(void*)f_1945},
{"f_1958ChickenBridge.scm",(void*)f_1958},
{"f_2142ChickenBridge.scm",(void*)f_2142},
{"f_2193ChickenBridge.scm",(void*)f_2193},
{"f_2196ChickenBridge.scm",(void*)f_2196},
{"f_2199ChickenBridge.scm",(void*)f_2199},
{"f_2202ChickenBridge.scm",(void*)f_2202},
{"f_2205ChickenBridge.scm",(void*)f_2205},
{"f_2208ChickenBridge.scm",(void*)f_2208},
{"f_2211ChickenBridge.scm",(void*)f_2211},
{"f_2214ChickenBridge.scm",(void*)f_2214},
{"f_2674ChickenBridge.scm",(void*)f_2674},
{"f_2232ChickenBridge.scm",(void*)f_2232},
{"f_2235ChickenBridge.scm",(void*)f_2235},
{"f_2509ChickenBridge.scm",(void*)f_2509},
{"f_2617ChickenBridge.scm",(void*)f_2617},
{"f_2529ChickenBridge.scm",(void*)f_2529},
{"f_2538ChickenBridge.scm",(void*)f_2538},
{"f_2542ChickenBridge.scm",(void*)f_2542},
{"f_2546ChickenBridge.scm",(void*)f_2546},
{"f_2554ChickenBridge.scm",(void*)f_2554},
{"f_2550ChickenBridge.scm",(void*)f_2550},
{"f_2519ChickenBridge.scm",(void*)f_2519},
{"f_2238ChickenBridge.scm",(void*)f_2238},
{"f_2241ChickenBridge.scm",(void*)f_2241},
{"f_2244ChickenBridge.scm",(void*)f_2244},
{"f_2247ChickenBridge.scm",(void*)f_2247},
{"f_2250ChickenBridge.scm",(void*)f_2250},
{"f_2503ChickenBridge.scm",(void*)f_2503},
{"f_2402ChickenBridge.scm",(void*)f_2402},
{"f_2409ChickenBridge.scm",(void*)f_2409},
{"f_2411ChickenBridge.scm",(void*)f_2411},
{"f_2483ChickenBridge.scm",(void*)f_2483},
{"f_2435ChickenBridge.scm",(void*)f_2435},
{"f_2438ChickenBridge.scm",(void*)f_2438},
{"f_2459ChickenBridge.scm",(void*)f_2459},
{"f_2425ChickenBridge.scm",(void*)f_2425},
{"f_2253ChickenBridge.scm",(void*)f_2253},
{"f_2391ChickenBridge.scm",(void*)f_2391},
{"f_2379ChickenBridge.scm",(void*)f_2379},
{"f_2375ChickenBridge.scm",(void*)f_2375},
{"f_2260ChickenBridge.scm",(void*)f_2260},
{"f_2217ChickenBridge.scm",(void*)f_2217},
{"f_2672ChickenBridge.scm",(void*)f_2672},
{"f_2186ChickenBridge.scm",(void*)f_2186},
{"f_2180ChickenBridge.scm",(void*)f_2180},
{"f_2174ChickenBridge.scm",(void*)f_2174},
{"f_2168ChickenBridge.scm",(void*)f_2168},
{"f_2162ChickenBridge.scm",(void*)f_2162},
{"f_2156ChickenBridge.scm",(void*)f_2156},
{"f_2150ChickenBridge.scm",(void*)f_2150},
{"f_2144ChickenBridge.scm",(void*)f_2144},
{"f_1461ChickenBridge.scm",(void*)f_1461},
{"f_1905ChickenBridge.scm",(void*)f_1905},
{"f_1913ChickenBridge.scm",(void*)f_1913},
{"f_1889ChickenBridge.scm",(void*)f_1889},
{"f_1571ChickenBridge.scm",(void*)f_1571},
{"f_1893ChickenBridge.scm",(void*)f_1893},
{"f_1831ChickenBridge.scm",(void*)f_1831},
{"f_1849ChickenBridge.scm",(void*)f_1849},
{"f_1859ChickenBridge.scm",(void*)f_1859},
{"f_1835ChickenBridge.scm",(void*)f_1835},
{"f_1822ChickenBridge.scm",(void*)f_1822},
{"f_1549ChickenBridge.scm",(void*)f_1549},
{"f_1826ChickenBridge.scm",(void*)f_1826},
{"f_1816ChickenBridge.scm",(void*)f_1816},
{"f_1531ChickenBridge.scm",(void*)f_1531},
{"f_1807ChickenBridge.scm",(void*)f_1807},
{"f_1540ChickenBridge.scm",(void*)f_1540},
{"f_1811ChickenBridge.scm",(void*)f_1811},
{"f_1744ChickenBridge.scm",(void*)f_1744},
{"f_1769ChickenBridge.scm",(void*)f_1769},
{"f_1496ChickenBridge.scm",(void*)f_1496},
{"f_1757ChickenBridge.scm",(void*)f_1757},
{"f_1576ChickenBridge.scm",(void*)f_1576},
{"f_1695ChickenBridge.scm",(void*)f_1695},
{"f_1690ChickenBridge.scm",(void*)f_1690},
{"f_1578ChickenBridge.scm",(void*)f_1578},
{"f_1685ChickenBridge.scm",(void*)f_1685},
{"f_1689ChickenBridge.scm",(void*)f_1689},
{"f_1681ChickenBridge.scm",(void*)f_1681},
{"f_1649ChickenBridge.scm",(void*)f_1649},
{"f_1674ChickenBridge.scm",(void*)f_1674},
{"f_1678ChickenBridge.scm",(void*)f_1678},
{"f_1659ChickenBridge.scm",(void*)f_1659},
{"f_1638ChickenBridge.scm",(void*)f_1638},
{"f_1608ChickenBridge.scm",(void*)f_1608},
{"f_1580ChickenBridge.scm",(void*)f_1580},
{"f_1554ChickenBridge.scm",(void*)f_1554},
{"f_1558ChickenBridge.scm",(void*)f_1558},
{"f_1510ChickenBridge.scm",(void*)f_1510},
{"f_1514ChickenBridge.scm",(void*)f_1514},
{"f_1501ChickenBridge.scm",(void*)f_1501},
{"f_1505ChickenBridge.scm",(void*)f_1505},
{"f_1489ChickenBridge.scm",(void*)f_1489},
{"f_1486ChickenBridge.scm",(void*)f_1486},
{"f_1443ChickenBridge.scm",(void*)f_1443},
{"f_1448ChickenBridge.scm",(void*)f_1448},
{"f_1429ChickenBridge.scm",(void*)f_1429},
{"f_1434ChickenBridge.scm",(void*)f_1434},
{"f_1423ChickenBridge.scm",(void*)f_1423},
{"f_1417ChickenBridge.scm",(void*)f_1417},
{"f_1398ChickenBridge.scm",(void*)f_1398},
{"f_1379ChickenBridge.scm",(void*)f_1379},
{"f_1373ChickenBridge.scm",(void*)f_1373},
{"f_1333ChickenBridge.scm",(void*)f_1333},
{"f_1314ChickenBridge.scm",(void*)f_1314},
{"f_1270ChickenBridge.scm",(void*)f_1270},
{"f_1264ChickenBridge.scm",(void*)f_1264},
{"f_1258ChickenBridge.scm",(void*)f_1258},
{"f_1252ChickenBridge.scm",(void*)f_1252},
{"f_1246ChickenBridge.scm",(void*)f_1246},
{"f_1223ChickenBridge.scm",(void*)f_1223},
{"f_1240ChickenBridge.scm",(void*)f_1240},
{"f_1165ChickenBridge.scm",(void*)f_1165},
{"f_1217ChickenBridge.scm",(void*)f_1217},
{"f_1201ChickenBridge.scm",(void*)f_1201},
{"f_1182ChickenBridge.scm",(void*)f_1182},
{"f_1077ChickenBridge.scm",(void*)f_1077},
{"f_1123ChickenBridge.scm",(void*)f_1123},
{"f_1071ChickenBridge.scm",(void*)f_1071},
{"f_1065ChickenBridge.scm",(void*)f_1065},
{"f_970ChickenBridge.scm",(void*)f_970},
{"f_974ChickenBridge.scm",(void*)f_974},
{"f_977ChickenBridge.scm",(void*)f_977},
{"f_989ChickenBridge.scm",(void*)f_989},
{"f_1011ChickenBridge.scm",(void*)f_1011},
{"f_964ChickenBridge.scm",(void*)f_964},
{"f_958ChickenBridge.scm",(void*)f_958},
{"f_952ChickenBridge.scm",(void*)f_952},
{"f_946ChickenBridge.scm",(void*)f_946},
{"f_940ChickenBridge.scm",(void*)f_940},
{"f_880ChickenBridge.scm",(void*)f_880},
{"f_892ChickenBridge.scm",(void*)f_892},
{"f_887ChickenBridge.scm",(void*)f_887},
{"f_882ChickenBridge.scm",(void*)f_882},
{"f_861ChickenBridge.scm",(void*)f_861},
{"f_855ChickenBridge.scm",(void*)f_855},
{"f_849ChickenBridge.scm",(void*)f_849},
{"f_830ChickenBridge.scm",(void*)f_830},
{"f_811ChickenBridge.scm",(void*)f_811},
{"f_798ChickenBridge.scm",(void*)f_798},
{"f_788ChickenBridge.scm",(void*)f_788},
{"f_777ChickenBridge.scm",(void*)f_777},
{"f_770ChickenBridge.scm",(void*)f_770},
{"f_759ChickenBridge.scm",(void*)f_759},
{"f_721ChickenBridge.scm",(void*)f_721},
{"f_714ChickenBridge.scm",(void*)f_714},
{"f_639ChickenBridge.scm",(void*)f_639},
{"f_605ChickenBridge.scm",(void*)f_605},
{"f_578ChickenBridge.scm",(void*)f_578},
{NULL,NULL}};
#endif

static C_PTABLE_ENTRY *create_ptable(void){
#ifdef C_ENABLE_PTABLES
return ptable;
#else
return NULL;
#endif
}
/* end of file */
