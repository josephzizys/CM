/* Generated from ChickenBridge.scm by the CHICKEN compiler
   http://www.call-with-current-continuation.org
   2007-11-17 09:24
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

static C_TLS C_word lf[263];


/* from k1697 in hush in k595 in k592 in k589 in k586 */
C_noret_decl(stub370)
static void C_ccall stub370(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub370(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_hush();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1691 */
C_noret_decl(stub365)
static void C_ccall stub365(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0) C_noret;
static void C_ccall stub365(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_unfix(C_a0);
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_stop(t0);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1675 in cont in k595 in k592 in k589 in k586 */
C_noret_decl(stub360)
static void C_ccall stub360(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub360(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_cont();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1666 in pause in k595 in k592 in k589 in k586 */
C_noret_decl(stub356)
static void C_ccall stub356(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub356(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_pause();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1657 in paused? in k595 in k592 in k589 in k586 */
C_noret_decl(stub352)
static void C_ccall stub352(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub352(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
C_r=C_mk_bool(scheduler_is_paused());
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1651 */
C_noret_decl(stub345)
static void C_ccall stub345(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2) C_noret;
static void C_ccall stub345(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
C_word t0=(C_word )(C_a0);
double t1=(double )C_c_double(C_a1);
int t2=(int )C_unfix(C_a2);
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_sprout(t0,t1,t2);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1631 in scheduler-set-time-milliseconds in k595 in k592 in k589 in k586 */
C_noret_decl(stub337)
static void C_ccall stub337(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0) C_noret;
static void C_ccall stub337(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_truep(C_a0);
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_set_time_milliseconds(t0);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1622 in time-format in k595 in k592 in k589 in k586 */
C_noret_decl(stub332)
static void C_ccall stub332(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub332(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
C_r=C_mk_bool(scheduler_is_time_milliseconds());
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from current-time-seconds in k595 in k592 in k589 in k586 */
#define return(x) C_cblock C_r = (C_flonum(&C_a,(x))); goto C_ret; C_cblockend
static C_word C_fcall stub329(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub329(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
 C_return( (Time::getMillisecondCounterHiRes() / 1000.0) );
C_ret:
#undef return

return C_r;}

/* from current-time-milliseconds in k595 in k592 in k589 in k586 */
#define return(x) C_cblock C_r = (C_flonum(&C_a,(x))); goto C_ret; C_cblockend
static C_word C_fcall stub326(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub326(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
 C_return( Time::getMillisecondCounterHiRes());
C_ret:
#undef return

return C_r;}

/* from k1610 */
C_noret_decl(stub317)
static void C_ccall stub317(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2,C_word C_a3,C_word C_a4) C_noret;
static void C_ccall stub317(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2,C_word C_a3,C_word C_a4){
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

/* from k1574 in print-error in k595 in k592 in k589 in k586 */
static C_word C_fcall stub307(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub307(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_error(t0);
return C_r;}

/* from k1560 in print-message in k595 in k592 in k589 in k586 */
static C_word C_fcall stub301(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub301(C_word C_buf,C_word C_a0){
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

/* from k822 */
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

/* from k812 */
static C_word C_fcall stub134(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub134(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::rangamma(t0));
return C_r;}

/* from k805 */
static C_word C_fcall stub128(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub128(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
C_r=C_flonum(&C_a,Toolbox::ranbeta(t0,t1));
return C_r;}

/* from k794 */
static C_word C_fcall stub122(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub122(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::ranexp(t0));
return C_r;}

/* from k787 */
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

/* from k767 */
static C_word C_fcall stub100(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub100(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
C_r=C_flonum(&C_a,Toolbox::ran(t0,t1));
return C_r;}

/* from k756 */
static C_word C_fcall stub94(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub94(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_unfix(C_a0);
int t1=(int )C_unfix(C_a1);
C_r=C_fix((C_word)Toolbox::ran(t0,t1));
return C_r;}

/* from k745 */
static C_word C_fcall stub88(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub88(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::ran(t0));
return C_r;}

/* from k738 */
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

/* from k728 */
static C_word C_fcall stub75(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub75(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::hertz_to_keynum(t0));
return C_r;}

/* from k721 */
static C_word C_fcall stub71(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub71(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_fix((C_word)Toolbox::keynum_to_pc(t0));
return C_r;}

/* from k714 */
static C_word C_fcall stub66(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub66(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::keynum_to_hertz(t0));
return C_r;}

/* from k707 */
static C_word C_fcall stub62(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub62(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_fix((C_word)Toolbox::scaler_to_cents(t0));
return C_r;}

/* from k700 */
static C_word C_fcall stub57(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub57(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_unfix(C_a0);
C_r=C_flonum(&C_a,Toolbox::cents_to_scaler(t0));
return C_r;}

/* from k693 */
static C_word C_fcall stub50(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2) C_regparm;
C_regparm static C_word C_fcall stub50(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
float t2=(float )C_c_double(C_a2);
C_r=C_flonum(&C_a,Toolbox::rhythm_to_seconds(t0,t1,t2));
return C_r;}

/* from k678 */
static C_word C_fcall stub42(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub42(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
C_r=C_flonum(&C_a,Toolbox::quantize(t0,t1));
return C_r;}

/* from k667 */
static C_word C_fcall stub35(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub35(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
int t1=(int )C_unfix(C_a1);
C_r=C_flonum(&C_a,Toolbox::decimals(t0,t1));
return C_r;}

/* from k656 */
static C_word C_fcall stub30(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub30(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_fix((C_word)Toolbox::float_to_fixnum(t0));
return C_r;}

/* from k649 */
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

/* from k622 */
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
C_noret_decl(f_588)
static void C_ccall f_588(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_591)
static void C_ccall f_591(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_594)
static void C_ccall f_594(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_597)
static void C_ccall f_597(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2028)
static void C_ccall f_2028(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2814)
static void C_ccall f_2814(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_2861)
static void C_ccall f_2861(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2851)
static void C_ccall f_2851(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2818)
static void C_ccall f_2818(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2031)
static void C_ccall f_2031(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2808)
static void C_ccall f_2808(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_2808)
static void C_ccall f_2808r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_2047)
static void C_ccall f_2047(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2260)
static void C_ccall f_2260(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2050)
static void C_ccall f_2050(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2053)
static void C_ccall f_2053(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2065)
static void C_ccall f_2065(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2113)
static void C_fcall f_2113(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_2129)
static void C_ccall f_2129(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2139)
static void C_ccall f_2139(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2238)
static void C_ccall f_2238(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2234)
static void C_ccall f_2234(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2183)
static void C_ccall f_2183(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2189)
static void C_ccall f_2189(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2123)
static void C_fcall f_2123(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2068)
static void C_ccall f_2068(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2073)
static void C_fcall f_2073(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2086)
static void C_fcall f_2086(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2270)
static void C_ccall f_2270(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2321)
static void C_ccall f_2321(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2324)
static void C_ccall f_2324(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2327)
static void C_ccall f_2327(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2330)
static void C_ccall f_2330(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2333)
static void C_ccall f_2333(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2336)
static void C_ccall f_2336(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2339)
static void C_ccall f_2339(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2342)
static void C_ccall f_2342(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2802)
static void C_ccall f_2802(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_2802)
static void C_ccall f_2802r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_2360)
static void C_ccall f_2360(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2363)
static void C_ccall f_2363(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2637)
static void C_fcall f_2637(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2745)
static void C_ccall f_2745(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2657)
static void C_fcall f_2657(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2666)
static void C_fcall f_2666(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2670)
static void C_ccall f_2670(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2674)
static void C_ccall f_2674(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2682)
static void C_fcall f_2682(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2678)
static void C_ccall f_2678(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2647)
static void C_ccall f_2647(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2366)
static void C_ccall f_2366(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2369)
static void C_ccall f_2369(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2372)
static void C_ccall f_2372(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2375)
static void C_ccall f_2375(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2378)
static void C_ccall f_2378(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2631)
static void C_ccall f_2631(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2530)
static void C_fcall f_2530(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2537)
static void C_ccall f_2537(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2539)
static void C_fcall f_2539(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2611)
static void C_ccall f_2611(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2563)
static void C_fcall f_2563(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2566)
static void C_ccall f_2566(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2587)
static void C_ccall f_2587(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2553)
static void C_ccall f_2553(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2381)
static void C_ccall f_2381(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2519)
static void C_ccall f_2519(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2507)
static void C_ccall f_2507(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2503)
static void C_ccall f_2503(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2388)
static void C_fcall f_2388(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2345)
static void C_ccall f_2345(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2800)
static void C_ccall f_2800(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2314)
static void C_ccall f_2314(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2308)
static void C_ccall f_2308(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2302)
static void C_ccall f_2302(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2296)
static void C_ccall f_2296(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_2290)
static void C_ccall f_2290(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_2284)
static void C_ccall f_2284(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_2278)
static void C_ccall f_2278(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_2272)
static void C_ccall f_2272(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_1589)
static void C_ccall f_1589(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2033)
static void C_fcall f_2033(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2041)
static void C_ccall f_2041(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2017)
static void C_ccall f_2017(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1699)
static void C_ccall f_1699(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2021)
static void C_ccall f_2021(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1959)
static void C_ccall f_1959(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1959)
static void C_ccall f_1959r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1977)
static void C_fcall f_1977(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1987)
static void C_ccall f_1987(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1963)
static void C_ccall f_1963(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1950)
static void C_ccall f_1950(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1677)
static void C_ccall f_1677(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1954)
static void C_ccall f_1954(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1944)
static void C_ccall f_1944(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1659)
static void C_ccall f_1659(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1935)
static void C_ccall f_1935(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1668)
static void C_ccall f_1668(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1939)
static void C_ccall f_1939(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1872)
static void C_ccall f_1872(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1872)
static void C_ccall f_1872r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1897)
static void C_fcall f_1897(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1624)
static void C_ccall f_1624(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1885)
static void C_ccall f_1885(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1704)
static void C_ccall f_1704(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_1704)
static void C_ccall f_1704r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_1823)
static void C_fcall f_1823(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1818)
static void C_fcall f_1818(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1706)
static void C_fcall f_1706(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_1813)
static void C_ccall f_1813(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1817)
static void C_ccall f_1817(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1809)
static void C_ccall f_1809(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1777)
static void C_fcall f_1777(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1802)
static void C_ccall f_1802(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1806)
static void C_ccall f_1806(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1787)
static void C_ccall f_1787(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1766)
static void C_ccall f_1766(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1736)
static void C_fcall f_1736(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1708)
static void C_fcall f_1708(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1682)
static void C_fcall f_1682(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1686)
static void C_ccall f_1686(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1638)
static void C_fcall f_1638(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_1642)
static void C_ccall f_1642(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1629)
static void C_fcall f_1629(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1633)
static void C_ccall f_1633(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1617)
static void C_ccall f_1617(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1614)
static void C_ccall f_1614(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1571)
static void C_ccall f_1571(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1576)
static void C_ccall f_1576(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1557)
static void C_ccall f_1557(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1562)
static void C_ccall f_1562(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1551)
static void C_ccall f_1551(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1545)
static void C_ccall f_1545(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1526)
static void C_ccall f_1526(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1526)
static void C_ccall f_1526r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1507)
static void C_ccall f_1507(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1507)
static void C_ccall f_1507r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1501)
static void C_ccall f_1501(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1461)
static void C_ccall f_1461(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1461)
static void C_ccall f_1461r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1442)
static void C_ccall f_1442(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1442)
static void C_ccall f_1442r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1398)
static void C_ccall f_1398(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1398)
static void C_ccall f_1398r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1392)
static void C_ccall f_1392(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1386)
static void C_ccall f_1386(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1380)
static void C_ccall f_1380(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1374)
static void C_ccall f_1374(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1374)
static void C_ccall f_1374r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1351)
static void C_ccall f_1351(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1368)
static void C_ccall f_1368(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1293)
static void C_ccall f_1293(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_1293)
static void C_ccall f_1293r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_1345)
static void C_ccall f_1345(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1329)
static void C_ccall f_1329(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1310)
static void C_ccall f_1310(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1205)
static void C_ccall f_1205(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1205)
static void C_ccall f_1205r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1251)
static void C_fcall f_1251(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1199)
static void C_ccall f_1199(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1140)
static void C_ccall f_1140(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_1140)
static void C_ccall f_1140r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_1153)
static void C_fcall f_1153(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_1189)
static void C_ccall f_1189(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1134)
static void C_ccall f_1134(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_1134)
static void C_ccall f_1134r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_1039)
static void C_ccall f_1039(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_1039)
static void C_ccall f_1039r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_1043)
static void C_ccall f_1043(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1046)
static void C_ccall f_1046(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1058)
static void C_fcall f_1058(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1080)
static void C_ccall f_1080(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1033)
static void C_ccall f_1033(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1027)
static void C_ccall f_1027(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1021)
static void C_ccall f_1021(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1015)
static void C_ccall f_1015(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1009)
static void C_ccall f_1009(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_949)
static void C_ccall f_949(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_949)
static void C_ccall f_949r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_961)
static void C_fcall f_961(C_word t0,C_word t1) C_noret;
C_noret_decl(f_956)
static void C_fcall f_956(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_951)
static void C_fcall f_951(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_930)
static void C_ccall f_930(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_930)
static void C_ccall f_930r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_924)
static void C_ccall f_924(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_918)
static void C_ccall f_918(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_870)
static void C_ccall f_870(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,...) C_noret;
C_noret_decl(f_870)
static void C_ccall f_870r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t7) C_noret;
C_noret_decl(f_878)
static void C_ccall f_878(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_851)
static void C_ccall f_851(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,...) C_noret;
C_noret_decl(f_851)
static void C_ccall f_851r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t8) C_noret;
C_noret_decl(f_832)
static void C_ccall f_832(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,...) C_noret;
C_noret_decl(f_832)
static void C_ccall f_832r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t8) C_noret;
C_noret_decl(f_819)
static void C_fcall f_819(C_word t0,C_word t1) C_noret;
C_noret_decl(f_809)
static void C_fcall f_809(C_word t0,C_word t1) C_noret;
C_noret_decl(f_798)
static void C_fcall f_798(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_791)
static void C_fcall f_791(C_word t0,C_word t1) C_noret;
C_noret_decl(f_780)
static void C_fcall f_780(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_742)
static void C_fcall f_742(C_word t0,C_word t1) C_noret;
C_noret_decl(f_735)
static void C_fcall f_735(C_word t0,C_word t1) C_noret;
C_noret_decl(f_660)
static void C_fcall f_660(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_626)
static void C_fcall f_626(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_599)
static void C_fcall f_599(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;

C_noret_decl(trf_2113)
static void C_fcall trf_2113(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2113(void *dummy){
C_word t4=C_pick(0);
C_word t3=C_pick(1);
C_word t2=C_pick(2);
C_word t1=C_pick(3);
C_word t0=C_pick(4);
C_adjust_stack(-5);
f_2113(t0,t1,t2,t3,t4);}

C_noret_decl(trf_2123)
static void C_fcall trf_2123(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2123(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2123(t0,t1);}

C_noret_decl(trf_2073)
static void C_fcall trf_2073(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2073(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_2073(t0,t1,t2);}

C_noret_decl(trf_2086)
static void C_fcall trf_2086(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2086(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2086(t0,t1);}

C_noret_decl(trf_2637)
static void C_fcall trf_2637(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2637(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_2637(t0,t1,t2);}

C_noret_decl(trf_2657)
static void C_fcall trf_2657(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2657(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2657(t0,t1);}

C_noret_decl(trf_2666)
static void C_fcall trf_2666(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2666(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2666(t0,t1);}

C_noret_decl(trf_2682)
static void C_fcall trf_2682(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2682(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2682(t0,t1);}

C_noret_decl(trf_2530)
static void C_fcall trf_2530(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2530(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2530(t0,t1);}

C_noret_decl(trf_2539)
static void C_fcall trf_2539(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2539(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_2539(t0,t1,t2);}

C_noret_decl(trf_2563)
static void C_fcall trf_2563(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2563(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2563(t0,t1);}

C_noret_decl(trf_2388)
static void C_fcall trf_2388(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2388(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2388(t0,t1);}

C_noret_decl(trf_2033)
static void C_fcall trf_2033(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2033(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_2033(t0,t1,t2);}

C_noret_decl(trf_1977)
static void C_fcall trf_1977(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1977(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1977(t0,t1,t2);}

C_noret_decl(trf_1897)
static void C_fcall trf_1897(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1897(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1897(t0,t1);}

C_noret_decl(trf_1823)
static void C_fcall trf_1823(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1823(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1823(t0,t1);}

C_noret_decl(trf_1818)
static void C_fcall trf_1818(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1818(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1818(t0,t1,t2);}

C_noret_decl(trf_1706)
static void C_fcall trf_1706(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1706(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_1706(t0,t1,t2,t3);}

C_noret_decl(trf_1777)
static void C_fcall trf_1777(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1777(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1777(t0,t1,t2);}

C_noret_decl(trf_1736)
static void C_fcall trf_1736(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1736(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1736(t0,t1);}

C_noret_decl(trf_1708)
static void C_fcall trf_1708(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1708(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1708(t0,t1);}

C_noret_decl(trf_1682)
static void C_fcall trf_1682(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1682(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1682(t0,t1);}

C_noret_decl(trf_1638)
static void C_fcall trf_1638(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1638(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_1638(t0,t1,t2,t3);}

C_noret_decl(trf_1629)
static void C_fcall trf_1629(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1629(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1629(t0,t1);}

C_noret_decl(trf_1251)
static void C_fcall trf_1251(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1251(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1251(t0,t1);}

C_noret_decl(trf_1153)
static void C_fcall trf_1153(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1153(void *dummy){
C_word t5=C_pick(0);
C_word t4=C_pick(1);
C_word t3=C_pick(2);
C_word t2=C_pick(3);
C_word t1=C_pick(4);
C_word t0=C_pick(5);
C_adjust_stack(-6);
f_1153(t0,t1,t2,t3,t4,t5);}

C_noret_decl(trf_1058)
static void C_fcall trf_1058(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1058(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1058(t0,t1,t2);}

C_noret_decl(trf_961)
static void C_fcall trf_961(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_961(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_961(t0,t1);}

C_noret_decl(trf_956)
static void C_fcall trf_956(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_956(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_956(t0,t1,t2);}

C_noret_decl(trf_951)
static void C_fcall trf_951(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_951(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_951(t0,t1,t2,t3);}

C_noret_decl(trf_819)
static void C_fcall trf_819(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_819(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_819(t0,t1);}

C_noret_decl(trf_809)
static void C_fcall trf_809(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_809(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_809(t0,t1);}

C_noret_decl(trf_798)
static void C_fcall trf_798(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_798(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_798(t0,t1,t2);}

C_noret_decl(trf_791)
static void C_fcall trf_791(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_791(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_791(t0,t1);}

C_noret_decl(trf_780)
static void C_fcall trf_780(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_780(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_780(t0,t1,t2);}

C_noret_decl(trf_742)
static void C_fcall trf_742(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_742(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_742(t0,t1);}

C_noret_decl(trf_735)
static void C_fcall trf_735(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_735(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_735(t0,t1);}

C_noret_decl(trf_660)
static void C_fcall trf_660(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_660(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_660(t0,t1,t2);}

C_noret_decl(trf_626)
static void C_fcall trf_626(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_626(void *dummy){
C_word t6=C_pick(0);
C_word t5=C_pick(1);
C_word t4=C_pick(2);
C_word t3=C_pick(3);
C_word t2=C_pick(4);
C_word t1=C_pick(5);
C_word t0=C_pick(6);
C_adjust_stack(-7);
f_626(t0,t1,t2,t3,t4,t5,t6);}

C_noret_decl(trf_599)
static void C_fcall trf_599(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_599(void *dummy){
C_word t6=C_pick(0);
C_word t5=C_pick(1);
C_word t4=C_pick(2);
C_word t3=C_pick(3);
C_word t2=C_pick(4);
C_word t1=C_pick(5);
C_word t0=C_pick(6);
C_adjust_stack(-7);
f_599(t0,t1,t2,t3,t4,t5,t6);}

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

C_noret_decl(tr6r)
static void C_fcall tr6r(C_proc6 k) C_regparm C_noret;
C_regparm static void C_fcall tr6r(C_proc6 k){
int n;
C_word *a,t6;
C_word t5=C_pick(0);
C_word t4=C_pick(1);
C_word t3=C_pick(2);
C_word t2=C_pick(3);
C_word t1=C_pick(4);
C_word t0=C_pick(5);
C_adjust_stack(-6);
n=C_rest_count(0);
a=C_alloc(n*3);
t6=C_restore_rest(a,n);
(k)(t0,t1,t2,t3,t4,t5,t6);}

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
if(!C_demand_2(1556)){
C_save(t1);
C_rereclaim2(1556*sizeof(C_word), 1);
t1=C_restore;}
a=C_alloc(3);
C_initialize_lf(lf,263);
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
lf[26]=C_h_intern(&lf[26],6,"lookup");
lf[27]=C_static_lambda_info(C_heaptop,43,"(lookup x163 x1164 x2165 list166 . args167)");
lf[28]=C_h_intern(&lf[28],3,"int");
lf[29]=C_static_lambda_info(C_heaptop,10,"(int f168)");
lf[30]=C_h_intern(&lf[30],8,"quantize");
lf[31]=C_static_lambda_info(C_heaptop,26,"(quantize num169 steps170)");
lf[32]=C_h_intern(&lf[32],8,"decimals");
lf[33]=C_static_lambda_info(C_heaptop,29,"(decimals num171 . digits172)");
lf[34]=C_h_intern(&lf[34],15,"rhythm->seconds");
lf[35]=C_static_lambda_info(C_heaptop,26,"(body177 tempo183 beat184)");
lf[36]=C_flonum(C_heaptop,0.25);
lf[37]=C_static_lambda_info(C_heaptop,26,"(def-beat180 %tempo175186)");
lf[38]=C_flonum(C_heaptop,60.0);
lf[39]=C_static_lambda_info(C_heaptop,14,"(def-tempo179)");
lf[40]=C_h_intern(&lf[40],9,"\003syserror");
lf[41]=C_static_lambda_info(C_heaptop,36,"(rhythm->seconds beats173 . args174)");
lf[42]=C_h_intern(&lf[42],13,"cents->scaler");
lf[43]=C_static_lambda_info(C_heaptop,24,"(cents->scaler cents193)");
lf[44]=C_h_intern(&lf[44],13,"scaler->cents");
lf[45]=C_static_lambda_info(C_heaptop,22,"(scaler->cents num194)");
lf[46]=C_h_intern(&lf[46],13,"keynum->hertz");
lf[47]=C_static_lambda_info(C_heaptop,20,"(keynum->hertz k195)");
lf[48]=C_h_intern(&lf[48],10,"keynum->pc");
lf[49]=C_static_lambda_info(C_heaptop,17,"(keynum->pc k196)");
lf[50]=C_h_intern(&lf[50],13,"hertz->keynum");
lf[51]=C_static_lambda_info(C_heaptop,21,"(hertz->keynum hz197)");
lf[52]=C_h_intern(&lf[52],7,"interpl");
lf[53]=C_h_intern(&lf[53],5,"error");
lf[54]=C_static_string(C_heaptop,27,"not an x y coordinate list:");
lf[55]=C_static_lambda_info(C_heaptop,15,"(do206 tail208)");
lf[56]=C_h_intern(&lf[56],3,"err");
lf[57]=C_static_string(C_heaptop,27,"not an x y coordinate list:");
lf[58]=C_static_string(C_heaptop,27,"not an x y coordinate list:");
lf[59]=C_static_lambda_info(C_heaptop,34,"(interpl x198 coords199 . base200)");
lf[60]=C_h_intern(&lf[60],6,"interp");
lf[61]=C_static_lambda_info(C_heaptop,23,"(interp x216 . args217)");
lf[62]=C_h_intern(&lf[62],5,"steps");
lf[63]=C_h_intern(&lf[63],6,"modulo");
lf[64]=C_static_lambda_info(C_heaptop,27,"(do222 i224 k225 l226 t227)");
lf[65]=C_static_lambda_info(C_heaptop,34,"(steps len218 keynum219 . args220)");
lf[66]=C_h_intern(&lf[66],8,"ran-set!");
lf[67]=C_static_lambda_info(C_heaptop,18,"(ran-set! seed232)");
lf[68]=C_h_intern(&lf[68],3,"ran");
lf[69]=C_flonum(C_heaptop,1.0);
lf[70]=C_static_lambda_info(C_heaptop,15,"(ran . args233)");
lf[71]=C_h_intern(&lf[71],4,"odds");
lf[72]=C_flonum(C_heaptop,1.0);
lf[73]=C_flonum(C_heaptop,1.0);
lf[74]=C_flonum(C_heaptop,1.0);
lf[75]=C_static_lambda_info(C_heaptop,21,"(odds n234 . args235)");
lf[76]=C_h_intern(&lf[76],5,"pickl");
lf[77]=C_static_string(C_heaptop,29,"cannot pick from empty list: ");
lf[78]=C_static_lambda_info(C_heaptop,15,"(pickl args236)");
lf[79]=C_h_intern(&lf[79],4,"pick");
lf[80]=C_static_lambda_info(C_heaptop,16,"(pick . args237)");
lf[81]=C_h_intern(&lf[81],6,"ranlow");
lf[82]=C_static_lambda_info(C_heaptop,8,"(ranlow)");
lf[83]=C_h_intern(&lf[83],7,"ranhigh");
lf[84]=C_static_lambda_info(C_heaptop,9,"(ranhigh)");
lf[85]=C_h_intern(&lf[85],9,"ranmiddle");
lf[86]=C_static_lambda_info(C_heaptop,11,"(ranmiddle)");
lf[87]=C_h_intern(&lf[87],7,"ranbeta");
lf[88]=C_flonum(C_heaptop,0.5);
lf[89]=C_flonum(C_heaptop,0.5);
lf[90]=C_static_lambda_info(C_heaptop,19,"(ranbeta . args238)");
lf[91]=C_h_intern(&lf[91],6,"ranexp");
lf[92]=C_static_lambda_info(C_heaptop,18,"(ranexp . args239)");
lf[93]=C_h_intern(&lf[93],8,"rangauss");
lf[94]=C_static_lambda_info(C_heaptop,20,"(rangauss . args240)");
lf[95]=C_h_intern(&lf[95],9,"rancauchy");
lf[96]=C_static_lambda_info(C_heaptop,11,"(rancauchy)");
lf[97]=C_h_intern(&lf[97],10,"ranpoisson");
lf[98]=C_h_intern(&lf[98],3,"arg");
lf[99]=C_static_lambda_info(C_heaptop,22,"(ranpoisson . args241)");
lf[100]=C_h_intern(&lf[100],8,"rangamma");
lf[101]=C_static_lambda_info(C_heaptop,20,"(rangamma . args242)");
lf[102]=C_h_intern(&lf[102],8,"ranbrown");
lf[103]=C_static_lambda_info(C_heaptop,10,"(ranbrown)");
lf[104]=C_h_intern(&lf[104],7,"ranpink");
lf[105]=C_static_lambda_info(C_heaptop,9,"(ranpink)");
lf[106]=C_h_intern(&lf[106],13,"print-message");
lf[107]=C_h_intern(&lf[107],17,"\003sysmake-c-string");
lf[108]=C_static_lambda_info(C_heaptop,23,"(print-message a300304)");
lf[109]=C_h_intern(&lf[109],11,"print-error");
lf[110]=C_static_lambda_info(C_heaptop,21,"(print-error a306310)");
lf[111]=C_h_intern(&lf[111],25,"current-time-milliseconds");
lf[112]=C_static_lambda_info(C_heaptop,27,"(current-time-milliseconds)");
lf[113]=C_h_intern(&lf[113],20,"current-time-seconds");
lf[114]=C_static_lambda_info(C_heaptop,22,"(current-time-seconds)");
lf[116]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[117]=C_h_intern(&lf[117],6,"\003sysgc");
lf[118]=C_static_lambda_info(C_heaptop,41,"(scheduler-set-time-milliseconds a336339)");
lf[120]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[121]=C_static_lambda_info(C_heaptop,42,"(scheduler-sprout a344347 a343348 a342349)");
lf[123]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[124]=C_static_lambda_info(C_heaptop,24,"(scheduler-stop a364367)");
lf[125]=C_h_intern(&lf[125],6,"sprout");
lf[126]=C_static_lambda_info(C_heaptop,11,"(nextstart)");
lf[127]=C_static_lambda_info(C_heaptop,8,"(nextid)");
lf[128]=C_static_lambda_info(C_heaptop,12,"(do392 p394)");
lf[129]=C_static_lambda_info(C_heaptop,24,"(body378 start384 id385)");
lf[130]=C_static_lambda_info(C_heaptop,24,"(def-id381 %start376400)");
lf[131]=C_static_lambda_info(C_heaptop,14,"(def-start380)");
lf[132]=C_static_lambda_info(C_heaptop,26,"(sprout proc374 . args375)");
lf[133]=C_h_intern(&lf[133],3,"now");
lf[134]=C_h_intern(&lf[134],11,"time-format");
lf[135]=C_flonum(C_heaptop,1.0);
lf[136]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[137]=C_flonum(C_heaptop,1.0);
lf[138]=C_h_intern(&lf[138],1,"m");
lf[139]=C_static_string(C_heaptop,17,"not a time-format");
lf[140]=C_h_intern(&lf[140],1,"s");
lf[141]=C_static_lambda_info(C_heaptop,22,"(time-format . arg406)");
lf[142]=C_h_intern(&lf[142],5,"pause");
lf[143]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[144]=C_static_lambda_info(C_heaptop,7,"(pause)");
lf[145]=C_h_intern(&lf[145],7,"paused\077");
lf[146]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[147]=C_static_lambda_info(C_heaptop,9,"(paused\077)");
lf[148]=C_h_intern(&lf[148],4,"cont");
lf[149]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[150]=C_static_lambda_info(C_heaptop,6,"(cont)");
lf[151]=C_h_intern(&lf[151],4,"stop");
lf[152]=C_static_string(C_heaptop,17,"Not an integer id");
lf[153]=C_static_lambda_info(C_heaptop,15,"(do420 tail422)");
lf[154]=C_static_lambda_info(C_heaptop,18,"(stop . procid419)");
lf[155]=C_h_intern(&lf[155],4,"hush");
lf[156]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[157]=C_static_lambda_info(C_heaptop,6,"(hush)");
lf[160]=C_h_intern(&lf[160],7,"sprintf");
lf[161]=C_static_lambda_info(C_heaptop,23,"(ferror str433 args434)");
lf[162]=C_h_intern(&lf[162],7,"mp:note");
lf[163]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[164]=C_static_lambda_info(C_heaptop,46,"(mp:note time471 dur472 key473 amp474 chan475)");
lf[165]=C_h_intern(&lf[165],5,"mp:on");
lf[166]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[167]=C_static_lambda_info(C_heaptop,37,"(mp:on time476 key477 vel478 chan479)");
lf[168]=C_h_intern(&lf[168],6,"mp:off");
lf[169]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[170]=C_static_lambda_info(C_heaptop,38,"(mp:off time480 key481 vel482 chan483)");
lf[171]=C_h_intern(&lf[171],7,"mp:prog");
lf[172]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[173]=C_static_lambda_info(C_heaptop,33,"(mp:prog time484 prog485 chan486)");
lf[174]=C_h_intern(&lf[174],7,"mp:ctrl");
lf[175]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[176]=C_static_lambda_info(C_heaptop,40,"(mp:ctrl time487 ctrl488 val489 chan490)");
lf[177]=C_h_intern(&lf[177],9,"mp:alloff");
lf[178]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[179]=C_static_lambda_info(C_heaptop,11,"(mp:alloff)");
lf[180]=C_h_intern(&lf[180],8,"mp:micro");
lf[181]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[182]=C_static_lambda_info(C_heaptop,18,"(mp:micro divs491)");
lf[183]=C_h_intern(&lf[183],9,"mp:inhook");
lf[184]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[185]=C_static_lambda_info(C_heaptop,19,"(mp:inhook func492)");
lf[186]=C_h_intern(&lf[186],14,"return-to-host");
lf[187]=C_h_intern(&lf[187],4,"else");
lf[188]=C_h_intern(&lf[188],4,"cond");
lf[189]=C_h_intern(&lf[189],6,"lambda");
lf[190]=C_h_intern(&lf[190],7,"elapsed");
lf[191]=C_h_intern(&lf[191],1,"x");
lf[192]=C_h_intern(&lf[192],4,"set!");
lf[193]=C_h_intern(&lf[193],4,"wait");
lf[194]=C_h_intern(&lf[194],4,"let*");
lf[195]=C_h_intern(&lf[195],5,"quote");
lf[196]=C_h_intern(&lf[196],3,"exn");
lf[197]=C_h_intern(&lf[197],7,"message");
lf[198]=C_h_intern(&lf[198],27,"condition-property-accessor");
lf[199]=C_h_intern(&lf[199],6,"printf");
lf[200]=C_static_string(C_heaptop,47,">>> Aborting process at time ~S:~%    Error: ~S");
lf[201]=C_h_intern(&lf[201],22,"with-exception-handler");
lf[202]=C_h_intern(&lf[202],30,"call-with-current-continuation");
lf[203]=C_h_intern(&lf[203],10,"\003sysappend");
lf[204]=C_h_intern(&lf[204],6,"safety");
lf[205]=C_h_intern(&lf[205],4,"cdar");
lf[206]=C_static_string(C_heaptop,19,"unknown declaration");
lf[207]=C_h_intern(&lf[207],4,"caar");
lf[208]=C_static_string(C_heaptop,31,"declaration not list (decl val)");
lf[209]=C_static_lambda_info(C_heaptop,15,"(do518 decl520)");
lf[210]=C_h_intern(&lf[210],7,"declare");
lf[211]=C_h_intern(&lf[211],6,"gensym");
lf[212]=C_h_intern(&lf[212],6,"append");
lf[213]=C_h_intern(&lf[213],5,"\000null");
lf[214]=C_static_string(C_heaptop,41,"binding clause not list (var init [step])");
lf[215]=C_static_lambda_info(C_heaptop,15,"(do502 tail504)");
lf[216]=C_static_string(C_heaptop,36,"go stopping clause missing test form");
lf[217]=C_static_string(C_heaptop,29,"go stopping clause not a list");
lf[218]=C_static_string(C_heaptop,22,"go bindings not a list");
lf[219]=C_static_lambda_info(C_heaptop,42,"(a2801 bindings493 terminate494 . body495)");
lf[220]=C_h_intern(&lf[220],18,"\003sysregister-macro");
lf[221]=C_h_intern(&lf[221],2,"go");
lf[222]=C_h_intern(&lf[222],15,"hash-table-set!");
lf[223]=C_static_string(C_heaptop,9,"mp:inhook");
tmp=C_intern(C_heaptop,9,"mp:inhook");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000func");
C_save(tmp);
tmp=C_SCHEME_FALSE;
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[224]=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
lf[225]=C_static_string(C_heaptop,8,"mp:micro");
tmp=C_intern(C_heaptop,8,"mp:micro");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000divs");
C_save(tmp);
tmp=C_fix(1);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[226]=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
lf[227]=C_static_string(C_heaptop,9,"mp:alloff");
tmp=C_intern(C_heaptop,9,"mp:alloff");
C_save(tmp);
tmp=C_SCHEME_END_OF_LIST;
lf[228]=C_h_pair(C_restore,tmp);
lf[229]=C_static_string(C_heaptop,7,"mp:ctrl");
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
lf[230]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[231]=C_static_string(C_heaptop,7,"mp:prog");
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
lf[232]=C_h_list(4,C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(4);
lf[233]=C_static_string(C_heaptop,6,"mp:off");
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
lf[234]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[235]=C_static_string(C_heaptop,5,"mp:on");
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
lf[236]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[237]=C_static_string(C_heaptop,7,"mp:note");
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
lf[238]=C_h_list(6,C_pick(5),C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(6);
lf[239]=C_static_lambda_info(C_heaptop,15,"(do462 tail464)");
lf[240]=C_static_string(C_heaptop,37,"~S found duplicate keyword \047~S\047 in ~S");
lf[241]=C_static_string(C_heaptop,33,"~S missing value for keyword \047~S\047");
lf[242]=C_static_string(C_heaptop,53,"~S found invalid keyword \047~S\047~%Available keywords: ~S");
lf[243]=C_h_intern(&lf[243],7,"\003sysmap");
lf[244]=C_h_intern(&lf[244],3,"car");
lf[245]=C_static_string(C_heaptop,32,"~S expected keyword but got \047~S\047");
lf[246]=C_h_intern(&lf[246],8,"keyword\077");
lf[247]=C_static_string(C_heaptop,35,"~S expected ~A arguments but got ~A");
lf[248]=C_static_lambda_info(C_heaptop,28,"(do445 key447 arg448 pos449)");
lf[249]=C_static_string(C_heaptop,24,"~S is an invalid message");
lf[250]=C_static_lambda_info(C_heaptop,7,"(a2259)");
lf[251]=C_h_intern(&lf[251],14,"hash-table-ref");
lf[252]=C_h_intern(&lf[252],14,"symbol->string");
lf[253]=C_static_lambda_info(C_heaptop,25,"(a2807 mess469 . data470)");
lf[254]=C_h_intern(&lf[254],4,"send");
lf[255]=C_h_intern(&lf[255],10,"*messages*");
lf[256]=C_h_intern(&lf[256],14,"string->symbol");
lf[257]=C_static_string(C_heaptop,51,"message function not string, symbol or list of both");
lf[258]=C_static_lambda_info(C_heaptop,23,"(a2813 func427 info428)");
lf[259]=C_h_intern(&lf[259],19,"define-send-message");
lf[260]=C_h_intern(&lf[260],15,"make-hash-table");
lf[261]=C_h_intern(&lf[261],6,"equal\077");
lf[262]=C_static_lambda_info(C_heaptop,10,"(toplevel)");
C_register_lf2(lf,263,create_ptable());
t2=C_mutate(&lf[0],lf[1]);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_588,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_library_toplevel(2,C_SCHEME_UNDEFINED,t3);}

/* k586 */
static void C_ccall f_588(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_588,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_591,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_eval_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k589 in k586 */
static void C_ccall f_591(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_591,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_594,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k592 in k589 in k586 */
static void C_ccall f_594(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_594,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_597,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k595 in k592 in k589 in k586 */
static void C_ccall f_597(C_word c,C_word t0,C_word t1){
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
C_word t58;
C_word t59;
C_word ab[168],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_597,2,t0,t1);}
t2=C_mutate(&lf[2],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_599,a[2]=lf[3],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate(&lf[4],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_626,a[2]=lf[5],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate(&lf[6],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_660,a[2]=lf[7],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate(&lf[8],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_735,a[2]=lf[9],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate(&lf[10],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_742,a[2]=lf[11],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate(&lf[12],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_780,a[2]=lf[13],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate(&lf[14],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_791,a[2]=lf[15],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate(&lf[16],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_798,a[2]=lf[17],tmp=(C_word)a,a+=3,tmp));
t10=C_mutate(&lf[18],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_809,a[2]=lf[19],tmp=(C_word)a,a+=3,tmp));
t11=C_mutate(&lf[20],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_819,a[2]=lf[21],tmp=(C_word)a,a+=3,tmp));
t12=C_mutate((C_word*)lf[22]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_832,a[2]=lf[23],tmp=(C_word)a,a+=3,tmp));
t13=C_mutate((C_word*)lf[24]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_851,a[2]=lf[25],tmp=(C_word)a,a+=3,tmp));
t14=C_mutate((C_word*)lf[26]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_870,a[2]=lf[27],tmp=(C_word)a,a+=3,tmp));
t15=C_mutate((C_word*)lf[28]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_918,a[2]=lf[29],tmp=(C_word)a,a+=3,tmp));
t16=C_mutate((C_word*)lf[30]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_924,a[2]=lf[31],tmp=(C_word)a,a+=3,tmp));
t17=C_mutate((C_word*)lf[32]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_930,a[2]=lf[33],tmp=(C_word)a,a+=3,tmp));
t18=C_mutate((C_word*)lf[34]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_949,a[2]=lf[41],tmp=(C_word)a,a+=3,tmp));
t19=C_mutate((C_word*)lf[42]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1009,a[2]=lf[43],tmp=(C_word)a,a+=3,tmp));
t20=C_mutate((C_word*)lf[44]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1015,a[2]=lf[45],tmp=(C_word)a,a+=3,tmp));
t21=C_mutate((C_word*)lf[46]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1021,a[2]=lf[47],tmp=(C_word)a,a+=3,tmp));
t22=C_mutate((C_word*)lf[48]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1027,a[2]=lf[49],tmp=(C_word)a,a+=3,tmp));
t23=C_mutate((C_word*)lf[50]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1033,a[2]=lf[51],tmp=(C_word)a,a+=3,tmp));
t24=C_mutate((C_word*)lf[52]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1039,a[2]=lf[59],tmp=(C_word)a,a+=3,tmp));
t25=C_mutate((C_word*)lf[60]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1134,a[2]=lf[61],tmp=(C_word)a,a+=3,tmp));
t26=C_mutate((C_word*)lf[62]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1140,a[2]=lf[65],tmp=(C_word)a,a+=3,tmp));
t27=C_mutate((C_word*)lf[66]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1199,a[2]=lf[67],tmp=(C_word)a,a+=3,tmp));
t28=C_mutate((C_word*)lf[68]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1205,a[2]=lf[70],tmp=(C_word)a,a+=3,tmp));
t29=C_mutate((C_word*)lf[71]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1293,a[2]=lf[75],tmp=(C_word)a,a+=3,tmp));
t30=C_mutate((C_word*)lf[76]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1351,a[2]=lf[78],tmp=(C_word)a,a+=3,tmp));
t31=C_mutate((C_word*)lf[79]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1374,a[2]=lf[80],tmp=(C_word)a,a+=3,tmp));
t32=C_mutate((C_word*)lf[81]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1380,a[2]=lf[82],tmp=(C_word)a,a+=3,tmp));
t33=C_mutate((C_word*)lf[83]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1386,a[2]=lf[84],tmp=(C_word)a,a+=3,tmp));
t34=C_mutate((C_word*)lf[85]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1392,a[2]=lf[86],tmp=(C_word)a,a+=3,tmp));
t35=C_mutate((C_word*)lf[87]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1398,a[2]=lf[90],tmp=(C_word)a,a+=3,tmp));
t36=C_mutate((C_word*)lf[91]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1442,a[2]=lf[92],tmp=(C_word)a,a+=3,tmp));
t37=C_mutate((C_word*)lf[93]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1461,a[2]=lf[94],tmp=(C_word)a,a+=3,tmp));
t38=C_mutate((C_word*)lf[95]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1501,a[2]=lf[96],tmp=(C_word)a,a+=3,tmp));
t39=C_mutate((C_word*)lf[97]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1507,a[2]=lf[99],tmp=(C_word)a,a+=3,tmp));
t40=C_mutate((C_word*)lf[100]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1526,a[2]=lf[101],tmp=(C_word)a,a+=3,tmp));
t41=C_mutate((C_word*)lf[102]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1545,a[2]=lf[103],tmp=(C_word)a,a+=3,tmp));
t42=C_mutate((C_word*)lf[104]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1551,a[2]=lf[105],tmp=(C_word)a,a+=3,tmp));
t43=C_mutate((C_word*)lf[106]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1557,a[2]=lf[108],tmp=(C_word)a,a+=3,tmp));
t44=C_mutate((C_word*)lf[109]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1571,a[2]=lf[110],tmp=(C_word)a,a+=3,tmp));
t45=C_mutate((C_word*)lf[111]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1614,a[2]=lf[112],tmp=(C_word)a,a+=3,tmp));
t46=C_mutate((C_word*)lf[113]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1617,a[2]=lf[114],tmp=(C_word)a,a+=3,tmp));
t47=C_mutate(&lf[115],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1629,a[2]=lf[118],tmp=(C_word)a,a+=3,tmp));
t48=C_mutate(&lf[119],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1638,a[2]=lf[121],tmp=(C_word)a,a+=3,tmp));
t49=C_mutate(&lf[122],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1682,a[2]=lf[124],tmp=(C_word)a,a+=3,tmp));
t50=C_mutate((C_word*)lf[125]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1704,a[2]=lf[132],tmp=(C_word)a,a+=3,tmp));
t51=C_mutate((C_word*)lf[133]+1,*((C_word*)lf[113]+1));
t52=C_mutate((C_word*)lf[134]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1872,a[2]=lf[141],tmp=(C_word)a,a+=3,tmp));
t53=C_mutate((C_word*)lf[142]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1935,a[2]=lf[144],tmp=(C_word)a,a+=3,tmp));
t54=C_mutate((C_word*)lf[145]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1944,a[2]=lf[147],tmp=(C_word)a,a+=3,tmp));
t55=C_mutate((C_word*)lf[148]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1950,a[2]=lf[150],tmp=(C_word)a,a+=3,tmp));
t56=C_mutate((C_word*)lf[151]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1959,a[2]=lf[154],tmp=(C_word)a,a+=3,tmp));
t57=C_mutate((C_word*)lf[155]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2017,a[2]=lf[157],tmp=(C_word)a,a+=3,tmp));
t58=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2028,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 271  make-hash-table");
t59=C_retrieve(lf[260]);
((C_proc3)C_retrieve_proc(t59))(3,t59,t58,*((C_word*)lf[261]+1));}

/* k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2028(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2028,2,t0,t1);}
t2=C_mutate(&lf[158],t1);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2031,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2814,a[2]=lf[258],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 273  ##sys#register-macro");
t5=C_retrieve(lf[220]);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,lf[259],t4);}

/* a2813 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2814(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_2814,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_2818,a[2]=t6,a[3]=t1,a[4]=t3,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t4)[1]))){
t8=(C_word)C_i_car(((C_word*)t4)[1]);
t9=C_set_block_item(t6,0,t8);
t10=(C_word)C_i_cadr(((C_word*)t4)[1]);
t11=C_set_block_item(t4,0,t10);
t12=t7;
f_2818(2,t12,t11);}
else{
if(C_truep((C_word)C_i_stringp(((C_word*)t4)[1]))){
t8=C_set_block_item(t6,0,((C_word*)t4)[1]);
t9=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2851,a[2]=t7,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 280  string->symbol");
t10=*((C_word*)lf[256]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)t4)[1]);}
else{
if(C_truep((C_word)C_i_symbolp(((C_word*)t4)[1]))){
t8=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2861,a[2]=t7,a[3]=t6,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 282  symbol->string");
t9=*((C_word*)lf[252]+1);
((C_proc3)C_retrieve_proc(t9))(3,t9,t8,((C_word*)t4)[1]);}
else{
C_trace("ChickenBridge.scm: 284  error");
t8=*((C_word*)lf[53]+1);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,lf[257]);}}}}

/* k2859 in a2813 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2861(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_2818(2,t3,t2);}

/* k2849 in a2813 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2851(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_2818(2,t3,t2);}

/* k2816 in a2813 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2818(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2818,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[4]);
t3=(C_word)C_a_i_list(&a,2,lf[195],t2);
t4=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_a_i_list(&a,4,lf[222],lf[255],((C_word*)((C_word*)t0)[2])[1],t3));}

/* k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2031(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2031,2,t0,t1);}
t2=C_mutate(&lf[159],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2033,a[2]=lf[161],tmp=(C_word)a,a+=3,tmp));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2270,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2808,a[2]=lf[253],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 360  ##sys#register-macro");
t5=C_retrieve(lf[220]);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,lf[254],t4);}

/* a2807 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2808(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+6)){
C_save_and_reclaim((void*)tr3r,(void*)f_2808r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_2808r(t0,t1,t2,t3);}}

static void C_ccall f_2808r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a=C_alloc(6);
t4=t3;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2047,a[2]=t1,a[3]=t5,tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_symbolp(t2))){
C_trace("ChickenBridge.scm: 291  symbol->string");
t7=*((C_word*)lf[252]+1);
((C_proc3)C_retrieve_proc(t7))(3,t7,t6,t2);}
else{
t7=t6;
f_2047(2,t7,t2);}}

/* k2045 in a2807 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2047(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2047,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2050,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2260,a[2]=lf[250],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 292  hash-table-ref");
t4=*((C_word*)lf[251]+1);
((C_proc5)C_retrieve_proc(t4))(5,t4,t2,lf[158],t1,t3);}

/* a2259 in k2045 in a2807 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2260(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2260,2,t0,t1);}
t2=t1;
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}

/* k2048 in k2045 in a2807 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2050(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2050,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_2053,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=t1;
if(C_truep(t3)){
t4=t2;
f_2053(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 293  ferror");
f_2033(t2,lf[249],(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]));}}

/* k2051 in k2048 in k2045 in a2807 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2053(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2053,2,t0,t1);}
t2=((C_word*)((C_word*)t0)[5])[1];
t3=(C_word)C_i_car(((C_word*)t0)[4]);
t4=(C_word)C_i_cdr(((C_word*)t0)[4]);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(C_word)C_i_length(t4);
t8=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_2065,a[2]=t7,a[3]=t2,a[4]=((C_word*)t0)[2],a[5]=t6,a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[3],a[8]=t4,a[9]=t3,tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 300  append");
t9=*((C_word*)lf[212]+1);
((C_proc4)C_retrieve_proc(t9))(4,t9,t8,t4,C_SCHEME_END_OF_LIST);}

/* k2063 in k2051 in k2048 in k2045 in a2807 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2065(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[19],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2065,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_2068,a[2]=((C_word*)t0)[7],a[3]=((C_word*)t0)[8],a[4]=t1,a[5]=((C_word*)t0)[9],tmp=(C_word)a,a+=6,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_2113,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[5],a[8]=t4,a[9]=((C_word*)t0)[6],a[10]=lf[248],tmp=(C_word)a,a+=11,tmp));
t6=((C_word*)t4)[1];
f_2113(t6,t2,C_SCHEME_FALSE,C_SCHEME_FALSE,C_fix(0));}

/* do445 in k2063 in k2051 in k2048 in k2045 in a2807 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_fcall f_2113(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
C_save_and_reclaim((void*)trf_2113,NULL,5,t0,t1,t2,t3,t4);}
t5=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[9])[1]))){
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,C_SCHEME_FALSE);}
else{
t8=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_2123,a[2]=t7,a[3]=t6,a[4]=t5,a[5]=t1,a[6]=((C_word*)t0)[8],tmp=(C_word)a,a+=7,tmp);
t9=(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_2129,a[2]=((C_word*)t0)[2],a[3]=t7,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=t6,a[8]=((C_word*)t0)[6],a[9]=t5,a[10]=((C_word*)t0)[9],a[11]=t8,a[12]=((C_word*)t0)[7],tmp=(C_word)a,a+=13,tmp);
t10=((C_word*)((C_word*)t0)[7])[1];
if(C_truep(t10)){
t11=t9;
f_2129(2,t11,C_SCHEME_FALSE);}
else{
t11=(C_word)C_i_car(((C_word*)((C_word*)t0)[9])[1]);
C_trace("ChickenBridge.scm: 311  keyword?");
t12=C_retrieve(lf[246]);
((C_proc3)C_retrieve_proc(t12))(3,t12,t9,t11);}}}

/* k2127 in do445 in k2063 in k2051 in k2048 in k2045 in a2807 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2129(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2129,2,t0,t1);}
if(C_truep(t1)){
t2=C_set_block_item(((C_word*)t0)[12],0,C_SCHEME_TRUE);
t3=((C_word*)t0)[11];
f_2123(t3,t2);}
else{
t2=((C_word*)((C_word*)t0)[12])[1];
if(C_truep(t2)){
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[10])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[9])+1,t3);
t5=(C_word)C_i_assoc(((C_word*)((C_word*)t0)[9])[1],((C_word*)t0)[8]);
t6=C_mutate(((C_word *)((C_word*)t0)[7])+1,t5);
t7=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[10])[1]);
t8=C_mutate(((C_word *)((C_word*)t0)[10])+1,t7);
t9=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_2183,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[9],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[11],a[6]=((C_word*)t0)[10],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t10=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_2238,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[9],a[5]=((C_word*)t0)[5],a[6]=t9,a[7]=((C_word*)t0)[10],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 331  keyword?");
t11=C_retrieve(lf[246]);
((C_proc3)C_retrieve_proc(t11))(3,t11,t10,((C_word*)((C_word*)t0)[9])[1]);}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_2139,a[2]=((C_word*)t0)[11],a[3]=((C_word*)t0)[10],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[6],tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_nequalp(((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]))){
t4=(C_word)C_i_length(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 321  ferror");
f_2033(t3,lf[247],(C_word)C_a_i_list(&a,3,((C_word*)t0)[5],((C_word*)t0)[2],t4));}
else{
t4=t3;
f_2139(2,t4,C_SCHEME_UNDEFINED);}}}}

/* k2137 in k2127 in do445 in k2063 in k2051 in k2048 in k2045 in a2807 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2139(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2139,2,t0,t1);}
t2=(C_word)C_i_list_tail(((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]);
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
t4=(C_word)C_i_set_car(t2,t3);
t5=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[3])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t5);
t7=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[4])[1],C_fix(1));
t8=C_mutate(((C_word *)((C_word*)t0)[4])+1,t7);
t9=((C_word*)t0)[2];
f_2123(t9,t8);}

/* k2236 in k2127 in do445 in k2063 in k2051 in k2048 in k2045 in a2807 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2238(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2238,2,t0,t1);}
if(C_truep(t1)){
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[7])[1]))){
C_trace("ChickenBridge.scm: 335  ferror");
f_2033(((C_word*)t0)[6],lf[241],(C_word)C_a_i_list(&a,2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]));}
else{
t2=((C_word*)((C_word*)t0)[3])[1];
if(C_truep(t2)){
t3=((C_word*)t0)[6];
f_2183(2,t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2234,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
C_trace("map");
t4=*((C_word*)lf[243]+1);
((C_proc4)(void*)(*((C_word*)t4+1)))(4,t4,t3,*((C_word*)lf[244]+1),((C_word*)t0)[2]);}}}
else{
C_trace("ChickenBridge.scm: 332  ferror");
f_2033(((C_word*)t0)[6],lf[245],(C_word)C_a_i_list(&a,2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]));}}

/* k2232 in k2236 in k2127 in do445 in k2063 in k2051 in k2048 in k2045 in a2807 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2234(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2234,2,t0,t1);}
C_trace("ChickenBridge.scm: 338  ferror");
f_2033(((C_word*)t0)[4],lf[242],(C_word)C_a_i_list(&a,3,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1));}

/* k2181 in k2127 in do445 in k2063 in k2051 in k2048 in k2045 in a2807 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2183(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[14],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2183,2,t0,t1);}
t2=(C_word)C_i_member(((C_word*)((C_word*)t0)[8])[1],((C_word*)t0)[7]);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2189,a[2]=((C_word*)t0)[5],a[3]=t2,a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
if(C_truep(t2)){
t4=t3;
f_2189(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 345  ferror");
f_2033(t3,lf[240],(C_word)C_a_i_list(&a,3,((C_word*)t0)[4],((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]));}}

/* k2187 in k2181 in k2127 in do445 in k2063 in k2051 in k2048 in k2045 in a2807 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2189(C_word c,C_word t0,C_word t1){
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
f_2123(t6,t5);}

/* k2121 in do445 in k2063 in k2051 in k2048 in k2045 in a2807 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_fcall f_2123(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[6])[1];
f_2113(t2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k2066 in k2063 in k2051 in k2048 in k2045 in a2807 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2068(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2068,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_2073,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=lf[239],tmp=(C_word)a,a+=7,tmp));
t5=((C_word*)t3)[1];
f_2073(t5,((C_word*)t0)[2],((C_word*)t0)[4]);}

/* do462 in k2066 in k2063 in k2051 in k2048 in k2045 in a2807 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_fcall f_2073(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2073,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[5],((C_word*)t0)[4]));}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2086,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_member(t4,((C_word*)t0)[2]))){
t5=(C_word)C_i_car(t2);
t6=(C_word)C_i_cadr(t5);
t7=t3;
f_2086(t7,(C_word)C_i_set_car(t2,t6));}
else{
t5=t3;
f_2086(t5,C_SCHEME_UNDEFINED);}}}

/* k2084 in do462 in k2066 in k2063 in k2051 in k2048 in k2045 in a2807 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_fcall f_2086(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_2073(t3,((C_word*)t0)[2],t2);}

/* k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2270(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2270,2,t0,t1);}
t2=C_mutate((C_word*)lf[162]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2272,a[2]=lf[164],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[165]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2278,a[2]=lf[167],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate((C_word*)lf[168]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2284,a[2]=lf[170],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate((C_word*)lf[171]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2290,a[2]=lf[173],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[174]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2296,a[2]=lf[176],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate((C_word*)lf[177]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2302,a[2]=lf[179],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate((C_word*)lf[180]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2308,a[2]=lf[182],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate((C_word*)lf[183]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2314,a[2]=lf[185],tmp=(C_word)a,a+=3,tmp));
t10=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2321,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 387  hash-table-set!");
t11=C_retrieve(lf[222]);
((C_proc5)C_retrieve_proc(t11))(5,t11,t10,lf[158],lf[237],lf[238]);}

/* k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2321(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2321,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2324,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 388  hash-table-set!");
t3=C_retrieve(lf[222]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[158],lf[235],lf[236]);}

/* k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2324(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2324,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2327,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 389  hash-table-set!");
t3=C_retrieve(lf[222]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[158],lf[233],lf[234]);}

/* k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2327(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2327,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2330,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 390  hash-table-set!");
t3=C_retrieve(lf[222]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[158],lf[231],lf[232]);}

/* k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2330(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2330,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2333,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 391  hash-table-set!");
t3=C_retrieve(lf[222]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[158],lf[229],lf[230]);}

/* k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2333(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2333,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2336,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 392  hash-table-set!");
t3=C_retrieve(lf[222]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[158],lf[227],lf[228]);}

/* k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2336(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2336,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2339,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 393  hash-table-set!");
t3=C_retrieve(lf[222]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[158],lf[225],lf[226]);}

/* k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2339(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2339,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2342,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 394  hash-table-set!");
t3=C_retrieve(lf[222]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[158],lf[223],lf[224]);}

/* k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2342(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2342,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2345,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2802,a[2]=lf[219],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 401  ##sys#register-macro");
t4=C_retrieve(lf[220]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,lf[221],t3);}

/* a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2802(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+17)){
C_save_and_reclaim((void*)tr4r,(void*)f_2802r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest(a,C_rest_count(0));
f_2802r(t0,t1,t2,t3,t4);}}

static void C_ccall f_2802r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
t13=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_2360,a[2]=t2,a[3]=t12,a[4]=t6,a[5]=t10,a[6]=t1,a[7]=t8,a[8]=t3,tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(t2))){
t14=t13;
f_2360(2,t14,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 410  error");
t14=*((C_word*)lf[53]+1);
((C_proc4)C_retrieve_proc(t14))(4,t14,t13,lf[218],t2);}}

/* k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2360(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2360,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_2363,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(((C_word*)t0)[8]))){
if(C_truep((C_word)C_i_nullp(((C_word*)t0)[8]))){
C_trace("ChickenBridge.scm: 414  error");
t3=*((C_word*)lf[53]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,lf[216]);}
else{
t3=t2;
f_2363(2,t3,C_SCHEME_UNDEFINED);}}
else{
C_trace("ChickenBridge.scm: 412  error");
t3=*((C_word*)lf[53]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t2,lf[217],((C_word*)t0)[8]);}}

/* k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2363(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2363,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_2366,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],tmp=(C_word)a,a+=8,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_2637,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[7],a[5]=t4,a[6]=lf[215],tmp=(C_word)a,a+=7,tmp));
t6=((C_word*)t4)[1];
f_2637(t6,t2,((C_word*)t0)[2]);}

/* do502 in k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_fcall f_2637(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_2637,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2647,a[2]=t1,a[3]=((C_word*)t0)[5],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_2657,a[2]=t3,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=t2,tmp=(C_word)a,a+=7,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2745,a[2]=t4,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t7=(C_word)C_i_car(t2);
t8=(C_word)C_i_length(t7);
C_trace("ChickenBridge.scm: 418  <");
C_lessp(5,0,t6,C_fix(0),t8,C_fix(4));}
else{
t6=t4;
f_2657(t6,C_SCHEME_FALSE);}}}

/* k2743 in do502 in k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2745(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=(C_word)C_i_car(t2);
t4=((C_word*)t0)[2];
f_2657(t4,(C_word)C_i_symbolp(t3));}
else{
t2=((C_word*)t0)[2];
f_2657(t2,C_SCHEME_FALSE);}}

/* k2655 in do502 in k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_fcall f_2657(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_2657,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[6]);
t3=(C_word)C_i_car(t2);
t4=(C_word)C_i_car(((C_word*)t0)[6]);
t5=(C_word)C_i_cadr(t4);
t6=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_2666,a[2]=t5,a[3]=t3,a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[5],tmp=(C_word)a,a+=8,tmp);
t7=(C_word)C_i_car(((C_word*)t0)[6]);
t8=(C_word)C_i_cddr(t7);
if(C_truep((C_word)C_i_nullp(t8))){
t9=t6;
f_2666(t9,lf[213]);}
else{
t9=(C_word)C_i_car(((C_word*)t0)[6]);
t10=t6;
f_2666(t10,(C_word)C_i_caddr(t9));}}
else{
t2=(C_word)C_i_car(((C_word*)t0)[6]);
C_trace("ChickenBridge.scm: 431  error");
t3=*((C_word*)lf[53]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[2],lf[214],t2);}}

/* k2664 in k2655 in do502 in k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_fcall f_2666(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2666,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_2670,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t3=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 426  append");
t4=*((C_word*)lf[212]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,((C_word*)((C_word*)t0)[7])[1],t3);}

/* k2668 in k2664 in k2655 in do502 in k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2670(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2670,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_2674,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
t4=(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 427  append");
t5=*((C_word*)lf[212]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,((C_word*)((C_word*)t0)[7])[1],t4);}

/* k2672 in k2668 in k2664 in k2655 in do502 in k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2674(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2674,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2678,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2682,a[2]=((C_word*)t0)[5],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_eqp(((C_word*)t0)[3],lf[213]);
if(C_truep(t5)){
t6=t4;
f_2682(t6,C_SCHEME_END_OF_LIST);}
else{
t6=(C_word)C_a_i_list(&a,3,lf[192],((C_word*)t0)[2],((C_word*)t0)[3]);
t7=t4;
f_2682(t7,(C_word)C_a_i_list(&a,1,t6));}}

/* k2680 in k2672 in k2668 in k2664 in k2655 in do502 in k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_fcall f_2682(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 428  append");
t2=*((C_word*)lf[212]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k2676 in k2672 in k2668 in k2664 in k2655 in do502 in k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2678(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_2647(2,t3,t2);}

/* k2645 in do502 in k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2647(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_2637(t3,((C_word*)t0)[2],t2);}

/* k2364 in k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2366(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2366,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_2369,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 433  gensym");
t3=C_retrieve(lf[211]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k2367 in k2364 in k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2369(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2369,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_2372,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 434  gensym");
t3=C_retrieve(lf[211]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k2370 in k2367 in k2364 in k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2372(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2372,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_2375,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 435  gensym");
t3=C_retrieve(lf[211]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k2373 in k2370 in k2367 in k2364 in k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2375(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2375,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_2378,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],a[10]=((C_word*)t0)[9],tmp=(C_word)a,a+=11,tmp);
C_trace("ChickenBridge.scm: 436  gensym");
t3=C_retrieve(lf[211]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k2376 in k2373 in k2370 in k2367 in k2364 in k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2378(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2378,2,t0,t1);}
t2=C_SCHEME_TRUE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_SCHEME_END_OF_LIST;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_2381,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=t3,a[7]=((C_word*)t0)[5],a[8]=((C_word*)t0)[6],a[9]=((C_word*)t0)[7],a[10]=((C_word*)t0)[8],a[11]=((C_word*)t0)[9],a[12]=t5,a[13]=((C_word*)t0)[10],tmp=(C_word)a,a+=14,tmp);
t7=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2530,a[2]=t6,a[3]=t3,a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)((C_word*)t0)[3])[1]))){
t8=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
if(C_truep((C_word)C_i_pairp(t8))){
t9=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2631,a[2]=t7,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 442  caar");
t10=*((C_word*)lf[207]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)((C_word*)t0)[3])[1]);}
else{
t9=t7;
f_2530(t9,C_SCHEME_FALSE);}}
else{
t8=t7;
f_2530(t8,C_SCHEME_FALSE);}}

/* k2629 in k2376 in k2373 in k2370 in k2367 in k2364 in k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2631(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_2530(t2,(C_word)C_eqp(t1,lf[210]));}

/* k2528 in k2376 in k2373 in k2370 in k2367 in k2364 in k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_fcall f_2530(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2530,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2537,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 443  cdar");
t3=*((C_word*)lf[205]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)((C_word*)t0)[4])[1]);}
else{
t2=((C_word*)t0)[2];
f_2381(2,t2,C_SCHEME_UNDEFINED);}}

/* k2535 in k2528 in k2376 in k2373 in k2370 in k2367 in k2364 in k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2537(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2537,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_2539,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=lf[209],tmp=(C_word)a,a+=6,tmp));
t5=((C_word*)t3)[1];
f_2539(t5,((C_word*)t0)[2],t1);}

/* do518 in k2535 in k2528 in k2376 in k2373 in k2370 in k2367 in k2364 in k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_fcall f_2539(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_2539,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[4])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[4])+1,t3);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,t4);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2553,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2563,a[2]=t2,a[3]=((C_word*)t0)[2],a[4]=t3,tmp=(C_word)a,a+=5,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2611,a[2]=t4,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 447  cdar");
t7=*((C_word*)lf[205]+1);
((C_proc3)C_retrieve_proc(t7))(3,t7,t6,t2);}
else{
t6=t4;
f_2563(t6,C_SCHEME_FALSE);}}}

/* k2609 in do518 in k2535 in k2528 in k2376 in k2373 in k2370 in k2367 in k2364 in k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2611(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_2563(t2,(C_word)C_i_pairp(t1));}

/* k2561 in do518 in k2535 in k2528 in k2376 in k2373 in k2370 in k2367 in k2364 in k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_fcall f_2563(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2563,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2566,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 448  caar");
t3=*((C_word*)lf[207]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)t0)[2]);}
else{
t2=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 454  error");
t3=*((C_word*)lf[53]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[4],lf[208],t2);}}

/* k2564 in k2561 in do518 in k2535 in k2528 in k2376 in k2373 in k2370 in k2367 in k2364 in k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2566(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2566,2,t0,t1);}
t2=(C_word)C_eqp(t1,lf[204]);
if(C_truep(t2)){
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2587,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 450  cdar");
t4=*((C_word*)lf[205]+1);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)t0)[2]);}
else{
t3=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 453  error");
t4=*((C_word*)lf[53]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,((C_word*)t0)[4],lf[206],t3);}}

/* k2585 in k2564 in k2561 in do518 in k2535 in k2528 in k2376 in k2373 in k2370 in k2367 in k2364 in k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2587(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep((C_word)C_i_car(t1))){
t2=((C_word*)t0)[3];
f_2553(2,t2,C_SCHEME_UNDEFINED);}
else{
t2=C_set_block_item(((C_word*)t0)[2],0,C_SCHEME_FALSE);
t3=((C_word*)t0)[3];
f_2553(2,t3,t2);}}

/* k2551 in do518 in k2535 in k2528 in k2376 in k2373 in k2370 in k2367 in k2364 in k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2553(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_2539(t3,((C_word*)t0)[2],t2);}

/* k2379 in k2376 in k2373 in k2370 in k2367 in k2364 in k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2381(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2381,2,t0,t1);}
t2=(C_word)C_i_car(((C_word*)t0)[13]);
t3=(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_2519,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],a[10]=((C_word*)t0)[10],a[11]=((C_word*)t0)[11],a[12]=((C_word*)t0)[12],a[13]=t2,tmp=(C_word)a,a+=14,tmp);
t4=(C_word)C_i_cdr(((C_word*)t0)[13]);
t5=(C_word)C_a_i_list(&a,1,C_fix(-1));
C_trace("ChickenBridge.scm: 405  ##sys#append");
t6=*((C_word*)lf[203]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t3,t4,t5);}

/* k2517 in k2379 in k2376 in k2373 in k2370 in k2367 in k2364 in k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2519(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2519,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[13],t1);
t3=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_2503,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],a[8]=((C_word*)t0)[10],a[9]=((C_word*)t0)[11],a[10]=((C_word*)t0)[12],a[11]=t2,tmp=(C_word)a,a+=12,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2507,a[2]=((C_word*)t0)[3],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_a_i_list(&a,1,((C_word*)t0)[10]);
C_trace("ChickenBridge.scm: 405  ##sys#append");
t6=*((C_word*)lf[203]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t4,((C_word*)((C_word*)t0)[2])[1],t5);}

/* k2505 in k2517 in k2379 in k2376 in k2373 in k2370 in k2367 in k2364 in k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2507(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 405  ##sys#append");
t2=*((C_word*)lf[203]+1);
((C_proc4)(void*)(*((C_word*)t2+1)))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k2501 in k2517 in k2379 in k2376 in k2373 in k2370 in k2367 in k2364 in k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2503(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2503,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,lf[187],t1);
t3=(C_word)C_a_i_list(&a,3,lf[188],((C_word*)t0)[11],t2);
t4=C_mutate(((C_word *)((C_word*)t0)[10])+1,t3);
t5=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_2388,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],a[5]=((C_word*)t0)[10],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],tmp=(C_word)a,a+=8,tmp);
if(C_truep(((C_word*)((C_word*)t0)[4])[1])){
t6=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
t7=(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]);
t8=(C_word)C_a_i_list(&a,2,lf[195],lf[196]);
t9=(C_word)C_a_i_list(&a,2,lf[195],lf[197]);
t10=(C_word)C_a_i_list(&a,3,lf[198],t8,t9);
t11=(C_word)C_a_i_list(&a,2,t10,((C_word*)t0)[2]);
t12=(C_word)C_a_i_list(&a,4,lf[199],lf[200],((C_word*)t0)[9],t11);
t13=(C_word)C_a_i_list(&a,2,((C_word*)t0)[3],C_fix(-2));
t14=(C_word)C_a_i_list(&a,4,lf[189],t7,t12,t13);
t15=(C_word)C_a_i_list(&a,3,lf[189],C_SCHEME_END_OF_LIST,((C_word*)((C_word*)t0)[10])[1]);
t16=(C_word)C_a_i_list(&a,3,lf[201],t14,t15);
t17=(C_word)C_a_i_list(&a,3,lf[189],t6,t16);
t18=(C_word)C_a_i_list(&a,2,lf[202],t17);
t19=C_mutate(((C_word *)((C_word*)t0)[10])+1,t18);
t20=t5;
f_2388(t20,t19);}
else{
t6=t5;
f_2388(t6,C_SCHEME_UNDEFINED);}}

/* k2386 in k2501 in k2517 in k2379 in k2376 in k2373 in k2370 in k2367 in k2364 in k2361 in k2358 in a2801 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_fcall f_2388(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_2388,NULL,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,((C_word*)t0)[7]);
t3=(C_word)C_a_i_list(&a,2,((C_word*)t0)[6],C_fix(0));
t4=(C_word)C_a_i_list(&a,3,lf[189],C_SCHEME_END_OF_LIST,((C_word*)t0)[7]);
t5=(C_word)C_a_i_list(&a,2,lf[190],t4);
t6=(C_word)C_a_i_list(&a,1,lf[191]);
t7=(C_word)C_a_i_list(&a,3,lf[192],((C_word*)t0)[6],lf[191]);
t8=(C_word)C_a_i_list(&a,3,lf[189],t6,t7);
t9=(C_word)C_a_i_list(&a,2,lf[193],t8);
t10=(C_word)C_a_i_list(&a,3,t3,t5,t9);
t11=(C_word)C_a_i_list(&a,3,lf[194],t10,((C_word*)((C_word*)t0)[5])[1]);
t12=(C_word)C_a_i_list(&a,3,lf[189],t2,t11);
t13=(C_word)C_a_i_list(&a,3,lf[189],((C_word*)((C_word*)t0)[4])[1],t12);
t14=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t14+1)))(2,t14,(C_word)C_a_i_cons(&a,2,t13,((C_word*)((C_word*)t0)[2])[1]));}

/* k2343 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2345(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2345,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2800,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 498  return-to-host");
t3=C_retrieve(lf[186]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k2798 in k2343 in k2340 in k2337 in k2334 in k2331 in k2328 in k2325 in k2322 in k2319 in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2800(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_UNDEFINED);}

/* mp:inhook in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2314(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2314,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 383  error");
t3=*((C_word*)lf[53]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[184]);}

/* mp:micro in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2308(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2308,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 381  error");
t3=*((C_word*)lf[53]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[181]);}

/* mp:alloff in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2302(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2302,2,t0,t1);}
C_trace("ChickenBridge.scm: 379  error");
t2=*((C_word*)lf[53]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,t1,lf[178]);}

/* mp:ctrl in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2296(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_2296,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 377  error");
t6=*((C_word*)lf[53]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[175]);}

/* mp:prog in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2290(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_2290,5,t0,t1,t2,t3,t4);}
C_trace("ChickenBridge.scm: 375  error");
t5=*((C_word*)lf[53]+1);
((C_proc3)C_retrieve_proc(t5))(3,t5,t1,lf[172]);}

/* mp:off in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2284(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_2284,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 373  error");
t6=*((C_word*)lf[53]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[169]);}

/* mp:on in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2278(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_2278,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 371  error");
t6=*((C_word*)lf[53]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[166]);}

/* mp:note in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2272(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
C_word tmp;
C_word t7;
C_word t8;
C_word ab[8],*a=ab;
if(c!=7) C_bad_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr7,(void*)f_2272,7,t0,t1,t2,t3,t4,t5,t6);}
t7=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_1589,a[2]=t1,a[3]=t6,a[4]=t5,a[5]=t4,a[6]=t3,a[7]=t2,tmp=(C_word)a,a+=8,tmp);
C_trace("##sys#gc");
t8=C_retrieve(lf[117]);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,C_SCHEME_FALSE);}

/* k1587 in mp:note in k2268 in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_1589(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_1589,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[7]);
t4=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[6]);
t5=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[5]);
t6=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[4]);
t7=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[3]);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub317,a[2]=lf[163],tmp=(C_word)a,a+=3,tmp);
((C_proc8)C_retrieve_proc(t8))(8,t8,((C_word*)t0)[2],t2,t3,t4,t5,t6,t7);}

/* ferror in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_fcall f_2033(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2033,NULL,3,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2041,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_apply(5,0,t4,C_retrieve(lf[160]),t2,t3);}

/* k2039 in ferror in k2029 in k2026 in k595 in k592 in k589 in k586 */
static void C_ccall f_2041(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 288  error");
t2=*((C_word*)lf[53]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* hush in k595 in k592 in k589 in k586 */
static void C_ccall f_2017(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2017,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2021,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1699,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[117]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k1697 in hush in k595 in k592 in k589 in k586 */
static void C_ccall f_1699(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1699,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub370,a[2]=lf[156],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k2019 in hush in k595 in k592 in k589 in k586 */
static void C_ccall f_2021(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 265  values");
C_values(2,0,((C_word*)t0)[2]);}

/* stop in k595 in k592 in k589 in k586 */
static void C_ccall f_1959(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+9)){
C_save_and_reclaim((void*)tr2r,(void*)f_1959r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_1959r(t0,t1,t2);}}

static void C_ccall f_1959r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a=C_alloc(9);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1963,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 255  scheduler-stop");
f_1682(t3,C_fix(-1));}
else{
t4=C_SCHEME_UNDEFINED;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_set_block_item(t5,0,(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1977,a[2]=t5,a[3]=lf[153],tmp=(C_word)a,a+=4,tmp));
t7=((C_word*)t5)[1];
f_1977(t7,t3,t2);}}

/* do420 in stop in k595 in k592 in k589 in k586 */
static void C_fcall f_1977(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1977,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1987,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_fixnump(t4))){
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 259  scheduler-stop");
f_1682(t3,t5);}
else{
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 260  error");
t6=*((C_word*)lf[53]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t3,lf[152],t5);}}}

/* k1985 in do420 in stop in k595 in k592 in k589 in k586 */
static void C_ccall f_1987(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_1977(t3,((C_word*)t0)[2],t2);}

/* k1961 in stop in k595 in k592 in k589 in k586 */
static void C_ccall f_1963(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 261  values");
C_values(2,0,((C_word*)t0)[2]);}

/* cont in k595 in k592 in k589 in k586 */
static void C_ccall f_1950(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1950,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1954,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1677,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[117]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k1675 in cont in k595 in k592 in k589 in k586 */
static void C_ccall f_1677(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1677,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub360,a[2]=lf[149],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k1952 in cont in k595 in k592 in k589 in k586 */
static void C_ccall f_1954(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 251  values");
C_values(2,0,((C_word*)t0)[2]);}

/* paused? in k595 in k592 in k589 in k586 */
static void C_ccall f_1944(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1944,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1659,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t3=C_retrieve(lf[117]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,C_SCHEME_FALSE);}

/* k1657 in paused? in k595 in k592 in k589 in k586 */
static void C_ccall f_1659(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1659,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub352,a[2]=lf[146],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* pause in k595 in k592 in k589 in k586 */
static void C_ccall f_1935(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1935,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1939,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1668,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[117]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k1666 in pause in k595 in k592 in k589 in k586 */
static void C_ccall f_1668(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1668,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub356,a[2]=lf[143],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k1937 in pause in k595 in k592 in k589 in k586 */
static void C_ccall f_1939(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 244  values");
C_values(2,0,((C_word*)t0)[2]);}

/* time-format in k595 in k592 in k589 in k586 */
static void C_ccall f_1872(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+11)){
C_save_and_reclaim((void*)tr2rv,(void*)f_1872r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_1872r(t0,t1,t2);}}

static void C_ccall f_1872r(C_word t0,C_word t1,C_word t2){
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
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1885,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1624,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t5=C_retrieve(lf[117]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,C_SCHEME_FALSE);}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
t4=(C_word)C_i_eqvp(t3,lf[137]);
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1897,a[2]=t2,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
if(C_truep(t4)){
t6=t5;
f_1897(t6,t4);}
else{
t6=(C_word)C_eqp(t3,C_fix(1));
t7=t5;
f_1897(t7,(C_truep(t6)?t6:(C_word)C_eqp(t3,lf[140])));}}}

/* k1895 in time-format in k595 in k592 in k589 in k586 */
static void C_fcall f_1897(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a;
if(C_truep(t1)){
t2=C_mutate((C_word*)lf[133]+1,*((C_word*)lf[113]+1));
C_trace("ChickenBridge.scm: 233  scheduler-set-time-milliseconds");
f_1629(((C_word*)t0)[4],C_SCHEME_FALSE);}
else{
t2=(C_word)C_eqp(((C_word*)t0)[3],C_fix(1000));
t3=(C_truep(t2)?t2:(C_word)C_eqp(((C_word*)t0)[3],lf[138]));
if(C_truep(t3)){
t4=C_mutate((C_word*)lf[133]+1,*((C_word*)lf[111]+1));
C_trace("ChickenBridge.scm: 237  scheduler-set-time-milliseconds");
f_1629(((C_word*)t0)[4],C_SCHEME_TRUE);}
else{
t4=(C_word)C_i_vector_ref(((C_word*)t0)[2],C_fix(0));
C_trace("ChickenBridge.scm: 240  error");
t5=*((C_word*)lf[53]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,((C_word*)t0)[4],lf[139],t4);}}}

/* k1622 in time-format in k595 in k592 in k589 in k586 */
static void C_ccall f_1624(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1624,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub332,a[2]=lf[136],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k1883 in time-format in k595 in k592 in k589 in k586 */
static void C_ccall f_1885(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_truep(t1)?C_fix(1000):lf[135]));}

/* sprout in k595 in k592 in k589 in k586 */
static void C_ccall f_1704(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+12)){
C_save_and_reclaim((void*)tr3r,(void*)f_1704r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_1704r(t0,t1,t2,t3);}}

static void C_ccall f_1704r(C_word t0,C_word t1,C_word t2,C_word t3){
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
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1706,a[2]=t2,a[3]=lf[129],tmp=(C_word)a,a+=4,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1818,a[2]=t4,a[3]=lf[130],tmp=(C_word)a,a+=4,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1823,a[2]=t5,a[3]=lf[131],tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("def-start380401");
t7=t6;
f_1823(t7,t1);}
else{
t7=(C_word)C_i_car(t3);
t8=(C_word)C_i_cdr(t3);
if(C_truep((C_word)C_i_nullp(t8))){
C_trace("def-id381399");
t9=t5;
f_1818(t9,t1,t7);}
else{
t9=(C_word)C_i_car(t8);
t10=(C_word)C_i_cdr(t8);
if(C_truep((C_word)C_i_nullp(t10))){
C_trace("body378383");
t11=t4;
f_1706(t11,t1,t7,t9);}
else{
C_trace("##sys#error");
t11=*((C_word*)lf[40]+1);
((C_proc4)(void*)(*((C_word*)t11+1)))(4,t11,t1,lf[0],t10);}}}}

/* def-start380 in sprout in k595 in k592 in k589 in k586 */
static void C_fcall f_1823(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1823,NULL,2,t0,t1);}
C_trace("def-id381399");
t2=((C_word*)t0)[2];
f_1818(t2,t1,C_fix(0));}

/* def-id381 in sprout in k595 in k592 in k589 in k586 */
static void C_fcall f_1818(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1818,NULL,3,t0,t1,t2);}
C_trace("body378383");
t3=((C_word*)t0)[2];
f_1706(t3,t1,t2,C_fix(-1));}

/* body378 in sprout in k595 in k592 in k589 in k586 */
static void C_fcall f_1706(C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)trf_1706,NULL,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1708,a[2]=t4,a[3]=lf[126],tmp=(C_word)a,a+=4,tmp);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1736,a[2]=t5,a[3]=lf[127],tmp=(C_word)a,a+=4,tmp);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1766,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t0)[2]))){
t9=C_SCHEME_UNDEFINED;
t10=(*a=C_VECTOR_TYPE|1,a[1]=t9,tmp=(C_word)a,a+=2,tmp);
t11=C_set_block_item(t10,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_1777,a[2]=t6,a[3]=t7,a[4]=t10,a[5]=((C_word*)t0)[2],a[6]=lf[128],tmp=(C_word)a,a+=7,tmp));
t12=((C_word*)t10)[1];
f_1777(t12,t8,((C_word*)t0)[2]);}
else{
t9=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1809,a[2]=((C_word*)t0)[2],a[3]=t8,tmp=(C_word)a,a+=4,tmp);
t10=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1813,a[2]=t7,a[3]=((C_word*)t0)[2],a[4]=t9,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 217  nextstart");
t11=t6;
f_1708(t11,t10);}}

/* k1811 in body378 in sprout in k595 in k592 in k589 in k586 */
static void C_ccall f_1813(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1813,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1817,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 217  nextid");
t3=((C_word*)t0)[2];
f_1736(t3,t2);}

/* k1815 in k1811 in body378 in sprout in k595 in k592 in k589 in k586 */
static void C_ccall f_1817(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 217  scheduler-sprout");
f_1638(((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k1807 in body378 in sprout in k595 in k592 in k589 in k586 */
static void C_ccall f_1809(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
f_1766(2,t2,((C_word*)t0)[2]);}

/* do392 in body378 in sprout in k595 in k592 in k589 in k586 */
static void C_fcall f_1777(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1777,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,((C_word*)t0)[5]);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1787,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1802,a[2]=((C_word*)t0)[3],a[3]=t4,a[4]=t3,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 215  nextstart");
t6=((C_word*)t0)[2];
f_1708(t6,t5);}}

/* k1800 in do392 in body378 in sprout in k595 in k592 in k589 in k586 */
static void C_ccall f_1802(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1802,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1806,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 215  nextid");
t3=((C_word*)t0)[2];
f_1736(t3,t2);}

/* k1804 in k1800 in do392 in body378 in sprout in k595 in k592 in k589 in k586 */
static void C_ccall f_1806(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 215  scheduler-sprout");
f_1638(((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k1785 in do392 in body378 in sprout in k595 in k592 in k589 in k586 */
static void C_ccall f_1787(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_1777(t3,((C_word*)t0)[2],t2);}

/* k1764 in body378 in sprout in k595 in k592 in k589 in k586 */
static void C_ccall f_1766(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 221  values");
C_values(2,0,((C_word*)t0)[2]);}

/* nextid in body378 in sprout in k595 in k592 in k589 in k586 */
static void C_fcall f_1736(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_1736,NULL,2,t0,t1);}
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

/* nextstart in body378 in sprout in k595 in k592 in k589 in k586 */
static void C_fcall f_1708(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_1708,NULL,2,t0,t1);}
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

/* scheduler-stop in k595 in k592 in k589 in k586 */
static void C_fcall f_1682(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1682,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1686,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[117]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k1684 in scheduler-stop in k595 in k592 in k589 in k586 */
static void C_ccall f_1686(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1686,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_fixnum_argumentp(((C_word*)t0)[3]);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub365,a[2]=lf[123],tmp=(C_word)a,a+=3,tmp);
((C_proc4)C_retrieve_proc(t4))(4,t4,((C_word*)t0)[2],t2,t3);}

/* scheduler-sprout in k595 in k592 in k589 in k586 */
static void C_fcall f_1638(C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1638,NULL,4,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_1642,a[2]=t2,a[3]=t1,a[4]=t4,a[5]=t3,tmp=(C_word)a,a+=6,tmp);
C_trace("##sys#gc");
t6=C_retrieve(lf[117]);
((C_proc3)C_retrieve_proc(t6))(3,t6,t5,C_SCHEME_FALSE);}

/* k1640 in scheduler-sprout in k595 in k592 in k589 in k586 */
static void C_ccall f_1642(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1642,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[5]);
t4=(C_word)C_i_foreign_fixnum_argumentp(((C_word*)t0)[4]);
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub345,a[2]=lf[120],tmp=(C_word)a,a+=3,tmp);
((C_proc6)C_retrieve_proc(t5))(6,t5,((C_word*)t0)[3],t2,((C_word*)t0)[2],t3,t4);}

/* scheduler-set-time-milliseconds in k595 in k592 in k589 in k586 */
static void C_fcall f_1629(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1629,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1633,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[117]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k1631 in scheduler-set-time-milliseconds in k595 in k592 in k589 in k586 */
static void C_ccall f_1633(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1633,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub337,a[2]=lf[116],tmp=(C_word)a,a+=3,tmp);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[3],t2,((C_word*)t0)[2]);}

/* current-time-seconds in k595 in k592 in k589 in k586 */
static void C_ccall f_1617(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1617,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub329(t2));}

/* current-time-milliseconds in k595 in k592 in k589 in k586 */
static void C_ccall f_1614(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1614,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub326(t2));}

/* print-error in k595 in k592 in k589 in k586 */
static void C_ccall f_1571(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1571,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1576,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[107]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_1576(2,t4,C_SCHEME_FALSE);}}

/* k1574 in print-error in k595 in k592 in k589 in k586 */
static void C_ccall f_1576(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub307(C_SCHEME_UNDEFINED,t1));}

/* print-message in k595 in k592 in k589 in k586 */
static void C_ccall f_1557(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1557,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1562,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[107]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_1562(2,t4,C_SCHEME_FALSE);}}

/* k1560 in print-message in k595 in k592 in k589 in k586 */
static void C_ccall f_1562(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub301(C_SCHEME_UNDEFINED,t1));}

/* ranpink in k595 in k592 in k589 in k586 */
static void C_ccall f_1551(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1551,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub145(t2));}

/* ranbrown in k595 in k592 in k589 in k586 */
static void C_ccall f_1545(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1545,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub148(t2));}

/* rangamma in k595 in k592 in k589 in k586 */
static void C_ccall f_1526(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2rv,(void*)f_1526r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_1526r(t0,t1,t2);}}

static void C_ccall f_1526r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
if(C_truep((C_word)C_vemptyp(t2))){
C_trace("ChickenBridge.scm: 102  tb:rangamma");
f_809(t1,C_fix(1));}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
C_trace("ChickenBridge.scm: 102  tb:rangamma");
f_809(t1,t3);}}

/* ranpoisson in k595 in k592 in k589 in k586 */
static void C_ccall f_1507(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2rv,(void*)f_1507r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_1507r(t0,t1,t2);}}

static void C_ccall f_1507r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
if(C_truep((C_word)C_i_nullp(C_retrieve(lf[98])))){
C_trace("ChickenBridge.scm: 102  tb:ranpoisson");
f_819(t1,C_fix(1));}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
C_trace("ChickenBridge.scm: 102  tb:ranpoisson");
f_819(t1,t3);}}

/* rancauchy in k595 in k592 in k589 in k586 */
static void C_ccall f_1501(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1501,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub138(t2));}

/* rangauss in k595 in k592 in k589 in k586 */
static void C_ccall f_1461(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2r,(void*)f_1461r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_1461r(t0,t1,t2);}}

static void C_ccall f_1461r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 102  tb:rangauss");
f_780(t1,C_fix(1),C_fix(0));}
else{
t3=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 102  tb:rangauss");
f_780(t1,t4,C_fix(0));}
else{
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cdr(t2);
C_trace("ChickenBridge.scm: 102  tb:rangauss");
f_780(t1,t4,t5);}}}

/* ranexp in k595 in k592 in k589 in k586 */
static void C_ccall f_1442(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2rv,(void*)f_1442r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_1442r(t0,t1,t2);}}

static void C_ccall f_1442r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
if(C_truep((C_word)C_vemptyp(t2))){
C_trace("ChickenBridge.scm: 102  tb:ranexp");
f_791(t1,C_fix(1));}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
C_trace("ChickenBridge.scm: 102  tb:ranexp");
f_791(t1,t3);}}

/* ranbeta in k595 in k592 in k589 in k586 */
static void C_ccall f_1398(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2r,(void*)f_1398r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_1398r(t0,t1,t2);}}

static void C_ccall f_1398r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 102  tb:ranbeta");
f_798(t1,lf[88],lf[89]);}
else{
t3=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 102  tb:ranbeta");
f_798(t1,t4,t5);}
else{
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cadr(t2);
C_trace("ChickenBridge.scm: 102  tb:ranbeta");
f_798(t1,t4,t5);}}}

/* ranmiddle in k595 in k592 in k589 in k586 */
static void C_ccall f_1392(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1392,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub111(t2));}

/* ranhigh in k595 in k592 in k589 in k586 */
static void C_ccall f_1386(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1386,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub108(t2));}

/* ranlow in k595 in k592 in k589 in k586 */
static void C_ccall f_1380(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1380,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub105(t2));}

/* pick in k595 in k592 in k589 in k586 */
static void C_ccall f_1374(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2r,(void*)f_1374r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_1374r(t0,t1,t2);}}

static void C_ccall f_1374r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_trace("ChickenBridge.scm: 102  pickl");
t3=*((C_word*)lf[76]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,t2);}

/* pickl in k595 in k592 in k589 in k586 */
static void C_ccall f_1351(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1351,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 102  error");
t3=*((C_word*)lf[53]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t1,lf[77],t2);}
else{
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1368,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
t4=(C_word)C_i_length(t2);
C_trace("ChickenBridge.scm: 102  tb:rani");
f_735(t3,t4);}}

/* k1366 in pickl in k595 in k592 in k589 in k586 */
static void C_ccall f_1368(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_i_list_ref(((C_word*)t0)[2],t1));}

/* odds in k595 in k592 in k589 in k586 */
static void C_ccall f_1293(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+14)){
C_save_and_reclaim((void*)tr3r,(void*)f_1293r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_1293r(t0,t1,t2,t3);}}

static void C_ccall f_1293r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word *a=C_alloc(14);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1310,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 102  tb:ranf");
f_742(t4,lf[72]);}
else{
t4=(C_word)C_i_cdr(t3);
if(C_truep((C_word)C_i_nullp(t4))){
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1329,a[2]=t3,a[3]=t1,a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 102  tb:ranf");
f_742(t5,lf[73]);}
else{
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1345,a[2]=t3,a[3]=t1,a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 102  tb:ranf");
f_742(t5,lf[74]);}}}

/* k1343 in odds in k595 in k592 in k589 in k586 */
static void C_ccall f_1345(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_lessp(t1,((C_word*)t0)[4]);
t3=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_truep(t2)?(C_word)C_i_car(((C_word*)t0)[2]):(C_word)C_i_cadr(((C_word*)t0)[2])));}

/* k1327 in odds in k595 in k592 in k589 in k586 */
static void C_ccall f_1329(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_lessp(t1,((C_word*)t0)[4]);
t3=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_truep(t2)?(C_word)C_i_car(((C_word*)t0)[2]):C_SCHEME_FALSE));}

/* k1308 in odds in k595 in k592 in k589 in k586 */
static void C_ccall f_1310(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_lessp(t1,((C_word*)t0)[3]);
t3=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_truep(t2)?C_SCHEME_TRUE:C_SCHEME_FALSE));}

/* ran in k595 in k592 in k589 in k586 */
static void C_ccall f_1205(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+4)){
C_save_and_reclaim((void*)tr2r,(void*)f_1205r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_1205r(t0,t1,t2);}}

static void C_ccall f_1205r(C_word t0,C_word t1,C_word t2){
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
f_742(t1,lf[69]);}
else{
t3=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_fixnump(t4))){
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 102  tb:rani");
f_735(t1,t5);}
else{
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 102  tb:ranf");
f_742(t1,t5);}}
else{
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1251,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_fixnump(t5))){
t6=(C_word)C_i_cadr(t2);
t7=t4;
f_1251(t7,(C_word)C_fixnump(t6));}
else{
t6=t4;
f_1251(t6,C_SCHEME_FALSE);}}}}

/* k1249 in ran in k595 in k592 in k589 in k586 */
static void C_fcall f_1251(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_1251,NULL,2,t0,t1);}
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

/* ran-set! in k595 in k592 in k589 in k586 */
static void C_ccall f_1199(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1199,3,t0,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub80(C_SCHEME_UNDEFINED,t2));}

/* steps in k595 in k592 in k589 in k586 */
static void C_ccall f_1140(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+12)){
C_save_and_reclaim((void*)tr4rv,(void*)f_1140r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest_vector(a,C_rest_count(0));
f_1140r(t0,t1,t2,t3,t4);}}

static void C_ccall f_1140r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word *a=C_alloc(12);
t5=(C_word)C_a_i_list(&a,1,C_SCHEME_TRUE);
t6=(C_word)C_block_size(t4);
t7=C_SCHEME_UNDEFINED;
t8=(*a=C_VECTOR_TYPE|1,a[1]=t7,tmp=(C_word)a,a+=2,tmp);
t9=C_set_block_item(t8,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_1153,a[2]=t5,a[3]=t8,a[4]=t4,a[5]=t2,a[6]=lf[64],tmp=(C_word)a,a+=7,tmp));
t10=((C_word*)t8)[1];
f_1153(t10,t1,C_fix(0),t3,t6,t5);}

/* do222 in steps in k595 in k592 in k589 in k586 */
static void C_fcall f_1153(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word t12;
C_word t13;
C_word ab[16],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1153,NULL,6,t0,t1,t2,t3,t4,t5);}
t6=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
if(C_truep((C_word)C_i_lessp(t2,((C_word*)t0)[5]))){
t8=(C_word)C_a_i_list(&a,1,((C_word*)t6)[1]);
t9=(C_word)C_i_set_cdr(((C_word*)t7)[1],t8);
t10=(C_word)C_i_cdr(((C_word*)t7)[1]);
t11=C_set_block_item(t7,0,t10);
t12=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_1189,a[2]=t7,a[3]=t4,a[4]=t1,a[5]=((C_word*)t0)[3],a[6]=t2,a[7]=t6,a[8]=((C_word*)t0)[4],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 102  modulo");
t13=*((C_word*)lf[63]+1);
((C_proc4)C_retrieve_proc(t13))(4,t13,t12,t2,t4);}
else{
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,(C_word)C_i_cdr(((C_word*)t0)[2]));}}

/* k1187 in do222 in steps in k595 in k592 in k589 in k586 */
static void C_ccall f_1189(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1189,2,t0,t1);}
t2=(C_word)C_i_vector_ref(((C_word*)t0)[8],t1);
t3=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[7])[1],t2);
t4=C_mutate(((C_word *)((C_word*)t0)[7])+1,t3);
t5=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[6],C_fix(1));
t6=((C_word*)((C_word*)t0)[5])[1];
f_1153(t6,((C_word*)t0)[4],t5,((C_word*)((C_word*)t0)[7])[1],((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1]);}

/* interp in k595 in k592 in k589 in k586 */
static void C_ccall f_1134(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr3r,(void*)f_1134r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_1134r(t0,t1,t2,t3);}}

static void C_ccall f_1134r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_trace("ChickenBridge.scm: 102  interpl");
t4=*((C_word*)lf[52]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t1,t2,t3);}

/* interpl in k595 in k592 in k589 in k586 */
static void C_ccall f_1039(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+6)){
C_save_and_reclaim((void*)tr4rv,(void*)f_1039r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest_vector(a,C_rest_count(0));
f_1039r(t0,t1,t2,t3,t4);}}

static void C_ccall f_1039r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word *a=C_alloc(6);
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_1043,a[2]=t1,a[3]=t2,a[4]=t3,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("ChickenBridge.scm: 102  error");
t6=*((C_word*)lf[53]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t5,lf[58],t3);}
else{
t6=t5;
f_1043(2,t6,(C_word)C_i_car(t3));}}

/* k1041 in interpl in k595 in k592 in k589 in k586 */
static void C_ccall f_1043(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1043,2,t0,t1);}
t2=t1;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_1046,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=t3,tmp=(C_word)a,a+=7,tmp);
t5=(C_word)C_i_cdr(((C_word*)t0)[4]);
if(C_truep((C_word)C_i_nullp(t5))){
C_trace("ChickenBridge.scm: 102  err");
t6=C_retrieve(lf[56]);
((C_proc4)C_retrieve_proc(t6))(4,t6,t4,lf[57],((C_word*)t0)[4]);}
else{
t6=t4;
f_1046(2,t6,(C_word)C_i_cadr(((C_word*)t0)[4]));}}

/* k1044 in k1041 in interpl in k595 in k592 in k589 in k586 */
static void C_ccall f_1046(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_1046,2,t0,t1);}
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
t13=C_set_block_item(t12,0,(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_1058,a[2]=((C_word*)t0)[4],a[3]=t12,a[4]=t9,a[5]=t7,a[6]=t3,a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[3],a[9]=t5,a[10]=lf[55],tmp=(C_word)a,a+=11,tmp));
t14=((C_word*)t12)[1];
f_1058(t14,((C_word*)t0)[2],t10);}

/* do206 in k1044 in k1041 in interpl in k595 in k592 in k589 in k586 */
static void C_fcall f_1058(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_1058,NULL,3,t0,t1,t2);}
t3=(C_word)C_i_nullp(t2);
t4=(C_truep(t3)?t3:(C_word)C_i_greaterp(((C_word*)((C_word*)t0)[9])[1],((C_word*)t0)[8]));
if(C_truep(t4)){
C_trace("ChickenBridge.scm: 102  tb:rescale");
f_599(t1,((C_word*)t0)[8],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[9])[1],((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[4]);}
else{
t5=C_mutate(((C_word *)((C_word*)t0)[7])+1,((C_word*)((C_word*)t0)[9])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[6])+1,((C_word*)((C_word*)t0)[5])[1]);
t7=(C_word)C_i_car(t2);
t8=C_mutate(((C_word *)((C_word*)t0)[9])+1,t7);
t9=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1080,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t10=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t10))){
C_trace("ChickenBridge.scm: 102  error");
t11=*((C_word*)lf[53]+1);
((C_proc4)C_retrieve_proc(t11))(4,t11,t9,lf[54],((C_word*)t0)[2]);}
else{
t11=(C_word)C_i_cadr(t2);
t12=C_mutate(((C_word *)((C_word*)t0)[5])+1,t11);
t13=t9;
f_1080(2,t13,t12);}}}

/* k1078 in do206 in k1044 in k1041 in interpl in k595 in k592 in k589 in k586 */
static void C_ccall f_1080(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cddr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_1058(t3,((C_word*)t0)[2],t2);}

/* hertz->keynum in k595 in k592 in k589 in k586 */
static void C_ccall f_1033(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1033,3,t0,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub75(t3,t4));}

/* keynum->pc in k595 in k592 in k589 in k586 */
static void C_ccall f_1027(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1027,3,t0,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub71(C_SCHEME_UNDEFINED,t3));}

/* keynum->hertz in k595 in k592 in k589 in k586 */
static void C_ccall f_1021(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1021,3,t0,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub66(t3,t4));}

/* scaler->cents in k595 in k592 in k589 in k586 */
static void C_ccall f_1015(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1015,3,t0,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub62(C_SCHEME_UNDEFINED,t3));}

/* cents->scaler in k595 in k592 in k589 in k586 */
static void C_ccall f_1009(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1009,3,t0,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_fixnum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub57(t3,t4));}

/* rhythm->seconds in k595 in k592 in k589 in k586 */
static void C_ccall f_949(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+12)){
C_save_and_reclaim((void*)tr3r,(void*)f_949r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_949r(t0,t1,t2,t3);}}

static void C_ccall f_949r(C_word t0,C_word t1,C_word t2,C_word t3){
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
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_951,a[2]=t2,a[3]=lf[35],tmp=(C_word)a,a+=4,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_956,a[2]=t4,a[3]=lf[37],tmp=(C_word)a,a+=4,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_961,a[2]=t5,a[3]=lf[39],tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("def-tempo179187");
t7=t6;
f_961(t7,t1);}
else{
t7=(C_word)C_i_car(t3);
t8=(C_word)C_i_cdr(t3);
if(C_truep((C_word)C_i_nullp(t8))){
C_trace("def-beat180185");
t9=t5;
f_956(t9,t1,t7);}
else{
t9=(C_word)C_i_car(t8);
t10=(C_word)C_i_cdr(t8);
if(C_truep((C_word)C_i_nullp(t10))){
C_trace("body177182");
t11=t4;
f_951(t11,t1,t7,t9);}
else{
C_trace("##sys#error");
t11=*((C_word*)lf[40]+1);
((C_proc4)(void*)(*((C_word*)t11+1)))(4,t11,t1,lf[0],t10);}}}}

/* def-tempo179 in rhythm->seconds in k595 in k592 in k589 in k586 */
static void C_fcall f_961(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_961,NULL,2,t0,t1);}
C_trace("def-beat180185");
t2=((C_word*)t0)[2];
f_956(t2,t1,lf[38]);}

/* def-beat180 in rhythm->seconds in k595 in k592 in k589 in k586 */
static void C_fcall f_956(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_956,NULL,3,t0,t1,t2);}
C_trace("body177182");
t3=((C_word*)t0)[2];
f_951(t3,t1,t2,lf[36]);}

/* body177 in rhythm->seconds in k595 in k592 in k589 in k586 */
static void C_fcall f_951(C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)trf_951,NULL,4,t0,t1,t2,t3);}
t4=((C_word*)t0)[2];
t5=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t6=(C_word)C_i_foreign_flonum_argumentp(t4);
t7=(C_word)C_i_foreign_flonum_argumentp(t2);
t8=(C_word)C_i_foreign_flonum_argumentp(t3);
t9=t1;
((C_proc2)(void*)(*((C_word*)t9+1)))(2,t9,(C_word)stub50(t5,t6,t7,t8));}

/* decimals in k595 in k592 in k589 in k586 */
static void C_ccall f_930(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr3rv,(void*)f_930r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest_vector(a,C_rest_count(0));
f_930r(t0,t1,t2,t3);}}

static void C_ccall f_930r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
if(C_truep((C_word)C_vemptyp(t3))){
C_trace("ChickenBridge.scm: 102  tb:decimals");
f_660(t1,t2,C_fix(3));}
else{
t4=(C_word)C_i_vector_ref(t3,C_fix(0));
C_trace("ChickenBridge.scm: 102  tb:decimals");
f_660(t1,t2,t4);}}

/* quantize in k595 in k592 in k589 in k586 */
static void C_ccall f_924(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_924,4,t0,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_flonum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub42(t4,t5,t6));}

/* int in k595 in k592 in k589 in k586 */
static void C_ccall f_918(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_918,3,t0,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub30(C_SCHEME_UNDEFINED,t3));}

/* lookup in k595 in k592 in k589 in k586 */
static void C_ccall f_870(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,...){
C_word tmp;
C_word t6;
va_list v;
C_word *a,c2=c;
C_save_rest(t5,c2,6);
if(c<6) C_bad_min_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+4)){
C_save_and_reclaim((void*)tr6r,(void*)f_870r,6,t0,t1,t2,t3,t4,t5);}
else{
a=C_alloc((c-6)*3);
t6=C_restore_rest(a,C_rest_count(0));
f_870r(t0,t1,t2,t3,t4,t5,t6);}}

static void C_ccall f_870r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
C_word tmp;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word t12;
C_word t13;
C_word *a=C_alloc(4);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_878,a[2]=t5,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_nullp(t6))){
t8=(C_word)C_i_length(t5);
C_trace("ChickenBridge.scm: 102  tb:discrete");
f_626(t7,t2,t3,t4,C_fix(0),t8,C_fix(1));}
else{
t8=(C_word)C_i_cdr(t6);
if(C_truep((C_word)C_i_nullp(t8))){
t9=(C_word)C_i_car(t6);
C_trace("ChickenBridge.scm: 102  tb:discrete");
f_626(t7,t2,t3,t4,C_fix(0),t9,C_fix(1));}
else{
t9=(C_word)C_i_car(t6);
t10=(C_word)C_i_cdr(t6);
C_trace("ChickenBridge.scm: 102  tb:discrete");
f_626(t7,t2,t3,t4,C_fix(0),t9,t10);}}}

/* k876 in lookup in k595 in k592 in k589 in k586 */
static void C_ccall f_878(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_i_list_ref(((C_word*)t0)[2],t1));}

/* discrete in k595 in k592 in k589 in k586 */
static void C_ccall f_851(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,...){
C_word tmp;
C_word t7;
va_list v;
C_word *a,c2=c;
C_save_rest(t6,c2,7);
if(c<7) C_bad_min_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr7rv,(void*)f_851r,7,t0,t1,t2,t3,t4,t5,t6);}
else{
a=C_alloc((c-7)*3);
t7=C_restore_rest_vector(a,C_rest_count(0));
f_851r(t0,t1,t2,t3,t4,t5,t6,t7);}}

static void C_ccall f_851r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
C_word tmp;
C_word t8;
C_word t9;
if(C_truep((C_word)C_vemptyp(t7))){
C_trace("ChickenBridge.scm: 102  tb:discrete");
f_626(t1,t2,t3,t4,t5,t6,C_fix(1));}
else{
t8=(C_word)C_i_vector_ref(t7,C_fix(0));
C_trace("ChickenBridge.scm: 102  tb:discrete");
f_626(t1,t2,t3,t4,t5,t6,t8);}}

/* rescale in k595 in k592 in k589 in k586 */
static void C_ccall f_832(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,...){
C_word tmp;
C_word t7;
va_list v;
C_word *a,c2=c;
C_save_rest(t6,c2,7);
if(c<7) C_bad_min_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr7rv,(void*)f_832r,7,t0,t1,t2,t3,t4,t5,t6);}
else{
a=C_alloc((c-7)*3);
t7=C_restore_rest_vector(a,C_rest_count(0));
f_832r(t0,t1,t2,t3,t4,t5,t6,t7);}}

static void C_ccall f_832r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
C_word tmp;
C_word t8;
C_word t9;
if(C_truep((C_word)C_vemptyp(t7))){
C_trace("ChickenBridge.scm: 102  tb:rescale");
f_599(t1,t2,t3,t4,t5,t6,C_fix(1));}
else{
t8=(C_word)C_i_vector_ref(t7,C_fix(0));
C_trace("ChickenBridge.scm: 102  tb:rescale");
f_599(t1,t2,t3,t4,t5,t6,t8);}}

/* tb:ranpoisson in k595 in k592 in k589 in k586 */
static void C_fcall f_819(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_819,NULL,2,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub142(C_SCHEME_UNDEFINED,t3));}

/* tb:rangamma in k595 in k592 in k589 in k586 */
static void C_fcall f_809(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_809,NULL,2,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub134(t3,t4));}

/* tb:ranbeta in k595 in k592 in k589 in k586 */
static void C_fcall f_798(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_798,NULL,3,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_flonum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub128(t4,t5,t6));}

/* tb:ranexp in k595 in k592 in k589 in k586 */
static void C_fcall f_791(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_791,NULL,2,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub122(t3,t4));}

/* tb:rangauss in k595 in k592 in k589 in k586 */
static void C_fcall f_780(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_780,NULL,3,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_flonum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub116(t4,t5,t6));}

/* tb:ranf in k595 in k592 in k589 in k586 */
static void C_fcall f_742(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_742,NULL,2,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub88(t3,t4));}

/* tb:rani in k595 in k592 in k589 in k586 */
static void C_fcall f_735(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_735,NULL,2,t1,t2);}
t3=(C_word)C_i_foreign_fixnum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub84(C_SCHEME_UNDEFINED,t3));}

/* tb:decimals in k595 in k592 in k589 in k586 */
static void C_fcall f_660(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_660,NULL,3,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_fixnum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub35(t4,t5,t6));}

/* tb:discrete in k595 in k592 in k589 in k586 */
static void C_fcall f_626(C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
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
C_save_and_reclaim((void*)trf_626,NULL,7,t1,t2,t3,t4,t5,t6,t7);}
t8=(C_word)C_i_foreign_flonum_argumentp(t2);
t9=(C_word)C_i_foreign_flonum_argumentp(t3);
t10=(C_word)C_i_foreign_flonum_argumentp(t4);
t11=(C_word)C_i_foreign_fixnum_argumentp(t5);
t12=(C_word)C_i_foreign_fixnum_argumentp(t6);
t13=(C_word)C_i_foreign_flonum_argumentp(t7);
t14=t1;
((C_proc2)(void*)(*((C_word*)t14+1)))(2,t14,(C_word)stub21(C_SCHEME_UNDEFINED,t8,t9,t10,t11,t12,t13));}

/* tb:rescale in k595 in k592 in k589 in k586 */
static void C_fcall f_599(C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
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
C_save_and_reclaim((void*)trf_599,NULL,7,t1,t2,t3,t4,t5,t6,t7);}
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
static C_PTABLE_ENTRY ptable[183] = {
{"toplevelChickenBridge.scm",(void*)C_grace_toplevel},
{"f_588ChickenBridge.scm",(void*)f_588},
{"f_591ChickenBridge.scm",(void*)f_591},
{"f_594ChickenBridge.scm",(void*)f_594},
{"f_597ChickenBridge.scm",(void*)f_597},
{"f_2028ChickenBridge.scm",(void*)f_2028},
{"f_2814ChickenBridge.scm",(void*)f_2814},
{"f_2861ChickenBridge.scm",(void*)f_2861},
{"f_2851ChickenBridge.scm",(void*)f_2851},
{"f_2818ChickenBridge.scm",(void*)f_2818},
{"f_2031ChickenBridge.scm",(void*)f_2031},
{"f_2808ChickenBridge.scm",(void*)f_2808},
{"f_2047ChickenBridge.scm",(void*)f_2047},
{"f_2260ChickenBridge.scm",(void*)f_2260},
{"f_2050ChickenBridge.scm",(void*)f_2050},
{"f_2053ChickenBridge.scm",(void*)f_2053},
{"f_2065ChickenBridge.scm",(void*)f_2065},
{"f_2113ChickenBridge.scm",(void*)f_2113},
{"f_2129ChickenBridge.scm",(void*)f_2129},
{"f_2139ChickenBridge.scm",(void*)f_2139},
{"f_2238ChickenBridge.scm",(void*)f_2238},
{"f_2234ChickenBridge.scm",(void*)f_2234},
{"f_2183ChickenBridge.scm",(void*)f_2183},
{"f_2189ChickenBridge.scm",(void*)f_2189},
{"f_2123ChickenBridge.scm",(void*)f_2123},
{"f_2068ChickenBridge.scm",(void*)f_2068},
{"f_2073ChickenBridge.scm",(void*)f_2073},
{"f_2086ChickenBridge.scm",(void*)f_2086},
{"f_2270ChickenBridge.scm",(void*)f_2270},
{"f_2321ChickenBridge.scm",(void*)f_2321},
{"f_2324ChickenBridge.scm",(void*)f_2324},
{"f_2327ChickenBridge.scm",(void*)f_2327},
{"f_2330ChickenBridge.scm",(void*)f_2330},
{"f_2333ChickenBridge.scm",(void*)f_2333},
{"f_2336ChickenBridge.scm",(void*)f_2336},
{"f_2339ChickenBridge.scm",(void*)f_2339},
{"f_2342ChickenBridge.scm",(void*)f_2342},
{"f_2802ChickenBridge.scm",(void*)f_2802},
{"f_2360ChickenBridge.scm",(void*)f_2360},
{"f_2363ChickenBridge.scm",(void*)f_2363},
{"f_2637ChickenBridge.scm",(void*)f_2637},
{"f_2745ChickenBridge.scm",(void*)f_2745},
{"f_2657ChickenBridge.scm",(void*)f_2657},
{"f_2666ChickenBridge.scm",(void*)f_2666},
{"f_2670ChickenBridge.scm",(void*)f_2670},
{"f_2674ChickenBridge.scm",(void*)f_2674},
{"f_2682ChickenBridge.scm",(void*)f_2682},
{"f_2678ChickenBridge.scm",(void*)f_2678},
{"f_2647ChickenBridge.scm",(void*)f_2647},
{"f_2366ChickenBridge.scm",(void*)f_2366},
{"f_2369ChickenBridge.scm",(void*)f_2369},
{"f_2372ChickenBridge.scm",(void*)f_2372},
{"f_2375ChickenBridge.scm",(void*)f_2375},
{"f_2378ChickenBridge.scm",(void*)f_2378},
{"f_2631ChickenBridge.scm",(void*)f_2631},
{"f_2530ChickenBridge.scm",(void*)f_2530},
{"f_2537ChickenBridge.scm",(void*)f_2537},
{"f_2539ChickenBridge.scm",(void*)f_2539},
{"f_2611ChickenBridge.scm",(void*)f_2611},
{"f_2563ChickenBridge.scm",(void*)f_2563},
{"f_2566ChickenBridge.scm",(void*)f_2566},
{"f_2587ChickenBridge.scm",(void*)f_2587},
{"f_2553ChickenBridge.scm",(void*)f_2553},
{"f_2381ChickenBridge.scm",(void*)f_2381},
{"f_2519ChickenBridge.scm",(void*)f_2519},
{"f_2507ChickenBridge.scm",(void*)f_2507},
{"f_2503ChickenBridge.scm",(void*)f_2503},
{"f_2388ChickenBridge.scm",(void*)f_2388},
{"f_2345ChickenBridge.scm",(void*)f_2345},
{"f_2800ChickenBridge.scm",(void*)f_2800},
{"f_2314ChickenBridge.scm",(void*)f_2314},
{"f_2308ChickenBridge.scm",(void*)f_2308},
{"f_2302ChickenBridge.scm",(void*)f_2302},
{"f_2296ChickenBridge.scm",(void*)f_2296},
{"f_2290ChickenBridge.scm",(void*)f_2290},
{"f_2284ChickenBridge.scm",(void*)f_2284},
{"f_2278ChickenBridge.scm",(void*)f_2278},
{"f_2272ChickenBridge.scm",(void*)f_2272},
{"f_1589ChickenBridge.scm",(void*)f_1589},
{"f_2033ChickenBridge.scm",(void*)f_2033},
{"f_2041ChickenBridge.scm",(void*)f_2041},
{"f_2017ChickenBridge.scm",(void*)f_2017},
{"f_1699ChickenBridge.scm",(void*)f_1699},
{"f_2021ChickenBridge.scm",(void*)f_2021},
{"f_1959ChickenBridge.scm",(void*)f_1959},
{"f_1977ChickenBridge.scm",(void*)f_1977},
{"f_1987ChickenBridge.scm",(void*)f_1987},
{"f_1963ChickenBridge.scm",(void*)f_1963},
{"f_1950ChickenBridge.scm",(void*)f_1950},
{"f_1677ChickenBridge.scm",(void*)f_1677},
{"f_1954ChickenBridge.scm",(void*)f_1954},
{"f_1944ChickenBridge.scm",(void*)f_1944},
{"f_1659ChickenBridge.scm",(void*)f_1659},
{"f_1935ChickenBridge.scm",(void*)f_1935},
{"f_1668ChickenBridge.scm",(void*)f_1668},
{"f_1939ChickenBridge.scm",(void*)f_1939},
{"f_1872ChickenBridge.scm",(void*)f_1872},
{"f_1897ChickenBridge.scm",(void*)f_1897},
{"f_1624ChickenBridge.scm",(void*)f_1624},
{"f_1885ChickenBridge.scm",(void*)f_1885},
{"f_1704ChickenBridge.scm",(void*)f_1704},
{"f_1823ChickenBridge.scm",(void*)f_1823},
{"f_1818ChickenBridge.scm",(void*)f_1818},
{"f_1706ChickenBridge.scm",(void*)f_1706},
{"f_1813ChickenBridge.scm",(void*)f_1813},
{"f_1817ChickenBridge.scm",(void*)f_1817},
{"f_1809ChickenBridge.scm",(void*)f_1809},
{"f_1777ChickenBridge.scm",(void*)f_1777},
{"f_1802ChickenBridge.scm",(void*)f_1802},
{"f_1806ChickenBridge.scm",(void*)f_1806},
{"f_1787ChickenBridge.scm",(void*)f_1787},
{"f_1766ChickenBridge.scm",(void*)f_1766},
{"f_1736ChickenBridge.scm",(void*)f_1736},
{"f_1708ChickenBridge.scm",(void*)f_1708},
{"f_1682ChickenBridge.scm",(void*)f_1682},
{"f_1686ChickenBridge.scm",(void*)f_1686},
{"f_1638ChickenBridge.scm",(void*)f_1638},
{"f_1642ChickenBridge.scm",(void*)f_1642},
{"f_1629ChickenBridge.scm",(void*)f_1629},
{"f_1633ChickenBridge.scm",(void*)f_1633},
{"f_1617ChickenBridge.scm",(void*)f_1617},
{"f_1614ChickenBridge.scm",(void*)f_1614},
{"f_1571ChickenBridge.scm",(void*)f_1571},
{"f_1576ChickenBridge.scm",(void*)f_1576},
{"f_1557ChickenBridge.scm",(void*)f_1557},
{"f_1562ChickenBridge.scm",(void*)f_1562},
{"f_1551ChickenBridge.scm",(void*)f_1551},
{"f_1545ChickenBridge.scm",(void*)f_1545},
{"f_1526ChickenBridge.scm",(void*)f_1526},
{"f_1507ChickenBridge.scm",(void*)f_1507},
{"f_1501ChickenBridge.scm",(void*)f_1501},
{"f_1461ChickenBridge.scm",(void*)f_1461},
{"f_1442ChickenBridge.scm",(void*)f_1442},
{"f_1398ChickenBridge.scm",(void*)f_1398},
{"f_1392ChickenBridge.scm",(void*)f_1392},
{"f_1386ChickenBridge.scm",(void*)f_1386},
{"f_1380ChickenBridge.scm",(void*)f_1380},
{"f_1374ChickenBridge.scm",(void*)f_1374},
{"f_1351ChickenBridge.scm",(void*)f_1351},
{"f_1368ChickenBridge.scm",(void*)f_1368},
{"f_1293ChickenBridge.scm",(void*)f_1293},
{"f_1345ChickenBridge.scm",(void*)f_1345},
{"f_1329ChickenBridge.scm",(void*)f_1329},
{"f_1310ChickenBridge.scm",(void*)f_1310},
{"f_1205ChickenBridge.scm",(void*)f_1205},
{"f_1251ChickenBridge.scm",(void*)f_1251},
{"f_1199ChickenBridge.scm",(void*)f_1199},
{"f_1140ChickenBridge.scm",(void*)f_1140},
{"f_1153ChickenBridge.scm",(void*)f_1153},
{"f_1189ChickenBridge.scm",(void*)f_1189},
{"f_1134ChickenBridge.scm",(void*)f_1134},
{"f_1039ChickenBridge.scm",(void*)f_1039},
{"f_1043ChickenBridge.scm",(void*)f_1043},
{"f_1046ChickenBridge.scm",(void*)f_1046},
{"f_1058ChickenBridge.scm",(void*)f_1058},
{"f_1080ChickenBridge.scm",(void*)f_1080},
{"f_1033ChickenBridge.scm",(void*)f_1033},
{"f_1027ChickenBridge.scm",(void*)f_1027},
{"f_1021ChickenBridge.scm",(void*)f_1021},
{"f_1015ChickenBridge.scm",(void*)f_1015},
{"f_1009ChickenBridge.scm",(void*)f_1009},
{"f_949ChickenBridge.scm",(void*)f_949},
{"f_961ChickenBridge.scm",(void*)f_961},
{"f_956ChickenBridge.scm",(void*)f_956},
{"f_951ChickenBridge.scm",(void*)f_951},
{"f_930ChickenBridge.scm",(void*)f_930},
{"f_924ChickenBridge.scm",(void*)f_924},
{"f_918ChickenBridge.scm",(void*)f_918},
{"f_870ChickenBridge.scm",(void*)f_870},
{"f_878ChickenBridge.scm",(void*)f_878},
{"f_851ChickenBridge.scm",(void*)f_851},
{"f_832ChickenBridge.scm",(void*)f_832},
{"f_819ChickenBridge.scm",(void*)f_819},
{"f_809ChickenBridge.scm",(void*)f_809},
{"f_798ChickenBridge.scm",(void*)f_798},
{"f_791ChickenBridge.scm",(void*)f_791},
{"f_780ChickenBridge.scm",(void*)f_780},
{"f_742ChickenBridge.scm",(void*)f_742},
{"f_735ChickenBridge.scm",(void*)f_735},
{"f_660ChickenBridge.scm",(void*)f_660},
{"f_626ChickenBridge.scm",(void*)f_626},
{"f_599ChickenBridge.scm",(void*)f_599},
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
