#ifndef __CSOUND__
#define __CSOUND__

// g++ -MMD -D "MACOSX=1" -D "SCHEME=1" -D "PORTCSOUND=1" -I "../../../chicken" -I "../../../juce" -I "/usr/local/include"  -O2 -o build/grace.obj/Release/Csound.o -c ../../src/Csound.cpp

#include <juce.h>
#include "Console.h"
#ifdef PORTCSOUND
#include <CsoundLib/csound.h> 
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

class CsoundPort {
 public:

  String options;
  //  String csdfile;
  RecentlyOpenedFilesList csdfiles;
  ConsoleWindow *console;
  CsoundConnection *connection;
  bool running;
  bool tracing;
  CsoundPort(ConsoleWindow *win) ;
  ~CsoundPort() ;
  String getOptions();
  void setOptions(String opts);
  File getCsdFile();
  void setCsdFile(File file);
  bool getTracing();
  void setTracing(bool b);
  void save();
  void revert();
  bool open() ;
  bool isOpen() ;
  void close();
  void sendEvent(char type, int len, MYFLT *pars);
  void testNote();
  void configure();
};


#endif
