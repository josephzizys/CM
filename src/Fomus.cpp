/*=======================================================================*
  Copyright (C) 2009 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#include "Enumerations.h"
#include "Fomus.h"
#include "Console.h"


/*=======================================================================*
                             Fomus Instance
 *=======================================================================*/

juce_ImplementSingleton(Fomus);

Fomus::Fomus () 
  : scorefile (File::nonexistent),
    application (File::nonexistent),
    commandargs (String::empty),
    playafter (false)
{
}

Fomus::~Fomus ()
{
}

void Fomus::execute()
{
  Console::getInstance()->printOutput("FIXME: Fomus execute.");
}

/*=======================================================================*
  Remainder of file is Grace GUI code, not part of the console CM app
 *=======================================================================*/

#ifdef GRACE


void Fomus::openSettings()
{
  AlertWindow::showMessageBox(AlertWindow::InfoIcon, T("Fomus Settings"),
			      T("FIXME: Fomus settings dialog."));
}

void Fomus::openDocumentation()
{
  AlertWindow::showMessageBox(AlertWindow::InfoIcon, T("Fomus Documentation"),
			      T("FIXME: Fomus documentation dialog."));
}

#endif
