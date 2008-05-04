/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

#include "Csound.h"
#include "Grace.h"

//
// Csound Performace Thread
//

CsoundConnection::CsoundConnection (CsoundPort *_port, int _mode) :
  Thread (T("Csound Thread") ), port (NULL) ,mode (0), csound (NULL) {
  port=_port;  // backpointer to port
  mode=_mode;  // This connection for writing audio file
}

CsoundConnection::~CsoundConnection() {
}

bool CsoundConnection::init (String input) {
  // start Csound with init initargs
  printf("cs init: '%s'\n", input.toUTF8() );
#ifdef PORTCSOUND
  StringArray toks ;
  toks.addTokens(input, true); // use JUCE tokenizer...
  int argc=toks.size();
  char *argv[argc];
  for (int i=0; i<argc; i++) {
    argv[i]=(char*)toks[i].toUTF8();
  }  
  csound=csoundCreate(NULL); 
  int result=csoundCompile(csound, argc, argv); 
  if (result != 0)  {
    csoundDestroy(csound);
    csound=NULL;
    return false;
  }
#endif
  return true;
}  

bool CsoundConnection::isWriter() {
  return (mode == CsoundPort::portWrite) ;
}

void CsoundConnection::run () { 
  // csound performace thread, either writes a score in non-realtime
  // or keeps port open until user explictly closes it.
#ifdef PORTCSOUND
  // writing sound file
  if ( isWriter() ) {
    int res=0;
    printf("BEGIN WRITING\n");
    while ( res == 0 ) {
      if ( threadShouldExit() ) // user abort
	break;
      res=csoundPerformKsmps(csound);
    }
    printf("END WRITING\n");
  }
  else  {
    // open for realtime. call performKsmps() until user closes port.
    while ( true ) {
      if ( threadShouldExit() )
	break;
      // victor: "if you are sending events from the other thread to the
      // instance that calls performKsmps() in this thread, make sure
      // you are thread-safe, ie, that the events get inserted in
      // between calls."
      port->lockCsound();
      csoundPerformKsmps(csound) ;
      port->unlockCsound();
    }
  }
  csoundCleanup(csound);
  csoundDestroy(csound);
  csound=NULL;
  if ( isWriter() ) {
    printf("END OF WRITE THREAD\n");
    port->console->postConsoleTextMessage( T("Csound audio written.\n") );
    port->setWriting(false);
  }
  else {
    port->console->postConsoleTextMessage( T("Csound port closed.\n") ); 
    port->setOpen(false);
  }
#endif
}

//
// Csound Port
//

CsoundPort::CsoundPort (ConsoleWindow *win) 
  : portoptions (String::empty),
    fileoptions (String::empty),
    console (NULL),
    portopen (false),
    tracing (false),
    writing (false),
    scoremode (false),
    recordmode (false),
    scorestart (0.0),
    scorestamp (-1.0),
    port_connection (NULL),
    file_connection (NULL) {
  console=win;
  orcfiles.setMaxNumberOfItems(10);
  revert(); // initialize config with values stored in prefs
  exportdialog=new ExportCsoundDialog();
}

CsoundPort::~CsoundPort () {
  if (exportdialog != NULL) {
    delete exportdialog;
    exportdialog=NULL;
  }
  if (port_connection != NULL) {
    if (port_connection->isThreadRunning())
      port_connection->stopThread(1000);
    delete port_connection;
  }
  if (file_connection != NULL) {
    if (file_connection->isThreadRunning())
      file_connection->stopThread(1000);
    delete file_connection;
  }
}

void CsoundPort::lockCsound() {
  lock.enter();
}

void CsoundPort::unlockCsound() {
  lock.exit();
}

String CsoundPort::getPortOptions() {
  return portoptions;
}

void CsoundPort::setPortOptions(String opts) {
  portoptions=opts;
}

String CsoundPort::getFileOptions() {
  return fileoptions;
}

void CsoundPort::setFileOptions(String opts) {
  fileoptions=opts;
}

File CsoundPort::getOrcFile() {
  if ( orcfiles.getNumFiles() > 0 )
    return orcfiles.getFile(0);
  else
    return File::nonexistent;
}

void CsoundPort::setOrcFile(File file) {
  // if file is already in collection it moves it to position[0]
  orcfiles.addFile(file);
}

bool CsoundPort::isOpen() {
  return portopen ;
}

void CsoundPort::setOpen(bool b) {
  portopen=b ;
}

bool CsoundPort::isClosed() {
  return ! isOpen() ;
}

bool CsoundPort::isWriting() {
  return writing ;
}

void CsoundPort::setWriting(bool b ) {
  writing=b;
}

bool CsoundPort::isTraceMode() {
  return tracing;
}

void CsoundPort::setTraceMode(bool b) {
  tracing=b;
}

bool CsoundPort::isScoreMode() {
  return scoremode;
}

void CsoundPort::setScoreMode(bool b) {
  scoremode=b;
  if (b)
    setRecordMode(false);
}

bool CsoundPort::isRecordMode() {
  return recordmode;
}

void CsoundPort::setRecordMode(bool b) {
  recordmode=b;
  scorestamp=-1.0;
  if (b) {
    setScoreMode(false);
  }
}

void CsoundPort::setRecordStart (double st) {
  scorestart=st;
}

//
// Configuration saving and reverting
//

void CsoundPort::save() {
  PropertiesFile *props=((GraceApp*)JUCEApplication::getInstance())->getPreferences()->getProperties();
  props->setValue(T("CsoundPortOptions"), portoptions);
  props->setValue(T("CsoundFileOptions"), fileoptions);
  props->setValue(T("CsoundOrcFiles"), orcfiles.toString() );
}

void CsoundPort::revert() {
  // initialize port configureation from Preferences
  PropertiesFile *props=((GraceApp*)JUCEApplication::getInstance())->getPreferences()->getProperties();
  String DEFAULT = ((GraceApp*)JUCEApplication::getInstance())->
    getResourceDirectory().getChildFile("csound/grace.orc").getFullPathName();

  orcfiles.restoreFromString(props->getValue(T("CsoundOrcFiles"), DEFAULT));
  // set csound options to preferences or to default if none.
#ifdef MACOSX
  DEFAULT=T("-+rtaudio=coreaudio -o dac -d");
#elif defined(LINUX)
  DEFAULT=T("-+rtaudio=ALSA -o dac:hw:0 -d");
#else
  DEFAULT=T("-+rtaudio=portaudio -o dac -d");
#endif
  portoptions=props->getValue(T("CsoundPortOptions"), DEFAULT);
  DEFAULT=T("-W -o test.wav -d");
  fileoptions=props->getValue(T("CsoundFileOptions"), DEFAULT);
}

//
// Port opening
//

bool CsoundPort::open (bool port) {
  // Open realtime port or csound audio file
  OpenCsoundDialog* dialog;
  String title;
  int mode;

  if ( port ) {
    if ( isOpen() ) return false;
    dialog = new OpenCsoundDialog(this, CsoundPort::portOpen) ;
    title = T("Open Csound");
  }
  else {
    if ( isWriting() ) return false;
    dialog = new OpenCsoundDialog(this, CsoundPort::portWrite) ;
    title = T("Write Audio");
  }
  mode = DialogWindow::showModalDialog( title, dialog, NULL,
					Colour(0xffe5e5e5),
					true, false, false);
  delete dialog;
  switch (mode) {
  case CsoundPort::portClosed : 
    // aborted dialog
    return false;
    break;
  case CsoundPort::portOpen :
    // if we are re-opening the port delete any old exhausted thread.
    if (port_connection != NULL) {
      delete port_connection;
      port_connection = NULL;
    }
    break;
  case CsoundPort::portWrite:
    if (file_connection != NULL) {
      delete file_connection;
      file_connection = NULL;
    }
    break;
  default:
    return false;
  }
  // create a new connection
  CsoundConnection* conn = new CsoundConnection(this, mode) ;

  // Parse port or file options into initargs passed to libCsound:
  String input = String::empty ;
  String options = ( mode==portWrite ) ? fileoptions : portoptions ;

  if ( options != String::empty )
    if ( ! options.containsOnly( T(" \t\n") ) )
      input << options;

  if ( orcfiles.getNumFiles() == 0 ) {
    console->printError( T(">>> Error: missing ORC file.") );
    return false;
  }
  else if (! orcfiles.getFile(0).existsAsFile() ) {
    console->printError(T(">>> Error: file '") + 
			orcfiles.getFile(0).getFullPathName() +
		        T("' does not exist.\n"));
    return false;
  }
  else
    input << " " << orcfiles.getFile(0).getFullPathName();

  console->printMessage( T("Initializing Csound: ") + input + T(" ..."));

  if ( ! conn->init( T("csound ") + input) ) {
    console->printError(" :(\n Csound failed to initialize.\n");
    delete conn;
    return false;
  }
  // Csound is open and initialized
  console->printValues( T(" :)\n") );

  if ( mode==portWrite ) {
    console->printMessage( T("Writing Csound audio...\n") );   
    // send score data to csound before starting performance thread
    file_connection=conn;
    writeScore(file_connection->csound);
    setWriting(true);
  }
  else {
    console->printMessage( T("Csound port open.\n") );    
    port_connection=conn;
    setOpen(true);
  }
  // start performance thread for realtime or score rendering
  conn->startThread();
  return true;
}

void CsoundPort::close(bool port) {
  CsoundConnection* conn;
  if (port) {
    if ( isClosed() ) return;
    conn = port_connection;
    port_connection=NULL;
    setOpen(false);
  }
  else {
    if ( ! isWriting() ) return;
    conn = file_connection;
    file_connection=NULL;
    setWriting(false);
  }
  if (conn != NULL) {
    if ( conn->isThreadRunning() )
      conn->stopThread(1000);
    delete conn;
  }
}

//
// Score Events
//

CsoundScoreEv::CsoundScoreEv(char typ, int siz, MYFLT *flt, String strval,
			     int strpar)
    : pars (NULL), strarg (String::empty)
{
  type=typ;
  size=siz;
  pars=new MYFLT[siz];
  for (int i=0;i<siz;i++)
    pars[i]=flt[i];
  strarg=strval;
  strpos=strpar;
}

CsoundScoreEv::~CsoundScoreEv() {
  if ( pars != NULL )
    delete [] pars;
}

String CsoundScoreEv::pfieldsToText(String delim) {
  int i = 0;
  String txt = String::empty;
  String del = String::empty;
  for (i=0; i<strpos; i++) {
    txt << del << String( pars[i] );
    del = delim;
  }
  // quote a string arg if present
  if (i == strpos) {
    txt << del << T("\"") << strarg << T("\"");
    del = delim;
    i++;
  }
  for ( ; i<size; i++) {
    txt << del << String( pars[i] );
    del = delim;
  }
  return txt;
}

String CsoundScoreEv::toText(int fmat) {
  String text = String::empty;
  switch (fmat) {
  case CsoundPort::formatCsound :
    text << String(&type,1) << T(" ") << pfieldsToText( T(" ") );
    break;
  case CsoundPort::formatSalData :
    text << T("{") << pfieldsToText( T(" ") ) << T("}");
    break;
  case CsoundPort::formatLispData :
    text << T("(") << pfieldsToText( T(" ") ) << T(")");
    break;
  case CsoundPort::formatSalSend :
    text << T("send \"cs:") << String(&type,1) + T("\", ") 
	 << pfieldsToText( T(", "));
    break;
  case CsoundPort::formatLispSend :
    text << T("(send \"cs:") << String(&type,1) + T("\" ") 
	 << pfieldsToText( T(" ") ) << T(")");
    break;
  default:
    break;
  }
  return text;
}

//
// Score Interface
//

void CsoundPort::sendScoreEvent(CsoundScoreEv* ev, bool del) {
  // scoreMode means to add the event to the score rather than send
  // out the port
  if ( isScoreMode() ) {
    addScoreEvent(ev);
    if ( isTraceMode() )
      console->postConsoleTextMessage( (ev->toText(formatCsound) + T("\n")) );
  }
  else if ( isOpen() ) {
    // if port is open and we are not in score mode then send event to
    // csound and delete the event if del flag is true
    String msg = ev->toText(formatCsound);
    lockCsound();
#ifdef PORTCSOUND
    csoundInputMessage(port_connection->csound, msg.toUTF8() );
#endif
    unlockCsound();

    if ( isRecordMode() ) {
      if (scorestamp<0.0) {
	//	scorestamp=Time::highResolutionTicksToSeconds(Time::getHighResolutionTicks());	
	scorestamp=Time::getMillisecondCounterHiRes()/1000.0;
      }
      //      double now=Time::highResolutionTicksToSeconds(Time::getHighResolutionTicks());	
      double now=Time::getMillisecondCounterHiRes()/1000.0;
      ev->pars[1]= ev->pars[1] + scorestart + (now-scorestamp);
      addScoreEvent(ev);
      del=false;  // don't gc the event we are recording!
    }
    if ( isTraceMode() )
      console->postConsoleTextMessage( (msg + T("\n")) );
    if (del) delete ev;
  }
  else {
    // if no score or port open then delete the event
    if ( isTraceMode() )
      console->postConsoleTextMessage( (ev->toText(formatCsound) + T("\n")) );
    delete ev;
  }
}

void CsoundPort::addScoreEvent(CsoundScoreEv* ev) {
  score.add( ev);
}

void CsoundPort::sortScore() {
  score.sort(comparator,true);
}

void CsoundPort::clearScore() {
  score.clear();
}

void CsoundPort::playScore(double start, double end, double shift) {
#ifdef PORTCSOUND  
  if ( isOpen() ) {
    sortScore();
    int i = 0;
    MYFLT p1,pn;
    if (start>0.0) {
      for ( ; i<score.size() ; i++)
	if (score[i]->pars[1] >= start) 
	  break;
    }    
    for ( ; i<numScoreEvents(); i++ ) {
      if ( (end > 0.0) && (score[i]->pars[1] > end) )
	break;
      // shift event in time by shift amount
      p1=score[i]->pars[1];
      pn=score[i]->pars[1] + (MYFLT)shift;
      score[i]->pars[1] = (pn<0.0) ? 0.0 : pn;
      lockCsound();
      csoundInputMessage(port_connection->csound,
			 score[i]->toText(formatCsound).toUTF8() );
      unlockCsound();
      score[i]->pars[1] = p1;
    }
  }
#endif
}

void CsoundPort::writeScore(CSOUND* csound) {
#ifdef PORTCSOUND
  sortScore();
  int i;
  for (i=0; i<numScoreEvents(); i++ ) {
    csoundInputMessage(csound, score[i]->toText(formatCsound).toUTF8() );
  }
  // add 'e' statement at end time of the last note in the score
  float end=score[i-1]->pars[1]+score[i-1]->pars[2];
  String e=T("e 0.0 ") + String(end) + T(" 0.0");
  csoundInputMessage(csound, e.toUTF8() );
#endif
}

void CsoundPort::displayScore() {
}

void CsoundPort::printScore(double start, double end) {
  if ( isScoreEmpty() ) return;
  sortScore();
  int i = 0;
  if (start>0.0) {
    for ( ; i<score.size() ; i++)
      if (score[i]->pars[1] >= start) 
	break;
  }
  console->postConsoleTextMessage( T("s\n") );  
  for ( ; i<score.size(); i++) {
    if ( (end > 0.0) && (score[i]->pars[1] > end) )
      break;
    console->postConsoleTextMessage( (score[i]->toText(formatCsound) + T("\n")) );
  }
  console->postConsoleTextMessage( T("e\n") );  
}

void CsoundPort::exportScore() {
  int mode = DialogWindow::showModalDialog( T("Export Csound"), 
					    exportdialog,
					    NULL, Colour(0xffe5e5e5),
					    true, false, false);
  if (mode != 1) return;
  double start=exportdialog->frombuffer->getText().getDoubleValue();
  double endtime=exportdialog->tobuffer->getText().getDoubleValue();
  if ( endtime <= 0.0 ) endtime=3600.0*24.0;

  int format=exportdialog->formatmenu->getSelectedId();
  bool addi=exportdialog->itoggle->getToggleState();
  bool addf=exportdialog->ftoggle->getToggleState();
  int i=0;
  String text, indent, after;
  switch (format) {
  case CsoundPort::formatCsound :
    text=T("s\n"); indent=String::empty; after=T("e\n");
    break;
  case CsoundPort::formatLispData :
    text=T("(define csound-score\n  '(\n"); indent=T("    "); after=T("  ))\n");
    break;
  case CsoundPort::formatSalData :
    text=T("define variable csound-score = \n  {\n"); indent=T("   "); after=T("  }\n");
    break;
  case CsoundPort::formatLispSend :
    text=T("(begin\n"); indent=T("  "); after=T("  )\n");
    break;
  case CsoundPort::formatSalSend :
    text=T("begin\n"); indent=T("  "); after=T("end\n");
    break;
  }
  sortScore();
  if ( start > 0.0 ) {   // fast forward to user's start time
    for ( ; i<score.size(); i++)
      if ( start <= (double)(score[i]->pars[1]) )
	break;
  }
  for ( ; i<score.size(); i++) {
    if ( score[i]->pars[1] > endtime ) break;   // stop after endtime
    if ( (score[i]->type == 'i' && addi) || 
	 (score[i]->type == 'f' && addf) )
      text << indent << score[i]->toText(format) << T("\n");
  }
  text << after;
  // output to console, clipboard or file.
  if ( exportdialog->consoletoggle->getToggleState() )
    console->printMessage(text);
  else if ( exportdialog->clipboardtoggle->getToggleState() )
    SystemClipboard::copyTextToClipboard(text);
  else {
    String comm="; written by Grace " + Time::getCurrentTime().toString(true,true) + T("\n\n");
    exportdialog->filechooser->getCurrentFile().replaceWithText(comm + text);
  }
}

int CsoundPort::numScoreEvents() {
  return score.size();
}

bool CsoundPort::isScoreEmpty() {
  return score.size() == 0;
}

//
//  Dialogs
//

OpenCsoundDialog::OpenCsoundDialog (CsoundPort *p, int m)
  : port (NULL),
    mode (0),
    label1 (0),
    label2 (0),
    options (0),
    orcfile (0),
    openbutton (0),
    tracebutton (0)
{
  port=p;
  mode=m;
  addAndMakeVisible (label1 = new Label(String::empty, T("Options:")));
  label1->setFont (Font (15.0000f, Font::plain));
  label1->setJustificationType (Justification::centredRight);
  label1->setEditable (false, false, false);
  label1->setColour (TextEditor::textColourId, Colours::black);
  label1->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (options = new Label(T("Options"), String::empty));
  options->setColour (Label::backgroundColourId, Colours::white);
  options->setColour(Label::outlineColourId,  Colour (0xb2808080));
  options->setEditable(true, true, false);
  options->addListener(this);

  // if the score not empty this dialog is being called by "Write..."
  // otherwise its being called by "Open..."

  if ( mode==CsoundPort::portOpen )
    options->setText ( port->getPortOptions() , false);
  else
    options->setText ( port->getFileOptions() , false);

  addAndMakeVisible (label2 = new Label ( String::empty, T("Orchestra:"))) ;
  label2->setFont (Font (15.0000f, Font::plain));
  label2->setJustificationType (Justification::centredRight);
  label2->setEditable (false, false, false);

  orcfile = new FilenameComponent(String::empty, 
				  String::empty,
				  true, 
				  false, 
				  false, 
				  T("*.orc;*.csd"),
				  String::empty,
				  T("Select Orchestra File..."));
  orcfile->addListener(this);

  StringArray files=port->orcfiles.getAllFilenames() ;
  orcfile->setRecentlyUsedFilenames(files);
  if ( files.size() > 0 )
    orcfile->setCurrentFile(port->orcfiles.getFile(0), false, false);
  addAndMakeVisible(orcfile);
  if ( mode==CsoundPort::portOpen ) {
    //    addAndMakeVisible( tracebutton = new ToggleButton(T("Trace output")));
    //    tracebutton->setButtonText(T("Trace output"));
    //    tracebutton->setToggleState(port->getTracing(), false);
    //    tracebutton->addButtonListener(this);
  }  

  if ( mode==CsoundPort::portWrite ) 
    addAndMakeVisible( openbutton = new TextButton( T( "Write")));
  else 
    addAndMakeVisible( openbutton = new TextButton( T( "Open")));
  openbutton->addButtonListener(this);

  setSize (600, 96 + 24 + 16);
}

OpenCsoundDialog::~OpenCsoundDialog() {
  deleteAndZero(label1);
  deleteAndZero(options);
  deleteAndZero(label2);
  deleteAndZero(orcfile);
  if ( mode==CsoundPort::portOpen ) {
    //    deleteAndZero(tracebutton);
  }
  deleteAndZero(openbutton);
}

void OpenCsoundDialog::resized() {
  // line1: y=16
  label1->setBounds(8,   16, 64, 24);
  options->setBounds(80, 16, getWidth()-80-8-8, 24);
  // line2: y=26
  label2->setBounds(8,   56, 64, 24);
  orcfile->setBounds(80, 56, getWidth()-80-8-8, 24);
  // line3: y=96
  //  if ( mode==CsoundPort::portOpen )
  //    tracebutton->setBounds(80, 96, 120, 24);
  openbutton->setBounds((getWidth()/2)-74, 96, 148, 24);    
}

void OpenCsoundDialog::labelTextChanged (Label *changed) {
  if ( mode==CsoundPort::portOpen )
    port->setPortOptions( changed->getText() );
  else
    port->setFileOptions( changed->getText() );
}

void OpenCsoundDialog::filenameComponentChanged (FilenameComponent* changed) {
  port->setOrcFile( changed->getCurrentFile() ) ;
}

void OpenCsoundDialog::buttonClicked (Button *clicked) {
  if ( clicked->getName() == T("Trace output") ) {
    port->setTraceMode( clicked->getToggleState() );
  }
  else if ( clicked->getName() == T("Write") ) {
    port->save();
    ((DialogWindow *)getTopLevelComponent())->exitModalState(CsoundPort::portWrite);
  }
  else if ( clicked->getName() == T("Open") ) {
    port->save();
    ((DialogWindow *)getTopLevelComponent())->exitModalState(CsoundPort::portOpen);
  }
}

//
// Export dialog
//

ExportCsoundDialog::ExportCsoundDialog ()
  : scoregroup (0),
    fromlabel (0),
    tolabel (0),
    frombuffer (0),
    tobuffer (0),
    formatlabel (0),
    formatmenu (0),
    exportgroup (0),
    consoletoggle (0),
    clipboardtoggle (0),
    filetoggle (0),
    itoggle (0),
    ftoggle (0),
    exportbutton (0),
    filechooser (0) 
{
  scoregroup = new GroupComponent (String::empty, T("Score"));
  addAndMakeVisible (scoregroup);
  addAndMakeVisible (fromlabel = new Label (String::empty, T("From:")));
  fromlabel->setFont (Font (15.0000f, Font::plain));
  fromlabel->setJustificationType (Justification::centredRight);
  fromlabel->setEditable (false, false, false);
  fromlabel->setColour (TextEditor::textColourId, Colours::black);
  fromlabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
 
  frombuffer = new Label (T("From"), String::empty);
  addAndMakeVisible (frombuffer);
  frombuffer->setFont (Font (15.0000f, Font::plain));
  frombuffer->setEditable (true, true, false);
  frombuffer->setColour (Label::outlineColourId,  Colour (0xb2808080));
  frombuffer->setColour (Label::backgroundColourId, Colours::white);
  frombuffer->addListener (this);

  tolabel = new Label (String::empty, T("To:"));
  addAndMakeVisible (tolabel);
  tolabel->setFont (Font (15.0000f, Font::plain));
  tolabel->setJustificationType (Justification::centredLeft);
  tolabel->setEditable (false, false, false);
  tolabel->setColour (TextEditor::textColourId, Colours::black);
  tolabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  tobuffer = new Label (T("To"), String::empty);
  addAndMakeVisible (tobuffer);
  tobuffer->setFont (Font (15.0000f, Font::plain));
  tobuffer->setJustificationType (Justification::centredLeft);
  tobuffer->setEditable (true, true, false);
  tobuffer->setColour (Label::outlineColourId, Colour (0xb2808080));
  tobuffer->setColour (Label::backgroundColourId, Colours::white);
  tobuffer->addListener (this);
  
  formatlabel = new Label (String::empty, T("Export Format:"));
  addAndMakeVisible (formatlabel);
  formatlabel->setFont (Font (15.0000f, Font::plain));
  formatlabel->setJustificationType (Justification::centredRight);
  formatlabel->setEditable (false, false, false);
  formatlabel->setColour (Label::textColourId, Colours::black);
  formatlabel->setColour (Label::backgroundColourId, Colour (0x0));
  
  formatmenu = new ComboBox (String::empty);
  addAndMakeVisible (formatmenu);
  formatmenu->setEditableText (false);
  formatmenu->setJustificationType (Justification::centredLeft);
  formatmenu->setTextWhenNothingSelected (String::empty);
  formatmenu->addItem (T("Csound score"), CsoundPort::formatCsound);
  formatmenu->addItem (T("SAL data"), CsoundPort::formatSalData);
  formatmenu->addItem (T("Lisp data"), CsoundPort::formatLispData);
  formatmenu->addItem (T("SAL sends"), CsoundPort::formatSalSend);
  formatmenu->addItem (T("Lisp sends"), CsoundPort::formatLispSend);

  formatmenu->setSelectedId(1,false);
  formatmenu->addListener (this);
  
  exportgroup = new GroupComponent (String::empty, T("Export To"));
  addAndMakeVisible (exportgroup);
  
  consoletoggle = new ToggleButton (String::empty);
  addAndMakeVisible (consoletoggle);
  consoletoggle->setButtonText (T("Console"));
  consoletoggle->setRadioGroupId (1);
  consoletoggle->setToggleState (true, false);
  consoletoggle->addButtonListener (this);

  clipboardtoggle = new ToggleButton (String::empty);
  addAndMakeVisible (clipboardtoggle);
  clipboardtoggle->setButtonText (T("Clipboard"));
  clipboardtoggle->setRadioGroupId (1);
  clipboardtoggle->addButtonListener (this);
  
  filetoggle = new ToggleButton (String::empty);
  addAndMakeVisible (filetoggle);
  filetoggle->setButtonText (T("File:"));
  filetoggle->setRadioGroupId (1);
  filetoggle->addButtonListener (this);
  
  itoggle = new ToggleButton (String::empty);
  addAndMakeVisible (itoggle);
  itoggle->setButtonText (T(" i statements"));
  itoggle->setToggleState (true, false);
  
  ftoggle = new ToggleButton (String::empty);
  addAndMakeVisible (ftoggle);
  ftoggle->setButtonText (T("f statements"));
  ftoggle->setToggleState (true, false);
  
  exportbutton = new TextButton (T("Export"));
  addAndMakeVisible (exportbutton);
  exportbutton->addButtonListener (this);
  
  filechooser = new FilenameComponent( T("File"), 
				       File::getSpecialLocation(File::userHomeDirectory).getChildFile(T("untitled.sco")),
				       true, 
				       false, 
				       true, 
				       String::empty,
				       String::empty,
				       T("(choose file)"));
  filechooser->setEnabled(false);
  filechooser->addListener(this);
  addAndMakeVisible(filechooser);

  setSize (568, 248);
}

ExportCsoundDialog::~ExportCsoundDialog() {
  deleteAndZero (scoregroup);
  deleteAndZero (fromlabel);
  deleteAndZero (tolabel);
  deleteAndZero (frombuffer);
  deleteAndZero (tobuffer);
  deleteAndZero (formatlabel);
  deleteAndZero (formatmenu);
  deleteAndZero (exportgroup);
  deleteAndZero (consoletoggle);
  deleteAndZero (clipboardtoggle);
  deleteAndZero (filetoggle);
  deleteAndZero (itoggle);
  deleteAndZero (ftoggle);
  deleteAndZero (exportbutton);
  deleteAndZero (filechooser);
}

void ExportCsoundDialog::resized() {
  scoregroup->setBounds (16, 8, 536, 80);
  fromlabel->setBounds (25, 28, 48, 24);
  tolabel->setBounds (161, 28, 32, 24);
  frombuffer->setBounds (81, 28, 64, 24);
  tobuffer->setBounds (201, 28, 64, 24);
  formatlabel->setBounds (281, 28, 95, 24);
  formatmenu->setBounds (385, 28, 150, 24);
  exportgroup->setBounds (16, 101, 536, 80);
  consoletoggle->setBounds (32, 128, 80, 24);
  clipboardtoggle->setBounds (118, 128, 88, 24);
  filetoggle->setBounds (216, 128, 56, 24);
  itoggle->setBounds (32, 56, 104, 24);
  ftoggle->setBounds (144, 56, 104, 24);
  exportbutton->setBounds (216, 200, 150, 24);
  filechooser->setBounds (280, 128, 256, 24);
}

void ExportCsoundDialog::labelTextChanged (Label* labelThatHasChanged) {
  if (labelThatHasChanged == frombuffer) {
  }
  else if (labelThatHasChanged == tobuffer) {
  }
}

void ExportCsoundDialog::comboBoxChanged (ComboBox* comboBoxThatHasChanged) {
  if (comboBoxThatHasChanged == formatmenu) {
  }
}

void ExportCsoundDialog::buttonClicked (Button* buttonThatWasClicked) {
  if (buttonThatWasClicked == filetoggle)
    if ( filetoggle->getToggleState() )
      filechooser->setEnabled(true);
    else
      filechooser->setEnabled(false);
  else if (buttonThatWasClicked == exportbutton)
    ((DialogWindow *)getTopLevelComponent())->exitModalState(1);
  else
    filechooser->setEnabled(false);
}

void ExportCsoundDialog::filenameComponentChanged (FilenameComponent* filenameComponentThatHasChanged) {
  if (filenameComponentThatHasChanged == filechooser) {
  }
}
