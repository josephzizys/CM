/* Generated from ChickenBridge.scm by the CHICKEN compiler
   http://www.call-with-current-continuation.org
   2007-12-20 10:02
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

static C_TLS C_word lf[260];


/* from k1741 in hush in k624 in k621 in k618 in k615 */
C_noret_decl(stub363)
static void C_ccall stub363(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub363(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_hush();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1735 */
C_noret_decl(stub358)
static void C_ccall stub358(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0) C_noret;
static void C_ccall stub358(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_unfix(C_a0);
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_stop(t0);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1719 in cont in k624 in k621 in k618 in k615 */
C_noret_decl(stub353)
static void C_ccall stub353(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub353(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_cont();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1710 in pause in k624 in k621 in k618 in k615 */
C_noret_decl(stub349)
static void C_ccall stub349(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub349(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_pause();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1701 in paused? in k624 in k621 in k618 in k615 */
C_noret_decl(stub345)
static void C_ccall stub345(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub345(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
C_r=C_mk_bool(scheduler_is_paused());
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1695 */
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

/* from k1675 in scheduler-set-time-milliseconds in k624 in k621 in k618 in k615 */
C_noret_decl(stub330)
static void C_ccall stub330(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0) C_noret;
static void C_ccall stub330(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_truep(C_a0);
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_set_time_milliseconds(t0);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k1666 in time-format in k624 in k621 in k618 in k615 */
C_noret_decl(stub325)
static void C_ccall stub325(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub325(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
C_r=C_mk_bool(scheduler_is_time_milliseconds());
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from current-time-seconds in k624 in k621 in k618 in k615 */
#define return(x) C_cblock C_r = (C_flonum(&C_a,(x))); goto C_ret; C_cblockend
static C_word C_fcall stub322(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub322(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
 C_return( (Time::getMillisecondCounterHiRes() / 1000.0) );
C_ret:
#undef return

return C_r;}

/* from current-time-milliseconds in k624 in k621 in k618 in k615 */
#define return(x) C_cblock C_r = (C_flonum(&C_a,(x))); goto C_ret; C_cblockend
static C_word C_fcall stub319(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub319(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
 C_return( Time::getMillisecondCounterHiRes());
C_ret:
#undef return

return C_r;}

/* from k1654 */
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

/* from k1618 in print-error in k624 in k621 in k618 in k615 */
static C_word C_fcall stub300(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub300(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_error(t0);
return C_r;}

/* from k1604 in print-message in k624 in k621 in k618 in k615 */
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

/* from k851 */
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

/* from k841 */
static C_word C_fcall stub134(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub134(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::rangamma(t0));
return C_r;}

/* from k834 */
static C_word C_fcall stub128(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub128(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
C_r=C_flonum(&C_a,Toolbox::ranbeta(t0,t1));
return C_r;}

/* from k823 */
static C_word C_fcall stub122(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub122(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::ranexp(t0));
return C_r;}

/* from k816 */
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

/* from k796 */
static C_word C_fcall stub100(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub100(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
C_r=C_flonum(&C_a,Toolbox::ran(t0,t1));
return C_r;}

/* from k785 */
static C_word C_fcall stub94(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub94(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_unfix(C_a0);
int t1=(int )C_unfix(C_a1);
C_r=C_fix((C_word)Toolbox::ran(t0,t1));
return C_r;}

/* from k774 */
static C_word C_fcall stub88(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub88(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::ran(t0));
return C_r;}

/* from k767 */
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

/* from k757 */
static C_word C_fcall stub75(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub75(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::hertz_to_keynum(t0));
return C_r;}

/* from k750 */
static C_word C_fcall stub71(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub71(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_fix((C_word)Toolbox::keynum_to_pc(t0));
return C_r;}

/* from k743 */
static C_word C_fcall stub66(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub66(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::keynum_to_hertz(t0));
return C_r;}

/* from k736 */
static C_word C_fcall stub62(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub62(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_fix((C_word)Toolbox::scaler_to_cents(t0));
return C_r;}

/* from k729 */
static C_word C_fcall stub57(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub57(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_unfix(C_a0);
C_r=C_flonum(&C_a,Toolbox::cents_to_scaler(t0));
return C_r;}

/* from k722 */
static C_word C_fcall stub50(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2) C_regparm;
C_regparm static C_word C_fcall stub50(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
float t2=(float )C_c_double(C_a2);
C_r=C_flonum(&C_a,Toolbox::rhythm_to_seconds(t0,t1,t2));
return C_r;}

/* from k707 */
static C_word C_fcall stub42(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub42(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
C_r=C_flonum(&C_a,Toolbox::quantize(t0,t1));
return C_r;}

/* from k696 */
static C_word C_fcall stub35(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub35(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
int t1=(int )C_unfix(C_a1);
C_r=C_flonum(&C_a,Toolbox::decimals(t0,t1));
return C_r;}

/* from k685 */
static C_word C_fcall stub30(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub30(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_fix((C_word)Toolbox::float_to_fixnum(t0));
return C_r;}

/* from k678 */
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

/* from k651 */
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
C_noret_decl(f_617)
static void C_ccall f_617(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_620)
static void C_ccall f_620(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_623)
static void C_ccall f_623(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_626)
static void C_ccall f_626(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2072)
static void C_ccall f_2072(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3106)
static void C_ccall f_3106(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_3153)
static void C_ccall f_3153(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3143)
static void C_ccall f_3143(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3110)
static void C_ccall f_3110(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2075)
static void C_ccall f_2075(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3100)
static void C_ccall f_3100(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_3100)
static void C_ccall f_3100r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_2091)
static void C_ccall f_2091(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2304)
static void C_ccall f_2304(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2094)
static void C_ccall f_2094(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2097)
static void C_ccall f_2097(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2109)
static void C_ccall f_2109(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2157)
static void C_fcall f_2157(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_2173)
static void C_ccall f_2173(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2183)
static void C_ccall f_2183(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2282)
static void C_ccall f_2282(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2278)
static void C_ccall f_2278(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2227)
static void C_ccall f_2227(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2233)
static void C_ccall f_2233(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2167)
static void C_fcall f_2167(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2112)
static void C_ccall f_2112(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2117)
static void C_fcall f_2117(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2130)
static void C_fcall f_2130(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2314)
static void C_ccall f_2314(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2365)
static void C_ccall f_2365(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2368)
static void C_ccall f_2368(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2371)
static void C_ccall f_2371(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2374)
static void C_ccall f_2374(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2377)
static void C_ccall f_2377(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2380)
static void C_ccall f_2380(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2383)
static void C_ccall f_2383(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2386)
static void C_ccall f_2386(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3094)
static void C_ccall f_3094(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_3094)
static void C_ccall f_3094r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_2404)
static void C_ccall f_2404(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2407)
static void C_ccall f_2407(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2685)
static void C_fcall f_2685(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2793)
static void C_ccall f_2793(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2705)
static void C_fcall f_2705(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2714)
static void C_fcall f_2714(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2718)
static void C_ccall f_2718(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2722)
static void C_ccall f_2722(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2730)
static void C_fcall f_2730(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2726)
static void C_ccall f_2726(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2695)
static void C_ccall f_2695(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2410)
static void C_ccall f_2410(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2413)
static void C_ccall f_2413(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2416)
static void C_ccall f_2416(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2419)
static void C_ccall f_2419(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2422)
static void C_ccall f_2422(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2679)
static void C_ccall f_2679(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2578)
static void C_fcall f_2578(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2585)
static void C_ccall f_2585(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2587)
static void C_fcall f_2587(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2659)
static void C_ccall f_2659(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2611)
static void C_fcall f_2611(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2614)
static void C_ccall f_2614(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2635)
static void C_ccall f_2635(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2601)
static void C_ccall f_2601(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2425)
static void C_ccall f_2425(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2567)
static void C_ccall f_2567(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2555)
static void C_ccall f_2555(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2551)
static void C_ccall f_2551(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2432)
static void C_fcall f_2432(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2389)
static void C_ccall f_2389(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3092)
static void C_ccall f_3092(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2358)
static void C_ccall f_2358(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_2352)
static void C_ccall f_2352(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2346)
static void C_ccall f_2346(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2340)
static void C_ccall f_2340(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_2334)
static void C_ccall f_2334(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_2328)
static void C_ccall f_2328(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_2322)
static void C_ccall f_2322(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_2316)
static void C_ccall f_2316(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_1633)
static void C_ccall f_1633(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2077)
static void C_fcall f_2077(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2085)
static void C_ccall f_2085(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2061)
static void C_ccall f_2061(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1743)
static void C_ccall f_1743(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2065)
static void C_ccall f_2065(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2003)
static void C_ccall f_2003(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_2003)
static void C_ccall f_2003r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_2021)
static void C_fcall f_2021(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2031)
static void C_ccall f_2031(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2007)
static void C_ccall f_2007(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1994)
static void C_ccall f_1994(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1721)
static void C_ccall f_1721(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1998)
static void C_ccall f_1998(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1988)
static void C_ccall f_1988(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1703)
static void C_ccall f_1703(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1979)
static void C_ccall f_1979(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1712)
static void C_ccall f_1712(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1983)
static void C_ccall f_1983(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1916)
static void C_ccall f_1916(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1916)
static void C_ccall f_1916r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1941)
static void C_fcall f_1941(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1668)
static void C_ccall f_1668(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1929)
static void C_ccall f_1929(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1748)
static void C_ccall f_1748(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_1748)
static void C_ccall f_1748r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_1867)
static void C_fcall f_1867(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1862)
static void C_fcall f_1862(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1750)
static void C_fcall f_1750(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_1857)
static void C_ccall f_1857(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1861)
static void C_ccall f_1861(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1853)
static void C_ccall f_1853(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1821)
static void C_fcall f_1821(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1846)
static void C_ccall f_1846(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1850)
static void C_ccall f_1850(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1831)
static void C_ccall f_1831(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1810)
static void C_ccall f_1810(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1780)
static void C_fcall f_1780(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1752)
static void C_fcall f_1752(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1726)
static void C_fcall f_1726(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1730)
static void C_ccall f_1730(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1682)
static void C_fcall f_1682(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_1686)
static void C_ccall f_1686(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1673)
static void C_fcall f_1673(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1677)
static void C_ccall f_1677(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1661)
static void C_ccall f_1661(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1658)
static void C_ccall f_1658(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1615)
static void C_ccall f_1615(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1620)
static void C_ccall f_1620(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1601)
static void C_ccall f_1601(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1606)
static void C_ccall f_1606(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1595)
static void C_ccall f_1595(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1589)
static void C_ccall f_1589(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1570)
static void C_ccall f_1570(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1570)
static void C_ccall f_1570r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1551)
static void C_ccall f_1551(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1551)
static void C_ccall f_1551r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1545)
static void C_ccall f_1545(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1505)
static void C_ccall f_1505(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1505)
static void C_ccall f_1505r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1486)
static void C_ccall f_1486(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1486)
static void C_ccall f_1486r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1442)
static void C_ccall f_1442(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1442)
static void C_ccall f_1442r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1436)
static void C_ccall f_1436(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1430)
static void C_ccall f_1430(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1424)
static void C_ccall f_1424(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1418)
static void C_ccall f_1418(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1418)
static void C_ccall f_1418r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1395)
static void C_ccall f_1395(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1412)
static void C_ccall f_1412(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1337)
static void C_ccall f_1337(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_1337)
static void C_ccall f_1337r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_1389)
static void C_ccall f_1389(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1373)
static void C_ccall f_1373(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1354)
static void C_ccall f_1354(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1249)
static void C_ccall f_1249(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_1249)
static void C_ccall f_1249r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_1295)
static void C_fcall f_1295(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1243)
static void C_ccall f_1243(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1184)
static void C_ccall f_1184(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_1184)
static void C_ccall f_1184r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_1197)
static void C_fcall f_1197(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_1233)
static void C_ccall f_1233(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1178)
static void C_ccall f_1178(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_1178)
static void C_ccall f_1178r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_1083)
static void C_ccall f_1083(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_1083)
static void C_ccall f_1083r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_1087)
static void C_ccall f_1087(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1090)
static void C_ccall f_1090(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1102)
static void C_fcall f_1102(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1124)
static void C_ccall f_1124(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1077)
static void C_ccall f_1077(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1071)
static void C_ccall f_1071(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1065)
static void C_ccall f_1065(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1059)
static void C_ccall f_1059(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1053)
static void C_ccall f_1053(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_993)
static void C_ccall f_993(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_993)
static void C_ccall f_993r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_1005)
static void C_fcall f_1005(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1000)
static void C_fcall f_1000(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_995)
static void C_fcall f_995(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_974)
static void C_ccall f_974(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_974)
static void C_ccall f_974r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_968)
static void C_ccall f_968(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_962)
static void C_ccall f_962(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_880)
static void C_ccall f_880(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,...) C_noret;
C_noret_decl(f_880)
static void C_ccall f_880r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t7) C_noret;
C_noret_decl(f_894)
static void C_ccall f_894(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_861)
static void C_ccall f_861(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,...) C_noret;
C_noret_decl(f_861)
static void C_ccall f_861r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t8) C_noret;
C_noret_decl(f_848)
static void C_fcall f_848(C_word t0,C_word t1) C_noret;
C_noret_decl(f_838)
static void C_fcall f_838(C_word t0,C_word t1) C_noret;
C_noret_decl(f_827)
static void C_fcall f_827(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_820)
static void C_fcall f_820(C_word t0,C_word t1) C_noret;
C_noret_decl(f_809)
static void C_fcall f_809(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_771)
static void C_fcall f_771(C_word t0,C_word t1) C_noret;
C_noret_decl(f_764)
static void C_fcall f_764(C_word t0,C_word t1) C_noret;
C_noret_decl(f_689)
static void C_fcall f_689(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_655)
static void C_fcall f_655(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_628)
static void C_fcall f_628(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;

C_noret_decl(trf_2157)
static void C_fcall trf_2157(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2157(void *dummy){
C_word t4=C_pick(0);
C_word t3=C_pick(1);
C_word t2=C_pick(2);
C_word t1=C_pick(3);
C_word t0=C_pick(4);
C_adjust_stack(-5);
f_2157(t0,t1,t2,t3,t4);}

C_noret_decl(trf_2167)
static void C_fcall trf_2167(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2167(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2167(t0,t1);}

C_noret_decl(trf_2117)
static void C_fcall trf_2117(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2117(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_2117(t0,t1,t2);}

C_noret_decl(trf_2130)
static void C_fcall trf_2130(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2130(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2130(t0,t1);}

C_noret_decl(trf_2685)
static void C_fcall trf_2685(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2685(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_2685(t0,t1,t2);}

C_noret_decl(trf_2705)
static void C_fcall trf_2705(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2705(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2705(t0,t1);}

C_noret_decl(trf_2714)
static void C_fcall trf_2714(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2714(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2714(t0,t1);}

C_noret_decl(trf_2730)
static void C_fcall trf_2730(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2730(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2730(t0,t1);}

C_noret_decl(trf_2578)
static void C_fcall trf_2578(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2578(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2578(t0,t1);}

C_noret_decl(trf_2587)
static void C_fcall trf_2587(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2587(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_2587(t0,t1,t2);}

C_noret_decl(trf_2611)
static void C_fcall trf_2611(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2611(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2611(t0,t1);}

C_noret_decl(trf_2432)
static void C_fcall trf_2432(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2432(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2432(t0,t1);}

C_noret_decl(trf_2077)
static void C_fcall trf_2077(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2077(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_2077(t0,t1,t2);}

C_noret_decl(trf_2021)
static void C_fcall trf_2021(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2021(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_2021(t0,t1,t2);}

C_noret_decl(trf_1941)
static void C_fcall trf_1941(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1941(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1941(t0,t1);}

C_noret_decl(trf_1867)
static void C_fcall trf_1867(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1867(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1867(t0,t1);}

C_noret_decl(trf_1862)
static void C_fcall trf_1862(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1862(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1862(t0,t1,t2);}

C_noret_decl(trf_1750)
static void C_fcall trf_1750(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1750(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_1750(t0,t1,t2,t3);}

C_noret_decl(trf_1821)
static void C_fcall trf_1821(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1821(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1821(t0,t1,t2);}

C_noret_decl(trf_1780)
static void C_fcall trf_1780(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1780(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1780(t0,t1);}

C_noret_decl(trf_1752)
static void C_fcall trf_1752(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1752(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1752(t0,t1);}

C_noret_decl(trf_1726)
static void C_fcall trf_1726(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1726(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1726(t0,t1);}

C_noret_decl(trf_1682)
static void C_fcall trf_1682(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1682(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_1682(t0,t1,t2,t3);}

C_noret_decl(trf_1673)
static void C_fcall trf_1673(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1673(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1673(t0,t1);}

C_noret_decl(trf_1295)
static void C_fcall trf_1295(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1295(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1295(t0,t1);}

C_noret_decl(trf_1197)
static void C_fcall trf_1197(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1197(void *dummy){
C_word t5=C_pick(0);
C_word t4=C_pick(1);
C_word t3=C_pick(2);
C_word t2=C_pick(3);
C_word t1=C_pick(4);
C_word t0=C_pick(5);
C_adjust_stack(-6);
f_1197(t0,t1,t2,t3,t4,t5);}

C_noret_decl(trf_1102)
static void C_fcall trf_1102(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1102(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1102(t0,t1,t2);}

C_noret_decl(trf_1005)
static void C_fcall trf_1005(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1005(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1005(t0,t1);}

C_noret_decl(trf_1000)
static void C_fcall trf_1000(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1000(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1000(t0,t1,t2);}

C_noret_decl(trf_995)
static void C_fcall trf_995(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_995(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_995(t0,t1,t2,t3);}

C_noret_decl(trf_848)
static void C_fcall trf_848(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_848(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_848(t0,t1);}

C_noret_decl(trf_838)
static void C_fcall trf_838(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_838(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_838(t0,t1);}

C_noret_decl(trf_827)
static void C_fcall trf_827(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_827(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_827(t0,t1,t2);}

C_noret_decl(trf_820)
static void C_fcall trf_820(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_820(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_820(t0,t1);}

C_noret_decl(trf_809)
static void C_fcall trf_809(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_809(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_809(t0,t1,t2);}

C_noret_decl(trf_771)
static void C_fcall trf_771(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_771(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_771(t0,t1);}

C_noret_decl(trf_764)
static void C_fcall trf_764(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_764(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_764(t0,t1);}

C_noret_decl(trf_689)
static void C_fcall trf_689(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_689(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_689(t0,t1,t2);}

C_noret_decl(trf_655)
static void C_fcall trf_655(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_655(void *dummy){
C_word t6=C_pick(0);
C_word t5=C_pick(1);
C_word t4=C_pick(2);
C_word t3=C_pick(3);
C_word t2=C_pick(4);
C_word t1=C_pick(5);
C_word t0=C_pick(6);
C_adjust_stack(-7);
f_655(t0,t1,t2,t3,t4,t5,t6);}

C_noret_decl(trf_628)
static void C_fcall trf_628(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_628(void *dummy){
C_word t6=C_pick(0);
C_word t5=C_pick(1);
C_word t4=C_pick(2);
C_word t3=C_pick(3);
C_word t2=C_pick(4);
C_word t1=C_pick(5);
C_word t0=C_pick(6);
C_adjust_stack(-7);
f_628(t0,t1,t2,t3,t4,t5,t6);}

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
if(!C_demand_2(1578)){
C_save(t1);
C_rereclaim2(1578*sizeof(C_word), 1);
t1=C_restore;}
a=C_alloc(3);
C_initialize_lf(lf,260);
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
lf[184]=C_h_intern(&lf[184],14,"return-to-host");
lf[185]=C_h_intern(&lf[185],4,"else");
lf[186]=C_h_intern(&lf[186],4,"cond");
lf[187]=C_h_intern(&lf[187],6,"lambda");
lf[188]=C_h_intern(&lf[188],7,"elapsed");
lf[189]=C_h_intern(&lf[189],1,"x");
lf[190]=C_h_intern(&lf[190],4,"set!");
lf[191]=C_h_intern(&lf[191],4,"wait");
lf[192]=C_h_intern(&lf[192],4,"let*");
lf[193]=C_h_intern(&lf[193],5,"quote");
lf[194]=C_h_intern(&lf[194],3,"exn");
lf[195]=C_h_intern(&lf[195],7,"message");
lf[196]=C_h_intern(&lf[196],27,"condition-property-accessor");
lf[197]=C_static_string(C_heaptop,48,">>> Error: ~A~%    Aborting process at time ~S~%");
lf[198]=C_h_intern(&lf[198],22,"with-exception-handler");
lf[199]=C_h_intern(&lf[199],30,"call-with-current-continuation");
lf[200]=C_h_intern(&lf[200],10,"\003sysappend");
lf[201]=C_h_intern(&lf[201],6,"safety");
lf[202]=C_h_intern(&lf[202],4,"cdar");
lf[203]=C_static_string(C_heaptop,19,"unknown declaration");
lf[204]=C_h_intern(&lf[204],4,"caar");
lf[205]=C_static_string(C_heaptop,31,"declaration not list (decl val)");
lf[206]=C_static_lambda_info(C_heaptop,15,"(do513 decl515)");
lf[207]=C_h_intern(&lf[207],7,"declare");
lf[208]=C_h_intern(&lf[208],6,"gensym");
lf[209]=C_h_intern(&lf[209],6,"append");
lf[210]=C_h_intern(&lf[210],5,"\000null");
lf[211]=C_static_string(C_heaptop,41,"binding clause not list (var init [step])");
lf[212]=C_static_lambda_info(C_heaptop,15,"(do497 tail499)");
lf[213]=C_static_string(C_heaptop,36,"go stopping clause missing test form");
lf[214]=C_static_string(C_heaptop,29,"go stopping clause not a list");
lf[215]=C_static_string(C_heaptop,22,"go bindings not a list");
lf[216]=C_static_lambda_info(C_heaptop,42,"(a3093 bindings488 terminate489 . body490)");
lf[217]=C_h_intern(&lf[217],18,"\003sysregister-macro");
lf[218]=C_h_intern(&lf[218],2,"go");
lf[219]=C_h_intern(&lf[219],15,"hash-table-set!");
lf[220]=C_static_string(C_heaptop,9,"mp:inhook");
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
lf[221]=C_h_list(4,C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(4);
lf[222]=C_static_string(C_heaptop,8,"mp:micro");
tmp=C_intern(C_heaptop,8,"mp:micro");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000divs");
C_save(tmp);
tmp=C_fix(1);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[223]=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
lf[224]=C_static_string(C_heaptop,9,"mp:alloff");
tmp=C_intern(C_heaptop,9,"mp:alloff");
C_save(tmp);
tmp=C_SCHEME_END_OF_LIST;
lf[225]=C_h_pair(C_restore,tmp);
lf[226]=C_static_string(C_heaptop,7,"mp:ctrl");
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
lf[227]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[228]=C_static_string(C_heaptop,7,"mp:prog");
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
lf[229]=C_h_list(4,C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(4);
lf[230]=C_static_string(C_heaptop,6,"mp:off");
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
lf[231]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[232]=C_static_string(C_heaptop,5,"mp:on");
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
lf[233]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[234]=C_static_string(C_heaptop,7,"mp:note");
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
lf[235]=C_h_list(6,C_pick(5),C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(6);
lf[236]=C_static_lambda_info(C_heaptop,15,"(do455 tail457)");
lf[237]=C_static_string(C_heaptop,37,"~S found duplicate keyword \047~S\047 in ~S");
lf[238]=C_static_string(C_heaptop,33,"~S missing value for keyword \047~S\047");
lf[239]=C_static_string(C_heaptop,53,"~S found invalid keyword \047~S\047~%Available keywords: ~S");
lf[240]=C_h_intern(&lf[240],7,"\003sysmap");
lf[241]=C_h_intern(&lf[241],3,"car");
lf[242]=C_static_string(C_heaptop,32,"~S expected keyword but got \047~S\047");
lf[243]=C_h_intern(&lf[243],8,"keyword\077");
lf[244]=C_static_string(C_heaptop,35,"~S expected ~A arguments but got ~A");
lf[245]=C_static_lambda_info(C_heaptop,28,"(do438 key440 arg441 pos442)");
lf[246]=C_static_string(C_heaptop,24,"~S is an invalid message");
lf[247]=C_static_lambda_info(C_heaptop,7,"(a2303)");
lf[248]=C_h_intern(&lf[248],14,"hash-table-ref");
lf[249]=C_h_intern(&lf[249],14,"symbol->string");
lf[250]=C_static_lambda_info(C_heaptop,25,"(a3099 mess462 . data463)");
lf[251]=C_h_intern(&lf[251],4,"send");
lf[252]=C_h_intern(&lf[252],10,"*messages*");
lf[253]=C_h_intern(&lf[253],14,"string->symbol");
lf[254]=C_static_string(C_heaptop,51,"message function not string, symbol or list of both");
lf[255]=C_static_lambda_info(C_heaptop,23,"(a3105 func420 info421)");
lf[256]=C_h_intern(&lf[256],19,"define-send-message");
lf[257]=C_h_intern(&lf[257],15,"make-hash-table");
lf[258]=C_h_intern(&lf[258],6,"equal\077");
lf[259]=C_static_lambda_info(C_heaptop,10,"(toplevel)");
C_register_lf2(lf,260,create_ptable());
t2=C_mutate(&lf[0],lf[1]);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_617,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_library_toplevel(2,C_SCHEME_UNDEFINED,t3);}

/* k615 */
static void C_ccall f_617(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_617,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_620,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_eval_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k618 in k615 */
static void C_ccall f_620(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_620,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_623,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k621 in k618 in k615 */
static void C_ccall f_623(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_623,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_626,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k624 in k621 in k618 in k615 */
static void C_ccall f_626(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_626,2,t0,t1);}
t2=C_mutate(&lf[2],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_628,a[2]=lf[3],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate(&lf[4],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_655,a[2]=lf[5],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate(&lf[6],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_689,a[2]=lf[7],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate(&lf[8],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_764,a[2]=lf[9],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate(&lf[10],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_771,a[2]=lf[11],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate(&lf[12],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_809,a[2]=lf[13],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate(&lf[14],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_820,a[2]=lf[15],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate(&lf[16],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_827,a[2]=lf[17],tmp=(C_word)a,a+=3,tmp));
t10=C_mutate(&lf[18],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_838,a[2]=lf[19],tmp=(C_word)a,a+=3,tmp));
t11=C_mutate(&lf[20],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_848,a[2]=lf[21],tmp=(C_word)a,a+=3,tmp));
t12=C_mutate((C_word*)lf[22]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_861,a[2]=lf[23],tmp=(C_word)a,a+=3,tmp));
t13=C_mutate((C_word*)lf[24]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_880,a[2]=lf[25],tmp=(C_word)a,a+=3,tmp));
t14=C_mutate((C_word*)lf[26]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_962,a[2]=lf[27],tmp=(C_word)a,a+=3,tmp));
t15=C_mutate((C_word*)lf[28]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_968,a[2]=lf[29],tmp=(C_word)a,a+=3,tmp));
t16=C_mutate((C_word*)lf[30]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_974,a[2]=lf[31],tmp=(C_word)a,a+=3,tmp));
t17=C_mutate((C_word*)lf[32]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_993,a[2]=lf[39],tmp=(C_word)a,a+=3,tmp));
t18=C_mutate((C_word*)lf[40]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1053,a[2]=lf[41],tmp=(C_word)a,a+=3,tmp));
t19=C_mutate((C_word*)lf[42]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1059,a[2]=lf[43],tmp=(C_word)a,a+=3,tmp));
t20=C_mutate((C_word*)lf[44]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1065,a[2]=lf[45],tmp=(C_word)a,a+=3,tmp));
t21=C_mutate((C_word*)lf[46]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1071,a[2]=lf[47],tmp=(C_word)a,a+=3,tmp));
t22=C_mutate((C_word*)lf[48]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1077,a[2]=lf[49],tmp=(C_word)a,a+=3,tmp));
t23=C_mutate((C_word*)lf[50]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1083,a[2]=lf[57],tmp=(C_word)a,a+=3,tmp));
t24=C_mutate((C_word*)lf[58]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1178,a[2]=lf[59],tmp=(C_word)a,a+=3,tmp));
t25=C_mutate((C_word*)lf[60]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1184,a[2]=lf[63],tmp=(C_word)a,a+=3,tmp));
t26=C_mutate((C_word*)lf[64]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1243,a[2]=lf[65],tmp=(C_word)a,a+=3,tmp));
t27=C_mutate((C_word*)lf[66]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1249,a[2]=lf[68],tmp=(C_word)a,a+=3,tmp));
t28=C_mutate((C_word*)lf[69]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1337,a[2]=lf[73],tmp=(C_word)a,a+=3,tmp));
t29=C_mutate((C_word*)lf[74]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1395,a[2]=lf[76],tmp=(C_word)a,a+=3,tmp));
t30=C_mutate((C_word*)lf[77]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1418,a[2]=lf[78],tmp=(C_word)a,a+=3,tmp));
t31=C_mutate((C_word*)lf[79]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1424,a[2]=lf[80],tmp=(C_word)a,a+=3,tmp));
t32=C_mutate((C_word*)lf[81]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1430,a[2]=lf[82],tmp=(C_word)a,a+=3,tmp));
t33=C_mutate((C_word*)lf[83]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1436,a[2]=lf[84],tmp=(C_word)a,a+=3,tmp));
t34=C_mutate((C_word*)lf[85]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1442,a[2]=lf[88],tmp=(C_word)a,a+=3,tmp));
t35=C_mutate((C_word*)lf[89]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1486,a[2]=lf[90],tmp=(C_word)a,a+=3,tmp));
t36=C_mutate((C_word*)lf[91]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1505,a[2]=lf[92],tmp=(C_word)a,a+=3,tmp));
t37=C_mutate((C_word*)lf[93]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1545,a[2]=lf[94],tmp=(C_word)a,a+=3,tmp));
t38=C_mutate((C_word*)lf[95]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1551,a[2]=lf[97],tmp=(C_word)a,a+=3,tmp));
t39=C_mutate((C_word*)lf[98]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1570,a[2]=lf[99],tmp=(C_word)a,a+=3,tmp));
t40=C_mutate((C_word*)lf[100]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1589,a[2]=lf[101],tmp=(C_word)a,a+=3,tmp));
t41=C_mutate((C_word*)lf[102]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1595,a[2]=lf[103],tmp=(C_word)a,a+=3,tmp));
t42=C_mutate((C_word*)lf[104]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1601,a[2]=lf[106],tmp=(C_word)a,a+=3,tmp));
t43=C_mutate((C_word*)lf[107]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1615,a[2]=lf[108],tmp=(C_word)a,a+=3,tmp));
t44=C_mutate((C_word*)lf[109]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1658,a[2]=lf[110],tmp=(C_word)a,a+=3,tmp));
t45=C_mutate((C_word*)lf[111]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1661,a[2]=lf[112],tmp=(C_word)a,a+=3,tmp));
t46=C_mutate(&lf[113],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1673,a[2]=lf[116],tmp=(C_word)a,a+=3,tmp));
t47=C_mutate(&lf[117],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1682,a[2]=lf[119],tmp=(C_word)a,a+=3,tmp));
t48=C_mutate(&lf[120],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1726,a[2]=lf[122],tmp=(C_word)a,a+=3,tmp));
t49=C_mutate((C_word*)lf[123]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1748,a[2]=lf[130],tmp=(C_word)a,a+=3,tmp));
t50=C_mutate((C_word*)lf[131]+1,*((C_word*)lf[111]+1));
t51=C_mutate((C_word*)lf[132]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1916,a[2]=lf[139],tmp=(C_word)a,a+=3,tmp));
t52=C_mutate((C_word*)lf[140]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1979,a[2]=lf[142],tmp=(C_word)a,a+=3,tmp));
t53=C_mutate((C_word*)lf[143]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1988,a[2]=lf[145],tmp=(C_word)a,a+=3,tmp));
t54=C_mutate((C_word*)lf[146]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1994,a[2]=lf[148],tmp=(C_word)a,a+=3,tmp));
t55=C_mutate((C_word*)lf[149]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2003,a[2]=lf[152],tmp=(C_word)a,a+=3,tmp));
t56=C_mutate((C_word*)lf[153]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2061,a[2]=lf[155],tmp=(C_word)a,a+=3,tmp));
t57=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2072,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 279  make-hash-table");
t58=C_retrieve(lf[257]);
((C_proc3)C_retrieve_proc(t58))(3,t58,t57,*((C_word*)lf[258]+1));}

/* k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2072(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2072,2,t0,t1);}
t2=C_mutate(&lf[156],t1);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2075,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3106,a[2]=lf[255],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 281  ##sys#register-macro");
t5=C_retrieve(lf[217]);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,lf[256],t4);}

/* a3105 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_3106(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_3106,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3110,a[2]=t6,a[3]=t1,a[4]=t3,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t4)[1]))){
t8=(C_word)C_i_car(((C_word*)t4)[1]);
t9=C_set_block_item(t6,0,t8);
t10=(C_word)C_i_cadr(((C_word*)t4)[1]);
t11=C_set_block_item(t4,0,t10);
t12=t7;
f_3110(2,t12,t11);}
else{
if(C_truep((C_word)C_i_stringp(((C_word*)t4)[1]))){
t8=C_set_block_item(t6,0,((C_word*)t4)[1]);
t9=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3143,a[2]=t7,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 288  string->symbol");
t10=*((C_word*)lf[253]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)t4)[1]);}
else{
if(C_truep((C_word)C_i_symbolp(((C_word*)t4)[1]))){
t8=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3153,a[2]=t7,a[3]=t6,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 290  symbol->string");
t9=*((C_word*)lf[249]+1);
((C_proc3)C_retrieve_proc(t9))(3,t9,t8,((C_word*)t4)[1]);}
else{
C_trace("ChickenBridge.scm: 292  error");
t8=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,lf[254]);}}}}

/* k3151 in a3105 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_3153(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_3110(2,t3,t2);}

/* k3141 in a3105 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_3143(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_3110(2,t3,t2);}

/* k3108 in a3105 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_3110(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3110,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[4]);
t3=(C_word)C_a_i_list(&a,2,lf[193],t2);
t4=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_a_i_list(&a,4,lf[219],lf[252],((C_word*)((C_word*)t0)[2])[1],t3));}

/* k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2075(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2075,2,t0,t1);}
t2=C_mutate(&lf[157],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2077,a[2]=lf[159],tmp=(C_word)a,a+=3,tmp));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2314,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3100,a[2]=lf[250],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 368  ##sys#register-macro");
t5=C_retrieve(lf[217]);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,lf[251],t4);}

/* a3099 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_3100(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+6)){
C_save_and_reclaim((void*)tr3r,(void*)f_3100r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_3100r(t0,t1,t2,t3);}}

static void C_ccall f_3100r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a=C_alloc(6);
t4=t3;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2091,a[2]=t1,a[3]=t5,tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_symbolp(t2))){
C_trace("ChickenBridge.scm: 299  symbol->string");
t7=*((C_word*)lf[249]+1);
((C_proc3)C_retrieve_proc(t7))(3,t7,t6,t2);}
else{
t7=t6;
f_2091(2,t7,t2);}}

/* k2089 in a3099 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2091(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2091,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2094,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2304,a[2]=lf[247],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 300  hash-table-ref");
t4=*((C_word*)lf[248]+1);
((C_proc5)C_retrieve_proc(t4))(5,t4,t2,lf[156],t1,t3);}

/* a2303 in k2089 in a3099 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2304(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2304,2,t0,t1);}
t2=t1;
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}

/* k2092 in k2089 in a3099 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2094(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2094,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_2097,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=t1;
if(C_truep(t3)){
t4=t2;
f_2097(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 301  ferror");
f_2077(t2,lf[246],(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]));}}

/* k2095 in k2092 in k2089 in a3099 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2097(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2097,2,t0,t1);}
t2=((C_word*)((C_word*)t0)[5])[1];
t3=(C_word)C_i_car(((C_word*)t0)[4]);
t4=(C_word)C_i_cdr(((C_word*)t0)[4]);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(C_word)C_i_length(t4);
t8=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_2109,a[2]=t7,a[3]=t2,a[4]=((C_word*)t0)[2],a[5]=t6,a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[3],a[8]=t4,a[9]=t3,tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 308  append");
t9=*((C_word*)lf[209]+1);
((C_proc4)C_retrieve_proc(t9))(4,t9,t8,t4,C_SCHEME_END_OF_LIST);}

/* k2107 in k2095 in k2092 in k2089 in a3099 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2109(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[19],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2109,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_2112,a[2]=((C_word*)t0)[7],a[3]=((C_word*)t0)[8],a[4]=t1,a[5]=((C_word*)t0)[9],tmp=(C_word)a,a+=6,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_2157,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[5],a[8]=t4,a[9]=((C_word*)t0)[6],a[10]=lf[245],tmp=(C_word)a,a+=11,tmp));
t6=((C_word*)t4)[1];
f_2157(t6,t2,C_SCHEME_FALSE,C_SCHEME_FALSE,C_fix(0));}

/* do438 in k2107 in k2095 in k2092 in k2089 in a3099 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_fcall f_2157(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
C_save_and_reclaim((void*)trf_2157,NULL,5,t0,t1,t2,t3,t4);}
t5=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[9])[1]))){
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,C_SCHEME_FALSE);}
else{
t8=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_2167,a[2]=t7,a[3]=t6,a[4]=t5,a[5]=t1,a[6]=((C_word*)t0)[8],tmp=(C_word)a,a+=7,tmp);
t9=(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_2173,a[2]=((C_word*)t0)[2],a[3]=t7,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=t6,a[8]=((C_word*)t0)[6],a[9]=t5,a[10]=((C_word*)t0)[9],a[11]=t8,a[12]=((C_word*)t0)[7],tmp=(C_word)a,a+=13,tmp);
t10=((C_word*)((C_word*)t0)[7])[1];
if(C_truep(t10)){
t11=t9;
f_2173(2,t11,C_SCHEME_FALSE);}
else{
t11=(C_word)C_i_car(((C_word*)((C_word*)t0)[9])[1]);
C_trace("ChickenBridge.scm: 319  keyword?");
t12=C_retrieve(lf[243]);
((C_proc3)C_retrieve_proc(t12))(3,t12,t9,t11);}}}

/* k2171 in do438 in k2107 in k2095 in k2092 in k2089 in a3099 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2173(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2173,2,t0,t1);}
if(C_truep(t1)){
t2=C_set_block_item(((C_word*)t0)[12],0,C_SCHEME_TRUE);
t3=((C_word*)t0)[11];
f_2167(t3,t2);}
else{
t2=((C_word*)((C_word*)t0)[12])[1];
if(C_truep(t2)){
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[10])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[9])+1,t3);
t5=(C_word)C_i_assoc(((C_word*)((C_word*)t0)[9])[1],((C_word*)t0)[8]);
t6=C_mutate(((C_word *)((C_word*)t0)[7])+1,t5);
t7=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[10])[1]);
t8=C_mutate(((C_word *)((C_word*)t0)[10])+1,t7);
t9=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_2227,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[9],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[11],a[6]=((C_word*)t0)[10],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t10=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_2282,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[9],a[5]=((C_word*)t0)[5],a[6]=t9,a[7]=((C_word*)t0)[10],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 339  keyword?");
t11=C_retrieve(lf[243]);
((C_proc3)C_retrieve_proc(t11))(3,t11,t10,((C_word*)((C_word*)t0)[9])[1]);}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_2183,a[2]=((C_word*)t0)[11],a[3]=((C_word*)t0)[10],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[6],tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_nequalp(((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]))){
t4=(C_word)C_i_length(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 329  ferror");
f_2077(t3,lf[244],(C_word)C_a_i_list(&a,3,((C_word*)t0)[5],((C_word*)t0)[2],t4));}
else{
t4=t3;
f_2183(2,t4,C_SCHEME_UNDEFINED);}}}}

/* k2181 in k2171 in do438 in k2107 in k2095 in k2092 in k2089 in a3099 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2183(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2183,2,t0,t1);}
t2=(C_word)C_i_list_tail(((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]);
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
t4=(C_word)C_i_set_car(t2,t3);
t5=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[3])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t5);
t7=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[4])[1],C_fix(1));
t8=C_mutate(((C_word *)((C_word*)t0)[4])+1,t7);
t9=((C_word*)t0)[2];
f_2167(t9,t8);}

/* k2280 in k2171 in do438 in k2107 in k2095 in k2092 in k2089 in a3099 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2282(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2282,2,t0,t1);}
if(C_truep(t1)){
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[7])[1]))){
C_trace("ChickenBridge.scm: 343  ferror");
f_2077(((C_word*)t0)[6],lf[238],(C_word)C_a_i_list(&a,2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]));}
else{
t2=((C_word*)((C_word*)t0)[3])[1];
if(C_truep(t2)){
t3=((C_word*)t0)[6];
f_2227(2,t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2278,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
C_trace("map");
t4=*((C_word*)lf[240]+1);
((C_proc4)(void*)(*((C_word*)t4+1)))(4,t4,t3,*((C_word*)lf[241]+1),((C_word*)t0)[2]);}}}
else{
C_trace("ChickenBridge.scm: 340  ferror");
f_2077(((C_word*)t0)[6],lf[242],(C_word)C_a_i_list(&a,2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]));}}

/* k2276 in k2280 in k2171 in do438 in k2107 in k2095 in k2092 in k2089 in a3099 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2278(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2278,2,t0,t1);}
C_trace("ChickenBridge.scm: 346  ferror");
f_2077(((C_word*)t0)[4],lf[239],(C_word)C_a_i_list(&a,3,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1));}

/* k2225 in k2171 in do438 in k2107 in k2095 in k2092 in k2089 in a3099 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2227(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[14],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2227,2,t0,t1);}
t2=(C_word)C_i_member(((C_word*)((C_word*)t0)[8])[1],((C_word*)t0)[7]);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2233,a[2]=((C_word*)t0)[5],a[3]=t2,a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
if(C_truep(t2)){
t4=t3;
f_2233(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 353  ferror");
f_2077(t3,lf[237],(C_word)C_a_i_list(&a,3,((C_word*)t0)[4],((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]));}}

/* k2231 in k2225 in k2171 in do438 in k2107 in k2095 in k2092 in k2089 in a3099 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2233(C_word c,C_word t0,C_word t1){
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
f_2167(t6,t5);}

/* k2165 in do438 in k2107 in k2095 in k2092 in k2089 in a3099 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_fcall f_2167(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[6])[1];
f_2157(t2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k2110 in k2107 in k2095 in k2092 in k2089 in a3099 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2112(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2112,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_2117,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=lf[236],tmp=(C_word)a,a+=7,tmp));
t5=((C_word*)t3)[1];
f_2117(t5,((C_word*)t0)[2],((C_word*)t0)[4]);}

/* do455 in k2110 in k2107 in k2095 in k2092 in k2089 in a3099 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_fcall f_2117(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2117,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[5],((C_word*)t0)[4]));}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2130,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_member(t4,((C_word*)t0)[2]))){
t5=(C_word)C_i_car(t2);
t6=(C_word)C_i_cadr(t5);
t7=t3;
f_2130(t7,(C_word)C_i_set_car(t2,t6));}
else{
t5=t3;
f_2130(t5,C_SCHEME_UNDEFINED);}}}

/* k2128 in do455 in k2110 in k2107 in k2095 in k2092 in k2089 in a3099 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_fcall f_2130(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_2117(t3,((C_word*)t0)[2],t2);}

/* k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2314(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2314,2,t0,t1);}
t2=C_mutate((C_word*)lf[160]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2316,a[2]=lf[162],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[163]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2322,a[2]=lf[165],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate((C_word*)lf[166]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2328,a[2]=lf[168],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate((C_word*)lf[169]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2334,a[2]=lf[171],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[172]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2340,a[2]=lf[174],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate((C_word*)lf[175]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2346,a[2]=lf[177],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate((C_word*)lf[178]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2352,a[2]=lf[180],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate((C_word*)lf[181]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2358,a[2]=lf[183],tmp=(C_word)a,a+=3,tmp));
t10=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2365,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 395  hash-table-set!");
t11=C_retrieve(lf[219]);
((C_proc5)C_retrieve_proc(t11))(5,t11,t10,lf[156],lf[234],lf[235]);}

/* k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2365(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2365,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2368,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 396  hash-table-set!");
t3=C_retrieve(lf[219]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[156],lf[232],lf[233]);}

/* k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2368(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2368,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2371,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 397  hash-table-set!");
t3=C_retrieve(lf[219]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[156],lf[230],lf[231]);}

/* k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2371(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2371,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2374,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 398  hash-table-set!");
t3=C_retrieve(lf[219]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[156],lf[228],lf[229]);}

/* k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2374(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2374,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2377,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 399  hash-table-set!");
t3=C_retrieve(lf[219]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[156],lf[226],lf[227]);}

/* k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2377(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2377,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2380,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 400  hash-table-set!");
t3=C_retrieve(lf[219]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[156],lf[224],lf[225]);}

/* k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2380(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2380,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2383,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 401  hash-table-set!");
t3=C_retrieve(lf[219]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[156],lf[222],lf[223]);}

/* k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2383(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2383,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2386,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 402  hash-table-set!");
t3=C_retrieve(lf[219]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[156],lf[220],lf[221]);}

/* k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2386(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2386,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2389,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3094,a[2]=lf[216],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 408  ##sys#register-macro");
t4=C_retrieve(lf[217]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,lf[218],t3);}

/* a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_3094(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+17)){
C_save_and_reclaim((void*)tr4r,(void*)f_3094r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest(a,C_rest_count(0));
f_3094r(t0,t1,t2,t3,t4);}}

static void C_ccall f_3094r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
t13=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_2404,a[2]=t2,a[3]=t12,a[4]=t6,a[5]=t10,a[6]=t1,a[7]=t8,a[8]=t3,tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(t2))){
t14=t13;
f_2404(2,t14,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 417  error");
t14=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t14))(4,t14,t13,lf[215],t2);}}

/* k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2404(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2404,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_2407,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(((C_word*)t0)[8]))){
if(C_truep((C_word)C_i_nullp(((C_word*)t0)[8]))){
C_trace("ChickenBridge.scm: 421  error");
t3=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,lf[213]);}
else{
t3=t2;
f_2407(2,t3,C_SCHEME_UNDEFINED);}}
else{
C_trace("ChickenBridge.scm: 419  error");
t3=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t2,lf[214],((C_word*)t0)[8]);}}

/* k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2407(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2407,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_2410,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],tmp=(C_word)a,a+=8,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_2685,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[7],a[5]=t4,a[6]=lf[212],tmp=(C_word)a,a+=7,tmp));
t6=((C_word*)t4)[1];
f_2685(t6,t2,((C_word*)t0)[2]);}

/* do497 in k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_fcall f_2685(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_2685,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2695,a[2]=t1,a[3]=((C_word*)t0)[5],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_2705,a[2]=t3,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=t2,tmp=(C_word)a,a+=7,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2793,a[2]=t4,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t7=(C_word)C_i_car(t2);
t8=(C_word)C_i_length(t7);
C_trace("ChickenBridge.scm: 425  <");
C_lessp(5,0,t6,C_fix(0),t8,C_fix(4));}
else{
t6=t4;
f_2705(t6,C_SCHEME_FALSE);}}}

/* k2791 in do497 in k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2793(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=(C_word)C_i_car(t2);
t4=((C_word*)t0)[2];
f_2705(t4,(C_word)C_i_symbolp(t3));}
else{
t2=((C_word*)t0)[2];
f_2705(t2,C_SCHEME_FALSE);}}

/* k2703 in do497 in k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_fcall f_2705(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_2705,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[6]);
t3=(C_word)C_i_car(t2);
t4=(C_word)C_i_car(((C_word*)t0)[6]);
t5=(C_word)C_i_cadr(t4);
t6=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_2714,a[2]=t5,a[3]=t3,a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[5],tmp=(C_word)a,a+=8,tmp);
t7=(C_word)C_i_car(((C_word*)t0)[6]);
t8=(C_word)C_i_cddr(t7);
if(C_truep((C_word)C_i_nullp(t8))){
t9=t6;
f_2714(t9,lf[210]);}
else{
t9=(C_word)C_i_car(((C_word*)t0)[6]);
t10=t6;
f_2714(t10,(C_word)C_i_caddr(t9));}}
else{
t2=(C_word)C_i_car(((C_word*)t0)[6]);
C_trace("ChickenBridge.scm: 438  error");
t3=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[2],lf[211],t2);}}

/* k2712 in k2703 in do497 in k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_fcall f_2714(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2714,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_2718,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t3=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 433  append");
t4=*((C_word*)lf[209]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,((C_word*)((C_word*)t0)[7])[1],t3);}

/* k2716 in k2712 in k2703 in do497 in k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2718(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2718,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_2722,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
t4=(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 434  append");
t5=*((C_word*)lf[209]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,((C_word*)((C_word*)t0)[7])[1],t4);}

/* k2720 in k2716 in k2712 in k2703 in do497 in k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2722(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2722,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2726,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2730,a[2]=((C_word*)t0)[5],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_eqp(((C_word*)t0)[3],lf[210]);
if(C_truep(t5)){
t6=t4;
f_2730(t6,C_SCHEME_END_OF_LIST);}
else{
t6=(C_word)C_a_i_list(&a,3,lf[190],((C_word*)t0)[2],((C_word*)t0)[3]);
t7=t4;
f_2730(t7,(C_word)C_a_i_list(&a,1,t6));}}

/* k2728 in k2720 in k2716 in k2712 in k2703 in do497 in k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_fcall f_2730(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 435  append");
t2=*((C_word*)lf[209]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k2724 in k2720 in k2716 in k2712 in k2703 in do497 in k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2726(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_2695(2,t3,t2);}

/* k2693 in do497 in k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2695(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_2685(t3,((C_word*)t0)[2],t2);}

/* k2408 in k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2410(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2410,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_2413,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 440  gensym");
t3=C_retrieve(lf[208]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k2411 in k2408 in k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2413(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2413,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_2416,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 441  gensym");
t3=C_retrieve(lf[208]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k2414 in k2411 in k2408 in k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2416(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2416,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_2419,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 442  gensym");
t3=C_retrieve(lf[208]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k2417 in k2414 in k2411 in k2408 in k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2419(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2419,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_2422,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],a[10]=((C_word*)t0)[9],tmp=(C_word)a,a+=11,tmp);
C_trace("ChickenBridge.scm: 443  gensym");
t3=C_retrieve(lf[208]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k2420 in k2417 in k2414 in k2411 in k2408 in k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2422(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2422,2,t0,t1);}
t2=C_SCHEME_TRUE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_SCHEME_END_OF_LIST;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_2425,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=t3,a[7]=((C_word*)t0)[5],a[8]=((C_word*)t0)[6],a[9]=((C_word*)t0)[7],a[10]=((C_word*)t0)[8],a[11]=((C_word*)t0)[9],a[12]=t5,a[13]=((C_word*)t0)[10],tmp=(C_word)a,a+=14,tmp);
t7=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2578,a[2]=t6,a[3]=t3,a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)((C_word*)t0)[3])[1]))){
t8=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
if(C_truep((C_word)C_i_pairp(t8))){
t9=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2679,a[2]=t7,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 449  caar");
t10=*((C_word*)lf[204]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)((C_word*)t0)[3])[1]);}
else{
t9=t7;
f_2578(t9,C_SCHEME_FALSE);}}
else{
t8=t7;
f_2578(t8,C_SCHEME_FALSE);}}

/* k2677 in k2420 in k2417 in k2414 in k2411 in k2408 in k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2679(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_2578(t2,(C_word)C_eqp(t1,lf[207]));}

/* k2576 in k2420 in k2417 in k2414 in k2411 in k2408 in k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_fcall f_2578(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2578,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2585,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 450  cdar");
t3=*((C_word*)lf[202]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)((C_word*)t0)[4])[1]);}
else{
t2=((C_word*)t0)[2];
f_2425(2,t2,C_SCHEME_UNDEFINED);}}

/* k2583 in k2576 in k2420 in k2417 in k2414 in k2411 in k2408 in k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2585(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2585,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_2587,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=lf[206],tmp=(C_word)a,a+=6,tmp));
t5=((C_word*)t3)[1];
f_2587(t5,((C_word*)t0)[2],t1);}

/* do513 in k2583 in k2576 in k2420 in k2417 in k2414 in k2411 in k2408 in k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_fcall f_2587(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_2587,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[4])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[4])+1,t3);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,t4);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2601,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2611,a[2]=t2,a[3]=((C_word*)t0)[2],a[4]=t3,tmp=(C_word)a,a+=5,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2659,a[2]=t4,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 454  cdar");
t7=*((C_word*)lf[202]+1);
((C_proc3)C_retrieve_proc(t7))(3,t7,t6,t2);}
else{
t6=t4;
f_2611(t6,C_SCHEME_FALSE);}}}

/* k2657 in do513 in k2583 in k2576 in k2420 in k2417 in k2414 in k2411 in k2408 in k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2659(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_2611(t2,(C_word)C_i_pairp(t1));}

/* k2609 in do513 in k2583 in k2576 in k2420 in k2417 in k2414 in k2411 in k2408 in k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_fcall f_2611(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2611,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2614,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 455  caar");
t3=*((C_word*)lf[204]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)t0)[2]);}
else{
t2=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 461  error");
t3=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[4],lf[205],t2);}}

/* k2612 in k2609 in do513 in k2583 in k2576 in k2420 in k2417 in k2414 in k2411 in k2408 in k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2614(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2614,2,t0,t1);}
t2=(C_word)C_eqp(t1,lf[201]);
if(C_truep(t2)){
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2635,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 457  cdar");
t4=*((C_word*)lf[202]+1);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)t0)[2]);}
else{
t3=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 460  error");
t4=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,((C_word*)t0)[4],lf[203],t3);}}

/* k2633 in k2612 in k2609 in do513 in k2583 in k2576 in k2420 in k2417 in k2414 in k2411 in k2408 in k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2635(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep((C_word)C_i_car(t1))){
t2=((C_word*)t0)[3];
f_2601(2,t2,C_SCHEME_UNDEFINED);}
else{
t2=C_set_block_item(((C_word*)t0)[2],0,C_SCHEME_FALSE);
t3=((C_word*)t0)[3];
f_2601(2,t3,t2);}}

/* k2599 in do513 in k2583 in k2576 in k2420 in k2417 in k2414 in k2411 in k2408 in k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2601(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_2587(t3,((C_word*)t0)[2],t2);}

/* k2423 in k2420 in k2417 in k2414 in k2411 in k2408 in k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2425(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2425,2,t0,t1);}
t2=(C_word)C_i_car(((C_word*)t0)[13]);
t3=(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_2567,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],a[10]=((C_word*)t0)[10],a[11]=((C_word*)t0)[11],a[12]=((C_word*)t0)[12],a[13]=t2,tmp=(C_word)a,a+=14,tmp);
t4=(C_word)C_i_cdr(((C_word*)t0)[13]);
t5=(C_word)C_a_i_list(&a,1,C_fix(-1));
C_trace("ChickenBridge.scm: 412  ##sys#append");
t6=*((C_word*)lf[200]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t3,t4,t5);}

/* k2565 in k2423 in k2420 in k2417 in k2414 in k2411 in k2408 in k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2567(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2567,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[13],t1);
t3=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_2551,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],a[8]=((C_word*)t0)[10],a[9]=((C_word*)t0)[11],a[10]=((C_word*)t0)[12],a[11]=t2,tmp=(C_word)a,a+=12,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2555,a[2]=((C_word*)t0)[3],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_a_i_list(&a,1,((C_word*)t0)[10]);
C_trace("ChickenBridge.scm: 412  ##sys#append");
t6=*((C_word*)lf[200]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t4,((C_word*)((C_word*)t0)[2])[1],t5);}

/* k2553 in k2565 in k2423 in k2420 in k2417 in k2414 in k2411 in k2408 in k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2555(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 412  ##sys#append");
t2=*((C_word*)lf[200]+1);
((C_proc4)(void*)(*((C_word*)t2+1)))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k2549 in k2565 in k2423 in k2420 in k2417 in k2414 in k2411 in k2408 in k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2551(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2551,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,lf[185],t1);
t3=(C_word)C_a_i_list(&a,3,lf[186],((C_word*)t0)[11],t2);
t4=C_mutate(((C_word *)((C_word*)t0)[10])+1,t3);
t5=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_2432,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],a[5]=((C_word*)t0)[10],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],tmp=(C_word)a,a+=8,tmp);
if(C_truep(((C_word*)((C_word*)t0)[4])[1])){
t6=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
t7=(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]);
t8=(C_word)C_a_i_list(&a,2,lf[193],lf[194]);
t9=(C_word)C_a_i_list(&a,2,lf[193],lf[195]);
t10=(C_word)C_a_i_list(&a,3,lf[196],t8,t9);
t11=(C_word)C_a_i_list(&a,2,t10,((C_word*)t0)[2]);
t12=(C_word)C_a_i_list(&a,4,lf[158],lf[197],t11,((C_word*)t0)[9]);
t13=(C_word)C_a_i_list(&a,2,lf[107],t12);
t14=(C_word)C_a_i_list(&a,2,((C_word*)t0)[3],C_fix(-2));
t15=(C_word)C_a_i_list(&a,4,lf[187],t7,t13,t14);
t16=(C_word)C_a_i_list(&a,3,lf[187],C_SCHEME_END_OF_LIST,((C_word*)((C_word*)t0)[10])[1]);
t17=(C_word)C_a_i_list(&a,3,lf[198],t15,t16);
t18=(C_word)C_a_i_list(&a,3,lf[187],t6,t17);
t19=(C_word)C_a_i_list(&a,2,lf[199],t18);
t20=C_mutate(((C_word *)((C_word*)t0)[10])+1,t19);
t21=t5;
f_2432(t21,t20);}
else{
t6=t5;
f_2432(t6,C_SCHEME_UNDEFINED);}}

/* k2430 in k2549 in k2565 in k2423 in k2420 in k2417 in k2414 in k2411 in k2408 in k2405 in k2402 in a3093 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_fcall f_2432(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_2432,NULL,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,((C_word*)t0)[7]);
t3=(C_word)C_a_i_list(&a,2,((C_word*)t0)[6],C_fix(0));
t4=(C_word)C_a_i_list(&a,3,lf[187],C_SCHEME_END_OF_LIST,((C_word*)t0)[7]);
t5=(C_word)C_a_i_list(&a,2,lf[188],t4);
t6=(C_word)C_a_i_list(&a,1,lf[189]);
t7=(C_word)C_a_i_list(&a,3,lf[190],((C_word*)t0)[6],lf[189]);
t8=(C_word)C_a_i_list(&a,3,lf[187],t6,t7);
t9=(C_word)C_a_i_list(&a,2,lf[191],t8);
t10=(C_word)C_a_i_list(&a,3,t3,t5,t9);
t11=(C_word)C_a_i_list(&a,3,lf[192],t10,((C_word*)((C_word*)t0)[5])[1]);
t12=(C_word)C_a_i_list(&a,3,lf[187],t2,t11);
t13=(C_word)C_a_i_list(&a,3,lf[187],((C_word*)((C_word*)t0)[4])[1],t12);
t14=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t14+1)))(2,t14,(C_word)C_a_i_cons(&a,2,t13,((C_word*)((C_word*)t0)[2])[1]));}

/* k2387 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2389(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2389,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3092,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 574  return-to-host");
t3=C_retrieve(lf[184]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k3090 in k2387 in k2384 in k2381 in k2378 in k2375 in k2372 in k2369 in k2366 in k2363 in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_3092(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_UNDEFINED);}

/* mp:inhook in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2358(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_2358,5,t0,t1,t2,t3,t4);}
C_trace("ChickenBridge.scm: 391  error");
t5=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t5))(3,t5,t1,lf[182]);}

/* mp:micro in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2352(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2352,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 389  error");
t3=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[179]);}

/* mp:alloff in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2346(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2346,2,t0,t1);}
C_trace("ChickenBridge.scm: 387  error");
t2=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,t1,lf[176]);}

/* mp:ctrl in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2340(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_2340,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 385  error");
t6=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[173]);}

/* mp:prog in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2334(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_2334,5,t0,t1,t2,t3,t4);}
C_trace("ChickenBridge.scm: 383  error");
t5=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t5))(3,t5,t1,lf[170]);}

/* mp:off in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2328(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_2328,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 381  error");
t6=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[167]);}

/* mp:on in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2322(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_2322,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 379  error");
t6=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[164]);}

/* mp:note in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2316(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
C_word tmp;
C_word t7;
C_word t8;
C_word ab[8],*a=ab;
if(c!=7) C_bad_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr7,(void*)f_2316,7,t0,t1,t2,t3,t4,t5,t6);}
t7=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_1633,a[2]=t1,a[3]=t6,a[4]=t5,a[5]=t4,a[6]=t3,a[7]=t2,tmp=(C_word)a,a+=8,tmp);
C_trace("##sys#gc");
t8=C_retrieve(lf[115]);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,C_SCHEME_FALSE);}

/* k1631 in mp:note in k2312 in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_1633(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_1633,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[7]);
t4=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[6]);
t5=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[5]);
t6=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[4]);
t7=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[3]);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub310,a[2]=lf[161],tmp=(C_word)a,a+=3,tmp);
((C_proc8)C_retrieve_proc(t8))(8,t8,((C_word*)t0)[2],t2,t3,t4,t5,t6,t7);}

/* ferror in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_fcall f_2077(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2077,NULL,3,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2085,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_apply(5,0,t4,C_retrieve(lf[158]),t2,t3);}

/* k2083 in ferror in k2073 in k2070 in k624 in k621 in k618 in k615 */
static void C_ccall f_2085(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 296  error");
t2=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* hush in k624 in k621 in k618 in k615 */
static void C_ccall f_2061(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2061,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2065,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1743,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[115]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k1741 in hush in k624 in k621 in k618 in k615 */
static void C_ccall f_1743(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1743,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub363,a[2]=lf[154],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k2063 in hush in k624 in k621 in k618 in k615 */
static void C_ccall f_2065(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 273  values");
C_values(2,0,((C_word*)t0)[2]);}

/* stop in k624 in k621 in k618 in k615 */
static void C_ccall f_2003(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+9)){
C_save_and_reclaim((void*)tr2r,(void*)f_2003r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_2003r(t0,t1,t2);}}

static void C_ccall f_2003r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a=C_alloc(9);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2007,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 263  scheduler-stop");
f_1726(t3,C_fix(-1));}
else{
t4=C_SCHEME_UNDEFINED;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_set_block_item(t5,0,(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2021,a[2]=t5,a[3]=lf[151],tmp=(C_word)a,a+=4,tmp));
t7=((C_word*)t5)[1];
f_2021(t7,t3,t2);}}

/* do413 in stop in k624 in k621 in k618 in k615 */
static void C_fcall f_2021(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2021,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2031,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_fixnump(t4))){
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 267  scheduler-stop");
f_1726(t3,t5);}
else{
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 268  error");
t6=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t3,lf[150],t5);}}}

/* k2029 in do413 in stop in k624 in k621 in k618 in k615 */
static void C_ccall f_2031(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_2021(t3,((C_word*)t0)[2],t2);}

/* k2005 in stop in k624 in k621 in k618 in k615 */
static void C_ccall f_2007(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 269  values");
C_values(2,0,((C_word*)t0)[2]);}

/* cont in k624 in k621 in k618 in k615 */
static void C_ccall f_1994(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1994,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1998,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1721,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[115]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k1719 in cont in k624 in k621 in k618 in k615 */
static void C_ccall f_1721(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1721,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub353,a[2]=lf[147],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k1996 in cont in k624 in k621 in k618 in k615 */
static void C_ccall f_1998(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 259  values");
C_values(2,0,((C_word*)t0)[2]);}

/* paused? in k624 in k621 in k618 in k615 */
static void C_ccall f_1988(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1988,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1703,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t3=C_retrieve(lf[115]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,C_SCHEME_FALSE);}

/* k1701 in paused? in k624 in k621 in k618 in k615 */
static void C_ccall f_1703(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1703,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub345,a[2]=lf[144],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* pause in k624 in k621 in k618 in k615 */
static void C_ccall f_1979(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1979,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1983,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1712,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[115]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k1710 in pause in k624 in k621 in k618 in k615 */
static void C_ccall f_1712(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1712,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub349,a[2]=lf[141],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k1981 in pause in k624 in k621 in k618 in k615 */
static void C_ccall f_1983(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 252  values");
C_values(2,0,((C_word*)t0)[2]);}

/* time-format in k624 in k621 in k618 in k615 */
static void C_ccall f_1916(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+11)){
C_save_and_reclaim((void*)tr2rv,(void*)f_1916r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_1916r(t0,t1,t2);}}

static void C_ccall f_1916r(C_word t0,C_word t1,C_word t2){
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
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1929,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1668,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t5=C_retrieve(lf[115]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,C_SCHEME_FALSE);}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
t4=(C_word)C_i_eqvp(t3,lf[135]);
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1941,a[2]=t2,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
if(C_truep(t4)){
t6=t5;
f_1941(t6,t4);}
else{
t6=(C_word)C_eqp(t3,C_fix(1));
t7=t5;
f_1941(t7,(C_truep(t6)?t6:(C_word)C_eqp(t3,lf[138])));}}}

/* k1939 in time-format in k624 in k621 in k618 in k615 */
static void C_fcall f_1941(C_word t0,C_word t1){
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
f_1673(((C_word*)t0)[4],C_SCHEME_FALSE);}
else{
t2=(C_word)C_eqp(((C_word*)t0)[3],C_fix(1000));
t3=(C_truep(t2)?t2:(C_word)C_eqp(((C_word*)t0)[3],lf[136]));
if(C_truep(t3)){
t4=C_mutate((C_word*)lf[131]+1,*((C_word*)lf[109]+1));
C_trace("ChickenBridge.scm: 245  scheduler-set-time-milliseconds");
f_1673(((C_word*)t0)[4],C_SCHEME_TRUE);}
else{
t4=(C_word)C_i_vector_ref(((C_word*)t0)[2],C_fix(0));
C_trace("ChickenBridge.scm: 248  error");
t5=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,((C_word*)t0)[4],lf[137],t4);}}}

/* k1666 in time-format in k624 in k621 in k618 in k615 */
static void C_ccall f_1668(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1668,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub325,a[2]=lf[134],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k1927 in time-format in k624 in k621 in k618 in k615 */
static void C_ccall f_1929(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_truep(t1)?C_fix(1000):lf[133]));}

/* sprout in k624 in k621 in k618 in k615 */
static void C_ccall f_1748(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+12)){
C_save_and_reclaim((void*)tr3r,(void*)f_1748r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_1748r(t0,t1,t2,t3);}}

static void C_ccall f_1748r(C_word t0,C_word t1,C_word t2,C_word t3){
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
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1750,a[2]=t2,a[3]=lf[127],tmp=(C_word)a,a+=4,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1862,a[2]=t4,a[3]=lf[128],tmp=(C_word)a,a+=4,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1867,a[2]=t5,a[3]=lf[129],tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("def-start373394");
t7=t6;
f_1867(t7,t1);}
else{
t7=(C_word)C_i_car(t3);
t8=(C_word)C_i_cdr(t3);
if(C_truep((C_word)C_i_nullp(t8))){
C_trace("def-id374392");
t9=t5;
f_1862(t9,t1,t7);}
else{
t9=(C_word)C_i_car(t8);
t10=(C_word)C_i_cdr(t8);
if(C_truep((C_word)C_i_nullp(t10))){
C_trace("body371376");
t11=t4;
f_1750(t11,t1,t7,t9);}
else{
C_trace("##sys#error");
t11=*((C_word*)lf[38]+1);
((C_proc4)(void*)(*((C_word*)t11+1)))(4,t11,t1,lf[0],t10);}}}}

/* def-start373 in sprout in k624 in k621 in k618 in k615 */
static void C_fcall f_1867(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1867,NULL,2,t0,t1);}
C_trace("def-id374392");
t2=((C_word*)t0)[2];
f_1862(t2,t1,C_fix(0));}

/* def-id374 in sprout in k624 in k621 in k618 in k615 */
static void C_fcall f_1862(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1862,NULL,3,t0,t1,t2);}
C_trace("body371376");
t3=((C_word*)t0)[2];
f_1750(t3,t1,t2,C_fix(-1));}

/* body371 in sprout in k624 in k621 in k618 in k615 */
static void C_fcall f_1750(C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)trf_1750,NULL,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1752,a[2]=t4,a[3]=lf[124],tmp=(C_word)a,a+=4,tmp);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1780,a[2]=t5,a[3]=lf[125],tmp=(C_word)a,a+=4,tmp);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1810,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t0)[2]))){
t9=C_SCHEME_UNDEFINED;
t10=(*a=C_VECTOR_TYPE|1,a[1]=t9,tmp=(C_word)a,a+=2,tmp);
t11=C_set_block_item(t10,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_1821,a[2]=t6,a[3]=t7,a[4]=t10,a[5]=((C_word*)t0)[2],a[6]=lf[126],tmp=(C_word)a,a+=7,tmp));
t12=((C_word*)t10)[1];
f_1821(t12,t8,((C_word*)t0)[2]);}
else{
t9=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1853,a[2]=((C_word*)t0)[2],a[3]=t8,tmp=(C_word)a,a+=4,tmp);
t10=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1857,a[2]=t7,a[3]=((C_word*)t0)[2],a[4]=t9,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 225  nextstart");
t11=t6;
f_1752(t11,t10);}}

/* k1855 in body371 in sprout in k624 in k621 in k618 in k615 */
static void C_ccall f_1857(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1857,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1861,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 225  nextid");
t3=((C_word*)t0)[2];
f_1780(t3,t2);}

/* k1859 in k1855 in body371 in sprout in k624 in k621 in k618 in k615 */
static void C_ccall f_1861(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 225  scheduler-sprout");
f_1682(((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k1851 in body371 in sprout in k624 in k621 in k618 in k615 */
static void C_ccall f_1853(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
f_1810(2,t2,((C_word*)t0)[2]);}

/* do385 in body371 in sprout in k624 in k621 in k618 in k615 */
static void C_fcall f_1821(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1821,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,((C_word*)t0)[5]);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1831,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1846,a[2]=((C_word*)t0)[3],a[3]=t4,a[4]=t3,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 223  nextstart");
t6=((C_word*)t0)[2];
f_1752(t6,t5);}}

/* k1844 in do385 in body371 in sprout in k624 in k621 in k618 in k615 */
static void C_ccall f_1846(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1846,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1850,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 223  nextid");
t3=((C_word*)t0)[2];
f_1780(t3,t2);}

/* k1848 in k1844 in do385 in body371 in sprout in k624 in k621 in k618 in k615 */
static void C_ccall f_1850(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 223  scheduler-sprout");
f_1682(((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k1829 in do385 in body371 in sprout in k624 in k621 in k618 in k615 */
static void C_ccall f_1831(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_1821(t3,((C_word*)t0)[2],t2);}

/* k1808 in body371 in sprout in k624 in k621 in k618 in k615 */
static void C_ccall f_1810(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 229  values");
C_values(2,0,((C_word*)t0)[2]);}

/* nextid in body371 in sprout in k624 in k621 in k618 in k615 */
static void C_fcall f_1780(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_1780,NULL,2,t0,t1);}
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

/* nextstart in body371 in sprout in k624 in k621 in k618 in k615 */
static void C_fcall f_1752(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_1752,NULL,2,t0,t1);}
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

/* scheduler-stop in k624 in k621 in k618 in k615 */
static void C_fcall f_1726(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1726,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1730,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[115]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k1728 in scheduler-stop in k624 in k621 in k618 in k615 */
static void C_ccall f_1730(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1730,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_fixnum_argumentp(((C_word*)t0)[3]);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub358,a[2]=lf[121],tmp=(C_word)a,a+=3,tmp);
((C_proc4)C_retrieve_proc(t4))(4,t4,((C_word*)t0)[2],t2,t3);}

/* scheduler-sprout in k624 in k621 in k618 in k615 */
static void C_fcall f_1682(C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1682,NULL,4,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_1686,a[2]=t2,a[3]=t1,a[4]=t4,a[5]=t3,tmp=(C_word)a,a+=6,tmp);
C_trace("##sys#gc");
t6=C_retrieve(lf[115]);
((C_proc3)C_retrieve_proc(t6))(3,t6,t5,C_SCHEME_FALSE);}

/* k1684 in scheduler-sprout in k624 in k621 in k618 in k615 */
static void C_ccall f_1686(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1686,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[5]);
t4=(C_word)C_i_foreign_fixnum_argumentp(((C_word*)t0)[4]);
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub338,a[2]=lf[118],tmp=(C_word)a,a+=3,tmp);
((C_proc6)C_retrieve_proc(t5))(6,t5,((C_word*)t0)[3],t2,((C_word*)t0)[2],t3,t4);}

/* scheduler-set-time-milliseconds in k624 in k621 in k618 in k615 */
static void C_fcall f_1673(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1673,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1677,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[115]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k1675 in scheduler-set-time-milliseconds in k624 in k621 in k618 in k615 */
static void C_ccall f_1677(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1677,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub330,a[2]=lf[114],tmp=(C_word)a,a+=3,tmp);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[3],t2,((C_word*)t0)[2]);}

/* current-time-seconds in k624 in k621 in k618 in k615 */
static void C_ccall f_1661(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1661,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub322(t2));}

/* current-time-milliseconds in k624 in k621 in k618 in k615 */
static void C_ccall f_1658(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1658,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub319(t2));}

/* print-error in k624 in k621 in k618 in k615 */
static void C_ccall f_1615(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1615,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1620,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[105]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_1620(2,t4,C_SCHEME_FALSE);}}

/* k1618 in print-error in k624 in k621 in k618 in k615 */
static void C_ccall f_1620(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub300(C_SCHEME_UNDEFINED,t1));}

/* print-message in k624 in k621 in k618 in k615 */
static void C_ccall f_1601(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1601,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1606,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[105]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_1606(2,t4,C_SCHEME_FALSE);}}

/* k1604 in print-message in k624 in k621 in k618 in k615 */
static void C_ccall f_1606(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub294(C_SCHEME_UNDEFINED,t1));}

/* ranpink in k624 in k621 in k618 in k615 */
static void C_ccall f_1595(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1595,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub145(t2));}

/* ranbrown in k624 in k621 in k618 in k615 */
static void C_ccall f_1589(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1589,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub148(t2));}

/* rangamma in k624 in k621 in k618 in k615 */
static void C_ccall f_1570(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2rv,(void*)f_1570r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_1570r(t0,t1,t2);}}

static void C_ccall f_1570r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
if(C_truep((C_word)C_vemptyp(t2))){
C_trace("ChickenBridge.scm: 109  tb:rangamma");
f_838(t1,C_fix(1));}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
C_trace("ChickenBridge.scm: 109  tb:rangamma");
f_838(t1,t3);}}

/* ranpoisson in k624 in k621 in k618 in k615 */
static void C_ccall f_1551(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2rv,(void*)f_1551r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_1551r(t0,t1,t2);}}

static void C_ccall f_1551r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
if(C_truep((C_word)C_i_nullp(C_retrieve(lf[96])))){
C_trace("ChickenBridge.scm: 109  tb:ranpoisson");
f_848(t1,C_fix(1));}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
C_trace("ChickenBridge.scm: 109  tb:ranpoisson");
f_848(t1,t3);}}

/* rancauchy in k624 in k621 in k618 in k615 */
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
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub138(t2));}

/* rangauss in k624 in k621 in k618 in k615 */
static void C_ccall f_1505(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2r,(void*)f_1505r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_1505r(t0,t1,t2);}}

static void C_ccall f_1505r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 109  tb:rangauss");
f_809(t1,C_fix(1),C_fix(0));}
else{
t3=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 109  tb:rangauss");
f_809(t1,t4,C_fix(0));}
else{
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cdr(t2);
C_trace("ChickenBridge.scm: 109  tb:rangauss");
f_809(t1,t4,t5);}}}

/* ranexp in k624 in k621 in k618 in k615 */
static void C_ccall f_1486(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2rv,(void*)f_1486r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_1486r(t0,t1,t2);}}

static void C_ccall f_1486r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
if(C_truep((C_word)C_vemptyp(t2))){
C_trace("ChickenBridge.scm: 109  tb:ranexp");
f_820(t1,C_fix(1));}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
C_trace("ChickenBridge.scm: 109  tb:ranexp");
f_820(t1,t3);}}

/* ranbeta in k624 in k621 in k618 in k615 */
static void C_ccall f_1442(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2r,(void*)f_1442r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_1442r(t0,t1,t2);}}

static void C_ccall f_1442r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 109  tb:ranbeta");
f_827(t1,lf[86],lf[87]);}
else{
t3=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 109  tb:ranbeta");
f_827(t1,t4,t5);}
else{
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cadr(t2);
C_trace("ChickenBridge.scm: 109  tb:ranbeta");
f_827(t1,t4,t5);}}}

/* ranmiddle in k624 in k621 in k618 in k615 */
static void C_ccall f_1436(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1436,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub111(t2));}

/* ranhigh in k624 in k621 in k618 in k615 */
static void C_ccall f_1430(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1430,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub108(t2));}

/* ranlow in k624 in k621 in k618 in k615 */
static void C_ccall f_1424(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1424,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub105(t2));}

/* pick in k624 in k621 in k618 in k615 */
static void C_ccall f_1418(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2r,(void*)f_1418r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_1418r(t0,t1,t2);}}

static void C_ccall f_1418r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_trace("ChickenBridge.scm: 109  pickl");
t3=*((C_word*)lf[74]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,t2);}

/* pickl in k624 in k621 in k618 in k615 */
static void C_ccall f_1395(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1395,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 109  error");
t3=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t1,lf[75],t2);}
else{
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1412,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
t4=(C_word)C_i_length(t2);
C_trace("ChickenBridge.scm: 109  tb:rani");
f_764(t3,t4);}}

/* k1410 in pickl in k624 in k621 in k618 in k615 */
static void C_ccall f_1412(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_i_list_ref(((C_word*)t0)[2],t1));}

/* odds in k624 in k621 in k618 in k615 */
static void C_ccall f_1337(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+14)){
C_save_and_reclaim((void*)tr3r,(void*)f_1337r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_1337r(t0,t1,t2,t3);}}

static void C_ccall f_1337r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word *a=C_alloc(14);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1354,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 109  tb:ranf");
f_771(t4,lf[70]);}
else{
t4=(C_word)C_i_cdr(t3);
if(C_truep((C_word)C_i_nullp(t4))){
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1373,a[2]=t3,a[3]=t1,a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 109  tb:ranf");
f_771(t5,lf[71]);}
else{
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1389,a[2]=t3,a[3]=t1,a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 109  tb:ranf");
f_771(t5,lf[72]);}}}

/* k1387 in odds in k624 in k621 in k618 in k615 */
static void C_ccall f_1389(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_lessp(t1,((C_word*)t0)[4]);
t3=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_truep(t2)?(C_word)C_i_car(((C_word*)t0)[2]):(C_word)C_i_cadr(((C_word*)t0)[2])));}

/* k1371 in odds in k624 in k621 in k618 in k615 */
static void C_ccall f_1373(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_lessp(t1,((C_word*)t0)[4]);
t3=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_truep(t2)?(C_word)C_i_car(((C_word*)t0)[2]):C_SCHEME_FALSE));}

/* k1352 in odds in k624 in k621 in k618 in k615 */
static void C_ccall f_1354(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_lessp(t1,((C_word*)t0)[3]);
t3=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_truep(t2)?C_SCHEME_TRUE:C_SCHEME_FALSE));}

/* ran in k624 in k621 in k618 in k615 */
static void C_ccall f_1249(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+4)){
C_save_and_reclaim((void*)tr2r,(void*)f_1249r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_1249r(t0,t1,t2);}}

static void C_ccall f_1249r(C_word t0,C_word t1,C_word t2){
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
f_771(t1,lf[67]);}
else{
t3=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_fixnump(t4))){
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 109  tb:rani");
f_764(t1,t5);}
else{
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 109  tb:ranf");
f_771(t1,t5);}}
else{
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1295,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_fixnump(t5))){
t6=(C_word)C_i_cadr(t2);
t7=t4;
f_1295(t7,(C_word)C_fixnump(t6));}
else{
t6=t4;
f_1295(t6,C_SCHEME_FALSE);}}}}

/* k1293 in ran in k624 in k621 in k618 in k615 */
static void C_fcall f_1295(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_1295,NULL,2,t0,t1);}
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

/* ran-set! in k624 in k621 in k618 in k615 */
static void C_ccall f_1243(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1243,3,t0,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub80(C_SCHEME_UNDEFINED,t2));}

/* steps in k624 in k621 in k618 in k615 */
static void C_ccall f_1184(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+12)){
C_save_and_reclaim((void*)tr4rv,(void*)f_1184r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest_vector(a,C_rest_count(0));
f_1184r(t0,t1,t2,t3,t4);}}

static void C_ccall f_1184r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
t9=C_set_block_item(t8,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_1197,a[2]=t5,a[3]=t8,a[4]=t4,a[5]=t2,a[6]=lf[62],tmp=(C_word)a,a+=7,tmp));
t10=((C_word*)t8)[1];
f_1197(t10,t1,C_fix(0),t3,t6,t5);}

/* do216 in steps in k624 in k621 in k618 in k615 */
static void C_fcall f_1197(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
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
C_save_and_reclaim((void*)trf_1197,NULL,6,t0,t1,t2,t3,t4,t5);}
t6=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
if(C_truep((C_word)C_i_lessp(t2,((C_word*)t0)[5]))){
t8=(C_word)C_a_i_list(&a,1,((C_word*)t6)[1]);
t9=(C_word)C_i_set_cdr(((C_word*)t7)[1],t8);
t10=(C_word)C_i_cdr(((C_word*)t7)[1]);
t11=C_set_block_item(t7,0,t10);
t12=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_1233,a[2]=t7,a[3]=t4,a[4]=t1,a[5]=((C_word*)t0)[3],a[6]=t2,a[7]=t6,a[8]=((C_word*)t0)[4],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 109  modulo");
t13=*((C_word*)lf[61]+1);
((C_proc4)C_retrieve_proc(t13))(4,t13,t12,t2,t4);}
else{
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,(C_word)C_i_cdr(((C_word*)t0)[2]));}}

/* k1231 in do216 in steps in k624 in k621 in k618 in k615 */
static void C_ccall f_1233(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1233,2,t0,t1);}
t2=(C_word)C_i_vector_ref(((C_word*)t0)[8],t1);
t3=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[7])[1],t2);
t4=C_mutate(((C_word *)((C_word*)t0)[7])+1,t3);
t5=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[6],C_fix(1));
t6=((C_word*)((C_word*)t0)[5])[1];
f_1197(t6,((C_word*)t0)[4],t5,((C_word*)((C_word*)t0)[7])[1],((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1]);}

/* interp in k624 in k621 in k618 in k615 */
static void C_ccall f_1178(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr3r,(void*)f_1178r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_1178r(t0,t1,t2,t3);}}

static void C_ccall f_1178r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_trace("ChickenBridge.scm: 109  interpl");
t4=*((C_word*)lf[50]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t1,t2,t3);}

/* interpl in k624 in k621 in k618 in k615 */
static void C_ccall f_1083(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+6)){
C_save_and_reclaim((void*)tr4rv,(void*)f_1083r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest_vector(a,C_rest_count(0));
f_1083r(t0,t1,t2,t3,t4);}}

static void C_ccall f_1083r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word *a=C_alloc(6);
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_1087,a[2]=t1,a[3]=t2,a[4]=t3,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("ChickenBridge.scm: 109  error");
t6=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t5,lf[56],t3);}
else{
t6=t5;
f_1087(2,t6,(C_word)C_i_car(t3));}}

/* k1085 in interpl in k624 in k621 in k618 in k615 */
static void C_ccall f_1087(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1087,2,t0,t1);}
t2=t1;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_1090,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=t3,tmp=(C_word)a,a+=7,tmp);
t5=(C_word)C_i_cdr(((C_word*)t0)[4]);
if(C_truep((C_word)C_i_nullp(t5))){
C_trace("ChickenBridge.scm: 109  err");
t6=C_retrieve(lf[54]);
((C_proc4)C_retrieve_proc(t6))(4,t6,t4,lf[55],((C_word*)t0)[4]);}
else{
t6=t4;
f_1090(2,t6,(C_word)C_i_cadr(((C_word*)t0)[4]));}}

/* k1088 in k1085 in interpl in k624 in k621 in k618 in k615 */
static void C_ccall f_1090(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_1090,2,t0,t1);}
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
t13=C_set_block_item(t12,0,(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_1102,a[2]=((C_word*)t0)[4],a[3]=t12,a[4]=t9,a[5]=t7,a[6]=t3,a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[3],a[9]=t5,a[10]=lf[53],tmp=(C_word)a,a+=11,tmp));
t14=((C_word*)t12)[1];
f_1102(t14,((C_word*)t0)[2],t10);}

/* do200 in k1088 in k1085 in interpl in k624 in k621 in k618 in k615 */
static void C_fcall f_1102(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_1102,NULL,3,t0,t1,t2);}
t3=(C_word)C_i_nullp(t2);
t4=(C_truep(t3)?t3:(C_word)C_i_greaterp(((C_word*)((C_word*)t0)[9])[1],((C_word*)t0)[8]));
if(C_truep(t4)){
C_trace("ChickenBridge.scm: 109  tb:rescale");
f_628(t1,((C_word*)t0)[8],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[9])[1],((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[4]);}
else{
t5=C_mutate(((C_word *)((C_word*)t0)[7])+1,((C_word*)((C_word*)t0)[9])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[6])+1,((C_word*)((C_word*)t0)[5])[1]);
t7=(C_word)C_i_car(t2);
t8=C_mutate(((C_word *)((C_word*)t0)[9])+1,t7);
t9=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1124,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t10=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t10))){
C_trace("ChickenBridge.scm: 109  error");
t11=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t11))(4,t11,t9,lf[52],((C_word*)t0)[2]);}
else{
t11=(C_word)C_i_cadr(t2);
t12=C_mutate(((C_word *)((C_word*)t0)[5])+1,t11);
t13=t9;
f_1124(2,t13,t12);}}}

/* k1122 in do200 in k1088 in k1085 in interpl in k624 in k621 in k618 in k615 */
static void C_ccall f_1124(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cddr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_1102(t3,((C_word*)t0)[2],t2);}

/* hertz->keynum in k624 in k621 in k618 in k615 */
static void C_ccall f_1077(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1077,3,t0,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub75(t3,t4));}

/* keynum->pc in k624 in k621 in k618 in k615 */
static void C_ccall f_1071(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1071,3,t0,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub71(C_SCHEME_UNDEFINED,t3));}

/* keynum->hertz in k624 in k621 in k618 in k615 */
static void C_ccall f_1065(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1065,3,t0,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub66(t3,t4));}

/* scaler->cents in k624 in k621 in k618 in k615 */
static void C_ccall f_1059(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1059,3,t0,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub62(C_SCHEME_UNDEFINED,t3));}

/* cents->scaler in k624 in k621 in k618 in k615 */
static void C_ccall f_1053(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_1053,3,t0,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_fixnum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub57(t3,t4));}

/* rhythm->seconds in k624 in k621 in k618 in k615 */
static void C_ccall f_993(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+12)){
C_save_and_reclaim((void*)tr3r,(void*)f_993r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_993r(t0,t1,t2,t3);}}

static void C_ccall f_993r(C_word t0,C_word t1,C_word t2,C_word t3){
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
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_995,a[2]=t2,a[3]=lf[33],tmp=(C_word)a,a+=4,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1000,a[2]=t4,a[3]=lf[35],tmp=(C_word)a,a+=4,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1005,a[2]=t5,a[3]=lf[37],tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("def-tempo173181");
t7=t6;
f_1005(t7,t1);}
else{
t7=(C_word)C_i_car(t3);
t8=(C_word)C_i_cdr(t3);
if(C_truep((C_word)C_i_nullp(t8))){
C_trace("def-beat174179");
t9=t5;
f_1000(t9,t1,t7);}
else{
t9=(C_word)C_i_car(t8);
t10=(C_word)C_i_cdr(t8);
if(C_truep((C_word)C_i_nullp(t10))){
C_trace("body171176");
t11=t4;
f_995(t11,t1,t7,t9);}
else{
C_trace("##sys#error");
t11=*((C_word*)lf[38]+1);
((C_proc4)(void*)(*((C_word*)t11+1)))(4,t11,t1,lf[0],t10);}}}}

/* def-tempo173 in rhythm->seconds in k624 in k621 in k618 in k615 */
static void C_fcall f_1005(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1005,NULL,2,t0,t1);}
C_trace("def-beat174179");
t2=((C_word*)t0)[2];
f_1000(t2,t1,lf[36]);}

/* def-beat174 in rhythm->seconds in k624 in k621 in k618 in k615 */
static void C_fcall f_1000(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1000,NULL,3,t0,t1,t2);}
C_trace("body171176");
t3=((C_word*)t0)[2];
f_995(t3,t1,t2,lf[34]);}

/* body171 in rhythm->seconds in k624 in k621 in k618 in k615 */
static void C_fcall f_995(C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)trf_995,NULL,4,t0,t1,t2,t3);}
t4=((C_word*)t0)[2];
t5=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t6=(C_word)C_i_foreign_flonum_argumentp(t4);
t7=(C_word)C_i_foreign_flonum_argumentp(t2);
t8=(C_word)C_i_foreign_flonum_argumentp(t3);
t9=t1;
((C_proc2)(void*)(*((C_word*)t9+1)))(2,t9,(C_word)stub50(t5,t6,t7,t8));}

/* decimals in k624 in k621 in k618 in k615 */
static void C_ccall f_974(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr3rv,(void*)f_974r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest_vector(a,C_rest_count(0));
f_974r(t0,t1,t2,t3);}}

static void C_ccall f_974r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
if(C_truep((C_word)C_vemptyp(t3))){
C_trace("ChickenBridge.scm: 109  tb:decimals");
f_689(t1,t2,C_fix(3));}
else{
t4=(C_word)C_i_vector_ref(t3,C_fix(0));
C_trace("ChickenBridge.scm: 109  tb:decimals");
f_689(t1,t2,t4);}}

/* quantize in k624 in k621 in k618 in k615 */
static void C_ccall f_968(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_968,4,t0,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_flonum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub42(t4,t5,t6));}

/* int in k624 in k621 in k618 in k615 */
static void C_ccall f_962(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_962,3,t0,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub30(C_SCHEME_UNDEFINED,t3));}

/* discrete in k624 in k621 in k618 in k615 */
static void C_ccall f_880(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,...){
C_word tmp;
C_word t6;
va_list v;
C_word *a,c2=c;
C_save_rest(t5,c2,6);
if(c<6) C_bad_min_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+4)){
C_save_and_reclaim((void*)tr6r,(void*)f_880r,6,t0,t1,t2,t3,t4,t5);}
else{
a=C_alloc((c-6)*3);
t6=C_restore_rest(a,C_rest_count(0));
f_880r(t0,t1,t2,t3,t4,t5,t6);}}

static void C_ccall f_880r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
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
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_894,a[2]=t5,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_nullp(t6))){
t8=(C_word)C_i_length(t5);
C_trace("ChickenBridge.scm: 109  tb:discrete");
f_655(t7,t2,t3,t4,C_fix(0),t8,C_fix(1));}
else{
t8=(C_word)C_i_cdr(t6);
if(C_truep((C_word)C_i_nullp(t8))){
t9=(C_word)C_i_car(t6);
C_trace("ChickenBridge.scm: 109  tb:discrete");
f_655(t7,t2,t3,t4,C_fix(0),t9,C_fix(1));}
else{
t9=(C_word)C_i_car(t6);
t10=(C_word)C_i_cadr(t6);
C_trace("ChickenBridge.scm: 109  tb:discrete");
f_655(t7,t2,t3,t4,C_fix(0),t9,t10);}}}
else{
t7=(C_word)C_i_cdr(t6);
if(C_truep((C_word)C_i_nullp(t7))){
t8=(C_word)C_i_car(t6);
C_trace("ChickenBridge.scm: 109  tb:discrete");
f_655(t1,t2,t3,t4,t5,t8,C_fix(1));}
else{
t8=(C_word)C_i_car(t6);
t9=(C_word)C_i_cadr(t6);
C_trace("ChickenBridge.scm: 109  tb:discrete");
f_655(t1,t2,t3,t4,t5,t8,t9);}}}

/* k892 in discrete in k624 in k621 in k618 in k615 */
static void C_ccall f_894(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_i_list_ref(((C_word*)t0)[2],t1));}

/* rescale in k624 in k621 in k618 in k615 */
static void C_ccall f_861(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,...){
C_word tmp;
C_word t7;
va_list v;
C_word *a,c2=c;
C_save_rest(t6,c2,7);
if(c<7) C_bad_min_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr7rv,(void*)f_861r,7,t0,t1,t2,t3,t4,t5,t6);}
else{
a=C_alloc((c-7)*3);
t7=C_restore_rest_vector(a,C_rest_count(0));
f_861r(t0,t1,t2,t3,t4,t5,t6,t7);}}

static void C_ccall f_861r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
C_word tmp;
C_word t8;
C_word t9;
if(C_truep((C_word)C_vemptyp(t7))){
C_trace("ChickenBridge.scm: 109  tb:rescale");
f_628(t1,t2,t3,t4,t5,t6,C_fix(1));}
else{
t8=(C_word)C_i_vector_ref(t7,C_fix(0));
C_trace("ChickenBridge.scm: 109  tb:rescale");
f_628(t1,t2,t3,t4,t5,t6,t8);}}

/* tb:ranpoisson in k624 in k621 in k618 in k615 */
static void C_fcall f_848(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_848,NULL,2,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub142(C_SCHEME_UNDEFINED,t3));}

/* tb:rangamma in k624 in k621 in k618 in k615 */
static void C_fcall f_838(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_838,NULL,2,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub134(t3,t4));}

/* tb:ranbeta in k624 in k621 in k618 in k615 */
static void C_fcall f_827(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_827,NULL,3,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_flonum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub128(t4,t5,t6));}

/* tb:ranexp in k624 in k621 in k618 in k615 */
static void C_fcall f_820(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_820,NULL,2,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub122(t3,t4));}

/* tb:rangauss in k624 in k621 in k618 in k615 */
static void C_fcall f_809(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_809,NULL,3,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_flonum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub116(t4,t5,t6));}

/* tb:ranf in k624 in k621 in k618 in k615 */
static void C_fcall f_771(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_771,NULL,2,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub88(t3,t4));}

/* tb:rani in k624 in k621 in k618 in k615 */
static void C_fcall f_764(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_764,NULL,2,t1,t2);}
t3=(C_word)C_i_foreign_fixnum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub84(C_SCHEME_UNDEFINED,t3));}

/* tb:decimals in k624 in k621 in k618 in k615 */
static void C_fcall f_689(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_689,NULL,3,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_fixnum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub35(t4,t5,t6));}

/* tb:discrete in k624 in k621 in k618 in k615 */
static void C_fcall f_655(C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
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
C_save_and_reclaim((void*)trf_655,NULL,7,t1,t2,t3,t4,t5,t6,t7);}
t8=(C_word)C_i_foreign_flonum_argumentp(t2);
t9=(C_word)C_i_foreign_flonum_argumentp(t3);
t10=(C_word)C_i_foreign_flonum_argumentp(t4);
t11=(C_word)C_i_foreign_fixnum_argumentp(t5);
t12=(C_word)C_i_foreign_fixnum_argumentp(t6);
t13=(C_word)C_i_foreign_flonum_argumentp(t7);
t14=t1;
((C_proc2)(void*)(*((C_word*)t14+1)))(2,t14,(C_word)stub21(C_SCHEME_UNDEFINED,t8,t9,t10,t11,t12,t13));}

/* tb:rescale in k624 in k621 in k618 in k615 */
static void C_fcall f_628(C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
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
C_save_and_reclaim((void*)trf_628,NULL,7,t1,t2,t3,t4,t5,t6,t7);}
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
static C_PTABLE_ENTRY ptable[182] = {
{"toplevelChickenBridge.scm",(void*)C_grace_toplevel},
{"f_617ChickenBridge.scm",(void*)f_617},
{"f_620ChickenBridge.scm",(void*)f_620},
{"f_623ChickenBridge.scm",(void*)f_623},
{"f_626ChickenBridge.scm",(void*)f_626},
{"f_2072ChickenBridge.scm",(void*)f_2072},
{"f_3106ChickenBridge.scm",(void*)f_3106},
{"f_3153ChickenBridge.scm",(void*)f_3153},
{"f_3143ChickenBridge.scm",(void*)f_3143},
{"f_3110ChickenBridge.scm",(void*)f_3110},
{"f_2075ChickenBridge.scm",(void*)f_2075},
{"f_3100ChickenBridge.scm",(void*)f_3100},
{"f_2091ChickenBridge.scm",(void*)f_2091},
{"f_2304ChickenBridge.scm",(void*)f_2304},
{"f_2094ChickenBridge.scm",(void*)f_2094},
{"f_2097ChickenBridge.scm",(void*)f_2097},
{"f_2109ChickenBridge.scm",(void*)f_2109},
{"f_2157ChickenBridge.scm",(void*)f_2157},
{"f_2173ChickenBridge.scm",(void*)f_2173},
{"f_2183ChickenBridge.scm",(void*)f_2183},
{"f_2282ChickenBridge.scm",(void*)f_2282},
{"f_2278ChickenBridge.scm",(void*)f_2278},
{"f_2227ChickenBridge.scm",(void*)f_2227},
{"f_2233ChickenBridge.scm",(void*)f_2233},
{"f_2167ChickenBridge.scm",(void*)f_2167},
{"f_2112ChickenBridge.scm",(void*)f_2112},
{"f_2117ChickenBridge.scm",(void*)f_2117},
{"f_2130ChickenBridge.scm",(void*)f_2130},
{"f_2314ChickenBridge.scm",(void*)f_2314},
{"f_2365ChickenBridge.scm",(void*)f_2365},
{"f_2368ChickenBridge.scm",(void*)f_2368},
{"f_2371ChickenBridge.scm",(void*)f_2371},
{"f_2374ChickenBridge.scm",(void*)f_2374},
{"f_2377ChickenBridge.scm",(void*)f_2377},
{"f_2380ChickenBridge.scm",(void*)f_2380},
{"f_2383ChickenBridge.scm",(void*)f_2383},
{"f_2386ChickenBridge.scm",(void*)f_2386},
{"f_3094ChickenBridge.scm",(void*)f_3094},
{"f_2404ChickenBridge.scm",(void*)f_2404},
{"f_2407ChickenBridge.scm",(void*)f_2407},
{"f_2685ChickenBridge.scm",(void*)f_2685},
{"f_2793ChickenBridge.scm",(void*)f_2793},
{"f_2705ChickenBridge.scm",(void*)f_2705},
{"f_2714ChickenBridge.scm",(void*)f_2714},
{"f_2718ChickenBridge.scm",(void*)f_2718},
{"f_2722ChickenBridge.scm",(void*)f_2722},
{"f_2730ChickenBridge.scm",(void*)f_2730},
{"f_2726ChickenBridge.scm",(void*)f_2726},
{"f_2695ChickenBridge.scm",(void*)f_2695},
{"f_2410ChickenBridge.scm",(void*)f_2410},
{"f_2413ChickenBridge.scm",(void*)f_2413},
{"f_2416ChickenBridge.scm",(void*)f_2416},
{"f_2419ChickenBridge.scm",(void*)f_2419},
{"f_2422ChickenBridge.scm",(void*)f_2422},
{"f_2679ChickenBridge.scm",(void*)f_2679},
{"f_2578ChickenBridge.scm",(void*)f_2578},
{"f_2585ChickenBridge.scm",(void*)f_2585},
{"f_2587ChickenBridge.scm",(void*)f_2587},
{"f_2659ChickenBridge.scm",(void*)f_2659},
{"f_2611ChickenBridge.scm",(void*)f_2611},
{"f_2614ChickenBridge.scm",(void*)f_2614},
{"f_2635ChickenBridge.scm",(void*)f_2635},
{"f_2601ChickenBridge.scm",(void*)f_2601},
{"f_2425ChickenBridge.scm",(void*)f_2425},
{"f_2567ChickenBridge.scm",(void*)f_2567},
{"f_2555ChickenBridge.scm",(void*)f_2555},
{"f_2551ChickenBridge.scm",(void*)f_2551},
{"f_2432ChickenBridge.scm",(void*)f_2432},
{"f_2389ChickenBridge.scm",(void*)f_2389},
{"f_3092ChickenBridge.scm",(void*)f_3092},
{"f_2358ChickenBridge.scm",(void*)f_2358},
{"f_2352ChickenBridge.scm",(void*)f_2352},
{"f_2346ChickenBridge.scm",(void*)f_2346},
{"f_2340ChickenBridge.scm",(void*)f_2340},
{"f_2334ChickenBridge.scm",(void*)f_2334},
{"f_2328ChickenBridge.scm",(void*)f_2328},
{"f_2322ChickenBridge.scm",(void*)f_2322},
{"f_2316ChickenBridge.scm",(void*)f_2316},
{"f_1633ChickenBridge.scm",(void*)f_1633},
{"f_2077ChickenBridge.scm",(void*)f_2077},
{"f_2085ChickenBridge.scm",(void*)f_2085},
{"f_2061ChickenBridge.scm",(void*)f_2061},
{"f_1743ChickenBridge.scm",(void*)f_1743},
{"f_2065ChickenBridge.scm",(void*)f_2065},
{"f_2003ChickenBridge.scm",(void*)f_2003},
{"f_2021ChickenBridge.scm",(void*)f_2021},
{"f_2031ChickenBridge.scm",(void*)f_2031},
{"f_2007ChickenBridge.scm",(void*)f_2007},
{"f_1994ChickenBridge.scm",(void*)f_1994},
{"f_1721ChickenBridge.scm",(void*)f_1721},
{"f_1998ChickenBridge.scm",(void*)f_1998},
{"f_1988ChickenBridge.scm",(void*)f_1988},
{"f_1703ChickenBridge.scm",(void*)f_1703},
{"f_1979ChickenBridge.scm",(void*)f_1979},
{"f_1712ChickenBridge.scm",(void*)f_1712},
{"f_1983ChickenBridge.scm",(void*)f_1983},
{"f_1916ChickenBridge.scm",(void*)f_1916},
{"f_1941ChickenBridge.scm",(void*)f_1941},
{"f_1668ChickenBridge.scm",(void*)f_1668},
{"f_1929ChickenBridge.scm",(void*)f_1929},
{"f_1748ChickenBridge.scm",(void*)f_1748},
{"f_1867ChickenBridge.scm",(void*)f_1867},
{"f_1862ChickenBridge.scm",(void*)f_1862},
{"f_1750ChickenBridge.scm",(void*)f_1750},
{"f_1857ChickenBridge.scm",(void*)f_1857},
{"f_1861ChickenBridge.scm",(void*)f_1861},
{"f_1853ChickenBridge.scm",(void*)f_1853},
{"f_1821ChickenBridge.scm",(void*)f_1821},
{"f_1846ChickenBridge.scm",(void*)f_1846},
{"f_1850ChickenBridge.scm",(void*)f_1850},
{"f_1831ChickenBridge.scm",(void*)f_1831},
{"f_1810ChickenBridge.scm",(void*)f_1810},
{"f_1780ChickenBridge.scm",(void*)f_1780},
{"f_1752ChickenBridge.scm",(void*)f_1752},
{"f_1726ChickenBridge.scm",(void*)f_1726},
{"f_1730ChickenBridge.scm",(void*)f_1730},
{"f_1682ChickenBridge.scm",(void*)f_1682},
{"f_1686ChickenBridge.scm",(void*)f_1686},
{"f_1673ChickenBridge.scm",(void*)f_1673},
{"f_1677ChickenBridge.scm",(void*)f_1677},
{"f_1661ChickenBridge.scm",(void*)f_1661},
{"f_1658ChickenBridge.scm",(void*)f_1658},
{"f_1615ChickenBridge.scm",(void*)f_1615},
{"f_1620ChickenBridge.scm",(void*)f_1620},
{"f_1601ChickenBridge.scm",(void*)f_1601},
{"f_1606ChickenBridge.scm",(void*)f_1606},
{"f_1595ChickenBridge.scm",(void*)f_1595},
{"f_1589ChickenBridge.scm",(void*)f_1589},
{"f_1570ChickenBridge.scm",(void*)f_1570},
{"f_1551ChickenBridge.scm",(void*)f_1551},
{"f_1545ChickenBridge.scm",(void*)f_1545},
{"f_1505ChickenBridge.scm",(void*)f_1505},
{"f_1486ChickenBridge.scm",(void*)f_1486},
{"f_1442ChickenBridge.scm",(void*)f_1442},
{"f_1436ChickenBridge.scm",(void*)f_1436},
{"f_1430ChickenBridge.scm",(void*)f_1430},
{"f_1424ChickenBridge.scm",(void*)f_1424},
{"f_1418ChickenBridge.scm",(void*)f_1418},
{"f_1395ChickenBridge.scm",(void*)f_1395},
{"f_1412ChickenBridge.scm",(void*)f_1412},
{"f_1337ChickenBridge.scm",(void*)f_1337},
{"f_1389ChickenBridge.scm",(void*)f_1389},
{"f_1373ChickenBridge.scm",(void*)f_1373},
{"f_1354ChickenBridge.scm",(void*)f_1354},
{"f_1249ChickenBridge.scm",(void*)f_1249},
{"f_1295ChickenBridge.scm",(void*)f_1295},
{"f_1243ChickenBridge.scm",(void*)f_1243},
{"f_1184ChickenBridge.scm",(void*)f_1184},
{"f_1197ChickenBridge.scm",(void*)f_1197},
{"f_1233ChickenBridge.scm",(void*)f_1233},
{"f_1178ChickenBridge.scm",(void*)f_1178},
{"f_1083ChickenBridge.scm",(void*)f_1083},
{"f_1087ChickenBridge.scm",(void*)f_1087},
{"f_1090ChickenBridge.scm",(void*)f_1090},
{"f_1102ChickenBridge.scm",(void*)f_1102},
{"f_1124ChickenBridge.scm",(void*)f_1124},
{"f_1077ChickenBridge.scm",(void*)f_1077},
{"f_1071ChickenBridge.scm",(void*)f_1071},
{"f_1065ChickenBridge.scm",(void*)f_1065},
{"f_1059ChickenBridge.scm",(void*)f_1059},
{"f_1053ChickenBridge.scm",(void*)f_1053},
{"f_993ChickenBridge.scm",(void*)f_993},
{"f_1005ChickenBridge.scm",(void*)f_1005},
{"f_1000ChickenBridge.scm",(void*)f_1000},
{"f_995ChickenBridge.scm",(void*)f_995},
{"f_974ChickenBridge.scm",(void*)f_974},
{"f_968ChickenBridge.scm",(void*)f_968},
{"f_962ChickenBridge.scm",(void*)f_962},
{"f_880ChickenBridge.scm",(void*)f_880},
{"f_894ChickenBridge.scm",(void*)f_894},
{"f_861ChickenBridge.scm",(void*)f_861},
{"f_848ChickenBridge.scm",(void*)f_848},
{"f_838ChickenBridge.scm",(void*)f_838},
{"f_827ChickenBridge.scm",(void*)f_827},
{"f_820ChickenBridge.scm",(void*)f_820},
{"f_809ChickenBridge.scm",(void*)f_809},
{"f_771ChickenBridge.scm",(void*)f_771},
{"f_764ChickenBridge.scm",(void*)f_764},
{"f_689ChickenBridge.scm",(void*)f_689},
{"f_655ChickenBridge.scm",(void*)f_655},
{"f_628ChickenBridge.scm",(void*)f_628},
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
