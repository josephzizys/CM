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
  // start Csound and load csd file, return true if successful
#ifdef PORTCSOUND
  StringArray toks ;
  toks.addTokens(input, true); // use JUCE tokenizer...
  int argc=toks.size();
  char *argv[argc];
  for (int i=0; i<argc; i++) {
    argv[i]=(char*)toks[i].toUTF8();
  }  
  //  printf("calling csoundCreate()...\n");
  csound=csoundCreate(NULL); 
  //  printf("calling csoundCompile()...\n");
  int result=csoundCompile(csound, argc, argv); 
  if (result != 0)  {
    csoundDestroy(csound);
    csound=NULL;
    //    printf("csoundCompile() failed, returning false\n");
    return false;
  }
#endif
  //  printf("csoundCompile() succeeded, returning true\n");
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
  : options (String::empty),
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

String CsoundPort::getOptions() {
  return options;
}

void CsoundPort::setOptions(String opts) {
  options=opts;
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
  props->setValue(T("CsoundOptions"), options);
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
  options=props->getValue(T("CsoundOptions"), DEFAULT);
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

  // Parse options into initargs passed to libCsound:
  String input = String::empty ;
  if ( options != String::empty )
    if ( ! options.containsOnly( T(" \t\n") ) )
      input << options;

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
  if ( ! connection->init( T("csound") + input) ) {
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

void CsoundPort::sendEvent(char type, int len, MYFLT *pars) {
  if ( isOpen() ) {
#ifdef PORTCSOUND
    if (tracing) {
      String msg = T("cs: ");
      msg << type << ((int)pars[0]) ;
      for (int i=1; i<len; i++)
	msg << T(", ") << ((float)pars[i] );
      msg << T("\n");
      console->printMessage( msg );
    }
    csoundScoreEvent(connection->csound, type, pars, len) ;
#endif
  }
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
    sendEvent ('i', len, pars) ;
  }
}

class ConfigureCsoundDialog : public Component,
			      public LabelListener,
			      public FilenameComponentListener,
			      public ButtonListener {
public:
  CsoundPort* port;
  Label* label1;
  Label* label2;
  Label* options;
  FilenameComponent* csdfile;
  ToggleButton* tracebutton;
  TextButton* savebutton;
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
    label1 (0),
    label2 (0),
    options (0),
    csdfile (0),
    savebutton (0),
    tracebutton (0)
{
  port=p;
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
  options->setText ( port->getOptions() , false);
  
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
			  T("*.csd"), 
			  String::empty,
			  T("Select CSD File..."));
  csdfile->addListener(this);

  StringArray files=port->csdfiles.getAllFilenames() ;
  csdfile->setRecentlyUsedFilenames(files);
  if (files.size() > 0)
    csdfile->setCurrentFile(port->csdfiles.getFile(0), false, false);
  addAndMakeVisible(csdfile);

  addAndMakeVisible( tracebutton = new ToggleButton(T("Trace output")));
  //tracebutton->setFont (Font (15.0000f, Font::plain));
  tracebutton->setButtonText(T("Trace output"));
  tracebutton->setToggleState(port->getTracing(), false);
  tracebutton->addButtonListener(this);
  
  //  addAndMakeVisible( savebutton = new TextButton(T( "save"), T("Save") ));
  //  savebutton->addButtonListener(this);
  setSize (600, 96 + 24 + 16);
}

ConfigureCsoundDialog::~ConfigureCsoundDialog() {
  deleteAndZero(label1);
  deleteAndZero(options);
  deleteAndZero(label2);
  deleteAndZero(csdfile);
  deleteAndZero(tracebutton);
  //  deleteAndZero(savebutton);
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
  tracebutton->setBounds(80, 96, 120, 24);
}

void ConfigureCsoundDialog::labelTextChanged (Label *changed) {
  port->setOptions( changed->getText() );
}

void ConfigureCsoundDialog::filenameComponentChanged (FilenameComponent* changed) {
  port->setCsdFile( changed->getCurrentFile() ) ;
}

void ConfigureCsoundDialog::buttonClicked (Button *clicked) {
  if (clicked->getName() == T("Trace output") ) {
    port->setTracing( clicked->getToggleState() );
  }
}

void CsoundPort::configure() {
  DialogWindow::showModalDialog(T("Configure CSound"), 
				new ConfigureCsoundDialog(this),
				NULL,
				Colour(0xffe5e5e5),
				true, false, false);
  save();
}
