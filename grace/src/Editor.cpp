/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

#include "Editor.h"
#include "Grace.h"
#include "Resources.h"

TextFileOutputStream::TextFileOutputStream(const File& f,
					   const int bufferSize_) 
  : FileOutputStream(f, bufferSize_)
{

}

TextFileOutputStream::~TextFileOutputStream()
{
  
}

void TextFileOutputStream::writeText(const String& text,
				const bool asUnicode,
				const bool writeUnicodeHeaderBytes,
				const bool asDOS)
{
    if (asUnicode)
    {
        if (writeUnicodeHeaderBytes)
            write ("\x0ff\x0fe", 2);

        const juce_wchar* src = (const juce_wchar*) text;
        bool lastCharWasReturn = false;
	if(asDOS) {
	  while (*src != 0)
	    {
	      if (*src == L'\n' && ! lastCharWasReturn)
                writeShort ((short) L'\r');
	      
	      lastCharWasReturn = (*src == L'\r');
	      writeShort ((short) *src++);
	    }
	} else {
	  while (*src != 0)
	    {
	      writeShort ((short) *src++);
	    }
	}
    }
    else
    {
        const char* src = (const char*) text;
        const char* t = src;

	if(asDOS) {
	  for (;;)
	    {
	      if (*t == '\n')
		{
		  if (t > src)
                    write (src, (int) (t - src));
		  
		  write ("\r\n", 2);
		  src = t + 1;
		}
	      else if (*t == '\r')
		{
		  if (t[1] == '\n')
                    ++t;
		}
	      else if (*t == 0)
		{
		  if (t > src)
                    write (src, (int) (t - src));
		  
		  break;
		}
	      
	      ++t;
	    }
	} else {
	  write( src, text.length());
		  
	}
    }
}



TextFile::TextFile() : File()
{
  #ifdef JUCE_WIN
  isDOS = true;
#else
  isDOS = false;
#endif

}

TextFile::TextFile(const File& other) : File(other)
{
  #ifdef JUCE_WIN
  isDOS = true;
#else
  isDOS = false;
#endif
}


TextFile::TextFile (const String& path) : File(path)
{

}
  

TextFile::~TextFile()
{
}

TextFileOutputStream* TextFile::createOutputStream (const int bufferSize)
{
  TextFileOutputStream* const out = new TextFileOutputStream (*this, bufferSize);
    
    if (out->failedToOpen())
    {
        delete out;
        return 0;
    }
    else
    {
        return out;
    }
}


bool TextFile::appendText (const String& text,
			   const bool asUnicode,
			   const bool writeUnicodeHeaderBytes) 
{
  TextFileOutputStream* const out = createOutputStream();
  
  if (out != 0)
    {
      out->writeText (text, asUnicode, writeUnicodeHeaderBytes, isDOS);
      delete out;
      
      return true;
    }
  
  return false;
}

bool TextFile::replaceWithText (const String& textToWrite,
				const bool asUnicode,
				const bool writeUnicodeHeaderBytes)
{
  TextFile tempFile (getSiblingFile (T(".") + getFileName()).getNonexistentSibling (false));
  
  if (tempFile.appendText (textToWrite, asUnicode, writeUnicodeHeaderBytes)
      && tempFile.moveFileTo (*this))
    {
      return true;
    }
  
  tempFile.deleteFile();
  return false;
}

const String TextFile::loadFileAsString()
{
  String str;
  String outstr;
  int i;
  tchar c;

  if (! existsAsFile())
    return String::empty;
  
  FileInputStream in (*this);
  str =  in.readEntireStreamAsString();

  
  for(i=0;i<str.length();i++) {
    c = str[i];
    if(c == '\r') {
      isDOS = true;
    }
    else
      outstr << c;
  }
  return outstr;
}

struct filetypemapping {
  // global filetype->syntax mapping. new mappings can be added via
  // addSyntaxFileType
  String name;
  TextID type;
} syntaxFileTypes [32] =  {{T(".lisp"), TextIDs::Lisp},
			   {T(".lsp"), TextIDs::Lisp},
			   {T(".cl"), TextIDs::Lisp},
			   {T(".scm"), TextIDs::Lisp},
			   {T(".cm"), TextIDs::Lisp},
			   {T(".clm"), TextIDs::Lisp},
			   {T(".cmn"), TextIDs::Lisp},
			   {T(".ins"), TextIDs::Lisp},
			   {T(".fms"), TextIDs::Lisp},
			   {T(".asd"), TextIDs::Lisp},
			   {T(".sal"), TextIDs::Sal},
			   {T(".text"), TextIDs::Text},
			   {T(".txt"), TextIDs::Text},
			   {T(""), TextIDs::Empty}  }; 

TextID getSyntaxFromFileType(String filename) {
  String ext = filename.fromLastOccurrenceOf(T("."), true, false);
  if ( ext == String::empty ) return TextIDs::Text;
  for (int i=0; i<32; i++)
    if ( syntaxFileTypes[i].name == String::empty )
      return TextIDs::Text;
    else if ( ext == syntaxFileTypes[i].name ) 
      return syntaxFileTypes[i].type;
  return TextIDs::Text; 
}

bool addSyntaxFileType(String name, TextID synt) {
  int i;
  for (i=0; i<32; i++)
    if ( syntaxFileTypes[i].name == T("") )
      break;
  if (i==32) return false;
  syntaxFileTypes[i].name=name;
  syntaxFileTypes[i].type=synt;
  if (i<31) {
    syntaxFileTypes[i].name=T("");
    syntaxFileTypes[i].type=TextIDs::Empty;
  }
  return true;
}

EditorWindow::EditorWindow (int synt, int flags, String filename,
			    String title, String text)
  : DocumentWindow (String::empty, 
		    Colours::white, 
		    DocumentWindow::allButtons, 
		    true)
{
  GraceApp* app = (GraceApp*)JUCEApplication::getInstance();
  GracePreferences* prefs=app->getPreferences();
  
  if (filename==String::empty)
    {
      if (title==String::empty)
	{
	  filename=T("untitled");
	  if (synt==TextIDs::Sal)
	    filename += T(".sal");
	  else if (synt==TextIDs::Lisp)
	    filename += T(".lisp");
	  else {
	    filename += T(".text");
	    synt=TextIDs::Text;
	  }
	  editfile=TextFile(T("~/") + filename);
	  title=filename;
	}
      else 
	{      // have title
	  editfile=TextFile::nonexistent;
	}
    }
  else
    {
      editfile=TextFile(filename);
      if (title == String::empty)
	title=editfile.getFileName();
    }
  
  setName(title);
  
  switch (synt)
    {
    case TextIDs::Sal :
    case TextIDs::Lisp :
    case TextIDs::Text :
      break;
    default:
      synt=getSyntaxFromFileType( editfile.getFileExtension());
      break;
    }
  
  editor = new EditorComponent((TextID)synt, flags) ;
  setContentComponent(editor);
  
  TextBuffer* buffer=editor->buffer;
  Font font= Font(Font::getDefaultMonospacedFontName(),
		  prefs->getEditorFontSize(),
		  Font::plain);
  buffer->setFont(font);
  buffer->setVisible(true);
  editor->setVisible(true);
  setResizable(true, true); 
  // set buffer to standard 74 column width.  + 10 adds space for
  // scrollers to avoid linewrap when scoller appears :/
  centreWithSize(font.getStringWidth(T("M"))*74+10, 400); 
  commandManager=app->commandManager;
  setWantsKeyboardFocus(false);  
  addKeyListener (commandManager->getKeyMappings());
  setMenuBar(this);
  setApplicationCommandManagerToWatch( commandManager );
  commandManager->registerAllCommandsForTarget(buffer);
  
  // BUG: If setNativeTitleBars is TRUE then closing the window crashes the app
  setUsingNativeTitleBar(prefs->isNativeTitleBars());
  //setUsingNativeTitleBar(false);
  
  // dont show window until very last
  setVisible(true);
  if ( text != String::empty )
    buffer->setText( text );    
  else if ( buffer->testFlag(EditFlags::Load) &&
	    editfile.existsAsFile() )
    {
      buffer->setText( editfile.loadFileAsString() );
      prefs->addRecentlyOpenedFile(editfile);
    }
  if ( !buffer->isEmpty() && buffer->isHiliting() )
    buffer->colorizeAll();  // could this be done in a thread?
  if ( buffer->testFlag(EditFlags::ReadOnly) )
    buffer->setReadOnly(true);
}

EditorWindow::~EditorWindow () {
  //  GracePreferences* p=GracePreferences::getInstance();
  //delete editor;
}

void EditorWindow::closeButtonPressed () {
  if ( ! getTextBuffer()->isChanged() )
    delete this;
  else {
    if ( AlertWindow::showOkCancelBox
	 (AlertWindow::QuestionIcon, T("Close"),
	  T("Save buffer before closing?"),
	  T("  Yes  "), T("  No  "))) {
      if ( saveFile() ) {
	delete this;
      }
    }
    else
      delete this;
  }
}

const StringArray EditorWindow::getMenuBarNames()
{
  const tchar* const textbar [] = 
    {T("File"), T("Edit"), T("View"), T("Windows"), T("Help"), 0};
  const tchar* const codebar [] =
    {T("File"), T("Edit"), T("View"), T("Eval"),
#ifdef SCHEME  
     T("Ports"),
#else
     T("Lisp"),
#endif
     T("Windows"), T("Help"), 0};

  if ( getTextBuffer()->isTextSyntax() )
    return StringArray((const tchar**)textbar);
  else 
    return StringArray((const tchar**)codebar);
}

const PopupMenu EditorWindow::getEvalMenu () {
  PopupMenu menu;
  menu.addCommandItem(commandManager, CommandIDs::EvalExecute);
  menu.addCommandItem(commandManager, CommandIDs::EvalExpand);
  menu.addSeparator();
  menu.addCommandItem(commandManager, CommandIDs::EvalLoadFile);
#ifndef SCHEME
  menu.addCommandItem(commandManager, CommandIDs::EvalCompileFile);
#endif
  menu.addSeparator();
  menu.addCommandItem(commandManager, CommandIDs::EvalShowDirectory);
  menu.addCommandItem(commandManager, CommandIDs::EvalSetDirectory);  
  menu.addSeparator();
  menu.addCommandItem(commandManager, CommandIDs::EvalSymbolHelp);
  return menu;
}

const PopupMenu EditorWindow::getMenuForIndex(int meuindex,
					      const String& menuname)
{
  PopupMenu menu, sub1, sub2;
  GraceApp* app = (GraceApp*)JUCEApplication::getInstance();
  GracePreferences* p=GracePreferences::getInstance();

  if (menuname==T("File")) 
    {
      sub1.addCommandItem(commandManager, 
			  CommandIDs::NewEditor + TextIDs::Sal);
      sub1.addCommandItem(commandManager, 
			  CommandIDs::NewEditor + TextIDs::Lisp);
      sub1.addCommandItem(commandManager, 
			  CommandIDs::NewEditor + TextIDs::Text);
      menu.addSubMenu(T("New"), sub1, true);
      menu.addCommandItem(commandManager, CommandIDs::FileOpen);
      if ( p->areRecentlyOpenedFiles() )
	{
	  p->addRecentlyOpenedItems(&sub2,CommandIDs::FileOpenRecent);
	  sub2.addSeparator();
	  sub2.addItem(CommandIDs::FileClearRecent, T("Clear"));
	  menu.addSubMenu(T("Open Recent"), sub2);
	}
      menu.addSeparator();
      menu.addCommandItem(commandManager, CommandIDs::FileSave);
      menu.addCommandItem(commandManager, CommandIDs::FileSaveAs);
      menu.addCommandItem(commandManager, CommandIDs::FileRevert);
      menu.addSeparator();
      menu.addCommandItem(commandManager, CommandIDs::FileClose);
    }
  else if (menuname==T("Edit"))
    {
      menu.addCommandItem(commandManager, CommandIDs::EditUndo);
      menu.addCommandItem(commandManager, CommandIDs::EditRedo);
      menu.addSeparator();
      menu.addCommandItem(commandManager, CommandIDs::EditCopy);
      menu.addCommandItem(commandManager, CommandIDs::EditCut);
      menu.addCommandItem(commandManager, CommandIDs::EditPaste);
      menu.addCommandItem(commandManager, CommandIDs::EditSelectAll);
      menu.addSeparator();
      menu.addItem(CommandIDs::EditEmacsMode, T("Emacs Mode"), 
		   true, p->isEmacsMode() );    }
  else if (menuname==T("View")) 
    {
      for (int i = 0; i<16; i++)
	sub1.addItem(CommandIDs::ViewFontSize+i,
		     String( fontSizeList[i] ),
		     true, 
		     (getTextBuffer()->getFontSize() == fontSizeList[i])
		     );
      menu.addSubMenu(T("Font Size"), sub1, true);
      menu.addSeparator();
      menu.addItem(CommandIDs::EditHilite,
		   T("Highlighting"), 
		   !getTextBuffer()->isTextSyntax(),
		   getTextBuffer()->isHiliting()
		   );
      menu.addItem(CommandIDs::EditParens,
		   T("Parens Matching"),
		   !getTextBuffer()->isTextSyntax(),
		   getTextBuffer()->isParensMatching()
		   );    
    }
  else if (menuname == T("Eval"))
    menu=getEvalMenu();
#ifdef SCHEME
  else if (menuname == T("Ports"))
    menu=((GraceApp *)GraceApp::getInstance())->
      getConsole()->getPortsMenu();
#endif
  else if (menuname == T("Windows"))
    {
    menu=app->getWindowMenu(false);
    }
  else if (menuname == T("Help"))
    menu=app->getHelpMenu();
  return menu;
}

void EditorWindow::menuItemSelected (int id, int idx)
{
  CommandID cmd = CommandIDs::getCommand(id);
  int data = CommandIDs::getCommandData(id);  
  int type = CommandIDs::getCommandType(id);  
  GraceApp* app = (GraceApp*)JUCEApplication::getInstance();
  GracePreferences* prefs=GracePreferences::getInstance();

  if (type == CommandIDs::Window)
    app->performWindowCommand(id);
  else if (type == CommandIDs::Help)
    app->performHelpCommand(id);
#ifdef SCHEME
  else if (type == CommandIDs::MidiOut)
      app->getMidiOutPort()->performMidiOutCommand(id);
  else if (type == CommandIDs::MidiIn)
      app->getMidiInPort()->performMidiInCommand(id);
  else if (type == CommandIDs::MidiSeq)  
      app->getMidiOutPort()->performMidiSeqCommand(id);
#ifdef PORTCSOUND
  else if (type == CommandIDs::Csound)  
      app->getCsoundPort()->performCsoundCommand(id);
#endif 
#ifdef FOMUS
  else if (type == CommandIDs::Fomus)
      app->getFomusPort()->performFomusCommand(id);
#endif 
  else if (type== CommandIDs::Scheduler)
    {
      app->schemeProcess->performSchedulerCommand(id);
    }
#else
  else if (type == CommandIDs::CommonLisp)
    app->getConsole()->lisp->performLispCommand(id);
#endif
  else
    switch (cmd)
      {

      case CommandIDs::FileOpenRecent :
	{
	  File f=prefs->getRecentlyOpenedFile(data);
	  new EditorWindow(0, EditFlags::Load, f.getFullPathName());
	}
	break;
	
      case CommandIDs::FileClearRecent :
	prefs->clearRecentlyOpenedFiles();
	break;
	
      case CommandIDs::ViewFontSize :
	getTextBuffer()->setFontSize(fontSizeList[data]);
	getTextBuffer()->colorizeAll();
	break;
	
      case CommandIDs::EditHilite :
	getTextBuffer()->toggleHiliting();      
	break;
	
      case CommandIDs::EditParens :
	getTextBuffer()->toggleParensMatching();
	break;
	
      case CommandIDs::EditEmacsMode :
	prefs->setEmacsMode(!prefs->isEmacsMode());
	break;
	
      default:
	break;
	
      }
}

void EditorWindow::newFile(TextID mode) {
  new EditorWindow(mode) ;
}

void EditorWindow::openFile() {
  File dir;
  if ( editfile.existsAsFile() )
    dir = editfile.getParentDirectory();
  else
    dir = File::getCurrentWorkingDirectory();

  FileChooser choose (T("Open File"), dir, String::empty, true);
  if ( choose.browseForFileToOpen() ) {
    TextFile f = (TextFile)choose.getResult();
    new EditorWindow(0, EditFlags::Load, f.getFullPathName());
  }
}

void EditorWindow::closeFile() {
  closeButtonPressed();
}

bool EditorWindow::saveFile() {
  TextBuffer* buff=getTextBuffer();
  if ( buff->isChanged() )
    if ( editfile.existsAsFile() ) {
      editfile.replaceWithText( buff->getText() ) ;
      buff->setChanged(false);
      return true;
    }
    else {
      return saveFileAs(editfile);
    }
  return false;
}

bool EditorWindow::saveFileAs(File defaultfile) {
  TextBuffer* buff=getTextBuffer();
  File dir;
  if (defaultfile==File::nonexistent)
    if ( editfile.existsAsFile() )
      defaultfile = editfile.getParentDirectory();
    else
      defaultfile = File::getCurrentWorkingDirectory();
  FileChooser choose (T("Save File As"), defaultfile, T("*.*"), true);
  if ( choose.browseForFileToSave(true) ) {
    TextFile f = choose.getResult();
    f.replaceWithText( buff->getText() );
    editfile=TextFile(f);
    buff->setChanged(false);
    buff->setFlagOff(EditFlags::NoSave);
    setName( editfile.getFileName() );
    return true;
  }
  else
    return false;
}

bool EditorWindow::revertFile() {
  TextBuffer* buff=getTextBuffer();
  bool doit=false;
  if ( buff->isChanged() && editfile.existsAsFile() ) 
    doit=AlertWindow::showOkCancelBox
      (AlertWindow::QuestionIcon, T("Revert File"),
       T("Really revert to last saved version of file?"),
       T("   OK   "), T("Cancel"));
  if ( doit ) {
    buff->setText( editfile.loadFileAsString() ) ;
    buff->setChanged(false);
    if ( buff->isHiliting() )
      buff->colorizeAll();
    return true;
  }
  else
    return false;
}

void EditorWindow::loadFile() 
{
  File dir;
  if ( editfile.existsAsFile() )
    dir = editfile.getParentDirectory();
  else
    dir = File::getCurrentWorkingDirectory();
  
  FileChooser choose (T("Load File"), dir, String::empty, true);
  if ( choose.browseForFileToOpen() )
    {
      File f = choose.getResult();
      if ( f.hasFileExtension( T(".sal") ) )
	{
#ifdef SCHEME
	  SalSyntax::getInstance()->loadFile( f.getFullPathName() );
#else
	  ((GraceApp *)GraceApp::getInstance())->getConsole()->
	    consoleEval( T("load \"") + f.getFullPathName() + T("\""),
			 true, false );      
#endif      
	}
      else
	{
	  String path=f.getFullPathName();
#ifdef WINDOWS
	  path=path.replace(String("\\"),String("/"));
#endif

#ifdef SCHEME
	  ((GraceApp *)GraceApp::getInstance())->getConsole()->
	    consoleEval( T("(load ") + path.quoted() + T(")"), 
			 false, false );
#else
	  ((GraceApp *)GraceApp::getInstance())->getConsole()->
	    consoleEval( T("(load \"") + path + T("\")"), 
			 false, false );
#endif
	}
    }
}

void EditorWindow::compileFile() {
  File dir;
  if ( editfile.existsAsFile() )
    dir=editfile.getParentDirectory();
  else
    dir=File::getCurrentWorkingDirectory();

  FileChooser choose (T("Compile File"), dir, String::empty, true);
  if ( choose.browseForFileToOpen() ) {
    File f = choose.getResult();
#ifndef SCHEME
    ((GraceApp *)GraceApp::getInstance())->getConsole()->
      consoleEval( T("(compile-file \"") + f.getFullPathName() + T("\")"), 
		   false, false );
#endif
  }
}

void EditorWindow::showDirectory() {
  ((GraceApp *)GraceApp::getInstance())->getConsole()->
    printMessage( T("Current directory: ") + 
		  File::getCurrentWorkingDirectory().getFullPathName().quoted() +
		  T("\n") );
}

void EditorWindow::setDirectory() {
  FileChooser choose (T("Change Directory"), File::getCurrentWorkingDirectory(), String::empty, true);
  if ( choose.browseForDirectory() ) {
    choose.getResult().setAsCurrentWorkingDirectory();
#ifndef SCHEME
    ((GraceApp *)GraceApp::getInstance())->getConsole()->
      consoleEval( T("(cd \"") + choose.getResult().getFullPathName() + 
		   T("\")"), false, false );
#else
    showDirectory();
#endif
  }
}

void EditorWindow::setPackage() {
}
