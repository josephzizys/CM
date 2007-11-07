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

SchemeNode::SchemeNode(double _time, int _type, C_word c, int _id)
  : time (0.0),start (0.0),type (0), expr (String::empty) 
{ 
  type = _type;
  id = _id;
  if(_time == 0.0) 
    time = Time::getMillisecondCounterHiRes();
  else
    time = _time + Time::getMillisecondCounterHiRes();
  start = time;
  closureGCRoot = CHICKEN_new_gc_root();
  CHICKEN_gc_root_set(closureGCRoot, c);
}

SchemeNode::SchemeNode(double _time, int _type, String s)
  : time (0.0),start (0.0),type (0), closure(0), id (-1)
{ 
  type = EXPR;
  expr=s;
  time = 0.0; //will always be ready to call
}

SchemeNode::SchemeNode(double _time, int _type)
  : start (0.0), closure (0), expr (String::empty), id (-1)
{ 
  time = _time;
  type = _type;
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
      double nexttime;
      closure = CHICKEN_gc_root_ref(closureGCRoot);
      elapsed_ptr = C_alloc(1); 
      // Time format milliseconds or seconds
      if ( schemeThread->isTimeMilliseconds() ) {
	elapsed_word = C_flonum( &elapsed_ptr, time - start); 
	C_save( elapsed_word );
	nexttime = C_c_double( C_callback(closure, 1));
      }
      else {
	elapsed_word = C_flonum( &elapsed_ptr, (time - start)/1000.0); 
	C_save( elapsed_word );
	nexttime = C_c_double( C_callback(closure, 1)) * 1000.0 ;
      }
      //      offset = Time::getMillisecondCounterHiRes() - curtime;
      if (nexttime < 0) {
        return more;
      } 
      else {
        more=true;
        time += nexttime;
	//	time += nexttime + offset;
      }
    }
    break;

  case PROCEDURE:
    {
      C_word closure = CHICKEN_gc_root_ref(closureGCRoot);
      C_callback(closure, 0);
    }
    break;

  case PAUSE :
    //printf ("processing pause node :(\n");
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
  : Thread(name), pausing (false), timemsec (true)
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
  pausing=false;
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
      wait(1);
    }
    wait(-1);
  }
}

void SchemeThread::clear()
{
  // this should NEVER be called from scheme code (an EVAL node) or
  // else the run() loop will bomb since it assumes index[0] exists
  schemeNodes.lockArray();
  schemeNodes.clear();
  schemeNodes.unlockArray();
}

void SchemeThread::addNode(int type, double _time, C_word c, int _id)
{
  SchemeNode *n = new SchemeNode(_time, type, c, _id);
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

void SchemeThread::setPaused(bool p) {
  if (p) {
    // pause the scheduler.
    // this cannot really pause the Thread or else evalling wont work.
    // so we effect a pause by hand inserting a PAUSE node at the
    // head of the queue with a 1hr future time stamp, which then
    // keeps any of nodes further down the line from being processed
    // by the scheduler
    if (pausing) return;
    double delta=Time::getMillisecondCounterHiRes();
    // calc time 1 hr in the future
    SchemeNode *n = new SchemeNode( delta + (1000.0 * 60.0 * 60),
				    SchemeNode::PAUSE);
    // cache start time of pause in node
    n->start=delta;
    schemeNodes.lockArray();
    // the eval node that got us here is at queu index 0 so add pause
    // at index 1 so that it becomes the head of the queue after the
    // eval node is popped
    schemeNodes.insert(1,n); 
    schemeNodes.unlockArray();
    pausing=true;
    notify();
  }
  else {
    // continue from a pause.
    // to stop the pause we add the pause delta (time-start) to every
    // node above the pause and then remove the pause node.
    if (! pausing) return;
    int i;
    schemeNodes.lockArray();
    // search for the pause node...
    for (i=0; i<schemeNodes.size(); i++) {
      //printf("node[%d].type=%d\n", i, schemeNodes[i]->type);
      if ( schemeNodes[i]->type == SchemeNode::PAUSE )
	break;
    }
    if (i == schemeNodes.size() ) {
      printf("FAILED TO FIND PAUSE NODE!\n");
      schemeNodes.unlockArray();
      return;
    }
    // now increment all nodes above the pause node by pause amount
    double delta=Time::getMillisecondCounterHiRes() - schemeNodes[i]->start;
    //printf("pause node at=%d, pause dur=%d\n", i, (int)delta);
    for (int j=i+1; j< schemeNodes.size(); j++) {
      schemeNodes[j]->start += delta;
      schemeNodes[j]->time += delta;    
    }
    schemeNodes.remove(i, true);
    schemeNodes.unlockArray();
    pausing=false;
  }
}

void SchemeThread::stop(int id) {
  // stop all process with id from running. if id=-1 then stop all
  // processes. iterate queue in reverse order so removal index always
  // valid. do NOT touch index 0 since that's the (eval) node that got
  // us here!
  schemeNodes.lockArray();
  if (id==-1) { 
    for (int i=schemeNodes.size()-1; i>0; i--)
      if (schemeNodes[i]->type == SchemeNode::PROCESS)
	schemeNodes.remove(i,true);
  }
  else {
    // else selectively remove all nodes with id process queue in
    // reverse order so removal index always valid
    for (int i=schemeNodes.size()-1; i>0; i--)
      if (schemeNodes[i]->id == id)
	schemeNodes.remove(i,true);
  }
  schemeNodes.unlockArray();
}

