/*
 *  Scheme.cpp
 *  
 *
 *  Created by todd ingalls on 9/1/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "Scheme.h"

SchemeThread::SchemeThread(String name, ConsoleWindow *win) :
  Thread(name)
{
  console=win;
}

SchemeThread::~SchemeThread()
{
}

void SchemeThread::run() {
  int res;
  C_word k;
  C_word r;
  char buffer[8192];
  String text = T("Chicken Scheme");

  res = CHICKEN_initialize(0, 0, 0, CHICKEN_default_toplevel);
  if (res==0) {
    console->printError(T(">>> Error: Chicken failed to initialize.\n"));	
    return;
  }
  k = CHICKEN_run(CHICKEN_default_toplevel);
  k = CHICKEN_continue(k);
  res = CHICKEN_eval_string_to_string( (char*)"(chicken-version)", 
				       buffer, 8192);
  if (res>0) 
    text = text + T(", version ") + String(buffer).unquoted();
  text += T("\n(c) 2000-2007 Felix L. Winkelmann\n");

  console->printMessage(text);
  bzero(buffer, 8192);
  while ( !threadShouldExit() ) {
    wait(-1);
    // set console to typeout color for printing under eval
    console->setConsoleTextColor(ConsoleTheme::outputColor);
    res = CHICKEN_eval_string_to_string( (char*)EvalString, buffer, 8192);
    if (res==0) {
      CHICKEN_get_error_message(buffer, 8192);
      text=T(">>> ") + String(buffer) ;
      console->printError(text);
    }
    else {
      text=String(buffer);
      if (text != String::empty)
	console->printValues(text );
    }
    bzero(buffer, 8192);
  }	
}

