/*=======================================================================*
  Copyright (C) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#ifndef CSOUND_H
#define CSOUND_H

#include "Libraries.h"

class CsoundScoreEv
{
 public:
  int type;
  int name;
  double time;
  String pars;
  CsoundScoreEv(int type, int name, double time, String pars);
  ~CsoundScoreEv() ;
  String pfieldsToString(String delim);
  String toString(int fmat) ;
};

class Csound
{
 private:

  class CsoundScoreEvComparator
  {
  public:
    static int compareElements(CsoundScoreEv* e1, CsoundScoreEv* e2) {
      if ( (e1->type==Csound::IStatement) &&
	   (e2->type==Csound::FStatement) )
	return (e1->time < e2->time) ? -1 : 1;
      else
	return (e1->time <= e2->time) ? -1 : 1;   
    }
  };
  File scorefile;
  File application;
  XmlElement* commandargs;
  String scoreheader;

  bool playafter;
  bool writeafter;
  CriticalSection lock;
  CsoundScoreEvComparator comparator;
  OwnedArray<CsoundScoreEv,CriticalSection> score;
 public:

  enum {IStatement=1, FStatement};

  Csound();
  ~Csound();

  void initPrefs();
  void savePrefs();
  void openSettings();

  File getScoreFile();
  void setScoreFile(File file);

  File getApplication();
  void setApplication(File app);
  bool canRunApplication();
  void runApplication();
  String getApplicationArgs();
  int findApplicationArgs(String args);
  void setApplicationArgs(String args);
  XmlElement* getCommandArgs();

  RecentlyOpenedFilesList orchestras;

  File getOrcFile();
  void setOrcFile(File file);

  String getScoreHeader();
  void setScoreHeader(String str);

  bool getPlayAfter();
  void setPlayAfter(bool flag);

  bool getWriteAfter();  
  void setWriteAfter(bool flag);  

  void initScore(String inits);
  void saveScore();
  void sortScore();
  bool isScoreEmpty();
  void clearScore();
  void addToScore(int typ, int id, double time, String vals);
  void writeScore(int dest, int fmat, double from=0.0, double to=-1.0,
		  bool istatements=true, bool fstatements=true);
  void exportScore();

  juce_DeclareSingleton (Csound, true)

};

#ifdef GRACE

class CsoundSettingsDialog : public Component,
                             //public LabelListener,
  public FilenameComponentListener,
  public ButtonListener,
  public ComboBoxListener,
  public TextEditorListener
{
 public:
  int mode;
  Label* csolab;
  FilenameComponent* csound;
  Label* optlab;
  ComboBox* options;
  Label* orclab;
  FilenameComponent* orcfile;
  Label* hdrlab;
  TextEditor* header;
  CsoundSettingsDialog();
  ~CsoundSettingsDialog();
  //  void paint (Graphics& g);
  void resized();
  void filenameComponentChanged (FilenameComponent* changed);
  //void labelTextChanged (Label *changed);
  void comboBoxChanged (ComboBox *comboBoxThatHasChanged);
  void buttonClicked (Button *clicked);
  void textEditorTextChanged(TextEditor& ed);
  void textEditorReturnKeyPressed(TextEditor& ed);
  void textEditorEscapeKeyPressed(TextEditor& ed);
  void textEditorFocusLost(TextEditor& ed);
  void updateOptions();
};

class ExportCsoundDialog : public Component,
  public LabelListener,
  public ComboBoxListener,
  public FilenameComponentListener,
  public ButtonListener
{
 public:
  //    void paint (Graphics& g);
  GroupComponent* scoregroup;
  Label* fromlabel;
  Label* tolabel;
  Label* frombuffer;
  Label* tobuffer;
  Label* formatlabel;
  ComboBox* formatmenu;
  GroupComponent* exportgroup;
  ToggleButton* consoletoggle;
  ToggleButton* clipboardtoggle;
  ToggleButton* filetoggle;
  ToggleButton* itoggle;
  ToggleButton* ftoggle;
  TextButton* exportbutton;
  FilenameComponent* filechooser;
  ExportCsoundDialog () ;
  ~ExportCsoundDialog () ;
  void resized() ;
  void filenameComponentChanged (FilenameComponent* changed);
  void labelTextChanged (Label* labelThatHasChanged) ;
  void comboBoxChanged (ComboBox* comboBoxThatHasChanged) ;
  void buttonClicked (Button* buttonThatWasClicked) ;
};

#endif

#endif
