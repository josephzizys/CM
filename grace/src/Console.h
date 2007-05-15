/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

#ifndef __CONSOLE__
#define __CONSOLE__

#include "Editor.h"

enum printType {textMessage,
		textWarning,
		textError};

class ConsoleWindow  : public DocumentWindow
{
  Colour inputColour, outputColour, errorColour, warningColour;
  void toggleColourOutput();
  void toggleColourInput();
  void toggleColourError();
  void toggleColourWarning();

public:
  EditorComponent* console;
  ConsoleWindow () ;
  ~ConsoleWindow () ;

  void closeButtonPressed () ;
  //  void activeWindowStatusChanged();
  TextBuffer * consoleBuffer();
  void consolePrint(printType mode, String str) ;
  void consoleFreshLine() ;
};

#endif











