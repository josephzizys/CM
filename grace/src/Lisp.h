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

class LispConnection : public InterprocessConnection {
 public:
  enum {local=1, remote};
  enum {SBCL=1, OpenMCL, CLisp, Custom};
  int type;  // local or remote
  String host;  // hostname
  int port;  // connection port
  int wait;  // timeout after
  int lpid;  // inferior lisp process id
  uint32 mnum;  //magic number?
  int impl;  // SBCL, OpenMCL ...
  String lisp; // program to exec
  String args; // program args

 LispConnection () 
   : type (local),
    host (T("localhost")),
    port (8000),
    wait (15),
    lpid (-1),
    mnum (0xf2b49e2c),
    impl (0),
    lisp (String::empty),
    args (String::empty)
    {
    }

  ~LispConnection () { }

  int getType() {return type;}
  void setType(int v) {type=v;}
  String getHost() {return host;}
  void setHost(String v) {host=v;}
  int getPort() {return port;}
  void setPort(int v) {port=v;}
  int getWait() {return wait;}
  void setWait(int v) {wait=v;}
  uint32 getMagicNumber() {return mnum;}
  void setMagicNumber(uint32 v) {mnum=v;}
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
  void connectionMade ();
  void connectionLost ();
  void messageReceived (const MemoryBlock &message);
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
  Label* magiclabel;
  Label* magicbuffer;
  TextButton* okbutton;
  TextButton* cancelbutton;

};

#endif

