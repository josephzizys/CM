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
#include "Console.h"

//#include "Scheme.h"

class NodeQueue;
//class SchemeThread;

class Node 
{
 public:
  Node(double _time, int _type, float *vals=0, int num_vals=0, C_word c=0, 
       String s=String::empty) ;		
  ~Node();

  enum {ATOM, PROCESS, CLOSURE, EXPR };
  double time;
  double start;
  //  double now;
  String expr;
  int type;

  Array<float> values;
  NodeQueue *queue;
  int num;
  void *gcroot;
  bool process();
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
  ConsoleWindow* console;
  String EvalString;
  char *evalBuffer ; 
  char *errorBuffer ; 
  MidiOutput *output;
  //  SchemeThread *schemeThread;
  
  NodeQueue(String name, ConsoleWindow *win,  MidiOutput *out);
  ~NodeQueue();

  OwnedArray<Node, CriticalSection> *nodes;
  void addNode(int type, double _time, float* vals=0, int num_vals=0, C_word c=0);
  void addNode(int type, double _time, String str);
  void removeNode(Node *n, bool deleteObject=true );
  void reinsertNode(Node *n, double newtime );
  
  NodeComparator comparator;
  bool init();
  void run();
  void clear();

};




#endif
