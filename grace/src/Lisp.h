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
#include "Grace.h"

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
  virtual void handleMessage (const Message& message) = 0; //what to do with message
  
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
  LispProcessConnection (const LispProcessConnection&);
  const LispProcessConnection& operator= (const LispProcessConnection&);
};


class LispConnection : public LispProcessConnection, public Timer {
 public:
  String host;  // hostname
  int port;  // connection port
  int lpid;  // inferior lisp process id
  File pollfile;
  int timeout;    // connection timeout (sec)
  int waiting;    // current wait time (ms)
  StringArray loaded; // array of loaded systems and files.
  int cmMinVersion;
  bool cmAutoLoad;
  ConsoleWindow* console;

  LispConnection (ConsoleWindow* w);
  ~LispConnection ();
  String getHost() {return host;}
  void setHost(String v) {host=v;}
  bool isLocalHost();

  bool isLoaded(ASDF* a) ;
  void setLoaded(ASDF* a) ;
  bool isLoaded(File f) ;
  void setLoaded(File f) ;

  void clearLoaded() ;
  void chooseAndLoadASDF();
  bool loadASDF(ASDF* asdf) ;
  void chooseAndLoadFile();
  bool loadFile(File f) ;
  void chooseAndCompileFile();
  bool compileFile(File f) ;

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

  const PopupMenu getLispMenu();
  void performLispCommand(CommandID id);
  void showConfigureLispWindow();
};

class ConfigureLispView  : public Component,
  public ButtonListener,
  public ComboBoxListener
{
public:
  StringArray lisps;
  LispConnection* connection;
  ConfigureLispView (LispConnection* c);
  ~ConfigureLispView();
  void resized();
  void buttonClicked (Button* buttonThatWasClicked);
  void comboBoxChanged (ComboBox* menu);
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
  Label* lisplabel;
  ComboBox* lispmenu;

  Label* proglab;
  Label* argslab;
  FilenameComponent* progbuf;
  Label* argsbuf;

  GroupComponent* sysgroup;
  Label* syslab;
  FilenameComponent* sysbuf;

  ToggleButton* autobutton;
  ToggleButton* autocmbutton;
  TextButton* okbutton;
  TextButton* cancelbutton;

};

#endif
