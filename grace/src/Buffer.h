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

class TextBuffer : public TextEditor,
  public ApplicationCommandTarget,
  public Timer
{
  syntaxID syntaxId;
  Syntax* syntax;
  int thisact, lastact;
  int goalColumn;
  int matching;
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
  //void mouseDown(const MouseEvent &e) ;
  void mouseDoubleClick(const MouseEvent &e) ;

 public:

  enum BufferFlags {needsave=1, readonly=2, hiliteoff=4, parensoff=8, 
		    load=16, nosave=32, emacsmode=64};
  int flags;

  int getFlag(int f) {return (flags & f);}
  bool testFlag(int f) {return (getFlag(f) == f);}
  void setFlagOn(int f) {flags |= f; return ;}
  void setFlagOff(int f) {flags &= ~f; return ;}
  bool toggleFlag(int f) {flags ^= f; return testFlag(f);}

  bool isTextSyntax() {return (syntaxId==syntaxText);}
  bool isSalSyntax() {return (syntaxId==syntaxSal);}
  bool isLispSyntax() {return (syntaxId==syntaxLisp);}
  bool isEmacsMode() {return testFlag(emacsmode);}
  void toggleEmacsMode() {toggleFlag(emacsmode);}

  // ENUMS defined in grace.lisp

  enum EditorCommand {
    cmdFileNewSal = 65536,
    cmdFileNewLisp = 65792,
    cmdFileNewText = 66048,
    cmdFileOpen = 66304,
    cmdFileSave = 66560,
    cmdFileSaveAs = 66816,
    cmdFileRevert = 67072,
    cmdFileClose = 67328,
    cmdEditUndo = 67584,
    cmdEditRedo = 67840,
    cmdEditCut = 68096,
    cmdEditCopy = 68352,
    cmdEditPaste = 68608,
    cmdEditSelectAll = 68864,
    cmdEditImport = 69120,
    cmdViewFontList = 69376,
    cmdViewFontSize = 69632,
    cmdViewThemes = 69888,
    cmdOptionsHiliting = 70144,
    cmdOptionsParens = 70400,
    cmdOptionsEmacsMode = 70656,
    cmdLispEval = 70912,
    cmdLispSetPackage = 71168,
    cmdSalEval = 71424,
    cmdSymbolHelp = 71680,
    cmdCharForward = 71936,
    cmdCharBackward = 72192,
    cmdWordForward = 72448,
    cmdWordBackward = 72704,
    cmdSexprForward = 72960,
    cmdSexprBackward = 73216,
    cmdLineForward = 73472,
    cmdLineBackward = 73728,
    cmdPageForward = 73984,
    cmdPageBackward = 74240,
    cmdGotoEOL = 74496,
    cmdGotoBOL = 74752,
    cmdGotoEOB = 75008,
    cmdGotoBOB = 75264,
    cmdGotoColumn = 75520,
    cmdGotoLine = 75776,
    cmdBackspace = 76032,
    cmdDelete = 76288,
    cmdKillWord = 76544,
    cmdKillSexpr = 76800,
    cmdKillWhite = 77056,
    cmdKillLine = 77312,
    cmdInsertChar = 77568,
    cmdInsertLine = 77824,
    cmdOpenLine = 78080,
    cmdComplete = 78336,
    cmdIndent = 78592,
    cmdToggleReadWrite = 78848};

  TextBuffer(syntaxID id, int flg);
  ~TextBuffer();

  syntaxID getBufferSyntax() { return syntaxId; }

  bool isHiliting();
  void toggleHiliting();
  bool isParensMatching();
  void toggleParensMatching ();
  bool isMatching();
  void startMatching(int pos1, int pos2);
  void stopMatching();
  void timerCallback();
  bool isChanged();
  void setChanged(bool b);
  void toggleReadOnly();

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
  int evalText();
  //  void toggleHiliting() ;
  void matchParens();
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

  void setFontType(const String typeface);
  float getFontSize( );
  void setFontSize( float size );

  ConsoleWindow* getConsole();

  void lookupHelpAtPoint() ;
  void reformatCommentBlock () ;
  void changeCase(int flag);
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
