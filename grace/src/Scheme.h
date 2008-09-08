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
#include "Midi.h"

class ConsoleWindow;
class SchemeThread;

class SchemeNode 
{
public:
  enum {PROCESS, INHOOK, EXPR, SAL, PAUSE, STOP };
  // method for process node
  SchemeNode(double _time, int _type, C_word c, int _id);
  // method for eval node
  SchemeNode(double _time, int _type, String s);
  // method for any type
  SchemeNode(double _time, int _type);
  // method for midi message callback from MidiIn port
  SchemeNode(double _time, int _type, const MidiMessage &_mess);
  ~SchemeNode();

  int type;
  int id;
  int nodeid;
  double time;
  double start;
  String expr;
  const MidiMessage mmess;
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
  bool capturemode;
  bool sprouted;
  CriticalSection lock;
  // in capturemode this is timeoffset of processess in seconds else 0.0
  double processtime;

  void *inputClosureGCRoot;
    
  OwnedArray<SchemeNode, CriticalSection> schemeNodes;
  SchemeNodeComparator comparator;  

  void reportChickenError(String text=String::empty);
  void addNode(int type, double _time, C_word c=0, int _id=-1);
  void addNode(int type, double _time, String str);
  void addNode(int type, double _time, const MidiMessage &mess);
  void removeNode(SchemeNode *n, bool deleteObject=true );
  void reinsertNode(SchemeNode *n, double newtime );
  void run();
  bool init();
  void clear();

  bool isPaused() { return pausing; }
  void setPaused(bool b);
  void stop(int id=-1);
  void stopProcesses(int id) ;
  void setInputHook(C_word hook);

  bool isScoreCapture();
  void setScoreCapture(bool b);
  void performSchedulerCommand(CommandID id);
  bool isQueueEmpty();
};

#endif
