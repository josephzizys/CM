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
		   public ApplicationCommandTarget
{
  syntaxID syntaxId;
  Syntax* syntax;
  int thisact, lastact;
  int goalColumn;

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
		    load=16};
  int flags;
  
  int getFlag(int f) {return (flags & f);}
  bool testFlag(int f) {return (getFlag(f) == f);}
  void setFlagOn(int f) {flags |= f; return ;}
  void setFlagOff(int f) {flags &= ~f; return ;}
  bool toggleFlag(int f) {flags ^= f; return testFlag(f);}

/*
(defun enums (block enumname &rest names)
  (let* ((cmdinfo #xFF)
         (blockwidth (* 128 cmdinfo))
	 (blockstart (* blockwidth block)))
  (format t "  enum ~A {~%" enumname)
  (loop with m = (length names)
     for n in names for i from 1
     do (if (= i 128) (error "too many commands, block size = 128"))
     (format t "    cmd~A = ~D~:[,~;};~]~%" n
	     (+ (ash i 8) blockstart)
	     (= i m)))))
(enums 3 "EditorCommand" "NewSal" "NewLisp" "NewText" "Open"
       "Save" "SaveAs" "Revert" "Close" "Undo" "Redo"
       "Cut" "Copy" "Paste" "SelectAll" "Options" "Fonts"
       "CharForward" "CharBackward" "WordForward" 
       "WordBackward" "SexprForward" "SexprBackward"
       "LineForward" "LineBackward" "PageForward"
       "PageBackward" "GotoEOL" "GotoBOL" "GotoEOB"
       "GotoBOB" "GotoColumn" "GotoLine"  "Backspace"
       "Delete" "KillWord" "KillSexpr" "KillWhite"
       "KillLine" "InsertChar" "InsertLine" "OpenLine"
       "ViewFontList" "ViewFontSize" "Complete" "Indent"
       "ToggleHiliting" "ToggleParens" "ToggleReadWrite"
        "Eval" "HelpEditor" )
*/
 
  enum EditorCommand {
    cmdNewSal = 98176,
    cmdNewLisp = 98432,
    cmdNewText = 98688,
    cmdOpen = 98944,
    cmdSave = 99200,
    cmdSaveAs = 99456,
    cmdRevert = 99712,
    cmdClose = 99968,
    cmdUndo = 100224,
    cmdRedo = 100480,
    cmdCut = 100736,
    cmdCopy = 100992,
    cmdPaste = 101248,
    cmdSelectAll = 101504,
    cmdOptions = 101760,
    cmdFonts = 102016,
    cmdCharForward = 102272,
    cmdCharBackward = 102528,
    cmdWordForward = 102784,
    cmdWordBackward = 103040,
    cmdSexprForward = 103296,
    cmdSexprBackward = 103552,
    cmdLineForward = 103808,
    cmdLineBackward = 104064,
    cmdPageForward = 104320,
    cmdPageBackward = 104576,
    cmdGotoEOL = 104832,
    cmdGotoBOL = 105088,
    cmdGotoEOB = 105344,
    cmdGotoBOB = 105600,
    cmdGotoColumn = 105856,
    cmdGotoLine = 106112,
    cmdBackspace = 106368,
    cmdDelete = 106624,
    cmdKillWord = 106880,
    cmdKillSexpr = 107136,
    cmdKillWhite = 107392,
    cmdKillLine = 107648,
    cmdInsertChar = 107904,
    cmdInsertLine = 108160,
    cmdOpenLine = 108416,
    cmdViewFontList = 108672,
    cmdViewFontSize = 108928,
    cmdComplete = 109184,
    cmdIndent = 109440,
    cmdToggleHiliting = 109696,
    cmdToggleParens = 109952,
    cmdToggleReadWrite = 110208,
    cmdEval = 110464,
    cmdHelpEditor = 110720};

  TextBuffer(syntaxID id, int flg);
  ~TextBuffer();

  syntaxID getBufferSyntax() { return syntaxId; }

  bool isHiliting();
  void toggleHiliting();
  bool isParensMatching();
  void toggleParensMatching ();
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
  int evalLastSexpr();
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
