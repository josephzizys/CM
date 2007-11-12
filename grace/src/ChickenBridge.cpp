/* Generated from ChickenBridge.scm by the CHICKEN compiler
   http://www.call-with-current-continuation.org
   2007-11-12 13:05
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



static C_PTABLE_ENTRY *create_ptable(void);
C_noret_decl(C_library_toplevel)
C_externimport void C_ccall C_library_toplevel(C_word c,C_word d,C_word k) C_noret;
C_noret_decl(C_eval_toplevel)
C_externimport void C_ccall C_eval_toplevel(C_word c,C_word d,C_word k) C_noret;
C_noret_decl(C_extras_toplevel)
C_externimport void C_ccall C_extras_toplevel(C_word c,C_word d,C_word k) C_noret;
C_noret_decl(C_extras_toplevel)
C_externimport void C_ccall C_extras_toplevel(C_word c,C_word d,C_word k) C_noret;

static C_TLS C_word lf[160];


/* from k439 in hush in k295 in k292 in k289 in k286 */
C_noret_decl(stub70)
static void C_ccall stub70(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub70(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_hush();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k433 */
C_noret_decl(stub65)
static void C_ccall stub65(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0) C_noret;
static void C_ccall stub65(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_unfix(C_a0);
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_stop(t0);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k417 in cont in k295 in k292 in k289 in k286 */
C_noret_decl(stub60)
static void C_ccall stub60(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub60(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_cont();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k408 in pause in k295 in k292 in k289 in k286 */
C_noret_decl(stub56)
static void C_ccall stub56(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub56(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_pause();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k399 in paused? in k295 in k292 in k289 in k286 */
C_noret_decl(stub52)
static void C_ccall stub52(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub52(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
C_r=C_mk_bool(scheduler_is_paused());
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k393 */
C_noret_decl(stub45)
static void C_ccall stub45(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2) C_noret;
static void C_ccall stub45(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
C_word t0=(C_word )(C_a0);
double t1=(double )C_c_double(C_a1);
int t2=(int )C_unfix(C_a2);
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_sprout(t0,t1,t2);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k373 in scheduler-set-time-milliseconds in k295 in k292 in k289 in k286 */
C_noret_decl(stub37)
static void C_ccall stub37(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0) C_noret;
static void C_ccall stub37(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_truep(C_a0);
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_set_time_milliseconds(t0);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k364 in time-format in k295 in k292 in k289 in k286 */
C_noret_decl(stub32)
static void C_ccall stub32(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub32(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
C_r=C_mk_bool(scheduler_is_time_milliseconds());
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from current-time-seconds in k295 in k292 in k289 in k286 */
#define return(x) C_cblock C_r = (C_flonum(&C_a,(x))); goto C_ret; C_cblockend
static C_word C_fcall stub29(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub29(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
 C_return( (Time::getMillisecondCounterHiRes() / 1000.0) );
C_ret:
#undef return

return C_r;}

/* from current-time-milliseconds in k295 in k292 in k289 in k286 */
#define return(x) C_cblock C_r = (C_flonum(&C_a,(x))); goto C_ret; C_cblockend
static C_word C_fcall stub26(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub26(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
 C_return( Time::getMillisecondCounterHiRes());
C_ret:
#undef return

return C_r;}

/* from k352 */
C_noret_decl(stub17)
static void C_ccall stub17(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2,C_word C_a3,C_word C_a4) C_noret;
static void C_ccall stub17(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2,C_word C_a3,C_word C_a4){
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

/* from k316 in print-error in k295 in k292 in k289 in k286 */
static C_word C_fcall stub7(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub7(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_error(t0);
return C_r;}

/* from k302 in print-message in k295 in k292 in k289 in k286 */
static C_word C_fcall stub1(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub1(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_message(t0);
return C_r;}

C_noret_decl(C_grace_toplevel)
C_externexport void C_ccall C_grace_toplevel(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_288)
static void C_ccall f_288(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_291)
static void C_ccall f_291(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_294)
static void C_ccall f_294(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_297)
static void C_ccall f_297(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_770)
static void C_ccall f_770(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1556)
static void C_ccall f_1556(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_1603)
static void C_ccall f_1603(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1593)
static void C_ccall f_1593(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1560)
static void C_ccall f_1560(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_773)
static void C_ccall f_773(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1550)
static void C_ccall f_1550(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_1550)
static void C_ccall f_1550r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_789)
static void C_ccall f_789(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1002)
static void C_ccall f_1002(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_792)
static void C_ccall f_792(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_795)
static void C_ccall f_795(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_807)
static void C_ccall f_807(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_855)
static void C_fcall f_855(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_871)
static void C_ccall f_871(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_881)
static void C_ccall f_881(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_980)
static void C_ccall f_980(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_976)
static void C_ccall f_976(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_925)
static void C_ccall f_925(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_931)
static void C_ccall f_931(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_865)
static void C_fcall f_865(C_word t0,C_word t1) C_noret;
C_noret_decl(f_810)
static void C_ccall f_810(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_815)
static void C_fcall f_815(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_828)
static void C_fcall f_828(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1012)
static void C_ccall f_1012(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1063)
static void C_ccall f_1063(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1066)
static void C_ccall f_1066(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1069)
static void C_ccall f_1069(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1072)
static void C_ccall f_1072(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1075)
static void C_ccall f_1075(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1078)
static void C_ccall f_1078(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1081)
static void C_ccall f_1081(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1084)
static void C_ccall f_1084(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1544)
static void C_ccall f_1544(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_1544)
static void C_ccall f_1544r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_1102)
static void C_ccall f_1102(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1105)
static void C_ccall f_1105(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1379)
static void C_fcall f_1379(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1487)
static void C_ccall f_1487(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1399)
static void C_fcall f_1399(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1408)
static void C_fcall f_1408(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1412)
static void C_ccall f_1412(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1416)
static void C_ccall f_1416(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1424)
static void C_fcall f_1424(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1420)
static void C_ccall f_1420(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1389)
static void C_ccall f_1389(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1108)
static void C_ccall f_1108(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1111)
static void C_ccall f_1111(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1114)
static void C_ccall f_1114(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1117)
static void C_ccall f_1117(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1120)
static void C_ccall f_1120(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1373)
static void C_ccall f_1373(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1272)
static void C_fcall f_1272(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1279)
static void C_ccall f_1279(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1281)
static void C_fcall f_1281(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1353)
static void C_ccall f_1353(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1305)
static void C_fcall f_1305(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1308)
static void C_ccall f_1308(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1329)
static void C_ccall f_1329(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1295)
static void C_ccall f_1295(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1123)
static void C_ccall f_1123(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1261)
static void C_ccall f_1261(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1249)
static void C_ccall f_1249(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1245)
static void C_ccall f_1245(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1130)
static void C_fcall f_1130(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1087)
static void C_ccall f_1087(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1542)
static void C_ccall f_1542(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1056)
static void C_ccall f_1056(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1050)
static void C_ccall f_1050(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1044)
static void C_ccall f_1044(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1038)
static void C_ccall f_1038(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_1032)
static void C_ccall f_1032(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_1026)
static void C_ccall f_1026(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_1020)
static void C_ccall f_1020(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_1014)
static void C_ccall f_1014(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_331)
static void C_ccall f_331(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_775)
static void C_fcall f_775(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_783)
static void C_ccall f_783(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_759)
static void C_ccall f_759(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_441)
static void C_ccall f_441(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_763)
static void C_ccall f_763(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_701)
static void C_ccall f_701(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_701)
static void C_ccall f_701r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_719)
static void C_fcall f_719(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_729)
static void C_ccall f_729(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_705)
static void C_ccall f_705(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_692)
static void C_ccall f_692(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_419)
static void C_ccall f_419(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_696)
static void C_ccall f_696(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_686)
static void C_ccall f_686(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_401)
static void C_ccall f_401(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_677)
static void C_ccall f_677(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_410)
static void C_ccall f_410(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_681)
static void C_ccall f_681(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_614)
static void C_ccall f_614(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_614)
static void C_ccall f_614r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_639)
static void C_fcall f_639(C_word t0,C_word t1) C_noret;
C_noret_decl(f_366)
static void C_ccall f_366(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_627)
static void C_ccall f_627(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_446)
static void C_ccall f_446(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_446)
static void C_ccall f_446r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_565)
static void C_fcall f_565(C_word t0,C_word t1) C_noret;
C_noret_decl(f_560)
static void C_fcall f_560(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_448)
static void C_fcall f_448(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_555)
static void C_ccall f_555(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_559)
static void C_ccall f_559(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_551)
static void C_ccall f_551(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_519)
static void C_fcall f_519(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_544)
static void C_ccall f_544(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_548)
static void C_ccall f_548(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_529)
static void C_ccall f_529(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_508)
static void C_ccall f_508(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_478)
static void C_fcall f_478(C_word t0,C_word t1) C_noret;
C_noret_decl(f_450)
static void C_fcall f_450(C_word t0,C_word t1) C_noret;
C_noret_decl(f_424)
static void C_fcall f_424(C_word t0,C_word t1) C_noret;
C_noret_decl(f_428)
static void C_ccall f_428(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_380)
static void C_fcall f_380(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_384)
static void C_ccall f_384(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_371)
static void C_fcall f_371(C_word t0,C_word t1) C_noret;
C_noret_decl(f_375)
static void C_ccall f_375(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_359)
static void C_ccall f_359(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_356)
static void C_ccall f_356(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_313)
static void C_ccall f_313(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_318)
static void C_ccall f_318(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_299)
static void C_ccall f_299(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_304)
static void C_ccall f_304(C_word c,C_word t0,C_word t1) C_noret;

C_noret_decl(trf_855)
static void C_fcall trf_855(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_855(void *dummy){
C_word t4=C_pick(0);
C_word t3=C_pick(1);
C_word t2=C_pick(2);
C_word t1=C_pick(3);
C_word t0=C_pick(4);
C_adjust_stack(-5);
f_855(t0,t1,t2,t3,t4);}

C_noret_decl(trf_865)
static void C_fcall trf_865(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_865(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_865(t0,t1);}

C_noret_decl(trf_815)
static void C_fcall trf_815(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_815(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_815(t0,t1,t2);}

C_noret_decl(trf_828)
static void C_fcall trf_828(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_828(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_828(t0,t1);}

C_noret_decl(trf_1379)
static void C_fcall trf_1379(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1379(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1379(t0,t1,t2);}

C_noret_decl(trf_1399)
static void C_fcall trf_1399(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1399(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1399(t0,t1);}

C_noret_decl(trf_1408)
static void C_fcall trf_1408(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1408(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1408(t0,t1);}

C_noret_decl(trf_1424)
static void C_fcall trf_1424(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1424(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1424(t0,t1);}

C_noret_decl(trf_1272)
static void C_fcall trf_1272(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1272(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1272(t0,t1);}

C_noret_decl(trf_1281)
static void C_fcall trf_1281(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1281(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1281(t0,t1,t2);}

C_noret_decl(trf_1305)
static void C_fcall trf_1305(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1305(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1305(t0,t1);}

C_noret_decl(trf_1130)
static void C_fcall trf_1130(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1130(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1130(t0,t1);}

C_noret_decl(trf_775)
static void C_fcall trf_775(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_775(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_775(t0,t1,t2);}

C_noret_decl(trf_719)
static void C_fcall trf_719(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_719(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_719(t0,t1,t2);}

C_noret_decl(trf_639)
static void C_fcall trf_639(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_639(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_639(t0,t1);}

C_noret_decl(trf_565)
static void C_fcall trf_565(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_565(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_565(t0,t1);}

C_noret_decl(trf_560)
static void C_fcall trf_560(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_560(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_560(t0,t1,t2);}

C_noret_decl(trf_448)
static void C_fcall trf_448(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_448(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_448(t0,t1,t2,t3);}

C_noret_decl(trf_519)
static void C_fcall trf_519(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_519(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_519(t0,t1,t2);}

C_noret_decl(trf_478)
static void C_fcall trf_478(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_478(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_478(t0,t1);}

C_noret_decl(trf_450)
static void C_fcall trf_450(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_450(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_450(t0,t1);}

C_noret_decl(trf_424)
static void C_fcall trf_424(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_424(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_424(t0,t1);}

C_noret_decl(trf_380)
static void C_fcall trf_380(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_380(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_380(t0,t1,t2,t3);}

C_noret_decl(trf_371)
static void C_fcall trf_371(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_371(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_371(t0,t1);}

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
C_word *a;
if(toplevel_initialized) C_kontinue(t1,C_SCHEME_UNDEFINED);
else C_toplevel_entry(C_text("grace_toplevel"));
C_check_nursery_minimum(3);
if(!C_demand(3)){
C_save(t1);
C_reclaim((void*)toplevel_trampoline,NULL);}
toplevel_initialized=1;
if(!C_demand_2(1184)){
C_save(t1);
C_rereclaim2(1184*sizeof(C_word), 1);
t1=C_restore;}
a=C_alloc(3);
C_initialize_lf(lf,160);
lf[0]=C_h_intern(&lf[0],13,"print-message");
lf[1]=C_h_intern(&lf[1],17,"\003sysmake-c-string");
lf[2]=C_static_lambda_info(C_heaptop,19,"(print-message a04)");
lf[3]=C_h_intern(&lf[3],11,"print-error");
lf[4]=C_static_lambda_info(C_heaptop,18,"(print-error a610)");
lf[5]=C_h_intern(&lf[5],25,"current-time-milliseconds");
lf[6]=C_static_lambda_info(C_heaptop,27,"(current-time-milliseconds)");
lf[7]=C_h_intern(&lf[7],20,"current-time-seconds");
lf[8]=C_static_lambda_info(C_heaptop,22,"(current-time-seconds)");
lf[10]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[11]=C_h_intern(&lf[11],6,"\003sysgc");
lf[12]=C_static_lambda_info(C_heaptop,39,"(scheduler-set-time-milliseconds a3639)");
lf[14]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[15]=C_static_lambda_info(C_heaptop,36,"(scheduler-sprout a4447 a4348 a4249)");
lf[17]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[18]=C_static_lambda_info(C_heaptop,22,"(scheduler-stop a6467)");
lf[19]=C_h_intern(&lf[19],6,"sprout");
lf[20]=C_static_lambda_info(C_heaptop,11,"(nextstart)");
lf[21]=C_static_lambda_info(C_heaptop,8,"(nextid)");
lf[22]=C_static_lambda_info(C_heaptop,10,"(do92 p94)");
lf[23]=C_static_lambda_info(C_heaptop,21,"(body78 start84 id85)");
lf[24]=C_static_lambda_info(C_heaptop,22,"(def-id81 %start76100)");
lf[25]=C_static_lambda_info(C_heaptop,13,"(def-start80)");
lf[26]=C_h_intern(&lf[26],9,"\003syserror");
lf[27]=C_static_string(C_heaptop,27,"too many optional arguments");
lf[28]=C_static_lambda_info(C_heaptop,24,"(sprout proc74 . args75)");
lf[29]=C_h_intern(&lf[29],3,"now");
lf[30]=C_h_intern(&lf[30],11,"time-format");
lf[31]=C_flonum(C_heaptop,1.0);
lf[32]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[33]=C_flonum(C_heaptop,1.0);
lf[34]=C_h_intern(&lf[34],1,"m");
lf[35]=C_h_intern(&lf[35],5,"error");
lf[36]=C_static_string(C_heaptop,17,"not a time-format");
lf[37]=C_h_intern(&lf[37],1,"s");
lf[38]=C_static_lambda_info(C_heaptop,22,"(time-format . arg107)");
lf[39]=C_h_intern(&lf[39],5,"pause");
lf[40]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[41]=C_static_lambda_info(C_heaptop,7,"(pause)");
lf[42]=C_h_intern(&lf[42],7,"paused\077");
lf[43]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[44]=C_static_lambda_info(C_heaptop,9,"(paused\077)");
lf[45]=C_h_intern(&lf[45],4,"cont");
lf[46]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[47]=C_static_lambda_info(C_heaptop,6,"(cont)");
lf[48]=C_h_intern(&lf[48],4,"stop");
lf[49]=C_static_string(C_heaptop,17,"Not an integer id");
lf[50]=C_static_lambda_info(C_heaptop,15,"(do121 tail123)");
lf[51]=C_static_lambda_info(C_heaptop,18,"(stop . procid120)");
lf[52]=C_h_intern(&lf[52],4,"hush");
lf[53]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[54]=C_static_lambda_info(C_heaptop,6,"(hush)");
lf[57]=C_h_intern(&lf[57],7,"sprintf");
lf[58]=C_static_lambda_info(C_heaptop,23,"(ferror str134 args135)");
lf[59]=C_h_intern(&lf[59],7,"mp:note");
lf[60]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[61]=C_static_lambda_info(C_heaptop,46,"(mp:note time172 dur173 key174 amp175 chan176)");
lf[62]=C_h_intern(&lf[62],5,"mp:on");
lf[63]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[64]=C_static_lambda_info(C_heaptop,37,"(mp:on time177 key178 vel179 chan180)");
lf[65]=C_h_intern(&lf[65],6,"mp:off");
lf[66]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[67]=C_static_lambda_info(C_heaptop,38,"(mp:off time181 key182 vel183 chan184)");
lf[68]=C_h_intern(&lf[68],7,"mp:prog");
lf[69]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[70]=C_static_lambda_info(C_heaptop,33,"(mp:prog time185 prog186 chan187)");
lf[71]=C_h_intern(&lf[71],7,"mp:ctrl");
lf[72]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[73]=C_static_lambda_info(C_heaptop,40,"(mp:ctrl time188 ctrl189 val190 chan191)");
lf[74]=C_h_intern(&lf[74],9,"mp:alloff");
lf[75]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[76]=C_static_lambda_info(C_heaptop,11,"(mp:alloff)");
lf[77]=C_h_intern(&lf[77],8,"mp:micro");
lf[78]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[79]=C_static_lambda_info(C_heaptop,18,"(mp:micro divs192)");
lf[80]=C_h_intern(&lf[80],9,"mp:inhook");
lf[81]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[82]=C_static_lambda_info(C_heaptop,19,"(mp:inhook func193)");
lf[83]=C_h_intern(&lf[83],14,"return-to-host");
lf[84]=C_h_intern(&lf[84],4,"else");
lf[85]=C_h_intern(&lf[85],4,"cond");
lf[86]=C_h_intern(&lf[86],6,"lambda");
lf[87]=C_h_intern(&lf[87],7,"elapsed");
lf[88]=C_h_intern(&lf[88],1,"x");
lf[89]=C_h_intern(&lf[89],4,"set!");
lf[90]=C_h_intern(&lf[90],4,"wait");
lf[91]=C_h_intern(&lf[91],4,"let*");
lf[92]=C_h_intern(&lf[92],5,"quote");
lf[93]=C_h_intern(&lf[93],3,"exn");
lf[94]=C_h_intern(&lf[94],7,"message");
lf[95]=C_h_intern(&lf[95],27,"condition-property-accessor");
lf[96]=C_h_intern(&lf[96],6,"printf");
lf[97]=C_static_string(C_heaptop,47,">>> Aborting process at time ~S:~%    Error: ~S");
lf[98]=C_h_intern(&lf[98],22,"with-exception-handler");
lf[99]=C_h_intern(&lf[99],30,"call-with-current-continuation");
lf[100]=C_h_intern(&lf[100],10,"\003sysappend");
lf[101]=C_h_intern(&lf[101],6,"safety");
lf[102]=C_h_intern(&lf[102],4,"cdar");
lf[103]=C_static_string(C_heaptop,19,"unknown declaration");
lf[104]=C_h_intern(&lf[104],4,"caar");
lf[105]=C_static_string(C_heaptop,31,"declaration not list (decl val)");
lf[106]=C_static_lambda_info(C_heaptop,15,"(do219 decl221)");
lf[107]=C_h_intern(&lf[107],7,"declare");
lf[108]=C_h_intern(&lf[108],6,"gensym");
lf[109]=C_h_intern(&lf[109],6,"append");
lf[110]=C_h_intern(&lf[110],5,"\000null");
lf[111]=C_static_string(C_heaptop,41,"binding clause not list (var init [step])");
lf[112]=C_static_lambda_info(C_heaptop,15,"(do203 tail205)");
lf[113]=C_static_string(C_heaptop,36,"go stopping clause missing test form");
lf[114]=C_static_string(C_heaptop,29,"go stopping clause not a list");
lf[115]=C_static_string(C_heaptop,22,"go bindings not a list");
lf[116]=C_static_lambda_info(C_heaptop,42,"(a1543 bindings194 terminate195 . body196)");
lf[117]=C_h_intern(&lf[117],18,"\003sysregister-macro");
lf[118]=C_h_intern(&lf[118],2,"go");
lf[119]=C_h_intern(&lf[119],15,"hash-table-set!");
lf[120]=C_static_string(C_heaptop,9,"mp:inhook");
tmp=C_intern(C_heaptop,9,"mp:inhook");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000func");
C_save(tmp);
tmp=C_SCHEME_FALSE;
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[121]=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
lf[122]=C_static_string(C_heaptop,8,"mp:micro");
tmp=C_intern(C_heaptop,8,"mp:micro");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000divs");
C_save(tmp);
tmp=C_fix(1);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[123]=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
lf[124]=C_static_string(C_heaptop,9,"mp:alloff");
tmp=C_intern(C_heaptop,9,"mp:alloff");
C_save(tmp);
tmp=C_SCHEME_END_OF_LIST;
lf[125]=C_h_pair(C_restore,tmp);
lf[126]=C_static_string(C_heaptop,7,"mp:ctrl");
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
lf[127]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[128]=C_static_string(C_heaptop,7,"mp:prog");
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
lf[129]=C_h_list(4,C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(4);
lf[130]=C_static_string(C_heaptop,6,"mp:off");
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
lf[131]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[132]=C_static_string(C_heaptop,5,"mp:on");
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
lf[133]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[134]=C_static_string(C_heaptop,7,"mp:note");
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
lf[135]=C_h_list(6,C_pick(5),C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(6);
lf[136]=C_static_lambda_info(C_heaptop,15,"(do163 tail165)");
lf[137]=C_static_string(C_heaptop,37,"~S found duplicate keyword \047~S\047 in ~S");
lf[138]=C_static_string(C_heaptop,33,"~S missing value for keyword \047~S\047");
lf[139]=C_static_string(C_heaptop,53,"~S found invalid keyword \047~S\047~%Available keywords: ~S");
lf[140]=C_h_intern(&lf[140],7,"\003sysmap");
lf[141]=C_h_intern(&lf[141],3,"car");
lf[142]=C_static_string(C_heaptop,32,"~S expected keyword but got \047~S\047");
lf[143]=C_h_intern(&lf[143],8,"keyword\077");
lf[144]=C_static_string(C_heaptop,35,"~S expected ~A arguments but got ~A");
lf[145]=C_static_lambda_info(C_heaptop,28,"(do146 key148 arg149 pos150)");
lf[146]=C_static_string(C_heaptop,24,"~S is an invalid message");
lf[147]=C_static_lambda_info(C_heaptop,7,"(a1001)");
lf[148]=C_h_intern(&lf[148],14,"hash-table-ref");
lf[149]=C_h_intern(&lf[149],14,"symbol->string");
lf[150]=C_static_lambda_info(C_heaptop,25,"(a1549 mess170 . data171)");
lf[151]=C_h_intern(&lf[151],4,"send");
lf[152]=C_h_intern(&lf[152],10,"*messages*");
lf[153]=C_h_intern(&lf[153],14,"string->symbol");
lf[154]=C_static_string(C_heaptop,51,"message function not string, symbol or list of both");
lf[155]=C_static_lambda_info(C_heaptop,23,"(a1555 func128 info129)");
lf[156]=C_h_intern(&lf[156],19,"define-send-message");
lf[157]=C_h_intern(&lf[157],15,"make-hash-table");
lf[158]=C_h_intern(&lf[158],6,"equal\077");
lf[159]=C_static_lambda_info(C_heaptop,10,"(toplevel)");
C_register_lf2(lf,160,create_ptable());
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_288,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_library_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k286 */
static void C_ccall f_288(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_288,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_291,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_eval_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k289 in k286 */
static void C_ccall f_291(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_291,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_294,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k292 in k289 in k286 */
static void C_ccall f_294(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_294,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_297,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k295 in k292 in k289 in k286 */
static void C_ccall f_297(C_word c,C_word t0,C_word t1){
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
C_word ab[45],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_297,2,t0,t1);}
t2=C_mutate((C_word*)lf[0]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_299,a[2]=lf[2],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[3]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_313,a[2]=lf[4],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate((C_word*)lf[5]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_356,a[2]=lf[6],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate((C_word*)lf[7]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_359,a[2]=lf[8],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate(&lf[9],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_371,a[2]=lf[12],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate(&lf[13],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_380,a[2]=lf[15],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate(&lf[16],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_424,a[2]=lf[18],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate((C_word*)lf[19]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_446,a[2]=lf[28],tmp=(C_word)a,a+=3,tmp));
t10=C_mutate((C_word*)lf[29]+1,*((C_word*)lf[5]+1));
t11=C_mutate((C_word*)lf[30]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_614,a[2]=lf[38],tmp=(C_word)a,a+=3,tmp));
t12=C_mutate((C_word*)lf[39]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_677,a[2]=lf[41],tmp=(C_word)a,a+=3,tmp));
t13=C_mutate((C_word*)lf[42]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_686,a[2]=lf[44],tmp=(C_word)a,a+=3,tmp));
t14=C_mutate((C_word*)lf[45]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_692,a[2]=lf[47],tmp=(C_word)a,a+=3,tmp));
t15=C_mutate((C_word*)lf[48]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_701,a[2]=lf[51],tmp=(C_word)a,a+=3,tmp));
t16=C_mutate((C_word*)lf[52]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_759,a[2]=lf[54],tmp=(C_word)a,a+=3,tmp));
t17=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_770,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 256  make-hash-table");
t18=C_retrieve(lf[157]);
((C_proc3)C_retrieve_proc(t18))(3,t18,t17,*((C_word*)lf[158]+1));}

/* k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_770(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_770,2,t0,t1);}
t2=C_mutate(&lf[55],t1);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_773,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1556,a[2]=lf[155],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 258  ##sys#register-macro");
t5=C_retrieve(lf[117]);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,lf[156],t4);}

/* a1555 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1556(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_1556,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_1560,a[2]=t6,a[3]=t1,a[4]=t3,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t4)[1]))){
t8=(C_word)C_i_car(((C_word*)t4)[1]);
t9=C_set_block_item(t6,0,t8);
t10=(C_word)C_i_cadr(((C_word*)t4)[1]);
t11=C_set_block_item(t4,0,t10);
t12=t7;
f_1560(2,t12,t11);}
else{
if(C_truep((C_word)C_i_stringp(((C_word*)t4)[1]))){
t8=C_set_block_item(t6,0,((C_word*)t4)[1]);
t9=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1593,a[2]=t7,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 265  string->symbol");
t10=*((C_word*)lf[153]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)t4)[1]);}
else{
if(C_truep((C_word)C_i_symbolp(((C_word*)t4)[1]))){
t8=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1603,a[2]=t7,a[3]=t6,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 267  symbol->string");
t9=*((C_word*)lf[149]+1);
((C_proc3)C_retrieve_proc(t9))(3,t9,t8,((C_word*)t4)[1]);}
else{
C_trace("ChickenBridge.scm: 269  error");
t8=*((C_word*)lf[35]+1);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,lf[154]);}}}}

/* k1601 in a1555 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1603(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_1560(2,t3,t2);}

/* k1591 in a1555 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1593(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_1560(2,t3,t2);}

/* k1558 in a1555 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1560(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1560,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[4]);
t3=(C_word)C_a_i_list(&a,2,lf[92],t2);
t4=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_a_i_list(&a,4,lf[119],lf[152],((C_word*)((C_word*)t0)[2])[1],t3));}

/* k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_773(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_773,2,t0,t1);}
t2=C_mutate(&lf[56],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_775,a[2]=lf[58],tmp=(C_word)a,a+=3,tmp));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1012,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1550,a[2]=lf[150],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 345  ##sys#register-macro");
t5=C_retrieve(lf[117]);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,lf[151],t4);}

/* a1549 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1550(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+6)){
C_save_and_reclaim((void*)tr3r,(void*)f_1550r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_1550r(t0,t1,t2,t3);}}

static void C_ccall f_1550r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a=C_alloc(6);
t4=t3;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_789,a[2]=t1,a[3]=t5,tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_symbolp(t2))){
C_trace("ChickenBridge.scm: 276  symbol->string");
t7=*((C_word*)lf[149]+1);
((C_proc3)C_retrieve_proc(t7))(3,t7,t6,t2);}
else{
t7=t6;
f_789(2,t7,t2);}}

/* k787 in a1549 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_789(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_789,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_792,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1002,a[2]=lf[147],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 277  hash-table-ref");
t4=*((C_word*)lf[148]+1);
((C_proc5)C_retrieve_proc(t4))(5,t4,t2,lf[55],t1,t3);}

/* a1001 in k787 in a1549 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1002(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1002,2,t0,t1);}
t2=t1;
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}

/* k790 in k787 in a1549 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_792(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_792,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_795,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=t1;
if(C_truep(t3)){
t4=t2;
f_795(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 278  ferror");
f_775(t2,lf[146],(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]));}}

/* k793 in k790 in k787 in a1549 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_795(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_795,2,t0,t1);}
t2=((C_word*)((C_word*)t0)[5])[1];
t3=(C_word)C_i_car(((C_word*)t0)[4]);
t4=(C_word)C_i_cdr(((C_word*)t0)[4]);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(C_word)C_i_length(t4);
t8=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_807,a[2]=t7,a[3]=t2,a[4]=((C_word*)t0)[2],a[5]=t6,a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[3],a[8]=t4,a[9]=t3,tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 285  append");
t9=*((C_word*)lf[109]+1);
((C_proc4)C_retrieve_proc(t9))(4,t9,t8,t4,C_SCHEME_END_OF_LIST);}

/* k805 in k793 in k790 in k787 in a1549 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_807(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[19],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_807,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_810,a[2]=((C_word*)t0)[7],a[3]=((C_word*)t0)[8],a[4]=t1,a[5]=((C_word*)t0)[9],tmp=(C_word)a,a+=6,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_855,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[5],a[8]=t4,a[9]=((C_word*)t0)[6],a[10]=lf[145],tmp=(C_word)a,a+=11,tmp));
t6=((C_word*)t4)[1];
f_855(t6,t2,C_SCHEME_FALSE,C_SCHEME_FALSE,C_fix(0));}

/* do146 in k805 in k793 in k790 in k787 in a1549 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_fcall f_855(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
C_save_and_reclaim((void*)trf_855,NULL,5,t0,t1,t2,t3,t4);}
t5=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[9])[1]))){
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,C_SCHEME_FALSE);}
else{
t8=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_865,a[2]=t7,a[3]=t6,a[4]=t5,a[5]=t1,a[6]=((C_word*)t0)[8],tmp=(C_word)a,a+=7,tmp);
t9=(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_871,a[2]=((C_word*)t0)[2],a[3]=t7,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=t6,a[8]=((C_word*)t0)[6],a[9]=t5,a[10]=((C_word*)t0)[9],a[11]=t8,a[12]=((C_word*)t0)[7],tmp=(C_word)a,a+=13,tmp);
t10=((C_word*)((C_word*)t0)[7])[1];
if(C_truep(t10)){
t11=t9;
f_871(2,t11,C_SCHEME_FALSE);}
else{
t11=(C_word)C_i_car(((C_word*)((C_word*)t0)[9])[1]);
C_trace("ChickenBridge.scm: 296  keyword?");
t12=C_retrieve(lf[143]);
((C_proc3)C_retrieve_proc(t12))(3,t12,t9,t11);}}}

/* k869 in do146 in k805 in k793 in k790 in k787 in a1549 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_871(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_871,2,t0,t1);}
if(C_truep(t1)){
t2=C_set_block_item(((C_word*)t0)[12],0,C_SCHEME_TRUE);
t3=((C_word*)t0)[11];
f_865(t3,t2);}
else{
t2=((C_word*)((C_word*)t0)[12])[1];
if(C_truep(t2)){
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[10])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[9])+1,t3);
t5=(C_word)C_i_assoc(((C_word*)((C_word*)t0)[9])[1],((C_word*)t0)[8]);
t6=C_mutate(((C_word *)((C_word*)t0)[7])+1,t5);
t7=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[10])[1]);
t8=C_mutate(((C_word *)((C_word*)t0)[10])+1,t7);
t9=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_925,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[9],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[11],a[6]=((C_word*)t0)[10],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t10=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_980,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[9],a[5]=((C_word*)t0)[5],a[6]=t9,a[7]=((C_word*)t0)[10],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 316  keyword?");
t11=C_retrieve(lf[143]);
((C_proc3)C_retrieve_proc(t11))(3,t11,t10,((C_word*)((C_word*)t0)[9])[1]);}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_881,a[2]=((C_word*)t0)[11],a[3]=((C_word*)t0)[10],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[6],tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_nequalp(((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]))){
t4=(C_word)C_i_length(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 306  ferror");
f_775(t3,lf[144],(C_word)C_a_i_list(&a,3,((C_word*)t0)[5],((C_word*)t0)[2],t4));}
else{
t4=t3;
f_881(2,t4,C_SCHEME_UNDEFINED);}}}}

/* k879 in k869 in do146 in k805 in k793 in k790 in k787 in a1549 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_881(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_881,2,t0,t1);}
t2=(C_word)C_i_list_tail(((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]);
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
t4=(C_word)C_i_set_car(t2,t3);
t5=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[3])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t5);
t7=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[4])[1],C_fix(1));
t8=C_mutate(((C_word *)((C_word*)t0)[4])+1,t7);
t9=((C_word*)t0)[2];
f_865(t9,t8);}

/* k978 in k869 in do146 in k805 in k793 in k790 in k787 in a1549 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_980(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_980,2,t0,t1);}
if(C_truep(t1)){
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[7])[1]))){
C_trace("ChickenBridge.scm: 320  ferror");
f_775(((C_word*)t0)[6],lf[138],(C_word)C_a_i_list(&a,2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]));}
else{
t2=((C_word*)((C_word*)t0)[3])[1];
if(C_truep(t2)){
t3=((C_word*)t0)[6];
f_925(2,t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_976,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
C_trace("map");
t4=*((C_word*)lf[140]+1);
((C_proc4)(void*)(*((C_word*)t4+1)))(4,t4,t3,*((C_word*)lf[141]+1),((C_word*)t0)[2]);}}}
else{
C_trace("ChickenBridge.scm: 317  ferror");
f_775(((C_word*)t0)[6],lf[142],(C_word)C_a_i_list(&a,2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]));}}

/* k974 in k978 in k869 in do146 in k805 in k793 in k790 in k787 in a1549 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_976(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_976,2,t0,t1);}
C_trace("ChickenBridge.scm: 323  ferror");
f_775(((C_word*)t0)[4],lf[139],(C_word)C_a_i_list(&a,3,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1));}

/* k923 in k869 in do146 in k805 in k793 in k790 in k787 in a1549 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_925(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[14],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_925,2,t0,t1);}
t2=(C_word)C_i_member(((C_word*)((C_word*)t0)[8])[1],((C_word*)t0)[7]);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_931,a[2]=((C_word*)t0)[5],a[3]=t2,a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
if(C_truep(t2)){
t4=t3;
f_931(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 330  ferror");
f_775(t3,lf[137],(C_word)C_a_i_list(&a,3,((C_word*)t0)[4],((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]));}}

/* k929 in k923 in k869 in do146 in k805 in k793 in k790 in k787 in a1549 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_931(C_word c,C_word t0,C_word t1){
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
f_865(t6,t5);}

/* k863 in do146 in k805 in k793 in k790 in k787 in a1549 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_fcall f_865(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[6])[1];
f_855(t2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k808 in k805 in k793 in k790 in k787 in a1549 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_810(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_810,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_815,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=lf[136],tmp=(C_word)a,a+=7,tmp));
t5=((C_word*)t3)[1];
f_815(t5,((C_word*)t0)[2],((C_word*)t0)[4]);}

/* do163 in k808 in k805 in k793 in k790 in k787 in a1549 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_fcall f_815(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_815,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[5],((C_word*)t0)[4]));}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_828,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_member(t4,((C_word*)t0)[2]))){
t5=(C_word)C_i_car(t2);
t6=(C_word)C_i_cadr(t5);
t7=t3;
f_828(t7,(C_word)C_i_set_car(t2,t6));}
else{
t5=t3;
f_828(t5,C_SCHEME_UNDEFINED);}}}

/* k826 in do163 in k808 in k805 in k793 in k790 in k787 in a1549 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_fcall f_828(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_815(t3,((C_word*)t0)[2],t2);}

/* k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1012(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_1012,2,t0,t1);}
t2=C_mutate((C_word*)lf[59]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1014,a[2]=lf[61],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[62]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1020,a[2]=lf[64],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate((C_word*)lf[65]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1026,a[2]=lf[67],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate((C_word*)lf[68]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1032,a[2]=lf[70],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[71]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1038,a[2]=lf[73],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate((C_word*)lf[74]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1044,a[2]=lf[76],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate((C_word*)lf[77]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1050,a[2]=lf[79],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate((C_word*)lf[80]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1056,a[2]=lf[82],tmp=(C_word)a,a+=3,tmp));
t10=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1063,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 372  hash-table-set!");
t11=C_retrieve(lf[119]);
((C_proc5)C_retrieve_proc(t11))(5,t11,t10,lf[55],lf[134],lf[135]);}

/* k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1063(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1063,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1066,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 373  hash-table-set!");
t3=C_retrieve(lf[119]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[55],lf[132],lf[133]);}

/* k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1066(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1066,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1069,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 374  hash-table-set!");
t3=C_retrieve(lf[119]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[55],lf[130],lf[131]);}

/* k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1069(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1069,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1072,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 375  hash-table-set!");
t3=C_retrieve(lf[119]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[55],lf[128],lf[129]);}

/* k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1072(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1072,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1075,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 376  hash-table-set!");
t3=C_retrieve(lf[119]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[55],lf[126],lf[127]);}

/* k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1075(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1075,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1078,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 377  hash-table-set!");
t3=C_retrieve(lf[119]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[55],lf[124],lf[125]);}

/* k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1078(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1078,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1081,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 378  hash-table-set!");
t3=C_retrieve(lf[119]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[55],lf[122],lf[123]);}

/* k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1081(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1081,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1084,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 379  hash-table-set!");
t3=C_retrieve(lf[119]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[55],lf[120],lf[121]);}

/* k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1084(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1084,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1087,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1544,a[2]=lf[116],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 386  ##sys#register-macro");
t4=C_retrieve(lf[117]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,lf[118],t3);}

/* a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1544(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+17)){
C_save_and_reclaim((void*)tr4r,(void*)f_1544r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest(a,C_rest_count(0));
f_1544r(t0,t1,t2,t3,t4);}}

static void C_ccall f_1544r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
t13=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_1102,a[2]=t2,a[3]=t12,a[4]=t6,a[5]=t10,a[6]=t1,a[7]=t8,a[8]=t3,tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(t2))){
t14=t13;
f_1102(2,t14,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 395  error");
t14=*((C_word*)lf[35]+1);
((C_proc4)C_retrieve_proc(t14))(4,t14,t13,lf[115],t2);}}

/* k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1102(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1102,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_1105,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(((C_word*)t0)[8]))){
if(C_truep((C_word)C_i_nullp(((C_word*)t0)[8]))){
C_trace("ChickenBridge.scm: 399  error");
t3=*((C_word*)lf[35]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,lf[113]);}
else{
t3=t2;
f_1105(2,t3,C_SCHEME_UNDEFINED);}}
else{
C_trace("ChickenBridge.scm: 397  error");
t3=*((C_word*)lf[35]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t2,lf[114],((C_word*)t0)[8]);}}

/* k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1105(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1105,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_1108,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],tmp=(C_word)a,a+=8,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_1379,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[7],a[5]=t4,a[6]=lf[112],tmp=(C_word)a,a+=7,tmp));
t6=((C_word*)t4)[1];
f_1379(t6,t2,((C_word*)t0)[2]);}

/* do203 in k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_fcall f_1379(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_1379,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1389,a[2]=t1,a[3]=((C_word*)t0)[5],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_1399,a[2]=t3,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=t2,tmp=(C_word)a,a+=7,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1487,a[2]=t4,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t7=(C_word)C_i_car(t2);
t8=(C_word)C_i_length(t7);
C_trace("ChickenBridge.scm: 403  <");
C_lessp(5,0,t6,C_fix(0),t8,C_fix(4));}
else{
t6=t4;
f_1399(t6,C_SCHEME_FALSE);}}}

/* k1485 in do203 in k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1487(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=(C_word)C_i_car(t2);
t4=((C_word*)t0)[2];
f_1399(t4,(C_word)C_i_symbolp(t3));}
else{
t2=((C_word*)t0)[2];
f_1399(t2,C_SCHEME_FALSE);}}

/* k1397 in do203 in k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_fcall f_1399(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_1399,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[6]);
t3=(C_word)C_i_car(t2);
t4=(C_word)C_i_car(((C_word*)t0)[6]);
t5=(C_word)C_i_cadr(t4);
t6=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_1408,a[2]=t5,a[3]=t3,a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[5],tmp=(C_word)a,a+=8,tmp);
t7=(C_word)C_i_car(((C_word*)t0)[6]);
t8=(C_word)C_i_cddr(t7);
if(C_truep((C_word)C_i_nullp(t8))){
t9=t6;
f_1408(t9,lf[110]);}
else{
t9=(C_word)C_i_car(((C_word*)t0)[6]);
t10=t6;
f_1408(t10,(C_word)C_i_caddr(t9));}}
else{
t2=(C_word)C_i_car(((C_word*)t0)[6]);
C_trace("ChickenBridge.scm: 416  error");
t3=*((C_word*)lf[35]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[2],lf[111],t2);}}

/* k1406 in k1397 in do203 in k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_fcall f_1408(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1408,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_1412,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t3=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 411  append");
t4=*((C_word*)lf[109]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,((C_word*)((C_word*)t0)[7])[1],t3);}

/* k1410 in k1406 in k1397 in do203 in k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1412(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1412,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_1416,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
t4=(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 412  append");
t5=*((C_word*)lf[109]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,((C_word*)((C_word*)t0)[7])[1],t4);}

/* k1414 in k1410 in k1406 in k1397 in do203 in k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1416(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_1416,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1420,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1424,a[2]=((C_word*)t0)[5],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_eqp(((C_word*)t0)[3],lf[110]);
if(C_truep(t5)){
t6=t4;
f_1424(t6,C_SCHEME_END_OF_LIST);}
else{
t6=(C_word)C_a_i_list(&a,3,lf[89],((C_word*)t0)[2],((C_word*)t0)[3]);
t7=t4;
f_1424(t7,(C_word)C_a_i_list(&a,1,t6));}}

/* k1422 in k1414 in k1410 in k1406 in k1397 in do203 in k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_fcall f_1424(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 413  append");
t2=*((C_word*)lf[109]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k1418 in k1414 in k1410 in k1406 in k1397 in do203 in k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1420(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_1389(2,t3,t2);}

/* k1387 in do203 in k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1389(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_1379(t3,((C_word*)t0)[2],t2);}

/* k1106 in k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1108(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1108,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_1111,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 418  gensym");
t3=C_retrieve(lf[108]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k1109 in k1106 in k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1111(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1111,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_1114,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 419  gensym");
t3=C_retrieve(lf[108]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k1112 in k1109 in k1106 in k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1114(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1114,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_1117,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 420  gensym");
t3=C_retrieve(lf[108]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k1115 in k1112 in k1109 in k1106 in k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1117(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1117,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_1120,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],a[10]=((C_word*)t0)[9],tmp=(C_word)a,a+=11,tmp);
C_trace("ChickenBridge.scm: 421  gensym");
t3=C_retrieve(lf[108]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k1118 in k1115 in k1112 in k1109 in k1106 in k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1120(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_1120,2,t0,t1);}
t2=C_SCHEME_TRUE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_SCHEME_END_OF_LIST;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_1123,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=t3,a[7]=((C_word*)t0)[5],a[8]=((C_word*)t0)[6],a[9]=((C_word*)t0)[7],a[10]=((C_word*)t0)[8],a[11]=((C_word*)t0)[9],a[12]=t5,a[13]=((C_word*)t0)[10],tmp=(C_word)a,a+=14,tmp);
t7=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1272,a[2]=t6,a[3]=t3,a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)((C_word*)t0)[3])[1]))){
t8=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
if(C_truep((C_word)C_i_pairp(t8))){
t9=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1373,a[2]=t7,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 427  caar");
t10=*((C_word*)lf[104]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)((C_word*)t0)[3])[1]);}
else{
t9=t7;
f_1272(t9,C_SCHEME_FALSE);}}
else{
t8=t7;
f_1272(t8,C_SCHEME_FALSE);}}

/* k1371 in k1118 in k1115 in k1112 in k1109 in k1106 in k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1373(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_1272(t2,(C_word)C_eqp(t1,lf[107]));}

/* k1270 in k1118 in k1115 in k1112 in k1109 in k1106 in k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_fcall f_1272(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1272,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1279,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 428  cdar");
t3=*((C_word*)lf[102]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)((C_word*)t0)[4])[1]);}
else{
t2=((C_word*)t0)[2];
f_1123(2,t2,C_SCHEME_UNDEFINED);}}

/* k1277 in k1270 in k1118 in k1115 in k1112 in k1109 in k1106 in k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1279(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1279,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_1281,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=lf[106],tmp=(C_word)a,a+=6,tmp));
t5=((C_word*)t3)[1];
f_1281(t5,((C_word*)t0)[2],t1);}

/* do219 in k1277 in k1270 in k1118 in k1115 in k1112 in k1109 in k1106 in k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_fcall f_1281(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_1281,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[4])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[4])+1,t3);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,t4);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1295,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1305,a[2]=t2,a[3]=((C_word*)t0)[2],a[4]=t3,tmp=(C_word)a,a+=5,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1353,a[2]=t4,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 432  cdar");
t7=*((C_word*)lf[102]+1);
((C_proc3)C_retrieve_proc(t7))(3,t7,t6,t2);}
else{
t6=t4;
f_1305(t6,C_SCHEME_FALSE);}}}

/* k1351 in do219 in k1277 in k1270 in k1118 in k1115 in k1112 in k1109 in k1106 in k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1353(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_1305(t2,(C_word)C_i_pairp(t1));}

/* k1303 in do219 in k1277 in k1270 in k1118 in k1115 in k1112 in k1109 in k1106 in k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_fcall f_1305(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1305,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1308,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 433  caar");
t3=*((C_word*)lf[104]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)t0)[2]);}
else{
t2=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 439  error");
t3=*((C_word*)lf[35]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[4],lf[105],t2);}}

/* k1306 in k1303 in do219 in k1277 in k1270 in k1118 in k1115 in k1112 in k1109 in k1106 in k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1308(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1308,2,t0,t1);}
t2=(C_word)C_eqp(t1,lf[101]);
if(C_truep(t2)){
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1329,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 435  cdar");
t4=*((C_word*)lf[102]+1);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)t0)[2]);}
else{
t3=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 438  error");
t4=*((C_word*)lf[35]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,((C_word*)t0)[4],lf[103],t3);}}

/* k1327 in k1306 in k1303 in do219 in k1277 in k1270 in k1118 in k1115 in k1112 in k1109 in k1106 in k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1329(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep((C_word)C_i_car(t1))){
t2=((C_word*)t0)[3];
f_1295(2,t2,C_SCHEME_UNDEFINED);}
else{
t2=C_set_block_item(((C_word*)t0)[2],0,C_SCHEME_FALSE);
t3=((C_word*)t0)[3];
f_1295(2,t3,t2);}}

/* k1293 in do219 in k1277 in k1270 in k1118 in k1115 in k1112 in k1109 in k1106 in k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1295(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_1281(t3,((C_word*)t0)[2],t2);}

/* k1121 in k1118 in k1115 in k1112 in k1109 in k1106 in k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1123(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1123,2,t0,t1);}
t2=(C_word)C_i_car(((C_word*)t0)[13]);
t3=(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_1261,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],a[10]=((C_word*)t0)[10],a[11]=((C_word*)t0)[11],a[12]=((C_word*)t0)[12],a[13]=t2,tmp=(C_word)a,a+=14,tmp);
t4=(C_word)C_i_cdr(((C_word*)t0)[13]);
t5=(C_word)C_a_i_list(&a,1,C_fix(-1));
C_trace("ChickenBridge.scm: 390  ##sys#append");
t6=*((C_word*)lf[100]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t3,t4,t5);}

/* k1259 in k1121 in k1118 in k1115 in k1112 in k1109 in k1106 in k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1261(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1261,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[13],t1);
t3=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_1245,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],a[8]=((C_word*)t0)[10],a[9]=((C_word*)t0)[11],a[10]=((C_word*)t0)[12],a[11]=t2,tmp=(C_word)a,a+=12,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1249,a[2]=((C_word*)t0)[3],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_a_i_list(&a,1,((C_word*)t0)[10]);
C_trace("ChickenBridge.scm: 390  ##sys#append");
t6=*((C_word*)lf[100]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t4,((C_word*)((C_word*)t0)[2])[1],t5);}

/* k1247 in k1259 in k1121 in k1118 in k1115 in k1112 in k1109 in k1106 in k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1249(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 390  ##sys#append");
t2=*((C_word*)lf[100]+1);
((C_proc4)(void*)(*((C_word*)t2+1)))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k1243 in k1259 in k1121 in k1118 in k1115 in k1112 in k1109 in k1106 in k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1245(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_1245,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,lf[84],t1);
t3=(C_word)C_a_i_list(&a,3,lf[85],((C_word*)t0)[11],t2);
t4=C_mutate(((C_word *)((C_word*)t0)[10])+1,t3);
t5=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_1130,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],a[5]=((C_word*)t0)[10],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],tmp=(C_word)a,a+=8,tmp);
if(C_truep(((C_word*)((C_word*)t0)[4])[1])){
t6=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
t7=(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]);
t8=(C_word)C_a_i_list(&a,2,lf[92],lf[93]);
t9=(C_word)C_a_i_list(&a,2,lf[92],lf[94]);
t10=(C_word)C_a_i_list(&a,3,lf[95],t8,t9);
t11=(C_word)C_a_i_list(&a,2,t10,((C_word*)t0)[2]);
t12=(C_word)C_a_i_list(&a,4,lf[96],lf[97],((C_word*)t0)[9],t11);
t13=(C_word)C_a_i_list(&a,2,((C_word*)t0)[3],C_fix(-2));
t14=(C_word)C_a_i_list(&a,4,lf[86],t7,t12,t13);
t15=(C_word)C_a_i_list(&a,3,lf[86],C_SCHEME_END_OF_LIST,((C_word*)((C_word*)t0)[10])[1]);
t16=(C_word)C_a_i_list(&a,3,lf[98],t14,t15);
t17=(C_word)C_a_i_list(&a,3,lf[86],t6,t16);
t18=(C_word)C_a_i_list(&a,2,lf[99],t17);
t19=C_mutate(((C_word *)((C_word*)t0)[10])+1,t18);
t20=t5;
f_1130(t20,t19);}
else{
t6=t5;
f_1130(t6,C_SCHEME_UNDEFINED);}}

/* k1128 in k1243 in k1259 in k1121 in k1118 in k1115 in k1112 in k1109 in k1106 in k1103 in k1100 in a1543 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_fcall f_1130(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_1130,NULL,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,((C_word*)t0)[7]);
t3=(C_word)C_a_i_list(&a,2,((C_word*)t0)[6],C_fix(0));
t4=(C_word)C_a_i_list(&a,3,lf[86],C_SCHEME_END_OF_LIST,((C_word*)t0)[7]);
t5=(C_word)C_a_i_list(&a,2,lf[87],t4);
t6=(C_word)C_a_i_list(&a,1,lf[88]);
t7=(C_word)C_a_i_list(&a,3,lf[89],((C_word*)t0)[6],lf[88]);
t8=(C_word)C_a_i_list(&a,3,lf[86],t6,t7);
t9=(C_word)C_a_i_list(&a,2,lf[90],t8);
t10=(C_word)C_a_i_list(&a,3,t3,t5,t9);
t11=(C_word)C_a_i_list(&a,3,lf[91],t10,((C_word*)((C_word*)t0)[5])[1]);
t12=(C_word)C_a_i_list(&a,3,lf[86],t2,t11);
t13=(C_word)C_a_i_list(&a,3,lf[86],((C_word*)((C_word*)t0)[4])[1],t12);
t14=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t14+1)))(2,t14,(C_word)C_a_i_cons(&a,2,t13,((C_word*)((C_word*)t0)[2])[1]));}

/* k1085 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1087(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1087,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1542,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 483  return-to-host");
t3=C_retrieve(lf[83]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k1540 in k1085 in k1082 in k1079 in k1076 in k1073 in k1070 in k1067 in k1064 in k1061 in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1542(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_UNDEFINED);}

/* mp:inhook in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1056(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1056,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 368  error");
t3=*((C_word*)lf[35]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[81]);}

/* mp:micro in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1050(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1050,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 366  error");
t3=*((C_word*)lf[35]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[78]);}

/* mp:alloff in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1044(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1044,2,t0,t1);}
C_trace("ChickenBridge.scm: 364  error");
t2=*((C_word*)lf[35]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,t1,lf[75]);}

/* mp:ctrl in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1038(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_1038,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 362  error");
t6=*((C_word*)lf[35]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[72]);}

/* mp:prog in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1032(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_1032,5,t0,t1,t2,t3,t4);}
C_trace("ChickenBridge.scm: 360  error");
t5=*((C_word*)lf[35]+1);
((C_proc3)C_retrieve_proc(t5))(3,t5,t1,lf[69]);}

/* mp:off in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1026(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_1026,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 358  error");
t6=*((C_word*)lf[35]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[66]);}

/* mp:on in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1020(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_1020,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 356  error");
t6=*((C_word*)lf[35]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[63]);}

/* mp:note in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_1014(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
C_word tmp;
C_word t7;
C_word t8;
C_word ab[8],*a=ab;
if(c!=7) C_bad_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr7,(void*)f_1014,7,t0,t1,t2,t3,t4,t5,t6);}
t7=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_331,a[2]=t1,a[3]=t6,a[4]=t5,a[5]=t4,a[6]=t3,a[7]=t2,tmp=(C_word)a,a+=8,tmp);
C_trace("##sys#gc");
t8=C_retrieve(lf[11]);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,C_SCHEME_FALSE);}

/* k329 in mp:note in k1010 in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_331(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_331,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[7]);
t4=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[6]);
t5=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[5]);
t6=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[4]);
t7=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[3]);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub17,a[2]=lf[60],tmp=(C_word)a,a+=3,tmp);
((C_proc8)C_retrieve_proc(t8))(8,t8,((C_word*)t0)[2],t2,t3,t4,t5,t6,t7);}

/* ferror in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_fcall f_775(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_775,NULL,3,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_783,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_apply(5,0,t4,C_retrieve(lf[57]),t2,t3);}

/* k781 in ferror in k771 in k768 in k295 in k292 in k289 in k286 */
static void C_ccall f_783(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 273  error");
t2=*((C_word*)lf[35]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* hush in k295 in k292 in k289 in k286 */
static void C_ccall f_759(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_759,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_763,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_441,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[11]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k439 in hush in k295 in k292 in k289 in k286 */
static void C_ccall f_441(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_441,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub70,a[2]=lf[53],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k761 in hush in k295 in k292 in k289 in k286 */
static void C_ccall f_763(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 250  values");
C_values(2,0,((C_word*)t0)[2]);}

/* stop in k295 in k292 in k289 in k286 */
static void C_ccall f_701(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+9)){
C_save_and_reclaim((void*)tr2r,(void*)f_701r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_701r(t0,t1,t2);}}

static void C_ccall f_701r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a=C_alloc(9);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_705,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 240  scheduler-stop");
f_424(t3,C_fix(-1));}
else{
t4=C_SCHEME_UNDEFINED;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_set_block_item(t5,0,(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_719,a[2]=t5,a[3]=lf[50],tmp=(C_word)a,a+=4,tmp));
t7=((C_word*)t5)[1];
f_719(t7,t3,t2);}}

/* do121 in stop in k295 in k292 in k289 in k286 */
static void C_fcall f_719(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_719,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_729,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_fixnump(t4))){
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 244  scheduler-stop");
f_424(t3,t5);}
else{
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 245  error");
t6=*((C_word*)lf[35]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t3,lf[49],t5);}}}

/* k727 in do121 in stop in k295 in k292 in k289 in k286 */
static void C_ccall f_729(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_719(t3,((C_word*)t0)[2],t2);}

/* k703 in stop in k295 in k292 in k289 in k286 */
static void C_ccall f_705(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 246  values");
C_values(2,0,((C_word*)t0)[2]);}

/* cont in k295 in k292 in k289 in k286 */
static void C_ccall f_692(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_692,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_696,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_419,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[11]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k417 in cont in k295 in k292 in k289 in k286 */
static void C_ccall f_419(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_419,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub60,a[2]=lf[46],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k694 in cont in k295 in k292 in k289 in k286 */
static void C_ccall f_696(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 236  values");
C_values(2,0,((C_word*)t0)[2]);}

/* paused? in k295 in k292 in k289 in k286 */
static void C_ccall f_686(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_686,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_401,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t3=C_retrieve(lf[11]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,C_SCHEME_FALSE);}

/* k399 in paused? in k295 in k292 in k289 in k286 */
static void C_ccall f_401(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_401,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub52,a[2]=lf[43],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* pause in k295 in k292 in k289 in k286 */
static void C_ccall f_677(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_677,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_681,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_410,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[11]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k408 in pause in k295 in k292 in k289 in k286 */
static void C_ccall f_410(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_410,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub56,a[2]=lf[40],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k679 in pause in k295 in k292 in k289 in k286 */
static void C_ccall f_681(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 229  values");
C_values(2,0,((C_word*)t0)[2]);}

/* time-format in k295 in k292 in k289 in k286 */
static void C_ccall f_614(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+11)){
C_save_and_reclaim((void*)tr2rv,(void*)f_614r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_614r(t0,t1,t2);}}

static void C_ccall f_614r(C_word t0,C_word t1,C_word t2){
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
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_627,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_366,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t5=C_retrieve(lf[11]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,C_SCHEME_FALSE);}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
t4=(C_word)C_i_eqvp(t3,lf[33]);
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_639,a[2]=t2,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
if(C_truep(t4)){
t6=t5;
f_639(t6,t4);}
else{
t6=(C_word)C_eqp(t3,C_fix(1));
t7=t5;
f_639(t7,(C_truep(t6)?t6:(C_word)C_eqp(t3,lf[37])));}}}

/* k637 in time-format in k295 in k292 in k289 in k286 */
static void C_fcall f_639(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a;
if(C_truep(t1)){
t2=C_mutate((C_word*)lf[29]+1,*((C_word*)lf[7]+1));
C_trace("ChickenBridge.scm: 218  scheduler-set-time-milliseconds");
f_371(((C_word*)t0)[4],C_SCHEME_FALSE);}
else{
t2=(C_word)C_eqp(((C_word*)t0)[3],C_fix(1000));
t3=(C_truep(t2)?t2:(C_word)C_eqp(((C_word*)t0)[3],lf[34]));
if(C_truep(t3)){
t4=C_mutate((C_word*)lf[29]+1,*((C_word*)lf[5]+1));
C_trace("ChickenBridge.scm: 222  scheduler-set-time-milliseconds");
f_371(((C_word*)t0)[4],C_SCHEME_TRUE);}
else{
t4=(C_word)C_i_vector_ref(((C_word*)t0)[2],C_fix(0));
C_trace("ChickenBridge.scm: 225  error");
t5=*((C_word*)lf[35]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,((C_word*)t0)[4],lf[36],t4);}}}

/* k364 in time-format in k295 in k292 in k289 in k286 */
static void C_ccall f_366(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_366,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub32,a[2]=lf[32],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k625 in time-format in k295 in k292 in k289 in k286 */
static void C_ccall f_627(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_truep(t1)?C_fix(1000):lf[31]));}

/* sprout in k295 in k292 in k289 in k286 */
static void C_ccall f_446(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+12)){
C_save_and_reclaim((void*)tr3r,(void*)f_446r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_446r(t0,t1,t2,t3);}}

static void C_ccall f_446r(C_word t0,C_word t1,C_word t2,C_word t3){
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
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_448,a[2]=t2,a[3]=lf[23],tmp=(C_word)a,a+=4,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_560,a[2]=t4,a[3]=lf[24],tmp=(C_word)a,a+=4,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_565,a[2]=t5,a[3]=lf[25],tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("def-start80101");
t7=t6;
f_565(t7,t1);}
else{
t7=(C_word)C_i_car(t3);
t8=(C_word)C_i_cdr(t3);
if(C_truep((C_word)C_i_nullp(t8))){
C_trace("def-id8199");
t9=t5;
f_560(t9,t1,t7);}
else{
t9=(C_word)C_i_car(t8);
t10=(C_word)C_i_cdr(t8);
if(C_truep((C_word)C_i_nullp(t10))){
C_trace("body7883");
t11=t4;
f_448(t11,t1,t7,t9);}
else{
C_trace("##sys#error");
t11=*((C_word*)lf[26]+1);
((C_proc4)(void*)(*((C_word*)t11+1)))(4,t11,t1,lf[27],t10);}}}}

/* def-start80 in sprout in k295 in k292 in k289 in k286 */
static void C_fcall f_565(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_565,NULL,2,t0,t1);}
C_trace("def-id8199");
t2=((C_word*)t0)[2];
f_560(t2,t1,C_fix(0));}

/* def-id81 in sprout in k295 in k292 in k289 in k286 */
static void C_fcall f_560(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_560,NULL,3,t0,t1,t2);}
C_trace("body7883");
t3=((C_word*)t0)[2];
f_448(t3,t1,t2,C_fix(-1));}

/* body78 in sprout in k295 in k292 in k289 in k286 */
static void C_fcall f_448(C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)trf_448,NULL,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_450,a[2]=t4,a[3]=lf[20],tmp=(C_word)a,a+=4,tmp);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_478,a[2]=t5,a[3]=lf[21],tmp=(C_word)a,a+=4,tmp);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_508,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t0)[2]))){
t9=C_SCHEME_UNDEFINED;
t10=(*a=C_VECTOR_TYPE|1,a[1]=t9,tmp=(C_word)a,a+=2,tmp);
t11=C_set_block_item(t10,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_519,a[2]=t6,a[3]=t7,a[4]=t10,a[5]=((C_word*)t0)[2],a[6]=lf[22],tmp=(C_word)a,a+=7,tmp));
t12=((C_word*)t10)[1];
f_519(t12,t8,((C_word*)t0)[2]);}
else{
t9=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_551,a[2]=((C_word*)t0)[2],a[3]=t8,tmp=(C_word)a,a+=4,tmp);
t10=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_555,a[2]=t7,a[3]=((C_word*)t0)[2],a[4]=t9,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 204  nextstart");
t11=t6;
f_450(t11,t10);}}

/* k553 in body78 in sprout in k295 in k292 in k289 in k286 */
static void C_ccall f_555(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_555,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_559,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 204  nextid");
t3=((C_word*)t0)[2];
f_478(t3,t2);}

/* k557 in k553 in body78 in sprout in k295 in k292 in k289 in k286 */
static void C_ccall f_559(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 204  scheduler-sprout");
f_380(((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k549 in body78 in sprout in k295 in k292 in k289 in k286 */
static void C_ccall f_551(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
f_508(2,t2,((C_word*)t0)[2]);}

/* do92 in body78 in sprout in k295 in k292 in k289 in k286 */
static void C_fcall f_519(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_519,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,((C_word*)t0)[5]);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_529,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_544,a[2]=((C_word*)t0)[3],a[3]=t4,a[4]=t3,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 202  nextstart");
t6=((C_word*)t0)[2];
f_450(t6,t5);}}

/* k542 in do92 in body78 in sprout in k295 in k292 in k289 in k286 */
static void C_ccall f_544(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_544,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_548,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 202  nextid");
t3=((C_word*)t0)[2];
f_478(t3,t2);}

/* k546 in k542 in do92 in body78 in sprout in k295 in k292 in k289 in k286 */
static void C_ccall f_548(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 202  scheduler-sprout");
f_380(((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k527 in do92 in body78 in sprout in k295 in k292 in k289 in k286 */
static void C_ccall f_529(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_519(t3,((C_word*)t0)[2],t2);}

/* k506 in body78 in sprout in k295 in k292 in k289 in k286 */
static void C_ccall f_508(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 208  values");
C_values(2,0,((C_word*)t0)[2]);}

/* nextid in body78 in sprout in k295 in k292 in k289 in k286 */
static void C_fcall f_478(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_478,NULL,2,t0,t1);}
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

/* nextstart in body78 in sprout in k295 in k292 in k289 in k286 */
static void C_fcall f_450(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_450,NULL,2,t0,t1);}
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

/* scheduler-stop in k295 in k292 in k289 in k286 */
static void C_fcall f_424(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_424,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_428,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[11]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k426 in scheduler-stop in k295 in k292 in k289 in k286 */
static void C_ccall f_428(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_428,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_fixnum_argumentp(((C_word*)t0)[3]);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub65,a[2]=lf[17],tmp=(C_word)a,a+=3,tmp);
((C_proc4)C_retrieve_proc(t4))(4,t4,((C_word*)t0)[2],t2,t3);}

/* scheduler-sprout in k295 in k292 in k289 in k286 */
static void C_fcall f_380(C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_380,NULL,4,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_384,a[2]=t2,a[3]=t1,a[4]=t4,a[5]=t3,tmp=(C_word)a,a+=6,tmp);
C_trace("##sys#gc");
t6=C_retrieve(lf[11]);
((C_proc3)C_retrieve_proc(t6))(3,t6,t5,C_SCHEME_FALSE);}

/* k382 in scheduler-sprout in k295 in k292 in k289 in k286 */
static void C_ccall f_384(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_384,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[5]);
t4=(C_word)C_i_foreign_fixnum_argumentp(((C_word*)t0)[4]);
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub45,a[2]=lf[14],tmp=(C_word)a,a+=3,tmp);
((C_proc6)C_retrieve_proc(t5))(6,t5,((C_word*)t0)[3],t2,((C_word*)t0)[2],t3,t4);}

/* scheduler-set-time-milliseconds in k295 in k292 in k289 in k286 */
static void C_fcall f_371(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_371,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_375,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[11]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k373 in scheduler-set-time-milliseconds in k295 in k292 in k289 in k286 */
static void C_ccall f_375(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_375,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub37,a[2]=lf[10],tmp=(C_word)a,a+=3,tmp);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[3],t2,((C_word*)t0)[2]);}

/* current-time-seconds in k295 in k292 in k289 in k286 */
static void C_ccall f_359(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_359,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub29(t2));}

/* current-time-milliseconds in k295 in k292 in k289 in k286 */
static void C_ccall f_356(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_356,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub26(t2));}

/* print-error in k295 in k292 in k289 in k286 */
static void C_ccall f_313(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_313,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_318,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[1]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_318(2,t4,C_SCHEME_FALSE);}}

/* k316 in print-error in k295 in k292 in k289 in k286 */
static void C_ccall f_318(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub7(C_SCHEME_UNDEFINED,t1));}

/* print-message in k295 in k292 in k289 in k286 */
static void C_ccall f_299(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_299,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_304,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[1]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_304(2,t4,C_SCHEME_FALSE);}}

/* k302 in print-message in k295 in k292 in k289 in k286 */
static void C_ccall f_304(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub1(C_SCHEME_UNDEFINED,t1));}

#ifdef C_ENABLE_PTABLES
static C_PTABLE_ENTRY ptable[127] = {
{"toplevelChickenBridge.scm",(void*)C_grace_toplevel},
{"f_288ChickenBridge.scm",(void*)f_288},
{"f_291ChickenBridge.scm",(void*)f_291},
{"f_294ChickenBridge.scm",(void*)f_294},
{"f_297ChickenBridge.scm",(void*)f_297},
{"f_770ChickenBridge.scm",(void*)f_770},
{"f_1556ChickenBridge.scm",(void*)f_1556},
{"f_1603ChickenBridge.scm",(void*)f_1603},
{"f_1593ChickenBridge.scm",(void*)f_1593},
{"f_1560ChickenBridge.scm",(void*)f_1560},
{"f_773ChickenBridge.scm",(void*)f_773},
{"f_1550ChickenBridge.scm",(void*)f_1550},
{"f_789ChickenBridge.scm",(void*)f_789},
{"f_1002ChickenBridge.scm",(void*)f_1002},
{"f_792ChickenBridge.scm",(void*)f_792},
{"f_795ChickenBridge.scm",(void*)f_795},
{"f_807ChickenBridge.scm",(void*)f_807},
{"f_855ChickenBridge.scm",(void*)f_855},
{"f_871ChickenBridge.scm",(void*)f_871},
{"f_881ChickenBridge.scm",(void*)f_881},
{"f_980ChickenBridge.scm",(void*)f_980},
{"f_976ChickenBridge.scm",(void*)f_976},
{"f_925ChickenBridge.scm",(void*)f_925},
{"f_931ChickenBridge.scm",(void*)f_931},
{"f_865ChickenBridge.scm",(void*)f_865},
{"f_810ChickenBridge.scm",(void*)f_810},
{"f_815ChickenBridge.scm",(void*)f_815},
{"f_828ChickenBridge.scm",(void*)f_828},
{"f_1012ChickenBridge.scm",(void*)f_1012},
{"f_1063ChickenBridge.scm",(void*)f_1063},
{"f_1066ChickenBridge.scm",(void*)f_1066},
{"f_1069ChickenBridge.scm",(void*)f_1069},
{"f_1072ChickenBridge.scm",(void*)f_1072},
{"f_1075ChickenBridge.scm",(void*)f_1075},
{"f_1078ChickenBridge.scm",(void*)f_1078},
{"f_1081ChickenBridge.scm",(void*)f_1081},
{"f_1084ChickenBridge.scm",(void*)f_1084},
{"f_1544ChickenBridge.scm",(void*)f_1544},
{"f_1102ChickenBridge.scm",(void*)f_1102},
{"f_1105ChickenBridge.scm",(void*)f_1105},
{"f_1379ChickenBridge.scm",(void*)f_1379},
{"f_1487ChickenBridge.scm",(void*)f_1487},
{"f_1399ChickenBridge.scm",(void*)f_1399},
{"f_1408ChickenBridge.scm",(void*)f_1408},
{"f_1412ChickenBridge.scm",(void*)f_1412},
{"f_1416ChickenBridge.scm",(void*)f_1416},
{"f_1424ChickenBridge.scm",(void*)f_1424},
{"f_1420ChickenBridge.scm",(void*)f_1420},
{"f_1389ChickenBridge.scm",(void*)f_1389},
{"f_1108ChickenBridge.scm",(void*)f_1108},
{"f_1111ChickenBridge.scm",(void*)f_1111},
{"f_1114ChickenBridge.scm",(void*)f_1114},
{"f_1117ChickenBridge.scm",(void*)f_1117},
{"f_1120ChickenBridge.scm",(void*)f_1120},
{"f_1373ChickenBridge.scm",(void*)f_1373},
{"f_1272ChickenBridge.scm",(void*)f_1272},
{"f_1279ChickenBridge.scm",(void*)f_1279},
{"f_1281ChickenBridge.scm",(void*)f_1281},
{"f_1353ChickenBridge.scm",(void*)f_1353},
{"f_1305ChickenBridge.scm",(void*)f_1305},
{"f_1308ChickenBridge.scm",(void*)f_1308},
{"f_1329ChickenBridge.scm",(void*)f_1329},
{"f_1295ChickenBridge.scm",(void*)f_1295},
{"f_1123ChickenBridge.scm",(void*)f_1123},
{"f_1261ChickenBridge.scm",(void*)f_1261},
{"f_1249ChickenBridge.scm",(void*)f_1249},
{"f_1245ChickenBridge.scm",(void*)f_1245},
{"f_1130ChickenBridge.scm",(void*)f_1130},
{"f_1087ChickenBridge.scm",(void*)f_1087},
{"f_1542ChickenBridge.scm",(void*)f_1542},
{"f_1056ChickenBridge.scm",(void*)f_1056},
{"f_1050ChickenBridge.scm",(void*)f_1050},
{"f_1044ChickenBridge.scm",(void*)f_1044},
{"f_1038ChickenBridge.scm",(void*)f_1038},
{"f_1032ChickenBridge.scm",(void*)f_1032},
{"f_1026ChickenBridge.scm",(void*)f_1026},
{"f_1020ChickenBridge.scm",(void*)f_1020},
{"f_1014ChickenBridge.scm",(void*)f_1014},
{"f_331ChickenBridge.scm",(void*)f_331},
{"f_775ChickenBridge.scm",(void*)f_775},
{"f_783ChickenBridge.scm",(void*)f_783},
{"f_759ChickenBridge.scm",(void*)f_759},
{"f_441ChickenBridge.scm",(void*)f_441},
{"f_763ChickenBridge.scm",(void*)f_763},
{"f_701ChickenBridge.scm",(void*)f_701},
{"f_719ChickenBridge.scm",(void*)f_719},
{"f_729ChickenBridge.scm",(void*)f_729},
{"f_705ChickenBridge.scm",(void*)f_705},
{"f_692ChickenBridge.scm",(void*)f_692},
{"f_419ChickenBridge.scm",(void*)f_419},
{"f_696ChickenBridge.scm",(void*)f_696},
{"f_686ChickenBridge.scm",(void*)f_686},
{"f_401ChickenBridge.scm",(void*)f_401},
{"f_677ChickenBridge.scm",(void*)f_677},
{"f_410ChickenBridge.scm",(void*)f_410},
{"f_681ChickenBridge.scm",(void*)f_681},
{"f_614ChickenBridge.scm",(void*)f_614},
{"f_639ChickenBridge.scm",(void*)f_639},
{"f_366ChickenBridge.scm",(void*)f_366},
{"f_627ChickenBridge.scm",(void*)f_627},
{"f_446ChickenBridge.scm",(void*)f_446},
{"f_565ChickenBridge.scm",(void*)f_565},
{"f_560ChickenBridge.scm",(void*)f_560},
{"f_448ChickenBridge.scm",(void*)f_448},
{"f_555ChickenBridge.scm",(void*)f_555},
{"f_559ChickenBridge.scm",(void*)f_559},
{"f_551ChickenBridge.scm",(void*)f_551},
{"f_519ChickenBridge.scm",(void*)f_519},
{"f_544ChickenBridge.scm",(void*)f_544},
{"f_548ChickenBridge.scm",(void*)f_548},
{"f_529ChickenBridge.scm",(void*)f_529},
{"f_508ChickenBridge.scm",(void*)f_508},
{"f_478ChickenBridge.scm",(void*)f_478},
{"f_450ChickenBridge.scm",(void*)f_450},
{"f_424ChickenBridge.scm",(void*)f_424},
{"f_428ChickenBridge.scm",(void*)f_428},
{"f_380ChickenBridge.scm",(void*)f_380},
{"f_384ChickenBridge.scm",(void*)f_384},
{"f_371ChickenBridge.scm",(void*)f_371},
{"f_375ChickenBridge.scm",(void*)f_375},
{"f_359ChickenBridge.scm",(void*)f_359},
{"f_356ChickenBridge.scm",(void*)f_356},
{"f_313ChickenBridge.scm",(void*)f_313},
{"f_318ChickenBridge.scm",(void*)f_318},
{"f_299ChickenBridge.scm",(void*)f_299},
{"f_304ChickenBridge.scm",(void*)f_304},
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
