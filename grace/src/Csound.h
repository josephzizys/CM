#ifndef __CSOUND__
#define __CSOUND__

// g++ -MMD -D "MACOSX=1" -D "SCHEME=1" -D "PORTCSOUND=1" -I "../../../chicken" -I "../../../juce" -I "/usr/local/include"  -O2 -o build/grace.obj/Release/Csound.o -c ../../src/Csound.cpp

#include <juce.h>
#include "Console.h"
#ifdef PORTCSOUND

#ifdef MACOSX
#include <CsoundLib/csound.h> 
#else
#include <csound/csound.h> 
#endif

#else
typedef MYFLT double;
#endif

class ConsoleWindow;
class CsoundPort;

class CsoundConnection : public Thread {
 public:
#ifdef PORTCSOUND
  CSOUND* csound;
#else
  void* csound;
#endif
  CsoundPort *port;
  CsoundConnection(CsoundPort *_port);
  ~CsoundConnection();
  bool init(String initargs) ;
  void run ();
};

class CsoundScoreEv {
 public:
  char type;
  int size;
  MYFLT *pars;
  CsoundScoreEv(char ty, int sz, MYFLT *fl) {
    type=ty;
    size=sz;
    pars=new MYFLT[sz];
    for (int i=0;i<sz;i++)
      pars[i]=fl[i];
  }
  ~CsoundScoreEv() {
    delete [] pars;
  }
};

class CsoundScoreEvComparator {
 public:
  static int compareElements(CsoundScoreEv* e1, CsoundScoreEv* e2) {
    if (e1->type=='f')
      if (e2->type=='f')
	return 0;
      else return -1;
    else if (e2->type=='f')
      return 1;
    if ( e1->pars[1] <= e2->pars[1])
      return -1;
    return 1;
  }
};

class CsoundPort {
 public:

  String portoptions, fileoptions;
  //  String csdfile;
  RecentlyOpenedFilesList csdfiles;
  ConsoleWindow *console;
  CsoundConnection *connection;
  OwnedArray<CsoundScoreEv> score;
  CsoundScoreEvComparator comparator;
  bool running;
  bool tracing;
  CsoundPort(ConsoleWindow *win) ;
  ~CsoundPort() ;
  String getPortOptions();
  void setPortOptions(String opts);
  String getFileOptions();
  void setFileOptions(String opts);
  File getCsdFile();
  void setCsdFile(File file);
  bool getTracing();
  void setTracing(bool b);
  void save();
  void revert();
  bool open() ;
  bool isOpen() ;
  void close();
  void sendScoreEvent(char type, int len, MYFLT *pars);

  void testNote();
  void configure();
  // scorefile api
  void addScoreEvent(char type, int len, MYFLT *pars);
  void printScoreEvent(char type, int len, MYFLT *pars);
  void sortScore();
  void writeScore();
  void clearScore();
  void printScore(double beg=0.0, double end=31536000.0);
  int numScoreEvents();
  bool isScoreEmpty();
};

#endif
