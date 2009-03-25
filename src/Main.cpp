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
#include "Fomus.h"

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
}

void Grace::initialise(const juce::String& commandLine)
{
  // Load preference file.
  Preferences::getInstance();
  // Make user's home folder the working directory on startup
  File::getSpecialLocation(File::userHomeDirectory).
    setAsCurrentWorkingDirectory();
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
      << T("\n")
      << SystemStats::getJUCEVersion()
      << T(" ") << SysInfo::getCopyright(T("Julian Storer")) 
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
  std::cout << "Deleting Fomus\n";
  Fomus::deleteInstance();
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

bool isEmpty(std::string& s)
{
  const char* c = s.c_str();
  while (*c)
    {
      switch (*c)
	{
	case ' ' :
	case '\n' :
	case '\t' :
	  break;
	default :
	  return false;
	}
      c++;
    }
  return true;
}

bool isBalanced(std::string& s)
{
  const char* c = s.c_str();
  const char* b = c;
  int par=0, bra=0, squ=0; 
  bool str=false;
  while (*c)
    {
      if (*c == '\"')
	{
	  if ((c==b) || (*(c-1) != '\\'))
	    str=!str;
	}
      if (!str)
	{
	  if (*c == '(')
	    par++;
	  else if (*c == ')')
	    par--;
	  else if (*c == ';')
	    {
	      while (*c && *c != '\n')
		c++;
	    }
	  // The rest of these are SAL
	  else if (*c == '{')
	    bra++;
	  else if (*c == '}')
	    bra--;
	  else if (*c == '[')
	    squ++;
	  else if (*c == ']')
	    squ--;
	}
      c++;
    }
  // allow input with too many closed parens to be passed to lisp
  return ((par<=0) && (bra<=0) && (squ<=0) && (!str));
}

int main(int argc, const char* argv[])
{
  initialiseJuce_NonGUI();

  // this keep assert from happening, not sure why
  MessageManager::getInstance(); 

  StringArray args(argv, argc);  // put command line args into array
  args.remove(0);                // pop program name from list of args

  if (args.contains(String("--version")))
    {
      std::cout << SysInfo::getCMVersion().toUTF8() << "\n";
      return 0;
    }

  Console* con=Console::getInstance();
  con->setPrompt(String("\ncm> "));
  String vers=SystemStats::getJUCEVersion();
  vers << T(" ") << SysInfo::getCopyright(T("Julian Storer")) << T("\n");
  con->printOutput(vers);
  Scheme* scm=Scheme::getInstance();

  scm->setPriority(10);
  scm->startThread();
  MidiOutPort* mid=MidiOutPort::getInstance();
  mid->setPriority(9);
  mid->startThread();
  std::string input="";
  while (scm->isThreadRunning())
    {
      bool more=true;
      while (more) 
	{
	  std::string str="";
	  getline(std::cin, str);
	  if (!input.empty())
	    input.append("\n");
	  input.append(str);
	  more=!isBalanced(input);
	}
      //std::cout << "is balanced...evaling '" << input.c_str() << "' ...\n";
      if (!isEmpty(input))
	{
	  if (input.length() == 1 && input[0]=='q')
	    break;
	  scm->eval(input.c_str());
	}
      input = "";
    }

  if (scm->isThreadRunning())
    {
      con->printOutput(String("Killing Scheme thread...\n"));
      scm->stopThread(2000);
    }
  if (mid->isThreadRunning())
    {
      con->printOutput(String("Killing MidiOut thread...\n"));
      mid->stopThread(2000);
    }
  
  Scheme::deleteInstance();
  Console::deleteInstance();
  MidiOutPort::deleteInstance();
  MidiInPort::deleteInstance();
  shutdownJuce_NonGUI();
  //delete scm;
  std::cout << "Bye!\n";
  return 0;
}

#endif
