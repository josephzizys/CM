/* Generated from ChickenBridge.scm by the CHICKEN compiler
   http://www.call-with-current-continuation.org
   2008-01-03 09:46
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

static C_TLS C_word lf[646];


/* from k6608 */
static C_word C_fcall stub1488(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub1488(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
load_sal_file(t0);
return C_r;}

/* from k6593 in hush in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
C_noret_decl(stub1482)
static void C_ccall stub1482(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub1482(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_hush();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k6587 */
C_noret_decl(stub1477)
static void C_ccall stub1477(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0) C_noret;
static void C_ccall stub1477(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_unfix(C_a0);
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_stop(t0);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k6571 in cont in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
C_noret_decl(stub1472)
static void C_ccall stub1472(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub1472(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_cont();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k6562 in pause in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
C_noret_decl(stub1468)
static void C_ccall stub1468(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub1468(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_pause();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k6553 in paused? in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
C_noret_decl(stub1464)
static void C_ccall stub1464(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub1464(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
C_r=C_mk_bool(scheduler_is_paused());
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k6547 */
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

/* from k6527 in scheduler-set-time-milliseconds in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
C_noret_decl(stub1449)
static void C_ccall stub1449(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0) C_noret;
static void C_ccall stub1449(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_truep(C_a0);
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_set_time_milliseconds(t0);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k6518 in time-format in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
C_noret_decl(stub1444)
static void C_ccall stub1444(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub1444(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
C_r=C_mk_bool(scheduler_is_time_milliseconds());
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from current-time-seconds in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
#define return(x) C_cblock C_r = (C_flonum(&C_a,(x))); goto C_ret; C_cblockend
static C_word C_fcall stub1441(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub1441(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
 C_return( (Time::getMillisecondCounterHiRes() / 1000.0) );
C_ret:
#undef return

return C_r;}

/* from current-time-milliseconds in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
#define return(x) C_cblock C_r = (C_flonum(&C_a,(x))); goto C_ret; C_cblockend
static C_word C_fcall stub1438(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub1438(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
 C_return( Time::getMillisecondCounterHiRes());
C_ret:
#undef return

return C_r;}

/* from k6506 */
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

/* from k6470 in print-error in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static C_word C_fcall stub1419(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub1419(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_error(t0);
return C_r;}

/* from k6456 in print-message in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static C_word C_fcall stub1413(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub1413(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_message(t0);
return C_r;}

/* from k6436 */
static C_word C_fcall stub1407(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub1407(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
set_current_directory(t0);
return C_r;}

/* from f_6418 in current-directory in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
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

/* from k1969 */
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

/* from k1959 */
static C_word C_fcall stub134(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub134(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::rangamma(t0));
return C_r;}

/* from k1952 */
static C_word C_fcall stub128(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub128(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
C_r=C_flonum(&C_a,Toolbox::ranbeta(t0,t1));
return C_r;}

/* from k1941 */
static C_word C_fcall stub122(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub122(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::ranexp(t0));
return C_r;}

/* from k1934 */
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

/* from k1914 */
static C_word C_fcall stub100(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub100(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
C_r=C_flonum(&C_a,Toolbox::ran(t0,t1));
return C_r;}

/* from k1903 */
static C_word C_fcall stub94(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub94(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_unfix(C_a0);
int t1=(int )C_unfix(C_a1);
C_r=C_fix((C_word)Toolbox::ran(t0,t1));
return C_r;}

/* from k1892 */
static C_word C_fcall stub88(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub88(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::ran(t0));
return C_r;}

/* from k1885 */
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

/* from k1875 */
static C_word C_fcall stub75(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub75(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::hertz_to_keynum(t0));
return C_r;}

/* from k1868 */
static C_word C_fcall stub71(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub71(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_fix((C_word)Toolbox::keynum_to_pc(t0));
return C_r;}

/* from k1861 */
static C_word C_fcall stub66(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub66(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::keynum_to_hertz(t0));
return C_r;}

/* from k1854 */
static C_word C_fcall stub62(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub62(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_fix((C_word)Toolbox::scaler_to_cents(t0));
return C_r;}

/* from k1847 */
static C_word C_fcall stub57(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub57(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_unfix(C_a0);
C_r=C_flonum(&C_a,Toolbox::cents_to_scaler(t0));
return C_r;}

/* from k1840 */
static C_word C_fcall stub50(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2) C_regparm;
C_regparm static C_word C_fcall stub50(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
float t2=(float )C_c_double(C_a2);
C_r=C_flonum(&C_a,Toolbox::rhythm_to_seconds(t0,t1,t2));
return C_r;}

/* from k1825 */
static C_word C_fcall stub42(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub42(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
C_r=C_flonum(&C_a,Toolbox::quantize(t0,t1));
return C_r;}

/* from k1814 */
static C_word C_fcall stub35(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub35(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
int t1=(int )C_unfix(C_a1);
C_r=C_flonum(&C_a,Toolbox::decimals(t0,t1));
return C_r;}

/* from k1803 */
static C_word C_fcall stub30(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub30(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_fix((C_word)Toolbox::float_to_fixnum(t0));
return C_r;}

/* from k1796 */
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

/* from k1769 */
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
C_noret_decl(f_1735)
static void C_ccall f_1735(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1738)
static void C_ccall f_1738(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1741)
static void C_ccall f_1741(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1744)
static void C_ccall f_1744(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12096)
static void C_ccall f_12096(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_12104)
static void C_ccall f_12104(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12108)
static void C_ccall f_12108(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2786)
static void C_ccall f_2786(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2837)
static void C_ccall f_2837(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12086)
static void C_ccall f_12086(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_12094)
static void C_ccall f_12094(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2942)
static void C_ccall f_2942(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12072)
static void C_ccall f_12072(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_12080)
static void C_ccall f_12080(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12084)
static void C_ccall f_12084(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3135)
static void C_ccall f_3135(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12046)
static void C_ccall f_12046(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_12050)
static void C_ccall f_12050(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12056)
static void C_ccall f_12056(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12067)
static void C_ccall f_12067(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12063)
static void C_ccall f_12063(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3204)
static void C_ccall f_3204(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12024)
static void C_ccall f_12024(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4449)
static void C_ccall f_4449(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12004)
static void C_ccall f_12004(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4452)
static void C_ccall f_4452(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11964)
static void C_ccall f_11964(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4455)
static void C_ccall f_4455(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11870)
static void C_ccall f_11870(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_11874)
static void C_ccall f_11874(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11877)
static void C_ccall f_11877(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11895)
static void C_ccall f_11895(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11898)
static void C_ccall f_11898(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11929)
static void C_ccall f_11929(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11901)
static void C_fcall f_11901(C_word t0,C_word t1) C_noret;
C_noret_decl(f_11907)
static void C_ccall f_11907(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11860)
static void C_ccall f_11860(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_11854)
static void C_ccall f_11854(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4458)
static void C_ccall f_4458(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11762)
static void C_ccall f_11762(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11764)
static void C_ccall f_11764(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_11768)
static void C_ccall f_11768(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11771)
static void C_ccall f_11771(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11774)
static void C_ccall f_11774(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11814)
static void C_ccall f_11814(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11806)
static void C_ccall f_11806(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11777)
static void C_ccall f_11777(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11780)
static void C_ccall f_11780(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11783)
static void C_ccall f_11783(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11754)
static void C_ccall f_11754(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4461)
static void C_ccall f_4461(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11726)
static void C_ccall f_11726(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4464)
static void C_ccall f_4464(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11690)
static void C_ccall f_11690(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_11702)
static void C_ccall f_11702(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11698)
static void C_ccall f_11698(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11672)
static void C_ccall f_11672(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_11666)
static void C_ccall f_11666(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4467)
static void C_ccall f_4467(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11580)
static void C_ccall f_11580(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_11584)
static void C_ccall f_11584(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11587)
static void C_ccall f_11587(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11590)
static void C_ccall f_11590(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11603)
static void C_ccall f_11603(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11549)
static void C_ccall f_11549(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_11553)
static void C_ccall f_11553(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11568)
static void C_ccall f_11568(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11543)
static void C_ccall f_11543(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4470)
static void C_ccall f_4470(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11429)
static void C_ccall f_11429(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_11445)
static void C_ccall f_11445(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11456)
static void C_ccall f_11456(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11423)
static void C_ccall f_11423(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4526)
static void C_ccall f_4526(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11290)
static void C_ccall f_11290(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_11313)
static void C_ccall f_11313(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11310)
static void C_ccall f_11310(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11284)
static void C_ccall f_11284(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4529)
static void C_ccall f_4529(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11138)
static void C_ccall f_11138(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_11156)
static void C_ccall f_11156(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11165)
static void C_ccall f_11165(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11132)
static void C_ccall f_11132(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4532)
static void C_ccall f_4532(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11085)
static void C_ccall f_11085(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_11089)
static void C_ccall f_11089(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11092)
static void C_ccall f_11092(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11108)
static void C_ccall f_11108(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11067)
static void C_ccall f_11067(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_11061)
static void C_ccall f_11061(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4535)
static void C_ccall f_4535(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10985)
static void C_ccall f_10985(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4674)
static void C_ccall f_4674(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10911)
static void C_ccall f_10911(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_10918)
static void C_ccall f_10918(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10905)
static void C_ccall f_10905(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4677)
static void C_ccall f_4677(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10801)
static void C_ccall f_10801(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_10809)
static void C_ccall f_10809(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10775)
static void C_ccall f_10775(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_10792)
static void C_ccall f_10792(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10783)
static void C_fcall f_10783(C_word t0,C_word t1) C_noret;
C_noret_decl(f_10769)
static void C_ccall f_10769(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4680)
static void C_ccall f_4680(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10725)
static void C_ccall f_10725(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4683)
static void C_ccall f_4683(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10643)
static void C_ccall f_10643(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_10654)
static void C_ccall f_10654(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10656)
static void C_fcall f_10656(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_10685)
static void C_ccall f_10685(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10621)
static void C_ccall f_10621(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_10637)
static void C_ccall f_10637(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10615)
static void C_ccall f_10615(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4686)
static void C_ccall f_4686(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10539)
static void C_ccall f_10539(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_10543)
static void C_ccall f_10543(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10575)
static void C_ccall f_10575(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10556)
static void C_ccall f_10556(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10560)
static void C_ccall f_10560(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10512)
static void C_ccall f_10512(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_10516)
static void C_ccall f_10516(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10506)
static void C_ccall f_10506(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4689)
static void C_ccall f_4689(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10374)
static void C_ccall f_10374(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_10414)
static void C_ccall f_10414(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10378)
static void C_ccall f_10378(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10394)
static void C_ccall f_10394(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_10394)
static void C_ccall f_10394r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_10406)
static void C_ccall f_10406(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10410)
static void C_ccall f_10410(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10402)
static void C_ccall f_10402(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10313)
static void C_ccall f_10313(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_10360)
static void C_ccall f_10360(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10320)
static void C_fcall f_10320(C_word t0,C_word t1) C_noret;
C_noret_decl(f_10331)
static void C_ccall f_10331(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10307)
static void C_ccall f_10307(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4692)
static void C_ccall f_4692(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10287)
static void C_ccall f_10287(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_10281)
static void C_ccall f_10281(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4695)
static void C_ccall f_4695(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10261)
static void C_ccall f_10261(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10265)
static void C_ccall f_10265(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10253)
static void C_ccall f_10253(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4698)
static void C_ccall f_4698(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10233)
static void C_ccall f_10233(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10237)
static void C_ccall f_10237(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10225)
static void C_ccall f_10225(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4701)
static void C_ccall f_4701(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10205)
static void C_ccall f_10205(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10209)
static void C_ccall f_10209(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10197)
static void C_ccall f_10197(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4704)
static void C_ccall f_4704(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10177)
static void C_ccall f_10177(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10181)
static void C_ccall f_10181(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10169)
static void C_ccall f_10169(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4707)
static void C_ccall f_4707(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10068)
static void C_ccall f_10068(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_10038)
static void C_ccall f_10038(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_10062)
static void C_ccall f_10062(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10032)
static void C_ccall f_10032(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4710)
static void C_ccall f_4710(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9982)
static void C_ccall f_9982(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9984)
static void C_ccall f_9984(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_9988)
static void C_ccall f_9988(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10016)
static void C_ccall f_10016(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10008)
static void C_ccall f_10008(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10004)
static void C_ccall f_10004(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9991)
static void C_ccall f_9991(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9974)
static void C_ccall f_9974(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4713)
static void C_ccall f_4713(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9921)
static void C_ccall f_9921(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9923)
static void C_ccall f_9923(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_9927)
static void C_ccall f_9927(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9958)
static void C_ccall f_9958(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9950)
static void C_ccall f_9950(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9946)
static void C_ccall f_9946(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9930)
static void C_ccall f_9930(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9933)
static void C_ccall f_9933(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9913)
static void C_ccall f_9913(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4716)
static void C_ccall f_4716(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9863)
static void C_ccall f_9863(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_9877)
static void C_ccall f_9877(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9869)
static void C_ccall f_9869(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_9828)
static void C_ccall f_9828(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_9861)
static void C_ccall f_9861(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9822)
static void C_ccall f_9822(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4719)
static void C_ccall f_4719(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9769)
static void C_ccall f_9769(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_9773)
static void C_ccall f_9773(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9786)
static void C_ccall f_9786(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9778)
static void C_ccall f_9778(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_9726)
static void C_ccall f_9726(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_9759)
static void C_ccall f_9759(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9720)
static void C_ccall f_9720(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4722)
static void C_ccall f_4722(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9640)
static void C_ccall f_9640(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_9634)
static void C_ccall f_9634(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4725)
static void C_ccall f_4725(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9403)
static void C_ccall f_9403(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_9407)
static void C_ccall f_9407(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9415)
static void C_fcall f_9415(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_9438)
static void C_ccall f_9438(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9441)
static void C_ccall f_9441(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9444)
static void C_ccall f_9444(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9447)
static void C_ccall f_9447(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9507)
static void C_ccall f_9507(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9514)
static void C_ccall f_9514(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9524)
static void C_ccall f_9524(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9534)
static void C_ccall f_9534(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9548)
static void C_ccall f_9548(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9558)
static void C_ccall f_9558(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9568)
static void C_ccall f_9568(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9578)
static void C_ccall f_9578(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9450)
static void C_fcall f_9450(C_word t0,C_word t1) C_noret;
C_noret_decl(f_9474)
static void C_fcall f_9474(C_word t0,C_word t1) C_noret;
C_noret_decl(f_9453)
static void C_fcall f_9453(C_word t0,C_word t1) C_noret;
C_noret_decl(f_9360)
static void C_ccall f_9360(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_9393)
static void C_ccall f_9393(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9354)
static void C_ccall f_9354(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4728)
static void C_ccall f_4728(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9272)
static void C_ccall f_9272(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_9276)
static void C_ccall f_9276(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9282)
static void C_ccall f_9282(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9302)
static void C_ccall f_9302(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9246)
static void C_ccall f_9246(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_9256)
static void C_fcall f_9256(C_word t0,C_word t1) C_noret;
C_noret_decl(f_9240)
static void C_ccall f_9240(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4731)
static void C_ccall f_4731(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9117)
static void C_ccall f_9117(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_9121)
static void C_ccall f_9121(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9049)
static void C_ccall f_9049(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_9068)
static void C_ccall f_9068(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9103)
static void C_ccall f_9103(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9074)
static void C_fcall f_9074(C_word t0,C_word t1) C_noret;
C_noret_decl(f_9078)
static void C_ccall f_9078(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9092)
static void C_ccall f_9092(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9081)
static void C_fcall f_9081(C_word t0,C_word t1) C_noret;
C_noret_decl(f_9062)
static void C_fcall f_9062(C_word t0,C_word t1) C_noret;
C_noret_decl(f_9043)
static void C_ccall f_9043(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4734)
static void C_ccall f_4734(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8771)
static void C_ccall f_8771(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5257)
static void C_ccall f_5257(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8723)
static void C_ccall f_8723(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8715)
static void C_ccall f_8715(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5260)
static void C_ccall f_5260(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8595)
static void C_ccall f_8595(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_5266)
static void C_ccall f_5266(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5738)
static void C_ccall f_5738(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5772)
static void C_ccall f_5772(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5764)
static void C_ccall f_5764(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5760)
static void C_ccall f_5760(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5745)
static void C_ccall f_5745(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5749)
static void C_ccall f_5749(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5742)
static void C_ccall f_5742(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5284)
static void C_fcall f_5284(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5731)
static void C_ccall f_5731(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5727)
static void C_ccall f_5727(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5291)
static void C_fcall f_5291(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5602)
static void C_fcall f_5602(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_5623)
static void C_ccall f_5623(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5625)
static void C_fcall f_5625(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_5639)
static void C_ccall f_5639(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5692)
static void C_ccall f_5692(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5642)
static void C_fcall f_5642(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5677)
static void C_ccall f_5677(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5645)
static void C_fcall f_5645(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5658)
static void C_ccall f_5658(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5670)
static void C_ccall f_5670(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5662)
static void C_ccall f_5662(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5648)
static void C_fcall f_5648(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5612)
static void C_ccall f_5612(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5294)
static void C_ccall f_5294(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5566)
static void C_fcall f_5566(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_5592)
static void C_ccall f_5592(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5577)
static void C_ccall f_5577(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5297)
static void C_ccall f_5297(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5301)
static void C_ccall f_5301(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5510)
static void C_fcall f_5510(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_5520)
static void C_ccall f_5520(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5523)
static void C_ccall f_5523(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5544)
static void C_ccall f_5544(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5526)
static void C_fcall f_5526(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5530)
static void C_ccall f_5530(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5304)
static void C_ccall f_5304(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5307)
static void C_fcall f_5307(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5473)
static void C_ccall f_5473(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5481)
static void C_ccall f_5481(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5477)
static void C_ccall f_5477(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5310)
static void C_fcall f_5310(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5338)
static void C_ccall f_5338(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5341)
static void C_ccall f_5341(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5344)
static void C_ccall f_5344(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5347)
static void C_ccall f_5347(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5406)
static void C_ccall f_5406(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8549)
static void C_ccall f_8549(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_8565)
static void C_ccall f_8565(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8568)
static void C_ccall f_8568(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8571)
static void C_fcall f_8571(C_word t0,C_word t1) C_noret;
C_noret_decl(f_8574)
static void C_fcall f_8574(C_word t0,C_word t1) C_noret;
C_noret_decl(f_8585)
static void C_ccall f_8585(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8543)
static void C_ccall f_8543(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5779)
static void C_ccall f_5779(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8404)
static void C_ccall f_8404(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_8443)
static void C_ccall f_8443(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8417)
static void C_fcall f_8417(C_word t0,C_word t1) C_noret;
C_noret_decl(f_8398)
static void C_ccall f_8398(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5782)
static void C_ccall f_5782(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7986)
static void C_ccall f_7986(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_7990)
static void C_ccall f_7990(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8002)
static void C_ccall f_8002(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8060)
static void C_ccall f_8060(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8063)
static void C_ccall f_8063(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8066)
static void C_ccall f_8066(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8278)
static void C_ccall f_8278(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8216)
static void C_ccall f_8216(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8250)
static void C_ccall f_8250(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8225)
static void C_fcall f_8225(C_word t0,C_word t1) C_noret;
C_noret_decl(f_8236)
static void C_ccall f_8236(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8232)
static void C_ccall f_8232(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8075)
static void C_fcall f_8075(C_word t0,C_word t1) C_noret;
C_noret_decl(f_8153)
static void C_ccall f_8153(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8194)
static void C_ccall f_8194(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8198)
static void C_ccall f_8198(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8202)
static void C_ccall f_8202(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8157)
static void C_ccall f_8157(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8161)
static void C_ccall f_8161(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8188)
static void C_ccall f_8188(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8164)
static void C_fcall f_8164(C_word t0,C_word t1) C_noret;
C_noret_decl(f_8078)
static void C_fcall f_8078(C_word t0,C_word t1) C_noret;
C_noret_decl(f_8150)
static void C_ccall f_8150(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8092)
static void C_ccall f_8092(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8094)
static void C_fcall f_8094(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_8142)
static void C_ccall f_8142(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8113)
static void C_ccall f_8113(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8130)
static void C_ccall f_8130(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8116)
static void C_fcall f_8116(C_word t0,C_word t1) C_noret;
C_noret_decl(f_8109)
static void C_ccall f_8109(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8081)
static void C_ccall f_8081(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8011)
static void C_fcall f_8011(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_8021)
static void C_ccall f_8021(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8027)
static void C_ccall f_8027(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7999)
static void C_ccall f_7999(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7947)
static void C_ccall f_7947(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_7964)
static void C_ccall f_7964(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7980)
static void C_ccall f_7980(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7958)
static void C_fcall f_7958(C_word t0,C_word t1) C_noret;
C_noret_decl(f_7941)
static void C_ccall f_7941(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5785)
static void C_ccall f_5785(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7865)
static void C_ccall f_7865(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5788)
static void C_ccall f_5788(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7841)
static void C_ccall f_7841(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_7853)
static void C_ccall f_7853(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7849)
static void C_ccall f_7849(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7827)
static void C_ccall f_7827(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_7835)
static void C_ccall f_7835(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7821)
static void C_ccall f_7821(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5791)
static void C_ccall f_5791(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6943)
static void C_ccall f_6943(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7767)
static void C_ccall f_7767(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_7814)
static void C_ccall f_7814(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7804)
static void C_ccall f_7804(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7771)
static void C_ccall f_7771(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6946)
static void C_ccall f_6946(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7761)
static void C_ccall f_7761(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_7761)
static void C_ccall f_7761r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_7219)
static void C_ccall f_7219(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7270)
static void C_ccall f_7270(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7273)
static void C_ccall f_7273(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7276)
static void C_ccall f_7276(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7279)
static void C_ccall f_7279(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7282)
static void C_ccall f_7282(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7285)
static void C_ccall f_7285(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7288)
static void C_ccall f_7288(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7291)
static void C_ccall f_7291(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7755)
static void C_ccall f_7755(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_7755)
static void C_ccall f_7755r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_7309)
static void C_ccall f_7309(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7312)
static void C_ccall f_7312(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7590)
static void C_fcall f_7590(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_7698)
static void C_ccall f_7698(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7610)
static void C_fcall f_7610(C_word t0,C_word t1) C_noret;
C_noret_decl(f_7619)
static void C_fcall f_7619(C_word t0,C_word t1) C_noret;
C_noret_decl(f_7623)
static void C_ccall f_7623(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7627)
static void C_ccall f_7627(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7635)
static void C_fcall f_7635(C_word t0,C_word t1) C_noret;
C_noret_decl(f_7631)
static void C_ccall f_7631(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7600)
static void C_ccall f_7600(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7315)
static void C_ccall f_7315(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7318)
static void C_ccall f_7318(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7321)
static void C_ccall f_7321(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7324)
static void C_ccall f_7324(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7327)
static void C_ccall f_7327(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7584)
static void C_ccall f_7584(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7483)
static void C_fcall f_7483(C_word t0,C_word t1) C_noret;
C_noret_decl(f_7490)
static void C_ccall f_7490(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7492)
static void C_fcall f_7492(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_7564)
static void C_ccall f_7564(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7516)
static void C_fcall f_7516(C_word t0,C_word t1) C_noret;
C_noret_decl(f_7519)
static void C_ccall f_7519(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7540)
static void C_ccall f_7540(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7506)
static void C_ccall f_7506(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7330)
static void C_ccall f_7330(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7472)
static void C_ccall f_7472(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7460)
static void C_ccall f_7460(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7456)
static void C_ccall f_7456(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7337)
static void C_fcall f_7337(C_word t0,C_word t1) C_noret;
C_noret_decl(f_7294)
static void C_ccall f_7294(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7753)
static void C_ccall f_7753(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7263)
static void C_ccall f_7263(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_7257)
static void C_ccall f_7257(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_7251)
static void C_ccall f_7251(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7245)
static void C_ccall f_7245(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_7239)
static void C_ccall f_7239(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_7233)
static void C_ccall f_7233(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_7227)
static void C_ccall f_7227(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_7221)
static void C_ccall f_7221(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_6485)
static void C_ccall f_6485(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6948)
static void C_ccall f_6948(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_6958)
static void C_ccall f_6958(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7189)
static void C_ccall f_7189(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6961)
static void C_ccall f_6961(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6964)
static void C_ccall f_6964(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6976)
static void C_ccall f_6976(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7024)
static void C_fcall f_7024(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_7040)
static void C_ccall f_7040(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7050)
static void C_ccall f_7050(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7167)
static void C_ccall f_7167(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7155)
static void C_ccall f_7155(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_7153)
static void C_ccall f_7153(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7140)
static void C_ccall f_7140(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7094)
static void C_ccall f_7094(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7121)
static void C_ccall f_7121(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7100)
static void C_ccall f_7100(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7034)
static void C_fcall f_7034(C_word t0,C_word t1) C_noret;
C_noret_decl(f_6979)
static void C_ccall f_6979(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6984)
static void C_fcall f_6984(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6997)
static void C_fcall f_6997(C_word t0,C_word t1) C_noret;
C_noret_decl(f_7206)
static void C_ccall f_7206(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_7197)
static void C_ccall f_7197(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_7205)
static void C_ccall f_7205(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7208)
static void C_ccall f_7208(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_7208)
static void C_ccall f_7208r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_7216)
static void C_ccall f_7216(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6932)
static void C_ccall f_6932(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6595)
static void C_ccall f_6595(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6936)
static void C_ccall f_6936(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6874)
static void C_ccall f_6874(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_6874)
static void C_ccall f_6874r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_6892)
static void C_fcall f_6892(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6902)
static void C_ccall f_6902(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6878)
static void C_ccall f_6878(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6865)
static void C_ccall f_6865(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6573)
static void C_ccall f_6573(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6869)
static void C_ccall f_6869(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6859)
static void C_ccall f_6859(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6555)
static void C_ccall f_6555(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6850)
static void C_ccall f_6850(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6564)
static void C_ccall f_6564(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6854)
static void C_ccall f_6854(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6787)
static void C_ccall f_6787(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_6787)
static void C_ccall f_6787r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_6812)
static void C_fcall f_6812(C_word t0,C_word t1) C_noret;
C_noret_decl(f_6520)
static void C_ccall f_6520(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6800)
static void C_ccall f_6800(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6619)
static void C_ccall f_6619(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_6619)
static void C_ccall f_6619r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_6738)
static void C_fcall f_6738(C_word t0,C_word t1) C_noret;
C_noret_decl(f_6733)
static void C_fcall f_6733(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6621)
static void C_fcall f_6621(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_6728)
static void C_ccall f_6728(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6732)
static void C_ccall f_6732(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6724)
static void C_ccall f_6724(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6692)
static void C_fcall f_6692(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6717)
static void C_ccall f_6717(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6721)
static void C_ccall f_6721(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6702)
static void C_ccall f_6702(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6681)
static void C_ccall f_6681(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6651)
static void C_fcall f_6651(C_word t0,C_word t1) C_noret;
C_noret_decl(f_6623)
static void C_fcall f_6623(C_word t0,C_word t1) C_noret;
C_noret_decl(f_6600)
static void C_ccall f_6600(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6605)
static void C_ccall f_6605(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6610)
static void C_ccall f_6610(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6578)
static void C_fcall f_6578(C_word t0,C_word t1) C_noret;
C_noret_decl(f_6582)
static void C_ccall f_6582(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6534)
static void C_fcall f_6534(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_6538)
static void C_ccall f_6538(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6525)
static void C_fcall f_6525(C_word t0,C_word t1) C_noret;
C_noret_decl(f_6529)
static void C_ccall f_6529(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6513)
static void C_ccall f_6513(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6510)
static void C_ccall f_6510(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6467)
static void C_ccall f_6467(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6472)
static void C_ccall f_6472(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6453)
static void C_ccall f_6453(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6458)
static void C_ccall f_6458(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6424)
static void C_ccall f_6424(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_6424)
static void C_ccall f_6424r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_6433)
static void C_ccall f_6433(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6438)
static void C_ccall f_6438(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6413)
static void C_ccall f_6413(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6418)
static void C_ccall f_6418(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6373)
static void C_ccall f_6373(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_6373)
static void C_ccall f_6373r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_6403)
static void C_ccall f_6403(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6325)
static void C_ccall f_6325(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6359)
static void C_ccall f_6359(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6305)
static void C_ccall f_6305(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6285)
static void C_ccall f_6285(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6271)
static void C_ccall f_6271(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6261)
static void C_ccall f_6261(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6251)
static void C_ccall f_6251(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6241)
static void C_ccall f_6241(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6231)
static void C_ccall f_6231(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6209)
static void C_ccall f_6209(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_6203)
static void C_ccall f_6203(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_6156)
static void C_ccall f_6156(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6160)
static void C_ccall f_6160(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6176)
static void C_ccall f_6176(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6185)
static void C_ccall f_6185(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6163)
static void C_ccall f_6163(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6147)
static void C_ccall f_6147(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6151)
static void C_ccall f_6151(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5968)
static void C_ccall f_5968(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_5968)
static void C_ccall f_5968r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_6121)
static void C_fcall f_6121(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6134)
static void C_ccall f_6134(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6116)
static void C_ccall f_6116(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5971)
static void C_fcall f_5971(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6113)
static void C_ccall f_6113(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6097)
static void C_ccall f_6097(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6090)
static void C_ccall f_6090(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6086)
static void C_ccall f_6086(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5999)
static void C_ccall f_5999(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6007)
static void C_fcall f_6007(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6017)
static void C_ccall f_6017(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6020)
static void C_ccall f_6020(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6002)
static void C_ccall f_6002(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5797)
static void C_ccall f_5797(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_5803)
static void C_ccall f_5803(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5806)
static void C_fcall f_5806(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3609)
static void C_ccall f_3609(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_3622)
static void C_ccall f_3622(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_3629)
static void C_fcall f_3629(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3636)
static void C_ccall f_3636(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3615)
static void C_ccall f_3615(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5810)
static void C_ccall f_5810(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5844)
static void C_ccall f_5844(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5937)
static void C_fcall f_5937(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_5947)
static void C_fcall f_5947(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5850)
static void C_ccall f_5850(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5907)
static void C_fcall f_5907(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_5917)
static void C_fcall f_5917(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5858)
static void C_ccall f_5858(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5872)
static void C_ccall f_5872(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5876)
static void C_ccall f_5876(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5880)
static void C_ccall f_5880(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5884)
static void C_ccall f_5884(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5891)
static void C_ccall f_5891(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5868)
static void C_ccall f_5868(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5861)
static void C_ccall f_5861(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5813)
static void C_ccall f_5813(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4736)
static void C_ccall f_4736(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_4749)
static void C_ccall f_4749(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4799)
static void C_ccall f_4799(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4896)
static void C_ccall f_4896(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4964)
static void C_ccall f_4964(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5221)
static void C_ccall f_5221(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4971)
static void C_fcall f_4971(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5209)
static void C_ccall f_5209(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5160)
static void C_ccall f_5160(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5166)
static void C_ccall f_5166(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5190)
static void C_ccall f_5190(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5186)
static void C_ccall f_5186(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5174)
static void C_ccall f_5174(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4974)
static void C_fcall f_4974(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5136)
static void C_ccall f_5136(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5140)
static void C_ccall f_5140(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4977)
static void C_fcall f_4977(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5113)
static void C_ccall f_5113(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5117)
static void C_ccall f_5117(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4980)
static void C_fcall f_4980(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5090)
static void C_ccall f_5090(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5094)
static void C_ccall f_5094(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4983)
static void C_fcall f_4983(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5015)
static void C_ccall f_5015(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5033)
static void C_ccall f_5033(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5051)
static void C_ccall f_5051(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5069)
static void C_ccall f_5069(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4986)
static void C_fcall f_4986(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4990)
static void C_ccall f_4990(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4900)
static void C_ccall f_4900(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4904)
static void C_ccall f_4904(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4908)
static void C_ccall f_4908(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4803)
static void C_ccall f_4803(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4807)
static void C_ccall f_4807(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4811)
static void C_ccall f_4811(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4830)
static void C_ccall f_4830(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4834)
static void C_ccall f_4834(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4814)
static void C_fcall f_4814(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4818)
static void C_ccall f_4818(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4753)
static void C_ccall f_4753(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4757)
static void C_ccall f_4757(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4761)
static void C_ccall f_4761(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4743)
static void C_fcall f_4743(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4558)
static void C_fcall f_4558(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4570)
static void C_fcall f_4570(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4589)
static void C_ccall f_4589(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4607)
static void C_fcall f_4607(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_4639)
static void C_ccall f_4639(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4642)
static void C_fcall f_4642(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4635)
static void C_ccall f_4635(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4621)
static void C_ccall f_4621(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4592)
static void C_ccall f_4592(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4537)
static void C_fcall f_4537(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4544)
static void C_ccall f_4544(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4547)
static void C_ccall f_4547(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4553)
static void C_ccall f_4553(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4472)
static void C_fcall f_4472(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_4481)
static void C_fcall f_4481(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_4504)
static void C_ccall f_4504(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4494)
static void C_fcall f_4494(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4428)
static void C_fcall f_4428(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_4416)
static void C_fcall f_4416(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4314)
static void C_fcall f_4314(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4266)
static void C_fcall f_4266(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3647)
static void C_fcall f_3647(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_3651)
static void C_ccall f_3651(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3654)
static void C_ccall f_3654(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4080)
static void C_ccall f_4080(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4076)
static void C_ccall f_4076(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4072)
static void C_ccall f_4072(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3657)
static void C_fcall f_3657(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3780)
static void C_ccall f_3780(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3013)
static void C_ccall f_3013(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3786)
static void C_fcall f_3786(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3029)
static void C_ccall f_3029(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3874)
static void C_fcall f_3874(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3944)
static void C_ccall f_3944(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3045)
static void C_ccall f_3045(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3947)
static void C_fcall f_3947(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3077)
static void C_ccall f_3077(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4025)
static void C_fcall f_4025(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4051)
static void C_ccall f_4051(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_4045)
static void C_ccall f_4045(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4034)
static void C_ccall f_4034(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3976)
static void C_fcall f_3976(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3986)
static void C_ccall f_3986(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4012)
static void C_ccall f_4012(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_4006)
static void C_ccall f_4006(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3989)
static void C_ccall f_3989(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3999)
static void C_ccall f_3999(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3992)
static void C_fcall f_3992(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3953)
static void C_ccall f_3953(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3962)
static void C_ccall f_3962(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3956)
static void C_fcall f_3956(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3880)
static void C_ccall f_3880(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3898)
static void C_fcall f_3898(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_3931)
static void C_ccall f_3931(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_3917)
static void C_ccall f_3917(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3925)
static void C_ccall f_3925(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3908)
static void C_ccall f_3908(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3883)
static void C_ccall f_3883(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3795)
static void C_ccall f_3795(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3817)
static void C_fcall f_3817(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_3864)
static void C_ccall f_3864(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_3850)
static void C_ccall f_3850(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3858)
static void C_ccall f_3858(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3830)
static void C_ccall f_3830(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3833)
static void C_fcall f_3833(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3798)
static void C_ccall f_3798(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3815)
static void C_ccall f_3815(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3801)
static void C_fcall f_3801(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3672)
static void C_ccall f_3672(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3730)
static void C_ccall f_3730(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3733)
static void C_ccall f_3733(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3754)
static void C_ccall f_3754(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_3765)
static void C_ccall f_3765(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3744)
static void C_ccall f_3744(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3678)
static void C_ccall f_3678(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3688)
static void C_ccall f_3688(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3724)
static void C_ccall f_3724(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3694)
static void C_ccall f_3694(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3709)
static void C_ccall f_3709(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3713)
static void C_ccall f_3713(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3717)
static void C_ccall f_3717(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3701)
static void C_ccall f_3701(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3543)
static void C_fcall f_3543(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3545)
static void C_ccall f_3545(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_3593)
static void C_ccall f_3593(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3549)
static void C_ccall f_3549(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3552)
static void C_fcall f_3552(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3557)
static void C_fcall f_3557(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_3578)
static void C_ccall f_3578(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3535)
static void C_fcall f_3535(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3537)
static void C_ccall f_3537(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_3327)
static void C_fcall f_3327(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_3344)
static void C_ccall f_3344(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3348)
static void C_ccall f_3348(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3294)
static void C_fcall f_3294(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_3301)
static void C_ccall f_3301(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3245)
static void C_ccall f_3245(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3252)
static void C_ccall f_3252(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3310)
static void C_ccall f_3310(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3533)
static void C_ccall f_3533(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3510)
static void C_ccall f_3510(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3526)
static void C_ccall f_3526(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3372)
static void C_ccall f_3372(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3375)
static void C_ccall f_3375(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3399)
static void C_ccall f_3399(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3456)
static void C_ccall f_3456(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3462)
static void C_ccall f_3462(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3471)
static void C_ccall f_3471(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3480)
static void C_ccall f_3480(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3489)
static void C_ccall f_3489(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3498)
static void C_ccall f_3498(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3450)
static void C_ccall f_3450(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3405)
static void C_ccall f_3405(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3411)
static void C_ccall f_3411(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3417)
static void C_ccall f_3417(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3423)
static void C_ccall f_3423(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3429)
static void C_ccall f_3429(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3435)
static void C_ccall f_3435(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3276)
static void C_fcall f_3276(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_3283)
static void C_ccall f_3283(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3266)
static void C_fcall f_3266(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_3254)
static void C_fcall f_3254(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_3222)
static void C_fcall f_3222(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_3229)
static void C_ccall f_3229(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3236)
static void C_ccall f_3236(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3206)
static void C_fcall f_3206(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3213)
static void C_ccall f_3213(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3220)
static void C_ccall f_3220(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3194)
static void C_fcall f_3194(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3176)
static void C_fcall f_3176(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3158)
static void C_fcall f_3158(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3143)
static void C_fcall f_3143(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3137)
static void C_fcall f_3137(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_3125)
static void C_fcall f_3125(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3107)
static void C_fcall f_3107(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3086)
static void C_fcall f_3086(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_3054)
static void C_fcall f_3054(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3061)
static void C_ccall f_3061(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2996)
static void C_fcall f_2996(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_3004)
static void C_ccall f_3004(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2986)
static void C_fcall f_2986(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2994)
static void C_ccall f_2994(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2980)
static void C_fcall f_2980(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2968)
static void C_fcall f_2968(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2944)
static void C_fcall f_2944(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2860)
static void C_fcall f_2860(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2839)
static void C_fcall f_2839(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_2829)
static void C_fcall f_2829(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2817)
static void C_fcall f_2817(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2788)
static void C_ccall f_2788(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2776)
static void C_fcall f_2776(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2758)
static void C_fcall f_2758(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2740)
static void C_fcall f_2740(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2719)
static void C_ccall f_2719(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_2713)
static void C_ccall f_2713(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2707)
static void C_ccall f_2707(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2688)
static void C_ccall f_2688(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_2688)
static void C_ccall f_2688r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_2669)
static void C_ccall f_2669(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_2669)
static void C_ccall f_2669r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_2663)
static void C_ccall f_2663(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2623)
static void C_ccall f_2623(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_2623)
static void C_ccall f_2623r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_2604)
static void C_ccall f_2604(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_2604)
static void C_ccall f_2604r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_2560)
static void C_ccall f_2560(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_2560)
static void C_ccall f_2560r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_2554)
static void C_ccall f_2554(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2548)
static void C_ccall f_2548(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2542)
static void C_ccall f_2542(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2536)
static void C_ccall f_2536(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_2536)
static void C_ccall f_2536r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_2513)
static void C_ccall f_2513(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2530)
static void C_ccall f_2530(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2455)
static void C_ccall f_2455(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_2455)
static void C_ccall f_2455r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_2507)
static void C_ccall f_2507(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2491)
static void C_ccall f_2491(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2472)
static void C_ccall f_2472(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2367)
static void C_ccall f_2367(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_2367)
static void C_ccall f_2367r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_2413)
static void C_fcall f_2413(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2361)
static void C_ccall f_2361(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2302)
static void C_ccall f_2302(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_2302)
static void C_ccall f_2302r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_2315)
static void C_fcall f_2315(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_2351)
static void C_ccall f_2351(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2296)
static void C_ccall f_2296(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_2296)
static void C_ccall f_2296r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_2201)
static void C_ccall f_2201(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_2201)
static void C_ccall f_2201r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_2205)
static void C_ccall f_2205(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2208)
static void C_ccall f_2208(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2220)
static void C_fcall f_2220(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2242)
static void C_ccall f_2242(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2195)
static void C_ccall f_2195(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2189)
static void C_ccall f_2189(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2183)
static void C_ccall f_2183(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2177)
static void C_ccall f_2177(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2171)
static void C_ccall f_2171(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2111)
static void C_ccall f_2111(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_2111)
static void C_ccall f_2111r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_2123)
static void C_fcall f_2123(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2118)
static void C_fcall f_2118(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2113)
static void C_fcall f_2113(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_2092)
static void C_ccall f_2092(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_2092)
static void C_ccall f_2092r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_2086)
static void C_ccall f_2086(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_2080)
static void C_ccall f_2080(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1998)
static void C_ccall f_1998(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,...) C_noret;
C_noret_decl(f_1998)
static void C_ccall f_1998r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t7) C_noret;
C_noret_decl(f_2012)
static void C_ccall f_2012(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1979)
static void C_ccall f_1979(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,...) C_noret;
C_noret_decl(f_1979)
static void C_ccall f_1979r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t8) C_noret;
C_noret_decl(f_1966)
static void C_fcall f_1966(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1956)
static void C_fcall f_1956(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1945)
static void C_fcall f_1945(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1938)
static void C_fcall f_1938(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1927)
static void C_fcall f_1927(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1889)
static void C_fcall f_1889(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1882)
static void C_fcall f_1882(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1807)
static void C_fcall f_1807(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1773)
static void C_fcall f_1773(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_1746)
static void C_fcall f_1746(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;

C_noret_decl(trf_11901)
static void C_fcall trf_11901(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_11901(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_11901(t0,t1);}

C_noret_decl(trf_10783)
static void C_fcall trf_10783(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_10783(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_10783(t0,t1);}

C_noret_decl(trf_10656)
static void C_fcall trf_10656(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_10656(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_10656(t0,t1,t2);}

C_noret_decl(trf_10320)
static void C_fcall trf_10320(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_10320(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_10320(t0,t1);}

C_noret_decl(trf_9415)
static void C_fcall trf_9415(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_9415(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_9415(t0,t1,t2);}

C_noret_decl(trf_9450)
static void C_fcall trf_9450(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_9450(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_9450(t0,t1);}

C_noret_decl(trf_9474)
static void C_fcall trf_9474(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_9474(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_9474(t0,t1);}

C_noret_decl(trf_9453)
static void C_fcall trf_9453(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_9453(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_9453(t0,t1);}

C_noret_decl(trf_9256)
static void C_fcall trf_9256(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_9256(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_9256(t0,t1);}

C_noret_decl(trf_9074)
static void C_fcall trf_9074(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_9074(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_9074(t0,t1);}

C_noret_decl(trf_9081)
static void C_fcall trf_9081(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_9081(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_9081(t0,t1);}

C_noret_decl(trf_9062)
static void C_fcall trf_9062(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_9062(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_9062(t0,t1);}

C_noret_decl(trf_5284)
static void C_fcall trf_5284(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5284(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5284(t0,t1);}

C_noret_decl(trf_5291)
static void C_fcall trf_5291(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5291(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5291(t0,t1);}

C_noret_decl(trf_5602)
static void C_fcall trf_5602(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5602(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_5602(t0,t1,t2);}

C_noret_decl(trf_5625)
static void C_fcall trf_5625(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5625(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_5625(t0,t1,t2);}

C_noret_decl(trf_5642)
static void C_fcall trf_5642(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5642(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5642(t0,t1);}

C_noret_decl(trf_5645)
static void C_fcall trf_5645(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5645(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5645(t0,t1);}

C_noret_decl(trf_5648)
static void C_fcall trf_5648(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5648(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5648(t0,t1);}

C_noret_decl(trf_5566)
static void C_fcall trf_5566(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5566(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_5566(t0,t1,t2);}

C_noret_decl(trf_5510)
static void C_fcall trf_5510(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5510(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_5510(t0,t1,t2);}

C_noret_decl(trf_5526)
static void C_fcall trf_5526(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5526(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5526(t0,t1);}

C_noret_decl(trf_5307)
static void C_fcall trf_5307(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5307(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5307(t0,t1);}

C_noret_decl(trf_5310)
static void C_fcall trf_5310(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5310(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5310(t0,t1);}

C_noret_decl(trf_8571)
static void C_fcall trf_8571(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8571(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_8571(t0,t1);}

C_noret_decl(trf_8574)
static void C_fcall trf_8574(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8574(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_8574(t0,t1);}

C_noret_decl(trf_8417)
static void C_fcall trf_8417(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8417(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_8417(t0,t1);}

C_noret_decl(trf_8225)
static void C_fcall trf_8225(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8225(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_8225(t0,t1);}

C_noret_decl(trf_8075)
static void C_fcall trf_8075(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8075(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_8075(t0,t1);}

C_noret_decl(trf_8164)
static void C_fcall trf_8164(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8164(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_8164(t0,t1);}

C_noret_decl(trf_8078)
static void C_fcall trf_8078(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8078(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_8078(t0,t1);}

C_noret_decl(trf_8094)
static void C_fcall trf_8094(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8094(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_8094(t0,t1,t2,t3);}

C_noret_decl(trf_8116)
static void C_fcall trf_8116(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8116(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_8116(t0,t1);}

C_noret_decl(trf_8011)
static void C_fcall trf_8011(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8011(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_8011(t0,t1,t2);}

C_noret_decl(trf_7958)
static void C_fcall trf_7958(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7958(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_7958(t0,t1);}

C_noret_decl(trf_7590)
static void C_fcall trf_7590(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7590(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_7590(t0,t1,t2);}

C_noret_decl(trf_7610)
static void C_fcall trf_7610(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7610(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_7610(t0,t1);}

C_noret_decl(trf_7619)
static void C_fcall trf_7619(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7619(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_7619(t0,t1);}

C_noret_decl(trf_7635)
static void C_fcall trf_7635(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7635(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_7635(t0,t1);}

C_noret_decl(trf_7483)
static void C_fcall trf_7483(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7483(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_7483(t0,t1);}

C_noret_decl(trf_7492)
static void C_fcall trf_7492(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7492(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_7492(t0,t1,t2);}

C_noret_decl(trf_7516)
static void C_fcall trf_7516(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7516(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_7516(t0,t1);}

C_noret_decl(trf_7337)
static void C_fcall trf_7337(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7337(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_7337(t0,t1);}

C_noret_decl(trf_7024)
static void C_fcall trf_7024(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7024(void *dummy){
C_word t4=C_pick(0);
C_word t3=C_pick(1);
C_word t2=C_pick(2);
C_word t1=C_pick(3);
C_word t0=C_pick(4);
C_adjust_stack(-5);
f_7024(t0,t1,t2,t3,t4);}

C_noret_decl(trf_7034)
static void C_fcall trf_7034(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7034(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_7034(t0,t1);}

C_noret_decl(trf_6984)
static void C_fcall trf_6984(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6984(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_6984(t0,t1,t2);}

C_noret_decl(trf_6997)
static void C_fcall trf_6997(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6997(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_6997(t0,t1);}

C_noret_decl(trf_6892)
static void C_fcall trf_6892(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6892(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_6892(t0,t1,t2);}

C_noret_decl(trf_6812)
static void C_fcall trf_6812(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6812(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_6812(t0,t1);}

C_noret_decl(trf_6738)
static void C_fcall trf_6738(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6738(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_6738(t0,t1);}

C_noret_decl(trf_6733)
static void C_fcall trf_6733(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6733(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_6733(t0,t1,t2);}

C_noret_decl(trf_6621)
static void C_fcall trf_6621(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6621(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_6621(t0,t1,t2,t3);}

C_noret_decl(trf_6692)
static void C_fcall trf_6692(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6692(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_6692(t0,t1,t2);}

C_noret_decl(trf_6651)
static void C_fcall trf_6651(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6651(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_6651(t0,t1);}

C_noret_decl(trf_6623)
static void C_fcall trf_6623(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6623(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_6623(t0,t1);}

C_noret_decl(trf_6578)
static void C_fcall trf_6578(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6578(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_6578(t0,t1);}

C_noret_decl(trf_6534)
static void C_fcall trf_6534(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6534(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_6534(t0,t1,t2,t3);}

C_noret_decl(trf_6525)
static void C_fcall trf_6525(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6525(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_6525(t0,t1);}

C_noret_decl(trf_6121)
static void C_fcall trf_6121(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6121(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_6121(t0,t1,t2);}

C_noret_decl(trf_5971)
static void C_fcall trf_5971(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5971(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_5971(t0,t1,t2);}

C_noret_decl(trf_6007)
static void C_fcall trf_6007(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6007(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_6007(t0,t1,t2);}

C_noret_decl(trf_5806)
static void C_fcall trf_5806(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5806(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5806(t0,t1);}

C_noret_decl(trf_3629)
static void C_fcall trf_3629(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3629(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3629(t0,t1);}

C_noret_decl(trf_5937)
static void C_fcall trf_5937(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5937(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_5937(t0,t1,t2);}

C_noret_decl(trf_5947)
static void C_fcall trf_5947(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5947(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5947(t0,t1);}

C_noret_decl(trf_5907)
static void C_fcall trf_5907(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5907(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_5907(t0,t1,t2);}

C_noret_decl(trf_5917)
static void C_fcall trf_5917(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5917(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5917(t0,t1);}

C_noret_decl(trf_4971)
static void C_fcall trf_4971(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4971(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4971(t0,t1);}

C_noret_decl(trf_4974)
static void C_fcall trf_4974(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4974(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4974(t0,t1);}

C_noret_decl(trf_4977)
static void C_fcall trf_4977(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4977(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4977(t0,t1);}

C_noret_decl(trf_4980)
static void C_fcall trf_4980(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4980(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4980(t0,t1);}

C_noret_decl(trf_4983)
static void C_fcall trf_4983(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4983(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4983(t0,t1);}

C_noret_decl(trf_4986)
static void C_fcall trf_4986(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4986(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4986(t0,t1);}

C_noret_decl(trf_4814)
static void C_fcall trf_4814(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4814(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4814(t0,t1);}

C_noret_decl(trf_4743)
static void C_fcall trf_4743(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4743(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4743(t0,t1);}

C_noret_decl(trf_4558)
static void C_fcall trf_4558(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4558(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4558(t0,t1);}

C_noret_decl(trf_4570)
static void C_fcall trf_4570(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4570(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4570(t0,t1);}

C_noret_decl(trf_4607)
static void C_fcall trf_4607(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4607(void *dummy){
C_word t4=C_pick(0);
C_word t3=C_pick(1);
C_word t2=C_pick(2);
C_word t1=C_pick(3);
C_word t0=C_pick(4);
C_adjust_stack(-5);
f_4607(t0,t1,t2,t3,t4);}

C_noret_decl(trf_4642)
static void C_fcall trf_4642(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4642(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4642(t0,t1);}

C_noret_decl(trf_4537)
static void C_fcall trf_4537(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4537(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4537(t0,t1);}

C_noret_decl(trf_4472)
static void C_fcall trf_4472(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4472(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_4472(t0,t1,t2);}

C_noret_decl(trf_4481)
static void C_fcall trf_4481(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4481(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_4481(t0,t1,t2);}

C_noret_decl(trf_4494)
static void C_fcall trf_4494(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4494(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4494(t0,t1);}

C_noret_decl(trf_4428)
static void C_fcall trf_4428(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4428(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_4428(t0,t1,t2);}

C_noret_decl(trf_4416)
static void C_fcall trf_4416(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4416(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4416(t0,t1);}

C_noret_decl(trf_4314)
static void C_fcall trf_4314(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4314(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4314(t0,t1);}

C_noret_decl(trf_4266)
static void C_fcall trf_4266(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4266(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4266(t0,t1);}

C_noret_decl(trf_3647)
static void C_fcall trf_3647(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3647(void *dummy){
C_word t6=C_pick(0);
C_word t5=C_pick(1);
C_word t4=C_pick(2);
C_word t3=C_pick(3);
C_word t2=C_pick(4);
C_word t1=C_pick(5);
C_word t0=C_pick(6);
C_adjust_stack(-7);
f_3647(t0,t1,t2,t3,t4,t5,t6);}

C_noret_decl(trf_3657)
static void C_fcall trf_3657(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3657(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3657(t0,t1);}

C_noret_decl(trf_3786)
static void C_fcall trf_3786(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3786(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3786(t0,t1);}

C_noret_decl(trf_3874)
static void C_fcall trf_3874(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3874(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3874(t0,t1);}

C_noret_decl(trf_3947)
static void C_fcall trf_3947(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3947(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3947(t0,t1);}

C_noret_decl(trf_4025)
static void C_fcall trf_4025(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4025(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4025(t0,t1);}

C_noret_decl(trf_3976)
static void C_fcall trf_3976(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3976(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3976(t0,t1);}

C_noret_decl(trf_3992)
static void C_fcall trf_3992(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3992(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3992(t0,t1);}

C_noret_decl(trf_3956)
static void C_fcall trf_3956(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3956(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3956(t0,t1);}

C_noret_decl(trf_3898)
static void C_fcall trf_3898(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3898(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_3898(t0,t1,t2);}

C_noret_decl(trf_3817)
static void C_fcall trf_3817(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3817(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_3817(t0,t1,t2);}

C_noret_decl(trf_3833)
static void C_fcall trf_3833(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3833(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3833(t0,t1);}

C_noret_decl(trf_3801)
static void C_fcall trf_3801(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3801(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3801(t0,t1);}

C_noret_decl(trf_3543)
static void C_fcall trf_3543(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3543(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3543(t0,t1);}

C_noret_decl(trf_3552)
static void C_fcall trf_3552(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3552(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3552(t0,t1);}

C_noret_decl(trf_3557)
static void C_fcall trf_3557(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3557(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_3557(t0,t1,t2);}

C_noret_decl(trf_3535)
static void C_fcall trf_3535(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3535(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3535(t0,t1);}

C_noret_decl(trf_3327)
static void C_fcall trf_3327(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3327(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_3327(t0,t1,t2,t3);}

C_noret_decl(trf_3294)
static void C_fcall trf_3294(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3294(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_3294(t0,t1,t2,t3);}

C_noret_decl(trf_3276)
static void C_fcall trf_3276(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3276(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_3276(t0,t1,t2,t3);}

C_noret_decl(trf_3266)
static void C_fcall trf_3266(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3266(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_3266(t0,t1,t2,t3);}

C_noret_decl(trf_3254)
static void C_fcall trf_3254(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3254(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_3254(t0,t1,t2);}

C_noret_decl(trf_3222)
static void C_fcall trf_3222(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3222(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_3222(t0,t1,t2);}

C_noret_decl(trf_3206)
static void C_fcall trf_3206(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3206(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3206(t0,t1);}

C_noret_decl(trf_3194)
static void C_fcall trf_3194(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3194(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3194(t0,t1);}

C_noret_decl(trf_3176)
static void C_fcall trf_3176(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3176(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3176(t0,t1);}

C_noret_decl(trf_3158)
static void C_fcall trf_3158(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3158(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3158(t0,t1);}

C_noret_decl(trf_3143)
static void C_fcall trf_3143(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3143(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3143(t0,t1);}

C_noret_decl(trf_3137)
static void C_fcall trf_3137(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3137(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_3137(t0,t1,t2,t3);}

C_noret_decl(trf_3125)
static void C_fcall trf_3125(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3125(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3125(t0,t1);}

C_noret_decl(trf_3107)
static void C_fcall trf_3107(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3107(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3107(t0,t1);}

C_noret_decl(trf_3086)
static void C_fcall trf_3086(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3086(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_3086(t0,t1,t2);}

C_noret_decl(trf_3054)
static void C_fcall trf_3054(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3054(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3054(t0,t1);}

C_noret_decl(trf_2996)
static void C_fcall trf_2996(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2996(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_2996(t0,t1,t2);}

C_noret_decl(trf_2986)
static void C_fcall trf_2986(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2986(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2986(t0,t1);}

C_noret_decl(trf_2980)
static void C_fcall trf_2980(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2980(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2980(t0,t1);}

C_noret_decl(trf_2968)
static void C_fcall trf_2968(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2968(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2968(t0,t1);}

C_noret_decl(trf_2944)
static void C_fcall trf_2944(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2944(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_2944(t0,t1,t2);}

C_noret_decl(trf_2860)
static void C_fcall trf_2860(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2860(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2860(t0,t1);}

C_noret_decl(trf_2839)
static void C_fcall trf_2839(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2839(void *dummy){
C_word t5=C_pick(0);
C_word t4=C_pick(1);
C_word t3=C_pick(2);
C_word t2=C_pick(3);
C_word t1=C_pick(4);
C_word t0=C_pick(5);
C_adjust_stack(-6);
f_2839(t0,t1,t2,t3,t4,t5);}

C_noret_decl(trf_2829)
static void C_fcall trf_2829(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2829(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2829(t0,t1);}

C_noret_decl(trf_2817)
static void C_fcall trf_2817(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2817(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2817(t0,t1);}

C_noret_decl(trf_2776)
static void C_fcall trf_2776(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2776(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2776(t0,t1);}

C_noret_decl(trf_2758)
static void C_fcall trf_2758(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2758(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2758(t0,t1);}

C_noret_decl(trf_2740)
static void C_fcall trf_2740(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2740(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2740(t0,t1);}

C_noret_decl(trf_2413)
static void C_fcall trf_2413(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2413(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2413(t0,t1);}

C_noret_decl(trf_2315)
static void C_fcall trf_2315(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2315(void *dummy){
C_word t5=C_pick(0);
C_word t4=C_pick(1);
C_word t3=C_pick(2);
C_word t2=C_pick(3);
C_word t1=C_pick(4);
C_word t0=C_pick(5);
C_adjust_stack(-6);
f_2315(t0,t1,t2,t3,t4,t5);}

C_noret_decl(trf_2220)
static void C_fcall trf_2220(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2220(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_2220(t0,t1,t2);}

C_noret_decl(trf_2123)
static void C_fcall trf_2123(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2123(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2123(t0,t1);}

C_noret_decl(trf_2118)
static void C_fcall trf_2118(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2118(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_2118(t0,t1,t2);}

C_noret_decl(trf_2113)
static void C_fcall trf_2113(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2113(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_2113(t0,t1,t2,t3);}

C_noret_decl(trf_1966)
static void C_fcall trf_1966(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1966(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1966(t0,t1);}

C_noret_decl(trf_1956)
static void C_fcall trf_1956(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1956(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1956(t0,t1);}

C_noret_decl(trf_1945)
static void C_fcall trf_1945(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1945(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1945(t0,t1,t2);}

C_noret_decl(trf_1938)
static void C_fcall trf_1938(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1938(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1938(t0,t1);}

C_noret_decl(trf_1927)
static void C_fcall trf_1927(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1927(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1927(t0,t1,t2);}

C_noret_decl(trf_1889)
static void C_fcall trf_1889(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1889(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1889(t0,t1);}

C_noret_decl(trf_1882)
static void C_fcall trf_1882(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1882(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1882(t0,t1);}

C_noret_decl(trf_1807)
static void C_fcall trf_1807(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1807(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1807(t0,t1,t2);}

C_noret_decl(trf_1773)
static void C_fcall trf_1773(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1773(void *dummy){
C_word t6=C_pick(0);
C_word t5=C_pick(1);
C_word t4=C_pick(2);
C_word t3=C_pick(3);
C_word t2=C_pick(4);
C_word t1=C_pick(5);
C_word t0=C_pick(6);
C_adjust_stack(-7);
f_1773(t0,t1,t2,t3,t4,t5,t6);}

C_noret_decl(trf_1746)
static void C_fcall trf_1746(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1746(void *dummy){
C_word t6=C_pick(0);
C_word t5=C_pick(1);
C_word t4=C_pick(2);
C_word t3=C_pick(3);
C_word t2=C_pick(4);
C_word t1=C_pick(5);
C_word t0=C_pick(6);
C_adjust_stack(-7);
f_1746(t0,t1,t2,t3,t4,t5,t6);}

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
C_initialize_lf(lf,646);
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
lf[189]=C_static_lambda_info(C_heaptop,24,"(f_3537 args468 errf469)");
lf[190]=C_static_lambda_info(C_heaptop,28,"(simple-unit-parser type467)");
lf[192]=C_static_lambda_info(C_heaptop,15,"(do477 tail479)");
lf[193]=C_h_intern(&lf[193],6,"append");
lf[194]=C_static_lambda_info(C_heaptop,32,"(f_3545 unit471 info472 errf473)");
lf[195]=C_static_lambda_info(C_heaptop,29,"(simple-unit-emitter func470)");
lf[198]=C_static_lambda_info(C_heaptop,7,"(a3743)");
lf[199]=C_static_lambda_info(C_heaptop,22,"(a3753 a509 b510 c511)");
lf[200]=C_static_string(C_heaptop,29,"Not a token type or rule type");
lf[201]=C_h_intern(&lf[201],7,"reverse");
lf[202]=C_static_lambda_info(C_heaptop,7,"(a3849)");
lf[203]=C_static_lambda_info(C_heaptop,22,"(a3863 a525 b526 c527)");
lf[204]=C_static_lambda_info(C_heaptop,12,"(do520 i522)");
lf[205]=C_static_lambda_info(C_heaptop,7,"(a3916)");
lf[206]=C_static_lambda_info(C_heaptop,22,"(a3930 a547 b548 c549)");
lf[207]=C_static_lambda_info(C_heaptop,12,"(do542 i544)");
lf[208]=C_static_lambda_info(C_heaptop,7,"(a4005)");
lf[209]=C_static_lambda_info(C_heaptop,22,"(a4011 a566 b567 c568)");
lf[210]=C_static_lambda_info(C_heaptop,7,"(do562)");
lf[211]=C_static_lambda_info(C_heaptop,7,"(a4044)");
lf[212]=C_static_lambda_info(C_heaptop,22,"(a4050 a584 b585 c586)");
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
lf[269]=C_static_lambda_info(C_heaptop,7,"(a3614)");
lf[270]=C_h_intern(&lf[270],7,"\000syntax");
lf[271]=C_h_intern(&lf[271],7,"\000scheme");
lf[272]=C_static_string(C_heaptop,19,"Illegal statement: ");
lf[273]=C_static_lambda_info(C_heaptop,40,"(a3621 success491 results492 remains493)");
lf[274]=C_static_lambda_info(C_heaptop,15,"(a3608 errf489)");
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
lf[338]=C_static_lambda_info(C_heaptop,8,"(f_6418)");
lf[339]=C_static_lambda_info(C_heaptop,19,"(current-directory)");
lf[340]=C_static_string(C_heaptop,2,"~/");
lf[341]=C_h_intern(&lf[341],17,"\003sysmake-c-string");
lf[342]=C_static_lambda_info(C_heaptop,18,"(f_6433 a14061410)");
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
lf[360]=C_static_lambda_info(C_heaptop,18,"(f_6605 a14871491)");
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
lf[397]=C_static_lambda_info(C_heaptop,27,"(f_7208 str1558 . args1559)");
lf[398]=C_static_string(C_heaptop,3,"~A:");
lf[399]=C_h_intern(&lf[399],15,"keyword->string");
lf[400]=C_static_lambda_info(C_heaptop,14,"(f_7197 k1562)");
lf[401]=C_static_lambda_info(C_heaptop,14,"(f_7206 k1563)");
lf[402]=C_static_lambda_info(C_heaptop,17,"(do1590 tail1592)");
lf[403]=C_static_string(C_heaptop,25,"~S duplicate keyword \047~S\047");
lf[404]=C_static_string(C_heaptop,33,"~S missing value for keyword \047~A\047");
lf[405]=C_static_string(C_heaptop,47,"~S invalid keyword \047~A\047~%Available keywords: ~A");
lf[406]=C_static_lambda_info(C_heaptop,13,"(a7154 x1580)");
lf[407]=C_static_string(C_heaptop,32,"~S expected keyword but got \047~S\047");
lf[408]=C_h_intern(&lf[408],8,"keyword\077");
lf[409]=C_static_string(C_heaptop,35,"~S expected ~A arguments but got ~A");
lf[410]=C_static_lambda_info(C_heaptop,32,"(do1572 key1574 arg1575 pos1576)");
lf[411]=C_static_string(C_heaptop,24,"~S is an invalid message");
lf[412]=C_static_lambda_info(C_heaptop,7,"(a7188)");
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
lf[437]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[438]=C_static_lambda_info(C_heaptop,39,"(mp:inhook func1620 chans1621 mask1622)");
lf[439]=C_h_intern(&lf[439],14,"return-to-host");
lf[440]=C_h_intern(&lf[440],4,"else");
lf[441]=C_h_intern(&lf[441],4,"cond");
lf[442]=C_h_intern(&lf[442],6,"lambda");
lf[443]=C_h_intern(&lf[443],7,"elapsed");
lf[444]=C_h_intern(&lf[444],1,"x");
lf[445]=C_h_intern(&lf[445],4,"wait");
lf[446]=C_h_intern(&lf[446],4,"let*");
lf[447]=C_h_intern(&lf[447],5,"quote");
lf[448]=C_h_intern(&lf[448],3,"exn");
lf[449]=C_h_intern(&lf[449],7,"message");
lf[450]=C_h_intern(&lf[450],27,"condition-property-accessor");
lf[451]=C_static_string(C_heaptop,48,">>> Error: ~A~%    Aborting process at time ~S~%");
lf[452]=C_h_intern(&lf[452],22,"with-exception-handler");
lf[453]=C_h_intern(&lf[453],30,"call-with-current-continuation");
lf[454]=C_h_intern(&lf[454],10,"\003sysappend");
lf[455]=C_h_intern(&lf[455],6,"safety");
lf[456]=C_h_intern(&lf[456],4,"cdar");
lf[457]=C_static_string(C_heaptop,19,"unknown declaration");
lf[458]=C_h_intern(&lf[458],4,"caar");
lf[459]=C_static_string(C_heaptop,31,"declaration not list (decl val)");
lf[460]=C_static_lambda_info(C_heaptop,17,"(do1648 decl1650)");
lf[461]=C_h_intern(&lf[461],7,"declare");
lf[462]=C_h_intern(&lf[462],5,"\000null");
lf[463]=C_static_string(C_heaptop,41,"binding clause not list (var init [step])");
lf[464]=C_static_lambda_info(C_heaptop,17,"(do1632 tail1634)");
lf[465]=C_static_string(C_heaptop,36,"go stopping clause missing test form");
lf[466]=C_static_string(C_heaptop,29,"go stopping clause not a list");
lf[467]=C_static_string(C_heaptop,22,"go bindings not a list");
lf[468]=C_static_lambda_info(C_heaptop,45,"(a7754 bindings1623 terminate1624 . body1625)");
lf[469]=C_h_intern(&lf[469],18,"\003sysregister-macro");
lf[470]=C_h_intern(&lf[470],2,"go");
lf[471]=C_h_intern(&lf[471],15,"hash-table-set!");
lf[472]=C_static_string(C_heaptop,9,"mp:inhook");
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
lf[473]=C_h_list(4,C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(4);
lf[474]=C_static_string(C_heaptop,8,"mp:micro");
tmp=C_intern(C_heaptop,8,"mp:micro");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000divs");
C_save(tmp);
tmp=C_fix(1);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[475]=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
lf[476]=C_static_string(C_heaptop,9,"mp:alloff");
tmp=C_intern(C_heaptop,9,"mp:alloff");
C_save(tmp);
tmp=C_SCHEME_END_OF_LIST;
lf[477]=C_h_pair(C_restore,tmp);
lf[478]=C_static_string(C_heaptop,7,"mp:ctrl");
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
lf[479]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[480]=C_static_string(C_heaptop,7,"mp:prog");
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
lf[481]=C_h_list(4,C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(4);
lf[482]=C_static_string(C_heaptop,6,"mp:off");
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
lf[483]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[484]=C_static_string(C_heaptop,5,"mp:on");
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
lf[485]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[486]=C_static_string(C_heaptop,7,"mp:note");
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
lf[487]=C_h_list(6,C_pick(5),C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(6);
lf[488]=C_static_lambda_info(C_heaptop,27,"(a7760 mess1597 . data1598)");
lf[489]=C_h_intern(&lf[489],4,"send");
lf[490]=C_h_intern(&lf[490],10,"*messages*");
lf[491]=C_static_string(C_heaptop,51,"message function not string, symbol or list of both");
lf[492]=C_static_lambda_info(C_heaptop,25,"(a7766 func1546 info1547)");
lf[493]=C_h_intern(&lf[493],19,"define-send-message");
lf[494]=C_h_intern(&lf[494],15,"make-hash-table");
lf[495]=C_h_intern(&lf[495],6,"equal\077");
lf[496]=C_static_lambda_info(C_heaptop,25,"(a7826 args1202 errf1203)");
lf[497]=C_static_lambda_info(C_heaptop,34,"(a7840 unit1204 info1205 errf1206)");
lf[498]=C_static_string(C_heaptop,24,"SalStatementSequenceRule");
lf[499]=C_static_string(C_heaptop,16,"SalStatementRule");
lf[500]=C_static_lambda_info(C_heaptop,25,"(a7946 args1151 errf1152)");
lf[501]=C_h_intern(&lf[501],6,"define");
lf[502]=C_static_string(C_heaptop,15,"Variable: ~A = ");
lf[503]=C_static_lambda_info(C_heaptop,17,"(do1163 rest1165)");
lf[504]=C_static_string(C_heaptop,2,")\012");
lf[505]=C_static_string(C_heaptop,2,", ");
lf[506]=C_static_lambda_info(C_heaptop,26,"(do1189 args1191 tail1192)");
lf[507]=C_static_string(C_heaptop,2," (");
lf[508]=C_static_string(C_heaptop,10,"Function: ");
lf[509]=C_h_intern(&lf[509],7,"\000return");
lf[510]=C_h_intern(&lf[510],6,"return");
lf[511]=C_h_intern(&lf[511],9,"\000function");
lf[512]=C_static_string(C_heaptop,9,"Process: ");
lf[513]=C_h_intern(&lf[513],8,"\000process");
lf[514]=C_static_string(C_heaptop,3,"...");
lf[515]=C_static_lambda_info(C_heaptop,34,"(a7985 unit1156 info1157 errf1158)");
lf[516]=C_static_string(C_heaptop,22,"SalDefineStatementRule");
lf[517]=C_static_lambda_info(C_heaptop,25,"(a8403 args1144 errf1145)");
lf[518]=C_static_string(C_heaptop,14,"SalFunDeclRule");
lf[519]=C_static_lambda_info(C_heaptop,25,"(a8548 args1130 errf1131)");
lf[520]=C_static_string(C_heaptop,47,">>> Error: ~A~%    process aborted at time ~S~%");
lf[521]=C_static_string(C_heaptop,5,"abort");
lf[522]=C_static_string(C_heaptop,5,"error");
lf[523]=C_static_string(C_heaptop,4,"wait");
lf[524]=C_static_string(C_heaptop,4,"time");
lf[525]=C_h_intern(&lf[525],2,"do");
lf[526]=C_static_lambda_info(C_heaptop,17,"(do1108 tail1110)");
lf[527]=C_static_lambda_info(C_heaptop,17,"(do1103 tail1105)");
lf[528]=C_static_lambda_info(C_heaptop,20,"(do1092 clauses1094)");
lf[529]=C_static_lambda_info(C_heaptop,17,"(do1089 tail1091)");
lf[530]=C_h_intern(&lf[530],5,"\000loop");
lf[531]=C_h_intern(&lf[531],4,"\000run");
lf[532]=C_static_string(C_heaptop,29,"run statement outside process");
lf[533]=C_static_lambda_info(C_heaptop,34,"(a8594 unit1140 info1141 errf1142)");
lf[534]=C_static_string(C_heaptop,20,"SalLoopStatementRule");
lf[535]=C_static_string(C_heaptop,18,"SalTerminationRule");
lf[536]=C_static_string(C_heaptop,15,"SalSteppingRule");
lf[537]=C_static_string(C_heaptop,2,"#f");
lf[538]=C_static_string(C_heaptop,2,"#f");
lf[539]=C_static_lambda_info(C_heaptop,25,"(a9048 args1005 errf1006)");
lf[540]=C_static_lambda_info(C_heaptop,34,"(a9116 unit1017 info1018 errf1019)");
lf[541]=C_static_string(C_heaptop,18,"SalConditionalRule");
lf[542]=C_static_lambda_info(C_heaptop,23,"(a9245 args993 errf994)");
lf[543]=C_static_lambda_info(C_heaptop,32,"(a9271 unit998 info999 errf1000)");
lf[544]=C_static_string(C_heaptop,12,"SalBlockRule");
lf[545]=C_static_lambda_info(C_heaptop,23,"(a9359 args971 errf972)");
lf[546]=C_h_intern(&lf[546],9,"list-tail");
lf[547]=C_h_intern(&lf[547],8,"set-car!");
lf[548]=C_h_intern(&lf[548],8,"list-ref");
lf[549]=C_h_intern(&lf[549],4,"list");
lf[550]=C_h_intern(&lf[550],4,"cons");
lf[551]=C_h_intern(&lf[551],3,"min");
lf[552]=C_static_lambda_info(C_heaptop,15,"(do979 iter981)");
lf[553]=C_static_lambda_info(C_heaptop,31,"(a9402 unit973 info974 errf975)");
lf[554]=C_static_string(C_heaptop,17,"SalAssignmentRule");
lf[555]=C_static_lambda_info(C_heaptop,23,"(a9639 args968 errf969)");
lf[556]=C_static_string(C_heaptop,13,"SalAssignRule");
lf[557]=C_static_lambda_info(C_heaptop,23,"(a9725 args960 errf961)");
lf[558]=C_static_lambda_info(C_heaptop,12,"(a9777 e966)");
lf[559]=C_h_intern(&lf[559],9,"\000bindings");
lf[560]=C_static_lambda_info(C_heaptop,31,"(a9768 unit962 info963 errf964)");
lf[561]=C_static_string(C_heaptop,15,"SalBindingsRule");
lf[562]=C_static_string(C_heaptop,2,"#f");
lf[563]=C_static_lambda_info(C_heaptop,23,"(a9827 args953 errf954)");
lf[564]=C_static_lambda_info(C_heaptop,12,"(a9868 e958)");
lf[565]=C_static_lambda_info(C_heaptop,31,"(a9862 unit955 info956 errf957)");
lf[566]=C_static_string(C_heaptop,11,"SalBindRule");
lf[567]=C_static_string(C_heaptop,33,"return statement outside function");
lf[568]=C_static_lambda_info(C_heaptop,31,"(a9922 unit946 info947 errf948)");
lf[569]=C_static_string(C_heaptop,21,"SalFunctionReturnRule");
lf[570]=C_static_string(C_heaptop,32,"wait statement outside run block");
lf[571]=C_static_lambda_info(C_heaptop,31,"(a9983 unit940 info941 errf942)");
lf[572]=C_static_string(C_heaptop,18,"SalProcessWaitRule");
lf[573]=C_static_lambda_info(C_heaptop,24,"(a10037 args934 errf935)");
tmp=C_intern(C_heaptop,6,"fix-me");
C_save(tmp);
tmp=C_intern(C_heaptop,4,"plot");
C_save(tmp);
lf[574]=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
lf[575]=C_static_lambda_info(C_heaptop,32,"(a10067 unit936 info937 errf938)");
lf[576]=C_static_string(C_heaptop,20,"SalPlotStatementRule");
lf[577]=C_static_string(C_heaptop,22,"SalOutputStatementRule");
lf[578]=C_static_string(C_heaptop,22,"SalSystemStatementRule");
lf[579]=C_h_intern(&lf[579],10,"sal:system");
lf[580]=C_static_string(C_heaptop,21,"SalChdirStatementRule");
lf[581]=C_static_string(C_heaptop,20,"SalLoadStatementRule");
lf[582]=C_static_lambda_info(C_heaptop,24,"(a10286 args927 errf928)");
lf[583]=C_static_string(C_heaptop,20,"SalExecStatementRule");
lf[584]=C_static_lambda_info(C_heaptop,24,"(a10312 args914 errf915)");
lf[585]=C_static_lambda_info(C_heaptop,25,"(a10393 str924 . args925)");
lf[586]=C_static_lambda_info(C_heaptop,32,"(a10373 unit919 info920 errf921)");
lf[587]=C_static_string(C_heaptop,20,"SalSendStatementRule");
lf[588]=C_static_lambda_info(C_heaptop,24,"(a10511 args906 errf907)");
lf[589]=C_static_lambda_info(C_heaptop,32,"(a10538 unit909 info910 errf911)");
lf[590]=C_static_string(C_heaptop,22,"SalSproutStatementRule");
lf[591]=C_static_lambda_info(C_heaptop,24,"(a10620 args892 errf893)");
lf[592]=C_static_lambda_info(C_heaptop,15,"(do899 args901)");
lf[593]=C_static_lambda_info(C_heaptop,32,"(a10642 unit894 info895 errf896)");
lf[594]=C_static_string(C_heaptop,21,"SalPrintStatementRule");
lf[595]=C_static_string(C_heaptop,12,"SalSexprRule");
lf[596]=C_static_lambda_info(C_heaptop,24,"(a10774 args885 errf886)");
lf[597]=C_static_lambda_info(C_heaptop,32,"(a10800 unit887 info888 errf889)");
lf[598]=C_static_string(C_heaptop,11,"SalTermRule");
lf[599]=C_static_lambda_info(C_heaptop,24,"(a10910 args881 errf882)");
lf[600]=C_static_string(C_heaptop,12,"SalMexprRule");
lf[601]=C_static_string(C_heaptop,9,"SalOpRule");
lf[602]=C_static_lambda_info(C_heaptop,24,"(a11066 args844 errf845)");
lf[603]=C_static_lambda_info(C_heaptop,32,"(a11084 unit846 info847 errf848)");
lf[604]=C_static_string(C_heaptop,14,"SalFuncallRule");
lf[605]=C_static_lambda_info(C_heaptop,24,"(a11137 args838 errf839)");
lf[606]=C_static_string(C_heaptop,14,"SalFunargsRule");
lf[607]=C_static_lambda_info(C_heaptop,24,"(a11289 args835 errf836)");
lf[608]=C_static_string(C_heaptop,12,"SalKargsRule");
lf[609]=C_static_lambda_info(C_heaptop,24,"(a11428 args832 errf833)");
lf[610]=C_static_string(C_heaptop,12,"SalPargsRule");
lf[611]=C_static_lambda_info(C_heaptop,24,"(a11548 args811 errf812)");
lf[612]=C_static_lambda_info(C_heaptop,32,"(a11579 unit814 info815 errf816)");
lf[613]=C_static_string(C_heaptop,13,"SalIfExprRule");
lf[614]=C_static_lambda_info(C_heaptop,24,"(a11671 args805 errf806)");
lf[615]=C_static_lambda_info(C_heaptop,32,"(a11689 unit807 info808 errf809)");
lf[616]=C_static_string(C_heaptop,11,"SalArefRule");
lf[617]=C_static_string(C_heaptop,10,"SalEltRule");
lf[618]=C_h_intern(&lf[618],7,"unquote");
lf[619]=C_h_intern(&lf[619],16,"unquote-splicing");
lf[620]=C_h_intern(&lf[620],5,"\000list");
lf[621]=C_h_intern(&lf[621],8,"\000unquote");
lf[622]=C_static_string(C_heaptop,19,"#$ outside of list.");
lf[623]=C_static_string(C_heaptop,19,"#^ outside of list.");
lf[624]=C_static_lambda_info(C_heaptop,32,"(a11763 unit794 info795 errf796)");
lf[625]=C_static_string(C_heaptop,14,"SalUnquoteRule");
lf[626]=C_static_lambda_info(C_heaptop,24,"(a11859 args782 errf783)");
lf[627]=C_h_intern(&lf[627],10,"quasiquote");
lf[628]=C_static_lambda_info(C_heaptop,32,"(a11869 unit784 info785 errf786)");
lf[629]=C_static_string(C_heaptop,11,"SalListRule");
lf[630]=C_static_string(C_heaptop,11,"SalAtomRule");
lf[631]=C_static_string(C_heaptop,11,"SalBoolRule");
lf[632]=C_static_string(C_heaptop,13,"SalNumberRule");
lf[633]=C_h_intern(&lf[633],7,"fprintf");
lf[634]=C_static_string(C_heaptop,7,"#<u ~A>");
lf[635]=C_static_string(C_heaptop,8,"#<u x~X>");
lf[636]=C_static_lambda_info(C_heaptop,18,"(a12045 u432 p433)");
lf[637]=C_h_intern(&lf[637],27,"\003sysregister-record-printer");
lf[638]=C_static_string(C_heaptop,24,"#<parse-error ~S (@ ~S)>");
lf[639]=C_static_lambda_info(C_heaptop,18,"(a12071 e404 p405)");
lf[640]=C_static_string(C_heaptop,7,"#<r ~A>");
lf[641]=C_static_lambda_info(C_heaptop,18,"(a12085 r368 p369)");
lf[642]=C_h_intern(&lf[642],3,"eq\077");
lf[643]=C_static_string(C_heaptop,11,"#<t x~X ~S>");
lf[644]=C_static_lambda_info(C_heaptop,18,"(a12095 t319 p320)");
lf[645]=C_static_lambda_info(C_heaptop,10,"(toplevel)");
C_register_lf2(lf,646,create_ptable());
t2=C_mutate(&lf[0],lf[1]);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1735,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_library_toplevel(2,C_SCHEME_UNDEFINED,t3);}

/* k1733 */
static void C_ccall f_1735(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1735,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1738,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_eval_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k1736 in k1733 */
static void C_ccall f_1738(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1738,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1741,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k1739 in k1736 in k1733 */
static void C_ccall f_1741(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1741,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1744,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_1744(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_1744,2,t0,t1);}
t2=C_mutate(&lf[2],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1746,a[2]=lf[3],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate(&lf[4],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1773,a[2]=lf[5],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate(&lf[6],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1807,a[2]=lf[7],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate(&lf[8],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1882,a[2]=lf[9],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate(&lf[10],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1889,a[2]=lf[11],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate(&lf[12],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1927,a[2]=lf[13],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate(&lf[14],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1938,a[2]=lf[15],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate(&lf[16],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1945,a[2]=lf[17],tmp=(C_word)a,a+=3,tmp));
t10=C_mutate(&lf[18],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1956,a[2]=lf[19],tmp=(C_word)a,a+=3,tmp));
t11=C_mutate(&lf[20],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1966,a[2]=lf[21],tmp=(C_word)a,a+=3,tmp));
t12=C_mutate((C_word*)lf[22]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1979,a[2]=lf[23],tmp=(C_word)a,a+=3,tmp));
t13=C_mutate((C_word*)lf[24]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1998,a[2]=lf[25],tmp=(C_word)a,a+=3,tmp));
t14=C_mutate((C_word*)lf[26]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2080,a[2]=lf[27],tmp=(C_word)a,a+=3,tmp));
t15=C_mutate((C_word*)lf[28]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2086,a[2]=lf[29],tmp=(C_word)a,a+=3,tmp));
t16=C_mutate((C_word*)lf[30]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2092,a[2]=lf[31],tmp=(C_word)a,a+=3,tmp));
t17=C_mutate((C_word*)lf[32]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2111,a[2]=lf[39],tmp=(C_word)a,a+=3,tmp));
t18=C_mutate((C_word*)lf[40]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2171,a[2]=lf[41],tmp=(C_word)a,a+=3,tmp));
t19=C_mutate((C_word*)lf[42]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2177,a[2]=lf[43],tmp=(C_word)a,a+=3,tmp));
t20=C_mutate((C_word*)lf[44]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2183,a[2]=lf[45],tmp=(C_word)a,a+=3,tmp));
t21=C_mutate((C_word*)lf[46]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2189,a[2]=lf[47],tmp=(C_word)a,a+=3,tmp));
t22=C_mutate((C_word*)lf[48]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2195,a[2]=lf[49],tmp=(C_word)a,a+=3,tmp));
t23=C_mutate((C_word*)lf[50]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2201,a[2]=lf[57],tmp=(C_word)a,a+=3,tmp));
t24=C_mutate((C_word*)lf[58]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2296,a[2]=lf[59],tmp=(C_word)a,a+=3,tmp));
t25=C_mutate((C_word*)lf[60]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2302,a[2]=lf[63],tmp=(C_word)a,a+=3,tmp));
t26=C_mutate((C_word*)lf[64]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2361,a[2]=lf[65],tmp=(C_word)a,a+=3,tmp));
t27=C_mutate((C_word*)lf[66]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2367,a[2]=lf[68],tmp=(C_word)a,a+=3,tmp));
t28=C_mutate((C_word*)lf[69]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2455,a[2]=lf[73],tmp=(C_word)a,a+=3,tmp));
t29=C_mutate((C_word*)lf[74]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2513,a[2]=lf[76],tmp=(C_word)a,a+=3,tmp));
t30=C_mutate((C_word*)lf[77]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2536,a[2]=lf[78],tmp=(C_word)a,a+=3,tmp));
t31=C_mutate((C_word*)lf[79]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2542,a[2]=lf[80],tmp=(C_word)a,a+=3,tmp));
t32=C_mutate((C_word*)lf[81]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2548,a[2]=lf[82],tmp=(C_word)a,a+=3,tmp));
t33=C_mutate((C_word*)lf[83]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2554,a[2]=lf[84],tmp=(C_word)a,a+=3,tmp));
t34=C_mutate((C_word*)lf[85]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2560,a[2]=lf[88],tmp=(C_word)a,a+=3,tmp));
t35=C_mutate((C_word*)lf[89]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2604,a[2]=lf[90],tmp=(C_word)a,a+=3,tmp));
t36=C_mutate((C_word*)lf[91]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2623,a[2]=lf[92],tmp=(C_word)a,a+=3,tmp));
t37=C_mutate((C_word*)lf[93]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2663,a[2]=lf[94],tmp=(C_word)a,a+=3,tmp));
t38=C_mutate((C_word*)lf[95]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2669,a[2]=lf[97],tmp=(C_word)a,a+=3,tmp));
t39=C_mutate((C_word*)lf[98]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2688,a[2]=lf[99],tmp=(C_word)a,a+=3,tmp));
t40=C_mutate((C_word*)lf[100]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2707,a[2]=lf[101],tmp=(C_word)a,a+=3,tmp));
t41=C_mutate((C_word*)lf[102]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2713,a[2]=lf[103],tmp=(C_word)a,a+=3,tmp));
t42=C_mutate(&lf[104],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2719,a[2]=lf[106],tmp=(C_word)a,a+=3,tmp));
t43=C_mutate(&lf[107],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2740,a[2]=lf[108],tmp=(C_word)a,a+=3,tmp));
t44=C_mutate(&lf[109],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2758,a[2]=lf[110],tmp=(C_word)a,a+=3,tmp));
t45=C_mutate(&lf[111],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2776,a[2]=lf[112],tmp=(C_word)a,a+=3,tmp));
t46=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2786,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t47=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_12096,a[2]=lf[644],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  ##sys#register-record-printer");
t48=C_retrieve(lf[637]);
((C_proc4)C_retrieve_proc(t48))(4,t48,t46,lf[105],t47);}

/* a12095 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_12096(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_12096,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_12104,a[2]=t2,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  token-type");
f_2740(t4,t2);}

/* k12102 in a12095 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_12104(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_12104,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_12108,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  token-string");
f_2758(t2,((C_word*)t0)[2]);}

/* k12106 in k12102 in a12095 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_12108(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  fprintf");
t2=C_retrieve(lf[633]);
((C_proc6)C_retrieve_proc(t2))(6,t2,((C_word*)t0)[4],((C_word*)t0)[3],lf[643],((C_word*)t0)[2],t1);}

/* k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2786(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2786,2,t0,t1);}
t2=C_mutate(&lf[113],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2788,a[2]=lf[115],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate(&lf[116],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2817,a[2]=lf[117],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate(&lf[118],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2829,a[2]=lf[119],tmp=(C_word)a,a+=3,tmp));
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2837,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  make-hash-table");
t6=C_retrieve(lf[494]);
((C_proc3)C_retrieve_proc(t6))(3,t6,t5,*((C_word*)lf[642]+1));}

/* k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2837(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2837,2,t0,t1);}
t2=C_mutate(&lf[120],t1);
t3=C_mutate(&lf[121],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2839,a[2]=lf[123],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate(&lf[124],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2860,a[2]=lf[125],tmp=(C_word)a,a+=3,tmp));
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2942,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_12086,a[2]=lf[641],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  ##sys#register-record-printer");
t7=C_retrieve(lf[637]);
((C_proc4)C_retrieve_proc(t7))(4,t7,t5,lf[122],t6);}

/* a12085 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_12086(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_12086,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_12094,a[2]=t3,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  rule-name");
f_2860(t4,t2);}

/* k12092 in a12085 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_12094(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  fprintf");
t2=C_retrieve(lf[633]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[3],((C_word*)t0)[2],lf[640],t1);}

/* k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2942(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2942,2,t0,t1);}
t2=C_mutate(&lf[126],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2944,a[2]=lf[129],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate(&lf[130],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2968,a[2]=lf[131],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate(&lf[132],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2980,a[2]=lf[133],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate(&lf[134],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2986,a[2]=lf[135],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate(&lf[136],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2996,a[2]=lf[137],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate(&lf[138],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3054,a[2]=lf[140],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate(&lf[141],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3086,a[2]=lf[143],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate(&lf[144],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3107,a[2]=lf[145],tmp=(C_word)a,a+=3,tmp));
t10=C_mutate(&lf[146],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3125,a[2]=lf[147],tmp=(C_word)a,a+=3,tmp));
t11=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3135,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t12=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_12072,a[2]=lf[639],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  ##sys#register-record-printer");
t13=C_retrieve(lf[637]);
((C_proc4)C_retrieve_proc(t13))(4,t13,t11,lf[142],t12);}

/* a12071 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_12072(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_12072,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_12080,a[2]=t2,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  parse-error-string");
f_3107(t4,t2);}

/* k12078 in a12071 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_12080(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_12080,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_12084,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  parse-error-position");
f_3125(t2,((C_word*)t0)[2]);}

/* k12082 in k12078 in a12071 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_12084(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  fprintf");
t2=C_retrieve(lf[633]);
((C_proc6)C_retrieve_proc(t2))(6,t2,((C_word*)t0)[4],((C_word*)t0)[3],lf[638],((C_word*)t0)[2],t1);}

/* k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3135(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_3135,2,t0,t1);}
t2=C_mutate(&lf[148],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3137,a[2]=lf[150],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate(&lf[151],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3143,a[2]=lf[152],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate(&lf[153],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3158,a[2]=lf[154],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate(&lf[155],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3176,a[2]=lf[156],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate(&lf[157],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3194,a[2]=lf[158],tmp=(C_word)a,a+=3,tmp));
t7=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3204,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_12046,a[2]=lf[636],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  ##sys#register-record-printer");
t9=C_retrieve(lf[637]);
((C_proc4)C_retrieve_proc(t9))(4,t9,t7,lf[149],t8);}

/* a12045 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_12046(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_12046,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_12050,a[2]=t3,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-type");
f_3158(t4,t2);}

/* k12048 in a12045 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_12050(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_12050,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_12056,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  SalRuleType?");
f_4416(t2,t1);}

/* k12054 in k12048 in a12045 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_12056(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_12056,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_12063,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_12067,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  get-rule");
f_2944(t3,((C_word*)t0)[2],C_SCHEME_END_OF_LIST);}
else{
C_trace("ChickenBridge.scm: 137  fprintf");
t2=C_retrieve(lf[633]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[4],((C_word*)t0)[3],lf[635],((C_word*)t0)[2]);}}

/* k12065 in k12054 in k12048 in a12045 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_12067(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  rule-name");
f_2860(((C_word*)t0)[2],t1);}

/* k12061 in k12054 in k12048 in a12045 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_12063(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  fprintf");
t2=C_retrieve(lf[633]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[3],((C_word*)t0)[2],lf[634],t1);}

/* k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3204(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_3204,2,t0,t1);}
t2=C_mutate(&lf[159],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3206,a[2]=lf[161],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate(&lf[162],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3222,a[2]=lf[164],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate(&lf[165],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3254,a[2]=lf[166],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate(&lf[167],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3266,a[2]=lf[168],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate(&lf[169],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3276,a[2]=lf[171],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate(&lf[172],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3294,a[2]=lf[186],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate(&lf[183],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3327,a[2]=lf[187],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate(&lf[188],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3535,a[2]=lf[190],tmp=(C_word)a,a+=3,tmp));
t10=C_mutate(&lf[191],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3543,a[2]=lf[195],tmp=(C_word)a,a+=3,tmp));
t11=lf[196]=C_SCHEME_FALSE;;
t12=C_mutate(&lf[197],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3647,a[2]=lf[220],tmp=(C_word)a,a+=3,tmp));
t13=C_mutate(&lf[160],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4266,a[2]=lf[221],tmp=(C_word)a,a+=3,tmp));
t14=C_mutate(&lf[182],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4314,a[2]=lf[222],tmp=(C_word)a,a+=3,tmp));
t15=C_mutate(&lf[185],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4416,a[2]=lf[223],tmp=(C_word)a,a+=3,tmp));
t16=C_mutate(&lf[163],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4428,a[2]=lf[224],tmp=(C_word)a,a+=3,tmp));
t17=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4449,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t18=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_12024,a[2]=t17,tmp=(C_word)a,a+=3,tmp);
t19=(C_word)C_a_i_cons(&a,2,C_fix(3072),C_SCHEME_END_OF_LIST);
t20=(C_word)C_a_i_cons(&a,2,C_fix(3328),t19);
t21=(C_word)C_a_i_cons(&a,2,C_fix(2816),t20);
t22=(C_word)C_a_i_cons(&a,2,lf[177],t21);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t18,lf[632],C_fix(25856),t22,C_SCHEME_FALSE,C_SCHEME_FALSE);}

/* k12022 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_12024(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(25856),t1);}

/* k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4449(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4449,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4452,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_12004,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(4608),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(4352),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[177],t5);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t3,lf[631],C_fix(26112),t6,C_SCHEME_FALSE,C_SCHEME_FALSE);}

/* k12002 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_12004(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(26112),t1);}

/* k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4452(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4452,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4455,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11964,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(4608),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(4352),t4);
t6=(C_word)C_a_i_cons(&a,2,C_fix(25088),t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(3840),t6);
t8=(C_word)C_a_i_cons(&a,2,C_fix(3072),t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(3328),t8);
t10=(C_word)C_a_i_cons(&a,2,C_fix(2816),t9);
t11=(C_word)C_a_i_cons(&a,2,lf[177],t10);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t3,lf[630],C_fix(26368),t11,C_SCHEME_FALSE,C_SCHEME_FALSE);}

/* k11962 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11964(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(26368),t1);}

/* k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4455(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4455,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4458,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11854,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(26880),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,lf[139],t4);
t6=(C_word)C_a_i_cons(&a,2,C_fix(1280),C_SCHEME_END_OF_LIST);
t7=(C_word)C_a_i_cons(&a,2,t5,t6);
t8=(C_word)C_a_i_cons(&a,2,C_fix(1024),t7);
t9=(C_word)C_a_i_cons(&a,2,lf[176],t8);
t10=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11860,a[2]=lf[626],tmp=(C_word)a,a+=3,tmp);
t11=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11870,a[2]=lf[628],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t3,lf[629],C_fix(26624),t9,t10,t11);}

/* a11869 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11870(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[6],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_11870,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_11874,a[2]=t2,a[3]=t4,a[4]=t3,a[5]=t1,tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 137  get-emit-info");
f_3254(t5,lf[620],t3);}

/* k11872 in a11869 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11874(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11874,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_11877,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=t1,tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-parsed");
f_3176(t2,((C_word*)t0)[2]);}

/* k11875 in k11872 in a11869 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11877(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11877,2,t0,t1);}
t2=((C_word*)t0)[5];
if(C_truep(t2)){
C_trace("ChickenBridge.scm: 137  emit");
f_3294(((C_word*)t0)[4],t1,((C_word*)t0)[3],((C_word*)t0)[2]);}
else{
if(C_truep((C_word)C_i_nullp(t1))){
t3=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_list(&a,1,lf[549]));}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_11895,a[2]=((C_word*)t0)[2],a[3]=t1,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 137  add-emit-info");
f_3266(t3,lf[620],C_SCHEME_TRUE,((C_word*)t0)[3]);}}}

/* k11893 in k11875 in k11872 in a11869 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11895(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11895,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11898,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t2,((C_word*)t0)[3],t1,((C_word*)t0)[2]);}

/* k11896 in k11893 in k11875 in k11872 in a11869 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11898(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11898,2,t0,t1);}
t2=C_SCHEME_FALSE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11901,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11929,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  get-emit-info");
f_3254(t5,lf[620],((C_word*)t0)[2]);}

/* k11927 in k11896 in k11893 in k11875 in k11872 in a11869 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11929(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_11929,2,t0,t1);}
t2=(C_word)C_eqp(t1,lf[621]);
if(C_truep(t2)){
t3=(C_word)C_a_i_list(&a,2,lf[627],((C_word*)t0)[4]);
t4=C_mutate(((C_word *)((C_word*)t0)[3])+1,t3);
t5=((C_word*)t0)[2];
f_11901(t5,t4);}
else{
t3=(C_word)C_a_i_list(&a,2,lf[447],((C_word*)t0)[4]);
t4=C_mutate(((C_word *)((C_word*)t0)[3])+1,t3);
t5=((C_word*)t0)[2];
f_11901(t5,t4);}}

/* k11899 in k11896 in k11893 in k11875 in k11872 in a11869 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_11901(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_11901,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_11907,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  get-emit-info");
f_3254(t2,lf[559],((C_word*)t0)[2]);}

/* k11905 in k11899 in k11896 in k11893 in k11875 in k11872 in a11869 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11907(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11907,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,1,lf[549]);
t3=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_list(&a,3,lf[193],((C_word*)((C_word*)t0)[2])[1],t2));}
else{
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,((C_word*)((C_word*)t0)[2])[1]);}}

/* a11859 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11860(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word *a;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_11860,4,t0,t1,t2,t3);}
t4=(C_word)C_i_cadr(t2);
C_trace("ChickenBridge.scm: 137  make-parse-unit");
f_3137(t1,C_fix(26624),t4,C_SCHEME_FALSE);}

/* k11852 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11854(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(26624),t1);}

/* k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4458(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4458,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4461,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11754,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(5632),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(5376),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[177],t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,t6,t7);
t9=(C_word)C_a_i_cons(&a,2,lf[176],t8);
t10=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_11762,a[2]=t9,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  simple-unit-parser");
f_3535(t10,C_fix(27648));}

/* k11760 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11762(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11762,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11764,a[2]=lf[624],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(((C_word*)t0)[3],lf[625],C_fix(27648),((C_word*)t0)[2],t1,t2);}

/* a11763 in k11760 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11764(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_11764,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11768,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-parsed");
f_3176(t5,t2);}

/* k11766 in a11763 in k11760 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11768(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11768,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_11771,a[2]=((C_word*)t0)[2],a[3]=t1,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=(C_word)C_i_car(t1);
C_trace("ChickenBridge.scm: 137  token-unit-type=?");
f_3222(t2,t3,C_fix(5376));}

/* k11769 in k11766 in a11763 in k11760 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11771(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11771,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_11774,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=((C_word*)t0)[5],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 137  get-emit-info");
f_3254(t2,lf[620],((C_word*)t0)[4]);}

/* k11772 in k11769 in k11766 in a11763 in k11760 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11774(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_11774,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_11777,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
if(C_truep(t1)){
t3=t2;
f_11777(2,t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_11806,a[2]=t2,a[3]=((C_word*)t0)[2],tmp=(C_word)a,a+=4,tmp);
t4=(C_truep(((C_word*)t0)[5])?lf[622]:lf[623]);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_11814,a[2]=t4,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t6=(C_word)C_i_car(((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 137  parse-unit-position");
f_3194(t5,t6);}}

/* k11812 in k11772 in k11769 in k11766 in a11763 in k11760 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11814(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  make-parse-error");
f_3086(((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k11804 in k11772 in k11769 in k11766 in a11763 in k11760 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11806(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  errf");
t2=((C_word*)t0)[3];
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k11775 in k11772 in k11769 in k11766 in a11763 in k11760 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11777(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11777,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11780,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
t3=(C_word)C_i_cadr(((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t2,t3,((C_word*)t0)[4],((C_word*)t0)[2]);}

/* k11778 in k11775 in k11772 in k11769 in k11766 in a11763 in k11760 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11780(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11780,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11783,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  set-emit-info!");
f_3276(t2,lf[620],lf[621],((C_word*)t0)[2]);}

/* k11781 in k11778 in k11775 in k11772 in k11769 in k11766 in a11763 in k11760 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11783(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11783,2,t0,t1);}
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_truep(((C_word*)t0)[3])?(C_word)C_a_i_list(&a,2,lf[618],((C_word*)t0)[2]):(C_word)C_a_i_list(&a,2,lf[619],((C_word*)t0)[2])));}

/* k11752 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11754(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(27648),t1);}

/* k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4461(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4461,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4464,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11726,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(27648),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(2304),t4);
t6=(C_word)C_a_i_cons(&a,2,C_fix(26624),t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(26368),t6);
t8=(C_word)C_a_i_cons(&a,2,lf[177],t7);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t3,lf[617],C_fix(26880),t8,C_SCHEME_FALSE,C_SCHEME_FALSE);}

/* k11724 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11726(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(26880),t1);}

/* k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4464(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4464,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4467,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11666,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(1792),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(29696),t4);
t6=(C_word)C_a_i_cons(&a,2,C_fix(1536),t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(25088),t6);
t8=(C_word)C_a_i_cons(&a,2,lf[176],t7);
t9=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11672,a[2]=lf[614],tmp=(C_word)a,a+=3,tmp);
t10=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11690,a[2]=lf[615],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t3,lf[616],C_fix(27136),t8,t9,t10);}

/* a11689 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11690(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[8],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_11690,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11698,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11702,a[2]=t4,a[3]=t3,a[4]=t5,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-parsed");
f_3176(t6,t2);}

/* k11700 in a11689 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11702(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  emit");
f_3294(((C_word*)t0)[4],t1,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k11696 in a11689 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11698(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11698,2,t0,t1);}
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_cons(&a,2,lf[548],t1));}

/* a11671 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11672(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_11672,4,t0,t1,t2,t3);}
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_caddr(t2);
t6=(C_word)C_a_i_list(&a,2,t4,t5);
C_trace("ChickenBridge.scm: 137  make-parse-unit");
f_3137(t1,C_fix(27136),t6,C_SCHEME_FALSE);}

/* k11664 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11666(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(27136),t1);}

/* k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4467(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4467,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4470,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11543,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
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
t15=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11549,a[2]=lf[611],tmp=(C_word)a,a+=3,tmp);
t16=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11580,a[2]=lf[612],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t3,lf[613],C_fix(27392),t14,t15,t16);}

/* a11579 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11580(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_11580,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11584,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-parsed");
f_3176(t5,t2);}

/* k11582 in a11579 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11584(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11584,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_11587,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,tmp=(C_word)a,a+=6,tmp);
t3=(C_word)C_i_car(t1);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k11585 in k11582 in a11579 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11587(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11587,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_11590,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],tmp=(C_word)a,a+=7,tmp);
t3=(C_word)C_i_cadr(((C_word*)t0)[5]);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k11588 in k11585 in k11582 in a11579 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11590(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11590,2,t0,t1);}
t2=(C_word)C_i_caddr(((C_word*)t0)[6]);
if(C_truep(t2)){
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11603,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t3,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}
else{
t3=((C_word*)t0)[5];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_list(&a,4,lf[241],((C_word*)t0)[4],t1,C_SCHEME_FALSE));}}

/* k11601 in k11588 in k11585 in k11582 in a11579 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11603(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11603,2,t0,t1);}
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_list(&a,4,lf[241],((C_word*)t0)[3],((C_word*)t0)[2],t1));}

/* a11548 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11549(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_11549,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_11553,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  sixth");
t5=C_retrieve(lf[319]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,t2);}

/* k11551 in a11548 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11553(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11553,2,t0,t1);}
t2=(C_word)C_i_caddr(((C_word*)t0)[3]);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11568,a[2]=((C_word*)t0)[2],a[3]=t2,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  fifth");
t4=C_retrieve(lf[243]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)t0)[3]);}

/* k11566 in k11551 in a11548 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11568(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11568,2,t0,t1);}
t2=(C_word)C_i_pairp(((C_word*)t0)[4]);
t3=(C_truep(t2)?(C_word)C_i_cadr(((C_word*)t0)[4]):C_SCHEME_FALSE);
t4=(C_word)C_a_i_list(&a,3,((C_word*)t0)[3],t1,t3);
C_trace("ChickenBridge.scm: 137  make-parse-unit");
f_3137(((C_word*)t0)[2],C_fix(27392),t4,C_SCHEME_FALSE);}

/* k11541 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11543(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(27392),t1);}

/* k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4470(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4470,2,t0,t1);}
t2=C_mutate(&lf[225],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4472,a[2]=lf[227],tmp=(C_word)a,a+=3,tmp));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4526,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11423,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
t5=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t6=(C_word)C_a_i_cons(&a,2,C_fix(256),t5);
t7=(C_word)C_a_i_cons(&a,2,lf[215],t6);
t8=(C_word)C_a_i_cons(&a,2,t7,C_SCHEME_END_OF_LIST);
t9=(C_word)C_a_i_cons(&a,2,C_fix(29696),t8);
t10=(C_word)C_a_i_cons(&a,2,lf[176],t9);
t11=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t12=(C_word)C_a_i_cons(&a,2,t10,t11);
t13=(C_word)C_a_i_cons(&a,2,lf[177],t12);
t14=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11429,a[2]=lf[609],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t4,lf[610],C_fix(28416),t13,t14,C_SCHEME_FALSE);}

/* a11428 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11429(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_11429,4,t0,t1,t2,t3);}
if(C_truep((C_word)C_i_pairp(t2))){
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_11445,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(C_word)C_i_cadr(t2);
if(C_truep((C_word)C_i_pairp(t6))){
t7=(C_word)C_i_cadr(t2);
t8=(C_word)C_i_car(t7);
C_trace("ChickenBridge.scm: 137  token-unit-type=?");
f_3222(t4,t8,C_fix(256));}
else{
t7=t4;
f_11445(2,t7,C_SCHEME_FALSE);}}
else{
t6=t4;
f_11445(2,t6,C_SCHEME_FALSE);}}
else{
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_a_i_list(&a,1,t2));}}

/* k11443 in a11428 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11445(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11445,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_11456,a[2]=t2,a[3]=((C_word*)t0)[2],tmp=(C_word)a,a+=4,tmp);
t4=(C_word)C_i_cadr(((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 137  remove-token-type");
f_4472(t3,t4,C_fix(256));}
else{
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]));}}

/* k11454 in k11443 in a11428 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11456(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11456,2,t0,t1);}
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[2],t1));}

/* k11421 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11423(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(28416),t1);}

/* k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4526(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4526,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4529,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11284,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
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
t18=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11290,a[2]=lf[607],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t3,lf[608],C_fix(28672),t17,t18,C_SCHEME_FALSE);}

/* a11289 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11290(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_11290,4,t0,t1,t2,t3);}
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cadr(t2);
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11310,a[2]=t4,a[3]=t1,a[4]=t5,tmp=(C_word)a,a+=5,tmp);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_11313,a[2]=t6,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t8=(C_word)C_i_cddr(t2);
if(C_truep((C_word)C_i_pairp(t8))){
t9=(C_word)C_i_caddr(t2);
if(C_truep((C_word)C_i_pairp(t9))){
t10=(C_word)C_i_caddr(t2);
t11=(C_word)C_i_car(t10);
C_trace("ChickenBridge.scm: 137  token-unit-type=?");
f_3222(t7,t11,C_fix(256));}
else{
t10=t7;
f_11313(2,t10,C_SCHEME_FALSE);}}
else{
t9=t7;
f_11313(2,t9,C_SCHEME_FALSE);}}

/* k11311 in a11289 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11313(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_caddr(((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 137  remove-token-type");
f_4472(((C_word*)t0)[2],t2,C_fix(256));}
else{
t2=((C_word*)t0)[2];
f_11310(2,t2,C_SCHEME_END_OF_LIST);}}

/* k11308 in a11289 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11310(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11310,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[4],t1);
t3=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[2],t2));}

/* k11282 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11284(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(28672),t1);}

/* k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4529(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4529,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4532,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11132,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
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
t26=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11138,a[2]=lf[605],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t3,lf[606],C_fix(28160),t25,t26,C_SCHEME_FALSE);}

/* a11137 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11138(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_11138,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=(C_word)C_i_cdr(((C_word*)t4)[1]);
t6=C_set_block_item(t4,0,t5);
t7=(C_word)C_i_car(((C_word*)t4)[1]);
t8=(C_word)C_i_cdr(((C_word*)t4)[1]);
t9=C_set_block_item(t4,0,t8);
t10=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11156,a[2]=t7,a[3]=t4,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  token-unit-type=?");
f_3222(t10,t7,C_fix(768));}

/* k11154 in a11137 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11156(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11156,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_END_OF_LIST);}
else{
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11165,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
C_trace("ChickenBridge.scm: 137  token-unit-type=?");
f_3222(t2,t3,C_fix(256));}}

/* k11163 in k11154 in a11137 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11165(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_cadr(((C_word*)((C_word*)t0)[4])[1]);
C_trace("ChickenBridge.scm: 137  append");
t3=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[3],((C_word*)t0)[2],t2);}
else{
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,((C_word*)t0)[2]);}}

/* k11130 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11132(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(28160),t1);}

/* k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4532(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4532,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4535,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11061,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(28160),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(25088),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[176],t5);
t7=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11067,a[2]=lf[602],tmp=(C_word)a,a+=3,tmp);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11085,a[2]=lf[603],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t3,lf[604],C_fix(27904),t6,t7,t8);}

/* a11084 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11085(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_11085,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11089,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-parsed");
f_3176(t5,t2);}

/* k11087 in a11084 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11089(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11089,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_11092,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=(C_word)C_i_car(t1);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k11090 in k11087 in a11084 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11092(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11092,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_11108,a[2]=t1,a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t3=(C_word)C_i_cdr(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k11106 in k11090 in k11087 in a11084 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11108(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11108,2,t0,t1);}
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[2],t1));}

/* a11066 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11067(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[3],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_11067,4,t0,t1,t2,t3);}
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cadr(t2);
t6=(C_word)C_a_i_cons(&a,2,t4,t5);
C_trace("ChickenBridge.scm: 137  make-parse-unit");
f_3137(t1,C_fix(27904),t6,C_SCHEME_FALSE);}

/* k11059 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_11061(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(27904),t1);}

/* k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4535(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4535,2,t0,t1);}
t2=C_mutate(&lf[228],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4537,a[2]=lf[229],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate(&lf[230],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4558,a[2]=lf[233],tmp=(C_word)a,a+=3,tmp));
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4674,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10985,a[2]=t4,tmp=(C_word)a,a+=3,tmp);
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
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t5,lf[601],C_fix(28928),t22,C_SCHEME_FALSE,C_SCHEME_FALSE);}

/* k10983 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10985(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(28928),t1);}

/* k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4674(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4674,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4677,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10905,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29440),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(28928),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[139],t5);
t7=(C_word)C_a_i_cons(&a,2,t6,C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(29440),t7);
t9=(C_word)C_a_i_cons(&a,2,lf[176],t8);
t10=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10911,a[2]=lf[599],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t3,lf[600],C_fix(29184),t9,t10,C_SCHEME_FALSE);}

/* a10910 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10911(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_10911,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10918,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_i_cadr(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(C_word)C_i_cadr(t2);
t7=(C_word)C_i_car(t6);
C_trace("ChickenBridge.scm: 137  is-op?");
f_4537(t4,t7);}
else{
t6=t4;
f_10918(2,t6,C_SCHEME_FALSE);}}

/* k10916 in a10910 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10918(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10918,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=(C_word)C_i_cadr(((C_word*)t0)[3]);
t4=(C_word)C_a_i_cons(&a,2,t2,t3);
C_trace("ChickenBridge.scm: 137  inf->pre");
f_4558(((C_word*)t0)[2],t4);}
else{
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_i_car(((C_word*)t0)[3]));}}

/* k10903 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10905(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(29184),t1);}

/* k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4677(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4677,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4680,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10769,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
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
t24=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10775,a[2]=lf[596],tmp=(C_word)a,a+=3,tmp);
t25=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10801,a[2]=lf[597],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t3,lf[598],C_fix(29440),t23,t24,t25);}

/* a10800 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10801(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_10801,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10809,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-parsed");
f_3176(t5,t2);}

/* k10807 in a10800 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10809(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  emit");
f_3294(((C_word*)t0)[4],t1,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* a10774 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10775(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[7],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_10775,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10783,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep((C_word)C_i_pairp(t2))){
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10792,a[2]=t2,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
t6=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 137  token-unit-type=?");
f_3222(t5,t6,C_fix(512));}
else{
t5=t4;
f_10783(t5,t2);}}

/* k10790 in a10774 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10792(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
f_10783(t2,(C_truep(t1)?(C_word)C_i_cadr(((C_word*)t0)[2]):((C_word*)t0)[2]));}

/* k10781 in a10774 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_10783(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  make-parse-unit");
f_3137(((C_word*)t0)[2],C_fix(29440),t1,C_SCHEME_FALSE);}

/* k10767 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10769(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(29440),t1);}

/* k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4680(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4680,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4683,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10725,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(26368),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(6400),t4);
t6=(C_word)C_a_i_cons(&a,2,C_fix(2304),t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(26624),t6);
t8=(C_word)C_a_i_cons(&a,2,C_fix(27136),t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(27904),t8);
t10=(C_word)C_a_i_cons(&a,2,C_fix(27392),t9);
t11=(C_word)C_a_i_cons(&a,2,C_fix(29184),t10);
t12=(C_word)C_a_i_cons(&a,2,lf[177],t11);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t3,lf[595],C_fix(29696),t12,C_SCHEME_FALSE,C_SCHEME_FALSE);}

/* k10723 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10725(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(29696),t1);}

/* k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4683(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4683,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4686,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10615,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(256),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[139],t5);
t7=(C_word)C_a_i_cons(&a,2,t6,C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(29696),t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(15872),t8);
t10=(C_word)C_a_i_cons(&a,2,lf[176],t9);
t11=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10621,a[2]=lf[591],tmp=(C_word)a,a+=3,tmp);
t12=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10643,a[2]=lf[593],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t3,lf[594],C_fix(33536),t10,t11,t12);}

/* a10642 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10643(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
C_save_and_reclaim((void*)tr5,(void*)f_10643,5,t0,t1,t2,t3,t4);}
t5=(C_word)C_a_i_list(&a,1,lf[278]);
t6=t5;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_10654,a[2]=t1,a[3]=t4,a[4]=t3,a[5]=t7,a[6]=t5,tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-parsed");
f_3176(t8,t2);}

/* k10652 in a10642 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10654(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10654,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_10656,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=t3,a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=lf[592],tmp=(C_word)a,a+=8,tmp));
t5=((C_word*)t3)[1];
f_10656(t5,((C_word*)t0)[2],t1);}

/* do899 in k10652 in a10642 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_10656(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_10656,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,((C_word*)t0)[6]);}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_10685,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=t2,a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
t4=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t3,t4,((C_word*)t0)[3],((C_word*)t0)[2]);}}

/* k10683 in do899 in k10652 in a10642 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10685(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_10685,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,t1);
t3=(C_word)C_i_set_cdr(((C_word*)((C_word*)t0)[5])[1],t2);
t4=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[5])[1]);
t5=C_mutate(((C_word *)((C_word*)t0)[5])+1,t4);
t6=(C_word)C_i_cdr(((C_word*)t0)[4]);
t7=((C_word*)((C_word*)t0)[3])[1];
f_10656(t7,((C_word*)t0)[2],t6);}

/* a10620 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10621(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[4],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_10621,4,t0,t1,t2,t3);}
t4=(C_word)C_i_cadr(t2);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10637,a[2]=t1,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
t6=(C_word)C_i_caddr(t2);
C_trace("ChickenBridge.scm: 137  remove-token-type");
f_4472(t5,t6,C_fix(256));}

/* k10635 in a10620 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10637(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10637,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[3],t1);
C_trace("ChickenBridge.scm: 137  make-parse-unit");
f_3137(((C_word*)t0)[2],C_fix(33536),t2,C_SCHEME_FALSE);}

/* k10613 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10615(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(33536),t1);}

/* k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4686(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4686,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4689,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10506,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(256),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[214],t5);
t7=(C_word)C_a_i_cons(&a,2,t6,C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(29696),t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(16896),t8);
t10=(C_word)C_a_i_cons(&a,2,lf[176],t9);
t11=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10512,a[2]=lf[588],tmp=(C_word)a,a+=3,tmp);
t12=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10539,a[2]=lf[589],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t3,lf[590],C_fix(34560),t10,t11,t12);}

/* a10538 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10539(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_10539,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10543,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-parsed");
f_3176(t5,t2);}

/* k10541 in a10538 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10543(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10543,2,t0,t1);}
if(C_truep((C_word)C_i_cadr(t1))){
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_10556,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=(C_word)C_i_car(t1);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}
else{
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10575,a[2]=((C_word*)t0)[4],tmp=(C_word)a,a+=3,tmp);
t3=(C_word)C_i_car(t1);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}}

/* k10573 in k10541 in a10538 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10575(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10575,2,t0,t1);}
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_list(&a,2,lf[362],t1));}

/* k10554 in k10541 in a10538 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10556(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10556,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10560,a[2]=t1,a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t3=(C_word)C_i_cadr(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k10558 in k10554 in k10541 in a10538 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10560(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10560,2,t0,t1);}
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_list(&a,3,lf[362],((C_word*)t0)[2],t1));}

/* a10511 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10512(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word ab[4],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_10512,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10516,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_caddr(t2))){
t5=(C_word)C_i_caddr(t2);
C_trace("ChickenBridge.scm: 137  remove-token-type");
f_4472(t4,t5,C_fix(256));}
else{
t5=t4;
f_10516(2,t5,C_SCHEME_FALSE);}}

/* k10514 in a10511 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10516(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10516,2,t0,t1);}
t2=(C_word)C_i_cadr(((C_word*)t0)[3]);
t3=(C_word)C_a_i_list(&a,2,t2,t1);
C_trace("ChickenBridge.scm: 137  make-parse-unit");
f_3137(((C_word*)t0)[2],C_fix(34560),t3,C_SCHEME_FALSE);}

/* k10504 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10506(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(34560),t1);}

/* k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4689(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4689,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4692,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10307,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
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
t22=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10313,a[2]=lf[584],tmp=(C_word)a,a+=3,tmp);
t23=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10374,a[2]=lf[586],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t3,lf[587],C_fix(34304),t21,t22,t23);}

/* a10373 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10374(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[10],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_10374,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10378,a[2]=t1,a[3]=t2,a[4]=t4,tmp=(C_word)a,a+=5,tmp);
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10414,a[2]=t4,a[3]=t3,a[4]=t5,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-parsed");
f_3176(t6,t2);}

/* k10412 in a10373 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10414(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  emit");
f_3294(((C_word*)t0)[4],t1,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k10376 in a10373 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10378(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10378,2,t0,t1);}
t2=(C_word)C_i_car(t1);
t3=(C_word)C_i_car(t1);
t4=(C_word)C_i_cdr(t1);
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10394,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=lf[585],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  expand-send");
t6=C_retrieve(lf[396]);
((C_proc5)C_retrieve_proc(t6))(5,t6,((C_word*)t0)[2],t3,t4,t5);}

/* a10393 in k10376 in a10373 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10394(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+8)){
C_save_and_reclaim((void*)tr3r,(void*)f_10394r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_10394r(t0,t1,t2,t3);}}

static void C_ccall f_10394r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word *a=C_alloc(8);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10402,a[2]=t1,a[3]=((C_word*)t0)[3],tmp=(C_word)a,a+=4,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10406,a[2]=((C_word*)t0)[2],a[3]=t4,tmp=(C_word)a,a+=4,tmp);
C_apply(5,0,t5,C_retrieve(lf[286]),t2,t3);}

/* k10404 in a10393 in k10376 in a10373 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10406(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10406,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10410,a[2]=t1,a[3]=((C_word*)t0)[3],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-position");
f_3194(t2,((C_word*)t0)[2]);}

/* k10408 in k10404 in a10393 in k10376 in a10373 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10410(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  make-parse-error");
f_3086(((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k10400 in a10393 in k10376 in a10373 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10402(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  errf");
t2=((C_word*)t0)[3];
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* a10312 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10313(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_10313,4,t0,t1,t2,t3);}
t4=(C_word)C_i_caddr(t2);
t5=t4;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10320,a[2]=t1,a[3]=t6,a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t8=((C_word*)t6)[1];
if(C_truep(t8)){
t9=(C_word)C_i_cadr(((C_word*)t6)[1]);
t10=C_set_block_item(t6,0,t9);
t11=(C_word)C_i_car(((C_word*)t6)[1]);
if(C_truep((C_word)C_i_pairp(t11))){
t12=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10360,a[2]=t7,a[3]=t6,tmp=(C_word)a,a+=4,tmp);
t13=(C_word)C_i_car(((C_word*)t6)[1]);
t14=(C_word)C_i_caddr(((C_word*)t6)[1]);
C_trace("ChickenBridge.scm: 137  append");
t15=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t15))(4,t15,t12,t13,t14);}
else{
t12=t7;
f_10320(t12,C_SCHEME_UNDEFINED);}}
else{
t9=C_set_block_item(t6,0,C_SCHEME_END_OF_LIST);
t10=t7;
f_10320(t10,t9);}}

/* k10358 in a10312 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10360(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_10320(t3,t2);}

/* k10318 in a10312 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_10320(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_10320,NULL,2,t0,t1);}
t2=(C_word)C_i_cadr(((C_word*)t0)[4]);
t3=(C_word)C_a_i_cons(&a,2,t2,((C_word*)((C_word*)t0)[3])[1]);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10331,a[2]=t3,a[3]=((C_word*)t0)[2],tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_i_car(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 137  parse-unit-position");
f_3194(t4,t5);}

/* k10329 in k10318 in a10312 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10331(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  make-parse-unit");
f_3137(((C_word*)t0)[3],C_fix(34304),((C_word*)t0)[2],t1);}

/* k10305 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10307(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(34304),t1);}

/* k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4692(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4692,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4695,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10281,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(14080),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[176],t5);
t7=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10287,a[2]=lf[582],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t3,lf[583],C_fix(33792),t6,t7,C_SCHEME_FALSE);}

/* a10286 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10287(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word *a;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_10287,4,t0,t1,t2,t3);}
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_cadr(t2));}

/* k10279 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10281(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(33792),t1);}

/* k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4695(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4695,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4698,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10253,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(14592),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[176],t5);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10261,a[2]=t6,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  simple-unit-parser");
f_3535(t7,C_fix(35072));}

/* k10259 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10261(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10261,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10265,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  simple-unit-emitter");
f_3543(t2,lf[296]);}

/* k10263 in k10259 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10265(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(((C_word*)t0)[4],lf[581],C_fix(35072),((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k10251 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10253(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(35072),t1);}

/* k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4698(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4698,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4701,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10225,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(13568),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[176],t5);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10233,a[2]=t6,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  simple-unit-parser");
f_3535(t7,C_fix(35584));}

/* k10231 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10233(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10233,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10237,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  simple-unit-emitter");
f_3543(t2,lf[293]);}

/* k10235 in k10231 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10237(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(((C_word*)t0)[4],lf[580],C_fix(35584),((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k10223 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10225(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(35584),t1);}

/* k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4701(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4701,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4704,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10197,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(17152),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[176],t5);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10205,a[2]=t6,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  simple-unit-parser");
f_3535(t7,C_fix(35328));}

/* k10203 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10205(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10205,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10209,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  simple-unit-emitter");
f_3543(t2,lf[579]);}

/* k10207 in k10203 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10209(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(((C_word*)t0)[4],lf[578],C_fix(35328),((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k10195 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10197(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(35328),t1);}

/* k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4704(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4704,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4707,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10169,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(18432),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[176],t5);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10177,a[2]=t6,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  simple-unit-parser");
f_3535(t7,C_fix(34816));}

/* k10175 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10177(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10177,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10181,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  simple-unit-emitter");
f_3543(t2,lf[308]);}

/* k10179 in k10175 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10181(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(((C_word*)t0)[4],lf[577],C_fix(34816),((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k10167 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10169(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(34816),t1);}

/* k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4707(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4707,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4710,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10032,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
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
t23=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10038,a[2]=lf[573],tmp=(C_word)a,a+=3,tmp);
t24=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10068,a[2]=lf[575],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t3,lf[576],C_fix(36096),t22,t23,t24);}

/* a10067 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10068(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_10068,5,t0,t1,t2,t3,t4);}
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,lf[574]);}

/* a10037 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10038(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_10038,4,t0,t1,t2,t3);}
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cadr(t2);
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10062,a[2]=t1,a[3]=t4,a[4]=t5,tmp=(C_word)a,a+=5,tmp);
t7=(C_word)C_i_caddr(t2);
C_trace("ChickenBridge.scm: 137  remove-token-type");
f_4472(t6,t7,C_fix(256));}

/* k10060 in a10037 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10062(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10062,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[4],t1);
t3=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[3],t2);
C_trace("ChickenBridge.scm: 137  make-parse-unit");
f_3137(((C_word*)t0)[2],C_fix(36096),t3,C_SCHEME_FALSE);}

/* k10030 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10032(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(36096),t1);}

/* k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4710(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4710,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4713,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9974,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(19712),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[176],t5);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9982,a[2]=t6,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  simple-unit-parser");
f_3535(t7,C_fix(31744));}

/* k9980 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9982(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9982,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9984,a[2]=lf[571],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(((C_word*)t0)[3],lf[572],C_fix(31744),((C_word*)t0)[2],t1,t2);}

/* a9983 in k9980 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9984(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_9984,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9988,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-parsed");
f_3176(t5,t2);}

/* k9986 in a9983 in k9980 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9988(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9988,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_9991,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10016,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  get-emit-info");
f_3254(t3,lf[531],((C_word*)t0)[3]);}

/* k10014 in k9986 in a9983 in k9980 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10016(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10016,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
f_9991(2,t2,C_SCHEME_UNDEFINED);}
else{
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10004,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[3],tmp=(C_word)a,a+=4,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10008,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 137  parse-unit-position");
f_3194(t3,t4);}}

/* k10006 in k10014 in k9986 in a9983 in k9980 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10008(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  make-parse-error");
f_3086(((C_word*)t0)[2],lf[570],t1);}

/* k10002 in k10014 in k9986 in a9983 in k9980 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_10004(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  errf");
t2=((C_word*)t0)[3];
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k9989 in k9986 in a9983 in k9980 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9991(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  emit");
f_3294(((C_word*)t0)[5],((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k9972 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9974(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(31744),t1);}

/* k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4713(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4713,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4716,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9913,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(18688),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[176],t5);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9921,a[2]=t6,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  simple-unit-parser");
f_3535(t7,C_fix(31488));}

/* k9919 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9921(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9921,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9923,a[2]=lf[568],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(((C_word*)t0)[3],lf[569],C_fix(31488),((C_word*)t0)[2],t1,t2);}

/* a9922 in k9919 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9923(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_9923,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9927,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-parsed");
f_3176(t5,t2);}

/* k9925 in a9922 in k9919 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9927(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9927,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_9930,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9958,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  get-emit-info");
f_3254(t3,lf[511],((C_word*)t0)[3]);}

/* k9956 in k9925 in a9922 in k9919 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9958(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9958,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
f_9930(2,t2,C_SCHEME_UNDEFINED);}
else{
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9946,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[3],tmp=(C_word)a,a+=4,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9950,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 137  parse-unit-position");
f_3194(t3,t4);}}

/* k9948 in k9956 in k9925 in a9922 in k9919 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9950(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  make-parse-error");
f_3086(((C_word*)t0)[2],lf[567],t1);}

/* k9944 in k9956 in k9925 in a9922 in k9919 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9946(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  errf");
t2=((C_word*)t0)[3];
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k9928 in k9925 in a9922 in k9919 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9930(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9930,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_9933,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 137  set-emit-info!");
f_3276(t2,lf[511],lf[509],((C_word*)t0)[3]);}

/* k9931 in k9928 in k9925 in a9922 in k9919 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9933(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  emit");
f_3294(((C_word*)t0)[5],((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k9911 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9913(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(31488),t1);}

/* k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4716(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4716,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4719,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9822,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(10756),t4);
t6=(C_word)C_a_i_cons(&a,2,C_fix(25088),t5);
t7=(C_word)C_a_i_cons(&a,2,lf[176],t6);
t8=(C_word)C_a_i_cons(&a,2,C_fix(25088),C_SCHEME_END_OF_LIST);
t9=(C_word)C_a_i_cons(&a,2,t7,t8);
t10=(C_word)C_a_i_cons(&a,2,lf[177],t9);
t11=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9828,a[2]=lf[563],tmp=(C_word)a,a+=3,tmp);
t12=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9863,a[2]=lf[565],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t3,lf[566],C_fix(30208),t10,t11,t12);}

/* a9862 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9863(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[9],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_9863,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9869,a[2]=t4,a[3]=t3,a[4]=lf[564],tmp=(C_word)a,a+=5,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9877,a[2]=t5,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-parsed");
f_3176(t6,t2);}

/* k9875 in a9862 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9877(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("map");
t2=*((C_word*)lf[276]+1);
((C_proc4)(void*)(*((C_word*)t2+1)))(4,t2,((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* a9868 in a9862 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9869(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_9869,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t1,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* a9827 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9828(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_9828,4,t0,t1,t2,t3);}
if(C_truep((C_word)C_i_pairp(t2))){
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_caddr(t2);
t6=(C_word)C_a_i_list(&a,2,t4,t5);
C_trace("ChickenBridge.scm: 137  make-parse-unit");
f_3137(t1,C_fix(30208),t6,C_SCHEME_FALSE);}
else{
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9861,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  make-parse-unit");
f_3137(t4,C_fix(4608),lf[562],C_SCHEME_FALSE);}}

/* k9859 in a9827 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9861(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9861,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,2,((C_word*)t0)[3],t1);
C_trace("ChickenBridge.scm: 137  make-parse-unit");
f_3137(((C_word*)t0)[2],C_fix(30208),t2,C_SCHEME_FALSE);}

/* k9820 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9822(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(30208),t1);}

/* k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4719(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4719,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4722,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9720,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(30208),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(256),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[139],t5);
t7=(C_word)C_a_i_cons(&a,2,t6,C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(30208),t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(20480),t8);
t10=(C_word)C_a_i_cons(&a,2,lf[176],t9);
t11=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9726,a[2]=lf[557],tmp=(C_word)a,a+=3,tmp);
t12=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9769,a[2]=lf[560],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t3,lf[561],C_fix(29952),t10,t11,t12);}

/* a9768 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9769(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_9769,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9773,a[2]=t2,a[3]=t1,a[4]=t4,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  add-emit-info");
f_3266(t5,lf[559],C_SCHEME_TRUE,t3);}

/* k9771 in a9768 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9773(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9773,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9778,a[2]=((C_word*)t0)[4],a[3]=t1,a[4]=lf[558],tmp=(C_word)a,a+=5,tmp);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9786,a[2]=t2,a[3]=((C_word*)t0)[3],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-parsed");
f_3176(t3,((C_word*)t0)[2]);}

/* k9784 in k9771 in a9768 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9786(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("map");
t2=*((C_word*)lf[276]+1);
((C_proc4)(void*)(*((C_word*)t2+1)))(4,t2,((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* a9777 in k9771 in a9768 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9778(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_9778,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t1,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* a9725 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9726(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_9726,4,t0,t1,t2,t3);}
if(C_truep((C_word)C_i_caddr(t2))){
t4=(C_word)C_i_cadr(t2);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9759,a[2]=t1,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
t6=(C_word)C_i_caddr(t2);
C_trace("ChickenBridge.scm: 137  remove-token-type");
f_4472(t5,t6,C_fix(256));}
else{
t4=(C_word)C_i_cadr(t2);
t5=(C_word)C_a_i_list(&a,1,t4);
C_trace("ChickenBridge.scm: 137  make-parse-unit");
f_3137(t1,C_fix(29952),t5,C_SCHEME_FALSE);}}

/* k9757 in a9725 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9759(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9759,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[3],t1);
C_trace("ChickenBridge.scm: 137  make-parse-unit");
f_3137(((C_word*)t0)[2],C_fix(29952),t2,C_SCHEME_FALSE);}

/* k9718 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9720(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(29952),t1);}

/* k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4722(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4722,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4725,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9634,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
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
t20=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9640,a[2]=lf[555],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t3,lf[556],C_fix(30720),t19,t20,C_SCHEME_FALSE);}

/* a9639 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9640(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word *a;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_9640,4,t0,t1,t2,t3);}
C_trace("ChickenBridge.scm: 137  make-parse-unit");
f_3137(t1,C_fix(30720),t2,C_SCHEME_FALSE);}

/* k9632 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9634(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(30720),t1);}

/* k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4725(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4725,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4728,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9354,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(30720),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(256),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[139],t5);
t7=(C_word)C_a_i_cons(&a,2,t6,C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(30720),t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(16640),t8);
t10=(C_word)C_a_i_cons(&a,2,lf[176],t9);
t11=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9360,a[2]=lf[545],tmp=(C_word)a,a+=3,tmp);
t12=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9403,a[2]=lf[553],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t3,lf[554],C_fix(30464),t10,t11,t12);}

/* a9402 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9403(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_9403,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9407,a[2]=t1,a[3]=t4,a[4]=t3,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-parsed");
f_3176(t5,t2);}

/* k9405 in a9402 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9407(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_9407,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,lf[240]);
t3=t2;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_SCHEME_UNDEFINED;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=C_set_block_item(t6,0,(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_9415,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=t6,a[5]=t4,a[6]=t2,a[7]=lf[552],tmp=(C_word)a,a+=8,tmp));
t8=((C_word*)t6)[1];
f_9415(t8,((C_word*)t0)[2],t1);}

/* do979 in k9405 in a9402 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_9415(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_9415,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=(C_word)C_i_cddr(((C_word*)t0)[6]);
t4=(C_word)C_i_nullp(t3);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_truep(t4)?(C_word)C_i_cadr(((C_word*)t0)[6]):((C_word*)t0)[6]));}
else{
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_9438,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=t2,a[7]=((C_word*)t0)[5],tmp=(C_word)a,a+=8,tmp);
t4=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 137  parse-unit-parsed");
f_3176(t3,t4);}}

/* k9436 in do979 in k9405 in a9402 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9438(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9438,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_9441,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t3=(C_word)C_i_car(t1);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k9439 in k9436 in do979 in k9405 in a9402 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9441(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9441,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_9444,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],tmp=(C_word)a,a+=10,tmp);
t3=(C_word)C_i_cadr(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 137  parse-unit-type");
f_3158(t2,t3);}

/* k9442 in k9439 in k9436 in do979 in k9405 in a9402 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9444(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9444,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_9447,a[2]=t1,a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],tmp=(C_word)a,a+=8,tmp);
t3=(C_word)C_i_caddr(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k9445 in k9442 in k9439 in k9436 in do979 in k9405 in a9402 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9447(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9447,2,t0,t1);}
t2=C_SCHEME_FALSE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_9450,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=t3,tmp=(C_word)a,a+=8,tmp);
t5=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_9507,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t4,a[5]=t1,a[6]=t3,tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 137  SalType=?");
f_4428(t5,((C_word*)t0)[2],C_fix(10756));}

/* k9505 in k9445 in k9442 in k9439 in k9436 in do979 in k9405 in a9402 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9507(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9507,2,t0,t1);}
if(C_truep(t1)){
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,((C_word*)t0)[5]);
t3=((C_word*)t0)[4];
f_9450(t3,t2);}
else{
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_9514,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[3],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 137  SalType=?");
f_4428(t2,((C_word*)t0)[2],C_fix(11776));}}

/* k9512 in k9505 in k9445 in k9442 in k9439 in k9436 in do979 in k9405 in a9402 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9514(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[16],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9514,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,3,lf[215],((C_word*)t0)[6],((C_word*)t0)[5]);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t4=((C_word*)t0)[3];
f_9450(t4,t3);}
else{
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_9524,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 137  SalType=?");
f_4428(t2,((C_word*)t0)[2],C_fix(12032));}}

/* k9522 in k9512 in k9505 in k9445 in k9442 in k9439 in k9436 in do979 in k9405 in a9402 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
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
t2=(C_word)C_a_i_list(&a,3,lf[139],((C_word*)t0)[6],((C_word*)t0)[5]);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t4=((C_word*)t0)[3];
f_9450(t4,t3);}
else{
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_9534,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[5],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 137  SalType=?");
f_4428(t2,((C_word*)t0)[2],C_fix(12288));}}

/* k9532 in k9522 in k9512 in k9505 in k9445 in k9442 in k9439 in k9436 in do979 in k9405 in a9402 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9534(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9534,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,2,lf[549],((C_word*)t0)[6]);
t3=(C_word)C_a_i_list(&a,3,lf[193],((C_word*)t0)[5],t2);
t4=C_mutate(((C_word *)((C_word*)t0)[4])+1,t3);
t5=((C_word*)t0)[3];
f_9450(t5,t4);}
else{
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_9548,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 137  SalType=?");
f_4428(t2,((C_word*)t0)[2],C_fix(12544));}}

/* k9546 in k9532 in k9522 in k9512 in k9505 in k9445 in k9442 in k9439 in k9436 in do979 in k9405 in a9402 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9548(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[16],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9548,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,3,lf[550],((C_word*)t0)[6],((C_word*)t0)[5]);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t4=((C_word*)t0)[3];
f_9450(t4,t3);}
else{
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_9558,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[5],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 137  SalType=?");
f_4428(t2,((C_word*)t0)[2],C_fix(12800));}}

/* k9556 in k9546 in k9532 in k9522 in k9512 in k9505 in k9445 in k9442 in k9439 in k9436 in do979 in k9405 in a9402 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
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
t2=(C_word)C_a_i_list(&a,3,lf[193],((C_word*)t0)[6],((C_word*)t0)[5]);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t4=((C_word*)t0)[3];
f_9450(t4,t3);}
else{
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_9568,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 137  SalType=?");
f_4428(t2,((C_word*)t0)[2],C_fix(11012));}}

/* k9566 in k9556 in k9546 in k9532 in k9522 in k9512 in k9505 in k9445 in k9442 in k9439 in k9436 in do979 in k9405 in a9402 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9568(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[15],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9568,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,3,lf[551],((C_word*)t0)[6],((C_word*)t0)[5]);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t4=((C_word*)t0)[3];
f_9450(t4,t3);}
else{
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_9578,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 137  SalType=?");
f_4428(t2,((C_word*)t0)[2],C_fix(11268));}}

/* k9576 in k9566 in k9556 in k9546 in k9532 in k9522 in k9512 in k9505 in k9445 in k9442 in k9439 in k9436 in do979 in k9405 in a9402 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9578(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9578,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,3,lf[217],((C_word*)t0)[5],((C_word*)t0)[4]);
t3=C_mutate(((C_word *)((C_word*)t0)[3])+1,t2);
t4=((C_word*)t0)[2];
f_9450(t4,t3);}
else{
t2=((C_word*)t0)[2];
f_9450(t2,C_SCHEME_UNDEFINED);}}

/* k9448 in k9445 in k9442 in k9439 in k9436 in do979 in k9405 in a9402 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_9450(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_9450,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_9453,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9474,a[2]=t2,a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[2],tmp=(C_word)a,a+=5,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t0)[2]))){
t4=(C_word)C_i_car(((C_word*)t0)[2]);
t5=t3;
f_9474(t5,(C_word)C_eqp(t4,lf[548]));}
else{
t4=t3;
f_9474(t4,C_SCHEME_FALSE);}}

/* k9472 in k9448 in k9445 in k9442 in k9439 in k9436 in do979 in k9405 in a9402 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_9474(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_9474,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_cadr(((C_word*)t0)[4]);
t3=(C_word)C_i_caddr(((C_word*)t0)[4]);
t4=(C_word)C_a_i_list(&a,3,lf[546],t2,t3);
t5=(C_word)C_a_i_list(&a,3,lf[547],t4,((C_word*)((C_word*)t0)[3])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t5);
t7=((C_word*)t0)[2];
f_9453(t7,t6);}
else{
t2=(C_word)C_a_i_list(&a,3,lf[235],((C_word*)t0)[4],((C_word*)((C_word*)t0)[3])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[3])+1,t2);
t4=((C_word*)t0)[2];
f_9453(t4,t3);}}

/* k9451 in k9448 in k9445 in k9442 in k9439 in k9436 in do979 in k9405 in a9402 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_9453(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_9453,NULL,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,((C_word*)((C_word*)t0)[6])[1]);
t3=(C_word)C_i_set_cdr(((C_word*)((C_word*)t0)[5])[1],t2);
t4=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[5])[1]);
t5=C_mutate(((C_word *)((C_word*)t0)[5])+1,t4);
t6=(C_word)C_i_cdr(((C_word*)t0)[4]);
t7=((C_word*)((C_word*)t0)[3])[1];
f_9415(t7,((C_word*)t0)[2],t6);}

/* a9359 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9360(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_9360,4,t0,t1,t2,t3);}
if(C_truep((C_word)C_i_caddr(t2))){
t4=(C_word)C_i_cadr(t2);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9393,a[2]=t1,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
t6=(C_word)C_i_caddr(t2);
C_trace("ChickenBridge.scm: 137  remove-token-type");
f_4472(t5,t6,C_fix(256));}
else{
t4=(C_word)C_i_cadr(t2);
t5=(C_word)C_a_i_list(&a,1,t4);
C_trace("ChickenBridge.scm: 137  make-parse-unit");
f_3137(t1,C_fix(30464),t5,C_SCHEME_FALSE);}}

/* k9391 in a9359 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9393(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9393,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[3],t1);
C_trace("ChickenBridge.scm: 137  make-parse-unit");
f_3137(((C_word*)t0)[2],C_fix(30464),t2,C_SCHEME_FALSE);}

/* k9352 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9354(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(30464),t1);}

/* k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4728(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4728,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4731,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9240,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29952),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,lf[214],t4);
t6=(C_word)C_a_i_cons(&a,2,C_fix(36608),C_SCHEME_END_OF_LIST);
t7=(C_word)C_a_i_cons(&a,2,lf[139],t6);
t8=(C_word)C_a_i_cons(&a,2,C_fix(18193),C_SCHEME_END_OF_LIST);
t9=(C_word)C_a_i_cons(&a,2,t7,t8);
t10=(C_word)C_a_i_cons(&a,2,t5,t9);
t11=(C_word)C_a_i_cons(&a,2,C_fix(13328),t10);
t12=(C_word)C_a_i_cons(&a,2,lf[176],t11);
t13=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9246,a[2]=lf[542],tmp=(C_word)a,a+=3,tmp);
t14=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9272,a[2]=lf[543],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t3,lf[544],C_fix(32000),t12,t13,t14);}

/* a9271 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9272(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_9272,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9276,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-parsed");
f_3176(t5,t2);}

/* k9274 in a9271 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9276(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9276,2,t0,t1);}
t2=(C_word)C_i_car(t1);
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_9282,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t2,tmp=(C_word)a,a+=6,tmp);
t4=(C_word)C_i_cdr(t1);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t3,t4,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k9280 in k9274 in a9271 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9282(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9282,2,t0,t1);}
if(C_truep(((C_word*)t0)[5])){
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9302,a[2]=((C_word*)t0)[4],a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t2,((C_word*)t0)[5],((C_word*)t0)[3],((C_word*)t0)[2]);}
else{
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_cons(&a,2,lf[240],t1));}}

/* k9300 in k9280 in k9274 in a9271 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9302(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9302,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,t1,((C_word*)t0)[3]);
t3=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_cons(&a,2,lf[446],t2));}

/* a9245 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9246(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_9246,4,t0,t1,t2,t3);}
t4=(C_word)C_i_cadr(t2);
t5=t4;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(C_word)C_i_caddr(t2);
t8=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9256,a[2]=t1,a[3]=t7,a[4]=t6,tmp=(C_word)a,a+=5,tmp);
t9=((C_word*)t6)[1];
if(C_truep(t9)){
t10=(C_word)C_i_car(((C_word*)t6)[1]);
t11=C_set_block_item(t6,0,t10);
t12=t8;
f_9256(t12,t11);}
else{
t10=t8;
f_9256(t10,C_SCHEME_FALSE);}}

/* k9254 in a9245 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_9256(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_9256,NULL,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)((C_word*)t0)[4])[1],((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 137  make-parse-unit");
f_3137(((C_word*)t0)[2],C_fix(32000),t2,C_SCHEME_FALSE);}

/* k9238 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9240(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(32000),t1);}

/* k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4731(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4731,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4734,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9043,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
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
t27=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9049,a[2]=lf[539],tmp=(C_word)a,a+=3,tmp);
t28=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9117,a[2]=lf[540],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t3,lf[541],C_fix(32256),t26,t27,t28);}

/* a9116 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9117(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_9117,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9121,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-parsed");
f_3176(t5,t2);}

/* k9119 in a9116 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9121(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  emit");
f_3294(((C_word*)t0)[4],t1,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* a9048 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9049(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_9049,4,t0,t1,t2,t3);}
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cadr(t2);
t6=C_SCHEME_END_OF_LIST;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9062,a[2]=t7,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
t9=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_9068,a[2]=t8,a[3]=t7,a[4]=t5,a[5]=t4,a[6]=t2,tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 137  token-unit-type=?");
f_3222(t9,t4,C_fix(14336));}

/* k9066 in a9048 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9068(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_9068,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_cadddr(((C_word*)t0)[6]);
t3=t2;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=C_SCHEME_FALSE;
t8=(*a=C_VECTOR_TYPE|1,a[1]=t7,tmp=(C_word)a,a+=2,tmp);
t9=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_9074,a[2]=((C_word*)t0)[6],a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=t8,a[6]=t6,a[7]=((C_word*)t0)[4],a[8]=((C_word*)t0)[5],a[9]=t4,tmp=(C_word)a,a+=10,tmp);
t10=((C_word*)t4)[1];
if(C_truep(t10)){
t11=(C_word)C_i_car(((C_word*)t4)[1]);
t12=C_set_block_item(t6,0,t11);
t13=t9;
f_9074(t13,t12);}
else{
t11=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9103,a[2]=t9,a[3]=t6,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  make-parse-unit");
f_3137(t11,C_fix(4608),lf[538],C_SCHEME_FALSE);}}
else{
t2=(C_word)C_i_caddr(((C_word*)t0)[6]);
t3=(C_word)C_a_i_list(&a,3,((C_word*)t0)[5],((C_word*)t0)[4],t2);
t4=C_mutate(((C_word *)((C_word*)t0)[3])+1,t3);
t5=((C_word*)t0)[2];
f_9062(t5,t4);}}

/* k9101 in k9066 in a9048 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9103(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_9074(t3,t2);}

/* k9072 in k9066 in a9048 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_9074(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_9074,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_9078,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],a[8]=((C_word*)t0)[9],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 137  fifth");
t3=C_retrieve(lf[243]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)t0)[2]);}

/* k9076 in k9072 in k9066 in a9048 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9078(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_9078,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_9081,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
t4=((C_word*)((C_word*)t0)[8])[1];
if(C_truep(t4)){
t5=(C_word)C_i_cadr(((C_word*)((C_word*)t0)[8])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[4])+1,t5);
t7=t3;
f_9081(t7,t6);}
else{
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9092,a[2]=t3,a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  make-parse-unit");
f_3137(t5,C_fix(4608),lf[537],C_SCHEME_FALSE);}}

/* k9090 in k9076 in k9072 in k9066 in a9048 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9092(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_9081(t3,t2);}

/* k9079 in k9076 in k9072 in k9066 in a9048 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_9081(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_9081,NULL,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,4,((C_word*)t0)[7],((C_word*)t0)[6],((C_word*)((C_word*)t0)[5])[1],((C_word*)((C_word*)t0)[4])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[3])+1,t2);
t4=((C_word*)t0)[2];
f_9062(t4,t3);}

/* k9060 in a9048 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_9062(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  make-parse-unit");
f_3137(((C_word*)t0)[3],C_fix(32256),((C_word*)((C_word*)t0)[2])[1],C_SCHEME_FALSE);}

/* k9041 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_9043(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(32256),t1);}

/* k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4734(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4734,2,t0,t1);}
t2=C_mutate(&lf[234],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4736,a[2]=lf[255],tmp=(C_word)a,a+=3,tmp));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5257,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8771,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
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
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t4,lf[536],C_fix(33024),t59,C_retrieve2(lf[234],"sal-parse-stepping"),C_SCHEME_FALSE);}

/* k8769 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8771(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(33024),t1);}

/* k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5257(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5257,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5260,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8715,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(20224),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[176],t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(19456),t7);
t9=(C_word)C_a_i_cons(&a,2,lf[176],t8);
t10=(C_word)C_a_i_cons(&a,2,t9,C_SCHEME_END_OF_LIST);
t11=(C_word)C_a_i_cons(&a,2,t6,t10);
t12=(C_word)C_a_i_cons(&a,2,lf[177],t11);
t13=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8723,a[2]=t12,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  simple-unit-parser");
f_3535(t13,C_fix(33280));}

/* k8721 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8723(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(((C_word*)t0)[3],lf[535],C_fix(33280),((C_word*)t0)[2],t1,C_SCHEME_FALSE);}

/* k8713 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8715(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(33280),t1);}

/* k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5260(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5260,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5779,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8543,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
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
t26=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8549,a[2]=lf[519],tmp=(C_word)a,a+=3,tmp);
t27=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8595,a[2]=lf[533],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t3,lf[534],C_fix(32512),t25,t26,t27);}

/* a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8595(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[7],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_8595,5,t0,t1,t2,t3,t4);}
t5=t3;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5266,a[2]=t4,a[3]=t6,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-parsed");
f_3176(t7,t2);}

/* k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5266(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5266,2,t0,t1);}
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
t16=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_5284,a[2]=t11,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=t7,a[6]=((C_word*)t0)[4],a[7]=t15,a[8]=t13,a[9]=t5,a[10]=t9,a[11]=t3,tmp=(C_word)a,a+=12,tmp);
t17=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5738,a[2]=t3,a[3]=((C_word*)t0)[2],a[4]=t5,a[5]=t16,a[6]=((C_word*)t0)[3],tmp=(C_word)a,a+=7,tmp);
t18=(C_word)C_i_car(((C_word*)t3)[1]);
C_trace("ChickenBridge.scm: 137  token-unit-type=?");
f_3222(t17,t18,C_fix(14864));}

/* k5736 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5738(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[14],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5738,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5742,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  add-emit-info");
f_3266(t2,lf[530],C_SCHEME_TRUE,((C_word*)((C_word*)t0)[6])[1]);}
else{
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5745,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5772,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  get-emit-info");
f_3254(t3,lf[513],((C_word*)((C_word*)t0)[6])[1]);}}

/* k5770 in k5736 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5772(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5772,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
f_5745(2,t2,C_SCHEME_UNDEFINED);}
else{
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5760,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[3],tmp=(C_word)a,a+=4,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5764,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_i_car(((C_word*)((C_word*)t0)[2])[1]);
C_trace("ChickenBridge.scm: 137  parse-unit-position");
f_3194(t3,t4);}}

/* k5762 in k5770 in k5736 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5764(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  make-parse-error");
f_3086(((C_word*)t0)[2],lf[532],t1);}

/* k5758 in k5770 in k5736 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5760(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  errf");
t2=((C_word*)t0)[3];
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k5743 in k5736 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5745(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5745,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5749,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  add-emit-info");
f_3266(t2,lf[531],C_SCHEME_TRUE,((C_word*)((C_word*)t0)[4])[1]);}

/* k5747 in k5743 in k5736 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5749(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[4])+1,t1);
t3=C_set_block_item(((C_word*)t0)[3],0,C_SCHEME_TRUE);
t4=((C_word*)t0)[2];
f_5284(t4,t3);}

/* k5740 in k5736 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5742(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_5284(t3,t2);}

/* k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_5284(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_5284,NULL,2,t0,t1);}
t2=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[11])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[11])+1,t2);
t4=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_5291,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[11],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],a[10]=((C_word*)t0)[9],a[11]=((C_word*)t0)[10],tmp=(C_word)a,a+=12,tmp);
if(C_truep((C_word)C_i_car(((C_word*)((C_word*)t0)[11])[1]))){
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5727,a[2]=t4,a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5731,a[2]=((C_word*)t0)[5],a[3]=t5,tmp=(C_word)a,a+=4,tmp);
t7=(C_word)C_i_car(((C_word*)((C_word*)t0)[11])[1]);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t6,t7,((C_word*)((C_word*)t0)[4])[1],((C_word*)t0)[3]);}
else{
t5=t4;
f_5291(t5,C_SCHEME_UNDEFINED);}}

/* k5729 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5731(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  append");
t2=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k5725 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5727(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_5291(t3,t2);}

/* k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_5291(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_5291,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_5294,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],a[10]=((C_word*)t0)[10],a[11]=((C_word*)t0)[11],tmp=(C_word)a,a+=12,tmp);
t3=(C_word)C_i_cadr(((C_word*)((C_word*)t0)[3])[1]);
t4=C_SCHEME_UNDEFINED;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_set_block_item(t5,0,(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5602,a[2]=((C_word*)t0)[11],a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[9],a[5]=((C_word*)t0)[6],a[6]=t5,a[7]=lf[529],tmp=(C_word)a,a+=8,tmp));
t7=((C_word*)t5)[1];
f_5602(t7,t2,t3);}

/* do1089 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_5602(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5602,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5612,a[2]=t1,a[3]=((C_word*)t0)[6],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5623,a[2]=t3,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],tmp=(C_word)a,a+=7,tmp);
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 137  parse-unit-parsed");
f_3176(t4,t5);}}

/* k5621 in do1089 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5623(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5623,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5625,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=t3,a[6]=((C_word*)t0)[6],a[7]=lf[528],tmp=(C_word)a,a+=8,tmp));
t5=((C_word*)t3)[1];
f_5625(t5,((C_word*)t0)[2],t1);}

/* do1092 in k5621 in do1089 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_5625(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_5625,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(C_word)C_i_car(t2);
t4=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_5639,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t3,a[5]=((C_word*)t0)[4],a[6]=t1,a[7]=((C_word*)t0)[5],a[8]=t2,a[9]=((C_word*)t0)[6],tmp=(C_word)a,a+=10,tmp);
t5=(C_word)C_i_car(t3);
t6=(C_word)C_i_cadr(t3);
t7=(C_word)C_a_i_list(&a,2,t5,t6);
t8=(C_word)C_a_i_list(&a,1,t7);
C_trace("ChickenBridge.scm: 137  append");
t9=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t9))(4,t9,t4,((C_word*)((C_word*)t0)[6])[1],t8);}}

/* k5637 in do1092 in k5621 in do1089 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5639(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5639,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[9])+1,t1);
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5642,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],tmp=(C_word)a,a+=8,tmp);
if(C_truep((C_word)C_i_caddr(((C_word*)t0)[4]))){
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5692,a[2]=t3,a[3]=((C_word*)t0)[2],tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_i_caddr(((C_word*)t0)[4]);
t6=(C_word)C_a_i_list(&a,1,t5);
C_trace("ChickenBridge.scm: 137  append");
t7=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t7))(4,t7,t4,((C_word*)((C_word*)t0)[2])[1],t6);}
else{
t4=t3;
f_5642(t4,C_SCHEME_UNDEFINED);}}

/* k5690 in k5637 in do1092 in k5621 in do1089 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5692(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_5642(t3,t2);}

/* k5640 in k5637 in do1092 in k5621 in do1089 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_5642(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[14],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5642,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5645,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
if(C_truep((C_word)C_i_cadddr(((C_word*)t0)[3]))){
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5677,a[2]=t2,a[3]=((C_word*)t0)[2],tmp=(C_word)a,a+=4,tmp);
t4=(C_word)C_i_cadddr(((C_word*)t0)[3]);
t5=(C_word)C_a_i_list(&a,1,t4);
C_trace("ChickenBridge.scm: 137  append");
t6=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t3,((C_word*)((C_word*)t0)[2])[1],t5);}
else{
t3=t2;
f_5645(t3,C_SCHEME_UNDEFINED);}}

/* k5675 in k5640 in k5637 in do1092 in k5621 in do1089 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5677(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_5645(t3,t2);}

/* k5643 in k5640 in k5637 in do1092 in k5621 in do1089 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_5645(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5645,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5648,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5658,a[2]=((C_word*)t0)[2],a[3]=t2,a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  fifth");
t4=C_retrieve(lf[243]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)t0)[2]);}

/* k5656 in k5643 in k5640 in k5637 in do1092 in k5621 in do1089 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5658(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5658,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5662,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5670,a[2]=((C_word*)t0)[4],a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  fifth");
t4=C_retrieve(lf[243]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)t0)[2]);}
else{
t2=((C_word*)t0)[3];
f_5648(t2,C_SCHEME_UNDEFINED);}}

/* k5668 in k5656 in k5643 in k5640 in k5637 in do1092 in k5621 in do1089 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5670(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5670,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,t1);
C_trace("ChickenBridge.scm: 137  append");
t3=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t2);}

/* k5660 in k5656 in k5643 in k5640 in k5637 in do1092 in k5621 in do1089 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5662(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_5648(t3,t2);}

/* k5646 in k5643 in k5640 in k5637 in do1092 in k5621 in do1089 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_5648(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_5625(t3,((C_word*)t0)[2],t2);}

/* k5610 in do1089 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5612(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_5602(t3,((C_word*)t0)[2],t2);}

/* k5292 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5294(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5294,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_5297,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],a[10]=((C_word*)t0)[10],a[11]=((C_word*)t0)[11],tmp=(C_word)a,a+=12,tmp);
t3=(C_word)C_i_cadddr(((C_word*)((C_word*)t0)[3])[1]);
t4=C_SCHEME_UNDEFINED;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_set_block_item(t5,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5566,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=t5,a[5]=((C_word*)t0)[11],a[6]=lf[527],tmp=(C_word)a,a+=7,tmp));
t7=((C_word*)t5)[1];
f_5566(t7,t2,t3);}

/* do1103 in k5292 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_5566(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5566,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_5577,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=t2,a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5592,a[2]=((C_word*)t0)[5],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t4,t5,((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]);}}

/* k5590 in do1103 in k5292 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5592(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5592,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,t1);
C_trace("ChickenBridge.scm: 137  append");
t3=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t2);}

/* k5575 in do1103 in k5292 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5577(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[5])+1,t1);
t3=(C_word)C_i_cdr(((C_word*)t0)[4]);
t4=((C_word*)((C_word*)t0)[3])[1];
f_5566(t4,((C_word*)t0)[2],t3);}

/* k5295 in k5292 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5297(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5297,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_5301,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],a[8]=((C_word*)t0)[9],a[9]=((C_word*)t0)[10],a[10]=((C_word*)t0)[11],tmp=(C_word)a,a+=11,tmp);
C_trace("ChickenBridge.scm: 137  append");
t3=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t2,((C_word*)((C_word*)t0)[11])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k5299 in k5295 in k5292 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5301(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5301,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[10])+1,t1);
t3=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_5304,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[10],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],a[10]=((C_word*)t0)[9],tmp=(C_word)a,a+=11,tmp);
t4=(C_word)C_i_caddr(((C_word*)((C_word*)t0)[2])[1]);
t5=C_SCHEME_UNDEFINED;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=C_set_block_item(t6,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5510,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=t6,a[5]=((C_word*)t0)[8],a[6]=lf[526],tmp=(C_word)a,a+=7,tmp));
t8=((C_word*)t6)[1];
f_5510(t8,t3,t4);}

/* do1108 in k5299 in k5295 in k5292 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_5510(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5510,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5520,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=t2,a[7]=((C_word*)t0)[5],tmp=(C_word)a,a+=8,tmp);
t4=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 137  parse-unit-parsed");
f_3176(t3,t4);}}

/* k5518 in do1108 in k5299 in k5295 in k5292 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5520(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5520,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5523,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
t3=(C_word)C_i_cadr(t1);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t2,t3,((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]);}

/* k5521 in k5518 in do1108 in k5299 in k5295 in k5292 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5523(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5523,2,t0,t1);}
t2=t1;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5526,a[2]=t3,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5544,a[2]=t4,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t6=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 137  token-unit-type=?");
f_3222(t5,t6,C_fix(20224));}

/* k5542 in k5521 in k5518 in do1108 in k5299 in k5295 in k5292 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5544(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5544,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,2,lf[178],((C_word*)((C_word*)t0)[3])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[3])+1,t2);
t4=((C_word*)t0)[2];
f_5526(t4,t3);}
else{
t2=((C_word*)t0)[2];
f_5526(t2,C_SCHEME_UNDEFINED);}}

/* k5524 in k5521 in k5518 in do1108 in k5299 in k5295 in k5292 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_5526(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5526,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_5530,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],tmp=(C_word)a,a+=6,tmp);
t3=(C_word)C_a_i_list(&a,1,((C_word*)((C_word*)t0)[2])[1]);
C_trace("ChickenBridge.scm: 137  append");
t4=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,((C_word*)((C_word*)t0)[6])[1],t3);}

/* k5528 in k5524 in k5521 in k5518 in do1108 in k5299 in k5295 in k5292 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5530(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[5])+1,t1);
t3=(C_word)C_i_cdr(((C_word*)t0)[4]);
t4=((C_word*)((C_word*)t0)[3])[1];
f_5510(t4,((C_word*)t0)[2],t3);}

/* k5302 in k5299 in k5295 in k5292 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5304(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5304,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_5307,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],a[10]=((C_word*)t0)[10],tmp=(C_word)a,a+=11,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)((C_word*)t0)[9])[1]))){
t3=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[9])[1]);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(C_word)C_i_car(((C_word*)((C_word*)t0)[9])[1]);
t5=C_mutate(((C_word *)((C_word*)t0)[9])+1,t4);
t6=t2;
f_5307(t6,t5);}
else{
t4=(C_word)C_a_i_cons(&a,2,lf[177],((C_word*)((C_word*)t0)[9])[1]);
t5=C_mutate(((C_word *)((C_word*)t0)[9])+1,t4);
t6=t2;
f_5307(t6,t5);}}
else{
t3=C_set_block_item(((C_word*)t0)[9],0,C_SCHEME_FALSE);
t4=t2;
f_5307(t4,t3);}}

/* k5305 in k5302 in k5299 in k5295 in k5292 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_5307(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[15],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5307,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5310,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],a[5]=((C_word*)t0)[8],a[6]=((C_word*)t0)[9],a[7]=((C_word*)t0)[10],tmp=(C_word)a,a+=8,tmp);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5473,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t2,a[6]=((C_word*)t0)[8],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 137  fifth");
t4=C_retrieve(lf[243]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)((C_word*)t0)[2])[1]);}

/* k5471 in k5305 in k5302 in k5299 in k5295 in k5292 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5473(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5473,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5477,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],tmp=(C_word)a,a+=4,tmp);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5481,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  fifth");
t4=C_retrieve(lf[243]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)((C_word*)t0)[2])[1]);}
else{
t2=C_set_block_item(((C_word*)t0)[6],0,C_SCHEME_FALSE);
t3=((C_word*)t0)[5];
f_5310(t3,t2);}}

/* k5479 in k5471 in k5305 in k5302 in k5299 in k5295 in k5292 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5481(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  emit");
f_3294(((C_word*)t0)[4],t1,((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]);}

/* k5475 in k5471 in k5305 in k5302 in k5299 in k5295 in k5292 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5477(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_5310(t3,t2);}

/* k5308 in k5305 in k5302 in k5299 in k5295 in k5292 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_5310(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_5310,NULL,2,t0,t1);}
t2=((C_word*)((C_word*)t0)[7])[1];
if(C_truep(t2)){
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5338,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 137  gensym");
t4=C_retrieve(lf[237]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,lf[524]);}
else{
t3=(C_word)C_a_i_list(&a,2,((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[5])[1]);
t4=(C_word)C_a_i_cons(&a,2,t3,((C_word*)((C_word*)t0)[2])[1]);
t5=(C_word)C_a_i_cons(&a,2,C_SCHEME_END_OF_LIST,t4);
t6=(C_word)C_a_i_cons(&a,2,lf[525],t5);
t7=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)C_a_i_list(&a,3,lf[446],((C_word*)((C_word*)t0)[3])[1],t6));}}

/* k5336 in k5308 in k5305 in k5302 in k5299 in k5295 in k5292 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5338(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5338,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5341,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 137  gensym");
t3=C_retrieve(lf[237]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,lf[523]);}

/* k5339 in k5336 in k5308 in k5305 in k5302 in k5299 in k5295 in k5292 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5341(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5341,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_5344,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 137  gensym");
t3=C_retrieve(lf[237]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,lf[522]);}

/* k5342 in k5339 in k5336 in k5308 in k5305 in k5302 in k5299 in k5295 in k5292 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5344(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5344,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_5347,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 137  gensym");
t3=C_retrieve(lf[237]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,lf[521]);}

/* k5345 in k5342 in k5339 in k5336 in k5308 in k5305 in k5302 in k5299 in k5295 in k5292 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5347(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5347,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,((C_word*)t0)[9]);
t3=(C_word)C_a_i_list(&a,2,((C_word*)t0)[8],C_fix(0));
t4=(C_word)C_a_i_list(&a,3,lf[442],C_SCHEME_END_OF_LIST,((C_word*)t0)[9]);
t5=(C_word)C_a_i_list(&a,2,lf[443],t4);
t6=(C_word)C_a_i_list(&a,1,lf[444]);
t7=(C_word)C_a_i_list(&a,3,lf[235],((C_word*)t0)[8],lf[444]);
t8=(C_word)C_a_i_list(&a,3,lf[442],t6,t7);
t9=(C_word)C_a_i_list(&a,2,lf[445],t8);
t10=(C_word)C_a_i_list(&a,3,t3,t5,t9);
t11=(C_word)C_a_i_list(&a,1,t1);
t12=(C_word)C_a_i_list(&a,1,((C_word*)t0)[7]);
t13=(C_word)C_a_i_list(&a,2,lf[447],lf[448]);
t14=(C_word)C_a_i_list(&a,2,lf[447],lf[449]);
t15=(C_word)C_a_i_list(&a,3,lf[450],t13,t14);
t16=(C_word)C_a_i_list(&a,2,t15,((C_word*)t0)[7]);
t17=(C_word)C_a_i_list(&a,4,lf[286],lf[520],t16,((C_word*)t0)[9]);
t18=(C_word)C_a_i_list(&a,2,lf[260],t17);
t19=(C_word)C_a_i_list(&a,2,t1,C_fix(-2));
t20=(C_word)C_a_i_list(&a,4,lf[442],t12,t18,t19);
t21=(C_word)C_a_i_list(&a,3,((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[5])[1],C_fix(-1));
t22=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_5406,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=t2,a[5]=t10,a[6]=t11,a[7]=t20,a[8]=t21,tmp=(C_word)a,a+=9,tmp);
t23=(C_word)C_a_i_list(&a,1,((C_word*)t0)[8]);
C_trace("##sys#append");
t24=*((C_word*)lf[454]+1);
((C_proc4)(void*)(*((C_word*)t24+1)))(4,t24,t22,((C_word*)((C_word*)t0)[2])[1],t23);}

/* k5404 in k5345 in k5342 in k5339 in k5336 in k5308 in k5305 in k5302 in k5299 in k5295 in k5292 in k5289 in k5282 in k5264 in a8594 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5406(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5406,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,lf[440],t1);
t3=(C_word)C_a_i_list(&a,3,lf[441],((C_word*)t0)[8],t2);
t4=(C_word)C_a_i_list(&a,3,lf[442],C_SCHEME_END_OF_LIST,t3);
t5=(C_word)C_a_i_list(&a,3,lf[452],((C_word*)t0)[7],t4);
t6=(C_word)C_a_i_list(&a,3,lf[442],((C_word*)t0)[6],t5);
t7=(C_word)C_a_i_list(&a,2,lf[453],t6);
t8=(C_word)C_a_i_list(&a,3,lf[446],((C_word*)t0)[5],t7);
t9=(C_word)C_a_i_list(&a,3,lf[442],((C_word*)t0)[4],t8);
t10=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t10+1)))(2,t10,(C_word)C_a_i_list(&a,3,lf[446],((C_word*)((C_word*)t0)[2])[1],t9));}

/* a8548 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8549(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_8549,4,t0,t1,t2,t3);}
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cadr(t2);
t6=t5;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=(C_word)C_i_caddr(t2);
t9=(C_word)C_i_cadddr(t2);
t10=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_8565,a[2]=t2,a[3]=t1,a[4]=t9,a[5]=t8,a[6]=t7,a[7]=t4,tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 137  fifth");
t11=C_retrieve(lf[243]);
((C_proc3)C_retrieve_proc(t11))(3,t11,t10,t2);}

/* k8563 in a8548 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8565(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8565,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_8568,a[2]=((C_word*)t0)[3],a[3]=t1,a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 137  sixth");
t3=C_retrieve(lf[319]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)t0)[2]);}

/* k8566 in k8563 in a8548 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8568(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_8568,2,t0,t1);}
t2=t1;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_8571,a[2]=((C_word*)t0)[2],a[3]=t3,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
if(C_truep(((C_word*)((C_word*)t0)[6])[1])){
t5=(C_word)C_i_car(((C_word*)((C_word*)t0)[6])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[6])+1,t5);
t7=t4;
f_8571(t7,t6);}
else{
t5=t4;
f_8571(t5,C_SCHEME_UNDEFINED);}}

/* k8569 in k8566 in k8563 in a8548 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_8571(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_8571,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_8574,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
if(C_truep(((C_word*)((C_word*)t0)[3])[1])){
t3=(C_word)C_i_cadr(((C_word*)((C_word*)t0)[3])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[3])+1,t3);
t5=t2;
f_8574(t5,t4);}
else{
t3=t2;
f_8574(t3,C_SCHEME_UNDEFINED);}}

/* k8572 in k8569 in k8566 in k8563 in a8548 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_8574(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_8574,NULL,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,6,((C_word*)t0)[8],((C_word*)((C_word*)t0)[7])[1],((C_word*)t0)[6],((C_word*)t0)[5],((C_word*)t0)[4],((C_word*)((C_word*)t0)[3])[1]);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8585,a[2]=t2,a[3]=((C_word*)t0)[2],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-position");
f_3194(t3,((C_word*)t0)[8]);}

/* k8583 in k8572 in k8569 in k8566 in k8563 in a8548 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8585(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  make-parse-unit");
f_3137(((C_word*)t0)[3],C_fix(32512),((C_word*)t0)[2],t1);}

/* k8541 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8543(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(32512),t1);}

/* k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5779(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5779,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5782,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8398,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
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
t22=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8404,a[2]=lf[517],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t3,lf[518],C_fix(37632),t21,t22,C_SCHEME_FALSE);}

/* a8403 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8404(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_8404,4,t0,t1,t2,t3);}
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cadr(t2);
t6=t5;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=(C_word)C_i_caddr(t2);
t9=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_8417,a[2]=t1,a[3]=t8,a[4]=t7,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
t10=(C_word)C_i_length(((C_word*)t7)[1]);
if(C_truep((C_word)C_i_nequalp(t10,C_fix(2)))){
t11=C_set_block_item(t7,0,C_SCHEME_END_OF_LIST);
t12=t9;
f_8417(t12,t11);}
else{
t11=(C_word)C_i_cadr(((C_word*)t7)[1]);
t12=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_8443,a[2]=t9,a[3]=t7,a[4]=t11,tmp=(C_word)a,a+=5,tmp);
t13=(C_word)C_i_caddr(((C_word*)t7)[1]);
C_trace("ChickenBridge.scm: 137  remove-token-type");
f_4472(t12,t13,C_fix(256));}}

/* k8441 in a8403 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8443(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8443,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[4],t1);
t3=C_mutate(((C_word *)((C_word*)t0)[3])+1,t2);
t4=((C_word*)t0)[2];
f_8417(t4,t3);}

/* k8415 in a8403 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_8417(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_8417,NULL,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,3,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 137  make-parse-unit");
f_3137(((C_word*)t0)[2],C_fix(37632),t2,C_SCHEME_FALSE);}

/* k8396 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8398(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(37632),t1);}

/* k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5782(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5782,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5785,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7941,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
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
t24=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7947,a[2]=lf[500],tmp=(C_word)a,a+=3,tmp);
t25=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7986,a[2]=lf[515],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t3,lf[516],C_fix(36352),t23,t24,t25);}

/* a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7986(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[7],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_7986,5,t0,t1,t2,t3,t4);}
t5=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7990,a[2]=t4,a[3]=t5,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-parsed");
f_3176(t6,t2);}

/* k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7990(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_7990,2,t0,t1);}
t2=(C_word)C_i_car(t1);
t3=(C_word)C_a_i_list(&a,1,lf[240]);
t4=t3;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7999,a[2]=t3,a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
t7=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_8002,a[2]=t2,a[3]=t3,a[4]=t6,a[5]=((C_word*)t0)[2],a[6]=((C_word*)t0)[3],a[7]=t5,a[8]=t1,tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 137  token-unit-type=?");
f_3222(t7,t2,C_fix(24576));}

/* k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8002(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_8002,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_cdr(((C_word*)t0)[8]);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_8011,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=t4,a[5]=((C_word*)t0)[7],a[6]=lf[503],tmp=(C_word)a,a+=7,tmp));
t6=((C_word*)t4)[1];
f_8011(t6,((C_word*)t0)[4],t2);}
else{
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_8060,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],tmp=(C_word)a,a+=7,tmp);
t3=(C_word)C_i_cadr(((C_word*)t0)[8]);
C_trace("ChickenBridge.scm: 137  parse-unit-parsed");
f_3176(t2,t3);}}

/* k8058 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8060(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8060,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_8063,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,tmp=(C_word)a,a+=8,tmp);
t3=(C_word)C_i_car(t1);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t2,t3,((C_word*)((C_word*)t0)[4])[1],((C_word*)t0)[3]);}

/* k8061 in k8058 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8063(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8063,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_8066,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=t1,tmp=(C_word)a,a+=9,tmp);
t3=(C_word)C_i_cadr(((C_word*)t0)[7]);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t2,t3,((C_word*)((C_word*)t0)[4])[1],((C_word*)t0)[3]);}

/* k8064 in k8061 in k8058 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8066(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8066,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_8278,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 137  append");
t3=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t2,t1,C_SCHEME_END_OF_LIST);}

/* k8276 in k8064 in k8061 in k8058 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8278(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_8278,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[9],t1);
t3=(C_word)C_i_caddr(((C_word*)t0)[8]);
t4=C_SCHEME_FALSE;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_SCHEME_FALSE;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_8075,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t3,a[5]=t2,a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[9],a[8]=((C_word*)t0)[5],a[9]=((C_word*)t0)[6],a[10]=((C_word*)t0)[7],a[11]=t7,a[12]=t5,tmp=(C_word)a,a+=13,tmp);
t9=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t9))){
t10=t8;
f_8075(t10,C_SCHEME_UNDEFINED);}
else{
t10=(C_word)C_i_length(t2);
t11=(C_word)C_a_i_minus(&a,2,t10,C_fix(2));
t12=(C_word)C_i_list_tail(t2,t11);
t13=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8216,a[2]=t12,a[3]=t8,tmp=(C_word)a,a+=4,tmp);
t14=(C_word)C_i_cadr(t12);
C_trace("ChickenBridge.scm: 137  symbol->string");
t15=*((C_word*)lf[413]+1);
((C_proc3)C_retrieve_proc(t15))(3,t15,t13,t14);}}

/* k8214 in k8276 in k8064 in k8061 in k8058 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8216(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[13],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8216,2,t0,t1);}
t2=(C_word)C_i_string_length(t1);
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_8225,a[2]=t1,a[3]=t2,a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_greaterp(t2,C_fix(3)))){
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8250,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
t5=(C_word)C_a_i_minus(&a,2,t2,C_fix(3));
C_trace("ChickenBridge.scm: 137  substring");
t6=*((C_word*)lf[264]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t4,t1,t5);}
else{
t4=t3;
f_8225(t4,C_SCHEME_FALSE);}}

/* k8248 in k8214 in k8276 in k8064 in k8061 in k8058 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8250(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_8225(t2,(C_word)C_i_string_equal_p(t1,lf[514]));}

/* k8223 in k8214 in k8276 in k8064 in k8061 in k8058 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_8225(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_8225,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8232,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8236,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_minus(&a,2,((C_word*)t0)[3],C_fix(3));
C_trace("ChickenBridge.scm: 137  substring");
t5=*((C_word*)lf[264]+1);
((C_proc5)C_retrieve_proc(t5))(5,t5,t3,((C_word*)t0)[2],C_fix(0),t4);}
else{
t2=((C_word*)t0)[5];
f_8075(t2,C_SCHEME_UNDEFINED);}}

/* k8234 in k8223 in k8214 in k8276 in k8064 in k8061 in k8058 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8236(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  string->symbol");
t2=*((C_word*)lf[173]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k8230 in k8223 in k8214 in k8276 in k8064 in k8061 in k8058 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8232(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
f_8075(t2,(C_word)C_i_set_cdr(((C_word*)t0)[2],t1));}

/* k8073 in k8276 in k8064 in k8061 in k8058 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_8075(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[18],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_8075,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_8078,a[2]=((C_word*)t0)[7],a[3]=((C_word*)t0)[8],a[4]=((C_word*)t0)[9],a[5]=((C_word*)t0)[10],a[6]=((C_word*)t0)[11],a[7]=((C_word*)t0)[12],tmp=(C_word)a,a+=8,tmp);
t3=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_8153,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t2,a[6]=((C_word*)t0)[12],a[7]=((C_word*)t0)[5],a[8]=((C_word*)t0)[11],a[9]=((C_word*)t0)[6],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 137  token-unit-type=?");
f_3222(t3,((C_word*)t0)[2],C_fix(24064));}

/* k8151 in k8073 in k8276 in k8064 in k8061 in k8058 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8153(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[18],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8153,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_8157,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],a[8]=((C_word*)t0)[9],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 137  add-emit-info");
f_3266(t2,lf[511],C_SCHEME_TRUE,((C_word*)((C_word*)t0)[9])[1]);}
else{
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_8194,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],a[8]=((C_word*)t0)[9],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 137  token-unit-type=?");
f_3222(t2,((C_word*)t0)[2],C_fix(24320));}}

/* k8192 in k8151 in k8073 in k8276 in k8064 in k8061 in k8058 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8194(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8194,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_8198,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 137  add-emit-info");
f_3266(t2,lf[513],C_SCHEME_TRUE,((C_word*)((C_word*)t0)[8])[1]);}
else{
t2=((C_word*)t0)[4];
f_8078(t2,C_SCHEME_UNDEFINED);}}

/* k8196 in k8192 in k8151 in k8073 in k8276 in k8064 in k8061 in k8058 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8198(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8198,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_8202,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t3,((C_word*)t0)[3],((C_word*)((C_word*)t0)[8])[1],((C_word*)t0)[2]);}

/* k8200 in k8196 in k8192 in k8151 in k8073 in k8276 in k8064 in k8061 in k8058 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8202(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8202,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[5])+1,t1);
t3=(C_word)C_a_i_list(&a,3,lf[501],((C_word*)t0)[4],((C_word*)((C_word*)t0)[5])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[5])+1,t3);
t5=C_mutate(((C_word *)((C_word*)t0)[3])+1,lf[512]);
t6=((C_word*)t0)[2];
f_8078(t6,t5);}

/* k8155 in k8151 in k8073 in k8276 in k8064 in k8061 in k8058 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8157(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8157,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_8161,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t3,((C_word*)t0)[3],((C_word*)((C_word*)t0)[8])[1],((C_word*)t0)[2]);}

/* k8159 in k8155 in k8151 in k8073 in k8276 in k8064 in k8061 in k8058 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8161(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8161,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_8164,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8188,a[2]=t3,a[3]=((C_word*)t0)[6],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  get-emit-info");
f_3254(t4,lf[511],((C_word*)((C_word*)t0)[2])[1]);}

/* k8186 in k8159 in k8155 in k8151 in k8073 in k8276 in k8064 in k8061 in k8058 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8188(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_8188,2,t0,t1);}
t2=(C_word)C_eqp(lf[509],t1);
if(C_truep(t2)){
t3=(C_word)C_a_i_list(&a,1,lf[510]);
t4=(C_word)C_a_i_list(&a,3,lf[442],t3,((C_word*)((C_word*)t0)[3])[1]);
t5=(C_word)C_a_i_list(&a,2,lf[453],t4);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t5);
t7=((C_word*)t0)[2];
f_8164(t7,t6);}
else{
t3=((C_word*)t0)[2];
f_8164(t3,C_SCHEME_UNDEFINED);}}

/* k8162 in k8159 in k8155 in k8151 in k8073 in k8276 in k8064 in k8061 in k8058 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_8164(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_8164,NULL,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,3,lf[501],((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t4=C_mutate(((C_word *)((C_word*)t0)[3])+1,lf[508]);
t5=((C_word*)t0)[2];
f_8078(t5,t4);}

/* k8076 in k8073 in k8276 in k8064 in k8061 in k8058 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_8078(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[15],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_8078,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_8081,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],tmp=(C_word)a,a+=6,tmp);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_8092,a[2]=((C_word*)t0)[3],a[3]=t2,a[4]=((C_word*)t0)[7],tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8150,a[2]=((C_word*)t0)[7],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  symbol->string");
t5=*((C_word*)lf[413]+1);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,((C_word*)t0)[2]);}

/* k8148 in k8076 in k8073 in k8276 in k8064 in k8061 in k8058 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8150(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  string-append");
t2=*((C_word*)lf[261]+1);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1,lf[507]);}

/* k8090 in k8076 in k8073 in k8276 in k8064 in k8061 in k8058 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8092(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8092,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_8094,a[2]=t3,a[3]=((C_word*)t0)[4],a[4]=lf[506],tmp=(C_word)a,a+=5,tmp));
t5=((C_word*)t3)[1];
f_8094(t5,((C_word*)t0)[3],t1,((C_word*)t0)[2]);}

/* do1189 in k8090 in k8076 in k8073 in k8276 in k8064 in k8061 in k8058 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_8094(C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)trf_8094,NULL,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8109,a[2]=t1,a[3]=((C_word*)t0)[3],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  string-append");
t6=*((C_word*)lf[261]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t5,((C_word*)t4)[1],lf[504]);}
else{
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_8113,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=t3,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8142,a[2]=t4,a[3]=t5,tmp=(C_word)a,a+=4,tmp);
t7=(C_word)C_i_car(t3);
C_trace("ChickenBridge.scm: 137  symbol->string");
t8=*((C_word*)lf[413]+1);
((C_proc3)C_retrieve_proc(t8))(3,t8,t6,t7);}}

/* k8140 in do1189 in k8090 in k8076 in k8073 in k8276 in k8064 in k8061 in k8058 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8142(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  string-append");
t2=*((C_word*)lf[261]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k8111 in do1189 in k8090 in k8076 in k8073 in k8276 in k8064 in k8061 in k8058 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8113(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8113,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[5])+1,t1);
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_8116,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t4=(C_word)C_i_cdr(((C_word*)t0)[4]);
if(C_truep((C_word)C_i_nullp(t4))){
t5=t3;
f_8116(t5,C_SCHEME_UNDEFINED);}
else{
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8130,a[2]=t3,a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  string-append");
t6=*((C_word*)lf[261]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t5,((C_word*)((C_word*)t0)[5])[1],lf[505]);}}

/* k8128 in k8111 in do1189 in k8090 in k8076 in k8073 in k8276 in k8064 in k8061 in k8058 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8130(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_8116(t3,t2);}

/* k8114 in k8111 in do1189 in k8090 in k8076 in k8073 in k8276 in k8064 in k8061 in k8058 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_8116(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[5]);
t3=((C_word*)((C_word*)t0)[4])[1];
f_8094(t3,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t2);}

/* k8107 in do1189 in k8090 in k8076 in k8073 in k8276 in k8064 in k8061 in k8058 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8109(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8109,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,2,lf[279],t1);
t3=C_mutate(((C_word *)((C_word*)t0)[3])+1,t2);
t4=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,t3);}

/* k8079 in k8076 in k8073 in k8276 in k8064 in k8061 in k8058 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8081(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8081,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,2,((C_word*)((C_word*)t0)[5])[1],((C_word*)((C_word*)t0)[4])[1]);
t3=((C_word*)t0)[3];
f_7999(2,t3,(C_word)C_i_set_cdr(((C_word*)t0)[2],t2));}

/* do1163 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_8011(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_8011,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_8021,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=t2,a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
t4=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t3,t4,((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]);}}

/* k8019 in do1163 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8021(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8021,2,t0,t1);}
t2=(C_word)C_i_car(t1);
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_8027,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=t2,a[7]=t1,tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 137  sprintf");
t4=C_retrieve(lf[286]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t3,lf[502],t2);}

/* k8025 in k8019 in do1163 in k8000 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_8027(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_8027,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,lf[501],((C_word*)t0)[7]);
t3=(C_word)C_a_i_list(&a,3,lf[278],t1,((C_word*)t0)[6]);
t4=(C_word)C_a_i_list(&a,2,t2,t3);
t5=(C_word)C_i_set_cdr(((C_word*)((C_word*)t0)[5])[1],t4);
t6=(C_word)C_i_cddr(((C_word*)((C_word*)t0)[5])[1]);
t7=C_mutate(((C_word *)((C_word*)t0)[5])+1,t6);
t8=(C_word)C_i_cdr(((C_word*)t0)[4]);
t9=((C_word*)((C_word*)t0)[3])[1];
f_8011(t9,((C_word*)t0)[2],t8);}

/* k7997 in k7988 in a7985 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7999(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,((C_word*)t0)[2]);}

/* a7946 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7947(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_7947,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=(C_word)C_i_cadr(((C_word*)t4)[1]);
t6=C_set_block_item(t4,0,t5);
t7=(C_word)C_i_car(((C_word*)t4)[1]);
t8=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7958,a[2]=t4,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
t9=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7964,a[2]=t8,a[3]=t7,a[4]=t4,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  token-unit-type=?");
f_3222(t9,t7,C_fix(24576));}

/* k7962 in a7946 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7964(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7964,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_cadr(((C_word*)((C_word*)t0)[4])[1]);
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_7980,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[3],a[5]=t2,tmp=(C_word)a,a+=6,tmp);
t4=(C_word)C_i_caddr(((C_word*)((C_word*)t0)[4])[1]);
C_trace("ChickenBridge.scm: 137  remove-token-type");
f_4472(t3,t4,C_fix(256));}
else{
t2=((C_word*)t0)[2];
f_7958(t2,C_SCHEME_UNDEFINED);}}

/* k7978 in k7962 in a7946 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7980(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7980,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[5],t1);
t3=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[4],t2);
t4=C_mutate(((C_word *)((C_word*)t0)[3])+1,t3);
t5=((C_word*)t0)[2];
f_7958(t5,t4);}

/* k7956 in a7946 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_7958(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  make-parse-unit");
f_3137(((C_word*)t0)[3],C_fix(36352),((C_word*)((C_word*)t0)[2])[1],C_SCHEME_FALSE);}

/* k7939 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7941(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(36352),t1);}

/* k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5785(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5785,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5788,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7865,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
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
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t3,lf[499],C_fix(36608),t20,C_SCHEME_FALSE,C_SCHEME_FALSE);}

/* k7863 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7865(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(36608),t1);}

/* k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5788(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5788,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5791,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7821,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(36608),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,lf[215],t4);
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7827,a[2]=lf[496],tmp=(C_word)a,a+=3,tmp);
t7=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7841,a[2]=lf[497],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  make-rule");
f_2839(t3,lf[498],C_fix(36864),t5,t6,t7);}

/* a7840 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7841(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[8],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_7841,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7849,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7853,a[2]=t4,a[3]=t3,a[4]=t5,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-parsed");
f_3176(t6,t2);}

/* k7851 in a7840 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7853(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  emit");
f_3294(((C_word*)t0)[4],t1,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k7847 in a7840 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7849(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7849,2,t0,t1);}
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_cons(&a,2,lf[240],t1));}

/* a7826 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7827(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word ab[4],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_7827,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7835,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 137  parse-unit-position");
f_3194(t4,t5);}

/* k7833 in a7826 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7835(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  make-parse-unit");
f_3137(((C_word*)t0)[3],C_fix(36864),((C_word*)t0)[2],t1);}

/* k7819 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7821(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  hash-table-set!");
t2=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[120],"*rules*"),C_fix(36864),t1);}

/* k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5791(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5791,2,t0,t1);}
t2=lf[256]=C_SCHEME_FALSE;;
t3=lf[257]=C_SCHEME_FALSE;;
t4=lf[258]=C_SCHEME_FALSE;;
t5=C_mutate((C_word*)lf[259]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5797,a[2]=lf[277],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[278]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5968,a[2]=lf[292],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate((C_word*)lf[293]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6147,a[2]=lf[295],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate((C_word*)lf[296]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6156,a[2]=lf[304],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate((C_word*)lf[305]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6203,a[2]=lf[307],tmp=(C_word)a,a+=3,tmp));
t10=C_mutate((C_word*)lf[308]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6209,a[2]=lf[310],tmp=(C_word)a,a+=3,tmp));
t11=C_mutate((C_word*)lf[311]+1,*((C_word*)lf[246]+1));
t12=C_mutate((C_word*)lf[312]+1,*((C_word*)lf[313]+1));
t13=C_mutate((C_word*)lf[314]+1,*((C_word*)lf[315]+1));
t14=C_mutate((C_word*)lf[316]+1,*((C_word*)lf[317]+1));
t15=C_mutate((C_word*)lf[243]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6231,a[2]=lf[318],tmp=(C_word)a,a+=3,tmp));
t16=C_mutate((C_word*)lf[319]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6241,a[2]=lf[320],tmp=(C_word)a,a+=3,tmp));
t17=C_mutate((C_word*)lf[321]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6251,a[2]=lf[322],tmp=(C_word)a,a+=3,tmp));
t18=C_mutate((C_word*)lf[323]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6261,a[2]=lf[324],tmp=(C_word)a,a+=3,tmp));
t19=C_mutate((C_word*)lf[325]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6271,a[2]=lf[326],tmp=(C_word)a,a+=3,tmp));
t20=C_mutate((C_word*)lf[327]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6285,a[2]=lf[328],tmp=(C_word)a,a+=3,tmp));
t21=C_mutate((C_word*)lf[329]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6305,a[2]=lf[330],tmp=(C_word)a,a+=3,tmp));
t22=C_mutate((C_word*)lf[331]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6325,a[2]=lf[332],tmp=(C_word)a,a+=3,tmp));
t23=C_mutate((C_word*)lf[333]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6373,a[2]=lf[335],tmp=(C_word)a,a+=3,tmp));
t24=C_mutate((C_word*)lf[336]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6413,a[2]=lf[339],tmp=(C_word)a,a+=3,tmp));
t25=C_mutate((C_word*)lf[294]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6424,a[2]=lf[343],tmp=(C_word)a,a+=3,tmp));
t26=C_mutate((C_word*)lf[279]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6453,a[2]=lf[344],tmp=(C_word)a,a+=3,tmp));
t27=C_mutate((C_word*)lf[260]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6467,a[2]=lf[345],tmp=(C_word)a,a+=3,tmp));
t28=C_mutate((C_word*)lf[346]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6510,a[2]=lf[347],tmp=(C_word)a,a+=3,tmp));
t29=C_mutate((C_word*)lf[348]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6513,a[2]=lf[349],tmp=(C_word)a,a+=3,tmp));
t30=C_mutate(&lf[350],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6525,a[2]=lf[353],tmp=(C_word)a,a+=3,tmp));
t31=C_mutate(&lf[354],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6534,a[2]=lf[356],tmp=(C_word)a,a+=3,tmp));
t32=C_mutate(&lf[357],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6578,a[2]=lf[359],tmp=(C_word)a,a+=3,tmp));
t33=C_mutate((C_word*)lf[297]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6600,a[2]=lf[361],tmp=(C_word)a,a+=3,tmp));
t34=C_mutate((C_word*)lf[362]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6619,a[2]=lf[369],tmp=(C_word)a,a+=3,tmp));
t35=C_mutate((C_word*)lf[370]+1,C_retrieve(lf[348]));
t36=C_mutate((C_word*)lf[371]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6787,a[2]=lf[378],tmp=(C_word)a,a+=3,tmp));
t37=C_mutate((C_word*)lf[379]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6850,a[2]=lf[381],tmp=(C_word)a,a+=3,tmp));
t38=C_mutate((C_word*)lf[382]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6859,a[2]=lf[384],tmp=(C_word)a,a+=3,tmp));
t39=C_mutate((C_word*)lf[385]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6865,a[2]=lf[387],tmp=(C_word)a,a+=3,tmp));
t40=C_mutate((C_word*)lf[388]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6874,a[2]=lf[391],tmp=(C_word)a,a+=3,tmp));
t41=C_mutate((C_word*)lf[392]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6932,a[2]=lf[394],tmp=(C_word)a,a+=3,tmp));
t42=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6943,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 357  make-hash-table");
t43=C_retrieve(lf[494]);
((C_proc3)C_retrieve_proc(t43))(3,t43,t42,*((C_word*)lf[495]+1));}

/* k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6943(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6943,2,t0,t1);}
t2=C_mutate(&lf[395],t1);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6946,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7767,a[2]=lf[492],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 359  ##sys#register-macro");
t5=C_retrieve(lf[469]);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,lf[493],t4);}

/* a7766 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7767(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_7767,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_7771,a[2]=t6,a[3]=t1,a[4]=t3,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t4)[1]))){
t8=(C_word)C_i_car(((C_word*)t4)[1]);
t9=C_set_block_item(t6,0,t8);
t10=(C_word)C_i_cadr(((C_word*)t4)[1]);
t11=C_set_block_item(t4,0,t10);
t12=t7;
f_7771(2,t12,t11);}
else{
if(C_truep((C_word)C_i_stringp(((C_word*)t4)[1]))){
t8=C_set_block_item(t6,0,((C_word*)t4)[1]);
t9=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7804,a[2]=t7,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 366  string->symbol");
t10=*((C_word*)lf[173]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)t4)[1]);}
else{
if(C_truep((C_word)C_i_symbolp(((C_word*)t4)[1]))){
t8=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7814,a[2]=t7,a[3]=t6,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 368  symbol->string");
t9=*((C_word*)lf[413]+1);
((C_proc3)C_retrieve_proc(t9))(3,t9,t8,((C_word*)t4)[1]);}
else{
C_trace("ChickenBridge.scm: 370  error");
t8=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,lf[491]);}}}}

/* k7812 in a7766 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7814(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_7771(2,t3,t2);}

/* k7802 in a7766 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7804(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_7771(2,t3,t2);}

/* k7769 in a7766 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7771(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7771,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[4]);
t3=(C_word)C_a_i_list(&a,2,lf[447],t2);
t4=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_a_i_list(&a,4,lf[471],lf[490],((C_word*)((C_word*)t0)[2])[1],t3));}

/* k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6946(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6946,2,t0,t1);}
t2=C_mutate((C_word*)lf[396]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6948,a[2]=lf[414],tmp=(C_word)a,a+=3,tmp));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7219,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7761,a[2]=lf[488],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 454  ##sys#register-macro");
t5=C_retrieve(lf[469]);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,lf[489],t4);}

/* a7760 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7761(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr3r,(void*)f_7761r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_7761r(t0,t1,t2,t3);}}

static void C_ccall f_7761r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_trace("ChickenBridge.scm: 455  expand-send");
t4=C_retrieve(lf[396]);
((C_proc5)C_retrieve_proc(t4))(5,t4,t1,t2,t3,C_SCHEME_FALSE);}

/* k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7219(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_7219,2,t0,t1);}
t2=C_mutate((C_word*)lf[415]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7221,a[2]=lf[417],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[418]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7227,a[2]=lf[420],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate((C_word*)lf[421]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7233,a[2]=lf[423],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate((C_word*)lf[424]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7239,a[2]=lf[426],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[427]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7245,a[2]=lf[429],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate((C_word*)lf[430]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7251,a[2]=lf[432],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate((C_word*)lf[433]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7257,a[2]=lf[435],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate((C_word*)lf[436]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7263,a[2]=lf[438],tmp=(C_word)a,a+=3,tmp));
t10=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7270,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 481  hash-table-set!");
t11=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t11))(5,t11,t10,C_retrieve2(lf[395],"*messages*"),lf[486],lf[487]);}

/* k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7270(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7270,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7273,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 482  hash-table-set!");
t3=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,C_retrieve2(lf[395],"*messages*"),lf[484],lf[485]);}

/* k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7273(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7273,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7276,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 483  hash-table-set!");
t3=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,C_retrieve2(lf[395],"*messages*"),lf[482],lf[483]);}

/* k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7276(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7276,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7279,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 484  hash-table-set!");
t3=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,C_retrieve2(lf[395],"*messages*"),lf[480],lf[481]);}

/* k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7279(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7279,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7282,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 485  hash-table-set!");
t3=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,C_retrieve2(lf[395],"*messages*"),lf[478],lf[479]);}

/* k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7282(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7282,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7285,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 486  hash-table-set!");
t3=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,C_retrieve2(lf[395],"*messages*"),lf[476],lf[477]);}

/* k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7285(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7285,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7288,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 487  hash-table-set!");
t3=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,C_retrieve2(lf[395],"*messages*"),lf[474],lf[475]);}

/* k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7288(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7288,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7291,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 488  hash-table-set!");
t3=C_retrieve(lf[471]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,C_retrieve2(lf[395],"*messages*"),lf[472],lf[473]);}

/* k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7291(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7291,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7294,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7755,a[2]=lf[468],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 494  ##sys#register-macro");
t4=C_retrieve(lf[469]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,lf[470],t3);}

/* a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7755(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+17)){
C_save_and_reclaim((void*)tr4r,(void*)f_7755r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest(a,C_rest_count(0));
f_7755r(t0,t1,t2,t3,t4);}}

static void C_ccall f_7755r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
t13=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_7309,a[2]=t2,a[3]=t12,a[4]=t6,a[5]=t10,a[6]=t1,a[7]=t8,a[8]=t3,tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(t2))){
t14=t13;
f_7309(2,t14,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 503  error");
t14=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t14))(4,t14,t13,lf[467],t2);}}

/* k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7309(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7309,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_7312,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(((C_word*)t0)[8]))){
if(C_truep((C_word)C_i_nullp(((C_word*)t0)[8]))){
C_trace("ChickenBridge.scm: 507  error");
t3=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,lf[465]);}
else{
t3=t2;
f_7312(2,t3,C_SCHEME_UNDEFINED);}}
else{
C_trace("ChickenBridge.scm: 505  error");
t3=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t2,lf[466],((C_word*)t0)[8]);}}

/* k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7312(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7312,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_7315,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],tmp=(C_word)a,a+=8,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_7590,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[7],a[5]=t4,a[6]=lf[464],tmp=(C_word)a,a+=7,tmp));
t6=((C_word*)t4)[1];
f_7590(t6,t2,((C_word*)t0)[2]);}

/* do1632 in k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_7590(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_7590,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7600,a[2]=t1,a[3]=((C_word*)t0)[5],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_7610,a[2]=t3,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=t2,tmp=(C_word)a,a+=7,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7698,a[2]=t4,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t7=(C_word)C_i_car(t2);
t8=(C_word)C_i_length(t7);
C_trace("ChickenBridge.scm: 511  <");
C_lessp(5,0,t6,C_fix(0),t8,C_fix(4));}
else{
t6=t4;
f_7610(t6,C_SCHEME_FALSE);}}}

/* k7696 in do1632 in k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7698(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=(C_word)C_i_car(t2);
t4=((C_word*)t0)[2];
f_7610(t4,(C_word)C_i_symbolp(t3));}
else{
t2=((C_word*)t0)[2];
f_7610(t2,C_SCHEME_FALSE);}}

/* k7608 in do1632 in k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_7610(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_7610,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[6]);
t3=(C_word)C_i_car(t2);
t4=(C_word)C_i_car(((C_word*)t0)[6]);
t5=(C_word)C_i_cadr(t4);
t6=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_7619,a[2]=t5,a[3]=t3,a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[5],tmp=(C_word)a,a+=8,tmp);
t7=(C_word)C_i_car(((C_word*)t0)[6]);
t8=(C_word)C_i_cddr(t7);
if(C_truep((C_word)C_i_nullp(t8))){
t9=t6;
f_7619(t9,lf[462]);}
else{
t9=(C_word)C_i_car(((C_word*)t0)[6]);
t10=t6;
f_7619(t10,(C_word)C_i_caddr(t9));}}
else{
t2=(C_word)C_i_car(((C_word*)t0)[6]);
C_trace("ChickenBridge.scm: 524  error");
t3=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[2],lf[463],t2);}}

/* k7617 in k7608 in do1632 in k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_7619(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_7619,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_7623,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t3=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 519  append");
t4=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,((C_word*)((C_word*)t0)[7])[1],t3);}

/* k7621 in k7617 in k7608 in do1632 in k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7623(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7623,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_7627,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
t4=(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 520  append");
t5=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,((C_word*)((C_word*)t0)[7])[1],t4);}

/* k7625 in k7621 in k7617 in k7608 in do1632 in k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7627(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_7627,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7631,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7635,a[2]=((C_word*)t0)[5],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_eqp(((C_word*)t0)[3],lf[462]);
if(C_truep(t5)){
t6=t4;
f_7635(t6,C_SCHEME_END_OF_LIST);}
else{
t6=(C_word)C_a_i_list(&a,3,lf[235],((C_word*)t0)[2],((C_word*)t0)[3]);
t7=t4;
f_7635(t7,(C_word)C_a_i_list(&a,1,t6));}}

/* k7633 in k7625 in k7621 in k7617 in k7608 in do1632 in k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_7635(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 521  append");
t2=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k7629 in k7625 in k7621 in k7617 in k7608 in do1632 in k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7631(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_7600(2,t3,t2);}

/* k7598 in do1632 in k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7600(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_7590(t3,((C_word*)t0)[2],t2);}

/* k7313 in k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7315(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7315,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_7318,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 526  gensym");
t3=C_retrieve(lf[237]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k7316 in k7313 in k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7318(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7318,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_7321,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 527  gensym");
t3=C_retrieve(lf[237]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k7319 in k7316 in k7313 in k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7321(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7321,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_7324,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 528  gensym");
t3=C_retrieve(lf[237]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k7322 in k7319 in k7316 in k7313 in k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7324(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7324,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_7327,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],a[10]=((C_word*)t0)[9],tmp=(C_word)a,a+=11,tmp);
C_trace("ChickenBridge.scm: 529  gensym");
t3=C_retrieve(lf[237]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k7325 in k7322 in k7319 in k7316 in k7313 in k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7327(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_7327,2,t0,t1);}
t2=C_SCHEME_TRUE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_SCHEME_END_OF_LIST;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_7330,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=t3,a[7]=((C_word*)t0)[5],a[8]=((C_word*)t0)[6],a[9]=((C_word*)t0)[7],a[10]=((C_word*)t0)[8],a[11]=((C_word*)t0)[9],a[12]=t5,a[13]=((C_word*)t0)[10],tmp=(C_word)a,a+=14,tmp);
t7=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7483,a[2]=t6,a[3]=t3,a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)((C_word*)t0)[3])[1]))){
t8=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
if(C_truep((C_word)C_i_pairp(t8))){
t9=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7584,a[2]=t7,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 535  caar");
t10=*((C_word*)lf[458]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)((C_word*)t0)[3])[1]);}
else{
t9=t7;
f_7483(t9,C_SCHEME_FALSE);}}
else{
t8=t7;
f_7483(t8,C_SCHEME_FALSE);}}

/* k7582 in k7325 in k7322 in k7319 in k7316 in k7313 in k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7584(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_7483(t2,(C_word)C_eqp(t1,lf[461]));}

/* k7481 in k7325 in k7322 in k7319 in k7316 in k7313 in k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_7483(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_7483,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7490,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 536  cdar");
t3=*((C_word*)lf[456]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)((C_word*)t0)[4])[1]);}
else{
t2=((C_word*)t0)[2];
f_7330(2,t2,C_SCHEME_UNDEFINED);}}

/* k7488 in k7481 in k7325 in k7322 in k7319 in k7316 in k7313 in k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7490(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7490,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_7492,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=lf[460],tmp=(C_word)a,a+=6,tmp));
t5=((C_word*)t3)[1];
f_7492(t5,((C_word*)t0)[2],t1);}

/* do1648 in k7488 in k7481 in k7325 in k7322 in k7319 in k7316 in k7313 in k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_7492(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_7492,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[4])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[4])+1,t3);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,t4);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7506,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7516,a[2]=t2,a[3]=((C_word*)t0)[2],a[4]=t3,tmp=(C_word)a,a+=5,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7564,a[2]=t4,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 540  cdar");
t7=*((C_word*)lf[456]+1);
((C_proc3)C_retrieve_proc(t7))(3,t7,t6,t2);}
else{
t6=t4;
f_7516(t6,C_SCHEME_FALSE);}}}

/* k7562 in do1648 in k7488 in k7481 in k7325 in k7322 in k7319 in k7316 in k7313 in k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7564(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_7516(t2,(C_word)C_i_pairp(t1));}

/* k7514 in do1648 in k7488 in k7481 in k7325 in k7322 in k7319 in k7316 in k7313 in k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_7516(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_7516,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7519,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 541  caar");
t3=*((C_word*)lf[458]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)t0)[2]);}
else{
t2=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 547  error");
t3=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[4],lf[459],t2);}}

/* k7517 in k7514 in do1648 in k7488 in k7481 in k7325 in k7322 in k7319 in k7316 in k7313 in k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7519(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7519,2,t0,t1);}
t2=(C_word)C_eqp(t1,lf[455]);
if(C_truep(t2)){
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7540,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 543  cdar");
t4=*((C_word*)lf[456]+1);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)t0)[2]);}
else{
t3=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 546  error");
t4=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,((C_word*)t0)[4],lf[457],t3);}}

/* k7538 in k7517 in k7514 in do1648 in k7488 in k7481 in k7325 in k7322 in k7319 in k7316 in k7313 in k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7540(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep((C_word)C_i_car(t1))){
t2=((C_word*)t0)[3];
f_7506(2,t2,C_SCHEME_UNDEFINED);}
else{
t2=C_set_block_item(((C_word*)t0)[2],0,C_SCHEME_FALSE);
t3=((C_word*)t0)[3];
f_7506(2,t3,t2);}}

/* k7504 in do1648 in k7488 in k7481 in k7325 in k7322 in k7319 in k7316 in k7313 in k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7506(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_7492(t3,((C_word*)t0)[2],t2);}

/* k7328 in k7325 in k7322 in k7319 in k7316 in k7313 in k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7330(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7330,2,t0,t1);}
t2=(C_word)C_i_car(((C_word*)t0)[13]);
t3=(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_7472,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],a[10]=((C_word*)t0)[10],a[11]=((C_word*)t0)[11],a[12]=((C_word*)t0)[12],a[13]=t2,tmp=(C_word)a,a+=14,tmp);
t4=(C_word)C_i_cdr(((C_word*)t0)[13]);
t5=(C_word)C_a_i_list(&a,1,C_fix(-1));
C_trace("ChickenBridge.scm: 498  ##sys#append");
t6=*((C_word*)lf[454]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t3,t4,t5);}

/* k7470 in k7328 in k7325 in k7322 in k7319 in k7316 in k7313 in k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7472(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7472,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[13],t1);
t3=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_7456,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],a[8]=((C_word*)t0)[10],a[9]=((C_word*)t0)[11],a[10]=((C_word*)t0)[12],a[11]=t2,tmp=(C_word)a,a+=12,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7460,a[2]=((C_word*)t0)[3],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_a_i_list(&a,1,((C_word*)t0)[10]);
C_trace("ChickenBridge.scm: 498  ##sys#append");
t6=*((C_word*)lf[454]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t4,((C_word*)((C_word*)t0)[2])[1],t5);}

/* k7458 in k7470 in k7328 in k7325 in k7322 in k7319 in k7316 in k7313 in k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7460(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 498  ##sys#append");
t2=*((C_word*)lf[454]+1);
((C_proc4)(void*)(*((C_word*)t2+1)))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k7454 in k7470 in k7328 in k7325 in k7322 in k7319 in k7316 in k7313 in k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7456(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_7456,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,lf[440],t1);
t3=(C_word)C_a_i_list(&a,3,lf[441],((C_word*)t0)[11],t2);
t4=C_mutate(((C_word *)((C_word*)t0)[10])+1,t3);
t5=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_7337,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],a[5]=((C_word*)t0)[10],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],tmp=(C_word)a,a+=8,tmp);
if(C_truep(((C_word*)((C_word*)t0)[4])[1])){
t6=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
t7=(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]);
t8=(C_word)C_a_i_list(&a,2,lf[447],lf[448]);
t9=(C_word)C_a_i_list(&a,2,lf[447],lf[449]);
t10=(C_word)C_a_i_list(&a,3,lf[450],t8,t9);
t11=(C_word)C_a_i_list(&a,2,t10,((C_word*)t0)[2]);
t12=(C_word)C_a_i_list(&a,4,lf[286],lf[451],t11,((C_word*)t0)[9]);
t13=(C_word)C_a_i_list(&a,2,lf[260],t12);
t14=(C_word)C_a_i_list(&a,2,((C_word*)t0)[3],C_fix(-2));
t15=(C_word)C_a_i_list(&a,4,lf[442],t7,t13,t14);
t16=(C_word)C_a_i_list(&a,3,lf[442],C_SCHEME_END_OF_LIST,((C_word*)((C_word*)t0)[10])[1]);
t17=(C_word)C_a_i_list(&a,3,lf[452],t15,t16);
t18=(C_word)C_a_i_list(&a,3,lf[442],t6,t17);
t19=(C_word)C_a_i_list(&a,2,lf[453],t18);
t20=C_mutate(((C_word *)((C_word*)t0)[10])+1,t19);
t21=t5;
f_7337(t21,t20);}
else{
t6=t5;
f_7337(t6,C_SCHEME_UNDEFINED);}}

/* k7335 in k7454 in k7470 in k7328 in k7325 in k7322 in k7319 in k7316 in k7313 in k7310 in k7307 in a7754 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_7337(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_7337,NULL,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,((C_word*)t0)[7]);
t3=(C_word)C_a_i_list(&a,2,((C_word*)t0)[6],C_fix(0));
t4=(C_word)C_a_i_list(&a,3,lf[442],C_SCHEME_END_OF_LIST,((C_word*)t0)[7]);
t5=(C_word)C_a_i_list(&a,2,lf[443],t4);
t6=(C_word)C_a_i_list(&a,1,lf[444]);
t7=(C_word)C_a_i_list(&a,3,lf[235],((C_word*)t0)[6],lf[444]);
t8=(C_word)C_a_i_list(&a,3,lf[442],t6,t7);
t9=(C_word)C_a_i_list(&a,2,lf[445],t8);
t10=(C_word)C_a_i_list(&a,3,t3,t5,t9);
t11=(C_word)C_a_i_list(&a,3,lf[446],t10,((C_word*)((C_word*)t0)[5])[1]);
t12=(C_word)C_a_i_list(&a,3,lf[442],t2,t11);
t13=(C_word)C_a_i_list(&a,3,lf[442],((C_word*)((C_word*)t0)[4])[1],t12);
t14=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t14+1)))(2,t14,(C_word)C_a_i_cons(&a,2,t13,((C_word*)((C_word*)t0)[2])[1]));}

/* k7292 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7294(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7294,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7753,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 595  return-to-host");
t3=C_retrieve(lf[439]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k7751 in k7292 in k7289 in k7286 in k7283 in k7280 in k7277 in k7274 in k7271 in k7268 in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7753(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_UNDEFINED);}

/* mp:inhook in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7263(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_7263,5,t0,t1,t2,t3,t4);}
C_trace("ChickenBridge.scm: 477  error");
t5=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t5))(3,t5,t1,lf[437]);}

/* mp:micro in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7257(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_7257,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 475  error");
t3=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[434]);}

/* mp:alloff in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7251(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7251,2,t0,t1);}
C_trace("ChickenBridge.scm: 473  error");
t2=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,t1,lf[431]);}

/* mp:ctrl in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7245(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_7245,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 471  error");
t6=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[428]);}

/* mp:prog in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7239(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_7239,5,t0,t1,t2,t3,t4);}
C_trace("ChickenBridge.scm: 469  error");
t5=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t5))(3,t5,t1,lf[425]);}

/* mp:off in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7233(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_7233,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 467  error");
t6=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[422]);}

/* mp:on in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7227(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_7227,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 465  error");
t6=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[419]);}

/* mp:note in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7221(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
C_word tmp;
C_word t7;
C_word t8;
C_word ab[8],*a=ab;
if(c!=7) C_bad_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr7,(void*)f_7221,7,t0,t1,t2,t3,t4,t5,t6);}
t7=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_6485,a[2]=t1,a[3]=t6,a[4]=t5,a[5]=t4,a[6]=t3,a[7]=t2,tmp=(C_word)a,a+=8,tmp);
C_trace("##sys#gc");
t8=C_retrieve(lf[352]);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,C_SCHEME_FALSE);}

/* k6483 in mp:note in k7217 in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6485(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_6485,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[7]);
t4=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[6]);
t5=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[5]);
t6=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[4]);
t7=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[3]);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub1429,a[2]=lf[416],tmp=(C_word)a,a+=3,tmp);
((C_proc8)C_retrieve_proc(t8))(8,t8,((C_word*)t0)[2],t2,t3,t4,t5,t6,t7);}

/* expand-send in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6948(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
C_save_and_reclaim((void*)tr5,(void*)f_6948,5,t0,t1,t2,t3,t4);}
t5=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t6=t4;
t7=(C_truep(t6)?t6:(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7208,a[2]=lf[397],tmp=(C_word)a,a+=3,tmp));
t8=t4;
t9=(C_truep(t8)?(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7197,a[2]=lf[400],tmp=(C_word)a,a+=3,tmp):(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7206,a[2]=lf[401],tmp=(C_word)a,a+=3,tmp));
t10=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_6958,a[2]=t9,a[3]=t7,a[4]=t1,a[5]=t5,tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_symbolp(t2))){
C_trace("ChickenBridge.scm: 385  symbol->string");
t11=*((C_word*)lf[413]+1);
((C_proc3)C_retrieve_proc(t11))(3,t11,t10,t2);}
else{
t11=t10;
f_6958(2,t11,t2);}}

/* k6956 in expand-send in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6958(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6958,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_6961,a[2]=((C_word*)t0)[2],a[3]=t1,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],tmp=(C_word)a,a+=7,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7189,a[2]=lf[412],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 386  hash-table-ref");
t4=*((C_word*)lf[127]+1);
((C_proc5)C_retrieve_proc(t4))(5,t4,t2,C_retrieve2(lf[395],"*messages*"),t1,t3);}

/* a7188 in k6956 in expand-send in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7189(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7189,2,t0,t1);}
t2=t1;
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}

/* k6959 in k6956 in expand-send in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6961(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6961,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_6964,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=t1,a[7]=((C_word*)t0)[6],tmp=(C_word)a,a+=8,tmp);
t3=t1;
if(C_truep(t3)){
t4=t2;
f_6964(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 387  ferror");
t4=((C_word*)t0)[4];
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,lf[411],((C_word*)t0)[3]);}}

/* k6962 in k6959 in k6956 in expand-send in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6964(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_6964,2,t0,t1);}
t2=((C_word*)((C_word*)t0)[7])[1];
t3=(C_word)C_i_car(((C_word*)t0)[6]);
t4=(C_word)C_i_cdr(((C_word*)t0)[6]);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(C_word)C_i_length(t4);
t8=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_6976,a[2]=t2,a[3]=t7,a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],a[7]=t6,a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[5],a[10]=t4,a[11]=t3,tmp=(C_word)a,a+=12,tmp);
C_trace("ChickenBridge.scm: 394  append");
t9=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t9))(4,t9,t8,t4,C_SCHEME_END_OF_LIST);}

/* k6974 in k6962 in k6959 in k6956 in expand-send in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6976(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6976,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_6979,a[2]=((C_word*)t0)[9],a[3]=((C_word*)t0)[10],a[4]=t1,a[5]=((C_word*)t0)[11],tmp=(C_word)a,a+=6,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_7024,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[10],a[9]=((C_word*)t0)[7],a[10]=t4,a[11]=((C_word*)t0)[8],a[12]=lf[410],tmp=(C_word)a,a+=13,tmp));
t6=((C_word*)t4)[1];
f_7024(t6,t2,C_SCHEME_FALSE,C_SCHEME_FALSE,C_fix(0));}

/* do1572 in k6974 in k6962 in k6959 in k6956 in expand-send in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_7024(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
C_save_and_reclaim((void*)trf_7024,NULL,5,t0,t1,t2,t3,t4);}
t5=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[11])[1]))){
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,C_SCHEME_FALSE);}
else{
t8=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_7034,a[2]=t7,a[3]=t6,a[4]=t5,a[5]=t1,a[6]=((C_word*)t0)[10],tmp=(C_word)a,a+=7,tmp);
t9=(*a=C_CLOSURE_TYPE|14,a[1]=(C_word)f_7040,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t7,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=t6,a[10]=((C_word*)t0)[8],a[11]=t5,a[12]=((C_word*)t0)[11],a[13]=t8,a[14]=((C_word*)t0)[9],tmp=(C_word)a,a+=15,tmp);
t10=((C_word*)((C_word*)t0)[9])[1];
if(C_truep(t10)){
t11=t9;
f_7040(2,t11,C_SCHEME_FALSE);}
else{
t11=(C_word)C_i_car(((C_word*)((C_word*)t0)[11])[1]);
C_trace("ChickenBridge.scm: 405  keyword?");
t12=C_retrieve(lf[408]);
((C_proc3)C_retrieve_proc(t12))(3,t12,t9,t11);}}}

/* k7038 in do1572 in k6974 in k6962 in k6959 in k6956 in expand-send in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7040(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_7040,2,t0,t1);}
if(C_truep(t1)){
t2=C_set_block_item(((C_word*)t0)[14],0,C_SCHEME_TRUE);
t3=((C_word*)t0)[13];
f_7034(t3,t2);}
else{
t2=((C_word*)((C_word*)t0)[14])[1];
if(C_truep(t2)){
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[12])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[11])+1,t3);
t5=(C_word)C_i_assoc(((C_word*)((C_word*)t0)[11])[1],((C_word*)t0)[10]);
t6=C_mutate(((C_word *)((C_word*)t0)[9])+1,t5);
t7=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[12])[1]);
t8=C_mutate(((C_word *)((C_word*)t0)[12])+1,t7);
t9=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_7094,a[2]=((C_word*)t0)[11],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],a[6]=((C_word*)t0)[13],a[7]=((C_word*)t0)[12],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],tmp=(C_word)a,a+=10,tmp);
t10=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_7167,a[2]=((C_word*)t0)[10],a[3]=((C_word*)t0)[9],a[4]=((C_word*)t0)[11],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t9,a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[12],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 425  keyword?");
t11=C_retrieve(lf[408]);
((C_proc3)C_retrieve_proc(t11))(3,t11,t10,((C_word*)((C_word*)t0)[11])[1]);}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_7050,a[2]=((C_word*)t0)[13],a[3]=((C_word*)t0)[12],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[8],tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_nequalp(((C_word*)((C_word*)t0)[4])[1],((C_word*)t0)[3]))){
t4=(C_word)C_i_length(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 415  ferror");
t5=((C_word*)t0)[7];
((C_proc6)C_retrieve_proc(t5))(6,t5,t3,lf[409],((C_word*)t0)[6],((C_word*)t0)[3],t4);}
else{
t4=t3;
f_7050(2,t4,C_SCHEME_UNDEFINED);}}}}

/* k7048 in k7038 in do1572 in k6974 in k6962 in k6959 in k6956 in expand-send in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7050(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_7050,2,t0,t1);}
t2=(C_word)C_i_list_tail(((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]);
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
t4=(C_word)C_i_set_car(t2,t3);
t5=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[3])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t5);
t7=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[4])[1],C_fix(1));
t8=C_mutate(((C_word *)((C_word*)t0)[4])+1,t7);
t9=((C_word*)t0)[2];
f_7034(t9,t8);}

/* k7165 in k7038 in do1572 in k6974 in k6962 in k6959 in k6956 in expand-send in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7167(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[15],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7167,2,t0,t1);}
if(C_truep(t1)){
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[9])[1]))){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7140,a[2]=((C_word*)t0)[6],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[8],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 430  keyname");
t3=((C_word*)t0)[5];
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)((C_word*)t0)[4])[1]);}
else{
t2=((C_word*)((C_word*)t0)[3])[1];
if(C_truep(t2)){
t3=((C_word*)t0)[7];
f_7094(2,t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_7153,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],a[5]=((C_word*)t0)[8],tmp=(C_word)a,a+=6,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7155,a[2]=((C_word*)t0)[5],a[3]=lf[406],tmp=(C_word)a,a+=4,tmp);
C_trace("map");
t5=*((C_word*)lf[276]+1);
((C_proc4)(void*)(*((C_word*)t5+1)))(4,t5,t3,t4,((C_word*)t0)[2]);}}}
else{
C_trace("ChickenBridge.scm: 426  ferror");
t2=((C_word*)t0)[8];
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[7],lf[407],((C_word*)t0)[6],((C_word*)((C_word*)t0)[4])[1]);}}

/* a7154 in k7165 in k7038 in do1572 in k6974 in k6962 in k6959 in k6956 in expand-send in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7155(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_7155,3,t0,t1,t2);}
t3=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 434  keyname");
t4=((C_word*)t0)[2];
((C_proc3)C_retrieve_proc(t4))(3,t4,t1,t3);}

/* k7151 in k7165 in k7038 in do1572 in k6974 in k6962 in k6959 in k6956 in expand-send in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7153(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 432  ferror");
t2=((C_word*)t0)[5];
((C_proc6)C_retrieve_proc(t2))(6,t2,((C_word*)t0)[4],lf[405],((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k7138 in k7165 in k7038 in do1572 in k6974 in k6962 in k6959 in k6956 in expand-send in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7140(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 429  ferror");
t2=((C_word*)t0)[4];
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[3],lf[404],((C_word*)t0)[2],t1);}

/* k7092 in k7038 in do1572 in k6974 in k6962 in k6959 in k6956 in expand-send in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7094(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7094,2,t0,t1);}
t2=(C_word)C_i_member(((C_word*)((C_word*)t0)[9])[1],((C_word*)t0)[8]);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7100,a[2]=((C_word*)t0)[6],a[3]=t2,a[4]=((C_word*)t0)[7],tmp=(C_word)a,a+=5,tmp);
if(C_truep(t2)){
t4=t3;
f_7100(2,t4,C_SCHEME_UNDEFINED);}
else{
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7121,a[2]=((C_word*)t0)[4],a[3]=t3,a[4]=((C_word*)t0)[5],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 440  keyname");
t5=((C_word*)t0)[3];
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,((C_word*)((C_word*)t0)[2])[1]);}}

/* k7119 in k7092 in k7038 in do1572 in k6974 in k6962 in k6959 in k6956 in expand-send in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7121(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 439  ferror");
t2=((C_word*)t0)[4];
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[3],lf[403],((C_word*)t0)[2],t1);}

/* k7098 in k7092 in k7038 in do1572 in k6974 in k6962 in k6959 in k6956 in expand-send in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7100(C_word c,C_word t0,C_word t1){
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
f_7034(t6,t5);}

/* k7032 in do1572 in k6974 in k6962 in k6959 in k6956 in expand-send in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_7034(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[6])[1];
f_7024(t2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k6977 in k6974 in k6962 in k6959 in k6956 in expand-send in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6979(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6979,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_6984,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=lf[402],tmp=(C_word)a,a+=7,tmp));
t5=((C_word*)t3)[1];
f_6984(t5,((C_word*)t0)[2],((C_word*)t0)[4]);}

/* do1590 in k6977 in k6974 in k6962 in k6959 in k6956 in expand-send in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_6984(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6984,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[5],((C_word*)t0)[4]));}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6997,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_member(t4,((C_word*)t0)[2]))){
t5=(C_word)C_i_car(t2);
t6=(C_word)C_i_cadr(t5);
t7=t3;
f_6997(t7,(C_word)C_i_set_car(t2,t6));}
else{
t5=t3;
f_6997(t5,C_SCHEME_UNDEFINED);}}}

/* k6995 in do1590 in k6977 in k6974 in k6962 in k6959 in k6956 in expand-send in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_6997(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_6984(t3,((C_word*)t0)[2],t2);}

/* f_7206 in expand-send in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7206(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_7206,3,t0,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,t2);}

/* f_7197 in expand-send in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7197(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_7197,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7205,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 383  keyword->string");
t4=C_retrieve(lf[399]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,t2);}

/* k7203 */
static void C_ccall f_7205(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 383  sprintf");
t2=C_retrieve(lf[286]);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[2],lf[398],t1);}

/* f_7208 in expand-send in k6944 in k6941 in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_7208(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+3)){
C_save_and_reclaim((void*)tr3r,(void*)f_7208r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_7208r(t0,t1,t2,t3);}}

static void C_ccall f_7208r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word *a=C_alloc(3);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7216,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_apply(5,0,t4,C_retrieve(lf[286]),t2,t3);}

/* k7214 */
static void C_ccall f_7216(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 379  error");
t2=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* hush in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6932(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6932,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6936,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6595,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[352]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k6593 in hush in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6595(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6595,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub1482,a[2]=lf[393],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k6934 in hush in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6936(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 351  values");
C_values(2,0,((C_word*)t0)[2]);}

/* stop in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6874(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+9)){
C_save_and_reclaim((void*)tr2r,(void*)f_6874r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_6874r(t0,t1,t2);}}

static void C_ccall f_6874r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a=C_alloc(9);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6878,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 341  scheduler-stop");
f_6578(t3,C_fix(-1));}
else{
t4=C_SCHEME_UNDEFINED;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_set_block_item(t5,0,(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6892,a[2]=t5,a[3]=lf[390],tmp=(C_word)a,a+=4,tmp));
t7=((C_word*)t5)[1];
f_6892(t7,t3,t2);}}

/* do1539 in stop in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_6892(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6892,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6902,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_fixnump(t4))){
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 345  scheduler-stop");
f_6578(t3,t5);}
else{
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 346  error");
t6=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t3,lf[389],t5);}}}

/* k6900 in do1539 in stop in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6902(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_6892(t3,((C_word*)t0)[2],t2);}

/* k6876 in stop in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6878(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 347  values");
C_values(2,0,((C_word*)t0)[2]);}

/* cont in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6865(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6865,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6869,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6573,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[352]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k6571 in cont in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6573(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6573,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub1472,a[2]=lf[386],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k6867 in cont in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6869(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 337  values");
C_values(2,0,((C_word*)t0)[2]);}

/* paused? in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6859(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6859,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6555,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t3=C_retrieve(lf[352]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,C_SCHEME_FALSE);}

/* k6553 in paused? in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6555(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6555,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub1464,a[2]=lf[383],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* pause in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6850(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6850,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6854,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6564,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[352]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k6562 in pause in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6564(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6564,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub1468,a[2]=lf[380],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k6852 in pause in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6854(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 330  values");
C_values(2,0,((C_word*)t0)[2]);}

/* time-format in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6787(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+11)){
C_save_and_reclaim((void*)tr2rv,(void*)f_6787r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_6787r(t0,t1,t2);}}

static void C_ccall f_6787r(C_word t0,C_word t1,C_word t2){
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
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6800,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6520,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t5=C_retrieve(lf[352]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,C_SCHEME_FALSE);}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
t4=(C_word)C_i_eqvp(t3,lf[374]);
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6812,a[2]=t2,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
if(C_truep(t4)){
t6=t5;
f_6812(t6,t4);}
else{
t6=(C_word)C_eqp(t3,C_fix(1));
t7=t5;
f_6812(t7,(C_truep(t6)?t6:(C_word)C_eqp(t3,lf[377])));}}}

/* k6810 in time-format in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_6812(C_word t0,C_word t1){
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
C_trace("ChickenBridge.scm: 319  scheduler-set-time-milliseconds");
f_6525(((C_word*)t0)[4],C_SCHEME_FALSE);}
else{
t2=(C_word)C_eqp(((C_word*)t0)[3],C_fix(1000));
t3=(C_truep(t2)?t2:(C_word)C_eqp(((C_word*)t0)[3],lf[375]));
if(C_truep(t3)){
t4=C_mutate((C_word*)lf[370]+1,C_retrieve(lf[346]));
C_trace("ChickenBridge.scm: 323  scheduler-set-time-milliseconds");
f_6525(((C_word*)t0)[4],C_SCHEME_TRUE);}
else{
t4=(C_word)C_i_vector_ref(((C_word*)t0)[2],C_fix(0));
C_trace("ChickenBridge.scm: 326  error");
t5=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,((C_word*)t0)[4],lf[376],t4);}}}

/* k6518 in time-format in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6520(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6520,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub1444,a[2]=lf[373],tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k6798 in time-format in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6800(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_truep(t1)?C_fix(1000):lf[372]));}

/* sprout in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6619(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+12)){
C_save_and_reclaim((void*)tr3r,(void*)f_6619r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_6619r(t0,t1,t2,t3);}}

static void C_ccall f_6619r(C_word t0,C_word t1,C_word t2,C_word t3){
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
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6621,a[2]=t2,a[3]=lf[366],tmp=(C_word)a,a+=4,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6733,a[2]=t4,a[3]=lf[367],tmp=(C_word)a,a+=4,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6738,a[2]=t5,a[3]=lf[368],tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("def-start14991520");
t7=t6;
f_6738(t7,t1);}
else{
t7=(C_word)C_i_car(t3);
t8=(C_word)C_i_cdr(t3);
if(C_truep((C_word)C_i_nullp(t8))){
C_trace("def-id15001518");
t9=t5;
f_6733(t9,t1,t7);}
else{
t9=(C_word)C_i_car(t8);
t10=(C_word)C_i_cdr(t8);
if(C_truep((C_word)C_i_nullp(t10))){
C_trace("body14971502");
t11=t4;
f_6621(t11,t1,t7,t9);}
else{
C_trace("##sys#error");
t11=*((C_word*)lf[38]+1);
((C_proc4)(void*)(*((C_word*)t11+1)))(4,t11,t1,lf[0],t10);}}}}

/* def-start1499 in sprout in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_6738(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6738,NULL,2,t0,t1);}
C_trace("def-id15001518");
t2=((C_word*)t0)[2];
f_6733(t2,t1,C_fix(0));}

/* def-id1500 in sprout in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_6733(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6733,NULL,3,t0,t1,t2);}
C_trace("body14971502");
t3=((C_word*)t0)[2];
f_6621(t3,t1,t2,C_fix(-1));}

/* body1497 in sprout in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_6621(C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)trf_6621,NULL,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6623,a[2]=t4,a[3]=lf[363],tmp=(C_word)a,a+=4,tmp);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6651,a[2]=t5,a[3]=lf[364],tmp=(C_word)a,a+=4,tmp);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6681,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t0)[2]))){
t9=C_SCHEME_UNDEFINED;
t10=(*a=C_VECTOR_TYPE|1,a[1]=t9,tmp=(C_word)a,a+=2,tmp);
t11=C_set_block_item(t10,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_6692,a[2]=t6,a[3]=t7,a[4]=t10,a[5]=((C_word*)t0)[2],a[6]=lf[365],tmp=(C_word)a,a+=7,tmp));
t12=((C_word*)t10)[1];
f_6692(t12,t8,((C_word*)t0)[2]);}
else{
t9=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6724,a[2]=((C_word*)t0)[2],a[3]=t8,tmp=(C_word)a,a+=4,tmp);
t10=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6728,a[2]=t7,a[3]=((C_word*)t0)[2],a[4]=t9,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 303  nextstart");
t11=t6;
f_6623(t11,t10);}}

/* k6726 in body1497 in sprout in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6728(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6728,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6732,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 303  nextid");
t3=((C_word*)t0)[2];
f_6651(t3,t2);}

/* k6730 in k6726 in body1497 in sprout in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6732(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 303  scheduler-sprout");
f_6534(((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k6722 in body1497 in sprout in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6724(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
f_6681(2,t2,((C_word*)t0)[2]);}

/* do1511 in body1497 in sprout in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_6692(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6692,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,((C_word*)t0)[5]);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6702,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6717,a[2]=((C_word*)t0)[3],a[3]=t4,a[4]=t3,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 301  nextstart");
t6=((C_word*)t0)[2];
f_6623(t6,t5);}}

/* k6715 in do1511 in body1497 in sprout in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6717(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6717,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6721,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 301  nextid");
t3=((C_word*)t0)[2];
f_6651(t3,t2);}

/* k6719 in k6715 in do1511 in body1497 in sprout in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6721(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 301  scheduler-sprout");
f_6534(((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k6700 in do1511 in body1497 in sprout in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6702(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_6692(t3,((C_word*)t0)[2],t2);}

/* k6679 in body1497 in sprout in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6681(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 307  values");
C_values(2,0,((C_word*)t0)[2]);}

/* nextid in body1497 in sprout in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_6651(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_6651,NULL,2,t0,t1);}
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

/* nextstart in body1497 in sprout in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_6623(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_6623,NULL,2,t0,t1);}
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

/* load-sal-file in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6600(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6600,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6605,a[2]=lf[360],tmp=(C_word)a,a+=3,tmp);
((C_proc3)(void*)(*((C_word*)t3+1)))(3,t3,t1,t2);}

/* f_6605 in load-sal-file in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6605(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6605,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6610,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[341]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_6610(2,t4,C_SCHEME_FALSE);}}

/* k6608 */
static void C_ccall f_6610(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub1488(C_SCHEME_UNDEFINED,t1));}

/* scheduler-stop in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_6578(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6578,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6582,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[352]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k6580 in scheduler-stop in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6582(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6582,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_fixnum_argumentp(((C_word*)t0)[3]);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub1477,a[2]=lf[358],tmp=(C_word)a,a+=3,tmp);
((C_proc4)C_retrieve_proc(t4))(4,t4,((C_word*)t0)[2],t2,t3);}

/* scheduler-sprout in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_6534(C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6534,NULL,4,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_6538,a[2]=t2,a[3]=t1,a[4]=t4,a[5]=t3,tmp=(C_word)a,a+=6,tmp);
C_trace("##sys#gc");
t6=C_retrieve(lf[352]);
((C_proc3)C_retrieve_proc(t6))(3,t6,t5,C_SCHEME_FALSE);}

/* k6536 in scheduler-sprout in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6538(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6538,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[5]);
t4=(C_word)C_i_foreign_fixnum_argumentp(((C_word*)t0)[4]);
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub1457,a[2]=lf[355],tmp=(C_word)a,a+=3,tmp);
((C_proc6)C_retrieve_proc(t5))(6,t5,((C_word*)t0)[3],t2,((C_word*)t0)[2],t3,t4);}

/* scheduler-set-time-milliseconds in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_6525(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6525,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6529,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[352]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k6527 in scheduler-set-time-milliseconds in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6529(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6529,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub1449,a[2]=lf[351],tmp=(C_word)a,a+=3,tmp);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[3],t2,((C_word*)t0)[2]);}

/* current-time-seconds in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6513(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6513,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub1441(t2));}

/* current-time-milliseconds in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6510(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6510,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub1438(t2));}

/* print-error in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6467(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6467,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6472,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[341]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_6472(2,t4,C_SCHEME_FALSE);}}

/* k6470 in print-error in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6472(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub1419(C_SCHEME_UNDEFINED,t1));}

/* print-message in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6453(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6453,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6458,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[341]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_6458(2,t4,C_SCHEME_FALSE);}}

/* k6456 in print-message in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6458(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub1413(C_SCHEME_UNDEFINED,t1));}

/* change-directory in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6424(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+3)){
C_save_and_reclaim((void*)tr2rv,(void*)f_6424r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_6424r(t0,t1,t2);}}

static void C_ccall f_6424r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word *a=C_alloc(3);
t3=(C_word)C_vemptyp(t2);
t4=(C_truep(t3)?lf[340]:(C_word)C_i_vector_ref(t2,C_fix(0)));
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6433,a[2]=lf[342],tmp=(C_word)a,a+=3,tmp);
((C_proc3)(void*)(*((C_word*)t5+1)))(3,t5,t1,t4);}

/* f_6433 in change-directory in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6433(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6433,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6438,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[341]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_6438(2,t4,C_SCHEME_FALSE);}}

/* k6436 */
static void C_ccall f_6438(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub1407(C_SCHEME_UNDEFINED,t1));}

/* current-directory in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6413(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[3],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6413,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6418,a[2]=lf[338],tmp=(C_word)a,a+=3,tmp);
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,t1);}

/* f_6418 in current-directory in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6418(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6418,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(3));
C_trace("##sys#peek-c-string");
t3=*((C_word*)lf[337]+1);
((C_proc4)(void*)(*((C_word*)t3+1)))(4,t3,t1,(C_word)stub1402(t2),C_fix(0));}

/* list* in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6373(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+4)){
C_save_and_reclaim((void*)tr2r,(void*)f_6373r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_6373r(t0,t1,t2);}}

static void C_ccall f_6373r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a=C_alloc(4);
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 195  error");
t3=*((C_word*)lf[51]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[334]);}
else{
t3=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t3))){
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_car(t2));}
else{
t4=(C_word)C_i_car(t2);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6403,a[2]=t4,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
t6=(C_word)C_i_cdr(t2);
C_apply(4,0,t5,C_retrieve(lf[333]),t6);}}}

/* k6401 in list* in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6403(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6403,2,t0,t1);}
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[2],t1));}

/* butlast in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6325(C_word c,C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)tr3,(void*)f_6325,3,t0,t1,t2);}
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
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6359,a[2]=t5,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
t7=(C_word)C_i_cdr(t2);
C_trace("ChickenBridge.scm: 191  butlast");
t8=C_retrieve(lf[331]);
((C_proc3)C_retrieve_proc(t8))(3,t8,t6,t7);}}}

/* k6357 in butlast in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6359(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6359,2,t0,t1);}
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[2],t1));}

/* last in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6305(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6305,3,t0,t1,t2);}
t3=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t3))){
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,t2);}
else{
t4=(C_word)C_i_cdr(t2);
C_trace("ChickenBridge.scm: 185  last");
t5=C_retrieve(lf[329]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t1,t4);}}

/* tenth in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6285(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6285,3,t0,t1,t2);}
t3=(C_word)C_i_cddddr(t2);
t4=(C_word)C_i_cddddr(t3);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)C_i_cadr(t4));}

/* ninth in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6271(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6271,3,t0,t1,t2);}
t3=(C_word)C_i_cddddr(t2);
t4=(C_word)C_i_cddddr(t3);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)C_i_car(t4));}

/* eighth in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6261(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6261,3,t0,t1,t2);}
t3=(C_word)C_i_cddddr(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_cadddr(t3));}

/* seventh in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6251(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6251,3,t0,t1,t2);}
t3=(C_word)C_i_cddddr(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_caddr(t3));}

/* sixth in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6241(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6241,3,t0,t1,t2);}
t3=(C_word)C_i_cddddr(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_cadr(t3));}

/* fifth in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6231(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6231,3,t0,t1,t2);}
t3=(C_word)C_i_cddddr(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_car(t3));}

/* sal:output in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6209(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6209,2,t0,t1);}
C_trace("ChickenBridge.scm: 137  print-error");
t2=C_retrieve(lf[260]);
((C_proc3)C_retrieve_proc(t2))(3,t2,t1,lf[309]);}

/* sal:open in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6203(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6203,2,t0,t1);}
C_trace("ChickenBridge.scm: 137  print-error");
t2=C_retrieve(lf[260]);
((C_proc3)C_retrieve_proc(t2))(3,t2,t1,lf[306]);}

/* sal:load in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6156(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6156,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6160,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  file-exists?");
t4=C_retrieve(lf[303]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,t2);}

/* k6158 in sal:load in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6160(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_6160,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6163,a[2]=((C_word*)t0)[3],tmp=(C_word)a,a+=3,tmp);
if(C_truep(t1)){
t3=(C_word)C_i_string_length(((C_word*)t0)[2]);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6185,a[2]=((C_word*)t0)[2],a[3]=t2,tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_greaterp(t3,C_fix(4)))){
t5=(C_word)C_a_i_minus(&a,2,t3,C_fix(4));
C_trace("substring=?");
t6=C_retrieve(lf[299]);
((C_proc7)(void*)(*((C_word*)t6+1)))(7,t6,t4,((C_word*)t0)[2],lf[300],t5,C_fix(0),C_SCHEME_FALSE);}
else{
t5=t4;
f_6185(2,t5,C_SCHEME_FALSE);}}
else{
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6176,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  string-append");
t4=*((C_word*)lf[261]+1);
((C_proc5)C_retrieve_proc(t4))(5,t4,t3,lf[301],((C_word*)t0)[2],lf[302]);}}

/* k6174 in k6158 in sal:load in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6176(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  print-error");
t2=C_retrieve(lf[260]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k6183 in k6158 in sal:load in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6185(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(C_truep(t1)){
C_trace("ChickenBridge.scm: 137  load-sal-file");
t2=C_retrieve(lf[297]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}
else{
C_trace("ChickenBridge.scm: 137  load");
t2=C_retrieve(lf[298]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}}

/* k6161 in k6158 in sal:load in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6163(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  values");
C_values(2,0,((C_word*)t0)[2]);}

/* sal:chdir in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6147(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6147,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6151,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  change-directory");
t4=C_retrieve(lf[294]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,t2);}

/* k6149 in sal:chdir in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6151(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  values");
C_values(2,0,((C_word*)t0)[2]);}

/* sal:print in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5968(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+16)){
C_save_and_reclaim((void*)tr2r,(void*)f_5968r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_5968r(t0,t1,t2);}}

static void C_ccall f_5968r(C_word t0,C_word t1,C_word t2){
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
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5971,a[2]=t4,a[3]=lf[289],tmp=(C_word)a,a+=4,tmp));
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6116,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t7=C_SCHEME_UNDEFINED;
t8=(*a=C_VECTOR_TYPE|1,a[1]=t7,tmp=(C_word)a,a+=2,tmp);
t9=C_set_block_item(t8,0,(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6121,a[2]=t4,a[3]=t8,a[4]=lf[291],tmp=(C_word)a,a+=5,tmp));
t10=((C_word*)t8)[1];
f_6121(t10,t6,t2);}

/* do1256 in sal:print in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_6121(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6121,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 137  print-message");
t3=C_retrieve(lf[279]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[290]);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6134,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 137  printer");
t5=((C_word*)((C_word*)t0)[2])[1];
f_5971(t5,t3,t4);}}

/* k6132 in do1256 in sal:print in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6134(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_6121(t3,((C_word*)t0)[2],t2);}

/* k6114 in sal:print in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6116(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  values");
C_values(2,0,((C_word*)t0)[2]);}

/* printer in sal:print in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_5971(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_5971,NULL,3,t0,t1,t2);}
t3=t2;
if(C_truep(t3)){
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 137  print-message");
t4=C_retrieve(lf[279]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t1,lf[280]);}
else{
if(C_truep((C_word)C_i_pairp(t2))){
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5999,a[2]=t2,a[3]=((C_word*)t0)[2],a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  print-message");
t5=C_retrieve(lf[279]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,lf[284]);}
else{
t4=(C_word)C_eqp(t2,C_SCHEME_TRUE);
if(C_truep(t4)){
C_trace("ChickenBridge.scm: 137  print-message");
t5=C_retrieve(lf[279]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t1,lf[285]);}
else{
if(C_truep((C_word)C_i_numberp(t2))){
if(C_truep((C_word)C_i_inexactp(t2))){
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6086,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6090,a[2]=t5,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  decimals");
t7=*((C_word*)lf[30]+1);
((C_proc4)C_retrieve_proc(t7))(4,t7,t6,t2,C_fix(3));}
else{
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6097,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  number->string");
C_number_to_string(3,0,t5,t2);}}
else{
if(C_truep((C_word)C_i_stringp(t2))){
C_trace("ChickenBridge.scm: 137  print-message");
t5=C_retrieve(lf[279]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t1,t2);}
else{
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6113,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  sprintf");
t6=C_retrieve(lf[286]);
((C_proc4)C_retrieve_proc(t6))(4,t6,t5,lf[287],t2);}}}}}}
else{
C_trace("ChickenBridge.scm: 137  print-message");
t4=C_retrieve(lf[279]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t1,lf[288]);}}

/* k6111 in printer in sal:print in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6113(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  print-message");
t2=C_retrieve(lf[279]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k6095 in printer in sal:print in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6097(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  print-message");
t2=C_retrieve(lf[279]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k6088 in printer in sal:print in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6090(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  number->string");
C_number_to_string(3,0,((C_word*)t0)[2],t1);}

/* k6084 in printer in sal:print in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6086(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  print-message");
t2=C_retrieve(lf[279]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k5997 in printer in sal:print in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5999(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5999,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6002,a[2]=((C_word*)t0)[4],tmp=(C_word)a,a+=3,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6007,a[2]=((C_word*)t0)[3],a[3]=t4,a[4]=lf[283],tmp=(C_word)a,a+=5,tmp));
t6=((C_word*)t4)[1];
f_6007(t6,t2,((C_word*)t0)[2]);}

/* do1248 in k5997 in printer in sal:print in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_6007(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6007,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6017,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 137  printer");
t5=((C_word*)((C_word*)t0)[2])[1];
f_5971(t5,t3,t4);}}

/* k6015 in do1248 in k5997 in printer in sal:print in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6017(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6017,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6020,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
t3=(C_word)C_i_cdr(((C_word*)t0)[4]);
if(C_truep((C_word)C_i_nullp(t3))){
t4=t2;
f_6020(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 137  print-message");
t4=C_retrieve(lf[279]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t2,lf[282]);}}

/* k6018 in k6015 in do1248 in k5997 in printer in sal:print in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6020(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_6007(t3,((C_word*)t0)[2],t2);}

/* k6000 in k5997 in printer in sal:print in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_6002(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  print-message");
t2=C_retrieve(lf[279]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],lf[281]);}

/* sal in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5797(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[7],*a=ab;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_5797,6,t0,t1,t2,t3,t4,t5);}
t6=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t7=C_mutate(&lf[256],t2);
t8=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5803,a[2]=t6,a[3]=t5,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("map");
t9=*((C_word*)lf[276]+1);
((C_proc4)(void*)(*((C_word*)t9+1)))(4,t9,t8,C_retrieve2(lf[113],"list->token"),t4);}

/* k5801 in sal in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5803(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5803,2,t0,t1);}
t2=C_mutate(&lf[257],t1);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5806,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
if(C_truep((C_word)C_i_nequalp(((C_word*)((C_word*)t0)[2])[1],C_fix(0)))){
t4=C_set_block_item(((C_word*)t0)[2],0,C_fix(36608));
t5=t3;
f_5806(t5,t4);}
else{
t4=t3;
f_5806(t4,C_SCHEME_FALSE);}}

/* k5804 in k5801 in sal in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_5806(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_5806,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5810,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
t3=((C_word*)((C_word*)t0)[2])[1];
t4=C_retrieve2(lf[257],"*sal-tokens*");
t5=(C_word)C_a_i_list(&a,4,C_SCHEME_FALSE,C_fix(0),C_SCHEME_FALSE,C_SCHEME_FALSE);
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3609,a[2]=t4,a[3]=t3,a[4]=lf[274],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  call/cc");
t7=*((C_word*)lf[275]+1);
((C_proc3)C_retrieve_proc(t7))(3,t7,t2,t6);}

/* a3608 in k5804 in k5801 in sal in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3609(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_3609,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3615,a[2]=t2,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=lf[269],tmp=(C_word)a,a+=6,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3622,a[2]=t2,a[3]=lf[273],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  call-with-values");
C_call_with_values(4,0,t1,t3,t4);}

/* a3621 in a3608 in k5804 in k5801 in sal in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3622(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_3622,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3629,a[2]=((C_word*)t0)[2],a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
if(C_truep(t2)){
t6=(C_word)C_i_nullp(t4);
t7=t5;
f_3629(t7,(C_truep(t6)?t6:C_SCHEME_FALSE));}
else{
t6=t5;
f_3629(t6,C_SCHEME_FALSE);}}

/* k3627 in a3621 in a3608 in k5804 in k5801 in sal in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3629(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3629,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3636,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  add-emit-info");
f_3266(t2,lf[270],lf[271],C_SCHEME_END_OF_LIST);}
else{
C_trace("ChickenBridge.scm: 137  make-parse-error");
f_3086(((C_word*)t0)[4],lf[272],C_retrieve2(lf[196],"*maxtokpos*"));}}

/* k3634 in k3627 in a3621 in a3608 in k5804 in k5801 in sal in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3636(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  emit");
f_3294(((C_word*)t0)[4],((C_word*)t0)[3],t1,((C_word*)t0)[2]);}

/* a3614 in a3608 in k5804 in k5801 in sal in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3615(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3615,2,t0,t1);}
t2=lf[196]=C_fix(0);;
C_trace("ChickenBridge.scm: 137  parser");
f_3647(t1,((C_word*)t0)[4],((C_word*)t0)[3],C_SCHEME_FALSE,C_fix(0),C_SCHEME_FALSE,((C_word*)t0)[2]);}

/* k5808 in k5804 in k5801 in sal in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5810(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5810,2,t0,t1);}
t2=C_mutate(&lf[258],t1);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5813,a[2]=((C_word*)t0)[3],tmp=(C_word)a,a+=3,tmp);
t4=C_retrieve2(lf[258],"*sal-output*");
if(C_truep((C_word)C_i_structurep(t4,lf[142]))){
t5=C_retrieve2(lf[256],"*sal-string*");
t6=C_retrieve2(lf[258],"*sal-output*");
t7=(C_word)C_i_string_length(t5);
t8=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_5844,a[2]=t7,a[3]=t6,a[4]=t5,a[5]=t3,tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 137  parse-error-position");
f_3125(t8,t6);}
else{
if(C_truep(((C_word*)t0)[2])){
C_trace("ChickenBridge.scm: 137  pp");
t5=C_retrieve(lf[267]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,C_retrieve2(lf[258],"*sal-output*"));}
else{
C_trace("ChickenBridge.scm: 137  eval");
t5=C_retrieve(lf[268]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,C_retrieve2(lf[258],"*sal-output*"));}}}

/* k5842 in k5808 in k5804 in k5801 in sal in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5844(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5844,2,t0,t1);}
t2=(C_word)C_a_i_minus(&a,2,t1,C_fix(1));
t3=t2;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_fix(0);
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_5850,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=t1,a[7]=t6,a[8]=t4,tmp=(C_word)a,a+=9,tmp);
t8=C_SCHEME_UNDEFINED;
t9=(*a=C_VECTOR_TYPE|1,a[1]=t8,tmp=(C_word)a,a+=2,tmp);
t10=C_set_block_item(t9,0,(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_5937,a[2]=((C_word*)t0)[4],a[3]=t9,a[4]=t4,a[5]=lf[266],tmp=(C_word)a,a+=6,tmp));
t11=((C_word*)t9)[1];
f_5937(t11,t7,C_SCHEME_FALSE);}

/* do1222 in k5842 in k5808 in k5804 in k5801 in sal in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_5937(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_5937,NULL,3,t0,t1,t2);}
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=((C_word*)t3)[1];
t5=(C_truep(t4)?t4:(C_word)C_i_nequalp(((C_word*)((C_word*)t0)[4])[1],C_fix(-1)));
if(C_truep(t5)){
t6=t1;
((C_proc2)(void*)(*((C_word*)t6+1)))(2,t6,C_SCHEME_FALSE);}
else{
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5947,a[2]=t3,a[3]=t1,a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
t7=(C_word)C_i_string_ref(((C_word*)t0)[2],((C_word*)((C_word*)t0)[4])[1]);
t8=(C_word)C_eqp(t7,C_make_character(10));
if(C_truep(t8)){
t9=C_set_block_item(t3,0,C_SCHEME_TRUE);
t10=t6;
f_5947(t10,t9);}
else{
t9=(C_word)C_a_i_minus(&a,2,((C_word*)((C_word*)t0)[4])[1],C_fix(1));
t10=C_mutate(((C_word *)((C_word*)t0)[4])+1,t9);
t11=t6;
f_5947(t11,t10);}}}

/* k5945 in do1222 in k5842 in k5808 in k5804 in k5801 in sal in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_5947(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[4])[1];
f_5937(t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1]);}

/* k5848 in k5842 in k5808 in k5804 in k5801 in sal in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5850(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5850,2,t0,t1);}
t2=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[8])[1],C_fix(1));
t3=C_mutate(((C_word *)((C_word*)t0)[8])+1,t2);
t4=C_mutate(((C_word *)((C_word*)t0)[7])+1,((C_word*)t0)[6]);
t5=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5858,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[8],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[5],tmp=(C_word)a,a+=8,tmp);
t6=C_SCHEME_UNDEFINED;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=C_set_block_item(t7,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5907,a[2]=((C_word*)t0)[4],a[3]=t7,a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[7],a[6]=lf[265],tmp=(C_word)a,a+=7,tmp));
t9=((C_word*)t7)[1];
f_5907(t9,t5,C_SCHEME_FALSE);}

/* do1229 in k5848 in k5842 in k5808 in k5804 in k5801 in sal in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_5907(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_5907,NULL,3,t0,t1,t2);}
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=((C_word*)t3)[1];
t5=(C_truep(t4)?t4:(C_word)C_i_nequalp(((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[4]));
if(C_truep(t5)){
t6=t1;
((C_proc2)(void*)(*((C_word*)t6+1)))(2,t6,C_SCHEME_FALSE);}
else{
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5917,a[2]=t3,a[3]=t1,a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
t7=(C_word)C_i_string_ref(((C_word*)t0)[2],((C_word*)((C_word*)t0)[5])[1]);
t8=(C_word)C_eqp(t7,C_make_character(10));
if(C_truep(t8)){
t9=C_set_block_item(t3,0,C_SCHEME_TRUE);
t10=t6;
f_5917(t10,t9);}
else{
t9=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[5])[1],C_fix(1));
t10=C_mutate(((C_word *)((C_word*)t0)[5])+1,t9);
t11=t6;
f_5917(t11,t10);}}}

/* k5915 in do1229 in k5848 in k5842 in k5808 in k5804 in k5801 in sal in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_5917(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[4])[1];
f_5907(t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1]);}

/* k5856 in k5848 in k5842 in k5808 in k5804 in k5801 in sal in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5858(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[13],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5858,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5861,a[2]=((C_word*)t0)[7],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5868,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5872,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=t3,a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 137  parse-error-string");
f_3107(t4,((C_word*)t0)[2]);}

/* k5870 in k5856 in k5848 in k5842 in k5808 in k5804 in k5801 in sal in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5872(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5872,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5876,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 137  make-string");
t3=*((C_word*)lf[263]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t2,C_fix(1),C_make_character(10));}

/* k5874 in k5870 in k5856 in k5848 in k5842 in k5808 in k5804 in k5801 in sal in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5876(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5876,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5880,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 137  substring");
t3=*((C_word*)lf[264]+1);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k5878 in k5874 in k5870 in k5856 in k5848 in k5842 in k5808 in k5804 in k5801 in sal in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5880(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5880,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5884,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 137  make-string");
t3=*((C_word*)lf[263]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t2,C_fix(1),C_make_character(10));}

/* k5882 in k5878 in k5874 in k5870 in k5856 in k5848 in k5842 in k5808 in k5804 in k5801 in sal in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5884(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[16],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5884,2,t0,t1);}
t2=(C_word)C_a_i_minus(&a,2,((C_word*)t0)[7],((C_word*)((C_word*)t0)[6])[1]);
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5891,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=t2,tmp=(C_word)a,a+=8,tmp);
t4=(C_word)C_a_i_plus(&a,2,t2,C_fix(2));
C_trace("ChickenBridge.scm: 137  make-string");
t5=*((C_word*)lf[263]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,t4,C_make_character(32));}

/* k5889 in k5882 in k5878 in k5874 in k5870 in k5856 in k5848 in k5842 in k5808 in k5804 in k5801 in sal in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5891(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5891,2,t0,t1);}
t2=(C_word)C_i_string_set(t1,((C_word*)t0)[7],C_make_character(94));
t3=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[7],C_fix(1));
t4=(C_word)C_i_string_set(t1,t3,C_make_character(10));
C_trace("ChickenBridge.scm: 137  string-append");
t5=*((C_word*)lf[261]+1);
((C_proc8)C_retrieve_proc(t5))(8,t5,((C_word*)t0)[6],lf[262],((C_word*)t0)[5],((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k5866 in k5856 in k5848 in k5842 in k5808 in k5804 in k5801 in sal in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5868(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  print-error");
t2=C_retrieve(lf[260]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k5859 in k5856 in k5848 in k5842 in k5808 in k5804 in k5801 in sal in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5861(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  values");
C_values(2,0,((C_word*)t0)[2]);}

/* k5811 in k5808 in k5804 in k5801 in sal in k5789 in k5786 in k5783 in k5780 in k5777 in k5258 in k5255 in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5813(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  values");
C_values(2,0,((C_word*)t0)[2]);}

/* sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4736(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_4736,4,t0,t1,t2,t3);}
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
t32=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_4743,a[2]=t5,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
t33=(*a=C_CLOSURE_TYPE|18,a[1]=(C_word)f_4749,a[2]=t27,a[3]=t25,a[4]=t29,a[5]=t31,a[6]=t23,a[7]=t19,a[8]=t17,a[9]=t21,a[10]=t15,a[11]=t7,a[12]=t3,a[13]=t2,a[14]=t32,a[15]=t5,a[16]=t13,a[17]=t11,a[18]=t9,tmp=(C_word)a,a+=19,tmp);
t34=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 137  token-unit-type=?");
f_3222(t33,t34,C_fix(23296));}

/* k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4749(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[25],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4749,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_4753,a[2]=((C_word*)t0)[14],a[3]=((C_word*)t0)[15],a[4]=((C_word*)t0)[16],a[5]=((C_word*)t0)[17],a[6]=((C_word*)t0)[18],tmp=(C_word)a,a+=7,tmp);
t3=(C_word)C_i_cadr(((C_word*)t0)[13]);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t2,t3,C_SCHEME_END_OF_LIST,((C_word*)t0)[12]);}
else{
t2=(*a=C_CLOSURE_TYPE|17,a[1]=(C_word)f_4799,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[16],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[13],a[10]=((C_word*)t0)[12],a[11]=((C_word*)t0)[8],a[12]=((C_word*)t0)[9],a[13]=((C_word*)t0)[14],a[14]=((C_word*)t0)[15],a[15]=((C_word*)t0)[10],a[16]=((C_word*)t0)[18],a[17]=((C_word*)t0)[11],tmp=(C_word)a,a+=18,tmp);
t3=(C_word)C_i_caddr(((C_word*)t0)[13]);
C_trace("ChickenBridge.scm: 137  token-unit-type=?");
f_3222(t2,t3,C_fix(10756));}}

/* k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4799(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[26],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4799,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_4803,a[2]=((C_word*)t0)[9],a[3]=((C_word*)t0)[10],a[4]=((C_word*)t0)[11],a[5]=((C_word*)t0)[12],a[6]=((C_word*)t0)[13],a[7]=((C_word*)t0)[14],a[8]=((C_word*)t0)[15],a[9]=((C_word*)t0)[16],a[10]=((C_word*)t0)[17],tmp=(C_word)a,a+=11,tmp);
t3=(C_word)C_i_cadr(((C_word*)t0)[9]);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t2,t3,C_SCHEME_END_OF_LIST,((C_word*)t0)[10]);}
else{
t2=(*a=C_CLOSURE_TYPE|14,a[1]=(C_word)f_4896,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[10],a[9]=((C_word*)t0)[9],a[10]=((C_word*)t0)[13],a[11]=((C_word*)t0)[14],a[12]=((C_word*)t0)[8],a[13]=((C_word*)t0)[16],a[14]=((C_word*)t0)[17],tmp=(C_word)a,a+=15,tmp);
t3=(C_word)C_i_caddr(((C_word*)t0)[9]);
C_trace("ChickenBridge.scm: 137  token-unit-type=?");
f_3222(t2,t3,C_fix(22784));}}

/* k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4896(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4896,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_4900,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[9],a[4]=((C_word*)t0)[10],a[5]=((C_word*)t0)[11],a[6]=((C_word*)t0)[12],a[7]=((C_word*)t0)[13],a[8]=((C_word*)t0)[14],tmp=(C_word)a,a+=9,tmp);
t3=(C_word)C_i_cadr(((C_word*)t0)[9]);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t2,t3,C_SCHEME_END_OF_LIST,((C_word*)t0)[8]);}
else{
t2=(C_word)C_i_length(((C_word*)t0)[9]);
t3=C_mutate(((C_word *)((C_word*)t0)[7])+1,t2);
t4=(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_4964,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[10],a[8]=((C_word*)t0)[11],a[9]=((C_word*)t0)[6],a[10]=((C_word*)t0)[9],a[11]=((C_word*)t0)[7],a[12]=((C_word*)t0)[14],tmp=(C_word)a,a+=13,tmp);
t5=(C_word)C_i_cadr(((C_word*)t0)[9]);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t4,t5,C_SCHEME_END_OF_LIST,((C_word*)t0)[8]);}}

/* k4962 in k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4964(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4964,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[12])+1,t1);
t3=(C_word)C_a_i_minus(&a,2,((C_word*)((C_word*)t0)[11])[1],C_fix(1));
t4=(C_word)C_i_list_ref(((C_word*)t0)[10],t3);
t5=C_mutate(((C_word *)((C_word*)t0)[9])+1,t4);
t6=(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_4971,a[2]=((C_word*)t0)[10],a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[11],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[5],a[8]=((C_word*)t0)[9],a[9]=((C_word*)t0)[6],a[10]=((C_word*)t0)[12],a[11]=((C_word*)t0)[7],a[12]=((C_word*)t0)[8],tmp=(C_word)a,a+=13,tmp);
if(C_truep(((C_word*)((C_word*)t0)[9])[1])){
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5221,a[2]=t6,a[3]=((C_word*)t0)[9],tmp=(C_word)a,a+=4,tmp);
t8=(C_word)C_i_cadr(((C_word*)((C_word*)t0)[9])[1]);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t7,t8,C_SCHEME_END_OF_LIST,((C_word*)t0)[2]);}
else{
t7=C_set_block_item(((C_word*)t0)[9],0,C_fix(1));
t8=t6;
f_4971(t8,t7);}}

/* k5219 in k4962 in k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5221(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_4971(t3,t2);}

/* k4969 in k4962 in k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_4971(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_4971,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_4974,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],a[5]=((C_word*)t0)[8],a[6]=((C_word*)t0)[9],a[7]=((C_word*)t0)[10],a[8]=((C_word*)t0)[11],a[9]=((C_word*)t0)[12],tmp=(C_word)a,a+=10,tmp);
if(C_truep((C_word)C_i_nequalp(((C_word*)((C_word*)t0)[4])[1],C_fix(6)))){
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5160,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t2,a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[9],tmp=(C_word)a,a+=8,tmp);
t4=(C_word)C_i_cadddr(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t3,t4,C_SCHEME_END_OF_LIST,((C_word*)t0)[3]);}
else{
t3=C_set_block_item(((C_word*)t0)[9],0,C_fix(0));
t4=(C_word)C_i_caddr(((C_word*)t0)[2]);
t5=C_mutate(((C_word *)((C_word*)t0)[6])+1,t4);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5209,a[2]=t2,a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t7=(C_word)C_i_cadddr(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t6,t7,C_SCHEME_END_OF_LIST,((C_word*)t0)[3]);}}

/* k5207 in k4969 in k4962 in k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5209(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_4974(t3,t2);}

/* k5158 in k4969 in k4962 in k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5160(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5160,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[7])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5166,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 137  fifth");
t4=C_retrieve(lf[243]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)t0)[2]);}

/* k5164 in k5158 in k4969 in k4962 in k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5166(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5166,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5190,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 137  fifth");
t3=C_retrieve(lf[243]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)t0)[2]);}
else{
t2=C_set_block_item(((C_word*)t0)[6],0,C_SCHEME_FALSE);
t3=C_set_block_item(((C_word*)t0)[5],0,C_SCHEME_FALSE);
t4=((C_word*)t0)[4];
f_4974(t4,t3);}}

/* k5188 in k5164 in k5158 in k4969 in k4962 in k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5190(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5190,2,t0,t1);}
t2=(C_word)C_i_car(t1);
t3=C_mutate(((C_word *)((C_word*)t0)[6])+1,t2);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5174,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5186,a[2]=((C_word*)t0)[3],a[3]=t4,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  fifth");
t6=C_retrieve(lf[243]);
((C_proc3)C_retrieve_proc(t6))(3,t6,t5,((C_word*)t0)[2]);}

/* k5184 in k5188 in k5164 in k5158 in k4969 in k4962 in k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5186(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cadr(t1);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(((C_word*)t0)[3],t2,C_SCHEME_END_OF_LIST,((C_word*)t0)[2]);}

/* k5172 in k5188 in k5164 in k5158 in k4969 in k4962 in k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5174(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_4974(t3,t2);}

/* k4972 in k4969 in k4962 in k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_4974(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[15],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4974,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_4977,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],tmp=(C_word)a,a+=10,tmp);
if(C_truep((C_word)C_i_numberp(((C_word*)((C_word*)t0)[5])[1]))){
t3=t2;
f_4977(t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5136,a[2]=t2,a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[9],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  gensym");
t4=C_retrieve(lf[237]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,lf[254]);}}

/* k5134 in k4972 in k4969 in k4962 in k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5136(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[24],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5136,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_5140,a[2]=((C_word*)t0)[2],a[3]=t1,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=(C_word)C_a_i_list(&a,5,t1,((C_word*)((C_word*)t0)[3])[1],C_SCHEME_FALSE,C_SCHEME_FALSE,C_SCHEME_FALSE);
t4=(C_word)C_a_i_list(&a,1,t3);
C_trace("ChickenBridge.scm: 137  append");
t5=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t2,((C_word*)((C_word*)t0)[4])[1],t4);}

/* k5138 in k5134 in k4972 in k4969 in k4962 in k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5140(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[5])+1,t1);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,((C_word*)t0)[3]);
t4=((C_word*)t0)[2];
f_4977(t4,t3);}

/* k4975 in k4972 in k4969 in k4962 in k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_4977(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[15],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4977,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_4980,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],tmp=(C_word)a,a+=10,tmp);
if(C_truep((C_word)C_i_numberp(((C_word*)((C_word*)t0)[6])[1]))){
t3=t2;
f_4980(t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5113,a[2]=t2,a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[9],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  gensym");
t4=C_retrieve(lf[237]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,lf[253]);}}

/* k5111 in k4975 in k4972 in k4969 in k4962 in k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5113(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[24],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5113,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_5117,a[2]=((C_word*)t0)[2],a[3]=t1,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=(C_word)C_a_i_list(&a,5,t1,((C_word*)((C_word*)t0)[3])[1],C_SCHEME_FALSE,C_SCHEME_FALSE,C_SCHEME_FALSE);
t4=(C_word)C_a_i_list(&a,1,t3);
C_trace("ChickenBridge.scm: 137  append");
t5=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t2,((C_word*)((C_word*)t0)[4])[1],t4);}

/* k5115 in k5111 in k4975 in k4972 in k4969 in k4962 in k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5117(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[5])+1,t1);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,((C_word*)t0)[3]);
t4=((C_word*)t0)[2];
f_4980(t4,t3);}

/* k4978 in k4975 in k4972 in k4969 in k4962 in k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_4980(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[15],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4980,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_4983,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],tmp=(C_word)a,a+=10,tmp);
if(C_truep(((C_word*)((C_word*)t0)[2])[1])){
if(C_truep((C_word)C_i_numberp(((C_word*)((C_word*)t0)[2])[1]))){
t3=t2;
f_4983(t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5090,a[2]=t2,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[9],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  gensym");
t4=C_retrieve(lf[237]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,lf[252]);}}
else{
t3=t2;
f_4983(t3,C_SCHEME_UNDEFINED);}}

/* k5088 in k4978 in k4975 in k4972 in k4969 in k4962 in k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5090(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[24],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5090,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_5094,a[2]=((C_word*)t0)[2],a[3]=t1,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=(C_word)C_a_i_list(&a,5,t1,((C_word*)((C_word*)t0)[3])[1],C_SCHEME_FALSE,C_SCHEME_FALSE,C_SCHEME_FALSE);
t4=(C_word)C_a_i_list(&a,1,t3);
C_trace("ChickenBridge.scm: 137  append");
t5=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t2,((C_word*)((C_word*)t0)[4])[1],t4);}

/* k5092 in k5088 in k4978 in k4975 in k4972 in k4969 in k4962 in k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5094(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[5])+1,t1);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,((C_word*)t0)[3]);
t4=((C_word*)t0)[2];
f_4983(t4,t3);}

/* k4981 in k4978 in k4975 in k4972 in k4969 in k4962 in k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_4983(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_4983,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_4986,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],tmp=(C_word)a,a+=8,tmp);
t3=((C_word*)((C_word*)t0)[3])[1];
if(C_truep(t3)){
t4=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5015,a[2]=((C_word*)t0)[3],a[3]=t2,a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[2],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 137  token-unit-type=?");
f_3222(t4,((C_word*)((C_word*)t0)[3])[1],C_fix(21248));}
else{
t4=(C_word)C_a_i_list(&a,3,lf[215],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[5])[1]);
t5=(C_word)C_a_i_list(&a,3,lf[235],((C_word*)((C_word*)t0)[7])[1],t4);
t6=C_mutate(((C_word *)((C_word*)t0)[5])+1,t5);
t7=t2;
f_4986(t7,t6);}}

/* k5013 in k4981 in k4978 in k4975 in k4972 in k4969 in k4962 in k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5015(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5015,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,3,lf[236],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[6])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[5])+1,t2);
t4=(C_word)C_a_i_list(&a,3,lf[215],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[4])[1]);
t5=(C_word)C_a_i_list(&a,3,lf[235],((C_word*)((C_word*)t0)[7])[1],t4);
t6=C_mutate(((C_word *)((C_word*)t0)[4])+1,t5);
t7=((C_word*)t0)[3];
f_4986(t7,t6);}
else{
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5033,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 137  token-unit-type=?");
f_3222(t2,((C_word*)((C_word*)t0)[2])[1],C_fix(23552));}}

/* k5031 in k5013 in k4981 in k4978 in k4975 in k4972 in k4969 in k4962 in k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5033(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5033,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,3,lf[248],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[6])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[5])+1,t2);
t4=(C_word)C_a_i_list(&a,3,lf[215],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[4])[1]);
t5=(C_word)C_a_i_list(&a,3,lf[235],((C_word*)((C_word*)t0)[7])[1],t4);
t6=C_mutate(((C_word *)((C_word*)t0)[4])+1,t5);
t7=((C_word*)t0)[3];
f_4986(t7,t6);}
else{
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5051,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 137  token-unit-type=?");
f_3222(t2,((C_word*)((C_word*)t0)[2])[1],C_fix(20992));}}

/* k5049 in k5031 in k5013 in k4981 in k4978 in k4975 in k4972 in k4969 in k4962 in k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5051(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5051,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,3,lf[249],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[6])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[5])+1,t2);
t4=(C_word)C_a_i_list(&a,3,lf[250],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[4])[1]);
t5=(C_word)C_a_i_list(&a,3,lf[235],((C_word*)((C_word*)t0)[7])[1],t4);
t6=C_mutate(((C_word *)((C_word*)t0)[4])+1,t5);
t7=((C_word*)t0)[3];
f_4986(t7,t6);}
else{
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5069,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 137  token-unit-type=?");
f_3222(t2,((C_word*)((C_word*)t0)[2])[1],C_fix(21760));}}

/* k5067 in k5049 in k5031 in k5013 in k4981 in k4978 in k4975 in k4972 in k4969 in k4962 in k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_5069(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5069,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,3,lf[251],((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[5])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t4=(C_word)C_a_i_list(&a,3,lf[250],((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[3])[1]);
t5=(C_word)C_a_i_list(&a,3,lf[235],((C_word*)((C_word*)t0)[6])[1],t4);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t5);
t7=((C_word*)t0)[2];
f_4986(t7,t6);}
else{
t2=((C_word*)t0)[2];
f_4986(t2,C_SCHEME_UNDEFINED);}}

/* k4984 in k4981 in k4978 in k4975 in k4972 in k4969 in k4962 in k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_4986(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4986,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_4990,a[2]=((C_word*)t0)[6],a[3]=((C_word*)t0)[7],tmp=(C_word)a,a+=4,tmp);
t3=(C_word)C_a_i_list(&a,5,((C_word*)((C_word*)t0)[5])[1],((C_word*)((C_word*)t0)[4])[1],C_SCHEME_FALSE,((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);
t4=(C_word)C_a_i_list(&a,1,t3);
C_trace("ChickenBridge.scm: 137  append");
t5=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t2,((C_word*)((C_word*)t0)[7])[1],t4);}

/* k4988 in k4984 in k4981 in k4978 in k4975 in k4972 in k4969 in k4962 in k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4990(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_4743(t3,t2);}

/* k4898 in k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4900(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4900,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_4904,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[8],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
t4=(C_word)C_i_cadddr(((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t3,t4,C_SCHEME_END_OF_LIST,((C_word*)t0)[2]);}

/* k4902 in k4898 in k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4904(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4904,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_4908,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[5],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 137  gensym");
t4=C_retrieve(lf[237]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,lf[247]);}

/* k4906 in k4902 in k4898 in k4894 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4908(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4908,2,t0,t1);}
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
f_4743(t12,t11);}

/* k4801 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4803(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4803,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[10])+1,t1);
t3=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_4807,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[10],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],a[10]=((C_word*)t0)[9],tmp=(C_word)a,a+=11,tmp);
t4=(C_word)C_i_cadddr(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t3,t4,C_SCHEME_END_OF_LIST,((C_word*)t0)[3]);}

/* k4805 in k4801 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4807(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4807,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[10])+1,t1);
t3=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_4811,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[10],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 137  fifth");
t4=C_retrieve(lf[243]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)t0)[2]);}

/* k4809 in k4805 in k4801 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4811(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4811,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[9])+1,t1);
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_4814,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],a[5]=((C_word*)t0)[8],tmp=(C_word)a,a+=6,tmp);
if(C_truep(((C_word*)((C_word*)t0)[9])[1])){
t4=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_4830,a[2]=t3,a[3]=((C_word*)t0)[8],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[4],a[8]=((C_word*)t0)[9],tmp=(C_word)a,a+=9,tmp);
t5=(C_word)C_i_cadr(((C_word*)((C_word*)t0)[9])[1]);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t4,t5,C_SCHEME_END_OF_LIST,((C_word*)t0)[2]);}
else{
t4=(C_word)C_a_i_list(&a,3,lf[235],((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[3])[1]);
t5=C_mutate(((C_word *)((C_word*)t0)[5])+1,t4);
t6=t3;
f_4814(t6,t5);}}

/* k4828 in k4809 in k4805 in k4801 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4830(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4830,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_4834,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[8],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 137  gensym");
t4=C_retrieve(lf[237]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,lf[242]);}

/* k4832 in k4828 in k4809 in k4805 in k4801 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4834(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4834,2,t0,t1);}
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
f_4814(t12,t11);}

/* k4812 in k4809 in k4805 in k4801 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_4814(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4814,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_4818,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t3=(C_word)C_a_i_list(&a,5,((C_word*)((C_word*)t0)[3])[1],C_SCHEME_FALSE,((C_word*)((C_word*)t0)[2])[1],C_SCHEME_FALSE,C_SCHEME_FALSE);
t4=(C_word)C_a_i_list(&a,1,t3);
C_trace("ChickenBridge.scm: 137  append");
t5=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t2,((C_word*)((C_word*)t0)[5])[1],t4);}

/* k4816 in k4812 in k4809 in k4805 in k4801 in k4797 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4818(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_4743(t3,t2);}

/* k4751 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4753(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4753,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_4757,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 137  gensym");
t4=C_retrieve(lf[237]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,lf[239]);}

/* k4755 in k4751 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4757(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4757,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_4761,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 137  gensym");
t4=C_retrieve(lf[237]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,lf[238]);}

/* k4759 in k4755 in k4751 in k4747 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4761(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4761,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(C_word)C_a_i_list(&a,5,((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[5])[1],C_SCHEME_FALSE,C_SCHEME_FALSE,C_SCHEME_FALSE);
t4=(C_word)C_a_i_list(&a,3,lf[215],((C_word*)((C_word*)t0)[4])[1],C_fix(1));
t5=(C_word)C_a_i_list(&a,3,lf[235],((C_word*)((C_word*)t0)[4])[1],t4);
t6=(C_word)C_a_i_list(&a,3,lf[236],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[6])[1]);
t7=(C_word)C_a_i_list(&a,5,((C_word*)((C_word*)t0)[4])[1],C_fix(0),C_SCHEME_FALSE,t5,t6);
t8=(C_word)C_a_i_list(&a,2,t3,t7);
t9=C_mutate(((C_word *)((C_word*)t0)[3])+1,t8);
t10=((C_word*)t0)[2];
f_4743(t10,t9);}

/* k4741 in sal-parse-stepping in k4732 in k4729 in k4726 in k4723 in k4720 in k4717 in k4714 in k4711 in k4708 in k4705 in k4702 in k4699 in k4696 in k4693 in k4690 in k4687 in k4684 in k4681 in k4678 in k4675 in k4672 in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_4743(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  make-parse-unit");
f_3137(((C_word*)t0)[3],C_fix(33024),((C_word*)((C_word*)t0)[2])[1],C_SCHEME_FALSE);}

/* inf->pre in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_4558(C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_4558,NULL,2,t1,t2);}
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
t14=C_set_block_item(t13,0,(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_4570,a[2]=t9,a[3]=t13,a[4]=t11,a[5]=t5,a[6]=t7,a[7]=t3,a[8]=lf[232],tmp=(C_word)a,a+=9,tmp));
t15=((C_word*)t13)[1];
f_4570(t15,t1);}
else{
t12=t1;
((C_proc2)(void*)(*((C_word*)t12+1)))(2,t12,((C_word*)t3)[1]);}}

/* do859 in inf->pre in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_4570(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_4570,NULL,2,t0,t1);}
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[7])[1]))){
t2=t1;
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,((C_word*)((C_word*)t0)[6])[1]);}
else{
t2=(C_word)C_i_car(((C_word*)((C_word*)t0)[7])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[5])+1,t2);
t4=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[7])[1]);
t5=C_mutate(((C_word *)((C_word*)t0)[7])+1,t4);
t6=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_4589,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[7],a[6]=t1,a[7]=((C_word*)t0)[3],a[8]=((C_word*)t0)[4],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 137  is-op?");
f_4537(t6,((C_word*)((C_word*)t0)[5])[1]);}}

/* k4587 in do859 in inf->pre in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4589(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4589,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_4592,a[2]=((C_word*)t0)[6],a[3]=((C_word*)t0)[7],tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_numberp(((C_word*)((C_word*)t0)[8])[1]))){
t4=C_SCHEME_UNDEFINED;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_set_block_item(t5,0,(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_4607,a[2]=((C_word*)t0)[8],a[3]=t5,a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[5],a[8]=lf[231],tmp=(C_word)a,a+=9,tmp));
t7=((C_word*)t5)[1];
f_4607(t7,t3,C_SCHEME_FALSE,C_SCHEME_TRUE,C_SCHEME_END_OF_LIST);}
else{
t4=C_mutate(((C_word *)((C_word*)t0)[3])+1,((C_word*)((C_word*)t0)[2])[1]);
t5=t3;
f_4592(2,t5,t4);}}

/* do861 in k4587 in do859 in inf->pre in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_4607(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
C_save_and_reclaim((void*)trf_4607,NULL,5,t0,t1,t2,t3,t4);}
t5=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t8=(C_word)C_i_nullp(((C_word*)((C_word*)t0)[7])[1]);
t9=(C_truep(t8)?t8:(C_word)C_i_not(((C_word*)t6)[1]));
if(C_truep(t9)){
t10=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_4621,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],tmp=(C_word)a,a+=6,tmp);
t11=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4635,a[2]=t10,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  reverse");
t12=*((C_word*)lf[201]+1);
((C_proc3)C_retrieve_proc(t12))(3,t12,t11,((C_word*)t7)[1]);}
else{
t10=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_4639,a[2]=((C_word*)t0)[7],a[3]=((C_word*)t0)[2],a[4]=t7,a[5]=t6,a[6]=t1,a[7]=((C_word*)t0)[3],a[8]=t5,tmp=(C_word)a,a+=9,tmp);
t11=(C_word)C_i_car(((C_word*)((C_word*)t0)[7])[1]);
C_trace("ChickenBridge.scm: 137  is-op?");
f_4537(t10,t11);}}

/* k4637 in do861 in k4587 in do859 in inf->pre in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4639(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4639,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_4642,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[8],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
t4=(C_truep(((C_word*)((C_word*)t0)[8])[1])?(C_word)C_i_less_or_equalp(((C_word*)((C_word*)t0)[8])[1],((C_word*)((C_word*)t0)[3])[1]):C_SCHEME_FALSE);
if(C_truep(t4)){
t5=C_set_block_item(((C_word*)t0)[5],0,C_SCHEME_FALSE);
t6=t3;
f_4642(t6,t5);}
else{
t5=(C_word)C_i_car(((C_word*)((C_word*)t0)[2])[1]);
t6=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[2])[1]);
t7=C_mutate(((C_word *)((C_word*)t0)[2])+1,t6);
t8=(C_word)C_a_i_cons(&a,2,t5,((C_word*)((C_word*)t0)[4])[1]);
t9=C_mutate(((C_word *)((C_word*)t0)[4])+1,t8);
t10=t3;
f_4642(t10,t9);}}

/* k4640 in k4637 in do861 in k4587 in do859 in inf->pre in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_4642(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[6])[1];
f_4607(t2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k4633 in do861 in k4587 in do859 in inf->pre in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4635(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  inf->pre");
f_4558(((C_word*)t0)[2],t1);}

/* k4619 in do861 in k4587 in do859 in inf->pre in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4621(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[18],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4621,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[5])+1,t1);
t3=(C_truep(((C_word*)((C_word*)t0)[4])[1])?(C_word)C_a_i_list(&a,3,((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[5])[1]):(C_word)C_a_i_list(&a,3,((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[5])[1],C_SCHEME_FALSE));
t4=C_mutate(((C_word *)((C_word*)t0)[4])+1,t3);
t5=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,t4);}

/* k4590 in k4587 in do859 in inf->pre in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4592(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[3])[1];
f_4570(t2,((C_word*)t0)[2]);}

/* is-op? in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_4537(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4537,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_4544,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  token-unit?");
f_3206(t3,t2);}

/* k4542 in is-op? in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4544(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4544,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4547,a[2]=((C_word*)t0)[3],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-type");
f_3158(t2,((C_word*)t0)[2]);}
else{
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}}

/* k4545 in k4542 in is-op? in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4547(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4547,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_4553,a[2]=t1,a[3]=((C_word*)t0)[2],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  SalOpType?");
f_4314(t2,t1);}

/* k4551 in k4545 in k4542 in is-op? in k4533 in k4530 in k4527 in k4524 in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4553(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4553,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[3];
t3=((C_word*)t0)[2];
t4=t2;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_a_i_bitwise_and(&a,2,t3,C_fix(255)));}
else{
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}}

/* remove-token-type in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_4472(C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)trf_4472,NULL,3,t1,t2,t3);}
t4=(C_word)C_a_i_list(&a,1,C_SCHEME_TRUE);
t5=t4;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=C_SCHEME_UNDEFINED;
t8=(*a=C_VECTOR_TYPE|1,a[1]=t7,tmp=(C_word)a,a+=2,tmp);
t9=C_set_block_item(t8,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_4481,a[2]=t3,a[3]=t6,a[4]=t8,a[5]=t4,a[6]=lf[226],tmp=(C_word)a,a+=7,tmp));
t10=((C_word*)t8)[1];
f_4481(t10,t1,t2);}

/* do825 in remove-token-type in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_4481(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4481,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_i_cdr(((C_word*)t0)[5]));}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_4494,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_4504,a[2]=((C_word*)t0)[3],a[3]=t2,a[4]=t3,tmp=(C_word)a,a+=5,tmp);
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 137  token-unit-type=?");
f_3222(t4,t5,((C_word*)t0)[2]);}}

/* k4502 in do825 in remove-token-type in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4504(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4504,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
f_4494(t2,C_SCHEME_FALSE);}
else{
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=(C_word)C_a_i_list(&a,1,t2);
t4=(C_word)C_i_set_cdr(((C_word*)((C_word*)t0)[2])[1],t3);
t5=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[2])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[2])+1,t5);
t7=((C_word*)t0)[4];
f_4494(t7,t6);}}

/* k4492 in do825 in remove-token-type in k4468 in k4465 in k4462 in k4459 in k4456 in k4453 in k4450 in k4447 in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_4494(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_4481(t3,((C_word*)t0)[2],t2);}

/* SalType=? in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_4428(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4428,NULL,3,t1,t2,t3);}
t4=(C_word)C_a_i_arithmetic_shift(&a,2,t2,C_fix(-8));
t5=(C_word)C_a_i_arithmetic_shift(&a,2,t3,C_fix(-8));
t6=t1;
((C_proc2)(void*)(*((C_word*)t6+1)))(2,t6,(C_word)C_i_nequalp(t4,t5));}

/* SalRuleType? in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_4416(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4416,NULL,2,t1,t2);}
t3=(C_word)C_i_lessp(C_fix(25600),t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_truep(t3)?(C_word)C_i_lessp(t2,C_fix(38400)):C_SCHEME_FALSE));}

/* SalOpType? in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_4314(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4314,NULL,2,t1,t2);}
t3=(C_word)C_i_lessp(C_fix(6656),t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_truep(t3)?(C_word)C_i_lessp(t2,C_fix(11520)):C_SCHEME_FALSE));}

/* SalTokenType? in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_4266(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4266,NULL,2,t1,t2);}
t3=(C_word)C_i_lessp(C_fix(0),t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_truep(t3)?(C_word)C_i_lessp(t2,C_fix(25600)):C_SCHEME_FALSE));}

/* parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3647(C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
C_word tmp;
C_word t8;
C_word t9;
C_word t10;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3647,NULL,7,t1,t2,t3,t4,t5,t6,t7);}
t8=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t9=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_3651,a[2]=t4,a[3]=t7,a[4]=t6,a[5]=t5,a[6]=t8,a[7]=t1,a[8]=t2,tmp=(C_word)a,a+=9,tmp);
if(C_truep(t6)){
C_trace("ChickenBridge.scm: 137  printf");
t10=C_retrieve(lf[218]);
((C_proc6)C_retrieve_proc(t10))(6,t10,t9,lf[219],t5,t2,((C_word*)t8)[1]);}
else{
t10=t9;
f_3651(2,t10,C_SCHEME_UNDEFINED);}}

/* k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3651(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3651,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_3654,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 137  null-tokens?");
f_2829(t2,((C_word*)((C_word*)t0)[6])[1]);}

/* k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3654(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[18],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3654,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_3657,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
if(C_truep(t1)){
t3=t2;
f_3657(t3,t1);}
else{
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4072,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4076,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4080,a[2]=t4,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  first-token");
f_2817(t5,((C_word*)((C_word*)t0)[6])[1]);}}

/* k4078 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4080(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  token-position");
f_2776(((C_word*)t0)[2],t1);}

/* k4074 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4076(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  max");
t2=*((C_word*)lf[217]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[2],C_retrieve2(lf[196],"*maxtokpos*"),t1);}

/* k4070 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4072(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(&lf[196],t1);
t3=((C_word*)t0)[2];
f_3657(t3,t2);}

/* k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3657(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3657,NULL,2,t0,t1);}
t2=((C_word*)t0)[8];
if(C_truep((C_word)C_i_numberp(t2))){
t3=((C_word*)t0)[8];
t4=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_3672,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=t3,a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 137  SalTokenType?");
f_4266(t4,t3);}
else{
t3=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_3780,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[2],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 137  pattern-clause?");
f_2968(t3,((C_word*)t0)[8]);}}

/* k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3780(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[13],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3780,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_3786,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
t3=((C_word*)t0)[2];
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3013,a[2]=t2,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  pattern-clause?");
f_2968(t4,t3);}
else{
C_trace("ChickenBridge.scm: 137  error");
t2=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[6],lf[216],((C_word*)t0)[2]);}}

/* k3011 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3013(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=((C_word*)t0)[2];
f_3786(t3,(C_word)C_eqp(t2,lf[176]));}
else{
t2=((C_word*)t0)[2];
f_3786(t2,C_SCHEME_FALSE);}}

/* k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3786(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_3786,NULL,2,t0,t1);}
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
t11=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_3795,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=t10,a[7]=((C_word*)t0)[7],a[8]=t6,a[9]=t8,a[10]=t4,a[11]=((C_word*)t0)[6],tmp=(C_word)a,a+=12,tmp);
C_trace("ChickenBridge.scm: 137  pattern-nsubs");
f_2986(t11,((C_word*)t0)[2]);}
else{
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_3874,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[6],tmp=(C_word)a,a+=8,tmp);
t4=((C_word*)t0)[2];
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3029,a[2]=t3,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  pattern-clause?");
f_2968(t5,t4);}}

/* k3027 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3029(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=((C_word*)t0)[2];
f_3874(t3,(C_word)C_eqp(t2,lf[177]));}
else{
t2=((C_word*)t0)[2];
f_3874(t2,C_SCHEME_FALSE);}}

/* k3872 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3874(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_3874,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=C_SCHEME_FALSE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_SCHEME_FALSE;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_SCHEME_END_OF_LIST;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_3880,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t7,a[8]=t5,a[9]=((C_word*)t0)[7],a[10]=t3,tmp=(C_word)a,a+=11,tmp);
C_trace("ChickenBridge.scm: 137  pattern-nsubs");
f_2986(t8,((C_word*)t0)[2]);}
else{
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_3944,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[2],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[6],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 137  pattern-zero-or-more?");
f_3054(t2,((C_word*)t0)[2]);}}

/* k3942 in k3872 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3944(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3944,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_3947,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
if(C_truep(t1)){
t3=t2;
f_3947(t3,t1);}
else{
t3=((C_word*)t0)[5];
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3045,a[2]=t2,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  pattern-clause?");
f_2968(t4,t3);}}

/* k3043 in k3942 in k3872 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3045(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=((C_word*)t0)[2];
f_3947(t3,(C_word)C_eqp(t2,lf[215]));}
else{
t2=((C_word*)t0)[2];
f_3947(t2,C_SCHEME_FALSE);}}

/* k3945 in k3942 in k3872 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3947(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_3947,NULL,2,t0,t1);}
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
t12=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_3953,a[2]=((C_word*)t0)[5],a[3]=t11,a[4]=((C_word*)t0)[7],a[5]=t9,a[6]=t3,a[7]=((C_word*)t0)[6],tmp=(C_word)a,a+=8,tmp);
t13=C_SCHEME_UNDEFINED;
t14=(*a=C_VECTOR_TYPE|1,a[1]=t13,tmp=(C_word)a,a+=2,tmp);
t15=C_set_block_item(t14,0,(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_3976,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=t5,a[7]=t11,a[8]=t7,a[9]=((C_word*)t0)[7],a[10]=t9,a[11]=t14,a[12]=t3,a[13]=lf[210],tmp=(C_word)a,a+=14,tmp));
t16=((C_word*)t14)[1];
f_3976(t16,t12);}
else{
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_4025,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[6],tmp=(C_word)a,a+=8,tmp);
t3=((C_word*)t0)[5];
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3077,a[2]=t2,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  pattern-clause?");
f_2968(t4,t3);}}

/* k3075 in k3945 in k3942 in k3872 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3077(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=((C_word*)t0)[2];
f_4025(t3,(C_word)C_eqp(t2,lf[214]));}
else{
t2=((C_word*)t0)[2];
f_4025(t2,C_SCHEME_FALSE);}}

/* k4023 in k3945 in k3942 in k3872 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_4025(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_4025,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=C_SCHEME_FALSE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_SCHEME_END_OF_LIST;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_SCHEME_END_OF_LIST;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_4034,a[2]=((C_word*)t0)[6],a[3]=t7,a[4]=t5,a[5]=((C_word*)t0)[7],a[6]=t3,tmp=(C_word)a,a+=7,tmp);
t9=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_4045,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[5],a[7]=lf[211],tmp=(C_word)a,a+=8,tmp);
t10=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_4051,a[2]=t7,a[3]=t5,a[4]=t3,a[5]=lf[212],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 137  call-with-values");
C_call_with_values(4,0,t8,t9,t10);}
else{
t2=((C_word*)t0)[5];
t3=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 137  error");
t4=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,((C_word*)t0)[7],lf[213],t3);}}

/* a4050 in k4023 in k3945 in k3942 in k3872 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4051(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_4051,5,t0,t1,t2,t3,t4);}
t5=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t3);
t7=C_mutate(((C_word *)((C_word*)t0)[2])+1,t4);
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,t7);}

/* a4044 in k4023 in k3945 in k3942 in k3872 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4045(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4045,2,t0,t1);}
C_trace("ChickenBridge.scm: 137  parser");
f_3647(t1,((C_word*)t0)[6],((C_word*)((C_word*)t0)[5])[1],C_SCHEME_TRUE,((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k4032 in k4023 in k3945 in k3942 in k3872 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4034(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(C_truep(((C_word*)((C_word*)t0)[6])[1])){
C_trace("ChickenBridge.scm: 137  values");
C_values(5,0,((C_word*)t0)[5],((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1]);}
else{
C_trace("ChickenBridge.scm: 137  values");
C_values(5,0,((C_word*)t0)[5],C_SCHEME_TRUE,C_SCHEME_FALSE,((C_word*)((C_word*)t0)[2])[1]);}}

/* do562 in k3945 in k3942 in k3872 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3976(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[14],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3976,NULL,2,t0,t1);}
t2=(C_word)C_i_not(((C_word*)((C_word*)t0)[12])[1]);
t3=(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_3986,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],a[10]=((C_word*)t0)[10],a[11]=((C_word*)t0)[12],a[12]=((C_word*)t0)[11],a[13]=t1,tmp=(C_word)a,a+=14,tmp);
if(C_truep(t2)){
t4=t3;
f_3986(2,t4,t2);}
else{
C_trace("ChickenBridge.scm: 137  null-tokens?");
f_2829(t3,((C_word*)((C_word*)t0)[8])[1]);}}

/* k3984 in do562 in k3945 in k3942 in k3872 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3986(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[24],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3986,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[13];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}
else{
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_3989,a[2]=((C_word*)t0)[6],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[8],a[5]=((C_word*)t0)[9],a[6]=((C_word*)t0)[10],a[7]=((C_word*)t0)[11],a[8]=((C_word*)t0)[13],a[9]=((C_word*)t0)[12],tmp=(C_word)a,a+=10,tmp);
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_4006,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[8],a[6]=((C_word*)t0)[5],a[7]=lf[208],tmp=(C_word)a,a+=8,tmp);
t4=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_4012,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[11],a[5]=lf[209],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 137  call-with-values");
C_call_with_values(4,0,t2,t3,t4);}}

/* a4011 in k3984 in do562 in k3945 in k3942 in k3872 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4012(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_4012,5,t0,t1,t2,t3,t4);}
t5=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t3);
t7=C_mutate(((C_word *)((C_word*)t0)[2])+1,t4);
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,t7);}

/* a4005 in k3984 in do562 in k3945 in k3942 in k3872 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_4006(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4006,2,t0,t1);}
C_trace("ChickenBridge.scm: 137  parser");
f_3647(t1,((C_word*)t0)[6],((C_word*)((C_word*)t0)[5])[1],C_SCHEME_TRUE,((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k3987 in k3984 in do562 in k3945 in k3942 in k3872 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3989(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3989,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3992,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[9],tmp=(C_word)a,a+=4,tmp);
if(C_truep(((C_word*)((C_word*)t0)[7])[1])){
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_3999,a[2]=t2,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 137  append");
t4=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t3,((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[2])[1]);}
else{
t3=t2;
f_3992(t3,C_SCHEME_UNDEFINED);}}

/* k3997 in k3987 in k3984 in do562 in k3945 in k3942 in k3872 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3999(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3999,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=C_mutate(((C_word *)((C_word*)t0)[5])+1,((C_word*)((C_word*)t0)[4])[1]);
t4=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[3])[1],C_fix(1));
t5=C_mutate(((C_word *)((C_word*)t0)[3])+1,t4);
t6=((C_word*)t0)[2];
f_3992(t6,t5);}

/* k3990 in k3987 in k3984 in do562 in k3945 in k3942 in k3872 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3992(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[3])[1];
f_3976(t2,((C_word*)t0)[2]);}

/* k3951 in k3945 in k3942 in k3872 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3953(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3953,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3956,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],tmp=(C_word)a,a+=6,tmp);
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3962,a[2]=((C_word*)t0)[5],a[3]=t2,a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[3],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 137  pattern-zero-or-more?");
f_3054(t3,((C_word*)t0)[2]);}

/* k3960 in k3951 in k3945 in k3942 in k3872 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3962(C_word c,C_word t0,C_word t1){
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
f_3956(t4,t3);}
else{
t3=C_set_block_item(((C_word*)t0)[4],0,C_SCHEME_FALSE);
t4=C_set_block_item(((C_word*)t0)[2],0,C_SCHEME_END_OF_LIST);
t5=((C_word*)t0)[3];
f_3956(t5,t4);}}

/* k3954 in k3951 in k3945 in k3942 in k3872 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3956(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  values");
C_values(5,0,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k3878 in k3872 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3880(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3880,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_3883,a[2]=((C_word*)t0)[6],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[8],a[5]=((C_word*)t0)[9],a[6]=((C_word*)t0)[10],tmp=(C_word)a,a+=7,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_3898,a[2]=((C_word*)t0)[7],a[3]=((C_word*)t0)[8],a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[5],a[9]=t4,a[10]=t1,a[11]=((C_word*)t0)[10],a[12]=lf[207],tmp=(C_word)a,a+=13,tmp));
t6=((C_word*)t4)[1];
f_3898(t6,t2,C_fix(0));}

/* do542 in k3878 in k3872 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3898(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_3898,NULL,3,t0,t1,t2);}
t3=((C_word*)((C_word*)t0)[11])[1];
t4=(C_truep(t3)?t3:(C_word)C_i_nequalp(t2,((C_word*)t0)[10]));
if(C_truep(t4)){
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,C_SCHEME_FALSE);}
else{
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3908,a[2]=t1,a[3]=((C_word*)t0)[9],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t6=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_3917,a[2]=t2,a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],a[8]=lf[205],tmp=(C_word)a,a+=9,tmp);
t7=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3931,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[11],a[5]=lf[206],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 137  call-with-values");
C_call_with_values(4,0,t5,t6,t7);}}

/* a3930 in do542 in k3878 in k3872 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3931(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_3931,5,t0,t1,t2,t3,t4);}
t5=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t3);
t7=C_mutate(((C_word *)((C_word*)t0)[2])+1,t4);
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,t7);}

/* a3916 in do542 in k3878 in k3872 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3917(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[7],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3917,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_3925,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=t1,a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 137  pattern-sub");
f_2996(t2,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k3923 in a3916 in do542 in k3878 in k3872 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3925(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3925,2,t0,t1);}
t2=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[6],C_fix(1));
C_trace("ChickenBridge.scm: 137  parser");
f_3647(((C_word*)t0)[5],t1,((C_word*)((C_word*)t0)[4])[1],C_SCHEME_FALSE,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k3906 in do542 in k3878 in k3872 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3908(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3908,2,t0,t1);}
t2=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[4],C_fix(1));
t3=((C_word*)((C_word*)t0)[3])[1];
f_3898(t3,((C_word*)t0)[2],t2);}

/* k3881 in k3878 in k3872 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3883(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(C_truep(((C_word*)((C_word*)t0)[6])[1])){
C_trace("ChickenBridge.scm: 137  values");
C_values(5,0,((C_word*)t0)[5],((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1]);}
else{
C_trace("ChickenBridge.scm: 137  values");
C_values(5,0,((C_word*)t0)[5],C_SCHEME_FALSE,C_SCHEME_END_OF_LIST,((C_word*)((C_word*)t0)[2])[1]);}}

/* k3793 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3795(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_3795,2,t0,t1);}
t2=C_SCHEME_FALSE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_3798,a[2]=((C_word*)t0)[7],a[3]=t3,a[4]=((C_word*)t0)[8],a[5]=((C_word*)t0)[9],a[6]=((C_word*)t0)[10],a[7]=((C_word*)t0)[11],tmp=(C_word)a,a+=8,tmp);
t5=C_SCHEME_UNDEFINED;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=C_set_block_item(t6,0,(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_3817,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[8],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[9],a[8]=((C_word*)t0)[6],a[9]=((C_word*)t0)[10],a[10]=t6,a[11]=t3,a[12]=t1,a[13]=lf[204],tmp=(C_word)a,a+=14,tmp));
t8=((C_word*)t6)[1];
f_3817(t8,t4,C_fix(0));}

/* do520 in k3793 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3817(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_3817,NULL,3,t0,t1,t2);}
t3=(C_word)C_i_nequalp(t2,((C_word*)t0)[12]);
t4=(C_truep(t3)?t3:((C_word*)((C_word*)t0)[11])[1]);
if(C_truep(t4)){
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,C_SCHEME_FALSE);}
else{
t5=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_3830,a[2]=((C_word*)t0)[11],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[8],a[5]=((C_word*)t0)[9],a[6]=t1,a[7]=((C_word*)t0)[10],a[8]=t2,tmp=(C_word)a,a+=9,tmp);
t6=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_3850,a[2]=t2,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=lf[202],tmp=(C_word)a,a+=9,tmp);
t7=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3864,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[8],a[4]=((C_word*)t0)[9],a[5]=lf[203],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 137  call-with-values");
C_call_with_values(4,0,t5,t6,t7);}}

/* a3863 in do520 in k3793 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3864(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_3864,5,t0,t1,t2,t3,t4);}
t5=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t3);
t7=C_mutate(((C_word *)((C_word*)t0)[2])+1,t4);
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,t7);}

/* a3849 in do520 in k3793 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3850(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[7],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3850,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_3858,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=t1,a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 137  pattern-sub");
f_2996(t2,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k3856 in a3849 in do520 in k3793 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3858(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3858,2,t0,t1);}
t2=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[6],C_fix(1));
C_trace("ChickenBridge.scm: 137  parser");
f_3647(((C_word*)t0)[5],t1,((C_word*)((C_word*)t0)[4])[1],C_SCHEME_FALSE,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k3828 in do520 in k3793 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3830(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_3830,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3833,a[2]=((C_word*)t0)[6],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[8],tmp=(C_word)a,a+=5,tmp);
t3=((C_word*)((C_word*)t0)[5])[1];
if(C_truep(t3)){
t4=(C_word)C_a_i_cons(&a,2,((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1]);
t5=C_mutate(((C_word *)((C_word*)t0)[3])+1,t4);
t6=t2;
f_3833(t6,t5);}
else{
t4=C_set_block_item(((C_word*)t0)[2],0,C_SCHEME_TRUE);
t5=t2;
f_3833(t5,t4);}}

/* k3831 in k3828 in do520 in k3793 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3833(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3833,NULL,2,t0,t1);}
t2=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[4],C_fix(1));
t3=((C_word*)((C_word*)t0)[3])[1];
f_3817(t3,((C_word*)t0)[2],t2);}

/* k3796 in k3793 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3798(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_3798,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3801,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],tmp=(C_word)a,a+=6,tmp);
if(C_truep(((C_word*)((C_word*)t0)[3])[1])){
t3=C_set_block_item(((C_word*)t0)[6],0,C_SCHEME_FALSE);
t4=C_set_block_item(((C_word*)t0)[5],0,C_SCHEME_END_OF_LIST);
t5=C_mutate(((C_word *)((C_word*)t0)[4])+1,((C_word*)((C_word*)t0)[2])[1]);
t6=t2;
f_3801(t6,t5);}
else{
t3=C_set_block_item(((C_word*)t0)[6],0,C_SCHEME_TRUE);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3815,a[2]=t2,a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  reverse");
t5=*((C_word*)lf[201]+1);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,((C_word*)((C_word*)t0)[5])[1]);}}

/* k3813 in k3796 in k3793 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3815(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_3801(t3,t2);}

/* k3799 in k3796 in k3793 in k3784 in k3778 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3801(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  values");
C_values(5,0,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k3670 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3672(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[13],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3672,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3678,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  null-tokens?");
f_2829(t2,((C_word*)((C_word*)t0)[6])[1]);}
else{
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_3730,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[4],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 137  SalRuleType?");
f_4416(t2,((C_word*)t0)[5]);}}

/* k3728 in k3670 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3730(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3730,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_3733,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 137  get-rule");
f_2944(t2,((C_word*)t0)[2],C_SCHEME_END_OF_LIST);}
else{
C_trace("ChickenBridge.scm: 137  error");
t2=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[3],lf[200],((C_word*)t0)[2]);}}

/* k3731 in k3728 in k3670 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3733(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_3733,2,t0,t1);}
t2=t1;
t3=(C_word)C_i_check_structure(t2,lf[122]);
t4=(C_word)C_i_block_ref(t2,C_fix(3));
t5=t1;
t6=(C_word)C_i_check_structure(t5,lf[122]);
t7=(C_word)C_i_block_ref(t5,C_fix(4));
t8=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_3744,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=t4,a[6]=((C_word*)t0)[6],a[7]=lf[198],tmp=(C_word)a,a+=8,tmp);
t9=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3754,a[2]=((C_word*)t0)[3],a[3]=t7,a[4]=lf[199],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  call-with-values");
C_call_with_values(4,0,((C_word*)t0)[2],t8,t9);}

/* a3753 in k3731 in k3728 in k3670 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3754(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_3754,5,t0,t1,t2,t3,t4);}
if(C_truep(t2)){
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3765,a[2]=t4,a[3]=t2,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
if(C_truep(((C_word*)t0)[3])){
C_trace("ChickenBridge.scm: 137  func");
t6=((C_word*)t0)[3];
((C_proc4)C_retrieve_proc(t6))(4,t6,t5,t3,((C_word*)t0)[2]);}
else{
t6=t5;
f_3765(2,t6,t3);}}
else{
C_trace("ChickenBridge.scm: 137  values");
C_values(5,0,t1,C_SCHEME_FALSE,C_SCHEME_FALSE,t4);}}

/* k3763 in a3753 in k3731 in k3728 in k3670 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3765(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  values");
C_values(5,0,((C_word*)t0)[4],((C_word*)t0)[3],t1,((C_word*)t0)[2]);}

/* a3743 in k3731 in k3728 in k3670 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3744(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3744,2,t0,t1);}
t2=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[6],C_fix(1));
C_trace("ChickenBridge.scm: 137  parser");
f_3647(t1,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],C_SCHEME_FALSE,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k3676 in k3670 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3678(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3678,2,t0,t1);}
if(C_truep(t1)){
C_trace("ChickenBridge.scm: 137  values");
C_values(5,0,((C_word*)t0)[4],C_SCHEME_FALSE,C_SCHEME_FALSE,C_SCHEME_END_OF_LIST);}
else{
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3688,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  first-token");
f_2817(t2,((C_word*)((C_word*)t0)[3])[1]);}}

/* k3686 in k3676 in k3670 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3688(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3688,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3694,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3724,a[2]=((C_word*)t0)[2],a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  token-type");
f_2740(t3,t1);}

/* k3722 in k3686 in k3676 in k3670 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3724(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  SalType=?");
f_4428(((C_word*)t0)[3],t1,((C_word*)t0)[2]);}

/* k3692 in k3686 in k3676 in k3670 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3694(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3694,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3701,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3709,a[2]=((C_word*)t0)[2],a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  token-type");
f_2740(t3,((C_word*)t0)[2]);}
else{
C_trace("ChickenBridge.scm: 137  values");
C_values(5,0,((C_word*)t0)[3],C_SCHEME_FALSE,C_SCHEME_FALSE,((C_word*)((C_word*)t0)[4])[1]);}}

/* k3707 in k3692 in k3686 in k3676 in k3670 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3709(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3709,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3713,a[2]=((C_word*)t0)[2],a[3]=t1,a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  token-string");
f_2758(t2,((C_word*)t0)[2]);}

/* k3711 in k3707 in k3692 in k3686 in k3676 in k3670 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3713(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3713,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3717,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  token-position");
f_2776(t2,((C_word*)t0)[2]);}

/* k3715 in k3711 in k3707 in k3692 in k3686 in k3676 in k3670 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3717(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  make-parse-unit");
f_3137(((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k3699 in k3692 in k3686 in k3676 in k3670 in k3655 in k3652 in k3649 in parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3701(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
t2=((C_word*)((C_word*)t0)[3])[1];
t3=(C_word)C_i_cdr(t2);
C_trace("ChickenBridge.scm: 137  values");
C_values(5,0,((C_word*)t0)[2],C_SCHEME_TRUE,t1,t3);}

/* simple-unit-emitter in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3543(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3543,NULL,2,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3545,a[2]=t2,a[3]=lf[194],tmp=(C_word)a,a+=4,tmp));}

/* f_3545 in simple-unit-emitter in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3545(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[9],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_3545,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3549,a[2]=((C_word*)t0)[2],a[3]=t1,a[4]=t4,a[5]=t3,tmp=(C_word)a,a+=6,tmp);
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3593,a[2]=t5,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-parsed");
f_3176(t6,t2);}

/* k3591 */
static void C_ccall f_3593(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  append");
t2=*((C_word*)lf[193]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[2],t1,C_SCHEME_END_OF_LIST);}

/* k3547 */
static void C_ccall f_3549(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_3549,2,t0,t1);}
t2=t1;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=((C_word*)t3)[1];
t5=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_3552,a[2]=t3,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=t4,tmp=(C_word)a,a+=7,tmp);
if(C_truep(((C_word*)t0)[2])){
t6=(C_word)C_i_set_car(((C_word*)t3)[1],((C_word*)t0)[2]);
t7=(C_word)C_i_cdr(((C_word*)t3)[1]);
t8=C_set_block_item(t3,0,t7);
t9=t5;
f_3552(t9,t8);}
else{
t6=t5;
f_3552(t6,C_SCHEME_UNDEFINED);}}

/* k3550 in k3547 */
static void C_fcall f_3552(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3552,NULL,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_3557,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=t3,a[5]=((C_word*)t0)[6],a[6]=lf[192],tmp=(C_word)a,a+=7,tmp));
t5=((C_word*)t3)[1];
f_3557(t5,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1]);}

/* do477 in k3550 in k3547 */
static void C_fcall f_3557(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3557,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,((C_word*)t0)[5]);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3578,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t3,t4,((C_word*)t0)[3],((C_word*)t0)[2]);}}

/* k3576 in do477 in k3550 in k3547 */
static void C_ccall f_3578(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
t2=(C_word)C_i_set_car(((C_word*)t0)[4],t1);
t3=(C_word)C_i_cdr(((C_word*)t0)[4]);
t4=((C_word*)((C_word*)t0)[3])[1];
f_3557(t4,((C_word*)t0)[2],t3);}

/* simple-unit-parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3535(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3535,NULL,2,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3537,a[2]=t2,a[3]=lf[189],tmp=(C_word)a,a+=4,tmp));}

/* f_3537 in simple-unit-parser in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3537(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word *a;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_3537,4,t0,t1,t2,t3);}
C_trace("ChickenBridge.scm: 137  make-parse-unit");
f_3137(t1,((C_word*)t0)[2],t2,C_SCHEME_FALSE);}

/* emit-list in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3327(C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3327,NULL,4,t1,t2,t3,t4);}
if(C_truep((C_word)C_i_nullp(t2))){
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,C_SCHEME_END_OF_LIST);}
else{
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3344,a[2]=t4,a[3]=t3,a[4]=t2,a[5]=t1,tmp=(C_word)a,a+=6,tmp);
t6=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 137  emit");
f_3294(t5,t6,t3,t4);}}

/* k3342 in emit-list in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3344(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3344,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3348,a[2]=t1,a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t3=(C_word)C_i_cdr(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 137  emit-list");
f_3327(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k3346 in k3342 in emit-list in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3348(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3348,2,t0,t1);}
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[2],t1));}

/* emit in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3294(C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3294,NULL,4,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3301,a[2]=t4,a[3]=t3,a[4]=t2,a[5]=t1,tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 137  token-unit?");
f_3206(t5,t2);}

/* k3299 in emit in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3301(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_3301,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[5];
t3=((C_word*)t0)[4];
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3372,a[2]=t3,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-type");
f_3158(t4,t3);}
else{
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3310,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
t3=((C_word*)t0)[4];
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3245,a[2]=t3,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit?");
f_3143(t4,t3);}}

/* k3243 in k3299 in emit in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3245(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3245,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3252,a[2]=((C_word*)t0)[3],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-type");
f_3158(t2,((C_word*)t0)[2]);}
else{
t2=((C_word*)t0)[3];
f_3310(2,t2,C_SCHEME_FALSE);}}

/* k3250 in k3243 in k3299 in emit in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3252(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  SalRuleType?");
f_4416(((C_word*)t0)[2],t1);}

/* k3308 in k3299 in emit in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3310(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_3310,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[5];
t3=((C_word*)t0)[4];
t4=((C_word*)t0)[3];
t5=((C_word*)t0)[2];
t6=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3510,a[2]=t5,a[3]=t4,a[4]=t3,a[5]=t2,tmp=(C_word)a,a+=6,tmp);
t7=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3533,a[2]=t6,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-type");
f_3158(t7,t3);}
else{
if(C_truep((C_word)C_i_listp(((C_word*)t0)[4]))){
C_trace("ChickenBridge.scm: 137  emit-list");
f_3327(((C_word*)t0)[5],((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2]);}
else{
C_trace("ChickenBridge.scm: 137  error");
t2=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[5],lf[184],((C_word*)t0)[4]);}}}

/* k3531 in k3308 in k3299 in emit in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3533(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  get-rule");
f_2944(((C_word*)t0)[2],t1,C_SCHEME_END_OF_LIST);}

/* k3508 in k3308 in k3299 in emit in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3510(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3510,2,t0,t1);}
t2=(C_word)C_i_check_structure(t1,lf[122]);
t3=(C_word)C_i_block_ref(t1,C_fix(5));
if(C_truep(t3)){
C_trace("ChickenBridge.scm: 137  meth");
t4=t3;
((C_proc5)C_retrieve_proc(t4))(5,t4,((C_word*)t0)[5],((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2]);}
else{
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3526,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[5],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-parsed");
f_3176(t4,((C_word*)t0)[4]);}}

/* k3524 in k3508 in k3308 in k3299 in emit in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3526(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  emit");
f_3294(((C_word*)t0)[4],t1,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k3370 in k3299 in emit in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3372(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3372,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3375,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-parsed");
f_3176(t2,((C_word*)t0)[2]);}

/* k3373 in k3370 in k3299 in emit in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3375(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_3375,2,t0,t1);}
t2=((C_word*)t0)[4];
t3=(C_word)C_i_lessp(C_fix(2560),t2);
t4=(C_truep(t3)?(C_word)C_i_lessp(t2,C_fix(3584)):C_SCHEME_FALSE);
if(C_truep(t4)){
C_trace("ChickenBridge.scm: 137  string->number");
C_string_to_number(3,0,((C_word*)t0)[3],t1);}
else{
t5=((C_word*)t0)[4];
t6=(C_word)C_i_lessp(C_fix(13056),t5);
t7=(C_truep(t6)?(C_word)C_i_lessp(t5,C_fix(23808)):C_SCHEME_FALSE);
if(C_truep(t7)){
C_trace("ChickenBridge.scm: 137  string->symbol");
t8=*((C_word*)lf[173]+1);
((C_proc3)C_retrieve_proc(t8))(3,t8,((C_word*)t0)[3],t1);}
else{
t8=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3399,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[4],a[4]=t1,a[5]=((C_word*)t0)[3],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 137  SalOpType?");
f_4314(t8,((C_word*)t0)[4]);}}}

/* k3397 in k3373 in k3370 in k3299 in emit in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3399(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_3399,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3405,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  SalType=?");
f_4428(t2,((C_word*)t0)[3],C_fix(7941));}
else{
t2=((C_word*)t0)[3];
t3=(C_word)C_i_lessp(C_fix(4096),t2);
t4=(C_truep(t3)?(C_word)C_i_lessp(t2,C_fix(4864)):C_SCHEME_FALSE);
if(C_truep(t4)){
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3450,a[2]=((C_word*)t0)[5],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  SalType=?");
f_4428(t5,((C_word*)t0)[3],C_fix(4352));}
else{
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3456,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 137  SalType=?");
f_4428(t5,((C_word*)t0)[3],C_fix(2304));}}}

/* k3454 in k3397 in k3373 in k3370 in k3299 in emit in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3456(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3456,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[5];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,((C_word*)t0)[4]);}
else{
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3462,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 137  SalType=?");
f_4428(t2,((C_word*)t0)[2],C_fix(6144));}}

/* k3460 in k3454 in k3397 in k3373 in k3370 in k3299 in emit in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3462(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3462,2,t0,t1);}
if(C_truep(t1)){
C_trace("ChickenBridge.scm: 137  string->keyword");
t2=C_retrieve(lf[179]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[5],((C_word*)t0)[4]);}
else{
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3471,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 137  SalType=?");
f_4428(t2,((C_word*)t0)[2],C_fix(3840));}}

/* k3469 in k3460 in k3454 in k3397 in k3373 in k3370 in k3299 in emit in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3471(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3471,2,t0,t1);}
if(C_truep(t1)){
C_trace("ChickenBridge.scm: 137  string->keyword");
t2=C_retrieve(lf[179]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[5],((C_word*)t0)[4]);}
else{
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3480,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 137  SalType=?");
f_4428(t2,((C_word*)t0)[2],C_fix(6400));}}

/* k3478 in k3469 in k3460 in k3454 in k3397 in k3373 in k3370 in k3299 in emit in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3480(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3480,2,t0,t1);}
if(C_truep(t1)){
C_trace("ChickenBridge.scm: 137  string->symbol");
t2=*((C_word*)lf[173]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[5],((C_word*)t0)[4]);}
else{
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3489,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 137  SalType=?");
f_4428(t2,((C_word*)t0)[2],C_fix(25344));}}

/* k3487 in k3478 in k3469 in k3460 in k3454 in k3397 in k3373 in k3370 in k3299 in emit in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3489(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3489,2,t0,t1);}
if(C_truep(t1)){
C_trace("ChickenBridge.scm: 137  error");
t2=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[5],lf[180],((C_word*)t0)[4]);}
else{
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3498,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[5],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  SalType=?");
f_4428(t2,((C_word*)t0)[2],C_fix(25088));}}

/* k3496 in k3487 in k3478 in k3469 in k3460 in k3454 in k3397 in k3373 in k3370 in k3299 in emit in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3498(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(C_truep(t1)){
C_trace("ChickenBridge.scm: 137  string->symbol");
t2=*((C_word*)lf[173]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[4],((C_word*)t0)[3]);}
else{
C_trace("ChickenBridge.scm: 137  error");
t2=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[4],lf[181],((C_word*)t0)[2]);}}

/* k3448 in k3397 in k3373 in k3370 in k3299 in emit in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3450(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_truep(t1)?C_SCHEME_TRUE:C_SCHEME_FALSE));}

/* k3403 in k3397 in k3373 in k3370 in k3299 in emit in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3405(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3405,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,lf[61]);}
else{
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3411,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  SalType=?");
f_4428(t2,((C_word*)t0)[2],C_fix(8199));}}

/* k3409 in k3403 in k3397 in k3373 in k3370 in k3299 in emit in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3411(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3411,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,lf[174]);}
else{
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3417,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  SalType=?");
f_4428(t2,((C_word*)t0)[2],C_fix(10244));}}

/* k3415 in k3409 in k3403 in k3397 in k3373 in k3370 in k3299 in emit in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3417(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3417,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,lf[175]);}
else{
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3423,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  SalType=?");
f_4428(t2,((C_word*)t0)[2],C_fix(8450));}}

/* k3421 in k3415 in k3409 in k3403 in k3397 in k3373 in k3370 in k3299 in emit in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3423(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3423,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,lf[176]);}
else{
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3429,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  SalType=?");
f_4428(t2,((C_word*)t0)[2],C_fix(8705));}}

/* k3427 in k3421 in k3415 in k3409 in k3403 in k3397 in k3373 in k3370 in k3299 in emit in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3429(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3429,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,lf[177]);}
else{
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3435,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  SalType=?");
f_4428(t2,((C_word*)t0)[2],C_fix(8963));}}

/* k3433 in k3427 in k3421 in k3415 in k3409 in k3403 in k3397 in k3373 in k3370 in k3299 in emit in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3435(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(C_truep(t1)){
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,lf[178]);}
else{
C_trace("ChickenBridge.scm: 137  string->symbol");
t2=*((C_word*)lf[173]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}}

/* set-emit-info! in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3276(C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3276,NULL,4,t1,t2,t3,t4);}
t5=(C_word)C_i_assoc(t2,t4);
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3283,a[2]=t3,a[3]=t5,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
if(C_truep(t5)){
t7=t6;
f_3283(2,t7,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 137  error");
t7=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t7))(4,t7,t6,lf[170],t2);}}

/* k3281 in set-emit-info! in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3283(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_i_set_cdr(((C_word*)t0)[3],((C_word*)t0)[2]));}

/* add-emit-info in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3266(C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3266,NULL,4,t1,t2,t3,t4);}
t5=(C_word)C_a_i_cons(&a,2,t2,t3);
t6=t1;
((C_proc2)(void*)(*((C_word*)t6+1)))(2,t6,(C_word)C_a_i_cons(&a,2,t5,t4));}

/* get-emit-info in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3254(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3254,NULL,3,t1,t2,t3);}
t4=(C_word)C_i_assoc(t2,t3);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_truep(t4)?(C_word)C_i_cdr(t4):C_SCHEME_FALSE));}

/* token-unit-type=? in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3222(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3222,NULL,3,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3229,a[2]=t2,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 137  token-unit?");
f_3206(t4,t2);}

/* k3227 in token-unit-type=? in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3229(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3229,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3236,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-type");
f_3158(t2,((C_word*)t0)[2]);}
else{
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}}

/* k3234 in k3227 in token-unit-type=? in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3236(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  SalType=?");
f_4428(((C_word*)t0)[3],t1,((C_word*)t0)[2]);}

/* token-unit? in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3206(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3206,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3213,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit?");
f_3143(t3,t2);}

/* k3211 in token-unit? in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3213(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3213,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3220,a[2]=((C_word*)t0)[3],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  parse-unit-type");
f_3158(t2,((C_word*)t0)[2]);}
else{
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}}

/* k3218 in k3211 in token-unit? in k3202 in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3220(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 137  SalTokenType?");
f_4266(((C_word*)t0)[2],t1);}

/* parse-unit-position in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3194(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3194,NULL,2,t1,t2);}
t3=(C_word)C_i_check_structure(t2,lf[149]);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_block_ref(t2,C_fix(3)));}

/* parse-unit-parsed in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3176(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3176,NULL,2,t1,t2);}
t3=(C_word)C_i_check_structure(t2,lf[149]);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_block_ref(t2,C_fix(2)));}

/* parse-unit-type in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3158(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3158,NULL,2,t1,t2);}
t3=(C_word)C_i_check_structure(t2,lf[149]);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_block_ref(t2,C_fix(1)));}

/* parse-unit? in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3143(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3143,NULL,2,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_i_structurep(t2,lf[149]));}

/* make-parse-unit in k3133 in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3137(C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3137,NULL,4,t1,t2,t3,t4);}
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)C_a_i_record(&a,4,lf[149],t2,t3,t4));}

/* parse-error-position in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3125(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3125,NULL,2,t1,t2);}
t3=(C_word)C_i_check_structure(t2,lf[142]);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_block_ref(t2,C_fix(2)));}

/* parse-error-string in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3107(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3107,NULL,2,t1,t2);}
t3=(C_word)C_i_check_structure(t2,lf[142]);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_block_ref(t2,C_fix(1)));}

/* make-parse-error in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3086(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3086,NULL,3,t1,t2,t3);}
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_a_i_record(&a,3,lf[142],t2,t3));}

/* pattern-zero-or-more? in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_3054(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3054,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3061,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  pattern-clause?");
f_2968(t3,t2);}

/* k3059 in pattern-zero-or-more? in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3061(C_word c,C_word t0,C_word t1){
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

/* pattern-sub in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_2996(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2996,NULL,3,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3004,a[2]=t3,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 137  pattern-subs");
f_2980(t4,t2);}

/* k3002 in pattern-sub in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_3004(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_i_list_ref(t1,((C_word*)t0)[2]));}

/* pattern-nsubs in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_2986(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2986,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2994,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 137  pattern-subs");
f_2980(t3,t2);}

/* k2992 in pattern-nsubs in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2994(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_i_length(t1));}

/* pattern-subs in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_2980(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2980,NULL,2,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_i_cdr(t2));}

/* pattern-clause? in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_2968(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2968,NULL,2,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_i_pairp(t2));}

/* get-rule in k2940 in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_2944(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2944,NULL,3,t1,t2,t3);}
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("ChickenBridge.scm: 137  hash-table-ref");
t4=*((C_word*)lf[127]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t1,C_retrieve2(lf[120],"*rules*"),t2);}
else{
C_trace("ChickenBridge.scm: 137  hash-table-ref/default");
t4=C_retrieve(lf[128]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t1,C_retrieve2(lf[120],"*rules*"),t3);}}

/* rule-name in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_2860(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2860,NULL,2,t1,t2);}
t3=(C_word)C_i_check_structure(t2,lf[122]);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_block_ref(t2,C_fix(1)));}

/* make-rule in k2835 in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_2839(C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
C_word tmp;
C_word t7;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2839,NULL,6,t1,t2,t3,t4,t5,t6);}
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)C_a_i_record(&a,6,lf[122],t2,t3,t4,t5,t6));}

/* null-tokens? in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_2829(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2829,NULL,2,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_i_nullp(t2));}

/* first-token in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_2817(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2817,NULL,2,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_i_car(t2));}

/* list->token in k2784 in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2788(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2788,3,t0,t1,t2);}
t3=(C_word)C_i_car(t2);
t4=(C_word)C_eqp(t3,lf[114]);
if(C_truep(t4)){
t5=(C_word)C_i_cdr(t2);
C_apply(4,0,t1,lf[104],t5);}
else{
C_apply(4,0,t1,lf[104],t2);}}

/* token-position in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_2776(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2776,NULL,2,t1,t2);}
t3=(C_word)C_i_check_structure(t2,lf[105]);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_block_ref(t2,C_fix(3)));}

/* token-string in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_2758(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2758,NULL,2,t1,t2);}
t3=(C_word)C_i_check_structure(t2,lf[105]);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_block_ref(t2,C_fix(2)));}

/* token-type in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_2740(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2740,NULL,2,t1,t2);}
t3=(C_word)C_i_check_structure(t2,lf[105]);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_block_ref(t2,C_fix(1)));}

/* make-token in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2719(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_2719,5,t0,t1,t2,t3,t4);}
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)C_a_i_record(&a,4,lf[105],t2,t3,t4));}

/* ranpink in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2713(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2713,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub145(t2));}

/* ranbrown in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2707(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2707,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub148(t2));}

/* rangamma in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2688(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2rv,(void*)f_2688r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_2688r(t0,t1,t2);}}

static void C_ccall f_2688r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
if(C_truep((C_word)C_vemptyp(t2))){
C_trace("ChickenBridge.scm: 135  tb:rangamma");
f_1956(t1,C_fix(1));}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
C_trace("ChickenBridge.scm: 135  tb:rangamma");
f_1956(t1,t3);}}

/* ranpoisson in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2669(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2rv,(void*)f_2669r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_2669r(t0,t1,t2);}}

static void C_ccall f_2669r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
if(C_truep((C_word)C_i_nullp(C_retrieve(lf[96])))){
C_trace("ChickenBridge.scm: 135  tb:ranpoisson");
f_1966(t1,C_fix(1));}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
C_trace("ChickenBridge.scm: 135  tb:ranpoisson");
f_1966(t1,t3);}}

/* rancauchy in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2663(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2663,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub138(t2));}

/* rangauss in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2623(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2r,(void*)f_2623r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_2623r(t0,t1,t2);}}

static void C_ccall f_2623r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 135  tb:rangauss");
f_1927(t1,C_fix(1),C_fix(0));}
else{
t3=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 135  tb:rangauss");
f_1927(t1,t4,C_fix(0));}
else{
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cdr(t2);
C_trace("ChickenBridge.scm: 135  tb:rangauss");
f_1927(t1,t4,t5);}}}

/* ranexp in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2604(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2rv,(void*)f_2604r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_2604r(t0,t1,t2);}}

static void C_ccall f_2604r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
if(C_truep((C_word)C_vemptyp(t2))){
C_trace("ChickenBridge.scm: 135  tb:ranexp");
f_1938(t1,C_fix(1));}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
C_trace("ChickenBridge.scm: 135  tb:ranexp");
f_1938(t1,t3);}}

/* ranbeta in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2560(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2r,(void*)f_2560r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_2560r(t0,t1,t2);}}

static void C_ccall f_2560r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 135  tb:ranbeta");
f_1945(t1,lf[86],lf[87]);}
else{
t3=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 135  tb:ranbeta");
f_1945(t1,t4,t5);}
else{
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cadr(t2);
C_trace("ChickenBridge.scm: 135  tb:ranbeta");
f_1945(t1,t4,t5);}}}

/* ranmiddle in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2554(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2554,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub111(t2));}

/* ranhigh in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2548(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2548,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub108(t2));}

/* ranlow in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2542(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2542,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub105(t2));}

/* pick in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2536(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2r,(void*)f_2536r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_2536r(t0,t1,t2);}}

static void C_ccall f_2536r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_trace("ChickenBridge.scm: 135  pickl");
t3=*((C_word*)lf[74]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,t2);}

/* pickl in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2513(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2513,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 135  error");
t3=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t1,lf[75],t2);}
else{
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2530,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
t4=(C_word)C_i_length(t2);
C_trace("ChickenBridge.scm: 135  tb:rani");
f_1882(t3,t4);}}

/* k2528 in pickl in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2530(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_i_list_ref(((C_word*)t0)[2],t1));}

/* odds in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2455(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+14)){
C_save_and_reclaim((void*)tr3r,(void*)f_2455r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_2455r(t0,t1,t2,t3);}}

static void C_ccall f_2455r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word *a=C_alloc(14);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2472,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 135  tb:ranf");
f_1889(t4,lf[70]);}
else{
t4=(C_word)C_i_cdr(t3);
if(C_truep((C_word)C_i_nullp(t4))){
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2491,a[2]=t3,a[3]=t1,a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 135  tb:ranf");
f_1889(t5,lf[71]);}
else{
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2507,a[2]=t3,a[3]=t1,a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 135  tb:ranf");
f_1889(t5,lf[72]);}}}

/* k2505 in odds in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2507(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_lessp(t1,((C_word*)t0)[4]);
t3=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_truep(t2)?(C_word)C_i_car(((C_word*)t0)[2]):(C_word)C_i_cadr(((C_word*)t0)[2])));}

/* k2489 in odds in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2491(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_lessp(t1,((C_word*)t0)[4]);
t3=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_truep(t2)?(C_word)C_i_car(((C_word*)t0)[2]):C_SCHEME_FALSE));}

/* k2470 in odds in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2472(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_lessp(t1,((C_word*)t0)[3]);
t3=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_truep(t2)?C_SCHEME_TRUE:C_SCHEME_FALSE));}

/* ran in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2367(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+4)){
C_save_and_reclaim((void*)tr2r,(void*)f_2367r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_2367r(t0,t1,t2);}}

static void C_ccall f_2367r(C_word t0,C_word t1,C_word t2){
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
C_trace("ChickenBridge.scm: 135  tb:ranf");
f_1889(t1,lf[67]);}
else{
t3=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_fixnump(t4))){
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 135  tb:rani");
f_1882(t1,t5);}
else{
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 135  tb:ranf");
f_1889(t1,t5);}}
else{
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2413,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_fixnump(t5))){
t6=(C_word)C_i_cadr(t2);
t7=t4;
f_2413(t7,(C_word)C_fixnump(t6));}
else{
t6=t4;
f_2413(t6,C_SCHEME_FALSE);}}}}

/* k2411 in ran in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_2413(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_2413,NULL,2,t0,t1);}
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

/* ran-set! in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2361(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2361,3,t0,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub80(C_SCHEME_UNDEFINED,t2));}

/* steps in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2302(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+12)){
C_save_and_reclaim((void*)tr4rv,(void*)f_2302r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest_vector(a,C_rest_count(0));
f_2302r(t0,t1,t2,t3,t4);}}

static void C_ccall f_2302r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
t9=C_set_block_item(t8,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_2315,a[2]=t5,a[3]=t8,a[4]=t4,a[5]=t2,a[6]=lf[62],tmp=(C_word)a,a+=7,tmp));
t10=((C_word*)t8)[1];
f_2315(t10,t1,C_fix(0),t3,t6,t5);}

/* do216 in steps in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_2315(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
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
C_save_and_reclaim((void*)trf_2315,NULL,6,t0,t1,t2,t3,t4,t5);}
t6=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
if(C_truep((C_word)C_i_lessp(t2,((C_word*)t0)[5]))){
t8=(C_word)C_a_i_list(&a,1,((C_word*)t6)[1]);
t9=(C_word)C_i_set_cdr(((C_word*)t7)[1],t8);
t10=(C_word)C_i_cdr(((C_word*)t7)[1]);
t11=C_set_block_item(t7,0,t10);
t12=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_2351,a[2]=t7,a[3]=t4,a[4]=t1,a[5]=((C_word*)t0)[3],a[6]=t2,a[7]=t6,a[8]=((C_word*)t0)[4],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 135  modulo");
t13=*((C_word*)lf[61]+1);
((C_proc4)C_retrieve_proc(t13))(4,t13,t12,t2,t4);}
else{
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,(C_word)C_i_cdr(((C_word*)t0)[2]));}}

/* k2349 in do216 in steps in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2351(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2351,2,t0,t1);}
t2=(C_word)C_i_vector_ref(((C_word*)t0)[8],t1);
t3=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[7])[1],t2);
t4=C_mutate(((C_word *)((C_word*)t0)[7])+1,t3);
t5=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[6],C_fix(1));
t6=((C_word*)((C_word*)t0)[5])[1];
f_2315(t6,((C_word*)t0)[4],t5,((C_word*)((C_word*)t0)[7])[1],((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1]);}

/* interp in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2296(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr3r,(void*)f_2296r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_2296r(t0,t1,t2,t3);}}

static void C_ccall f_2296r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_trace("ChickenBridge.scm: 135  interpl");
t4=*((C_word*)lf[50]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t1,t2,t3);}

/* interpl in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2201(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+6)){
C_save_and_reclaim((void*)tr4rv,(void*)f_2201r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest_vector(a,C_rest_count(0));
f_2201r(t0,t1,t2,t3,t4);}}

static void C_ccall f_2201r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word *a=C_alloc(6);
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_2205,a[2]=t1,a[3]=t2,a[4]=t3,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("ChickenBridge.scm: 135  error");
t6=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t5,lf[56],t3);}
else{
t6=t5;
f_2205(2,t6,(C_word)C_i_car(t3));}}

/* k2203 in interpl in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2205(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2205,2,t0,t1);}
t2=t1;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_2208,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=t3,tmp=(C_word)a,a+=7,tmp);
t5=(C_word)C_i_cdr(((C_word*)t0)[4]);
if(C_truep((C_word)C_i_nullp(t5))){
C_trace("ChickenBridge.scm: 135  err");
t6=C_retrieve(lf[54]);
((C_proc4)C_retrieve_proc(t6))(4,t6,t4,lf[55],((C_word*)t0)[4]);}
else{
t6=t4;
f_2208(2,t6,(C_word)C_i_cadr(((C_word*)t0)[4]));}}

/* k2206 in k2203 in interpl in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2208(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2208,2,t0,t1);}
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
t13=C_set_block_item(t12,0,(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_2220,a[2]=((C_word*)t0)[4],a[3]=t12,a[4]=t9,a[5]=t7,a[6]=t3,a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[3],a[9]=t5,a[10]=lf[53],tmp=(C_word)a,a+=11,tmp));
t14=((C_word*)t12)[1];
f_2220(t14,((C_word*)t0)[2],t10);}

/* do200 in k2206 in k2203 in interpl in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_2220(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_2220,NULL,3,t0,t1,t2);}
t3=(C_word)C_i_nullp(t2);
t4=(C_truep(t3)?t3:(C_word)C_i_greaterp(((C_word*)((C_word*)t0)[9])[1],((C_word*)t0)[8]));
if(C_truep(t4)){
C_trace("ChickenBridge.scm: 135  tb:rescale");
f_1746(t1,((C_word*)t0)[8],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[9])[1],((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[4]);}
else{
t5=C_mutate(((C_word *)((C_word*)t0)[7])+1,((C_word*)((C_word*)t0)[9])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[6])+1,((C_word*)((C_word*)t0)[5])[1]);
t7=(C_word)C_i_car(t2);
t8=C_mutate(((C_word *)((C_word*)t0)[9])+1,t7);
t9=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2242,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t10=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t10))){
C_trace("ChickenBridge.scm: 135  error");
t11=*((C_word*)lf[51]+1);
((C_proc4)C_retrieve_proc(t11))(4,t11,t9,lf[52],((C_word*)t0)[2]);}
else{
t11=(C_word)C_i_cadr(t2);
t12=C_mutate(((C_word *)((C_word*)t0)[5])+1,t11);
t13=t9;
f_2242(2,t13,t12);}}}

/* k2240 in do200 in k2206 in k2203 in interpl in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2242(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cddr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_2220(t3,((C_word*)t0)[2],t2);}

/* hertz->keynum in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2195(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2195,3,t0,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub75(t3,t4));}

/* keynum->pc in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2189(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2189,3,t0,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub71(C_SCHEME_UNDEFINED,t3));}

/* keynum->hertz in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2183(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2183,3,t0,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub66(t3,t4));}

/* scaler->cents in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2177(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2177,3,t0,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub62(C_SCHEME_UNDEFINED,t3));}

/* cents->scaler in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2171(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2171,3,t0,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_fixnum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub57(t3,t4));}

/* rhythm->seconds in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2111(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+12)){
C_save_and_reclaim((void*)tr3r,(void*)f_2111r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_2111r(t0,t1,t2,t3);}}

static void C_ccall f_2111r(C_word t0,C_word t1,C_word t2,C_word t3){
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
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2113,a[2]=t2,a[3]=lf[33],tmp=(C_word)a,a+=4,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2118,a[2]=t4,a[3]=lf[35],tmp=(C_word)a,a+=4,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2123,a[2]=t5,a[3]=lf[37],tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("def-tempo173181");
t7=t6;
f_2123(t7,t1);}
else{
t7=(C_word)C_i_car(t3);
t8=(C_word)C_i_cdr(t3);
if(C_truep((C_word)C_i_nullp(t8))){
C_trace("def-beat174179");
t9=t5;
f_2118(t9,t1,t7);}
else{
t9=(C_word)C_i_car(t8);
t10=(C_word)C_i_cdr(t8);
if(C_truep((C_word)C_i_nullp(t10))){
C_trace("body171176");
t11=t4;
f_2113(t11,t1,t7,t9);}
else{
C_trace("##sys#error");
t11=*((C_word*)lf[38]+1);
((C_proc4)(void*)(*((C_word*)t11+1)))(4,t11,t1,lf[0],t10);}}}}

/* def-tempo173 in rhythm->seconds in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_2123(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2123,NULL,2,t0,t1);}
C_trace("def-beat174179");
t2=((C_word*)t0)[2];
f_2118(t2,t1,lf[36]);}

/* def-beat174 in rhythm->seconds in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_2118(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2118,NULL,3,t0,t1,t2);}
C_trace("body171176");
t3=((C_word*)t0)[2];
f_2113(t3,t1,t2,lf[34]);}

/* body171 in rhythm->seconds in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_2113(C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)trf_2113,NULL,4,t0,t1,t2,t3);}
t4=((C_word*)t0)[2];
t5=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t6=(C_word)C_i_foreign_flonum_argumentp(t4);
t7=(C_word)C_i_foreign_flonum_argumentp(t2);
t8=(C_word)C_i_foreign_flonum_argumentp(t3);
t9=t1;
((C_proc2)(void*)(*((C_word*)t9+1)))(2,t9,(C_word)stub50(t5,t6,t7,t8));}

/* decimals in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2092(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr3rv,(void*)f_2092r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest_vector(a,C_rest_count(0));
f_2092r(t0,t1,t2,t3);}}

static void C_ccall f_2092r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
if(C_truep((C_word)C_vemptyp(t3))){
C_trace("ChickenBridge.scm: 135  tb:decimals");
f_1807(t1,t2,C_fix(3));}
else{
t4=(C_word)C_i_vector_ref(t3,C_fix(0));
C_trace("ChickenBridge.scm: 135  tb:decimals");
f_1807(t1,t2,t4);}}

/* quantize in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2086(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_2086,4,t0,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_flonum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub42(t4,t5,t6));}

/* int in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2080(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2080,3,t0,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub30(C_SCHEME_UNDEFINED,t3));}

/* discrete in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_1998(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,...){
C_word tmp;
C_word t6;
va_list v;
C_word *a,c2=c;
C_save_rest(t5,c2,6);
if(c<6) C_bad_min_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+4)){
C_save_and_reclaim((void*)tr6r,(void*)f_1998r,6,t0,t1,t2,t3,t4,t5);}
else{
a=C_alloc((c-6)*3);
t6=C_restore_rest(a,C_rest_count(0));
f_1998r(t0,t1,t2,t3,t4,t5,t6);}}

static void C_ccall f_1998r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
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
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2012,a[2]=t5,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_nullp(t6))){
t8=(C_word)C_i_length(t5);
C_trace("ChickenBridge.scm: 135  tb:discrete");
f_1773(t7,t2,t3,t4,C_fix(0),t8,C_fix(1));}
else{
t8=(C_word)C_i_cdr(t6);
if(C_truep((C_word)C_i_nullp(t8))){
t9=(C_word)C_i_car(t6);
C_trace("ChickenBridge.scm: 135  tb:discrete");
f_1773(t7,t2,t3,t4,C_fix(0),t9,C_fix(1));}
else{
t9=(C_word)C_i_car(t6);
t10=(C_word)C_i_cadr(t6);
C_trace("ChickenBridge.scm: 135  tb:discrete");
f_1773(t7,t2,t3,t4,C_fix(0),t9,t10);}}}
else{
t7=(C_word)C_i_cdr(t6);
if(C_truep((C_word)C_i_nullp(t7))){
t8=(C_word)C_i_car(t6);
C_trace("ChickenBridge.scm: 135  tb:discrete");
f_1773(t1,t2,t3,t4,t5,t8,C_fix(1));}
else{
t8=(C_word)C_i_car(t6);
t9=(C_word)C_i_cadr(t6);
C_trace("ChickenBridge.scm: 135  tb:discrete");
f_1773(t1,t2,t3,t4,t5,t8,t9);}}}

/* k2010 in discrete in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_2012(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_i_list_ref(((C_word*)t0)[2],t1));}

/* rescale in k1742 in k1739 in k1736 in k1733 */
static void C_ccall f_1979(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,...){
C_word tmp;
C_word t7;
va_list v;
C_word *a,c2=c;
C_save_rest(t6,c2,7);
if(c<7) C_bad_min_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr7rv,(void*)f_1979r,7,t0,t1,t2,t3,t4,t5,t6);}
else{
a=C_alloc((c-7)*3);
t7=C_restore_rest_vector(a,C_rest_count(0));
f_1979r(t0,t1,t2,t3,t4,t5,t6,t7);}}

static void C_ccall f_1979r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
C_word tmp;
C_word t8;
C_word t9;
if(C_truep((C_word)C_vemptyp(t7))){
C_trace("ChickenBridge.scm: 135  tb:rescale");
f_1746(t1,t2,t3,t4,t5,t6,C_fix(1));}
else{
t8=(C_word)C_i_vector_ref(t7,C_fix(0));
C_trace("ChickenBridge.scm: 135  tb:rescale");
f_1746(t1,t2,t3,t4,t5,t6,t8);}}

/* tb:ranpoisson in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_1966(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1966,NULL,2,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub142(C_SCHEME_UNDEFINED,t3));}

/* tb:rangamma in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_1956(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1956,NULL,2,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub134(t3,t4));}

/* tb:ranbeta in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_1945(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1945,NULL,3,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_flonum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub128(t4,t5,t6));}

/* tb:ranexp in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_1938(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1938,NULL,2,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub122(t3,t4));}

/* tb:rangauss in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_1927(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1927,NULL,3,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_flonum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub116(t4,t5,t6));}

/* tb:ranf in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_1889(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1889,NULL,2,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub88(t3,t4));}

/* tb:rani in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_1882(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1882,NULL,2,t1,t2);}
t3=(C_word)C_i_foreign_fixnum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub84(C_SCHEME_UNDEFINED,t3));}

/* tb:decimals in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_1807(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1807,NULL,3,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_fixnum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub35(t4,t5,t6));}

/* tb:discrete in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_1773(C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
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
C_save_and_reclaim((void*)trf_1773,NULL,7,t1,t2,t3,t4,t5,t6,t7);}
t8=(C_word)C_i_foreign_flonum_argumentp(t2);
t9=(C_word)C_i_foreign_flonum_argumentp(t3);
t10=(C_word)C_i_foreign_flonum_argumentp(t4);
t11=(C_word)C_i_foreign_fixnum_argumentp(t5);
t12=(C_word)C_i_foreign_fixnum_argumentp(t6);
t13=(C_word)C_i_foreign_flonum_argumentp(t7);
t14=t1;
((C_proc2)(void*)(*((C_word*)t14+1)))(2,t14,(C_word)stub21(C_SCHEME_UNDEFINED,t8,t9,t10,t11,t12,t13));}

/* tb:rescale in k1742 in k1739 in k1736 in k1733 */
static void C_fcall f_1746(C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
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
C_save_and_reclaim((void*)trf_1746,NULL,7,t1,t2,t3,t4,t5,t6,t7);}
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
{"f_1735ChickenBridge.scm",(void*)f_1735},
{"f_1738ChickenBridge.scm",(void*)f_1738},
{"f_1741ChickenBridge.scm",(void*)f_1741},
{"f_1744ChickenBridge.scm",(void*)f_1744},
{"f_12096ChickenBridge.scm",(void*)f_12096},
{"f_12104ChickenBridge.scm",(void*)f_12104},
{"f_12108ChickenBridge.scm",(void*)f_12108},
{"f_2786ChickenBridge.scm",(void*)f_2786},
{"f_2837ChickenBridge.scm",(void*)f_2837},
{"f_12086ChickenBridge.scm",(void*)f_12086},
{"f_12094ChickenBridge.scm",(void*)f_12094},
{"f_2942ChickenBridge.scm",(void*)f_2942},
{"f_12072ChickenBridge.scm",(void*)f_12072},
{"f_12080ChickenBridge.scm",(void*)f_12080},
{"f_12084ChickenBridge.scm",(void*)f_12084},
{"f_3135ChickenBridge.scm",(void*)f_3135},
{"f_12046ChickenBridge.scm",(void*)f_12046},
{"f_12050ChickenBridge.scm",(void*)f_12050},
{"f_12056ChickenBridge.scm",(void*)f_12056},
{"f_12067ChickenBridge.scm",(void*)f_12067},
{"f_12063ChickenBridge.scm",(void*)f_12063},
{"f_3204ChickenBridge.scm",(void*)f_3204},
{"f_12024ChickenBridge.scm",(void*)f_12024},
{"f_4449ChickenBridge.scm",(void*)f_4449},
{"f_12004ChickenBridge.scm",(void*)f_12004},
{"f_4452ChickenBridge.scm",(void*)f_4452},
{"f_11964ChickenBridge.scm",(void*)f_11964},
{"f_4455ChickenBridge.scm",(void*)f_4455},
{"f_11870ChickenBridge.scm",(void*)f_11870},
{"f_11874ChickenBridge.scm",(void*)f_11874},
{"f_11877ChickenBridge.scm",(void*)f_11877},
{"f_11895ChickenBridge.scm",(void*)f_11895},
{"f_11898ChickenBridge.scm",(void*)f_11898},
{"f_11929ChickenBridge.scm",(void*)f_11929},
{"f_11901ChickenBridge.scm",(void*)f_11901},
{"f_11907ChickenBridge.scm",(void*)f_11907},
{"f_11860ChickenBridge.scm",(void*)f_11860},
{"f_11854ChickenBridge.scm",(void*)f_11854},
{"f_4458ChickenBridge.scm",(void*)f_4458},
{"f_11762ChickenBridge.scm",(void*)f_11762},
{"f_11764ChickenBridge.scm",(void*)f_11764},
{"f_11768ChickenBridge.scm",(void*)f_11768},
{"f_11771ChickenBridge.scm",(void*)f_11771},
{"f_11774ChickenBridge.scm",(void*)f_11774},
{"f_11814ChickenBridge.scm",(void*)f_11814},
{"f_11806ChickenBridge.scm",(void*)f_11806},
{"f_11777ChickenBridge.scm",(void*)f_11777},
{"f_11780ChickenBridge.scm",(void*)f_11780},
{"f_11783ChickenBridge.scm",(void*)f_11783},
{"f_11754ChickenBridge.scm",(void*)f_11754},
{"f_4461ChickenBridge.scm",(void*)f_4461},
{"f_11726ChickenBridge.scm",(void*)f_11726},
{"f_4464ChickenBridge.scm",(void*)f_4464},
{"f_11690ChickenBridge.scm",(void*)f_11690},
{"f_11702ChickenBridge.scm",(void*)f_11702},
{"f_11698ChickenBridge.scm",(void*)f_11698},
{"f_11672ChickenBridge.scm",(void*)f_11672},
{"f_11666ChickenBridge.scm",(void*)f_11666},
{"f_4467ChickenBridge.scm",(void*)f_4467},
{"f_11580ChickenBridge.scm",(void*)f_11580},
{"f_11584ChickenBridge.scm",(void*)f_11584},
{"f_11587ChickenBridge.scm",(void*)f_11587},
{"f_11590ChickenBridge.scm",(void*)f_11590},
{"f_11603ChickenBridge.scm",(void*)f_11603},
{"f_11549ChickenBridge.scm",(void*)f_11549},
{"f_11553ChickenBridge.scm",(void*)f_11553},
{"f_11568ChickenBridge.scm",(void*)f_11568},
{"f_11543ChickenBridge.scm",(void*)f_11543},
{"f_4470ChickenBridge.scm",(void*)f_4470},
{"f_11429ChickenBridge.scm",(void*)f_11429},
{"f_11445ChickenBridge.scm",(void*)f_11445},
{"f_11456ChickenBridge.scm",(void*)f_11456},
{"f_11423ChickenBridge.scm",(void*)f_11423},
{"f_4526ChickenBridge.scm",(void*)f_4526},
{"f_11290ChickenBridge.scm",(void*)f_11290},
{"f_11313ChickenBridge.scm",(void*)f_11313},
{"f_11310ChickenBridge.scm",(void*)f_11310},
{"f_11284ChickenBridge.scm",(void*)f_11284},
{"f_4529ChickenBridge.scm",(void*)f_4529},
{"f_11138ChickenBridge.scm",(void*)f_11138},
{"f_11156ChickenBridge.scm",(void*)f_11156},
{"f_11165ChickenBridge.scm",(void*)f_11165},
{"f_11132ChickenBridge.scm",(void*)f_11132},
{"f_4532ChickenBridge.scm",(void*)f_4532},
{"f_11085ChickenBridge.scm",(void*)f_11085},
{"f_11089ChickenBridge.scm",(void*)f_11089},
{"f_11092ChickenBridge.scm",(void*)f_11092},
{"f_11108ChickenBridge.scm",(void*)f_11108},
{"f_11067ChickenBridge.scm",(void*)f_11067},
{"f_11061ChickenBridge.scm",(void*)f_11061},
{"f_4535ChickenBridge.scm",(void*)f_4535},
{"f_10985ChickenBridge.scm",(void*)f_10985},
{"f_4674ChickenBridge.scm",(void*)f_4674},
{"f_10911ChickenBridge.scm",(void*)f_10911},
{"f_10918ChickenBridge.scm",(void*)f_10918},
{"f_10905ChickenBridge.scm",(void*)f_10905},
{"f_4677ChickenBridge.scm",(void*)f_4677},
{"f_10801ChickenBridge.scm",(void*)f_10801},
{"f_10809ChickenBridge.scm",(void*)f_10809},
{"f_10775ChickenBridge.scm",(void*)f_10775},
{"f_10792ChickenBridge.scm",(void*)f_10792},
{"f_10783ChickenBridge.scm",(void*)f_10783},
{"f_10769ChickenBridge.scm",(void*)f_10769},
{"f_4680ChickenBridge.scm",(void*)f_4680},
{"f_10725ChickenBridge.scm",(void*)f_10725},
{"f_4683ChickenBridge.scm",(void*)f_4683},
{"f_10643ChickenBridge.scm",(void*)f_10643},
{"f_10654ChickenBridge.scm",(void*)f_10654},
{"f_10656ChickenBridge.scm",(void*)f_10656},
{"f_10685ChickenBridge.scm",(void*)f_10685},
{"f_10621ChickenBridge.scm",(void*)f_10621},
{"f_10637ChickenBridge.scm",(void*)f_10637},
{"f_10615ChickenBridge.scm",(void*)f_10615},
{"f_4686ChickenBridge.scm",(void*)f_4686},
{"f_10539ChickenBridge.scm",(void*)f_10539},
{"f_10543ChickenBridge.scm",(void*)f_10543},
{"f_10575ChickenBridge.scm",(void*)f_10575},
{"f_10556ChickenBridge.scm",(void*)f_10556},
{"f_10560ChickenBridge.scm",(void*)f_10560},
{"f_10512ChickenBridge.scm",(void*)f_10512},
{"f_10516ChickenBridge.scm",(void*)f_10516},
{"f_10506ChickenBridge.scm",(void*)f_10506},
{"f_4689ChickenBridge.scm",(void*)f_4689},
{"f_10374ChickenBridge.scm",(void*)f_10374},
{"f_10414ChickenBridge.scm",(void*)f_10414},
{"f_10378ChickenBridge.scm",(void*)f_10378},
{"f_10394ChickenBridge.scm",(void*)f_10394},
{"f_10406ChickenBridge.scm",(void*)f_10406},
{"f_10410ChickenBridge.scm",(void*)f_10410},
{"f_10402ChickenBridge.scm",(void*)f_10402},
{"f_10313ChickenBridge.scm",(void*)f_10313},
{"f_10360ChickenBridge.scm",(void*)f_10360},
{"f_10320ChickenBridge.scm",(void*)f_10320},
{"f_10331ChickenBridge.scm",(void*)f_10331},
{"f_10307ChickenBridge.scm",(void*)f_10307},
{"f_4692ChickenBridge.scm",(void*)f_4692},
{"f_10287ChickenBridge.scm",(void*)f_10287},
{"f_10281ChickenBridge.scm",(void*)f_10281},
{"f_4695ChickenBridge.scm",(void*)f_4695},
{"f_10261ChickenBridge.scm",(void*)f_10261},
{"f_10265ChickenBridge.scm",(void*)f_10265},
{"f_10253ChickenBridge.scm",(void*)f_10253},
{"f_4698ChickenBridge.scm",(void*)f_4698},
{"f_10233ChickenBridge.scm",(void*)f_10233},
{"f_10237ChickenBridge.scm",(void*)f_10237},
{"f_10225ChickenBridge.scm",(void*)f_10225},
{"f_4701ChickenBridge.scm",(void*)f_4701},
{"f_10205ChickenBridge.scm",(void*)f_10205},
{"f_10209ChickenBridge.scm",(void*)f_10209},
{"f_10197ChickenBridge.scm",(void*)f_10197},
{"f_4704ChickenBridge.scm",(void*)f_4704},
{"f_10177ChickenBridge.scm",(void*)f_10177},
{"f_10181ChickenBridge.scm",(void*)f_10181},
{"f_10169ChickenBridge.scm",(void*)f_10169},
{"f_4707ChickenBridge.scm",(void*)f_4707},
{"f_10068ChickenBridge.scm",(void*)f_10068},
{"f_10038ChickenBridge.scm",(void*)f_10038},
{"f_10062ChickenBridge.scm",(void*)f_10062},
{"f_10032ChickenBridge.scm",(void*)f_10032},
{"f_4710ChickenBridge.scm",(void*)f_4710},
{"f_9982ChickenBridge.scm",(void*)f_9982},
{"f_9984ChickenBridge.scm",(void*)f_9984},
{"f_9988ChickenBridge.scm",(void*)f_9988},
{"f_10016ChickenBridge.scm",(void*)f_10016},
{"f_10008ChickenBridge.scm",(void*)f_10008},
{"f_10004ChickenBridge.scm",(void*)f_10004},
{"f_9991ChickenBridge.scm",(void*)f_9991},
{"f_9974ChickenBridge.scm",(void*)f_9974},
{"f_4713ChickenBridge.scm",(void*)f_4713},
{"f_9921ChickenBridge.scm",(void*)f_9921},
{"f_9923ChickenBridge.scm",(void*)f_9923},
{"f_9927ChickenBridge.scm",(void*)f_9927},
{"f_9958ChickenBridge.scm",(void*)f_9958},
{"f_9950ChickenBridge.scm",(void*)f_9950},
{"f_9946ChickenBridge.scm",(void*)f_9946},
{"f_9930ChickenBridge.scm",(void*)f_9930},
{"f_9933ChickenBridge.scm",(void*)f_9933},
{"f_9913ChickenBridge.scm",(void*)f_9913},
{"f_4716ChickenBridge.scm",(void*)f_4716},
{"f_9863ChickenBridge.scm",(void*)f_9863},
{"f_9877ChickenBridge.scm",(void*)f_9877},
{"f_9869ChickenBridge.scm",(void*)f_9869},
{"f_9828ChickenBridge.scm",(void*)f_9828},
{"f_9861ChickenBridge.scm",(void*)f_9861},
{"f_9822ChickenBridge.scm",(void*)f_9822},
{"f_4719ChickenBridge.scm",(void*)f_4719},
{"f_9769ChickenBridge.scm",(void*)f_9769},
{"f_9773ChickenBridge.scm",(void*)f_9773},
{"f_9786ChickenBridge.scm",(void*)f_9786},
{"f_9778ChickenBridge.scm",(void*)f_9778},
{"f_9726ChickenBridge.scm",(void*)f_9726},
{"f_9759ChickenBridge.scm",(void*)f_9759},
{"f_9720ChickenBridge.scm",(void*)f_9720},
{"f_4722ChickenBridge.scm",(void*)f_4722},
{"f_9640ChickenBridge.scm",(void*)f_9640},
{"f_9634ChickenBridge.scm",(void*)f_9634},
{"f_4725ChickenBridge.scm",(void*)f_4725},
{"f_9403ChickenBridge.scm",(void*)f_9403},
{"f_9407ChickenBridge.scm",(void*)f_9407},
{"f_9415ChickenBridge.scm",(void*)f_9415},
{"f_9438ChickenBridge.scm",(void*)f_9438},
{"f_9441ChickenBridge.scm",(void*)f_9441},
{"f_9444ChickenBridge.scm",(void*)f_9444},
{"f_9447ChickenBridge.scm",(void*)f_9447},
{"f_9507ChickenBridge.scm",(void*)f_9507},
{"f_9514ChickenBridge.scm",(void*)f_9514},
{"f_9524ChickenBridge.scm",(void*)f_9524},
{"f_9534ChickenBridge.scm",(void*)f_9534},
{"f_9548ChickenBridge.scm",(void*)f_9548},
{"f_9558ChickenBridge.scm",(void*)f_9558},
{"f_9568ChickenBridge.scm",(void*)f_9568},
{"f_9578ChickenBridge.scm",(void*)f_9578},
{"f_9450ChickenBridge.scm",(void*)f_9450},
{"f_9474ChickenBridge.scm",(void*)f_9474},
{"f_9453ChickenBridge.scm",(void*)f_9453},
{"f_9360ChickenBridge.scm",(void*)f_9360},
{"f_9393ChickenBridge.scm",(void*)f_9393},
{"f_9354ChickenBridge.scm",(void*)f_9354},
{"f_4728ChickenBridge.scm",(void*)f_4728},
{"f_9272ChickenBridge.scm",(void*)f_9272},
{"f_9276ChickenBridge.scm",(void*)f_9276},
{"f_9282ChickenBridge.scm",(void*)f_9282},
{"f_9302ChickenBridge.scm",(void*)f_9302},
{"f_9246ChickenBridge.scm",(void*)f_9246},
{"f_9256ChickenBridge.scm",(void*)f_9256},
{"f_9240ChickenBridge.scm",(void*)f_9240},
{"f_4731ChickenBridge.scm",(void*)f_4731},
{"f_9117ChickenBridge.scm",(void*)f_9117},
{"f_9121ChickenBridge.scm",(void*)f_9121},
{"f_9049ChickenBridge.scm",(void*)f_9049},
{"f_9068ChickenBridge.scm",(void*)f_9068},
{"f_9103ChickenBridge.scm",(void*)f_9103},
{"f_9074ChickenBridge.scm",(void*)f_9074},
{"f_9078ChickenBridge.scm",(void*)f_9078},
{"f_9092ChickenBridge.scm",(void*)f_9092},
{"f_9081ChickenBridge.scm",(void*)f_9081},
{"f_9062ChickenBridge.scm",(void*)f_9062},
{"f_9043ChickenBridge.scm",(void*)f_9043},
{"f_4734ChickenBridge.scm",(void*)f_4734},
{"f_8771ChickenBridge.scm",(void*)f_8771},
{"f_5257ChickenBridge.scm",(void*)f_5257},
{"f_8723ChickenBridge.scm",(void*)f_8723},
{"f_8715ChickenBridge.scm",(void*)f_8715},
{"f_5260ChickenBridge.scm",(void*)f_5260},
{"f_8595ChickenBridge.scm",(void*)f_8595},
{"f_5266ChickenBridge.scm",(void*)f_5266},
{"f_5738ChickenBridge.scm",(void*)f_5738},
{"f_5772ChickenBridge.scm",(void*)f_5772},
{"f_5764ChickenBridge.scm",(void*)f_5764},
{"f_5760ChickenBridge.scm",(void*)f_5760},
{"f_5745ChickenBridge.scm",(void*)f_5745},
{"f_5749ChickenBridge.scm",(void*)f_5749},
{"f_5742ChickenBridge.scm",(void*)f_5742},
{"f_5284ChickenBridge.scm",(void*)f_5284},
{"f_5731ChickenBridge.scm",(void*)f_5731},
{"f_5727ChickenBridge.scm",(void*)f_5727},
{"f_5291ChickenBridge.scm",(void*)f_5291},
{"f_5602ChickenBridge.scm",(void*)f_5602},
{"f_5623ChickenBridge.scm",(void*)f_5623},
{"f_5625ChickenBridge.scm",(void*)f_5625},
{"f_5639ChickenBridge.scm",(void*)f_5639},
{"f_5692ChickenBridge.scm",(void*)f_5692},
{"f_5642ChickenBridge.scm",(void*)f_5642},
{"f_5677ChickenBridge.scm",(void*)f_5677},
{"f_5645ChickenBridge.scm",(void*)f_5645},
{"f_5658ChickenBridge.scm",(void*)f_5658},
{"f_5670ChickenBridge.scm",(void*)f_5670},
{"f_5662ChickenBridge.scm",(void*)f_5662},
{"f_5648ChickenBridge.scm",(void*)f_5648},
{"f_5612ChickenBridge.scm",(void*)f_5612},
{"f_5294ChickenBridge.scm",(void*)f_5294},
{"f_5566ChickenBridge.scm",(void*)f_5566},
{"f_5592ChickenBridge.scm",(void*)f_5592},
{"f_5577ChickenBridge.scm",(void*)f_5577},
{"f_5297ChickenBridge.scm",(void*)f_5297},
{"f_5301ChickenBridge.scm",(void*)f_5301},
{"f_5510ChickenBridge.scm",(void*)f_5510},
{"f_5520ChickenBridge.scm",(void*)f_5520},
{"f_5523ChickenBridge.scm",(void*)f_5523},
{"f_5544ChickenBridge.scm",(void*)f_5544},
{"f_5526ChickenBridge.scm",(void*)f_5526},
{"f_5530ChickenBridge.scm",(void*)f_5530},
{"f_5304ChickenBridge.scm",(void*)f_5304},
{"f_5307ChickenBridge.scm",(void*)f_5307},
{"f_5473ChickenBridge.scm",(void*)f_5473},
{"f_5481ChickenBridge.scm",(void*)f_5481},
{"f_5477ChickenBridge.scm",(void*)f_5477},
{"f_5310ChickenBridge.scm",(void*)f_5310},
{"f_5338ChickenBridge.scm",(void*)f_5338},
{"f_5341ChickenBridge.scm",(void*)f_5341},
{"f_5344ChickenBridge.scm",(void*)f_5344},
{"f_5347ChickenBridge.scm",(void*)f_5347},
{"f_5406ChickenBridge.scm",(void*)f_5406},
{"f_8549ChickenBridge.scm",(void*)f_8549},
{"f_8565ChickenBridge.scm",(void*)f_8565},
{"f_8568ChickenBridge.scm",(void*)f_8568},
{"f_8571ChickenBridge.scm",(void*)f_8571},
{"f_8574ChickenBridge.scm",(void*)f_8574},
{"f_8585ChickenBridge.scm",(void*)f_8585},
{"f_8543ChickenBridge.scm",(void*)f_8543},
{"f_5779ChickenBridge.scm",(void*)f_5779},
{"f_8404ChickenBridge.scm",(void*)f_8404},
{"f_8443ChickenBridge.scm",(void*)f_8443},
{"f_8417ChickenBridge.scm",(void*)f_8417},
{"f_8398ChickenBridge.scm",(void*)f_8398},
{"f_5782ChickenBridge.scm",(void*)f_5782},
{"f_7986ChickenBridge.scm",(void*)f_7986},
{"f_7990ChickenBridge.scm",(void*)f_7990},
{"f_8002ChickenBridge.scm",(void*)f_8002},
{"f_8060ChickenBridge.scm",(void*)f_8060},
{"f_8063ChickenBridge.scm",(void*)f_8063},
{"f_8066ChickenBridge.scm",(void*)f_8066},
{"f_8278ChickenBridge.scm",(void*)f_8278},
{"f_8216ChickenBridge.scm",(void*)f_8216},
{"f_8250ChickenBridge.scm",(void*)f_8250},
{"f_8225ChickenBridge.scm",(void*)f_8225},
{"f_8236ChickenBridge.scm",(void*)f_8236},
{"f_8232ChickenBridge.scm",(void*)f_8232},
{"f_8075ChickenBridge.scm",(void*)f_8075},
{"f_8153ChickenBridge.scm",(void*)f_8153},
{"f_8194ChickenBridge.scm",(void*)f_8194},
{"f_8198ChickenBridge.scm",(void*)f_8198},
{"f_8202ChickenBridge.scm",(void*)f_8202},
{"f_8157ChickenBridge.scm",(void*)f_8157},
{"f_8161ChickenBridge.scm",(void*)f_8161},
{"f_8188ChickenBridge.scm",(void*)f_8188},
{"f_8164ChickenBridge.scm",(void*)f_8164},
{"f_8078ChickenBridge.scm",(void*)f_8078},
{"f_8150ChickenBridge.scm",(void*)f_8150},
{"f_8092ChickenBridge.scm",(void*)f_8092},
{"f_8094ChickenBridge.scm",(void*)f_8094},
{"f_8142ChickenBridge.scm",(void*)f_8142},
{"f_8113ChickenBridge.scm",(void*)f_8113},
{"f_8130ChickenBridge.scm",(void*)f_8130},
{"f_8116ChickenBridge.scm",(void*)f_8116},
{"f_8109ChickenBridge.scm",(void*)f_8109},
{"f_8081ChickenBridge.scm",(void*)f_8081},
{"f_8011ChickenBridge.scm",(void*)f_8011},
{"f_8021ChickenBridge.scm",(void*)f_8021},
{"f_8027ChickenBridge.scm",(void*)f_8027},
{"f_7999ChickenBridge.scm",(void*)f_7999},
{"f_7947ChickenBridge.scm",(void*)f_7947},
{"f_7964ChickenBridge.scm",(void*)f_7964},
{"f_7980ChickenBridge.scm",(void*)f_7980},
{"f_7958ChickenBridge.scm",(void*)f_7958},
{"f_7941ChickenBridge.scm",(void*)f_7941},
{"f_5785ChickenBridge.scm",(void*)f_5785},
{"f_7865ChickenBridge.scm",(void*)f_7865},
{"f_5788ChickenBridge.scm",(void*)f_5788},
{"f_7841ChickenBridge.scm",(void*)f_7841},
{"f_7853ChickenBridge.scm",(void*)f_7853},
{"f_7849ChickenBridge.scm",(void*)f_7849},
{"f_7827ChickenBridge.scm",(void*)f_7827},
{"f_7835ChickenBridge.scm",(void*)f_7835},
{"f_7821ChickenBridge.scm",(void*)f_7821},
{"f_5791ChickenBridge.scm",(void*)f_5791},
{"f_6943ChickenBridge.scm",(void*)f_6943},
{"f_7767ChickenBridge.scm",(void*)f_7767},
{"f_7814ChickenBridge.scm",(void*)f_7814},
{"f_7804ChickenBridge.scm",(void*)f_7804},
{"f_7771ChickenBridge.scm",(void*)f_7771},
{"f_6946ChickenBridge.scm",(void*)f_6946},
{"f_7761ChickenBridge.scm",(void*)f_7761},
{"f_7219ChickenBridge.scm",(void*)f_7219},
{"f_7270ChickenBridge.scm",(void*)f_7270},
{"f_7273ChickenBridge.scm",(void*)f_7273},
{"f_7276ChickenBridge.scm",(void*)f_7276},
{"f_7279ChickenBridge.scm",(void*)f_7279},
{"f_7282ChickenBridge.scm",(void*)f_7282},
{"f_7285ChickenBridge.scm",(void*)f_7285},
{"f_7288ChickenBridge.scm",(void*)f_7288},
{"f_7291ChickenBridge.scm",(void*)f_7291},
{"f_7755ChickenBridge.scm",(void*)f_7755},
{"f_7309ChickenBridge.scm",(void*)f_7309},
{"f_7312ChickenBridge.scm",(void*)f_7312},
{"f_7590ChickenBridge.scm",(void*)f_7590},
{"f_7698ChickenBridge.scm",(void*)f_7698},
{"f_7610ChickenBridge.scm",(void*)f_7610},
{"f_7619ChickenBridge.scm",(void*)f_7619},
{"f_7623ChickenBridge.scm",(void*)f_7623},
{"f_7627ChickenBridge.scm",(void*)f_7627},
{"f_7635ChickenBridge.scm",(void*)f_7635},
{"f_7631ChickenBridge.scm",(void*)f_7631},
{"f_7600ChickenBridge.scm",(void*)f_7600},
{"f_7315ChickenBridge.scm",(void*)f_7315},
{"f_7318ChickenBridge.scm",(void*)f_7318},
{"f_7321ChickenBridge.scm",(void*)f_7321},
{"f_7324ChickenBridge.scm",(void*)f_7324},
{"f_7327ChickenBridge.scm",(void*)f_7327},
{"f_7584ChickenBridge.scm",(void*)f_7584},
{"f_7483ChickenBridge.scm",(void*)f_7483},
{"f_7490ChickenBridge.scm",(void*)f_7490},
{"f_7492ChickenBridge.scm",(void*)f_7492},
{"f_7564ChickenBridge.scm",(void*)f_7564},
{"f_7516ChickenBridge.scm",(void*)f_7516},
{"f_7519ChickenBridge.scm",(void*)f_7519},
{"f_7540ChickenBridge.scm",(void*)f_7540},
{"f_7506ChickenBridge.scm",(void*)f_7506},
{"f_7330ChickenBridge.scm",(void*)f_7330},
{"f_7472ChickenBridge.scm",(void*)f_7472},
{"f_7460ChickenBridge.scm",(void*)f_7460},
{"f_7456ChickenBridge.scm",(void*)f_7456},
{"f_7337ChickenBridge.scm",(void*)f_7337},
{"f_7294ChickenBridge.scm",(void*)f_7294},
{"f_7753ChickenBridge.scm",(void*)f_7753},
{"f_7263ChickenBridge.scm",(void*)f_7263},
{"f_7257ChickenBridge.scm",(void*)f_7257},
{"f_7251ChickenBridge.scm",(void*)f_7251},
{"f_7245ChickenBridge.scm",(void*)f_7245},
{"f_7239ChickenBridge.scm",(void*)f_7239},
{"f_7233ChickenBridge.scm",(void*)f_7233},
{"f_7227ChickenBridge.scm",(void*)f_7227},
{"f_7221ChickenBridge.scm",(void*)f_7221},
{"f_6485ChickenBridge.scm",(void*)f_6485},
{"f_6948ChickenBridge.scm",(void*)f_6948},
{"f_6958ChickenBridge.scm",(void*)f_6958},
{"f_7189ChickenBridge.scm",(void*)f_7189},
{"f_6961ChickenBridge.scm",(void*)f_6961},
{"f_6964ChickenBridge.scm",(void*)f_6964},
{"f_6976ChickenBridge.scm",(void*)f_6976},
{"f_7024ChickenBridge.scm",(void*)f_7024},
{"f_7040ChickenBridge.scm",(void*)f_7040},
{"f_7050ChickenBridge.scm",(void*)f_7050},
{"f_7167ChickenBridge.scm",(void*)f_7167},
{"f_7155ChickenBridge.scm",(void*)f_7155},
{"f_7153ChickenBridge.scm",(void*)f_7153},
{"f_7140ChickenBridge.scm",(void*)f_7140},
{"f_7094ChickenBridge.scm",(void*)f_7094},
{"f_7121ChickenBridge.scm",(void*)f_7121},
{"f_7100ChickenBridge.scm",(void*)f_7100},
{"f_7034ChickenBridge.scm",(void*)f_7034},
{"f_6979ChickenBridge.scm",(void*)f_6979},
{"f_6984ChickenBridge.scm",(void*)f_6984},
{"f_6997ChickenBridge.scm",(void*)f_6997},
{"f_7206ChickenBridge.scm",(void*)f_7206},
{"f_7197ChickenBridge.scm",(void*)f_7197},
{"f_7205ChickenBridge.scm",(void*)f_7205},
{"f_7208ChickenBridge.scm",(void*)f_7208},
{"f_7216ChickenBridge.scm",(void*)f_7216},
{"f_6932ChickenBridge.scm",(void*)f_6932},
{"f_6595ChickenBridge.scm",(void*)f_6595},
{"f_6936ChickenBridge.scm",(void*)f_6936},
{"f_6874ChickenBridge.scm",(void*)f_6874},
{"f_6892ChickenBridge.scm",(void*)f_6892},
{"f_6902ChickenBridge.scm",(void*)f_6902},
{"f_6878ChickenBridge.scm",(void*)f_6878},
{"f_6865ChickenBridge.scm",(void*)f_6865},
{"f_6573ChickenBridge.scm",(void*)f_6573},
{"f_6869ChickenBridge.scm",(void*)f_6869},
{"f_6859ChickenBridge.scm",(void*)f_6859},
{"f_6555ChickenBridge.scm",(void*)f_6555},
{"f_6850ChickenBridge.scm",(void*)f_6850},
{"f_6564ChickenBridge.scm",(void*)f_6564},
{"f_6854ChickenBridge.scm",(void*)f_6854},
{"f_6787ChickenBridge.scm",(void*)f_6787},
{"f_6812ChickenBridge.scm",(void*)f_6812},
{"f_6520ChickenBridge.scm",(void*)f_6520},
{"f_6800ChickenBridge.scm",(void*)f_6800},
{"f_6619ChickenBridge.scm",(void*)f_6619},
{"f_6738ChickenBridge.scm",(void*)f_6738},
{"f_6733ChickenBridge.scm",(void*)f_6733},
{"f_6621ChickenBridge.scm",(void*)f_6621},
{"f_6728ChickenBridge.scm",(void*)f_6728},
{"f_6732ChickenBridge.scm",(void*)f_6732},
{"f_6724ChickenBridge.scm",(void*)f_6724},
{"f_6692ChickenBridge.scm",(void*)f_6692},
{"f_6717ChickenBridge.scm",(void*)f_6717},
{"f_6721ChickenBridge.scm",(void*)f_6721},
{"f_6702ChickenBridge.scm",(void*)f_6702},
{"f_6681ChickenBridge.scm",(void*)f_6681},
{"f_6651ChickenBridge.scm",(void*)f_6651},
{"f_6623ChickenBridge.scm",(void*)f_6623},
{"f_6600ChickenBridge.scm",(void*)f_6600},
{"f_6605ChickenBridge.scm",(void*)f_6605},
{"f_6610ChickenBridge.scm",(void*)f_6610},
{"f_6578ChickenBridge.scm",(void*)f_6578},
{"f_6582ChickenBridge.scm",(void*)f_6582},
{"f_6534ChickenBridge.scm",(void*)f_6534},
{"f_6538ChickenBridge.scm",(void*)f_6538},
{"f_6525ChickenBridge.scm",(void*)f_6525},
{"f_6529ChickenBridge.scm",(void*)f_6529},
{"f_6513ChickenBridge.scm",(void*)f_6513},
{"f_6510ChickenBridge.scm",(void*)f_6510},
{"f_6467ChickenBridge.scm",(void*)f_6467},
{"f_6472ChickenBridge.scm",(void*)f_6472},
{"f_6453ChickenBridge.scm",(void*)f_6453},
{"f_6458ChickenBridge.scm",(void*)f_6458},
{"f_6424ChickenBridge.scm",(void*)f_6424},
{"f_6433ChickenBridge.scm",(void*)f_6433},
{"f_6438ChickenBridge.scm",(void*)f_6438},
{"f_6413ChickenBridge.scm",(void*)f_6413},
{"f_6418ChickenBridge.scm",(void*)f_6418},
{"f_6373ChickenBridge.scm",(void*)f_6373},
{"f_6403ChickenBridge.scm",(void*)f_6403},
{"f_6325ChickenBridge.scm",(void*)f_6325},
{"f_6359ChickenBridge.scm",(void*)f_6359},
{"f_6305ChickenBridge.scm",(void*)f_6305},
{"f_6285ChickenBridge.scm",(void*)f_6285},
{"f_6271ChickenBridge.scm",(void*)f_6271},
{"f_6261ChickenBridge.scm",(void*)f_6261},
{"f_6251ChickenBridge.scm",(void*)f_6251},
{"f_6241ChickenBridge.scm",(void*)f_6241},
{"f_6231ChickenBridge.scm",(void*)f_6231},
{"f_6209ChickenBridge.scm",(void*)f_6209},
{"f_6203ChickenBridge.scm",(void*)f_6203},
{"f_6156ChickenBridge.scm",(void*)f_6156},
{"f_6160ChickenBridge.scm",(void*)f_6160},
{"f_6176ChickenBridge.scm",(void*)f_6176},
{"f_6185ChickenBridge.scm",(void*)f_6185},
{"f_6163ChickenBridge.scm",(void*)f_6163},
{"f_6147ChickenBridge.scm",(void*)f_6147},
{"f_6151ChickenBridge.scm",(void*)f_6151},
{"f_5968ChickenBridge.scm",(void*)f_5968},
{"f_6121ChickenBridge.scm",(void*)f_6121},
{"f_6134ChickenBridge.scm",(void*)f_6134},
{"f_6116ChickenBridge.scm",(void*)f_6116},
{"f_5971ChickenBridge.scm",(void*)f_5971},
{"f_6113ChickenBridge.scm",(void*)f_6113},
{"f_6097ChickenBridge.scm",(void*)f_6097},
{"f_6090ChickenBridge.scm",(void*)f_6090},
{"f_6086ChickenBridge.scm",(void*)f_6086},
{"f_5999ChickenBridge.scm",(void*)f_5999},
{"f_6007ChickenBridge.scm",(void*)f_6007},
{"f_6017ChickenBridge.scm",(void*)f_6017},
{"f_6020ChickenBridge.scm",(void*)f_6020},
{"f_6002ChickenBridge.scm",(void*)f_6002},
{"f_5797ChickenBridge.scm",(void*)f_5797},
{"f_5803ChickenBridge.scm",(void*)f_5803},
{"f_5806ChickenBridge.scm",(void*)f_5806},
{"f_3609ChickenBridge.scm",(void*)f_3609},
{"f_3622ChickenBridge.scm",(void*)f_3622},
{"f_3629ChickenBridge.scm",(void*)f_3629},
{"f_3636ChickenBridge.scm",(void*)f_3636},
{"f_3615ChickenBridge.scm",(void*)f_3615},
{"f_5810ChickenBridge.scm",(void*)f_5810},
{"f_5844ChickenBridge.scm",(void*)f_5844},
{"f_5937ChickenBridge.scm",(void*)f_5937},
{"f_5947ChickenBridge.scm",(void*)f_5947},
{"f_5850ChickenBridge.scm",(void*)f_5850},
{"f_5907ChickenBridge.scm",(void*)f_5907},
{"f_5917ChickenBridge.scm",(void*)f_5917},
{"f_5858ChickenBridge.scm",(void*)f_5858},
{"f_5872ChickenBridge.scm",(void*)f_5872},
{"f_5876ChickenBridge.scm",(void*)f_5876},
{"f_5880ChickenBridge.scm",(void*)f_5880},
{"f_5884ChickenBridge.scm",(void*)f_5884},
{"f_5891ChickenBridge.scm",(void*)f_5891},
{"f_5868ChickenBridge.scm",(void*)f_5868},
{"f_5861ChickenBridge.scm",(void*)f_5861},
{"f_5813ChickenBridge.scm",(void*)f_5813},
{"f_4736ChickenBridge.scm",(void*)f_4736},
{"f_4749ChickenBridge.scm",(void*)f_4749},
{"f_4799ChickenBridge.scm",(void*)f_4799},
{"f_4896ChickenBridge.scm",(void*)f_4896},
{"f_4964ChickenBridge.scm",(void*)f_4964},
{"f_5221ChickenBridge.scm",(void*)f_5221},
{"f_4971ChickenBridge.scm",(void*)f_4971},
{"f_5209ChickenBridge.scm",(void*)f_5209},
{"f_5160ChickenBridge.scm",(void*)f_5160},
{"f_5166ChickenBridge.scm",(void*)f_5166},
{"f_5190ChickenBridge.scm",(void*)f_5190},
{"f_5186ChickenBridge.scm",(void*)f_5186},
{"f_5174ChickenBridge.scm",(void*)f_5174},
{"f_4974ChickenBridge.scm",(void*)f_4974},
{"f_5136ChickenBridge.scm",(void*)f_5136},
{"f_5140ChickenBridge.scm",(void*)f_5140},
{"f_4977ChickenBridge.scm",(void*)f_4977},
{"f_5113ChickenBridge.scm",(void*)f_5113},
{"f_5117ChickenBridge.scm",(void*)f_5117},
{"f_4980ChickenBridge.scm",(void*)f_4980},
{"f_5090ChickenBridge.scm",(void*)f_5090},
{"f_5094ChickenBridge.scm",(void*)f_5094},
{"f_4983ChickenBridge.scm",(void*)f_4983},
{"f_5015ChickenBridge.scm",(void*)f_5015},
{"f_5033ChickenBridge.scm",(void*)f_5033},
{"f_5051ChickenBridge.scm",(void*)f_5051},
{"f_5069ChickenBridge.scm",(void*)f_5069},
{"f_4986ChickenBridge.scm",(void*)f_4986},
{"f_4990ChickenBridge.scm",(void*)f_4990},
{"f_4900ChickenBridge.scm",(void*)f_4900},
{"f_4904ChickenBridge.scm",(void*)f_4904},
{"f_4908ChickenBridge.scm",(void*)f_4908},
{"f_4803ChickenBridge.scm",(void*)f_4803},
{"f_4807ChickenBridge.scm",(void*)f_4807},
{"f_4811ChickenBridge.scm",(void*)f_4811},
{"f_4830ChickenBridge.scm",(void*)f_4830},
{"f_4834ChickenBridge.scm",(void*)f_4834},
{"f_4814ChickenBridge.scm",(void*)f_4814},
{"f_4818ChickenBridge.scm",(void*)f_4818},
{"f_4753ChickenBridge.scm",(void*)f_4753},
{"f_4757ChickenBridge.scm",(void*)f_4757},
{"f_4761ChickenBridge.scm",(void*)f_4761},
{"f_4743ChickenBridge.scm",(void*)f_4743},
{"f_4558ChickenBridge.scm",(void*)f_4558},
{"f_4570ChickenBridge.scm",(void*)f_4570},
{"f_4589ChickenBridge.scm",(void*)f_4589},
{"f_4607ChickenBridge.scm",(void*)f_4607},
{"f_4639ChickenBridge.scm",(void*)f_4639},
{"f_4642ChickenBridge.scm",(void*)f_4642},
{"f_4635ChickenBridge.scm",(void*)f_4635},
{"f_4621ChickenBridge.scm",(void*)f_4621},
{"f_4592ChickenBridge.scm",(void*)f_4592},
{"f_4537ChickenBridge.scm",(void*)f_4537},
{"f_4544ChickenBridge.scm",(void*)f_4544},
{"f_4547ChickenBridge.scm",(void*)f_4547},
{"f_4553ChickenBridge.scm",(void*)f_4553},
{"f_4472ChickenBridge.scm",(void*)f_4472},
{"f_4481ChickenBridge.scm",(void*)f_4481},
{"f_4504ChickenBridge.scm",(void*)f_4504},
{"f_4494ChickenBridge.scm",(void*)f_4494},
{"f_4428ChickenBridge.scm",(void*)f_4428},
{"f_4416ChickenBridge.scm",(void*)f_4416},
{"f_4314ChickenBridge.scm",(void*)f_4314},
{"f_4266ChickenBridge.scm",(void*)f_4266},
{"f_3647ChickenBridge.scm",(void*)f_3647},
{"f_3651ChickenBridge.scm",(void*)f_3651},
{"f_3654ChickenBridge.scm",(void*)f_3654},
{"f_4080ChickenBridge.scm",(void*)f_4080},
{"f_4076ChickenBridge.scm",(void*)f_4076},
{"f_4072ChickenBridge.scm",(void*)f_4072},
{"f_3657ChickenBridge.scm",(void*)f_3657},
{"f_3780ChickenBridge.scm",(void*)f_3780},
{"f_3013ChickenBridge.scm",(void*)f_3013},
{"f_3786ChickenBridge.scm",(void*)f_3786},
{"f_3029ChickenBridge.scm",(void*)f_3029},
{"f_3874ChickenBridge.scm",(void*)f_3874},
{"f_3944ChickenBridge.scm",(void*)f_3944},
{"f_3045ChickenBridge.scm",(void*)f_3045},
{"f_3947ChickenBridge.scm",(void*)f_3947},
{"f_3077ChickenBridge.scm",(void*)f_3077},
{"f_4025ChickenBridge.scm",(void*)f_4025},
{"f_4051ChickenBridge.scm",(void*)f_4051},
{"f_4045ChickenBridge.scm",(void*)f_4045},
{"f_4034ChickenBridge.scm",(void*)f_4034},
{"f_3976ChickenBridge.scm",(void*)f_3976},
{"f_3986ChickenBridge.scm",(void*)f_3986},
{"f_4012ChickenBridge.scm",(void*)f_4012},
{"f_4006ChickenBridge.scm",(void*)f_4006},
{"f_3989ChickenBridge.scm",(void*)f_3989},
{"f_3999ChickenBridge.scm",(void*)f_3999},
{"f_3992ChickenBridge.scm",(void*)f_3992},
{"f_3953ChickenBridge.scm",(void*)f_3953},
{"f_3962ChickenBridge.scm",(void*)f_3962},
{"f_3956ChickenBridge.scm",(void*)f_3956},
{"f_3880ChickenBridge.scm",(void*)f_3880},
{"f_3898ChickenBridge.scm",(void*)f_3898},
{"f_3931ChickenBridge.scm",(void*)f_3931},
{"f_3917ChickenBridge.scm",(void*)f_3917},
{"f_3925ChickenBridge.scm",(void*)f_3925},
{"f_3908ChickenBridge.scm",(void*)f_3908},
{"f_3883ChickenBridge.scm",(void*)f_3883},
{"f_3795ChickenBridge.scm",(void*)f_3795},
{"f_3817ChickenBridge.scm",(void*)f_3817},
{"f_3864ChickenBridge.scm",(void*)f_3864},
{"f_3850ChickenBridge.scm",(void*)f_3850},
{"f_3858ChickenBridge.scm",(void*)f_3858},
{"f_3830ChickenBridge.scm",(void*)f_3830},
{"f_3833ChickenBridge.scm",(void*)f_3833},
{"f_3798ChickenBridge.scm",(void*)f_3798},
{"f_3815ChickenBridge.scm",(void*)f_3815},
{"f_3801ChickenBridge.scm",(void*)f_3801},
{"f_3672ChickenBridge.scm",(void*)f_3672},
{"f_3730ChickenBridge.scm",(void*)f_3730},
{"f_3733ChickenBridge.scm",(void*)f_3733},
{"f_3754ChickenBridge.scm",(void*)f_3754},
{"f_3765ChickenBridge.scm",(void*)f_3765},
{"f_3744ChickenBridge.scm",(void*)f_3744},
{"f_3678ChickenBridge.scm",(void*)f_3678},
{"f_3688ChickenBridge.scm",(void*)f_3688},
{"f_3724ChickenBridge.scm",(void*)f_3724},
{"f_3694ChickenBridge.scm",(void*)f_3694},
{"f_3709ChickenBridge.scm",(void*)f_3709},
{"f_3713ChickenBridge.scm",(void*)f_3713},
{"f_3717ChickenBridge.scm",(void*)f_3717},
{"f_3701ChickenBridge.scm",(void*)f_3701},
{"f_3543ChickenBridge.scm",(void*)f_3543},
{"f_3545ChickenBridge.scm",(void*)f_3545},
{"f_3593ChickenBridge.scm",(void*)f_3593},
{"f_3549ChickenBridge.scm",(void*)f_3549},
{"f_3552ChickenBridge.scm",(void*)f_3552},
{"f_3557ChickenBridge.scm",(void*)f_3557},
{"f_3578ChickenBridge.scm",(void*)f_3578},
{"f_3535ChickenBridge.scm",(void*)f_3535},
{"f_3537ChickenBridge.scm",(void*)f_3537},
{"f_3327ChickenBridge.scm",(void*)f_3327},
{"f_3344ChickenBridge.scm",(void*)f_3344},
{"f_3348ChickenBridge.scm",(void*)f_3348},
{"f_3294ChickenBridge.scm",(void*)f_3294},
{"f_3301ChickenBridge.scm",(void*)f_3301},
{"f_3245ChickenBridge.scm",(void*)f_3245},
{"f_3252ChickenBridge.scm",(void*)f_3252},
{"f_3310ChickenBridge.scm",(void*)f_3310},
{"f_3533ChickenBridge.scm",(void*)f_3533},
{"f_3510ChickenBridge.scm",(void*)f_3510},
{"f_3526ChickenBridge.scm",(void*)f_3526},
{"f_3372ChickenBridge.scm",(void*)f_3372},
{"f_3375ChickenBridge.scm",(void*)f_3375},
{"f_3399ChickenBridge.scm",(void*)f_3399},
{"f_3456ChickenBridge.scm",(void*)f_3456},
{"f_3462ChickenBridge.scm",(void*)f_3462},
{"f_3471ChickenBridge.scm",(void*)f_3471},
{"f_3480ChickenBridge.scm",(void*)f_3480},
{"f_3489ChickenBridge.scm",(void*)f_3489},
{"f_3498ChickenBridge.scm",(void*)f_3498},
{"f_3450ChickenBridge.scm",(void*)f_3450},
{"f_3405ChickenBridge.scm",(void*)f_3405},
{"f_3411ChickenBridge.scm",(void*)f_3411},
{"f_3417ChickenBridge.scm",(void*)f_3417},
{"f_3423ChickenBridge.scm",(void*)f_3423},
{"f_3429ChickenBridge.scm",(void*)f_3429},
{"f_3435ChickenBridge.scm",(void*)f_3435},
{"f_3276ChickenBridge.scm",(void*)f_3276},
{"f_3283ChickenBridge.scm",(void*)f_3283},
{"f_3266ChickenBridge.scm",(void*)f_3266},
{"f_3254ChickenBridge.scm",(void*)f_3254},
{"f_3222ChickenBridge.scm",(void*)f_3222},
{"f_3229ChickenBridge.scm",(void*)f_3229},
{"f_3236ChickenBridge.scm",(void*)f_3236},
{"f_3206ChickenBridge.scm",(void*)f_3206},
{"f_3213ChickenBridge.scm",(void*)f_3213},
{"f_3220ChickenBridge.scm",(void*)f_3220},
{"f_3194ChickenBridge.scm",(void*)f_3194},
{"f_3176ChickenBridge.scm",(void*)f_3176},
{"f_3158ChickenBridge.scm",(void*)f_3158},
{"f_3143ChickenBridge.scm",(void*)f_3143},
{"f_3137ChickenBridge.scm",(void*)f_3137},
{"f_3125ChickenBridge.scm",(void*)f_3125},
{"f_3107ChickenBridge.scm",(void*)f_3107},
{"f_3086ChickenBridge.scm",(void*)f_3086},
{"f_3054ChickenBridge.scm",(void*)f_3054},
{"f_3061ChickenBridge.scm",(void*)f_3061},
{"f_2996ChickenBridge.scm",(void*)f_2996},
{"f_3004ChickenBridge.scm",(void*)f_3004},
{"f_2986ChickenBridge.scm",(void*)f_2986},
{"f_2994ChickenBridge.scm",(void*)f_2994},
{"f_2980ChickenBridge.scm",(void*)f_2980},
{"f_2968ChickenBridge.scm",(void*)f_2968},
{"f_2944ChickenBridge.scm",(void*)f_2944},
{"f_2860ChickenBridge.scm",(void*)f_2860},
{"f_2839ChickenBridge.scm",(void*)f_2839},
{"f_2829ChickenBridge.scm",(void*)f_2829},
{"f_2817ChickenBridge.scm",(void*)f_2817},
{"f_2788ChickenBridge.scm",(void*)f_2788},
{"f_2776ChickenBridge.scm",(void*)f_2776},
{"f_2758ChickenBridge.scm",(void*)f_2758},
{"f_2740ChickenBridge.scm",(void*)f_2740},
{"f_2719ChickenBridge.scm",(void*)f_2719},
{"f_2713ChickenBridge.scm",(void*)f_2713},
{"f_2707ChickenBridge.scm",(void*)f_2707},
{"f_2688ChickenBridge.scm",(void*)f_2688},
{"f_2669ChickenBridge.scm",(void*)f_2669},
{"f_2663ChickenBridge.scm",(void*)f_2663},
{"f_2623ChickenBridge.scm",(void*)f_2623},
{"f_2604ChickenBridge.scm",(void*)f_2604},
{"f_2560ChickenBridge.scm",(void*)f_2560},
{"f_2554ChickenBridge.scm",(void*)f_2554},
{"f_2548ChickenBridge.scm",(void*)f_2548},
{"f_2542ChickenBridge.scm",(void*)f_2542},
{"f_2536ChickenBridge.scm",(void*)f_2536},
{"f_2513ChickenBridge.scm",(void*)f_2513},
{"f_2530ChickenBridge.scm",(void*)f_2530},
{"f_2455ChickenBridge.scm",(void*)f_2455},
{"f_2507ChickenBridge.scm",(void*)f_2507},
{"f_2491ChickenBridge.scm",(void*)f_2491},
{"f_2472ChickenBridge.scm",(void*)f_2472},
{"f_2367ChickenBridge.scm",(void*)f_2367},
{"f_2413ChickenBridge.scm",(void*)f_2413},
{"f_2361ChickenBridge.scm",(void*)f_2361},
{"f_2302ChickenBridge.scm",(void*)f_2302},
{"f_2315ChickenBridge.scm",(void*)f_2315},
{"f_2351ChickenBridge.scm",(void*)f_2351},
{"f_2296ChickenBridge.scm",(void*)f_2296},
{"f_2201ChickenBridge.scm",(void*)f_2201},
{"f_2205ChickenBridge.scm",(void*)f_2205},
{"f_2208ChickenBridge.scm",(void*)f_2208},
{"f_2220ChickenBridge.scm",(void*)f_2220},
{"f_2242ChickenBridge.scm",(void*)f_2242},
{"f_2195ChickenBridge.scm",(void*)f_2195},
{"f_2189ChickenBridge.scm",(void*)f_2189},
{"f_2183ChickenBridge.scm",(void*)f_2183},
{"f_2177ChickenBridge.scm",(void*)f_2177},
{"f_2171ChickenBridge.scm",(void*)f_2171},
{"f_2111ChickenBridge.scm",(void*)f_2111},
{"f_2123ChickenBridge.scm",(void*)f_2123},
{"f_2118ChickenBridge.scm",(void*)f_2118},
{"f_2113ChickenBridge.scm",(void*)f_2113},
{"f_2092ChickenBridge.scm",(void*)f_2092},
{"f_2086ChickenBridge.scm",(void*)f_2086},
{"f_2080ChickenBridge.scm",(void*)f_2080},
{"f_1998ChickenBridge.scm",(void*)f_1998},
{"f_2012ChickenBridge.scm",(void*)f_2012},
{"f_1979ChickenBridge.scm",(void*)f_1979},
{"f_1966ChickenBridge.scm",(void*)f_1966},
{"f_1956ChickenBridge.scm",(void*)f_1956},
{"f_1945ChickenBridge.scm",(void*)f_1945},
{"f_1938ChickenBridge.scm",(void*)f_1938},
{"f_1927ChickenBridge.scm",(void*)f_1927},
{"f_1889ChickenBridge.scm",(void*)f_1889},
{"f_1882ChickenBridge.scm",(void*)f_1882},
{"f_1807ChickenBridge.scm",(void*)f_1807},
{"f_1773ChickenBridge.scm",(void*)f_1773},
{"f_1746ChickenBridge.scm",(void*)f_1746},
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
