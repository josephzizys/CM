/*
 *  Nodes.cpp
 *  rker
 *
 *  Created by Todd Ingalls on 9/24/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "Grace.h"
#include "Nodes.h"
#include "ChickenBridge.h"

//
//  Nodes
//

Node::Node(double _time, int _type, float *vals, int num_vals, C_word c, String s) 
  : time (0.0),
    start (0.0),
    type (0),
    num (0),
    expr (String::empty)
{ 
  int i;
  
  if(_time == 0.0) 
    time = Time::getMillisecondCounterHiRes();
  else
    time = _time + Time::getMillisecondCounterHiRes();
  start = time;
  type = _type;
  
  switch (type) {
  case ATOM:
    for(i=0;i<num_vals;i++)
      values.add( vals[i]);
    //    delete vals;
    break;
  case PROCESS:
    gcroot = CHICKEN_new_gc_root();
    CHICKEN_gc_root_set(gcroot, c);
    num = num_vals;
    break;
  case CLOSURE:
    gcroot = CHICKEN_new_gc_root();
    CHICKEN_gc_root_set(gcroot, c);
    break;
  case EXPR :
    // does this need to copy?
    expr=String(s);
    break;
  default:
    break;
  }  
}

Node::~Node(){ 
  if(type ==  PROCESS || type == CLOSURE) {
    CHICKEN_delete_gc_root(gcroot);
  } 
}

bool Node::process() {
  // return true if node should be rescheduled
  bool more=false;

  switch (type) {

  case ATOM:
    if(values[1] == 0.0) 
      queue->output->sendMessageNow( MidiMessage::noteOff( (int)values[2], (int)values[0]) );
    else 
      queue->output->sendMessageNow( MidiMessage::noteOn((int)values[2], (int)values[0], 127.0f / values[1]) );
    break;

  case PROCESS:
    {
        double nexttime ;
        C_word *elapsed_ptr;
        C_word elapsed_word;
	C_word closure;

        closure = CHICKEN_gc_root_ref(gcroot);
	elapsed_ptr = C_alloc(C_SIZEOF_FLONUM);
	elapsed_word = C_flonum( &elapsed_ptr, time - start); 
	C_save( elapsed_word );
        nexttime = C_c_double( C_callback(closure, 1));
        if (nexttime < 0) {
	  printf("done!\n");
        } 
	else {
	  more=true;
	  time += nexttime;
        }
    }
    break;

  case CLOSURE:
    break;

  case EXPR :
    {
      int res;	
      bzero(queue->evalBuffer, 8192);
      bzero(queue->errorBuffer, 8192);
      res = CHICKEN_eval_string_to_string( (char *)expr.toUTF8(), queue->evalBuffer,
					   expr.length() );
      if ( res==0 ) {
	CHICKEN_get_error_message(queue->errorBuffer, 8192);
	String text=T(String(queue->errorBuffer));
	//queue->console->printError(text);
	printf(">>> %s\n", queue->errorBuffer);
      }
      else {
        //queue->console->printValues(String(queue->evalBuffer) + T("\n"));
	printf("*** Value: %s\n", queue->evalBuffer);
      }
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

NodeQueue::NodeQueue(String name, ConsoleWindow *win, MidiOutput *out)
  : Thread(name)
{	
  console = win;
  output = out;
  evalBuffer = new char[8192];
  errorBuffer = new char[8192];
}

NodeQueue::~NodeQueue()
{
  delete evalBuffer;
  delete errorBuffer;
}

// UNUSED
void NodeQueue::removeNode(Node *n, bool deleteObject)
{
  //  nodes.lockArray();
  //  nodes.removeObject(n, deleteObject);
  //  nodes.unlockArray();
  //  notify();
}

// UNUSED
void NodeQueue::reinsertNode(Node *n, double newtime )
{
  //  nodes.lockArray();
  //  n->time += newtime;  
  //  nodes.addSorted(comparator, n); 
  //  nodes.unlockArray();
}

bool NodeQueue::init() {
  int res;
  C_word r;
  char buffer[8192];
  String text = T("Chicken Scheme");
  
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
  CHICKEN_eval_string("(require-extension srfi-18)", &r);
  CHICKEN_eval_string("(require-extension chicken-more-macros)", &r);
 // CHICKEN_eval_string("(define *grace-std-out*  (make-output-port print-message (lambda () #f)))", NULL);
//  CHICKEN_eval_string("(current-output-port *grace-std-out*)", NULL);
//  CHICKEN_eval_string("(define *grace-err-out*  (make-output-port print-error (lambda () #f)))", NULL);
//  CHICKEN_eval_string("(current-error-port *grace-err-out*)", NULL);
  return true;
}

void NodeQueue::run()
{
  // start chicken
  if (! init() ) return;

  while( !threadShouldExit() ) {
    while (true) {
      // lock array before referencing node[0]
      nodes.lockArray();
      if ( (nodes.size() == 0) || 
	   (nodes[0]->time > round(Time::getMillisecondCounterHiRes())) ) {
	nodes.unlockArray();
	break;
      }
      Node *n=nodes[0];
      nodes.removeObject(n, false);
      nodes.unlockArray();
      // call process function with nodes unlocked other nodes can be
      // added to queue under callback
      if ( n->process() ) {
	// if process() returns true node wants reinsertion
	nodes.lockArray();
	nodes.addSorted(comparator, n); 
	nodes.unlockArray();
      }
      else delete n;
    } // end inner loop
    wait(1);

  }
}

void NodeQueue::addNode(int type, double _time, float* vals, int num_vals, C_word c)
{
  Node *n = new Node(_time, type, vals, num_vals, c);
  n->queue = this;
  nodes.lockArray();
  nodes.addSorted(comparator, n);
  nodes.unlockArray();	
  notify();
}

void NodeQueue::addNode(int type, double _time, String s) {
  Node *n = new Node(_time, type, NULL, 0, 0, s);
  n->queue = this;
  nodes.lockArray();
  nodes.addSorted(comparator, n);
  nodes.unlockArray();	
  notify();
}  
