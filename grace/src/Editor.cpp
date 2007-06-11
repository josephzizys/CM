#include "Editor.h"
#include "FontList.h"
#include "Grace.h"
/*
 * global filetype -> syntax mapping. new mappings can be added via
 * addSyntaxFileType
 */

struct {
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

EditorWindow::EditorWindow (String filename, bool load, int synt)
  : DocumentWindow (String::empty , Colours::white, 
		    DocumentWindow::allButtons, true ) {
  
  static int unt=0;
  if (filename==String::empty) {
    filename=T("untitled");
    //if (unt>0) filename += unt;
    if (synt==syntaxSal)
      filename += T(".sal");
    else if (synt==syntaxLisp)
      filename += T(".lisp");
    else {
      filename += T(".text");
      synt=syntaxText;
    }
    //unt++;
  }

  editfile=File(filename);

  String type = editfile.getFileExtension();
  String path = editfile.getFullPathName();
  syntaxID mode;
  TextBuffer * buffer;

  switch (synt) {
  case syntaxSal :
  case syntaxLisp :
  case syntaxText :
    mode=(syntaxID)synt;
    break;
  default:
    mode = getSyntaxFromFileType(type);
    break;
  }

  setName( editfile.getFileName() );
  setWantsKeyboardFocus(false);
  editor = new EditorComponent( path, mode) ;
  buffer=editor->buffer;
  buffer->setFont( Font(Font::getDefaultMonospacedFontName(), 17.0f, Font::plain ) );

  if ( load && editfile.existsAsFile() ) {
    buffer->setText( editfile.loadFileAsString() );
  }

  buffer->setVisible(true);  // dont show window until subs are ready.
  editor->setVisible(true);
  setContentComponent(editor);
  setResizable(true, true); 
  // set to standard 74 col width in current font.
  Font f = editor->buffer->getFont();
  int w = f.getStringWidth(T("**************************************************************************"));
  centreWithSize (w+40, 400);
  
  commandManager = ((GraceApp*)JUCEApplication::getInstance())->commandManager;
  
  addKeyListener (commandManager->getKeyMappings());
  setMenuBar(this, commandManager);
  commandManager->registerAllCommandsForTarget(buffer);
  // dont show window until very last
  setVisible(true);
  
  if ( !buffer->isEmpty() && buffer->isHiliting() )
    buffer->colorizeAll();  // could this be done in a thread?
}

EditorWindow::~EditorWindow () {
  editor->~EditorComponent();
}

void EditorWindow::closeButtonPressed () {
  if (AlertWindow::showOkCancelBox
      (AlertWindow::QuestionIcon, T("Close"),
       T("Really close the window? Unsaved work will be lost."),
       T("OK"), T("Cancel"))
      )
    this->~EditorWindow();
    }

/*
 * File menu commands
 */



const StringArray EditorWindow::getMenuBarNames (MenuBarComponent* menuBar) 
{
  const tchar* const menuNames[] = { T("File"), T("Edit"), T("Format"), 0 };
  return StringArray ((const tchar**) menuNames);
    }


const PopupMenu EditorWindow::getMenuForIndex (MenuBarComponent* menuBar, int menuIndex, const String& menuName) 
{
  PopupMenu menu;
  FontList* fontList = FontList::getInstance();
  
  if (menuIndex == 0) 
    {
      PopupMenu bufs;
      bufs.addCommandItem( commandManager, TextBuffer::cmdNewSal );
      bufs.addCommandItem( commandManager, TextBuffer::cmdNewLisp );
      bufs.addCommandItem( commandManager, TextBuffer::cmdNewText );
      menu.addSubMenu(T("New"), bufs, true);
      menu.addSeparator();
      menu.addCommandItem( commandManager, TextBuffer::cmdOpen);
      menu.addSeparator();
      //menu.addCommandItem( commandManager, TextBuffer::cmdClose);
      menu.addCommandItem( commandManager, TextBuffer::cmdSave);
      menu.addCommandItem( commandManager, TextBuffer::cmdSaveAs);
    }
  
  else if (menuIndex == 1) 
    {
      menu.addCommandItem ( commandManager, TextBuffer::cmdUndo);
      menu.addCommandItem ( commandManager, TextBuffer::cmdRedo);
      menu.addSeparator();
      menu.addCommandItem ( commandManager, TextBuffer::cmdCopy);
      menu.addCommandItem ( commandManager, TextBuffer::cmdCut);
      menu.addCommandItem ( commandManager, TextBuffer::cmdPaste);
      menu.addCommandItem ( commandManager, TextBuffer::cmdSelectAll);

    }
  else if (menuIndex == 2) 
    {
      PopupMenu fontsMenu;
      PopupMenu fontsSizeMenu;

      for(int i = 0;i<fontList->fontNames.size();i++) 
	{
	  fontsMenu.addItem(i+1, fontList->fontNames[i], true, false);
	}
      
      for(int i = 0;i<8;i++) 
	{
	  fontsSizeMenu.addItem(6000+i, String( fontSizeList[i] ), true, false);
	}
      
      menu.addSubMenu(T("Font"), fontsMenu, true);
      menu.addSubMenu(T("Font Size"), fontsSizeMenu, true);
      
    }
  
  return menu;
}


void EditorWindow::menuItemSelected (MenuBarComponent* menuBar,
				     int menuItemID,
				     int topLevelMenuIndex) 
{

  switch (topLevelMenuIndex) 
    {
    case 2:
      if(menuItemID < 5000)
	{
	  getTextBuffer()->setFontType(FontList::getInstance()->fontNames[menuItemID-1]);
	} else if (menuItemID >= 6000)
	{
	  getTextBuffer()->setFontSize(fontSizeList[menuItemID-6000]);
	}
      break;
    default:
      break;
    }
}



