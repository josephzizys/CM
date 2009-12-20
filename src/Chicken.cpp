/*=======================================================================*
  Copyright (C) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#include <iostream>
#include "juce.h"
#include "chicken.h"
#include "Enumerations.h"
#include "ChickenBridge.h"
#include "Scheme.h"
#include "Console.h"
#include "CmSupport.h"

#define OUTSTRSIZE 8192
static char outstr[OUTSTRSIZE];
static bool chicken_run = true;


bool SchemeThread::init()
{
  int res;
  int hsize=500000;
  int ssize=64000;

  res = CHICKEN_initialize(hsize, ssize, 0, (void*)C_cm_toplevel);
  if (res==0)
    {
      std::cout << "CHICKEN_initialize failed.\n";
      return false;
    }
  res = CHICKEN_run(NULL);
  if (res==0)
    {
      std::cout << "CHICKEN_run failed.\n";
      return false;
    }
  /*
  res=CHICKEN_eval_string_to_string((char *)"(chicken-version)",
				    outstr, OUTSTRSIZE);
  if (res>0)
    {
      String str = String("Chicken ");
      str << String(outstr).unquoted()
	  << T(" ") << SysInfo::getCopyright(T("Felix L. Winkelmann\n"))
	  << SysInfo::getCMLogo() << T("\n" );
	Console::getInstance()->printOutput(str);
    }
  */
  CHICKEN_eval_string((char*)"(define *grace-std-out* (make-output-port print-output (lambda () #f)))", NULL);
  CHICKEN_eval_string((char*)"(current-output-port *grace-std-out*)", NULL);
  CHICKEN_eval_string((char*)"(define *grace-err-out* (make-output-port print-error (lambda () #f)))", NULL);
  CHICKEN_eval_string((char*)"(current-error-port *grace-err-out*)", NULL);

  memset(outstr, 0, OUTSTRSIZE);
  inputClosureGCRoot=CHICKEN_new_gc_root();
  CHICKEN_gc_root_set(inputClosureGCRoot, C_SCHEME_FALSE);
  return true;
}

void SchemeThread::cleanup()
{
  CHICKEN_delete_gc_root(inputClosureGCRoot);
}

String SchemeThread::getLispVersion()
{
  String str = T("Chicken ");
  int res=CHICKEN_eval_string_to_string((char *)"(chicken-version)",
					outstr, OUTSTRSIZE);
  if (res>0)
    str << String(outstr).unquoted();
  else
    str << T("?.?.?");
  str << T(" ") << SysInfo::getCopyright(T("Felix L. Winkelmann"));
  return str;
}

bool SchemeThread::isMidiInputHook()
{
  return (CHICKEN_gc_root_ref(inputClosureGCRoot) != C_SCHEME_FALSE);
}

void SchemeThread::setMidiInputHook(SCHEMEPROC hook)
{
  clearMidiInputHook();
  CHICKEN_gc_root_set(inputClosureGCRoot, hook);
}

void SchemeThread::clearMidiInputHook()
{
  CHICKEN_gc_root_set(inputClosureGCRoot, C_SCHEME_FALSE);
}

//
// implementation specific Node API
//

// method for process node
SchemeNode::SchemeNode(int _type, double _time, SCHEMEPROC c, int _id)
  : time (0.0),
    start (0.0), 
    elapsed (0.0),
    type (0),
    expr (String::empty),
    mmess(0xff)
{

  type = _type;
  id = _id;
  time = _time;
  start = _time;
  closureGCRoot = CHICKEN_new_gc_root();
  CHICKEN_gc_root_set(closureGCRoot, c);
}

void SchemeNode::applyEvalNode()
{
  int res=CHICKEN_eval_string_to_string((char *)expr.toUTF8(),
					schemeThread->evalBuffer,
					8192);
  if (res>0)
    {
      // UGLY! dont print if return value is "#<unspecfied>"
      if (strcmp(schemeThread->evalBuffer, "#<unspecified>") != 0)
	{
	  int len=strlen(schemeThread->evalBuffer);
	  // add NewLine for terminal output
	  if ((len>0) && (len<8191))
	    {
	      char* p=schemeThread->evalBuffer+len;
	      *p='\n';
	      *(p+1)=NULL;
	    }
	  Console::getInstance()->printValues(schemeThread->evalBuffer);
	}
    }
  else
    {
      CHICKEN_get_error_message(schemeThread->evalBuffer,
				8192);
      Console::getInstance()->printError(schemeThread->evalBuffer);
    }
  memset(schemeThread->evalBuffer, 0, 8192);
}

void SchemeNode::applyMidiInputHookNode()
{
  int op=(mmess.getRawData()[0] & 0xf0)>>4;
  int ch=mmess.getChannel()-1;
  int d1=mmess.getRawData()[1] & 0x7f;
  int d2=0;
  if (mmess.getRawDataSize()>2)
    d2=mmess.getRawData()[2] & 0x7f;
  C_save(C_fix(op));
  C_save(C_fix(ch));
  C_save(C_fix(d1));
  C_save(C_fix(d2));
  C_word hook=CHICKEN_gc_root_ref(schemeThread->inputClosureGCRoot);
  int val=C_unfix(C_callback(hook, 4));
  if (val<0)
    {
      Console::getInstance()->printError(T("Clearing Midi input hook.\n"));
      schemeThread->clearMidiInputHook();
    }
}

double SchemeNode::applyProcessNode(double elapsed)
{
  double delta;
  C_word closure = CHICKEN_gc_root_ref(closureGCRoot);
  elapsed_ptr = C_alloc(C_SIZEOF_FLONUM);
  elapsed_word = C_flonum( &elapsed_ptr, elapsed);
  C_save(elapsed_word);
  delta=C_c_double(C_callback(closure, 1));
  if (delta < 0) // process signals all done
    CHICKEN_delete_gc_root(closureGCRoot);
  return delta;
}


/*
void chicken_print_message(char* st)
{
  // attempt at buffering: if string ends with #\Return, send string
  // AND trigger update else send string without triggering update
  String s=String(st);
  if ( s.endsWithChar('\n') )
    Console::getInstance()->printMessage(s, true);
  else
    Console::getInstance()->printMessage(s, false);
}

void chicken_print_error(char* st)
{
  // attempt at buffering: if string ends with #\Return, send string
  // AND trigger update else send string without triggering update
  String s=String(st);
  if ( s.endsWithChar('\n') )
    Console::getInstance()->printError(s, true);
  else
    Console::getInstance()->printError(s, false);
}

CHICKEN_eval_string((char *)"(current-output-port (make-output-port (foreign-lambda void \"chicken_print_message\" c-string) (lambda () #f)))", NULL);

CHICKEN_eval_string((char *)"(current-error-port (make-output-port (foreign-lambda void \"chicken_print_error\" c-string) (lambda () #f)))", NULL);

*/
















