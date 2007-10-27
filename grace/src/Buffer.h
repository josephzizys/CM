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
  int isKeyCommand(const KeyPress& key);
  void keyControlAction(const KeyPress& key);
  void keyControlXAction(const KeyPress& key);
  void keyMetaAction(const KeyPress& key);
  void keyControlMetaAction(const KeyPress& key);
  void keyCommandAction(const KeyPress& key);
  void keyIllegalAction(const KeyPress& key);
  void keyDefaultAction(const KeyPress& key);
  bool keyPressed(const KeyPress& key) ;
  //void mouseDown(const MouseEvent &e) ;
  void mouseDoubleClick(const MouseEvent &e) ;

 public:

  enum BufferFlags {needsave=1, readonly=2, hiliteoff=4, parensoff=8, 
		    load=16, nosave=32, emacsmode=64};

  // some commands span more than one command
  enum editAction { actMoveLine = 1, actKillLine, actKillWord, actKillSexpr, 
		    actControlX };

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
    cmdFileOpenRecent = 66560,
    cmdFileClearRecent = 66816,
    cmdFileSave = 67072,
    cmdFileSaveAs = 67328,
    cmdFileRevert = 67584,
    cmdFileClose = 67840,
    cmdEditUndo = 68096,
    cmdEditRedo = 68352,
    cmdEditCut = 68608,
    cmdEditCopy = 68864,
    cmdEditPaste = 69120,
    cmdEditSelectAll = 69376,
    cmdEditImport = 69632,
    cmdViewFontList = 69888,
    cmdViewFontSize = 70144,
    cmdViewThemes = 70400,
    cmdOptionsHiliting = 70656,
    cmdOptionsParens = 70912,
    cmdOptionsEmacsMode = 71168,
    cmdLispEval = 71424,
    cmdLispSetPackage = 71680,
    cmdSalEval = 71936,
    cmdSymbolHelp = 72192,
    cmdCharForward = 72448,
    cmdCharBackward = 72704,
    cmdWordForward = 72960,
    cmdWordBackward = 73216,
    cmdSexprForward = 73472,
    cmdSexprBackward = 73728,
    cmdLineForward = 73984,
    cmdLineBackward = 74240,
    cmdPageForward = 74496,
    cmdPageBackward = 74752,
    cmdGotoEOL = 75008,
    cmdGotoBOL = 75264,
    cmdGotoEOB = 75520,
    cmdGotoBOB = 75776,
    cmdGotoColumn = 76032,
    cmdGotoLine = 76288,
    cmdBackspace = 76544,
    cmdDelete = 76800,
    cmdKillWord = 77056,
    cmdKillSexpr = 77312,
    cmdKillWhite = 77568,
    cmdKillLine = 77824,
    cmdInsertChar = 78080,
    cmdInsertLine = 78336,
    cmdOpenLine = 78592,
    cmdComplete = 78848,
    cmdIndent = 79104,
    cmdToggleReadWrite = 79360};

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
  int findCharForward(char c);
  int findCharBackward(char c);

  void salTokenize();
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
