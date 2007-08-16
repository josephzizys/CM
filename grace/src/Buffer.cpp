/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

#include "Buffer.h"
#include "Editor.h"
#include "FontList.h"
#include "Grace.h"

#define BUFMAX 0xFFFFFFF

TextBuffer::TextBuffer (syntaxID id, int flg) 
  : TextEditor(String::empty) {
  flags=flg;
  matching=-1;
  setWantsKeyboardFocus(true);
  setMultiLine(true);
  setReturnKeyStartsNewLine(true);
  setCaretPosition(0);
  setPoint(0);
  initSyntax(id);
  setPopupMenuEnabled(false);
#ifdef DARWIN
  setFlagOn(emacsmode);
#endif

}

void TextBuffer::initSyntax (syntaxID id) {
  // initialize buffers' syntax table for the appropriate editing mode
  syntaxId=id;
  switch (id) {
  case syntaxSal :
    syntax= new SalSyntax();
    break;
  case syntaxLisp :
    syntax= new LispSyntax();
    break;
  case syntaxText :
  default : 
    syntaxId=syntaxText;
    setFlagOn(hiliteoff);
    syntax= new TextSyntax();
    break;
  }
}

TextBuffer::~TextBuffer () {	
}

ApplicationCommandTarget* TextBuffer::getNextCommandTarget() 
{
  return findFirstTargetParentComponent();
}


void TextBuffer::getAllCommands (Array <CommandID>& commands)
{
  const CommandID ids[] = { 
    cmdFileNewSal,
    cmdFileNewLisp,
    cmdFileNewText,
    cmdFileOpen,
    cmdFileOpenRecent,
    cmdFileClearRecent,
    cmdFileSave,
    cmdFileSaveAs,
    cmdFileRevert,
    cmdFileClose,
    cmdEditUndo,
    cmdEditRedo,
    cmdEditCut,
    cmdEditCopy,
    cmdEditPaste,
    cmdEditSelectAll,
    cmdEditImport,
    cmdViewFontList,
    cmdViewFontSize,
    cmdViewThemes,
    cmdOptionsHiliting,
    cmdOptionsParens,
    cmdOptionsEmacsMode,
    cmdLispEval,
    cmdLispSetPackage,
    cmdSalEval,
    cmdSymbolHelp,
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
    cmdToggleReadWrite};
  
  commands.addArray (ids, sizeof (ids) / sizeof (ids [0]));
}

void TextBuffer::getCommandInfo (const CommandID commandID, 
				 ApplicationCommandInfo& result) {
  const String fileCategory (T("File"));
  const String preferencesCategory (T("Preferences"));
  const String navigationCategory (T("Navigation"));
  const String editingCategory (T("Editing"));
  const String optionsCategory (T("Options"));
  PopupMenu fontsMenu;
  GracePreferences* p=GracePreferences::getInstance();

  switch (commandID) {
  case cmdFileNewSal:
    result.setInfo (T("SAL"), String::empty, fileCategory, 0);
    result.addDefaultKeypress (T('N'), ModifierKeys::commandModifier);
    break;
  case cmdFileNewLisp:
    result.setInfo (T("Lisp"), String::empty, fileCategory, 0);
    result.addDefaultKeypress (T('N'), 
			       ModifierKeys::commandModifier | 
			       ModifierKeys::shiftModifier);
    break;
  case cmdFileNewText:
    result.setInfo (T("Text"), String::empty, fileCategory, 0);
    break;
  case cmdFileOpen:
    result.setInfo (T("Open..."), String::empty, fileCategory, 0);
    result.addDefaultKeypress (T('O'), ModifierKeys::commandModifier);
    break;
  case cmdFileOpenRecent:
    result.setInfo (T("Open Recent File"), String::empty, fileCategory, 0);
    break;
  case cmdFileClearRecent:
    result.setInfo (T("Clear Recent Files"), String::empty, fileCategory, 0);
    break;
  case cmdFileClose:
    result.setInfo (T("Close"), String::empty, fileCategory, 0);
    result.addDefaultKeypress (T('W'), ModifierKeys::commandModifier);
    break;
  case cmdFileSave:
    result.setInfo (T("Save"), String::empty, fileCategory, 0);
    result.addDefaultKeypress (T('S'), ModifierKeys::commandModifier);
    result.setActive( isChanged() && !testFlag(nosave) ) ;
    break;
  case cmdFileSaveAs:
    result.setInfo (T("Save As..."), String::empty, fileCategory, 0);
    result.addDefaultKeypress (T('S'), ModifierKeys::commandModifier | 
			       ModifierKeys::shiftModifier);
    break;
  case cmdFileRevert:
    result.setInfo (T("Revert"), String::empty, fileCategory, 0);
    result.addDefaultKeypress (T('R'), ModifierKeys::commandModifier);
    break;
  case cmdEditUndo:
    result.setInfo (T("Undo"), String::empty, editingCategory, 0);
    result.addDefaultKeypress (T('Z'), ModifierKeys::commandModifier);
    break;
  case cmdEditRedo:
    result.setInfo (T("Redo"), String::empty, editingCategory, 0);
    result.addDefaultKeypress (T('Z'), ModifierKeys::commandModifier | 
			       ModifierKeys::shiftModifier);
    break;
  case cmdEditCut:
    result.setInfo (T("Cut"), String::empty, editingCategory, 0);
    result.addDefaultKeypress (T('X'), ModifierKeys::commandModifier);
    break;
  case cmdEditCopy:
    result.setInfo (T("Copy"), String::empty, editingCategory, 0);
    result.addDefaultKeypress (T('C'), ModifierKeys::commandModifier);
    break;
  case cmdEditPaste:
    result.setInfo (T("Paste"), String::empty, editingCategory, 0);
    result.addDefaultKeypress (T('V'), ModifierKeys::commandModifier);
    break;
  case cmdEditSelectAll:
    result.setInfo (T("Select All"), String::empty, editingCategory, 0);
    result.addDefaultKeypress (T('A'), ModifierKeys::commandModifier);
    break;
  case cmdEditImport:
    result.setInfo (T("Import"), String::empty, editingCategory, 0);
    result.addDefaultKeypress(T('I'), ModifierKeys::commandModifier);
    break;
  case cmdOptionsParens:
    result.setInfo (T("Parens Matching"), String::empty, 
		    preferencesCategory, 0);
    break;
  case cmdOptionsEmacsMode:
    result.setInfo (T("Emacs Mode"), String::empty, 
		    preferencesCategory, 0);
    break;
  case cmdLispEval:
    result.setInfo (T("Eval"), String::empty, editingCategory, 0);
    result.addDefaultKeypress(T('E'), ModifierKeys::commandModifier);
    result.setActive(getConsole()->lisp->isLispRunning() );
    break;
  case cmdLispSetPackage:
    result.setInfo (T("Set Package"), String::empty, editingCategory, 0);
    result.setActive(getConsole()->lisp->isLispRunning() );
    break;
  case cmdSalEval:
    result.setInfo (T("Execute"), String::empty, editingCategory, 0);
    result.addDefaultKeypress(KeyPress::returnKey, ModifierKeys::commandModifier);
    result.setActive(getConsole()->lisp->isLoaded(p->getASDF(ASDF::CM)));
    break;

  case cmdSymbolHelp:
    result.setInfo (T("SAL Symbol Help"), String::empty, editingCategory, 0);
    // command H doesn work :(
    // result.addDefaultKeypress(  String::empty, ModifierKeys::commandModifier);
    break;

  case cmdLineBackward:
    result.setInfo (T("Up line"), String::empty, navigationCategory, 0);
    break;
  case cmdLineForward:
    result.setInfo (T("Down line"), String::empty, navigationCategory, 0);
    break;
  case cmdCharBackward:
    result.setInfo (T("Backward char"), String::empty, navigationCategory, 0);
    break;      
  case cmdCharForward:
    result.setInfo (T("Forward char"), String::empty, navigationCategory, 0);
    break;
  case cmdWordBackward:
    result.setInfo (T("Backward word"), String::empty, navigationCategory, 0);
    break;
  case cmdWordForward:
    result.setInfo (T("Forward word"), String::empty, navigationCategory, 0);
    break;
  case cmdGotoEOL:
    result.setInfo (T("End of line"), String::empty, navigationCategory, 0);
    break;
  case cmdGotoBOL:
    result.setInfo (T("Beginning of line"), String::empty, 
		    navigationCategory, 0);
    break;
  case cmdGotoEOB:
    result.setInfo (T("End of buffer"), String::empty, 
		    navigationCategory, 0);
    break;
  case cmdGotoBOB:
    result.setInfo (T("Beginning of buffer"), String::empty,
		    navigationCategory, 0);
    break;
  case cmdPageBackward:
    result.setInfo (T("Page up"), String::empty, navigationCategory, 0);
    break;
  case cmdPageForward:
    result.setInfo (T("Page down"), String::empty, navigationCategory, 0);
    break; 
  case cmdSexprForward:
    result.setInfo (T("End of sexpr"), String::empty, 
		    navigationCategory, 0);
    break;
  case cmdSexprBackward:
    result.setInfo (T("Beginning of sexpr"), String::empty, 
		    navigationCategory, 0);
    break;
  case cmdDelete:
    result.setInfo (T("Delete backward"), String::empty, editingCategory, 0);
    break;
  case cmdKillSexpr:
    result.setInfo (T("Delete to end of sexpr"), String::empty,
		    editingCategory, 0);
    break;
  case cmdIndent:
    result.setInfo (T("Indent"), String::empty, editingCategory, 0);
    break;
  default:
    break;
  }
}

bool TextBuffer::perform (const InvocationInfo& info) {
  switch (info.commandID) {
  case cmdFileNewSal:
    ((EditorWindow*)getTopLevelComponent())->newFile(syntaxSal);
    break;
  case cmdFileNewLisp:
    ((EditorWindow*)getTopLevelComponent())->newFile(syntaxLisp);
    break;
  case cmdFileNewText:
    ((EditorWindow*)getTopLevelComponent())->newFile(syntaxText);
    break;
  case cmdFileOpen:
    ((EditorWindow*)getTopLevelComponent())->openFile();
    break;
  case cmdFileClose:
    ((EditorWindow*)getTopLevelComponent())->closeFile();
    break;
  case cmdFileSave:
    ((EditorWindow*)getTopLevelComponent())->saveFile();
    break;
  case cmdFileSaveAs:
    ((EditorWindow*)getTopLevelComponent())->saveFileAs();
    break;
  case cmdFileRevert:
    ((EditorWindow*)getTopLevelComponent())->revertFile();
    break;  
  case cmdEditUndo:
    break;
  case cmdEditRedo:
    break;
  case cmdEditCut:
    cut();
    setChanged(true);
    break;
  case cmdEditCopy:
    copy();
    break;
  case cmdEditPaste:
    paste();
    setChanged(true);
    // hkt 0000000000000000000
    colorizeAfterChange(cmdEditPaste);
    break;
  case cmdEditSelectAll:
    selectAll();
    break;
  case cmdEditImport:
    break;
  case cmdLineBackward:
    previousLine();
    break;
  case cmdLineForward:
    nextLine();
    break;
  case cmdCharBackward:
    backwardChar();
    break;      
  case cmdCharForward:
    forwardChar();
    break;
  case cmdWordBackward:
    backwardWord();
    break;
  case cmdWordForward:
    forwardWord();
    break;
  case cmdGotoEOL:
    gotoEOL();
    break;
  case cmdGotoBOL:
    gotoBOL();
    break;
  case cmdGotoEOB:
    gotoEOB();
    break;
  case cmdGotoBOB:
    gotoBOB();
    break;
  case cmdPageBackward:
    backwardScreen();
    break;
  case cmdPageForward:
    forwardScreen();
    break; 
  case cmdSexprForward:
    break;
  case cmdSexprBackward:
    break;
  case cmdDelete:
    setChanged(true);
    break;
  case cmdKillSexpr:
    setChanged(true);
    break;
  case cmdIndent:
    setChanged(true);
    break;
  case cmdLispEval:
    evalText();
    break;
  case cmdSalEval:
    evalText();
    break;
  case cmdSymbolHelp:
    lookupHelpAtPoint();
    break;

  default:
    return false;
  }
  return true;
}

//
// Emacs Key Actions
//
#ifndef WINDOWS
#define emacsControl 1
#define emacsMeta 2
#define emacsControlMeta 3
#define emacsCommand 4
#define emacsCommandControl 5
#define emacsCommandMeta 6
#define emacsCommandControlMeta 7

#else

#define emacsControl 2
#define emacsMeta 4
#define emacsControlMeta 6
//all set to numbers too high.
#define emacsCommand 178
#define emacsCommandControl 179
#define emacsCommandMeta 180
#define emacsCommandControlMeta 181



#endif 

// some commands span more than one command invocation.

enum editAction 
  { actMoveLine = 1,
    actKillLine,
    actKillWord,
    actKillSexpr,
    actControlX
  };

int TextBuffer::isKeyAction (const KeyPress& key) {
  // return code if control, meta or command keys are down
  // ignoring Shift key

  int flag = 0;
  if ( isEmacsMode() ) {
    if ( key.getModifiers().isCtrlDown() )
      flag = emacsControl;
    if ( key.getModifiers().isAltDown() )
      flag |= emacsMeta;
#ifdef DARWIN
    if ( key.getModifiers().isCommandDown() )
      flag |= emacsCommand;
#endif
  }
  else {
    if ( key.getModifiers().isCommandDown() )
      flag |= emacsCommand;
  }

  if ((flag != 0) && key.getModifiers().isAnyMouseButtonDown() )
    flag = -1;

  return flag;
}

void TextBuffer::keyControlAction(const KeyPress& key) {
  int kcode = key.getKeyCode();
  int alias = 0;
  // this is unfortunate -- for some reason the control key in JUCE
  // causes the charcode to be uppercase! maybe its just the mac...
  switch (kcode) {
  case 'a' :
  case 'A' :
    gotoBOL();
    break;
  case 'b' :
  case 'B' :
    backwardChar();
    break;
  case 'd' :
  case 'D' :
    deleteChar(1);
    setChanged(true);
    colorizeAfterChange(cmdDelete);
    break;
  case 'e' :
  case 'E' :
    gotoEOL();
    break;
  case 'f' :
  case 'F' :
    forwardChar();
    break;
  case 'k' :
  case 'K' :
    killLine();
    setChanged(true);
    colorizeAfterChange(cmdKillLine);
    break;
  case 'n' :
  case 'N' :
    nextLine(); 
    break;
  case 'o' :
  case 'O' :
    openLine();
    setChanged(true);
    colorizeAfterChange(cmdOpenLine);
    break;
  case 'p' :
  case 'P' :
    previousLine();
    break;
  case 't' :     /** C-t for temp command testing  **/
  case 'T' :
    break;
  case 'v' :
  case 'V' :
    forwardScreen();
    break;
  case 'w' :
  case 'W' :
    cut();
    break;
  case 'x' :
  case 'X' :
    setAction(actControlX);
    break;
  case 'y' :
  case 'Y' :
    paste();
    setChanged(true);
    colorizeAfterChange(cmdEditPaste);
    break;
  default :
    keyIllegalAction(key);
  }
  if (alias != 0) {
    setChanged(true);
    TextEditor::keyPressed(KeyPress(alias));
  }
}

void TextBuffer::keyControlXAction (const KeyPress& key) {
  int kcode = key.getKeyCode();
 //rintf("Control-X: %s\n", key.getTextDescription().toUTF8() );
  switch (kcode) {
  case 'c':
  case 'C':
    ((EditorWindow*)getTopLevelComponent())->closeFile();
    break;
  case 'e':
  case 'E':
    evalText();
    break;
  case 'f':
  case 'F':
    ((EditorWindow*)getTopLevelComponent())->openFile();
    break;
  case 'h':
  case 'H':
    toggleHiliting();
    break;
  case 's':
  case 'S':
    ((EditorWindow*)getTopLevelComponent())->saveFile();
    break;
  case 'w':
  case 'W':
    ((EditorWindow*)getTopLevelComponent())->saveFileAs();
    break;
  case 'z' :
  case 'Z' :
    break;
  default :
    keyIllegalAction(key);
    break;
  } 
}

// this hair is really unfortunate -- for some reason the meta key
// actually changes the keycode from ascii to some weird unicode
// nonsense. need to track down if its juce or the mac thats
// resposible for this mess

#ifdef DARWIN
#define META_F 402
#define META_B 8747
#define META_D 8706
#define META_Q 339    // hkt
#define META_V 8730
#define META_SPACE 160
#define META_DOT 8805
#define META_LT 175
#define META_GT 728
#define META_L 172
#define META_U 0
#define META_C 231
#define KPAD_ENTER 13
#define ARROWL 28
#define ARROWR 29
#define ARROWU 30
#define ARROWD 31
#endif

#ifndef DARWIN && WINDOWS
#define META_F 102
#define META_B 98
#define META_D 100
#define META_Q 113          // hkt
#define META_V 118
#define META_SPACE 32
#define META_DOT 46
#define META_LT 60
#define META_GT 62
#define META_L 76
#define META_U 85
#define META_C 67
#define KPAD_ENTER 13
#define ARROWL 268435537
#define ARROWR 268435539
#define ARROWU 268435538
#define ARROWD 268435540
#endif

#ifdef WINDOWS
#define META_F 70
#define META_B 66
#define META_D 68
#define META_Q 81        // hkt
#define META_V 86
#define META_SPACE 32
#define META_DOT '.'
#define META_LT 60
#define META_GT 62
#define META_L 76
#define META_U 85
#define META_C 67
#define KPAD_ENTER 13
#define ARROWL 65573
#define ARROWR 65575
#define ARROWU 65574
#define ARROWD 65576
#endif

void TextBuffer::keyMetaAction(const KeyPress& key) {
  int kcode = key.getKeyCode();
   // printf("Meta key: %d\n", kcode );
  switch ( kcode ) {
  case META_F :
    forwardWord();
    break;
  case META_B :
    backwardWord();
    break;
  case META_Q :
    reformatCommentBlock();
    break;
  case META_L :
    changeCase(0);
    break;
  case META_U :
    changeCase(1);
    break;
  case META_C :
    changeCase(2);
    break;
  case META_V :
    backwardScreen();
    break;
  case META_LT :
    gotoBOB();
    break;
  case META_GT :
    gotoEOB();
    break;
  case META_D :
    killWord();
    setChanged(true);
    colorizeAfterChange(cmdKillWord);
    break;
  case META_SPACE :
    forwardDeleteChars( T(" \t\n") );
    setChanged(true);
    colorizeAfterChange(cmdKillWhite);
    break;
  default :
    keyIllegalAction(key);
    break;
  }
}

void TextBuffer::keyControlMetaAction(const KeyPress& key) {
  int kcode = key.getKeyCode();
  //printf("CtrlMeta: %d\n", kcode);
  switch (kcode) {
  case 'f' :
  case 'F' :

    forwardSexpr();
    break;
  case 'b' :
  case 'B' :
    backwardSexpr();
    break;
  case 'k' :
  case 'K' :
    killSexpr();
    setChanged(true);
    colorizeAfterChange(cmdKillSexpr);
    break;
  default:
    keyIllegalAction(key);
    break;
  }
}

void TextBuffer::keyCommandAction(const KeyPress& key) {
  int kcode = key.getKeyCode();
  syntaxID sid = syntaxSal;
  //printf("Command: %d\n", kcode );
  switch ( kcode ) {
  case 'a' :
  case 'A' :
    selectAll();
    break;
  case 'v' :
  case 'V' :
    paste(); 
    setChanged(true);
    colorizeAfterChange(cmdEditPaste);
    break;
  case 'c' :
  case 'C' :
    copy();
    break;
  case 'O' :
  case 'o' :
    ((EditorWindow*)getTopLevelComponent())->openFile();
    break;
  case 'N' :
  case 'n' :  
    // new window should probably default to sal mode. Maybe
    // Shift-Command-M for opening new Lisp buffer (?)
    sid=(key.getModifiers().isShiftDown()) ? syntaxLisp : syntaxSal;
    ((EditorWindow*)getTopLevelComponent())->newFile(sid);
    break;
  case 'R' :
  case 'r' :
    ((EditorWindow*)getTopLevelComponent())->revertFile();
    break;
  case 'S' :
  case 's' :
    ((EditorWindow*)getTopLevelComponent())->saveFile();
    break;
  case 'w' :
  case 'W' :
    ((EditorWindow*)getTopLevelComponent())->closeFile();
  case 'x' :
  case 'X' :
    cut();
    break;
  case 'e' :
  case 'E' :
  case KPAD_ENTER :
    evalText();
    break;
    // hkt 000000000000000000000000
  case ARROWL : // left 
    gotoBOL();
    break;
  case ARROWR : 
    gotoEOL();
    break;
  case ARROWU : // up
    gotoBOB();
    break;
  case ARROWD : 
    gotoEOB();
    break;

  default :
    keyIllegalAction(key);
    break;
  }
}
   
void TextBuffer::keyIllegalAction(const KeyPress& key) {
  String msg = T("Editor: ") + key.getTextDescription() +
    T(" is not a command.\n") ;
  getConsole()->printMessage(msg, ConsoleTheme::errorColor);
}

// the main key handling function. dispatches to other key handlers
// depending on what keys have been pressed

bool TextBuffer::isMatching() {return (matching > -1);}

void TextBuffer::startMatching(int pos1, int pos2) {
  setPoint(pos1);
  setColour(TextEditor::caretColourId, Colours::red);
  matching=pos2;
  startTimer(1000);
}

void TextBuffer::timerCallback() {
  stopMatching();
}

void TextBuffer::stopMatching() {
  if (matching != -1) {
    //printf("stopping matching\n");
    setPoint(matching);  
    setColour(TextEditor::caretColourId, Colours::black);
    matching=-1;
    if (isTimerRunning()) stopTimer();
  }
}

void TextBuffer::keyPressed (const KeyPress& key) {
  int keyCode, keyMod, flag, last;
  keyCode =  key.getKeyCode();
  keyMod = key.getModifiers().getRawFlags();
  flag = isKeyAction(key);
  // some commands like killLine need to know what the last command
  // was.  setAction() and storeAction() keep a memory of (one)
  // previous command.
  last = lastact;
  setAction(0);

  //printf("key=%d mod=%d\n", keyCode, keyMod);
  
  if ( isMatching() ) stopMatching();

  if (last == actControlX)
    keyControlXAction(key);
  else if (flag == 0) 
    switch (keyCode) {
    case '\t' :
      syntacticIndent();
      break;
    case '\n' :
    case '\r' :
      TextEditor::keyPressed(key);
      setChanged(true);
      colorizeAfterChange(cmdInsertLine);
      break;
#ifdef DARWIN
    case 5 :           // Help key
#else
    case 268435646 :   // F1
#endif
      lookupHelpAtPoint();
      break;
    case 8 :  // backspace
      TextEditor::keyPressed(key);
      setChanged(true);
      colorizeAfterChange(cmdBackspace);
      break;
    case 127 :  // delete
      TextEditor::keyPressed(key);
      setChanged(true);
      colorizeAfterChange(cmdDelete);
      break;
    case ')':
      TextEditor::keyPressed(key);
      if ( isParensMatching() )
	matchParens();
      break;
    case '}':
      TextEditor::keyPressed(key);
      if ( (syntaxId==syntaxSal) && isParensMatching() )
	matchParens();
      break;
      // hkt ???
    default :  // inserting text
      if (31<keyCode && keyCode<127) {
      TextEditor::keyPressed(key);
      setChanged(true);
      colorizeAfterChange(cmdInsertChar);
      }
      // hkt 00000000000000
      else TextEditor::keyPressed(key);

    }
  else if (flag < 1)
    keyIllegalAction(key);
  else {
    switch (flag) {
    case emacsControl :
      keyControlAction(key);
      break;
    case emacsMeta :
      keyMetaAction(key);
      break;
    case emacsCommand :
      keyCommandAction(key);
      break;
    case emacsControlMeta :
      keyControlMetaAction(key);
      break;
    default :
      keyIllegalAction(key);
    }
  }
  storeAction();
}
  
///
/// Emacs Cursor Motion : point() etc
///

int TextBuffer::point () {
  return getCaretPosition();
}

int TextBuffer::bufferMin () {
  return 0;
}

int TextBuffer::bufferMax() {
  // stupid but its faster than getText().length() !
  int cp1 = getCaretPosition(), cp2;
  setCaretVisible(false);
  setCaretPosition(BUFMAX);
  cp2=getCaretPosition();
  setCaretPosition(cp1);
  setCaretVisible(true);
  return cp2;
}

int TextBuffer::setPoint(int p) {
  setCaretPosition(p);
  return getCaretPosition();
}

int TextBuffer::incPoint(int i) {
  return setPoint(point() + i);
}

// hkt 0000000000000000000
int TextBuffer::gotoBOL () {
  int pos=findCharBackward('\n');
  //  printf("pos=%d\n", pos);
  if (pos<0) return gotoBOB();
  else return setPoint(pos);
}

int TextBuffer::gotoEOL () {
  int pos=findCharForward('\n');
  if (pos<0) return gotoEOB();
  else return setPoint(pos);
}
/*
int TextBuffer::gotoBOL () {
  static KeyPress key = KeyPress(KeyPress::homeKey);
  TextEditor::keyPressed(key);
  return point();
}

int TextBuffer::gotoEOL () {
  static KeyPress key = KeyPress(KeyPress::endKey);
  TextEditor::keyPressed(key);
  return point();
  }
*/

int TextBuffer::gotoBOB () {
  return setPoint( 0 );
}

int TextBuffer::gotoEOB () {
  return setPoint( BUFMAX );
}

int TextBuffer::forwardChar() {
  static KeyPress key = KeyPress(KeyPress::rightKey);
  TextEditor::keyPressed(key);
  return point();
}

int TextBuffer::backwardChar() {
  static KeyPress key = KeyPress(KeyPress::leftKey);
  TextEditor::keyPressed(key);
  return point();
}

bool TextBuffer::moveLine(int n) {
  // the main function for moving and accessing line text. moves N
  // lines forward or backward and positions point at BOL.  returns
  // true if line actually moved, else false. checking for false
  // allows code to stop line iteration without bounds checking.
  int old = gotoBOL();
  // warning: this code assumes setting point out of bounds is legal
  if (n < 0) {
    for (int i=n; i<0; i++) {
      incPoint(-1);
      gotoBOL();
    }
  }
  else if (n > 0) {
    for (int i=0; i<n; i++) {
      gotoEOL();
      incPoint(1);
    }
  }
  //printf("in move line, new position is %d.\n", point() );
  return  ( pointBOL() == old ) ? false : true;
}

void TextBuffer::nextLine() {
  // Emacs C-n  motion including goal column
  int col;
  if ( ! isLastAction(actMoveLine) )
    goalColumn=pointColumn();
  moveLine(1);
  col=pointColumn();
  if ( (col < goalColumn) && (pointLineLength() >= goalColumn) )
    incPoint(goalColumn-col);
  setAction(actMoveLine);
}

void TextBuffer::previousLine() {
  // Emacs C-p motion including goal column

  int col;
  if ( ! isLastAction(actMoveLine) )
    goalColumn=pointColumn();
  moveLine(-1);
  col=pointColumn();
  if ( (col < goalColumn) && (pointLineLength() >= goalColumn) )
    incPoint(goalColumn-col);
  setAction(actMoveLine);
}

/*
bool TextBuffer::moveLine(int n) {
  // the main function for moving and accessing line text. its based
  // on up/down key so that does not require buffer bounds checking to
  // determine if it can move or not.  function moves N lines forward
  // or backward if n<0 and positions point at BOL.  returns true if
  // line actually moved, else false. checking for false allows code
  // to stop line iteration without bounds checking.
  static KeyPress ukey = KeyPress(KeyPress::upKey);
  static KeyPress dkey = KeyPress(KeyPress::downKey);
  //  int old = point();
  int old = gotoBOL();
  // this code assumes up/down key always places cursor at BOL
  if (n < 0)
    for (int i=n; i<0; i++) TextEditor::keyPressed(ukey);
  else if (n > 0)
    for (int i=0; i<n; i++) TextEditor::keyPressed(dkey);
  //printf("in move line, new position is %d.\n", point() );
  return  ( pointBOL() == old ) ? false : true;
}

void TextBuffer::nextLine() {
  // Emacs C-n  motion including goal column
  static KeyPress key = KeyPress(KeyPress::downKey);
  int col;
  if ( ! isLastAction(actMoveLine) )
    goalColumn=pointColumn();
  TextEditor::keyPressed(key); 
  col=pointColumn();
  if ( (col < goalColumn) && (pointLineLength() >= goalColumn) )
    incPoint(goalColumn-col);
  setAction(actMoveLine);
}

void TextBuffer::previousLine() {
  // Emacs C-p motion including goal column
  static KeyPress key = KeyPress(KeyPress::upKey);
  int col;
  if ( ! isLastAction(actMoveLine) )
    goalColumn=pointColumn();
  TextEditor::keyPressed(key); 
  col=pointColumn();
  if ( (col < goalColumn) && (pointLineLength() >= goalColumn) )
    incPoint(goalColumn-col);
  setAction(actMoveLine);
}

*/

void TextBuffer::forwardScreen() {
  static KeyPress key = KeyPress(KeyPress::pageDownKey);
  TextEditor::keyPressed(key); 
}

void TextBuffer::backwardScreen() {
  static KeyPress key = KeyPress(KeyPress::pageUpKey);
  TextEditor::keyPressed(key); 
}

int TextBuffer::forwardSkipChars(String chars) {
  String text = getText();
  return skip_chars(text, chars, point(), text.length() );
}

int TextBuffer::forwardWord() {
  // Emacs M-f word motion. process buffer line by line scanning for
  // next word.
  String str;
  int pos, eol, len, loc;
  pos = point();
  eol = pointEOL();
  while (1) {
    len=eol-pos;
    //printf("line: pos=%d eol=%d len=%d,str='%s'\n",pos,eol,len,
    //       getTextSubstring(pos,eol).toUTF8());
    if (len > 0) {
      str = getTextSubstring(pos, eol);
      // skip over white space
      loc = skip_syntax(syntax->syntab, str, T("^w_"), 0, len);
      if (loc < len) {
	// found a word, scan to other side. dont have to search
	// further because a word cannot span a line break.
	loc = skip_syntax(syntax->syntab, str, T("w_"), loc, len);	
	return setPoint(pos+loc);
      }
    }
    if ( moveLine(1) ) {
      pos=point();
      eol=pointEOL();
      //printf("MOVED: point=%d eol=%d\n", pos,eol);
    }
    else break;
  }
  return setPoint(eol);
}

int TextBuffer::backwardWord() {
  // Emacs M-b word motion. search line by line scanning for next
  // word.
  String str;
  int pos, bol, len, loc;
  pos = point(); // pos is EXCLUSIVE upper bound
  bol = pointBOL();
  while (1) {
    len=pos-bol;
    if (len > 0) {
      str = getTextSubstring(bol,pos);
      loc = skip_syntax(syntax->syntab, str, T("^w_"), len-1, -1);
      if (loc > -1) {
	loc = skip_syntax(syntax->syntab, str, T("w_"), loc, -1);
	// loc is now -1 or on nonword
	return setPoint(bol+loc+1);
      }
    }
    if ( moveLine(-1) ) {
      bol=point();
      pos=pointEOL();
    }
    else break;
  }
  return setPoint(bol);
}

int TextBuffer::forwardSexpr() {
  // Emacs C-M-f sexpr motion. access to buffer string is constrained
  // to the forward text up to but not including the next top level
  // sexpr in the buffer (because, by definition, the current sexpr
  // cant extend beyond that)

  String text = forwardTopLevelText();
  int typ, loc, pos=point(), end=text.length();

  typ = scan_sexpr(syntax->syntab, text, 0, end, SCAN_CODE, &loc);
  if (typ == SCAN_UNLEVEL)
    getConsole()->printMessage(T("Editor C-M-f:\nCan't move forward past end of list.\n"),
			       ConsoleTheme::warningColor);
  else if (typ == SCAN_UNMATCHED)
    getConsole()->printMessage(T("Editor C-M-f:\nForward unmatched delimiter.\n"),
			       ConsoleTheme::warningColor);
  else
    setPoint(pos+loc);
  return point();
}

int TextBuffer::backwardSexpr() {
  String text = backwardTopLevelText();
  int typ, loc, pos=point(), end=text.length();

  typ = scan_sexpr(syntax->syntab, text, end-1, -1, SCAN_CODE, &loc);
  if (typ == SCAN_UNLEVEL)
    getConsole()->printMessage(T("Editor C-M-b:\nCan't move backward past start of list.\n"),
			       ConsoleTheme::warningColor);
  else if (typ == SCAN_UNMATCHED)
    getConsole()->printMessage(T("Editor: C-M-b:\nBackward unmatched delimiter.\n"),
			       ConsoleTheme::warningColor);
  else 
    setPoint(pos-end+loc+1);
  //printf("char at loc+1='%c'\n", text[loc+1]);
  return point();
}

//
// Information. these need to be fast and NOT change point.
//

bool TextBuffer::isBOB() {
  return ( point() == bufferMin() ) ? true : false;
}

bool TextBuffer::isEOB() {
  return ( point() == bufferMax() ) ? true : false;
}

bool TextBuffer::isBOL() {
  if ( isBOB() ) return true;
  return ( point() == pointBOL() ) ? true : false;
}

bool TextBuffer::isEOL() {
  if ( isEOB() ) return true;
  return ( point() == pointEOL() ) ? true : false;
}

int TextBuffer::pointBOL () {
  static KeyPress key = KeyPress(KeyPress::homeKey);
  int here = getCaretPosition();
  setCaretVisible(false);
  int there=gotoBOL();
  setCaretPosition(here);
  setCaretVisible(true);
  return there;
}

int TextBuffer::pointEOL() {
  static KeyPress key = KeyPress(KeyPress::endKey);
  int here = getCaretPosition();
  setCaretVisible(false);
  int there=gotoEOL();
  setCaretPosition(here);
  setCaretVisible(true);
  return there;
}

/*
int TextBuffer::pointBOL () {
  static KeyPress key = KeyPress(KeyPress::homeKey);
  int here = getCaretPosition(), there;
  setCaretVisible(false);
  TextEditor::keyPressed(key);
  there=getCaretPosition();
  setCaretPosition(here);
  setCaretVisible(true);
  return there;
}
int TextBuffer::pointEOL() {
  static KeyPress key = KeyPress(KeyPress::endKey);
  int here = getCaretPosition(), there;
  setCaretVisible(false);
  TextEditor::keyPressed(key);
  there=getCaretPosition();
  setCaretPosition(here);
  setCaretVisible(true);
  return there;
}
*/

int TextBuffer::pointColumn() {
  return point() - pointBOL();
}

int TextBuffer::pointLineLength () {
  return pointEOL() - pointBOL() ;
}

//
// char and string access
//

String TextBuffer::forwardTopLevelText() {
  // return all the text starting at point() up to, but not including,
  // the next top-level line that begins after at least one non-white
  // line has been encountered. in other words, a toplevel line that
  // is preceded only by whitespace will not stop the forward
  // exclusive search (else return text would just be whitespace.)
  setCaretVisible(false);
  setScrollToShowCursor(false);
  String line, text = String::empty;
  int here=point();
  int pos=here;
  int eol=pointEOL();
  bool nonw=false; // non-white line flag

  for (int i=0; ; i++) {
    if (eol > pos) {
      line = getTextSubstring(pos, eol);
      if ( syntax->isWhiteBetween(line, 0, line.length()) )
	text += line;
      else if ( i == 0) {
	// collect first line no matter what
	text += line;
	nonw=true;
      }
      else if ( nonw && syntax->isTopLevel(line))
	break;
      else {
	text += line;
	nonw=true;
      }
    }
    text += T("\n");
    if ( moveLine(1) ) {
      pos=point();
      eol=pointEOL();
    }
    else {
      break;
    }
  }
  setPoint(here);
  setCaretVisible(true);
  setScrollToShowCursor(true);
  return text;
}

String TextBuffer::backwardTopLevelText() {
  // return all the text from point() back to the start of the nearest
  // top-level form before it
  setCaretVisible(false);
  setScrollToShowCursor(false);
  String line, text = String::empty;
  String he;
  int here=point();
  int pos=here;
  int bol=pointBOL();

  for (int i=0; ; i++) {
    line = getTextSubstring(bol, pos);
    if ( i == 0 ) 
      text=line;
    else
      text = line + T("\n") + text;
    if ( syntax->isTopLevel(line) || ! moveLine(-1) )
      break;
    else {
      bol=point();
      pos=pointEOL();
    }
  }
  setPoint(here);
  setCaretVisible(true);
  setScrollToShowCursor(true);
  return text;
}

///
/// Selection
///

void TextBuffer::selectAll() {
  // unfortunately JUCE moves caret to end of selection, the opposite of emacs.
  if ( ! isEmpty() ) {
    setHighlightedRegion( bufferMin(), BUFMAX );
  }
}

void TextBuffer::mouseDoubleClick (const MouseEvent &e) {
  // Call underlying method and then update point.
  int a, b;
  //if (e.getNumberOfClicks() == 2) {
    String it = getTextSubstring(point(),point()+1);
    switch (it[0]) {
    case '(' :
    case '{' :
    case '"' :
      a=point();
      b=forwardSexpr();
      if (b>a) setHighlightedRegion(a,b-a);
      break;
    case ')' :
    case '}' :
      b=incPoint(1);
      a=backwardSexpr();
      if (a<b) setHighlightedRegion(a,b-a);
      break;
    default:
      TextEditor::mouseDoubleClick(e);
      break;
    }
    //}
    //else 
    //  TextEditor::mouseDoubleClick(e);
}  	

void TextBuffer::matchParens() {
  int b=point();
  int a=backwardSexpr();
  if (a<b) {
    startMatching(a,b);
    //    setCaretPosition(a);
    //    setColour(TextEditor::caretColourId, Colours::red);
    //    matching=b;
  }
}

///
/// Evaluation
///

int TextBuffer::evalText() {
  String cmdname;

  switch (syntaxId) {
  case syntaxSal :
    cmdname=T("Execute");
    break;
  case syntaxLisp :
    cmdname=T("Eval");
    break;
  default :
    return 0;
  }

  bool region=(getHighlightedRegionLength() > 0);
  String text;

  if ( region )
    text=getHighlightedText();
  else
    text=backwardTopLevelText();

  int typ=SCAN_EMPTY, end=text.length(), pos=end-1, old=pos;

  // parse backwards 1 sexpr for lisp or to toplevel for Sal
  // if region parse whole thing
  while (pos>-1) {
    typ = scan_sexpr(syntax->syntab, text, old, -1, SCAN_CODE, &pos);
    if ( (typ<=SCAN_EMPTY) || ((syntaxId==syntaxLisp) && !region) )
      break;
    old=pos;
  }

  if (typ==SCAN_EMPTY) {
    getConsole()->printWarning(cmdname + T(": nothing selected.\n"));
    return 0;
  }

  if (typ<SCAN_EMPTY) {
    int l1, l2;
    getConsole()->printError( T(">>> ") + cmdname +
				     T(": unbalanced expression:\n"));
    // print line containing error with ^ marking offending position
    for (l2=old+1; l2<end; l2++)
      if (text[l2]=='\n') break;
    for (l1=old; l1>-1; l1--)
      if (text[l1]=='\n') break;
    l1++;
    getConsole()->printMessage( text.substring(l1,l2), ConsoleTheme::errorColor);
    getConsole()->terpri();
    String mark=String::empty;
    for (int i=l1; i<old; i++)
      mark += T(" ");
    mark += T("^");
    getConsole()->printMessage( mark, ConsoleTheme::errorColor);
    getConsole()->terpri();
    return 0;
  }
  if (syntaxId==syntaxSal)
    getConsole()->consoleEval(text, true, region);
  else
    getConsole()->consoleEval(text.substring(pos+1), false, region);
  return 0;
}

/// 
/// Editing
///

int TextBuffer::openLine() {
  // C-o new line does not change point
  int here = point();
  insertTextAtCursor(T("\n"));
  return setPoint(here);
}

int TextBuffer::insertText (String str) {
  insertTextAtCursor(str);
  return point();
}

void TextBuffer::deleteRegion(int from, int to) {
  // delete chars between from and to (exclusive), do not update
  // clipboard
  if (to > from) {
    setHighlightedRegion(from, to-from);
    insertTextAtCursor(String::empty);
  }
}

// Emacs Killing

void TextBuffer::updateClipboardWithKill(String kill, int cmd) {
  // repeating kill commands ADDS kills to clipboard.
  if ( isLastAction(cmd) )
    kill = SystemClipboard::getTextFromClipboard() + kill;
  SystemClipboard::copyTextToClipboard(kill);
}

void TextBuffer::killWord() {
  int from=point();
  int to=forwardWord();
  if (to > from) {
    String text = getTextSubstring(from,to);
    deleteRegion(from, to);
    updateClipboardWithKill(text,actKillWord);
    setAction(actKillWord);
  }
}

void TextBuffer::killSexpr() {
  int from=point();
  int to=forwardSexpr();
  if (to > from) {
    String text= getTextSubstring(from,to);
    deleteRegion(from,to);
    updateClipboardWithKill(text,actKillSexpr);
    setAction(actKillSexpr);
  }
}

void TextBuffer::killLine() {
  // Emacs C-k line killing from point forward. kills to EOL+1 if line
  // contains only white space after point
  int from=point();
  int to=pointEOL();
  String text=getTextSubstring(from,to);
  if ( text == String::empty || text.containsOnly(T(" \t")) ) {
       text += T("\n");
       to++;
  }
  deleteRegion(from,to);
  updateClipboardWithKill(text,actKillLine);
  setAction(actKillLine) ;
}

int TextBuffer::deleteChar (int num) {
  static KeyPress dkey = KeyPress(KeyPress::deleteKey);
  static KeyPress bkey = KeyPress(KeyPress::backspaceKey);
  if (num > 0)
    for (int i = 0; i < num; i++)
      TextEditor::keyPressed(dkey); 
  else
    for (int i = num; i < 0; i++)
      TextEditor::keyPressed(bkey); 
  return point(); 
}

int TextBuffer::forwardDeleteChars (String chars) {
  int pos = point(), top;
  top=forwardSkipChars(chars);  // top now non-white or eob
  if (top > pos) {
    setHighlightedRegion(pos,top-pos);
    insertTextAtCursor(String::empty);    
  }
  return point();
}

int TextBuffer::currentIndent() {
  int bol=pointBOL();
  int eol=pointEOL();
  String txt=getTextSubstring(bol,eol);
  return skip_chars(txt, T(" \t"), 0, txt.length());
}

int TextBuffer::indentToColumn(int col) {
  // reindent current line so that there are col white spaces before
  // the first non-white char in line

  int bol=pointBOL();
  int top=bol+currentIndent();  // current pos of first non-white or eol
  int loc=bol+col;  // goal pos for indentation

  setCaretVisible(false);
  setScrollToShowCursor(false);

  if ( loc < top) {
    setPoint(loc);
    deleteChar(top-loc);
  }
  else if (loc > top) {
    // weird  things happen if line is last line in buffer w/out eol
    // setPoint(top);    // should work but doesnt if eob

    //    if (top == bufferMax() )
    //      setPoint(top-1);
    //    else 
      setPoint(top); 
    // BUG: inserting text causes cursor line to reposition itself!
    for (int i=top; i<loc; i++) 
      insertTextAtCursor(T(" "));
  }
  else setPoint(loc);

  setCaretVisible(true);
  setScrollToShowCursor(true);

  return 0;
}

void TextBuffer::syntacticIndent() {
  int bol, eol, col, pos, len;
  String txt;
  bol=gotoBOL();
  if ( bol == bufferMin() ) 
    col=0;
  else {
    txt=backwardTopLevelText();
    len=txt.length();
    pos=len-1; // search start
    // add current line to end of string (after search start)
    eol=gotoEOL();
    if ( eol > bol ) {
      txt += getTextSubstring(bol,eol);
      len += (eol-bol);
    }
    col=syntax->getIndent( txt, -1, len, pos);
  }
  indentToColumn(col);
  colorizeAfterChange(cmdIndent); // recolor current line
}

///
/// Non commands
///

ConsoleWindow* TextBuffer::getConsole() {
  return ((GraceApp *)GraceApp::getInstance())->getConsole();
}

void TextBuffer::colorize (int from, int to, bool force) {
  // FIX: recoloring should only happen in the visible region of
  // buffer but i dont see anyway to get this information from the
  // viewpoint
  String text = getTextSubstring(from, to);
  int len = text.length();
  int here = point(), pos = 0, start, end;
  String expr;
  scanresult typ;
  hiliteID hilite;
  Colour color, normal=syntax->hilites[hiliteNone];
  static KeyPress dkey = KeyPress(KeyPress::deleteKey);

  // offset is the starting position of text string in buffer.
  setCaretVisible(false);
  setScrollToShowCursor(false);
  //printf("hiliting %d to %d...\n", from, to);
  while (pos < len) {
    typ=parse_sexpr(syntax->syntab,text,-1,len,1,SCAN_COLOR,&pos,&start,&end);
    hilite=hiliteNone;
    if (typ>0) {
      if (typ==SCAN_TOKEN) {
	hilite=syntax->getHilite(text, start, end);
      }
      else if (typ==SCAN_COMMENT) {
	hilite=hiliteComment;
      }
      else if (typ==SCAN_STRING) {
	hilite=hiliteString;
      }
      if (hilite>hiliteNone || force) {
	// this is REALLY gross!
	expr=text.substring(start,end);
	color=syntax->hilites[hilite];
	setPoint(from+start);
	setHighlightedRegion(from+start, end-start);
	if (0) {
	  printf("SCAN: start=%d,end=%d string='%s'\n",
		 start,end,expr.toUTF8());
	  printf("BUFF: from=%d,to=%d text to replace: '%s'\n",
		 from+start, from+end,
		 getTextSubstring(from+start, from+end).toUTF8());
	}
	TextEditor::keyPressed(dkey);
	setColour(TextEditor::textColourId, color);
	insertTextAtCursor(expr);
	setColour(TextEditor::textColourId, normal);
      }
    }
  }
  setPoint(here);
  setCaretVisible(true);
  setScrollToShowCursor(true);
  //printf("...done!\n");
}

void TextBuffer::colorizeAll() {
  if (!isHiliting()) return;
  colorize(bufferMin(), bufferMax(), false );
}

void TextBuffer::colorizeAfterChange(int cmd) {
  if (!isHiliting()) return;
  int loc=point(), bol=pointBOL(), eol=pointEOL();
  int bot=bol, top=eol;
  switch (cmd) {
  case cmdEditPaste :  
    // point is after pasted material. colorize from bol before
    // previous point to eol AFTER pasted
    top=eol;
    bot=loc-SystemClipboard::getTextFromClipboard().length();
    setPoint(bot);
    bot=pointBOL();
    setPoint(loc);
    break;
  case cmdOpenLine : // include new line in recolor
    if ( moveLine(1) ) {
      top=pointEOL();
      setPoint(loc);
    }
  case cmdInsertLine : // include previous line in recolor
    if ( moveLine(-1) ) {
      bot=point();
      setPoint(loc);
      }
    break;
  case cmdIndent :   // colorize current line
    bot=bol;
    top=eol;
    break;
  default :
    break;
  }
  if (bot==top) return;
  colorize(bot,top,true);
}

//
// Flag twidding.
//

bool TextBuffer::isHiliting() {
  return !testFlag(hiliteoff);
}

void TextBuffer::toggleHiliting() {
  if (syntaxId==syntaxText) return;
  toggleFlag(hiliteoff);
  if ( isHiliting() )
    colorizeAll();
  else {
    String text=getText();
    setText(String::empty);
    setColour(TextEditor::textColourId, 
	      syntax->hilites[hiliteNone]);
    setText(text);
  }
}

bool TextBuffer::isParensMatching() {
  return !testFlag(parensoff);
}

void TextBuffer::toggleParensMatching () {
  toggleFlag(parensoff); 
  return;
}

bool TextBuffer::isChanged() {
  return testFlag(needsave);
}

void TextBuffer::setChanged(bool b) {
  if (b) setFlagOn(needsave); 
  else setFlagOff(needsave); 
  return;
}

void TextBuffer::toggleReadOnly() {
  toggleFlag(readonly);
  setReadOnly(testFlag(readonly));
}

///
/// Font twiddling.
///

void TextBuffer::setFontType(const String name) {
  Font font=getFont();
  font.setTypefaceName( name );
  applyFontToAllText(font);
}

void TextBuffer::setFontSize( float size ) {
  GracePreferences* p=GracePreferences::getInstance();
  Font font=getFont();
  font.setHeight(size);
  applyFontToAllText(font);
  p->setEditorFontSize(size);
}

float TextBuffer::getFontSize(  ) {
  return getFont().getHeight();
}

void TextBuffer::lookupHelpAtPoint() {
  bool region=(getHighlightedRegionLength() > 0);
  String text;

  if ( region )
    text=getHighlightedText();
  else {
    int pos=point();
    int bol=pointBOL();
    text=getTextSubstring(bol, pointEOL() );
    int len=text.length();
    int beg=skip_syntax(syntax->syntab, text, T("w_"), pos-bol-1, -1);
    int end=skip_syntax(syntax->syntab, text, T("w_"), pos-bol, len);
    //    printf("beg=%d, end=%d\n", beg+1, end);
    if (beg+1==end) return;
    text=text.substring(beg+1,end);
  }
  //  printf("lookup help for %s\n", text.toUTF8() );
  SynTok* tok=syntax->getSynTok(text);
  if (tok == (SynTok *)NULL) return;
  String file=T("doc/sal/help/") + text + T(".sal");
  File help=getGraceResourceDirectory().getChildFile(file);
  if ( help.existsAsFile() ) {
    new EditorWindow(syntaxSal, 
		     (TextBuffer::load | TextBuffer::nosave), 
		     help.getFullPathName(),
		     ( T("Help for ") + text));
  }
}

void TextBuffer::reformatCommentBlock () {
  // reformats toplevel comment block
  setCaretVisible(false);
  int here = gotoBOL();
  int save=here;
  int beg=-1, end=-1;
  String c;
  // find start and end of block;
  while (1) {
    c=getTextSubstring(here, here+1);
    if (c == T(";")) {
      beg=here;
      if ( moveLine(-1) )
	here=point();
      else break;
    }
    else break;
  }
  if (beg==-1) {
    setCaretVisible(true);
    return;
  }
  here=save;
  while (1) {
    c=getTextSubstring(here, here+1);    
    if (c == T(";")) {
      end=here;
      if ( moveLine(1) )
	here=point();
      else break;
    }
    else break;
  }
  setPoint(end);
  end=pointEOL();
  String block=getTextSubstring(beg,end);
  //printf("comment block='%s'\n",block.toUTF8());
  deleteRegion(beg,end);
  setPoint(beg);

  Colour comment=syntax->hilites[hiliteComment];
  Colour regular=syntax->hilites[hiliteNone];
  setColour(TextEditor::textColourId, comment);
  int len=block.length();
  int col=0;
  String tok;
  int num=0;
  for (int i=0;i<len;i++)
    if (block[i]==';') num++;
    else break;
  beg=end=0;
  while (1) {
    beg=skip_syntax(syntax->syntab, block, T("-<"), end, len); 
    if (beg==len) break;
    // beg is now on nonwhite non comment.
    end=skip_syntax(syntax->syntab, block, T("^-<"), beg, len); 
    tok=block.substring(beg,end);
    if ( (col + tok.length() + 1) > 70) {
      insertTextAtCursor(T("\n"));
      col=0;
    }
    if (col==0) {
      for (int i=0;i<num;i++)
	insertTextAtCursor(T(";"));
      col+=num;
    }
    insertTextAtCursor(T(" "));
    insertTextAtCursor(tok);
    col+=tok.length()+1;
  }

  setColour(TextEditor::textColourId, regular);
  setCaretVisible(true);
}

void TextBuffer::changeCase(int flag) {
  int beg=point();
  int end=forwardWord();
  String text=getTextSubstring(beg, end);
  if (text==String::empty) return;
  deleteRegion(beg,end);
  if (flag==0)
    insertTextAtCursor(text.toLowerCase());
  else if (flag==1)
    insertTextAtCursor(text.toUpperCase());
  else if (flag==2) {
    int len=text.length();
    // get first alphachar 
    int loc=skip_syntax(syntax->syntab, text, T("^w"), 0, len);	
    insertTextAtCursor(text.substring(0,loc));
    if (loc<len) {
      insertTextAtCursor(text.substring(loc,loc+1).toUpperCase());
      insertTextAtCursor(text.substring(loc+1,len));
    }
  }
  beg=point();
  colorizeAfterChange(cmdIndent); // recolorize whole line for now..
  setPoint(beg);
}

// hkt 0000000000000000

#define CHUNKSIZE 128

int TextBuffer::findCharForward(char c) {
  int pos=point();
  int len;
  int loc=-1;
  String str;
  // potential gocha: this works only because its not an error to pass
  // getTextSubstring an index that is out of range.
  str = getTextSubstring(pos, pos+CHUNKSIZE);
  len = str.length();
  while (1) {
    if (len==0) break;
    for (int i=0; i<len; i++)
      if (str[i] == c) {
	loc=pos+i;
	break;
      }
    if (loc>-1) break;
    pos += len;
    str = getTextSubstring(pos, pos+CHUNKSIZE);
    len = str.length();
  }
  return loc;
}

int TextBuffer::findCharBackward(char c) {
  int pos=point();
  int len;
  int loc=-1;
  String str;
  // potential gocha: this works only because its not an error to pass
  // getTextSubstring an index that is out of range.
  str = getTextSubstring(pos-CHUNKSIZE, pos);
  len = str.length();
  while (1) {
    if (len==0) break;
    for (int i=len-1; i>-1; i--)
      if (str[i] == c) {
	loc=pos-(len-i)+1;
	break;
      }
    if (loc>-1) break;
    pos -= len;
    str = getTextSubstring(pos-CHUNKSIZE, pos);
    len = str.length();
  }
  return loc;
}
