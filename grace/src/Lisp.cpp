/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

#include "Lisp.h"
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

ConfigureLispView::ConfigureLispView (LispConnection* c)
    : impgroup (0),
      sbclbutton (0),
      openmclbutton (0),
      clispbutton (0),
      custombutton (0),
      proglab (0),
      argslab (0),
      progbuf (0),
      argsbuf (0),
      congroup (0),
      hostlabel (0),
      hostbuffer (0),
      portlabel (0),
      portbuffer (0),
      timeslider (0),
      timelabel (0),
      magiclabel (0),
      magicbuffer (0),
      okbutton (0),
      cancelbutton (0)
{ 
  connection=c;
  addAndMakeVisible (impgroup = new GroupComponent (String::empty,
						    T("Application")));

  addAndMakeVisible (sbclbutton = new ToggleButton (String::empty));
  sbclbutton->setButtonText (T("SBCL"));
  sbclbutton->addButtonListener (this);
  sbclbutton->setRadioGroupId(1);

  addAndMakeVisible (openmclbutton = new ToggleButton (String::empty));
  openmclbutton->setButtonText (T("OpenMCL"));
  openmclbutton->addButtonListener (this);
  openmclbutton->setRadioGroupId(1);

  addAndMakeVisible (clispbutton = new ToggleButton (String::empty));
  clispbutton->setButtonText (T("CLisp"));
  clispbutton->addButtonListener (this);
  clispbutton->setRadioGroupId(1);

  addAndMakeVisible (custombutton = new ToggleButton (String::empty));
  custombutton->setButtonText (T("Custom"));
  custombutton->addButtonListener (this);
  custombutton->setRadioGroupId(1);

  addAndMakeVisible(proglab = new Label(String::empty,T("Executable:")));
  proglab->setFont (Font (15.0000f, Font::plain));
  proglab->setJustificationType (Justification::centredRight);
  proglab->setEditable (false, false, false);

  addAndMakeVisible (argslab = new Label (String::empty,
						 T("Arguments:")));
  argslab->setFont (Font (15.0000f, Font::plain));
  argslab->setJustificationType (Justification::centredRight);

  addAndMakeVisible(progbuf = new Label(String::empty, String::empty));
  progbuf->setFont(Font (15.0000f, Font::plain));
  progbuf->setJustificationType(Justification::centredLeft);
  // true= Return checks existence of executable
  progbuf->setEditable(false, false, true);
  progbuf->setColour(Label::outlineColourId, Colours::black);
  progbuf->setColour(Label::backgroundColourId, Colours::white);
  progbuf->addListener(this);

  addAndMakeVisible(argsbuf = new Label(String::empty, String::empty));
  argsbuf->setFont( Font(15.0000f, Font::plain));
  argsbuf->setJustificationType(Justification::centredLeft);
  argsbuf->setEditable(true, true, false);
  argsbuf->setColour(Label::outlineColourId, Colours::black);
  argsbuf->setColour(Label::backgroundColourId, Colours::white);
  argsbuf->addListener(this);

  addAndMakeVisible(congroup = new GroupComponent(String::empty,
						  T("Connection")));
  addAndMakeVisible(hostlabel = new Label(String::empty, T("Host:")));
  hostlabel->setFont( Font(15.0000f, Font::plain));
  hostlabel->setJustificationType(Justification::centredRight);
  hostlabel->setEditable(false, false, false);

  addAndMakeVisible(hostbuffer = new Label (String::empty,
					     String::empty));
  hostbuffer->setFont(Font(15.0000f, Font::plain));
  hostbuffer->setJustificationType(Justification::centredLeft);
  hostbuffer->setEditable(false, false, false);
  hostbuffer->setColour(Label::outlineColourId, Colours::black);
  hostbuffer->setColour(Label::backgroundColourId, Colours::white);

  addAndMakeVisible(portlabel = new Label(String::empty, T("Port:")));
  portlabel->setFont(Font (15.0000f, Font::plain));
  portlabel->setJustificationType(Justification::centredRight);
  portlabel->setEditable(false, false, false);

  addAndMakeVisible (portbuffer = new Label(String::empty, String::empty));
  portbuffer->setFont (Font (15.0000f, Font::plain));
  portbuffer->setJustificationType (Justification::centredLeft);
  portbuffer->setEditable (true, true, false);
  portbuffer->setColour (Label::outlineColourId, Colours::black);
  portbuffer->setColour (Label::backgroundColourId, Colours::white);
  portbuffer->addListener (this);

  addAndMakeVisible(timeslider = new Slider (String::empty));
  timeslider->setRange(5, 60, 1);
  timeslider->setSliderStyle(Slider::LinearHorizontal);
  timeslider->setTextBoxStyle(Slider::TextBoxLeft, false, 30, 20);
  timeslider->addListener(this);

  addAndMakeVisible(timelabel = new Label(String::empty, T("Timeout:")));
  timelabel->setFont( Font(15.0000f, Font::plain));
  timelabel->setJustificationType(Justification::centredRight);
  timelabel->setEditable(false, false, false);

  addAndMakeVisible(magiclabel = new Label(String::empty, T("Magic #:")));
  magiclabel->setFont(Font (15.0000f, Font::plain));
  magiclabel->setJustificationType(Justification::centredRight);
  magiclabel->setEditable(false, false, false);

  addAndMakeVisible(magicbuffer = new Label(String::empty, String::empty));
  magicbuffer->setFont (Font (15.0000f, Font::plain));
  magicbuffer->setJustificationType (Justification::centredLeft);
  // dont allow editing for now...
  magicbuffer->setEditable (false, false, false);
  magicbuffer->setColour (Label::outlineColourId, Colours::black);
  magicbuffer->setColour (Label::backgroundColourId, Colours::white);
  magicbuffer->addListener (this);

  addAndMakeVisible (okbutton = new TextButton (String::empty));
  okbutton->setButtonText (T("OK"));
  okbutton->addButtonListener (this);

  addAndMakeVisible (cancelbutton = new TextButton (String::empty));
  cancelbutton->setButtonText (T("Cancel"));
  cancelbutton->addButtonListener (this);
  updateFromConnection();
  setSize(408, 280);
}

ConfigureLispView::~ConfigureLispView () {
    deleteAndZero (impgroup);
    deleteAndZero (sbclbutton);
    deleteAndZero (openmclbutton);
    deleteAndZero (clispbutton);
    deleteAndZero (custombutton);
    deleteAndZero (proglab);
    deleteAndZero (argslab);
    deleteAndZero (progbuf);
    deleteAndZero (argsbuf);
    deleteAndZero (congroup);
    deleteAndZero (hostlabel);
    deleteAndZero (hostbuffer);
    deleteAndZero (portlabel);
    deleteAndZero (portbuffer);
    deleteAndZero (timeslider);
    deleteAndZero (timelabel);
    deleteAndZero (magiclabel);
    deleteAndZero (magicbuffer);
    deleteAndZero (okbutton);
    deleteAndZero (cancelbutton);
}

//void ConfigureLispView::paint (Graphics& g) {
//  g.fillAll (Colours::white);
//}

void ConfigureLispView::resized() {
    impgroup->setBounds (8, 120, 392, 120);
    sbclbutton->setBounds (16, 136, 90, 24);
    openmclbutton->setBounds (112, 136, 90, 24);
    clispbutton->setBounds (208, 136, 90, 24);
    custombutton->setBounds (304, 136, 88, 24);
    proglab->setBounds (16, 168, 96, 24);
    argslab->setBounds (16, 200, 96, 24);
    progbuf->setBounds (120, 168, 264, 24);
    argsbuf->setBounds (120, 200, 264, 24);
    congroup->setBounds (8, 8, 392, 96);
    hostlabel->setBounds (24, 32, 40, 24);
    hostbuffer->setBounds (72, 32, 152, 24);
    portlabel->setBounds (240, 32, 40, 24);
    portbuffer->setBounds (288, 32, 96, 24);
    timeslider->setBounds (96, 64, 104, 24);
    timelabel->setBounds (24, 64, 64, 24);
    magiclabel->setBounds (216, 64, 64, 24);
    magicbuffer->setBounds (288, 64, 96, 24);
    okbutton->setBounds (336, 248, 60, 24);
    cancelbutton->setBounds (264, 248, 60, 24);
}

void ConfigureLispView::updateFromConnection () {
  hostbuffer->setText(connection->getHost(), true);
  portbuffer->setText(String(connection->getPort()), true);
  timeslider->setValue((double)(connection->getWait()), true);
  magicbuffer->setText(String((uint32)(connection->getMagicNumber())), true);
  if (connection->getType() == LispConnection::local)
    hostbuffer->setEditable(false, false);
  else
    hostbuffer->setEditable(true, true);
  int i=connection->getImplementation();
  if (i==LispConnection::SBCL) 
    sbclbutton->setToggleState(true,false);
  else if (i==LispConnection::OpenMCL) 
    openmclbutton->setToggleState(true,false);
  else if (i==LispConnection::CLisp) 
    clispbutton->setToggleState(true,false);
  else if (i==LispConnection::Custom) 
    custombutton->setToggleState(true,false);
  progbuf->setText(connection->getExecutable(), true);
  argsbuf->setText(connection->getArguments(), true);
}

bool ConfigureLispView::updateConnection () {
  String s1, s2, s3;
  int i1, i2, i3=-1;
  uint32 u1;
  s1=hostbuffer->getText();
  i1=portbuffer->getText().getIntValue();
  if (i1<1024) {
    portbuffer->setColour (Label::backgroundColourId, Colours::lightpink);
    return false;
  }
  i2=(int)(timeslider->getValue());
  u1=(uint32)(magicbuffer->getText().getIntValue());
  if (sbclbutton->getToggleState()) i3=LispConnection::SBCL;
  else if (openmclbutton->getToggleState()) i3=LispConnection::OpenMCL;
  else if (clispbutton->getToggleState()) i3=LispConnection::CLisp;
  else if (custombutton->getToggleState()) i3=LispConnection::Custom;
  if (i3<LispConnection::SBCL) return false;
  s2=progbuf->getText();
  if (s2 != String::empty) {
    File file=File(s2);
    if ( !file.existsAsFile() ) {
      progbuf->setColour(Label::backgroundColourId, Colours::lightpink);
      return false;
    }
  }
  s3=argsbuf->getText();
  //printf("Lisp config: host=%s, port=%d wait=%d magic=%u lisp=%d prog=%s args=%s\n",
  //       s1.toUTF8(), i1, i2, u1, i3,s2.toUTF8(),s3.toUTF8()) ;
  connection->setHost(s1);
  connection->setPort(i1);
  connection->setWait(i2);
  connection->setMagicNumber(u1);
  connection->setImplementation(i3);
  connection->setExecutable(s2);
  connection->setArguments(s3);
  return true;
}

void ConfigureLispView::setApplication(String path) {
  progbuf->setEditable(false, false, true); // assume not Custom
  progbuf->setText(path, true); // force check of exe file
  argsbuf->setText(String::empty, true);
}

String ConfigureLispView::getApplication() {
  String path=progbuf->getText();
  if ( path==String::empty )
    return path;
  else {
    File file=File(path);    
    if ( file.existsAsFile() )
      return path;
    else return String::empty;
  }
}

void ConfigureLispView::buttonClicked (Button* buttonThatWasClicked) {
  DialogWindow* win;
  if (buttonThatWasClicked == okbutton) {
    if (! updateConnection() ) return;
    win=(DialogWindow*)getTopLevelComponent();
    win->getCloseButton()->triggerClick();
    return;
  }
  if (buttonThatWasClicked == cancelbutton) {
    win=(DialogWindow*)getTopLevelComponent();
    win->getCloseButton()->triggerClick();
    return;
  }

  if (buttonThatWasClicked == sbclbutton) {
    setApplication( T("/usr/local/bin/sbcl"));
    }
  else if (buttonThatWasClicked == openmclbutton) {
    setApplication( T("/usr/local/bin/openmcl"));
    }
  else if (buttonThatWasClicked == clispbutton) {
    setApplication( T("/usr/local/bin/clisp"));
    }
  else if (buttonThatWasClicked == custombutton) {
    progbuf->setEditable(true, true, true);
    progbuf->setColour(Label::backgroundColourId, Colours::white);
    progbuf->setText(String::empty, false);
    argsbuf->setText(String::empty, false);
    }
}

void ConfigureLispView::labelTextChanged (Label* labelThatHasChanged) {
  if (labelThatHasChanged == progbuf) {
    // check lisp program to make sure it exists.
    // show red background if lisp executable doesnt exist.
    String path=progbuf->getText();
    if ( path == String::empty) 
      progbuf->setColour(Label::backgroundColourId, Colours::white);
    else {
      File file=File(path);
      if ( file.existsAsFile() )
	progbuf->setColour(Label::backgroundColourId, Colours::white);
      else
	progbuf->setColour(Label::backgroundColourId, Colours::lightpink);
    }
  }
  else if (labelThatHasChanged == argsbuf) {
  }
  else if (labelThatHasChanged == portbuffer) {
    int i1=portbuffer->getText().getIntValue();
    if (i1<1024)
      portbuffer->setColour (Label::backgroundColourId, Colours::lightpink);
    else
      portbuffer->setColour (Label::backgroundColourId, Colours::white);
  }
  else if (labelThatHasChanged == magicbuffer) {
  }
}

void ConfigureLispView::sliderValueChanged (Slider* sliderThatWasMoved) {
    if (sliderThatWasMoved == timeslider) {
    }
}

//=========================================================================
//=========================================================================

LispConnection::LispConnection (ConsoleWindow* w) 
   : InterprocessConnection(true),
    type (local),
    host (T("localhost")),
    port (8000),
    wait (15),
    lpid (-1),
    mnum (0xf2b49e2c),
    impl (0),
    lisp (String::empty),
    args (String::empty)
{
  console=w;
}

LispConnection::~LispConnection () {
 }

bool LispConnection::isLispStartable () {
  return ((type==remote) || (lisp != String::empty));
}  

bool LispConnection::startLisp () {
/* 
  // THIS WORKS BUT IS COMMENTED OUT UNTIL I CAN FIGURE OUT HOW TO
  // WAIT FOR THE SERVER TO LOAD UP BEFORE ATTEMPTING A CONNECTION.

  String command=getExecutable();
  if (getArguments() != String::empty)
    command += getArguments();
  command +=  T(" --load \"/Lisp/grace/src/socketserver.lisp\"");
  command +=  T(" --eval '(start-server " );
  command += String(getPort());
  command += ")'" ;

  printf("Starting lisp: %s\n", command.toUTF8() );

  char* const argv[4] = { "/bin/sh", "-c", (char*)(const char*)command, 0};
  const int cpid = fork();


  if (cpid == 0)  {
    // Child process
    if (execve(argv[0], argv, 0) < 0)
      exit (0);
  }
  else if (cpid < 0) {
    printf("Failed to start Lisp.\n");
    lpid=-1;
    return false;
  }
  else {
    // Parent process
    lpid=cpid;
    printf("Lisp started, pid=%d\n", lpid);
    connectToLisp();
  }
  return true;
*/

  return  connectToLisp();
}

bool LispConnection::connectToLisp () {
  String message = T("Connecting to Lisp on '") + getHost() +
    T("' port ") + String(getPort()) + T("...\n") ;

  console->consolePrint(message);
  if ( connectToSocket( getHost(), getPort(), (getWait()*1000) ) ) {
    console->consolePrint( T("OK =:)\n") );
    return true;
  }  
  else console->consoleError( T("FAILED >:(\n") );
  return false;
}

bool LispConnection::isLispRunning () {
  return (lpid != -1);
}

bool LispConnection::killLisp () {
  if ( isConnected() )
    disconnect();

  if ( isLispRunning() ) {
    kill(lpid, SIGKILL);
    lpid=-1;
    return true;
  }
  return false;
}

void LispConnection::sendLispSexpr(String sexpr) {
  if (! isConnected() ){
    console->consoleWarning(T("Lisp not connected.\n"));
    return;
  }
  int len=sexpr.length();
  printf("Grace sending: '%s'\n", sexpr.toUTF8());
  MemoryBlock mem=MemoryBlock(len, true);  
  for (int i=0; i<len; i++)
    mem[i]=(char)sexpr[i];
  sendMessage(mem);
}

void LispConnection::testConnection() {
  if (! isConnected() )  {
    console->consoleWarning(T("Lisp not connected.\n"));
    return;
  }
  String test= T("(+");
  int num = 2+Random::getSystemRandom().nextInt(9);
  for (int i=0; i<num; i++)
    test = test + T(" ") + String(Random::getSystemRandom().nextInt(100000));
  test += T(")");
  sendLispSexpr(test);
}  

void LispConnection::connectionMade () {
}

void LispConnection::connectionLost () {
  console->consoleWarning(T("Lisp connection lost =:/\n"));
}

void LispConnection::messageReceived (const MemoryBlock &message) {
  int len=message.getSize();
  String text=String((const char *)message, len);
  console->consolePrint(text);
  console->consoleTerpri();
}
