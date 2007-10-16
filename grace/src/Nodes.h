/*
 *  Nodes.h
 *  rker
 *
 *  Created by Todd Ingalls on 9/24/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __NODES__
#define __NODES__

#include <juce.h>
#include <chicken.h>
#include "Scheme.h"

class NodeQueue;
class SchemeThread;

class Node 
{
 public:
  Node(double _time, int _type, float *vals=0, int num_vals=0, C_word c=0) ;		
  ~Node();

  enum {ATOM, PROCESS, CLOSURE };
  double time;
  int type;
  Array<float> values;

  NodeQueue *queue;
  int num;
  void *gcroot;
  
  double now;
  double elapsed;
  
  C_word *now_ptr;
  C_word *elapsed_ptr;
  void process();
  void print();
  
};

class NodeComparator
{
 public:
  static int compareElements(Node* e1, Node* e2)
  {
    if( e1->time < e2->time)
      return -1;
    else 
      return 1;
  }
};


class NodeQueue : public Thread
{
 public:
  MidiOutput *output;
  SchemeThread *schemeThread;
  
  NodeQueue(String name, SchemeThread *thread,  MidiOutput *out);
  ~NodeQueue();

  OwnedArray<Node, CriticalSection> nodes;

  void addNode(int type, double _time, float* vals=0, int num_vals=0, C_word c=0);
  void removeNode(Node *n, bool deleteObject=true );
  void reinsertNode(Node *n, double newtime );
  
  NodeComparator comparator;
  void run();
  
};




#endif
