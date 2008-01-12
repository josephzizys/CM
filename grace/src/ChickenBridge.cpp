/* Generated from ChickenBridge.scm by the CHICKEN compiler
   http://www.call-with-current-continuation.org
   2008-01-12 09:48
   Version 2.741 - macosx-unix-gnu-ppc	[ manyargs dload ptables applyhook ]
   (c)2000-2007 Felix L. Winkelmann	compiled 2008-01-12 on galen.local (Darwin)
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

static C_TLS C_word lf[401];
static C_char C_TLS li0[]={C_lihdr(0,0,40),40,116,98,58,114,101,115,99,97,108,101,32,97,53,56,32,97,52,57,32,97,51,49,48,32,97,50,49,49,32,97,49,49,50,32,97,48,49,51,41};
static C_char C_TLS li1[]={C_lihdr(0,0,49),40,116,98,58,100,105,115,99,114,101,116,101,32,97,50,48,50,51,32,97,49,57,50,52,32,97,49,56,50,53,32,97,49,55,50,54,32,97,49,54,50,55,32,97,49,53,50,56,41};
static C_char C_TLS li2[]={C_lihdr(0,0,25),40,116,98,58,100,101,99,105,109,97,108,115,32,97,51,52,51,55,32,97,51,51,51,56,41};
static C_char C_TLS li3[]={C_lihdr(0,0,15),40,116,98,58,114,97,110,105,32,97,56,51,56,54,41};
static C_char C_TLS li4[]={C_lihdr(0,0,15),40,116,98,58,114,97,110,102,32,97,56,55,57,48,41};
static C_char C_TLS li5[]={C_lihdr(0,0,29),40,116,98,58,114,97,110,103,97,117,115,115,32,97,49,49,53,49,49,56,32,97,49,49,52,49,49,57,41};
static C_char C_TLS li6[]={C_lihdr(0,0,19),40,116,98,58,114,97,110,101,120,112,32,97,49,50,49,49,50,52,41};
static C_char C_TLS li7[]={C_lihdr(0,0,28),40,116,98,58,114,97,110,98,101,116,97,32,97,49,50,55,49,51,48,32,97,49,50,54,49,51,49,41};
static C_char C_TLS li8[]={C_lihdr(0,0,21),40,116,98,58,114,97,110,103,97,109,109,97,32,97,49,51,51,49,51,54,41};
static C_char C_TLS li9[]={C_lihdr(0,0,23),40,116,98,58,114,97,110,112,111,105,115,115,111,110,32,97,49,52,49,49,52,52,41};
static C_char C_TLS li10[]={C_lihdr(0,0,45),40,114,101,115,99,97,108,101,32,120,49,53,49,32,120,49,49,53,50,32,120,50,49,53,51,32,121,49,49,53,52,32,121,50,49,53,53,32,46,32,98,49,53,54,41};
static C_char C_TLS li11[]={C_lihdr(0,0,43),40,100,105,115,99,114,101,116,101,32,120,49,53,55,32,120,49,49,53,56,32,120,50,49,53,57,32,105,49,49,54,48,32,46,32,97,114,103,115,49,54,49,41};
static C_char C_TLS li12[]={C_lihdr(0,0,10),40,105,110,116,32,102,49,54,50,41};
static C_char C_TLS li13[]={C_lihdr(0,0,26),40,113,117,97,110,116,105,122,101,32,110,117,109,49,54,51,32,115,116,101,112,115,49,54,52,41};
static C_char C_TLS li14[]={C_lihdr(0,0,29),40,100,101,99,105,109,97,108,115,32,110,117,109,49,54,53,32,46,32,100,105,103,105,116,115,49,54,54,41};
static C_char C_TLS li15[]={C_lihdr(0,0,26),40,98,111,100,121,49,55,49,32,116,101,109,112,111,49,55,55,32,98,101,97,116,49,55,56,41};
static C_char C_TLS li16[]={C_lihdr(0,0,26),40,100,101,102,45,98,101,97,116,49,55,52,32,37,116,101,109,112,111,49,54,57,49,56,48,41};
static C_char C_TLS li17[]={C_lihdr(0,0,14),40,100,101,102,45,116,101,109,112,111,49,55,51,41};
static C_char C_TLS li18[]={C_lihdr(0,0,36),40,114,104,121,116,104,109,45,62,115,101,99,111,110,100,115,32,98,101,97,116,115,49,54,55,32,46,32,97,114,103,115,49,54,56,41};
static C_char C_TLS li19[]={C_lihdr(0,0,24),40,99,101,110,116,115,45,62,115,99,97,108,101,114,32,99,101,110,116,115,49,56,55,41};
static C_char C_TLS li20[]={C_lihdr(0,0,22),40,115,99,97,108,101,114,45,62,99,101,110,116,115,32,110,117,109,49,56,56,41};
static C_char C_TLS li21[]={C_lihdr(0,0,20),40,107,101,121,110,117,109,45,62,104,101,114,116,122,32,107,49,56,57,41};
static C_char C_TLS li22[]={C_lihdr(0,0,17),40,107,101,121,110,117,109,45,62,112,99,32,107,49,57,48,41};
static C_char C_TLS li23[]={C_lihdr(0,0,21),40,104,101,114,116,122,45,62,107,101,121,110,117,109,32,104,122,49,57,49,41};
static C_char C_TLS li24[]={C_lihdr(0,0,15),40,100,111,50,48,48,32,116,97,105,108,50,48,50,41};
static C_char C_TLS li25[]={C_lihdr(0,0,34),40,105,110,116,101,114,112,108,32,120,49,57,50,32,99,111,111,114,100,115,49,57,51,32,46,32,98,97,115,101,49,57,52,41};
static C_char C_TLS li26[]={C_lihdr(0,0,23),40,105,110,116,101,114,112,32,120,50,49,48,32,46,32,97,114,103,115,50,49,49,41};
static C_char C_TLS li27[]={C_lihdr(0,0,27),40,100,111,50,49,54,32,105,50,49,56,32,107,50,49,57,32,108,50,50,48,32,116,50,50,49,41};
static C_char C_TLS li28[]={C_lihdr(0,0,34),40,115,116,101,112,115,32,108,101,110,50,49,50,32,107,101,121,110,117,109,50,49,51,32,46,32,97,114,103,115,50,49,52,41};
static C_char C_TLS li29[]={C_lihdr(0,0,18),40,114,97,110,45,115,101,116,33,32,115,101,101,100,50,50,54,41};
static C_char C_TLS li30[]={C_lihdr(0,0,15),40,114,97,110,32,46,32,97,114,103,115,50,50,55,41};
static C_char C_TLS li31[]={C_lihdr(0,0,21),40,111,100,100,115,32,110,50,50,56,32,46,32,97,114,103,115,50,50,57,41};
static C_char C_TLS li32[]={C_lihdr(0,0,15),40,112,105,99,107,108,32,97,114,103,115,50,51,48,41};
static C_char C_TLS li33[]={C_lihdr(0,0,16),40,112,105,99,107,32,46,32,97,114,103,115,50,51,49,41};
static C_char C_TLS li34[]={C_lihdr(0,0,8),40,114,97,110,108,111,119,41};
static C_char C_TLS li35[]={C_lihdr(0,0,9),40,114,97,110,104,105,103,104,41};
static C_char C_TLS li36[]={C_lihdr(0,0,11),40,114,97,110,109,105,100,100,108,101,41};
static C_char C_TLS li37[]={C_lihdr(0,0,19),40,114,97,110,98,101,116,97,32,46,32,97,114,103,115,50,51,50,41};
static C_char C_TLS li38[]={C_lihdr(0,0,18),40,114,97,110,101,120,112,32,46,32,97,114,103,115,50,51,51,41};
static C_char C_TLS li39[]={C_lihdr(0,0,20),40,114,97,110,103,97,117,115,115,32,46,32,97,114,103,115,50,51,52,41};
static C_char C_TLS li40[]={C_lihdr(0,0,11),40,114,97,110,99,97,117,99,104,121,41};
static C_char C_TLS li41[]={C_lihdr(0,0,22),40,114,97,110,112,111,105,115,115,111,110,32,46,32,97,114,103,115,50,51,53,41};
static C_char C_TLS li42[]={C_lihdr(0,0,20),40,114,97,110,103,97,109,109,97,32,46,32,97,114,103,115,50,51,54,41};
static C_char C_TLS li43[]={C_lihdr(0,0,10),40,114,97,110,98,114,111,119,110,41};
static C_char C_TLS li44[]={C_lihdr(0,0,9),40,114,97,110,112,105,110,107,41};
static C_char C_TLS li45[]={C_lihdr(0,0,42),40,109,97,107,101,45,116,111,107,101,110,32,116,121,112,101,50,57,51,32,115,116,114,105,110,103,50,57,52,32,112,111,115,105,116,105,111,110,50,57,53,41};
static C_char C_TLS li46[]={C_lihdr(0,0,17),40,116,111,107,101,110,45,116,121,112,101,32,120,51,48,48,41};
static C_char C_TLS li47[]={C_lihdr(0,0,19),40,116,111,107,101,110,45,115,116,114,105,110,103,32,120,51,48,54,41};
static C_char C_TLS li48[]={C_lihdr(0,0,21),40,116,111,107,101,110,45,112,111,115,105,116,105,111,110,32,120,51,49,50,41};
static C_char C_TLS li49[]={C_lihdr(0,0,18),40,108,105,115,116,45,62,116,111,107,101,110,32,108,51,50,49,41};
static C_char C_TLS li50[]={C_lihdr(0,0,21),40,102,105,114,115,116,45,116,111,107,101,110,32,116,111,107,115,51,50,51,41};
static C_char C_TLS li51[]={C_lihdr(0,0,22),40,110,117,108,108,45,116,111,107,101,110,115,63,32,116,111,107,115,51,50,53,41};
static C_char C_TLS li52[]={C_lihdr(0,0,58),40,109,97,107,101,45,114,117,108,101,32,110,97,109,101,51,50,54,32,116,121,112,101,51,50,55,32,112,97,116,116,101,114,110,51,50,56,32,112,97,114,115,101,114,51,50,57,32,101,109,105,116,101,114,51,51,48,41};
static C_char C_TLS li53[]={C_lihdr(0,0,16),40,114,117,108,101,45,110,97,109,101,32,120,51,51,53,41};
static C_char C_TLS li54[]={C_lihdr(0,0,24),40,103,101,116,45,114,117,108,101,32,116,121,112,51,55,49,32,100,101,102,51,55,50,41};
static C_char C_TLS li55[]={C_lihdr(0,0,22),40,112,97,116,116,101,114,110,45,99,108,97,117,115,101,63,32,120,51,55,53,41};
static C_char C_TLS li56[]={C_lihdr(0,0,19),40,112,97,116,116,101,114,110,45,115,117,98,115,32,120,51,55,55,41};
static C_char C_TLS li57[]={C_lihdr(0,0,20),40,112,97,116,116,101,114,110,45,110,115,117,98,115,32,120,51,55,56,41};
static C_char C_TLS li58[]={C_lihdr(0,0,23),40,112,97,116,116,101,114,110,45,115,117,98,32,120,51,55,57,32,105,51,56,48,41};
static C_char C_TLS li59[]={C_lihdr(0,0,28),40,112,97,116,116,101,114,110,45,122,101,114,111,45,111,114,45,109,111,114,101,63,32,120,51,56,52,41};
static C_char C_TLS li60[]={C_lihdr(0,0,40),40,109,97,107,101,45,112,97,114,115,101,45,101,114,114,111,114,32,115,116,114,105,110,103,51,56,54,32,112,111,115,105,116,105,111,110,51,56,55,41};
static C_char C_TLS li61[]={C_lihdr(0,0,25),40,112,97,114,115,101,45,101,114,114,111,114,45,115,116,114,105,110,103,32,120,51,57,50,41};
static C_char C_TLS li62[]={C_lihdr(0,0,27),40,112,97,114,115,101,45,101,114,114,111,114,45,112,111,115,105,116,105,111,110,32,120,51,57,56,41};
static C_char C_TLS li63[]={C_lihdr(0,0,47),40,109,97,107,101,45,112,97,114,115,101,45,117,110,105,116,32,116,121,112,101,52,48,54,32,112,97,114,115,101,100,52,48,55,32,112,111,115,105,116,105,111,110,52,48,56,41};
static C_char C_TLS li64[]={C_lihdr(0,0,18),40,112,97,114,115,101,45,117,110,105,116,63,32,120,52,48,57,41};
static C_char C_TLS li65[]={C_lihdr(0,0,22),40,112,97,114,115,101,45,117,110,105,116,45,116,121,112,101,32,120,52,49,51,41};
static C_char C_TLS li66[]={C_lihdr(0,0,24),40,112,97,114,115,101,45,117,110,105,116,45,112,97,114,115,101,100,32,120,52,49,57,41};
static C_char C_TLS li67[]={C_lihdr(0,0,26),40,112,97,114,115,101,45,117,110,105,116,45,112,111,115,105,116,105,111,110,32,120,52,50,53,41};
static C_char C_TLS li68[]={C_lihdr(0,0,18),40,116,111,107,101,110,45,117,110,105,116,63,32,120,52,51,53,41};
static C_char C_TLS li69[]={C_lihdr(0,0,31),40,116,111,107,101,110,45,117,110,105,116,45,116,121,112,101,61,63,32,120,52,51,54,32,116,121,112,52,51,55,41};
static C_char C_TLS li70[]={C_lihdr(0,0,31),40,103,101,116,45,101,109,105,116,45,105,110,102,111,32,110,97,109,101,52,51,57,32,105,110,102,111,52,52,48,41};
static C_char C_TLS li71[]={C_lihdr(0,0,39),40,97,100,100,45,101,109,105,116,45,105,110,102,111,32,110,97,109,101,52,52,50,32,100,97,116,97,52,52,51,32,105,110,102,111,52,52,52,41};
static C_char C_TLS li72[]={C_lihdr(0,0,40),40,115,101,116,45,101,109,105,116,45,105,110,102,111,33,32,110,97,109,101,52,52,53,32,100,97,116,97,52,52,54,32,105,110,102,111,52,52,55,41};
static C_char C_TLS li73[]={C_lihdr(0,0,27),40,101,109,105,116,32,120,52,53,48,32,105,110,102,111,52,53,49,32,101,114,114,102,52,53,50,41};
static C_char C_TLS li74[]={C_lihdr(0,0,34),40,101,109,105,116,45,108,105,115,116,32,108,105,115,52,53,51,32,105,110,102,111,52,53,52,32,101,114,114,102,52,53,53,41};
static C_char C_TLS li75[]={C_lihdr(0,0,24),40,102,95,51,53,53,51,32,97,114,103,115,52,54,56,32,101,114,114,102,52,54,57,41};
static C_char C_TLS li76[]={C_lihdr(0,0,28),40,115,105,109,112,108,101,45,117,110,105,116,45,112,97,114,115,101,114,32,116,121,112,101,52,54,55,41};
static C_char C_TLS li77[]={C_lihdr(0,0,15),40,100,111,52,55,55,32,116,97,105,108,52,55,57,41};
static C_char C_TLS li78[]={C_lihdr(0,0,32),40,102,95,51,53,54,49,32,117,110,105,116,52,55,49,32,105,110,102,111,52,55,50,32,101,114,114,102,52,55,51,41};
static C_char C_TLS li79[]={C_lihdr(0,0,29),40,115,105,109,112,108,101,45,117,110,105,116,45,101,109,105,116,116,101,114,32,102,117,110,99,52,55,48,41};
static C_char C_TLS li80[]={C_lihdr(0,0,7),40,97,51,55,53,57,41};
static C_char C_TLS li81[]={C_lihdr(0,0,22),40,97,51,55,54,57,32,97,53,48,57,32,98,53,49,48,32,99,53,49,49,41};
static C_char C_TLS li82[]={C_lihdr(0,0,7),40,97,51,56,54,53,41};
static C_char C_TLS li83[]={C_lihdr(0,0,22),40,97,51,56,55,57,32,97,53,50,53,32,98,53,50,54,32,99,53,50,55,41};
static C_char C_TLS li84[]={C_lihdr(0,0,12),40,100,111,53,50,48,32,105,53,50,50,41};
static C_char C_TLS li85[]={C_lihdr(0,0,7),40,97,51,57,51,50,41};
static C_char C_TLS li86[]={C_lihdr(0,0,22),40,97,51,57,52,54,32,97,53,52,55,32,98,53,52,56,32,99,53,52,57,41};
static C_char C_TLS li87[]={C_lihdr(0,0,12),40,100,111,53,52,50,32,105,53,52,52,41};
static C_char C_TLS li88[]={C_lihdr(0,0,7),40,97,52,48,50,49,41};
static C_char C_TLS li89[]={C_lihdr(0,0,22),40,97,52,48,50,55,32,97,53,54,54,32,98,53,54,55,32,99,53,54,56,41};
static C_char C_TLS li90[]={C_lihdr(0,0,7),40,100,111,53,54,50,41};
static C_char C_TLS li91[]={C_lihdr(0,0,7),40,97,52,48,54,48,41};
static C_char C_TLS li92[]={C_lihdr(0,0,22),40,97,52,48,54,54,32,97,53,56,52,32,98,53,56,53,32,99,53,56,54,41};
static C_char C_TLS li93[]={C_lihdr(0,0,64),40,112,97,114,115,101,114,32,112,97,116,52,57,54,32,116,111,107,101,110,115,52,57,55,32,102,111,114,99,101,45,97,110,100,52,57,56,32,108,101,118,101,108,52,57,57,32,116,114,97,99,101,53,48,48,32,101,114,114,102,53,48,49,41};
static C_char C_TLS li94[]={C_lihdr(0,0,20),40,83,97,108,84,111,107,101,110,84,121,112,101,63,32,105,55,54,49,41};
static C_char C_TLS li95[]={C_lihdr(0,0,17),40,83,97,108,79,112,84,121,112,101,63,32,105,55,54,53,41};
static C_char C_TLS li96[]={C_lihdr(0,0,19),40,83,97,108,82,117,108,101,84,121,112,101,63,32,105,55,55,52,41};
static C_char C_TLS li97[]={C_lihdr(0,0,27),40,83,97,108,84,121,112,101,61,63,32,116,121,112,49,55,55,53,32,116,121,112,50,55,55,54,41};
static C_char C_TLS li98[]={C_lihdr(0,0,15),40,100,111,56,50,53,32,116,111,107,115,56,50,55,41};
static C_char C_TLS li99[]={C_lihdr(0,0,34),40,114,101,109,111,118,101,45,116,111,107,101,110,45,116,121,112,101,32,116,111,107,115,56,50,49,32,116,121,112,56,50,50,41};
static C_char C_TLS li100[]={C_lihdr(0,0,13),40,105,115,45,111,112,63,32,120,56,53,50,41};
static C_char C_TLS li101[]={C_lihdr(0,0,25),40,100,111,56,54,49,32,119,50,56,54,51,32,111,107,56,54,52,32,108,105,56,54,53,41};
static C_char C_TLS li102[]={C_lihdr(0,0,7),40,100,111,56,53,57,41};
static C_char C_TLS li103[]={C_lihdr(0,0,17),40,105,110,102,45,62,112,114,101,32,105,110,102,56,53,52,41};
static C_char C_TLS li104[]={C_lihdr(0,0,38),40,115,97,108,45,112,97,114,115,101,45,115,116,101,112,112,105,110,103,32,97,114,103,115,49,48,50,49,32,101,114,114,102,49,48,50,50,41};
static C_char C_TLS li105[]={C_lihdr(0,0,14),40,100,111,49,50,50,57,32,102,49,50,51,49,41};
static C_char C_TLS li106[]={C_lihdr(0,0,14),40,100,111,49,50,50,50,32,102,49,50,50,52,41};
static C_char C_TLS li107[]={C_lihdr(0,0,7),40,97,51,54,51,48,41};
static C_char C_TLS li108[]={C_lihdr(0,0,40),40,97,51,54,51,55,32,115,117,99,99,101,115,115,52,57,49,32,114,101,115,117,108,116,115,52,57,50,32,114,101,109,97,105,110,115,52,57,51,41};
static C_char C_TLS li109[]={C_lihdr(0,0,15),40,97,51,54,50,52,32,101,114,114,102,52,56,57,41};
static C_char C_TLS li110[]={C_lihdr(0,0,47),40,115,97,108,32,115,116,114,105,110,103,49,50,48,55,32,114,117,108,101,49,50,48,56,32,116,111,107,101,110,115,49,50,48,57,32,116,114,97,99,101,63,49,50,49,48,41};
static C_char C_TLS li111[]={C_lihdr(0,0,17),40,100,111,49,50,52,56,32,116,97,105,108,49,50,53,48,41};
static C_char C_TLS li112[]={C_lihdr(0,0,19),40,112,114,105,110,116,101,114,32,116,104,105,110,103,49,50,52,55,41};
static C_char C_TLS li113[]={C_lihdr(0,0,17),40,100,111,49,50,53,54,32,116,97,105,108,49,50,53,56,41};
static C_char C_TLS li114[]={C_lihdr(0,0,22),40,115,97,108,58,112,114,105,110,116,32,46,32,97,114,103,115,49,50,52,53,41};
static C_char C_TLS li115[]={C_lihdr(0,0,20),40,115,97,108,58,99,104,100,105,114,32,112,97,116,104,49,50,54,51,41};
static C_char C_TLS li116[]={C_lihdr(0,0,19),40,115,97,108,58,108,111,97,100,32,102,105,108,101,49,50,54,53,41};
static C_char C_TLS li117[]={C_lihdr(0,0,21),40,115,97,108,58,111,112,101,110,32,46,32,97,114,103,115,49,50,54,57,41};
static C_char C_TLS li118[]={C_lihdr(0,0,23),40,115,97,108,58,111,117,116,112,117,116,32,46,32,97,114,103,115,49,50,55,48,41};
static C_char C_TLS li119[]={C_lihdr(0,0,13),40,102,105,102,116,104,32,108,49,51,57,50,41};
static C_char C_TLS li120[]={C_lihdr(0,0,13),40,115,105,120,116,104,32,108,49,51,57,51,41};
static C_char C_TLS li121[]={C_lihdr(0,0,15),40,115,101,118,101,110,116,104,32,108,49,51,57,52,41};
static C_char C_TLS li122[]={C_lihdr(0,0,14),40,101,105,103,104,116,104,32,108,49,51,57,53,41};
static C_char C_TLS li123[]={C_lihdr(0,0,13),40,110,105,110,116,104,32,108,49,51,57,54,41};
static C_char C_TLS li124[]={C_lihdr(0,0,13),40,116,101,110,116,104,32,108,49,51,57,55,41};
static C_char C_TLS li125[]={C_lihdr(0,0,12),40,108,97,115,116,32,108,49,51,57,57,41};
static C_char C_TLS li126[]={C_lihdr(0,0,15),40,98,117,116,108,97,115,116,32,108,49,52,48,48,41};
static C_char C_TLS li127[]={C_lihdr(0,0,18),40,108,105,115,116,42,32,46,32,97,114,103,115,49,52,48,49,41};
static C_char C_TLS li128[]={C_lihdr(0,0,8),40,102,95,54,52,51,52,41};
static C_char C_TLS li129[]={C_lihdr(0,0,19),40,99,117,114,114,101,110,116,45,100,105,114,101,99,116,111,114,121,41};
static C_char C_TLS li130[]={C_lihdr(0,0,18),40,102,95,54,52,52,57,32,97,49,52,48,54,49,52,49,48,41};
static C_char C_TLS li131[]={C_lihdr(0,0,28),40,99,104,97,110,103,101,45,100,105,114,101,99,116,111,114,121,32,46,32,100,105,114,49,52,48,53,41};
static C_char C_TLS li132[]={C_lihdr(0,0,25),40,112,114,105,110,116,45,109,101,115,115,97,103,101,32,97,49,52,49,50,49,52,49,54,41};
static C_char C_TLS li133[]={C_lihdr(0,0,23),40,112,114,105,110,116,45,101,114,114,111,114,32,97,49,52,49,56,49,52,50,50,41};
static C_char C_TLS li134[]={C_lihdr(0,0,27),40,99,117,114,114,101,110,116,45,116,105,109,101,45,109,105,108,108,105,115,101,99,111,110,100,115,41};
static C_char C_TLS li135[]={C_lihdr(0,0,22),40,99,117,114,114,101,110,116,45,116,105,109,101,45,115,101,99,111,110,100,115,41};
static C_char C_TLS li136[]={C_lihdr(0,0,3),0,0,0};
static C_char C_TLS li137[]={C_lihdr(0,0,43),40,115,99,104,101,100,117,108,101,114,45,115,101,116,45,116,105,109,101,45,109,105,108,108,105,115,101,99,111,110,100,115,32,97,49,52,52,56,49,52,53,49,41};
static C_char C_TLS li138[]={C_lihdr(0,0,3),0,0,0};
static C_char C_TLS li139[]={C_lihdr(0,0,48),40,115,99,104,101,100,117,108,101,114,45,115,112,114,111,117,116,32,97,49,52,53,54,49,52,53,57,32,97,49,52,53,53,49,52,54,48,32,97,49,52,53,52,49,52,54,49,41};
static C_char C_TLS li140[]={C_lihdr(0,0,3),0,0,0};
static C_char C_TLS li141[]={C_lihdr(0,0,26),40,115,99,104,101,100,117,108,101,114,45,115,116,111,112,32,97,49,52,55,54,49,52,55,57,41};
static C_char C_TLS li142[]={C_lihdr(0,0,18),40,102,95,54,54,50,49,32,97,49,52,56,55,49,52,57,49,41};
static C_char C_TLS li143[]={C_lihdr(0,0,24),40,108,111,97,100,45,115,97,108,45,102,105,108,101,32,102,105,108,101,49,52,56,54,41};
static C_char C_TLS li144[]={C_lihdr(0,0,11),40,110,101,120,116,115,116,97,114,116,41};
static C_char C_TLS li145[]={C_lihdr(0,0,8),40,110,101,120,116,105,100,41};
static C_char C_TLS li146[]={C_lihdr(0,0,14),40,100,111,49,53,49,49,32,112,49,53,49,51,41};
static C_char C_TLS li147[]={C_lihdr(0,0,27),40,98,111,100,121,49,52,57,55,32,115,116,97,114,116,49,53,48,51,32,105,100,49,53,48,52,41};
static C_char C_TLS li148[]={C_lihdr(0,0,27),40,100,101,102,45,105,100,49,53,48,48,32,37,115,116,97,114,116,49,52,57,53,49,53,49,57,41};
static C_char C_TLS li149[]={C_lihdr(0,0,15),40,100,101,102,45,115,116,97,114,116,49,52,57,57,41};
static C_char C_TLS li150[]={C_lihdr(0,0,28),40,115,112,114,111,117,116,32,112,114,111,99,49,52,57,51,32,46,32,97,114,103,115,49,52,57,52,41};
static C_char C_TLS li151[]={C_lihdr(0,0,3),0,0,0};
static C_char C_TLS li152[]={C_lihdr(0,0,23),40,116,105,109,101,45,102,111,114,109,97,116,32,46,32,97,114,103,49,53,50,53,41};
static C_char C_TLS li153[]={C_lihdr(0,0,3),0,0,0};
static C_char C_TLS li154[]={C_lihdr(0,0,7),40,112,97,117,115,101,41};
static C_char C_TLS li155[]={C_lihdr(0,0,3),0,0,0};
static C_char C_TLS li156[]={C_lihdr(0,0,9),40,112,97,117,115,101,100,63,41};
static C_char C_TLS li157[]={C_lihdr(0,0,3),0,0,0};
static C_char C_TLS li158[]={C_lihdr(0,0,6),40,99,111,110,116,41};
static C_char C_TLS li159[]={C_lihdr(0,0,17),40,100,111,49,53,51,57,32,116,97,105,108,49,53,52,49,41};
static C_char C_TLS li160[]={C_lihdr(0,0,19),40,115,116,111,112,32,46,32,112,114,111,99,105,100,49,53,51,56,41};
static C_char C_TLS li161[]={C_lihdr(0,0,3),0,0,0};
static C_char C_TLS li162[]={C_lihdr(0,0,6),40,104,117,115,104,41};
static C_char C_TLS li163[]={C_lihdr(0,0,27),40,102,95,55,50,50,52,32,115,116,114,49,53,53,56,32,46,32,97,114,103,115,49,53,53,57,41};
static C_char C_TLS li164[]={C_lihdr(0,0,14),40,102,95,55,50,49,51,32,107,49,53,54,50,41};
static C_char C_TLS li165[]={C_lihdr(0,0,14),40,102,95,55,50,50,50,32,107,49,53,54,51,41};
static C_char C_TLS li166[]={C_lihdr(0,0,17),40,100,111,49,53,57,48,32,116,97,105,108,49,53,57,50,41};
static C_char C_TLS li167[]={C_lihdr(0,0,13),40,97,55,49,55,48,32,120,49,53,56,48,41};
static C_char C_TLS li168[]={C_lihdr(0,0,32),40,100,111,49,53,55,50,32,107,101,121,49,53,55,52,32,97,114,103,49,53,55,53,32,112,111,115,49,53,55,54,41};
static C_char C_TLS li169[]={C_lihdr(0,0,7),40,97,55,50,48,52,41};
static C_char C_TLS li170[]={C_lihdr(0,0,40),40,101,120,112,97,110,100,45,115,101,110,100,32,109,101,115,103,49,53,53,50,32,100,97,116,97,49,53,53,51,32,101,114,114,102,49,53,53,52,41};
static C_char C_TLS li171[]={C_lihdr(0,0,3),0,0,0};
static C_char C_TLS li172[]={C_lihdr(0,0,51),40,109,112,58,110,111,116,101,32,116,105,109,101,49,53,57,57,32,100,117,114,49,54,48,48,32,107,101,121,49,54,48,49,32,97,109,112,49,54,48,50,32,99,104,97,110,49,54,48,51,41};
static C_char C_TLS li173[]={C_lihdr(0,0,41),40,109,112,58,111,110,32,116,105,109,101,49,54,48,52,32,107,101,121,49,54,48,53,32,118,101,108,49,54,48,54,32,99,104,97,110,49,54,48,55,41};
static C_char C_TLS li174[]={C_lihdr(0,0,42),40,109,112,58,111,102,102,32,116,105,109,101,49,54,48,56,32,107,101,121,49,54,48,57,32,118,101,108,49,54,49,48,32,99,104,97,110,49,54,49,49,41};
static C_char C_TLS li175[]={C_lihdr(0,0,36),40,109,112,58,112,114,111,103,32,116,105,109,101,49,54,49,50,32,112,114,111,103,49,54,49,51,32,99,104,97,110,49,54,49,52,41};
static C_char C_TLS li176[]={C_lihdr(0,0,44),40,109,112,58,99,116,114,108,32,116,105,109,101,49,54,49,53,32,99,116,114,108,49,54,49,54,32,118,97,108,49,54,49,55,32,99,104,97,110,49,54,49,56,41};
static C_char C_TLS li177[]={C_lihdr(0,0,11),40,109,112,58,97,108,108,111,102,102,41};
static C_char C_TLS li178[]={C_lihdr(0,0,19),40,109,112,58,109,105,99,114,111,32,100,105,118,115,49,54,49,57,41};
static C_char C_TLS li179[]={C_lihdr(0,0,16),40,97,55,50,57,57,32,37,101,114,114,49,54,51,53,41};
static C_char C_TLS li180[]={C_lihdr(0,0,7),40,97,55,51,49,57,41};
static C_char C_TLS li181[]={C_lihdr(0,0,17),40,97,55,50,57,51,32,37,99,111,110,116,49,54,51,52,41};
static C_char C_TLS li182[]={C_lihdr(0,0,16),40,97,55,50,56,55,32,37,109,115,103,49,54,51,51,41};
static C_char C_TLS li183[]={C_lihdr(0,0,38),40,102,95,55,51,50,53,32,97,49,54,50,55,49,54,51,48,32,97,49,54,50,54,49,54,51,49,32,97,49,54,50,53,49,54,51,50,41};
static C_char C_TLS li184[]={C_lihdr(0,0,32),40,109,112,58,105,110,104,111,111,107,32,37,104,111,111,107,49,54,50,48,32,46,32,97,114,103,115,49,54,50,49,41};
static C_char C_TLS li185[]={C_lihdr(0,0,17),40,100,111,49,54,54,52,32,100,101,99,108,49,54,54,54,41};
static C_char C_TLS li186[]={C_lihdr(0,0,17),40,100,111,49,54,52,56,32,116,97,105,108,49,54,53,48,41};
static C_char C_TLS li187[]={C_lihdr(0,0,45),40,97,55,56,52,50,32,98,105,110,100,105,110,103,115,49,54,51,57,32,116,101,114,109,105,110,97,116,101,49,54,52,48,32,46,32,98,111,100,121,49,54,52,49,41};
static C_char C_TLS li188[]={C_lihdr(0,0,27),40,97,55,56,52,56,32,109,101,115,115,49,53,57,55,32,46,32,100,97,116,97,49,53,57,56,41};
static C_char C_TLS li189[]={C_lihdr(0,0,25),40,97,55,56,53,52,32,102,117,110,99,49,53,52,54,32,105,110,102,111,49,53,52,55,41};
static C_char C_TLS li190[]={C_lihdr(0,0,25),40,97,55,57,49,52,32,97,114,103,115,49,50,48,50,32,101,114,114,102,49,50,48,51,41};
static C_char C_TLS li191[]={C_lihdr(0,0,34),40,97,55,57,50,56,32,117,110,105,116,49,50,48,52,32,105,110,102,111,49,50,48,53,32,101,114,114,102,49,50,48,54,41};
static C_char C_TLS li192[]={C_lihdr(0,0,25),40,97,56,48,51,52,32,97,114,103,115,49,49,53,49,32,101,114,114,102,49,49,53,50,41};
static C_char C_TLS li193[]={C_lihdr(0,0,17),40,100,111,49,49,54,51,32,114,101,115,116,49,49,54,53,41};
static C_char C_TLS li194[]={C_lihdr(0,0,26),40,100,111,49,49,56,57,32,97,114,103,115,49,49,57,49,32,116,97,105,108,49,49,57,50,41};
static C_char C_TLS li195[]={C_lihdr(0,0,34),40,97,56,48,55,51,32,117,110,105,116,49,49,53,54,32,105,110,102,111,49,49,53,55,32,101,114,114,102,49,49,53,56,41};
static C_char C_TLS li196[]={C_lihdr(0,0,25),40,97,56,52,57,49,32,97,114,103,115,49,49,52,52,32,101,114,114,102,49,49,52,53,41};
static C_char C_TLS li197[]={C_lihdr(0,0,25),40,97,56,54,51,54,32,97,114,103,115,49,49,51,48,32,101,114,114,102,49,49,51,49,41};
static C_char C_TLS li198[]={C_lihdr(0,0,17),40,100,111,49,49,48,56,32,116,97,105,108,49,49,49,48,41};
static C_char C_TLS li199[]={C_lihdr(0,0,17),40,100,111,49,49,48,51,32,116,97,105,108,49,49,48,53,41};
static C_char C_TLS li200[]={C_lihdr(0,0,20),40,100,111,49,48,57,50,32,99,108,97,117,115,101,115,49,48,57,52,41};
static C_char C_TLS li201[]={C_lihdr(0,0,17),40,100,111,49,48,56,57,32,116,97,105,108,49,48,57,49,41};
static C_char C_TLS li202[]={C_lihdr(0,0,34),40,97,56,54,56,50,32,117,110,105,116,49,49,52,48,32,105,110,102,111,49,49,52,49,32,101,114,114,102,49,49,52,50,41};
static C_char C_TLS li203[]={C_lihdr(0,0,25),40,97,57,49,51,54,32,97,114,103,115,49,48,48,53,32,101,114,114,102,49,48,48,54,41};
static C_char C_TLS li204[]={C_lihdr(0,0,34),40,97,57,50,48,52,32,117,110,105,116,49,48,49,55,32,105,110,102,111,49,48,49,56,32,101,114,114,102,49,48,49,57,41};
static C_char C_TLS li205[]={C_lihdr(0,0,23),40,97,57,51,51,51,32,97,114,103,115,57,57,51,32,101,114,114,102,57,57,52,41};
static C_char C_TLS li206[]={C_lihdr(0,0,32),40,97,57,51,53,57,32,117,110,105,116,57,57,56,32,105,110,102,111,57,57,57,32,101,114,114,102,49,48,48,48,41};
static C_char C_TLS li207[]={C_lihdr(0,0,23),40,97,57,52,52,55,32,97,114,103,115,57,55,49,32,101,114,114,102,57,55,50,41};
static C_char C_TLS li208[]={C_lihdr(0,0,15),40,100,111,57,55,57,32,105,116,101,114,57,56,49,41};
static C_char C_TLS li209[]={C_lihdr(0,0,31),40,97,57,52,57,48,32,117,110,105,116,57,55,51,32,105,110,102,111,57,55,52,32,101,114,114,102,57,55,53,41};
static C_char C_TLS li210[]={C_lihdr(0,0,23),40,97,57,55,50,55,32,97,114,103,115,57,54,56,32,101,114,114,102,57,54,57,41};
static C_char C_TLS li211[]={C_lihdr(0,0,23),40,97,57,56,49,51,32,97,114,103,115,57,54,48,32,101,114,114,102,57,54,49,41};
static C_char C_TLS li212[]={C_lihdr(0,0,12),40,97,57,56,54,53,32,101,57,54,54,41};
static C_char C_TLS li213[]={C_lihdr(0,0,31),40,97,57,56,53,54,32,117,110,105,116,57,54,50,32,105,110,102,111,57,54,51,32,101,114,114,102,57,54,52,41};
static C_char C_TLS li214[]={C_lihdr(0,0,23),40,97,57,57,49,53,32,97,114,103,115,57,53,51,32,101,114,114,102,57,53,52,41};
static C_char C_TLS li215[]={C_lihdr(0,0,12),40,97,57,57,53,54,32,101,57,53,56,41};
static C_char C_TLS li216[]={C_lihdr(0,0,31),40,97,57,57,53,48,32,117,110,105,116,57,53,53,32,105,110,102,111,57,53,54,32,101,114,114,102,57,53,55,41};
static C_char C_TLS li217[]={C_lihdr(0,0,32),40,97,49,48,48,49,48,32,117,110,105,116,57,52,54,32,105,110,102,111,57,52,55,32,101,114,114,102,57,52,56,41};
static C_char C_TLS li218[]={C_lihdr(0,0,32),40,97,49,48,48,55,49,32,117,110,105,116,57,52,48,32,105,110,102,111,57,52,49,32,101,114,114,102,57,52,50,41};
static C_char C_TLS li219[]={C_lihdr(0,0,24),40,97,49,48,49,50,53,32,97,114,103,115,57,51,52,32,101,114,114,102,57,51,53,41};
static C_char C_TLS li220[]={C_lihdr(0,0,32),40,97,49,48,49,53,53,32,117,110,105,116,57,51,54,32,105,110,102,111,57,51,55,32,101,114,114,102,57,51,56,41};
static C_char C_TLS li221[]={C_lihdr(0,0,24),40,97,49,48,51,55,52,32,97,114,103,115,57,50,55,32,101,114,114,102,57,50,56,41};
static C_char C_TLS li222[]={C_lihdr(0,0,24),40,97,49,48,52,48,48,32,97,114,103,115,57,49,52,32,101,114,114,102,57,49,53,41};
static C_char C_TLS li223[]={C_lihdr(0,0,25),40,97,49,48,52,56,49,32,115,116,114,57,50,52,32,46,32,97,114,103,115,57,50,53,41};
static C_char C_TLS li224[]={C_lihdr(0,0,32),40,97,49,48,52,54,49,32,117,110,105,116,57,49,57,32,105,110,102,111,57,50,48,32,101,114,114,102,57,50,49,41};
static C_char C_TLS li225[]={C_lihdr(0,0,24),40,97,49,48,53,57,57,32,97,114,103,115,57,48,54,32,101,114,114,102,57,48,55,41};
static C_char C_TLS li226[]={C_lihdr(0,0,32),40,97,49,48,54,50,54,32,117,110,105,116,57,48,57,32,105,110,102,111,57,49,48,32,101,114,114,102,57,49,49,41};
static C_char C_TLS li227[]={C_lihdr(0,0,24),40,97,49,48,55,48,56,32,97,114,103,115,56,57,50,32,101,114,114,102,56,57,51,41};
static C_char C_TLS li228[]={C_lihdr(0,0,15),40,100,111,56,57,57,32,97,114,103,115,57,48,49,41};
static C_char C_TLS li229[]={C_lihdr(0,0,32),40,97,49,48,55,51,48,32,117,110,105,116,56,57,52,32,105,110,102,111,56,57,53,32,101,114,114,102,56,57,54,41};
static C_char C_TLS li230[]={C_lihdr(0,0,24),40,97,49,48,56,54,50,32,97,114,103,115,56,56,53,32,101,114,114,102,56,56,54,41};
static C_char C_TLS li231[]={C_lihdr(0,0,32),40,97,49,48,56,56,56,32,117,110,105,116,56,56,55,32,105,110,102,111,56,56,56,32,101,114,114,102,56,56,57,41};
static C_char C_TLS li232[]={C_lihdr(0,0,24),40,97,49,48,57,57,56,32,97,114,103,115,56,56,49,32,101,114,114,102,56,56,50,41};
static C_char C_TLS li233[]={C_lihdr(0,0,24),40,97,49,49,49,53,52,32,97,114,103,115,56,52,52,32,101,114,114,102,56,52,53,41};
static C_char C_TLS li234[]={C_lihdr(0,0,32),40,97,49,49,49,55,50,32,117,110,105,116,56,52,54,32,105,110,102,111,56,52,55,32,101,114,114,102,56,52,56,41};
static C_char C_TLS li235[]={C_lihdr(0,0,24),40,97,49,49,50,50,53,32,97,114,103,115,56,51,56,32,101,114,114,102,56,51,57,41};
static C_char C_TLS li236[]={C_lihdr(0,0,24),40,97,49,49,51,55,55,32,97,114,103,115,56,51,53,32,101,114,114,102,56,51,54,41};
static C_char C_TLS li237[]={C_lihdr(0,0,24),40,97,49,49,53,49,54,32,97,114,103,115,56,51,50,32,101,114,114,102,56,51,51,41};
static C_char C_TLS li238[]={C_lihdr(0,0,24),40,97,49,49,54,51,54,32,97,114,103,115,56,49,49,32,101,114,114,102,56,49,50,41};
static C_char C_TLS li239[]={C_lihdr(0,0,32),40,97,49,49,54,54,55,32,117,110,105,116,56,49,52,32,105,110,102,111,56,49,53,32,101,114,114,102,56,49,54,41};
static C_char C_TLS li240[]={C_lihdr(0,0,24),40,97,49,49,55,53,57,32,97,114,103,115,56,48,53,32,101,114,114,102,56,48,54,41};
static C_char C_TLS li241[]={C_lihdr(0,0,32),40,97,49,49,55,55,55,32,117,110,105,116,56,48,55,32,105,110,102,111,56,48,56,32,101,114,114,102,56,48,57,41};
static C_char C_TLS li242[]={C_lihdr(0,0,32),40,97,49,49,56,53,49,32,117,110,105,116,55,57,52,32,105,110,102,111,55,57,53,32,101,114,114,102,55,57,54,41};
static C_char C_TLS li243[]={C_lihdr(0,0,24),40,97,49,49,57,52,55,32,97,114,103,115,55,56,50,32,101,114,114,102,55,56,51,41};
static C_char C_TLS li244[]={C_lihdr(0,0,32),40,97,49,49,57,53,55,32,117,110,105,116,55,56,52,32,105,110,102,111,55,56,53,32,101,114,114,102,55,56,54,41};
static C_char C_TLS li245[]={C_lihdr(0,0,18),40,97,49,50,49,51,51,32,117,52,51,50,32,112,52,51,51,41};
static C_char C_TLS li246[]={C_lihdr(0,0,18),40,97,49,50,49,53,57,32,101,52,48,52,32,112,52,48,53,41};
static C_char C_TLS li247[]={C_lihdr(0,0,18),40,97,49,50,49,55,51,32,114,51,54,56,32,112,51,54,57,41};
static C_char C_TLS li248[]={C_lihdr(0,0,18),40,97,49,50,49,56,51,32,116,51,49,57,32,112,51,50,48,41};
static C_char C_TLS li249[]={C_lihdr(0,0,10),40,116,111,112,108,101,118,101,108,41};


/* from k7332 */
static C_word C_fcall stub1628(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2) C_regparm;
C_regparm static C_word C_fcall stub1628(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
C_word t0=(C_word )(C_a0);
unsigned int t1=(unsigned int )C_unfix(C_a1);
unsigned int t2=(unsigned int )C_unfix(C_a2);
set_input_hook(t0,t1,t2);
return C_r;}

/* from k6624 */
static C_word C_fcall stub1488(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub1488(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
load_sal_file(t0);
return C_r;}

/* from k6609 in hush in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
C_noret_decl(stub1482)
static void C_ccall stub1482(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub1482(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_hush();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k6603 */
C_noret_decl(stub1477)
static void C_ccall stub1477(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0) C_noret;
static void C_ccall stub1477(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_unfix(C_a0);
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_stop(t0);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k6587 in cont in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
C_noret_decl(stub1472)
static void C_ccall stub1472(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub1472(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_cont();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k6578 in pause in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
C_noret_decl(stub1468)
static void C_ccall stub1468(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub1468(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_pause();
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k6569 in paused? in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
C_noret_decl(stub1464)
static void C_ccall stub1464(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub1464(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
C_r=C_mk_bool(scheduler_is_paused());
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k6563 */
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

/* from k6543 in scheduler-set-time-milliseconds in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
C_noret_decl(stub1449)
static void C_ccall stub1449(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0) C_noret;
static void C_ccall stub1449(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_truep(C_a0);
int C_level=C_save_callback_continuation(&C_a,C_k);
scheduler_set_time_milliseconds(t0);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k6534 in time-format in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
C_noret_decl(stub1444)
static void C_ccall stub1444(C_word C_c,C_word C_self,C_word C_k,C_word C_buf) C_noret;
static void C_ccall stub1444(C_word C_c,C_word C_self,C_word C_k,C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int C_level=C_save_callback_continuation(&C_a,C_k);
C_r=C_mk_bool(scheduler_is_time_milliseconds());
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from current-time-seconds in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
#define return(x) C_cblock C_r = (C_flonum(&C_a,(x))); goto C_ret; C_cblockend
static C_word C_fcall stub1441(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub1441(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
 C_return( (Time::getMillisecondCounterHiRes() / 1000.0) );
C_ret:
#undef return

return C_r;}

/* from current-time-milliseconds in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
#define return(x) C_cblock C_r = (C_flonum(&C_a,(x))); goto C_ret; C_cblockend
static C_word C_fcall stub1438(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub1438(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
 C_return( Time::getMillisecondCounterHiRes());
C_ret:
#undef return

return C_r;}

/* from k6522 */
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

/* from k6486 in print-error in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static C_word C_fcall stub1419(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub1419(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_error(t0);
return C_r;}

/* from k6472 in print-message in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static C_word C_fcall stub1413(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub1413(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_message(t0);
return C_r;}

/* from k6452 */
static C_word C_fcall stub1407(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub1407(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
set_current_directory(t0);
return C_r;}

/* from f_6434 in current-directory in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
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

/* from k1985 */
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

/* from k1975 */
static C_word C_fcall stub134(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub134(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::rangamma(t0));
return C_r;}

/* from k1968 */
static C_word C_fcall stub128(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub128(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
C_r=C_flonum(&C_a,Toolbox::ranbeta(t0,t1));
return C_r;}

/* from k1957 */
static C_word C_fcall stub122(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub122(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::ranexp(t0));
return C_r;}

/* from k1950 */
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

/* from k1930 */
static C_word C_fcall stub100(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub100(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
C_r=C_flonum(&C_a,Toolbox::ran(t0,t1));
return C_r;}

/* from k1919 */
static C_word C_fcall stub94(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub94(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_unfix(C_a0);
int t1=(int )C_unfix(C_a1);
C_r=C_fix((C_word)Toolbox::ran(t0,t1));
return C_r;}

/* from k1908 */
static C_word C_fcall stub88(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub88(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::ran(t0));
return C_r;}

/* from k1901 */
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

/* from k1891 */
static C_word C_fcall stub75(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub75(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::hertz_to_keynum(t0));
return C_r;}

/* from k1884 */
static C_word C_fcall stub71(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub71(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_fix((C_word)Toolbox::keynum_to_pc(t0));
return C_r;}

/* from k1877 */
static C_word C_fcall stub66(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub66(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_flonum(&C_a,Toolbox::keynum_to_hertz(t0));
return C_r;}

/* from k1870 */
static C_word C_fcall stub62(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub62(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_fix((C_word)Toolbox::scaler_to_cents(t0));
return C_r;}

/* from k1863 */
static C_word C_fcall stub57(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub57(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
int t0=(int )C_unfix(C_a0);
C_r=C_flonum(&C_a,Toolbox::cents_to_scaler(t0));
return C_r;}

/* from k1856 */
static C_word C_fcall stub50(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2) C_regparm;
C_regparm static C_word C_fcall stub50(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
float t2=(float )C_c_double(C_a2);
C_r=C_flonum(&C_a,Toolbox::rhythm_to_seconds(t0,t1,t2));
return C_r;}

/* from k1841 */
static C_word C_fcall stub42(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub42(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
C_r=C_flonum(&C_a,Toolbox::quantize(t0,t1));
return C_r;}

/* from k1830 */
static C_word C_fcall stub35(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub35(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
int t1=(int )C_unfix(C_a1);
C_r=C_flonum(&C_a,Toolbox::decimals(t0,t1));
return C_r;}

/* from k1819 */
static C_word C_fcall stub30(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub30(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
float t0=(float )C_c_double(C_a0);
C_r=C_fix((C_word)Toolbox::float_to_fixnum(t0));
return C_r;}

/* from k1812 */
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

/* from k1785 */
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
C_noret_decl(f_1751)
static void C_ccall f_1751(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1754)
static void C_ccall f_1754(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1757)
static void C_ccall f_1757(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1760)
static void C_ccall f_1760(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12184)
static void C_ccall f_12184(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_12192)
static void C_ccall f_12192(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12196)
static void C_ccall f_12196(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2802)
static void C_ccall f_2802(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2853)
static void C_ccall f_2853(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12174)
static void C_ccall f_12174(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_12182)
static void C_ccall f_12182(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2958)
static void C_ccall f_2958(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12160)
static void C_ccall f_12160(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_12168)
static void C_ccall f_12168(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12172)
static void C_ccall f_12172(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3151)
static void C_ccall f_3151(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12134)
static void C_ccall f_12134(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_12138)
static void C_ccall f_12138(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12144)
static void C_ccall f_12144(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12155)
static void C_ccall f_12155(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12151)
static void C_ccall f_12151(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3220)
static void C_ccall f_3220(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12112)
static void C_ccall f_12112(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4465)
static void C_ccall f_4465(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12092)
static void C_ccall f_12092(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4468)
static void C_ccall f_4468(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12052)
static void C_ccall f_12052(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4471)
static void C_ccall f_4471(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11958)
static void C_ccall f_11958(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_11962)
static void C_ccall f_11962(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11965)
static void C_ccall f_11965(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11983)
static void C_ccall f_11983(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11986)
static void C_ccall f_11986(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12017)
static void C_ccall f_12017(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11989)
static void C_fcall f_11989(C_word t0,C_word t1) C_noret;
C_noret_decl(f_11995)
static void C_ccall f_11995(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11948)
static void C_ccall f_11948(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_11942)
static void C_ccall f_11942(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4474)
static void C_ccall f_4474(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11850)
static void C_ccall f_11850(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11852)
static void C_ccall f_11852(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_11856)
static void C_ccall f_11856(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11859)
static void C_ccall f_11859(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11862)
static void C_ccall f_11862(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11902)
static void C_ccall f_11902(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11894)
static void C_ccall f_11894(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11865)
static void C_ccall f_11865(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11868)
static void C_ccall f_11868(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11871)
static void C_ccall f_11871(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11842)
static void C_ccall f_11842(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4477)
static void C_ccall f_4477(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11814)
static void C_ccall f_11814(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4480)
static void C_ccall f_4480(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11778)
static void C_ccall f_11778(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_11790)
static void C_ccall f_11790(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11786)
static void C_ccall f_11786(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11760)
static void C_ccall f_11760(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_11754)
static void C_ccall f_11754(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4483)
static void C_ccall f_4483(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11668)
static void C_ccall f_11668(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_11672)
static void C_ccall f_11672(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11675)
static void C_ccall f_11675(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11678)
static void C_ccall f_11678(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11691)
static void C_ccall f_11691(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11637)
static void C_ccall f_11637(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_11641)
static void C_ccall f_11641(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11656)
static void C_ccall f_11656(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11631)
static void C_ccall f_11631(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4486)
static void C_ccall f_4486(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11517)
static void C_ccall f_11517(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_11533)
static void C_ccall f_11533(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11544)
static void C_ccall f_11544(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11511)
static void C_ccall f_11511(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4542)
static void C_ccall f_4542(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11378)
static void C_ccall f_11378(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_11401)
static void C_ccall f_11401(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11398)
static void C_ccall f_11398(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11372)
static void C_ccall f_11372(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4545)
static void C_ccall f_4545(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11226)
static void C_ccall f_11226(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_11244)
static void C_ccall f_11244(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11253)
static void C_ccall f_11253(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11220)
static void C_ccall f_11220(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4548)
static void C_ccall f_4548(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11173)
static void C_ccall f_11173(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_11177)
static void C_ccall f_11177(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11180)
static void C_ccall f_11180(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11196)
static void C_ccall f_11196(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11155)
static void C_ccall f_11155(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_11149)
static void C_ccall f_11149(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4551)
static void C_ccall f_4551(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_11073)
static void C_ccall f_11073(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4690)
static void C_ccall f_4690(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10999)
static void C_ccall f_10999(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_11006)
static void C_ccall f_11006(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10993)
static void C_ccall f_10993(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4693)
static void C_ccall f_4693(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10889)
static void C_ccall f_10889(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_10897)
static void C_ccall f_10897(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10863)
static void C_ccall f_10863(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_10880)
static void C_ccall f_10880(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10871)
static void C_fcall f_10871(C_word t0,C_word t1) C_noret;
C_noret_decl(f_10857)
static void C_ccall f_10857(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4696)
static void C_ccall f_4696(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10813)
static void C_ccall f_10813(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4699)
static void C_ccall f_4699(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10731)
static void C_ccall f_10731(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_10742)
static void C_ccall f_10742(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10744)
static void C_fcall f_10744(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_10773)
static void C_ccall f_10773(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10709)
static void C_ccall f_10709(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_10725)
static void C_ccall f_10725(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10703)
static void C_ccall f_10703(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4702)
static void C_ccall f_4702(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10627)
static void C_ccall f_10627(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_10631)
static void C_ccall f_10631(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10663)
static void C_ccall f_10663(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10644)
static void C_ccall f_10644(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10648)
static void C_ccall f_10648(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10600)
static void C_ccall f_10600(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_10604)
static void C_ccall f_10604(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10594)
static void C_ccall f_10594(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4705)
static void C_ccall f_4705(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10462)
static void C_ccall f_10462(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_10502)
static void C_ccall f_10502(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10466)
static void C_ccall f_10466(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10482)
static void C_ccall f_10482(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_10482)
static void C_ccall f_10482r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_10494)
static void C_ccall f_10494(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10498)
static void C_ccall f_10498(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10490)
static void C_ccall f_10490(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10401)
static void C_ccall f_10401(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_10448)
static void C_ccall f_10448(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10408)
static void C_fcall f_10408(C_word t0,C_word t1) C_noret;
C_noret_decl(f_10419)
static void C_ccall f_10419(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10395)
static void C_ccall f_10395(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4708)
static void C_ccall f_4708(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10375)
static void C_ccall f_10375(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_10369)
static void C_ccall f_10369(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4711)
static void C_ccall f_4711(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10349)
static void C_ccall f_10349(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10353)
static void C_ccall f_10353(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10341)
static void C_ccall f_10341(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4714)
static void C_ccall f_4714(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10321)
static void C_ccall f_10321(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10325)
static void C_ccall f_10325(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10313)
static void C_ccall f_10313(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4717)
static void C_ccall f_4717(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10293)
static void C_ccall f_10293(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10297)
static void C_ccall f_10297(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10285)
static void C_ccall f_10285(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4720)
static void C_ccall f_4720(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10265)
static void C_ccall f_10265(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10269)
static void C_ccall f_10269(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10257)
static void C_ccall f_10257(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4723)
static void C_ccall f_4723(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10156)
static void C_ccall f_10156(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_10126)
static void C_ccall f_10126(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_10150)
static void C_ccall f_10150(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10120)
static void C_ccall f_10120(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4726)
static void C_ccall f_4726(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10070)
static void C_ccall f_10070(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10072)
static void C_ccall f_10072(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_10076)
static void C_ccall f_10076(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10104)
static void C_ccall f_10104(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10096)
static void C_ccall f_10096(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10092)
static void C_ccall f_10092(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10079)
static void C_ccall f_10079(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10062)
static void C_ccall f_10062(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4729)
static void C_ccall f_4729(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10009)
static void C_ccall f_10009(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10011)
static void C_ccall f_10011(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_10015)
static void C_ccall f_10015(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10046)
static void C_ccall f_10046(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10038)
static void C_ccall f_10038(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10034)
static void C_ccall f_10034(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10018)
static void C_ccall f_10018(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10021)
static void C_ccall f_10021(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_10001)
static void C_ccall f_10001(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4732)
static void C_ccall f_4732(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9951)
static void C_ccall f_9951(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_9965)
static void C_ccall f_9965(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9957)
static void C_ccall f_9957(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_9916)
static void C_ccall f_9916(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_9949)
static void C_ccall f_9949(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9910)
static void C_ccall f_9910(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4735)
static void C_ccall f_4735(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9857)
static void C_ccall f_9857(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_9861)
static void C_ccall f_9861(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9874)
static void C_ccall f_9874(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9866)
static void C_ccall f_9866(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_9814)
static void C_ccall f_9814(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_9847)
static void C_ccall f_9847(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9808)
static void C_ccall f_9808(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4738)
static void C_ccall f_4738(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9728)
static void C_ccall f_9728(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_9722)
static void C_ccall f_9722(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4741)
static void C_ccall f_4741(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9491)
static void C_ccall f_9491(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_9495)
static void C_ccall f_9495(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9503)
static void C_fcall f_9503(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_9526)
static void C_ccall f_9526(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9529)
static void C_ccall f_9529(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9532)
static void C_ccall f_9532(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9535)
static void C_ccall f_9535(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9595)
static void C_ccall f_9595(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9602)
static void C_ccall f_9602(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9612)
static void C_ccall f_9612(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9622)
static void C_ccall f_9622(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9636)
static void C_ccall f_9636(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9646)
static void C_ccall f_9646(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9656)
static void C_ccall f_9656(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9666)
static void C_ccall f_9666(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9538)
static void C_fcall f_9538(C_word t0,C_word t1) C_noret;
C_noret_decl(f_9562)
static void C_fcall f_9562(C_word t0,C_word t1) C_noret;
C_noret_decl(f_9541)
static void C_fcall f_9541(C_word t0,C_word t1) C_noret;
C_noret_decl(f_9448)
static void C_ccall f_9448(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_9481)
static void C_ccall f_9481(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9442)
static void C_ccall f_9442(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4744)
static void C_ccall f_4744(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9360)
static void C_ccall f_9360(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_9364)
static void C_ccall f_9364(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9370)
static void C_ccall f_9370(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9390)
static void C_ccall f_9390(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9334)
static void C_ccall f_9334(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_9344)
static void C_fcall f_9344(C_word t0,C_word t1) C_noret;
C_noret_decl(f_9328)
static void C_ccall f_9328(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4747)
static void C_ccall f_4747(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9205)
static void C_ccall f_9205(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_9209)
static void C_ccall f_9209(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9137)
static void C_ccall f_9137(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_9156)
static void C_ccall f_9156(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9191)
static void C_ccall f_9191(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9162)
static void C_fcall f_9162(C_word t0,C_word t1) C_noret;
C_noret_decl(f_9166)
static void C_ccall f_9166(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9180)
static void C_ccall f_9180(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_9169)
static void C_fcall f_9169(C_word t0,C_word t1) C_noret;
C_noret_decl(f_9150)
static void C_fcall f_9150(C_word t0,C_word t1) C_noret;
C_noret_decl(f_9131)
static void C_ccall f_9131(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4750)
static void C_ccall f_4750(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8859)
static void C_ccall f_8859(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5273)
static void C_ccall f_5273(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8811)
static void C_ccall f_8811(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8803)
static void C_ccall f_8803(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5276)
static void C_ccall f_5276(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8683)
static void C_ccall f_8683(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_5282)
static void C_ccall f_5282(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5754)
static void C_ccall f_5754(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5788)
static void C_ccall f_5788(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5780)
static void C_ccall f_5780(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5776)
static void C_ccall f_5776(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5761)
static void C_ccall f_5761(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5765)
static void C_ccall f_5765(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5758)
static void C_ccall f_5758(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5300)
static void C_fcall f_5300(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5747)
static void C_ccall f_5747(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5743)
static void C_ccall f_5743(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5307)
static void C_fcall f_5307(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5618)
static void C_fcall f_5618(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_5639)
static void C_ccall f_5639(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5641)
static void C_fcall f_5641(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_5655)
static void C_ccall f_5655(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5708)
static void C_ccall f_5708(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5658)
static void C_fcall f_5658(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5693)
static void C_ccall f_5693(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5661)
static void C_fcall f_5661(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5674)
static void C_ccall f_5674(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5686)
static void C_ccall f_5686(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5678)
static void C_ccall f_5678(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5664)
static void C_fcall f_5664(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5628)
static void C_ccall f_5628(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5310)
static void C_ccall f_5310(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5582)
static void C_fcall f_5582(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_5608)
static void C_ccall f_5608(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5593)
static void C_ccall f_5593(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5313)
static void C_ccall f_5313(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5317)
static void C_ccall f_5317(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5526)
static void C_fcall f_5526(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_5536)
static void C_ccall f_5536(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5539)
static void C_ccall f_5539(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5560)
static void C_ccall f_5560(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5542)
static void C_fcall f_5542(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5546)
static void C_ccall f_5546(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5320)
static void C_ccall f_5320(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5323)
static void C_fcall f_5323(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5489)
static void C_ccall f_5489(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5497)
static void C_ccall f_5497(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5493)
static void C_ccall f_5493(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5326)
static void C_fcall f_5326(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5354)
static void C_ccall f_5354(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5357)
static void C_ccall f_5357(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5360)
static void C_ccall f_5360(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5363)
static void C_ccall f_5363(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5422)
static void C_ccall f_5422(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8637)
static void C_ccall f_8637(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_8653)
static void C_ccall f_8653(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8656)
static void C_ccall f_8656(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8659)
static void C_fcall f_8659(C_word t0,C_word t1) C_noret;
C_noret_decl(f_8662)
static void C_fcall f_8662(C_word t0,C_word t1) C_noret;
C_noret_decl(f_8673)
static void C_ccall f_8673(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8631)
static void C_ccall f_8631(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5795)
static void C_ccall f_5795(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8492)
static void C_ccall f_8492(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_8531)
static void C_ccall f_8531(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8505)
static void C_fcall f_8505(C_word t0,C_word t1) C_noret;
C_noret_decl(f_8486)
static void C_ccall f_8486(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5798)
static void C_ccall f_5798(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8074)
static void C_ccall f_8074(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_8078)
static void C_ccall f_8078(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8090)
static void C_ccall f_8090(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8148)
static void C_ccall f_8148(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8151)
static void C_ccall f_8151(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8154)
static void C_ccall f_8154(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8366)
static void C_ccall f_8366(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8304)
static void C_ccall f_8304(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8338)
static void C_ccall f_8338(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8313)
static void C_fcall f_8313(C_word t0,C_word t1) C_noret;
C_noret_decl(f_8324)
static void C_ccall f_8324(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8320)
static void C_ccall f_8320(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8163)
static void C_fcall f_8163(C_word t0,C_word t1) C_noret;
C_noret_decl(f_8241)
static void C_ccall f_8241(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8282)
static void C_ccall f_8282(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8286)
static void C_ccall f_8286(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8290)
static void C_ccall f_8290(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8245)
static void C_ccall f_8245(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8249)
static void C_ccall f_8249(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8276)
static void C_ccall f_8276(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8252)
static void C_fcall f_8252(C_word t0,C_word t1) C_noret;
C_noret_decl(f_8166)
static void C_fcall f_8166(C_word t0,C_word t1) C_noret;
C_noret_decl(f_8238)
static void C_ccall f_8238(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8180)
static void C_ccall f_8180(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8182)
static void C_fcall f_8182(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_8230)
static void C_ccall f_8230(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8201)
static void C_ccall f_8201(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8218)
static void C_ccall f_8218(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8204)
static void C_fcall f_8204(C_word t0,C_word t1) C_noret;
C_noret_decl(f_8197)
static void C_ccall f_8197(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8169)
static void C_ccall f_8169(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8099)
static void C_fcall f_8099(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_8109)
static void C_ccall f_8109(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8115)
static void C_ccall f_8115(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8087)
static void C_ccall f_8087(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8035)
static void C_ccall f_8035(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_8052)
static void C_ccall f_8052(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8068)
static void C_ccall f_8068(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_8046)
static void C_fcall f_8046(C_word t0,C_word t1) C_noret;
C_noret_decl(f_8029)
static void C_ccall f_8029(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5801)
static void C_ccall f_5801(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7953)
static void C_ccall f_7953(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5804)
static void C_ccall f_5804(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7929)
static void C_ccall f_7929(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_7941)
static void C_ccall f_7941(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7937)
static void C_ccall f_7937(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7915)
static void C_ccall f_7915(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_7923)
static void C_ccall f_7923(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7909)
static void C_ccall f_7909(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5807)
static void C_ccall f_5807(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6959)
static void C_ccall f_6959(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7855)
static void C_ccall f_7855(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_7902)
static void C_ccall f_7902(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7892)
static void C_ccall f_7892(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7859)
static void C_ccall f_7859(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6962)
static void C_ccall f_6962(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7849)
static void C_ccall f_7849(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_7849)
static void C_ccall f_7849r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_7235)
static void C_ccall f_7235(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7358)
static void C_ccall f_7358(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7361)
static void C_ccall f_7361(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7364)
static void C_ccall f_7364(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7367)
static void C_ccall f_7367(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7370)
static void C_ccall f_7370(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7373)
static void C_ccall f_7373(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7376)
static void C_ccall f_7376(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7379)
static void C_ccall f_7379(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7843)
static void C_ccall f_7843(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_7843)
static void C_ccall f_7843r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_7397)
static void C_ccall f_7397(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7400)
static void C_ccall f_7400(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7678)
static void C_fcall f_7678(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_7786)
static void C_ccall f_7786(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7698)
static void C_fcall f_7698(C_word t0,C_word t1) C_noret;
C_noret_decl(f_7707)
static void C_fcall f_7707(C_word t0,C_word t1) C_noret;
C_noret_decl(f_7711)
static void C_ccall f_7711(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7715)
static void C_ccall f_7715(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7723)
static void C_fcall f_7723(C_word t0,C_word t1) C_noret;
C_noret_decl(f_7719)
static void C_ccall f_7719(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7688)
static void C_ccall f_7688(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7403)
static void C_ccall f_7403(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7406)
static void C_ccall f_7406(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7409)
static void C_ccall f_7409(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7412)
static void C_ccall f_7412(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7415)
static void C_ccall f_7415(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7672)
static void C_ccall f_7672(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7571)
static void C_fcall f_7571(C_word t0,C_word t1) C_noret;
C_noret_decl(f_7578)
static void C_ccall f_7578(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7580)
static void C_fcall f_7580(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_7652)
static void C_ccall f_7652(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7604)
static void C_fcall f_7604(C_word t0,C_word t1) C_noret;
C_noret_decl(f_7607)
static void C_ccall f_7607(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7628)
static void C_ccall f_7628(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7594)
static void C_ccall f_7594(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7418)
static void C_ccall f_7418(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7560)
static void C_ccall f_7560(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7548)
static void C_ccall f_7548(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7544)
static void C_ccall f_7544(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7425)
static void C_fcall f_7425(C_word t0,C_word t1) C_noret;
C_noret_decl(f_7382)
static void C_ccall f_7382(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7841)
static void C_ccall f_7841(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7279)
static void C_ccall f_7279(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_7279)
static void C_ccall f_7279r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_7283)
static void C_fcall f_7283(C_word t0,C_word t1) C_noret;
C_noret_decl(f_7325)
static void C_ccall f_7325(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_7288)
static void C_ccall f_7288(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_7294)
static void C_ccall f_7294(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_7320)
static void C_ccall f_7320(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7324)
static void C_ccall f_7324(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7300)
static void C_ccall f_7300(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_7318)
static void C_ccall f_7318(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7315)
static void C_ccall f_7315(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7311)
static void C_ccall f_7311(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7304)
static void C_ccall f_7304(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7273)
static void C_ccall f_7273(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_7267)
static void C_ccall f_7267(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7261)
static void C_ccall f_7261(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_7255)
static void C_ccall f_7255(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_7249)
static void C_ccall f_7249(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_7243)
static void C_ccall f_7243(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_7237)
static void C_ccall f_7237(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_6501)
static void C_ccall f_6501(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6964)
static void C_ccall f_6964(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_6974)
static void C_ccall f_6974(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7205)
static void C_ccall f_7205(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6977)
static void C_ccall f_6977(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6980)
static void C_ccall f_6980(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6992)
static void C_ccall f_6992(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7040)
static void C_fcall f_7040(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_7056)
static void C_ccall f_7056(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7066)
static void C_ccall f_7066(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7183)
static void C_ccall f_7183(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7171)
static void C_ccall f_7171(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_7169)
static void C_ccall f_7169(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7156)
static void C_ccall f_7156(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7110)
static void C_ccall f_7110(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7137)
static void C_ccall f_7137(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7116)
static void C_ccall f_7116(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7050)
static void C_fcall f_7050(C_word t0,C_word t1) C_noret;
C_noret_decl(f_6995)
static void C_ccall f_6995(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7000)
static void C_fcall f_7000(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_7013)
static void C_fcall f_7013(C_word t0,C_word t1) C_noret;
C_noret_decl(f_7222)
static void C_ccall f_7222(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_7213)
static void C_ccall f_7213(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_7221)
static void C_ccall f_7221(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_7224)
static void C_ccall f_7224(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_7224)
static void C_ccall f_7224r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_7232)
static void C_ccall f_7232(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6948)
static void C_ccall f_6948(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6611)
static void C_ccall f_6611(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6952)
static void C_ccall f_6952(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6890)
static void C_ccall f_6890(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_6890)
static void C_ccall f_6890r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_6908)
static void C_fcall f_6908(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6918)
static void C_ccall f_6918(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6894)
static void C_ccall f_6894(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6881)
static void C_ccall f_6881(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6589)
static void C_ccall f_6589(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6885)
static void C_ccall f_6885(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6875)
static void C_ccall f_6875(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6571)
static void C_ccall f_6571(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6866)
static void C_ccall f_6866(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6580)
static void C_ccall f_6580(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6870)
static void C_ccall f_6870(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6803)
static void C_ccall f_6803(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_6803)
static void C_ccall f_6803r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_6828)
static void C_fcall f_6828(C_word t0,C_word t1) C_noret;
C_noret_decl(f_6536)
static void C_ccall f_6536(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6816)
static void C_ccall f_6816(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6635)
static void C_ccall f_6635(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_6635)
static void C_ccall f_6635r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_6754)
static void C_fcall f_6754(C_word t0,C_word t1) C_noret;
C_noret_decl(f_6749)
static void C_fcall f_6749(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6637)
static void C_fcall f_6637(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_6744)
static void C_ccall f_6744(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6748)
static void C_ccall f_6748(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6740)
static void C_ccall f_6740(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6708)
static void C_fcall f_6708(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6733)
static void C_ccall f_6733(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6737)
static void C_ccall f_6737(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6718)
static void C_ccall f_6718(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6697)
static void C_ccall f_6697(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6667)
static void C_fcall f_6667(C_word t0,C_word t1) C_noret;
C_noret_decl(f_6639)
static void C_fcall f_6639(C_word t0,C_word t1) C_noret;
C_noret_decl(f_6616)
static void C_ccall f_6616(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6621)
static void C_ccall f_6621(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6626)
static void C_ccall f_6626(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6594)
static void C_fcall f_6594(C_word t0,C_word t1) C_noret;
C_noret_decl(f_6598)
static void C_ccall f_6598(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6550)
static void C_fcall f_6550(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_6554)
static void C_ccall f_6554(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6541)
static void C_fcall f_6541(C_word t0,C_word t1) C_noret;
C_noret_decl(f_6545)
static void C_ccall f_6545(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6529)
static void C_ccall f_6529(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6526)
static void C_ccall f_6526(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6483)
static void C_ccall f_6483(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6488)
static void C_ccall f_6488(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6469)
static void C_ccall f_6469(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6474)
static void C_ccall f_6474(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6440)
static void C_ccall f_6440(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_6440)
static void C_ccall f_6440r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_6449)
static void C_ccall f_6449(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6454)
static void C_ccall f_6454(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6429)
static void C_ccall f_6429(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6434)
static void C_ccall f_6434(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6389)
static void C_ccall f_6389(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_6389)
static void C_ccall f_6389r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_6419)
static void C_ccall f_6419(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6341)
static void C_ccall f_6341(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6375)
static void C_ccall f_6375(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6321)
static void C_ccall f_6321(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6301)
static void C_ccall f_6301(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6287)
static void C_ccall f_6287(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6277)
static void C_ccall f_6277(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6267)
static void C_ccall f_6267(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6257)
static void C_ccall f_6257(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6247)
static void C_ccall f_6247(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6225)
static void C_ccall f_6225(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_6219)
static void C_ccall f_6219(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_6172)
static void C_ccall f_6172(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6176)
static void C_ccall f_6176(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6192)
static void C_ccall f_6192(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6201)
static void C_ccall f_6201(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6179)
static void C_ccall f_6179(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6163)
static void C_ccall f_6163(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6167)
static void C_ccall f_6167(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5984)
static void C_ccall f_5984(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_5984)
static void C_ccall f_5984r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_6137)
static void C_fcall f_6137(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6150)
static void C_ccall f_6150(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6132)
static void C_ccall f_6132(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5987)
static void C_fcall f_5987(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6129)
static void C_ccall f_6129(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6113)
static void C_ccall f_6113(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6106)
static void C_ccall f_6106(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6102)
static void C_ccall f_6102(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6015)
static void C_ccall f_6015(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6023)
static void C_fcall f_6023(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_6033)
static void C_ccall f_6033(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6036)
static void C_ccall f_6036(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_6018)
static void C_ccall f_6018(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5813)
static void C_ccall f_5813(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_5819)
static void C_ccall f_5819(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5822)
static void C_fcall f_5822(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3625)
static void C_ccall f_3625(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_3638)
static void C_ccall f_3638(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_3645)
static void C_fcall f_3645(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3652)
static void C_ccall f_3652(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3631)
static void C_ccall f_3631(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5826)
static void C_ccall f_5826(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5860)
static void C_ccall f_5860(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5953)
static void C_fcall f_5953(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_5963)
static void C_fcall f_5963(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5866)
static void C_ccall f_5866(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5923)
static void C_fcall f_5923(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_5933)
static void C_fcall f_5933(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5874)
static void C_ccall f_5874(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5888)
static void C_ccall f_5888(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5892)
static void C_ccall f_5892(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5896)
static void C_ccall f_5896(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5900)
static void C_ccall f_5900(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5907)
static void C_ccall f_5907(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5884)
static void C_ccall f_5884(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5877)
static void C_ccall f_5877(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5829)
static void C_ccall f_5829(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4752)
static void C_ccall f_4752(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_4765)
static void C_ccall f_4765(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4815)
static void C_ccall f_4815(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4912)
static void C_ccall f_4912(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4980)
static void C_ccall f_4980(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5237)
static void C_ccall f_5237(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4987)
static void C_fcall f_4987(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5225)
static void C_ccall f_5225(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5176)
static void C_ccall f_5176(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5182)
static void C_ccall f_5182(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5206)
static void C_ccall f_5206(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5202)
static void C_ccall f_5202(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5190)
static void C_ccall f_5190(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4990)
static void C_fcall f_4990(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5152)
static void C_ccall f_5152(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5156)
static void C_ccall f_5156(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4993)
static void C_fcall f_4993(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5129)
static void C_ccall f_5129(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5133)
static void C_ccall f_5133(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4996)
static void C_fcall f_4996(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5106)
static void C_ccall f_5106(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5110)
static void C_ccall f_5110(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4999)
static void C_fcall f_4999(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5031)
static void C_ccall f_5031(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5049)
static void C_ccall f_5049(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5067)
static void C_ccall f_5067(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5085)
static void C_ccall f_5085(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_5002)
static void C_fcall f_5002(C_word t0,C_word t1) C_noret;
C_noret_decl(f_5006)
static void C_ccall f_5006(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4916)
static void C_ccall f_4916(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4920)
static void C_ccall f_4920(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4924)
static void C_ccall f_4924(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4819)
static void C_ccall f_4819(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4823)
static void C_ccall f_4823(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4827)
static void C_ccall f_4827(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4846)
static void C_ccall f_4846(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4850)
static void C_ccall f_4850(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4830)
static void C_fcall f_4830(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4834)
static void C_ccall f_4834(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4769)
static void C_ccall f_4769(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4773)
static void C_ccall f_4773(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4777)
static void C_ccall f_4777(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4759)
static void C_fcall f_4759(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4574)
static void C_fcall f_4574(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4586)
static void C_fcall f_4586(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4605)
static void C_ccall f_4605(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4623)
static void C_fcall f_4623(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_4655)
static void C_ccall f_4655(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4658)
static void C_fcall f_4658(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4651)
static void C_ccall f_4651(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4637)
static void C_ccall f_4637(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4608)
static void C_ccall f_4608(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4553)
static void C_fcall f_4553(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4560)
static void C_ccall f_4560(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4563)
static void C_ccall f_4563(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4569)
static void C_ccall f_4569(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4488)
static void C_fcall f_4488(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_4497)
static void C_fcall f_4497(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_4520)
static void C_ccall f_4520(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4510)
static void C_fcall f_4510(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4444)
static void C_fcall f_4444(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_4432)
static void C_fcall f_4432(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4330)
static void C_fcall f_4330(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4282)
static void C_fcall f_4282(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3663)
static void C_fcall f_3663(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_3667)
static void C_ccall f_3667(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3670)
static void C_ccall f_3670(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4096)
static void C_ccall f_4096(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4092)
static void C_ccall f_4092(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4088)
static void C_ccall f_4088(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3673)
static void C_fcall f_3673(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3796)
static void C_ccall f_3796(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3029)
static void C_ccall f_3029(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3802)
static void C_fcall f_3802(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3045)
static void C_ccall f_3045(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3890)
static void C_fcall f_3890(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3960)
static void C_ccall f_3960(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3061)
static void C_ccall f_3061(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3963)
static void C_fcall f_3963(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3093)
static void C_ccall f_3093(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4041)
static void C_fcall f_4041(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4067)
static void C_ccall f_4067(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_4061)
static void C_ccall f_4061(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4050)
static void C_ccall f_4050(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3992)
static void C_fcall f_3992(C_word t0,C_word t1) C_noret;
C_noret_decl(f_4002)
static void C_ccall f_4002(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4028)
static void C_ccall f_4028(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_4022)
static void C_ccall f_4022(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4005)
static void C_ccall f_4005(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4015)
static void C_ccall f_4015(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_4008)
static void C_fcall f_4008(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3969)
static void C_ccall f_3969(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3978)
static void C_ccall f_3978(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3972)
static void C_fcall f_3972(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3896)
static void C_ccall f_3896(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3914)
static void C_fcall f_3914(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_3947)
static void C_ccall f_3947(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_3933)
static void C_ccall f_3933(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3941)
static void C_ccall f_3941(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3924)
static void C_ccall f_3924(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3899)
static void C_ccall f_3899(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3811)
static void C_ccall f_3811(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3833)
static void C_fcall f_3833(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_3880)
static void C_ccall f_3880(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_3866)
static void C_ccall f_3866(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3874)
static void C_ccall f_3874(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3846)
static void C_ccall f_3846(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3849)
static void C_fcall f_3849(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3814)
static void C_ccall f_3814(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3831)
static void C_ccall f_3831(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3817)
static void C_fcall f_3817(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3688)
static void C_ccall f_3688(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3746)
static void C_ccall f_3746(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3749)
static void C_ccall f_3749(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3770)
static void C_ccall f_3770(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_3781)
static void C_ccall f_3781(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3760)
static void C_ccall f_3760(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3694)
static void C_ccall f_3694(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3704)
static void C_ccall f_3704(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3740)
static void C_ccall f_3740(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3710)
static void C_ccall f_3710(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3725)
static void C_ccall f_3725(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3729)
static void C_ccall f_3729(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3733)
static void C_ccall f_3733(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3717)
static void C_ccall f_3717(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3559)
static void C_fcall f_3559(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3561)
static void C_ccall f_3561(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_3609)
static void C_ccall f_3609(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3565)
static void C_ccall f_3565(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3568)
static void C_fcall f_3568(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3573)
static void C_fcall f_3573(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_3594)
static void C_ccall f_3594(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3551)
static void C_fcall f_3551(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3553)
static void C_ccall f_3553(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_3343)
static void C_fcall f_3343(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_3360)
static void C_ccall f_3360(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3364)
static void C_ccall f_3364(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3310)
static void C_fcall f_3310(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_3317)
static void C_ccall f_3317(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3261)
static void C_ccall f_3261(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3268)
static void C_ccall f_3268(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3326)
static void C_ccall f_3326(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3549)
static void C_ccall f_3549(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3526)
static void C_ccall f_3526(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3542)
static void C_ccall f_3542(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3388)
static void C_ccall f_3388(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3391)
static void C_ccall f_3391(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3415)
static void C_ccall f_3415(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3472)
static void C_ccall f_3472(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3478)
static void C_ccall f_3478(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3487)
static void C_ccall f_3487(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3496)
static void C_ccall f_3496(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3505)
static void C_ccall f_3505(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3514)
static void C_ccall f_3514(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3466)
static void C_ccall f_3466(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3421)
static void C_ccall f_3421(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3427)
static void C_ccall f_3427(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3433)
static void C_ccall f_3433(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3439)
static void C_ccall f_3439(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3445)
static void C_ccall f_3445(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3451)
static void C_ccall f_3451(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3292)
static void C_fcall f_3292(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_3299)
static void C_ccall f_3299(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3282)
static void C_fcall f_3282(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_3270)
static void C_fcall f_3270(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_3238)
static void C_fcall f_3238(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_3245)
static void C_ccall f_3245(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3252)
static void C_ccall f_3252(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3222)
static void C_fcall f_3222(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3229)
static void C_ccall f_3229(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3236)
static void C_ccall f_3236(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3210)
static void C_fcall f_3210(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3192)
static void C_fcall f_3192(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3174)
static void C_fcall f_3174(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3159)
static void C_fcall f_3159(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3153)
static void C_fcall f_3153(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_3141)
static void C_fcall f_3141(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3123)
static void C_fcall f_3123(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3102)
static void C_fcall f_3102(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_3070)
static void C_fcall f_3070(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3077)
static void C_ccall f_3077(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3012)
static void C_fcall f_3012(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_3020)
static void C_ccall f_3020(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_3002)
static void C_fcall f_3002(C_word t0,C_word t1) C_noret;
C_noret_decl(f_3010)
static void C_ccall f_3010(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2996)
static void C_fcall f_2996(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2984)
static void C_fcall f_2984(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2960)
static void C_fcall f_2960(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2876)
static void C_fcall f_2876(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2855)
static void C_fcall f_2855(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_2845)
static void C_fcall f_2845(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2833)
static void C_fcall f_2833(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2804)
static void C_ccall f_2804(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2792)
static void C_fcall f_2792(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2774)
static void C_fcall f_2774(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2756)
static void C_fcall f_2756(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2735)
static void C_ccall f_2735(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_2729)
static void C_ccall f_2729(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2723)
static void C_ccall f_2723(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2704)
static void C_ccall f_2704(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_2704)
static void C_ccall f_2704r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_2685)
static void C_ccall f_2685(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_2685)
static void C_ccall f_2685r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_2679)
static void C_ccall f_2679(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2639)
static void C_ccall f_2639(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_2639)
static void C_ccall f_2639r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_2620)
static void C_ccall f_2620(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_2620)
static void C_ccall f_2620r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_2576)
static void C_ccall f_2576(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_2576)
static void C_ccall f_2576r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_2570)
static void C_ccall f_2570(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2564)
static void C_ccall f_2564(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2558)
static void C_ccall f_2558(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2552)
static void C_ccall f_2552(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_2552)
static void C_ccall f_2552r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_2529)
static void C_ccall f_2529(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2546)
static void C_ccall f_2546(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2471)
static void C_ccall f_2471(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_2471)
static void C_ccall f_2471r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_2523)
static void C_ccall f_2523(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2507)
static void C_ccall f_2507(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2488)
static void C_ccall f_2488(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2383)
static void C_ccall f_2383(C_word c,C_word t0,C_word t1,...) C_noret;
C_noret_decl(f_2383)
static void C_ccall f_2383r(C_word t0,C_word t1,C_word t3) C_noret;
C_noret_decl(f_2429)
static void C_fcall f_2429(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2377)
static void C_ccall f_2377(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2318)
static void C_ccall f_2318(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_2318)
static void C_ccall f_2318r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_2331)
static void C_fcall f_2331(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_2367)
static void C_ccall f_2367(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2312)
static void C_ccall f_2312(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_2312)
static void C_ccall f_2312r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_2217)
static void C_ccall f_2217(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_2217)
static void C_ccall f_2217r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_2221)
static void C_ccall f_2221(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2224)
static void C_ccall f_2224(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2236)
static void C_fcall f_2236(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2258)
static void C_ccall f_2258(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_2211)
static void C_ccall f_2211(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2205)
static void C_ccall f_2205(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2199)
static void C_ccall f_2199(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2193)
static void C_ccall f_2193(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2187)
static void C_ccall f_2187(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2127)
static void C_ccall f_2127(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_2127)
static void C_ccall f_2127r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_2139)
static void C_fcall f_2139(C_word t0,C_word t1) C_noret;
C_noret_decl(f_2134)
static void C_fcall f_2134(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2129)
static void C_fcall f_2129(C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_2108)
static void C_ccall f_2108(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_2108)
static void C_ccall f_2108r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_2102)
static void C_ccall f_2102(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_2096)
static void C_ccall f_2096(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_2014)
static void C_ccall f_2014(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,...) C_noret;
C_noret_decl(f_2014)
static void C_ccall f_2014r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t7) C_noret;
C_noret_decl(f_2028)
static void C_ccall f_2028(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1995)
static void C_ccall f_1995(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,...) C_noret;
C_noret_decl(f_1995)
static void C_ccall f_1995r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t8) C_noret;
C_noret_decl(f_1982)
static void C_fcall f_1982(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1972)
static void C_fcall f_1972(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1961)
static void C_fcall f_1961(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1954)
static void C_fcall f_1954(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1943)
static void C_fcall f_1943(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1905)
static void C_fcall f_1905(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1898)
static void C_fcall f_1898(C_word t0,C_word t1) C_noret;
C_noret_decl(f_1823)
static void C_fcall f_1823(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1789)
static void C_fcall f_1789(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_1762)
static void C_fcall f_1762(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;

C_noret_decl(trf_11989)
static void C_fcall trf_11989(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_11989(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_11989(t0,t1);}

C_noret_decl(trf_10871)
static void C_fcall trf_10871(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_10871(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_10871(t0,t1);}

C_noret_decl(trf_10744)
static void C_fcall trf_10744(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_10744(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_10744(t0,t1,t2);}

C_noret_decl(trf_10408)
static void C_fcall trf_10408(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_10408(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_10408(t0,t1);}

C_noret_decl(trf_9503)
static void C_fcall trf_9503(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_9503(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_9503(t0,t1,t2);}

C_noret_decl(trf_9538)
static void C_fcall trf_9538(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_9538(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_9538(t0,t1);}

C_noret_decl(trf_9562)
static void C_fcall trf_9562(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_9562(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_9562(t0,t1);}

C_noret_decl(trf_9541)
static void C_fcall trf_9541(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_9541(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_9541(t0,t1);}

C_noret_decl(trf_9344)
static void C_fcall trf_9344(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_9344(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_9344(t0,t1);}

C_noret_decl(trf_9162)
static void C_fcall trf_9162(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_9162(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_9162(t0,t1);}

C_noret_decl(trf_9169)
static void C_fcall trf_9169(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_9169(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_9169(t0,t1);}

C_noret_decl(trf_9150)
static void C_fcall trf_9150(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_9150(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_9150(t0,t1);}

C_noret_decl(trf_5300)
static void C_fcall trf_5300(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5300(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5300(t0,t1);}

C_noret_decl(trf_5307)
static void C_fcall trf_5307(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5307(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5307(t0,t1);}

C_noret_decl(trf_5618)
static void C_fcall trf_5618(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5618(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_5618(t0,t1,t2);}

C_noret_decl(trf_5641)
static void C_fcall trf_5641(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5641(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_5641(t0,t1,t2);}

C_noret_decl(trf_5658)
static void C_fcall trf_5658(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5658(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5658(t0,t1);}

C_noret_decl(trf_5661)
static void C_fcall trf_5661(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5661(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5661(t0,t1);}

C_noret_decl(trf_5664)
static void C_fcall trf_5664(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5664(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5664(t0,t1);}

C_noret_decl(trf_5582)
static void C_fcall trf_5582(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5582(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_5582(t0,t1,t2);}

C_noret_decl(trf_5526)
static void C_fcall trf_5526(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5526(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_5526(t0,t1,t2);}

C_noret_decl(trf_5542)
static void C_fcall trf_5542(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5542(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5542(t0,t1);}

C_noret_decl(trf_5323)
static void C_fcall trf_5323(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5323(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5323(t0,t1);}

C_noret_decl(trf_5326)
static void C_fcall trf_5326(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5326(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5326(t0,t1);}

C_noret_decl(trf_8659)
static void C_fcall trf_8659(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8659(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_8659(t0,t1);}

C_noret_decl(trf_8662)
static void C_fcall trf_8662(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8662(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_8662(t0,t1);}

C_noret_decl(trf_8505)
static void C_fcall trf_8505(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8505(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_8505(t0,t1);}

C_noret_decl(trf_8313)
static void C_fcall trf_8313(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8313(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_8313(t0,t1);}

C_noret_decl(trf_8163)
static void C_fcall trf_8163(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8163(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_8163(t0,t1);}

C_noret_decl(trf_8252)
static void C_fcall trf_8252(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8252(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_8252(t0,t1);}

C_noret_decl(trf_8166)
static void C_fcall trf_8166(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8166(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_8166(t0,t1);}

C_noret_decl(trf_8182)
static void C_fcall trf_8182(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8182(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_8182(t0,t1,t2,t3);}

C_noret_decl(trf_8204)
static void C_fcall trf_8204(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8204(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_8204(t0,t1);}

C_noret_decl(trf_8099)
static void C_fcall trf_8099(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8099(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_8099(t0,t1,t2);}

C_noret_decl(trf_8046)
static void C_fcall trf_8046(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_8046(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_8046(t0,t1);}

C_noret_decl(trf_7678)
static void C_fcall trf_7678(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7678(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_7678(t0,t1,t2);}

C_noret_decl(trf_7698)
static void C_fcall trf_7698(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7698(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_7698(t0,t1);}

C_noret_decl(trf_7707)
static void C_fcall trf_7707(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7707(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_7707(t0,t1);}

C_noret_decl(trf_7723)
static void C_fcall trf_7723(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7723(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_7723(t0,t1);}

C_noret_decl(trf_7571)
static void C_fcall trf_7571(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7571(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_7571(t0,t1);}

C_noret_decl(trf_7580)
static void C_fcall trf_7580(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7580(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_7580(t0,t1,t2);}

C_noret_decl(trf_7604)
static void C_fcall trf_7604(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7604(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_7604(t0,t1);}

C_noret_decl(trf_7425)
static void C_fcall trf_7425(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7425(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_7425(t0,t1);}

C_noret_decl(trf_7283)
static void C_fcall trf_7283(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7283(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_7283(t0,t1);}

C_noret_decl(trf_7040)
static void C_fcall trf_7040(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7040(void *dummy){
C_word t4=C_pick(0);
C_word t3=C_pick(1);
C_word t2=C_pick(2);
C_word t1=C_pick(3);
C_word t0=C_pick(4);
C_adjust_stack(-5);
f_7040(t0,t1,t2,t3,t4);}

C_noret_decl(trf_7050)
static void C_fcall trf_7050(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7050(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_7050(t0,t1);}

C_noret_decl(trf_7000)
static void C_fcall trf_7000(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7000(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_7000(t0,t1,t2);}

C_noret_decl(trf_7013)
static void C_fcall trf_7013(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_7013(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_7013(t0,t1);}

C_noret_decl(trf_6908)
static void C_fcall trf_6908(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6908(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_6908(t0,t1,t2);}

C_noret_decl(trf_6828)
static void C_fcall trf_6828(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6828(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_6828(t0,t1);}

C_noret_decl(trf_6754)
static void C_fcall trf_6754(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6754(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_6754(t0,t1);}

C_noret_decl(trf_6749)
static void C_fcall trf_6749(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6749(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_6749(t0,t1,t2);}

C_noret_decl(trf_6637)
static void C_fcall trf_6637(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6637(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_6637(t0,t1,t2,t3);}

C_noret_decl(trf_6708)
static void C_fcall trf_6708(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6708(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_6708(t0,t1,t2);}

C_noret_decl(trf_6667)
static void C_fcall trf_6667(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6667(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_6667(t0,t1);}

C_noret_decl(trf_6639)
static void C_fcall trf_6639(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6639(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_6639(t0,t1);}

C_noret_decl(trf_6594)
static void C_fcall trf_6594(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6594(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_6594(t0,t1);}

C_noret_decl(trf_6550)
static void C_fcall trf_6550(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6550(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_6550(t0,t1,t2,t3);}

C_noret_decl(trf_6541)
static void C_fcall trf_6541(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6541(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_6541(t0,t1);}

C_noret_decl(trf_6137)
static void C_fcall trf_6137(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6137(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_6137(t0,t1,t2);}

C_noret_decl(trf_5987)
static void C_fcall trf_5987(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5987(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_5987(t0,t1,t2);}

C_noret_decl(trf_6023)
static void C_fcall trf_6023(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_6023(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_6023(t0,t1,t2);}

C_noret_decl(trf_5822)
static void C_fcall trf_5822(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5822(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5822(t0,t1);}

C_noret_decl(trf_3645)
static void C_fcall trf_3645(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3645(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3645(t0,t1);}

C_noret_decl(trf_5953)
static void C_fcall trf_5953(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5953(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_5953(t0,t1,t2);}

C_noret_decl(trf_5963)
static void C_fcall trf_5963(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5963(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5963(t0,t1);}

C_noret_decl(trf_5923)
static void C_fcall trf_5923(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5923(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_5923(t0,t1,t2);}

C_noret_decl(trf_5933)
static void C_fcall trf_5933(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5933(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5933(t0,t1);}

C_noret_decl(trf_4987)
static void C_fcall trf_4987(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4987(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4987(t0,t1);}

C_noret_decl(trf_4990)
static void C_fcall trf_4990(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4990(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4990(t0,t1);}

C_noret_decl(trf_4993)
static void C_fcall trf_4993(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4993(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4993(t0,t1);}

C_noret_decl(trf_4996)
static void C_fcall trf_4996(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4996(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4996(t0,t1);}

C_noret_decl(trf_4999)
static void C_fcall trf_4999(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4999(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4999(t0,t1);}

C_noret_decl(trf_5002)
static void C_fcall trf_5002(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_5002(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_5002(t0,t1);}

C_noret_decl(trf_4830)
static void C_fcall trf_4830(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4830(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4830(t0,t1);}

C_noret_decl(trf_4759)
static void C_fcall trf_4759(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4759(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4759(t0,t1);}

C_noret_decl(trf_4574)
static void C_fcall trf_4574(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4574(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4574(t0,t1);}

C_noret_decl(trf_4586)
static void C_fcall trf_4586(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4586(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4586(t0,t1);}

C_noret_decl(trf_4623)
static void C_fcall trf_4623(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4623(void *dummy){
C_word t4=C_pick(0);
C_word t3=C_pick(1);
C_word t2=C_pick(2);
C_word t1=C_pick(3);
C_word t0=C_pick(4);
C_adjust_stack(-5);
f_4623(t0,t1,t2,t3,t4);}

C_noret_decl(trf_4658)
static void C_fcall trf_4658(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4658(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4658(t0,t1);}

C_noret_decl(trf_4553)
static void C_fcall trf_4553(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4553(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4553(t0,t1);}

C_noret_decl(trf_4488)
static void C_fcall trf_4488(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4488(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_4488(t0,t1,t2);}

C_noret_decl(trf_4497)
static void C_fcall trf_4497(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4497(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_4497(t0,t1,t2);}

C_noret_decl(trf_4510)
static void C_fcall trf_4510(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4510(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4510(t0,t1);}

C_noret_decl(trf_4444)
static void C_fcall trf_4444(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4444(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_4444(t0,t1,t2);}

C_noret_decl(trf_4432)
static void C_fcall trf_4432(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4432(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4432(t0,t1);}

C_noret_decl(trf_4330)
static void C_fcall trf_4330(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4330(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4330(t0,t1);}

C_noret_decl(trf_4282)
static void C_fcall trf_4282(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4282(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4282(t0,t1);}

C_noret_decl(trf_3663)
static void C_fcall trf_3663(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3663(void *dummy){
C_word t6=C_pick(0);
C_word t5=C_pick(1);
C_word t4=C_pick(2);
C_word t3=C_pick(3);
C_word t2=C_pick(4);
C_word t1=C_pick(5);
C_word t0=C_pick(6);
C_adjust_stack(-7);
f_3663(t0,t1,t2,t3,t4,t5,t6);}

C_noret_decl(trf_3673)
static void C_fcall trf_3673(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3673(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3673(t0,t1);}

C_noret_decl(trf_3802)
static void C_fcall trf_3802(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3802(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3802(t0,t1);}

C_noret_decl(trf_3890)
static void C_fcall trf_3890(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3890(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3890(t0,t1);}

C_noret_decl(trf_3963)
static void C_fcall trf_3963(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3963(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3963(t0,t1);}

C_noret_decl(trf_4041)
static void C_fcall trf_4041(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4041(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4041(t0,t1);}

C_noret_decl(trf_3992)
static void C_fcall trf_3992(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3992(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3992(t0,t1);}

C_noret_decl(trf_4008)
static void C_fcall trf_4008(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_4008(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_4008(t0,t1);}

C_noret_decl(trf_3972)
static void C_fcall trf_3972(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3972(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3972(t0,t1);}

C_noret_decl(trf_3914)
static void C_fcall trf_3914(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3914(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_3914(t0,t1,t2);}

C_noret_decl(trf_3833)
static void C_fcall trf_3833(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3833(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_3833(t0,t1,t2);}

C_noret_decl(trf_3849)
static void C_fcall trf_3849(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3849(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3849(t0,t1);}

C_noret_decl(trf_3817)
static void C_fcall trf_3817(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3817(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3817(t0,t1);}

C_noret_decl(trf_3559)
static void C_fcall trf_3559(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3559(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3559(t0,t1);}

C_noret_decl(trf_3568)
static void C_fcall trf_3568(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3568(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3568(t0,t1);}

C_noret_decl(trf_3573)
static void C_fcall trf_3573(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3573(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_3573(t0,t1,t2);}

C_noret_decl(trf_3551)
static void C_fcall trf_3551(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3551(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3551(t0,t1);}

C_noret_decl(trf_3343)
static void C_fcall trf_3343(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3343(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_3343(t0,t1,t2,t3);}

C_noret_decl(trf_3310)
static void C_fcall trf_3310(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3310(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_3310(t0,t1,t2,t3);}

C_noret_decl(trf_3292)
static void C_fcall trf_3292(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3292(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_3292(t0,t1,t2,t3);}

C_noret_decl(trf_3282)
static void C_fcall trf_3282(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3282(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_3282(t0,t1,t2,t3);}

C_noret_decl(trf_3270)
static void C_fcall trf_3270(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3270(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_3270(t0,t1,t2);}

C_noret_decl(trf_3238)
static void C_fcall trf_3238(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3238(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_3238(t0,t1,t2);}

C_noret_decl(trf_3222)
static void C_fcall trf_3222(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3222(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3222(t0,t1);}

C_noret_decl(trf_3210)
static void C_fcall trf_3210(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3210(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3210(t0,t1);}

C_noret_decl(trf_3192)
static void C_fcall trf_3192(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3192(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3192(t0,t1);}

C_noret_decl(trf_3174)
static void C_fcall trf_3174(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3174(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3174(t0,t1);}

C_noret_decl(trf_3159)
static void C_fcall trf_3159(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3159(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3159(t0,t1);}

C_noret_decl(trf_3153)
static void C_fcall trf_3153(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3153(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_3153(t0,t1,t2,t3);}

C_noret_decl(trf_3141)
static void C_fcall trf_3141(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3141(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3141(t0,t1);}

C_noret_decl(trf_3123)
static void C_fcall trf_3123(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3123(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3123(t0,t1);}

C_noret_decl(trf_3102)
static void C_fcall trf_3102(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3102(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_3102(t0,t1,t2);}

C_noret_decl(trf_3070)
static void C_fcall trf_3070(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3070(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3070(t0,t1);}

C_noret_decl(trf_3012)
static void C_fcall trf_3012(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3012(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_3012(t0,t1,t2);}

C_noret_decl(trf_3002)
static void C_fcall trf_3002(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_3002(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_3002(t0,t1);}

C_noret_decl(trf_2996)
static void C_fcall trf_2996(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2996(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2996(t0,t1);}

C_noret_decl(trf_2984)
static void C_fcall trf_2984(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2984(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2984(t0,t1);}

C_noret_decl(trf_2960)
static void C_fcall trf_2960(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2960(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_2960(t0,t1,t2);}

C_noret_decl(trf_2876)
static void C_fcall trf_2876(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2876(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2876(t0,t1);}

C_noret_decl(trf_2855)
static void C_fcall trf_2855(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2855(void *dummy){
C_word t5=C_pick(0);
C_word t4=C_pick(1);
C_word t3=C_pick(2);
C_word t2=C_pick(3);
C_word t1=C_pick(4);
C_word t0=C_pick(5);
C_adjust_stack(-6);
f_2855(t0,t1,t2,t3,t4,t5);}

C_noret_decl(trf_2845)
static void C_fcall trf_2845(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2845(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2845(t0,t1);}

C_noret_decl(trf_2833)
static void C_fcall trf_2833(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2833(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2833(t0,t1);}

C_noret_decl(trf_2792)
static void C_fcall trf_2792(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2792(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2792(t0,t1);}

C_noret_decl(trf_2774)
static void C_fcall trf_2774(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2774(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2774(t0,t1);}

C_noret_decl(trf_2756)
static void C_fcall trf_2756(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2756(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2756(t0,t1);}

C_noret_decl(trf_2429)
static void C_fcall trf_2429(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2429(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2429(t0,t1);}

C_noret_decl(trf_2331)
static void C_fcall trf_2331(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2331(void *dummy){
C_word t5=C_pick(0);
C_word t4=C_pick(1);
C_word t3=C_pick(2);
C_word t2=C_pick(3);
C_word t1=C_pick(4);
C_word t0=C_pick(5);
C_adjust_stack(-6);
f_2331(t0,t1,t2,t3,t4,t5);}

C_noret_decl(trf_2236)
static void C_fcall trf_2236(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2236(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_2236(t0,t1,t2);}

C_noret_decl(trf_2139)
static void C_fcall trf_2139(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2139(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_2139(t0,t1);}

C_noret_decl(trf_2134)
static void C_fcall trf_2134(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2134(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_2134(t0,t1,t2);}

C_noret_decl(trf_2129)
static void C_fcall trf_2129(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_2129(void *dummy){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
f_2129(t0,t1,t2,t3);}

C_noret_decl(trf_1982)
static void C_fcall trf_1982(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1982(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1982(t0,t1);}

C_noret_decl(trf_1972)
static void C_fcall trf_1972(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1972(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1972(t0,t1);}

C_noret_decl(trf_1961)
static void C_fcall trf_1961(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1961(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1961(t0,t1,t2);}

C_noret_decl(trf_1954)
static void C_fcall trf_1954(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1954(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1954(t0,t1);}

C_noret_decl(trf_1943)
static void C_fcall trf_1943(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1943(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1943(t0,t1,t2);}

C_noret_decl(trf_1905)
static void C_fcall trf_1905(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1905(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1905(t0,t1);}

C_noret_decl(trf_1898)
static void C_fcall trf_1898(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1898(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1898(t0,t1);}

C_noret_decl(trf_1823)
static void C_fcall trf_1823(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1823(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_1823(t0,t1,t2);}

C_noret_decl(trf_1789)
static void C_fcall trf_1789(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1789(void *dummy){
C_word t6=C_pick(0);
C_word t5=C_pick(1);
C_word t4=C_pick(2);
C_word t3=C_pick(3);
C_word t2=C_pick(4);
C_word t1=C_pick(5);
C_word t0=C_pick(6);
C_adjust_stack(-7);
f_1789(t0,t1,t2,t3,t4,t5,t6);}

C_noret_decl(trf_1762)
static void C_fcall trf_1762(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1762(void *dummy){
C_word t6=C_pick(0);
C_word t5=C_pick(1);
C_word t4=C_pick(2);
C_word t3=C_pick(3);
C_word t2=C_pick(4);
C_word t1=C_pick(5);
C_word t0=C_pick(6);
C_adjust_stack(-7);
f_1762(t0,t1,t2,t3,t4,t5,t6);}

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
C_initialize_lf(lf,401);
lf[1]=C_decode_literal(C_heaptop,"\376B\000\000\033too many optional arguments");
lf[12]=C_h_intern(&lf[12],7,"rescale");
lf[13]=C_h_intern(&lf[13],8,"discrete");
lf[14]=C_h_intern(&lf[14],3,"int");
lf[15]=C_h_intern(&lf[15],8,"quantize");
lf[16]=C_h_intern(&lf[16],8,"decimals");
lf[17]=C_h_intern(&lf[17],15,"rhythm->seconds");
lf[18]=C_decode_literal(C_heaptop,"\376U0.25\000");
lf[19]=C_decode_literal(C_heaptop,"\376U60.0\000");
lf[20]=C_h_intern(&lf[20],9,"\003syserror");
lf[21]=C_h_intern(&lf[21],13,"cents->scaler");
lf[22]=C_h_intern(&lf[22],13,"scaler->cents");
lf[23]=C_h_intern(&lf[23],13,"keynum->hertz");
lf[24]=C_h_intern(&lf[24],10,"keynum->pc");
lf[25]=C_h_intern(&lf[25],13,"hertz->keynum");
lf[26]=C_h_intern(&lf[26],7,"interpl");
lf[27]=C_h_intern(&lf[27],5,"error");
lf[28]=C_decode_literal(C_heaptop,"\376B\000\000\033not an x y coordinate list:");
lf[29]=C_h_intern(&lf[29],3,"err");
lf[30]=C_decode_literal(C_heaptop,"\376B\000\000\033not an x y coordinate list:");
lf[31]=C_decode_literal(C_heaptop,"\376B\000\000\033not an x y coordinate list:");
lf[32]=C_h_intern(&lf[32],6,"interp");
lf[33]=C_h_intern(&lf[33],5,"steps");
lf[34]=C_h_intern(&lf[34],6,"modulo");
lf[35]=C_h_intern(&lf[35],8,"ran-set!");
lf[36]=C_h_intern(&lf[36],3,"ran");
lf[37]=C_decode_literal(C_heaptop,"\376U1.0\000");
lf[38]=C_h_intern(&lf[38],4,"odds");
lf[39]=C_decode_literal(C_heaptop,"\376U1.0\000");
lf[40]=C_decode_literal(C_heaptop,"\376U1.0\000");
lf[41]=C_decode_literal(C_heaptop,"\376U1.0\000");
lf[42]=C_h_intern(&lf[42],5,"pickl");
lf[43]=C_decode_literal(C_heaptop,"\376B\000\000\035cannot pick from empty list: ");
lf[44]=C_h_intern(&lf[44],4,"pick");
lf[45]=C_h_intern(&lf[45],6,"ranlow");
lf[46]=C_h_intern(&lf[46],7,"ranhigh");
lf[47]=C_h_intern(&lf[47],9,"ranmiddle");
lf[48]=C_h_intern(&lf[48],7,"ranbeta");
lf[49]=C_decode_literal(C_heaptop,"\376U0.5\000");
lf[50]=C_decode_literal(C_heaptop,"\376U0.5\000");
lf[51]=C_h_intern(&lf[51],6,"ranexp");
lf[52]=C_h_intern(&lf[52],8,"rangauss");
lf[53]=C_h_intern(&lf[53],9,"rancauchy");
lf[54]=C_h_intern(&lf[54],10,"ranpoisson");
lf[55]=C_h_intern(&lf[55],3,"arg");
lf[56]=C_h_intern(&lf[56],8,"rangamma");
lf[57]=C_h_intern(&lf[57],8,"ranbrown");
lf[58]=C_h_intern(&lf[58],7,"ranpink");
lf[60]=C_h_intern(&lf[60],5,"token");
lf[65]=C_h_intern(&lf[65],1,"t");
lf[70]=C_h_intern(&lf[70],4,"rule");
lf[73]=C_h_intern(&lf[73],14,"hash-table-ref");
lf[74]=C_h_intern(&lf[74],22,"hash-table-ref/default");
lf[80]=C_h_intern(&lf[80],1,"*");
lf[82]=C_h_intern(&lf[82],11,"parse-error");
lf[86]=C_h_intern(&lf[86],10,"parse-unit");
lf[98]=C_decode_literal(C_heaptop,"\376B\000\000\014no info for ");
lf[100]=C_h_intern(&lf[100],14,"string->symbol");
lf[101]=C_h_intern(&lf[101],4,"expt");
lf[102]=C_h_intern(&lf[102],5,"equal");
lf[103]=C_h_intern(&lf[103],3,"and");
lf[104]=C_h_intern(&lf[104],2,"or");
lf[105]=C_h_intern(&lf[105],3,"not");
lf[106]=C_h_intern(&lf[106],15,"string->keyword");
lf[107]=C_decode_literal(C_heaptop,"\376B\000\0005emit-token-unit: dont know how to emit slotref token ");
lf[108]=C_decode_literal(C_heaptop,"\376B\000\000\047emit-token-unit: dont know how to emit ");
lf[111]=C_decode_literal(C_heaptop,"\376B\000\000\033emit: dont know how to emit");
lf[115]=C_h_intern(&lf[115],6,"append");
lf[118]=C_decode_literal(C_heaptop,"\376B\000\000\035Not a token type or rule type");
lf[119]=C_h_intern(&lf[119],7,"reverse");
lf[120]=C_decode_literal(C_heaptop,"\376B\000\000\047Pattern opr not one of and, or, *, +, @");
lf[121]=C_h_intern(&lf[121],1,"@");
lf[122]=C_h_intern(&lf[122],1,"+");
lf[123]=C_decode_literal(C_heaptop,"\376B\000\000\047Not a pattern value or pattern operator");
lf[124]=C_h_intern(&lf[124],3,"max");
lf[125]=C_h_intern(&lf[125],6,"printf");
lf[126]=C_decode_literal(C_heaptop,"\376B\000\000!~%parse[~A]: pattern=~S tokens=~S");
lf[131]=C_h_intern(&lf[131],4,"set!");
lf[132]=C_h_intern(&lf[132],2,">=");
lf[133]=C_h_intern(&lf[133],6,"gensym");
lf[134]=C_decode_literal(C_heaptop,"\376B\000\000\004stop");
lf[135]=C_decode_literal(C_heaptop,"\376B\000\000\004temp");
lf[136]=C_h_intern(&lf[136],5,"begin");
lf[137]=C_h_intern(&lf[137],2,"if");
lf[138]=C_decode_literal(C_heaptop,"\376B\000\000\004bool");
lf[139]=C_h_intern(&lf[139],5,"fifth");
lf[140]=C_h_intern(&lf[140],3,"cdr");
lf[141]=C_h_intern(&lf[141],5,"null\077");
lf[142]=C_h_intern(&lf[142],3,"car");
lf[143]=C_decode_literal(C_heaptop,"\376B\000\000\004tail");
lf[144]=C_h_intern(&lf[144],1,">");
lf[145]=C_h_intern(&lf[145],2,"<=");
lf[146]=C_h_intern(&lf[146],1,"-");
lf[147]=C_h_intern(&lf[147],1,"<");
lf[148]=C_decode_literal(C_heaptop,"\376B\000\000\004goal");
lf[149]=C_decode_literal(C_heaptop,"\376B\000\000\004from");
lf[150]=C_decode_literal(C_heaptop,"\376B\000\000\004step");
lf[154]=C_h_intern(&lf[154],3,"sal");
lf[155]=C_h_intern(&lf[155],11,"print-error");
lf[156]=C_h_intern(&lf[156],13,"string-append");
lf[157]=C_decode_literal(C_heaptop,"\376B\000\000\013>>> Error: ");
lf[158]=C_h_intern(&lf[158],11,"make-string");
lf[159]=C_h_intern(&lf[159],9,"substring");
lf[160]=C_h_intern(&lf[160],2,"pp");
lf[161]=C_h_intern(&lf[161],4,"eval");
lf[162]=C_h_intern(&lf[162],7,"\000syntax");
lf[163]=C_h_intern(&lf[163],7,"\000scheme");
lf[164]=C_decode_literal(C_heaptop,"\376B\000\000\023Illegal statement: ");
lf[165]=C_h_intern(&lf[165],7,"call/cc");
lf[166]=C_h_intern(&lf[166],7,"\003sysmap");
lf[167]=C_h_intern(&lf[167],9,"sal:print");
lf[168]=C_h_intern(&lf[168],13,"print-message");
lf[169]=C_decode_literal(C_heaptop,"\376B\000\000\002{}");
lf[170]=C_decode_literal(C_heaptop,"\376B\000\000\001}");
lf[171]=C_decode_literal(C_heaptop,"\376B\000\000\001 ");
lf[172]=C_decode_literal(C_heaptop,"\376B\000\000\001{");
lf[173]=C_decode_literal(C_heaptop,"\376B\000\000\002#t");
lf[174]=C_h_intern(&lf[174],7,"sprintf");
lf[175]=C_decode_literal(C_heaptop,"\376B\000\000\002~S");
lf[176]=C_decode_literal(C_heaptop,"\376B\000\000\002#f");
lf[177]=C_decode_literal(C_heaptop,"\376B\000\000\001\012");
lf[178]=C_h_intern(&lf[178],9,"sal:chdir");
lf[179]=C_h_intern(&lf[179],16,"change-directory");
lf[180]=C_h_intern(&lf[180],8,"sal:load");
lf[181]=C_h_intern(&lf[181],13,"load-sal-file");
lf[182]=C_h_intern(&lf[182],4,"load");
lf[183]=C_h_intern(&lf[183],15,"\003syssubstring=\077");
lf[184]=C_decode_literal(C_heaptop,"\376B\000\000\004.sal");
lf[185]=C_decode_literal(C_heaptop,"\376B\000\000\021>>> Error: file \042");
lf[186]=C_decode_literal(C_heaptop,"\376B\000\000\020\042does not exist\012");
lf[187]=C_h_intern(&lf[187],12,"file-exists\077");
lf[188]=C_h_intern(&lf[188],8,"sal:open");
lf[189]=C_decode_literal(C_heaptop,"\376B\000\000)>>> Error: open command not implemented.\012");
lf[190]=C_h_intern(&lf[190],10,"sal:output");
lf[191]=C_decode_literal(C_heaptop,"\376B\000\000+>>> Error: output command not implemented.\012");
lf[192]=C_h_intern(&lf[192],5,"first");
lf[193]=C_h_intern(&lf[193],6,"second");
lf[194]=C_h_intern(&lf[194],4,"cadr");
lf[195]=C_h_intern(&lf[195],5,"third");
lf[196]=C_h_intern(&lf[196],5,"caddr");
lf[197]=C_h_intern(&lf[197],6,"fourth");
lf[198]=C_h_intern(&lf[198],6,"cadddr");
lf[199]=C_h_intern(&lf[199],5,"sixth");
lf[200]=C_h_intern(&lf[200],7,"seventh");
lf[201]=C_h_intern(&lf[201],6,"eighth");
lf[202]=C_h_intern(&lf[202],5,"ninth");
lf[203]=C_h_intern(&lf[203],5,"tenth");
lf[204]=C_h_intern(&lf[204],4,"last");
lf[205]=C_h_intern(&lf[205],7,"butlast");
lf[206]=C_h_intern(&lf[206],5,"list*");
lf[207]=C_decode_literal(C_heaptop,"\376B\000\000&>>> Error: too few arguments to list*.");
lf[208]=C_h_intern(&lf[208],17,"current-directory");
lf[209]=C_h_intern(&lf[209],17,"\003syspeek-c-string");
lf[210]=C_decode_literal(C_heaptop,"\376B\000\000\002~/");
lf[211]=C_h_intern(&lf[211],17,"\003sysmake-c-string");
lf[212]=C_h_intern(&lf[212],25,"current-time-milliseconds");
lf[213]=C_h_intern(&lf[213],20,"current-time-seconds");
lf[215]=C_h_intern(&lf[215],6,"\003sysgc");
lf[218]=C_h_intern(&lf[218],6,"sprout");
lf[219]=C_h_intern(&lf[219],3,"now");
lf[220]=C_h_intern(&lf[220],11,"time-format");
lf[221]=C_decode_literal(C_heaptop,"\376U1.0\000");
lf[222]=C_decode_literal(C_heaptop,"\376U1.0\000");
lf[223]=C_h_intern(&lf[223],1,"m");
lf[224]=C_decode_literal(C_heaptop,"\376B\000\000\021not a time-format");
lf[225]=C_h_intern(&lf[225],1,"s");
lf[226]=C_h_intern(&lf[226],5,"pause");
lf[227]=C_h_intern(&lf[227],7,"paused\077");
lf[228]=C_h_intern(&lf[228],4,"cont");
lf[229]=C_h_intern(&lf[229],4,"stop");
lf[230]=C_decode_literal(C_heaptop,"\376B\000\000\021Not an integer id");
lf[231]=C_h_intern(&lf[231],4,"hush");
lf[233]=C_h_intern(&lf[233],11,"expand-send");
lf[234]=C_decode_literal(C_heaptop,"\376B\000\000\003~A:");
lf[235]=C_h_intern(&lf[235],15,"keyword->string");
lf[236]=C_decode_literal(C_heaptop,"\376B\000\000\031~S duplicate keyword \047~S\047");
lf[237]=C_decode_literal(C_heaptop,"\376B\000\000!~S missing value for keyword \047~A\047");
lf[238]=C_decode_literal(C_heaptop,"\376B\000\000/~S invalid keyword \047~A\047~%Available keywords: ~A");
lf[239]=C_decode_literal(C_heaptop,"\376B\000\000 ~S expected keyword but got \047~S\047");
lf[240]=C_h_intern(&lf[240],8,"keyword\077");
lf[241]=C_decode_literal(C_heaptop,"\376B\000\000#~S expected ~A arguments but got ~A");
lf[242]=C_decode_literal(C_heaptop,"\376B\000\000\030~S is an invalid message");
lf[243]=C_h_intern(&lf[243],14,"symbol->string");
lf[244]=C_h_intern(&lf[244],7,"mp:note");
lf[245]=C_h_intern(&lf[245],5,"mp:on");
lf[246]=C_decode_literal(C_heaptop,"\376B\000\000!message function not implemented.");
lf[247]=C_h_intern(&lf[247],6,"mp:off");
lf[248]=C_decode_literal(C_heaptop,"\376B\000\000!message function not implemented.");
lf[249]=C_h_intern(&lf[249],7,"mp:prog");
lf[250]=C_decode_literal(C_heaptop,"\376B\000\000!message function not implemented.");
lf[251]=C_h_intern(&lf[251],7,"mp:ctrl");
lf[252]=C_decode_literal(C_heaptop,"\376B\000\000!message function not implemented.");
lf[253]=C_h_intern(&lf[253],9,"mp:alloff");
lf[254]=C_decode_literal(C_heaptop,"\376B\000\000!message function not implemented.");
lf[255]=C_h_intern(&lf[255],8,"mp:micro");
lf[256]=C_decode_literal(C_heaptop,"\376B\000\000!message function not implemented.");
lf[257]=C_h_intern(&lf[257],9,"mp:inhook");
lf[258]=C_decode_literal(C_heaptop,"\376B\000\000*>>> Error: ~A~%    Aborting MIDI inhook.~%");
lf[259]=C_h_intern(&lf[259],27,"condition-property-accessor");
lf[260]=C_h_intern(&lf[260],3,"exn");
lf[261]=C_h_intern(&lf[261],7,"message");
lf[262]=C_h_intern(&lf[262],22,"with-exception-handler");
lf[263]=C_h_intern(&lf[263],30,"call-with-current-continuation");
lf[264]=C_h_intern(&lf[264],14,"return-to-host");
lf[265]=C_h_intern(&lf[265],4,"else");
lf[266]=C_h_intern(&lf[266],4,"cond");
lf[267]=C_h_intern(&lf[267],6,"lambda");
lf[268]=C_h_intern(&lf[268],7,"elapsed");
lf[269]=C_h_intern(&lf[269],1,"x");
lf[270]=C_h_intern(&lf[270],4,"wait");
lf[271]=C_h_intern(&lf[271],4,"let*");
lf[272]=C_h_intern(&lf[272],5,"quote");
lf[273]=C_decode_literal(C_heaptop,"\376B\000\0000>>> Error: ~A~%    Aborting process at time ~S~%");
lf[274]=C_h_intern(&lf[274],10,"\003sysappend");
lf[275]=C_h_intern(&lf[275],6,"safety");
lf[276]=C_h_intern(&lf[276],4,"cdar");
lf[277]=C_decode_literal(C_heaptop,"\376B\000\000\023unknown declaration");
lf[278]=C_h_intern(&lf[278],4,"caar");
lf[279]=C_decode_literal(C_heaptop,"\376B\000\000\037declaration not list (decl val)");
lf[280]=C_h_intern(&lf[280],7,"declare");
lf[281]=C_h_intern(&lf[281],5,"\000null");
lf[282]=C_decode_literal(C_heaptop,"\376B\000\000)binding clause not list (var init [step])");
lf[283]=C_decode_literal(C_heaptop,"\376B\000\000$go stopping clause missing test form");
lf[284]=C_decode_literal(C_heaptop,"\376B\000\000\035go stopping clause not a list");
lf[285]=C_decode_literal(C_heaptop,"\376B\000\000\026go bindings not a list");
lf[286]=C_h_intern(&lf[286],18,"\003sysregister-macro");
lf[287]=C_h_intern(&lf[287],2,"go");
lf[288]=C_h_intern(&lf[288],15,"hash-table-set!");
lf[289]=C_decode_literal(C_heaptop,"\376B\000\000\011mp:inhook");
lf[290]=C_decode_literal(C_heaptop,"\376\003\000\000\002\376\001\000\000\011mp:inhook\376\003\000\000\002\376\003\000\000\002\376\001\000\000\005\000func\376\003\000\000\002\376\377\006\000\376\377\016\376\003\000\000\002\376\003\000\000\002\376\001\000\000\006:chans\376\003\000\000\002\376\377\001"
"\000\000\000\000\376\377\016\376\003\000\000\002\376\003\000\000\002\376\001\000\000\005:filt\376\003\000\000\002\376\377\001\000\000\000\000\376\377\016\376\377\016");
lf[291]=C_decode_literal(C_heaptop,"\376B\000\000\010mp:micro");
lf[292]=C_decode_literal(C_heaptop,"\376\003\000\000\002\376\001\000\000\010mp:micro\376\003\000\000\002\376\003\000\000\002\376\001\000\000\005\000divs\376\003\000\000\002\376\377\001\000\000\000\001\376\377\016\376\377\016");
lf[293]=C_decode_literal(C_heaptop,"\376B\000\000\011mp:alloff");
lf[294]=C_decode_literal(C_heaptop,"\376\003\000\000\002\376\001\000\000\011mp:alloff\376\377\016");
lf[295]=C_decode_literal(C_heaptop,"\376B\000\000\007mp:ctrl");
lf[296]=C_decode_literal(C_heaptop,"\376\003\000\000\002\376\001\000\000\007mp:ctrl\376\003\000\000\002\376\003\000\000\002\376\001\000\000\005\000wait\376\003\000\000\002\376\377\001\000\000\000\000\376\377\016\376\003\000\000\002\376\003\000\000\002\376\001\000\000\005\000ctrl\376\003\000\000\002\376\377\001"
"\000\000\000<\376\377\016\376\003\000\000\002\376\003\000\000\002\376\001\000\000\004\000val\376\003\000\000\002\376\377\001\000\000\000\000\376\377\016\376\003\000\000\002\376\003\000\000\002\376\001\000\000\005\000chan\376\003\000\000\002\376\377\001\000\000\000\000\376\377\016\376\377\016");
lf[297]=C_decode_literal(C_heaptop,"\376B\000\000\007mp:prog");
lf[298]=C_decode_literal(C_heaptop,"\376\003\000\000\002\376\001\000\000\007mp:prog\376\003\000\000\002\376\003\000\000\002\376\001\000\000\005\000wait\376\003\000\000\002\376\377\001\000\000\000\000\376\377\016\376\003\000\000\002\376\003\000\000\002\376\001\000\000\005\000prog\376\003\000\000\002\376\377\001"
"\000\000\000<\376\377\016\376\003\000\000\002\376\003\000\000\002\376\001\000\000\005\000chan\376\003\000\000\002\376\377\001\000\000\000\000\376\377\016\376\377\016");
lf[299]=C_decode_literal(C_heaptop,"\376B\000\000\006mp:off");
lf[300]=C_decode_literal(C_heaptop,"\376\003\000\000\002\376\001\000\000\006mp:off\376\003\000\000\002\376\003\000\000\002\376\001\000\000\005\000wait\376\003\000\000\002\376\377\001\000\000\000\000\376\377\016\376\003\000\000\002\376\003\000\000\002\376\001\000\000\004\000key\376\003\000\000\002\376\377\001\000\000"
"\000<\376\377\016\376\003\000\000\002\376\003\000\000\002\376\001\000\000\004\000vel\376\003\000\000\002\376\377\001\000\000\000@\376\377\016\376\003\000\000\002\376\003\000\000\002\376\001\000\000\005\000chan\376\003\000\000\002\376\377\001\000\000\000\000\376\377\016\376\377\016");
lf[301]=C_decode_literal(C_heaptop,"\376B\000\000\005mp:on");
lf[302]=C_decode_literal(C_heaptop,"\376\003\000\000\002\376\001\000\000\005mp:on\376\003\000\000\002\376\003\000\000\002\376\001\000\000\005\000wait\376\003\000\000\002\376\377\001\000\000\000\000\376\377\016\376\003\000\000\002\376\003\000\000\002\376\001\000\000\004\000key\376\003\000\000\002\376\377\001\000\000\000"
"<\376\377\016\376\003\000\000\002\376\003\000\000\002\376\001\000\000\004\000vel\376\003\000\000\002\376\377\001\000\000\000@\376\377\016\376\003\000\000\002\376\003\000\000\002\376\001\000\000\005\000chan\376\003\000\000\002\376\377\001\000\000\000\000\376\377\016\376\377\016");
lf[303]=C_decode_literal(C_heaptop,"\376B\000\000\007mp:note");
lf[304]=C_decode_literal(C_heaptop,"\376\003\000\000\002\376\001\000\000\007mp:note\376\003\000\000\002\376\003\000\000\002\376\001\000\000\005\000wait\376\003\000\000\002\376\377\001\000\000\000\000\376\377\016\376\003\000\000\002\376\003\000\000\002\376\001\000\000\004\000dur\376\003\000\000\002\376U0."
"5\000\376\377\016\376\003\000\000\002\376\003\000\000\002\376\001\000\000\004\000key\376\003\000\000\002\376\377\001\000\000\000<\376\377\016\376\003\000\000\002\376\003\000\000\002\376\001\000\000\004\000amp\376\003\000\000\002\376U0.5\000\376\377\016\376\003\000\000\002\376\003\000"
"\000\002\376\001\000\000\005\000chan\376\003\000\000\002\376\377\001\000\000\000\000\376\377\016\376\377\016");
lf[305]=C_h_intern(&lf[305],4,"send");
lf[306]=C_h_intern(&lf[306],10,"*messages*");
lf[307]=C_decode_literal(C_heaptop,"\376B\000\0003message function not string, symbol or list of both");
lf[308]=C_h_intern(&lf[308],19,"define-send-message");
lf[309]=C_h_intern(&lf[309],15,"make-hash-table");
lf[310]=C_h_intern(&lf[310],6,"equal\077");
lf[311]=C_decode_literal(C_heaptop,"\376B\000\000\030SalStatementSequenceRule");
lf[312]=C_decode_literal(C_heaptop,"\376B\000\000\020SalStatementRule");
lf[313]=C_h_intern(&lf[313],6,"define");
lf[314]=C_decode_literal(C_heaptop,"\376B\000\000\017Variable: ~A = ");
lf[315]=C_decode_literal(C_heaptop,"\376B\000\000\002)\012");
lf[316]=C_decode_literal(C_heaptop,"\376B\000\000\002, ");
lf[317]=C_decode_literal(C_heaptop,"\376B\000\000\002 (");
lf[318]=C_decode_literal(C_heaptop,"\376B\000\000\012Function: ");
lf[319]=C_h_intern(&lf[319],7,"\000return");
lf[320]=C_h_intern(&lf[320],6,"return");
lf[321]=C_h_intern(&lf[321],9,"\000function");
lf[322]=C_decode_literal(C_heaptop,"\376B\000\000\011Process: ");
lf[323]=C_h_intern(&lf[323],8,"\000process");
lf[324]=C_decode_literal(C_heaptop,"\376B\000\000\003...");
lf[325]=C_decode_literal(C_heaptop,"\376B\000\000\026SalDefineStatementRule");
lf[326]=C_decode_literal(C_heaptop,"\376B\000\000\016SalFunDeclRule");
lf[327]=C_decode_literal(C_heaptop,"\376B\000\000/>>> Error: ~A~%    process aborted at time ~S~%");
lf[328]=C_decode_literal(C_heaptop,"\376B\000\000\005abort");
lf[329]=C_decode_literal(C_heaptop,"\376B\000\000\005error");
lf[330]=C_decode_literal(C_heaptop,"\376B\000\000\004wait");
lf[331]=C_decode_literal(C_heaptop,"\376B\000\000\004time");
lf[332]=C_h_intern(&lf[332],2,"do");
lf[333]=C_h_intern(&lf[333],5,"\000loop");
lf[334]=C_h_intern(&lf[334],4,"\000run");
lf[335]=C_decode_literal(C_heaptop,"\376B\000\000\035run statement outside process");
lf[336]=C_decode_literal(C_heaptop,"\376B\000\000\024SalLoopStatementRule");
lf[337]=C_decode_literal(C_heaptop,"\376B\000\000\022SalTerminationRule");
lf[338]=C_decode_literal(C_heaptop,"\376B\000\000\017SalSteppingRule");
lf[339]=C_decode_literal(C_heaptop,"\376B\000\000\002#f");
lf[340]=C_decode_literal(C_heaptop,"\376B\000\000\002#f");
lf[341]=C_decode_literal(C_heaptop,"\376B\000\000\022SalConditionalRule");
lf[342]=C_decode_literal(C_heaptop,"\376B\000\000\014SalBlockRule");
lf[343]=C_h_intern(&lf[343],9,"list-tail");
lf[344]=C_h_intern(&lf[344],8,"set-car!");
lf[345]=C_h_intern(&lf[345],8,"list-ref");
lf[346]=C_h_intern(&lf[346],4,"list");
lf[347]=C_h_intern(&lf[347],4,"cons");
lf[348]=C_h_intern(&lf[348],3,"min");
lf[349]=C_decode_literal(C_heaptop,"\376B\000\000\021SalAssignmentRule");
lf[350]=C_decode_literal(C_heaptop,"\376B\000\000\015SalAssignRule");
lf[351]=C_h_intern(&lf[351],9,"\000bindings");
lf[352]=C_decode_literal(C_heaptop,"\376B\000\000\017SalBindingsRule");
lf[353]=C_decode_literal(C_heaptop,"\376B\000\000\002#f");
lf[354]=C_decode_literal(C_heaptop,"\376B\000\000\013SalBindRule");
lf[355]=C_decode_literal(C_heaptop,"\376B\000\000!return statement outside function");
lf[356]=C_decode_literal(C_heaptop,"\376B\000\000\025SalFunctionReturnRule");
lf[357]=C_decode_literal(C_heaptop,"\376B\000\000 wait statement outside run block");
lf[358]=C_decode_literal(C_heaptop,"\376B\000\000\022SalProcessWaitRule");
lf[359]=C_decode_literal(C_heaptop,"\376\003\000\000\002\376\001\000\000\006fix-me\376\003\000\000\002\376\001\000\000\004plot\376\377\016");
lf[360]=C_decode_literal(C_heaptop,"\376B\000\000\024SalPlotStatementRule");
lf[361]=C_decode_literal(C_heaptop,"\376B\000\000\026SalOutputStatementRule");
lf[362]=C_decode_literal(C_heaptop,"\376B\000\000\026SalSystemStatementRule");
lf[363]=C_h_intern(&lf[363],10,"sal:system");
lf[364]=C_decode_literal(C_heaptop,"\376B\000\000\025SalChdirStatementRule");
lf[365]=C_decode_literal(C_heaptop,"\376B\000\000\024SalLoadStatementRule");
lf[366]=C_decode_literal(C_heaptop,"\376B\000\000\024SalExecStatementRule");
lf[367]=C_decode_literal(C_heaptop,"\376B\000\000\024SalSendStatementRule");
lf[368]=C_decode_literal(C_heaptop,"\376B\000\000\026SalSproutStatementRule");
lf[369]=C_decode_literal(C_heaptop,"\376B\000\000\025SalPrintStatementRule");
lf[370]=C_decode_literal(C_heaptop,"\376B\000\000\014SalSexprRule");
lf[371]=C_decode_literal(C_heaptop,"\376B\000\000\013SalTermRule");
lf[372]=C_decode_literal(C_heaptop,"\376B\000\000\014SalMexprRule");
lf[373]=C_decode_literal(C_heaptop,"\376B\000\000\011SalOpRule");
lf[374]=C_decode_literal(C_heaptop,"\376B\000\000\016SalFuncallRule");
lf[375]=C_decode_literal(C_heaptop,"\376B\000\000\016SalFunargsRule");
lf[376]=C_decode_literal(C_heaptop,"\376B\000\000\014SalKargsRule");
lf[377]=C_decode_literal(C_heaptop,"\376B\000\000\014SalPargsRule");
lf[378]=C_decode_literal(C_heaptop,"\376B\000\000\015SalIfExprRule");
lf[379]=C_decode_literal(C_heaptop,"\376B\000\000\013SalArefRule");
lf[380]=C_decode_literal(C_heaptop,"\376B\000\000\012SalEltRule");
lf[381]=C_h_intern(&lf[381],7,"unquote");
lf[382]=C_h_intern(&lf[382],16,"unquote-splicing");
lf[383]=C_h_intern(&lf[383],5,"\000list");
lf[384]=C_h_intern(&lf[384],8,"\000unquote");
lf[385]=C_decode_literal(C_heaptop,"\376B\000\000\023#$ outside of list.");
lf[386]=C_decode_literal(C_heaptop,"\376B\000\000\023#^ outside of list.");
lf[387]=C_decode_literal(C_heaptop,"\376B\000\000\016SalUnquoteRule");
lf[388]=C_h_intern(&lf[388],10,"quasiquote");
lf[389]=C_decode_literal(C_heaptop,"\376B\000\000\013SalListRule");
lf[390]=C_decode_literal(C_heaptop,"\376B\000\000\013SalAtomRule");
lf[391]=C_decode_literal(C_heaptop,"\376B\000\000\013SalBoolRule");
lf[392]=C_decode_literal(C_heaptop,"\376B\000\000\015SalNumberRule");
lf[393]=C_h_intern(&lf[393],7,"fprintf");
lf[394]=C_decode_literal(C_heaptop,"\376B\000\000\007#<u ~A>");
lf[395]=C_decode_literal(C_heaptop,"\376B\000\000\010#<u x~X>");
lf[396]=C_h_intern(&lf[396],27,"\003sysregister-record-printer");
lf[397]=C_decode_literal(C_heaptop,"\376B\000\000\030#<parse-error ~S (@ ~S)>");
lf[398]=C_decode_literal(C_heaptop,"\376B\000\000\007#<r ~A>");
lf[399]=C_h_intern(&lf[399],3,"eq\077");
lf[400]=C_decode_literal(C_heaptop,"\376B\000\000\013#<t x~X ~S>");
C_register_lf2(lf,401,create_ptable());
t2=C_mutate(&lf[0],lf[1]);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1751,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_library_toplevel(2,C_SCHEME_UNDEFINED,t3);}

/* k1749 */
static void C_ccall f_1751(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1751,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1754,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_eval_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k1752 in k1749 */
static void C_ccall f_1754(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1754,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1757,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k1755 in k1752 in k1749 */
static void C_ccall f_1757(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1757,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1760,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_1760(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_1760,2,t0,t1);}
t2=C_mutate(&lf[2],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1762,a[2]=((C_word)li0),tmp=(C_word)a,a+=3,tmp));
t3=C_mutate(&lf[3],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1789,a[2]=((C_word)li1),tmp=(C_word)a,a+=3,tmp));
t4=C_mutate(&lf[4],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1823,a[2]=((C_word)li2),tmp=(C_word)a,a+=3,tmp));
t5=C_mutate(&lf[5],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1898,a[2]=((C_word)li3),tmp=(C_word)a,a+=3,tmp));
t6=C_mutate(&lf[6],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1905,a[2]=((C_word)li4),tmp=(C_word)a,a+=3,tmp));
t7=C_mutate(&lf[7],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1943,a[2]=((C_word)li5),tmp=(C_word)a,a+=3,tmp));
t8=C_mutate(&lf[8],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1954,a[2]=((C_word)li6),tmp=(C_word)a,a+=3,tmp));
t9=C_mutate(&lf[9],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1961,a[2]=((C_word)li7),tmp=(C_word)a,a+=3,tmp));
t10=C_mutate(&lf[10],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1972,a[2]=((C_word)li8),tmp=(C_word)a,a+=3,tmp));
t11=C_mutate(&lf[11],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1982,a[2]=((C_word)li9),tmp=(C_word)a,a+=3,tmp));
t12=C_mutate((C_word*)lf[12]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1995,a[2]=((C_word)li10),tmp=(C_word)a,a+=3,tmp));
t13=C_mutate((C_word*)lf[13]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2014,a[2]=((C_word)li11),tmp=(C_word)a,a+=3,tmp));
t14=C_mutate((C_word*)lf[14]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2096,a[2]=((C_word)li12),tmp=(C_word)a,a+=3,tmp));
t15=C_mutate((C_word*)lf[15]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2102,a[2]=((C_word)li13),tmp=(C_word)a,a+=3,tmp));
t16=C_mutate((C_word*)lf[16]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2108,a[2]=((C_word)li14),tmp=(C_word)a,a+=3,tmp));
t17=C_mutate((C_word*)lf[17]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2127,a[2]=((C_word)li18),tmp=(C_word)a,a+=3,tmp));
t18=C_mutate((C_word*)lf[21]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2187,a[2]=((C_word)li19),tmp=(C_word)a,a+=3,tmp));
t19=C_mutate((C_word*)lf[22]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2193,a[2]=((C_word)li20),tmp=(C_word)a,a+=3,tmp));
t20=C_mutate((C_word*)lf[23]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2199,a[2]=((C_word)li21),tmp=(C_word)a,a+=3,tmp));
t21=C_mutate((C_word*)lf[24]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2205,a[2]=((C_word)li22),tmp=(C_word)a,a+=3,tmp));
t22=C_mutate((C_word*)lf[25]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2211,a[2]=((C_word)li23),tmp=(C_word)a,a+=3,tmp));
t23=C_mutate((C_word*)lf[26]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2217,a[2]=((C_word)li25),tmp=(C_word)a,a+=3,tmp));
t24=C_mutate((C_word*)lf[32]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2312,a[2]=((C_word)li26),tmp=(C_word)a,a+=3,tmp));
t25=C_mutate((C_word*)lf[33]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2318,a[2]=((C_word)li28),tmp=(C_word)a,a+=3,tmp));
t26=C_mutate((C_word*)lf[35]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2377,a[2]=((C_word)li29),tmp=(C_word)a,a+=3,tmp));
t27=C_mutate((C_word*)lf[36]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2383,a[2]=((C_word)li30),tmp=(C_word)a,a+=3,tmp));
t28=C_mutate((C_word*)lf[38]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2471,a[2]=((C_word)li31),tmp=(C_word)a,a+=3,tmp));
t29=C_mutate((C_word*)lf[42]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2529,a[2]=((C_word)li32),tmp=(C_word)a,a+=3,tmp));
t30=C_mutate((C_word*)lf[44]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2552,a[2]=((C_word)li33),tmp=(C_word)a,a+=3,tmp));
t31=C_mutate((C_word*)lf[45]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2558,a[2]=((C_word)li34),tmp=(C_word)a,a+=3,tmp));
t32=C_mutate((C_word*)lf[46]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2564,a[2]=((C_word)li35),tmp=(C_word)a,a+=3,tmp));
t33=C_mutate((C_word*)lf[47]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2570,a[2]=((C_word)li36),tmp=(C_word)a,a+=3,tmp));
t34=C_mutate((C_word*)lf[48]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2576,a[2]=((C_word)li37),tmp=(C_word)a,a+=3,tmp));
t35=C_mutate((C_word*)lf[51]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2620,a[2]=((C_word)li38),tmp=(C_word)a,a+=3,tmp));
t36=C_mutate((C_word*)lf[52]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2639,a[2]=((C_word)li39),tmp=(C_word)a,a+=3,tmp));
t37=C_mutate((C_word*)lf[53]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2679,a[2]=((C_word)li40),tmp=(C_word)a,a+=3,tmp));
t38=C_mutate((C_word*)lf[54]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2685,a[2]=((C_word)li41),tmp=(C_word)a,a+=3,tmp));
t39=C_mutate((C_word*)lf[56]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2704,a[2]=((C_word)li42),tmp=(C_word)a,a+=3,tmp));
t40=C_mutate((C_word*)lf[57]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2723,a[2]=((C_word)li43),tmp=(C_word)a,a+=3,tmp));
t41=C_mutate((C_word*)lf[58]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2729,a[2]=((C_word)li44),tmp=(C_word)a,a+=3,tmp));
t42=C_mutate(&lf[59],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2735,a[2]=((C_word)li45),tmp=(C_word)a,a+=3,tmp));
t43=C_mutate(&lf[61],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2756,a[2]=((C_word)li46),tmp=(C_word)a,a+=3,tmp));
t44=C_mutate(&lf[62],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2774,a[2]=((C_word)li47),tmp=(C_word)a,a+=3,tmp));
t45=C_mutate(&lf[63],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2792,a[2]=((C_word)li48),tmp=(C_word)a,a+=3,tmp));
t46=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2802,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t47=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_12184,a[2]=((C_word)li248),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  ##sys#register-record-printer");
t48=C_retrieve(lf[396]);
((C_proc4)C_retrieve_proc(t48))(4,t48,t46,lf[60],t47);}

/* a12183 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_12184(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_12184,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_12192,a[2]=t2,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  token-type");
f_2756(t4,t2);}

/* k12190 in a12183 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_12192(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_12192,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_12196,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  token-string");
f_2774(t2,((C_word*)t0)[2]);}

/* k12194 in k12190 in a12183 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_12196(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  fprintf");
t2=C_retrieve(lf[393]);
((C_proc6)C_retrieve_proc(t2))(6,t2,((C_word*)t0)[4],((C_word*)t0)[3],lf[400],((C_word*)t0)[2],t1);}

/* k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2802(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2802,2,t0,t1);}
t2=C_mutate(&lf[64],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2804,a[2]=((C_word)li49),tmp=(C_word)a,a+=3,tmp));
t3=C_mutate(&lf[66],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2833,a[2]=((C_word)li50),tmp=(C_word)a,a+=3,tmp));
t4=C_mutate(&lf[67],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2845,a[2]=((C_word)li51),tmp=(C_word)a,a+=3,tmp));
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2853,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-hash-table");
t6=C_retrieve(lf[309]);
((C_proc3)C_retrieve_proc(t6))(3,t6,t5,*((C_word*)lf[399]+1));}

/* k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2853(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2853,2,t0,t1);}
t2=C_mutate(&lf[68],t1);
t3=C_mutate(&lf[69],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2855,a[2]=((C_word)li52),tmp=(C_word)a,a+=3,tmp));
t4=C_mutate(&lf[71],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2876,a[2]=((C_word)li53),tmp=(C_word)a,a+=3,tmp));
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2958,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_12174,a[2]=((C_word)li247),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  ##sys#register-record-printer");
t7=C_retrieve(lf[396]);
((C_proc4)C_retrieve_proc(t7))(4,t7,t5,lf[70],t6);}

/* a12173 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_12174(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_12174,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_12182,a[2]=t3,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  rule-name");
f_2876(t4,t2);}

/* k12180 in a12173 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_12182(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  fprintf");
t2=C_retrieve(lf[393]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[3],((C_word*)t0)[2],lf[398],t1);}

/* k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2958(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2958,2,t0,t1);}
t2=C_mutate(&lf[72],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2960,a[2]=((C_word)li54),tmp=(C_word)a,a+=3,tmp));
t3=C_mutate(&lf[75],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2984,a[2]=((C_word)li55),tmp=(C_word)a,a+=3,tmp));
t4=C_mutate(&lf[76],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_2996,a[2]=((C_word)li56),tmp=(C_word)a,a+=3,tmp));
t5=C_mutate(&lf[77],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3002,a[2]=((C_word)li57),tmp=(C_word)a,a+=3,tmp));
t6=C_mutate(&lf[78],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3012,a[2]=((C_word)li58),tmp=(C_word)a,a+=3,tmp));
t7=C_mutate(&lf[79],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3070,a[2]=((C_word)li59),tmp=(C_word)a,a+=3,tmp));
t8=C_mutate(&lf[81],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3102,a[2]=((C_word)li60),tmp=(C_word)a,a+=3,tmp));
t9=C_mutate(&lf[83],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3123,a[2]=((C_word)li61),tmp=(C_word)a,a+=3,tmp));
t10=C_mutate(&lf[84],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3141,a[2]=((C_word)li62),tmp=(C_word)a,a+=3,tmp));
t11=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3151,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t12=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_12160,a[2]=((C_word)li246),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  ##sys#register-record-printer");
t13=C_retrieve(lf[396]);
((C_proc4)C_retrieve_proc(t13))(4,t13,t11,lf[82],t12);}

/* a12159 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_12160(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_12160,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_12168,a[2]=t2,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-error-string");
f_3123(t4,t2);}

/* k12166 in a12159 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_12168(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_12168,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_12172,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-error-position");
f_3141(t2,((C_word*)t0)[2]);}

/* k12170 in k12166 in a12159 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_12172(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  fprintf");
t2=C_retrieve(lf[393]);
((C_proc6)C_retrieve_proc(t2))(6,t2,((C_word*)t0)[4],((C_word*)t0)[3],lf[397],((C_word*)t0)[2],t1);}

/* k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3151(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_3151,2,t0,t1);}
t2=C_mutate(&lf[85],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3153,a[2]=((C_word)li63),tmp=(C_word)a,a+=3,tmp));
t3=C_mutate(&lf[87],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3159,a[2]=((C_word)li64),tmp=(C_word)a,a+=3,tmp));
t4=C_mutate(&lf[88],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3174,a[2]=((C_word)li65),tmp=(C_word)a,a+=3,tmp));
t5=C_mutate(&lf[89],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3192,a[2]=((C_word)li66),tmp=(C_word)a,a+=3,tmp));
t6=C_mutate(&lf[90],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3210,a[2]=((C_word)li67),tmp=(C_word)a,a+=3,tmp));
t7=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3220,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_12134,a[2]=((C_word)li245),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  ##sys#register-record-printer");
t9=C_retrieve(lf[396]);
((C_proc4)C_retrieve_proc(t9))(4,t9,t7,lf[86],t8);}

/* a12133 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_12134(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_12134,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_12138,a[2]=t3,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-type");
f_3174(t4,t2);}

/* k12136 in a12133 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_12138(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_12138,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_12144,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  SalRuleType?");
f_4432(t2,t1);}

/* k12142 in k12136 in a12133 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_12144(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_12144,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_12151,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_12155,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  get-rule");
f_2960(t3,((C_word*)t0)[2],C_SCHEME_END_OF_LIST);}
else{
C_trace("ChickenBridge.scm: 145  fprintf");
t2=C_retrieve(lf[393]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[4],((C_word*)t0)[3],lf[395],((C_word*)t0)[2]);}}

/* k12153 in k12142 in k12136 in a12133 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_12155(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  rule-name");
f_2876(((C_word*)t0)[2],t1);}

/* k12149 in k12142 in k12136 in a12133 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_12151(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  fprintf");
t2=C_retrieve(lf[393]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[3],((C_word*)t0)[2],lf[394],t1);}

/* k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3220(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_3220,2,t0,t1);}
t2=C_mutate(&lf[91],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3222,a[2]=((C_word)li68),tmp=(C_word)a,a+=3,tmp));
t3=C_mutate(&lf[93],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3238,a[2]=((C_word)li69),tmp=(C_word)a,a+=3,tmp));
t4=C_mutate(&lf[95],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3270,a[2]=((C_word)li70),tmp=(C_word)a,a+=3,tmp));
t5=C_mutate(&lf[96],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3282,a[2]=((C_word)li71),tmp=(C_word)a,a+=3,tmp));
t6=C_mutate(&lf[97],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3292,a[2]=((C_word)li72),tmp=(C_word)a,a+=3,tmp));
t7=C_mutate(&lf[99],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3310,a[2]=((C_word)li73),tmp=(C_word)a,a+=3,tmp));
t8=C_mutate(&lf[110],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3343,a[2]=((C_word)li74),tmp=(C_word)a,a+=3,tmp));
t9=C_mutate(&lf[113],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3551,a[2]=((C_word)li76),tmp=(C_word)a,a+=3,tmp));
t10=C_mutate(&lf[114],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3559,a[2]=((C_word)li79),tmp=(C_word)a,a+=3,tmp));
t11=lf[116]=C_SCHEME_FALSE;;
t12=C_mutate(&lf[117],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3663,a[2]=((C_word)li93),tmp=(C_word)a,a+=3,tmp));
t13=C_mutate(&lf[92],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4282,a[2]=((C_word)li94),tmp=(C_word)a,a+=3,tmp));
t14=C_mutate(&lf[109],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4330,a[2]=((C_word)li95),tmp=(C_word)a,a+=3,tmp));
t15=C_mutate(&lf[112],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4432,a[2]=((C_word)li96),tmp=(C_word)a,a+=3,tmp));
t16=C_mutate(&lf[94],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4444,a[2]=((C_word)li97),tmp=(C_word)a,a+=3,tmp));
t17=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4465,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t18=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_12112,a[2]=t17,tmp=(C_word)a,a+=3,tmp);
t19=(C_word)C_a_i_cons(&a,2,C_fix(3072),C_SCHEME_END_OF_LIST);
t20=(C_word)C_a_i_cons(&a,2,C_fix(3328),t19);
t21=(C_word)C_a_i_cons(&a,2,C_fix(2816),t20);
t22=(C_word)C_a_i_cons(&a,2,lf[104],t21);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t18,lf[392],C_fix(25856),t22,C_SCHEME_FALSE,C_SCHEME_FALSE);}

/* k12110 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_12112(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(25856),t1);}

/* k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4465(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4465,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4468,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_12092,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(4608),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(4352),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[104],t5);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t3,lf[391],C_fix(26112),t6,C_SCHEME_FALSE,C_SCHEME_FALSE);}

/* k12090 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_12092(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(26112),t1);}

/* k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4468(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4468,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4471,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_12052,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(4608),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(4352),t4);
t6=(C_word)C_a_i_cons(&a,2,C_fix(25088),t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(3840),t6);
t8=(C_word)C_a_i_cons(&a,2,C_fix(3072),t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(3328),t8);
t10=(C_word)C_a_i_cons(&a,2,C_fix(2816),t9);
t11=(C_word)C_a_i_cons(&a,2,lf[104],t10);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t3,lf[390],C_fix(26368),t11,C_SCHEME_FALSE,C_SCHEME_FALSE);}

/* k12050 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_12052(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(26368),t1);}

/* k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4471(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4471,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4474,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11942,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(26880),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,lf[80],t4);
t6=(C_word)C_a_i_cons(&a,2,C_fix(1280),C_SCHEME_END_OF_LIST);
t7=(C_word)C_a_i_cons(&a,2,t5,t6);
t8=(C_word)C_a_i_cons(&a,2,C_fix(1024),t7);
t9=(C_word)C_a_i_cons(&a,2,lf[103],t8);
t10=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11948,a[2]=((C_word)li243),tmp=(C_word)a,a+=3,tmp);
t11=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11958,a[2]=((C_word)li244),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t3,lf[389],C_fix(26624),t9,t10,t11);}

/* a11957 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11958(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[6],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_11958,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_11962,a[2]=t2,a[3]=t4,a[4]=t3,a[5]=t1,tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  get-emit-info");
f_3270(t5,lf[383],t3);}

/* k11960 in a11957 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11962(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11962,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_11965,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=t1,tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3192(t2,((C_word*)t0)[2]);}

/* k11963 in k11960 in a11957 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11965(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11965,2,t0,t1);}
t2=((C_word*)t0)[5];
if(C_truep(t2)){
C_trace("ChickenBridge.scm: 145  emit");
f_3310(((C_word*)t0)[4],t1,((C_word*)t0)[3],((C_word*)t0)[2]);}
else{
if(C_truep((C_word)C_i_nullp(t1))){
t3=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_list(&a,1,lf[346]));}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_11983,a[2]=((C_word*)t0)[2],a[3]=t1,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  add-emit-info");
f_3282(t3,lf[383],C_SCHEME_TRUE,((C_word*)t0)[3]);}}}

/* k11981 in k11963 in k11960 in a11957 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11983(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11983,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11986,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t2,((C_word*)t0)[3],t1,((C_word*)t0)[2]);}

/* k11984 in k11981 in k11963 in k11960 in a11957 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11986(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11986,2,t0,t1);}
t2=C_SCHEME_FALSE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11989,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_12017,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  get-emit-info");
f_3270(t5,lf[383],((C_word*)t0)[2]);}

/* k12015 in k11984 in k11981 in k11963 in k11960 in a11957 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_12017(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_12017,2,t0,t1);}
t2=(C_word)C_eqp(t1,lf[384]);
if(C_truep(t2)){
t3=(C_word)C_a_i_list(&a,2,lf[388],((C_word*)t0)[4]);
t4=C_mutate(((C_word *)((C_word*)t0)[3])+1,t3);
t5=((C_word*)t0)[2];
f_11989(t5,t4);}
else{
t3=(C_word)C_a_i_list(&a,2,lf[272],((C_word*)t0)[4]);
t4=C_mutate(((C_word *)((C_word*)t0)[3])+1,t3);
t5=((C_word*)t0)[2];
f_11989(t5,t4);}}

/* k11987 in k11984 in k11981 in k11963 in k11960 in a11957 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_11989(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_11989,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_11995,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  get-emit-info");
f_3270(t2,lf[351],((C_word*)t0)[2]);}

/* k11993 in k11987 in k11984 in k11981 in k11963 in k11960 in a11957 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11995(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11995,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,1,lf[346]);
t3=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_list(&a,3,lf[115],((C_word*)((C_word*)t0)[2])[1],t2));}
else{
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,((C_word*)((C_word*)t0)[2])[1]);}}

/* a11947 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11948(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word *a;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_11948,4,t0,t1,t2,t3);}
t4=(C_word)C_i_cadr(t2);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3153(t1,C_fix(26624),t4,C_SCHEME_FALSE);}

/* k11940 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11942(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(26624),t1);}

/* k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4474(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4474,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4477,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11842,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(5632),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(5376),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[104],t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,t6,t7);
t9=(C_word)C_a_i_cons(&a,2,lf[103],t8);
t10=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_11850,a[2]=t9,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  simple-unit-parser");
f_3551(t10,C_fix(27648));}

/* k11848 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11850(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11850,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11852,a[2]=((C_word)li242),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(((C_word*)t0)[3],lf[387],C_fix(27648),((C_word*)t0)[2],t1,t2);}

/* a11851 in k11848 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11852(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_11852,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11856,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3192(t5,t2);}

/* k11854 in a11851 in k11848 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11856(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11856,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_11859,a[2]=((C_word*)t0)[2],a[3]=t1,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=(C_word)C_i_car(t1);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3238(t2,t3,C_fix(5376));}

/* k11857 in k11854 in a11851 in k11848 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11859(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11859,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_11862,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=((C_word*)t0)[5],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  get-emit-info");
f_3270(t2,lf[383],((C_word*)t0)[4]);}

/* k11860 in k11857 in k11854 in a11851 in k11848 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11862(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_11862,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_11865,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
if(C_truep(t1)){
t3=t2;
f_11865(2,t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_11894,a[2]=t2,a[3]=((C_word*)t0)[2],tmp=(C_word)a,a+=4,tmp);
t4=(C_truep(((C_word*)t0)[5])?lf[385]:lf[386]);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_11902,a[2]=t4,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t6=(C_word)C_i_car(((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 145  parse-unit-position");
f_3210(t5,t6);}}

/* k11900 in k11860 in k11857 in k11854 in a11851 in k11848 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11902(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-parse-error");
f_3102(((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k11892 in k11860 in k11857 in k11854 in a11851 in k11848 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11894(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  errf");
t2=((C_word*)t0)[3];
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k11863 in k11860 in k11857 in k11854 in a11851 in k11848 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11865(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11865,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11868,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
t3=(C_word)C_i_cadr(((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t2,t3,((C_word*)t0)[4],((C_word*)t0)[2]);}

/* k11866 in k11863 in k11860 in k11857 in k11854 in a11851 in k11848 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11868(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11868,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11871,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  set-emit-info!");
f_3292(t2,lf[383],lf[384],((C_word*)t0)[2]);}

/* k11869 in k11866 in k11863 in k11860 in k11857 in k11854 in a11851 in k11848 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11871(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11871,2,t0,t1);}
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_truep(((C_word*)t0)[3])?(C_word)C_a_i_list(&a,2,lf[381],((C_word*)t0)[2]):(C_word)C_a_i_list(&a,2,lf[382],((C_word*)t0)[2])));}

/* k11840 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11842(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(27648),t1);}

/* k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4477(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4477,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4480,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11814,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(27648),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(2304),t4);
t6=(C_word)C_a_i_cons(&a,2,C_fix(26624),t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(26368),t6);
t8=(C_word)C_a_i_cons(&a,2,lf[104],t7);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t3,lf[380],C_fix(26880),t8,C_SCHEME_FALSE,C_SCHEME_FALSE);}

/* k11812 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11814(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(26880),t1);}

/* k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4480(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4480,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4483,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11754,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(1792),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(29696),t4);
t6=(C_word)C_a_i_cons(&a,2,C_fix(1536),t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(25088),t6);
t8=(C_word)C_a_i_cons(&a,2,lf[103],t7);
t9=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11760,a[2]=((C_word)li240),tmp=(C_word)a,a+=3,tmp);
t10=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11778,a[2]=((C_word)li241),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t3,lf[379],C_fix(27136),t8,t9,t10);}

/* a11777 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11778(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[8],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_11778,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11786,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11790,a[2]=t4,a[3]=t3,a[4]=t5,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3192(t6,t2);}

/* k11788 in a11777 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11790(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  emit");
f_3310(((C_word*)t0)[4],t1,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k11784 in a11777 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11786(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11786,2,t0,t1);}
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_cons(&a,2,lf[345],t1));}

/* a11759 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11760(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_11760,4,t0,t1,t2,t3);}
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_caddr(t2);
t6=(C_word)C_a_i_list(&a,2,t4,t5);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3153(t1,C_fix(27136),t6,C_SCHEME_FALSE);}

/* k11752 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11754(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(27136),t1);}

/* k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4483(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4483,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4486,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11631,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(256),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[121],t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(768),C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,t6,t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(29696),t8);
t10=(C_word)C_a_i_cons(&a,2,C_fix(256),t9);
t11=(C_word)C_a_i_cons(&a,2,C_fix(29696),t10);
t12=(C_word)C_a_i_cons(&a,2,C_fix(512),t11);
t13=(C_word)C_a_i_cons(&a,2,C_fix(5120),t12);
t14=(C_word)C_a_i_cons(&a,2,lf[103],t13);
t15=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11637,a[2]=((C_word)li238),tmp=(C_word)a,a+=3,tmp);
t16=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11668,a[2]=((C_word)li239),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t3,lf[378],C_fix(27392),t14,t15,t16);}

/* a11667 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11668(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_11668,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11672,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3192(t5,t2);}

/* k11670 in a11667 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11672(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11672,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_11675,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,tmp=(C_word)a,a+=6,tmp);
t3=(C_word)C_i_car(t1);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k11673 in k11670 in a11667 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11675(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11675,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_11678,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],tmp=(C_word)a,a+=7,tmp);
t3=(C_word)C_i_cadr(((C_word*)t0)[5]);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k11676 in k11673 in k11670 in a11667 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11678(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11678,2,t0,t1);}
t2=(C_word)C_i_caddr(((C_word*)t0)[6]);
if(C_truep(t2)){
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11691,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t3,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}
else{
t3=((C_word*)t0)[5];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_list(&a,4,lf[137],((C_word*)t0)[4],t1,C_SCHEME_FALSE));}}

/* k11689 in k11676 in k11673 in k11670 in a11667 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11691(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11691,2,t0,t1);}
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_list(&a,4,lf[137],((C_word*)t0)[3],((C_word*)t0)[2],t1));}

/* a11636 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11637(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_11637,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_11641,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  sixth");
t5=C_retrieve(lf[199]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,t2);}

/* k11639 in a11636 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11641(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11641,2,t0,t1);}
t2=(C_word)C_i_caddr(((C_word*)t0)[3]);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11656,a[2]=((C_word*)t0)[2],a[3]=t2,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  fifth");
t4=C_retrieve(lf[139]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)t0)[3]);}

/* k11654 in k11639 in a11636 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11656(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11656,2,t0,t1);}
t2=(C_word)C_i_pairp(((C_word*)t0)[4]);
t3=(C_truep(t2)?(C_word)C_i_cadr(((C_word*)t0)[4]):C_SCHEME_FALSE);
t4=(C_word)C_a_i_list(&a,3,((C_word*)t0)[3],t1,t3);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3153(((C_word*)t0)[2],C_fix(27392),t4,C_SCHEME_FALSE);}

/* k11629 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11631(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(27392),t1);}

/* k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4486(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4486,2,t0,t1);}
t2=C_mutate(&lf[127],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4488,a[2]=((C_word)li99),tmp=(C_word)a,a+=3,tmp));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4542,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11511,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
t5=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t6=(C_word)C_a_i_cons(&a,2,C_fix(256),t5);
t7=(C_word)C_a_i_cons(&a,2,lf[122],t6);
t8=(C_word)C_a_i_cons(&a,2,t7,C_SCHEME_END_OF_LIST);
t9=(C_word)C_a_i_cons(&a,2,C_fix(29696),t8);
t10=(C_word)C_a_i_cons(&a,2,lf[103],t9);
t11=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t12=(C_word)C_a_i_cons(&a,2,t10,t11);
t13=(C_word)C_a_i_cons(&a,2,lf[104],t12);
t14=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11517,a[2]=((C_word)li237),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t4,lf[377],C_fix(28416),t13,t14,C_SCHEME_FALSE);}

/* a11516 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11517(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_11517,4,t0,t1,t2,t3);}
if(C_truep((C_word)C_i_pairp(t2))){
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_11533,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(C_word)C_i_cadr(t2);
if(C_truep((C_word)C_i_pairp(t6))){
t7=(C_word)C_i_cadr(t2);
t8=(C_word)C_i_car(t7);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3238(t4,t8,C_fix(256));}
else{
t7=t4;
f_11533(2,t7,C_SCHEME_FALSE);}}
else{
t6=t4;
f_11533(2,t6,C_SCHEME_FALSE);}}
else{
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_a_i_list(&a,1,t2));}}

/* k11531 in a11516 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11533(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11533,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_11544,a[2]=t2,a[3]=((C_word*)t0)[2],tmp=(C_word)a,a+=4,tmp);
t4=(C_word)C_i_cadr(((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 145  remove-token-type");
f_4488(t3,t4,C_fix(256));}
else{
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]));}}

/* k11542 in k11531 in a11516 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11544(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11544,2,t0,t1);}
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[2],t1));}

/* k11509 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11511(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(28416),t1);}

/* k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4542(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4542,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4545,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11372,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(6144),t4);
t6=(C_word)C_a_i_cons(&a,2,C_fix(256),t5);
t7=(C_word)C_a_i_cons(&a,2,lf[122],t6);
t8=(C_word)C_a_i_cons(&a,2,t7,C_SCHEME_END_OF_LIST);
t9=(C_word)C_a_i_cons(&a,2,C_fix(29696),t8);
t10=(C_word)C_a_i_cons(&a,2,C_fix(6144),t9);
t11=(C_word)C_a_i_cons(&a,2,lf[103],t10);
t12=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t13=(C_word)C_a_i_cons(&a,2,C_fix(6144),t12);
t14=(C_word)C_a_i_cons(&a,2,lf[103],t13);
t15=(C_word)C_a_i_cons(&a,2,t14,C_SCHEME_END_OF_LIST);
t16=(C_word)C_a_i_cons(&a,2,t11,t15);
t17=(C_word)C_a_i_cons(&a,2,lf[104],t16);
t18=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11378,a[2]=((C_word)li236),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t3,lf[376],C_fix(28672),t17,t18,C_SCHEME_FALSE);}

/* a11377 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11378(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_11378,4,t0,t1,t2,t3);}
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cadr(t2);
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11398,a[2]=t4,a[3]=t1,a[4]=t5,tmp=(C_word)a,a+=5,tmp);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_11401,a[2]=t6,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t8=(C_word)C_i_cddr(t2);
if(C_truep((C_word)C_i_pairp(t8))){
t9=(C_word)C_i_caddr(t2);
if(C_truep((C_word)C_i_pairp(t9))){
t10=(C_word)C_i_caddr(t2);
t11=(C_word)C_i_car(t10);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3238(t7,t11,C_fix(256));}
else{
t10=t7;
f_11401(2,t10,C_SCHEME_FALSE);}}
else{
t9=t7;
f_11401(2,t9,C_SCHEME_FALSE);}}

/* k11399 in a11377 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11401(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_caddr(((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 145  remove-token-type");
f_4488(((C_word*)t0)[2],t2,C_fix(256));}
else{
t2=((C_word*)t0)[2];
f_11398(2,t2,C_SCHEME_END_OF_LIST);}}

/* k11396 in a11377 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11398(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11398,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[4],t1);
t3=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[2],t2));}

/* k11370 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11372(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(28672),t1);}

/* k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4545(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4545,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4548,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11220,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(768),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(512),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[103],t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(768),C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(28416),t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(512),t8);
t10=(C_word)C_a_i_cons(&a,2,lf[103],t9);
t11=(C_word)C_a_i_cons(&a,2,C_fix(768),C_SCHEME_END_OF_LIST);
t12=(C_word)C_a_i_cons(&a,2,C_fix(28672),t11);
t13=(C_word)C_a_i_cons(&a,2,C_fix(512),t12);
t14=(C_word)C_a_i_cons(&a,2,lf[103],t13);
t15=(C_word)C_a_i_cons(&a,2,C_fix(768),C_SCHEME_END_OF_LIST);
t16=(C_word)C_a_i_cons(&a,2,C_fix(28672),t15);
t17=(C_word)C_a_i_cons(&a,2,C_fix(256),t16);
t18=(C_word)C_a_i_cons(&a,2,C_fix(28416),t17);
t19=(C_word)C_a_i_cons(&a,2,C_fix(512),t18);
t20=(C_word)C_a_i_cons(&a,2,lf[103],t19);
t21=(C_word)C_a_i_cons(&a,2,t20,C_SCHEME_END_OF_LIST);
t22=(C_word)C_a_i_cons(&a,2,t14,t21);
t23=(C_word)C_a_i_cons(&a,2,t10,t22);
t24=(C_word)C_a_i_cons(&a,2,t6,t23);
t25=(C_word)C_a_i_cons(&a,2,lf[104],t24);
t26=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11226,a[2]=((C_word)li235),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t3,lf[375],C_fix(28160),t25,t26,C_SCHEME_FALSE);}

/* a11225 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11226(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_11226,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=(C_word)C_i_cdr(((C_word*)t4)[1]);
t6=C_set_block_item(t4,0,t5);
t7=(C_word)C_i_car(((C_word*)t4)[1]);
t8=(C_word)C_i_cdr(((C_word*)t4)[1]);
t9=C_set_block_item(t4,0,t8);
t10=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11244,a[2]=t7,a[3]=t4,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3238(t10,t7,C_fix(768));}

/* k11242 in a11225 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11244(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11244,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_END_OF_LIST);}
else{
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11253,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3238(t2,t3,C_fix(256));}}

/* k11251 in k11242 in a11225 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11253(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_cadr(((C_word*)((C_word*)t0)[4])[1]);
C_trace("ChickenBridge.scm: 145  append");
t3=*((C_word*)lf[115]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[3],((C_word*)t0)[2],t2);}
else{
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,((C_word*)t0)[2]);}}

/* k11218 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11220(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(28160),t1);}

/* k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4548(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4548,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4551,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11149,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(28160),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(25088),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[103],t5);
t7=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11155,a[2]=((C_word)li233),tmp=(C_word)a,a+=3,tmp);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11173,a[2]=((C_word)li234),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t3,lf[374],C_fix(27904),t6,t7,t8);}

/* a11172 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11173(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_11173,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_11177,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3192(t5,t2);}

/* k11175 in a11172 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11177(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11177,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_11180,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=(C_word)C_i_car(t1);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k11178 in k11175 in a11172 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11180(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11180,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_11196,a[2]=t1,a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t3=(C_word)C_i_cdr(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k11194 in k11178 in k11175 in a11172 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11196(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11196,2,t0,t1);}
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[2],t1));}

/* a11154 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11155(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[3],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_11155,4,t0,t1,t2,t3);}
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cadr(t2);
t6=(C_word)C_a_i_cons(&a,2,t4,t5);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3153(t1,C_fix(27904),t6,C_SCHEME_FALSE);}

/* k11147 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11149(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(27904),t1);}

/* k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4551(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4551,2,t0,t1);}
t2=C_mutate(&lf[128],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4553,a[2]=((C_word)li100),tmp=(C_word)a,a+=3,tmp));
t3=C_mutate(&lf[129],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4574,a[2]=((C_word)li103),tmp=(C_word)a,a+=3,tmp));
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4690,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_11073,a[2]=t4,tmp=(C_word)a,a+=3,tmp);
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
t22=(C_word)C_a_i_cons(&a,2,lf[104],t21);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t5,lf[373],C_fix(28928),t22,C_SCHEME_FALSE,C_SCHEME_FALSE);}

/* k11071 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11073(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(28928),t1);}

/* k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4690(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4690,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4693,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10993,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29440),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(28928),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[80],t5);
t7=(C_word)C_a_i_cons(&a,2,t6,C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(29440),t7);
t9=(C_word)C_a_i_cons(&a,2,lf[103],t8);
t10=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10999,a[2]=((C_word)li232),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t3,lf[372],C_fix(29184),t9,t10,C_SCHEME_FALSE);}

/* a10998 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10999(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_10999,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_11006,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_i_cadr(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(C_word)C_i_cadr(t2);
t7=(C_word)C_i_car(t6);
C_trace("ChickenBridge.scm: 145  is-op?");
f_4553(t4,t7);}
else{
t6=t4;
f_11006(2,t6,C_SCHEME_FALSE);}}

/* k11004 in a10998 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_11006(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_11006,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=(C_word)C_i_cadr(((C_word*)t0)[3]);
t4=(C_word)C_a_i_cons(&a,2,t2,t3);
C_trace("ChickenBridge.scm: 145  inf->pre");
f_4574(((C_word*)t0)[2],t4);}
else{
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_i_car(((C_word*)t0)[3]));}}

/* k10991 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10993(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(29184),t1);}

/* k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4693(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4693,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4696,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10857,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29440),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(7173),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[103],t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(29440),C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(8963),t7);
t9=(C_word)C_a_i_cons(&a,2,lf[103],t8);
t10=(C_word)C_a_i_cons(&a,2,C_fix(768),C_SCHEME_END_OF_LIST);
t11=(C_word)C_a_i_cons(&a,2,C_fix(29184),t10);
t12=(C_word)C_a_i_cons(&a,2,C_fix(512),t11);
t13=(C_word)C_a_i_cons(&a,2,lf[103],t12);
t14=(C_word)C_a_i_cons(&a,2,C_fix(2304),C_SCHEME_END_OF_LIST);
t15=(C_word)C_a_i_cons(&a,2,C_fix(26624),t14);
t16=(C_word)C_a_i_cons(&a,2,C_fix(26368),t15);
t17=(C_word)C_a_i_cons(&a,2,C_fix(27136),t16);
t18=(C_word)C_a_i_cons(&a,2,C_fix(27904),t17);
t19=(C_word)C_a_i_cons(&a,2,C_fix(27392),t18);
t20=(C_word)C_a_i_cons(&a,2,t13,t19);
t21=(C_word)C_a_i_cons(&a,2,t9,t20);
t22=(C_word)C_a_i_cons(&a,2,t6,t21);
t23=(C_word)C_a_i_cons(&a,2,lf[104],t22);
t24=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10863,a[2]=((C_word)li230),tmp=(C_word)a,a+=3,tmp);
t25=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10889,a[2]=((C_word)li231),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t3,lf[371],C_fix(29440),t23,t24,t25);}

/* a10888 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10889(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_10889,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10897,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3192(t5,t2);}

/* k10895 in a10888 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10897(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  emit");
f_3310(((C_word*)t0)[4],t1,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* a10862 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10863(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[7],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_10863,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10871,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep((C_word)C_i_pairp(t2))){
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10880,a[2]=t2,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
t6=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3238(t5,t6,C_fix(512));}
else{
t5=t4;
f_10871(t5,t2);}}

/* k10878 in a10862 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10880(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
f_10871(t2,(C_truep(t1)?(C_word)C_i_cadr(((C_word*)t0)[2]):((C_word*)t0)[2]));}

/* k10869 in a10862 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_10871(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3153(((C_word*)t0)[2],C_fix(29440),t1,C_SCHEME_FALSE);}

/* k10855 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10857(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(29440),t1);}

/* k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4696(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4696,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4699,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10813,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(26368),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(6400),t4);
t6=(C_word)C_a_i_cons(&a,2,C_fix(2304),t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(26624),t6);
t8=(C_word)C_a_i_cons(&a,2,C_fix(27136),t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(27904),t8);
t10=(C_word)C_a_i_cons(&a,2,C_fix(27392),t9);
t11=(C_word)C_a_i_cons(&a,2,C_fix(29184),t10);
t12=(C_word)C_a_i_cons(&a,2,lf[104],t11);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t3,lf[370],C_fix(29696),t12,C_SCHEME_FALSE,C_SCHEME_FALSE);}

/* k10811 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10813(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(29696),t1);}

/* k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4699(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4699,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4702,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10703,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(256),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[80],t5);
t7=(C_word)C_a_i_cons(&a,2,t6,C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(29696),t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(15872),t8);
t10=(C_word)C_a_i_cons(&a,2,lf[103],t9);
t11=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10709,a[2]=((C_word)li227),tmp=(C_word)a,a+=3,tmp);
t12=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10731,a[2]=((C_word)li229),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t3,lf[369],C_fix(33536),t10,t11,t12);}

/* a10730 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10731(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
C_save_and_reclaim((void*)tr5,(void*)f_10731,5,t0,t1,t2,t3,t4);}
t5=(C_word)C_a_i_list(&a,1,lf[167]);
t6=t5;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_10742,a[2]=t1,a[3]=t4,a[4]=t3,a[5]=t7,a[6]=t5,tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3192(t8,t2);}

/* k10740 in a10730 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10742(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10742,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_10744,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=t3,a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word)li228),tmp=(C_word)a,a+=8,tmp));
t5=((C_word*)t3)[1];
f_10744(t5,((C_word*)t0)[2],t1);}

/* do899 in k10740 in a10730 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_10744(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_10744,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,((C_word*)t0)[6]);}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_10773,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=t2,a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
t4=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t3,t4,((C_word*)t0)[3],((C_word*)t0)[2]);}}

/* k10771 in do899 in k10740 in a10730 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10773(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_10773,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,t1);
t3=(C_word)C_i_set_cdr(((C_word*)((C_word*)t0)[5])[1],t2);
t4=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[5])[1]);
t5=C_mutate(((C_word *)((C_word*)t0)[5])+1,t4);
t6=(C_word)C_i_cdr(((C_word*)t0)[4]);
t7=((C_word*)((C_word*)t0)[3])[1];
f_10744(t7,((C_word*)t0)[2],t6);}

/* a10708 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10709(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[4],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_10709,4,t0,t1,t2,t3);}
t4=(C_word)C_i_cadr(t2);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10725,a[2]=t1,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
t6=(C_word)C_i_caddr(t2);
C_trace("ChickenBridge.scm: 145  remove-token-type");
f_4488(t5,t6,C_fix(256));}

/* k10723 in a10708 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10725(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10725,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[3],t1);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3153(((C_word*)t0)[2],C_fix(33536),t2,C_SCHEME_FALSE);}

/* k10701 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10703(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(33536),t1);}

/* k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4702(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4702,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4705,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10594,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(256),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[121],t5);
t7=(C_word)C_a_i_cons(&a,2,t6,C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(29696),t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(16896),t8);
t10=(C_word)C_a_i_cons(&a,2,lf[103],t9);
t11=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10600,a[2]=((C_word)li225),tmp=(C_word)a,a+=3,tmp);
t12=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10627,a[2]=((C_word)li226),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t3,lf[368],C_fix(34560),t10,t11,t12);}

/* a10626 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10627(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_10627,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10631,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3192(t5,t2);}

/* k10629 in a10626 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10631(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10631,2,t0,t1);}
if(C_truep((C_word)C_i_cadr(t1))){
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_10644,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=(C_word)C_i_car(t1);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}
else{
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10663,a[2]=((C_word*)t0)[4],tmp=(C_word)a,a+=3,tmp);
t3=(C_word)C_i_car(t1);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}}

/* k10661 in k10629 in a10626 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10663(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10663,2,t0,t1);}
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_list(&a,2,lf[218],t1));}

/* k10642 in k10629 in a10626 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10644(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10644,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10648,a[2]=t1,a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t3=(C_word)C_i_cadr(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k10646 in k10642 in k10629 in a10626 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10648(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10648,2,t0,t1);}
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_list(&a,3,lf[218],((C_word*)t0)[2],t1));}

/* a10599 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10600(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word ab[4],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_10600,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10604,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_caddr(t2))){
t5=(C_word)C_i_caddr(t2);
C_trace("ChickenBridge.scm: 145  remove-token-type");
f_4488(t4,t5,C_fix(256));}
else{
t5=t4;
f_10604(2,t5,C_SCHEME_FALSE);}}

/* k10602 in a10599 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10604(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10604,2,t0,t1);}
t2=(C_word)C_i_cadr(((C_word*)t0)[3]);
t3=(C_word)C_a_i_list(&a,2,t2,t1);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3153(((C_word*)t0)[2],C_fix(34560),t3,C_SCHEME_FALSE);}

/* k10592 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10594(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(34560),t1);}

/* k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4705(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4705,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4708,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10395,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(25088),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(2304),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[104],t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(28672),C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(256),t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(28416),t8);
t10=(C_word)C_a_i_cons(&a,2,lf[103],t9);
t11=(C_word)C_a_i_cons(&a,2,C_fix(28672),C_SCHEME_END_OF_LIST);
t12=(C_word)C_a_i_cons(&a,2,C_fix(28416),t11);
t13=(C_word)C_a_i_cons(&a,2,t10,t12);
t14=(C_word)C_a_i_cons(&a,2,lf[104],t13);
t15=(C_word)C_a_i_cons(&a,2,t14,C_SCHEME_END_OF_LIST);
t16=(C_word)C_a_i_cons(&a,2,C_fix(256),t15);
t17=(C_word)C_a_i_cons(&a,2,lf[121],t16);
t18=(C_word)C_a_i_cons(&a,2,t17,C_SCHEME_END_OF_LIST);
t19=(C_word)C_a_i_cons(&a,2,t6,t18);
t20=(C_word)C_a_i_cons(&a,2,C_fix(16384),t19);
t21=(C_word)C_a_i_cons(&a,2,lf[103],t20);
t22=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10401,a[2]=((C_word)li222),tmp=(C_word)a,a+=3,tmp);
t23=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10462,a[2]=((C_word)li224),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t3,lf[367],C_fix(34304),t21,t22,t23);}

/* a10461 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10462(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[10],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_10462,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10466,a[2]=t1,a[3]=t2,a[4]=t4,tmp=(C_word)a,a+=5,tmp);
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10502,a[2]=t4,a[3]=t3,a[4]=t5,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3192(t6,t2);}

/* k10500 in a10461 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10502(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  emit");
f_3310(((C_word*)t0)[4],t1,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k10464 in a10461 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10466(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10466,2,t0,t1);}
t2=(C_word)C_i_car(t1);
t3=(C_word)C_i_car(t1);
t4=(C_word)C_i_cdr(t1);
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10482,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word)li223),tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  expand-send");
t6=C_retrieve(lf[233]);
((C_proc5)C_retrieve_proc(t6))(5,t6,((C_word*)t0)[2],t3,t4,t5);}

/* a10481 in k10464 in a10461 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10482(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+8)){
C_save_and_reclaim((void*)tr3r,(void*)f_10482r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_10482r(t0,t1,t2,t3);}}

static void C_ccall f_10482r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word *a=C_alloc(8);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10490,a[2]=t1,a[3]=((C_word*)t0)[3],tmp=(C_word)a,a+=4,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10494,a[2]=((C_word*)t0)[2],a[3]=t4,tmp=(C_word)a,a+=4,tmp);
C_apply(5,0,t5,C_retrieve(lf[174]),t2,t3);}

/* k10492 in a10481 in k10464 in a10461 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10494(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10494,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10498,a[2]=t1,a[3]=((C_word*)t0)[3],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-position");
f_3210(t2,((C_word*)t0)[2]);}

/* k10496 in k10492 in a10481 in k10464 in a10461 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10498(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-parse-error");
f_3102(((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k10488 in a10481 in k10464 in a10461 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10490(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  errf");
t2=((C_word*)t0)[3];
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* a10400 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10401(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_10401,4,t0,t1,t2,t3);}
t4=(C_word)C_i_caddr(t2);
t5=t4;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10408,a[2]=t1,a[3]=t6,a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t8=((C_word*)t6)[1];
if(C_truep(t8)){
t9=(C_word)C_i_cadr(((C_word*)t6)[1]);
t10=C_set_block_item(t6,0,t9);
t11=(C_word)C_i_car(((C_word*)t6)[1]);
if(C_truep((C_word)C_i_pairp(t11))){
t12=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10448,a[2]=t7,a[3]=t6,tmp=(C_word)a,a+=4,tmp);
t13=(C_word)C_i_car(((C_word*)t6)[1]);
t14=(C_word)C_i_caddr(((C_word*)t6)[1]);
C_trace("ChickenBridge.scm: 145  append");
t15=*((C_word*)lf[115]+1);
((C_proc4)C_retrieve_proc(t15))(4,t15,t12,t13,t14);}
else{
t12=t7;
f_10408(t12,C_SCHEME_UNDEFINED);}}
else{
t9=C_set_block_item(t6,0,C_SCHEME_END_OF_LIST);
t10=t7;
f_10408(t10,t9);}}

/* k10446 in a10400 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10448(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_10408(t3,t2);}

/* k10406 in a10400 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_10408(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_10408,NULL,2,t0,t1);}
t2=(C_word)C_i_cadr(((C_word*)t0)[4]);
t3=(C_word)C_a_i_cons(&a,2,t2,((C_word*)((C_word*)t0)[3])[1]);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10419,a[2]=t3,a[3]=((C_word*)t0)[2],tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_i_car(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 145  parse-unit-position");
f_3210(t4,t5);}

/* k10417 in k10406 in a10400 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10419(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3153(((C_word*)t0)[3],C_fix(34304),((C_word*)t0)[2],t1);}

/* k10393 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10395(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(34304),t1);}

/* k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4708(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4708,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4711,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10369,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(14080),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[103],t5);
t7=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10375,a[2]=((C_word)li221),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t3,lf[366],C_fix(33792),t6,t7,C_SCHEME_FALSE);}

/* a10374 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10375(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word *a;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_10375,4,t0,t1,t2,t3);}
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_cadr(t2));}

/* k10367 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10369(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(33792),t1);}

/* k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4711(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4711,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4714,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10341,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(14592),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[103],t5);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10349,a[2]=t6,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  simple-unit-parser");
f_3551(t7,C_fix(35072));}

/* k10347 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10349(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10349,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10353,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  simple-unit-emitter");
f_3559(t2,lf[180]);}

/* k10351 in k10347 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10353(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(((C_word*)t0)[4],lf[365],C_fix(35072),((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k10339 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10341(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(35072),t1);}

/* k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4714(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4714,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4717,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10313,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(13568),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[103],t5);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10321,a[2]=t6,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  simple-unit-parser");
f_3551(t7,C_fix(35584));}

/* k10319 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10321(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10321,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10325,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  simple-unit-emitter");
f_3559(t2,lf[178]);}

/* k10323 in k10319 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10325(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(((C_word*)t0)[4],lf[364],C_fix(35584),((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k10311 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10313(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(35584),t1);}

/* k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4717(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4717,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4720,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10285,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(17152),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[103],t5);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10293,a[2]=t6,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  simple-unit-parser");
f_3551(t7,C_fix(35328));}

/* k10291 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10293(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10293,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10297,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  simple-unit-emitter");
f_3559(t2,lf[363]);}

/* k10295 in k10291 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10297(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(((C_word*)t0)[4],lf[362],C_fix(35328),((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k10283 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10285(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(35328),t1);}

/* k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4720(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4720,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4723,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10257,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(18432),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[103],t5);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10265,a[2]=t6,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  simple-unit-parser");
f_3551(t7,C_fix(34816));}

/* k10263 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10265(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10265,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10269,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  simple-unit-emitter");
f_3559(t2,lf[190]);}

/* k10267 in k10263 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10269(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(((C_word*)t0)[4],lf[361],C_fix(34816),((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k10255 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10257(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(34816),t1);}

/* k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4723(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4723,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4726,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10120,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(6144),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[103],t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,t6,t7);
t9=(C_word)C_a_i_cons(&a,2,lf[104],t8);
t10=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t11=(C_word)C_a_i_cons(&a,2,C_fix(6144),t10);
t12=(C_word)C_a_i_cons(&a,2,lf[103],t11);
t13=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t14=(C_word)C_a_i_cons(&a,2,t12,t13);
t15=(C_word)C_a_i_cons(&a,2,lf[104],t14);
t16=(C_word)C_a_i_cons(&a,2,t15,C_SCHEME_END_OF_LIST);
t17=(C_word)C_a_i_cons(&a,2,C_fix(256),t16);
t18=(C_word)C_a_i_cons(&a,2,lf[80],t17);
t19=(C_word)C_a_i_cons(&a,2,t18,C_SCHEME_END_OF_LIST);
t20=(C_word)C_a_i_cons(&a,2,t9,t19);
t21=(C_word)C_a_i_cons(&a,2,C_fix(15616),t20);
t22=(C_word)C_a_i_cons(&a,2,lf[103],t21);
t23=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10126,a[2]=((C_word)li219),tmp=(C_word)a,a+=3,tmp);
t24=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10156,a[2]=((C_word)li220),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t3,lf[360],C_fix(36096),t22,t23,t24);}

/* a10155 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10156(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_10156,5,t0,t1,t2,t3,t4);}
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,lf[359]);}

/* a10125 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10126(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_10126,4,t0,t1,t2,t3);}
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cadr(t2);
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10150,a[2]=t1,a[3]=t4,a[4]=t5,tmp=(C_word)a,a+=5,tmp);
t7=(C_word)C_i_caddr(t2);
C_trace("ChickenBridge.scm: 145  remove-token-type");
f_4488(t6,t7,C_fix(256));}

/* k10148 in a10125 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10150(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10150,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[4],t1);
t3=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[3],t2);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3153(((C_word*)t0)[2],C_fix(36096),t3,C_SCHEME_FALSE);}

/* k10118 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10120(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(36096),t1);}

/* k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4726(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4726,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4729,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10062,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(19712),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[103],t5);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10070,a[2]=t6,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  simple-unit-parser");
f_3551(t7,C_fix(31744));}

/* k10068 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10070(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10070,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10072,a[2]=((C_word)li218),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(((C_word*)t0)[3],lf[358],C_fix(31744),((C_word*)t0)[2],t1,t2);}

/* a10071 in k10068 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10072(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_10072,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10076,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3192(t5,t2);}

/* k10074 in a10071 in k10068 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10076(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10076,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_10079,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10104,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  get-emit-info");
f_3270(t3,lf[334],((C_word*)t0)[3]);}

/* k10102 in k10074 in a10071 in k10068 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10104(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10104,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
f_10079(2,t2,C_SCHEME_UNDEFINED);}
else{
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10092,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[3],tmp=(C_word)a,a+=4,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10096,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 145  parse-unit-position");
f_3210(t3,t4);}}

/* k10094 in k10102 in k10074 in a10071 in k10068 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10096(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-parse-error");
f_3102(((C_word*)t0)[2],lf[357],t1);}

/* k10090 in k10102 in k10074 in a10071 in k10068 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10092(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  errf");
t2=((C_word*)t0)[3];
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k10077 in k10074 in a10071 in k10068 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10079(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  emit");
f_3310(((C_word*)t0)[5],((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k10060 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10062(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(31744),t1);}

/* k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4729(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4729,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4732,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10001,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(18688),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[103],t5);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10009,a[2]=t6,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  simple-unit-parser");
f_3551(t7,C_fix(31488));}

/* k10007 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10009(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10009,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10011,a[2]=((C_word)li217),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(((C_word*)t0)[3],lf[356],C_fix(31488),((C_word*)t0)[2],t1,t2);}

/* a10010 in k10007 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10011(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_10011,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10015,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3192(t5,t2);}

/* k10013 in a10010 in k10007 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10015(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10015,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_10018,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_10046,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  get-emit-info");
f_3270(t3,lf[321],((C_word*)t0)[3]);}

/* k10044 in k10013 in a10010 in k10007 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10046(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10046,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
f_10018(2,t2,C_SCHEME_UNDEFINED);}
else{
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_10034,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[3],tmp=(C_word)a,a+=4,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_10038,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 145  parse-unit-position");
f_3210(t3,t4);}}

/* k10036 in k10044 in k10013 in a10010 in k10007 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10038(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-parse-error");
f_3102(((C_word*)t0)[2],lf[355],t1);}

/* k10032 in k10044 in k10013 in a10010 in k10007 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10034(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  errf");
t2=((C_word*)t0)[3];
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k10016 in k10013 in a10010 in k10007 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10018(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_10018,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_10021,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  set-emit-info!");
f_3292(t2,lf[321],lf[319],((C_word*)t0)[3]);}

/* k10019 in k10016 in k10013 in a10010 in k10007 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10021(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  emit");
f_3310(((C_word*)t0)[5],((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k9999 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_10001(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(31488),t1);}

/* k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4732(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4732,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4735,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9910,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(10756),t4);
t6=(C_word)C_a_i_cons(&a,2,C_fix(25088),t5);
t7=(C_word)C_a_i_cons(&a,2,lf[103],t6);
t8=(C_word)C_a_i_cons(&a,2,C_fix(25088),C_SCHEME_END_OF_LIST);
t9=(C_word)C_a_i_cons(&a,2,t7,t8);
t10=(C_word)C_a_i_cons(&a,2,lf[104],t9);
t11=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9916,a[2]=((C_word)li214),tmp=(C_word)a,a+=3,tmp);
t12=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9951,a[2]=((C_word)li216),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t3,lf[354],C_fix(30208),t10,t11,t12);}

/* a9950 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9951(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[9],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_9951,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9957,a[2]=t4,a[3]=t3,a[4]=((C_word)li215),tmp=(C_word)a,a+=5,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9965,a[2]=t5,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3192(t6,t2);}

/* k9963 in a9950 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9965(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("map");
t2=*((C_word*)lf[166]+1);
((C_proc4)(void*)(*((C_word*)t2+1)))(4,t2,((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* a9956 in a9950 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9957(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_9957,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t1,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* a9915 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9916(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_9916,4,t0,t1,t2,t3);}
if(C_truep((C_word)C_i_pairp(t2))){
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_caddr(t2);
t6=(C_word)C_a_i_list(&a,2,t4,t5);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3153(t1,C_fix(30208),t6,C_SCHEME_FALSE);}
else{
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9949,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3153(t4,C_fix(4608),lf[353],C_SCHEME_FALSE);}}

/* k9947 in a9915 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9949(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9949,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,2,((C_word*)t0)[3],t1);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3153(((C_word*)t0)[2],C_fix(30208),t2,C_SCHEME_FALSE);}

/* k9908 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9910(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(30208),t1);}

/* k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4735(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4735,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4738,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9808,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(30208),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(256),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[80],t5);
t7=(C_word)C_a_i_cons(&a,2,t6,C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(30208),t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(20480),t8);
t10=(C_word)C_a_i_cons(&a,2,lf[103],t9);
t11=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9814,a[2]=((C_word)li211),tmp=(C_word)a,a+=3,tmp);
t12=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9857,a[2]=((C_word)li213),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t3,lf[352],C_fix(29952),t10,t11,t12);}

/* a9856 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9857(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_9857,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9861,a[2]=t2,a[3]=t1,a[4]=t4,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  add-emit-info");
f_3282(t5,lf[351],C_SCHEME_TRUE,t3);}

/* k9859 in a9856 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9861(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9861,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9866,a[2]=((C_word*)t0)[4],a[3]=t1,a[4]=((C_word)li212),tmp=(C_word)a,a+=5,tmp);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9874,a[2]=t2,a[3]=((C_word*)t0)[3],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3192(t3,((C_word*)t0)[2]);}

/* k9872 in k9859 in a9856 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9874(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("map");
t2=*((C_word*)lf[166]+1);
((C_proc4)(void*)(*((C_word*)t2+1)))(4,t2,((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* a9865 in k9859 in a9856 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9866(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_9866,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t1,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* a9813 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9814(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_9814,4,t0,t1,t2,t3);}
if(C_truep((C_word)C_i_caddr(t2))){
t4=(C_word)C_i_cadr(t2);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9847,a[2]=t1,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
t6=(C_word)C_i_caddr(t2);
C_trace("ChickenBridge.scm: 145  remove-token-type");
f_4488(t5,t6,C_fix(256));}
else{
t4=(C_word)C_i_cadr(t2);
t5=(C_word)C_a_i_list(&a,1,t4);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3153(t1,C_fix(29952),t5,C_SCHEME_FALSE);}}

/* k9845 in a9813 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9847(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9847,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[3],t1);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3153(((C_word*)t0)[2],C_fix(29952),t2,C_SCHEME_FALSE);}

/* k9806 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9808(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(29952),t1);}

/* k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4738(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4738,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4741,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9722,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(25088),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(27136),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[104],t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(12800),C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(12544),t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(12288),t8);
t10=(C_word)C_a_i_cons(&a,2,C_fix(12032),t9);
t11=(C_word)C_a_i_cons(&a,2,C_fix(11776),t10);
t12=(C_word)C_a_i_cons(&a,2,C_fix(11268),t11);
t13=(C_word)C_a_i_cons(&a,2,C_fix(11012),t12);
t14=(C_word)C_a_i_cons(&a,2,C_fix(10756),t13);
t15=(C_word)C_a_i_cons(&a,2,lf[104],t14);
t16=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t17=(C_word)C_a_i_cons(&a,2,t15,t16);
t18=(C_word)C_a_i_cons(&a,2,t6,t17);
t19=(C_word)C_a_i_cons(&a,2,lf[103],t18);
t20=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9728,a[2]=((C_word)li210),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t3,lf[350],C_fix(30720),t19,t20,C_SCHEME_FALSE);}

/* a9727 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9728(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word *a;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_9728,4,t0,t1,t2,t3);}
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3153(t1,C_fix(30720),t2,C_SCHEME_FALSE);}

/* k9720 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9722(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(30720),t1);}

/* k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4741(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4741,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4744,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9442,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(30720),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(256),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[80],t5);
t7=(C_word)C_a_i_cons(&a,2,t6,C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(30720),t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(16640),t8);
t10=(C_word)C_a_i_cons(&a,2,lf[103],t9);
t11=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9448,a[2]=((C_word)li207),tmp=(C_word)a,a+=3,tmp);
t12=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9491,a[2]=((C_word)li209),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t3,lf[349],C_fix(30464),t10,t11,t12);}

/* a9490 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9491(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_9491,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9495,a[2]=t1,a[3]=t4,a[4]=t3,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3192(t5,t2);}

/* k9493 in a9490 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9495(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_9495,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,lf[136]);
t3=t2;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_SCHEME_UNDEFINED;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=C_set_block_item(t6,0,(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_9503,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=t6,a[5]=t4,a[6]=t2,a[7]=((C_word)li208),tmp=(C_word)a,a+=8,tmp));
t8=((C_word*)t6)[1];
f_9503(t8,((C_word*)t0)[2],t1);}

/* do979 in k9493 in a9490 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_9503(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_9503,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=(C_word)C_i_cddr(((C_word*)t0)[6]);
t4=(C_word)C_i_nullp(t3);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_truep(t4)?(C_word)C_i_cadr(((C_word*)t0)[6]):((C_word*)t0)[6]));}
else{
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_9526,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=t2,a[7]=((C_word*)t0)[5],tmp=(C_word)a,a+=8,tmp);
t4=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3192(t3,t4);}}

/* k9524 in do979 in k9493 in a9490 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9526(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9526,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_9529,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t3=(C_word)C_i_car(t1);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k9527 in k9524 in do979 in k9493 in a9490 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9529(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9529,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_9532,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],tmp=(C_word)a,a+=10,tmp);
t3=(C_word)C_i_cadr(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 145  parse-unit-type");
f_3174(t2,t3);}

/* k9530 in k9527 in k9524 in do979 in k9493 in a9490 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9532(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9532,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_9535,a[2]=t1,a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],tmp=(C_word)a,a+=8,tmp);
t3=(C_word)C_i_caddr(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k9533 in k9530 in k9527 in k9524 in do979 in k9493 in a9490 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9535(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9535,2,t0,t1);}
t2=C_SCHEME_FALSE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_9538,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=t3,tmp=(C_word)a,a+=8,tmp);
t5=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_9595,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t4,a[5]=t1,a[6]=t3,tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4444(t5,((C_word*)t0)[2],C_fix(10756));}

/* k9593 in k9533 in k9530 in k9527 in k9524 in do979 in k9493 in a9490 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9595(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9595,2,t0,t1);}
if(C_truep(t1)){
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,((C_word*)t0)[5]);
t3=((C_word*)t0)[4];
f_9538(t3,t2);}
else{
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_9602,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[3],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4444(t2,((C_word*)t0)[2],C_fix(11776));}}

/* k9600 in k9593 in k9533 in k9530 in k9527 in k9524 in do979 in k9493 in a9490 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9602(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[16],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9602,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,3,lf[122],((C_word*)t0)[6],((C_word*)t0)[5]);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t4=((C_word*)t0)[3];
f_9538(t4,t3);}
else{
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_9612,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4444(t2,((C_word*)t0)[2],C_fix(12032));}}

/* k9610 in k9600 in k9593 in k9533 in k9530 in k9527 in k9524 in do979 in k9493 in a9490 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9612(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[16],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9612,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,3,lf[80],((C_word*)t0)[6],((C_word*)t0)[5]);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t4=((C_word*)t0)[3];
f_9538(t4,t3);}
else{
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_9622,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[5],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4444(t2,((C_word*)t0)[2],C_fix(12288));}}

/* k9620 in k9610 in k9600 in k9593 in k9533 in k9530 in k9527 in k9524 in do979 in k9493 in a9490 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9622(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9622,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,2,lf[346],((C_word*)t0)[6]);
t3=(C_word)C_a_i_list(&a,3,lf[115],((C_word*)t0)[5],t2);
t4=C_mutate(((C_word *)((C_word*)t0)[4])+1,t3);
t5=((C_word*)t0)[3];
f_9538(t5,t4);}
else{
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_9636,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4444(t2,((C_word*)t0)[2],C_fix(12544));}}

/* k9634 in k9620 in k9610 in k9600 in k9593 in k9533 in k9530 in k9527 in k9524 in do979 in k9493 in a9490 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9636(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[16],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9636,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,3,lf[347],((C_word*)t0)[6],((C_word*)t0)[5]);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t4=((C_word*)t0)[3];
f_9538(t4,t3);}
else{
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_9646,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[5],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4444(t2,((C_word*)t0)[2],C_fix(12800));}}

/* k9644 in k9634 in k9620 in k9610 in k9600 in k9593 in k9533 in k9530 in k9527 in k9524 in do979 in k9493 in a9490 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9646(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[16],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9646,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,3,lf[115],((C_word*)t0)[6],((C_word*)t0)[5]);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t4=((C_word*)t0)[3];
f_9538(t4,t3);}
else{
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_9656,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4444(t2,((C_word*)t0)[2],C_fix(11012));}}

/* k9654 in k9644 in k9634 in k9620 in k9610 in k9600 in k9593 in k9533 in k9530 in k9527 in k9524 in do979 in k9493 in a9490 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9656(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[15],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9656,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,3,lf[348],((C_word*)t0)[6],((C_word*)t0)[5]);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t4=((C_word*)t0)[3];
f_9538(t4,t3);}
else{
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_9666,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4444(t2,((C_word*)t0)[2],C_fix(11268));}}

/* k9664 in k9654 in k9644 in k9634 in k9620 in k9610 in k9600 in k9593 in k9533 in k9530 in k9527 in k9524 in do979 in k9493 in a9490 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9666(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9666,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,3,lf[124],((C_word*)t0)[5],((C_word*)t0)[4]);
t3=C_mutate(((C_word *)((C_word*)t0)[3])+1,t2);
t4=((C_word*)t0)[2];
f_9538(t4,t3);}
else{
t2=((C_word*)t0)[2];
f_9538(t2,C_SCHEME_UNDEFINED);}}

/* k9536 in k9533 in k9530 in k9527 in k9524 in do979 in k9493 in a9490 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_9538(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_9538,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_9541,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9562,a[2]=t2,a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[2],tmp=(C_word)a,a+=5,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t0)[2]))){
t4=(C_word)C_i_car(((C_word*)t0)[2]);
t5=t3;
f_9562(t5,(C_word)C_eqp(t4,lf[345]));}
else{
t4=t3;
f_9562(t4,C_SCHEME_FALSE);}}

/* k9560 in k9536 in k9533 in k9530 in k9527 in k9524 in do979 in k9493 in a9490 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_9562(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_9562,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_cadr(((C_word*)t0)[4]);
t3=(C_word)C_i_caddr(((C_word*)t0)[4]);
t4=(C_word)C_a_i_list(&a,3,lf[343],t2,t3);
t5=(C_word)C_a_i_list(&a,3,lf[344],t4,((C_word*)((C_word*)t0)[3])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t5);
t7=((C_word*)t0)[2];
f_9541(t7,t6);}
else{
t2=(C_word)C_a_i_list(&a,3,lf[131],((C_word*)t0)[4],((C_word*)((C_word*)t0)[3])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[3])+1,t2);
t4=((C_word*)t0)[2];
f_9541(t4,t3);}}

/* k9539 in k9536 in k9533 in k9530 in k9527 in k9524 in do979 in k9493 in a9490 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_9541(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_9541,NULL,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,((C_word*)((C_word*)t0)[6])[1]);
t3=(C_word)C_i_set_cdr(((C_word*)((C_word*)t0)[5])[1],t2);
t4=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[5])[1]);
t5=C_mutate(((C_word *)((C_word*)t0)[5])+1,t4);
t6=(C_word)C_i_cdr(((C_word*)t0)[4]);
t7=((C_word*)((C_word*)t0)[3])[1];
f_9503(t7,((C_word*)t0)[2],t6);}

/* a9447 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9448(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_9448,4,t0,t1,t2,t3);}
if(C_truep((C_word)C_i_caddr(t2))){
t4=(C_word)C_i_cadr(t2);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9481,a[2]=t1,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
t6=(C_word)C_i_caddr(t2);
C_trace("ChickenBridge.scm: 145  remove-token-type");
f_4488(t5,t6,C_fix(256));}
else{
t4=(C_word)C_i_cadr(t2);
t5=(C_word)C_a_i_list(&a,1,t4);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3153(t1,C_fix(30464),t5,C_SCHEME_FALSE);}}

/* k9479 in a9447 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9481(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9481,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[3],t1);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3153(((C_word*)t0)[2],C_fix(30464),t2,C_SCHEME_FALSE);}

/* k9440 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9442(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(30464),t1);}

/* k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4744(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4744,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4747,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9328,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29952),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,lf[121],t4);
t6=(C_word)C_a_i_cons(&a,2,C_fix(36608),C_SCHEME_END_OF_LIST);
t7=(C_word)C_a_i_cons(&a,2,lf[80],t6);
t8=(C_word)C_a_i_cons(&a,2,C_fix(18193),C_SCHEME_END_OF_LIST);
t9=(C_word)C_a_i_cons(&a,2,t7,t8);
t10=(C_word)C_a_i_cons(&a,2,t5,t9);
t11=(C_word)C_a_i_cons(&a,2,C_fix(13328),t10);
t12=(C_word)C_a_i_cons(&a,2,lf[103],t11);
t13=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9334,a[2]=((C_word)li205),tmp=(C_word)a,a+=3,tmp);
t14=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9360,a[2]=((C_word)li206),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t3,lf[342],C_fix(32000),t12,t13,t14);}

/* a9359 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9360(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_9360,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9364,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3192(t5,t2);}

/* k9362 in a9359 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9364(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9364,2,t0,t1);}
t2=(C_word)C_i_car(t1);
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_9370,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t2,tmp=(C_word)a,a+=6,tmp);
t4=(C_word)C_i_cdr(t1);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t3,t4,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k9368 in k9362 in a9359 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9370(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9370,2,t0,t1);}
if(C_truep(((C_word*)t0)[5])){
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9390,a[2]=((C_word*)t0)[4],a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t2,((C_word*)t0)[5],((C_word*)t0)[3],((C_word*)t0)[2]);}
else{
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_cons(&a,2,lf[136],t1));}}

/* k9388 in k9368 in k9362 in a9359 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9390(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_9390,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,t1,((C_word*)t0)[3]);
t3=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_cons(&a,2,lf[271],t2));}

/* a9333 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9334(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_9334,4,t0,t1,t2,t3);}
t4=(C_word)C_i_cadr(t2);
t5=t4;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(C_word)C_i_caddr(t2);
t8=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9344,a[2]=t1,a[3]=t7,a[4]=t6,tmp=(C_word)a,a+=5,tmp);
t9=((C_word*)t6)[1];
if(C_truep(t9)){
t10=(C_word)C_i_car(((C_word*)t6)[1]);
t11=C_set_block_item(t6,0,t10);
t12=t8;
f_9344(t12,t11);}
else{
t10=t8;
f_9344(t10,C_SCHEME_FALSE);}}

/* k9342 in a9333 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_9344(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_9344,NULL,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)((C_word*)t0)[4])[1],((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3153(((C_word*)t0)[2],C_fix(32000),t2,C_SCHEME_FALSE);}

/* k9326 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9328(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(32000),t1);}

/* k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4747(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4747,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4750,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9131,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(36608),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,lf[121],t4);
t6=(C_word)C_a_i_cons(&a,2,C_fix(36608),C_SCHEME_END_OF_LIST);
t7=(C_word)C_a_i_cons(&a,2,C_fix(17920),t6);
t8=(C_word)C_a_i_cons(&a,2,lf[121],t7);
t9=(C_word)C_a_i_cons(&a,2,t8,C_SCHEME_END_OF_LIST);
t10=(C_word)C_a_i_cons(&a,2,t5,t9);
t11=(C_word)C_a_i_cons(&a,2,C_fix(18944),t10);
t12=(C_word)C_a_i_cons(&a,2,C_fix(29696),t11);
t13=(C_word)C_a_i_cons(&a,2,C_fix(14336),t12);
t14=(C_word)C_a_i_cons(&a,2,lf[103],t13);
t15=(C_word)C_a_i_cons(&a,2,C_fix(36608),C_SCHEME_END_OF_LIST);
t16=(C_word)C_a_i_cons(&a,2,C_fix(29696),t15);
t17=(C_word)C_a_i_cons(&a,2,C_fix(19968),t16);
t18=(C_word)C_a_i_cons(&a,2,lf[103],t17);
t19=(C_word)C_a_i_cons(&a,2,C_fix(36608),C_SCHEME_END_OF_LIST);
t20=(C_word)C_a_i_cons(&a,2,C_fix(29696),t19);
t21=(C_word)C_a_i_cons(&a,2,C_fix(19200),t20);
t22=(C_word)C_a_i_cons(&a,2,lf[103],t21);
t23=(C_word)C_a_i_cons(&a,2,t22,C_SCHEME_END_OF_LIST);
t24=(C_word)C_a_i_cons(&a,2,t18,t23);
t25=(C_word)C_a_i_cons(&a,2,t14,t24);
t26=(C_word)C_a_i_cons(&a,2,lf[104],t25);
t27=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9137,a[2]=((C_word)li203),tmp=(C_word)a,a+=3,tmp);
t28=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_9205,a[2]=((C_word)li204),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t3,lf[341],C_fix(32256),t26,t27,t28);}

/* a9204 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9205(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_9205,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_9209,a[2]=t4,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3192(t5,t2);}

/* k9207 in a9204 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9209(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  emit");
f_3310(((C_word*)t0)[4],t1,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* a9136 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9137(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_9137,4,t0,t1,t2,t3);}
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cadr(t2);
t6=C_SCHEME_END_OF_LIST;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9150,a[2]=t7,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
t9=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_9156,a[2]=t8,a[3]=t7,a[4]=t5,a[5]=t4,a[6]=t2,tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3238(t9,t4,C_fix(14336));}

/* k9154 in a9136 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9156(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_9156,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_cadddr(((C_word*)t0)[6]);
t3=t2;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=C_SCHEME_FALSE;
t8=(*a=C_VECTOR_TYPE|1,a[1]=t7,tmp=(C_word)a,a+=2,tmp);
t9=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_9162,a[2]=((C_word*)t0)[6],a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=t8,a[6]=t6,a[7]=((C_word*)t0)[4],a[8]=((C_word*)t0)[5],a[9]=t4,tmp=(C_word)a,a+=10,tmp);
t10=((C_word*)t4)[1];
if(C_truep(t10)){
t11=(C_word)C_i_car(((C_word*)t4)[1]);
t12=C_set_block_item(t6,0,t11);
t13=t9;
f_9162(t13,t12);}
else{
t11=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9191,a[2]=t9,a[3]=t6,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3153(t11,C_fix(4608),lf[340],C_SCHEME_FALSE);}}
else{
t2=(C_word)C_i_caddr(((C_word*)t0)[6]);
t3=(C_word)C_a_i_list(&a,3,((C_word*)t0)[5],((C_word*)t0)[4],t2);
t4=C_mutate(((C_word *)((C_word*)t0)[3])+1,t3);
t5=((C_word*)t0)[2];
f_9150(t5,t4);}}

/* k9189 in k9154 in a9136 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9191(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_9162(t3,t2);}

/* k9160 in k9154 in a9136 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_9162(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_9162,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_9166,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],a[8]=((C_word*)t0)[9],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 145  fifth");
t3=C_retrieve(lf[139]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)t0)[2]);}

/* k9164 in k9160 in k9154 in a9136 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9166(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_9166,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_9169,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
t4=((C_word*)((C_word*)t0)[8])[1];
if(C_truep(t4)){
t5=(C_word)C_i_cadr(((C_word*)((C_word*)t0)[8])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[4])+1,t5);
t7=t3;
f_9169(t7,t6);}
else{
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_9180,a[2]=t3,a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3153(t5,C_fix(4608),lf[339],C_SCHEME_FALSE);}}

/* k9178 in k9164 in k9160 in k9154 in a9136 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9180(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_9169(t3,t2);}

/* k9167 in k9164 in k9160 in k9154 in a9136 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_9169(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_9169,NULL,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,4,((C_word*)t0)[7],((C_word*)t0)[6],((C_word*)((C_word*)t0)[5])[1],((C_word*)((C_word*)t0)[4])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[3])+1,t2);
t4=((C_word*)t0)[2];
f_9150(t4,t3);}

/* k9148 in a9136 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_9150(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3153(((C_word*)t0)[3],C_fix(32256),((C_word*)((C_word*)t0)[2])[1],C_SCHEME_FALSE);}

/* k9129 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_9131(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(32256),t1);}

/* k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4750(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4750,2,t0,t1);}
t2=C_mutate(&lf[130],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4752,a[2]=((C_word)li104),tmp=(C_word)a,a+=3,tmp));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5273,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8859,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
t5=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t6=(C_word)C_a_i_cons(&a,2,C_fix(23296),t5);
t7=(C_word)C_a_i_cons(&a,2,lf[103],t6);
t8=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t9=(C_word)C_a_i_cons(&a,2,C_fix(18944),t8);
t10=(C_word)C_a_i_cons(&a,2,lf[121],t9);
t11=(C_word)C_a_i_cons(&a,2,t10,C_SCHEME_END_OF_LIST);
t12=(C_word)C_a_i_cons(&a,2,C_fix(29696),t11);
t13=(C_word)C_a_i_cons(&a,2,C_fix(10756),t12);
t14=(C_word)C_a_i_cons(&a,2,C_fix(25088),t13);
t15=(C_word)C_a_i_cons(&a,2,C_fix(22272),t14);
t16=(C_word)C_a_i_cons(&a,2,lf[103],t15);
t17=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t18=(C_word)C_a_i_cons(&a,2,C_fix(22784),t17);
t19=(C_word)C_a_i_cons(&a,2,C_fix(25088),t18);
t20=(C_word)C_a_i_cons(&a,2,C_fix(22272),t19);
t21=(C_word)C_a_i_cons(&a,2,lf[103],t20);
t22=(C_word)C_a_i_cons(&a,2,C_fix(21760),C_SCHEME_END_OF_LIST);
t23=(C_word)C_a_i_cons(&a,2,C_fix(20992),t22);
t24=(C_word)C_a_i_cons(&a,2,C_fix(23552),t23);
t25=(C_word)C_a_i_cons(&a,2,C_fix(21248),t24);
t26=(C_word)C_a_i_cons(&a,2,lf[104],t25);
t27=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t28=(C_word)C_a_i_cons(&a,2,t26,t27);
t29=(C_word)C_a_i_cons(&a,2,lf[121],t28);
t30=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t31=(C_word)C_a_i_cons(&a,2,C_fix(21504),t30);
t32=(C_word)C_a_i_cons(&a,2,lf[121],t31);
t33=(C_word)C_a_i_cons(&a,2,t32,C_SCHEME_END_OF_LIST);
t34=(C_word)C_a_i_cons(&a,2,t29,t33);
t35=(C_word)C_a_i_cons(&a,2,C_fix(29696),t34);
t36=(C_word)C_a_i_cons(&a,2,C_fix(22528),t35);
t37=(C_word)C_a_i_cons(&a,2,C_fix(25088),t36);
t38=(C_word)C_a_i_cons(&a,2,C_fix(22272),t37);
t39=(C_word)C_a_i_cons(&a,2,lf[103],t38);
t40=(C_word)C_a_i_cons(&a,2,C_fix(21760),C_SCHEME_END_OF_LIST);
t41=(C_word)C_a_i_cons(&a,2,C_fix(20992),t40);
t42=(C_word)C_a_i_cons(&a,2,C_fix(23552),t41);
t43=(C_word)C_a_i_cons(&a,2,C_fix(21248),t42);
t44=(C_word)C_a_i_cons(&a,2,lf[104],t43);
t45=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t46=(C_word)C_a_i_cons(&a,2,C_fix(21504),t45);
t47=(C_word)C_a_i_cons(&a,2,lf[121],t46);
t48=(C_word)C_a_i_cons(&a,2,t47,C_SCHEME_END_OF_LIST);
t49=(C_word)C_a_i_cons(&a,2,C_fix(29696),t48);
t50=(C_word)C_a_i_cons(&a,2,t44,t49);
t51=(C_word)C_a_i_cons(&a,2,C_fix(25088),t50);
t52=(C_word)C_a_i_cons(&a,2,C_fix(22272),t51);
t53=(C_word)C_a_i_cons(&a,2,lf[103],t52);
t54=(C_word)C_a_i_cons(&a,2,t53,C_SCHEME_END_OF_LIST);
t55=(C_word)C_a_i_cons(&a,2,t39,t54);
t56=(C_word)C_a_i_cons(&a,2,t21,t55);
t57=(C_word)C_a_i_cons(&a,2,t16,t56);
t58=(C_word)C_a_i_cons(&a,2,t7,t57);
t59=(C_word)C_a_i_cons(&a,2,lf[104],t58);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t4,lf[338],C_fix(33024),t59,C_retrieve2(lf[130],"sal-parse-stepping"),C_SCHEME_FALSE);}

/* k8857 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8859(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(33024),t1);}

/* k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5273(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5273,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5276,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8803,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(20224),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[103],t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(29696),C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(19456),t7);
t9=(C_word)C_a_i_cons(&a,2,lf[103],t8);
t10=(C_word)C_a_i_cons(&a,2,t9,C_SCHEME_END_OF_LIST);
t11=(C_word)C_a_i_cons(&a,2,t6,t10);
t12=(C_word)C_a_i_cons(&a,2,lf[104],t11);
t13=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8811,a[2]=t12,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  simple-unit-parser");
f_3551(t13,C_fix(33280));}

/* k8809 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8811(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(((C_word*)t0)[3],lf[337],C_fix(33280),((C_word*)t0)[2],t1,C_SCHEME_FALSE);}

/* k8801 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8803(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(33280),t1);}

/* k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5276(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5276,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5795,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8631,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(16144),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(14864),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[104],t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(29952),C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,lf[121],t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(33024),C_SCHEME_END_OF_LIST);
t10=(C_word)C_a_i_cons(&a,2,lf[80],t9);
t11=(C_word)C_a_i_cons(&a,2,C_fix(33280),C_SCHEME_END_OF_LIST);
t12=(C_word)C_a_i_cons(&a,2,lf[80],t11);
t13=(C_word)C_a_i_cons(&a,2,C_fix(36608),C_SCHEME_END_OF_LIST);
t14=(C_word)C_a_i_cons(&a,2,lf[122],t13);
t15=(C_word)C_a_i_cons(&a,2,C_fix(36608),C_SCHEME_END_OF_LIST);
t16=(C_word)C_a_i_cons(&a,2,C_fix(22016),t15);
t17=(C_word)C_a_i_cons(&a,2,lf[121],t16);
t18=(C_word)C_a_i_cons(&a,2,C_fix(18193),C_SCHEME_END_OF_LIST);
t19=(C_word)C_a_i_cons(&a,2,t17,t18);
t20=(C_word)C_a_i_cons(&a,2,t14,t19);
t21=(C_word)C_a_i_cons(&a,2,t12,t20);
t22=(C_word)C_a_i_cons(&a,2,t10,t21);
t23=(C_word)C_a_i_cons(&a,2,t8,t22);
t24=(C_word)C_a_i_cons(&a,2,t6,t23);
t25=(C_word)C_a_i_cons(&a,2,lf[103],t24);
t26=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8637,a[2]=((C_word)li197),tmp=(C_word)a,a+=3,tmp);
t27=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8683,a[2]=((C_word)li202),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t3,lf[336],C_fix(32512),t25,t26,t27);}

/* a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8683(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[7],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_8683,5,t0,t1,t2,t3,t4);}
t5=t3;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5282,a[2]=t4,a[3]=t6,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3192(t7,t2);}

/* k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5282(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5282,2,t0,t1);}
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
t16=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_5300,a[2]=t11,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=t7,a[6]=((C_word*)t0)[4],a[7]=t15,a[8]=t13,a[9]=t5,a[10]=t9,a[11]=t3,tmp=(C_word)a,a+=12,tmp);
t17=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5754,a[2]=t3,a[3]=((C_word*)t0)[2],a[4]=t5,a[5]=t16,a[6]=((C_word*)t0)[3],tmp=(C_word)a,a+=7,tmp);
t18=(C_word)C_i_car(((C_word*)t3)[1]);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3238(t17,t18,C_fix(14864));}

/* k5752 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5754(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[14],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5754,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5758,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  add-emit-info");
f_3282(t2,lf[333],C_SCHEME_TRUE,((C_word*)((C_word*)t0)[6])[1]);}
else{
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5761,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5788,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  get-emit-info");
f_3270(t3,lf[323],((C_word*)((C_word*)t0)[6])[1]);}}

/* k5786 in k5752 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5788(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5788,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
f_5761(2,t2,C_SCHEME_UNDEFINED);}
else{
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5776,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[3],tmp=(C_word)a,a+=4,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5780,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_i_car(((C_word*)((C_word*)t0)[2])[1]);
C_trace("ChickenBridge.scm: 145  parse-unit-position");
f_3210(t3,t4);}}

/* k5778 in k5786 in k5752 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5780(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-parse-error");
f_3102(((C_word*)t0)[2],lf[335],t1);}

/* k5774 in k5786 in k5752 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5776(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  errf");
t2=((C_word*)t0)[3];
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k5759 in k5752 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5761(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5761,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5765,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  add-emit-info");
f_3282(t2,lf[334],C_SCHEME_TRUE,((C_word*)((C_word*)t0)[4])[1]);}

/* k5763 in k5759 in k5752 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5765(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[4])+1,t1);
t3=C_set_block_item(((C_word*)t0)[3],0,C_SCHEME_TRUE);
t4=((C_word*)t0)[2];
f_5300(t4,t3);}

/* k5756 in k5752 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5758(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_5300(t3,t2);}

/* k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_5300(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_5300,NULL,2,t0,t1);}
t2=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[11])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[11])+1,t2);
t4=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_5307,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[11],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],a[10]=((C_word*)t0)[9],a[11]=((C_word*)t0)[10],tmp=(C_word)a,a+=12,tmp);
if(C_truep((C_word)C_i_car(((C_word*)((C_word*)t0)[11])[1]))){
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5743,a[2]=t4,a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5747,a[2]=((C_word*)t0)[5],a[3]=t5,tmp=(C_word)a,a+=4,tmp);
t7=(C_word)C_i_car(((C_word*)((C_word*)t0)[11])[1]);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t6,t7,((C_word*)((C_word*)t0)[4])[1],((C_word*)t0)[3]);}
else{
t5=t4;
f_5307(t5,C_SCHEME_UNDEFINED);}}

/* k5745 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5747(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  append");
t2=*((C_word*)lf[115]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k5741 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5743(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_5307(t3,t2);}

/* k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_5307(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_5307,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_5310,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],a[10]=((C_word*)t0)[10],a[11]=((C_word*)t0)[11],tmp=(C_word)a,a+=12,tmp);
t3=(C_word)C_i_cadr(((C_word*)((C_word*)t0)[3])[1]);
t4=C_SCHEME_UNDEFINED;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_set_block_item(t5,0,(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5618,a[2]=((C_word*)t0)[11],a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[9],a[5]=((C_word*)t0)[6],a[6]=t5,a[7]=((C_word)li201),tmp=(C_word)a,a+=8,tmp));
t7=((C_word*)t5)[1];
f_5618(t7,t2,t3);}

/* do1089 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_5618(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5618,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5628,a[2]=t1,a[3]=((C_word*)t0)[6],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5639,a[2]=t3,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],tmp=(C_word)a,a+=7,tmp);
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3192(t4,t5);}}

/* k5637 in do1089 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5639(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5639,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5641,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=t3,a[6]=((C_word*)t0)[6],a[7]=((C_word)li200),tmp=(C_word)a,a+=8,tmp));
t5=((C_word*)t3)[1];
f_5641(t5,((C_word*)t0)[2],t1);}

/* do1092 in k5637 in do1089 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_5641(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_5641,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(C_word)C_i_car(t2);
t4=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_5655,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t3,a[5]=((C_word*)t0)[4],a[6]=t1,a[7]=((C_word*)t0)[5],a[8]=t2,a[9]=((C_word*)t0)[6],tmp=(C_word)a,a+=10,tmp);
t5=(C_word)C_i_car(t3);
t6=(C_word)C_i_cadr(t3);
t7=(C_word)C_a_i_list(&a,2,t5,t6);
t8=(C_word)C_a_i_list(&a,1,t7);
C_trace("ChickenBridge.scm: 145  append");
t9=*((C_word*)lf[115]+1);
((C_proc4)C_retrieve_proc(t9))(4,t9,t4,((C_word*)((C_word*)t0)[6])[1],t8);}}

/* k5653 in do1092 in k5637 in do1089 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5655(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5655,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[9])+1,t1);
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5658,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],tmp=(C_word)a,a+=8,tmp);
if(C_truep((C_word)C_i_caddr(((C_word*)t0)[4]))){
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5708,a[2]=t3,a[3]=((C_word*)t0)[2],tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_i_caddr(((C_word*)t0)[4]);
t6=(C_word)C_a_i_list(&a,1,t5);
C_trace("ChickenBridge.scm: 145  append");
t7=*((C_word*)lf[115]+1);
((C_proc4)C_retrieve_proc(t7))(4,t7,t4,((C_word*)((C_word*)t0)[2])[1],t6);}
else{
t4=t3;
f_5658(t4,C_SCHEME_UNDEFINED);}}

/* k5706 in k5653 in do1092 in k5637 in do1089 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5708(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_5658(t3,t2);}

/* k5656 in k5653 in do1092 in k5637 in do1089 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_5658(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[14],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5658,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5661,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
if(C_truep((C_word)C_i_cadddr(((C_word*)t0)[3]))){
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5693,a[2]=t2,a[3]=((C_word*)t0)[2],tmp=(C_word)a,a+=4,tmp);
t4=(C_word)C_i_cadddr(((C_word*)t0)[3]);
t5=(C_word)C_a_i_list(&a,1,t4);
C_trace("ChickenBridge.scm: 145  append");
t6=*((C_word*)lf[115]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t3,((C_word*)((C_word*)t0)[2])[1],t5);}
else{
t3=t2;
f_5661(t3,C_SCHEME_UNDEFINED);}}

/* k5691 in k5656 in k5653 in do1092 in k5637 in do1089 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5693(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_5661(t3,t2);}

/* k5659 in k5656 in k5653 in do1092 in k5637 in do1089 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_5661(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5661,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5664,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5674,a[2]=((C_word*)t0)[2],a[3]=t2,a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  fifth");
t4=C_retrieve(lf[139]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)t0)[2]);}

/* k5672 in k5659 in k5656 in k5653 in do1092 in k5637 in do1089 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5674(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5674,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5678,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5686,a[2]=((C_word*)t0)[4],a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  fifth");
t4=C_retrieve(lf[139]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)t0)[2]);}
else{
t2=((C_word*)t0)[3];
f_5664(t2,C_SCHEME_UNDEFINED);}}

/* k5684 in k5672 in k5659 in k5656 in k5653 in do1092 in k5637 in do1089 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5686(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5686,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,t1);
C_trace("ChickenBridge.scm: 145  append");
t3=*((C_word*)lf[115]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t2);}

/* k5676 in k5672 in k5659 in k5656 in k5653 in do1092 in k5637 in do1089 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5678(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_5664(t3,t2);}

/* k5662 in k5659 in k5656 in k5653 in do1092 in k5637 in do1089 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_5664(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_5641(t3,((C_word*)t0)[2],t2);}

/* k5626 in do1089 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5628(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_5618(t3,((C_word*)t0)[2],t2);}

/* k5308 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5310(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5310,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_5313,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],a[10]=((C_word*)t0)[10],a[11]=((C_word*)t0)[11],tmp=(C_word)a,a+=12,tmp);
t3=(C_word)C_i_cadddr(((C_word*)((C_word*)t0)[3])[1]);
t4=C_SCHEME_UNDEFINED;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_set_block_item(t5,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5582,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=t5,a[5]=((C_word*)t0)[11],a[6]=((C_word)li199),tmp=(C_word)a,a+=7,tmp));
t7=((C_word*)t5)[1];
f_5582(t7,t2,t3);}

/* do1103 in k5308 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_5582(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5582,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_5593,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=t2,a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5608,a[2]=((C_word*)t0)[5],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t4,t5,((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]);}}

/* k5606 in do1103 in k5308 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5608(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5608,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,t1);
C_trace("ChickenBridge.scm: 145  append");
t3=*((C_word*)lf[115]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t2);}

/* k5591 in do1103 in k5308 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5593(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[5])+1,t1);
t3=(C_word)C_i_cdr(((C_word*)t0)[4]);
t4=((C_word*)((C_word*)t0)[3])[1];
f_5582(t4,((C_word*)t0)[2],t3);}

/* k5311 in k5308 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5313(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5313,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_5317,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],a[8]=((C_word*)t0)[9],a[9]=((C_word*)t0)[10],a[10]=((C_word*)t0)[11],tmp=(C_word)a,a+=11,tmp);
C_trace("ChickenBridge.scm: 145  append");
t3=*((C_word*)lf[115]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t2,((C_word*)((C_word*)t0)[11])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k5315 in k5311 in k5308 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5317(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5317,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[10])+1,t1);
t3=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_5320,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[10],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],a[10]=((C_word*)t0)[9],tmp=(C_word)a,a+=11,tmp);
t4=(C_word)C_i_caddr(((C_word*)((C_word*)t0)[2])[1]);
t5=C_SCHEME_UNDEFINED;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=C_set_block_item(t6,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5526,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=t6,a[5]=((C_word*)t0)[8],a[6]=((C_word)li198),tmp=(C_word)a,a+=7,tmp));
t8=((C_word*)t6)[1];
f_5526(t8,t3,t4);}

/* do1108 in k5315 in k5311 in k5308 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_5526(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5526,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5536,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=t2,a[7]=((C_word*)t0)[5],tmp=(C_word)a,a+=8,tmp);
t4=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3192(t3,t4);}}

/* k5534 in do1108 in k5315 in k5311 in k5308 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5536(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5536,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5539,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
t3=(C_word)C_i_cadr(t1);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t2,t3,((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]);}

/* k5537 in k5534 in do1108 in k5315 in k5311 in k5308 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5539(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5539,2,t0,t1);}
t2=t1;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5542,a[2]=t3,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5560,a[2]=t4,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t6=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3238(t5,t6,C_fix(20224));}

/* k5558 in k5537 in k5534 in do1108 in k5315 in k5311 in k5308 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5560(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5560,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,2,lf[105],((C_word*)((C_word*)t0)[3])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[3])+1,t2);
t4=((C_word*)t0)[2];
f_5542(t4,t3);}
else{
t2=((C_word*)t0)[2];
f_5542(t2,C_SCHEME_UNDEFINED);}}

/* k5540 in k5537 in k5534 in do1108 in k5315 in k5311 in k5308 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_5542(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5542,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_5546,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],tmp=(C_word)a,a+=6,tmp);
t3=(C_word)C_a_i_list(&a,1,((C_word*)((C_word*)t0)[2])[1]);
C_trace("ChickenBridge.scm: 145  append");
t4=*((C_word*)lf[115]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,((C_word*)((C_word*)t0)[6])[1],t3);}

/* k5544 in k5540 in k5537 in k5534 in do1108 in k5315 in k5311 in k5308 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5546(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[5])+1,t1);
t3=(C_word)C_i_cdr(((C_word*)t0)[4]);
t4=((C_word*)((C_word*)t0)[3])[1];
f_5526(t4,((C_word*)t0)[2],t3);}

/* k5318 in k5315 in k5311 in k5308 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5320(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5320,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_5323,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],a[10]=((C_word*)t0)[10],tmp=(C_word)a,a+=11,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)((C_word*)t0)[9])[1]))){
t3=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[9])[1]);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(C_word)C_i_car(((C_word*)((C_word*)t0)[9])[1]);
t5=C_mutate(((C_word *)((C_word*)t0)[9])+1,t4);
t6=t2;
f_5323(t6,t5);}
else{
t4=(C_word)C_a_i_cons(&a,2,lf[104],((C_word*)((C_word*)t0)[9])[1]);
t5=C_mutate(((C_word *)((C_word*)t0)[9])+1,t4);
t6=t2;
f_5323(t6,t5);}}
else{
t3=C_set_block_item(((C_word*)t0)[9],0,C_SCHEME_FALSE);
t4=t2;
f_5323(t4,t3);}}

/* k5321 in k5318 in k5315 in k5311 in k5308 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_5323(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[15],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5323,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5326,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],a[5]=((C_word*)t0)[8],a[6]=((C_word*)t0)[9],a[7]=((C_word*)t0)[10],tmp=(C_word)a,a+=8,tmp);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5489,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t2,a[6]=((C_word*)t0)[8],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  fifth");
t4=C_retrieve(lf[139]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)((C_word*)t0)[2])[1]);}

/* k5487 in k5321 in k5318 in k5315 in k5311 in k5308 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5489(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5489,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5493,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],tmp=(C_word)a,a+=4,tmp);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5497,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  fifth");
t4=C_retrieve(lf[139]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)((C_word*)t0)[2])[1]);}
else{
t2=C_set_block_item(((C_word*)t0)[6],0,C_SCHEME_FALSE);
t3=((C_word*)t0)[5];
f_5326(t3,t2);}}

/* k5495 in k5487 in k5321 in k5318 in k5315 in k5311 in k5308 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5497(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  emit");
f_3310(((C_word*)t0)[4],t1,((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]);}

/* k5491 in k5487 in k5321 in k5318 in k5315 in k5311 in k5308 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5493(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_5326(t3,t2);}

/* k5324 in k5321 in k5318 in k5315 in k5311 in k5308 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_5326(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_5326,NULL,2,t0,t1);}
t2=((C_word*)((C_word*)t0)[7])[1];
if(C_truep(t2)){
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5354,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  gensym");
t4=C_retrieve(lf[133]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,lf[331]);}
else{
t3=(C_word)C_a_i_list(&a,2,((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[5])[1]);
t4=(C_word)C_a_i_cons(&a,2,t3,((C_word*)((C_word*)t0)[2])[1]);
t5=(C_word)C_a_i_cons(&a,2,C_SCHEME_END_OF_LIST,t4);
t6=(C_word)C_a_i_cons(&a,2,lf[332],t5);
t7=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)C_a_i_list(&a,3,lf[271],((C_word*)((C_word*)t0)[3])[1],t6));}}

/* k5352 in k5324 in k5321 in k5318 in k5315 in k5311 in k5308 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5354(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5354,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5357,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 145  gensym");
t3=C_retrieve(lf[133]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,lf[330]);}

/* k5355 in k5352 in k5324 in k5321 in k5318 in k5315 in k5311 in k5308 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5357(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5357,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_5360,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 145  gensym");
t3=C_retrieve(lf[133]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,lf[329]);}

/* k5358 in k5355 in k5352 in k5324 in k5321 in k5318 in k5315 in k5311 in k5308 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5360(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5360,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_5363,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 145  gensym");
t3=C_retrieve(lf[133]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,lf[328]);}

/* k5361 in k5358 in k5355 in k5352 in k5324 in k5321 in k5318 in k5315 in k5311 in k5308 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5363(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5363,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,((C_word*)t0)[9]);
t3=(C_word)C_a_i_list(&a,2,((C_word*)t0)[8],C_fix(0));
t4=(C_word)C_a_i_list(&a,3,lf[267],C_SCHEME_END_OF_LIST,((C_word*)t0)[9]);
t5=(C_word)C_a_i_list(&a,2,lf[268],t4);
t6=(C_word)C_a_i_list(&a,1,lf[269]);
t7=(C_word)C_a_i_list(&a,3,lf[131],((C_word*)t0)[8],lf[269]);
t8=(C_word)C_a_i_list(&a,3,lf[267],t6,t7);
t9=(C_word)C_a_i_list(&a,2,lf[270],t8);
t10=(C_word)C_a_i_list(&a,3,t3,t5,t9);
t11=(C_word)C_a_i_list(&a,1,t1);
t12=(C_word)C_a_i_list(&a,1,((C_word*)t0)[7]);
t13=(C_word)C_a_i_list(&a,2,lf[272],lf[260]);
t14=(C_word)C_a_i_list(&a,2,lf[272],lf[261]);
t15=(C_word)C_a_i_list(&a,3,lf[259],t13,t14);
t16=(C_word)C_a_i_list(&a,2,t15,((C_word*)t0)[7]);
t17=(C_word)C_a_i_list(&a,4,lf[174],lf[327],t16,((C_word*)t0)[9]);
t18=(C_word)C_a_i_list(&a,2,lf[155],t17);
t19=(C_word)C_a_i_list(&a,2,t1,C_fix(-2));
t20=(C_word)C_a_i_list(&a,4,lf[267],t12,t18,t19);
t21=(C_word)C_a_i_list(&a,3,((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[5])[1],C_fix(-1));
t22=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_5422,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=t2,a[5]=t10,a[6]=t11,a[7]=t20,a[8]=t21,tmp=(C_word)a,a+=9,tmp);
t23=(C_word)C_a_i_list(&a,1,((C_word*)t0)[8]);
C_trace("##sys#append");
t24=*((C_word*)lf[274]+1);
((C_proc4)(void*)(*((C_word*)t24+1)))(4,t24,t22,((C_word*)((C_word*)t0)[2])[1],t23);}

/* k5420 in k5361 in k5358 in k5355 in k5352 in k5324 in k5321 in k5318 in k5315 in k5311 in k5308 in k5305 in k5298 in k5280 in a8682 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5422(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5422,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,lf[265],t1);
t3=(C_word)C_a_i_list(&a,3,lf[266],((C_word*)t0)[8],t2);
t4=(C_word)C_a_i_list(&a,3,lf[267],C_SCHEME_END_OF_LIST,t3);
t5=(C_word)C_a_i_list(&a,3,lf[262],((C_word*)t0)[7],t4);
t6=(C_word)C_a_i_list(&a,3,lf[267],((C_word*)t0)[6],t5);
t7=(C_word)C_a_i_list(&a,2,lf[263],t6);
t8=(C_word)C_a_i_list(&a,3,lf[271],((C_word*)t0)[5],t7);
t9=(C_word)C_a_i_list(&a,3,lf[267],((C_word*)t0)[4],t8);
t10=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t10+1)))(2,t10,(C_word)C_a_i_list(&a,3,lf[271],((C_word*)((C_word*)t0)[2])[1],t9));}

/* a8636 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8637(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_8637,4,t0,t1,t2,t3);}
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cadr(t2);
t6=t5;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=(C_word)C_i_caddr(t2);
t9=(C_word)C_i_cadddr(t2);
t10=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_8653,a[2]=t2,a[3]=t1,a[4]=t9,a[5]=t8,a[6]=t7,a[7]=t4,tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 145  fifth");
t11=C_retrieve(lf[139]);
((C_proc3)C_retrieve_proc(t11))(3,t11,t10,t2);}

/* k8651 in a8636 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8653(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8653,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_8656,a[2]=((C_word*)t0)[3],a[3]=t1,a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 145  sixth");
t3=C_retrieve(lf[199]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)t0)[2]);}

/* k8654 in k8651 in a8636 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8656(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_8656,2,t0,t1);}
t2=t1;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_8659,a[2]=((C_word*)t0)[2],a[3]=t3,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
if(C_truep(((C_word*)((C_word*)t0)[6])[1])){
t5=(C_word)C_i_car(((C_word*)((C_word*)t0)[6])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[6])+1,t5);
t7=t4;
f_8659(t7,t6);}
else{
t5=t4;
f_8659(t5,C_SCHEME_UNDEFINED);}}

/* k8657 in k8654 in k8651 in a8636 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_8659(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_8659,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_8662,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
if(C_truep(((C_word*)((C_word*)t0)[3])[1])){
t3=(C_word)C_i_cadr(((C_word*)((C_word*)t0)[3])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[3])+1,t3);
t5=t2;
f_8662(t5,t4);}
else{
t3=t2;
f_8662(t3,C_SCHEME_UNDEFINED);}}

/* k8660 in k8657 in k8654 in k8651 in a8636 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_8662(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_8662,NULL,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,6,((C_word*)t0)[8],((C_word*)((C_word*)t0)[7])[1],((C_word*)t0)[6],((C_word*)t0)[5],((C_word*)t0)[4],((C_word*)((C_word*)t0)[3])[1]);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8673,a[2]=t2,a[3]=((C_word*)t0)[2],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-position");
f_3210(t3,((C_word*)t0)[8]);}

/* k8671 in k8660 in k8657 in k8654 in k8651 in a8636 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8673(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3153(((C_word*)t0)[3],C_fix(32512),((C_word*)t0)[2],t1);}

/* k8629 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8631(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(32512),t1);}

/* k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5795(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5795,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5798,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8486,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(768),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(512),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[103],t5);
t7=(C_word)C_a_i_cons(&a,2,C_fix(25088),C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(256),t7);
t9=(C_word)C_a_i_cons(&a,2,lf[80],t8);
t10=(C_word)C_a_i_cons(&a,2,C_fix(768),C_SCHEME_END_OF_LIST);
t11=(C_word)C_a_i_cons(&a,2,t9,t10);
t12=(C_word)C_a_i_cons(&a,2,C_fix(25088),t11);
t13=(C_word)C_a_i_cons(&a,2,C_fix(512),t12);
t14=(C_word)C_a_i_cons(&a,2,lf[103],t13);
t15=(C_word)C_a_i_cons(&a,2,t14,C_SCHEME_END_OF_LIST);
t16=(C_word)C_a_i_cons(&a,2,t6,t15);
t17=(C_word)C_a_i_cons(&a,2,lf[104],t16);
t18=(C_word)C_a_i_cons(&a,2,C_fix(36608),C_SCHEME_END_OF_LIST);
t19=(C_word)C_a_i_cons(&a,2,t17,t18);
t20=(C_word)C_a_i_cons(&a,2,C_fix(25088),t19);
t21=(C_word)C_a_i_cons(&a,2,lf[103],t20);
t22=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8492,a[2]=((C_word)li196),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t3,lf[326],C_fix(37632),t21,t22,C_SCHEME_FALSE);}

/* a8491 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8492(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_8492,4,t0,t1,t2,t3);}
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cadr(t2);
t6=t5;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=(C_word)C_i_caddr(t2);
t9=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_8505,a[2]=t1,a[3]=t8,a[4]=t7,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
t10=(C_word)C_i_length(((C_word*)t7)[1]);
if(C_truep((C_word)C_i_nequalp(t10,C_fix(2)))){
t11=C_set_block_item(t7,0,C_SCHEME_END_OF_LIST);
t12=t9;
f_8505(t12,t11);}
else{
t11=(C_word)C_i_cadr(((C_word*)t7)[1]);
t12=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_8531,a[2]=t9,a[3]=t7,a[4]=t11,tmp=(C_word)a,a+=5,tmp);
t13=(C_word)C_i_caddr(((C_word*)t7)[1]);
C_trace("ChickenBridge.scm: 145  remove-token-type");
f_4488(t12,t13,C_fix(256));}}

/* k8529 in a8491 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8531(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8531,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[4],t1);
t3=C_mutate(((C_word *)((C_word*)t0)[3])+1,t2);
t4=((C_word*)t0)[2];
f_8505(t4,t3);}

/* k8503 in a8491 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_8505(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_8505,NULL,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,3,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3153(((C_word*)t0)[2],C_fix(37632),t2,C_SCHEME_FALSE);}

/* k8484 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8486(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(37632),t1);}

/* k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5798(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5798,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5801,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8029,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(30208),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,C_fix(256),t4);
t6=(C_word)C_a_i_cons(&a,2,lf[80],t5);
t7=(C_word)C_a_i_cons(&a,2,t6,C_SCHEME_END_OF_LIST);
t8=(C_word)C_a_i_cons(&a,2,C_fix(30208),t7);
t9=(C_word)C_a_i_cons(&a,2,C_fix(24576),t8);
t10=(C_word)C_a_i_cons(&a,2,lf[103],t9);
t11=(C_word)C_a_i_cons(&a,2,C_fix(37632),C_SCHEME_END_OF_LIST);
t12=(C_word)C_a_i_cons(&a,2,C_fix(24064),t11);
t13=(C_word)C_a_i_cons(&a,2,lf[103],t12);
t14=(C_word)C_a_i_cons(&a,2,C_fix(37632),C_SCHEME_END_OF_LIST);
t15=(C_word)C_a_i_cons(&a,2,C_fix(24320),t14);
t16=(C_word)C_a_i_cons(&a,2,lf[103],t15);
t17=(C_word)C_a_i_cons(&a,2,t16,C_SCHEME_END_OF_LIST);
t18=(C_word)C_a_i_cons(&a,2,t13,t17);
t19=(C_word)C_a_i_cons(&a,2,t10,t18);
t20=(C_word)C_a_i_cons(&a,2,lf[104],t19);
t21=(C_word)C_a_i_cons(&a,2,t20,C_SCHEME_END_OF_LIST);
t22=(C_word)C_a_i_cons(&a,2,C_fix(13824),t21);
t23=(C_word)C_a_i_cons(&a,2,lf[103],t22);
t24=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8035,a[2]=((C_word)li192),tmp=(C_word)a,a+=3,tmp);
t25=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8074,a[2]=((C_word)li195),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t3,lf[325],C_fix(36352),t23,t24,t25);}

/* a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8074(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[7],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_8074,5,t0,t1,t2,t3,t4);}
t5=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_8078,a[2]=t4,a[3]=t5,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3192(t6,t2);}

/* k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8078(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_8078,2,t0,t1);}
t2=(C_word)C_i_car(t1);
t3=(C_word)C_a_i_list(&a,1,lf[136]);
t4=t3;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8087,a[2]=t3,a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
t7=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_8090,a[2]=t2,a[3]=t3,a[4]=t6,a[5]=((C_word*)t0)[2],a[6]=((C_word*)t0)[3],a[7]=t5,a[8]=t1,tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3238(t7,t2,C_fix(24576));}

/* k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8090(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_8090,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_cdr(((C_word*)t0)[8]);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_8099,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=t4,a[5]=((C_word*)t0)[7],a[6]=((C_word)li193),tmp=(C_word)a,a+=7,tmp));
t6=((C_word*)t4)[1];
f_8099(t6,((C_word*)t0)[4],t2);}
else{
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_8148,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],tmp=(C_word)a,a+=7,tmp);
t3=(C_word)C_i_cadr(((C_word*)t0)[8]);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3192(t2,t3);}}

/* k8146 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8148(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8148,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_8151,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,tmp=(C_word)a,a+=8,tmp);
t3=(C_word)C_i_car(t1);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t2,t3,((C_word*)((C_word*)t0)[4])[1],((C_word*)t0)[3]);}

/* k8149 in k8146 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8151(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8151,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_8154,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=t1,tmp=(C_word)a,a+=9,tmp);
t3=(C_word)C_i_cadr(((C_word*)t0)[7]);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t2,t3,((C_word*)((C_word*)t0)[4])[1],((C_word*)t0)[3]);}

/* k8152 in k8149 in k8146 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8154(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8154,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_8366,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 145  append");
t3=*((C_word*)lf[115]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t2,t1,C_SCHEME_END_OF_LIST);}

/* k8364 in k8152 in k8149 in k8146 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8366(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_8366,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[9],t1);
t3=(C_word)C_i_caddr(((C_word*)t0)[8]);
t4=C_SCHEME_FALSE;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_SCHEME_FALSE;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_8163,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t3,a[5]=t2,a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[9],a[8]=((C_word*)t0)[5],a[9]=((C_word*)t0)[6],a[10]=((C_word*)t0)[7],a[11]=t7,a[12]=t5,tmp=(C_word)a,a+=13,tmp);
t9=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t9))){
t10=t8;
f_8163(t10,C_SCHEME_UNDEFINED);}
else{
t10=(C_word)C_i_length(t2);
t11=(C_word)C_a_i_minus(&a,2,t10,C_fix(2));
t12=(C_word)C_i_list_tail(t2,t11);
t13=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8304,a[2]=t12,a[3]=t8,tmp=(C_word)a,a+=4,tmp);
t14=(C_word)C_i_cadr(t12);
C_trace("ChickenBridge.scm: 145  symbol->string");
t15=*((C_word*)lf[243]+1);
((C_proc3)C_retrieve_proc(t15))(3,t15,t13,t14);}}

/* k8302 in k8364 in k8152 in k8149 in k8146 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8304(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[13],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8304,2,t0,t1);}
t2=(C_word)C_i_string_length(t1);
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_8313,a[2]=t1,a[3]=t2,a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_greaterp(t2,C_fix(3)))){
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8338,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
t5=(C_word)C_a_i_minus(&a,2,t2,C_fix(3));
C_trace("ChickenBridge.scm: 145  substring");
t6=*((C_word*)lf[159]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t4,t1,t5);}
else{
t4=t3;
f_8313(t4,C_SCHEME_FALSE);}}

/* k8336 in k8302 in k8364 in k8152 in k8149 in k8146 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8338(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_8313(t2,(C_word)C_i_string_equal_p(t1,lf[324]));}

/* k8311 in k8302 in k8364 in k8152 in k8149 in k8146 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_8313(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_8313,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8320,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_8324,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_minus(&a,2,((C_word*)t0)[3],C_fix(3));
C_trace("ChickenBridge.scm: 145  substring");
t5=*((C_word*)lf[159]+1);
((C_proc5)C_retrieve_proc(t5))(5,t5,t3,((C_word*)t0)[2],C_fix(0),t4);}
else{
t2=((C_word*)t0)[5];
f_8163(t2,C_SCHEME_UNDEFINED);}}

/* k8322 in k8311 in k8302 in k8364 in k8152 in k8149 in k8146 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8324(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  string->symbol");
t2=*((C_word*)lf[100]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k8318 in k8311 in k8302 in k8364 in k8152 in k8149 in k8146 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8320(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
f_8163(t2,(C_word)C_i_set_cdr(((C_word*)t0)[2],t1));}

/* k8161 in k8364 in k8152 in k8149 in k8146 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_8163(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[18],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_8163,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_8166,a[2]=((C_word*)t0)[7],a[3]=((C_word*)t0)[8],a[4]=((C_word*)t0)[9],a[5]=((C_word*)t0)[10],a[6]=((C_word*)t0)[11],a[7]=((C_word*)t0)[12],tmp=(C_word)a,a+=8,tmp);
t3=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_8241,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t2,a[6]=((C_word*)t0)[12],a[7]=((C_word*)t0)[5],a[8]=((C_word*)t0)[11],a[9]=((C_word*)t0)[6],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3238(t3,((C_word*)t0)[2],C_fix(24064));}

/* k8239 in k8161 in k8364 in k8152 in k8149 in k8146 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8241(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[18],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8241,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_8245,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],a[8]=((C_word*)t0)[9],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 145  add-emit-info");
f_3282(t2,lf[321],C_SCHEME_TRUE,((C_word*)((C_word*)t0)[9])[1]);}
else{
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_8282,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],a[8]=((C_word*)t0)[9],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3238(t2,((C_word*)t0)[2],C_fix(24320));}}

/* k8280 in k8239 in k8161 in k8364 in k8152 in k8149 in k8146 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8282(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8282,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_8286,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 145  add-emit-info");
f_3282(t2,lf[323],C_SCHEME_TRUE,((C_word*)((C_word*)t0)[8])[1]);}
else{
t2=((C_word*)t0)[4];
f_8166(t2,C_SCHEME_UNDEFINED);}}

/* k8284 in k8280 in k8239 in k8161 in k8364 in k8152 in k8149 in k8146 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8286(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8286,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_8290,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t3,((C_word*)t0)[3],((C_word*)((C_word*)t0)[8])[1],((C_word*)t0)[2]);}

/* k8288 in k8284 in k8280 in k8239 in k8161 in k8364 in k8152 in k8149 in k8146 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8290(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8290,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[5])+1,t1);
t3=(C_word)C_a_i_list(&a,3,lf[313],((C_word*)t0)[4],((C_word*)((C_word*)t0)[5])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[5])+1,t3);
t5=C_mutate(((C_word *)((C_word*)t0)[3])+1,lf[322]);
t6=((C_word*)t0)[2];
f_8166(t6,t5);}

/* k8243 in k8239 in k8161 in k8364 in k8152 in k8149 in k8146 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8245(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8245,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_8249,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t3,((C_word*)t0)[3],((C_word*)((C_word*)t0)[8])[1],((C_word*)t0)[2]);}

/* k8247 in k8243 in k8239 in k8161 in k8364 in k8152 in k8149 in k8146 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8249(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8249,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_8252,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8276,a[2]=t3,a[3]=((C_word*)t0)[6],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  get-emit-info");
f_3270(t4,lf[321],((C_word*)((C_word*)t0)[2])[1]);}

/* k8274 in k8247 in k8243 in k8239 in k8161 in k8364 in k8152 in k8149 in k8146 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8276(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_8276,2,t0,t1);}
t2=(C_word)C_eqp(lf[319],t1);
if(C_truep(t2)){
t3=(C_word)C_a_i_list(&a,1,lf[320]);
t4=(C_word)C_a_i_list(&a,3,lf[267],t3,((C_word*)((C_word*)t0)[3])[1]);
t5=(C_word)C_a_i_list(&a,2,lf[263],t4);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t5);
t7=((C_word*)t0)[2];
f_8252(t7,t6);}
else{
t3=((C_word*)t0)[2];
f_8252(t3,C_SCHEME_UNDEFINED);}}

/* k8250 in k8247 in k8243 in k8239 in k8161 in k8364 in k8152 in k8149 in k8146 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_8252(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_8252,NULL,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,3,lf[313],((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t4=C_mutate(((C_word *)((C_word*)t0)[3])+1,lf[318]);
t5=((C_word*)t0)[2];
f_8166(t5,t4);}

/* k8164 in k8161 in k8364 in k8152 in k8149 in k8146 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_8166(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[15],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_8166,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_8169,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],tmp=(C_word)a,a+=6,tmp);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_8180,a[2]=((C_word*)t0)[3],a[3]=t2,a[4]=((C_word*)t0)[7],tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8238,a[2]=((C_word*)t0)[7],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  symbol->string");
t5=*((C_word*)lf[243]+1);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,((C_word*)t0)[2]);}

/* k8236 in k8164 in k8161 in k8364 in k8152 in k8149 in k8146 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8238(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  string-append");
t2=*((C_word*)lf[156]+1);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1,lf[317]);}

/* k8178 in k8164 in k8161 in k8364 in k8152 in k8149 in k8146 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8180(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8180,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_8182,a[2]=t3,a[3]=((C_word*)t0)[4],a[4]=((C_word)li194),tmp=(C_word)a,a+=5,tmp));
t5=((C_word*)t3)[1];
f_8182(t5,((C_word*)t0)[3],t1,((C_word*)t0)[2]);}

/* do1189 in k8178 in k8164 in k8161 in k8364 in k8152 in k8149 in k8146 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_8182(C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)trf_8182,NULL,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8197,a[2]=t1,a[3]=((C_word*)t0)[3],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  string-append");
t6=*((C_word*)lf[156]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t5,((C_word*)t4)[1],lf[315]);}
else{
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_8201,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=t3,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8230,a[2]=t4,a[3]=t5,tmp=(C_word)a,a+=4,tmp);
t7=(C_word)C_i_car(t3);
C_trace("ChickenBridge.scm: 145  symbol->string");
t8=*((C_word*)lf[243]+1);
((C_proc3)C_retrieve_proc(t8))(3,t8,t6,t7);}}

/* k8228 in do1189 in k8178 in k8164 in k8161 in k8364 in k8152 in k8149 in k8146 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8230(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  string-append");
t2=*((C_word*)lf[156]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k8199 in do1189 in k8178 in k8164 in k8161 in k8364 in k8152 in k8149 in k8146 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8201(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8201,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[5])+1,t1);
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_8204,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t4=(C_word)C_i_cdr(((C_word*)t0)[4]);
if(C_truep((C_word)C_i_nullp(t4))){
t5=t3;
f_8204(t5,C_SCHEME_UNDEFINED);}
else{
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8218,a[2]=t3,a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  string-append");
t6=*((C_word*)lf[156]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t5,((C_word*)((C_word*)t0)[5])[1],lf[316]);}}

/* k8216 in k8199 in do1189 in k8178 in k8164 in k8161 in k8364 in k8152 in k8149 in k8146 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8218(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_8204(t3,t2);}

/* k8202 in k8199 in do1189 in k8178 in k8164 in k8161 in k8364 in k8152 in k8149 in k8146 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_8204(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[5]);
t3=((C_word*)((C_word*)t0)[4])[1];
f_8182(t3,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t2);}

/* k8195 in do1189 in k8178 in k8164 in k8161 in k8364 in k8152 in k8149 in k8146 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8197(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8197,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,2,lf[168],t1);
t3=C_mutate(((C_word *)((C_word*)t0)[3])+1,t2);
t4=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,t3);}

/* k8167 in k8164 in k8161 in k8364 in k8152 in k8149 in k8146 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8169(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8169,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,2,((C_word*)((C_word*)t0)[5])[1],((C_word*)((C_word*)t0)[4])[1]);
t3=((C_word*)t0)[3];
f_8087(2,t3,(C_word)C_i_set_cdr(((C_word*)t0)[2],t2));}

/* do1163 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_8099(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_8099,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_8109,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=t2,a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
t4=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t3,t4,((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]);}}

/* k8107 in do1163 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8109(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8109,2,t0,t1);}
t2=(C_word)C_i_car(t1);
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_8115,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=t2,a[7]=t1,tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 145  sprintf");
t4=C_retrieve(lf[174]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t3,lf[314],t2);}

/* k8113 in k8107 in do1163 in k8088 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8115(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_8115,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,lf[313],((C_word*)t0)[7]);
t3=(C_word)C_a_i_list(&a,3,lf[167],t1,((C_word*)t0)[6]);
t4=(C_word)C_a_i_list(&a,2,t2,t3);
t5=(C_word)C_i_set_cdr(((C_word*)((C_word*)t0)[5])[1],t4);
t6=(C_word)C_i_cddr(((C_word*)((C_word*)t0)[5])[1]);
t7=C_mutate(((C_word *)((C_word*)t0)[5])+1,t6);
t8=(C_word)C_i_cdr(((C_word*)t0)[4]);
t9=((C_word*)((C_word*)t0)[3])[1];
f_8099(t9,((C_word*)t0)[2],t8);}

/* k8085 in k8076 in a8073 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8087(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,((C_word*)t0)[2]);}

/* a8034 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8035(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_8035,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=(C_word)C_i_cadr(((C_word*)t4)[1]);
t6=C_set_block_item(t4,0,t5);
t7=(C_word)C_i_car(((C_word*)t4)[1]);
t8=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_8046,a[2]=t4,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
t9=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_8052,a[2]=t8,a[3]=t7,a[4]=t4,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3238(t9,t7,C_fix(24576));}

/* k8050 in a8034 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8052(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8052,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_cadr(((C_word*)((C_word*)t0)[4])[1]);
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_8068,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[3],a[5]=t2,tmp=(C_word)a,a+=6,tmp);
t4=(C_word)C_i_caddr(((C_word*)((C_word*)t0)[4])[1]);
C_trace("ChickenBridge.scm: 145  remove-token-type");
f_4488(t3,t4,C_fix(256));}
else{
t2=((C_word*)t0)[2];
f_8046(t2,C_SCHEME_UNDEFINED);}}

/* k8066 in k8050 in a8034 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8068(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_8068,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[5],t1);
t3=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[4],t2);
t4=C_mutate(((C_word *)((C_word*)t0)[3])+1,t3);
t5=((C_word*)t0)[2];
f_8046(t5,t4);}

/* k8044 in a8034 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_8046(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3153(((C_word*)t0)[3],C_fix(36352),((C_word*)((C_word*)t0)[2])[1],C_SCHEME_FALSE);}

/* k8027 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_8029(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(36352),t1);}

/* k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5801(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5801,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5804,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7953,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
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
t20=(C_word)C_a_i_cons(&a,2,lf[104],t19);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t3,lf[312],C_fix(36608),t20,C_SCHEME_FALSE,C_SCHEME_FALSE);}

/* k7951 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7953(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(36608),t1);}

/* k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5804(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5804,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5807,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7909,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(C_word)C_a_i_cons(&a,2,C_fix(36608),C_SCHEME_END_OF_LIST);
t5=(C_word)C_a_i_cons(&a,2,lf[122],t4);
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7915,a[2]=((C_word)li190),tmp=(C_word)a,a+=3,tmp);
t7=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7929,a[2]=((C_word)li191),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  make-rule");
f_2855(t3,lf[311],C_fix(36864),t5,t6,t7);}

/* a7928 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7929(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[8],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_7929,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7937,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7941,a[2]=t4,a[3]=t3,a[4]=t5,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3192(t6,t2);}

/* k7939 in a7928 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7941(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  emit");
f_3310(((C_word*)t0)[4],t1,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k7935 in a7928 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7937(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7937,2,t0,t1);}
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_cons(&a,2,lf[136],t1));}

/* a7914 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7915(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word ab[4],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_7915,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7923,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  parse-unit-position");
f_3210(t4,t5);}

/* k7921 in a7914 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7923(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3153(((C_word*)t0)[3],C_fix(36864),((C_word*)t0)[2],t1);}

/* k7907 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7909(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  hash-table-set!");
t2=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[2],C_retrieve2(lf[68],"*rules*"),C_fix(36864),t1);}

/* k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5807(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5807,2,t0,t1);}
t2=lf[151]=C_SCHEME_FALSE;;
t3=lf[152]=C_SCHEME_FALSE;;
t4=lf[153]=C_SCHEME_FALSE;;
t5=C_mutate((C_word*)lf[154]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5813,a[2]=((C_word)li110),tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[167]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5984,a[2]=((C_word)li114),tmp=(C_word)a,a+=3,tmp));
t7=C_mutate((C_word*)lf[178]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6163,a[2]=((C_word)li115),tmp=(C_word)a,a+=3,tmp));
t8=C_mutate((C_word*)lf[180]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6172,a[2]=((C_word)li116),tmp=(C_word)a,a+=3,tmp));
t9=C_mutate((C_word*)lf[188]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6219,a[2]=((C_word)li117),tmp=(C_word)a,a+=3,tmp));
t10=C_mutate((C_word*)lf[190]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6225,a[2]=((C_word)li118),tmp=(C_word)a,a+=3,tmp));
t11=C_mutate((C_word*)lf[192]+1,*((C_word*)lf[142]+1));
t12=C_mutate((C_word*)lf[193]+1,*((C_word*)lf[194]+1));
t13=C_mutate((C_word*)lf[195]+1,*((C_word*)lf[196]+1));
t14=C_mutate((C_word*)lf[197]+1,*((C_word*)lf[198]+1));
t15=C_mutate((C_word*)lf[139]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6247,a[2]=((C_word)li119),tmp=(C_word)a,a+=3,tmp));
t16=C_mutate((C_word*)lf[199]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6257,a[2]=((C_word)li120),tmp=(C_word)a,a+=3,tmp));
t17=C_mutate((C_word*)lf[200]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6267,a[2]=((C_word)li121),tmp=(C_word)a,a+=3,tmp));
t18=C_mutate((C_word*)lf[201]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6277,a[2]=((C_word)li122),tmp=(C_word)a,a+=3,tmp));
t19=C_mutate((C_word*)lf[202]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6287,a[2]=((C_word)li123),tmp=(C_word)a,a+=3,tmp));
t20=C_mutate((C_word*)lf[203]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6301,a[2]=((C_word)li124),tmp=(C_word)a,a+=3,tmp));
t21=C_mutate((C_word*)lf[204]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6321,a[2]=((C_word)li125),tmp=(C_word)a,a+=3,tmp));
t22=C_mutate((C_word*)lf[205]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6341,a[2]=((C_word)li126),tmp=(C_word)a,a+=3,tmp));
t23=C_mutate((C_word*)lf[206]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6389,a[2]=((C_word)li127),tmp=(C_word)a,a+=3,tmp));
t24=C_mutate((C_word*)lf[208]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6429,a[2]=((C_word)li129),tmp=(C_word)a,a+=3,tmp));
t25=C_mutate((C_word*)lf[179]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6440,a[2]=((C_word)li131),tmp=(C_word)a,a+=3,tmp));
t26=C_mutate((C_word*)lf[168]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6469,a[2]=((C_word)li132),tmp=(C_word)a,a+=3,tmp));
t27=C_mutate((C_word*)lf[155]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6483,a[2]=((C_word)li133),tmp=(C_word)a,a+=3,tmp));
t28=C_mutate((C_word*)lf[212]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6526,a[2]=((C_word)li134),tmp=(C_word)a,a+=3,tmp));
t29=C_mutate((C_word*)lf[213]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6529,a[2]=((C_word)li135),tmp=(C_word)a,a+=3,tmp));
t30=C_mutate(&lf[214],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6541,a[2]=((C_word)li137),tmp=(C_word)a,a+=3,tmp));
t31=C_mutate(&lf[216],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6550,a[2]=((C_word)li139),tmp=(C_word)a,a+=3,tmp));
t32=C_mutate(&lf[217],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6594,a[2]=((C_word)li141),tmp=(C_word)a,a+=3,tmp));
t33=C_mutate((C_word*)lf[181]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6616,a[2]=((C_word)li143),tmp=(C_word)a,a+=3,tmp));
t34=C_mutate((C_word*)lf[218]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6635,a[2]=((C_word)li150),tmp=(C_word)a,a+=3,tmp));
t35=C_mutate((C_word*)lf[219]+1,C_retrieve(lf[213]));
t36=C_mutate((C_word*)lf[220]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6803,a[2]=((C_word)li152),tmp=(C_word)a,a+=3,tmp));
t37=C_mutate((C_word*)lf[226]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6866,a[2]=((C_word)li154),tmp=(C_word)a,a+=3,tmp));
t38=C_mutate((C_word*)lf[227]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6875,a[2]=((C_word)li156),tmp=(C_word)a,a+=3,tmp));
t39=C_mutate((C_word*)lf[228]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6881,a[2]=((C_word)li158),tmp=(C_word)a,a+=3,tmp));
t40=C_mutate((C_word*)lf[229]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6890,a[2]=((C_word)li160),tmp=(C_word)a,a+=3,tmp));
t41=C_mutate((C_word*)lf[231]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6948,a[2]=((C_word)li162),tmp=(C_word)a,a+=3,tmp));
t42=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6959,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 369  make-hash-table");
t43=C_retrieve(lf[309]);
((C_proc3)C_retrieve_proc(t43))(3,t43,t42,*((C_word*)lf[310]+1));}

/* k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6959(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6959,2,t0,t1);}
t2=C_mutate(&lf[232],t1);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6962,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7855,a[2]=((C_word)li189),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 371  ##sys#register-macro");
t5=C_retrieve(lf[286]);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,lf[308],t4);}

/* a7854 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7855(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_7855,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_7859,a[2]=t6,a[3]=t1,a[4]=t3,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t4)[1]))){
t8=(C_word)C_i_car(((C_word*)t4)[1]);
t9=C_set_block_item(t6,0,t8);
t10=(C_word)C_i_cadr(((C_word*)t4)[1]);
t11=C_set_block_item(t4,0,t10);
t12=t7;
f_7859(2,t12,t11);}
else{
if(C_truep((C_word)C_i_stringp(((C_word*)t4)[1]))){
t8=C_set_block_item(t6,0,((C_word*)t4)[1]);
t9=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7892,a[2]=t7,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 378  string->symbol");
t10=*((C_word*)lf[100]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)t4)[1]);}
else{
if(C_truep((C_word)C_i_symbolp(((C_word*)t4)[1]))){
t8=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7902,a[2]=t7,a[3]=t6,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 380  symbol->string");
t9=*((C_word*)lf[243]+1);
((C_proc3)C_retrieve_proc(t9))(3,t9,t8,((C_word*)t4)[1]);}
else{
C_trace("ChickenBridge.scm: 382  error");
t8=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,lf[307]);}}}}

/* k7900 in a7854 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7902(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_7859(2,t3,t2);}

/* k7890 in a7854 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7892(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_7859(2,t3,t2);}

/* k7857 in a7854 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7859(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7859,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[4]);
t3=(C_word)C_a_i_list(&a,2,lf[272],t2);
t4=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_a_i_list(&a,4,lf[288],lf[306],((C_word*)((C_word*)t0)[2])[1],t3));}

/* k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6962(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6962,2,t0,t1);}
t2=C_mutate((C_word*)lf[233]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6964,a[2]=((C_word)li170),tmp=(C_word)a,a+=3,tmp));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7235,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7849,a[2]=((C_word)li188),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 466  ##sys#register-macro");
t5=C_retrieve(lf[286]);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,lf[305],t4);}

/* a7848 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7849(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr3r,(void*)f_7849r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_7849r(t0,t1,t2,t3);}}

static void C_ccall f_7849r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_trace("ChickenBridge.scm: 467  expand-send");
t4=C_retrieve(lf[233]);
((C_proc5)C_retrieve_proc(t4))(5,t4,t1,t2,t3,C_SCHEME_FALSE);}

/* k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7235(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_7235,2,t0,t1);}
t2=C_mutate((C_word*)lf[244]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7237,a[2]=((C_word)li172),tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[245]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7243,a[2]=((C_word)li173),tmp=(C_word)a,a+=3,tmp));
t4=C_mutate((C_word*)lf[247]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7249,a[2]=((C_word)li174),tmp=(C_word)a,a+=3,tmp));
t5=C_mutate((C_word*)lf[249]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7255,a[2]=((C_word)li175),tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[251]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7261,a[2]=((C_word)li176),tmp=(C_word)a,a+=3,tmp));
t7=C_mutate((C_word*)lf[253]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7267,a[2]=((C_word)li177),tmp=(C_word)a,a+=3,tmp));
t8=C_mutate((C_word*)lf[255]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7273,a[2]=((C_word)li178),tmp=(C_word)a,a+=3,tmp));
t9=C_mutate((C_word*)lf[257]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7279,a[2]=((C_word)li184),tmp=(C_word)a,a+=3,tmp));
t10=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7358,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 522  hash-table-set!");
t11=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t11))(5,t11,t10,C_retrieve2(lf[232],"*messages*"),lf[303],lf[304]);}

/* k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7358(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7358,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7361,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 523  hash-table-set!");
t3=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,C_retrieve2(lf[232],"*messages*"),lf[301],lf[302]);}

/* k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7361(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7361,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7364,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 524  hash-table-set!");
t3=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,C_retrieve2(lf[232],"*messages*"),lf[299],lf[300]);}

/* k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7364(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7364,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7367,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 525  hash-table-set!");
t3=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,C_retrieve2(lf[232],"*messages*"),lf[297],lf[298]);}

/* k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7367(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7367,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7370,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 526  hash-table-set!");
t3=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,C_retrieve2(lf[232],"*messages*"),lf[295],lf[296]);}

/* k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7370(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7370,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7373,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 527  hash-table-set!");
t3=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,C_retrieve2(lf[232],"*messages*"),lf[293],lf[294]);}

/* k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7373(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7373,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7376,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 528  hash-table-set!");
t3=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,C_retrieve2(lf[232],"*messages*"),lf[291],lf[292]);}

/* k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7376(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7376,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7379,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 529  hash-table-set!");
t3=C_retrieve(lf[288]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,C_retrieve2(lf[232],"*messages*"),lf[289],lf[290]);}

/* k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7379(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7379,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7382,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7843,a[2]=((C_word)li187),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 535  ##sys#register-macro");
t4=C_retrieve(lf[286]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,lf[287],t3);}

/* a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7843(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+17)){
C_save_and_reclaim((void*)tr4r,(void*)f_7843r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest(a,C_rest_count(0));
f_7843r(t0,t1,t2,t3,t4);}}

static void C_ccall f_7843r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
t13=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_7397,a[2]=t2,a[3]=t12,a[4]=t6,a[5]=t10,a[6]=t1,a[7]=t8,a[8]=t3,tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(t2))){
t14=t13;
f_7397(2,t14,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 544  error");
t14=*((C_word*)lf[27]+1);
((C_proc4)C_retrieve_proc(t14))(4,t14,t13,lf[285],t2);}}

/* k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7397(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7397,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_7400,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(((C_word*)t0)[8]))){
if(C_truep((C_word)C_i_nullp(((C_word*)t0)[8]))){
C_trace("ChickenBridge.scm: 548  error");
t3=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,lf[283]);}
else{
t3=t2;
f_7400(2,t3,C_SCHEME_UNDEFINED);}}
else{
C_trace("ChickenBridge.scm: 546  error");
t3=*((C_word*)lf[27]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t2,lf[284],((C_word*)t0)[8]);}}

/* k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7400(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7400,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_7403,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],tmp=(C_word)a,a+=8,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_7678,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[7],a[5]=t4,a[6]=((C_word)li186),tmp=(C_word)a,a+=7,tmp));
t6=((C_word*)t4)[1];
f_7678(t6,t2,((C_word*)t0)[2]);}

/* do1648 in k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_7678(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_7678,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7688,a[2]=t1,a[3]=((C_word*)t0)[5],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_7698,a[2]=t3,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=t2,tmp=(C_word)a,a+=7,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7786,a[2]=t4,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t7=(C_word)C_i_car(t2);
t8=(C_word)C_i_length(t7);
C_trace("ChickenBridge.scm: 552  <");
C_lessp(5,0,t6,C_fix(0),t8,C_fix(4));}
else{
t6=t4;
f_7698(t6,C_SCHEME_FALSE);}}}

/* k7784 in do1648 in k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7786(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=(C_word)C_i_car(t2);
t4=((C_word*)t0)[2];
f_7698(t4,(C_word)C_i_symbolp(t3));}
else{
t2=((C_word*)t0)[2];
f_7698(t2,C_SCHEME_FALSE);}}

/* k7696 in do1648 in k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_7698(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_7698,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[6]);
t3=(C_word)C_i_car(t2);
t4=(C_word)C_i_car(((C_word*)t0)[6]);
t5=(C_word)C_i_cadr(t4);
t6=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_7707,a[2]=t5,a[3]=t3,a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[5],tmp=(C_word)a,a+=8,tmp);
t7=(C_word)C_i_car(((C_word*)t0)[6]);
t8=(C_word)C_i_cddr(t7);
if(C_truep((C_word)C_i_nullp(t8))){
t9=t6;
f_7707(t9,lf[281]);}
else{
t9=(C_word)C_i_car(((C_word*)t0)[6]);
t10=t6;
f_7707(t10,(C_word)C_i_caddr(t9));}}
else{
t2=(C_word)C_i_car(((C_word*)t0)[6]);
C_trace("ChickenBridge.scm: 565  error");
t3=*((C_word*)lf[27]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[2],lf[282],t2);}}

/* k7705 in k7696 in do1648 in k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_7707(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_7707,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_7711,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t3=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 560  append");
t4=*((C_word*)lf[115]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,((C_word*)((C_word*)t0)[7])[1],t3);}

/* k7709 in k7705 in k7696 in do1648 in k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7711(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7711,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_7715,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
t4=(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 561  append");
t5=*((C_word*)lf[115]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,((C_word*)((C_word*)t0)[7])[1],t4);}

/* k7713 in k7709 in k7705 in k7696 in do1648 in k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7715(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_7715,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7719,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7723,a[2]=((C_word*)t0)[5],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_eqp(((C_word*)t0)[3],lf[281]);
if(C_truep(t5)){
t6=t4;
f_7723(t6,C_SCHEME_END_OF_LIST);}
else{
t6=(C_word)C_a_i_list(&a,3,lf[131],((C_word*)t0)[2],((C_word*)t0)[3]);
t7=t4;
f_7723(t7,(C_word)C_a_i_list(&a,1,t6));}}

/* k7721 in k7713 in k7709 in k7705 in k7696 in do1648 in k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_7723(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 562  append");
t2=*((C_word*)lf[115]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k7717 in k7713 in k7709 in k7705 in k7696 in do1648 in k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7719(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_7688(2,t3,t2);}

/* k7686 in do1648 in k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7688(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_7678(t3,((C_word*)t0)[2],t2);}

/* k7401 in k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7403(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7403,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_7406,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 567  gensym");
t3=C_retrieve(lf[133]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k7404 in k7401 in k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7406(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7406,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_7409,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 568  gensym");
t3=C_retrieve(lf[133]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k7407 in k7404 in k7401 in k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7409(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7409,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_7412,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 569  gensym");
t3=C_retrieve(lf[133]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k7410 in k7407 in k7404 in k7401 in k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7412(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7412,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_7415,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],a[10]=((C_word*)t0)[9],tmp=(C_word)a,a+=11,tmp);
C_trace("ChickenBridge.scm: 570  gensym");
t3=C_retrieve(lf[133]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k7413 in k7410 in k7407 in k7404 in k7401 in k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7415(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_7415,2,t0,t1);}
t2=C_SCHEME_TRUE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_SCHEME_END_OF_LIST;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_7418,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=t3,a[7]=((C_word*)t0)[5],a[8]=((C_word*)t0)[6],a[9]=((C_word*)t0)[7],a[10]=((C_word*)t0)[8],a[11]=((C_word*)t0)[9],a[12]=t5,a[13]=((C_word*)t0)[10],tmp=(C_word)a,a+=14,tmp);
t7=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7571,a[2]=t6,a[3]=t3,a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)((C_word*)t0)[3])[1]))){
t8=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
if(C_truep((C_word)C_i_pairp(t8))){
t9=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7672,a[2]=t7,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 576  caar");
t10=*((C_word*)lf[278]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)((C_word*)t0)[3])[1]);}
else{
t9=t7;
f_7571(t9,C_SCHEME_FALSE);}}
else{
t8=t7;
f_7571(t8,C_SCHEME_FALSE);}}

/* k7670 in k7413 in k7410 in k7407 in k7404 in k7401 in k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7672(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_7571(t2,(C_word)C_eqp(t1,lf[280]));}

/* k7569 in k7413 in k7410 in k7407 in k7404 in k7401 in k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_7571(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_7571,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7578,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 577  cdar");
t3=*((C_word*)lf[276]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)((C_word*)t0)[4])[1]);}
else{
t2=((C_word*)t0)[2];
f_7418(2,t2,C_SCHEME_UNDEFINED);}}

/* k7576 in k7569 in k7413 in k7410 in k7407 in k7404 in k7401 in k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7578(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7578,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_7580,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=((C_word)li185),tmp=(C_word)a,a+=6,tmp));
t5=((C_word*)t3)[1];
f_7580(t5,((C_word*)t0)[2],t1);}

/* do1664 in k7576 in k7569 in k7413 in k7410 in k7407 in k7404 in k7401 in k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_7580(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_7580,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[4])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[4])+1,t3);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,t4);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7594,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7604,a[2]=t2,a[3]=((C_word*)t0)[2],a[4]=t3,tmp=(C_word)a,a+=5,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7652,a[2]=t4,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 581  cdar");
t7=*((C_word*)lf[276]+1);
((C_proc3)C_retrieve_proc(t7))(3,t7,t6,t2);}
else{
t6=t4;
f_7604(t6,C_SCHEME_FALSE);}}}

/* k7650 in do1664 in k7576 in k7569 in k7413 in k7410 in k7407 in k7404 in k7401 in k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7652(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_7604(t2,(C_word)C_i_pairp(t1));}

/* k7602 in do1664 in k7576 in k7569 in k7413 in k7410 in k7407 in k7404 in k7401 in k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_7604(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_7604,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7607,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 582  caar");
t3=*((C_word*)lf[278]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)t0)[2]);}
else{
t2=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 588  error");
t3=*((C_word*)lf[27]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[4],lf[279],t2);}}

/* k7605 in k7602 in do1664 in k7576 in k7569 in k7413 in k7410 in k7407 in k7404 in k7401 in k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7607(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7607,2,t0,t1);}
t2=(C_word)C_eqp(t1,lf[275]);
if(C_truep(t2)){
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7628,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 584  cdar");
t4=*((C_word*)lf[276]+1);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)t0)[2]);}
else{
t3=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 587  error");
t4=*((C_word*)lf[27]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,((C_word*)t0)[4],lf[277],t3);}}

/* k7626 in k7605 in k7602 in do1664 in k7576 in k7569 in k7413 in k7410 in k7407 in k7404 in k7401 in k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7628(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep((C_word)C_i_car(t1))){
t2=((C_word*)t0)[3];
f_7594(2,t2,C_SCHEME_UNDEFINED);}
else{
t2=C_set_block_item(((C_word*)t0)[2],0,C_SCHEME_FALSE);
t3=((C_word*)t0)[3];
f_7594(2,t3,t2);}}

/* k7592 in do1664 in k7576 in k7569 in k7413 in k7410 in k7407 in k7404 in k7401 in k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7594(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_7580(t3,((C_word*)t0)[2],t2);}

/* k7416 in k7413 in k7410 in k7407 in k7404 in k7401 in k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7418(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7418,2,t0,t1);}
t2=(C_word)C_i_car(((C_word*)t0)[13]);
t3=(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_7560,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],a[10]=((C_word*)t0)[10],a[11]=((C_word*)t0)[11],a[12]=((C_word*)t0)[12],a[13]=t2,tmp=(C_word)a,a+=14,tmp);
t4=(C_word)C_i_cdr(((C_word*)t0)[13]);
t5=(C_word)C_a_i_list(&a,1,C_fix(-1));
C_trace("ChickenBridge.scm: 539  ##sys#append");
t6=*((C_word*)lf[274]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t3,t4,t5);}

/* k7558 in k7416 in k7413 in k7410 in k7407 in k7404 in k7401 in k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7560(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7560,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[13],t1);
t3=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_7544,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],a[8]=((C_word*)t0)[10],a[9]=((C_word*)t0)[11],a[10]=((C_word*)t0)[12],a[11]=t2,tmp=(C_word)a,a+=12,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7548,a[2]=((C_word*)t0)[3],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_a_i_list(&a,1,((C_word*)t0)[10]);
C_trace("ChickenBridge.scm: 539  ##sys#append");
t6=*((C_word*)lf[274]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t4,((C_word*)((C_word*)t0)[2])[1],t5);}

/* k7546 in k7558 in k7416 in k7413 in k7410 in k7407 in k7404 in k7401 in k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7548(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 539  ##sys#append");
t2=*((C_word*)lf[274]+1);
((C_proc4)(void*)(*((C_word*)t2+1)))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k7542 in k7558 in k7416 in k7413 in k7410 in k7407 in k7404 in k7401 in k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7544(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_7544,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,lf[265],t1);
t3=(C_word)C_a_i_list(&a,3,lf[266],((C_word*)t0)[11],t2);
t4=C_mutate(((C_word *)((C_word*)t0)[10])+1,t3);
t5=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_7425,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],a[5]=((C_word*)t0)[10],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],tmp=(C_word)a,a+=8,tmp);
if(C_truep(((C_word*)((C_word*)t0)[4])[1])){
t6=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
t7=(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]);
t8=(C_word)C_a_i_list(&a,2,lf[272],lf[260]);
t9=(C_word)C_a_i_list(&a,2,lf[272],lf[261]);
t10=(C_word)C_a_i_list(&a,3,lf[259],t8,t9);
t11=(C_word)C_a_i_list(&a,2,t10,((C_word*)t0)[2]);
t12=(C_word)C_a_i_list(&a,4,lf[174],lf[273],t11,((C_word*)t0)[9]);
t13=(C_word)C_a_i_list(&a,2,lf[155],t12);
t14=(C_word)C_a_i_list(&a,2,((C_word*)t0)[3],C_fix(-2));
t15=(C_word)C_a_i_list(&a,4,lf[267],t7,t13,t14);
t16=(C_word)C_a_i_list(&a,3,lf[267],C_SCHEME_END_OF_LIST,((C_word*)((C_word*)t0)[10])[1]);
t17=(C_word)C_a_i_list(&a,3,lf[262],t15,t16);
t18=(C_word)C_a_i_list(&a,3,lf[267],t6,t17);
t19=(C_word)C_a_i_list(&a,2,lf[263],t18);
t20=C_mutate(((C_word *)((C_word*)t0)[10])+1,t19);
t21=t5;
f_7425(t21,t20);}
else{
t6=t5;
f_7425(t6,C_SCHEME_UNDEFINED);}}

/* k7423 in k7542 in k7558 in k7416 in k7413 in k7410 in k7407 in k7404 in k7401 in k7398 in k7395 in a7842 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_7425(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_7425,NULL,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,((C_word*)t0)[7]);
t3=(C_word)C_a_i_list(&a,2,((C_word*)t0)[6],C_fix(0));
t4=(C_word)C_a_i_list(&a,3,lf[267],C_SCHEME_END_OF_LIST,((C_word*)t0)[7]);
t5=(C_word)C_a_i_list(&a,2,lf[268],t4);
t6=(C_word)C_a_i_list(&a,1,lf[269]);
t7=(C_word)C_a_i_list(&a,3,lf[131],((C_word*)t0)[6],lf[269]);
t8=(C_word)C_a_i_list(&a,3,lf[267],t6,t7);
t9=(C_word)C_a_i_list(&a,2,lf[270],t8);
t10=(C_word)C_a_i_list(&a,3,t3,t5,t9);
t11=(C_word)C_a_i_list(&a,3,lf[271],t10,((C_word*)((C_word*)t0)[5])[1]);
t12=(C_word)C_a_i_list(&a,3,lf[267],t2,t11);
t13=(C_word)C_a_i_list(&a,3,lf[267],((C_word*)((C_word*)t0)[4])[1],t12);
t14=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t14+1)))(2,t14,(C_word)C_a_i_cons(&a,2,t13,((C_word*)((C_word*)t0)[2])[1]));}

/* k7380 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7382(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7382,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7841,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 636  return-to-host");
t3=C_retrieve(lf[264]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k7839 in k7380 in k7377 in k7374 in k7371 in k7368 in k7365 in k7362 in k7359 in k7356 in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7841(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_UNDEFINED);}

/* mp:inhook in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7279(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+10)){
C_save_and_reclaim((void*)tr3r,(void*)f_7279r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_7279r(t0,t1,t2,t3);}}

static void C_ccall f_7279r(C_word t0,C_word t1,C_word t2,C_word t3){
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
C_word *a=C_alloc(10);
t4=C_fix(0);
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_fix(0);
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_7283,a[2]=t7,a[3]=t5,a[4]=t1,a[5]=t2,tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_pairp(t3))){
t9=(C_word)C_i_car(t3);
t10=C_set_block_item(t5,0,t9);
t11=(C_word)C_i_cdr(t3);
if(C_truep((C_word)C_i_pairp(t11))){
t12=(C_word)C_i_cadr(t3);
t13=C_set_block_item(t7,0,t12);
t14=t8;
f_7283(t14,t13);}
else{
t12=t8;
f_7283(t12,C_SCHEME_UNDEFINED);}}
else{
t9=t8;
f_7283(t9,C_SCHEME_UNDEFINED);}}

/* k7281 in mp:inhook in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_7283(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_7283,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7288,a[2]=((C_word*)t0)[5],a[3]=((C_word)li182),tmp=(C_word)a,a+=4,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7325,a[2]=((C_word)li183),tmp=(C_word)a,a+=3,tmp);
((C_proc5)(void*)(*((C_word*)t3+1)))(5,t3,((C_word*)t0)[4],t2,((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* f_7325 in k7281 in mp:inhook in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7325(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_7325,5,t0,t1,t2,t3,t4);}
t5=(C_word)C_i_foreign_fixnum_argumentp(t3);
t6=(C_word)C_i_foreign_fixnum_argumentp(t4);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub1628(C_SCHEME_UNDEFINED,t2,t5,t6));}

/* a7287 in k7281 in mp:inhook in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7288(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[5],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_7288,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7294,a[2]=t2,a[3]=((C_word*)t0)[2],a[4]=((C_word)li181),tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 502  call-with-current-continuation");
t4=*((C_word*)lf[263]+1);
((C_proc3)C_retrieve_proc(t4))(3,t4,t1,t3);}

/* a7293 in a7287 in k7281 in mp:inhook in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7294(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_7294,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7300,a[2]=t2,a[3]=((C_word)li179),tmp=(C_word)a,a+=4,tmp);
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7320,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word)li180),tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 504  with-exception-handler");
t5=C_retrieve(lf[262]);
((C_proc4)C_retrieve_proc(t5))(4,t5,t1,t3,t4);}

/* a7319 in a7293 in a7287 in k7281 in mp:inhook in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7320(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7320,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7324,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 513  %hook");
t3=((C_word*)t0)[3];
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)t0)[2]);}

/* k7322 in a7319 in a7293 in a7287 in k7281 in mp:inhook in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7324(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_fix(0));}

/* a7299 in a7293 in a7287 in k7281 in mp:inhook in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7300(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[14],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_7300,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7304,a[2]=t1,a[3]=((C_word*)t0)[2],tmp=(C_word)a,a+=4,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7311,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7315,a[2]=t4,tmp=(C_word)a,a+=3,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7318,a[2]=t2,a[3]=t5,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 508  condition-property-accessor");
t7=C_retrieve(lf[259]);
((C_proc4)C_retrieve_proc(t7))(4,t7,t6,lf[260],lf[261]);}

/* k7316 in a7299 in a7293 in a7287 in k7281 in mp:inhook in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7318(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=t1;
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k7313 in a7299 in a7293 in a7287 in k7281 in mp:inhook in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7315(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 507  sprintf");
t2=C_retrieve(lf[174]);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[2],lf[258],t1);}

/* k7309 in a7299 in a7293 in a7287 in k7281 in mp:inhook in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7311(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 506  print-error");
t2=C_retrieve(lf[155]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k7302 in a7299 in a7293 in a7287 in k7281 in mp:inhook in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7304(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 510  %cont");
t2=((C_word*)t0)[3];
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],C_fix(-1));}

/* mp:micro in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7273(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_7273,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 487  error");
t3=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[256]);}

/* mp:alloff in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7267(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7267,2,t0,t1);}
C_trace("ChickenBridge.scm: 485  error");
t2=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,t1,lf[254]);}

/* mp:ctrl in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7261(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_7261,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 483  error");
t6=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[252]);}

/* mp:prog in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7255(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_7255,5,t0,t1,t2,t3,t4);}
C_trace("ChickenBridge.scm: 481  error");
t5=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t5))(3,t5,t1,lf[250]);}

/* mp:off in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7249(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_7249,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 479  error");
t6=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[248]);}

/* mp:on in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7243(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_7243,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 477  error");
t6=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[246]);}

/* mp:note in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7237(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
C_word tmp;
C_word t7;
C_word t8;
C_word ab[8],*a=ab;
if(c!=7) C_bad_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr7,(void*)f_7237,7,t0,t1,t2,t3,t4,t5,t6);}
t7=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_6501,a[2]=t1,a[3]=t6,a[4]=t5,a[5]=t4,a[6]=t3,a[7]=t2,tmp=(C_word)a,a+=8,tmp);
C_trace("##sys#gc");
t8=C_retrieve(lf[215]);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,C_SCHEME_FALSE);}

/* k6499 in mp:note in k7233 in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6501(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_6501,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[7]);
t4=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[6]);
t5=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[5]);
t6=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[4]);
t7=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[3]);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub1429,a[2]=((C_word)li171),tmp=(C_word)a,a+=3,tmp);
((C_proc8)C_retrieve_proc(t8))(8,t8,((C_word*)t0)[2],t2,t3,t4,t5,t6,t7);}

/* expand-send in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6964(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
C_save_and_reclaim((void*)tr5,(void*)f_6964,5,t0,t1,t2,t3,t4);}
t5=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t6=t4;
t7=(C_truep(t6)?t6:(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7224,a[2]=((C_word)li163),tmp=(C_word)a,a+=3,tmp));
t8=t4;
t9=(C_truep(t8)?(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7213,a[2]=((C_word)li164),tmp=(C_word)a,a+=3,tmp):(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7222,a[2]=((C_word)li165),tmp=(C_word)a,a+=3,tmp));
t10=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_6974,a[2]=t9,a[3]=t7,a[4]=t1,a[5]=t5,tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_symbolp(t2))){
C_trace("ChickenBridge.scm: 397  symbol->string");
t11=*((C_word*)lf[243]+1);
((C_proc3)C_retrieve_proc(t11))(3,t11,t10,t2);}
else{
t11=t10;
f_6974(2,t11,t2);}}

/* k6972 in expand-send in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6974(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6974,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_6977,a[2]=((C_word*)t0)[2],a[3]=t1,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],tmp=(C_word)a,a+=7,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7205,a[2]=((C_word)li169),tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 398  hash-table-ref");
t4=*((C_word*)lf[73]+1);
((C_proc5)C_retrieve_proc(t4))(5,t4,t2,C_retrieve2(lf[232],"*messages*"),t1,t3);}

/* a7204 in k6972 in expand-send in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7205(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7205,2,t0,t1);}
t2=t1;
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}

/* k6975 in k6972 in expand-send in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6977(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6977,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_6980,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=t1,a[7]=((C_word*)t0)[6],tmp=(C_word)a,a+=8,tmp);
t3=t1;
if(C_truep(t3)){
t4=t2;
f_6980(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 399  ferror");
t4=((C_word*)t0)[4];
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,lf[242],((C_word*)t0)[3]);}}

/* k6978 in k6975 in k6972 in expand-send in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6980(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_6980,2,t0,t1);}
t2=((C_word*)((C_word*)t0)[7])[1];
t3=(C_word)C_i_car(((C_word*)t0)[6]);
t4=(C_word)C_i_cdr(((C_word*)t0)[6]);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(C_word)C_i_length(t4);
t8=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_6992,a[2]=t2,a[3]=t7,a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],a[7]=t6,a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[5],a[10]=t4,a[11]=t3,tmp=(C_word)a,a+=12,tmp);
C_trace("ChickenBridge.scm: 406  append");
t9=*((C_word*)lf[115]+1);
((C_proc4)C_retrieve_proc(t9))(4,t9,t8,t4,C_SCHEME_END_OF_LIST);}

/* k6990 in k6978 in k6975 in k6972 in expand-send in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6992(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6992,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_6995,a[2]=((C_word*)t0)[9],a[3]=((C_word*)t0)[10],a[4]=t1,a[5]=((C_word*)t0)[11],tmp=(C_word)a,a+=6,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_7040,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[10],a[9]=((C_word*)t0)[7],a[10]=t4,a[11]=((C_word*)t0)[8],a[12]=((C_word)li168),tmp=(C_word)a,a+=13,tmp));
t6=((C_word*)t4)[1];
f_7040(t6,t2,C_SCHEME_FALSE,C_SCHEME_FALSE,C_fix(0));}

/* do1572 in k6990 in k6978 in k6975 in k6972 in expand-send in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_7040(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
C_save_and_reclaim((void*)trf_7040,NULL,5,t0,t1,t2,t3,t4);}
t5=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[11])[1]))){
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,C_SCHEME_FALSE);}
else{
t8=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_7050,a[2]=t7,a[3]=t6,a[4]=t5,a[5]=t1,a[6]=((C_word*)t0)[10],tmp=(C_word)a,a+=7,tmp);
t9=(*a=C_CLOSURE_TYPE|14,a[1]=(C_word)f_7056,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t7,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=t6,a[10]=((C_word*)t0)[8],a[11]=t5,a[12]=((C_word*)t0)[11],a[13]=t8,a[14]=((C_word*)t0)[9],tmp=(C_word)a,a+=15,tmp);
t10=((C_word*)((C_word*)t0)[9])[1];
if(C_truep(t10)){
t11=t9;
f_7056(2,t11,C_SCHEME_FALSE);}
else{
t11=(C_word)C_i_car(((C_word*)((C_word*)t0)[11])[1]);
C_trace("ChickenBridge.scm: 417  keyword?");
t12=C_retrieve(lf[240]);
((C_proc3)C_retrieve_proc(t12))(3,t12,t9,t11);}}}

/* k7054 in do1572 in k6990 in k6978 in k6975 in k6972 in expand-send in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7056(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_7056,2,t0,t1);}
if(C_truep(t1)){
t2=C_set_block_item(((C_word*)t0)[14],0,C_SCHEME_TRUE);
t3=((C_word*)t0)[13];
f_7050(t3,t2);}
else{
t2=((C_word*)((C_word*)t0)[14])[1];
if(C_truep(t2)){
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[12])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[11])+1,t3);
t5=(C_word)C_i_assoc(((C_word*)((C_word*)t0)[11])[1],((C_word*)t0)[10]);
t6=C_mutate(((C_word *)((C_word*)t0)[9])+1,t5);
t7=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[12])[1]);
t8=C_mutate(((C_word *)((C_word*)t0)[12])+1,t7);
t9=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_7110,a[2]=((C_word*)t0)[11],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],a[6]=((C_word*)t0)[13],a[7]=((C_word*)t0)[12],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],tmp=(C_word)a,a+=10,tmp);
t10=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_7183,a[2]=((C_word*)t0)[10],a[3]=((C_word*)t0)[9],a[4]=((C_word*)t0)[11],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t9,a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[12],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 437  keyword?");
t11=C_retrieve(lf[240]);
((C_proc3)C_retrieve_proc(t11))(3,t11,t10,((C_word*)((C_word*)t0)[11])[1]);}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_7066,a[2]=((C_word*)t0)[13],a[3]=((C_word*)t0)[12],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[8],tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_nequalp(((C_word*)((C_word*)t0)[4])[1],((C_word*)t0)[3]))){
t4=(C_word)C_i_length(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 427  ferror");
t5=((C_word*)t0)[7];
((C_proc6)C_retrieve_proc(t5))(6,t5,t3,lf[241],((C_word*)t0)[6],((C_word*)t0)[3],t4);}
else{
t4=t3;
f_7066(2,t4,C_SCHEME_UNDEFINED);}}}}

/* k7064 in k7054 in do1572 in k6990 in k6978 in k6975 in k6972 in expand-send in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7066(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_7066,2,t0,t1);}
t2=(C_word)C_i_list_tail(((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]);
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
t4=(C_word)C_i_set_car(t2,t3);
t5=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[3])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t5);
t7=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[4])[1],C_fix(1));
t8=C_mutate(((C_word *)((C_word*)t0)[4])+1,t7);
t9=((C_word*)t0)[2];
f_7050(t9,t8);}

/* k7181 in k7054 in do1572 in k6990 in k6978 in k6975 in k6972 in expand-send in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7183(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[15],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7183,2,t0,t1);}
if(C_truep(t1)){
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[9])[1]))){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7156,a[2]=((C_word*)t0)[6],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[8],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 442  keyname");
t3=((C_word*)t0)[5];
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)((C_word*)t0)[4])[1]);}
else{
t2=((C_word*)((C_word*)t0)[3])[1];
if(C_truep(t2)){
t3=((C_word*)t0)[7];
f_7110(2,t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_7169,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],a[5]=((C_word*)t0)[8],tmp=(C_word)a,a+=6,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_7171,a[2]=((C_word*)t0)[5],a[3]=((C_word)li167),tmp=(C_word)a,a+=4,tmp);
C_trace("map");
t5=*((C_word*)lf[166]+1);
((C_proc4)(void*)(*((C_word*)t5+1)))(4,t5,t3,t4,((C_word*)t0)[2]);}}}
else{
C_trace("ChickenBridge.scm: 438  ferror");
t2=((C_word*)t0)[8];
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[7],lf[239],((C_word*)t0)[6],((C_word*)((C_word*)t0)[4])[1]);}}

/* a7170 in k7181 in k7054 in do1572 in k6990 in k6978 in k6975 in k6972 in expand-send in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7171(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_7171,3,t0,t1,t2);}
t3=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 446  keyname");
t4=((C_word*)t0)[2];
((C_proc3)C_retrieve_proc(t4))(3,t4,t1,t3);}

/* k7167 in k7181 in k7054 in do1572 in k6990 in k6978 in k6975 in k6972 in expand-send in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7169(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 444  ferror");
t2=((C_word*)t0)[5];
((C_proc6)C_retrieve_proc(t2))(6,t2,((C_word*)t0)[4],lf[238],((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k7154 in k7181 in k7054 in do1572 in k6990 in k6978 in k6975 in k6972 in expand-send in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7156(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 441  ferror");
t2=((C_word*)t0)[4];
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[3],lf[237],((C_word*)t0)[2],t1);}

/* k7108 in k7054 in do1572 in k6990 in k6978 in k6975 in k6972 in expand-send in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7110(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_7110,2,t0,t1);}
t2=(C_word)C_i_member(((C_word*)((C_word*)t0)[9])[1],((C_word*)t0)[8]);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7116,a[2]=((C_word*)t0)[6],a[3]=t2,a[4]=((C_word*)t0)[7],tmp=(C_word)a,a+=5,tmp);
if(C_truep(t2)){
t4=t3;
f_7116(2,t4,C_SCHEME_UNDEFINED);}
else{
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7137,a[2]=((C_word*)t0)[4],a[3]=t3,a[4]=((C_word*)t0)[5],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 452  keyname");
t5=((C_word*)t0)[3];
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,((C_word*)((C_word*)t0)[2])[1]);}}

/* k7135 in k7108 in k7054 in do1572 in k6990 in k6978 in k6975 in k6972 in expand-send in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7137(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 451  ferror");
t2=((C_word*)t0)[4];
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[3],lf[236],((C_word*)t0)[2],t1);}

/* k7114 in k7108 in k7054 in do1572 in k6990 in k6978 in k6975 in k6972 in expand-send in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7116(C_word c,C_word t0,C_word t1){
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
f_7050(t6,t5);}

/* k7048 in do1572 in k6990 in k6978 in k6975 in k6972 in expand-send in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_7050(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[6])[1];
f_7040(t2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k6993 in k6990 in k6978 in k6975 in k6972 in expand-send in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6995(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6995,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_7000,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word)li166),tmp=(C_word)a,a+=7,tmp));
t5=((C_word*)t3)[1];
f_7000(t5,((C_word*)t0)[2],((C_word*)t0)[4]);}

/* do1590 in k6993 in k6990 in k6978 in k6975 in k6972 in expand-send in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_7000(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_7000,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[5],((C_word*)t0)[4]));}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_7013,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_member(t4,((C_word*)t0)[2]))){
t5=(C_word)C_i_car(t2);
t6=(C_word)C_i_cadr(t5);
t7=t3;
f_7013(t7,(C_word)C_i_set_car(t2,t6));}
else{
t5=t3;
f_7013(t5,C_SCHEME_UNDEFINED);}}}

/* k7011 in do1590 in k6993 in k6990 in k6978 in k6975 in k6972 in expand-send in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_7013(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_7000(t3,((C_word*)t0)[2],t2);}

/* f_7222 in expand-send in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7222(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_7222,3,t0,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,t2);}

/* f_7213 in expand-send in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7213(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_7213,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7221,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 395  keyword->string");
t4=C_retrieve(lf[235]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,t2);}

/* k7219 */
static void C_ccall f_7221(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 395  sprintf");
t2=C_retrieve(lf[174]);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[2],lf[234],t1);}

/* f_7224 in expand-send in k6960 in k6957 in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_7224(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+3)){
C_save_and_reclaim((void*)tr3r,(void*)f_7224r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_7224r(t0,t1,t2,t3);}}

static void C_ccall f_7224r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word *a=C_alloc(3);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_7232,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_apply(5,0,t4,C_retrieve(lf[174]),t2,t3);}

/* k7230 */
static void C_ccall f_7232(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 391  error");
t2=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* hush in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6948(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6948,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6952,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6611,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[215]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k6609 in hush in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6611(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6611,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub1482,a[2]=((C_word)li161),tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k6950 in hush in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6952(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 363  values");
C_values(2,0,((C_word*)t0)[2]);}

/* stop in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6890(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+9)){
C_save_and_reclaim((void*)tr2r,(void*)f_6890r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_6890r(t0,t1,t2);}}

static void C_ccall f_6890r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a=C_alloc(9);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6894,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 353  scheduler-stop");
f_6594(t3,C_fix(-1));}
else{
t4=C_SCHEME_UNDEFINED;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_set_block_item(t5,0,(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6908,a[2]=t5,a[3]=((C_word)li159),tmp=(C_word)a,a+=4,tmp));
t7=((C_word*)t5)[1];
f_6908(t7,t3,t2);}}

/* do1539 in stop in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_6908(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6908,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6918,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_fixnump(t4))){
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 357  scheduler-stop");
f_6594(t3,t5);}
else{
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 358  error");
t6=*((C_word*)lf[27]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t3,lf[230],t5);}}}

/* k6916 in do1539 in stop in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6918(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_6908(t3,((C_word*)t0)[2],t2);}

/* k6892 in stop in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6894(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 359  values");
C_values(2,0,((C_word*)t0)[2]);}

/* cont in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6881(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6881,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6885,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6589,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[215]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k6587 in cont in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6589(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6589,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub1472,a[2]=((C_word)li157),tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k6883 in cont in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6885(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 349  values");
C_values(2,0,((C_word*)t0)[2]);}

/* paused? in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6875(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6875,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6571,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t3=C_retrieve(lf[215]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,C_SCHEME_FALSE);}

/* k6569 in paused? in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6571(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6571,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub1464,a[2]=((C_word)li155),tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* pause in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6866(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6866,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6870,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6580,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[215]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k6578 in pause in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6580(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6580,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub1468,a[2]=((C_word)li153),tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k6868 in pause in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6870(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 342  values");
C_values(2,0,((C_word*)t0)[2]);}

/* time-format in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6803(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+11)){
C_save_and_reclaim((void*)tr2rv,(void*)f_6803r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_6803r(t0,t1,t2);}}

static void C_ccall f_6803r(C_word t0,C_word t1,C_word t2){
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
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6816,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6536,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#gc");
t5=C_retrieve(lf[215]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,C_SCHEME_FALSE);}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
t4=(C_word)C_i_eqvp(t3,lf[222]);
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6828,a[2]=t2,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
if(C_truep(t4)){
t6=t5;
f_6828(t6,t4);}
else{
t6=(C_word)C_eqp(t3,C_fix(1));
t7=t5;
f_6828(t7,(C_truep(t6)?t6:(C_word)C_eqp(t3,lf[225])));}}}

/* k6826 in time-format in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_6828(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a;
if(C_truep(t1)){
t2=C_mutate((C_word*)lf[219]+1,C_retrieve(lf[213]));
C_trace("ChickenBridge.scm: 331  scheduler-set-time-milliseconds");
f_6541(((C_word*)t0)[4],C_SCHEME_FALSE);}
else{
t2=(C_word)C_eqp(((C_word*)t0)[3],C_fix(1000));
t3=(C_truep(t2)?t2:(C_word)C_eqp(((C_word*)t0)[3],lf[223]));
if(C_truep(t3)){
t4=C_mutate((C_word*)lf[219]+1,C_retrieve(lf[212]));
C_trace("ChickenBridge.scm: 335  scheduler-set-time-milliseconds");
f_6541(((C_word*)t0)[4],C_SCHEME_TRUE);}
else{
t4=(C_word)C_i_vector_ref(((C_word*)t0)[2],C_fix(0));
C_trace("ChickenBridge.scm: 338  error");
t5=*((C_word*)lf[27]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,((C_word*)t0)[4],lf[224],t4);}}}

/* k6534 in time-format in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6536(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6536,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub1444,a[2]=((C_word)li151),tmp=(C_word)a,a+=3,tmp);
((C_proc3)C_retrieve_proc(t3))(3,t3,((C_word*)t0)[2],t2);}

/* k6814 in time-format in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6816(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_truep(t1)?C_fix(1000):lf[221]));}

/* sprout in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6635(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+12)){
C_save_and_reclaim((void*)tr3r,(void*)f_6635r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_6635r(t0,t1,t2,t3);}}

static void C_ccall f_6635r(C_word t0,C_word t1,C_word t2,C_word t3){
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
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6637,a[2]=t2,a[3]=((C_word)li147),tmp=(C_word)a,a+=4,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6749,a[2]=t4,a[3]=((C_word)li148),tmp=(C_word)a,a+=4,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6754,a[2]=t5,a[3]=((C_word)li149),tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("def-start14991520");
t7=t6;
f_6754(t7,t1);}
else{
t7=(C_word)C_i_car(t3);
t8=(C_word)C_i_cdr(t3);
if(C_truep((C_word)C_i_nullp(t8))){
C_trace("def-id15001518");
t9=t5;
f_6749(t9,t1,t7);}
else{
t9=(C_word)C_i_car(t8);
t10=(C_word)C_i_cdr(t8);
if(C_truep((C_word)C_i_nullp(t10))){
C_trace("body14971502");
t11=t4;
f_6637(t11,t1,t7,t9);}
else{
C_trace("##sys#error");
t11=*((C_word*)lf[20]+1);
((C_proc4)(void*)(*((C_word*)t11+1)))(4,t11,t1,lf[0],t10);}}}}

/* def-start1499 in sprout in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_6754(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6754,NULL,2,t0,t1);}
C_trace("def-id15001518");
t2=((C_word*)t0)[2];
f_6749(t2,t1,C_fix(0));}

/* def-id1500 in sprout in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_6749(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6749,NULL,3,t0,t1,t2);}
C_trace("body14971502");
t3=((C_word*)t0)[2];
f_6637(t3,t1,t2,C_fix(-1));}

/* body1497 in sprout in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_6637(C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)trf_6637,NULL,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6639,a[2]=t4,a[3]=((C_word)li144),tmp=(C_word)a,a+=4,tmp);
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6667,a[2]=t5,a[3]=((C_word)li145),tmp=(C_word)a,a+=4,tmp);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6697,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t0)[2]))){
t9=C_SCHEME_UNDEFINED;
t10=(*a=C_VECTOR_TYPE|1,a[1]=t9,tmp=(C_word)a,a+=2,tmp);
t11=C_set_block_item(t10,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_6708,a[2]=t6,a[3]=t7,a[4]=t10,a[5]=((C_word*)t0)[2],a[6]=((C_word)li146),tmp=(C_word)a,a+=7,tmp));
t12=((C_word*)t10)[1];
f_6708(t12,t8,((C_word*)t0)[2]);}
else{
t9=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6740,a[2]=((C_word*)t0)[2],a[3]=t8,tmp=(C_word)a,a+=4,tmp);
t10=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6744,a[2]=t7,a[3]=((C_word*)t0)[2],a[4]=t9,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 315  nextstart");
t11=t6;
f_6639(t11,t10);}}

/* k6742 in body1497 in sprout in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6744(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6744,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6748,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 315  nextid");
t3=((C_word*)t0)[2];
f_6667(t3,t2);}

/* k6746 in k6742 in body1497 in sprout in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6748(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 315  scheduler-sprout");
f_6550(((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k6738 in body1497 in sprout in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6740(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
f_6697(2,t2,((C_word*)t0)[2]);}

/* do1511 in body1497 in sprout in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_6708(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6708,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,((C_word*)t0)[5]);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6718,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6733,a[2]=((C_word*)t0)[3],a[3]=t4,a[4]=t3,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 313  nextstart");
t6=((C_word*)t0)[2];
f_6639(t6,t5);}}

/* k6731 in do1511 in body1497 in sprout in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6733(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6733,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6737,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 313  nextid");
t3=((C_word*)t0)[2];
f_6667(t3,t2);}

/* k6735 in k6731 in do1511 in body1497 in sprout in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6737(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 313  scheduler-sprout");
f_6550(((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k6716 in do1511 in body1497 in sprout in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6718(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_6708(t3,((C_word*)t0)[2],t2);}

/* k6695 in body1497 in sprout in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6697(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 319  values");
C_values(2,0,((C_word*)t0)[2]);}

/* nextid in body1497 in sprout in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_6667(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_6667,NULL,2,t0,t1);}
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

/* nextstart in body1497 in sprout in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_6639(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_6639,NULL,2,t0,t1);}
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

/* load-sal-file in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6616(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6616,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6621,a[2]=((C_word)li142),tmp=(C_word)a,a+=3,tmp);
((C_proc3)(void*)(*((C_word*)t3+1)))(3,t3,t1,t2);}

/* f_6621 in load-sal-file in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6621(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6621,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6626,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[211]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_6626(2,t4,C_SCHEME_FALSE);}}

/* k6624 */
static void C_ccall f_6626(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub1488(C_SCHEME_UNDEFINED,t1));}

/* scheduler-stop in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_6594(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6594,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6598,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[215]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k6596 in scheduler-stop in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6598(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6598,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_fixnum_argumentp(((C_word*)t0)[3]);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub1477,a[2]=((C_word)li140),tmp=(C_word)a,a+=3,tmp);
((C_proc4)C_retrieve_proc(t4))(4,t4,((C_word*)t0)[2],t2,t3);}

/* scheduler-sprout in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_6550(C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6550,NULL,4,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_6554,a[2]=t2,a[3]=t1,a[4]=t4,a[5]=t3,tmp=(C_word)a,a+=6,tmp);
C_trace("##sys#gc");
t6=C_retrieve(lf[215]);
((C_proc3)C_retrieve_proc(t6))(3,t6,t5,C_SCHEME_FALSE);}

/* k6552 in scheduler-sprout in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6554(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6554,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[5]);
t4=(C_word)C_i_foreign_fixnum_argumentp(((C_word*)t0)[4]);
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub1457,a[2]=((C_word)li138),tmp=(C_word)a,a+=3,tmp);
((C_proc6)C_retrieve_proc(t5))(6,t5,((C_word*)t0)[3],t2,((C_word*)t0)[2],t3,t4);}

/* scheduler-set-time-milliseconds in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_6541(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6541,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6545,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("##sys#gc");
t4=C_retrieve(lf[215]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,C_SCHEME_FALSE);}

/* k6543 in scheduler-set-time-milliseconds in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6545(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6545,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub1449,a[2]=((C_word)li136),tmp=(C_word)a,a+=3,tmp);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[3],t2,((C_word*)t0)[2]);}

/* current-time-seconds in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6529(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6529,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub1441(t2));}

/* current-time-milliseconds in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6526(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6526,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub1438(t2));}

/* print-error in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6483(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6483,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6488,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[211]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_6488(2,t4,C_SCHEME_FALSE);}}

/* k6486 in print-error in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6488(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub1419(C_SCHEME_UNDEFINED,t1));}

/* print-message in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6469(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6469,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6474,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[211]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_6474(2,t4,C_SCHEME_FALSE);}}

/* k6472 in print-message in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6474(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub1413(C_SCHEME_UNDEFINED,t1));}

/* change-directory in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6440(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+3)){
C_save_and_reclaim((void*)tr2rv,(void*)f_6440r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_6440r(t0,t1,t2);}}

static void C_ccall f_6440r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word *a=C_alloc(3);
t3=(C_word)C_vemptyp(t2);
t4=(C_truep(t3)?lf[210]:(C_word)C_i_vector_ref(t2,C_fix(0)));
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6449,a[2]=((C_word)li130),tmp=(C_word)a,a+=3,tmp);
((C_proc3)(void*)(*((C_word*)t5+1)))(3,t5,t1,t4);}

/* f_6449 in change-directory in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6449(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6449,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6454,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[211]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_6454(2,t4,C_SCHEME_FALSE);}}

/* k6452 */
static void C_ccall f_6454(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub1407(C_SCHEME_UNDEFINED,t1));}

/* current-directory in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6429(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[3],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6429,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6434,a[2]=((C_word)li128),tmp=(C_word)a,a+=3,tmp);
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,t1);}

/* f_6434 in current-directory in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6434(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6434,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(3));
C_trace("##sys#peek-c-string");
t3=*((C_word*)lf[209]+1);
((C_proc4)(void*)(*((C_word*)t3+1)))(4,t3,t1,(C_word)stub1402(t2),C_fix(0));}

/* list* in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6389(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+4)){
C_save_and_reclaim((void*)tr2r,(void*)f_6389r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_6389r(t0,t1,t2);}}

static void C_ccall f_6389r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word *a=C_alloc(4);
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 207  error");
t3=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[207]);}
else{
t3=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t3))){
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_car(t2));}
else{
t4=(C_word)C_i_car(t2);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6419,a[2]=t4,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
t6=(C_word)C_i_cdr(t2);
C_apply(4,0,t5,C_retrieve(lf[206]),t6);}}}

/* k6417 in list* in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6419(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6419,2,t0,t1);}
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[2],t1));}

/* butlast in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6341(C_word c,C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)tr3,(void*)f_6341,3,t0,t1,t2);}
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
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6375,a[2]=t5,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
t7=(C_word)C_i_cdr(t2);
C_trace("ChickenBridge.scm: 203  butlast");
t8=C_retrieve(lf[205]);
((C_proc3)C_retrieve_proc(t8))(3,t8,t6,t7);}}}

/* k6373 in butlast in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6375(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6375,2,t0,t1);}
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[2],t1));}

/* last in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6321(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6321,3,t0,t1,t2);}
t3=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t3))){
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,t2);}
else{
t4=(C_word)C_i_cdr(t2);
C_trace("ChickenBridge.scm: 197  last");
t5=C_retrieve(lf[204]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t1,t4);}}

/* tenth in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6301(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6301,3,t0,t1,t2);}
t3=(C_word)C_i_cddddr(t2);
t4=(C_word)C_i_cddddr(t3);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)C_i_cadr(t4));}

/* ninth in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6287(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6287,3,t0,t1,t2);}
t3=(C_word)C_i_cddddr(t2);
t4=(C_word)C_i_cddddr(t3);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)C_i_car(t4));}

/* eighth in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6277(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6277,3,t0,t1,t2);}
t3=(C_word)C_i_cddddr(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_cadddr(t3));}

/* seventh in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6267(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6267,3,t0,t1,t2);}
t3=(C_word)C_i_cddddr(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_caddr(t3));}

/* sixth in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6257(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6257,3,t0,t1,t2);}
t3=(C_word)C_i_cddddr(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_cadr(t3));}

/* fifth in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6247(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6247,3,t0,t1,t2);}
t3=(C_word)C_i_cddddr(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_car(t3));}

/* sal:output in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6225(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6225,2,t0,t1);}
C_trace("ChickenBridge.scm: 145  print-error");
t2=C_retrieve(lf[155]);
((C_proc3)C_retrieve_proc(t2))(3,t2,t1,lf[191]);}

/* sal:open in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6219(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6219,2,t0,t1);}
C_trace("ChickenBridge.scm: 145  print-error");
t2=C_retrieve(lf[155]);
((C_proc3)C_retrieve_proc(t2))(3,t2,t1,lf[189]);}

/* sal:load in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6172(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6172,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6176,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  file-exists?");
t4=C_retrieve(lf[187]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,t2);}

/* k6174 in sal:load in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6176(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_6176,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6179,a[2]=((C_word*)t0)[3],tmp=(C_word)a,a+=3,tmp);
if(C_truep(t1)){
t3=(C_word)C_i_string_length(((C_word*)t0)[2]);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_6201,a[2]=((C_word*)t0)[2],a[3]=t2,tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_greaterp(t3,C_fix(4)))){
t5=(C_word)C_a_i_minus(&a,2,t3,C_fix(4));
C_trace("substring=?");
t6=C_retrieve(lf[183]);
((C_proc7)(void*)(*((C_word*)t6+1)))(7,t6,t4,((C_word*)t0)[2],lf[184],t5,C_fix(0),C_SCHEME_FALSE);}
else{
t5=t4;
f_6201(2,t5,C_SCHEME_FALSE);}}
else{
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6192,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  string-append");
t4=*((C_word*)lf[156]+1);
((C_proc5)C_retrieve_proc(t4))(5,t4,t3,lf[185],((C_word*)t0)[2],lf[186]);}}

/* k6190 in k6174 in sal:load in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6192(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  print-error");
t2=C_retrieve(lf[155]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k6199 in k6174 in sal:load in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6201(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(C_truep(t1)){
C_trace("ChickenBridge.scm: 145  load-sal-file");
t2=C_retrieve(lf[181]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}
else{
C_trace("ChickenBridge.scm: 145  load");
t2=C_retrieve(lf[182]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}}

/* k6177 in k6174 in sal:load in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6179(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  values");
C_values(2,0,((C_word*)t0)[2]);}

/* sal:chdir in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6163(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_6163,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6167,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  change-directory");
t4=C_retrieve(lf[179]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,t2);}

/* k6165 in sal:chdir in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6167(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  values");
C_values(2,0,((C_word*)t0)[2]);}

/* sal:print in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5984(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+16)){
C_save_and_reclaim((void*)tr2r,(void*)f_5984r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_5984r(t0,t1,t2);}}

static void C_ccall f_5984r(C_word t0,C_word t1,C_word t2){
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
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5987,a[2]=t4,a[3]=((C_word)li112),tmp=(C_word)a,a+=4,tmp));
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6132,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t7=C_SCHEME_UNDEFINED;
t8=(*a=C_VECTOR_TYPE|1,a[1]=t7,tmp=(C_word)a,a+=2,tmp);
t9=C_set_block_item(t8,0,(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6137,a[2]=t4,a[3]=t8,a[4]=((C_word)li113),tmp=(C_word)a,a+=5,tmp));
t10=((C_word*)t8)[1];
f_6137(t10,t6,t2);}

/* do1256 in sal:print in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_6137(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6137,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 145  print-message");
t3=C_retrieve(lf[168]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[177]);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6150,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  printer");
t5=((C_word*)((C_word*)t0)[2])[1];
f_5987(t5,t3,t4);}}

/* k6148 in do1256 in sal:print in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6150(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_6137(t3,((C_word*)t0)[2],t2);}

/* k6130 in sal:print in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6132(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  values");
C_values(2,0,((C_word*)t0)[2]);}

/* printer in sal:print in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_5987(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_5987,NULL,3,t0,t1,t2);}
t3=t2;
if(C_truep(t3)){
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 145  print-message");
t4=C_retrieve(lf[168]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t1,lf[169]);}
else{
if(C_truep((C_word)C_i_pairp(t2))){
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6015,a[2]=t2,a[3]=((C_word*)t0)[2],a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  print-message");
t5=C_retrieve(lf[168]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,lf[172]);}
else{
t4=(C_word)C_eqp(t2,C_SCHEME_TRUE);
if(C_truep(t4)){
C_trace("ChickenBridge.scm: 145  print-message");
t5=C_retrieve(lf[168]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t1,lf[173]);}
else{
if(C_truep((C_word)C_i_numberp(t2))){
if(C_truep((C_word)C_i_inexactp(t2))){
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6102,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6106,a[2]=t5,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  decimals");
t7=*((C_word*)lf[16]+1);
((C_proc4)C_retrieve_proc(t7))(4,t7,t6,t2,C_fix(3));}
else{
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6113,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  number->string");
C_number_to_string(3,0,t5,t2);}}
else{
if(C_truep((C_word)C_i_stringp(t2))){
C_trace("ChickenBridge.scm: 145  print-message");
t5=C_retrieve(lf[168]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t1,t2);}
else{
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6129,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  sprintf");
t6=C_retrieve(lf[174]);
((C_proc4)C_retrieve_proc(t6))(4,t6,t5,lf[175],t2);}}}}}}
else{
C_trace("ChickenBridge.scm: 145  print-message");
t4=C_retrieve(lf[168]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t1,lf[176]);}}

/* k6127 in printer in sal:print in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6129(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  print-message");
t2=C_retrieve(lf[168]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k6111 in printer in sal:print in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6113(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  print-message");
t2=C_retrieve(lf[168]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k6104 in printer in sal:print in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6106(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  number->string");
C_number_to_string(3,0,((C_word*)t0)[2],t1);}

/* k6100 in printer in sal:print in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6102(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  print-message");
t2=C_retrieve(lf[168]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k6013 in printer in sal:print in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6015(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6015,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_6018,a[2]=((C_word*)t0)[4],tmp=(C_word)a,a+=3,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6023,a[2]=((C_word*)t0)[3],a[3]=t4,a[4]=((C_word)li111),tmp=(C_word)a,a+=5,tmp));
t6=((C_word*)t4)[1];
f_6023(t6,t2,((C_word*)t0)[2]);}

/* do1248 in k6013 in printer in sal:print in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_6023(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_6023,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6033,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  printer");
t5=((C_word*)((C_word*)t0)[2])[1];
f_5987(t5,t3,t4);}}

/* k6031 in do1248 in k6013 in printer in sal:print in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6033(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_6033,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_6036,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
t3=(C_word)C_i_cdr(((C_word*)t0)[4]);
if(C_truep((C_word)C_i_nullp(t3))){
t4=t2;
f_6036(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 145  print-message");
t4=C_retrieve(lf[168]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t2,lf[171]);}}

/* k6034 in k6031 in do1248 in k6013 in printer in sal:print in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6036(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_6023(t3,((C_word*)t0)[2],t2);}

/* k6016 in k6013 in printer in sal:print in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_6018(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  print-message");
t2=C_retrieve(lf[168]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],lf[170]);}

/* sal in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5813(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[7],*a=ab;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_5813,6,t0,t1,t2,t3,t4,t5);}
t6=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t7=C_mutate(&lf[151],t2);
t8=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5819,a[2]=t6,a[3]=t5,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("map");
t9=*((C_word*)lf[166]+1);
((C_proc4)(void*)(*((C_word*)t9+1)))(4,t9,t8,C_retrieve2(lf[64],"list->token"),t4);}

/* k5817 in sal in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5819(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5819,2,t0,t1);}
t2=C_mutate(&lf[152],t1);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5822,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
if(C_truep((C_word)C_i_nequalp(((C_word*)((C_word*)t0)[2])[1],C_fix(0)))){
t4=C_set_block_item(((C_word*)t0)[2],0,C_fix(36608));
t5=t3;
f_5822(t5,t4);}
else{
t4=t3;
f_5822(t4,C_SCHEME_FALSE);}}

/* k5820 in k5817 in sal in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_5822(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_5822,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5826,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
t3=((C_word*)((C_word*)t0)[2])[1];
t4=C_retrieve2(lf[152],"*sal-tokens*");
t5=(C_word)C_a_i_list(&a,4,C_SCHEME_FALSE,C_fix(0),C_SCHEME_FALSE,C_SCHEME_FALSE);
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3625,a[2]=t4,a[3]=t3,a[4]=((C_word)li109),tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  call/cc");
t7=*((C_word*)lf[165]+1);
((C_proc3)C_retrieve_proc(t7))(3,t7,t2,t6);}

/* a3624 in k5820 in k5817 in sal in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3625(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_3625,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3631,a[2]=t2,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word)li107),tmp=(C_word)a,a+=6,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3638,a[2]=t2,a[3]=((C_word)li108),tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  call-with-values");
C_call_with_values(4,0,t1,t3,t4);}

/* a3637 in a3624 in k5820 in k5817 in sal in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3638(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_3638,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3645,a[2]=((C_word*)t0)[2],a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
if(C_truep(t2)){
t6=(C_word)C_i_nullp(t4);
t7=t5;
f_3645(t7,(C_truep(t6)?t6:C_SCHEME_FALSE));}
else{
t6=t5;
f_3645(t6,C_SCHEME_FALSE);}}

/* k3643 in a3637 in a3624 in k5820 in k5817 in sal in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3645(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3645,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3652,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  add-emit-info");
f_3282(t2,lf[162],lf[163],C_SCHEME_END_OF_LIST);}
else{
C_trace("ChickenBridge.scm: 145  make-parse-error");
f_3102(((C_word*)t0)[4],lf[164],C_retrieve2(lf[116],"*maxtokpos*"));}}

/* k3650 in k3643 in a3637 in a3624 in k5820 in k5817 in sal in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3652(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  emit");
f_3310(((C_word*)t0)[4],((C_word*)t0)[3],t1,((C_word*)t0)[2]);}

/* a3630 in a3624 in k5820 in k5817 in sal in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3631(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3631,2,t0,t1);}
t2=lf[116]=C_fix(0);;
C_trace("ChickenBridge.scm: 145  parser");
f_3663(t1,((C_word*)t0)[4],((C_word*)t0)[3],C_SCHEME_FALSE,C_fix(0),C_SCHEME_FALSE,((C_word*)t0)[2]);}

/* k5824 in k5820 in k5817 in sal in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5826(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5826,2,t0,t1);}
t2=C_mutate(&lf[153],t1);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5829,a[2]=((C_word*)t0)[3],tmp=(C_word)a,a+=3,tmp);
t4=C_retrieve2(lf[153],"*sal-output*");
if(C_truep((C_word)C_i_structurep(t4,lf[82]))){
t5=C_retrieve2(lf[151],"*sal-string*");
t6=C_retrieve2(lf[153],"*sal-output*");
t7=(C_word)C_i_string_length(t5);
t8=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_5860,a[2]=t7,a[3]=t6,a[4]=t5,a[5]=t3,tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  parse-error-position");
f_3141(t8,t6);}
else{
if(C_truep(((C_word*)t0)[2])){
C_trace("ChickenBridge.scm: 145  pp");
t5=C_retrieve(lf[160]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,C_retrieve2(lf[153],"*sal-output*"));}
else{
C_trace("ChickenBridge.scm: 145  eval");
t5=C_retrieve(lf[161]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,C_retrieve2(lf[153],"*sal-output*"));}}}

/* k5858 in k5824 in k5820 in k5817 in sal in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5860(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5860,2,t0,t1);}
t2=(C_word)C_a_i_minus(&a,2,t1,C_fix(1));
t3=t2;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_fix(0);
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_5866,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=t1,a[7]=t6,a[8]=t4,tmp=(C_word)a,a+=9,tmp);
t8=C_SCHEME_UNDEFINED;
t9=(*a=C_VECTOR_TYPE|1,a[1]=t8,tmp=(C_word)a,a+=2,tmp);
t10=C_set_block_item(t9,0,(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_5953,a[2]=((C_word*)t0)[4],a[3]=t9,a[4]=t4,a[5]=((C_word)li106),tmp=(C_word)a,a+=6,tmp));
t11=((C_word*)t9)[1];
f_5953(t11,t7,C_SCHEME_FALSE);}

/* do1222 in k5858 in k5824 in k5820 in k5817 in sal in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_5953(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_5953,NULL,3,t0,t1,t2);}
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=((C_word*)t3)[1];
t5=(C_truep(t4)?t4:(C_word)C_i_nequalp(((C_word*)((C_word*)t0)[4])[1],C_fix(-1)));
if(C_truep(t5)){
t6=t1;
((C_proc2)(void*)(*((C_word*)t6+1)))(2,t6,C_SCHEME_FALSE);}
else{
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5963,a[2]=t3,a[3]=t1,a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
t7=(C_word)C_i_string_ref(((C_word*)t0)[2],((C_word*)((C_word*)t0)[4])[1]);
t8=(C_word)C_eqp(t7,C_make_character(10));
if(C_truep(t8)){
t9=C_set_block_item(t3,0,C_SCHEME_TRUE);
t10=t6;
f_5963(t10,t9);}
else{
t9=(C_word)C_a_i_minus(&a,2,((C_word*)((C_word*)t0)[4])[1],C_fix(1));
t10=C_mutate(((C_word *)((C_word*)t0)[4])+1,t9);
t11=t6;
f_5963(t11,t10);}}}

/* k5961 in do1222 in k5858 in k5824 in k5820 in k5817 in sal in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_5963(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[4])[1];
f_5953(t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1]);}

/* k5864 in k5858 in k5824 in k5820 in k5817 in sal in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5866(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5866,2,t0,t1);}
t2=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[8])[1],C_fix(1));
t3=C_mutate(((C_word *)((C_word*)t0)[8])+1,t2);
t4=C_mutate(((C_word *)((C_word*)t0)[7])+1,((C_word*)t0)[6]);
t5=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5874,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[8],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[5],tmp=(C_word)a,a+=8,tmp);
t6=C_SCHEME_UNDEFINED;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=C_set_block_item(t7,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5923,a[2]=((C_word*)t0)[4],a[3]=t7,a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[7],a[6]=((C_word)li105),tmp=(C_word)a,a+=7,tmp));
t9=((C_word*)t7)[1];
f_5923(t9,t5,C_SCHEME_FALSE);}

/* do1229 in k5864 in k5858 in k5824 in k5820 in k5817 in sal in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_5923(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_5923,NULL,3,t0,t1,t2);}
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=((C_word*)t3)[1];
t5=(C_truep(t4)?t4:(C_word)C_i_nequalp(((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[4]));
if(C_truep(t5)){
t6=t1;
((C_proc2)(void*)(*((C_word*)t6+1)))(2,t6,C_SCHEME_FALSE);}
else{
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5933,a[2]=t3,a[3]=t1,a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
t7=(C_word)C_i_string_ref(((C_word*)t0)[2],((C_word*)((C_word*)t0)[5])[1]);
t8=(C_word)C_eqp(t7,C_make_character(10));
if(C_truep(t8)){
t9=C_set_block_item(t3,0,C_SCHEME_TRUE);
t10=t6;
f_5933(t10,t9);}
else{
t9=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[5])[1],C_fix(1));
t10=C_mutate(((C_word *)((C_word*)t0)[5])+1,t9);
t11=t6;
f_5933(t11,t10);}}}

/* k5931 in do1229 in k5864 in k5858 in k5824 in k5820 in k5817 in sal in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_5933(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[4])[1];
f_5923(t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1]);}

/* k5872 in k5864 in k5858 in k5824 in k5820 in k5817 in sal in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5874(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[13],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5874,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5877,a[2]=((C_word*)t0)[7],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_5884,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5888,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=t3,a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  parse-error-string");
f_3123(t4,((C_word*)t0)[2]);}

/* k5886 in k5872 in k5864 in k5858 in k5824 in k5820 in k5817 in sal in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5888(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5888,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5892,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 145  make-string");
t3=*((C_word*)lf[158]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t2,C_fix(1),C_make_character(10));}

/* k5890 in k5886 in k5872 in k5864 in k5858 in k5824 in k5820 in k5817 in sal in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5892(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5892,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5896,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  substring");
t3=*((C_word*)lf[159]+1);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k5894 in k5890 in k5886 in k5872 in k5864 in k5858 in k5824 in k5820 in k5817 in sal in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5896(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5896,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5900,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 145  make-string");
t3=*((C_word*)lf[158]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t2,C_fix(1),C_make_character(10));}

/* k5898 in k5894 in k5890 in k5886 in k5872 in k5864 in k5858 in k5824 in k5820 in k5817 in sal in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5900(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[16],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5900,2,t0,t1);}
t2=(C_word)C_a_i_minus(&a,2,((C_word*)t0)[7],((C_word*)((C_word*)t0)[6])[1]);
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5907,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=t2,tmp=(C_word)a,a+=8,tmp);
t4=(C_word)C_a_i_plus(&a,2,t2,C_fix(2));
C_trace("ChickenBridge.scm: 145  make-string");
t5=*((C_word*)lf[158]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,t4,C_make_character(32));}

/* k5905 in k5898 in k5894 in k5890 in k5886 in k5872 in k5864 in k5858 in k5824 in k5820 in k5817 in sal in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5907(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5907,2,t0,t1);}
t2=(C_word)C_i_string_set(t1,((C_word*)t0)[7],C_make_character(94));
t3=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[7],C_fix(1));
t4=(C_word)C_i_string_set(t1,t3,C_make_character(10));
C_trace("ChickenBridge.scm: 145  string-append");
t5=*((C_word*)lf[156]+1);
((C_proc8)C_retrieve_proc(t5))(8,t5,((C_word*)t0)[6],lf[157],((C_word*)t0)[5],((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k5882 in k5872 in k5864 in k5858 in k5824 in k5820 in k5817 in sal in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5884(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  print-error");
t2=C_retrieve(lf[155]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* k5875 in k5872 in k5864 in k5858 in k5824 in k5820 in k5817 in sal in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5877(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  values");
C_values(2,0,((C_word*)t0)[2]);}

/* k5827 in k5824 in k5820 in k5817 in sal in k5805 in k5802 in k5799 in k5796 in k5793 in k5274 in k5271 in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5829(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  values");
C_values(2,0,((C_word*)t0)[2]);}

/* sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4752(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_4752,4,t0,t1,t2,t3);}
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
t32=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_4759,a[2]=t5,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
t33=(*a=C_CLOSURE_TYPE|18,a[1]=(C_word)f_4765,a[2]=t27,a[3]=t25,a[4]=t29,a[5]=t31,a[6]=t23,a[7]=t19,a[8]=t17,a[9]=t21,a[10]=t15,a[11]=t7,a[12]=t3,a[13]=t2,a[14]=t32,a[15]=t5,a[16]=t13,a[17]=t11,a[18]=t9,tmp=(C_word)a,a+=19,tmp);
t34=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3238(t33,t34,C_fix(23296));}

/* k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4765(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[25],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4765,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_4769,a[2]=((C_word*)t0)[14],a[3]=((C_word*)t0)[15],a[4]=((C_word*)t0)[16],a[5]=((C_word*)t0)[17],a[6]=((C_word*)t0)[18],tmp=(C_word)a,a+=7,tmp);
t3=(C_word)C_i_cadr(((C_word*)t0)[13]);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t2,t3,C_SCHEME_END_OF_LIST,((C_word*)t0)[12]);}
else{
t2=(*a=C_CLOSURE_TYPE|17,a[1]=(C_word)f_4815,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[16],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[13],a[10]=((C_word*)t0)[12],a[11]=((C_word*)t0)[8],a[12]=((C_word*)t0)[9],a[13]=((C_word*)t0)[14],a[14]=((C_word*)t0)[15],a[15]=((C_word*)t0)[10],a[16]=((C_word*)t0)[18],a[17]=((C_word*)t0)[11],tmp=(C_word)a,a+=18,tmp);
t3=(C_word)C_i_caddr(((C_word*)t0)[13]);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3238(t2,t3,C_fix(10756));}}

/* k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4815(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[26],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4815,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_4819,a[2]=((C_word*)t0)[9],a[3]=((C_word*)t0)[10],a[4]=((C_word*)t0)[11],a[5]=((C_word*)t0)[12],a[6]=((C_word*)t0)[13],a[7]=((C_word*)t0)[14],a[8]=((C_word*)t0)[15],a[9]=((C_word*)t0)[16],a[10]=((C_word*)t0)[17],tmp=(C_word)a,a+=11,tmp);
t3=(C_word)C_i_cadr(((C_word*)t0)[9]);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t2,t3,C_SCHEME_END_OF_LIST,((C_word*)t0)[10]);}
else{
t2=(*a=C_CLOSURE_TYPE|14,a[1]=(C_word)f_4912,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[10],a[9]=((C_word*)t0)[9],a[10]=((C_word*)t0)[13],a[11]=((C_word*)t0)[14],a[12]=((C_word*)t0)[8],a[13]=((C_word*)t0)[16],a[14]=((C_word*)t0)[17],tmp=(C_word)a,a+=15,tmp);
t3=(C_word)C_i_caddr(((C_word*)t0)[9]);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3238(t2,t3,C_fix(22784));}}

/* k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4912(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4912,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_4916,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[9],a[4]=((C_word*)t0)[10],a[5]=((C_word*)t0)[11],a[6]=((C_word*)t0)[12],a[7]=((C_word*)t0)[13],a[8]=((C_word*)t0)[14],tmp=(C_word)a,a+=9,tmp);
t3=(C_word)C_i_cadr(((C_word*)t0)[9]);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t2,t3,C_SCHEME_END_OF_LIST,((C_word*)t0)[8]);}
else{
t2=(C_word)C_i_length(((C_word*)t0)[9]);
t3=C_mutate(((C_word *)((C_word*)t0)[7])+1,t2);
t4=(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_4980,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[10],a[8]=((C_word*)t0)[11],a[9]=((C_word*)t0)[6],a[10]=((C_word*)t0)[9],a[11]=((C_word*)t0)[7],a[12]=((C_word*)t0)[14],tmp=(C_word)a,a+=13,tmp);
t5=(C_word)C_i_cadr(((C_word*)t0)[9]);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t4,t5,C_SCHEME_END_OF_LIST,((C_word*)t0)[8]);}}

/* k4978 in k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4980(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4980,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[12])+1,t1);
t3=(C_word)C_a_i_minus(&a,2,((C_word*)((C_word*)t0)[11])[1],C_fix(1));
t4=(C_word)C_i_list_ref(((C_word*)t0)[10],t3);
t5=C_mutate(((C_word *)((C_word*)t0)[9])+1,t4);
t6=(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_4987,a[2]=((C_word*)t0)[10],a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[11],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[5],a[8]=((C_word*)t0)[9],a[9]=((C_word*)t0)[6],a[10]=((C_word*)t0)[12],a[11]=((C_word*)t0)[7],a[12]=((C_word*)t0)[8],tmp=(C_word)a,a+=13,tmp);
if(C_truep(((C_word*)((C_word*)t0)[9])[1])){
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5237,a[2]=t6,a[3]=((C_word*)t0)[9],tmp=(C_word)a,a+=4,tmp);
t8=(C_word)C_i_cadr(((C_word*)((C_word*)t0)[9])[1]);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t7,t8,C_SCHEME_END_OF_LIST,((C_word*)t0)[2]);}
else{
t7=C_set_block_item(((C_word*)t0)[9],0,C_fix(1));
t8=t6;
f_4987(t8,t7);}}

/* k5235 in k4978 in k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5237(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_4987(t3,t2);}

/* k4985 in k4978 in k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_4987(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_4987,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_4990,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],a[5]=((C_word*)t0)[8],a[6]=((C_word*)t0)[9],a[7]=((C_word*)t0)[10],a[8]=((C_word*)t0)[11],a[9]=((C_word*)t0)[12],tmp=(C_word)a,a+=10,tmp);
if(C_truep((C_word)C_i_nequalp(((C_word*)((C_word*)t0)[4])[1],C_fix(6)))){
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5176,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t2,a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[9],tmp=(C_word)a,a+=8,tmp);
t4=(C_word)C_i_cadddr(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t3,t4,C_SCHEME_END_OF_LIST,((C_word*)t0)[3]);}
else{
t3=C_set_block_item(((C_word*)t0)[9],0,C_fix(0));
t4=(C_word)C_i_caddr(((C_word*)t0)[2]);
t5=C_mutate(((C_word *)((C_word*)t0)[6])+1,t4);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5225,a[2]=t2,a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t7=(C_word)C_i_cadddr(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t6,t7,C_SCHEME_END_OF_LIST,((C_word*)t0)[3]);}}

/* k5223 in k4985 in k4978 in k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5225(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_4990(t3,t2);}

/* k5174 in k4985 in k4978 in k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5176(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5176,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[7])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5182,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  fifth");
t4=C_retrieve(lf[139]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)t0)[2]);}

/* k5180 in k5174 in k4985 in k4978 in k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5182(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5182,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5206,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  fifth");
t3=C_retrieve(lf[139]);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)t0)[2]);}
else{
t2=C_set_block_item(((C_word*)t0)[6],0,C_SCHEME_FALSE);
t3=C_set_block_item(((C_word*)t0)[5],0,C_SCHEME_FALSE);
t4=((C_word*)t0)[4];
f_4990(t4,t3);}}

/* k5204 in k5180 in k5174 in k4985 in k4978 in k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5206(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5206,2,t0,t1);}
t2=(C_word)C_i_car(t1);
t3=C_mutate(((C_word *)((C_word*)t0)[6])+1,t2);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5190,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5202,a[2]=((C_word*)t0)[3],a[3]=t4,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  fifth");
t6=C_retrieve(lf[139]);
((C_proc3)C_retrieve_proc(t6))(3,t6,t5,((C_word*)t0)[2]);}

/* k5200 in k5204 in k5180 in k5174 in k4985 in k4978 in k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5202(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cadr(t1);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(((C_word*)t0)[3],t2,C_SCHEME_END_OF_LIST,((C_word*)t0)[2]);}

/* k5188 in k5204 in k5180 in k5174 in k4985 in k4978 in k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5190(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_4990(t3,t2);}

/* k4988 in k4985 in k4978 in k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_4990(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[15],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4990,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_4993,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],tmp=(C_word)a,a+=10,tmp);
if(C_truep((C_word)C_i_numberp(((C_word*)((C_word*)t0)[5])[1]))){
t3=t2;
f_4993(t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5152,a[2]=t2,a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[9],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  gensym");
t4=C_retrieve(lf[133]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,lf[150]);}}

/* k5150 in k4988 in k4985 in k4978 in k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5152(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[24],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5152,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_5156,a[2]=((C_word*)t0)[2],a[3]=t1,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=(C_word)C_a_i_list(&a,5,t1,((C_word*)((C_word*)t0)[3])[1],C_SCHEME_FALSE,C_SCHEME_FALSE,C_SCHEME_FALSE);
t4=(C_word)C_a_i_list(&a,1,t3);
C_trace("ChickenBridge.scm: 145  append");
t5=*((C_word*)lf[115]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t2,((C_word*)((C_word*)t0)[4])[1],t4);}

/* k5154 in k5150 in k4988 in k4985 in k4978 in k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5156(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[5])+1,t1);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,((C_word*)t0)[3]);
t4=((C_word*)t0)[2];
f_4993(t4,t3);}

/* k4991 in k4988 in k4985 in k4978 in k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_4993(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[15],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4993,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_4996,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],tmp=(C_word)a,a+=10,tmp);
if(C_truep((C_word)C_i_numberp(((C_word*)((C_word*)t0)[6])[1]))){
t3=t2;
f_4996(t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5129,a[2]=t2,a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[9],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  gensym");
t4=C_retrieve(lf[133]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,lf[149]);}}

/* k5127 in k4991 in k4988 in k4985 in k4978 in k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5129(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[24],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5129,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_5133,a[2]=((C_word*)t0)[2],a[3]=t1,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=(C_word)C_a_i_list(&a,5,t1,((C_word*)((C_word*)t0)[3])[1],C_SCHEME_FALSE,C_SCHEME_FALSE,C_SCHEME_FALSE);
t4=(C_word)C_a_i_list(&a,1,t3);
C_trace("ChickenBridge.scm: 145  append");
t5=*((C_word*)lf[115]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t2,((C_word*)((C_word*)t0)[4])[1],t4);}

/* k5131 in k5127 in k4991 in k4988 in k4985 in k4978 in k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5133(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[5])+1,t1);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,((C_word*)t0)[3]);
t4=((C_word*)t0)[2];
f_4996(t4,t3);}

/* k4994 in k4991 in k4988 in k4985 in k4978 in k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_4996(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[15],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4996,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_4999,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],tmp=(C_word)a,a+=10,tmp);
if(C_truep(((C_word*)((C_word*)t0)[2])[1])){
if(C_truep((C_word)C_i_numberp(((C_word*)((C_word*)t0)[2])[1]))){
t3=t2;
f_4999(t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_5106,a[2]=t2,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[9],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  gensym");
t4=C_retrieve(lf[133]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,lf[148]);}}
else{
t3=t2;
f_4999(t3,C_SCHEME_UNDEFINED);}}

/* k5104 in k4994 in k4991 in k4988 in k4985 in k4978 in k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5106(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[24],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_5106,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_5110,a[2]=((C_word*)t0)[2],a[3]=t1,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=(C_word)C_a_i_list(&a,5,t1,((C_word*)((C_word*)t0)[3])[1],C_SCHEME_FALSE,C_SCHEME_FALSE,C_SCHEME_FALSE);
t4=(C_word)C_a_i_list(&a,1,t3);
C_trace("ChickenBridge.scm: 145  append");
t5=*((C_word*)lf[115]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t2,((C_word*)((C_word*)t0)[4])[1],t4);}

/* k5108 in k5104 in k4994 in k4991 in k4988 in k4985 in k4978 in k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5110(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[5])+1,t1);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,((C_word*)t0)[3]);
t4=((C_word*)t0)[2];
f_4999(t4,t3);}

/* k4997 in k4994 in k4991 in k4988 in k4985 in k4978 in k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_4999(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_4999,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5002,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],tmp=(C_word)a,a+=8,tmp);
t3=((C_word*)((C_word*)t0)[3])[1];
if(C_truep(t3)){
t4=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5031,a[2]=((C_word*)t0)[3],a[3]=t2,a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[2],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3238(t4,((C_word*)((C_word*)t0)[3])[1],C_fix(21248));}
else{
t4=(C_word)C_a_i_list(&a,3,lf[122],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[5])[1]);
t5=(C_word)C_a_i_list(&a,3,lf[131],((C_word*)((C_word*)t0)[7])[1],t4);
t6=C_mutate(((C_word *)((C_word*)t0)[5])+1,t5);
t7=t2;
f_5002(t7,t6);}}

/* k5029 in k4997 in k4994 in k4991 in k4988 in k4985 in k4978 in k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5031(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5031,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,3,lf[132],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[6])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[5])+1,t2);
t4=(C_word)C_a_i_list(&a,3,lf[122],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[4])[1]);
t5=(C_word)C_a_i_list(&a,3,lf[131],((C_word*)((C_word*)t0)[7])[1],t4);
t6=C_mutate(((C_word *)((C_word*)t0)[4])+1,t5);
t7=((C_word*)t0)[3];
f_5002(t7,t6);}
else{
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5049,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3238(t2,((C_word*)((C_word*)t0)[2])[1],C_fix(23552));}}

/* k5047 in k5029 in k4997 in k4994 in k4991 in k4988 in k4985 in k4978 in k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5049(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5049,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,3,lf[144],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[6])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[5])+1,t2);
t4=(C_word)C_a_i_list(&a,3,lf[122],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[4])[1]);
t5=(C_word)C_a_i_list(&a,3,lf[131],((C_word*)((C_word*)t0)[7])[1],t4);
t6=C_mutate(((C_word *)((C_word*)t0)[4])+1,t5);
t7=((C_word*)t0)[3];
f_5002(t7,t6);}
else{
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_5067,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3238(t2,((C_word*)((C_word*)t0)[2])[1],C_fix(20992));}}

/* k5065 in k5047 in k5029 in k4997 in k4994 in k4991 in k4988 in k4985 in k4978 in k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5067(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5067,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,3,lf[145],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[6])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[5])+1,t2);
t4=(C_word)C_a_i_list(&a,3,lf[146],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[4])[1]);
t5=(C_word)C_a_i_list(&a,3,lf[131],((C_word*)((C_word*)t0)[7])[1],t4);
t6=C_mutate(((C_word *)((C_word*)t0)[4])+1,t5);
t7=((C_word*)t0)[3];
f_5002(t7,t6);}
else{
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_5085,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3238(t2,((C_word*)((C_word*)t0)[2])[1],C_fix(21760));}}

/* k5083 in k5065 in k5047 in k5029 in k4997 in k4994 in k4991 in k4988 in k4985 in k4978 in k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5085(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_5085,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_a_i_list(&a,3,lf[147],((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[5])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t4=(C_word)C_a_i_list(&a,3,lf[146],((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[3])[1]);
t5=(C_word)C_a_i_list(&a,3,lf[131],((C_word*)((C_word*)t0)[6])[1],t4);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t5);
t7=((C_word*)t0)[2];
f_5002(t7,t6);}
else{
t2=((C_word*)t0)[2];
f_5002(t2,C_SCHEME_UNDEFINED);}}

/* k5000 in k4997 in k4994 in k4991 in k4988 in k4985 in k4978 in k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_5002(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_5002,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_5006,a[2]=((C_word*)t0)[6],a[3]=((C_word*)t0)[7],tmp=(C_word)a,a+=4,tmp);
t3=(C_word)C_a_i_list(&a,5,((C_word*)((C_word*)t0)[5])[1],((C_word*)((C_word*)t0)[4])[1],C_SCHEME_FALSE,((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);
t4=(C_word)C_a_i_list(&a,1,t3);
C_trace("ChickenBridge.scm: 145  append");
t5=*((C_word*)lf[115]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t2,((C_word*)((C_word*)t0)[7])[1],t4);}

/* k5004 in k5000 in k4997 in k4994 in k4991 in k4988 in k4985 in k4978 in k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_5006(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_4759(t3,t2);}

/* k4914 in k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4916(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4916,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_4920,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[8],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
t4=(C_word)C_i_cadddr(((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t3,t4,C_SCHEME_END_OF_LIST,((C_word*)t0)[2]);}

/* k4918 in k4914 in k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4920(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4920,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_4924,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[5],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  gensym");
t4=C_retrieve(lf[133]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,lf[143]);}

/* k4922 in k4918 in k4914 in k4910 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4924(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4924,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(C_word)C_a_i_list(&a,2,lf[140],((C_word*)((C_word*)t0)[6])[1]);
t4=(C_word)C_a_i_list(&a,3,lf[131],((C_word*)((C_word*)t0)[6])[1],t3);
t5=(C_word)C_a_i_list(&a,2,lf[141],((C_word*)((C_word*)t0)[6])[1]);
t6=(C_word)C_a_i_list(&a,5,((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[5])[1],C_SCHEME_FALSE,t4,t5);
t7=(C_word)C_a_i_list(&a,2,lf[142],((C_word*)((C_word*)t0)[6])[1]);
t8=(C_word)C_a_i_list(&a,3,lf[131],((C_word*)((C_word*)t0)[4])[1],t7);
t9=(C_word)C_a_i_list(&a,5,((C_word*)((C_word*)t0)[4])[1],C_SCHEME_FALSE,t8,C_SCHEME_FALSE,C_SCHEME_FALSE);
t10=(C_word)C_a_i_list(&a,2,t6,t9);
t11=C_mutate(((C_word *)((C_word*)t0)[3])+1,t10);
t12=((C_word*)t0)[2];
f_4759(t12,t11);}

/* k4817 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4819(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4819,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[10])+1,t1);
t3=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_4823,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[10],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],a[10]=((C_word*)t0)[9],tmp=(C_word)a,a+=11,tmp);
t4=(C_word)C_i_cadddr(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t3,t4,C_SCHEME_END_OF_LIST,((C_word*)t0)[3]);}

/* k4821 in k4817 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4823(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4823,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[10])+1,t1);
t3=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_4827,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[10],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 145  fifth");
t4=C_retrieve(lf[139]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)t0)[2]);}

/* k4825 in k4821 in k4817 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4827(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4827,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[9])+1,t1);
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_4830,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],a[5]=((C_word*)t0)[8],tmp=(C_word)a,a+=6,tmp);
if(C_truep(((C_word*)((C_word*)t0)[9])[1])){
t4=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_4846,a[2]=t3,a[3]=((C_word*)t0)[8],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[4],a[8]=((C_word*)t0)[9],tmp=(C_word)a,a+=9,tmp);
t5=(C_word)C_i_cadr(((C_word*)((C_word*)t0)[9])[1]);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t4,t5,C_SCHEME_END_OF_LIST,((C_word*)t0)[2]);}
else{
t4=(C_word)C_a_i_list(&a,3,lf[131],((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[3])[1]);
t5=C_mutate(((C_word *)((C_word*)t0)[5])+1,t4);
t6=t3;
f_4830(t6,t5);}}

/* k4844 in k4825 in k4821 in k4817 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4846(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4846,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_4850,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[8],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 145  gensym");
t4=C_retrieve(lf[133]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,lf[138]);}

/* k4848 in k4844 in k4825 in k4821 in k4817 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4850(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4850,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(C_word)C_a_i_list(&a,3,lf[131],((C_word*)((C_word*)t0)[8])[1],C_SCHEME_FALSE);
t4=(C_word)C_a_i_list(&a,3,lf[131],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[6])[1]);
t5=(C_word)C_a_i_list(&a,3,lf[136],t3,t4);
t6=(C_word)C_a_i_list(&a,3,lf[131],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[5])[1]);
t7=(C_word)C_a_i_list(&a,4,lf[137],((C_word*)((C_word*)t0)[8])[1],t5,t6);
t8=C_mutate(((C_word *)((C_word*)t0)[4])+1,t7);
t9=(C_word)C_a_i_list(&a,5,((C_word*)((C_word*)t0)[8])[1],C_SCHEME_TRUE,C_SCHEME_FALSE,C_SCHEME_FALSE,C_SCHEME_FALSE);
t10=(C_word)C_a_i_list(&a,1,t9);
t11=C_mutate(((C_word *)((C_word*)t0)[3])+1,t10);
t12=((C_word*)t0)[2];
f_4830(t12,t11);}

/* k4828 in k4825 in k4821 in k4817 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_4830(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4830,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_4834,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t3=(C_word)C_a_i_list(&a,5,((C_word*)((C_word*)t0)[3])[1],C_SCHEME_FALSE,((C_word*)((C_word*)t0)[2])[1],C_SCHEME_FALSE,C_SCHEME_FALSE);
t4=(C_word)C_a_i_list(&a,1,t3);
C_trace("ChickenBridge.scm: 145  append");
t5=*((C_word*)lf[115]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t2,((C_word*)((C_word*)t0)[5])[1],t4);}

/* k4832 in k4828 in k4825 in k4821 in k4817 in k4813 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4834(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_4759(t3,t2);}

/* k4767 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4769(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4769,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_4773,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  gensym");
t4=C_retrieve(lf[133]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,lf[135]);}

/* k4771 in k4767 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4773(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4773,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_4777,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  gensym");
t4=C_retrieve(lf[133]);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,lf[134]);}

/* k4775 in k4771 in k4767 in k4763 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4777(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4777,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(C_word)C_a_i_list(&a,5,((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[5])[1],C_SCHEME_FALSE,C_SCHEME_FALSE,C_SCHEME_FALSE);
t4=(C_word)C_a_i_list(&a,3,lf[122],((C_word*)((C_word*)t0)[4])[1],C_fix(1));
t5=(C_word)C_a_i_list(&a,3,lf[131],((C_word*)((C_word*)t0)[4])[1],t4);
t6=(C_word)C_a_i_list(&a,3,lf[132],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[6])[1]);
t7=(C_word)C_a_i_list(&a,5,((C_word*)((C_word*)t0)[4])[1],C_fix(0),C_SCHEME_FALSE,t5,t6);
t8=(C_word)C_a_i_list(&a,2,t3,t7);
t9=C_mutate(((C_word *)((C_word*)t0)[3])+1,t8);
t10=((C_word*)t0)[2];
f_4759(t10,t9);}

/* k4757 in sal-parse-stepping in k4748 in k4745 in k4742 in k4739 in k4736 in k4733 in k4730 in k4727 in k4724 in k4721 in k4718 in k4715 in k4712 in k4709 in k4706 in k4703 in k4700 in k4697 in k4694 in k4691 in k4688 in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_4759(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3153(((C_word*)t0)[3],C_fix(33024),((C_word*)((C_word*)t0)[2])[1],C_SCHEME_FALSE);}

/* inf->pre in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_4574(C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_4574,NULL,2,t1,t2);}
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
t14=C_set_block_item(t13,0,(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_4586,a[2]=t9,a[3]=t13,a[4]=t11,a[5]=t5,a[6]=t7,a[7]=t3,a[8]=((C_word)li102),tmp=(C_word)a,a+=9,tmp));
t15=((C_word*)t13)[1];
f_4586(t15,t1);}
else{
t12=t1;
((C_proc2)(void*)(*((C_word*)t12+1)))(2,t12,((C_word*)t3)[1]);}}

/* do859 in inf->pre in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_4586(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_4586,NULL,2,t0,t1);}
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[7])[1]))){
t2=t1;
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,((C_word*)((C_word*)t0)[6])[1]);}
else{
t2=(C_word)C_i_car(((C_word*)((C_word*)t0)[7])[1]);
t3=C_mutate(((C_word *)((C_word*)t0)[5])+1,t2);
t4=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[7])[1]);
t5=C_mutate(((C_word *)((C_word*)t0)[7])+1,t4);
t6=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_4605,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[7],a[6]=t1,a[7]=((C_word*)t0)[3],a[8]=((C_word*)t0)[4],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 145  is-op?");
f_4553(t6,((C_word*)((C_word*)t0)[5])[1]);}}

/* k4603 in do859 in inf->pre in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4605(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4605,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_4608,a[2]=((C_word*)t0)[6],a[3]=((C_word*)t0)[7],tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_numberp(((C_word*)((C_word*)t0)[8])[1]))){
t4=C_SCHEME_UNDEFINED;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_set_block_item(t5,0,(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_4623,a[2]=((C_word*)t0)[8],a[3]=t5,a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[5],a[8]=((C_word)li101),tmp=(C_word)a,a+=9,tmp));
t7=((C_word*)t5)[1];
f_4623(t7,t3,C_SCHEME_FALSE,C_SCHEME_TRUE,C_SCHEME_END_OF_LIST);}
else{
t4=C_mutate(((C_word *)((C_word*)t0)[3])+1,((C_word*)((C_word*)t0)[2])[1]);
t5=t3;
f_4608(2,t5,t4);}}

/* do861 in k4603 in do859 in inf->pre in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_4623(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
C_save_and_reclaim((void*)trf_4623,NULL,5,t0,t1,t2,t3,t4);}
t5=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t8=(C_word)C_i_nullp(((C_word*)((C_word*)t0)[7])[1]);
t9=(C_truep(t8)?t8:(C_word)C_i_not(((C_word*)t6)[1]));
if(C_truep(t9)){
t10=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_4637,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],tmp=(C_word)a,a+=6,tmp);
t11=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4651,a[2]=t10,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  reverse");
t12=*((C_word*)lf[119]+1);
((C_proc3)C_retrieve_proc(t12))(3,t12,t11,((C_word*)t7)[1]);}
else{
t10=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_4655,a[2]=((C_word*)t0)[7],a[3]=((C_word*)t0)[2],a[4]=t7,a[5]=t6,a[6]=t1,a[7]=((C_word*)t0)[3],a[8]=t5,tmp=(C_word)a,a+=9,tmp);
t11=(C_word)C_i_car(((C_word*)((C_word*)t0)[7])[1]);
C_trace("ChickenBridge.scm: 145  is-op?");
f_4553(t10,t11);}}

/* k4653 in do861 in k4603 in do859 in inf->pre in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4655(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4655,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_4658,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[8],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
t4=(C_truep(((C_word*)((C_word*)t0)[8])[1])?(C_word)C_i_less_or_equalp(((C_word*)((C_word*)t0)[8])[1],((C_word*)((C_word*)t0)[3])[1]):C_SCHEME_FALSE);
if(C_truep(t4)){
t5=C_set_block_item(((C_word*)t0)[5],0,C_SCHEME_FALSE);
t6=t3;
f_4658(t6,t5);}
else{
t5=(C_word)C_i_car(((C_word*)((C_word*)t0)[2])[1]);
t6=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[2])[1]);
t7=C_mutate(((C_word *)((C_word*)t0)[2])+1,t6);
t8=(C_word)C_a_i_cons(&a,2,t5,((C_word*)((C_word*)t0)[4])[1]);
t9=C_mutate(((C_word *)((C_word*)t0)[4])+1,t8);
t10=t3;
f_4658(t10,t9);}}

/* k4656 in k4653 in do861 in k4603 in do859 in inf->pre in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_4658(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[6])[1];
f_4623(t2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k4649 in do861 in k4603 in do859 in inf->pre in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4651(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  inf->pre");
f_4574(((C_word*)t0)[2],t1);}

/* k4635 in do861 in k4603 in do859 in inf->pre in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4637(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[18],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4637,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[5])+1,t1);
t3=(C_truep(((C_word*)((C_word*)t0)[4])[1])?(C_word)C_a_i_list(&a,3,((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[5])[1]):(C_word)C_a_i_list(&a,3,((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[5])[1],C_SCHEME_FALSE));
t4=C_mutate(((C_word *)((C_word*)t0)[4])+1,t3);
t5=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,t4);}

/* k4606 in k4603 in do859 in inf->pre in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4608(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[3])[1];
f_4586(t2,((C_word*)t0)[2]);}

/* is-op? in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_4553(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4553,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_4560,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  token-unit?");
f_3222(t3,t2);}

/* k4558 in is-op? in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4560(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4560,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4563,a[2]=((C_word*)t0)[3],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-type");
f_3174(t2,((C_word*)t0)[2]);}
else{
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}}

/* k4561 in k4558 in is-op? in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4563(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4563,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_4569,a[2]=t1,a[3]=((C_word*)t0)[2],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  SalOpType?");
f_4330(t2,t1);}

/* k4567 in k4561 in k4558 in is-op? in k4549 in k4546 in k4543 in k4540 in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4569(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4569,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[3];
t3=((C_word*)t0)[2];
t4=t2;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_a_i_bitwise_and(&a,2,t3,C_fix(255)));}
else{
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}}

/* remove-token-type in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_4488(C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)trf_4488,NULL,3,t1,t2,t3);}
t4=(C_word)C_a_i_list(&a,1,C_SCHEME_TRUE);
t5=t4;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=C_SCHEME_UNDEFINED;
t8=(*a=C_VECTOR_TYPE|1,a[1]=t7,tmp=(C_word)a,a+=2,tmp);
t9=C_set_block_item(t8,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_4497,a[2]=t3,a[3]=t6,a[4]=t8,a[5]=t4,a[6]=((C_word)li98),tmp=(C_word)a,a+=7,tmp));
t10=((C_word*)t8)[1];
f_4497(t10,t1,t2);}

/* do825 in remove-token-type in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_4497(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4497,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_i_cdr(((C_word*)t0)[5]));}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_4510,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_4520,a[2]=((C_word*)t0)[3],a[3]=t2,a[4]=t3,tmp=(C_word)a,a+=5,tmp);
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  token-unit-type=?");
f_3238(t4,t5,((C_word*)t0)[2]);}}

/* k4518 in do825 in remove-token-type in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4520(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_4520,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
f_4510(t2,C_SCHEME_FALSE);}
else{
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=(C_word)C_a_i_list(&a,1,t2);
t4=(C_word)C_i_set_cdr(((C_word*)((C_word*)t0)[2])[1],t3);
t5=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[2])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[2])+1,t5);
t7=((C_word*)t0)[4];
f_4510(t7,t6);}}

/* k4508 in do825 in remove-token-type in k4484 in k4481 in k4478 in k4475 in k4472 in k4469 in k4466 in k4463 in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_4510(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_4497(t3,((C_word*)t0)[2],t2);}

/* SalType=? in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_4444(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4444,NULL,3,t1,t2,t3);}
t4=(C_word)C_a_i_arithmetic_shift(&a,2,t2,C_fix(-8));
t5=(C_word)C_a_i_arithmetic_shift(&a,2,t3,C_fix(-8));
t6=t1;
((C_proc2)(void*)(*((C_word*)t6+1)))(2,t6,(C_word)C_i_nequalp(t4,t5));}

/* SalRuleType? in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_4432(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4432,NULL,2,t1,t2);}
t3=(C_word)C_i_lessp(C_fix(25600),t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_truep(t3)?(C_word)C_i_lessp(t2,C_fix(38400)):C_SCHEME_FALSE));}

/* SalOpType? in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_4330(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4330,NULL,2,t1,t2);}
t3=(C_word)C_i_lessp(C_fix(6656),t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_truep(t3)?(C_word)C_i_lessp(t2,C_fix(11520)):C_SCHEME_FALSE));}

/* SalTokenType? in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_4282(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_4282,NULL,2,t1,t2);}
t3=(C_word)C_i_lessp(C_fix(0),t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_truep(t3)?(C_word)C_i_lessp(t2,C_fix(25600)):C_SCHEME_FALSE));}

/* parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3663(C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
C_word tmp;
C_word t8;
C_word t9;
C_word t10;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3663,NULL,7,t1,t2,t3,t4,t5,t6,t7);}
t8=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t9=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_3667,a[2]=t4,a[3]=t7,a[4]=t6,a[5]=t5,a[6]=t8,a[7]=t1,a[8]=t2,tmp=(C_word)a,a+=9,tmp);
if(C_truep(t6)){
C_trace("ChickenBridge.scm: 145  printf");
t10=C_retrieve(lf[125]);
((C_proc6)C_retrieve_proc(t10))(6,t10,t9,lf[126],t5,t2,((C_word*)t8)[1]);}
else{
t10=t9;
f_3667(2,t10,C_SCHEME_UNDEFINED);}}

/* k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3667(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3667,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_3670,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 145  null-tokens?");
f_2845(t2,((C_word*)((C_word*)t0)[6])[1]);}

/* k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3670(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[18],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3670,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_3673,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
if(C_truep(t1)){
t3=t2;
f_3673(t3,t1);}
else{
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4088,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4092,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_4096,a[2]=t4,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  first-token");
f_2833(t5,((C_word*)((C_word*)t0)[6])[1]);}}

/* k4094 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4096(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  token-position");
f_2792(((C_word*)t0)[2],t1);}

/* k4090 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4092(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  max");
t2=*((C_word*)lf[124]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[2],C_retrieve2(lf[116],"*maxtokpos*"),t1);}

/* k4086 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4088(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(&lf[116],t1);
t3=((C_word*)t0)[2];
f_3673(t3,t2);}

/* k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3673(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3673,NULL,2,t0,t1);}
t2=((C_word*)t0)[8];
if(C_truep((C_word)C_i_numberp(t2))){
t3=((C_word*)t0)[8];
t4=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_3688,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=t3,a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 145  SalTokenType?");
f_4282(t4,t3);}
else{
t3=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_3796,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[2],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 145  pattern-clause?");
f_2984(t3,((C_word*)t0)[8]);}}

/* k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3796(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[13],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3796,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_3802,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
t3=((C_word*)t0)[2];
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3029,a[2]=t2,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  pattern-clause?");
f_2984(t4,t3);}
else{
C_trace("ChickenBridge.scm: 145  error");
t2=*((C_word*)lf[27]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[6],lf[123],((C_word*)t0)[2]);}}

/* k3027 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3029(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=((C_word*)t0)[2];
f_3802(t3,(C_word)C_eqp(t2,lf[103]));}
else{
t2=((C_word*)t0)[2];
f_3802(t2,C_SCHEME_FALSE);}}

/* k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3802(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_3802,NULL,2,t0,t1);}
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
t11=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_3811,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=t10,a[7]=((C_word*)t0)[7],a[8]=t6,a[9]=t8,a[10]=t4,a[11]=((C_word*)t0)[6],tmp=(C_word)a,a+=12,tmp);
C_trace("ChickenBridge.scm: 145  pattern-nsubs");
f_3002(t11,((C_word*)t0)[2]);}
else{
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_3890,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[6],tmp=(C_word)a,a+=8,tmp);
t4=((C_word*)t0)[2];
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3045,a[2]=t3,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  pattern-clause?");
f_2984(t5,t4);}}

/* k3043 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3045(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=((C_word*)t0)[2];
f_3890(t3,(C_word)C_eqp(t2,lf[104]));}
else{
t2=((C_word*)t0)[2];
f_3890(t2,C_SCHEME_FALSE);}}

/* k3888 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3890(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_3890,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=C_SCHEME_FALSE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_SCHEME_FALSE;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_SCHEME_END_OF_LIST;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_3896,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t7,a[8]=t5,a[9]=((C_word*)t0)[7],a[10]=t3,tmp=(C_word)a,a+=11,tmp);
C_trace("ChickenBridge.scm: 145  pattern-nsubs");
f_3002(t8,((C_word*)t0)[2]);}
else{
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_3960,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[2],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[6],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 145  pattern-zero-or-more?");
f_3070(t2,((C_word*)t0)[2]);}}

/* k3958 in k3888 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3960(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3960,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_3963,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
if(C_truep(t1)){
t3=t2;
f_3963(t3,t1);}
else{
t3=((C_word*)t0)[5];
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3061,a[2]=t2,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  pattern-clause?");
f_2984(t4,t3);}}

/* k3059 in k3958 in k3888 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3061(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=((C_word*)t0)[2];
f_3963(t3,(C_word)C_eqp(t2,lf[122]));}
else{
t2=((C_word*)t0)[2];
f_3963(t2,C_SCHEME_FALSE);}}

/* k3961 in k3958 in k3888 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3963(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_3963,NULL,2,t0,t1);}
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
t12=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_3969,a[2]=((C_word*)t0)[5],a[3]=t11,a[4]=((C_word*)t0)[7],a[5]=t9,a[6]=t3,a[7]=((C_word*)t0)[6],tmp=(C_word)a,a+=8,tmp);
t13=C_SCHEME_UNDEFINED;
t14=(*a=C_VECTOR_TYPE|1,a[1]=t13,tmp=(C_word)a,a+=2,tmp);
t15=C_set_block_item(t14,0,(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_3992,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=t5,a[7]=t11,a[8]=t7,a[9]=((C_word*)t0)[7],a[10]=t9,a[11]=t14,a[12]=t3,a[13]=((C_word)li90),tmp=(C_word)a,a+=14,tmp));
t16=((C_word*)t14)[1];
f_3992(t16,t12);}
else{
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_4041,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[6],tmp=(C_word)a,a+=8,tmp);
t3=((C_word*)t0)[5];
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3093,a[2]=t2,a[3]=t3,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  pattern-clause?");
f_2984(t4,t3);}}

/* k3091 in k3961 in k3958 in k3888 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3093(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=((C_word*)t0)[2];
f_4041(t3,(C_word)C_eqp(t2,lf[121]));}
else{
t2=((C_word*)t0)[2];
f_4041(t2,C_SCHEME_FALSE);}}

/* k4039 in k3961 in k3958 in k3888 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_4041(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_4041,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=C_SCHEME_FALSE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_SCHEME_END_OF_LIST;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_SCHEME_END_OF_LIST;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_4050,a[2]=((C_word*)t0)[6],a[3]=t7,a[4]=t5,a[5]=((C_word*)t0)[7],a[6]=t3,tmp=(C_word)a,a+=7,tmp);
t9=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_4061,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[5],a[7]=((C_word)li91),tmp=(C_word)a,a+=8,tmp);
t10=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_4067,a[2]=t7,a[3]=t5,a[4]=t3,a[5]=((C_word)li92),tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  call-with-values");
C_call_with_values(4,0,t8,t9,t10);}
else{
t2=((C_word*)t0)[5];
t3=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  error");
t4=*((C_word*)lf[27]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,((C_word*)t0)[7],lf[120],t3);}}

/* a4066 in k4039 in k3961 in k3958 in k3888 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4067(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_4067,5,t0,t1,t2,t3,t4);}
t5=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t3);
t7=C_mutate(((C_word *)((C_word*)t0)[2])+1,t4);
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,t7);}

/* a4060 in k4039 in k3961 in k3958 in k3888 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4061(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4061,2,t0,t1);}
C_trace("ChickenBridge.scm: 145  parser");
f_3663(t1,((C_word*)t0)[6],((C_word*)((C_word*)t0)[5])[1],C_SCHEME_TRUE,((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k4048 in k4039 in k3961 in k3958 in k3888 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4050(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(C_truep(((C_word*)((C_word*)t0)[6])[1])){
C_trace("ChickenBridge.scm: 145  values");
C_values(5,0,((C_word*)t0)[5],((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1]);}
else{
C_trace("ChickenBridge.scm: 145  values");
C_values(5,0,((C_word*)t0)[5],C_SCHEME_TRUE,C_SCHEME_FALSE,((C_word*)((C_word*)t0)[2])[1]);}}

/* do562 in k3961 in k3958 in k3888 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3992(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[14],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3992,NULL,2,t0,t1);}
t2=(C_word)C_i_not(((C_word*)((C_word*)t0)[12])[1]);
t3=(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_4002,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],a[10]=((C_word*)t0)[10],a[11]=((C_word*)t0)[12],a[12]=((C_word*)t0)[11],a[13]=t1,tmp=(C_word)a,a+=14,tmp);
if(C_truep(t2)){
t4=t3;
f_4002(2,t4,t2);}
else{
C_trace("ChickenBridge.scm: 145  null-tokens?");
f_2845(t3,((C_word*)((C_word*)t0)[8])[1]);}}

/* k4000 in do562 in k3961 in k3958 in k3888 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4002(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[24],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4002,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[13];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}
else{
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_4005,a[2]=((C_word*)t0)[6],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[8],a[5]=((C_word*)t0)[9],a[6]=((C_word*)t0)[10],a[7]=((C_word*)t0)[11],a[8]=((C_word*)t0)[13],a[9]=((C_word*)t0)[12],tmp=(C_word)a,a+=10,tmp);
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_4022,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[8],a[6]=((C_word*)t0)[5],a[7]=((C_word)li88),tmp=(C_word)a,a+=8,tmp);
t4=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_4028,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[11],a[5]=((C_word)li89),tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  call-with-values");
C_call_with_values(4,0,t2,t3,t4);}}

/* a4027 in k4000 in do562 in k3961 in k3958 in k3888 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4028(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_4028,5,t0,t1,t2,t3,t4);}
t5=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t3);
t7=C_mutate(((C_word *)((C_word*)t0)[2])+1,t4);
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,t7);}

/* a4021 in k4000 in do562 in k3961 in k3958 in k3888 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4022(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4022,2,t0,t1);}
C_trace("ChickenBridge.scm: 145  parser");
f_3663(t1,((C_word*)t0)[6],((C_word*)((C_word*)t0)[5])[1],C_SCHEME_TRUE,((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k4003 in k4000 in do562 in k3961 in k3958 in k3888 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4005(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4005,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_4008,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[9],tmp=(C_word)a,a+=4,tmp);
if(C_truep(((C_word*)((C_word*)t0)[7])[1])){
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_4015,a[2]=t2,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  append");
t4=*((C_word*)lf[115]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t3,((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[2])[1]);}
else{
t3=t2;
f_4008(t3,C_SCHEME_UNDEFINED);}}

/* k4013 in k4003 in k4000 in do562 in k3961 in k3958 in k3888 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_4015(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_4015,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=C_mutate(((C_word *)((C_word*)t0)[5])+1,((C_word*)((C_word*)t0)[4])[1]);
t4=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[3])[1],C_fix(1));
t5=C_mutate(((C_word *)((C_word*)t0)[3])+1,t4);
t6=((C_word*)t0)[2];
f_4008(t6,t5);}

/* k4006 in k4003 in k4000 in do562 in k3961 in k3958 in k3888 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_4008(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[3])[1];
f_3992(t2,((C_word*)t0)[2]);}

/* k3967 in k3961 in k3958 in k3888 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3969(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3969,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3972,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],tmp=(C_word)a,a+=6,tmp);
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3978,a[2]=((C_word*)t0)[5],a[3]=t2,a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[3],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  pattern-zero-or-more?");
f_3070(t3,((C_word*)t0)[2]);}

/* k3976 in k3967 in k3961 in k3958 in k3888 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3978(C_word c,C_word t0,C_word t1){
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
f_3972(t4,t3);}
else{
t3=C_set_block_item(((C_word*)t0)[4],0,C_SCHEME_FALSE);
t4=C_set_block_item(((C_word*)t0)[2],0,C_SCHEME_END_OF_LIST);
t5=((C_word*)t0)[3];
f_3972(t5,t4);}}

/* k3970 in k3967 in k3961 in k3958 in k3888 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3972(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  values");
C_values(5,0,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k3894 in k3888 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3896(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3896,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_3899,a[2]=((C_word*)t0)[6],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[8],a[5]=((C_word*)t0)[9],a[6]=((C_word*)t0)[10],tmp=(C_word)a,a+=7,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_3914,a[2]=((C_word*)t0)[7],a[3]=((C_word*)t0)[8],a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[5],a[9]=t4,a[10]=t1,a[11]=((C_word*)t0)[10],a[12]=((C_word)li87),tmp=(C_word)a,a+=13,tmp));
t6=((C_word*)t4)[1];
f_3914(t6,t2,C_fix(0));}

/* do542 in k3894 in k3888 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3914(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_3914,NULL,3,t0,t1,t2);}
t3=((C_word*)((C_word*)t0)[11])[1];
t4=(C_truep(t3)?t3:(C_word)C_i_nequalp(t2,((C_word*)t0)[10]));
if(C_truep(t4)){
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,C_SCHEME_FALSE);}
else{
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3924,a[2]=t1,a[3]=((C_word*)t0)[9],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t6=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_3933,a[2]=t2,a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],a[8]=((C_word)li85),tmp=(C_word)a,a+=9,tmp);
t7=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3947,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[11],a[5]=((C_word)li86),tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  call-with-values");
C_call_with_values(4,0,t5,t6,t7);}}

/* a3946 in do542 in k3894 in k3888 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3947(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_3947,5,t0,t1,t2,t3,t4);}
t5=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t3);
t7=C_mutate(((C_word *)((C_word*)t0)[2])+1,t4);
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,t7);}

/* a3932 in do542 in k3894 in k3888 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3933(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[7],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3933,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_3941,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=t1,a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  pattern-sub");
f_3012(t2,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k3939 in a3932 in do542 in k3894 in k3888 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3941(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3941,2,t0,t1);}
t2=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[6],C_fix(1));
C_trace("ChickenBridge.scm: 145  parser");
f_3663(((C_word*)t0)[5],t1,((C_word*)((C_word*)t0)[4])[1],C_SCHEME_FALSE,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k3922 in do542 in k3894 in k3888 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3924(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3924,2,t0,t1);}
t2=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[4],C_fix(1));
t3=((C_word*)((C_word*)t0)[3])[1];
f_3914(t3,((C_word*)t0)[2],t2);}

/* k3897 in k3894 in k3888 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3899(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(C_truep(((C_word*)((C_word*)t0)[6])[1])){
C_trace("ChickenBridge.scm: 145  values");
C_values(5,0,((C_word*)t0)[5],((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1]);}
else{
C_trace("ChickenBridge.scm: 145  values");
C_values(5,0,((C_word*)t0)[5],C_SCHEME_FALSE,C_SCHEME_END_OF_LIST,((C_word*)((C_word*)t0)[2])[1]);}}

/* k3809 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3811(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_3811,2,t0,t1);}
t2=C_SCHEME_FALSE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_3814,a[2]=((C_word*)t0)[7],a[3]=t3,a[4]=((C_word*)t0)[8],a[5]=((C_word*)t0)[9],a[6]=((C_word*)t0)[10],a[7]=((C_word*)t0)[11],tmp=(C_word)a,a+=8,tmp);
t5=C_SCHEME_UNDEFINED;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=C_set_block_item(t6,0,(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_3833,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[8],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[9],a[8]=((C_word*)t0)[6],a[9]=((C_word*)t0)[10],a[10]=t6,a[11]=t3,a[12]=t1,a[13]=((C_word)li84),tmp=(C_word)a,a+=14,tmp));
t8=((C_word*)t6)[1];
f_3833(t8,t4,C_fix(0));}

/* do520 in k3809 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3833(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_3833,NULL,3,t0,t1,t2);}
t3=(C_word)C_i_nequalp(t2,((C_word*)t0)[12]);
t4=(C_truep(t3)?t3:((C_word*)((C_word*)t0)[11])[1]);
if(C_truep(t4)){
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,C_SCHEME_FALSE);}
else{
t5=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_3846,a[2]=((C_word*)t0)[11],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[8],a[5]=((C_word*)t0)[9],a[6]=t1,a[7]=((C_word*)t0)[10],a[8]=t2,tmp=(C_word)a,a+=9,tmp);
t6=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_3866,a[2]=t2,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word)li82),tmp=(C_word)a,a+=9,tmp);
t7=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3880,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[8],a[4]=((C_word*)t0)[9],a[5]=((C_word)li83),tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  call-with-values");
C_call_with_values(4,0,t5,t6,t7);}}

/* a3879 in do520 in k3809 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3880(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_3880,5,t0,t1,t2,t3,t4);}
t5=C_mutate(((C_word *)((C_word*)t0)[4])+1,t2);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t3);
t7=C_mutate(((C_word *)((C_word*)t0)[2])+1,t4);
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,t7);}

/* a3865 in do520 in k3809 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3866(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[7],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3866,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_3874,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=t1,a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  pattern-sub");
f_3012(t2,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k3872 in a3865 in do520 in k3809 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3874(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3874,2,t0,t1);}
t2=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[6],C_fix(1));
C_trace("ChickenBridge.scm: 145  parser");
f_3663(((C_word*)t0)[5],t1,((C_word*)((C_word*)t0)[4])[1],C_SCHEME_FALSE,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k3844 in do520 in k3809 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3846(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_3846,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3849,a[2]=((C_word*)t0)[6],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[8],tmp=(C_word)a,a+=5,tmp);
t3=((C_word*)((C_word*)t0)[5])[1];
if(C_truep(t3)){
t4=(C_word)C_a_i_cons(&a,2,((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1]);
t5=C_mutate(((C_word *)((C_word*)t0)[3])+1,t4);
t6=t2;
f_3849(t6,t5);}
else{
t4=C_set_block_item(((C_word*)t0)[2],0,C_SCHEME_TRUE);
t5=t2;
f_3849(t5,t4);}}

/* k3847 in k3844 in do520 in k3809 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3849(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3849,NULL,2,t0,t1);}
t2=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[4],C_fix(1));
t3=((C_word*)((C_word*)t0)[3])[1];
f_3833(t3,((C_word*)t0)[2],t2);}

/* k3812 in k3809 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3814(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_3814,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3817,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],tmp=(C_word)a,a+=6,tmp);
if(C_truep(((C_word*)((C_word*)t0)[3])[1])){
t3=C_set_block_item(((C_word*)t0)[6],0,C_SCHEME_FALSE);
t4=C_set_block_item(((C_word*)t0)[5],0,C_SCHEME_END_OF_LIST);
t5=C_mutate(((C_word *)((C_word*)t0)[4])+1,((C_word*)((C_word*)t0)[2])[1]);
t6=t2;
f_3817(t6,t5);}
else{
t3=C_set_block_item(((C_word*)t0)[6],0,C_SCHEME_TRUE);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3831,a[2]=t2,a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  reverse");
t5=*((C_word*)lf[119]+1);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,((C_word*)((C_word*)t0)[5])[1]);}}

/* k3829 in k3812 in k3809 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3831(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_3817(t3,t2);}

/* k3815 in k3812 in k3809 in k3800 in k3794 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3817(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  values");
C_values(5,0,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k3686 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3688(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[13],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3688,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3694,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  null-tokens?");
f_2845(t2,((C_word*)((C_word*)t0)[6])[1]);}
else{
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_3746,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[4],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 145  SalRuleType?");
f_4432(t2,((C_word*)t0)[5]);}}

/* k3744 in k3686 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3746(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3746,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_3749,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 145  get-rule");
f_2960(t2,((C_word*)t0)[2],C_SCHEME_END_OF_LIST);}
else{
C_trace("ChickenBridge.scm: 145  error");
t2=*((C_word*)lf[27]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[3],lf[118],((C_word*)t0)[2]);}}

/* k3747 in k3744 in k3686 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3749(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_3749,2,t0,t1);}
t2=t1;
t3=(C_word)C_i_check_structure(t2,lf[70]);
t4=(C_word)C_i_block_ref(t2,C_fix(3));
t5=t1;
t6=(C_word)C_i_check_structure(t5,lf[70]);
t7=(C_word)C_i_block_ref(t5,C_fix(4));
t8=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_3760,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=t4,a[6]=((C_word*)t0)[6],a[7]=((C_word)li80),tmp=(C_word)a,a+=8,tmp);
t9=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3770,a[2]=((C_word*)t0)[3],a[3]=t7,a[4]=((C_word)li81),tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  call-with-values");
C_call_with_values(4,0,((C_word*)t0)[2],t8,t9);}

/* a3769 in k3747 in k3744 in k3686 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3770(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_3770,5,t0,t1,t2,t3,t4);}
if(C_truep(t2)){
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3781,a[2]=t4,a[3]=t2,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
if(C_truep(((C_word*)t0)[3])){
C_trace("ChickenBridge.scm: 145  func");
t6=((C_word*)t0)[3];
((C_proc4)C_retrieve_proc(t6))(4,t6,t5,t3,((C_word*)t0)[2]);}
else{
t6=t5;
f_3781(2,t6,t3);}}
else{
C_trace("ChickenBridge.scm: 145  values");
C_values(5,0,t1,C_SCHEME_FALSE,C_SCHEME_FALSE,t4);}}

/* k3779 in a3769 in k3747 in k3744 in k3686 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3781(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  values");
C_values(5,0,((C_word*)t0)[4],((C_word*)t0)[3],t1,((C_word*)t0)[2]);}

/* a3759 in k3747 in k3744 in k3686 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3760(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3760,2,t0,t1);}
t2=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[6],C_fix(1));
C_trace("ChickenBridge.scm: 145  parser");
f_3663(t1,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],C_SCHEME_FALSE,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k3692 in k3686 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3694(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3694,2,t0,t1);}
if(C_truep(t1)){
C_trace("ChickenBridge.scm: 145  values");
C_values(5,0,((C_word*)t0)[4],C_SCHEME_FALSE,C_SCHEME_FALSE,C_SCHEME_END_OF_LIST);}
else{
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3704,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  first-token");
f_2833(t2,((C_word*)((C_word*)t0)[3])[1]);}}

/* k3702 in k3692 in k3686 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3704(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3704,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3710,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3740,a[2]=((C_word*)t0)[2],a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  token-type");
f_2756(t3,t1);}

/* k3738 in k3702 in k3692 in k3686 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3740(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4444(((C_word*)t0)[3],t1,((C_word*)t0)[2]);}

/* k3708 in k3702 in k3692 in k3686 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3710(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3710,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3717,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3725,a[2]=((C_word*)t0)[2],a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  token-type");
f_2756(t3,((C_word*)t0)[2]);}
else{
C_trace("ChickenBridge.scm: 145  values");
C_values(5,0,((C_word*)t0)[3],C_SCHEME_FALSE,C_SCHEME_FALSE,((C_word*)((C_word*)t0)[4])[1]);}}

/* k3723 in k3708 in k3702 in k3692 in k3686 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3725(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3725,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3729,a[2]=((C_word*)t0)[2],a[3]=t1,a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  token-string");
f_2774(t2,((C_word*)t0)[2]);}

/* k3727 in k3723 in k3708 in k3702 in k3692 in k3686 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3729(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3729,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3733,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  token-position");
f_2792(t2,((C_word*)t0)[2]);}

/* k3731 in k3727 in k3723 in k3708 in k3702 in k3692 in k3686 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3733(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3153(((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k3715 in k3708 in k3702 in k3692 in k3686 in k3671 in k3668 in k3665 in parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3717(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
t2=((C_word*)((C_word*)t0)[3])[1];
t3=(C_word)C_i_cdr(t2);
C_trace("ChickenBridge.scm: 145  values");
C_values(5,0,((C_word*)t0)[2],C_SCHEME_TRUE,t1,t3);}

/* simple-unit-emitter in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3559(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3559,NULL,2,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3561,a[2]=t2,a[3]=((C_word)li78),tmp=(C_word)a,a+=4,tmp));}

/* f_3561 in simple-unit-emitter in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3561(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[9],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_3561,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3565,a[2]=((C_word*)t0)[2],a[3]=t1,a[4]=t4,a[5]=t3,tmp=(C_word)a,a+=6,tmp);
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3609,a[2]=t5,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3192(t6,t2);}

/* k3607 */
static void C_ccall f_3609(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  append");
t2=*((C_word*)lf[115]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[2],t1,C_SCHEME_END_OF_LIST);}

/* k3563 */
static void C_ccall f_3565(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_3565,2,t0,t1);}
t2=t1;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=((C_word*)t3)[1];
t5=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_3568,a[2]=t3,a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=t4,tmp=(C_word)a,a+=7,tmp);
if(C_truep(((C_word*)t0)[2])){
t6=(C_word)C_i_set_car(((C_word*)t3)[1],((C_word*)t0)[2]);
t7=(C_word)C_i_cdr(((C_word*)t3)[1]);
t8=C_set_block_item(t3,0,t7);
t9=t5;
f_3568(t9,t8);}
else{
t6=t5;
f_3568(t6,C_SCHEME_UNDEFINED);}}

/* k3566 in k3563 */
static void C_fcall f_3568(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3568,NULL,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_3573,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=t3,a[5]=((C_word*)t0)[6],a[6]=((C_word)li77),tmp=(C_word)a,a+=7,tmp));
t5=((C_word*)t3)[1];
f_3573(t5,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1]);}

/* do477 in k3566 in k3563 */
static void C_fcall f_3573(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3573,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,((C_word*)t0)[5]);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3594,a[2]=t1,a[3]=((C_word*)t0)[4],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t3,t4,((C_word*)t0)[3],((C_word*)t0)[2]);}}

/* k3592 in do477 in k3566 in k3563 */
static void C_ccall f_3594(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
t2=(C_word)C_i_set_car(((C_word*)t0)[4],t1);
t3=(C_word)C_i_cdr(((C_word*)t0)[4]);
t4=((C_word*)((C_word*)t0)[3])[1];
f_3573(t4,((C_word*)t0)[2],t3);}

/* simple-unit-parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3551(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3551,NULL,2,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3553,a[2]=t2,a[3]=((C_word)li75),tmp=(C_word)a,a+=4,tmp));}

/* f_3553 in simple-unit-parser in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3553(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word *a;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_3553,4,t0,t1,t2,t3);}
C_trace("ChickenBridge.scm: 145  make-parse-unit");
f_3153(t1,((C_word*)t0)[2],t2,C_SCHEME_FALSE);}

/* emit-list in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3343(C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3343,NULL,4,t1,t2,t3,t4);}
if(C_truep((C_word)C_i_nullp(t2))){
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,C_SCHEME_END_OF_LIST);}
else{
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3360,a[2]=t4,a[3]=t3,a[4]=t2,a[5]=t1,tmp=(C_word)a,a+=6,tmp);
t6=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 145  emit");
f_3310(t5,t6,t3,t4);}}

/* k3358 in emit-list in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3360(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3360,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3364,a[2]=t1,a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t3=(C_word)C_i_cdr(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 145  emit-list");
f_3343(t2,t3,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k3362 in k3358 in emit-list in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3364(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3364,2,t0,t1);}
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[2],t1));}

/* emit in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3310(C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3310,NULL,4,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3317,a[2]=t4,a[3]=t3,a[4]=t2,a[5]=t1,tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  token-unit?");
f_3222(t5,t2);}

/* k3315 in emit in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3317(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_3317,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[5];
t3=((C_word*)t0)[4];
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3388,a[2]=t3,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-type");
f_3174(t4,t3);}
else{
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3326,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
t3=((C_word*)t0)[4];
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3261,a[2]=t3,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit?");
f_3159(t4,t3);}}

/* k3259 in k3315 in emit in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3261(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3261,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3268,a[2]=((C_word*)t0)[3],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-type");
f_3174(t2,((C_word*)t0)[2]);}
else{
t2=((C_word*)t0)[3];
f_3326(2,t2,C_SCHEME_FALSE);}}

/* k3266 in k3259 in k3315 in emit in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3268(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  SalRuleType?");
f_4432(((C_word*)t0)[2],t1);}

/* k3324 in k3315 in emit in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3326(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_3326,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[5];
t3=((C_word*)t0)[4];
t4=((C_word*)t0)[3];
t5=((C_word*)t0)[2];
t6=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3526,a[2]=t5,a[3]=t4,a[4]=t3,a[5]=t2,tmp=(C_word)a,a+=6,tmp);
t7=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3549,a[2]=t6,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-type");
f_3174(t7,t3);}
else{
if(C_truep((C_word)C_i_listp(((C_word*)t0)[4]))){
C_trace("ChickenBridge.scm: 145  emit-list");
f_3343(((C_word*)t0)[5],((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2]);}
else{
C_trace("ChickenBridge.scm: 145  error");
t2=*((C_word*)lf[27]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[5],lf[111],((C_word*)t0)[4]);}}}

/* k3547 in k3324 in k3315 in emit in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3549(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  get-rule");
f_2960(((C_word*)t0)[2],t1,C_SCHEME_END_OF_LIST);}

/* k3524 in k3324 in k3315 in emit in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3526(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3526,2,t0,t1);}
t2=(C_word)C_i_check_structure(t1,lf[70]);
t3=(C_word)C_i_block_ref(t1,C_fix(5));
if(C_truep(t3)){
C_trace("ChickenBridge.scm: 145  meth");
t4=t3;
((C_proc5)C_retrieve_proc(t4))(5,t4,((C_word*)t0)[5],((C_word*)t0)[4],((C_word*)t0)[3],((C_word*)t0)[2]);}
else{
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3542,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[5],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3192(t4,((C_word*)t0)[4]);}}

/* k3540 in k3524 in k3324 in k3315 in emit in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3542(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  emit");
f_3310(((C_word*)t0)[4],t1,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* k3386 in k3315 in emit in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3388(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3388,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3391,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-parsed");
f_3192(t2,((C_word*)t0)[2]);}

/* k3389 in k3386 in k3315 in emit in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3391(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_3391,2,t0,t1);}
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
t8=*((C_word*)lf[100]+1);
((C_proc3)C_retrieve_proc(t8))(3,t8,((C_word*)t0)[3],t1);}
else{
t8=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3415,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[4],a[4]=t1,a[5]=((C_word*)t0)[3],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  SalOpType?");
f_4330(t8,((C_word*)t0)[4]);}}}

/* k3413 in k3389 in k3386 in k3315 in emit in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3415(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_3415,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3421,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4444(t2,((C_word*)t0)[3],C_fix(7941));}
else{
t2=((C_word*)t0)[3];
t3=(C_word)C_i_lessp(C_fix(4096),t2);
t4=(C_truep(t3)?(C_word)C_i_lessp(t2,C_fix(4864)):C_SCHEME_FALSE);
if(C_truep(t4)){
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3466,a[2]=((C_word*)t0)[5],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4444(t5,((C_word*)t0)[3],C_fix(4352));}
else{
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3472,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4444(t5,((C_word*)t0)[3],C_fix(2304));}}}

/* k3470 in k3413 in k3389 in k3386 in k3315 in emit in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3472(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3472,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[5];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,((C_word*)t0)[4]);}
else{
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3478,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4444(t2,((C_word*)t0)[2],C_fix(6144));}}

/* k3476 in k3470 in k3413 in k3389 in k3386 in k3315 in emit in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3478(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3478,2,t0,t1);}
if(C_truep(t1)){
C_trace("ChickenBridge.scm: 145  string->keyword");
t2=C_retrieve(lf[106]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[5],((C_word*)t0)[4]);}
else{
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3487,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4444(t2,((C_word*)t0)[2],C_fix(3840));}}

/* k3485 in k3476 in k3470 in k3413 in k3389 in k3386 in k3315 in emit in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3487(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3487,2,t0,t1);}
if(C_truep(t1)){
C_trace("ChickenBridge.scm: 145  string->keyword");
t2=C_retrieve(lf[106]);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[5],((C_word*)t0)[4]);}
else{
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3496,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4444(t2,((C_word*)t0)[2],C_fix(6400));}}

/* k3494 in k3485 in k3476 in k3470 in k3413 in k3389 in k3386 in k3315 in emit in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3496(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3496,2,t0,t1);}
if(C_truep(t1)){
C_trace("ChickenBridge.scm: 145  string->symbol");
t2=*((C_word*)lf[100]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[5],((C_word*)t0)[4]);}
else{
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_3505,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4444(t2,((C_word*)t0)[2],C_fix(25344));}}

/* k3503 in k3494 in k3485 in k3476 in k3470 in k3413 in k3389 in k3386 in k3315 in emit in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3505(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3505,2,t0,t1);}
if(C_truep(t1)){
C_trace("ChickenBridge.scm: 145  error");
t2=*((C_word*)lf[27]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[5],lf[107],((C_word*)t0)[4]);}
else{
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3514,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[5],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4444(t2,((C_word*)t0)[2],C_fix(25088));}}

/* k3512 in k3503 in k3494 in k3485 in k3476 in k3470 in k3413 in k3389 in k3386 in k3315 in emit in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3514(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(C_truep(t1)){
C_trace("ChickenBridge.scm: 145  string->symbol");
t2=*((C_word*)lf[100]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[4],((C_word*)t0)[3]);}
else{
C_trace("ChickenBridge.scm: 145  error");
t2=*((C_word*)lf[27]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[4],lf[108],((C_word*)t0)[2]);}}

/* k3464 in k3413 in k3389 in k3386 in k3315 in emit in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3466(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_truep(t1)?C_SCHEME_TRUE:C_SCHEME_FALSE));}

/* k3419 in k3413 in k3389 in k3386 in k3315 in emit in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3421(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3421,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,lf[34]);}
else{
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3427,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4444(t2,((C_word*)t0)[2],C_fix(8199));}}

/* k3425 in k3419 in k3413 in k3389 in k3386 in k3315 in emit in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3427(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3427,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,lf[101]);}
else{
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3433,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4444(t2,((C_word*)t0)[2],C_fix(10244));}}

/* k3431 in k3425 in k3419 in k3413 in k3389 in k3386 in k3315 in emit in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3433(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3433,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,lf[102]);}
else{
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3439,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4444(t2,((C_word*)t0)[2],C_fix(8450));}}

/* k3437 in k3431 in k3425 in k3419 in k3413 in k3389 in k3386 in k3315 in emit in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3439(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3439,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,lf[103]);}
else{
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3445,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4444(t2,((C_word*)t0)[2],C_fix(8705));}}

/* k3443 in k3437 in k3431 in k3425 in k3419 in k3413 in k3389 in k3386 in k3315 in emit in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3445(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3445,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,lf[104]);}
else{
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3451,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4444(t2,((C_word*)t0)[2],C_fix(8963));}}

/* k3449 in k3443 in k3437 in k3431 in k3425 in k3419 in k3413 in k3389 in k3386 in k3315 in emit in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3451(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(C_truep(t1)){
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,lf[105]);}
else{
C_trace("ChickenBridge.scm: 145  string->symbol");
t2=*((C_word*)lf[100]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[3],((C_word*)t0)[2]);}}

/* set-emit-info! in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3292(C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3292,NULL,4,t1,t2,t3,t4);}
t5=(C_word)C_i_assoc(t2,t4);
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3299,a[2]=t3,a[3]=t5,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
if(C_truep(t5)){
t7=t6;
f_3299(2,t7,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 145  error");
t7=*((C_word*)lf[27]+1);
((C_proc4)C_retrieve_proc(t7))(4,t7,t6,lf[98],t2);}}

/* k3297 in set-emit-info! in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3299(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_i_set_cdr(((C_word*)t0)[3],((C_word*)t0)[2]));}

/* add-emit-info in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3282(C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3282,NULL,4,t1,t2,t3,t4);}
t5=(C_word)C_a_i_cons(&a,2,t2,t3);
t6=t1;
((C_proc2)(void*)(*((C_word*)t6+1)))(2,t6,(C_word)C_a_i_cons(&a,2,t5,t4));}

/* get-emit-info in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3270(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3270,NULL,3,t1,t2,t3);}
t4=(C_word)C_i_assoc(t2,t3);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_truep(t4)?(C_word)C_i_cdr(t4):C_SCHEME_FALSE));}

/* token-unit-type=? in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3238(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3238,NULL,3,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_3245,a[2]=t2,a[3]=t3,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 145  token-unit?");
f_3222(t4,t2);}

/* k3243 in token-unit-type=? in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3245(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3245,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3252,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-type");
f_3174(t2,((C_word*)t0)[2]);}
else{
t2=((C_word*)t0)[4];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}}

/* k3250 in k3243 in token-unit-type=? in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3252(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  SalType=?");
f_4444(((C_word*)t0)[3],t1,((C_word*)t0)[2]);}

/* token-unit? in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3222(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3222,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3229,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit?");
f_3159(t3,t2);}

/* k3227 in token-unit? in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3229(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_3229,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3236,a[2]=((C_word*)t0)[3],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  parse-unit-type");
f_3174(t2,((C_word*)t0)[2]);}
else{
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}}

/* k3234 in k3227 in token-unit? in k3218 in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3236(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 145  SalTokenType?");
f_4282(((C_word*)t0)[2],t1);}

/* parse-unit-position in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3210(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3210,NULL,2,t1,t2);}
t3=(C_word)C_i_check_structure(t2,lf[86]);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_block_ref(t2,C_fix(3)));}

/* parse-unit-parsed in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3192(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3192,NULL,2,t1,t2);}
t3=(C_word)C_i_check_structure(t2,lf[86]);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_block_ref(t2,C_fix(2)));}

/* parse-unit-type in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3174(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3174,NULL,2,t1,t2);}
t3=(C_word)C_i_check_structure(t2,lf[86]);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_block_ref(t2,C_fix(1)));}

/* parse-unit? in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3159(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3159,NULL,2,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_i_structurep(t2,lf[86]));}

/* make-parse-unit in k3149 in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3153(C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3153,NULL,4,t1,t2,t3,t4);}
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)C_a_i_record(&a,4,lf[86],t2,t3,t4));}

/* parse-error-position in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3141(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3141,NULL,2,t1,t2);}
t3=(C_word)C_i_check_structure(t2,lf[82]);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_block_ref(t2,C_fix(2)));}

/* parse-error-string in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3123(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3123,NULL,2,t1,t2);}
t3=(C_word)C_i_check_structure(t2,lf[82]);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_block_ref(t2,C_fix(1)));}

/* make-parse-error in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3102(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3102,NULL,3,t1,t2,t3);}
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_a_i_record(&a,3,lf[82],t2,t3));}

/* pattern-zero-or-more? in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3070(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3070,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3077,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  pattern-clause?");
f_2984(t3,t2);}

/* k3075 in pattern-zero-or-more? in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3077(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_eqp(t2,lf[80]));}
else{
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}}

/* pattern-sub in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3012(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3012,NULL,3,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_3020,a[2]=t3,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 145  pattern-subs");
f_2996(t4,t2);}

/* k3018 in pattern-sub in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3020(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_i_list_ref(t1,((C_word*)t0)[2]));}

/* pattern-nsubs in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_3002(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_3002,NULL,2,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_3010,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 145  pattern-subs");
f_2996(t3,t2);}

/* k3008 in pattern-nsubs in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_3010(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_i_length(t1));}

/* pattern-subs in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_2996(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2996,NULL,2,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_i_cdr(t2));}

/* pattern-clause? in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_2984(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2984,NULL,2,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_i_pairp(t2));}

/* get-rule in k2956 in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_2960(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2960,NULL,3,t1,t2,t3);}
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("ChickenBridge.scm: 145  hash-table-ref");
t4=*((C_word*)lf[73]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t1,C_retrieve2(lf[68],"*rules*"),t2);}
else{
C_trace("ChickenBridge.scm: 145  hash-table-ref/default");
t4=C_retrieve(lf[74]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t1,C_retrieve2(lf[68],"*rules*"),t3);}}

/* rule-name in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_2876(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2876,NULL,2,t1,t2);}
t3=(C_word)C_i_check_structure(t2,lf[70]);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_block_ref(t2,C_fix(1)));}

/* make-rule in k2851 in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_2855(C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
C_word tmp;
C_word t7;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2855,NULL,6,t1,t2,t3,t4,t5,t6);}
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)C_a_i_record(&a,6,lf[70],t2,t3,t4,t5,t6));}

/* null-tokens? in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_2845(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2845,NULL,2,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_i_nullp(t2));}

/* first-token in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_2833(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2833,NULL,2,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_i_car(t2));}

/* list->token in k2800 in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2804(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2804,3,t0,t1,t2);}
t3=(C_word)C_i_car(t2);
t4=(C_word)C_eqp(t3,lf[65]);
if(C_truep(t4)){
t5=(C_word)C_i_cdr(t2);
C_apply(4,0,t1,lf[59],t5);}
else{
C_apply(4,0,t1,lf[59],t2);}}

/* token-position in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_2792(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2792,NULL,2,t1,t2);}
t3=(C_word)C_i_check_structure(t2,lf[60]);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_block_ref(t2,C_fix(3)));}

/* token-string in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_2774(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2774,NULL,2,t1,t2);}
t3=(C_word)C_i_check_structure(t2,lf[60]);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_block_ref(t2,C_fix(2)));}

/* token-type in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_2756(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2756,NULL,2,t1,t2);}
t3=(C_word)C_i_check_structure(t2,lf[60]);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_i_block_ref(t2,C_fix(1)));}

/* make-token in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2735(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_2735,5,t0,t1,t2,t3,t4);}
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)C_a_i_record(&a,4,lf[60],t2,t3,t4));}

/* ranpink in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2729(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2729,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub145(t2));}

/* ranbrown in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2723(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2723,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub148(t2));}

/* rangamma in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2704(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2rv,(void*)f_2704r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_2704r(t0,t1,t2);}}

static void C_ccall f_2704r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
if(C_truep((C_word)C_vemptyp(t2))){
C_trace("ChickenBridge.scm: 143  tb:rangamma");
f_1972(t1,C_fix(1));}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
C_trace("ChickenBridge.scm: 143  tb:rangamma");
f_1972(t1,t3);}}

/* ranpoisson in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2685(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2rv,(void*)f_2685r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_2685r(t0,t1,t2);}}

static void C_ccall f_2685r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
if(C_truep((C_word)C_i_nullp(C_retrieve(lf[55])))){
C_trace("ChickenBridge.scm: 143  tb:ranpoisson");
f_1982(t1,C_fix(1));}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
C_trace("ChickenBridge.scm: 143  tb:ranpoisson");
f_1982(t1,t3);}}

/* rancauchy in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2679(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2679,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub138(t2));}

/* rangauss in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2639(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2r,(void*)f_2639r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_2639r(t0,t1,t2);}}

static void C_ccall f_2639r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 143  tb:rangauss");
f_1943(t1,C_fix(1),C_fix(0));}
else{
t3=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 143  tb:rangauss");
f_1943(t1,t4,C_fix(0));}
else{
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cdr(t2);
C_trace("ChickenBridge.scm: 143  tb:rangauss");
f_1943(t1,t4,t5);}}}

/* ranexp in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2620(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2rv,(void*)f_2620r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest_vector(a,C_rest_count(0));
f_2620r(t0,t1,t2);}}

static void C_ccall f_2620r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
if(C_truep((C_word)C_vemptyp(t2))){
C_trace("ChickenBridge.scm: 143  tb:ranexp");
f_1954(t1,C_fix(1));}
else{
t3=(C_word)C_i_vector_ref(t2,C_fix(0));
C_trace("ChickenBridge.scm: 143  tb:ranexp");
f_1954(t1,t3);}}

/* ranbeta in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2576(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2r,(void*)f_2576r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_2576r(t0,t1,t2);}}

static void C_ccall f_2576r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 143  tb:ranbeta");
f_1961(t1,lf[49],lf[50]);}
else{
t3=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 143  tb:ranbeta");
f_1961(t1,t4,t5);}
else{
t4=(C_word)C_i_car(t2);
t5=(C_word)C_i_cadr(t2);
C_trace("ChickenBridge.scm: 143  tb:ranbeta");
f_1961(t1,t4,t5);}}}

/* ranmiddle in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2570(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2570,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub111(t2));}

/* ranhigh in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2564(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2564,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub108(t2));}

/* ranlow in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2558(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2558,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub105(t2));}

/* pick in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2552(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr2r,(void*)f_2552r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_2552r(t0,t1,t2);}}

static void C_ccall f_2552r(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_trace("ChickenBridge.scm: 143  pickl");
t3=*((C_word*)lf[42]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,t2);}

/* pickl in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2529(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2529,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
C_trace("ChickenBridge.scm: 143  error");
t3=*((C_word*)lf[27]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t1,lf[43],t2);}
else{
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2546,a[2]=t2,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
t4=(C_word)C_i_length(t2);
C_trace("ChickenBridge.scm: 143  tb:rani");
f_1898(t3,t4);}}

/* k2544 in pickl in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2546(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_i_list_ref(((C_word*)t0)[2],t1));}

/* odds in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2471(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+14)){
C_save_and_reclaim((void*)tr3r,(void*)f_2471r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_2471r(t0,t1,t2,t3);}}

static void C_ccall f_2471r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word *a=C_alloc(14);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2488,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 143  tb:ranf");
f_1905(t4,lf[39]);}
else{
t4=(C_word)C_i_cdr(t3);
if(C_truep((C_word)C_i_nullp(t4))){
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2507,a[2]=t3,a[3]=t1,a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 143  tb:ranf");
f_1905(t5,lf[40]);}
else{
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2523,a[2]=t3,a[3]=t1,a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 143  tb:ranf");
f_1905(t5,lf[41]);}}}

/* k2521 in odds in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2523(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_lessp(t1,((C_word*)t0)[4]);
t3=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_truep(t2)?(C_word)C_i_car(((C_word*)t0)[2]):(C_word)C_i_cadr(((C_word*)t0)[2])));}

/* k2505 in odds in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2507(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_lessp(t1,((C_word*)t0)[4]);
t3=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_truep(t2)?(C_word)C_i_car(((C_word*)t0)[2]):C_SCHEME_FALSE));}

/* k2486 in odds in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2488(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_lessp(t1,((C_word*)t0)[3]);
t3=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_truep(t2)?C_SCHEME_TRUE:C_SCHEME_FALSE));}

/* ran in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2383(C_word c,C_word t0,C_word t1,...){
C_word tmp;
C_word t2;
va_list v;
C_word *a,c2=c;
C_save_rest(t1,c2,2);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+4)){
C_save_and_reclaim((void*)tr2r,(void*)f_2383r,2,t0,t1);}
else{
a=C_alloc((c-2)*3);
t2=C_restore_rest(a,C_rest_count(0));
f_2383r(t0,t1,t2);}}

static void C_ccall f_2383r(C_word t0,C_word t1,C_word t2){
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
f_1905(t1,lf[37]);}
else{
t3=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t3))){
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_fixnump(t4))){
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 143  tb:rani");
f_1898(t1,t5);}
else{
t5=(C_word)C_i_car(t2);
C_trace("ChickenBridge.scm: 143  tb:ranf");
f_1905(t1,t5);}}
else{
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2429,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_fixnump(t5))){
t6=(C_word)C_i_cadr(t2);
t7=t4;
f_2429(t7,(C_word)C_fixnump(t6));}
else{
t6=t4;
f_2429(t6,C_SCHEME_FALSE);}}}}

/* k2427 in ran in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_2429(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_2429,NULL,2,t0,t1);}
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

/* ran-set! in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2377(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2377,3,t0,t1,t2);}
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub80(C_SCHEME_UNDEFINED,t2));}

/* steps in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2318(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+12)){
C_save_and_reclaim((void*)tr4rv,(void*)f_2318r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest_vector(a,C_rest_count(0));
f_2318r(t0,t1,t2,t3,t4);}}

static void C_ccall f_2318r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
t9=C_set_block_item(t8,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_2331,a[2]=t5,a[3]=t8,a[4]=t4,a[5]=t2,a[6]=((C_word)li27),tmp=(C_word)a,a+=7,tmp));
t10=((C_word*)t8)[1];
f_2331(t10,t1,C_fix(0),t3,t6,t5);}

/* do216 in steps in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_2331(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
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
C_save_and_reclaim((void*)trf_2331,NULL,6,t0,t1,t2,t3,t4,t5);}
t6=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
if(C_truep((C_word)C_i_lessp(t2,((C_word*)t0)[5]))){
t8=(C_word)C_a_i_list(&a,1,((C_word*)t6)[1]);
t9=(C_word)C_i_set_cdr(((C_word*)t7)[1],t8);
t10=(C_word)C_i_cdr(((C_word*)t7)[1]);
t11=C_set_block_item(t7,0,t10);
t12=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_2367,a[2]=t7,a[3]=t4,a[4]=t1,a[5]=((C_word*)t0)[3],a[6]=t2,a[7]=t6,a[8]=((C_word*)t0)[4],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 143  modulo");
t13=*((C_word*)lf[34]+1);
((C_proc4)C_retrieve_proc(t13))(4,t13,t12,t2,t4);}
else{
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,(C_word)C_i_cdr(((C_word*)t0)[2]));}}

/* k2365 in do216 in steps in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2367(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2367,2,t0,t1);}
t2=(C_word)C_i_vector_ref(((C_word*)t0)[8],t1);
t3=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[7])[1],t2);
t4=C_mutate(((C_word *)((C_word*)t0)[7])+1,t3);
t5=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[6],C_fix(1));
t6=((C_word*)((C_word*)t0)[5])[1];
f_2331(t6,((C_word*)t0)[4],t5,((C_word*)((C_word*)t0)[7])[1],((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1]);}

/* interp in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2312(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr3r,(void*)f_2312r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_2312r(t0,t1,t2,t3);}}

static void C_ccall f_2312r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_trace("ChickenBridge.scm: 143  interpl");
t4=*((C_word*)lf[26]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t1,t2,t3);}

/* interpl in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2217(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+6)){
C_save_and_reclaim((void*)tr4rv,(void*)f_2217r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest_vector(a,C_rest_count(0));
f_2217r(t0,t1,t2,t3,t4);}}

static void C_ccall f_2217r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word *a=C_alloc(6);
t5=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_2221,a[2]=t1,a[3]=t2,a[4]=t3,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("ChickenBridge.scm: 143  error");
t6=*((C_word*)lf[27]+1);
((C_proc4)C_retrieve_proc(t6))(4,t6,t5,lf[31],t3);}
else{
t6=t5;
f_2221(2,t6,(C_word)C_i_car(t3));}}

/* k2219 in interpl in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2221(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_2221,2,t0,t1);}
t2=t1;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_2224,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=t3,tmp=(C_word)a,a+=7,tmp);
t5=(C_word)C_i_cdr(((C_word*)t0)[4]);
if(C_truep((C_word)C_i_nullp(t5))){
C_trace("ChickenBridge.scm: 143  err");
t6=C_retrieve(lf[29]);
((C_proc4)C_retrieve_proc(t6))(4,t6,t4,lf[30],((C_word*)t0)[4]);}
else{
t6=t4;
f_2224(2,t6,(C_word)C_i_cadr(((C_word*)t0)[4]));}}

/* k2222 in k2219 in interpl in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2224(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_2224,2,t0,t1);}
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
t13=C_set_block_item(t12,0,(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_2236,a[2]=((C_word*)t0)[4],a[3]=t12,a[4]=t9,a[5]=t7,a[6]=t3,a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[3],a[9]=t5,a[10]=((C_word)li24),tmp=(C_word)a,a+=11,tmp));
t14=((C_word*)t12)[1];
f_2236(t14,((C_word*)t0)[2],t10);}

/* do200 in k2222 in k2219 in interpl in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_2236(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_2236,NULL,3,t0,t1,t2);}
t3=(C_word)C_i_nullp(t2);
t4=(C_truep(t3)?t3:(C_word)C_i_greaterp(((C_word*)((C_word*)t0)[9])[1],((C_word*)t0)[8]));
if(C_truep(t4)){
C_trace("ChickenBridge.scm: 143  tb:rescale");
f_1762(t1,((C_word*)t0)[8],((C_word*)((C_word*)t0)[7])[1],((C_word*)((C_word*)t0)[9])[1],((C_word*)((C_word*)t0)[6])[1],((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[4]);}
else{
t5=C_mutate(((C_word *)((C_word*)t0)[7])+1,((C_word*)((C_word*)t0)[9])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[6])+1,((C_word*)((C_word*)t0)[5])[1]);
t7=(C_word)C_i_car(t2);
t8=C_mutate(((C_word *)((C_word*)t0)[9])+1,t7);
t9=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_2258,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t10=(C_word)C_i_cdr(t2);
if(C_truep((C_word)C_i_nullp(t10))){
C_trace("ChickenBridge.scm: 143  error");
t11=*((C_word*)lf[27]+1);
((C_proc4)C_retrieve_proc(t11))(4,t11,t9,lf[28],((C_word*)t0)[2]);}
else{
t11=(C_word)C_i_cadr(t2);
t12=C_mutate(((C_word *)((C_word*)t0)[5])+1,t11);
t13=t9;
f_2258(2,t13,t12);}}}

/* k2256 in do200 in k2222 in k2219 in interpl in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2258(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cddr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_2236(t3,((C_word*)t0)[2],t2);}

/* hertz->keynum in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2211(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2211,3,t0,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub75(t3,t4));}

/* keynum->pc in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2205(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2205,3,t0,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub71(C_SCHEME_UNDEFINED,t3));}

/* keynum->hertz in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2199(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2199,3,t0,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub66(t3,t4));}

/* scaler->cents in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2193(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2193,3,t0,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub62(C_SCHEME_UNDEFINED,t3));}

/* cents->scaler in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2187(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2187,3,t0,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_fixnum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub57(t3,t4));}

/* rhythm->seconds in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2127(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+12)){
C_save_and_reclaim((void*)tr3r,(void*)f_2127r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_2127r(t0,t1,t2,t3);}}

static void C_ccall f_2127r(C_word t0,C_word t1,C_word t2,C_word t3){
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
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2129,a[2]=t2,a[3]=((C_word)li15),tmp=(C_word)a,a+=4,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2134,a[2]=t4,a[3]=((C_word)li16),tmp=(C_word)a,a+=4,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2139,a[2]=t5,a[3]=((C_word)li17),tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_nullp(t3))){
C_trace("def-tempo173181");
t7=t6;
f_2139(t7,t1);}
else{
t7=(C_word)C_i_car(t3);
t8=(C_word)C_i_cdr(t3);
if(C_truep((C_word)C_i_nullp(t8))){
C_trace("def-beat174179");
t9=t5;
f_2134(t9,t1,t7);}
else{
t9=(C_word)C_i_car(t8);
t10=(C_word)C_i_cdr(t8);
if(C_truep((C_word)C_i_nullp(t10))){
C_trace("body171176");
t11=t4;
f_2129(t11,t1,t7,t9);}
else{
C_trace("##sys#error");
t11=*((C_word*)lf[20]+1);
((C_proc4)(void*)(*((C_word*)t11+1)))(4,t11,t1,lf[0],t10);}}}}

/* def-tempo173 in rhythm->seconds in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_2139(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2139,NULL,2,t0,t1);}
C_trace("def-beat174179");
t2=((C_word*)t0)[2];
f_2134(t2,t1,lf[19]);}

/* def-beat174 in rhythm->seconds in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_2134(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_2134,NULL,3,t0,t1,t2);}
C_trace("body171176");
t3=((C_word*)t0)[2];
f_2129(t3,t1,t2,lf[18]);}

/* body171 in rhythm->seconds in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_2129(C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)trf_2129,NULL,4,t0,t1,t2,t3);}
t4=((C_word*)t0)[2];
t5=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t6=(C_word)C_i_foreign_flonum_argumentp(t4);
t7=(C_word)C_i_foreign_flonum_argumentp(t2);
t8=(C_word)C_i_foreign_flonum_argumentp(t3);
t9=t1;
((C_proc2)(void*)(*((C_word*)t9+1)))(2,t9,(C_word)stub50(t5,t6,t7,t8));}

/* decimals in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2108(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr3rv,(void*)f_2108r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest_vector(a,C_rest_count(0));
f_2108r(t0,t1,t2,t3);}}

static void C_ccall f_2108r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
if(C_truep((C_word)C_vemptyp(t3))){
C_trace("ChickenBridge.scm: 143  tb:decimals");
f_1823(t1,t2,C_fix(3));}
else{
t4=(C_word)C_i_vector_ref(t3,C_fix(0));
C_trace("ChickenBridge.scm: 143  tb:decimals");
f_1823(t1,t2,t4);}}

/* quantize in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2102(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_2102,4,t0,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_flonum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub42(t4,t5,t6));}

/* int in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2096(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_2096,3,t0,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub30(C_SCHEME_UNDEFINED,t3));}

/* discrete in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2014(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,...){
C_word tmp;
C_word t6;
va_list v;
C_word *a,c2=c;
C_save_rest(t5,c2,6);
if(c<6) C_bad_min_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+4)){
C_save_and_reclaim((void*)tr6r,(void*)f_2014r,6,t0,t1,t2,t3,t4,t5);}
else{
a=C_alloc((c-6)*3);
t6=C_restore_rest(a,C_rest_count(0));
f_2014r(t0,t1,t2,t3,t4,t5,t6);}}

static void C_ccall f_2014r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
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
t7=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_2028,a[2]=t5,a[3]=t1,tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_nullp(t6))){
t8=(C_word)C_i_length(t5);
C_trace("ChickenBridge.scm: 143  tb:discrete");
f_1789(t7,t2,t3,t4,C_fix(0),t8,C_fix(1));}
else{
t8=(C_word)C_i_cdr(t6);
if(C_truep((C_word)C_i_nullp(t8))){
t9=(C_word)C_i_car(t6);
C_trace("ChickenBridge.scm: 143  tb:discrete");
f_1789(t7,t2,t3,t4,C_fix(0),t9,C_fix(1));}
else{
t9=(C_word)C_i_car(t6);
t10=(C_word)C_i_cadr(t6);
C_trace("ChickenBridge.scm: 143  tb:discrete");
f_1789(t7,t2,t3,t4,C_fix(0),t9,t10);}}}
else{
t7=(C_word)C_i_cdr(t6);
if(C_truep((C_word)C_i_nullp(t7))){
t8=(C_word)C_i_car(t6);
C_trace("ChickenBridge.scm: 143  tb:discrete");
f_1789(t1,t2,t3,t4,t5,t8,C_fix(1));}
else{
t8=(C_word)C_i_car(t6);
t9=(C_word)C_i_cadr(t6);
C_trace("ChickenBridge.scm: 143  tb:discrete");
f_1789(t1,t2,t3,t4,t5,t8,t9);}}}

/* k2026 in discrete in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_2028(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)C_i_list_ref(((C_word*)t0)[2],t1));}

/* rescale in k1758 in k1755 in k1752 in k1749 */
static void C_ccall f_1995(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,...){
C_word tmp;
C_word t7;
va_list v;
C_word *a,c2=c;
C_save_rest(t6,c2,7);
if(c<7) C_bad_min_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr7rv,(void*)f_1995r,7,t0,t1,t2,t3,t4,t5,t6);}
else{
a=C_alloc((c-7)*3);
t7=C_restore_rest_vector(a,C_rest_count(0));
f_1995r(t0,t1,t2,t3,t4,t5,t6,t7);}}

static void C_ccall f_1995r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
C_word tmp;
C_word t8;
C_word t9;
if(C_truep((C_word)C_vemptyp(t7))){
C_trace("ChickenBridge.scm: 143  tb:rescale");
f_1762(t1,t2,t3,t4,t5,t6,C_fix(1));}
else{
t8=(C_word)C_i_vector_ref(t7,C_fix(0));
C_trace("ChickenBridge.scm: 143  tb:rescale");
f_1762(t1,t2,t3,t4,t5,t6,t8);}}

/* tb:ranpoisson in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_1982(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1982,NULL,2,t1,t2);}
t3=(C_word)C_i_foreign_flonum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub142(C_SCHEME_UNDEFINED,t3));}

/* tb:rangamma in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_1972(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1972,NULL,2,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub134(t3,t4));}

/* tb:ranbeta in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_1961(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1961,NULL,3,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_flonum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub128(t4,t5,t6));}

/* tb:ranexp in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_1954(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1954,NULL,2,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub122(t3,t4));}

/* tb:rangauss in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_1943(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1943,NULL,3,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_flonum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub116(t4,t5,t6));}

/* tb:ranf in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_1905(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1905,NULL,2,t1,t2);}
t3=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub88(t3,t4));}

/* tb:rani in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_1898(C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word *a;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1898,NULL,2,t1,t2);}
t3=(C_word)C_i_foreign_fixnum_argumentp(t2);
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)stub84(C_SCHEME_UNDEFINED,t3));}

/* tb:decimals in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_1823(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_1823,NULL,3,t1,t2,t3);}
t4=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_fixnum_argumentp(t3);
t7=t1;
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)stub35(t4,t5,t6));}

/* tb:discrete in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_1789(C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
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
C_save_and_reclaim((void*)trf_1789,NULL,7,t1,t2,t3,t4,t5,t6,t7);}
t8=(C_word)C_i_foreign_flonum_argumentp(t2);
t9=(C_word)C_i_foreign_flonum_argumentp(t3);
t10=(C_word)C_i_foreign_flonum_argumentp(t4);
t11=(C_word)C_i_foreign_fixnum_argumentp(t5);
t12=(C_word)C_i_foreign_fixnum_argumentp(t6);
t13=(C_word)C_i_foreign_flonum_argumentp(t7);
t14=t1;
((C_proc2)(void*)(*((C_word*)t14+1)))(2,t14,(C_word)stub21(C_SCHEME_UNDEFINED,t8,t9,t10,t11,t12,t13));}

/* tb:rescale in k1758 in k1755 in k1752 in k1749 */
static void C_fcall f_1762(C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6,C_word t7){
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
C_save_and_reclaim((void*)trf_1762,NULL,7,t1,t2,t3,t4,t5,t6,t7);}
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
static C_PTABLE_ENTRY ptable[815] = {
{"toplevelChickenBridge.scm",(void*)C_grace_toplevel},
{"f_1751ChickenBridge.scm",(void*)f_1751},
{"f_1754ChickenBridge.scm",(void*)f_1754},
{"f_1757ChickenBridge.scm",(void*)f_1757},
{"f_1760ChickenBridge.scm",(void*)f_1760},
{"f_12184ChickenBridge.scm",(void*)f_12184},
{"f_12192ChickenBridge.scm",(void*)f_12192},
{"f_12196ChickenBridge.scm",(void*)f_12196},
{"f_2802ChickenBridge.scm",(void*)f_2802},
{"f_2853ChickenBridge.scm",(void*)f_2853},
{"f_12174ChickenBridge.scm",(void*)f_12174},
{"f_12182ChickenBridge.scm",(void*)f_12182},
{"f_2958ChickenBridge.scm",(void*)f_2958},
{"f_12160ChickenBridge.scm",(void*)f_12160},
{"f_12168ChickenBridge.scm",(void*)f_12168},
{"f_12172ChickenBridge.scm",(void*)f_12172},
{"f_3151ChickenBridge.scm",(void*)f_3151},
{"f_12134ChickenBridge.scm",(void*)f_12134},
{"f_12138ChickenBridge.scm",(void*)f_12138},
{"f_12144ChickenBridge.scm",(void*)f_12144},
{"f_12155ChickenBridge.scm",(void*)f_12155},
{"f_12151ChickenBridge.scm",(void*)f_12151},
{"f_3220ChickenBridge.scm",(void*)f_3220},
{"f_12112ChickenBridge.scm",(void*)f_12112},
{"f_4465ChickenBridge.scm",(void*)f_4465},
{"f_12092ChickenBridge.scm",(void*)f_12092},
{"f_4468ChickenBridge.scm",(void*)f_4468},
{"f_12052ChickenBridge.scm",(void*)f_12052},
{"f_4471ChickenBridge.scm",(void*)f_4471},
{"f_11958ChickenBridge.scm",(void*)f_11958},
{"f_11962ChickenBridge.scm",(void*)f_11962},
{"f_11965ChickenBridge.scm",(void*)f_11965},
{"f_11983ChickenBridge.scm",(void*)f_11983},
{"f_11986ChickenBridge.scm",(void*)f_11986},
{"f_12017ChickenBridge.scm",(void*)f_12017},
{"f_11989ChickenBridge.scm",(void*)f_11989},
{"f_11995ChickenBridge.scm",(void*)f_11995},
{"f_11948ChickenBridge.scm",(void*)f_11948},
{"f_11942ChickenBridge.scm",(void*)f_11942},
{"f_4474ChickenBridge.scm",(void*)f_4474},
{"f_11850ChickenBridge.scm",(void*)f_11850},
{"f_11852ChickenBridge.scm",(void*)f_11852},
{"f_11856ChickenBridge.scm",(void*)f_11856},
{"f_11859ChickenBridge.scm",(void*)f_11859},
{"f_11862ChickenBridge.scm",(void*)f_11862},
{"f_11902ChickenBridge.scm",(void*)f_11902},
{"f_11894ChickenBridge.scm",(void*)f_11894},
{"f_11865ChickenBridge.scm",(void*)f_11865},
{"f_11868ChickenBridge.scm",(void*)f_11868},
{"f_11871ChickenBridge.scm",(void*)f_11871},
{"f_11842ChickenBridge.scm",(void*)f_11842},
{"f_4477ChickenBridge.scm",(void*)f_4477},
{"f_11814ChickenBridge.scm",(void*)f_11814},
{"f_4480ChickenBridge.scm",(void*)f_4480},
{"f_11778ChickenBridge.scm",(void*)f_11778},
{"f_11790ChickenBridge.scm",(void*)f_11790},
{"f_11786ChickenBridge.scm",(void*)f_11786},
{"f_11760ChickenBridge.scm",(void*)f_11760},
{"f_11754ChickenBridge.scm",(void*)f_11754},
{"f_4483ChickenBridge.scm",(void*)f_4483},
{"f_11668ChickenBridge.scm",(void*)f_11668},
{"f_11672ChickenBridge.scm",(void*)f_11672},
{"f_11675ChickenBridge.scm",(void*)f_11675},
{"f_11678ChickenBridge.scm",(void*)f_11678},
{"f_11691ChickenBridge.scm",(void*)f_11691},
{"f_11637ChickenBridge.scm",(void*)f_11637},
{"f_11641ChickenBridge.scm",(void*)f_11641},
{"f_11656ChickenBridge.scm",(void*)f_11656},
{"f_11631ChickenBridge.scm",(void*)f_11631},
{"f_4486ChickenBridge.scm",(void*)f_4486},
{"f_11517ChickenBridge.scm",(void*)f_11517},
{"f_11533ChickenBridge.scm",(void*)f_11533},
{"f_11544ChickenBridge.scm",(void*)f_11544},
{"f_11511ChickenBridge.scm",(void*)f_11511},
{"f_4542ChickenBridge.scm",(void*)f_4542},
{"f_11378ChickenBridge.scm",(void*)f_11378},
{"f_11401ChickenBridge.scm",(void*)f_11401},
{"f_11398ChickenBridge.scm",(void*)f_11398},
{"f_11372ChickenBridge.scm",(void*)f_11372},
{"f_4545ChickenBridge.scm",(void*)f_4545},
{"f_11226ChickenBridge.scm",(void*)f_11226},
{"f_11244ChickenBridge.scm",(void*)f_11244},
{"f_11253ChickenBridge.scm",(void*)f_11253},
{"f_11220ChickenBridge.scm",(void*)f_11220},
{"f_4548ChickenBridge.scm",(void*)f_4548},
{"f_11173ChickenBridge.scm",(void*)f_11173},
{"f_11177ChickenBridge.scm",(void*)f_11177},
{"f_11180ChickenBridge.scm",(void*)f_11180},
{"f_11196ChickenBridge.scm",(void*)f_11196},
{"f_11155ChickenBridge.scm",(void*)f_11155},
{"f_11149ChickenBridge.scm",(void*)f_11149},
{"f_4551ChickenBridge.scm",(void*)f_4551},
{"f_11073ChickenBridge.scm",(void*)f_11073},
{"f_4690ChickenBridge.scm",(void*)f_4690},
{"f_10999ChickenBridge.scm",(void*)f_10999},
{"f_11006ChickenBridge.scm",(void*)f_11006},
{"f_10993ChickenBridge.scm",(void*)f_10993},
{"f_4693ChickenBridge.scm",(void*)f_4693},
{"f_10889ChickenBridge.scm",(void*)f_10889},
{"f_10897ChickenBridge.scm",(void*)f_10897},
{"f_10863ChickenBridge.scm",(void*)f_10863},
{"f_10880ChickenBridge.scm",(void*)f_10880},
{"f_10871ChickenBridge.scm",(void*)f_10871},
{"f_10857ChickenBridge.scm",(void*)f_10857},
{"f_4696ChickenBridge.scm",(void*)f_4696},
{"f_10813ChickenBridge.scm",(void*)f_10813},
{"f_4699ChickenBridge.scm",(void*)f_4699},
{"f_10731ChickenBridge.scm",(void*)f_10731},
{"f_10742ChickenBridge.scm",(void*)f_10742},
{"f_10744ChickenBridge.scm",(void*)f_10744},
{"f_10773ChickenBridge.scm",(void*)f_10773},
{"f_10709ChickenBridge.scm",(void*)f_10709},
{"f_10725ChickenBridge.scm",(void*)f_10725},
{"f_10703ChickenBridge.scm",(void*)f_10703},
{"f_4702ChickenBridge.scm",(void*)f_4702},
{"f_10627ChickenBridge.scm",(void*)f_10627},
{"f_10631ChickenBridge.scm",(void*)f_10631},
{"f_10663ChickenBridge.scm",(void*)f_10663},
{"f_10644ChickenBridge.scm",(void*)f_10644},
{"f_10648ChickenBridge.scm",(void*)f_10648},
{"f_10600ChickenBridge.scm",(void*)f_10600},
{"f_10604ChickenBridge.scm",(void*)f_10604},
{"f_10594ChickenBridge.scm",(void*)f_10594},
{"f_4705ChickenBridge.scm",(void*)f_4705},
{"f_10462ChickenBridge.scm",(void*)f_10462},
{"f_10502ChickenBridge.scm",(void*)f_10502},
{"f_10466ChickenBridge.scm",(void*)f_10466},
{"f_10482ChickenBridge.scm",(void*)f_10482},
{"f_10494ChickenBridge.scm",(void*)f_10494},
{"f_10498ChickenBridge.scm",(void*)f_10498},
{"f_10490ChickenBridge.scm",(void*)f_10490},
{"f_10401ChickenBridge.scm",(void*)f_10401},
{"f_10448ChickenBridge.scm",(void*)f_10448},
{"f_10408ChickenBridge.scm",(void*)f_10408},
{"f_10419ChickenBridge.scm",(void*)f_10419},
{"f_10395ChickenBridge.scm",(void*)f_10395},
{"f_4708ChickenBridge.scm",(void*)f_4708},
{"f_10375ChickenBridge.scm",(void*)f_10375},
{"f_10369ChickenBridge.scm",(void*)f_10369},
{"f_4711ChickenBridge.scm",(void*)f_4711},
{"f_10349ChickenBridge.scm",(void*)f_10349},
{"f_10353ChickenBridge.scm",(void*)f_10353},
{"f_10341ChickenBridge.scm",(void*)f_10341},
{"f_4714ChickenBridge.scm",(void*)f_4714},
{"f_10321ChickenBridge.scm",(void*)f_10321},
{"f_10325ChickenBridge.scm",(void*)f_10325},
{"f_10313ChickenBridge.scm",(void*)f_10313},
{"f_4717ChickenBridge.scm",(void*)f_4717},
{"f_10293ChickenBridge.scm",(void*)f_10293},
{"f_10297ChickenBridge.scm",(void*)f_10297},
{"f_10285ChickenBridge.scm",(void*)f_10285},
{"f_4720ChickenBridge.scm",(void*)f_4720},
{"f_10265ChickenBridge.scm",(void*)f_10265},
{"f_10269ChickenBridge.scm",(void*)f_10269},
{"f_10257ChickenBridge.scm",(void*)f_10257},
{"f_4723ChickenBridge.scm",(void*)f_4723},
{"f_10156ChickenBridge.scm",(void*)f_10156},
{"f_10126ChickenBridge.scm",(void*)f_10126},
{"f_10150ChickenBridge.scm",(void*)f_10150},
{"f_10120ChickenBridge.scm",(void*)f_10120},
{"f_4726ChickenBridge.scm",(void*)f_4726},
{"f_10070ChickenBridge.scm",(void*)f_10070},
{"f_10072ChickenBridge.scm",(void*)f_10072},
{"f_10076ChickenBridge.scm",(void*)f_10076},
{"f_10104ChickenBridge.scm",(void*)f_10104},
{"f_10096ChickenBridge.scm",(void*)f_10096},
{"f_10092ChickenBridge.scm",(void*)f_10092},
{"f_10079ChickenBridge.scm",(void*)f_10079},
{"f_10062ChickenBridge.scm",(void*)f_10062},
{"f_4729ChickenBridge.scm",(void*)f_4729},
{"f_10009ChickenBridge.scm",(void*)f_10009},
{"f_10011ChickenBridge.scm",(void*)f_10011},
{"f_10015ChickenBridge.scm",(void*)f_10015},
{"f_10046ChickenBridge.scm",(void*)f_10046},
{"f_10038ChickenBridge.scm",(void*)f_10038},
{"f_10034ChickenBridge.scm",(void*)f_10034},
{"f_10018ChickenBridge.scm",(void*)f_10018},
{"f_10021ChickenBridge.scm",(void*)f_10021},
{"f_10001ChickenBridge.scm",(void*)f_10001},
{"f_4732ChickenBridge.scm",(void*)f_4732},
{"f_9951ChickenBridge.scm",(void*)f_9951},
{"f_9965ChickenBridge.scm",(void*)f_9965},
{"f_9957ChickenBridge.scm",(void*)f_9957},
{"f_9916ChickenBridge.scm",(void*)f_9916},
{"f_9949ChickenBridge.scm",(void*)f_9949},
{"f_9910ChickenBridge.scm",(void*)f_9910},
{"f_4735ChickenBridge.scm",(void*)f_4735},
{"f_9857ChickenBridge.scm",(void*)f_9857},
{"f_9861ChickenBridge.scm",(void*)f_9861},
{"f_9874ChickenBridge.scm",(void*)f_9874},
{"f_9866ChickenBridge.scm",(void*)f_9866},
{"f_9814ChickenBridge.scm",(void*)f_9814},
{"f_9847ChickenBridge.scm",(void*)f_9847},
{"f_9808ChickenBridge.scm",(void*)f_9808},
{"f_4738ChickenBridge.scm",(void*)f_4738},
{"f_9728ChickenBridge.scm",(void*)f_9728},
{"f_9722ChickenBridge.scm",(void*)f_9722},
{"f_4741ChickenBridge.scm",(void*)f_4741},
{"f_9491ChickenBridge.scm",(void*)f_9491},
{"f_9495ChickenBridge.scm",(void*)f_9495},
{"f_9503ChickenBridge.scm",(void*)f_9503},
{"f_9526ChickenBridge.scm",(void*)f_9526},
{"f_9529ChickenBridge.scm",(void*)f_9529},
{"f_9532ChickenBridge.scm",(void*)f_9532},
{"f_9535ChickenBridge.scm",(void*)f_9535},
{"f_9595ChickenBridge.scm",(void*)f_9595},
{"f_9602ChickenBridge.scm",(void*)f_9602},
{"f_9612ChickenBridge.scm",(void*)f_9612},
{"f_9622ChickenBridge.scm",(void*)f_9622},
{"f_9636ChickenBridge.scm",(void*)f_9636},
{"f_9646ChickenBridge.scm",(void*)f_9646},
{"f_9656ChickenBridge.scm",(void*)f_9656},
{"f_9666ChickenBridge.scm",(void*)f_9666},
{"f_9538ChickenBridge.scm",(void*)f_9538},
{"f_9562ChickenBridge.scm",(void*)f_9562},
{"f_9541ChickenBridge.scm",(void*)f_9541},
{"f_9448ChickenBridge.scm",(void*)f_9448},
{"f_9481ChickenBridge.scm",(void*)f_9481},
{"f_9442ChickenBridge.scm",(void*)f_9442},
{"f_4744ChickenBridge.scm",(void*)f_4744},
{"f_9360ChickenBridge.scm",(void*)f_9360},
{"f_9364ChickenBridge.scm",(void*)f_9364},
{"f_9370ChickenBridge.scm",(void*)f_9370},
{"f_9390ChickenBridge.scm",(void*)f_9390},
{"f_9334ChickenBridge.scm",(void*)f_9334},
{"f_9344ChickenBridge.scm",(void*)f_9344},
{"f_9328ChickenBridge.scm",(void*)f_9328},
{"f_4747ChickenBridge.scm",(void*)f_4747},
{"f_9205ChickenBridge.scm",(void*)f_9205},
{"f_9209ChickenBridge.scm",(void*)f_9209},
{"f_9137ChickenBridge.scm",(void*)f_9137},
{"f_9156ChickenBridge.scm",(void*)f_9156},
{"f_9191ChickenBridge.scm",(void*)f_9191},
{"f_9162ChickenBridge.scm",(void*)f_9162},
{"f_9166ChickenBridge.scm",(void*)f_9166},
{"f_9180ChickenBridge.scm",(void*)f_9180},
{"f_9169ChickenBridge.scm",(void*)f_9169},
{"f_9150ChickenBridge.scm",(void*)f_9150},
{"f_9131ChickenBridge.scm",(void*)f_9131},
{"f_4750ChickenBridge.scm",(void*)f_4750},
{"f_8859ChickenBridge.scm",(void*)f_8859},
{"f_5273ChickenBridge.scm",(void*)f_5273},
{"f_8811ChickenBridge.scm",(void*)f_8811},
{"f_8803ChickenBridge.scm",(void*)f_8803},
{"f_5276ChickenBridge.scm",(void*)f_5276},
{"f_8683ChickenBridge.scm",(void*)f_8683},
{"f_5282ChickenBridge.scm",(void*)f_5282},
{"f_5754ChickenBridge.scm",(void*)f_5754},
{"f_5788ChickenBridge.scm",(void*)f_5788},
{"f_5780ChickenBridge.scm",(void*)f_5780},
{"f_5776ChickenBridge.scm",(void*)f_5776},
{"f_5761ChickenBridge.scm",(void*)f_5761},
{"f_5765ChickenBridge.scm",(void*)f_5765},
{"f_5758ChickenBridge.scm",(void*)f_5758},
{"f_5300ChickenBridge.scm",(void*)f_5300},
{"f_5747ChickenBridge.scm",(void*)f_5747},
{"f_5743ChickenBridge.scm",(void*)f_5743},
{"f_5307ChickenBridge.scm",(void*)f_5307},
{"f_5618ChickenBridge.scm",(void*)f_5618},
{"f_5639ChickenBridge.scm",(void*)f_5639},
{"f_5641ChickenBridge.scm",(void*)f_5641},
{"f_5655ChickenBridge.scm",(void*)f_5655},
{"f_5708ChickenBridge.scm",(void*)f_5708},
{"f_5658ChickenBridge.scm",(void*)f_5658},
{"f_5693ChickenBridge.scm",(void*)f_5693},
{"f_5661ChickenBridge.scm",(void*)f_5661},
{"f_5674ChickenBridge.scm",(void*)f_5674},
{"f_5686ChickenBridge.scm",(void*)f_5686},
{"f_5678ChickenBridge.scm",(void*)f_5678},
{"f_5664ChickenBridge.scm",(void*)f_5664},
{"f_5628ChickenBridge.scm",(void*)f_5628},
{"f_5310ChickenBridge.scm",(void*)f_5310},
{"f_5582ChickenBridge.scm",(void*)f_5582},
{"f_5608ChickenBridge.scm",(void*)f_5608},
{"f_5593ChickenBridge.scm",(void*)f_5593},
{"f_5313ChickenBridge.scm",(void*)f_5313},
{"f_5317ChickenBridge.scm",(void*)f_5317},
{"f_5526ChickenBridge.scm",(void*)f_5526},
{"f_5536ChickenBridge.scm",(void*)f_5536},
{"f_5539ChickenBridge.scm",(void*)f_5539},
{"f_5560ChickenBridge.scm",(void*)f_5560},
{"f_5542ChickenBridge.scm",(void*)f_5542},
{"f_5546ChickenBridge.scm",(void*)f_5546},
{"f_5320ChickenBridge.scm",(void*)f_5320},
{"f_5323ChickenBridge.scm",(void*)f_5323},
{"f_5489ChickenBridge.scm",(void*)f_5489},
{"f_5497ChickenBridge.scm",(void*)f_5497},
{"f_5493ChickenBridge.scm",(void*)f_5493},
{"f_5326ChickenBridge.scm",(void*)f_5326},
{"f_5354ChickenBridge.scm",(void*)f_5354},
{"f_5357ChickenBridge.scm",(void*)f_5357},
{"f_5360ChickenBridge.scm",(void*)f_5360},
{"f_5363ChickenBridge.scm",(void*)f_5363},
{"f_5422ChickenBridge.scm",(void*)f_5422},
{"f_8637ChickenBridge.scm",(void*)f_8637},
{"f_8653ChickenBridge.scm",(void*)f_8653},
{"f_8656ChickenBridge.scm",(void*)f_8656},
{"f_8659ChickenBridge.scm",(void*)f_8659},
{"f_8662ChickenBridge.scm",(void*)f_8662},
{"f_8673ChickenBridge.scm",(void*)f_8673},
{"f_8631ChickenBridge.scm",(void*)f_8631},
{"f_5795ChickenBridge.scm",(void*)f_5795},
{"f_8492ChickenBridge.scm",(void*)f_8492},
{"f_8531ChickenBridge.scm",(void*)f_8531},
{"f_8505ChickenBridge.scm",(void*)f_8505},
{"f_8486ChickenBridge.scm",(void*)f_8486},
{"f_5798ChickenBridge.scm",(void*)f_5798},
{"f_8074ChickenBridge.scm",(void*)f_8074},
{"f_8078ChickenBridge.scm",(void*)f_8078},
{"f_8090ChickenBridge.scm",(void*)f_8090},
{"f_8148ChickenBridge.scm",(void*)f_8148},
{"f_8151ChickenBridge.scm",(void*)f_8151},
{"f_8154ChickenBridge.scm",(void*)f_8154},
{"f_8366ChickenBridge.scm",(void*)f_8366},
{"f_8304ChickenBridge.scm",(void*)f_8304},
{"f_8338ChickenBridge.scm",(void*)f_8338},
{"f_8313ChickenBridge.scm",(void*)f_8313},
{"f_8324ChickenBridge.scm",(void*)f_8324},
{"f_8320ChickenBridge.scm",(void*)f_8320},
{"f_8163ChickenBridge.scm",(void*)f_8163},
{"f_8241ChickenBridge.scm",(void*)f_8241},
{"f_8282ChickenBridge.scm",(void*)f_8282},
{"f_8286ChickenBridge.scm",(void*)f_8286},
{"f_8290ChickenBridge.scm",(void*)f_8290},
{"f_8245ChickenBridge.scm",(void*)f_8245},
{"f_8249ChickenBridge.scm",(void*)f_8249},
{"f_8276ChickenBridge.scm",(void*)f_8276},
{"f_8252ChickenBridge.scm",(void*)f_8252},
{"f_8166ChickenBridge.scm",(void*)f_8166},
{"f_8238ChickenBridge.scm",(void*)f_8238},
{"f_8180ChickenBridge.scm",(void*)f_8180},
{"f_8182ChickenBridge.scm",(void*)f_8182},
{"f_8230ChickenBridge.scm",(void*)f_8230},
{"f_8201ChickenBridge.scm",(void*)f_8201},
{"f_8218ChickenBridge.scm",(void*)f_8218},
{"f_8204ChickenBridge.scm",(void*)f_8204},
{"f_8197ChickenBridge.scm",(void*)f_8197},
{"f_8169ChickenBridge.scm",(void*)f_8169},
{"f_8099ChickenBridge.scm",(void*)f_8099},
{"f_8109ChickenBridge.scm",(void*)f_8109},
{"f_8115ChickenBridge.scm",(void*)f_8115},
{"f_8087ChickenBridge.scm",(void*)f_8087},
{"f_8035ChickenBridge.scm",(void*)f_8035},
{"f_8052ChickenBridge.scm",(void*)f_8052},
{"f_8068ChickenBridge.scm",(void*)f_8068},
{"f_8046ChickenBridge.scm",(void*)f_8046},
{"f_8029ChickenBridge.scm",(void*)f_8029},
{"f_5801ChickenBridge.scm",(void*)f_5801},
{"f_7953ChickenBridge.scm",(void*)f_7953},
{"f_5804ChickenBridge.scm",(void*)f_5804},
{"f_7929ChickenBridge.scm",(void*)f_7929},
{"f_7941ChickenBridge.scm",(void*)f_7941},
{"f_7937ChickenBridge.scm",(void*)f_7937},
{"f_7915ChickenBridge.scm",(void*)f_7915},
{"f_7923ChickenBridge.scm",(void*)f_7923},
{"f_7909ChickenBridge.scm",(void*)f_7909},
{"f_5807ChickenBridge.scm",(void*)f_5807},
{"f_6959ChickenBridge.scm",(void*)f_6959},
{"f_7855ChickenBridge.scm",(void*)f_7855},
{"f_7902ChickenBridge.scm",(void*)f_7902},
{"f_7892ChickenBridge.scm",(void*)f_7892},
{"f_7859ChickenBridge.scm",(void*)f_7859},
{"f_6962ChickenBridge.scm",(void*)f_6962},
{"f_7849ChickenBridge.scm",(void*)f_7849},
{"f_7235ChickenBridge.scm",(void*)f_7235},
{"f_7358ChickenBridge.scm",(void*)f_7358},
{"f_7361ChickenBridge.scm",(void*)f_7361},
{"f_7364ChickenBridge.scm",(void*)f_7364},
{"f_7367ChickenBridge.scm",(void*)f_7367},
{"f_7370ChickenBridge.scm",(void*)f_7370},
{"f_7373ChickenBridge.scm",(void*)f_7373},
{"f_7376ChickenBridge.scm",(void*)f_7376},
{"f_7379ChickenBridge.scm",(void*)f_7379},
{"f_7843ChickenBridge.scm",(void*)f_7843},
{"f_7397ChickenBridge.scm",(void*)f_7397},
{"f_7400ChickenBridge.scm",(void*)f_7400},
{"f_7678ChickenBridge.scm",(void*)f_7678},
{"f_7786ChickenBridge.scm",(void*)f_7786},
{"f_7698ChickenBridge.scm",(void*)f_7698},
{"f_7707ChickenBridge.scm",(void*)f_7707},
{"f_7711ChickenBridge.scm",(void*)f_7711},
{"f_7715ChickenBridge.scm",(void*)f_7715},
{"f_7723ChickenBridge.scm",(void*)f_7723},
{"f_7719ChickenBridge.scm",(void*)f_7719},
{"f_7688ChickenBridge.scm",(void*)f_7688},
{"f_7403ChickenBridge.scm",(void*)f_7403},
{"f_7406ChickenBridge.scm",(void*)f_7406},
{"f_7409ChickenBridge.scm",(void*)f_7409},
{"f_7412ChickenBridge.scm",(void*)f_7412},
{"f_7415ChickenBridge.scm",(void*)f_7415},
{"f_7672ChickenBridge.scm",(void*)f_7672},
{"f_7571ChickenBridge.scm",(void*)f_7571},
{"f_7578ChickenBridge.scm",(void*)f_7578},
{"f_7580ChickenBridge.scm",(void*)f_7580},
{"f_7652ChickenBridge.scm",(void*)f_7652},
{"f_7604ChickenBridge.scm",(void*)f_7604},
{"f_7607ChickenBridge.scm",(void*)f_7607},
{"f_7628ChickenBridge.scm",(void*)f_7628},
{"f_7594ChickenBridge.scm",(void*)f_7594},
{"f_7418ChickenBridge.scm",(void*)f_7418},
{"f_7560ChickenBridge.scm",(void*)f_7560},
{"f_7548ChickenBridge.scm",(void*)f_7548},
{"f_7544ChickenBridge.scm",(void*)f_7544},
{"f_7425ChickenBridge.scm",(void*)f_7425},
{"f_7382ChickenBridge.scm",(void*)f_7382},
{"f_7841ChickenBridge.scm",(void*)f_7841},
{"f_7279ChickenBridge.scm",(void*)f_7279},
{"f_7283ChickenBridge.scm",(void*)f_7283},
{"f_7325ChickenBridge.scm",(void*)f_7325},
{"f_7288ChickenBridge.scm",(void*)f_7288},
{"f_7294ChickenBridge.scm",(void*)f_7294},
{"f_7320ChickenBridge.scm",(void*)f_7320},
{"f_7324ChickenBridge.scm",(void*)f_7324},
{"f_7300ChickenBridge.scm",(void*)f_7300},
{"f_7318ChickenBridge.scm",(void*)f_7318},
{"f_7315ChickenBridge.scm",(void*)f_7315},
{"f_7311ChickenBridge.scm",(void*)f_7311},
{"f_7304ChickenBridge.scm",(void*)f_7304},
{"f_7273ChickenBridge.scm",(void*)f_7273},
{"f_7267ChickenBridge.scm",(void*)f_7267},
{"f_7261ChickenBridge.scm",(void*)f_7261},
{"f_7255ChickenBridge.scm",(void*)f_7255},
{"f_7249ChickenBridge.scm",(void*)f_7249},
{"f_7243ChickenBridge.scm",(void*)f_7243},
{"f_7237ChickenBridge.scm",(void*)f_7237},
{"f_6501ChickenBridge.scm",(void*)f_6501},
{"f_6964ChickenBridge.scm",(void*)f_6964},
{"f_6974ChickenBridge.scm",(void*)f_6974},
{"f_7205ChickenBridge.scm",(void*)f_7205},
{"f_6977ChickenBridge.scm",(void*)f_6977},
{"f_6980ChickenBridge.scm",(void*)f_6980},
{"f_6992ChickenBridge.scm",(void*)f_6992},
{"f_7040ChickenBridge.scm",(void*)f_7040},
{"f_7056ChickenBridge.scm",(void*)f_7056},
{"f_7066ChickenBridge.scm",(void*)f_7066},
{"f_7183ChickenBridge.scm",(void*)f_7183},
{"f_7171ChickenBridge.scm",(void*)f_7171},
{"f_7169ChickenBridge.scm",(void*)f_7169},
{"f_7156ChickenBridge.scm",(void*)f_7156},
{"f_7110ChickenBridge.scm",(void*)f_7110},
{"f_7137ChickenBridge.scm",(void*)f_7137},
{"f_7116ChickenBridge.scm",(void*)f_7116},
{"f_7050ChickenBridge.scm",(void*)f_7050},
{"f_6995ChickenBridge.scm",(void*)f_6995},
{"f_7000ChickenBridge.scm",(void*)f_7000},
{"f_7013ChickenBridge.scm",(void*)f_7013},
{"f_7222ChickenBridge.scm",(void*)f_7222},
{"f_7213ChickenBridge.scm",(void*)f_7213},
{"f_7221ChickenBridge.scm",(void*)f_7221},
{"f_7224ChickenBridge.scm",(void*)f_7224},
{"f_7232ChickenBridge.scm",(void*)f_7232},
{"f_6948ChickenBridge.scm",(void*)f_6948},
{"f_6611ChickenBridge.scm",(void*)f_6611},
{"f_6952ChickenBridge.scm",(void*)f_6952},
{"f_6890ChickenBridge.scm",(void*)f_6890},
{"f_6908ChickenBridge.scm",(void*)f_6908},
{"f_6918ChickenBridge.scm",(void*)f_6918},
{"f_6894ChickenBridge.scm",(void*)f_6894},
{"f_6881ChickenBridge.scm",(void*)f_6881},
{"f_6589ChickenBridge.scm",(void*)f_6589},
{"f_6885ChickenBridge.scm",(void*)f_6885},
{"f_6875ChickenBridge.scm",(void*)f_6875},
{"f_6571ChickenBridge.scm",(void*)f_6571},
{"f_6866ChickenBridge.scm",(void*)f_6866},
{"f_6580ChickenBridge.scm",(void*)f_6580},
{"f_6870ChickenBridge.scm",(void*)f_6870},
{"f_6803ChickenBridge.scm",(void*)f_6803},
{"f_6828ChickenBridge.scm",(void*)f_6828},
{"f_6536ChickenBridge.scm",(void*)f_6536},
{"f_6816ChickenBridge.scm",(void*)f_6816},
{"f_6635ChickenBridge.scm",(void*)f_6635},
{"f_6754ChickenBridge.scm",(void*)f_6754},
{"f_6749ChickenBridge.scm",(void*)f_6749},
{"f_6637ChickenBridge.scm",(void*)f_6637},
{"f_6744ChickenBridge.scm",(void*)f_6744},
{"f_6748ChickenBridge.scm",(void*)f_6748},
{"f_6740ChickenBridge.scm",(void*)f_6740},
{"f_6708ChickenBridge.scm",(void*)f_6708},
{"f_6733ChickenBridge.scm",(void*)f_6733},
{"f_6737ChickenBridge.scm",(void*)f_6737},
{"f_6718ChickenBridge.scm",(void*)f_6718},
{"f_6697ChickenBridge.scm",(void*)f_6697},
{"f_6667ChickenBridge.scm",(void*)f_6667},
{"f_6639ChickenBridge.scm",(void*)f_6639},
{"f_6616ChickenBridge.scm",(void*)f_6616},
{"f_6621ChickenBridge.scm",(void*)f_6621},
{"f_6626ChickenBridge.scm",(void*)f_6626},
{"f_6594ChickenBridge.scm",(void*)f_6594},
{"f_6598ChickenBridge.scm",(void*)f_6598},
{"f_6550ChickenBridge.scm",(void*)f_6550},
{"f_6554ChickenBridge.scm",(void*)f_6554},
{"f_6541ChickenBridge.scm",(void*)f_6541},
{"f_6545ChickenBridge.scm",(void*)f_6545},
{"f_6529ChickenBridge.scm",(void*)f_6529},
{"f_6526ChickenBridge.scm",(void*)f_6526},
{"f_6483ChickenBridge.scm",(void*)f_6483},
{"f_6488ChickenBridge.scm",(void*)f_6488},
{"f_6469ChickenBridge.scm",(void*)f_6469},
{"f_6474ChickenBridge.scm",(void*)f_6474},
{"f_6440ChickenBridge.scm",(void*)f_6440},
{"f_6449ChickenBridge.scm",(void*)f_6449},
{"f_6454ChickenBridge.scm",(void*)f_6454},
{"f_6429ChickenBridge.scm",(void*)f_6429},
{"f_6434ChickenBridge.scm",(void*)f_6434},
{"f_6389ChickenBridge.scm",(void*)f_6389},
{"f_6419ChickenBridge.scm",(void*)f_6419},
{"f_6341ChickenBridge.scm",(void*)f_6341},
{"f_6375ChickenBridge.scm",(void*)f_6375},
{"f_6321ChickenBridge.scm",(void*)f_6321},
{"f_6301ChickenBridge.scm",(void*)f_6301},
{"f_6287ChickenBridge.scm",(void*)f_6287},
{"f_6277ChickenBridge.scm",(void*)f_6277},
{"f_6267ChickenBridge.scm",(void*)f_6267},
{"f_6257ChickenBridge.scm",(void*)f_6257},
{"f_6247ChickenBridge.scm",(void*)f_6247},
{"f_6225ChickenBridge.scm",(void*)f_6225},
{"f_6219ChickenBridge.scm",(void*)f_6219},
{"f_6172ChickenBridge.scm",(void*)f_6172},
{"f_6176ChickenBridge.scm",(void*)f_6176},
{"f_6192ChickenBridge.scm",(void*)f_6192},
{"f_6201ChickenBridge.scm",(void*)f_6201},
{"f_6179ChickenBridge.scm",(void*)f_6179},
{"f_6163ChickenBridge.scm",(void*)f_6163},
{"f_6167ChickenBridge.scm",(void*)f_6167},
{"f_5984ChickenBridge.scm",(void*)f_5984},
{"f_6137ChickenBridge.scm",(void*)f_6137},
{"f_6150ChickenBridge.scm",(void*)f_6150},
{"f_6132ChickenBridge.scm",(void*)f_6132},
{"f_5987ChickenBridge.scm",(void*)f_5987},
{"f_6129ChickenBridge.scm",(void*)f_6129},
{"f_6113ChickenBridge.scm",(void*)f_6113},
{"f_6106ChickenBridge.scm",(void*)f_6106},
{"f_6102ChickenBridge.scm",(void*)f_6102},
{"f_6015ChickenBridge.scm",(void*)f_6015},
{"f_6023ChickenBridge.scm",(void*)f_6023},
{"f_6033ChickenBridge.scm",(void*)f_6033},
{"f_6036ChickenBridge.scm",(void*)f_6036},
{"f_6018ChickenBridge.scm",(void*)f_6018},
{"f_5813ChickenBridge.scm",(void*)f_5813},
{"f_5819ChickenBridge.scm",(void*)f_5819},
{"f_5822ChickenBridge.scm",(void*)f_5822},
{"f_3625ChickenBridge.scm",(void*)f_3625},
{"f_3638ChickenBridge.scm",(void*)f_3638},
{"f_3645ChickenBridge.scm",(void*)f_3645},
{"f_3652ChickenBridge.scm",(void*)f_3652},
{"f_3631ChickenBridge.scm",(void*)f_3631},
{"f_5826ChickenBridge.scm",(void*)f_5826},
{"f_5860ChickenBridge.scm",(void*)f_5860},
{"f_5953ChickenBridge.scm",(void*)f_5953},
{"f_5963ChickenBridge.scm",(void*)f_5963},
{"f_5866ChickenBridge.scm",(void*)f_5866},
{"f_5923ChickenBridge.scm",(void*)f_5923},
{"f_5933ChickenBridge.scm",(void*)f_5933},
{"f_5874ChickenBridge.scm",(void*)f_5874},
{"f_5888ChickenBridge.scm",(void*)f_5888},
{"f_5892ChickenBridge.scm",(void*)f_5892},
{"f_5896ChickenBridge.scm",(void*)f_5896},
{"f_5900ChickenBridge.scm",(void*)f_5900},
{"f_5907ChickenBridge.scm",(void*)f_5907},
{"f_5884ChickenBridge.scm",(void*)f_5884},
{"f_5877ChickenBridge.scm",(void*)f_5877},
{"f_5829ChickenBridge.scm",(void*)f_5829},
{"f_4752ChickenBridge.scm",(void*)f_4752},
{"f_4765ChickenBridge.scm",(void*)f_4765},
{"f_4815ChickenBridge.scm",(void*)f_4815},
{"f_4912ChickenBridge.scm",(void*)f_4912},
{"f_4980ChickenBridge.scm",(void*)f_4980},
{"f_5237ChickenBridge.scm",(void*)f_5237},
{"f_4987ChickenBridge.scm",(void*)f_4987},
{"f_5225ChickenBridge.scm",(void*)f_5225},
{"f_5176ChickenBridge.scm",(void*)f_5176},
{"f_5182ChickenBridge.scm",(void*)f_5182},
{"f_5206ChickenBridge.scm",(void*)f_5206},
{"f_5202ChickenBridge.scm",(void*)f_5202},
{"f_5190ChickenBridge.scm",(void*)f_5190},
{"f_4990ChickenBridge.scm",(void*)f_4990},
{"f_5152ChickenBridge.scm",(void*)f_5152},
{"f_5156ChickenBridge.scm",(void*)f_5156},
{"f_4993ChickenBridge.scm",(void*)f_4993},
{"f_5129ChickenBridge.scm",(void*)f_5129},
{"f_5133ChickenBridge.scm",(void*)f_5133},
{"f_4996ChickenBridge.scm",(void*)f_4996},
{"f_5106ChickenBridge.scm",(void*)f_5106},
{"f_5110ChickenBridge.scm",(void*)f_5110},
{"f_4999ChickenBridge.scm",(void*)f_4999},
{"f_5031ChickenBridge.scm",(void*)f_5031},
{"f_5049ChickenBridge.scm",(void*)f_5049},
{"f_5067ChickenBridge.scm",(void*)f_5067},
{"f_5085ChickenBridge.scm",(void*)f_5085},
{"f_5002ChickenBridge.scm",(void*)f_5002},
{"f_5006ChickenBridge.scm",(void*)f_5006},
{"f_4916ChickenBridge.scm",(void*)f_4916},
{"f_4920ChickenBridge.scm",(void*)f_4920},
{"f_4924ChickenBridge.scm",(void*)f_4924},
{"f_4819ChickenBridge.scm",(void*)f_4819},
{"f_4823ChickenBridge.scm",(void*)f_4823},
{"f_4827ChickenBridge.scm",(void*)f_4827},
{"f_4846ChickenBridge.scm",(void*)f_4846},
{"f_4850ChickenBridge.scm",(void*)f_4850},
{"f_4830ChickenBridge.scm",(void*)f_4830},
{"f_4834ChickenBridge.scm",(void*)f_4834},
{"f_4769ChickenBridge.scm",(void*)f_4769},
{"f_4773ChickenBridge.scm",(void*)f_4773},
{"f_4777ChickenBridge.scm",(void*)f_4777},
{"f_4759ChickenBridge.scm",(void*)f_4759},
{"f_4574ChickenBridge.scm",(void*)f_4574},
{"f_4586ChickenBridge.scm",(void*)f_4586},
{"f_4605ChickenBridge.scm",(void*)f_4605},
{"f_4623ChickenBridge.scm",(void*)f_4623},
{"f_4655ChickenBridge.scm",(void*)f_4655},
{"f_4658ChickenBridge.scm",(void*)f_4658},
{"f_4651ChickenBridge.scm",(void*)f_4651},
{"f_4637ChickenBridge.scm",(void*)f_4637},
{"f_4608ChickenBridge.scm",(void*)f_4608},
{"f_4553ChickenBridge.scm",(void*)f_4553},
{"f_4560ChickenBridge.scm",(void*)f_4560},
{"f_4563ChickenBridge.scm",(void*)f_4563},
{"f_4569ChickenBridge.scm",(void*)f_4569},
{"f_4488ChickenBridge.scm",(void*)f_4488},
{"f_4497ChickenBridge.scm",(void*)f_4497},
{"f_4520ChickenBridge.scm",(void*)f_4520},
{"f_4510ChickenBridge.scm",(void*)f_4510},
{"f_4444ChickenBridge.scm",(void*)f_4444},
{"f_4432ChickenBridge.scm",(void*)f_4432},
{"f_4330ChickenBridge.scm",(void*)f_4330},
{"f_4282ChickenBridge.scm",(void*)f_4282},
{"f_3663ChickenBridge.scm",(void*)f_3663},
{"f_3667ChickenBridge.scm",(void*)f_3667},
{"f_3670ChickenBridge.scm",(void*)f_3670},
{"f_4096ChickenBridge.scm",(void*)f_4096},
{"f_4092ChickenBridge.scm",(void*)f_4092},
{"f_4088ChickenBridge.scm",(void*)f_4088},
{"f_3673ChickenBridge.scm",(void*)f_3673},
{"f_3796ChickenBridge.scm",(void*)f_3796},
{"f_3029ChickenBridge.scm",(void*)f_3029},
{"f_3802ChickenBridge.scm",(void*)f_3802},
{"f_3045ChickenBridge.scm",(void*)f_3045},
{"f_3890ChickenBridge.scm",(void*)f_3890},
{"f_3960ChickenBridge.scm",(void*)f_3960},
{"f_3061ChickenBridge.scm",(void*)f_3061},
{"f_3963ChickenBridge.scm",(void*)f_3963},
{"f_3093ChickenBridge.scm",(void*)f_3093},
{"f_4041ChickenBridge.scm",(void*)f_4041},
{"f_4067ChickenBridge.scm",(void*)f_4067},
{"f_4061ChickenBridge.scm",(void*)f_4061},
{"f_4050ChickenBridge.scm",(void*)f_4050},
{"f_3992ChickenBridge.scm",(void*)f_3992},
{"f_4002ChickenBridge.scm",(void*)f_4002},
{"f_4028ChickenBridge.scm",(void*)f_4028},
{"f_4022ChickenBridge.scm",(void*)f_4022},
{"f_4005ChickenBridge.scm",(void*)f_4005},
{"f_4015ChickenBridge.scm",(void*)f_4015},
{"f_4008ChickenBridge.scm",(void*)f_4008},
{"f_3969ChickenBridge.scm",(void*)f_3969},
{"f_3978ChickenBridge.scm",(void*)f_3978},
{"f_3972ChickenBridge.scm",(void*)f_3972},
{"f_3896ChickenBridge.scm",(void*)f_3896},
{"f_3914ChickenBridge.scm",(void*)f_3914},
{"f_3947ChickenBridge.scm",(void*)f_3947},
{"f_3933ChickenBridge.scm",(void*)f_3933},
{"f_3941ChickenBridge.scm",(void*)f_3941},
{"f_3924ChickenBridge.scm",(void*)f_3924},
{"f_3899ChickenBridge.scm",(void*)f_3899},
{"f_3811ChickenBridge.scm",(void*)f_3811},
{"f_3833ChickenBridge.scm",(void*)f_3833},
{"f_3880ChickenBridge.scm",(void*)f_3880},
{"f_3866ChickenBridge.scm",(void*)f_3866},
{"f_3874ChickenBridge.scm",(void*)f_3874},
{"f_3846ChickenBridge.scm",(void*)f_3846},
{"f_3849ChickenBridge.scm",(void*)f_3849},
{"f_3814ChickenBridge.scm",(void*)f_3814},
{"f_3831ChickenBridge.scm",(void*)f_3831},
{"f_3817ChickenBridge.scm",(void*)f_3817},
{"f_3688ChickenBridge.scm",(void*)f_3688},
{"f_3746ChickenBridge.scm",(void*)f_3746},
{"f_3749ChickenBridge.scm",(void*)f_3749},
{"f_3770ChickenBridge.scm",(void*)f_3770},
{"f_3781ChickenBridge.scm",(void*)f_3781},
{"f_3760ChickenBridge.scm",(void*)f_3760},
{"f_3694ChickenBridge.scm",(void*)f_3694},
{"f_3704ChickenBridge.scm",(void*)f_3704},
{"f_3740ChickenBridge.scm",(void*)f_3740},
{"f_3710ChickenBridge.scm",(void*)f_3710},
{"f_3725ChickenBridge.scm",(void*)f_3725},
{"f_3729ChickenBridge.scm",(void*)f_3729},
{"f_3733ChickenBridge.scm",(void*)f_3733},
{"f_3717ChickenBridge.scm",(void*)f_3717},
{"f_3559ChickenBridge.scm",(void*)f_3559},
{"f_3561ChickenBridge.scm",(void*)f_3561},
{"f_3609ChickenBridge.scm",(void*)f_3609},
{"f_3565ChickenBridge.scm",(void*)f_3565},
{"f_3568ChickenBridge.scm",(void*)f_3568},
{"f_3573ChickenBridge.scm",(void*)f_3573},
{"f_3594ChickenBridge.scm",(void*)f_3594},
{"f_3551ChickenBridge.scm",(void*)f_3551},
{"f_3553ChickenBridge.scm",(void*)f_3553},
{"f_3343ChickenBridge.scm",(void*)f_3343},
{"f_3360ChickenBridge.scm",(void*)f_3360},
{"f_3364ChickenBridge.scm",(void*)f_3364},
{"f_3310ChickenBridge.scm",(void*)f_3310},
{"f_3317ChickenBridge.scm",(void*)f_3317},
{"f_3261ChickenBridge.scm",(void*)f_3261},
{"f_3268ChickenBridge.scm",(void*)f_3268},
{"f_3326ChickenBridge.scm",(void*)f_3326},
{"f_3549ChickenBridge.scm",(void*)f_3549},
{"f_3526ChickenBridge.scm",(void*)f_3526},
{"f_3542ChickenBridge.scm",(void*)f_3542},
{"f_3388ChickenBridge.scm",(void*)f_3388},
{"f_3391ChickenBridge.scm",(void*)f_3391},
{"f_3415ChickenBridge.scm",(void*)f_3415},
{"f_3472ChickenBridge.scm",(void*)f_3472},
{"f_3478ChickenBridge.scm",(void*)f_3478},
{"f_3487ChickenBridge.scm",(void*)f_3487},
{"f_3496ChickenBridge.scm",(void*)f_3496},
{"f_3505ChickenBridge.scm",(void*)f_3505},
{"f_3514ChickenBridge.scm",(void*)f_3514},
{"f_3466ChickenBridge.scm",(void*)f_3466},
{"f_3421ChickenBridge.scm",(void*)f_3421},
{"f_3427ChickenBridge.scm",(void*)f_3427},
{"f_3433ChickenBridge.scm",(void*)f_3433},
{"f_3439ChickenBridge.scm",(void*)f_3439},
{"f_3445ChickenBridge.scm",(void*)f_3445},
{"f_3451ChickenBridge.scm",(void*)f_3451},
{"f_3292ChickenBridge.scm",(void*)f_3292},
{"f_3299ChickenBridge.scm",(void*)f_3299},
{"f_3282ChickenBridge.scm",(void*)f_3282},
{"f_3270ChickenBridge.scm",(void*)f_3270},
{"f_3238ChickenBridge.scm",(void*)f_3238},
{"f_3245ChickenBridge.scm",(void*)f_3245},
{"f_3252ChickenBridge.scm",(void*)f_3252},
{"f_3222ChickenBridge.scm",(void*)f_3222},
{"f_3229ChickenBridge.scm",(void*)f_3229},
{"f_3236ChickenBridge.scm",(void*)f_3236},
{"f_3210ChickenBridge.scm",(void*)f_3210},
{"f_3192ChickenBridge.scm",(void*)f_3192},
{"f_3174ChickenBridge.scm",(void*)f_3174},
{"f_3159ChickenBridge.scm",(void*)f_3159},
{"f_3153ChickenBridge.scm",(void*)f_3153},
{"f_3141ChickenBridge.scm",(void*)f_3141},
{"f_3123ChickenBridge.scm",(void*)f_3123},
{"f_3102ChickenBridge.scm",(void*)f_3102},
{"f_3070ChickenBridge.scm",(void*)f_3070},
{"f_3077ChickenBridge.scm",(void*)f_3077},
{"f_3012ChickenBridge.scm",(void*)f_3012},
{"f_3020ChickenBridge.scm",(void*)f_3020},
{"f_3002ChickenBridge.scm",(void*)f_3002},
{"f_3010ChickenBridge.scm",(void*)f_3010},
{"f_2996ChickenBridge.scm",(void*)f_2996},
{"f_2984ChickenBridge.scm",(void*)f_2984},
{"f_2960ChickenBridge.scm",(void*)f_2960},
{"f_2876ChickenBridge.scm",(void*)f_2876},
{"f_2855ChickenBridge.scm",(void*)f_2855},
{"f_2845ChickenBridge.scm",(void*)f_2845},
{"f_2833ChickenBridge.scm",(void*)f_2833},
{"f_2804ChickenBridge.scm",(void*)f_2804},
{"f_2792ChickenBridge.scm",(void*)f_2792},
{"f_2774ChickenBridge.scm",(void*)f_2774},
{"f_2756ChickenBridge.scm",(void*)f_2756},
{"f_2735ChickenBridge.scm",(void*)f_2735},
{"f_2729ChickenBridge.scm",(void*)f_2729},
{"f_2723ChickenBridge.scm",(void*)f_2723},
{"f_2704ChickenBridge.scm",(void*)f_2704},
{"f_2685ChickenBridge.scm",(void*)f_2685},
{"f_2679ChickenBridge.scm",(void*)f_2679},
{"f_2639ChickenBridge.scm",(void*)f_2639},
{"f_2620ChickenBridge.scm",(void*)f_2620},
{"f_2576ChickenBridge.scm",(void*)f_2576},
{"f_2570ChickenBridge.scm",(void*)f_2570},
{"f_2564ChickenBridge.scm",(void*)f_2564},
{"f_2558ChickenBridge.scm",(void*)f_2558},
{"f_2552ChickenBridge.scm",(void*)f_2552},
{"f_2529ChickenBridge.scm",(void*)f_2529},
{"f_2546ChickenBridge.scm",(void*)f_2546},
{"f_2471ChickenBridge.scm",(void*)f_2471},
{"f_2523ChickenBridge.scm",(void*)f_2523},
{"f_2507ChickenBridge.scm",(void*)f_2507},
{"f_2488ChickenBridge.scm",(void*)f_2488},
{"f_2383ChickenBridge.scm",(void*)f_2383},
{"f_2429ChickenBridge.scm",(void*)f_2429},
{"f_2377ChickenBridge.scm",(void*)f_2377},
{"f_2318ChickenBridge.scm",(void*)f_2318},
{"f_2331ChickenBridge.scm",(void*)f_2331},
{"f_2367ChickenBridge.scm",(void*)f_2367},
{"f_2312ChickenBridge.scm",(void*)f_2312},
{"f_2217ChickenBridge.scm",(void*)f_2217},
{"f_2221ChickenBridge.scm",(void*)f_2221},
{"f_2224ChickenBridge.scm",(void*)f_2224},
{"f_2236ChickenBridge.scm",(void*)f_2236},
{"f_2258ChickenBridge.scm",(void*)f_2258},
{"f_2211ChickenBridge.scm",(void*)f_2211},
{"f_2205ChickenBridge.scm",(void*)f_2205},
{"f_2199ChickenBridge.scm",(void*)f_2199},
{"f_2193ChickenBridge.scm",(void*)f_2193},
{"f_2187ChickenBridge.scm",(void*)f_2187},
{"f_2127ChickenBridge.scm",(void*)f_2127},
{"f_2139ChickenBridge.scm",(void*)f_2139},
{"f_2134ChickenBridge.scm",(void*)f_2134},
{"f_2129ChickenBridge.scm",(void*)f_2129},
{"f_2108ChickenBridge.scm",(void*)f_2108},
{"f_2102ChickenBridge.scm",(void*)f_2102},
{"f_2096ChickenBridge.scm",(void*)f_2096},
{"f_2014ChickenBridge.scm",(void*)f_2014},
{"f_2028ChickenBridge.scm",(void*)f_2028},
{"f_1995ChickenBridge.scm",(void*)f_1995},
{"f_1982ChickenBridge.scm",(void*)f_1982},
{"f_1972ChickenBridge.scm",(void*)f_1972},
{"f_1961ChickenBridge.scm",(void*)f_1961},
{"f_1954ChickenBridge.scm",(void*)f_1954},
{"f_1943ChickenBridge.scm",(void*)f_1943},
{"f_1905ChickenBridge.scm",(void*)f_1905},
{"f_1898ChickenBridge.scm",(void*)f_1898},
{"f_1823ChickenBridge.scm",(void*)f_1823},
{"f_1789ChickenBridge.scm",(void*)f_1789},
{"f_1762ChickenBridge.scm",(void*)f_1762},
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
