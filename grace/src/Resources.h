/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

#ifndef RESOURCES
#define RESOURCES

#include "juce.h"

enum GraceWindowType {winConsole=1, winEditor, winPlotter};

// ENUMS defined in grace.lisp
/*

;; Items shared across different menubars. [Resource.h]
(enums 4 "SharedCommand" "WindowSelect" "WindowNative" 
       "WindowConsole" 
       "HelpWindow"
       "HelpCMDictionary"
       "HelpExamples"
       "HelpSalTutorial"
       "HelpURL"
       "HelpAboutGrace")
*/

enum SharedCommand {
  cmdWindowSelect = 130816,
  cmdWindowNative = 131072,
  cmdWindowConsole = 131328,
  cmdHelpWindow = 131584,
  cmdHelpCMDictionary = 131840,
  cmdHelpHomePages = 132096,
  cmdHelpExamples = 132352,
  cmdHelpSalTutorial = 132608,
  cmdHelpURL = 132864,
  cmdHelpAboutGrace = 133120};

void addCommonWindowItems(PopupMenu* menu, GraceWindowType w);
void addCommonHelpItems(PopupMenu* menu, GraceWindowType w);
void commonWindowItemSelected(int cmd, int arg);
void commonHelpItemSelected(int cmd, int arg);

int getHostOS();
bool isHostWindows();
bool isHostLinux();
bool isHostMacOSX();

class SplashComponent : public Component {
 public:
  Image * logo;
  static const char* grace_png;
  static const int grace_pngSize;

  SplashComponent() {
    setName("splash");
    logo = ImageCache::getFromMemory(grace_png,grace_pngSize);
  }
  ~SplashComponent() {delete logo;}

  void paint(Graphics& g) {
    //g.fillAll(Colours::yellow);
    g.fillAll(Colours::black);
    g.drawImage(logo,0,0,getWidth(), getHeight(),
		0,0,getWidth(), getHeight(), false);
  }

  void close() {
    setVisible(false);
    setSize(0,0);
    getParentComponent()->removeChildComponent(this);
  }    

  void mouseDown (const MouseEvent &e) {
    close();
  }
};


class GraceSplash  : public SplashScreen
{
public:
  GraceSplash () {};
  ~GraceSplash();
  // Binary resources:
  static const char* grace_png;
  static const int grace_pngSize;

  //    void paint (Graphics& g);
  //    void resized();
  //    juce_UseDebuggingNewOperator
  //private:
  //    GraceSplash (const GraceSplash&);
  //    const GraceSplash& operator= (const GraceSplash&);
};


#define NUM_LISPS 3

class Lisp : public XmlElement {
 public:
  Lisp (String n, String t, String o, String e, String a) ;
  ~Lisp () {}
  String getLispName () ;
  String getLispEvalArg () ;
  String getLispProgram () ;
  void setLispProgram (String e) ;
  String getLispProgramArgs () ;
  void setLispProgramArgs (String a) ;
}; 

class ASDF : public XmlElement {
 public:

  enum {Grace=0, CM}; // enums for "required" systems

  ASDF (String n, String p=String::empty,
	String o=T("asdf:load-op"), String b=String::empty,
	String a=String::empty) ;
  ~ASDF () {}
  String getPathName() ;
  void setPathName(String p) ;
  String getASDFName (bool lower=false) ;
  String getASDFFileName () ;
  String findASDFFile(File dir);
  File getDefinitionFile(File dir=File::nonexistent) ;
  String getLoadForm(String path);
};


class GracePreferences {
 public:
  PropertiesFile* propfile;
  bool loadPrefs;
  XmlElement* lisps; // initalized from property files
  XmlElement* asdfs; // initalized from property files
  RecentlyOpenedFilesList recentlyloaded;
  RecentlyOpenedFilesList recentlyopened;

  GracePreferences();
  ~GracePreferences();
  void initPreferences (String cmdlineargs);
  PropertiesFile* getProperties() {return propfile;}
  bool save();
  void print();

  // General preferences
  bool isNativeTitleBars();
  void setNativeTitleBars(bool b) ;
  bool isEmacsMode();
  void setEmacsMode(bool b);
  String getConsoleTheme() ;
  void setConsoleTheme(String t) ;
  float getConsoleFontSize() ;
  void setConsoleFontSize(float s) ;
  float getEditorFontSize() ;
  void setEditorFontSize(float s) ;

  // Recently opened and loaded files support
  void addRecentlyOpenedFile(File f) ;
  File getRecentlyOpenedFile(int i) ;
  void addRecentlyOpenedItems(PopupMenu* m, int i);
  bool areRecentlyOpenedFiles();
  void clearRecentlyOpenedFiles() ;
  void addRecentlyLoadedFile(File f) ;
  File getRecentlyLoadedFile(int i) ;
  void addRecentlyLoadedItems(PopupMenu* m, int i);
  bool areRecentlyLoadedFiles();
  void clearRecentlyLoadedFiles() ;

  // Scheme Preferences
  int getSchemeHeapSize() ;
  void setSchemeHeapSize(int size) ;
  int getSchemeStackSize() ;
  void setSchemeStackSize(int size) ;

  // Lisp Implementations support
  XmlElement* getLispImplementations();
  File getAsdfSystemsDirectory () ;
  void setAsdfSystemsDirectory (File dir) ;
  bool isLispLaunchAtStartup();
  void setLispLaunchAtStartup(bool b);

  Lisp* getLispToLaunch();
  void setLispToLaunch(Lisp* l);
  int numLisps () ;
  Lisp* getLisp (int i) ;
  int getLispIndex(Lisp* lisp) ;
  Lisp* findLisp(String name) ;

  // Lisp ASDF Systems support
  XmlElement* getAsdfSystems() ;
  void clearLispSystems() ;
  int numASDFs() ;
  ASDF* getASDF(int i) ;
  void addASDF(ASDF* a) ;
  ASDF* findASDF(String n) ;
  bool autoLoadCM();
  void setAutoLoadCM(bool b);


  juce_DeclareSingleton (GracePreferences, true);
};

#endif 
