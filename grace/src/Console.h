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

/*

;; Grace menu command IDS are organized in "menubar blocks" and have
;; their lower 7 bits available for encoding command information. each
;; menubar block has max 128 commands. Use this lisp code to generate
;; the enum definition for a menubar:

(in-package :cm)

(defun enums (block enumname &rest names)
  (let* ((cmdinfo #xFF)
         (blockwidth (* 128 cmdinfo))
	 (blockstart (* blockwidth block)))
  (format t "  enum ~A {~%" enumname)
  (loop with m = (length names)
     for n in names for i from 1
     do (if (= i 128) (error "too many commands, block size = 128"))
     (format t "    cmd~A = ~D~:[,~;};~]~%" n
	     (+ (ash i 8) blockstart)
	     (= i m)))))

(enums 1 "ConsoleCommand" "GraceEditorNew" "GracePlotterNew"
         "GraceEditorOpen" "GracePreferences" "GraceQuit"
	 "EditCopy" "EditSelectAll"
	 "ViewClearText" "ViewFontSize"  "ViewThemes" "ViewOpacity"
	 "AudioMidiSetup" "AudioAudioSetup"
	 "LispConnect" "LispLoadSystem" "LispLoadFile" 
	 "LispConfigure"
	 "HelpConsole" "HelpAboutGrace")
*/

  enum ConsoleCommand {
    cmdGraceEditorNew = 32896,
    cmdGracePlotterNew = 33152,
    cmdGraceEditorOpen = 33408,
    cmdGracePreferences = 33664,
    cmdGraceQuit = 33920,
    cmdEditCopy = 34176,
    cmdEditSelectAll = 34432,
    cmdViewClearText = 34688,
    cmdViewFontSize = 34944,
    cmdViewThemes = 35200,
    cmdViewOpacity = 35456,
    cmdAudioMidiSetup = 35712,
    cmdAudioAudioSetup = 35968,
    cmdLispConnect = 36224,
    cmdLispLoadSystem = 36480,
    cmdLispLoadFile = 36736,
    cmdLispConfigure = 36992,
    cmdHelpConsole = 37248,
    cmdHelpAboutGrace = 37504};

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
  float getFontSize();
  void setFontSize(float s);
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

};

#endif

