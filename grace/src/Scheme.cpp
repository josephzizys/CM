/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

#include "Grace.h"
#include "Scheme.h"
#include "ChickenBridge.h"

#define SCHEME_DEBUG 0
// 1= trace scheme entry/exit points
// 2= include gc info in trace
// 3= include node creation/insertion/deletion info in tracce

// 
//  Nodes
//

SchemeNode::SchemeNode(double _time, int _type, C_word c, int _id)
  : time (0.0),start (0.0),type (0), expr (String::empty) , mmess(0)
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

SchemeNode::SchemeNode(double _time, int _type, String _expr)
  : time (0.0),start (0.0),type (0), closure(0), id (-1), mmess(0)
{ 
  //  type = EXPR;
  type=_type;
  expr=_expr;
  time = 0.0; //will always be ready to call
}

SchemeNode::SchemeNode(double _time, int _type)
  : start (0.0), closure (0), expr (String::empty), id (-1), mmess(0)
{ 
  time = _time;
  type = _type;
}

SchemeNode::SchemeNode(double _time, int _type, const MidiMessage &_mess)
  : time(0.0), type(_type), mmess(_mess)
{
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
	//printf("...Error: %s\n", schemeThread->errorBuffer);
	if ( SCHEME_DEBUG )
	  printf("...done calling eval node %d\n", nodeid);
	schemeThread->reportChickenError();
      }
      else {
	//printf("returned: %s\n", schemeThread->evalBuffer);
	if ( SCHEME_DEBUG )
	  printf("...done calling eval node %d\n", nodeid);
	String s=String(schemeThread->evalBuffer);
	if ( !s.endsWithChar('\n') )
	  s << T("\n");
	schemeThread->console->
	  postConsoleTextMessage(s, ConsoleMessage::VALUES);
      }
      expr=String::empty;
    }
    break;
  case SAL :
    {
      C_word err;
      int res = CHICKEN_eval_string((char *)expr.toUTF8(), NULL);
      if ( res==0 )
	schemeThread->reportChickenError();
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

  case INHOOK:
    {      
      printf("huh\n");
      printf("is noteon %i\n", mmess.isNoteOn());
      C_word *mmess_ptr;
      mmess_ptr = C_alloc( sizeof(MidiMessage*) );
      C_save(C_mpointer(&mmess_ptr , (void*)&mmess));
      closure = CHICKEN_gc_root_ref(schemeThread->inputClosureGCRoot);
      C_callback(closure, 1);
    }
    break;

  case PAUSE :
    //printf ("processing pause node :(\n");
    break;

  case STOP :
    if ( SCHEME_DEBUG )
      printf("...calling stop node %d\n", nodeid);
    schemeThread->stopProcesses(id);
    if ( SCHEME_DEBUG )
      printf("...done calling stop node %d\n", nodeid);
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
  printf("deleting SchemeThread\n");
  delete evalBuffer;
  delete errorBuffer;
  CHICKEN_delete_gc_root(inputClosureGCRoot);
  schemeNodes.clear();
}

void postGCHook(int m, long ms)
{
  if (m == 1)
    printf("\nMAJOR GC\n\n");
  else
    printf("minor GC\n");
}



void SchemeThread::setInputHook(C_word hook)
{
  if(hook == C_SCHEME_FALSE) {
    CHICKEN_gc_root_set(inputClosureGCRoot, C_SCHEME_FALSE);
    if( ((GraceApp*)GraceApp::getInstance())->midiInPort->isActive(MidiInPort::SCHEMEHOOK) )
      ((GraceApp*)GraceApp::getInstance())->midiInPort->stopSchemeInput();
  }
  else {
    CHICKEN_gc_root_set(inputClosureGCRoot, hook);
    if(!((GraceApp*)GraceApp::getInstance())->midiInPort->isActive(MidiInPort::SCHEMEHOOK)) 
      ((GraceApp*)GraceApp::getInstance())->midiInPort->startSchemeInput();
  }
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

  /* chicken/runtime.c :
    #define DEFAULT_STACK_SIZE             64000
    #define DEFAULT_SYMBOL_TABLE_SIZE      2999
    #define DEFAULT_HEAP_SIZE              500000
    #define MINIMAL_HEAP_SIZE              500000
    #define DEFAULT_MAXIMAL_HEAP_SIZE      2147483632
  */

  GracePreferences* prefs=GracePreferences::getInstance();
  int hsize=prefs->getSchemeHeapSize();
  int ssize=prefs->getSchemeStackSize();

  if ( SCHEME_DEBUG )
    printf("Chicken init: heap=%d stack=%d\n", hsize, ssize);
  res = CHICKEN_initialize(hsize, ssize, 0, (void*)C_grace_toplevel);
  //  res = CHICKEN_initialize(0, 0, 0,  (void*)C_grace_toplevel);
  // default to 4x Chicken's minimum heap size
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

  if ( SCHEME_DEBUG > 1) {
    C_post_gc_hook = postGCHook;
    C_heap_size_is_fixed = 1;
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
  
  inputClosureGCRoot = CHICKEN_new_gc_root();
  
  
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
	// NOTE: the node to process has now been popped from the
	// queue.  i did this while trying to debug the random
	// crashing. im not sure if this is the right thing to do or
	// not since this means that flushing the queue, etc will have
	// no effect on this node. Search for the word POP to see the
	// places this affects...
	bool keep=node->process(0.0);
	if ( keep ) {
	  if ( SCHEME_DEBUG > 2)
	    printf("reinserting process node %d...\n", node->nodeid);
	  schemeNodes.lockArray();
	  schemeNodes.addSorted(comparator,node); 
	  //          schemeNodes.remove(0, false);
	  schemeNodes.unlockArray();
	  if ( SCHEME_DEBUG > 2)
	    printf("...done reinserting process node %d\n", node->nodeid);
	}
	else {
	  int myid=node->nodeid;
	  int mytyp=node->type;
	  delete node;
	  if ( SCHEME_DEBUG > 2) {
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
    if ( SCHEME_DEBUG )
      printf("scheduling queue is empty\n");
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
  if ( SCHEME_DEBUG > 2)
    printf("adding process node %d...\n", n->nodeid);
  n->schemeThread = this;
  schemeNodes.lockArray();
  schemeNodes.addSorted(comparator, n);
  schemeNodes.unlockArray();
  notify();
  if ( SCHEME_DEBUG > 2)
    printf("...done adding process node %d\n", n->nodeid);
}

void SchemeThread::addNode(int type, double _time, String s) {
  static int nextid=000;
  SchemeNode *n = new SchemeNode(_time, type, s);
  n->nodeid=++nextid;
  if ( SCHEME_DEBUG > 2)
    printf("adding eval node %d...\n", n->nodeid);
  n->schemeThread = this;
  schemeNodes.lockArray();
  schemeNodes.addSorted(comparator, n);
  schemeNodes.unlockArray();
  notify();
  if ( SCHEME_DEBUG > 2)
    printf("...done adding eval node %d\n", n->nodeid);
}  

void SchemeThread::addNode(int type, double _time, const MidiMessage &mess) {
  static int nextid=000;
  SchemeNode *n = new SchemeNode(_time, type, mess);
  n->nodeid=++nextid;
  if ( SCHEME_DEBUG > 2)
    printf("adding input hook node %d...\n", n->nodeid);
  n->schemeThread = this;
  schemeNodes.lockArray();
  schemeNodes.addSorted(comparator, n);
  schemeNodes.unlockArray();
  notify();
  if ( SCHEME_DEBUG > 2)
    printf("...done adding input hook node %d\n", n->nodeid);
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
    // NOTE: POP removed the node that got us here so
    // we add pause node at index 0.
    // otherwise the eval node that got us here is at queu index 0 so add pause
    // at index 1 so that it becomes the head of the queue after the
    // eval node is popped
    schemeNodes.insert(0,n); // POP
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
  // always add stop nodes to the front of the queue.
  SchemeNode *node = new SchemeNode (0.0, SchemeNode::STOP);
  node->nodeid=0;
  node->id=id;
  if ( SCHEME_DEBUG > 2)
    printf("adding stop node %d...\n", node->nodeid);
  node->schemeThread = this;
  schemeNodes.lockArray();
  schemeNodes.insert(0,node);
  schemeNodes.unlockArray();
  notify();
  if ( SCHEME_DEBUG > 2)
    printf("...done adding stop node %d\n", node->nodeid);
}

void SchemeThread::stopProcesses(int id) {
  // this is called by a STOP node from process().  stop all processes
  // with id from running. if id=-1 then stop all processes. iterate
  // queue in reverse order so removal index remains valid.  NOTE: POP
  // removed the (STOP) node that got us here so this deletes up to
  // and including index 0. otherwise dont include index 0
  schemeNodes.lockArray();
  if ( id<0 ) { 
    for (int i=schemeNodes.size()-1; i>=0; i--)
      if (schemeNodes[i]->type == SchemeNode::PROCESS)
	schemeNodes.remove(i,true);
  }
  else {
    // else selectively remove all nodes with id process queue in
    // reverse order so removal index always valid
    for (int i=schemeNodes.size()-1; i>=0; i--)
      if ( (schemeNodes[i]->type == SchemeNode::PROCESS) && 
	   (schemeNodes[i]->id == id) )
	schemeNodes.remove(i,true);
  }
  schemeNodes.unlockArray();
}


