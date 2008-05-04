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
#endif

}

void GraceApp::graceQuit (bool ask) {
  bool doit=false;
  if (ask) {
    if (AlertWindow::showOkCancelBox
	(AlertWindow::QuestionIcon, T("Quit"),
	 T("Really quit Grace? Any unsaved work will be lost."),
	 T("   OK   "), T("Cancel"))
	)
      doit=true;
  }
  else doit=false;
  if (doit) {
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

//==============================================================================
// This macro creates the application's main() function..

START_JUCE_APPLICATION (GraceApp)
