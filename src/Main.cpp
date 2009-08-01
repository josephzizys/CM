/*=======================================================================*
  Copyright (c) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify
  it under the terms of the Lisp Lesser Gnu Public License. The text
  of this agreement is available at http://www.cliki.net/LLGPL
 *=======================================================================*/

#include "juce.h"
#include "Enumerations.h"
#include "CmSupport.h"
#include "Console.h"
#include "Scheme.h"
#include "Midi.h"
#include "Main.h"
#include "Audio.h"
#include "CommonLisp.h"
#include "Scanner.h"
#include "Syntax.h"
#ifdef WITHFOMUS
#include "Fomus.h"
#endif

#include <string>
#include <iostream>
 
#ifdef GRACE

/*=======================================================================*
                            GRACE GUI APPLICATION                         
 *=======================================================================*/

#include "Commands.h"
#include "Skin.h"
#include "Preferences.h"

const String Grace::getApplicationName(void)
{
  // asd
  if (SysInfo::isGraceCL())
    return T("GraceCL");
  else
    return T("Grace");
}

const String Grace::getApplicationVersion(void)
{
  return SysInfo::getVersionString(SysInfo::GRACE_VERSION);
}

bool Grace::moreThanOneInstanceAllowed(void)
{
  return SysInfo::isMac();
}

void Grace::anotherInstanceStarted(const juce::String& commandLine)
{
  StringArray droppedfiles;
  // tokenize input with whitespace inside quoted file names preserved
  droppedfiles.addTokens(commandLine, true);
  int size=droppedfiles.size();
  if (size>0)
    {
      // strip explicit quotes from file names
      for (int i=0;i<size;i++)
	droppedfiles.set(i, droppedfiles[i].unquoted());
      if (Console::getInstance()->isInterestedInFileDrag(droppedfiles))
	Console::getInstance()->filesDropped(droppedfiles,0,0);
    }
}

void Grace::initialise(const juce::String& commandLine)
{
  // Load preference file.
  Preferences::getInstance();
  if (SysInfo::isWindows())
    lookandfeel = new WindowsSkin;
  else if (SysInfo::isMac())
    lookandfeel = new MacSkin;
  else if (SysInfo::isLinux())
    lookandfeel = new LinuxSkin;
  LookAndFeel::setDefaultLookAndFeel(lookandfeel);
  // create application command manager
  CommandManager::getInstance()->registerAllCommandsForTarget(this);
  new ConsoleWindow();
  Console* con=Console::getInstance();
  String str=String::empty;
  str << getApplicationName() << T(" ") << SysInfo::getGraceVersion()
      << T(" ") << SysInfo::getCopyright(T("Todd Ingalls, Rick Taube"))
      << T("\n");
  con->printOutput(str);
  // don't initialize anything if we are GraceCL
  if (SysInfo::isGraceCL())
    {
      const String msg=
	T("\nWelcome to GraceCL, a version of Grace that supports the Common Lisp branch (CM2) of Common Music. Your Common Lisp environment is not configured yet. Use Configure Lisp... in the Console Window's file menu to specify the full pathname to your Common Lisp program (SBCL or CLisp) and your Common Music source directory. GraceCL requires version 2.12.0 or later from the CM2 branch, available on the web at http://commonmusic.sf.net or via the svn shell command (all one line):\n\nsvn co http://commonmusic.svn.sf.net/svnroot/commonmusic/branches/cm2 cm2\n\nHappy hacking!\n");
      if (!CommonLisp::getInstance()->isLispStartable())
	Console::getInstance()->printOutput(msg);
      else if (CommonLisp::getInstance()->getLispLaunchAtStartup())
	CommonLisp::getInstance()->startLisp();
      return;
    }
  Scheme* scm=Scheme::getInstance();
  scm->setPriority(10);
  scm->startThread();
  // MidiOut 
  MidiOutPort* mid=MidiOutPort::getInstance();
  mid->setPriority(9);
  mid->startThread();
  // Audio Manager
  AudioManager* aud=AudioManager::getInstance();
  str=aud->initialise(2,2,0,true);
  if (str.isEmpty())
    aud->isAudioReady(true);
  else
    con->printWarning(T("Warning: Audio Manager: ") + str);
  str=Preferences::getInstance()->getStringProp("LispInitFile");
  if (str!=String::empty)
    scm->load(File(str),false);
}

void Grace::systemRequestedQuit()
{
  quit();
}

void Grace::shutdown()
{
  /* Typing COMMAND-Q on mac brings us here but WITHOUT closing any
     windows. */

  std::cout << "Quitting Grace...\n";
  Preferences::getInstance()->getProps().saveIfNeeded();
  delete lookandfeel;
  std::cout << "Deleting Scheme\n";
  Scheme::deleteInstance();
  std::cout << "Deleting CommonLisp\n";
  CommonLisp::deleteInstance();
  std::cout << "Deleting MidiOut\n";
  MidiOutPort::deleteInstance();
  std::cout << "Deleting MidiIn\n";
  MidiInPort::deleteInstance();
#ifdef WITHFOMUS
  std::cout << "Deleting Fomus\n";
  Fomus::deleteInstance();
#endif
  std::cout << "Deleting AudioManager\n";
  AudioManager::deleteInstance();
  std::cout << "Deleting Console\n";
  Console::deleteInstance();
  std::cout << "Deleting CommandManager\n";
  CommandManager::deleteInstance();
  std::cout << "Deleting Preferences\n";
  Preferences::deleteInstance();
  std::cout << "Bye!\n";
  //  std::cout << "Desktop components=" 
  //	    << Desktop::getInstance().getNumComponents() << "\n";
  //  std::cout << "name=" << Desktop::getInstance().getComponent(0)->getName().toUTF8() << "\n";
}

void Grace::showWorkingDirectory() 
{
  Console::getInstance()->
    printOutput(T("Working directory: ") + 
		File::getCurrentWorkingDirectory().
		getFullPathName().quoted() +
		T("\n"));
}

void Grace::chooseWorkingDirectory() 
{
  FileChooser choose (T("Change Directory"),
		      File::getCurrentWorkingDirectory(),
		      String::empty,
		      true);
  if (choose.browseForDirectory())
    {
      choose.getResult().setAsCurrentWorkingDirectory();
      showWorkingDirectory();
    }
}

START_JUCE_APPLICATION(Grace)

#else

/*=======================================================================*
                            CM CONSOLE APPLICATION                       
 *=======================================================================*/

void cm_cleanup()
{
  if (Scheme::getInstance()->isThreadRunning())
    {
//    Console::getInstance()->printOutput(T("Killing Scheme thread...\n"));
      Scheme::getInstance()->stopThread(2000);
    }
  if (MidiOutPort::getInstance()->isThreadRunning())
    {
//    Console::getInstance()->printOutput(T("Killing Midi thread...\n"));
      MidiOutPort::getInstance()->stopThread(2000);
    }
  Scheme::deleteInstance();
  Console::deleteInstance();
  MidiOutPort::deleteInstance();
  MidiInPort::deleteInstance();
  shutdownJuce_NonGUI();
  std::cout << "Bye!\n";
}

int main(int argc, const char* argv[])
{
  initialiseJuce_NonGUI();
  atexit(cm_cleanup);

  // COMMAND ARG PARSING

  StringArray args(argv, argc);  // put command line args into array
  args.remove(0);                // pop program name from list of args
  CommandArgs cmdargs;
  cmdargs.addCommand(T("--version"), T("print version and exit"));
  cmdargs.addCommand(T("--help"), T("print help and exit"));
  cmdargs.addCommand(T("--load"), T("load file"), T("<file>"));
  cmdargs.addCommand(T("--eval"), T("evaluate expression"), T("<expr>"));
  cmdargs.addCommand(T("--batch"), T("process options and exit"));
  cmdargs.addCommand(T("--quiet"), T("don't print startup banner"));
  String err=cmdargs.init(args);
  if (!err.isEmpty())
    {
      std::cout << err.toUTF8() << "\n"
		<< "Usage: cm [options]\noptions:\n"
		<< cmdargs.getHelp().toUTF8() << "\n";
      return 0;
    }
  else if (cmdargs.getCommandArg(T("--version")))
    {
      std::cout << SysInfo::getCMVersion().toUTF8() << "\n";
      return 0;
    }
  else if (cmdargs.getCommandArg(T("--help")))
    {
      std::cout << "Usage: cm [options]\noptions:\n"
		<< cmdargs.getHelp().toUTF8() << "\n";
      return 0;
    }

  // NORMAL STARTUP

  MessageManager::getInstance(); // stops an assert, not sure why
  Console* con=Console::getInstance();
  con->setPrompt(String("\ncm> "));
  //String vers=SystemStats::getJUCEVersion();
  //vers << T(" ") << SysInfo::getCopyright(T("Julian Storer")) << T("\n");
  //con->printOutput(vers);
  Scheme* scm=Scheme::getInstance();
  scm->setQuiet(cmdargs.getCommandArg(T("--quiet")) != NULL);
  scm->setPriority(10);
  scm->startThread();
  MidiOutPort* mid=MidiOutPort::getInstance();
  mid->setPriority(9);
  mid->startThread();

  // COMMAND ARG PROCESSING
  
  bool batch=false;
  for (int i=0; i<cmdargs.size(); i++)
    {
      CommandArg* c=cmdargs.getUnchecked(i);
      if (c->name==T("--load"))
	scm->eval(T("(load ") + c->expr.quoted() + T(")"));
      else if (c->name==T("--eval"))
	scm->eval(c->expr);
      else if (c->name==T("--batch"))
	batch=true;
    }
  
  if (batch)
    scm->eval(T("(quit)"));
  
  // LOOP TIL SCHEME QUITS

  scm->waitForThreadToExit(-1);

  //  while (scm->isThreadRunning())
  //    Thread::sleep(500) ;
  //    sleep(1) ;

  return 0;
}

#endif
