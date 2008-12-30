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
  void applyInHookNode();
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
  Scheme(String name, ConsoleWindow *win);
  ~Scheme();

  ConsoleWindow* console;
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

  void *inputClosureGCRoot;
    
  OwnedArray<SchemeNode, CriticalSection> schemeNodes;
  SchemeNodeComparator comparator;  

  bool init();
  void cleanup();

  void sprout(double _time, SCHEMEPROC c=0, int _id=-1);

  void eval(String str);
  void eval(char* str);
  void midiin(const MidiMessage &mess);

  void removeNode(SchemeNode *n, bool deleteObject=true );
  void reinsertNode(SchemeNode *n, double newtime );
  void run();

  void clear();

  bool isPaused() { return pausing; }
  void setPaused(bool b);
  void stop(int id=-1);
  void stopProcesses(int id) ;
  void setInputHook(SCHEMEPROC hook);
  void performSchedulerCommand(CommandID id);
  bool isQueueEmpty();

  //  void printError(char* str);
  //  void printValues(char* str);
  //  void printOutput(char* str);

  juce_DeclareSingleton (Scheme, true)

};

#endif
