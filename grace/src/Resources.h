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

enum SharedCommand {
  cmdWindowSelect = 130816,
  cmdWindowNative = 131072,
  cmdWindowConsole = 131328,
  cmdHelpWindow = 131584,
  cmdHelpSalTutorial = 131840,
  cmdHelpURL = 132096,
  cmdHelpAboutGrace = 132352};

void addCommonWindowItems(PopupMenu* menu, GraceWindowType w);
void addCommonHelpItems(PopupMenu* menu, GraceWindowType w);
void commonWindowItemSelected(int cmd, int arg);
void commonHelpItemSelected(int cmd, int arg);

File getGraceResourceDirectory ();
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
  XmlElement* lisps; // initalized from property files
  XmlElement* asdfs; // initalized from property files
  GracePreferences();
  ~GracePreferences();

  PropertiesFile* getProperties() {return propfile;}
  bool isNativeTitleBars();
  void setNativeTitleBars(bool b);
  bool save();
  void initPropertiesFile ();

  // Lisp Implementations support
  XmlElement* getLispImplementations();
  File getLispSystemsDirectory () ;
  void setLispSystemsDirectory (File dir) ;
  bool isLispLaunchAtStartup();
  void setLispLaunchAtStartup(bool b);

  Lisp* getLispToLaunch();
  void setLispToLaunch(Lisp* l);
  int numLisps () ;
  Lisp* getLisp (int i) ;
  int getLispIndex(Lisp* lisp) ;
  Lisp* findLisp(String name) ;
  // Lisp ASDF Systems

  XmlElement* getLispSystems() ;
  int numASDFs() ;
  ASDF* getASDF(int i) ;
  void addASDF(ASDF* a) ;
  ASDF* findASDF(String n) ;

  juce_DeclareSingleton (GracePreferences, true);
};

#endif 
