/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

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
#endif


TransparencySlider::TransparencySlider(DocumentWindow* _window) : Slider(String::empty) {
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

void Console::handleAsyncUpdate( ) {
  // this happens in the main thread
  for (int i=0; i<messages.size(); i++)
    switch ( messages[i]->type ) {
    case ConsoleMessage::TEXT :
      display( messages[i]->text, ConsoleTheme::outputColor);
      break;
    case ConsoleMessage::VALUES :
      display( messages[i]->text, ConsoleTheme::valueColor);
      break;
    case ConsoleMessage::WARNING :
      display( messages[i]->text, ConsoleTheme::warningColor);
      break;
    case ConsoleMessage::ERROR :
      display( messages[i]->text, ConsoleTheme::errorColor);
      break;
    default:
      break;
    }
  messages.lockArray();
  messages.clear();
  messages.unlockArray();
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
    + T("\n(c) 2007 Todd Ingalls, Rick Taube\n");
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
    if (! lisp->isLoaded(p->getASDF(ASDF::CM)) ) {
      printError(">>> Error: Common Music is not loaded.\nUse Console>Lisp>Load System> to load Common Music.\n");
      return;
    }
    message=LispConnection::msgSalEval;
    code=code.replace(T("\""),T("\\\"") );
    sexpr=( T("(cm::sal ") + String("\"") + code + String("\"") );
    if ( isRegion )
      sexpr+=T(" :pattern :statement-sequence");
    sexpr+=T(")");
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

void ConsoleWindow::consoleEval (String code, bool isSal, 
				 bool isRegion) 
{
  evalnum++;
  printf("[%d] Eval: '%s'\n", evalnum, code.toUTF8());
  ((GraceApp *)GraceApp::getInstance())->schemeProcess->addNode(SchemeNode::EXPR, 0.0, code);
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
				     T("Ports"), T("Windows"), T("Help"),
				     0 };
#else
  const tchar* const menuNames[] = { T("File"), T("Edit"), T("View"),
				     T("Lisp"), T("Windows"), 
				     T("Help"), 0 };
#endif
  return StringArray((const tchar**) menuNames);
}

/*
moved to midi.cpp
const StringArray ConsoleWindow::getTuningItems () {
  const tchar* const items [] = { 
    "Semitone (100 cents)", "Quartertone (50 cents)",
    "6th tone (33.3 cents)", "8th tone (25 cents)",
    "10th tone (20 cents)", "12th tone (16.6 cents)", 
    "14th tone (14.3 cents)", "16th tone (12.5 cents)", 
    "18th tone (11.1 cents)", "20th tone (10 cents)",
    "22nd tone (9 cents)", "24th tone (8.2 cents)", 
    "26th tone (7.7 cents)", "28th tone (7.1 cents)",
    "30th tone (6.6 cents)", "32nd tone (6.25 cents)", 0 };
  return StringArray((const tchar**) items);
}
*/

const PopupMenu ConsoleWindow::getMenuForIndex (int idx,
						const String &name)
{
  GraceApp* app = (GraceApp*)JUCEApplication::getInstance();
  //  GracePreferences* p=GracePreferences::getInstance();
  GracePreferences* p=app->getPreferences();
  ApplicationCommandManager* cm = app->commandManager;

  PopupMenu menu;
  PopupMenu sub1, sub2, sub3, sub4, sub5, sub6;
  int val;
  switch (idx) {
  case GRACEMENU :
    sub1.addItem( cmdGraceEditorNew + 3, T("Sal"), true); 
    sub1.addItem( cmdGraceEditorNew + 2, T("Lisp"), true);
    sub1.addItem( cmdGraceEditorNew + 1, T("Text"), true);
    menu.addSubMenu( T("New"), sub1, true);    
    menu.addItem( cmdGraceOpenFile, T("Open..."), true);
    if ( p->areRecentlyOpenedFiles() ) {
      p->addRecentlyOpenedItems(&sub3, cmdGraceOpenRecentFile);
      sub3.addSeparator();
      sub3.addItem( cmdGraceClearRecentFiles, T("Clear"), true);
      menu.addSubMenu( T("Open Recent"), sub3, true);
    }
    menu.addSeparator();
    menu.addItem( cmdGracePreferences, T("Preferences..."), false);
    menu.addSeparator();
    menu.addItem( cmdGraceQuit, T("Quit Grace"), true);
    break;
  case EDITMENU :
    menu.addItem( cmdEditCopy, T("Copy"), true);    
    menu.addItem( cmdEditSelectAll, T("Select All"), true);
    break;
  case VIEWMENU :
    for (int i = 0;i<16;i++) {
      sub2.addItem(cmdViewFontSize+i,
		   String( fontSizeList[i] ),
		   true, 
		   (getFontSize() == fontSizeList[i])
		   );
    }
    menu.addSubMenu(T("Font Size"), sub2, true);
    for (int i=0;i<console->numThemes(); i++)
      sub1.addItem( cmdViewThemes + i,
		    console->getThemeName(i),
		    true, console->isCurrentTheme(i));
    sub1.addSeparator();
    sub1.addItem( cmdViewThemes + console->numThemes(), 
		  T("Roll Your Own..."), 
		  false);
    menu.addSubMenu( T("Themes"), sub1, true);
    {
      SliderMenuComponent *sliderComp = new SliderMenuComponent(this);
      sliderComp->slider->setValue(getOpacity(), false);
      sliderComp->slider->addListener(this);
      menu.addCustomItem( cmdViewOpacity,  sliderComp);
    }
    menu.addSeparator();
    menu.addItem( cmdViewClearText, T("Clear Console"), true);
    break;

#ifdef SCHEME
  case PORTSMENU :
    {
      // MIDI OUT MENU
      StringArray devs= MidiOutput::getDevices();
      int ndevs=devs.size();
      // warning! this activity test has to make sure no processes are
      // running either!
      bool active=app->midiOutPort->isOutputQueueActive();
      if ( ndevs == 0)
	sub1.addItem(cmdPortsMidiOutOpen, T("(no devices)"), false);
      else
	for (int i=0;i<ndevs;i++)
	  sub1.addItem(cmdPortsMidiOutOpen + i, devs[i],
		       ( ! active ),
		       app->midiOutPort->isOpen(i));
      sub1.addSeparator();
      sub1.addItem(cmdPortsMidiOutTest, T("Test Output"), ( ! active ));
      sub1.addItem(cmdPortsMidiOutHush, T("Hush"), active);
      sub1.addSeparator();
      int t= app->midiOutPort->getTuning();
      for (int i=1;i<=16;i++)
	sub5.addItem(cmdPortsMidiOutTuning+i, 
		     app->midiOutPort->getTuningName(i),
		     ( ! active ), (i==t));
      sub5.addSeparator();
      sub5.addItem(cmdPortsMidiOutDrumTrack, T("Avoid Drum Track"),
		   (t>1), app->midiOutPort->avoidDrumTrack());
      t=app->midiOutPort->getPitchBendWidth();
      for (int b=1;b<13; b++)
	sub6.addItem(cmdPortsMidiOutPitchBend+b, 
		     String(b), true, (b==t));
      sub5.addSubMenu( T("Pitch Bend Width") , sub6);      
      sub1.addSubMenu( T("Microtuning") , sub5);
      sub1.addItem(cmdPortsMidiOutInstruments, T("Instruments...."),
		   ( ! active ));
      menu.addSubMenu( T("Midi Out") , sub1);
      menu.addSeparator();
      // MIDI IN (stubbed for now)
      devs= MidiInput::getDevices();

      //      printf("isopen=%d isactive=%d\n", app->midiInPort->isOpen(),
      //	     app->midiInPort->isActive() );

      if (devs.size() == 0)
	sub2.addItem(cmdPortsMidiInOpen, T("(no devices)"), false);
      else
	for (int i=0;i<devs.size();i++)
	  sub2.addItem(cmdPortsMidiInOpen + i, devs[i],
		       // cant choose port if anything active
		       ( ! app->midiInPort->isActive(i) ) ,
		       app->midiInPort->isOpen(i) );
      sub2.addSeparator();

      sub2.addItem(cmdPortsMidiInTest, T("Test Input"),
		   // sensitive if port is open, no device activity or
		   // is same activity
		   ( app->midiInPort->isOpen() &&
		     (!app->midiInPort->isActive() ||
		      app->midiInPort->isActive(MidiInPort::TESTING) )),
		   app->midiInPort->isActive(MidiInPort::TESTING));
      
      sub2.addItem(cmdPortsMidiInRecord, T("Record Input"), 
		   // sensitive if port is open, no device activity or
		   // is same activity
		   ( app->midiInPort->isOpen() &&
		     (!app->midiInPort->isActive() ||
		       app->midiInPort->isActive(MidiInPort::RECORDING) )),
		   app->midiInPort->isActive(MidiInPort::RECORDING) );
      sub2.addItem(cmdPortsMidiInHook, T("Clear Input Hook"),
		   app->midiInPort->isActive(MidiInPort::SCHEMEHOOK) );
      sub2.addSeparator();
      sub2.addItem(cmdPortsMidiInConfigure, T("Configure..."));
      menu.addSubMenu(T("Midi In"), sub2);
      menu.addSeparator();
      sub3.addItem(1, T("New"), false);
      sub3.addItem(2, T("Delete"), false);
      sub3.addItem(3, T("Copy to Plotter"), false);
      sub3.addItem(4, T("Import..."), false);
      sub3.addItem(5, T("Save..."), false);
      menu.addSubMenu(T("Midi File"), sub3);
      menu.addSeparator();
      sub4.addItem( cmdGracePlotterNew + XYPlot, T("XY"));
      sub4.addItem( cmdGracePlotterNew + MidiPlot, T("Midi"));
      menu.addSubMenu( T("Plotter"), sub4, true);    
      menu.addSeparator();
      menu.addItem(0, T("Osc Setup..."), false);    
      //menu.addSeparator();
      menu.addItem(cmdPortsAudioSetup, T("Audio Setup..."), false);
    }
    break;
#endif

#ifndef SCHEME
  case LISPMENU :
    {
      bool running=lisp->isLispRunning();
      if ( running )
	menu.addItem( cmdLispConnect, T("Quit Lisp")); 
      else 
	menu.addItem( cmdLispConnect, T("Start Lisp"), 
		      lisp->isLispStartable()); 
      menu.addSeparator();
      // Load system
      for (int i=0; i<p->numASDFs(); i++) {
	ASDF* a=p->getASDF(i);
	sub1.addItem( cmdLispLoadRecentSystem + i,
		      a->getASDFName(), true,
		      lisp->isLoaded(a));
      }
      sub1.addSeparator();
      sub1.addItem( cmdLispLoadSystem, T("Load..."), 
		    true);
      if ( p->numASDFs() > 2 )
	sub1.addItem( cmdLispClearRecentSystems, T("Clear"),
		      running);
      menu.addSubMenu(T("Load System"), sub1, running);
      // Load File
      if ( p->areRecentlyLoadedFiles() ) {
	p->addRecentlyLoadedItems(&sub2, cmdLispLoadRecentFile);
	sub2.addSeparator();
	sub2.addItem( cmdLispLoadFile, T("Load..."), running);
	sub2.addItem( cmdLispClearRecentLoaded, T("Clear"), running);
	menu.addSubMenu(T("Load File"), sub2, running);
      }
      else
	menu.addItem( cmdLispLoadFile, T("Load File..."), running);
      menu.addSeparator();
      menu.addItem( cmdLispConfigure, T("Configure Lisp..."), true); 
    }
    break;
#endif
  case WINDOWSMENU :
    addCommonWindowItems(&menu, winConsole);
    break;
  case HELPMENU :
    addCommonHelpItems(&menu, winConsole);
    break;
  }
  return menu;
}

void ConsoleWindow::menuItemSelected (int id, int idx) {
  // lower seven bits encode command information
  int arg = id & 0x0000007F;
  int cmd = id & 0xFFFFFF80;
  GraceApp * app = (GraceApp*)JUCEApplication::getInstance();
  ApplicationCommandManager * cm = app->commandManager;
  //  GracePreferences* p=GracePreferences::getInstance();
  GracePreferences* p=app->getPreferences();
  File f;
  //printf("menubar: raw=%d command=%d data=%d\n", id, cmd, arg);
  switch (cmd) {

  case cmdGracePlotterNew :
    new PlotterWindow( (PlotType)arg);
    break;

  case cmdGraceEditorNew :
    new EditorWindow(arg);
    break;

  case cmdGraceOpenFile :
    {
      FileChooser choose
	(T("Open File"), 
	 File::getSpecialLocation(File::userHomeDirectory),
	 String::empty, true);
      if ( choose.browseForFileToOpen() ) {
	String f=choose.getResult().getFullPathName();
	new EditorWindow(0, TextBuffer::load, f);
      }
    }
    break;

  case cmdGraceOpenRecentFile :
    {
      f=p->getRecentlyOpenedFile(arg);

      new EditorWindow(0, TextBuffer::load, f.getFullPathName());
    }
    break;

  case cmdGraceClearRecentFiles :
    p->clearRecentlyOpenedFiles();
    break;

  case cmdGraceQuit :
    app->graceQuit(true);
    break;

  case cmdViewClearText :
    consoleClear();
    break;

  case cmdViewFontSize :
    setFontSize(fontSizeList[arg]);
    break;

#ifdef SCHEME

  case cmdPortsMidiOutOpen:
    app->getMidiOutPort()->open(arg);
    break;

  case cmdPortsMidiOutTest:
    app->getMidiOutPort()->testMidiOutput();
    break;

  case cmdPortsMidiOutHush :
    app->schemeProcess->stop();
    app->midiOutPort->clear();
    break;

  case cmdPortsMidiOutTuning :
    app->midiOutPort->setTuning(arg, true);
    break;

  case cmdPortsMidiOutPitchBend :
    app->midiOutPort->setPitchBendWidth(arg);
    break;

  case cmdPortsMidiOutDrumTrack :
    app->midiOutPort->
      setAvoidDrumTrack(! app->midiOutPort->avoidDrumTrack());
    break;

  case cmdPortsMidiOutInstruments :
    app->midiOutPort->showInstrumentsWindow();
    break;

  case cmdPortsMidiInOpen :
    app->midiInPort->open(arg);
    break;

  case cmdPortsMidiInTest :
    if ( app->midiInPort->isActive(MidiInPort::TESTING) )
      app->midiInPort->stopTestInput();
    else 
      app->midiInPort->startTestInput();
    break;

  case cmdPortsMidiInRecord :
    if ( app->midiInPort->isActive(MidiInPort::RECORDING) )
      app->midiInPort->stopRecordInput();
    else 
      app->midiInPort->startRecordInput();
    break;

  case cmdPortsMidiInHook :
    if ( app->midiInPort->isActive(MidiInPort::SCHEMEHOOK) )
      app->midiInPort->stopSchemeInput();
    break;

#endif

  case cmdPortsAudioSetup: 
    //    showAudioMidiWindow();
    break;

  case cmdViewThemes :
    console->setTheme( arg);
    break;


#ifndef SCHEME
  case cmdLispConnect :
    if (lisp->isLispRunning())
      lisp->stopLisp();
    else 
      lisp->startLisp();
    break;
  case cmdLispConfigure :
    showConfigureLispWindow();
    break;
  case cmdLispLoadSystem :
    lisp->chooseAndLoadASDF();
    break;
  case cmdLispLoadRecentSystem :
    lisp->loadASDF(p->getASDF(arg));
    break;
  case cmdLispClearRecentSystems :
    p->clearLispSystems();
    break;
  case cmdLispLoadFile :
    lisp->chooseAndLoadFile();
    break;
  case cmdLispLoadRecentFile :
    lisp->loadFile(p->getRecentlyLoadedFile(arg));
    break;
  case cmdLispClearRecentLoaded :
    p->clearRecentlyLoadedFiles();
    break;
#endif

  default :
    // help menu=index 5 
    if (idx==WINDOWSMENU)
      commonWindowItemSelected(cmd,arg);
    else if (idx==HELPMENU)
      commonHelpItemSelected(cmd,arg);
    break;
  }
}

void ConsoleWindow::showConfigureLispWindow () {
#ifndef SCHEME
  DialogWindow::showModalDialog (T("Configure Lisp"),
								 
				 new ConfigureLispView(lisp),
				 this,
				 Colour(0xffe5e5e5),
				 true);
#endif
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

void ConsoleWindow::doAsyncUpdate() {
  console->triggerAsyncUpdate();
}

void ConsoleWindow::postConsoleTextMessage(String msg, int typ, 
					   bool trig) {
  console->messages.lockArray();
  console->messages.add(new ConsoleMessage(typ, msg));
  console->messages.unlockArray();
  if ( trig )
    console->triggerAsyncUpdate();
}
