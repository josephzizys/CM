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
#include "xen.h"
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
{
}

SndLib::~SndLib()
{
}

/*=======================================================================*
                            Scheduler Support
 *=======================================================================*/

SchemeNode::SchemeNode(int _type, double _time, SCHEMEPROC c, int _id)
  : time (0.0),
    start (0.0), 
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
#ifdef GRACE
      String str=String(s7_object_to_c_string(s7, val));
      str << T("\n");
      Console::getInstance()->printValues(str);
#else
      Console::getInstance()->printValues(s7_object_to_c_string(s7, val));
#endif
    }
  //  else
  //    schemeThread->printVoidValue();
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
  std::cout << "applyMidiInputHookNode()\n";
  int op=(mmess.getRawData()[0] & 0xf0)>>4;
  int ch=mmess.getChannel()-1;
  int d1=mmess.getRawData()[1] & 0x7f;
  int d2=0;
  if (mmess.getRawDataSize()>2)
    d2=mmess.getRawData()[2] & 0x7f;
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
                    Required definitions for scm/sndlib-ws.scm 
 *=======================================================================*/

static XEN g_file_exists_p(XEN name)
{
  #define H_file_exists_p "(file-exists? filename): #t if the file exists"
  XEN_ASSERT_TYPE(XEN_STRING_P(name), name, XEN_ONLY_ARG, "file-exists?", "a string");
  return(C_TO_XEN_BOOLEAN(mus_file_probe(XEN_TO_C_STRING(name))));
}

XEN_NARGIFY_1(g_file_exists_p_w, g_file_exists_p)

static XEN g_delete_file(XEN name)
{
  #define H_delete_file "(delete-file filename): deletes the file"
  XEN_ASSERT_TYPE(XEN_STRING_P(name), name, XEN_ONLY_ARG, "delete-file", "a string");
  return(C_TO_XEN_BOOLEAN(unlink(XEN_TO_C_STRING(name))));
}

XEN_NARGIFY_1(g_delete_file_w, g_delete_file)

static XEN g_random(XEN val)
{
  if (XEN_INTEGER_P(val))
    return(C_TO_XEN_INT(mus_irandom(XEN_TO_C_INT(val))));
  return(C_TO_XEN_DOUBLE(mus_frandom(XEN_TO_C_DOUBLE(val))));
}

XEN_NARGIFY_1(g_random_w, g_random)


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

void loadCode(const char* code, int size)
{
#ifndef WINDOWS
  File f=File::createTempFile("scm");
  f.replaceWithText( String(code,size) );
  String p=f.getFullPathName();
  s7_load(s7, (char *)f.getFullPathName().toUTF8());
  f.deleteFile();
#else
  String in=T("(begin\n");
  in << String(code) << T(")\n");
  s7_eval_c_string(s7, in.toUTF8());
#endif
}

bool Scheme::init()
{
  midiinhook=NULL;

  /* initialize the interpreter; s7 is declared in xen.h */
  s7 = s7_init();
  if (!s7) 
    return false;

  /* initialize the xen stuff (hooks and the xen s7 FFI) */
  s7_xen_initialize(s7);
  /* initialize sndlib with all the functions linked into s7 */
  Init_sndlib(); 

  /* these next lines are for compatibility with Guile (ws.scm has
     Guile-specific junk) */

  XEN_EVAL_C_STRING("(defmacro use-modules (arg . args) #f)");
  XEN_EVAL_C_STRING("(define (make-soft-port . args) #f)");
  XEN_EVAL_C_STRING("(define (current-module) (current-environment))");
  XEN_EVAL_C_STRING("(define load-from-path load)");
  XEN_DEFINE_PROCEDURE("file-exists?", g_file_exists_p_w, 
		       1, 0, 0, H_file_exists_p);
  XEN_DEFINE_PROCEDURE("delete-file", g_delete_file_w,
		       1, 0, 0, H_delete_file);
  XEN_DEFINE_PROCEDURE("random", g_random_w, 1, 0, 0,
		       "(random arg): random number between 0 and arg");
  /* deal with the ubiquitous run macro */
  XEN_EVAL_C_STRING("(define (run-safety) 0)");
  //  XEN_EVAL_C_STRING("(defmacro run (thunk) `(,thunk))");
  XEN_EVAL_C_STRING("(define (1+ x) (+ x 1))");

  /* Install custom port handlers for stdout and stderr */

  s7_set_current_output_port(s7, 
			     s7_open_output_function(s7, cm_stdout));
  s7_set_current_error_port(s7,
			    s7_open_output_function(s7, cm_stderr));

  // initalize CM 
  cm_init(s7);
  loadCode(SchemeSources::s7_scm, SchemeSources::s7_scmSize);
  loadCode(SchemeSources::utilities_scm, SchemeSources::utilities_scmSize);
  loadCode(SchemeSources::loop_scm, SchemeSources::loop_scmSize);
  loadCode(SchemeSources::patterns_scm, SchemeSources::patterns_scmSize);
  loadCode(SchemeSources::toolbox_scm, SchemeSources::toolbox_scmSize);
  loadCode(SchemeSources::spectral_scm, SchemeSources::spectral_scmSize);
  loadCode(SchemeSources::sal_scm, SchemeSources::sal_scmSize);
  loadCode(SchemeSources::ports_scm, SchemeSources::ports_scmSize);
  loadCode(SchemeSources::fomus_scm, SchemeSources::fomus_scmSize);
  loadCode(SchemeSources::processes_scm, SchemeSources::processes_scmSize);
  loadCode(SchemeSources::sndlibws_scm, SchemeSources::sndlibws_scmSize);
  // need this for some .ins files...
  XEN_EVAL_C_STRING("(provide 'snd-ws.scm)");
  loadCode(SchemeSources::env_scm, SchemeSources::env_scmSize);
  s7_define_function(s7, "void", s7_void_value, 0, 0, false, "void value");

  String str=String::empty;

  // Initialize CLM variables. Make WAV the default audio format
  // everywhere since all the OSes support it and the built in player
  // can handle it. For Grace initialize *clm-player* to our built in
  // play() function, install the user's preferences for :srate,
  // :channels and :play values and autoload instruments.

  s7_eval_c_string(s7,"(define *clm-header-type* mus-riff)");
  s7_eval_c_string(s7,"(define *clm-data-format* mus-lshort)");
  s7_eval_c_string(s7,"(define *clm-file-name* \"test.wav\")");

#ifdef GRACE
  Preferences* pref=Preferences::getInstance();
  str << T("(begin (set! *clm-player* play) ")
      << T("(set! *clm-srate* ")
      << pref->getIntProp(T("SndLibSrate"), 44100)
      << T(") (set! *clm-channels* ")
      << pref->getIntProp(T("SndLibChannels"), 1)
      << T(") (set! *clm-play* ")
      << ((pref->getBoolProp(T("SndLibAutoPlay"), true))
	  ? T("#t))") : T("#f))"));
  s7_eval_c_string(s7,str.toUTF8());
  // autoload user's instruments. right now this is just a hardwired
  // wave.ins
  str=SndLib::getInstance()->getInstrumentCode(T("wave.scm"));
  s7_eval_c_string(s7, str.toUTF8());
#endif

  // Print herald

  str=String::empty;
  str << String("SndLib ")
      << String(SNDLIB_VERSION) << String(".") << String(SNDLIB_REVISION)
      << T(" ") << SysInfo::getCopyright( T("William Schottstaedt")) << T("\n")
      << SysInfo::getCMLogo() << T("\n");
  Console::getInstance()->printOutput(str);

  // clear out backtrace history set it to length 0 since most of the
  // entries will be C calls...
  s7_eval_c_string(s7,"(clear-backtrace)");
  s7_eval_c_string(s7,"(backtracing #f)");
  return true;
}

void Scheme::cleanup()
{
  free(s7);
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

  class AutoLoad  : public Component,
    public ButtonListener
    {
    private:
      int row, cid;
      TextButton* openButton;
      TextButton* loadButton;
      ToggleButton* autoButton;
      InstrumentTable* dialog;
      AutoLoad (const AutoLoad&);
      const AutoLoad& operator= (const AutoLoad&);
    public:
      AutoLoad (InstrumentTable* dlg);
      ~AutoLoad();
      void paint (Graphics& g);
      void resized();
      void buttonClicked (Button* buttonThatWasClicked);
      void setRowAndColumn(const int r, const int c);
      //juce_UseDebuggingNewOperator
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

String SndLib::getInstrumentCode(String name)
{
  // create file path in zip file
  String path=T("files/");
  path << name;
  // create zip archive from embedded resource
  MemoryInputStream zipstream (Instruments::files_zip,
			       Instruments::files_zipSize,
			       false);
  ZipFile archive(&zipstream, false);
  // look up file
  int index = archive.getIndexOfFileName(path);
  if (index<0)
    {
      std::cout << "no index for file, returning\n";
      return String::empty;
    }
  InputStream* inst=NULL;
  String text;
  inst = archive.createStreamForEntry(index);
  if(!inst)
	  return String::empty;
  text = inst->readEntireStreamAsString();
  delete inst;
  return text;
}

/*=======================================================================*
                              The XML Table Display
 *=======================================================================*/

InstrumentTable::InstrumentTable() 
  : font (14.0f),
    loadButton (0),
    open1Button (0),
    open2Button (0),
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

  setSize(tablewidth + 60, 16+300+16+24+16);
}

InstrumentTable::~InstrumentTable()
{
  deleteAllChildren();
  delete insData;
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
}

void InstrumentTable::buttonClicked (Button* button)
{
  // no row selected (shouldn't happen)
  if (selRow == -1)
    return;
  const XmlElement* row=dataList->getChildElement(selRow);
  // this shouldn't happen
  if (row == NULL)
    return;
  String path, code;
  if ((button==loadButton) || (button==open2Button))
    {
      path=row->getStringAttribute(T("File"));
      code=SndLib::getInstance()->getInstrumentCode(path);
      if (code.isEmpty())
	return;
      if (button==loadButton)
	{
	  String msg=T("Loading ");
	  msg << path.quoted() << T("\n");
	  Console::getInstance()->printOutput(msg);
	  Scheme::getInstance()->eval(code);
	}
      else
	{
	  new TextEditorWindow(File::nonexistent, code, TextIDs::Lisp,
			       File(path).getFileName());
	}
    } 
  else if (button == open1Button)
    {
      path=row->getStringAttribute(T("Examples"));
      code=SndLib::getInstance()->getInstrumentCode(path);
      if (code.isEmpty())
	return;
      new TextEditorWindow(File::nonexistent, code, TextIDs::Lisp,
			   path);
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
  String text=String((const char*) Instruments::table_xml);
  XmlDocument dataDoc (text );
  insData = dataDoc.getDocumentElement();
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
  g.setColour (Colours::black);
  g.setFont (font);
  const XmlElement* rowElement = dataList->getChildElement(rowNumber);
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
  if (columnId == AutoloadColumn) 
    {
      AutoLoad* act = (AutoLoad*)comp;
      // update an existing component else create it
      if (act == NULL)
	act = new AutoLoad (this);
      act->setRowAndColumn(rowNumber, columnId);
      return act;
    }
  else // for any other column, just return 0,lumns directly.
    return NULL;
}

int InstrumentTable::getColumnAutoSizeWidth (int columnId)
{
  // this is the actions column containing a custom compone
  //    if (columnId == AutoloadColumn)
  //      return 80;

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

/*=======================================================================*
                    AutoLoad - custom component for each ins
		    THIS DOESNT WORK YET...
 *=======================================================================*/

InstrumentTable::AutoLoad::AutoLoad (InstrumentTable* dlg)
    : 
      autoButton (0),
      row(0),
      cid(0)
{
  dialog=dlg;
  Font font;
  addAndMakeVisible(autoButton = new ToggleButton (String::empty));
  autoButton->setButtonText(String::empty);//T("Auto")
  autoButton->addButtonListener (this);
  setSize (24, 24);
}

InstrumentTable::AutoLoad::~AutoLoad()
{
  deleteAndZero (autoButton);
}

void InstrumentTable::AutoLoad::setRowAndColumn (const int r, const int c)
{
  // Our demo code will call this when we may need to update our contents
  row = r;
  cid = c;
  //  autoButton->setToggleState(autoButton->getToggleState(),false);
  autoButton->repaint();
}

void InstrumentTable::AutoLoad::paint (Graphics& g)
{
   g.fillAll(Colours::white);
  //autoButton->repaint();
}

void InstrumentTable::AutoLoad::resized()
{
  autoButton->setBounds((getWidth()/2)-12, 0, 24, 24);
}

void InstrumentTable::AutoLoad::buttonClicked (Button* button)
{
  if (button == autoButton)
    {
      std::cout << "autobutton: row=" << row << " col=" << cid << "\n";
      //   getParentComponent()->repaint();
    }
}

#endif
