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
      editfile=File(filename);
    }
    else
      editfile=File::nonexistent;
  else
    editfile=File(filename);

  if (title==String::empty)
    setName( filename );
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
  setMenuBar(this, commandManager);
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

const StringArray EditorWindow::getMenuBarNames(MenuBarComponent* mbar) {
  const tchar* const menuNames[] = { T("File"), T("Edit"),  T("View"), 
				     T("Help"),0 };
  return StringArray ((const tchar**) menuNames);
}

const PopupMenu EditorWindow::getMenuForIndex (MenuBarComponent* menuBar, 
					       int menuIndex,
					       const String& menuName) {
  PopupMenu menu, sub1, sub2;
  //FontList* fontList = FontList::getInstance();
  
  if (menuIndex == 0) {
    sub1.addCommandItem( commandManager, TextBuffer::cmdNewSal );
    sub1.addCommandItem( commandManager, TextBuffer::cmdNewLisp );
    sub1.addCommandItem( commandManager, TextBuffer::cmdNewText );
    menu.addSubMenu(T("New"), sub1, true);
    menu.addCommandItem( commandManager, TextBuffer::cmdOpen);
    menu.addSeparator();
    menu.addCommandItem( commandManager, TextBuffer::cmdSave);
    menu.addCommandItem( commandManager, TextBuffer::cmdSaveAs);
    menu.addCommandItem( commandManager, TextBuffer::cmdRevert);
    menu.addSeparator();
    menu.addCommandItem( commandManager, TextBuffer::cmdClose);
  }
  else if (menuIndex == 1) {
      menu.addCommandItem( commandManager, TextBuffer::cmdUndo);
      menu.addCommandItem( commandManager, TextBuffer::cmdRedo);
      menu.addSeparator();
      menu.addCommandItem( commandManager, TextBuffer::cmdCopy);
      menu.addCommandItem( commandManager, TextBuffer::cmdCut);
      menu.addCommandItem( commandManager, TextBuffer::cmdPaste);
      menu.addCommandItem( commandManager, TextBuffer::cmdSelectAll);
    }
  else if (menuIndex == 2) {
      //for (int i = 0;i<fontList->fontNames.size();i++) {
      //sub1.addItem(i+1, fontList->fontNames[i], true, false);
      //}
      for (int i = 0;i<16;i++) {
	sub2.addItem(TextBuffer::cmdViewFontSize+i,
		     String( fontSizeList[i] ),
		     true, 
		     (getTextBuffer()->getFontSize() == fontSizeList[i])
		     );
      }
      //menu.addSubMenu(T("Font"), fontsMenu, false);
      menu.addSubMenu(T("Font Size"), sub2, true);
      menu.addSeparator();
      menu.addItem(TextBuffer::cmdToggleHiliting,
		   T("Highlighting"), 
		   (getTextBuffer()->getBufferSyntax() != syntaxText),
		   getTextBuffer()->isHiliting()
		   );
      menu.addItem(TextBuffer::cmdToggleParens,
		   T("Parens Matching"),
		   (getTextBuffer()->getBufferSyntax() != syntaxText),
		   getTextBuffer()->isParensMatching()
		   );
  }
  else if (menuIndex == 3) {
    menu.addItem(TextBuffer::cmdHelpEditor+0, T("Editor Help"));
    sub1.addItem(TextBuffer::cmdHelpEditor+1, T("Hello World"));
    sub1.addItem(TextBuffer::cmdHelpEditor+2, T("Expressions"));
    sub1.addItem(TextBuffer::cmdHelpEditor+3, T("Function Calls"));
    sub1.addItem(TextBuffer::cmdHelpEditor+4, T("Making Sound"));
    sub1.addItem(TextBuffer::cmdHelpEditor+5, T("Variables"));
    sub1.addItem(TextBuffer::cmdHelpEditor+6, T("Functions"));
    sub1.addItem(TextBuffer::cmdHelpEditor+7, T("Iteration"));
    menu.addSubMenu(T("SAL Tutorials"), sub1, true);
    menu.addSeparator();
    menu.addItem(TextBuffer::cmdHelpEditor+8, T("CM Dictionary"));
    menu.addItem(TextBuffer::cmdHelpEditor+9, T("CM Homepage"));
    menu.addItem(TextBuffer::cmdHelpEditor+10, T("Juce Homepage"));
  }
  return menu;
}

void EditorWindow::menuItemSelected (MenuBarComponent* menuBar,
				     int id, int idx) {
  int arg = id & 0x0000007F;
  int cmd = id & 0xFFFFFF80;
  switch (cmd) {

  case TextBuffer::cmdViewFontSize :
    getTextBuffer()->setFontSize(fontSizeList[arg]);
    getTextBuffer()->colorizeAll();
    break;
  case TextBuffer::cmdToggleHiliting :
    getTextBuffer()->toggleHiliting();      
    break;
  case TextBuffer::cmdToggleParens :
    getTextBuffer()->toggleParensMatching();
    break;
  case TextBuffer::cmdHelpEditor :
    showEditorHelp(arg);
    break;
  default:
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
    File f = choose.getResult();
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
    File f = choose.getResult();
    f.replaceWithText( buff->getText() );
    editfile=File(f);
    buff->setChanged(false);
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

void EditorWindow::showEditorHelp(int arg) {
  URL u;

  switch(arg) {
  case 0:
    new EditorWindow(syntaxText, TextBuffer::readonly, String::empty,
		     T("Editor Help"), getEditorHelp());
    break;
  case 1:
    break;
  case 2:
    break;
  case 3:
    break;
  case 4:
    break;
  case 5:
    break;
  case 6:
    break;
  case 7:
    break;
  case 8:
    u=URL(T("http://commonmusic.sourceforge.net/doc/dict/index.html"));
    u.launchInDefaultBrowser();
    break;
  case 9:
    u=URL(T("http://commonmusic.sourceforge.net/doc/cm.html"));
    u.launchInDefaultBrowser();
    break;  
  case 10:
    u=URL(T("http://www.rawmaterialsoftware.com/juce"));
    u.launchInDefaultBrowser();
    break;
  default:
    break;
  }
}
