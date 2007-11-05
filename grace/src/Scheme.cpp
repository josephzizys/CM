/*
 *  Nodes.cpp
 *  rker
 *
 *  Created by Todd Ingalls on 9/24/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "Grace.h"
#include "Scheme.h"
#include "ChickenBridge.h"

// 
//  Nodes
//



SchemeNode::SchemeNode(double _time, int _type, C_word c)
: time (0.0),start (0.0),type (0), expr (String::empty)
{ 
  type = _type;
     
  if(_time == 0.0) 
    time = Time::getMillisecondCounterHiRes();
  else
    time = _time + Time::getMillisecondCounterHiRes();

  start = time;
   
  closureGCRoot = CHICKEN_new_gc_root();
  CHICKEN_gc_root_set(closureGCRoot, c);
}

SchemeNode::SchemeNode(double _time, int _type, String s)
: time (0.0),start (0.0),type (0), closure(0)
{ 
  type = EXPR;
  expr=s;
  time = 0.0; //will always be ready to call
}

SchemeNode::~SchemeNode(){ 
  if(type ==  PROCESS || type == PROCEDURE) {
    CHICKEN_delete_gc_root(closureGCRoot);
  } 
}

bool SchemeNode::process(double curtime) {
  bool more=false;
  
  switch (type) {
    case EXPR :
    {
      C_word res;	
      bzero(schemeThread->evalBuffer, 8192);
      bzero(schemeThread->errorBuffer, 8192);
      res = CHICKEN_eval_string_to_string( (char *)expr.toUTF8(), schemeThread->evalBuffer,
                                           8192);
      if ( res==0 ) {
        CHICKEN_get_error_message(schemeThread->errorBuffer, 8192);
	//	String text=T(String(schemeThread->errorBuffer));
	//	schemeThread->console->printError(text);
        printf(">>> %s\n", schemeThread->errorBuffer);
      }
      else {
	//        schemeThread->console->printValues(String(schemeThread->evalBuffer) + T("\n"));
	printf("*** Value: %s\n", schemeThread->evalBuffer);
      }
    }
      break;
          
    case PROCESS:
    {
      double nexttime;//, offset; 
      
      closure = CHICKEN_gc_root_ref(closureGCRoot);
      elapsed_ptr = C_alloc(1); 
      elapsed_word = C_flonum( &elapsed_ptr, time - start); 
      
      C_save( elapsed_word );
      nexttime = C_c_double( C_callback(closure, 1));
      
//      offset = Time::getMillisecondCounterHiRes() - curtime;

      if (nexttime < 0) {
        return more;
      } 
      else {
        more=true;
        time += nexttime;
//        time += nexttime + offset;
        
      }
    }
      break;

    case PROCEDURE:
      {
      C_word closure = CHICKEN_gc_root_ref(closureGCRoot);
      C_callback(closure, 0);
      }
      break;

    default:
      break;
  }	
  return more;
}

//
// Scheduler
//

SchemeThread::SchemeThread(String name, ConsoleWindow *win)
: Thread(name)
{	
  console = win;
  evalBuffer = new char[8192];
  errorBuffer = new char[8192];
}

SchemeThread::~SchemeThread()
{
  delete evalBuffer;
  delete errorBuffer;
}

void postGCHook(int m, long ms)
{
  if(m == 1)
    printf("major gc - %i\n", ms);
}

bool SchemeThread::init() {
  int res;
  C_word r;
  char buffer[8192];
  String text = T("Chicken Scheme");
  
 // res = CHICKEN_initialize(20000000,  64000,  0, (void*)C_grace_toplevel);
  
  res = CHICKEN_initialize(0, 0, 0,  (void*)C_grace_toplevel);
  if (res==0) {
    console->printError(T(">>> Error: Chicken failed to initialize.\n"));	
    return false;
  }
  res = CHICKEN_run(NULL);
  if (res==0) {
    console->printError(T(">>> Error: Chicken failed to initialize.\n"));	
    return false;
  }
  res = CHICKEN_eval_string_to_string( (char*)"(chicken-version)", buffer, 8192);
  if (res>0) 
    text = text + T(", version ") + String(buffer).unquoted();
  text += T("\n(c) 2000-2007 Felix L. Winkelmann\n");
  console->printMessage(text);
  bzero(buffer, 8192);
  if (res==0) {
    console->printError(T(">>> Error: Chicken failed to initialize.\n"));	
    return false;
  }
 // C_post_gc_hook = postGCHook;
  CHICKEN_eval_string("(require-extension srfi-18)", &r);
  CHICKEN_eval_string("(require-extension srfi-1)", &r);
  //  CHICKEN_eval_string("(require-extension chicken-more-macros)", &r);
  
  CHICKEN_eval_string("(define *grace-std-out*  (make-output-port print-message (lambda () #f)))", NULL);
  res = CHICKEN_eval_string("(current-output-port *grace-std-out*)", NULL);
  if ( res==0 ) {
    CHICKEN_get_error_message(errorBuffer, 8192);
    String text=T(String(errorBuffer));
    console->printError(text);
    //        printf(">>> %s\n", schemeThread->errorBuffer);
  }
  res = CHICKEN_eval_string("(define *grace-err-out*  (make-output-port print-error (lambda () #f)))", NULL);
  if ( res==0 ) {
    CHICKEN_get_error_message(errorBuffer, 8192);
    String text=T(String(errorBuffer));
    console->printError(text);
    //        printf(">>> %s\n", schemeThread->errorBuffer);
  }
  res = CHICKEN_eval_string("(current-error-port *grace-err-out*)", NULL);
  if ( res==0 ) {
    CHICKEN_get_error_message(errorBuffer, 8192);
    String text=T(String(errorBuffer));
    console->printError(text);
    //        printf(">>> %s\n", schemeThread->errorBuffer);
  }
  
  return true;
}


void SchemeThread::run()
{
  // start chicken  
  if (! init() ) return;
  double curr;
  
  while( !threadShouldExit() ) {
    
    while(schemeNodes.size() > 0) {     
      curr = Time::getMillisecondCounterHiRes() ;
      
      while ( schemeNodes.getFirst()->time <= curr ) {
        
        if ( schemeNodes.getFirst()->process( curr = Time::getMillisecondCounterHiRes()  ) ) {
          schemeNodes.addSorted(comparator, schemeNodes.getFirst()); 
          schemeNodes.remove(0, false);
        }
        else 
          schemeNodes.remove(0, true);
    
        if(schemeNodes.size() == 0) 
          break;

      }
      usleep(100);

    }
    wait(-1);
  }
  
}

void SchemeThread::clear()
{
  schemeNodes.lockArray();
  schemeNodes.clear();
  schemeNodes.unlockArray();
}


void SchemeThread::addNode(int type, double _time, C_word c)
{
  SchemeNode *n = new SchemeNode(_time, type, c);
  n->schemeThread = this;
  schemeNodes.lockArray();
  schemeNodes.addSorted(comparator, n);
  schemeNodes.unlockArray();
  notify();
}

void SchemeThread::addNode(int type, double _time, String s) {
  SchemeNode *n = new SchemeNode(_time, type, s);
  n->schemeThread = this;
  schemeNodes.lockArray();
  schemeNodes.addSorted(comparator, n);
  schemeNodes.unlockArray();
  notify();
}  
