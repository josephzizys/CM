/*=======================================================================*
  Copyright (c) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify
  it under the terms of the Lisp Lesser Gnu Public License. The text
  of this agreement is available at http://www.cliki.net/LLGPL
 *=======================================================================*/

#include "Libraries.h"

#include "Enumerations.h"
#include "CmSupport.h"
#include "Console.h"
#include "Scheme.h"
#include "Midi.h"
#include "Main.h"
#include "Audio.h"
#include "Syntax.h"
#include "CodeEditor.h"
#include "Plot.h"
#ifdef WITH_FOMUS
#include "Fomus.h"
#endif
#ifdef WITH_LIBLO
#include "Osc.h"
#endif

#ifdef GRACE

/*=======================================================================*
                            GRACE GUI APPLICATION                         
 *=======================================================================*/

#include "Commands.h"
#include "Skin.h"
#include "Preferences.h"

extern Console* globalConsole;

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
  //  return SysInfo::isMac();
  return false;
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
  if (SysInfo::isWindows())
    lookandfeel = new WindowsSkin;
  else if (SysInfo::isMac())
    lookandfeel = new MacSkin;
  else if (SysInfo::isLinux())
    lookandfeel = new LinuxSkin;
  LookAndFeel::setDefaultLookAndFeel(lookandfeel);
  // Console must exist before any components attempt to write to it!
  Console* con = Console::globalInstance = new Console;
  // Load preference file.
  Preferences::getInstance();
  // create application command manager
  CommandManager::getInstance()->registerAllCommandsForTarget(this);
  // create the console window (console may have output in it already)
  new ConsoleWindow();

  String str=String::empty;
  str << getApplicationName() 
      << T(" ") << SysInfo::getGraceVersion()
      << T(" ") << SysInfo::getCMSvnRevision()
      << T(" ") << SysInfo::getCopyright(T("Rick Taube"))
      << T("\n");
  con->printOutput(str);

#ifdef WITH_FOMUS  
  // Initialize fomus
  initfomus();
#endif  

#ifdef WITH_SDIF
  SdifGenInit("");
#endif

  SchemeThread* scm=SchemeThread::getInstance();
  scm->setPriority(10);
  scm->startThread();
  // MidiOut 
  MidiOutPort* mid=MidiOutPort::getInstance();
  mid->setPriority(9);
  mid->startThread();

  // Audio Manager
  AudioManager* aud=AudioManager::getInstance();
  str=aud->initialise(0,2,0,true);
  if (str.isEmpty())
    aud->configureForUse();
  else
    con->printWarning(T("Warning: Audio Manager: ") + str);
  str=Preferences::getInstance()->getStringProp("LispInitFile");
  if (str!=String::empty)
    scm->load(File(str),false);
  //Console::getInstance()->getTopLevelComponent()->toFront(true);
}

void Grace::systemRequestedQuit()
{
  int flag=-1; 
  int unsaved=getNumUnsavedWindows();
  //  std::cout << "system requested quit!\n";
  if (unsaved>0)
  {
    String m=T("You have ");
    m << String(unsaved) << " document";
    if (unsaved>1) m << T("s");
    m << T(" with unsaved changes. Do you want to review these changes before quitting?");
    flag=AlertWindow::showYesNoCancelBox(AlertWindow::WarningIcon,
                                         T("Quit Grace"),
                                         m,
                                         T("Discard Changes"),
                                         T("Review Changes..."),
                                         T("Cancel")
                                         );
  }
  // flag: -1=quit (no changes), 0=cancel, 1=discard and quit, 2=review changes
  std::cout << "flag=" << flag << "\n";
  if (flag==-1 || flag==1 || (flag==2 && queryUnsavedWindows()))
    quit();
}

int Grace::getNumUnsavedWindows()
{
  int n=0;
  for (int i=0; i<TopLevelWindow::getNumTopLevelWindows(); i++)
  {
    TopLevelWindow* w=TopLevelWindow::getTopLevelWindow(i);
    if (WindowTypes::isWindowType(w, WindowTypes::CodeEditor))
    {
      CodeEditorWindow* e=(CodeEditorWindow*)w;
      if (e->hasUnsavedChanges())
        n++;
    }
    else if (WindowTypes::isWindowType(w, WindowTypes::PlotWindow))
    {
      PlotWindow* p=(PlotWindow*)w;
      if (p->hasUnsavedChanges())
        n++;
    }
  }
  return n;
}

bool Grace::queryUnsavedWindows()
{
  for (int i=0;i<TopLevelWindow::getNumTopLevelWindows();i++)
  {
    TopLevelWindow* w=TopLevelWindow::getTopLevelWindow(i);
    if (!(WindowTypes::isWindowType(w, WindowTypes::CodeEditor) ||
          (WindowTypes::isWindowType(w, WindowTypes::PlotWindow))))
      continue;
    String m = T("Do you want to save the changes you made in the document ");
    m << T("\"") << w->getName() << T("\"?");
    int flag=AlertWindow::showYesNoCancelBox(AlertWindow::QuestionIcon,
                                             String::empty,
                                             m,
                                             T("Don't Save"),
                                             T("Save"),
                                             T("Cancel"));
    if (flag==0) return false;
    if (flag==1) continue; 
    if (WindowTypes::isWindowType(w, WindowTypes::CodeEditor))
    {
      w->toFront(false);
      CodeEditorWindow* c=(CodeEditorWindow*)w;
      c->saveFile(false);
    }
    else if (WindowTypes::isWindowType(w, WindowTypes::PlotWindow))
    {
    }
  }
  return true;
}

void Grace::shutdown()
{
  /* Typing COMMAND-Q on mac brings us here but WITHOUT closing any
     windows. */
  std::cout << "Quitting Grace...\n";
  ConsoleWindow* cw=(ConsoleWindow *)Console::getInstance()->getParentComponent();
  // save current position and size as preference
  Preferences::getInstance()->setStringProp(T("ConsoleState"), cw->getWindowStateAsString()); 	
  for (int i=0; i<Desktop::getInstance().getNumComponents(); i++)
  {
    Component* c=Desktop::getInstance().getComponent(i);
    if (c!=cw) // handle console window later
    {
      c->removeFromDesktop();
    }
  }
  Preferences::getInstance()->getProps().saveIfNeeded();
  std::cout << "Deleting Scheme\n";
  SchemeThread::deleteInstance();
  std::cout << "Deleting MidiOut\n";
  MidiOutPort::deleteInstance();
  std::cout << "Deleting MidiIn\n";
  MidiInPort::deleteInstance();
#ifdef WITH_LIBLO
  OscPort::deleteInstance();
#endif
#ifdef WITH_FOMUS
  std::cout << "Deleting Fomus\n";
  Fomus::deleteInstance();
#endif
#ifdef WITH_SDIF
  std::cout << "Deleting SDIF\n";
  SdifGenKill();
#endif

  std::cout << "Deleting AudioManager\n";
  AudioManager::deleteInstance();
  std::cout << "Deleting Console Window\n";
  // now delete the console window (console instance is automatically
  // deleted by window because its the content componenet)
  delete cw;
  std::cout << "Deleting CommandManager\n";
  CommandManager::deleteInstance();
  std::cout << "Deleting Preferences\n";
  Preferences::deleteInstance();
  delete lookandfeel;
  std::cout << "Bye!\n";
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

/** flush any musical processes currently running, interrupt any lisp
    eval taking place and silence any audio/midi output **/

void Grace::reset()
{
  std::cout << "RESET!\n";
}

START_JUCE_APPLICATION(Grace)

#else

/*=======================================================================*
                            CM CONSOLE APPLICATION                       
 *=======================================================================*/

void cm_cleanup()
{
  if (SchemeThread::getInstance()->isThreadRunning())
    SchemeThread::getInstance()->stopThread(2000);
  if (MidiOutPort::getInstance()->isThreadRunning())
    MidiOutPort::getInstance()->stopThread(2000);
  SchemeThread::deleteInstance();
  delete Console::getInstance();
  MidiOutPort::deleteInstance();
  MidiInPort::deleteInstance();
#ifdef WITH_SDIF
  SdifGenKill();
#endif
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
  Console* con = Console::globalInstance = new Console;
  con->setPrompt(String("\ncm> "));
  //String vers=SystemStats::getJUCEVersion();
  //vers << T(" ") << SysInfo::getCopyright(T("Julian Storer")) << T("\n");
  //con->printOutput(vers);
  SchemeThread* scm=SchemeThread::getInstance();
  scm->setQuiet(cmdargs.getCommandArg(T("--quiet")) != NULL);
  scm->setPriority(10);
  scm->startThread();
  MidiOutPort* mid=MidiOutPort::getInstance();
  mid->setPriority(9);
  mid->startThread();
#ifdef WITH_SDIF
  SdifGenInit("");
#endif

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
