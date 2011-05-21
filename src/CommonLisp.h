/*=======================================================================*
  Copyright (C) 2007-2009 Todd Ingalls, Rick Taube.
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#ifndef CL_H
#define CL_H

#include "Libraries.h"

#include "Console.h"

class CLProcessThread : public Thread, private MessageListener
{
public:
  CLProcessThread (const bool callbacksOnMessageThread = true);
  ~CLProcessThread();

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
      msgErrorDisconnect,
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
  virtual void handleMessage (const Message& message) = 0;
  
private:
  CriticalSection pipeAndSocketLock;
  StreamingSocket* socket;
  NamedPipe* pipe;
  bool callbackConnectionState;
  const bool useMessageThread;
  
  void initialiseWithSocket (StreamingSocket* const socket_);
  void initialiseWithPipe (NamedPipe* const pipe_);
  void connectionMadeInt();
  void connectionLostInt();
  void deliverDataInt (const MemoryBlock& data, MessageType messageType);
  bool readNextMessageInt();
  void run();
  CLProcessThread (const CLProcessThread&);
  const CLProcessThread& operator= (const CLProcessThread&);
};


class CommonLisp : public CLProcessThread, public Timer {
 public:
  String host;  // hostname
  int port;  // connection port
  int lpid;  // inferior lisp process id
  File pollfile;
  int timeout;    // connection timeout (sec)
  int waiting;    // current wait time (ms)
  StringArray loaded; // array of loaded systems and files.

  CommonLisp ();
  ~CommonLisp ();
  String getHost() {return host;}
  void setHost(String v) {host=v;}
  bool isLocalHost();

  // Socket connection

  int getPort() {return port;}
  void setPort(int v) {port=v;}
  int getTimeOut() {return timeout;}
  void setTimeOut(int v) {timeout=v;}

  File getPollFile(bool newfile=false);
  void deletePollFile();

  bool isLispStartable();
  bool isLispRunning();
  bool launchLisp();
  void startLisp();
  void stopLisp();
  void timerCallback();

  String getLispProgram();
  void setLispProgram(String prog);
  String getLispProgramArgs();
  void setLispProgramArgs(String args);
  String getCommonMusicDirectory();
  void setCommonMusicDirectory(String dir);
  bool getLispLaunchAtStartup();
  void setLispLaunchAtStartup(bool flag);

  void eval(String expr, bool issal=false);
  void load(File file, bool addtorecent=true);
  void compileFile(File file);

  String escapeForDOS(String path);
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

  void showConfigureLispWindow();

  juce_DeclareSingleton (CommonLisp, true)
};

#endif
