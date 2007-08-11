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
#include "Audio.h"
#include "Lisp.h"


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
  uint32 b, i, o, r, h, c;

  //Font f=Font(Font::getDefaultMonospacedFontName(), 
  //	      17.0f, Font::plain );
  // make value, warning and error colors consistent across themes (?)
  uint32 v= 0x00cd00, w=0xff8c00, e=0xcd0000;

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

ConsoleWindow::ConsoleWindow (bool dosplash)
  : DocumentWindow ( T("Console") , Colours::white,
		     DocumentWindow::allButtons, true ),
    lisp (0),
    currentTransparency (100.0)
{
  lisp = new LispConnection(this);
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
  if (p->isLispLaunchAtStartup())
    lisp->startLisp();
}

ConsoleWindow::~ConsoleWindow () {
  // this will be called by GraceApp
  if ( lisp->isLispRunning() )
    lisp->stopLisp();
  delete lisp;
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

void ConsoleWindow::consoleGotoEOB() {
  console->buffer->setCaretPosition(0xFFFFFF);
}

void ConsoleWindow::terpri() {
  console->buffer->insertTextAtCursor(T("\n"));
}

void ConsoleWindow::freshLine() {
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

void ConsoleWindow::display( String str, ConsoleTheme::ColorType typ) {
  console->lock->enter();
  consoleGotoEOB();
  setConsoleTextColor(typ);
  console->buffer->insertTextAtCursor(str);
  console->lock->exit();
}

void ConsoleWindow::printMessage( String str, ConsoleTheme::ColorType typ,
				  bool eob) {
  console->lock->enter();
  //ConsoleWindow* win=((ConsoleWindow*)getTopLevelComponent());
  //toFront();
  if (eob) consoleGotoEOB();
  setConsoleTextColor(typ);
  console->buffer->insertTextAtCursor(str);
  console->lock->exit();
}

void ConsoleWindow::printWarning( String str,  bool eob) {
  freshLine();
  printMessage(str, ConsoleTheme::warningColor, eob);
}

void ConsoleWindow::printError( String str,  bool eob) {
  freshLine();
  printMessage(str, ConsoleTheme::errorColor, eob);
}

void ConsoleWindow::printValues( String str,  bool eob) {
  freshLine();
  printMessage(str, ConsoleTheme::valueColor, eob);
}

float ConsoleWindow::getFontSize( ) {
  return getConsole()->getFont().getHeight();
}

void ConsoleWindow::setFontSize( float size ) {
  printf("fontsize=%f\n", size);
  GracePreferences* p=GracePreferences::getInstance();
  TextEditor* ed=getConsole();
  Font font=ed->getFont();
  font.setHeight(size);
  ed->applyFontToAllText(font);
  p->setConsoleFontSize(size);
}

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
      printError(">>> SAL: Common Music is not loaded.\nUse Console>Lisp>Load System> to load Common Music.\n");
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
  const tchar* const menuNames[] = { T("Grace"), T("Edit"), T("View"),
				     T("Audio"), T("Lisp"), 
				     T("Windows"), T("Help"), 0 };
  return StringArray((const tchar**) menuNames);
}

const PopupMenu ConsoleWindow::getMenuForIndex (int idx,
						const String &name)
{
  GraceApp* app = (GraceApp*)JUCEApplication::getInstance();
  //  GracePreferences* p=GracePreferences::getInstance();
  GracePreferences* p=app->getPreferences();
  ApplicationCommandManager* cm = app->commandManager;

  PopupMenu menu;
  PopupMenu sub1, sub2, sub3, sub4;
  int val;
  switch (idx) {
  case 0 :
    // should make syntaxId enum global !!
    sub1.addItem( cmdGraceEditorNew + 3, T("Sal"), true); 
    sub1.addItem( cmdGraceEditorNew + 2, T("Lisp"), true);
    sub1.addItem( cmdGraceEditorNew + 1, T("Text"), true);
    menu.addSubMenu( T("New Editor"), sub1, true);    
    sub2.addItem( cmdGracePlotterNew + XYPlot, T("XY"));
    sub2.addItem( cmdGracePlotterNew + MidiPlot, T("Midi"));
    sub2.addItem( cmdGracePlotterNew + VKeyPlot, T("Fomus"), false);
    sub2.addItem( cmdGracePlotterNew + FomusPlot, T("Vkey"), false);
    sub2.addItem( cmdGracePlotterNew + SpearPlot, T("Spear"), false);
    sub2.addItem( cmdGracePlotterNew + CLMPlot, T("CLM"), false);
    menu.addSubMenu( T("New Plotter"), sub2, true);    

    menu.addSeparator();
    menu.addItem( cmdGraceOpenFile, T("Open File..."), true);
    if ( p->areRecentlyOpenedFiles() ) {
      printf("in fill menu, are recently edited files\n");
      p->addRecentlyOpenedItems(&sub3, cmdGraceOpenRecentFile);
      sub3.addSeparator();
      sub3.addItem( cmdGraceClearRecentFiles, T("Clear"), true);
      menu.addSubMenu( T("Open Recent"), sub3, true);
    }
    else
      printf("in fill menu, NO recently edited files\n");

    menu.addSeparator();
    menu.addItem( cmdGracePreferences, T("Preferences..."), false);
    menu.addSeparator();
    menu.addItem( cmdGraceQuit, T("Quit Grace"), true);
    break;
  case 1 :
    menu.addItem( cmdEditCopy, T("Copy"), true);    
    menu.addItem( cmdEditSelectAll, T("Select All"), true);
    break;
  case 2 :
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
  case 3 :
    menu.addItem(cmdAudioMidiSetup, T("Midi Setup..."), true);
    menu.addItem(cmdAudioAudioSetup, T("Audio Setup..."),true);
    break;
  case 4 :
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
  case 5 :
    addCommonWindowItems(&menu, winConsole);
    break;
  case 6 :
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
      FileChooser choose (T("Open File"), 
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

  case cmdAudioMidiSetup: 
  case cmdAudioAudioSetup: 
    showAudioMidiWindow();
    break;

  case cmdViewThemes :
    console->setTheme( arg);
    break;

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

  default :
    // help menu=index 5 
    if (idx==5)
      commonWindowItemSelected(cmd,arg);
    else if (idx==6)
      commonHelpItemSelected(cmd,arg);
    break;
  }
}

void ConsoleWindow::showConfigureLispWindow () {
  DialogWindow::showModalDialog (T("Configure Lisp"),
				 new ConfigureLispView(lisp),
				 this,
				 Colour(0xffe5e5e5),
				 true);
}

void ConsoleWindow::showAudioMidiWindow () {
  GraceApp * app = (GraceApp*)JUCEApplication::getInstance();
  AudioDeviceSelectorComponent audioSettingsComp (app->audioManager,
						  0, 16,
						  2, 16,
						  true);
  audioSettingsComp.setSize (500, 300);
  DialogWindow::showModalDialog (T("Audio Settings"),
				 &audioSettingsComp,
				 this,
				 Colour(0xffe5e5e5),
				 true);
}
