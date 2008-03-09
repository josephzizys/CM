#ifndef __CSOUND__
#define __CSOUND__

// g++ -MMD -D "MACOSX=1" -D "SCHEME=1" -D "PORTCSOUND=1" -I "../../../chicken" -I "../../../juce" -I "/usr/local/include"  -O2 -o build/grace.obj/Release/Csound.o -c ../../src/Csound.cpp

#include <juce.h>
#include "Console.h"
#ifdef PORTCSOUND

#ifdef MACOSX
#include <CsoundLib/csound.h> 
#else
#include <csound/csound.h> 
#endif

#else
typedef MYFLT double;
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
  CsoundConnection(CsoundPort *_port);
  ~CsoundConnection();
  bool init(String initargs) ;
  void run ();
};

class CsoundScoreEv {
 public:
  char type;
  int size;
  MYFLT *pars;
  CsoundScoreEv(char ty, int sz, MYFLT *fl) {
    type=ty;
    size=sz;
    pars=new MYFLT[sz];
    for (int i=0;i<sz;i++)
      pars[i]=fl[i];
  }
  ~CsoundScoreEv() {
    delete [] pars;
  }
};

class CsoundScoreEvComparator {
 public:
  static int compareElements(CsoundScoreEv* e1, CsoundScoreEv* e2) {
    //    if (e1->type=='f')
    //      if (e2->type=='f')
    //	return 0;
    //      else return -1;
    //    else if (e2->type=='f')
    //      return 1;
    if ( e1->pars[1] <= e2->pars[1])
      return -1;
    return 1;
  }
};

class ExportCsoundDialog;

class CsoundPort {
 public:
  enum {portClosed=0, portOpen, portWriting};
  enum {formatCsound=1, formatLispData, formatSalData,
	formatLispSend, formatSalSend};
  enum {exportConsole=1, exportClipboard, exportFile};
  String portoptions, fileoptions;
  RecentlyOpenedFilesList orcfiles;
  ConsoleWindow *console;
  ExportCsoundDialog *exportdialog;
  CsoundConnection *connection;
  OwnedArray<CsoundScoreEv> score;
  CsoundScoreEvComparator comparator;
  int running;
  bool tracing;
  CriticalSection lock;
  CsoundPort(ConsoleWindow *win) ;
  ~CsoundPort() ;
  String getPortOptions();
  void setPortOptions(String opts);
  String getFileOptions();
  void setFileOptions(String opts);
  File getOrcFile();
  void setOrcFile(File file);
  bool getTracing();
  void setTracing(bool b);
  void save();
  void revert();
  bool open() ;
  void close();
  bool isOpen() ;
  bool isClosed() ;
  bool isWriting() ;
  void lockCsound();
  void unlockCsound();
  // scorefile api
  void writeScore();
  void clearScore();
  void displayScore();
  void exportScore();
  void sendScoreEvent(char type, int len, MYFLT *pars);
  void addScoreEvent(char type, int len, MYFLT *pars);
  String getScoreEventText(int fmat, char type, int len, 
			   MYFLT *pars);
  String getScoreText(int fmat);
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
  OpenCsoundDialog(CsoundPort* p);
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
