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


#ifndef SCHEME

#include "Lisp.h"
#else
#include "Scheme.h"
#include "MidiReceiveComponent.h"
#endif

class MidiReceiveComponent;
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
  enum ColorType {bgColor=0, inputColor, outputColor, errorColor,
		  warningColor, valueColor, hiliteColor, hiliteTextColor,
		  caretColor};	
  String name;
  //Font font;
  Colour colors[9];
  ConsoleTheme() {}
  ~ConsoleTheme() {}
  String getName() {return name;}
  void setName(String n) {name=n;}
  //Font getFont() {return font;}
  //void setFont(Font f) {font=f;}
  //float getFontHeight() {return font.getHeight();}
  //void setFontHeight(float h) {return font.setHeight(h);}
  Colour getColor(int i) {return colors[i];}
  void setColor(int i, Colour c) {colors[i]=c;}
};

class ConsoleMessage {
 public:
  enum {TEXT, VALUES, WARNING, ERROR};
  int type;
  String text;
  ConsoleMessage(int typ, String txt) {
    type=typ;
    text=txt;
  }
  ~ConsoleMessage() {}
};

class Console : public Component,
  public AsyncUpdater
{
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
  ConsoleTheme* getTheme(int i){return &themes[i];}
  ConsoleTheme* getCurrentTheme() {return getTheme(curtheme);}
  int findTheme(String name) {
    for (int i=0; i<numThemes(); i++)
      if (getThemeName(i) == name) return i;
    return -1;
  }
  bool isCurrentTheme(int i) {return (curtheme==i);}

  OwnedArray<ConsoleMessage, CriticalSection> messages;
  void handleAsyncUpdate() ;
  void display(String str, ConsoleTheme::ColorType col);
};

class ConsoleWindow  : public DocumentWindow,
  public MenuBarModel,
  public SliderListener
{
public:
  /*    enums() defined in grace.lisp */
  /*    (enums 1 "ConsoleCommand" "GraceEditorNew" "GracePlotterNew"
         "GraceOpenFile" "GraceOpenRecentFile" "GraceClearRecentFiles"
	 "GracePreferences" "GraceQuit"
	 "EditCopy" "EditSelectAll"
	 "ViewClearText" "ViewFontSize"  "ViewThemes" "ViewOpacity"
	 "PortsMidiOutOpen" "PortsMidiOutTest" "PortsMidiOutHush"
	 "PortsMidiOutAllNotesOff"
	 "PortsMidiOutTuning" "PortsMidiOutDrumTrack"
	 "PortsMidiOutPitchBend" 
	 "PortsMidiOutWrite" "PortsMidiOutClear" "PortsMidiOutDisplay"
	 "PortsMidiOutInstruments"
	 "PortsMidiInOpen" "PortsMidiInTest" "PortsMidiInHook"
	 "PortsMidiInRecord" "PortsMidiInConfigure"
	 "PortsCsoundOpen" "PortsCsoundClose"
	 "PortsCsoundWrite" "PortsCsoundAbortWrite"
	 "PortsCsoundPlay" "PortsCsoundImport"
	 "PortsCsoundExport" "PortsCsoundPrint" "PortsCsoundDisplay"
	 "PortsCsoundClear"
	 "PortsCsoundScoreMode" "PortsCsoundRecordMode"
	 "PortsCsoundTraceMode"
	 "PortsAudioSetup"
	 "LispConnect" 
	 "LispLoadSystem" "LispLoadRecentSystem"
	 "LispClearRecentSystems"
	 "LispLoadFile" "LispLoadRecentFile" "LispCompileFile" 
	 "LispClearRecentLoaded" "LispConfigure")  */

   enum ConsoleCommand {
    cmdGraceEditorNew = 32896,
    cmdGracePlotterNew = 33152,
    cmdGraceOpenFile = 33408,
    cmdGraceOpenRecentFile = 33664,
    cmdGraceClearRecentFiles = 33920,
    cmdGracePreferences = 34176,
    cmdGraceQuit = 34432,
    cmdEditCopy = 34688,
    cmdEditSelectAll = 34944,
    cmdViewClearText = 35200,
    cmdViewFontSize = 35456,
    cmdViewThemes = 35712,
    cmdViewOpacity = 35968,
    cmdPortsMidiOutOpen = 36224,
    cmdPortsMidiOutTest = 36480,
    cmdPortsMidiOutHush = 36736,
    cmdPortsMidiOutAllNotesOff = 36992,
    cmdPortsMidiOutTuning = 37248,
    cmdPortsMidiOutDrumTrack = 37504,
    cmdPortsMidiOutPitchBend = 37760,
    cmdPortsMidiOutWrite = 38016,
    cmdPortsMidiOutClear = 38272,
    cmdPortsMidiOutDisplay = 38528,
    cmdPortsMidiOutInstruments = 38784,
    cmdPortsMidiInOpen = 39040,
    cmdPortsMidiInTest = 39296,
    cmdPortsMidiInHook = 39552,
    cmdPortsMidiInRecord = 39808,
    cmdPortsMidiInConfigure = 40064,
    cmdPortsCsoundOpen = 40320,
    cmdPortsCsoundClose = 40576,
    cmdPortsCsoundWrite = 40832,
    cmdPortsCsoundAbortWrite = 41088,
    cmdPortsCsoundPlay = 41344,
    cmdPortsCsoundImport = 41600,
    cmdPortsCsoundExport = 41856,
    cmdPortsCsoundPrint = 42112,
    cmdPortsCsoundDisplay = 42368,
    cmdPortsCsoundClear = 42624,
    cmdPortsCsoundScoreMode = 42880,
    cmdPortsCsoundRecordMode = 43136,
    cmdPortsCsoundTraceMode = 43392,
    cmdPortsAudioSetup = 43648,
    cmdLispConnect = 43904,
    cmdLispLoadSystem = 44160,
    cmdLispLoadRecentSystem = 44416,
    cmdLispClearRecentSystems = 44672,
    cmdLispLoadFile = 44928,
    cmdLispLoadRecentFile = 45184,
    cmdLispCompileFile = 45440,
    cmdLispClearRecentLoaded = 45696,
    cmdLispConfigure = 45952};

#ifdef SCHEME
  enum {GRACEMENU, EDITMENU, VIEWMENU, PORTSMENU, WINDOWSMENU, HELPMENU};
#else
  enum {GRACEMENU, EDITMENU, VIEWMENU, LISPMENU, WINDOWSMENU, HELPMENU};
#endif

  Console * console;
  ConsoleTheme theme;
  SplashComponent * splash;
  MenuBarComponent * menubar;

 

#ifndef SCHEME
  LispConnection * lisp;
#endif
  int evalnum;
  ConsoleWindow (bool dosplash) ;
  ~ConsoleWindow () ;
  void closeButtonPressed () ;
  //  void resized();
  const StringArray getMenuBarNames ();
  const PopupMenu getMenuForIndex (int idx, const String &name);
  void menuItemSelected (int id, int idx);

  TextEditor * getConsole();
  bool isConsoleReadOnly();
  void setConsoleReadOnly(bool b);
  void setConsoleTextColor(int c);
  float getFontSize();
  void setFontSize(float s);
  void consoleClear();
  void consoleCopy();
  void consoleSelectAll();
  void gotoEOB();

  void terpri();  
  void freshLine();
  void printBanner();
  void printMessage(String str, bool redraw=false);
  void printWarning(String str, bool redraw=false);
  void printError(String str, bool redraw=false);
  void printValues(String str, bool redraw=false);  

  void consoleEval(String code, bool isSal, bool region);
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

  void postConsoleTextMessage(String msg, int typ=ConsoleMessage::TEXT,
			      bool dotrig=true);
  void doAsyncUpdate() ;

};

#endif

