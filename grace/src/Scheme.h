/*
 *  Scheme.h
 *  
 *
 *  Created by todd ingalls on 9/1/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __GRACESCHEME__
#define __GRACESCHEME__
#include "juce.h"
#include "chicken.h"
#include "Console.h"

class ConsoleWindow;
class SchemeThread;



class SchemeNode 
{
public:
  SchemeNode(double _time, int _type, C_word c);
  SchemeNode(double _time, int _type, String s);
  ~SchemeNode();
  
  enum {PROCESS, PROCEDURE, EXPR };
  int type;
  double time;
  double start;

  String expr;
  
  void *closureGCRoot;
  C_word closure;
  SchemeThread *schemeThread;
  
  bool process(double curr);
  bool init();
  void run();
  void clear();
};

class SchemeNodeComparator
{
public:
  static int compareElements(SchemeNode* e1, SchemeNode* e2)
  {
    if( e1->time <= e2->time)
      return -1;
    else 
      return 1;
  }
};


class SchemeThread : public Thread
{
public:
  SchemeThread(String name, ConsoleWindow *win);
  ~SchemeThread();
  ConsoleWindow* console;
  String EvalString;
  char *evalBuffer ; 
  char *errorBuffer ; 

  OwnedArray<SchemeNode, CriticalSection> schemeNodes;
  
  void addNode(int type, double _time, C_word c=0);
  void addNode(int type, double _time, String str);
  void removeNode(SchemeNode *n, bool deleteObject=true );
  void reinsertNode(SchemeNode *n, double newtime );
  void run();
  bool init();
  void clear();
  SchemeNodeComparator comparator;

};

#endif