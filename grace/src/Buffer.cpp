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
//#include "Console.h"

/*
Unresolved problems:
JUCE Home/End and Up/Down keys dont search for true BOL/EOL conditions
so cursor motion fails on wrapped lines...
*/

#define BUFMAX 0xFFFFFFF

TextBuffer::TextBuffer (String pathname, syntaxID id, TopLevelWindow *pwind) 
 : TextEditor(pathname) {
  changed=false;
  setWantsKeyboardFocus(true);
  setMultiLine(true);
  setReturnKeyStartsNewLine(true);
  setCaretPosition(0);
  setPoint(0);
  initSyntax(id);
  parentWindow = pwind;
  editfont = Font(Font::getDefaultMonospacedFontName(), 17.0f, Font::plain );
  // adding a TextChanged listener doesnt work because JUCE calls the
  // listener even if there is only cursor motion!
  // addListener( new TextBufferListener( this ) );
 
  //
}

void TextBuffer::initSyntax (syntaxID id) {
  // initialize buffers' syntax table for the appropriate editing mode
  syntaxId=id;
  hiliting=(id==syntaxText) ? false : true;
  switch (id) {
  case syntaxSal :
    syntax= new SalSyntax();
    break;
  case syntaxLisp :
    syntax= new LispSyntax();
    break;
  case syntaxText :
  default : 
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
    cmdNew,
    cmdOpen,
    cmdSave,
    cmdSaveAs,
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
  
  commands.addArray (ids, sizeof (ids) / sizeof (ids [0]));
}

void TextBuffer::getCommandInfo (const CommandID commandID, ApplicationCommandInfo& result)
{
  const String fileCategory (T("File"));
  const String preferencesCategory (T("Preferences"));
  const String navigationCategory (T("Navigation"));
  const String editingCategory (T("Editing"));
  const String optionsCategory (T("Options"));
  PopupMenu fontsMenu;
  
  switch (commandID)
    {
    case cmdNew:
      result.setInfo (T("New Editor..."), String::empty, fileCategory, 0);
      result.addDefaultKeypress (T('N'), ModifierKeys::commandModifier);
      break;
    case cmdOpen:
      result.setInfo (T("Open"), String::empty, fileCategory, 0);
      result.addDefaultKeypress (T('O'), ModifierKeys::commandModifier);
      break;
    case cmdSave:
      result.setInfo (T("Save"), String::empty, fileCategory, 0);
      result.addDefaultKeypress (T('S'), ModifierKeys::commandModifier);
      break;
    case cmdSaveAs:
      result.setInfo (T("Save As..."), String::empty, fileCategory, 0);
      result.addDefaultKeypress (T('S'), ModifierKeys::commandModifier || ModifierKeys::shiftModifier);
      break;
    case cmdClose:
      result.setInfo (T("Close"), String::empty, fileCategory, 0);
      result.addDefaultKeypress (T('W'), ModifierKeys::commandModifier);
      break;
    case cmdUndo:
      result.setInfo (T("Undo"), String::empty, editingCategory, 0);
      result.addDefaultKeypress (T('Z'), ModifierKeys::commandModifier);
      break;
    case cmdRedo:
      result.setInfo (T("Redo"), String::empty, editingCategory, 0);
      result.addDefaultKeypress (T('Z'), ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
      break;
    case cmdCut:
      result.setInfo (T("Cut"), String::empty, editingCategory, 0);
      result.addDefaultKeypress (T('X'), ModifierKeys::commandModifier);
      break;
    case cmdCopy:
      result.setInfo (T("Copy"), String::empty, editingCategory, 0);
      result.addDefaultKeypress (T('C'), ModifierKeys::commandModifier);
      break;
    case cmdPaste:
      result.setInfo (T("Paste"), String::empty, editingCategory, 0);
      result.addDefaultKeypress (T('V'), ModifierKeys::commandModifier);
      break;
    case cmdSelectAll:
      result.setInfo (T("Select All"), String::empty, editingCategory, 0);
      result.addDefaultKeypress (T('A'), ModifierKeys::commandModifier);
      break;
    case cmdOptions:
      result.setInfo (T("Preferences"), String::empty, preferencesCategory, 0);
      break;
    case cmdFonts:
      result.setInfo (T("Font"), String::empty, preferencesCategory, 0);      
      break;

    case cmdLineBackward:
      result.setInfo (T("Move up line"), String::empty, navigationCategory, 0);
      break;
    case cmdLineForward:
      result.setInfo (T("Move down line"), String::empty, navigationCategory, 0);
      break;
    case cmdCharBackward:
      result.setInfo (T("Move back char"), String::empty, navigationCategory, 0);
      break;      
    case cmdCharForward:
      result.setInfo (T("Move forward char"), String::empty, navigationCategory, 0);
      break;
    case cmdWordBackward:
      result.setInfo (T("Move backward word"), String::empty, navigationCategory, 0);
      break;
    case cmdWordForward:
      result.setInfo (T("Move forward word"), String::empty, navigationCategory, 0);
      break;
    case cmdGotoEOL:
      result.setInfo (T("Move to end of line"), String::empty, navigationCategory, 0);
      break;
    case cmdGotoBOL:
      result.setInfo (T("Move to beginning of line"), String::empty, navigationCategory, 0);
      break;
    case cmdGotoEOB:
      result.setInfo (T("Move to end of document"), String::empty, navigationCategory, 0);
      break;
    case cmdGotoBOB:
      result.setInfo (T("Move to beginning of document"), String::empty, navigationCategory, 0);
      break;
    case cmdPageBackward:
      result.setInfo (T("Move page up"), String::empty, navigationCategory, 0);
      break;
    case cmdPageForward:
      result.setInfo (T("Move page down"), String::empty, navigationCategory, 0);
      break; 
    case cmdSexprForward:
      result.setInfo (T("Move to end of sexpr"), String::empty, navigationCategory, 0);
      break;
    case cmdSexprBackward:
      result.setInfo (T("Move to beginning of sexpr"), String::empty, navigationCategory, 0);
      break;

    case cmdDelete:
      result.setInfo (T("Delete backward"), String::empty, editingCategory, 0);
      break;
    case cmdKillSexpr:
      result.setInfo (T("Delete to end of sexpr"), String::empty, editingCategory, 0);
      break;
    case cmdIndent:
      result.setInfo (T("Indent"), String::empty, editingCategory, 0);
      break;
    
    case cmdEval:
      result.setInfo (T("Eval"), String::empty, editingCategory, 0);
      break;
    default:
      break;
      
    }
}


bool TextBuffer::perform (const InvocationInfo& info)
{
  switch (info.commandID) 
    {
    case cmdNew:
      newFile(syntaxSal);
      break;
    case cmdOpen:
      openFile();
      break;
    case cmdSave:
      saveFile();
      break;
    case cmdSaveAs:
      saveFileAs();
      break;
    case cmdUndo:
      break;
    case cmdRedo:
      break;
    case cmdCut:
      cut();
      break;
    case cmdCopy:
      copy();
      break;
    case cmdPaste:
      paste();
      break;
    case cmdSelectAll:
      selectAll();
      break;
      /* could open dialogue window, etc for these */
    case cmdOptions:
      break;
    case cmdFonts:
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
      break;
    case cmdKillSexpr:
      break;
    case cmdIndent:
      break;
    case cmdEval:
      evalLastSexpr();
      break;
    default:
      return false;
    }
  return true;
}


//
// Emacs Key Actions
//

#define emacsControl 1
#define emacsMeta 2
#define emacsControlMeta 3
#define emacsCommand 4
#define emacsCommandControl 5
#define emacsCommandMeta 6
#define emacsCommandControlMeta 7

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
  if ( key.getModifiers().isCtrlDown() )
    flag = emacsControl;
  if ( key.getModifiers().isAltDown() )
    flag |= emacsMeta;
  if ( key.getModifiers().isCommandDown() )
    flag |= emacsCommand;
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
    colorizeAfterChange(cmdPaste);
    break;
  default :
    keyIllegalAction(key);
  }
  if (alias != 0) {
    TextEditor::keyPressed(KeyPress(alias));
  }
}

void TextBuffer::keyControlXAction (const KeyPress& key) {
  int kcode = key.getKeyCode();
  //printf("Control-X: %s\n", key.getTextDescription().toUTF8() );
  switch (kcode) {
  case 'e':
  case 'E':
    evalLastSexpr();
    break;
  case 'f':
  case 'F':
    openFile();
    break;
  case 'h':
  case 'H':
    toggleHiliting();
    break;
  case 's':
  case 'S':
    saveFile();
    break;
  case 'w':
  case 'W':
    saveFileAs();
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

#define META_F 402
#define META_B 8747
#define META_D 8706
#define META_V 8730
#define META_SPACE 160
#define META_DOT 8805
#define META_LT 175
#define META_GT 728
// this is unfortunate -- juce maps keypad enter to return :(
#define KPAD_ENTER 13

void TextBuffer::keyMetaAction(const KeyPress& key) {
  int kcode = key.getKeyCode();
  //printf("Meta key: %d\n", kcode );
  switch ( kcode ) {
  case META_F :
    forwardWord();
    break;
  case META_B :
    backwardWord();
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
  //printf("CtrlMeta: %d\n", keycode);
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
    colorizeAfterChange(cmdPaste);
    break;
  case 'c' :
  case 'C' :
    copy();
    break;
  case 'O' :
  case 'o' :
    openFile();
    break;
  case 'N' :
  case 'n' :  
    // new window should probably default to sal mode. Maybe
    // Shift-Command-M for opening new Lisp buffer (?)
    sid=(key.getModifiers().isShiftDown()) ? syntaxLisp : syntaxSal;
    newFile(sid);
    break;
  case 'R' :
  case 'r' :
    revertFile();
    break;
  case 'S' :
  case 's' :
    saveFile();
    break;
  case 'x' :
  case 'X' :
    cut();
    break;
  case 'e' :
  case 'E' :
  case KPAD_ENTER :
    evalLastSexpr();
    break;
  default :
    keyIllegalAction(key);
    break;
  }
}
   
void TextBuffer::keyIllegalAction(const KeyPress& key) {
  String msg = T("Editor: ") + key.getTextDescription() +
    T(" is not a command.\n") ;
  getConsole()->consolePrint(msg, ConsoleTheme::errorColor);
}

// the main key handling function. dispatches to other key handlers
// depending on what keys have been pressed

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
    default :  // inserting text
      if (31<keyCode && keyCode<127) {
      TextEditor::keyPressed(key);
      setChanged(true);
      colorizeAfterChange(cmdInsertChar);
      }
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
  
void TextBuffer::mouseDown (const MouseEvent &e) {
  // Call underlying method and then update point.
  TextEditor::mouseDown(e);
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
    getConsole()->consolePrint(T("Editor C-M-f:\nCan't move forward past end of list.\n"),
			       ConsoleTheme::warningColor);
  else if (typ == SCAN_UNMATCHED)
    getConsole()->consolePrint(T("Editor C-M-f:\nForward unmatched delimiter.\n"),
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
    getConsole()->consolePrint(T("Editor C-M-b:\nCan't move backward past start of list.\n"),
			       ConsoleTheme::warningColor);
  else if (typ == SCAN_UNMATCHED)
    getConsole()->consolePrint(T("Editor: C-M-b:\nBackward unmatched delimiter.\n"),
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

///
/// Evaluation
///

int TextBuffer::evalLastSexpr() {
  switch (syntaxId) {
  case syntaxLisp :
  case syntaxSal :
    break;
  default :
    return 0;
  }

  String text=backwardTopLevelText();
  int typ=SCAN_EMPTY, end=text.length(), pos=end-1, old=pos;
  // parse backwards 1 sexpr for lisp or to toplevel for Sal
  while (pos>-1) {
  typ = scan_sexpr(syntax->syntab, text, old, -1, SCAN_CODE, &pos);
  if ( (typ<=SCAN_EMPTY) || (syntaxId==syntaxLisp))
    break;
  old=pos;
  }

  if (typ==SCAN_EMPTY) {
    getConsole()->consolePrint(T("Editor (eval): Nothing to evaluate.\n"),
			       ConsoleTheme::warningColor);
  }
  if (typ<SCAN_EMPTY) {
    int l1, l2;
    getConsole()->consolePrint( T("Editor (eval): Unbalanced expression:\n"),
				ConsoleTheme::errorColor);
    // print line containing error with ^ marking offending position
    for (l2=old+1; l2<end; l2++)
      if (text[l2]=='\n') break;
    for (l1=old; l1>-1; l1--)
      if (text[l1]=='\n') break;
    l1++;
    getConsole()->consolePrint( text.substring(l1,l2), ConsoleTheme::errorColor);
    getConsole()->consoleTerpri();
    String mark=String::empty;
    for (int i=l1; i<old; i++)
      mark += T(" ");
    mark += T("^");
    getConsole()->consolePrint( mark, ConsoleTheme::errorColor);
    getConsole()->consoleTerpri();
    return 0;
  }
  if (syntaxId==syntaxSal)
    getConsole()->consoleEval(text, true);
  else
    getConsole()->consoleEval(text, false);
  return 0;
}

/// 
/// Editing
///

int TextBuffer::openLine() {
  // C-o new line does not change point
  int here = point();
  insertTextAtCursor(T("\n"));
  setPoint(here);
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
}

///
/// Non commands
///

ConsoleWindow* TextBuffer::getConsole() {
  return ((GraceApp *)GraceApp::getInstance())->getConsole();
}

int dodo=0;

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

  /*
  if (force) {
    // if recoloring, check if odd number of " in the edited region.  if
    // yes then color till end of buffer....
    // inserting " will have to do this as well i guess...
    int quo=0;
    for (int i=0;i<len;i++)
      if (text[i]=='\"') quo++;
    if (1 == quo % 2) {
      printf("odd string delims: hiliting rest of buffer\n");
      text=getTextSubstring(from,bufferMax());
      len=text.length();
    }
  }
  */

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
  case cmdPaste :  
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
  default :
    break;
  }
  if (bot==top) return;
  colorize(bot,top,true);
}

void TextBuffer::toggleHiliting() {
  //printf("toggle color\n");
  setHiliting ( ! isHiliting() ) ;
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

void TextBuffer::saveFile() {
  editfile.replaceWithText( getText() ) ;
  setChanged(false);
}

void TextBuffer::saveFileAs() {
  File dir;

  if ( editfile.existsAsFile() )
    dir = editfile.getParentDirectory();
  else dir = File::getSpecialLocation(File::userHomeDirectory);

  FileChooser choose (String::empty, dir, String::empty, true);

  if ( choose.browseForFileToSave(true) ) {
    File f = choose.getResult();
    f.replaceWithText( getText() );
    setChanged(false);
    editfile=File(f);
    parentWindow->setName( editfile.getFileName() );
  }
}

void TextBuffer::newFile(syntaxID mode) {
  // Open untitled (new) file with syntax Mode.
  static int num = 1;
  String name = T("untitled");
  if (num > 1) name << num;
  if (mode == syntaxSal) name << T(".sal") ;    
  else if (mode == syntaxLisp) name << T(".lisp") ;
  num++;
  new EditorWindow( File(name) ) ;
}

void TextBuffer::openFile() {
  File dir;
  if ( editfile.existsAsFile() )
    dir = editfile.getParentDirectory();
  else dir = File::getSpecialLocation(File::userHomeDirectory);

  FileChooser choose (T("Open File"), dir, String::empty, true);

  if ( choose.browseForFileToOpen() ) {
    File f = choose.getResult();
    new EditorWindow(f);
  }
}

void TextBuffer::revertFile() {
  File file = File( getName() );
  bool doit=false;
  if ( file.existsAsFile() ) 
    doit=AlertWindow::showOkCancelBox
      (AlertWindow::QuestionIcon, T("Revert File"),
       T("Really revert to last saved version of file?"),
       T("OK"), T("Cancel"));
  if ( doit ) {
    setText( file.loadFileAsString() ) ;
    if ( isHiliting() )
      colorizeAll();
  }
}


void TextBuffer::setFontType(const String name) {
  editfont.setTypefaceName( name );
  applyFontToAllText(editfont);
}

void TextBuffer::setFontSize( float size ) {
  editfont.setHeight(size);
  applyFontToAllText(editfont);
}
