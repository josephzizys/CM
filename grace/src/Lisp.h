/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

#ifndef __LISP__
#define __LISP__

#include "juce.h"

class LispConnection;
class ConsoleWindow;

#include "Console.h"

#define NUM_LISPS 3

class Lisp {
 public:
  enum {CLTL=1, Scheme=2, SBCL=4, OpenMCL=8, CLISP=16};
  enum {OsAll = (SystemStats::Windows | SystemStats::MacOSX | 
		 SystemStats::Linux ),
	OsUnix = (SystemStats::MacOSX | SystemStats::Linux ),
	OsWin = (SystemStats::Windows )
  };
  String name, url, eval, exec, args;
  int os, imp, num;

 Lisp (int i, String n, String u, String p, String e, int o) : 
  imp (i), name (n), url (u), exec (p),
    args (T("")), eval (e), os (o)
  { 
    if ((SystemStats::getOperatingSystemType() & 
	 SystemStats::Windows) != 0)
      exec+=T(".exe");
    else exec=T("/usr/local/bin/") + exec;
  }
  ~Lisp () {}
  bool isLispImplementation(int i) {return ((imp & i) != 0);}
  int getLispIndex () {return num;}
  String getLispName () {return name;}
  String getLispUrl () {return url;}
  String getLispEvalArg () {return eval;}
  String getLispProgram () {return exec;}
  void setLispProgram (String e) {exec=e;}
  String getLispProgramArgs () {return args;}
  void setLispProgramArgs (String a) {args=a;}
  bool isSupportedOS (int o=-1) {
    if (o<0) o=getHostOS() ;
    return ((os & o) != 0);
  }
}; 

class ASDF {
  String name, path, oper, before, after;
  int flags [NUM_LISPS];
  bool loa;
 public:
  enum {Grace=0, CM}; // enumerate "required" systems (?)
  ASDF (String n, String p, int f0, int f1, int f2, String o=T("asdf:load-op"),
	String b=String::empty, String a=String::empty) {
    name=n;
    path=p;
    flags[0]=f0; flags[1]=f1; flags[2]=f2;
    oper=o;
    before=b;
    after=a;
    loa=false;
  }

  ~ASDF () {}
  String getPathName() {return path;}
  void setPathName(String p) {path=p;}
  String getASDFName (bool lower=false) {
    if (lower) return name.toLowerCase();
    return name;
  }
  String getASDFFileName () {
    return getASDFName(true) + T(".asd");
  }
  bool isLoadable(Lisp* lisp, int os=-1) {
    if (os<0) os=getHostOS();
    int i=lisp->getLispIndex();
    return ((flags[i] & os) != 0);
  }
  bool isLoaded() {return loa;}
  bool setLoaded(bool f) { loa=f;}
  String findASDFFile(File dir);
  File getDefinitionFile(File dir=File::nonexistent) {
    String path=getPathName();
    if (path != String::empty) return File(path);
    path=findASDFFile(dir);
    if (path != String::empty) return File(path);
    return File::nonexistent;
  }
  String getLoadForm(String path);
};

class LispProcessConnection : public Thread,
			      private MessageListener
{
public:
  LispProcessConnection (const bool callbacksOnMessageThread = true);
  ~LispProcessConnection();

  // message types, must be same as socketserver.lisp !!
  typedef enum MessageType
    {
      msgNone = 0x0,
      msgError,
      msgWarning,
      msgPrintout, 
      msgValues, 
      msgLispEval,
      msgSalEval,
      msgKillLisp, 
      msgLoadSystem,
      msgListPackages,
      msgListFeatures,
      msgBinaryData = 128,  // binary messages > 128
      msgStatus = 0xFF
    } ;
  
  bool connectToSocket (const String& hostName,
			const int portNumber,
			const int timeOutMillisecs);
  bool connectToPipe (const String& pipeName);
  bool createPipe (const String& pipeName);
  void disconnect();
  bool isConnected() const;
  bool sendMessage (const MemoryBlock& message, MessageType messageType);
  virtual void connectionMade() = 0;
  virtual void connectionLost() = 0;
  virtual void messageReceived (const MemoryBlock& message) = 0;
  virtual void handleMessage (const Message& message) = 0; //what to do with message
  
private:
  CriticalSection pipeAndSocketLock;
  Socket* socket;
  NamedPipe* pipe;
  bool callbackConnectionState;
  const bool useMessageThread;
  
  void initialiseWithSocket (Socket* const socket_);
  void initialiseWithPipe (NamedPipe* const pipe_);
  void connectionMadeInt();
  void connectionLostInt();
  void deliverDataInt (const MemoryBlock& data, MessageType messageType);
  bool readNextMessageInt();
  void run();
  LispProcessConnection (const LispProcessConnection&);
  const LispProcessConnection& operator= (const LispProcessConnection&);
};


class LispConnection : public LispProcessConnection, public Timer {
 public:

  OwnedArray<Lisp> lisps;
  Lisp* impl;  // currently selected implementation
  OwnedArray<ASDF> asdfs;

  String host;  // hostname
  int port;  // connection port
  int lpid;  // inferior lisp process id
  File pollfile;
  File lispsysdir;
  int timeout;    // connection timeout (sec)
  int waiting;    // current wait time (ms)
  String lispinfo;

  ConsoleWindow* console;

  LispConnection (ConsoleWindow* w);
  ~LispConnection ();
  String getHost() {return host;}
  void setHost(String v) {host=v;}
  bool isLocalHost();

  // Lisp Implementations

  int numLisps () {return lisps.size();}

  void addLisp (Lisp* l) {
    l->num=numLisps(); // cache array index in object
    lisps.add(l);
  }

  Lisp* getLisp (int i=-1) {
    if (i<0) return impl;
    return lisps[i];
  }

  void setLisp (Lisp* l) {impl=l;}

  Lisp* findLisp (int id) {
    for (int i=0; i<numLisps(); i++)
      if (lisps[i]->isLispImplementation(id))
	return lisps[i];
    return (Lisp *)NULL;
  }

  Lisp* findLisp (String name) {
    for (int i=0; i<numLisps(); i++)
      if (lisps[i]->getLispName().equalsIgnoreCase(name) ) 
	return lisps[i];
    return (Lisp *)NULL;
  }

  // Lisp ASDF Systems

  int numASDFs(){return asdfs.size();}
  void addASDF (ASDF* s) {asdfs.add(s);}
  ASDF* getASDF(int i) {return asdfs[i];}
  ASDF* findASDF(String name) {
    for (int i=0; i<numASDFs(); i++)
      if (asdfs[i]->getASDFName().equalsIgnoreCase(name) )
	return asdfs[i];
    return (ASDF *)NULL;
  }
  bool loadASDF(ASDF* asdf);
  bool chooseASDF();

  // Socket connection

  int getPort() {return port;}
  void setPort(int v) {port=v;}
  int getTimeOut() {return timeout;}
  void setTimeOut(int v) {timeout=v;}

  File getLispSystemsDirectory () {return lispsysdir;}
  void setLispSystemsDirectory (File dir) {lispsysdir=dir;}
  File getPollFile(bool newfile=false);
  void deletePollFile();

  bool isLispStartable();
  bool isLispRunning();
  bool launchLisp();
  void startLisp();
  void stopLisp();
  void timerCallback();

  void connectionMade ();
  void connectionLost ();
  void sendLispSexpr(String sexpr, int msg=msgLispEval);

  void messageReceived (const MemoryBlock &message);
  void handleLoadSystem(const MemoryBlock &message);
  void handleListPackages(const MemoryBlock &message);
  void handleListFeatures(const MemoryBlock &message);

  void postMessage (const MemoryBlock &message);
  void postPrintout (const MemoryBlock &message);
  void postWarning (const MemoryBlock &message);
  void postError (const MemoryBlock &message);
  void postValues (const MemoryBlock &message);
  void handleBinaryData (const MemoryBlock &message);
  void handleMessage (const Message& message);

};

class ConfigureLispView  : public Component,
                           public ButtonListener,
                           public LabelListener,
                           public SliderListener
{
public:
  StringArray lisps;
  LispConnection* connection;

  ConfigureLispView (LispConnection* c);
  ~ConfigureLispView();
  //void paint (Graphics& g);
  void resized();
  void buttonClicked (Button* buttonThatWasClicked);
  void labelTextChanged (Label* labelThatHasChanged);
  void sliderValueChanged (Slider* sliderThatWasMoved);
  void chooseLisp(Lisp* lisp);

  bool updateConnection();
  void updateFromConnection();

private:
  GroupComponent* congroup;
  Label* hostlabel;
  Label* hostbuffer;
  Label* portlabel;
  Label* portbuffer;
  Slider* timeslider;
  Label* timelabel;

  GroupComponent* impgroup;
  ToggleButton* sbclbutton;
  ToggleButton* openmclbutton;
  ToggleButton* clispbutton;
  ToggleButton* custombutton;
  Label* proglab;
  Label* argslab;
  Label* progbuf;
  Label* argsbuf;

  GroupComponent* sysgroup;
  Label* syslab;
  Label* sysbuf;

  TextButton* okbutton;
  TextButton* cancelbutton;

};


#endif

