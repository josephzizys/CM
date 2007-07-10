/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

#include "Editor.h"
#include "FontList.h"
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
    
    if (out->areAnyErrors())
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



struct {
  // global filetype->syntax mapping. new mappings can be added via
  // addSyntaxFileType
  String name;
  syntaxID type;
} syntaxFileTypes [32] =  {{T(".lisp"), syntaxLisp},
			   {T(".lsp"), syntaxLisp},
			   {T(".cl"), syntaxLisp},
			   {T(".scm"), syntaxLisp},
			   {T(".cm"), syntaxLisp},
			   {T(".clm"), syntaxLisp},
			   {T(".cmn"), syntaxLisp},
			   {T(".ins"), syntaxLisp},
			   {T(".fms"), syntaxLisp},
			   {T(".asd"), syntaxLisp},
			   {T(".sal"), syntaxSal},
			   {T(".text"), syntaxText},
			   {T(".txt"), syntaxText},
			   {T(""), syntaxNone}  }; 

syntaxID getSyntaxFromFileType(String filename) {
  String ext = filename.fromLastOccurrenceOf(T("."), true, false);
  if ( ext == String::empty ) return syntaxText;
  for (int i=0; i<32; i++)
    if ( syntaxFileTypes[i].name == String::empty )
      return syntaxText;
    else if ( ext == syntaxFileTypes[i].name ) 
      return syntaxFileTypes[i].type;
  return syntaxText; 
}

bool addSyntaxFileType(String name, syntaxID synt) {
  int i;
  for (i=0; i<32; i++)
    if ( syntaxFileTypes[i].name == T("") )
      break;
  if (i==32) return false;
  syntaxFileTypes[i].name=name;
  syntaxFileTypes[i].type=synt;
  if (i<31) {
    syntaxFileTypes[i].name=T("");
    syntaxFileTypes[i].type=syntaxNone;
  }
  return true;
}

EditorWindow::EditorWindow (int synt, int flags, String filename,
			    String title, String text)
  : DocumentWindow (String::empty , Colours::white, 
		    DocumentWindow::allButtons, true ) {

  if (filename==String::empty) 
    if (title==String::empty) {
      filename=T("untitled");
      if (synt==syntaxSal)
	filename += T(".sal");
      else if (synt==syntaxLisp)
	filename += T(".lisp");
      else {
	filename += T(".text");
	synt=syntaxText;
      }
      editfile=TextFile(filename);
    }
    else
      editfile=TextFile::nonexistent;
    else 
      editfile=TextFile(filename);

  if (title==String::empty)
    setName( TextFile(filename).getFileName() );
  else 
    setName(title);

  switch (synt) {
  case syntaxSal :
  case syntaxLisp :
  case syntaxText :
    break;
  default:
    synt=getSyntaxFromFileType( editfile.getFileExtension());
    break;
  }

  editor = new EditorComponent((syntaxID)synt, flags) ;
  setContentComponent(editor);
  TextBuffer* buffer=editor->buffer;
  Font font= Font(Font::getDefaultMonospacedFontName(),
		  17.0f, Font::plain);
  buffer->setFont(font);
  buffer->setVisible(true);
  editor->setVisible(true);
  setResizable(true, true); 
  // set buffer to standard 74 column width.  + 10 adds space for
  // scrollers to avoid linewrap when scoller appears :/
  centreWithSize(font.getStringWidth(T("M"))*74+10, 400); 
  commandManager=((GraceApp*)
		  JUCEApplication::getInstance())->commandManager;
  setWantsKeyboardFocus(false);  
  addKeyListener (commandManager->getKeyMappings());
  setMenuBar(this);
  setApplicationCommandManagerToWatch( commandManager );
  commandManager->registerAllCommandsForTarget(buffer);
  // dont show window until very last
  setVisible(true);
  if ( text != String::empty )
    buffer->setText( text );    
  else if ( buffer->testFlag(TextBuffer::load) &&
	    editfile.existsAsFile() )
    buffer->setText( editfile.loadFileAsString() );
  if ( !buffer->isEmpty() && buffer->isHiliting() )
    buffer->colorizeAll();  // could this be done in a thread?
  if ( buffer->testFlag(TextBuffer::readonly) )
    buffer->setReadOnly(true);
}

EditorWindow::~EditorWindow () {
  editor->~EditorComponent();
}

void EditorWindow::closeButtonPressed () {
  if ( ! getTextBuffer()->isChanged() ||
       (AlertWindow::showOkCancelBox
	(AlertWindow::QuestionIcon, T("Close"),
	 T("Really close the window? Unsaved work will be lost."),
	 T("   OK   "), T("Cancel"))
	) )
    this->~EditorWindow();
    }

const StringArray EditorWindow::getMenuBarNames() {
  const tchar* const textbar [] = { T("File"), T("Edit"),  T("View"), 
				    T("Options"), T("Text"), T("Windows"), T("Help"), 0};
  const tchar* const lispbar [] = { T("File"), T("Edit"),  T("View"), 
				    T("Options"), T("Lisp"), T("Windows"), T("Help"), 0};
  const tchar* const salbar [] = { T("File"), T("Edit"),  T("View"), 
				    T("Options"), T("SAL"), T("Windows"), T("Help"), 0};
  if ( getTextBuffer()->isLispSyntax() )
    return StringArray((const tchar**)lispbar);
  else if ( getTextBuffer()->isSalSyntax() )
    return StringArray((const tchar**)salbar);    
  else
    return StringArray((const tchar**)textbar);    
}

const PopupMenu EditorWindow::getLispMenu () {
  PopupMenu menu;
  menu.addCommandItem( commandManager, TextBuffer::cmdLispEval);
  menu.addSeparator();
  menu.addCommandItem( commandManager, TextBuffer::cmdLispSetPackage);
  return menu;
}

const PopupMenu EditorWindow::getSalMenu () {
  PopupMenu menu, sub1, sub2;
  menu.addCommandItem( commandManager, TextBuffer::cmdSalEval);
  return menu;
}

const PopupMenu EditorWindow::getHelpMenu () {
  PopupMenu menu, sub1;
  if (getTextBuffer()->isSalSyntax()) {
    menu.addCommandItem( commandManager, TextBuffer::cmdSymbolHelp);
    menu.addSeparator();
  }
  addCommonHelpItems(&menu, winEditor);
  return menu;
}

const PopupMenu EditorWindow::getMenuForIndex ( int menuIndex,
					       const String& menuName) {
  PopupMenu menu, sub1, sub2;
  
  if (menuIndex == 0) {
    // File menu
    sub1.addCommandItem( commandManager, TextBuffer::cmdFileNewSal );
    sub1.addCommandItem( commandManager, TextBuffer::cmdFileNewLisp );
    sub1.addCommandItem( commandManager, TextBuffer::cmdFileNewText );
    menu.addSubMenu(T("New"), sub1, true);
    menu.addCommandItem( commandManager, TextBuffer::cmdFileOpen);
    menu.addSeparator();
    menu.addCommandItem( commandManager, TextBuffer::cmdFileSave);
    menu.addCommandItem( commandManager, TextBuffer::cmdFileSaveAs);
    menu.addCommandItem( commandManager, TextBuffer::cmdFileRevert);
    menu.addSeparator();
    menu.addCommandItem( commandManager, TextBuffer::cmdFileClose);
  }
  else if (menuIndex == 1) {
    // Edit menu
    menu.addCommandItem( commandManager, TextBuffer::cmdEditUndo);
    menu.addCommandItem( commandManager, TextBuffer::cmdEditRedo);
    menu.addSeparator();
    menu.addCommandItem( commandManager, TextBuffer::cmdEditCopy);
    menu.addCommandItem( commandManager, TextBuffer::cmdEditCut);
    menu.addCommandItem( commandManager, TextBuffer::cmdEditPaste);
    menu.addCommandItem( commandManager, TextBuffer::cmdEditSelectAll);
    menu.addSeparator();
    menu.addCommandItem( commandManager, TextBuffer::cmdEditImport);
  }
  else if (menuIndex == 2) {
    // View menu
    for (int i = 0;i<16;i++)
      sub1.addItem(TextBuffer::cmdViewFontSize+i,
		   String( fontSizeList[i] ),
		   true, 
		   (getTextBuffer()->getFontSize() == fontSizeList[i])
		   );
    menu.addSubMenu(T("Font Size"), sub1, true);
    menu.addSeparator();
    menu.addSubMenu(T("Themes"), sub2, false);
  }
  else if (menuIndex == 3) {
    // Options menu
    menu.addItem(TextBuffer::cmdOptionsHiliting,
		 T("Highlighting"), 
		 !getTextBuffer()->isTextSyntax(),
		 getTextBuffer()->isHiliting()
		 );
    menu.addItem(TextBuffer::cmdOptionsParens,
		 T("Parens Matching"),
		 !getTextBuffer()->isTextSyntax(),
		 getTextBuffer()->isParensMatching()
		 );
    menu.addSeparator();
    menu.addItem(TextBuffer::cmdOptionsEmacsMode,
		 T("Emacs Mode"), true,
		 getTextBuffer()->isEmacsMode()
		 );
  }
  else if (menuIndex == 4) {
    if (getTextBuffer()->isSalSyntax() )
      menu=getSalMenu();
    if (getTextBuffer()->isLispSyntax() )    
      menu=getSalMenu();
    // Oops! Text menu  is currently empty!
  }
  else if (menuIndex == 5) 
    addCommonWindowItems(&menu, winEditor);
  else if (menuIndex == 6)
    addCommonHelpItems(&menu, winEditor);
  return menu;
}

void EditorWindow::menuItemSelected (int id, int idx) {
  int arg = id & 0x0000007F;
  int cmd = id & 0xFFFFFF80;
  switch (cmd) {
  case TextBuffer::cmdViewFontSize :
    getTextBuffer()->setFontSize(fontSizeList[arg]);
    getTextBuffer()->colorizeAll();
    break;
  case TextBuffer::cmdOptionsHiliting :
    getTextBuffer()->toggleHiliting();      
    break;
  case TextBuffer::cmdOptionsParens :
    getTextBuffer()->toggleParensMatching();
    break;
  case TextBuffer::cmdOptionsEmacsMode :
    getTextBuffer()->toggleEmacsMode();
    break;
  default:
    if (idx == 5)
      commonWindowItemSelected(cmd, arg);      
    if (idx == 6)
      commonHelpItemSelected(cmd, arg);
    break;
  }
}

void EditorWindow::newFile(syntaxID mode) {
  new EditorWindow(mode) ;
}

void EditorWindow::openFile() {
  File dir;
  if ( editfile.existsAsFile() )
    dir = editfile.getParentDirectory();
  else
    dir = File::getSpecialLocation(File::userHomeDirectory);
  FileChooser choose (T("Open File"), dir, String::empty, true);
  if ( choose.browseForFileToOpen() ) {
    TextFile f = (TextFile)choose.getResult();
    new EditorWindow(0, TextBuffer::load, f.getFullPathName());
  }
}

void EditorWindow::closeFile() {
  getCloseButton()->triggerClick();
}

void EditorWindow::saveFile() {
  TextBuffer* buff=getTextBuffer();
  if ( buff->isChanged() ) {
    editfile.replaceWithText( buff->getText() ) ;
    buff->setChanged(false);
  }
}

void EditorWindow::saveFileAs() {
  TextBuffer* buff=getTextBuffer();
  File dir;

  if ( editfile.existsAsFile() )
    dir = editfile.getParentDirectory();
  else
    dir = File::getSpecialLocation(File::userHomeDirectory);
  FileChooser choose (String::empty, dir, String::empty, true);
  if ( choose.browseForFileToSave(true) ) {
    TextFile f = choose.getResult();
    f.replaceWithText( buff->getText() );
    editfile=TextFile(f);
    buff->setChanged(false);
    buff->setFlagOff(TextBuffer::nosave);
    setName( editfile.getFileName() );
  }
}

void EditorWindow::revertFile() {
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
  }
}

