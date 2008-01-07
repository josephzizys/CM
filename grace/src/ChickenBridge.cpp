/* Generated from ChickenBridge.scm by the CHICKEN compiler
   http://www.call-with-current-continuation.org
   2008-01-07 06:31
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
#include "Syntax.h"
#include "Midi.h"
#include <juce.h>

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

//void print_current_directory() {
//  String s=File::getCurrentWorkingDirectory().getFullPathName().quoted() + T("\n");
//  ((GraceApp *)GraceApp::getInstance())->getConsole()->postConsoleTextMessage(s, ConsoleMessage::TEXT, true);
//}

char *get_current_directory() {
  return (char *)File::getCurrentWorkingDirectory().getFullPathName().toUTF8();
}

void set_current_directory (char *path) {
  File dir=File(String(path));
  if ( dir.isDirectory() ) {
    dir.setAsCurrentWorkingDirectory();
    //print_working_directory();
  }
  else {
    String s=T(">>> Error: ") + dir.getFullPathName().quoted() + T(" is not a directory.\n");
    ((GraceApp *)GraceApp::getInstance())->getConsole()->postConsoleTextMessage(s, ConsoleMessage::ERROR, true);
  }			 
}

void load_sal_file(char *path) {
  SalSyntax::getInstance()->loadFile( String(path) );  
}

//INput Hook Code
void set_input_hook( C_word proc, unsigned int chanmask, unsigned int msgfilt )
{
 ((GraceApp *)GraceApp::getInstance())->schemeProcess->setInputHook( proc, chanmask, msgfilt );
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

static C_TLS C_word lf[645];


/* from k7275 */
static C_word C_fcall stub1623(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2) C_regparm;
C_regparm static C_word C_fcall stub1623(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
C_word t0=(C_word )(C_a0);
unsigned int t1=(unsigned int )C_unfix(C_a1);
unsigned int t2=(unsigned int )C_unfix(C_a2);
set_input_hook(t0,t1,t2);
return C_r;}

/* from k6613 */
static C_word C_fcall stub1488(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub1488(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
load_sal_file(t0);
return C_r;}

/* from k6598 in hush in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
C_noret_decl(stub1482)
static void C_ccall stub1482(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub1482(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_hush();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k6592 */
C_noret_decl(stub1477)
static void C_ccall stub1477(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0) C_noret;
static void C_ccall stub1477(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_unfix(C_a0);
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_stop(t0);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k6576 in cont in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
C_noret_decl(stub1472)
static void C_ccall stub1472(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub1472(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_cont();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k6567 in pause in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
C_noret_decl(stub1468)
static void C_ccall stub1468(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub1468(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_pause();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k6558 in paused? in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
C_noret_decl(stub1464)
static void C_ccall stub1464(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub1464(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
C_r=C_mk_bool(scheduler_is_paused());
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k6552 */
C_noret_decl(stub1457)
static void C_ccall stub1457(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2) C_noret;
static void C_ccall stub1457(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
C_word t0=(C_word )(C_a0);
double t1=(double )C_c_double(C_a1);
int t2=(int )C_unfix(C_a2);
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_sprout(t0,t1,t2);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k6532 in scheduler-set-time-milliseconds in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
C_noret_decl(stub1449)
static void C_ccall stub1449(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0) C_noret;
static void C_ccall stub1449(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_truep(C_a0);
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_set_time_milliseconds(t0);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k6523 in time-format in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
C_noret_decl(stub1444)
static void C_ccall stub1444(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub1444(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
C_r=C_mk_bool(scheduler_is_time_milliseconds());
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from current-time-seconds in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
#define return(x) C_cblock C_r = (C_flonum(&C_a,(x))); goto C_ret; C_cblockend
static C_word C_fcall stub1441(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub1441(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
 C_return( (Time::getMillisecondCounterHiRes() / 1000.0) );
C_ret:
#undef return

return C_r;}

/* from current-time-milliseconds in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
#define return(x) C_cblock C_r = (C_flonum(&C_a,(x))); goto C_ret; C_cblockend
static C_word C_fcall stub1438(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub1438(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
 C_return( Time::getMillisecondCounterHiRes());
C_ret:
#undef return

return C_r;}

/* from k6511 */
C_noret_decl(stub1429)
static void C_ccall stub1429(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2,C_word C_a3,C_word C_a4) C_noret;
static void C_ccall stub1429(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2,C_word C_a3,C_word C_a4){
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

/* from k6475 in print-error in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static C_word C_fcall stub1419(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub1419(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_error(t0);
return C_r;}

/* from k6461 in print-message in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static C_word C_fcall stub1413(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub1413(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_message(t0);
return C_r;}

/* from k6441 */
static C_word C_fcall stub1407(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub1407(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
set_current_directory(t0);
return C_r;}

/* from f_6423 in current-directory in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static C_word C_fcall stub1402(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub1402(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
C_r=C_mpointer(&C_a,(void*)get_current_directory());
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

/* from k1974 */
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

/* from k1964 */
static C_word C_fcall stub134(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub134(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::rangamma(t0));
return C_r;}

/* from k1957 */
static C_word C_fcall stub128(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub128(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
C_r=C_flonum(&C_a,Toolbox::ranbeta(t0,t1));
return C_r;}

/* from k1946 */
static C_word C_fcall stub122(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub122(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::ranexp(t0));
return C_r;}

/* from k1939 */
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

/* from k1919 */
static C_word C_fcall stub100(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub100(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
C_r=C_flonum(&C_a,Toolbox::ran(t0,t1));
return C_r;}

/* from k1908 */
static C_word C_fcall stub94(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub94(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_unfix(C_a0);
int t1=(int )C_unfix(C_a1);
C_r=C_fix((C_word)Toolbox::ran(t0,t1));
return C_r;}

/* from k1897 */
static C_word C_fcall stub88(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub88(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::ran(t0));
return C_r;}

/* from k1890 */
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

/* from k1880 */
static C_word C_fcall stub75(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub75(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::hertz_to_keynum(t0));
return C_r;}

/* from k1873 */
static C_word C_fcall stub71(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub71(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_fix((C_word)Toolbox::keynum_to_pc(t0));
return C_r;}

/* from k1866 */
static C_word C_fcall stub66(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub66(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::keynum_to_hertz(t0));
return C_r;}

/* from k1859 */
static C_word C_fcall stub62(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub62(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_fix((C_word)Toolbox::scaler_to_cents(t0));
return C_r;}

/* from k1852 */
static C_word C_fcall stub57(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub57(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_unfix(C_a0);
C_r=C_flonum(&C_a,Toolbox::cents_to_scaler(t0));
return C_r;}

/* from k1845 */
static C_word C_fcall stub50(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2) C_regparm;
C_regparm static C_word C_fcall stub50(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
float t2=(float )C_c_double(C_a2);
C_r=C_flonum(&C_a,Toolbox::rhythm_to_seconds(t0,t1,t2));
return C_r;}

/* from k1830 */
static C_word C_fcall stub42(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub42(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
C_r=C_flonum(&C_a,Toolbox::quantize(t0,t1));
return C_r;}

/* from k1819 */
static C_word C_fcall stub35(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub35(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
int t1=(int )C_unfix(C_a1);
C_r=C_flonum(&C_a,Toolbox::decimals(t0,t1));
return C_r;}

/* from k1808 */
static C_word C_fcall stub30(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub30(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_fix((C_word)Toolbox::float_to_fixnum(t0));
return C_r;}

/* from k1801 */
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

/* from k1774 */
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
C_noret_decl(f_1740)
static void C_ccall f_1740(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1743)
static void C_ccall f_1743(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1746)
static void C_ccall f_1746(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1749)
static void C_ccall f_1749(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12106)
static void C_ccall f_12106(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_12114)
static void C_ccall f_12114(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12118)
static void C_ccall f_12118(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2791)
static void C_ccall f_2791(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2842)
static void C_ccall f_2842(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12096)
static void C_ccall f_12096(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_12104)
static void C_ccall f_12104(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2947)
static void C_ccall f_2947(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12082)
static void C_ccall f_12082(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_12090)
static void C_ccall f_12090(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12094)
static void C_ccall f_12094(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3140)
static void C_ccall f_3140(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12056)
static void C_ccall f_12056(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_12060)
static void C_ccall f_12060(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12066)
static void C_ccall f_12066(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12077)
static void C_ccall f_12077(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12073)
static void C_ccall f_12073(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3209)
static void C_ccall f_3209(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12034)
static void C_ccall f_12034(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4454)
static void C_ccall f_4454(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12014)
static void C_ccall f_12014(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4457)
static void C_ccall f_4457(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11974)
static void C_ccall f_11974(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4460)
static void C_ccall f_4460(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11880)
static void C_ccall f_11880(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_11884)
static void C_ccall f_11884(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11887)
static void C_ccall f_11887(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11905)
static void C_ccall f_11905(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11908)
static void C_ccall f_11908(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11939)
static void C_ccall f_11939(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11911)
static void C_fcall f_11911(C_word t0,C_word t1) C_noret;
C_noret_decl(f_11917)
static void C_ccall f_11917(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11870)
static void C_ccall f_11870(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_11864)
static void C_ccall f_11864(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4463)
static void C_ccall f_4463(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11772)
static void C_ccall f_11772(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11774)
static void C_ccall f_11774(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_11778)
static void C_ccall f_11778(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11781)
static void C_ccall f_11781(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11784)
static void C_ccall f_11784(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11824)
static void C_ccall f_11824(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11816)
static void C_ccall f_11816(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11787)
static void C_ccall f_11787(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11790)
static void C_ccall f_11790(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11793)
static void C_ccall f_11793(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11764)
static void C_ccall f_11764(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4466)
static void C_ccall f_4466(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11736)
static void C_ccall f_11736(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4469)
static void C_ccall f_4469(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11700)
static void C_ccall f_11700(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_11712)
static void C_ccall f_11712(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11708)
static void C_ccall f_11708(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11682)
static void C_ccall f_11682(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_11676)
static void C_ccall f_11676(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4472)
static void C_ccall f_4472(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11590)
static void C_ccall f_11590(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_11594)
static void C_ccall f_11594(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11597)
static void C_ccall f_11597(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11600)
static void C_ccall f_11600(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11613)
static void C_ccall f_11613(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11559)
static void C_ccall f_11559(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_11563)
static void C_ccall f_11563(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11578)
static void C_ccall f_11578(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11553)
static void C_ccall f_11553(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4475)
static void C_ccall f_4475(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11439)
static void C_ccall f_11439(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_11455)
static void C_ccall f_11455(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11466)
static void C_ccall f_11466(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11433)
static void C_ccall f_11433(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4531)
static void C_ccall f_4531(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11300)
static void C_ccall f_11300(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_11323)
static void C_ccall f_11323(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11320)
static void C_ccall f_11320(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11294)
static void C_ccall f_11294(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4534)
static void C_ccall f_4534(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11148)
static void C_ccall f_11148(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_11166)
static void C_ccall f_11166(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11175)
static void C_ccall f_11175(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11142)
static void C_ccall f_11142(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4537)
static void C_ccall f_4537(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11095)
static void C_ccall f_11095(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_11099)
static void C_ccall f_11099(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11102)
static void C_ccall f_11102(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11118)
static void C_ccall f_11118(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11077)
static void C_ccall f_11077(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_11071)
static void C_ccall f_11071(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4540)
static void C_ccall f_4540(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10995)
static void C_ccall f_10995(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4679)
static void C_ccall f_4679(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10921)
static void C_ccall f_10921(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_10928)
static void C_ccall f_10928(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10915)
static void C_ccall f_10915(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4682)
static void C_ccall f_4682(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10811)
static void C_ccall f_10811(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_10819)
static void C_ccall f_10819(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10785)
static void C_ccall f_10785(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_10802)
static void C_ccall f_10802(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10793)
static void C_fcall f_10793(C_word t0,C_word t1) C_noret;
C_noret_decl(f_10779)
static void C_ccall f_10779(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4685)
static void C_ccall f_4685(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10735)
static void C_ccall f_10735(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4688)
static void C_ccall f_4688(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10653)
static void C_ccall f_10653(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_10664)
static void C_ccall f_10664(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10666)
static void C_fcall f_10666(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_10695)
static void C_ccall f_10695(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10631)
static void C_ccall f_10631(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_10647)
static void C_ccall f_10647(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10625)
static void C_ccall f_10625(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4691)
static void C_ccall f_4691(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10549)
static void C_ccall f_10549(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_10553)
static void C_ccall f_10553(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10585)
static void C_ccall f_10585(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10566)
static void C_ccall f_10566(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10570)
static void C_ccall f_10570(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10522)
static void C_ccall f_10522(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_10526)
static void C_ccall f_10526(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10516)
static void C_ccall f_10516(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4694)
static void C_ccall f_4694(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10384)
static void C_ccall f_10384(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_10424)
static void C_ccall f_10424(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10388)
static void C_ccall f_10388(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10404)
static void C_ccall f_10404(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_10404)
static void C_ccall f_10404r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_10416)
static void C_ccall f_10416(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10420)
static void C_ccall f_10420(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10412)
static void C_ccall f_10412(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10323)
static void C_ccall f_10323(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_10370)
static void C_ccall f_10370(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10330)
static void C_fcall f_10330(C_word t0,C_word t1) C_noret;
C_noret_decl(f_10341)
static void C_ccall f_10341(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10317)
static void C_ccall f_10317(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4697)
static void C_ccall f_4697(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10297)
static void C_ccall f_10297(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_10291)
static void C_ccall f_10291(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4700)
static void C_ccall f_4700(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10271)
static void C_ccall f_10271(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10275)
static void C_ccall f_10275(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10263)
static void C_ccall f_10263(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4703)
static void C_ccall f_4703(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10243)
static void C_ccall f_10243(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10247)
static void C_ccall f_10247(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10235)
static void C_ccall f_10235(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4706)
static void C_ccall f_4706(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10215)
static void C_ccall f_10215(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10219)
static void C_ccall f_10219(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10207)
static void C_ccall f_10207(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4709)
static void C_ccall f_4709(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10187)
static void C_ccall f_10187(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10191)
static void C_ccall f_10191(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10179)
static void C_ccall f_10179(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4712)
static void C_ccall f_4712(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10078)
static void C_ccall f_10078(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_10048)
static void C_ccall f_10048(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_10072)
static void C_ccall f_10072(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10042)
static void C_ccall f_10042(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4715)
static void C_ccall f_4715(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9992)
static void C_ccall f_9992(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9994)
static void C_ccall f_9994(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_9998)
static void C_ccall f_9998(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10026)
static void C_ccall f_10026(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10018)
static void C_ccall f_10018(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10014)
static void C_ccall f_10014(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10001)
static void C_ccall f_10001(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9984)
static void C_ccall f_9984(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4718)
static void C_ccall f_4718(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9931)
static void C_ccall f_9931(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9933)
static void C_ccall f_9933(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_9937)
static void C_ccall f_9937(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9968)
static void C_ccall f_9968(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9960)
static void C_ccall f_9960(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9956)
static void C_ccall f_9956(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9940)
static void C_ccall f_9940(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9943)
static void C_ccall f_9943(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9923)
static void C_ccall f_9923(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4721)
static void C_ccall f_4721(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9873)
static void C_ccall f_9873(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_9887)
static void C_ccall f_9887(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9879)
static void C_ccall f_9879(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_9838)
static void C_ccall f_9838(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_9871)
static void C_ccall f_9871(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9832)
static void C_ccall f_9832(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4724)
static void C_ccall f_4724(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9779)
static void C_ccall f_9779(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_9783)
static void C_ccall f_9783(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9796)
static void C_ccall f_9796(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9788)
static void C_ccall f_9788(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_9736)
static void C_ccall f_9736(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_9769)
static void C_ccall f_9769(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9730)
static void C_ccall f_9730(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4727)
static void C_ccall f_4727(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9650)
static void C_ccall f_9650(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_9644)
static void C_ccall f_9644(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4730)
static void C_ccall f_4730(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9413)
static void C_ccall f_9413(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_9417)
static void C_ccall f_9417(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9425)
static void C_fcall f_9425(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_9448)
static void C_ccall f_9448(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9451)
static void C_ccall f_9451(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9454)
static void C_ccall f_9454(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9457)
static void C_ccall f_9457(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9517)
static void C_ccall f_9517(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9524)
static void C_ccall f_9524(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9534)
static void C_ccall f_9534(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9544)
static void C_ccall f_9544(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9558)
static void C_ccall f_9558(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9568)
static void C_ccall f_9568(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9578)
static void C_ccall f_9578(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9588)
static void C_ccall f_9588(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9460)
static void C_fcall f_9460(C_word t0,C_word t1) C_noret;
C_noret_decl(f_9484)
static void C_fcall f_9484(C_word t0,C_word t1) C_noret;
C_noret_decl(f_9463)
static void C_fcall f_9463(C_word t0,C_word t1) C_noret;
C_noret_decl(f_9370)
static void C_ccall f_9370(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_9403)
static void C_ccall f_9403(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9364)
static void C_ccall f_9364(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4733)
static void C_ccall f_4733(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9282)
static void C_ccall f_9282(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_9286)
static void C_ccall f_9286(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9292)
static void C_ccall f_9292(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9312)
static void C_ccall f_9312(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9256)
static void C_ccall f_9256(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_9266)
static void C_fcall f_9266(C_word t0,C_word t1) C_noret;
C_noret_decl(f_9250)
static void C_ccall f_9250(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4736)
static void C_ccall f_4736(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9127)
static void C_ccall f_9127(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_9131)
static void C_ccall f_9131(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9059)
static void C_ccall f_9059(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_9078)
static void C_ccall f_9078(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9113)
static void C_ccall f_9113(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9084)
static void C_fcall f_9084(C_word t0,C_word t1) C_noret;
C_noret_decl(f_9088)
static void C_ccall f_9088(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9102)
static void C_ccall f_9102(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9091)
static void C_fcall f_9091(C_word t0,C_word t1) C_noret;
C_noret_decl(f_9072)
static void C_fcall f_9072(C_word t0,C_word t1) C_noret;
C_noret_decl(f_9053)
static void C_ccall f_9053(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4739)
static void C_ccall f_4739(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8781)
static void C_ccall f_8781(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5262)
static void C_ccall f_5262(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8733)
static void C_ccall f_8733(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8725)
static void C_ccall f_8725(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5265)
static void C_ccall f_5265(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8605)
static void C_ccall f_8605(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_5271)
static void C_ccall f_5271(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5743)
static void C_ccall f_5743(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5777)
static void C_ccall f_5777(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5769)
static void C_ccall f_5769(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5765)
static void C_ccall f_5765(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5750)
static void C_ccall f_5750(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5754)
static void C_ccall f_5754(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5747)
static void C_ccall f_5747(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5289)
static void C_fcall f_5289(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5736)
static void C_ccall f_5736(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5732)
static void C_ccall f_5732(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5296)
static void C_fcall f_5296(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5607)
static void C_fcall f_5607(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_5628)
static void C_ccall f_5628(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5630)
static void C_fcall f_5630(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_5644)
static void C_ccall f_5644(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5697)
static void C_ccall f_5697(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5647)
static void C_fcall f_5647(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5682)
static void C_ccall f_5682(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5650)
static void C_fcall f_5650(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5663)
static void C_ccall f_5663(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5675)
static void C_ccall f_5675(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5667)
static void C_ccall f_5667(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5653)
static void C_fcall f_5653(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5617)
static void C_ccall f_5617(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5299)
static void C_ccall f_5299(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5571)
static void C_fcall f_5571(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_5597)
static void C_ccall f_5597(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5582)
static void C_ccall f_5582(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5302)
static void C_ccall f_5302(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5306)
static void C_ccall f_5306(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5515)
static void C_fcall f_5515(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_5525)
static void C_ccall f_5525(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5528)
static void C_ccall f_5528(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5549)
static void C_ccall f_5549(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5531)
static void C_fcall f_5531(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5535)
static void C_ccall f_5535(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5309)
static void C_ccall f_5309(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5312)
static void C_fcall f_5312(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5478)
static void C_ccall f_5478(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5486)
static void C_ccall f_5486(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5482)
static void C_ccall f_5482(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5315)
static void C_fcall f_5315(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5343)
static void C_ccall f_5343(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5346)
static void C_ccall f_5346(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5349)
static void C_ccall f_5349(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5352)
static void C_ccall f_5352(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5411)
static void C_ccall f_5411(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8559)
static void C_ccall f_8559(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_8575)
static void C_ccall f_8575(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8578)
static void C_ccall f_8578(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8581)
static void C_fcall f_8581(C_word t0,C_word t1) C_noret;
C_noret_decl(f_8584)
static void C_fcall f_8584(C_word t0,C_word t1) C_noret;
C_noret_decl(f_8595)
static void C_ccall f_8595(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8553)
static void C_ccall f_8553(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5784)
static void C_ccall f_5784(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8414)
static void C_ccall f_8414(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_8453)
static void C_ccall f_8453(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8427)
static void C_fcall f_8427(C_word t0,C_word t1) C_noret;
C_noret_decl(f_8408)
static void C_ccall f_8408(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5787)
static void C_ccall f_5787(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7996)
static void C_ccall f_7996(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_8000)
static void C_ccall f_8000(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8012)
static void C_ccall f_8012(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8070)
static void C_ccall f_8070(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8073)
static void C_ccall f_8073(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8076)
static void C_ccall f_8076(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8288)
static void C_ccall f_8288(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8226)
static void C_ccall f_8226(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8260)
static void C_ccall f_8260(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8235)
static void C_fcall f_8235(C_word t0,C_word t1) C_noret;
C_noret_decl(f_8246)
static void C_ccall f_8246(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8242)
static void C_ccall f_8242(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8085)
static void C_fcall f_8085(C_word t0,C_word t1) C_noret;
C_noret_decl(f_8163)
static void C_ccall f_8163(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8204)
static void C_ccall f_8204(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8208)
static void C_ccall f_8208(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8212)
static void C_ccall f_8212(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8167)
static void C_ccall f_8167(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8171)
static void C_ccall f_8171(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8198)
static void C_ccall f_8198(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8174)
static void C_fcall f_8174(C_word t0,C_word t1) C_noret;
C_noret_decl(f_8088)
static void C_fcall f_8088(C_word t0,C_word t1) C_noret;
C_noret_decl(f_8160)
static void C_ccall f_8160(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8102)
static void C_ccall f_8102(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8104)
static void C_fcall f_8104(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_8152)
static void C_ccall f_8152(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8123)
static void C_ccall f_8123(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8140)
static void C_ccall f_8140(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8126)
static void C_fcall f_8126(C_word t0,C_word t1) C_noret;
C_noret_decl(f_8119)
static void C_ccall f_8119(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8091)
static void C_ccall f_8091(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8021)
static void C_fcall f_8021(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_8031)
static void C_ccall f_8031(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8037)
static void C_ccall f_8037(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8009)
static void C_ccall f_8009(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7957)
static void C_ccall f_7957(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_7974)
static void C_ccall f_7974(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7990)
static void C_ccall f_7990(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7968)
static void C_fcall f_7968(C_word t0,C_word t1) C_noret;
C_noret_decl(f_7951)
static void C_ccall f_7951(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5790)
static void C_ccall f_5790(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7875)
static void C_ccall f_7875(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5793)
static void C_ccall f_5793(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7851)
static void C_ccall f_7851(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_7863)
static void C_ccall f_7863(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7859)
static void C_ccall f_7859(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7837)
static void C_ccall f_7837(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_7845)
static void C_ccall f_7845(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7831)
static void C_ccall f_7831(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5796)
static void C_ccall f_5796(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6948)
static void C_ccall f_6948(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7777)
static void C_ccall f_7777(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_7824)
static void C_ccall f_7824(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7814)
static void C_ccall f_7814(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7781)
static void C_ccall f_7781(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6951)
static void C_ccall f_6951(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7771)
static void C_ccall f_7771(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_7771)
static void C_ccall f_7771r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_7224)
static void C_ccall f_7224(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7280)
static void C_ccall f_7280(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7283)
static void C_ccall f_7283(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7286)
static void C_ccall f_7286(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7289)
static void C_ccall f_7289(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7292)
static void C_ccall f_7292(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7295)
static void C_ccall f_7295(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7298)
static void C_ccall f_7298(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7301)
static void C_ccall f_7301(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7765)
static void C_ccall f_7765(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_7765)
static void C_ccall f_7765r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_7319)
static void C_ccall f_7319(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7322)
static void C_ccall f_7322(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7600)
static void C_fcall f_7600(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_7708)
static void C_ccall f_7708(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7620)
static void C_fcall f_7620(C_word t0,C_word t1) C_noret;
C_noret_decl(f_7629)
static void C_fcall f_7629(C_word t0,C_word t1) C_noret;
C_noret_decl(f_7633)
static void C_ccall f_7633(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7637)
static void C_ccall f_7637(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7645)
static void C_fcall f_7645(C_word t0,C_word t1) C_noret;
C_noret_decl(f_7641)
static void C_ccall f_7641(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7610)
static void C_ccall f_7610(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7325)
static void C_ccall f_7325(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7328)
static void C_ccall f_7328(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7331)
static void C_ccall f_7331(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7334)
static void C_ccall f_7334(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7337)
static void C_ccall f_7337(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7594)
static void C_ccall f_7594(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7493)
static void C_fcall f_7493(C_word t0,C_word t1) C_noret;
C_noret_decl(f_7500)
static void C_ccall f_7500(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7502)
static void C_fcall f_7502(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_7574)
static void C_ccall f_7574(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7526)
static void C_fcall f_7526(C_word t0,C_word t1) C_noret;
C_noret_decl(f_7529)
static void C_ccall f_7529(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7550)
static void C_ccall f_7550(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7516)
static void C_ccall f_7516(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7340)
static void C_ccall f_7340(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7482)
static void C_ccall f_7482(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7470)
static void C_ccall f_7470(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7466)
static void C_ccall f_7466(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7347)
static void C_fcall f_7347(C_word t0,C_word t1) C_noret;
C_noret_decl(f_7304)
static void C_ccall f_7304(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7763)
static void C_ccall f_7763(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7268)
static void C_ccall f_7268(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_7262)
static void C_ccall f_7262(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_7256)
static void C_ccall f_7256(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7250)
static void C_ccall f_7250(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_7244)
static void C_ccall f_7244(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_7238)
static void C_ccall f_7238(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_7232)
static void C_ccall f_7232(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_7226)
static void C_ccall f_7226(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_6490)
static void C_ccall f_6490(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6953)
static void C_ccall f_6953(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_6963)
static void C_ccall f_6963(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7194)
static void C_ccall f_7194(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6966)
static void C_ccall f_6966(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6969)
static void C_ccall f_6969(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6981)
static void C_ccall f_6981(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7029)
static void C_fcall f_7029(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_7045)
static void C_ccall f_7045(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7055)
static void C_ccall f_7055(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7172)
static void C_ccall f_7172(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7160)
static void C_ccall f_7160(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_7158)
static void C_ccall f_7158(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7145)
static void C_ccall f_7145(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7099)
static void C_ccall f_7099(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7126)
static void C_ccall f_7126(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7105)
static void C_ccall f_7105(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7039)
static void C_fcall f_7039(C_word t0,C_word t1) C_noret;
C_noret_decl(f_6984)
static void C_ccall f_6984(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6989)
static void C_fcall f_6989(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_7002)
static void C_fcall f_7002(C_word t0,C_word t1) C_noret;
C_noret_decl(f_7211)
static void C_ccall f_7211(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_7202)
static void C_ccall f_7202(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_7210)
static void C_ccall f_7210(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7213)
static void C_ccall f_7213(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_7213)
static void C_ccall f_7213r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_7221)
static void C_ccall f_7221(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6937)
static void C_ccall f_6937(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6600)
static void C_ccall f_6600(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6941)
static void C_ccall f_6941(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6879)
static void C_ccall f_6879(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_6879)
static void C_ccall f_6879r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_6897)
static void C_fcall f_6897(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6907)
static void C_ccall f_6907(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6883)
static void C_ccall f_6883(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6870)
static void C_ccall f_6870(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6578)
static void C_ccall f_6578(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6874)
static void C_ccall f_6874(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6864)
static void C_ccall f_6864(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6560)
static void C_ccall f_6560(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6855)
static void C_ccall f_6855(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6569)
static void C_ccall f_6569(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6859)
static void C_ccall f_6859(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6792)
static void C_ccall f_6792(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_6792)
static void C_ccall f_6792r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_6817)
static void C_fcall f_6817(C_word t0,C_word t1) C_noret;
C_noret_decl(f_6525)
static void C_ccall f_6525(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6805)
static void C_ccall f_6805(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6624)
static void C_ccall f_6624(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_6624)
static void C_ccall f_6624r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_6743)
static void C_fcall f_6743(C_word t0,C_word t1) C_noret;
C_noret_decl(f_6738)
static void C_fcall f_6738(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6626)
static void C_fcall f_6626(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_6733)
static void C_ccall f_6733(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6737)
static void C_ccall f_6737(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6729)
static void C_ccall f_6729(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6697)
static void C_fcall f_6697(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6722)
static void C_ccall f_6722(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6726)
static void C_ccall f_6726(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6707)
static void C_ccall f_6707(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6686)
static void C_ccall f_6686(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6656)
static void C_fcall f_6656(C_word t0,C_word t1) C_noret;
C_noret_decl(f_6628)
static void C_fcall f_6628(C_word t0,C_word t1) C_noret;
C_noret_decl(f_6605)
static void C_ccall f_6605(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6610)
static void C_ccall f_6610(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6615)
static void C_ccall f_6615(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6583)
static void C_fcall f_6583(C_word t0,C_word t1) C_noret;
C_noret_decl(f_6587)
static void C_ccall f_6587(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6539)
static void C_fcall f_6539(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_6543)
static void C_ccall f_6543(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6530)
static void C_fcall f_6530(C_word t0,C_word t1) C_noret;
C_noret_decl(f_6534)
static void C_ccall f_6534(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6518)
static void C_ccall f_6518(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6515)
static void C_ccall f_6515(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6472)
static void C_ccall f_6472(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6477)
static void C_ccall f_6477(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6458)
static void C_ccall f_6458(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6463)
static void C_ccall f_6463(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6429)
static void C_ccall f_6429(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_6429)
static void C_ccall f_6429r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_6438)
static void C_ccall f_6438(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6443)
static void C_ccall f_6443(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6418)
static void C_ccall f_6418(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6423)
static void C_ccall f_6423(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6378)
static void C_ccall f_6378(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_6378)
static void C_ccall f_6378r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_6408)
static void C_ccall f_6408(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6330)
static void C_ccall f_6330(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6364)
static void C_ccall f_6364(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6310)
static void C_ccall f_6310(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6290)
static void C_ccall f_6290(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6276)
static void C_ccall f_6276(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6266)
static void C_ccall f_6266(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6256)
static void C_ccall f_6256(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6246)
static void C_ccall f_6246(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6236)
static void C_ccall f_6236(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6214)
static void C_ccall f_6214(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_6208)
static void C_ccall f_6208(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_6161)
static void C_ccall f_6161(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6165)
static void C_ccall f_6165(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6181)
static void C_ccall f_6181(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6190)
static void C_ccall f_6190(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6168)
static void C_ccall f_6168(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6152)
static void C_ccall f_6152(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6156)
static void C_ccall f_6156(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5973)
static void C_ccall f_5973(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_5973)
static void C_ccall f_5973r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_6126)
static void C_fcall f_6126(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6139)
static void C_ccall f_6139(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6121)
static void C_ccall f_6121(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5976)
static void C_fcall f_5976(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6118)
static void C_ccall f_6118(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6102)
static void C_ccall f_6102(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6095)
static void C_ccall f_6095(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6091)
static void C_ccall f_6091(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6004)
static void C_ccall f_6004(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6012)
static void C_fcall f_6012(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6022)
static void C_ccall f_6022(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6025)
static void C_ccall f_6025(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6007)
static void C_ccall f_6007(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5802)
static void C_ccall f_5802(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_5808)
static void C_ccall f_5808(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5811)
static void C_fcall f_5811(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3614)
static void C_ccall f_3614(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_3627)
static void C_ccall f_3627(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_3634)
static void C_fcall f_3634(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3641)
static void C_ccall f_3641(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3620)
static void C_ccall f_3620(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5815)
static void C_ccall f_5815(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5849)
static void C_ccall f_5849(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5942)
static void C_fcall f_5942(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_5952)
static void C_fcall f_5952(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5855)
static void C_ccall f_5855(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5912)
static void C_fcall f_5912(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_5922)
static void C_fcall f_5922(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5863)
static void C_ccall f_5863(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5877)
static void C_ccall f_5877(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5881)
static void C_ccall f_5881(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5885)
static void C_ccall f_5885(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5889)
static void C_ccall f_5889(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5896)
static void C_ccall f_5896(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5873)
static void C_ccall f_5873(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5866)
static void C_ccall f_5866(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5818)
static void C_ccall f_5818(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4741)
static void C_ccall f_4741(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_4754)
static void C_ccall f_4754(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4804)
static void C_ccall f_4804(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4901)
static void C_ccall f_4901(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4969)
static void C_ccall f_4969(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5226)
static void C_ccall f_5226(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4976)
static void C_fcall f_4976(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5214)
static void C_ccall f_5214(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5165)
static void C_ccall f_5165(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5171)
static void C_ccall f_5171(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5195)
static void C_ccall f_5195(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5191)
static void C_ccall f_5191(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5179)
static void C_ccall f_5179(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4979)
static void C_fcall f_4979(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5141)
static void C_ccall f_5141(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5145)
static void C_ccall f_5145(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4982)
static void C_fcall f_4982(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5118)
static void C_ccall f_5118(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5122)
static void C_ccall f_5122(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4985)
static void C_fcall f_4985(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5095)
static void C_ccall f_5095(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5099)
static void C_ccall f_5099(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4988)
static void C_fcall f_4988(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5020)
static void C_ccall f_5020(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5038)
static void C_ccall f_5038(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5056)
static void C_ccall f_5056(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5074)
static void C_ccall f_5074(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4991)
static void C_fcall f_4991(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4995)
static void C_ccall f_4995(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4905)
static void C_ccall f_4905(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4909)
static void C_ccall f_4909(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4913)
static void C_ccall f_4913(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4808)
static void C_ccall f_4808(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4812)
static void C_ccall f_4812(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4816)
static void C_ccall f_4816(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4835)
static void C_ccall f_4835(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4839)
static void C_ccall f_4839(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4819)
static void C_fcall f_4819(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4823)
static void C_ccall f_4823(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4758)
static void C_ccall f_4758(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4762)
static void C_ccall f_4762(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4766)
static void C_ccall f_4766(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4748)
static void C_fcall f_4748(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4563)
static void C_fcall f_4563(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4575)
static void C_fcall f_4575(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4594)
static void C_ccall f_4594(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4612)
static void C_fcall f_4612(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_4644)
static void C_ccall f_4644(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4647)
static void C_fcall f_4647(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4640)
static void C_ccall f_4640(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4626)
static void C_ccall f_4626(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4597)
static void C_ccall f_4597(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4542)
static void C_fcall f_4542(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4549)
static void C_ccall f_4549(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4552)
static void C_ccall f_4552(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4558)
static void C_ccall f_4558(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4477)
static void C_fcall f_4477(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_4486)
static void C_fcall f_4486(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_4509)
static void C_ccall f_4509(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4499)
static void C_fcall f_4499(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4433)
static void C_fcall f_4433(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_4421)
static void C_fcall f_4421(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4319)
static void C_fcall f_4319(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4271)
static void C_fcall f_4271(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3652)
static void C_fcall f_3652(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_3656)
static void C_ccall f_3656(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3659)
static void C_ccall f_3659(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4085)
static void C_ccall f_4085(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4081)
static void C_ccall f_4081(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4077)
static void C_ccall f_4077(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3662)
static void C_fcall f_3662(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3785)
static void C_ccall f_3785(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3018)
static void C_ccall f_3018(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3791)
static void C_fcall f_3791(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3034)
static void C_ccall f_3034(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3879)
static void C_fcall f_3879(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3949)
static void C_ccall f_3949(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3050)
static void C_ccall f_3050(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3952)
static void C_fcall f_3952(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3082)
static void C_ccall f_3082(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4030)
static void C_fcall f_4030(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4056)
static void C_ccall f_4056(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_4050)
static void C_ccall f_4050(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4039)
static void C_ccall f_4039(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3981)
static void C_fcall f_3981(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3991)
static void C_ccall f_3991(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4017)
static void C_ccall f_4017(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_4011)
static void C_ccall f_4011(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3994)
static void C_ccall f_3994(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4004)
static void C_ccall f_4004(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3997)
static void C_fcall f_3997(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3958)
static void C_ccall f_3958(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3967)
static void C_ccall f_3967(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3961)
static void C_fcall f_3961(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3885)
static void C_ccall f_3885(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3903)
static void C_fcall f_3903(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_3936)
static void C_ccall f_3936(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_3922)
static void C_ccall f_3922(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3930)
static void C_ccall f_3930(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3913)
static void C_ccall f_3913(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3888)
static void C_ccall f_3888(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3800)
static void C_ccall f_3800(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3822)
static void C_fcall f_3822(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_3869)
static void C_ccall f_3869(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_3855)
static void C_ccall f_3855(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3863)
static void C_ccall f_3863(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3835)
static void C_ccall f_3835(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3838)
static void C_fcall f_3838(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3803)
static void C_ccall f_3803(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3820)
static void C_ccall f_3820(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3806)
static void C_fcall f_3806(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3677)
static void C_ccall f_3677(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3735)
static void C_ccall f_3735(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3738)
static void C_ccall f_3738(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3759)
static void C_ccall f_3759(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_3770)
static void C_ccall f_3770(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3749)
static void C_ccall f_3749(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3683)
static void C_ccall f_3683(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3693)
static void C_ccall f_3693(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3729)
static void C_ccall f_3729(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3699)
static void C_ccall f_3699(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3714)
static void C_ccall f_3714(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3718)
static void C_ccall f_3718(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3722)
static void C_ccall f_3722(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3706)
static void C_ccall f_3706(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3548)
static void C_fcall f_3548(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3550)
static void C_ccall f_3550(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_3598)
static void C_ccall f_3598(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3554)
static void C_ccall f_3554(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3557)
static void C_fcall f_3557(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3562)
static void C_fcall f_3562(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_3583)
static void C_ccall f_3583(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3540)
static void C_fcall f_3540(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3542)
static void C_ccall f_3542(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_3332)
static void C_fcall f_3332(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_3349)
static void C_ccall f_3349(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3353)
static void C_ccall f_3353(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3299)
static void C_fcall f_3299(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_3306)
static void C_ccall f_3306(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3250)
static void C_ccall f_3250(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3257)
static void C_ccall f_3257(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3315)
static void C_ccall f_3315(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3538)
static void C_ccall f_3538(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3515)
static void C_ccall f_3515(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3531)
static void C_ccall f_3531(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3377)
static void C_ccall f_3377(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3380)
static void C_ccall f_3380(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3404)
static void C_ccall f_3404(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3461)
static void C_ccall f_3461(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3467)
static void C_ccall f_3467(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3476)
static void C_ccall f_3476(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3485)
static void C_ccall f_3485(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3494)
static void C_ccall f_3494(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3503)
static void C_ccall f_3503(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3455)
static void C_ccall f_3455(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3410)
static void C_ccall f_3410(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3416)
static void C_ccall f_3416(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3422)
static void C_ccall f_3422(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3428)
static void C_ccall f_3428(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3434)
static void C_ccall f_3434(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3440)
static void C_ccall f_3440(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3281)
static void C_fcall f_3281(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_3288)
static void C_ccall f_3288(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3271)
static void C_fcall f_3271(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_3259)
static void C_fcall f_3259(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_3227)
static void C_fcall f_3227(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_3234)
static void C_ccall f_3234(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3241)
static void C_ccall f_3241(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3211)
static void C_fcall f_3211(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3218)
static void C_ccall f_3218(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3225)
static void C_ccall f_3225(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3199)
static void C_fcall f_3199(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3181)
static void C_fcall f_3181(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3163)
static void C_fcall f_3163(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3148)
static void C_fcall f_3148(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3142)
static void C_fcall f_3142(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_3130)
static void C_fcall f_3130(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3112)
static void C_fcall f_3112(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3091)
static void C_fcall f_3091(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_3059)
static void C_fcall f_3059(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3066)
static void C_ccall f_3066(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3001)
static void C_fcall f_3001(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_3009)
static void C_ccall f_3009(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2991)
static void C_fcall f_2991(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2999)
static void C_ccall f_2999(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2985)
static void C_fcall f_2985(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2973)
static void C_fcall f_2973(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2949)
static void C_fcall f_2949(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2865)
static void C_fcall f_2865(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2844)
static void C_fcall f_2844(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_2834)
static void C_fcall f_2834(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2822)
static void C_fcall f_2822(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2793)
static void C_ccall f_2793(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2781)
static void C_fcall f_2781(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2763)
static void C_fcall f_2763(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2745)
static void C_fcall f_2745(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2724)
static void C_ccall f_2724(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_2718)
static void C_ccall f_2718(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2712)
static void C_ccall f_2712(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2693)
static void C_ccall f_2693(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_2693)
static void C_ccall f_2693r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_2674)
static void C_ccall f_2674(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_2674)
static void C_ccall f_2674r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_2668)
static void C_ccall f_2668(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2628)
static void C_ccall f_2628(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_2628)
static void C_ccall f_2628r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_2609)
static void C_ccall f_2609(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_2609)
static void C_ccall f_2609r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_2565)
static void C_ccall f_2565(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_2565)
static void C_ccall f_2565r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_2559)
static void C_ccall f_2559(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2553)
static void C_ccall f_2553(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2547)
static void C_ccall f_2547(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2541)
static void C_ccall f_2541(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_2541)
static void C_ccall f_2541r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_2518)
static void C_ccall f_2518(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2535)
static void C_ccall f_2535(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2460)
static void C_ccall f_2460(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_2460)
static void C_ccall f_2460r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_2512)
static void C_ccall f_2512(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2496)
static void C_ccall f_2496(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2477)
static void C_ccall f_2477(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2372)
static void C_ccall f_2372(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_2372)
static void C_ccall f_2372r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_2418)
static void C_fcall f_2418(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2366)
static void C_ccall f_2366(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2307)
static void C_ccall f_2307(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_2307)
static void C_ccall f_2307r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_2320)
static void C_fcall f_2320(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_2356)
static void C_ccall f_2356(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2301)
static void C_ccall f_2301(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_2301)
static void C_ccall f_2301r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_2206)
static void C_ccall f_2206(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_2206)
static void C_ccall f_2206r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_2210)
static void C_ccall f_2210(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2213)
static void C_ccall f_2213(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2225)
static void C_fcall f_2225(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2247)
static void C_ccall f_2247(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2200)
static void C_ccall f_2200(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2194)
static void C_ccall f_2194(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2188)
static void C_ccall f_2188(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2182)
static void C_ccall f_2182(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2176)
static void C_ccall f_2176(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2116)
static void C_ccall f_2116(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_2116)
static void C_ccall f_2116r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_2128)
static void C_fcall f_2128(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2123)
static void C_fcall f_2123(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2118)
static void C_fcall f_2118(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_2097)
static void C_ccall f_2097(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_2097)
static void C_ccall f_2097r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_2091)
static void C_ccall f_2091(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_2085)
static void C_ccall f_2085(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2003)
static void C_ccall f_2003(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,...) C_noret;
C_noret_decl(f_2003)
static void C_ccall f_2003r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t7) C_noret;
C_noret_decl(f_2017)
static void C_ccall f_2017(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1984)
static void C_ccall f_1984(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,...) C_noret;
C_noret_decl(f_1984)
static void C_ccall f_1984r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t8) C_noret;
C_noret_decl(f_1971)
static void C_fcall f_1971(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1961)
static void C_fcall f_1961(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1950)
static void C_fcall f_1950(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1943)
static void C_fcall f_1943(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1932)
static void C_fcall f_1932(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1894)
static void C_fcall f_1894(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1887)
static void C_fcall f_1887(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1812)
static void C_fcall f_1812(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1778)
static void C_fcall f_1778(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_1751)
static void C_fcall f_1751(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;

C_noret_decl(trf_11911)
static void C_fcall trf_11911(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_11911(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_11911(t0,t1);}

C_noret_decl(trf_10793)
static void C_fcall trf_10793(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_10793(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_10793(t0,t1);}

C_noret_decl(trf_10666)
static void C_fcall trf_10666(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_10666(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_10666(t0,t1,t2);}

C_noret_decl(trf_10330)
static void C_fcall trf_10330(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_10330(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_10330(t0,t1);}

C_noret_decl(trf_9425)
static void C_fcall trf_9425(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_9425(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_9425(t0,t1,t2);}

C_noret_decl(trf_9460)
static void C_fcall trf_9460(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_9460(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_9460(t0,t1);}

C_noret_decl(trf_9484)
static void C_fcall trf_9484(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_9484(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_9484(t0,t1);}

C_noret_decl(trf_9463)
static void C_fcall trf_9463(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_9463(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_9463(t0,t1);}

C_noret_decl(trf_9266)
static void C_fcall trf_9266(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_9266(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_9266(t0,t1);}

C_noret_decl(trf_9084)
static void C_fcall trf_9084(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_9084(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_9084(t0,t1);}

C_noret_decl(trf_9091)
static void C_fcall trf_9091(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_9091(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_9091(t0,t1);}

C_noret_decl(trf_9072)
static void C_fcall trf_9072(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_9072(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_9072(t0,t1);}

C_noret_decl(trf_5289)
static void C_fcall trf_5289(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5289(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5289(t0,t1);}

C_noret_decl(trf_5296)
static void C_fcall trf_5296(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5296(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5296(t0,t1);}

C_noret_decl(trf_5607)
static void C_fcall trf_5607(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5607(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_5607(t0,t1,t2);}

C_noret_decl(trf_5630)
static void C_fcall trf_5630(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5630(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_5630(t0,t1,t2);}

C_noret_decl(trf_5647)
static void C_fcall trf_5647(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5647(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5647(t0,t1);}

C_noret_decl(trf_5650)
static void C_fcall trf_5650(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5650(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5650(t0,t1);}

C_noret_decl(trf_5653)
static void C_fcall trf_5653(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5653(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5653(t0,t1);}

C_noret_decl(trf_5571)
static void C_fcall trf_5571(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5571(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_5571(t0,t1,t2);}

C_noret_decl(trf_5515)
static void C_fcall trf_5515(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5515(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_5515(t0,t1,t2);}

C_noret_decl(trf_5531)
static void C_fcall trf_5531(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5531(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5531(t0,t1);}

C_noret_decl(trf_5312)
static void C_fcall trf_5312(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5312(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5312(t0,t1);}

C_noret_decl(trf_5315)
static void C_fcall trf_5315(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5315(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5315(t0,t1);}

C_noret_decl(trf_8581)
static void C_fcall trf_8581(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8581(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_8581(t0,t1);}

C_noret_decl(trf_8584)
static void C_fcall trf_8584(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8584(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_8584(t0,t1);}

C_noret_decl(trf_8427)
static void C_fcall trf_8427(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8427(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_8427(t0,t1);}

C_noret_decl(trf_8235)
static void C_fcall trf_8235(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8235(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_8235(t0,t1);}

C_noret_decl(trf_8085)
static void C_fcall trf_8085(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8085(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_8085(t0,t1);}

C_noret_decl(trf_8174)
static void C_fcall trf_8174(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8174(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_8174(t0,t1);}

C_noret_decl(trf_8088)
static void C_fcall trf_8088(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8088(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_8088(t0,t1);}

C_noret_decl(trf_8104)
static void C_fcall trf_8104(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8104(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_8104(t0,t1,t2,t3);}

C_noret_decl(trf_8126)
static void C_fcall trf_8126(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8126(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_8126(t0,t1);}

C_noret_decl(trf_8021)
static void C_fcall trf_8021(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8021(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_8021(t0,t1,t2);}

C_noret_decl(trf_7968)
static void C_fcall trf_7968(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7968(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_7968(t0,t1);}

C_noret_decl(trf_7600)
static void C_fcall trf_7600(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7600(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_7600(t0,t1,t2);}

C_noret_decl(trf_7620)
static void C_fcall trf_7620(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7620(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_7620(t0,t1);}

C_noret_decl(trf_7629)
static void C_fcall trf_7629(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7629(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_7629(t0,t1);}

C_noret_decl(trf_7645)
static void C_fcall trf_7645(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7645(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_7645(t0,t1);}

C_noret_decl(trf_7493)
static void C_fcall trf_7493(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7493(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_7493(t0,t1);}

C_noret_decl(trf_7502)
static void C_fcall trf_7502(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7502(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_7502(t0,t1,t2);}

C_noret_decl(trf_7526)
static void C_fcall trf_7526(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7526(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_7526(t0,t1);}

C_noret_decl(trf_7347)
static void C_fcall trf_7347(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7347(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_7347(t0,t1);}

C_noret_decl(trf_7029)
static void C_fcall trf_7029(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7029(void *dummy){
C_word t4=C_pick(0);
C_word t3=C_pick(1);
C_word t2=C_pick(2);
C_word t1=C_pick(3);
C_word t0=C_pick(4);
C_adjust_stack(-5);
f_7029(t0,t1,t2,t3,t4);}

C_noret_decl(trf_7039)
static void C_fcall trf_7039(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7039(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_7039(t0,t1);}

C_noret_decl(trf_6989)
static void C_fcall trf_6989(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6989(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_6989(t0,t1,t2);}

C_noret_decl(trf_7002)
static void C_fcall trf_7002(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7002(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_7002(t0,t1);}

C_noret_decl(trf_6897)
static void C_fcall trf_6897(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6897(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_6897(t0,t1,t2);}

C_noret_decl(trf_6817)
static void C_fcall trf_6817(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6817(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_6817(t0,t1);}

C_noret_decl(trf_6743)
static void C_fcall trf_6743(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6743(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_6743(t0,t1);}

C_noret_decl(trf_6738)
static void C_fcall trf_6738(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6738(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_6738(t0,t1,t2);}

C_noret_decl(trf_6626)
static void C_fcall trf_6626(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6626(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_6626(t0,t1,t2,t3);}

C_noret_decl(trf_6697)
static void C_fcall trf_6697(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6697(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_6697(t0,t1,t2);}

C_noret_decl(trf_6656)
static void C_fcall trf_6656(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6656(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_6656(t0,t1);}

C_noret_decl(trf_6628)
static void C_fcall trf_6628(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6628(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_6628(t0,t1);}

C_noret_decl(trf_6583)
static void C_fcall trf_6583(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6583(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_6583(t0,t1);}

C_noret_decl(trf_6539)
static void C_fcall trf_6539(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6539(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_6539(t0,t1,t2,t3);}

C_noret_decl(trf_6530)
static void C_fcall trf_6530(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6530(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_6530(t0,t1);}

C_noret_decl(trf_6126)
static void C_fcall trf_6126(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6126(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_6126(t0,t1,t2);}

C_noret_decl(trf_5976)
static void C_fcall trf_5976(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5976(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_5976(t0,t1,t2);}

C_noret_decl(trf_6012)
static void C_fcall trf_6012(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6012(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_6012(t0,t1,t2);}

C_noret_decl(trf_5811)
static void C_fcall trf_5811(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5811(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5811(t0,t1);}

C_noret_decl(trf_3634)
static void C_fcall trf_3634(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3634(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3634(t0,t1);}

C_noret_decl(trf_5942)
static void C_fcall trf_5942(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5942(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_5942(t0,t1,t2);}

C_noret_decl(trf_5952)
static void C_fcall trf_5952(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5952(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5952(t0,t1);}

C_noret_decl(trf_5912)
static void C_fcall trf_5912(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5912(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_5912(t0,t1,t2);}

C_noret_decl(trf_5922)
static void C_fcall trf_5922(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5922(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5922(t0,t1);}

C_noret_decl(trf_4976)
static void C_fcall trf_4976(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4976(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4976(t0,t1);}

C_noret_decl(trf_4979)
static void C_fcall trf_4979(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4979(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4979(t0,t1);}

C_noret_decl(trf_4982)
static void C_fcall trf_4982(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4982(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4982(t0,t1);}

C_noret_decl(trf_4985)
static void C_fcall trf_4985(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4985(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4985(t0,t1);}

C_noret_decl(trf_4988)
static void C_fcall trf_4988(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4988(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4988(t0,t1);}

C_noret_decl(trf_4991)
static void C_fcall trf_4991(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4991(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4991(t0,t1);}

C_noret_decl(trf_4819)
static void C_fcall trf_4819(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4819(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4819(t0,t1);}

C_noret_decl(trf_4748)
static void C_fcall trf_4748(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4748(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4748(t0,t1);}

C_noret_decl(trf_4563)
static void C_fcall trf_4563(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4563(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4563(t0,t1);}

C_noret_decl(trf_4575)
static void C_fcall trf_4575(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4575(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4575(t0,t1);}

C_noret_decl(trf_4612)
static void C_fcall trf_4612(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4612(void *dummy){
C_word t4=C_pick(0);
C_word t3=C_pick(1);
C_word t2=C_pick(2);
C_word t1=C_pick(3);
C_word t0=C_pick(4);
C_adjust_stack(-5);
f_4612(t0,t1,t2,t3,t4);}

C_noret_decl(trf_4647)
static void C_fcall trf_4647(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4647(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4647(t0,t1);}

C_noret_decl(trf_4542)
static void C_fcall trf_4542(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4542(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4542(t0,t1);}

C_noret_decl(trf_4477)
static void C_fcall trf_4477(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4477(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_4477(t0,t1,t2);}

C_noret_decl(trf_4486)
static void C_fcall trf_4486(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4486(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_4486(t0,t1,t2);}

C_noret_decl(trf_4499)
static void C_fcall trf_4499(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4499(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4499(t0,t1);}

C_noret_decl(trf_4433)
static void C_fcall trf_4433(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4433(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_4433(t0,t1,t2);}

C_noret_decl(trf_4421)
static void C_fcall trf_4421(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4421(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4421(t0,t1);}

C_noret_decl(trf_4319)
static void C_fcall trf_4319(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4319(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4319(t0,t1);}

C_noret_decl(trf_4271)
static void C_fcall trf_4271(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4271(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4271(t0,t1);}

C_noret_decl(trf_3652)
static void C_fcall trf_3652(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3652(void *dummy){
C_word t6=C_pick(0);
C_word t5=C_pick(1);
C_word t4=C_pick(2);
C_word t3=C_pick(3);
C_word t2=C_pick(4);
C_word t1=C_pick(5);
C_word t0=C_pick(6);
C_adjust_stack(-7);
f_3652(t0,t1,t2,t3,t4,t5,t6);}

C_noret_decl(trf_3662)
static void C_fcall trf_3662(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3662(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3662(t0,t1);}

C_noret_decl(trf_3791)
static void C_fcall trf_3791(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3791(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3791(t0,t1);}

C_noret_decl(trf_3879)
static void C_fcall trf_3879(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3879(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3879(t0,t1);}

C_noret_decl(trf_3952)
static void C_fcall trf_3952(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3952(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3952(t0,t1);}

C_noret_decl(trf_4030)
static void C_fcall trf_4030(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4030(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4030(t0,t1);}

C_noret_decl(trf_3981)
static void C_fcall trf_3981(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3981(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3981(t0,t1);}

C_noret_decl(trf_3997)
static void C_fcall trf_3997(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3997(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3997(t0,t1);}

C_noret_decl(trf_3961)
static void C_fcall trf_3961(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3961(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3961(t0,t1);}

C_noret_decl(trf_3903)
static void C_fcall trf_3903(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3903(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_3903(t0,t1,t2);}

C_noret_decl(trf_3822)
static void C_fcall trf_3822(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3822(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_3822(t0,t1,t2);}

C_noret_decl(trf_3838)
static void C_fcall trf_3838(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3838(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3838(t0,t1);}

C_noret_decl(trf_3806)
static void C_fcall trf_3806(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3806(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3806(t0,t1);}

C_noret_decl(trf_3548)
static void C_fcall trf_3548(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3548(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3548(t0,t1);}

C_noret_decl(trf_3557)
static void C_fcall trf_3557(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3557(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3557(t0,t1);}

C_noret_decl(trf_3562)
static void C_fcall trf_3562(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3562(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_3562(t0,t1,t2);}

C_noret_decl(trf_3540)
static void C_fcall trf_3540(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3540(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3540(t0,t1);}

C_noret_decl(trf_3332)
static void C_fcall trf_3332(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3332(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_3332(t0,t1,t2,t3);}

C_noret_decl(trf_3299)
static void C_fcall trf_3299(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3299(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_3299(t0,t1,t2,t3);}

C_noret_decl(trf_3281)
static void C_fcall trf_3281(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3281(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_3281(t0,t1,t2,t3);}

C_noret_decl(trf_3271)
static void C_fcall trf_3271(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3271(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_3271(t0,t1,t2,t3);}

C_noret_decl(trf_3259)
static void C_fcall trf_3259(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3259(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_3259(t0,t1,t2);}

C_noret_decl(trf_3227)
static void C_fcall trf_3227(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3227(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_3227(t0,t1,t2);}

C_noret_decl(trf_3211)
static void C_fcall trf_3211(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3211(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3211(t0,t1);}

C_noret_decl(trf_3199)
static void C_fcall trf_3199(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3199(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3199(t0,t1);}

C_noret_decl(trf_3181)
static void C_fcall trf_3181(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3181(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3181(t0,t1);}

C_noret_decl(trf_3163)
static void C_fcall trf_3163(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3163(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3163(t0,t1);}

C_noret_decl(trf_3148)
static void C_fcall trf_3148(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3148(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3148(t0,t1);}

C_noret_decl(trf_3142)
static void C_fcall trf_3142(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3142(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_3142(t0,t1,t2,t3);}

C_noret_decl(trf_3130)
static void C_fcall trf_3130(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3130(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3130(t0,t1);}

C_noret_decl(trf_3112)
static void C_fcall trf_3112(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3112(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3112(t0,t1);}

C_noret_decl(trf_3091)
static void C_fcall trf_3091(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3091(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_3091(t0,t1,t2);}

C_noret_decl(trf_3059)
static void C_fcall trf_3059(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3059(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3059(t0,t1);}

C_noret_decl(trf_3001)
static void C_fcall trf_3001(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3001(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_3001(t0,t1,t2);}

C_noret_decl(trf_2991)
static void C_fcall trf_2991(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2991(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2991(t0,t1);}

C_noret_decl(trf_2985)
static void C_fcall trf_2985(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2985(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2985(t0,t1);}

C_noret_decl(trf_2973)
static void C_fcall trf_2973(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2973(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2973(t0,t1);}

C_noret_decl(trf_2949)
static void C_fcall trf_2949(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2949(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_2949(t0,t1,t2);}

C_noret_decl(trf_2865)
static void C_fcall trf_2865(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2865(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2865(t0,t1);}

C_noret_decl(trf_2844)
static void C_fcall trf_2844(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2844(void *dummy){
C_word t5=C_pick(0);
C_word t4=C_pick(1);
C_word t3=C_pick(2);
C_word t2=C_pick(3);
C_word t1=C_pick(4);
C_word t0=C_pick(5);
C_adjust_stack(-6);
f_2844(t0,t1,t2,t3,t4,t5);}

C_noret_decl(trf_2834)
static void C_fcall trf_2834(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2834(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2834(t0,t1);}

C_noret_decl(trf_2822)
static void C_fcall trf_2822(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2822(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2822(t0,t1);}

C_noret_decl(trf_2781)
static void C_fcall trf_2781(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2781(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2781(t0,t1);}

C_noret_decl(trf_2763)
static void C_fcall trf_2763(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2763(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2763(t0,t1);}

C_noret_decl(trf_2745)
static void C_fcall trf_2745(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2745(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2745(t0,t1);}

C_noret_decl(trf_2418)
static void C_fcall trf_2418(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2418(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2418(t0,t1);}

C_noret_decl(trf_2320)
static void C_fcall trf_2320(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2320(void *dummy){
C_word t5=C_pick(0);
C_word t4=C_pick(1);
C_word t3=C_pick(2);
C_word t2=C_pick(3);
C_word t1=C_pick(4);
C_word t0=C_pick(5);
C_adjust_stack(-6);
f_2320(t0,t1,t2,t3,t4,t5);}

C_noret_decl(trf_2225)
static void C_fcall trf_2225(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2225(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_2225(t0,t1,t2);}

C_noret_decl(trf_2128)
static void C_fcall trf_2128(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2128(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2128(t0,t1);}

C_noret_decl(trf_2123)
static void C_fcall trf_2123(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2123(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_2123(t0,t1,t2);}

C_noret_decl(trf_2118)
static void C_fcall trf_2118(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2118(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_2118(t0,t1,t2,t3);}

C_noret_decl(trf_1971)
static void C_fcall trf_1971(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1971(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1971(t0,t1);}

C_noret_decl(trf_1961)
static void C_fcall trf_1961(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1961(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1961(t0,t1);}

C_noret_decl(trf_1950)
static void C_fcall trf_1950(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1950(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1950(t0,t1,t2);}

C_noret_decl(trf_1943)
static void C_fcall trf_1943(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1943(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1943(t0,t1);}

C_noret_decl(trf_1932)
static void C_fcall trf_1932(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1932(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1932(t0,t1,t2);}

C_noret_decl(trf_1894)
static void C_fcall trf_1894(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1894(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1894(t0,t1);}

C_noret_decl(trf_1887)
static void C_fcall trf_1887(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1887(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1887(t0,t1);}

C_noret_decl(trf_1812)
static void C_fcall trf_1812(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1812(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1812(t0,t1,t2);}

C_noret_decl(trf_1778)
static void C_fcall trf_1778(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1778(void *dummy){
C_word t6=C_pick(0);
C_word t5=C_pick(1);
C_word t4=C_pick(2);
C_word t3=C_pick(3);
C_word t2=C_pick(4);
C_word t1=C_pick(5);
C_word t0=C_pick(6);
C_adjust_stack(-7);
f_1778(t0,t1,t2,t3,t4,t5,t6);}

C_noret_decl(trf_1751)
static void C_fcall trf_1751(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1751(void *dummy){
C_word t6=C_pick(0);
C_word t5=C_pick(1);
C_word t4=C_pick(2);
C_word t3=C_pick(3);
C_word t2=C_pick(4);
C_word t1=C_pick(5);
C_word t0=C_pick(6);
C_adjust_stack(-7);
f_1751(t0,t1,t2,t3,t4,t5,t6);}

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
if(!C_demand_2(2504)){
C_save(t1);
C_rereclaim2(2504*sizeof(C_word), 1);
t1=C_restore;}
a=C_alloc(3);
C_initialize_lf(lf,645);
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
lf[105]=C_h_intern(&lf[105],5,"token");
lf[106]=C_static_lambda_info(C_heaptop,42,"(make-token type293 string294 position295)");
lf[108]=C_static_lambda_info(C_heaptop,17,"(token-type x300)");
lf[110]=C_static_lambda_info(C_heaptop,19,"(token-string x306)");
lf[112]=C_static_lambda_info(C_heaptop,21,"(token-position x312)");
lf[114]=C_h_intern(&lf[114],1,"t");
lf[115]=C_static_lambda_info(C_heaptop,18,"(list->token l321)");
lf[117]=C_static_lambda_info(C_heaptop,21,"(first-token toks323)");
lf[119]=C_static_lambda_info(C_heaptop,22,"(null-tokens\077 toks325)");
lf[122]=C_h_intern(&lf[122],4,"rule");
lf[123]=C_static_lambda_info(C_heaptop,58,"(make-rule name326 type327 pattern328 parser329 emiter330)");
lf[125]=C_static_lambda_info(C_heaptop,16,"(rule-name x335)");
lf[127]=C_h_intern(&lf[127],14,"hash-table-ref");
lf[128]=C_h_intern(&lf[128],22,"hash-table-ref/default");
lf[129]=C_static_lambda_info(C_heaptop,24,"(get-rule typ371 def372)");
lf[131]=C_static_lambda_info(C_heaptop,22,"(pattern-clause\077 x375)");
lf[133]=C_static_lambda_info(C_heaptop,19,"(pattern-subs x377)");
lf[135]=C_static_lambda_info(C_heaptop,20,"(pattern-nsubs x378)");
lf[137]=C_static_lambda_info(C_heaptop,23,"(pattern-sub x379 i380)");
lf[139]=C_h_intern(&lf[139],1,"*");
lf[140]=C_static_lambda_info(C_heaptop,28,"(pattern-zero-or-more\077 x384)");
lf[142]=C_h_intern(&lf[142],11,"parse-error");
lf[143]=C_static_lambda_info(C_heaptop,40,"(make-parse-error string386 position387)");
lf[145]=C_static_lambda_info(C_heaptop,25,"(parse-error-string x392)");
lf[147]=C_static_lambda_info(C_heaptop,27,"(parse-error-position x398)");
lf[149]=C_h_intern(&lf[149],10,"parse-unit");
lf[150]=C_static_lambda_info(C_heaptop,47,"(make-parse-unit type406 parsed407 position408)");
lf[152]=C_static_lambda_info(C_heaptop,18,"(parse-unit\077 x409)");
lf[154]=C_static_lambda_info(C_heaptop,22,"(parse-unit-type x413)");
lf[156]=C_static_lambda_info(C_heaptop,24,"(parse-unit-parsed x419)");
lf[158]=C_static_lambda_info(C_heaptop,26,"(parse-unit-position x425)");
lf[161]=C_static_lambda_info(C_heaptop,18,"(token-unit\077 x435)");
lf[164]=C_static_lambda_info(C_heaptop,31,"(token-unit-type=\077 x436 typ437)");
lf[166]=C_static_lambda_info(C_heaptop,31,"(get-emit-info name439 info440)");
lf[168]=C_static_lambda_info(C_heaptop,39,"(add-emit-info name442 data443 info444)");
lf[170]=C_static_string(C_heaptop,12,"no info for ");
lf[171]=C_static_lambda_info(C_heaptop,40,"(set-emit-info! name445 data446 info447)");
lf[173]=C_h_intern(&lf[173],14,"string->symbol");
lf[174]=C_h_intern(&lf[174],4,"expt");
lf[175]=C_h_intern(&lf[175],5,"equal");
lf[176]=C_h_intern(&lf[176],3,"and");
lf[177]=C_h_intern(&lf[177],2,"or");
lf[178]=C_h_intern(&lf[178],3,"not");
lf[179]=C_h_intern(&lf[179],15,"string->keyword");
lf[180]=C_static_string(C_heaptop,53,"emit-token-unit: dont know how to emit slotref token ");
lf[181]=C_static_string(C_heaptop,39,"emit-token-unit: dont know how to emit ");
lf[184]=C_static_string(C_heaptop,27,"emit: dont know how to emit");
lf[186]=C_static_lambda_info(C_heaptop,27,"(emit x450 info451 errf452)");
lf[187]=C_static_lambda_info(C_heaptop,34,"(emit-list lis453 info454 errf455)");
lf[189]=C_static_lambda_info(C_heaptop,24,"(f_3542 args468 errf469)");
lf[190]=C_static_lambda_info(C_heaptop,28,"(simple-unit-parser type467)");
lf[192]=C_static_lambda_info(C_heaptop,15,"(do477 tail479)");
lf[193]=C_h_intern(&lf[193],6,"append");
lf[194]=C_static_lambda_info(C_heaptop,32,"(f_3550 unit471 info472 errf473)");
lf[195]=C_static_lambda_info(C_heaptop,29,"(simple-unit-emitter func470)");
lf[198]=C_static_lambda_info(C_heaptop,7,"(a3748)");
lf[199]=C_static_lambda_info(C_heaptop,22,"(a3758 a509 b510 c511)");
lf[200]=C_static_string(C_heaptop,29,"Not a token type or rule type");
lf[201]=C_h_intern(&lf[201],7,"reverse");
lf[202]=C_static_lambda_info(C_heaptop,7,"(a3854)");
lf[203]=C_static_lambda_info(C_heaptop,22,"(a3868 a525 b526 c527)");
lf[204]=C_static_lambda_info(C_heaptop,12,"(do520 i522)");
lf[205]=C_static_lambda_info(C_heaptop,7,"(a3921)");
lf[206]=C_static_lambda_info(C_heaptop,22,"(a3935 a547 b548 c549)");
lf[207]=C_static_lambda_info(C_heaptop,12,"(do542 i544)");
lf[208]=C_static_lambda_info(C_heaptop,7,"(a4010)");
lf[209]=C_static_lambda_info(C_heaptop,22,"(a4016 a566 b567 c568)");
lf[210]=C_static_lambda_info(C_heaptop,7,"(do562)");
lf[211]=C_static_lambda_info(C_heaptop,7,"(a4049)");
lf[212]=C_static_lambda_info(C_heaptop,22,"(a4055 a584 b585 c586)");
lf[213]=C_static_string(C_heaptop,39,"Pattern opr not one of and, or, *, +, @");
lf[214]=C_h_intern(&lf[214],1,"@");
lf[215]=C_h_intern(&lf[215],1,"+");
lf[216]=C_static_string(C_heaptop,39,"Not a pattern value or pattern operator");
lf[217]=C_h_intern(&lf[217],3,"max");
lf[218]=C_h_intern(&lf[218],6,"printf");
lf[219]=C_static_string(C_heaptop,33,"~%parse[~A]: pattern=~S tokens=~S");
lf[220]=C_static_lambda_info(C_heaptop,64,"(parser pat496 tokens497 force-and498 level499 trace500 errf501)");
lf[221]=C_static_lambda_info(C_heaptop,20,"(SalTokenType\077 i761)");
lf[222]=C_static_lambda_info(C_heaptop,17,"(SalOpType\077 i765)");
lf[223]=C_static_lambda_info(C_heaptop,19,"(SalRuleType\077 i774)");
lf[224]=C_static_lambda_info(C_heaptop,27,"(SalType=\077 typ1775 typ2776)");
lf[226]=C_static_lambda_info(C_heaptop,15,"(do825 toks827)");
lf[227]=C_static_lambda_info(C_heaptop,34,"(remove-token-type toks821 typ822)");
lf[229]=C_static_lambda_info(C_heaptop,13,"(is-op\077 x852)");
lf[231]=C_static_lambda_info(C_heaptop,25,"(do861 w2863 ok864 li865)");
lf[232]=C_static_lambda_info(C_heaptop,7,"(do859)");
lf[233]=C_static_lambda_info(C_heaptop,17,"(inf->pre inf854)");
lf[235]=C_h_intern(&lf[235],4,"set!");
lf[236]=C_h_intern(&lf[236],2,">=");
lf[237]=C_h_intern(&lf[237],6,"gensym");
lf[238]=C_static_string(C_heaptop,4,"stop");
lf[239]=C_static_string(C_heaptop,4,"temp");
lf[240]=C_h_intern(&lf[240],5,"begin");
lf[241]=C_h_intern(&lf[241],2,"if");
lf[242]=C_static_string(C_heaptop,4,"bool");
lf[243]=C_h_intern(&lf[243],5,"fifth");
lf[244]=C_h_intern(&lf[244],3,"cdr");
lf[245]=C_h_intern(&lf[245],5,"null\077");
lf[246]=C_h_intern(&lf[246],3,"car");
lf[247]=C_static_string(C_heaptop,4,"tail");
lf[248]=C_h_intern(&lf[248],1,">");
lf[249]=C_h_intern(&lf[249],2,"<=");
lf[250]=C_h_intern(&lf[250],1,"-");
lf[251]=C_h_intern(&lf[251],1,"<");
lf[252]=C_static_string(C_heaptop,4,"goal");
lf[253]=C_static_string(C_heaptop,4,"from");
lf[254]=C_static_string(C_heaptop,4,"step");
lf[255]=C_static_lambda_info(C_heaptop,38,"(sal-parse-stepping args1021 errf1022)");
lf[259]=C_h_intern(&lf[259],3,"sal");
lf[260]=C_h_intern(&lf[260],11,"print-error");
lf[261]=C_h_intern(&lf[261],13,"string-append");
lf[262]=C_static_string(C_heaptop,11,">>> Error: ");
lf[263]=C_h_intern(&lf[263],11,"make-string");
lf[264]=C_h_intern(&lf[264],9,"substring");
lf[265]=C_static_lambda_info(C_heaptop,14,"(do1229 f1231)");
lf[266]=C_static_lambda_info(C_heaptop,14,"(do1222 f1224)");
lf[267]=C_h_intern(&lf[267],2,"pp");
lf[268]=C_h_intern(&lf[268],4,"eval");
lf[269]=C_static_lambda_info(C_heaptop,7,"(a3619)");
lf[270]=C_h_intern(&lf[270],7,"\000syntax");
lf[271]=C_h_intern(&lf[271],7,"\000scheme");
lf[272]=C_static_string(C_heaptop,19,"Illegal statement: ");
lf[273]=C_static_lambda_info(C_heaptop,40,"(a3626 success491 results492 remains493)");
lf[274]=C_static_lambda_info(C_heaptop,15,"(a3613 errf489)");
lf[275]=C_h_intern(&lf[275],7,"call/cc");
lf[276]=C_h_intern(&lf[276],7,"\003sysmap");
lf[277]=C_static_lambda_info(C_heaptop,47,"(sal string1207 rule1208 tokens1209 trace\0771210)");
lf[278]=C_h_intern(&lf[278],9,"sal:print");
lf[279]=C_h_intern(&lf[279],13,"print-message");
lf[280]=C_static_string(C_heaptop,2,"{}");
lf[281]=C_static_string(C_heaptop,1,"}");
lf[282]=C_static_string(C_heaptop,1," ");
lf[283]=C_static_lambda_info(C_heaptop,17,"(do1248 tail1250)");
lf[284]=C_static_string(C_heaptop,1,"{");
lf[285]=C_static_string(C_heaptop,2,"#t");
lf[286]=C_h_intern(&lf[286],7,"sprintf");
lf[287]=C_static_string(C_heaptop,2,"~S");
lf[288]=C_static_string(C_heaptop,2,"#f");
lf[289]=C_static_lambda_info(C_heaptop,19,"(printer thing1247)");
lf[290]=C_static_string(C_heaptop,1,"\012");
lf[291]=C_static_lambda_info(C_heaptop,17,"(do1256 tail1258)");
lf[292]=C_static_lambda_info(C_heaptop,22,"(sal:print . args1245)");
lf[293]=C_h_intern(&lf[293],9,"sal:chdir");
lf[294]=C_h_intern(&lf[294],16,"change-directory");
lf[295]=C_static_lambda_info(C_heaptop,20,"(sal:chdir path1263)");
lf[296]=C_h_intern(&lf[296],8,"sal:load");
lf[297]=C_h_intern(&lf[297],13,"load-sal-file");
lf[298]=C_h_intern(&lf[298],4,"load");
lf[299]=C_h_intern(&lf[299],15,"\003syssubstring=\077");
lf[300]=C_static_string(C_heaptop,4,".sal");
lf[301]=C_static_string(C_heaptop,17,">>> Error: file \042");
lf[302]=C_static_string(C_heaptop,16,"\042does not exist\012");
lf[303]=C_h_intern(&lf[303],12,"file-exists\077");
lf[304]=C_static_lambda_info(C_heaptop,19,"(sal:load file1265)");
lf[305]=C_h_intern(&lf[305],8,"sal:open");
lf[306]=C_static_string(C_heaptop,41,">>> Error: open command not implemented.\012");
lf[307]=C_static_lambda_info(C_heaptop,21,"(sal:open . args1269)");
lf[308]=C_h_intern(&lf[308],10,"sal:output");
lf[309]=C_static_string(C_heaptop,43,">>> Error: output command not implemented.\012");
lf[310]=C_static_lambda_info(C_heaptop,23,"(sal:output . args1270)");
lf[311]=C_h_intern(&lf[311],5,"first");
lf[312]=C_h_intern(&lf[312],6,"second");
lf[313]=C_h_intern(&lf[313],4,"cadr");
lf[314]=C_h_intern(&lf[314],5,"third");
lf[315]=C_h_intern(&lf[315],5,"caddr");
lf[316]=C_h_intern(&lf[316],6,"fourth");
lf[317]=C_h_intern(&lf[317],6,"cadddr");
lf[318]=C_static_lambda_info(C_heaptop,13,"(fifth l1392)");
lf[319]=C_h_intern(&lf[319],5,"sixth");
lf[320]=C_static_lambda_info(C_heaptop,13,"(sixth l1393)");
lf[321]=C_h_intern(&lf[321],7,"seventh");
lf[322]=C_static_lambda_info(C_heaptop,15,"(seventh l1394)");
lf[323]=C_h_intern(&lf[323],6,"eighth");
lf[324]=C_static_lambda_info(C_heaptop,14,"(eighth l1395)");
lf[325]=C_h_intern(&lf[325],5,"ninth");
lf[326]=C_static_lambda_info(C_heaptop,13,"(ninth l1396)");
lf[327]=C_h_intern(&lf[327],5,"tenth");
lf[328]=C_static_lambda_info(C_heaptop,13,"(tenth l1397)");
lf[329]=C_h_intern(&lf[329],4,"last");
lf[330]=C_static_lambda_info(C_heaptop,12,"(last l1399)");
lf[331]=C_h_intern(&lf[331],7,"butlast");
lf[332]=C_static_lambda_info(C_heaptop,15,"(butlast l1400)");
lf[333]=C_h_intern(&lf[333],5,"list*");
lf[334]=C_static_string(C_heaptop,38,">>> Error: too few arguments to list*.");
lf[335]=C_static_lambda_info(C_heaptop,18,"(list* . args1401)");
lf[336]=C_h_intern(&lf[336],17,"current-directory");
lf[337]=C_h_intern(&lf[337],17,"\003syspeek-c-string");
lf[338]=C_static_lambda_info(C_heaptop,8,"(f_6423)");
lf[339]=C_static_lambda_info(C_heaptop,19,"(current-directory)");
lf[340]=C_static_string(C_heaptop,2,"~/");
lf[341]=C_h_intern(&lf[341],17,"\003sysmake-c-string");
lf[342]=C_static_lambda_info(C_heaptop,18,"(f_6438 a14061410)");
lf[343]=C_static_lambda_info(C_heaptop,28,"(change-directory . dir1405)");
lf[344]=C_static_lambda_info(C_heaptop,25,"(print-message a14121416)");
lf[345]=C_static_lambda_info(C_heaptop,23,"(print-error a14181422)");
lf[346]=C_h_intern(&lf[346],25,"current-time-milliseconds");
lf[347]=C_static_lambda_info(C_heaptop,27,"(current-time-milliseconds)");
lf[348]=C_h_intern(&lf[348],20,"current-time-seconds");
lf[349]=C_static_lambda_info(C_heaptop,22,"(current-time-seconds)");
lf[351]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[352]=C_h_intern(&lf[352],6,"\003sysgc");
lf[353]=C_static_lambda_info(C_heaptop,43,"(scheduler-set-time-milliseconds a14481451)");
lf[355]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[356]=C_static_lambda_info(C_heaptop,48,"(scheduler-sprout a14561459 a14551460 a14541461)");
lf[358]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[359]=C_static_lambda_info(C_heaptop,26,"(scheduler-stop a14761479)");
lf[360]=C_static_lambda_info(C_heaptop,18,"(f_6610 a14871491)");
lf[361]=C_static_lambda_info(C_heaptop,24,"(load-sal-file file1486)");
lf[362]=C_h_intern(&lf[362],6,"sprout");
lf[363]=C_static_lambda_info(C_heaptop,11,"(nextstart)");
lf[364]=C_static_lambda_info(C_heaptop,8,"(nextid)");
lf[365]=C_static_lambda_info(C_heaptop,14,"(do1511 p1513)");
lf[366]=C_static_lambda_info(C_heaptop,27,"(body1497 start1503 id1504)");
lf[367]=C_static_lambda_info(C_heaptop,27,"(def-id1500 %start14951519)");
lf[368]=C_static_lambda_info(C_heaptop,15,"(def-start1499)");
lf[369]=C_static_lambda_info(C_heaptop,28,"(sprout proc1493 . args1494)");
lf[370]=C_h_intern(&lf[370],3,"now");
lf[371]=C_h_intern(&lf[371],11,"time-format");
lf[372]=C_flonum(C_heaptop,1.0);
lf[373]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[374]=C_flonum(C_heaptop,1.0);
lf[375]=C_h_intern(&lf[375],1,"m");
lf[376]=C_static_string(C_heaptop,17,"not a time-format");
lf[377]=C_h_intern(&lf[377],1,"s");
lf[378]=C_static_lambda_info(C_heaptop,23,"(time-format . arg1525)");
lf[379]=C_h_intern(&lf[379],5,"pause");
lf[380]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[381]=C_static_lambda_info(C_heaptop,7,"(pause)");
lf[382]=C_h_intern(&lf[382],7,"paused\077");
lf[383]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[384]=C_static_lambda_info(C_heaptop,9,"(paused\077)");
lf[385]=C_h_intern(&lf[385],4,"cont");
lf[386]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[387]=C_static_lambda_info(C_heaptop,6,"(cont)");
lf[388]=C_h_intern(&lf[388],4,"stop");
lf[389]=C_static_string(C_heaptop,17,"Not an integer id");
lf[390]=C_static_lambda_info(C_heaptop,17,"(do1539 tail1541)");
lf[391]=C_static_lambda_info(C_heaptop,19,"(stop . procid1538)");
lf[392]=C_h_intern(&lf[392],4,"hush");
lf[393]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[394]=C_static_lambda_info(C_heaptop,6,"(hush)");
lf[396]=C_h_intern(&lf[396],11,"expand-send");
lf[397]=C_static_lambda_info(C_heaptop,27,"(f_7213 str1558 . args1559)");
lf[398]=C_static_string(C_heaptop,3,"~A:");
lf[399]=C_h_intern(&lf[399],15,"keyword->string");
lf[400]=C_static_lambda_info(C_heaptop,14,"(f_7202 k1562)");
lf[401]=C_static_lambda_info(C_heaptop,14,"(f_7211 k1563)");
lf[402]=C_static_lambda_info(C_heaptop,17,"(do1590 tail1592)");
lf[403]=C_static_string(C_heaptop,25,"~S duplicate keyword \047~S\047");
lf[404]=C_static_string(C_heaptop,33,"~S missing value for keyword \047~A\047");
lf[405]=C_static_string(C_heaptop,47,"~S invalid keyword \047~A\047~%Available keywords: ~A");
lf[406]=C_static_lambda_info(C_heaptop,13,"(a7159 x1580)");
lf[407]=C_static_string(C_heaptop,32,"~S expected keyword but got \047~S\047");
lf[408]=C_h_intern(&lf[408],8,"keyword\077");
lf[409]=C_static_string(C_heaptop,35,"~S expected ~A arguments but got ~A");
lf[410]=C_static_lambda_info(C_heaptop,32,"(do1572 key1574 arg1575 pos1576)");
lf[411]=C_static_string(C_heaptop,24,"~S is an invalid message");
lf[412]=C_static_lambda_info(C_heaptop,7,"(a7193)");
lf[413]=C_h_intern(&lf[413],14,"symbol->string");
lf[414]=C_static_lambda_info(C_heaptop,40,"(expand-send mesg1552 data1553 errf1554)");
lf[415]=C_h_intern(&lf[415],7,"mp:note");
lf[416]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[417]=C_static_lambda_info(C_heaptop,51,"(mp:note time1599 dur1600 key1601 amp1602 chan1603)");
lf[418]=C_h_intern(&lf[418],5,"mp:on");
lf[419]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[420]=C_static_lambda_info(C_heaptop,41,"(mp:on time1604 key1605 vel1606 chan1607)");
lf[421]=C_h_intern(&lf[421],6,"mp:off");
lf[422]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[423]=C_static_lambda_info(C_heaptop,42,"(mp:off time1608 key1609 vel1610 chan1611)");
lf[424]=C_h_intern(&lf[424],7,"mp:prog");
lf[425]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[426]=C_static_lambda_info(C_heaptop,36,"(mp:prog time1612 prog1613 chan1614)");
lf[427]=C_h_intern(&lf[427],7,"mp:ctrl");
lf[428]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[429]=C_static_lambda_info(C_heaptop,44,"(mp:ctrl time1615 ctrl1616 val1617 chan1618)");
lf[430]=C_h_intern(&lf[430],9,"mp:alloff");
lf[431]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[432]=C_static_lambda_info(C_heaptop,11,"(mp:alloff)");
lf[433]=C_h_intern(&lf[433],8,"mp:micro");
lf[434]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[435]=C_static_lambda_info(C_heaptop,19,"(mp:micro divs1619)");
lf[436]=C_h_intern(&lf[436],9,"mp:inhook");
lf[437]=C_static_lambda_info(C_heaptop,41,"(mp:inhook a16221625 a16211626 a16201627)");
lf[438]=C_h_intern(&lf[438],14,"return-to-host");
lf[439]=C_h_intern(&lf[439],4,"else");
lf[440]=C_h_intern(&lf[440],4,"cond");
lf[441]=C_h_intern(&lf[441],6,"lambda");
lf[442]=C_h_intern(&lf[442],7,"elapsed");
lf[443]=C_h_intern(&lf[443],1,"x");
lf[444]=C_h_intern(&lf[444],4,"wait");
lf[445]=C_h_intern(&lf[445],4,"let*");
lf[446]=C_h_intern(&lf[446],5,"quote");
lf[447]=C_h_intern(&lf[447],3,"exn");
lf[448]=C_h_intern(&lf[448],7,"message");
lf[449]=C_h_intern(&lf[449],27,"condition-property-accessor");
lf[450]=C_static_string(C_heaptop,48,">>> Error: ~A~%    Aborting process at time ~S~%");
lf[451]=C_h_intern(&lf[451],22,"with-exception-handler");
lf[452]=C_h_intern(&lf[452],30,"call-with-current-continuation");
lf[453]=C_h_intern(&lf[453],10,"\003sysappend");
lf[454]=C_h_intern(&lf[454],6,"safety");
lf[455]=C_h_intern(&lf[455],4,"cdar");
lf[456]=C_static_string(C_heaptop,19,"unknown declaration");
lf[457]=C_h_intern(&lf[457],4,"caar");
lf[458]=C_static_string(C_heaptop,31,"declaration not list (decl val)");
lf[459]=C_static_lambda_info(C_heaptop,17,"(do1653 decl1655)");
lf[460]=C_h_intern(&lf[460],7,"declare");
lf[461]=C_h_intern(&lf[461],5,"\000null");
lf[462]=C_static_string(C_heaptop,41,"binding clause not list (var init [step])");
lf[463]=C_static_lambda_info(C_heaptop,17,"(do1637 tail1639)");
lf[464]=C_static_string(C_heaptop,36,"go stopping clause missing test form");
lf[465]=C_static_string(C_heaptop,29,"go stopping clause not a list");
lf[466]=C_static_string(C_heaptop,22,"go bindings not a list");
lf[467]=C_static_lambda_info(C_heaptop,45,"(a7764 bindings1628 terminate1629 . body1630)");
lf[468]=C_h_intern(&lf[468],18,"\003sysregister-macro");
lf[469]=C_h_intern(&lf[469],2,"go");
lf[470]=C_h_intern(&lf[470],15,"hash-table-set!");
lf[471]=C_static_string(C_heaptop,9,"mp:inhook");
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
lf[472]=C_h_list(4,C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(4);
lf[473]=C_static_string(C_heaptop,8,"mp:micro");
tmp=C_intern(C_heaptop,8,"mp:micro");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000divs");
C_save(tmp);
tmp=C_fix(1);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[474]=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
lf[475]=C_static_string(C_heaptop,9,"mp:alloff");
tmp=C_intern(C_heaptop,9,"mp:alloff");
C_save(tmp);
tmp=C_SCHEME_END_OF_LIST;
lf[476]=C_h_pair(C_restore,tmp);
lf[477]=C_static_string(C_heaptop,7,"mp:ctrl");
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
lf[478]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[479]=C_static_string(C_heaptop,7,"mp:prog");
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
lf[480]=C_h_list(4,C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(4);
lf[481]=C_static_string(C_heaptop,6,"mp:off");
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
lf[482]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[483]=C_static_string(C_heaptop,5,"mp:on");
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
lf[484]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[485]=C_static_string(C_heaptop,7,"mp:note");
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
lf[486]=C_h_list(6,C_pick(5),C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(6);
lf[487]=C_static_lambda_info(C_heaptop,27,"(a7770 mess1597 . data1598)");
lf[488]=C_h_intern(&lf[488],4,"send");
lf[489]=C_h_intern(&lf[489],10,"*messages*");
lf[490]=C_static_string(C_heaptop,51,"message function not string, symbol or list of both");
lf[491]=C_static_lambda_info(C_heaptop,25,"(a7776 func1546 info1547)");
lf[492]=C_h_intern(&lf[492],19,"define-send-message");
lf[493]=C_h_intern(&lf[493],15,"make-hash-table");
lf[494]=C_h_intern(&lf[494],6,"equal\077");
lf[495]=C_static_lambda_info(C_heaptop,25,"(a7836 args1202 errf1203)");
lf[496]=C_static_lambda_info(C_heaptop,34,"(a7850 unit1204 info1205 errf1206)");
lf[497]=C_static_string(C_heaptop,24,"SalStatementSequenceRule");
lf[498]=C_static_string(C_heaptop,16,"SalStatementRule");
lf[499]=C_static_lambda_info(C_heaptop,25,"(a7956 args1151 errf1152)");
lf[500]=C_h_intern(&lf[500],6,"define");
lf[501]=C_static_string(C_heaptop,15,"Variable: ~A = ");
lf[502]=C_static_lambda_info(C_heaptop,17,"(do1163 rest1165)");
lf[503]=C_static_string(C_heaptop,2,")\012");
lf[504]=C_static_string(C_heaptop,2,", ");
lf[505]=C_static_lambda_info(C_heaptop,26,"(do1189 args1191 tail1192)");
lf[506]=C_static_string(C_heaptop,2," (");
lf[507]=C_static_string(C_heaptop,10,"Function: ");
lf[508]=C_h_intern(&lf[508],7,"\000return");
lf[509]=C_h_intern(&lf[509],6,"return");
lf[510]=C_h_intern(&lf[510],9,"\000function");
lf[511]=C_static_string(C_heaptop,9,"Process: ");
lf[512]=C_h_intern(&lf[512],8,"\000process");
lf[513]=C_static_string(C_heaptop,3,"...");
lf[514]=C_static_lambda_info(C_heaptop,34,"(a7995 unit1156 info1157 errf1158)");
lf[515]=C_static_string(C_heaptop,22,"SalDefineStatementRule");
lf[516]=C_static_lambda_info(C_heaptop,25,"(a8413 args1144 errf1145)");
lf[517]=C_static_string(C_heaptop,14,"SalFunDeclRule");
lf[518]=C_static_lambda_info(C_heaptop,25,"(a8558 args1130 errf1131)");
lf[519]=C_static_string(C_heaptop,47,">>> Error: ~A~%    process aborted at time ~S~%");
lf[520]=C_static_string(C_heaptop,5,"abort");
lf[521]=C_static_string(C_heaptop,5,"error");
lf[522]=C_static_string(C_heaptop,4,"wait");
lf[523]=C_static_string(C_heaptop,4,"time");
lf[524]=C_h_intern(&lf[524],2,"do");
lf[525]=C_static_lambda_info(C_heaptop,17,"(do1108 tail1110)");
lf[526]=C_static_lambda_info(C_heaptop,17,"(do1103 tail1105)");
lf[527]=C_static_lambda_info(C_heaptop,20,"(do1092 clauses1094)");
lf[528]=C_static_lambda_info(C_heaptop,17,"(do1089 tail1091)");
lf[529]=C_h_intern(&lf[529],5,"\000loop");
lf[530]=C_h_intern(&lf[530],4,"\000run");
lf[531]=C_static_string(C_heaptop,29,"run statement outside process");
lf[532]=C_static_lambda_info(C_heaptop,34,"(a8604 unit1140 info1141 errf1142)");
lf[533]=C_static_string(C_heaptop,20,"SalLoopStatementRule");
lf[534]=C_static_string(C_heaptop,18,"SalTerminationRule");
lf[535]=C_static_string(C_heaptop,15,"SalSteppingRule");
lf[536]=C_static_string(C_heaptop,2,"#f");
lf[537]=C_static_string(C_heaptop,2,"#f");
lf[538]=C_static_lambda_info(C_heaptop,25,"(a9058 args1005 errf1006)");
lf[539]=C_static_lambda_info(C_heaptop,34,"(a9126 unit1017 info1018 errf1019)");
lf[540]=C_static_string(C_heaptop,18,"SalConditionalRule");
lf[541]=C_static_lambda_info(C_heaptop,23,"(a9255 args993 errf994)");
lf[542]=C_static_lambda_info(C_heaptop,32,"(a9281 unit998 info999 errf1000)");
lf[543]=C_static_string(C_heaptop,12,"SalBlockRule");
lf[544]=C_static_lambda_info(C_heaptop,23,"(a9369 args971 errf972)");
lf[545]=C_h_intern(&lf[545],9,"list-tail");
lf[546]=C_h_intern(&lf[546],8,"set-car!");
lf[547]=C_h_intern(&lf[547],8,"list-ref");
lf[548]=C_h_intern(&lf[548],4,"list");
lf[549]=C_h_intern(&lf[549],4,"cons");
lf[550]=C_h_intern(&lf[550],3,"min");
lf[551]=C_static_lambda_info(C_heaptop,15,"(do979 iter981)");
lf[552]=C_static_lambda_info(C_heaptop,31,"(a9412 unit973 info974 errf975)");
lf[553]=C_static_string(C_heaptop,17,"SalAssignmentRule");
lf[554]=C_static_lambda_info(C_heaptop,23,"(a9649 args968 errf969)");
lf[555]=C_static_string(C_heaptop,13,"SalAssignRule");
lf[556]=C_static_lambda_info(C_heaptop,23,"(a9735 args960 errf961)");
lf[557]=C_static_lambda_info(C_heaptop,12,"(a9787 e966)");
lf[558]=C_h_intern(&lf[558],9,"\000bindings");
lf[559]=C_static_lambda_info(C_heaptop,31,"(a9778 unit962 info963 errf964)");
lf[560]=C_static_string(C_heaptop,15,"SalBindingsRule");
lf[561]=C_static_string(C_heaptop,2,"#f");
lf[562]=C_static_lambda_info(C_heaptop,23,"(a9837 args953 errf954)");
lf[563]=C_static_lambda_info(C_heaptop,12,"(a9878 e958)");
lf[564]=C_static_lambda_info(C_heaptop,31,"(a9872 unit955 info956 errf957)");
lf[565]=C_static_string(C_heaptop,11,"SalBindRule");
lf[566]=C_static_string(C_heaptop,33,"return statement outside function");
lf[567]=C_static_lambda_info(C_heaptop,31,"(a9932 unit946 info947 errf948)");
lf[568]=C_static_string(C_heaptop,21,"SalFunctionReturnRule");
lf[569]=C_static_string(C_heaptop,32,"wait statement outside run block");
lf[570]=C_static_lambda_info(C_heaptop,31,"(a9993 unit940 info941 errf942)");
lf[571]=C_static_string(C_heaptop,18,"SalProcessWaitRule");
lf[572]=C_static_lambda_info(C_heaptop,24,"(a10047 args934 errf935)");
tmp=C_intern(C_heaptop,6,"fix-me");
C_save(tmp);
tmp=C_intern(C_heaptop,4,"plot");
C_save(tmp);
lf[573]=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
lf[574]=C_static_lambda_info(C_heaptop,32,"(a10077 unit936 info937 errf938)");
lf[575]=C_static_string(C_heaptop,20,"SalPlotStatementRule");
lf[576]=C_static_string(C_heaptop,22,"SalOutputStatementRule");
lf[577]=C_static_string(C_heaptop,22,"SalSystemStatementRule");
lf[578]=C_h_intern(&lf[578],10,"sal:system");
lf[579]=C_static_string(C_heaptop,21,"SalChdirStatementRule");
lf[580]=C_static_string(C_heaptop,20,"SalLoadStatementRule");
lf[581]=C_static_lambda_info(C_heaptop,24,"(a10296 args927 errf928)");
lf[582]=C_static_string(C_heaptop,20,"SalExecStatementRule");
lf[583]=C_static_lambda_info(C_heaptop,24,"(a10322 args914 errf915)");
lf[584]=C_static_lambda_info(C_heaptop,25,"(a10403 str924 . args925)");
lf[585]=C_static_lambda_info(C_heaptop,32,"(a10383 unit919 info920 errf921)");
lf[586]=C_static_string(C_heaptop,20,"SalSendStatementRule");
lf[587]=C_static_lambda_info(C_heaptop,24,"(a10521 args906 errf907)");
lf[588]=C_static_lambda_info(C_heaptop,32,"(a10548 unit909 info910 errf911)");
lf[589]=C_static_string(C_heaptop,22,"SalSproutStatementRule");
lf[590]=C_static_lambda_info(C_heaptop,24,"(a10630 args892 errf893)");
lf[591]=C_static_lambda_info(C_heaptop,15,"(do899 args901)");
lf[592]=C_static_lambda_info(C_heaptop,32,"(a10652 unit894 info895 errf896)");
lf[593]=C_static_string(C_heaptop,21,"SalPrintStatementRule");
lf[594]=C_static_string(C_heaptop,12,"SalSexprRule");
lf[595]=C_static_lambda_info(C_heaptop,24,"(a10784 args885 errf886)");
lf[596]=C_static_lambda_info(C_heaptop,32,"(a10810 unit887 info888 errf889)");
lf[597]=C_static_string(C_heaptop,11,"SalTermRule");
lf[598]=C_static_lambda_info(C_heaptop,24,"(a10920 args881 errf882)");
lf[599]=C_static_string(C_heaptop,12,"SalMexprRule");
lf[600]=C_static_string(C_heaptop,9,"SalOpRule");
lf[601]=C_static_lambda_info(C_heaptop,24,"(a11076 args844 errf845)");
lf[602]=C_static_lambda_info(C_heaptop,32,"(a11094 unit846 info847 errf848)");
lf[603]=C_static_string(C_heaptop,14,"SalFuncallRule");
lf[604]=C_static_lambda_info(C_heaptop,24,"(a11147 args838 errf839)");
lf[605]=C_static_string(C_heaptop,14,"SalFunargsRule");
lf[606]=C_static_lambda_info(C_heaptop,24,"(a11299 args835 errf836)");
lf[607]=C_static_string(C_heaptop,12,"SalKargsRule");
lf[608]=C_static_lambda_info(C_heaptop,24,"(a11438 args832 errf833)");
lf[609]=C_static_string(C_heaptop,12,"SalPargsRule");
lf[610]=C_static_lambda_info(C_heaptop,24,"(a11558 args811 errf812)");
lf[611]=C_static_lambda_info(C_heaptop,32,"(a11589 unit814 info815 errf816)");
lf[612]=C_static_string(C_heaptop,13,"SalIfExprRule");
lf[613]=C_static_lambda_info(C_heaptop,24,"(a11681 args805 errf806)");
lf[614]=C_static_lambda_info(C_heaptop,32,"(a11699 unit807 info808 errf809)");
lf[615]=C_static_string(C_heaptop,11,"SalArefRule");
lf[616]=C_static_string(C_heaptop,10,"SalEltRule");
lf[617]=C_h_intern(&lf[617],7,"unquote");
lf[618]=C_h_intern(&lf[618],16,"unquote-splicing");
lf[619]=C_h_intern(&lf[619],5,"\000list");
lf[620]=C_h_intern(&lf[620],8,"\000unquote");
lf[621]=C_static_string(C_heaptop,19,"#$ outside of list.");
lf[622]=C_static_string(C_heaptop,19,"#^ outside of list.");
lf[623]=C_static_lambda_info(C_heaptop,32,"(a11773 unit794 info795 errf796)");
lf[624]=C_static_string(C_heaptop,14,"SalUnquoteRule");
lf[625]=C_static_lambda_info(C_heaptop,24,"(a11869 args782 errf783)");
lf[626]=C_h_intern(&lf[626],10,"quasiquote");
lf[627]=C_static_lambda_info(C_heaptop,32,"(a11879 unit784 info785 errf786)");
lf[628]=C_static_string(C_heaptop,11,"SalListRule");
lf[629]=C_static_string(C_heaptop,11,"SalAtomRule");
lf[630]=C_static_string(C_heaptop,11,"SalBoolRule");
lf[631]=C_static_string(C_heaptop,13,"SalNumberRule");
lf[632]=C_h_intern(&lf[632],7,"fprintf");
lf[633]=C_static_string(C_heaptop,7,"#<u ~A>");
lf[634]=C_static_string(C_heaptop,8,"#<u x~X>");
lf[635]=C_static_lambda_info(C_heaptop,18,"(a12055 u432 p433)");
lf[636]=C_h_intern(&lf[636],27,"\003sysregister-record-printer");
lf[637]=C_static_string(C_heaptop,24,"#<parse-error ~S (@ ~S)>");
lf[638]=C_static_lambda_info(C_heaptop,18,"(a12081 e404 p405)");
lf[639]=C_static_string(C_heaptop,7,"#<r ~A>");
lf[640]=C_static_lambda_info(C_heaptop,18,"(a12095 r368 p369)");
lf[641]=C_h_intern(&lf[641],3,"eq\077");
lf[642]=C_static_string(C_heaptop,11,"#<t x~X ~S>");
lf[643]=C_static_lambda_info(C_heaptop,18,"(a12105 t319 p320)");
lf[644]=C_static_lambda_info(C_heaptop,10,"(toplevel)");
C_register_lf2(lf,645,create_ptable());
t2=C_mutate(&lf[0],lf[1]);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1740,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_library_toplevel(2,C_SCHEME_UNDEFINED,t3);}

/* k1738 */
static void C_ccall f_1740(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1740,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1743,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_eval_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k1741 in k1738 */
static void C_ccall f_1743(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1743,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1746,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k1744 in k1741 in k1738 */
static void C_ccall f_1746(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1746,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1749,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_1749(C_word c,C_word t0,C_word t1){
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
C_word ab[138],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1749,2,t0,t1);}
t2=C_mutate(&lf[2],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1751,a[2]=lf[3],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate(&lf[4],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1778,a[2]=lf[5],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate(&lf[6],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1812,a[2]=lf[7],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate(&lf[8],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1887,a[2]=lf[9],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate(&lf[10],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1894,a[2]=lf[11],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate(&lf[12],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1932,a[2]=lf[13],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate(&lf[14],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1943,a[2]=lf[15],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate(&lf[16],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1950,a[2]=lf[17],tmp=(C_word)a,a+=3,tmp));
t10=C_mutate(&lf[18],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1961,a[2]=lf[19],tmp=(C_word)a,a+=3,tmp));
t11=C_mutate(&lf[20],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1971,a[2]=lf[21],tmp=(C_word)a,a+=3,tmp));
t12=C_mutate((C_word*)lf[22]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1984,a[2]=lf[23],tmp=(C_word)a,a+=3,tmp));
t13=C_mutate((C_word*)lf[24]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2003,a[2]=lf[25],tmp=(C_word)a,a+=3,tmp));
t14=C_mutate((C_word*)lf[26]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2085,a[2]=lf[27],tmp=(C_word)a,a+=3,tmp));
t15=C_mutate((C_word*)lf[28]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2091,a[2]=lf[29],tmp=(C_word)a,a+=3,tmp));
t16=C_mutate((C_word*)lf[30]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2097,a[2]=lf[31],tmp=(C_word)a,a+=3,tmp));
t17=C_mutate((C_word*)lf[32]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2116,a[2]=lf[39],tmp=(C_word)a,a+=3,tmp));
t18=C_mutate((C_word*)lf[40]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2176,a[2]=lf[41],tmp=(C_word)a,a+=3,tmp));
t19=C_mutate((C_word*)lf[42]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2182,a[2]=lf[43],tmp=(C_word)a,a+=3,tmp));
t20=C_mutate((C_word*)lf[44]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2188,a[2]=lf[45],tmp=(C_word)a,a+=3,tmp));
t21=C_mutate((C_word*)lf[46]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2194,a[2]=lf[47],tmp=(C_word)a,a+=3,tmp));
t22=C_mutate((C_word*)lf[48]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2200,a[2]=lf[49],tmp=(C_word)a,a+=3,tmp));
t23=C_mutate((C_word*)lf[50]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2206,a[2]=lf[57],tmp=(C_word)a,a+=3,tmp));
t24=C_mutate((C_word*)lf[58]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2301,a[2]=lf[59],tmp=(C_word)a,a+=3,tmp));
t25=C_mutate((C_word*)lf[60]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2307,a[2]=lf[63],tmp=(C_word)a,a+=3,tmp));
t26=C_mutate((C_word*)lf[64]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2366,a[2]=lf[65],tmp=(C_word)a,a+=3,tmp));
t27=C_mutate((C_word*)lf[66]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2372,a[2]=lf[68],tmp=(C_word)a,a+=3,tmp));
t28=C_mutate((C_word*)lf[69]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2460,a[2]=lf[73],tmp=(C_word)a,a+=3,tmp));
t29=C_mutate((C_word*)lf[74]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2518,a[2]=lf[76],tmp=(C_word)a,a+=3,tmp));
t30=C_mutate((C_word*)lf[77]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2541,a[2]=lf[78],tmp=(C_word)a,a+=3,tmp));
t31=C_mutate((C_word*)lf[79]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2547,a[2]=lf[80],tmp=(C_word)a,a+=3,tmp));
t32=C_mutate((C_word*)lf[81]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2553,a[2]=lf[82],tmp=(C_word)a,a+=3,tmp));
t33=C_mutate((C_word*)lf[83]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2559,a[2]=lf[84],tmp=(C_word)a,a+=3,tmp));
t34=C_mutate((C_word*)lf[85]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2565,a[2]=lf[88],tmp=(C_word)a,a+=3,tmp));
t35=C_mutate((C_word*)lf[89]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2609,a[2]=lf[90],tmp=(C_word)a,a+=3,tmp));
t36=C_mutate((C_word*)lf[91]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2628,a[2]=lf[92],tmp=(C_word)a,a+=3,tmp));
t37=C_mutate((C_word*)lf[93]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2668,a[2]=lf[94],tmp=(C_word)a,a+=3,tmp));
t38=C_mutate((C_word*)lf[95]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2674,a[2]=lf[97],tmp=(C_word)a,a+=3,tmp));
t39=C_mutate((C_word*)lf[98]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2693,a[2]=lf[99],tmp=(C_word)a,a+=3,tmp));
t40=C_mutate((C_word*)lf[100]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2712,a[2]=lf[101],tmp=(C_word)a,a+=3,tmp));
t41=C_mutate((C_word*)lf[102]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2718,a[2]=lf[103],tmp=(C_word)a,a+=3,tmp));
t42=C_mutate(&lf[104],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2724,a[2]=lf[106],tmp=(C_word)a,a+=3,tmp));
t43=C_mutate(&lf[107],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2745,a[2]=lf[108],tmp=(C_word)a,a+=3,tmp));
t44=C_mutate(&lf[109],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2763,a[2]=lf[110],tmp=(C_word)a,a+=3,tmp));
t45=C_mutate(&lf[111],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2781,a[2]=lf[112],tmp=(C_word)a,a+=3,tmp));
t46=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2791,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t47=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_12106,a[2]=lf[643],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  ##sys#register-record-printer");
t48=C_retrieve(lf[636]);
((C_proc4)C_retrieve_proc(t48))(4,t48,t46,lf[105],t47);}

/* a12105 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_12106(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_12106,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_12114,a[2]=t2,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  token-type");
f_2745(t4,t2);}

/* k12112 in a12105 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_12114(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_12114,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_12118,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  token-string");
f_2763(t2,((C_word*)t0)[2]);}

/* k12116 in k12112 in a12105 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_12118(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  fprintf");
t2=C_retrieve(lf[632]);
((C_proc6)C_retrieve_proc(t2))(6,t2,((C_word*)t0)[4],((C_word*)t0)[3],lf[642],((C_word*)t0)[2],t1);}

/* k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2791(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2791,2,t0,t1);}
t2=C_mutate(&lf[113],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2793,a[2]=lf[115],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate(&lf[116],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2822,a[2]=lf[117],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate(&lf[118],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2834,a[2]=lf[119],tmp=(C_word)a,a+=3,tmp));
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2842,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-hash-table");
t6=C_retrieve(lf[493]);
((C_proc3)C_retrieve_proc(t6))(3,t6,t5,*((C_word*)lf[641]+1));}

/* k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2842(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2842,2,t0,t1);}
t2=C_mutate(&lf[120],t1);
t3=C_mutate(&lf[121],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2844,a[2]=lf[123],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate(&lf[124],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2865,a[2]=lf[125],tmp=(C_word)a,a+=3,tmp));
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2947,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_12096,a[2]=lf[640],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  ##sys#register-record-printer");
t7=C_retrieve(lf[636]);
((C_proc4)C_retrieve_proc(t7))(4,t7,t5,lf[122],t6);}

/* a12095 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_12096(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_12096,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_12104,a[2]=t3,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  rule-name");
f_2865(t4,t2);}

/* k12102 in a12095 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_12104(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  fprintf");
t2=C_retrieve(lf[632]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[3],((C_word*)t0)[2],lf[639],t1);}

/* k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2947(C_word c,C_word t0,C_word t1){
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
C_word ab[33],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2947,2,t0,t1);}
t2=C_mutate(&lf[126],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2949,a[2]=lf[129],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate(&lf[130],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2973,a[2]=lf[131],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate(&lf[132],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2985,a[2]=lf[133],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate(&lf[134],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2991,a[2]=lf[135],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate(&lf[136],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3001,a[2]=lf[137],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate(&lf[138],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3059,a[2]=lf[140],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate(&lf[141],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3091,a[2]=lf[143],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate(&lf[144],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3112,a[2]=lf[145],tmp=(C_word)a,a+=3,tmp));
t10=C_mutate(&lf[146],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3130,a[2]=lf[147],tmp=(C_word)a,a+=3,tmp));
t11=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3140,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t12=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_12082,a[2]=lf[638],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  ##sys#register-record-printer");
t13=C_retrieve(lf[636]);
((C_proc4)C_retrieve_proc(t13))(4,t13,t11,lf[142],t12);}

/* a12081 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_12082(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_12082,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_12090,a[2]=t2,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-error-string");
f_3112(t4,t2);}

/* k12088 in a12081 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_12090(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_12090,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_12094,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-error-position");
f_3130(t2,((C_word*)t0)[2]);}

/* k12092 in k12088 in a12081 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_12094(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  fprintf");
t2=C_retrieve(lf[632]);
((C_proc6)C_retrieve_proc(t2))(6,t2,((C_word*)t0)[4],((C_word*)t0)[3],lf[637],((C_word*)t0)[2],t1);}

/* k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3140(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3140,2,t0,t1);}
t2=C_mutate(&lf[148],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3142,a[2]=lf[150],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate(&lf[151],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3148,a[2]=lf[152],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate(&lf[153],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3163,a[2]=lf[154],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate(&lf[155],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3181,a[2]=lf[156],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate(&lf[157],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3199,a[2]=lf[158],tmp=(C_word)a,a+=3,tmp));
t7=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3209,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_12056,a[2]=lf[635],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  ##sys#register-record-printer");
t9=C_retrieve(lf[636]);
((C_proc4)C_retrieve_proc(t9))(4,t9,t7,lf[149],t8);}

/* a12055 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_12056(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_12056,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_12060,a[2]=t3,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-type");
f_3163(t4,t2);}

/* k12058 in a12055 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_12060(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_12060,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_12066,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  SalRuleType?");
f_4421(t2,t1);}

/* k12064 in k12058 in a12055 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_12066(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_12066,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_12073,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_12077,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  get-rule");
f_2949(t3,((C_word*)t0)[2],C_SCHEME_END_OF_LIST);}
else{
C_trace("ChickenBridge.scm: 145  fprintf");
t2=C_retrieve(lf[632]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[4],((C_word*)t0)[3],lf[634],((C_word*)t0)[2]);}}

/* k12075 in k12064 in k12058 in a12055 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_12077(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  rule-name");
f_2865(((C_word*)t0)[2],t1);}

/* k12071 in k12064 in k12058 in a12055 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_12073(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  fprintf");
t2=C_retrieve(lf[632]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[3],((C_word*)t0)[2],lf[633],t1);}

/* k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3209(C_word c,C_word t0,C_word t1){
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
C_word ab[60],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3209,2,t0,t1);}
t2=C_mutate(&lf[159],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3211,a[2]=lf[161],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate(&lf[162],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3227,a[2]=lf[164],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate(&lf[165],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3259,a[2]=lf[166],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate(&lf[167],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3271,a[2]=lf[168],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate(&lf[169],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3281,a[2]=lf[171],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate(&lf[172],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3299,a[2]=lf[186],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate(&lf[183],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3332,a[2]=lf[187],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate(&lf[188],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3540,a[2]=lf[190],tmp=(C_word)a,a+=3,tmp));
t10=C_mutate(&lf[191],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3548,a[2]=lf[195],tmp=(C_word)a,a+=3,tmp));
t11=lf[196]=C_SCHEME_FALSE;;
t12=C_mutate(&lf[197],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3652,a[2]=lf[220],tmp=(C_word)a,a+=3,tmp));
t13=C_mutate(&lf[160],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4271,a[2]=lf[221],tmp=(C_word)a,a+=3,tmp));
t14=C_mutate(&lf[182],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4319,a[2]=lf[222],tmp=(C_word)a,a+=3,tmp));
t15=C_mutate(&lf[185],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4421,a[2]=lf[223],tmp=(C_word)a,a+=3,tmp));
t16=C_mutate(&lf[163],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4433,a[2]=lf[224],tmp=(C_word)a,a+=3,tmp));
t17=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4454,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t18=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_12034,a[2]=t17,tmp=(C_word)a,a+=3,tmp);
t19=(C_word)C_a_i_cons(&a,2,C_fix(3072),C_SCHEME_END_OF_LIST);
t20=(C_word)C_a_i_cons(&a,2,C_fix(3328),t19);
t21=(C_word)C_a_i_cons(&a,2,C_fix(2816),t20);
t22=(C_word)C_a_i_cons(&a,2,lf[177],t21);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t18,lf[631],C_fix(25856),t22,C_SCHEME_FALSE,C_SCHEME_FALSE);}

/* k12032 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_12034(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(25856),t1);}

/* k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4454(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[15],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4454,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4457,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_12014,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(4608),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(4352),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[177],t5);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t3,lf[630],C_fix(26112),t6,C_SCHEME_FALSE,C_SCHEME_FALSE);}

/* k12012 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_12014(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(26112),t1);}

/* k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4457(C_word c,C_word t0,C_word t1){
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
C_word ab[30],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4457,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4460,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11974,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(4608),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(4352),t4);
t6=(C_word)C_a_i_cons(&a,2,C_fix(25088),t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(3840),t6);
t8=(C_word)C_a_i_cons(&a,2,C_fix(3072),t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(3328),t8);
t10=(C_word)C_a_i_cons(&a,2,C_fix(2816),t9);
t11=(C_word)C_a_i_cons(&a,2,lf[177],t10);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t3,lf[629],C_fix(26368),t11,C_SCHEME_FALSE,C_SCHEME_FALSE);}

/* k11972 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11974(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(26368),t1);}

/* k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4460(C_word c,C_word t0,C_word t1){
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
C_word ab[30],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4460,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4463,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11864,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(26880),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,lf[139],t4);
t6=(C_word)C_a_i_cons(&a,2,C_fix(1280),C_SCHEME_END_OF_LIST);
t7=(C_word)C_a_i_cons(&a,2,t5,t6);
t8=(C_word)C_a_i_cons(&a,2,C_fix(1024),t7);
t9=(C_word)C_a_i_cons(&a,2,lf[176],t8);
t10=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11870,a[2]=lf[625],tmp=(C_word)a,a+=3,tmp);
t11=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11880,a[2]=lf[627],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t3,lf[628],C_fix(26624),t9,t10,t11);}

/* a11879 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11880(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[6],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_11880,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_11884,a[2]=t2,a[3]=t4,a[4]=t3,a[5]=t1,tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  get-emit-info");
f_3259(t5,lf[619],t3);}

/* k11882 in a11879 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11884(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11884,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_11887,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=t1,tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3181(t2,((C_word*)t0)[2]);}

/* k11885 in k11882 in a11879 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11887(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11887,2,t0,t1);}
t2=((C_word*)t0)[5];
if(C_truep(t2)){
C_trace("ChickenBridge.scm: 145  emit");
f_3299(((C_word*)t0)[4],t1,((C_word*)t0)[3],((C_word*)t0)[2]);}
else{
if(C_truep((C_word)C_i_nullp(t1))){
t3=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_list(&a,1,lf[548]));}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_11905,a[2]=((C_word*)t0)[2],a[3]=t1,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  add-emit-info");
f_3271(t3,lf[619],C_SCHEME_TRUE,((C_word*)t0)[3]);}}}

/* k11903 in k11885 in k11882 in a11879 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11905(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11905,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11908,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t2,((C_word*)t0)[3],t1,((C_word*)t0)[2]);}

/* k11906 in k11903 in k11885 in k11882 in a11879 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11908(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11908,2,t0,t1);}
t2=C_SCHEME_FALSE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11911,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11939,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  get-emit-info");
f_3259(t5,lf[619],((C_word*)t0)[2]);}

/* k11937 in k11906 in k11903 in k11885 in k11882 in a11879 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11939(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11939,2,t0,t1);}
t2=(C_word)C_eqp(t1,lf[620]);
if(C_truep(t2)){
t3=(C_word)C_a_i_list(&a,2,lf[626],((C_word*)t0)[4]);
t4=C_mutate(((C_word *)((C_word*)t0)[3])+1,t3);
t5=((C_word*)t0)[2];
f_11911(t5,t4);}
else{
t3=(C_word)C_a_i_list(&a,2,lf[446],((C_word*)t0)[4]);
t4=C_mutate(((C_word *)((C_word*)t0)[3])+1,t3);
t5=((C_word*)t0)[2];
f_11911(t5,t4);}}

/* k11909 in k11906 in k11903 in k11885 in k11882 in a11879 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_11911(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_11911,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_11917,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  get-emit-info");
f_3259(t2,lf[558],((C_word*)t0)[2]);}

/* k11915 in k11909 in k11906 in k11903 in k11885 in k11882 in a11879 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11917(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11917,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,1,lf[548]);
t3=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_list(&a,3,lf[193],((C_word*)((C_word*)t0)[2])[1],t2));}
else{
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,((C_word*)((C_word*)t0)[2])[1]);}}

/* a11869 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11870(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word *a;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_11870,4,t0,t1,t2,t3);}
t4=(C_word)C_i_cadr(t2);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3142(t1,C_fix(26624),t4,C_SCHEME_FALSE);}

/* k11862 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11864(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(26624),t1);}

/* k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4463(C_word c,C_word t0,C_word t1){
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
C_word ab[28],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4463,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4466,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11764,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(5632),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(5376),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[177],t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,t6,t7);
t9=(C_word)C_a_i_cons(&a,2,lf[176],t8);
t10=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_11772,a[2]=t9,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  simple-unit-parser");
f_3540(t10,C_fix(27648));}

/* k11770 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11772(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11772,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11774,a[2]=lf[623],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(((C_word*)t0)[3],lf[624],C_fix(27648),((C_word*)t0)[2],t1,t2);}

/* a11773 in k11770 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11774(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_11774,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11778,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3181(t5,t2);}

/* k11776 in a11773 in k11770 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11778(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11778,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_11781,a[2]=((C_word*)t0)[2],a[3]=t1,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=(C_word)C_i_car(t1);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3227(t2,t3,C_fix(5376));}

/* k11779 in k11776 in a11773 in k11770 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11781(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11781,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_11784,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=((C_word*)t0)[5],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  get-emit-info");
f_3259(t2,lf[619],((C_word*)t0)[4]);}

/* k11782 in k11779 in k11776 in a11773 in k11770 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11784(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[15],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11784,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_11787,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
if(C_truep(t1)){
t3=t2;
f_11787(2,t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_11816,a[2]=t2,a[3]=((C_word*)t0)[2],tmp=(C_word)a,a+=4,tmp);
t4=(C_truep(((C_word*)t0)[5])?lf[621]:lf[622]);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_11824,a[2]=t4,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t6=(C_word)C_i_car(((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 145  parse-unit-position");
f_3199(t5,t6);}}

/* k11822 in k11782 in k11779 in k11776 in a11773 in k11770 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11824(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-parse-error");
f_3091(((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k11814 in k11782 in k11779 in k11776 in a11773 in k11770 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11816(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  errf");
t2=((C_word*)t0)[3];
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k11785 in k11782 in k11779 in k11776 in a11773 in k11770 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11787(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11787,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11790,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
t3=(C_word)C_i_cadr(((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t2,t3,((C_word*)t0)[4],((C_word*)t0)[2]);}

/* k11788 in k11785 in k11782 in k11779 in k11776 in a11773 in k11770 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11790(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11790,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11793,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  set-emit-info!");
f_3281(t2,lf[619],lf[620],((C_word*)t0)[2]);}

/* k11791 in k11788 in k11785 in k11782 in k11779 in k11776 in a11773 in k11770 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11793(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11793,2,t0,t1);}
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_truep(((C_word*)t0)[3])?(C_word)C_a_i_list(&a,2,lf[617],((C_word*)t0)[2]):(C_word)C_a_i_list(&a,2,lf[618],((C_word*)t0)[2])));}

/* k11762 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11764(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(27648),t1);}

/* k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4466(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4466,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4469,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11736,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(27648),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(2304),t4);
t6=(C_word)C_a_i_cons(&a,2,C_fix(26624),t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(26368),t6);
t8=(C_word)C_a_i_cons(&a,2,lf[177],t7);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t3,lf[616],C_fix(26880),t8,C_SCHEME_FALSE,C_SCHEME_FALSE);}

/* k11734 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11736(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(26880),t1);}

/* k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4469(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4469,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4472,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11676,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(1792),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(29696),t4);
t6=(C_word)C_a_i_cons(&a,2,C_fix(1536),t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(25088),t6);
t8=(C_word)C_a_i_cons(&a,2,lf[176],t7);
t9=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11682,a[2]=lf[613],tmp=(C_word)a,a+=3,tmp);
t10=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11700,a[2]=lf[614],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t3,lf[615],C_fix(27136),t8,t9,t10);}

/* a11699 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11700(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[8],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_11700,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11708,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11712,a[2]=t4,a[3]=t3,a[4]=t5,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3181(t6,t2);}

/* k11710 in a11699 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11712(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  emit");
f_3299(((C_word*)t0)[4],t1,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k11706 in a11699 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11708(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11708,2,t0,t1);}
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_cons(&a,2,lf[547],t1));}

/* a11681 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11682(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_11682,4,t0,t1,t2,t3);}
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_caddr(t2);
t6=(C_word)C_a_i_list(&a,2,t4,t5);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3142(t1,C_fix(27136),t6,C_SCHEME_FALSE);}

/* k11674 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11676(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(27136),t1);}

/* k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4472(C_word c,C_word t0,C_word t1){
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
C_word ab[45],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4472,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4475,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11553,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(256),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[214],t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(768),C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,t6,t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(29696),t8);
t10=(C_word)C_a_i_cons(&a,2,C_fix(256),t9);
t11=(C_word)C_a_i_cons(&a,2,C_fix(29696),t10);
t12=(C_word)C_a_i_cons(&a,2,C_fix(512),t11);
t13=(C_word)C_a_i_cons(&a,2,C_fix(5120),t12);
t14=(C_word)C_a_i_cons(&a,2,lf[176],t13);
t15=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11559,a[2]=lf[610],tmp=(C_word)a,a+=3,tmp);
t16=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11590,a[2]=lf[611],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t3,lf[612],C_fix(27392),t14,t15,t16);}

/* a11589 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11590(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_11590,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11594,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3181(t5,t2);}

/* k11592 in a11589 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11594(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11594,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_11597,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,tmp=(C_word)a,a+=6,tmp);
t3=(C_word)C_i_car(t1);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k11595 in k11592 in a11589 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11597(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11597,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_11600,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],tmp=(C_word)a,a+=7,tmp);
t3=(C_word)C_i_cadr(((C_word*)t0)[5]);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k11598 in k11595 in k11592 in a11589 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11600(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11600,2,t0,t1);}
t2=(C_word)C_i_caddr(((C_word*)t0)[6]);
if(C_truep(t2)){
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11613,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t3,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}
else{
t3=((C_word*)t0)[5];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_list(&a,4,lf[241],((C_word*)t0)[4],t1,C_SCHEME_FALSE));}}

/* k11611 in k11598 in k11595 in k11592 in a11589 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11613(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11613,2,t0,t1);}
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_list(&a,4,lf[241],((C_word*)t0)[3],((C_word*)t0)[2],t1));}

/* a11558 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11559(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_11559,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_11563,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  sixth");
t5=C_retrieve(lf[319]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,t2);}

/* k11561 in a11558 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11563(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11563,2,t0,t1);}
t2=(C_word)C_i_caddr(((C_word*)t0)[3]);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11578,a[2]=((C_word*)t0)[2],a[3]=t2,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  fifth");
t4=C_retrieve(lf[243]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)t0)[3]);}

/* k11576 in k11561 in a11558 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11578(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11578,2,t0,t1);}
t2=(C_word)C_i_pairp(((C_word*)t0)[4]);
t3=(C_truep(t2)?(C_word)C_i_cadr(((C_word*)t0)[4]):C_SCHEME_FALSE);
t4=(C_word)C_a_i_list(&a,3,((C_word*)t0)[3],t1,t3);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3142(((C_word*)t0)[2],C_fix(27392),t4,C_SCHEME_FALSE);}

/* k11551 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11553(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(27392),t1);}

/* k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4475(C_word c,C_word t0,C_word t1){
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
C_word ab[39],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4475,2,t0,t1);}
t2=C_mutate(&lf[225],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4477,a[2]=lf[227],tmp=(C_word)a,a+=3,tmp));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4531,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11433,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
t5=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t6=(C_word)C_a_i_cons(&a,2,C_fix(256),t5);
t7=(C_word)C_a_i_cons(&a,2,lf[215],t6);
t8=(C_word)C_a_i_cons(&a,2,t7,C_SCHEME_END_OF_LIST);
t9=(C_word)C_a_i_cons(&a,2,C_fix(29696),t8);
t10=(C_word)C_a_i_cons(&a,2,lf[176],t9);
t11=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t12=(C_word)C_a_i_cons(&a,2,t10,t11);
t13=(C_word)C_a_i_cons(&a,2,lf[177],t12);
t14=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11439,a[2]=lf[608],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t4,lf[609],C_fix(28416),t13,t14,C_SCHEME_FALSE);}

/* a11438 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11439(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[7],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_11439,4,t0,t1,t2,t3);}
if(C_truep((C_word)C_i_pairp(t2))){
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_11455,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(C_word)C_i_cadr(t2);
if(C_truep((C_word)C_i_pairp(t6))){
t7=(C_word)C_i_cadr(t2);
t8=(C_word)C_i_car(t7);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3227(t4,t8,C_fix(256));}
else{
t7=t4;
f_11455(2,t7,C_SCHEME_FALSE);}}
else{
t6=t4;
f_11455(2,t6,C_SCHEME_FALSE);}}
else{
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_a_i_list(&a,1,t2));}}

/* k11453 in a11438 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11455(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11455,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_11466,a[2]=t2,a[3]=((C_word*)t0)[2],tmp=(C_word)a,a+=4,tmp);
t4=(C_word)C_i_cadr(((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 145  remove-token-type");
f_4477(t3,t4,C_fix(256));}
else{
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]));}}

/* k11464 in k11453 in a11438 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11466(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11466,2,t0,t1);}
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[2],t1));}

/* k11431 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11433(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(28416),t1);}

/* k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4531(C_word c,C_word t0,C_word t1){
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
C_word ab[51],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4531,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4534,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11294,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(6144),t4);
t6=(C_word)C_a_i_cons(&a,2,C_fix(256),t5);
t7=(C_word)C_a_i_cons(&a,2,lf[215],t6);
t8=(C_word)C_a_i_cons(&a,2,t7,C_SCHEME_END_OF_LIST);
t9=(C_word)C_a_i_cons(&a,2,C_fix(29696),t8);
t10=(C_word)C_a_i_cons(&a,2,C_fix(6144),t9);
t11=(C_word)C_a_i_cons(&a,2,lf[176],t10);
t12=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t13=(C_word)C_a_i_cons(&a,2,C_fix(6144),t12);
t14=(C_word)C_a_i_cons(&a,2,lf[176],t13);
t15=(C_word)C_a_i_cons(&a,2,t14,C_SCHEME_END_OF_LIST);
t16=(C_word)C_a_i_cons(&a,2,t11,t15);
t17=(C_word)C_a_i_cons(&a,2,lf[177],t16);
t18=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11300,a[2]=lf[606],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t3,lf[607],C_fix(28672),t17,t18,C_SCHEME_FALSE);}

/* a11299 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11300(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_word ab[9],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_11300,4,t0,t1,t2,t3);}
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cadr(t2);
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11320,a[2]=t4,a[3]=t1,a[4]=t5,tmp=(C_word)a,a+=5,tmp);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_11323,a[2]=t6,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t8=(C_word)C_i_cddr(t2);
if(C_truep((C_word)C_i_pairp(t8))){
t9=(C_word)C_i_caddr(t2);
if(C_truep((C_word)C_i_pairp(t9))){
t10=(C_word)C_i_caddr(t2);
t11=(C_word)C_i_car(t10);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3227(t7,t11,C_fix(256));}
else{
t10=t7;
f_11323(2,t10,C_SCHEME_FALSE);}}
else{
t9=t7;
f_11323(2,t9,C_SCHEME_FALSE);}}

/* k11321 in a11299 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11323(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_caddr(((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 145  remove-token-type");
f_4477(((C_word*)t0)[2],t2,C_fix(256));}
else{
t2=((C_word*)t0)[2];
f_11320(2,t2,C_SCHEME_END_OF_LIST);}}

/* k11318 in a11299 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11320(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11320,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[4],t1);
t3=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[2],t2));}

/* k11292 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11294(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(28672),t1);}

/* k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4534(C_word c,C_word t0,C_word t1){
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
C_word ab[75],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4534,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4537,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11142,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(768),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(512),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[176],t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(768),C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(28416),t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(512),t8);
t10=(C_word)C_a_i_cons(&a,2,lf[176],t9);
t11=(C_word)C_a_i_cons(&a,2,C_fix(768),C_SCHEME_END_OF_LIST);
t12=(C_word)C_a_i_cons(&a,2,C_fix(28672),t11);
t13=(C_word)C_a_i_cons(&a,2,C_fix(512),t12);
t14=(C_word)C_a_i_cons(&a,2,lf[176],t13);
t15=(C_word)C_a_i_cons(&a,2,C_fix(768),C_SCHEME_END_OF_LIST);
t16=(C_word)C_a_i_cons(&a,2,C_fix(28672),t15);
t17=(C_word)C_a_i_cons(&a,2,C_fix(256),t16);
t18=(C_word)C_a_i_cons(&a,2,C_fix(28416),t17);
t19=(C_word)C_a_i_cons(&a,2,C_fix(512),t18);
t20=(C_word)C_a_i_cons(&a,2,lf[176],t19);
t21=(C_word)C_a_i_cons(&a,2,t20,C_SCHEME_END_OF_LIST);
t22=(C_word)C_a_i_cons(&a,2,t14,t21);
t23=(C_word)C_a_i_cons(&a,2,t10,t22);
t24=(C_word)C_a_i_cons(&a,2,t6,t23);
t25=(C_word)C_a_i_cons(&a,2,lf[177],t24);
t26=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11148,a[2]=lf[604],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t3,lf[605],C_fix(28160),t25,t26,C_SCHEME_FALSE);}

/* a11147 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11148(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word ab[7],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_11148,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=(C_word)C_i_cdr(((C_word*)t4)[1]);
t6=C_set_block_item(t4,0,t5);
t7=(C_word)C_i_car(((C_word*)t4)[1]);
t8=(C_word)C_i_cdr(((C_word*)t4)[1]);
t9=C_set_block_item(t4,0,t8);
t10=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11166,a[2]=t7,a[3]=t4,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3227(t10,t7,C_fix(768));}

/* k11164 in a11147 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11166(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11166,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_END_OF_LIST);}
else{
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11175,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3227(t2,t3,C_fix(256));}}

/* k11173 in k11164 in a11147 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11175(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_cadr(((C_word*)((C_word*)t0)[4])[1]);
C_trace("ChickenBridge.scm: 145  append");
t3=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[3],((C_word*)t0)[2],t2);}
else{
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,((C_word*)t0)[2]);}}

/* k11140 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11142(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(28160),t1);}

/* k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4537(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4537,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4540,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11071,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(28160),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(25088),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[176],t5);
t7=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11077,a[2]=lf[601],tmp=(C_word)a,a+=3,tmp);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11095,a[2]=lf[602],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t3,lf[603],C_fix(27904),t6,t7,t8);}

/* a11094 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11095(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_11095,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11099,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3181(t5,t2);}

/* k11097 in a11094 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11099(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11099,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_11102,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=(C_word)C_i_car(t1);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k11100 in k11097 in a11094 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11102(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11102,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_11118,a[2]=t1,a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t3=(C_word)C_i_cdr(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k11116 in k11100 in k11097 in a11094 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11118(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11118,2,t0,t1);}
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[2],t1));}

/* a11076 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11077(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[3],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_11077,4,t0,t1,t2,t3);}
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cadr(t2);
t6=(C_word)C_a_i_cons(&a,2,t4,t5);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3142(t1,C_fix(27904),t6,C_SCHEME_FALSE);}

/* k11069 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_11071(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(27904),t1);}

/* k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4540(C_word c,C_word t0,C_word t1){
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
C_word ab[63],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4540,2,t0,t1);}
t2=C_mutate(&lf[228],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4542,a[2]=lf[229],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate(&lf[230],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4563,a[2]=lf[233],tmp=(C_word)a,a+=3,tmp));
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4679,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10995,a[2]=t4,tmp=(C_word)a,a+=3,tmp);
t6=(C_word)C_a_i_cons(&a,2,C_fix(8705),C_SCHEME_END_OF_LIST);
t7=(C_word)C_a_i_cons(&a,2,C_fix(8450),t6);
t8=(C_word)C_a_i_cons(&a,2,C_fix(8963),t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(10244),t8);
t10=(C_word)C_a_i_cons(&a,2,C_fix(11268),t9);
t11=(C_word)C_a_i_cons(&a,2,C_fix(11012),t10);
t12=(C_word)C_a_i_cons(&a,2,C_fix(9732),t11);
t13=(C_word)C_a_i_cons(&a,2,C_fix(9476),t12);
t14=(C_word)C_a_i_cons(&a,2,C_fix(9988),t13);
t15=(C_word)C_a_i_cons(&a,2,C_fix(10756),t14);
t16=(C_word)C_a_i_cons(&a,2,C_fix(8199),t15);
t17=(C_word)C_a_i_cons(&a,2,C_fix(7941),t16);
t18=(C_word)C_a_i_cons(&a,2,C_fix(7686),t17);
t19=(C_word)C_a_i_cons(&a,2,C_fix(7430),t18);
t20=(C_word)C_a_i_cons(&a,2,C_fix(7173),t19);
t21=(C_word)C_a_i_cons(&a,2,C_fix(6917),t20);
t22=(C_word)C_a_i_cons(&a,2,lf[177],t21);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t5,lf[600],C_fix(28928),t22,C_SCHEME_FALSE,C_SCHEME_FALSE);}

/* k10993 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10995(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(28928),t1);}

/* k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4679(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4679,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4682,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10915,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29440),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(28928),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[139],t5);
t7=(C_word)C_a_i_cons(&a,2,t6,C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(29440),t7);
t9=(C_word)C_a_i_cons(&a,2,lf[176],t8);
t10=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10921,a[2]=lf[598],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t3,lf[599],C_fix(29184),t9,t10,C_SCHEME_FALSE);}

/* a10920 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10921(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[4],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_10921,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10928,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_i_cadr(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(C_word)C_i_cadr(t2);
t7=(C_word)C_i_car(t6);
C_trace("ChickenBridge.scm: 145  is-op?");
f_4542(t4,t7);}
else{
t6=t4;
f_10928(2,t6,C_SCHEME_FALSE);}}

/* k10926 in a10920 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10928(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10928,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=(C_word)C_i_cadr(((C_word*)t0)[3]);
t4=(C_word)C_a_i_cons(&a,2,t2,t3);
C_trace("ChickenBridge.scm: 145  inf->pre");
f_4563(((C_word*)t0)[2],t4);}
else{
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_i_car(((C_word*)t0)[3]));}}

/* k10913 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10915(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(29184),t1);}

/* k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4682(C_word c,C_word t0,C_word t1){
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
C_word ab[72],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4682,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4685,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10779,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29440),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(7173),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[176],t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(29440),C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(8963),t7);
t9=(C_word)C_a_i_cons(&a,2,lf[176],t8);
t10=(C_word)C_a_i_cons(&a,2,C_fix(768),C_SCHEME_END_OF_LIST);
t11=(C_word)C_a_i_cons(&a,2,C_fix(29184),t10);
t12=(C_word)C_a_i_cons(&a,2,C_fix(512),t11);
t13=(C_word)C_a_i_cons(&a,2,lf[176],t12);
t14=(C_word)C_a_i_cons(&a,2,C_fix(2304),C_SCHEME_END_OF_LIST);
t15=(C_word)C_a_i_cons(&a,2,C_fix(26624),t14);
t16=(C_word)C_a_i_cons(&a,2,C_fix(26368),t15);
t17=(C_word)C_a_i_cons(&a,2,C_fix(27136),t16);
t18=(C_word)C_a_i_cons(&a,2,C_fix(27904),t17);
t19=(C_word)C_a_i_cons(&a,2,C_fix(27392),t18);
t20=(C_word)C_a_i_cons(&a,2,t13,t19);
t21=(C_word)C_a_i_cons(&a,2,t9,t20);
t22=(C_word)C_a_i_cons(&a,2,t6,t21);
t23=(C_word)C_a_i_cons(&a,2,lf[177],t22);
t24=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10785,a[2]=lf[595],tmp=(C_word)a,a+=3,tmp);
t25=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10811,a[2]=lf[596],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t3,lf[597],C_fix(29440),t23,t24,t25);}

/* a10810 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10811(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_10811,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10819,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3181(t5,t2);}

/* k10817 in a10810 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10819(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  emit");
f_3299(((C_word*)t0)[4],t1,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* a10784 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10785(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[7],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_10785,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10793,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep((C_word)C_i_pairp(t2))){
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10802,a[2]=t2,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
t6=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3227(t5,t6,C_fix(512));}
else{
t5=t4;
f_10793(t5,t2);}}

/* k10800 in a10784 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10802(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
f_10793(t2,(C_truep(t1)?(C_word)C_i_cadr(((C_word*)t0)[2]):((C_word*)t0)[2]));}

/* k10791 in a10784 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_10793(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3142(((C_word*)t0)[2],C_fix(29440),t1,C_SCHEME_FALSE);}

/* k10777 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10779(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(29440),t1);}

/* k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4685(C_word c,C_word t0,C_word t1){
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
C_word ab[33],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4685,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4688,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10735,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(26368),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(6400),t4);
t6=(C_word)C_a_i_cons(&a,2,C_fix(2304),t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(26624),t6);
t8=(C_word)C_a_i_cons(&a,2,C_fix(27136),t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(27904),t8);
t10=(C_word)C_a_i_cons(&a,2,C_fix(27392),t9);
t11=(C_word)C_a_i_cons(&a,2,C_fix(29184),t10);
t12=(C_word)C_a_i_cons(&a,2,lf[177],t11);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t3,lf[594],C_fix(29696),t12,C_SCHEME_FALSE,C_SCHEME_FALSE);}

/* k10733 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10735(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(29696),t1);}

/* k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4688(C_word c,C_word t0,C_word t1){
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
C_word ab[33],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4688,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4691,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10625,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(256),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[139],t5);
t7=(C_word)C_a_i_cons(&a,2,t6,C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(29696),t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(15872),t8);
t10=(C_word)C_a_i_cons(&a,2,lf[176],t9);
t11=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10631,a[2]=lf[590],tmp=(C_word)a,a+=3,tmp);
t12=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10653,a[2]=lf[592],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t3,lf[593],C_fix(33536),t10,t11,t12);}

/* a10652 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10653(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[12],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_10653,5,t0,t1,t2,t3,t4);}
t5=(C_word)C_a_i_list(&a,1,lf[278]);
t6=t5;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_10664,a[2]=t1,a[3]=t4,a[4]=t3,a[5]=t7,a[6]=t5,tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3181(t8,t2);}

/* k10662 in a10652 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10664(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10664,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_10666,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=t3,a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=lf[591],tmp=(C_word)a,a+=8,tmp));
t5=((C_word*)t3)[1];
f_10666(t5,((C_word*)t0)[2],t1);}

/* do899 in k10662 in a10652 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_10666(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_10666,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,((C_word*)t0)[6]);}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_10695,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=t2,a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
t4=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t3,t4,((C_word*)t0)[3],((C_word*)t0)[2]);}}

/* k10693 in do899 in k10662 in a10652 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10695(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10695,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,t1);
t3=(C_word)C_i_set_cdr(((C_word*)((C_word*)t0)[5])[1],t2);
t4=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[5])[1]);
t5=C_mutate(((C_word *)((C_word*)t0)[5])+1,t4);
t6=(C_word)C_i_cdr(((C_word*)t0)[4]);
t7=((C_word*)((C_word*)t0)[3])[1];
f_10666(t7,((C_word*)t0)[2],t6);}

/* a10630 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10631(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[4],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_10631,4,t0,t1,t2,t3);}
t4=(C_word)C_i_cadr(t2);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10647,a[2]=t1,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
t6=(C_word)C_i_caddr(t2);
C_trace("ChickenBridge.scm: 145  remove-token-type");
f_4477(t5,t6,C_fix(256));}

/* k10645 in a10630 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10647(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10647,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[3],t1);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3142(((C_word*)t0)[2],C_fix(33536),t2,C_SCHEME_FALSE);}

/* k10623 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10625(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(33536),t1);}

/* k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4691(C_word c,C_word t0,C_word t1){
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
C_word ab[33],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4691,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4694,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10516,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(256),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[214],t5);
t7=(C_word)C_a_i_cons(&a,2,t6,C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(29696),t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(16896),t8);
t10=(C_word)C_a_i_cons(&a,2,lf[176],t9);
t11=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10522,a[2]=lf[587],tmp=(C_word)a,a+=3,tmp);
t12=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10549,a[2]=lf[588],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t3,lf[589],C_fix(34560),t10,t11,t12);}

/* a10548 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10549(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_10549,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10553,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3181(t5,t2);}

/* k10551 in a10548 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10553(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10553,2,t0,t1);}
if(C_truep((C_word)C_i_cadr(t1))){
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_10566,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=(C_word)C_i_car(t1);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}
else{
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10585,a[2]=((C_word*)t0)[4],tmp=(C_word)a,a+=3,tmp);
t3=(C_word)C_i_car(t1);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}}

/* k10583 in k10551 in a10548 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10585(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10585,2,t0,t1);}
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_list(&a,2,lf[362],t1));}

/* k10564 in k10551 in a10548 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10566(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10566,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10570,a[2]=t1,a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t3=(C_word)C_i_cadr(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k10568 in k10564 in k10551 in a10548 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10570(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10570,2,t0,t1);}
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_list(&a,3,lf[362],((C_word*)t0)[2],t1));}

/* a10521 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10522(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word ab[4],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_10522,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10526,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_caddr(t2))){
t5=(C_word)C_i_caddr(t2);
C_trace("ChickenBridge.scm: 145  remove-token-type");
f_4477(t4,t5,C_fix(256));}
else{
t5=t4;
f_10526(2,t5,C_SCHEME_FALSE);}}

/* k10524 in a10521 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10526(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10526,2,t0,t1);}
t2=(C_word)C_i_cadr(((C_word*)t0)[3]);
t3=(C_word)C_a_i_list(&a,2,t2,t1);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3142(((C_word*)t0)[2],C_fix(34560),t3,C_SCHEME_FALSE);}

/* k10514 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10516(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(34560),t1);}

/* k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4694(C_word c,C_word t0,C_word t1){
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
C_word ab[66],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4694,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4697,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10317,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(25088),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(2304),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[177],t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(28672),C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(256),t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(28416),t8);
t10=(C_word)C_a_i_cons(&a,2,lf[176],t9);
t11=(C_word)C_a_i_cons(&a,2,C_fix(28672),C_SCHEME_END_OF_LIST);
t12=(C_word)C_a_i_cons(&a,2,C_fix(28416),t11);
t13=(C_word)C_a_i_cons(&a,2,t10,t12);
t14=(C_word)C_a_i_cons(&a,2,lf[177],t13);
t15=(C_word)C_a_i_cons(&a,2,t14,C_SCHEME_END_OF_LIST);
t16=(C_word)C_a_i_cons(&a,2,C_fix(256),t15);
t17=(C_word)C_a_i_cons(&a,2,lf[214],t16);
t18=(C_word)C_a_i_cons(&a,2,t17,C_SCHEME_END_OF_LIST);
t19=(C_word)C_a_i_cons(&a,2,t6,t18);
t20=(C_word)C_a_i_cons(&a,2,C_fix(16384),t19);
t21=(C_word)C_a_i_cons(&a,2,lf[176],t20);
t22=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10323,a[2]=lf[583],tmp=(C_word)a,a+=3,tmp);
t23=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10384,a[2]=lf[585],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t3,lf[586],C_fix(34304),t21,t22,t23);}

/* a10383 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10384(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[10],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_10384,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10388,a[2]=t1,a[3]=t2,a[4]=t4,tmp=(C_word)a,a+=5,tmp);
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10424,a[2]=t4,a[3]=t3,a[4]=t5,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3181(t6,t2);}

/* k10422 in a10383 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10424(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  emit");
f_3299(((C_word*)t0)[4],t1,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k10386 in a10383 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10388(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10388,2,t0,t1);}
t2=(C_word)C_i_car(t1);
t3=(C_word)C_i_car(t1);
t4=(C_word)C_i_cdr(t1);
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10404,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=lf[584],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  expand-send");
t6=C_retrieve(lf[396]);
((C_proc5)C_retrieve_proc(t6))(5,t6,((C_word*)t0)[2],t3,t4,t5);}

/* a10403 in k10386 in a10383 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10404(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+8)){
C_save_and_reclaim((void*)tr3r,(void*)f_10404r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_10404r(t0,t1,t2,t3);}}

static void C_ccall f_10404r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word *a=C_alloc(8);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10412,a[2]=t1,a[3]=((C_word*)t0)[3],tmp=(C_word)a,a+=4,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10416,a[2]=((C_word*)t0)[2],a[3]=t4,tmp=(C_word)a,a+=4,tmp);
C_apply(5,0,t5,C_retrieve(lf[286]),t2,t3);}

/* k10414 in a10403 in k10386 in a10383 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10416(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10416,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10420,a[2]=t1,a[3]=((C_word*)t0)[3],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-position");
f_3199(t2,((C_word*)t0)[2]);}

/* k10418 in k10414 in a10403 in k10386 in a10383 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10420(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-parse-error");
f_3091(((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k10410 in a10403 in k10386 in a10383 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10412(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  errf");
t2=((C_word*)t0)[3];
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* a10322 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10323(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_word t16;
C_word ab[11],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_10323,4,t0,t1,t2,t3);}
t4=(C_word)C_i_caddr(t2);
t5=t4;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10330,a[2]=t1,a[3]=t6,a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t8=((C_word*)t6)[1];
if(C_truep(t8)){
t9=(C_word)C_i_cadr(((C_word*)t6)[1]);
t10=C_set_block_item(t6,0,t9);
t11=(C_word)C_i_car(((C_word*)t6)[1]);
if(C_truep((C_word)C_i_pairp(t11))){
t12=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10370,a[2]=t7,a[3]=t6,tmp=(C_word)a,a+=4,tmp);
t13=(C_word)C_i_car(((C_word*)t6)[1]);
t14=(C_word)C_i_caddr(((C_word*)t6)[1]);
C_trace("ChickenBridge.scm: 145  append");
t15=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t15))(4,t15,t12,t13,t14);}
else{
t12=t7;
f_10330(t12,C_SCHEME_UNDEFINED);}}
else{
t9=C_set_block_item(t6,0,C_SCHEME_END_OF_LIST);
t10=t7;
f_10330(t10,t9);}}

/* k10368 in a10322 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10370(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_10330(t3,t2);}

/* k10328 in a10322 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_10330(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_10330,NULL,2,t0,t1);}
t2=(C_word)C_i_cadr(((C_word*)t0)[4]);
t3=(C_word)C_a_i_cons(&a,2,t2,((C_word*)((C_word*)t0)[3])[1]);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10341,a[2]=t3,a[3]=((C_word*)t0)[2],tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_i_car(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 145  parse-unit-position");
f_3199(t4,t5);}

/* k10339 in k10328 in a10322 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10341(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3142(((C_word*)t0)[3],C_fix(34304),((C_word*)t0)[2],t1);}

/* k10315 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10317(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(34304),t1);}

/* k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4697(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[18],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4697,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4700,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10291,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(14080),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[176],t5);
t7=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10297,a[2]=lf[581],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t3,lf[582],C_fix(33792),t6,t7,C_SCHEME_FALSE);}

/* a10296 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10297(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word *a;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_10297,4,t0,t1,t2,t3);}
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_cadr(t2));}

/* k10289 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10291(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(33792),t1);}

/* k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4700(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[19],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4700,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4703,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10263,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(14592),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[176],t5);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10271,a[2]=t6,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  simple-unit-parser");
f_3540(t7,C_fix(35072));}

/* k10269 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10271(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10271,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10275,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  simple-unit-emitter");
f_3548(t2,lf[296]);}

/* k10273 in k10269 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10275(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(((C_word*)t0)[4],lf[580],C_fix(35072),((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k10261 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10263(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(35072),t1);}

/* k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4703(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[19],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4703,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4706,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10235,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(13568),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[176],t5);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10243,a[2]=t6,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  simple-unit-parser");
f_3540(t7,C_fix(35584));}

/* k10241 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10243(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10243,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10247,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  simple-unit-emitter");
f_3548(t2,lf[293]);}

/* k10245 in k10241 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10247(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(((C_word*)t0)[4],lf[579],C_fix(35584),((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k10233 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10235(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(35584),t1);}

/* k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4706(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[19],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4706,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4709,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10207,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(17152),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[176],t5);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10215,a[2]=t6,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  simple-unit-parser");
f_3540(t7,C_fix(35328));}

/* k10213 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10215(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10215,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10219,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  simple-unit-emitter");
f_3548(t2,lf[578]);}

/* k10217 in k10213 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10219(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(((C_word*)t0)[4],lf[577],C_fix(35328),((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k10205 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10207(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(35328),t1);}

/* k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4709(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[19],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4709,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4712,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10179,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(18432),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[176],t5);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10187,a[2]=t6,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  simple-unit-parser");
f_3540(t7,C_fix(34816));}

/* k10185 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10187(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10187,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10191,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  simple-unit-emitter");
f_3548(t2,lf[308]);}

/* k10189 in k10185 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10191(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(((C_word*)t0)[4],lf[576],C_fix(34816),((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k10177 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10179(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(34816),t1);}

/* k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4712(C_word c,C_word t0,C_word t1){
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
C_word ab[69],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4712,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4715,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10042,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(6144),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[176],t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,t6,t7);
t9=(C_word)C_a_i_cons(&a,2,lf[177],t8);
t10=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t11=(C_word)C_a_i_cons(&a,2,C_fix(6144),t10);
t12=(C_word)C_a_i_cons(&a,2,lf[176],t11);
t13=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t14=(C_word)C_a_i_cons(&a,2,t12,t13);
t15=(C_word)C_a_i_cons(&a,2,lf[177],t14);
t16=(C_word)C_a_i_cons(&a,2,t15,C_SCHEME_END_OF_LIST);
t17=(C_word)C_a_i_cons(&a,2,C_fix(256),t16);
t18=(C_word)C_a_i_cons(&a,2,lf[139],t17);
t19=(C_word)C_a_i_cons(&a,2,t18,C_SCHEME_END_OF_LIST);
t20=(C_word)C_a_i_cons(&a,2,t9,t19);
t21=(C_word)C_a_i_cons(&a,2,C_fix(15616),t20);
t22=(C_word)C_a_i_cons(&a,2,lf[176],t21);
t23=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10048,a[2]=lf[572],tmp=(C_word)a,a+=3,tmp);
t24=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10078,a[2]=lf[574],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t3,lf[575],C_fix(36096),t22,t23,t24);}

/* a10077 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10078(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_10078,5,t0,t1,t2,t3,t4);}
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,lf[573]);}

/* a10047 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10048(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[5],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_10048,4,t0,t1,t2,t3);}
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cadr(t2);
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10072,a[2]=t1,a[3]=t4,a[4]=t5,tmp=(C_word)a,a+=5,tmp);
t7=(C_word)C_i_caddr(t2);
C_trace("ChickenBridge.scm: 145  remove-token-type");
f_4477(t6,t7,C_fix(256));}

/* k10070 in a10047 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10072(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10072,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[4],t1);
t3=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[3],t2);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3142(((C_word*)t0)[2],C_fix(36096),t3,C_SCHEME_FALSE);}

/* k10040 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10042(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(36096),t1);}

/* k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4715(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[19],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4715,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4718,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9984,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(19712),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[176],t5);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9992,a[2]=t6,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  simple-unit-parser");
f_3540(t7,C_fix(31744));}

/* k9990 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9992(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9992,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9994,a[2]=lf[570],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(((C_word*)t0)[3],lf[571],C_fix(31744),((C_word*)t0)[2],t1,t2);}

/* a9993 in k9990 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9994(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_9994,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9998,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3181(t5,t2);}

/* k9996 in a9993 in k9990 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9998(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9998,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_10001,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10026,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  get-emit-info");
f_3259(t3,lf[530],((C_word*)t0)[3]);}

/* k10024 in k9996 in a9993 in k9990 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10026(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10026,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
f_10001(2,t2,C_SCHEME_UNDEFINED);}
else{
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10014,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[3],tmp=(C_word)a,a+=4,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10018,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 145  parse-unit-position");
f_3199(t3,t4);}}

/* k10016 in k10024 in k9996 in a9993 in k9990 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10018(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-parse-error");
f_3091(((C_word*)t0)[2],lf[569],t1);}

/* k10012 in k10024 in k9996 in a9993 in k9990 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10014(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  errf");
t2=((C_word*)t0)[3];
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k9999 in k9996 in a9993 in k9990 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_10001(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  emit");
f_3299(((C_word*)t0)[5],((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k9982 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9984(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(31744),t1);}

/* k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4718(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[19],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4718,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4721,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9923,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(18688),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[176],t5);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9931,a[2]=t6,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  simple-unit-parser");
f_3540(t7,C_fix(31488));}

/* k9929 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9931(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9931,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9933,a[2]=lf[567],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(((C_word*)t0)[3],lf[568],C_fix(31488),((C_word*)t0)[2],t1,t2);}

/* a9932 in k9929 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9933(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_9933,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9937,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3181(t5,t2);}

/* k9935 in a9932 in k9929 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9937(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9937,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_9940,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9968,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  get-emit-info");
f_3259(t3,lf[510],((C_word*)t0)[3]);}

/* k9966 in k9935 in a9932 in k9929 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9968(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9968,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
f_9940(2,t2,C_SCHEME_UNDEFINED);}
else{
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9956,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[3],tmp=(C_word)a,a+=4,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9960,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 145  parse-unit-position");
f_3199(t3,t4);}}

/* k9958 in k9966 in k9935 in a9932 in k9929 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9960(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-parse-error");
f_3091(((C_word*)t0)[2],lf[566],t1);}

/* k9954 in k9966 in k9935 in a9932 in k9929 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9956(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  errf");
t2=((C_word*)t0)[3];
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k9938 in k9935 in a9932 in k9929 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9940(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9940,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_9943,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  set-emit-info!");
f_3281(t2,lf[510],lf[508],((C_word*)t0)[3]);}

/* k9941 in k9938 in k9935 in a9932 in k9929 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9943(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  emit");
f_3299(((C_word*)t0)[5],((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k9921 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9923(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(31488),t1);}

/* k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4721(C_word c,C_word t0,C_word t1){
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
C_word ab[33],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4721,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4724,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9832,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(10756),t4);
t6=(C_word)C_a_i_cons(&a,2,C_fix(25088),t5);
t7=(C_word)C_a_i_cons(&a,2,lf[176],t6);
t8=(C_word)C_a_i_cons(&a,2,C_fix(25088),C_SCHEME_END_OF_LIST);
t9=(C_word)C_a_i_cons(&a,2,t7,t8);
t10=(C_word)C_a_i_cons(&a,2,lf[177],t9);
t11=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9838,a[2]=lf[562],tmp=(C_word)a,a+=3,tmp);
t12=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9873,a[2]=lf[564],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t3,lf[565],C_fix(30208),t10,t11,t12);}

/* a9872 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9873(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[9],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_9873,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9879,a[2]=t4,a[3]=t3,a[4]=lf[563],tmp=(C_word)a,a+=5,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9887,a[2]=t5,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3181(t6,t2);}

/* k9885 in a9872 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9887(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("map");
t2=*((C_word*)lf[276]+1);
((C_proc4)(void*)(*((C_word*)t2+1)))(4,t2,((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* a9878 in a9872 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9879(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_9879,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t1,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* a9837 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9838(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[10],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_9838,4,t0,t1,t2,t3);}
if(C_truep((C_word)C_i_pairp(t2))){
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_caddr(t2);
t6=(C_word)C_a_i_list(&a,2,t4,t5);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3142(t1,C_fix(30208),t6,C_SCHEME_FALSE);}
else{
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9871,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3142(t4,C_fix(4608),lf[561],C_SCHEME_FALSE);}}

/* k9869 in a9837 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9871(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9871,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,2,((C_word*)t0)[3],t1);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3142(((C_word*)t0)[2],C_fix(30208),t2,C_SCHEME_FALSE);}

/* k9830 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9832(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(30208),t1);}

/* k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4724(C_word c,C_word t0,C_word t1){
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
C_word ab[33],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4724,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4727,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9730,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(30208),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(256),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[139],t5);
t7=(C_word)C_a_i_cons(&a,2,t6,C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(30208),t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(20480),t8);
t10=(C_word)C_a_i_cons(&a,2,lf[176],t9);
t11=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9736,a[2]=lf[556],tmp=(C_word)a,a+=3,tmp);
t12=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9779,a[2]=lf[559],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t3,lf[560],C_fix(29952),t10,t11,t12);}

/* a9778 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9779(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_9779,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9783,a[2]=t2,a[3]=t1,a[4]=t4,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  add-emit-info");
f_3271(t5,lf[558],C_SCHEME_TRUE,t3);}

/* k9781 in a9778 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9783(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9783,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9788,a[2]=((C_word*)t0)[4],a[3]=t1,a[4]=lf[557],tmp=(C_word)a,a+=5,tmp);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9796,a[2]=t2,a[3]=((C_word*)t0)[3],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3181(t3,((C_word*)t0)[2]);}

/* k9794 in k9781 in a9778 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9796(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("map");
t2=*((C_word*)lf[276]+1);
((C_proc4)(void*)(*((C_word*)t2+1)))(4,t2,((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* a9787 in k9781 in a9778 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9788(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_9788,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t1,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* a9735 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9736(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[7],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_9736,4,t0,t1,t2,t3);}
if(C_truep((C_word)C_i_caddr(t2))){
t4=(C_word)C_i_cadr(t2);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9769,a[2]=t1,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
t6=(C_word)C_i_caddr(t2);
C_trace("ChickenBridge.scm: 145  remove-token-type");
f_4477(t5,t6,C_fix(256));}
else{
t4=(C_word)C_i_cadr(t2);
t5=(C_word)C_a_i_list(&a,1,t4);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3142(t1,C_fix(29952),t5,C_SCHEME_FALSE);}}

/* k9767 in a9735 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9769(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9769,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[3],t1);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3142(((C_word*)t0)[2],C_fix(29952),t2,C_SCHEME_FALSE);}

/* k9728 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9730(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(29952),t1);}

/* k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4727(C_word c,C_word t0,C_word t1){
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
C_word ab[57],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4727,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4730,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9644,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(25088),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(27136),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[177],t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(12800),C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(12544),t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(12288),t8);
t10=(C_word)C_a_i_cons(&a,2,C_fix(12032),t9);
t11=(C_word)C_a_i_cons(&a,2,C_fix(11776),t10);
t12=(C_word)C_a_i_cons(&a,2,C_fix(11268),t11);
t13=(C_word)C_a_i_cons(&a,2,C_fix(11012),t12);
t14=(C_word)C_a_i_cons(&a,2,C_fix(10756),t13);
t15=(C_word)C_a_i_cons(&a,2,lf[177],t14);
t16=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t17=(C_word)C_a_i_cons(&a,2,t15,t16);
t18=(C_word)C_a_i_cons(&a,2,t6,t17);
t19=(C_word)C_a_i_cons(&a,2,lf[176],t18);
t20=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9650,a[2]=lf[554],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t3,lf[555],C_fix(30720),t19,t20,C_SCHEME_FALSE);}

/* a9649 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9650(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word *a;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_9650,4,t0,t1,t2,t3);}
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3142(t1,C_fix(30720),t2,C_SCHEME_FALSE);}

/* k9642 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9644(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(30720),t1);}

/* k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4730(C_word c,C_word t0,C_word t1){
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
C_word ab[33],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4730,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4733,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9364,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(30720),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(256),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[139],t5);
t7=(C_word)C_a_i_cons(&a,2,t6,C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(30720),t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(16640),t8);
t10=(C_word)C_a_i_cons(&a,2,lf[176],t9);
t11=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9370,a[2]=lf[544],tmp=(C_word)a,a+=3,tmp);
t12=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9413,a[2]=lf[552],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t3,lf[553],C_fix(30464),t10,t11,t12);}

/* a9412 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9413(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_9413,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9417,a[2]=t1,a[3]=t4,a[4]=t3,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3181(t5,t2);}

/* k9415 in a9412 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9417(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[15],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9417,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,lf[240]);
t3=t2;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_SCHEME_UNDEFINED;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=C_set_block_item(t6,0,(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_9425,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=t6,a[5]=t4,a[6]=t2,a[7]=lf[551],tmp=(C_word)a,a+=8,tmp));
t8=((C_word*)t6)[1];
f_9425(t8,((C_word*)t0)[2],t1);}

/* do979 in k9415 in a9412 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_9425(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_9425,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=(C_word)C_i_cddr(((C_word*)t0)[6]);
t4=(C_word)C_i_nullp(t3);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_truep(t4)?(C_word)C_i_cadr(((C_word*)t0)[6]):((C_word*)t0)[6]));}
else{
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_9448,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=t2,a[7]=((C_word*)t0)[5],tmp=(C_word)a,a+=8,tmp);
t4=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3181(t3,t4);}}

/* k9446 in do979 in k9415 in a9412 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9448(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9448,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_9451,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t3=(C_word)C_i_car(t1);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k9449 in k9446 in do979 in k9415 in a9412 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9451(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9451,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_9454,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],tmp=(C_word)a,a+=10,tmp);
t3=(C_word)C_i_cadr(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 145  parse-unit-type");
f_3163(t2,t3);}

/* k9452 in k9449 in k9446 in do979 in k9415 in a9412 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9454(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9454,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_9457,a[2]=t1,a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],tmp=(C_word)a,a+=8,tmp);
t3=(C_word)C_i_caddr(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k9455 in k9452 in k9449 in k9446 in do979 in k9415 in a9412 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9457(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9457,2,t0,t1);}
t2=C_SCHEME_FALSE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_9460,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=t3,tmp=(C_word)a,a+=8,tmp);
t5=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_9517,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t4,a[5]=t1,a[6]=t3,tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4433(t5,((C_word*)t0)[2],C_fix(10756));}

/* k9515 in k9455 in k9452 in k9449 in k9446 in do979 in k9415 in a9412 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9517(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9517,2,t0,t1);}
if(C_truep(t1)){
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,((C_word*)t0)[5]);
t3=((C_word*)t0)[4];
f_9460(t3,t2);}
else{
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_9524,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[3],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4433(t2,((C_word*)t0)[2],C_fix(11776));}}

/* k9522 in k9515 in k9455 in k9452 in k9449 in k9446 in do979 in k9415 in a9412 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9524(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[16],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9524,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,3,lf[215],((C_word*)t0)[6],((C_word*)t0)[5]);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t4=((C_word*)t0)[3];
f_9460(t4,t3);}
else{
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_9534,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4433(t2,((C_word*)t0)[2],C_fix(12032));}}

/* k9532 in k9522 in k9515 in k9455 in k9452 in k9449 in k9446 in do979 in k9415 in a9412 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9534(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[16],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9534,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,3,lf[139],((C_word*)t0)[6],((C_word*)t0)[5]);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t4=((C_word*)t0)[3];
f_9460(t4,t3);}
else{
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_9544,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[5],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4433(t2,((C_word*)t0)[2],C_fix(12288));}}

/* k9542 in k9532 in k9522 in k9515 in k9455 in k9452 in k9449 in k9446 in do979 in k9415 in a9412 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9544(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9544,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,2,lf[548],((C_word*)t0)[6]);
t3=(C_word)C_a_i_list(&a,3,lf[193],((C_word*)t0)[5],t2);
t4=C_mutate(((C_word *)((C_word*)t0)[4])+1,t3);
t5=((C_word*)t0)[3];
f_9460(t5,t4);}
else{
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_9558,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4433(t2,((C_word*)t0)[2],C_fix(12544));}}

/* k9556 in k9542 in k9532 in k9522 in k9515 in k9455 in k9452 in k9449 in k9446 in do979 in k9415 in a9412 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9558(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[16],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9558,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,3,lf[549],((C_word*)t0)[6],((C_word*)t0)[5]);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t4=((C_word*)t0)[3];
f_9460(t4,t3);}
else{
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_9568,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[5],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4433(t2,((C_word*)t0)[2],C_fix(12800));}}

/* k9566 in k9556 in k9542 in k9532 in k9522 in k9515 in k9455 in k9452 in k9449 in k9446 in do979 in k9415 in a9412 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9568(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[16],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9568,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,3,lf[193],((C_word*)t0)[6],((C_word*)t0)[5]);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t4=((C_word*)t0)[3];
f_9460(t4,t3);}
else{
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_9578,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4433(t2,((C_word*)t0)[2],C_fix(11012));}}

/* k9576 in k9566 in k9556 in k9542 in k9532 in k9522 in k9515 in k9455 in k9452 in k9449 in k9446 in do979 in k9415 in a9412 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9578(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[15],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9578,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,3,lf[550],((C_word*)t0)[6],((C_word*)t0)[5]);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t4=((C_word*)t0)[3];
f_9460(t4,t3);}
else{
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_9588,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4433(t2,((C_word*)t0)[2],C_fix(11268));}}

/* k9586 in k9576 in k9566 in k9556 in k9542 in k9532 in k9522 in k9515 in k9455 in k9452 in k9449 in k9446 in do979 in k9415 in a9412 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9588(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9588,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,3,lf[217],((C_word*)t0)[5],((C_word*)t0)[4]);
t3=C_mutate(((C_word *)((C_word*)t0)[3])+1,t2);
t4=((C_word*)t0)[2];
f_9460(t4,t3);}
else{
t2=((C_word*)t0)[2];
f_9460(t2,C_SCHEME_UNDEFINED);}}

/* k9458 in k9455 in k9452 in k9449 in k9446 in do979 in k9415 in a9412 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_9460(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_9460,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_9463,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9484,a[2]=t2,a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[2],tmp=(C_word)a,a+=5,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t0)[2]))){
t4=(C_word)C_i_car(((C_word*)t0)[2]);
t5=t3;
f_9484(t5,(C_word)C_eqp(t4,lf[547]));}
else{
t4=t3;
f_9484(t4,C_SCHEME_FALSE);}}

/* k9482 in k9458 in k9455 in k9452 in k9449 in k9446 in do979 in k9415 in a9412 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_9484(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[27],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_9484,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_cadr(((C_word*)t0)[4]);
t3=(C_word)C_i_caddr(((C_word*)t0)[4]);
t4=(C_word)C_a_i_list(&a,3,lf[545],t2,t3);
t5=(C_word)C_a_i_list(&a,3,lf[546],t4,((C_word*)((C_word*)t0)[3])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t5);
t7=((C_word*)t0)[2];
f_9463(t7,t6);}
else{
t2=(C_word)C_a_i_list(&a,3,lf[235],((C_word*)t0)[4],((C_word*)((C_word*)t0)[3])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[3])+1,t2);
t4=((C_word*)t0)[2];
f_9463(t4,t3);}}

/* k9461 in k9458 in k9455 in k9452 in k9449 in k9446 in do979 in k9415 in a9412 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_9463(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_9463,NULL,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,((C_word*)((C_word*)t0)[6])[1]);
t3=(C_word)C_i_set_cdr(((C_word*)((C_word*)t0)[5])[1],t2);
t4=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[5])[1]);
t5=C_mutate(((C_word *)((C_word*)t0)[5])+1,t4);
t6=(C_word)C_i_cdr(((C_word*)t0)[4]);
t7=((C_word*)((C_word*)t0)[3])[1];
f_9425(t7,((C_word*)t0)[2],t6);}

/* a9369 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9370(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[7],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_9370,4,t0,t1,t2,t3);}
if(C_truep((C_word)C_i_caddr(t2))){
t4=(C_word)C_i_cadr(t2);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9403,a[2]=t1,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
t6=(C_word)C_i_caddr(t2);
C_trace("ChickenBridge.scm: 145  remove-token-type");
f_4477(t5,t6,C_fix(256));}
else{
t4=(C_word)C_i_cadr(t2);
t5=(C_word)C_a_i_list(&a,1,t4);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3142(t1,C_fix(30464),t5,C_SCHEME_FALSE);}}

/* k9401 in a9369 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9403(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9403,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[3],t1);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3142(((C_word*)t0)[2],C_fix(30464),t2,C_SCHEME_FALSE);}

/* k9362 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9364(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(30464),t1);}

/* k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4733(C_word c,C_word t0,C_word t1){
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
C_word ab[39],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4733,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4736,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9250,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29952),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,lf[214],t4);
t6=(C_word)C_a_i_cons(&a,2,C_fix(36608),C_SCHEME_END_OF_LIST);
t7=(C_word)C_a_i_cons(&a,2,lf[139],t6);
t8=(C_word)C_a_i_cons(&a,2,C_fix(18193),C_SCHEME_END_OF_LIST);
t9=(C_word)C_a_i_cons(&a,2,t7,t8);
t10=(C_word)C_a_i_cons(&a,2,t5,t9);
t11=(C_word)C_a_i_cons(&a,2,C_fix(13328),t10);
t12=(C_word)C_a_i_cons(&a,2,lf[176],t11);
t13=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9256,a[2]=lf[541],tmp=(C_word)a,a+=3,tmp);
t14=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9282,a[2]=lf[542],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t3,lf[543],C_fix(32000),t12,t13,t14);}

/* a9281 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9282(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_9282,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9286,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3181(t5,t2);}

/* k9284 in a9281 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9286(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9286,2,t0,t1);}
t2=(C_word)C_i_car(t1);
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_9292,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t2,tmp=(C_word)a,a+=6,tmp);
t4=(C_word)C_i_cdr(t1);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t3,t4,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k9290 in k9284 in a9281 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9292(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9292,2,t0,t1);}
if(C_truep(((C_word*)t0)[5])){
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9312,a[2]=((C_word*)t0)[4],a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t2,((C_word*)t0)[5],((C_word*)t0)[3],((C_word*)t0)[2]);}
else{
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_cons(&a,2,lf[240],t1));}}

/* k9310 in k9290 in k9284 in a9281 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9312(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9312,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,t1,((C_word*)t0)[3]);
t3=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_cons(&a,2,lf[445],t2));}

/* a9255 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9256(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_word ab[7],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_9256,4,t0,t1,t2,t3);}
t4=(C_word)C_i_cadr(t2);
t5=t4;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(C_word)C_i_caddr(t2);
t8=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9266,a[2]=t1,a[3]=t7,a[4]=t6,tmp=(C_word)a,a+=5,tmp);
t9=((C_word*)t6)[1];
if(C_truep(t9)){
t10=(C_word)C_i_car(((C_word*)t6)[1]);
t11=C_set_block_item(t6,0,t10);
t12=t8;
f_9266(t12,t11);}
else{
t10=t8;
f_9266(t10,C_SCHEME_FALSE);}}

/* k9264 in a9255 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_9266(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_9266,NULL,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)((C_word*)t0)[4])[1],((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3142(((C_word*)t0)[2],C_fix(32000),t2,C_SCHEME_FALSE);}

/* k9248 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9250(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(32000),t1);}

/* k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4736(C_word c,C_word t0,C_word t1){
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
C_word ab[81],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4736,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4739,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9053,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(36608),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,lf[214],t4);
t6=(C_word)C_a_i_cons(&a,2,C_fix(36608),C_SCHEME_END_OF_LIST);
t7=(C_word)C_a_i_cons(&a,2,C_fix(17920),t6);
t8=(C_word)C_a_i_cons(&a,2,lf[214],t7);
t9=(C_word)C_a_i_cons(&a,2,t8,C_SCHEME_END_OF_LIST);
t10=(C_word)C_a_i_cons(&a,2,t5,t9);
t11=(C_word)C_a_i_cons(&a,2,C_fix(18944),t10);
t12=(C_word)C_a_i_cons(&a,2,C_fix(29696),t11);
t13=(C_word)C_a_i_cons(&a,2,C_fix(14336),t12);
t14=(C_word)C_a_i_cons(&a,2,lf[176],t13);
t15=(C_word)C_a_i_cons(&a,2,C_fix(36608),C_SCHEME_END_OF_LIST);
t16=(C_word)C_a_i_cons(&a,2,C_fix(29696),t15);
t17=(C_word)C_a_i_cons(&a,2,C_fix(19968),t16);
t18=(C_word)C_a_i_cons(&a,2,lf[176],t17);
t19=(C_word)C_a_i_cons(&a,2,C_fix(36608),C_SCHEME_END_OF_LIST);
t20=(C_word)C_a_i_cons(&a,2,C_fix(29696),t19);
t21=(C_word)C_a_i_cons(&a,2,C_fix(19200),t20);
t22=(C_word)C_a_i_cons(&a,2,lf[176],t21);
t23=(C_word)C_a_i_cons(&a,2,t22,C_SCHEME_END_OF_LIST);
t24=(C_word)C_a_i_cons(&a,2,t18,t23);
t25=(C_word)C_a_i_cons(&a,2,t14,t24);
t26=(C_word)C_a_i_cons(&a,2,lf[177],t25);
t27=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9059,a[2]=lf[538],tmp=(C_word)a,a+=3,tmp);
t28=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9127,a[2]=lf[539],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t3,lf[540],C_fix(32256),t26,t27,t28);}

/* a9126 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9127(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_9127,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9131,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3181(t5,t2);}

/* k9129 in a9126 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9131(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  emit");
f_3299(((C_word*)t0)[4],t1,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* a9058 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9059(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word ab[13],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_9059,4,t0,t1,t2,t3);}
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cadr(t2);
t6=C_SCHEME_END_OF_LIST;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9072,a[2]=t7,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
t9=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_9078,a[2]=t8,a[3]=t7,a[4]=t5,a[5]=t4,a[6]=t2,tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3227(t9,t4,C_fix(14336));}

/* k9076 in a9058 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9078(C_word c,C_word t0,C_word t1){
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
C_word ab[29],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9078,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_cadddr(((C_word*)t0)[6]);
t3=t2;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=C_SCHEME_FALSE;
t8=(*a=C_VECTOR_TYPE|1,a[1]=t7,tmp=(C_word)a,a+=2,tmp);
t9=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_9084,a[2]=((C_word*)t0)[6],a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=t8,a[6]=t6,a[7]=((C_word*)t0)[4],a[8]=((C_word*)t0)[5],a[9]=t4,tmp=(C_word)a,a+=10,tmp);
t10=((C_word*)t4)[1];
if(C_truep(t10)){
t11=(C_word)C_i_car(((C_word*)t4)[1]);
t12=C_set_block_item(t6,0,t11);
t13=t9;
f_9084(t13,t12);}
else{
t11=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9113,a[2]=t9,a[3]=t6,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3142(t11,C_fix(4608),lf[537],C_SCHEME_FALSE);}}
else{
t2=(C_word)C_i_caddr(((C_word*)t0)[6]);
t3=(C_word)C_a_i_list(&a,3,((C_word*)t0)[5],((C_word*)t0)[4],t2);
t4=C_mutate(((C_word *)((C_word*)t0)[3])+1,t3);
t5=((C_word*)t0)[2];
f_9072(t5,t4);}}

/* k9111 in k9076 in a9058 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9113(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_9084(t3,t2);}

/* k9082 in k9076 in a9058 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_9084(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_9084,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_9088,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],a[8]=((C_word*)t0)[9],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 145  fifth");
t3=C_retrieve(lf[243]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)t0)[2]);}

/* k9086 in k9082 in k9076 in a9058 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9088(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9088,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_9091,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
t4=((C_word*)((C_word*)t0)[8])[1];
if(C_truep(t4)){
t5=(C_word)C_i_cadr(((C_word*)((C_word*)t0)[8])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[4])+1,t5);
t7=t3;
f_9091(t7,t6);}
else{
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9102,a[2]=t3,a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3142(t5,C_fix(4608),lf[536],C_SCHEME_FALSE);}}

/* k9100 in k9086 in k9082 in k9076 in a9058 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9102(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_9091(t3,t2);}

/* k9089 in k9086 in k9082 in k9076 in a9058 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_9091(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_9091,NULL,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,4,((C_word*)t0)[7],((C_word*)t0)[6],((C_word*)((C_word*)t0)[5])[1],((C_word*)((C_word*)t0)[4])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[3])+1,t2);
t4=((C_word*)t0)[2];
f_9072(t4,t3);}

/* k9070 in a9058 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_9072(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3142(((C_word*)t0)[3],C_fix(32256),((C_word*)((C_word*)t0)[2])[1],C_SCHEME_FALSE);}

/* k9051 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_9053(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(32256),t1);}

/* k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4739(C_word c,C_word t0,C_word t1){
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
C_word t60;
C_word ab[174],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4739,2,t0,t1);}
t2=C_mutate(&lf[234],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4741,a[2]=lf[255],tmp=(C_word)a,a+=3,tmp));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5262,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8781,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
t5=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t6=(C_word)C_a_i_cons(&a,2,C_fix(23296),t5);
t7=(C_word)C_a_i_cons(&a,2,lf[176],t6);
t8=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t9=(C_word)C_a_i_cons(&a,2,C_fix(18944),t8);
t10=(C_word)C_a_i_cons(&a,2,lf[214],t9);
t11=(C_word)C_a_i_cons(&a,2,t10,C_SCHEME_END_OF_LIST);
t12=(C_word)C_a_i_cons(&a,2,C_fix(29696),t11);
t13=(C_word)C_a_i_cons(&a,2,C_fix(10756),t12);
t14=(C_word)C_a_i_cons(&a,2,C_fix(25088),t13);
t15=(C_word)C_a_i_cons(&a,2,C_fix(22272),t14);
t16=(C_word)C_a_i_cons(&a,2,lf[176],t15);
t17=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t18=(C_word)C_a_i_cons(&a,2,C_fix(22784),t17);
t19=(C_word)C_a_i_cons(&a,2,C_fix(25088),t18);
t20=(C_word)C_a_i_cons(&a,2,C_fix(22272),t19);
t21=(C_word)C_a_i_cons(&a,2,lf[176],t20);
t22=(C_word)C_a_i_cons(&a,2,C_fix(21760),C_SCHEME_END_OF_LIST);
t23=(C_word)C_a_i_cons(&a,2,C_fix(20992),t22);
t24=(C_word)C_a_i_cons(&a,2,C_fix(23552),t23);
t25=(C_word)C_a_i_cons(&a,2,C_fix(21248),t24);
t26=(C_word)C_a_i_cons(&a,2,lf[177],t25);
t27=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t28=(C_word)C_a_i_cons(&a,2,t26,t27);
t29=(C_word)C_a_i_cons(&a,2,lf[214],t28);
t30=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t31=(C_word)C_a_i_cons(&a,2,C_fix(21504),t30);
t32=(C_word)C_a_i_cons(&a,2,lf[214],t31);
t33=(C_word)C_a_i_cons(&a,2,t32,C_SCHEME_END_OF_LIST);
t34=(C_word)C_a_i_cons(&a,2,t29,t33);
t35=(C_word)C_a_i_cons(&a,2,C_fix(29696),t34);
t36=(C_word)C_a_i_cons(&a,2,C_fix(22528),t35);
t37=(C_word)C_a_i_cons(&a,2,C_fix(25088),t36);
t38=(C_word)C_a_i_cons(&a,2,C_fix(22272),t37);
t39=(C_word)C_a_i_cons(&a,2,lf[176],t38);
t40=(C_word)C_a_i_cons(&a,2,C_fix(21760),C_SCHEME_END_OF_LIST);
t41=(C_word)C_a_i_cons(&a,2,C_fix(20992),t40);
t42=(C_word)C_a_i_cons(&a,2,C_fix(23552),t41);
t43=(C_word)C_a_i_cons(&a,2,C_fix(21248),t42);
t44=(C_word)C_a_i_cons(&a,2,lf[177],t43);
t45=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t46=(C_word)C_a_i_cons(&a,2,C_fix(21504),t45);
t47=(C_word)C_a_i_cons(&a,2,lf[214],t46);
t48=(C_word)C_a_i_cons(&a,2,t47,C_SCHEME_END_OF_LIST);
t49=(C_word)C_a_i_cons(&a,2,C_fix(29696),t48);
t50=(C_word)C_a_i_cons(&a,2,t44,t49);
t51=(C_word)C_a_i_cons(&a,2,C_fix(25088),t50);
t52=(C_word)C_a_i_cons(&a,2,C_fix(22272),t51);
t53=(C_word)C_a_i_cons(&a,2,lf[176],t52);
t54=(C_word)C_a_i_cons(&a,2,t53,C_SCHEME_END_OF_LIST);
t55=(C_word)C_a_i_cons(&a,2,t39,t54);
t56=(C_word)C_a_i_cons(&a,2,t21,t55);
t57=(C_word)C_a_i_cons(&a,2,t16,t56);
t58=(C_word)C_a_i_cons(&a,2,t7,t57);
t59=(C_word)C_a_i_cons(&a,2,lf[177],t58);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t4,lf[535],C_fix(33024),t59,C_retrieve2(lf[234],"sal-parse-stepping"),C_SCHEME_FALSE);}

/* k8779 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8781(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(33024),t1);}

/* k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5262(C_word c,C_word t0,C_word t1){
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
C_word ab[37],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5262,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5265,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8725,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(20224),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[176],t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(19456),t7);
t9=(C_word)C_a_i_cons(&a,2,lf[176],t8);
t10=(C_word)C_a_i_cons(&a,2,t9,C_SCHEME_END_OF_LIST);
t11=(C_word)C_a_i_cons(&a,2,t6,t10);
t12=(C_word)C_a_i_cons(&a,2,lf[177],t11);
t13=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8733,a[2]=t12,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  simple-unit-parser");
f_3540(t13,C_fix(33280));}

/* k8731 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8733(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(((C_word*)t0)[3],lf[534],C_fix(33280),((C_word*)t0)[2],t1,C_SCHEME_FALSE);}

/* k8723 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8725(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(33280),t1);}

/* k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5265(C_word c,C_word t0,C_word t1){
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
C_word ab[78],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5265,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5784,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8553,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(16144),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(14864),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[177],t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(29952),C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,lf[214],t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(33024),C_SCHEME_END_OF_LIST);
t10=(C_word)C_a_i_cons(&a,2,lf[139],t9);
t11=(C_word)C_a_i_cons(&a,2,C_fix(33280),C_SCHEME_END_OF_LIST);
t12=(C_word)C_a_i_cons(&a,2,lf[139],t11);
t13=(C_word)C_a_i_cons(&a,2,C_fix(36608),C_SCHEME_END_OF_LIST);
t14=(C_word)C_a_i_cons(&a,2,lf[215],t13);
t15=(C_word)C_a_i_cons(&a,2,C_fix(36608),C_SCHEME_END_OF_LIST);
t16=(C_word)C_a_i_cons(&a,2,C_fix(22016),t15);
t17=(C_word)C_a_i_cons(&a,2,lf[214],t16);
t18=(C_word)C_a_i_cons(&a,2,C_fix(18193),C_SCHEME_END_OF_LIST);
t19=(C_word)C_a_i_cons(&a,2,t17,t18);
t20=(C_word)C_a_i_cons(&a,2,t14,t19);
t21=(C_word)C_a_i_cons(&a,2,t12,t20);
t22=(C_word)C_a_i_cons(&a,2,t10,t21);
t23=(C_word)C_a_i_cons(&a,2,t8,t22);
t24=(C_word)C_a_i_cons(&a,2,t6,t23);
t25=(C_word)C_a_i_cons(&a,2,lf[176],t24);
t26=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8559,a[2]=lf[518],tmp=(C_word)a,a+=3,tmp);
t27=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8605,a[2]=lf[532],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t3,lf[533],C_fix(32512),t25,t26,t27);}

/* a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8605(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[7],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_8605,5,t0,t1,t2,t3,t4);}
t5=t3;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5271,a[2]=t4,a[3]=t6,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3181(t7,t2);}

/* k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5271(C_word c,C_word t0,C_word t1){
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
C_word ab[33],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5271,2,t0,t1);}
t2=t1;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_SCHEME_FALSE;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_SCHEME_END_OF_LIST;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=C_SCHEME_END_OF_LIST;
t9=(*a=C_VECTOR_TYPE|1,a[1]=t8,tmp=(C_word)a,a+=2,tmp);
t10=C_SCHEME_END_OF_LIST;
t11=(*a=C_VECTOR_TYPE|1,a[1]=t10,tmp=(C_word)a,a+=2,tmp);
t12=C_SCHEME_END_OF_LIST;
t13=(*a=C_VECTOR_TYPE|1,a[1]=t12,tmp=(C_word)a,a+=2,tmp);
t14=C_SCHEME_END_OF_LIST;
t15=(*a=C_VECTOR_TYPE|1,a[1]=t14,tmp=(C_word)a,a+=2,tmp);
t16=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_5289,a[2]=t11,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=t7,a[6]=((C_word*)t0)[4],a[7]=t15,a[8]=t13,a[9]=t5,a[10]=t9,a[11]=t3,tmp=(C_word)a,a+=12,tmp);
t17=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5743,a[2]=t3,a[3]=((C_word*)t0)[2],a[4]=t5,a[5]=t16,a[6]=((C_word*)t0)[3],tmp=(C_word)a,a+=7,tmp);
t18=(C_word)C_i_car(((C_word*)t3)[1]);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3227(t17,t18,C_fix(14864));}

/* k5741 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5743(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[14],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5743,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5747,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  add-emit-info");
f_3271(t2,lf[529],C_SCHEME_TRUE,((C_word*)((C_word*)t0)[6])[1]);}
else{
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5750,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5777,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  get-emit-info");
f_3259(t3,lf[512],((C_word*)((C_word*)t0)[6])[1]);}}

/* k5775 in k5741 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5777(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5777,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
f_5750(2,t2,C_SCHEME_UNDEFINED);}
else{
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5765,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[3],tmp=(C_word)a,a+=4,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5769,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_i_car(((C_word*)((C_word*)t0)[2])[1]);
C_trace("ChickenBridge.scm: 145  parse-unit-position");
f_3199(t3,t4);}}

/* k5767 in k5775 in k5741 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5769(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-parse-error");
f_3091(((C_word*)t0)[2],lf[531],t1);}

/* k5763 in k5775 in k5741 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5765(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  errf");
t2=((C_word*)t0)[3];
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k5748 in k5741 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5750(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5750,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5754,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  add-emit-info");
f_3271(t2,lf[530],C_SCHEME_TRUE,((C_word*)((C_word*)t0)[4])[1]);}

/* k5752 in k5748 in k5741 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5754(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[4])+1,t1);
t3=C_set_block_item(((C_word*)t0)[3],0,C_SCHEME_TRUE);
t4=((C_word*)t0)[2];
f_5289(t4,t3);}

/* k5745 in k5741 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5747(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_5289(t3,t2);}

/* k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_5289(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[20],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5289,NULL,2,t0,t1);}
t2=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[11])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[11])+1,t2);
t4=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_5296,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[11],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],a[10]=((C_word*)t0)[9],a[11]=((C_word*)t0)[10],tmp=(C_word)a,a+=12,tmp);
if(C_truep((C_word)C_i_car(((C_word*)((C_word*)t0)[11])[1]))){
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5732,a[2]=t4,a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5736,a[2]=((C_word*)t0)[5],a[3]=t5,tmp=(C_word)a,a+=4,tmp);
t7=(C_word)C_i_car(((C_word*)((C_word*)t0)[11])[1]);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t6,t7,((C_word*)((C_word*)t0)[4])[1],((C_word*)t0)[3]);}
else{
t5=t4;
f_5296(t5,C_SCHEME_UNDEFINED);}}

/* k5734 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5736(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  append");
t2=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k5730 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5732(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_5296(t3,t2);}

/* k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_5296(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5296,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_5299,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],a[10]=((C_word*)t0)[10],a[11]=((C_word*)t0)[11],tmp=(C_word)a,a+=12,tmp);
t3=(C_word)C_i_cadr(((C_word*)((C_word*)t0)[3])[1]);
t4=C_SCHEME_UNDEFINED;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_set_block_item(t5,0,(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5607,a[2]=((C_word*)t0)[11],a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[9],a[5]=((C_word*)t0)[6],a[6]=t5,a[7]=lf[528],tmp=(C_word)a,a+=8,tmp));
t7=((C_word*)t5)[1];
f_5607(t7,t2,t3);}

/* do1089 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_5607(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5607,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5617,a[2]=t1,a[3]=((C_word*)t0)[6],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5628,a[2]=t3,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],tmp=(C_word)a,a+=7,tmp);
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3181(t4,t5);}}

/* k5626 in do1089 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5628(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5628,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5630,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=t3,a[6]=((C_word*)t0)[6],a[7]=lf[527],tmp=(C_word)a,a+=8,tmp));
t5=((C_word*)t3)[1];
f_5630(t5,((C_word*)t0)[2],t1);}

/* do1092 in k5626 in do1089 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_5630(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[19],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5630,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(C_word)C_i_car(t2);
t4=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_5644,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t3,a[5]=((C_word*)t0)[4],a[6]=t1,a[7]=((C_word*)t0)[5],a[8]=t2,a[9]=((C_word*)t0)[6],tmp=(C_word)a,a+=10,tmp);
t5=(C_word)C_i_car(t3);
t6=(C_word)C_i_cadr(t3);
t7=(C_word)C_a_i_list(&a,2,t5,t6);
t8=(C_word)C_a_i_list(&a,1,t7);
C_trace("ChickenBridge.scm: 145  append");
t9=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t9))(4,t9,t4,((C_word*)((C_word*)t0)[6])[1],t8);}}

/* k5642 in do1092 in k5626 in do1089 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5644(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[15],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5644,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[9])+1,t1);
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5647,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],tmp=(C_word)a,a+=8,tmp);
if(C_truep((C_word)C_i_caddr(((C_word*)t0)[4]))){
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5697,a[2]=t3,a[3]=((C_word*)t0)[2],tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_i_caddr(((C_word*)t0)[4]);
t6=(C_word)C_a_i_list(&a,1,t5);
C_trace("ChickenBridge.scm: 145  append");
t7=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t7))(4,t7,t4,((C_word*)((C_word*)t0)[2])[1],t6);}
else{
t4=t3;
f_5647(t4,C_SCHEME_UNDEFINED);}}

/* k5695 in k5642 in do1092 in k5626 in do1089 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5697(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_5647(t3,t2);}

/* k5645 in k5642 in do1092 in k5626 in do1089 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_5647(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[14],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5647,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5650,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
if(C_truep((C_word)C_i_cadddr(((C_word*)t0)[3]))){
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5682,a[2]=t2,a[3]=((C_word*)t0)[2],tmp=(C_word)a,a+=4,tmp);
t4=(C_word)C_i_cadddr(((C_word*)t0)[3]);
t5=(C_word)C_a_i_list(&a,1,t4);
C_trace("ChickenBridge.scm: 145  append");
t6=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t3,((C_word*)((C_word*)t0)[2])[1],t5);}
else{
t3=t2;
f_5650(t3,C_SCHEME_UNDEFINED);}}

/* k5680 in k5645 in k5642 in do1092 in k5626 in do1089 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5682(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_5650(t3,t2);}

/* k5648 in k5645 in k5642 in do1092 in k5626 in do1089 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_5650(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5650,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5653,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5663,a[2]=((C_word*)t0)[2],a[3]=t2,a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  fifth");
t4=C_retrieve(lf[243]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)t0)[2]);}

/* k5661 in k5648 in k5645 in k5642 in do1092 in k5626 in do1089 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5663(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5663,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5667,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5675,a[2]=((C_word*)t0)[4],a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  fifth");
t4=C_retrieve(lf[243]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)t0)[2]);}
else{
t2=((C_word*)t0)[3];
f_5653(t2,C_SCHEME_UNDEFINED);}}

/* k5673 in k5661 in k5648 in k5645 in k5642 in do1092 in k5626 in do1089 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5675(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5675,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,t1);
C_trace("ChickenBridge.scm: 145  append");
t3=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t2);}

/* k5665 in k5661 in k5648 in k5645 in k5642 in do1092 in k5626 in do1089 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5667(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_5653(t3,t2);}

/* k5651 in k5648 in k5645 in k5642 in do1092 in k5626 in do1089 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_5653(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_5630(t3,((C_word*)t0)[2],t2);}

/* k5615 in do1089 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5617(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_5607(t3,((C_word*)t0)[2],t2);}

/* k5297 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5299(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5299,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_5302,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],a[10]=((C_word*)t0)[10],a[11]=((C_word*)t0)[11],tmp=(C_word)a,a+=12,tmp);
t3=(C_word)C_i_cadddr(((C_word*)((C_word*)t0)[3])[1]);
t4=C_SCHEME_UNDEFINED;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_set_block_item(t5,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5571,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=t5,a[5]=((C_word*)t0)[11],a[6]=lf[526],tmp=(C_word)a,a+=7,tmp));
t7=((C_word*)t5)[1];
f_5571(t7,t2,t3);}

/* do1103 in k5297 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_5571(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5571,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_5582,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=t2,a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5597,a[2]=((C_word*)t0)[5],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t4,t5,((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]);}}

/* k5595 in do1103 in k5297 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5597(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5597,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,t1);
C_trace("ChickenBridge.scm: 145  append");
t3=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t2);}

/* k5580 in do1103 in k5297 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5582(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[5])+1,t1);
t3=(C_word)C_i_cdr(((C_word*)t0)[4]);
t4=((C_word*)((C_word*)t0)[3])[1];
f_5571(t4,((C_word*)t0)[2],t3);}

/* k5300 in k5297 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5302(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5302,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_5306,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],a[8]=((C_word*)t0)[9],a[9]=((C_word*)t0)[10],a[10]=((C_word*)t0)[11],tmp=(C_word)a,a+=11,tmp);
C_trace("ChickenBridge.scm: 145  append");
t3=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t2,((C_word*)((C_word*)t0)[11])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k5304 in k5300 in k5297 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5306(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[20],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5306,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[10])+1,t1);
t3=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_5309,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[10],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],a[10]=((C_word*)t0)[9],tmp=(C_word)a,a+=11,tmp);
t4=(C_word)C_i_caddr(((C_word*)((C_word*)t0)[2])[1]);
t5=C_SCHEME_UNDEFINED;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=C_set_block_item(t6,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5515,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=t6,a[5]=((C_word*)t0)[8],a[6]=lf[525],tmp=(C_word)a,a+=7,tmp));
t8=((C_word*)t6)[1];
f_5515(t8,t3,t4);}

/* do1108 in k5304 in k5300 in k5297 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_5515(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5515,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5525,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=t2,a[7]=((C_word*)t0)[5],tmp=(C_word)a,a+=8,tmp);
t4=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3181(t3,t4);}}

/* k5523 in do1108 in k5304 in k5300 in k5297 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5525(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5525,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5528,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
t3=(C_word)C_i_cadr(t1);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t2,t3,((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]);}

/* k5526 in k5523 in do1108 in k5304 in k5300 in k5297 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5528(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[13],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5528,2,t0,t1);}
t2=t1;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5531,a[2]=t3,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5549,a[2]=t4,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t6=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3227(t5,t6,C_fix(20224));}

/* k5547 in k5526 in k5523 in do1108 in k5304 in k5300 in k5297 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5549(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5549,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,2,lf[178],((C_word*)((C_word*)t0)[3])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[3])+1,t2);
t4=((C_word*)t0)[2];
f_5531(t4,t3);}
else{
t2=((C_word*)t0)[2];
f_5531(t2,C_SCHEME_UNDEFINED);}}

/* k5529 in k5526 in k5523 in do1108 in k5304 in k5300 in k5297 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_5531(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5531,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_5535,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],tmp=(C_word)a,a+=6,tmp);
t3=(C_word)C_a_i_list(&a,1,((C_word*)((C_word*)t0)[2])[1]);
C_trace("ChickenBridge.scm: 145  append");
t4=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,((C_word*)((C_word*)t0)[6])[1],t3);}

/* k5533 in k5529 in k5526 in k5523 in do1108 in k5304 in k5300 in k5297 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5535(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[5])+1,t1);
t3=(C_word)C_i_cdr(((C_word*)t0)[4]);
t4=((C_word*)((C_word*)t0)[3])[1];
f_5515(t4,((C_word*)t0)[2],t3);}

/* k5307 in k5304 in k5300 in k5297 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5309(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[14],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5309,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_5312,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],a[10]=((C_word*)t0)[10],tmp=(C_word)a,a+=11,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)((C_word*)t0)[9])[1]))){
t3=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[9])[1]);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(C_word)C_i_car(((C_word*)((C_word*)t0)[9])[1]);
t5=C_mutate(((C_word *)((C_word*)t0)[9])+1,t4);
t6=t2;
f_5312(t6,t5);}
else{
t4=(C_word)C_a_i_cons(&a,2,lf[177],((C_word*)((C_word*)t0)[9])[1]);
t5=C_mutate(((C_word *)((C_word*)t0)[9])+1,t4);
t6=t2;
f_5312(t6,t5);}}
else{
t3=C_set_block_item(((C_word*)t0)[9],0,C_SCHEME_FALSE);
t4=t2;
f_5312(t4,t3);}}

/* k5310 in k5307 in k5304 in k5300 in k5297 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_5312(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[15],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5312,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5315,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],a[5]=((C_word*)t0)[8],a[6]=((C_word*)t0)[9],a[7]=((C_word*)t0)[10],tmp=(C_word)a,a+=8,tmp);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5478,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t2,a[6]=((C_word*)t0)[8],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  fifth");
t4=C_retrieve(lf[243]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)((C_word*)t0)[2])[1]);}

/* k5476 in k5310 in k5307 in k5304 in k5300 in k5297 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5478(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5478,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5482,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],tmp=(C_word)a,a+=4,tmp);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5486,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  fifth");
t4=C_retrieve(lf[243]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)((C_word*)t0)[2])[1]);}
else{
t2=C_set_block_item(((C_word*)t0)[6],0,C_SCHEME_FALSE);
t3=((C_word*)t0)[5];
f_5315(t3,t2);}}

/* k5484 in k5476 in k5310 in k5307 in k5304 in k5300 in k5297 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5486(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  emit");
f_3299(((C_word*)t0)[4],t1,((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]);}

/* k5480 in k5476 in k5310 in k5307 in k5304 in k5300 in k5297 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5482(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_5315(t3,t2);}

/* k5313 in k5310 in k5307 in k5304 in k5300 in k5297 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_5315(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[31],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5315,NULL,2,t0,t1);}
t2=((C_word*)((C_word*)t0)[7])[1];
if(C_truep(t2)){
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5343,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  gensym");
t4=C_retrieve(lf[237]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,lf[523]);}
else{
t3=(C_word)C_a_i_list(&a,2,((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[5])[1]);
t4=(C_word)C_a_i_cons(&a,2,t3,((C_word*)((C_word*)t0)[2])[1]);
t5=(C_word)C_a_i_cons(&a,2,C_SCHEME_END_OF_LIST,t4);
t6=(C_word)C_a_i_cons(&a,2,lf[524],t5);
t7=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)C_a_i_list(&a,3,lf[445],((C_word*)((C_word*)t0)[3])[1],t6));}}

/* k5341 in k5313 in k5310 in k5307 in k5304 in k5300 in k5297 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5343(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5343,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5346,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 145  gensym");
t3=C_retrieve(lf[237]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,lf[522]);}

/* k5344 in k5341 in k5313 in k5310 in k5307 in k5304 in k5300 in k5297 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5346(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5346,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_5349,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 145  gensym");
t3=C_retrieve(lf[237]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,lf[521]);}

/* k5347 in k5344 in k5341 in k5313 in k5310 in k5307 in k5304 in k5300 in k5297 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5349(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5349,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_5352,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 145  gensym");
t3=C_retrieve(lf[237]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,lf[520]);}

/* k5350 in k5347 in k5344 in k5341 in k5313 in k5310 in k5307 in k5304 in k5300 in k5297 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5352(C_word c,C_word t0,C_word t1){
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
C_word ab[150],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5352,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,((C_word*)t0)[9]);
t3=(C_word)C_a_i_list(&a,2,((C_word*)t0)[8],C_fix(0));
t4=(C_word)C_a_i_list(&a,3,lf[441],C_SCHEME_END_OF_LIST,((C_word*)t0)[9]);
t5=(C_word)C_a_i_list(&a,2,lf[442],t4);
t6=(C_word)C_a_i_list(&a,1,lf[443]);
t7=(C_word)C_a_i_list(&a,3,lf[235],((C_word*)t0)[8],lf[443]);
t8=(C_word)C_a_i_list(&a,3,lf[441],t6,t7);
t9=(C_word)C_a_i_list(&a,2,lf[444],t8);
t10=(C_word)C_a_i_list(&a,3,t3,t5,t9);
t11=(C_word)C_a_i_list(&a,1,t1);
t12=(C_word)C_a_i_list(&a,1,((C_word*)t0)[7]);
t13=(C_word)C_a_i_list(&a,2,lf[446],lf[447]);
t14=(C_word)C_a_i_list(&a,2,lf[446],lf[448]);
t15=(C_word)C_a_i_list(&a,3,lf[449],t13,t14);
t16=(C_word)C_a_i_list(&a,2,t15,((C_word*)t0)[7]);
t17=(C_word)C_a_i_list(&a,4,lf[286],lf[519],t16,((C_word*)t0)[9]);
t18=(C_word)C_a_i_list(&a,2,lf[260],t17);
t19=(C_word)C_a_i_list(&a,2,t1,C_fix(-2));
t20=(C_word)C_a_i_list(&a,4,lf[441],t12,t18,t19);
t21=(C_word)C_a_i_list(&a,3,((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[5])[1],C_fix(-1));
t22=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_5411,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=t2,a[5]=t10,a[6]=t11,a[7]=t20,a[8]=t21,tmp=(C_word)a,a+=9,tmp);
t23=(C_word)C_a_i_list(&a,1,((C_word*)t0)[8]);
C_trace("##sys#append");
t24=*((C_word*)lf[453]+1);
((C_proc4)(void*)(*((C_word*)t24+1)))(4,t24,t22,((C_word*)((C_word*)t0)[2])[1],t23);}

/* k5409 in k5350 in k5347 in k5344 in k5341 in k5313 in k5310 in k5307 in k5304 in k5300 in k5297 in k5294 in k5287 in k5269 in a8604 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5411(C_word c,C_word t0,C_word t1){
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
C_word ab[72],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5411,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,lf[439],t1);
t3=(C_word)C_a_i_list(&a,3,lf[440],((C_word*)t0)[8],t2);
t4=(C_word)C_a_i_list(&a,3,lf[441],C_SCHEME_END_OF_LIST,t3);
t5=(C_word)C_a_i_list(&a,3,lf[451],((C_word*)t0)[7],t4);
t6=(C_word)C_a_i_list(&a,3,lf[441],((C_word*)t0)[6],t5);
t7=(C_word)C_a_i_list(&a,2,lf[452],t6);
t8=(C_word)C_a_i_list(&a,3,lf[445],((C_word*)t0)[5],t7);
t9=(C_word)C_a_i_list(&a,3,lf[441],((C_word*)t0)[4],t8);
t10=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t10+1)))(2,t10,(C_word)C_a_i_list(&a,3,lf[445],((C_word*)((C_word*)t0)[2])[1],t9));}

/* a8558 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8559(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word ab[10],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_8559,4,t0,t1,t2,t3);}
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cadr(t2);
t6=t5;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=(C_word)C_i_caddr(t2);
t9=(C_word)C_i_cadddr(t2);
t10=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_8575,a[2]=t2,a[3]=t1,a[4]=t9,a[5]=t8,a[6]=t7,a[7]=t4,tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 145  fifth");
t11=C_retrieve(lf[243]);
((C_proc3)C_retrieve_proc(t11))(3,t11,t10,t2);}

/* k8573 in a8558 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8575(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8575,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_8578,a[2]=((C_word*)t0)[3],a[3]=t1,a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 145  sixth");
t3=C_retrieve(lf[319]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)t0)[2]);}

/* k8576 in k8573 in a8558 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8578(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8578,2,t0,t1);}
t2=t1;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_8581,a[2]=((C_word*)t0)[2],a[3]=t3,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
if(C_truep(((C_word*)((C_word*)t0)[6])[1])){
t5=(C_word)C_i_car(((C_word*)((C_word*)t0)[6])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[6])+1,t5);
t7=t4;
f_8581(t7,t6);}
else{
t5=t4;
f_8581(t5,C_SCHEME_UNDEFINED);}}

/* k8579 in k8576 in k8573 in a8558 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_8581(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_8581,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_8584,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
if(C_truep(((C_word*)((C_word*)t0)[3])[1])){
t3=(C_word)C_i_cadr(((C_word*)((C_word*)t0)[3])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[3])+1,t3);
t5=t2;
f_8584(t5,t4);}
else{
t3=t2;
f_8584(t3,C_SCHEME_UNDEFINED);}}

/* k8582 in k8579 in k8576 in k8573 in a8558 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_8584(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_8584,NULL,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,6,((C_word*)t0)[8],((C_word*)((C_word*)t0)[7])[1],((C_word*)t0)[6],((C_word*)t0)[5],((C_word*)t0)[4],((C_word*)((C_word*)t0)[3])[1]);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8595,a[2]=t2,a[3]=((C_word*)t0)[2],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-position");
f_3199(t3,((C_word*)t0)[8]);}

/* k8593 in k8582 in k8579 in k8576 in k8573 in a8558 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8595(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3142(((C_word*)t0)[3],C_fix(32512),((C_word*)t0)[2],t1);}

/* k8551 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8553(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(32512),t1);}

/* k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5784(C_word c,C_word t0,C_word t1){
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
C_word ab[63],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5784,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5787,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8408,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(768),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(512),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[176],t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(25088),C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(256),t7);
t9=(C_word)C_a_i_cons(&a,2,lf[139],t8);
t10=(C_word)C_a_i_cons(&a,2,C_fix(768),C_SCHEME_END_OF_LIST);
t11=(C_word)C_a_i_cons(&a,2,t9,t10);
t12=(C_word)C_a_i_cons(&a,2,C_fix(25088),t11);
t13=(C_word)C_a_i_cons(&a,2,C_fix(512),t12);
t14=(C_word)C_a_i_cons(&a,2,lf[176],t13);
t15=(C_word)C_a_i_cons(&a,2,t14,C_SCHEME_END_OF_LIST);
t16=(C_word)C_a_i_cons(&a,2,t6,t15);
t17=(C_word)C_a_i_cons(&a,2,lf[177],t16);
t18=(C_word)C_a_i_cons(&a,2,C_fix(36608),C_SCHEME_END_OF_LIST);
t19=(C_word)C_a_i_cons(&a,2,t17,t18);
t20=(C_word)C_a_i_cons(&a,2,C_fix(25088),t19);
t21=(C_word)C_a_i_cons(&a,2,lf[176],t20);
t22=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8414,a[2]=lf[516],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t3,lf[517],C_fix(37632),t21,t22,C_SCHEME_FALSE);}

/* a8413 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8414(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_word ab[13],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_8414,4,t0,t1,t2,t3);}
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cadr(t2);
t6=t5;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=(C_word)C_i_caddr(t2);
t9=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_8427,a[2]=t1,a[3]=t8,a[4]=t7,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
t10=(C_word)C_i_length(((C_word*)t7)[1]);
if(C_truep((C_word)C_i_nequalp(t10,C_fix(2)))){
t11=C_set_block_item(t7,0,C_SCHEME_END_OF_LIST);
t12=t9;
f_8427(t12,t11);}
else{
t11=(C_word)C_i_cadr(((C_word*)t7)[1]);
t12=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_8453,a[2]=t9,a[3]=t7,a[4]=t11,tmp=(C_word)a,a+=5,tmp);
t13=(C_word)C_i_caddr(((C_word*)t7)[1]);
C_trace("ChickenBridge.scm: 145  remove-token-type");
f_4477(t12,t13,C_fix(256));}}

/* k8451 in a8413 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8453(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8453,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[4],t1);
t3=C_mutate(((C_word *)((C_word*)t0)[3])+1,t2);
t4=((C_word*)t0)[2];
f_8427(t4,t3);}

/* k8425 in a8413 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_8427(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_8427,NULL,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,3,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3142(((C_word*)t0)[2],C_fix(37632),t2,C_SCHEME_FALSE);}

/* k8406 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8408(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(37632),t1);}

/* k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5787(C_word c,C_word t0,C_word t1){
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
C_word ab[72],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5787,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5790,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7951,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(30208),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(256),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[139],t5);
t7=(C_word)C_a_i_cons(&a,2,t6,C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(30208),t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(24576),t8);
t10=(C_word)C_a_i_cons(&a,2,lf[176],t9);
t11=(C_word)C_a_i_cons(&a,2,C_fix(37632),C_SCHEME_END_OF_LIST);
t12=(C_word)C_a_i_cons(&a,2,C_fix(24064),t11);
t13=(C_word)C_a_i_cons(&a,2,lf[176],t12);
t14=(C_word)C_a_i_cons(&a,2,C_fix(37632),C_SCHEME_END_OF_LIST);
t15=(C_word)C_a_i_cons(&a,2,C_fix(24320),t14);
t16=(C_word)C_a_i_cons(&a,2,lf[176],t15);
t17=(C_word)C_a_i_cons(&a,2,t16,C_SCHEME_END_OF_LIST);
t18=(C_word)C_a_i_cons(&a,2,t13,t17);
t19=(C_word)C_a_i_cons(&a,2,t10,t18);
t20=(C_word)C_a_i_cons(&a,2,lf[177],t19);
t21=(C_word)C_a_i_cons(&a,2,t20,C_SCHEME_END_OF_LIST);
t22=(C_word)C_a_i_cons(&a,2,C_fix(13824),t21);
t23=(C_word)C_a_i_cons(&a,2,lf[176],t22);
t24=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7957,a[2]=lf[499],tmp=(C_word)a,a+=3,tmp);
t25=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7996,a[2]=lf[514],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t3,lf[515],C_fix(36352),t23,t24,t25);}

/* a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7996(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[7],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_7996,5,t0,t1,t2,t3,t4);}
t5=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_8000,a[2]=t4,a[3]=t5,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3181(t6,t2);}

/* k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8000(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[18],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8000,2,t0,t1);}
t2=(C_word)C_i_car(t1);
t3=(C_word)C_a_i_list(&a,1,lf[240]);
t4=t3;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8009,a[2]=t3,a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
t7=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_8012,a[2]=t2,a[3]=t3,a[4]=t6,a[5]=((C_word*)t0)[2],a[6]=((C_word*)t0)[3],a[7]=t5,a[8]=t1,tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3227(t7,t2,C_fix(24576));}

/* k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8012(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[16],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8012,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_cdr(((C_word*)t0)[8]);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_8021,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=t4,a[5]=((C_word*)t0)[7],a[6]=lf[502],tmp=(C_word)a,a+=7,tmp));
t6=((C_word*)t4)[1];
f_8021(t6,((C_word*)t0)[4],t2);}
else{
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_8070,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],tmp=(C_word)a,a+=7,tmp);
t3=(C_word)C_i_cadr(((C_word*)t0)[8]);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3181(t2,t3);}}

/* k8068 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8070(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8070,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_8073,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,tmp=(C_word)a,a+=8,tmp);
t3=(C_word)C_i_car(t1);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t2,t3,((C_word*)((C_word*)t0)[4])[1],((C_word*)t0)[3]);}

/* k8071 in k8068 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8073(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8073,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_8076,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=t1,tmp=(C_word)a,a+=9,tmp);
t3=(C_word)C_i_cadr(((C_word*)t0)[7]);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t2,t3,((C_word*)((C_word*)t0)[4])[1],((C_word*)t0)[3]);}

/* k8074 in k8071 in k8068 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8076(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8076,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_8288,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 145  append");
t3=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t2,t1,C_SCHEME_END_OF_LIST);}

/* k8286 in k8074 in k8071 in k8068 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8288(C_word c,C_word t0,C_word t1){
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
C_word ab[28],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8288,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[9],t1);
t3=(C_word)C_i_caddr(((C_word*)t0)[8]);
t4=C_SCHEME_FALSE;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_SCHEME_FALSE;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_8085,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t3,a[5]=t2,a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[9],a[8]=((C_word*)t0)[5],a[9]=((C_word*)t0)[6],a[10]=((C_word*)t0)[7],a[11]=t7,a[12]=t5,tmp=(C_word)a,a+=13,tmp);
t9=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t9))){
t10=t8;
f_8085(t10,C_SCHEME_UNDEFINED);}
else{
t10=(C_word)C_i_length(t2);
t11=(C_word)C_a_i_minus(&a,2,t10,C_fix(2));
t12=(C_word)C_i_list_tail(t2,t11);
t13=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8226,a[2]=t12,a[3]=t8,tmp=(C_word)a,a+=4,tmp);
t14=(C_word)C_i_cadr(t12);
C_trace("ChickenBridge.scm: 145  symbol->string");
t15=*((C_word*)lf[413]+1);
((C_proc3)C_retrieve_proc(t15))(3,t15,t13,t14);}}

/* k8224 in k8286 in k8074 in k8071 in k8068 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8226(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[13],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8226,2,t0,t1);}
t2=(C_word)C_i_string_length(t1);
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_8235,a[2]=t1,a[3]=t2,a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_greaterp(t2,C_fix(3)))){
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8260,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
t5=(C_word)C_a_i_minus(&a,2,t2,C_fix(3));
C_trace("ChickenBridge.scm: 145  substring");
t6=*((C_word*)lf[264]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t4,t1,t5);}
else{
t4=t3;
f_8235(t4,C_SCHEME_FALSE);}}

/* k8258 in k8224 in k8286 in k8074 in k8071 in k8068 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8260(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_8235(t2,(C_word)C_i_string_equal_p(t1,lf[513]));}

/* k8233 in k8224 in k8286 in k8074 in k8071 in k8068 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_8235(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_8235,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8242,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8246,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_minus(&a,2,((C_word*)t0)[3],C_fix(3));
C_trace("ChickenBridge.scm: 145  substring");
t5=*((C_word*)lf[264]+1);
((C_proc5)C_retrieve_proc(t5))(5,t5,t3,((C_word*)t0)[2],C_fix(0),t4);}
else{
t2=((C_word*)t0)[5];
f_8085(t2,C_SCHEME_UNDEFINED);}}

/* k8244 in k8233 in k8224 in k8286 in k8074 in k8071 in k8068 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8246(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  string->symbol");
t2=*((C_word*)lf[173]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k8240 in k8233 in k8224 in k8286 in k8074 in k8071 in k8068 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8242(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
f_8085(t2,(C_word)C_i_set_cdr(((C_word*)t0)[2],t1));}

/* k8083 in k8286 in k8074 in k8071 in k8068 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_8085(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[18],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_8085,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_8088,a[2]=((C_word*)t0)[7],a[3]=((C_word*)t0)[8],a[4]=((C_word*)t0)[9],a[5]=((C_word*)t0)[10],a[6]=((C_word*)t0)[11],a[7]=((C_word*)t0)[12],tmp=(C_word)a,a+=8,tmp);
t3=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_8163,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t2,a[6]=((C_word*)t0)[12],a[7]=((C_word*)t0)[5],a[8]=((C_word*)t0)[11],a[9]=((C_word*)t0)[6],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3227(t3,((C_word*)t0)[2],C_fix(24064));}

/* k8161 in k8083 in k8286 in k8074 in k8071 in k8068 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8163(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[18],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8163,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_8167,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],a[8]=((C_word*)t0)[9],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 145  add-emit-info");
f_3271(t2,lf[510],C_SCHEME_TRUE,((C_word*)((C_word*)t0)[9])[1]);}
else{
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_8204,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],a[8]=((C_word*)t0)[9],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3227(t2,((C_word*)t0)[2],C_fix(24320));}}

/* k8202 in k8161 in k8083 in k8286 in k8074 in k8071 in k8068 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8204(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8204,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_8208,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 145  add-emit-info");
f_3271(t2,lf[512],C_SCHEME_TRUE,((C_word*)((C_word*)t0)[8])[1]);}
else{
t2=((C_word*)t0)[4];
f_8088(t2,C_SCHEME_UNDEFINED);}}

/* k8206 in k8202 in k8161 in k8083 in k8286 in k8074 in k8071 in k8068 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8208(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8208,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_8212,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t3,((C_word*)t0)[3],((C_word*)((C_word*)t0)[8])[1],((C_word*)t0)[2]);}

/* k8210 in k8206 in k8202 in k8161 in k8083 in k8286 in k8074 in k8071 in k8068 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8212(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8212,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[5])+1,t1);
t3=(C_word)C_a_i_list(&a,3,lf[500],((C_word*)t0)[4],((C_word*)((C_word*)t0)[5])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[5])+1,t3);
t5=C_mutate(((C_word *)((C_word*)t0)[3])+1,lf[511]);
t6=((C_word*)t0)[2];
f_8088(t6,t5);}

/* k8165 in k8161 in k8083 in k8286 in k8074 in k8071 in k8068 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8167(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8167,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_8171,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t3,((C_word*)t0)[3],((C_word*)((C_word*)t0)[8])[1],((C_word*)t0)[2]);}

/* k8169 in k8165 in k8161 in k8083 in k8286 in k8074 in k8071 in k8068 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8171(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8171,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_8174,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8198,a[2]=t3,a[3]=((C_word*)t0)[6],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  get-emit-info");
f_3259(t4,lf[510],((C_word*)((C_word*)t0)[2])[1]);}

/* k8196 in k8169 in k8165 in k8161 in k8083 in k8286 in k8074 in k8071 in k8068 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8198(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[18],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8198,2,t0,t1);}
t2=(C_word)C_eqp(lf[508],t1);
if(C_truep(t2)){
t3=(C_word)C_a_i_list(&a,1,lf[509]);
t4=(C_word)C_a_i_list(&a,3,lf[441],t3,((C_word*)((C_word*)t0)[3])[1]);
t5=(C_word)C_a_i_list(&a,2,lf[452],t4);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t5);
t7=((C_word*)t0)[2];
f_8174(t7,t6);}
else{
t3=((C_word*)t0)[2];
f_8174(t3,C_SCHEME_UNDEFINED);}}

/* k8172 in k8169 in k8165 in k8161 in k8083 in k8286 in k8074 in k8071 in k8068 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_8174(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_8174,NULL,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,3,lf[500],((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t4=C_mutate(((C_word *)((C_word*)t0)[3])+1,lf[507]);
t5=((C_word*)t0)[2];
f_8088(t5,t4);}

/* k8086 in k8083 in k8286 in k8074 in k8071 in k8068 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_8088(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[15],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_8088,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_8091,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],tmp=(C_word)a,a+=6,tmp);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_8102,a[2]=((C_word*)t0)[3],a[3]=t2,a[4]=((C_word*)t0)[7],tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8160,a[2]=((C_word*)t0)[7],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  symbol->string");
t5=*((C_word*)lf[413]+1);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,((C_word*)t0)[2]);}

/* k8158 in k8086 in k8083 in k8286 in k8074 in k8071 in k8068 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8160(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  string-append");
t2=*((C_word*)lf[261]+1);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1,lf[506]);}

/* k8100 in k8086 in k8083 in k8286 in k8074 in k8071 in k8068 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8102(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8102,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_8104,a[2]=t3,a[3]=((C_word*)t0)[4],a[4]=lf[505],tmp=(C_word)a,a+=5,tmp));
t5=((C_word*)t3)[1];
f_8104(t5,((C_word*)t0)[3],t1,((C_word*)t0)[2]);}

/* do1189 in k8100 in k8086 in k8083 in k8286 in k8074 in k8071 in k8068 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_8104(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[16],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_8104,NULL,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8119,a[2]=t1,a[3]=((C_word*)t0)[3],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  string-append");
t6=*((C_word*)lf[261]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t5,((C_word*)t4)[1],lf[503]);}
else{
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_8123,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=t3,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8152,a[2]=t4,a[3]=t5,tmp=(C_word)a,a+=4,tmp);
t7=(C_word)C_i_car(t3);
C_trace("ChickenBridge.scm: 145  symbol->string");
t8=*((C_word*)lf[413]+1);
((C_proc3)C_retrieve_proc(t8))(3,t8,t6,t7);}}

/* k8150 in do1189 in k8100 in k8086 in k8083 in k8286 in k8074 in k8071 in k8068 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8152(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  string-append");
t2=*((C_word*)lf[261]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k8121 in do1189 in k8100 in k8086 in k8083 in k8286 in k8074 in k8071 in k8068 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8123(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8123,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[5])+1,t1);
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_8126,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t4=(C_word)C_i_cdr(((C_word*)t0)[4]);
if(C_truep((C_word)C_i_nullp(t4))){
t5=t3;
f_8126(t5,C_SCHEME_UNDEFINED);}
else{
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8140,a[2]=t3,a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  string-append");
t6=*((C_word*)lf[261]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t5,((C_word*)((C_word*)t0)[5])[1],lf[504]);}}

/* k8138 in k8121 in do1189 in k8100 in k8086 in k8083 in k8286 in k8074 in k8071 in k8068 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8140(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_8126(t3,t2);}

/* k8124 in k8121 in do1189 in k8100 in k8086 in k8083 in k8286 in k8074 in k8071 in k8068 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_8126(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[5]);
t3=((C_word*)((C_word*)t0)[4])[1];
f_8104(t3,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t2);}

/* k8117 in do1189 in k8100 in k8086 in k8083 in k8286 in k8074 in k8071 in k8068 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8119(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8119,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,2,lf[279],t1);
t3=C_mutate(((C_word *)((C_word*)t0)[3])+1,t2);
t4=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,t3);}

/* k8089 in k8086 in k8083 in k8286 in k8074 in k8071 in k8068 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8091(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8091,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,2,((C_word*)((C_word*)t0)[5])[1],((C_word*)((C_word*)t0)[4])[1]);
t3=((C_word*)t0)[3];
f_8009(2,t3,(C_word)C_i_set_cdr(((C_word*)t0)[2],t2));}

/* do1163 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_8021(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_8021,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_8031,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=t2,a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
t4=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t3,t4,((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]);}}

/* k8029 in do1163 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8031(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8031,2,t0,t1);}
t2=(C_word)C_i_car(t1);
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_8037,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=t2,a[7]=t1,tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 145  sprintf");
t4=C_retrieve(lf[286]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t3,lf[501],t2);}

/* k8035 in k8029 in do1163 in k8010 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8037(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[18],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8037,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,lf[500],((C_word*)t0)[7]);
t3=(C_word)C_a_i_list(&a,3,lf[278],t1,((C_word*)t0)[6]);
t4=(C_word)C_a_i_list(&a,2,t2,t3);
t5=(C_word)C_i_set_cdr(((C_word*)((C_word*)t0)[5])[1],t4);
t6=(C_word)C_i_cddr(((C_word*)((C_word*)t0)[5])[1]);
t7=C_mutate(((C_word *)((C_word*)t0)[5])+1,t6);
t8=(C_word)C_i_cdr(((C_word*)t0)[4]);
t9=((C_word*)((C_word*)t0)[3])[1];
f_8021(t9,((C_word*)t0)[2],t8);}

/* k8007 in k7998 in a7995 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_8009(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,((C_word*)t0)[2]);}

/* a7956 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7957(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word ab[11],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_7957,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=(C_word)C_i_cadr(((C_word*)t4)[1]);
t6=C_set_block_item(t4,0,t5);
t7=(C_word)C_i_car(((C_word*)t4)[1]);
t8=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7968,a[2]=t4,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
t9=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7974,a[2]=t8,a[3]=t7,a[4]=t4,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3227(t9,t7,C_fix(24576));}

/* k7972 in a7956 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7974(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7974,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_cadr(((C_word*)((C_word*)t0)[4])[1]);
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_7990,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[3],a[5]=t2,tmp=(C_word)a,a+=6,tmp);
t4=(C_word)C_i_caddr(((C_word*)((C_word*)t0)[4])[1]);
C_trace("ChickenBridge.scm: 145  remove-token-type");
f_4477(t3,t4,C_fix(256));}
else{
t2=((C_word*)t0)[2];
f_7968(t2,C_SCHEME_UNDEFINED);}}

/* k7988 in k7972 in a7956 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7990(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7990,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[5],t1);
t3=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[4],t2);
t4=C_mutate(((C_word *)((C_word*)t0)[3])+1,t3);
t5=((C_word*)t0)[2];
f_7968(t5,t4);}

/* k7966 in a7956 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_7968(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3142(((C_word*)t0)[3],C_fix(36352),((C_word*)((C_word*)t0)[2])[1],C_SCHEME_FALSE);}

/* k7949 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7951(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(36352),t1);}

/* k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5790(C_word c,C_word t0,C_word t1){
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
C_word ab[57],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5790,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5793,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7875,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(33792),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(35584),t4);
t6=(C_word)C_a_i_cons(&a,2,C_fix(35072),t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(36096),t6);
t8=(C_word)C_a_i_cons(&a,2,C_fix(34816),t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(35328),t8);
t10=(C_word)C_a_i_cons(&a,2,C_fix(31488),t9);
t11=(C_word)C_a_i_cons(&a,2,C_fix(31744),t10);
t12=(C_word)C_a_i_cons(&a,2,C_fix(32512),t11);
t13=(C_word)C_a_i_cons(&a,2,C_fix(32256),t12);
t14=(C_word)C_a_i_cons(&a,2,C_fix(30464),t13);
t15=(C_word)C_a_i_cons(&a,2,C_fix(34304),t14);
t16=(C_word)C_a_i_cons(&a,2,C_fix(34560),t15);
t17=(C_word)C_a_i_cons(&a,2,C_fix(33536),t16);
t18=(C_word)C_a_i_cons(&a,2,C_fix(32000),t17);
t19=(C_word)C_a_i_cons(&a,2,C_fix(36352),t18);
t20=(C_word)C_a_i_cons(&a,2,lf[177],t19);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t3,lf[498],C_fix(36608),t20,C_SCHEME_FALSE,C_SCHEME_FALSE);}

/* k7873 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7875(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(36608),t1);}

/* k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5793(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[18],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5793,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5796,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7831,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(36608),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,lf[215],t4);
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7837,a[2]=lf[495],tmp=(C_word)a,a+=3,tmp);
t7=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7851,a[2]=lf[496],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2844(t3,lf[497],C_fix(36864),t5,t6,t7);}

/* a7850 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7851(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[8],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_7851,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7859,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7863,a[2]=t4,a[3]=t3,a[4]=t5,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3181(t6,t2);}

/* k7861 in a7850 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7863(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  emit");
f_3299(((C_word*)t0)[4],t1,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k7857 in a7850 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7859(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7859,2,t0,t1);}
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_cons(&a,2,lf[240],t1));}

/* a7836 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7837(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word ab[4],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_7837,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7845,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  parse-unit-position");
f_3199(t4,t5);}

/* k7843 in a7836 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7845(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3142(((C_word*)t0)[3],C_fix(36864),((C_word*)t0)[2],t1);}

/* k7829 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7831(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(36864),t1);}

/* k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5796(C_word c,C_word t0,C_word t1){
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
C_word ab[99],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5796,2,t0,t1);}
t2=lf[256]=C_SCHEME_FALSE;;
t3=lf[257]=C_SCHEME_FALSE;;
t4=lf[258]=C_SCHEME_FALSE;;
t5=C_mutate((C_word*)lf[259]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5802,a[2]=lf[277],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[278]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5973,a[2]=lf[292],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate((C_word*)lf[293]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6152,a[2]=lf[295],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate((C_word*)lf[296]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6161,a[2]=lf[304],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate((C_word*)lf[305]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6208,a[2]=lf[307],tmp=(C_word)a,a+=3,tmp));
t10=C_mutate((C_word*)lf[308]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6214,a[2]=lf[310],tmp=(C_word)a,a+=3,tmp));
t11=C_mutate((C_word*)lf[311]+1,*((C_word*)lf[246]+1));
t12=C_mutate((C_word*)lf[312]+1,*((C_word*)lf[313]+1));
t13=C_mutate((C_word*)lf[314]+1,*((C_word*)lf[315]+1));
t14=C_mutate((C_word*)lf[316]+1,*((C_word*)lf[317]+1));
t15=C_mutate((C_word*)lf[243]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6236,a[2]=lf[318],tmp=(C_word)a,a+=3,tmp));
t16=C_mutate((C_word*)lf[319]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6246,a[2]=lf[320],tmp=(C_word)a,a+=3,tmp));
t17=C_mutate((C_word*)lf[321]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6256,a[2]=lf[322],tmp=(C_word)a,a+=3,tmp));
t18=C_mutate((C_word*)lf[323]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6266,a[2]=lf[324],tmp=(C_word)a,a+=3,tmp));
t19=C_mutate((C_word*)lf[325]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6276,a[2]=lf[326],tmp=(C_word)a,a+=3,tmp));
t20=C_mutate((C_word*)lf[327]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6290,a[2]=lf[328],tmp=(C_word)a,a+=3,tmp));
t21=C_mutate((C_word*)lf[329]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6310,a[2]=lf[330],tmp=(C_word)a,a+=3,tmp));
t22=C_mutate((C_word*)lf[331]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6330,a[2]=lf[332],tmp=(C_word)a,a+=3,tmp));
t23=C_mutate((C_word*)lf[333]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6378,a[2]=lf[335],tmp=(C_word)a,a+=3,tmp));
t24=C_mutate((C_word*)lf[336]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6418,a[2]=lf[339],tmp=(C_word)a,a+=3,tmp));
t25=C_mutate((C_word*)lf[294]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6429,a[2]=lf[343],tmp=(C_word)a,a+=3,tmp));
t26=C_mutate((C_word*)lf[279]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6458,a[2]=lf[344],tmp=(C_word)a,a+=3,tmp));
t27=C_mutate((C_word*)lf[260]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6472,a[2]=lf[345],tmp=(C_word)a,a+=3,tmp));
t28=C_mutate((C_word*)lf[346]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6515,a[2]=lf[347],tmp=(C_word)a,a+=3,tmp));
t29=C_mutate((C_word*)lf[348]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6518,a[2]=lf[349],tmp=(C_word)a,a+=3,tmp));
t30=C_mutate(&lf[350],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6530,a[2]=lf[353],tmp=(C_word)a,a+=3,tmp));
t31=C_mutate(&lf[354],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6539,a[2]=lf[356],tmp=(C_word)a,a+=3,tmp));
t32=C_mutate(&lf[357],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6583,a[2]=lf[359],tmp=(C_word)a,a+=3,tmp));
t33=C_mutate((C_word*)lf[297]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6605,a[2]=lf[361],tmp=(C_word)a,a+=3,tmp));
t34=C_mutate((C_word*)lf[362]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6624,a[2]=lf[369],tmp=(C_word)a,a+=3,tmp));
t35=C_mutate((C_word*)lf[370]+1,C_retrieve(lf[348]));
t36=C_mutate((C_word*)lf[371]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6792,a[2]=lf[378],tmp=(C_word)a,a+=3,tmp));
t37=C_mutate((C_word*)lf[379]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6855,a[2]=lf[381],tmp=(C_word)a,a+=3,tmp));
t38=C_mutate((C_word*)lf[382]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6864,a[2]=lf[384],tmp=(C_word)a,a+=3,tmp));
t39=C_mutate((C_word*)lf[385]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6870,a[2]=lf[387],tmp=(C_word)a,a+=3,tmp));
t40=C_mutate((C_word*)lf[388]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6879,a[2]=lf[391],tmp=(C_word)a,a+=3,tmp));
t41=C_mutate((C_word*)lf[392]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6937,a[2]=lf[394],tmp=(C_word)a,a+=3,tmp));
t42=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6948,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 369  make-hash-table");
t43=C_retrieve(lf[493]);
((C_proc3)C_retrieve_proc(t43))(3,t43,t42,*((C_word*)lf[494]+1));}

/* k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6948(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6948,2,t0,t1);}
t2=C_mutate(&lf[395],t1);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6951,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7777,a[2]=lf[491],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 371  ##sys#register-macro");
t5=C_retrieve(lf[468]);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,lf[492],t4);}

/* a7776 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7777(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_7777,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_7781,a[2]=t6,a[3]=t1,a[4]=t3,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t4)[1]))){
t8=(C_word)C_i_car(((C_word*)t4)[1]);
t9=C_set_block_item(t6,0,t8);
t10=(C_word)C_i_cadr(((C_word*)t4)[1]);
t11=C_set_block_item(t4,0,t10);
t12=t7;
f_7781(2,t12,t11);}
else{
if(C_truep((C_word)C_i_stringp(((C_word*)t4)[1]))){
t8=C_set_block_item(t6,0,((C_word*)t4)[1]);
t9=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7814,a[2]=t7,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 378  string->symbol");
t10=*((C_word*)lf[173]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)t4)[1]);}
else{
if(C_truep((C_word)C_i_symbolp(((C_word*)t4)[1]))){
t8=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7824,a[2]=t7,a[3]=t6,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 380  symbol->string");
t9=*((C_word*)lf[413]+1);
((C_proc3)C_retrieve_proc(t9))(3,t9,t8,((C_word*)t4)[1]);}
else{
C_trace("ChickenBridge.scm: 382  error");
t8=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,lf[490]);}}}}

/* k7822 in a7776 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7824(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_7781(2,t3,t2);}

/* k7812 in a7776 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7814(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_7781(2,t3,t2);}

/* k7779 in a7776 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7781(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7781,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[4]);
t3=(C_word)C_a_i_list(&a,2,lf[446],t2);
t4=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_a_i_list(&a,4,lf[470],lf[489],((C_word*)((C_word*)t0)[2])[1],t3));}

/* k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6951(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6951,2,t0,t1);}
t2=C_mutate((C_word*)lf[396]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6953,a[2]=lf[414],tmp=(C_word)a,a+=3,tmp));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7224,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7771,a[2]=lf[487],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 466  ##sys#register-macro");
t5=C_retrieve(lf[468]);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,lf[488],t4);}

/* a7770 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7771(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr3r,(void*)f_7771r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_7771r(t0,t1,t2,t3);}}

static void C_ccall f_7771r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_trace("ChickenBridge.scm: 467  expand-send");
t4=C_retrieve(lf[396]);
((C_proc5)C_retrieve_proc(t4))(5,t4,t1,t2,t3,C_SCHEME_FALSE);}

/* k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7224(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_7224,2,t0,t1);}
t2=C_mutate((C_word*)lf[415]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7226,a[2]=lf[417],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[418]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7232,a[2]=lf[420],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate((C_word*)lf[421]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7238,a[2]=lf[423],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate((C_word*)lf[424]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7244,a[2]=lf[426],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[427]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7250,a[2]=lf[429],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate((C_word*)lf[430]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7256,a[2]=lf[432],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate((C_word*)lf[433]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7262,a[2]=lf[435],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate((C_word*)lf[436]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7268,a[2]=lf[437],tmp=(C_word)a,a+=3,tmp));
t10=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7280,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 495  hash-table-set!");
t11=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t11))(5,t11,t10,C_retrieve2(lf[395],"*messages*"),lf[485],lf[486]);}

/* k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7280(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7280,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7283,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 496  hash-table-set!");
t3=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,C_retrieve2(lf[395],"*messages*"),lf[483],lf[484]);}

/* k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7283(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7283,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7286,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 497  hash-table-set!");
t3=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,C_retrieve2(lf[395],"*messages*"),lf[481],lf[482]);}

/* k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7286(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7286,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7289,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 498  hash-table-set!");
t3=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,C_retrieve2(lf[395],"*messages*"),lf[479],lf[480]);}

/* k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7289(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7289,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7292,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 499  hash-table-set!");
t3=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,C_retrieve2(lf[395],"*messages*"),lf[477],lf[478]);}

/* k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7292(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7292,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7295,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 500  hash-table-set!");
t3=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,C_retrieve2(lf[395],"*messages*"),lf[475],lf[476]);}

/* k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7295(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7295,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7298,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 501  hash-table-set!");
t3=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,C_retrieve2(lf[395],"*messages*"),lf[473],lf[474]);}

/* k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7298(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7298,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7301,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 502  hash-table-set!");
t3=C_retrieve(lf[470]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,C_retrieve2(lf[395],"*messages*"),lf[471],lf[472]);}

/* k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7301(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7301,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7304,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7765,a[2]=lf[467],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 508  ##sys#register-macro");
t4=C_retrieve(lf[468]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,lf[469],t3);}

/* a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7765(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+17)){
C_save_and_reclaim((void*)tr4r,(void*)f_7765r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest(a,C_rest_count(0));
f_7765r(t0,t1,t2,t3,t4);}}

static void C_ccall f_7765r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
t13=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_7319,a[2]=t2,a[3]=t12,a[4]=t6,a[5]=t10,a[6]=t1,a[7]=t8,a[8]=t3,tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(t2))){
t14=t13;
f_7319(2,t14,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 517  error");
t14=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t14))(4,t14,t13,lf[466],t2);}}

/* k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7319(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7319,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_7322,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(((C_word*)t0)[8]))){
if(C_truep((C_word)C_i_nullp(((C_word*)t0)[8]))){
C_trace("ChickenBridge.scm: 521  error");
t3=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,lf[464]);}
else{
t3=t2;
f_7322(2,t3,C_SCHEME_UNDEFINED);}}
else{
C_trace("ChickenBridge.scm: 519  error");
t3=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t2,lf[465],((C_word*)t0)[8]);}}

/* k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7322(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7322,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_7325,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],tmp=(C_word)a,a+=8,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_7600,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[7],a[5]=t4,a[6]=lf[463],tmp=(C_word)a,a+=7,tmp));
t6=((C_word*)t4)[1];
f_7600(t6,t2,((C_word*)t0)[2]);}

/* do1637 in k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_7600(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_7600,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7610,a[2]=t1,a[3]=((C_word*)t0)[5],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_7620,a[2]=t3,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=t2,tmp=(C_word)a,a+=7,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7708,a[2]=t4,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t7=(C_word)C_i_car(t2);
t8=(C_word)C_i_length(t7);
C_trace("ChickenBridge.scm: 525  <");
C_lessp(5,0,t6,C_fix(0),t8,C_fix(4));}
else{
t6=t4;
f_7620(t6,C_SCHEME_FALSE);}}}

/* k7706 in do1637 in k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7708(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=(C_word)C_i_car(t2);
t4=((C_word*)t0)[2];
f_7620(t4,(C_word)C_i_symbolp(t3));}
else{
t2=((C_word*)t0)[2];
f_7620(t2,C_SCHEME_FALSE);}}

/* k7618 in do1637 in k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_7620(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_7620,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[6]);
t3=(C_word)C_i_car(t2);
t4=(C_word)C_i_car(((C_word*)t0)[6]);
t5=(C_word)C_i_cadr(t4);
t6=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_7629,a[2]=t5,a[3]=t3,a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[5],tmp=(C_word)a,a+=8,tmp);
t7=(C_word)C_i_car(((C_word*)t0)[6]);
t8=(C_word)C_i_cddr(t7);
if(C_truep((C_word)C_i_nullp(t8))){
t9=t6;
f_7629(t9,lf[461]);}
else{
t9=(C_word)C_i_car(((C_word*)t0)[6]);
t10=t6;
f_7629(t10,(C_word)C_i_caddr(t9));}}
else{
t2=(C_word)C_i_car(((C_word*)t0)[6]);
C_trace("ChickenBridge.scm: 538  error");
t3=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[2],lf[462],t2);}}

/* k7627 in k7618 in do1637 in k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_7629(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_7629,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_7633,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t3=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 533  append");
t4=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,((C_word*)((C_word*)t0)[7])[1],t3);}

/* k7631 in k7627 in k7618 in do1637 in k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7633(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7633,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_7637,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
t4=(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 534  append");
t5=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,((C_word*)((C_word*)t0)[7])[1],t4);}

/* k7635 in k7631 in k7627 in k7618 in do1637 in k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7637(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_7637,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7641,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7645,a[2]=((C_word*)t0)[5],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_eqp(((C_word*)t0)[3],lf[461]);
if(C_truep(t5)){
t6=t4;
f_7645(t6,C_SCHEME_END_OF_LIST);}
else{
t6=(C_word)C_a_i_list(&a,3,lf[235],((C_word*)t0)[2],((C_word*)t0)[3]);
t7=t4;
f_7645(t7,(C_word)C_a_i_list(&a,1,t6));}}

/* k7643 in k7635 in k7631 in k7627 in k7618 in do1637 in k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_7645(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 535  append");
t2=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k7639 in k7635 in k7631 in k7627 in k7618 in do1637 in k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7641(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_7610(2,t3,t2);}

/* k7608 in do1637 in k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7610(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_7600(t3,((C_word*)t0)[2],t2);}

/* k7323 in k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7325(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7325,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_7328,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 540  gensym");
t3=C_retrieve(lf[237]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k7326 in k7323 in k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7328(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7328,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_7331,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 541  gensym");
t3=C_retrieve(lf[237]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k7329 in k7326 in k7323 in k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7331(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7331,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_7334,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 542  gensym");
t3=C_retrieve(lf[237]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k7332 in k7329 in k7326 in k7323 in k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7334(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7334,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_7337,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],a[10]=((C_word*)t0)[9],tmp=(C_word)a,a+=11,tmp);
C_trace("ChickenBridge.scm: 543  gensym");
t3=C_retrieve(lf[237]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k7335 in k7332 in k7329 in k7326 in k7323 in k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7337(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_7337,2,t0,t1);}
t2=C_SCHEME_TRUE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_SCHEME_END_OF_LIST;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_7340,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=t3,a[7]=((C_word*)t0)[5],a[8]=((C_word*)t0)[6],a[9]=((C_word*)t0)[7],a[10]=((C_word*)t0)[8],a[11]=((C_word*)t0)[9],a[12]=t5,a[13]=((C_word*)t0)[10],tmp=(C_word)a,a+=14,tmp);
t7=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7493,a[2]=t6,a[3]=t3,a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)((C_word*)t0)[3])[1]))){
t8=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
if(C_truep((C_word)C_i_pairp(t8))){
t9=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7594,a[2]=t7,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 549  caar");
t10=*((C_word*)lf[457]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)((C_word*)t0)[3])[1]);}
else{
t9=t7;
f_7493(t9,C_SCHEME_FALSE);}}
else{
t8=t7;
f_7493(t8,C_SCHEME_FALSE);}}

/* k7592 in k7335 in k7332 in k7329 in k7326 in k7323 in k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7594(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_7493(t2,(C_word)C_eqp(t1,lf[460]));}

/* k7491 in k7335 in k7332 in k7329 in k7326 in k7323 in k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_7493(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_7493,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7500,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 550  cdar");
t3=*((C_word*)lf[455]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)((C_word*)t0)[4])[1]);}
else{
t2=((C_word*)t0)[2];
f_7340(2,t2,C_SCHEME_UNDEFINED);}}

/* k7498 in k7491 in k7335 in k7332 in k7329 in k7326 in k7323 in k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7500(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7500,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_7502,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=lf[459],tmp=(C_word)a,a+=6,tmp));
t5=((C_word*)t3)[1];
f_7502(t5,((C_word*)t0)[2],t1);}

/* do1653 in k7498 in k7491 in k7335 in k7332 in k7329 in k7326 in k7323 in k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_7502(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_7502,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[4])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[4])+1,t3);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,t4);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7516,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7526,a[2]=t2,a[3]=((C_word*)t0)[2],a[4]=t3,tmp=(C_word)a,a+=5,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7574,a[2]=t4,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 554  cdar");
t7=*((C_word*)lf[455]+1);
((C_proc3)C_retrieve_proc(t7))(3,t7,t6,t2);}
else{
t6=t4;
f_7526(t6,C_SCHEME_FALSE);}}}

/* k7572 in do1653 in k7498 in k7491 in k7335 in k7332 in k7329 in k7326 in k7323 in k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7574(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_7526(t2,(C_word)C_i_pairp(t1));}

/* k7524 in do1653 in k7498 in k7491 in k7335 in k7332 in k7329 in k7326 in k7323 in k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_7526(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_7526,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7529,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 555  caar");
t3=*((C_word*)lf[457]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)t0)[2]);}
else{
t2=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 561  error");
t3=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[4],lf[458],t2);}}

/* k7527 in k7524 in do1653 in k7498 in k7491 in k7335 in k7332 in k7329 in k7326 in k7323 in k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7529(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7529,2,t0,t1);}
t2=(C_word)C_eqp(t1,lf[454]);
if(C_truep(t2)){
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7550,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 557  cdar");
t4=*((C_word*)lf[455]+1);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)t0)[2]);}
else{
t3=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 560  error");
t4=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,((C_word*)t0)[4],lf[456],t3);}}

/* k7548 in k7527 in k7524 in do1653 in k7498 in k7491 in k7335 in k7332 in k7329 in k7326 in k7323 in k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7550(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep((C_word)C_i_car(t1))){
t2=((C_word*)t0)[3];
f_7516(2,t2,C_SCHEME_UNDEFINED);}
else{
t2=C_set_block_item(((C_word*)t0)[2],0,C_SCHEME_FALSE);
t3=((C_word*)t0)[3];
f_7516(2,t3,t2);}}

/* k7514 in do1653 in k7498 in k7491 in k7335 in k7332 in k7329 in k7326 in k7323 in k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7516(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_7502(t3,((C_word*)t0)[2],t2);}

/* k7338 in k7335 in k7332 in k7329 in k7326 in k7323 in k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7340(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7340,2,t0,t1);}
t2=(C_word)C_i_car(((C_word*)t0)[13]);
t3=(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_7482,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],a[10]=((C_word*)t0)[10],a[11]=((C_word*)t0)[11],a[12]=((C_word*)t0)[12],a[13]=t2,tmp=(C_word)a,a+=14,tmp);
t4=(C_word)C_i_cdr(((C_word*)t0)[13]);
t5=(C_word)C_a_i_list(&a,1,C_fix(-1));
C_trace("ChickenBridge.scm: 512  ##sys#append");
t6=*((C_word*)lf[453]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t3,t4,t5);}

/* k7480 in k7338 in k7335 in k7332 in k7329 in k7326 in k7323 in k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7482(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7482,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[13],t1);
t3=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_7466,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],a[8]=((C_word*)t0)[10],a[9]=((C_word*)t0)[11],a[10]=((C_word*)t0)[12],a[11]=t2,tmp=(C_word)a,a+=12,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7470,a[2]=((C_word*)t0)[3],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_a_i_list(&a,1,((C_word*)t0)[10]);
C_trace("ChickenBridge.scm: 512  ##sys#append");
t6=*((C_word*)lf[453]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t4,((C_word*)((C_word*)t0)[2])[1],t5);}

/* k7468 in k7480 in k7338 in k7335 in k7332 in k7329 in k7326 in k7323 in k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7470(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 512  ##sys#append");
t2=*((C_word*)lf[453]+1);
((C_proc4)(void*)(*((C_word*)t2+1)))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k7464 in k7480 in k7338 in k7335 in k7332 in k7329 in k7326 in k7323 in k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7466(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_7466,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,lf[439],t1);
t3=(C_word)C_a_i_list(&a,3,lf[440],((C_word*)t0)[11],t2);
t4=C_mutate(((C_word *)((C_word*)t0)[10])+1,t3);
t5=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_7347,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],a[5]=((C_word*)t0)[10],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],tmp=(C_word)a,a+=8,tmp);
if(C_truep(((C_word*)((C_word*)t0)[4])[1])){
t6=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
t7=(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]);
t8=(C_word)C_a_i_list(&a,2,lf[446],lf[447]);
t9=(C_word)C_a_i_list(&a,2,lf[446],lf[448]);
t10=(C_word)C_a_i_list(&a,3,lf[449],t8,t9);
t11=(C_word)C_a_i_list(&a,2,t10,((C_word*)t0)[2]);
t12=(C_word)C_a_i_list(&a,4,lf[286],lf[450],t11,((C_word*)t0)[9]);
t13=(C_word)C_a_i_list(&a,2,lf[260],t12);
t14=(C_word)C_a_i_list(&a,2,((C_word*)t0)[3],C_fix(-2));
t15=(C_word)C_a_i_list(&a,4,lf[441],t7,t13,t14);
t16=(C_word)C_a_i_list(&a,3,lf[441],C_SCHEME_END_OF_LIST,((C_word*)((C_word*)t0)[10])[1]);
t17=(C_word)C_a_i_list(&a,3,lf[451],t15,t16);
t18=(C_word)C_a_i_list(&a,3,lf[441],t6,t17);
t19=(C_word)C_a_i_list(&a,2,lf[452],t18);
t20=C_mutate(((C_word *)((C_word*)t0)[10])+1,t19);
t21=t5;
f_7347(t21,t20);}
else{
t6=t5;
f_7347(t6,C_SCHEME_UNDEFINED);}}

/* k7345 in k7464 in k7480 in k7338 in k7335 in k7332 in k7329 in k7326 in k7323 in k7320 in k7317 in a7764 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_7347(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_7347,NULL,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,((C_word*)t0)[7]);
t3=(C_word)C_a_i_list(&a,2,((C_word*)t0)[6],C_fix(0));
t4=(C_word)C_a_i_list(&a,3,lf[441],C_SCHEME_END_OF_LIST,((C_word*)t0)[7]);
t5=(C_word)C_a_i_list(&a,2,lf[442],t4);
t6=(C_word)C_a_i_list(&a,1,lf[443]);
t7=(C_word)C_a_i_list(&a,3,lf[235],((C_word*)t0)[6],lf[443]);
t8=(C_word)C_a_i_list(&a,3,lf[441],t6,t7);
t9=(C_word)C_a_i_list(&a,2,lf[444],t8);
t10=(C_word)C_a_i_list(&a,3,t3,t5,t9);
t11=(C_word)C_a_i_list(&a,3,lf[445],t10,((C_word*)((C_word*)t0)[5])[1]);
t12=(C_word)C_a_i_list(&a,3,lf[441],t2,t11);
t13=(C_word)C_a_i_list(&a,3,lf[441],((C_word*)((C_word*)t0)[4])[1],t12);
t14=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t14+1)))(2,t14,(C_word)C_a_i_cons(&a,2,t13,((C_word*)((C_word*)t0)[2])[1]));}

/* k7302 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7304(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7304,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7763,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 609  return-to-host");
t3=C_retrieve(lf[438]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k7761 in k7302 in k7299 in k7296 in k7293 in k7290 in k7287 in k7284 in k7281 in k7278 in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7763(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_UNDEFINED);}

/* mp:inhook in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7268(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_7268,5,t0,t1,t2,t3,t4);}
t5=(C_word)C_i_foreign_fixnum_argumentp(t3);
t6=(C_word)C_i_foreign_fixnum_argumentp(t4);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub1623(C_SCHEME_UNDEFINED,t2,t5,t6));}

/* mp:micro in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7262(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_7262,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 487  error");
t3=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[434]);}

/* mp:alloff in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7256(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7256,2,t0,t1);}
C_trace("ChickenBridge.scm: 485  error");
t2=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,t1,lf[431]);}

/* mp:ctrl in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7250(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_7250,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 483  error");
t6=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[428]);}

/* mp:prog in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7244(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_7244,5,t0,t1,t2,t3,t4);}
C_trace("ChickenBridge.scm: 481  error");
t5=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t5))(3,t5,t1,lf[425]);}

/* mp:off in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7238(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_7238,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 479  error");
t6=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[422]);}

/* mp:on in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7232(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_7232,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 477  error");
t6=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[419]);}

/* mp:note in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7226(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
C_word tmp;
C_word t7;
C_word t8;
C_word ab[8],*a=ab;
if(c!=7) C_bad_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr7,(void*)f_7226,7,t0,t1,t2,t3,t4,t5,t6);}
t7=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_6490,a[2]=t1,a[3]=t6,a[4]=t5,a[5]=t4,a[6]=t3,a[7]=t2,tmp=(C_word)a,a+=8,tmp);
C_trace("##sys#gc");
t8=C_retrieve(lf[352]);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,C_SCHEME_FALSE);}

/* k6488 in mp:note in k7222 in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6490(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_6490,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[7]);
t4=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[6]);
t5=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[5]);
t6=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[4]);
t7=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[3]);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub1429,a[2]=lf[416],tmp=(C_word)a,a+=3,tmp);
((C_proc8)C_retrieve_proc(t8))(8,t8,((C_word*)t0)[2],t2,t3,t4,t5,t6,t7);}

/* expand-send in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6953(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word ab[17],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_6953,5,t0,t1,t2,t3,t4);}
t5=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t6=t4;
t7=(C_truep(t6)?t6:(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7213,a[2]=lf[397],tmp=(C_word)a,a+=3,tmp));
t8=t4;
t9=(C_truep(t8)?(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7202,a[2]=lf[400],tmp=(C_word)a,a+=3,tmp):(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7211,a[2]=lf[401],tmp=(C_word)a,a+=3,tmp));
t10=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_6963,a[2]=t9,a[3]=t7,a[4]=t1,a[5]=t5,tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_symbolp(t2))){
C_trace("ChickenBridge.scm: 397  symbol->string");
t11=*((C_word*)lf[413]+1);
((C_proc3)C_retrieve_proc(t11))(3,t11,t10,t2);}
else{
t11=t10;
f_6963(2,t11,t2);}}

/* k6961 in expand-send in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6963(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6963,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_6966,a[2]=((C_word*)t0)[2],a[3]=t1,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],tmp=(C_word)a,a+=7,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7194,a[2]=lf[412],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 398  hash-table-ref");
t4=*((C_word*)lf[127]+1);
((C_proc5)C_retrieve_proc(t4))(5,t4,t2,C_retrieve2(lf[395],"*messages*"),t1,t3);}

/* a7193 in k6961 in expand-send in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7194(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7194,2,t0,t1);}
t2=t1;
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}

/* k6964 in k6961 in expand-send in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6966(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6966,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_6969,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=t1,a[7]=((C_word*)t0)[6],tmp=(C_word)a,a+=8,tmp);
t3=t1;
if(C_truep(t3)){
t4=t2;
f_6969(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 399  ferror");
t4=((C_word*)t0)[4];
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,lf[411],((C_word*)t0)[3]);}}

/* k6967 in k6964 in k6961 in expand-send in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6969(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[14],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6969,2,t0,t1);}
t2=((C_word*)((C_word*)t0)[7])[1];
t3=(C_word)C_i_car(((C_word*)t0)[6]);
t4=(C_word)C_i_cdr(((C_word*)t0)[6]);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(C_word)C_i_length(t4);
t8=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_6981,a[2]=t2,a[3]=t7,a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],a[7]=t6,a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[5],a[10]=t4,a[11]=t3,tmp=(C_word)a,a+=12,tmp);
C_trace("ChickenBridge.scm: 406  append");
t9=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t9))(4,t9,t8,t4,C_SCHEME_END_OF_LIST);}

/* k6979 in k6967 in k6964 in k6961 in expand-send in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6981(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6981,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_6984,a[2]=((C_word*)t0)[9],a[3]=((C_word*)t0)[10],a[4]=t1,a[5]=((C_word*)t0)[11],tmp=(C_word)a,a+=6,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_7029,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[10],a[9]=((C_word*)t0)[7],a[10]=t4,a[11]=((C_word*)t0)[8],a[12]=lf[410],tmp=(C_word)a,a+=13,tmp));
t6=((C_word*)t4)[1];
f_7029(t6,t2,C_SCHEME_FALSE,C_SCHEME_FALSE,C_fix(0));}

/* do1572 in k6979 in k6967 in k6964 in k6961 in expand-send in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_7029(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word t12;
C_word ab[28],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_7029,NULL,5,t0,t1,t2,t3,t4);}
t5=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[11])[1]))){
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,C_SCHEME_FALSE);}
else{
t8=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_7039,a[2]=t7,a[3]=t6,a[4]=t5,a[5]=t1,a[6]=((C_word*)t0)[10],tmp=(C_word)a,a+=7,tmp);
t9=(*a=C_CLOSURE_TYPE|14,a[1]=(C_word)f_7045,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t7,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=t6,a[10]=((C_word*)t0)[8],a[11]=t5,a[12]=((C_word*)t0)[11],a[13]=t8,a[14]=((C_word*)t0)[9],tmp=(C_word)a,a+=15,tmp);
t10=((C_word*)((C_word*)t0)[9])[1];
if(C_truep(t10)){
t11=t9;
f_7045(2,t11,C_SCHEME_FALSE);}
else{
t11=(C_word)C_i_car(((C_word*)((C_word*)t0)[11])[1]);
C_trace("ChickenBridge.scm: 417  keyword?");
t12=C_retrieve(lf[408]);
((C_proc3)C_retrieve_proc(t12))(3,t12,t9,t11);}}}

/* k7043 in do1572 in k6979 in k6967 in k6964 in k6961 in expand-send in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7045(C_word c,C_word t0,C_word t1){
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
C_word ab[26],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7045,2,t0,t1);}
if(C_truep(t1)){
t2=C_set_block_item(((C_word*)t0)[14],0,C_SCHEME_TRUE);
t3=((C_word*)t0)[13];
f_7039(t3,t2);}
else{
t2=((C_word*)((C_word*)t0)[14])[1];
if(C_truep(t2)){
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[12])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[11])+1,t3);
t5=(C_word)C_i_assoc(((C_word*)((C_word*)t0)[11])[1],((C_word*)t0)[10]);
t6=C_mutate(((C_word *)((C_word*)t0)[9])+1,t5);
t7=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[12])[1]);
t8=C_mutate(((C_word *)((C_word*)t0)[12])+1,t7);
t9=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_7099,a[2]=((C_word*)t0)[11],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],a[6]=((C_word*)t0)[13],a[7]=((C_word*)t0)[12],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],tmp=(C_word)a,a+=10,tmp);
t10=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_7172,a[2]=((C_word*)t0)[10],a[3]=((C_word*)t0)[9],a[4]=((C_word*)t0)[11],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t9,a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[12],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 437  keyword?");
t11=C_retrieve(lf[408]);
((C_proc3)C_retrieve_proc(t11))(3,t11,t10,((C_word*)((C_word*)t0)[11])[1]);}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_7055,a[2]=((C_word*)t0)[13],a[3]=((C_word*)t0)[12],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[8],tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_nequalp(((C_word*)((C_word*)t0)[4])[1],((C_word*)t0)[3]))){
t4=(C_word)C_i_length(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 427  ferror");
t5=((C_word*)t0)[7];
((C_proc6)C_retrieve_proc(t5))(6,t5,t3,lf[409],((C_word*)t0)[6],((C_word*)t0)[3],t4);}
else{
t4=t3;
f_7055(2,t4,C_SCHEME_UNDEFINED);}}}}

/* k7053 in k7043 in do1572 in k6979 in k6967 in k6964 in k6961 in expand-send in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7055(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_7055,2,t0,t1);}
t2=(C_word)C_i_list_tail(((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]);
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
t4=(C_word)C_i_set_car(t2,t3);
t5=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[3])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t5);
t7=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[4])[1],C_fix(1));
t8=C_mutate(((C_word *)((C_word*)t0)[4])+1,t7);
t9=((C_word*)t0)[2];
f_7039(t9,t8);}

/* k7170 in k7043 in do1572 in k6979 in k6967 in k6964 in k6961 in expand-send in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7172(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[15],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7172,2,t0,t1);}
if(C_truep(t1)){
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[9])[1]))){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7145,a[2]=((C_word*)t0)[6],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[8],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 442  keyname");
t3=((C_word*)t0)[5];
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)((C_word*)t0)[4])[1]);}
else{
t2=((C_word*)((C_word*)t0)[3])[1];
if(C_truep(t2)){
t3=((C_word*)t0)[7];
f_7099(2,t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_7158,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],a[5]=((C_word*)t0)[8],tmp=(C_word)a,a+=6,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7160,a[2]=((C_word*)t0)[5],a[3]=lf[406],tmp=(C_word)a,a+=4,tmp);
C_trace("map");
t5=*((C_word*)lf[276]+1);
((C_proc4)(void*)(*((C_word*)t5+1)))(4,t5,t3,t4,((C_word*)t0)[2]);}}}
else{
C_trace("ChickenBridge.scm: 438  ferror");
t2=((C_word*)t0)[8];
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[7],lf[407],((C_word*)t0)[6],((C_word*)((C_word*)t0)[4])[1]);}}

/* a7159 in k7170 in k7043 in do1572 in k6979 in k6967 in k6964 in k6961 in expand-send in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7160(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_7160,3,t0,t1,t2);}
t3=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 446  keyname");
t4=((C_word*)t0)[2];
((C_proc3)C_retrieve_proc(t4))(3,t4,t1,t3);}

/* k7156 in k7170 in k7043 in do1572 in k6979 in k6967 in k6964 in k6961 in expand-send in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7158(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 444  ferror");
t2=((C_word*)t0)[5];
((C_proc6)C_retrieve_proc(t2))(6,t2,((C_word*)t0)[4],lf[405],((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k7143 in k7170 in k7043 in do1572 in k6979 in k6967 in k6964 in k6961 in expand-send in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7145(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 441  ferror");
t2=((C_word*)t0)[4];
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[3],lf[404],((C_word*)t0)[2],t1);}

/* k7097 in k7043 in do1572 in k6979 in k6967 in k6964 in k6961 in expand-send in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7099(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7099,2,t0,t1);}
t2=(C_word)C_i_member(((C_word*)((C_word*)t0)[9])[1],((C_word*)t0)[8]);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7105,a[2]=((C_word*)t0)[6],a[3]=t2,a[4]=((C_word*)t0)[7],tmp=(C_word)a,a+=5,tmp);
if(C_truep(t2)){
t4=t3;
f_7105(2,t4,C_SCHEME_UNDEFINED);}
else{
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7126,a[2]=((C_word*)t0)[4],a[3]=t3,a[4]=((C_word*)t0)[5],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 452  keyname");
t5=((C_word*)t0)[3];
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,((C_word*)((C_word*)t0)[2])[1]);}}

/* k7124 in k7097 in k7043 in do1572 in k6979 in k6967 in k6964 in k6961 in expand-send in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7126(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 451  ferror");
t2=((C_word*)t0)[4];
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[3],lf[403],((C_word*)t0)[2],t1);}

/* k7103 in k7097 in k7043 in do1572 in k6979 in k6967 in k6964 in k6961 in expand-send in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7105(C_word c,C_word t0,C_word t1){
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
f_7039(t6,t5);}

/* k7037 in do1572 in k6979 in k6967 in k6964 in k6961 in expand-send in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_7039(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[6])[1];
f_7029(t2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k6982 in k6979 in k6967 in k6964 in k6961 in expand-send in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6984(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6984,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_6989,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=lf[402],tmp=(C_word)a,a+=7,tmp));
t5=((C_word*)t3)[1];
f_6989(t5,((C_word*)t0)[2],((C_word*)t0)[4]);}

/* do1590 in k6982 in k6979 in k6967 in k6964 in k6961 in expand-send in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_6989(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6989,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[5],((C_word*)t0)[4]));}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7002,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_member(t4,((C_word*)t0)[2]))){
t5=(C_word)C_i_car(t2);
t6=(C_word)C_i_cadr(t5);
t7=t3;
f_7002(t7,(C_word)C_i_set_car(t2,t6));}
else{
t5=t3;
f_7002(t5,C_SCHEME_UNDEFINED);}}}

/* k7000 in do1590 in k6982 in k6979 in k6967 in k6964 in k6961 in expand-send in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_7002(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_6989(t3,((C_word*)t0)[2],t2);}

/* f_7211 in expand-send in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7211(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_7211,3,t0,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,t2);}

/* f_7202 in expand-send in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7202(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_7202,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7210,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 395  keyword->string");
t4=C_retrieve(lf[399]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,t2);}

/* k7208 */
static void C_ccall f_7210(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 395  sprintf");
t2=C_retrieve(lf[286]);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[2],lf[398],t1);}

/* f_7213 in expand-send in k6949 in k6946 in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_7213(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+3)){
C_save_and_reclaim((void*)tr3r,(void*)f_7213r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_7213r(t0,t1,t2,t3);}}

static void C_ccall f_7213r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word *a=C_alloc(3);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7221,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_apply(5,0,t4,C_retrieve(lf[286]),t2,t3);}

/* k7219 */
static void C_ccall f_7221(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 391  error");
t2=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* hush in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6937(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6937,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6941,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6600,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[352]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k6598 in hush in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6600(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6600,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub1482,a[2]=lf[393],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k6939 in hush in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6941(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 363  values");
C_values(2,0,((C_word*)t0)[2]);}

/* stop in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6879(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+9)){
C_save_and_reclaim((void*)tr2r,(void*)f_6879r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_6879r(t0,t1,t2);}}

static void C_ccall f_6879r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a=C_alloc(9);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6883,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 353  scheduler-stop");
f_6583(t3,C_fix(-1));}
else{
t4=C_SCHEME_UNDEFINED;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_set_block_item(t5,0,(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6897,a[2]=t5,a[3]=lf[390],tmp=(C_word)a,a+=4,tmp));
t7=((C_word*)t5)[1];
f_6897(t7,t3,t2);}}

/* do1539 in stop in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_6897(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6897,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6907,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_fixnump(t4))){
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 357  scheduler-stop");
f_6583(t3,t5);}
else{
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 358  error");
t6=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t3,lf[389],t5);}}}

/* k6905 in do1539 in stop in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6907(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_6897(t3,((C_word*)t0)[2],t2);}

/* k6881 in stop in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6883(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 359  values");
C_values(2,0,((C_word*)t0)[2]);}

/* cont in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6870(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6870,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6874,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6578,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[352]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k6576 in cont in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6578(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6578,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub1472,a[2]=lf[386],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k6872 in cont in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6874(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 349  values");
C_values(2,0,((C_word*)t0)[2]);}

/* paused? in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6864(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6864,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6560,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t3=C_retrieve(lf[352]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,C_SCHEME_FALSE);}

/* k6558 in paused? in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6560(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6560,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub1464,a[2]=lf[383],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* pause in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6855(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6855,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6859,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6569,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[352]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k6567 in pause in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6569(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6569,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub1468,a[2]=lf[380],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k6857 in pause in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6859(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 342  values");
C_values(2,0,((C_word*)t0)[2]);}

/* time-format in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6792(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+11)){
C_save_and_reclaim((void*)tr2rv,(void*)f_6792r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_6792r(t0,t1,t2);}}

static void C_ccall f_6792r(C_word t0,C_word t1,C_word t2){
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
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6805,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6525,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t5=C_retrieve(lf[352]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,C_SCHEME_FALSE);}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
t4=(C_word)C_i_eqvp(t3,lf[374]);
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6817,a[2]=t2,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
if(C_truep(t4)){
t6=t5;
f_6817(t6,t4);}
else{
t6=(C_word)C_eqp(t3,C_fix(1));
t7=t5;
f_6817(t7,(C_truep(t6)?t6:(C_word)C_eqp(t3,lf[377])));}}}

/* k6815 in time-format in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_6817(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a;
if(C_truep(t1)){
t2=C_mutate((C_word*)lf[370]+1,C_retrieve(lf[348]));
C_trace("ChickenBridge.scm: 331  scheduler-set-time-milliseconds");
f_6530(((C_word*)t0)[4],C_SCHEME_FALSE);}
else{
t2=(C_word)C_eqp(((C_word*)t0)[3],C_fix(1000));
t3=(C_truep(t2)?t2:(C_word)C_eqp(((C_word*)t0)[3],lf[375]));
if(C_truep(t3)){
t4=C_mutate((C_word*)lf[370]+1,C_retrieve(lf[346]));
C_trace("ChickenBridge.scm: 335  scheduler-set-time-milliseconds");
f_6530(((C_word*)t0)[4],C_SCHEME_TRUE);}
else{
t4=(C_word)C_i_vector_ref(((C_word*)t0)[2],C_fix(0));
C_trace("ChickenBridge.scm: 338  error");
t5=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,((C_word*)t0)[4],lf[376],t4);}}}

/* k6523 in time-format in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6525(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6525,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub1444,a[2]=lf[373],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k6803 in time-format in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6805(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_truep(t1)?C_fix(1000):lf[372]));}

/* sprout in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6624(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+12)){
C_save_and_reclaim((void*)tr3r,(void*)f_6624r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_6624r(t0,t1,t2,t3);}}

static void C_ccall f_6624r(C_word t0,C_word t1,C_word t2,C_word t3){
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
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6626,a[2]=t2,a[3]=lf[366],tmp=(C_word)a,a+=4,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6738,a[2]=t4,a[3]=lf[367],tmp=(C_word)a,a+=4,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6743,a[2]=t5,a[3]=lf[368],tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("def-start14991520");
t7=t6;
f_6743(t7,t1);}
else{
t7=(C_word)C_i_car(t3);
t8=(C_word)C_i_cdr(t3);
if(C_truep((C_word)C_i_nullp(t8))){
C_trace("def-id15001518");
t9=t5;
f_6738(t9,t1,t7);}
else{
t9=(C_word)C_i_car(t8);
t10=(C_word)C_i_cdr(t8);
if(C_truep((C_word)C_i_nullp(t10))){
C_trace("body14971502");
t11=t4;
f_6626(t11,t1,t7,t9);}
else{
C_trace("##sys#error");
t11=*((C_word*)lf[38]+1);
((C_proc4)(void*)(*((C_word*)t11+1)))(4,t11,t1,lf[0],t10);}}}}

/* def-start1499 in sprout in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_6743(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6743,NULL,2,t0,t1);}
C_trace("def-id15001518");
t2=((C_word*)t0)[2];
f_6738(t2,t1,C_fix(0));}

/* def-id1500 in sprout in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_6738(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6738,NULL,3,t0,t1,t2);}
C_trace("body14971502");
t3=((C_word*)t0)[2];
f_6626(t3,t1,t2,C_fix(-1));}

/* body1497 in sprout in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_6626(C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)trf_6626,NULL,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6628,a[2]=t4,a[3]=lf[363],tmp=(C_word)a,a+=4,tmp);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6656,a[2]=t5,a[3]=lf[364],tmp=(C_word)a,a+=4,tmp);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6686,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t0)[2]))){
t9=C_SCHEME_UNDEFINED;
t10=(*a=C_VECTOR_TYPE|1,a[1]=t9,tmp=(C_word)a,a+=2,tmp);
t11=C_set_block_item(t10,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_6697,a[2]=t6,a[3]=t7,a[4]=t10,a[5]=((C_word*)t0)[2],a[6]=lf[365],tmp=(C_word)a,a+=7,tmp));
t12=((C_word*)t10)[1];
f_6697(t12,t8,((C_word*)t0)[2]);}
else{
t9=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6729,a[2]=((C_word*)t0)[2],a[3]=t8,tmp=(C_word)a,a+=4,tmp);
t10=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6733,a[2]=t7,a[3]=((C_word*)t0)[2],a[4]=t9,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 315  nextstart");
t11=t6;
f_6628(t11,t10);}}

/* k6731 in body1497 in sprout in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6733(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6733,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6737,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 315  nextid");
t3=((C_word*)t0)[2];
f_6656(t3,t2);}

/* k6735 in k6731 in body1497 in sprout in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6737(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 315  scheduler-sprout");
f_6539(((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k6727 in body1497 in sprout in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6729(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
f_6686(2,t2,((C_word*)t0)[2]);}

/* do1511 in body1497 in sprout in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_6697(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6697,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,((C_word*)t0)[5]);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6707,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6722,a[2]=((C_word*)t0)[3],a[3]=t4,a[4]=t3,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 313  nextstart");
t6=((C_word*)t0)[2];
f_6628(t6,t5);}}

/* k6720 in do1511 in body1497 in sprout in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6722(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6722,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6726,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 313  nextid");
t3=((C_word*)t0)[2];
f_6656(t3,t2);}

/* k6724 in k6720 in do1511 in body1497 in sprout in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6726(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 313  scheduler-sprout");
f_6539(((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k6705 in do1511 in body1497 in sprout in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6707(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_6697(t3,((C_word*)t0)[2],t2);}

/* k6684 in body1497 in sprout in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6686(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 319  values");
C_values(2,0,((C_word*)t0)[2]);}

/* nextid in body1497 in sprout in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_6656(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_6656,NULL,2,t0,t1);}
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

/* nextstart in body1497 in sprout in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_6628(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_6628,NULL,2,t0,t1);}
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

/* load-sal-file in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6605(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6605,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6610,a[2]=lf[360],tmp=(C_word)a,a+=3,tmp);
((C_proc3)(void*)(*((C_word*)t3+1)))(3,t3,t1,t2);}

/* f_6610 in load-sal-file in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6610(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6610,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6615,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[341]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_6615(2,t4,C_SCHEME_FALSE);}}

/* k6613 */
static void C_ccall f_6615(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub1488(C_SCHEME_UNDEFINED,t1));}

/* scheduler-stop in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_6583(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6583,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6587,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[352]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k6585 in scheduler-stop in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6587(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6587,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_fixnum_argumentp(((C_word*)t0)[3]);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub1477,a[2]=lf[358],tmp=(C_word)a,a+=3,tmp);
((C_proc4)C_retrieve_proc(t4))(4,t4,((C_word*)t0)[2],t2,t3);}

/* scheduler-sprout in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_6539(C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6539,NULL,4,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_6543,a[2]=t2,a[3]=t1,a[4]=t4,a[5]=t3,tmp=(C_word)a,a+=6,tmp);
C_trace("##sys#gc");
t6=C_retrieve(lf[352]);
((C_proc3)C_retrieve_proc(t6))(3,t6,t5,C_SCHEME_FALSE);}

/* k6541 in scheduler-sprout in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6543(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6543,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[5]);
t4=(C_word)C_i_foreign_fixnum_argumentp(((C_word*)t0)[4]);
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub1457,a[2]=lf[355],tmp=(C_word)a,a+=3,tmp);
((C_proc6)C_retrieve_proc(t5))(6,t5,((C_word*)t0)[3],t2,((C_word*)t0)[2],t3,t4);}

/* scheduler-set-time-milliseconds in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_6530(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6530,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6534,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[352]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k6532 in scheduler-set-time-milliseconds in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6534(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6534,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub1449,a[2]=lf[351],tmp=(C_word)a,a+=3,tmp);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[3],t2,((C_word*)t0)[2]);}

/* current-time-seconds in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6518(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6518,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub1441(t2));}

/* current-time-milliseconds in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6515(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6515,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub1438(t2));}

/* print-error in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6472(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6472,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6477,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[341]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_6477(2,t4,C_SCHEME_FALSE);}}

/* k6475 in print-error in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6477(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub1419(C_SCHEME_UNDEFINED,t1));}

/* print-message in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6458(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6458,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6463,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[341]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_6463(2,t4,C_SCHEME_FALSE);}}

/* k6461 in print-message in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6463(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub1413(C_SCHEME_UNDEFINED,t1));}

/* change-directory in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6429(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+3)){
C_save_and_reclaim((void*)tr2rv,(void*)f_6429r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_6429r(t0,t1,t2);}}

static void C_ccall f_6429r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word *a=C_alloc(3);
t3=(C_word)C_vemptyp(t2);
t4=(C_truep(t3)?lf[340]:(C_word)C_i_vector_ref(t2,C_fix(0)));
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6438,a[2]=lf[342],tmp=(C_word)a,a+=3,tmp);
((C_proc3)(void*)(*((C_word*)t5+1)))(3,t5,t1,t4);}

/* f_6438 in change-directory in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6438(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6438,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6443,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[341]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_6443(2,t4,C_SCHEME_FALSE);}}

/* k6441 */
static void C_ccall f_6443(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub1407(C_SCHEME_UNDEFINED,t1));}

/* current-directory in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6418(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[3],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6418,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6423,a[2]=lf[338],tmp=(C_word)a,a+=3,tmp);
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,t1);}

/* f_6423 in current-directory in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6423(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6423,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(3));
C_trace("##sys#peek-c-string");
t3=*((C_word*)lf[337]+1);
((C_proc4)(void*)(*((C_word*)t3+1)))(4,t3,t1,(C_word)stub1402(t2),C_fix(0));}

/* list* in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6378(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+4)){
C_save_and_reclaim((void*)tr2r,(void*)f_6378r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_6378r(t0,t1,t2);}}

static void C_ccall f_6378r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a=C_alloc(4);
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 207  error");
t3=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[334]);}
else{
t3=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t3))){
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_car(t2));}
else{
t4=(C_word)C_i_car(t2);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6408,a[2]=t4,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
t6=(C_word)C_i_cdr(t2);
C_apply(4,0,t5,C_retrieve(lf[333]),t6);}}}

/* k6406 in list* in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6408(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6408,2,t0,t1);}
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[2],t1));}

/* butlast in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6330(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[7],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6330,3,t0,t1,t2);}
t3=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t3))){
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,C_SCHEME_END_OF_LIST);}
else{
t4=(C_word)C_i_cddr(t2);
if(C_truep((C_word)C_i_nullp(t4))){
t5=(C_word)C_i_car(t2);
t6=t1;
((C_proc2)(void*)(*((C_word*)t6+1)))(2,t6,(C_word)C_a_i_list(&a,1,t5));}
else{
t5=(C_word)C_i_car(t2);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6364,a[2]=t5,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
t7=(C_word)C_i_cdr(t2);
C_trace("ChickenBridge.scm: 203  butlast");
t8=C_retrieve(lf[331]);
((C_proc3)C_retrieve_proc(t8))(3,t8,t6,t7);}}}

/* k6362 in butlast in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6364(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6364,2,t0,t1);}
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[2],t1));}

/* last in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6310(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6310,3,t0,t1,t2);}
t3=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t3))){
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,t2);}
else{
t4=(C_word)C_i_cdr(t2);
C_trace("ChickenBridge.scm: 197  last");
t5=C_retrieve(lf[329]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t1,t4);}}

/* tenth in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6290(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6290,3,t0,t1,t2);}
t3=(C_word)C_i_cddddr(t2);
t4=(C_word)C_i_cddddr(t3);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)C_i_cadr(t4));}

/* ninth in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6276(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6276,3,t0,t1,t2);}
t3=(C_word)C_i_cddddr(t2);
t4=(C_word)C_i_cddddr(t3);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)C_i_car(t4));}

/* eighth in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6266(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6266,3,t0,t1,t2);}
t3=(C_word)C_i_cddddr(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_cadddr(t3));}

/* seventh in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6256(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6256,3,t0,t1,t2);}
t3=(C_word)C_i_cddddr(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_caddr(t3));}

/* sixth in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6246(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6246,3,t0,t1,t2);}
t3=(C_word)C_i_cddddr(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_cadr(t3));}

/* fifth in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6236(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6236,3,t0,t1,t2);}
t3=(C_word)C_i_cddddr(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_car(t3));}

/* sal:output in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6214(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6214,2,t0,t1);}
C_trace("ChickenBridge.scm: 145  print-error");
t2=C_retrieve(lf[260]);
((C_proc3)C_retrieve_proc(t2))(3,t2,t1,lf[309]);}

/* sal:open in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6208(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6208,2,t0,t1);}
C_trace("ChickenBridge.scm: 145  print-error");
t2=C_retrieve(lf[260]);
((C_proc3)C_retrieve_proc(t2))(3,t2,t1,lf[306]);}

/* sal:load in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6161(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6161,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6165,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  file-exists?");
t4=C_retrieve(lf[303]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,t2);}

/* k6163 in sal:load in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6165(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[14],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6165,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6168,a[2]=((C_word*)t0)[3],tmp=(C_word)a,a+=3,tmp);
if(C_truep(t1)){
t3=(C_word)C_i_string_length(((C_word*)t0)[2]);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6190,a[2]=((C_word*)t0)[2],a[3]=t2,tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_greaterp(t3,C_fix(4)))){
t5=(C_word)C_a_i_minus(&a,2,t3,C_fix(4));
C_trace("substring=?");
t6=C_retrieve(lf[299]);
((C_proc7)(void*)(*((C_word*)t6+1)))(7,t6,t4,((C_word*)t0)[2],lf[300],t5,C_fix(0),C_SCHEME_FALSE);}
else{
t5=t4;
f_6190(2,t5,C_SCHEME_FALSE);}}
else{
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6181,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  string-append");
t4=*((C_word*)lf[261]+1);
((C_proc5)C_retrieve_proc(t4))(5,t4,t3,lf[301],((C_word*)t0)[2],lf[302]);}}

/* k6179 in k6163 in sal:load in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6181(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  print-error");
t2=C_retrieve(lf[260]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k6188 in k6163 in sal:load in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6190(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(C_truep(t1)){
C_trace("ChickenBridge.scm: 145  load-sal-file");
t2=C_retrieve(lf[297]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}
else{
C_trace("ChickenBridge.scm: 145  load");
t2=C_retrieve(lf[298]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}}

/* k6166 in k6163 in sal:load in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6168(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  values");
C_values(2,0,((C_word*)t0)[2]);}

/* sal:chdir in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6152(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6152,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6156,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  change-directory");
t4=C_retrieve(lf[294]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,t2);}

/* k6154 in sal:chdir in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6156(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  values");
C_values(2,0,((C_word*)t0)[2]);}

/* sal:print in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5973(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+16)){
C_save_and_reclaim((void*)tr2r,(void*)f_5973r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_5973r(t0,t1,t2);}}

static void C_ccall f_5973r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word *a=C_alloc(16);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5976,a[2]=t4,a[3]=lf[289],tmp=(C_word)a,a+=4,tmp));
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6121,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t7=C_SCHEME_UNDEFINED;
t8=(*a=C_VECTOR_TYPE|1,a[1]=t7,tmp=(C_word)a,a+=2,tmp);
t9=C_set_block_item(t8,0,(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6126,a[2]=t4,a[3]=t8,a[4]=lf[291],tmp=(C_word)a,a+=5,tmp));
t10=((C_word*)t8)[1];
f_6126(t10,t6,t2);}

/* do1256 in sal:print in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_6126(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6126,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 145  print-message");
t3=C_retrieve(lf[279]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[290]);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6139,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  printer");
t5=((C_word*)((C_word*)t0)[2])[1];
f_5976(t5,t3,t4);}}

/* k6137 in do1256 in sal:print in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6139(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_6126(t3,((C_word*)t0)[2],t2);}

/* k6119 in sal:print in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6121(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  values");
C_values(2,0,((C_word*)t0)[2]);}

/* printer in sal:print in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_5976(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5976,NULL,3,t0,t1,t2);}
t3=t2;
if(C_truep(t3)){
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 145  print-message");
t4=C_retrieve(lf[279]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t1,lf[280]);}
else{
if(C_truep((C_word)C_i_pairp(t2))){
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6004,a[2]=t2,a[3]=((C_word*)t0)[2],a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  print-message");
t5=C_retrieve(lf[279]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,lf[284]);}
else{
t4=(C_word)C_eqp(t2,C_SCHEME_TRUE);
if(C_truep(t4)){
C_trace("ChickenBridge.scm: 145  print-message");
t5=C_retrieve(lf[279]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t1,lf[285]);}
else{
if(C_truep((C_word)C_i_numberp(t2))){
if(C_truep((C_word)C_i_inexactp(t2))){
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6091,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6095,a[2]=t5,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  decimals");
t7=*((C_word*)lf[30]+1);
((C_proc4)C_retrieve_proc(t7))(4,t7,t6,t2,C_fix(3));}
else{
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6102,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  number->string");
C_number_to_string(3,0,t5,t2);}}
else{
if(C_truep((C_word)C_i_stringp(t2))){
C_trace("ChickenBridge.scm: 145  print-message");
t5=C_retrieve(lf[279]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t1,t2);}
else{
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6118,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  sprintf");
t6=C_retrieve(lf[286]);
((C_proc4)C_retrieve_proc(t6))(4,t6,t5,lf[287],t2);}}}}}}
else{
C_trace("ChickenBridge.scm: 145  print-message");
t4=C_retrieve(lf[279]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t1,lf[288]);}}

/* k6116 in printer in sal:print in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6118(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  print-message");
t2=C_retrieve(lf[279]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k6100 in printer in sal:print in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6102(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  print-message");
t2=C_retrieve(lf[279]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k6093 in printer in sal:print in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6095(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  number->string");
C_number_to_string(3,0,((C_word*)t0)[2],t1);}

/* k6089 in printer in sal:print in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6091(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  print-message");
t2=C_retrieve(lf[279]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k6002 in printer in sal:print in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6004(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6004,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6007,a[2]=((C_word*)t0)[4],tmp=(C_word)a,a+=3,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6012,a[2]=((C_word*)t0)[3],a[3]=t4,a[4]=lf[283],tmp=(C_word)a,a+=5,tmp));
t6=((C_word*)t4)[1];
f_6012(t6,t2,((C_word*)t0)[2]);}

/* do1248 in k6002 in printer in sal:print in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_6012(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6012,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6022,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  printer");
t5=((C_word*)((C_word*)t0)[2])[1];
f_5976(t5,t3,t4);}}

/* k6020 in do1248 in k6002 in printer in sal:print in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6022(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6022,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6025,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
t3=(C_word)C_i_cdr(((C_word*)t0)[4]);
if(C_truep((C_word)C_i_nullp(t3))){
t4=t2;
f_6025(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 145  print-message");
t4=C_retrieve(lf[279]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t2,lf[282]);}}

/* k6023 in k6020 in do1248 in k6002 in printer in sal:print in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6025(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_6012(t3,((C_word*)t0)[2],t2);}

/* k6005 in k6002 in printer in sal:print in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_6007(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  print-message");
t2=C_retrieve(lf[279]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],lf[281]);}

/* sal in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5802(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[7],*a=ab;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_5802,6,t0,t1,t2,t3,t4,t5);}
t6=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t7=C_mutate(&lf[256],t2);
t8=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5808,a[2]=t6,a[3]=t5,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("map");
t9=*((C_word*)lf[276]+1);
((C_proc4)(void*)(*((C_word*)t9+1)))(4,t9,t8,C_retrieve2(lf[113],"list->token"),t4);}

/* k5806 in sal in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5808(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5808,2,t0,t1);}
t2=C_mutate(&lf[257],t1);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5811,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
if(C_truep((C_word)C_i_nequalp(((C_word*)((C_word*)t0)[2])[1],C_fix(0)))){
t4=C_set_block_item(((C_word*)t0)[2],0,C_fix(36608));
t5=t3;
f_5811(t5,t4);}
else{
t4=t3;
f_5811(t4,C_SCHEME_FALSE);}}

/* k5809 in k5806 in sal in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_5811(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5811,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5815,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
t3=((C_word*)((C_word*)t0)[2])[1];
t4=C_retrieve2(lf[257],"*sal-tokens*");
t5=(C_word)C_a_i_list(&a,4,C_SCHEME_FALSE,C_fix(0),C_SCHEME_FALSE,C_SCHEME_FALSE);
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3614,a[2]=t4,a[3]=t3,a[4]=lf[274],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  call/cc");
t7=*((C_word*)lf[275]+1);
((C_proc3)C_retrieve_proc(t7))(3,t7,t2,t6);}

/* a3613 in k5809 in k5806 in sal in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3614(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_3614,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3620,a[2]=t2,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=lf[269],tmp=(C_word)a,a+=6,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3627,a[2]=t2,a[3]=lf[273],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  call-with-values");
C_call_with_values(4,0,t1,t3,t4);}

/* a3626 in a3613 in k5809 in k5806 in sal in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3627(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_3627,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3634,a[2]=((C_word*)t0)[2],a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
if(C_truep(t2)){
t6=(C_word)C_i_nullp(t4);
t7=t5;
f_3634(t7,(C_truep(t6)?t6:C_SCHEME_FALSE));}
else{
t6=t5;
f_3634(t6,C_SCHEME_FALSE);}}

/* k3632 in a3626 in a3613 in k5809 in k5806 in sal in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3634(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3634,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3641,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  add-emit-info");
f_3271(t2,lf[270],lf[271],C_SCHEME_END_OF_LIST);}
else{
C_trace("ChickenBridge.scm: 145  make-parse-error");
f_3091(((C_word*)t0)[4],lf[272],C_retrieve2(lf[196],"*maxtokpos*"));}}

/* k3639 in k3632 in a3626 in a3613 in k5809 in k5806 in sal in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3641(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  emit");
f_3299(((C_word*)t0)[4],((C_word*)t0)[3],t1,((C_word*)t0)[2]);}

/* a3619 in a3613 in k5809 in k5806 in sal in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3620(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3620,2,t0,t1);}
t2=lf[196]=C_fix(0);;
C_trace("ChickenBridge.scm: 145  parser");
f_3652(t1,((C_word*)t0)[4],((C_word*)t0)[3],C_SCHEME_FALSE,C_fix(0),C_SCHEME_FALSE,((C_word*)t0)[2]);}

/* k5813 in k5809 in k5806 in sal in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5815(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5815,2,t0,t1);}
t2=C_mutate(&lf[258],t1);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5818,a[2]=((C_word*)t0)[3],tmp=(C_word)a,a+=3,tmp);
t4=C_retrieve2(lf[258],"*sal-output*");
if(C_truep((C_word)C_i_structurep(t4,lf[142]))){
t5=C_retrieve2(lf[256],"*sal-string*");
t6=C_retrieve2(lf[258],"*sal-output*");
t7=(C_word)C_i_string_length(t5);
t8=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_5849,a[2]=t7,a[3]=t6,a[4]=t5,a[5]=t3,tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  parse-error-position");
f_3130(t8,t6);}
else{
if(C_truep(((C_word*)t0)[2])){
C_trace("ChickenBridge.scm: 145  pp");
t5=C_retrieve(lf[267]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,C_retrieve2(lf[258],"*sal-output*"));}
else{
C_trace("ChickenBridge.scm: 145  eval");
t5=C_retrieve(lf[268]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,C_retrieve2(lf[258],"*sal-output*"));}}}

/* k5847 in k5813 in k5809 in k5806 in sal in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5849(C_word c,C_word t0,C_word t1){
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
C_word ab[25],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5849,2,t0,t1);}
t2=(C_word)C_a_i_minus(&a,2,t1,C_fix(1));
t3=t2;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_fix(0);
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_5855,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=t1,a[7]=t6,a[8]=t4,tmp=(C_word)a,a+=9,tmp);
t8=C_SCHEME_UNDEFINED;
t9=(*a=C_VECTOR_TYPE|1,a[1]=t8,tmp=(C_word)a,a+=2,tmp);
t10=C_set_block_item(t9,0,(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_5942,a[2]=((C_word*)t0)[4],a[3]=t9,a[4]=t4,a[5]=lf[266],tmp=(C_word)a,a+=6,tmp));
t11=((C_word*)t9)[1];
f_5942(t11,t7,C_SCHEME_FALSE);}

/* do1222 in k5847 in k5813 in k5809 in k5806 in sal in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_5942(C_word t0,C_word t1,C_word t2){
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
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5942,NULL,3,t0,t1,t2);}
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=((C_word*)t3)[1];
t5=(C_truep(t4)?t4:(C_word)C_i_nequalp(((C_word*)((C_word*)t0)[4])[1],C_fix(-1)));
if(C_truep(t5)){
t6=t1;
((C_proc2)(void*)(*((C_word*)t6+1)))(2,t6,C_SCHEME_FALSE);}
else{
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5952,a[2]=t3,a[3]=t1,a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
t7=(C_word)C_i_string_ref(((C_word*)t0)[2],((C_word*)((C_word*)t0)[4])[1]);
t8=(C_word)C_eqp(t7,C_make_character(10));
if(C_truep(t8)){
t9=C_set_block_item(t3,0,C_SCHEME_TRUE);
t10=t6;
f_5952(t10,t9);}
else{
t9=(C_word)C_a_i_minus(&a,2,((C_word*)((C_word*)t0)[4])[1],C_fix(1));
t10=C_mutate(((C_word *)((C_word*)t0)[4])+1,t9);
t11=t6;
f_5952(t11,t10);}}}

/* k5950 in do1222 in k5847 in k5813 in k5809 in k5806 in sal in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_5952(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[4])[1];
f_5942(t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1]);}

/* k5853 in k5847 in k5813 in k5809 in k5806 in sal in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5855(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5855,2,t0,t1);}
t2=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[8])[1],C_fix(1));
t3=C_mutate(((C_word *)((C_word*)t0)[8])+1,t2);
t4=C_mutate(((C_word *)((C_word*)t0)[7])+1,((C_word*)t0)[6]);
t5=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5863,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[8],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[5],tmp=(C_word)a,a+=8,tmp);
t6=C_SCHEME_UNDEFINED;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=C_set_block_item(t7,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5912,a[2]=((C_word*)t0)[4],a[3]=t7,a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[7],a[6]=lf[265],tmp=(C_word)a,a+=7,tmp));
t9=((C_word*)t7)[1];
f_5912(t9,t5,C_SCHEME_FALSE);}

/* do1229 in k5853 in k5847 in k5813 in k5809 in k5806 in sal in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_5912(C_word t0,C_word t1,C_word t2){
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
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5912,NULL,3,t0,t1,t2);}
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=((C_word*)t3)[1];
t5=(C_truep(t4)?t4:(C_word)C_i_nequalp(((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[4]));
if(C_truep(t5)){
t6=t1;
((C_proc2)(void*)(*((C_word*)t6+1)))(2,t6,C_SCHEME_FALSE);}
else{
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5922,a[2]=t3,a[3]=t1,a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
t7=(C_word)C_i_string_ref(((C_word*)t0)[2],((C_word*)((C_word*)t0)[5])[1]);
t8=(C_word)C_eqp(t7,C_make_character(10));
if(C_truep(t8)){
t9=C_set_block_item(t3,0,C_SCHEME_TRUE);
t10=t6;
f_5922(t10,t9);}
else{
t9=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[5])[1],C_fix(1));
t10=C_mutate(((C_word *)((C_word*)t0)[5])+1,t9);
t11=t6;
f_5922(t11,t10);}}}

/* k5920 in do1229 in k5853 in k5847 in k5813 in k5809 in k5806 in sal in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_5922(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[4])[1];
f_5912(t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1]);}

/* k5861 in k5853 in k5847 in k5813 in k5809 in k5806 in sal in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5863(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[13],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5863,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5866,a[2]=((C_word*)t0)[7],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5873,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5877,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=t3,a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  parse-error-string");
f_3112(t4,((C_word*)t0)[2]);}

/* k5875 in k5861 in k5853 in k5847 in k5813 in k5809 in k5806 in sal in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5877(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5877,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5881,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 145  make-string");
t3=*((C_word*)lf[263]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t2,C_fix(1),C_make_character(10));}

/* k5879 in k5875 in k5861 in k5853 in k5847 in k5813 in k5809 in k5806 in sal in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5881(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5881,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5885,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  substring");
t3=*((C_word*)lf[264]+1);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k5883 in k5879 in k5875 in k5861 in k5853 in k5847 in k5813 in k5809 in k5806 in sal in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5885(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5885,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5889,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 145  make-string");
t3=*((C_word*)lf[263]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t2,C_fix(1),C_make_character(10));}

/* k5887 in k5883 in k5879 in k5875 in k5861 in k5853 in k5847 in k5813 in k5809 in k5806 in sal in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5889(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[16],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5889,2,t0,t1);}
t2=(C_word)C_a_i_minus(&a,2,((C_word*)t0)[7],((C_word*)((C_word*)t0)[6])[1]);
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5896,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=t2,tmp=(C_word)a,a+=8,tmp);
t4=(C_word)C_a_i_plus(&a,2,t2,C_fix(2));
C_trace("ChickenBridge.scm: 145  make-string");
t5=*((C_word*)lf[263]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,t4,C_make_character(32));}

/* k5894 in k5887 in k5883 in k5879 in k5875 in k5861 in k5853 in k5847 in k5813 in k5809 in k5806 in sal in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5896(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5896,2,t0,t1);}
t2=(C_word)C_i_string_set(t1,((C_word*)t0)[7],C_make_character(94));
t3=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[7],C_fix(1));
t4=(C_word)C_i_string_set(t1,t3,C_make_character(10));
C_trace("ChickenBridge.scm: 145  string-append");
t5=*((C_word*)lf[261]+1);
((C_proc8)C_retrieve_proc(t5))(8,t5,((C_word*)t0)[6],lf[262],((C_word*)t0)[5],((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k5871 in k5861 in k5853 in k5847 in k5813 in k5809 in k5806 in sal in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5873(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  print-error");
t2=C_retrieve(lf[260]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k5864 in k5861 in k5853 in k5847 in k5813 in k5809 in k5806 in sal in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5866(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  values");
C_values(2,0,((C_word*)t0)[2]);}

/* k5816 in k5813 in k5809 in k5806 in sal in k5794 in k5791 in k5788 in k5785 in k5782 in k5263 in k5260 in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5818(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  values");
C_values(2,0,((C_word*)t0)[2]);}

/* sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4741(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_word ab[51],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_4741,4,t0,t1,t2,t3);}
t4=C_SCHEME_END_OF_LIST;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_SCHEME_FALSE;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=C_SCHEME_FALSE;
t9=(*a=C_VECTOR_TYPE|1,a[1]=t8,tmp=(C_word)a,a+=2,tmp);
t10=C_SCHEME_FALSE;
t11=(*a=C_VECTOR_TYPE|1,a[1]=t10,tmp=(C_word)a,a+=2,tmp);
t12=C_SCHEME_FALSE;
t13=(*a=C_VECTOR_TYPE|1,a[1]=t12,tmp=(C_word)a,a+=2,tmp);
t14=C_SCHEME_FALSE;
t15=(*a=C_VECTOR_TYPE|1,a[1]=t14,tmp=(C_word)a,a+=2,tmp);
t16=C_SCHEME_FALSE;
t17=(*a=C_VECTOR_TYPE|1,a[1]=t16,tmp=(C_word)a,a+=2,tmp);
t18=C_SCHEME_FALSE;
t19=(*a=C_VECTOR_TYPE|1,a[1]=t18,tmp=(C_word)a,a+=2,tmp);
t20=C_SCHEME_FALSE;
t21=(*a=C_VECTOR_TYPE|1,a[1]=t20,tmp=(C_word)a,a+=2,tmp);
t22=C_SCHEME_FALSE;
t23=(*a=C_VECTOR_TYPE|1,a[1]=t22,tmp=(C_word)a,a+=2,tmp);
t24=C_SCHEME_FALSE;
t25=(*a=C_VECTOR_TYPE|1,a[1]=t24,tmp=(C_word)a,a+=2,tmp);
t26=C_SCHEME_FALSE;
t27=(*a=C_VECTOR_TYPE|1,a[1]=t26,tmp=(C_word)a,a+=2,tmp);
t28=C_SCHEME_FALSE;
t29=(*a=C_VECTOR_TYPE|1,a[1]=t28,tmp=(C_word)a,a+=2,tmp);
t30=C_SCHEME_FALSE;
t31=(*a=C_VECTOR_TYPE|1,a[1]=t30,tmp=(C_word)a,a+=2,tmp);
t32=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_4748,a[2]=t5,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
t33=(*a=C_CLOSURE_TYPE|18,a[1]=(C_word)f_4754,a[2]=t27,a[3]=t25,a[4]=t29,a[5]=t31,a[6]=t23,a[7]=t19,a[8]=t17,a[9]=t21,a[10]=t15,a[11]=t7,a[12]=t3,a[13]=t2,a[14]=t32,a[15]=t5,a[16]=t13,a[17]=t11,a[18]=t9,tmp=(C_word)a,a+=19,tmp);
t34=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3227(t33,t34,C_fix(23296));}

/* k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4754(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[25],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4754,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_4758,a[2]=((C_word*)t0)[14],a[3]=((C_word*)t0)[15],a[4]=((C_word*)t0)[16],a[5]=((C_word*)t0)[17],a[6]=((C_word*)t0)[18],tmp=(C_word)a,a+=7,tmp);
t3=(C_word)C_i_cadr(((C_word*)t0)[13]);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t2,t3,C_SCHEME_END_OF_LIST,((C_word*)t0)[12]);}
else{
t2=(*a=C_CLOSURE_TYPE|17,a[1]=(C_word)f_4804,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[16],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[13],a[10]=((C_word*)t0)[12],a[11]=((C_word*)t0)[8],a[12]=((C_word*)t0)[9],a[13]=((C_word*)t0)[14],a[14]=((C_word*)t0)[15],a[15]=((C_word*)t0)[10],a[16]=((C_word*)t0)[18],a[17]=((C_word*)t0)[11],tmp=(C_word)a,a+=18,tmp);
t3=(C_word)C_i_caddr(((C_word*)t0)[13]);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3227(t2,t3,C_fix(10756));}}

/* k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4804(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[26],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4804,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_4808,a[2]=((C_word*)t0)[9],a[3]=((C_word*)t0)[10],a[4]=((C_word*)t0)[11],a[5]=((C_word*)t0)[12],a[6]=((C_word*)t0)[13],a[7]=((C_word*)t0)[14],a[8]=((C_word*)t0)[15],a[9]=((C_word*)t0)[16],a[10]=((C_word*)t0)[17],tmp=(C_word)a,a+=11,tmp);
t3=(C_word)C_i_cadr(((C_word*)t0)[9]);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t2,t3,C_SCHEME_END_OF_LIST,((C_word*)t0)[10]);}
else{
t2=(*a=C_CLOSURE_TYPE|14,a[1]=(C_word)f_4901,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[10],a[9]=((C_word*)t0)[9],a[10]=((C_word*)t0)[13],a[11]=((C_word*)t0)[14],a[12]=((C_word*)t0)[8],a[13]=((C_word*)t0)[16],a[14]=((C_word*)t0)[17],tmp=(C_word)a,a+=15,tmp);
t3=(C_word)C_i_caddr(((C_word*)t0)[9]);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3227(t2,t3,C_fix(22784));}}

/* k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4901(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4901,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_4905,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[9],a[4]=((C_word*)t0)[10],a[5]=((C_word*)t0)[11],a[6]=((C_word*)t0)[12],a[7]=((C_word*)t0)[13],a[8]=((C_word*)t0)[14],tmp=(C_word)a,a+=9,tmp);
t3=(C_word)C_i_cadr(((C_word*)t0)[9]);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t2,t3,C_SCHEME_END_OF_LIST,((C_word*)t0)[8]);}
else{
t2=(C_word)C_i_length(((C_word*)t0)[9]);
t3=C_mutate(((C_word *)((C_word*)t0)[7])+1,t2);
t4=(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_4969,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[10],a[8]=((C_word*)t0)[11],a[9]=((C_word*)t0)[6],a[10]=((C_word*)t0)[9],a[11]=((C_word*)t0)[7],a[12]=((C_word*)t0)[14],tmp=(C_word)a,a+=13,tmp);
t5=(C_word)C_i_cadr(((C_word*)t0)[9]);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t4,t5,C_SCHEME_END_OF_LIST,((C_word*)t0)[8]);}}

/* k4967 in k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4969(C_word c,C_word t0,C_word t1){
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
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4969,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[12])+1,t1);
t3=(C_word)C_a_i_minus(&a,2,((C_word*)((C_word*)t0)[11])[1],C_fix(1));
t4=(C_word)C_i_list_ref(((C_word*)t0)[10],t3);
t5=C_mutate(((C_word *)((C_word*)t0)[9])+1,t4);
t6=(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_4976,a[2]=((C_word*)t0)[10],a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[11],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[5],a[8]=((C_word*)t0)[9],a[9]=((C_word*)t0)[6],a[10]=((C_word*)t0)[12],a[11]=((C_word*)t0)[7],a[12]=((C_word*)t0)[8],tmp=(C_word)a,a+=13,tmp);
if(C_truep(((C_word*)((C_word*)t0)[9])[1])){
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5226,a[2]=t6,a[3]=((C_word*)t0)[9],tmp=(C_word)a,a+=4,tmp);
t8=(C_word)C_i_cadr(((C_word*)((C_word*)t0)[9])[1]);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t7,t8,C_SCHEME_END_OF_LIST,((C_word*)t0)[2]);}
else{
t7=C_set_block_item(((C_word*)t0)[9],0,C_fix(1));
t8=t6;
f_4976(t8,t7);}}

/* k5224 in k4967 in k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5226(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_4976(t3,t2);}

/* k4974 in k4967 in k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_4976(C_word t0,C_word t1){
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
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4976,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_4979,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],a[5]=((C_word*)t0)[8],a[6]=((C_word*)t0)[9],a[7]=((C_word*)t0)[10],a[8]=((C_word*)t0)[11],a[9]=((C_word*)t0)[12],tmp=(C_word)a,a+=10,tmp);
if(C_truep((C_word)C_i_nequalp(((C_word*)((C_word*)t0)[4])[1],C_fix(6)))){
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5165,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t2,a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[9],tmp=(C_word)a,a+=8,tmp);
t4=(C_word)C_i_cadddr(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t3,t4,C_SCHEME_END_OF_LIST,((C_word*)t0)[3]);}
else{
t3=C_set_block_item(((C_word*)t0)[9],0,C_fix(0));
t4=(C_word)C_i_caddr(((C_word*)t0)[2]);
t5=C_mutate(((C_word *)((C_word*)t0)[6])+1,t4);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5214,a[2]=t2,a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t7=(C_word)C_i_cadddr(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t6,t7,C_SCHEME_END_OF_LIST,((C_word*)t0)[3]);}}

/* k5212 in k4974 in k4967 in k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5214(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_4979(t3,t2);}

/* k5163 in k4974 in k4967 in k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5165(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5165,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[7])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5171,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  fifth");
t4=C_retrieve(lf[243]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)t0)[2]);}

/* k5169 in k5163 in k4974 in k4967 in k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5171(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5171,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5195,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  fifth");
t3=C_retrieve(lf[243]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)t0)[2]);}
else{
t2=C_set_block_item(((C_word*)t0)[6],0,C_SCHEME_FALSE);
t3=C_set_block_item(((C_word*)t0)[5],0,C_SCHEME_FALSE);
t4=((C_word*)t0)[4];
f_4979(t4,t3);}}

/* k5193 in k5169 in k5163 in k4974 in k4967 in k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5195(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5195,2,t0,t1);}
t2=(C_word)C_i_car(t1);
t3=C_mutate(((C_word *)((C_word*)t0)[6])+1,t2);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5179,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5191,a[2]=((C_word*)t0)[3],a[3]=t4,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  fifth");
t6=C_retrieve(lf[243]);
((C_proc3)C_retrieve_proc(t6))(3,t6,t5,((C_word*)t0)[2]);}

/* k5189 in k5193 in k5169 in k5163 in k4974 in k4967 in k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5191(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cadr(t1);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(((C_word*)t0)[3],t2,C_SCHEME_END_OF_LIST,((C_word*)t0)[2]);}

/* k5177 in k5193 in k5169 in k5163 in k4974 in k4967 in k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5179(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_4979(t3,t2);}

/* k4977 in k4974 in k4967 in k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_4979(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[15],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4979,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_4982,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],tmp=(C_word)a,a+=10,tmp);
if(C_truep((C_word)C_i_numberp(((C_word*)((C_word*)t0)[5])[1]))){
t3=t2;
f_4982(t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5141,a[2]=t2,a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[9],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  gensym");
t4=C_retrieve(lf[237]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,lf[254]);}}

/* k5139 in k4977 in k4974 in k4967 in k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5141(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[24],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5141,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_5145,a[2]=((C_word*)t0)[2],a[3]=t1,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=(C_word)C_a_i_list(&a,5,t1,((C_word*)((C_word*)t0)[3])[1],C_SCHEME_FALSE,C_SCHEME_FALSE,C_SCHEME_FALSE);
t4=(C_word)C_a_i_list(&a,1,t3);
C_trace("ChickenBridge.scm: 145  append");
t5=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t2,((C_word*)((C_word*)t0)[4])[1],t4);}

/* k5143 in k5139 in k4977 in k4974 in k4967 in k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5145(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[5])+1,t1);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,((C_word*)t0)[3]);
t4=((C_word*)t0)[2];
f_4982(t4,t3);}

/* k4980 in k4977 in k4974 in k4967 in k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_4982(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[15],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4982,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_4985,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],tmp=(C_word)a,a+=10,tmp);
if(C_truep((C_word)C_i_numberp(((C_word*)((C_word*)t0)[6])[1]))){
t3=t2;
f_4985(t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5118,a[2]=t2,a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[9],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  gensym");
t4=C_retrieve(lf[237]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,lf[253]);}}

/* k5116 in k4980 in k4977 in k4974 in k4967 in k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5118(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[24],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5118,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_5122,a[2]=((C_word*)t0)[2],a[3]=t1,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=(C_word)C_a_i_list(&a,5,t1,((C_word*)((C_word*)t0)[3])[1],C_SCHEME_FALSE,C_SCHEME_FALSE,C_SCHEME_FALSE);
t4=(C_word)C_a_i_list(&a,1,t3);
C_trace("ChickenBridge.scm: 145  append");
t5=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t2,((C_word*)((C_word*)t0)[4])[1],t4);}

/* k5120 in k5116 in k4980 in k4977 in k4974 in k4967 in k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5122(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[5])+1,t1);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,((C_word*)t0)[3]);
t4=((C_word*)t0)[2];
f_4985(t4,t3);}

/* k4983 in k4980 in k4977 in k4974 in k4967 in k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_4985(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[15],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4985,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_4988,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],tmp=(C_word)a,a+=10,tmp);
if(C_truep(((C_word*)((C_word*)t0)[2])[1])){
if(C_truep((C_word)C_i_numberp(((C_word*)((C_word*)t0)[2])[1]))){
t3=t2;
f_4988(t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5095,a[2]=t2,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[9],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  gensym");
t4=C_retrieve(lf[237]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,lf[252]);}}
else{
t3=t2;
f_4988(t3,C_SCHEME_UNDEFINED);}}

/* k5093 in k4983 in k4980 in k4977 in k4974 in k4967 in k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5095(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[24],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5095,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_5099,a[2]=((C_word*)t0)[2],a[3]=t1,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=(C_word)C_a_i_list(&a,5,t1,((C_word*)((C_word*)t0)[3])[1],C_SCHEME_FALSE,C_SCHEME_FALSE,C_SCHEME_FALSE);
t4=(C_word)C_a_i_list(&a,1,t3);
C_trace("ChickenBridge.scm: 145  append");
t5=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t2,((C_word*)((C_word*)t0)[4])[1],t4);}

/* k5097 in k5093 in k4983 in k4980 in k4977 in k4974 in k4967 in k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5099(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[5])+1,t1);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,((C_word*)t0)[3]);
t4=((C_word*)t0)[2];
f_4988(t4,t3);}

/* k4986 in k4983 in k4980 in k4977 in k4974 in k4967 in k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_4988(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[34],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4988,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_4991,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],tmp=(C_word)a,a+=8,tmp);
t3=((C_word*)((C_word*)t0)[3])[1];
if(C_truep(t3)){
t4=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5020,a[2]=((C_word*)t0)[3],a[3]=t2,a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[2],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3227(t4,((C_word*)((C_word*)t0)[3])[1],C_fix(21248));}
else{
t4=(C_word)C_a_i_list(&a,3,lf[215],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[5])[1]);
t5=(C_word)C_a_i_list(&a,3,lf[235],((C_word*)((C_word*)t0)[7])[1],t4);
t6=C_mutate(((C_word *)((C_word*)t0)[5])+1,t5);
t7=t2;
f_4991(t7,t6);}}

/* k5018 in k4986 in k4983 in k4980 in k4977 in k4974 in k4967 in k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5020(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[35],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5020,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,3,lf[236],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[6])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[5])+1,t2);
t4=(C_word)C_a_i_list(&a,3,lf[215],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[4])[1]);
t5=(C_word)C_a_i_list(&a,3,lf[235],((C_word*)((C_word*)t0)[7])[1],t4);
t6=C_mutate(((C_word *)((C_word*)t0)[4])+1,t5);
t7=((C_word*)t0)[3];
f_4991(t7,t6);}
else{
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5038,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3227(t2,((C_word*)((C_word*)t0)[2])[1],C_fix(23552));}}

/* k5036 in k5018 in k4986 in k4983 in k4980 in k4977 in k4974 in k4967 in k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5038(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[35],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5038,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,3,lf[248],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[6])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[5])+1,t2);
t4=(C_word)C_a_i_list(&a,3,lf[215],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[4])[1]);
t5=(C_word)C_a_i_list(&a,3,lf[235],((C_word*)((C_word*)t0)[7])[1],t4);
t6=C_mutate(((C_word *)((C_word*)t0)[4])+1,t5);
t7=((C_word*)t0)[3];
f_4991(t7,t6);}
else{
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5056,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3227(t2,((C_word*)((C_word*)t0)[2])[1],C_fix(20992));}}

/* k5054 in k5036 in k5018 in k4986 in k4983 in k4980 in k4977 in k4974 in k4967 in k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5056(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[34],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5056,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,3,lf[249],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[6])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[5])+1,t2);
t4=(C_word)C_a_i_list(&a,3,lf[250],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[4])[1]);
t5=(C_word)C_a_i_list(&a,3,lf[235],((C_word*)((C_word*)t0)[7])[1],t4);
t6=C_mutate(((C_word *)((C_word*)t0)[4])+1,t5);
t7=((C_word*)t0)[3];
f_4991(t7,t6);}
else{
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5074,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3227(t2,((C_word*)((C_word*)t0)[2])[1],C_fix(21760));}}

/* k5072 in k5054 in k5036 in k5018 in k4986 in k4983 in k4980 in k4977 in k4974 in k4967 in k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_5074(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[27],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5074,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,3,lf[251],((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[5])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t4=(C_word)C_a_i_list(&a,3,lf[250],((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[3])[1]);
t5=(C_word)C_a_i_list(&a,3,lf[235],((C_word*)((C_word*)t0)[6])[1],t4);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t5);
t7=((C_word*)t0)[2];
f_4991(t7,t6);}
else{
t2=((C_word*)t0)[2];
f_4991(t2,C_SCHEME_UNDEFINED);}}

/* k4989 in k4986 in k4983 in k4980 in k4977 in k4974 in k4967 in k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_4991(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4991,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_4995,a[2]=((C_word*)t0)[6],a[3]=((C_word*)t0)[7],tmp=(C_word)a,a+=4,tmp);
t3=(C_word)C_a_i_list(&a,5,((C_word*)((C_word*)t0)[5])[1],((C_word*)((C_word*)t0)[4])[1],C_SCHEME_FALSE,((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);
t4=(C_word)C_a_i_list(&a,1,t3);
C_trace("ChickenBridge.scm: 145  append");
t5=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t2,((C_word*)((C_word*)t0)[7])[1],t4);}

/* k4993 in k4989 in k4986 in k4983 in k4980 in k4977 in k4974 in k4967 in k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4995(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_4748(t3,t2);}

/* k4903 in k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4905(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4905,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_4909,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[8],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
t4=(C_word)C_i_cadddr(((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t3,t4,C_SCHEME_END_OF_LIST,((C_word*)t0)[2]);}

/* k4907 in k4903 in k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4909(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4909,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_4913,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[5],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  gensym");
t4=C_retrieve(lf[237]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,lf[247]);}

/* k4911 in k4907 in k4903 in k4899 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4913(C_word c,C_word t0,C_word t1){
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
C_word ab[72],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4913,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(C_word)C_a_i_list(&a,2,lf[244],((C_word*)((C_word*)t0)[6])[1]);
t4=(C_word)C_a_i_list(&a,3,lf[235],((C_word*)((C_word*)t0)[6])[1],t3);
t5=(C_word)C_a_i_list(&a,2,lf[245],((C_word*)((C_word*)t0)[6])[1]);
t6=(C_word)C_a_i_list(&a,5,((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[5])[1],C_SCHEME_FALSE,t4,t5);
t7=(C_word)C_a_i_list(&a,2,lf[246],((C_word*)((C_word*)t0)[6])[1]);
t8=(C_word)C_a_i_list(&a,3,lf[235],((C_word*)((C_word*)t0)[4])[1],t7);
t9=(C_word)C_a_i_list(&a,5,((C_word*)((C_word*)t0)[4])[1],C_SCHEME_FALSE,t8,C_SCHEME_FALSE,C_SCHEME_FALSE);
t10=(C_word)C_a_i_list(&a,2,t6,t9);
t11=C_mutate(((C_word *)((C_word*)t0)[3])+1,t10);
t12=((C_word*)t0)[2];
f_4748(t12,t11);}

/* k4806 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4808(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4808,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[10])+1,t1);
t3=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_4812,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[10],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],a[10]=((C_word*)t0)[9],tmp=(C_word)a,a+=11,tmp);
t4=(C_word)C_i_cadddr(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t3,t4,C_SCHEME_END_OF_LIST,((C_word*)t0)[3]);}

/* k4810 in k4806 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4812(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4812,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[10])+1,t1);
t3=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_4816,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[10],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 145  fifth");
t4=C_retrieve(lf[243]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)t0)[2]);}

/* k4814 in k4810 in k4806 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4816(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[24],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4816,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[9])+1,t1);
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_4819,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],a[5]=((C_word*)t0)[8],tmp=(C_word)a,a+=6,tmp);
if(C_truep(((C_word*)((C_word*)t0)[9])[1])){
t4=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_4835,a[2]=t3,a[3]=((C_word*)t0)[8],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[4],a[8]=((C_word*)t0)[9],tmp=(C_word)a,a+=9,tmp);
t5=(C_word)C_i_cadr(((C_word*)((C_word*)t0)[9])[1]);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t4,t5,C_SCHEME_END_OF_LIST,((C_word*)t0)[2]);}
else{
t4=(C_word)C_a_i_list(&a,3,lf[235],((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[3])[1]);
t5=C_mutate(((C_word *)((C_word*)t0)[5])+1,t4);
t6=t3;
f_4819(t6,t5);}}

/* k4833 in k4814 in k4810 in k4806 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4835(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4835,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_4839,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[8],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 145  gensym");
t4=C_retrieve(lf[237]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,lf[242]);}

/* k4837 in k4833 in k4814 in k4810 in k4806 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4839(C_word c,C_word t0,C_word t1){
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
C_word ab[66],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4839,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(C_word)C_a_i_list(&a,3,lf[235],((C_word*)((C_word*)t0)[8])[1],C_SCHEME_FALSE);
t4=(C_word)C_a_i_list(&a,3,lf[235],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[6])[1]);
t5=(C_word)C_a_i_list(&a,3,lf[240],t3,t4);
t6=(C_word)C_a_i_list(&a,3,lf[235],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[5])[1]);
t7=(C_word)C_a_i_list(&a,4,lf[241],((C_word*)((C_word*)t0)[8])[1],t5,t6);
t8=C_mutate(((C_word *)((C_word*)t0)[4])+1,t7);
t9=(C_word)C_a_i_list(&a,5,((C_word*)((C_word*)t0)[8])[1],C_SCHEME_TRUE,C_SCHEME_FALSE,C_SCHEME_FALSE,C_SCHEME_FALSE);
t10=(C_word)C_a_i_list(&a,1,t9);
t11=C_mutate(((C_word *)((C_word*)t0)[3])+1,t10);
t12=((C_word*)t0)[2];
f_4819(t12,t11);}

/* k4817 in k4814 in k4810 in k4806 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_4819(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4819,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_4823,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t3=(C_word)C_a_i_list(&a,5,((C_word*)((C_word*)t0)[3])[1],C_SCHEME_FALSE,((C_word*)((C_word*)t0)[2])[1],C_SCHEME_FALSE,C_SCHEME_FALSE);
t4=(C_word)C_a_i_list(&a,1,t3);
C_trace("ChickenBridge.scm: 145  append");
t5=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t2,((C_word*)((C_word*)t0)[5])[1],t4);}

/* k4821 in k4817 in k4814 in k4810 in k4806 in k4802 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4823(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_4748(t3,t2);}

/* k4756 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4758(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4758,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_4762,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  gensym");
t4=C_retrieve(lf[237]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,lf[239]);}

/* k4760 in k4756 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4762(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4762,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_4766,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  gensym");
t4=C_retrieve(lf[237]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,lf[238]);}

/* k4764 in k4760 in k4756 in k4752 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4766(C_word c,C_word t0,C_word t1){
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
C_word ab[63],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4766,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(C_word)C_a_i_list(&a,5,((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[5])[1],C_SCHEME_FALSE,C_SCHEME_FALSE,C_SCHEME_FALSE);
t4=(C_word)C_a_i_list(&a,3,lf[215],((C_word*)((C_word*)t0)[4])[1],C_fix(1));
t5=(C_word)C_a_i_list(&a,3,lf[235],((C_word*)((C_word*)t0)[4])[1],t4);
t6=(C_word)C_a_i_list(&a,3,lf[236],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[6])[1]);
t7=(C_word)C_a_i_list(&a,5,((C_word*)((C_word*)t0)[4])[1],C_fix(0),C_SCHEME_FALSE,t5,t6);
t8=(C_word)C_a_i_list(&a,2,t3,t7);
t9=C_mutate(((C_word *)((C_word*)t0)[3])+1,t8);
t10=((C_word*)t0)[2];
f_4748(t10,t9);}

/* k4746 in sal-parse-stepping in k4737 in k4734 in k4731 in k4728 in k4725 in k4722 in k4719 in k4716 in k4713 in k4710 in k4707 in k4704 in k4701 in k4698 in k4695 in k4692 in k4689 in k4686 in k4683 in k4680 in k4677 in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_4748(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3142(((C_word*)t0)[3],C_fix(33024),((C_word*)((C_word*)t0)[2])[1],C_SCHEME_FALSE);}

/* inf->pre in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_4563(C_word t1,C_word t2){
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
C_word t14;
C_word t15;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4563,NULL,2,t1,t2);}
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_SCHEME_FALSE;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_SCHEME_FALSE;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=C_SCHEME_FALSE;
t9=(*a=C_VECTOR_TYPE|1,a[1]=t8,tmp=(C_word)a,a+=2,tmp);
t10=C_SCHEME_FALSE;
t11=(*a=C_VECTOR_TYPE|1,a[1]=t10,tmp=(C_word)a,a+=2,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t3)[1]))){
t12=C_SCHEME_UNDEFINED;
t13=(*a=C_VECTOR_TYPE|1,a[1]=t12,tmp=(C_word)a,a+=2,tmp);
t14=C_set_block_item(t13,0,(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_4575,a[2]=t9,a[3]=t13,a[4]=t11,a[5]=t5,a[6]=t7,a[7]=t3,a[8]=lf[232],tmp=(C_word)a,a+=9,tmp));
t15=((C_word*)t13)[1];
f_4575(t15,t1);}
else{
t12=t1;
((C_proc2)(void*)(*((C_word*)t12+1)))(2,t12,((C_word*)t3)[1]);}}

/* do859 in inf->pre in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_4575(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4575,NULL,2,t0,t1);}
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[7])[1]))){
t2=t1;
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,((C_word*)((C_word*)t0)[6])[1]);}
else{
t2=(C_word)C_i_car(((C_word*)((C_word*)t0)[7])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[5])+1,t2);
t4=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[7])[1]);
t5=C_mutate(((C_word *)((C_word*)t0)[7])+1,t4);
t6=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_4594,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[7],a[6]=t1,a[7]=((C_word*)t0)[3],a[8]=((C_word*)t0)[4],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 145  is-op?");
f_4542(t6,((C_word*)((C_word*)t0)[5])[1]);}}

/* k4592 in do859 in inf->pre in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4594(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[15],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4594,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_4597,a[2]=((C_word*)t0)[6],a[3]=((C_word*)t0)[7],tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_numberp(((C_word*)((C_word*)t0)[8])[1]))){
t4=C_SCHEME_UNDEFINED;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_set_block_item(t5,0,(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_4612,a[2]=((C_word*)t0)[8],a[3]=t5,a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[5],a[8]=lf[231],tmp=(C_word)a,a+=9,tmp));
t7=((C_word*)t5)[1];
f_4612(t7,t3,C_SCHEME_FALSE,C_SCHEME_TRUE,C_SCHEME_END_OF_LIST);}
else{
t4=C_mutate(((C_word *)((C_word*)t0)[3])+1,((C_word*)((C_word*)t0)[2])[1]);
t5=t3;
f_4597(2,t5,t4);}}

/* do861 in k4592 in do859 in inf->pre in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_4612(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
C_word ab[24],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4612,NULL,5,t0,t1,t2,t3,t4);}
t5=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t8=(C_word)C_i_nullp(((C_word*)((C_word*)t0)[7])[1]);
t9=(C_truep(t8)?t8:(C_word)C_i_not(((C_word*)t6)[1]));
if(C_truep(t9)){
t10=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_4626,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],tmp=(C_word)a,a+=6,tmp);
t11=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4640,a[2]=t10,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  reverse");
t12=*((C_word*)lf[201]+1);
((C_proc3)C_retrieve_proc(t12))(3,t12,t11,((C_word*)t7)[1]);}
else{
t10=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_4644,a[2]=((C_word*)t0)[7],a[3]=((C_word*)t0)[2],a[4]=t7,a[5]=t6,a[6]=t1,a[7]=((C_word*)t0)[3],a[8]=t5,tmp=(C_word)a,a+=9,tmp);
t11=(C_word)C_i_car(((C_word*)((C_word*)t0)[7])[1]);
C_trace("ChickenBridge.scm: 145  is-op?");
f_4542(t10,t11);}}

/* k4642 in do861 in k4592 in do859 in inf->pre in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4644(C_word c,C_word t0,C_word t1){
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
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4644,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_4647,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[8],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
t4=(C_truep(((C_word*)((C_word*)t0)[8])[1])?(C_word)C_i_less_or_equalp(((C_word*)((C_word*)t0)[8])[1],((C_word*)((C_word*)t0)[3])[1]):C_SCHEME_FALSE);
if(C_truep(t4)){
t5=C_set_block_item(((C_word*)t0)[5],0,C_SCHEME_FALSE);
t6=t3;
f_4647(t6,t5);}
else{
t5=(C_word)C_i_car(((C_word*)((C_word*)t0)[2])[1]);
t6=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[2])[1]);
t7=C_mutate(((C_word *)((C_word*)t0)[2])+1,t6);
t8=(C_word)C_a_i_cons(&a,2,t5,((C_word*)((C_word*)t0)[4])[1]);
t9=C_mutate(((C_word *)((C_word*)t0)[4])+1,t8);
t10=t3;
f_4647(t10,t9);}}

/* k4645 in k4642 in do861 in k4592 in do859 in inf->pre in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_4647(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[6])[1];
f_4612(t2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k4638 in do861 in k4592 in do859 in inf->pre in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4640(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  inf->pre");
f_4563(((C_word*)t0)[2],t1);}

/* k4624 in do861 in k4592 in do859 in inf->pre in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4626(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[18],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4626,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[5])+1,t1);
t3=(C_truep(((C_word*)((C_word*)t0)[4])[1])?(C_word)C_a_i_list(&a,3,((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[5])[1]):(C_word)C_a_i_list(&a,3,((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[5])[1],C_SCHEME_FALSE));
t4=C_mutate(((C_word *)((C_word*)t0)[4])+1,t3);
t5=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,t4);}

/* k4595 in k4592 in do859 in inf->pre in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4597(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[3])[1];
f_4575(t2,((C_word*)t0)[2]);}

/* is-op? in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_4542(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4542,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_4549,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  token-unit?");
f_3211(t3,t2);}

/* k4547 in is-op? in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4549(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4549,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4552,a[2]=((C_word*)t0)[3],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-type");
f_3163(t2,((C_word*)t0)[2]);}
else{
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}}

/* k4550 in k4547 in is-op? in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4552(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4552,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_4558,a[2]=t1,a[3]=((C_word*)t0)[2],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  SalOpType?");
f_4319(t2,t1);}

/* k4556 in k4550 in k4547 in is-op? in k4538 in k4535 in k4532 in k4529 in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4558(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4558,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[3];
t3=((C_word*)t0)[2];
t4=t2;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_a_i_bitwise_and(&a,2,t3,C_fix(255)));}
else{
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}}

/* remove-token-type in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_4477(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word ab[14],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4477,NULL,3,t1,t2,t3);}
t4=(C_word)C_a_i_list(&a,1,C_SCHEME_TRUE);
t5=t4;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=C_SCHEME_UNDEFINED;
t8=(*a=C_VECTOR_TYPE|1,a[1]=t7,tmp=(C_word)a,a+=2,tmp);
t9=C_set_block_item(t8,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_4486,a[2]=t3,a[3]=t6,a[4]=t8,a[5]=t4,a[6]=lf[226],tmp=(C_word)a,a+=7,tmp));
t10=((C_word*)t8)[1];
f_4486(t10,t1,t2);}

/* do825 in remove-token-type in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_4486(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4486,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_i_cdr(((C_word*)t0)[5]));}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_4499,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_4509,a[2]=((C_word*)t0)[3],a[3]=t2,a[4]=t3,tmp=(C_word)a,a+=5,tmp);
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3227(t4,t5,((C_word*)t0)[2]);}}

/* k4507 in do825 in remove-token-type in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4509(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4509,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
f_4499(t2,C_SCHEME_FALSE);}
else{
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=(C_word)C_a_i_list(&a,1,t2);
t4=(C_word)C_i_set_cdr(((C_word*)((C_word*)t0)[2])[1],t3);
t5=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[2])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[2])+1,t5);
t7=((C_word*)t0)[4];
f_4499(t7,t6);}}

/* k4497 in do825 in remove-token-type in k4473 in k4470 in k4467 in k4464 in k4461 in k4458 in k4455 in k4452 in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_4499(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_4486(t3,((C_word*)t0)[2],t2);}

/* SalType=? in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_4433(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4433,NULL,3,t1,t2,t3);}
t4=(C_word)C_a_i_arithmetic_shift(&a,2,t2,C_fix(-8));
t5=(C_word)C_a_i_arithmetic_shift(&a,2,t3,C_fix(-8));
t6=t1;
((C_proc2)(void*)(*((C_word*)t6+1)))(2,t6,(C_word)C_i_nequalp(t4,t5));}

/* SalRuleType? in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_4421(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4421,NULL,2,t1,t2);}
t3=(C_word)C_i_lessp(C_fix(25600),t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_truep(t3)?(C_word)C_i_lessp(t2,C_fix(38400)):C_SCHEME_FALSE));}

/* SalOpType? in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_4319(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4319,NULL,2,t1,t2);}
t3=(C_word)C_i_lessp(C_fix(6656),t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_truep(t3)?(C_word)C_i_lessp(t2,C_fix(11520)):C_SCHEME_FALSE));}

/* SalTokenType? in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_4271(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4271,NULL,2,t1,t2);}
t3=(C_word)C_i_lessp(C_fix(0),t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_truep(t3)?(C_word)C_i_lessp(t2,C_fix(25600)):C_SCHEME_FALSE));}

/* parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3652(C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
C_word tmp;
C_word t8;
C_word t9;
C_word t10;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3652,NULL,7,t1,t2,t3,t4,t5,t6,t7);}
t8=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t9=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_3656,a[2]=t4,a[3]=t7,a[4]=t6,a[5]=t5,a[6]=t8,a[7]=t1,a[8]=t2,tmp=(C_word)a,a+=9,tmp);
if(C_truep(t6)){
C_trace("ChickenBridge.scm: 145  printf");
t10=C_retrieve(lf[218]);
((C_proc6)C_retrieve_proc(t10))(6,t10,t9,lf[219],t5,t2,((C_word*)t8)[1]);}
else{
t10=t9;
f_3656(2,t10,C_SCHEME_UNDEFINED);}}

/* k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3656(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3656,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_3659,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 145  null-tokens?");
f_2834(t2,((C_word*)((C_word*)t0)[6])[1]);}

/* k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3659(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[18],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3659,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_3662,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
if(C_truep(t1)){
t3=t2;
f_3662(t3,t1);}
else{
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4077,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4081,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4085,a[2]=t4,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  first-token");
f_2822(t5,((C_word*)((C_word*)t0)[6])[1]);}}

/* k4083 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4085(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  token-position");
f_2781(((C_word*)t0)[2],t1);}

/* k4079 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4081(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  max");
t2=*((C_word*)lf[217]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[2],C_retrieve2(lf[196],"*maxtokpos*"),t1);}

/* k4075 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4077(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(&lf[196],t1);
t3=((C_word*)t0)[2];
f_3662(t3,t2);}

/* k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3662(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3662,NULL,2,t0,t1);}
t2=((C_word*)t0)[8];
if(C_truep((C_word)C_i_numberp(t2))){
t3=((C_word*)t0)[8];
t4=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_3677,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=t3,a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 145  SalTokenType?");
f_4271(t4,t3);}
else{
t3=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_3785,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[2],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 145  pattern-clause?");
f_2973(t3,((C_word*)t0)[8]);}}

/* k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3785(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[13],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3785,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_3791,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
t3=((C_word*)t0)[2];
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3018,a[2]=t2,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  pattern-clause?");
f_2973(t4,t3);}
else{
C_trace("ChickenBridge.scm: 145  error");
t2=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[6],lf[216],((C_word*)t0)[2]);}}

/* k3016 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3018(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=((C_word*)t0)[2];
f_3791(t3,(C_word)C_eqp(t2,lf[176]));}
else{
t2=((C_word*)t0)[2];
f_3791(t2,C_SCHEME_FALSE);}}

/* k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3791(C_word t0,C_word t1){
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
C_word ab[32],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3791,NULL,2,t0,t1);}
t2=(C_truep(t1)?t1:((C_word*)t0)[8]);
if(C_truep(t2)){
t3=C_SCHEME_FALSE;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=((C_word*)((C_word*)t0)[7])[1];
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=C_SCHEME_END_OF_LIST;
t8=(*a=C_VECTOR_TYPE|1,a[1]=t7,tmp=(C_word)a,a+=2,tmp);
t9=C_SCHEME_FALSE;
t10=(*a=C_VECTOR_TYPE|1,a[1]=t9,tmp=(C_word)a,a+=2,tmp);
t11=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_3800,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=t10,a[7]=((C_word*)t0)[7],a[8]=t6,a[9]=t8,a[10]=t4,a[11]=((C_word*)t0)[6],tmp=(C_word)a,a+=12,tmp);
C_trace("ChickenBridge.scm: 145  pattern-nsubs");
f_2991(t11,((C_word*)t0)[2]);}
else{
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_3879,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[6],tmp=(C_word)a,a+=8,tmp);
t4=((C_word*)t0)[2];
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3034,a[2]=t3,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  pattern-clause?");
f_2973(t5,t4);}}

/* k3032 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3034(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=((C_word*)t0)[2];
f_3879(t3,(C_word)C_eqp(t2,lf[177]));}
else{
t2=((C_word*)t0)[2];
f_3879(t2,C_SCHEME_FALSE);}}

/* k3877 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3879(C_word t0,C_word t1){
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
C_word ab[25],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3879,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=C_SCHEME_FALSE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_SCHEME_FALSE;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_SCHEME_END_OF_LIST;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_3885,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t7,a[8]=t5,a[9]=((C_word*)t0)[7],a[10]=t3,tmp=(C_word)a,a+=11,tmp);
C_trace("ChickenBridge.scm: 145  pattern-nsubs");
f_2991(t8,((C_word*)t0)[2]);}
else{
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_3949,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[2],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[6],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 145  pattern-zero-or-more?");
f_3059(t2,((C_word*)t0)[2]);}}

/* k3947 in k3877 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3949(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3949,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_3952,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
if(C_truep(t1)){
t3=t2;
f_3952(t3,t1);}
else{
t3=((C_word*)t0)[5];
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3050,a[2]=t2,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  pattern-clause?");
f_2973(t4,t3);}}

/* k3048 in k3947 in k3877 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3050(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=((C_word*)t0)[2];
f_3952(t3,(C_word)C_eqp(t2,lf[215]));}
else{
t2=((C_word*)t0)[2];
f_3952(t2,C_SCHEME_FALSE);}}

/* k3950 in k3947 in k3877 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3952(C_word t0,C_word t1){
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
C_word ab[46],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3952,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=C_SCHEME_TRUE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_SCHEME_FALSE;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=((C_word*)((C_word*)t0)[7])[1];
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=C_SCHEME_END_OF_LIST;
t9=(*a=C_VECTOR_TYPE|1,a[1]=t8,tmp=(C_word)a,a+=2,tmp);
t10=C_fix(0);
t11=(*a=C_VECTOR_TYPE|1,a[1]=t10,tmp=(C_word)a,a+=2,tmp);
t12=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_3958,a[2]=((C_word*)t0)[5],a[3]=t11,a[4]=((C_word*)t0)[7],a[5]=t9,a[6]=t3,a[7]=((C_word*)t0)[6],tmp=(C_word)a,a+=8,tmp);
t13=C_SCHEME_UNDEFINED;
t14=(*a=C_VECTOR_TYPE|1,a[1]=t13,tmp=(C_word)a,a+=2,tmp);
t15=C_set_block_item(t14,0,(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_3981,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=t5,a[7]=t11,a[8]=t7,a[9]=((C_word*)t0)[7],a[10]=t9,a[11]=t14,a[12]=t3,a[13]=lf[210],tmp=(C_word)a,a+=14,tmp));
t16=((C_word*)t14)[1];
f_3981(t16,t12);}
else{
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_4030,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[6],tmp=(C_word)a,a+=8,tmp);
t3=((C_word*)t0)[5];
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3082,a[2]=t2,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  pattern-clause?");
f_2973(t4,t3);}}

/* k3080 in k3950 in k3947 in k3877 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3082(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=((C_word*)t0)[2];
f_4030(t3,(C_word)C_eqp(t2,lf[214]));}
else{
t2=((C_word*)t0)[2];
f_4030(t2,C_SCHEME_FALSE);}}

/* k4028 in k3950 in k3947 in k3877 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_4030(C_word t0,C_word t1){
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
C_word ab[27],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4030,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=C_SCHEME_FALSE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_SCHEME_END_OF_LIST;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_SCHEME_END_OF_LIST;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_4039,a[2]=((C_word*)t0)[6],a[3]=t7,a[4]=t5,a[5]=((C_word*)t0)[7],a[6]=t3,tmp=(C_word)a,a+=7,tmp);
t9=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_4050,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[5],a[7]=lf[211],tmp=(C_word)a,a+=8,tmp);
t10=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_4056,a[2]=t7,a[3]=t5,a[4]=t3,a[5]=lf[212],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  call-with-values");
C_call_with_values(4,0,t8,t9,t10);}
else{
t2=((C_word*)t0)[5];
t3=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  error");
t4=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,((C_word*)t0)[7],lf[213],t3);}}

/* a4055 in k4028 in k3950 in k3947 in k3877 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4056(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_4056,5,t0,t1,t2,t3,t4);}
t5=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t3);
t7=C_mutate(((C_word *)((C_word*)t0)[2])+1,t4);
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,t7);}

/* a4049 in k4028 in k3950 in k3947 in k3877 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4050(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4050,2,t0,t1);}
C_trace("ChickenBridge.scm: 145  parser");
f_3652(t1,((C_word*)t0)[6],((C_word*)((C_word*)t0)[5])[1],C_SCHEME_TRUE,((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k4037 in k4028 in k3950 in k3947 in k3877 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4039(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(C_truep(((C_word*)((C_word*)t0)[6])[1])){
C_trace("ChickenBridge.scm: 145  values");
C_values(5,0,((C_word*)t0)[5],((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1]);}
else{
C_trace("ChickenBridge.scm: 145  values");
C_values(5,0,((C_word*)t0)[5],C_SCHEME_TRUE,C_SCHEME_FALSE,((C_word*)((C_word*)t0)[2])[1]);}}

/* do562 in k3950 in k3947 in k3877 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3981(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[14],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3981,NULL,2,t0,t1);}
t2=(C_word)C_i_not(((C_word*)((C_word*)t0)[12])[1]);
t3=(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_3991,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],a[10]=((C_word*)t0)[10],a[11]=((C_word*)t0)[12],a[12]=((C_word*)t0)[11],a[13]=t1,tmp=(C_word)a,a+=14,tmp);
if(C_truep(t2)){
t4=t3;
f_3991(2,t4,t2);}
else{
C_trace("ChickenBridge.scm: 145  null-tokens?");
f_2834(t3,((C_word*)((C_word*)t0)[8])[1]);}}

/* k3989 in do562 in k3950 in k3947 in k3877 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3991(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[24],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3991,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[13];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}
else{
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_3994,a[2]=((C_word*)t0)[6],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[8],a[5]=((C_word*)t0)[9],a[6]=((C_word*)t0)[10],a[7]=((C_word*)t0)[11],a[8]=((C_word*)t0)[13],a[9]=((C_word*)t0)[12],tmp=(C_word)a,a+=10,tmp);
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_4011,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[8],a[6]=((C_word*)t0)[5],a[7]=lf[208],tmp=(C_word)a,a+=8,tmp);
t4=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_4017,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[11],a[5]=lf[209],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  call-with-values");
C_call_with_values(4,0,t2,t3,t4);}}

/* a4016 in k3989 in do562 in k3950 in k3947 in k3877 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4017(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_4017,5,t0,t1,t2,t3,t4);}
t5=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t3);
t7=C_mutate(((C_word *)((C_word*)t0)[2])+1,t4);
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,t7);}

/* a4010 in k3989 in do562 in k3950 in k3947 in k3877 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4011(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4011,2,t0,t1);}
C_trace("ChickenBridge.scm: 145  parser");
f_3652(t1,((C_word*)t0)[6],((C_word*)((C_word*)t0)[5])[1],C_SCHEME_TRUE,((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k3992 in k3989 in do562 in k3950 in k3947 in k3877 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3994(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3994,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3997,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[9],tmp=(C_word)a,a+=4,tmp);
if(C_truep(((C_word*)((C_word*)t0)[7])[1])){
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_4004,a[2]=t2,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  append");
t4=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t3,((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[2])[1]);}
else{
t3=t2;
f_3997(t3,C_SCHEME_UNDEFINED);}}

/* k4002 in k3992 in k3989 in do562 in k3950 in k3947 in k3877 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_4004(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4004,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=C_mutate(((C_word *)((C_word*)t0)[5])+1,((C_word*)((C_word*)t0)[4])[1]);
t4=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[3])[1],C_fix(1));
t5=C_mutate(((C_word *)((C_word*)t0)[3])+1,t4);
t6=((C_word*)t0)[2];
f_3997(t6,t5);}

/* k3995 in k3992 in k3989 in do562 in k3950 in k3947 in k3877 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3997(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[3])[1];
f_3981(t2,((C_word*)t0)[2]);}

/* k3956 in k3950 in k3947 in k3877 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3958(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3958,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3961,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],tmp=(C_word)a,a+=6,tmp);
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3967,a[2]=((C_word*)t0)[5],a[3]=t2,a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[3],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  pattern-zero-or-more?");
f_3059(t3,((C_word*)t0)[2]);}

/* k3965 in k3956 in k3950 in k3947 in k3877 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3967(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word *a;
t2=(C_truep(t1)?t1:(C_word)C_i_greaterp(((C_word*)((C_word*)t0)[5])[1],C_fix(0)));
if(C_truep(t2)){
t3=C_set_block_item(((C_word*)t0)[4],0,C_SCHEME_TRUE);
t4=((C_word*)t0)[3];
f_3961(t4,t3);}
else{
t3=C_set_block_item(((C_word*)t0)[4],0,C_SCHEME_FALSE);
t4=C_set_block_item(((C_word*)t0)[2],0,C_SCHEME_END_OF_LIST);
t5=((C_word*)t0)[3];
f_3961(t5,t4);}}

/* k3959 in k3956 in k3950 in k3947 in k3877 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3961(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  values");
C_values(5,0,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k3883 in k3877 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3885(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3885,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_3888,a[2]=((C_word*)t0)[6],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[8],a[5]=((C_word*)t0)[9],a[6]=((C_word*)t0)[10],tmp=(C_word)a,a+=7,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_3903,a[2]=((C_word*)t0)[7],a[3]=((C_word*)t0)[8],a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[5],a[9]=t4,a[10]=t1,a[11]=((C_word*)t0)[10],a[12]=lf[207],tmp=(C_word)a,a+=13,tmp));
t6=((C_word*)t4)[1];
f_3903(t6,t2,C_fix(0));}

/* do542 in k3883 in k3877 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3903(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[20],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3903,NULL,3,t0,t1,t2);}
t3=((C_word*)((C_word*)t0)[11])[1];
t4=(C_truep(t3)?t3:(C_word)C_i_nequalp(t2,((C_word*)t0)[10]));
if(C_truep(t4)){
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,C_SCHEME_FALSE);}
else{
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3913,a[2]=t1,a[3]=((C_word*)t0)[9],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t6=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_3922,a[2]=t2,a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],a[8]=lf[205],tmp=(C_word)a,a+=9,tmp);
t7=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3936,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[11],a[5]=lf[206],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  call-with-values");
C_call_with_values(4,0,t5,t6,t7);}}

/* a3935 in do542 in k3883 in k3877 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3936(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_3936,5,t0,t1,t2,t3,t4);}
t5=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t3);
t7=C_mutate(((C_word *)((C_word*)t0)[2])+1,t4);
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,t7);}

/* a3921 in do542 in k3883 in k3877 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3922(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[7],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3922,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_3930,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=t1,a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  pattern-sub");
f_3001(t2,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k3928 in a3921 in do542 in k3883 in k3877 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3930(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3930,2,t0,t1);}
t2=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[6],C_fix(1));
C_trace("ChickenBridge.scm: 145  parser");
f_3652(((C_word*)t0)[5],t1,((C_word*)((C_word*)t0)[4])[1],C_SCHEME_FALSE,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k3911 in do542 in k3883 in k3877 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3913(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3913,2,t0,t1);}
t2=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[4],C_fix(1));
t3=((C_word*)((C_word*)t0)[3])[1];
f_3903(t3,((C_word*)t0)[2],t2);}

/* k3886 in k3883 in k3877 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3888(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(C_truep(((C_word*)((C_word*)t0)[6])[1])){
C_trace("ChickenBridge.scm: 145  values");
C_values(5,0,((C_word*)t0)[5],((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1]);}
else{
C_trace("ChickenBridge.scm: 145  values");
C_values(5,0,((C_word*)t0)[5],C_SCHEME_FALSE,C_SCHEME_END_OF_LIST,((C_word*)((C_word*)t0)[2])[1]);}}

/* k3798 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3800(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[26],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3800,2,t0,t1);}
t2=C_SCHEME_FALSE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_3803,a[2]=((C_word*)t0)[7],a[3]=t3,a[4]=((C_word*)t0)[8],a[5]=((C_word*)t0)[9],a[6]=((C_word*)t0)[10],a[7]=((C_word*)t0)[11],tmp=(C_word)a,a+=8,tmp);
t5=C_SCHEME_UNDEFINED;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=C_set_block_item(t6,0,(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_3822,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[8],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[9],a[8]=((C_word*)t0)[6],a[9]=((C_word*)t0)[10],a[10]=t6,a[11]=t3,a[12]=t1,a[13]=lf[204],tmp=(C_word)a,a+=14,tmp));
t8=((C_word*)t6)[1];
f_3822(t8,t4,C_fix(0));}

/* do520 in k3798 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3822(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[24],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3822,NULL,3,t0,t1,t2);}
t3=(C_word)C_i_nequalp(t2,((C_word*)t0)[12]);
t4=(C_truep(t3)?t3:((C_word*)((C_word*)t0)[11])[1]);
if(C_truep(t4)){
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,C_SCHEME_FALSE);}
else{
t5=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_3835,a[2]=((C_word*)t0)[11],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[8],a[5]=((C_word*)t0)[9],a[6]=t1,a[7]=((C_word*)t0)[10],a[8]=t2,tmp=(C_word)a,a+=9,tmp);
t6=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_3855,a[2]=t2,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=lf[202],tmp=(C_word)a,a+=9,tmp);
t7=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3869,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[8],a[4]=((C_word*)t0)[9],a[5]=lf[203],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  call-with-values");
C_call_with_values(4,0,t5,t6,t7);}}

/* a3868 in do520 in k3798 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3869(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_3869,5,t0,t1,t2,t3,t4);}
t5=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t3);
t7=C_mutate(((C_word *)((C_word*)t0)[2])+1,t4);
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,t7);}

/* a3854 in do520 in k3798 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3855(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[7],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3855,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_3863,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=t1,a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  pattern-sub");
f_3001(t2,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k3861 in a3854 in do520 in k3798 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3863(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3863,2,t0,t1);}
t2=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[6],C_fix(1));
C_trace("ChickenBridge.scm: 145  parser");
f_3652(((C_word*)t0)[5],t1,((C_word*)((C_word*)t0)[4])[1],C_SCHEME_FALSE,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k3833 in do520 in k3798 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3835(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3835,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3838,a[2]=((C_word*)t0)[6],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[8],tmp=(C_word)a,a+=5,tmp);
t3=((C_word*)((C_word*)t0)[5])[1];
if(C_truep(t3)){
t4=(C_word)C_a_i_cons(&a,2,((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1]);
t5=C_mutate(((C_word *)((C_word*)t0)[3])+1,t4);
t6=t2;
f_3838(t6,t5);}
else{
t4=C_set_block_item(((C_word*)t0)[2],0,C_SCHEME_TRUE);
t5=t2;
f_3838(t5,t4);}}

/* k3836 in k3833 in do520 in k3798 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3838(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3838,NULL,2,t0,t1);}
t2=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[4],C_fix(1));
t3=((C_word*)((C_word*)t0)[3])[1];
f_3822(t3,((C_word*)t0)[2],t2);}

/* k3801 in k3798 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3803(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3803,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3806,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],tmp=(C_word)a,a+=6,tmp);
if(C_truep(((C_word*)((C_word*)t0)[3])[1])){
t3=C_set_block_item(((C_word*)t0)[6],0,C_SCHEME_FALSE);
t4=C_set_block_item(((C_word*)t0)[5],0,C_SCHEME_END_OF_LIST);
t5=C_mutate(((C_word *)((C_word*)t0)[4])+1,((C_word*)((C_word*)t0)[2])[1]);
t6=t2;
f_3806(t6,t5);}
else{
t3=C_set_block_item(((C_word*)t0)[6],0,C_SCHEME_TRUE);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3820,a[2]=t2,a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  reverse");
t5=*((C_word*)lf[201]+1);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,((C_word*)((C_word*)t0)[5])[1]);}}

/* k3818 in k3801 in k3798 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3820(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_3806(t3,t2);}

/* k3804 in k3801 in k3798 in k3789 in k3783 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3806(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  values");
C_values(5,0,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k3675 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3677(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[13],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3677,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3683,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  null-tokens?");
f_2834(t2,((C_word*)((C_word*)t0)[6])[1]);}
else{
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_3735,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[4],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 145  SalRuleType?");
f_4421(t2,((C_word*)t0)[5]);}}

/* k3733 in k3675 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3735(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3735,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_3738,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  get-rule");
f_2949(t2,((C_word*)t0)[2],C_SCHEME_END_OF_LIST);}
else{
C_trace("ChickenBridge.scm: 145  error");
t2=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[3],lf[200],((C_word*)t0)[2]);}}

/* k3736 in k3733 in k3675 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3738(C_word c,C_word t0,C_word t1){
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
C_word ab[13],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3738,2,t0,t1);}
t2=t1;
t3=(C_word)C_i_check_structure(t2,lf[122]);
t4=(C_word)C_i_block_ref(t2,C_fix(3));
t5=t1;
t6=(C_word)C_i_check_structure(t5,lf[122]);
t7=(C_word)C_i_block_ref(t5,C_fix(4));
t8=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_3749,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=t4,a[6]=((C_word*)t0)[6],a[7]=lf[198],tmp=(C_word)a,a+=8,tmp);
t9=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3759,a[2]=((C_word*)t0)[3],a[3]=t7,a[4]=lf[199],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  call-with-values");
C_call_with_values(4,0,((C_word*)t0)[2],t8,t9);}

/* a3758 in k3736 in k3733 in k3675 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3759(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_3759,5,t0,t1,t2,t3,t4);}
if(C_truep(t2)){
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3770,a[2]=t4,a[3]=t2,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
if(C_truep(((C_word*)t0)[3])){
C_trace("ChickenBridge.scm: 145  func");
t6=((C_word*)t0)[3];
((C_proc4)C_retrieve_proc(t6))(4,t6,t5,t3,((C_word*)t0)[2]);}
else{
t6=t5;
f_3770(2,t6,t3);}}
else{
C_trace("ChickenBridge.scm: 145  values");
C_values(5,0,t1,C_SCHEME_FALSE,C_SCHEME_FALSE,t4);}}

/* k3768 in a3758 in k3736 in k3733 in k3675 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3770(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  values");
C_values(5,0,((C_word*)t0)[4],((C_word*)t0)[3],t1,((C_word*)t0)[2]);}

/* a3748 in k3736 in k3733 in k3675 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3749(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3749,2,t0,t1);}
t2=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[6],C_fix(1));
C_trace("ChickenBridge.scm: 145  parser");
f_3652(t1,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],C_SCHEME_FALSE,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k3681 in k3675 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3683(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3683,2,t0,t1);}
if(C_truep(t1)){
C_trace("ChickenBridge.scm: 145  values");
C_values(5,0,((C_word*)t0)[4],C_SCHEME_FALSE,C_SCHEME_FALSE,C_SCHEME_END_OF_LIST);}
else{
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3693,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  first-token");
f_2822(t2,((C_word*)((C_word*)t0)[3])[1]);}}

/* k3691 in k3681 in k3675 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3693(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3693,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3699,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3729,a[2]=((C_word*)t0)[2],a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  token-type");
f_2745(t3,t1);}

/* k3727 in k3691 in k3681 in k3675 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3729(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4433(((C_word*)t0)[3],t1,((C_word*)t0)[2]);}

/* k3697 in k3691 in k3681 in k3675 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3699(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3699,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3706,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3714,a[2]=((C_word*)t0)[2],a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  token-type");
f_2745(t3,((C_word*)t0)[2]);}
else{
C_trace("ChickenBridge.scm: 145  values");
C_values(5,0,((C_word*)t0)[3],C_SCHEME_FALSE,C_SCHEME_FALSE,((C_word*)((C_word*)t0)[4])[1]);}}

/* k3712 in k3697 in k3691 in k3681 in k3675 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3714(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3714,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3718,a[2]=((C_word*)t0)[2],a[3]=t1,a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  token-string");
f_2763(t2,((C_word*)t0)[2]);}

/* k3716 in k3712 in k3697 in k3691 in k3681 in k3675 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3718(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3718,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3722,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  token-position");
f_2781(t2,((C_word*)t0)[2]);}

/* k3720 in k3716 in k3712 in k3697 in k3691 in k3681 in k3675 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3722(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3142(((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k3704 in k3697 in k3691 in k3681 in k3675 in k3660 in k3657 in k3654 in parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3706(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
t2=((C_word*)((C_word*)t0)[3])[1];
t3=(C_word)C_i_cdr(t2);
C_trace("ChickenBridge.scm: 145  values");
C_values(5,0,((C_word*)t0)[2],C_SCHEME_TRUE,t1,t3);}

/* simple-unit-emitter in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3548(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3548,NULL,2,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3550,a[2]=t2,a[3]=lf[194],tmp=(C_word)a,a+=4,tmp));}

/* f_3550 in simple-unit-emitter in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3550(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[9],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_3550,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3554,a[2]=((C_word*)t0)[2],a[3]=t1,a[4]=t4,a[5]=t3,tmp=(C_word)a,a+=6,tmp);
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3598,a[2]=t5,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3181(t6,t2);}

/* k3596 */
static void C_ccall f_3598(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  append");
t2=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[2],t1,C_SCHEME_END_OF_LIST);}

/* k3552 */
static void C_ccall f_3554(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3554,2,t0,t1);}
t2=t1;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=((C_word*)t3)[1];
t5=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_3557,a[2]=t3,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=t4,tmp=(C_word)a,a+=7,tmp);
if(C_truep(((C_word*)t0)[2])){
t6=(C_word)C_i_set_car(((C_word*)t3)[1],((C_word*)t0)[2]);
t7=(C_word)C_i_cdr(((C_word*)t3)[1]);
t8=C_set_block_item(t3,0,t7);
t9=t5;
f_3557(t9,t8);}
else{
t6=t5;
f_3557(t6,C_SCHEME_UNDEFINED);}}

/* k3555 in k3552 */
static void C_fcall f_3557(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3557,NULL,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_3562,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=t3,a[5]=((C_word*)t0)[6],a[6]=lf[192],tmp=(C_word)a,a+=7,tmp));
t5=((C_word*)t3)[1];
f_3562(t5,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1]);}

/* do477 in k3555 in k3552 */
static void C_fcall f_3562(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3562,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,((C_word*)t0)[5]);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3583,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t3,t4,((C_word*)t0)[3],((C_word*)t0)[2]);}}

/* k3581 in do477 in k3555 in k3552 */
static void C_ccall f_3583(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
t2=(C_word)C_i_set_car(((C_word*)t0)[4],t1);
t3=(C_word)C_i_cdr(((C_word*)t0)[4]);
t4=((C_word*)((C_word*)t0)[3])[1];
f_3562(t4,((C_word*)t0)[2],t3);}

/* simple-unit-parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3540(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3540,NULL,2,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3542,a[2]=t2,a[3]=lf[189],tmp=(C_word)a,a+=4,tmp));}

/* f_3542 in simple-unit-parser in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3542(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word *a;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_3542,4,t0,t1,t2,t3);}
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3142(t1,((C_word*)t0)[2],t2,C_SCHEME_FALSE);}

/* emit-list in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3332(C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3332,NULL,4,t1,t2,t3,t4);}
if(C_truep((C_word)C_i_nullp(t2))){
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,C_SCHEME_END_OF_LIST);}
else{
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3349,a[2]=t4,a[3]=t3,a[4]=t2,a[5]=t1,tmp=(C_word)a,a+=6,tmp);
t6=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  emit");
f_3299(t5,t6,t3,t4);}}

/* k3347 in emit-list in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3349(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3349,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3353,a[2]=t1,a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t3=(C_word)C_i_cdr(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 145  emit-list");
f_3332(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k3351 in k3347 in emit-list in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3353(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3353,2,t0,t1);}
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[2],t1));}

/* emit in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3299(C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3299,NULL,4,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3306,a[2]=t4,a[3]=t3,a[4]=t2,a[5]=t1,tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  token-unit?");
f_3211(t5,t2);}

/* k3304 in emit in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3306(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[14],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3306,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[5];
t3=((C_word*)t0)[4];
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3377,a[2]=t3,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-type");
f_3163(t4,t3);}
else{
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3315,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
t3=((C_word*)t0)[4];
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3250,a[2]=t3,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit?");
f_3148(t4,t3);}}

/* k3248 in k3304 in emit in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3250(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3250,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3257,a[2]=((C_word*)t0)[3],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-type");
f_3163(t2,((C_word*)t0)[2]);}
else{
t2=((C_word*)t0)[3];
f_3315(2,t2,C_SCHEME_FALSE);}}

/* k3255 in k3248 in k3304 in emit in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3257(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  SalRuleType?");
f_4421(((C_word*)t0)[2],t1);}

/* k3313 in k3304 in emit in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3315(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3315,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[5];
t3=((C_word*)t0)[4];
t4=((C_word*)t0)[3];
t5=((C_word*)t0)[2];
t6=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3515,a[2]=t5,a[3]=t4,a[4]=t3,a[5]=t2,tmp=(C_word)a,a+=6,tmp);
t7=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3538,a[2]=t6,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-type");
f_3163(t7,t3);}
else{
if(C_truep((C_word)C_i_listp(((C_word*)t0)[4]))){
C_trace("ChickenBridge.scm: 145  emit-list");
f_3332(((C_word*)t0)[5],((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2]);}
else{
C_trace("ChickenBridge.scm: 145  error");
t2=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[5],lf[184],((C_word*)t0)[4]);}}}

/* k3536 in k3313 in k3304 in emit in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3538(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  get-rule");
f_2949(((C_word*)t0)[2],t1,C_SCHEME_END_OF_LIST);}

/* k3513 in k3313 in k3304 in emit in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3515(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3515,2,t0,t1);}
t2=(C_word)C_i_check_structure(t1,lf[122]);
t3=(C_word)C_i_block_ref(t1,C_fix(5));
if(C_truep(t3)){
C_trace("ChickenBridge.scm: 145  meth");
t4=t3;
((C_proc5)C_retrieve_proc(t4))(5,t4,((C_word*)t0)[5],((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2]);}
else{
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3531,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[5],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3181(t4,((C_word*)t0)[4]);}}

/* k3529 in k3513 in k3313 in k3304 in emit in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3531(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  emit");
f_3299(((C_word*)t0)[4],t1,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k3375 in k3304 in emit in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3377(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3377,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3380,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3181(t2,((C_word*)t0)[2]);}

/* k3378 in k3375 in k3304 in emit in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3380(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3380,2,t0,t1);}
t2=((C_word*)t0)[4];
t3=(C_word)C_i_lessp(C_fix(2560),t2);
t4=(C_truep(t3)?(C_word)C_i_lessp(t2,C_fix(3584)):C_SCHEME_FALSE);
if(C_truep(t4)){
C_trace("ChickenBridge.scm: 145  string->number");
C_string_to_number(3,0,((C_word*)t0)[3],t1);}
else{
t5=((C_word*)t0)[4];
t6=(C_word)C_i_lessp(C_fix(13056),t5);
t7=(C_truep(t6)?(C_word)C_i_lessp(t5,C_fix(23808)):C_SCHEME_FALSE);
if(C_truep(t7)){
C_trace("ChickenBridge.scm: 145  string->symbol");
t8=*((C_word*)lf[173]+1);
((C_proc3)C_retrieve_proc(t8))(3,t8,((C_word*)t0)[3],t1);}
else{
t8=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3404,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[4],a[4]=t1,a[5]=((C_word*)t0)[3],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  SalOpType?");
f_4319(t8,((C_word*)t0)[4]);}}}

/* k3402 in k3378 in k3375 in k3304 in emit in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3404(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[14],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3404,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3410,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4433(t2,((C_word*)t0)[3],C_fix(7941));}
else{
t2=((C_word*)t0)[3];
t3=(C_word)C_i_lessp(C_fix(4096),t2);
t4=(C_truep(t3)?(C_word)C_i_lessp(t2,C_fix(4864)):C_SCHEME_FALSE);
if(C_truep(t4)){
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3455,a[2]=((C_word*)t0)[5],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4433(t5,((C_word*)t0)[3],C_fix(4352));}
else{
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3461,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4433(t5,((C_word*)t0)[3],C_fix(2304));}}}

/* k3459 in k3402 in k3378 in k3375 in k3304 in emit in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3461(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3461,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[5];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,((C_word*)t0)[4]);}
else{
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3467,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4433(t2,((C_word*)t0)[2],C_fix(6144));}}

/* k3465 in k3459 in k3402 in k3378 in k3375 in k3304 in emit in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3467(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3467,2,t0,t1);}
if(C_truep(t1)){
C_trace("ChickenBridge.scm: 145  string->keyword");
t2=C_retrieve(lf[179]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[5],((C_word*)t0)[4]);}
else{
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3476,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4433(t2,((C_word*)t0)[2],C_fix(3840));}}

/* k3474 in k3465 in k3459 in k3402 in k3378 in k3375 in k3304 in emit in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3476(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3476,2,t0,t1);}
if(C_truep(t1)){
C_trace("ChickenBridge.scm: 145  string->keyword");
t2=C_retrieve(lf[179]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[5],((C_word*)t0)[4]);}
else{
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3485,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4433(t2,((C_word*)t0)[2],C_fix(6400));}}

/* k3483 in k3474 in k3465 in k3459 in k3402 in k3378 in k3375 in k3304 in emit in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3485(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3485,2,t0,t1);}
if(C_truep(t1)){
C_trace("ChickenBridge.scm: 145  string->symbol");
t2=*((C_word*)lf[173]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[5],((C_word*)t0)[4]);}
else{
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3494,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4433(t2,((C_word*)t0)[2],C_fix(25344));}}

/* k3492 in k3483 in k3474 in k3465 in k3459 in k3402 in k3378 in k3375 in k3304 in emit in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3494(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3494,2,t0,t1);}
if(C_truep(t1)){
C_trace("ChickenBridge.scm: 145  error");
t2=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[5],lf[180],((C_word*)t0)[4]);}
else{
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3503,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[5],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4433(t2,((C_word*)t0)[2],C_fix(25088));}}

/* k3501 in k3492 in k3483 in k3474 in k3465 in k3459 in k3402 in k3378 in k3375 in k3304 in emit in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3503(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(C_truep(t1)){
C_trace("ChickenBridge.scm: 145  string->symbol");
t2=*((C_word*)lf[173]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[4],((C_word*)t0)[3]);}
else{
C_trace("ChickenBridge.scm: 145  error");
t2=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[4],lf[181],((C_word*)t0)[2]);}}

/* k3453 in k3402 in k3378 in k3375 in k3304 in emit in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3455(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_truep(t1)?C_SCHEME_TRUE:C_SCHEME_FALSE));}

/* k3408 in k3402 in k3378 in k3375 in k3304 in emit in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3410(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3410,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,lf[61]);}
else{
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3416,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4433(t2,((C_word*)t0)[2],C_fix(8199));}}

/* k3414 in k3408 in k3402 in k3378 in k3375 in k3304 in emit in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3416(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3416,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,lf[174]);}
else{
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3422,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4433(t2,((C_word*)t0)[2],C_fix(10244));}}

/* k3420 in k3414 in k3408 in k3402 in k3378 in k3375 in k3304 in emit in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3422(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3422,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,lf[175]);}
else{
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3428,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4433(t2,((C_word*)t0)[2],C_fix(8450));}}

/* k3426 in k3420 in k3414 in k3408 in k3402 in k3378 in k3375 in k3304 in emit in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3428(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3428,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,lf[176]);}
else{
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3434,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4433(t2,((C_word*)t0)[2],C_fix(8705));}}

/* k3432 in k3426 in k3420 in k3414 in k3408 in k3402 in k3378 in k3375 in k3304 in emit in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3434(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3434,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,lf[177]);}
else{
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3440,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4433(t2,((C_word*)t0)[2],C_fix(8963));}}

/* k3438 in k3432 in k3426 in k3420 in k3414 in k3408 in k3402 in k3378 in k3375 in k3304 in emit in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3440(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(C_truep(t1)){
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,lf[178]);}
else{
C_trace("ChickenBridge.scm: 145  string->symbol");
t2=*((C_word*)lf[173]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}}

/* set-emit-info! in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3281(C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3281,NULL,4,t1,t2,t3,t4);}
t5=(C_word)C_i_assoc(t2,t4);
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3288,a[2]=t3,a[3]=t5,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
if(C_truep(t5)){
t7=t6;
f_3288(2,t7,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 145  error");
t7=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t7))(4,t7,t6,lf[170],t2);}}

/* k3286 in set-emit-info! in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3288(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_i_set_cdr(((C_word*)t0)[3],((C_word*)t0)[2]));}

/* add-emit-info in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3271(C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3271,NULL,4,t1,t2,t3,t4);}
t5=(C_word)C_a_i_cons(&a,2,t2,t3);
t6=t1;
((C_proc2)(void*)(*((C_word*)t6+1)))(2,t6,(C_word)C_a_i_cons(&a,2,t5,t4));}

/* get-emit-info in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3259(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3259,NULL,3,t1,t2,t3);}
t4=(C_word)C_i_assoc(t2,t3);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_truep(t4)?(C_word)C_i_cdr(t4):C_SCHEME_FALSE));}

/* token-unit-type=? in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3227(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3227,NULL,3,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3234,a[2]=t2,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  token-unit?");
f_3211(t4,t2);}

/* k3232 in token-unit-type=? in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3234(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3234,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3241,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-type");
f_3163(t2,((C_word*)t0)[2]);}
else{
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}}

/* k3239 in k3232 in token-unit-type=? in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3241(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4433(((C_word*)t0)[3],t1,((C_word*)t0)[2]);}

/* token-unit? in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3211(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3211,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3218,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit?");
f_3148(t3,t2);}

/* k3216 in token-unit? in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3218(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3218,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3225,a[2]=((C_word*)t0)[3],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-type");
f_3163(t2,((C_word*)t0)[2]);}
else{
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}}

/* k3223 in k3216 in token-unit? in k3207 in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3225(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  SalTokenType?");
f_4271(((C_word*)t0)[2],t1);}

/* parse-unit-position in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3199(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3199,NULL,2,t1,t2);}
t3=(C_word)C_i_check_structure(t2,lf[149]);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_block_ref(t2,C_fix(3)));}

/* parse-unit-parsed in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3181(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3181,NULL,2,t1,t2);}
t3=(C_word)C_i_check_structure(t2,lf[149]);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_block_ref(t2,C_fix(2)));}

/* parse-unit-type in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3163(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3163,NULL,2,t1,t2);}
t3=(C_word)C_i_check_structure(t2,lf[149]);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_block_ref(t2,C_fix(1)));}

/* parse-unit? in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3148(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3148,NULL,2,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_i_structurep(t2,lf[149]));}

/* make-parse-unit in k3138 in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3142(C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3142,NULL,4,t1,t2,t3,t4);}
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)C_a_i_record(&a,4,lf[149],t2,t3,t4));}

/* parse-error-position in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3130(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3130,NULL,2,t1,t2);}
t3=(C_word)C_i_check_structure(t2,lf[142]);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_block_ref(t2,C_fix(2)));}

/* parse-error-string in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3112(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3112,NULL,2,t1,t2);}
t3=(C_word)C_i_check_structure(t2,lf[142]);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_block_ref(t2,C_fix(1)));}

/* make-parse-error in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3091(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3091,NULL,3,t1,t2,t3);}
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_a_i_record(&a,3,lf[142],t2,t3));}

/* pattern-zero-or-more? in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3059(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3059,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3066,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  pattern-clause?");
f_2973(t3,t2);}

/* k3064 in pattern-zero-or-more? in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3066(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_eqp(t2,lf[139]));}
else{
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}}

/* pattern-sub in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_3001(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3001,NULL,3,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3009,a[2]=t3,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  pattern-subs");
f_2985(t4,t2);}

/* k3007 in pattern-sub in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_3009(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_i_list_ref(t1,((C_word*)t0)[2]));}

/* pattern-nsubs in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_2991(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2991,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2999,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  pattern-subs");
f_2985(t3,t2);}

/* k2997 in pattern-nsubs in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2999(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_i_length(t1));}

/* pattern-subs in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_2985(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2985,NULL,2,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_i_cdr(t2));}

/* pattern-clause? in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_2973(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2973,NULL,2,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_i_pairp(t2));}

/* get-rule in k2945 in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_2949(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2949,NULL,3,t1,t2,t3);}
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("ChickenBridge.scm: 145  hash-table-ref");
t4=*((C_word*)lf[127]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t1,C_retrieve2(lf[120],"*rules*"),t2);}
else{
C_trace("ChickenBridge.scm: 145  hash-table-ref/default");
t4=C_retrieve(lf[128]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t1,C_retrieve2(lf[120],"*rules*"),t3);}}

/* rule-name in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_2865(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2865,NULL,2,t1,t2);}
t3=(C_word)C_i_check_structure(t2,lf[122]);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_block_ref(t2,C_fix(1)));}

/* make-rule in k2840 in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_2844(C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
C_word tmp;
C_word t7;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2844,NULL,6,t1,t2,t3,t4,t5,t6);}
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)C_a_i_record(&a,6,lf[122],t2,t3,t4,t5,t6));}

/* null-tokens? in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_2834(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2834,NULL,2,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_i_nullp(t2));}

/* first-token in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_2822(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2822,NULL,2,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_i_car(t2));}

/* list->token in k2789 in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2793(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2793,3,t0,t1,t2);}
t3=(C_word)C_i_car(t2);
t4=(C_word)C_eqp(t3,lf[114]);
if(C_truep(t4)){
t5=(C_word)C_i_cdr(t2);
C_apply(4,0,t1,lf[104],t5);}
else{
C_apply(4,0,t1,lf[104],t2);}}

/* token-position in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_2781(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2781,NULL,2,t1,t2);}
t3=(C_word)C_i_check_structure(t2,lf[105]);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_block_ref(t2,C_fix(3)));}

/* token-string in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_2763(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2763,NULL,2,t1,t2);}
t3=(C_word)C_i_check_structure(t2,lf[105]);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_block_ref(t2,C_fix(2)));}

/* token-type in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_2745(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2745,NULL,2,t1,t2);}
t3=(C_word)C_i_check_structure(t2,lf[105]);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_block_ref(t2,C_fix(1)));}

/* make-token in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2724(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_2724,5,t0,t1,t2,t3,t4);}
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)C_a_i_record(&a,4,lf[105],t2,t3,t4));}

/* ranpink in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2718(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2718,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub145(t2));}

/* ranbrown in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2712(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2712,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub148(t2));}

/* rangamma in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2693(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2rv,(void*)f_2693r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_2693r(t0,t1,t2);}}

static void C_ccall f_2693r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
if(C_truep((C_word)C_vemptyp(t2))){
C_trace("ChickenBridge.scm: 143  tb:rangamma");
f_1961(t1,C_fix(1));}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
C_trace("ChickenBridge.scm: 143  tb:rangamma");
f_1961(t1,t3);}}

/* ranpoisson in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2674(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2rv,(void*)f_2674r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_2674r(t0,t1,t2);}}

static void C_ccall f_2674r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
if(C_truep((C_word)C_i_nullp(C_retrieve(lf[96])))){
C_trace("ChickenBridge.scm: 143  tb:ranpoisson");
f_1971(t1,C_fix(1));}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
C_trace("ChickenBridge.scm: 143  tb:ranpoisson");
f_1971(t1,t3);}}

/* rancauchy in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2668(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2668,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub138(t2));}

/* rangauss in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2628(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2r,(void*)f_2628r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_2628r(t0,t1,t2);}}

static void C_ccall f_2628r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 143  tb:rangauss");
f_1932(t1,C_fix(1),C_fix(0));}
else{
t3=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 143  tb:rangauss");
f_1932(t1,t4,C_fix(0));}
else{
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cdr(t2);
C_trace("ChickenBridge.scm: 143  tb:rangauss");
f_1932(t1,t4,t5);}}}

/* ranexp in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2609(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2rv,(void*)f_2609r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_2609r(t0,t1,t2);}}

static void C_ccall f_2609r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
if(C_truep((C_word)C_vemptyp(t2))){
C_trace("ChickenBridge.scm: 143  tb:ranexp");
f_1943(t1,C_fix(1));}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
C_trace("ChickenBridge.scm: 143  tb:ranexp");
f_1943(t1,t3);}}

/* ranbeta in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2565(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2r,(void*)f_2565r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_2565r(t0,t1,t2);}}

static void C_ccall f_2565r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 143  tb:ranbeta");
f_1950(t1,lf[86],lf[87]);}
else{
t3=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 143  tb:ranbeta");
f_1950(t1,t4,t5);}
else{
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cadr(t2);
C_trace("ChickenBridge.scm: 143  tb:ranbeta");
f_1950(t1,t4,t5);}}}

/* ranmiddle in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2559(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2559,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub111(t2));}

/* ranhigh in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2553(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2553,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub108(t2));}

/* ranlow in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2547(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2547,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub105(t2));}

/* pick in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2541(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2r,(void*)f_2541r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_2541r(t0,t1,t2);}}

static void C_ccall f_2541r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_trace("ChickenBridge.scm: 143  pickl");
t3=*((C_word*)lf[74]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,t2);}

/* pickl in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2518(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2518,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 143  error");
t3=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t1,lf[75],t2);}
else{
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2535,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
t4=(C_word)C_i_length(t2);
C_trace("ChickenBridge.scm: 143  tb:rani");
f_1887(t3,t4);}}

/* k2533 in pickl in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2535(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_i_list_ref(((C_word*)t0)[2],t1));}

/* odds in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2460(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+14)){
C_save_and_reclaim((void*)tr3r,(void*)f_2460r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_2460r(t0,t1,t2,t3);}}

static void C_ccall f_2460r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word *a=C_alloc(14);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2477,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 143  tb:ranf");
f_1894(t4,lf[70]);}
else{
t4=(C_word)C_i_cdr(t3);
if(C_truep((C_word)C_i_nullp(t4))){
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2496,a[2]=t3,a[3]=t1,a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 143  tb:ranf");
f_1894(t5,lf[71]);}
else{
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2512,a[2]=t3,a[3]=t1,a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 143  tb:ranf");
f_1894(t5,lf[72]);}}}

/* k2510 in odds in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2512(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_lessp(t1,((C_word*)t0)[4]);
t3=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_truep(t2)?(C_word)C_i_car(((C_word*)t0)[2]):(C_word)C_i_cadr(((C_word*)t0)[2])));}

/* k2494 in odds in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2496(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_lessp(t1,((C_word*)t0)[4]);
t3=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_truep(t2)?(C_word)C_i_car(((C_word*)t0)[2]):C_SCHEME_FALSE));}

/* k2475 in odds in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2477(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_lessp(t1,((C_word*)t0)[3]);
t3=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_truep(t2)?C_SCHEME_TRUE:C_SCHEME_FALSE));}

/* ran in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2372(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+4)){
C_save_and_reclaim((void*)tr2r,(void*)f_2372r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_2372r(t0,t1,t2);}}

static void C_ccall f_2372r(C_word t0,C_word t1,C_word t2){
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
C_trace("ChickenBridge.scm: 143  tb:ranf");
f_1894(t1,lf[67]);}
else{
t3=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_fixnump(t4))){
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 143  tb:rani");
f_1887(t1,t5);}
else{
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 143  tb:ranf");
f_1894(t1,t5);}}
else{
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2418,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_fixnump(t5))){
t6=(C_word)C_i_cadr(t2);
t7=t4;
f_2418(t7,(C_word)C_fixnump(t6));}
else{
t6=t4;
f_2418(t6,C_SCHEME_FALSE);}}}}

/* k2416 in ran in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_2418(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_2418,NULL,2,t0,t1);}
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

/* ran-set! in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2366(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2366,3,t0,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub80(C_SCHEME_UNDEFINED,t2));}

/* steps in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2307(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+12)){
C_save_and_reclaim((void*)tr4rv,(void*)f_2307r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest_vector(a,C_rest_count(0));
f_2307r(t0,t1,t2,t3,t4);}}

static void C_ccall f_2307r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
t9=C_set_block_item(t8,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_2320,a[2]=t5,a[3]=t8,a[4]=t4,a[5]=t2,a[6]=lf[62],tmp=(C_word)a,a+=7,tmp));
t10=((C_word*)t8)[1];
f_2320(t10,t1,C_fix(0),t3,t6,t5);}

/* do216 in steps in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_2320(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
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
C_save_and_reclaim((void*)trf_2320,NULL,6,t0,t1,t2,t3,t4,t5);}
t6=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
if(C_truep((C_word)C_i_lessp(t2,((C_word*)t0)[5]))){
t8=(C_word)C_a_i_list(&a,1,((C_word*)t6)[1]);
t9=(C_word)C_i_set_cdr(((C_word*)t7)[1],t8);
t10=(C_word)C_i_cdr(((C_word*)t7)[1]);
t11=C_set_block_item(t7,0,t10);
t12=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_2356,a[2]=t7,a[3]=t4,a[4]=t1,a[5]=((C_word*)t0)[3],a[6]=t2,a[7]=t6,a[8]=((C_word*)t0)[4],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 143  modulo");
t13=*((C_word*)lf[61]+1);
((C_proc4)C_retrieve_proc(t13))(4,t13,t12,t2,t4);}
else{
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,(C_word)C_i_cdr(((C_word*)t0)[2]));}}

/* k2354 in do216 in steps in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2356(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2356,2,t0,t1);}
t2=(C_word)C_i_vector_ref(((C_word*)t0)[8],t1);
t3=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[7])[1],t2);
t4=C_mutate(((C_word *)((C_word*)t0)[7])+1,t3);
t5=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[6],C_fix(1));
t6=((C_word*)((C_word*)t0)[5])[1];
f_2320(t6,((C_word*)t0)[4],t5,((C_word*)((C_word*)t0)[7])[1],((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1]);}

/* interp in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2301(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr3r,(void*)f_2301r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_2301r(t0,t1,t2,t3);}}

static void C_ccall f_2301r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_trace("ChickenBridge.scm: 143  interpl");
t4=*((C_word*)lf[50]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t1,t2,t3);}

/* interpl in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2206(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+6)){
C_save_and_reclaim((void*)tr4rv,(void*)f_2206r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest_vector(a,C_rest_count(0));
f_2206r(t0,t1,t2,t3,t4);}}

static void C_ccall f_2206r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word *a=C_alloc(6);
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_2210,a[2]=t1,a[3]=t2,a[4]=t3,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("ChickenBridge.scm: 143  error");
t6=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t5,lf[56],t3);}
else{
t6=t5;
f_2210(2,t6,(C_word)C_i_car(t3));}}

/* k2208 in interpl in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2210(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2210,2,t0,t1);}
t2=t1;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_2213,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=t3,tmp=(C_word)a,a+=7,tmp);
t5=(C_word)C_i_cdr(((C_word*)t0)[4]);
if(C_truep((C_word)C_i_nullp(t5))){
C_trace("ChickenBridge.scm: 143  err");
t6=C_retrieve(lf[54]);
((C_proc4)C_retrieve_proc(t6))(4,t6,t4,lf[55],((C_word*)t0)[4]);}
else{
t6=t4;
f_2213(2,t6,(C_word)C_i_cadr(((C_word*)t0)[4]));}}

/* k2211 in k2208 in interpl in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2213(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2213,2,t0,t1);}
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
t13=C_set_block_item(t12,0,(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_2225,a[2]=((C_word*)t0)[4],a[3]=t12,a[4]=t9,a[5]=t7,a[6]=t3,a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[3],a[9]=t5,a[10]=lf[53],tmp=(C_word)a,a+=11,tmp));
t14=((C_word*)t12)[1];
f_2225(t14,((C_word*)t0)[2],t10);}

/* do200 in k2211 in k2208 in interpl in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_2225(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_2225,NULL,3,t0,t1,t2);}
t3=(C_word)C_i_nullp(t2);
t4=(C_truep(t3)?t3:(C_word)C_i_greaterp(((C_word*)((C_word*)t0)[9])[1],((C_word*)t0)[8]));
if(C_truep(t4)){
C_trace("ChickenBridge.scm: 143  tb:rescale");
f_1751(t1,((C_word*)t0)[8],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[9])[1],((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[4]);}
else{
t5=C_mutate(((C_word *)((C_word*)t0)[7])+1,((C_word*)((C_word*)t0)[9])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[6])+1,((C_word*)((C_word*)t0)[5])[1]);
t7=(C_word)C_i_car(t2);
t8=C_mutate(((C_word *)((C_word*)t0)[9])+1,t7);
t9=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2247,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t10=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t10))){
C_trace("ChickenBridge.scm: 143  error");
t11=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t11))(4,t11,t9,lf[52],((C_word*)t0)[2]);}
else{
t11=(C_word)C_i_cadr(t2);
t12=C_mutate(((C_word *)((C_word*)t0)[5])+1,t11);
t13=t9;
f_2247(2,t13,t12);}}}

/* k2245 in do200 in k2211 in k2208 in interpl in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2247(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cddr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_2225(t3,((C_word*)t0)[2],t2);}

/* hertz->keynum in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2200(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2200,3,t0,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub75(t3,t4));}

/* keynum->pc in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2194(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2194,3,t0,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub71(C_SCHEME_UNDEFINED,t3));}

/* keynum->hertz in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2188(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2188,3,t0,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub66(t3,t4));}

/* scaler->cents in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2182(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2182,3,t0,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub62(C_SCHEME_UNDEFINED,t3));}

/* cents->scaler in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2176(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2176,3,t0,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_fixnum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub57(t3,t4));}

/* rhythm->seconds in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2116(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+12)){
C_save_and_reclaim((void*)tr3r,(void*)f_2116r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_2116r(t0,t1,t2,t3);}}

static void C_ccall f_2116r(C_word t0,C_word t1,C_word t2,C_word t3){
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
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2118,a[2]=t2,a[3]=lf[33],tmp=(C_word)a,a+=4,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2123,a[2]=t4,a[3]=lf[35],tmp=(C_word)a,a+=4,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2128,a[2]=t5,a[3]=lf[37],tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("def-tempo173181");
t7=t6;
f_2128(t7,t1);}
else{
t7=(C_word)C_i_car(t3);
t8=(C_word)C_i_cdr(t3);
if(C_truep((C_word)C_i_nullp(t8))){
C_trace("def-beat174179");
t9=t5;
f_2123(t9,t1,t7);}
else{
t9=(C_word)C_i_car(t8);
t10=(C_word)C_i_cdr(t8);
if(C_truep((C_word)C_i_nullp(t10))){
C_trace("body171176");
t11=t4;
f_2118(t11,t1,t7,t9);}
else{
C_trace("##sys#error");
t11=*((C_word*)lf[38]+1);
((C_proc4)(void*)(*((C_word*)t11+1)))(4,t11,t1,lf[0],t10);}}}}

/* def-tempo173 in rhythm->seconds in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_2128(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2128,NULL,2,t0,t1);}
C_trace("def-beat174179");
t2=((C_word*)t0)[2];
f_2123(t2,t1,lf[36]);}

/* def-beat174 in rhythm->seconds in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_2123(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2123,NULL,3,t0,t1,t2);}
C_trace("body171176");
t3=((C_word*)t0)[2];
f_2118(t3,t1,t2,lf[34]);}

/* body171 in rhythm->seconds in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_2118(C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)trf_2118,NULL,4,t0,t1,t2,t3);}
t4=((C_word*)t0)[2];
t5=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t6=(C_word)C_i_foreign_flonum_argumentp(t4);
t7=(C_word)C_i_foreign_flonum_argumentp(t2);
t8=(C_word)C_i_foreign_flonum_argumentp(t3);
t9=t1;
((C_proc2)(void*)(*((C_word*)t9+1)))(2,t9,(C_word)stub50(t5,t6,t7,t8));}

/* decimals in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2097(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr3rv,(void*)f_2097r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest_vector(a,C_rest_count(0));
f_2097r(t0,t1,t2,t3);}}

static void C_ccall f_2097r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
if(C_truep((C_word)C_vemptyp(t3))){
C_trace("ChickenBridge.scm: 143  tb:decimals");
f_1812(t1,t2,C_fix(3));}
else{
t4=(C_word)C_i_vector_ref(t3,C_fix(0));
C_trace("ChickenBridge.scm: 143  tb:decimals");
f_1812(t1,t2,t4);}}

/* quantize in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2091(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_2091,4,t0,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_flonum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub42(t4,t5,t6));}

/* int in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2085(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2085,3,t0,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub30(C_SCHEME_UNDEFINED,t3));}

/* discrete in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2003(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,...){
C_word tmp;
C_word t6;
va_list v;
C_word *a,c2=c;
C_save_rest(t5,c2,6);
if(c<6) C_bad_min_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+4)){
C_save_and_reclaim((void*)tr6r,(void*)f_2003r,6,t0,t1,t2,t3,t4,t5);}
else{
a=C_alloc((c-6)*3);
t6=C_restore_rest(a,C_rest_count(0));
f_2003r(t0,t1,t2,t3,t4,t5,t6);}}

static void C_ccall f_2003r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
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
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2017,a[2]=t5,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_nullp(t6))){
t8=(C_word)C_i_length(t5);
C_trace("ChickenBridge.scm: 143  tb:discrete");
f_1778(t7,t2,t3,t4,C_fix(0),t8,C_fix(1));}
else{
t8=(C_word)C_i_cdr(t6);
if(C_truep((C_word)C_i_nullp(t8))){
t9=(C_word)C_i_car(t6);
C_trace("ChickenBridge.scm: 143  tb:discrete");
f_1778(t7,t2,t3,t4,C_fix(0),t9,C_fix(1));}
else{
t9=(C_word)C_i_car(t6);
t10=(C_word)C_i_cadr(t6);
C_trace("ChickenBridge.scm: 143  tb:discrete");
f_1778(t7,t2,t3,t4,C_fix(0),t9,t10);}}}
else{
t7=(C_word)C_i_cdr(t6);
if(C_truep((C_word)C_i_nullp(t7))){
t8=(C_word)C_i_car(t6);
C_trace("ChickenBridge.scm: 143  tb:discrete");
f_1778(t1,t2,t3,t4,t5,t8,C_fix(1));}
else{
t8=(C_word)C_i_car(t6);
t9=(C_word)C_i_cadr(t6);
C_trace("ChickenBridge.scm: 143  tb:discrete");
f_1778(t1,t2,t3,t4,t5,t8,t9);}}}

/* k2015 in discrete in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_2017(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_i_list_ref(((C_word*)t0)[2],t1));}

/* rescale in k1747 in k1744 in k1741 in k1738 */
static void C_ccall f_1984(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,...){
C_word tmp;
C_word t7;
va_list v;
C_word *a,c2=c;
C_save_rest(t6,c2,7);
if(c<7) C_bad_min_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr7rv,(void*)f_1984r,7,t0,t1,t2,t3,t4,t5,t6);}
else{
a=C_alloc((c-7)*3);
t7=C_restore_rest_vector(a,C_rest_count(0));
f_1984r(t0,t1,t2,t3,t4,t5,t6,t7);}}

static void C_ccall f_1984r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
C_word tmp;
C_word t8;
C_word t9;
if(C_truep((C_word)C_vemptyp(t7))){
C_trace("ChickenBridge.scm: 143  tb:rescale");
f_1751(t1,t2,t3,t4,t5,t6,C_fix(1));}
else{
t8=(C_word)C_i_vector_ref(t7,C_fix(0));
C_trace("ChickenBridge.scm: 143  tb:rescale");
f_1751(t1,t2,t3,t4,t5,t6,t8);}}

/* tb:ranpoisson in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_1971(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1971,NULL,2,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub142(C_SCHEME_UNDEFINED,t3));}

/* tb:rangamma in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_1961(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1961,NULL,2,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub134(t3,t4));}

/* tb:ranbeta in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_1950(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1950,NULL,3,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_flonum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub128(t4,t5,t6));}

/* tb:ranexp in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_1943(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1943,NULL,2,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub122(t3,t4));}

/* tb:rangauss in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_1932(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1932,NULL,3,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_flonum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub116(t4,t5,t6));}

/* tb:ranf in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_1894(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1894,NULL,2,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub88(t3,t4));}

/* tb:rani in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_1887(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1887,NULL,2,t1,t2);}
t3=(C_word)C_i_foreign_fixnum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub84(C_SCHEME_UNDEFINED,t3));}

/* tb:decimals in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_1812(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1812,NULL,3,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_fixnum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub35(t4,t5,t6));}

/* tb:discrete in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_1778(C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
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
C_save_and_reclaim((void*)trf_1778,NULL,7,t1,t2,t3,t4,t5,t6,t7);}
t8=(C_word)C_i_foreign_flonum_argumentp(t2);
t9=(C_word)C_i_foreign_flonum_argumentp(t3);
t10=(C_word)C_i_foreign_flonum_argumentp(t4);
t11=(C_word)C_i_foreign_fixnum_argumentp(t5);
t12=(C_word)C_i_foreign_fixnum_argumentp(t6);
t13=(C_word)C_i_foreign_flonum_argumentp(t7);
t14=t1;
((C_proc2)(void*)(*((C_word*)t14+1)))(2,t14,(C_word)stub21(C_SCHEME_UNDEFINED,t8,t9,t10,t11,t12,t13));}

/* tb:rescale in k1747 in k1744 in k1741 in k1738 */
static void C_fcall f_1751(C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
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
C_save_and_reclaim((void*)trf_1751,NULL,7,t1,t2,t3,t4,t5,t6,t7);}
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
static C_PTABLE_ENTRY ptable[804] = {
{"toplevelChickenBridge.scm",(void*)C_grace_toplevel},
{"f_1740ChickenBridge.scm",(void*)f_1740},
{"f_1743ChickenBridge.scm",(void*)f_1743},
{"f_1746ChickenBridge.scm",(void*)f_1746},
{"f_1749ChickenBridge.scm",(void*)f_1749},
{"f_12106ChickenBridge.scm",(void*)f_12106},
{"f_12114ChickenBridge.scm",(void*)f_12114},
{"f_12118ChickenBridge.scm",(void*)f_12118},
{"f_2791ChickenBridge.scm",(void*)f_2791},
{"f_2842ChickenBridge.scm",(void*)f_2842},
{"f_12096ChickenBridge.scm",(void*)f_12096},
{"f_12104ChickenBridge.scm",(void*)f_12104},
{"f_2947ChickenBridge.scm",(void*)f_2947},
{"f_12082ChickenBridge.scm",(void*)f_12082},
{"f_12090ChickenBridge.scm",(void*)f_12090},
{"f_12094ChickenBridge.scm",(void*)f_12094},
{"f_3140ChickenBridge.scm",(void*)f_3140},
{"f_12056ChickenBridge.scm",(void*)f_12056},
{"f_12060ChickenBridge.scm",(void*)f_12060},
{"f_12066ChickenBridge.scm",(void*)f_12066},
{"f_12077ChickenBridge.scm",(void*)f_12077},
{"f_12073ChickenBridge.scm",(void*)f_12073},
{"f_3209ChickenBridge.scm",(void*)f_3209},
{"f_12034ChickenBridge.scm",(void*)f_12034},
{"f_4454ChickenBridge.scm",(void*)f_4454},
{"f_12014ChickenBridge.scm",(void*)f_12014},
{"f_4457ChickenBridge.scm",(void*)f_4457},
{"f_11974ChickenBridge.scm",(void*)f_11974},
{"f_4460ChickenBridge.scm",(void*)f_4460},
{"f_11880ChickenBridge.scm",(void*)f_11880},
{"f_11884ChickenBridge.scm",(void*)f_11884},
{"f_11887ChickenBridge.scm",(void*)f_11887},
{"f_11905ChickenBridge.scm",(void*)f_11905},
{"f_11908ChickenBridge.scm",(void*)f_11908},
{"f_11939ChickenBridge.scm",(void*)f_11939},
{"f_11911ChickenBridge.scm",(void*)f_11911},
{"f_11917ChickenBridge.scm",(void*)f_11917},
{"f_11870ChickenBridge.scm",(void*)f_11870},
{"f_11864ChickenBridge.scm",(void*)f_11864},
{"f_4463ChickenBridge.scm",(void*)f_4463},
{"f_11772ChickenBridge.scm",(void*)f_11772},
{"f_11774ChickenBridge.scm",(void*)f_11774},
{"f_11778ChickenBridge.scm",(void*)f_11778},
{"f_11781ChickenBridge.scm",(void*)f_11781},
{"f_11784ChickenBridge.scm",(void*)f_11784},
{"f_11824ChickenBridge.scm",(void*)f_11824},
{"f_11816ChickenBridge.scm",(void*)f_11816},
{"f_11787ChickenBridge.scm",(void*)f_11787},
{"f_11790ChickenBridge.scm",(void*)f_11790},
{"f_11793ChickenBridge.scm",(void*)f_11793},
{"f_11764ChickenBridge.scm",(void*)f_11764},
{"f_4466ChickenBridge.scm",(void*)f_4466},
{"f_11736ChickenBridge.scm",(void*)f_11736},
{"f_4469ChickenBridge.scm",(void*)f_4469},
{"f_11700ChickenBridge.scm",(void*)f_11700},
{"f_11712ChickenBridge.scm",(void*)f_11712},
{"f_11708ChickenBridge.scm",(void*)f_11708},
{"f_11682ChickenBridge.scm",(void*)f_11682},
{"f_11676ChickenBridge.scm",(void*)f_11676},
{"f_4472ChickenBridge.scm",(void*)f_4472},
{"f_11590ChickenBridge.scm",(void*)f_11590},
{"f_11594ChickenBridge.scm",(void*)f_11594},
{"f_11597ChickenBridge.scm",(void*)f_11597},
{"f_11600ChickenBridge.scm",(void*)f_11600},
{"f_11613ChickenBridge.scm",(void*)f_11613},
{"f_11559ChickenBridge.scm",(void*)f_11559},
{"f_11563ChickenBridge.scm",(void*)f_11563},
{"f_11578ChickenBridge.scm",(void*)f_11578},
{"f_11553ChickenBridge.scm",(void*)f_11553},
{"f_4475ChickenBridge.scm",(void*)f_4475},
{"f_11439ChickenBridge.scm",(void*)f_11439},
{"f_11455ChickenBridge.scm",(void*)f_11455},
{"f_11466ChickenBridge.scm",(void*)f_11466},
{"f_11433ChickenBridge.scm",(void*)f_11433},
{"f_4531ChickenBridge.scm",(void*)f_4531},
{"f_11300ChickenBridge.scm",(void*)f_11300},
{"f_11323ChickenBridge.scm",(void*)f_11323},
{"f_11320ChickenBridge.scm",(void*)f_11320},
{"f_11294ChickenBridge.scm",(void*)f_11294},
{"f_4534ChickenBridge.scm",(void*)f_4534},
{"f_11148ChickenBridge.scm",(void*)f_11148},
{"f_11166ChickenBridge.scm",(void*)f_11166},
{"f_11175ChickenBridge.scm",(void*)f_11175},
{"f_11142ChickenBridge.scm",(void*)f_11142},
{"f_4537ChickenBridge.scm",(void*)f_4537},
{"f_11095ChickenBridge.scm",(void*)f_11095},
{"f_11099ChickenBridge.scm",(void*)f_11099},
{"f_11102ChickenBridge.scm",(void*)f_11102},
{"f_11118ChickenBridge.scm",(void*)f_11118},
{"f_11077ChickenBridge.scm",(void*)f_11077},
{"f_11071ChickenBridge.scm",(void*)f_11071},
{"f_4540ChickenBridge.scm",(void*)f_4540},
{"f_10995ChickenBridge.scm",(void*)f_10995},
{"f_4679ChickenBridge.scm",(void*)f_4679},
{"f_10921ChickenBridge.scm",(void*)f_10921},
{"f_10928ChickenBridge.scm",(void*)f_10928},
{"f_10915ChickenBridge.scm",(void*)f_10915},
{"f_4682ChickenBridge.scm",(void*)f_4682},
{"f_10811ChickenBridge.scm",(void*)f_10811},
{"f_10819ChickenBridge.scm",(void*)f_10819},
{"f_10785ChickenBridge.scm",(void*)f_10785},
{"f_10802ChickenBridge.scm",(void*)f_10802},
{"f_10793ChickenBridge.scm",(void*)f_10793},
{"f_10779ChickenBridge.scm",(void*)f_10779},
{"f_4685ChickenBridge.scm",(void*)f_4685},
{"f_10735ChickenBridge.scm",(void*)f_10735},
{"f_4688ChickenBridge.scm",(void*)f_4688},
{"f_10653ChickenBridge.scm",(void*)f_10653},
{"f_10664ChickenBridge.scm",(void*)f_10664},
{"f_10666ChickenBridge.scm",(void*)f_10666},
{"f_10695ChickenBridge.scm",(void*)f_10695},
{"f_10631ChickenBridge.scm",(void*)f_10631},
{"f_10647ChickenBridge.scm",(void*)f_10647},
{"f_10625ChickenBridge.scm",(void*)f_10625},
{"f_4691ChickenBridge.scm",(void*)f_4691},
{"f_10549ChickenBridge.scm",(void*)f_10549},
{"f_10553ChickenBridge.scm",(void*)f_10553},
{"f_10585ChickenBridge.scm",(void*)f_10585},
{"f_10566ChickenBridge.scm",(void*)f_10566},
{"f_10570ChickenBridge.scm",(void*)f_10570},
{"f_10522ChickenBridge.scm",(void*)f_10522},
{"f_10526ChickenBridge.scm",(void*)f_10526},
{"f_10516ChickenBridge.scm",(void*)f_10516},
{"f_4694ChickenBridge.scm",(void*)f_4694},
{"f_10384ChickenBridge.scm",(void*)f_10384},
{"f_10424ChickenBridge.scm",(void*)f_10424},
{"f_10388ChickenBridge.scm",(void*)f_10388},
{"f_10404ChickenBridge.scm",(void*)f_10404},
{"f_10416ChickenBridge.scm",(void*)f_10416},
{"f_10420ChickenBridge.scm",(void*)f_10420},
{"f_10412ChickenBridge.scm",(void*)f_10412},
{"f_10323ChickenBridge.scm",(void*)f_10323},
{"f_10370ChickenBridge.scm",(void*)f_10370},
{"f_10330ChickenBridge.scm",(void*)f_10330},
{"f_10341ChickenBridge.scm",(void*)f_10341},
{"f_10317ChickenBridge.scm",(void*)f_10317},
{"f_4697ChickenBridge.scm",(void*)f_4697},
{"f_10297ChickenBridge.scm",(void*)f_10297},
{"f_10291ChickenBridge.scm",(void*)f_10291},
{"f_4700ChickenBridge.scm",(void*)f_4700},
{"f_10271ChickenBridge.scm",(void*)f_10271},
{"f_10275ChickenBridge.scm",(void*)f_10275},
{"f_10263ChickenBridge.scm",(void*)f_10263},
{"f_4703ChickenBridge.scm",(void*)f_4703},
{"f_10243ChickenBridge.scm",(void*)f_10243},
{"f_10247ChickenBridge.scm",(void*)f_10247},
{"f_10235ChickenBridge.scm",(void*)f_10235},
{"f_4706ChickenBridge.scm",(void*)f_4706},
{"f_10215ChickenBridge.scm",(void*)f_10215},
{"f_10219ChickenBridge.scm",(void*)f_10219},
{"f_10207ChickenBridge.scm",(void*)f_10207},
{"f_4709ChickenBridge.scm",(void*)f_4709},
{"f_10187ChickenBridge.scm",(void*)f_10187},
{"f_10191ChickenBridge.scm",(void*)f_10191},
{"f_10179ChickenBridge.scm",(void*)f_10179},
{"f_4712ChickenBridge.scm",(void*)f_4712},
{"f_10078ChickenBridge.scm",(void*)f_10078},
{"f_10048ChickenBridge.scm",(void*)f_10048},
{"f_10072ChickenBridge.scm",(void*)f_10072},
{"f_10042ChickenBridge.scm",(void*)f_10042},
{"f_4715ChickenBridge.scm",(void*)f_4715},
{"f_9992ChickenBridge.scm",(void*)f_9992},
{"f_9994ChickenBridge.scm",(void*)f_9994},
{"f_9998ChickenBridge.scm",(void*)f_9998},
{"f_10026ChickenBridge.scm",(void*)f_10026},
{"f_10018ChickenBridge.scm",(void*)f_10018},
{"f_10014ChickenBridge.scm",(void*)f_10014},
{"f_10001ChickenBridge.scm",(void*)f_10001},
{"f_9984ChickenBridge.scm",(void*)f_9984},
{"f_4718ChickenBridge.scm",(void*)f_4718},
{"f_9931ChickenBridge.scm",(void*)f_9931},
{"f_9933ChickenBridge.scm",(void*)f_9933},
{"f_9937ChickenBridge.scm",(void*)f_9937},
{"f_9968ChickenBridge.scm",(void*)f_9968},
{"f_9960ChickenBridge.scm",(void*)f_9960},
{"f_9956ChickenBridge.scm",(void*)f_9956},
{"f_9940ChickenBridge.scm",(void*)f_9940},
{"f_9943ChickenBridge.scm",(void*)f_9943},
{"f_9923ChickenBridge.scm",(void*)f_9923},
{"f_4721ChickenBridge.scm",(void*)f_4721},
{"f_9873ChickenBridge.scm",(void*)f_9873},
{"f_9887ChickenBridge.scm",(void*)f_9887},
{"f_9879ChickenBridge.scm",(void*)f_9879},
{"f_9838ChickenBridge.scm",(void*)f_9838},
{"f_9871ChickenBridge.scm",(void*)f_9871},
{"f_9832ChickenBridge.scm",(void*)f_9832},
{"f_4724ChickenBridge.scm",(void*)f_4724},
{"f_9779ChickenBridge.scm",(void*)f_9779},
{"f_9783ChickenBridge.scm",(void*)f_9783},
{"f_9796ChickenBridge.scm",(void*)f_9796},
{"f_9788ChickenBridge.scm",(void*)f_9788},
{"f_9736ChickenBridge.scm",(void*)f_9736},
{"f_9769ChickenBridge.scm",(void*)f_9769},
{"f_9730ChickenBridge.scm",(void*)f_9730},
{"f_4727ChickenBridge.scm",(void*)f_4727},
{"f_9650ChickenBridge.scm",(void*)f_9650},
{"f_9644ChickenBridge.scm",(void*)f_9644},
{"f_4730ChickenBridge.scm",(void*)f_4730},
{"f_9413ChickenBridge.scm",(void*)f_9413},
{"f_9417ChickenBridge.scm",(void*)f_9417},
{"f_9425ChickenBridge.scm",(void*)f_9425},
{"f_9448ChickenBridge.scm",(void*)f_9448},
{"f_9451ChickenBridge.scm",(void*)f_9451},
{"f_9454ChickenBridge.scm",(void*)f_9454},
{"f_9457ChickenBridge.scm",(void*)f_9457},
{"f_9517ChickenBridge.scm",(void*)f_9517},
{"f_9524ChickenBridge.scm",(void*)f_9524},
{"f_9534ChickenBridge.scm",(void*)f_9534},
{"f_9544ChickenBridge.scm",(void*)f_9544},
{"f_9558ChickenBridge.scm",(void*)f_9558},
{"f_9568ChickenBridge.scm",(void*)f_9568},
{"f_9578ChickenBridge.scm",(void*)f_9578},
{"f_9588ChickenBridge.scm",(void*)f_9588},
{"f_9460ChickenBridge.scm",(void*)f_9460},
{"f_9484ChickenBridge.scm",(void*)f_9484},
{"f_9463ChickenBridge.scm",(void*)f_9463},
{"f_9370ChickenBridge.scm",(void*)f_9370},
{"f_9403ChickenBridge.scm",(void*)f_9403},
{"f_9364ChickenBridge.scm",(void*)f_9364},
{"f_4733ChickenBridge.scm",(void*)f_4733},
{"f_9282ChickenBridge.scm",(void*)f_9282},
{"f_9286ChickenBridge.scm",(void*)f_9286},
{"f_9292ChickenBridge.scm",(void*)f_9292},
{"f_9312ChickenBridge.scm",(void*)f_9312},
{"f_9256ChickenBridge.scm",(void*)f_9256},
{"f_9266ChickenBridge.scm",(void*)f_9266},
{"f_9250ChickenBridge.scm",(void*)f_9250},
{"f_4736ChickenBridge.scm",(void*)f_4736},
{"f_9127ChickenBridge.scm",(void*)f_9127},
{"f_9131ChickenBridge.scm",(void*)f_9131},
{"f_9059ChickenBridge.scm",(void*)f_9059},
{"f_9078ChickenBridge.scm",(void*)f_9078},
{"f_9113ChickenBridge.scm",(void*)f_9113},
{"f_9084ChickenBridge.scm",(void*)f_9084},
{"f_9088ChickenBridge.scm",(void*)f_9088},
{"f_9102ChickenBridge.scm",(void*)f_9102},
{"f_9091ChickenBridge.scm",(void*)f_9091},
{"f_9072ChickenBridge.scm",(void*)f_9072},
{"f_9053ChickenBridge.scm",(void*)f_9053},
{"f_4739ChickenBridge.scm",(void*)f_4739},
{"f_8781ChickenBridge.scm",(void*)f_8781},
{"f_5262ChickenBridge.scm",(void*)f_5262},
{"f_8733ChickenBridge.scm",(void*)f_8733},
{"f_8725ChickenBridge.scm",(void*)f_8725},
{"f_5265ChickenBridge.scm",(void*)f_5265},
{"f_8605ChickenBridge.scm",(void*)f_8605},
{"f_5271ChickenBridge.scm",(void*)f_5271},
{"f_5743ChickenBridge.scm",(void*)f_5743},
{"f_5777ChickenBridge.scm",(void*)f_5777},
{"f_5769ChickenBridge.scm",(void*)f_5769},
{"f_5765ChickenBridge.scm",(void*)f_5765},
{"f_5750ChickenBridge.scm",(void*)f_5750},
{"f_5754ChickenBridge.scm",(void*)f_5754},
{"f_5747ChickenBridge.scm",(void*)f_5747},
{"f_5289ChickenBridge.scm",(void*)f_5289},
{"f_5736ChickenBridge.scm",(void*)f_5736},
{"f_5732ChickenBridge.scm",(void*)f_5732},
{"f_5296ChickenBridge.scm",(void*)f_5296},
{"f_5607ChickenBridge.scm",(void*)f_5607},
{"f_5628ChickenBridge.scm",(void*)f_5628},
{"f_5630ChickenBridge.scm",(void*)f_5630},
{"f_5644ChickenBridge.scm",(void*)f_5644},
{"f_5697ChickenBridge.scm",(void*)f_5697},
{"f_5647ChickenBridge.scm",(void*)f_5647},
{"f_5682ChickenBridge.scm",(void*)f_5682},
{"f_5650ChickenBridge.scm",(void*)f_5650},
{"f_5663ChickenBridge.scm",(void*)f_5663},
{"f_5675ChickenBridge.scm",(void*)f_5675},
{"f_5667ChickenBridge.scm",(void*)f_5667},
{"f_5653ChickenBridge.scm",(void*)f_5653},
{"f_5617ChickenBridge.scm",(void*)f_5617},
{"f_5299ChickenBridge.scm",(void*)f_5299},
{"f_5571ChickenBridge.scm",(void*)f_5571},
{"f_5597ChickenBridge.scm",(void*)f_5597},
{"f_5582ChickenBridge.scm",(void*)f_5582},
{"f_5302ChickenBridge.scm",(void*)f_5302},
{"f_5306ChickenBridge.scm",(void*)f_5306},
{"f_5515ChickenBridge.scm",(void*)f_5515},
{"f_5525ChickenBridge.scm",(void*)f_5525},
{"f_5528ChickenBridge.scm",(void*)f_5528},
{"f_5549ChickenBridge.scm",(void*)f_5549},
{"f_5531ChickenBridge.scm",(void*)f_5531},
{"f_5535ChickenBridge.scm",(void*)f_5535},
{"f_5309ChickenBridge.scm",(void*)f_5309},
{"f_5312ChickenBridge.scm",(void*)f_5312},
{"f_5478ChickenBridge.scm",(void*)f_5478},
{"f_5486ChickenBridge.scm",(void*)f_5486},
{"f_5482ChickenBridge.scm",(void*)f_5482},
{"f_5315ChickenBridge.scm",(void*)f_5315},
{"f_5343ChickenBridge.scm",(void*)f_5343},
{"f_5346ChickenBridge.scm",(void*)f_5346},
{"f_5349ChickenBridge.scm",(void*)f_5349},
{"f_5352ChickenBridge.scm",(void*)f_5352},
{"f_5411ChickenBridge.scm",(void*)f_5411},
{"f_8559ChickenBridge.scm",(void*)f_8559},
{"f_8575ChickenBridge.scm",(void*)f_8575},
{"f_8578ChickenBridge.scm",(void*)f_8578},
{"f_8581ChickenBridge.scm",(void*)f_8581},
{"f_8584ChickenBridge.scm",(void*)f_8584},
{"f_8595ChickenBridge.scm",(void*)f_8595},
{"f_8553ChickenBridge.scm",(void*)f_8553},
{"f_5784ChickenBridge.scm",(void*)f_5784},
{"f_8414ChickenBridge.scm",(void*)f_8414},
{"f_8453ChickenBridge.scm",(void*)f_8453},
{"f_8427ChickenBridge.scm",(void*)f_8427},
{"f_8408ChickenBridge.scm",(void*)f_8408},
{"f_5787ChickenBridge.scm",(void*)f_5787},
{"f_7996ChickenBridge.scm",(void*)f_7996},
{"f_8000ChickenBridge.scm",(void*)f_8000},
{"f_8012ChickenBridge.scm",(void*)f_8012},
{"f_8070ChickenBridge.scm",(void*)f_8070},
{"f_8073ChickenBridge.scm",(void*)f_8073},
{"f_8076ChickenBridge.scm",(void*)f_8076},
{"f_8288ChickenBridge.scm",(void*)f_8288},
{"f_8226ChickenBridge.scm",(void*)f_8226},
{"f_8260ChickenBridge.scm",(void*)f_8260},
{"f_8235ChickenBridge.scm",(void*)f_8235},
{"f_8246ChickenBridge.scm",(void*)f_8246},
{"f_8242ChickenBridge.scm",(void*)f_8242},
{"f_8085ChickenBridge.scm",(void*)f_8085},
{"f_8163ChickenBridge.scm",(void*)f_8163},
{"f_8204ChickenBridge.scm",(void*)f_8204},
{"f_8208ChickenBridge.scm",(void*)f_8208},
{"f_8212ChickenBridge.scm",(void*)f_8212},
{"f_8167ChickenBridge.scm",(void*)f_8167},
{"f_8171ChickenBridge.scm",(void*)f_8171},
{"f_8198ChickenBridge.scm",(void*)f_8198},
{"f_8174ChickenBridge.scm",(void*)f_8174},
{"f_8088ChickenBridge.scm",(void*)f_8088},
{"f_8160ChickenBridge.scm",(void*)f_8160},
{"f_8102ChickenBridge.scm",(void*)f_8102},
{"f_8104ChickenBridge.scm",(void*)f_8104},
{"f_8152ChickenBridge.scm",(void*)f_8152},
{"f_8123ChickenBridge.scm",(void*)f_8123},
{"f_8140ChickenBridge.scm",(void*)f_8140},
{"f_8126ChickenBridge.scm",(void*)f_8126},
{"f_8119ChickenBridge.scm",(void*)f_8119},
{"f_8091ChickenBridge.scm",(void*)f_8091},
{"f_8021ChickenBridge.scm",(void*)f_8021},
{"f_8031ChickenBridge.scm",(void*)f_8031},
{"f_8037ChickenBridge.scm",(void*)f_8037},
{"f_8009ChickenBridge.scm",(void*)f_8009},
{"f_7957ChickenBridge.scm",(void*)f_7957},
{"f_7974ChickenBridge.scm",(void*)f_7974},
{"f_7990ChickenBridge.scm",(void*)f_7990},
{"f_7968ChickenBridge.scm",(void*)f_7968},
{"f_7951ChickenBridge.scm",(void*)f_7951},
{"f_5790ChickenBridge.scm",(void*)f_5790},
{"f_7875ChickenBridge.scm",(void*)f_7875},
{"f_5793ChickenBridge.scm",(void*)f_5793},
{"f_7851ChickenBridge.scm",(void*)f_7851},
{"f_7863ChickenBridge.scm",(void*)f_7863},
{"f_7859ChickenBridge.scm",(void*)f_7859},
{"f_7837ChickenBridge.scm",(void*)f_7837},
{"f_7845ChickenBridge.scm",(void*)f_7845},
{"f_7831ChickenBridge.scm",(void*)f_7831},
{"f_5796ChickenBridge.scm",(void*)f_5796},
{"f_6948ChickenBridge.scm",(void*)f_6948},
{"f_7777ChickenBridge.scm",(void*)f_7777},
{"f_7824ChickenBridge.scm",(void*)f_7824},
{"f_7814ChickenBridge.scm",(void*)f_7814},
{"f_7781ChickenBridge.scm",(void*)f_7781},
{"f_6951ChickenBridge.scm",(void*)f_6951},
{"f_7771ChickenBridge.scm",(void*)f_7771},
{"f_7224ChickenBridge.scm",(void*)f_7224},
{"f_7280ChickenBridge.scm",(void*)f_7280},
{"f_7283ChickenBridge.scm",(void*)f_7283},
{"f_7286ChickenBridge.scm",(void*)f_7286},
{"f_7289ChickenBridge.scm",(void*)f_7289},
{"f_7292ChickenBridge.scm",(void*)f_7292},
{"f_7295ChickenBridge.scm",(void*)f_7295},
{"f_7298ChickenBridge.scm",(void*)f_7298},
{"f_7301ChickenBridge.scm",(void*)f_7301},
{"f_7765ChickenBridge.scm",(void*)f_7765},
{"f_7319ChickenBridge.scm",(void*)f_7319},
{"f_7322ChickenBridge.scm",(void*)f_7322},
{"f_7600ChickenBridge.scm",(void*)f_7600},
{"f_7708ChickenBridge.scm",(void*)f_7708},
{"f_7620ChickenBridge.scm",(void*)f_7620},
{"f_7629ChickenBridge.scm",(void*)f_7629},
{"f_7633ChickenBridge.scm",(void*)f_7633},
{"f_7637ChickenBridge.scm",(void*)f_7637},
{"f_7645ChickenBridge.scm",(void*)f_7645},
{"f_7641ChickenBridge.scm",(void*)f_7641},
{"f_7610ChickenBridge.scm",(void*)f_7610},
{"f_7325ChickenBridge.scm",(void*)f_7325},
{"f_7328ChickenBridge.scm",(void*)f_7328},
{"f_7331ChickenBridge.scm",(void*)f_7331},
{"f_7334ChickenBridge.scm",(void*)f_7334},
{"f_7337ChickenBridge.scm",(void*)f_7337},
{"f_7594ChickenBridge.scm",(void*)f_7594},
{"f_7493ChickenBridge.scm",(void*)f_7493},
{"f_7500ChickenBridge.scm",(void*)f_7500},
{"f_7502ChickenBridge.scm",(void*)f_7502},
{"f_7574ChickenBridge.scm",(void*)f_7574},
{"f_7526ChickenBridge.scm",(void*)f_7526},
{"f_7529ChickenBridge.scm",(void*)f_7529},
{"f_7550ChickenBridge.scm",(void*)f_7550},
{"f_7516ChickenBridge.scm",(void*)f_7516},
{"f_7340ChickenBridge.scm",(void*)f_7340},
{"f_7482ChickenBridge.scm",(void*)f_7482},
{"f_7470ChickenBridge.scm",(void*)f_7470},
{"f_7466ChickenBridge.scm",(void*)f_7466},
{"f_7347ChickenBridge.scm",(void*)f_7347},
{"f_7304ChickenBridge.scm",(void*)f_7304},
{"f_7763ChickenBridge.scm",(void*)f_7763},
{"f_7268ChickenBridge.scm",(void*)f_7268},
{"f_7262ChickenBridge.scm",(void*)f_7262},
{"f_7256ChickenBridge.scm",(void*)f_7256},
{"f_7250ChickenBridge.scm",(void*)f_7250},
{"f_7244ChickenBridge.scm",(void*)f_7244},
{"f_7238ChickenBridge.scm",(void*)f_7238},
{"f_7232ChickenBridge.scm",(void*)f_7232},
{"f_7226ChickenBridge.scm",(void*)f_7226},
{"f_6490ChickenBridge.scm",(void*)f_6490},
{"f_6953ChickenBridge.scm",(void*)f_6953},
{"f_6963ChickenBridge.scm",(void*)f_6963},
{"f_7194ChickenBridge.scm",(void*)f_7194},
{"f_6966ChickenBridge.scm",(void*)f_6966},
{"f_6969ChickenBridge.scm",(void*)f_6969},
{"f_6981ChickenBridge.scm",(void*)f_6981},
{"f_7029ChickenBridge.scm",(void*)f_7029},
{"f_7045ChickenBridge.scm",(void*)f_7045},
{"f_7055ChickenBridge.scm",(void*)f_7055},
{"f_7172ChickenBridge.scm",(void*)f_7172},
{"f_7160ChickenBridge.scm",(void*)f_7160},
{"f_7158ChickenBridge.scm",(void*)f_7158},
{"f_7145ChickenBridge.scm",(void*)f_7145},
{"f_7099ChickenBridge.scm",(void*)f_7099},
{"f_7126ChickenBridge.scm",(void*)f_7126},
{"f_7105ChickenBridge.scm",(void*)f_7105},
{"f_7039ChickenBridge.scm",(void*)f_7039},
{"f_6984ChickenBridge.scm",(void*)f_6984},
{"f_6989ChickenBridge.scm",(void*)f_6989},
{"f_7002ChickenBridge.scm",(void*)f_7002},
{"f_7211ChickenBridge.scm",(void*)f_7211},
{"f_7202ChickenBridge.scm",(void*)f_7202},
{"f_7210ChickenBridge.scm",(void*)f_7210},
{"f_7213ChickenBridge.scm",(void*)f_7213},
{"f_7221ChickenBridge.scm",(void*)f_7221},
{"f_6937ChickenBridge.scm",(void*)f_6937},
{"f_6600ChickenBridge.scm",(void*)f_6600},
{"f_6941ChickenBridge.scm",(void*)f_6941},
{"f_6879ChickenBridge.scm",(void*)f_6879},
{"f_6897ChickenBridge.scm",(void*)f_6897},
{"f_6907ChickenBridge.scm",(void*)f_6907},
{"f_6883ChickenBridge.scm",(void*)f_6883},
{"f_6870ChickenBridge.scm",(void*)f_6870},
{"f_6578ChickenBridge.scm",(void*)f_6578},
{"f_6874ChickenBridge.scm",(void*)f_6874},
{"f_6864ChickenBridge.scm",(void*)f_6864},
{"f_6560ChickenBridge.scm",(void*)f_6560},
{"f_6855ChickenBridge.scm",(void*)f_6855},
{"f_6569ChickenBridge.scm",(void*)f_6569},
{"f_6859ChickenBridge.scm",(void*)f_6859},
{"f_6792ChickenBridge.scm",(void*)f_6792},
{"f_6817ChickenBridge.scm",(void*)f_6817},
{"f_6525ChickenBridge.scm",(void*)f_6525},
{"f_6805ChickenBridge.scm",(void*)f_6805},
{"f_6624ChickenBridge.scm",(void*)f_6624},
{"f_6743ChickenBridge.scm",(void*)f_6743},
{"f_6738ChickenBridge.scm",(void*)f_6738},
{"f_6626ChickenBridge.scm",(void*)f_6626},
{"f_6733ChickenBridge.scm",(void*)f_6733},
{"f_6737ChickenBridge.scm",(void*)f_6737},
{"f_6729ChickenBridge.scm",(void*)f_6729},
{"f_6697ChickenBridge.scm",(void*)f_6697},
{"f_6722ChickenBridge.scm",(void*)f_6722},
{"f_6726ChickenBridge.scm",(void*)f_6726},
{"f_6707ChickenBridge.scm",(void*)f_6707},
{"f_6686ChickenBridge.scm",(void*)f_6686},
{"f_6656ChickenBridge.scm",(void*)f_6656},
{"f_6628ChickenBridge.scm",(void*)f_6628},
{"f_6605ChickenBridge.scm",(void*)f_6605},
{"f_6610ChickenBridge.scm",(void*)f_6610},
{"f_6615ChickenBridge.scm",(void*)f_6615},
{"f_6583ChickenBridge.scm",(void*)f_6583},
{"f_6587ChickenBridge.scm",(void*)f_6587},
{"f_6539ChickenBridge.scm",(void*)f_6539},
{"f_6543ChickenBridge.scm",(void*)f_6543},
{"f_6530ChickenBridge.scm",(void*)f_6530},
{"f_6534ChickenBridge.scm",(void*)f_6534},
{"f_6518ChickenBridge.scm",(void*)f_6518},
{"f_6515ChickenBridge.scm",(void*)f_6515},
{"f_6472ChickenBridge.scm",(void*)f_6472},
{"f_6477ChickenBridge.scm",(void*)f_6477},
{"f_6458ChickenBridge.scm",(void*)f_6458},
{"f_6463ChickenBridge.scm",(void*)f_6463},
{"f_6429ChickenBridge.scm",(void*)f_6429},
{"f_6438ChickenBridge.scm",(void*)f_6438},
{"f_6443ChickenBridge.scm",(void*)f_6443},
{"f_6418ChickenBridge.scm",(void*)f_6418},
{"f_6423ChickenBridge.scm",(void*)f_6423},
{"f_6378ChickenBridge.scm",(void*)f_6378},
{"f_6408ChickenBridge.scm",(void*)f_6408},
{"f_6330ChickenBridge.scm",(void*)f_6330},
{"f_6364ChickenBridge.scm",(void*)f_6364},
{"f_6310ChickenBridge.scm",(void*)f_6310},
{"f_6290ChickenBridge.scm",(void*)f_6290},
{"f_6276ChickenBridge.scm",(void*)f_6276},
{"f_6266ChickenBridge.scm",(void*)f_6266},
{"f_6256ChickenBridge.scm",(void*)f_6256},
{"f_6246ChickenBridge.scm",(void*)f_6246},
{"f_6236ChickenBridge.scm",(void*)f_6236},
{"f_6214ChickenBridge.scm",(void*)f_6214},
{"f_6208ChickenBridge.scm",(void*)f_6208},
{"f_6161ChickenBridge.scm",(void*)f_6161},
{"f_6165ChickenBridge.scm",(void*)f_6165},
{"f_6181ChickenBridge.scm",(void*)f_6181},
{"f_6190ChickenBridge.scm",(void*)f_6190},
{"f_6168ChickenBridge.scm",(void*)f_6168},
{"f_6152ChickenBridge.scm",(void*)f_6152},
{"f_6156ChickenBridge.scm",(void*)f_6156},
{"f_5973ChickenBridge.scm",(void*)f_5973},
{"f_6126ChickenBridge.scm",(void*)f_6126},
{"f_6139ChickenBridge.scm",(void*)f_6139},
{"f_6121ChickenBridge.scm",(void*)f_6121},
{"f_5976ChickenBridge.scm",(void*)f_5976},
{"f_6118ChickenBridge.scm",(void*)f_6118},
{"f_6102ChickenBridge.scm",(void*)f_6102},
{"f_6095ChickenBridge.scm",(void*)f_6095},
{"f_6091ChickenBridge.scm",(void*)f_6091},
{"f_6004ChickenBridge.scm",(void*)f_6004},
{"f_6012ChickenBridge.scm",(void*)f_6012},
{"f_6022ChickenBridge.scm",(void*)f_6022},
{"f_6025ChickenBridge.scm",(void*)f_6025},
{"f_6007ChickenBridge.scm",(void*)f_6007},
{"f_5802ChickenBridge.scm",(void*)f_5802},
{"f_5808ChickenBridge.scm",(void*)f_5808},
{"f_5811ChickenBridge.scm",(void*)f_5811},
{"f_3614ChickenBridge.scm",(void*)f_3614},
{"f_3627ChickenBridge.scm",(void*)f_3627},
{"f_3634ChickenBridge.scm",(void*)f_3634},
{"f_3641ChickenBridge.scm",(void*)f_3641},
{"f_3620ChickenBridge.scm",(void*)f_3620},
{"f_5815ChickenBridge.scm",(void*)f_5815},
{"f_5849ChickenBridge.scm",(void*)f_5849},
{"f_5942ChickenBridge.scm",(void*)f_5942},
{"f_5952ChickenBridge.scm",(void*)f_5952},
{"f_5855ChickenBridge.scm",(void*)f_5855},
{"f_5912ChickenBridge.scm",(void*)f_5912},
{"f_5922ChickenBridge.scm",(void*)f_5922},
{"f_5863ChickenBridge.scm",(void*)f_5863},
{"f_5877ChickenBridge.scm",(void*)f_5877},
{"f_5881ChickenBridge.scm",(void*)f_5881},
{"f_5885ChickenBridge.scm",(void*)f_5885},
{"f_5889ChickenBridge.scm",(void*)f_5889},
{"f_5896ChickenBridge.scm",(void*)f_5896},
{"f_5873ChickenBridge.scm",(void*)f_5873},
{"f_5866ChickenBridge.scm",(void*)f_5866},
{"f_5818ChickenBridge.scm",(void*)f_5818},
{"f_4741ChickenBridge.scm",(void*)f_4741},
{"f_4754ChickenBridge.scm",(void*)f_4754},
{"f_4804ChickenBridge.scm",(void*)f_4804},
{"f_4901ChickenBridge.scm",(void*)f_4901},
{"f_4969ChickenBridge.scm",(void*)f_4969},
{"f_5226ChickenBridge.scm",(void*)f_5226},
{"f_4976ChickenBridge.scm",(void*)f_4976},
{"f_5214ChickenBridge.scm",(void*)f_5214},
{"f_5165ChickenBridge.scm",(void*)f_5165},
{"f_5171ChickenBridge.scm",(void*)f_5171},
{"f_5195ChickenBridge.scm",(void*)f_5195},
{"f_5191ChickenBridge.scm",(void*)f_5191},
{"f_5179ChickenBridge.scm",(void*)f_5179},
{"f_4979ChickenBridge.scm",(void*)f_4979},
{"f_5141ChickenBridge.scm",(void*)f_5141},
{"f_5145ChickenBridge.scm",(void*)f_5145},
{"f_4982ChickenBridge.scm",(void*)f_4982},
{"f_5118ChickenBridge.scm",(void*)f_5118},
{"f_5122ChickenBridge.scm",(void*)f_5122},
{"f_4985ChickenBridge.scm",(void*)f_4985},
{"f_5095ChickenBridge.scm",(void*)f_5095},
{"f_5099ChickenBridge.scm",(void*)f_5099},
{"f_4988ChickenBridge.scm",(void*)f_4988},
{"f_5020ChickenBridge.scm",(void*)f_5020},
{"f_5038ChickenBridge.scm",(void*)f_5038},
{"f_5056ChickenBridge.scm",(void*)f_5056},
{"f_5074ChickenBridge.scm",(void*)f_5074},
{"f_4991ChickenBridge.scm",(void*)f_4991},
{"f_4995ChickenBridge.scm",(void*)f_4995},
{"f_4905ChickenBridge.scm",(void*)f_4905},
{"f_4909ChickenBridge.scm",(void*)f_4909},
{"f_4913ChickenBridge.scm",(void*)f_4913},
{"f_4808ChickenBridge.scm",(void*)f_4808},
{"f_4812ChickenBridge.scm",(void*)f_4812},
{"f_4816ChickenBridge.scm",(void*)f_4816},
{"f_4835ChickenBridge.scm",(void*)f_4835},
{"f_4839ChickenBridge.scm",(void*)f_4839},
{"f_4819ChickenBridge.scm",(void*)f_4819},
{"f_4823ChickenBridge.scm",(void*)f_4823},
{"f_4758ChickenBridge.scm",(void*)f_4758},
{"f_4762ChickenBridge.scm",(void*)f_4762},
{"f_4766ChickenBridge.scm",(void*)f_4766},
{"f_4748ChickenBridge.scm",(void*)f_4748},
{"f_4563ChickenBridge.scm",(void*)f_4563},
{"f_4575ChickenBridge.scm",(void*)f_4575},
{"f_4594ChickenBridge.scm",(void*)f_4594},
{"f_4612ChickenBridge.scm",(void*)f_4612},
{"f_4644ChickenBridge.scm",(void*)f_4644},
{"f_4647ChickenBridge.scm",(void*)f_4647},
{"f_4640ChickenBridge.scm",(void*)f_4640},
{"f_4626ChickenBridge.scm",(void*)f_4626},
{"f_4597ChickenBridge.scm",(void*)f_4597},
{"f_4542ChickenBridge.scm",(void*)f_4542},
{"f_4549ChickenBridge.scm",(void*)f_4549},
{"f_4552ChickenBridge.scm",(void*)f_4552},
{"f_4558ChickenBridge.scm",(void*)f_4558},
{"f_4477ChickenBridge.scm",(void*)f_4477},
{"f_4486ChickenBridge.scm",(void*)f_4486},
{"f_4509ChickenBridge.scm",(void*)f_4509},
{"f_4499ChickenBridge.scm",(void*)f_4499},
{"f_4433ChickenBridge.scm",(void*)f_4433},
{"f_4421ChickenBridge.scm",(void*)f_4421},
{"f_4319ChickenBridge.scm",(void*)f_4319},
{"f_4271ChickenBridge.scm",(void*)f_4271},
{"f_3652ChickenBridge.scm",(void*)f_3652},
{"f_3656ChickenBridge.scm",(void*)f_3656},
{"f_3659ChickenBridge.scm",(void*)f_3659},
{"f_4085ChickenBridge.scm",(void*)f_4085},
{"f_4081ChickenBridge.scm",(void*)f_4081},
{"f_4077ChickenBridge.scm",(void*)f_4077},
{"f_3662ChickenBridge.scm",(void*)f_3662},
{"f_3785ChickenBridge.scm",(void*)f_3785},
{"f_3018ChickenBridge.scm",(void*)f_3018},
{"f_3791ChickenBridge.scm",(void*)f_3791},
{"f_3034ChickenBridge.scm",(void*)f_3034},
{"f_3879ChickenBridge.scm",(void*)f_3879},
{"f_3949ChickenBridge.scm",(void*)f_3949},
{"f_3050ChickenBridge.scm",(void*)f_3050},
{"f_3952ChickenBridge.scm",(void*)f_3952},
{"f_3082ChickenBridge.scm",(void*)f_3082},
{"f_4030ChickenBridge.scm",(void*)f_4030},
{"f_4056ChickenBridge.scm",(void*)f_4056},
{"f_4050ChickenBridge.scm",(void*)f_4050},
{"f_4039ChickenBridge.scm",(void*)f_4039},
{"f_3981ChickenBridge.scm",(void*)f_3981},
{"f_3991ChickenBridge.scm",(void*)f_3991},
{"f_4017ChickenBridge.scm",(void*)f_4017},
{"f_4011ChickenBridge.scm",(void*)f_4011},
{"f_3994ChickenBridge.scm",(void*)f_3994},
{"f_4004ChickenBridge.scm",(void*)f_4004},
{"f_3997ChickenBridge.scm",(void*)f_3997},
{"f_3958ChickenBridge.scm",(void*)f_3958},
{"f_3967ChickenBridge.scm",(void*)f_3967},
{"f_3961ChickenBridge.scm",(void*)f_3961},
{"f_3885ChickenBridge.scm",(void*)f_3885},
{"f_3903ChickenBridge.scm",(void*)f_3903},
{"f_3936ChickenBridge.scm",(void*)f_3936},
{"f_3922ChickenBridge.scm",(void*)f_3922},
{"f_3930ChickenBridge.scm",(void*)f_3930},
{"f_3913ChickenBridge.scm",(void*)f_3913},
{"f_3888ChickenBridge.scm",(void*)f_3888},
{"f_3800ChickenBridge.scm",(void*)f_3800},
{"f_3822ChickenBridge.scm",(void*)f_3822},
{"f_3869ChickenBridge.scm",(void*)f_3869},
{"f_3855ChickenBridge.scm",(void*)f_3855},
{"f_3863ChickenBridge.scm",(void*)f_3863},
{"f_3835ChickenBridge.scm",(void*)f_3835},
{"f_3838ChickenBridge.scm",(void*)f_3838},
{"f_3803ChickenBridge.scm",(void*)f_3803},
{"f_3820ChickenBridge.scm",(void*)f_3820},
{"f_3806ChickenBridge.scm",(void*)f_3806},
{"f_3677ChickenBridge.scm",(void*)f_3677},
{"f_3735ChickenBridge.scm",(void*)f_3735},
{"f_3738ChickenBridge.scm",(void*)f_3738},
{"f_3759ChickenBridge.scm",(void*)f_3759},
{"f_3770ChickenBridge.scm",(void*)f_3770},
{"f_3749ChickenBridge.scm",(void*)f_3749},
{"f_3683ChickenBridge.scm",(void*)f_3683},
{"f_3693ChickenBridge.scm",(void*)f_3693},
{"f_3729ChickenBridge.scm",(void*)f_3729},
{"f_3699ChickenBridge.scm",(void*)f_3699},
{"f_3714ChickenBridge.scm",(void*)f_3714},
{"f_3718ChickenBridge.scm",(void*)f_3718},
{"f_3722ChickenBridge.scm",(void*)f_3722},
{"f_3706ChickenBridge.scm",(void*)f_3706},
{"f_3548ChickenBridge.scm",(void*)f_3548},
{"f_3550ChickenBridge.scm",(void*)f_3550},
{"f_3598ChickenBridge.scm",(void*)f_3598},
{"f_3554ChickenBridge.scm",(void*)f_3554},
{"f_3557ChickenBridge.scm",(void*)f_3557},
{"f_3562ChickenBridge.scm",(void*)f_3562},
{"f_3583ChickenBridge.scm",(void*)f_3583},
{"f_3540ChickenBridge.scm",(void*)f_3540},
{"f_3542ChickenBridge.scm",(void*)f_3542},
{"f_3332ChickenBridge.scm",(void*)f_3332},
{"f_3349ChickenBridge.scm",(void*)f_3349},
{"f_3353ChickenBridge.scm",(void*)f_3353},
{"f_3299ChickenBridge.scm",(void*)f_3299},
{"f_3306ChickenBridge.scm",(void*)f_3306},
{"f_3250ChickenBridge.scm",(void*)f_3250},
{"f_3257ChickenBridge.scm",(void*)f_3257},
{"f_3315ChickenBridge.scm",(void*)f_3315},
{"f_3538ChickenBridge.scm",(void*)f_3538},
{"f_3515ChickenBridge.scm",(void*)f_3515},
{"f_3531ChickenBridge.scm",(void*)f_3531},
{"f_3377ChickenBridge.scm",(void*)f_3377},
{"f_3380ChickenBridge.scm",(void*)f_3380},
{"f_3404ChickenBridge.scm",(void*)f_3404},
{"f_3461ChickenBridge.scm",(void*)f_3461},
{"f_3467ChickenBridge.scm",(void*)f_3467},
{"f_3476ChickenBridge.scm",(void*)f_3476},
{"f_3485ChickenBridge.scm",(void*)f_3485},
{"f_3494ChickenBridge.scm",(void*)f_3494},
{"f_3503ChickenBridge.scm",(void*)f_3503},
{"f_3455ChickenBridge.scm",(void*)f_3455},
{"f_3410ChickenBridge.scm",(void*)f_3410},
{"f_3416ChickenBridge.scm",(void*)f_3416},
{"f_3422ChickenBridge.scm",(void*)f_3422},
{"f_3428ChickenBridge.scm",(void*)f_3428},
{"f_3434ChickenBridge.scm",(void*)f_3434},
{"f_3440ChickenBridge.scm",(void*)f_3440},
{"f_3281ChickenBridge.scm",(void*)f_3281},
{"f_3288ChickenBridge.scm",(void*)f_3288},
{"f_3271ChickenBridge.scm",(void*)f_3271},
{"f_3259ChickenBridge.scm",(void*)f_3259},
{"f_3227ChickenBridge.scm",(void*)f_3227},
{"f_3234ChickenBridge.scm",(void*)f_3234},
{"f_3241ChickenBridge.scm",(void*)f_3241},
{"f_3211ChickenBridge.scm",(void*)f_3211},
{"f_3218ChickenBridge.scm",(void*)f_3218},
{"f_3225ChickenBridge.scm",(void*)f_3225},
{"f_3199ChickenBridge.scm",(void*)f_3199},
{"f_3181ChickenBridge.scm",(void*)f_3181},
{"f_3163ChickenBridge.scm",(void*)f_3163},
{"f_3148ChickenBridge.scm",(void*)f_3148},
{"f_3142ChickenBridge.scm",(void*)f_3142},
{"f_3130ChickenBridge.scm",(void*)f_3130},
{"f_3112ChickenBridge.scm",(void*)f_3112},
{"f_3091ChickenBridge.scm",(void*)f_3091},
{"f_3059ChickenBridge.scm",(void*)f_3059},
{"f_3066ChickenBridge.scm",(void*)f_3066},
{"f_3001ChickenBridge.scm",(void*)f_3001},
{"f_3009ChickenBridge.scm",(void*)f_3009},
{"f_2991ChickenBridge.scm",(void*)f_2991},
{"f_2999ChickenBridge.scm",(void*)f_2999},
{"f_2985ChickenBridge.scm",(void*)f_2985},
{"f_2973ChickenBridge.scm",(void*)f_2973},
{"f_2949ChickenBridge.scm",(void*)f_2949},
{"f_2865ChickenBridge.scm",(void*)f_2865},
{"f_2844ChickenBridge.scm",(void*)f_2844},
{"f_2834ChickenBridge.scm",(void*)f_2834},
{"f_2822ChickenBridge.scm",(void*)f_2822},
{"f_2793ChickenBridge.scm",(void*)f_2793},
{"f_2781ChickenBridge.scm",(void*)f_2781},
{"f_2763ChickenBridge.scm",(void*)f_2763},
{"f_2745ChickenBridge.scm",(void*)f_2745},
{"f_2724ChickenBridge.scm",(void*)f_2724},
{"f_2718ChickenBridge.scm",(void*)f_2718},
{"f_2712ChickenBridge.scm",(void*)f_2712},
{"f_2693ChickenBridge.scm",(void*)f_2693},
{"f_2674ChickenBridge.scm",(void*)f_2674},
{"f_2668ChickenBridge.scm",(void*)f_2668},
{"f_2628ChickenBridge.scm",(void*)f_2628},
{"f_2609ChickenBridge.scm",(void*)f_2609},
{"f_2565ChickenBridge.scm",(void*)f_2565},
{"f_2559ChickenBridge.scm",(void*)f_2559},
{"f_2553ChickenBridge.scm",(void*)f_2553},
{"f_2547ChickenBridge.scm",(void*)f_2547},
{"f_2541ChickenBridge.scm",(void*)f_2541},
{"f_2518ChickenBridge.scm",(void*)f_2518},
{"f_2535ChickenBridge.scm",(void*)f_2535},
{"f_2460ChickenBridge.scm",(void*)f_2460},
{"f_2512ChickenBridge.scm",(void*)f_2512},
{"f_2496ChickenBridge.scm",(void*)f_2496},
{"f_2477ChickenBridge.scm",(void*)f_2477},
{"f_2372ChickenBridge.scm",(void*)f_2372},
{"f_2418ChickenBridge.scm",(void*)f_2418},
{"f_2366ChickenBridge.scm",(void*)f_2366},
{"f_2307ChickenBridge.scm",(void*)f_2307},
{"f_2320ChickenBridge.scm",(void*)f_2320},
{"f_2356ChickenBridge.scm",(void*)f_2356},
{"f_2301ChickenBridge.scm",(void*)f_2301},
{"f_2206ChickenBridge.scm",(void*)f_2206},
{"f_2210ChickenBridge.scm",(void*)f_2210},
{"f_2213ChickenBridge.scm",(void*)f_2213},
{"f_2225ChickenBridge.scm",(void*)f_2225},
{"f_2247ChickenBridge.scm",(void*)f_2247},
{"f_2200ChickenBridge.scm",(void*)f_2200},
{"f_2194ChickenBridge.scm",(void*)f_2194},
{"f_2188ChickenBridge.scm",(void*)f_2188},
{"f_2182ChickenBridge.scm",(void*)f_2182},
{"f_2176ChickenBridge.scm",(void*)f_2176},
{"f_2116ChickenBridge.scm",(void*)f_2116},
{"f_2128ChickenBridge.scm",(void*)f_2128},
{"f_2123ChickenBridge.scm",(void*)f_2123},
{"f_2118ChickenBridge.scm",(void*)f_2118},
{"f_2097ChickenBridge.scm",(void*)f_2097},
{"f_2091ChickenBridge.scm",(void*)f_2091},
{"f_2085ChickenBridge.scm",(void*)f_2085},
{"f_2003ChickenBridge.scm",(void*)f_2003},
{"f_2017ChickenBridge.scm",(void*)f_2017},
{"f_1984ChickenBridge.scm",(void*)f_1984},
{"f_1971ChickenBridge.scm",(void*)f_1971},
{"f_1961ChickenBridge.scm",(void*)f_1961},
{"f_1950ChickenBridge.scm",(void*)f_1950},
{"f_1943ChickenBridge.scm",(void*)f_1943},
{"f_1932ChickenBridge.scm",(void*)f_1932},
{"f_1894ChickenBridge.scm",(void*)f_1894},
{"f_1887ChickenBridge.scm",(void*)f_1887},
{"f_1812ChickenBridge.scm",(void*)f_1812},
{"f_1778ChickenBridge.scm",(void*)f_1778},
{"f_1751ChickenBridge.scm",(void*)f_1751},
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
