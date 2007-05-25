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
#include <strings.h>

// NEVER touch these, use initialize() and shutdown() methods!
GraceApp::GraceApp () : console (0) {}
GraceApp::~GraceApp () {}

void GraceApp::initialise (const String& commandLine) {
  File home = File::getSpecialLocation(File::userHomeDirectory);

  home.setAsCurrentWorkingDirectory();
  LookAndFeel::setDefaultLookAndFeel(&shinyLookAndFeel);
  commandManager = new ApplicationCommandManager();
  //audioManager= new AudioDeviceManager();
  audioManager.initialise(1,2,0,true);
  fontList = FontList::getInstance();
  console = new ConsoleWindow(true);
  printBanner();
}

void GraceApp::graceQuit (bool ask) {
  bool doit=false;
  if (ask) {
    if (AlertWindow::showOkCancelBox
	(AlertWindow::QuestionIcon, T("Quit"),
	 T("Really quit Grace? Any unsaved work will be lost."),
	 T("OK"), T("Cancel"))
	)
      doit=true;
  }
  else doit=false;
  if (doit)
    JUCEApplication::quit();
}


void GraceApp::shutdown () {
  /*  delete console;
  delete audioManager;
  delete commandManager;
  */
  LookAndFeel::setDefaultLookAndFeel(0);
}

const String GraceApp::getApplicationName () {
  return T("Grace");
}

const String GraceApp::getApplicationVersion () {
  return T("0.0.0");
}

bool GraceApp::moreThanOneInstanceAllowed () {
  // JUCE LINUX BUG: if this is false then Grace will not launch on
  // Fedora Core Linux unless you are su'ed to ROOT.
  return true;
}

void GraceApp::anotherInstanceStarted (const String& commandLine) {
}

void GraceApp::printBanner() {
  String banner = getApplicationName() + T(" ")
    + getApplicationVersion()
    + T("\n(c) 2007 Todd Ingalls, Rick Taube\n");
  console->consolePrint( banner);
  //console->gotoEOB();
}

//==============================================================================
// This macro creates the application's main() function..

START_JUCE_APPLICATION (GraceApp)
