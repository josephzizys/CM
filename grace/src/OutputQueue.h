/*
 *  OutputQueue.h
 *  grace
 *
 *  Created by Todd Ingalls on 10/31/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __OUTPUTQUEUE__
#define __OUTPUTQUEUE__

#include <juce.h>
#include <chicken.h>
#include "Console.h"

class OutputQueue;

class OutputNode 
{
public:
  OutputNode(double _time, float *vals=0, int num_vals=0) ;		
  ~OutputNode();

  double time;
  Array<float> values;
  OutputQueue *outputQueue;
  int num;
  void process();
  void print();
};

class OutputNodeComparator
{
public:
  static int compareElements(OutputNode* e1, OutputNode* e2)
  {
    if( e1->time <= e2->time)
      return -1;
    else 
      return 1;
  }
};


class OutputQueue : public Thread
{
public:
  enum { MIDIOUT=1, MIDISEQ, PLOTTER };
  int porttype;
  MidiOutput *output;
  OutputQueue(String name, MidiOutput *out);
  ~OutputQueue();
  
  OwnedArray<OutputNode, CriticalSection> outputNodes;
  void addNode(double _time, float* vals=0, int num_vals=0);
  OutputNodeComparator comparator;
  
  void run();
  void clear();
  
};

#endif
