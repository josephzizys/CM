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
  enum {PROCESS, INHOOK, EXPR, SAL, PAUSE, STOP };

  SchemeNode(double _time, int _type, C_word c, int _id);
  SchemeNode(double _time, int _type, String s);
  SchemeNode(double _time, int _type);
  ~SchemeNode();

  int type;
  int id;
  int nodeid;
  double time;
  double start;
  String expr;
  void *closureGCRoot;
  C_word *elapsed_ptr;
  C_word elapsed_word;
  C_word closure;
  
  SchemeThread *schemeThread;
  bool process(double curr);
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
  bool pausing;
  bool timemsec;

  OwnedArray<SchemeNode, CriticalSection> schemeNodes;
  SchemeNodeComparator comparator;  

  void reportChickenError(String text=String::empty);
  void addNode(int type, double _time, C_word c=0, int _id=-1);
  void addNode(int type, double _time, String str);
  void removeNode(SchemeNode *n, bool deleteObject=true );
  void reinsertNode(SchemeNode *n, double newtime );
  void run();
  bool init();
  void clear();
  bool isTimeMilliseconds () { return timemsec; }
  void setTimeMilliseconds(bool b) { timemsec=b;}
  bool isPaused() { return pausing; }
  void setPaused(bool b);
  void stop(int id=-1);
  void stopProcesses(int id) ;
};

#endif
