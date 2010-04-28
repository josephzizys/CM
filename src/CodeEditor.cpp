/*=======================================================================*
  Copyright (c) 2010 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify
  it under the terms of the Lisp Lesser Gnu Public License. The text
  of this agreement is available at http://www.cliki.net/LLGPL
 *=======================================================================*/

#include "Enumerations.h"
#include "Commands.h"
#include "Menus.h"
#include "Preferences.h"
#include "Syntax.h"
#include "CodeEditor.h"
#include "Console.h"
#include "Scheme.h"
#include "Main.h"
#include "Help.h"
#include <iostream>
#include <limits>

/*=======================================================================*
                               CodeEditorWindow
 *=======================================================================*/

CodeEditorWindow::CodeEditorWindow (File file, String text, int synt, String title)
  : DocumentWindow(String::empty, Colours::white, DocumentWindow::allButtons, true)
{
  setMenuBar(this);
  Preferences* prefs=Preferences::getInstance();
  if (file.existsAsFile())
    {
      if (synt==TextIDs::Empty)
        synt=TextIDs::fromFileType(file.getFileExtension());
      if (synt<TextIDs::Text || synt>TextIDs::Fomus)
        synt=TextIDs::Text;
      text=file.loadFileAsString();
    }
  else
    {
      if (synt==TextIDs::Empty)
        synt=prefs->getIntProp(T("EditorSyntax"), TextIDs::Lisp);
      file=File::nonexistent;
    }
  sourcefile=file;
  document.setNewLineCharacters(T("\n"));
  document.replaceAllContent(String(text));
  document.setSavePoint();
  document.clearUndoHistory();
  // parse optional first-line buffer customizations comment. we have
  // to parse customizations before the buffer is created since the
  // comment may declare a specific buffer syntax and this cannot be
  // altered after the buffer is created. if no comment then customs
  // will be null.
  XmlElement* customs=getCustomizations();
  if (customs && customs->hasAttribute(T("syntax:")))
    synt=customs->getIntAttribute(T("syntax:")); 
  Syntax* syntax;
  switch (synt)
    {
    case TextIDs::Text: syntax=TextSyntax::getInstance(); break;
    case TextIDs::Lisp: syntax=LispSyntax::getInstance(); break;
    case TextIDs::Sal: syntax=SalSyntax::getInstance(); break;
    case TextIDs::Sal2: syntax=Sal2Syntax::getInstance(); break;
    default: syntax=TextSyntax::getInstance(); break;
    }
  // create the code buffer and add it to the content component (the
  // buffer is not the content component so the window can contain
  // other components eg a mode line, toolbar, etc)
  CodeBuffer* buffer=new CodeBuffer(document, syntax, &commands, customs);
  EditorComponent* edcomp=new EditorComponent();
  setContentComponent(edcomp);
  // now set window and content component's size to buffer's optimum
  // size before adding the buffer (so buffer doesnt get resized by
  // the window sizing)
  centreWithSize(jmin(800, buffer->getWidth()), 
                 jmin(800, buffer->getHeight()));
  // now add the buffer to the content component
  edcomp->setCodeBuffer(buffer);
  // add customization comment to new empty buffers (???)
  if (text.isEmpty())
    writeCustomComment(false);
  commands.registerAllCommandsForTarget(this);
  // ARRRG DONT DO THIS OR GRACE WILL CRASH WHEN THE WINDOW IS CLOSED
  //setApplicationCommandManagerToWatch(&commands)
  commands.setFirstCommandTarget(this);
  updateKeyPressesForEditMode();
  setWantsKeyboardFocus(false); // let buffer have focus
  setWindowTitle(title);
  setResizable(true, true); 
  setUsingNativeTitleBar(true);
  setDropShadowEnabled(true);
  if (customs) delete customs;
  WindowTypes::setWindowType(this, WindowTypes::CodeEditor);
  setVisible(true);
}

CodeEditorWindow::~CodeEditorWindow ()
{
  // deleteing an zeroing the buffer first seems to take care of the
  // asserts in juce_amalgamated.
  commands.setFirstCommandTarget(0);
  setMenuBar(0);
  EditorComponent* comp=(EditorComponent*)getContentComponent();
  comp->deleteCodeBuffer();
}

void CodeEditorWindow::closeButtonPressed ()
{
  if (getCodeBuffer()->isChanged())
    {
      int v=AlertWindow::showYesNoCancelBox(AlertWindow::QuestionIcon, T("Close"),
                                            T("Save changes before closing?"),
                                            T("Save and Close"),
                                            T("Close Without Saving"),
                                            T("Cancel"));
      if (v==0) return;
      if (v==1) saveFile(false);
    }
  delete this;
}

ApplicationCommandTarget* CodeEditorWindow::getNextCommandTarget()
{
  return Console::getInstance();
}

void CodeEditorWindow::getAllCommands(Array<CommandID>& commands)
{
  const CommandID ids[] = 
    {
      CommandIDs::EditorNew,         // File menu
      CommandIDs::EditorOpen,
      CommandIDs::PrefsOpenRecent + 0,
      CommandIDs::PrefsOpenRecent + 1,
      CommandIDs::PrefsOpenRecent + 2,
      CommandIDs::PrefsOpenRecent + 3,
      CommandIDs::PrefsOpenRecent + 4,
      CommandIDs::PrefsOpenRecent + 5,
      CommandIDs::PrefsOpenRecent + 6,
      CommandIDs::PrefsOpenRecent + 7,
      CommandIDs::PrefsOpenRecent + 8,
      CommandIDs::PrefsOpenRecent + 9,
      CommandIDs::PrefsOpenRecent + 10,
      CommandIDs::PrefsOpenRecent + 11,
      CommandIDs::PrefsOpenRecent + 12,
      CommandIDs::PrefsOpenRecent + 13,
      CommandIDs::PrefsOpenRecent + 14,
      CommandIDs::PrefsOpenRecent + 15,
      CommandIDs::PrefsClearOpenRecent,
      CommandIDs::EditorSave,
      CommandIDs::EditorSaveAs,
      CommandIDs::LispLoadFile,
      CommandIDs::PrefsLoadRecent + 0,
      CommandIDs::PrefsLoadRecent + 1,
      CommandIDs::PrefsLoadRecent + 2,
      CommandIDs::PrefsLoadRecent + 3,
      CommandIDs::PrefsLoadRecent + 4,
      CommandIDs::PrefsLoadRecent + 5,
      CommandIDs::PrefsLoadRecent + 6,
      CommandIDs::PrefsLoadRecent + 7,
      CommandIDs::PrefsLoadRecent + 8,
      CommandIDs::PrefsLoadRecent + 9,
      CommandIDs::PrefsLoadRecent + 10,
      CommandIDs::PrefsLoadRecent + 11,
      CommandIDs::PrefsLoadRecent + 12,
      CommandIDs::PrefsLoadRecent + 13,
      CommandIDs::PrefsLoadRecent + 14,
      CommandIDs::PrefsLoadRecent + 15,
      CommandIDs::PrefsClearLoadRecent,      
      CommandIDs::EditorShowDirectory,
      CommandIDs::EditorSetDirectory,
      CommandIDs::EditorClose,      
      CommandIDs::AppQuit,

      CommandIDs::EditorUndo,        // Edit menu
      CommandIDs::EditorRedo,
      CommandIDs::EditorDelete,
      CommandIDs::EditorCut,
      CommandIDs::EditorCopy,
      CommandIDs::EditorPaste,
      CommandIDs::EditorSelectAll,
      CommandIDs::EditorIndent,
      CommandIDs::EditorCommentOut,
      CommandIDs::EditorUncommentOut,
      CommandIDs::EditorFind,

      CommandIDs::EditorSyntax + TextIDs::Text,    // Options menu
      CommandIDs::EditorSyntax + TextIDs::Lisp,
      CommandIDs::EditorSyntax + TextIDs::Sal,
      CommandIDs::EditorSyntax + TextIDs::Sal2,
      CommandIDs::EditorFontSize + 10,
      CommandIDs::EditorFontSize + 12,
      CommandIDs::EditorFontSize + 14,
      CommandIDs::EditorFontSize + 16,
      CommandIDs::EditorFontSize + 18,
      CommandIDs::EditorFontSize + 20,
      CommandIDs::EditorFontSize + 22,
      CommandIDs::EditorFontSize + 24,
      CommandIDs::EditorFontSize + 26,
      CommandIDs::EditorFontSize + 28,
      CommandIDs::EditorFontSize + 30,
      CommandIDs::EditorFontSize + 32,
      CommandIDs::EditorFontLarger,
      CommandIDs::EditorFontSmaller,
      CommandIDs::EditorTheme + 0,
      CommandIDs::EditorTheme + 1,
      CommandIDs::EditorTheme + 2,
      CommandIDs::EditorTheme + 3,
      CommandIDs::EditorTheme + 4,
      CommandIDs::EditorTheme + 5,
      CommandIDs::EditorTheme + 6,
      CommandIDs::EditorTheme + 7,
      CommandIDs::EditorParensMatching,
      CommandIDs::EditorEmacsMode,
      CommandIDs::EditorDefaultFontSize,
      CommandIDs::EditorDefaultSyntax,
      CommandIDs::EditorDefaultTheme,

      CommandIDs::EditorReadCustom,
      CommandIDs::EditorSaveCustom,
      CommandIDs::EditorExecute,      // Eval menu
      CommandIDs::EditorExpand,
      CommandIDs::SchedulerStop,
      CommandIDs::SchedulerPause,

      CommandIDs::EditorSymbolHelp
    } ;
  commands.addArray(ids, sizeof(ids) / sizeof(CommandID));       
}

void CodeEditorWindow::getCommandInfo(const CommandID id, ApplicationCommandInfo& info)
{
  int comm = CommandIDs::getCommand(info.commandID);
  int data = CommandIDs::getCommandData(info.commandID);
  bool text=(document.getNumCharacters()>0);
  info.setActive(true);
  info.setTicked(false);
  // On Windows and Linux the Command key == Emacs Control key so
  // default Command shortcuts are only added if emacs mode is false
  CodeBuffer* buff=getCodeBuffer();
  bool commandkeyactive=SysInfo::isMac(); // (SysInfo::isMac() || !buff->isEmacsMode());
  switch (comm)
    {
      // FILE MENU
    case CommandIDs::EditorNew:
      info.shortName=T("New");
      if (commandkeyactive)
	info.addDefaultKeypress(T('N'), ModifierKeys::commandModifier);
      break;
    case CommandIDs::EditorOpen:
      info.shortName=T("Open...");
      if (commandkeyactive)
	info.addDefaultKeypress(T('O'), ModifierKeys::commandModifier);
      break;
    case CommandIDs::PrefsOpenRecent:
      {
	File f=Preferences::getInstance()->recentlyOpened.getFile(data);
	if (f==File::nonexistent)
	  info.shortName=T("<Unknown File>");
	else
	  info.shortName=f.getFileName();
      }
      break;
    case CommandIDs::PrefsClearOpenRecent:
      info.shortName=T("Clear Menu");
      break;
    case CommandIDs::EditorSave:
      info.shortName=T("Save...");
      if (commandkeyactive)
	info.addDefaultKeypress(T('S'), ModifierKeys::commandModifier);
      info.setActive(buff->isChanged());
      break;
    case CommandIDs::EditorSaveAs:
      info.shortName=T("Save As...");
      if (commandkeyactive)
	info.addDefaultKeypress(T('S'), ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
      break;
    case CommandIDs::LispLoadFile:
      info.shortName=T("Load...");
      break;
    case CommandIDs::PrefsLoadRecent:
      {
	File f=Preferences::getInstance()->recentlyLoaded.getFile(data);
	if (f==File::nonexistent)
	  info.shortName=T("<Unknown File>");
	else
	  info.shortName=f.getFileName();
      }
      break;
    case CommandIDs::PrefsClearLoadRecent:
      info.shortName=T("Clear Menu");
      break;
    case CommandIDs::EditorShowDirectory:
      info.shortName=T("Show Working Directory");
      break;
    case CommandIDs::EditorSetDirectory:
      info.shortName=T("Set Working Directory...");
      break;
    case CommandIDs::EditorClose:
      info.shortName=T("Close");
      if (commandkeyactive)
	info.addDefaultKeypress(T('W'), ModifierKeys::commandModifier);
      break;
    case CommandIDs::AppQuit:
      info.shortName=T("Quit Grace");
      info.addDefaultKeypress(T('Q'), ModifierKeys::commandModifier);
      break;
      // EDIT MENU
   case CommandIDs::EditorUndo:
      info.shortName=T("Undo");
      if (commandkeyactive)
	info.addDefaultKeypress(T('Z'), ModifierKeys::commandModifier);
      info.setActive(document.getUndoManager().canUndo());
      break;
    case CommandIDs::EditorRedo:
      info.shortName=T("Redo");
      if (commandkeyactive)
	info.addDefaultKeypress(T('Z'), ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
      info.setActive(document.getUndoManager().canRedo());
      break;
    case CommandIDs::EditorDelete:
      info.shortName=T("Delete");
      info.setActive(getCodeBuffer()->getHighlightedRegion().getLength()>1);
      break;
    case CommandIDs::EditorCut:
      info.shortName=T("Cut");
      if (commandkeyactive)
	info.addDefaultKeypress(T('X'), ModifierKeys::commandModifier);
      info.setActive(getCodeBuffer()->getHighlightedRegion().getLength()>0);
      break;
    case CommandIDs::EditorCopy:
      info.shortName=T("Copy");
      if (commandkeyactive)
	info.addDefaultKeypress(T('C'), ModifierKeys::commandModifier);
      info.setActive(getCodeBuffer()->getHighlightedRegion().getLength()>0);
      break;
    case CommandIDs::EditorPaste:
      info.shortName=T("Paste");
      if (commandkeyactive)
	info.addDefaultKeypress(T('V'), ModifierKeys::commandModifier);
      info.setActive(SystemClipboard::getTextFromClipboard().length()>0);
      break;
    case CommandIDs::EditorSelectAll:
      info.shortName=T("Select All");
      if (commandkeyactive)
	info.addDefaultKeypress(T('A'), ModifierKeys::commandModifier);
      info.setActive(text);
      break;
    case CommandIDs::EditorIndent:
      info.shortName=T("Indent");
      info.addDefaultKeypress(T('\t'), 0);
      break;
    case CommandIDs::EditorCommentOut:
      info.shortName=T("Comment Region");
      info.setActive(getCodeBuffer()->getHighlightedRegion().getLength()>0);
      break;
    case CommandIDs::EditorUncommentOut:
      info.shortName=T("Uncomment Region");
      info.setActive(getCodeBuffer()->getHighlightedRegion().getLength()>0);
      break;
    case CommandIDs::EditorFind:
      info.shortName=T("Find...");
      if (commandkeyactive)
	info.addDefaultKeypress(T('F'), ModifierKeys::commandModifier);
      info.setActive(text);
      break;
      // OPTIONS MENU
    case CommandIDs::EditorSyntax:
      info.shortName=TextIDs::toString(data);
      info.setTicked(getCodeBuffer()->isTextType(data));
      //      info.setActive(false);
      break;
    case CommandIDs::EditorFontSize:
      info.shortName=String(data);
      info.setTicked(getCodeBuffer()->getFontSize()==data);
      break;
    case CommandIDs::EditorFontLarger:
      info.shortName=T("Font Larger");
      if (commandkeyactive)
	info.addDefaultKeypress(T('='), ModifierKeys::commandModifier);
      break;
    case CommandIDs::EditorFontSmaller:
      info.shortName=T("Font Smaller");
      info.setActive(getCodeBuffer()->getFontSize()>=8);
      if (commandkeyactive)
	info.addDefaultKeypress(T('-'), ModifierKeys::commandModifier);
      break;
    case CommandIDs::EditorTheme:
      {
        XmlElement* theme=Preferences::getInstance()->getColorTheme(data);
        if (theme)
          {
            info.shortName=ColorThemeIDs::getColorThemeName(theme);
            info.setTicked(getCodeBuffer()->getColorTheme()==theme);
          }
        else
          {
            info.shortName=T("<no color theme>");
            info.setActive(false);
          }
      }
      break;
    case CommandIDs::EditorDefaultFontSize:
      info.shortName=T("Make Default Font Size");
      info.setActive(data!=Preferences::getInstance()->getIntProp(T("EditorFontSize")));
      break;
    case CommandIDs::EditorDefaultSyntax:
      info.shortName=T("Make Default Syntax");
      info.setActive(data!=Preferences::getInstance()->getIntProp(T("EditorSyntax")));      
      break;
    case CommandIDs::EditorDefaultTheme:
      {
        XmlElement* theme=getCodeBuffer()->getColorTheme();
        info.shortName=T("Make Default Theme");
        info.setActive(theme!=0 && ColorThemeIDs::getColorThemeName(theme) !=
                       Preferences::getInstance()->getStringProp(T("EditorTheme")));
      }
      break;
    case CommandIDs::EditorSaveCustom:
      info.shortName=T("Save Customizations");
      break;
    case CommandIDs::EditorReadCustom:
      info.shortName=T("Read Customizations");
      info.setActive(isCustomComment());
      break;
    case CommandIDs::EditorParensMatching:
      info.shortName=T("Parentheses Matching");
      info.setTicked(getCodeBuffer()->isParensMatching());
      break;
      // EVAL MENU
    case CommandIDs::EditorEmacsMode:
      info.shortName=T("Emacs Mode");
      info.setTicked(getCodeBuffer()->isEmacsMode());
      break;
    case CommandIDs::EditorExecute:
      info.shortName=T("Execute");
      if (commandkeyactive)
        info.addDefaultKeypress(KeyPress::returnKey, ModifierKeys::commandModifier);
      info.setActive(TextIDs::canExecute(getCodeBuffer()->getTextType()));
      break;
    case CommandIDs::EditorExpand:
      info.shortName=T("Expand");
      if (commandkeyactive)
        info.addDefaultKeypress(KeyPress::returnKey, ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
      info.setActive(TextIDs::canExpand(getCodeBuffer()->getTextType()));
      break;
    case CommandIDs::SchedulerStop:
      info.shortName=T("Abort Processes");
      info.setActive(!SchemeThread::getInstance()->isQueueEmpty());
      break;
    case CommandIDs::SchedulerPause:
      info.shortName=((SchemeThread::getInstance()->isPaused()) ? T("Resume Processes") :
		      T("Pause Processes"));
      info.setActive(!SchemeThread::getInstance()->isQueueEmpty());
      break;
    case CommandIDs::EditorSymbolHelp:
      info.shortName=T("Documention For Symbol under Cursor");
       if (commandkeyactive)
         {
           info.addDefaultKeypress(T('D'), ModifierKeys::commandModifier );
           CodeBuffer* buf=getCodeBuffer();
           tchar chr=buf->getCaretPos().getCharacter();
           info.setActive((buf->getHighlightedRegion().getLength()>0) ||
                          buf->syntax->isWordChar(chr) ||
                          buf->syntax->isSymbolChar(chr));
         }
      break;
    default:
      //      std::cout << "CodeEditorWindow::getCommandInfo: unhandled command: " << comm << "\n";
      break;
    }
}

bool CodeEditorWindow::perform(const ApplicationCommandTarget::InvocationInfo& info)
{
  int comm = CommandIDs::getCommand(info.commandID);
  int data = CommandIDs::getCommandData(info.commandID);
  Preferences* pref=Preferences::getInstance();
  // command invocation cancels a running parens match
  //if (isMatching()) 
  //  stopMatching();
  switch (comm)
    {
    case CommandIDs::EditorNew:
      new CodeEditorWindow(File::nonexistent, String::empty, getCodeBuffer()->getTextType(), String::empty);
      break;
    case CommandIDs::EditorOpen:
      openFile();
      break;
    case CommandIDs::PrefsOpenRecent:
      CodeEditorWindow::openFile(Preferences::getInstance()->recentlyOpened.getFile(data));
      break;
    case CommandIDs::EditorSave:
      saveFile(false);
      break;
    case CommandIDs::EditorSaveAs:
      saveFile(true);
      break;
    case CommandIDs::EditorShowDirectory:
      ((Grace *)JUCEApplication::getInstance())->showWorkingDirectory();
      break;
    case CommandIDs::EditorSetDirectory:
      ((Grace *)JUCEApplication::getInstance())->chooseWorkingDirectory();
      break;
    case CommandIDs::LispLoadFile:
      SchemeThread::getInstance()->load(File::nonexistent,true);	
      break;
    case CommandIDs::PrefsLoadRecent:
      SchemeThread::getInstance()->load(Preferences::getInstance()->recentlyLoaded.getFile(data), true);
      break;
    case CommandIDs::EditorClose:
      closeButtonPressed();
      break;
    case CommandIDs::AppQuit:
      ((ConsoleWindow *)Console::getInstance()->getTopLevelComponent())->closeButtonPressed();
      break;
      // EDIT MENU
    case CommandIDs::EditorUndo:
      getCodeBuffer()->undo();
      getCodeBuffer()->isChanged(true);
      break;
    case CommandIDs::EditorRedo:
      getCodeBuffer()->redo();
      getCodeBuffer()->isChanged(true);
      break;
    case CommandIDs::EditorDelete:
      getCodeBuffer()->cut();
      break;
    case CommandIDs::EditorCut:
      getCodeBuffer()->copyThenCut();
      getCodeBuffer()->isChanged(true);
      break;
    case CommandIDs::EditorCopy:
      getCodeBuffer()->copy();
      break;
    case CommandIDs::EditorPaste:
      getCodeBuffer()->paste();
      getCodeBuffer()->isChanged(true);
      break;
    case CommandIDs::EditorSelectAll:
      getCodeBuffer()->selectAll();
      break;
    case CommandIDs::EditorIndent:
      getCodeBuffer()->indent();
      break;
    case CommandIDs::EditorFind:
      openFindAndReplaceDialog();
      break;
      // OPTIONS MENU
    case CommandIDs::EditorSyntax:
      switchBufferSyntax(data);
      break;
    case CommandIDs::EditorFontSize:
      getCodeBuffer()->setFontSize(data);
      resizeForColumnsAndLines();
      break;
    case CommandIDs::EditorFontLarger:
      getCodeBuffer()->setFontSize(getCodeBuffer()->getFontSize()+1);
      getCodeBuffer()->repaint();
      break;
    case CommandIDs::EditorFontSmaller:
      getCodeBuffer()->setFontSize(jmax(8, getCodeBuffer()->getFontSize()-1));
      getCodeBuffer()->repaint();
      break;
    case CommandIDs::EditorTheme:
      if (XmlElement* theme=Preferences::getInstance()->getColorTheme(data))
        if (getCodeBuffer()->getColorTheme()!=theme)
          getCodeBuffer()->setColorTheme(theme);
      break;
    case CommandIDs::EditorDefaultSyntax:
      Preferences::getInstance()->setIntProp(T("EditorSyntax"), getCodeBuffer()->getTextType());
      break;
    case CommandIDs::EditorDefaultFontSize:
      Preferences::getInstance()->setIntProp(T("EditorFontSize"), getCodeBuffer()->getFontSize());
      break;
    case CommandIDs::EditorDefaultTheme:
      Preferences::getInstance()->setStringProp(T("EditorTheme"), getCodeBuffer()->getColorTheme()->getStringAttribute(T("name")));
      break;
    case CommandIDs::EditorReadCustom:
      applyCustomComment();
      break;
    case CommandIDs::EditorSaveCustom:
      writeCustomComment(true);
      break;
    case CommandIDs::EditorParensMatching:
      getCodeBuffer()->isParensMatching(!getCodeBuffer()->isParensMatching());
      break;
    case CommandIDs::EditorEmacsMode:
      {
	CodeBuffer* buff=getCodeBuffer();
	buff->isEmacsMode(!buff->isEmacsMode()); 
	Preferences::getInstance()->setBoolProp(T("EditorEmacsMode"), buff->isEmacsMode());
	updateKeyPressesForEditMode();
      }
      break;
      // EVAL MENU
    case CommandIDs::EditorExecute:
      getCodeBuffer()->eval(false);
      break;
    case CommandIDs::EditorExpand:
      getCodeBuffer()->eval(true);
      break;
    case CommandIDs::SchedulerStop:
      break;
    case CommandIDs::SchedulerPause:
      break;
    case CommandIDs::EditorSymbolHelp:
      getCodeBuffer()->lookupHelpAtPoint();
      break;
    default:
      std::cout << "CodeEditorWindow::perform: unhandled command: " << comm << "\n";
    }
  return true;
}

const StringArray CodeEditorWindow::getMenuBarNames()
{
  const tchar* const menubar [] = 
    {T("File"), T("Edit"), T("Options"), T("Eval"), T("Audio"), T("Windows"), T("Help"), 0};
  return StringArray((const tchar**)menubar);
}

const PopupMenu CodeEditorWindow::getMenuForIndex(int index, const String& name)
{
  ApplicationCommandManager* gmanager=CommandManager::getInstance();
  PopupMenu menu;
  CodeBuffer* buff=getCodeBuffer();
  if (name==T("File")) 
    {
      int num;
      PopupMenu sub;
      menu.addCommandItem(&commands, CommandIDs::EditorNew);
      menu.addCommandItem(&commands, CommandIDs::EditorOpen);
      num=jmin(16, Preferences::getInstance()->recentlyOpened.getNumFiles());
      for (int i=0; i<num; i++) 
        sub.addCommandItem(&commands, CommandIDs::PrefsOpenRecent + i);  
      sub.addSeparator();
      sub.addCommandItem(&commands, CommandIDs::PrefsClearOpenRecent);  
      menu.addSubMenu(T("Open Recent"), sub);
      menu.addSeparator();
      menu.addCommandItem(&commands, CommandIDs::EditorSave);
      menu.addCommandItem(&commands, CommandIDs::EditorSaveAs);
      menu.addSeparator();
      menu.addCommandItem(&commands, CommandIDs::LispLoadFile);
      sub.clear();
      num=jmin(16, Preferences::getInstance()->recentlyLoaded.getNumFiles());
      for (int i=0; i<num; i++) 
        sub.addCommandItem(&commands, CommandIDs::PrefsLoadRecent + i);  
      sub.addSeparator();
      sub.addCommandItem(&commands, CommandIDs::PrefsClearLoadRecent);
      menu.addSubMenu(T("Load Recent"), sub);
      menu.addSeparator();
      menu.addCommandItem(&commands, CommandIDs::EditorShowDirectory);
      menu.addCommandItem(&commands, CommandIDs::EditorSetDirectory);
      menu.addSeparator();
      menu.addCommandItem(&commands, CommandIDs::EditorClose);
      menu.addCommandItem(&commands, CommandIDs::AppQuit);
    }
  else if (name==T("Edit")) 
    {
      menu.addCommandItem(&commands, CommandIDs::EditorUndo);
      menu.addCommandItem(&commands, CommandIDs::EditorRedo);
      menu.addSeparator();
      menu.addCommandItem(&commands, CommandIDs::EditorDelete);
      menu.addCommandItem(&commands, CommandIDs::EditorCut);
      menu.addCommandItem(&commands, CommandIDs::EditorCopy);
      menu.addCommandItem(&commands, CommandIDs::EditorPaste);
      menu.addCommandItem(&commands, CommandIDs::EditorSelectAll);
      menu.addSeparator();
      menu.addCommandItem(&commands, CommandIDs::EditorIndent);
      menu.addCommandItem(&commands, CommandIDs::EditorCommentOut);
      menu.addCommandItem(&commands, CommandIDs::EditorUncommentOut);
      menu.addSeparator();
      menu.addCommandItem(&commands, CommandIDs::EditorFind);
    }
  else if (name==T("Options")) 
    {
      PopupMenu sub1, sub2, sub3;
      sub1.addCommandItem(&commands, CommandIDs::EditorSyntax+TextIDs::Text);
      sub1.addCommandItem(&commands, CommandIDs::EditorSyntax+TextIDs::Lisp);
      sub1.addCommandItem(&commands, CommandIDs::EditorSyntax+TextIDs::Sal);
      sub1.addCommandItem(&commands, CommandIDs::EditorSyntax+TextIDs::Sal2);
      sub1.addSeparator();
      sub1.addCommandItem(&commands, CommandIDs::EditorDefaultSyntax);
      menu.addSubMenu(T("Syntax"), sub1);
      menu.addSeparator();
      for (int i=0; i<jmin(8,Preferences::getInstance()->numColorThemes()); i++)
        sub2.addCommandItem(&commands, CommandIDs::EditorTheme+i);
      sub2.addSeparator();
      sub2.addCommandItem(&commands, CommandIDs::EditorDefaultTheme);
      menu.addSubMenu(T("Theme"), sub2);
      sub3.addCommandItem(&commands, CommandIDs::EditorFontLarger);
      sub3.addCommandItem(&commands, CommandIDs::EditorFontSmaller);
      sub3.addSeparator();
      for (int i=8; i<=32; i+=2)
        sub3.addCommandItem(&commands, CommandIDs::EditorFontSize+i);
      sub3.addSeparator();
      sub3.addCommandItem(&commands, CommandIDs::EditorDefaultFontSize);
      menu.addSubMenu(T("Font Size"), sub3);
      menu.addSeparator();
      menu.addCommandItem(&commands, CommandIDs::EditorSaveCustom);
      menu.addCommandItem(&commands, CommandIDs::EditorReadCustom);
      menu.addSeparator();
      menu.addCommandItem(&commands, CommandIDs::EditorParensMatching);
      menu.addCommandItem(&commands, CommandIDs::EditorEmacsMode);
    }
  else if (name==T("Eval")) 
    {
      menu.addCommandItem(&commands, CommandIDs::EditorExecute);
      menu.addCommandItem(&commands, CommandIDs::EditorExpand);
      menu.addSeparator();
      menu.addCommandItem(&commands, CommandIDs::SchedulerStop);
      menu.addCommandItem(&commands, CommandIDs::SchedulerPause);
    }
  else if (name==T("Audio")) 
    {
      menu=CommandMenus::getAudioMenu(true);
    }
  else if (name==T("Windows")) 
    {
      menu=CommandMenus::getWindowMenu();
    }
  else if (name==T("Help")) 
    {
      menu=CommandMenus::getHelpMenu(WindowTypes::CodeEditor, gmanager);
      menu.addSeparator();
      menu.addCommandItem(&commands, CommandIDs::EditorSymbolHelp);
    }
  return menu;
}

void CodeEditorWindow::menuItemSelected (int id, int index)
{
}

//
///  Implementation
//

CodeBuffer* CodeEditorWindow::getCodeBuffer()
{
  return ((EditorComponent*)getContentComponent())->getCodeBuffer();
}

void CodeEditorWindow::updateKeyPressesForEditMode()
{
  // mac command keypresses do not conflict with control keypresses
  if (SysInfo::isMac())
    return;
  KeyPressMappingSet* keymap=commands.getKeyMappings();
  keymap->clearAllKeyPresses();

  if (getCodeBuffer()->isEmacsMode())
    {
      keymap->addKeyPress(CommandIDs::EditorClose, KeyPress(T('W'), ModifierKeys::commandModifier, 0));
      keymap->addKeyPress(CommandIDs::AppQuit, KeyPress(T('Q'), ModifierKeys::commandModifier, 0));
      keymap->addKeyPress(CommandIDs::EditorExecute, KeyPress::createFromDescription(T("ctrl + return")));
      keymap->addKeyPress(CommandIDs::EditorExpand, KeyPress::createFromDescription(T("ctrl + shift + return")));
    }
  else
    {
      keymap->addKeyPress(CommandIDs::EditorFontLarger, KeyPress(T('='), ModifierKeys::commandModifier, 0));
      keymap->addKeyPress(CommandIDs::EditorFontSmaller, KeyPress(T('-'), ModifierKeys::commandModifier, 0));
      keymap->addKeyPress(CommandIDs::EditorSymbolHelp, KeyPress(T('D'), ModifierKeys::commandModifier, 0));
      keymap->addKeyPress(CommandIDs::EditorNew, KeyPress(T('N'), ModifierKeys::commandModifier, 0));
      keymap->addKeyPress(CommandIDs::EditorOpen, KeyPress(T('O'), ModifierKeys::commandModifier, 0));
      keymap->addKeyPress(CommandIDs::EditorSave, KeyPress(T('S'), ModifierKeys::commandModifier, 0));
      keymap->addKeyPress(CommandIDs::EditorSaveAs, KeyPress(T('S'), ModifierKeys::commandModifier | ModifierKeys::shiftModifier, 0));
      keymap->addKeyPress(CommandIDs::EditorClose, KeyPress(T('W'), ModifierKeys::commandModifier, 0));
      keymap->addKeyPress(CommandIDs::AppQuit, KeyPress(T('Q'), ModifierKeys::commandModifier, 0));
      keymap->addKeyPress(CommandIDs::EditorUndo, KeyPress(T('Z'), ModifierKeys::commandModifier, 0));
      keymap->addKeyPress(CommandIDs::EditorRedo, KeyPress(T('Z'), ModifierKeys::commandModifier | ModifierKeys::shiftModifier, 0));
      keymap->addKeyPress(CommandIDs::EditorCut, KeyPress(T('X'), ModifierKeys::commandModifier, 0));
      keymap->addKeyPress(CommandIDs::EditorCopy, KeyPress(T('C'), ModifierKeys::commandModifier, 0));
      keymap->addKeyPress(CommandIDs::EditorPaste, KeyPress(T('V'), ModifierKeys::commandModifier, 0));
      keymap->addKeyPress(CommandIDs::EditorSelectAll, KeyPress(T('A'), ModifierKeys::commandModifier, 0));
      keymap->addKeyPress(CommandIDs::EditorFind, KeyPress(T('F'), ModifierKeys::commandModifier, 0));
      keymap->addKeyPress(CommandIDs::EditorExecute, KeyPress::createFromDescription(T("ctrl + return")));
      keymap->addKeyPress(CommandIDs::EditorExpand, KeyPress::createFromDescription(T("ctrl + shift + return")));
      //keymap->addKeyPress(CommandIDs::,KeyPress);
    }
}

void CodeEditorWindow::switchBufferSyntax(int newtype)
{
  if (getCodeBuffer()->isTextType(newtype))
    return;
  XmlElement* customs=getCustomizations();  // buffer customizations or null
  EditorComponent* comp=(EditorComponent*)getContentComponent();

  // remove and delete current buffer.
  comp->deleteCodeBuffer();
  // add new buffer
  Syntax* syntax=0;
  switch (newtype)
    {
    case TextIDs::Text: syntax=TextSyntax::getInstance(); break;
    case TextIDs::Lisp: syntax=LispSyntax::getInstance(); break;
    case TextIDs::Sal: syntax=SalSyntax::getInstance(); break;
    case TextIDs::Sal2: syntax=Sal2Syntax::getInstance(); break;
    default: syntax=TextSyntax::getInstance(); break;
    }
  // pass in any existing customizations, the buffer does NOT look at
  // the syntax anymore
  CodeBuffer* buffer=new CodeBuffer(document, syntax, &commands, customs);
  // maintain current size of window.
  buffer->setSize(comp->getWidth(), comp->getHeight());
  comp->setCodeBuffer(buffer);
  if (customs)
    {
      writeCustomComment(false); // update comment with new syntax
      delete customs;
    }
  setWindowTitle();
}

void CodeEditorWindow::resizeForColumnsAndLines()
{
  setSize(jmin(800, getCodeBuffer()->getWidth()), //28
          jmin(800, getCodeBuffer()->getHeight()) );
}

void CodeEditorWindow::setWindowTitle(String title)
{
  if (title.isEmpty())
    {
      if (sourcefile==File::nonexistent)
        {
          title=T("Untitled");
        }
      else
        title = sourcefile.getFileName();
    }
  title << T(" (") << TextIDs::toString(getCodeBuffer()->getTextType()) << T(")");
  setName(title);
}

void CodeEditorWindow::openFile(File file)
{
  if (file==File::nonexistent)
    {
      FileChooser choose (T("Open File"), File::getCurrentWorkingDirectory(), String::empty, true);
      if (choose.browseForFileToOpen())
        file=choose.getResult();
      else return;
    }
  new CodeEditorWindow(file);
  Preferences::getInstance()->recentlyOpened.addFile(file);
}

void CodeEditorWindow::newFile(String title, int synt, String content)
{
  new CodeEditorWindow(File::nonexistent, content, synt, title);
}

void CodeEditorWindow::saveFile(bool saveas)
{
  bool exists=sourcefile.existsAsFile();
  if (saveas || !exists)
    {
      File saveto ((exists) ? sourcefile.getParentDirectory() : File::getCurrentWorkingDirectory());
      FileChooser choose (T("Save File"), saveto, T("*.*"), true);
      if (choose.browseForFileToSave(true))
        sourcefile=choose.getResult();
      else
        return;
    }
  if (sourcefile.replaceWithText(document.getAllContent()))
    {
      getCodeBuffer()->isChanged(false);
      document.setSavePoint();
      if (saveas) document.clearUndoHistory(); // SHOULD I DO THIS?
      setWindowTitle();
      Preferences::getInstance()->recentlyOpened.addFile(sourcefile);
    }
  else
    AlertWindow::showMessageBox(AlertWindow::WarningIcon, T("Save File"), 
                                T("Error saving ") + sourcefile.getFullPathName() + T(". File not saved."));
}

bool CodeEditorWindow::isCustomComment ()
{
  // true if first line in document is a comment line starting with -*-
  // example:  ;; -*- syntax: lisp, theme: "clarity and beauty", -*-
  String line=document.getLine(0);
  //std::cout << "isCustomComment(), first line='" << line.toUTF8() << "'\n";

  if (line.isEmpty()) return false;
  int len=line.length();
  int pos=0;
  while (pos<len && CharacterFunctions::isWhitespace(line[pos])) pos++;
  if (pos==len || line[pos]!=T(';')) return false;
  while (pos<len && line[pos]==T(';')) pos++;
  while (pos<len && CharacterFunctions::isWhitespace(line[pos])) pos++;
  if (pos==len || line.substring(pos,pos+3)!=T("-*-")) return false;
  return true;
}

XmlElement* CodeEditorWindow::getCustomizations ()
{
  // parse customization comment into xml, return null if there is
  // none. make sure you delete the xlm element after you use it!
  if (!isCustomComment()) return 0;
  String line=document.getLine(0).fromFirstOccurrenceOf(T("-*-"), false, false).trimStart();
  StringArray tokens;
  tokens.addTokens(line, T("\t, ;"), T("\""));
  tokens.removeEmptyStrings();
  //for (int i=0; i<tokens.size(); i++) std::cout << "tokens["<<i<<"]='" << tokens[i].toUTF8() << "'\n";
  XmlElement* xml=new XmlElement(T("customizations"));
  // customization comment is case insensitive
  for (int i=0; i<tokens.size()-1; i+=2)
    {
      if (tokens[i].equalsIgnoreCase(T("syntax:") ))
        {
          int n=TextIDs::fromString(tokens[i+1]);
          if (TextIDs::Text<=n && n<=TextIDs::Fomus)
            xml->setAttribute(T("syntax:"), n);
        }
      else if (tokens[i].equalsIgnoreCase(T("font-size:") ))
        {
          float n=tokens[i+1].getFloatValue();
          if (8.0<=n && n<=80.0)
            xml->setAttribute(T("font-size:") , floor(n));
        }
      else if (tokens[i].equalsIgnoreCase(T("theme:")))
        {
          String s=tokens[i+1];
          if (s.isQuotedString())
            s=s.unquoted();
          if (Preferences::getInstance()->getColorTheme(s))
            xml->setAttribute(T("theme:"), s);
        }
      else if (tokens[i].equalsIgnoreCase(T("columns:")))
        {
          int n=tokens[i+1].getIntValue();
          if (18<=n && n<144)
            xml->setAttribute(T("columns:"), n);
        }
      else if (tokens[i].equalsIgnoreCase(T("lines:")))
        {
          int n=tokens[i+1].getIntValue();
          if (10<=n && n<=120)
            xml->setAttribute(T("lines:"), n);
        }
    }
  if (xml->getNumAttributes()==0) 
    {
      delete xml;
      xml=0;
    }
  return xml;
}

void CodeEditorWindow::applyCustomComment()
{
  XmlElement* xml=getCustomizations();
  if (!xml) return;
  
  CodeBuffer* buff=getCodeBuffer();
  //std::cout << "Customizations:\n";
  for (int i=0; i<xml->getNumAttributes(); i++)
    {
      String name=xml->getAttributeName(i);
      //std::cout << "  " << name.toUTF8() << " " << xml->getAttributeValue(i).toUTF8() << "\n";
      if (name==T("syntax:"))
        ;
      else if (name==T("theme:"))
        buff->setColorTheme(Preferences::getInstance()->getColorTheme(xml->getIntAttribute(name)));
      else if (name==T("font-size:"))
        buff->setFontSize(xml->getIntAttribute(name));
      else if (name==T("columns:"))
        buff->setColumns(xml->getIntAttribute(name));
      else if (name==T("lines:"))
        buff->setLines(xml->getIntAttribute(name));
    }
  delete xml;
}

void CodeEditorWindow::writeCustomComment(bool select)
{
  //;; -*- syntax: lisp; theme: "clarity and beauty" -*-
  String custom (T(";;; -*-"));
  CodeBuffer* buffer=getCodeBuffer();
  custom << " syntax: " << TextIDs::toString(getCodeBuffer()->getTextType()) << T(";");
  custom << " font-size: " << buffer->getFontSize() << T(";"); 
  custom << " theme: " << buffer->getColorTheme()->getStringAttribute(T("name")).quoted() << T(";");
  int n=buffer->getColumns();
  if (n!=72) custom << " columns: " << n << T(";");
  n=buffer->getLines();
  if (n!=30) custom << " lines: " << n << T(";");
  custom << " -*-" << document.getNewLineCharacters();
  CodeDocument::Position a (&document,0);
  if (isCustomComment())  // delete existing comment line including eol
    {
      CodeDocument::Position e (&document, 1, 0); //0, INT_MAX);
      document.deleteSection(a,e);
    }
  buffer->goToStartOfDocument(false);

  //std::cout << "after delete, looking at (" << buffer->getCaretPos().getPosition() << "): '" << document.getTextBetween(buffer->getCaretPos(), buffer->getCaretPos().movedBy(1)).toUTF8() << "'\n";

  if (buffer->isEOB())
    custom << document.getNewLineCharacters();
  if ( !CharacterFunctions::isWhitespace( a.getCharacter())) //.movedByLines(1)
    custom << document.getNewLineCharacters();
  buffer->insertTextAtCaret(custom);
  a.setLineAndIndex(1,0);
  buffer->moveCaretTo(a, false);
}

CodeEditorWindow* CodeEditorWindow::getFocusCodeEditor()
{
  for (int i=0; i<TopLevelWindow::getNumTopLevelWindows(); i++)
    {
      TopLevelWindow* w=TopLevelWindow::getTopLevelWindow(i);
      NamedValueSet& s=w->getProperties();
      if (s[ var::identifier(T("FocusEditor")) ]==var(true))
       return (CodeEditorWindow*)w;
    }
  return (CodeEditorWindow*)NULL;
}

/*=======================================================================*
                           Find and Replace Window
 *=======================================================================*/

class FindAndReplaceDialog  : public Component,
                              public ButtonListener,
                              public TextEditorListener
{
public:
  FindAndReplaceDialog ();
  ~FindAndReplaceDialog();
  void resized();
  void buttonClicked (Button* buttonThatWasClicked);
  void textEditorReturnKeyPressed(TextEditor& editor);
  void textEditorTextChanged(TextEditor& editor){}
  void textEditorEscapeKeyPressed(TextEditor& editor){}
  void textEditorFocusLost(TextEditor& editor){}
private:
  Label* label1;
  TextEditor* textEditor1;
  Label* label2;
  TextEditor* textEditor2;
  TextButton* textButton1;
  TextButton* textButton2;
  TextButton* textButton3;
  TextButton* textButton4;
  TextButton* textButton5;
};

class FindAndReplaceWindow : public DocumentWindow
{
public:
  void closeButtonPressed() {delete this;}
  FindAndReplaceWindow(FindAndReplaceDialog* comp) :
    DocumentWindow(T("Find & Replace"), 
		   Colour(0xffe5e5e5),
		   DocumentWindow::closeButton,
		   true)
  {
    comp->setVisible(true);
    centreWithSize(comp->getWidth(),comp->getHeight());
    setContentComponent(comp);
    setResizable(false, false); 
    setUsingNativeTitleBar(true);
    setDropShadowEnabled(true);
    setVisible(true);
  }
  ~FindAndReplaceWindow() {}
};

FindAndReplaceDialog::FindAndReplaceDialog ()
    : label1 (0),
      label2 (0),
      textEditor1 (0),
      textEditor2 (0),
      textButton1 (0),
      textButton2 (0),
      textButton3 (0),
      textButton4 (0),
      textButton5 (0)
{
  addAndMakeVisible (label1 = new Label (String::empty, T("Find:")));
  label1->setFont (Font (15.0000f, Font::plain));
  label1->setJustificationType (Justification::centredRight);
  label1->setEditable (false, false, false);
  label1->setColour (TextEditor::textColourId, Colours::black);
  label1->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (textEditor1 = new TextEditor (String::empty));
  textEditor1->setMultiLine (false);
  textEditor1->setReturnKeyStartsNewLine (false);
  textEditor1->setReadOnly (false);
  textEditor1->setScrollbarsShown (true);
  textEditor1->setCaretVisible (true);
  textEditor1->setPopupMenuEnabled (true);
  textEditor1->setText (String::empty);
  textEditor1->setWantsKeyboardFocus(true);
  textEditor1->addListener(this);

  addAndMakeVisible (label2 = new Label (String::empty, T("Replace:")));
  label2->setFont (Font (15.0000f, Font::plain));
  label2->setJustificationType (Justification::centredRight);
  label2->setEditable (false, false, false);
  label2->setColour (TextEditor::textColourId, Colours::black);
  label2->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (textEditor2 = new TextEditor (String::empty));
  textEditor2->setMultiLine (false);
  textEditor2->setReturnKeyStartsNewLine (false);
  textEditor2->setReadOnly (false);
  textEditor2->setScrollbarsShown (true);
  textEditor2->setCaretVisible (true);
  textEditor2->setPopupMenuEnabled (true);
  textEditor2->setText (String::empty);
  textEditor2->addListener(this);
  
  addAndMakeVisible (textButton1 = new TextButton (String::empty));
  textButton1->setButtonText (T("Replace All"));
  textButton1->setConnectedEdges (Button::ConnectedOnRight);
  textButton1->addButtonListener (this);
  
  addAndMakeVisible (textButton2 = new TextButton (String::empty));
  textButton2->setButtonText (T("Replace"));
  textButton2->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
  textButton2->addButtonListener (this);
  
  addAndMakeVisible (textButton3 = new TextButton (String::empty));
  textButton3->setButtonText (T("Replace & Find"));
  textButton3->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
  textButton3->addButtonListener (this);
  
  addAndMakeVisible (textButton4 = new TextButton (String::empty));
  textButton4->setButtonText (T("Previous"));
  textButton4->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
  textButton4->addButtonListener (this);
  
  addAndMakeVisible (textButton5 = new TextButton (String::empty));
  textButton5->setButtonText (T("Next"));
  textButton5->setConnectedEdges (Button::ConnectedOnLeft);
  textButton5->addButtonListener (this);
  
  setSize (414, 104);
}

FindAndReplaceDialog::~FindAndReplaceDialog()
{
  deleteAndZero (label1);
  deleteAndZero (textEditor1);
  deleteAndZero (label2);
  deleteAndZero (textEditor2);
  deleteAndZero (textButton1);
  deleteAndZero (textButton2);
  deleteAndZero (textButton3);
  deleteAndZero (textButton4);
  deleteAndZero (textButton5);
}

void FindAndReplaceDialog::resized()
{
  label1->setBounds (8, 8, 56, 24);
  textEditor1->setBounds (72, 8, 336, 24);
  label2->setBounds (8, 40, 56, 24);
  textEditor2->setBounds (72, 40, 336, 24);
  textButton1->setBounds (8, 72, 80, 24);
  textButton2->setBounds (88, 72, 80, 24);
  textButton3->setBounds (168, 72, 96, 24);
  textButton4->setBounds (264, 72, 64, 24);
  textButton5->setBounds (328, 72, 80, 24);
}

void FindAndReplaceDialog::textEditorReturnKeyPressed (TextEditor& editor)
{
  if (&editor == textEditor1)
    {
      if (!editor.isEmpty()) 
        textButton5->triggerClick();
    }
  //else if (&editor == textEditor2) {}
}

void FindAndReplaceDialog::buttonClicked (Button* buttonThatWasClicked)
{
  CodeEditorWindow* win=CodeEditorWindow::getFocusCodeEditor();

  if (!win)  // no editor open
    {
      PlatformUtilities::beep();
      return;
    }
  CodeBuffer* buf=win->getCodeBuffer();
  // no find string
  String str=textEditor1->getText();
  if (str.isEmpty())
    {
      PlatformUtilities::beep();
      textEditor1->grabKeyboardFocus();
      return;
    }

  if (buttonThatWasClicked == textButton1)       // Replace All
    {
      if (!buf->replaceAll(str, textEditor2->getText()))
	PlatformUtilities::beep();
    }
  else if (buttonThatWasClicked == textButton2)  // Replace
    {
      if (!buf->replace(textEditor2->getText()))
	PlatformUtilities::beep();
    }
  else if (buttonThatWasClicked == textButton3) // Find & Replace
    {
      if (!buf->replaceAndFind(str, textEditor2->getText()))
	PlatformUtilities::beep();	
    }
  else if (buttonThatWasClicked == textButton4) // Previous
    {
      if (!buf->findPrevious(str))
	PlatformUtilities::beep();
    }
  else if (buttonThatWasClicked == textButton5) // Next
    {
      if (!buf->findNext(str))
	PlatformUtilities::beep();
    }
}

void CodeEditorWindow::openFindAndReplaceDialog()
{
  const String title=T("Find & Replace");
  for (int i=0; i<getNumTopLevelWindows(); i++)
    {
      TopLevelWindow* w=TopLevelWindow::getTopLevelWindow(i);
      if (w && w->getName() == title)
	{
	  w->grabKeyboardFocus();
	  w->toFront(true);
	  return;
	}
    }
  FindAndReplaceDialog* d=new FindAndReplaceDialog();
  FindAndReplaceWindow* w=new FindAndReplaceWindow(d);
  //  d->setVisible(true);
  //  w->setContentComponent(d, true, true);
  //  w->centreWithSize(d->getWidth(), d->getHeight());
  //  w->setUsingNativeTitleBar(true);
  //  w->setDropShadowEnabled(true);
  //  w->setVisible(true);
  d->grabKeyboardFocus();
}


/*=======================================================================*
                                   CodeBuffer
 *=======================================================================*/

CodeBuffer::CodeBuffer(CodeDocument& doc, Syntax* tokenizer, ApplicationCommandManager* commands, XmlElement* customs)
  : document (doc),
    fontsize (16),
    tabwidth (2),
    columns (72),
    lines (30),
    parensmatching(true),
    changed (false),
    colortheme (NULL),
    matchpos (-1),
    CodeEditorComponent(doc, tokenizer)
{
  Preferences* prefs=Preferences::getInstance();
  syntax=tokenizer;
  manager=commands;
  fontsize=prefs->getIntProp(T("EditorFontSize"), 16);
  emacsmode=prefs->getBoolProp(T("EditorEmacsMode"), SysInfo::isMac());
  colortheme=prefs->getColorTheme(prefs->getStringProp(T("EditorTheme"), T("Emacs")));
  if (customs) // file has customizations
    {
      fontsize=customs->getDoubleAttribute(T("font-size:"), fontsize);
      columns=customs->getIntAttribute(T("columns:"), columns);
      lines=customs->getIntAttribute(T("lines:"), lines);
      if (customs->hasAttribute(T("theme:")))
        colortheme=prefs->getColorTheme(customs->getStringAttribute(T("theme:")));
    }
  Font mono (Font::getDefaultMonospacedFontName(), (float)fontsize, Font::plain);
  setFont(mono);
  setTabSize(tabwidth, true);
  setColorTheme(colortheme);
  // 16 is for the scollbars, not sure why i need the extra 4....
  setSize((getCharWidth() * columns)+16+4, (getLineHeight() * lines)+16+4);
  setWantsKeyboardFocus(true);
  setVisible(true);
}

CodeBuffer::~CodeBuffer()
{
}

void CodeBuffer::insertTextAtCaret (const String& textToInsert)
{
  bool add=true;
  bool match=false;
  if (isParensMatchingActive()) 
    stopParensMatching();
  if (textToInsert.length()==1)
    {
      const juce_wchar c=textToInsert[0];
      const bool e=isEmacsMode();
      //      std::cout << "CodeBuffer::insertTextAtCaret='" << c << "'\n";  
      add=false;
      switch (c)
        {
        case T(')') :
        case T('}') :
        case T(']') :
          add=true;
          match=(syntax->isCloseChar(c) && isParensMatching()) ;
          break;
        case 8747: // Meta-b
          if (e) moveWordBackward();
          break;
        case 231:  // Meta-c
          if (e) changeCase(2);
          break;
        case 8706: // Meta-d
          if (e) killWordForward();
          break;
        case 402:  // Meta-f
          if (e) moveWordForward();
          break;
        case 172:  // Meta-l
          if (e) changeCase(0);
          break;
        case 168:  // Meta-u
          if (e) changeCase(1);
          break;
        case 8730: // Meta-v
          if (e) movePageBackward();
          break;
        case 160:  // Meta-spaceKey
          if (e) killWhite();  
          break;
          // case  Meta-backspaceKey
          // killWordBackward();
        default:
          add=true;
          break;
        }
    }
  if (add)
    {
      CodeEditorComponent::insertTextAtCaret(textToInsert);        
      if (match)
        matchParens();
      isChanged(true);
    }
}

bool CodeBuffer::keyPressed (const KeyPress& key)
{
  const int ctrl = ModifierKeys::ctrlModifier;
  const int meta = ModifierKeys::altModifier;
  const int both = (ModifierKeys::ctrlModifier | ModifierKeys::altModifier);
  const bool emacs=isEmacsMode();

  //std::cout << "CodeBuffer::keyPressed key=" << key.getTextDescription().toUTF8() << "\n";
  if (isParensMatchingActive()) 
      stopParensMatching();

  if (key == KeyPress(T('\t')))
    indent();
  // Control commands
  else if (emacs && key == KeyPress(T('a'), ctrl, 0))
    gotoBOL();
  else if (emacs && key == KeyPress(T('b'), ctrl, 0))
    moveCharBackward();
  else if (emacs && key == KeyPress(T('d'), ctrl, 0))
    killCharForward();
  else if (emacs && key == KeyPress(T('e'), ctrl, 0))
    {
      if (prevkey==KeyPress(T('x'), ctrl, 0))
        eval(false);
      else
        gotoEOL();
    }
  else if (emacs && key == KeyPress(T('f'), ctrl, 0))
    {
      if (prevkey==KeyPress(T('x'), ctrl, 0))
        ((CodeEditorWindow *)getTopLevelComponent())->openFile();
      else
        moveCharForward();
    }
  else if (emacs && key == KeyPress(T('h'), ctrl, 0))
    lookupHelpAtPoint();
  else if (emacs && key == KeyPress(T('k'), ctrl, 0))
    killLine();
  else if (emacs && key == KeyPress(T('n'), ctrl, 0))
    moveLineForward();
  else if (emacs && key == KeyPress(T('o'), ctrl, 0))
    openLine();
  else if (emacs && key == KeyPress(T('p'), ctrl, 0))
    moveLineBackward();
  else if (emacs && key == KeyPress(T('s'), ctrl, 0)
           && (prevkey==KeyPress(T('x'), ctrl, 0)))
    ((CodeEditorWindow *)getTopLevelComponent())->saveFile(false);
  else if (emacs && key == KeyPress(T('v'), ctrl, 0))
    movePageForward();
  else if (emacs && key == KeyPress(T('y'), ctrl, 0))
    paste();
  else if (emacs && key == KeyPress(T('x'), ctrl, 0))
    ;  
  // Meta commands  
  else if (emacs && key == KeyPress(T('b'), meta, 0))
    moveWordBackward();
  else if (emacs && key == KeyPress(T('c'), meta, 0))
    changeCase(2);
  else if (emacs && key == KeyPress(T('d'), meta, 0))
    killWordForward();
  else if (emacs && key == KeyPress(T('f'), meta, 0))
    moveWordForward();
  else if (emacs && key == KeyPress(T('l'), meta, 0))
    changeCase(0);
  else if (emacs && key == KeyPress(T('u'), meta, 0))
    changeCase(1);
  else if (emacs && key == KeyPress(T('v'), meta, 0))
    movePageBackward();
  else if (emacs && key == KeyPress(KeyPress::backspaceKey, meta, 0))
    killWordBackward();
  else if (emacs && key == KeyPress(KeyPress::spaceKey, meta, 0))
    killWhite();  
  // Control-Meta commands  
  else if (emacs && key == KeyPress(T('b'), both, 0))
    moveExprBackward();  
  else if (emacs && key == KeyPress(T('f'), both, 0))
    moveExprForward();
  else if (emacs && key == KeyPress(T('k'), both, 0))
    killExprForward();
  // NON emacs additions
  else if (SysInfo::isMac() && key.isKeyCode(KeyPress::rightKey))
    {
      const bool moveInWholeWordSteps = key.getModifiers().isCtrlDown() || key.getModifiers().isAltDown();
      if (key.getModifiers().isCommandDown())
        goToEndOfLine(key.getModifiers().isShiftDown());
      else
        cursorRight(moveInWholeWordSteps, key.getModifiers().isShiftDown());
    }
  else if (SysInfo::isMac() && key.isKeyCode(KeyPress::leftKey))
    {
      const bool moveInWholeWordSteps = key.getModifiers().isCtrlDown() || key.getModifiers().isAltDown();
      if (key.getModifiers().isCommandDown())
        goToStartOfLine(key.getModifiers().isShiftDown());
      else
        cursorLeft(moveInWholeWordSteps, key.getModifiers().isShiftDown());
    }
  else 
    {
      // else try other keypress handlers in this order: (1) Juce
      // CodeEditorComponent (2) the CodeEditorWindow and (3) the
      // global command manager
      prevkey=KeyPress(key);
      if (CodeEditorComponent::keyPressed(key)) // search component's keypress
        {
          // ')' moved to insertTextAtCursor
          //          juce_wchar chr=key.getTextCharacter();
          //          if (isParensMatching() && (chr==T(')') || chr==T('}')))
          //            matchParens();
          //          //std::cout << "returning true from CodeEditorComponent";
          //          isChanged(true); // if handled give up and 
          //          //(KeyPress::leftKey)(KeyPress::rightKey) (KeyPress::upKey) (KeyPress::downKey) (KeyPress::pageDownKey) (KeyPress::pageUpKey) (KeyPress::homeKey) (KeyPress::endKey)
          return true;
        }
      //std::cout << "searching window manager for keypress=" << key.getTextDescription().toUTF8() << "\n";
      CommandID id=manager->getKeyMappings()->findCommandForKeyPress(key);
      //std::cout << "command id=" << id << "\n";
      if (id)
        {
          //std::cout << "found " << id << " in window command mananger\n";
          manager->invokeDirectly(id, true);
          //std::cout << "done invoking !\n";
          return true;
        }
      // Otherwise try Global command manager
      id=CommandManager::getInstance()->getKeyMappings()->findCommandForKeyPress(key);
      if (id)
        { 
          //std::cout << "found " << id << " in global command mananger\n";
          CommandManager::getInstance()->invokeDirectly(id, true);
          //std::cout << "done invoking !\n";
          return true;
        }
      std::cout << "no handler for keypress, setting buffer changed=true\n";
      isChanged(true); // unhandled so adding chars to the buffer
      return false;     
    }
  prevkey=KeyPress(key);
  return true;
} 

void CodeBuffer::mouseDown (const MouseEvent& e)
{
  if (e.mods.isPopupMenu())
    {
      PopupMenu m;
      // m.setLookAndFeel (&getLookAndFeel());
      addPopupMenuItems (m, &e);
      const int result = m.show();
      if (result != 0)
        performPopupMenuAction(result);
    }
  else
    CodeEditorComponent::mouseDown(e);
}

void CodeBuffer::performPopupMenuAction (int menuItemID)
{
  std::cout << "performPopupMenuAction, id=" << menuItemID << "\n";
}

void CodeBuffer::mouseDoubleClick (const MouseEvent &e)
{
  tchar c=getCaretPos().getCharacter();
  switch (c)
    {
    case T('(') :
    case T('{') :
      {
        CodeDocument::Position a (getCaretPos());
        moveExprForward();
        CodeDocument::Position b (getCaretPos());
        if (b!=a) moveCaretTo(a,true);
        break;
      }
    case T(')') :
    case T('}') :
      {
        CodeDocument::Position a (getCaretPos());
        moveExprBackward();
        CodeDocument::Position b (getCaretPos());
        if (b!=a) moveCaretTo(a,true);
        break;
      }
    default:
      CodeEditorComponent::mouseDoubleClick(e);
      break;
    }
}  	

void CodeBuffer::addPopupMenuItems (PopupMenu& m, const MouseEvent*)
{
  m.addCommandItem(manager, CommandIDs::EditorDelete);
  m.addCommandItem(manager, CommandIDs::EditorCut);
  m.addCommandItem(manager, CommandIDs::EditorCopy);
  m.addCommandItem(manager, CommandIDs::EditorPaste);
  m.addSeparator();
  m.addCommandItem(manager, CommandIDs::EditorSelectAll);
  m.addSeparator();
  m.addCommandItem(manager, CommandIDs::EditorUndo);
  m.addCommandItem(manager, CommandIDs::EditorRedo);
}

void CodeBuffer::matchParens()
{
  std::cout << "matchParens()\n";
  CodeDocument::Position pos (getCaretPos());
  pos.moveBy(-1);
  int b=pos.getPosition();
  int scan=syntax->scanCode(document, pos, false, ScanIDs::MoveExpressions);
  if (scan<=ScanIDs::SCAN_EMPTY)
    return;
  int a=pos.getPosition();
  if (a<b)
    startParensMatching(pos,getCaretPos());
}

bool CodeBuffer::isParensMatching()
{
  return parensmatching; 
}

void CodeBuffer::isParensMatching(bool val)
{
  parensmatching=val; 
}

bool CodeBuffer::isParensMatchingActive()
{
  // true if we are matching right now
  return (matchpos > -1); 
}

void CodeBuffer::startParensMatching(const CodeDocument::Position pos1, const CodeDocument::Position pos2)
{
  moveCaretTo(pos1, false);
  //setColour(TextEditor::caretColourId, Colours::red);
  matchpos=pos2.getPosition();
  startTimer(1000);
}

void CodeBuffer::timerCallback()
{
  stopParensMatching();
}

void CodeBuffer::stopParensMatching()
{
  if (matchpos > -1)
    {
      moveCaretTo(CodeDocument::Position(&document, matchpos), false);
      //setColour(TextEditor::caretColourId, Colours::black);
      matchpos=-1;
      if (isTimerRunning())
	stopTimer();
    }
}

void CodeBuffer::focusGained(Component::FocusChangeType cause)
{
  // When a code buffer is selected is becomes the "focus" and only
  // loses focus when a different code buffer is selected, i.e. the
  // editing focus is maintained even when the window itself is not
  // the active window
  TopLevelWindow* w=NULL;
  // clear any other editing window of the focus
  for (int i=0; i<TopLevelWindow::getNumTopLevelWindows(); i++)
    {
      w=TopLevelWindow::getTopLevelWindow(i);
      NamedValueSet& s=w->getProperties();
      if (s.contains(var::identifier(T("FocusEditor"))))
        s.set(var::identifier(T("FocusEditor")), var(false)) ;
      // FIXME
      //if (w->getComponentPropertyBool(T("FocusEditor"), false))
      //	w->setComponentProperty(T("FocusEditor"), false);
    }
  // select this one
  // FIXME
  //  getTopLevelComponent()->setComponentProperty(T("FocusEditor"), true);
  getTopLevelComponent()->getProperties().set(var::identifier(T("FocusEditor")), var(true));
}

//
// Implemenation
//

XmlElement* CodeBuffer::getColorTheme()
{
  return colortheme;
}

void CodeBuffer::setColorTheme(XmlElement* theme)
{
  colortheme=theme;
  // CodeEditorComponent::backgroundColourId,    0xffffffff,
  // CodeEditorComponent::caretColourId,         0xff000000,
  // CodeEditorComponent::highlightColourId,     0x401111ee,
  // CodeEditorComponent::defaultTextColourId,   0xff000000,
  setColour(CodeEditorComponent::backgroundColourId,
            ColorThemeIDs::fromHtmlColorString(theme->getStringAttribute(T("background")),
                                               LookAndFeel::getDefaultLookAndFeel().
                                               findColour(CodeEditorComponent::backgroundColourId)));
  setColour(CodeEditorComponent::caretColourId,
            ColorThemeIDs::fromHtmlColorString(theme->getStringAttribute(T("cursor")),
                                               LookAndFeel::getDefaultLookAndFeel().
                                               findColour(CodeEditorComponent::caretColourId))
            );
  setColour(CodeEditorComponent::highlightColourId,
            ColorThemeIDs::fromHtmlColorString(theme->getStringAttribute(T("region")),
                                               LookAndFeel::getDefaultLookAndFeel().
                                               findColour(CodeEditorComponent::highlightColourId)));
  // fetch the color attribute names that the syntax uses. each index
  // in the array is a syntax token type, each array string is its
  // ColorTheme color (xml attribute name)
  const StringArray attrs=syntax->getTokenTypes(); 
  // set the color for each syntax tokentype
  for (int toktyp=0; toktyp<attrs.size(); toktyp++)
    if (ColorThemeIDs::fromString(attrs[toktyp])!=ColorThemeIDs::Empty)
      {
        const Colour color=ColorThemeIDs::fromHtmlColorString(theme->getStringAttribute(attrs[toktyp]));
        setColourForTokenType(toktyp, color);
      }
}

bool CodeBuffer::isChanged()
{
  return changed;
}

void CodeBuffer::isChanged(bool ch)
{
  changed=ch;
}

int CodeBuffer::getTextType()
{
  return syntax->getTextType();
}

bool CodeBuffer::isTextType(int type)
{
  return (getTextType()==type);
}

int CodeBuffer::getFontSize()
{
  return fontsize;
}

void CodeBuffer::setFontSize(int size)
{
  fontsize=size;
  Font mono (Font::getDefaultMonospacedFontName(), size, Font::plain);
  setFont(mono);
}

int CodeBuffer::getTabWidth()
{
  return getTabSize();
}

void CodeBuffer::setTabWidth(int siz)
{
  setTabSize(siz, true);
}

int CodeBuffer::getColumns()
{
  return columns;
}

void CodeBuffer::setColumns(int cols, bool redisplay)
{
  columns=jmax(cols, 1);
  if (redisplay)
    {
      Font mono (Font::getDefaultMonospacedFontName(), (float)fontsize, Font::plain);
      setSize(getCharWidth() * getColumns(), getLineHeight() * getLines() );
      // RESIZE WINDOW
      ((CodeEditorWindow*)getTopLevelComponent())->resizeForColumnsAndLines();
    }
}

int CodeBuffer::getLines()
{
  return lines;
}

void CodeBuffer::setLines(int num, bool redisplay)
{
  lines=jmax(num,1);
  if (redisplay)
    {
      ((CodeEditorWindow*)getTopLevelComponent())->resizeForColumnsAndLines();
    }
}  

bool CodeBuffer::isEmacsMode()
{
  return emacsmode;
}

void CodeBuffer::isEmacsMode(bool mode)
{
  emacsmode=mode;
}

///
///  Point Functions
///

CodeDocument::Position CodeBuffer::getBOL(const CodeDocument::Position pos)
{
  return CodeDocument::Position(&document, pos.getLineNumber(), 0);
}

CodeDocument::Position CodeBuffer::getBOL()
{
  return getBOL(getCaretPos());
}

CodeDocument::Position CodeBuffer::getEOL(const CodeDocument::Position pos)
{
  return CodeDocument::Position(&document, pos.getLineNumber(), INT_MAX);
}

CodeDocument::Position CodeBuffer::getEOL()
{
  return getEOL(getCaretPos());
}

CodeDocument::Position CodeBuffer::getEOB() 
{
  return CodeDocument::Position(&document, INT_MAX);
}

CodeDocument::Position CodeBuffer::getBOB() 
{
  return CodeDocument::Position(&document, 0);
}

bool CodeBuffer::isBOB()
{
  return (getCaretPos().getPosition()==0);
}

bool CodeBuffer::isEOB() 
{
  CodeDocument::Position eob (&document, INT_MAX);
  return (getCaretPos() == eob);
}

bool CodeBuffer::isBOL() 
{
  return (getCaretPos().getIndexInLine() == 0);
}

bool CodeBuffer::isEOL() 
{
  CodeDocument::Position here=getCaretPos();
  CodeDocument::Position there (&document, here.getLineNumber(), INT_MAX);
  return (here.getIndexInLine()==there.getIndexInLine());
}

/*=======================================================================*
                         Emacs Cursor Motion Functions
 *=======================================================================*/

CodeDocument::Position CodeBuffer::gotoBOB(bool sel)
{
  goToStartOfDocument(sel);
  return getCaretPos();
}

CodeDocument::Position CodeBuffer::gotoEOB(bool sel)
{
  goToEndOfDocument(sel);
  return getCaretPos();
}

CodeDocument::Position CodeBuffer::gotoBOL(bool sel)
{
  //goToStartOfLine(false); // this stops at whitespace
  CodeDocument::Position here=getCaretPos();
  CodeDocument::Position there (&document, here.getLineNumber(), 0);
  moveCaretTo(there, sel);
  return getCaretPos();
}

CodeDocument::Position CodeBuffer::gotoEOL(bool sel)
{
  goToEndOfLine(sel);
  return getCaretPos();
}

void CodeBuffer::moveCharForward(bool sel)
{
  cursorRight(false, sel);
}

void CodeBuffer::moveCharBackward(bool sel)
{
  cursorLeft(false, sel);
}

void CodeBuffer::moveWordForward(bool sel)
{
  //cursorRight(true,false); 
  CodeDocument::Position pos(getCaretPos());
  int loc=pos.getPosition();
  int eob=getEOB().getPosition();
  // skip over non word, non token characters
  while (loc<eob && !(syntax->isWordChar(pos.getCharacter()) ||
                      syntax->isSymbolChar(pos.getCharacter())))
    pos.setPosition(++loc);
  // skip over word or token characters
  while (loc<eob && (syntax->isWordChar(pos.getCharacter()) ||
                     syntax->isSymbolChar(pos.getCharacter())))
    pos.setPosition(++loc);
  moveCaretTo(pos, sel);
}

void CodeBuffer::moveWordBackward(bool sel)
{
  //cursorLeft(true,false);
  CodeDocument::Position pos(getCaretPos());
  int loc=pos.getPosition();
  int bob=-1;
  // in backwards scanning cursor is always 1 past starting position
  pos.setPosition(--loc); 
  // skip over non word, non token characters
  while (loc>bob && !(syntax->isWordChar(pos.getCharacter()) ||
                      syntax->isSymbolChar(pos.getCharacter())))
    pos.setPosition(--loc);
  // skip over word or token characters
  while (loc>bob && (syntax->isWordChar(pos.getCharacter()) ||
                     syntax->isSymbolChar(pos.getCharacter())))
    pos.setPosition(--loc);
  // loc is is now 1 BELOW position.
  pos.setPosition(loc+1);
  moveCaretTo(pos, sel);
}

void CodeBuffer::moveExprForward(bool sel)
{
  CodeDocument::Position pos (getCaretPos());
  int scan=syntax->scanCode(document, pos, true, ScanIDs::MoveExpressions);
  if (scan<0)
    PlatformUtilities::beep();
  else
    moveCaretTo(pos, sel);
}

void CodeBuffer::moveExprBackward(bool sel)
{
  CodeDocument::Position pos (getCaretPos());
  // if moving backwards the cursor is one char beyond start of scan
  pos.moveBy(-1);
  int scan=syntax->scanCode(document, pos, false, ScanIDs::MoveExpressions);
  if (scan<0)
    PlatformUtilities::beep();
  else
    moveCaretTo(pos, sel);
}

void CodeBuffer::moveLineForward(bool sel)
{
  cursorDown(sel);
}

void CodeBuffer::moveLineBackward(bool sel)
{
  cursorUp(sel);
}

void CodeBuffer::movePageForward(bool sel)
{
  pageDown(sel);
}

void CodeBuffer::movePageBackward(bool sel)
{
  pageUp(sel);
}

/*=======================================================================*
                            Find And Replace Methods
 *=======================================================================*/

bool CodeBuffer::findPrevious(String str, bool wrap)
{
  CodeDocument::Position pos(getCaretPos());
  pos.moveBy(-getHighlightedRegion().getLength());
  int wid=str.length();
  int got=-1;
  while (true)
    {
      if (pos.getPosition()<=wid) // not enough chars to make a match
	{
	  if (wrap)
	    {
	      wrap=false;
	      pos.setPosition(INT_MAX);
	    }
	  else
	    break;
	}
      CodeDocument::Position bot=pos.movedBy(-100);
      String tmp=document.getTextBetween(bot, pos);
      int len=tmp.length();
      got=tmp.lastIndexOf(str);
      if (got>-1)
	{
	  pos.moveBy(-(len-got));
	  break;
	}
      // next search position must overlapping current end
      pos.setPosition(bot.getPosition()+wid);
    }
  if (got>-1)
    {
      Range<int> r (pos.getPosition(), pos.getPosition()+wid);
      setHighlightedRegion(r);
      return true;
    }
  return false;
}

bool CodeBuffer::findNext(String str, bool wrap)
{
  // start looking at current cursor position (if region exists caret
  // position is end of region)
  CodeDocument::Position pos (getCaretPos());
  int eob=getEOB().getPosition();
  int wid=str.length();
  int got=-1;
  while (true)
    {
      //std::cout << "Top of loop, pos="<<pos.getPosition() 
      //          << ", pos+wid=" << pos.getPosition()+wid << ", eob=" << eob << "\n";
      if (pos.getPosition()+wid>eob) // not enough chars to make a match
	{
	  if (wrap)
	    {
	      wrap=false;
	      pos.setPosition(0);
	    }
	  else
	    break;
	}
      const String tmp=document.getTextBetween(pos, pos.movedBy(100));
      got=tmp.indexOf(str);
      if (got>-1)
	{
	  pos.moveBy(got);
	  break;
	}
      int len=tmp.length();
      // next search position must overlapping current end
      //std::cout<< "bottom of loop, moving pos by " << len-wid+1 << "\n";
      pos.moveBy(len-wid+1);
    }
  if (got>-1)
    {
      Range<int> r (pos.getPosition(), pos.getPosition()+wid);
      setHighlightedRegion(r);
      return true;
    }
  return false;
}
bool CodeBuffer::replaceAll(String str, String rep)
{
  int n=0;
  while (findNext(str, false))
    {
      n++;
      replace(rep);
    }
  return (n>0);
}

bool CodeBuffer::replace(String rep)
{
  if (!(getHighlightedRegion().getLength()>0))
    return false;
  insertTextAtCaret(rep);
  isChanged(true);
  return true;
}

bool CodeBuffer::replaceAndFind(String str, String rep)
{
  if (replace(rep))
    return findNext(str);
  return false;
}

/*=======================================================================*
                                 Symbol Help
 *=======================================================================*/

void CodeBuffer::lookupHelpAtPoint()
{
  bool region=(getHighlightedRegion().getLength() > 0);
  String text;
  String helppath;

  switch (getTextType())
    {
    case TextIDs::Sal:
      helppath=T("Sal:CM");
      break;
    case TextIDs::Sal2:
      helppath=T("Sal:CM");
      break;
    case TextIDs::Lisp:
      helppath=T("CM");
      break;
    default:
      return;
    }
  helppath<<T(":SndLib:Scheme");
  CodeDocument::Position a;
  CodeDocument::Position e;
  if (region)
    {
      a=CodeDocument::Position(&document, getHighlightedRegion().getStart());
      e=CodeDocument::Position(&document, getHighlightedRegion().getEnd()+1);
    }
  else
    {
      a=getCaretPos();
      e=a.movedBy(INT_MAX); // EOB
      int p=a.getPosition();
      // cursor always one past start of backwards positions
      a.moveBy(-1);
      p--;
      while (p>=0 && (syntax->isWordChar(a.getCharacter()) || syntax->isSymbolChar(a.getCharacter())))
        {
          a.moveBy(-1);
          p--;
        }
      // IF there is a token it starts at p+1
      a.setPosition(p+1);
    }
  
  CodeDocument::Position b (a);
  while (b!=e && (syntax->isWordChar(b.getCharacter()) || syntax->isSymbolChar(b.getCharacter())))
    b.moveBy(1);
  // if B>A then we have a token and B is one past it.
  if (!(b==a))
    {
      text=document.getTextBetween(a, b);
      std::cout << "HelpAtPoint='" << text.toUTF8() << T("'\n");
      Help::getInstance()->symbolHelp(text, helppath);
    }
}

/*=======================================================================*
                             Emacs Editing Commands
 *=======================================================================*/

void CodeBuffer::killCharForward()
{
  deleteForward(false);
  isChanged(true);
}

void CodeBuffer::killCharBackward()
{
  backspace(false);
  isChanged(true);
}

void CodeBuffer::killWordForward()
{
  //deleteForward(true);
  if (getCaretPos()!=getEOB())
    {
      moveWordForward(true);
      cut();
      isChanged(true);
    }
}

void CodeBuffer::killWordBackward()
{
  //backspace(true);
  if (getCaretPos()!=getBOB())
    {
      moveWordBackward(true);
      cut();
      isChanged(true);
    }
}

void CodeBuffer::killExprForward()
{
  CodeDocument::Position here (getCaretPos());
  if (here!=getEOB())
    {
      moveExprForward(true);
      // scanning could fail so test if we moved
      if (here!=getCaretPos())
        {
          copyThenCut();
          isChanged(true);
        }
    }
}

void CodeBuffer::killExprBackward()
{
  std::cout << "killExprBackward\n";
}

void CodeBuffer::killLine()
{
  // Kill line adding EOL+1 if line is only white space after point
  CodeDocument::Position to=getEOL();
  String kill=document.getTextBetween(getCaretPos(),to);
  if (!kill.containsNonWhitespaceChars()) // all white or empty
    {
      String eol=document.getNewLineCharacters();
      kill << eol;
      to.moveBy(eol.length());
    }
  moveCaretTo(to, true);
  backspace(false);
  isChanged(true);
  // consecutive kills ADD the kill to clipboard
  if (prevkey==KeyPress(T('k'), ModifierKeys::ctrlModifier, 0))
    kill = SystemClipboard::getTextFromClipboard() + kill;
  SystemClipboard::copyTextToClipboard(kill);
}

void CodeBuffer::killWhite()
{
  CodeDocument::Position p(getCaretPos());
  CodeDocument::Position e=getEOB();
  while (p != e && CharacterFunctions::isWhitespace(p.getCharacter()))
    p.moveBy(1);
  if (getCaretPos()!=p)
    {
      moveCaretTo(p,true);
      backspace(false);
      isChanged(true);
    }
}

void CodeBuffer::changeCase(int flag)
{
  // change case of word at point. 0=lower,1=upper,2=capitalize
  CodeDocument::Position beg=getCaretPos();
  cursorRight(true, true);
  String text=document.getTextBetween(beg, getCaretPos());
  if (text==String::empty)
    return;
  backspace(false);
  if (flag==0)
    text=text.toLowerCase();
  else if (flag==1)
    text=text.toUpperCase();
  else if (flag==2)
    for (int i=0; i<text.length(); i++)
      if (CharacterFunctions::isLetter(text[i]))
        {
          text[i]=CharacterFunctions::toUpperCase(text[i]);
          break;
        }
  insertTextAtCaret(text);
  isChanged(true);
}

void CodeBuffer::killRegion()
{
  std::cout << "killRegion\n";
}

void CodeBuffer::openLine()
{
  CodeDocument::Position here=getCaretPos();
  insertTextAtCaret(document.getNewLineCharacters());
  moveCaretTo(here, false);
  isChanged(true);
}

void CodeBuffer::posInfo(const CodeDocument::Position p)
{
  String s;
  s << p.getCharacter();
  std::cout << "curs=" << p.getPosition() << " (" << p.getLineNumber() << "," << p.getIndexInLine() << "), char='" << s.toUTF8() << "'\n"
            << "line='" << p.getLineText().toUTF8() << "'\n"
            << ", bol?="<< isBOL() << ", eol?=" << isEOL() << ", bob?="<< isBOB() << ", eob?=" << isEOB() << "\n";
}

void CodeBuffer::test(bool forward)
{
}

/*=======================================================================*
                    Evaluation and Syntactic Backward Expression
 *=======================================================================*/

void CodeBuffer::eval(bool expandonly)
{
  if (!TextIDs::canExecute(getTextType()))
    return;
  int regn=getHighlightedRegion().getLength();
  int scan=ScanIDs::SCAN_EMPTY;
  Array<int> epos; // positions of backward exprs
  CodeDocument::Position bot (getCaretPos());
  CodeDocument::Position top (getCaretPos());
  int end=0;  // lowest position possible

  if (regn>0) // if region use its bounds
    {
      bot=CodeDocument::Position(&document, getHighlightedRegion().getStart());
      top=bot.movedBy(regn);
      end=bot.getPosition();
    }
  // process region backwards recording the starting and ending
  // positions of expressions
  //// int n=0;
  while (true /*&& (n<100) */)
    {
      ////std::cout << n++ << " before backwardExpr, bot=" << bot.getPosition() << ", top=" << top.getPosition() << "\n";

      scan=syntax->backwardExpr(document, bot, top);

      //      std::cout << "after backwardExpr, scan=" << scan << ", bot="
      //            << bot.getPosition() << ", top=" << top.getPosition() 
      //            << ", expr='" << document.getTextBetween(bot, top).toUTF8() << "'"
      //            << "\n";
      
      // break on error or nothing new to add
      if (scan<=0) 
        {
          //std::cout << "breaking scan<0\n";
          break;
        }
      // break if past lower bounds
      if (bot.getPosition()<end)
        {
          //std::cout << "breaking pos<end\n";
          break;
        }
      // push current expr bounds onto array
      epos.insert(0, top.getPosition());
      epos.insert(0, bot.getPosition());
      // break if we are evalling just one backward expr
      if (regn==0) 
        {
          //std::cout << "breaking (regn=false)\n";
          break; 
        }
      // break if we added last possible expr
      if (bot.getPosition()==end)
        {
          //std::cout << "breaking pos=end\n";
          break;
        }
      // move top to bot (ie 1 above next start)
      top=CodeDocument::Position(bot);
    }

  //std::cout << "after loop, epos.size()=" << epos.size() << "\n";
  if (scan<0)
    {
      String text;
      if (scan==ScanIDs::SCAN_UNLEVEL)
        {
          text=T(">> Error: unbalanced delimiter, line ");
          text << bot.getLineNumber() << T(":\n") 
               << bot.getLineText() << T("\n");
        }
      else if (scan=ScanIDs::SCAN_UNMATCHED)
        {
          text=T(">>> Error: unmatched delimiter, line ");
          // line is most recent upper bounds
          text << top.getLineNumber() << T(":\n") 
               << top.getLineText() << T("\n");
        }
      //      PlatformUtilities::beep();
      Console::getInstance()->printError(text, true);
    }
  else if (epos.size()>0) // got expr(s)
    {
      bot.setPosition(epos.getFirst());
      top.setPosition(epos.getLast());
      syntax->eval(document, bot, top, expandonly, regn);
    }
  else
    {
      //std::cout << "empty!\n";
    }
}

void CodeBuffer::indent()
{
  CodeDocument::Position bol=getBOL();
  CodeDocument::Position pos (getCaretPos());
  String all=pos.getLineText();
  int col=syntax->getIndentation(document, getCaretPos().getLineNumber());
  if (col<0)
    {
      insertTabAtCaret();
      isChanged(true);
      return;
    }

  int old=0;
  while (old<all.length() && (all[old]==T(' ') || all[old]==T('\t')))
    old++;
  //std::cout << "old=" << old << ", col=" << col << ", len=" << all.length() << "\n";
  //if (col==old) return;
  moveCaretTo(bol,false);
  if (old>col)
    {
      //std::cout <<"cursor at col="<<getCaretPos().getIndexInLine()<<"\n";
      //std::cout << "removing " << (old-col)<<"\n";
      for (int i=0; i<(old-col); i++)
        cursorRight(false,true);
      deleteForward(false);
      isChanged(true);
    }
  else if (old<col)
    {
      String pad (String::empty);  
      for (int i=0; i<(col-old); i++)
        pad<<String(" ");
      //std::cout << "adding " << (col-old)<< "pad=='" << pad.toUTF8() << "'\n";
      insertTextAtCaret(pad);
      isChanged(true);
    }
  while (bol!=getEOL() && (bol.getCharacter()==T(' ') || bol.getCharacter()==T('\t')))
    bol.moveBy(1);
  moveCaretTo(bol, false);
}

