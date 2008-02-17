/*************************************************************************
 * Copyright (C) 2007, 2008 Todd Ingalls, Rick Taube.                    *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

#ifndef __GRACE__
#define __GRACE__
#include "juce.h"
#include "Console.h"

#ifdef SCHEME
#include "Scheme.h"
#include "Midi.h"
#include "Csound.h"
#endif

class GraceApp : public JUCEApplication
{
  LookAndFeel shinyLookAndFeel;
public:
  ConsoleWindow* console;
  //    FontList* fontList;
  ApplicationCommandManager *commandManager ;
  AudioDeviceManager audioManager;
#ifdef SCHEME
  SchemeThread* schemeProcess;
  MidiOutPort* midiOutPort;
  MidiInPort* midiInPort;
  CsoundPort* csoundPort;
  MidiOutPort* getMidiOutPort() {return midiOutPort;}
  MidiInPort * getMidiInPort(){return midiInPort;}
  CsoundPort * getCsoundPort(){return csoundPort;}
#endif
  File resourceDirectory;
  GraceApp() ;
  ~GraceApp();
  void anotherInstanceStarted (const String& commandLine);
  bool moreThanOneInstanceAllowed() ;
  void initialise (const String& commandLine);
  void shutdown() ;
  const String getApplicationName() ;
  const String getApplicationVersion() ;
  void graceQuit(bool ask);
  AudioDeviceManager * getAudioDeviceManager();
  ConsoleWindow* getConsole() {return console;}
  File getResourceDirectory() {return resourceDirectory;}
  void setResourceDirectory(File dir) {resourceDirectory=dir;}
  String getResourceDirectoryPathName() {return resourceDirectory.getFullPathName();}
  GracePreferences* prefs;
  GracePreferences* getPreferences() {return prefs;}
};

#endif
