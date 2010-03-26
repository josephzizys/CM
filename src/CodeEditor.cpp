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
#include <iostream>
#include <limits>

/*=======================================================================*
                               CodeEditorWindow
 *=======================================================================*/

CodeEditorWindow::CodeEditorWindow (File file, String text, int synt, String title)
  : DocumentWindow(String::empty, Colours::white, DocumentWindow::allButtons, true)
{
  setMenuBar(this);
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
        synt=Preferences::getInstance()->getIntProp(T("EditorSyntax"), TextIDs::Lisp);
      file=File::nonexistent;
    }
  sourcefile=file;
  document.setNewLineCharacters(T("\n"));
  document.replaceAllContent(String(text));
  document.setSavePoint();
  document.clearUndoHistory();
  // parse optional first-line buffer customizations comment.  if no
  // comment then customs will be null
  XmlElement* customs=getCustomizations();
  // since the buffer syntax is fixed per buffer the window has to
  // handle this customization
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

  //std::cout << "syntax synt=" << syntax->getType() << "\n";

  // create the code buffer and add it to a content component. the
  // buffer is not the content component so the window can contain
  // other components besides the editor, eg a mode line, toolbar etc.
  CodeBuffer* buffer=new CodeBuffer(document, syntax, &commands, customs);
  EditorComponent* edcomp=new EditorComponent();
  setContentComponent(edcomp);
  // now set window and content component's size to buffer's optimum
  // size before adding the buffer (so buffer doesnt get resized)
  centreWithSize(jmin(800, buffer->getWidth()), 
                 jmin(800, buffer->getHeight()));
  edcomp->setCodeBuffer(buffer);

  // add (current) customizations to new empty buffers (???)
  if (text.isEmpty())
    writeCustomComment(false);
  commands.registerAllCommandsForTarget(this);
  //setApplicationCommandManagerToWatch(&commands);
  commands.setFirstCommandTarget(this);
  updateKeyPressesForEditMode();
  setWantsKeyboardFocus(false); // buffer wants focus
  setWindowTitle(title);
  setResizable(true, true); 
  setUsingNativeTitleBar(true);
  setDropShadowEnabled(true);
  if (customs) delete customs;
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

CodeBuffer* CodeEditorWindow::getCodeBuffer()
{
  return ((EditorComponent*)getContentComponent())->getCodeBuffer();
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
      //      CommandIDs::EditorTabWidth + 2,
      //      CommandIDs::EditorTabWidth + 4,
      //      CommandIDs::EditorTabWidth + 6,
      //      CommandIDs::EditorTabWidth + 8,
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
      CommandIDs::SchedulerPause
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
    case CommandIDs::EditorCut:
      info.shortName=T("Cut");
      if (commandkeyactive)
	info.addDefaultKeypress(T('X'), ModifierKeys::commandModifier);
      info.setActive(getCodeBuffer()->getHighlightedRegionLength()>0);
      break;
    case CommandIDs::EditorCopy:
      info.shortName=T("Copy");
      if (commandkeyactive)
	info.addDefaultKeypress(T('C'), ModifierKeys::commandModifier);
      info.setActive(getCodeBuffer()->getHighlightedRegionLength()>0);
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
      info.setActive(getCodeBuffer()->getHighlightedRegionLength()>0);
      break;
    case CommandIDs::EditorUncommentOut:
      info.shortName=T("Uncomment Region");
      info.setActive(getCodeBuffer()->getHighlightedRegionLength()>0);
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
    case CommandIDs::EditorTheme:
      info.shortName=T("Editor Theme") + String(data);
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
      info.shortName=T("Make Default Theme");
      break;
    case CommandIDs::EditorSaveCustom:
      info.shortName=T("Update Customizations");
      break;
    case CommandIDs::EditorReadCustom:
      {
        info.shortName=T("Apply Customizations");
        info.setActive(isCustomComment());
      }
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
    case CommandIDs::EditorCut:
      getCodeBuffer()->cut();
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
      // OPTIONS MENU
    case CommandIDs::EditorSyntax:
      switchBufferSyntax(data);
      break;
    case CommandIDs::EditorFontSize:
      getCodeBuffer()->setFontSize(data);
      resizeForColumnsAndLines();
      break;
    case CommandIDs::EditorTheme:
      std::cout << "EditorTheme\n";
      break;
    case CommandIDs::EditorDefaultSyntax:
      Preferences::getInstance()->setIntProp(T("EditorSyntax"), getCodeBuffer()->getTextType());
      break;
    case CommandIDs::EditorDefaultFontSize:
      Preferences::getInstance()->setIntProp(T("EditorFontSize"), getCodeBuffer()->getFontSize());
      break;
    case CommandIDs::EditorDefaultTheme:
      std::cout << "EditorDefaultTheme\n";
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
      for (int i=0; i<8; i++)
        sub2.addCommandItem(&commands, CommandIDs::EditorTheme+i);
      sub2.addSeparator();
      sub2.addCommandItem(&commands, CommandIDs::EditorDefaultTheme);
      menu.addSubMenu(T("Theme"), sub2);
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
      menu=CommandMenus::getHelpMenu(WindowTypes::TextEditor, gmanager);
    }
  return menu;
}

void CodeEditorWindow::menuItemSelected (int id, int index)
{
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
      std::cout << "installing keypresses for emacs\n";
      keymap->addKeyPress(CommandIDs::EditorClose, KeyPress(T('W'), ModifierKeys::commandModifier, 0));
      keymap->addKeyPress(CommandIDs::AppQuit, KeyPress(T('Q'), ModifierKeys::commandModifier, 0));
      keymap->addKeyPress(CommandIDs::EditorExecute, KeyPress::createFromDescription(T("ctrl + return")));
      keymap->addKeyPress(CommandIDs::EditorExpand, KeyPress::createFromDescription(T("ctrl + shift + return")));
    }
  else
    {
      std::cout << "installing standard keypresses\n";
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
  return NULL;
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
          if (tokens[i+1].isQuotedString())
            xml->setAttribute(T("theme:"), tokens[i+1].unquoted());
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
        ;
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
  custom << " theme: \"Basic\"" ; //<< getTheme.get
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

/*=======================================================================*
                                   CodeBuffer
 *=======================================================================*/

CodeBuffer::CodeBuffer(CodeDocument& doc, Syntax* tokenizer, ApplicationCommandManager* commands, XmlElement* customs)
  : 
  document (doc),
  fontsize (16),
  tabwidth (2),
  columns (72),
  lines (30),
  parensmatching(true),
  changed (false),
  CodeEditorComponent(doc, tokenizer)
{
  syntax=tokenizer;
  manager=commands;
  fontsize=Preferences::getInstance()->getIntProp(T("EditorFontSize"), 16);
  emacsmode=Preferences::getInstance()->getBoolProp(T("EditorEmacsMode"), SysInfo::isMac());
  String themename=Preferences::getInstance()->getStringProp(T("EditorTheme"), T("vanilla"));
  if (customs) // file has customizations
    {
      fontsize=customs->getDoubleAttribute(T("font-size:"), fontsize);
      columns=customs->getIntAttribute(T("columns:"), columns);
      lines=customs->getIntAttribute(T("lines:"), lines);
      themename=customs->getStringAttribute(T("theme:"), themename);
    }
  Font mono (Font::getDefaultMonospacedFontName(), (float)fontsize, Font::plain);
  setFont(mono);
  setTabSize(tabwidth, true);
  // 16 is for the scollbars, not sure why i need the extra 4....
  setSize((getCharWidth() * columns)+16+4, (getLineHeight() * lines)+16+4);
  setWantsKeyboardFocus(true);
  setVisible(true);
}

CodeBuffer::~CodeBuffer()
{
}

bool CodeBuffer::keyPressed (const KeyPress& key)
{
  const int ctrl = ModifierKeys::ctrlModifier;
  const int meta = ModifierKeys::altModifier;
  const int both = (ModifierKeys::ctrlModifier | ModifierKeys::altModifier);
  const bool emacs=isEmacsMode();

  //std::cout << "CodeBuffer::keyPressed key=" << key.getTextDescription().toUTF8() << "\n";

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
  else if (emacs && key == KeyPress(T('k'), ctrl, 0))
    killLine();
  else if (emacs && key == KeyPress(T('n'), ctrl, 0))
    moveLineForward();
  else if (emacs && key == KeyPress(T('o'), ctrl, 0))
    openLine();
  else if (emacs && key == KeyPress(T('p'), ctrl, 0))
    moveLineBackward();
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
  // TESTING commands  
  else if (emacs && key == KeyPress(T('='), ModifierKeys::ctrlModifier, 0))
    posInfo(getCaretPos());
  else if (emacs && key == KeyPress(T('-'), ModifierKeys::ctrlModifier, 0))
    test(false);
  else if (emacs && key == KeyPress(T('+'), ModifierKeys::ctrlModifier | ModifierKeys::shiftModifier, 0))
    test(true); 
  else 
    {
      // else try other keypress handlers in this order: (1) Juce
      // CodeEditorComponent (2) the CodeEditorWindow and (3) the
      // global command manager
      prevkey=KeyPress(key);
      if (CodeEditorComponent::keyPressed(key)) // search component's keypress
        {
          //std::cout << "returning true from CodeEditorComponent";
          isChanged(true); // if handled give up and 
          //(KeyPress::leftKey)(KeyPress::rightKey) (KeyPress::upKey) (KeyPress::downKey) (KeyPress::pageDownKey) (KeyPress::pageUpKey) (KeyPress::homeKey) (KeyPress::endKey)
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
  return syntax->getType();
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

bool CodeBuffer::isParensMatching()
{
  return parensmatching;
}

void CodeBuffer::isParensMatching(bool match)
{
  parensmatching=match;
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

bool CodeBuffer::lookingAt(const CodeDocument::Position pos, const String text, const bool forward, const bool delimited)
{
  // return true if buffer contents matches text starting at pos,
  // which must be ON the first char to check. if delimited is true
  // then the text must match as a delimited word.
  CodeDocument::Position at (pos);
  int len=text.length();
  if (forward)
    {
      CodeDocument::Position end=getEOB();
      int i=0;
      for ( ; i<len && at!=end; i++)
        {
          //String str=T("comparing ");
          //str << at.getCharacter() << T("&") << text[i] << T("\n");
          //std::cout << str.toUTF8();
        if (at.getCharacter() != text[i])
          return false;
        else
          at.moveBy(1);
        }
      //std::cout << "done, i==len: " << (i==len) << " at==end: "  << (at==end) << "\n";
      if (i==len)
        return (delimited) ? ((at==end) || !char_token_p(syntax->syntab, at.getCharacter())) : true;
      return false;

    }
  else
    {
      CodeDocument::Position end=getBOB();
      bool b=false;
      int i=len-1;
      for ( ; i>=0; i--)
        if (at.getCharacter() != text[i])
          return false;
        // at this point we've matched at position i
        else if (at==end)
          {
            i--;    // still increment i
            b=true; // note we matched at bob
            break;
          }
        else at.moveBy(-1);

      if (i<0 )
        return (delimited) ? (b || !char_token_p(syntax->syntab, at.getCharacter())) : true;
      return false;
    }
}

/*=======================================================================*
                         Emacs Cursor Motion Functions
 *=======================================================================*/

CodeDocument::Position CodeBuffer::gotoBOB()
{
  goToStartOfDocument(false);
  return getCaretPos();
}

CodeDocument::Position CodeBuffer::gotoEOB()
{
  goToEndOfDocument(false);
  return getCaretPos();
}

CodeDocument::Position CodeBuffer::gotoBOL()
{
  //goToStartOfLine(false); // this stops at whitespace
  CodeDocument::Position here=getCaretPos();
  CodeDocument::Position there (&document, here.getLineNumber(), 0);
  moveCaretTo(there, false);
  return getCaretPos();
}

CodeDocument::Position CodeBuffer::gotoEOL()
{
  goToEndOfLine(false);
  return getCaretPos();
}

void CodeBuffer::moveCharForward()
{
  cursorRight(false,false);
}

void CodeBuffer::moveCharBackward()
{
  cursorLeft(false,false);
}

void CodeBuffer::moveWordForward()
{
  cursorRight(true,false);
}

void CodeBuffer::moveWordBackward()
{
  cursorLeft(true,false);
}

void CodeBuffer::moveLineForward()
{
  cursorDown(false);
}

void CodeBuffer::moveLineBackward()
{
  cursorUp(false);
}

void CodeBuffer::movePageForward()
{
  pageDown(false);
}

void CodeBuffer::movePageBackward()
{
  pageUp(false);
}

void CodeBuffer::moveExprForward()
{
  CodeDocument::Position pos (getCaretPos());
  int scan=scanCode(pos, true, ScanFlags::MoveExpressions);
  if (scan<0)
    PlatformUtilities::beep();
  else
    moveCaretTo(pos, false);
}

void CodeBuffer::moveExprBackward()
{
  CodeDocument::Position pos (getCaretPos());
  // if moving backwards the cursor is one char beyond start of scan
  pos.moveBy(-1);
  int scan=scanCode(pos, false, ScanFlags::MoveExpressions);
  if (scan<0)
    PlatformUtilities::beep();
  else
    moveCaretTo(pos, false);
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
  deleteForward(true);
  isChanged(true);
}

void CodeBuffer::killWordBackward()
{
  backspace(true);
  isChanged(true);
}

void CodeBuffer::killExprForward()
{
  std::cout << "killExprForward\n";
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
  CodeDocument::Position bol (getBOL());
  CodeDocument::Position eol (getEOL(bol)); 
  //  while (bol!=eol && (bol.getCharacter()==T(' ') || bol.getCharacter()==T('\t'))) 
  //    bol.moveBy(1);
  if (forward)
    if (lookingAt(getCaretPos(), T("end"), true, true) )
      std::cout << "forward looking at end\n";
    else
      std::cout << "NOT looking at end (forward)\n";
  else
    if (lookingAt(getCaretPos().movedBy(-1), T("end"), false, true) )
      std::cout << "backward looking at end\n";
    else
      std::cout << "NOT looking at end (backward)\n";
}

/*=======================================================================*
                    Evaluation and Syntactic Backward Expression
 *=======================================================================*/

void CodeBuffer::eval(bool expandonly)
{
  int type=getTextType();
  int regn=getHighlightedRegionLength();
  int scan=SCAN_EMPTY;
  Array<int> epos; // positions of backward exprs
  CodeDocument::Position bot (getCaretPos());
  CodeDocument::Position top (getCaretPos());
  int end=0;  // lowest position possible

  if (regn>0) // if region use its bounds
    {
      bot=getHighlightedRegionStart();
      top=bot.movedBy(regn);
      end=bot.getPosition();
    }
  // process region backwards recording the starting and ending
  // positions of expressions
  //// int n=0;
  while (true /*&& (n<100) */)
    {
      ////std::cout << n++ << " before backwardExpr, bot=" << bot.getPosition() << ", top=" << top.getPosition() << "\n";

      if (type==TextIDs::Lisp)
        scan=backwardLispExpr(bot, top);
      else if (type==TextIDs::Sal)
        scan=backwardSal1Expr(bot, top);
      else if (type==TextIDs::Sal2)
        scan=backwardSal2Expr(bot, top);
      ////std::cout << "after backwardExpr, scan=" << scan << ", bot="
      ////      << bot.getPosition() << ", top=" << top.getPosition() 
      ////      << "expr='" << document.getTextBetween(bot, top).toUTF8() << "'"
      ////      << "\n";
      
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
      if (scan==SCAN_UNLEVEL)
        {
          text=T(">> Error: unbalanced delimiter, line ");
          text << bot.getLineNumber() << T(":\n") 
               << bot.getLineText() << T("\n");
        }
      else if (scan=SCAN_UNMATCHED)
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
      if (type==TextIDs::Lisp)
        evalLisp(bot,top,expandonly,regn);
      else if (type==TextIDs::Sal2 || type==TextIDs::Sal)
        evalSal(bot,top,expandonly,regn);
    }
  else
    {
      //std::cout << "empty!\n";
    }
}

void CodeBuffer::evalLisp(const CodeDocument::Position start, const CodeDocument::Position end, bool expand, bool region)
{
  String code=document.getTextBetween(start, end);
  //std::cout << "eval='" << code.toUTF8() << "'\n";
  if (expand)
    code=T("(macroexpand ") + code + T(")");
  if (region)
    code=T("(begin ") + code + T(")");
  SchemeThread::getInstance()->eval(code);
}

void CodeBuffer::evalSal(const CodeDocument::Position start, const CodeDocument::Position end, bool expand, bool region)
{
  // forward scan sal tokens and call sal on result. if region is true
  // then surround the add 'begin' and 'end' to the string and token
  // array adjust string positions accordingly
 
  String code=document.getTextBetween(start, end);
  std::cout << "expr='" << code.toUTF8() << "', start=" << start.getPosition() 
            << ", end=" << end.getPosition() << "\n";
  OwnedArray<SynTok> tokens;
  CodeDocument::Position pos (start);
  int beg=pos.getPosition();  // offset of string
  int ins=(region) ? 6 : 0;   // inset length of "begin "
  int lev=0, par=0, cur=0, squ=0;
  int scan=scanCode(pos,true,ScanFlags::MoveWhiteAndComments, end.getPosition());
  while (pos!=end)
    {
      CodeDocument::Position far(pos);
      scan=scanCode(far, true, ScanFlags::MoveTokens, end.getPosition());
      if (scan<=0) break;
      int loc=pos.getPosition()-beg + ins;
      if (scan==SCAN_OPEN)
        {
          tchar c=pos.getCharacter();
          if (c==T('('))
            {
              par++;
              tokens.add(new SynTok(T("("), SalSyntax::SalLParen, loc));
            }
          else if (c==T('{'))
            {
              cur++;
              tokens.add(new SynTok(T("{"), SalSyntax::SalLCurly, loc));
            }
          else if (c==T('['))
            {
              squ++;
              tokens.add(new SynTok(T("["), SalSyntax::SalLBrace, loc));
            }
        }
      else if (scan==SCAN_CLOSE)
        {
          tchar c=pos.getCharacter();
          if (c==T(')'))
            {
              if (--par < 0) break;
              tokens.add(new SynTok(T(")"), SalSyntax::SalRParen, loc));
            }
          else if (c==T('}'))
            {
              if (--cur < 0) break;
              tokens.add(new SynTok(T("}"), SalSyntax::SalRCurly, loc));
            }
          else if (c==T(']'))
            {
              if (--squ < 0) break;
              tokens.add(new SynTok(T("]"), SalSyntax::SalRBrace, loc));
            }
        }
      else if (scan==SCAN_PUNCT)
        tokens.add(new SynTok(T(","), SalSyntax::SalComma, loc));
      else if (scan==SCAN_STRING)
        {
          tokens.add(new SynTok(document.getTextBetween(pos,far).unquoted(), SalSyntax::SalString, loc));
        }
      else if (scan==SCAN_TOKEN)
        {
          String s=document.getTextBetween(pos,far);
          if (SynTok* t=syntax->getSynTok(s))
            {
              int x=t->getType();
              tokens.add(new SynTok(s, x, loc));
              if (SalSyntax::isSalBlockOpen(x))
                lev++;
              else if (SalSyntax::isSalBlockClose(x))
                {
                  if (--lev < 0) break;
                }
            }
          else if (int t=isNumberToken(s))
            {
              int typs[] = {SalSyntax::SalInteger, SalSyntax::SalFloat, SalSyntax::SalRatio};
              tokens.add(new SynTok(s, typs[t-1], loc));
            }
          else // is still a valid token!
            {
              if (s.getLastCharacter()==T(':'))
                tokens.add(new SynTok(s.dropLastCharacters(1), SalSyntax::SalKeyparam, loc));
              else if (s[0]==T(':'))
                tokens.add(new SynTok(s.substring(1), SalSyntax::SalKeyword, loc));
              else
                tokens.add(new SynTok(s, SalSyntax::SalIdentifier, loc));
            }
        }
      pos=far;
      scan=scanCode(pos,true,ScanFlags::MoveWhiteAndComments, end.getPosition());
    }

  //  std::cout << "tokens=";
  //  for (int i=0; i<tokens.size(); i++)
  //    std::cout << " " << tokens[i]->toString().toUTF8();
  //  std::cout << "\n";

  String text;
  if (scan<0)
    {
      text << T(">>> Error: illegal token, line: ")
           << pos.getLineNumber() << T("\n")
           << pos.getLineText() << T("\n");
      Console::getInstance()->printError(text);
    }
  else if (lev!=0 || par!=0 || cur!=0 || squ!=0)
    {
      SynTok* tok=NULL;
      if (lev<0) // too many ends
        text << T(">>> Error: extraneous 'end', line: ");
      else if (par<0)
        text << T(">>> Error: extraneous ')', line: ");
      else if (cur<0)
        text << T(">>> Error: extraneous '}', line: ");
      else if (squ<0)
        text << T(">>> Error: extraneous ']', line: ");
      else if (lev>0)
        {
          text << T(">>> Error: missing 'end'");
          for (int i=tokens.size()-1, n=0; i>-1; i--)
            {
              int x=SalSyntax::SalTypeDataBits(tokens[i]->getType());
              if (x==SalSyntax::SalBlockOpen)
                if (n==lev) {tok=tokens[i]; break;} else n--;
              else if (x==SalSyntax::SalBlockClose) n++;
            }
          if (tok) text << " for " << tok->getName();
          text << T(", line: ");
        }
      else if (par>0)
        {
          text << T(">>> Error: missing ')', line: ");
          for (int i=tokens.size()-1, n=0; i>-1; i--)
            if (tokens[i]->getType()==SalSyntax::SalLParen) 
              if (n==par) {tok=tokens[i]; break;} else n--;
            else if (tokens[i]->getType()==SalSyntax::SalRParen) n++;
        }
      else if (cur>0)
        {
          text << T(">>> Error: missing '}', line: ");
          for (int i=tokens.size()-1, n=0; i>-1; i--)
            if (tokens[i]->getType()==SalSyntax::SalLCurly) 
              if (n==cur) {tok=tokens[i]; break;} else n--;
            else if (tokens[i]->getType()==SalSyntax::SalRCurly) n++;
        }
      else if (squ>0)
        {
          text << T(">>> Error: missing ']', line: ");
          for (int i=tokens.size()-1, n=0; i>-1; i--)
            if (tokens[i]->getType()==SalSyntax::SalLBrace) 
              if (n==cur) {tok=tokens[i]; break;} else n--;
            else if (tokens[i]->getType()==SalSyntax::SalRBrace) n++;
       }
      if (tok) pos.setPosition(beg+tok->getData1()-ins);
      text << pos.getLineNumber() << T("\n")
           << pos.getLineText() << T("\n");
      Console::getInstance()->printError(text);
    }
  else
    {
      if (region)
        {
          // if we are evalling a region we need to add begin and end
          // tokens to the token array and also add their names to the
          // text string so that token positions are corrent when
          // reporting errors
          text << T("begin ") << document.getTextBetween(start, end) << T(" end");
          tokens.insert(0, new SynTok(T("begin"), SalSyntax::SalBegin, 0));
          tokens.add(new SynTok(T("end"), SalSyntax::SalEnd, 
                                end.getPosition()-start.getPosition()+ins));
        }
      else
        text=document.getTextBetween(start, end);
      XSalNode* node=new XSalNode(0.0, text, getTextType(), expand);
      // swapping moves tokens from the local array to the evalnode's
      // array AND clears the local array in a single
      // operation. swapping must be done or the tokens will be
      // deleted when the local array goes out of scope!
      node->toks.swapWithArray(tokens);
      //std::cout << "tokens=";
      //for (int i=0; i<node->toks.size(); i++)
      //  std::cout << " " << node->toks[i]->toString().toUTF8();
      //std::cout << "\n";
      SchemeThread::getInstance()->addNode(node);
    }
}

int CodeBuffer::isNumberToken(const String str) 
{
  // returns 0==nan, 1==int, 2==float, 3==ratio
  int len=str.length();
  int typ=0, dot=0, div=0, dig=0;
  for (int pos=0; pos<len; pos++) 
    switch ( str[pos] )
      {
      case T('-') :
      case T('+') :
        if (pos>0) return 0; // not in leading position
        break;
      case T('.') :
        if (dot>0) return 0; // too many dots
        if (div>0) return 0; // in ratio
        dot++;
        break;
      case T('/') :
        if (div>0) return 0; // too many divs
        if (dig==0) return 0; // no digit yet
        if (dot>0) return 0;  // float already
        if (pos==len-1) return 0; // at end
        div++;
        break;
      case T('0') :
      case T('1') :
      case T('2') :
      case T('3') :
      case T('4') :
      case T('5') :
      case T('6') :
      case T('7') :
      case T('8') :
      case T('9') :
        dig++;
        break;
      default:
        return 0;
      }
  if (div) return 3;
  if (dot) return 2; 
  return 1;
}

/*=======================================================================*
                            Backward Expression Gathering
 *=======================================================================*/

int CodeBuffer::backwardLispExpr(CodeDocument::Position& from, CodeDocument::Position& to)
{
  ////  CodeDocument::Position pos (getCaretPos());
  CodeDocument::Position pos (to);
  // moving backwards the cursor is always one char past scan start
  pos.moveBy(-1);
  // skip trailing comments and whitespace
  scanCode(pos, false, ScanFlags::MoveWhiteAndComments);
  // pos is now ON ending char of expr (or at eob if only white) so
  // set end to one beyond ending char of expr
  CodeDocument::Position end (pos.movedBy(1));
  // scan backwords to start of expr
  int scan=scanCode(pos, false, ScanFlags::MoveExpressions);
  from.setPosition(pos.getPosition());
  to.setPosition(end.getPosition());
  return scan;
}

int CodeBuffer::backwardSal2Expr(CodeDocument::Position& from, CodeDocument::Position& to)
{
  //CodeDocument::Position pos (getCaretPos());
  CodeDocument::Position pos (to);
  CodeDocument::Position bob=getBOB();
  int scan=0, last=0, here=-1, level=0;
  #define SCAN_CURLY (SCAN_PUNCT+1)
  #define SCAN_SQUARE (SCAN_PUNCT+2)

  // cursor always 1 past start of backward scan
  pos.moveBy(-1);
  // move backward over white and comments
  scanCode(pos, false, ScanFlags::MoveWhiteAndComments);
  // pos now on last constituent char for backward scan (or at
  // bob). set scan's exclusive upper bound to 1 above pos
  CodeDocument::Position top (pos.movedBy(1));

  if (lookingAt(pos, T("end"), false, true)) // at block end
    while (true)
      {
        // now on last constituent char for scan (or at bob). set the
        // exclusive upper bound of expr to 1 above that
        CodeDocument::Position end (pos.movedBy(1)); 
        scan=scanCode(pos, false, ScanFlags::MoveExpressions);
        // quit if error or only white space
        if (scan<=0)
          break;
        String code=document.getTextBetween(pos, end);
        //std::cout << "Code ("<<from.getPosition()<<","<<to.getPosition()<<"): '" << code.toUTF8() << "'\n";
        if (scan==SCAN_TOKEN)
          {
            if (SynTok* tok=syntax->getSynTok(code))
              {
                // token is a literal (e.g. statement, op)
                int typ=tok->getType();
                if (SalSyntax::isSalBlockClose(typ))
                  level++; 
                else if (SalSyntax::isSalBlockOpen(typ))
                  level--; 
                // stop on a blockopen word with no pending end. this
                // doesn't mean the statement is actually balanced
                // since the word could be reached without seeing a
                // balancing end (in which case level is negative)
                if (level<=0)
                  {
                    here=pos.getPosition();
                    break;
                  }
              }
          }
        if (pos==bob) break;
        pos.moveBy(-1);
        scanCode(pos, false, ScanFlags::MoveWhiteAndComments);
      }
  else   
    // else parse expr back, possibly to a command (set or variable)
    // but stopping before any clausal
    while (true)
      {
        // pos is on last consitute char of backwards expr (or at bol)
        // set exclusive end of current expr and scan backwards
        CodeDocument::Position end (pos.movedBy(1)); 
        scan=scanCode(pos, false, ScanFlags::MoveExpressions);
        // quit if scan error or only white space
        if (scan<=0)
          {
            //std::cout << "breaking with scan <= 0: " << scan << "\n";;
            break;
          }
        String code=document.getTextBetween(pos,end);
        //std::cout << "Code ("<<pos.getPosition()<<","<<end.getPosition()<<"): '" << code.toUTF8() << "'\n";
        if (scan==SCAN_TOKEN)
          {
            SynTok* tok=syntax->getSynTok(code);
            if (tok && !SalIDs::isSalBoolType(tok->getType()))  // booleans are values...
              {
                // token is a literal. stop if its the first thing
                // encountered or if its a clausal
                if (last==0 || SalSyntax::isSalClausalType(tok->getType()))
                  {
                    //std::cout<<"literal breaking with last==0"<<code.toUTF8()<<"\n";
                    break;
                  }
                scan=tok->getType();
                // if its a command then include and stop
                if (SalSyntax::isSalCommandType(scan))
                  {
                    //std::cout << "stopping on command '"<<code.toUTF8()<<"'\n";
                    here=pos.getPosition();
                    break;
                  }
                // otherwise (its a op or comma? ) keep going...
                here=pos.getPosition();
              }
            else 
              {
                // token is a variable or constant.  if its the first
                // expr or if the last was a literal then include it
                // and keep going
                if ((last==0) || SalSyntax::isSalType(last))
                  here=pos.getPosition();
                // otherwise if its a constant then stop (because last
                // is an expr)
                else if (code.containsOnly(T("0123456789+-./")) ||
                         code.startsWith(T("#")) ||
                         code.startsWith(T(":")) ||
                         code.endsWith(T(":")) )
                  {
                    //std::cout<<"breaking with constant="<<code.toUTF8()<<"\n";
                    break;
                  }
                // otherwise its a variable, if last was a () expr its
                // a function call, if last was a [] its a aref
                // otherwise stop
                else if (last==SCAN_LIST || last==SCAN_SQUARE)
                  here=pos.getPosition();
                else
                  {
                    //std::cout << "token breaking with code='"<<code.toUTF8()<<"'\n";
                    break;
                  }
              }
          }
        else if (scan==SCAN_PUNCT)
          {
            // its a comma, stop if last not an expression
            if (last==0 || SalSyntax::isSalType(last))
              {
                //std::cout << "breaking on SCAN_PUNCT=\n";
                break;
              }
            scan=SalSyntax::SalComma;
          }
        // otherwise its a {[( or string expression. stop unless this
        // expr its the first or the previous thing was not an expr
        else if (last==0 || SalSyntax::isSalType(last))
          {
            if (pos.getCharacter()==T('{'))
              scan=SCAN_CURLY;
            else if (pos.getCharacter()==T('['))
              scan=SCAN_SQUARE;
            here=pos.getPosition();
          }
        else
          {
            //std::cout << "breaking with scan=" << ScanFlags::scanResultToString(scan).toUTF8() << "\n";
            break;
          }
        if (pos==bob) break;
        // move one below first expr char, skip comments and white
        last=scan;
        pos.moveBy(-1);
        scanCode(pos, false, ScanFlags::MoveWhiteAndComments);
      }
  //std::cout << "_______________\n";

  if (scan<0) 
    {
      //std::cout << "returning: " << scan << "\n";
      return scan;
    }
  //std::cout << "after loop, here=" << here << "scan=" << scan << "\n";
  from.setPosition(here);
  //std::cout << "setting from position="<< here << "\n";
  to.setPosition(top.getPosition());
  //std::cout << "setting to position=" << top.getPosition() << "\n";
  
  // stopped without lower bound means no expr encountered
  if (here<0) 
    {
      scan=SCAN_EMPTY;
      here=pos.getPosition();
    }
  //std::cout << "returning: "  << ((here>-1) ? 1 : scan) << "\n";
  return (here>-1) ? 1 : scan;
}

int CodeBuffer::backwardSal1Expr(CodeDocument::Position& from, CodeDocument::Position& to)
{
  // in sal1 backward expression finds the nearest command literal
  // that start in 0th column position of a line
  // moving backwards the cursor is always one char past scan start
  to.moveBy(-1);
  // skip trailing comments and whitespace
  scanCode(to, false, ScanFlags::MoveWhiteAndComments);
  // to is now ON ending char of expr (or at eob if only white) so set
  // end to one beyond ending char of expr
  to.moveBy(1);
  int line=to.getLineNumber();
  while (line>=0)
    {
      from.setLineAndIndex(line, 0);
      CodeDocument::Position t (from);
      if (scanToken(t, 1, getEOL(from)))
        {
          if (SynTok* tok=syntax->getSynTok(document.getTextBetween(from, t)))
            {
              if (SalSyntax::isSalCommandType(tok->getType()))
                {
                  //std::cout << "command=" << tok->getName().toUTF8() << "\n";
                  return 1;
                }
            }
        }
      line-=1;
    }
  return 0;
}

/*=======================================================================*
                                Syntactic Indentation
 *=======================================================================*/

void CodeBuffer::indent()
{
  CodeDocument::Position bol=getBOL();
  CodeDocument::Position pos (getCaretPos());
  String all=pos.getLineText();
  int col=0;

  if (isTextType(TextIDs::Sal2) || isTextType(TextIDs::Sal))
    col=indentSal2();
  else if (isTextType(TextIDs::Lisp))
    col=indentLisp();

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

int CodeBuffer::indentLisp()
{
  CodeDocument::Position pos (getCaretPos());
  Array<int> subtypes;
  Array<int> substarts;
  int line=pos.getLineNumber();
  int scan=0;

  // if no lines above point indent 0 else move cursor to end of
  // previous line and scan backward until either unlevel OR a
  // balanced expression in column 0. record types and starting
  // positions of subexpressions traversed

  if (line==0) return 0;
  pos.setLineAndIndex(line-1, INT_MAX); // goto eol of previous line
  while (true)
    {
      scan=scanCode(pos, false, ScanFlags::MoveExpressions);
      if (scan>0)
        if (pos.getIndexInLine()==0)
          {
            break;
          }
        else
          {
            // prepend since moving backward
            subtypes.insert(0, scan);
            substarts.insert(0, pos.getPosition());
            // arrrgh! the 1st position problem
            pos.moveBy(-1); 
          }
      else
        {
          break;
        }
    }

  //std::cout << "after loop, scan="<<scan<< ", pos=" << pos.getPosition() << ", col=" << pos.getIndexInLine() << "\n";

  // stopped on a balanced expr in column 0 so indent to whatever
  // position the very LATEST subexpr is or use column 0
  if (scan!=SCAN_UNLEVEL)
    {
      if (substarts.size()==0)
        {
          ////          std::cout << "balanced indent: 0\n";
          return 0;
        }
      CodeDocument::Position sub (&document, substarts.getLast());
      ////std::cout << "balanced indent: " << sub.getIndexInLine() << "\n";
      return sub.getIndexInLine();
    }
  // otherwise we've stopped on an unbalanced open parens.

  //  std::cout << "unlevel: (" << pos.getPosition() << ") -> '" 
  //            << document.getTextBetween(pos, pos.movedBy(1)).toUTF8() 
  //           << "'\nsubexprs:\n";
  //  for (int i=0; i<subtypes.size(); i++)
  //    std::cout << "  " << substarts[i] << ": " << ScanFlags::scanResultToString(subtypes[i]).toUTF8() << "\n";

  // if no subexprs indent 1 position beyond open parens
  if (subtypes.size()==0)
    {
      ////std::cout << "nothing forward, indent column=" << pos.getIndexInLine()+1 << "\n";
      return pos.getIndexInLine()+1;
    }

  // if first subexpr is NOT a token indent to its column position
  if (subtypes.getFirst()!=SCAN_TOKEN)
    {
      CodeDocument::Position sub (&document, substarts.getFirst());
      ////std::cout << "not a token, indent column=" << sub.getIndexInLine() << "\n";
      return sub.getIndexInLine();
    }

  // first expr after the open parens is a token, get its name and
  // check for special indentation rules
  CodeDocument::Position tokbeg (&document, substarts.getFirst());
  CodeDocument::Position tokend (&document, substarts.getFirst());
  scanToken(tokend,1,getEOL(tokbeg));
  String name=document.getTextBetween(tokbeg,tokend);
  int nargs=substarts.size()-1;    // num subexpr args after token

  //std::cout << "num exprs=" << subtypes.size() << ", numstarts=" << substarts.size() << "\n";

  if (SynTok* syntok=syntax->getSynTok(name)) // is special form
    {
      // car of list is a special form. get num distinguished args to
      // see if we do a body indent
      int body=syntok->getIndent(); // num distinguished args
 
      // if we have no args or exactly body args then do a body indent
      // otherwise indent to the column of the last subexpr.

      ////std::cout << "special form: '" << name.toUTF8() << "', nargs="<< nargs << ", body=" << body;

      //std::cout << "special nargs=" << nargs << "\n";

      if (nargs==0 || nargs==body)
        {
          ////std::cout << "body indent, indent column=" << pos.movedBy(2).getIndexInLine() << "\n";
          return pos.movedBy(2).getIndexInLine();
        }
      else
        {
          //**  CodeDocument::Position sub (&document, substarts.getLast());
          //**//std::cout << "indent to last expr, indent column=" << sub.getIndexInLine() << "\n";
          //** return sub.getIndexInLine();
          substarts.remove(0);  
          int x=lastIndented(substarts, false);
          //std::cout << "returning indent col=" << x << "\n";
          return x;
        }
    }
  else // token not special, indent to last expr or to pos+1 if none
    {
      //std::cout << "no special nargs=" << nargs << "\n";
      if (nargs==0)
        {
          ////std::cout << "normal token with no args, indent column=" << pos.movedBy(1).getIndexInLine() << "\n";
          return pos.movedBy(1).getIndexInLine();
        }
      else
        {
          //** CodeDocument::Position sub (&document, substarts.getLast());
          //**//std::cout << "normal token (args), indent column=" << sub.getIndexInLine() << "\n";
          //return sub.getIndexInLine();
          substarts.remove(0);
          int x=lastIndented(substarts, false);
          //std::cout << "returning indent col=" << x << "\n";
          return x;
        }
    }
}

int CodeBuffer::indentSal2()
{
  Array<int> subtypes;
  Array<int> substarts;
  SynTok* cmdtoken=0;
  CodeDocument::Position pos (getBOL());
  int line=pos.getLineNumber();
  int scan=0;
  int col=0;

  // if no lines above point indent 0
  if (line==0) return 0;
  // move to EOL of line above cursor
  line--;
  pos.setLineAndIndex(line, INT_MAX);

  // scan backwards until either unlevel OR a command or a balanced
  // expr in column 0. record types and starting positions of
  // subexpressions traversed
  while (true)
    {
      scan=scanCode(pos, false, ScanFlags::MoveExpressions);
      if (scan>0)
        {
          // prepend expr type since moving backward
          subtypes.insert(0, scan);
          substarts.insert(0, pos.getPosition());
          if (scan==SCAN_TOKEN)
            {
              CodeDocument::Position end (pos);
              scanToken(end, 1, getEOL(pos));
              String str=document.getTextBetween(pos,end);
              if (SynTok* tok=syntax->getSynTok(str))
                {
                  // update subtype with actual sal type. if type is a
                  // command, 'end' or 'else' then break
                  int type=tok->getType();
                  subtypes.set(0,type);
                  if (SalSyntax::isSalCommandType(type) )
                    {
                      cmdtoken=tok;
                      break;
                    }
                }
              else if (pos.getIndexInLine()==0)
                break;
            }
          else if (pos.getIndexInLine()==0)
            break;
          pos.moveBy(-1); 
        }
      else
        break;
    }

  if (scan<0) // scan stopped on unlevel parens
    {
      if (substarts.size()>0) // use last subexpr indentation
        {
          col=lastIndented(substarts, false);
          //std::cout << "UNLEVEL indent (last expr), column=" << col << "\n";
          return col;
        }
      else
        {
          col=pos.movedBy(1).getIndexInLine();
          //std::cout << "UNLEVEL indent (no exprs), column=" << col << "\n";
          return col;
        }
    }
  else if (subtypes.size()==0) // no expressions encountered (only white space)
    {
      //std::cout << "EMPTY indent, column=0\n" ;
      return 0;
    }  

  // at this point we have at least one subexpr and may have stopped
  // on a sal type

  if (!SalSyntax::isSalType(subtypes[0]))     // stopped on a non-sal expression
    {
      col=lastIndented(substarts, false);
      //std::cout << "SEXPR indent, column=" << col << "\n";
    }
  else // types[0] is sal entity, hopefully a command
    {
      if (cmdtoken)  // we stopped on a command
        {
          int cmdline=pos.getLineNumber(); // num of line with cmd
          // last is INDEX of last indented or command we stopped on
          int last=lastIndented(substarts, true);
          // IF the VERY last line ends with comma then indent 1 past
          // command name or a subexpr 'with' (if found)
          if (isCommaTerminatedLine(line))
            {
              for (last=subtypes[subtypes.size()-1]; last>=0; last--)
                if (subtypes[last]==SalSyntax::SalWith)
                  break;
              if (last<0) // reached command
                col=pos.getIndexInLine()+cmdtoken->getName().length()+1;
              else // indent relative to 'with'
                {
                  CodeDocument::Position p (&document, substarts[last]);
                  col=p.getIndexInLine()+4+1;
                }
              //std::cout << "COMMA indent, column=" << col << "\n";
            }
          // ELSE (the very last line does NOT end with comma) if
          // line-1 is >= cmdline and DOES end with comma then we are
          // done with comma indenting so intent to body or pos
          else if ((cmdline<=line-1) && isCommaTerminatedLine(line-1))
            {
              if (cmdtoken->getData1()>0)
                {
                  col=pos.getIndexInLine()+2;
                  //std::cout << "BODY indent (after comma stop), column=" << col << "\n";
                }
              else
                {
                  col=pos.getIndexInLine();
                  //std::cout << "RESET indent (after comma stop), column=" << col << "\n";
                }
            }
          // ELSE if the last indented is 'else' then body indent
          // based on position of 'else'
          else if (subtypes[last]==SalSyntax::SalElse)
            {
              CodeDocument::Position p (&document, substarts[last]);
              col=p.getIndexInLine()+2;
              //std::cout << "ELSE indent, column=" << col << "\n";
            }          
          // else if the command is a body indent, indent to the last
          // expression or to 2 past the first (command) expr
          else if (cmdtoken->getData1()>0)
            {
              if (last==0) // the command, no subexprs on own line
                {
                  col=pos.getIndexInLine()+2;
                  //std::cout << "BODY indent, column=" << col << "\n";
                }
              // else indent to the last expression
              else
                {
                  CodeDocument::Position p (&document, substarts[last]);
                  col=p.getIndexInLine();
                  //std::cout << "LAST indent (body), column=" << col << "\n";
                }
            }
          // else indent to the last expression
          else
            {
              CodeDocument::Position p (&document, substarts[last]);
              col=p.getIndexInLine();
              //std::cout << "LAST indent, column=" << col << "\n";
            }
        }
      else
        {
          col=lastIndented(substarts, false);
          //std::cout << "non-standard sal indent, column=" << col << "\n";
        }
    }

  // if we are looking at an 'end' or an 'else' in the cursor line
  // then adjust -2

  CodeDocument::Position bol (getBOL());
  CodeDocument::Position eol (getEOL(bol)); 
  while (bol!=eol && (bol.getCharacter()==T(' ') || bol.getCharacter()==T('\t'))) 
    bol.moveBy(1);
  if (lookingAt(bol, T("end"), true, true) || lookingAt(bol, T("else"), true, true))
    {
      col-=2;
      //std::cout << "cursor is looking at end or else\n";
    }
  return jmax(col,0);
}

bool CodeBuffer::isCommaTerminatedLine(int line)
{
  // quick and dirty test for line ending with comma. doesnt check for
  // () or "" nesting etc
  CodeDocument::Position b (&document, line, 0);
  CodeDocument::Position e (&document, line, INT_MAX);
  bool x=false;
  while (b != e)
    {
      const tchar c=b.getCharacter();
      if (c==T(',')) x=true;
      else if (char_comment_p(syntax->syntab, c)) break;
      else if (char_white_p(syntax->syntab, c)) ;
      else x=false;
      b.moveBy(1);
    }
  return x;
}  

int CodeBuffer::lastIndented(Array<int>& starts, bool index)
{
  // search array of expr starting positions and return the indent
  // column (or array index) of the latest postion that is first in
  // its line, or position of first expr if there isn't one
  int size=starts.size();
  if (size==0) return -1; // -1 for error either way
  else if (size==1) // if only one expr use it
    {
      CodeDocument::Position a (&document, starts[0]);
      return (index) ? 0 : a.getIndexInLine();
    }
  else // find latest expr that starts a line
    {
      int i=0;
      for (i=starts.size()-1; i>0; i--)
        {
          CodeDocument::Position a (&document, starts[i-1]);
          CodeDocument::Position b (&document, starts[i]);
          // if the i-1 expr is on an earlier line then THIS expr
          // starts a line
          if (a.getLineNumber() < b.getLineNumber())
            break;
        }
      CodeDocument::Position a (&document, starts[i]);
      return (index) ? i : a.getIndexInLine();
    }
}

/*=======================================================================*
                              Scanning Functions
 *=======================================================================*/

bool CodeBuffer::scanEOL(CodeDocument::Position& pos)
{
  // move position to end of line, return true if actually moved
  CodeDocument::Position eol (&document, pos.getLineNumber(), INT_MAX);
  if (pos==eol)
    return false;
  pos.setLineAndIndex(eol.getLineNumber(),eol.getIndexInLine());
  return true;
}

bool CodeBuffer::scanBOL(CodeDocument::Position& pos)
{
  // move position to beginning of line, return true if actually moved
  if (pos.getIndexInLine()==0)
    return false;
  pos.setLineAndIndex(pos.getLineNumber(),0);
  return true;
}

bool CodeBuffer::scanToken(CodeDocument::Position& pos, const int dir, const CodeDocument::Position end)
{
  // scan while position is on a token
  bool token=false;
  bool atend=false;
  while (!atend && char_token_p(syntax->syntab, pos.getCharacter()))
    {
      token=true;
      pos.moveBy(dir);
      if (pos==end) atend=true;
    }
  // pos is now on delim or at End. If not at end then check to see if
  // the delim is escaped. if it is then continue searching
  if (atend)
    return token;
  if (char_escape_p(syntax->syntab, pos.movedBy(-1).getCharacter()))
    {
      pos.moveBy(dir);
      return scanToken(pos,dir, end);
    }
  else
    return token;
}

bool CodeBuffer::scanCharacter(tchar chr, CodeDocument::Position& pos, const int dir, const CodeDocument::Position end)
{
  // scan for character, if found leave pos on the char's position and
  // return true otherwise return false
  bool found=false;
  bool atend=false;
  CodeDocument::Position check (pos);
  while (!atend)
    {
      if (check.getCharacter()==chr)
        {
          if (check.movedBy(-1).getCharacter()==T('\\'))
            check.moveBy(dir);
          else
            {
              found=true;
              atend=true;
            }
        }
      else if (check==end)
        atend=true;
      else
        check.moveBy(dir);
    }
  if (found)
    pos.setLineAndIndex(check.getLineNumber(),check.getIndexInLine());
  return found;
}

bool CodeBuffer::scanPrefix(CodeDocument::Position& pos, const int dir, const CodeDocument::Position end)
{
  bool prefix=false;
  while (char_prefix_p(syntax->syntab, pos.getCharacter()))
    {
      prefix=true;
      if (pos==end) break;
      pos.moveBy(dir);
    }
  return prefix;
}

int CodeBuffer::scanCode(CodeDocument::Position& pos, bool forward, int mode, int limit)
{
  int typ = SCAN_EMPTY;
  int dir=(forward) ? 1 : -1;
  int par=0, sqr=0, cur=0, ang=0;
  //  CodeDocument::Position end = (forward) ? getEOB() : getBOB();
  CodeDocument::Position end (&document,0);
  bool atfirst=false;
  #define ISLEVEL(a,b,c,d) (((a)==0)&&((b)==0)&&((c)==0)&&((d)==0))

  if (limit==-1)
    end=(forward) ? getEOB() : getBOB();
  else
    end.setPosition(limit);

  while (true)
    {
      if (pos==end)
        {
          if (forward) // we've moved past the last char
            break;
          else if (!atfirst) // we're checking the first char
            atfirst=true;
          else // we've already checked the first char
            break;
        }
      tchar chr=pos.getCharacter();
      // WHITE SPACE. advance one position
      if (char_white_p(syntax->syntab, chr))
        {  
          pos.moveBy(dir);
        }
      // COMMENT CHAR. advance forward eol or backward one char
      else if (char_comment_p(syntax->syntab, chr))
        {
          if (forward)
            scanEOL(pos);
          else
            pos.moveBy(dir);
        }
      // MAYBE MOVING BACKWARD IN A COMMENT LINE
      else if ((!forward) &&
               scanCharacter(T(';'), // FIXME!
                             pos, dir, 
                             CodeDocument::Position(&document, 
                                                    pos.getLineNumber(),
                                                    0)))
        {
          pos.moveBy(dir); // move one beyond the comment character
        }
      // SKIP WHITE/COMMENTS. char now not white or part of comment
      else if (mode==ScanFlags::MoveWhiteAndComments)
        {
          break;
        }
      // TOKEN CHAR. scan out token
      else if (char_token_p(syntax->syntab, chr))
        {
          scanToken(pos,dir,end);
          // pos is now either one beyond token or at BOB and on
          // the token start. quit scanning if at top level
          if (ISLEVEL(par,cur,sqr,ang) )
            {
              if (!forward) scanPrefix(pos,dir,end); // include any prefix chars
              typ = SCAN_TOKEN;
              break;
            }
        }
      // STRING START.  scan for end of string char
      else if (char_string_p(syntax->syntab, chr))
        {
          CodeDocument::Position check=pos.movedBy(dir);
          if (check==end)
            {
              typ=SCAN_MISMATCH;
              break;
            }
          pos.moveBy(dir); // advance position one beyond first "
          if (scanCharacter(T('\"'), pos, dir, end))
            {
              // now on end of string advance pos one past that char
              // 
              if (/*!forward &&*/ (pos!=end))  pos.moveBy(dir);
              if (ISLEVEL(par,cur,sqr,ang)) 
                {
                  typ = SCAN_STRING;
                  break;
                }
            }
          else
            {
              // missing end of string char, return error
              typ=SCAN_UNMATCHED;
              break;
            }
        }
      // PUNCTUATION. keep going unless toplevel (was token mode)
      else if (char_punctuation_p(syntax->syntab, chr))
        {
          pos.moveBy(dir);
          if (ISLEVEL(par,cur,sqr,ang)) //(mode==ScanFlags::MoveTokens) 
            {
              typ=SCAN_PUNCT;
              break;
            }
        }
      // PREFIX. keep going
      else if (char_prefix_p(syntax->syntab, chr) ) 
        {
          pos.moveBy(dir);
        }
      // OPEN PARENS TOKEN
      else if ((mode==ScanFlags::MoveTokens) && char_open_p(syntax->syntab, chr) )
        {
          pos.moveBy(dir);
          typ=SCAN_OPEN;
          break;
        }
      // CLOSE PARENS TOKEN
      else if ((mode==ScanFlags::MoveTokens) && char_close_p(syntax->syntab, chr) )
        {
          pos.moveBy(dir);
          typ=SCAN_CLOSE;
          break;
        }
      // OPEN PARENS EXPRESSION. increment level of paren.
      else if ((forward && char_open_p(syntax->syntab, chr) ) ||
               (!forward && char_close_p(syntax->syntab, chr)))
        {
          if ( paren_char_p(chr) ) par++;
          else if ( curly_char_p(chr) ) cur++;
          else if ( square_char_p(chr) ) sqr++;
          pos.moveBy(dir);
        }
      // CLOSE PARENS EXPRESSION. decrement level, stop if level zero
      else if ((forward && char_close_p(syntax->syntab, chr)) ||
               (!forward && char_open_p(syntax->syntab, chr))) 
        {
          if (paren_char_p(chr)) 
            if (par==0) typ = SCAN_UNLEVEL; else par--;
          else if (curly_char_p(chr)) 
            if (cur==0) typ = SCAN_UNLEVEL; else cur--;
          else if (square_char_p(chr)) 
            if (sqr==0) typ = SCAN_UNLEVEL; else sqr--;
          if (typ==SCAN_UNLEVEL)
            {
              break;
            }
          else if (ISLEVEL(par,cur,sqr,ang))
            {
              pos.moveBy(dir);
              if (!forward) scanPrefix(pos,dir,end); // include any prefix chars
              typ = SCAN_LIST;
              break;
            }
          else
            {
              pos.moveBy(dir);
            }
        }
      else
        {
          typ=SCAN_MISMATCH;
          break;
        } 
    } // end while

  //std::cout << "pos="<<pos.getPosition()<< ",typ="<<typ<<",isfirst="<<atfirst<<"\n";
  //std::cout << "after scan, par=" << par << "\n";
  // move pos back to the first char if backward scan

  if (typ<0) 
    ;
  else if (ISLEVEL(par,cur,sqr,ang))
    {
      // if we are moving backwards then our position is now either
      // one BEFORE the start of the expression OR we are on the first
      // character and that character is part of the expression
      if //(!forward && !atfirst && typ>0) //pos!=end
        (!forward &&  typ>0 &&
         ((pos==end && char_white_p(syntax->syntab, pos.getCharacter())) ||
          (pos!=end )    )      
         )
        {
          //std::cout << "incrementing pos\n";
          pos.moveBy(1);
        }
    }
  else
    typ=SCAN_UNMATCHED;
  return typ;
}

/*****

void CodeBuffer::test(bool forward)
{
  std::cout << "buffer width=" << getWidth() << "\n"
           << "window width=" << ((CodeEditorWindow*)getTopLevelComponent())->getWidth() << "\n";
  return;
  ((CodeEditorWindow*)getTopLevelComponent())->updateFromCustomizations();
  return;

  CodeDocument::Position start (getCaretPos());  
  CodeDocument::Position end (start);
  int res = backwardSal2Expr(start, end);
  if (res>0 )
    {
      String code=document.getTextBetween(start,end);
      std::cout << "Code ("<< start.getPosition() << "," << end.getPosition() << ")\n     '" << code.toUTF8() << "'\n";
    }
}

void CodeBuffer::backwardSalBlock(const CodeDocument::Position top)
{
  // top is 1 past an "end" tag. scan backward till balancing block open
  CodeDocument::Position bob=getBOB();
  CodeDocument::Position pos (top);
  int lev=0;
  int scan=0;
  while (true)
    {
      // moving backwards: cursor is always 1 past start of scan
      pos.moveBy(-1);
      // skip over comments and white
      scanCode(pos, false, ScanFlags::MoveWhiteAndComments);
      // now on last constituent char for scan (or at bob). set the
      // exclusive upper bound of expr to 1 above that
      CodeDocument::Position to (pos.movedBy(1)); 
      scan=scanCode(pos, false, ScanFlags::MoveExpressions);
      // quit if error or only white space
      if (scan<=0)
        break;
      String code=document.getTextBetween(pos,to);
      //std::cout << "Code ("<<from.getPosition()<<","<<to.getPosition()<<"): '" << code.toUTF8() << "'\n";
      if (scan==SCAN_TOKEN)
        {
          if (SynTok* tok=syntax->getSynTok(code))
            {
              // token is a literal (e.g. statement, op)
              int typ=tok->getType();
              if (SalSyntax::isSalBlockClose(typ))
                lev++; 
              else if (SalSyntax::isSalBlockOpen(typ))
                lev--; 
              // stop on a blockopen with no pending end. this doenst
              // mean the statement is actually balanced since the
              // word could be a blockopen that was reached without a
              // balancing end (in which case the level is negative)
              if (lev<=0)
                break;
            }
        }
      if (pos==bob) break;
    }
  if (scan<0)
    std::cout << "scan error: " << scan << "\n";
  else if (scan==0)
    std::cout << "scan empty\n";
  else if (lev>0)
    std::cout << "missing block open for end" << "\n";
  else if (lev<0)
    std::cout << "block open without an end" << "\n";
  else
    {
      String expr=document.getTextBetween(pos,top);
      std::cout << "Expr: '" << expr.toUTF8() << "'\n";
    }
  std::cout << "Done.\n";
}



void CodeBuffer::LOOKINGATtestScan(bool forward)
{
  bool delim=true;
  String match = SystemClipboard::getTextFromClipboard().trim();
  if (match.isEmpty()) return;
  if (match.containsOnly(T("[]{}()"))) delim=false;
  if (lookingAt(getCaretPos(), match, forward, delim))
    std::cout << "buffer matches '" << match.toUTF8() << "'\n";
  else
    std::cout << "buffer does not match '" << match.toUTF8() << "'\n";
}

void CodeBuffer::TOKENtestScan(bool forward)
{
  CodeDocument::Position pos = getBOB();
  CodeDocument::Position end = getEOB();
  int dir = (forward) ? 1 : -1;
  int scan=0;
  while (pos!=end)
    {
      scan=scanCode(pos,true,ScanFlags::MoveWhiteAndComments);
      if (scan<0)
        {
          std::cout << "scan: error (" << scan << ") while scanning comments and white, pos=" << pos.getPosition() << "\n";
          break;
        }
      CodeDocument::Position far(pos);
      scan=scanCode(far, true, ScanFlags::MoveTokens);
      if (scan<0)
        {
          std::cout << "scan: error (" << scan << ") while scanning comments and white, pos=" << far.getPosition() << "\n";
          break;
        }
      else if (scan>0)
        {
          String tok=document.getTextBetween(pos,far);
          std::cout << "token='" << tok.toUTF8() << "'\n";
        }
      pos=far;
    }
}


void CodeBuffer::ORIGINALtestScan(bool forward)
{
  CodeDocument::Position from (getCaretPos());

  CodeDocument::Position end = (forward) ? getEOB() : getBOB();
  int dir = (forward) ? 1 : -1;
  int scan=0;

  if (from==end)
     {
       std::cout << "nothing to do\n";
        return;
     }
  // if backward the cursor is one after the start of the expression
  if (!forward) from.moveBy(-1);

  // advance past whitespace and comments

  //skipCommentsAndWhite(from,dir,end); 
  scanCode(from, forward, ScanFlags::MoveWhiteAndComments);
  std::cout << "after skipCommentsAndWhite\n";

  CodeDocument::Position to (from);  

  if (forward)
    {
      scan=scanCode(to, forward, 0);
      std::cout << "--------------------\nscan=" << ScanFlags::scanResultToString(scan).toUpperCase().toUTF8() << "\n";
      std::cout << "start=" << from.getPosition() << ", end=" << to.getPosition() << "\n";
      if (scan>0)
        std::cout << "text='" << document.getTextBetween(from,to).toUTF8() << "'\n";
    }
  else
    {
      scan=scanCode(to, forward, 0);
      from.moveBy(1);
      std::cout << "--------------------\nscan=" << ScanFlags::scanResultToString(scan).toUpperCase().toUTF8() << "\n";
      std::cout << "start=" << to.getPosition() << ", end=" << from.getPosition() << "\n";
      if (scan>0)
        std::cout << "text='" << document.getTextBetween(to,from).toUTF8() << "'\n";
    }
}
*****/
