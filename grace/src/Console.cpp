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

/* 
 * Console Window
 */

ConsoleComponent::ConsoleComponent () {
  buffer = new TextEditor( String::empty) ;
  buffer->setMultiLine(true);
  buffer->setScrollToShowCursor(true);
  buffer->setReadOnly(true);
  buffer->setCaretVisible(false);    
  addChildComponent(buffer);
  buffer->setVisible(true);
  setVisible(true);
}

ConsoleComponent::~ConsoleComponent () {
  delete buffer;
}

ConsoleWindow::ConsoleWindow (bool dosplash)
  : DocumentWindow (String::empty , Colours::white,
		    DocumentWindow::allButtons, true ) {
  menubar = new MenuBarComponent(this);
  setMenuBar(this,0);
  console=new ConsoleComponent();
  setConsoleDefaultTheme();
  splash=new SplashComponent();
  setContentComponent(console);
  setResizable(true, true); 
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
}

ConsoleWindow::~ConsoleWindow () {

}

void ConsoleWindow::closeButtonPressed () {
  if (AlertWindow::showOkCancelBox
      (AlertWindow::QuestionIcon, T("Quit"),
       T("Really quit Grace? Any unsaved work will be lost."),
       String::empty, String::empty)
      )
    JUCEApplication::quit();
}

/*
void ConsoleWindow::resized() {
  console->buffer->setSize(getWidth(),getHeight());
  if (isSplashVisible())
    splash->setSize(getWidth(),getHeight());
}
*/


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

void ConsoleWindow::setConsoleDefaultTheme () {
  // Aquamacs theme "Clarity and Beauty" by Richard Wellum
  theme.name=T("Clarity and Beauty");
  theme.font=Font(Font::getDefaultMonospacedFontName(), 
		  17.0f, Font::plain );
  theme.setColor(ConsoleTheme::bgColor, Colours::black);
  theme.setColor(ConsoleTheme::inputColor, Colours::white);
  theme.setColor(ConsoleTheme::outputColor, Colours::lightsalmon);
  theme.setColor(ConsoleTheme::errorColor, Colours::red);
  theme.setColor(ConsoleTheme::warningColor,Colours::orange);
  theme.setColor(ConsoleTheme::hiliteColor, Colours::grey);
  theme.setColor(ConsoleTheme::hiliteTextColor, Colours::white);
  theme.setColor(ConsoleTheme::caretColor,Colours::yellow);
  applyConsoleTheme();
}

void ConsoleWindow::applyConsoleTheme() {
  console->buffer->setFont(theme.getFont());
  console->buffer->setColour( TextEditor::backgroundColourId, 
		      theme.getColor(ConsoleTheme::bgColor));
  console->buffer->setColour( TextEditor::textColourId,
		      theme.getColor(ConsoleTheme::outputColor));
  console->buffer->setColour( TextEditor::highlightColourId,
		      theme.getColor(ConsoleTheme::hiliteColor));
  console->buffer->setColour( TextEditor::highlightedTextColourId,
		      theme.getColor(ConsoleTheme::hiliteTextColor));
  console->buffer->setColour( TextEditor::caretColourId,
		      theme.getColor(ConsoleTheme::caretColor));
  console->buffer->applyFontToAllText(theme.getFont());
}

void ConsoleWindow::setConsoleTextColor (int c) {
  console->buffer->setColour( TextEditor::textColourId,
			      theme.getColor(c));
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

void ConsoleWindow::consolePrint( String str) {
  printf("printing\n");
  setConsoleTextColor(ConsoleTheme::outputColor);
  console->buffer->insertTextAtCursor(str);
}

void ConsoleWindow::consoleError( String str) {
  setConsoleTextColor(ConsoleTheme::errorColor);
  console->buffer->insertTextAtCursor(str);
}

void ConsoleWindow::consoleWarning( String str) {
  setConsoleTextColor(ConsoleTheme::warningColor);
  console->buffer->insertTextAtCursor(str);
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
  printf("here1 \n");
  return StringArray((const tchar**) menuNames);
}


const PopupMenu ConsoleWindow::getMenuForIndex (MenuBarComponent* mbar,
						int idx,
						const String &name)
{
  PopupMenu menu;
  PopupMenu sub1, sub2, sub3;
  int val;



  switch (idx) {
  case 0 :
    menu.addItem( cmdGraceEditorNew, T("New Editor"), true);    
    sub1.addItem( cmdGracePlotterNew + XYPlot, T("XY"));
    sub1.addItem( cmdGracePlotterNew + XYZPlot, T("XYZ"), false);
    sub1.addItem( cmdGracePlotterNew + MidiPlot, T("Midi"));
    sub1.addItem( cmdGracePlotterNew + VKeyPlot, T("Fomus"), false);
    sub1.addItem( cmdGracePlotterNew + FomusPlot, T("Vkey"), false);
    sub1.addItem( cmdGracePlotterNew + CLMPlot, T("CLM"), false);
    menu.addSubMenu( T("New Plotter"), sub1, true);    
    menu.addSeparator();
    menu.addItem( cmdGraceEditorOpen, T("Open..."), true);
    menu.addSeparator();
    sub1.addItem( cmdGracePreferences, T("Preferences..."), false);
    menu.addSeparator();
    menu.addItem( cmdGraceQuit, T("Quit Grace"), true);
    break;
  case 1 :
    menu.addItem( cmdEditCopy, T("Copy"), true);    
    menu.addItem( cmdEditSelectAll, T("Select All"), true);
    break;
  case 2 :
    menu.addItem( cmdViewFonts, T("Show Fonts..."), false);    
    menu.addSeparator();
    sub1.addItem( cmdViewThemes + 1, T("Clarity and Beauty"), true, true);
    sub1.addItem( cmdViewThemes + 2, T("Gnome"), false);
    sub1.addItem( cmdViewThemes + 3, T("Deep Blue"), false);
    sub1.addItem( cmdViewThemes + 4, T("Snowish"), false);
    sub1.addItem( cmdViewThemes + 5, T("Standard Emacs"), false);
    sub1.addItem( cmdViewThemes + 6, T("Standard XEmacs"), false);
    sub1.addSeparator();
    sub1.addItem( cmdViewThemes + 7, T("Roll your Own..."), 
		  false);
    menu.addSubMenu( T("Themes"), sub1, true);
    break;
  case 3 :
    menu.addItem( cmdAudioMidiSetup, T("Midi Setup..."), false); 
    menu.addItem( cmdAudioAudioSetup, T("Audio Setup..."), false); 
    break;
  case 4 :
    menu.addItem( cmdLispRestart, T("Restart"), false); 
    menu.addItem( cmdLispInputTracing, T("Trace Input"), false); 
    menu.addItem( cmdLispErrorTracing, T("Trace Errors"), false); 
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
    ApplicationCommandManager * cm
      = ((GraceApp*)JUCEApplication::getInstance())->commandManager;

  printf("menubar: raw=%d command=%d data=%d\n", id, cmd, arg);

  switch (cmd) {
  case cmdGracePlotterNew :
    new PlotterWindow( (PlotType)arg);
    break;
  case cmdGraceEditorNew :
    // doesnt work
    //cm->invokeDirectly(TextBuffer::cmdNew,false);
    new EditorWindow( File( T("untitled.sal")) );
    break;
  case cmdGraceEditorOpen :
    // doesnt work
    //cm->invokeDirectly(TextBuffer::cmdOpen,false);
    break;
  default :
    break;
  }
}
