/*
 *  OutputQueue.cpp
 *  grace
 *
 *  Created by Todd Ingalls on 10/31/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "OutputQueue.h"
#include "Grace.h"
#include "ChickenBridge.h"


//
//  Nodes
//


OutputNode::OutputNode(double _time, float *vals, int num_vals)
: time (0.0),num (0)
{ 
  int i = 0;
  if(_time == 0.0) 
    time = Time::getMillisecondCounterHiRes();
  else
    time = _time + Time::getMillisecondCounterHiRes();
  
  time = _time;
  
  for(i=0;i<num_vals;i++)
    values.add( vals[i]);
}

OutputNode::~OutputNode()
{ 
}

void OutputNode::process() {
  
  if(values[1] == 0.0) 
    outputQueue->output->sendMessageNow( MidiMessage::noteOff( (int)values[2], (int)values[0]) );
  else 
  {
    outputQueue->output->sendMessageNow( MidiMessage::noteOn((int)values[2], (int)values[0], values[1] / 127.0f));
    
  }
}



OutputQueue::OutputQueue(String name,MidiOutput *out)
: Thread(name)
{	
  output = out;
}

OutputQueue::~OutputQueue()
{
}


void OutputQueue::run()
{
  double curr;
  while( !threadShouldExit() ) {
    
    curr = Time::getMillisecondCounterHiRes() ;
    
    while(outputNodes.size() > 0) {     
      while ( outputNodes.getFirst()->time <= curr ) {       
        
        outputNodes.lockArray();
        
        outputNodes.getFirst()->process();
       
        outputNodes.remove(0, true);
        
        if(outputNodes.size() == 0) {
          outputNodes.unlockArray();
          break;
        }
        outputNodes.unlockArray();
        curr = Time::getMillisecondCounterHiRes() ;

      }
      usleep(100);
    }
    wait(-1);
  }
}

void OutputQueue::clear()
{
  outputNodes.lockArray();
  outputNodes.clear();
  outputNodes.unlockArray();
  
  
}


void OutputQueue::addNode(double _time, float* vals, int num_vals)
{
  OutputNode *n = new OutputNode(_time, vals, num_vals);

  n->outputQueue = this;
  outputNodes.lockArray();
  outputNodes.addSorted(comparator, n);
  outputNodes.unlockArray();	
  notify();
}

