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
#include "Lisp.h"

// Aquamacs themes from Resources/site-lisp/color-theme-themes.gz
// As previewed in Slime repl these are the value mappings used:
//   bgColor:             background-color
//   inputColor           foreground-color
//   outputColor          font-lock-string-face
//   errorColor           {USE RED ALL THEMES?}
//   warningColor         font-lock-warning-face
//   valueColor           green3
//   highlightColor       region
//   highlightTextColor   region
//   caretColor:          cursor-color

class TransparencySlider : public Slider
{
public:
  TransparencySlider(DocumentWindow* _window);
  ~TransparencySlider();
  DocumentWindow *window;
};

//class TransparencySliderListener : public SliderListener
//{
//public:
//  TransparencySliderListener();
//  ~TransparencySliderListener();
//  void sliderValueChanged(Slider * slider);
//
//}; 

class SliderMenuComponent : public PopupMenuCustomComponent
{
public:
  SliderMenuComponent(DocumentWindow* _window);
  ~SliderMenuComponent();
  TransparencySlider *slider;
  void getIdealSize(int &idealWidth, int &idealHeight);
};



class ConsoleTheme {
 public:
  enum ColorType {bgColor=0, inputColor, outputColor, errorColor, warningColor,
		  valueColor, hiliteColor, hiliteTextColor, caretColor};	
  String name;
  Font font;
  Colour colors[9];
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
  CriticalSection * lock;
  Console ();
  ~Console();
  void resized() {buffer->setSize(getWidth(),getHeight());}
  void paint (Graphics& g) {g.fillAll (Colours::transparentBlack); }
  int numThemes() {return numthemes;}
  void initTheme(int i) ;
  void setTheme(int i);
  String getThemeName(int i) {return themes[i].name;}
  Font getThemeFont(int i) {return themes[i].font;}
  ConsoleTheme* getCurrentTheme() {return &themes[curtheme];}
  bool isCurrentTheme(int i) {return (curtheme==i);}
};

class ConsoleWindow  : public DocumentWindow,
  public MenuBarModel,
  public SliderListener
{
public:

  /* See Plotter.h for the code that generates these enum command IDs */

  enum ConsoleCommand {
    cmdGraceEditorNew = 32896,
    cmdGracePlotterNew = 33152,
    cmdGraceEditorOpen = 33408,
    cmdGracePreferences = 33664,
    cmdGraceQuit = 33920,
    cmdEditCopy = 34176,
    cmdEditSelectAll = 34432,
    cmdViewFonts = 34688,
    cmdViewThemes = 34944,
    cmdConsoleTransparency = 35200,
    cmdAudioMidiSetup = 35456,
    cmdAudioAudioSetup = 35712,
    cmdLispConnect = 35968,
    cmdLispConfigure = 36224,
    cmdLispCompileFile = 36480,
    cmdLispLoadFile = 36736,
    cmdLispLoadSystem = 36992,
    cmdHelpConsole = 37248,
    cmdHelpAboutGrace = 37504
  };


  Console * console;
  ConsoleTheme theme;
  SplashComponent * splash;
  MenuBarComponent * menubar;
  LispConnection * lisp;

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
  void display(String str,
	       ConsoleTheme::ColorType typ=ConsoleTheme::outputColor);
  void consoleTerpri();  
  void consoleFreshLine();
  void consolePrint(String str, 
		    ConsoleTheme::ColorType typ=ConsoleTheme::outputColor,
		    bool eob=true);
  void consolePrintWarning( String str,  bool eob=true);
  void consolePrintError( String str,  bool eob=true);
  void consolePrintValues( String str,  bool eob=true);  
  void consoleEval(String code, bool isSal);
  void installMenbar();
  void showSplash();
  void hideSplash();
  bool isSplashVisible() ;

  void showAudioMidiWindow();
  void showConfigureLispWindow();

  double currentTransparency;
  //TransparencySliderListener * sliderListener;  
  void sliderValueChanged(Slider * slider);
  double getOpacity(){return currentTransparency;}
  void setOpacity(double o) {currentTransparency=o;}

};

#endif

