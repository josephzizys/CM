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

CsoundConnection::CsoundConnection (CsoundPort *_port) :
  Thread (T("Csound Thread") ),
  port (NULL),
  csound (NULL) 
{
  port=_port;  // backpointer to port
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

void CsoundConnection::run () { 
  /* the performance loop. calls csoundPerformKsmps()   */ 

  //  printf("csound thread running!\n");

  while (true) {
    if ( threadShouldExit () )
      break;
#ifdef PORTCSOUND
    if ( csoundPerformKsmps(csound) != 0 )
      break; 
#endif
  }
#ifdef PORTCSOUND
  csoundCleanup(csound);
  csoundDestroy(csound);
#endif
  csound=NULL;
  port->running=false;
  //  printf("csound thread stopped!\n");
  port->console->printMessage("Csound closed.\n");
}

//
// Csound Port
//

CsoundPort::CsoundPort (ConsoleWindow *win) 
  : portoptions (String::empty),
    fileoptions (String::empty),
    console (NULL),
    running (false),
    connection (NULL) {
  console=win;
  csdfiles.setMaxNumberOfItems(10);
  revert(); // initialize config with values stored in prefs
}

CsoundPort::~CsoundPort () {
  if (connection != NULL) {
    if (connection->isThreadRunning())
      connection->stopThread(1000);
    delete connection;
  }
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

File CsoundPort::getCsdFile() {
  if (csdfiles.getNumFiles() > 0)
    return csdfiles.getFile(0);
  else
    return File::nonexistent;
}

void CsoundPort::setCsdFile(File file) {
  // if file is already in collection it moves it to position[0]
  csdfiles.addFile(file);
}

bool CsoundPort::getTracing() {
  return tracing;
}

void CsoundPort::setTracing(bool b) {
  tracing=b;
}

//
// Configuration saving and reverting
//

void CsoundPort::save() {
  PropertiesFile *props=((GraceApp*)JUCEApplication::getInstance())->getPreferences()->getProperties();
  props->setValue(T("CsoundPortOptions"), portoptions);
  props->setValue(T("CsoundFileOptions"), fileoptions);
  props->setValue(T("CsoundCsdFiles"), csdfiles.toString() );
  //  printf("saving config, saved options=%s\n", props->getValue("CsoundOptions").toUTF8());
}

void CsoundPort::revert() {
  // initialize port configureation from Preferences
  PropertiesFile *props=((GraceApp*)JUCEApplication::getInstance())->getPreferences()->getProperties();
  String DEFAULT = ((GraceApp*)JUCEApplication::getInstance())->
    getResourceDirectory().getChildFile("csound/grace.csd").getFullPathName();

  csdfiles.restoreFromString(props->getValue(T("CsoundCsdFiles"), DEFAULT));
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

bool CsoundPort::isOpen() {
  return running;
}

bool CsoundPort::open() {
  if ( isOpen() )
    return true;
  // we are re-opening the port, delete existing (exhausted) thread
  if (connection != NULL) {
    delete connection;
    connection = NULL;
  }
  connection = new CsoundConnection(this) ;

  // Parse port options into initargs passed to libCsound:
  String input = String::empty ;
  if ( portoptions != String::empty )
    if ( ! portoptions.containsOnly( T(" \t\n") ) )
      input << portoptions;

  if ( csdfiles.getNumFiles() == 0 ) {
    console->printError( T(">>> Error: no CSD file set. Use Ports>Csound>Configure... to configure the Csound session.") );
    return false;
  }
  else if (! csdfiles.getFile(0).existsAsFile() ) {
    console->printError(T(">>> Error: the file ") + 
			csdfiles.getFile(0).getFullPathName() +
		        T(" does not exist.\nUse Ports>Csound>Configure... to configure the Csound session."));
    return false;
  }
  else
    input << " " << csdfiles.getFile(0).getFullPathName();

  console->printMessage( (T("Opening Csound ") + input + T(" ... ") ) );
  if ( ! connection->init( T("csound ") + input) ) {
    console->printError(":(\n Csound port failed to open. Use Ports>Csound>Configure... to configure the Csound session.");
    delete connection;
    connection = NULL;
    return false;
  }
  //console->printMessage( T("CsoundPort: open") );
  console->printValues( T(":)\n") );
  connection->startThread();
  running=true;
  return true;
}

void CsoundPort::close()  {
  if ( ! running) return ;

  if (connection != NULL) {
      if ( connection->isThreadRunning() )
	connection->stopThread(1000);
    delete connection;
    connection=NULL;
  }
  running=false;
  //  printf("csound closed!\n");
}

void CsoundPort::printScoreEvent (char type, int len, MYFLT *pars) {
  //  String msg = T("cs: ");
  String msg = String::empty;
  msg << type << ((int)pars[0]) ;
  for (int i=1; i<len; i++)
    msg << T(" ") << ((float)pars[i] );
  msg << T("\n");
  console->printMessage( msg );
}

void CsoundPort::sendScoreEvent(char type, int len, MYFLT *pars) {
  if (tracing) 
    printScoreEvent(type, len, pars);
  if ( isOpen() ) {
#ifdef PORTCSOUND
    csoundScoreEvent(connection->csound, type, pars, len) ;
#endif
  }
  else
    addScoreEvent(type, len, pars);
}

void CsoundPort::testNote() {
  if ( isOpen() ) {
    int len=5;
    MYFLT pars[len];
    pars[0]=1;
    pars[1]=0;
    pars[2]=1;
    pars[3]=60 + Random::getSystemRandom().nextInt(24);
    pars[4]=1000;
    sendScoreEvent ('i', len, pars) ;
  }
}

//
// Score Interface
//

void CsoundPort::addScoreEvent(char type, int len, MYFLT *pars) {
  score.add( new CsoundScoreEv(type, len, pars) );
}

void CsoundPort::sortScore() {
  score.sort(comparator,true);
}

void CsoundPort::clearScore() {
  score.clear();
}

void CsoundPort::printScore(double start, double endtime) {
  int i;
  if ( isScoreEmpty() )
    return;
  sortScore();
  if (start > 0.0) {
    for (i=0; i<score.size(); i++)
      if ( score[i]->type=='i' && start==(double)(score[i]->pars[1]) )
	break;
  }
  else {
    for (i=0; i<score.size(); i++)
      if (score[i]->type == 'f') {
	printScoreEvent(score[i]->type, score[i]->size, score[i]->pars);
      }
      else break;
  }
  // i at first ins statement to print or end of buffer
  for ( ; i<score.size(); i++) 
    if ((double)(score[i]->pars[1]) > endtime) 
      break;
    else {
      printScoreEvent(score[i]->type, score[i]->size, score[i]->pars);
    }
}

int CsoundPort::numScoreEvents() {
  return score.size();
}

bool CsoundPort::isScoreEmpty() {
  return score.size() == 0;
}

//
// Configure Dialog
//

class ConfigureCsoundDialog : public Component,
			      public LabelListener,
			      public FilenameComponentListener,
			      public ButtonListener {
public:
  enum {configMode=0, writeMode};
  CsoundPort* port;
  int mode;
  Label* label1;
  Label* label2;
  Label* options;
  FilenameComponent* csdfile;
  ToggleButton* tracebutton;
  TextButton* writebutton;
  ConfigureCsoundDialog(CsoundPort* p);
  ~ConfigureCsoundDialog();
  //  void paint (Graphics& g);
  void resized();
  void filenameComponentChanged (FilenameComponent* changed);
  void labelTextChanged (Label *changed);
  void buttonClicked (Button *clicked);
};

ConfigureCsoundDialog::ConfigureCsoundDialog (CsoundPort *p)
  : port (NULL),
    mode (configMode),
    label1 (0),
    label2 (0),
    options (0),
    csdfile (0),
    writebutton (0),
    tracebutton (0)
{
  port=p;
  if ( ! p->isScoreEmpty() )
    mode=writeMode;
  addAndMakeVisible (label1 = new Label(String::empty, T("Options:")));
  label1->setFont (Font (15.0000f, Font::plain));
  label1->setJustificationType (Justification::centredRight);
  label1->setEditable (false, false, false);
  label1->setColour (TextEditor::textColourId, Colours::black);
  label1->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (options = new Label(T("Options"), String::empty));
  options->setColour (Label::backgroundColourId, Colours::white);
  options->setColour(Label::outlineColourId, Colours::silver);
  options->setEditable(true, true, false);
  options->addListener(this);

  // if the score not empty this dialog is being called by "Write..."
  // otherwise its being called for port configuration.

  if ( mode==configMode )
    options->setText ( port->getPortOptions() , false);
  else
    options->setText ( port->getFileOptions() , false);

  addAndMakeVisible (label2 = new Label ( String::empty, T("CSD File:"))) ;
  label2->setFont (Font (15.0000f, Font::plain));
  label2->setJustificationType (Justification::centredRight);
  label2->setEditable (false, false, false);

  csdfile = 
    new FilenameComponent(String::empty, 
			  String::empty,
			  true, 
			  false, 
			  false, 
			  ( mode==configMode ) ? T("*.csd") : T("*.csd;*.orc") ,
			  String::empty,
			  T("Select CSD File..."));
  csdfile->addListener(this);

  StringArray files=port->csdfiles.getAllFilenames() ;
  csdfile->setRecentlyUsedFilenames(files);
  if ( files.size() > 0 )
    csdfile->setCurrentFile(port->csdfiles.getFile(0), false, false);
  addAndMakeVisible(csdfile);

  if ( mode==configMode ) {
    addAndMakeVisible( tracebutton = new ToggleButton(T("Trace output")));
    tracebutton->setButtonText(T("Trace output"));
    tracebutton->setToggleState(port->getTracing(), false);
    tracebutton->addButtonListener(this);
  }  
  else if ( mode==writeMode ) {
    addAndMakeVisible( writebutton = new TextButton( T( "Write")));
    writebutton->addButtonListener(this);
  }

  setSize (600, 96 + 24 + 16);
}

ConfigureCsoundDialog::~ConfigureCsoundDialog() {
  deleteAndZero(label1);
  deleteAndZero(options);
  deleteAndZero(label2);
  deleteAndZero(csdfile);
  if ( mode==configMode ) {
    deleteAndZero(tracebutton);
  }
  else {
    deleteAndZero(writebutton);
  }
}

//void ConfigureCsoundDialog::paint (Graphics& g) {
//  g.fillAll (Colours::white);
//}

void ConfigureCsoundDialog::resized() {
  // line1: y=16
  label1->setBounds(8,   16, 64, 24);
  options->setBounds(80, 16, getWidth()-80-8-8, 24);
  // line2: y=26
  label2->setBounds(8,   56, 64, 24);
  csdfile->setBounds(80, 56, getWidth()-80-8-8, 24);
  // line3: y=96
  if ( mode==configMode )
    tracebutton->setBounds(80, 96, 120, 24);
  else
    writebutton->setBounds(getWidth()-8-8-64, 96, 64, 24);    
}

void ConfigureCsoundDialog::labelTextChanged (Label *changed) {
  if ( mode==configMode )
    port->setPortOptions( changed->getText() );
  else
    port->setFileOptions( changed->getText() );
}

void ConfigureCsoundDialog::filenameComponentChanged (FilenameComponent* changed) {
  port->setCsdFile( changed->getCurrentFile() ) ;
}

void ConfigureCsoundDialog::buttonClicked (Button *clicked) {
  if ( clicked->getName() == T("Trace output") ) {
    port->setTracing( clicked->getToggleState() );
  }
  else if ( clicked->getName() == T("Write") ) {
    ((DialogWindow *)getTopLevelComponent())->exitModalState(writeMode);
    //    ((DialogWindow *)getTopLevelComponent())->closeButtonPressed();
  }
}

void CsoundPort::configure() {
  DialogWindow::showModalDialog(T("Configure CSound Port"), 
				new ConfigureCsoundDialog(this),
				NULL,
				Colour(0xffe5e5e5),
				true, false, false);
  save();
}

void CsoundPort::writeScore() {
  // Open configure dialog in Write mode
  int res = DialogWindow::showModalDialog(T("Write Csound Score"),
					  new ConfigureCsoundDialog(this),
					  NULL,
					  Colour(0xffe5e5e5),
					  true, false, false);
  if (res != ConfigureCsoundDialog::writeMode ) return;
  if ( isScoreEmpty() ) return;

  // Parse options and cds file into initargs passed to libCsound:
  String input = String::empty ;
  if ( fileoptions != String::empty )
    if ( ! fileoptions.containsOnly( T(" \t\n") ) )
      input << fileoptions;
  if ( csdfiles.getNumFiles() == 0 ) {
    console->printError( T(">>> Error: no CSD or ORC file set.") );
    return;
  }
  else if (! csdfiles.getFile(0).existsAsFile() ) {
    console->printError(T(">>> Error: the file ") + 
			csdfiles.getFile(0).getFullPathName() +
		        T(" does not exist.\n"));
    return;
  }
  else
    input << " " << csdfiles.getFile(0).getFullPathName();

  // initialize csound 
  console->printMessage( (T("Writing Csound score: ") + input + T(" ...\n") ) );
  CsoundConnection *conn=new CsoundConnection(this);
  if ( ! conn->init( T("csound ") + input) ) {
    console->printError(":(\n Csound failed to start.");
    delete conn;
    return ;
  }
  save();
#ifdef PORTCSOUND
  // sort the score
  sortScore();
  // add the events
  for (int i=0; i<numScoreEvents(); i++ ) 
    csoundScoreEvent(conn->csound, score[i]->type, score[i]->pars, score[i]->size) ;
  // run csound performace loop
  while ( csoundPerformKsmps( conn->csound ) == 0) ;
  // cleanup and close csoun
  csoundCleanup(conn->csound);
  csoundDestroy(conn->csound);
#endif
  console->printMessage( T("done!\n") );
}

