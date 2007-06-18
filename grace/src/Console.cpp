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


TransparencySlider::TransparencySlider(DocumentWindow* _window) : Slider(String::empty)
{
  window = _window;
  setRange(10, 100, 0);
  setSliderStyle(Slider::LinearHorizontal);
  setTextBoxStyle(Slider::TextBoxLeft, false, 80, 20);
  setValue(100.0);
}

TransparencySlider::~TransparencySlider()
{
}

TransparencySliderListener::TransparencySliderListener() : SliderListener()
{
}

TransparencySliderListener::~TransparencySliderListener()
{
}

void TransparencySliderListener::sliderValueChanged(Slider *slider)
{
  TransparencySlider *tslider = (TransparencySlider*)slider;
  ConsoleWindow *win = (ConsoleWindow*)(tslider->window);
  ConsoleTheme *theme = win->console->getCurrentTheme();
  Colour bgcolor = win->getBackgroundColour();
  Colour teditColor = theme->getColor(ConsoleTheme::bgColor);
  
  double val = slider->getValue();
  win->setBackgroundColour( bgcolor.withAlpha( (float) (val / 100.5) ));
  theme->setColor(ConsoleTheme::bgColor, teditColor.withAlpha( (float) (val / 100.5) ));
  win->currentTransparency = val;
  
}


SliderMenuComponent::SliderMenuComponent(DocumentWindow* _window) : PopupMenuCustomComponent(true)
{
  addAndMakeVisible (slider = new TransparencySlider (_window));
  slider->setValue(100.0);
  slider->setBounds(0, 0, 300, 24);
}

SliderMenuComponent::~SliderMenuComponent()
{
  delete slider;
}

void SliderMenuComponent::getIdealSize(int &idealWidth, int &idealHeight)
{
  idealWidth = 300;
  idealHeight = 24;
}


Console::Console () : 
  numthemes (0),
  curtheme (0)
{
  buffer = new TextEditor( String::empty) ;
  buffer->setMultiLine(true);
  buffer->setScrollToShowCursor(true);
  buffer->setReadOnly(true);
  buffer->setCaretVisible(false);    
  addChildComponent(buffer);
  numthemes=6;
  for (int i=0; i<numthemes; i++)
    initTheme(i);

  setTheme(0);
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

  Font f=Font(Font::getDefaultMonospacedFontName(), 
	      17.0f, Font::plain );
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
    r=0xeedc82;  h=0x2f4f4f;  c=0xcd0000;
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
  themes[idx].font=f;
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
  curtheme=i;
  printf("current theme: %s\n", themes[i].name.toUTF8());
  buffer->setFont( themes[i].getFont() );
  buffer->setColour( TextEditor::backgroundColourId, 
		     themes[i].getColor(ConsoleTheme::bgColor));
  buffer->setColour( TextEditor::textColourId,
		     themes[i].getColor(ConsoleTheme::outputColor));
  buffer->setColour( TextEditor::highlightColourId,
		     themes[i].getColor(ConsoleTheme::hiliteColor));
  buffer->setColour( TextEditor::highlightedTextColourId,
		     themes[i].getColor(ConsoleTheme::hiliteTextColor));
  buffer->setColour( TextEditor::caretColourId,
		     themes[i].getColor(ConsoleTheme::caretColor));
  buffer->applyFontToAllText(themes[i].getFont());
}

ConsoleWindow::ConsoleWindow (bool dosplash)
  : DocumentWindow ( T("Console") , Colours::white,
		     DocumentWindow::allButtons, true ),
    lisp (0)
{
  lisp = new LispConnection(this);
  menubar = new MenuBarComponent(this);
  setMenuBar(this,0);
  console=new Console();
  splash=new SplashComponent();
  setContentComponent(console);
  setResizable(true, true); 
  setAlwaysOnTop(true);
  setVisible(true);
  console->buffer->setVisible(true);
  setVisible(true);
  centreWithSize (450, 375);
  if (dosplash) {
    showSplash();
    splash->fadeOutComponent(4000);
    if ( isSplashVisible() ) // user might have clicked
      hideSplash();
  }
  sliderListener = new TransparencySliderListener();
  currentTransparency = 100.0;

}

ConsoleWindow::~ConsoleWindow () {
  // this will be called by GraceApp
  if ( lisp->isLispRunning() )
    lisp->killLisp();
  delete lisp;
}

void ConsoleWindow::closeButtonPressed () {
  GraceApp * app = (GraceApp*)JUCEApplication::getInstance();
  app->graceQuit(true);
}

/*
 * Console specific methods
 */

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

void ConsoleWindow::consoleTerpri() {
  console->buffer->insertTextAtCursor(T("\n"));
}

void ConsoleWindow::consoleFreshLine() {
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

void ConsoleWindow::consolePrint( String str, ConsoleTheme::ColorType typ,
				  bool eob) {

  console->lock->enter();
  if (eob) consoleGotoEOB();
  setConsoleTextColor(typ);
  console->buffer->insertTextAtCursor(str);
  console->lock->exit();
}

void ConsoleWindow::consolePrintWarning( String str,  bool eob) {
  consolePrint(str, ConsoleTheme::warningColor, eob);
}

void ConsoleWindow::consolePrintError( String str,  bool eob) {
  consolePrint(str, ConsoleTheme::errorColor, eob);
}



void ConsoleWindow::consoleEval (String code, bool isSal) {
  // HACK display until eval is tied in
  //  consolePrint(code, ConsoleTheme::inputColor);
  //consoleTerpri();
  if( !isSal )
    lisp->sendLispSexpr(code);
  else
    printf("sending sal not supported yet!\n");
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

const StringArray ConsoleWindow::getMenuBarNames (MenuBarComponent* mbar) {
  const tchar* const menuNames[] = { T("Grace"), T("Edit"), T("View"),
				     T("Audio"), T("Lisp"), T("Help"), 0 };
  return StringArray((const tchar**) menuNames);
}

const PopupMenu ConsoleWindow::getMenuForIndex (MenuBarComponent* mbar,
						int idx,
						const String &name)
{
  PopupMenu menu;
  PopupMenu sub1, sub2, sub3, sub4;
  int val;
  SliderMenuComponent *sliderComp = new SliderMenuComponent(this);
  sliderComp->slider->setValue(currentTransparency);
  sliderComp->slider->addListener(sliderListener);
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
    menu.addItem( cmdGraceEditorOpen, T("Open File..."), true);
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
    
    sub4.addCustomItem( cmdConsoleTransparency,  sliderComp);
    
    menu.addItem( cmdViewFonts, T("Show Fonts..."), false);    
    menu.addSeparator();
    for (int i=0;i<console->numThemes(); i++)
      sub1.addItem( cmdViewThemes + i, console->getThemeName(i),
		    true, console->isCurrentTheme(i));
    sub1.addSeparator();
    sub1.addItem( cmdViewThemes + console->numThemes(), 
		  T("Roll Your Own..."), 
		  false);
    menu.addSubMenu( T("Themes"), sub1, true);
    menu.addSubMenu( T("Console Transparency"), sub4, true);
    break;
  case 3 :
    menu.addItem( cmdAudioMidiSetup, T("Midi Setup..."), true); 
    menu.addItem( cmdAudioAudioSetup, T("Audio Setup..."), true); 
    break;
  case 4 :
    if ( lisp->isLispRunning() )
      menu.addItem( cmdLispConnect, T("Stop Lisp")); 
    else 
      menu.addItem( cmdLispConnect, T("Start Lisp"), 
		    lisp->isLispStartable()); 
    menu.addItem( cmdLispConfigure, T("Configure..."), 
		  (! lisp->isLispRunning() )
		  ); 
    menu.addSeparator();
    menu.addItem( cmdLispCompileFile, T("Compile File..."), false);
    menu.addItem( cmdLispLoadFile, T("Load File..."), false);
    menu.addItem( cmdLispLoadSystem, T("Load System..."), false);
    break;
  case 5 :
    menu.addItem( cmdHelpConsole, T("Console Help"), false); 
    menu.addItem( cmdHelpAboutGrace, T("About Grace"), false); 
    break;
  }
  return menu;
}

void ConsoleWindow::menuItemSelected (MenuBarComponent* mbar, int id, int idx)
{
  // lower seven bits may encode command information
  int arg = id & 0x0000007F;
  int cmd = id & 0xFFFFFF80;
  GraceApp * app = (GraceApp*)JUCEApplication::getInstance();
  ApplicationCommandManager * cm = app->commandManager;

  //printf("menubar: raw=%d command=%d data=%d\n", id, cmd, arg);

  switch (cmd) {
  case cmdGracePlotterNew :
    new PlotterWindow( (PlotType)arg);
    break;
  case cmdGraceEditorNew :
    // doesnt work
    //cm->invokeDirectly(TextBuffer::cmdNew,false);
    new EditorWindow(arg);
    break;
  case cmdGraceEditorOpen :
    // doesnt work
    //cm->invokeDirectly(TextBuffer::cmdOpen,false);
    {
      FileChooser choose (T("Open File"), 
			  File::getSpecialLocation(File::userHomeDirectory),
			  String::empty, true);
      if ( choose.browseForFileToOpen() )
	new EditorWindow(0, TextBuffer::load,
                       choose.getResult().getFullPathName());

    }
    break;
  case cmdAudioMidiSetup: 
  case cmdAudioAudioSetup: 
    showAudioMidiWindow();
    break;
  case cmdGraceQuit :
    app->graceQuit(true);
    break;
  case cmdViewThemes :
    console->setTheme( arg);
    break;
  case cmdLispConnect :
    if (lisp->isLispRunning()) {
      //lisp->killLisp();
      lisp->sendLispSexpr( T("(kill-server)\n") );
      lisp->disconnect();
    }
    else 
      lisp->startLisp();
    break;
  case cmdLispConfigure :
    showConfigureLispWindow();
    break;
  default :
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
