/*=======================================================================*
  Copyright (C) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#ifndef SCHEME_H
#define SCHEME_H

#include "juce.h"
#ifdef CHICKEN
#include "chicken.h"
#define SCHEMEPROC C_word
#endif
#ifdef SNDLIB
#include "s7.h"
#define SCHEMEPROC s7_pointer
#endif

class ConsoleWindow;
class Scheme;

class SchemeNode 
{

 public:

  enum
  {
    PROCESS, 
    INHOOK,
    EVAL, 
    SAL, 
    PAUSE,
    STOP
  };
  
  SchemeNode(int _type,double _time);
  SchemeNode(int _type, double _time, SCHEMEPROC c, int _id);
  SchemeNode(int _type, double _time, String s);
  SchemeNode(int _type, double _time, const MidiMessage &_mess);

  ~SchemeNode();

  int type;
  int id;
  int nodeid;
  double time;
  double start;
  String expr;
  const MidiMessage mmess;

#ifdef CHICKEN
  void *closureGCRoot;
  C_word *elapsed_ptr;
  C_word elapsed_word;
#endif
#ifdef SNDLIB
  SCHEMEPROC schemeproc;
#endif
  
  Scheme *schemeThread;

  bool applyNode(double curr);
  void applyEvalNode();
  double applyProcessNode(double now);
  void applyMidiInputHookNode();
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

class Scheme : public Thread
{
public:
  Scheme() ;
  ~Scheme();

#ifdef SNDLIB
  SCHEMEPROC midiinhook;
#endif
#ifdef CHICKEN
  void *inputClosureGCRoot;
#endif

  String voidstring;
  bool showvoid;
  bool showVoidValues();
  void setShowVoidValues(bool b);
  void printVoidValue(String input=String::empty);

  char *evalBuffer ; 
  char *errorBuffer ; 
  //  String prompt;
  bool pausing;
  bool sprouted;
  CriticalSection lock;

  int scoremode;
  void setScoreMode(int mode);
  bool isScoreMode();
  bool isScoreMode(int mode);

  double scoretime;
  double getScoreTime();


    
  OwnedArray<SchemeNode, CriticalSection> schemeNodes;
  SchemeNodeComparator comparator;  

  // These next methods are defined in the scheme implementation files
  // (SndLib.cpp and Chicken.cpp)
  bool init();
  void cleanup();
  bool isMidiInputHook();
  void setMidiInputHook(SCHEMEPROC hook);
  void clearMidiInputHook();


  void sprout(double _time, SCHEMEPROC c=0, int _id=-1);
  void eval(String str);
  void eval(char* str);
  void load(File file, bool addtorecent=false);
  void midiin(const MidiMessage &mess);

  void removeNode(SchemeNode *n, bool deleteObject=true );
  void reinsertNode(SchemeNode *n, double newtime );
  void run();

  void clear();

  bool isPaused() { return pausing; }
  void setPaused(bool b);
  void stop(int id=-1);
  void stopProcesses(int id) ;
  void performSchedulerCommand(CommandID id);
  bool isQueueEmpty();

  //  void printError(char* str);
  //  void printValues(char* str);
  //  void printOutput(char* str);

  juce_DeclareSingleton (Scheme, true)

};

#endif
