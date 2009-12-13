/*=======================================================================*
  Copyright (C) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifndef _MSC_VER
#include <unistd.h>
#endif
#include "mus-config.h" // in SndLib.h
#include "s7.h"
#include "clm.h"
#include "clm2xen.h"

#include <iostream>
#include "juce.h"
#include "Enumerations.h"
#include "SndLibBridge.h"
#include "CmSupport.h"
#include "SchemeSources.h"
#include "Scheme.h"
#include "Console.h"
#include "SndLib.h"
#ifdef GRACE
#include "Preferences.h"
#include "TextEditor.h"
#include "Instruments.h"
#endif

// Singleton instance for SndLib...

juce_ImplementSingleton(SndLib)

#ifdef _MSC_VER
#define unlink _unlink
s7_scheme *s7;
XEN xen_false, xen_true, xen_nil, xen_undefined;
#endif

SndLib::SndLib()
  : instable (0)
{
#ifdef GRACE
  XmlDocument dataDoc (String((const char*)Instruments::ins_xml)); 
  instable=dataDoc.getDocumentElement();
  String autos=Preferences::getInstance()->getStringProp(T("SndLibAutoLoad"));  
  if (autos.isNotEmpty())
    forEachXmlChildElement (*(instable->getChildByName(T("instruments"))),
			    e)
      {
	if (autos.containsWholeWord(e->getStringAttribute(T("File"))))
	  {
	    //std::cout << "initing as autoloaded: " 
	    //<< e->getStringAttribute(T("File")).toUTF8() << "\n";
	    e->setAttribute(T("AutoLoad"), T("yes"));
	  }
      }
#endif
}

SndLib::~SndLib()
{
  deleteAndZero(instable);
}


/*=======================================================================*
                            Scheduler Support
 *=======================================================================*/

SchemeNode::SchemeNode(int _type, double _time, SCHEMEPROC c, int _id)
  : time (0.0),
    start (0.0), 
    elapsed (0.0),
    type (0),
    expr (String::empty),
    mmess(0xff)
{
  type = _type;
  id = _id;
  time = _time;
  start = _time;
  schemeproc=c;
  s7_gc_protect(s7, schemeproc);
}

void SchemeNode::applyEvalNode()
{
  s7_pointer val=s7_eval_c_string(s7, (char *)expr.toUTF8());
  if (! s7_is_unspecified(s7, val))
    {
      String str=String(s7_object_to_c_string(s7, val));
      if (str!=T("scheme-error"))
	{
#ifdef GRACE
	  str << T("\n");
#endif
	  Console::getInstance()->printValues(str);
	}
    }
#if 0
  //  optional echoing when there no output in the repl
  else
    if (Preferences::getInstance()->getBoolProp(T("SchemeShowVoidValues"), true))
      {
	if (expr.substring(0,5)==T("(sal "))
	  {
	  }
	else
	  {
	    std::cout << expr.toUTF8() << "\n";
	    String stop=T(" ()\"\t\n");
	    String text=expr.trim();
	    int beg=0;
	    while (beg<text.length() && stop.containsChar(text[beg])) beg++;
	    int end=beg+1;
	    while (end<text.length() && !stop.containsChar(text[end])) end++;
	    String what=T("<eval ");
	    what << text.substring(beg,end);
	    if (end<text.length()) what << T("...");
	    what<<T(">\n");
	    Console::getInstance()->printValues(what);
	  }
    }
#endif
}

double SchemeNode::applyProcessNode(double elapsed)
{
  //  std::cout << "before callback, elapsed=" << elapsed << "\n";
  double delta=s7_number_to_real(s7_call(s7, 
					 schemeproc, 
					 s7_cons(s7,
						 s7_make_real(s7, elapsed),
						 s7_NIL(s7))
					 )
				 );
  //std::cout << "after callback, delta is " << delta << "\n";
  if (delta < 0.0)
    s7_gc_unprotect(s7,schemeproc);
  return delta;
}

void SchemeNode::applyMidiInputHookNode()
{
  // called on Midi message nodes if an input hook is set
  //std::cout << "applyMidiInputHookNode()\n";
  int op=(mmess.getRawData()[0] & 0xf0)>>4;
  int ch=mmess.getChannel()-1;
  int d1=mmess.getRawData()[1] & 0x7f;
  int d2=0;
  if (mmess.getRawDataSize()>2)
    d2=mmess.getRawData()[2] & 0x7f;
  // convert MidiOns with zero velocity to MidiOff
  if ((op==MidiFlags::On) && (d2==0))
    op=MidiFlags::Off;
  int res=(int)s7_integer(s7_call(s7, 
				  schemeThread->midiinhook, 
				  s7_cons(s7,
					  s7_make_integer(s7, op),
					  s7_cons(s7,					  
						  s7_make_integer(s7, ch),
						  s7_cons(s7,
							  s7_make_integer(s7, d1),
							  s7_cons(s7,
								  s7_make_integer(s7, d2),
								  s7_NIL(s7)))))));
  if (res!=0)
    {
      schemeThread->clearMidiInputHook();
      Console::getInstance()->printError(T(" Clearing Midi input hook.\n"));
    }
}

bool Scheme::isMidiInputHook()
{
  return (midiinhook != NULL);
}

void Scheme::setMidiInputHook(SCHEMEPROC hook)
{
  //std::cout << "sndlib setMidiInputHook\n";
  clearMidiInputHook();
  midiinhook=hook;
  s7_gc_protect(s7, midiinhook);
}

void Scheme::clearMidiInputHook()
{
  // hooks are set, cleared and exectued only in the scheduling thread
  // so we dont need to lock anything.
  if (midiinhook != NULL)
    {
      //std::cout << "sndlib clearMidiInputHook\n";
      s7_gc_unprotect(s7,midiinhook);
      midiinhook=NULL;
    }
}

int SndLib::performCommand(int id, int data, String text)
{
  // let other components send commands to sndlib. right now its
  // running synchronously, not sure if this will work in grace...
  CommandID cmd = CommandIDs::getCommand(id);
  int arg = CommandIDs::getCommandData(id);  
  int res=0;

  switch (cmd)
    {
    case CommandIDs::SchedulerScoreComplete :
      // this is really gross, i need to figure out how to do the
      // with-sound file opening closing in c so i dont have to call
      // back into lisp to do (finalize-with-sound)

      //std::cout << "schedulerScoreComplete!\n";
      //      s7_eval_c_string(s7,"(snd:close-output-file)");
      Scheme::getInstance()->eval("(snd:close-output-file)");

      break;
    default:
      break;
    }
  return res;
}

/*=======================================================================*
                               CM Support
 *=======================================================================*/

// s7 (values) returns (), we add void to signify no return values

s7_pointer s7_void_value(s7_scheme *sc, s7_pointer args)
{
  return s7_UNSPECIFIED(sc);
}

// custom port handers route stdout and stderr to CM displays

#define OUTBUFSIZ 1024
#define MAXBUFPOS OUTBUFSIZ-2 // leave room for null char

static void cm_stdout(s7_scheme *sc, char c, s7_pointer port)
{
  static char stdoutbuf[OUTBUFSIZ];
  static int stdoutpos = 0;
  stdoutbuf[0]=c;
  stdoutbuf[1]=(char)NULL;
  cm_print_output(stdoutbuf);
  /*
  if (stdoutpos==MAXBUFPOS)  // flush if no more room in buffer
    {
      stdoutbuf[MAXBUFPOS+1]=(char)NULL;
      cm_print_output(stdoutbuf, false);
      stdoutpos=0;      
    }
  stdoutbuf[stdoutpos]=c;
  stdoutpos++;  
  if (c=='\n')  // flush on  EOL
    {
      stdoutbuf[stdoutpos]=(char)NULL;
      cm_print_output(stdoutbuf, false);
      stdoutpos=0;      
    }
  */
}

static void cm_stderr(s7_scheme *sc, char c, s7_pointer port)
{
  static char stderrbuf[OUTBUFSIZ];
  static int stderrpos = 0;
  stderrbuf[0]=c;
  stderrbuf[1]=(char)NULL;
  cm_print_error(stderrbuf);
  /*
  if (stderrpos==MAXBUFPOS)  // flush if no more room in buffer
    {
      stderrbuf[MAXBUFPOS+1]=(char)NULL;
      cm_print_output(stderrbuf, false);
      stderrpos=0;      
    }
  stderrbuf[stderrpos]=c;
  stderrpos++;  
  if (c=='\n')  // flush on  EOL
    {
      stderrbuf[stderrpos]=(char)NULL;
      cm_print_error(stderrbuf);
      stderrpos=0;      
    }
  */
}


/*=======================================================================*
                          Scheme Runtime Support
 *=======================================================================*/

void loadCode(String file, const char* code, int size, bool trace)
{
  if (trace)
    Console::getInstance()->printOutput(file + T("\n"));
  s7_eval_c_string(s7, code);
  //#ifndef WINDOWS
  //  File f=File::createTempFile("scm");
  //  f.replaceWithText( String(code,size) );
  //  String p=f.getFullPathName();
  //  s7_load(s7, (char *)f.getFullPathName().toUTF8());
  //  f.deleteFile();
  //#else
  //  String in=T("(begin\n");
  //  in << String(code) << T(")\n");
  //  s7_eval_c_string(s7, in.toUTF8());
  //#endif
}

bool Scheme::init()
{
  midiinhook=NULL;

  /* initialize the interpreter; s7 is declared in xen.h */
  s7 = s7_init();
  if (!s7) 
    return false;

  scheme=s7;

  /* initialize the xen stuff (hooks and the xen s7 FFI) */
  s7_xen_initialize(s7);

  /* initialize sndlib with all the functions linked into s7 */
  Init_sndlib(); 

  /* Install custom port handlers for stdout and stderr */
  s7_set_current_output_port(s7, s7_open_output_function(s7, cm_stdout));
  // this is handled by *error-hook* now
  //  s7_set_current_error_port(s7, s7_open_output_function(s7, cm_stderr));

  // initalize CM 
  cm_init(s7);
  bool tr=false;
  loadCode(T("s7.scm"), SchemeSources::s7_scm, 
	   SchemeSources::s7_scmSize, tr);
  loadCode(T("utilities.scm"), SchemeSources::utilities_scm,
	   SchemeSources::utilities_scmSize, tr);
  loadCode(T("loop.scm"), SchemeSources::loop_scm, 
	   SchemeSources::loop_scmSize, tr);
  loadCode(T("patterns.scm"), SchemeSources::patterns_scm,
	   SchemeSources::patterns_scmSize, tr);
  loadCode(T("toolbox.scm"), SchemeSources::toolbox_scm,
	   SchemeSources::toolbox_scmSize, tr);
  loadCode(T("spectral.scm"), SchemeSources::spectral_scm,
	   SchemeSources::spectral_scmSize, tr);
  loadCode(T("sal.scm"), SchemeSources::sal_scm, 
	   SchemeSources::sal_scmSize, tr);
  loadCode(T("ports.scm"), SchemeSources::ports_scm, 
	   SchemeSources::ports_scmSize, tr);
  loadCode(T("fomus.scm"), SchemeSources::fomus_scm,
	   SchemeSources::fomus_scmSize, tr);
  loadCode(T("processes.scm"), SchemeSources::processes_scm, 
	   SchemeSources::processes_scmSize, tr);
  loadCode(T("plot.scm"), SchemeSources::plot_scm, 
	   SchemeSources::plot_scmSize, tr);
  loadCode(T("automata.scm"), SchemeSources::automata_scm, 
	   SchemeSources::automata_scmSize, tr);
  loadCode(T("sndlib-ws.scm"), SchemeSources::sndlibws_scm, 
	   SchemeSources::sndlibws_scmSize, tr);
  loadCode(T("osc.scm"), SchemeSources::osc_scm, 
	   SchemeSources::osc_scmSize, tr);
  // need this for some .ins files...
  XEN_EVAL_C_STRING("(provide 'snd-ws.scm)");
  s7_define_function(s7, "void", s7_void_value, 0, 0, false, "void value");

  String str=String::empty;

  // Initialize CLM variables. Make WAV the default audio format
  // everywhere since all the OSes support it and the built in player
  // can handle it. For Grace initialize *clm-player* to our built in
  // play() function, install the user's preferences for :srate,
  // :channels and :play values and autoload instruments.

  // TODO: this code actually duplicates the menu Commands that do
  // these things because this function is called before the Scheme
  // process is actually running.  The fix would be to break this
  // function into two parts: a startScheme() that does then generic
  // start up and then an init() that customizes. the latter function
  // could then call Scheme::getIntance() function.s

#ifdef GRACE
  Preferences* pref=Preferences::getInstance();
  str << T("(begin")
      << T("  (set! *clm-player* play)")
      << T("  (set! *clm-srate* ") << pref->getIntProp(T("SndLibSrate"), 44100) << T(")")
      << T("  (set! *clm-channels* ") << pref->getIntProp(T("SndLibChannels"), 1) << T(")");
  if (pref->getBoolProp(T("SndLibAutoPlay"), true))
    str << T("  (set! *clm-play* #t)");
  else 
    str << T("  (set! *clm-play* #f)");
  str << T(")");
  s7_eval_c_string(s7,str.toUTF8());

  String fmat=SndLib::getInstance()->getAudioFormat();
  if (fmat.equalsIgnoreCase(T("WAV")))
    s7_eval_c_string(s7,"(begin (set! *clm-header-type* mus-riff) (set! *clm-data-format* mus-lshort) (set! *clm-file-name* \"test.wav\"))");
  else if (fmat.equalsIgnoreCase(T("AIFF")))
    s7_eval_c_string(s7,"(begin (set! *clm-header-type* mus-aifc) (set! *clm-data-format* mus-bshort) (set! *clm-file-name* \"test.aif\"))");
  else if (fmat.equalsIgnoreCase(T("SND")))
    s7_eval_c_string(s7,"(begin (set! *clm-header-type* mus-next) (set! *clm-data-format* mus-bshort) (set! *clm-file-name* \"test.snd\"))");
  SndLib::getInstance()->autoLoadInstruments();
#else
  s7_eval_c_string(s7,"(define *clm-header-type* mus-riff)");
  s7_eval_c_string(s7,"(define *clm-data-format* mus-lshort)");
  s7_eval_c_string(s7,"(define *clm-file-name* \"test.wav\")");
#endif

  return true;
}

void Scheme::cleanup()
{
  free(s7);
}

String Scheme::getLispVersion()
{
  String str=String::empty;
  str << T("S7 Scheme") << T(" ") << String(S7_VERSION) << T(" (") << String(S7_DATE)<< T(")")
      << T(" ") << SysInfo::getCopyright( T("William Schottstaedt"));
  return str;
}

void SndLib::restoreInstruments(String dir)
{
#ifdef GRACE
  FileChooser chooser (T("Choose Directory For Instruments"),
                       File::getSpecialLocation(File::userHomeDirectory));
  if (!chooser.browseForDirectory() )
    return;
  File directory (chooser.getResult());  
  MemoryInputStream zipstream (Instruments::ins_zip,
			       Instruments::ins_zipSize,
			       false);
  ZipFile archive(&zipstream, false);
  archive.uncompressTo(directory, true);
  Console::getInstance()->printOutput(T("Instruments saved in ") +
                                      directory.getFullPathName() + 
                                      T(".\n"));
#endif
}

bool SndLib::getAutoPlay()
{
#ifdef GRACE
  return Preferences::getInstance()->getBoolProp(T("SndLibAutoPlay"), true);
#endif
  return false;
}

void SndLib::setAutoPlay(bool ap)
{
#ifdef GRACE
  String st=T("(begin (set! *clm-play* ");
  st << ((ap) ? T("#t") : T("#f"))
     << T(") (void))");
  Preferences::getInstance()->setIntProp(T("SndLibAutoPlay"), ap);
  Scheme::getInstance()->eval(st);
#endif
} 

int SndLib::getSrate()
{
#ifdef GRACE
  return Preferences::getInstance()->getIntProp(T("SndLibSrate"), 44100);
#endif
  return 0;
}

void SndLib::setSrate(int sr)
{
#ifdef GRACE
  String st=T("(begin (set! *clm-srate* ") + String(sr) + T(") (void))");
  Preferences::getInstance()->setIntProp(T("SndLibSrate"), sr);
  Scheme::getInstance()->eval(st);
#endif
}

int SndLib::getChannels()
{
#ifdef GRACE
  return Preferences::getInstance()->getIntProp(T("SndLibChannels"), 1);
#endif
  return 0;
}

void SndLib::setChannels(int ch)
{
#ifdef GRACE
  String st=T("(begin (set! *clm-channels* ") + String(ch) + T(") (void))");
  Preferences::getInstance()->setIntProp(T("SndLibChannels"), ch);
  Scheme::getInstance()->eval(st);
#endif
}

String SndLib::getAudioFormat()
{
#ifdef GRACE
  return Preferences::getInstance()->getStringProp(T("SndLibAudioFormat"),
                                                   T("WAV"));
#endif
  return String::empty;
}

void SndLib::setAudioFormat(String format)
{
#ifdef GRACE
  String head, data, file, code;
  if (format.equalsIgnoreCase(T("WAV")))
    {
      head=T("mus-riff");
      data=T("mus-lshort");
      file=T("test.wav");
    }
  else if (format.equalsIgnoreCase(T("AIFF")))
    {
      head=T("mus-aifc");
      data=T("mus-bshort");
      file=T("test.aif");
    }
  else if (format.equalsIgnoreCase(T("SND")))
    {
      head=T("mus-next");
      data=T("mus-bshort");
      file=T("test.snd");
    }
  else 
    return;

  Preferences::getInstance()->setStringProp(T("SndLibAudioFormat"), format);

  code << T("(begin")
       << T(" (set! *clm-header-type* ") << head << T(")")
       << T(" (set! *clm-data-format* ") << data << T(")")
       << T(" (set! *clm-file-name* ") << file.quoted() << T(")")
       << T("(void))");

  Scheme::getInstance()->eval(code);
#endif
}

/*=======================================================================*
                               Instrument Browser
 *=======================================================================*/

#ifdef GRACE

class InstrumentWindow : public DocumentWindow
{
public:
  InstrumentWindow()
    : DocumentWindow(T("SndLib Instruments"), 
		     Colour(0xffe5e5e5),
		     DocumentWindow::allButtons)
  {
  }
  ~InstrumentWindow()
  {
  }
  void closeButtonPressed()
  {
    delete this;
  }
};

class InstrumentTable : public Component,
  public TableListBoxModel,
  public ButtonListener 
{
  TableListBox* table; 
  Font font;
  XmlElement* insData;
  XmlElement* columnList;
  XmlElement* dataList;
  TextButton* loadButton;
  TextButton* open1Button;
  TextButton* open2Button;
  TextButton* autoButton;
  int selRow;
  int numRows; 
  static const int AutoloadColumn=5;
  //Column sorting class
  class DemoDataSorter
  {
    const String attributeToSort;
    const int direction;
  public:
  DemoDataSorter(const String attributeToSort_, bool forwards)
    : attributeToSort(attributeToSort_), 
      direction(forwards ? 1 : -1)
      {
      }
    int compareElements(XmlElement* first, XmlElement* second) const
    {
      int result = first->getStringAttribute(attributeToSort).
        compareLexicographically(second->getStringAttribute(attributeToSort));
      const tchar* indexString = T("Name");
      if (result == 0) //Tie breaker
        result = first->getStringAttribute(indexString).
	  compareLexicographically(second->getStringAttribute(indexString));
      return direction * result;
    }
  };

  void loadInstrument(String file);
  void openInstrument(String file);
  void loadTableData();
  const String getAttributeNameForColumnId(const int columnId);

 public:

  InstrumentTable();
  ~InstrumentTable();
  int getNumRows();
  void selectedRowsChanged(int r);
  void paintRowBackground(Graphics& g, int rowNumber, int width, 
			  int height, bool rowIsSelected);
  void paintCell(Graphics& g, int rowNumber, int columnId, 
		 int width, int height, bool rowIsSelected);
  void sortOrderChanged(int newSortColumnId, const bool isForwards);
  Component* refreshComponentForCell(int rowNumber, int columnId, 
				     bool isRowSelected, 
				     Component* componentToUpdate);
  int getColumnAutoSizeWidth(int columnId);
  void resized();
  void cellDoubleClicked(int rowNumber,	int columnId, const MouseEvent &e);
  void returnKeyPressed(int row);
  void buttonClicked (Button* button);
  static void openInstrumentTable();
};

void SndLib::openInstrumentBrowser()
{
  InstrumentTable* ins=new InstrumentTable();
  InstrumentWindow* win=new InstrumentWindow();
  ins->setVisible(true);
  win->setUsingNativeTitleBar(true);
  win->centreWithSize(ins->getWidth(),ins->getHeight());
  win->setContentComponent(ins);
  win->setDropShadowEnabled(true);
  win->setWantsKeyboardFocus(false);
  win->setResizable(true, true); 
  win->setVisible(true);
}



XmlElement* SndLib::getInstrumentTable(bool all)
{
  // return instrument table or list of instruments in it
  return (all) ? instable : instable->getChildByName(T("instruments"));
}

XmlElement* SndLib::getInstrumentElement(String filename)
{
  XmlElement* instab=getInstrumentTable();
  forEachXmlChildElement (*instab, e)
    {
      if (e->getStringAttribute(T("File")) == filename)
	return e;
    }
  return NULL;
}

//
// Instrument Loading and AutoLoading
// 

String SndLib::getInstrumentCode(String filename)
{
  // filename can be a single file or list of space delimited files
  // create zip archive from embedded resource
  MemoryInputStream zipstream (Instruments::ins_zip,
			       Instruments::ins_zipSize,
			       false);
  StringArray filenames;
  filenames.addTokens(filename, false);
  ZipFile archive(&zipstream, false);
  InputStream* inst=NULL;
  String text=String::empty;
  for (int i=0; i<filenames.size(); i++)
    {
      // create file path in zip file
      String path=filenames[i];
      int index = archive.getIndexOfFileName(path);
      if (index<0)
	continue;
      inst = archive.createStreamForEntry(index);
      if (!inst)
	continue;
      text << inst->readEntireStreamAsString();
      delete inst;
    }
  inst=NULL;
  return text;
}

void SndLib::getInstrumentFilesToLoad(XmlElement* ins, StringArray& files)
{
  // return files to load for ins, including unloaded dependencies
  StringArray depends;
  depends.addTokens(ins->getStringAttribute(T("Depend")), false);
  for (int i=0; i<depends.size(); i++)
    {
      XmlElement* s=getInstrumentElement(depends[i]);
      if (s && !s->getBoolAttribute(T("Loaded")))
	{
	  String f=s->getStringAttribute(T("File"));
	  if (!files.contains(f) )
	    files.add(f);
	}
    }
  files.add(ins->getStringAttribute(T("File"))); // always load this one
}

void SndLib::updateAutoLoaded()
{
  XmlElement* tab=getInstrumentTable();
  String s=String::empty;
  forEachXmlChildElement (*tab, e)
    {
      if (e->getBoolAttribute(T("AutoLoad")))
	if (s.isEmpty())
	  s=e->getStringAttribute(T("File"));
	else
	  s << T(" ") << e->getStringAttribute(T("File"));
    }
  //std::cout << "setting prefs=" << s.toUTF8() << "\n";
  Preferences::getInstance()->setStringProp(T("SndLibAutoLoad"),s);
}

void SndLib::autoLoadInstruments()
{
  String str=Preferences::getInstance()->getStringProp(T("SndLibAutoLoad"));
  if (str.isEmpty()) return;
  // fill array of instruments to autoload
  StringArray autos;
  autos.addTokens(str, false);
  if (autos.size()==0) return;
  // fill array of all files to load 
  StringArray loads;
  for (int i=0; i<autos.size(); i++)
    {
      // get xml instrument element
      XmlElement* ins=SndLib::getInstance()->getInstrumentElement(autos[i]);
      getInstrumentFilesToLoad(ins, loads);
    }
  
  for (int i=0; i<loads.size(); i++)  
    {
      String str=getInstrumentCode(loads[i]);
      //      std::cout << "loading: " << loads[i].toUTF8() << "\n";
      s7_eval_c_string(s7, str.toUTF8());
      XmlElement* ins=SndLib::getInstance()->getInstrumentElement(loads[i]);
      ins->setAttribute(T("Loaded"), "yes");
    }  
}

void SndLib::loadInstrumentCode(XmlElement* ins)
{
  StringArray loads;
  getInstrumentFilesToLoad(ins, loads);
  for (int i=0; i<loads.size(); i++)  
    {
      String msg=T("Loading ") + loads[i] + T("\n");
      String str=getInstrumentCode(loads[i]);
      Console::getInstance()->printOutput(msg);
      Scheme::getInstance()->eval(str);
      XmlElement* x=SndLib::getInstance()->getInstrumentElement(loads[i]);
      x->setAttribute(T("Loaded"), "yes");
    }  
}


/*=======================================================================*
                              The XML Table Display
 *=======================================================================*/

InstrumentTable::InstrumentTable() 
  : font (14.0f),
    loadButton (0),
    open1Button (0),
    open2Button (0),
    autoButton (0),
    insData (0),
    selRow(-1)
{
  // Load instrument data from the embedded XML file..
  loadTableData();
  // Create table and add it to this component..
  addAndMakeVisible (table = new TableListBox (T("SndLib Instruments"),
					       this));
  // give it a border
  table->setColour(ListBox::outlineColourId, Colours::grey);
  table->setOutlineThickness(1);
  // Add the columns to the table header and calculate widths of
  // columns and table
  int columnid=1, tablewidth=0;
  forEachXmlChildElement(*columnList, columnXml)
    {
      // heading width includes min space for sorting triangle
      int width=jmax(font.getStringWidth
		     (columnXml->getStringAttribute(T("Name"))),
			    75); 
      // column width is data width max heading width
      int columnwidth = jmax( getColumnAutoSizeWidth(columnid), width);
      table->getHeader()->
	addColumn(columnXml->getStringAttribute(T("Name")),
		  columnXml->getIntAttribute(T("Id")),
		  columnwidth, 50, 400,
		  TableHeaderComponent::defaultFlags);
      tablewidth += columnwidth;
      columnid++;
    }
  // sort forward by the ID column
  table->getHeader()->setSortColumnId (1, true);

  addAndMakeVisible (loadButton = new TextButton (String::empty));
  loadButton->setEnabled(false);
  loadButton->setButtonText (T("Load Instrument"));
  loadButton->addButtonListener (this);

  addAndMakeVisible (open1Button = new TextButton (String::empty));
  open1Button->setEnabled(false);
  open1Button->setButtonText (T("Open Examples"));
  open1Button->addButtonListener (this);

  addAndMakeVisible (open2Button = new TextButton (String::empty));
  open2Button->setEnabled(false);
  open2Button->setButtonText (T("Open Instrument"));
  open2Button->addButtonListener (this);

  addAndMakeVisible (autoButton = new TextButton (String::empty));
  autoButton->setButtonText (T("Auto Load"));
  autoButton->addButtonListener (this);

  setSize(tablewidth + 60, 16+300+16+24+16);
}

InstrumentTable::~InstrumentTable()
{
  deleteAllChildren();
  // delete insData;
}

void InstrumentTable::resized()
{
  // position our table with a gap around its edge
  //500+8+24+8;
  table->setBounds(16, 16, getWidth()-32, getHeight()-16-24-16-16);
  int x=getWidth()/2;
  int y=getBottom()-16-24;
  // middle button
  open1Button->setBounds(x-66, y, 132, 24);
  loadButton->setBounds (open1Button->getX()-16-132, y, 132, 24);
  open2Button->setBounds(open1Button->getRight()+16, y, 132, 24);
  autoButton->setBounds(getWidth()-90-16-24, y, 90, 24);
}

void InstrumentTable::buttonClicked (Button* button)
{
  // no row selected 
  if (selRow == -1) return;
  XmlElement* ins=dataList->getChildElement(selRow);
  // this shouldn't happen
  if (ins == NULL) return;
  String path, code;
  if (button==loadButton)
    {
      SndLib::getInstance()->loadInstrumentCode(ins);
    } 
  else if (button==open2Button)
    {
      path=ins->getStringAttribute(T("File"));
      code=SndLib::getInstance()->getInstrumentCode(path);
      if (code.isEmpty())
	return;
      new TextEditorWindow(File::nonexistent, code, TextIDs::Lisp,
			   File(path).getFileName());
    } 
  else if (button == open1Button)
    {
      path=ins->getStringAttribute(T("Examples"));
      code=SndLib::getInstance()->getInstrumentCode(path);
      if (code.isEmpty())
	return;
      new TextEditorWindow(File::nonexistent, code, TextIDs::Lisp,
			   path);
    }
  else if (button == autoButton)
    {
      if (ins->getBoolAttribute(T("AutoLoad")))
	ins->setAttribute(T("AutoLoad"), T("no"));
      else 
	ins->setAttribute(T("AutoLoad"), T("yes"));
      repaint();
      SndLib::getInstance()->updateAutoLoaded(); // update preferences
    }
}

/*=======================================================================*
                               XML Table Code
 *=======================================================================*/

int InstrumentTable::getNumRows()
{
  return numRows;
}

void InstrumentTable::loadTableData()
{
  //  String text=String((const char*) Instruments::table_xml);
  //  XmlDocument dataDoc (text );
  //  insData = dataDoc.getDocumentElement();
  insData=SndLib::getInstance()->getInstrumentTable(true);
  dataList = insData->getChildByName(T("instruments"));
  columnList = insData->getChildByName(T("columns"));
  numRows = dataList->getNumChildElements();
}

void InstrumentTable::selectedRowsChanged(int selectedRow)
{
  selRow=selectedRow;
  bool active=(selRow>-1);
  loadButton->setEnabled(active);
  open2Button->setEnabled(active);
  // example button only active if entry has Example attribute set
  const XmlElement* row=dataList->getChildElement(selRow);
  if (!active || row==NULL)
    open1Button->setEnabled(false);
  else
    {
      String file=row->getStringAttribute(T("Examples"));
      if (file.isEmpty())
	open1Button->setEnabled(false);
      else
	open1Button->setEnabled(true);
    }
}

const String InstrumentTable::getAttributeNameForColumnId (const int colId) 
{
  // search COLUMNS component for the attribute that matches a column ID
  forEachXmlChildElement (*columnList, columnXml) 
    {
      if (columnXml->getIntAttribute(T("Id")) == colId)
	return columnXml->getStringAttribute(T("Name"));
    }
  return String::empty;
}

void InstrumentTable::paintRowBackground (Graphics& g, 
					     int rowNumber, 
					     int width, int height, 
					     bool rowIsSelected)
{
  if (rowIsSelected)
    g.fillAll (Colours::lightgoldenrodyellow); 
}

void InstrumentTable::paintCell (Graphics& g, int rowNumber,
				    int columnId, 
				    int width, int height,
				    bool rowIsSelected)
{
  const XmlElement* rowElement = dataList->getChildElement(rowNumber);
  //g.setColour (Colours::black);
  if (rowElement->getBoolAttribute(T("Loaded")))
    g.setColour (Colours::green);
  else
    g.setColour (Colours::black);
  g.setFont (font);
  if (rowElement != 0)
    {
      const String text 
	(rowElement->
	 getStringAttribute( getAttributeNameForColumnId(columnId)));
      g.drawText (text, 2, 0, width - 4, height, Justification::centredLeft,
		  true);
    }
  g.setColour (Colours::black.withAlpha (0.2f));
  g.fillRect (width - 1, 0, 1, height);
}

void InstrumentTable::sortOrderChanged (int newSortColumnId,
					const bool isForwards) 
{
  if (newSortColumnId != 0)
    {
      DemoDataSorter sorter 
	(getAttributeNameForColumnId (newSortColumnId), isForwards);
      dataList->sortChildElements (sorter);
      table->updateContent();
    }
}

Component* InstrumentTable::refreshComponentForCell
(int rowNumber, int columnId, bool isRowSelected, Component* comp) 
{
    return NULL;
}

int InstrumentTable::getColumnAutoSizeWidth (int columnId)
{
  int widest = 32;
  // find the widest bit of text in this column..
  for (int i = getNumRows(); --i >= 0;)
    {
      const XmlElement* rowElement = dataList->getChildElement (i);
      if (rowElement != 0) 
	{
	  const String text 
	    (rowElement->
	     getStringAttribute(getAttributeNameForColumnId (columnId)));
	  widest = jmax (widest, font.getStringWidth (text));
	}
    }
  return widest + 8;
}

void InstrumentTable::cellDoubleClicked(int rowNumber, int colId, 
					   const MouseEvent &e) 
{
  if (selRow>-1)
    {
      loadButton->triggerClick();
      open1Button->triggerClick();
    }
}

void InstrumentTable::returnKeyPressed(int row) 
{
  if (selRow>-1)
    {
      loadButton->triggerClick();
    }
}


#endif
