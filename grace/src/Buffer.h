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
		    load=16, emacsmode=32};
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

(enums 3 "EditorCommand"
       "FileNewSal" "FileNewLisp" "FileNewText" "FileOpen"
       "FileSave" "FileSaveAs" "FileRevert" "FileClose"
       "EditUndo" "EditRedo" "EditCut" "EditCopy" "EditPaste"
       "EditSelectAll" "EditImport"

       "ViewFontList" "ViewFontSize" "ViewThemes"

       "OptionsHiliting" "OptionsParens" "OptionsEmacsMode"

       "LispEval" "LispSetPackage"
       "SalEval"
       "HelpEditor"

       "CharForward" "CharBackward" "WordForward" 
       "WordBackward" "SexprForward" "SexprBackward"
       "LineForward" "LineBackward" "PageForward"
       "PageBackward" "GotoEOL" "GotoBOL" "GotoEOB"
       "GotoBOB" "GotoColumn" "GotoLine"  "Backspace"
       "Delete" "KillWord" "KillSexpr" "KillWhite"
       "KillLine" "InsertChar" "InsertLine" "OpenLine"
       "Complete" "Indent"  "ToggleReadWrite"
 )
*/
 
  enum EditorCommand {
    cmdFileNewSal = 98176,
    cmdFileNewLisp = 98432,
    cmdFileNewText = 98688,
    cmdFileOpen = 98944,
    cmdFileSave = 99200,
    cmdFileSaveAs = 99456,
    cmdFileRevert = 99712,
    cmdFileClose = 99968,
    cmdEditUndo = 100224,
    cmdEditRedo = 100480,
    cmdEditCut = 100736,
    cmdEditCopy = 100992,
    cmdEditPaste = 101248,
    cmdEditSelectAll = 101504,
    cmdEditImport = 101760,
    cmdViewFontList = 102016,
    cmdViewFontSize = 102272,
    cmdViewThemes = 102528,
    cmdOptionsHiliting = 102784,
    cmdOptionsParens = 103040,
    cmdOptionsEmacsMode = 103296,
    cmdLispEval = 103552,
    cmdLispSetPackage = 103808,
    cmdSalEval = 104064,
    cmdHelpEditor = 104320,
    cmdCharForward = 104576,
    cmdCharBackward = 104832,
    cmdWordForward = 105088,
    cmdWordBackward = 105344,
    cmdSexprForward = 105600,
    cmdSexprBackward = 105856,
    cmdLineForward = 106112,
    cmdLineBackward = 106368,
    cmdPageForward = 106624,
    cmdPageBackward = 106880,
    cmdGotoEOL = 107136,
    cmdGotoBOL = 107392,
    cmdGotoEOB = 107648,
    cmdGotoBOB = 107904,
    cmdGotoColumn = 108160,
    cmdGotoLine = 108416,
    cmdBackspace = 108672,
    cmdDelete = 108928,
    cmdKillWord = 109184,
    cmdKillSexpr = 109440,
    cmdKillWhite = 109696,
    cmdKillLine = 109952,
    cmdInsertChar = 110208,
    cmdInsertLine = 110464,
    cmdOpenLine = 110720,
    cmdComplete = 110976,
    cmdIndent = 111232,
    cmdToggleReadWrite = 111488};


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
