/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

#ifndef __GRACE__
#define __GRACE__
#include "juce.h"
#include "FontList.h"
#include "Console.h"
#include "Audio.h"

#ifdef EMBED_SCHEME
#include "Scheme.h"
#endif


class GraceApp : public JUCEApplication
{
  LookAndFeel shinyLookAndFeel;

public:
    
    ConsoleWindow* console;
    FontList* fontList;
    ApplicationCommandManager *commandManager ;
    AudioDeviceManager audioManager;

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
    GracePreferences* prefs;
    GracePreferences* getPreferences() {return prefs;}
#ifdef EMBED_SCHEME
	SchemeThread* schemeProcess;
#endif
	
	
};


#endif
