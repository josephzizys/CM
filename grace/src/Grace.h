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

class GraceApp : public JUCEApplication
{
    ShinyLookAndFeel shinyLookAndFeel;

public:
    
    ConsoleWindow* console;
    FontList* fontList;
    GraceApp() ;
    ~GraceApp();
    void anotherInstanceStarted (const String& commandLine);
    bool moreThanOneInstanceAllowed() ;
    void initialise (const String& commandLine);
    void shutdown() ;
    const String getApplicationName() ;
    const String getApplicationVersion() ;
    EditorWindow * newFile(syntaxID mode);
    EditorWindow * openFile(String defaultDir);
    EditorWindow * editFile(File file);
    ApplicationCommandManager *commandManager ;
    
    void openInitialWindows();
    void openSplashWindow(bool modal);

    void printMessage(String str);
    void printWarning(String str);
    void printError(String str);
    void printBanner();
};


#endif
