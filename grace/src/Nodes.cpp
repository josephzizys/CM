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

//
/* Queues */

NodeQueue::NodeQueue(String name, SchemeThread *thread, MidiOutput *out) : Thread(name)
{	
  output = out;
  schemeThread = thread;
}


NodeQueue::~NodeQueue()
{
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


void NodeQueue::removeNode(Node *n, bool deleteObject)
{
  nodes.lockArray();
  nodes.removeObject(n, deleteObject);
  nodes.unlockArray();
  notify();
}

void NodeQueue::reinsertNode(Node *n, double newtime )
{
  
  nodes.lockArray();
  n->time += newtime;

  nodes.addSorted(comparator, n); 
  nodes.unlockArray();
  
}


void NodeQueue::run()
{
  double cur;
  
  while(!threadShouldExit() )
    {
      if( nodes.size() > 0) {
	cur = Time::getMillisecondCounterHiRes();
	
	while ( nodes.size() > 0 && cur >= nodes[0]->time ) {
	  
	  nodes[0]->process();
	  cur = Time::getMillisecondCounterHiRes();
	  
	}
      }		
      wait(1);
    }
}



void Node::process()
{
  C_word res;
  
  switch (type)
    {
    case ATOM:
      if(values[0] == 0.0) 
	queue->output->sendMessageNow( MidiMessage::noteOff( 1, (int)values[0]) );
      else 
	queue->output->sendMessageNow( MidiMessage::noteOn(  1, (int)values[0], 127.0f / values[1]) );
      queue->removeNode(this);
      break;
    case PROCESS:
      queue->removeNode(this, false);
      queue->schemeThread->insertMessage( new SchemeMessage( this ) );
      break;
    case CLOSURE:
      queue->removeNode(this, false);
      queue->schemeThread->insertMessage( new SchemeMessage( this ) );
      break;
    default:
      break;
    }	
  
}

Node::Node(double _time, int _type, float *vals, int num_vals, C_word c) 
{ 
  int i;
  
  if(_time == 0.0) 
    time = Time::getMillisecondCounterHiRes();
  else
    time = _time + Time::getMillisecondCounterHiRes();

  type = _type;
  printf("type %i\n", type);
  switch (type) 
    {
    case ATOM:
      for(i=0;i<num_vals;i++)
	values.add( vals[i]);
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
    default:
      break;
    }  
}


