/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

#ifndef __CONSOLE__
#define __CONSOLE__

#include "juce.h"
#include "Resources.h"

// Aquamacs themes from Resources/site-lisp/color-theme-themes.gz
// As previewed in Slime repl these are the value mappings used:
//   bgColor:             background-color
//   inputColor           foreground-color
//   outputColor          font-lock-string-face
//   errorColor           {USE RED ALL THEMES?}
//   warningColor         font-lock-warning-face
//   highlightColor       region
//   highlightTextColor   region
//   caretColor:          cursor-color


class ConsoleTheme {
 public:
  enum {bgColor=0, inputColor, outputColor, errorColor, warningColor,
	hiliteColor, hiliteTextColor, caretColor};	
  String name;
  Font font;
  Colour colors[8];
  ConsoleTheme() {}
  ~ConsoleTheme() {}
  String getName() {return name;}
  void setName(String n) {name=n;}
  Font getFont() {return font;}
  void setFont(Font f) {font=f;}
  float getFontHeight() {return font.getHeight();}
  void setFontHeight(float h) {return font.setHeight(h);}
  Colour getColor(int i) {return colors[i];}
  void setColor(int i, Colour c) {colors[i]=c;}
};

class Console : public Component {
 public:
  TextEditor * buffer;
  ConsoleTheme themes[8];   // make these alloc'ed
  int curtheme;
  int numthemes;
  Console ();
  ~Console();
  void resized() {buffer->setSize(getWidth(),getHeight());}
  void paint (Graphics& g) {g.fillAll (Colours::black); }
  int numThemes() {return numthemes;}
  void initTheme(int i) ;
  void setTheme(int i);
  String getThemeName(int i) {return themes[i].name;}
  Font getThemeFont(int i) {return themes[i].font;}
  ConsoleTheme* getCurrentTheme() {return &themes[curtheme];}
  bool isCurrentTheme(int i) {return (curtheme==i);}
};

class ConsoleWindow  : public DocumentWindow,
  public MenuBarModel
{
public:

  /* Look in Plotter.h for the code that generates the enum command IDs */

  enum ConsoleCommand {
    cmdGraceEditorNew = 32896,
    cmdGraceEditorOpen = 33152,
    cmdGracePlotterNew = 33408,
    cmdGracePreferences = 33664,
    cmdGraceQuit = 33920,
    cmdEditCopy = 34176,
    cmdEditSelectAll = 34432,
    cmdViewFonts = 34688,
    cmdViewThemes = 34944,
    cmdAudioMidiSetup = 35200,
    cmdAudioAudioSetup = 35456,
    cmdLispRestart = 35712,
    cmdLispInputTracing = 35968,
    cmdLispErrorTracing = 36224,
    cmdHelpConsole = 36480,
    cmdHelpAboutGrace = 36736};

  Console * console;
  ConsoleTheme theme;
  SplashComponent * splash;
  MenuBarComponent * menubar;

  ConsoleWindow (bool dosplash) ;
  ~ConsoleWindow () ;
  void closeButtonPressed () ;
  //  void resized();
  const StringArray getMenuBarNames (MenuBarComponent* mbar);
  const PopupMenu getMenuForIndex (MenuBarComponent* mbar, int idx, 
				   const String &name);
  void menuItemSelected (MenuBarComponent* mbar, int id, int idx);

  TextEditor * getConsole();
  bool isConsoleReadOnly();
  void setConsoleReadOnly(bool b);
  void setConsoleTextColor(int c);
  void consoleClear();
  void consoleCopy();
  void consoleSelectAll();
  void consoleGotoEOB();
  void consoleTerpri();
  void consolePrint(String str);
  void consoleError(String str);
  void consoleWarning(String str);

  void installMenbar();
  void showSplash();
  void hideSplash();
  bool isSplashVisible() ;

  void showAudioMidiWindow();
};

#endif