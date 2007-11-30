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
  StringArray devices;
  int i=0;
  home.setAsCurrentWorkingDirectory();
  LookAndFeel::setDefaultLookAndFeel(&shinyLookAndFeel);
  commandManager = new ApplicationCommandManager();
  audioManager.initialise(1,2,0,true);
  //  fontList = FontList::getInstance();
  prefs=GracePreferences::getInstance();
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
  printf("in shutdown\n");
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
#endif
  delete console;
  delete prefs;
  delete commandManager;
  //LookAndFeel::setDefaultLookAndFeel(0); // this causes crash. not needed. 
  printf("end shutdown\n");
}

const String GraceApp::getApplicationName () {
  return T("Grace");
}

const String GraceApp::getApplicationVersion () {
  return T("0.2.0");
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
