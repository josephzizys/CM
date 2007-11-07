/* Generated from ChickenBridge.scm by the CHICKEN compiler
   http://www.call-with-current-continuation.org
   2007-11-07 07:11
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
#include "OutputQueue.h"

//
// Console Window code
//

void print_mess(char * st)
{
// ((GraceApp *)GraceApp::getInstance())->getConsole()->printMessage( String(st));
   printf("%s", st);
}

void print_error(char * st)
{
// ((GraceApp *)GraceApp::getInstance())->getConsole()->printError( String(st));
   printf("%s", st);
}

//
// MIDI Port code
//

void mp_note(double time, double dur, float k, float v, float c) {
 float on[3];
 float off[3];
 on[0] =  off[0] = k;
 on[1] = v;
 off[1] = 0.0;
 on[2] = off[2] =  c;
 ((GraceApp *)GraceApp::getInstance())->outputQueue->outputNodes.lockArray();
 ((GraceApp *)GraceApp::getInstance())->outputQueue->addNode(time, on, 3);
 ((GraceApp *)GraceApp::getInstance())->outputQueue->addNode(time+dur, off, 3); 
 ((GraceApp *)GraceApp::getInstance())->outputQueue->outputNodes.unlockArray();
}

void mp_on(double time, float k, float v, float c) {
 float vals[3];
 vals[0] = k;
 vals[1] = v;
 vals[2] = c;
 ((GraceApp *)GraceApp::getInstance())->outputQueue->outputNodes.lockArray();
 ((GraceApp *)GraceApp::getInstance())->outputQueue->addNode(time, vals, 3);
 ((GraceApp *)GraceApp::getInstance())->outputQueue->outputNodes.unlockArray();
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
  ((GraceApp *)GraceApp::getInstance())->outputQueue->clear();
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


/* from k438 in hush in k294 in k291 in k288 in k285 */
C_noret_decl(stub69)
static void C_ccall stub69(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub69(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_hush();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k432 */
C_noret_decl(stub64)
static void C_ccall stub64(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0) C_noret;
static void C_ccall stub64(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_unfix(C_a0);
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_stop(t0);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k416 in cont in k294 in k291 in k288 in k285 */
C_noret_decl(stub59)
static void C_ccall stub59(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub59(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_cont();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k407 in pause in k294 in k291 in k288 in k285 */
C_noret_decl(stub55)
static void C_ccall stub55(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub55(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_pause();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k398 in paused? in k294 in k291 in k288 in k285 */
C_noret_decl(stub51)
static void C_ccall stub51(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub51(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
C_r=C_mk_bool(scheduler_is_paused());
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k392 */
C_noret_decl(stub44)
static void C_ccall stub44(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2) C_noret;
static void C_ccall stub44(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
C_word t0=(C_word )(C_a0);
double t1=(double )C_c_double(C_a1);
int t2=(int )C_unfix(C_a2);
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_sprout(t0,t1,t2);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k372 in scheduler-set-time-milliseconds in k294 in k291 in k288 in k285 */
C_noret_decl(stub36)
static void C_ccall stub36(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0) C_noret;
static void C_ccall stub36(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_truep(C_a0);
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_set_time_milliseconds(t0);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k363 in time-format in k294 in k291 in k288 in k285 */
C_noret_decl(stub31)
static void C_ccall stub31(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub31(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
C_r=C_mk_bool(scheduler_is_time_milliseconds());
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from current-time-seconds in k294 in k291 in k288 in k285 */
#define return(x) C_cblock C_r = (C_flonum(&C_a,(x))); goto C_ret; C_cblockend
static C_word C_fcall stub28(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub28(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
 C_return( (float) (Time::getMillisecondCounterHiRes() / 1000.0));
C_ret:
#undef return

return C_r;}

/* from current-time-milliseconds in k294 in k291 in k288 in k285 */
#define return(x) C_cblock C_r = (C_fix((C_word)(x))); goto C_ret; C_cblockend
static C_word C_fcall stub26(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub26(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
 C_return( (int) Time::getMillisecondCounterHiRes());
C_ret:
#undef return

return C_r;}

/* from k351 */
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

/* from k315 in print-error in k294 in k291 in k288 in k285 */
static C_word C_fcall stub7(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub7(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_error(t0);
return C_r;}

/* from k301 in print-message in k294 in k291 in k288 in k285 */
static C_word C_fcall stub1(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub1(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_mess(t0);
return C_r;}

C_noret_decl(C_grace_toplevel)
C_externexport void C_ccall C_grace_toplevel(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_287)
static void C_ccall f_287(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_290)
static void C_ccall f_290(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_293)
static void C_ccall f_293(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_296)
static void C_ccall f_296(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_769)
static void C_ccall f_769(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1555)
static void C_ccall f_1555(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_1602)
static void C_ccall f_1602(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1592)
static void C_ccall f_1592(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1559)
static void C_ccall f_1559(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_772)
static void C_ccall f_772(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1549)
static void C_ccall f_1549(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_1549)
static void C_ccall f_1549r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_788)
static void C_ccall f_788(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1001)
static void C_ccall f_1001(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_791)
static void C_ccall f_791(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_794)
static void C_ccall f_794(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_806)
static void C_ccall f_806(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_854)
static void C_fcall f_854(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_870)
static void C_ccall f_870(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_880)
static void C_ccall f_880(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_979)
static void C_ccall f_979(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_975)
static void C_ccall f_975(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_924)
static void C_ccall f_924(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_930)
static void C_ccall f_930(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_864)
static void C_fcall f_864(C_word t0,C_word t1) C_noret;
C_noret_decl(f_809)
static void C_ccall f_809(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_814)
static void C_fcall f_814(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_827)
static void C_fcall f_827(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1011)
static void C_ccall f_1011(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1062)
static void C_ccall f_1062(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1065)
static void C_ccall f_1065(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1068)
static void C_ccall f_1068(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1071)
static void C_ccall f_1071(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1074)
static void C_ccall f_1074(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1077)
static void C_ccall f_1077(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1080)
static void C_ccall f_1080(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1083)
static void C_ccall f_1083(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1543)
static void C_ccall f_1543(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_1543)
static void C_ccall f_1543r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_1101)
static void C_ccall f_1101(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1104)
static void C_ccall f_1104(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1378)
static void C_fcall f_1378(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1486)
static void C_ccall f_1486(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1398)
static void C_fcall f_1398(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1407)
static void C_fcall f_1407(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1411)
static void C_ccall f_1411(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1415)
static void C_ccall f_1415(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1423)
static void C_fcall f_1423(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1419)
static void C_ccall f_1419(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1388)
static void C_ccall f_1388(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1107)
static void C_ccall f_1107(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1110)
static void C_ccall f_1110(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1113)
static void C_ccall f_1113(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1116)
static void C_ccall f_1116(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1119)
static void C_ccall f_1119(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1372)
static void C_ccall f_1372(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1271)
static void C_fcall f_1271(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1278)
static void C_ccall f_1278(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1280)
static void C_fcall f_1280(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1352)
static void C_ccall f_1352(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1304)
static void C_fcall f_1304(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1307)
static void C_ccall f_1307(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1328)
static void C_ccall f_1328(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1294)
static void C_ccall f_1294(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1122)
static void C_ccall f_1122(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1260)
static void C_ccall f_1260(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1248)
static void C_ccall f_1248(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1244)
static void C_ccall f_1244(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1129)
static void C_fcall f_1129(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1086)
static void C_ccall f_1086(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1541)
static void C_ccall f_1541(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1055)
static void C_ccall f_1055(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1049)
static void C_ccall f_1049(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1043)
static void C_ccall f_1043(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1037)
static void C_ccall f_1037(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_1031)
static void C_ccall f_1031(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_1025)
static void C_ccall f_1025(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_1019)
static void C_ccall f_1019(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_1013)
static void C_ccall f_1013(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_330)
static void C_ccall f_330(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_774)
static void C_fcall f_774(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_782)
static void C_ccall f_782(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_758)
static void C_ccall f_758(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_440)
static void C_ccall f_440(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_762)
static void C_ccall f_762(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_700)
static void C_ccall f_700(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_700)
static void C_ccall f_700r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_718)
static void C_fcall f_718(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_728)
static void C_ccall f_728(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_704)
static void C_ccall f_704(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_691)
static void C_ccall f_691(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_418)
static void C_ccall f_418(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_695)
static void C_ccall f_695(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_685)
static void C_ccall f_685(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_400)
static void C_ccall f_400(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_676)
static void C_ccall f_676(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_409)
static void C_ccall f_409(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_680)
static void C_ccall f_680(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_613)
static void C_ccall f_613(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_613)
static void C_ccall f_613r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_638)
static void C_fcall f_638(C_word t0,C_word t1) C_noret;
C_noret_decl(f_365)
static void C_ccall f_365(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_626)
static void C_ccall f_626(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_445)
static void C_ccall f_445(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_445)
static void C_ccall f_445r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_564)
static void C_fcall f_564(C_word t0,C_word t1) C_noret;
C_noret_decl(f_559)
static void C_fcall f_559(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_447)
static void C_fcall f_447(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_554)
static void C_ccall f_554(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_558)
static void C_ccall f_558(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_550)
static void C_ccall f_550(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_518)
static void C_fcall f_518(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_543)
static void C_ccall f_543(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_547)
static void C_ccall f_547(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_528)
static void C_ccall f_528(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_507)
static void C_ccall f_507(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_477)
static void C_fcall f_477(C_word t0,C_word t1) C_noret;
C_noret_decl(f_449)
static void C_fcall f_449(C_word t0,C_word t1) C_noret;
C_noret_decl(f_423)
static void C_fcall f_423(C_word t0,C_word t1) C_noret;
C_noret_decl(f_427)
static void C_ccall f_427(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_379)
static void C_fcall f_379(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_383)
static void C_ccall f_383(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_370)
static void C_fcall f_370(C_word t0,C_word t1) C_noret;
C_noret_decl(f_374)
static void C_ccall f_374(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_358)
static void C_ccall f_358(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_355)
static void C_ccall f_355(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_312)
static void C_ccall f_312(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_317)
static void C_ccall f_317(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_298)
static void C_ccall f_298(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_303)
static void C_ccall f_303(C_word c,C_word t0,C_word t1) C_noret;

C_noret_decl(trf_854)
static void C_fcall trf_854(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_854(void *dummy){
C_word t4=C_pick(0);
C_word t3=C_pick(1);
C_word t2=C_pick(2);
C_word t1=C_pick(3);
C_word t0=C_pick(4);
C_adjust_stack(-5);
f_854(t0,t1,t2,t3,t4);}

C_noret_decl(trf_864)
static void C_fcall trf_864(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_864(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_864(t0,t1);}

C_noret_decl(trf_814)
static void C_fcall trf_814(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_814(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_814(t0,t1,t2);}

C_noret_decl(trf_827)
static void C_fcall trf_827(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_827(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_827(t0,t1);}

C_noret_decl(trf_1378)
static void C_fcall trf_1378(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1378(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1378(t0,t1,t2);}

C_noret_decl(trf_1398)
static void C_fcall trf_1398(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1398(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1398(t0,t1);}

C_noret_decl(trf_1407)
static void C_fcall trf_1407(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1407(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1407(t0,t1);}

C_noret_decl(trf_1423)
static void C_fcall trf_1423(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1423(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1423(t0,t1);}

C_noret_decl(trf_1271)
static void C_fcall trf_1271(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1271(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1271(t0,t1);}

C_noret_decl(trf_1280)
static void C_fcall trf_1280(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1280(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1280(t0,t1,t2);}

C_noret_decl(trf_1304)
static void C_fcall trf_1304(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1304(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1304(t0,t1);}

C_noret_decl(trf_1129)
static void C_fcall trf_1129(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1129(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1129(t0,t1);}

C_noret_decl(trf_774)
static void C_fcall trf_774(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_774(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_774(t0,t1,t2);}

C_noret_decl(trf_718)
static void C_fcall trf_718(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_718(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_718(t0,t1,t2);}

C_noret_decl(trf_638)
static void C_fcall trf_638(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_638(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_638(t0,t1);}

C_noret_decl(trf_564)
static void C_fcall trf_564(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_564(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_564(t0,t1);}

C_noret_decl(trf_559)
static void C_fcall trf_559(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_559(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_559(t0,t1,t2);}

C_noret_decl(trf_447)
static void C_fcall trf_447(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_447(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_447(t0,t1,t2,t3);}

C_noret_decl(trf_518)
static void C_fcall trf_518(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_518(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_518(t0,t1,t2);}

C_noret_decl(trf_477)
static void C_fcall trf_477(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_477(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_477(t0,t1);}

C_noret_decl(trf_449)
static void C_fcall trf_449(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_449(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_449(t0,t1);}

C_noret_decl(trf_423)
static void C_fcall trf_423(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_423(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_423(t0,t1);}

C_noret_decl(trf_379)
static void C_fcall trf_379(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_379(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_379(t0,t1,t2,t3);}

C_noret_decl(trf_370)
static void C_fcall trf_370(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_370(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_370(t0,t1);}

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
if(!C_demand_2(1164)){
C_save(t1);
C_rereclaim2(1164*sizeof(C_word), 1);
t1=C_restore;}
a=C_alloc(3);
C_initialize_lf(lf,160);
lf[0]=C_h_intern(&lf[0],13,"print-message");
lf[1]=C_h_intern(&lf[1],17,"\003sysmake-c-string");
lf[2]=C_static_lambda_info(C_heaptop,19,"(print-message a04)");
lf[3]=C_h_intern(&lf[3],11,"print-error");
lf[4]=C_static_lambda_info(C_heaptop,18,"(print-error a610)");
lf[6]=C_static_lambda_info(C_heaptop,27,"(current-time-milliseconds)");
lf[8]=C_static_lambda_info(C_heaptop,22,"(current-time-seconds)");
lf[10]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[11]=C_h_intern(&lf[11],6,"\003sysgc");
lf[12]=C_static_lambda_info(C_heaptop,39,"(scheduler-set-time-milliseconds a3538)");
lf[14]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[15]=C_static_lambda_info(C_heaptop,36,"(scheduler-sprout a4346 a4247 a4148)");
lf[17]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[18]=C_static_lambda_info(C_heaptop,22,"(scheduler-stop a6366)");
lf[19]=C_h_intern(&lf[19],6,"sprout");
lf[20]=C_static_lambda_info(C_heaptop,11,"(nextstart)");
lf[21]=C_static_lambda_info(C_heaptop,8,"(nextid)");
lf[22]=C_static_lambda_info(C_heaptop,10,"(do91 p93)");
lf[23]=C_static_lambda_info(C_heaptop,21,"(body77 start83 id84)");
lf[24]=C_static_lambda_info(C_heaptop,21,"(def-id80 %start7599)");
lf[25]=C_static_lambda_info(C_heaptop,13,"(def-start79)");
lf[26]=C_h_intern(&lf[26],9,"\003syserror");
lf[27]=C_static_string(C_heaptop,27,"too many optional arguments");
lf[28]=C_static_lambda_info(C_heaptop,24,"(sprout proc73 . args74)");
lf[29]=C_h_intern(&lf[29],3,"now");
lf[30]=C_h_intern(&lf[30],11,"time-format");
lf[31]=C_flonum(C_heaptop,1.0);
lf[32]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[33]=C_flonum(C_heaptop,1.0);
lf[34]=C_h_intern(&lf[34],1,"m");
lf[35]=C_h_intern(&lf[35],5,"error");
lf[36]=C_static_string(C_heaptop,17,"not a time-format");
lf[37]=C_h_intern(&lf[37],1,"s");
lf[38]=C_static_lambda_info(C_heaptop,22,"(time-format . arg106)");
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
lf[50]=C_static_lambda_info(C_heaptop,15,"(do120 tail122)");
lf[51]=C_static_lambda_info(C_heaptop,18,"(stop . procid119)");
lf[52]=C_h_intern(&lf[52],4,"hush");
lf[53]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[54]=C_static_lambda_info(C_heaptop,6,"(hush)");
lf[57]=C_h_intern(&lf[57],7,"sprintf");
lf[58]=C_static_lambda_info(C_heaptop,23,"(ferror str133 args134)");
lf[59]=C_h_intern(&lf[59],7,"mp:note");
lf[60]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[61]=C_static_lambda_info(C_heaptop,46,"(mp:note time171 dur172 key173 amp174 chan175)");
lf[62]=C_h_intern(&lf[62],5,"mp:on");
lf[63]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[64]=C_static_lambda_info(C_heaptop,37,"(mp:on time176 key177 vel178 chan179)");
lf[65]=C_h_intern(&lf[65],6,"mp:off");
lf[66]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[67]=C_static_lambda_info(C_heaptop,38,"(mp:off time180 key181 vel182 chan183)");
lf[68]=C_h_intern(&lf[68],7,"mp:prog");
lf[69]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[70]=C_static_lambda_info(C_heaptop,33,"(mp:prog time184 prog185 chan186)");
lf[71]=C_h_intern(&lf[71],7,"mp:ctrl");
lf[72]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[73]=C_static_lambda_info(C_heaptop,40,"(mp:ctrl time187 ctrl188 val189 chan190)");
lf[74]=C_h_intern(&lf[74],9,"mp:alloff");
lf[75]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[76]=C_static_lambda_info(C_heaptop,11,"(mp:alloff)");
lf[77]=C_h_intern(&lf[77],8,"mp:micro");
lf[78]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[79]=C_static_lambda_info(C_heaptop,18,"(mp:micro divs191)");
lf[80]=C_h_intern(&lf[80],9,"mp:inhook");
lf[81]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[82]=C_static_lambda_info(C_heaptop,19,"(mp:inhook func192)");
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
lf[106]=C_static_lambda_info(C_heaptop,15,"(do218 decl220)");
lf[107]=C_h_intern(&lf[107],7,"declare");
lf[108]=C_h_intern(&lf[108],6,"gensym");
lf[109]=C_h_intern(&lf[109],6,"append");
lf[110]=C_h_intern(&lf[110],5,"\000null");
lf[111]=C_static_string(C_heaptop,41,"binding clause not list (var init [step])");
lf[112]=C_static_lambda_info(C_heaptop,15,"(do202 tail204)");
lf[113]=C_static_string(C_heaptop,36,"go stopping clause missing test form");
lf[114]=C_static_string(C_heaptop,29,"go stopping clause not a list");
lf[115]=C_static_string(C_heaptop,22,"go bindings not a list");
lf[116]=C_static_lambda_info(C_heaptop,42,"(a1542 bindings193 terminate194 . body195)");
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
lf[136]=C_static_lambda_info(C_heaptop,15,"(do162 tail164)");
lf[137]=C_static_string(C_heaptop,37,"~S found duplicate keyword \047~S\047 in ~S");
lf[138]=C_static_string(C_heaptop,33,"~S missing value for keyword \047~S\047");
lf[139]=C_static_string(C_heaptop,53,"~S found invalid keyword \047~S\047~%Available keywords: ~S");
lf[140]=C_h_intern(&lf[140],7,"\003sysmap");
lf[141]=C_h_intern(&lf[141],3,"car");
lf[142]=C_static_string(C_heaptop,32,"~S expected keyword but got \047~S\047");
lf[143]=C_h_intern(&lf[143],8,"keyword\077");
lf[144]=C_static_string(C_heaptop,35,"~S expected ~A arguments but got ~A");
lf[145]=C_static_lambda_info(C_heaptop,28,"(do145 key147 arg148 pos149)");
lf[146]=C_static_string(C_heaptop,24,"~S is an invalid message");
lf[147]=C_static_lambda_info(C_heaptop,7,"(a1000)");
lf[148]=C_h_intern(&lf[148],14,"hash-table-ref");
lf[149]=C_h_intern(&lf[149],14,"symbol->string");
lf[150]=C_static_lambda_info(C_heaptop,25,"(a1548 mess169 . data170)");
lf[151]=C_h_intern(&lf[151],4,"send");
lf[152]=C_h_intern(&lf[152],10,"*messages*");
lf[153]=C_h_intern(&lf[153],14,"string->symbol");
lf[154]=C_static_string(C_heaptop,51,"message function not string, symbol or list of both");
lf[155]=C_static_lambda_info(C_heaptop,23,"(a1554 func127 info128)");
lf[156]=C_h_intern(&lf[156],19,"define-send-message");
lf[157]=C_h_intern(&lf[157],15,"make-hash-table");
lf[158]=C_h_intern(&lf[158],6,"equal\077");
lf[159]=C_static_lambda_info(C_heaptop,10,"(toplevel)");
C_register_lf2(lf,160,create_ptable());
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_287,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_library_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k285 */
static void C_ccall f_287(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_287,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_290,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_eval_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k288 in k285 */
static void C_ccall f_290(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_290,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_293,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k291 in k288 in k285 */
static void C_ccall f_293(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_293,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_296,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k294 in k291 in k288 in k285 */
static void C_ccall f_296(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_296,2,t0,t1);}
t2=C_mutate((C_word*)lf[0]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_298,a[2]=lf[2],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[3]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_312,a[2]=lf[4],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate(&lf[5],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_355,a[2]=lf[6],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate(&lf[7],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_358,a[2]=lf[8],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate(&lf[9],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_370,a[2]=lf[12],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate(&lf[13],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_379,a[2]=lf[15],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate(&lf[16],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_423,a[2]=lf[18],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate((C_word*)lf[19]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_445,a[2]=lf[28],tmp=(C_word)a,a+=3,tmp));
t10=C_mutate((C_word*)lf[29]+1,lf[5]);
t11=C_mutate((C_word*)lf[30]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_613,a[2]=lf[38],tmp=(C_word)a,a+=3,tmp));
t12=C_mutate((C_word*)lf[39]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_676,a[2]=lf[41],tmp=(C_word)a,a+=3,tmp));
t13=C_mutate((C_word*)lf[42]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_685,a[2]=lf[44],tmp=(C_word)a,a+=3,tmp));
t14=C_mutate((C_word*)lf[45]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_691,a[2]=lf[47],tmp=(C_word)a,a+=3,tmp));
t15=C_mutate((C_word*)lf[48]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_700,a[2]=lf[51],tmp=(C_word)a,a+=3,tmp));
t16=C_mutate((C_word*)lf[52]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_758,a[2]=lf[54],tmp=(C_word)a,a+=3,tmp));
t17=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_769,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 258  make-hash-table");
t18=C_retrieve(lf[157]);
((C_proc3)C_retrieve_proc(t18))(3,t18,t17,*((C_word*)lf[158]+1));}

/* k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_769(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_769,2,t0,t1);}
t2=C_mutate(&lf[55],t1);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_772,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1555,a[2]=lf[155],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 260  ##sys#register-macro");
t5=C_retrieve(lf[117]);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,lf[156],t4);}

/* a1554 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1555(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_1555,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_1559,a[2]=t6,a[3]=t1,a[4]=t3,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t4)[1]))){
t8=(C_word)C_i_car(((C_word*)t4)[1]);
t9=C_set_block_item(t6,0,t8);
t10=(C_word)C_i_cadr(((C_word*)t4)[1]);
t11=C_set_block_item(t4,0,t10);
t12=t7;
f_1559(2,t12,t11);}
else{
if(C_truep((C_word)C_i_stringp(((C_word*)t4)[1]))){
t8=C_set_block_item(t6,0,((C_word*)t4)[1]);
t9=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1592,a[2]=t7,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 267  string->symbol");
t10=*((C_word*)lf[153]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)t4)[1]);}
else{
if(C_truep((C_word)C_i_symbolp(((C_word*)t4)[1]))){
t8=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1602,a[2]=t7,a[3]=t6,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 269  symbol->string");
t9=*((C_word*)lf[149]+1);
((C_proc3)C_retrieve_proc(t9))(3,t9,t8,((C_word*)t4)[1]);}
else{
C_trace("ChickenBridge.scm: 271  error");
t8=*((C_word*)lf[35]+1);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,lf[154]);}}}}

/* k1600 in a1554 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1602(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_1559(2,t3,t2);}

/* k1590 in a1554 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1592(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_1559(2,t3,t2);}

/* k1557 in a1554 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1559(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1559,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[4]);
t3=(C_word)C_a_i_list(&a,2,lf[92],t2);
t4=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_a_i_list(&a,4,lf[119],lf[152],((C_word*)((C_word*)t0)[2])[1],t3));}

/* k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_772(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_772,2,t0,t1);}
t2=C_mutate(&lf[56],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_774,a[2]=lf[58],tmp=(C_word)a,a+=3,tmp));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1011,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1549,a[2]=lf[150],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 347  ##sys#register-macro");
t5=C_retrieve(lf[117]);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,lf[151],t4);}

/* a1548 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1549(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+6)){
C_save_and_reclaim((void*)tr3r,(void*)f_1549r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_1549r(t0,t1,t2,t3);}}

static void C_ccall f_1549r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a=C_alloc(6);
t4=t3;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_788,a[2]=t1,a[3]=t5,tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_symbolp(t2))){
C_trace("ChickenBridge.scm: 278  symbol->string");
t7=*((C_word*)lf[149]+1);
((C_proc3)C_retrieve_proc(t7))(3,t7,t6,t2);}
else{
t7=t6;
f_788(2,t7,t2);}}

/* k786 in a1548 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_788(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_788,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_791,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1001,a[2]=lf[147],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 279  hash-table-ref");
t4=*((C_word*)lf[148]+1);
((C_proc5)C_retrieve_proc(t4))(5,t4,t2,lf[55],t1,t3);}

/* a1000 in k786 in a1548 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1001(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1001,2,t0,t1);}
t2=t1;
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}

/* k789 in k786 in a1548 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_791(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_791,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_794,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=t1;
if(C_truep(t3)){
t4=t2;
f_794(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 280  ferror");
f_774(t2,lf[146],(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]));}}

/* k792 in k789 in k786 in a1548 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_794(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_794,2,t0,t1);}
t2=((C_word*)((C_word*)t0)[5])[1];
t3=(C_word)C_i_car(((C_word*)t0)[4]);
t4=(C_word)C_i_cdr(((C_word*)t0)[4]);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(C_word)C_i_length(t4);
t8=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_806,a[2]=t7,a[3]=t2,a[4]=((C_word*)t0)[2],a[5]=t6,a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[3],a[8]=t4,a[9]=t3,tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 287  append");
t9=*((C_word*)lf[109]+1);
((C_proc4)C_retrieve_proc(t9))(4,t9,t8,t4,C_SCHEME_END_OF_LIST);}

/* k804 in k792 in k789 in k786 in a1548 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_806(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[19],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_806,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_809,a[2]=((C_word*)t0)[7],a[3]=((C_word*)t0)[8],a[4]=t1,a[5]=((C_word*)t0)[9],tmp=(C_word)a,a+=6,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_854,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[5],a[8]=t4,a[9]=((C_word*)t0)[6],a[10]=lf[145],tmp=(C_word)a,a+=11,tmp));
t6=((C_word*)t4)[1];
f_854(t6,t2,C_SCHEME_FALSE,C_SCHEME_FALSE,C_fix(0));}

/* do145 in k804 in k792 in k789 in k786 in a1548 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_fcall f_854(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
C_save_and_reclaim((void*)trf_854,NULL,5,t0,t1,t2,t3,t4);}
t5=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[9])[1]))){
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,C_SCHEME_FALSE);}
else{
t8=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_864,a[2]=t7,a[3]=t6,a[4]=t5,a[5]=t1,a[6]=((C_word*)t0)[8],tmp=(C_word)a,a+=7,tmp);
t9=(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_870,a[2]=((C_word*)t0)[2],a[3]=t7,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=t6,a[8]=((C_word*)t0)[6],a[9]=t5,a[10]=((C_word*)t0)[9],a[11]=t8,a[12]=((C_word*)t0)[7],tmp=(C_word)a,a+=13,tmp);
t10=((C_word*)((C_word*)t0)[7])[1];
if(C_truep(t10)){
t11=t9;
f_870(2,t11,C_SCHEME_FALSE);}
else{
t11=(C_word)C_i_car(((C_word*)((C_word*)t0)[9])[1]);
C_trace("ChickenBridge.scm: 298  keyword?");
t12=C_retrieve(lf[143]);
((C_proc3)C_retrieve_proc(t12))(3,t12,t9,t11);}}}

/* k868 in do145 in k804 in k792 in k789 in k786 in a1548 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_870(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_870,2,t0,t1);}
if(C_truep(t1)){
t2=C_set_block_item(((C_word*)t0)[12],0,C_SCHEME_TRUE);
t3=((C_word*)t0)[11];
f_864(t3,t2);}
else{
t2=((C_word*)((C_word*)t0)[12])[1];
if(C_truep(t2)){
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[10])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[9])+1,t3);
t5=(C_word)C_i_assoc(((C_word*)((C_word*)t0)[9])[1],((C_word*)t0)[8]);
t6=C_mutate(((C_word *)((C_word*)t0)[7])+1,t5);
t7=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[10])[1]);
t8=C_mutate(((C_word *)((C_word*)t0)[10])+1,t7);
t9=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_924,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[9],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[11],a[6]=((C_word*)t0)[10],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t10=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_979,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[9],a[5]=((C_word*)t0)[5],a[6]=t9,a[7]=((C_word*)t0)[10],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 318  keyword?");
t11=C_retrieve(lf[143]);
((C_proc3)C_retrieve_proc(t11))(3,t11,t10,((C_word*)((C_word*)t0)[9])[1]);}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_880,a[2]=((C_word*)t0)[11],a[3]=((C_word*)t0)[10],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[6],tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_nequalp(((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]))){
t4=(C_word)C_i_length(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 308  ferror");
f_774(t3,lf[144],(C_word)C_a_i_list(&a,3,((C_word*)t0)[5],((C_word*)t0)[2],t4));}
else{
t4=t3;
f_880(2,t4,C_SCHEME_UNDEFINED);}}}}

/* k878 in k868 in do145 in k804 in k792 in k789 in k786 in a1548 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_880(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_880,2,t0,t1);}
t2=(C_word)C_i_list_tail(((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]);
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
t4=(C_word)C_i_set_car(t2,t3);
t5=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[3])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t5);
t7=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[4])[1],C_fix(1));
t8=C_mutate(((C_word *)((C_word*)t0)[4])+1,t7);
t9=((C_word*)t0)[2];
f_864(t9,t8);}

/* k977 in k868 in do145 in k804 in k792 in k789 in k786 in a1548 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_979(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_979,2,t0,t1);}
if(C_truep(t1)){
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[7])[1]))){
C_trace("ChickenBridge.scm: 322  ferror");
f_774(((C_word*)t0)[6],lf[138],(C_word)C_a_i_list(&a,2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]));}
else{
t2=((C_word*)((C_word*)t0)[3])[1];
if(C_truep(t2)){
t3=((C_word*)t0)[6];
f_924(2,t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_975,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
C_trace("map");
t4=*((C_word*)lf[140]+1);
((C_proc4)(void*)(*((C_word*)t4+1)))(4,t4,t3,*((C_word*)lf[141]+1),((C_word*)t0)[2]);}}}
else{
C_trace("ChickenBridge.scm: 319  ferror");
f_774(((C_word*)t0)[6],lf[142],(C_word)C_a_i_list(&a,2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]));}}

/* k973 in k977 in k868 in do145 in k804 in k792 in k789 in k786 in a1548 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_975(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_975,2,t0,t1);}
C_trace("ChickenBridge.scm: 325  ferror");
f_774(((C_word*)t0)[4],lf[139],(C_word)C_a_i_list(&a,3,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1));}

/* k922 in k868 in do145 in k804 in k792 in k789 in k786 in a1548 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_924(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[14],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_924,2,t0,t1);}
t2=(C_word)C_i_member(((C_word*)((C_word*)t0)[8])[1],((C_word*)t0)[7]);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_930,a[2]=((C_word*)t0)[5],a[3]=t2,a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
if(C_truep(t2)){
t4=t3;
f_930(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 332  ferror");
f_774(t3,lf[137],(C_word)C_a_i_list(&a,3,((C_word*)t0)[4],((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]));}}

/* k928 in k922 in k868 in do145 in k804 in k792 in k789 in k786 in a1548 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_930(C_word c,C_word t0,C_word t1){
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
f_864(t6,t5);}

/* k862 in do145 in k804 in k792 in k789 in k786 in a1548 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_fcall f_864(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[6])[1];
f_854(t2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k807 in k804 in k792 in k789 in k786 in a1548 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_809(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_809,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_814,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=lf[136],tmp=(C_word)a,a+=7,tmp));
t5=((C_word*)t3)[1];
f_814(t5,((C_word*)t0)[2],((C_word*)t0)[4]);}

/* do162 in k807 in k804 in k792 in k789 in k786 in a1548 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_fcall f_814(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_814,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[5],((C_word*)t0)[4]));}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_827,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_member(t4,((C_word*)t0)[2]))){
t5=(C_word)C_i_car(t2);
t6=(C_word)C_i_cadr(t5);
t7=t3;
f_827(t7,(C_word)C_i_set_car(t2,t6));}
else{
t5=t3;
f_827(t5,C_SCHEME_UNDEFINED);}}}

/* k825 in do162 in k807 in k804 in k792 in k789 in k786 in a1548 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_fcall f_827(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_814(t3,((C_word*)t0)[2],t2);}

/* k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1011(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_1011,2,t0,t1);}
t2=C_mutate((C_word*)lf[59]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1013,a[2]=lf[61],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[62]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1019,a[2]=lf[64],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate((C_word*)lf[65]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1025,a[2]=lf[67],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate((C_word*)lf[68]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1031,a[2]=lf[70],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[71]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1037,a[2]=lf[73],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate((C_word*)lf[74]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1043,a[2]=lf[76],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate((C_word*)lf[77]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1049,a[2]=lf[79],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate((C_word*)lf[80]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1055,a[2]=lf[82],tmp=(C_word)a,a+=3,tmp));
t10=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1062,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 374  hash-table-set!");
t11=C_retrieve(lf[119]);
((C_proc5)C_retrieve_proc(t11))(5,t11,t10,lf[55],lf[134],lf[135]);}

/* k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1062(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1062,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1065,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 375  hash-table-set!");
t3=C_retrieve(lf[119]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[55],lf[132],lf[133]);}

/* k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1065(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1065,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1068,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 376  hash-table-set!");
t3=C_retrieve(lf[119]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[55],lf[130],lf[131]);}

/* k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1068(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1068,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1071,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 377  hash-table-set!");
t3=C_retrieve(lf[119]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[55],lf[128],lf[129]);}

/* k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1071(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1071,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1074,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 378  hash-table-set!");
t3=C_retrieve(lf[119]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[55],lf[126],lf[127]);}

/* k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1074(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1074,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1077,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 379  hash-table-set!");
t3=C_retrieve(lf[119]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[55],lf[124],lf[125]);}

/* k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1077(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1077,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1080,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 380  hash-table-set!");
t3=C_retrieve(lf[119]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[55],lf[122],lf[123]);}

/* k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1080(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1080,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1083,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 381  hash-table-set!");
t3=C_retrieve(lf[119]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[55],lf[120],lf[121]);}

/* k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1083(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1083,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1086,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1543,a[2]=lf[116],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 388  ##sys#register-macro");
t4=C_retrieve(lf[117]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,lf[118],t3);}

/* a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1543(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+17)){
C_save_and_reclaim((void*)tr4r,(void*)f_1543r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest(a,C_rest_count(0));
f_1543r(t0,t1,t2,t3,t4);}}

static void C_ccall f_1543r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
t13=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_1101,a[2]=t2,a[3]=t12,a[4]=t6,a[5]=t10,a[6]=t1,a[7]=t8,a[8]=t3,tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(t2))){
t14=t13;
f_1101(2,t14,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 397  error");
t14=*((C_word*)lf[35]+1);
((C_proc4)C_retrieve_proc(t14))(4,t14,t13,lf[115],t2);}}

/* k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1101(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1101,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_1104,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(((C_word*)t0)[8]))){
if(C_truep((C_word)C_i_nullp(((C_word*)t0)[8]))){
C_trace("ChickenBridge.scm: 401  error");
t3=*((C_word*)lf[35]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,lf[113]);}
else{
t3=t2;
f_1104(2,t3,C_SCHEME_UNDEFINED);}}
else{
C_trace("ChickenBridge.scm: 399  error");
t3=*((C_word*)lf[35]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t2,lf[114],((C_word*)t0)[8]);}}

/* k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1104(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1104,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_1107,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],tmp=(C_word)a,a+=8,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_1378,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[7],a[5]=t4,a[6]=lf[112],tmp=(C_word)a,a+=7,tmp));
t6=((C_word*)t4)[1];
f_1378(t6,t2,((C_word*)t0)[2]);}

/* do202 in k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_fcall f_1378(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_1378,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1388,a[2]=t1,a[3]=((C_word*)t0)[5],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_1398,a[2]=t3,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=t2,tmp=(C_word)a,a+=7,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1486,a[2]=t4,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t7=(C_word)C_i_car(t2);
t8=(C_word)C_i_length(t7);
C_trace("ChickenBridge.scm: 405  <");
C_lessp(5,0,t6,C_fix(0),t8,C_fix(4));}
else{
t6=t4;
f_1398(t6,C_SCHEME_FALSE);}}}

/* k1484 in do202 in k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1486(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=(C_word)C_i_car(t2);
t4=((C_word*)t0)[2];
f_1398(t4,(C_word)C_i_symbolp(t3));}
else{
t2=((C_word*)t0)[2];
f_1398(t2,C_SCHEME_FALSE);}}

/* k1396 in do202 in k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_fcall f_1398(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_1398,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[6]);
t3=(C_word)C_i_car(t2);
t4=(C_word)C_i_car(((C_word*)t0)[6]);
t5=(C_word)C_i_cadr(t4);
t6=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_1407,a[2]=t5,a[3]=t3,a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[5],tmp=(C_word)a,a+=8,tmp);
t7=(C_word)C_i_car(((C_word*)t0)[6]);
t8=(C_word)C_i_cddr(t7);
if(C_truep((C_word)C_i_nullp(t8))){
t9=t6;
f_1407(t9,lf[110]);}
else{
t9=(C_word)C_i_car(((C_word*)t0)[6]);
t10=t6;
f_1407(t10,(C_word)C_i_caddr(t9));}}
else{
t2=(C_word)C_i_car(((C_word*)t0)[6]);
C_trace("ChickenBridge.scm: 418  error");
t3=*((C_word*)lf[35]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[2],lf[111],t2);}}

/* k1405 in k1396 in do202 in k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_fcall f_1407(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1407,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_1411,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t3=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 413  append");
t4=*((C_word*)lf[109]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,((C_word*)((C_word*)t0)[7])[1],t3);}

/* k1409 in k1405 in k1396 in do202 in k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1411(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1411,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_1415,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
t4=(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 414  append");
t5=*((C_word*)lf[109]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,((C_word*)((C_word*)t0)[7])[1],t4);}

/* k1413 in k1409 in k1405 in k1396 in do202 in k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1415(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_1415,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1419,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1423,a[2]=((C_word*)t0)[5],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_eqp(((C_word*)t0)[3],lf[110]);
if(C_truep(t5)){
t6=t4;
f_1423(t6,C_SCHEME_END_OF_LIST);}
else{
t6=(C_word)C_a_i_list(&a,3,lf[89],((C_word*)t0)[2],((C_word*)t0)[3]);
t7=t4;
f_1423(t7,(C_word)C_a_i_list(&a,1,t6));}}

/* k1421 in k1413 in k1409 in k1405 in k1396 in do202 in k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_fcall f_1423(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 415  append");
t2=*((C_word*)lf[109]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k1417 in k1413 in k1409 in k1405 in k1396 in do202 in k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1419(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_1388(2,t3,t2);}

/* k1386 in do202 in k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1388(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_1378(t3,((C_word*)t0)[2],t2);}

/* k1105 in k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1107(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1107,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_1110,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 420  gensym");
t3=C_retrieve(lf[108]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k1108 in k1105 in k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1110(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1110,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_1113,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 421  gensym");
t3=C_retrieve(lf[108]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k1111 in k1108 in k1105 in k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1113(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1113,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_1116,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 422  gensym");
t3=C_retrieve(lf[108]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k1114 in k1111 in k1108 in k1105 in k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1116(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1116,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_1119,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],a[10]=((C_word*)t0)[9],tmp=(C_word)a,a+=11,tmp);
C_trace("ChickenBridge.scm: 423  gensym");
t3=C_retrieve(lf[108]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k1117 in k1114 in k1111 in k1108 in k1105 in k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1119(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_1119,2,t0,t1);}
t2=C_SCHEME_TRUE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_SCHEME_END_OF_LIST;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_1122,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=t3,a[7]=((C_word*)t0)[5],a[8]=((C_word*)t0)[6],a[9]=((C_word*)t0)[7],a[10]=((C_word*)t0)[8],a[11]=((C_word*)t0)[9],a[12]=t5,a[13]=((C_word*)t0)[10],tmp=(C_word)a,a+=14,tmp);
t7=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1271,a[2]=t6,a[3]=t3,a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)((C_word*)t0)[3])[1]))){
t8=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
if(C_truep((C_word)C_i_pairp(t8))){
t9=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1372,a[2]=t7,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 429  caar");
t10=*((C_word*)lf[104]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)((C_word*)t0)[3])[1]);}
else{
t9=t7;
f_1271(t9,C_SCHEME_FALSE);}}
else{
t8=t7;
f_1271(t8,C_SCHEME_FALSE);}}

/* k1370 in k1117 in k1114 in k1111 in k1108 in k1105 in k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1372(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_1271(t2,(C_word)C_eqp(t1,lf[107]));}

/* k1269 in k1117 in k1114 in k1111 in k1108 in k1105 in k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_fcall f_1271(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1271,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1278,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 430  cdar");
t3=*((C_word*)lf[102]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)((C_word*)t0)[4])[1]);}
else{
t2=((C_word*)t0)[2];
f_1122(2,t2,C_SCHEME_UNDEFINED);}}

/* k1276 in k1269 in k1117 in k1114 in k1111 in k1108 in k1105 in k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1278(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1278,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_1280,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=lf[106],tmp=(C_word)a,a+=6,tmp));
t5=((C_word*)t3)[1];
f_1280(t5,((C_word*)t0)[2],t1);}

/* do218 in k1276 in k1269 in k1117 in k1114 in k1111 in k1108 in k1105 in k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_fcall f_1280(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_1280,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[4])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[4])+1,t3);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,t4);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1294,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1304,a[2]=t2,a[3]=((C_word*)t0)[2],a[4]=t3,tmp=(C_word)a,a+=5,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1352,a[2]=t4,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 434  cdar");
t7=*((C_word*)lf[102]+1);
((C_proc3)C_retrieve_proc(t7))(3,t7,t6,t2);}
else{
t6=t4;
f_1304(t6,C_SCHEME_FALSE);}}}

/* k1350 in do218 in k1276 in k1269 in k1117 in k1114 in k1111 in k1108 in k1105 in k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1352(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_1304(t2,(C_word)C_i_pairp(t1));}

/* k1302 in do218 in k1276 in k1269 in k1117 in k1114 in k1111 in k1108 in k1105 in k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_fcall f_1304(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1304,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1307,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 435  caar");
t3=*((C_word*)lf[104]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)t0)[2]);}
else{
t2=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 441  error");
t3=*((C_word*)lf[35]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[4],lf[105],t2);}}

/* k1305 in k1302 in do218 in k1276 in k1269 in k1117 in k1114 in k1111 in k1108 in k1105 in k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1307(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1307,2,t0,t1);}
t2=(C_word)C_eqp(t1,lf[101]);
if(C_truep(t2)){
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1328,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 437  cdar");
t4=*((C_word*)lf[102]+1);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)t0)[2]);}
else{
t3=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 440  error");
t4=*((C_word*)lf[35]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,((C_word*)t0)[4],lf[103],t3);}}

/* k1326 in k1305 in k1302 in do218 in k1276 in k1269 in k1117 in k1114 in k1111 in k1108 in k1105 in k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1328(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep((C_word)C_i_car(t1))){
t2=((C_word*)t0)[3];
f_1294(2,t2,C_SCHEME_UNDEFINED);}
else{
t2=C_set_block_item(((C_word*)t0)[2],0,C_SCHEME_FALSE);
t3=((C_word*)t0)[3];
f_1294(2,t3,t2);}}

/* k1292 in do218 in k1276 in k1269 in k1117 in k1114 in k1111 in k1108 in k1105 in k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1294(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_1280(t3,((C_word*)t0)[2],t2);}

/* k1120 in k1117 in k1114 in k1111 in k1108 in k1105 in k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1122(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1122,2,t0,t1);}
t2=(C_word)C_i_car(((C_word*)t0)[13]);
t3=(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_1260,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],a[10]=((C_word*)t0)[10],a[11]=((C_word*)t0)[11],a[12]=((C_word*)t0)[12],a[13]=t2,tmp=(C_word)a,a+=14,tmp);
t4=(C_word)C_i_cdr(((C_word*)t0)[13]);
t5=(C_word)C_a_i_list(&a,1,C_fix(-1));
C_trace("ChickenBridge.scm: 392  ##sys#append");
t6=*((C_word*)lf[100]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t3,t4,t5);}

/* k1258 in k1120 in k1117 in k1114 in k1111 in k1108 in k1105 in k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1260(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1260,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[13],t1);
t3=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_1244,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],a[8]=((C_word*)t0)[10],a[9]=((C_word*)t0)[11],a[10]=((C_word*)t0)[12],a[11]=t2,tmp=(C_word)a,a+=12,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1248,a[2]=((C_word*)t0)[3],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_a_i_list(&a,1,((C_word*)t0)[10]);
C_trace("ChickenBridge.scm: 392  ##sys#append");
t6=*((C_word*)lf[100]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t4,((C_word*)((C_word*)t0)[2])[1],t5);}

/* k1246 in k1258 in k1120 in k1117 in k1114 in k1111 in k1108 in k1105 in k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1248(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 392  ##sys#append");
t2=*((C_word*)lf[100]+1);
((C_proc4)(void*)(*((C_word*)t2+1)))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k1242 in k1258 in k1120 in k1117 in k1114 in k1111 in k1108 in k1105 in k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1244(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_1244,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,lf[84],t1);
t3=(C_word)C_a_i_list(&a,3,lf[85],((C_word*)t0)[11],t2);
t4=C_mutate(((C_word *)((C_word*)t0)[10])+1,t3);
t5=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_1129,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],a[5]=((C_word*)t0)[10],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],tmp=(C_word)a,a+=8,tmp);
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
f_1129(t20,t19);}
else{
t6=t5;
f_1129(t6,C_SCHEME_UNDEFINED);}}

/* k1127 in k1242 in k1258 in k1120 in k1117 in k1114 in k1111 in k1108 in k1105 in k1102 in k1099 in a1542 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_fcall f_1129(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_1129,NULL,2,t0,t1);}
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

/* k1084 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1086(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1086,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1541,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 485  return-to-host");
t3=C_retrieve(lf[83]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k1539 in k1084 in k1081 in k1078 in k1075 in k1072 in k1069 in k1066 in k1063 in k1060 in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1541(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_UNDEFINED);}

/* mp:inhook in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1055(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1055,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 370  error");
t3=*((C_word*)lf[35]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[81]);}

/* mp:micro in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1049(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1049,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 368  error");
t3=*((C_word*)lf[35]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[78]);}

/* mp:alloff in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1043(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1043,2,t0,t1);}
C_trace("ChickenBridge.scm: 366  error");
t2=*((C_word*)lf[35]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,t1,lf[75]);}

/* mp:ctrl in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1037(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_1037,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 364  error");
t6=*((C_word*)lf[35]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[72]);}

/* mp:prog in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1031(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_1031,5,t0,t1,t2,t3,t4);}
C_trace("ChickenBridge.scm: 362  error");
t5=*((C_word*)lf[35]+1);
((C_proc3)C_retrieve_proc(t5))(3,t5,t1,lf[69]);}

/* mp:off in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1025(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_1025,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 360  error");
t6=*((C_word*)lf[35]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[66]);}

/* mp:on in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1019(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_1019,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 358  error");
t6=*((C_word*)lf[35]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[63]);}

/* mp:note in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_1013(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
C_word tmp;
C_word t7;
C_word t8;
C_word ab[8],*a=ab;
if(c!=7) C_bad_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr7,(void*)f_1013,7,t0,t1,t2,t3,t4,t5,t6);}
t7=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_330,a[2]=t1,a[3]=t6,a[4]=t5,a[5]=t4,a[6]=t3,a[7]=t2,tmp=(C_word)a,a+=8,tmp);
C_trace("##sys#gc");
t8=C_retrieve(lf[11]);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,C_SCHEME_FALSE);}

/* k328 in mp:note in k1009 in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_330(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_330,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[7]);
t4=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[6]);
t5=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[5]);
t6=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[4]);
t7=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[3]);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub17,a[2]=lf[60],tmp=(C_word)a,a+=3,tmp);
((C_proc8)C_retrieve_proc(t8))(8,t8,((C_word*)t0)[2],t2,t3,t4,t5,t6,t7);}

/* ferror in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_fcall f_774(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_774,NULL,3,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_782,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_apply(5,0,t4,C_retrieve(lf[57]),t2,t3);}

/* k780 in ferror in k770 in k767 in k294 in k291 in k288 in k285 */
static void C_ccall f_782(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 275  error");
t2=*((C_word*)lf[35]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* hush in k294 in k291 in k288 in k285 */
static void C_ccall f_758(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_758,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_762,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_440,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[11]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k438 in hush in k294 in k291 in k288 in k285 */
static void C_ccall f_440(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_440,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub69,a[2]=lf[53],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k760 in hush in k294 in k291 in k288 in k285 */
static void C_ccall f_762(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 252  values");
C_values(2,0,((C_word*)t0)[2]);}

/* stop in k294 in k291 in k288 in k285 */
static void C_ccall f_700(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+9)){
C_save_and_reclaim((void*)tr2r,(void*)f_700r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_700r(t0,t1,t2);}}

static void C_ccall f_700r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a=C_alloc(9);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_704,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 242  scheduler-stop");
f_423(t3,C_fix(-1));}
else{
t4=C_SCHEME_UNDEFINED;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_set_block_item(t5,0,(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_718,a[2]=t5,a[3]=lf[50],tmp=(C_word)a,a+=4,tmp));
t7=((C_word*)t5)[1];
f_718(t7,t3,t2);}}

/* do120 in stop in k294 in k291 in k288 in k285 */
static void C_fcall f_718(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_718,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_728,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_fixnump(t4))){
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 246  scheduler-stop");
f_423(t3,t5);}
else{
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 247  error");
t6=*((C_word*)lf[35]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t3,lf[49],t5);}}}

/* k726 in do120 in stop in k294 in k291 in k288 in k285 */
static void C_ccall f_728(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_718(t3,((C_word*)t0)[2],t2);}

/* k702 in stop in k294 in k291 in k288 in k285 */
static void C_ccall f_704(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 248  values");
C_values(2,0,((C_word*)t0)[2]);}

/* cont in k294 in k291 in k288 in k285 */
static void C_ccall f_691(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_691,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_695,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_418,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[11]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k416 in cont in k294 in k291 in k288 in k285 */
static void C_ccall f_418(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_418,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub59,a[2]=lf[46],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k693 in cont in k294 in k291 in k288 in k285 */
static void C_ccall f_695(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 238  values");
C_values(2,0,((C_word*)t0)[2]);}

/* paused? in k294 in k291 in k288 in k285 */
static void C_ccall f_685(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_685,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_400,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t3=C_retrieve(lf[11]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,C_SCHEME_FALSE);}

/* k398 in paused? in k294 in k291 in k288 in k285 */
static void C_ccall f_400(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_400,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub51,a[2]=lf[43],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* pause in k294 in k291 in k288 in k285 */
static void C_ccall f_676(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_676,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_680,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_409,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[11]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k407 in pause in k294 in k291 in k288 in k285 */
static void C_ccall f_409(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_409,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub55,a[2]=lf[40],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k678 in pause in k294 in k291 in k288 in k285 */
static void C_ccall f_680(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 231  values");
C_values(2,0,((C_word*)t0)[2]);}

/* time-format in k294 in k291 in k288 in k285 */
static void C_ccall f_613(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+11)){
C_save_and_reclaim((void*)tr2rv,(void*)f_613r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_613r(t0,t1,t2);}}

static void C_ccall f_613r(C_word t0,C_word t1,C_word t2){
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
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_626,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_365,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t5=C_retrieve(lf[11]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,C_SCHEME_FALSE);}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
t4=(C_word)C_i_eqvp(t3,lf[33]);
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_638,a[2]=t2,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
if(C_truep(t4)){
t6=t5;
f_638(t6,t4);}
else{
t6=(C_word)C_eqp(t3,C_fix(1));
t7=t5;
f_638(t7,(C_truep(t6)?t6:(C_word)C_eqp(t3,lf[37])));}}}

/* k636 in time-format in k294 in k291 in k288 in k285 */
static void C_fcall f_638(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a;
if(C_truep(t1)){
t2=C_mutate((C_word*)lf[29]+1,lf[7]);
C_trace("ChickenBridge.scm: 220  scheduler-set-time-milliseconds");
f_370(((C_word*)t0)[4],C_SCHEME_FALSE);}
else{
t2=(C_word)C_eqp(((C_word*)t0)[3],C_fix(1000));
t3=(C_truep(t2)?t2:(C_word)C_eqp(((C_word*)t0)[3],lf[34]));
if(C_truep(t3)){
t4=C_mutate((C_word*)lf[29]+1,lf[5]);
C_trace("ChickenBridge.scm: 224  scheduler-set-time-milliseconds");
f_370(((C_word*)t0)[4],C_SCHEME_TRUE);}
else{
t4=(C_word)C_i_vector_ref(((C_word*)t0)[2],C_fix(0));
C_trace("ChickenBridge.scm: 227  error");
t5=*((C_word*)lf[35]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,((C_word*)t0)[4],lf[36],t4);}}}

/* k363 in time-format in k294 in k291 in k288 in k285 */
static void C_ccall f_365(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_365,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub31,a[2]=lf[32],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k624 in time-format in k294 in k291 in k288 in k285 */
static void C_ccall f_626(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_truep(t1)?C_fix(1000):lf[31]));}

/* sprout in k294 in k291 in k288 in k285 */
static void C_ccall f_445(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+12)){
C_save_and_reclaim((void*)tr3r,(void*)f_445r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_445r(t0,t1,t2,t3);}}

static void C_ccall f_445r(C_word t0,C_word t1,C_word t2,C_word t3){
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
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_447,a[2]=t2,a[3]=lf[23],tmp=(C_word)a,a+=4,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_559,a[2]=t4,a[3]=lf[24],tmp=(C_word)a,a+=4,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_564,a[2]=t5,a[3]=lf[25],tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("def-start79100");
t7=t6;
f_564(t7,t1);}
else{
t7=(C_word)C_i_car(t3);
t8=(C_word)C_i_cdr(t3);
if(C_truep((C_word)C_i_nullp(t8))){
C_trace("def-id8098");
t9=t5;
f_559(t9,t1,t7);}
else{
t9=(C_word)C_i_car(t8);
t10=(C_word)C_i_cdr(t8);
if(C_truep((C_word)C_i_nullp(t10))){
C_trace("body7782");
t11=t4;
f_447(t11,t1,t7,t9);}
else{
C_trace("##sys#error");
t11=*((C_word*)lf[26]+1);
((C_proc4)(void*)(*((C_word*)t11+1)))(4,t11,t1,lf[27],t10);}}}}

/* def-start79 in sprout in k294 in k291 in k288 in k285 */
static void C_fcall f_564(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_564,NULL,2,t0,t1);}
C_trace("def-id8098");
t2=((C_word*)t0)[2];
f_559(t2,t1,C_fix(0));}

/* def-id80 in sprout in k294 in k291 in k288 in k285 */
static void C_fcall f_559(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_559,NULL,3,t0,t1,t2);}
C_trace("body7782");
t3=((C_word*)t0)[2];
f_447(t3,t1,t2,C_fix(-1));}

/* body77 in sprout in k294 in k291 in k288 in k285 */
static void C_fcall f_447(C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)trf_447,NULL,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_449,a[2]=t4,a[3]=lf[20],tmp=(C_word)a,a+=4,tmp);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_477,a[2]=t5,a[3]=lf[21],tmp=(C_word)a,a+=4,tmp);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_507,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t0)[2]))){
t9=C_SCHEME_UNDEFINED;
t10=(*a=C_VECTOR_TYPE|1,a[1]=t9,tmp=(C_word)a,a+=2,tmp);
t11=C_set_block_item(t10,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_518,a[2]=t6,a[3]=t7,a[4]=t10,a[5]=((C_word*)t0)[2],a[6]=lf[22],tmp=(C_word)a,a+=7,tmp));
t12=((C_word*)t10)[1];
f_518(t12,t8,((C_word*)t0)[2]);}
else{
t9=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_550,a[2]=((C_word*)t0)[2],a[3]=t8,tmp=(C_word)a,a+=4,tmp);
t10=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_554,a[2]=t7,a[3]=((C_word*)t0)[2],a[4]=t9,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 206  nextstart");
t11=t6;
f_449(t11,t10);}}

/* k552 in body77 in sprout in k294 in k291 in k288 in k285 */
static void C_ccall f_554(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_554,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_558,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 206  nextid");
t3=((C_word*)t0)[2];
f_477(t3,t2);}

/* k556 in k552 in body77 in sprout in k294 in k291 in k288 in k285 */
static void C_ccall f_558(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 206  scheduler-sprout");
f_379(((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k548 in body77 in sprout in k294 in k291 in k288 in k285 */
static void C_ccall f_550(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
f_507(2,t2,((C_word*)t0)[2]);}

/* do91 in body77 in sprout in k294 in k291 in k288 in k285 */
static void C_fcall f_518(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_518,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,((C_word*)t0)[5]);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_528,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_543,a[2]=((C_word*)t0)[3],a[3]=t4,a[4]=t3,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 204  nextstart");
t6=((C_word*)t0)[2];
f_449(t6,t5);}}

/* k541 in do91 in body77 in sprout in k294 in k291 in k288 in k285 */
static void C_ccall f_543(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_543,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_547,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 204  nextid");
t3=((C_word*)t0)[2];
f_477(t3,t2);}

/* k545 in k541 in do91 in body77 in sprout in k294 in k291 in k288 in k285 */
static void C_ccall f_547(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 204  scheduler-sprout");
f_379(((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k526 in do91 in body77 in sprout in k294 in k291 in k288 in k285 */
static void C_ccall f_528(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_518(t3,((C_word*)t0)[2],t2);}

/* k505 in body77 in sprout in k294 in k291 in k288 in k285 */
static void C_ccall f_507(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 210  values");
C_values(2,0,((C_word*)t0)[2]);}

/* nextid in body77 in sprout in k294 in k291 in k288 in k285 */
static void C_fcall f_477(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_477,NULL,2,t0,t1);}
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

/* nextstart in body77 in sprout in k294 in k291 in k288 in k285 */
static void C_fcall f_449(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_449,NULL,2,t0,t1);}
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

/* scheduler-stop in k294 in k291 in k288 in k285 */
static void C_fcall f_423(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_423,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_427,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[11]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k425 in scheduler-stop in k294 in k291 in k288 in k285 */
static void C_ccall f_427(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_427,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_fixnum_argumentp(((C_word*)t0)[3]);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub64,a[2]=lf[17],tmp=(C_word)a,a+=3,tmp);
((C_proc4)C_retrieve_proc(t4))(4,t4,((C_word*)t0)[2],t2,t3);}

/* scheduler-sprout in k294 in k291 in k288 in k285 */
static void C_fcall f_379(C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_379,NULL,4,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_383,a[2]=t2,a[3]=t1,a[4]=t4,a[5]=t3,tmp=(C_word)a,a+=6,tmp);
C_trace("##sys#gc");
t6=C_retrieve(lf[11]);
((C_proc3)C_retrieve_proc(t6))(3,t6,t5,C_SCHEME_FALSE);}

/* k381 in scheduler-sprout in k294 in k291 in k288 in k285 */
static void C_ccall f_383(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_383,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[5]);
t4=(C_word)C_i_foreign_fixnum_argumentp(((C_word*)t0)[4]);
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub44,a[2]=lf[14],tmp=(C_word)a,a+=3,tmp);
((C_proc6)C_retrieve_proc(t5))(6,t5,((C_word*)t0)[3],t2,((C_word*)t0)[2],t3,t4);}

/* scheduler-set-time-milliseconds in k294 in k291 in k288 in k285 */
static void C_fcall f_370(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_370,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_374,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[11]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k372 in scheduler-set-time-milliseconds in k294 in k291 in k288 in k285 */
static void C_ccall f_374(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_374,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub36,a[2]=lf[10],tmp=(C_word)a,a+=3,tmp);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[3],t2,((C_word*)t0)[2]);}

/* current-time-seconds in k294 in k291 in k288 in k285 */
static void C_ccall f_358(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_358,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub28(t2));}

/* current-time-milliseconds in k294 in k291 in k288 in k285 */
static void C_ccall f_355(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_355,2,t0,t1);}
t2=t1;
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub26(C_SCHEME_UNDEFINED));}

/* print-error in k294 in k291 in k288 in k285 */
static void C_ccall f_312(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_312,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_317,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[1]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_317(2,t4,C_SCHEME_FALSE);}}

/* k315 in print-error in k294 in k291 in k288 in k285 */
static void C_ccall f_317(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub7(C_SCHEME_UNDEFINED,t1));}

/* print-message in k294 in k291 in k288 in k285 */
static void C_ccall f_298(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_298,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_303,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[1]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_303(2,t4,C_SCHEME_FALSE);}}

/* k301 in print-message in k294 in k291 in k288 in k285 */
static void C_ccall f_303(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub1(C_SCHEME_UNDEFINED,t1));}

#ifdef C_ENABLE_PTABLES
static C_PTABLE_ENTRY ptable[127] = {
{"toplevelChickenBridge.scm",(void*)C_grace_toplevel},
{"f_287ChickenBridge.scm",(void*)f_287},
{"f_290ChickenBridge.scm",(void*)f_290},
{"f_293ChickenBridge.scm",(void*)f_293},
{"f_296ChickenBridge.scm",(void*)f_296},
{"f_769ChickenBridge.scm",(void*)f_769},
{"f_1555ChickenBridge.scm",(void*)f_1555},
{"f_1602ChickenBridge.scm",(void*)f_1602},
{"f_1592ChickenBridge.scm",(void*)f_1592},
{"f_1559ChickenBridge.scm",(void*)f_1559},
{"f_772ChickenBridge.scm",(void*)f_772},
{"f_1549ChickenBridge.scm",(void*)f_1549},
{"f_788ChickenBridge.scm",(void*)f_788},
{"f_1001ChickenBridge.scm",(void*)f_1001},
{"f_791ChickenBridge.scm",(void*)f_791},
{"f_794ChickenBridge.scm",(void*)f_794},
{"f_806ChickenBridge.scm",(void*)f_806},
{"f_854ChickenBridge.scm",(void*)f_854},
{"f_870ChickenBridge.scm",(void*)f_870},
{"f_880ChickenBridge.scm",(void*)f_880},
{"f_979ChickenBridge.scm",(void*)f_979},
{"f_975ChickenBridge.scm",(void*)f_975},
{"f_924ChickenBridge.scm",(void*)f_924},
{"f_930ChickenBridge.scm",(void*)f_930},
{"f_864ChickenBridge.scm",(void*)f_864},
{"f_809ChickenBridge.scm",(void*)f_809},
{"f_814ChickenBridge.scm",(void*)f_814},
{"f_827ChickenBridge.scm",(void*)f_827},
{"f_1011ChickenBridge.scm",(void*)f_1011},
{"f_1062ChickenBridge.scm",(void*)f_1062},
{"f_1065ChickenBridge.scm",(void*)f_1065},
{"f_1068ChickenBridge.scm",(void*)f_1068},
{"f_1071ChickenBridge.scm",(void*)f_1071},
{"f_1074ChickenBridge.scm",(void*)f_1074},
{"f_1077ChickenBridge.scm",(void*)f_1077},
{"f_1080ChickenBridge.scm",(void*)f_1080},
{"f_1083ChickenBridge.scm",(void*)f_1083},
{"f_1543ChickenBridge.scm",(void*)f_1543},
{"f_1101ChickenBridge.scm",(void*)f_1101},
{"f_1104ChickenBridge.scm",(void*)f_1104},
{"f_1378ChickenBridge.scm",(void*)f_1378},
{"f_1486ChickenBridge.scm",(void*)f_1486},
{"f_1398ChickenBridge.scm",(void*)f_1398},
{"f_1407ChickenBridge.scm",(void*)f_1407},
{"f_1411ChickenBridge.scm",(void*)f_1411},
{"f_1415ChickenBridge.scm",(void*)f_1415},
{"f_1423ChickenBridge.scm",(void*)f_1423},
{"f_1419ChickenBridge.scm",(void*)f_1419},
{"f_1388ChickenBridge.scm",(void*)f_1388},
{"f_1107ChickenBridge.scm",(void*)f_1107},
{"f_1110ChickenBridge.scm",(void*)f_1110},
{"f_1113ChickenBridge.scm",(void*)f_1113},
{"f_1116ChickenBridge.scm",(void*)f_1116},
{"f_1119ChickenBridge.scm",(void*)f_1119},
{"f_1372ChickenBridge.scm",(void*)f_1372},
{"f_1271ChickenBridge.scm",(void*)f_1271},
{"f_1278ChickenBridge.scm",(void*)f_1278},
{"f_1280ChickenBridge.scm",(void*)f_1280},
{"f_1352ChickenBridge.scm",(void*)f_1352},
{"f_1304ChickenBridge.scm",(void*)f_1304},
{"f_1307ChickenBridge.scm",(void*)f_1307},
{"f_1328ChickenBridge.scm",(void*)f_1328},
{"f_1294ChickenBridge.scm",(void*)f_1294},
{"f_1122ChickenBridge.scm",(void*)f_1122},
{"f_1260ChickenBridge.scm",(void*)f_1260},
{"f_1248ChickenBridge.scm",(void*)f_1248},
{"f_1244ChickenBridge.scm",(void*)f_1244},
{"f_1129ChickenBridge.scm",(void*)f_1129},
{"f_1086ChickenBridge.scm",(void*)f_1086},
{"f_1541ChickenBridge.scm",(void*)f_1541},
{"f_1055ChickenBridge.scm",(void*)f_1055},
{"f_1049ChickenBridge.scm",(void*)f_1049},
{"f_1043ChickenBridge.scm",(void*)f_1043},
{"f_1037ChickenBridge.scm",(void*)f_1037},
{"f_1031ChickenBridge.scm",(void*)f_1031},
{"f_1025ChickenBridge.scm",(void*)f_1025},
{"f_1019ChickenBridge.scm",(void*)f_1019},
{"f_1013ChickenBridge.scm",(void*)f_1013},
{"f_330ChickenBridge.scm",(void*)f_330},
{"f_774ChickenBridge.scm",(void*)f_774},
{"f_782ChickenBridge.scm",(void*)f_782},
{"f_758ChickenBridge.scm",(void*)f_758},
{"f_440ChickenBridge.scm",(void*)f_440},
{"f_762ChickenBridge.scm",(void*)f_762},
{"f_700ChickenBridge.scm",(void*)f_700},
{"f_718ChickenBridge.scm",(void*)f_718},
{"f_728ChickenBridge.scm",(void*)f_728},
{"f_704ChickenBridge.scm",(void*)f_704},
{"f_691ChickenBridge.scm",(void*)f_691},
{"f_418ChickenBridge.scm",(void*)f_418},
{"f_695ChickenBridge.scm",(void*)f_695},
{"f_685ChickenBridge.scm",(void*)f_685},
{"f_400ChickenBridge.scm",(void*)f_400},
{"f_676ChickenBridge.scm",(void*)f_676},
{"f_409ChickenBridge.scm",(void*)f_409},
{"f_680ChickenBridge.scm",(void*)f_680},
{"f_613ChickenBridge.scm",(void*)f_613},
{"f_638ChickenBridge.scm",(void*)f_638},
{"f_365ChickenBridge.scm",(void*)f_365},
{"f_626ChickenBridge.scm",(void*)f_626},
{"f_445ChickenBridge.scm",(void*)f_445},
{"f_564ChickenBridge.scm",(void*)f_564},
{"f_559ChickenBridge.scm",(void*)f_559},
{"f_447ChickenBridge.scm",(void*)f_447},
{"f_554ChickenBridge.scm",(void*)f_554},
{"f_558ChickenBridge.scm",(void*)f_558},
{"f_550ChickenBridge.scm",(void*)f_550},
{"f_518ChickenBridge.scm",(void*)f_518},
{"f_543ChickenBridge.scm",(void*)f_543},
{"f_547ChickenBridge.scm",(void*)f_547},
{"f_528ChickenBridge.scm",(void*)f_528},
{"f_507ChickenBridge.scm",(void*)f_507},
{"f_477ChickenBridge.scm",(void*)f_477},
{"f_449ChickenBridge.scm",(void*)f_449},
{"f_423ChickenBridge.scm",(void*)f_423},
{"f_427ChickenBridge.scm",(void*)f_427},
{"f_379ChickenBridge.scm",(void*)f_379},
{"f_383ChickenBridge.scm",(void*)f_383},
{"f_370ChickenBridge.scm",(void*)f_370},
{"f_374ChickenBridge.scm",(void*)f_374},
{"f_358ChickenBridge.scm",(void*)f_358},
{"f_355ChickenBridge.scm",(void*)f_355},
{"f_312ChickenBridge.scm",(void*)f_312},
{"f_317ChickenBridge.scm",(void*)f_317},
{"f_298ChickenBridge.scm",(void*)f_298},
{"f_303ChickenBridge.scm",(void*)f_303},
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
