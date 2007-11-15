/* Generated from ChickenBridge.scm by the CHICKEN compiler
   http://www.call-with-current-continuation.org
   2007-11-15 14:56
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

static C_TLS C_word lf[220];


/* from k1235 in hush in k519 in k516 in k513 in k510 */
C_noret_decl(stub294)
static void C_ccall stub294(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub294(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_hush();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1229 */
C_noret_decl(stub289)
static void C_ccall stub289(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0) C_noret;
static void C_ccall stub289(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_unfix(C_a0);
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_stop(t0);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1213 in cont in k519 in k516 in k513 in k510 */
C_noret_decl(stub284)
static void C_ccall stub284(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub284(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_cont();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1204 in pause in k519 in k516 in k513 in k510 */
C_noret_decl(stub280)
static void C_ccall stub280(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub280(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_pause();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1195 in paused? in k519 in k516 in k513 in k510 */
C_noret_decl(stub276)
static void C_ccall stub276(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub276(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
C_r=C_mk_bool(scheduler_is_paused());
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1189 */
C_noret_decl(stub269)
static void C_ccall stub269(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2) C_noret;
static void C_ccall stub269(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
C_word t0=(C_word )(C_a0);
double t1=(double )C_c_double(C_a1);
int t2=(int )C_unfix(C_a2);
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_sprout(t0,t1,t2);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1169 in scheduler-set-time-milliseconds in k519 in k516 in k513 in k510 */
C_noret_decl(stub261)
static void C_ccall stub261(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0) C_noret;
static void C_ccall stub261(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_truep(C_a0);
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_set_time_milliseconds(t0);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1160 in time-format in k519 in k516 in k513 in k510 */
C_noret_decl(stub256)
static void C_ccall stub256(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub256(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
C_r=C_mk_bool(scheduler_is_time_milliseconds());
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from current-time-seconds in k519 in k516 in k513 in k510 */
#define return(x) C_cblock C_r = (C_flonum(&C_a,(x))); goto C_ret; C_cblockend
static C_word C_fcall stub253(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub253(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
 C_return( (Time::getMillisecondCounterHiRes() / 1000.0) );
C_ret:
#undef return

return C_r;}

/* from current-time-milliseconds in k519 in k516 in k513 in k510 */
#define return(x) C_cblock C_r = (C_flonum(&C_a,(x))); goto C_ret; C_cblockend
static C_word C_fcall stub250(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub250(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
 C_return( Time::getMillisecondCounterHiRes());
C_ret:
#undef return

return C_r;}

/* from k1148 */
C_noret_decl(stub241)
static void C_ccall stub241(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2,C_word C_a3,C_word C_a4) C_noret;
static void C_ccall stub241(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2,C_word C_a3,C_word C_a4){
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

/* from k1112 in print-error in k519 in k516 in k513 in k510 */
static C_word C_fcall stub231(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub231(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_error(t0);
return C_r;}

/* from k1098 in print-message in k519 in k516 in k513 in k510 */
static C_word C_fcall stub225(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub225(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_message(t0);
return C_r;}

/* from k691 */
static C_word C_fcall stub100(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub100(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
C_r=C_flonum(&C_a,Toolbox::ran(t0,t1));
return C_r;}

/* from k680 */
static C_word C_fcall stub94(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub94(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_unfix(C_a0);
int t1=(int )C_unfix(C_a1);
C_r=C_fix((C_word)Toolbox::ran(t0,t1));
return C_r;}

/* from k669 */
static C_word C_fcall stub88(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub88(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::ran(t0));
return C_r;}

/* from k662 */
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

/* from k652 */
static C_word C_fcall stub75(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub75(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::hertz_to_keynum(t0));
return C_r;}

/* from k645 */
static C_word C_fcall stub71(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub71(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_fix((C_word)Toolbox::keynum_to_pc(t0));
return C_r;}

/* from k638 */
static C_word C_fcall stub66(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub66(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::keynum_to_hertz(t0));
return C_r;}

/* from k631 */
static C_word C_fcall stub62(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub62(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_fix((C_word)Toolbox::scaler_to_cents(t0));
return C_r;}

/* from k624 */
static C_word C_fcall stub57(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub57(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_unfix(C_a0);
C_r=C_flonum(&C_a,Toolbox::cents_to_scaler(t0));
return C_r;}

/* from k617 */
static C_word C_fcall stub50(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2) C_regparm;
C_regparm static C_word C_fcall stub50(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
float t2=(float )C_c_double(C_a2);
C_r=C_flonum(&C_a,Toolbox::rhythm_to_seconds(t0,t1,t2));
return C_r;}

/* from k602 */
static C_word C_fcall stub42(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub42(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
C_r=C_flonum(&C_a,Toolbox::quantize(t0,t1));
return C_r;}

/* from k591 */
static C_word C_fcall stub35(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub35(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
int t1=(int )C_unfix(C_a1);
C_r=C_flonum(&C_a,Toolbox::decimals(t0,t1));
return C_r;}

/* from k580 */
static C_word C_fcall stub30(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub30(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_fix((C_word)Toolbox::float_to_fixnum(t0));
return C_r;}

/* from k573 */
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

/* from k546 */
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
C_noret_decl(f_512)
static void C_ccall f_512(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_515)
static void C_ccall f_515(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_518)
static void C_ccall f_518(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_521)
static void C_ccall f_521(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1566)
static void C_ccall f_1566(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2352)
static void C_ccall f_2352(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_2399)
static void C_ccall f_2399(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2389)
static void C_ccall f_2389(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2356)
static void C_ccall f_2356(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1569)
static void C_ccall f_1569(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2346)
static void C_ccall f_2346(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_2346)
static void C_ccall f_2346r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_1585)
static void C_ccall f_1585(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1798)
static void C_ccall f_1798(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1588)
static void C_ccall f_1588(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1591)
static void C_ccall f_1591(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1603)
static void C_ccall f_1603(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1651)
static void C_fcall f_1651(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_1667)
static void C_ccall f_1667(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1677)
static void C_ccall f_1677(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1776)
static void C_ccall f_1776(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1772)
static void C_ccall f_1772(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1721)
static void C_ccall f_1721(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1727)
static void C_ccall f_1727(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1661)
static void C_fcall f_1661(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1606)
static void C_ccall f_1606(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1611)
static void C_fcall f_1611(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1624)
static void C_fcall f_1624(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1808)
static void C_ccall f_1808(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1859)
static void C_ccall f_1859(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1862)
static void C_ccall f_1862(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1865)
static void C_ccall f_1865(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1868)
static void C_ccall f_1868(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1871)
static void C_ccall f_1871(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1874)
static void C_ccall f_1874(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1877)
static void C_ccall f_1877(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1880)
static void C_ccall f_1880(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2340)
static void C_ccall f_2340(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_2340)
static void C_ccall f_2340r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_1898)
static void C_ccall f_1898(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1901)
static void C_ccall f_1901(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2175)
static void C_fcall f_2175(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2283)
static void C_ccall f_2283(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2195)
static void C_fcall f_2195(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2204)
static void C_fcall f_2204(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2208)
static void C_ccall f_2208(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2212)
static void C_ccall f_2212(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2220)
static void C_fcall f_2220(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2216)
static void C_ccall f_2216(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2185)
static void C_ccall f_2185(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1904)
static void C_ccall f_1904(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1907)
static void C_ccall f_1907(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1910)
static void C_ccall f_1910(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1913)
static void C_ccall f_1913(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1916)
static void C_ccall f_1916(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2169)
static void C_ccall f_2169(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2068)
static void C_fcall f_2068(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2075)
static void C_ccall f_2075(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2077)
static void C_fcall f_2077(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2149)
static void C_ccall f_2149(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2101)
static void C_fcall f_2101(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2104)
static void C_ccall f_2104(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2125)
static void C_ccall f_2125(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2091)
static void C_ccall f_2091(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1919)
static void C_ccall f_1919(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2057)
static void C_ccall f_2057(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2045)
static void C_ccall f_2045(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2041)
static void C_ccall f_2041(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1926)
static void C_fcall f_1926(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1883)
static void C_ccall f_1883(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2338)
static void C_ccall f_2338(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1852)
static void C_ccall f_1852(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1846)
static void C_ccall f_1846(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1840)
static void C_ccall f_1840(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1834)
static void C_ccall f_1834(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_1828)
static void C_ccall f_1828(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_1822)
static void C_ccall f_1822(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_1816)
static void C_ccall f_1816(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_1810)
static void C_ccall f_1810(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_1127)
static void C_ccall f_1127(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1571)
static void C_fcall f_1571(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1579)
static void C_ccall f_1579(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1555)
static void C_ccall f_1555(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1237)
static void C_ccall f_1237(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1559)
static void C_ccall f_1559(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1497)
static void C_ccall f_1497(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1497)
static void C_ccall f_1497r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1515)
static void C_fcall f_1515(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1525)
static void C_ccall f_1525(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1501)
static void C_ccall f_1501(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1488)
static void C_ccall f_1488(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1215)
static void C_ccall f_1215(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1492)
static void C_ccall f_1492(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1482)
static void C_ccall f_1482(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1197)
static void C_ccall f_1197(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1473)
static void C_ccall f_1473(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1206)
static void C_ccall f_1206(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1477)
static void C_ccall f_1477(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1410)
static void C_ccall f_1410(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1410)
static void C_ccall f_1410r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1435)
static void C_fcall f_1435(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1162)
static void C_ccall f_1162(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1423)
static void C_ccall f_1423(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1242)
static void C_ccall f_1242(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_1242)
static void C_ccall f_1242r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_1361)
static void C_fcall f_1361(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1356)
static void C_fcall f_1356(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1244)
static void C_fcall f_1244(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_1351)
static void C_ccall f_1351(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1355)
static void C_ccall f_1355(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1347)
static void C_ccall f_1347(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1315)
static void C_fcall f_1315(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1340)
static void C_ccall f_1340(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1344)
static void C_ccall f_1344(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1325)
static void C_ccall f_1325(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1304)
static void C_ccall f_1304(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1274)
static void C_fcall f_1274(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1246)
static void C_fcall f_1246(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1220)
static void C_fcall f_1220(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1224)
static void C_ccall f_1224(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1176)
static void C_fcall f_1176(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_1180)
static void C_ccall f_1180(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1167)
static void C_fcall f_1167(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1171)
static void C_ccall f_1171(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1155)
static void C_ccall f_1155(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1152)
static void C_ccall f_1152(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1109)
static void C_ccall f_1109(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1114)
static void C_ccall f_1114(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1095)
static void C_ccall f_1095(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1100)
static void C_ccall f_1100(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1089)
static void C_ccall f_1089(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1089)
static void C_ccall f_1089r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1066)
static void C_ccall f_1066(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1083)
static void C_ccall f_1083(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_999)
static void C_ccall f_999(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_999)
static void C_ccall f_999r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_1018)
static void C_fcall f_1018(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1013)
static void C_fcall f_1013(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1001)
static void C_fcall f_1001(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_1012)
static void C_ccall f_1012(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_948)
static void C_ccall f_948(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_948)
static void C_ccall f_948r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_973)
static void C_fcall f_973(C_word t0,C_word t1) C_noret;
C_noret_decl(f_942)
static void C_ccall f_942(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_936)
static void C_ccall f_936(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_936)
static void C_ccall f_936r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_841)
static void C_ccall f_841(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_841)
static void C_ccall f_841r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_845)
static void C_ccall f_845(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_848)
static void C_ccall f_848(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_860)
static void C_fcall f_860(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_882)
static void C_ccall f_882(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_835)
static void C_ccall f_835(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_829)
static void C_ccall f_829(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_823)
static void C_ccall f_823(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_817)
static void C_ccall f_817(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_811)
static void C_ccall f_811(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_751)
static void C_ccall f_751(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_751)
static void C_ccall f_751r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_763)
static void C_fcall f_763(C_word t0,C_word t1) C_noret;
C_noret_decl(f_758)
static void C_fcall f_758(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_753)
static void C_fcall f_753(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_745)
static void C_ccall f_745(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_739)
static void C_ccall f_739(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_733)
static void C_ccall f_733(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_714)
static void C_ccall f_714(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,...) C_noret;
C_noret_decl(f_714)
static void C_ccall f_714r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t8) C_noret;
C_noret_decl(f_695)
static void C_ccall f_695(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,...) C_noret;
C_noret_decl(f_695)
static void C_ccall f_695r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t8) C_noret;
C_noret_decl(f_666)
static void C_fcall f_666(C_word t0,C_word t1) C_noret;
C_noret_decl(f_659)
static void C_fcall f_659(C_word t0,C_word t1) C_noret;
C_noret_decl(f_550)
static void C_fcall f_550(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_523)
static void C_fcall f_523(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;

C_noret_decl(trf_1651)
static void C_fcall trf_1651(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1651(void *dummy){
C_word t4=C_pick(0);
C_word t3=C_pick(1);
C_word t2=C_pick(2);
C_word t1=C_pick(3);
C_word t0=C_pick(4);
C_adjust_stack(-5);
f_1651(t0,t1,t2,t3,t4);}

C_noret_decl(trf_1661)
static void C_fcall trf_1661(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1661(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1661(t0,t1);}

C_noret_decl(trf_1611)
static void C_fcall trf_1611(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1611(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1611(t0,t1,t2);}

C_noret_decl(trf_1624)
static void C_fcall trf_1624(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1624(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1624(t0,t1);}

C_noret_decl(trf_2175)
static void C_fcall trf_2175(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2175(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_2175(t0,t1,t2);}

C_noret_decl(trf_2195)
static void C_fcall trf_2195(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2195(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2195(t0,t1);}

C_noret_decl(trf_2204)
static void C_fcall trf_2204(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2204(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2204(t0,t1);}

C_noret_decl(trf_2220)
static void C_fcall trf_2220(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2220(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2220(t0,t1);}

C_noret_decl(trf_2068)
static void C_fcall trf_2068(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2068(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2068(t0,t1);}

C_noret_decl(trf_2077)
static void C_fcall trf_2077(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2077(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_2077(t0,t1,t2);}

C_noret_decl(trf_2101)
static void C_fcall trf_2101(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2101(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2101(t0,t1);}

C_noret_decl(trf_1926)
static void C_fcall trf_1926(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1926(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1926(t0,t1);}

C_noret_decl(trf_1571)
static void C_fcall trf_1571(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1571(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1571(t0,t1,t2);}

C_noret_decl(trf_1515)
static void C_fcall trf_1515(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1515(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1515(t0,t1,t2);}

C_noret_decl(trf_1435)
static void C_fcall trf_1435(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1435(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1435(t0,t1);}

C_noret_decl(trf_1361)
static void C_fcall trf_1361(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1361(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1361(t0,t1);}

C_noret_decl(trf_1356)
static void C_fcall trf_1356(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1356(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1356(t0,t1,t2);}

C_noret_decl(trf_1244)
static void C_fcall trf_1244(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1244(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_1244(t0,t1,t2,t3);}

C_noret_decl(trf_1315)
static void C_fcall trf_1315(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1315(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1315(t0,t1,t2);}

C_noret_decl(trf_1274)
static void C_fcall trf_1274(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1274(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1274(t0,t1);}

C_noret_decl(trf_1246)
static void C_fcall trf_1246(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1246(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1246(t0,t1);}

C_noret_decl(trf_1220)
static void C_fcall trf_1220(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1220(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1220(t0,t1);}

C_noret_decl(trf_1176)
static void C_fcall trf_1176(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1176(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_1176(t0,t1,t2,t3);}

C_noret_decl(trf_1167)
static void C_fcall trf_1167(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1167(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1167(t0,t1);}

C_noret_decl(trf_1018)
static void C_fcall trf_1018(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1018(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1018(t0,t1);}

C_noret_decl(trf_1013)
static void C_fcall trf_1013(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1013(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1013(t0,t1,t2);}

C_noret_decl(trf_1001)
static void C_fcall trf_1001(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1001(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_1001(t0,t1,t2,t3);}

C_noret_decl(trf_973)
static void C_fcall trf_973(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_973(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_973(t0,t1);}

C_noret_decl(trf_860)
static void C_fcall trf_860(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_860(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_860(t0,t1,t2);}

C_noret_decl(trf_763)
static void C_fcall trf_763(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_763(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_763(t0,t1);}

C_noret_decl(trf_758)
static void C_fcall trf_758(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_758(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_758(t0,t1,t2);}

C_noret_decl(trf_753)
static void C_fcall trf_753(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_753(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_753(t0,t1,t2,t3);}

C_noret_decl(trf_666)
static void C_fcall trf_666(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_666(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_666(t0,t1);}

C_noret_decl(trf_659)
static void C_fcall trf_659(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_659(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_659(t0,t1);}

C_noret_decl(trf_550)
static void C_fcall trf_550(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_550(void *dummy){
C_word t6=C_pick(0);
C_word t5=C_pick(1);
C_word t4=C_pick(2);
C_word t3=C_pick(3);
C_word t2=C_pick(4);
C_word t1=C_pick(5);
C_word t0=C_pick(6);
C_adjust_stack(-7);
f_550(t0,t1,t2,t3,t4,t5,t6);}

C_noret_decl(trf_523)
static void C_fcall trf_523(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_523(void *dummy){
C_word t6=C_pick(0);
C_word t5=C_pick(1);
C_word t4=C_pick(2);
C_word t3=C_pick(3);
C_word t2=C_pick(4);
C_word t1=C_pick(5);
C_word t0=C_pick(6);
C_adjust_stack(-7);
f_523(t0,t1,t2,t3,t4,t5,t6);}

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
if(!C_demand_2(1392)){
C_save(t1);
C_rereclaim2(1392*sizeof(C_word), 1);
t1=C_restore;}
a=C_alloc(3);
C_initialize_lf(lf,220);
lf[1]=C_static_string(C_heaptop,27,"too many optional arguments");
lf[3]=C_static_lambda_info(C_heaptop,40,"(tb:rescale a58 a49 a310 a211 a112 a013)");
lf[5]=C_static_lambda_info(C_heaptop,49,"(tb:discrete a2023 a1924 a1825 a1726 a1627 a1528)");
lf[7]=C_static_lambda_info(C_heaptop,15,"(tb:rani a8386)");
lf[9]=C_static_lambda_info(C_heaptop,15,"(tb:ranf a8790)");
lf[10]=C_h_intern(&lf[10],7,"rescale");
lf[11]=C_static_lambda_info(C_heaptop,45,"(rescale x105 x1106 x2107 y1108 y2109 . b110)");
lf[12]=C_h_intern(&lf[12],8,"discrete");
lf[13]=C_static_lambda_info(C_heaptop,46,"(discrete x111 x1112 x2113 i1114 i2115 . b116)");
lf[14]=C_h_intern(&lf[14],3,"int");
lf[15]=C_static_lambda_info(C_heaptop,10,"(int f117)");
lf[16]=C_h_intern(&lf[16],8,"quantize");
lf[17]=C_static_lambda_info(C_heaptop,26,"(quantize num118 steps119)");
lf[18]=C_h_intern(&lf[18],8,"decimals");
lf[19]=C_static_lambda_info(C_heaptop,27,"(decimals num120 digits121)");
lf[20]=C_h_intern(&lf[20],15,"rhythm->seconds");
lf[21]=C_static_lambda_info(C_heaptop,26,"(body126 tempo132 beat133)");
lf[22]=C_flonum(C_heaptop,0.25);
lf[23]=C_static_lambda_info(C_heaptop,26,"(def-beat129 %tempo124135)");
lf[24]=C_flonum(C_heaptop,60.0);
lf[25]=C_static_lambda_info(C_heaptop,14,"(def-tempo128)");
lf[26]=C_h_intern(&lf[26],9,"\003syserror");
lf[27]=C_static_lambda_info(C_heaptop,36,"(rhythm->seconds beats122 . args123)");
lf[28]=C_h_intern(&lf[28],13,"cents->scaler");
lf[29]=C_static_lambda_info(C_heaptop,24,"(cents->scaler cents142)");
lf[30]=C_h_intern(&lf[30],13,"scaler->cents");
lf[31]=C_static_lambda_info(C_heaptop,22,"(scaler->cents num143)");
lf[32]=C_h_intern(&lf[32],13,"keynum->hertz");
lf[33]=C_static_lambda_info(C_heaptop,20,"(keynum->hertz k144)");
lf[34]=C_h_intern(&lf[34],10,"keynum->pc");
lf[35]=C_static_lambda_info(C_heaptop,17,"(keynum->pc k145)");
lf[36]=C_h_intern(&lf[36],13,"hertz->keynum");
lf[37]=C_static_lambda_info(C_heaptop,21,"(hertz->keynum hz146)");
lf[38]=C_h_intern(&lf[38],7,"interpl");
lf[39]=C_h_intern(&lf[39],5,"error");
lf[40]=C_static_string(C_heaptop,27,"not an x y coordinate list:");
lf[41]=C_static_lambda_info(C_heaptop,15,"(do155 tail157)");
lf[42]=C_h_intern(&lf[42],3,"err");
lf[43]=C_static_string(C_heaptop,27,"not an x y coordinate list:");
lf[44]=C_static_string(C_heaptop,27,"not an x y coordinate list:");
lf[45]=C_static_lambda_info(C_heaptop,34,"(interpl x147 coords148 . base149)");
lf[46]=C_h_intern(&lf[46],6,"interp");
lf[47]=C_static_lambda_info(C_heaptop,23,"(interp x165 . args166)");
lf[48]=C_h_intern(&lf[48],8,"ran-set!");
lf[49]=C_static_lambda_info(C_heaptop,18,"(ran-set! seed167)");
lf[50]=C_h_intern(&lf[50],3,"ran");
lf[51]=C_static_lambda_info(C_heaptop,18,"(ran n168 . n2169)");
lf[52]=C_h_intern(&lf[52],4,"odds");
lf[53]=C_static_lambda_info(C_heaptop,26,"(body174 true180 false181)");
lf[54]=C_static_lambda_info(C_heaptop,26,"(def-false177 %true172183)");
lf[55]=C_static_lambda_info(C_heaptop,13,"(def-true176)");
lf[56]=C_static_lambda_info(C_heaptop,21,"(odds n170 . args171)");
lf[57]=C_h_intern(&lf[57],5,"pickl");
lf[58]=C_static_string(C_heaptop,29,"cannot pick from empty list: ");
lf[59]=C_h_intern(&lf[59],3,"arg");
lf[60]=C_static_lambda_info(C_heaptop,15,"(pickl args189)");
lf[61]=C_h_intern(&lf[61],4,"pick");
lf[62]=C_static_lambda_info(C_heaptop,16,"(pick . args190)");
lf[63]=C_h_intern(&lf[63],13,"print-message");
lf[64]=C_h_intern(&lf[64],17,"\003sysmake-c-string");
lf[65]=C_static_lambda_info(C_heaptop,23,"(print-message a224228)");
lf[66]=C_h_intern(&lf[66],11,"print-error");
lf[67]=C_static_lambda_info(C_heaptop,21,"(print-error a230234)");
lf[68]=C_h_intern(&lf[68],25,"current-time-milliseconds");
lf[69]=C_static_lambda_info(C_heaptop,27,"(current-time-milliseconds)");
lf[70]=C_h_intern(&lf[70],20,"current-time-seconds");
lf[71]=C_static_lambda_info(C_heaptop,22,"(current-time-seconds)");
lf[73]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[74]=C_h_intern(&lf[74],6,"\003sysgc");
lf[75]=C_static_lambda_info(C_heaptop,41,"(scheduler-set-time-milliseconds a260263)");
lf[77]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[78]=C_static_lambda_info(C_heaptop,42,"(scheduler-sprout a268271 a267272 a266273)");
lf[80]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[81]=C_static_lambda_info(C_heaptop,24,"(scheduler-stop a288291)");
lf[82]=C_h_intern(&lf[82],6,"sprout");
lf[83]=C_static_lambda_info(C_heaptop,11,"(nextstart)");
lf[84]=C_static_lambda_info(C_heaptop,8,"(nextid)");
lf[85]=C_static_lambda_info(C_heaptop,12,"(do316 p318)");
lf[86]=C_static_lambda_info(C_heaptop,24,"(body302 start308 id309)");
lf[87]=C_static_lambda_info(C_heaptop,24,"(def-id305 %start300324)");
lf[88]=C_static_lambda_info(C_heaptop,14,"(def-start304)");
lf[89]=C_static_lambda_info(C_heaptop,26,"(sprout proc298 . args299)");
lf[90]=C_h_intern(&lf[90],3,"now");
lf[91]=C_h_intern(&lf[91],11,"time-format");
lf[92]=C_flonum(C_heaptop,1.0);
lf[93]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[94]=C_flonum(C_heaptop,1.0);
lf[95]=C_h_intern(&lf[95],1,"m");
lf[96]=C_static_string(C_heaptop,17,"not a time-format");
lf[97]=C_h_intern(&lf[97],1,"s");
lf[98]=C_static_lambda_info(C_heaptop,22,"(time-format . arg330)");
lf[99]=C_h_intern(&lf[99],5,"pause");
lf[100]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[101]=C_static_lambda_info(C_heaptop,7,"(pause)");
lf[102]=C_h_intern(&lf[102],7,"paused\077");
lf[103]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[104]=C_static_lambda_info(C_heaptop,9,"(paused\077)");
lf[105]=C_h_intern(&lf[105],4,"cont");
lf[106]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[107]=C_static_lambda_info(C_heaptop,6,"(cont)");
lf[108]=C_h_intern(&lf[108],4,"stop");
lf[109]=C_static_string(C_heaptop,17,"Not an integer id");
lf[110]=C_static_lambda_info(C_heaptop,15,"(do344 tail346)");
lf[111]=C_static_lambda_info(C_heaptop,18,"(stop . procid343)");
lf[112]=C_h_intern(&lf[112],4,"hush");
lf[113]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[114]=C_static_lambda_info(C_heaptop,6,"(hush)");
lf[117]=C_h_intern(&lf[117],7,"sprintf");
lf[118]=C_static_lambda_info(C_heaptop,23,"(ferror str357 args358)");
lf[119]=C_h_intern(&lf[119],7,"mp:note");
lf[120]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[121]=C_static_lambda_info(C_heaptop,46,"(mp:note time395 dur396 key397 amp398 chan399)");
lf[122]=C_h_intern(&lf[122],5,"mp:on");
lf[123]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[124]=C_static_lambda_info(C_heaptop,37,"(mp:on time400 key401 vel402 chan403)");
lf[125]=C_h_intern(&lf[125],6,"mp:off");
lf[126]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[127]=C_static_lambda_info(C_heaptop,38,"(mp:off time404 key405 vel406 chan407)");
lf[128]=C_h_intern(&lf[128],7,"mp:prog");
lf[129]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[130]=C_static_lambda_info(C_heaptop,33,"(mp:prog time408 prog409 chan410)");
lf[131]=C_h_intern(&lf[131],7,"mp:ctrl");
lf[132]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[133]=C_static_lambda_info(C_heaptop,40,"(mp:ctrl time411 ctrl412 val413 chan414)");
lf[134]=C_h_intern(&lf[134],9,"mp:alloff");
lf[135]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[136]=C_static_lambda_info(C_heaptop,11,"(mp:alloff)");
lf[137]=C_h_intern(&lf[137],8,"mp:micro");
lf[138]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[139]=C_static_lambda_info(C_heaptop,18,"(mp:micro divs415)");
lf[140]=C_h_intern(&lf[140],9,"mp:inhook");
lf[141]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[142]=C_static_lambda_info(C_heaptop,19,"(mp:inhook func416)");
lf[143]=C_h_intern(&lf[143],14,"return-to-host");
lf[144]=C_h_intern(&lf[144],4,"else");
lf[145]=C_h_intern(&lf[145],4,"cond");
lf[146]=C_h_intern(&lf[146],6,"lambda");
lf[147]=C_h_intern(&lf[147],7,"elapsed");
lf[148]=C_h_intern(&lf[148],1,"x");
lf[149]=C_h_intern(&lf[149],4,"set!");
lf[150]=C_h_intern(&lf[150],4,"wait");
lf[151]=C_h_intern(&lf[151],4,"let*");
lf[152]=C_h_intern(&lf[152],5,"quote");
lf[153]=C_h_intern(&lf[153],3,"exn");
lf[154]=C_h_intern(&lf[154],7,"message");
lf[155]=C_h_intern(&lf[155],27,"condition-property-accessor");
lf[156]=C_h_intern(&lf[156],6,"printf");
lf[157]=C_static_string(C_heaptop,47,">>> Aborting process at time ~S:~%    Error: ~S");
lf[158]=C_h_intern(&lf[158],22,"with-exception-handler");
lf[159]=C_h_intern(&lf[159],30,"call-with-current-continuation");
lf[160]=C_h_intern(&lf[160],10,"\003sysappend");
lf[161]=C_h_intern(&lf[161],6,"safety");
lf[162]=C_h_intern(&lf[162],4,"cdar");
lf[163]=C_static_string(C_heaptop,19,"unknown declaration");
lf[164]=C_h_intern(&lf[164],4,"caar");
lf[165]=C_static_string(C_heaptop,31,"declaration not list (decl val)");
lf[166]=C_static_lambda_info(C_heaptop,15,"(do442 decl444)");
lf[167]=C_h_intern(&lf[167],7,"declare");
lf[168]=C_h_intern(&lf[168],6,"gensym");
lf[169]=C_h_intern(&lf[169],6,"append");
lf[170]=C_h_intern(&lf[170],5,"\000null");
lf[171]=C_static_string(C_heaptop,41,"binding clause not list (var init [step])");
lf[172]=C_static_lambda_info(C_heaptop,15,"(do426 tail428)");
lf[173]=C_static_string(C_heaptop,36,"go stopping clause missing test form");
lf[174]=C_static_string(C_heaptop,29,"go stopping clause not a list");
lf[175]=C_static_string(C_heaptop,22,"go bindings not a list");
lf[176]=C_static_lambda_info(C_heaptop,42,"(a2339 bindings417 terminate418 . body419)");
lf[177]=C_h_intern(&lf[177],18,"\003sysregister-macro");
lf[178]=C_h_intern(&lf[178],2,"go");
lf[179]=C_h_intern(&lf[179],15,"hash-table-set!");
lf[180]=C_static_string(C_heaptop,9,"mp:inhook");
tmp=C_intern(C_heaptop,9,"mp:inhook");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000func");
C_save(tmp);
tmp=C_SCHEME_FALSE;
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[181]=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
lf[182]=C_static_string(C_heaptop,8,"mp:micro");
tmp=C_intern(C_heaptop,8,"mp:micro");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000divs");
C_save(tmp);
tmp=C_fix(1);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[183]=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
lf[184]=C_static_string(C_heaptop,9,"mp:alloff");
tmp=C_intern(C_heaptop,9,"mp:alloff");
C_save(tmp);
tmp=C_SCHEME_END_OF_LIST;
lf[185]=C_h_pair(C_restore,tmp);
lf[186]=C_static_string(C_heaptop,7,"mp:ctrl");
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
lf[187]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[188]=C_static_string(C_heaptop,7,"mp:prog");
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
lf[189]=C_h_list(4,C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(4);
lf[190]=C_static_string(C_heaptop,6,"mp:off");
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
lf[191]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[192]=C_static_string(C_heaptop,5,"mp:on");
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
lf[193]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[194]=C_static_string(C_heaptop,7,"mp:note");
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
lf[195]=C_h_list(6,C_pick(5),C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(6);
lf[196]=C_static_lambda_info(C_heaptop,15,"(do386 tail388)");
lf[197]=C_static_string(C_heaptop,37,"~S found duplicate keyword \047~S\047 in ~S");
lf[198]=C_static_string(C_heaptop,33,"~S missing value for keyword \047~S\047");
lf[199]=C_static_string(C_heaptop,53,"~S found invalid keyword \047~S\047~%Available keywords: ~S");
lf[200]=C_h_intern(&lf[200],7,"\003sysmap");
lf[201]=C_h_intern(&lf[201],3,"car");
lf[202]=C_static_string(C_heaptop,32,"~S expected keyword but got \047~S\047");
lf[203]=C_h_intern(&lf[203],8,"keyword\077");
lf[204]=C_static_string(C_heaptop,35,"~S expected ~A arguments but got ~A");
lf[205]=C_static_lambda_info(C_heaptop,28,"(do369 key371 arg372 pos373)");
lf[206]=C_static_string(C_heaptop,24,"~S is an invalid message");
lf[207]=C_static_lambda_info(C_heaptop,7,"(a1797)");
lf[208]=C_h_intern(&lf[208],14,"hash-table-ref");
lf[209]=C_h_intern(&lf[209],14,"symbol->string");
lf[210]=C_static_lambda_info(C_heaptop,25,"(a2345 mess393 . data394)");
lf[211]=C_h_intern(&lf[211],4,"send");
lf[212]=C_h_intern(&lf[212],10,"*messages*");
lf[213]=C_h_intern(&lf[213],14,"string->symbol");
lf[214]=C_static_string(C_heaptop,51,"message function not string, symbol or list of both");
lf[215]=C_static_lambda_info(C_heaptop,23,"(a2351 func351 info352)");
lf[216]=C_h_intern(&lf[216],19,"define-send-message");
lf[217]=C_h_intern(&lf[217],15,"make-hash-table");
lf[218]=C_h_intern(&lf[218],6,"equal\077");
lf[219]=C_static_lambda_info(C_heaptop,10,"(toplevel)");
C_register_lf2(lf,220,create_ptable());
t2=C_mutate(&lf[0],lf[1]);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_512,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_library_toplevel(2,C_SCHEME_UNDEFINED,t3);}

/* k510 */
static void C_ccall f_512(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_512,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_515,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_eval_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k513 in k510 */
static void C_ccall f_515(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_515,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_518,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k516 in k513 in k510 */
static void C_ccall f_518(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_518,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_521,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k519 in k516 in k513 in k510 */
static void C_ccall f_521(C_word c,C_word t0,C_word t1){
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
C_word ab[111],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_521,2,t0,t1);}
t2=C_mutate(&lf[2],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_523,a[2]=lf[3],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate(&lf[4],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_550,a[2]=lf[5],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate(&lf[6],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_659,a[2]=lf[7],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate(&lf[8],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_666,a[2]=lf[9],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[10]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_695,a[2]=lf[11],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate((C_word*)lf[12]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_714,a[2]=lf[13],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate((C_word*)lf[14]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_733,a[2]=lf[15],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate((C_word*)lf[16]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_739,a[2]=lf[17],tmp=(C_word)a,a+=3,tmp));
t10=C_mutate((C_word*)lf[18]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_745,a[2]=lf[19],tmp=(C_word)a,a+=3,tmp));
t11=C_mutate((C_word*)lf[20]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_751,a[2]=lf[27],tmp=(C_word)a,a+=3,tmp));
t12=C_mutate((C_word*)lf[28]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_811,a[2]=lf[29],tmp=(C_word)a,a+=3,tmp));
t13=C_mutate((C_word*)lf[30]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_817,a[2]=lf[31],tmp=(C_word)a,a+=3,tmp));
t14=C_mutate((C_word*)lf[32]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_823,a[2]=lf[33],tmp=(C_word)a,a+=3,tmp));
t15=C_mutate((C_word*)lf[34]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_829,a[2]=lf[35],tmp=(C_word)a,a+=3,tmp));
t16=C_mutate((C_word*)lf[36]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_835,a[2]=lf[37],tmp=(C_word)a,a+=3,tmp));
t17=C_mutate((C_word*)lf[38]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_841,a[2]=lf[45],tmp=(C_word)a,a+=3,tmp));
t18=C_mutate((C_word*)lf[46]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_936,a[2]=lf[47],tmp=(C_word)a,a+=3,tmp));
t19=C_mutate((C_word*)lf[48]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_942,a[2]=lf[49],tmp=(C_word)a,a+=3,tmp));
t20=C_mutate((C_word*)lf[50]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_948,a[2]=lf[51],tmp=(C_word)a,a+=3,tmp));
t21=C_mutate((C_word*)lf[52]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_999,a[2]=lf[56],tmp=(C_word)a,a+=3,tmp));
t22=C_mutate((C_word*)lf[57]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1066,a[2]=lf[60],tmp=(C_word)a,a+=3,tmp));
t23=C_mutate((C_word*)lf[61]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1089,a[2]=lf[62],tmp=(C_word)a,a+=3,tmp));
t24=C_mutate((C_word*)lf[63]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1095,a[2]=lf[65],tmp=(C_word)a,a+=3,tmp));
t25=C_mutate((C_word*)lf[66]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1109,a[2]=lf[67],tmp=(C_word)a,a+=3,tmp));
t26=C_mutate((C_word*)lf[68]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1152,a[2]=lf[69],tmp=(C_word)a,a+=3,tmp));
t27=C_mutate((C_word*)lf[70]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1155,a[2]=lf[71],tmp=(C_word)a,a+=3,tmp));
t28=C_mutate(&lf[72],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1167,a[2]=lf[75],tmp=(C_word)a,a+=3,tmp));
t29=C_mutate(&lf[76],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1176,a[2]=lf[78],tmp=(C_word)a,a+=3,tmp));
t30=C_mutate(&lf[79],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1220,a[2]=lf[81],tmp=(C_word)a,a+=3,tmp));
t31=C_mutate((C_word*)lf[82]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1242,a[2]=lf[89],tmp=(C_word)a,a+=3,tmp));
t32=C_mutate((C_word*)lf[90]+1,*((C_word*)lf[68]+1));
t33=C_mutate((C_word*)lf[91]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1410,a[2]=lf[98],tmp=(C_word)a,a+=3,tmp));
t34=C_mutate((C_word*)lf[99]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1473,a[2]=lf[101],tmp=(C_word)a,a+=3,tmp));
t35=C_mutate((C_word*)lf[102]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1482,a[2]=lf[104],tmp=(C_word)a,a+=3,tmp));
t36=C_mutate((C_word*)lf[105]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1488,a[2]=lf[107],tmp=(C_word)a,a+=3,tmp));
t37=C_mutate((C_word*)lf[108]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1497,a[2]=lf[111],tmp=(C_word)a,a+=3,tmp));
t38=C_mutate((C_word*)lf[112]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1555,a[2]=lf[114],tmp=(C_word)a,a+=3,tmp));
t39=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1566,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 266  make-hash-table");
t40=C_retrieve(lf[217]);
((C_proc3)C_retrieve_proc(t40))(3,t40,t39,*((C_word*)lf[218]+1));}

/* k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1566(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1566,2,t0,t1);}
t2=C_mutate(&lf[115],t1);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1569,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2352,a[2]=lf[215],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 268  ##sys#register-macro");
t5=C_retrieve(lf[177]);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,lf[216],t4);}

/* a2351 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_2352(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_2352,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_2356,a[2]=t6,a[3]=t1,a[4]=t3,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t4)[1]))){
t8=(C_word)C_i_car(((C_word*)t4)[1]);
t9=C_set_block_item(t6,0,t8);
t10=(C_word)C_i_cadr(((C_word*)t4)[1]);
t11=C_set_block_item(t4,0,t10);
t12=t7;
f_2356(2,t12,t11);}
else{
if(C_truep((C_word)C_i_stringp(((C_word*)t4)[1]))){
t8=C_set_block_item(t6,0,((C_word*)t4)[1]);
t9=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2389,a[2]=t7,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 275  string->symbol");
t10=*((C_word*)lf[213]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)t4)[1]);}
else{
if(C_truep((C_word)C_i_symbolp(((C_word*)t4)[1]))){
t8=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2399,a[2]=t7,a[3]=t6,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 277  symbol->string");
t9=*((C_word*)lf[209]+1);
((C_proc3)C_retrieve_proc(t9))(3,t9,t8,((C_word*)t4)[1]);}
else{
C_trace("ChickenBridge.scm: 279  error");
t8=*((C_word*)lf[39]+1);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,lf[214]);}}}}

/* k2397 in a2351 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_2399(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_2356(2,t3,t2);}

/* k2387 in a2351 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_2389(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_2356(2,t3,t2);}

/* k2354 in a2351 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_2356(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2356,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[4]);
t3=(C_word)C_a_i_list(&a,2,lf[152],t2);
t4=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_a_i_list(&a,4,lf[179],lf[212],((C_word*)((C_word*)t0)[2])[1],t3));}

/* k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1569(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1569,2,t0,t1);}
t2=C_mutate(&lf[116],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1571,a[2]=lf[118],tmp=(C_word)a,a+=3,tmp));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1808,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2346,a[2]=lf[210],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 355  ##sys#register-macro");
t5=C_retrieve(lf[177]);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,lf[211],t4);}

/* a2345 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_2346(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+6)){
C_save_and_reclaim((void*)tr3r,(void*)f_2346r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_2346r(t0,t1,t2,t3);}}

static void C_ccall f_2346r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a=C_alloc(6);
t4=t3;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1585,a[2]=t1,a[3]=t5,tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_symbolp(t2))){
C_trace("ChickenBridge.scm: 286  symbol->string");
t7=*((C_word*)lf[209]+1);
((C_proc3)C_retrieve_proc(t7))(3,t7,t6,t2);}
else{
t7=t6;
f_1585(2,t7,t2);}}

/* k1583 in a2345 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1585(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1585,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1588,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1798,a[2]=lf[207],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 287  hash-table-ref");
t4=*((C_word*)lf[208]+1);
((C_proc5)C_retrieve_proc(t4))(5,t4,t2,lf[115],t1,t3);}

/* a1797 in k1583 in a2345 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1798(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1798,2,t0,t1);}
t2=t1;
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}

/* k1586 in k1583 in a2345 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1588(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1588,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_1591,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=t1;
if(C_truep(t3)){
t4=t2;
f_1591(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 288  ferror");
f_1571(t2,lf[206],(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]));}}

/* k1589 in k1586 in k1583 in a2345 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1591(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_1591,2,t0,t1);}
t2=((C_word*)((C_word*)t0)[5])[1];
t3=(C_word)C_i_car(((C_word*)t0)[4]);
t4=(C_word)C_i_cdr(((C_word*)t0)[4]);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(C_word)C_i_length(t4);
t8=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_1603,a[2]=t7,a[3]=t2,a[4]=((C_word*)t0)[2],a[5]=t6,a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[3],a[8]=t4,a[9]=t3,tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 295  append");
t9=*((C_word*)lf[169]+1);
((C_proc4)C_retrieve_proc(t9))(4,t9,t8,t4,C_SCHEME_END_OF_LIST);}

/* k1601 in k1589 in k1586 in k1583 in a2345 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1603(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[19],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1603,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_1606,a[2]=((C_word*)t0)[7],a[3]=((C_word*)t0)[8],a[4]=t1,a[5]=((C_word*)t0)[9],tmp=(C_word)a,a+=6,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_1651,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[5],a[8]=t4,a[9]=((C_word*)t0)[6],a[10]=lf[205],tmp=(C_word)a,a+=11,tmp));
t6=((C_word*)t4)[1];
f_1651(t6,t2,C_SCHEME_FALSE,C_SCHEME_FALSE,C_fix(0));}

/* do369 in k1601 in k1589 in k1586 in k1583 in a2345 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_fcall f_1651(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
C_save_and_reclaim((void*)trf_1651,NULL,5,t0,t1,t2,t3,t4);}
t5=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[9])[1]))){
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,C_SCHEME_FALSE);}
else{
t8=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_1661,a[2]=t7,a[3]=t6,a[4]=t5,a[5]=t1,a[6]=((C_word*)t0)[8],tmp=(C_word)a,a+=7,tmp);
t9=(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_1667,a[2]=((C_word*)t0)[2],a[3]=t7,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=t6,a[8]=((C_word*)t0)[6],a[9]=t5,a[10]=((C_word*)t0)[9],a[11]=t8,a[12]=((C_word*)t0)[7],tmp=(C_word)a,a+=13,tmp);
t10=((C_word*)((C_word*)t0)[7])[1];
if(C_truep(t10)){
t11=t9;
f_1667(2,t11,C_SCHEME_FALSE);}
else{
t11=(C_word)C_i_car(((C_word*)((C_word*)t0)[9])[1]);
C_trace("ChickenBridge.scm: 306  keyword?");
t12=C_retrieve(lf[203]);
((C_proc3)C_retrieve_proc(t12))(3,t12,t9,t11);}}}

/* k1665 in do369 in k1601 in k1589 in k1586 in k1583 in a2345 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1667(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_1667,2,t0,t1);}
if(C_truep(t1)){
t2=C_set_block_item(((C_word*)t0)[12],0,C_SCHEME_TRUE);
t3=((C_word*)t0)[11];
f_1661(t3,t2);}
else{
t2=((C_word*)((C_word*)t0)[12])[1];
if(C_truep(t2)){
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[10])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[9])+1,t3);
t5=(C_word)C_i_assoc(((C_word*)((C_word*)t0)[9])[1],((C_word*)t0)[8]);
t6=C_mutate(((C_word *)((C_word*)t0)[7])+1,t5);
t7=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[10])[1]);
t8=C_mutate(((C_word *)((C_word*)t0)[10])+1,t7);
t9=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_1721,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[9],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[11],a[6]=((C_word*)t0)[10],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t10=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_1776,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[9],a[5]=((C_word*)t0)[5],a[6]=t9,a[7]=((C_word*)t0)[10],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 326  keyword?");
t11=C_retrieve(lf[203]);
((C_proc3)C_retrieve_proc(t11))(3,t11,t10,((C_word*)((C_word*)t0)[9])[1]);}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_1677,a[2]=((C_word*)t0)[11],a[3]=((C_word*)t0)[10],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[6],tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_nequalp(((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]))){
t4=(C_word)C_i_length(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 316  ferror");
f_1571(t3,lf[204],(C_word)C_a_i_list(&a,3,((C_word*)t0)[5],((C_word*)t0)[2],t4));}
else{
t4=t3;
f_1677(2,t4,C_SCHEME_UNDEFINED);}}}}

/* k1675 in k1665 in do369 in k1601 in k1589 in k1586 in k1583 in a2345 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1677(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_1677,2,t0,t1);}
t2=(C_word)C_i_list_tail(((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]);
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
t4=(C_word)C_i_set_car(t2,t3);
t5=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[3])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t5);
t7=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[4])[1],C_fix(1));
t8=C_mutate(((C_word *)((C_word*)t0)[4])+1,t7);
t9=((C_word*)t0)[2];
f_1661(t9,t8);}

/* k1774 in k1665 in do369 in k1601 in k1589 in k1586 in k1583 in a2345 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1776(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1776,2,t0,t1);}
if(C_truep(t1)){
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[7])[1]))){
C_trace("ChickenBridge.scm: 330  ferror");
f_1571(((C_word*)t0)[6],lf[198],(C_word)C_a_i_list(&a,2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]));}
else{
t2=((C_word*)((C_word*)t0)[3])[1];
if(C_truep(t2)){
t3=((C_word*)t0)[6];
f_1721(2,t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1772,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
C_trace("map");
t4=*((C_word*)lf[200]+1);
((C_proc4)(void*)(*((C_word*)t4+1)))(4,t4,t3,*((C_word*)lf[201]+1),((C_word*)t0)[2]);}}}
else{
C_trace("ChickenBridge.scm: 327  ferror");
f_1571(((C_word*)t0)[6],lf[202],(C_word)C_a_i_list(&a,2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]));}}

/* k1770 in k1774 in k1665 in do369 in k1601 in k1589 in k1586 in k1583 in a2345 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1772(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1772,2,t0,t1);}
C_trace("ChickenBridge.scm: 333  ferror");
f_1571(((C_word*)t0)[4],lf[199],(C_word)C_a_i_list(&a,3,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1));}

/* k1719 in k1665 in do369 in k1601 in k1589 in k1586 in k1583 in a2345 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1721(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[14],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1721,2,t0,t1);}
t2=(C_word)C_i_member(((C_word*)((C_word*)t0)[8])[1],((C_word*)t0)[7]);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1727,a[2]=((C_word*)t0)[5],a[3]=t2,a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
if(C_truep(t2)){
t4=t3;
f_1727(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 340  ferror");
f_1571(t3,lf[197],(C_word)C_a_i_list(&a,3,((C_word*)t0)[4],((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]));}}

/* k1725 in k1719 in k1665 in do369 in k1601 in k1589 in k1586 in k1583 in a2345 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1727(C_word c,C_word t0,C_word t1){
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
f_1661(t6,t5);}

/* k1659 in do369 in k1601 in k1589 in k1586 in k1583 in a2345 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_fcall f_1661(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[6])[1];
f_1651(t2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k1604 in k1601 in k1589 in k1586 in k1583 in a2345 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1606(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1606,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_1611,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=lf[196],tmp=(C_word)a,a+=7,tmp));
t5=((C_word*)t3)[1];
f_1611(t5,((C_word*)t0)[2],((C_word*)t0)[4]);}

/* do386 in k1604 in k1601 in k1589 in k1586 in k1583 in a2345 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_fcall f_1611(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1611,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[5],((C_word*)t0)[4]));}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1624,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_member(t4,((C_word*)t0)[2]))){
t5=(C_word)C_i_car(t2);
t6=(C_word)C_i_cadr(t5);
t7=t3;
f_1624(t7,(C_word)C_i_set_car(t2,t6));}
else{
t5=t3;
f_1624(t5,C_SCHEME_UNDEFINED);}}}

/* k1622 in do386 in k1604 in k1601 in k1589 in k1586 in k1583 in a2345 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_fcall f_1624(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_1611(t3,((C_word*)t0)[2],t2);}

/* k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1808(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_1808,2,t0,t1);}
t2=C_mutate((C_word*)lf[119]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1810,a[2]=lf[121],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[122]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1816,a[2]=lf[124],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate((C_word*)lf[125]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1822,a[2]=lf[127],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate((C_word*)lf[128]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1828,a[2]=lf[130],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[131]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1834,a[2]=lf[133],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate((C_word*)lf[134]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1840,a[2]=lf[136],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate((C_word*)lf[137]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1846,a[2]=lf[139],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate((C_word*)lf[140]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1852,a[2]=lf[142],tmp=(C_word)a,a+=3,tmp));
t10=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1859,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 382  hash-table-set!");
t11=C_retrieve(lf[179]);
((C_proc5)C_retrieve_proc(t11))(5,t11,t10,lf[115],lf[194],lf[195]);}

/* k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1859(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1859,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1862,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 383  hash-table-set!");
t3=C_retrieve(lf[179]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[115],lf[192],lf[193]);}

/* k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1862(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1862,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1865,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 384  hash-table-set!");
t3=C_retrieve(lf[179]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[115],lf[190],lf[191]);}

/* k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1865(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1865,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1868,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 385  hash-table-set!");
t3=C_retrieve(lf[179]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[115],lf[188],lf[189]);}

/* k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1868(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1868,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1871,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 386  hash-table-set!");
t3=C_retrieve(lf[179]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[115],lf[186],lf[187]);}

/* k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1871(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1871,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1874,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 387  hash-table-set!");
t3=C_retrieve(lf[179]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[115],lf[184],lf[185]);}

/* k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1874(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1874,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1877,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 388  hash-table-set!");
t3=C_retrieve(lf[179]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[115],lf[182],lf[183]);}

/* k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1877(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1877,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1880,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 389  hash-table-set!");
t3=C_retrieve(lf[179]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[115],lf[180],lf[181]);}

/* k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1880(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1880,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1883,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2340,a[2]=lf[176],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 396  ##sys#register-macro");
t4=C_retrieve(lf[177]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,lf[178],t3);}

/* a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_2340(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+17)){
C_save_and_reclaim((void*)tr4r,(void*)f_2340r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest(a,C_rest_count(0));
f_2340r(t0,t1,t2,t3,t4);}}

static void C_ccall f_2340r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
t13=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_1898,a[2]=t2,a[3]=t12,a[4]=t6,a[5]=t10,a[6]=t1,a[7]=t8,a[8]=t3,tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(t2))){
t14=t13;
f_1898(2,t14,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 405  error");
t14=*((C_word*)lf[39]+1);
((C_proc4)C_retrieve_proc(t14))(4,t14,t13,lf[175],t2);}}

/* k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1898(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1898,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_1901,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(((C_word*)t0)[8]))){
if(C_truep((C_word)C_i_nullp(((C_word*)t0)[8]))){
C_trace("ChickenBridge.scm: 409  error");
t3=*((C_word*)lf[39]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,lf[173]);}
else{
t3=t2;
f_1901(2,t3,C_SCHEME_UNDEFINED);}}
else{
C_trace("ChickenBridge.scm: 407  error");
t3=*((C_word*)lf[39]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t2,lf[174],((C_word*)t0)[8]);}}

/* k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1901(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1901,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_1904,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],tmp=(C_word)a,a+=8,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_2175,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[7],a[5]=t4,a[6]=lf[172],tmp=(C_word)a,a+=7,tmp));
t6=((C_word*)t4)[1];
f_2175(t6,t2,((C_word*)t0)[2]);}

/* do426 in k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_fcall f_2175(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_2175,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2185,a[2]=t1,a[3]=((C_word*)t0)[5],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_2195,a[2]=t3,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=t2,tmp=(C_word)a,a+=7,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2283,a[2]=t4,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t7=(C_word)C_i_car(t2);
t8=(C_word)C_i_length(t7);
C_trace("ChickenBridge.scm: 413  <");
C_lessp(5,0,t6,C_fix(0),t8,C_fix(4));}
else{
t6=t4;
f_2195(t6,C_SCHEME_FALSE);}}}

/* k2281 in do426 in k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_2283(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=(C_word)C_i_car(t2);
t4=((C_word*)t0)[2];
f_2195(t4,(C_word)C_i_symbolp(t3));}
else{
t2=((C_word*)t0)[2];
f_2195(t2,C_SCHEME_FALSE);}}

/* k2193 in do426 in k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_fcall f_2195(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_2195,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[6]);
t3=(C_word)C_i_car(t2);
t4=(C_word)C_i_car(((C_word*)t0)[6]);
t5=(C_word)C_i_cadr(t4);
t6=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_2204,a[2]=t5,a[3]=t3,a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[5],tmp=(C_word)a,a+=8,tmp);
t7=(C_word)C_i_car(((C_word*)t0)[6]);
t8=(C_word)C_i_cddr(t7);
if(C_truep((C_word)C_i_nullp(t8))){
t9=t6;
f_2204(t9,lf[170]);}
else{
t9=(C_word)C_i_car(((C_word*)t0)[6]);
t10=t6;
f_2204(t10,(C_word)C_i_caddr(t9));}}
else{
t2=(C_word)C_i_car(((C_word*)t0)[6]);
C_trace("ChickenBridge.scm: 426  error");
t3=*((C_word*)lf[39]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[2],lf[171],t2);}}

/* k2202 in k2193 in do426 in k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_fcall f_2204(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2204,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_2208,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t3=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 421  append");
t4=*((C_word*)lf[169]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,((C_word*)((C_word*)t0)[7])[1],t3);}

/* k2206 in k2202 in k2193 in do426 in k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_2208(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2208,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_2212,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
t4=(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 422  append");
t5=*((C_word*)lf[169]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,((C_word*)((C_word*)t0)[7])[1],t4);}

/* k2210 in k2206 in k2202 in k2193 in do426 in k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_2212(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2212,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2216,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2220,a[2]=((C_word*)t0)[5],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_eqp(((C_word*)t0)[3],lf[170]);
if(C_truep(t5)){
t6=t4;
f_2220(t6,C_SCHEME_END_OF_LIST);}
else{
t6=(C_word)C_a_i_list(&a,3,lf[149],((C_word*)t0)[2],((C_word*)t0)[3]);
t7=t4;
f_2220(t7,(C_word)C_a_i_list(&a,1,t6));}}

/* k2218 in k2210 in k2206 in k2202 in k2193 in do426 in k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_fcall f_2220(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 423  append");
t2=*((C_word*)lf[169]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k2214 in k2210 in k2206 in k2202 in k2193 in do426 in k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_2216(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_2185(2,t3,t2);}

/* k2183 in do426 in k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_2185(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_2175(t3,((C_word*)t0)[2],t2);}

/* k1902 in k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1904(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1904,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_1907,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 428  gensym");
t3=C_retrieve(lf[168]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k1905 in k1902 in k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1907(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1907,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_1910,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 429  gensym");
t3=C_retrieve(lf[168]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k1908 in k1905 in k1902 in k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1910(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1910,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_1913,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 430  gensym");
t3=C_retrieve(lf[168]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k1911 in k1908 in k1905 in k1902 in k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1913(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1913,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_1916,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],a[10]=((C_word*)t0)[9],tmp=(C_word)a,a+=11,tmp);
C_trace("ChickenBridge.scm: 431  gensym");
t3=C_retrieve(lf[168]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k1914 in k1911 in k1908 in k1905 in k1902 in k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1916(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_1916,2,t0,t1);}
t2=C_SCHEME_TRUE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_SCHEME_END_OF_LIST;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_1919,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=t3,a[7]=((C_word*)t0)[5],a[8]=((C_word*)t0)[6],a[9]=((C_word*)t0)[7],a[10]=((C_word*)t0)[8],a[11]=((C_word*)t0)[9],a[12]=t5,a[13]=((C_word*)t0)[10],tmp=(C_word)a,a+=14,tmp);
t7=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2068,a[2]=t6,a[3]=t3,a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)((C_word*)t0)[3])[1]))){
t8=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
if(C_truep((C_word)C_i_pairp(t8))){
t9=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2169,a[2]=t7,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 437  caar");
t10=*((C_word*)lf[164]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)((C_word*)t0)[3])[1]);}
else{
t9=t7;
f_2068(t9,C_SCHEME_FALSE);}}
else{
t8=t7;
f_2068(t8,C_SCHEME_FALSE);}}

/* k2167 in k1914 in k1911 in k1908 in k1905 in k1902 in k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_2169(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_2068(t2,(C_word)C_eqp(t1,lf[167]));}

/* k2066 in k1914 in k1911 in k1908 in k1905 in k1902 in k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_fcall f_2068(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2068,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2075,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 438  cdar");
t3=*((C_word*)lf[162]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)((C_word*)t0)[4])[1]);}
else{
t2=((C_word*)t0)[2];
f_1919(2,t2,C_SCHEME_UNDEFINED);}}

/* k2073 in k2066 in k1914 in k1911 in k1908 in k1905 in k1902 in k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_2075(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2075,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_2077,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=lf[166],tmp=(C_word)a,a+=6,tmp));
t5=((C_word*)t3)[1];
f_2077(t5,((C_word*)t0)[2],t1);}

/* do442 in k2073 in k2066 in k1914 in k1911 in k1908 in k1905 in k1902 in k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_fcall f_2077(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_2077,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[4])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[4])+1,t3);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,t4);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2091,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2101,a[2]=t2,a[3]=((C_word*)t0)[2],a[4]=t3,tmp=(C_word)a,a+=5,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2149,a[2]=t4,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 442  cdar");
t7=*((C_word*)lf[162]+1);
((C_proc3)C_retrieve_proc(t7))(3,t7,t6,t2);}
else{
t6=t4;
f_2101(t6,C_SCHEME_FALSE);}}}

/* k2147 in do442 in k2073 in k2066 in k1914 in k1911 in k1908 in k1905 in k1902 in k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_2149(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_2101(t2,(C_word)C_i_pairp(t1));}

/* k2099 in do442 in k2073 in k2066 in k1914 in k1911 in k1908 in k1905 in k1902 in k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_fcall f_2101(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2101,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2104,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 443  caar");
t3=*((C_word*)lf[164]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)t0)[2]);}
else{
t2=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 449  error");
t3=*((C_word*)lf[39]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[4],lf[165],t2);}}

/* k2102 in k2099 in do442 in k2073 in k2066 in k1914 in k1911 in k1908 in k1905 in k1902 in k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_2104(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2104,2,t0,t1);}
t2=(C_word)C_eqp(t1,lf[161]);
if(C_truep(t2)){
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2125,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 445  cdar");
t4=*((C_word*)lf[162]+1);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)t0)[2]);}
else{
t3=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 448  error");
t4=*((C_word*)lf[39]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,((C_word*)t0)[4],lf[163],t3);}}

/* k2123 in k2102 in k2099 in do442 in k2073 in k2066 in k1914 in k1911 in k1908 in k1905 in k1902 in k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_2125(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep((C_word)C_i_car(t1))){
t2=((C_word*)t0)[3];
f_2091(2,t2,C_SCHEME_UNDEFINED);}
else{
t2=C_set_block_item(((C_word*)t0)[2],0,C_SCHEME_FALSE);
t3=((C_word*)t0)[3];
f_2091(2,t3,t2);}}

/* k2089 in do442 in k2073 in k2066 in k1914 in k1911 in k1908 in k1905 in k1902 in k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_2091(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_2077(t3,((C_word*)t0)[2],t2);}

/* k1917 in k1914 in k1911 in k1908 in k1905 in k1902 in k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1919(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1919,2,t0,t1);}
t2=(C_word)C_i_car(((C_word*)t0)[13]);
t3=(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_2057,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],a[10]=((C_word*)t0)[10],a[11]=((C_word*)t0)[11],a[12]=((C_word*)t0)[12],a[13]=t2,tmp=(C_word)a,a+=14,tmp);
t4=(C_word)C_i_cdr(((C_word*)t0)[13]);
t5=(C_word)C_a_i_list(&a,1,C_fix(-1));
C_trace("ChickenBridge.scm: 400  ##sys#append");
t6=*((C_word*)lf[160]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t3,t4,t5);}

/* k2055 in k1917 in k1914 in k1911 in k1908 in k1905 in k1902 in k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_2057(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2057,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[13],t1);
t3=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_2041,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],a[8]=((C_word*)t0)[10],a[9]=((C_word*)t0)[11],a[10]=((C_word*)t0)[12],a[11]=t2,tmp=(C_word)a,a+=12,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2045,a[2]=((C_word*)t0)[3],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_a_i_list(&a,1,((C_word*)t0)[10]);
C_trace("ChickenBridge.scm: 400  ##sys#append");
t6=*((C_word*)lf[160]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t4,((C_word*)((C_word*)t0)[2])[1],t5);}

/* k2043 in k2055 in k1917 in k1914 in k1911 in k1908 in k1905 in k1902 in k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_2045(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 400  ##sys#append");
t2=*((C_word*)lf[160]+1);
((C_proc4)(void*)(*((C_word*)t2+1)))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k2039 in k2055 in k1917 in k1914 in k1911 in k1908 in k1905 in k1902 in k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_2041(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2041,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,lf[144],t1);
t3=(C_word)C_a_i_list(&a,3,lf[145],((C_word*)t0)[11],t2);
t4=C_mutate(((C_word *)((C_word*)t0)[10])+1,t3);
t5=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_1926,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],a[5]=((C_word*)t0)[10],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],tmp=(C_word)a,a+=8,tmp);
if(C_truep(((C_word*)((C_word*)t0)[4])[1])){
t6=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
t7=(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]);
t8=(C_word)C_a_i_list(&a,2,lf[152],lf[153]);
t9=(C_word)C_a_i_list(&a,2,lf[152],lf[154]);
t10=(C_word)C_a_i_list(&a,3,lf[155],t8,t9);
t11=(C_word)C_a_i_list(&a,2,t10,((C_word*)t0)[2]);
t12=(C_word)C_a_i_list(&a,4,lf[156],lf[157],((C_word*)t0)[9],t11);
t13=(C_word)C_a_i_list(&a,2,((C_word*)t0)[3],C_fix(-2));
t14=(C_word)C_a_i_list(&a,4,lf[146],t7,t12,t13);
t15=(C_word)C_a_i_list(&a,3,lf[146],C_SCHEME_END_OF_LIST,((C_word*)((C_word*)t0)[10])[1]);
t16=(C_word)C_a_i_list(&a,3,lf[158],t14,t15);
t17=(C_word)C_a_i_list(&a,3,lf[146],t6,t16);
t18=(C_word)C_a_i_list(&a,2,lf[159],t17);
t19=C_mutate(((C_word *)((C_word*)t0)[10])+1,t18);
t20=t5;
f_1926(t20,t19);}
else{
t6=t5;
f_1926(t6,C_SCHEME_UNDEFINED);}}

/* k1924 in k2039 in k2055 in k1917 in k1914 in k1911 in k1908 in k1905 in k1902 in k1899 in k1896 in a2339 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_fcall f_1926(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_1926,NULL,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,((C_word*)t0)[7]);
t3=(C_word)C_a_i_list(&a,2,((C_word*)t0)[6],C_fix(0));
t4=(C_word)C_a_i_list(&a,3,lf[146],C_SCHEME_END_OF_LIST,((C_word*)t0)[7]);
t5=(C_word)C_a_i_list(&a,2,lf[147],t4);
t6=(C_word)C_a_i_list(&a,1,lf[148]);
t7=(C_word)C_a_i_list(&a,3,lf[149],((C_word*)t0)[6],lf[148]);
t8=(C_word)C_a_i_list(&a,3,lf[146],t6,t7);
t9=(C_word)C_a_i_list(&a,2,lf[150],t8);
t10=(C_word)C_a_i_list(&a,3,t3,t5,t9);
t11=(C_word)C_a_i_list(&a,3,lf[151],t10,((C_word*)((C_word*)t0)[5])[1]);
t12=(C_word)C_a_i_list(&a,3,lf[146],t2,t11);
t13=(C_word)C_a_i_list(&a,3,lf[146],((C_word*)((C_word*)t0)[4])[1],t12);
t14=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t14+1)))(2,t14,(C_word)C_a_i_cons(&a,2,t13,((C_word*)((C_word*)t0)[2])[1]));}

/* k1881 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1883(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1883,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2338,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 493  return-to-host");
t3=C_retrieve(lf[143]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k2336 in k1881 in k1878 in k1875 in k1872 in k1869 in k1866 in k1863 in k1860 in k1857 in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_2338(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_UNDEFINED);}

/* mp:inhook in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1852(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1852,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 378  error");
t3=*((C_word*)lf[39]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[141]);}

/* mp:micro in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1846(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1846,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 376  error");
t3=*((C_word*)lf[39]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[138]);}

/* mp:alloff in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1840(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1840,2,t0,t1);}
C_trace("ChickenBridge.scm: 374  error");
t2=*((C_word*)lf[39]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,t1,lf[135]);}

/* mp:ctrl in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1834(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_1834,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 372  error");
t6=*((C_word*)lf[39]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[132]);}

/* mp:prog in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1828(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_1828,5,t0,t1,t2,t3,t4);}
C_trace("ChickenBridge.scm: 370  error");
t5=*((C_word*)lf[39]+1);
((C_proc3)C_retrieve_proc(t5))(3,t5,t1,lf[129]);}

/* mp:off in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1822(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_1822,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 368  error");
t6=*((C_word*)lf[39]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[126]);}

/* mp:on in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1816(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_1816,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 366  error");
t6=*((C_word*)lf[39]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[123]);}

/* mp:note in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1810(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
C_word tmp;
C_word t7;
C_word t8;
C_word ab[8],*a=ab;
if(c!=7) C_bad_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr7,(void*)f_1810,7,t0,t1,t2,t3,t4,t5,t6);}
t7=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_1127,a[2]=t1,a[3]=t6,a[4]=t5,a[5]=t4,a[6]=t3,a[7]=t2,tmp=(C_word)a,a+=8,tmp);
C_trace("##sys#gc");
t8=C_retrieve(lf[74]);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,C_SCHEME_FALSE);}

/* k1125 in mp:note in k1806 in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1127(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_1127,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[7]);
t4=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[6]);
t5=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[5]);
t6=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[4]);
t7=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[3]);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub241,a[2]=lf[120],tmp=(C_word)a,a+=3,tmp);
((C_proc8)C_retrieve_proc(t8))(8,t8,((C_word*)t0)[2],t2,t3,t4,t5,t6,t7);}

/* ferror in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_fcall f_1571(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1571,NULL,3,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1579,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_apply(5,0,t4,C_retrieve(lf[117]),t2,t3);}

/* k1577 in ferror in k1567 in k1564 in k519 in k516 in k513 in k510 */
static void C_ccall f_1579(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 283  error");
t2=*((C_word*)lf[39]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* hush in k519 in k516 in k513 in k510 */
static void C_ccall f_1555(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1555,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1559,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1237,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[74]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k1235 in hush in k519 in k516 in k513 in k510 */
static void C_ccall f_1237(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1237,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub294,a[2]=lf[113],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k1557 in hush in k519 in k516 in k513 in k510 */
static void C_ccall f_1559(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 260  values");
C_values(2,0,((C_word*)t0)[2]);}

/* stop in k519 in k516 in k513 in k510 */
static void C_ccall f_1497(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+9)){
C_save_and_reclaim((void*)tr2r,(void*)f_1497r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_1497r(t0,t1,t2);}}

static void C_ccall f_1497r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a=C_alloc(9);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1501,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 250  scheduler-stop");
f_1220(t3,C_fix(-1));}
else{
t4=C_SCHEME_UNDEFINED;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_set_block_item(t5,0,(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1515,a[2]=t5,a[3]=lf[110],tmp=(C_word)a,a+=4,tmp));
t7=((C_word*)t5)[1];
f_1515(t7,t3,t2);}}

/* do344 in stop in k519 in k516 in k513 in k510 */
static void C_fcall f_1515(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1515,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1525,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_fixnump(t4))){
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 254  scheduler-stop");
f_1220(t3,t5);}
else{
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 255  error");
t6=*((C_word*)lf[39]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t3,lf[109],t5);}}}

/* k1523 in do344 in stop in k519 in k516 in k513 in k510 */
static void C_ccall f_1525(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_1515(t3,((C_word*)t0)[2],t2);}

/* k1499 in stop in k519 in k516 in k513 in k510 */
static void C_ccall f_1501(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 256  values");
C_values(2,0,((C_word*)t0)[2]);}

/* cont in k519 in k516 in k513 in k510 */
static void C_ccall f_1488(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1488,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1492,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1215,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[74]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k1213 in cont in k519 in k516 in k513 in k510 */
static void C_ccall f_1215(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1215,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub284,a[2]=lf[106],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k1490 in cont in k519 in k516 in k513 in k510 */
static void C_ccall f_1492(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 246  values");
C_values(2,0,((C_word*)t0)[2]);}

/* paused? in k519 in k516 in k513 in k510 */
static void C_ccall f_1482(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1482,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1197,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t3=C_retrieve(lf[74]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,C_SCHEME_FALSE);}

/* k1195 in paused? in k519 in k516 in k513 in k510 */
static void C_ccall f_1197(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1197,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub276,a[2]=lf[103],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* pause in k519 in k516 in k513 in k510 */
static void C_ccall f_1473(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1473,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1477,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1206,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[74]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k1204 in pause in k519 in k516 in k513 in k510 */
static void C_ccall f_1206(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1206,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub280,a[2]=lf[100],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k1475 in pause in k519 in k516 in k513 in k510 */
static void C_ccall f_1477(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 239  values");
C_values(2,0,((C_word*)t0)[2]);}

/* time-format in k519 in k516 in k513 in k510 */
static void C_ccall f_1410(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+11)){
C_save_and_reclaim((void*)tr2rv,(void*)f_1410r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_1410r(t0,t1,t2);}}

static void C_ccall f_1410r(C_word t0,C_word t1,C_word t2){
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
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1423,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1162,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t5=C_retrieve(lf[74]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,C_SCHEME_FALSE);}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
t4=(C_word)C_i_eqvp(t3,lf[94]);
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1435,a[2]=t2,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
if(C_truep(t4)){
t6=t5;
f_1435(t6,t4);}
else{
t6=(C_word)C_eqp(t3,C_fix(1));
t7=t5;
f_1435(t7,(C_truep(t6)?t6:(C_word)C_eqp(t3,lf[97])));}}}

/* k1433 in time-format in k519 in k516 in k513 in k510 */
static void C_fcall f_1435(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a;
if(C_truep(t1)){
t2=C_mutate((C_word*)lf[90]+1,*((C_word*)lf[70]+1));
C_trace("ChickenBridge.scm: 228  scheduler-set-time-milliseconds");
f_1167(((C_word*)t0)[4],C_SCHEME_FALSE);}
else{
t2=(C_word)C_eqp(((C_word*)t0)[3],C_fix(1000));
t3=(C_truep(t2)?t2:(C_word)C_eqp(((C_word*)t0)[3],lf[95]));
if(C_truep(t3)){
t4=C_mutate((C_word*)lf[90]+1,*((C_word*)lf[68]+1));
C_trace("ChickenBridge.scm: 232  scheduler-set-time-milliseconds");
f_1167(((C_word*)t0)[4],C_SCHEME_TRUE);}
else{
t4=(C_word)C_i_vector_ref(((C_word*)t0)[2],C_fix(0));
C_trace("ChickenBridge.scm: 235  error");
t5=*((C_word*)lf[39]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,((C_word*)t0)[4],lf[96],t4);}}}

/* k1160 in time-format in k519 in k516 in k513 in k510 */
static void C_ccall f_1162(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1162,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub256,a[2]=lf[93],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k1421 in time-format in k519 in k516 in k513 in k510 */
static void C_ccall f_1423(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_truep(t1)?C_fix(1000):lf[92]));}

/* sprout in k519 in k516 in k513 in k510 */
static void C_ccall f_1242(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+12)){
C_save_and_reclaim((void*)tr3r,(void*)f_1242r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_1242r(t0,t1,t2,t3);}}

static void C_ccall f_1242r(C_word t0,C_word t1,C_word t2,C_word t3){
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
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1244,a[2]=t2,a[3]=lf[86],tmp=(C_word)a,a+=4,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1356,a[2]=t4,a[3]=lf[87],tmp=(C_word)a,a+=4,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1361,a[2]=t5,a[3]=lf[88],tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("def-start304325");
t7=t6;
f_1361(t7,t1);}
else{
t7=(C_word)C_i_car(t3);
t8=(C_word)C_i_cdr(t3);
if(C_truep((C_word)C_i_nullp(t8))){
C_trace("def-id305323");
t9=t5;
f_1356(t9,t1,t7);}
else{
t9=(C_word)C_i_car(t8);
t10=(C_word)C_i_cdr(t8);
if(C_truep((C_word)C_i_nullp(t10))){
C_trace("body302307");
t11=t4;
f_1244(t11,t1,t7,t9);}
else{
C_trace("##sys#error");
t11=*((C_word*)lf[26]+1);
((C_proc4)(void*)(*((C_word*)t11+1)))(4,t11,t1,lf[0],t10);}}}}

/* def-start304 in sprout in k519 in k516 in k513 in k510 */
static void C_fcall f_1361(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1361,NULL,2,t0,t1);}
C_trace("def-id305323");
t2=((C_word*)t0)[2];
f_1356(t2,t1,C_fix(0));}

/* def-id305 in sprout in k519 in k516 in k513 in k510 */
static void C_fcall f_1356(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1356,NULL,3,t0,t1,t2);}
C_trace("body302307");
t3=((C_word*)t0)[2];
f_1244(t3,t1,t2,C_fix(-1));}

/* body302 in sprout in k519 in k516 in k513 in k510 */
static void C_fcall f_1244(C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)trf_1244,NULL,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1246,a[2]=t4,a[3]=lf[83],tmp=(C_word)a,a+=4,tmp);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1274,a[2]=t5,a[3]=lf[84],tmp=(C_word)a,a+=4,tmp);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1304,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t0)[2]))){
t9=C_SCHEME_UNDEFINED;
t10=(*a=C_VECTOR_TYPE|1,a[1]=t9,tmp=(C_word)a,a+=2,tmp);
t11=C_set_block_item(t10,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_1315,a[2]=t6,a[3]=t7,a[4]=t10,a[5]=((C_word*)t0)[2],a[6]=lf[85],tmp=(C_word)a,a+=7,tmp));
t12=((C_word*)t10)[1];
f_1315(t12,t8,((C_word*)t0)[2]);}
else{
t9=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1347,a[2]=((C_word*)t0)[2],a[3]=t8,tmp=(C_word)a,a+=4,tmp);
t10=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1351,a[2]=t7,a[3]=((C_word*)t0)[2],a[4]=t9,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 214  nextstart");
t11=t6;
f_1246(t11,t10);}}

/* k1349 in body302 in sprout in k519 in k516 in k513 in k510 */
static void C_ccall f_1351(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1351,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1355,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 214  nextid");
t3=((C_word*)t0)[2];
f_1274(t3,t2);}

/* k1353 in k1349 in body302 in sprout in k519 in k516 in k513 in k510 */
static void C_ccall f_1355(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 214  scheduler-sprout");
f_1176(((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k1345 in body302 in sprout in k519 in k516 in k513 in k510 */
static void C_ccall f_1347(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
f_1304(2,t2,((C_word*)t0)[2]);}

/* do316 in body302 in sprout in k519 in k516 in k513 in k510 */
static void C_fcall f_1315(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1315,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,((C_word*)t0)[5]);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1325,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1340,a[2]=((C_word*)t0)[3],a[3]=t4,a[4]=t3,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 212  nextstart");
t6=((C_word*)t0)[2];
f_1246(t6,t5);}}

/* k1338 in do316 in body302 in sprout in k519 in k516 in k513 in k510 */
static void C_ccall f_1340(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1340,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1344,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 212  nextid");
t3=((C_word*)t0)[2];
f_1274(t3,t2);}

/* k1342 in k1338 in do316 in body302 in sprout in k519 in k516 in k513 in k510 */
static void C_ccall f_1344(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 212  scheduler-sprout");
f_1176(((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k1323 in do316 in body302 in sprout in k519 in k516 in k513 in k510 */
static void C_ccall f_1325(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_1315(t3,((C_word*)t0)[2],t2);}

/* k1302 in body302 in sprout in k519 in k516 in k513 in k510 */
static void C_ccall f_1304(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 218  values");
C_values(2,0,((C_word*)t0)[2]);}

/* nextid in body302 in sprout in k519 in k516 in k513 in k510 */
static void C_fcall f_1274(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_1274,NULL,2,t0,t1);}
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

/* nextstart in body302 in sprout in k519 in k516 in k513 in k510 */
static void C_fcall f_1246(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_1246,NULL,2,t0,t1);}
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

/* scheduler-stop in k519 in k516 in k513 in k510 */
static void C_fcall f_1220(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1220,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1224,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[74]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k1222 in scheduler-stop in k519 in k516 in k513 in k510 */
static void C_ccall f_1224(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1224,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_fixnum_argumentp(((C_word*)t0)[3]);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub289,a[2]=lf[80],tmp=(C_word)a,a+=3,tmp);
((C_proc4)C_retrieve_proc(t4))(4,t4,((C_word*)t0)[2],t2,t3);}

/* scheduler-sprout in k519 in k516 in k513 in k510 */
static void C_fcall f_1176(C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1176,NULL,4,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_1180,a[2]=t2,a[3]=t1,a[4]=t4,a[5]=t3,tmp=(C_word)a,a+=6,tmp);
C_trace("##sys#gc");
t6=C_retrieve(lf[74]);
((C_proc3)C_retrieve_proc(t6))(3,t6,t5,C_SCHEME_FALSE);}

/* k1178 in scheduler-sprout in k519 in k516 in k513 in k510 */
static void C_ccall f_1180(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1180,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[5]);
t4=(C_word)C_i_foreign_fixnum_argumentp(((C_word*)t0)[4]);
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub269,a[2]=lf[77],tmp=(C_word)a,a+=3,tmp);
((C_proc6)C_retrieve_proc(t5))(6,t5,((C_word*)t0)[3],t2,((C_word*)t0)[2],t3,t4);}

/* scheduler-set-time-milliseconds in k519 in k516 in k513 in k510 */
static void C_fcall f_1167(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1167,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1171,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[74]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k1169 in scheduler-set-time-milliseconds in k519 in k516 in k513 in k510 */
static void C_ccall f_1171(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1171,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub261,a[2]=lf[73],tmp=(C_word)a,a+=3,tmp);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[3],t2,((C_word*)t0)[2]);}

/* current-time-seconds in k519 in k516 in k513 in k510 */
static void C_ccall f_1155(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1155,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub253(t2));}

/* current-time-milliseconds in k519 in k516 in k513 in k510 */
static void C_ccall f_1152(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1152,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub250(t2));}

/* print-error in k519 in k516 in k513 in k510 */
static void C_ccall f_1109(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1109,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1114,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[64]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_1114(2,t4,C_SCHEME_FALSE);}}

/* k1112 in print-error in k519 in k516 in k513 in k510 */
static void C_ccall f_1114(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub231(C_SCHEME_UNDEFINED,t1));}

/* print-message in k519 in k516 in k513 in k510 */
static void C_ccall f_1095(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1095,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1100,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[64]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_1100(2,t4,C_SCHEME_FALSE);}}

/* k1098 in print-message in k519 in k516 in k513 in k510 */
static void C_ccall f_1100(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub225(C_SCHEME_UNDEFINED,t1));}

/* pick in k519 in k516 in k513 in k510 */
static void C_ccall f_1089(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2r,(void*)f_1089r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_1089r(t0,t1,t2);}}

static void C_ccall f_1089r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_trace("ChickenBridge.scm: 102  pickl");
t3=*((C_word*)lf[57]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,t2);}

/* pickl in k519 in k516 in k513 in k510 */
static void C_ccall f_1066(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1066,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 102  error");
t3=*((C_word*)lf[39]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t1,lf[58],C_retrieve(lf[59]));}
else{
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1083,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
t4=(C_word)C_i_length(t2);
C_trace("ChickenBridge.scm: 102  tb:rani");
f_659(t3,t4);}}

/* k1081 in pickl in k519 in k516 in k513 in k510 */
static void C_ccall f_1083(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_i_list_ref(((C_word*)t0)[2],t1));}

/* odds in k519 in k516 in k513 in k510 */
static void C_ccall f_999(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+12)){
C_save_and_reclaim((void*)tr3r,(void*)f_999r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_999r(t0,t1,t2,t3);}}

static void C_ccall f_999r(C_word t0,C_word t1,C_word t2,C_word t3){
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
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1001,a[2]=t2,a[3]=lf[53],tmp=(C_word)a,a+=4,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1013,a[2]=t4,a[3]=lf[54],tmp=(C_word)a,a+=4,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1018,a[2]=t5,a[3]=lf[55],tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("def-true176184");
t7=t6;
f_1018(t7,t1);}
else{
t7=(C_word)C_i_car(t3);
t8=(C_word)C_i_cdr(t3);
if(C_truep((C_word)C_i_nullp(t8))){
C_trace("def-false177182");
t9=t5;
f_1013(t9,t1,t7);}
else{
t9=(C_word)C_i_car(t8);
t10=(C_word)C_i_cdr(t8);
if(C_truep((C_word)C_i_nullp(t10))){
C_trace("body174179");
t11=t4;
f_1001(t11,t1,t7,t9);}
else{
C_trace("##sys#error");
t11=*((C_word*)lf[26]+1);
((C_proc4)(void*)(*((C_word*)t11+1)))(4,t11,t1,lf[0],t10);}}}}

/* def-true176 in odds in k519 in k516 in k513 in k510 */
static void C_fcall f_1018(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1018,NULL,2,t0,t1);}
C_trace("def-false177182");
t2=((C_word*)t0)[2];
f_1013(t2,t1,C_SCHEME_TRUE);}

/* def-false177 in odds in k519 in k516 in k513 in k510 */
static void C_fcall f_1013(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1013,NULL,3,t0,t1,t2);}
C_trace("body174179");
t3=((C_word*)t0)[2];
f_1001(t3,t1,t2,C_SCHEME_FALSE);}

/* body174 in odds in k519 in k516 in k513 in k510 */
static void C_fcall f_1001(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1001,NULL,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_1012,a[2]=t3,a[3]=t2,a[4]=t1,a[5]=((C_word*)t0)[2],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 102  tb:ranf");
f_666(t4,C_fix(1));}

/* k1010 in body174 in odds in k519 in k516 in k513 in k510 */
static void C_ccall f_1012(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_lessp(t1,((C_word*)t0)[5]);
t3=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_truep(t2)?((C_word*)t0)[3]:((C_word*)t0)[2]));}

/* ran in k519 in k516 in k513 in k510 */
static void C_ccall f_948(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+5)){
C_save_and_reclaim((void*)tr3rv,(void*)f_948r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest_vector(a,C_rest_count(0));
f_948r(t0,t1,t2,t3);}}

static void C_ccall f_948r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word *a=C_alloc(5);
if(C_truep((C_word)C_vemptyp(t3))){
if(C_truep((C_word)C_fixnump(t2))){
C_trace("ChickenBridge.scm: 102  tb:rani");
f_659(t1,t2);}
else{
C_trace("ChickenBridge.scm: 102  tb:ranf");
f_666(t1,t2);}}
else{
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_973,a[2]=t2,a[3]=t1,a[4]=t3,tmp=(C_word)a,a+=5,tmp);
if(C_truep((C_word)C_fixnump(t2))){
t5=(C_word)C_i_vector_ref(t3,C_fix(0));
t6=t4;
f_973(t6,(C_word)C_fixnump(t5));}
else{
t5=t4;
f_973(t5,C_SCHEME_FALSE);}}}

/* k971 in ran in k519 in k516 in k513 in k510 */
static void C_fcall f_973(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_973,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_vector_ref(((C_word*)t0)[4],C_fix(0));
t3=((C_word*)t0)[3];
t4=((C_word*)t0)[2];
t5=(C_word)C_i_foreign_fixnum_argumentp(t4);
t6=(C_word)C_i_foreign_fixnum_argumentp(t2);
t7=t3;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub94(C_SCHEME_UNDEFINED,t5,t6));}
else{
t2=(C_word)C_i_vector_ref(((C_word*)t0)[4],C_fix(0));
t3=((C_word*)t0)[3];
t4=((C_word*)t0)[2];
t5=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t6=(C_word)C_i_foreign_flonum_argumentp(t4);
t7=(C_word)C_i_foreign_flonum_argumentp(t2);
t8=t3;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,(C_word)stub100(t5,t6,t7));}}

/* ran-set! in k519 in k516 in k513 in k510 */
static void C_ccall f_942(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_942,3,t0,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub80(C_SCHEME_UNDEFINED,t2));}

/* interp in k519 in k516 in k513 in k510 */
static void C_ccall f_936(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr3r,(void*)f_936r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_936r(t0,t1,t2,t3);}}

static void C_ccall f_936r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_trace("ChickenBridge.scm: 102  interpl");
t4=*((C_word*)lf[38]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t1,t2,t3);}

/* interpl in k519 in k516 in k513 in k510 */
static void C_ccall f_841(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+6)){
C_save_and_reclaim((void*)tr4rv,(void*)f_841r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest_vector(a,C_rest_count(0));
f_841r(t0,t1,t2,t3,t4);}}

static void C_ccall f_841r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word *a=C_alloc(6);
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_845,a[2]=t1,a[3]=t2,a[4]=t3,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("ChickenBridge.scm: 102  error");
t6=*((C_word*)lf[39]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t5,lf[44],t3);}
else{
t6=t5;
f_845(2,t6,(C_word)C_i_car(t3));}}

/* k843 in interpl in k519 in k516 in k513 in k510 */
static void C_ccall f_845(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_845,2,t0,t1);}
t2=t1;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_848,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=t3,tmp=(C_word)a,a+=7,tmp);
t5=(C_word)C_i_cdr(((C_word*)t0)[4]);
if(C_truep((C_word)C_i_nullp(t5))){
C_trace("ChickenBridge.scm: 102  err");
t6=C_retrieve(lf[42]);
((C_proc4)C_retrieve_proc(t6))(4,t6,t4,lf[43],((C_word*)t0)[4]);}
else{
t6=t4;
f_848(2,t6,(C_word)C_i_cadr(((C_word*)t0)[4]));}}

/* k846 in k843 in interpl in k519 in k516 in k513 in k510 */
static void C_ccall f_848(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_848,2,t0,t1);}
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
t13=C_set_block_item(t12,0,(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_860,a[2]=((C_word*)t0)[4],a[3]=t12,a[4]=t9,a[5]=t7,a[6]=t3,a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[3],a[9]=t5,a[10]=lf[41],tmp=(C_word)a,a+=11,tmp));
t14=((C_word*)t12)[1];
f_860(t14,((C_word*)t0)[2],t10);}

/* do155 in k846 in k843 in interpl in k519 in k516 in k513 in k510 */
static void C_fcall f_860(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_860,NULL,3,t0,t1,t2);}
t3=(C_word)C_i_nullp(t2);
t4=(C_truep(t3)?t3:(C_word)C_i_greaterp(((C_word*)((C_word*)t0)[9])[1],((C_word*)t0)[8]));
if(C_truep(t4)){
C_trace("ChickenBridge.scm: 102  tb:rescale");
f_523(t1,((C_word*)t0)[8],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[9])[1],((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[4]);}
else{
t5=C_mutate(((C_word *)((C_word*)t0)[7])+1,((C_word*)((C_word*)t0)[9])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[6])+1,((C_word*)((C_word*)t0)[5])[1]);
t7=(C_word)C_i_car(t2);
t8=C_mutate(((C_word *)((C_word*)t0)[9])+1,t7);
t9=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_882,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t10=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t10))){
C_trace("ChickenBridge.scm: 102  error");
t11=*((C_word*)lf[39]+1);
((C_proc4)C_retrieve_proc(t11))(4,t11,t9,lf[40],((C_word*)t0)[2]);}
else{
t11=(C_word)C_i_cadr(t2);
t12=C_mutate(((C_word *)((C_word*)t0)[5])+1,t11);
t13=t9;
f_882(2,t13,t12);}}}

/* k880 in do155 in k846 in k843 in interpl in k519 in k516 in k513 in k510 */
static void C_ccall f_882(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cddr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_860(t3,((C_word*)t0)[2],t2);}

/* hertz->keynum in k519 in k516 in k513 in k510 */
static void C_ccall f_835(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_835,3,t0,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub75(t3,t4));}

/* keynum->pc in k519 in k516 in k513 in k510 */
static void C_ccall f_829(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_829,3,t0,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub71(C_SCHEME_UNDEFINED,t3));}

/* keynum->hertz in k519 in k516 in k513 in k510 */
static void C_ccall f_823(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_823,3,t0,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub66(t3,t4));}

/* scaler->cents in k519 in k516 in k513 in k510 */
static void C_ccall f_817(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_817,3,t0,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub62(C_SCHEME_UNDEFINED,t3));}

/* cents->scaler in k519 in k516 in k513 in k510 */
static void C_ccall f_811(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_811,3,t0,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_fixnum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub57(t3,t4));}

/* rhythm->seconds in k519 in k516 in k513 in k510 */
static void C_ccall f_751(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+12)){
C_save_and_reclaim((void*)tr3r,(void*)f_751r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_751r(t0,t1,t2,t3);}}

static void C_ccall f_751r(C_word t0,C_word t1,C_word t2,C_word t3){
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
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_753,a[2]=t2,a[3]=lf[21],tmp=(C_word)a,a+=4,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_758,a[2]=t4,a[3]=lf[23],tmp=(C_word)a,a+=4,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_763,a[2]=t5,a[3]=lf[25],tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("def-tempo128136");
t7=t6;
f_763(t7,t1);}
else{
t7=(C_word)C_i_car(t3);
t8=(C_word)C_i_cdr(t3);
if(C_truep((C_word)C_i_nullp(t8))){
C_trace("def-beat129134");
t9=t5;
f_758(t9,t1,t7);}
else{
t9=(C_word)C_i_car(t8);
t10=(C_word)C_i_cdr(t8);
if(C_truep((C_word)C_i_nullp(t10))){
C_trace("body126131");
t11=t4;
f_753(t11,t1,t7,t9);}
else{
C_trace("##sys#error");
t11=*((C_word*)lf[26]+1);
((C_proc4)(void*)(*((C_word*)t11+1)))(4,t11,t1,lf[0],t10);}}}}

/* def-tempo128 in rhythm->seconds in k519 in k516 in k513 in k510 */
static void C_fcall f_763(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_763,NULL,2,t0,t1);}
C_trace("def-beat129134");
t2=((C_word*)t0)[2];
f_758(t2,t1,lf[24]);}

/* def-beat129 in rhythm->seconds in k519 in k516 in k513 in k510 */
static void C_fcall f_758(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_758,NULL,3,t0,t1,t2);}
C_trace("body126131");
t3=((C_word*)t0)[2];
f_753(t3,t1,t2,lf[22]);}

/* body126 in rhythm->seconds in k519 in k516 in k513 in k510 */
static void C_fcall f_753(C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)trf_753,NULL,4,t0,t1,t2,t3);}
t4=((C_word*)t0)[2];
t5=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t6=(C_word)C_i_foreign_flonum_argumentp(t4);
t7=(C_word)C_i_foreign_flonum_argumentp(t2);
t8=(C_word)C_i_foreign_flonum_argumentp(t3);
t9=t1;
((C_proc2)(void*)(*((C_word*)t9+1)))(2,t9,(C_word)stub50(t5,t6,t7,t8));}

/* decimals in k519 in k516 in k513 in k510 */
static void C_ccall f_745(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_745,4,t0,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_fixnum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub35(t4,t5,t6));}

/* quantize in k519 in k516 in k513 in k510 */
static void C_ccall f_739(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_739,4,t0,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_flonum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub42(t4,t5,t6));}

/* int in k519 in k516 in k513 in k510 */
static void C_ccall f_733(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_733,3,t0,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub30(C_SCHEME_UNDEFINED,t3));}

/* discrete in k519 in k516 in k513 in k510 */
static void C_ccall f_714(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,...){
C_word tmp;
C_word t7;
va_list v;
C_word *a,c2=c;
C_save_rest(t6,c2,7);
if(c<7) C_bad_min_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr7rv,(void*)f_714r,7,t0,t1,t2,t3,t4,t5,t6);}
else{
a=C_alloc((c-7)*3);
t7=C_restore_rest_vector(a,C_rest_count(0));
f_714r(t0,t1,t2,t3,t4,t5,t6,t7);}}

static void C_ccall f_714r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
C_word tmp;
C_word t8;
C_word t9;
if(C_truep((C_word)C_vemptyp(t7))){
C_trace("ChickenBridge.scm: 102  tb:discrete");
f_550(t1,t2,t3,t4,t5,t6,C_fix(1));}
else{
t8=(C_word)C_i_vector_ref(t7,C_fix(0));
C_trace("ChickenBridge.scm: 102  tb:discrete");
f_550(t1,t2,t3,t4,t5,t6,t8);}}

/* rescale in k519 in k516 in k513 in k510 */
static void C_ccall f_695(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,...){
C_word tmp;
C_word t7;
va_list v;
C_word *a,c2=c;
C_save_rest(t6,c2,7);
if(c<7) C_bad_min_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr7rv,(void*)f_695r,7,t0,t1,t2,t3,t4,t5,t6);}
else{
a=C_alloc((c-7)*3);
t7=C_restore_rest_vector(a,C_rest_count(0));
f_695r(t0,t1,t2,t3,t4,t5,t6,t7);}}

static void C_ccall f_695r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
C_word tmp;
C_word t8;
C_word t9;
if(C_truep((C_word)C_vemptyp(t7))){
C_trace("ChickenBridge.scm: 102  tb:rescale");
f_523(t1,t2,t3,t4,t5,t6,C_fix(1));}
else{
t8=(C_word)C_i_vector_ref(t7,C_fix(0));
C_trace("ChickenBridge.scm: 102  tb:rescale");
f_523(t1,t2,t3,t4,t5,t6,t8);}}

/* tb:ranf in k519 in k516 in k513 in k510 */
static void C_fcall f_666(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_666,NULL,2,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub88(t3,t4));}

/* tb:rani in k519 in k516 in k513 in k510 */
static void C_fcall f_659(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_659,NULL,2,t1,t2);}
t3=(C_word)C_i_foreign_fixnum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub84(C_SCHEME_UNDEFINED,t3));}

/* tb:discrete in k519 in k516 in k513 in k510 */
static void C_fcall f_550(C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
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
C_save_and_reclaim((void*)trf_550,NULL,7,t1,t2,t3,t4,t5,t6,t7);}
t8=(C_word)C_i_foreign_flonum_argumentp(t2);
t9=(C_word)C_i_foreign_flonum_argumentp(t3);
t10=(C_word)C_i_foreign_flonum_argumentp(t4);
t11=(C_word)C_i_foreign_fixnum_argumentp(t5);
t12=(C_word)C_i_foreign_fixnum_argumentp(t6);
t13=(C_word)C_i_foreign_flonum_argumentp(t7);
t14=t1;
((C_proc2)(void*)(*((C_word*)t14+1)))(2,t14,(C_word)stub21(C_SCHEME_UNDEFINED,t8,t9,t10,t11,t12,t13));}

/* tb:rescale in k519 in k516 in k513 in k510 */
static void C_fcall f_523(C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
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
C_save_and_reclaim((void*)trf_523,NULL,7,t1,t2,t3,t4,t5,t6,t7);}
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
static C_PTABLE_ENTRY ptable[162] = {
{"toplevelChickenBridge.scm",(void*)C_grace_toplevel},
{"f_512ChickenBridge.scm",(void*)f_512},
{"f_515ChickenBridge.scm",(void*)f_515},
{"f_518ChickenBridge.scm",(void*)f_518},
{"f_521ChickenBridge.scm",(void*)f_521},
{"f_1566ChickenBridge.scm",(void*)f_1566},
{"f_2352ChickenBridge.scm",(void*)f_2352},
{"f_2399ChickenBridge.scm",(void*)f_2399},
{"f_2389ChickenBridge.scm",(void*)f_2389},
{"f_2356ChickenBridge.scm",(void*)f_2356},
{"f_1569ChickenBridge.scm",(void*)f_1569},
{"f_2346ChickenBridge.scm",(void*)f_2346},
{"f_1585ChickenBridge.scm",(void*)f_1585},
{"f_1798ChickenBridge.scm",(void*)f_1798},
{"f_1588ChickenBridge.scm",(void*)f_1588},
{"f_1591ChickenBridge.scm",(void*)f_1591},
{"f_1603ChickenBridge.scm",(void*)f_1603},
{"f_1651ChickenBridge.scm",(void*)f_1651},
{"f_1667ChickenBridge.scm",(void*)f_1667},
{"f_1677ChickenBridge.scm",(void*)f_1677},
{"f_1776ChickenBridge.scm",(void*)f_1776},
{"f_1772ChickenBridge.scm",(void*)f_1772},
{"f_1721ChickenBridge.scm",(void*)f_1721},
{"f_1727ChickenBridge.scm",(void*)f_1727},
{"f_1661ChickenBridge.scm",(void*)f_1661},
{"f_1606ChickenBridge.scm",(void*)f_1606},
{"f_1611ChickenBridge.scm",(void*)f_1611},
{"f_1624ChickenBridge.scm",(void*)f_1624},
{"f_1808ChickenBridge.scm",(void*)f_1808},
{"f_1859ChickenBridge.scm",(void*)f_1859},
{"f_1862ChickenBridge.scm",(void*)f_1862},
{"f_1865ChickenBridge.scm",(void*)f_1865},
{"f_1868ChickenBridge.scm",(void*)f_1868},
{"f_1871ChickenBridge.scm",(void*)f_1871},
{"f_1874ChickenBridge.scm",(void*)f_1874},
{"f_1877ChickenBridge.scm",(void*)f_1877},
{"f_1880ChickenBridge.scm",(void*)f_1880},
{"f_2340ChickenBridge.scm",(void*)f_2340},
{"f_1898ChickenBridge.scm",(void*)f_1898},
{"f_1901ChickenBridge.scm",(void*)f_1901},
{"f_2175ChickenBridge.scm",(void*)f_2175},
{"f_2283ChickenBridge.scm",(void*)f_2283},
{"f_2195ChickenBridge.scm",(void*)f_2195},
{"f_2204ChickenBridge.scm",(void*)f_2204},
{"f_2208ChickenBridge.scm",(void*)f_2208},
{"f_2212ChickenBridge.scm",(void*)f_2212},
{"f_2220ChickenBridge.scm",(void*)f_2220},
{"f_2216ChickenBridge.scm",(void*)f_2216},
{"f_2185ChickenBridge.scm",(void*)f_2185},
{"f_1904ChickenBridge.scm",(void*)f_1904},
{"f_1907ChickenBridge.scm",(void*)f_1907},
{"f_1910ChickenBridge.scm",(void*)f_1910},
{"f_1913ChickenBridge.scm",(void*)f_1913},
{"f_1916ChickenBridge.scm",(void*)f_1916},
{"f_2169ChickenBridge.scm",(void*)f_2169},
{"f_2068ChickenBridge.scm",(void*)f_2068},
{"f_2075ChickenBridge.scm",(void*)f_2075},
{"f_2077ChickenBridge.scm",(void*)f_2077},
{"f_2149ChickenBridge.scm",(void*)f_2149},
{"f_2101ChickenBridge.scm",(void*)f_2101},
{"f_2104ChickenBridge.scm",(void*)f_2104},
{"f_2125ChickenBridge.scm",(void*)f_2125},
{"f_2091ChickenBridge.scm",(void*)f_2091},
{"f_1919ChickenBridge.scm",(void*)f_1919},
{"f_2057ChickenBridge.scm",(void*)f_2057},
{"f_2045ChickenBridge.scm",(void*)f_2045},
{"f_2041ChickenBridge.scm",(void*)f_2041},
{"f_1926ChickenBridge.scm",(void*)f_1926},
{"f_1883ChickenBridge.scm",(void*)f_1883},
{"f_2338ChickenBridge.scm",(void*)f_2338},
{"f_1852ChickenBridge.scm",(void*)f_1852},
{"f_1846ChickenBridge.scm",(void*)f_1846},
{"f_1840ChickenBridge.scm",(void*)f_1840},
{"f_1834ChickenBridge.scm",(void*)f_1834},
{"f_1828ChickenBridge.scm",(void*)f_1828},
{"f_1822ChickenBridge.scm",(void*)f_1822},
{"f_1816ChickenBridge.scm",(void*)f_1816},
{"f_1810ChickenBridge.scm",(void*)f_1810},
{"f_1127ChickenBridge.scm",(void*)f_1127},
{"f_1571ChickenBridge.scm",(void*)f_1571},
{"f_1579ChickenBridge.scm",(void*)f_1579},
{"f_1555ChickenBridge.scm",(void*)f_1555},
{"f_1237ChickenBridge.scm",(void*)f_1237},
{"f_1559ChickenBridge.scm",(void*)f_1559},
{"f_1497ChickenBridge.scm",(void*)f_1497},
{"f_1515ChickenBridge.scm",(void*)f_1515},
{"f_1525ChickenBridge.scm",(void*)f_1525},
{"f_1501ChickenBridge.scm",(void*)f_1501},
{"f_1488ChickenBridge.scm",(void*)f_1488},
{"f_1215ChickenBridge.scm",(void*)f_1215},
{"f_1492ChickenBridge.scm",(void*)f_1492},
{"f_1482ChickenBridge.scm",(void*)f_1482},
{"f_1197ChickenBridge.scm",(void*)f_1197},
{"f_1473ChickenBridge.scm",(void*)f_1473},
{"f_1206ChickenBridge.scm",(void*)f_1206},
{"f_1477ChickenBridge.scm",(void*)f_1477},
{"f_1410ChickenBridge.scm",(void*)f_1410},
{"f_1435ChickenBridge.scm",(void*)f_1435},
{"f_1162ChickenBridge.scm",(void*)f_1162},
{"f_1423ChickenBridge.scm",(void*)f_1423},
{"f_1242ChickenBridge.scm",(void*)f_1242},
{"f_1361ChickenBridge.scm",(void*)f_1361},
{"f_1356ChickenBridge.scm",(void*)f_1356},
{"f_1244ChickenBridge.scm",(void*)f_1244},
{"f_1351ChickenBridge.scm",(void*)f_1351},
{"f_1355ChickenBridge.scm",(void*)f_1355},
{"f_1347ChickenBridge.scm",(void*)f_1347},
{"f_1315ChickenBridge.scm",(void*)f_1315},
{"f_1340ChickenBridge.scm",(void*)f_1340},
{"f_1344ChickenBridge.scm",(void*)f_1344},
{"f_1325ChickenBridge.scm",(void*)f_1325},
{"f_1304ChickenBridge.scm",(void*)f_1304},
{"f_1274ChickenBridge.scm",(void*)f_1274},
{"f_1246ChickenBridge.scm",(void*)f_1246},
{"f_1220ChickenBridge.scm",(void*)f_1220},
{"f_1224ChickenBridge.scm",(void*)f_1224},
{"f_1176ChickenBridge.scm",(void*)f_1176},
{"f_1180ChickenBridge.scm",(void*)f_1180},
{"f_1167ChickenBridge.scm",(void*)f_1167},
{"f_1171ChickenBridge.scm",(void*)f_1171},
{"f_1155ChickenBridge.scm",(void*)f_1155},
{"f_1152ChickenBridge.scm",(void*)f_1152},
{"f_1109ChickenBridge.scm",(void*)f_1109},
{"f_1114ChickenBridge.scm",(void*)f_1114},
{"f_1095ChickenBridge.scm",(void*)f_1095},
{"f_1100ChickenBridge.scm",(void*)f_1100},
{"f_1089ChickenBridge.scm",(void*)f_1089},
{"f_1066ChickenBridge.scm",(void*)f_1066},
{"f_1083ChickenBridge.scm",(void*)f_1083},
{"f_999ChickenBridge.scm",(void*)f_999},
{"f_1018ChickenBridge.scm",(void*)f_1018},
{"f_1013ChickenBridge.scm",(void*)f_1013},
{"f_1001ChickenBridge.scm",(void*)f_1001},
{"f_1012ChickenBridge.scm",(void*)f_1012},
{"f_948ChickenBridge.scm",(void*)f_948},
{"f_973ChickenBridge.scm",(void*)f_973},
{"f_942ChickenBridge.scm",(void*)f_942},
{"f_936ChickenBridge.scm",(void*)f_936},
{"f_841ChickenBridge.scm",(void*)f_841},
{"f_845ChickenBridge.scm",(void*)f_845},
{"f_848ChickenBridge.scm",(void*)f_848},
{"f_860ChickenBridge.scm",(void*)f_860},
{"f_882ChickenBridge.scm",(void*)f_882},
{"f_835ChickenBridge.scm",(void*)f_835},
{"f_829ChickenBridge.scm",(void*)f_829},
{"f_823ChickenBridge.scm",(void*)f_823},
{"f_817ChickenBridge.scm",(void*)f_817},
{"f_811ChickenBridge.scm",(void*)f_811},
{"f_751ChickenBridge.scm",(void*)f_751},
{"f_763ChickenBridge.scm",(void*)f_763},
{"f_758ChickenBridge.scm",(void*)f_758},
{"f_753ChickenBridge.scm",(void*)f_753},
{"f_745ChickenBridge.scm",(void*)f_745},
{"f_739ChickenBridge.scm",(void*)f_739},
{"f_733ChickenBridge.scm",(void*)f_733},
{"f_714ChickenBridge.scm",(void*)f_714},
{"f_695ChickenBridge.scm",(void*)f_695},
{"f_666ChickenBridge.scm",(void*)f_666},
{"f_659ChickenBridge.scm",(void*)f_659},
{"f_550ChickenBridge.scm",(void*)f_550},
{"f_523ChickenBridge.scm",(void*)f_523},
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
