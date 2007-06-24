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

class LispProcessConnection : public Thread,
			      private MessageListener
{
public:
  LispProcessConnection (const bool callbacksOnMessageThread = true);
  ~LispProcessConnection();

  // message types, must be same as socketserver.lisp !!
  typedef enum MessageType
    {
      msgBinaryData  = 0x0,
      // grace->lisp
      msgLispEval,
      msgSalEval,
      // lisp->grace
      msgError,
      msgWarning,
      msgPrintout, 
      msgValues, 
      msgKillLisp, 
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


class LispConnection : public LispProcessConnection,
  public Timer
{
 public:
  enum {local=1, remote};
  enum {SBCL=1, OpenMCL, CLisp};
  int type;  // local or remote
  String host;  // hostname
  int port;  // connection port
   int lpid;  // inferior lisp process id
  int impl;  // SBCL, OpenMCL ...
  String lisp; // program to exec
  String args; // program args
  File pollfile;
  File lispexedir;
  File lispsysdir;
  int timeout;    // connection timeout (sec)
  int waiting;    // current wait time (ms)

 String lispinfo;

  ConsoleWindow* console;

  LispConnection (ConsoleWindow* w);
  ~LispConnection ();
  int getType() {return type;}
  void setType(int v) {type=v;}
  String getHost() {return host;}
  void setHost(String v) {host=v;}
  bool isLocalHost();
  int getPort() {return port;}
  void setPort(int v) {port=v;}
  int getTimeOut() {return timeout;}
  void setTimeOut(int v) {timeout=v;}
  int getImplementation() {return impl;}
  void setImplementation(int v) {impl=v;}
  String getExecutable() {return lisp;}
  void setExecutable(String v) {lisp=v;}
  String getArguments() {return args;}
  void setArguments(String v) {args=v;}

  File getGraceResourceDirectory(String sub=String::empty);
  File getLispExecutableDirectory(String sub=String::empty);

  File getLispSystemsDirectory(String sub=String::empty);
  void setLispSystemsDirectory(File dir) {lispsysdir=dir;}

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
  void sendLispSexpr(String in);
  void testConnection();
  void messageReceived (const MemoryBlock &message);

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
  String getApplication();  
  void setApplication(String app);
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

