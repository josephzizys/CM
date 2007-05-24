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
#include "Resources.h"
#include <strings.h>


// NEVER touch these, use initialize() and shutdown() methods!
GraceApp::GraceApp () : console (0) {}
GraceApp::~GraceApp () {}

GraceSplash::~GraceSplash () {  // defined in Resource.h
  GraceApp* app = (GraceApp *)GraceApp::getInstance();

  //app->printBanner();
  printf("Hello from Grace!\n");
  app->openInitialWindows();
};

void GraceApp::openInitialWindows () {

  // HACKED to open some demo windows...
  EditorWindow * e = new EditorWindow( File(T("demo.sal")) ) ;
  e->editor->buffer->setText(T("; this is a sal buffer with emacs support\n\ndefine function rankeys (n)\n  loop with l = {}\n    for i below n\n    set l &= random(127)\n    finally return l\n  end\n\nprint \"random keys \", rankeys(20)\n\nprint make(<midi>, time: now(), keynum: between(60, 80)\n\nbegin\n  open \"test.mid\", versioning: #t\n  sprout fuff( note(440, :hz) ,2) ; keywords colored as constants\nend\n"));
    e->editor->buffer->colorizeAll();
    //    PlotterWindow * p1 = new PlotterWindow( MidiPlot ) ;
    PlotterWindow * p2 = new PlotterWindow( XYPlot ) ;
    p2->setTopLeftPosition(e->getX()+40,e->getY()+40);
}

void GraceApp::openSplashWindow (bool modal) {
  // at some point the splash will also serve as the About... window
  GraceSplash * splash = new GraceSplash();
  Image * logo = ImageCache::getFromMemory (splash->grace_png,
					    splash->grace_pngSize
					    ) ;
  splash->centreWithSize (450, 340);
  splash->show ("", logo, 1500, false);
}

void GraceApp::initialise (const String& commandLine) {
  openSplashWindow(false);  // hack opens top-level windows at end
  LookAndFeel::setDefaultLookAndFeel (&shinyLookAndFeel);
  File home = File::getSpecialLocation(File::userHomeDirectory);
  commandManager = new ApplicationCommandManager();
  home.setAsCurrentWorkingDirectory();
  fontList = FontList::getInstance();
  console = 0;
}

void GraceApp::shutdown () {
  if (console != 0)
    delete console;
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

void GraceApp::printMessage(String str) {
  console->consolePrint(textMessage, str);
}

void GraceApp::printWarning(String str) {
  console->consolePrint(textWarning, str);
}

void GraceApp::printError(String str) {
  console->consolePrint(textError, str);    
  }

void GraceApp::printBanner() {
  String banner = getApplicationName() + T(" ")
    + getApplicationVersion()
    + T("\n(c) 2007 Todd Ingalls, Rick Taube\n");
  console->consolePrint(textMessage, banner);
  console->consoleBuffer()->gotoEOB();
}

//==============================================================================
// This macro creates the application's main() function..

START_JUCE_APPLICATION (GraceApp)
