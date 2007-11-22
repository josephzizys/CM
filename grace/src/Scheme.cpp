/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

#include "Grace.h"
#include "Scheme.h"
#include "ChickenBridge.h"

#define SCHEME_DEBUG 1

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
  // MOVED THIS TO PROCESS() TO SEE IF THIS CAUSED THE RANDOM CRASHING...
  //  if(type ==  PROCESS || type == PROCEDURE) {
  //    CHICKEN_delete_gc_root(closureGCRoot);
  //  } 
}

bool SchemeNode::process(double curtime) {
  bool more=false;
  
  switch (type) {
  case EXPR :
    {
      if ( SCHEME_DEBUG )
	printf("\ncalling eval node %d...\n", nodeid);
      C_word res;	
      bzero(schemeThread->evalBuffer, 8192);
      bzero(schemeThread->errorBuffer, 8192);
      res = CHICKEN_eval_string_to_string( (char *)expr.toUTF8(),
					   schemeThread->evalBuffer,
                                           8192);
      if ( res==0 ) {
	printf("Scheme Error: %s\n", schemeThread->errorBuffer);
	schemeThread->reportChickenError();
      }
      else {
	printf("Returned: %s\n", schemeThread->evalBuffer);
	String s=String(schemeThread->evalBuffer);
	if ( !s.endsWithChar('\n') )
	  s << T("\n");
	schemeThread->console->
	  postConsoleTextMessage(s, ConsoleMessage::VALUES);
      }
      expr=String::empty;
    }
    break;
          
  case PROCESS:
    {
      if ( SCHEME_DEBUG )
	printf("\ncalling process node %d...\n", nodeid);
      double nexttime;
      closure = CHICKEN_gc_root_ref(closureGCRoot);
      // Time format is either int milliseconds or float seconds
      // MILLI
      if ( 0 ) { //schemeThread->isTimeMilliseconds()
	elapsed_word = C_fix( (int)(time-start)); 
	C_save( elapsed_word );

	nexttime = C_c_double( C_callback(closure, 1));
      }
      else {
	elapsed_ptr = C_alloc(C_SIZEOF_FLONUM); 
	// MILLI
	elapsed_word = C_flonum( &elapsed_ptr, 
				 (double)((time - start)/1000.0)); 
	C_save( elapsed_word );
	nexttime = C_c_double( C_callback(closure, 1)) * 1000.0 ;
      }
      if ( SCHEME_DEBUG )
	printf("...done calling process node %d\n", nodeid);

      //      offset = Time::getMillisecondCounterHiRes() - curtime;
      if (nexttime < 0) {
	CHICKEN_delete_gc_root(closureGCRoot);
        return false;
      } 
      else {
        more=true;
	//        time += nexttime;
	time = (Time::getMillisecondCounterHiRes() + nexttime) ;
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
  : Thread(name), pausing (false), timemsec (false)
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
  if (m == 1)
    printf("\nMAJOR GC\n\n");
  else
    printf("minor GC\n");
}

void SchemeThread::reportChickenError (String text) {
  // if text is null we are reporting a runtime error so we fetch the
  // text from the error buffer and insure that it ends with \n
  if ( text == String::empty ) {
    CHICKEN_get_error_message(errorBuffer, 8192);
    text=T(">>> ") + T(String(errorBuffer));
    if ( ! text.endsWithChar('\n') )
      text << T("\n");
  }  
  console->postConsoleTextMessage(text, ConsoleMessage::ERROR);
}

bool SchemeThread::init() {
  int res;
  C_word r;
  char buffer[8192];
  String text = T("Chicken Scheme");
  GracePreferences* prefs=GracePreferences::getInstance();
  int hsz=prefs->getSchemeHeapSize();
  int ssz=prefs->getSchemeStackSize();

  if ( SCHEME_DEBUG )
    printf("Chicken init: heap=%d stack=%d\n", hsz, ssz);

  /* chicken/runtime.c :
    #define DEFAULT_STACK_SIZE             64000
    #define DEFAULT_SYMBOL_TABLE_SIZE      2999
    #define DEFAULT_HEAP_SIZE              500000
    #define MINIMAL_HEAP_SIZE              500000
    #define DEFAULT_MAXIMAL_HEAP_SIZE      2147483632
  */

  // default to 4x Chicken's minimum heap size
  res = CHICKEN_initialize(hsz, ssz, 0, (void*)C_grace_toplevel);

  //  res = CHICKEN_initialize(0, 0, 0,  (void*)C_grace_toplevel);
  //  res = CHICKEN_initialize(20000000, 64000, 0, (void*)C_grace_toplevel);

  if (res==0) {
    reportChickenError( T(">>> Error: Chicken failed to initialize.\n") );
    return false;
  }
  res = CHICKEN_run(NULL);
  if (res==0) {
    reportChickenError( T(">>> Error: Chicken failed to initialize.\n") );
    return false;
  }
  res = CHICKEN_eval_string_to_string( (char*)"(chicken-version)", 
				       buffer, 8192);
  if (res>0) 
    text = text + T(", version ") + String(buffer).unquoted();
  text += T("\n(c) 2000-2007 Felix L. Winkelmann\n");
  // console->printMessage(text, true);
  console->postConsoleTextMessage(text);
  //console->doAsyncUpdate();	
  bzero(buffer, 8192);
  if (res==0) {
    reportChickenError( T(">>> Error: Chicken failed to initialize.\n") );
    return false;
  }
  CHICKEN_eval_string("(require-extension srfi-18)", &r);
  CHICKEN_eval_string("(require-extension srfi-1)", &r);
  CHICKEN_eval_string("(define *grace-std-out* (make-output-port print-message (lambda () #f)))", NULL);
  res = CHICKEN_eval_string("(current-output-port *grace-std-out*)", NULL);
  if ( res==0 )
    reportChickenError();
  res = CHICKEN_eval_string("(define *grace-err-out* (make-output-port print-error (lambda () #f)))", NULL);
  if ( res==0 )
    reportChickenError();
  res = CHICKEN_eval_string("(current-error-port *grace-err-out*)", NULL);
  if ( res==0 )
    reportChickenError();
  if ( SCHEME_DEBUG )
    C_post_gc_hook = postGCHook;
  return true;
}

void SchemeThread::run()
{
  double qtime, utime;
  SchemeNode* node;
  // start chicken  
  if (! init() ) return;
  pausing=false;
  while ( true ) {
    if ( threadShouldExit() )
      break;
    while ( true ) {     
      schemeNodes.lockArray();
      node=schemeNodes.getFirst();
      schemeNodes.unlockArray();      
      if ( node == NULL ) {
	break;
      }
      qtime=node->time;
      utime = Time::getMillisecondCounterHiRes() ;
      // this should probably test if the difference between qtime and
      // utime is less that 1ms, if not then it probably shouldn't
      // sleep (?)
      if ( qtime > utime ) {
	wait(1);
      }
      else {
	schemeNodes.lockArray();
	schemeNodes.remove(0, false);
	schemeNodes.unlockArray();
	bool keep=node->process(0.0);
	if ( keep ) {
	  if ( SCHEME_DEBUG )
	    printf("reinserting process node %d...\n", node->nodeid);
	  schemeNodes.lockArray();
	  schemeNodes.addSorted(comparator,node); 
	  //          schemeNodes.remove(0, false);
	  schemeNodes.unlockArray();
	  if ( SCHEME_DEBUG )
	    printf("...done reinserting process node %d\n", node->nodeid);
	}
	else {
	  int myid=node->nodeid;
	  int mytyp=node->type;
	  delete node;
	  if ( SCHEME_DEBUG ) {
	    if (mytyp==SchemeNode::PROCESS)
	      printf("deleted process node %d\n", myid);	
	    else
	      printf("deleted eval node %d\n", myid);
	    schemeNodes.lockArray();
	    int mysize=schemeNodes.size();
	    printf ("Queue size: %d\n", mysize);
	    if (mysize>0) {
	    printf ("Remaining nodes: ");
	    for (int i=0;i<mysize;i++)
	      printf(" %d",schemeNodes[i]->nodeid);
	    printf("\n");
	    }
	    schemeNodes.unlockArray();	
	  }
	  //	  schemeNodes.lockArray();
	  //          schemeNodes.remove(0, true);
	  //mysize=schemeNodes.size();
	  //schemeNodes.unlockArray();
	  //printf("...done removing %d, array size now %d\n", myid, mysize);	  
	}
      }
      node=NULL;
    }
    wait(-1);
  }
}

/*** THIS VERSION WORKS
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
	//was: process(curr = Time::getMillisecondCounterHiRes())
        if ( schemeNodes.getFirst()->process( 0.0  ) ) {
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
***/

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
  static int nextid=1000;
  SchemeNode *n = new SchemeNode(_time, SchemeNode::PROCESS, c, _id);
  n->nodeid=++nextid;
  if ( SCHEME_DEBUG )
    printf("adding process node %d...\n", n->nodeid);
  n->schemeThread = this;
  schemeNodes.lockArray();
  schemeNodes.addSorted(comparator, n);
  schemeNodes.unlockArray();
  notify();
  if ( SCHEME_DEBUG )
    printf("...done adding process node %d\n", n->nodeid);
}

void SchemeThread::addNode(int type, double _time, String s) {
  static int nextid=000;
  SchemeNode *n = new SchemeNode(_time, type, s);
  n->nodeid=++nextid;
  if ( SCHEME_DEBUG )
    printf("adding eval node %d...\n", n->nodeid);
  n->schemeThread = this;
  schemeNodes.lockArray();
  schemeNodes.addSorted(comparator, n);
  schemeNodes.unlockArray();
  notify();
  if ( SCHEME_DEBUG )
    printf("...done adding eval node %d\n", n->nodeid);
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

