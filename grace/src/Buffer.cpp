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
//#include "FontList.h"
#include "Grace.h"

#ifdef SCHEME
#include "Midi.h"
#endif

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
#ifdef MACOSX
  setFlagOn(emacsmode);
#endif

}

void TextBuffer::initSyntax (syntaxID id) {
  // initialize buffers' syntax table for the appropriate editing mode
  syntaxId=id;
  switch (id) {
  case syntaxSal :
    syntax=SalSyntax::getInstance();
    break;
  case syntaxLisp :
    syntax=LispSyntax::getInstance();
    break;
  case syntaxText :
  default : 
    syntaxId=syntaxText;
    setFlagOn(hiliteoff);
    syntax= TextSyntax::getInstance();
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
    cmdLispExpand,
    cmdLispLoadFile,
    cmdLispCompileFile,
    cmdLispShowDirectory,
    cmdLispSetDirectory,
    cmdLispSetPackage,
    cmdLispSymbolHelp,

    cmdSalEval,
    cmdSalExpand,
    cmdSalLoadFile,
    cmdSalShowDirectory,
    cmdSalSetDirectory,
    cmdSalSymbolHelp,

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
#ifndef SCHEME
    result.setActive(getConsole()->lisp->isLispRunning() );
#endif
    break;
  case cmdSalExpand:
  case cmdLispExpand:
    result.setInfo ((commandID==cmdLispExpand) ? T("Macro Expand") : T("Expand"), 
		    String::empty, editingCategory, 0);
#ifndef SCHEME
    result.setActive(getConsole()->lisp->isLispRunning() );
#endif
    break;
  case cmdLispLoadFile:
  case cmdSalLoadFile:
    result.setInfo (T("Load..."), String::empty, editingCategory, 0);
#ifndef SCHEME
    result.setActive(getConsole()->lisp->isLispRunning() );
#endif
    break;
  case cmdLispCompileFile:
    result.setInfo (T("Compile..."), String::empty, editingCategory, 0);
#ifndef SCHEME
    result.setActive(getConsole()->lisp->isLispRunning() );
#endif
    break;
  case cmdLispShowDirectory:
  case cmdSalShowDirectory:
    result.setInfo (T("Current Directory"), String::empty, editingCategory, 0);
#ifndef SCHEME
    result.setActive(getConsole()->lisp->isLispRunning() );
#endif
    break;
  case cmdLispSetDirectory:
  case cmdSalSetDirectory:
    result.setInfo (T("Change Directory..."), String::empty, editingCategory, 0);
#ifndef SCHEME
    result.setActive(getConsole()->lisp->isLispRunning() );
#endif
    break;
  case cmdLispSetPackage:
    result.setInfo (T("Set Package..."), String::empty, editingCategory, 0);
#ifndef SCHEME
    result.setActive(getConsole()->lisp->isLispRunning() );
#endif
    break;
  case cmdLispSymbolHelp:
  case cmdSalSymbolHelp:
    result.setInfo (T("Symbol Help"), String::empty, editingCategory, 0);
    result.addDefaultKeypress(T('?'), ModifierKeys::commandModifier);
    break;

  case cmdSalEval:
    result.setInfo (T("Execute"), String::empty, editingCategory, 0);
    result.addDefaultKeypress(KeyPress::returnKey, ModifierKeys::commandModifier);
#ifndef SCHEME
    result.setActive(getConsole()->lisp->isLoaded(p->getASDF(ASDF::CM)));
#endif
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

  case cmdViewFontList :   
    result.setInfo (T("Font Lisp"), String::empty, editingCategory, 0);
    break;
  case cmdViewFontSize :   
    result.setInfo (T("Font Size"), String::empty, editingCategory, 0);
    break;
  case cmdViewThemes :   
    result.setInfo (T("Themes"), String::empty, editingCategory, 0);
    break;
  case cmdOptionsHiliting :   
    result.setInfo (T("Toggle Highlighting"), String::empty, editingCategory, 0);
    break;
  case cmdGotoColumn :   
    result.setInfo (T("Goto Column"), String::empty, editingCategory, 0);
    break;
  case cmdGotoLine :   
    result.setInfo (T("Goto Line"), String::empty, editingCategory, 0);
    break;
  case cmdBackspace :   
    result.setInfo (T("Backspace"), String::empty, editingCategory, 0);
    break;
  case cmdKillWord :   
    result.setInfo (T("Kill Word"), String::empty, editingCategory, 0);
    break;
  case cmdKillWhite :   
    result.setInfo (T("Kill Whitespace"), String::empty, editingCategory, 0);
    break;
  case cmdKillLine :   
    result.setInfo (T("Kill Line"), String::empty, editingCategory, 0);
    break;
  case cmdInsertChar :   
    result.setInfo (T("Insert Character"), String::empty, editingCategory, 0);
    break;
  case cmdInsertLine :   
    result.setInfo (T("Insert Line"), String::empty, editingCategory, 0);
    break;
  case cmdOpenLine :   
    result.setInfo (T("Open Line"), String::empty, editingCategory, 0);
    break;
  case cmdComplete :   
    result.setInfo (T("Complete"), String::empty, editingCategory, 0);
    break;
  case cmdToggleReadWrite :   
    result.setInfo (T("Toggle Read/Write"), String::empty, editingCategory, 0);
    break;
  default:
    printf("FIXME: in getCommandInfo (Buffer.cpp) no info for command id %d.\n",
	   commandID);
    result.setInfo (T("UNKNOWN"), String::empty, editingCategory, 0);
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
    //cut();
    if (getHighlightedRegionLength()>0) {
      copy();
      keyPressed(KeyPress(KeyPress::deleteKey));
    }
    setChanged(true);
    break;
  case cmdEditCopy:
    copy();
    break;
  case cmdEditPaste:
    paste();
    //setChanged(true);
    //colorizeAfterChange(cmdEditPaste);
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
  case cmdSalEval:
    evalText();
    break;
  case cmdLispExpand:
  case cmdSalExpand:
    evalText(true);
    break;
  case cmdLispLoadFile:
  case cmdSalLoadFile:
    ((EditorWindow*)getTopLevelComponent())->loadFile();
    break;
  case cmdLispCompileFile:
    ((EditorWindow*)getTopLevelComponent())->compileFile();
    break;
  case cmdLispShowDirectory:
  case cmdSalShowDirectory:
    ((EditorWindow*)getTopLevelComponent())->showDirectory();
    break;
  case cmdLispSetDirectory:
  case cmdSalSetDirectory:
    ((EditorWindow*)getTopLevelComponent())->setDirectory();
    break;
  case cmdLispSetPackage:
    ((EditorWindow*)getTopLevelComponent())->setPackage();
    break;
  case cmdLispSymbolHelp:
  case cmdSalSymbolHelp:
    lookupHelpAtPoint();
    break;

  default:
    return false;
  }
  return true;
}

//
// Emacs Key Commands
//

class KeyCommands {
public:
  // seperate enums and arrays because the methods that call this code
  // already know what modifier group to search
  enum {Ctrl_A, Ctrl_B, Ctrl_D, Ctrl_E, Ctrl_F, Ctrl_K, Ctrl_N,
	Ctrl_O, Ctrl_P, Ctrl_T, Ctrl_V, Ctrl_W, Ctrl_X, Ctrl_Y, 
	MAXCTRLKEY};
  enum {Meta_B, Meta_C,  Meta_D, Meta_F, Meta_L, Meta_Q, Meta_U, Meta_V, 
	Meta_Sp, Meta_LT, Meta_GT, 
	MAXMETAKEY};
  enum {CtrlX_C, CtrlX_E, CtrlX_F, CtrlX_H, CtrlX_S, CtrlX_W, CtrlX_Z,
	MAXCTRLXKEY};
  enum {CtrlMeta_F, CtrlMeta_B, CtrlMeta_K, MAXCTRLMETAKEY};
  enum {Com_A, Com_C, Com_E, Com_N, Com_O, Com_R, Com_S, Com_T, Com_V,
	Com_W, Com_X, Com_Ret, Com_ArL, Com_ArR, Com_ArU, Com_ArD, Com_Period,
	Com_QMark,
	MAXCOMKEY};
#ifndef WINDOWS
  enum {emacsControl=1, emacsMeta, emacsControlMeta, emacsCommand, emacsCommandControl,
	emacsCommandMeta, emacsCommandControlMeta};
#else
  enum {emacsControl=2, emacsMeta=4, emacsControlMeta=6,
	// noops in windows (?)
	emacsCommand=178,emacsCommandControl=179, emacsCommandMeta=180, 
	emacsCommandControlMeta=181};
#endif 

  KeyPress ctrlkeys[MAXCTRLKEY];
  KeyPress metakeys[MAXMETAKEY];
  KeyPress ctrlxkeys[MAXCTRLXKEY];
  KeyPress ctrlmetakeys[MAXCTRLMETAKEY];
  KeyPress comkeys[MAXCOMKEY];

  KeyCommands() {
    ctrlkeys[Ctrl_A]=KeyPress::createFromDescription(T("ctrl + A"));
    ctrlkeys[Ctrl_B]=KeyPress::createFromDescription(T("ctrl + B"));
    ctrlkeys[Ctrl_D]=KeyPress::createFromDescription(T("ctrl + D"));
    ctrlkeys[Ctrl_E]=KeyPress::createFromDescription(T("ctrl + E"));
    ctrlkeys[Ctrl_F]=KeyPress::createFromDescription(T("ctrl + F"));
    ctrlkeys[Ctrl_K]=KeyPress::createFromDescription(T("ctrl + K"));
    ctrlkeys[Ctrl_N]=KeyPress::createFromDescription(T("ctrl + N"));
    ctrlkeys[Ctrl_O]=KeyPress::createFromDescription(T("ctrl + O"));
    ctrlkeys[Ctrl_P]=KeyPress::createFromDescription(T("ctrl + P"));
    ctrlkeys[Ctrl_T]=KeyPress::createFromDescription(T("ctrl + T"));
    ctrlkeys[Ctrl_V]=KeyPress::createFromDescription(T("ctrl + V"));
    ctrlkeys[Ctrl_W]=KeyPress::createFromDescription(T("ctrl + W"));
    ctrlkeys[Ctrl_X]=KeyPress::createFromDescription(T("ctrl + X"));
    ctrlkeys[Ctrl_Y]=KeyPress::createFromDescription(T("ctrl + Y"));

    metakeys[Meta_B]=KeyPress::createFromDescription(T("option + B"));
    metakeys[Meta_C]=KeyPress::createFromDescription(T("option + C"));
    metakeys[Meta_D]=KeyPress::createFromDescription(T("option + D"));
    metakeys[Meta_F]=KeyPress::createFromDescription(T("option + F"));
    metakeys[Meta_L]=KeyPress::createFromDescription(T("option + L"));
    metakeys[Meta_Q]=KeyPress::createFromDescription(T("option + Q"));
    metakeys[Meta_U]=KeyPress::createFromDescription(T("option + U"));
    metakeys[Meta_V]=KeyPress::createFromDescription(T("option + V"));
    metakeys[Meta_Sp]=KeyPress::createFromDescription(T("option + spacebar"));
    metakeys[Meta_LT]=KeyPress::createFromDescription(T("shift + option + ,"));
    metakeys[Meta_GT]=KeyPress::createFromDescription(T("shift + option + ."));
    //metakeys[Meta_ArL]=KeyPress::createFromDescription(T("option + cursor left"));
    //metakeys[Meta_ArR]=KeyPress::createFromDescription(T("option + cursor right"));
    //metakeys[Meta_ArU]=KeyPress::createFromDescription(T("option + cursor up"));
    //metakeys[Meta_ArD]=KeyPress::createFromDescription(T("option + cursor down"));

    ctrlxkeys[CtrlX_C]=KeyPress::createFromDescription(T("ctrl + C"));
    ctrlxkeys[CtrlX_E]=KeyPress::createFromDescription(T("ctrl + E"));
    ctrlxkeys[CtrlX_F]=KeyPress::createFromDescription(T("ctrl + F"));
    ctrlxkeys[CtrlX_H]=KeyPress::createFromDescription(T("ctrl + H"));
    ctrlxkeys[CtrlX_S]=KeyPress::createFromDescription(T("ctrl + S"));
    ctrlxkeys[CtrlX_W]=KeyPress::createFromDescription(T("ctrl + W"));
    ctrlxkeys[CtrlX_Z]=KeyPress::createFromDescription(T("ctrl + Z"));

    ctrlmetakeys[CtrlMeta_F]=KeyPress::createFromDescription(T("ctrl + option + F"));
    ctrlmetakeys[CtrlMeta_B]=KeyPress::createFromDescription(T("ctrl + option + B"));
    ctrlmetakeys[CtrlMeta_K]=KeyPress::createFromDescription(T("ctrl + option + K"));

    comkeys[Com_A]=KeyPress::createFromDescription(T("command + A"));
    comkeys[Com_C]=KeyPress::createFromDescription(T("command + C"));
    comkeys[Com_E]=KeyPress::createFromDescription(T("command + E"));
    comkeys[Com_N]=KeyPress::createFromDescription(T("command + N"));
    comkeys[Com_O]=KeyPress::createFromDescription(T("command + O"));
    comkeys[Com_R]=KeyPress::createFromDescription(T("command + R"));
    comkeys[Com_S]=KeyPress::createFromDescription(T("command + S"));
    comkeys[Com_T]=KeyPress::createFromDescription(T("command + T"));
    comkeys[Com_V]=KeyPress::createFromDescription(T("command + V"));
    comkeys[Com_W]=KeyPress::createFromDescription(T("command + W"));
    comkeys[Com_X]=KeyPress::createFromDescription(T("command + X"));
    comkeys[Com_Period] = KeyPress::createFromDescription(T("command + ."));
    comkeys[Com_QMark] = KeyPress::createFromDescription(T("shift + command + /"));
    comkeys[Com_Ret]=KeyPress::createFromDescription(T("command + return"));
    comkeys[Com_ArL]=KeyPress::createFromDescription(T("command + cursor left"));
    comkeys[Com_ArR]=KeyPress::createFromDescription(T("command + cursor right"));
    comkeys[Com_ArU]=KeyPress::createFromDescription(T("command + cursor up"));
    comkeys[Com_ArD]=KeyPress::createFromDescription(T("command + cursor down"));
  }

  ~KeyCommands() {
    clearSingletonInstance();
  }

  int isCtrlCommand(KeyPress key) {
    for (int i=0; i<MAXCTRLKEY; i++)
      if (ctrlkeys[i]==key) return i;
    return -1;
  }

  int isMetaCommand(KeyPress key) {
    for (int i=0; i<MAXMETAKEY; i++)
      if (metakeys[i]==key) return i;
    return -1;
  }

  int isCtrlXCommand(KeyPress key) {
    for (int i=0; i<MAXCTRLXKEY; i++)
      if (ctrlxkeys[i]==key) return i;
    return -1;
  }

  int isCtrlMetaCommand(KeyPress key) {
    for (int i=0; i<MAXCTRLMETAKEY; i++)
      if (ctrlmetakeys[i]==key) return i;
    return -1;
  }

  int isComKeyCommand(KeyPress key) {
    for (int i=0; i<MAXCOMKEY; i++)
      if (comkeys[i]==key) return i;
    return -1;
  }

  juce_DeclareSingleton (KeyCommands, true)

};

juce_ImplementSingleton (KeyCommands) ;


// Main Keyboard Command functions

int getCtrlCommand(KeyPress key) {
  return KeyCommands::getInstance()->isCtrlCommand(key);
}

int getMetaCommand(KeyPress key) {
  return KeyCommands::getInstance()->isMetaCommand(key);
}

int getCtrlMetaCommand(KeyPress key) {
  return KeyCommands::getInstance()->isCtrlMetaCommand(key);
}

int getCtrlXCommand(KeyPress key) {
  return KeyCommands::getInstance()->isCtrlXCommand(key);
}

int getComKeyCommand(KeyPress key) {
  return KeyCommands::getInstance()->isComKeyCommand(key);
}

int TextBuffer::isKeyCommand (const KeyPress& key) {
  // true if Emacs mode and C, M or COM keys down w Shift ignored
  int flag = 0;
  if ( isEmacsMode() ) {
    if ( key.getModifiers().isCtrlDown() )
      flag = KeyCommands::emacsControl;
    if ( key.getModifiers().isAltDown() )
      flag |= KeyCommands::emacsMeta;
#ifdef MACOSX
    if ( key.getModifiers().isCommandDown() )
      flag |= KeyCommands::emacsCommand;
#endif
  }
  else {
    if ( key.getModifiers().isCommandDown() )
      flag |= KeyCommands::emacsCommand;
  }
  if ((flag != 0) && key.getModifiers().isAnyMouseButtonDown() )
    return -1;
  else
    return flag;
}

void TextBuffer::keyControlAction(const KeyPress& key) {
  // Called if Emacs mode AND keypress has Control Key down
  int cmd = getCtrlCommand(key);

  //String text = key.getTextDescription();
  //printf("keypress: T(\"%s\"), command: %d\n", text.toUTF8(), cmd);

  switch (cmd) {
  case KeyCommands::Ctrl_A :
    gotoBOL();
    break;
  case KeyCommands::Ctrl_B :
    backwardChar();
    break;
  case KeyCommands::Ctrl_D :
    deleteChar(1);
    setChanged(true);
    colorizeAfterChange(cmdDelete);
    break;
  case KeyCommands::Ctrl_E :
    gotoEOL();
    break;
  case KeyCommands::Ctrl_F :
    forwardChar();
    break;
  case KeyCommands::Ctrl_K :
    killLine();
    setChanged(true);
    colorizeAfterChange(cmdKillLine);
    break;
  case KeyCommands::Ctrl_N :
    nextLine(); 
    break;
  case KeyCommands::Ctrl_O :
    openLine();
    setChanged(true);
    colorizeAfterChange(cmdOpenLine);
    break;
  case KeyCommands::Ctrl_P :
    previousLine();
    break;
  case KeyCommands::Ctrl_T :
    /**** C-t for temp command testing  ****/
    break;
  case KeyCommands::Ctrl_V :
    forwardScreen();
    break;
  case KeyCommands::Ctrl_W :
    if (getHighlightedRegionLength()>0) {
      copy();
      keyPressed(KeyPress(KeyPress::deleteKey));
    }
    break;
  case KeyCommands::Ctrl_X :
    setAction(actControlX);
    break;
  case KeyCommands::Ctrl_Y :
    paste();
    //setChanged(true);
    //colorizeAfterChange(cmdEditPaste);
    break;
  default :
    keyIllegalAction(key);
  }
}

void TextBuffer::keyControlXAction (const KeyPress& key) {
  // Called if EmacMode AND keypress after Control X
  int cmd = getCtrlXCommand(key);

  //String text = key.getTextDescription();
  //printf("keypress: T(\"%s\"), command: %d\n", text.toUTF8(), cmd);

  switch (cmd) {
  case KeyCommands::CtrlX_C :
    ((EditorWindow*)getTopLevelComponent())->closeFile();
    break;
  case KeyCommands::CtrlX_E :
    evalText();
    break;
  case KeyCommands::CtrlX_F :
    ((EditorWindow*)getTopLevelComponent())->openFile();
    break;
  case KeyCommands::CtrlX_H :
    toggleHiliting();
    break;
  case KeyCommands::CtrlX_S :
    ((EditorWindow*)getTopLevelComponent())->saveFile();
    break;
  case KeyCommands::CtrlX_W :
    ((EditorWindow*)getTopLevelComponent())->saveFileAs();
    break;
  case KeyCommands::CtrlX_Z :
    break;
  default :
    keyIllegalAction(key);
    break;
  } 
}

void TextBuffer::keyMetaAction(const KeyPress& key) {
  // Called if EmacsMode AND keypress has Meta key down
  int cmd = getMetaCommand(key);

  //String text = key.getTextDescription();
  //printf("keypress: T(\"%s\"), command: %d\n", text.toUTF8(), cmd);

  switch ( cmd ) {
  case KeyCommands::Meta_F :
    forwardWord();
    break;
  case KeyCommands::Meta_B :
    backwardWord();
    break;
  case KeyCommands::Meta_Q :
    reformatCommentBlock();
    break;
  case KeyCommands::Meta_L :
    changeCase(0);
    break;
  case KeyCommands::Meta_U :
    changeCase(1);
    break;
  case KeyCommands::Meta_C :
    changeCase(2);
    break;
  case KeyCommands::Meta_V :
    backwardScreen();
    break;
  case KeyCommands::Meta_LT :
    gotoBOB();
    break;
  case KeyCommands::Meta_GT :
    gotoEOB();
    break;
  case KeyCommands::Meta_D :
    killWord();
    setChanged(true);
    colorizeAfterChange(cmdKillWord);
    break;
  case KeyCommands::Meta_Sp :
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
  // Called if EmacsMode AND keypress has Ctrl Meta down
  int cmd = getCtrlMetaCommand(key);

  //  String text = key.getTextDescription();
  //  printf("keypress: T(\"%s\"), command: %d\n", text.toUTF8(), cmd);

  switch (cmd) {
  case KeyCommands::CtrlMeta_F :
    forwardSexpr();
    break;
  case KeyCommands::CtrlMeta_B :
    backwardSexpr();
    break;
  case KeyCommands::CtrlMeta_K :
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
  // Called if keypress is Command Key
  int cmd = getComKeyCommand(key);
  syntaxID sid = syntaxSal;

  //String text = key.getTextDescription();
  //printf("keypress: T(\"%s\")\n", text.toUTF8());

  switch ( cmd ) {
  case KeyCommands::Com_A :
    selectAll();
    break;
  case KeyCommands::Com_V :
    paste(); 
    //setChanged(true);
    //colorizeAfterChange(cmdEditPaste);
    break;
  case KeyCommands::Com_C :
    copy();
    break;
  case KeyCommands::Com_O :
    ((EditorWindow*)getTopLevelComponent())->openFile();
    break;
  case KeyCommands::Com_N :
    sid=(key.getModifiers().isShiftDown()) ? syntaxLisp : syntaxSal;
    ((EditorWindow*)getTopLevelComponent())->newFile(sid);
    break;
  case KeyCommands::Com_R :
    ((EditorWindow*)getTopLevelComponent())->revertFile();
    break;
  case KeyCommands::Com_S :
    ((EditorWindow*)getTopLevelComponent())->saveFile();
    break;
  case KeyCommands::Com_W :
    ((EditorWindow*)getTopLevelComponent())->closeFile();
    break;
  case KeyCommands::Com_X :
    if (getHighlightedRegionLength()>0) {
      copy();
      keyPressed(KeyPress(KeyPress::deleteKey));
    }
    break;
  case KeyCommands::Com_Period :
#ifdef SCHEME
    // flush scheduler and midi out thread
    ((GraceApp *)GraceApp::getInstance())->schemeProcess->stop();
    ((GraceApp *)GraceApp::getInstance())->midiOutPort->clear();
#endif
    break;

  case KeyCommands::Com_QMark:
    lookupHelpAtPoint();
    break;

  case KeyCommands::Com_E :
  case KeyCommands::Com_Ret :
    evalText();
    break;
  case KeyCommands::Com_ArL :
    gotoBOL();
    break;
  case KeyCommands::Com_ArR :
    gotoEOL();
    break;
  case KeyCommands::Com_ArU :
    gotoBOB();
    break;
  case KeyCommands::Com_ArD :
    gotoEOB();
    break;
    
  case KeyCommands::Com_T :
    /****  SAL TESTING  *****/
    if (syntaxId == syntaxSal) {
      //      String text=backwardTopLevelText();
      //      if (text != String::empty)
      //	((SalSyntax *)syntax)->tokenize(text);
      salTokenize();
    }
    break;
  default :
    keyIllegalAction(key);
    break;
  }
}
   
void TextBuffer::keyIllegalAction(const KeyPress& key) {
  String msg = T(">>> Error: ") + key.getTextDescription() +
    T(" is not a keyboard command.\n") ;
  getConsole()->printError(msg);
}

///
/// Symbol Help. This should get moved to its own File!
///

juce_ImplementSingleton (SymbolHelp) ;

SymbolHelp::SymbolHelp() {
  addSalHelp();
  addGraceSchemeHelp();
  addSchemeHelp();
  addCommonMusicHelp();
  addCommonLispMusicHelp();
  addFomusHelp();
  addCommonLispHelp();
}

SymbolHelp::~SymbolHelp() {
  clearSingletonInstance();
}

void SymbolHelp::addSalHelp() {
  maproots.set( T("Sal"), ((GraceApp *)GraceApp::getInstance())->
		getResourceDirectoryPathName()+T("/doc/sal/help/"));
  salmap.set(T("begin"), T("begin.sal"));
  salmap.set(T("chdir"), T("chdir.sal"));
  salmap.set(T("define"), T("define.sal"));
  salmap.set(T("end"), T("begin.sal"));
  salmap.set(T("exec"), T("exec.sal"));
  salmap.set(T("if"), T("if.sal"));
  salmap.set(T("load"), T("load.sal"));
  salmap.set(T("loop"), T("loop.sal"));
  salmap.set(T("open"), T("open.sal"));
  salmap.set(T("output"), T("output.sal"));
  salmap.set(T("play"), T("play.sal"));
  salmap.set(T("plot"), T("plot.sal"));
  salmap.set(T("print"), T("print.sal"));
  salmap.set(T("return"), T("return.sal"));
  salmap.set(T("run"), T("run.sal"));
  salmap.set(T("send"), T("send.sal"));
  salmap.set(T("set"), T("set.sal"));
  salmap.set(T("="), T("set.sal"));
  salmap.set(T("&="), T("set.sal"));
  salmap.set(T("^="), T("set.sal"));
  salmap.set(T("*="), T("set.sal"));
  salmap.set(T("+="), T("set.sal"));
  salmap.set(T(">="), T("set.sal"));
  salmap.set(T("<="), T("set.sal"));
  salmap.set(T("sprout"), T("sprout.sal"));
  salmap.set(T("system"), T("system.sal"));
  salmap.set(T("unless"), T("unless.sal"));
  salmap.set(T("wait"), T("run.sal"));
  salmap.set(T("while"), T("loop.sal"));
  salmap.set(T("until"), T("loop.sal"));
  salmap.set(T("when"), T("when.sal"));
  salmap.set(T("with"), T("with.sal"));
}

void SymbolHelp::addGraceSchemeHelp() {
  maproots.set( T("GraceScheme"), T("file://") + ((GraceApp *)GraceApp::getInstance())->
		getResourceDirectoryPathName() + T("/doc/"));
}

void SymbolHelp::addSchemeHelp() {
  maproots.set( T("Scheme"), T("http://www.schemers.org/Documents/Standards/R5RS/HTML/"));
#ifdef SCHEME
  schememap.set( T("*"), T("r5rs-Z-H-9.html#%_idx_280") );
  schememap.set( T("+"), T("r5rs-Z-H-9.html#%_idx_278") );
  schememap.set( T("-"), T("r5rs-Z-H-9.html#%_idx_282") );
  schememap.set( T("/"), T("r5rs-Z-H-9.html#%_idx_284") );
  schememap.set( T("<"), T("r5rs-Z-H-9.html#%_idx_256") );
  schememap.set( T("<="), T("r5rs-Z-H-9.html#%_idx_260") );
  schememap.set( T("="), T("r5rs-Z-H-9.html#%_idx_254") );
  schememap.set( T("=>"), T("r5rs-Z-H-7.html#%_idx_110") );
  schememap.set( T(">"), T("r5rs-Z-H-9.html#%_idx_258") );
  schememap.set( T(">="), T("r5rs-Z-H-9.html#%_idx_262") );
  schememap.set( T("abs"), T("r5rs-Z-H-9.html#%_idx_286") );
  schememap.set( T("acos"), T("r5rs-Z-H-9.html#%_idx_326") );
  schememap.set( T("and"), T("r5rs-Z-H-7.html#%_idx_118") );
  schememap.set( T("angle"), T("r5rs-Z-H-9.html#%_idx_344") );
  schememap.set( T("append"), T("r5rs-Z-H-9.html#%_idx_420") );
  schememap.set( T("apply"), T("r5rs-Z-H-9.html#%_idx_556") );
  schememap.set( T("asin"), T("r5rs-Z-H-9.html#%_idx_324") );
  schememap.set( T("assoc"), T("r5rs-Z-H-9.html#%_idx_438") );
  schememap.set( T("assq"), T("r5rs-Z-H-9.html#%_idx_434") );
  schememap.set( T("assv"), T("r5rs-Z-H-9.html#%_idx_436") );
  schememap.set( T("atan"), T("r5rs-Z-H-9.html#%_idx_328") );
  schememap.set( T("#b"), T("r5rs-Z-H-9.html#%_idx_228") );
  schememap.set( T("begin"), T("r5rs-Z-H-7.html#%_idx_136") );
  schememap.set( T("boolean?"), T("r5rs-Z-H-6.html#%_idx_46") );
  schememap.set( T("caar"), T("r5rs-Z-H-9.html#%_idx_402") );
  schememap.set( T("cadr"), T("r5rs-Z-H-9.html#%_idx_404") );
  schememap.set( T("call-with-current-continuation"), T("r5rs-Z-H-9.html#%_idx_566") );
  schememap.set( T("call-with-input-file"), T("r5rs-Z-H-9.html#%_idx_588") );
  schememap.set( T("call-with-output-file"), T("r5rs-Z-H-9.html#%_idx_590") );
  schememap.set( T("call-with-values"), T("r5rs-Z-H-9.html#%_idx_574") );
  schememap.set( T("car"), T("r5rs-Z-H-9.html#%_idx_392") );
  schememap.set( T("case"), T("r5rs-Z-H-7.html#%_idx_114") );
  schememap.set( T("cdddar"), T("r5rs-Z-H-9.html#%_idx_406") );
  schememap.set( T("cddddr"), T("r5rs-Z-H-9.html#%_idx_408") );
  schememap.set( T("cdr"), T("r5rs-Z-H-9.html#%_idx_396") );
  schememap.set( T("ceiling"), T("r5rs-Z-H-9.html#%_idx_304") );
  schememap.set( T("char->integer"), T("r5rs-Z-H-9.html#%_idx_480") );
  schememap.set( T("char-alphabetic?"), T("r5rs-Z-H-9.html#%_idx_470") );
  schememap.set( T("char-ci<=?"), T("r5rs-Z-H-9.html#%_idx_466") );
  schememap.set( T("char-ci<?"), T("r5rs-Z-H-9.html#%_idx_462") );
  schememap.set( T("char-ci=?"), T("r5rs-Z-H-9.html#%_idx_460") );
  schememap.set( T("char-ci>=?"), T("r5rs-Z-H-9.html#%_idx_468") );
  schememap.set( T("char-ci>?"), T("r5rs-Z-H-9.html#%_idx_464") );
  schememap.set( T("char-downcase"), T("r5rs-Z-H-9.html#%_idx_486") );
  schememap.set( T("char-lower-case?"), T("r5rs-Z-H-9.html#%_idx_478") );
  schememap.set( T("char-numeric?"), T("r5rs-Z-H-9.html#%_idx_472") );
  schememap.set( T("char-ready?"), T("r5rs-Z-H-9.html#%_idx_620") );
  schememap.set( T("char-upcase"), T("r5rs-Z-H-9.html#%_idx_484") );
  schememap.set( T("char-upper-case?"), T("r5rs-Z-H-9.html#%_idx_476") );
  schememap.set( T("char-whitespace?"), T("r5rs-Z-H-9.html#%_idx_474") );
  schememap.set( T("char<=?"), T("r5rs-Z-H-9.html#%_idx_456") );
  schememap.set( T("char<?"), T("r5rs-Z-H-9.html#%_idx_452") );
  schememap.set( T("char=?"), T("r5rs-Z-H-9.html#%_idx_450") );
  schememap.set( T("char>=?"), T("r5rs-Z-H-9.html#%_idx_458") );
  schememap.set( T("char>?"), T("r5rs-Z-H-9.html#%_idx_454") );
  schememap.set( T("char?"), T("r5rs-Z-H-6.html#%_idx_54") );
  schememap.set( T("close-input-port"), T("r5rs-Z-H-9.html#%_idx_608") );
  schememap.set( T("close-output-port"), T("r5rs-Z-H-9.html#%_idx_610") );
  schememap.set( T("complex?"), T("r5rs-Z-H-9.html#%_idx_242") );
  schememap.set( T("cond"), T("r5rs-Z-H-7.html#%_idx_106") );
  schememap.set( T("cons"), T("r5rs-Z-H-9.html#%_idx_390") );
  schememap.set( T("cos"), T("r5rs-Z-H-9.html#%_idx_320") );
  schememap.set( T("current-input-port"), T("r5rs-Z-H-9.html#%_idx_596") );
  schememap.set( T("current-output-port"), T("r5rs-Z-H-9.html#%_idx_598") );
  schememap.set( T("#d"), T("r5rs-Z-H-9.html#%_idx_232") );
  schememap.set( T("define"), T("r5rs-Z-H-8.html#%_idx_190") );
  schememap.set( T("define-syntax"), T("r5rs-Z-H-8.html#%_idx_198") );
  schememap.set( T("delay"), T("r5rs-Z-H-7.html#%_idx_142") );
  schememap.set( T("denominator"), T("r5rs-Z-H-9.html#%_idx_300") );
  schememap.set( T("display"), T("r5rs-Z-H-9.html#%_idx_624") );
  schememap.set( T("do"), T("r5rs-Z-H-7.html#%_idx_138") );
  schememap.set( T("dynamic-wind"), T("r5rs-Z-H-9.html#%_idx_576") );
  schememap.set( T("#e"), T("r5rs-Z-H-9.html#%_idx_236") );
  schememap.set( T("else"), T("r5rs-Z-H-7.html#%_idx_108") );
  schememap.set( T("eof-object?"), T("r5rs-Z-H-9.html#%_idx_618") );
  schememap.set( T("eq?"), T("r5rs-Z-H-9.html#%_idx_216") );
  schememap.set( T("equal?"), T("r5rs-Z-H-9.html#%_idx_218") );
  schememap.set( T("eqv?"), T("r5rs-Z-H-9.html#%_idx_210") );
  schememap.set( T("eval"), T("r5rs-Z-H-9.html#%_idx_578") );
  schememap.set( T("even?"), T("r5rs-Z-H-9.html#%_idx_272") );
  schememap.set( T("exact->inexact"), T("r5rs-Z-H-9.html#%_idx_346") );
  schememap.set( T("exact?"), T("r5rs-Z-H-9.html#%_idx_250") );
  schememap.set( T("exp"), T("r5rs-Z-H-9.html#%_idx_314") );
  schememap.set( T("expt"), T("r5rs-Z-H-9.html#%_idx_332") );
  schememap.set( T("#f"), T("r5rs-Z-H-9.html#%_idx_356") );
  schememap.set( T("floor"), T("r5rs-Z-H-9.html#%_idx_302") );
  schememap.set( T("for-each"), T("r5rs-Z-H-9.html#%_idx_560") );
  schememap.set( T("force"), T("r5rs-Z-H-9.html#%_idx_562") );
  schememap.set( T("gcd"), T("r5rs-Z-H-9.html#%_idx_294") );
  schememap.set( T("#i"), T("r5rs-Z-H-9.html#%_idx_238") );
  schememap.set( T("if"), T("r5rs-Z-H-7.html#%_idx_98") );
  schememap.set( T("imag-part"), T("r5rs-Z-H-9.html#%_idx_340") );
  schememap.set( T("inexact->exact"), T("r5rs-Z-H-9.html#%_idx_348") );
  schememap.set( T("inexact?"), T("r5rs-Z-H-9.html#%_idx_252") );
  schememap.set( T("input-port?"), T("r5rs-Z-H-9.html#%_idx_592") );
  schememap.set( T("integer->char"), T("r5rs-Z-H-9.html#%_idx_482") );
  schememap.set( T("integer?"), T("r5rs-Z-H-9.html#%_idx_248") );
  schememap.set( T("interaction-environment"), T("r5rs-Z-H-9.html#%_idx_584") );
  schememap.set( T("lambda"), T("r5rs-Z-H-7.html#%_idx_96") );
  schememap.set( T("lcm"), T("r5rs-Z-H-9.html#%_idx_296") );
  schememap.set( T("length"), T("r5rs-Z-H-9.html#%_idx_418") );
  schememap.set( T("let"), T("r5rs-Z-H-7.html#%_idx_124") );
  schememap.set( T("let*"), T("r5rs-Z-H-7.html#%_idx_128") );
  schememap.set( T("let-syntax"), T("r5rs-Z-H-7.html#%_idx_180") );
  schememap.set( T("letrec"), T("r5rs-Z-H-7.html#%_idx_132") );
  schememap.set( T("letrec-syntax"), T("r5rs-Z-H-7.html#%_idx_182") );
  schememap.set( T("list"), T("r5rs-Z-H-9.html#%_idx_416") );
  schememap.set( T("list->string"), T("r5rs-Z-H-9.html#%_idx_528") );
  schememap.set( T("list->vector"), T("r5rs-Z-H-9.html#%_idx_550") );
  schememap.set( T("list-ref"), T("r5rs-Z-H-9.html#%_idx_426") );
  schememap.set( T("list-tail"), T("r5rs-Z-H-9.html#%_idx_424") );
  schememap.set( T("list?"), T("r5rs-Z-H-9.html#%_idx_414") );
  schememap.set( T("load"), T("r5rs-Z-H-9.html#%_idx_630") );
  schememap.set( T("log"), T("r5rs-Z-H-9.html#%_idx_316") );
  schememap.set( T("magnitude"), T("r5rs-Z-H-9.html#%_idx_342") );
  schememap.set( T("make-polar"), T("r5rs-Z-H-9.html#%_idx_336") );
  schememap.set( T("make-rectangular"), T("r5rs-Z-H-9.html#%_idx_334") );
  schememap.set( T("make-string"), T("r5rs-Z-H-9.html#%_idx_492") );
  schememap.set( T("make-vector"), T("r5rs-Z-H-9.html#%_idx_538") );
  schememap.set( T("map"), T("r5rs-Z-H-9.html#%_idx_558") );
  schememap.set( T("max"), T("r5rs-Z-H-9.html#%_idx_274") );
  schememap.set( T("member"), T("r5rs-Z-H-9.html#%_idx_432") );
  schememap.set( T("memq"), T("r5rs-Z-H-9.html#%_idx_428") );
  schememap.set( T("memv"), T("r5rs-Z-H-9.html#%_idx_430") );
  schememap.set( T("min"), T("r5rs-Z-H-9.html#%_idx_276") );
  schememap.set( T("modulo"), T("r5rs-Z-H-9.html#%_idx_292") );
  schememap.set( T("negative?"), T("r5rs-Z-H-9.html#%_idx_268") );
  schememap.set( T("newline"), T("r5rs-Z-H-9.html#%_idx_626") );
  schememap.set( T("not"), T("r5rs-Z-H-9.html#%_idx_368") );
  schememap.set( T("null-environment"), T("r5rs-Z-H-9.html#%_idx_582") );
  schememap.set( T("null?"), T("r5rs-Z-H-9.html#%_idx_410") );
  schememap.set( T("number->string"), T("r5rs-Z-H-9.html#%_idx_350") );
  schememap.set( T("number?"), T("r5rs-Z-H-6.html#%_idx_52") );
  schememap.set( T("numerator"), T("r5rs-Z-H-9.html#%_idx_298") );
  schememap.set( T("#o"), T("r5rs-Z-H-9.html#%_idx_230") );
  schememap.set( T("odd?"), T("r5rs-Z-H-9.html#%_idx_270") );
  schememap.set( T("open-input-file"), T("r5rs-Z-H-9.html#%_idx_604") );
  schememap.set( T("open-output-file"), T("r5rs-Z-H-9.html#%_idx_606") );
  schememap.set( T("or"), T("r5rs-Z-H-7.html#%_idx_120") );
  schememap.set( T("output-port?"), T("r5rs-Z-H-9.html#%_idx_594") );
  schememap.set( T("pair?"), T("r5rs-Z-H-6.html#%_idx_48") );
  schememap.set( T("peek-char"), T("r5rs-Z-H-9.html#%_idx_616") );
  schememap.set( T("port?"), T("r5rs-Z-H-6.html#%_idx_60") );
  schememap.set( T("positive?"), T("r5rs-Z-H-9.html#%_idx_266") );
  schememap.set( T("procedure?"), T("r5rs-Z-H-6.html#%_idx_62") );
  schememap.set( T("quasiquote"), T("r5rs-Z-H-7.html#%_idx_150") );
  schememap.set( T("quote"), T("r5rs-Z-H-7.html#%_idx_86") );
  schememap.set( T("quotient"), T("r5rs-Z-H-9.html#%_idx_288") );
  schememap.set( T("rational?"), T("r5rs-Z-H-9.html#%_idx_246") );
  schememap.set( T("rationalize"), T("r5rs-Z-H-9.html#%_idx_310") );
  schememap.set( T("read"), T("r5rs-Z-H-9.html#%_idx_612") );
  schememap.set( T("read-char"), T("r5rs-Z-H-9.html#%_idx_614") );
  schememap.set( T("real-part"), T("r5rs-Z-H-9.html#%_idx_338") );
  schememap.set( T("real?"), T("r5rs-Z-H-9.html#%_idx_244") );
  schememap.set( T("remainder"), T("r5rs-Z-H-9.html#%_idx_290") );
  schememap.set( T("reverse"), T("r5rs-Z-H-9.html#%_idx_422") );
  schememap.set( T("round"), T("r5rs-Z-H-9.html#%_idx_308") );
  schememap.set( T("scheme-report-environment"), T("r5rs-Z-H-9.html#%_idx_580") );
  schememap.set( T("set!"), T("r5rs-Z-H-7.html#%_idx_102") );
  schememap.set( T("set-car!"), T("r5rs-Z-H-9.html#%_idx_398") );
  schememap.set( T("set-cdr!"), T("r5rs-Z-H-9.html#%_idx_400") );
  schememap.set( T("setcar"), T("r5rs-Z-H-10.html#%_idx_644") );
  schememap.set( T("sin"), T("r5rs-Z-H-9.html#%_idx_318") );
  schememap.set( T("sqrt"), T("r5rs-Z-H-9.html#%_idx_330") );
  schememap.set( T("string"), T("r5rs-Z-H-9.html#%_idx_494") );
  schememap.set( T("string->list"), T("r5rs-Z-H-9.html#%_idx_526") );
  schememap.set( T("string->number"), T("r5rs-Z-H-9.html#%_idx_352") );
  schememap.set( T("string->symbol"), T("r5rs-Z-H-9.html#%_idx_446") );
  schememap.set( T("string-append"), T("r5rs-Z-H-9.html#%_idx_524") );
  schememap.set( T("string-ci<=?"), T("r5rs-Z-H-9.html#%_idx_518") );
  schememap.set( T("string-ci<?"), T("r5rs-Z-H-9.html#%_idx_514") );
  schememap.set( T("string-ci=?"), T("r5rs-Z-H-9.html#%_idx_504") );
  schememap.set( T("string-ci>=?"), T("r5rs-Z-H-9.html#%_idx_520") );
  schememap.set( T("string-ci>?"), T("r5rs-Z-H-9.html#%_idx_516") );
  schememap.set( T("string-copy"), T("r5rs-Z-H-9.html#%_idx_530") );
  schememap.set( T("string-fill!"), T("r5rs-Z-H-9.html#%_idx_532") );
  schememap.set( T("string-length"), T("r5rs-Z-H-9.html#%_idx_496") );
  schememap.set( T("string-ref"), T("r5rs-Z-H-9.html#%_idx_498") );
  schememap.set( T("string-set!"), T("r5rs-Z-H-9.html#%_idx_500") );
  schememap.set( T("string<=?"), T("r5rs-Z-H-9.html#%_idx_510") );
  schememap.set( T("string<?"), T("r5rs-Z-H-9.html#%_idx_506") );
  schememap.set( T("string=?"), T("r5rs-Z-H-9.html#%_idx_502") );
  schememap.set( T("string>=?"), T("r5rs-Z-H-9.html#%_idx_512") );
  schememap.set( T("string>?"), T("r5rs-Z-H-9.html#%_idx_508") );
  schememap.set( T("string?"), T("r5rs-Z-H-6.html#%_idx_56") );
  schememap.set( T("substring"), T("r5rs-Z-H-9.html#%_idx_522") );
  schememap.set( T("symbol->string"), T("r5rs-Z-H-9.html#%_idx_444") );
  schememap.set( T("symbol?"), T("r5rs-Z-H-6.html#%_idx_50") );
  schememap.set( T("syntax-rules"), T("r5rs-Z-H-7.html#%_idx_184") );
  schememap.set( T("#t"), T("r5rs-Z-H-9.html#%_idx_354") );
  schememap.set( T("tan"), T("r5rs-Z-H-9.html#%_idx_322") );
  schememap.set( T("transcript-off"), T("r5rs-Z-H-9.html#%_idx_634") );
  schememap.set( T("transcript-on"), T("r5rs-Z-H-9.html#%_idx_632") );
  schememap.set( T("truncate"), T("r5rs-Z-H-9.html#%_idx_306") );
  schememap.set( T("values"), T("r5rs-Z-H-9.html#%_idx_572") );
  schememap.set( T("vector"), T("r5rs-Z-H-9.html#%_idx_540") );
  schememap.set( T("vector->list"), T("r5rs-Z-H-9.html#%_idx_548") );
  schememap.set( T("vector-fill!"), T("r5rs-Z-H-9.html#%_idx_552") );
  schememap.set( T("vector-length"), T("r5rs-Z-H-9.html#%_idx_542") );
  schememap.set( T("vector-ref"), T("r5rs-Z-H-9.html#%_idx_544") );
  schememap.set( T("vector-set!"), T("r5rs-Z-H-9.html#%_idx_546") );
  schememap.set( T("vector?"), T("r5rs-Z-H-6.html#%_idx_58") );
  schememap.set( T("with-input-from-file"), T("r5rs-Z-H-9.html#%_idx_600") );
  schememap.set( T("with-output-to-file"), T("r5rs-Z-H-9.html#%_idx_602") );
  schememap.set( T("write"), T("r5rs-Z-H-9.html#%_idx_622") );
  schememap.set( T("write-char"), T("r5rs-Z-H-9.html#%_idx_628") );
  schememap.set( T("#x"), T("r5rs-Z-H-9.html#%_idx_234") );
  schememap.set( T("zero?"), T("r5rs-Z-H-9.html#%_idx_264") );
#endif
}

void SymbolHelp::addCommonMusicHelp() {
  maproots.set( T("CommonMusic"), T("http://commonmusic.sf.net/doc/dict/") );
}

void SymbolHelp::addCommonLispMusicHelp() {
  maproots.set( T("CommonLispMusic"), T("http://ccrma.stanford.edu/software/snd/snd/") );
}

void SymbolHelp::addFomusHelp() {
  maproots.set( T("Fomus"), T("http://common-lisp.net/project/fomus/doc/") );
}

void SymbolHelp::addCommonLispHelp() {
  maproots.set( T("CommonLisp"), T("http://www.lisp.org/HyperSpec/Body/"));
#ifndef SCHEME
  clmap.set( T("&allow-other-keys"), T("sec_3-4-1.html#AMallow-other-keys"));
  clmap.set( T("&aux"), T("sec_3-4-1.html#AMaux"));
  clmap.set( T("&body"), T("sec_3-4-4.html#AMbody"));
  clmap.set( T("&environment"), T("sec_3-4-4.html#AMenvironment"));
  clmap.set( T("&key"), T("sec_3-4-1.html#AMkey"));
  clmap.set( T("&optional"), T("sec_3-4-1.html#AMoptional"));
  clmap.set( T("&rest"), T("sec_3-4-1.html#AMrest"));
  clmap.set( T("&whole"), T("sec_3-4-4.html#AMwhole"));
  clmap.set( T("*"), T("any_st.html#ST"));
  clmap.set( T("**"), T("var_stcm_ststcm_ststst.html#STST"));
  clmap.set( T("***"), T("var_stcm_ststcm_ststst.html#STSTST"));
  clmap.set( T("*break-on-signals*"), T("var_stbreak-on-signalsst.html#STbreak-on-signalsST"));
  clmap.set( T("*compile-file-pathname*"), T("var_stcompile_e-truenamest.html#STcompile-file-pathnameST"));
  clmap.set( T("*compile-file-truename*"), T("var_stcompile_e-truenamest.html#STcompile-file-truenameST"));
  clmap.set( T("*compile-print*"), T("var_stcompile_le-verbosest.html#STcompile-printST"));
  clmap.set( T("*compile-verbose*"), T("var_stcompile_le-verbosest.html#STcompile-verboseST"));
  clmap.set( T("*debug-io*"), T("var_stdebug-i_ace-outputst.html#STdebug-ioST"));
  clmap.set( T("*debugger-hook*"), T("var_stdebugger-hookst.html#STdebugger-hookST"));
  clmap.set( T("*default-pathname-defaults*"), T("var_stdefault_e-defaultsst.html#STdefault-pathname-defaultsST"));
  clmap.set( T("*error-output*"), T("var_stdebug-i_ace-outputst.html#STerror-outputST"));
  clmap.set( T("*features*"), T("var_stfeaturesst.html#STfeaturesST"));
  clmap.set( T("*gensym-counter*"), T("var_stgensym-counterst.html#STgensym-counterST"));
  clmap.set( T("*load-pathname*"), T("var_stload-pa_d-truenamest.html#STload-pathnameST"));
  clmap.set( T("*load-print*"), T("var_stload-pr_ad-verbosest.html#STload-printST"));
  clmap.set( T("*load-truename*"), T("var_stload-pa_d-truenamest.html#STload-truenameST"));
  clmap.set( T("*load-verbose*"), T("var_stload-pr_ad-verbosest.html#STload-verboseST"));
  clmap.set( T("*macroexpand-hook*"), T("var_stmacroexpand-hookst.html#STmacroexpand-hookST"));
  clmap.set( T("*modules*"), T("var_stmodulesst.html#STmodulesST"));
  clmap.set( T("*package*"), T("var_stpackagest.html#STpackageST"));
  clmap.set( T("*print-array*"), T("var_stprint-arrayst.html#STprint-arrayST"));
  clmap.set( T("*print-base*"), T("var_stprint-b_rint-radixst.html#STprint-baseST"));
  clmap.set( T("*print-case*"), T("var_stprint-casest.html#STprint-caseST"));
  clmap.set( T("*print-circle*"), T("var_stprint-circlest.html#STprint-circleST"));
  clmap.set( T("*print-escape*"), T("var_stprint-escapest.html#STprint-escapeST"));
  clmap.set( T("*print-gensym*"), T("var_stprint-gensymst.html#STprint-gensymST"));
  clmap.set( T("*print-length*"), T("var_stprint-l_int-lengthst.html#STprint-lengthST"));
  clmap.set( T("*print-level*"), T("var_stprint-l_int-lengthst.html#STprint-levelST"));
  clmap.set( T("*print-lines*"), T("var_stprint-linesst.html#STprint-linesST"));
  clmap.set( T("*print-miser-width*"), T("var_stprint-miser-widthst.html#STprint-miser-widthST"));
  clmap.set( T("*print-pprint-dispatch*"), T("var_stprint-p_t-dispatchst.html#STprint-pprint-dispatchST"));
  clmap.set( T("*print-pretty*"), T("var_stprint-prettyst.html#STprint-prettyST"));
  clmap.set( T("*print-radix*"), T("var_stprint-b_rint-radixst.html#STprint-radixST"));
  clmap.set( T("*print-readably*"), T("var_stprint-readablyst.html#STprint-readablyST"));
  clmap.set( T("*print-right-margin*"), T("var_stprint-right-marginst.html#STprint-right-marginST"));
  clmap.set( T("*query-io*"), T("var_stdebug-i_ace-outputst.html#STquery-ioST"));
  clmap.set( T("*random-state*"), T("var_strandom-statest.html#STrandom-stateST"));
  clmap.set( T("*read-base*"), T("var_stread-basest.html#STread-baseST"));
  clmap.set( T("*read-default-float-format*"), T("var_stread-de_oat-formatst.html#STread-default-float-formatST"));
  clmap.set( T("*read-eval*"), T("var_stread-evalst.html#STread-evalST"));
  clmap.set( T("*read-suppress*"), T("var_stread-suppressst.html#STread-suppressST"));
  clmap.set( T("*readtable*"), T("var_streadtablest.html#STreadtableST"));
  clmap.set( T("*standard-input*"), T("var_stdebug-i_ace-outputst.html#STstandard-inputST"));
  clmap.set( T("*standard-output*"), T("var_stdebug-i_ace-outputst.html#STstandard-outputST"));
  clmap.set( T("*terminal-io*"), T("var_stterminal-iost.html#STterminal-ioST"));
  clmap.set( T("*trace-output*"), T("var_stdebug-i_ace-outputst.html#STtrace-outputST"));
  clmap.set( T("+"), T("any_pl.html#PL"));
  clmap.set( T("++"), T("var_plcm_plplcm_plplpl.html#PLPL"));
  clmap.set( T("+++"), T("var_plcm_plplcm_plplpl.html#PLPLPL"));
  clmap.set( T("-"), T("any_-.html#-"));
  clmap.set( T("/"), T("any_sl.html#SL"));
  clmap.set( T("//"), T("var_slcm_slslcm_slslsl.html#SLSL"));
  clmap.set( T("///"), T("var_slcm_slslcm_slslsl.html#SLSLSL"));
  clmap.set( T("/="), T("fun_eqcm_sleq__lteqcm_gteq.html#SLEQ"));
  clmap.set( T("1+"), T("fun_1plcm_1-.html#1PL"));
  clmap.set( T("1-"), T("fun_1plcm_1-.html#1-"));
  clmap.set( T("&lt;"), T("fun_eqcm_sleq__lteqcm_gteq.html#LT"));
  clmap.set( T("&lt;="), T("fun_eqcm_sleq__lteqcm_gteq.html#LTEQ"));
  clmap.set( T("="), T("fun_eqcm_sleq__lteqcm_gteq.html#EQ"));
  clmap.set( T("&gt;"), T("fun_eqcm_sleq__lteqcm_gteq.html#GT"));
  clmap.set( T("&gt;="), T("fun_eqcm_sleq__lteqcm_gteq.html#GTEQ"));
  clmap.set( T("abort"), T("any_abort.html#abort"));
  clmap.set( T("abs"), T("fun_abs.html#abs"));
  clmap.set( T("acons"), T("fun_acons.html#acons"));
  clmap.set( T("acos"), T("fun_asincm_acoscm_atan.html#acos"));
  clmap.set( T("acosh"), T("fun_sinhcm_co_coshcm_atanh.html#acosh"));
  clmap.set( T("add-method"), T("stagenfun_add-method.html#add-method"));
  clmap.set( T("adjoin"), T("fun_adjoin.html#adjoin"));
  clmap.set( T("adjust-array"), T("fun_adjust-array.html#adjust-array"));
  clmap.set( T("adjustable-array-p"), T("fun_adjustable-array-p.html#adjustable-array-p"));
  clmap.set( T("allocate-instance"), T("stagenfun_all_ate-instance.html#allocate-instance"));
  clmap.set( T("alpha-char-p"), T("fun_alpha-char-p.html#alpha-char-p"));
  clmap.set( T("alphanumericp"), T("fun_alphanumericp.html#alphanumericp"));
  clmap.set( T("and"), T("any_and.html#and"));
  clmap.set( T("append"), T("fun_append.html#append"));
  clmap.set( T("apply"), T("fun_apply.html#apply"));
  clmap.set( T("apropos"), T("fun_aproposcm_apropos-list.html#apropos"));
  clmap.set( T("apropos-list"), T("fun_aproposcm_apropos-list.html#apropos-list"));
  clmap.set( T("aref"), T("acc_aref.html#aref"));
  clmap.set( T("arithmetic-error"), T("contyp_arithmetic-error.html#arithmetic-error"));
  clmap.set( T("arithmetic-error-operands"), T("fun_arithmeti_or-operation.html#arithmetic-error-operands"));
  clmap.set( T("arithmetic-error-operation"), T("fun_arithmeti_or-operation.html#arithmetic-error-operation"));
  clmap.set( T("array"), T("syscla_array.html#array"));
  clmap.set( T("array-dimension"), T("fun_array-dimension.html#array-dimension"));
  clmap.set( T("array-dimension-limit"), T("convar_array-_ension-limit.html#array-dimension-limit"));
  clmap.set( T("array-dimensions"), T("fun_array-dimensions.html#array-dimensions"));
  clmap.set( T("array-displacement"), T("fun_array-displacement.html#array-displacement"));
  clmap.set( T("array-element-type"), T("fun_array-element-type.html#array-element-type"));
  clmap.set( T("array-has-fill-pointer-p"), T("fun_array-has_ll-pointer-p.html#array-has-fill-pointer-p"));
  clmap.set( T("array-in-bounds-p"), T("fun_array-in-bounds-p.html#array-in-bounds-p"));
  clmap.set( T("array-rank"), T("fun_array-rank.html#array-rank"));
  clmap.set( T("array-rank-limit"), T("convar_array-rank-limit.html#array-rank-limit"));
  clmap.set( T("array-row-major-index"), T("fun_array-row-major-index.html#array-row-major-index"));
  clmap.set( T("array-total-size"), T("fun_array-total-size.html#array-total-size"));
  clmap.set( T("array-total-size-limit"), T("convar_array-_l-size-limit.html#array-total-size-limit"));
  clmap.set( T("arrayp"), T("fun_arrayp.html#arrayp"));
  clmap.set( T("ash"), T("fun_ash.html#ash"));
  clmap.set( T("asin"), T("fun_asincm_acoscm_atan.html#asin"));
  clmap.set( T("asinh"), T("fun_sinhcm_co_coshcm_atanh.html#asinh"));
  clmap.set( T("assert"), T("mac_assert.html#assert"));
  clmap.set( T("assoc"), T("fun_assoccm_a_assoc-if-not.html#assoc"));
  clmap.set( T("assoc-if"), T("fun_assoccm_a_assoc-if-not.html#assoc-if"));
  clmap.set( T("assoc-if-not"), T("fun_assoccm_a_assoc-if-not.html#assoc-if-not"));
  clmap.set( T("atan"), T("fun_asincm_acoscm_atan.html#atan"));
  clmap.set( T("atanh"), T("fun_sinhcm_co_coshcm_atanh.html#atanh"));
  clmap.set( T("atom"), T("any_atom.html#atom"));
  clmap.set( T("base-char"), T("typ_base-char.html#base-char"));
  clmap.set( T("base-string"), T("typ_base-string.html#base-string"));
  clmap.set( T("bignum"), T("typ_bignum.html#bignum"));
  clmap.set( T("bit"), T("any_bit.html#bit"));
  clmap.set( T("bit-and"), T("fun_bit-andcm_c2cm_bit-xor.html#bit-and"));
  clmap.set( T("bit-andc1"), T("fun_bit-andcm_c2cm_bit-xor.html#bit-andc1"));
  clmap.set( T("bit-andc2"), T("fun_bit-andcm_c2cm_bit-xor.html#bit-andc2"));
  clmap.set( T("bit-eqv"), T("fun_bit-andcm_c2cm_bit-xor.html#bit-eqv"));
  clmap.set( T("bit-ior"), T("fun_bit-andcm_c2cm_bit-xor.html#bit-ior"));
  clmap.set( T("bit-nand"), T("fun_bit-andcm_c2cm_bit-xor.html#bit-nand"));
  clmap.set( T("bit-nor"), T("fun_bit-andcm_c2cm_bit-xor.html#bit-nor"));
  clmap.set( T("bit-not"), T("fun_bit-andcm_c2cm_bit-xor.html#bit-not"));
  clmap.set( T("bit-orc1"), T("fun_bit-andcm_c2cm_bit-xor.html#bit-orc1"));
  clmap.set( T("bit-orc2"), T("fun_bit-andcm_c2cm_bit-xor.html#bit-orc2"));
  clmap.set( T("bit-vector"), T("syscla_bit-vector.html#bit-vector"));
  clmap.set( T("bit-vector-p"), T("fun_bit-vector-p.html#bit-vector-p"));
  clmap.set( T("bit-xor"), T("fun_bit-andcm_c2cm_bit-xor.html#bit-xor"));
  clmap.set( T("block"), T("speope_block.html#block"));
  clmap.set( T("boole"), T("fun_boole.html#boole"));
  clmap.set( T("boole-1"), T("convar_boole-_cm_boole-xor.html#boole-1"));
  clmap.set( T("boole-2"), T("convar_boole-_cm_boole-xor.html#boole-2"));
  clmap.set( T("boole-and"), T("convar_boole-_cm_boole-xor.html#boole-and"));
  clmap.set( T("boole-andc1"), T("convar_boole-_cm_boole-xor.html#boole-andc1"));
  clmap.set( T("boole-andc2"), T("convar_boole-_cm_boole-xor.html#boole-andc2"));
  clmap.set( T("boole-c1"), T("convar_boole-_cm_boole-xor.html#boole-c1"));
  clmap.set( T("boole-c2"), T("convar_boole-_cm_boole-xor.html#boole-c2"));
  clmap.set( T("boole-clr"), T("convar_boole-_cm_boole-xor.html#boole-clr"));
  clmap.set( T("boole-eqv"), T("convar_boole-_cm_boole-xor.html#boole-eqv"));
  clmap.set( T("boole-ior"), T("convar_boole-_cm_boole-xor.html#boole-ior"));
  clmap.set( T("boole-nand"), T("convar_boole-_cm_boole-xor.html#boole-nand"));
  clmap.set( T("boole-nor"), T("convar_boole-_cm_boole-xor.html#boole-nor"));
  clmap.set( T("boole-orc1"), T("convar_boole-_cm_boole-xor.html#boole-orc1"));
  clmap.set( T("boole-orc2"), T("convar_boole-_cm_boole-xor.html#boole-orc2"));
  clmap.set( T("boole-set"), T("convar_boole-_cm_boole-xor.html#boole-set"));
  clmap.set( T("boole-xor"), T("convar_boole-_cm_boole-xor.html#boole-xor"));
  clmap.set( T("boolean"), T("typ_boolean.html#boolean"));
  clmap.set( T("both-case-p"), T("fun_upper-cas__both-case-p.html#both-case-p"));
  clmap.set( T("boundp"), T("fun_boundp.html#boundp"));
  clmap.set( T("break"), T("fun_break.html#break"));
  clmap.set( T("broadcast-stream"), T("syscla_broadcast-stream.html#broadcast-stream"));
  clmap.set( T("broadcast-stream-streams"), T("fun_broadcast_ream-streams.html#broadcast-stream-streams"));
  clmap.set( T("built-in-class"), T("syscla_built-in-class.html#built-in-class"));
  clmap.set( T("butlast"), T("fun_butlastcm_nbutlast.html#butlast"));
  clmap.set( T("byte"), T("fun_bytecm_by_yte-position.html#byte"));
  clmap.set( T("byte-position"), T("fun_bytecm_by_yte-position.html#byte-position"));
  clmap.set( T("byte-size"), T("fun_bytecm_by_yte-position.html#byte-size"));
  clmap.set( T("caaaar"), T("acc_carcm_cdr_darcm_cddddr.html#caaaar"));
  clmap.set( T("caaadr"), T("acc_carcm_cdr_darcm_cddddr.html#caaadr"));
  clmap.set( T("caaar"), T("acc_carcm_cdr_darcm_cddddr.html#caaar"));
  clmap.set( T("caadar"), T("acc_carcm_cdr_darcm_cddddr.html#caadar"));
  clmap.set( T("caaddr"), T("acc_carcm_cdr_darcm_cddddr.html#caaddr"));
  clmap.set( T("caadr"), T("acc_carcm_cdr_darcm_cddddr.html#caadr"));
  clmap.set( T("caar"), T("acc_carcm_cdr_darcm_cddddr.html#caar"));
  clmap.set( T("cadaar"), T("acc_carcm_cdr_darcm_cddddr.html#cadaar"));
  clmap.set( T("cadadr"), T("acc_carcm_cdr_darcm_cddddr.html#cadadr"));
  clmap.set( T("cadar"), T("acc_carcm_cdr_darcm_cddddr.html#cadar"));
  clmap.set( T("caddar"), T("acc_carcm_cdr_darcm_cddddr.html#caddar"));
  clmap.set( T("cadddr"), T("acc_carcm_cdr_darcm_cddddr.html#cadddr"));
  clmap.set( T("caddr"), T("acc_carcm_cdr_darcm_cddddr.html#caddr"));
  clmap.set( T("cadr"), T("acc_carcm_cdr_darcm_cddddr.html#cadr"));
  clmap.set( T("call-arguments-limit"), T("convar_call-a_uments-limit.html#call-arguments-limit"));
  clmap.set( T("call-method"), T("locmac_call-m__make-method.html#call-method"));
  clmap.set( T("call-next-method"), T("locfun_call-next-method.html#call-next-method"));
  clmap.set( T("car"), T("acc_carcm_cdr_darcm_cddddr.html#car"));
  clmap.set( T("case"), T("mac_casecm_ccasecm_ecase.html#case"));
  clmap.set( T("catch"), T("speope_catch.html#catch"));
  clmap.set( T("ccase"), T("mac_casecm_ccasecm_ecase.html#ccase"));
  clmap.set( T("cdaaar"), T("acc_carcm_cdr_darcm_cddddr.html#cdaaar"));
  clmap.set( T("cdaadr"), T("acc_carcm_cdr_darcm_cddddr.html#cdaadr"));
  clmap.set( T("cdaar"), T("acc_carcm_cdr_darcm_cddddr.html#cdaar"));
  clmap.set( T("cdadar"), T("acc_carcm_cdr_darcm_cddddr.html#cdadar"));
  clmap.set( T("cdaddr"), T("acc_carcm_cdr_darcm_cddddr.html#cdaddr"));
  clmap.set( T("cdadr"), T("acc_carcm_cdr_darcm_cddddr.html#cdadr"));
  clmap.set( T("cdar"), T("acc_carcm_cdr_darcm_cddddr.html#cdar"));
  clmap.set( T("cddaar"), T("acc_carcm_cdr_darcm_cddddr.html#cddaar"));
  clmap.set( T("cddadr"), T("acc_carcm_cdr_darcm_cddddr.html#cddadr"));
  clmap.set( T("cddar"), T("acc_carcm_cdr_darcm_cddddr.html#cddar"));
  clmap.set( T("cdddar"), T("acc_carcm_cdr_darcm_cddddr.html#cdddar"));
  clmap.set( T("cddddr"), T("acc_carcm_cdr_darcm_cddddr.html#cddddr"));
  clmap.set( T("cdddr"), T("acc_carcm_cdr_darcm_cddddr.html#cdddr"));
  clmap.set( T("cddr"), T("acc_carcm_cdr_darcm_cddddr.html#cddr"));
  clmap.set( T("cdr"), T("acc_carcm_cdr_darcm_cddddr.html#cdr"));
  clmap.set( T("ceiling"), T("fun_floorcm_f_undcm_fround.html#ceiling"));
  clmap.set( T("cell-error"), T("contyp_cell-error.html#cell-error"));
  clmap.set( T("cell-error-name"), T("fun_cell-error-name.html#cell-error-name"));
  clmap.set( T("cerror"), T("fun_cerror.html#cerror"));
  clmap.set( T("change-class"), T("stagenfun_change-class.html#change-class"));
  clmap.set( T("char"), T("acc_charcm_schar.html#char"));
  clmap.set( T("char-code"), T("fun_char-code.html#char-code"));
  clmap.set( T("char-code-limit"), T("convar_char-code-limit.html#char-code-limit"));
  clmap.set( T("char-downcase"), T("fun_char-upca_har-downcase.html#char-downcase"));
  clmap.set( T("char-equal"), T("fun_chareqcm__ar-not-lessp.html#char-equal"));
  clmap.set( T("char-greaterp"), T("fun_chareqcm__ar-not-lessp.html#char-greaterp"));
  clmap.set( T("char-int"), T("fun_char-int.html#char-int"));
  clmap.set( T("char-lessp"), T("fun_chareqcm__ar-not-lessp.html#char-lessp"));
  clmap.set( T("char-name"), T("fun_char-name.html#char-name"));
  clmap.set( T("char-not-equal"), T("fun_chareqcm__ar-not-lessp.html#char-not-equal"));
  clmap.set( T("char-not-greaterp"), T("fun_chareqcm__ar-not-lessp.html#char-not-greaterp"));
  clmap.set( T("char-not-lessp"), T("fun_chareqcm__ar-not-lessp.html#char-not-lessp"));
  clmap.set( T("char-upcase"), T("fun_char-upca_har-downcase.html#char-upcase"));
  clmap.set( T("char/="), T("fun_chareqcm__ar-not-lessp.html#charSLEQ"));
  clmap.set( T("char&lt;"), T("fun_chareqcm__ar-not-lessp.html#charLT"));
  clmap.set( T("char&lt;="), T("fun_chareqcm__ar-not-lessp.html#charLTEQ"));
  clmap.set( T("char="), T("fun_chareqcm__ar-not-lessp.html#charEQ"));
  clmap.set( T("char&gt;"), T("fun_chareqcm__ar-not-lessp.html#charGT"));
  clmap.set( T("char&gt;="), T("fun_chareqcm__ar-not-lessp.html#charGTEQ"));
  clmap.set( T("character"), T("any_character.html#character"));
  clmap.set( T("characterp"), T("fun_characterp.html#characterp"));
  clmap.set( T("check-type"), T("mac_check-type.html#check-type"));
  clmap.set( T("cis"), T("fun_cis.html#cis"));
  clmap.set( T("class"), T("syscla_class.html#class"));
  clmap.set( T("class-name"), T("stagenfun_class-name.html#class-name"));
  clmap.set( T("class-of"), T("fun_class-of.html#class-of"));
  clmap.set( T("clear-input"), T("fun_clear-input.html#clear-input"));
  clmap.set( T("clear-output"), T("fun_finish-ou_clear-output.html#clear-output"));
  clmap.set( T("close"), T("fun_close.html#close"));
  clmap.set( T("clrhash"), T("fun_clrhash.html#clrhash"));
  clmap.set( T("code-char"), T("fun_code-char.html#code-char"));
  clmap.set( T("coerce"), T("fun_coerce.html#coerce"));
  clmap.set( T("compilation-speed"), T("dec_optimize.html#compilation-speed"));
  clmap.set( T("compile"), T("fun_compile.html#compile"));
  clmap.set( T("compile-file"), T("fun_compile-file.html#compile-file"));
  clmap.set( T("compile-file-pathname"), T("fun_compile-file-pathname.html#compile-file-pathname"));
  clmap.set( T("compiled-function"), T("typ_compiled-function.html#compiled-function"));
  clmap.set( T("compiled-function-p"), T("fun_compiled-function-p.html#compiled-function-p"));
  clmap.set( T("compiler-macro"), T("stagenfun_doc_umentationcp.html#compiler-macro"));
  clmap.set( T("compiler-macro-function"), T("acc_compiler-_cro-function.html#compiler-macro-function"));
  clmap.set( T("complement"), T("fun_complement.html#complement"));
  clmap.set( T("complex"), T("any_complex.html#complex"));
  clmap.set( T("complexp"), T("fun_complexp.html#complexp"));
  clmap.set( T("compute-applicable-methods"), T("stagenfun_com_able-methods.html#compute-applicable-methods"));
  clmap.set( T("compute-restarts"), T("fun_compute-restarts.html#compute-restarts"));
  clmap.set( T("concatenate"), T("fun_concatenate.html#concatenate"));
  clmap.set( T("concatenated-stream"), T("syscla_concatenated-stream.html#concatenated-stream"));
  clmap.set( T("concatenated-stream-streams"), T("fun_concatena_ream-streams.html#concatenated-stream-streams"));
  clmap.set( T("cond"), T("mac_cond.html#cond"));
  clmap.set( T("condition"), T("contyp_condition.html#condition"));
  clmap.set( T("conjugate"), T("fun_conjugate.html#conjugate"));
  clmap.set( T("cons"), T("any_cons.html#cons"));
  clmap.set( T("consp"), T("fun_consp.html#consp"));
  clmap.set( T("constantly"), T("fun_constantly.html#constantly"));
  clmap.set( T("constantp"), T("fun_constantp.html#constantp"));
  clmap.set( T("continue"), T("any_continue.html#continue"));
  clmap.set( T("control-error"), T("contyp_control-error.html#control-error"));
  clmap.set( T("copy-alist"), T("fun_copy-alist.html#copy-alist"));
  clmap.set( T("copy-list"), T("fun_copy-list.html#copy-list"));
  clmap.set( T("copy-pprint-dispatch"), T("fun_copy-pprint-dispatch.html#copy-pprint-dispatch"));
  clmap.set( T("copy-readtable"), T("fun_copy-readtable.html#copy-readtable"));
  clmap.set( T("copy-seq"), T("fun_copy-seq.html#copy-seq"));
  clmap.set( T("copy-structure"), T("fun_copy-structure.html#copy-structure"));
  clmap.set( T("copy-symbol"), T("fun_copy-symbol.html#copy-symbol"));
  clmap.set( T("copy-tree"), T("fun_copy-tree.html#copy-tree"));
  clmap.set( T("cos"), T("fun_sincm_coscm_tan.html#cos"));
  clmap.set( T("cosh"), T("fun_sinhcm_co_coshcm_atanh.html#cosh"));
  clmap.set( T("count"), T("fun_countcm_c_count-if-not.html#count"));
  clmap.set( T("count-if"), T("fun_countcm_c_count-if-not.html#count-if"));
  clmap.set( T("count-if-not"), T("fun_countcm_c_count-if-not.html#count-if-not"));
  clmap.set( T("ctypecase"), T("mac_typecasec_cm_etypecase.html#ctypecase"));
  clmap.set( T("debug"), T("dec_optimize.html#debug"));
  clmap.set( T("decf"), T("mac_incfcm_decf.html#decf"));
  clmap.set( T("declaim"), T("mac_declaim.html#declaim"));
  clmap.set( T("declaration"), T("dec_declaration.html#declaration"));
  clmap.set( T("declare"), T("sym_declare.html#declare"));
  clmap.set( T("decode-float"), T("fun_decode-fl_decode-float.html#decode-float"));
  clmap.set( T("decode-universal-time"), T("fun_decode-universal-time.html#decode-universal-time"));
  clmap.set( T("defclass"), T("mac_defclass.html#defclass"));
  clmap.set( T("defconstant"), T("mac_defconstant.html#defconstant"));
  clmap.set( T("defgeneric"), T("mac_defgeneric.html#defgeneric"));
  clmap.set( T("define-compiler-macro"), T("mac_define-compiler-macro.html#define-compiler-macro"));
  clmap.set( T("define-condition"), T("mac_define-condition.html#define-condition"));
  clmap.set( T("define-method-combination"), T("mac_define-me_-combination.html#define-method-combination"));
  clmap.set( T("define-modify-macro"), T("mac_define-modify-macro.html#define-modify-macro"));
  clmap.set( T("define-setf-expander"), T("mac_define-setf-expander.html#define-setf-expander"));
  clmap.set( T("define-symbol-macro"), T("mac_define-symbol-macro.html#define-symbol-macro"));
  clmap.set( T("defmacro"), T("mac_defmacro.html#defmacro"));
  clmap.set( T("defmethod"), T("mac_defmethod.html#defmethod"));
  clmap.set( T("defpackage"), T("mac_defpackage.html#defpackage"));
  clmap.set( T("defparameter"), T("mac_defparametercm_defvar.html#defparameter"));
  clmap.set( T("defsetf"), T("mac_defsetf.html#defsetf"));
  clmap.set( T("defstruct"), T("mac_defstruct.html#defstruct"));
  clmap.set( T("deftype"), T("mac_deftype.html#deftype"));
  clmap.set( T("defun"), T("mac_defun.html#defun"));
  clmap.set( T("defvar"), T("mac_defparametercm_defvar.html#defvar"));
  clmap.set( T("delete"), T("fun_removecm__elete-if-not.html#delete"));
  clmap.set( T("delete-duplicates"), T("fun_remove-du_e-duplicates.html#delete-duplicates"));
  clmap.set( T("delete-file"), T("fun_delete-file.html#delete-file"));
  clmap.set( T("delete-if"), T("fun_removecm__elete-if-not.html#delete-if"));
  clmap.set( T("delete-if-not"), T("fun_removecm__elete-if-not.html#delete-if-not"));
  clmap.set( T("delete-package"), T("fun_delete-package.html#delete-package"));
  clmap.set( T("denominator"), T("fun_numerator__denominator.html#denominator"));
  clmap.set( T("deposit-field"), T("fun_deposit-field.html#deposit-field"));
  clmap.set( T("describe"), T("fun_describe.html#describe"));
  clmap.set( T("describe-object"), T("stagenfun_describe-object.html#describe-object"));
  clmap.set( T("destructuring-bind"), T("mac_destructuring-bind.html#destructuring-bind"));
  clmap.set( T("digit-char"), T("fun_digit-char.html#digit-char"));
  clmap.set( T("digit-char-p"), T("fun_digit-char-p.html#digit-char-p"));
  clmap.set( T("directory"), T("fun_directory.html#directory"));
  clmap.set( T("directory-namestring"), T("fun_namestrin_h-namestring.html#directory-namestring"));
  clmap.set( T("disassemble"), T("fun_disassemble.html#disassemble"));
  clmap.set( T("division-by-zero"), T("contyp_division-by-zero.html#division-by-zero"));
  clmap.set( T("do"), T("mac_docm_dost.html#do"));
  clmap.set( T("do*"), T("mac_docm_dost.html#doST"));
  clmap.set( T("do-all-symbols"), T("mac_do-symbol_-all-symbols.html#do-all-symbols"));
  clmap.set( T("do-external-symbols"), T("mac_do-symbol_-all-symbols.html#do-external-symbols"));
  clmap.set( T("do-symbols"), T("mac_do-symbol_-all-symbols.html#do-symbols"));
  clmap.set( T("documentation"), T("stagenfun_doc_umentationcp.html#documentation"));
  clmap.set( T("dolist"), T("mac_dolist.html#dolist"));
  clmap.set( T("dotimes"), T("mac_dotimes.html#dotimes"));
  clmap.set( T("double-float"), T("typ_short-flo_m_long-float.html#double-float"));
  clmap.set( T("double-float-epsilon"), T("convar_short-_tive-epsilon.html#double-float-epsilon"));
  clmap.set( T("double-float-negative-epsilon"), T("convar_short-_tive-epsilon.html#double-float-negative-epsilon"));
  clmap.set( T("dpb"), T("fun_dpb.html#dpb"));
  clmap.set( T("dribble"), T("fun_dribble.html#dribble"));
  clmap.set( T("dynamic-extent"), T("dec_dynamic-extent.html#dynamic-extent"));
  clmap.set( T("ecase"), T("mac_casecm_ccasecm_ecase.html#ecase"));
  clmap.set( T("echo-stream"), T("syscla_echo-stream.html#echo-stream"));
  clmap.set( T("echo-stream-input-stream"), T("fun_echo-stre_utput-stream.html#echo-stream-input-stream"));
  clmap.set( T("echo-stream-output-stream"), T("fun_echo-stre_utput-stream.html#echo-stream-output-stream"));
  clmap.set( T("ed"), T("fun_ed.html#ed"));
  clmap.set( T("eighth"), T("acc_firstcm_s_inthcm_tenth.html#eighth"));
  clmap.set( T("elt"), T("acc_elt.html#elt"));
  clmap.set( T("encode-universal-time"), T("fun_encode-universal-time.html#encode-universal-time"));
  clmap.set( T("end-of-file"), T("contyp_end-of-file.html#end-of-file"));
  clmap.set( T("endp"), T("fun_endp.html#endp"));
  clmap.set( T("enough-namestring"), T("fun_namestrin_h-namestring.html#enough-namestring"));
  clmap.set( T("ensure-directories-exist"), T("fun_ensure-di_tories-exist.html#ensure-directories-exist"));
  clmap.set( T("ensure-generic-function"), T("fun_ensure-ge_ric-function.html#ensure-generic-function"));
  clmap.set( T("eq"), T("fun_eq.html#eq"));
  clmap.set( T("eql"), T("any_eql.html#eql"));
  clmap.set( T("equal"), T("fun_equal.html#equal"));
  clmap.set( T("equalp"), T("fun_equalp.html#equalp"));
  clmap.set( T("error"), T("any_error.html#error"));
  clmap.set( T("etypecase"), T("mac_typecasec_cm_etypecase.html#etypecase"));
  clmap.set( T("eval"), T("fun_eval.html#eval"));
  clmap.set( T("eval-when"), T("speope_eval-when.html#eval-when"));
  clmap.set( T("evenp"), T("fun_evenpcm_oddp.html#evenp"));
  clmap.set( T("every"), T("fun_everycm_s_erycm_notany.html#every"));
  clmap.set( T("exp"), T("fun_expcm_expt.html#exp"));
  clmap.set( T("export"), T("fun_export.html#export"));
  clmap.set( T("expt"), T("fun_expcm_expt.html#expt"));
  clmap.set( T("extended-char"), T("typ_extended-char.html#extended-char"));
  clmap.set( T("fboundp"), T("fun_fboundp.html#fboundp"));
  clmap.set( T("fceiling"), T("fun_floorcm_f_undcm_fround.html#fceiling"));
  clmap.set( T("fdefinition"), T("acc_fdefinition.html#fdefinition"));
  clmap.set( T("ffloor"), T("fun_floorcm_f_undcm_fround.html#ffloor"));
  clmap.set( T("fifth"), T("acc_firstcm_s_inthcm_tenth.html#fifth"));
  clmap.set( T("file-author"), T("fun_file-author.html#file-author"));
  clmap.set( T("file-error"), T("contyp_file-error.html#file-error"));
  clmap.set( T("file-error-pathname"), T("fun_file-error-pathname.html#file-error-pathname"));
  clmap.set( T("file-length"), T("fun_file-length.html#file-length"));
  clmap.set( T("file-namestring"), T("fun_namestrin_h-namestring.html#file-namestring"));
  clmap.set( T("file-position"), T("fun_file-position.html#file-position"));
  clmap.set( T("file-stream"), T("syscla_file-stream.html#file-stream"));
  clmap.set( T("file-string-length"), T("fun_file-string-length.html#file-string-length"));
  clmap.set( T("file-write-date"), T("fun_file-write-date.html#file-write-date"));
  clmap.set( T("fill"), T("fun_fill.html#fill"));
  clmap.set( T("fill-pointer"), T("acc_fill-pointer.html#fill-pointer"));
  clmap.set( T("find"), T("fun_findcm_fi__find-if-not.html#find"));
  clmap.set( T("find-all-symbols"), T("fun_find-all-symbols.html#find-all-symbols"));
  clmap.set( T("find-class"), T("acc_find-class.html#find-class"));
  clmap.set( T("find-if"), T("fun_findcm_fi__find-if-not.html#find-if"));
  clmap.set( T("find-if-not"), T("fun_findcm_fi__find-if-not.html#find-if-not"));
  clmap.set( T("find-method"), T("stagenfun_find-method.html#find-method"));
  clmap.set( T("find-package"), T("fun_find-package.html#find-package"));
  clmap.set( T("find-restart"), T("fun_find-restart.html#find-restart"));
  clmap.set( T("find-symbol"), T("fun_find-symbol.html#find-symbol"));
  clmap.set( T("finish-output"), T("fun_finish-ou_clear-output.html#finish-output"));
  clmap.set( T("first"), T("acc_firstcm_s_inthcm_tenth.html#first"));
  clmap.set( T("fixnum"), T("typ_fixnum.html#fixnum"));
  clmap.set( T("flet"), T("speope_fletcm_scm_macrolet.html#flet"));
  clmap.set( T("float"), T("any_float.html#float"));
  clmap.set( T("float-digits"), T("fun_decode-fl_decode-float.html#float-digits"));
  clmap.set( T("float-precision"), T("fun_decode-fl_decode-float.html#float-precision"));
  clmap.set( T("float-radix"), T("fun_decode-fl_decode-float.html#float-radix"));
  clmap.set( T("float-sign"), T("fun_decode-fl_decode-float.html#float-sign"));
  clmap.set( T("floating-point-inexact"), T("contyp_floati_oint-inexact.html#floating-point-inexact"));
  clmap.set( T("floating-point-invalid-operation"), T("contyp_floati_id-operation.html#floating-point-invalid-operation"));
  clmap.set( T("floating-point-overflow"), T("contyp_floati_int-overflow.html#floating-point-overflow"));
  clmap.set( T("floating-point-underflow"), T("contyp_floati_nt-underflow.html#floating-point-underflow"));
  clmap.set( T("floatp"), T("fun_floatp.html#floatp"));
  clmap.set( T("floor"), T("fun_floorcm_f_undcm_fround.html#floor"));
  clmap.set( T("fmakunbound"), T("fun_fmakunbound.html#fmakunbound"));
  clmap.set( T("force-output"), T("fun_finish-ou_clear-output.html#force-output"));
  clmap.set( T("format"), T("fun_format.html#format"));
  clmap.set( T("formatter"), T("mac_formatter.html#formatter"));
  clmap.set( T("fourth"), T("acc_firstcm_s_inthcm_tenth.html#fourth"));
  clmap.set( T("fresh-line"), T("fun_terpricm_fresh-line.html#fresh-line"));
  clmap.set( T("fround"), T("fun_floorcm_f_undcm_fround.html#fround"));
  clmap.set( T("ftruncate"), T("fun_floorcm_f_undcm_fround.html#ftruncate"));
  clmap.set( T("ftype"), T("dec_ftype.html#ftype"));
  clmap.set( T("funcall"), T("fun_funcall.html#funcall"));
  clmap.set( T("function"), T("any_function.html#function"));
  clmap.set( T("function-keywords"), T("stagenfun_fun_ion-keywords.html#function-keywords"));
  clmap.set( T("function-lambda-expression"), T("fun_function-_a-expression.html#function-lambda-expression"));
  clmap.set( T("functionp"), T("fun_functionp.html#functionp"));
  clmap.set( T("gcd"), T("fun_gcd.html#gcd"));
  clmap.set( T("generic-function"), T("syscla_generic-function.html#generic-function"));
  clmap.set( T("gensym"), T("fun_gensym.html#gensym"));
  clmap.set( T("gentemp"), T("fun_gentemp.html#gentemp"));
  clmap.set( T("get"), T("acc_get.html#get"));
  clmap.set( T("get-decoded-time"), T("fun_get-unive_decoded-time.html#get-decoded-time"));
  clmap.set( T("get-dispatch-macro-character"), T("fun_set-dispa_ro-character.html#get-dispatch-macro-character"));
  clmap.set( T("get-internal-real-time"), T("fun_get-internal-real-time.html#get-internal-real-time"));
  clmap.set( T("get-internal-run-time"), T("fun_get-internal-run-time.html#get-internal-run-time"));
  clmap.set( T("get-macro-character"), T("fun_set-macro_ro-character.html#get-macro-character"));
  clmap.set( T("get-output-stream-string"), T("fun_get-outpu_tream-string.html#get-output-stream-string"));
  clmap.set( T("get-properties"), T("fun_get-properties.html#get-properties"));
  clmap.set( T("get-setf-expansion"), T("fun_get-setf-expansion.html#get-setf-expansion"));
  clmap.set( T("get-universal-time"), T("fun_get-unive_decoded-time.html#get-universal-time"));
  clmap.set( T("getf"), T("acc_getf.html#getf"));
  clmap.set( T("gethash"), T("acc_gethash.html#gethash"));
  clmap.set( T("go"), T("speope_go.html#go"));
  clmap.set( T("graphic-char-p"), T("fun_graphic-char-p.html#graphic-char-p"));
  clmap.set( T("handler-bind"), T("mac_handler-bind.html#handler-bind"));
  clmap.set( T("handler-case"), T("mac_handler-case.html#handler-case"));
  clmap.set( T("hash-table"), T("syscla_hash-table.html#hash-table"));
  clmap.set( T("hash-table-count"), T("fun_hash-table-count.html#hash-table-count"));
  clmap.set( T("hash-table-p"), T("fun_hash-table-p.html#hash-table-p"));
  clmap.set( T("hash-table-rehash-size"), T("fun_hash-table-rehash-size.html#hash-table-rehash-size"));
  clmap.set( T("hash-table-rehash-threshold"), T("fun_hash-tabl_sh-threshold.html#hash-table-rehash-threshold"));
  clmap.set( T("hash-table-size"), T("fun_hash-table-size.html#hash-table-size"));
  clmap.set( T("hash-table-test"), T("fun_hash-table-test.html#hash-table-test"));
  clmap.set( T("host-namestring"), T("fun_namestrin_h-namestring.html#host-namestring"));
  clmap.set( T("identity"), T("fun_identity.html#identity"));
  clmap.set( T("if"), T("speope_if.html#if"));
  clmap.set( T("ignorable"), T("dec_ignorecm_ignorable.html#ignorable"));
  clmap.set( T("ignore"), T("dec_ignorecm_ignorable.html#ignore"));
  clmap.set( T("ignore-errors"), T("mac_ignore-errors.html#ignore-errors"));
  clmap.set( T("imagpart"), T("fun_realpartcm_imagpart.html#imagpart"));
  clmap.set( T("import"), T("fun_import.html#import"));
  clmap.set( T("in-package"), T("mac_in-package.html#in-package"));
  clmap.set( T("incf"), T("mac_incfcm_decf.html#incf"));
  clmap.set( T("initialize-instance"), T("stagenfun_ini_ize-instance.html#initialize-instance"));
  clmap.set( T("inline"), T("dec_inlinecm_notinline.html#inline"));
  clmap.set( T("input-stream-p"), T("fun_input-str_put-stream-p.html#input-stream-p"));
  clmap.set( T("inspect"), T("fun_inspect.html#inspect"));
  clmap.set( T("integer"), T("syscla_integer.html#integer"));
  clmap.set( T("integer-decode-float"), T("fun_decode-fl_decode-float.html#integer-decode-float"));
  clmap.set( T("integer-length"), T("fun_integer-length.html#integer-length"));
  clmap.set( T("integerp"), T("fun_integerp.html#integerp"));
  clmap.set( T("interactive-stream-p"), T("fun_interactive-stream-p.html#interactive-stream-p"));
  clmap.set( T("intern"), T("fun_intern.html#intern"));
  clmap.set( T("internal-time-units-per-second"), T("convar_intern_s-per-second.html#internal-time-units-per-second"));
  clmap.set( T("intersection"), T("fun_intersect_intersection.html#intersection"));
  clmap.set( T("invalid-method-error"), T("fun_invalid-method-error.html#invalid-method-error"));
  clmap.set( T("invoke-debugger"), T("fun_invoke-debugger.html#invoke-debugger"));
  clmap.set( T("invoke-restart"), T("fun_invoke-restart.html#invoke-restart"));
  clmap.set( T("invoke-restart-interactively"), T("fun_invoke-re_nteractively.html#invoke-restart-interactively"));
  clmap.set( T("isqrt"), T("fun_sqrtcm_isqrt.html#isqrt"));
  clmap.set( T("keyword"), T("typ_keyword.html#keyword"));
  clmap.set( T("keywordp"), T("fun_keywordp.html#keywordp"));
  clmap.set( T("labels"), T("speope_fletcm_scm_macrolet.html#labels"));
  clmap.set( T("lambda"), T("any_lambda.html#lambda"));
  clmap.set( T("lambda-list-keywords"), T("convar_lambda_ist-keywords.html#lambda-list-keywords"));
  clmap.set( T("lambda-parameters-limit"), T("convar_lambda_meters-limit.html#lambda-parameters-limit"));
  clmap.set( T("last"), T("fun_last.html#last"));
  clmap.set( T("lcm"), T("fun_lcm.html#lcm"));
  clmap.set( T("ldb"), T("acc_ldb.html#ldb"));
  clmap.set( T("ldb-test"), T("fun_ldb-test.html#ldb-test"));
  clmap.set( T("ldiff"), T("fun_ldiffcm_tailp.html#ldiff"));
  clmap.set( T("least-negative-double-float"), T("convar_most-p_d-long-float.html#least-negative-double-float"));
  clmap.set( T("least-negative-long-float"), T("convar_most-p_d-long-float.html#least-negative-long-float"));
  clmap.set( T("least-negative-normalized-double-float"), T("convar_most-p_d-long-float.html#least-negative-normalized-double-float"));
  clmap.set( T("least-negative-normalized-long-float"), T("convar_most-p_d-long-float.html#least-negative-normalized-long-float"));
  clmap.set( T("least-negative-normalized-short-float"), T("convar_most-p_d-long-float.html#least-negative-normalized-short-float"));
  clmap.set( T("least-negative-normalized-single-float"), T("convar_most-p_d-long-float.html#least-negative-normalized-single-float"));
  clmap.set( T("least-negative-short-float"), T("convar_most-p_d-long-float.html#least-negative-short-float"));
  clmap.set( T("least-negative-single-float"), T("convar_most-p_d-long-float.html#least-negative-single-float"));
  clmap.set( T("least-positive-double-float"), T("convar_most-p_d-long-float.html#least-positive-double-float"));
  clmap.set( T("least-positive-long-float"), T("convar_most-p_d-long-float.html#least-positive-long-float"));
  clmap.set( T("least-positive-normalized-double-float"), T("convar_most-p_d-long-float.html#least-positive-normalized-double-float"));
  clmap.set( T("least-positive-normalized-long-float"), T("convar_most-p_d-long-float.html#least-positive-normalized-long-float"));
  clmap.set( T("least-positive-normalized-short-float"), T("convar_most-p_d-long-float.html#least-positive-normalized-short-float"));
  clmap.set( T("least-positive-normalized-single-float"), T("convar_most-p_d-long-float.html#least-positive-normalized-single-float"));
  clmap.set( T("least-positive-short-float"), T("convar_most-p_d-long-float.html#least-positive-short-float"));
  clmap.set( T("least-positive-single-float"), T("convar_most-p_d-long-float.html#least-positive-single-float"));
  clmap.set( T("length"), T("fun_length.html#length"));
  clmap.set( T("let"), T("speope_letcm_letst.html#let"));
  clmap.set( T("let*"), T("speope_letcm_letst.html#letST"));
  clmap.set( T("lisp-implementation-type"), T("fun_lisp-impl_tion-version.html#lisp-implementation-type"));
  clmap.set( T("lisp-implementation-version"), T("fun_lisp-impl_tion-version.html#lisp-implementation-version"));
  clmap.set( T("list"), T("any_list.html#list"));
  clmap.set( T("list*"), T("fun_listcm_listst.html#listST"));
  clmap.set( T("list-all-packages"), T("fun_list-all-packages.html#list-all-packages"));
  clmap.set( T("list-length"), T("fun_list-length.html#list-length"));
  clmap.set( T("listen"), T("fun_listen.html#listen"));
  clmap.set( T("listp"), T("fun_listp.html#listp"));
  clmap.set( T("load"), T("fun_load.html#load"));
  clmap.set( T("load-logical-pathname-translations"), T("fun_load-logi_translations.html#load-logical-pathname-translations"));
  clmap.set( T("load-time-value"), T("speope_load-time-value.html#load-time-value"));
  clmap.set( T("locally"), T("speope_locally.html#locally"));
  clmap.set( T("log"), T("fun_log.html#log"));
  clmap.set( T("logand"), T("fun_logandcm__rc2cm_logxor.html#logand"));
  clmap.set( T("logandc1"), T("fun_logandcm__rc2cm_logxor.html#logandc1"));
  clmap.set( T("logandc2"), T("fun_logandcm__rc2cm_logxor.html#logandc2"));
  clmap.set( T("logbitp"), T("fun_logbitp.html#logbitp"));
  clmap.set( T("logcount"), T("fun_logcount.html#logcount"));
  clmap.set( T("logeqv"), T("fun_logandcm__rc2cm_logxor.html#logeqv"));
  clmap.set( T("logical-pathname"), T("any_logical-pathname.html#logical-pathname"));
  clmap.set( T("logical-pathname-translations"), T("acc_logical-p_translations.html#logical-pathname-translations"));
  clmap.set( T("logior"), T("fun_logandcm__rc2cm_logxor.html#logior"));
  clmap.set( T("lognand"), T("fun_logandcm__rc2cm_logxor.html#lognand"));
  clmap.set( T("lognor"), T("fun_logandcm__rc2cm_logxor.html#lognor"));
  clmap.set( T("lognot"), T("fun_logandcm__rc2cm_logxor.html#lognot"));
  clmap.set( T("logorc1"), T("fun_logandcm__rc2cm_logxor.html#logorc1"));
  clmap.set( T("logorc2"), T("fun_logandcm__rc2cm_logxor.html#logorc2"));
  clmap.set( T("logtest"), T("fun_logtest.html#logtest"));
  clmap.set( T("logxor"), T("fun_logandcm__rc2cm_logxor.html#logxor"));
  clmap.set( T("long-float"), T("typ_short-flo_m_long-float.html#long-float"));
  clmap.set( T("long-float-epsilon"), T("convar_short-_tive-epsilon.html#long-float-epsilon"));
  clmap.set( T("long-float-negative-epsilon"), T("convar_short-_tive-epsilon.html#long-float-negative-epsilon"));
  clmap.set( T("long-site-name"), T("fun_short-sit_ng-site-name.html#long-site-name"));
  clmap.set( T("loop"), T("mac_loop.html#loop"));
  clmap.set( T("loop-finish"), T("locmac_loop-finish.html#loop-finish"));
  clmap.set( T("lower-case-p"), T("fun_upper-cas__both-case-p.html#lower-case-p"));
  clmap.set( T("machine-instance"), T("fun_machine-instance.html#machine-instance"));
  clmap.set( T("machine-type"), T("fun_machine-type.html#machine-type"));
  clmap.set( T("machine-version"), T("fun_machine-version.html#machine-version"));
  clmap.set( T("macro-function"), T("acc_macro-function.html#macro-function"));
  clmap.set( T("macroexpand"), T("fun_macroexpa_acroexpand-1.html#macroexpand"));
  clmap.set( T("macroexpand-1"), T("fun_macroexpa_acroexpand-1.html#macroexpand-1"));
  clmap.set( T("macrolet"), T("speope_fletcm_scm_macrolet.html#macrolet"));
  clmap.set( T("make-array"), T("fun_make-array.html#make-array"));
  clmap.set( T("make-broadcast-stream"), T("fun_make-broadcast-stream.html#make-broadcast-stream"));
  clmap.set( T("make-concatenated-stream"), T("fun_make-conc_nated-stream.html#make-concatenated-stream"));
  clmap.set( T("make-condition"), T("fun_make-condition.html#make-condition"));
  clmap.set( T("make-dispatch-macro-character"), T("fun_make-disp_ro-character.html#make-dispatch-macro-character"));
  clmap.set( T("make-echo-stream"), T("fun_make-echo-stream.html#make-echo-stream"));
  clmap.set( T("make-hash-table"), T("fun_make-hash-table.html#make-hash-table"));
  clmap.set( T("make-instance"), T("stagenfun_make-instance.html#make-instance"));
  clmap.set( T("make-instances-obsolete"), T("stagenfun_mak_ces-obsolete.html#make-instances-obsolete"));
  clmap.set( T("make-list"), T("fun_make-list.html#make-list"));
  clmap.set( T("make-load-form"), T("stagenfun_make-load-form.html#make-load-form"));
  clmap.set( T("make-load-form-saving-slots"), T("fun_make-load_saving-slots.html#make-load-form-saving-slots"));
  clmap.set( T("make-method"), T("locmac_call-m__make-method.html#make-method"));
  clmap.set( T("make-package"), T("fun_make-package.html#make-package"));
  clmap.set( T("make-pathname"), T("fun_make-pathname.html#make-pathname"));
  clmap.set( T("make-random-state"), T("fun_make-random-state.html#make-random-state"));
  clmap.set( T("make-sequence"), T("fun_make-sequence.html#make-sequence"));
  clmap.set( T("make-string"), T("fun_make-string.html#make-string"));
  clmap.set( T("make-string-input-stream"), T("fun_make-stri_input-stream.html#make-string-input-stream"));
  clmap.set( T("make-string-output-stream"), T("fun_make-stri_utput-stream.html#make-string-output-stream"));
  clmap.set( T("make-symbol"), T("fun_make-symbol.html#make-symbol"));
  clmap.set( T("make-synonym-stream"), T("fun_make-synonym-stream.html#make-synonym-stream"));
  clmap.set( T("make-two-way-stream"), T("fun_make-two-way-stream.html#make-two-way-stream"));
  clmap.set( T("makunbound"), T("fun_makunbound.html#makunbound"));
  clmap.set( T("map"), T("fun_map.html#map"));
  clmap.set( T("map-into"), T("fun_map-into.html#map-into"));
  clmap.set( T("mapc"), T("fun_mapccm_ma_istcm_mapcon.html#mapc"));
  clmap.set( T("mapcan"), T("fun_mapccm_ma_istcm_mapcon.html#mapcan"));
  clmap.set( T("mapcar"), T("fun_mapccm_ma_istcm_mapcon.html#mapcar"));
  clmap.set( T("mapcon"), T("fun_mapccm_ma_istcm_mapcon.html#mapcon"));
  clmap.set( T("maphash"), T("fun_maphash.html#maphash"));
  clmap.set( T("mapl"), T("fun_mapccm_ma_istcm_mapcon.html#mapl"));
  clmap.set( T("maplist"), T("fun_mapccm_ma_istcm_mapcon.html#maplist"));
  clmap.set( T("mask-field"), T("acc_mask-field.html#mask-field"));
  clmap.set( T("max"), T("fun_maxcm_min.html#max"));
  clmap.set( T("member"), T("any_member.html#member"));
  clmap.set( T("member-if"), T("fun_membercm__ember-if-not.html#member-if"));
  clmap.set( T("member-if-not"), T("fun_membercm__ember-if-not.html#member-if-not"));
  clmap.set( T("merge"), T("fun_merge.html#merge"));
  clmap.set( T("merge-pathnames"), T("fun_merge-pathnames.html#merge-pathnames"));
  clmap.set( T("method"), T("syscla_method.html#method"));
  clmap.set( T("method-combination"), T("any_method-combination.html#method-combination"));
  clmap.set( T("method-combination-error"), T("fun_method-co_nation-error.html#method-combination-error"));
  clmap.set( T("method-qualifiers"), T("stagenfun_met_d-qualifiers.html#method-qualifiers"));
  clmap.set( T("min"), T("fun_maxcm_min.html#min"));
  clmap.set( T("minusp"), T("fun_minuspcm_plusp.html#minusp"));
  clmap.set( T("mismatch"), T("fun_mismatch.html#mismatch"));
  clmap.set( T("mod"), T("any_mod.html#mod"));
  clmap.set( T("most-negative-double-float"), T("convar_most-p_d-long-float.html#most-negative-double-float"));
  clmap.set( T("most-negative-fixnum"), T("convar_most-p_ative-fixnum.html#most-negative-fixnum"));
  clmap.set( T("most-negative-long-float"), T("convar_most-p_d-long-float.html#most-negative-long-float"));
  clmap.set( T("most-negative-short-float"), T("convar_most-p_d-long-float.html#most-negative-short-float"));
  clmap.set( T("most-negative-single-float"), T("convar_most-p_d-long-float.html#most-negative-single-float"));
  clmap.set( T("most-positive-double-float"), T("convar_most-p_d-long-float.html#most-positive-double-float"));
  clmap.set( T("most-positive-fixnum"), T("convar_most-p_ative-fixnum.html#most-positive-fixnum"));
  clmap.set( T("most-positive-long-float"), T("convar_most-p_d-long-float.html#most-positive-long-float"));
  clmap.set( T("most-positive-short-float"), T("convar_most-p_d-long-float.html#most-positive-short-float"));
  clmap.set( T("most-positive-single-float"), T("convar_most-p_d-long-float.html#most-positive-single-float"));
  clmap.set( T("muffle-warning"), T("any_muffle-warning.html#muffle-warning"));
  clmap.set( T("multiple-value-bind"), T("mac_multiple-value-bind.html#multiple-value-bind"));
  clmap.set( T("multiple-value-call"), T("speope_multiple-value-call.html#multiple-value-call"));
  clmap.set( T("multiple-value-list"), T("mac_multiple-value-list.html#multiple-value-list"));
  clmap.set( T("multiple-value-prog1"), T("speope_multip_-value-prog1.html#multiple-value-prog1"));
  clmap.set( T("multiple-value-setq"), T("mac_multiple-value-setq.html#multiple-value-setq"));
  clmap.set( T("multiple-values-limit"), T("convar_multip_values-limit.html#multiple-values-limit"));
  clmap.set( T("name-char"), T("fun_name-char.html#name-char"));
  clmap.set( T("namestring"), T("fun_namestrin_h-namestring.html#namestring"));
  clmap.set( T("nbutlast"), T("fun_butlastcm_nbutlast.html#nbutlast"));
  clmap.set( T("nconc"), T("fun_nconc.html#nconc"));
  clmap.set( T("next-method-p"), T("locfun_next-method-p.html#next-method-p"));
  clmap.set( T("nil"), T("any_nil.html#nil"));
  clmap.set( T("nintersection"), T("fun_intersect_intersection.html#nintersection"));
  clmap.set( T("ninth"), T("acc_firstcm_s_inthcm_tenth.html#ninth"));
  clmap.set( T("no-applicable-method"), T("stagenfun_no-_cable-method.html#no-applicable-method"));
  clmap.set( T("no-next-method"), T("stagenfun_no-next-method.html#no-next-method"));
  clmap.set( T("not"), T("any_not.html#not"));
  clmap.set( T("notany"), T("fun_everycm_s_erycm_notany.html#notany"));
  clmap.set( T("notevery"), T("fun_everycm_s_erycm_notany.html#notevery"));
  clmap.set( T("notinline"), T("dec_inlinecm_notinline.html#notinline"));
  clmap.set( T("nreconc"), T("fun_revappendcm_nreconc.html#nreconc"));
  clmap.set( T("nreverse"), T("fun_reversecm_nreverse.html#nreverse"));
  clmap.set( T("nset-difference"), T("fun_set-diffe_t-difference.html#nset-difference"));
  clmap.set( T("nset-exclusive-or"), T("fun_set-exclu_exclusive-or.html#nset-exclusive-or"));
  clmap.set( T("nstring-capitalize"), T("fun_string-up_g-capitalize.html#nstring-capitalize"));
  clmap.set( T("nstring-downcase"), T("fun_string-up_g-capitalize.html#nstring-downcase"));
  clmap.set( T("nstring-upcase"), T("fun_string-up_g-capitalize.html#nstring-upcase"));
  clmap.set( T("nsublis"), T("fun_subliscm_nsublis.html#nsublis"));
  clmap.set( T("nsubst"), T("fun_substcm_s_subst-if-not.html#nsubst"));
  clmap.set( T("nsubst-if"), T("fun_substcm_s_subst-if-not.html#nsubst-if"));
  clmap.set( T("nsubst-if-not"), T("fun_substcm_s_subst-if-not.html#nsubst-if-not"));
  clmap.set( T("nsubstitute"), T("fun_substitut_itute-if-not.html#nsubstitute"));
  clmap.set( T("nsubstitute-if"), T("fun_substitut_itute-if-not.html#nsubstitute-if"));
  clmap.set( T("nsubstitute-if-not"), T("fun_substitut_itute-if-not.html#nsubstitute-if-not"));
  clmap.set( T("nth"), T("acc_nth.html#nth"));
  clmap.set( T("nth-value"), T("mac_nth-value.html#nth-value"));
  clmap.set( T("nthcdr"), T("fun_nthcdr.html#nthcdr"));
  clmap.set( T("null"), T("any_null.html#null"));
  clmap.set( T("number"), T("syscla_number.html#number"));
  clmap.set( T("numberp"), T("fun_numberp.html#numberp"));
  clmap.set( T("numerator"), T("fun_numerator__denominator.html#numerator"));
  clmap.set( T("nunion"), T("fun_unioncm_nunion.html#nunion"));
  clmap.set( T("oddp"), T("fun_evenpcm_oddp.html#oddp"));
  clmap.set( T("open"), T("fun_open.html#open"));
  clmap.set( T("open-stream-p"), T("fun_open-stream-p.html#open-stream-p"));
  clmap.set( T("optimize"), T("dec_optimize.html#optimize"));
  clmap.set( T("or"), T("any_or.html#or"));
  clmap.set( T("otherwise"), T("mac_casecm_ccasecm_ecase.html#otherwise"));
  clmap.set( T("output-stream-p"), T("fun_input-str_put-stream-p.html#output-stream-p"));
  clmap.set( T("package"), T("syscla_package.html#package"));
  clmap.set( T("package-error"), T("contyp_package-error.html#package-error"));
  clmap.set( T("package-error-package"), T("fun_package-error-package.html#package-error-package"));
  clmap.set( T("package-name"), T("fun_package-name.html#package-name"));
  clmap.set( T("package-nicknames"), T("fun_package-nicknames.html#package-nicknames"));
  clmap.set( T("package-shadowing-symbols"), T("fun_package-s_wing-symbols.html#package-shadowing-symbols"));
  clmap.set( T("package-use-list"), T("fun_package-use-list.html#package-use-list"));
  clmap.set( T("package-used-by-list"), T("fun_package-used-by-list.html#package-used-by-list"));
  clmap.set( T("packagep"), T("fun_packagep.html#packagep"));
  clmap.set( T("pairlis"), T("fun_pairlis.html#pairlis"));
  clmap.set( T("parse-error"), T("contyp_parse-error.html#parse-error"));
  clmap.set( T("parse-integer"), T("fun_parse-integer.html#parse-integer"));
  clmap.set( T("parse-namestring"), T("fun_parse-namestring.html#parse-namestring"));
  clmap.set( T("pathname"), T("any_pathname.html#pathname"));
  clmap.set( T("pathname-device"), T("fun_pathname-_name-version.html#pathname-device"));
  clmap.set( T("pathname-directory"), T("fun_pathname-_name-version.html#pathname-directory"));
  clmap.set( T("pathname-host"), T("fun_pathname-_name-version.html#pathname-host"));
  clmap.set( T("pathname-match-p"), T("fun_pathname-match-p.html#pathname-match-p"));
  clmap.set( T("pathname-name"), T("fun_pathname-_name-version.html#pathname-name"));
  clmap.set( T("pathname-type"), T("fun_pathname-_name-version.html#pathname-type"));
  clmap.set( T("pathname-version"), T("fun_pathname-_name-version.html#pathname-version"));
  clmap.set( T("pathnamep"), T("fun_pathnamep.html#pathnamep"));
  clmap.set( T("peek-char"), T("fun_peek-char.html#peek-char"));
  clmap.set( T("phase"), T("fun_phase.html#phase"));
  clmap.set( T("pi"), T("convar_pi.html#pi"));
  clmap.set( T("plusp"), T("fun_minuspcm_plusp.html#plusp"));
  clmap.set( T("pop"), T("mac_pop.html#pop"));
  clmap.set( T("position"), T("fun_positionc_ition-if-not.html#position"));
  clmap.set( T("position-if"), T("fun_positionc_ition-if-not.html#position-if"));
  clmap.set( T("position-if-not"), T("fun_positionc_ition-if-not.html#position-if-not"));
  clmap.set( T("pprint"), T("fun_writecm_p_rintcm_princ.html#pprint"));
  clmap.set( T("pprint-dispatch"), T("fun_pprint-dispatch.html#pprint-dispatch"));
  clmap.set( T("pprint-exit-if-list-exhausted"), T("locmac_pprint_st-exhausted.html#pprint-exit-if-list-exhausted"));
  clmap.set( T("pprint-fill"), T("fun_pprint-fi_rint-tabular.html#pprint-fill"));
  clmap.set( T("pprint-indent"), T("fun_pprint-indent.html#pprint-indent"));
  clmap.set( T("pprint-linear"), T("fun_pprint-fi_rint-tabular.html#pprint-linear"));
  clmap.set( T("pprint-logical-block"), T("mac_pprint-logical-block.html#pprint-logical-block"));
  clmap.set( T("pprint-newline"), T("fun_pprint-newline.html#pprint-newline"));
  clmap.set( T("pprint-pop"), T("locmac_pprint-pop.html#pprint-pop"));
  clmap.set( T("pprint-tab"), T("fun_pprint-tab.html#pprint-tab"));
  clmap.set( T("pprint-tabular"), T("fun_pprint-fi_rint-tabular.html#pprint-tabular"));
  clmap.set( T("prin1"), T("fun_writecm_p_rintcm_princ.html#prin1"));
  clmap.set( T("prin1-to-string"), T("fun_write-to-_nc-to-string.html#prin1-to-string"));
  clmap.set( T("princ"), T("fun_writecm_p_rintcm_princ.html#princ"));
  clmap.set( T("princ-to-string"), T("fun_write-to-_nc-to-string.html#princ-to-string"));
  clmap.set( T("print"), T("fun_writecm_p_rintcm_princ.html#print"));
  clmap.set( T("print-not-readable"), T("contyp_print-not-readable.html#print-not-readable"));
  clmap.set( T("print-not-readable-object"), T("fun_print-not_dable-object.html#print-not-readable-object"));
  clmap.set( T("print-object"), T("stagenfun_print-object.html#print-object"));
  clmap.set( T("print-unreadable-object"), T("mac_print-unr_dable-object.html#print-unreadable-object"));
  clmap.set( T("probe-file"), T("fun_probe-file.html#probe-file"));
  clmap.set( T("proclaim"), T("fun_proclaim.html#proclaim"));
  clmap.set( T("prog"), T("mac_progcm_progst.html#prog"));
  clmap.set( T("prog*"), T("mac_progcm_progst.html#progST"));
  clmap.set( T("prog1"), T("mac_prog1cm_prog2.html#prog1"));
  clmap.set( T("prog2"), T("mac_prog1cm_prog2.html#prog2"));
  clmap.set( T("progn"), T("speope_progn.html#progn"));
  clmap.set( T("program-error"), T("contyp_program-error.html#program-error"));
  clmap.set( T("progv"), T("speope_progv.html#progv"));
  clmap.set( T("provide"), T("fun_providecm_require.html#provide"));
  clmap.set( T("psetf"), T("mac_setfcm_psetf.html#psetf"));
  clmap.set( T("psetq"), T("mac_psetq.html#psetq"));
  clmap.set( T("push"), T("mac_push.html#push"));
  clmap.set( T("pushnew"), T("mac_pushnew.html#pushnew"));
  clmap.set( T("quote"), T("speope_quote.html#quote"));
  clmap.set( T("random"), T("fun_random.html#random"));
  clmap.set( T("random-state"), T("syscla_random-state.html#random-state"));
  clmap.set( T("random-state-p"), T("fun_random-state-p.html#random-state-p"));
  clmap.set( T("rassoc"), T("fun_rassoccm__assoc-if-not.html#rassoc"));
  clmap.set( T("rassoc-if"), T("fun_rassoccm__assoc-if-not.html#rassoc-if"));
  clmap.set( T("rassoc-if-not"), T("fun_rassoccm__assoc-if-not.html#rassoc-if-not"));
  clmap.set( T("ratio"), T("syscla_ratio.html#ratio"));
  clmap.set( T("rational"), T("any_rational.html#rational"));
  clmap.set( T("rationalize"), T("fun_rationalcm_rationalize.html#rationalize"));
  clmap.set( T("rationalp"), T("fun_rationalp.html#rationalp"));
  clmap.set( T("read"), T("fun_readcm_re_g-whitespace.html#read"));
  clmap.set( T("read-byte"), T("fun_read-byte.html#read-byte"));
  clmap.set( T("read-char"), T("fun_read-char.html#read-char"));
  clmap.set( T("read-char-no-hang"), T("fun_read-char-no-hang.html#read-char-no-hang"));
  clmap.set( T("read-delimited-list"), T("fun_read-delimited-list.html#read-delimited-list"));
  clmap.set( T("read-from-string"), T("fun_read-from-string.html#read-from-string"));
  clmap.set( T("read-line"), T("fun_read-line.html#read-line"));
  clmap.set( T("read-preserving-whitespace"), T("fun_readcm_re_g-whitespace.html#read-preserving-whitespace"));
  clmap.set( T("read-sequence"), T("fun_read-sequence.html#read-sequence"));
  clmap.set( T("reader-error"), T("contyp_reader-error.html#reader-error"));
  clmap.set( T("readtable"), T("syscla_readtable.html#readtable"));
  clmap.set( T("readtable-case"), T("acc_readtable-case.html#readtable-case"));
  clmap.set( T("readtablep"), T("fun_readtablep.html#readtablep"));
  clmap.set( T("real"), T("syscla_real.html#real"));
  clmap.set( T("realp"), T("fun_realp.html#realp"));
  clmap.set( T("realpart"), T("fun_realpartcm_imagpart.html#realpart"));
  clmap.set( T("reduce"), T("fun_reduce.html#reduce"));
  clmap.set( T("reinitialize-instance"), T("stagenfun_rei_ize-instance.html#reinitialize-instance"));
  clmap.set( T("rem"), T("fun_modcm_rem.html#rem"));
  clmap.set( T("remf"), T("mac_remf.html#remf"));
  clmap.set( T("remhash"), T("fun_remhash.html#remhash"));
  clmap.set( T("remove"), T("fun_removecm__elete-if-not.html#remove"));
  clmap.set( T("remove-duplicates"), T("fun_remove-du_e-duplicates.html#remove-duplicates"));
  clmap.set( T("remove-if"), T("fun_removecm__elete-if-not.html#remove-if"));
  clmap.set( T("remove-if-not"), T("fun_removecm__elete-if-not.html#remove-if-not"));
  clmap.set( T("remove-method"), T("stagenfun_remove-method.html#remove-method"));
  clmap.set( T("remprop"), T("fun_remprop.html#remprop"));
  clmap.set( T("rename-file"), T("fun_rename-file.html#rename-file"));
  clmap.set( T("rename-package"), T("fun_rename-package.html#rename-package"));
  clmap.set( T("replace"), T("fun_replace.html#replace"));
  clmap.set( T("require"), T("fun_providecm_require.html#require"));
  clmap.set( T("rest"), T("acc_rest.html#rest"));
  clmap.set( T("restart"), T("syscla_restart.html#restart"));
  clmap.set( T("restart-bind"), T("mac_restart-bind.html#restart-bind"));
  clmap.set( T("restart-case"), T("mac_restart-case.html#restart-case"));
  clmap.set( T("restart-name"), T("fun_restart-name.html#restart-name"));
  clmap.set( T("return"), T("mac_return.html#return"));
  clmap.set( T("return-from"), T("speope_return-from.html#return-from"));
  clmap.set( T("revappend"), T("fun_revappendcm_nreconc.html#revappend"));
  clmap.set( T("reverse"), T("fun_reversecm_nreverse.html#reverse"));
  clmap.set( T("room"), T("fun_room.html#room"));
  clmap.set( T("rotatef"), T("mac_rotatef.html#rotatef"));
  clmap.set( T("round"), T("fun_floorcm_f_undcm_fround.html#round"));
  clmap.set( T("row-major-aref"), T("acc_row-major-aref.html#row-major-aref"));
  clmap.set( T("rplaca"), T("fun_rplacacm_rplacd.html#rplaca"));
  clmap.set( T("rplacd"), T("fun_rplacacm_rplacd.html#rplacd"));
  clmap.set( T("safety"), T("dec_optimize.html#safety"));
  clmap.set( T("satisfies"), T("typspe_satisfies.html#satisfies"));
  clmap.set( T("sbit"), T("acc_bitcm_sbit.html#sbit"));
  clmap.set( T("scale-float"), T("fun_decode-fl_decode-float.html#scale-float"));
  clmap.set( T("schar"), T("acc_charcm_schar.html#schar"));
  clmap.set( T("search"), T("fun_search.html#search"));
  clmap.set( T("second"), T("acc_firstcm_s_inthcm_tenth.html#second"));
  clmap.set( T("sequence"), T("syscla_sequence.html#sequence"));
  clmap.set( T("serious-condition"), T("contyp_serious-condition.html#serious-condition"));
  clmap.set( T("set"), T("fun_set.html#set"));
  clmap.set( T("set-difference"), T("fun_set-diffe_t-difference.html#set-difference"));
  clmap.set( T("set-dispatch-macro-character"), T("fun_set-dispa_ro-character.html#set-dispatch-macro-character"));
  clmap.set( T("set-exclusive-or"), T("fun_set-exclu_exclusive-or.html#set-exclusive-or"));
  clmap.set( T("set-macro-character"), T("fun_set-macro_ro-character.html#set-macro-character"));
  clmap.set( T("set-pprint-dispatch"), T("fun_set-pprint-dispatch.html#set-pprint-dispatch"));
  clmap.set( T("set-syntax-from-char"), T("fun_set-syntax-from-char.html#set-syntax-from-char"));
  clmap.set( T("setf"), T("any_setf.html#setf"));
  clmap.set( T("setq"), T("spefor_setq.html#setq"));
  clmap.set( T("seventh"), T("acc_firstcm_s_inthcm_tenth.html#seventh"));
  clmap.set( T("shadow"), T("fun_shadow.html#shadow"));
  clmap.set( T("shadowing-import"), T("fun_shadowing-import.html#shadowing-import"));
  clmap.set( T("shared-initialize"), T("stagenfun_sha_d-initialize.html#shared-initialize"));
  clmap.set( T("shiftf"), T("mac_shiftf.html#shiftf"));
  clmap.set( T("short-float"), T("typ_short-flo_m_long-float.html#short-float"));
  clmap.set( T("short-float-epsilon"), T("convar_short-_tive-epsilon.html#short-float-epsilon"));
  clmap.set( T("short-float-negative-epsilon"), T("convar_short-_tive-epsilon.html#short-float-negative-epsilon"));
  clmap.set( T("short-site-name"), T("fun_short-sit_ng-site-name.html#short-site-name"));
  clmap.set( T("signal"), T("fun_signal.html#signal"));
  clmap.set( T("signed-byte"), T("typ_signed-byte.html#signed-byte"));
  clmap.set( T("signum"), T("fun_signum.html#signum"));
  clmap.set( T("simple-array"), T("typ_simple-array.html#simple-array"));
  clmap.set( T("simple-base-string"), T("typ_simple-base-string.html#simple-base-string"));
  clmap.set( T("simple-bit-vector"), T("typ_simple-bit-vector.html#simple-bit-vector"));
  clmap.set( T("simple-bit-vector-p"), T("fun_simple-bit-vector-p.html#simple-bit-vector-p"));
  clmap.set( T("simple-condition"), T("contyp_simple-condition.html#simple-condition"));
  clmap.set( T("simple-condition-format-arguments"), T("fun_simple-co_at-arguments.html#simple-condition-format-arguments"));
  clmap.set( T("simple-condition-format-control"), T("fun_simple-co_at-arguments.html#simple-condition-format-control"));
  clmap.set( T("simple-error"), T("contyp_simple-error.html#simple-error"));
  clmap.set( T("simple-string"), T("typ_simple-string.html#simple-string"));
  clmap.set( T("simple-string-p"), T("fun_simple-string-p.html#simple-string-p"));
  clmap.set( T("simple-type-error"), T("contyp_simple-type-error.html#simple-type-error"));
  clmap.set( T("simple-vector"), T("typ_simple-vector.html#simple-vector"));
  clmap.set( T("simple-vector-p"), T("fun_simple-vector-p.html#simple-vector-p"));
  clmap.set( T("simple-warning"), T("contyp_simple-warning.html#simple-warning"));
  clmap.set( T("sin"), T("fun_sincm_coscm_tan.html#sin"));
  clmap.set( T("single-float"), T("typ_short-flo_m_long-float.html#single-float"));
  clmap.set( T("single-float-epsilon"), T("convar_short-_tive-epsilon.html#single-float-epsilon"));
  clmap.set( T("single-float-negative-epsilon"), T("convar_short-_tive-epsilon.html#single-float-negative-epsilon"));
  clmap.set( T("sinh"), T("fun_sinhcm_co_coshcm_atanh.html#sinh"));
  clmap.set( T("sixth"), T("acc_firstcm_s_inthcm_tenth.html#sixth"));
  clmap.set( T("sleep"), T("fun_sleep.html#sleep"));
  clmap.set( T("slot-boundp"), T("fun_slot-boundp.html#slot-boundp"));
  clmap.set( T("slot-exists-p"), T("fun_slot-exists-p.html#slot-exists-p"));
  clmap.set( T("slot-makunbound"), T("fun_slot-makunbound.html#slot-makunbound"));
  clmap.set( T("slot-missing"), T("stagenfun_slot-missing.html#slot-missing"));
  clmap.set( T("slot-unbound"), T("stagenfun_slot-unbound.html#slot-unbound"));
  clmap.set( T("slot-value"), T("fun_slot-value.html#slot-value"));
  clmap.set( T("software-type"), T("fun_software-_ware-version.html#software-type"));
  clmap.set( T("software-version"), T("fun_software-_ware-version.html#software-version"));
  clmap.set( T("some"), T("fun_everycm_s_erycm_notany.html#some"));
  clmap.set( T("sort"), T("fun_sortcm_stable-sort.html#sort"));
  clmap.set( T("space"), T("dec_optimize.html#space"));
  clmap.set( T("special"), T("dec_special.html#special"));
  clmap.set( T("special-operator-p"), T("fun_special-operator-p.html#special-operator-p"));
  clmap.set( T("speed"), T("dec_optimize.html#speed"));
  clmap.set( T("sqrt"), T("fun_sqrtcm_isqrt.html#sqrt"));
  clmap.set( T("stable-sort"), T("fun_sortcm_stable-sort.html#stable-sort"));
  clmap.set( T("standard"), T("sec_7-6-6-2.html#standard"));
  clmap.set( T("standard-char"), T("typ_standard-char.html#standard-char"));
  clmap.set( T("standard-char-p"), T("fun_standard-char-p.html#standard-char-p"));
  clmap.set( T("standard-class"), T("syscla_standard-class.html#standard-class"));
  clmap.set( T("standard-generic-function"), T("syscla_standa_ric-function.html#standard-generic-function"));
  clmap.set( T("standard-method"), T("syscla_standard-method.html#standard-method"));
  clmap.set( T("standard-object"), T("cla_standard-object.html#standard-object"));
  clmap.set( T("step"), T("mac_step.html#step"));
  clmap.set( T("storage-condition"), T("contyp_storage-condition.html#storage-condition"));
  clmap.set( T("store-value"), T("any_store-value.html#store-value"));
  clmap.set( T("stream"), T("syscla_stream.html#stream"));
  clmap.set( T("stream-element-type"), T("fun_stream-element-type.html#stream-element-type"));
  clmap.set( T("stream-error"), T("contyp_stream-error.html#stream-error"));
  clmap.set( T("stream-error-stream"), T("fun_stream-error-stream.html#stream-error-stream"));
  clmap.set( T("stream-external-format"), T("fun_stream-external-format.html#stream-external-format"));
  clmap.set( T("streamp"), T("fun_streamp.html#streamp"));
  clmap.set( T("string"), T("any_string.html#string"));
  clmap.set( T("string-capitalize"), T("fun_string-up_g-capitalize.html#string-capitalize"));
  clmap.set( T("string-downcase"), T("fun_string-up_g-capitalize.html#string-downcase"));
  clmap.set( T("string-equal"), T("fun_stringeqc_ng-not-lessp.html#string-equal"));
  clmap.set( T("string-greaterp"), T("fun_stringeqc_ng-not-lessp.html#string-greaterp"));
  clmap.set( T("string-left-trim"), T("fun_string-tr_g-right-trim.html#string-left-trim"));
  clmap.set( T("string-lessp"), T("fun_stringeqc_ng-not-lessp.html#string-lessp"));
  clmap.set( T("string-not-equal"), T("fun_stringeqc_ng-not-lessp.html#string-not-equal"));
  clmap.set( T("string-not-greaterp"), T("fun_stringeqc_ng-not-lessp.html#string-not-greaterp"));
  clmap.set( T("string-not-lessp"), T("fun_stringeqc_ng-not-lessp.html#string-not-lessp"));
  clmap.set( T("string-right-trim"), T("fun_string-tr_g-right-trim.html#string-right-trim"));
  clmap.set( T("string-stream"), T("syscla_string-stream.html#string-stream"));
  clmap.set( T("string-trim"), T("fun_string-tr_g-right-trim.html#string-trim"));
  clmap.set( T("string-upcase"), T("fun_string-up_g-capitalize.html#string-upcase"));
  clmap.set( T("string/="), T("fun_stringeqc_ng-not-lessp.html#stringSLEQ"));
  clmap.set( T("string&lt;"), T("fun_stringeqc_ng-not-lessp.html#stringLT"));
  clmap.set( T("string&lt;="), T("fun_stringeqc_ng-not-lessp.html#stringLTEQ"));
  clmap.set( T("string="), T("fun_stringeqc_ng-not-lessp.html#stringEQ"));
  clmap.set( T("string&gt;"), T("fun_stringeqc_ng-not-lessp.html#stringGT"));
  clmap.set( T("string&gt;="), T("fun_stringeqc_ng-not-lessp.html#stringGTEQ"));
  clmap.set( T("stringp"), T("fun_stringp.html#stringp"));
  clmap.set( T("structure"), T("stagenfun_doc_umentationcp.html#structure"));
  clmap.set( T("structure-class"), T("syscla_structure-class.html#structure-class"));
  clmap.set( T("structure-object"), T("cla_structure-object.html#structure-object"));
  clmap.set( T("style-warning"), T("contyp_style-warning.html#style-warning"));
  clmap.set( T("sublis"), T("fun_subliscm_nsublis.html#sublis"));
  clmap.set( T("subseq"), T("acc_subseq.html#subseq"));
  clmap.set( T("subsetp"), T("fun_subsetp.html#subsetp"));
  clmap.set( T("subst"), T("fun_substcm_s_subst-if-not.html#subst"));
  clmap.set( T("subst-if"), T("fun_substcm_s_subst-if-not.html#subst-if"));
  clmap.set( T("subst-if-not"), T("fun_substcm_s_subst-if-not.html#subst-if-not"));
  clmap.set( T("substitute"), T("fun_substitut_itute-if-not.html#substitute"));
  clmap.set( T("substitute-if"), T("fun_substitut_itute-if-not.html#substitute-if"));
  clmap.set( T("substitute-if-not"), T("fun_substitut_itute-if-not.html#substitute-if-not"));
  clmap.set( T("subtypep"), T("fun_subtypep.html#subtypep"));
  clmap.set( T("svref"), T("acc_svref.html#svref"));
  clmap.set( T("sxhash"), T("fun_sxhash.html#sxhash"));
  clmap.set( T("symbol"), T("syscla_symbol.html#symbol"));
  clmap.set( T("symbol-function"), T("acc_symbol-function.html#symbol-function"));
  clmap.set( T("symbol-macrolet"), T("speope_symbol-macrolet.html#symbol-macrolet"));
  clmap.set( T("symbol-name"), T("fun_symbol-name.html#symbol-name"));
  clmap.set( T("symbol-package"), T("fun_symbol-package.html#symbol-package"));
  clmap.set( T("symbol-plist"), T("acc_symbol-plist.html#symbol-plist"));
  clmap.set( T("symbol-value"), T("acc_symbol-value.html#symbol-value"));
  clmap.set( T("symbolp"), T("fun_symbolp.html#symbolp"));
  clmap.set( T("synonym-stream"), T("syscla_synonym-stream.html#synonym-stream"));
  clmap.set( T("synonym-stream-symbol"), T("fun_synonym-stream-symbol.html#synonym-stream-symbol"));
  clmap.set( T("t"), T("any_t.html#t"));
  clmap.set( T("tagbody"), T("speope_tagbody.html#tagbody"));
  clmap.set( T("tailp"), T("fun_ldiffcm_tailp.html#tailp"));
  clmap.set( T("tan"), T("fun_sincm_coscm_tan.html#tan"));
  clmap.set( T("tanh"), T("fun_sinhcm_co_coshcm_atanh.html#tanh"));
  clmap.set( T("tenth"), T("acc_firstcm_s_inthcm_tenth.html#tenth"));
  clmap.set( T("terpri"), T("fun_terpricm_fresh-line.html#terpri"));
  clmap.set( T("the"), T("speope_the.html#the"));
  clmap.set( T("third"), T("acc_firstcm_s_inthcm_tenth.html#third"));
  clmap.set( T("throw"), T("speope_throw.html#throw"));
  clmap.set( T("time"), T("mac_time.html#time"));
  clmap.set( T("trace"), T("mac_tracecm_untrace.html#trace"));
  clmap.set( T("translate-logical-pathname"), T("fun_translate_cal-pathname.html#translate-logical-pathname"));
  clmap.set( T("translate-pathname"), T("fun_translate-pathname.html#translate-pathname"));
  clmap.set( T("tree-equal"), T("fun_tree-equal.html#tree-equal"));
  clmap.set( T("truename"), T("fun_truename.html#truename"));
  clmap.set( T("truncate"), T("fun_floorcm_f_undcm_fround.html#truncate"));
  clmap.set( T("two-way-stream"), T("syscla_two-way-stream.html#two-way-stream"));
  clmap.set( T("two-way-stream-input-stream"), T("fun_two-way-s_utput-stream.html#two-way-stream-input-stream"));
  clmap.set( T("two-way-stream-output-stream"), T("fun_two-way-s_utput-stream.html#two-way-stream-output-stream"));
  clmap.set( T("type"), T("any_type.html#type"));
  clmap.set( T("type-error"), T("contyp_type-error.html#type-error"));
  clmap.set( T("type-error-datum"), T("fun_type-erro_xpected-type.html#type-error-datum"));
  clmap.set( T("type-error-expected-type"), T("fun_type-erro_xpected-type.html#type-error-expected-type"));
  clmap.set( T("type-of"), T("fun_type-of.html#type-of"));
  clmap.set( T("typecase"), T("mac_typecasec_cm_etypecase.html#typecase"));
  clmap.set( T("typep"), T("fun_typep.html#typep"));
  clmap.set( T("unbound-slot"), T("contyp_unbound-slot.html#unbound-slot"));
  clmap.set( T("unbound-slot-instance"), T("fun_unbound-slot-instance.html#unbound-slot-instance"));
  clmap.set( T("unbound-variable"), T("contyp_unbound-variable.html#unbound-variable"));
  clmap.set( T("undefined-function"), T("contyp_undefined-function.html#undefined-function"));
  clmap.set( T("unexport"), T("fun_unexport.html#unexport"));
  clmap.set( T("unintern"), T("fun_unintern.html#unintern"));
  clmap.set( T("union"), T("fun_unioncm_nunion.html#union"));
  clmap.set( T("unless"), T("mac_whencm_unless.html#unless"));
  clmap.set( T("unread-char"), T("fun_unread-char.html#unread-char"));
  clmap.set( T("unsigned-byte"), T("typ_unsigned-byte.html#unsigned-byte"));
  clmap.set( T("untrace"), T("mac_tracecm_untrace.html#untrace"));
  clmap.set( T("unuse-package"), T("fun_unuse-package.html#unuse-package"));
  clmap.set( T("unwind-protect"), T("speope_unwind-protect.html#unwind-protect"));
  clmap.set( T("update-instance-for-different-class"), T("stagenfun_upd_ferent-class.html#update-instance-for-different-class"));
  clmap.set( T("update-instance-for-redefined-class"), T("stagenfun_upd_efined-class.html#update-instance-for-redefined-class"));
  clmap.set( T("upgraded-array-element-type"), T("fun_upgraded-_element-type.html#upgraded-array-element-type"));
  clmap.set( T("upgraded-complex-part-type"), T("fun_upgraded-_ex-part-type.html#upgraded-complex-part-type"));
  clmap.set( T("upper-case-p"), T("fun_upper-cas__both-case-p.html#upper-case-p"));
  clmap.set( T("use-package"), T("fun_use-package.html#use-package"));
  clmap.set( T("use-value"), T("any_use-value.html#use-value"));
  clmap.set( T("user-homedir-pathname"), T("fun_user-homedir-pathname.html#user-homedir-pathname"));
  clmap.set( T("values"), T("any_values.html#values"));
  clmap.set( T("values-list"), T("fun_values-list.html#values-list"));
  clmap.set( T("variable"), T("stagenfun_doc_umentationcp.html#variable"));
  clmap.set( T("vector"), T("any_vector.html#vector"));
  clmap.set( T("vector-pop"), T("fun_vector-pop.html#vector-pop"));
  clmap.set( T("vector-push"), T("fun_vector-pu_-push-extend.html#vector-push"));
  clmap.set( T("vector-push-extend"), T("fun_vector-pu_-push-extend.html#vector-push-extend"));
  clmap.set( T("vectorp"), T("fun_vectorp.html#vectorp"));
  clmap.set( T("warn"), T("fun_warn.html#warn"));
  clmap.set( T("warning"), T("contyp_warning.html#warning"));
  clmap.set( T("when"), T("mac_whencm_unless.html#when"));
  clmap.set( T("wild-pathname-p"), T("fun_wild-pathname-p.html#wild-pathname-p"));
  clmap.set( T("with-accessors"), T("mac_with-accessors.html#with-accessors"));
  clmap.set( T("with-compilation-unit"), T("mac_with-compilation-unit.html#with-compilation-unit"));
  clmap.set( T("with-condition-restarts"), T("mac_with-cond_ion-restarts.html#with-condition-restarts"));
  clmap.set( T("with-hash-table-iterator"), T("mac_with-hash_ble-iterator.html#with-hash-table-iterator"));
  clmap.set( T("with-input-from-string"), T("mac_with-input-from-string.html#with-input-from-string"));
  clmap.set( T("with-open-file"), T("mac_with-open-file.html#with-open-file"));
  clmap.set( T("with-open-stream"), T("mac_with-open-stream.html#with-open-stream"));
  clmap.set( T("with-output-to-string"), T("mac_with-output-to-string.html#with-output-to-string"));
  clmap.set( T("with-package-iterator"), T("mac_with-package-iterator.html#with-package-iterator"));
  clmap.set( T("with-simple-restart"), T("mac_with-simple-restart.html#with-simple-restart"));
  clmap.set( T("with-slots"), T("mac_with-slots.html#with-slots"));
  clmap.set( T("with-standard-io-syntax"), T("mac_with-stan_rd-io-syntax.html#with-standard-io-syntax"));
  clmap.set( T("write"), T("fun_writecm_p_rintcm_princ.html#write"));
  clmap.set( T("write-byte"), T("fun_write-byte.html#write-byte"));
  clmap.set( T("write-char"), T("fun_write-char.html#write-char"));
  clmap.set( T("write-line"), T("fun_write-str_m_write-line.html#write-line"));
  clmap.set( T("write-sequence"), T("fun_write-sequence.html#write-sequence"));
  clmap.set( T("write-string"), T("fun_write-str_m_write-line.html#write-string"));
  clmap.set( T("write-to-string"), T("fun_write-to-_nc-to-string.html#write-to-string"));
  clmap.set( T("y-or-n-p"), T("fun_y-or-n-pcm_yes-or-no-p.html#y-or-n-p"));
  clmap.set( T("yes-or-no-p"), T("fun_y-or-n-pcm_yes-or-no-p.html#yes-or-no-p"));
  clmap.set( T("zerop"), T("fun_zerop.html#zerop"));
#endif
}

String SymbolHelp::getRoot(String help) {
  return maproots[help] ;
}

String SymbolHelp::getHelp(String symbol, String helppath) {
  // search for symbol help in colon delimited help path.
  int i, p=0, l=helppath.length();
  String s, h, r, x;
  while (helppath != String::empty) {
    x=String::empty;
    i=helppath.indexOfChar(':');
    if (i==-1) {
      h=helppath;
      helppath=String::empty;
    }
    else {
      h=helppath.substring(0,i);
      helppath=helppath.substring(i+1);
    }
    //printf("helppath='%s'  help='%s'\n", helppath.toUTF8(), h.toUTF8());
    if ( h == T("Sal") )
      x=salmap[symbol];
    else if ( h == T("GraceScheme") )
      x=graceschememap[symbol];
    else if ( h == T("Scheme") )
      x=schememap[symbol];
    else if ( h == T("CommonMusic") )
      x=cmmap[symbol];
    else if ( h == T("CommonLispMusic") )
      x=clmmap[symbol];
    else if ( h == T("Fomus") ) 
      x=fomusmap[symbol];
    else if ( h == T("CommonLisp") ) 
      x=clmap[symbol];
    else
      x=String::empty;
    if ( x != String::empty) {
      return getRoot( h ) + x;
    }
  }
  return String::empty;
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

bool TextBuffer::keyPressed (const KeyPress& key) {
  int keyCode, keyMod, flag, last;
  keyCode =  key.getKeyCode();
  keyMod = key.getModifiers().getRawFlags();
  flag = isKeyCommand(key);
  // some commands like killLine need to know what the last command
  // was.  setAction() and storeAction() keep a memory of (one)
  // previous command.
  last = lastact;
  setAction(0);

  //printf("key=%d mod=%d\n", keyCode, keyMod);

  if ( isMatching() ) stopMatching();

  if (last == actControlX)
    keyControlXAction(key);
  else if (flag == 0) {
    if (keyCode == KeyPress::tabKey)
      syntacticIndent();
    else if (keyCode == KeyPress::returnKey) {
	TextEditor::keyPressed(key);
	setChanged(true);
	colorizeAfterChange(cmdInsertLine);
      }
    //    else if (keyCode == KeyPress::F1Key)
    //      lookupHelpAtPoint();
    else if (keyCode == KeyPress::backspaceKey) {
      TextEditor::keyPressed(key);
      setChanged(true);
      colorizeAfterChange(cmdBackspace);
      }
    else if (keyCode == KeyPress::deleteKey ) {
      TextEditor::keyPressed(key);
      setChanged(true);
      colorizeAfterChange(cmdDelete);
    }
    else {
      // inserting normal text but maybe match parens
      juce_wchar c=key.getTextCharacter();
      TextEditor::keyPressed(key); // call editor method
      setChanged(true);
      if ( (c==')') && isParensMatching() ) {
	matchParens();
      }
      else if ( (c=='}') && (syntaxId==syntaxSal) && isParensMatching() ) {
	matchParens();
      }
      else if ((31<c && c<127)) {
	colorizeAfterChange(cmdInsertChar);
      }
    }
  }
  else if (flag < 1)
    keyIllegalAction(key);
  else {
    switch (flag) {
    case KeyCommands::emacsControl :
      keyControlAction(key);
      break;
    case KeyCommands::emacsMeta :
      keyMetaAction(key);
      break;
    case KeyCommands::emacsCommand :
      keyCommandAction(key);
      break;
    case KeyCommands::emacsControlMeta :
      keyControlMetaAction(key);
      break;
    default :
      keyIllegalAction(key);
    }
  }
  storeAction();
  return true;
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

  typ = scan_sexpr(syntax->syntab, text, 0, end, SCAN_CODE, &loc, NULL);
  if (typ == SCAN_UNLEVEL)
    getConsole()->printWarning(T("Editor C-M-f:\nCan't move forward past end of list.\n"));
  else if (typ == SCAN_UNMATCHED)
    getConsole()->printWarning(T("Editor C-M-f:\nForward unmatched delimiter.\n"));
  else
    setPoint(pos+loc);
  return point();
}

int TextBuffer::backwardSexpr() {
  String text = backwardTopLevelText();
  int typ, loc, pos=point(), end=text.length();

  typ = scan_sexpr(syntax->syntab, text, end-1, -1, SCAN_CODE, &loc, NULL);
  if (typ == SCAN_UNLEVEL)
    getConsole()->printWarning(T("Can't move backward past start of list.\n"));
  else if (typ == SCAN_UNMATCHED)
    getConsole()->printWarning(T("Backward unmatched delimiter.\n"));
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

int TextBuffer::evalText(bool macroexpand) {
  bool region=(getHighlightedRegionLength() > 0);
  String text;

  if ( region )
    text=getHighlightedText();
  else 
    text=backwardTopLevelText();

  if (syntaxId==syntaxLisp && !region) {
    // parse out backward sexpr if not region
    int typ, loc, end=text.length();
    typ = scan_sexpr(syntax->syntab, text, end-1, -1, SCAN_CODE, &loc, NULL);
    if (typ>SCAN_EMPTY) 
      text=text.substring(loc+1,end);
  }
  printf("parsed-> %s\n", text.toUTF8());
  syntax->evalText(text, region, macroexpand);
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

  if (syntaxId==syntaxText) return; // symbol help not avaiable in Text mode

  if ( region )
    text=getHighlightedText();
  else {
    int pos=point();
    int bol=pointBOL();
    text=getTextSubstring(bol, pointEOL() );
    int len=text.length();
    int beg=skip_syntax(syntax->syntab, text, T("w_"), pos-bol-1, -1);
    int end=skip_syntax(syntax->syntab, text, T("w_"), pos-bol, len);
    if (beg+1==end) return;
    text=text.substring(beg+1,end);
  }
  //  printf("lookup help for %s\n", text.toUTF8() );

  /*SynTok* tok=syntax->getSynTok(text);
  if (tok == (SynTok *)NULL) return;
  String file=T("doc/sal/help/") + text + T(".sal");
  File help=getGraceResourceDirectory().getChildFile(file);*/

  String path=String::empty;
  String help=String::empty;
#ifdef SCHEME
  if ( syntaxId==syntaxSal )
    path= T("Sal:GraceScheme:Scheme");
  else if ( syntaxId==syntaxLisp )
    path= T("GraceScheme:Scheme");    
#else
  if ( syntaxId==syntaxSal )
    path = T("Sal:CommonMusic:CommonLispMusic:CommonLisp");
 else if ( syntaxId==syntaxLisp )
    path = T("CommonMusic:CommonLispMusic:CommonLisp");
#endif

  help=SymbolHelp::getInstance()->getHelp(text, path );
  printf("SymbolHelp='%s'\n", help.toUTF8());

  //http://www.rawmaterialsoftware.com/juce/api/classString.html#8a7ef356e05eb9b1ea1ab518baee3095


  if (help==String::empty) return;

  if ( help.startsWithIgnoreCase(T("http:")) || 
       help.startsWithIgnoreCase(T("file:"))  ) {
    URL(help).launchInDefaultBrowser();
  }
  else if ( File(help).existsAsFile() ) 
    new EditorWindow(syntaxNone, (TextBuffer::load | TextBuffer::nosave), 
		     File(help).getFullPathName());
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


///////// sal testing

void TextBuffer::salTokenize() {
  if (! isBOB() ) {
    String text=backwardTopLevelText();
    if (text != String::empty)
      ((SalSyntax *)syntax)->tokenize(text);
    return;
  }
  bool eob=false;
  String str=String::empty;
  while (! eob) {
    int b, e;
    String l;
    while ( ! eob) {
      b=point();
      e=pointEOL();
      if ( e > b) {
	l=getTextSubstring(b,e);
	if (l[0] != ';')  break;
      }
      if ( ! moveLine(1) ) {
	eob=true;
      }
    }
    str=String::empty;
    while ( ! eob) {
      if (str != String::empty) str += T("\n");
      str += l;
      if ( ! moveLine(1) ) {
	eob=true;
      }
      b=point();
      e=pointEOL();
      if (b == e) break;
      l=getTextSubstring(b,e);      
      if ( l[0]==';' ) break;
    }
    if (str != String::empty)
      ((SalSyntax *)syntax)->tokenize(str);
  }
  return;
}

void TextBuffer::paste() {
  String clip=SystemClipboard::getTextFromClipboard();
  if ( clip.isNotEmpty() ) {
    if ( clip.containsChar( '\r') ) {
      printf("Converting CR chars\n");
#ifdef MACOSX
      clip=clip.replaceCharacter('\r', '\n');
#else
      String temp=String::empty;
      for (int i=0; i<clip.length(); i++)
	if (clip[i] != '\r' ) 
	  temp << clip[i];
      clip=temp;
#endif
    }
    insertTextAtCursor(clip);
    setChanged(true);
    colorizeAfterChange(cmdEditPaste);
  }
}
