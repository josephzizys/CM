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
  : time (0.0), num (0)
{ 
  int i = 0;
  //  if(_time == 0.0) 
  //    time = Time::getMillisecondCounterHiRes();
  //  else
  time = _time + Time::getMillisecondCounterHiRes();
  
  //  time = _time;
  //  if (vals[1] == 0) 
  //    printf("adding note off %d at %d\n", (int) vals[0], (int) time);
  //  else
  //    printf("adding note On %d at %d\n", (int) vals[0], (int) time);
 
  for(i=0;i<num_vals;i++)
    values.add( vals[i]);
}

OutputNode::~OutputNode()
{ 
}

void OutputNode::process() {
  // array [0]=keynum, [1]=velocity, [2]=channel
  if(values[1] == 0.0) {
    outputQueue->output->
      sendMessageNow( MidiMessage::noteOff( (int)values[2]+1,
					    (int)values[0]) );
    //    printf("sending off %d at %d\n", (int)values[0], 
    //	   (int)Time::getMillisecondCounterHiRes());
  }
  else 
  {
    // velocity range either 0.0-1.0 or 0.0-127.0
    float vel = (values[1]>1.0) ? (values[1] / 127.0f) : values[1] ;
    outputQueue->output->
      sendMessageNow( MidiMessage::noteOn((int)values[2]+1, 
					  (int)values[0], 
					  vel));
    //    printf("sending On %d at %d\n", (int)values[0], 
    //	   (int)Time::getMillisecondCounterHiRes());
    
  }
}

OutputQueue::OutputQueue(String name,MidiOutput *out)
: Thread(name) , porttype (0)
{	
  porttype=MIDIOUT;
  output = out;
}

OutputQueue::~OutputQueue()
{
}

void OutputQueue::run()
{
  double curr;
  while( !threadShouldExit() ) {
    while(outputNodes.size() > 0) {     
      curr = Time::getMillisecondCounterHiRes() ;
      while ( outputNodes.getFirst()->time <= curr ) {       
        outputNodes.lockArray();
	outputNodes.getFirst()->process();
        outputNodes.remove(0, true);
        if(outputNodes.size() == 0) {
          outputNodes.unlockArray();
          break;
        }
        outputNodes.unlockArray();
	// im not sure that we want to do this, it
        //curr = Time::getMillisecondCounterHiRes() ;
      }
      wait(1);
    }
    wait(-1);
  }
}

void OutputQueue::clear()
{
  outputNodes.lockArray();
  outputNodes.clear();

  // avoid hanging notes if port is MIDIOUT
  if ( porttype==MIDIOUT )
    for ( int i=0; i< 16; i++ )
      output->sendMessageNow( MidiMessage::allSoundOff(i) );
  outputNodes.unlockArray();
}

void OutputQueue::addNode(double _time, float* vals, int num_vals)
{
  OutputNode *n = new OutputNode(_time, vals, num_vals);
  n->outputQueue = this;

  // dont bother adding to queue if its immediate...
  if ( _time == 0.0 ) {
    n->process();
    delete n;
  }
  else {
    outputNodes.lockArray();
    outputNodes.addSorted(comparator, n);
    outputNodes.unlockArray();	
    notify();
  }
}

