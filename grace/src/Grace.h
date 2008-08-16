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
#include "Fomus.h"
#endif

class GraceApp : public JUCEApplication
{
  LookAndFeel shinyLookAndFeel;

  class HelpDoc
  {
  public:
    CommandID type;
    String name;
    String path;
    HelpDoc(CommandID _type, String _name, String _path)
      {
	type=_type;
	name=_name;
	path=_path;
      }
    ~HelpDoc()
      {
      }
  };
  OwnedArray<HelpDoc> helpdocs;
  void initHelp();

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
  FomusPort* fomusPort;
  MidiOutPort* getMidiOutPort() {return midiOutPort;}
  MidiInPort* getMidiInPort() {return midiInPort;}
  CsoundPort* getCsoundPort() {return csoundPort;}
  FomusPort* getFomusPort() {return fomusPort;}
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


  const PopupMenu getWindowMenu();
  void performWindowCommand(CommandID id);
  const PopupMenu getHelpMenu();
  void performHelpCommand(CommandID id);
};

#endif
