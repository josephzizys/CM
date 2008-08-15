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
#include "Enumerations.h"

#if LINUX || MACOSX
#include <unistd.h>
#endif

//==============================================================================
LispProcessConnection::LispProcessConnection (const bool callbacksOnMessageThread)
  : Thread (T("Grace to Lisp connection")),
    socket (0),
    pipe (0),
    callbackConnectionState (false),
    useMessageThread (callbacksOnMessageThread)
    
{
}

LispProcessConnection::~LispProcessConnection()
{
  disconnect();
}


//==============================================================================
bool LispProcessConnection::connectToSocket (const String& hostName,
					     const int portNumber,
					     const int timeOutMillisecs)
{
  disconnect();
  
  const ScopedLock sl (pipeAndSocketLock);
  socket = new StreamingSocket();
  
  if (socket->connect (hostName, portNumber, timeOutMillisecs))
    {
      connectionMadeInt();
      startThread();
      return true;
    }
  else
    {
      deleteAndZero (socket);
      return false;
    }
}

bool LispProcessConnection::connectToPipe (const String& pipeName)
{
  disconnect();
  
  NamedPipe* const newPipe = new NamedPipe();
  
  if (newPipe->openExisting (pipeName))
    {
      const ScopedLock sl (pipeAndSocketLock);
      initialiseWithPipe (newPipe);
      return true;
    }
  else
    {
      delete newPipe;
      return false;
    }
}

bool LispProcessConnection::createPipe (const String& pipeName)
{
  disconnect();
  
  NamedPipe* const newPipe = new NamedPipe();
  
  if (newPipe->createNewPipe (pipeName))
    {
      const ScopedLock sl (pipeAndSocketLock);
      initialiseWithPipe (newPipe);
      return true;
    }
  else
    {
      delete newPipe;
      return false;
    }
}

void LispProcessConnection::disconnect()
{
  if (socket != 0)
    socket->close();
  
  if (pipe != 0)
    {
      pipe->cancelPendingReads();
      pipe->close();
    }
  
  stopThread (4000);
  
  {
    const ScopedLock sl (pipeAndSocketLock);
    deleteAndZero (socket);
    deleteAndZero (pipe);
  }
  
  connectionLostInt();
}

bool LispProcessConnection::isConnected() const
{
  const ScopedLock sl (pipeAndSocketLock);
  
  return ((socket != 0 && socket->isConnected())
	  || (pipe != 0 && pipe->isOpen()))
    && isThreadRunning();
}

//==============================================================================
bool LispProcessConnection::sendMessage (const MemoryBlock& message,
					 MessageType messageType)
// changed: force type to be specified...
{
  juce::uint32 messageHeader[2];
  messageHeader [0] = swapIfBigEndian ((juce::uint32) messageType);
  messageHeader [1] = swapIfBigEndian ((juce::uint32) message.getSize());

  MemoryBlock messageData (sizeof (messageHeader) + message.getSize());
  messageData.copyFrom(messageHeader, 0, sizeof (messageHeader));
  messageData.copyFrom(message.getData(), sizeof (messageHeader), message.getSize());
  
  int bytesWritten = 0;
  
  const ScopedLock sl (pipeAndSocketLock);
  
  if (socket != 0)
    {
      bytesWritten = socket->write (messageData.getData(), messageData.getSize());
    }
  else if (pipe != 0)
    {
      bytesWritten = pipe->write (messageData.getData(), messageData.getSize());
    }
  
  if (bytesWritten < 0)
    {
      // error..
      return false;
    }
  
  return (bytesWritten == messageData.getSize());
}

//==============================================================================
void LispProcessConnection::initialiseWithSocket (StreamingSocket* const socket_)
{
  jassert (socket == 0);
  socket = socket_;
  connectionMadeInt();
  startThread();
}

void LispProcessConnection::initialiseWithPipe (NamedPipe* const pipe_)
{
  jassert (pipe == 0);
  pipe = pipe_;
  connectionMadeInt();
  startThread();
}


void LispProcessConnection::connectionMadeInt()
{
  if (! callbackConnectionState)
    {
      callbackConnectionState = true;
      
      if (useMessageThread)
	postMessage (new Message (msgStatus, 1, 0, 0));
      else
	connectionMade();
    }
}

void LispProcessConnection::connectionLostInt()
{
  if (callbackConnectionState)
    {
      callbackConnectionState = false;
      
      if (useMessageThread)
	postMessage (new Message (msgStatus, 2, 0, 0));
      else
	connectionLost();
    }
}

void LispProcessConnection::deliverDataInt (const MemoryBlock& data,  MessageType messageType )
{
  jassert (callbackConnectionState);
  
  if (useMessageThread)
    postMessage (new Message (messageType , 0, 0, new MemoryBlock (data)));
  else
    messageReceived (data);
}

//==============================================================================
bool LispProcessConnection::readNextMessageInt()
{
  const int maximumMessageSize = 1024 * 1024 * 10; // sanity check
  
  juce::uint32 messageHeader[2];
  const int bytes = (socket != 0) ? socket->read (messageHeader, sizeof (messageHeader))
    : pipe->read (messageHeader, sizeof (messageHeader));
  
  if (bytes == sizeof (messageHeader) )
    {
      const int bytesInMessage = (int) swapIfBigEndian (messageHeader[1]);
      
      if (bytesInMessage > 0 && bytesInMessage < maximumMessageSize)
        {
	  MemoryBlock messageData (bytesInMessage, true);
	  int bytesRead = 0;
	  
	  while (bytesRead < bytesInMessage)
            {
	      if (threadShouldExit())
		return false;
	      
	      const int numThisTime = jmin (bytesInMessage, 65536);
	      const int bytesIn = (socket != 0) ? socket->read (((char*) messageData.getData()) + bytesRead, numThisTime)
		: pipe->read (((char*) messageData.getData()) + bytesRead, numThisTime);
	      
	      if (bytesIn <= 0)
		break;
	      
	      bytesRead += bytesIn;
            }
	  
	  if (bytesRead >= 0)
	    deliverDataInt (messageData, (MessageType)swapIfBigEndian (messageHeader[0]) );
        }
    }
  else if (bytes < 0)
    {
      {
	const ScopedLock sl (pipeAndSocketLock);
	deleteAndZero (socket);
      }
      
      connectionLostInt();
      return false;
    }
  
  return true;
}

void LispProcessConnection::run()
{
  while (! threadShouldExit())
    {
      if (socket != 0)
        {
	  const int ready = socket->waitUntilReady (true, 0);
	  
	  if (ready < 0)
            {
	      {
		const ScopedLock sl (pipeAndSocketLock);
		deleteAndZero (socket);
	      }
	      
	      connectionLostInt();
	      break;
            }
	  else if (ready > 0)
            {
	      if (! readNextMessageInt())
		break;
            }
	  else
            {
	      Thread::sleep (2);
            }
        }
      else if (pipe != 0)
        {
	  if (! pipe->isOpen())
            {
	      {
		const ScopedLock sl (pipeAndSocketLock);
		deleteAndZero (pipe);
	      }
	      
	      connectionLostInt();
	      break;
            }
	  else
            {
	      if (! readNextMessageInt())
		break;
            }
        }
      else
        {
	  break;
        }
    }
}

ConfigureLispView::ConfigureLispView (LispConnection* c)
  : impgroup (0),
    lisplabel(0),
    lispmenu(0),
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
    sysgroup (0),
    syslab (0),
    sysbuf (0),
    okbutton (0),
    cancelbutton (0)
{ 
  connection=c;
  GracePreferences* p=GracePreferences::getInstance();

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
  
  addAndMakeVisible(timeslider = new Slider (String::empty));
  timeslider->setRange(5, 60, 1);
  timeslider->setSliderStyle(Slider::LinearHorizontal);
  timeslider->setTextBoxStyle(Slider::TextBoxLeft, false, 30, 20);
  
  addAndMakeVisible(timelabel = new Label(String::empty, T("Timeout:")));
  timelabel->setFont( Font(15.0000f, Font::plain));
  timelabel->setJustificationType(Justification::centredRight);
  timelabel->setEditable(false, false, false);
  // Lisp Group
  addAndMakeVisible (impgroup = new GroupComponent (String::empty,
						    T("Lisp Implementation")));
  addAndMakeVisible (lispmenu = new ComboBox (String::empty));
  lispmenu->setEditableText (false);
  lispmenu->setJustificationType (Justification::centredLeft);
  lispmenu->setTextWhenNothingSelected (T("Select Lisp"));
  for (int i=0; i<p->numLisps(); i++) {
    lispmenu->addItem (p->getLisp(i)->getLispName(), i+1);
    // disable OpenMCL until I can get it working...
    if ( p->getLisp(i)->getLispName() == T("OpenMCL") )
      lispmenu->setItemEnabled(i+1, false);
  }
  lispmenu->addListener (this);
  addAndMakeVisible(proglab = new Label(String::empty,T("Executable:")));
  proglab->setFont (Font (15.0000f, Font::plain));
  proglab->setJustificationType (Justification::centredRight);
  proglab->setEditable (false, false, false);
  
  addAndMakeVisible(progbuf = new FilenameComponent(String::empty,
						    File::nonexistent,
						    true,
						    false,
						    false,
						    String::empty,
						    String::empty,
						    T("Select Executable")));
  progbuf->setMaxNumberOfRecentFiles(1);

  addAndMakeVisible (argslab = new Label (String::empty,
					  T("Arguments:")));
  argslab->setFont (Font (15.0000f, Font::plain));
  argslab->setJustificationType (Justification::centredRight);
  
  addAndMakeVisible(argsbuf = new Label(String::empty, String::empty));
  argsbuf->setFont( Font(15.0000f, Font::plain));
  argsbuf->setJustificationType(Justification::centredLeft);
  argsbuf->setColour (Label::outlineColourId, Colours::black);
  argsbuf->setColour (Label::backgroundColourId, Colours::white);
  argsbuf->setEditable(true, true, false);

  // System software
  addAndMakeVisible (sysgroup = new GroupComponent (String::empty, T("ASDF Systems Directory")));
  addAndMakeVisible(sysbuf = new FilenameComponent(String::empty, p->getAsdfSystemsDirectory(), true, true, false, String::empty, String::empty, T("Select Directory")));
  sysbuf->setMaxNumberOfRecentFiles(1);

  // buttons
  addAndMakeVisible (autobutton = new ToggleButton (String::empty));
  autobutton->setButtonText (T("Launch lisp at startup"));
  addAndMakeVisible (autocmbutton = new ToggleButton (String::empty));
  autocmbutton->setButtonText (T("Autoload Common Music"));

  addAndMakeVisible (okbutton = new TextButton (String::empty));
  okbutton->setButtonText (T("OK"));
  okbutton->addButtonListener (this);

  addAndMakeVisible (cancelbutton = new TextButton (String::empty));
  cancelbutton->setButtonText (T("Cancel"));
  cancelbutton->addButtonListener (this);
  updateFromConnection();
  setSize(408, 380);
}

ConfigureLispView::~ConfigureLispView () {
    deleteAndZero (congroup);
    deleteAndZero (hostlabel);
    deleteAndZero (hostbuffer);
    deleteAndZero (portlabel);
    deleteAndZero (portbuffer);
    deleteAndZero (timeslider);
    deleteAndZero (timelabel);
    deleteAndZero (impgroup);
    deleteAndZero (lisplabel);
    deleteAndZero (lispmenu);
    deleteAndZero (proglab);
    deleteAndZero (argslab);
    deleteAndZero (progbuf);
    deleteAndZero (argsbuf);
    deleteAndZero (sysgroup);
    deleteAndZero (sysbuf);
    deleteAndZero (autobutton);
    deleteAndZero (autocmbutton);
    deleteAndZero (okbutton);
    deleteAndZero (cancelbutton);
}

void ConfigureLispView::resized() {
    congroup->setBounds (8, 8, 392, 96);
    hostlabel->setBounds (24, 32, 40, 24);
    hostbuffer->setBounds (72, 32, 152, 24);
    portlabel->setBounds (240, 32, 40, 24);
    portbuffer->setBounds (288, 32, 96, 24);
    timeslider->setBounds (96, 64, 104, 24);
    timelabel->setBounds (24, 64, 64, 24);

    impgroup->setBounds (8, 120, 392, 120);
    lispmenu->setBounds (20, 136, 100, 24);
    proglab->setBounds (16, 168, 96, 24);
    progbuf->setBounds (120, 168, 264, 24);
    argslab->setBounds (16, 200, 96, 24);
    argsbuf->setBounds (120, 200, 264, 24);

    sysgroup->setBounds (8, argslab->getY()+56, 392, 64);
    sysbuf->setBounds (24, sysgroup->getY()+24, 96+264, 24);

    autobutton->setBounds (8, sysbuf->getY()+45, 170, 24); //60
    autocmbutton->setBounds (8, sysbuf->getY()+65, 170, 24);

    okbutton->setBounds (336, sysbuf->getY()+60, 60, 24);
    cancelbutton->setBounds (264, sysbuf->getY()+60, 60, 24);
}

void ConfigureLispView::updateFromConnection () {
  GraceApp* app = (GraceApp*)JUCEApplication::getInstance();
  GracePreferences* p=GracePreferences::getInstance();
  hostbuffer->setText(connection->getHost(), true);
  portbuffer->setText(String(connection->getPort()), true);
  timeslider->setValue((double)(connection->getTimeOut()), true);
  if ( connection->isLocalHost() )
    hostbuffer->setEditable(false, false);
  else
    hostbuffer->setEditable(true, true);

  Lisp* l=p->getLispToLaunch();
  if (l == (Lisp *)NULL)
    ; //   lispmenu->setSelectedId( 1, false);
  else
    lispmenu->setSelectedId( p->getLispIndex(l)+1, false);

  sysbuf->setMaxNumberOfRecentFiles(2);
  String asdfdir=p->getAsdfSystemsDirectory().getFullPathName();
  String resodir=app->getResourceDirectoryPathName();

  sysbuf->addRecentlyUsedFile(File(asdfdir));
  if (asdfdir != resodir) 
    sysbuf->addRecentlyUsedFile(File(resodir));
  sysbuf->setCurrentFile(asdfdir, false);
  autobutton->setToggleState(p->isLispLaunchAtStartup(),false);
  autocmbutton->setToggleState(p->autoLoadCM(),false);
}

bool ConfigureLispView::updateConnection () {
  GracePreferences* p=GracePreferences::getInstance();
  String s1, s2, s3, s4;
  int i1, i2, i3=-1;
  juce::uint32 u1;

  s1=hostbuffer->getText();
  i1=portbuffer->getText().getIntValue();
  i2=(int)(timeslider->getValue());

  int id=lispmenu->getSelectedId();
  if (id>0)
    p->setLispToLaunch(p->getLisp(id-1));

  s2=progbuf->getCurrentFile().getFullPathName();
  s3=argsbuf->getText();
  s4=sysbuf->getCurrentFile().getFullPathName();

  connection->setHost(s1);
  connection->setPort(i1);
  connection->setTimeOut(i2);
  Lisp* l=p->getLispToLaunch();
  if (l != (Lisp *)NULL) {
    l->setLispProgram(s2);
    l->setLispProgramArgs(s3);
  }
  p->setAsdfSystemsDirectory(File(s4));
  p->setLispLaunchAtStartup(autobutton->getToggleState());
  p->setAutoLoadCM(autocmbutton->getToggleState());
  return true;
}

void ConfigureLispView::chooseLisp(Lisp* lisp) {
  // set Executable and Arguments buffers from selected lisp
  if (lisp != (Lisp *)NULL) {
    progbuf->setCurrentFile(File(lisp->getLispProgram()), false); 
    argsbuf->setText(lisp->getLispProgramArgs(), false);
  }
  else {
    progbuf->setCurrentFile(File::nonexistent, false);
    argsbuf->setText(String::empty, false);
  }
}

void ConfigureLispView::comboBoxChanged (ComboBox* menu) {
  GracePreferences* p=GracePreferences::getInstance();
  int id=menu->getSelectedId();
  if (id>0)
    chooseLisp(p->getLisp(id-1));
  else
    chooseLisp((Lisp *) NULL);
}

void ConfigureLispView::buttonClicked (Button* buttonThatWasClicked) {
  GracePreferences* p=GracePreferences::getInstance();
  DialogWindow* win;
  if (buttonThatWasClicked == okbutton) {
    if (! updateConnection() ) return;
    win=(DialogWindow*)getTopLevelComponent();
    win->getCloseButton()->triggerClick();
  }
  else if (buttonThatWasClicked == cancelbutton) {
    win=(DialogWindow*)getTopLevelComponent();
    win->getCloseButton()->triggerClick();
  }
}

//=========================================================================
//=========================================================================

LispConnection::LispConnection (ConsoleWindow* w) 
   : LispProcessConnection(true),
     host (T("localhost")),
     port (8000),
     lpid (-1),
     timeout (30),
     pollfile (File::nonexistent),
     cmMinVersion (0x2B2)
{
  console=w;
}

LispConnection::~LispConnection () {
 }

bool LispConnection::isLispRunning () {
  return isConnected();
}  

bool LispConnection::isLispStartable () {
  GracePreferences* p=GracePreferences::getInstance();
  return ( ! isLocalHost() || (p->getLispToLaunch() != (Lisp *)NULL));
}  

bool LispConnection::isLocalHost() {
  return (getHost().equalsIgnoreCase(T("localhost")) ||
	  getHost() == T("127.0.0.1"));
}

File LispConnection::getPollFile(bool newfile) {
  if (newfile) pollfile=File::createTempFile(T("grace"));
  return pollfile;
}

void LispConnection::deletePollFile() {
  getPollFile().deleteFile();
  pollfile=File::nonexistent;
}

#ifdef WINDOWS
String escapeForDOS(String path) {
  return path.replace(T("\\"),T("\\\\"));
}
#endif

bool LispConnection::launchLisp () {
  GraceApp* app = (GraceApp*)JUCEApplication::getInstance();
  GracePreferences* p=GracePreferences::getInstance();
  Lisp* lisp = p->getLispToLaunch();
  // Do upfront checks to make sure we can start Lisp...
  if ( lisp == (Lisp *)NULL)  {
    console->printError(T(">>> Error: Lisp implementaton has not been set, use Console>Lisp>Configure Lisp... to configure the Lisp session.\n"));
    return false;
  }
  String prog = lisp->getLispProgram();
  if (prog == String::empty) {
    console->printError(T(">>> Error: Lisp executable has not been set. Use Console>Lisp>Configure Lisp... to configure the Lisp session.\n"));
    return false;
  }
  else if (! File(prog).existsAsFile() ) {
    console->printError( T(">>> Error: Lisp executable ") + prog + T(" does not exist.\nUse Console>Lisp>Configure Lisp... to configure the Lisp session.\n") );
    return false;
  }
  // Dont start Lisp if Grace system definition isnt found. look under both
  // AsdfSystemsDirectory and GraceResourceDirectory
  File load;
  File reso = app->getResourceDirectory().getChildFile(T("grace/grace.asd"));    
  File lsys = p->getAsdfSystemsDirectory().getChildFile(T("grace/grace.asd"));

  if ( reso.existsAsFile() ) 
    load=reso;
  else if ( lsys.existsAsFile() )
    load=lsys;
  else {
    String err = T(">>> Error: Grace system definition file cannot be located under the resource directory: ") + reso.getFullPathName();
    if (reso != lsys)
      err += T(" or under the ASDF systems directory: ") + lsys.getFullPathName() + T(".");
    err += T("\nUse Console>Lisp>Configure Lisp... to configure the Lisp session.");
    console->printError(err);
    return false;
  }
#ifndef WINDOWS
  // build --eval expers for starting the grace server. spread over
  // multiple args to avoid package nonsense...
  String args = lisp->getLispProgramArgs(); // start with users' own
  if (args != String::empty) args += T(" ");
  String eval=lisp->getLispEvalArg() + T(" "); // --eval, -x etc
  args += eval;
  args += T("'(load ") + load.getFullPathName().quoted() + T(")'");
  args += T(" ") + eval;
  args += T("'(asdf:oos (quote asdf:load-op) \"grace\")'");
  args += T(" ") + eval;
  args += T("'(grace:start-server ") + String(getPort()) + T(" ") +
    getPollFile(true).getFullPathName().quoted() +
    T(")'");
#else
  // build --eval expers for starting the grace server. spread over
  // multiple args to avoid package nonsense...
  String args = lisp->getLispProgramArgs(); // start with users' own
  if (args != String::empty) args += T(" ");
  String eval=lisp->getLispEvalArg() + T(" "); // --eval, -x etc
  args += eval;
  
  args += T("\"(load ") + String::charToString('\\') + String::charToString('"') + 
    escapeForDOS(load.getFullPathName()) + String::charToString('\\') + T("\")\"");
  args += T(" ") + eval;
  args += T("\"(asdf:oos (quote asdf:load-op)") + String::charToString('\\') + T("\"grace") + String::charToString('\\') + T("\")\"");
  args += T(" ") + eval;
  args += T("\"(grace:start-server ") + String(getPort()) + T(" ") +
    String::charToString('\\') + String::charToString('"') +
    escapeForDOS(getPollFile(true).getFullPathName()) +
    String::charToString('\\') + T("\")\"");
#endif
  console->consoleClear();
  console->printMessage(T("Launching ") + prog + T(" ") + args + T("\n"));
  if (! File(prog).startAsProcess(args) ) {
    console->printError(T(">>> Lisp executable ") + prog + 
      T(" failed to start.\nUse Console>Lisp>Configure Lisp... to configure the Lisp session.\n"));
    return false;
  }
  return true;
}

void LispConnection::timerCallback () {
  if ( pollfile.existsAsFile() && 
       (pollfile.getSize() > 0) && 
       connectToSocket( getHost(), getPort(), 500) ) {
    stopTimer();
  }
  else if (waiting > (getTimeOut()*1000)) {
    console->printError(T(" =:(\n"));
    console->printMessage(T("Connection failed.\n"));
    stopTimer();
    setPort(getPort()+1); // avoid reusing port
  }
  else {
    console->printMessage(T("."));
    waiting += 1000;
  }
}

void LispConnection::startLisp () {
  if (isConnected()) return;
  if (getPort() < 1024) {
    console->printError(T(">>> Lisp connection port ") + 
			       String(getPort()) + T(" is not > 1024.\n"));
    return;
  }
  waiting=0;
  lpid=-1;
  if ( isLocalHost() )
    if (! launchLisp() )
      return;
  console->printMessage(T("Polling socket server"));
  startTimer(1000);
}

void LispConnection::connectionMade () {
  GracePreferences* p=GracePreferences::getInstance();
  //lispinfo=pollfile.loadFileAsString();
  //printf("lispinfo=%s\n", lispinfo.toUTF8());
  deletePollFile();

  console->printValues(T(" =:)\n"));
  String msg=T("Connected to ") + p->getLispToLaunch()->getLispName() + " on ";
  if (!isLocalHost() )
    msg+= getHost() + T(" ");
  console->printMessage(msg + T("port ") + String(getPort()) + T("\n"));
  setLoaded(p->getASDF(ASDF::Grace));
  if ( p->autoLoadCM() )
    loadASDF( p->getASDF(ASDF::CM) );

  setPort(getPort()+1); // avoid reusing port unless
}

void LispConnection::stopLisp () {
  if ( isConnected() ) {
    MemoryBlock mem=MemoryBlock(0, true);  
    sendMessage(mem, msgKillLisp);
    lpid=-1;
    disconnect();
    console->printMessage(T("Lisp disconnected.\n"));
    // clear all loaded systems and files
    clearLoaded();
  }
}

void LispConnection::connectionLost () {
  if (lpid != -1)
    console->printError(T("Lisp: connection unexpectedly lost!\n"));
}

// File loading

bool LispConnection::loadFile(File file) {
  if ( ! isLispRunning () ) return false;
  if ( ! file.existsAsFile() ) {
    console->printError( T(">>> Error: file ") + file.getFullPathName() +
			 T(" does not exist.\n"));
    return false;
  }
#ifdef WINDOWS
  String path=escapeForDOS(file.getFullPathName());
#else
  String path=file.getFullPathName();
#endif
  String sexpr=T("(load ") + path.quoted() + T(")");
  sendLispSexpr(sexpr);
  setLoaded(file);
  GracePreferences* p=GracePreferences::getInstance();
  p->addRecentlyLoadedFile(file);
  return true;
}

void LispConnection::chooseAndLoadFile() {
  GracePreferences* p=GracePreferences::getInstance();
  File dir;
  // directory defaults to directory of most recently loaded file or
  // to Lisp Systems Directory if none.
  if ( p->areRecentlyLoadedFiles() )
    dir=p->getRecentlyLoadedFile(0).getParentDirectory();
  else
    dir=p->getAsdfSystemsDirectory();
  FileChooser choose (T("Load File"), dir, String::empty, true);
  if ( choose.browseForFileToOpen() ) {
    File file = choose.getResult();
    loadFile(file);
  }
}

bool LispConnection::compileFile(File file) {
  if ( ! isLispRunning () ) return false;
  if ( ! file.existsAsFile() ) {
    console->printError( T(">>> Error: file ") + file.getFullPathName() +
			 T(" does not exist.\n"));
    return false;
  }
#ifdef WINDOWS
  String path=escapeForDOS(file.getFullPathName());
#else
  String path=file.getFullPathName();
#endif
  String sexpr=T("(compile-file ") + path.quoted() + T(")");
  sendLispSexpr(sexpr);
  return true;
}

void LispConnection::chooseAndCompileFile() {
  GracePreferences* p=GracePreferences::getInstance();
  File dir;
  // directory defaults to directory of most recently loaded file or
  // to Lisp Systems Directory if none.
  if ( p->areRecentlyLoadedFiles() )
    dir=p->getRecentlyLoadedFile(0).getParentDirectory();
  else
    dir=p->getAsdfSystemsDirectory();
  FileChooser choose (T("Compile File"), dir, String::empty, true);
  if ( choose.browseForFileToOpen() ) {
    File file = choose.getResult();
    compileFile(file);
  }
}

// ASDF loading 

bool LispConnection::loadASDF(ASDF* asdf) {
  if ( ! isLispRunning () ) return false;
  if ( isLoaded(asdf) ) return true;
  GracePreferences* p=GracePreferences::getInstance();
  File file = asdf->getDefinitionFile( p->getAsdfSystemsDirectory() );
  String load = String::empty;
  if ( file.existsAsFile() ) {
#ifdef WINDOWS
  String path=escapeForDOS(file.getFullPathName());
#else
  String path=file.getFullPathName();
#endif
    load=asdf->getLoadForm(path);
  }
  else {
    String bad=asdf->getPathName();
    if (bad==String::empty)
      bad=p->getAsdfSystemsDirectory().getChildFile(T("**")).getChildFile(asdf->getASDFFileName()).getFullPathName();
    console->printError( T(">>> Error: ") + 
			 asdf->getASDFName() +
			 T(" failed to load because the ASDF definition file ") + 
			 bad + T(" does not exist.\n"));
    return false;
  }
  sendLispSexpr(load);
  setLoaded(asdf);
  // if loading CM test for min version compatability
  //  if ( asdf->getASDFName() == T("CM") )
  //    sendLispSexpr(T("(grace::insure-cm-version " + String(cmMinVersion) + ")"));
  return true;
}

void LispConnection::chooseAndLoadASDF() {
  GracePreferences* p=GracePreferences::getInstance();
  FileChooser choose (T("Load System"),
		      p->getAsdfSystemsDirectory(),
		      T("*.asd"),
		      true);
  if ( choose.browseForFileToOpen() ) {
    File file = choose.getResult();
    String name=file.getFileNameWithoutExtension();
    ASDF* asdf=p->findASDF(name);
    if (asdf == (ASDF *)NULL) {
      asdf=new ASDF(name, file.getFullPathName());
      p->addASDF(asdf);
    }
    else
      asdf->setPathName( file.getFullPathName() );
    loadASDF(asdf);
  }
}

//
// Sending and receiving messages
//

void LispConnection::sendLispSexpr(String sexpr, int msg) {
  int len=sexpr.length();
  printf("Send: '%s'\n", sexpr.toUTF8());
  MemoryBlock mem=MemoryBlock(len, true);  
  for (int i=0; i<len; i++)
    mem[i]=(char)sexpr[i];
  sendMessage(mem, (MessageType)msg);
}

void LispConnection::messageReceived (const MemoryBlock &message) {
  printf("in message receive, what is this for?\n");
  int len=message.getSize();
  String text=String((const char *)message, len);
  console->printValues(text);
}

void LispConnection::postMessage (const MemoryBlock &message) {
  int len=message.getSize();
  String text=String((const char *)message, len);
  console->printMessage(text);
}

void LispConnection::postWarning (const MemoryBlock &message) {
  int len=message.getSize();
  String text=String((const char *)message, len);
  console->printWarning(text);
}

void LispConnection::postError (const MemoryBlock &message) {
  int len=message.getSize();
  String text=String((const char *)message, len);
  console->printError(text);
}

void LispConnection::postValues (const MemoryBlock &message) {
  int len=message.getSize();
  String text=String((const char *)message, len);
  printf("Recv: '%s'\n", text.toUTF8());
  console->printValues(text);
}

void LispConnection::handleBinaryData (const MemoryBlock &message) {
   printf("grace got binary data from lisp\n");
}

bool LispConnection::isLoaded(ASDF* a) {
  return loaded.contains(a->getASDFFileName());
}

void LispConnection::setLoaded(ASDF* a) {
  loaded.add(a->getASDFFileName());
}

bool LispConnection::isLoaded(File f) {
  return loaded.contains(f.getFullPathName());
}

void LispConnection::setLoaded(File f) {
  loaded.add(f.getFullPathName());
}

void LispConnection::clearLoaded() {loaded.clear();}

void LispConnection::handleLoadSystem (const MemoryBlock &message) {
  int len=message.getSize();
  String text=String((const char *)message, len);
  GracePreferences* p=GracePreferences::getInstance();
  ASDF* s=p->findASDF(text);
  if (s != (ASDF *)NULL) {
    setLoaded(s);
  }
}

void LispConnection::handleListPackages (const MemoryBlock &message) {
   printf("grace got listPackages data from lisp\n");
}

void LispConnection::handleListFeatures (const MemoryBlock &message) {
   printf("grace got listFeatures data from lisp\n");
}

// ok this would be the point to handle different types of messages 
// coming back from the lisp

void LispConnection::handleMessage (const Message& message) {
  MemoryBlock* const data = (MemoryBlock*) message.pointerParameter;
  //printf ("message id %i\n", message.intParameter1);
  switch( message.intParameter1 ) {
  case (juce::uint32)msgStatus:   //status messages about the connection
    {
      switch  (message.intParameter2) {
      case 1:
	connectionMade();
	break;
      case 2:
	connectionLost();
	break;
      }
    }
    break;
    
  case (juce::uint32)msgPrintout:
    postMessage(*data);
    delete data;
    break;
  case (juce::uint32)msgWarning:
    postWarning(*data);
    delete data;
    break;
  case (juce::uint32)msgError:
    postError(*data);
    delete data;
    break;
  case (juce::uint32)msgErrorDisconnect:
    postError(*data);
    delete data;
    stopLisp();
    break;
  case (juce::uint32)msgValues:
    postValues(*data);
    delete data;
    break;
  case (juce::uint32)msgLoadSystem:
    handleLoadSystem(*data);
    delete data;
    break;
  case (juce::uint32)msgListPackages:
    printf("ListPackages message\n");    
    break;
  case (juce::uint32)msgListFeatures:
    printf("ListPackages message\n");    
    break;
  case (juce::uint32)msgBinaryData:
    handleBinaryData (*data);
    delete data;
    break;
  case (juce::uint32)msgNone:
    printf("Caught msgNone and dont know why...\n");
  default:
    break;
  }
}

//
// Lisp Menu Management
//

const PopupMenu LispConnection::getLispMenu()
{
  GraceApp* app = (GraceApp*)JUCEApplication::getInstance();
  GracePreferences* pref=app->getPreferences();
  bool running=isLispRunning();
  PopupMenu lispmenu, asdfmenu, filemenu;

  if (running)
    lispmenu.addItem(CommandIDs::CommonLispConnect,
		     T("Quit Lisp")); 
  else 
    lispmenu.addItem(CommandIDs::CommonLispConnect,
		     T("Start Lisp"), 
		     isLispStartable()); 
  lispmenu.addSeparator();
  // Load system
  for (int i=0; i<pref->numASDFs(); i++) 
    {
      ASDF* a=pref->getASDF(i);
      asdfmenu.addItem(CommandIDs::CommonLispLoadRecentSystem + i,
		       a->getASDFName(),
		       true,
		       isLoaded(a));
    }
  asdfmenu.addSeparator();
  asdfmenu.addItem(CommandIDs::CommonLispLoadSystem,
		   T("Load..."), 
		   true);
  if (pref->numASDFs() > 2)
    asdfmenu.addItem(CommandIDs::CommonLispClearRecentSystems, 
		     T("Clear"),
		     running);
  lispmenu.addSubMenu(T("ASDF Systems"), asdfmenu, running);
  lispmenu.addItem(CommandIDs::CommonLispLoadFile,
		   T("Load File..."),
		   running);
  if (pref->areRecentlyLoadedFiles())
    {
      pref->addRecentlyLoadedItems(&filemenu,
				   CommandIDs::CommonLispLoadRecentFile);
      filemenu.addSeparator();
      filemenu.addItem(CommandIDs::CommonLispClearRecentLoaded,
		       T("Clear"),
		       running);
      lispmenu.addSubMenu(T("Load Recent"), filemenu, running);
    }
  lispmenu.addItem(CommandIDs::CommonLispCompileFile,
		   T("Compile File..."), 
		   running);
  lispmenu.addSeparator();
  lispmenu.addItem(CommandIDs::CommonLispConfigure,
		   T("Configure Lisp..."),
		   true); 
  return lispmenu;
}

void LispConnection::performLispCommand(CommandID id)
{
  // lower eight bits of id encode command information
  CommandID cmd = CommandIDs::getCommand(id);
  int arg = CommandIDs::getCommandData(id); 
  GraceApp * app = (GraceApp*)JUCEApplication::getInstance();
  GracePreferences* p=app->getPreferences();

  switch (cmd)
    {
    case CommandIDs::CommonLispConnect :
      if (isLispRunning())
        stopLisp();
      else 
        startLisp();
      break;
    case CommandIDs::CommonLispConfigure :
      showConfigureLispWindow();
      break;
    case CommandIDs::CommonLispLoadSystem :
      chooseAndLoadASDF();
      break;
    case CommandIDs::CommonLispLoadRecentSystem :
      loadASDF(p->getASDF(arg));
      break;
    case CommandIDs::CommonLispClearRecentSystems :
      p->clearLispSystems();
      break;
    case CommandIDs::CommonLispLoadFile :
      chooseAndLoadFile();
      break;
    case CommandIDs::CommonLispCompileFile :
      chooseAndCompileFile();
      break;
    case CommandIDs::CommonLispLoadRecentFile :
      loadFile(p->getRecentlyLoadedFile(arg));
      break;
    case CommandIDs::CommonLispClearRecentLoaded :
      p->clearRecentlyLoadedFiles();
      break;
    default:
      break;
    }
}

void LispConnection::showConfigureLispWindow()
{
  DialogWindow::showModalDialog(T("Configure Lisp"),
				new ConfigureLispView(this),
				NULL,
				Colour(0xffe5e5e5),
				true);
}

