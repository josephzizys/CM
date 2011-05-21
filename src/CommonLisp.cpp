/*=======================================================================*
  Copyright (C) 2007-2009 Todd Ingalls, Rick Taube.
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#include "CommonLisp.h"
#include "Enumerations.h"
#include "Preferences.h"

#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

#if LINUX || MACOSX
  #include <unistd.h>
#endif

juce_ImplementSingleton(CommonLisp)

String CommonLisp::getLispProgram()
{
  return Preferences::getInstance()->getStringProp(T("LispProgram"));
}

void CommonLisp::setLispProgram(String prog)
{
  Preferences::getInstance()->setStringProp(T("LispProgram"), prog);
}

String CommonLisp::getLispProgramArgs()
{
  return Preferences::getInstance()->getStringProp(T("LispProgramArgs"));
}

void CommonLisp::setLispProgramArgs(String args)
{
  Preferences::getInstance()->setStringProp(T("LispProgramArgs"), args);
}

String CommonLisp::getCommonMusicDirectory()
{
  return Preferences::getInstance()->getStringProp(T("CommonMusicDirectory"));
}

void CommonLisp::setCommonMusicDirectory(String dir)
{
  Preferences::getInstance()->setStringProp(T("CommonMusicDirectory"), dir);
}

bool CommonLisp::getLispLaunchAtStartup()
{
  return Preferences::getInstance()->getBoolProp(T("LispLaunchAtStartup"));
}

void CommonLisp::setLispLaunchAtStartup(bool flag)
{
  Preferences::getInstance()->setBoolProp(T("LispLaunchAtStartup"), flag);
}

void CommonLisp::eval(String text, bool issal)
{
  if (!isLispRunning())
    {
      text=T(">>> Error Lisp is not running.\n");
      Console::getInstance()->printError(text);
      return;
    }
  sendLispSexpr(text, ((issal) ? msgSalEval : msgLispEval));
}

void CommonLisp::load(File file, bool addtorecent)
{
  if (file==File::nonexistent)
    {
      FileChooser choose(T("Load"), File::getCurrentWorkingDirectory());
      if (choose.browseForFileToOpen())
	{
	  file=choose.getResult();
	}
      else
	return;
    }
  String text=String::empty;
  String path=file.getFullPathName().quoted();
  if (SysInfo::isWindows())
    path=escapeForDOS(path);
  if (!file.existsAsFile())
    {
      text << T(">>> Error loading ") << path
	   << T(": file does not exist.\n");
      Console::getInstance()->printError(text);
      return;
    }
  text << T("(load ") << path << T(")");
  sendLispSexpr(text);
}

void CommonLisp::compileFile(File file)
{
  if (file==File::nonexistent)
    {
      FileChooser choose(T("Load"), File::getCurrentWorkingDirectory());
      if (choose.browseForFileToOpen())
	{
	  file=choose.getResult();
	}
      else
	return;
    }
  String text=String::empty;
  String path=file.getFullPathName().quoted();
  if (SysInfo::isWindows())
    path=escapeForDOS(path);
  if (!file.existsAsFile())
    text << T(">>> Error compiling ") << path
	 << T(": file does not exist.\n");
  if (!text.isEmpty())
    {
      Console::getInstance()->printError(text);
      return;
    }
  text << T("(compile-file ") << path << T(")");
  sendLispSexpr(text);
}

/*=======================================================================*
                             CLProcessThread
 *=======================================================================*/

CLProcessThread::CLProcessThread (const bool callbacksOnMessageThread)
  : Thread (T("Common Lisp Thread")),
    socket (0),
    pipe (0),
    callbackConnectionState (false),
    useMessageThread (callbacksOnMessageThread)
{
}

CLProcessThread::~CLProcessThread()
{
  disconnect();
}

bool CLProcessThread::connectToSocket (const String& hostName,
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

bool CLProcessThread::connectToPipe (const String& pipeName)
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

bool CLProcessThread::createPipe (const String& pipeName)
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

void CLProcessThread::disconnect()
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

bool CLProcessThread::isConnected() const
{
  const ScopedLock sl (pipeAndSocketLock);
  return ((socket != 0 && socket->isConnected())
	  || (pipe != 0 && pipe->isOpen()))
    && isThreadRunning();
}


bool CLProcessThread::sendMessage (const MemoryBlock& message,
					 MessageType messageType)
{
  juce::uint32 messageHeader[2];
  messageHeader [0] = ByteOrder::swapIfBigEndian ((juce::uint32) messageType);
  messageHeader [1] = ByteOrder::swapIfBigEndian ((juce::uint32) message.getSize());

  MemoryBlock messageData (sizeof (messageHeader) + message.getSize());
  messageData.copyFrom(messageHeader, 0, sizeof (messageHeader));
  messageData.copyFrom(message.getData(), sizeof (messageHeader),
		       message.getSize());
  
  int bytesWritten = 0;
  const ScopedLock sl (pipeAndSocketLock);
  if (socket != 0)
    {
      bytesWritten = socket->write(messageData.getData(), 
				   messageData.getSize());
    }
  else if (pipe != 0)
    {
      bytesWritten = pipe->write (messageData.getData(), 
				  messageData.getSize());
    }
  if (bytesWritten < 0)
    {
      // error..
      return false;
    }
  return (bytesWritten == messageData.getSize());
}

void CLProcessThread::initialiseWithSocket (StreamingSocket* const socket_)
{
  jassert (socket == 0);
  socket = socket_;
  connectionMadeInt();
  startThread();
}

void CLProcessThread::initialiseWithPipe (NamedPipe* const pipe_)
{
  jassert (pipe == 0);
  pipe = pipe_;
  connectionMadeInt();
  startThread();
}

void CLProcessThread::connectionMadeInt()
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

void CLProcessThread::connectionLostInt()
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

void CLProcessThread::deliverDataInt (const MemoryBlock& data,
				      MessageType messageType )
{
  jassert (callbackConnectionState);
  
  if (useMessageThread)
    postMessage (new Message (messageType , 0, 0, new MemoryBlock (data)));
  else
    messageReceived (data);
}

bool CLProcessThread::readNextMessageInt()
{
  const int maximumMessageSize = 1024 * 1024 * 10; // sanity check
  
  juce::uint32 messageHeader[2];
  const int bytes = (socket != 0) 
#if (JUCE_MINOR_VERSION<50)
    ? socket->read (messageHeader, sizeof (messageHeader))
#else
    ? socket->read (messageHeader, sizeof (messageHeader), false)
#endif
    : pipe->read (messageHeader, sizeof (messageHeader));
  
  if (bytes == sizeof (messageHeader) )
    {
      const int bytesInMessage = (int) ByteOrder::swapIfBigEndian (messageHeader[1]);
      
      if (bytesInMessage > 0 && bytesInMessage < maximumMessageSize)
        {
	  MemoryBlock messageData (bytesInMessage, true);
	  int bytesRead = 0;
	  
	  while (bytesRead < bytesInMessage)
            {
	      if (threadShouldExit())
		return false;
	      
	      const int numThisTime = jmin (bytesInMessage, 65536);
	      const int bytesIn = (socket != 0) 
		? socket->read(((char*)messageData.getData())+bytesRead, 
#if (JUCE_MINOR_VERSION<50)
			       numThisTime)
#else
			       numThisTime, false)
#endif
		: pipe->read(((char*) messageData.getData())+bytesRead,
			     numThisTime);
	      
	      if (bytesIn <= 0)
		break;
	      
	      bytesRead += bytesIn;
            }
	  
	  if (bytesRead >= 0)
	    deliverDataInt(messageData,
			   (MessageType)ByteOrder::swapIfBigEndian(messageHeader[0]));
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

void CLProcessThread::run()
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

/*=======================================================================*
                             Common Lisp Connection
 *=======================================================================*/

CommonLisp::CommonLisp () 
   : CLProcessThread(true),
     host (T("localhost")),
     port (8000),
     lpid (-1),
     timeout (30),
     pollfile (File::nonexistent)
{
}

CommonLisp::~CommonLisp ()
{
}

bool CommonLisp::isLispRunning ()
{
  return isConnected();
}  

bool CommonLisp::isLispStartable ()
{
  if (getLispProgram().isEmpty() ||
      getCommonMusicDirectory().isEmpty())
    return false;
  else						
    return true;
}

bool CommonLisp::isLocalHost() 
{
  return (getHost().equalsIgnoreCase(T("localhost")) ||
	  getHost() == T("127.0.0.1"));
}

File CommonLisp::getPollFile(bool newfile)
{
  if (newfile)
    pollfile=File::createTempFile(T("GraceCL"));
  return pollfile;
}

void CommonLisp::deletePollFile() {
  getPollFile().deleteFile();
  pollfile=File::nonexistent;
}

String CommonLisp::escapeForDOS(String path) 
{
  return path.replace(T("\\"),T("\\\\"));
}

bool CommonLisp::launchLisp ()
{
  String prog=getLispProgram();
  String eval=String::empty;
  String text=String::empty;
  String path=getCommonMusicDirectory();
  File asdf=File(path).getChildFile(T("cm.asd"));
  File serv=File(path).getChildFile(T("src/socketserver.lisp"));
  
  if (prog.isEmpty())
    text << T(">>> Error: A Common Lisp program has not been set.\nUse File>Configure Lisp... to specify the full pathname to your SBCL or CLisp executable.");
  else if (! File(prog).existsAsFile() )
    text << T(">>> Error: Lisp program ") << prog
	 << T(" does not exist.\nUse File>Configure Lisp... to specify the full pathname to your SBCL or CLisp executable.\n");
  else if (path.isEmpty())
    text << T(">>> Error: Common Music source directory has not bee set\nUse File>Configure Lisp... to specify the full pathname to your Common Music source directory.");
  else if (!asdf.existsAsFile())
    text << T(">>> Error: Common Music file ") << asdf.getFullPathName() 
	 << T(" cannot be found.\nUse File>Configure Lisp... to specify the full pathname to your Common Music source directory.");
  else if (!serv.existsAsFile()) 
    text << T(">>> Error: Common Music file ") << serv.getFullPathName() 
	 << T(" cannot be found.\n Please install Common Music 2.12.0 or higher\n");
  else if (prog.containsIgnoreCase(T("clisp")))
    eval=T("-x");
  else if (prog.containsIgnoreCase(T("sbcl")))
    eval=T("--eval");
  else
    text << T(">>> Error: Unable to determine Lisp implementation of ") 
	 << prog 
	 << T(".\nUse File>Configure Lisp... to specifiy a Common Lisp executable with either 'clisp' or 'sbcl' in its name.\n");
  if (!text.isEmpty())
    {
      Console::getInstance()->printError(text);
      return false;
    }

  // build program's eval args to start the grace server. spread it
  // over multiple args to avoid cm package nonsense...
  String args = getLispProgramArgs(); // start with users' own
  if (!args.isEmpty()) 
    args << T(" ");

#ifndef WINDOWS
  args << eval << T(" '(load ") 
       << serv.getFullPathName().quoted() << T(")' ")
       << eval << T(" '(cl-user::start-server ") 
       << String(getPort()) << T(" ")
       << getPollFile(true).getFullPathName().quoted() << T(")'");
#else
  args << eval << T(" \"(load ") << String::charToString('\\') 
       << String::charToString('"') 
       << escapeForDOS(serv.getFullPathName()) 
       << String::charToString('\\') << T("\")\" ")
       << eval << T(" \"(cl-user::start-server ") 
       << String(getPort()) << T(" ") 
       << String::charToString('\\') << String::charToString('"') 
       << escapeForDOS(getPollFile(true).getFullPathName()) 
       << String::charToString('\\') << T("\")\"");
#endif

  Console::getInstance()->printOutput(T("Launching ") + prog + T(" ") +
				      args + T("\n"));
  if (!File(prog).startAsProcess(args))
    {
      text << T(">>> Error: Lisp program ")
	   << prog << T("failed to start.\n")
	   << T(" Use File>Configure Lisp... to fix it.\n");
      Console::getInstance()->printError(text);
      return false;
    }
  return true;
}

void CommonLisp::timerCallback () {
  if ( pollfile.existsAsFile() && 
       (pollfile.getSize() > 0) && 
       connectToSocket( getHost(), getPort(), 500) ) {
    stopTimer();
  }
  else if (waiting > (getTimeOut()*1000)) {
    Console::getInstance()->printError(T(" =:(\n"));
    Console::getInstance()->printOutput(T("Connection failed.\n"));
    stopTimer();
    setPort(getPort()+1); // avoid reusing port
  }
  else {
    Console::getInstance()->printOutput(T("."));
    waiting += 1000;
  }
}

void CommonLisp::startLisp ()
{
  std::cout << "starting Lisp !\n";

  if (isConnected())
    return;
  if (getPort() < 1024)
    {
      Console::getInstance()->printError(T(">>> Lisp connection port ") + 
					 String(getPort()) + T(" is not > 1024.\n"));
      return;
    }
  waiting=0;
  lpid=-1;
  if ( isLocalHost() )
    if (! launchLisp() )
      return;
  Console::getInstance()->printOutput(T("Polling socket server"));
  startTimer(1000);
}

void CommonLisp::connectionMade ()
{
  // String info=pollfile.loadFileAsString();
  deletePollFile();
  Console::getInstance()->printValues(T(" =:)\n"));
  String msg=T("Connected to Common Lisp on") ;
  if (!isLocalHost())
    msg <<  T(" ") << getHost();
  msg << T(" port ") << String(getPort()) << T("\n");
  Console::getInstance()->printOutput(msg);

 File asdf=File(getCommonMusicDirectory()).getChildFile(T("cm.asd"));
 String path=asdf.getFullPathName();
 if (SysInfo::isWindows())
   path=escapeForDOS(path);

 // clisp hack: asdf package isn't around until after cm.asd has been
 // loaded so we access asdf symbols dynamically via find-symbol
 String expr=T("(PROGN ");
 expr << T("(LOAD ") << path.quoted() << T(")")
      << T("(FUNCALL (FIND-SYMBOL \"OOS\" :ASDF) ")
      <<          T("(FIND-SYMBOL \"LOAD-OP\" :ASDF) ")
      <<          T(":CM) ")
      << T("(CL-USER::CM)")
      << T(")");
 sendLispSexpr(expr);
 expr=Preferences::getInstance()->getStringProp("LispInitFile");
 if (!expr.isEmpty())
   load(File(expr),false);
 setPort(getPort()+1); // avoid reusing port 
}

void CommonLisp::stopLisp ()
{
  if ( isConnected() )
    {
      MemoryBlock mem=MemoryBlock(0, true);  
      sendMessage(mem, msgKillLisp);
      lpid=-1;
      disconnect();
      Console::getInstance()->printOutput(T("Lisp disconnected.\n"));
    }
}

void CommonLisp::connectionLost ()
{
  if (lpid != -1)
    Console::getInstance()->printError(T("Lisp: connection unexpectedly lost!\n"));
}

//
// Sending and receiving messages
//

void CommonLisp::sendLispSexpr(String sexpr, int msg)
{
  int len=sexpr.length();
  printf("Sending: '%s'\n", sexpr.toUTF8());
  MemoryBlock mem=MemoryBlock(len, true);  
  for (int i=0; i<len; i++)
    mem[i]=(char)sexpr[i];
  sendMessage(mem, (MessageType)msg);
}

void CommonLisp::messageReceived (const MemoryBlock &message)
{
  int len=message.getSize();
  String text=String((const char *)message.getData(), len);
  Console::getInstance()->printValues(text);
}

void CommonLisp::postMessage (const MemoryBlock &message)
{
  int len=message.getSize();
  String text=String((const char *)message.getData(), len);
  Console::getInstance()->printOutput(text);
}

void CommonLisp::postWarning (const MemoryBlock &message)
{
  int len=message.getSize();
  String text=String((const char *)message.getData(), len);
  Console::getInstance()->printWarning(text);
}

void CommonLisp::postError (const MemoryBlock &message)
{
  int len=message.getSize();
  String text=String((const char *)message.getData(), len);
  Console::getInstance()->printError(text);
}

void CommonLisp::postValues (const MemoryBlock &message)
{
  int len=message.getSize();
  String text=String((const char *)message.getData(), len);
  printf("Recv: '%s'\n", text.toUTF8());
  Console::getInstance()->printValues(text);
}

void CommonLisp::handleBinaryData (const MemoryBlock &message)
{
}

void CommonLisp::handleLoadSystem (const MemoryBlock &message)
{
}

void CommonLisp::handleListPackages (const MemoryBlock &message)
{

}

void CommonLisp::handleListFeatures (const MemoryBlock &message)
{
}

// ok this would be the point to handle different types of messages 
// coming back from the lisp

void CommonLisp::handleMessage (const Message& message)
{
  MemoryBlock* const data = (MemoryBlock*) message.pointerParameter;
  //printf ("message id %i\n", message.intParameter1);
  switch( message.intParameter1 )
    {
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


class ConfigureLispView  : public Component,
  public ButtonListener,
  public ComboBoxListener
{
public:
  StringArray lisps;
  CommonLisp* connection;
  ConfigureLispView (CommonLisp* c);
  ~ConfigureLispView();
  void resized();
  void buttonClicked (Button* buttonThatWasClicked);
  void comboBoxChanged (ComboBox* menu);
  void chooseLisp();

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

  Label* proglab;
  Label* argslab;
  FilenameComponent* progbuf;
  Label* argsbuf;

  GroupComponent* sysgroup;
  Label* syslab;
  FilenameComponent* sysbuf;

  ToggleButton* autobutton;
  TextButton* okbutton;
  TextButton* cancelbutton;

};

ConfigureLispView::ConfigureLispView (CommonLisp* c)
  : impgroup (0),
    lisplabel(0),
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
  //  GracePreferences* p=GracePreferences::getInstance();

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
  hostbuffer->setEnabled(false);
  
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

  addAndMakeVisible(autobutton = new ToggleButton (String::empty));
  autobutton->setButtonText (T("Autoconnect at Startup"));

  // Lisp Program Group

  addAndMakeVisible (impgroup = new GroupComponent (String::empty, T("Lisp Program")));
  addAndMakeVisible(proglab = new Label(String::empty,T("Executable:")));
  proglab->setFont (Font (15.0000f, Font::plain));
  proglab->setJustificationType (Justification::centredLeft);
  proglab->setEditable (false, false, false);
  addAndMakeVisible(progbuf = new FilenameComponent(String::empty,
						    File::nonexistent,
						    true,
						    false,
						    false,
						    String::empty,
						    String::empty,
						    T("Select Program")));
  progbuf->setMaxNumberOfRecentFiles(1);
  addAndMakeVisible (argslab = new Label (String::empty, T("Arguments:")));
  argslab->setFont (Font (15.0000f, Font::plain));
  argslab->setJustificationType (Justification::centredLeft);
  
  addAndMakeVisible(argsbuf = new Label(String::empty, String::empty));
  argsbuf->setFont( Font(15.0000f, Font::plain));
  argsbuf->setJustificationType(Justification::centredLeft);
  argsbuf->setColour (Label::outlineColourId, Colours::black);
  argsbuf->setColour (Label::backgroundColourId, Colours::white);
  argsbuf->setEditable(true, true, false);

  // System software
  addAndMakeVisible (sysgroup = new GroupComponent(String::empty,
						   T("Common Music Directory")));
  sysbuf = new FilenameComponent(String::empty, 
				 File(connection->getCommonMusicDirectory()),
				 true, 
				 true,
				 false,
				 String::empty,
				 String::empty,
				 T("Select Directory"));
  addAndMakeVisible(sysbuf);
  sysbuf->setMaxNumberOfRecentFiles(1);

  addAndMakeVisible (okbutton = new TextButton (String::empty));
  okbutton->setButtonText (T("OK"));
  okbutton->addButtonListener (this);

  addAndMakeVisible (cancelbutton = new TextButton (String::empty));
  cancelbutton->setButtonText (T("Cancel"));
  cancelbutton->addButtonListener (this);
  updateFromConnection();
  setSize(408, 348);
}

ConfigureLispView::~ConfigureLispView ()
{
  deleteAndZero (congroup);
  deleteAndZero (hostlabel);
  deleteAndZero (hostbuffer);
  deleteAndZero (portlabel);
  deleteAndZero (portbuffer);
  deleteAndZero (timeslider);
  deleteAndZero (timelabel);
  deleteAndZero (impgroup);
  deleteAndZero (lisplabel);
  deleteAndZero (proglab);
  deleteAndZero (argslab);
  deleteAndZero (progbuf);
  deleteAndZero (argsbuf);
  deleteAndZero (sysgroup);
  deleteAndZero (sysbuf);
  deleteAndZero (autobutton);
  deleteAndZero (okbutton);
  deleteAndZero (cancelbutton);
}

void ConfigureLispView::resized()
{
  congroup->setBounds (8, 8, 392, 96);
  hostlabel->setBounds (24, 32, 40, 24);
  hostbuffer->setBounds (72, 32, 152, 24);
  portlabel->setBounds (240, 32, 40, 24);
  portbuffer->setBounds (288, 32, 96, 24);
  timeslider->setBounds (96, 64, 104, 24);
  timelabel->setBounds (24, 64, 64, 24);
  autobutton->setBounds (220, 64, 170, 24);
 
  impgroup->setBounds (8, 120, 392, 96);
  proglab->setBounds (24, 144, 96, 24);
  progbuf->setBounds (120, 144, 264, 24);
  argslab->setBounds (24, 176, 96, 24);
  argsbuf->setBounds (120, 176, 264, 24);
  
  sysgroup->setBounds(8, 232, 392, 64);
  sysbuf->setBounds(24, 256, 96+264, 24);
  
  okbutton->setBounds (322, 308, 74, 24);
  cancelbutton->setBounds (236, 308, 74, 24);
}

void ConfigureLispView::updateFromConnection () 
{
  hostbuffer->setText(connection->getHost(), true);
  portbuffer->setText(String(connection->getPort()), true);
  timeslider->setValue((double)(connection->getTimeOut()), true);
  autobutton->setToggleState(connection->getLispLaunchAtStartup(), true);

  if ( connection->isLocalHost() )
    hostbuffer->setEditable(false, false);
  else
    hostbuffer->setEditable(true, true);
  String prog=connection->getLispProgram();
  if (prog.isEmpty())
    progbuf->setCurrentFile(File::nonexistent, false);
  else 
    progbuf->setCurrentFile(File(prog), false);
  argsbuf->setText(connection->getLispProgramArgs(), false);
}

bool ConfigureLispView::updateConnection ()
{
  connection->setHost(hostbuffer->getText());
  connection->setPort(portbuffer->getText().getIntValue());
  connection->setTimeOut((int)(timeslider->getValue()));
  connection->setLispLaunchAtStartup(autobutton->getToggleState());
  connection->setLispProgram(progbuf->getCurrentFile().getFullPathName());
  connection->setLispProgramArgs(argsbuf->getText());
  connection->setCommonMusicDirectory(sysbuf->getCurrentFile().getFullPathName());
  return true;
}

void ConfigureLispView::chooseLisp()
{
}

void ConfigureLispView::comboBoxChanged (ComboBox* menu)
{
}

void ConfigureLispView::buttonClicked (Button* buttonThatWasClicked)
{
  DialogWindow* win;
  if (buttonThatWasClicked == okbutton)
    {
      if (! updateConnection() )
	return;
      win=(DialogWindow*)getTopLevelComponent();
      win->getCloseButton()->triggerClick();
    }
  else if (buttonThatWasClicked == cancelbutton)
    {
      win=(DialogWindow*)getTopLevelComponent();
      win->getCloseButton()->triggerClick();
  }
}

void CommonLisp::showConfigureLispWindow ()
{
  DialogWindow::showModalDialog(T("Configure Lisp"),
				new ConfigureLispView(this),
				NULL,
				Colour(0xffe5e5e5),
				true);
}
