/*
 *  Scheme.cpp
 *  
 *
 *  Created by todd ingalls on 9/1/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "Scheme.h"
#include "Scheme.h"
#include "ChickenBridge.h"

SchemeMessage::SchemeMessage( Node *n ) 
{ 
	type = SCHEME_NODE; 	
	node = n; 
}

SchemeMessage::SchemeMessage( String str ) 
{ 
	type = SCHEME_STRING; 
	string = str; 
}

SchemeMessage::~SchemeMessage() 
{
}


SchemeThread::SchemeThread(String name, ConsoleWindow *win) :
  Thread(name)
{
  console=win;
}

SchemeThread::~SchemeThread()
{
}

void SchemeThread::handleMessage(SchemeMessage* schemeMessage)
{
  String text;

  switch (schemeMessage->type) 
    {
    case SCHEME_STRING:
      C_word res;	
      char buffer[8192];      
      res = CHICKEN_eval_string_to_string( (char*)((String&)schemeMessage->string).toUTF8(), buffer, 8192 );
      if (res==0) {
	CHICKEN_get_error_message(buffer, 8192);
	text=T(String(buffer));
	console->printError(text);
	bzero(buffer, 8192);
      } else
	console->printMessage(String(buffer) + T("\n"));

      
      break;
      
    case SCHEME_NODE:
      double nexttime;
      nexttime = G_apply_process(schemeMessage->node->closure);
      if(nexttime == -1)
	delete  schemeMessage->node ;
      else
	schemeMessage->node->queue->reinsertNode(schemeMessage->node, nexttime);
      break;
      
    default:
      break;
    }
}

void SchemeThread::insertMessage(SchemeMessage* schemeMessage)
{
  printf("inserting message\n");
  messageBuffer.lockArray();
  messageBuffer.add( schemeMessage );
  messageBuffer.unlockArray();
  notify();
}

void SchemeThread::run() {
  int res;
  C_word k;
  C_word r;
  char buffer[8192];
  String text = T("Chicken Scheme");
  

  res = CHICKEN_initialize(0, 0, 0, (void*)C_grace_toplevel);
  
  if (res==0) {
    console->printError(T(">>> Error: Chicken failed to initialize.\n"));	
    return;
  }
  res = CHICKEN_run(NULL);
  
  if (res==0) {
    console->printError(T(">>> Error: Chicken failed to initialize.\n"));	
    return;
  }
  

  res = CHICKEN_eval_string_to_string( (char*)"(chicken-version)", 
				       buffer, 8192);
  if (res>0) 
    text = text + T(", version ") + String(buffer).unquoted();
  text += T("\n(c) 2000-2007 Felix L. Winkelmann\n");
  
  console->printMessage(text);
  bzero(buffer, 8192);

  if (res==0) {
    console->printError(T(">>> Error: Chicken failed to initialize.\n"));	
    return;
  }
  
  CHICKEN_eval_string("(require-extension srfi-18)", &r);

  
  CHICKEN_eval_string("(define *grace-std-out*  (make-output-port print-message (lambda () #f)))", NULL);
  CHICKEN_eval_string("(current-output-port *grace-std-out*)", NULL);
  CHICKEN_eval_string("(define *grace-err-out*  (make-output-port print-error (lambda () #f)))", NULL);
  CHICKEN_eval_string("(current-error-port *grace-err-out*)", NULL);

  while ( !threadShouldExit() ) {
    while( messageBuffer.size() > 0 ) {
      handleMessage( messageBuffer[0] );
      messageBuffer.remove(0, true); 
    }
    wait(-1);
  }	
}

 
