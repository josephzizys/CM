/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

#ifndef __EDITOR__
#define __EDITOR__

#include "Buffer.h"

const int fontSizeList[] = {9, 10, 12, 14, 16, 18, 24, 32};

class EditorComponent : public Component {
  // this class is currently useless since all it holds is the
  // buffer. maybe later can group buffer with other stuff

  void resized () { buffer->setSize(getWidth(), getHeight()); }

 public:
  
  TextBuffer* buffer;

  EditorComponent (String pathname, syntaxID mode) {
    buffer = new TextBuffer(pathname, mode);
    buffer->setTopLeftPosition(0,0);
    addChildComponent( buffer, -1);
  }

  ~EditorComponent() {
    buffer->~TextBuffer();
  }
};

class EditorWindow  : public DocumentWindow,
		      public MenuBarModel
{
 public:
  
  File editfile;
  Font editfont;
  EditorComponent* editor;
  TextBuffer* getTextBuffer() {return editor->buffer; }
  
  EditorWindow (String filename, bool load=false, int syntax=0) ;
  ~EditorWindow () ;
  void closeButtonPressed () ;

  /* File Menu */

  ApplicationCommandManager *commandManager;
  

  // menubar and menus
  const StringArray getMenuBarNames (MenuBarComponent* menuBar);
  const PopupMenu getMenuForIndex (MenuBarComponent* menuBar, int menuIndex, const String& menuName);
  void menuItemSelected (MenuBarComponent* menuBar, int menuItemID, int topLevelMenuIndex);
   
 
};

#endif
