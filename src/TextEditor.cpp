/*=======================================================================*
  Copyright (c) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify
  it under the terms of the Lisp Lesser Gnu Public License. The text
  of this agreement is available at http://www.cliki.net/LLGPL
 *=======================================================================*/

#include "Enumerations.h"
#include "TextEditor.h"
#include "Preferences.h"
#include "Commands.h"
#include "Console.h"
#include "Syntax.h"
#include "Help.h"
#include <iostream>

/*=======================================================================*
                             TextEditorWindow
 *=======================================================================*/

TextEditorWindow::TextEditorWindow (File file, String text, int synt,
				    String title)
  : DocumentWindow (String::empty, Colours::white, 
		    DocumentWindow::allButtons, true)
{
  Preferences* prefs=Preferences::getInstance();
  setMenuBar(this);
  int size=0;
  if (file.existsAsFile())
    {
      String ext=file.getFileExtension();
      String lsp=T(".lisp.lsp.scm.cm.clm.cmn.ins.fms");
      String sal=T(".sal");
      if (synt==TextIDs::Empty)
	if (sal.contains(ext))
	  synt=TextIDs::Sal;
	else if (lsp.contains(ext))
	  synt=TextIDs::Lisp;
	else
	  synt=TextIDs::Text; 
      size=file.getSize();
      text=file.loadFileAsString();
    }
  else
    {
      file=File::nonexistent;
      size=text.length();
    }
  if (synt==TextIDs::Empty)
    synt=prefs->getIntProp(T("EditorSyntax"), TextIDs::Lisp);
  buffer=new TextBuffer(synt);
  setContentComponent(buffer);
  setApplicationCommandManagerToWatch(buffer->manager);
  setResizable(true, true); 
  // set buffer to standard 74 column width.  + 10 adds space for
  // scrollers to avoid linewrap when scoller appears :/
  centreWithSize(buffer->getFont().getStringWidth(T("M"))*74+10, 400); 
  setUsingNativeTitleBar(true);
  setDropShadowEnabled(true);
  setWantsKeyboardFocus(false);  // Buffer has it.
  buffer->setFile(file);
  buffer->setText(text);
  if (title.isEmpty())
    buffer->updateWindowTitle();
  else
    setName(title);

  // flag may have been set by loading editor.
  buffer->clearFlag(EditFlags::NeedsSave);
  // goddam Juce Text coloring!
  if (size>20000)
    {
      Console::getInstance()->printWarning(T("Cowardly refusing to colorize large buffer for ") + getName().quoted() + T(".\n"));
      buffer->setFlag(EditFlags::HiliteOff);
    }
  setVisible(true);
  buffer->colorizeAll();
}

TextEditorWindow::~TextEditorWindow ()
{
}

void TextEditorWindow::closeButtonPressed ()
{
  if (!buffer->testFlag(EditFlags::NeedsSave))
    {
      delete this;
      return;
    }
  int x=AlertWindow::showYesNoCancelBox(AlertWindow::QuestionIcon,
					T("Close"),
					T("Save changes before closing?"),
					T("Save"),
					T("Don't Save"),
					T("Cancel")
					);
  if (x==0)
    return;
  if (x==2 || buffer->saveFile())
    delete this;
}

/*=======================================================================*
                             TextBuffer
 *=======================================================================*/

TextBuffer::TextBuffer(int texttype)
  : file (File::nonexistent),
    flags (0),
    prev (0),
    thisid (0),
    matchpos (-1)
{
  // set syntax right away since commands manager needs this
  // information for adding commands
  setSyntax(texttype);
  Preferences* prefs=Preferences::getInstance();
  manager=new ApplicationCommandManager();
  setFont(Font(Font::getDefaultMonospacedFontName(),
	       prefs->getIntProp(T("EditorFontSize"), 17),
	       Font::plain));
  if (prefs->getBoolProp("EditorEmacsMode", false))
    setFlag(EditFlags::EmacsMode);
  addKeyListener(manager->getKeyMappings());
  addKeyListener(CommandManager::getInstance()->getKeyMappings());
  manager->registerAllCommandsForTarget(this);
  setWantsKeyboardFocus(true);
  setMultiLine(true);
  setReturnKeyStartsNewLine(true);
  setCaretPosition(0);
  setVisible(true);
  // add callback for registering changes.
  //addListener(&listener); 
}

TextBuffer::~TextBuffer()
{
  delete manager;
}

/*=======================================================================*
                            File Menu Support
 *=======================================================================*/


bool TextBuffer::saveFile()
{
  if (testFlag(EditFlags::NeedsSave))
    if (file.existsAsFile())
      {
	file.replaceWithText(getText());
	clearFlag(EditFlags::NeedsSave);
	return true;
      }
    else
      return saveFileAs(file);
  return false;
}

bool TextBuffer::saveFileAs(File defaultfile)
{
  if (defaultfile==File::nonexistent)
    if (file.existsAsFile())
      defaultfile=file.getParentDirectory();
    else
      defaultfile=File::getCurrentWorkingDirectory();
  FileChooser choose (T("Save File As"), defaultfile, T("*.*"), true);
  if (choose.browseForFileToSave(true))
    {
      File sav=choose.getResult();
      sav.replaceWithText(getText());
      file=sav;
      clearFlag(EditFlags::NeedsSave);
      updateWindowTitle();
      return true;
    }
  else
    return false;
}

bool TextBuffer::revertFile()
{
  bool doit=false;
  if (testFlag(EditFlags::NeedsSave) && file.existsAsFile()) 
    doit=AlertWindow::showOkCancelBox(AlertWindow::QuestionIcon,
				      T("Revert File"),
				      T("Revert to last saved version?"),
				      T("Revert"),
				      T("Don't Revert"));
  if (doit)
    {
      setText(file.loadFileAsString());
      clearFlag(EditFlags::NeedsSave);
      colorizeAll();
      return true;
    }
  else
    return false;
}

/** 
void TextBuffer::showDirectory() 
{
  Console::getInstance()->
    printOutput(T("Current directory: ") + 
		File::getCurrentWorkingDirectory().
		getFullPathName().quoted() +
		T("\n"));
}

void TextBuffer::setDirectory() 
{
  FileChooser choose (T("Change Directory"),
		      File::getCurrentWorkingDirectory(),
		      String::empty,
		      true);
  if (choose.browseForDirectory())
    {
      choose.getResult().setAsCurrentWorkingDirectory();
      showDirectory();
    }
}
**/

void TextBuffer::loadFile()
{
  File dir;
  if (file.existsAsFile())
    dir=file.getParentDirectory();
  else
    dir=File::getCurrentWorkingDirectory();
  FileChooser choose (T("Load File"), dir, String::empty, true);
  if (!choose.browseForFileToOpen())
    return;
  File load=choose.getResult();
  if (load.hasFileExtension(T(".sal")))
    SalSyntax::getInstance()->eval(load.loadFileAsString());
  else
    LispSyntax::getInstance()->eval(T("(load ") +
				    load.getFullPathName().quoted() +
				    T(")"));
}

void TextBuffer::updateWindowTitle()
{
  String title;
  if (file==File::nonexistent)
    {
      title=T("Untitled");
      title << T(" (") << TextIDs::toString(textid) << T(")");
    }
  else
    title = file.getFileName();
  getTopLevelComponent()->setName(title);
}

/*=======================================================================*
                            Edit Menu Support
 *=======================================================================*/

void TextBuffer::selectAll() 
{
  setHighlightedRegion(0,BUFMAX);
}

void TextBuffer::paste()
{
  String clip=SystemClipboard::getTextFromClipboard();
  if (clip.containsChar('\r'))
    {
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
  setFlag(EditFlags::NeedsSave);
}

void TextBuffer::cut()
{
  if (getHighlightedRegionLength()>0)
    {
      copy();
      keyPressed(KeyPress(KeyPress::deleteKey));
    }
  setFlag(EditFlags::NeedsSave);
}

/*=======================================================================*
                            Options Menu Support
 *=======================================================================*/

int TextBuffer::getFontSize()
{
  return (int)getFont().getHeight();
}

void TextBuffer::setFontSize(int size)
{
  Font font=getFont();
  font.setHeight((float)size);
  applyFontToAllText(font);
  colorizeAll();
}

void TextBuffer::setSyntax(int synt)
{
  textid=synt;
  switch (textid)
    {
    case TextIDs::Lisp:
      syntax=LispSyntax::getInstance();
      break;
    case TextIDs::Sal:
      syntax=SalSyntax::getInstance();
      break;
    default:
      syntax=TextSyntax::getInstance();      
      break;
    }
}

/*=======================================================================*
                                  KeyPresses 
 *=======================================================================*/

// this method shouldnt be necessary but a juce change listener bug
// stops the Return callback from happening.  i will try
// implementing these as commands in the TextBuffer command table
// but for now im just taking the old code...

bool TextBuffer::keyPressed (const KeyPress& key)
{

  //std::cout << "keyPressed: " << key.getTextDescription().toUTF8() << T("\n");
  if (isMatching()) 
    stopMatching();
  TextEditor::keyPressed(key);
  juce_wchar chr=key.getTextCharacter();
  CommandID com=CommandIDs::EditorTextChanged;

  if (key.getKeyCode()==KeyPress::returnKey)
    com=CommandIDs::EditorNewline;
  else if (key.getKeyCode()==KeyPress::backspaceKey)
    com=CommandIDs::EditorBackspace;
  else if (!testFlag(EditFlags::MatchingOff) &&
	   (chr==')' || ((textid==TextIDs::Sal) && chr=='}')))
    matchParens();
  colorizeAfterChange(com);
  setFlag(EditFlags::NeedsSave);
  return true;
}

/*=======================================================================*
                              Mouse and Cursor 
 *=======================================================================*/

void TextBuffer::mouseDoubleClick (const MouseEvent &e)
{
  // make double click select exprs
  int a, b;
  String it=getTextSubstring(point(),point()+1);
  switch (it[0])
    {
    case '(' :
    case '{' :
    case '"' :
      a=point();
      forwardExpr();
      b=point();
      if (b>a)
	setHighlightedRegion(a, b-a);
      break;
    case ')' :
    case '}' :
      b=incPoint(1);
      backwardExpr();
      a=point();
      if (a<b)
	setHighlightedRegion(a, b-a);
      break;
    default:
      TextEditor::mouseDoubleClick(e);
      break;
    }
}  	

void TextBuffer::matchParens()
{
  //std::cout << "matchParens()\n";
  int b=point();
  backwardExpr(); // find start of expr
  int a=point();
  if (a<b)
    startMatching(a,b);
}

bool TextBuffer::isMatching()
{
  // true if we are matching right now
  return (matchpos > -1); 
}

void TextBuffer::startMatching(int pos1, int pos2)
{
  setPoint(pos1);
  setColour(TextEditor::caretColourId, Colours::red);
  matchpos=pos2;
  startTimer(1000);
}

void TextBuffer::timerCallback()
{
  stopMatching();
}

void TextBuffer::stopMatching()
{
  if (matchpos != -1)
    {
      setPoint(matchpos);  
      setColour(TextEditor::caretColourId, Colours::black);
      matchpos=-1;
      if (isTimerRunning())
	stopTimer();
    }
}

/*=======================================================================*
                            Eval Menu Support
 *=======================================================================*/

void TextBuffer::eval(bool macroexpand)
{

  bool region=(getHighlightedRegionLength() > 0);
  String text;
  
  if (region)
    text=getHighlightedText();
  else 
    text=backwardTopLevelText();
  
  if (isSyntax(TextIDs::Lisp) && !region)
    {
      // parse out backward sexpr if not region
      int typ, loc, end=text.length();
      typ = scan_sexpr(syntax->syntab, text, end-1, -1, 
		       SCAN_CODE, &loc, NULL);
      if (typ>SCAN_EMPTY) 
	text=text.substring(loc+1,end);
    }

  syntax->eval(text, region, macroexpand);
  //  std::cout << "text='" << text.toUTF8() << "'\n";
}

/*=======================================================================*
                              Syntactic Indentation
 *=======================================================================*/


void TextBuffer::syntacticIndent()
{
  int bol, eol, col, pos, len;
  String txt;
  bol=gotoBOL();
  if (bol==bufferMin()) 
    col=0;
  else 
    {
      txt=backwardTopLevelText();
      len=txt.length();
      pos=len-1; // search start
      // add current line to end of string (after search start)
      eol=gotoEOL();
      if (eol > bol)
	{
	  txt += getTextSubstring(bol,eol);
	  len += (eol-bol);
	}
      col=syntax->getIndent( txt, -1, len, pos);
    }
  //std::cout << "indent to column: " << col << "\n";
  if (indentToColumn(col))
    setFlag(EditFlags::NeedsSave);
}

bool TextBuffer::indentToColumn(int col)
{
  // reindent current line so that there are col white spaces before
  // the first non-white char in line
  
  int bol=pointBOL();
  int top=bol+currentIndent();  // current pos of first non-white or eol
  int loc=bol+col;  // goal pos for indentation
  
  setCaretVisible(false);
  setScrollToShowCursor(false);

  if (loc < top)
    {
      //std::cout << "deleting " << top-loc << " spaces.\n";
     setPoint(bol);
     setHighlightedRegion(bol, (top-loc));
     insertTextAtCursor(String::empty);    
    }
  else if (loc > top)
    {
      setPoint(bol);
      String pad=String::empty;
      for (int i=top; i<loc; i++) 
	pad << T(" ");
      //std::cout << "inserting " << pad.length() << " spaces.\n";
      insertTextAtCursor(pad);
    }
  setPoint(loc);
  setCaretVisible(true);
  setScrollToShowCursor(true);
  return (loc!=top);
}

int TextBuffer::currentIndent()
{
  int bol=pointBOL();
  int eol=pointEOL();
  String txt=getTextSubstring(bol,eol);
  return skip_chars(txt, T(" \t"), 0, txt.length());
}

/*=======================================================================*
                              Syntax Highlighting

   Syntax highlighting is slow and hideous because text can only be
   colorized when it is inserted into the texteditor! so to implement
   syntax highlighting you have to delete and reinsert any word you
   want colored. this is not only painfully slow for large files it
   makes the texteditor's underlying undo/redo facility useless since
   its filled with 'edits' that are only there because of
   highlighting.

 *=======================================================================*/



void TextBuffer::colorizeAll()
{
  if (testFlag(EditFlags::HiliteOff) ||
      !syntax->highlighting())
    return;
  else
    colorize(bufferMin(), bufferMax(), false);
}

void TextBuffer::colorizeAfterChange(CommandID cmd)
{
  if (testFlag(EditFlags::HiliteOff) ||
      !syntax->highlighting())
    return;
  int loc=0, bot=0, top=0;
  switch (cmd)
    {
    case CommandIDs::EditorBackspace:
    case CommandIDs::EditorTextChanged:
    case CommandIDs::EditorDelete:
    case CommandIDs::EmacsKillChar:
    case CommandIDs::EmacsKillLine:
    case CommandIDs::EmacsKillWord:
    case CommandIDs::EmacsKillWhite:
    case CommandIDs::EmacsKillExpr:
    case CommandIDs::EmacsYank:
    case CommandIDs::EditorIndent:
    case CommandIDs::EmacsUppercase:
    case CommandIDs::EmacsLowercase:
    case CommandIDs::EmacsCapitalize:
      // colorize current line
      bot=pointBOL();
      top=pointEOL();
      break;
    case CommandIDs::EditorNewline:
      // include previous line in recolor
      loc=point();
      bot=pointBOL();
      top=pointEOL();
      if (moveLine(-1)) 
	{
	  bot=point();
	  setPoint(loc);
	}
      break;
    case CommandIDs::EditorPaste:  
      // point is after pasted material. colorize from bol before
      // previous point to eol AFTER pasted
      loc=point();
      top=pointEOL();
      bot=loc-SystemClipboard::getTextFromClipboard().length();
      setPoint(bot);
      bot=pointBOL();
      setPoint(loc);
      break;
    case CommandIDs::EmacsOpenLine:
      // include new line in recolor
      loc=point();
      bot=pointBOL();
      top=pointEOL();
       if ( moveLine(1) )
	{
	  top=pointEOL();
	  setPoint(loc);
	}
      break;
    default:
      return;
    }
  if (bot!=top) 
    {
      // std::cout << "ColorizeAfterChange: " 
      //   << CommandIDs::toString(cmd).toUTF8() << "\n";
      colorize(bot, top, true);
    }
}

void TextBuffer::colorize (int from, int to, bool force)
{
  // JUCE LACAUNEA: (1) recoloring should only happen in the visible
  // region of buffer but i dont see anyway to get this information
  // from the viewpoint. (2) In order to recolor I have to delete and
  // add the text back into the buffer

  // this is needed because coloring changes the text buffer and we
  // dont want the editor's change callback to call the colorizer for
  // these changes.
  //  setFlag(EditFlags::Coloring); 

  String text = getTextSubstring(from, to);
  int len = text.length();
  int here = point(), pos = 0, start, end;
  String expr;
  scanresult typ;
  HiliteID hilite;
  Colour color, normal=syntax->hilites[HiliteIDs::None];
  static KeyPress dkey = KeyPress(KeyPress::deleteKey);
  
  // offset is the starting position of text string in buffer.
  setCaretVisible(false);
  setScrollToShowCursor(false);
  //printf("hiliting %d to %d...\n", from, to);
  while (pos < len)
    {
      typ=parse_sexpr(syntax->syntab, text, -1, len, 1,
		      SCAN_COLOR, &pos, &start, &end);
      hilite=HiliteIDs::None;
      if (typ>0)
	{
	  if (typ==SCAN_TOKEN)
	    {
	      hilite=syntax->getHilite(text, start, end);
	    }
	  else if (typ==SCAN_COMMENT) 
	    {
	      hilite=HiliteIDs::Comment;
	    }
	  else if (typ==SCAN_STRING)
	    {
	      hilite=HiliteIDs::String;
	    }
	  if ((hilite>HiliteIDs::None) || force)
	    {
	      // this is REALLY GROSS!
	      expr=text.substring(start,end);
	      color=syntax->hilites[hilite];
	      setPoint(from+start);
	      setHighlightedRegion(from+start, end-start);
	      TextEditor::keyPressed(dkey);
	      setColour(TextEditor::textColourId, color);
	      insertTextAtCursor(expr);
	      setColour(TextEditor::textColourId, normal);
	      /**
	      color=syntax->hilites[hilite];
	      setColour(TextEditor::textColourId, color);
	      TextEditor::repaintText(from+start, end-start);
	      setColour(TextEditor::textColourId, normal); 
	      **/
	    }
	}
    }
  setPoint(here);
  setCaretVisible(true);
  setScrollToShowCursor(true);
  //  clearFlag(EditFlags::Coloring); 
}

String TextBuffer::forwardTopLevelText()
{
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
  
  for (int i=0; ; i++)
    {
      if (eol > pos)
	{
	  line = getTextSubstring(pos, eol);
	  if (syntax->isWhiteBetween(line, 0, line.length()))
	    text += line;
	  else if (i == 0)
	    {
	      // collect first line no matter what
	      text += line;
	      nonw=true;
	    }
	  else if (nonw && syntax->isTopLevel(line))
	    break;
	  else 
	    {
	      text += line;
	      nonw=true;
	    }
	}
      text += T("\n");
      if (moveLine(1))
	{
	  pos=point();
	  eol=pointEOL();
	}
      else 
	{
	  break;
	}
    }
  setPoint(here);
  setCaretVisible(true);
  setScrollToShowCursor(true);
  return text;
}

String TextBuffer::backwardTopLevelText()
{
  // return all the text from point() back to the start of the nearest
  // top-level form before it
  setCaretVisible(false);
  setScrollToShowCursor(false);
  String line, text = String::empty;
  int here=point();
  int pos=here;
  int bol=pointBOL();
  
  for (int i=0; ; i++)
    {
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

/*=======================================================================*
                                 Symbol Help
 *=======================================================================*/

void TextBuffer::lookupHelpAtPoint()
{
  bool region=(getHighlightedRegionLength() > 0);
  String text;
  String helppath;

  switch (textid)
    {
    case TextIDs::Sal:
      helppath=T("Sal:CM");
      break;
    case TextIDs::Lisp:
      helppath=T("CM");
      break;
    default:
      return;
    }
#ifdef SNDLIB
  helppath<<T(":SndLib");
#endif
  helppath<<T(":Scheme");
  if (region)
    text=getHighlightedText();
  else
    {
      int pos=point();
      int bol=pointBOL();
      text=getTextSubstring(bol, pointEOL() );
      int len=text.length();
      int beg=skip_syntax(syntax->syntab, text, T("w_"), pos-bol-1, -1);
      int end=skip_syntax(syntax->syntab, text, T("w_"), pos-bol, len);
      if (beg+1==end)
	return;
      text=text.substring(beg+1,end);
    }
  Help::getInstance()->symbolHelp(text, helppath);
}

/*=======================================================================*
                          Emacs Point Info Functions
 *=======================================================================*/

int TextBuffer::point() 
{
  return getCaretPosition();
}

int TextBuffer::setPoint(int p) 
{
  setCaretPosition(p);
  return getCaretPosition();
}

int TextBuffer::incPoint(int i) 
{
  return setPoint(point() + i);
}

bool TextBuffer::isBOB()
{
  return (point()==bufferMin());
}

bool TextBuffer::isEOB() 
{
  return (point()==bufferMax());
}

bool TextBuffer::isBOL() 
{
  if (isBOB())
    return true;
  return (point()==pointBOL());
}

bool TextBuffer::isEOL() 
{
  if (isEOB()) 
    return true;
  return (point()==pointEOL());
}

int TextBuffer::pointBOL()
{
  int here = getCaretPosition();
  setCaretVisible(false);
  int there=gotoBOL();
  setCaretPosition(here);
  setCaretVisible(true);
  return there;
}

int TextBuffer::pointEOL()
{
  int here = getCaretPosition();
  setCaretVisible(false);
  int there=gotoEOL();
  setCaretPosition(here);
  setCaretVisible(true);
  return there;
}

int TextBuffer::pointColumn()
{
  return point()-pointBOL();
}

int TextBuffer::pointLineLength()
{
  return pointEOL()-pointBOL();
}

int TextBuffer::bufferMin()
{
  return 0;
}

int TextBuffer::bufferMax()
{
  // really stupid but its much faster than getText().length() !
  int cp1 = getCaretPosition();
  setCaretVisible(false);
  setCaretPosition(BUFMAX);
  int cp2=getCaretPosition();
  setCaretPosition(cp1);
  setCaretVisible(true);
  return cp2;
}

/*=======================================================================*
                         Emacs Cursor Motion Functions
 *=======================================================================*/

int TextBuffer::gotoBOB()
{
  return setPoint(0);
}

int TextBuffer::gotoEOB()
{
  return setPoint(BUFMAX);
}

int TextBuffer::gotoBOL()
{
  int pos=findCharBackward('\n');
  if (pos<0)
    return gotoBOB();
  else 
    return setPoint(pos);
}

int TextBuffer::gotoEOL()
{
  int pos=findCharForward('\n');
  if (pos<0) 
    return gotoEOB();
  else 
    return setPoint(pos);
}

void TextBuffer::forwardPage() 
{
  TextEditor::keyPressed(KeyPress(KeyPress::pageDownKey)); 
}

void TextBuffer::backwardPage()
{
  TextEditor::keyPressed(KeyPress(KeyPress::pageUpKey)); 
}

void TextBuffer::forwardChar() 
{
  TextEditor::keyPressed(KeyPress(KeyPress::rightKey)); 
}

void TextBuffer::backwardChar()
{
  TextEditor::keyPressed(KeyPress(KeyPress::leftKey)); 
}

void TextBuffer::forwardLine()
{
  // Emacs C-n motion with goal column
  static int goal=0;
  int col;
  if (prev != CommandIDs::EmacsLineForward)
    goal=pointColumn();
  moveLine(1); // cursor now on bol
  col=pointColumn();
  if (col<goal)
    if (pointLineLength()>=goal)
      incPoint(goal-col);
    else
      gotoEOL();
}

void TextBuffer::backwardLine()
{
  // Emacs C-p motion including goal column
  static int goal=0;
  int col;
  if (prev != CommandIDs::EmacsLineBackward)
    goal=pointColumn();
  moveLine(-1);
  col=pointColumn();
  if (col<goal)
    if (pointLineLength()>=goal)
      incPoint(goal-col);
    else
      gotoEOL();
}

void TextBuffer::forwardWord()
{
  // Emacs M-f word motion. process buffer line by line scanning for
  // next word.
  String str;
  int pos, eol, len, loc;
  pos = point();
  eol = pointEOL();
  while (true)
    {
      len=eol-pos;
      if (len > 0)
	{
	  str = getTextSubstring(pos, eol);
	  // skip over white space
	  loc = skip_syntax(syntax->syntab, str, T("^w_"), 0, len);
	  if (loc < len)
	    {
	      loc = skip_syntax(syntax->syntab, str, T("w_"), loc, len);
	      setPoint(pos+loc);
	      return;
	    }
	}
      if (moveLine(1)) 
	{
	  pos=point();
	  eol=pointEOL();
	}
      else
	break;
    }
  setPoint(eol);
}

void TextBuffer::backwardWord()
{
  // Emacs M-b word motion. search line by line scanning for next
  // word.
  String str;
  int pos, bol, len, loc;
  pos = point(); // pos is EXCLUSIVE upper bound
  bol = pointBOL();
  while (true)
    {
      len=pos-bol;
      if (len > 0)
	{
	  str = getTextSubstring(bol,pos);
	  loc = skip_syntax(syntax->syntab, str, T("^w_"), len-1, -1);
	  if (loc > -1) 
	    {
	      loc = skip_syntax(syntax->syntab, str, T("w_"), loc, -1);
	      // loc is now -1 or on nonword
	      setPoint(bol+loc+1);
	      return;
	    }
	}
      if (moveLine(-1))
	{
	  bol=point();
	  pos=pointEOL();
	}
      else
	break;
    }
  setPoint(bol);
}

void TextBuffer::forwardExpr()
{
  if (isSyntax(TextIDs::Sal) )
    {
      String text = forwardTopLevelText();
      int typ, loc, pos=point(), end=text.length();
      typ=scan_sexpr(syntax->syntab,text,0,end,SCAN_CODE,&loc,NULL);
      if (typ == SCAN_UNLEVEL)
	PlatformUtilities::beep();
      else if (typ == SCAN_UNMATCHED)
	PlatformUtilities::beep();
      else
	setPoint(pos+loc);
    }
  else if (isSyntax(TextIDs::Lisp) )
    {
      String text;
      int end, typ, loc;
      int top=-1;
      int pos=point();
      gotoEOL();
      while (true)
	{
	  text=getTextSubstring(pos, point());
	  end=text.length();
	  typ=scan_sexpr(syntax->syntab,text,0,end,SCAN_CODE,&loc,NULL);
	  if ((typ==SCAN_LIST) || (typ==SCAN_TOKEN) || (typ==SCAN_STRING))
	    {
	      top=pos+loc;
	      break;
	    }
	  if (!moveLine(1))
	    break;
	}
      
      if (top>-1)
	{
	  //std::cout << "parsed='" << getTextSubstring(pos,top).toUTF8()
	  //<< "'\n";
	  setPoint(top);
	}
      else
	{
	  PlatformUtilities::beep();
	  setPoint(pos);
	}
    }
  else
    PlatformUtilities::beep();
}

void TextBuffer::backwardExpr()
{
  if (isSyntax(TextIDs::Sal) )
    {
      String text = backwardTopLevelText();
      int typ, loc, pos=point(), end=text.length();
      typ=scan_sexpr(syntax->syntab, text, end-1, -1,SCAN_CODE, &loc, NULL);
      if (typ == SCAN_UNLEVEL)
	PlatformUtilities::beep();
      else if (typ == SCAN_UNMATCHED)
	PlatformUtilities::beep();
      else 
	setPoint(pos-end+loc+1);
    }
  else if (isSyntax(TextIDs::Lisp) )
    {
      String text;
      int end, typ, loc;
      int beg=-1;
      int pos=point();
      gotoBOL();
      while (true)
	{
	  text=getTextSubstring(point(), pos);
	  end=text.length();
	  typ=scan_sexpr(syntax->syntab,text,end-1,-1,SCAN_CODE, &loc,NULL);
	  if ((typ==SCAN_LIST) || (typ==SCAN_TOKEN) || (typ==SCAN_STRING))
	    {
	      beg=pos-end+loc+1;
	      break;
	    }
	  if (!moveLine(-1))
	    break;
	}
      if (beg>-1)
	{
	  //std::cout << "parsed='" << getTextSubstring(beg,pos).toUTF8()
	  //	    << "'\n";
	  setPoint(beg);
	}
      else
	{
	  PlatformUtilities::beep();
	  setPoint(pos);
	}
    }
  else
    PlatformUtilities::beep();
}

bool TextBuffer::moveLine(int n)
{
  // the main function for moving and accessing line text. move N
  // lines forward or backward and position point at BOL.  returns
  // true if line actually moved, else false, which allows calling
  // code to stop line iteration without bounds checking.
  int old = gotoBOL();
  // warning: this code assumes setting point out of bounds is legal
  if (n<0)
    {
      for (int i=n; i<0; i++)
	{
	  incPoint(-1);
	  gotoBOL();
	}
    }
  else if (n>0)
    {
      for (int i=0; i<n; i++)
	{
	  gotoEOL();
	  incPoint(1);
	}
    }
  return !(pointBOL()==old);
}

/*=======================================================================*
                             Search Functions
 *=======================================================================*/

int TextBuffer::findCharForward(char c)
{
  int pos=point();
  int len;
  int loc=-1;
  String str;
  // Warning: this only works because its not an error to pass
  // getTextSubstring an index that is out of range.
  str = getTextSubstring(pos, pos+CHUNKSIZE);
  len = str.length();
  while (1)
    {
    if (len==0)
      break;
    for (int i=0; i<len; i++)
      if (str[i]==c)
	{
	  loc=pos+i;
	  break;
	}
    if (loc>-1)
      break;
    pos += len;
    str = getTextSubstring(pos, pos+CHUNKSIZE);
    len = str.length();
  }
  return loc;
}

int TextBuffer::findCharBackward(char c)
{
  int pos=point();
  int len;
  int loc=-1;
  String str;
  // Warning: this only works because its not an error to pass
  // getTextSubstring an index that is out of range.
  str = getTextSubstring(pos-CHUNKSIZE, pos);
  len = str.length();
  while (1)
    {
      if (len==0)
	break;
      for (int i=len-1; i>-1; i--)
	if (str[i] == c)
	  {
	    loc=pos-(len-i)+1;
	    break;
	  }
      if (loc>-1)
	break;
      pos -= len;
      str = getTextSubstring(pos-CHUNKSIZE, pos);
      len = str.length();
    }
  return loc;
}

/*=======================================================================*
                               Find and Replace
 *=======================================================================*/

bool TextBuffer::replaceAll(String str, String rep)
{
  int n=0;
  while (findNext(str, false))
    {
      n++;
      replace(rep);
    }
  return (n>0);
}

bool TextBuffer::replace(String rep)
{
  if (!getHighlightedRegionLength()>0)
    return false;
  insertTextAtCursor(rep);
  setFlag(EditFlags::NeedsSave);
  return true;
}

bool TextBuffer::replaceAndFind(String str, String rep)
{
  if (replace(rep))
    return findNext(str);
  return false;
}

bool TextBuffer::findPrevious(String str, bool wrap)
{
  int pos=getCaretPosition()-getHighlightedRegionLength();
  int wid=str.length();
  int tot=size();
  int got=-1;
  while (true)
    {
      if (pos<=wid) // not enough chars to make a match
	{
	  if (wrap)
	    {
	      wrap=false;
	      pos=tot;
	    }
	  else
	    break;
	}
      int top=pos-100;
      if (top<0) top=0;
      String tmp=getTextSubstring(top, pos);
      int len=tmp.length();
      got=tmp.lastIndexOf(str);
      if (got>-1)
	{
	  pos -= (len-got);
	  break;
	}
      // next search position must overlapping current end
      pos=top+wid;
    }
  if (got>-1)
    {
      setHighlightedRegion(pos,wid);
      return true;
    }
  return false;
}

bool TextBuffer::findNext(String str, bool wrap)
{
  // start looking at current cursor position (if region exists caret
  // position is end of region)
  int pos=getCaretPosition();
  int wid=str.length();
  int tot=size();
  int got=-1;
  //  bool wrap=true;
  while (true)
    {
      if (pos>tot-wid) // not enough chars to make a match
	{
	  if (wrap)
	    {
	      wrap=false;
	      pos=0;
	    }
	  else
	    break;
	}
      String tmp=getTextSubstring(pos, pos+100);
      got=tmp.indexOf(str);
      if (got>-1)
	{
	  pos += got;
	  break;
	}
      int len=tmp.length();
      // next search position must overlapping current end
      pos=pos+len-wid+1;
    }
  if (got>-1)
    {
      setHighlightedRegion(pos,wid);
      return true;
    }
  return false;
}

/*=======================================================================*
                            Emacs Edit Functions
 *=======================================================================*/

void TextBuffer::killChar()
{
  TextEditor::keyPressed(KeyPress(KeyPress::deleteKey));
  setFlag(EditFlags::NeedsSave);
}

void TextBuffer::killWord()
{
  int from=point();
  forwardWord();
  int to=point();
  if (to > from)
    {
      String text=getTextSubstring(from,to);
      deleteRegion(from, to);
      updateClipboardWithKill(text, CommandIDs::EmacsKillWord);
      setFlag(EditFlags::NeedsSave);
    }
}

void TextBuffer::killExpr() 
{
  int from=point();
  forwardExpr();
  int to=point();
  if (to > from)
    {
      String text=getTextSubstring(from,to);
      deleteRegion(from, to);
      updateClipboardWithKill(text, CommandIDs::EmacsKillExpr);
      setFlag(EditFlags::NeedsSave);
    }
}

void TextBuffer::killLine()
{
  // Emacs C-k line killing from point forward. kills to EOL+1 if line
  // contains only white space after point
  int from=point();
  int to=pointEOL();
  String text=getTextSubstring(from,to);
  if ( text == String::empty || text.containsOnly(T(" \t")) )
    {
      text += T("\n");
      to++;
    }
  deleteRegion(from, to);
  updateClipboardWithKill(text, CommandIDs::EmacsKillLine);
  setFlag(EditFlags::NeedsSave);
}

void TextBuffer::killRegion()
{
  copy();
  keyPressed(KeyPress(KeyPress::deleteKey));
  setFlag(EditFlags::NeedsSave);
}

void TextBuffer::killWhite()
{
  // search buffer for next non-white char and delete up to that
  // position
  String white=T(" \t\n");
  int from=point();
  int to;
  while (true)
    {
      bool go=true;
      to=point();
      String line=getTextSubstring(to,pointEOL());
      for (int i=0; i<line.length() && go; i++)
	if (white.containsChar(line[i])) 
	  to++;
	else
	  go=false;
      if (!go)
	break;
      else if (!moveLine(1)) // point now at next bol
	break;
    }
  deleteRegion(from,to);
  setFlag(EditFlags::NeedsSave);
}

void TextBuffer::openLine()
{
  // C-o new line does not change point
  int here=point();
  insertTextAtCursor(T("\n"));
  setPoint(here);
  setFlag(EditFlags::NeedsSave);
}

void TextBuffer::changeCase(int flag)
{
  // change case of word at point. 0=lower,1=upper,2=capitalize
  int beg=point();
  forwardWord();
  int end=point();
  String text=getTextSubstring(beg, end);
  if (text==String::empty)
    return;
  deleteRegion(beg,end);
  if (flag==0)
    insertTextAtCursor(text.toLowerCase());
  else if (flag==1)
    insertTextAtCursor(text.toUpperCase());
  else if (flag==2)
    {
      int len=text.length();
      // get first alphachar 
      int loc=skip_syntax(syntax->syntab, text, T("^w"), 0, len);	
      insertTextAtCursor(text.substring(0,loc));
      if (loc<len)
	{
	  insertTextAtCursor(text.substring(loc,loc+1).toUpperCase());
	  insertTextAtCursor(text.substring(loc+1,len));
	}
    }
  beg=point();
  //colorizeAfterChange(CommandIDs::EditorIndent); // recolorize whole line for now..
  setPoint(beg);
  setFlag(EditFlags::NeedsSave);
}

void TextBuffer::updateClipboardWithKill(String kill, CommandID cmd)
{
  // repeating kill commands ADDS kills to clipboard.
  if (prev==cmd)
    kill = SystemClipboard::getTextFromClipboard() + kill;
  SystemClipboard::copyTextToClipboard(kill);
}

void TextBuffer::deleteRegion(int from, int to)
{
  // delete chars between from and to (exclusive), do not update
  // clipboard
  if (to>from)
    {
      setHighlightedRegion(from, to-from);
      insertTextAtCursor(String::empty);
    }
}

/*=======================================================================*
                              Focus Changing
 *=======================================================================*/

void TextBuffer::focusGained(Component::FocusChangeType cause)
{
  // When an editor window is selected is becomes the "focus" editor
  // and it only loses this focus when another editor window is
  // selected, i.e. the editing focus is maintained even when the
  // window itself is not the active window
  TopLevelWindow* w=NULL;
  // clear any other editing window of the focus
  for (int i=0; i<TopLevelWindow::getNumTopLevelWindows(); i++)
    {
      w=TopLevelWindow::getTopLevelWindow(i);
      if (w->getComponentPropertyBool(T("FocusEditor"), false))
	w->setComponentProperty(T("FocusEditor"), false);
    }
  // select this one
  getTopLevelComponent()->setComponentProperty(T("FocusEditor"), true);
}

// void TextBuffer::focusLost(Component::FocusChangeType cause) {}

TextEditorWindow* TextEditorWindow::getFocusTextEditor()
{
  for (int i=0; i<TopLevelWindow::getNumTopLevelWindows(); i++)
    {
      TopLevelWindow* w=TopLevelWindow::getTopLevelWindow(i);
      if ( w->getComponentPropertyBool(T("FocusEditor"), false))
	{
	  return (TextEditorWindow*)w;
	}
    }
  return (TextEditorWindow*)NULL;
}

/*=======================================================================*
                           Find and Replace Window
  *=======================================================================*/

class FindAndReplaceDialog  : public Component,
                              public ButtonListener
{
public:
  FindAndReplaceDialog ();
  ~FindAndReplaceDialog();
  void resized();
  void buttonClicked (Button* buttonThatWasClicked);
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
  ~FindAndReplaceWindow()
  {
    // dont have to delete content component
  }
};


FindAndReplaceDialog::FindAndReplaceDialog ()
    : label1 (0),
      textEditor1 (0),
      label2 (0),
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
  
  addAndMakeVisible (textButton1 = new TextButton (String::empty));
  textButton1->setButtonText (T("Replace All"));
  textButton1->setConnectedEdges (Button::ConnectedOnRight);
  textButton1->addButtonListener (this);
  
  addAndMakeVisible (textButton2 = new TextButton (String::empty));
  textButton2->setButtonText (T("Replace"));
  textButton2->setConnectedEdges (Button::ConnectedOnLeft | 
				  Button::ConnectedOnRight);
  textButton2->addButtonListener (this);
  
  addAndMakeVisible (textButton3 = new TextButton (String::empty));
  textButton3->setButtonText (T("Replace & Find"));
  textButton3->setConnectedEdges (Button::ConnectedOnLeft |
				  Button::ConnectedOnRight);
  textButton3->addButtonListener (this);
  
  addAndMakeVisible (textButton4 = new TextButton (String::empty));
  textButton4->setButtonText (T("Previous"));
  textButton4->setConnectedEdges (Button::ConnectedOnLeft |
				  Button::ConnectedOnRight);
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

void FindAndReplaceDialog::buttonClicked (Button* buttonThatWasClicked)
{
  TextEditorWindow* win=TextEditorWindow::getFocusTextEditor();

  if (!win)  // no editor open
    {
      PlatformUtilities::beep();
      return;
    }
  TextBuffer* buf=win->getTextBuffer();
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

void TextEditorWindow::openFindAndReplaceDialog()
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

