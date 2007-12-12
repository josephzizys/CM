/* Generated from ChickenBridge.scm by the CHICKEN compiler
   http://www.call-with-current-continuation.org
   2007-12-12 06:17
   Version 2.737 - macosx-unix-gnu-ppc	[ manyargs dload ptables applyhook ]
(c)2000-2007 Felix L. Winkelmann	compiled 2007-12-11 on galen.local (Darwin)
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

void print_message(char * st) {
  // attempt at buffering: if string ends with #\Return, send string
  // AND trigger update else send string without triggering update
  String s=String(st);
  if ( s.endsWithChar('\n') )
    ((GraceApp *)GraceApp::getInstance())->getConsole()->postConsoleTextMessage(s, ConsoleMessage::TEXT, true);
  else
    ((GraceApp *)GraceApp::getInstance())->getConsole()->postConsoleTextMessage(s, ConsoleMessage::TEXT, false);
}

void print_error(char * st) {
  // attempt at buffering: if string ends with #\Return, send string
  // AND trigger update else send string without triggering update
  String s=String(st);
  if ( s.endsWithChar('\n') )
    ((GraceApp *)GraceApp::getInstance())->getConsole()->postConsoleTextMessage(s, ConsoleMessage::ERROR, true);
  else
    ((GraceApp *)GraceApp::getInstance())->getConsole()->postConsoleTextMessage(s, ConsoleMessage::ERROR, false);
}

//
// MIDI Port code
//

void mp_note(double time, double dur, float k, float v, float c) {
 ((GraceApp *)GraceApp::getInstance())->midiOutPort->sendNote(time, dur, k, v, c); 
}

void mp_on(double time, float k, float v, float c) {
 ((GraceApp *)GraceApp::getInstance())->midiOutPort->sendOn(time, k, v, c);
}

void mp_off(double time, float k, float v, float c) {
 ((GraceApp *)GraceApp::getInstance())->midiOutPort->sendOff(time, k, v, c);
}

void mp_prog(double time, float p, float c) {
 ((GraceApp *)GraceApp::getInstance())->midiOutPort->sendProg(time, p, c);
}

void mp_ctrl(double time, float n, float v, float c) {
 ((GraceApp *)GraceApp::getInstance())->midiOutPort->sendCtrl(time, n, v, c);
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
  ((GraceApp *)GraceApp::getInstance())->midiOutPort->clear();
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


/* from k1711 in hush in k594 in k591 in k588 in k585 */
C_noret_decl(stub363)
static void C_ccall stub363(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub363(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_hush();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1705 */
C_noret_decl(stub358)
static void C_ccall stub358(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0) C_noret;
static void C_ccall stub358(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_unfix(C_a0);
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_stop(t0);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1689 in cont in k594 in k591 in k588 in k585 */
C_noret_decl(stub353)
static void C_ccall stub353(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub353(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_cont();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1680 in pause in k594 in k591 in k588 in k585 */
C_noret_decl(stub349)
static void C_ccall stub349(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub349(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_pause();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1671 in paused? in k594 in k591 in k588 in k585 */
C_noret_decl(stub345)
static void C_ccall stub345(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub345(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
C_r=C_mk_bool(scheduler_is_paused());
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1665 */
C_noret_decl(stub338)
static void C_ccall stub338(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2) C_noret;
static void C_ccall stub338(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
C_word t0=(C_word )(C_a0);
double t1=(double )C_c_double(C_a1);
int t2=(int )C_unfix(C_a2);
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_sprout(t0,t1,t2);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1645 in scheduler-set-time-milliseconds in k594 in k591 in k588 in k585 */
C_noret_decl(stub330)
static void C_ccall stub330(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0) C_noret;
static void C_ccall stub330(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_truep(C_a0);
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_set_time_milliseconds(t0);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1636 in time-format in k594 in k591 in k588 in k585 */
C_noret_decl(stub325)
static void C_ccall stub325(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub325(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
C_r=C_mk_bool(scheduler_is_time_milliseconds());
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from current-time-seconds in k594 in k591 in k588 in k585 */
#define return(x) C_cblock C_r = (C_flonum(&C_a,(x))); goto C_ret; C_cblockend
static C_word C_fcall stub322(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub322(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
 C_return( (Time::getMillisecondCounterHiRes() / 1000.0) );
C_ret:
#undef return

return C_r;}

/* from current-time-milliseconds in k594 in k591 in k588 in k585 */
#define return(x) C_cblock C_r = (C_flonum(&C_a,(x))); goto C_ret; C_cblockend
static C_word C_fcall stub319(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub319(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
 C_return( Time::getMillisecondCounterHiRes());
C_ret:
#undef return

return C_r;}

/* from k1624 */
C_noret_decl(stub310)
static void C_ccall stub310(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2,C_word C_a3,C_word C_a4) C_noret;
static void C_ccall stub310(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2,C_word C_a3,C_word C_a4){
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

/* from k1588 in print-error in k594 in k591 in k588 in k585 */
static C_word C_fcall stub300(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub300(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_error(t0);
return C_r;}

/* from k1574 in print-message in k594 in k591 in k588 in k585 */
static C_word C_fcall stub294(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub294(C_word C_buf,C_word C_a0){
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

/* from k821 */
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

/* from k811 */
static C_word C_fcall stub134(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub134(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::rangamma(t0));
return C_r;}

/* from k804 */
static C_word C_fcall stub128(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub128(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
C_r=C_flonum(&C_a,Toolbox::ranbeta(t0,t1));
return C_r;}

/* from k793 */
static C_word C_fcall stub122(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub122(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::ranexp(t0));
return C_r;}

/* from k786 */
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

/* from k766 */
static C_word C_fcall stub100(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub100(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
C_r=C_flonum(&C_a,Toolbox::ran(t0,t1));
return C_r;}

/* from k755 */
static C_word C_fcall stub94(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub94(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_unfix(C_a0);
int t1=(int )C_unfix(C_a1);
C_r=C_fix((C_word)Toolbox::ran(t0,t1));
return C_r;}

/* from k744 */
static C_word C_fcall stub88(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub88(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::ran(t0));
return C_r;}

/* from k737 */
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

/* from k727 */
static C_word C_fcall stub75(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub75(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::hertz_to_keynum(t0));
return C_r;}

/* from k720 */
static C_word C_fcall stub71(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub71(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_fix((C_word)Toolbox::keynum_to_pc(t0));
return C_r;}

/* from k713 */
static C_word C_fcall stub66(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub66(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::keynum_to_hertz(t0));
return C_r;}

/* from k706 */
static C_word C_fcall stub62(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub62(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_fix((C_word)Toolbox::scaler_to_cents(t0));
return C_r;}

/* from k699 */
static C_word C_fcall stub57(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub57(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_unfix(C_a0);
C_r=C_flonum(&C_a,Toolbox::cents_to_scaler(t0));
return C_r;}

/* from k692 */
static C_word C_fcall stub50(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2) C_regparm;
C_regparm static C_word C_fcall stub50(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
float t2=(float )C_c_double(C_a2);
C_r=C_flonum(&C_a,Toolbox::rhythm_to_seconds(t0,t1,t2));
return C_r;}

/* from k677 */
static C_word C_fcall stub42(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub42(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
C_r=C_flonum(&C_a,Toolbox::quantize(t0,t1));
return C_r;}

/* from k666 */
static C_word C_fcall stub35(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub35(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
int t1=(int )C_unfix(C_a1);
C_r=C_flonum(&C_a,Toolbox::decimals(t0,t1));
return C_r;}

/* from k655 */
static C_word C_fcall stub30(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub30(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_fix((C_word)Toolbox::float_to_fixnum(t0));
return C_r;}

/* from k648 */
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

/* from k621 */
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
C_noret_decl(f_587)
static void C_ccall f_587(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_590)
static void C_ccall f_590(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_593)
static void C_ccall f_593(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_596)
static void C_ccall f_596(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2042)
static void C_ccall f_2042(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2841)
static void C_ccall f_2841(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_2888)
static void C_ccall f_2888(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2878)
static void C_ccall f_2878(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2845)
static void C_ccall f_2845(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2045)
static void C_ccall f_2045(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2835)
static void C_ccall f_2835(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_2835)
static void C_ccall f_2835r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_2061)
static void C_ccall f_2061(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2274)
static void C_ccall f_2274(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2064)
static void C_ccall f_2064(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2067)
static void C_ccall f_2067(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2079)
static void C_ccall f_2079(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2127)
static void C_fcall f_2127(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_2143)
static void C_ccall f_2143(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2153)
static void C_ccall f_2153(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2252)
static void C_ccall f_2252(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2248)
static void C_ccall f_2248(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2197)
static void C_ccall f_2197(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2203)
static void C_ccall f_2203(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2137)
static void C_fcall f_2137(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2082)
static void C_ccall f_2082(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2087)
static void C_fcall f_2087(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2100)
static void C_fcall f_2100(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2284)
static void C_ccall f_2284(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2335)
static void C_ccall f_2335(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2338)
static void C_ccall f_2338(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2341)
static void C_ccall f_2341(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2344)
static void C_ccall f_2344(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2347)
static void C_ccall f_2347(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2350)
static void C_ccall f_2350(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2353)
static void C_ccall f_2353(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2356)
static void C_ccall f_2356(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2829)
static void C_ccall f_2829(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_2829)
static void C_ccall f_2829r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_2374)
static void C_ccall f_2374(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2377)
static void C_ccall f_2377(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2655)
static void C_fcall f_2655(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2763)
static void C_ccall f_2763(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2675)
static void C_fcall f_2675(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2684)
static void C_fcall f_2684(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2688)
static void C_ccall f_2688(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2692)
static void C_ccall f_2692(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2700)
static void C_fcall f_2700(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2696)
static void C_ccall f_2696(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2665)
static void C_ccall f_2665(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2380)
static void C_ccall f_2380(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2383)
static void C_ccall f_2383(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2386)
static void C_ccall f_2386(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2389)
static void C_ccall f_2389(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2392)
static void C_ccall f_2392(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2649)
static void C_ccall f_2649(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2548)
static void C_fcall f_2548(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2555)
static void C_ccall f_2555(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2557)
static void C_fcall f_2557(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2629)
static void C_ccall f_2629(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2581)
static void C_fcall f_2581(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2584)
static void C_ccall f_2584(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2605)
static void C_ccall f_2605(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2571)
static void C_ccall f_2571(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2395)
static void C_ccall f_2395(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2537)
static void C_ccall f_2537(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2525)
static void C_ccall f_2525(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2521)
static void C_ccall f_2521(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2402)
static void C_fcall f_2402(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2359)
static void C_ccall f_2359(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2827)
static void C_ccall f_2827(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2817)
static void C_ccall f_2817(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_2821)
static void C_ccall f_2821(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2328)
static void C_ccall f_2328(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_2322)
static void C_ccall f_2322(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2316)
static void C_ccall f_2316(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2310)
static void C_ccall f_2310(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_2304)
static void C_ccall f_2304(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_2298)
static void C_ccall f_2298(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_2292)
static void C_ccall f_2292(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_2286)
static void C_ccall f_2286(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_1603)
static void C_ccall f_1603(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2047)
static void C_fcall f_2047(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2055)
static void C_ccall f_2055(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2031)
static void C_ccall f_2031(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1713)
static void C_ccall f_1713(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2035)
static void C_ccall f_2035(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1973)
static void C_ccall f_1973(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1973)
static void C_ccall f_1973r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1991)
static void C_fcall f_1991(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2001)
static void C_ccall f_2001(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1977)
static void C_ccall f_1977(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1964)
static void C_ccall f_1964(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1691)
static void C_ccall f_1691(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1968)
static void C_ccall f_1968(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1958)
static void C_ccall f_1958(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1673)
static void C_ccall f_1673(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1949)
static void C_ccall f_1949(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1682)
static void C_ccall f_1682(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1953)
static void C_ccall f_1953(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1886)
static void C_ccall f_1886(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1886)
static void C_ccall f_1886r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1911)
static void C_fcall f_1911(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1638)
static void C_ccall f_1638(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1899)
static void C_ccall f_1899(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1718)
static void C_ccall f_1718(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_1718)
static void C_ccall f_1718r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_1837)
static void C_fcall f_1837(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1832)
static void C_fcall f_1832(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1720)
static void C_fcall f_1720(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_1827)
static void C_ccall f_1827(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1831)
static void C_ccall f_1831(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1823)
static void C_ccall f_1823(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1791)
static void C_fcall f_1791(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1816)
static void C_ccall f_1816(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1820)
static void C_ccall f_1820(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1801)
static void C_ccall f_1801(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1780)
static void C_ccall f_1780(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1750)
static void C_fcall f_1750(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1722)
static void C_fcall f_1722(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1696)
static void C_fcall f_1696(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1700)
static void C_ccall f_1700(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1652)
static void C_fcall f_1652(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_1656)
static void C_ccall f_1656(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1643)
static void C_fcall f_1643(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1647)
static void C_ccall f_1647(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1631)
static void C_ccall f_1631(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1628)
static void C_ccall f_1628(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1585)
static void C_ccall f_1585(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1590)
static void C_ccall f_1590(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1571)
static void C_ccall f_1571(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1576)
static void C_ccall f_1576(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1565)
static void C_ccall f_1565(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1559)
static void C_ccall f_1559(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1540)
static void C_ccall f_1540(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1540)
static void C_ccall f_1540r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1521)
static void C_ccall f_1521(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1521)
static void C_ccall f_1521r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1515)
static void C_ccall f_1515(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1475)
static void C_ccall f_1475(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1475)
static void C_ccall f_1475r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1456)
static void C_ccall f_1456(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1456)
static void C_ccall f_1456r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1412)
static void C_ccall f_1412(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1412)
static void C_ccall f_1412r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1406)
static void C_ccall f_1406(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1400)
static void C_ccall f_1400(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1394)
static void C_ccall f_1394(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1388)
static void C_ccall f_1388(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1388)
static void C_ccall f_1388r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1365)
static void C_ccall f_1365(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1382)
static void C_ccall f_1382(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1307)
static void C_ccall f_1307(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_1307)
static void C_ccall f_1307r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_1359)
static void C_ccall f_1359(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1343)
static void C_ccall f_1343(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1324)
static void C_ccall f_1324(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1219)
static void C_ccall f_1219(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1219)
static void C_ccall f_1219r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1265)
static void C_fcall f_1265(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1213)
static void C_ccall f_1213(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1154)
static void C_ccall f_1154(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_1154)
static void C_ccall f_1154r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_1167)
static void C_fcall f_1167(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_1203)
static void C_ccall f_1203(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1148)
static void C_ccall f_1148(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_1148)
static void C_ccall f_1148r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_1053)
static void C_ccall f_1053(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_1053)
static void C_ccall f_1053r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_1057)
static void C_ccall f_1057(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1060)
static void C_ccall f_1060(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1072)
static void C_fcall f_1072(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1094)
static void C_ccall f_1094(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1047)
static void C_ccall f_1047(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1041)
static void C_ccall f_1041(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1035)
static void C_ccall f_1035(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1029)
static void C_ccall f_1029(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1023)
static void C_ccall f_1023(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_963)
static void C_ccall f_963(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_963)
static void C_ccall f_963r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_975)
static void C_fcall f_975(C_word t0,C_word t1) C_noret;
C_noret_decl(f_970)
static void C_fcall f_970(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_965)
static void C_fcall f_965(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_944)
static void C_ccall f_944(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_944)
static void C_ccall f_944r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_938)
static void C_ccall f_938(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_932)
static void C_ccall f_932(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_850)
static void C_ccall f_850(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,...) C_noret;
C_noret_decl(f_850)
static void C_ccall f_850r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t7) C_noret;
C_noret_decl(f_864)
static void C_ccall f_864(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_831)
static void C_ccall f_831(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,...) C_noret;
C_noret_decl(f_831)
static void C_ccall f_831r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t8) C_noret;
C_noret_decl(f_818)
static void C_fcall f_818(C_word t0,C_word t1) C_noret;
C_noret_decl(f_808)
static void C_fcall f_808(C_word t0,C_word t1) C_noret;
C_noret_decl(f_797)
static void C_fcall f_797(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_790)
static void C_fcall f_790(C_word t0,C_word t1) C_noret;
C_noret_decl(f_779)
static void C_fcall f_779(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_741)
static void C_fcall f_741(C_word t0,C_word t1) C_noret;
C_noret_decl(f_734)
static void C_fcall f_734(C_word t0,C_word t1) C_noret;
C_noret_decl(f_659)
static void C_fcall f_659(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_625)
static void C_fcall f_625(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_598)
static void C_fcall f_598(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;

C_noret_decl(trf_2127)
static void C_fcall trf_2127(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2127(void *dummy){
C_word t4=C_pick(0);
C_word t3=C_pick(1);
C_word t2=C_pick(2);
C_word t1=C_pick(3);
C_word t0=C_pick(4);
C_adjust_stack(-5);
f_2127(t0,t1,t2,t3,t4);}

C_noret_decl(trf_2137)
static void C_fcall trf_2137(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2137(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2137(t0,t1);}

C_noret_decl(trf_2087)
static void C_fcall trf_2087(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2087(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_2087(t0,t1,t2);}

C_noret_decl(trf_2100)
static void C_fcall trf_2100(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2100(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2100(t0,t1);}

C_noret_decl(trf_2655)
static void C_fcall trf_2655(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2655(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_2655(t0,t1,t2);}

C_noret_decl(trf_2675)
static void C_fcall trf_2675(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2675(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2675(t0,t1);}

C_noret_decl(trf_2684)
static void C_fcall trf_2684(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2684(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2684(t0,t1);}

C_noret_decl(trf_2700)
static void C_fcall trf_2700(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2700(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2700(t0,t1);}

C_noret_decl(trf_2548)
static void C_fcall trf_2548(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2548(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2548(t0,t1);}

C_noret_decl(trf_2557)
static void C_fcall trf_2557(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2557(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_2557(t0,t1,t2);}

C_noret_decl(trf_2581)
static void C_fcall trf_2581(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2581(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2581(t0,t1);}

C_noret_decl(trf_2402)
static void C_fcall trf_2402(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2402(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2402(t0,t1);}

C_noret_decl(trf_2047)
static void C_fcall trf_2047(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2047(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_2047(t0,t1,t2);}

C_noret_decl(trf_1991)
static void C_fcall trf_1991(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1991(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1991(t0,t1,t2);}

C_noret_decl(trf_1911)
static void C_fcall trf_1911(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1911(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1911(t0,t1);}

C_noret_decl(trf_1837)
static void C_fcall trf_1837(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1837(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1837(t0,t1);}

C_noret_decl(trf_1832)
static void C_fcall trf_1832(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1832(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1832(t0,t1,t2);}

C_noret_decl(trf_1720)
static void C_fcall trf_1720(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1720(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_1720(t0,t1,t2,t3);}

C_noret_decl(trf_1791)
static void C_fcall trf_1791(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1791(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1791(t0,t1,t2);}

C_noret_decl(trf_1750)
static void C_fcall trf_1750(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1750(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1750(t0,t1);}

C_noret_decl(trf_1722)
static void C_fcall trf_1722(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1722(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1722(t0,t1);}

C_noret_decl(trf_1696)
static void C_fcall trf_1696(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1696(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1696(t0,t1);}

C_noret_decl(trf_1652)
static void C_fcall trf_1652(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1652(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_1652(t0,t1,t2,t3);}

C_noret_decl(trf_1643)
static void C_fcall trf_1643(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1643(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1643(t0,t1);}

C_noret_decl(trf_1265)
static void C_fcall trf_1265(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1265(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1265(t0,t1);}

C_noret_decl(trf_1167)
static void C_fcall trf_1167(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1167(void *dummy){
C_word t5=C_pick(0);
C_word t4=C_pick(1);
C_word t3=C_pick(2);
C_word t2=C_pick(3);
C_word t1=C_pick(4);
C_word t0=C_pick(5);
C_adjust_stack(-6);
f_1167(t0,t1,t2,t3,t4,t5);}

C_noret_decl(trf_1072)
static void C_fcall trf_1072(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1072(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1072(t0,t1,t2);}

C_noret_decl(trf_975)
static void C_fcall trf_975(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_975(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_975(t0,t1);}

C_noret_decl(trf_970)
static void C_fcall trf_970(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_970(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_970(t0,t1,t2);}

C_noret_decl(trf_965)
static void C_fcall trf_965(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_965(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_965(t0,t1,t2,t3);}

C_noret_decl(trf_818)
static void C_fcall trf_818(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_818(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_818(t0,t1);}

C_noret_decl(trf_808)
static void C_fcall trf_808(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_808(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_808(t0,t1);}

C_noret_decl(trf_797)
static void C_fcall trf_797(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_797(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_797(t0,t1,t2);}

C_noret_decl(trf_790)
static void C_fcall trf_790(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_790(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_790(t0,t1);}

C_noret_decl(trf_779)
static void C_fcall trf_779(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_779(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_779(t0,t1,t2);}

C_noret_decl(trf_741)
static void C_fcall trf_741(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_741(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_741(t0,t1);}

C_noret_decl(trf_734)
static void C_fcall trf_734(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_734(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_734(t0,t1);}

C_noret_decl(trf_659)
static void C_fcall trf_659(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_659(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_659(t0,t1,t2);}

C_noret_decl(trf_625)
static void C_fcall trf_625(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_625(void *dummy){
C_word t6=C_pick(0);
C_word t5=C_pick(1);
C_word t4=C_pick(2);
C_word t3=C_pick(3);
C_word t2=C_pick(4);
C_word t1=C_pick(5);
C_word t0=C_pick(6);
C_adjust_stack(-7);
f_625(t0,t1,t2,t3,t4,t5,t6);}

C_noret_decl(trf_598)
static void C_fcall trf_598(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_598(void *dummy){
C_word t6=C_pick(0);
C_word t5=C_pick(1);
C_word t4=C_pick(2);
C_word t3=C_pick(3);
C_word t2=C_pick(4);
C_word t1=C_pick(5);
C_word t0=C_pick(6);
C_adjust_stack(-7);
f_598(t0,t1,t2,t3,t4,t5,t6);}

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
if(!C_demand_2(1598)){
C_save(t1);
C_rereclaim2(1598*sizeof(C_word), 1);
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
lf[25]=C_static_lambda_info(C_heaptop,43,"(discrete x157 x1158 x2159 i1160 . args161)");
lf[26]=C_h_intern(&lf[26],3,"int");
lf[27]=C_static_lambda_info(C_heaptop,10,"(int f162)");
lf[28]=C_h_intern(&lf[28],8,"quantize");
lf[29]=C_static_lambda_info(C_heaptop,26,"(quantize num163 steps164)");
lf[30]=C_h_intern(&lf[30],8,"decimals");
lf[31]=C_static_lambda_info(C_heaptop,29,"(decimals num165 . digits166)");
lf[32]=C_h_intern(&lf[32],15,"rhythm->seconds");
lf[33]=C_static_lambda_info(C_heaptop,26,"(body171 tempo177 beat178)");
lf[34]=C_flonum(C_heaptop,0.25);
lf[35]=C_static_lambda_info(C_heaptop,26,"(def-beat174 %tempo169180)");
lf[36]=C_flonum(C_heaptop,60.0);
lf[37]=C_static_lambda_info(C_heaptop,14,"(def-tempo173)");
lf[38]=C_h_intern(&lf[38],9,"\003syserror");
lf[39]=C_static_lambda_info(C_heaptop,36,"(rhythm->seconds beats167 . args168)");
lf[40]=C_h_intern(&lf[40],13,"cents->scaler");
lf[41]=C_static_lambda_info(C_heaptop,24,"(cents->scaler cents187)");
lf[42]=C_h_intern(&lf[42],13,"scaler->cents");
lf[43]=C_static_lambda_info(C_heaptop,22,"(scaler->cents num188)");
lf[44]=C_h_intern(&lf[44],13,"keynum->hertz");
lf[45]=C_static_lambda_info(C_heaptop,20,"(keynum->hertz k189)");
lf[46]=C_h_intern(&lf[46],10,"keynum->pc");
lf[47]=C_static_lambda_info(C_heaptop,17,"(keynum->pc k190)");
lf[48]=C_h_intern(&lf[48],13,"hertz->keynum");
lf[49]=C_static_lambda_info(C_heaptop,21,"(hertz->keynum hz191)");
lf[50]=C_h_intern(&lf[50],7,"interpl");
lf[51]=C_h_intern(&lf[51],5,"error");
lf[52]=C_static_string(C_heaptop,27,"not an x y coordinate list:");
lf[53]=C_static_lambda_info(C_heaptop,15,"(do200 tail202)");
lf[54]=C_h_intern(&lf[54],3,"err");
lf[55]=C_static_string(C_heaptop,27,"not an x y coordinate list:");
lf[56]=C_static_string(C_heaptop,27,"not an x y coordinate list:");
lf[57]=C_static_lambda_info(C_heaptop,34,"(interpl x192 coords193 . base194)");
lf[58]=C_h_intern(&lf[58],6,"interp");
lf[59]=C_static_lambda_info(C_heaptop,23,"(interp x210 . args211)");
lf[60]=C_h_intern(&lf[60],5,"steps");
lf[61]=C_h_intern(&lf[61],6,"modulo");
lf[62]=C_static_lambda_info(C_heaptop,27,"(do216 i218 k219 l220 t221)");
lf[63]=C_static_lambda_info(C_heaptop,34,"(steps len212 keynum213 . args214)");
lf[64]=C_h_intern(&lf[64],8,"ran-set!");
lf[65]=C_static_lambda_info(C_heaptop,18,"(ran-set! seed226)");
lf[66]=C_h_intern(&lf[66],3,"ran");
lf[67]=C_flonum(C_heaptop,1.0);
lf[68]=C_static_lambda_info(C_heaptop,15,"(ran . args227)");
lf[69]=C_h_intern(&lf[69],4,"odds");
lf[70]=C_flonum(C_heaptop,1.0);
lf[71]=C_flonum(C_heaptop,1.0);
lf[72]=C_flonum(C_heaptop,1.0);
lf[73]=C_static_lambda_info(C_heaptop,21,"(odds n228 . args229)");
lf[74]=C_h_intern(&lf[74],5,"pickl");
lf[75]=C_static_string(C_heaptop,29,"cannot pick from empty list: ");
lf[76]=C_static_lambda_info(C_heaptop,15,"(pickl args230)");
lf[77]=C_h_intern(&lf[77],4,"pick");
lf[78]=C_static_lambda_info(C_heaptop,16,"(pick . args231)");
lf[79]=C_h_intern(&lf[79],6,"ranlow");
lf[80]=C_static_lambda_info(C_heaptop,8,"(ranlow)");
lf[81]=C_h_intern(&lf[81],7,"ranhigh");
lf[82]=C_static_lambda_info(C_heaptop,9,"(ranhigh)");
lf[83]=C_h_intern(&lf[83],9,"ranmiddle");
lf[84]=C_static_lambda_info(C_heaptop,11,"(ranmiddle)");
lf[85]=C_h_intern(&lf[85],7,"ranbeta");
lf[86]=C_flonum(C_heaptop,0.5);
lf[87]=C_flonum(C_heaptop,0.5);
lf[88]=C_static_lambda_info(C_heaptop,19,"(ranbeta . args232)");
lf[89]=C_h_intern(&lf[89],6,"ranexp");
lf[90]=C_static_lambda_info(C_heaptop,18,"(ranexp . args233)");
lf[91]=C_h_intern(&lf[91],8,"rangauss");
lf[92]=C_static_lambda_info(C_heaptop,20,"(rangauss . args234)");
lf[93]=C_h_intern(&lf[93],9,"rancauchy");
lf[94]=C_static_lambda_info(C_heaptop,11,"(rancauchy)");
lf[95]=C_h_intern(&lf[95],10,"ranpoisson");
lf[96]=C_h_intern(&lf[96],3,"arg");
lf[97]=C_static_lambda_info(C_heaptop,22,"(ranpoisson . args235)");
lf[98]=C_h_intern(&lf[98],8,"rangamma");
lf[99]=C_static_lambda_info(C_heaptop,20,"(rangamma . args236)");
lf[100]=C_h_intern(&lf[100],8,"ranbrown");
lf[101]=C_static_lambda_info(C_heaptop,10,"(ranbrown)");
lf[102]=C_h_intern(&lf[102],7,"ranpink");
lf[103]=C_static_lambda_info(C_heaptop,9,"(ranpink)");
lf[104]=C_h_intern(&lf[104],13,"print-message");
lf[105]=C_h_intern(&lf[105],17,"\003sysmake-c-string");
lf[106]=C_static_lambda_info(C_heaptop,23,"(print-message a293297)");
lf[107]=C_h_intern(&lf[107],11,"print-error");
lf[108]=C_static_lambda_info(C_heaptop,21,"(print-error a299303)");
lf[109]=C_h_intern(&lf[109],25,"current-time-milliseconds");
lf[110]=C_static_lambda_info(C_heaptop,27,"(current-time-milliseconds)");
lf[111]=C_h_intern(&lf[111],20,"current-time-seconds");
lf[112]=C_static_lambda_info(C_heaptop,22,"(current-time-seconds)");
lf[114]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[115]=C_h_intern(&lf[115],6,"\003sysgc");
lf[116]=C_static_lambda_info(C_heaptop,41,"(scheduler-set-time-milliseconds a329332)");
lf[118]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[119]=C_static_lambda_info(C_heaptop,42,"(scheduler-sprout a337340 a336341 a335342)");
lf[121]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[122]=C_static_lambda_info(C_heaptop,24,"(scheduler-stop a357360)");
lf[123]=C_h_intern(&lf[123],6,"sprout");
lf[124]=C_static_lambda_info(C_heaptop,11,"(nextstart)");
lf[125]=C_static_lambda_info(C_heaptop,8,"(nextid)");
lf[126]=C_static_lambda_info(C_heaptop,12,"(do385 p387)");
lf[127]=C_static_lambda_info(C_heaptop,24,"(body371 start377 id378)");
lf[128]=C_static_lambda_info(C_heaptop,24,"(def-id374 %start369393)");
lf[129]=C_static_lambda_info(C_heaptop,14,"(def-start373)");
lf[130]=C_static_lambda_info(C_heaptop,26,"(sprout proc367 . args368)");
lf[131]=C_h_intern(&lf[131],3,"now");
lf[132]=C_h_intern(&lf[132],11,"time-format");
lf[133]=C_flonum(C_heaptop,1.0);
lf[134]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[135]=C_flonum(C_heaptop,1.0);
lf[136]=C_h_intern(&lf[136],1,"m");
lf[137]=C_static_string(C_heaptop,17,"not a time-format");
lf[138]=C_h_intern(&lf[138],1,"s");
lf[139]=C_static_lambda_info(C_heaptop,22,"(time-format . arg399)");
lf[140]=C_h_intern(&lf[140],5,"pause");
lf[141]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[142]=C_static_lambda_info(C_heaptop,7,"(pause)");
lf[143]=C_h_intern(&lf[143],7,"paused\077");
lf[144]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[145]=C_static_lambda_info(C_heaptop,9,"(paused\077)");
lf[146]=C_h_intern(&lf[146],4,"cont");
lf[147]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[148]=C_static_lambda_info(C_heaptop,6,"(cont)");
lf[149]=C_h_intern(&lf[149],4,"stop");
lf[150]=C_static_string(C_heaptop,17,"Not an integer id");
lf[151]=C_static_lambda_info(C_heaptop,15,"(do413 tail415)");
lf[152]=C_static_lambda_info(C_heaptop,18,"(stop . procid412)");
lf[153]=C_h_intern(&lf[153],4,"hush");
lf[154]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[155]=C_static_lambda_info(C_heaptop,6,"(hush)");
lf[158]=C_h_intern(&lf[158],7,"sprintf");
lf[159]=C_static_lambda_info(C_heaptop,23,"(ferror str426 args427)");
lf[160]=C_h_intern(&lf[160],7,"mp:note");
lf[161]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[162]=C_static_lambda_info(C_heaptop,46,"(mp:note time464 dur465 key466 amp467 chan468)");
lf[163]=C_h_intern(&lf[163],5,"mp:on");
lf[164]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[165]=C_static_lambda_info(C_heaptop,37,"(mp:on time469 key470 vel471 chan472)");
lf[166]=C_h_intern(&lf[166],6,"mp:off");
lf[167]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[168]=C_static_lambda_info(C_heaptop,38,"(mp:off time473 key474 vel475 chan476)");
lf[169]=C_h_intern(&lf[169],7,"mp:prog");
lf[170]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[171]=C_static_lambda_info(C_heaptop,33,"(mp:prog time477 prog478 chan479)");
lf[172]=C_h_intern(&lf[172],7,"mp:ctrl");
lf[173]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[174]=C_static_lambda_info(C_heaptop,40,"(mp:ctrl time480 ctrl481 val482 chan483)");
lf[175]=C_h_intern(&lf[175],9,"mp:alloff");
lf[176]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[177]=C_static_lambda_info(C_heaptop,11,"(mp:alloff)");
lf[178]=C_h_intern(&lf[178],8,"mp:micro");
lf[179]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[180]=C_static_lambda_info(C_heaptop,18,"(mp:micro divs484)");
lf[181]=C_h_intern(&lf[181],9,"mp:inhook");
lf[182]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[183]=C_static_lambda_info(C_heaptop,36,"(mp:inhook func485 chans486 mask487)");
lf[184]=C_h_intern(&lf[184],3,"sal");
lf[185]=C_h_intern(&lf[185],5,"print");
lf[186]=C_static_lambda_info(C_heaptop,22,"(sal str526 tokens527)");
lf[187]=C_h_intern(&lf[187],14,"return-to-host");
lf[188]=C_h_intern(&lf[188],4,"else");
lf[189]=C_h_intern(&lf[189],4,"cond");
lf[190]=C_h_intern(&lf[190],6,"lambda");
lf[191]=C_h_intern(&lf[191],7,"elapsed");
lf[192]=C_h_intern(&lf[192],1,"x");
lf[193]=C_h_intern(&lf[193],4,"set!");
lf[194]=C_h_intern(&lf[194],4,"wait");
lf[195]=C_h_intern(&lf[195],4,"let*");
lf[196]=C_h_intern(&lf[196],5,"quote");
lf[197]=C_h_intern(&lf[197],3,"exn");
lf[198]=C_h_intern(&lf[198],7,"message");
lf[199]=C_h_intern(&lf[199],27,"condition-property-accessor");
lf[200]=C_static_string(C_heaptop,48,">>> Error: ~A~%    Aborting process at time ~S~%");
lf[201]=C_h_intern(&lf[201],22,"with-exception-handler");
lf[202]=C_h_intern(&lf[202],30,"call-with-current-continuation");
lf[203]=C_h_intern(&lf[203],10,"\003sysappend");
lf[204]=C_h_intern(&lf[204],6,"safety");
lf[205]=C_h_intern(&lf[205],4,"cdar");
lf[206]=C_static_string(C_heaptop,19,"unknown declaration");
lf[207]=C_h_intern(&lf[207],4,"caar");
lf[208]=C_static_string(C_heaptop,31,"declaration not list (decl val)");
lf[209]=C_static_lambda_info(C_heaptop,15,"(do513 decl515)");
lf[210]=C_h_intern(&lf[210],7,"declare");
lf[211]=C_h_intern(&lf[211],6,"gensym");
lf[212]=C_h_intern(&lf[212],6,"append");
lf[213]=C_h_intern(&lf[213],5,"\000null");
lf[214]=C_static_string(C_heaptop,41,"binding clause not list (var init [step])");
lf[215]=C_static_lambda_info(C_heaptop,15,"(do497 tail499)");
lf[216]=C_static_string(C_heaptop,36,"go stopping clause missing test form");
lf[217]=C_static_string(C_heaptop,29,"go stopping clause not a list");
lf[218]=C_static_string(C_heaptop,22,"go bindings not a list");
lf[219]=C_static_lambda_info(C_heaptop,42,"(a2828 bindings488 terminate489 . body490)");
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
tmp=C_intern(C_heaptop,6,":chans");
C_save(tmp);
tmp=C_fix(0);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,5,":filt");
C_save(tmp);
tmp=C_fix(0);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[224]=C_h_list(4,C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(4);
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
tmp=C_intern(C_heaptop,5,"\000wait");
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
tmp=C_fix(0);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[230]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[231]=C_static_string(C_heaptop,7,"mp:prog");
tmp=C_intern(C_heaptop,7,"mp:prog");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000wait");
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
tmp=C_intern(C_heaptop,5,"\000wait");
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
tmp=C_fix(0);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[234]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[235]=C_static_string(C_heaptop,5,"mp:on");
tmp=C_intern(C_heaptop,5,"mp:on");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000wait");
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
tmp=C_fix(0);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[236]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[237]=C_static_string(C_heaptop,7,"mp:note");
tmp=C_intern(C_heaptop,7,"mp:note");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000wait");
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
tmp=C_flonum(C_heaptop,0.5);
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
lf[238]=C_h_list(6,C_pick(5),C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(6);
lf[239]=C_static_lambda_info(C_heaptop,15,"(do455 tail457)");
lf[240]=C_static_string(C_heaptop,37,"~S found duplicate keyword \047~S\047 in ~S");
lf[241]=C_static_string(C_heaptop,33,"~S missing value for keyword \047~S\047");
lf[242]=C_static_string(C_heaptop,53,"~S found invalid keyword \047~S\047~%Available keywords: ~S");
lf[243]=C_h_intern(&lf[243],7,"\003sysmap");
lf[244]=C_h_intern(&lf[244],3,"car");
lf[245]=C_static_string(C_heaptop,32,"~S expected keyword but got \047~S\047");
lf[246]=C_h_intern(&lf[246],8,"keyword\077");
lf[247]=C_static_string(C_heaptop,35,"~S expected ~A arguments but got ~A");
lf[248]=C_static_lambda_info(C_heaptop,28,"(do438 key440 arg441 pos442)");
lf[249]=C_static_string(C_heaptop,24,"~S is an invalid message");
lf[250]=C_static_lambda_info(C_heaptop,7,"(a2273)");
lf[251]=C_h_intern(&lf[251],14,"hash-table-ref");
lf[252]=C_h_intern(&lf[252],14,"symbol->string");
lf[253]=C_static_lambda_info(C_heaptop,25,"(a2834 mess462 . data463)");
lf[254]=C_h_intern(&lf[254],4,"send");
lf[255]=C_h_intern(&lf[255],10,"*messages*");
lf[256]=C_h_intern(&lf[256],14,"string->symbol");
lf[257]=C_static_string(C_heaptop,51,"message function not string, symbol or list of both");
lf[258]=C_static_lambda_info(C_heaptop,23,"(a2840 func420 info421)");
lf[259]=C_h_intern(&lf[259],19,"define-send-message");
lf[260]=C_h_intern(&lf[260],15,"make-hash-table");
lf[261]=C_h_intern(&lf[261],6,"equal\077");
lf[262]=C_static_lambda_info(C_heaptop,10,"(toplevel)");
C_register_lf2(lf,263,create_ptable());
t2=C_mutate(&lf[0],lf[1]);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_587,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_library_toplevel(2,C_SCHEME_UNDEFINED,t3);}

/* k585 */
static void C_ccall f_587(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_587,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_590,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_eval_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k588 in k585 */
static void C_ccall f_590(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_590,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_593,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k591 in k588 in k585 */
static void C_ccall f_593(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_593,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_596,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k594 in k591 in k588 in k585 */
static void C_ccall f_596(C_word c,C_word t0,C_word t1){
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
C_word ab[165],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_596,2,t0,t1);}
t2=C_mutate(&lf[2],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_598,a[2]=lf[3],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate(&lf[4],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_625,a[2]=lf[5],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate(&lf[6],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_659,a[2]=lf[7],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate(&lf[8],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_734,a[2]=lf[9],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate(&lf[10],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_741,a[2]=lf[11],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate(&lf[12],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_779,a[2]=lf[13],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate(&lf[14],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_790,a[2]=lf[15],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate(&lf[16],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_797,a[2]=lf[17],tmp=(C_word)a,a+=3,tmp));
t10=C_mutate(&lf[18],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_808,a[2]=lf[19],tmp=(C_word)a,a+=3,tmp));
t11=C_mutate(&lf[20],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_818,a[2]=lf[21],tmp=(C_word)a,a+=3,tmp));
t12=C_mutate((C_word*)lf[22]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_831,a[2]=lf[23],tmp=(C_word)a,a+=3,tmp));
t13=C_mutate((C_word*)lf[24]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_850,a[2]=lf[25],tmp=(C_word)a,a+=3,tmp));
t14=C_mutate((C_word*)lf[26]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_932,a[2]=lf[27],tmp=(C_word)a,a+=3,tmp));
t15=C_mutate((C_word*)lf[28]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_938,a[2]=lf[29],tmp=(C_word)a,a+=3,tmp));
t16=C_mutate((C_word*)lf[30]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_944,a[2]=lf[31],tmp=(C_word)a,a+=3,tmp));
t17=C_mutate((C_word*)lf[32]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_963,a[2]=lf[39],tmp=(C_word)a,a+=3,tmp));
t18=C_mutate((C_word*)lf[40]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1023,a[2]=lf[41],tmp=(C_word)a,a+=3,tmp));
t19=C_mutate((C_word*)lf[42]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1029,a[2]=lf[43],tmp=(C_word)a,a+=3,tmp));
t20=C_mutate((C_word*)lf[44]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1035,a[2]=lf[45],tmp=(C_word)a,a+=3,tmp));
t21=C_mutate((C_word*)lf[46]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1041,a[2]=lf[47],tmp=(C_word)a,a+=3,tmp));
t22=C_mutate((C_word*)lf[48]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1047,a[2]=lf[49],tmp=(C_word)a,a+=3,tmp));
t23=C_mutate((C_word*)lf[50]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1053,a[2]=lf[57],tmp=(C_word)a,a+=3,tmp));
t24=C_mutate((C_word*)lf[58]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1148,a[2]=lf[59],tmp=(C_word)a,a+=3,tmp));
t25=C_mutate((C_word*)lf[60]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1154,a[2]=lf[63],tmp=(C_word)a,a+=3,tmp));
t26=C_mutate((C_word*)lf[64]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1213,a[2]=lf[65],tmp=(C_word)a,a+=3,tmp));
t27=C_mutate((C_word*)lf[66]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1219,a[2]=lf[68],tmp=(C_word)a,a+=3,tmp));
t28=C_mutate((C_word*)lf[69]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1307,a[2]=lf[73],tmp=(C_word)a,a+=3,tmp));
t29=C_mutate((C_word*)lf[74]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1365,a[2]=lf[76],tmp=(C_word)a,a+=3,tmp));
t30=C_mutate((C_word*)lf[77]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1388,a[2]=lf[78],tmp=(C_word)a,a+=3,tmp));
t31=C_mutate((C_word*)lf[79]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1394,a[2]=lf[80],tmp=(C_word)a,a+=3,tmp));
t32=C_mutate((C_word*)lf[81]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1400,a[2]=lf[82],tmp=(C_word)a,a+=3,tmp));
t33=C_mutate((C_word*)lf[83]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1406,a[2]=lf[84],tmp=(C_word)a,a+=3,tmp));
t34=C_mutate((C_word*)lf[85]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1412,a[2]=lf[88],tmp=(C_word)a,a+=3,tmp));
t35=C_mutate((C_word*)lf[89]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1456,a[2]=lf[90],tmp=(C_word)a,a+=3,tmp));
t36=C_mutate((C_word*)lf[91]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1475,a[2]=lf[92],tmp=(C_word)a,a+=3,tmp));
t37=C_mutate((C_word*)lf[93]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1515,a[2]=lf[94],tmp=(C_word)a,a+=3,tmp));
t38=C_mutate((C_word*)lf[95]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1521,a[2]=lf[97],tmp=(C_word)a,a+=3,tmp));
t39=C_mutate((C_word*)lf[98]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1540,a[2]=lf[99],tmp=(C_word)a,a+=3,tmp));
t40=C_mutate((C_word*)lf[100]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1559,a[2]=lf[101],tmp=(C_word)a,a+=3,tmp));
t41=C_mutate((C_word*)lf[102]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1565,a[2]=lf[103],tmp=(C_word)a,a+=3,tmp));
t42=C_mutate((C_word*)lf[104]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1571,a[2]=lf[106],tmp=(C_word)a,a+=3,tmp));
t43=C_mutate((C_word*)lf[107]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1585,a[2]=lf[108],tmp=(C_word)a,a+=3,tmp));
t44=C_mutate((C_word*)lf[109]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1628,a[2]=lf[110],tmp=(C_word)a,a+=3,tmp));
t45=C_mutate((C_word*)lf[111]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1631,a[2]=lf[112],tmp=(C_word)a,a+=3,tmp));
t46=C_mutate(&lf[113],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1643,a[2]=lf[116],tmp=(C_word)a,a+=3,tmp));
t47=C_mutate(&lf[117],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1652,a[2]=lf[119],tmp=(C_word)a,a+=3,tmp));
t48=C_mutate(&lf[120],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1696,a[2]=lf[122],tmp=(C_word)a,a+=3,tmp));
t49=C_mutate((C_word*)lf[123]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1718,a[2]=lf[130],tmp=(C_word)a,a+=3,tmp));
t50=C_mutate((C_word*)lf[131]+1,*((C_word*)lf[111]+1));
t51=C_mutate((C_word*)lf[132]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1886,a[2]=lf[139],tmp=(C_word)a,a+=3,tmp));
t52=C_mutate((C_word*)lf[140]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1949,a[2]=lf[142],tmp=(C_word)a,a+=3,tmp));
t53=C_mutate((C_word*)lf[143]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1958,a[2]=lf[145],tmp=(C_word)a,a+=3,tmp));
t54=C_mutate((C_word*)lf[146]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1964,a[2]=lf[148],tmp=(C_word)a,a+=3,tmp));
t55=C_mutate((C_word*)lf[149]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1973,a[2]=lf[152],tmp=(C_word)a,a+=3,tmp));
t56=C_mutate((C_word*)lf[153]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2031,a[2]=lf[155],tmp=(C_word)a,a+=3,tmp));
t57=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2042,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 279  make-hash-table");
t58=C_retrieve(lf[260]);
((C_proc3)C_retrieve_proc(t58))(3,t58,t57,*((C_word*)lf[261]+1));}

/* k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2042(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2042,2,t0,t1);}
t2=C_mutate(&lf[156],t1);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2045,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2841,a[2]=lf[258],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 281  ##sys#register-macro");
t5=C_retrieve(lf[220]);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,lf[259],t4);}

/* a2840 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2841(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_2841,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_2845,a[2]=t6,a[3]=t1,a[4]=t3,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t4)[1]))){
t8=(C_word)C_i_car(((C_word*)t4)[1]);
t9=C_set_block_item(t6,0,t8);
t10=(C_word)C_i_cadr(((C_word*)t4)[1]);
t11=C_set_block_item(t4,0,t10);
t12=t7;
f_2845(2,t12,t11);}
else{
if(C_truep((C_word)C_i_stringp(((C_word*)t4)[1]))){
t8=C_set_block_item(t6,0,((C_word*)t4)[1]);
t9=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2878,a[2]=t7,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 288  string->symbol");
t10=*((C_word*)lf[256]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)t4)[1]);}
else{
if(C_truep((C_word)C_i_symbolp(((C_word*)t4)[1]))){
t8=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2888,a[2]=t7,a[3]=t6,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 290  symbol->string");
t9=*((C_word*)lf[252]+1);
((C_proc3)C_retrieve_proc(t9))(3,t9,t8,((C_word*)t4)[1]);}
else{
C_trace("ChickenBridge.scm: 292  error");
t8=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,lf[257]);}}}}

/* k2886 in a2840 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2888(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_2845(2,t3,t2);}

/* k2876 in a2840 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2878(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_2845(2,t3,t2);}

/* k2843 in a2840 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2845(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2845,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[4]);
t3=(C_word)C_a_i_list(&a,2,lf[196],t2);
t4=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_a_i_list(&a,4,lf[222],lf[255],((C_word*)((C_word*)t0)[2])[1],t3));}

/* k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2045(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2045,2,t0,t1);}
t2=C_mutate(&lf[157],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2047,a[2]=lf[159],tmp=(C_word)a,a+=3,tmp));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2284,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2835,a[2]=lf[253],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 368  ##sys#register-macro");
t5=C_retrieve(lf[220]);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,lf[254],t4);}

/* a2834 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2835(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+6)){
C_save_and_reclaim((void*)tr3r,(void*)f_2835r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_2835r(t0,t1,t2,t3);}}

static void C_ccall f_2835r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a=C_alloc(6);
t4=t3;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2061,a[2]=t1,a[3]=t5,tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_symbolp(t2))){
C_trace("ChickenBridge.scm: 299  symbol->string");
t7=*((C_word*)lf[252]+1);
((C_proc3)C_retrieve_proc(t7))(3,t7,t6,t2);}
else{
t7=t6;
f_2061(2,t7,t2);}}

/* k2059 in a2834 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2061(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2061,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2064,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2274,a[2]=lf[250],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 300  hash-table-ref");
t4=*((C_word*)lf[251]+1);
((C_proc5)C_retrieve_proc(t4))(5,t4,t2,lf[156],t1,t3);}

/* a2273 in k2059 in a2834 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2274(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2274,2,t0,t1);}
t2=t1;
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}

/* k2062 in k2059 in a2834 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2064(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2064,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_2067,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=t1;
if(C_truep(t3)){
t4=t2;
f_2067(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 301  ferror");
f_2047(t2,lf[249],(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]));}}

/* k2065 in k2062 in k2059 in a2834 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2067(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2067,2,t0,t1);}
t2=((C_word*)((C_word*)t0)[5])[1];
t3=(C_word)C_i_car(((C_word*)t0)[4]);
t4=(C_word)C_i_cdr(((C_word*)t0)[4]);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(C_word)C_i_length(t4);
t8=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_2079,a[2]=t7,a[3]=t2,a[4]=((C_word*)t0)[2],a[5]=t6,a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[3],a[8]=t4,a[9]=t3,tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 308  append");
t9=*((C_word*)lf[212]+1);
((C_proc4)C_retrieve_proc(t9))(4,t9,t8,t4,C_SCHEME_END_OF_LIST);}

/* k2077 in k2065 in k2062 in k2059 in a2834 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2079(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[19],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2079,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_2082,a[2]=((C_word*)t0)[7],a[3]=((C_word*)t0)[8],a[4]=t1,a[5]=((C_word*)t0)[9],tmp=(C_word)a,a+=6,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_2127,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[5],a[8]=t4,a[9]=((C_word*)t0)[6],a[10]=lf[248],tmp=(C_word)a,a+=11,tmp));
t6=((C_word*)t4)[1];
f_2127(t6,t2,C_SCHEME_FALSE,C_SCHEME_FALSE,C_fix(0));}

/* do438 in k2077 in k2065 in k2062 in k2059 in a2834 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_fcall f_2127(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
C_save_and_reclaim((void*)trf_2127,NULL,5,t0,t1,t2,t3,t4);}
t5=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[9])[1]))){
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,C_SCHEME_FALSE);}
else{
t8=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_2137,a[2]=t7,a[3]=t6,a[4]=t5,a[5]=t1,a[6]=((C_word*)t0)[8],tmp=(C_word)a,a+=7,tmp);
t9=(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_2143,a[2]=((C_word*)t0)[2],a[3]=t7,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=t6,a[8]=((C_word*)t0)[6],a[9]=t5,a[10]=((C_word*)t0)[9],a[11]=t8,a[12]=((C_word*)t0)[7],tmp=(C_word)a,a+=13,tmp);
t10=((C_word*)((C_word*)t0)[7])[1];
if(C_truep(t10)){
t11=t9;
f_2143(2,t11,C_SCHEME_FALSE);}
else{
t11=(C_word)C_i_car(((C_word*)((C_word*)t0)[9])[1]);
C_trace("ChickenBridge.scm: 319  keyword?");
t12=C_retrieve(lf[246]);
((C_proc3)C_retrieve_proc(t12))(3,t12,t9,t11);}}}

/* k2141 in do438 in k2077 in k2065 in k2062 in k2059 in a2834 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2143(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2143,2,t0,t1);}
if(C_truep(t1)){
t2=C_set_block_item(((C_word*)t0)[12],0,C_SCHEME_TRUE);
t3=((C_word*)t0)[11];
f_2137(t3,t2);}
else{
t2=((C_word*)((C_word*)t0)[12])[1];
if(C_truep(t2)){
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[10])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[9])+1,t3);
t5=(C_word)C_i_assoc(((C_word*)((C_word*)t0)[9])[1],((C_word*)t0)[8]);
t6=C_mutate(((C_word *)((C_word*)t0)[7])+1,t5);
t7=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[10])[1]);
t8=C_mutate(((C_word *)((C_word*)t0)[10])+1,t7);
t9=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_2197,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[9],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[11],a[6]=((C_word*)t0)[10],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t10=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_2252,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[9],a[5]=((C_word*)t0)[5],a[6]=t9,a[7]=((C_word*)t0)[10],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 339  keyword?");
t11=C_retrieve(lf[246]);
((C_proc3)C_retrieve_proc(t11))(3,t11,t10,((C_word*)((C_word*)t0)[9])[1]);}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_2153,a[2]=((C_word*)t0)[11],a[3]=((C_word*)t0)[10],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[6],tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_nequalp(((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]))){
t4=(C_word)C_i_length(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 329  ferror");
f_2047(t3,lf[247],(C_word)C_a_i_list(&a,3,((C_word*)t0)[5],((C_word*)t0)[2],t4));}
else{
t4=t3;
f_2153(2,t4,C_SCHEME_UNDEFINED);}}}}

/* k2151 in k2141 in do438 in k2077 in k2065 in k2062 in k2059 in a2834 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2153(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2153,2,t0,t1);}
t2=(C_word)C_i_list_tail(((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]);
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
t4=(C_word)C_i_set_car(t2,t3);
t5=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[3])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t5);
t7=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[4])[1],C_fix(1));
t8=C_mutate(((C_word *)((C_word*)t0)[4])+1,t7);
t9=((C_word*)t0)[2];
f_2137(t9,t8);}

/* k2250 in k2141 in do438 in k2077 in k2065 in k2062 in k2059 in a2834 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2252(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2252,2,t0,t1);}
if(C_truep(t1)){
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[7])[1]))){
C_trace("ChickenBridge.scm: 343  ferror");
f_2047(((C_word*)t0)[6],lf[241],(C_word)C_a_i_list(&a,2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]));}
else{
t2=((C_word*)((C_word*)t0)[3])[1];
if(C_truep(t2)){
t3=((C_word*)t0)[6];
f_2197(2,t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2248,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
C_trace("map");
t4=*((C_word*)lf[243]+1);
((C_proc4)(void*)(*((C_word*)t4+1)))(4,t4,t3,*((C_word*)lf[244]+1),((C_word*)t0)[2]);}}}
else{
C_trace("ChickenBridge.scm: 340  ferror");
f_2047(((C_word*)t0)[6],lf[245],(C_word)C_a_i_list(&a,2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]));}}

/* k2246 in k2250 in k2141 in do438 in k2077 in k2065 in k2062 in k2059 in a2834 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2248(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2248,2,t0,t1);}
C_trace("ChickenBridge.scm: 346  ferror");
f_2047(((C_word*)t0)[4],lf[242],(C_word)C_a_i_list(&a,3,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1));}

/* k2195 in k2141 in do438 in k2077 in k2065 in k2062 in k2059 in a2834 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2197(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[14],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2197,2,t0,t1);}
t2=(C_word)C_i_member(((C_word*)((C_word*)t0)[8])[1],((C_word*)t0)[7]);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2203,a[2]=((C_word*)t0)[5],a[3]=t2,a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
if(C_truep(t2)){
t4=t3;
f_2203(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 353  ferror");
f_2047(t3,lf[240],(C_word)C_a_i_list(&a,3,((C_word*)t0)[4],((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]));}}

/* k2201 in k2195 in k2141 in do438 in k2077 in k2065 in k2062 in k2059 in a2834 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2203(C_word c,C_word t0,C_word t1){
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
f_2137(t6,t5);}

/* k2135 in do438 in k2077 in k2065 in k2062 in k2059 in a2834 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_fcall f_2137(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[6])[1];
f_2127(t2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k2080 in k2077 in k2065 in k2062 in k2059 in a2834 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2082(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2082,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_2087,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=lf[239],tmp=(C_word)a,a+=7,tmp));
t5=((C_word*)t3)[1];
f_2087(t5,((C_word*)t0)[2],((C_word*)t0)[4]);}

/* do455 in k2080 in k2077 in k2065 in k2062 in k2059 in a2834 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_fcall f_2087(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2087,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[5],((C_word*)t0)[4]));}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2100,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_member(t4,((C_word*)t0)[2]))){
t5=(C_word)C_i_car(t2);
t6=(C_word)C_i_cadr(t5);
t7=t3;
f_2100(t7,(C_word)C_i_set_car(t2,t6));}
else{
t5=t3;
f_2100(t5,C_SCHEME_UNDEFINED);}}}

/* k2098 in do455 in k2080 in k2077 in k2065 in k2062 in k2059 in a2834 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_fcall f_2100(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_2087(t3,((C_word*)t0)[2],t2);}

/* k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2284(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2284,2,t0,t1);}
t2=C_mutate((C_word*)lf[160]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2286,a[2]=lf[162],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[163]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2292,a[2]=lf[165],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate((C_word*)lf[166]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2298,a[2]=lf[168],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate((C_word*)lf[169]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2304,a[2]=lf[171],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[172]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2310,a[2]=lf[174],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate((C_word*)lf[175]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2316,a[2]=lf[177],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate((C_word*)lf[178]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2322,a[2]=lf[180],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate((C_word*)lf[181]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2328,a[2]=lf[183],tmp=(C_word)a,a+=3,tmp));
t10=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2335,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 395  hash-table-set!");
t11=C_retrieve(lf[222]);
((C_proc5)C_retrieve_proc(t11))(5,t11,t10,lf[156],lf[237],lf[238]);}

/* k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2335(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2335,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2338,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 396  hash-table-set!");
t3=C_retrieve(lf[222]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[156],lf[235],lf[236]);}

/* k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2338(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2338,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2341,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 397  hash-table-set!");
t3=C_retrieve(lf[222]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[156],lf[233],lf[234]);}

/* k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2341(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2341,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2344,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 398  hash-table-set!");
t3=C_retrieve(lf[222]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[156],lf[231],lf[232]);}

/* k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2344(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2344,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2347,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 399  hash-table-set!");
t3=C_retrieve(lf[222]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[156],lf[229],lf[230]);}

/* k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2347(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2347,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2350,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 400  hash-table-set!");
t3=C_retrieve(lf[222]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[156],lf[227],lf[228]);}

/* k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2350(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2350,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2353,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 401  hash-table-set!");
t3=C_retrieve(lf[222]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[156],lf[225],lf[226]);}

/* k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2353(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2353,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2356,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 402  hash-table-set!");
t3=C_retrieve(lf[222]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[156],lf[223],lf[224]);}

/* k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2356(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2356,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2359,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2829,a[2]=lf[219],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 408  ##sys#register-macro");
t4=C_retrieve(lf[220]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,lf[221],t3);}

/* a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2829(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+17)){
C_save_and_reclaim((void*)tr4r,(void*)f_2829r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest(a,C_rest_count(0));
f_2829r(t0,t1,t2,t3,t4);}}

static void C_ccall f_2829r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
t13=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_2374,a[2]=t2,a[3]=t12,a[4]=t6,a[5]=t10,a[6]=t1,a[7]=t8,a[8]=t3,tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(t2))){
t14=t13;
f_2374(2,t14,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 417  error");
t14=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t14))(4,t14,t13,lf[218],t2);}}

/* k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2374(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2374,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_2377,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(((C_word*)t0)[8]))){
if(C_truep((C_word)C_i_nullp(((C_word*)t0)[8]))){
C_trace("ChickenBridge.scm: 421  error");
t3=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,lf[216]);}
else{
t3=t2;
f_2377(2,t3,C_SCHEME_UNDEFINED);}}
else{
C_trace("ChickenBridge.scm: 419  error");
t3=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t2,lf[217],((C_word*)t0)[8]);}}

/* k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2377(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2377,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_2380,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],tmp=(C_word)a,a+=8,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_2655,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[7],a[5]=t4,a[6]=lf[215],tmp=(C_word)a,a+=7,tmp));
t6=((C_word*)t4)[1];
f_2655(t6,t2,((C_word*)t0)[2]);}

/* do497 in k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_fcall f_2655(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_2655,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2665,a[2]=t1,a[3]=((C_word*)t0)[5],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_2675,a[2]=t3,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=t2,tmp=(C_word)a,a+=7,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2763,a[2]=t4,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t7=(C_word)C_i_car(t2);
t8=(C_word)C_i_length(t7);
C_trace("ChickenBridge.scm: 425  <");
C_lessp(5,0,t6,C_fix(0),t8,C_fix(4));}
else{
t6=t4;
f_2675(t6,C_SCHEME_FALSE);}}}

/* k2761 in do497 in k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2763(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=(C_word)C_i_car(t2);
t4=((C_word*)t0)[2];
f_2675(t4,(C_word)C_i_symbolp(t3));}
else{
t2=((C_word*)t0)[2];
f_2675(t2,C_SCHEME_FALSE);}}

/* k2673 in do497 in k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_fcall f_2675(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_2675,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[6]);
t3=(C_word)C_i_car(t2);
t4=(C_word)C_i_car(((C_word*)t0)[6]);
t5=(C_word)C_i_cadr(t4);
t6=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_2684,a[2]=t5,a[3]=t3,a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[5],tmp=(C_word)a,a+=8,tmp);
t7=(C_word)C_i_car(((C_word*)t0)[6]);
t8=(C_word)C_i_cddr(t7);
if(C_truep((C_word)C_i_nullp(t8))){
t9=t6;
f_2684(t9,lf[213]);}
else{
t9=(C_word)C_i_car(((C_word*)t0)[6]);
t10=t6;
f_2684(t10,(C_word)C_i_caddr(t9));}}
else{
t2=(C_word)C_i_car(((C_word*)t0)[6]);
C_trace("ChickenBridge.scm: 438  error");
t3=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[2],lf[214],t2);}}

/* k2682 in k2673 in do497 in k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_fcall f_2684(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2684,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_2688,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t3=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 433  append");
t4=*((C_word*)lf[212]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,((C_word*)((C_word*)t0)[7])[1],t3);}

/* k2686 in k2682 in k2673 in do497 in k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2688(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2688,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_2692,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
t4=(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 434  append");
t5=*((C_word*)lf[212]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,((C_word*)((C_word*)t0)[7])[1],t4);}

/* k2690 in k2686 in k2682 in k2673 in do497 in k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2692(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2692,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2696,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2700,a[2]=((C_word*)t0)[5],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_eqp(((C_word*)t0)[3],lf[213]);
if(C_truep(t5)){
t6=t4;
f_2700(t6,C_SCHEME_END_OF_LIST);}
else{
t6=(C_word)C_a_i_list(&a,3,lf[193],((C_word*)t0)[2],((C_word*)t0)[3]);
t7=t4;
f_2700(t7,(C_word)C_a_i_list(&a,1,t6));}}

/* k2698 in k2690 in k2686 in k2682 in k2673 in do497 in k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_fcall f_2700(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 435  append");
t2=*((C_word*)lf[212]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k2694 in k2690 in k2686 in k2682 in k2673 in do497 in k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2696(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_2665(2,t3,t2);}

/* k2663 in do497 in k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2665(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_2655(t3,((C_word*)t0)[2],t2);}

/* k2378 in k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2380(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2380,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_2383,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 440  gensym");
t3=C_retrieve(lf[211]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k2381 in k2378 in k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2383(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2383,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_2386,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 441  gensym");
t3=C_retrieve(lf[211]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k2384 in k2381 in k2378 in k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2386(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2386,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_2389,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 442  gensym");
t3=C_retrieve(lf[211]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k2387 in k2384 in k2381 in k2378 in k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2389(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2389,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_2392,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],a[10]=((C_word*)t0)[9],tmp=(C_word)a,a+=11,tmp);
C_trace("ChickenBridge.scm: 443  gensym");
t3=C_retrieve(lf[211]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k2390 in k2387 in k2384 in k2381 in k2378 in k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2392(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2392,2,t0,t1);}
t2=C_SCHEME_TRUE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_SCHEME_END_OF_LIST;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_2395,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=t3,a[7]=((C_word*)t0)[5],a[8]=((C_word*)t0)[6],a[9]=((C_word*)t0)[7],a[10]=((C_word*)t0)[8],a[11]=((C_word*)t0)[9],a[12]=t5,a[13]=((C_word*)t0)[10],tmp=(C_word)a,a+=14,tmp);
t7=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2548,a[2]=t6,a[3]=t3,a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)((C_word*)t0)[3])[1]))){
t8=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
if(C_truep((C_word)C_i_pairp(t8))){
t9=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2649,a[2]=t7,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 449  caar");
t10=*((C_word*)lf[207]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)((C_word*)t0)[3])[1]);}
else{
t9=t7;
f_2548(t9,C_SCHEME_FALSE);}}
else{
t8=t7;
f_2548(t8,C_SCHEME_FALSE);}}

/* k2647 in k2390 in k2387 in k2384 in k2381 in k2378 in k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2649(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_2548(t2,(C_word)C_eqp(t1,lf[210]));}

/* k2546 in k2390 in k2387 in k2384 in k2381 in k2378 in k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_fcall f_2548(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2548,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2555,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 450  cdar");
t3=*((C_word*)lf[205]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)((C_word*)t0)[4])[1]);}
else{
t2=((C_word*)t0)[2];
f_2395(2,t2,C_SCHEME_UNDEFINED);}}

/* k2553 in k2546 in k2390 in k2387 in k2384 in k2381 in k2378 in k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2555(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2555,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_2557,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=lf[209],tmp=(C_word)a,a+=6,tmp));
t5=((C_word*)t3)[1];
f_2557(t5,((C_word*)t0)[2],t1);}

/* do513 in k2553 in k2546 in k2390 in k2387 in k2384 in k2381 in k2378 in k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_fcall f_2557(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_2557,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[4])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[4])+1,t3);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,t4);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2571,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2581,a[2]=t2,a[3]=((C_word*)t0)[2],a[4]=t3,tmp=(C_word)a,a+=5,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2629,a[2]=t4,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 454  cdar");
t7=*((C_word*)lf[205]+1);
((C_proc3)C_retrieve_proc(t7))(3,t7,t6,t2);}
else{
t6=t4;
f_2581(t6,C_SCHEME_FALSE);}}}

/* k2627 in do513 in k2553 in k2546 in k2390 in k2387 in k2384 in k2381 in k2378 in k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2629(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_2581(t2,(C_word)C_i_pairp(t1));}

/* k2579 in do513 in k2553 in k2546 in k2390 in k2387 in k2384 in k2381 in k2378 in k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_fcall f_2581(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2581,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2584,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 455  caar");
t3=*((C_word*)lf[207]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)t0)[2]);}
else{
t2=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 461  error");
t3=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[4],lf[208],t2);}}

/* k2582 in k2579 in do513 in k2553 in k2546 in k2390 in k2387 in k2384 in k2381 in k2378 in k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2584(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2584,2,t0,t1);}
t2=(C_word)C_eqp(t1,lf[204]);
if(C_truep(t2)){
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2605,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 457  cdar");
t4=*((C_word*)lf[205]+1);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)t0)[2]);}
else{
t3=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 460  error");
t4=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,((C_word*)t0)[4],lf[206],t3);}}

/* k2603 in k2582 in k2579 in do513 in k2553 in k2546 in k2390 in k2387 in k2384 in k2381 in k2378 in k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2605(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep((C_word)C_i_car(t1))){
t2=((C_word*)t0)[3];
f_2571(2,t2,C_SCHEME_UNDEFINED);}
else{
t2=C_set_block_item(((C_word*)t0)[2],0,C_SCHEME_FALSE);
t3=((C_word*)t0)[3];
f_2571(2,t3,t2);}}

/* k2569 in do513 in k2553 in k2546 in k2390 in k2387 in k2384 in k2381 in k2378 in k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2571(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_2557(t3,((C_word*)t0)[2],t2);}

/* k2393 in k2390 in k2387 in k2384 in k2381 in k2378 in k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2395(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2395,2,t0,t1);}
t2=(C_word)C_i_car(((C_word*)t0)[13]);
t3=(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_2537,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],a[10]=((C_word*)t0)[10],a[11]=((C_word*)t0)[11],a[12]=((C_word*)t0)[12],a[13]=t2,tmp=(C_word)a,a+=14,tmp);
t4=(C_word)C_i_cdr(((C_word*)t0)[13]);
t5=(C_word)C_a_i_list(&a,1,C_fix(-1));
C_trace("ChickenBridge.scm: 412  ##sys#append");
t6=*((C_word*)lf[203]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t3,t4,t5);}

/* k2535 in k2393 in k2390 in k2387 in k2384 in k2381 in k2378 in k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2537(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2537,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[13],t1);
t3=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_2521,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],a[8]=((C_word*)t0)[10],a[9]=((C_word*)t0)[11],a[10]=((C_word*)t0)[12],a[11]=t2,tmp=(C_word)a,a+=12,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2525,a[2]=((C_word*)t0)[3],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_a_i_list(&a,1,((C_word*)t0)[10]);
C_trace("ChickenBridge.scm: 412  ##sys#append");
t6=*((C_word*)lf[203]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t4,((C_word*)((C_word*)t0)[2])[1],t5);}

/* k2523 in k2535 in k2393 in k2390 in k2387 in k2384 in k2381 in k2378 in k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2525(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 412  ##sys#append");
t2=*((C_word*)lf[203]+1);
((C_proc4)(void*)(*((C_word*)t2+1)))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k2519 in k2535 in k2393 in k2390 in k2387 in k2384 in k2381 in k2378 in k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2521(C_word c,C_word t0,C_word t1){
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
C_word ab[122],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2521,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,lf[188],t1);
t3=(C_word)C_a_i_list(&a,3,lf[189],((C_word*)t0)[11],t2);
t4=C_mutate(((C_word *)((C_word*)t0)[10])+1,t3);
t5=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_2402,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],a[5]=((C_word*)t0)[10],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],tmp=(C_word)a,a+=8,tmp);
if(C_truep(((C_word*)((C_word*)t0)[4])[1])){
t6=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
t7=(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]);
t8=(C_word)C_a_i_list(&a,2,lf[196],lf[197]);
t9=(C_word)C_a_i_list(&a,2,lf[196],lf[198]);
t10=(C_word)C_a_i_list(&a,3,lf[199],t8,t9);
t11=(C_word)C_a_i_list(&a,2,t10,((C_word*)t0)[2]);
t12=(C_word)C_a_i_list(&a,4,lf[158],lf[200],t11,((C_word*)t0)[9]);
t13=(C_word)C_a_i_list(&a,2,lf[107],t12);
t14=(C_word)C_a_i_list(&a,2,((C_word*)t0)[3],C_fix(-2));
t15=(C_word)C_a_i_list(&a,4,lf[190],t7,t13,t14);
t16=(C_word)C_a_i_list(&a,3,lf[190],C_SCHEME_END_OF_LIST,((C_word*)((C_word*)t0)[10])[1]);
t17=(C_word)C_a_i_list(&a,3,lf[201],t15,t16);
t18=(C_word)C_a_i_list(&a,3,lf[190],t6,t17);
t19=(C_word)C_a_i_list(&a,2,lf[202],t18);
t20=C_mutate(((C_word *)((C_word*)t0)[10])+1,t19);
t21=t5;
f_2402(t21,t20);}
else{
t6=t5;
f_2402(t6,C_SCHEME_UNDEFINED);}}

/* k2400 in k2519 in k2535 in k2393 in k2390 in k2387 in k2384 in k2381 in k2378 in k2375 in k2372 in a2828 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_fcall f_2402(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_2402,NULL,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,((C_word*)t0)[7]);
t3=(C_word)C_a_i_list(&a,2,((C_word*)t0)[6],C_fix(0));
t4=(C_word)C_a_i_list(&a,3,lf[190],C_SCHEME_END_OF_LIST,((C_word*)t0)[7]);
t5=(C_word)C_a_i_list(&a,2,lf[191],t4);
t6=(C_word)C_a_i_list(&a,1,lf[192]);
t7=(C_word)C_a_i_list(&a,3,lf[193],((C_word*)t0)[6],lf[192]);
t8=(C_word)C_a_i_list(&a,3,lf[190],t6,t7);
t9=(C_word)C_a_i_list(&a,2,lf[194],t8);
t10=(C_word)C_a_i_list(&a,3,t3,t5,t9);
t11=(C_word)C_a_i_list(&a,3,lf[195],t10,((C_word*)((C_word*)t0)[5])[1]);
t12=(C_word)C_a_i_list(&a,3,lf[190],t2,t11);
t13=(C_word)C_a_i_list(&a,3,lf[190],((C_word*)((C_word*)t0)[4])[1],t12);
t14=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t14+1)))(2,t14,(C_word)C_a_i_cons(&a,2,t13,((C_word*)((C_word*)t0)[2])[1]));}

/* k2357 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2359(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2359,2,t0,t1);}
t2=C_mutate((C_word*)lf[184]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2817,a[2]=lf[186],tmp=(C_word)a,a+=3,tmp));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2827,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 514  return-to-host");
t4=C_retrieve(lf[187]);
((C_proc2)C_retrieve_proc(t4))(2,t4,t3);}

/* k2825 in k2357 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2827(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_UNDEFINED);}

/* sal in k2357 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2817(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_2817,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2821,a[2]=t3,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 509  print");
t5=*((C_word*)lf[185]+1);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,t2);}

/* k2819 in sal in k2357 in k2354 in k2351 in k2348 in k2345 in k2342 in k2339 in k2336 in k2333 in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2821(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 510  print");
t2=*((C_word*)lf[185]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* mp:inhook in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2328(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_2328,5,t0,t1,t2,t3,t4);}
C_trace("ChickenBridge.scm: 391  error");
t5=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t5))(3,t5,t1,lf[182]);}

/* mp:micro in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2322(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2322,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 389  error");
t3=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[179]);}

/* mp:alloff in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2316(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2316,2,t0,t1);}
C_trace("ChickenBridge.scm: 387  error");
t2=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,t1,lf[176]);}

/* mp:ctrl in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2310(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_2310,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 385  error");
t6=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[173]);}

/* mp:prog in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2304(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_2304,5,t0,t1,t2,t3,t4);}
C_trace("ChickenBridge.scm: 383  error");
t5=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t5))(3,t5,t1,lf[170]);}

/* mp:off in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2298(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_2298,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 381  error");
t6=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[167]);}

/* mp:on in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2292(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_2292,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 379  error");
t6=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[164]);}

/* mp:note in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2286(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
C_word tmp;
C_word t7;
C_word t8;
C_word ab[8],*a=ab;
if(c!=7) C_bad_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr7,(void*)f_2286,7,t0,t1,t2,t3,t4,t5,t6);}
t7=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_1603,a[2]=t1,a[3]=t6,a[4]=t5,a[5]=t4,a[6]=t3,a[7]=t2,tmp=(C_word)a,a+=8,tmp);
C_trace("##sys#gc");
t8=C_retrieve(lf[115]);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,C_SCHEME_FALSE);}

/* k1601 in mp:note in k2282 in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_1603(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_1603,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[7]);
t4=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[6]);
t5=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[5]);
t6=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[4]);
t7=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[3]);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub310,a[2]=lf[161],tmp=(C_word)a,a+=3,tmp);
((C_proc8)C_retrieve_proc(t8))(8,t8,((C_word*)t0)[2],t2,t3,t4,t5,t6,t7);}

/* ferror in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_fcall f_2047(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2047,NULL,3,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2055,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_apply(5,0,t4,C_retrieve(lf[158]),t2,t3);}

/* k2053 in ferror in k2043 in k2040 in k594 in k591 in k588 in k585 */
static void C_ccall f_2055(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 296  error");
t2=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* hush in k594 in k591 in k588 in k585 */
static void C_ccall f_2031(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2031,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2035,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1713,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[115]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k1711 in hush in k594 in k591 in k588 in k585 */
static void C_ccall f_1713(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1713,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub363,a[2]=lf[154],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k2033 in hush in k594 in k591 in k588 in k585 */
static void C_ccall f_2035(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 273  values");
C_values(2,0,((C_word*)t0)[2]);}

/* stop in k594 in k591 in k588 in k585 */
static void C_ccall f_1973(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+9)){
C_save_and_reclaim((void*)tr2r,(void*)f_1973r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_1973r(t0,t1,t2);}}

static void C_ccall f_1973r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a=C_alloc(9);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1977,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 263  scheduler-stop");
f_1696(t3,C_fix(-1));}
else{
t4=C_SCHEME_UNDEFINED;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_set_block_item(t5,0,(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1991,a[2]=t5,a[3]=lf[151],tmp=(C_word)a,a+=4,tmp));
t7=((C_word*)t5)[1];
f_1991(t7,t3,t2);}}

/* do413 in stop in k594 in k591 in k588 in k585 */
static void C_fcall f_1991(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1991,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2001,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_fixnump(t4))){
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 267  scheduler-stop");
f_1696(t3,t5);}
else{
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 268  error");
t6=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t3,lf[150],t5);}}}

/* k1999 in do413 in stop in k594 in k591 in k588 in k585 */
static void C_ccall f_2001(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_1991(t3,((C_word*)t0)[2],t2);}

/* k1975 in stop in k594 in k591 in k588 in k585 */
static void C_ccall f_1977(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 269  values");
C_values(2,0,((C_word*)t0)[2]);}

/* cont in k594 in k591 in k588 in k585 */
static void C_ccall f_1964(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1964,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1968,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1691,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[115]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k1689 in cont in k594 in k591 in k588 in k585 */
static void C_ccall f_1691(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1691,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub353,a[2]=lf[147],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k1966 in cont in k594 in k591 in k588 in k585 */
static void C_ccall f_1968(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 259  values");
C_values(2,0,((C_word*)t0)[2]);}

/* paused? in k594 in k591 in k588 in k585 */
static void C_ccall f_1958(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1958,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1673,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t3=C_retrieve(lf[115]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,C_SCHEME_FALSE);}

/* k1671 in paused? in k594 in k591 in k588 in k585 */
static void C_ccall f_1673(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1673,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub345,a[2]=lf[144],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* pause in k594 in k591 in k588 in k585 */
static void C_ccall f_1949(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1949,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1953,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1682,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[115]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k1680 in pause in k594 in k591 in k588 in k585 */
static void C_ccall f_1682(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1682,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub349,a[2]=lf[141],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k1951 in pause in k594 in k591 in k588 in k585 */
static void C_ccall f_1953(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 252  values");
C_values(2,0,((C_word*)t0)[2]);}

/* time-format in k594 in k591 in k588 in k585 */
static void C_ccall f_1886(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+11)){
C_save_and_reclaim((void*)tr2rv,(void*)f_1886r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_1886r(t0,t1,t2);}}

static void C_ccall f_1886r(C_word t0,C_word t1,C_word t2){
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
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1899,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1638,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t5=C_retrieve(lf[115]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,C_SCHEME_FALSE);}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
t4=(C_word)C_i_eqvp(t3,lf[135]);
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1911,a[2]=t2,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
if(C_truep(t4)){
t6=t5;
f_1911(t6,t4);}
else{
t6=(C_word)C_eqp(t3,C_fix(1));
t7=t5;
f_1911(t7,(C_truep(t6)?t6:(C_word)C_eqp(t3,lf[138])));}}}

/* k1909 in time-format in k594 in k591 in k588 in k585 */
static void C_fcall f_1911(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a;
if(C_truep(t1)){
t2=C_mutate((C_word*)lf[131]+1,*((C_word*)lf[111]+1));
C_trace("ChickenBridge.scm: 241  scheduler-set-time-milliseconds");
f_1643(((C_word*)t0)[4],C_SCHEME_FALSE);}
else{
t2=(C_word)C_eqp(((C_word*)t0)[3],C_fix(1000));
t3=(C_truep(t2)?t2:(C_word)C_eqp(((C_word*)t0)[3],lf[136]));
if(C_truep(t3)){
t4=C_mutate((C_word*)lf[131]+1,*((C_word*)lf[109]+1));
C_trace("ChickenBridge.scm: 245  scheduler-set-time-milliseconds");
f_1643(((C_word*)t0)[4],C_SCHEME_TRUE);}
else{
t4=(C_word)C_i_vector_ref(((C_word*)t0)[2],C_fix(0));
C_trace("ChickenBridge.scm: 248  error");
t5=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,((C_word*)t0)[4],lf[137],t4);}}}

/* k1636 in time-format in k594 in k591 in k588 in k585 */
static void C_ccall f_1638(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1638,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub325,a[2]=lf[134],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k1897 in time-format in k594 in k591 in k588 in k585 */
static void C_ccall f_1899(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_truep(t1)?C_fix(1000):lf[133]));}

/* sprout in k594 in k591 in k588 in k585 */
static void C_ccall f_1718(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+12)){
C_save_and_reclaim((void*)tr3r,(void*)f_1718r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_1718r(t0,t1,t2,t3);}}

static void C_ccall f_1718r(C_word t0,C_word t1,C_word t2,C_word t3){
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
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1720,a[2]=t2,a[3]=lf[127],tmp=(C_word)a,a+=4,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1832,a[2]=t4,a[3]=lf[128],tmp=(C_word)a,a+=4,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1837,a[2]=t5,a[3]=lf[129],tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("def-start373394");
t7=t6;
f_1837(t7,t1);}
else{
t7=(C_word)C_i_car(t3);
t8=(C_word)C_i_cdr(t3);
if(C_truep((C_word)C_i_nullp(t8))){
C_trace("def-id374392");
t9=t5;
f_1832(t9,t1,t7);}
else{
t9=(C_word)C_i_car(t8);
t10=(C_word)C_i_cdr(t8);
if(C_truep((C_word)C_i_nullp(t10))){
C_trace("body371376");
t11=t4;
f_1720(t11,t1,t7,t9);}
else{
C_trace("##sys#error");
t11=*((C_word*)lf[38]+1);
((C_proc4)(void*)(*((C_word*)t11+1)))(4,t11,t1,lf[0],t10);}}}}

/* def-start373 in sprout in k594 in k591 in k588 in k585 */
static void C_fcall f_1837(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1837,NULL,2,t0,t1);}
C_trace("def-id374392");
t2=((C_word*)t0)[2];
f_1832(t2,t1,C_fix(0));}

/* def-id374 in sprout in k594 in k591 in k588 in k585 */
static void C_fcall f_1832(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1832,NULL,3,t0,t1,t2);}
C_trace("body371376");
t3=((C_word*)t0)[2];
f_1720(t3,t1,t2,C_fix(-1));}

/* body371 in sprout in k594 in k591 in k588 in k585 */
static void C_fcall f_1720(C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)trf_1720,NULL,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1722,a[2]=t4,a[3]=lf[124],tmp=(C_word)a,a+=4,tmp);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1750,a[2]=t5,a[3]=lf[125],tmp=(C_word)a,a+=4,tmp);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1780,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t0)[2]))){
t9=C_SCHEME_UNDEFINED;
t10=(*a=C_VECTOR_TYPE|1,a[1]=t9,tmp=(C_word)a,a+=2,tmp);
t11=C_set_block_item(t10,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_1791,a[2]=t6,a[3]=t7,a[4]=t10,a[5]=((C_word*)t0)[2],a[6]=lf[126],tmp=(C_word)a,a+=7,tmp));
t12=((C_word*)t10)[1];
f_1791(t12,t8,((C_word*)t0)[2]);}
else{
t9=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1823,a[2]=((C_word*)t0)[2],a[3]=t8,tmp=(C_word)a,a+=4,tmp);
t10=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1827,a[2]=t7,a[3]=((C_word*)t0)[2],a[4]=t9,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 225  nextstart");
t11=t6;
f_1722(t11,t10);}}

/* k1825 in body371 in sprout in k594 in k591 in k588 in k585 */
static void C_ccall f_1827(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1827,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1831,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 225  nextid");
t3=((C_word*)t0)[2];
f_1750(t3,t2);}

/* k1829 in k1825 in body371 in sprout in k594 in k591 in k588 in k585 */
static void C_ccall f_1831(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 225  scheduler-sprout");
f_1652(((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k1821 in body371 in sprout in k594 in k591 in k588 in k585 */
static void C_ccall f_1823(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
f_1780(2,t2,((C_word*)t0)[2]);}

/* do385 in body371 in sprout in k594 in k591 in k588 in k585 */
static void C_fcall f_1791(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1791,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,((C_word*)t0)[5]);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1801,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1816,a[2]=((C_word*)t0)[3],a[3]=t4,a[4]=t3,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 223  nextstart");
t6=((C_word*)t0)[2];
f_1722(t6,t5);}}

/* k1814 in do385 in body371 in sprout in k594 in k591 in k588 in k585 */
static void C_ccall f_1816(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1816,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1820,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 223  nextid");
t3=((C_word*)t0)[2];
f_1750(t3,t2);}

/* k1818 in k1814 in do385 in body371 in sprout in k594 in k591 in k588 in k585 */
static void C_ccall f_1820(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 223  scheduler-sprout");
f_1652(((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k1799 in do385 in body371 in sprout in k594 in k591 in k588 in k585 */
static void C_ccall f_1801(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_1791(t3,((C_word*)t0)[2],t2);}

/* k1778 in body371 in sprout in k594 in k591 in k588 in k585 */
static void C_ccall f_1780(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 229  values");
C_values(2,0,((C_word*)t0)[2]);}

/* nextid in body371 in sprout in k594 in k591 in k588 in k585 */
static void C_fcall f_1750(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_1750,NULL,2,t0,t1);}
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

/* nextstart in body371 in sprout in k594 in k591 in k588 in k585 */
static void C_fcall f_1722(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_1722,NULL,2,t0,t1);}
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

/* scheduler-stop in k594 in k591 in k588 in k585 */
static void C_fcall f_1696(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1696,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1700,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[115]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k1698 in scheduler-stop in k594 in k591 in k588 in k585 */
static void C_ccall f_1700(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1700,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_fixnum_argumentp(((C_word*)t0)[3]);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub358,a[2]=lf[121],tmp=(C_word)a,a+=3,tmp);
((C_proc4)C_retrieve_proc(t4))(4,t4,((C_word*)t0)[2],t2,t3);}

/* scheduler-sprout in k594 in k591 in k588 in k585 */
static void C_fcall f_1652(C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1652,NULL,4,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_1656,a[2]=t2,a[3]=t1,a[4]=t4,a[5]=t3,tmp=(C_word)a,a+=6,tmp);
C_trace("##sys#gc");
t6=C_retrieve(lf[115]);
((C_proc3)C_retrieve_proc(t6))(3,t6,t5,C_SCHEME_FALSE);}

/* k1654 in scheduler-sprout in k594 in k591 in k588 in k585 */
static void C_ccall f_1656(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1656,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[5]);
t4=(C_word)C_i_foreign_fixnum_argumentp(((C_word*)t0)[4]);
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub338,a[2]=lf[118],tmp=(C_word)a,a+=3,tmp);
((C_proc6)C_retrieve_proc(t5))(6,t5,((C_word*)t0)[3],t2,((C_word*)t0)[2],t3,t4);}

/* scheduler-set-time-milliseconds in k594 in k591 in k588 in k585 */
static void C_fcall f_1643(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1643,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1647,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[115]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k1645 in scheduler-set-time-milliseconds in k594 in k591 in k588 in k585 */
static void C_ccall f_1647(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1647,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub330,a[2]=lf[114],tmp=(C_word)a,a+=3,tmp);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[3],t2,((C_word*)t0)[2]);}

/* current-time-seconds in k594 in k591 in k588 in k585 */
static void C_ccall f_1631(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1631,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub322(t2));}

/* current-time-milliseconds in k594 in k591 in k588 in k585 */
static void C_ccall f_1628(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1628,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub319(t2));}

/* print-error in k594 in k591 in k588 in k585 */
static void C_ccall f_1585(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1585,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1590,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[105]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_1590(2,t4,C_SCHEME_FALSE);}}

/* k1588 in print-error in k594 in k591 in k588 in k585 */
static void C_ccall f_1590(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub300(C_SCHEME_UNDEFINED,t1));}

/* print-message in k594 in k591 in k588 in k585 */
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
t5=C_retrieve(lf[105]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_1576(2,t4,C_SCHEME_FALSE);}}

/* k1574 in print-message in k594 in k591 in k588 in k585 */
static void C_ccall f_1576(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub294(C_SCHEME_UNDEFINED,t1));}

/* ranpink in k594 in k591 in k588 in k585 */
static void C_ccall f_1565(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1565,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub145(t2));}

/* ranbrown in k594 in k591 in k588 in k585 */
static void C_ccall f_1559(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1559,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub148(t2));}

/* rangamma in k594 in k591 in k588 in k585 */
static void C_ccall f_1540(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2rv,(void*)f_1540r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_1540r(t0,t1,t2);}}

static void C_ccall f_1540r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
if(C_truep((C_word)C_vemptyp(t2))){
C_trace("ChickenBridge.scm: 109  tb:rangamma");
f_808(t1,C_fix(1));}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
C_trace("ChickenBridge.scm: 109  tb:rangamma");
f_808(t1,t3);}}

/* ranpoisson in k594 in k591 in k588 in k585 */
static void C_ccall f_1521(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2rv,(void*)f_1521r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_1521r(t0,t1,t2);}}

static void C_ccall f_1521r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
if(C_truep((C_word)C_i_nullp(C_retrieve(lf[96])))){
C_trace("ChickenBridge.scm: 109  tb:ranpoisson");
f_818(t1,C_fix(1));}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
C_trace("ChickenBridge.scm: 109  tb:ranpoisson");
f_818(t1,t3);}}

/* rancauchy in k594 in k591 in k588 in k585 */
static void C_ccall f_1515(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1515,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub138(t2));}

/* rangauss in k594 in k591 in k588 in k585 */
static void C_ccall f_1475(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2r,(void*)f_1475r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_1475r(t0,t1,t2);}}

static void C_ccall f_1475r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 109  tb:rangauss");
f_779(t1,C_fix(1),C_fix(0));}
else{
t3=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 109  tb:rangauss");
f_779(t1,t4,C_fix(0));}
else{
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cdr(t2);
C_trace("ChickenBridge.scm: 109  tb:rangauss");
f_779(t1,t4,t5);}}}

/* ranexp in k594 in k591 in k588 in k585 */
static void C_ccall f_1456(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2rv,(void*)f_1456r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_1456r(t0,t1,t2);}}

static void C_ccall f_1456r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
if(C_truep((C_word)C_vemptyp(t2))){
C_trace("ChickenBridge.scm: 109  tb:ranexp");
f_790(t1,C_fix(1));}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
C_trace("ChickenBridge.scm: 109  tb:ranexp");
f_790(t1,t3);}}

/* ranbeta in k594 in k591 in k588 in k585 */
static void C_ccall f_1412(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2r,(void*)f_1412r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_1412r(t0,t1,t2);}}

static void C_ccall f_1412r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 109  tb:ranbeta");
f_797(t1,lf[86],lf[87]);}
else{
t3=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 109  tb:ranbeta");
f_797(t1,t4,t5);}
else{
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cadr(t2);
C_trace("ChickenBridge.scm: 109  tb:ranbeta");
f_797(t1,t4,t5);}}}

/* ranmiddle in k594 in k591 in k588 in k585 */
static void C_ccall f_1406(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1406,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub111(t2));}

/* ranhigh in k594 in k591 in k588 in k585 */
static void C_ccall f_1400(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1400,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub108(t2));}

/* ranlow in k594 in k591 in k588 in k585 */
static void C_ccall f_1394(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1394,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub105(t2));}

/* pick in k594 in k591 in k588 in k585 */
static void C_ccall f_1388(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2r,(void*)f_1388r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_1388r(t0,t1,t2);}}

static void C_ccall f_1388r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_trace("ChickenBridge.scm: 109  pickl");
t3=*((C_word*)lf[74]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,t2);}

/* pickl in k594 in k591 in k588 in k585 */
static void C_ccall f_1365(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1365,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 109  error");
t3=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t1,lf[75],t2);}
else{
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1382,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
t4=(C_word)C_i_length(t2);
C_trace("ChickenBridge.scm: 109  tb:rani");
f_734(t3,t4);}}

/* k1380 in pickl in k594 in k591 in k588 in k585 */
static void C_ccall f_1382(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_i_list_ref(((C_word*)t0)[2],t1));}

/* odds in k594 in k591 in k588 in k585 */
static void C_ccall f_1307(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+14)){
C_save_and_reclaim((void*)tr3r,(void*)f_1307r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_1307r(t0,t1,t2,t3);}}

static void C_ccall f_1307r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word *a=C_alloc(14);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1324,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 109  tb:ranf");
f_741(t4,lf[70]);}
else{
t4=(C_word)C_i_cdr(t3);
if(C_truep((C_word)C_i_nullp(t4))){
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1343,a[2]=t3,a[3]=t1,a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 109  tb:ranf");
f_741(t5,lf[71]);}
else{
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1359,a[2]=t3,a[3]=t1,a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 109  tb:ranf");
f_741(t5,lf[72]);}}}

/* k1357 in odds in k594 in k591 in k588 in k585 */
static void C_ccall f_1359(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_lessp(t1,((C_word*)t0)[4]);
t3=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_truep(t2)?(C_word)C_i_car(((C_word*)t0)[2]):(C_word)C_i_cadr(((C_word*)t0)[2])));}

/* k1341 in odds in k594 in k591 in k588 in k585 */
static void C_ccall f_1343(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_lessp(t1,((C_word*)t0)[4]);
t3=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_truep(t2)?(C_word)C_i_car(((C_word*)t0)[2]):C_SCHEME_FALSE));}

/* k1322 in odds in k594 in k591 in k588 in k585 */
static void C_ccall f_1324(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_lessp(t1,((C_word*)t0)[3]);
t3=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_truep(t2)?C_SCHEME_TRUE:C_SCHEME_FALSE));}

/* ran in k594 in k591 in k588 in k585 */
static void C_ccall f_1219(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+4)){
C_save_and_reclaim((void*)tr2r,(void*)f_1219r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_1219r(t0,t1,t2);}}

static void C_ccall f_1219r(C_word t0,C_word t1,C_word t2){
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
C_trace("ChickenBridge.scm: 109  tb:ranf");
f_741(t1,lf[67]);}
else{
t3=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_fixnump(t4))){
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 109  tb:rani");
f_734(t1,t5);}
else{
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 109  tb:ranf");
f_741(t1,t5);}}
else{
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1265,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_fixnump(t5))){
t6=(C_word)C_i_cadr(t2);
t7=t4;
f_1265(t7,(C_word)C_fixnump(t6));}
else{
t6=t4;
f_1265(t6,C_SCHEME_FALSE);}}}}

/* k1263 in ran in k594 in k591 in k588 in k585 */
static void C_fcall f_1265(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_1265,NULL,2,t0,t1);}
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

/* ran-set! in k594 in k591 in k588 in k585 */
static void C_ccall f_1213(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1213,3,t0,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub80(C_SCHEME_UNDEFINED,t2));}

/* steps in k594 in k591 in k588 in k585 */
static void C_ccall f_1154(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+12)){
C_save_and_reclaim((void*)tr4rv,(void*)f_1154r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest_vector(a,C_rest_count(0));
f_1154r(t0,t1,t2,t3,t4);}}

static void C_ccall f_1154r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
t9=C_set_block_item(t8,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_1167,a[2]=t5,a[3]=t8,a[4]=t4,a[5]=t2,a[6]=lf[62],tmp=(C_word)a,a+=7,tmp));
t10=((C_word*)t8)[1];
f_1167(t10,t1,C_fix(0),t3,t6,t5);}

/* do216 in steps in k594 in k591 in k588 in k585 */
static void C_fcall f_1167(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
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
C_save_and_reclaim((void*)trf_1167,NULL,6,t0,t1,t2,t3,t4,t5);}
t6=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
if(C_truep((C_word)C_i_lessp(t2,((C_word*)t0)[5]))){
t8=(C_word)C_a_i_list(&a,1,((C_word*)t6)[1]);
t9=(C_word)C_i_set_cdr(((C_word*)t7)[1],t8);
t10=(C_word)C_i_cdr(((C_word*)t7)[1]);
t11=C_set_block_item(t7,0,t10);
t12=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_1203,a[2]=t7,a[3]=t4,a[4]=t1,a[5]=((C_word*)t0)[3],a[6]=t2,a[7]=t6,a[8]=((C_word*)t0)[4],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 109  modulo");
t13=*((C_word*)lf[61]+1);
((C_proc4)C_retrieve_proc(t13))(4,t13,t12,t2,t4);}
else{
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,(C_word)C_i_cdr(((C_word*)t0)[2]));}}

/* k1201 in do216 in steps in k594 in k591 in k588 in k585 */
static void C_ccall f_1203(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1203,2,t0,t1);}
t2=(C_word)C_i_vector_ref(((C_word*)t0)[8],t1);
t3=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[7])[1],t2);
t4=C_mutate(((C_word *)((C_word*)t0)[7])+1,t3);
t5=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[6],C_fix(1));
t6=((C_word*)((C_word*)t0)[5])[1];
f_1167(t6,((C_word*)t0)[4],t5,((C_word*)((C_word*)t0)[7])[1],((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1]);}

/* interp in k594 in k591 in k588 in k585 */
static void C_ccall f_1148(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr3r,(void*)f_1148r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_1148r(t0,t1,t2,t3);}}

static void C_ccall f_1148r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_trace("ChickenBridge.scm: 109  interpl");
t4=*((C_word*)lf[50]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t1,t2,t3);}

/* interpl in k594 in k591 in k588 in k585 */
static void C_ccall f_1053(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+6)){
C_save_and_reclaim((void*)tr4rv,(void*)f_1053r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest_vector(a,C_rest_count(0));
f_1053r(t0,t1,t2,t3,t4);}}

static void C_ccall f_1053r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word *a=C_alloc(6);
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_1057,a[2]=t1,a[3]=t2,a[4]=t3,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("ChickenBridge.scm: 109  error");
t6=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t5,lf[56],t3);}
else{
t6=t5;
f_1057(2,t6,(C_word)C_i_car(t3));}}

/* k1055 in interpl in k594 in k591 in k588 in k585 */
static void C_ccall f_1057(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1057,2,t0,t1);}
t2=t1;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_1060,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=t3,tmp=(C_word)a,a+=7,tmp);
t5=(C_word)C_i_cdr(((C_word*)t0)[4]);
if(C_truep((C_word)C_i_nullp(t5))){
C_trace("ChickenBridge.scm: 109  err");
t6=C_retrieve(lf[54]);
((C_proc4)C_retrieve_proc(t6))(4,t6,t4,lf[55],((C_word*)t0)[4]);}
else{
t6=t4;
f_1060(2,t6,(C_word)C_i_cadr(((C_word*)t0)[4]));}}

/* k1058 in k1055 in interpl in k594 in k591 in k588 in k585 */
static void C_ccall f_1060(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_1060,2,t0,t1);}
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
t13=C_set_block_item(t12,0,(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_1072,a[2]=((C_word*)t0)[4],a[3]=t12,a[4]=t9,a[5]=t7,a[6]=t3,a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[3],a[9]=t5,a[10]=lf[53],tmp=(C_word)a,a+=11,tmp));
t14=((C_word*)t12)[1];
f_1072(t14,((C_word*)t0)[2],t10);}

/* do200 in k1058 in k1055 in interpl in k594 in k591 in k588 in k585 */
static void C_fcall f_1072(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_1072,NULL,3,t0,t1,t2);}
t3=(C_word)C_i_nullp(t2);
t4=(C_truep(t3)?t3:(C_word)C_i_greaterp(((C_word*)((C_word*)t0)[9])[1],((C_word*)t0)[8]));
if(C_truep(t4)){
C_trace("ChickenBridge.scm: 109  tb:rescale");
f_598(t1,((C_word*)t0)[8],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[9])[1],((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[4]);}
else{
t5=C_mutate(((C_word *)((C_word*)t0)[7])+1,((C_word*)((C_word*)t0)[9])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[6])+1,((C_word*)((C_word*)t0)[5])[1]);
t7=(C_word)C_i_car(t2);
t8=C_mutate(((C_word *)((C_word*)t0)[9])+1,t7);
t9=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1094,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t10=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t10))){
C_trace("ChickenBridge.scm: 109  error");
t11=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t11))(4,t11,t9,lf[52],((C_word*)t0)[2]);}
else{
t11=(C_word)C_i_cadr(t2);
t12=C_mutate(((C_word *)((C_word*)t0)[5])+1,t11);
t13=t9;
f_1094(2,t13,t12);}}}

/* k1092 in do200 in k1058 in k1055 in interpl in k594 in k591 in k588 in k585 */
static void C_ccall f_1094(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cddr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_1072(t3,((C_word*)t0)[2],t2);}

/* hertz->keynum in k594 in k591 in k588 in k585 */
static void C_ccall f_1047(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1047,3,t0,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub75(t3,t4));}

/* keynum->pc in k594 in k591 in k588 in k585 */
static void C_ccall f_1041(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1041,3,t0,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub71(C_SCHEME_UNDEFINED,t3));}

/* keynum->hertz in k594 in k591 in k588 in k585 */
static void C_ccall f_1035(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1035,3,t0,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub66(t3,t4));}

/* scaler->cents in k594 in k591 in k588 in k585 */
static void C_ccall f_1029(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1029,3,t0,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub62(C_SCHEME_UNDEFINED,t3));}

/* cents->scaler in k594 in k591 in k588 in k585 */
static void C_ccall f_1023(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1023,3,t0,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_fixnum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub57(t3,t4));}

/* rhythm->seconds in k594 in k591 in k588 in k585 */
static void C_ccall f_963(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+12)){
C_save_and_reclaim((void*)tr3r,(void*)f_963r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_963r(t0,t1,t2,t3);}}

static void C_ccall f_963r(C_word t0,C_word t1,C_word t2,C_word t3){
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
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_965,a[2]=t2,a[3]=lf[33],tmp=(C_word)a,a+=4,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_970,a[2]=t4,a[3]=lf[35],tmp=(C_word)a,a+=4,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_975,a[2]=t5,a[3]=lf[37],tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("def-tempo173181");
t7=t6;
f_975(t7,t1);}
else{
t7=(C_word)C_i_car(t3);
t8=(C_word)C_i_cdr(t3);
if(C_truep((C_word)C_i_nullp(t8))){
C_trace("def-beat174179");
t9=t5;
f_970(t9,t1,t7);}
else{
t9=(C_word)C_i_car(t8);
t10=(C_word)C_i_cdr(t8);
if(C_truep((C_word)C_i_nullp(t10))){
C_trace("body171176");
t11=t4;
f_965(t11,t1,t7,t9);}
else{
C_trace("##sys#error");
t11=*((C_word*)lf[38]+1);
((C_proc4)(void*)(*((C_word*)t11+1)))(4,t11,t1,lf[0],t10);}}}}

/* def-tempo173 in rhythm->seconds in k594 in k591 in k588 in k585 */
static void C_fcall f_975(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_975,NULL,2,t0,t1);}
C_trace("def-beat174179");
t2=((C_word*)t0)[2];
f_970(t2,t1,lf[36]);}

/* def-beat174 in rhythm->seconds in k594 in k591 in k588 in k585 */
static void C_fcall f_970(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_970,NULL,3,t0,t1,t2);}
C_trace("body171176");
t3=((C_word*)t0)[2];
f_965(t3,t1,t2,lf[34]);}

/* body171 in rhythm->seconds in k594 in k591 in k588 in k585 */
static void C_fcall f_965(C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)trf_965,NULL,4,t0,t1,t2,t3);}
t4=((C_word*)t0)[2];
t5=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t6=(C_word)C_i_foreign_flonum_argumentp(t4);
t7=(C_word)C_i_foreign_flonum_argumentp(t2);
t8=(C_word)C_i_foreign_flonum_argumentp(t3);
t9=t1;
((C_proc2)(void*)(*((C_word*)t9+1)))(2,t9,(C_word)stub50(t5,t6,t7,t8));}

/* decimals in k594 in k591 in k588 in k585 */
static void C_ccall f_944(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr3rv,(void*)f_944r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest_vector(a,C_rest_count(0));
f_944r(t0,t1,t2,t3);}}

static void C_ccall f_944r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
if(C_truep((C_word)C_vemptyp(t3))){
C_trace("ChickenBridge.scm: 109  tb:decimals");
f_659(t1,t2,C_fix(3));}
else{
t4=(C_word)C_i_vector_ref(t3,C_fix(0));
C_trace("ChickenBridge.scm: 109  tb:decimals");
f_659(t1,t2,t4);}}

/* quantize in k594 in k591 in k588 in k585 */
static void C_ccall f_938(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_938,4,t0,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_flonum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub42(t4,t5,t6));}

/* int in k594 in k591 in k588 in k585 */
static void C_ccall f_932(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_932,3,t0,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub30(C_SCHEME_UNDEFINED,t3));}

/* discrete in k594 in k591 in k588 in k585 */
static void C_ccall f_850(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,...){
C_word tmp;
C_word t6;
va_list v;
C_word *a,c2=c;
C_save_rest(t5,c2,6);
if(c<6) C_bad_min_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+4)){
C_save_and_reclaim((void*)tr6r,(void*)f_850r,6,t0,t1,t2,t3,t4,t5);}
else{
a=C_alloc((c-6)*3);
t6=C_restore_rest(a,C_rest_count(0));
f_850r(t0,t1,t2,t3,t4,t5,t6);}}

static void C_ccall f_850r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
C_word tmp;
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
C_word *a=C_alloc(4);
if(C_truep((C_word)C_i_pairp(t5))){
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_864,a[2]=t5,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_nullp(t6))){
t8=(C_word)C_i_length(t5);
C_trace("ChickenBridge.scm: 109  tb:discrete");
f_625(t7,t2,t3,t4,C_fix(0),t8,C_fix(1));}
else{
t8=(C_word)C_i_cdr(t6);
if(C_truep((C_word)C_i_nullp(t8))){
t9=(C_word)C_i_car(t6);
C_trace("ChickenBridge.scm: 109  tb:discrete");
f_625(t7,t2,t3,t4,C_fix(0),t9,C_fix(1));}
else{
t9=(C_word)C_i_car(t6);
t10=(C_word)C_i_cadr(t6);
C_trace("ChickenBridge.scm: 109  tb:discrete");
f_625(t7,t2,t3,t4,C_fix(0),t9,t10);}}}
else{
t7=(C_word)C_i_cdr(t6);
if(C_truep((C_word)C_i_nullp(t7))){
t8=(C_word)C_i_car(t6);
C_trace("ChickenBridge.scm: 109  tb:discrete");
f_625(t1,t2,t3,t4,t5,t8,C_fix(1));}
else{
t8=(C_word)C_i_car(t6);
t9=(C_word)C_i_cadr(t6);
C_trace("ChickenBridge.scm: 109  tb:discrete");
f_625(t1,t2,t3,t4,t5,t8,t9);}}}

/* k862 in discrete in k594 in k591 in k588 in k585 */
static void C_ccall f_864(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_i_list_ref(((C_word*)t0)[2],t1));}

/* rescale in k594 in k591 in k588 in k585 */
static void C_ccall f_831(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,...){
C_word tmp;
C_word t7;
va_list v;
C_word *a,c2=c;
C_save_rest(t6,c2,7);
if(c<7) C_bad_min_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr7rv,(void*)f_831r,7,t0,t1,t2,t3,t4,t5,t6);}
else{
a=C_alloc((c-7)*3);
t7=C_restore_rest_vector(a,C_rest_count(0));
f_831r(t0,t1,t2,t3,t4,t5,t6,t7);}}

static void C_ccall f_831r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
C_word tmp;
C_word t8;
C_word t9;
if(C_truep((C_word)C_vemptyp(t7))){
C_trace("ChickenBridge.scm: 109  tb:rescale");
f_598(t1,t2,t3,t4,t5,t6,C_fix(1));}
else{
t8=(C_word)C_i_vector_ref(t7,C_fix(0));
C_trace("ChickenBridge.scm: 109  tb:rescale");
f_598(t1,t2,t3,t4,t5,t6,t8);}}

/* tb:ranpoisson in k594 in k591 in k588 in k585 */
static void C_fcall f_818(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_818,NULL,2,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub142(C_SCHEME_UNDEFINED,t3));}

/* tb:rangamma in k594 in k591 in k588 in k585 */
static void C_fcall f_808(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_808,NULL,2,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub134(t3,t4));}

/* tb:ranbeta in k594 in k591 in k588 in k585 */
static void C_fcall f_797(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_797,NULL,3,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_flonum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub128(t4,t5,t6));}

/* tb:ranexp in k594 in k591 in k588 in k585 */
static void C_fcall f_790(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_790,NULL,2,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub122(t3,t4));}

/* tb:rangauss in k594 in k591 in k588 in k585 */
static void C_fcall f_779(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_779,NULL,3,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_flonum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub116(t4,t5,t6));}

/* tb:ranf in k594 in k591 in k588 in k585 */
static void C_fcall f_741(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_741,NULL,2,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub88(t3,t4));}

/* tb:rani in k594 in k591 in k588 in k585 */
static void C_fcall f_734(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_734,NULL,2,t1,t2);}
t3=(C_word)C_i_foreign_fixnum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub84(C_SCHEME_UNDEFINED,t3));}

/* tb:decimals in k594 in k591 in k588 in k585 */
static void C_fcall f_659(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_659,NULL,3,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_fixnum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub35(t4,t5,t6));}

/* tb:discrete in k594 in k591 in k588 in k585 */
static void C_fcall f_625(C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
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
C_save_and_reclaim((void*)trf_625,NULL,7,t1,t2,t3,t4,t5,t6,t7);}
t8=(C_word)C_i_foreign_flonum_argumentp(t2);
t9=(C_word)C_i_foreign_flonum_argumentp(t3);
t10=(C_word)C_i_foreign_flonum_argumentp(t4);
t11=(C_word)C_i_foreign_fixnum_argumentp(t5);
t12=(C_word)C_i_foreign_fixnum_argumentp(t6);
t13=(C_word)C_i_foreign_flonum_argumentp(t7);
t14=t1;
((C_proc2)(void*)(*((C_word*)t14+1)))(2,t14,(C_word)stub21(C_SCHEME_UNDEFINED,t8,t9,t10,t11,t12,t13));}

/* tb:rescale in k594 in k591 in k588 in k585 */
static void C_fcall f_598(C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
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
C_save_and_reclaim((void*)trf_598,NULL,7,t1,t2,t3,t4,t5,t6,t7);}
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
static C_PTABLE_ENTRY ptable[184] = {
{"toplevelChickenBridge.scm",(void*)C_grace_toplevel},
{"f_587ChickenBridge.scm",(void*)f_587},
{"f_590ChickenBridge.scm",(void*)f_590},
{"f_593ChickenBridge.scm",(void*)f_593},
{"f_596ChickenBridge.scm",(void*)f_596},
{"f_2042ChickenBridge.scm",(void*)f_2042},
{"f_2841ChickenBridge.scm",(void*)f_2841},
{"f_2888ChickenBridge.scm",(void*)f_2888},
{"f_2878ChickenBridge.scm",(void*)f_2878},
{"f_2845ChickenBridge.scm",(void*)f_2845},
{"f_2045ChickenBridge.scm",(void*)f_2045},
{"f_2835ChickenBridge.scm",(void*)f_2835},
{"f_2061ChickenBridge.scm",(void*)f_2061},
{"f_2274ChickenBridge.scm",(void*)f_2274},
{"f_2064ChickenBridge.scm",(void*)f_2064},
{"f_2067ChickenBridge.scm",(void*)f_2067},
{"f_2079ChickenBridge.scm",(void*)f_2079},
{"f_2127ChickenBridge.scm",(void*)f_2127},
{"f_2143ChickenBridge.scm",(void*)f_2143},
{"f_2153ChickenBridge.scm",(void*)f_2153},
{"f_2252ChickenBridge.scm",(void*)f_2252},
{"f_2248ChickenBridge.scm",(void*)f_2248},
{"f_2197ChickenBridge.scm",(void*)f_2197},
{"f_2203ChickenBridge.scm",(void*)f_2203},
{"f_2137ChickenBridge.scm",(void*)f_2137},
{"f_2082ChickenBridge.scm",(void*)f_2082},
{"f_2087ChickenBridge.scm",(void*)f_2087},
{"f_2100ChickenBridge.scm",(void*)f_2100},
{"f_2284ChickenBridge.scm",(void*)f_2284},
{"f_2335ChickenBridge.scm",(void*)f_2335},
{"f_2338ChickenBridge.scm",(void*)f_2338},
{"f_2341ChickenBridge.scm",(void*)f_2341},
{"f_2344ChickenBridge.scm",(void*)f_2344},
{"f_2347ChickenBridge.scm",(void*)f_2347},
{"f_2350ChickenBridge.scm",(void*)f_2350},
{"f_2353ChickenBridge.scm",(void*)f_2353},
{"f_2356ChickenBridge.scm",(void*)f_2356},
{"f_2829ChickenBridge.scm",(void*)f_2829},
{"f_2374ChickenBridge.scm",(void*)f_2374},
{"f_2377ChickenBridge.scm",(void*)f_2377},
{"f_2655ChickenBridge.scm",(void*)f_2655},
{"f_2763ChickenBridge.scm",(void*)f_2763},
{"f_2675ChickenBridge.scm",(void*)f_2675},
{"f_2684ChickenBridge.scm",(void*)f_2684},
{"f_2688ChickenBridge.scm",(void*)f_2688},
{"f_2692ChickenBridge.scm",(void*)f_2692},
{"f_2700ChickenBridge.scm",(void*)f_2700},
{"f_2696ChickenBridge.scm",(void*)f_2696},
{"f_2665ChickenBridge.scm",(void*)f_2665},
{"f_2380ChickenBridge.scm",(void*)f_2380},
{"f_2383ChickenBridge.scm",(void*)f_2383},
{"f_2386ChickenBridge.scm",(void*)f_2386},
{"f_2389ChickenBridge.scm",(void*)f_2389},
{"f_2392ChickenBridge.scm",(void*)f_2392},
{"f_2649ChickenBridge.scm",(void*)f_2649},
{"f_2548ChickenBridge.scm",(void*)f_2548},
{"f_2555ChickenBridge.scm",(void*)f_2555},
{"f_2557ChickenBridge.scm",(void*)f_2557},
{"f_2629ChickenBridge.scm",(void*)f_2629},
{"f_2581ChickenBridge.scm",(void*)f_2581},
{"f_2584ChickenBridge.scm",(void*)f_2584},
{"f_2605ChickenBridge.scm",(void*)f_2605},
{"f_2571ChickenBridge.scm",(void*)f_2571},
{"f_2395ChickenBridge.scm",(void*)f_2395},
{"f_2537ChickenBridge.scm",(void*)f_2537},
{"f_2525ChickenBridge.scm",(void*)f_2525},
{"f_2521ChickenBridge.scm",(void*)f_2521},
{"f_2402ChickenBridge.scm",(void*)f_2402},
{"f_2359ChickenBridge.scm",(void*)f_2359},
{"f_2827ChickenBridge.scm",(void*)f_2827},
{"f_2817ChickenBridge.scm",(void*)f_2817},
{"f_2821ChickenBridge.scm",(void*)f_2821},
{"f_2328ChickenBridge.scm",(void*)f_2328},
{"f_2322ChickenBridge.scm",(void*)f_2322},
{"f_2316ChickenBridge.scm",(void*)f_2316},
{"f_2310ChickenBridge.scm",(void*)f_2310},
{"f_2304ChickenBridge.scm",(void*)f_2304},
{"f_2298ChickenBridge.scm",(void*)f_2298},
{"f_2292ChickenBridge.scm",(void*)f_2292},
{"f_2286ChickenBridge.scm",(void*)f_2286},
{"f_1603ChickenBridge.scm",(void*)f_1603},
{"f_2047ChickenBridge.scm",(void*)f_2047},
{"f_2055ChickenBridge.scm",(void*)f_2055},
{"f_2031ChickenBridge.scm",(void*)f_2031},
{"f_1713ChickenBridge.scm",(void*)f_1713},
{"f_2035ChickenBridge.scm",(void*)f_2035},
{"f_1973ChickenBridge.scm",(void*)f_1973},
{"f_1991ChickenBridge.scm",(void*)f_1991},
{"f_2001ChickenBridge.scm",(void*)f_2001},
{"f_1977ChickenBridge.scm",(void*)f_1977},
{"f_1964ChickenBridge.scm",(void*)f_1964},
{"f_1691ChickenBridge.scm",(void*)f_1691},
{"f_1968ChickenBridge.scm",(void*)f_1968},
{"f_1958ChickenBridge.scm",(void*)f_1958},
{"f_1673ChickenBridge.scm",(void*)f_1673},
{"f_1949ChickenBridge.scm",(void*)f_1949},
{"f_1682ChickenBridge.scm",(void*)f_1682},
{"f_1953ChickenBridge.scm",(void*)f_1953},
{"f_1886ChickenBridge.scm",(void*)f_1886},
{"f_1911ChickenBridge.scm",(void*)f_1911},
{"f_1638ChickenBridge.scm",(void*)f_1638},
{"f_1899ChickenBridge.scm",(void*)f_1899},
{"f_1718ChickenBridge.scm",(void*)f_1718},
{"f_1837ChickenBridge.scm",(void*)f_1837},
{"f_1832ChickenBridge.scm",(void*)f_1832},
{"f_1720ChickenBridge.scm",(void*)f_1720},
{"f_1827ChickenBridge.scm",(void*)f_1827},
{"f_1831ChickenBridge.scm",(void*)f_1831},
{"f_1823ChickenBridge.scm",(void*)f_1823},
{"f_1791ChickenBridge.scm",(void*)f_1791},
{"f_1816ChickenBridge.scm",(void*)f_1816},
{"f_1820ChickenBridge.scm",(void*)f_1820},
{"f_1801ChickenBridge.scm",(void*)f_1801},
{"f_1780ChickenBridge.scm",(void*)f_1780},
{"f_1750ChickenBridge.scm",(void*)f_1750},
{"f_1722ChickenBridge.scm",(void*)f_1722},
{"f_1696ChickenBridge.scm",(void*)f_1696},
{"f_1700ChickenBridge.scm",(void*)f_1700},
{"f_1652ChickenBridge.scm",(void*)f_1652},
{"f_1656ChickenBridge.scm",(void*)f_1656},
{"f_1643ChickenBridge.scm",(void*)f_1643},
{"f_1647ChickenBridge.scm",(void*)f_1647},
{"f_1631ChickenBridge.scm",(void*)f_1631},
{"f_1628ChickenBridge.scm",(void*)f_1628},
{"f_1585ChickenBridge.scm",(void*)f_1585},
{"f_1590ChickenBridge.scm",(void*)f_1590},
{"f_1571ChickenBridge.scm",(void*)f_1571},
{"f_1576ChickenBridge.scm",(void*)f_1576},
{"f_1565ChickenBridge.scm",(void*)f_1565},
{"f_1559ChickenBridge.scm",(void*)f_1559},
{"f_1540ChickenBridge.scm",(void*)f_1540},
{"f_1521ChickenBridge.scm",(void*)f_1521},
{"f_1515ChickenBridge.scm",(void*)f_1515},
{"f_1475ChickenBridge.scm",(void*)f_1475},
{"f_1456ChickenBridge.scm",(void*)f_1456},
{"f_1412ChickenBridge.scm",(void*)f_1412},
{"f_1406ChickenBridge.scm",(void*)f_1406},
{"f_1400ChickenBridge.scm",(void*)f_1400},
{"f_1394ChickenBridge.scm",(void*)f_1394},
{"f_1388ChickenBridge.scm",(void*)f_1388},
{"f_1365ChickenBridge.scm",(void*)f_1365},
{"f_1382ChickenBridge.scm",(void*)f_1382},
{"f_1307ChickenBridge.scm",(void*)f_1307},
{"f_1359ChickenBridge.scm",(void*)f_1359},
{"f_1343ChickenBridge.scm",(void*)f_1343},
{"f_1324ChickenBridge.scm",(void*)f_1324},
{"f_1219ChickenBridge.scm",(void*)f_1219},
{"f_1265ChickenBridge.scm",(void*)f_1265},
{"f_1213ChickenBridge.scm",(void*)f_1213},
{"f_1154ChickenBridge.scm",(void*)f_1154},
{"f_1167ChickenBridge.scm",(void*)f_1167},
{"f_1203ChickenBridge.scm",(void*)f_1203},
{"f_1148ChickenBridge.scm",(void*)f_1148},
{"f_1053ChickenBridge.scm",(void*)f_1053},
{"f_1057ChickenBridge.scm",(void*)f_1057},
{"f_1060ChickenBridge.scm",(void*)f_1060},
{"f_1072ChickenBridge.scm",(void*)f_1072},
{"f_1094ChickenBridge.scm",(void*)f_1094},
{"f_1047ChickenBridge.scm",(void*)f_1047},
{"f_1041ChickenBridge.scm",(void*)f_1041},
{"f_1035ChickenBridge.scm",(void*)f_1035},
{"f_1029ChickenBridge.scm",(void*)f_1029},
{"f_1023ChickenBridge.scm",(void*)f_1023},
{"f_963ChickenBridge.scm",(void*)f_963},
{"f_975ChickenBridge.scm",(void*)f_975},
{"f_970ChickenBridge.scm",(void*)f_970},
{"f_965ChickenBridge.scm",(void*)f_965},
{"f_944ChickenBridge.scm",(void*)f_944},
{"f_938ChickenBridge.scm",(void*)f_938},
{"f_932ChickenBridge.scm",(void*)f_932},
{"f_850ChickenBridge.scm",(void*)f_850},
{"f_864ChickenBridge.scm",(void*)f_864},
{"f_831ChickenBridge.scm",(void*)f_831},
{"f_818ChickenBridge.scm",(void*)f_818},
{"f_808ChickenBridge.scm",(void*)f_808},
{"f_797ChickenBridge.scm",(void*)f_797},
{"f_790ChickenBridge.scm",(void*)f_790},
{"f_779ChickenBridge.scm",(void*)f_779},
{"f_741ChickenBridge.scm",(void*)f_741},
{"f_734ChickenBridge.scm",(void*)f_734},
{"f_659ChickenBridge.scm",(void*)f_659},
{"f_625ChickenBridge.scm",(void*)f_625},
{"f_598ChickenBridge.scm",(void*)f_598},
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
