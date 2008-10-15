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

  // Ports Preferences
  bool getScoreCaptureMode();
  void setScoreCaptureMode(bool val);

  String getMidiOutDevice();
  void setMidiOutDevice(String name);

  int getMidiOutTuning();
  void setMidiOutTuning(int div);

  // midi in port
  String getMidiInDevice();
  void setMidiInDevice(String name);
  int getMidiInChannelMask();
  void setMidiInChannelMask(int chans);
  int getMidiInMessageMask();
  void setMidiInMessageMask(int types);


  bool getMidiSeqAutoPlay();
  void setMidiSeqAutoPlay(bool b);
  bool getMidiSeqAutoSave();
  void setMidiSeqAutoSave(bool b);
  int getMidiFileTimeDivision();
  void setMidiFileTimeDivision(int div);

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


class TextDialogComponent  : public Component,
                             public ButtonListener
{
private:
  Label* textlabel;
  TextEditor* textbuffer;
  TextButton* cancelbutton;
  TextButton* okbutton;

public:
  TextDialogComponent ()
    : textlabel (0),
      textbuffer (0),
      cancelbutton (0),
      okbutton (0)
  {
    addAndMakeVisible (textlabel = new Label (String::empty,
                                              String::empty));
    textlabel->setFont (Font (15.0000f, Font::plain));
    textlabel->setJustificationType (Justification::centredRight);
    textlabel->setEditable (false, false, false);
    textlabel->setColour (TextEditor::textColourId, Colours::black);
    textlabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
    
    addAndMakeVisible (textbuffer = new TextEditor (String::empty));
    textbuffer->setMultiLine (false);
    textbuffer->setReturnKeyStartsNewLine (false);
    textbuffer->setReadOnly (false);
    textbuffer->setScrollbarsShown (false);
    textbuffer->setCaretVisible (true);
    textbuffer->setPopupMenuEnabled (true);
    textbuffer->setText (String::empty);

    addAndMakeVisible (cancelbutton = new TextButton (String::empty));
    cancelbutton->setButtonText (T("Cancel"));
    cancelbutton->addButtonListener (this);
    addAndMakeVisible (okbutton = new TextButton (String::empty));
    okbutton->setButtonText (T("Ok"));
    okbutton->addButtonListener (this);
    setSize (300, 150);
}

  ~TextDialogComponent()
  {
    deleteAndZero (textlabel);
    deleteAndZero (textbuffer);
    deleteAndZero (cancelbutton);
    deleteAndZero (okbutton);
  }
  
  void paint (Graphics& g)
  {
    g.fillAll (Colours::white);
  }

  void resized()
  {
    textlabel->setBounds (16, 32, 88, 24);
    textbuffer->setBounds (112, 32, 160, 24);
    cancelbutton->setBounds (138 - 74, 88, 74, 24);
    okbutton->setBounds (160, 88, 74, 24);
  }

  void buttonClicked (Button* button)
  {
    if (button == cancelbutton)
      ((DialogWindow *)getTopLevelComponent())->exitModalState(false);
    else if (button == okbutton)
      ((DialogWindow *)getTopLevelComponent())->exitModalState(true);
  }
  
  static String ShowTextDialog(String title, String prompt, 
			       String text, String okname,
			       String cancelstr=String::empty )
  {
    TextDialogComponent* dialog= new TextDialogComponent();
    String str=String::empty;
    dialog->textlabel->setText(prompt,false);
    dialog->textbuffer->setText(text,false);
    dialog->textbuffer->setHighlightedRegion(0,text.length());
    if (okname != String::empty)
      dialog->okbutton->setButtonText(okname);
    int res=DialogWindow::showModalDialog(title, dialog, NULL,
					  Colour(0xffe5e5e5),
					  true, false, false);
    if (res)
      str=dialog->textbuffer->getText().trim();
    else
      str=cancelstr;
    delete dialog;
    return str;
  }
  
  String getText()
  {
    return textbuffer->getText().trim();
  }
  
  // (prevent copy constructor and operator= being generated..)
  TextDialogComponent (const TextDialogComponent&);
  const TextDialogComponent& operator= (const TextDialogComponent&);
};

#endif 
