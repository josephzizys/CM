/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

#ifndef __BUFFER__
#define __BUFFER__

#include "juce.h"
#include "Syntax.h"
#include "Console.h"

class TextRange
{
 public:
  int start;
  int end;
  TextRange(int a, int b) { end = a; end = b;}
  ~TextRange() {}

  void setRange(int a, int b) { start = a; end = b;}
  int length() { return end-start;}
};

class TextBuffer : public TextEditor,
		   public ApplicationCommandTarget
{
  syntaxID syntaxId;
  Syntax* syntax;
  int thisact, lastact;
  int goalColumn;
  bool changed; // needs save
  bool hiliting; // wants hiliting

  TopLevelWindow *parentWindow;

  void initSyntax(syntaxID m);
  void setAction(int act) { thisact=act ;}
  void storeAction() { lastact=thisact; }
  bool isLastAction(int act) { return (lastact==act) ? true : false; }
  int isKeyAction(const KeyPress& key);
  void keyControlAction(const KeyPress& key);
  void keyControlXAction(const KeyPress& key);
  void keyMetaAction(const KeyPress& key);
  void keyControlMetaAction(const KeyPress& key);
  void keyCommandAction(const KeyPress& key);
  void keyIllegalAction(const KeyPress& key);
  void keyDefaultAction(const KeyPress& key);
  void keyPressed(const KeyPress& key) ;
  void mouseDown(const MouseEvent &e) ;

 public:

  enum CommandIDs {
    cmdNewSal = 20001,
    cmdNewLisp,
    cmdNewText,
    cmdOpen,
    cmdSave,
    cmdSaveAs,
    cmdRevert,
    cmdClose,
    cmdUndo,
    cmdRedo,
    cmdCut,
    cmdCopy,
    cmdPaste,
    cmdSelectAll,
    cmdOptions,
    cmdFonts,
    
    cmdCharForward,
    cmdCharBackward,
    cmdWordForward,
    cmdWordBackward,
    cmdSexprForward,
    cmdSexprBackward,
    cmdLineForward,
    cmdLineBackward,
    cmdPageForward,
    cmdPageBackward,
    cmdGotoEOL,
    cmdGotoBOL,
    cmdGotoEOB,
    cmdGotoBOB,
    cmdGotoColumn,
    cmdGotoLine,

    cmdBackspace,
    cmdDelete,
    cmdKillWord,
    cmdKillSexpr,
    cmdKillWhite,
    cmdKillLine,
    cmdInsertChar,
    cmdInsertLine,
    cmdOpenLine,

    cmdComplete,
    cmdIndent,
    cmdToggleHiliting,
    cmdSymbolHelp,
    cmdEval
  };

  bool isHiliting() {return hiliting;}
  void setHiliting(bool h) {hiliting=h;}
  bool isChanged()  {return changed;}
  void setChanged(bool c) {changed=c;}
    
  TextBuffer(String nam, syntaxID m, TopLevelWindow *pwind = 0);
  ~TextBuffer();
  syntaxID getBufferSyntax() { return syntaxId; }
  int point ();
  int setPoint(int p);
  int incPoint(int i);

  int bufferMin ();
  int bufferMax ();
  int pointBOL ();
  int pointEOL ();
  int pointColumn();
  int pointLineLength();
  bool isBOB();
  bool isEOB();
  bool isBOL();
  bool isEOL();
  int gotoBOL ();
  int gotoEOL ();
  int gotoBOB ();
  int gotoEOB ();
  int forwardChar();
  int backwardChar();

  bool moveLine(int n);
  void nextLine();
  void previousLine();

  void forwardScreen();
  void backwardScreen();
  int forwardSkipChars(String chars);

  // syntax dependant
  String backwardTopLevelText();
  String forwardTopLevelText();
  void syntacticIndent();
  int moveWord(int num);
  int forwardWord();
  int backwardWord();  
  int forwardSexpr();
  int backwardSexpr();
  int evalLastSexpr();
  void toggleHiliting() ;
  void colorize(int from, int to, bool force) ;
  void colorizeAll() ;
  void colorizeAfterChange(int cmd) ;

  // editing
  void updateClipboardWithKill(String text, int cmd);
  int deleteChar(int num);
  int openLine();
  void deleteRegion(int from, int to);
  void killLine();
  void killWord();
  void killSexpr();
  int forwardDeleteChars(String chars);
  int insertText(String str);
  void selectAll();
  int currentIndent();
  int indentToColumn(int col);

  void testit();

  ApplicationCommandTarget* getNextCommandTarget();
  void getAllCommands (Array <CommandID>& commands);
  void getCommandInfo (const CommandID commandID, ApplicationCommandInfo& result);
  bool perform (const InvocationInfo& info);


  File editfile;
  Font editfont;


  
  void openFile();
  void newFile(syntaxID syn);
  void saveFile();
  void saveFileAs();
  void revertFile();
  void setFontType(const String typeface);
  void setFontSize( float size );
  ConsoleWindow* getConsole();
};


/* 

// this code is commented out because JUCE calls the textchanged method
// whever a key is pressed, not when text has actually changed.

class TextBufferListener : public TextEditorListener
{  public:
  TextBuffer * buf;
  TextBufferListener (TextBuffer * b) { buf=b; }
  ~TextBufferListener () {
  }

  void textEditorTextChanged (TextEditor &editor) {
    buf->setChanged(true);
    printf("Changed!\n");
  }
  void textEditorReturnKeyPressed (TextEditor &editor) {}
  void textEditorEscapeKeyPressed (TextEditor &editor) {}
  void textEditorFocusLost (TextEditor &editor) {}

};

*/


#endif
