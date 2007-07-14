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
  socket = new Socket();
  
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
  uint32 messageHeader[2];
  messageHeader [0] = swapIfBigEndian ((uint32) messageType);
  messageHeader [1] = swapIfBigEndian ((uint32) message.getSize());

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
void LispProcessConnection::initialiseWithSocket (Socket* const socket_)
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
  
  uint32 messageHeader[2];
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
	  const int ready = socket->isReady (0);
	  
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
    sbclbutton (0),
    openmclbutton (0),
    clispbutton (0),
    //    custombutton (0),
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
  // Lisp Executable
  addAndMakeVisible (impgroup = new GroupComponent (String::empty,
						    T("Lisp Implementation")));
  addAndMakeVisible (sbclbutton = new ToggleButton (String::empty));
  sbclbutton->setButtonText (T("SBCL"));
  sbclbutton->addButtonListener (this);
  sbclbutton->setRadioGroupId(1);
  sbclbutton->setEnabled(c->findLisp(Lisp::SBCL)->isSupportedOS());

  addAndMakeVisible (openmclbutton = new ToggleButton (String::empty));
  openmclbutton->setButtonText (T("OpenMCL"));
  openmclbutton->addButtonListener (this);
  openmclbutton->setRadioGroupId(1);
  openmclbutton->setEnabled(c->findLisp(Lisp::OpenMCL)->isSupportedOS());

  addAndMakeVisible (clispbutton = new ToggleButton (String::empty));
  clispbutton->setButtonText (T("CLisp"));
  clispbutton->addButtonListener (this);
  clispbutton->setRadioGroupId(1);
  clispbutton->setEnabled(c->findLisp(Lisp::CLISP)->isSupportedOS());

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
  progbuf->setEditable(true, true, false);
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
  // System software
  addAndMakeVisible (sysgroup = new GroupComponent (String::empty,
						    T("Lisp Systems Directory")));
  //  addAndMakeVisible (syslab = new Label (String::empty,
  //					 T("Root Directory:")));
  //  syslab->setFont (Font (15.0000f, Font::plain));
  //  syslab->setJustificationType (Justification::centredRight);
  addAndMakeVisible(sysbuf = new Label(String::empty, String::empty));
  sysbuf->setFont(Font (15.0000f, Font::plain));
  sysbuf->setJustificationType(Justification::centredLeft);
  sysbuf->setEditable(true, true, false);
  sysbuf->setColour(Label::outlineColourId, Colours::black);
  sysbuf->setColour(Label::backgroundColourId, Colours::white);
  sysbuf->addListener(this);

  // buttons
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
    deleteAndZero (sbclbutton);
    deleteAndZero (openmclbutton);
    deleteAndZero (clispbutton);
    deleteAndZero (proglab);
    deleteAndZero (argslab);
    deleteAndZero (progbuf);
    deleteAndZero (argsbuf);
    deleteAndZero (sysgroup);
    //    deleteAndZero (syslab);
    deleteAndZero (sysbuf);
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
    sbclbutton->setBounds (16, 136, 90, 24);
    openmclbutton->setBounds (112, 136, 90, 24);
    clispbutton->setBounds (208, 136, 90, 24);
    proglab->setBounds (16, 168, 96, 24);
    progbuf->setBounds (120, 168, 264, 24);
    argslab->setBounds (16, 200, 96, 24);
    argsbuf->setBounds (120, 200, 264, 24);

    sysgroup->setBounds (8, argslab->getY()+56, 392, 64);
    //    syslab->setBounds (16, sysgroup->getY()+24, 96, 24);
    //    sysbuf->setBounds (120, syslab->getY(), 264, 24);
    sysbuf->setBounds (24, sysgroup->getY()+24, 96+264, 24);

    okbutton->setBounds (336, sysbuf->getY()+60, 60, 24);
    cancelbutton->setBounds (264, sysbuf->getY()+60, 60, 24);
}

void ConfigureLispView::updateFromConnection () {
  hostbuffer->setText(connection->getHost(), true);
  portbuffer->setText(String(connection->getPort()), true);
  timeslider->setValue((double)(connection->getTimeOut()), true);
  if ( connection->isLocalHost() )
    hostbuffer->setEditable(false, false);
  else
    hostbuffer->setEditable(true, true);

  Lisp* l=connection->getLisp();
  if (l != (Lisp *)NULL) {
    if (l->isLispImplementation(Lisp::SBCL) )
      sbclbutton->setToggleState(true,true);
    else if (l->isLispImplementation(Lisp::OpenMCL)  )
      openmclbutton->setToggleState(true,true);
    else if (l->isLispImplementation(Lisp::CLISP) )
      clispbutton->setToggleState(true,true);
  }
  else
    chooseLisp( (Lisp *)NULL);
  sysbuf->setText(connection->getLispSystemsDirectory().getFullPathName(), true);
}

bool ConfigureLispView::updateConnection () {
  String s1, s2, s3, s4;
  int i1, i2, i3=-1;
  uint32 u1;
  s1=hostbuffer->getText();
  i1=portbuffer->getText().getIntValue();
  i2=(int)(timeslider->getValue());

  if (sbclbutton->getToggleState()) 
    connection->setLisp(connection->findLisp(Lisp::SBCL));
  else if (openmclbutton->getToggleState())
    connection->setLisp(connection->findLisp(Lisp::OpenMCL));
  else if (clispbutton->getToggleState())
    connection->setLisp(connection->findLisp(Lisp::CLISP));

  s2=progbuf->getText();
  s3=argsbuf->getText();
  s4=sysbuf->getText();

  connection->setHost(s1);
  connection->setPort(i1);
  connection->setTimeOut(i2);
  Lisp* l=connection->getLisp();
  if (l != (Lisp *)NULL) {
    l->setLispProgram(s2);
    l->setLispProgramArgs(s3);
  }
  connection->setLispSystemsDirectory(File(s4));
  return true;
}

void ConfigureLispView::chooseLisp(Lisp* lisp) {
  // set Executable and Arguments buffers from selected lisp
  if (lisp != (Lisp *)NULL) {
    progbuf->setText(lisp->getLispProgram(), true); 
    argsbuf->setText(lisp->getLispProgramArgs(), true);
  }
  else {
    progbuf->setText(String::empty, true);
    argsbuf->setText(String::empty, true);
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
  if (buttonThatWasClicked == sbclbutton) 
    chooseLisp(connection->findLisp(Lisp::SBCL));
  else if (buttonThatWasClicked == openmclbutton)
      chooseLisp(connection->findLisp(Lisp::OpenMCL));    
  else if (buttonThatWasClicked == clispbutton)
    chooseLisp(connection->findLisp(Lisp::CLISP));
}

void ConfigureLispView::labelTextChanged (Label* labelThatHasChanged) {
  if (labelThatHasChanged == portbuffer) {
    // show red background if port number is invalid
    int i1=portbuffer->getText().getIntValue();
    if (i1<1024)
      portbuffer->setColour (Label::backgroundColourId, Colours::lightpink);
    else
      portbuffer->setColour (Label::backgroundColourId, Colours::white);
  }
  else if (labelThatHasChanged == progbuf) {
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
  else if (labelThatHasChanged == sysbuf) {
    // show red background if lisp systems dir doesnt exist.
    String path=sysbuf->getText();

    /*    LispSystem* cm= new LispSystem(T("CM"));
    String asdf=cm->findSystemFile(path);
    printf("cmpath=%s\n", asdf.toUTF8());
    */

    if ( path == String::empty || File(path).isDirectory() )
      sysbuf->setColour(Label::backgroundColourId, Colours::white);
    else
      sysbuf->setColour(Label::backgroundColourId, Colours::lightpink);
  }
}

void ConfigureLispView::sliderValueChanged (Slider* sliderThatWasMoved) {
    if (sliderThatWasMoved == timeslider) {
    }
}

//=========================================================================
//=========================================================================

///
/// Lisp System (ASDF) support
///

String ASDF::findASDFFile(File root) {
  if ( root.isDirectory() ) {
    String file=getASDFFileName();
    if ( root.getChildFile(file).existsAsFile() )
      return root.getChildFile(file).getFullPathName();
    else {
      // search for subdir whose name starts with the ASDF's name, if
      // it exists then look inside for the .asd file.
      OwnedArray<File> dirs;
      OwnedArray<File> asds;
      int d=root.findChildFiles(dirs, File::findDirectories, false,
				( getASDFName(true) + T("*")));
      for (int i=0; i<d; i++) {
	int b=dirs[i]->findChildFiles(asds, File::findFiles, false, file);
	if (b==1)
	  return asds[0]->getFullPathName();
	asds.clear();
      }
    }
  }
  return String::empty;
}

String ASDF::getLoadForm(String path) {
  String form=T("(progn ");
  if (before != String::empty)
    form += before + T(" ");
  form += T("(load ") + path.quoted() + T(") (asdf:oos (quote ") + 
    oper + T(") ") + getASDFName(true).quoted() + T(")");
  if (after != String::empty)
    form += T(" ") + after;
  form += T("(values))");
  return form;
}

LispConnection::LispConnection (ConsoleWindow* w) 
   : LispProcessConnection(true),
     host (T("localhost")),
     port (8000),
     lpid (-1),
     impl ((Lisp *)NULL),
     timeout (20),
     pollfile (File::nonexistent),
     lispsysdir (File::nonexistent)     
{
  console=w;
  int allos=(SystemStats::Windows | SystemStats::MacOSX | 
	     SystemStats::Linux );
  int nowin=(SystemStats::MacOSX | SystemStats::Linux ); 

  addLisp(new Lisp( (Lisp::CLTL | Lisp::SBCL), T("SBCL"),
		    T("http://sbcl.sourceforge.net/"),
		    T("sbcl"), T("--eval"), nowin));
  addLisp(new Lisp( (Lisp::CLTL | Lisp::OpenMCL), T("OpenMCL"),
		    T("http://openmcl.closure.com/"),
		    T("openmcl"), T("--eval"), nowin));
  addLisp(new Lisp( (Lisp::CLTL | Lisp::CLISP), T("CLISP"),
		    T("http://clisp.cons.org/"),
		    T("clisp"), T("-x"), allos));

  // initialize the Lisp systems directory to the apps resource dir.
  lispsysdir=getGraceResourceDirectory();

  String path=String::empty;
  addASDF(new ASDF( T("Grace"), path, allos, allos, allos));
  addASDF(new ASDF( T("CM"), path, allos, allos, allos,
		    T("asdf:load-op"), String::empty, 
		    T("(cl-user::cm)")));
  addASDF(new ASDF( T("CFFI"), path, allos, allos, allos));
  addASDF(new ASDF( T("FOMUS"), path, allos, allos, allos));
  addASDF(new ASDF( T("Portmidi"), path, nowin, nowin, nowin));
  addASDF(new ASDF( T("CLM"), path, nowin, nowin, 0,
		    T("asdf:load-source-op")));
  addASDF(new ASDF( T("CMN"), path, allos, allos, allos,
		    T("asdf:load-source-op")));
  addASDF(new ASDF( T("RTS"), path, SystemStats::Linux,
		    SystemStats::MacOSX, 0));
}

LispConnection::~LispConnection () {
 }

bool LispConnection::isLispRunning () {
  isConnected();
}  

bool LispConnection::isLispStartable () {
  return ( ! isLocalHost() || (getLisp() != (Lisp *)NULL));
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

bool LispConnection::launchLisp () {
  Lisp* lisp = getLisp();
  // Do upfront checks to make sure we can start Lisp...
  if (lisp == (Lisp *)NULL) {
    console->consolePrintError(T(">>> Lisp failed to start, use Console>Lisp>Configure Lisp... to configure the Lisp session.\n"));
    return false;
  }
  String prog = lisp->getLispProgram();
  if (prog == String::empty) {
    console->consolePrintError(T(">>> Lisp program has not been set. Use Console>Lisp>Configure Lisp... to configure the Lisp session.\n"));
    return false;
  }
  if (! File(prog).existsAsFile() ) {
    String msg=T(">>> Lisp program ") + prog + 
      T(" does not exist.\nUse Console>Lisp>Configure Lisp... to configure the Lisp session.\n");
    console->consolePrintError(msg);
    return false;
  }
  // Dont start if Grace system definition isnt found. look under both
  // LispSystemsDirectory and GraceResourceDirectory
  File load;
  File lsys = getLispSystemsDirectory().getChildFile(T("grace/grace.asd"));
  if (lsys.existsAsFile() )
    load=lsys;
  else {
    File reso = getGraceResourceDirectory().getChildFile(T("grace/grace.asd"));    
    if ( reso.existsAsFile() ) 
      load=reso;
    else {
      String err = T(">>> System file grace.asd cannot be found under the Lisp systems directory ") +
	lsys.getFullPathName();
      if (reso != lsys)
	err += T(" or under the Grace resource directory ") + reso.getFullPathName() + T(".");
      err += T("\nUse Console>Lisp>Configure Lisp... to configure the Lisp session.");
      console->consolePrintError(err);
      return false;
    }
  }
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

  console->consoleClear();
  console->consolePrint(T("Launching ") + prog + T(" ") + args + T("\n"));

  if (! File(prog).startAsProcess(args) ) {
    console->consolePrintError(T(">>> Lisp program ") + prog + 
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
    console->consolePrintError(T(" =:(\n"));
    console->consolePrint(T("Connection failed.\n"));
    stopTimer();
  }
  else {
    console->consolePrint(T("."));
    waiting += 1000;
  }
}

void LispConnection::startLisp () {
  if (isConnected()) return;
  if (getPort() < 1024) {
    console->consolePrintError(T(">>> Lisp connection port ") + 
			       String(getPort()) + T(" is not > 1024.\n"));
    return;
  }
  waiting=0;
  lpid=-1;
  if ( isLocalHost() )
    if (! launchLisp() )
      return;
  console->consolePrint(T("Polling socket server"));
  startTimer(1000);
}

void LispConnection::connectionMade () {
  lispinfo=pollfile.loadFileAsString();
  printf("lispinfo=%s\n", lispinfo.toUTF8());
  deletePollFile();

  console->consolePrintValues(T(" =:)\n"));
  String msg=T("Connected to ") + getLisp()->getLispName() + " on ";
  if (!isLocalHost() )
    msg+= getHost() + T(" ");
  console->consolePrint(msg + T("port ") + String(getPort()) + T("\n"));
  getASDF(ASDF::Grace)->setLoaded(true);
  loadASDF( getASDF(ASDF::CM) );
}

void LispConnection::stopLisp () {
  if ( isConnected() ) {
    MemoryBlock mem=MemoryBlock(0, true);  
    sendMessage(mem, msgKillLisp);
    lpid=-1;
    disconnect();
    console->consolePrint(T("Lisp disconnected.\n"));
    // mark all system unloaded.
    for (int i=0;i<numASDFs();i++)
      getASDF(i)->setLoaded(false);
  }
}

void LispConnection::connectionLost () {
  if (lpid != -1)
    console->consolePrintError(T("Lisp: connection unexpectedly lost!\n"));
}

// ASDF loading

bool LispConnection::loadASDF(ASDF* asdf) {
  if ( ! isLispRunning () ) return false;
  if ( asdf->isLoaded() ) return true;
  File file = asdf->getDefinitionFile( getLispSystemsDirectory() );
  String load = String::empty;
  if ( file.existsAsFile() ) {
    load=asdf->getLoadForm(file.getFullPathName());
  }
  else {
    String bad=asdf->getPathName();
    if (bad==String::empty)
      bad=getLispSystemsDirectory().getChildFile(T("**")).getChildFile(asdf->getASDFFileName()).getFullPathName();
    console->consolePrintError( T(">>> System ") + asdf->getASDFName() + 
				T(" not found:\n") + bad + 
				T(" does not exist.\n"));
    return false;
  }
  sendLispSexpr(load);
  return true;
}

bool LispConnection::chooseASDF() {
  FileChooser choose (T("Load System"), getLispSystemsDirectory(),
		      T("*.asd"),
		      true);
  if ( choose.browseForFileToOpen() ) {
    File file = choose.getResult();
    String name=file.getFileNameWithoutExtension();
    ASDF* asdf=findASDF(name);
    if (asdf == (ASDF *)NULL) {
      asdf=new ASDF(name, file.getFullPathName(), Lisp::OsAll,
		    Lisp::OsAll, Lisp::OsAll);
      addASDF(asdf);
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
  if (! isConnected() ){
    console->consolePrintError(T("Lisp: not connected.\n"));
    return;
  }
  int len=sexpr.length();
  printf("Grace sending: '%s'\n", sexpr.toUTF8());
  MemoryBlock mem=MemoryBlock(len, true);  
  for (int i=0; i<len; i++)
    mem[i]=(char)sexpr[i];
  sendMessage(mem, (MessageType)msg);
}

void LispConnection::messageReceived (const MemoryBlock &message) {
  printf("in message receive, what is this for?\n");
  int len=message.getSize();
  String text=String((const char *)message, len);
  console->consolePrint(text,ConsoleTheme::valueColor);
  console->consoleTerpri();
}

void LispConnection::postMessage (const MemoryBlock &message) {
  int len=message.getSize();
  String text=String((const char *)message, len);
  console->consolePrint(text, ConsoleTheme::outputColor);
  console->consoleTerpri();
}

void LispConnection::postWarning (const MemoryBlock &message) {
   printf("post warning\n");
  int len=message.getSize();
  String text=String((const char *)message, len);
  console->consolePrintWarning(text);
  console->consoleTerpri();
}

void LispConnection::postError (const MemoryBlock &message) {
  printf("post error\n");
  int len=message.getSize();
  String text=String((const char *)message, len);
  console->consolePrintError(text);
  console->consoleTerpri();
}

void LispConnection::postValues (const MemoryBlock &message) {
  int len=message.getSize();
  String text=String((const char *)message, len);
  console->consolePrint(text, ConsoleTheme::valueColor);
  console->consoleTerpri();
}

void LispConnection::handleBinaryData (const MemoryBlock &message) {
   printf("grace got binary data from lisp\n");
}

void LispConnection::handleLoadSystem (const MemoryBlock &message) {
  int len=message.getSize();
  printf("received LoadSystem message system, len=%d", len);
  String text=String((const char *)message, len);
  printf(" text=%s\n", text.toUTF8());
  ASDF* s=findASDF(text);
  if (s != (ASDF *)NULL)
    s->setLoaded(true);
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
  printf ("message id %i\n", message.intParameter1);
  switch( message.intParameter1 ) {
  case (uint32)msgStatus:   //status messages about the connection
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
    
  case (uint32)msgPrintout:
    postMessage(*data);
    delete data;
    break;
  case (uint32)msgWarning:
    postWarning(*data);
    delete data;
    break;
  case (uint32)msgError:
    postError(*data);
    delete data;
    break;
  case (uint32)msgValues:
    postValues(*data);
    delete data;
    break;
  case (uint32)msgLoadSystem:
    handleLoadSystem(*data);
    delete data;
    break;
  case (uint32)msgListPackages:
    printf("ListPackages message\n");    
    break;
  case (uint32)msgListFeatures:
    printf("ListPackages message\n");    
    break;
  case (uint32)msgBinaryData:
    handleBinaryData (*data);
    delete data;
    break;
  case (uint32)msgNone:
    printf("Caught msgNone and dont know why...\n");
  default:
    break;
  }
}
