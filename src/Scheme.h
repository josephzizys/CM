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
#endif

#include "Syntax.h"

class SchemeThread;

/*=======================================================================*
                                Input Hook Classes
 *=======================================================================*/

class OscHook
{
 public:
  String path;
  s7_pointer proc;
  OscHook (String oscpath, s7_pointer func) : path (oscpath), proc (func) {}
  ~OscHook () {}
};

class MidiHook
{
 public:
  int op;
  s7_pointer proc;
  MidiHook (int oper, s7_pointer func) : op (oper), proc (func) {}
  ~MidiHook () {}
};

/*=======================================================================*
                           Scheme Execution Node Classes
 *=======================================================================*/

class XSchemeNode 
{
 public:
  double time;
  int nodeid;
  int userid;  // user's id
  XSchemeNode(double qtime);
  virtual ~XSchemeNode(){}
  virtual bool applyNode(SchemeThread* scheme, double curtime)=0;
};

class XControlNode : public XSchemeNode
{
 public:
  enum {QueueStop=1, QueueQuit};
  int type;
  XControlNode(double qtime, int control, int ident=-1);
  ~XControlNode();
  bool applyNode(SchemeThread* scheme, double curtime);
};

class XEvalNode : public XSchemeNode
{
 public:
  String expr;
  XEvalNode(double qtime, String sexpr);
  ~XEvalNode();
  bool applyNode(SchemeThread* scheme, double curtime);
};

class XSalNode : public XSchemeNode
{
 public:
  String expr;
  //OwnedArray<SynTok>* toks;
  OwnedArray<SynTok> toks;
  XSalNode(double qtime, String input /*, OwnedArray<SynTok>* tokens*/);
  ~XSalNode();
  bool applyNode(SchemeThread* scheme, double curtime);
};

class XProcessNode : public XSchemeNode
{
 public:
  double start;
  double elapsed;
  s7_pointer schemeproc;
  //  int id;
  XProcessNode(double qtime, s7_pointer proc, int qid);
  ~XProcessNode();
  bool applyNode(SchemeThread* schemethread, double curtime);
};

class XMidiNode : public XSchemeNode
{
public:
  const MidiMessage mmess;
  MidiHook* hook;
  XMidiNode(double qtime, const MidiMessage &mess, MidiHook* huk)
    : XSchemeNode (qtime), mmess (mess), hook (huk) {}
  ~XMidiNode(){}
  bool applyNode(SchemeThread* scheme, double curtime);
};

class XOscNode : public XSchemeNode
{
 public:
  String path;
  String types;
  OscHook* hook;
  Array<s7_Int> ints;
  Array<double> flos;
  StringArray strs;
  XOscNode(double qtime, String oscpath, String osctypes) ;
  ~XOscNode() ;
  bool applyNode(SchemeThread* scheme, double curtime) ;
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

/*=======================================================================*
                              Scheme Thread Singleton
 *=======================================================================*/

class SchemeThread : public Thread
{
 public:
  
  SchemeThread() ;
  ~SchemeThread();

  s7_scheme *scheme;
  s7_pointer oscHook;
  s7_pointer schemeFalse;
  s7_pointer schemeTrue;
  s7_pointer schemeNil;  
  s7_pointer schemeError; 
  s7_pointer schemeVoid;
  void signalSchemeError(String text);

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
  //  CriticalSection lock;

  // Midi Receiving
  OwnedArray<MidiHook, CriticalSection> midiHooks;
  void midiin(const MidiMessage &mess);
  bool isMidiHook(int opr);
  MidiHook* getMidiHook(int opr, bool strict=false);
  void removeMidiHook(MidiHook* hook);
  bool clearMidiHook(int opr);
  void addMidiHook(int opr, s7_pointer proc);

  // Midi Receiving
  OwnedArray<OscHook, CriticalSection> oscHooks;
  bool isOscHook(String path=String::empty);
  OscHook* getOscHook(String path, bool strict=false);
  void removeOscHook(OscHook* hook);
  bool clearOscHook(String path);
  void addOscHook(String path, s7_pointer proc);
  void receiveOsc(XOscNode* n);
 
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
  String getLispVersion();

  void sprout(double _time, s7_pointer c=0, int _id=-1);
  void eval(String str);
  void eval(char* str);
  void load(File file, bool addtorecent=false);

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

  juce_DeclareSingleton (SchemeThread, true)

};

#endif
