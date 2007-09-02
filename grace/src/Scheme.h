/*
 *  Scheme.h
 *  
 *
 *  Created by todd ingalls on 9/1/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __GRACESCHEME__
#define __GRACESCHEME__
#include "juce.h"
#include "chicken.h"

class ConsoleWindow;

#include "Console.h"

class SchemeThread : public Thread
{
 public:	
  SchemeThread(String name, ConsoleWindow* win);
  ~SchemeThread();
  void run();
  ConsoleWindow* console;
  String EvalString;
};

#endif
