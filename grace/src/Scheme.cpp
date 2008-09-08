/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

#include "Grace.h"
#include "Scheme.h"
#include "Enumerations.h"
#include "ChickenBridge.h"
#include <iostream>

#define SCHEME_DEBUG 0

// 1= trace scheme entry/exit points
// 2= include gc info in trace
// 3= include node creation/insertion/deletion info in tracce

//
//  Nodes
//

SchemeNode::SchemeNode(double _time, int _type, C_word c, int _id)
  : time (0.0), start (0.0), type (0), expr (String::empty) , mmess(0xff)
{
  // method for process node
  type = _type;
  id = _id;
  time = _time;
  start = _time;
  closureGCRoot = CHICKEN_new_gc_root();
  CHICKEN_gc_root_set(closureGCRoot, c);
}

SchemeNode::SchemeNode(double _time, int _type, String _expr)
  : time (0.0), start (0.0), type (0), closure(0), id (-1), mmess(0xff)
{
  // method for eval node
  type=_type; //  type = EXPR;
  expr=_expr;
  time = 0.0; // will always be ready to call
}

SchemeNode::SchemeNode(double _time, int _type)
  : start (0.0), closure (0), expr (String::empty), id (-1), mmess(0xff)
{
  // method for any type of node
  time = _time;
  type = _type;
}

SchemeNode::SchemeNode(double _time, int _type, const MidiMessage &_mess)
  : time(0.0), type(_type), mmess(_mess)
{
  // method for midi message callback from MidiIn port
}

SchemeNode::~SchemeNode()
{
}

bool SchemeNode::process(double curtime) 
{
  bool more=false;

  switch (type)
    {
    case EXPR :
      {
	C_word res;
	memset(schemeThread->evalBuffer, 0, 8192);
	memset(schemeThread->errorBuffer, 0, 8192);
	if ( SCHEME_DEBUG )
	  printf("\ncalling eval node %d, input '%s'\n", 
		 nodeid,  (char *)expr.toUTF8()
		 );
	
	res = CHICKEN_eval_string_to_string( (char *)expr.toUTF8(),
					     schemeThread->evalBuffer,
					     8192);
	//printf("\nafter eval-string-to-string, res=%d\n",res);
	if ( res==0 )
	  {
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
	    postConsoleMessage(s, CommandIDs::ConsolePrintValues,
				   true);
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
	  std::cout << "\ncalling process node " 
		    << nodeid << " time=" << time << "\n";
	double thistime;
	double nexttime;
	bool capturing=schemeThread->capturemode;
	closure = CHICKEN_gc_root_ref(closureGCRoot);
	elapsed_ptr = C_alloc(C_SIZEOF_FLONUM);
	// if capturing is true then time is milliseconds else its
	// milliseconds
	if (capturing)
	  {
	    thistime=time-start;
	    schemeThread->processtime=time;
	  }
	else
	  {
	    thistime=(time-start)/1000.0;
	  }
	elapsed_word = C_flonum( &elapsed_ptr, thistime );
	C_save( elapsed_word );
	nexttime = C_c_double( C_callback(closure, 1));
	if (nexttime < 0)
	  {
	    CHICKEN_delete_gc_root(closureGCRoot);
	    if ( SCHEME_DEBUG )
	      std::cout << "...killing process node "
			<< nodeid << "\n";
	    return false;
	  }
	else
	  {
	    more=true;
	    if (capturing)
	      {
		time = time + nexttime;
	      }
	    else
	      {
		time=Time::getMillisecondCounterHiRes() +
		  (nexttime * 1000.0);
	      }
	    if ( SCHEME_DEBUG )
	      std::cout << "...next run time "
			<< time << "\n";
	  }
	schemeThread->processtime=0.0;
      }
      break;
      
    case INHOOK:
      {
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
  : Thread(name),
    pausing (false),
    capturemode (false),
    sprouted (false),
    processtime (0.0)
{
  console = win;
  evalBuffer = new char[8192];
  errorBuffer = new char[8192];

}

SchemeThread::~SchemeThread()
{
  delete evalBuffer;
  delete errorBuffer;
  CHICKEN_delete_gc_root(inputClosureGCRoot);
  schemeNodes.clear();
}

void postGCHook(int m, long ms)
{
  if (SCHEME_DEBUG)
    if (m == 1)
      printf("\nMAJOR GC\n\n");
    else
      printf("minor GC\n");
}

void SchemeThread::setInputHook(C_word hook) {
  if (hook == C_SCHEME_FALSE) {
    CHICKEN_gc_root_set(inputClosureGCRoot, C_SCHEME_FALSE);
    if( ((GraceApp*)GraceApp::getInstance())->midiInPort->
	isActive(MidiInPort::SCHEMEHOOK) )
      ((GraceApp*)GraceApp::getInstance())->midiInPort->
	stopSchemeInput();
  }
  else {
    CHICKEN_gc_root_set(inputClosureGCRoot, hook);
    if(!((GraceApp*)GraceApp::getInstance())->midiInPort->
       isActive(MidiInPort::SCHEMEHOOK))
      ((GraceApp*)GraceApp::getInstance())->midiInPort->
	startSchemeInput();
  }
}

void SchemeThread::reportChickenError (String text) {
  // if text is null we are reporting a runtime error so we fetch the
  // text from the error buffer and insure that it ends with \n
  if ( text == String::empty ) {
    CHICKEN_get_error_message(errorBuffer, 8192);
    text << T(">>> ") << String(errorBuffer);
    if ( ! text.endsWithChar('\n') )
      text << T("\n");
  }
  console->postConsoleMessage(text, CommandIDs::ConsolePrintError,
				  true);
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

  capturemode=prefs->getScoreCaptureMode();

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
  text += T("\n(c) 2000-2008 Felix L. Winkelmann\n");
  // console->printMessage(text, true);
  console->postConsoleMessage(text, CommandIDs::ConsolePrintText,
				  true);
  //console->doAsyncUpdate();
  memset(buffer, 0,8192);
  if (res==0) {
    reportChickenError( T(">>> Error: Chicken failed to initialize.\n") );
    return false;
  }
  CHICKEN_eval_string((char*)"(define *grace-std-out* (make-output-port print-message (lambda () #f)))", NULL);
  res = CHICKEN_eval_string((char*)"(current-output-port *grace-std-out*)", NULL);
  if ( res==0 )
    reportChickenError();
  res = CHICKEN_eval_string((char*)"(define *grace-err-out* (make-output-port print-error (lambda () #f)))", NULL);
  if ( res==0 )
    reportChickenError();
  res = CHICKEN_eval_string((char*)"(current-error-port *grace-err-out*)", NULL);
  if ( res==0 )
    reportChickenError();
  res = CHICKEN_eval_string((char*)"(cm-logo 30000)", NULL);
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
  while ( true ) 
    {
      if ( threadShouldExit() )
	break;
      while ( true ) 
	{
	  schemeNodes.lockArray();
	  node=schemeNodes.getFirst();
	  schemeNodes.unlockArray();
	  if ( node == NULL )
	    {
	      break;
	    }
	  // if capturemode is true then qtime will be in seconds else
	  // milliseconds.
	  qtime=node->time;
	  utime = Time::getMillisecondCounterHiRes() ;
	  // this should probably test if the difference between qtime
	  // and utime is less that 1ms, if not then it probably
	  // shouldn't sleep (?)
	  if ( qtime > utime )
	    {
	      // if capturemode is true then qtime will be in seconds
	      // so this will not happen (which is what we want)
	      wait(1);
	    }
	  else
	    {
	      schemeNodes.lockArray();
	      schemeNodes.remove(0, false);
	      schemeNodes.unlockArray();
	      // NOTE: the node to process has now been popped from the
	      // queue.  i did this while trying to debug the random
	      // crashing. im not sure if this is the right thing to do or
	      // not since this means that flushing the queue, etc will have
	      // no effect on this node. Search for the word POP to see the
	      // places this affects...
	      lock.enter();
	      bool keep=node->process(0.0);
	      lock.exit();
	      if ( keep )
		{
		  if ( SCHEME_DEBUG > 2)
		    printf("reinserting process node %d...\n",
			   node->nodeid);
		  schemeNodes.lockArray();
		  schemeNodes.addSorted(comparator,node);
		  //          schemeNodes.remove(0, false);
		  schemeNodes.unlockArray();
		  if ( SCHEME_DEBUG > 2)
		    printf("...done reinserting process node %d\n",
			   node->nodeid);
		}
	      else
		{
		  int myid=node->nodeid;
		  int mytyp=node->type;
		  delete node;
		  if ( SCHEME_DEBUG > 2)
		    {
		      if (mytyp==SchemeNode::PROCESS)
			printf("deleted process node %d\n", myid);
		      else
			printf("deleted eval node %d\n", myid);
		      schemeNodes.lockArray();
		      int mysize=schemeNodes.size();
		      printf ("Queue size: %d\n", mysize);
		      if (mysize>0)
			{
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
		  //printf("...removed %d, queue now %d\n", myid, mysize);
		}
	    }
	  node=NULL;
	}
      // queue is empty. at this point we could signal autoplay if
      // sprouted is true
      if ( 1 )
	printf("scheduling queue is empty\n");
      if (sprouted && capturemode)
	{
	  // we finished running a sprouted process, send a "score
	  // complete" message to the console for auto processing
	  console->postConsoleMessage(String::empty, 
				      CommandIDs::SchedulerScoreComplete,
				      true);
	}
      sprouted=false;
      processtime=0.0;
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

// addNode for processes

void SchemeThread::addNode(int type, double _time, C_word c, int _id)
{
  // this method add a musical process and it is only called by scheme
  // code, ie evalling sprout() under an eval node in the process()
  // method. this means that a lock.enter() is in effect so we dont
  // need to lock anything to reference capturemode.
  static int nextid=1000;
  if (!capturemode)
    {
      _time = (_time * 1000) + Time::getMillisecondCounterHiRes();
    }
  SchemeNode *n = new SchemeNode(_time, SchemeNode::PROCESS, c, _id);
  n->nodeid=++nextid;
  if ( SCHEME_DEBUG > 2)
    printf("adding process node %d...\n", n->nodeid);
  n->schemeThread = this;
  sprouted=true;
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


bool SchemeThread::isScoreCapture()
{
  lock.enter();
  bool val=capturemode;
  lock.exit();
  return val;
}

void SchemeThread::setScoreCapture(bool b)
{
  lock.enter();
  capturemode=b;
  // (re)set processtime to 0 regardless of scorecapture's current
  // value.  processtime will only be set under callbacks when
  // capturemode is true;
  processtime=0.0;
  lock.exit();
}

bool SchemeThread::isQueueEmpty()
{
  schemeNodes.lockArray();
  int size=schemeNodes.size();
  schemeNodes.unlockArray();
  //std::cout << "isQueueEmpty: " << (size==0) << "\n";
  return (size == 0);
}

void SchemeThread::performSchedulerCommand(CommandID id)
{
  GracePreferences* prefs=GracePreferences::getInstance();
  switch (id)
    {
    case CommandIDs::SchedulerScoreMode :
      lock.enter();
      capturemode=(!capturemode);
      lock.exit();
      prefs->setScoreCaptureMode(capturemode);
      break;
    default:
      break;
    }
}





