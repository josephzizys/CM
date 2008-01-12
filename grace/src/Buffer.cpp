/*************************************************************************
 * Copyright (C) 2007, 2008 Todd Ingalls, Rick Taube.                    *
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
#include "Help.h"

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
    result.setInfo (T("Load File..."), String::empty, editingCategory, 0);
#ifndef SCHEME
    result.setActive(getConsole()->lisp->isLispRunning() );
#endif
    break;

#ifndef SCHEME
  case cmdLispCompileFile:
    result.setInfo (T("Compile File..."), String::empty, editingCategory, 0);
    result.setActive(getConsole()->lisp->isLispRunning() );
    break;
#endif

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

#ifndef SCHEME
  case cmdLispSetPackage:
    result.setInfo (T("Set Package..."), String::empty, editingCategory, 0);

    result.setActive(getConsole()->lisp->isLispRunning() );
    break;
#endif

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
 
  String helppath=String::empty;
  String help=String::empty;
#ifdef SCHEME
  if ( syntaxId==syntaxSal )
    helppath= T("Sal:GraceScheme:Scheme");
  else if ( syntaxId==syntaxLisp )
    helppath= T("GraceScheme:Scheme");    
#else
  if ( syntaxId==syntaxSal )
    helppath = T("Sal:CommonMusic:CommonLispMusic:CommonLisp");
 else if ( syntaxId==syntaxLisp )
    helppath = T("CommonMusic:CommonLispMusic:CommonLisp");
#endif

  help=SymbolHelp::getInstance()->lookupHelp(text, helppath );
  printf("SymbolHelp='%s'\n", help.toUTF8());
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
