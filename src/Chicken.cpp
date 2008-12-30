/*************************************************************************
 * Copyright (C) 2008, Rick Taube.                                       *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

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

bool Scheme::init()
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
  memset(outstr, 0, OUTSTRSIZE);
  return true;
}

void Scheme::cleanup()
{
}

//
// implementation specific Node API
//

// method for process node
SchemeNode::SchemeNode(int _type, double _time, SCHEMEPROC c, int _id)
  : time (0.0),
    start (0.0), 
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

void SchemeNode::applyInHookNode()
{
  C_word *mmess_ptr;
  mmess_ptr = C_alloc( sizeof(MidiMessage*) );
  C_save(C_mpointer(&mmess_ptr , (void*)&mmess));
  C_word closure = CHICKEN_gc_root_ref(schemeThread->inputClosureGCRoot);
  C_callback(closure, 1);
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

