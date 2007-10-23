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
  string = 0;
}

SchemeMessage::SchemeMessage( String str ) 
{ 
  type = SCHEME_STRING; 
  string = str; 
  node = 0;
}

SchemeMessage::~SchemeMessage() 
{
}


SchemeThread::SchemeThread(String name, ConsoleWindow *win) :
Thread(name)
{
  console=win;
  evalBuffer = new char[8192];
  errorBuffer = new char[8192];
}

SchemeThread::~SchemeThread()
{
  
}

void SchemeThread::handleMessage(SchemeMessage* schemeMessage)
{
  String text;
  C_word closure;
  
  switch (schemeMessage->type) 
  {
    case SCHEME_STRING:
      int res;	
      bzero(evalBuffer, 8192);
      bzero(errorBuffer, 8192);

      res = CHICKEN_eval_string_to_string( (char*)(schemeMessage->string).toUTF8(), evalBuffer, schemeMessage->string.length() );
      
      if (res==0) {
        
        CHICKEN_get_error_message(errorBuffer, strlen(errorBuffer));
        text=T(String(errorBuffer));
        console->printError(text);
      } else
        console->printValues(String(evalBuffer) + T("\n"));
       messageBuffer.removeObject(schemeMessage, true);
      break;
      
    case SCHEME_NODE:
      if(schemeMessage->node->type == Node::PROCESS ) {
        double nexttime ;
        double elapsed;
        C_word *now_ptr;
        C_word *elapsed_ptr;
        C_word now_word;
        C_word elapsed_word;

	//        now_ptr = C_alloc(1);
	//        elapsed_ptr = C_alloc(1);
               
        closure = CHICKEN_gc_root_ref(schemeMessage->node->gcroot);
	//        schemeMessage->node->now = Time::getMillisecondCounterHiRes();
	//        now_word = C_flonum( &now_ptr, schemeMessage->node->now);
	//        elapsed = schemeMessage->node->now - schemeMessage->node->start;
	//        elapsed_word = C_flonum( &elapsed_ptr, elapsed); 
	//        C_save( now_word );
	//        C_save( elapsed_word );

	//        nexttime = C_c_double( C_callback(closure, 2));

        nexttime = C_c_double( C_callback(closure, 0));
	printf("nexttime=%d\n", nexttime);
        if(nexttime == -1) {
          delete schemeMessage->node;
          messageBuffer.removeObject(schemeMessage, true);
        } else {
          schemeMessage->node->queue->reinsertNode(schemeMessage->node, nexttime);
          messageBuffer.removeObject(schemeMessage, true);
        }
        
      } else {
        closure = CHICKEN_gc_root_ref(schemeMessage->node->gcroot);
        C_callback(closure, 0);
        delete schemeMessage->node;
        messageBuffer.removeObject(schemeMessage, true);
      }
      break;
      
    default:
      break;
  }

}

void SchemeThread::insertMessage(SchemeMessage* schemeMessage)
{
  messageBuffer.lockArray();
  messageBuffer.add( schemeMessage );
  messageBuffer.unlockArray();
  notify();
}


void SchemeThread::run() {
  int res;
  C_word r;
  char buffer[8192];
  String text = T("Chicken Scheme");
  
  res = CHICKEN_initialize(0, 0, 0,  (void*)C_grace_toplevel);
  
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
      messageBuffer.lockArray();
      handleMessage( messageBuffer[0] );
      messageBuffer.unlockArray();
      }
    wait(-1);
  }
  
}


