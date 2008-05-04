/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

#ifndef __CSOUND__
#define __CSOUND__

// g++ -MMD -D "MACOSX=1" -D "SCHEME=1" -D "PORTCSOUND=1" -I "../../../chicken" -I "../../../juce" -I "/usr/local/include"  -O2 -o build/grace.obj/Release/Csound.o -c ../../src/Csound.cpp

#include <juce.h>
#include "Console.h"
#ifdef PORTCSOUND

#ifdef MACOSX
#include <CsoundLib/csound.h>
#endif
#ifdef WINDOWS
#include <csound.h>
#endif
#ifdef LINUX
#include <csound/csound.h>
#endif

#else
typedef double MYFLT;
#endif

class ConsoleWindow;
class CsoundPort;

class CsoundConnection : public Thread {
 public:
#ifdef PORTCSOUND
  CSOUND* csound;
#else
  void* csound;
#endif
  CsoundPort *port;
  int mode;

  CsoundConnection(CsoundPort* _port, int _mode);
  ~CsoundConnection();
  bool init(String initargs) ;
  void run ();
  bool isWriter();
};

class CsoundScoreEv {
 public:
  char type;
  int size;
  MYFLT *pars;
  String strarg; // csound supports 1 string parameter
  int strpos;    // string par's pfield number

  CsoundScoreEv(char typ, int siz, MYFLT *flt, 
		String strval = String::empty,
		int strpar = -1);
  ~CsoundScoreEv() ;
  String pfieldsToText(String delim);
  String toText(int fmat) ;
};

class CsoundScoreEvComparator {
 public:
  static int compareElements(CsoundScoreEv* e1, CsoundScoreEv* e2) {
    //    if ( e1->pars[1] <= e2->pars[1])
    //      return -1;
    //    return 1;
    // f statements at eact time as i statements put first
    if ( (e1->type=='i') && (e2->type=='f') )
      return (e1->pars[1] < e2->pars[1]) ? -1 : 1;
    else
      return (e1->pars[1] <= e2->pars[1]) ? -1 : 1;   
  }
};

class ExportCsoundDialog;

class CsoundPort {
 public:
  enum {portClosed=0, portOpen, portWrite};
  enum {formatCsound=1, formatLispData, formatSalData,
	formatLispSend, formatSalSend};
  enum {exportConsole=1, exportClipboard, exportFile};
  String portoptions, fileoptions;
  RecentlyOpenedFilesList orcfiles;
  ConsoleWindow *console;
  ExportCsoundDialog *exportdialog;
  CsoundConnection *port_connection;
  CsoundConnection *file_connection;
  OwnedArray<CsoundScoreEv> score;
  CsoundScoreEvComparator comparator;
  bool portopen;
  bool tracing;
  bool writing;
  bool scoremode;
  bool recordmode;
  double scorestart, scorestamp;
  CriticalSection lock;
  CsoundPort(ConsoleWindow *win) ;
  ~CsoundPort() ;
  String getPortOptions();
  void setPortOptions(String opts);
  String getFileOptions();
  void setFileOptions(String opts);
  File getOrcFile();
  void setOrcFile(File file);
  void save();
  void revert();
  bool open(bool port ) ;
  void close(bool port
);
  bool isOpen() ;
  void setOpen(bool b) ;
  bool isClosed() ;
  bool isWriting() ;
  void setWriting(bool b);

  bool isTraceMode();
  void setTraceMode(bool b);
  bool isScoreMode();
  void setScoreMode(bool b);
  bool isRecordMode() ;
  void setRecordMode(bool b);
  void setRecordStart(double f);

  void lockCsound();
  void unlockCsound();

  void playScore(double start = 0.0, double end = -1.0, double shift = 0.0 );
  void writeScore(CSOUND* csound);
  void clearScore();
  void printScore(double start = 0.0, double end = -1.0 );
  void displayScore();
  void importScore();
  void exportScore();

  void sendScoreEvent(char type, int len, MYFLT *pars);
  void sendScoreEvent(CsoundScoreEv* ev, bool del=true);
  void addScoreEvent(char type, int len, MYFLT *pars);
  void addScoreEvent(CsoundScoreEv* ev);

  void sortScore();
  int numScoreEvents();
  bool isScoreEmpty();
};

class OpenCsoundDialog : public Component,
  public LabelListener,
  public FilenameComponentListener,
  public ButtonListener
{
 public:
  CsoundPort* port;
  int mode;
  Label* label1;
  Label* label2;
  Label* options;
  FilenameComponent* orcfile;
  ToggleButton* tracebutton;
  TextButton* openbutton;
  OpenCsoundDialog(CsoundPort* p, int m);
  ~OpenCsoundDialog();
  //  void paint (Graphics& g);
  void resized();
  void filenameComponentChanged (FilenameComponent* changed);
  void labelTextChanged (Label *changed);
  void buttonClicked (Button *clicked);
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
