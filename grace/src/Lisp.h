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
  
  typedef enum MessageType
    {
      msgString = 0x0,
      msgBinaryData,

      msgError,
      msgWarning,
      msgPrintout
    } ;
  
  bool connectToSocket (const String& hostName,
			const int portNumber,
			const int timeOutMillisecs);
  bool connectToPipe (const String& pipeName);
  bool createPipe (const String& pipeName);
  void disconnect();
  bool isConnected() const;
  bool sendMessage (const MemoryBlock& message, MessageType messageType=msgString);
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
  void deliverDataInt (const MemoryBlock& data);
  bool readNextMessageInt();
  void run();
  LispProcessConnection (const LispProcessConnection&);
  const LispProcessConnection& operator= (const LispProcessConnection&);
};


class LispConnection : public LispProcessConnection {
public:
  enum {local=1, remote};
  enum {SBCL=1, OpenMCL, CLisp, Custom};
  int type;  // local or remote
  String host;  // hostname
  int port;  // connection port
  int wait;  // timeout after
  int lpid;  // inferior lisp process id
  int impl;  // SBCL, OpenMCL ...
  String lisp; // program to exec
  String args; // program args
  ConsoleWindow* console;

  LispConnection (ConsoleWindow* w);
  ~LispConnection ();
  int getType() {return type;}
  void setType(int v) {type=v;}
  String getHost() {return host;}
  void setHost(String v) {host=v;}
  int getPort() {return port;}
  void setPort(int v) {port=v;}
  int getWait() {return wait;}
  void setWait(int v) {wait=v;}
  int getImplementation() {return impl;}
  void setImplementation(int v) {impl=v;}
  String getExecutable() {return lisp;}
  void setExecutable(String v) {lisp=v;}
  String getArguments() {return args;}
  void setArguments(String v) {args=v;}
  bool isLispStartable();
  bool startLisp();
  bool killLisp();
  bool isLispRunning();
  bool connectToLisp();
  void connectionMade ();
  void connectionLost ();
  void sendLispSexpr(String in);
  void testConnection();
  void messageReceived (const MemoryBlock &message);
  
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
  GroupComponent* impgroup;
  ToggleButton* sbclbutton;
  ToggleButton* openmclbutton;
  ToggleButton* clispbutton;
  ToggleButton* custombutton;
  Label* proglab;
  Label* argslab;
  Label* progbuf;
  Label* argsbuf;
  GroupComponent* congroup;
  Label* hostlabel;
  Label* hostbuffer;
  Label* portlabel;
  Label* portbuffer;
  Slider* timeslider;
  Label* timelabel;
  TextButton* okbutton;
  TextButton* cancelbutton;

};

#endif

