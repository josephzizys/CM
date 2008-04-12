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

class TextFileOutputStream : public FileOutputStream
{
 public:
  TextFileOutputStream(const File& f,
		       const int bufferSize_);
  ~TextFileOutputStream();
  void writeText (const String& text,
		  const bool asUnicode,
		  const bool writeUnicodeHeaderBytes,
		  const bool asDOS);
};



class TextFile : public File
{
 public:
  TextFile();
  TextFile (const String& path);
  TextFile (const File& other) ;

  ~TextFile();

  bool isDOS;

  TextFileOutputStream* createOutputStream (const int bufferSize = 0x8000) ;

  bool appendText (const String& textToAppend,
		   const bool asUnicode = false,
		   const bool writeUnicodeHeaderBytes = false) ;
  
  bool replaceWithText (const String& textToWrite,
			const bool asUnicode = false,
			const bool writeUnicodeHeaderBytes = false) ;

  const String loadFileAsString();

};



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
  ~EditorComponent() {
    //delete buffer;
  }
};

class EditorWindow : public DocumentWindow, public MenuBarModel {
 public:
  TextFile editfile;
  Font editfont;
  EditorComponent* editor;
  
  EditorWindow (int syntax=0, int flags=0, String file=String::empty,
		String title=String::empty, String text=String::empty) ;
  ~EditorWindow () ;

  void openFile();
  void closeFile();
  void newFile(syntaxID syn);
  bool saveFile();
  bool saveFileAs(File defaultfile=File::nonexistent);
  bool revertFile();
  void showEditorHelp(int id);
  TextBuffer* getTextBuffer() {return editor->buffer; }
  void closeButtonPressed () ;
  ApplicationCommandManager *commandManager;
  const StringArray getMenuBarNames ();
  const PopupMenu getMenuForIndex (int menuIndex, 
				   const String& menuName);
  void menuItemSelected ( int menuItemID, 
			 int topLevelMenuIndex);
  const PopupMenu getSalMenu();
  const PopupMenu getLispMenu();
  const PopupMenu getHelpMenu();

  void loadFile();
  void compileFile();
  void showDirectory();
  void setDirectory();
  void setPackage();    

};

#endif
