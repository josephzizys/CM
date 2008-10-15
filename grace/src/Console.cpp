/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

#include "Enumerations.h"
#include "Console.h"
#include "Plotter.h"
#include "Buffer.h"
#include "Editor.h"
#include "Grace.h"

//#include "Audio.h"

#ifndef SCHEME
#include "Lisp.h"
#else
#include "Scheme.h"
#include "Midi.h"
#include "Csound.h"
#endif

#include <iostream>

TransparencySlider::TransparencySlider(DocumentWindow* _window) 
  : Slider(String::empty) 
{
  window = _window;
  setRange(10, 100, 1);
  setSliderStyle(Slider::LinearHorizontal);
  setTextBoxStyle(Slider::NoTextBox, false, 70, 20);
  setValue(((ConsoleWindow *)window)->getOpacity(), false);
  setTextValueSuffix(T("%"));
}

TransparencySlider::~TransparencySlider() { }

void ConsoleWindow::sliderValueChanged(Slider *slider) {
  TransparencySlider *tslider = (TransparencySlider*)slider;
  ConsoleWindow *win = (ConsoleWindow*)(tslider->window);
  TextEditor* ted=win->getConsole();
  ConsoleTheme *theme = win->console->getCurrentTheme();
  Colour bgcolor = win->getBackgroundColour();
  Colour teditColor = theme->getColor(ConsoleTheme::bgColor);
  double val = slider->getValue();
  ted->setColour(TextEditor::backgroundColourId,
                 teditColor.withAlpha( (float) (val / 100.5)));
  win->setBackgroundColour( bgcolor.withAlpha( (float) (val / 100.5) ));
  win->setOpacity(val);
}


SliderMenuComponent::SliderMenuComponent(DocumentWindow* _window) 
: PopupMenuCustomComponent(false)
{
  String str=T("Opacity");
  Label* lab=new Label(String::empty, str);
  Font font=Font(getLookAndFeel().getPopupMenuFont());
  lab->setFont(font);
  lab->setBounds(24,0,font.getStringWidth(str), 30);
  addAndMakeVisible(lab);
  addAndMakeVisible(slider = new TransparencySlider (_window));
  slider->setValue(((ConsoleWindow *)_window)->getOpacity(), false);
  slider->setBounds(lab->getRight()+8, 0, 70, 30);
}

SliderMenuComponent::~SliderMenuComponent()
{
  delete slider;
}

void SliderMenuComponent::getIdealSize(int &idealWidth, int &idealHeight)
{
  idealWidth = 200;
  idealHeight = 30;
}

Console::Console () : 
numthemes (0),
curtheme (0)
{
  GracePreferences* p=GracePreferences::getInstance();
  buffer = new TextEditor( String::empty) ;
  buffer->setMultiLine(true);
  buffer->setScrollToShowCursor(true);
  buffer->setReadOnly(true);
  buffer->setCaretVisible(false);    
  addChildComponent(buffer);
  buffer->setFont( Font(Font::getDefaultMonospacedFontName(), 
                        p->getConsoleFontSize(),
                        Font::plain));
  numthemes=6;
  for (int i=0; i<numthemes; i++)
    initTheme(i);
  int t=findTheme(p->getConsoleTheme());
  if (t==-1)
    setTheme(0); 
  else
    setTheme(t);
  buffer->setVisible(true);
  setVisible(true);
  lock = new CriticalSection();
}

Console::~Console () {
  delete buffer;
  delete lock;
}

void Console::initTheme (int idx) {
  String n=String::empty;
  juce::uint32 b, i, o, r, h, c;
  
  //Font f=Font(Font::getDefaultMonospacedFontName(), 
  //	      17.0f, Font::plain );
  // make value, warning and error colors consistent across themes (?)
  juce::uint32 v= 0x00cd00, w=0xff8c00, e=0xcd0000;
  
  switch (idx) {
    case 0 :
      n=T("Clarity and Beauty");
      b=0x000000; i=0xffffff; o=0xffa07a; 
      r=0xbebebe; h=0xffffff; c=0xffff00;
      break;
    case 1 :
      n=T("Deep Blue");
      b=0x102e4e;  i=0xeeeeee;  o=0xdeb887;  
      r=0x008b8b;  h=0xeeeeee;  c=0x00ff00;        
      break;
    case 2 :
      n=T("Gnome");
      b=0x2f4f4f;  i=0xf5deb3;  o=0xffa07a;
      r=0x008b8b;  h=0x00ffff;  c=0xd3d3d3;
      break;
    case 3 :
      n=T("Snowish");
      b=0xeee9e9;  i=0x2f4f4f;  o=0x9400d3;
      r=0xeedc82;  h=0x000000;  c=0xcd0000;
      break;
    case 4 :
      n=T("Standard Emacs");
      b=0xffffff;  i=0x000000;  o=0xbc8f8f;  
      r=0xeedc82;  h=0x000000;  c=0x000000;
      break;
    case 5 :
      n=T("Standard XEmacs");
      b=0xcccccc;  i=0x000000;  o=0x008b00;  
      r=0xa6a6a6;  h=0x000000;  c=0xcd0000;
      break;
    default :
      n=String::empty;
      b=0xffffff; i=0x000000; o=0x000000; 
      r=0xbebebe; h=0x000000; c=0xff0000;
      break;
  }
  v += 0xff000000;  w += 0xff000000;  e += 0xff000000;
  b += 0xff000000;  i += 0xff000000;  o += 0xff000000;
  r += 0xff000000;  h += 0xff000000;  c += 0xff000000;  
  themes[idx].name=n;
  //themes[idx].font=f;
  themes[idx].setColor(ConsoleTheme::bgColor, Colour(b));
  themes[idx].setColor(ConsoleTheme::inputColor, Colour(i));
  themes[idx].setColor(ConsoleTheme::outputColor, Colour(o));
  themes[idx].setColor(ConsoleTheme::warningColor,Colour(w));
  themes[idx].setColor(ConsoleTheme::errorColor, Colour(e));
  themes[idx].setColor(ConsoleTheme::valueColor, Colour(v));
  themes[idx].setColor(ConsoleTheme::hiliteColor, Colour(r));
  themes[idx].setColor(ConsoleTheme::hiliteTextColor, Colour(h));
  themes[idx].setColor(ConsoleTheme::caretColor, Colour(c));
}

void Console::setTheme(int i) {
  ConsoleWindow* win=((ConsoleWindow*)getTopLevelComponent());
  curtheme=i;
  //  win->setOpacity(100.0);
  //buffer->setFont( themes[i].getFont() );
  Colour bgcolor=themes[i].getColor(ConsoleTheme::bgColor);
  buffer->setColour( TextEditor::backgroundColourId, 
                    bgcolor);
  buffer->setColour( TextEditor::textColourId,
                    themes[i].getColor(ConsoleTheme::outputColor));
  buffer->setColour( TextEditor::highlightColourId,
                    themes[i].getColor(ConsoleTheme::hiliteColor));
  buffer->setColour( TextEditor::highlightedTextColourId,
                    themes[i].getColor(ConsoleTheme::hiliteTextColor));
  buffer->setColour( TextEditor::caretColourId,
                    themes[i].getColor(ConsoleTheme::caretColor));
  //buffer->applyFontToAllText(themes[i].getFont());
  buffer->applyFontToAllText(buffer->getFont());
  GracePreferences* p=GracePreferences::getInstance();
  p->setConsoleTheme(getThemeName(curtheme));
}

void Console::display(String str, ConsoleTheme::ColorType col) {
  buffer->setCaretPosition(0xFFFFFF);
  buffer->setColour(TextEditor::textColourId,
                    getCurrentTheme()->getColor(col));
  buffer->insertTextAtCursor(str);
}

//////////////////////////////////////////////////////////////////////
/// Console window
//

ConsoleWindow::ConsoleWindow (bool dosplash)
: DocumentWindow ( T("Console") , Colours::white,
                  DocumentWindow::allButtons, true ),
#ifndef SCHEME
lisp (0),
#endif
currentTransparency (100.0),
evalnum (0)
{
#ifndef SCHEME
  lisp = new LispConnection(this);
  
#endif
  
  menubar = new MenuBarComponent(this);
  setMenuBar(this);
  //setApplicationCommandManagerToWatch(commandManager);
  console=new Console();
  splash=new SplashComponent();
  setContentComponent(console);
  setResizable(true, true); 
  
  //GraceApp* app = (GraceApp*)JUCEApplication::getInstance();
  GracePreferences* p=GracePreferences::getInstance();
  setUsingNativeTitleBar(p->isNativeTitleBars());
  console->buffer->setVisible(true);
  centreWithSize (450, 350);
  setVisible(true);
  if (dosplash) {
    showSplash();
    splash->fadeOutComponent(5000);
    if ( isSplashVisible() ) // user might have clicked
      hideSplash();
  }
  printBanner();
#ifndef SCHEME
  
  if (p->isLispLaunchAtStartup())
    lisp->startLisp();
#endif
}

ConsoleWindow::~ConsoleWindow () {
  // this will be called by GraceApp
#ifndef SCHEME
  
  if ( lisp->isLispRunning() )
    lisp->stopLisp();
  delete lisp;
#endif
}

void ConsoleWindow::closeButtonPressed () {
  GraceApp * app = (GraceApp*)JUCEApplication::getInstance();
  app->graceQuit(true);
}

/*
 * Console specific methods
 */

void ConsoleWindow::printBanner() {
  GraceApp* app = (GraceApp*)JUCEApplication::getInstance();
  String banner = app->getApplicationName() + T(" ")
  + app->getApplicationVersion()
  + T("\n(c) 2008 Todd Ingalls, Rick Taube\n");

  banner << T("JUCE ") << JUCE_MAJOR_VERSION << T(".") 
	 << JUCE_MINOR_VERSION 
	 << T(", (c) 2008 Julian Storer\n");

  printMessage( banner);
  File reso=File(app->getResourceDirectoryPathName());
  if ( ! reso.isDirectory() )
    printWarning(T("Warning: application resource directory '") + 
                 reso.getFullPathName() + T("' does not exist.\n"));
  
}

TextEditor * ConsoleWindow::getConsole() {
  return console->buffer;
}

bool ConsoleWindow::isConsoleReadOnly() {
  return console->buffer->isReadOnly();
}

void ConsoleWindow::setConsoleReadOnly(bool b) {
  if (b) {
    console->buffer->setReadOnly(true);
    console->buffer->setCaretVisible(false);    
  }
  else {
    console->buffer->setReadOnly(false);
    console->buffer->setCaretVisible(true);    
  }
}

void ConsoleWindow::setConsoleTextColor (int c) {
  //  const MessageManagerLock mmLock;
  console->buffer->setColour(TextEditor::textColourId,
                             console->getCurrentTheme()->getColor(c));
  //  console->buffer->setColour(TextEditor::textColourId,
  //  			     Colours::white);
}

void ConsoleWindow::consoleClear() {
  console->buffer->clear();
  printBanner();
}

void ConsoleWindow::consoleCopy() {
  console->buffer->copy();
}

void ConsoleWindow::consoleSelectAll() {
  // yuck!
  console->buffer->setHighlightedRegion( 0, 0xFFFFFFF );
}

void ConsoleWindow::gotoEOB() {
  //  const MessageManagerLock mmLock;
  console->buffer->setCaretPosition(0xFFFFFF);
}

void ConsoleWindow::terpri() {
  //  const MessageManagerLock mmLock;
  console->buffer->insertTextAtCursor(T("\n"));
}

void ConsoleWindow::freshLine() {
  //  const MessageManagerLock mmLock;
  int pos=console->buffer->getCaretPosition();
  if (pos > 0) {
    if (T("\n") != console->buffer->getTextSubstring(pos-1,pos)) {
      KeyPress key = KeyPress(KeyPress::endKey);
      //KeyPress dkey = KeyPress(KeyPress::downKey);
      console->buffer->keyPressed(key);
      console->buffer->insertTextAtCursor(T("\n"));
    }
  }
}	

void ConsoleWindow::printMessage(String str, bool force) {
  console->display(str, ConsoleTheme::outputColor);
}

void ConsoleWindow::printWarning(String str, bool force) {
  console->display(str, ConsoleTheme::warningColor);
}

void ConsoleWindow::printError(String str, bool force) {
  console->display(str, ConsoleTheme::errorColor);
}

void ConsoleWindow::printValues(String str, bool force) {
  console->display(str, ConsoleTheme::valueColor);
}

float ConsoleWindow::getFontSize( ) {
  return getConsole()->getFont().getHeight();
}

void ConsoleWindow::setFontSize( float size ) {
  GracePreferences* p=GracePreferences::getInstance();
  TextEditor* ed=getConsole();
  Font font=ed->getFont();
  font.setHeight(size);
  ed->applyFontToAllText(font);
  p->setConsoleFontSize(size);
}

#ifndef SCHEME
void ConsoleWindow::consoleEval (String code, bool isSal, 
                                 bool isRegion) {
  if (! lisp->isLispRunning() ){
    printError(T(">>> Lisp is not running. Use Console>Lisp>Start Lisp\nto start a Lisp session.\n"));
    return;
  }
  String sexpr;
  int message;
  GracePreferences* p=GracePreferences::getInstance();
  if ( isSal ) {
    message=LispConnection::msgSalEval;
    sexpr=code;
  }
  else {
    message=LispConnection::msgLispEval;
    sexpr=code;
    if ( isRegion )
      sexpr= T("(progn ") + sexpr + T(")");
  }
  lisp->sendLispSexpr(sexpr, message);
}
#else
void ConsoleWindow::consoleEval (String code, bool isSal, bool isRegion) {
  int nodetype=SchemeNode::EXPR;
  //  evalnum++;
  //  printf("[%d] Eval: '%s'\n", evalnum, code.toUTF8());
  if ( isSal )
    nodetype=SchemeNode::SAL;
  ((GraceApp *)GraceApp::getInstance())->
  schemeProcess->addNode(nodetype, 0.0, code);
}
#endif

void ConsoleWindow::showSplash () {
  splash->setSize(console->getWidth(),console->getHeight());
  console->addChildComponent(splash);
  splash->setVisible(true);
}

void ConsoleWindow::hideSplash () {
  splash->setVisible(false);
  splash->setSize(0,0);
  console->removeChildComponent(splash);
}

bool ConsoleWindow::isSplashVisible() {
  return splash->isVisible();
}

/* Console Menubar
 *
 */

const StringArray ConsoleWindow::getMenuBarNames () {
#ifdef SCHEME
  const tchar* const menuNames[] = { T("File"), T("Edit"), T("View"),
    T("Ports"), T("Window"), T("Help"), 0 };
#else
  const tchar* const menuNames[] = { T("File"), T("Edit"), T("View"),
    T("Lisp"), T("Window"), T("Help"), 0 };
#endif
  return StringArray((const tchar**) menuNames);
}


#ifdef SCHEME
const PopupMenu ConsoleWindow::getPortsMenu ()
{ 
  GraceApp* app = (GraceApp*)JUCEApplication::getInstance();
  PopupMenu portsmenu;

  portsmenu.addSubMenu( T("Midi Out"), app->midiOutPort->getMidiOutMenu());
  portsmenu.addSubMenu(T("Midi In"), app->midiInPort->getMidiInMenu());
  portsmenu.addSubMenu( T("Midi Seq"), app->midiOutPort->getMidiSeqMenu());
#ifdef PORTCSOUND
  portsmenu.addSubMenu(T("Csound"), app->getCsoundPort()->getCsoundMenu());
#endif
#ifdef FOMUS
  portsmenu.addSubMenu(T("Fomus"), app->getFomusPort()->getFomusMenu());
#endif
  portsmenu.addSeparator();
  portsmenu.addItem(CommandIDs::SchedulerScoreMode,
		    T("Score Capture"), 
		    app->schemeProcess->isQueueEmpty(),
		    app->schemeProcess->isScoreCapture());
  return portsmenu;
}
#endif

const PopupMenu ConsoleWindow::getMenuForIndex (int idx, const String &name)
{
  GraceApp* app = (GraceApp*)JUCEApplication::getInstance();
  //  GracePreferences* p=GracePreferences::getInstance();
  GracePreferences* p=app->getPreferences();
  ApplicationCommandManager* cm = app->commandManager;
  
  PopupMenu menu;
  PopupMenu sub1, sub2, sub3, sub4, sub5, sub6, sub7;
  PopupMenu midiSeqMenu;
  int val;
  switch (idx) 
    {

    case GRACEMENU :
      // encode buffer syntax as id data
      sub1.addItem(CommandIDs::toID(CommandIDs::NewEditor,
				    TextIDs::Sal),
		   T("Sal Editor"), 
		   true); 
      sub1.addItem(CommandIDs::toID(CommandIDs::NewEditor,
				    TextIDs::Lisp),
		   T("Lisp Editor"),
		   true);
      sub1.addItem(CommandIDs::toID(CommandIDs::NewEditor,
				    TextIDs::Text),
		   T("Text Editor"),
		   true);
      sub1.addSeparator();
      sub1.addItem(CommandIDs::toID(CommandIDs::NewPlotter,
					 PlotIDs::XYPlot),
		 T("XY Plot"),
		 true);
      sub1.addItem(CommandIDs::toID(CommandIDs::NewPlotter,
				    PlotIDs::MidiPlot),
		   T("Midi Plot"),
		   true);
    
      menu.addSubMenu( T("New"), sub1, true);    
      menu.addItem( CommandIDs::FileOpen,
		    T("Open..."),
		    true);
      if ( p->areRecentlyOpenedFiles() ) 
	{
	  p->addRecentlyOpenedItems(&sub3, CommandIDs::FileOpenRecent);
	  sub3.addSeparator();
	  sub3.addItem( CommandIDs::FileClearRecent, 
			T("Clear"), 
			true);
	  menu.addSubMenu( T("Open Recent"), 
			   sub3,
			   true);
	}
      menu.addSeparator();
      menu.addItem(CommandIDs::AppPreferences,
		   T("Preferences..."),
		   false);
      menu.addSeparator();
      menu.addItem(CommandIDs::AppQuit, 
		   T("Quit Grace"),
		   true);
      break;
      
    case EDITMENU :
      menu.addItem(CommandIDs::EditCopy, 
		   T("Copy"),
		   true);    
      menu.addItem(CommandIDs::EditSelectAll,
		   T("Select All"),
		   true);
      menu.addSeparator();
      menu.addItem(CommandIDs::EditClear,
		   T("Clear Console"), 
		   true);
      break;
      
    case VIEWMENU :
      {
      for (int i = 0;i<16;i++) {
        sub2.addItem(CommandIDs::ViewFontSize+i,
                     String( fontSizeList[i] ),
                     true, 
                     (getFontSize() == fontSizeList[i]));
      }
      menu.addSubMenu(T("Font Size"), sub2, true);
      for (int i=0; i<console->numThemes(); i++)
        sub1.addItem(CommandIDs::ViewSelectTheme + i,
		     console->getThemeName(i),
		     true,
		     console->isCurrentTheme(i));
      menu.addSubMenu(T("Themes"), sub1, true);
      SliderMenuComponent *sliderComp = new SliderMenuComponent(this);
      sliderComp->slider->setValue(getOpacity(), false);
      sliderComp->slider->addListener(this);
      menu.addCustomItem(CommandIDs::ViewOpacity,
			 sliderComp);
      menu.addSeparator();
      }
      break;

#ifdef SCHEME
    case PORTSMENU :
      menu=getPortsMenu();
      break;
#else
    case LISPMENU :
      menu=lisp->getLispMenu();
      break;
#endif

    case WINDOWSMENU :
      menu=app->getWindowMenu(true);
      break;
      
    case HELPMENU :
      menu=app->getHelpMenu();
      break;

    default:
      break;

    }
  return menu;
}

void ConsoleWindow::menuItemSelected (int id, int idx) 
{
  int cmd = CommandIDs::getCommand(id);
  int arg = CommandIDs::getCommandData(id);
  int type=CommandIDs::getCommandType(id);

  GraceApp * app = (GraceApp*)JUCEApplication::getInstance();
  ApplicationCommandManager * cm = app->commandManager;
  GracePreferences* p=app->getPreferences();

  //std::cout << "CommandID: " << "type=" << type << " number=" << CommandIDs::getCommandNumber(id) << " data=" << arg << "\n";

  if (type==CommandIDs::Window)
    app->performWindowCommand(id);
  else if (type==CommandIDs::Help)
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
      //std::cout << "calling performSchedulerCommand\n";
      app->schemeProcess->performSchedulerCommand(id);
      // std::cout << "after performSchedulerCommand\n";
    }
#else
  else if (type == CommandIDs::CommonLisp)  
    lisp->performLispCommand(id);
#endif
  else  // otherwise the command belongs to the Console window
    switch (cmd)
      {

      case CommandIDs::NewPlotter :
	new PlotterWindow((PlotID)arg);
	break;

      case CommandIDs::NewEditor :
	new EditorWindow((TextID)arg);
	break;
	
      case CommandIDs::FileOpen :
	{
	  FileChooser choose
	    (T("Open File"), 
	     File::getSpecialLocation(File::userHomeDirectory),
	     String::empty, true);
	  if ( choose.browseForFileToOpen() ) 
	    {
	      String f=choose.getResult().getFullPathName();
	      new EditorWindow(0, EditFlags::Load, f);
	    }
	}
	break;
	
      case CommandIDs::FileOpenRecent :
	{
	  File f=p->getRecentlyOpenedFile(arg);
	  new EditorWindow(0, EditFlags::Load, f.getFullPathName());
	}
	break;
	
      case CommandIDs::FileClearRecent :
	p->clearRecentlyOpenedFiles();
	break;
	
      case CommandIDs::AppQuit :
	app->graceQuit(true);
	break;

      case CommandIDs::EditCopy :
	consoleCopy();
	break;
	
      case CommandIDs::EditSelectAll :
	consoleSelectAll();
	break;
	
      case CommandIDs::EditClear :
	consoleClear();
	break;
	
      case CommandIDs::ViewFontSize :
	setFontSize(fontSizeList[arg]);
	break;
	
      case CommandIDs::AudioSetup: 
	//    showAudioMidiWindow();
	break;
	
      case CommandIDs::ViewSelectTheme :
	console->setTheme( arg);
	break;
	
      default :
	break;
      }
}

void ConsoleWindow::showAudioMidiWindow () {
  /*
   GraceApp * app = (GraceApp*)JUCEApplication::getInstance();
   AudioDeviceSelectorComponent audioSettingsComp (app->audioManager,
   0, 16,
   2, 16,
   false,
   false);
   audioSettingsComp.setSize (500, 300);
   DialogWindow::showModalDialog (T("Audio Settings"),
   &audioSettingsComp,
   this,
   Colour(0xffe5e5e5),
   true);
   */
}

void ConsoleWindow::doAsyncUpdate()
{
  console->triggerAsyncUpdate();
}

void ConsoleWindow::postConsoleMessage(int typ, bool trig)
{
  console->messages.lockArray();
  console->messages.add(new ConsoleMessage(typ));
  console->messages.unlockArray();
  if ( trig )
    console->triggerAsyncUpdate();
}

void ConsoleWindow::postConsoleMessage(int typ, String msg, bool trig)
{
  console->messages.lockArray();
  console->messages.add(new ConsoleMessage(typ, msg));
  console->messages.unlockArray();
  if ( trig )
    console->triggerAsyncUpdate();
}

void ConsoleWindow::postConsoleMessage(int typ, int msg, bool trig)
{
  console->messages.lockArray();
  console->messages.add(new ConsoleMessage(typ, msg));
  console->messages.unlockArray();
  if ( trig )
    console->triggerAsyncUpdate();
}

void Console::handleAsyncUpdate()
{
  GraceApp* app = (GraceApp*)JUCEApplication::getInstance();
  // this happens in the main thread
  //std::cout << "Handling " << messages.size() << " messages\n";
  for (int i=0; i<messages.size(); i++)
    {
      int cid = messages[i]->type;
      int cmd = CommandIDs::getCommand(cid);
      int arg = CommandIDs::getCommandData(cid);
      switch (cmd) 
	{

	case CommandIDs::ConsolePrintText :
	  //std::cout << "Printing message text[" << i << "]='" << messages[i]->text.toUTF8()  << "'\n";
	  display( messages[i]->text, ConsoleTheme::outputColor);
	  break;

	case CommandIDs::ConsolePrintValues :
	  display( messages[i]->text, ConsoleTheme::valueColor);
	  break;

	case CommandIDs::ConsolePrintWarning :
	  display( messages[i]->text, ConsoleTheme::warningColor);
	  break;

	case CommandIDs::ConsolePrintError :
	  display( messages[i]->text, ConsoleTheme::errorColor);
	  break;

#ifdef SCHEME	
	case CommandIDs::SchedulerScoreComplete :
	  // sent by Scheme thread only if Score Capture is on and
	  // the queue is done running processes.
	  app->midiOutPort->performAutoScoreActions();
	  break;

	case CommandIDs::MidiSeqPlay :
	case CommandIDs::MidiSeqSave :
	case CommandIDs::MidiSeqPlot :
	case CommandIDs::MidiSeqClear :
	case CommandIDs::MidiSeqCopyToTrack :
	case CommandIDs::MidiSeqRecordMidiOut :
	  app->midiOutPort->performMidiSeqCommand(cid);
	  break;

	case CommandIDs::MidiOutTuning :
	  app->midiOutPort->performMidiOutCommand(cid);
	  break;

	case CommandIDs::MidiInChannelMask :
	  app->midiInPort->setChannelMask( messages[i]->data);
	  break;

	case CommandIDs::MidiInMessageMask :
	  app->midiInPort->setMessageMask( messages[i]->data);
	  break;
#endif	  

	default:
	  std::cout << "ERROR: unhandled async message\n";
	  break;
	}
    }      
      messages.lockArray();
      messages.clear();
      messages.unlockArray();
}
