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
  : DocumentWindow(String::empty, Colours::white, 
                   DocumentWindow::allButtons, true)
{
  setMenuBar(this);

  if (file.existsAsFile())
    {
      String ext=file.getFileExtension();
      String lsp=T(".lisp.lsp.scm.cm.clm.cmn.ins");
      String sal=T(".sal");
      String sal2=T(".sal2");
      String fms=T(".fms");
      if (synt==TextIDs::Empty)
	if (sal.contains(ext)) synt=TextIDs::Sal;
	else if (sal2.contains(ext)) synt=TextIDs::Sal2;
	else if (lsp.contains(ext)) synt=TextIDs::Lisp;
	else if (fms.contains(ext)) synt=TextIDs::Fomus;
        else synt=TextIDs::Text; 
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
  document.replaceAllContent(text);
  document.setSavePoint();
  document.clearUndoHistory();
  // parse optional first-line buffer customizations comment.  if no
  // comment then customs will be null
  XmlElement* customs=getCustomizations();
  // customization syntax overrides any other
  if (customs && customs->hasAttribute(T("syntax:")))
    synt=TextIDs::fromString(customs->getStringAttribute(T("syntax:")));
  Syntax* syntax;
  switch (synt)
    {
    case TextIDs::Text: syntax=TextSyntax::getInstance(); break;
    case TextIDs::Lisp: syntax=LispSyntax::getInstance(); break;
    case TextIDs::Sal: syntax=SalSyntax::getInstance(); break;
    case TextIDs::Sal2: syntax=Sal2Syntax::getInstance(); break;
    default: syntax=TextSyntax::getInstance(); break;
    }
  CodeBuffer* buffer=new CodeBuffer(document, syntax, &commands, customs);
  setContentComponent(new EditorComponent(buffer));

  commands.registerAllCommandsForTarget(this);
  setApplicationCommandManagerToWatch(&commands);
  commands.setFirstCommandTarget(this);
  setWantsKeyboardFocus(false);

  setWindowTitle(title);
  setResizable(true, true); 
  setUsingNativeTitleBar(true);
  setDropShadowEnabled(true);
  //std::cout << "setting window width to" << buffer->getWidth()+28 << "\n";
  centreWithSize(jmin(800, buffer->getWidth()+0), //28
                 jmin(800, buffer->getHeight()+0)
                 );
  if (customs) delete customs;
  setVisible(true);
}

CodeEditorWindow::~CodeEditorWindow ()
{
  commands.setFirstCommandTarget(0);
  setMenuBar(0);
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
      CommandIDs::EditorSave,
      CommandIDs::EditorSaveAs,
      CommandIDs::EditorShowDirectory,
      CommandIDs::EditorSetDirectory,

      CommandIDs::EditorClose,      

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
      CommandIDs::EditorTabWidth + 2,
      CommandIDs::EditorTabWidth + 4,
      CommandIDs::EditorTabWidth + 6,
      CommandIDs::EditorTabWidth + 8,
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
  // Command shortcuts are only added if emacs mode is false
  CodeBuffer* buff=getCodeBuffer();
  bool commandkeyactive=(SysInfo::isMac() || !buff->isEmacsMode());
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
      info.setTicked(getCodeBuffer()->getTextType()==data);
      info.setActive(false);
      break;
    case CommandIDs::EditorFontSize:
      info.shortName=String(data);
      info.setTicked(getCodeBuffer()->getFontSize()==data);
      break;
    case CommandIDs::EditorTabWidth:
      info.shortName=String(data);
      info.setTicked(getCodeBuffer()->getTabWidth()==data);
      break;
    case CommandIDs::EditorTheme:
      info.shortName=T("Editor Theme ") + String(data);
      break;
    case CommandIDs::EditorSaveCustom:
      info.shortName=T("Save Customizations");
      break;
    case CommandIDs::EditorReadCustom:
      {
        info.shortName=T("Read Customizations");
        info.setActive(isCustomComment());
      }
      break;
    case CommandIDs::EditorParensMatching:
      info.shortName=T("Parentheses Matching");
      info.setTicked(getCodeBuffer()->isParensMatching());
      break;
    case CommandIDs::EditorEmacsMode:
      info.shortName=T("Emacs Mode");
      info.setTicked(getCodeBuffer()->isEmacsMode());
      break;
    case CommandIDs::EditorExecute:
      info.shortName=T("Execute");
      if (commandkeyactive)
	info.addDefaultKeypress(KeyPress::returnKey, ModifierKeys::commandModifier);
      break;
    case CommandIDs::EditorExpand:
      info.shortName=T("Expand");
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
    case CommandIDs::EditorSave:
      saveFile(false);
      break;
    case CommandIDs::EditorSaveAs:
      saveFile(true);
      break;
    case CommandIDs::EditorSetDirectory:
      ((Grace *)JUCEApplication::getInstance())->chooseWorkingDirectory();
      break;
    case CommandIDs::EditorShowDirectory:
      ((Grace *)JUCEApplication::getInstance())->showWorkingDirectory();
      break;
    case CommandIDs::EditorClose:
      closeButtonPressed();
      break;
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
      std::cout << "EditorSyntax\n";
      break;
    case CommandIDs::EditorFontSize:
      getCodeBuffer()->setFontSize(data);
      break;
    case CommandIDs::EditorTabWidth:
      getCodeBuffer()->setTabWidth(data);
      break;
    case CommandIDs::EditorTheme:
      std::cout << "EditorTheme\n";
      break;
    case CommandIDs::EditorReadCustom:
      applyCustomComment();
      break;
    case CommandIDs::EditorSaveCustom:
      writeCustomComment();
      break;
    case CommandIDs::EditorParensMatching:
      getCodeBuffer()->isParensMatching(!getCodeBuffer()->isParensMatching()); // toggle parens matching
      break;
    case CommandIDs::EditorEmacsMode:
      getCodeBuffer()->isEmacsMode(!getCodeBuffer()->isEmacsMode()); // toggle emacs mode
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
      menu.addCommandItem(&commands, CommandIDs::EditorNew);
      menu.addCommandItem(&commands, CommandIDs::EditorOpen);
      menu.addSeparator();
      menu.addCommandItem(&commands, CommandIDs::EditorSave);
      menu.addCommandItem(&commands, CommandIDs::EditorSaveAs);
      menu.addSeparator();
      menu.addCommandItem(&commands, CommandIDs::EditorShowDirectory);
      menu.addCommandItem(&commands, CommandIDs::EditorSetDirectory);
      menu.addSeparator();
      menu.addCommandItem(&commands, CommandIDs::EditorClose);
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
      PopupMenu sub;
      sub.addCommandItem(&commands, CommandIDs::EditorSyntax+TextIDs::Text);
      sub.addCommandItem(&commands, CommandIDs::EditorSyntax+TextIDs::Lisp);
      sub.addCommandItem(&commands, CommandIDs::EditorSyntax+TextIDs::Sal);
      sub.addCommandItem(&commands, CommandIDs::EditorSyntax+TextIDs::Sal2);
      menu.addSubMenu(T("Syntax"), sub);
      menu.addSeparator();
      sub.clear();
      for (int i=0; i<8; i++)
        sub.addCommandItem(&commands, CommandIDs::EditorTheme+i);
      menu.addSubMenu(T("Theme"), sub);
      sub.clear();
      for (int i=8; i<=32; i+=2)
        sub.addCommandItem(&commands, CommandIDs::EditorFontSize+i);
      menu.addSubMenu(T("Font Size"), sub);
      sub.clear();
      for (int i=2; i<=8; i+=2)
        sub.addCommandItem(&commands, CommandIDs::EditorTabWidth+i);
      menu.addSubMenu(T("Tab Width"), sub);
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

// 
//
//

void CodeEditorWindow::setWindowTitle(String title)
{
  if (title.isEmpty())
    {
      if (sourcefile==File::nonexistent)
        {
          int id=getCodeBuffer()->getTextType();
          title=T("Untitled");
          title << T(" (") << TextIDs::toString(id) << T(")");
        }
      else
        title = sourcefile.getFileName();
    }
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

/*
void CodeEditorWindow::saveFile()
{
  if (getCodeBuffer()->isChanged())
    if (sourcefile.existsAsFile())
      {
	if (sourcefile.replaceWithText(document.getAllContent()))
          {
            document.setSavePoint();
            getCodeBuffer()->isChanged(false);
            Preferences::getInstance()->recentlyOpened.addFile(sourcefile);
          }
        else
          AlertWindow::showMessageBox(AlertWindow::WarningIcon, T("Save File"), 
                                      T("Error saving ") + sourcefile.getFullPathName() + T(". File not saved."));
      }
    else
      saveFileAs();
}

void CodeEditorWindow::saveFileAs()
{
  bool exists=sourcefile.existsAsFile();
  File saveto ( (exists) ? sourcefile.getParentDirectory() : File::getCurrentWorkingDirectory());
  FileChooser choose (T("Save File"), saveto, T("*.*"), true);
  if (choose.browseForFileToSave(true))
    {
      sourcefile=choose.getResult();
      if (sourcefile.replaceWithText(document.getAllContent()))
        {
          document.setSavePoint();
          getCodeBuffer()->isChanged(false);
          if (exists) document.clearUndoHistory(); // SHOULD I DO THIS?
          setWindowTitle();
          Preferences::getInstance()->recentlyOpened.addFile(sourcefile);
        }
      else
        AlertWindow::showMessageBox(AlertWindow::WarningIcon, T("Save File"), 
                                    T("Error saving ") + sourcefile.getFullPathName() + T(". File not saved."));
    }
}
*/

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
  //;; -*- syntax: lisp, theme: "clarity and beauty", -*-
  /*  String line=document.getLine(0);
  if (line.isEmpty()) return 0;
  int len=line.length();
  int pos=0;
  while (pos<len && line[pos]==T(';')) pos++;
  while (pos<len && CharacterFunctions::isWhitespace(line[pos])) pos++;
  if (pos==len || line.substring(pos,pos+3)!=T("-*-")) return 0;
  line=line.substring(pos+3).trim();
  */
  if (!isCustomComment()) return 0;
  String line=document.getLine(0).fromFirstOccurrenceOf(T("-*-"), false, false).trimStart();
  StringArray tokens;
  tokens.addTokens(line, T("\t, ;"), T("\""));
  tokens.removeEmptyStrings();
  //for (int i=0; i<tokens.size(); i++) std::cout << "tokens["<<i<<"]='" << tokens[i].toUTF8() << "'\n";
  XmlElement* xml=new XmlElement(T("customizations"));
  for (int i=0; i<tokens.size()-1; i+=2)
    {
      if (tokens[i]==T("syntax:") )
        {
          if (tokens[i+1].equalsIgnoreCase(T("text")))
            xml->setAttribute(tokens[i], tokens[i+1].toLowerCase());
          else if (tokens[i+1].equalsIgnoreCase(T("lisp")))
            xml->setAttribute(tokens[i], tokens[i+1].toLowerCase());
          else if (tokens[i+1].equalsIgnoreCase(T("sal")))
            xml->setAttribute(tokens[i], tokens[i+1].toLowerCase());
          else if (tokens[i+1].equalsIgnoreCase(T("sal2")))
            xml->setAttribute(tokens[i], tokens[i+1].toLowerCase());
          else if (tokens[i+1].equalsIgnoreCase(T("fomus")))
            xml->setAttribute(tokens[i], tokens[i+1].toLowerCase());
        }
      /*      else if (tokens[i]==T("tab-width:") )
        {
          int n=tokens[i+1].getIntValue();
          if (1<=n && n<=16)
            xml->setAttribute(tokens[i], n);
            } */
      else if (tokens[i]==T("font-size:") )
        {
          float n=tokens[i+1].getFloatValue();
          if (8.0<=n && n<=80.0)
            xml->setAttribute(tokens[i], floor(n));
        }
      else if (tokens[i]==T("theme:"))
        {
          if (tokens[i+1].isQuotedString())
            xml->setAttribute(tokens[i], tokens[i+1].unquoted());
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
  if (xml)
    {
      std::cout << "Customizations:\n";
      for (int i=0; i<xml->getNumAttributes(); i++)
        std::cout << "  " << xml->getAttributeName(i).toUTF8() << " " 
                  << xml->getAttributeValue(i).toUTF8() << "\n";
      delete xml;
    }
}

void CodeEditorWindow::writeCustomComment()
{
  //;; -*- syntax: lisp; theme: "clarity and beauty"; -*-
  String custom (T(";;; -*- "));
  CodeBuffer* buffer=getCodeBuffer();
  custom << "syntax: " << TextIDs::toString(getCodeBuffer()->getTextType());
  custom << ", font-size: " << buffer->getFontSize(); 
  custom << ", theme: \"standard emacs\"" ; //<< getTheme.get
  if (buffer->getTabWidth()!=2)
    custom << ", tab-width: " << buffer->getTabWidth();
  if (buffer->getColumnWidth()!=74)
    custom << ", column-width: " << buffer->getColumnWidth();
  custom << " -*-\n";
  CodeDocument::Position a(&document,0);
  if (isCustomComment())
    {
      // delete first line including eol
      CodeDocument::Position e (&document, 0, INT_MAX);
      document.deleteSection(a,e);
    }
  document.insertText(a,custom);
}

/*=======================================================================*
                                   CodeBuffer
 *=======================================================================*/

CodeBuffer::CodeBuffer(CodeDocument& doc, Syntax* tokenizer, ApplicationCommandManager* commands, XmlElement* customs)
  : 
  document (doc),
  fontsize (16),
  tabwidth (2),
  columnwidth (74),
  parensmatching(true),
  changed (false),
  CodeEditorComponent(doc, tokenizer)
{
  syntax=tokenizer;
  manager=commands;
  fontsize=Preferences::getInstance()->getIntProp(T("EditorFontSize"), 16);
  emacsmode=Preferences::getInstance()->getBoolProp(T("EditorEmacsMode"), SysInfo::isMac());
  if (customs)
    {
      fontsize=customs->getDoubleAttribute(T("font-size:"), fontsize);
      tabwidth=customs->getIntAttribute(T("tab-width:"), tabwidth);
    }
  Font mono (Font::getDefaultMonospacedFontName(), (float)fontsize, Font::plain);
  setFont(mono);
  setTabSize(tabwidth, true);
  //  setSize(getCharWidth() * columnwidth, getLineHeight() * 20);
  setSize(getCharWidth() * columnwidth, getLineHeight() * 30);
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
        return true;
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

int CodeBuffer::getColumnWidth()
{
  return columnwidth;
}

void CodeBuffer::setColumnWidth(int cols)
{
  columnwidth=cols;
  Font mono (Font::getDefaultMonospacedFontName(), (float)fontsize, Font::plain);
  setSize(getCharWidth() * columnwidth, getLineHeight() * 20);
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
  // return true if buffer contents matches text starting a pos, which
  // must be ON the first char to check. if delimited is true then the
  // text must match as a delimited word.
  CodeDocument::Position at (pos);
  int len=text.length();
  if (forward)
    {
      CodeDocument::Position end=getEOB();
      for (int i=0; i<len && at!=end; i++)
        if ((at==end) || at.getCharacter() != text[i])
          return false;
        else
          at.moveBy(1);
      if (delimited)
        return ((at==end) || !char_token_p(syntax->syntab, at.getCharacter()));
      return true;
    }
  else
    {
      int end=len-1;
      int loc=pos.getPosition();
      if (end>loc) // not enough backward chars to match
        return false;   
      for ( ; end>=0; end--)
        if (at.getCharacter() != text[end])
          return false;
        else
          at.moveBy(-1);
      if (!delimited) 
        return true;
      loc-=len;
      return ((loc<0) ? true : (!char_token_p(syntax->syntab, at.getCharacter())));
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
  char c[2];
  c[0]=(char)p.getCharacter();
  c[1]=0;
  std::cout << "pos=" << p.getPosition() << " (" << p.getLineNumber() << "," << p.getIndexInLine() << "), char='" << c << ", bol="<< isBOL() << ", eol=" << isEOL()   << ", bob="<< isBOB() << ", eob=" << isEOB() << "\n";
}

void CodeBuffer::test(bool forward)
{
  CodeEditorWindow* win=(CodeEditorWindow *)getTopLevelComponent();
  std::cout << "buf=" << getWidth() << " " << getHeight() << "\n"
            << "win=" << win->getWidth() << " " <<  win->getHeight() << "\n";
}

/*=======================================================================*
                    Evaluation and Syntactic Backward Expression
 *=======================================================================*/

void CodeBuffer::eval(bool expandonly)
{
  CodeDocument::Position from (getCaretPos());
  CodeDocument::Position to (getCaretPos());
  int type=getTextType();
  int regn=getHighlightedRegionLength();
  int scan=SCAN_EMPTY;
  if (regn>0)
    {
      from=getHighlightedRegionStart();
      to=from.movedBy(regn);
      scan=1; // is never empty
    }
  else if (type==TextIDs::Lisp)
    scan=backwardLispExpr(from, to);
  else if (type==TextIDs::Sal2)
    {
      scan=backwardSal2Expr(from, to);
    }
  if (scan>SCAN_EMPTY)
    {
      String code=document.getTextBetween(from, to);
      if (expandonly && (type==TextIDs::Lisp))
        code=T("(macroexpand ") + code + T(")");
      if (regn)
        if (type==TextIDs::Lisp)
          code=T("(begin ") + code + T(")");
        else
          code=T("begin ") + code + T(" end");
      if (type==TextIDs::Lisp)
        SchemeThread::getInstance()->eval(code);
      std::cout << "eval='" << code.toUTF8() << "'\n";
    }
  else
    PlatformUtilities::beep();
}

int CodeBuffer::backwardLispExpr(CodeDocument::Position& from, CodeDocument::Position& to)
{
  CodeDocument::Position pos (getCaretPos());
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
  CodeDocument::Position pos (getCaretPos());
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
    while (true)
      {
        // pos is on last consitute char of backwards expr (or at bol)
        // set exclusive end of current expr and scan backwards
        CodeDocument::Position end (pos.movedBy(1)); 
        scan=scanCode(pos, false, ScanFlags::MoveExpressions);
        // quit if scan error or only white space
        if (scan<=0)
          break;
        String code=document.getTextBetween(pos,end);
        //std::cout << "Code ("<<pos.getPosition()<<","<<end.getPosition()<<"): '" << code.toUTF8() << "'\n";
        if (scan==SCAN_TOKEN)
          {
            if (SynTok* tok=syntax->getSynTok(code))
              {
                // token is a literal. stop if first thing encountered
                if (last==0)
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
                // otherwise its a clausal or op so keep going...
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
                else if (code.containsOnly(T("0123456789+-.")) ||
                         code.startsWith(T("#")) ||
                         code.startsWith(T(":")) ||
                         code.endsWith(T(":")))
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

  // stopped without lower bound means no expr encountered
  if (here<0) 
    {
      scan=SCAN_EMPTY;
      here=pos.getPosition();
    }
  //std::cout << "setting from position\n";
  from.setPosition(here);
  //std::cout << "setting to position\n";
  to.setPosition(top.getPosition());
  //std::cout << "returning\n";
  return scan;
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

  if (getTextType()==TextIDs::Sal2)
    {
      col=indentSal2();
      return;
    }
  if (getTextType()==TextIDs::Lisp)
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
  while (bol!=getEOL() && bol.getCharacter()==T(' '))
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
          substarts.remove(0); // 
          int x=columnOfLastIndented(substarts);
          //std::cout << "returning indent col=" << x << "\n";
          return x;
        }
    }
  else // token not special, indent to last expr or to pos+1 if none
    {
      std::cout << "no special nargs=" << nargs << "\n";
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
          int x=columnOfLastIndented(substarts);
          //std::cout << "returning indent col=" << x << "\n";
          return x;
        }
    }
}

int CodeBuffer::indentSal2()
{
  CodeDocument::Position bol (getBOL());
  CodeDocument::Position pos (bol);  
  Array<int> subtypes;
  Array<int> substarts;
  int line=pos.getLineNumber();
  int scan=0;
  bool back=false;

  // if no lines above point indent 0 else move cursor to end of
  // previous line and scan backwards until either unlevel OR a
  // balanced expression in column 0. record types and starting
  // positions of subexpressions traversed

  if (line==0) return 0;
  // move position to EOL of previous line
  pos.setLineAndIndex(line-1, INT_MAX);
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
                  if (SalSyntax::isSalCommandType(type) || type==SalSyntax::SalEnd || type==SalSyntax::SalElse)
                    break;
                }
            }
          if (pos.getIndexInLine()==0)
            break;
          pos.moveBy(-1); 
        }
      else
        break;
    }
  if (scan==0)
    {
      //std::cout << "empty: indent column=0\n" ;
      return 0;
    }
  else if (scan<0)
    {
      std::cout << "unlevel: position="<<pos.getPosition()<<", (column="<<pos.getIndexInLine()<<")\n";
      // use indentation of subexp or pos
      if (subtypes.size()>0)
        return columnOfLastIndented(substarts);
      else
        return pos.movedBy(1).getIndexInLine();
    }
  else
    {
      std::cout << "expression: position="<<pos.getPosition()<<", (column="
                <<pos.getIndexInLine()<<") type="<<subtypes[0] << "\n";


      // see if we are looking at an 'end' or an 'else' on cursor
      // line. if so we will adjust indent -2
      while (bol.getCharacter()==T(' ') || bol.getCharacter()==T('\t')) 
        bol.moveBy(1);
      if (lookingAt(bol, T("end"), true, true) || lookingAt(bol, T("else"), true, true))
        back=true;
      if (back)
        std::cout << "cursor is looking at end or else\n";
      return 0;
    }
}

int CodeBuffer::columnOfLastIndented(Array<int>& starts)
{
  // starts is an array of the starting positions of all the backward
  // sub expressions. return the column of the latest starting postion
  // that is also the first position in its line, otherwise return the
  // position of the first expr.  we use the last expression because
  // if the user "hand indentents" a line then we want to respect that
  // postion as the indentation column for subsequent lines
  int size=starts.size();
  if (size==0) return -1; // -1 for error
  else if (size==1)
    {
      // if only one expr use it
      CodeDocument::Position a (&document, starts[0]);
      return a.getIndexInLine();
    }
  else
    { // get column latest expr that starts a line
      int i=0;
      for (i=starts.size()-1; i>0; i--)
        {
          CodeDocument::Position a (&document, starts[i-1]);
          CodeDocument::Position b (&document, starts[i]);
          // if the i-1 expr is on an earlier line then this expr is
          // the latest expr that starts a line
          if (a.getLineNumber() < b.getLineNumber())
            break;
        }
      CodeDocument::Position a (&document, starts[i]);
      return a.getIndexInLine();
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

int CodeBuffer::scanCode(CodeDocument::Position& pos, bool forward, int mode)
{
  int typ = SCAN_EMPTY;
  int dir=(forward) ? 1 : -1;
  int par=0, sqr=0, cur=0, ang=0;
  CodeDocument::Position end = (forward) ? getEOB() : getBOB();
  bool atfirst=false;
  #define ISLEVEL(a,b,c,d) (((a)==0)&&((b)==0)&&((c)==0)&&((d)==0))

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
              // found end of string advance pos one past that char
              pos.moveBy(dir);
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
