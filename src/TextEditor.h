/*=======================================================================*
   Copyright (C) 2008 Rick Taube.                                        
   This program is free software; you can redistribute it and/or modify  
   it under the terms of the Lisp Lesser Gnu Public License. The text of 
   this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include "juce.h"
#include <iostream>

class Syntax;

class TextBuffer : public TextEditor, 
  public ApplicationCommandTarget,
  public Timer
{
  int textid;
  int flags;
  Syntax* syntax;
  File file;
  int matchpos;
  class TextBufferListener : public TextEditorListener
  {
    // callback sets change flag
    void textEditorTextChanged(TextEditor& editor)
    {
      TextBuffer* buffer=(TextBuffer *)&editor;
      buffer->setFlag(EditFlags::NeedsSave);
      if (buffer->testFlag(EditFlags::Coloring))
	return;
      // command was NOT just invoked
      if (buffer->thisid==CommandIDs::Empty)
	buffer->colorizeAfterChange(CommandIDs::EditorTextChanged);
      else
	{
	  buffer->colorizeAfterChange(buffer->thisid);
	  //  std::cout << "TextChanged: " 
	  //	    << CommandIDs::toString(buffer->thisid).toUTF8()
	  //	    << " (prev=" << CommandIDs::toString(buffer->prev).toUTF8()
	  //	    << ")\n";
	  buffer->thisid=CommandIDs::Empty;
	}
    }
    void textEditorReturnKeyPressed(TextEditor& editor)
    {
      std::cout << "return pressed\n"; // THIS ISNT CALLED!
    }
    void textEditorEscapeKeyPressed(TextEditor& editor) {}
    void textEditorFocusLost(TextEditor& editor) {}
  };
  TextBufferListener listener;
  CommandID prev, thisid;
  static const int BUFMAX = 0xFFFFFFF;
  static const int CHUNKSIZE = 128;
  // mouse and cursor
  void mouseDoubleClick(const MouseEvent &e) ;
  void matchParens();
  bool isMatching();
  void startMatching(int pos1, int pos2);
  void timerCallback();
  void stopMatching();
    
 public:
  ApplicationCommandManager* manager;
  TextBuffer(int texttype);
  ~TextBuffer();

  bool keyPressed(const KeyPress& key);

  // File Menu Support
  bool saveFile();
  bool saveFileAs(File defaultfile=File::nonexistent);
  bool revertFile();
  void loadFile();
  File getFile() {return file;}
  void setFile(File f) {file=f;}
  //  void showDirectory();
  //  void setDirectory();

  // Edit Menu Support
  void paste();
  void cut();
  void selectAll();
  // Options Menu Support
  int getFontSize();
  void setFontSize(int s);
  // Eval Menu Support
  void eval(bool macroexpand=false);

  // Syntax and Highlighting Support
  bool isSyntax(int id) {return (textid==id);}
  void setSyntax(int id) ;
  void syntacticIndent();
  bool indentToColumn(int col);
  int currentIndent();
  void colorizeAll();
  void colorizeAfterChange(CommandID id);
  void colorize(int from, int to, bool force);
  void commentRegion(bool undo);
  String backwardTopLevelText();
  String forwardTopLevelText();

  // Point functions
  int point();
  int setPoint(int p);
  int incPoint(int i);
  bool isBOB();
  bool isEOB();
  bool isBOL();
  bool isEOL();
  int pointBOL();
  int pointEOL();
  int pointColumn();
  int pointLineLength();
  int bufferMin();
  int bufferMax();

  // Cursor motion functions
  int gotoBOL();
  int gotoEOL();
  int gotoBOB();
  int gotoEOB();
  void forwardChar();
  void backwardChar();
  void forwardWord();
  void backwardWord();
  void forwardLine();
  void backwardLine();
  void forwardPage();
  void backwardPage();
  void forwardExpr();
  void backwardExpr();
  bool moveLine(int n);

  // Search functions
  int findCharForward(char c);
  int findCharBackward(char c);
  // Edit functions
  void killChar();
  void killWord();
  void killExpr();
  void killLine();
  void killWhite();
  void killRegion();
  void openLine();
  void changeCase(int typ);

  void updateClipboardWithKill(String kill, CommandID com);
  void deleteRegion(int from, int to);

  // Basic support
  bool testFlag(int f) {return Flags::test(flags,f);}
  void setFlag(int f) {Flags::setOn(flags,f);}
  void clearFlag(int f) {Flags::setOff(flags,f);}
  bool toggleFlag(int f) {return Flags::toggle(flags,f);}
  void updateEditorCommands(bool emacs);
  void updateWindowTitle();
  void lookupHelpAtPoint();

  // Command Target methods implemented in Command.cpp
  ApplicationCommandTarget* getNextCommandTarget();
  void getAllCommands(Array<CommandID>& commands);
  void getCommandInfo(const CommandID id, ApplicationCommandInfo& info);
  bool perform(const ApplicationCommandTarget::InvocationInfo& info);

  // editing


};

class TextEditorWindow : public DocumentWindow, public MenuBarModel
{
  TextBuffer* buffer;
 public:
  TextEditorWindow (File file=File::nonexistent, 
		    String text=String::empty,
		    int synt=TextIDs::Empty,
		    String title=String::empty
		    ) ;
  ~TextEditorWindow () ;
  void closeButtonPressed () ;
  TextBuffer* getTextBuffer() {return buffer;}
  const StringArray getMenuBarNames ();
  const PopupMenu getMenuForIndex (int menuIndex, 
				   const String& menuName);
  void menuItemSelected (int menuItemID, int topLevelMenuIndex);
};

#endif

