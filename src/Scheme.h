/*=======================================================================*
  Copyright (C) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#ifndef SCHEME_H
#define SCHEME_H

#include "juce.h"

#ifdef SNDLIB
#include "s7.h"
#define SCHEMEPROC s7_pointer
#define SCHEMEOBJECT s7_pointer
#endif

class ConsoleWindow;
class Scheme;

class XSchemeNode 
{
 public:
  double time;
  int nodeid;
  int userid;  // user's id
  XSchemeNode(double qtime);
  virtual ~XSchemeNode(){}
  virtual bool applyNode(Scheme* scheme, double curtime)=0;
};

class XControlNode : public XSchemeNode
{
 public:
  enum {QueueStop=1, QueueQuit};
  int type;
  XControlNode(double qtime, int control, int ident=-1);
  ~XControlNode();
  bool applyNode(Scheme* scheme, double curtime);
};

class XEvalNode : public XSchemeNode
{
 public:
  String expr;
  XEvalNode(double qtime, String sexpr);
  ~XEvalNode();
  bool applyNode(Scheme* scheme, double curtime);
};

class XProcessNode : public XSchemeNode
{
 public:
  double start;
  double elapsed;
  SCHEMEPROC schemeproc;
  //  int id;
  XProcessNode(double qtime, SCHEMEPROC proc, int qid);
  ~XProcessNode();
  bool applyNode(Scheme* schemethread, double curtime);
  //double applyProcessNode(Scheme* schemethread, double elapsed);
};

class XMidiNode : public XSchemeNode
{
 public:
  const MidiMessage mmess;
  XMidiNode(double qtime, const MidiMessage &mess);
  ~XMidiNode();
  bool applyNode(Scheme* scheme, double curtime);
};

class XOscNode : public XSchemeNode
{
 public:
  String path;
  String types;
  Array<s7_Int> ints;
  Array<double> flos;
  XOscNode(double qtime, String oscpath, String osctypes) ;
  ~XOscNode() ;
  bool applyNode(Scheme* scheme, double curtime) ;
};

class XSchemeNodeComparator
{
 public:
  static int compareElements(XSchemeNode* e1, XSchemeNode* e2)
  {
    if (e1->time < e2->time)
      return -1;
    else if (e2->time < e1->time)
      return 1;
    // else both at same time, return node that was added first
    else if (e1->nodeid<e2->nodeid)
      return -1;
    else
      return 1;
  }
};

//
// Scheme Thread executes Scheme Nodes in a priority queue.
//

class Scheme : public Thread
{
public:
  Scheme() ;
  ~Scheme();

#ifdef SNDLIB

  s7_scheme *scheme;
  s7_pointer midiinhook;
  s7_pointer oscHook;
  s7_pointer schemeFalse;
  s7_pointer schemeTrue;
  s7_pointer schemeNil;  
  s7_pointer schemeErr; 
  s7_pointer schemeVoid;

  void schemeError(String text)
  {
    // use this function to signal errors in C code called by Scheme
    s7_error(scheme,
             schemeErr, //s7_make_symbol(scheme, "scheme-error"), 
             s7_make_string(scheme, text.toUTF8())
             );
  }
#endif
  int nextid;
  String voidstring;
  bool quiet;
  bool isQuiet(){ return quiet;}
  void setQuiet(bool q){quiet=q;}
  bool showvoid;
  bool showVoidValues();
  void setShowVoidValues(bool b);
  void printVoidValue(String input=String::empty);

  bool pausing;
  bool sprouted;
  CriticalSection lock;

  // Osc Input Hook
  CriticalSection oscLock;
  void setOscHook(s7_pointer hook);
  void clearOscHook();
  bool isOscHook();
  void lockOscHook();
  void unlockOscHook();

  int scoremode;
  void setScoreMode(int mode);
  bool isScoreMode();
  bool isScoreMode(int mode);

  double scoretime;
  double getScoreTime();


    
  OwnedArray<XSchemeNode, CriticalSection> schemeNodes;
  XSchemeNodeComparator comparator;  

  // These next methods are defined in the scheme implementation files
  // (SndLib.cpp and Chicken.cpp)
  bool init();
  void cleanup();
  bool isMidiInputHook();
  void setMidiInputHook(SCHEMEPROC hook);
  void clearMidiInputHook();
  String getLispVersion();

  void sprout(double _time, SCHEMEPROC c=0, int _id=-1);
  void eval(String str);
  void eval(char* str);
  void load(File file, bool addtorecent=false);
  void midiin(const MidiMessage &mess);
  void quit();
  void read();
  void run();
  void clear();
  void addNode(XSchemeNode* node);
  bool isPaused() { return pausing; }
  void setPaused(bool b);
  void stop(int id=-1);
  void stopProcesses(int id) ;
  void performSchedulerCommand(CommandID id);
  bool isQueueEmpty();

  juce_DeclareSingleton (Scheme, true)

};

#endif
