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

const int fontSizeList[] = 
  {9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 22, 24, 28, 32};

class EditorComponent : public Component {
  void resized () { buffer->setSize(getWidth(), getHeight()); }
 public:
  TextBuffer* buffer;
  EditorComponent (syntaxID mode, int flags) {
    buffer = new TextBuffer(mode, flags);
    buffer->setTopLeftPosition(0,0);
    addChildComponent( buffer, -1);
  }
  ~EditorComponent() {buffer->~TextBuffer();}
};

class EditorWindow : public DocumentWindow, public MenuBarModel {
 public:
  File editfile;
  Font editfont;
  EditorComponent* editor;
  
  EditorWindow (int syntax=0, int flags=0, String file=String::empty,
		String title=String::empty, String text=String::empty) ;
  ~EditorWindow () ;

  void openFile();
  void closeFile();
  void newFile(syntaxID syn);
  void saveFile();
  void saveFileAs();
  void revertFile();
  void showEditorHelp(int id);
  TextBuffer* getTextBuffer() {return editor->buffer; }
  void closeButtonPressed () ;
  ApplicationCommandManager *commandManager;
  const StringArray getMenuBarNames (MenuBarComponent* menuBar);
  const PopupMenu getMenuForIndex (MenuBarComponent* menuBar, int menuIndex, 
				   const String& menuName);
  void menuItemSelected (MenuBarComponent* menuBar, int menuItemID, 
			 int topLevelMenuIndex);
};

#endif
