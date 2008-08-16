/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$

#include "Editor.h"
#include "Console.h"
#include "Plotter.h"
#include "Grace.h"
#include "Enumerations.h"
#include <iostream>

// NEVER touch these, use initialize() and shutdown() methods!
GraceApp::GraceApp () : console (0) {}
GraceApp::~GraceApp () {}

void GraceApp::initialise (const String& commandLine) {
  File home = File::getSpecialLocation(File::userHomeDirectory);
  home.setAsCurrentWorkingDirectory();
  // Cache the absolute path to the resource directory. This is
  // normally determined relative to the Grace executable at run time and can be overridden by the --resource-directory command arg.
#ifdef RESOURCEDIR
  resourceDirectory = File(String(RESOURCEDIR));
#elif MACOSX
  resourceDirectory = File(File::getSpecialLocation(File::currentExecutableFile).getParentDirectory().getParentDirectory().getChildFile(T("Resources")).getFullPathName());
#elif LINUX
  resourceDirectory = File(File::getSpecialLocation(File::currentExecutableFile).getParentDirectory().getParentDirectory().getChildFile((T("lib/") + getApplicationName())).getFullPathName());
#elif WINDOWS
  resourceDirectory = File(File::getSpecialLocation(File::currentExecutableFile).getSiblingFile(T("Resources")).getFullPathName());
#endif

  //  // add resource directory to library path for loading libchicken
  //#if (defined(MACOSX) && defined(SCHEME))
  //  setenv("DYLD_LIBRARY_PATH=", resourceDirectory.getFullPathName().toUTF8(), 1);
  //  //  printf("DYLD_LIBRARY_PATH=%s\n",resourceDirectory.getFullPathName().toUTF8(), 1);
  //#endif

  File pref=PropertiesFile::getDefaultAppSettingsFile(getApplicationName(), T("prefs"), String::empty, false);
  if ( pref.existsAsFile() ) {
    Time releasedate (2008, 0, 8, 9, 20) ;
    if (pref.getLastModificationTime() < releasedate ) {
      pref.deleteFile();
    }
  }

  // create and initialize preferences
  prefs=GracePreferences::getInstance();
  prefs->initPreferences(commandLine) ;

  String graceinfo;
  graceinfo << T("\n-----------------------------------------------------------\n")
	    << getApplicationName() << T(" ") << getApplicationVersion()
	    << T("\nExecutable file: ")
	    << File::getSpecialLocation(File::currentExecutableFile).getFullPathName()
	    << T("\nResource directory: ")
 	    << getResourceDirectoryPathName()
	    << T("\nApplication file: ")
	    << File::getSpecialLocation(File::currentApplicationFile).getFullPathName()
	    << T("\nPreferences file: ")
	    << prefs->getProperties()->getFile().getFullPathName()
	    << T("\nHome directory: ")
	    << File::getSpecialLocation(File::userHomeDirectory).getFullPathName()
	    << T("\nCurrent working directory: ")
	    << File::getCurrentWorkingDirectory().getFullPathName()
	    << T("\nUser documents directory: ")
	    << File::getSpecialLocation(File::userDocumentsDirectory).getFullPathName()
	    << T("\nUser application data directory: ")
	    << File::getSpecialLocation(File::userApplicationDataDirectory).getFullPathName()
	    << T("\nCommon application data directory: ")
	    << File::getSpecialLocation(File::commonApplicationDataDirectory).getFullPathName()
	    << T("\nTemp directory: ")
	    << File::getSpecialLocation(File::tempDirectory).getFullPathName()
	    << T("\n");
  printf("%s", graceinfo.toUTF8());
  prefs->print();
  printf("-----------------------------------------------------------\n");

  initHelp();  // create global Help entires

  LookAndFeel::setDefaultLookAndFeel(&shinyLookAndFeel);
  commandManager = new ApplicationCommandManager();
  audioManager.initialise(1,2,0,true);
  console = new ConsoleWindow(true);
#ifdef SCHEME
  schemeProcess =  new SchemeThread("Scheduler", console);
  schemeProcess->setPriority(10);
  schemeProcess->startThread();
  midiOutPort = new MidiOutPort(console);
  midiOutPort->open(0);
  midiOutPort->setPriority(9);
  midiOutPort->startThread();
  midiInPort = new MidiInPort(console);
  csoundPort = new CsoundPort(console);
  fomusPort = new FomusPort(console);
#endif

}

void GraceApp::graceQuit (bool ask)
{
  bool doit=false;
  if (ask)
    {
      // NOTE: Juce positions the OK button on the left side of the
      // dialog, opposite to what Mac dialogs do. Ive reversed buttons
      // (and the logic) so that Quit appears on the right side.
      if (!AlertWindow::showOkCancelBox
	  (AlertWindow::QuestionIcon, T("Quit"),
	   T("Really quit Grace? Any unsaved work will be lost."),
	   //T("   OK   "), T("Cancel")
	   T("Cancel"), T("  Quit   ")
	   )
	  )
	doit=true;
    }
  else
    doit=false;
  if (doit)
    {
      JUCEApplication::quit();
    }
}

void GraceApp::shutdown () {
#ifdef SCHEME
  if ( schemeProcess->isThreadRunning() ) {
    schemeProcess->stop();
    schemeProcess->stopThread(2000);
  }
  delete schemeProcess;

  if ( midiOutPort->isThreadRunning() ) {
    midiOutPort->clear();
    midiOutPort->stopThread(2000);
  }
  delete midiOutPort;

  if ( midiInPort->isActive() )
    midiInPort->stop();
  delete midiInPort;

  if ( csoundPort->isOpen() )
    csoundPort->close(true);
  if ( csoundPort->isWriting() )
    csoundPort->close(false);

  delete csoundPort;

#endif
  delete console;
  delete prefs;
  delete commandManager;
  helpdocs.clear();
}

const String GraceApp::getApplicationName () {
#ifndef SCHEME
  return T("GraceCL");
#else
  return T("Grace");
#endif
}

const String GraceApp::getApplicationVersion () {
  String ver=String::empty;
#ifdef RELEASE
  int n=RELEASE, a=0, b=0;
  if (n>0) {
    a=n/100;
    n=n % 100;
    b=n/10;
    n=n % 10;
    ver=String(a) + T(".") + String(b) + T(".") + String(n);
  }
#endif
#ifdef REVISION
  if (ver != String::empty)
    ver << T(" ");
  ver << T("(rev ") << String(REVISION) << T(")");
#endif
  return ver;
}

bool GraceApp::moreThanOneInstanceAllowed () {
  // JUCE LINUX BUG: if this is false then Grace will not launch on
  // Fedora Core Linux unless you are su'ed to ROOT.
#ifdef LINUX
  return true;
#else
  return false;
#endif
}

void GraceApp::anotherInstanceStarted (const String& commandLine) {
}

///
/// App-wide menus common to most windows
///

const PopupMenu GraceApp::getWindowMenu()
{
  PopupMenu windowmenu;
  for (int i=0; i<TopLevelWindow::getNumTopLevelWindows(); i++)
    {
      TopLevelWindow* w = TopLevelWindow::getTopLevelWindow(i);
      windowmenu.addItem(CommandIDs::WindowSelect+i, w->getName() );
    }
  return windowmenu;
}

void GraceApp::performWindowCommand(CommandID id)
{
  CommandID cmd = CommandIDs::getCommand(id);
  int arg = CommandIDs::getCommandData(id);  
  TopLevelWindow* win=TopLevelWindow::getTopLevelWindow(arg);
    if (win != NULL) 
      {
	win->grabKeyboardFocus();
	win->toFront(true);
      }
}

const PopupMenu GraceApp::getHelpMenu()
{
  PopupMenu helpmenu, tutorialsmenu, examplesmenu;
  int i=0;
  while (i<helpdocs.size())
    {
      HelpDoc* h=helpdocs.getUnchecked(i);
      if (! CommandIDs::isCommand(h->type, CommandIDs::HelpTopic))
	break;
      helpmenu.addItem(h->type, h->name);
      i++;
    }
  helpmenu.addSeparator();
  while (i<helpdocs.size())
    {
      HelpDoc* h=helpdocs.getUnchecked(i);
      if (! CommandIDs::isCommand(h->type, CommandIDs::HelpTutorial))
	break;
      tutorialsmenu.addItem(h->type, h->name);
      i++;
    }
  helpmenu.addSubMenu("Tutorials", tutorialsmenu);
  while (i<helpdocs.size())
    {
      HelpDoc* h=helpdocs.getUnchecked(i);
      if (! CommandIDs::isCommand(h->type, CommandIDs::HelpExample))
	break;
      examplesmenu.addItem(h->type, h->name);
      i++;
    }
  helpmenu.addSubMenu("Examples", examplesmenu);
  helpmenu.addSeparator();
  while (i<helpdocs.size())
    {
      HelpDoc* h=helpdocs.getUnchecked(i);
      if ( ! CommandIDs::isCommand(h->type, CommandIDs::HelpWebSite))
	break;
      helpmenu.addItem(h->type, h->name);
      i++;
    }
  return helpmenu;
}

void GraceApp::performHelpCommand(CommandID id)
{
  CommandID cmd = CommandIDs::getCommand(id);
  int arg = CommandIDs::getCommandData(id);  
  HelpDoc* help=NULL;
  // find the help entry that matches ID
  for (int i=0; i<helpdocs.size(); i++)
    if (helpdocs.getUnchecked(i)->type == id)
      {
	help=helpdocs.getUnchecked(i);
	break;
      }
  if (help==NULL)
    return;
  File file=File::nonexistent;
  URL url;
  bool browser=false; // if true use browser for display else Editor
  bool local=false;   // if true help is local resource file;

  // help topics are HTML files in resources/doc
  if (cmd==CommandIDs::HelpTopic)
    {
      file=getResourceDirectory().
	getChildFile("doc/").getChildFile(help->path);
      browser=true;
      local=true;
    }
  // tutorials are editable text files in resources/tutorials
  if (cmd==CommandIDs::HelpTutorial)
    {
      file=getResourceDirectory().
	getChildFile("doc/tutorials/").getChildFile(help->path);
      browser=false;
      local=true;
    }
  // tutorials are editable text files in resources/tutorials
  if (cmd==CommandIDs::HelpExample)
    {
      file=getResourceDirectory().
	getChildFile("doc/examples/").getChildFile(help->path);
      browser=false;
      local=true;
    }

  // WebSites are remote urls.
  if (cmd==CommandIDs::HelpWebSite)
    {
      browser=true;
      local=false;
      url=URL(help->path);
    }

  if (local)
    if (file.existsAsFile())  // file must exist if local
      { 
	if (browser)
#ifndef LINUX	  
	    URL(file.getFullPathName()).launchInDefaultBrowser();
#else
	{ // LINUX nonsense: launchInDefaultBrowser on Linux does not
	  // for local files so I have to hardwire a browser. At some
	  // point this could be a Preference setting...
	  String u=T("file://") + file.getFullPathName();
	  File foxy=File(T("/usr/bin/firefox"));
	  if ( foxy.existsAsFile() ) {
	    foxy.startAsProcess(u.quoted());
	  }
	  else
	    err=T(">>> Can't open ") + u + T(" on Linux because") +
	      foxy.getFullPathName() + T(" does not exist.");
	}
#endif	
	else
	  {
	    new EditorWindow(0, (EditFlags::Load | EditFlags::NoSave),
			     file.getFullPathName());
	  }
      }
      else
	{
	  String err;
	  err << T(">>> File ") <<
	    file.getFullPathName() << T(" does not exist.\n");
	  getConsole()->printError(err);
	}
  else
    {
      url.launchInDefaultBrowser();
    }
}

void GraceApp::initHelp()
{
  // Topics
  helpdocs.add(new HelpDoc(CommandIDs::HelpTopic+0, 
			   T("Console"),
			   T("console.html")));
  helpdocs.add(new HelpDoc(CommandIDs::HelpTopic+1,
			   T("Editor"),
			   T("editor.html")));
  helpdocs.add(new HelpDoc(CommandIDs::HelpTopic+2,
			   T("Ports"),
			   T("ports.html")));
  helpdocs.add(new HelpDoc(CommandIDs::HelpTopic+3, 
			   T("Plotter"),
			   T("plotter.html")));
  helpdocs.add(new HelpDoc(CommandIDs::HelpTopic+4,
			   T("Common Music"),
			   T("cm.html")));
  // Tutorials
  helpdocs.add(new HelpDoc(CommandIDs::HelpTutorial+0, 
			   T("Hello World"), 
			   T("hello.sal")));
  helpdocs.add(new HelpDoc(CommandIDs::HelpTutorial+1, 
			   T("Expressions"),
			   T("sexpr.sal")));
  helpdocs.add(new HelpDoc(CommandIDs::HelpTutorial+2,
			   T("Function Calls"),
			   T("funcall.sal")));
  helpdocs.add(new HelpDoc(CommandIDs::HelpTutorial+3,
			   T("Working with Lists"),
			   T("lists.sal")));
  helpdocs.add(new HelpDoc(CommandIDs::HelpTutorial+4,
			   T("Making Sound"), 
			   T("sound.sal")));
  helpdocs.add(new HelpDoc(CommandIDs::HelpTutorial+5,
			   T("Defining Variables"),
			   T("variables.sal")));
  helpdocs.add(new HelpDoc(CommandIDs::HelpTutorial+6,
			   T("Defining Functions"),
			   T("functions.sal")));
  helpdocs.add(new HelpDoc(CommandIDs::HelpTutorial+7,
			   T("Iteration"), 
			   T("loop.sal")));
  helpdocs.add(new HelpDoc(CommandIDs::HelpTutorial+8, 
			   T("Musical Processes"), 
			   T("processes.sal")));
  // Examples
  helpdocs.add(new HelpDoc(CommandIDs::HelpExample+0,
			   T("Notes, keys and pitch classes"),
			   T("notes.sal")));
  helpdocs.add(new HelpDoc(CommandIDs::HelpExample+1,
			   T("Scales and interval cycles"),
			   T("scales.sal")));
  helpdocs.add(new HelpDoc(CommandIDs::HelpExample+2,
			   T("Sending data to ports"),
			   T("send.sal")));  
  helpdocs.add(new HelpDoc(CommandIDs::HelpExample+3,
			   T("Sending data to Csound"),
			   T("harmonizer.sal")));  
  helpdocs.add(new HelpDoc(CommandIDs::HelpExample+4,
			   T("Markov harmonizer a la Messiaen"),
			   T("harmonizer.sal")));  
  helpdocs.add(new HelpDoc(CommandIDs::HelpExample+5,
			   T("Sprouting processes"),
			   T("sprout.sal")));  
  helpdocs.add(new HelpDoc(CommandIDs::HelpExample+6,
			   T("Building gestures"),
			   T("gestures.sal")));  
  helpdocs.add(new HelpDoc(CommandIDs::HelpExample+7,
			   T("A la maniere de 'continuum' (Ligeti)"),
			   T("continuum.sal")));  
  // Websites
  helpdocs.add(new HelpDoc(CommandIDs::HelpWebSite+0,
			   T("Common Music Homepage"),
			   T("http://commonmusic.sf.net/doc/cm.html")
			   ));
  helpdocs.add(new HelpDoc(CommandIDs::HelpWebSite+1,
			   T("Chicken Scheme Homepage"),
	       T("http://www.call-with-current-continuation.org/")
			   ));
  helpdocs.add(new HelpDoc(CommandIDs::HelpWebSite+2,
			   T("JUCE Homepage"),
			   T("http://www.rawmaterialsoftware.com/juce")
			   ));
}

//==============================================================================
// This macro creates the application's main() function..

START_JUCE_APPLICATION (GraceApp)
