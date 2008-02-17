#include "Csound.h"

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
  printf("argc=%d\n", argc);
  for (int i=0; i<argc; i++) {
    printf("argv[%d]=%s\n", i, toks[i].toUTF8() );
    argv[i]=(char*)toks[i].toUTF8();
  }  
  printf("calling csoundCreate()...\n");
  csound=csoundCreate(NULL); 
  printf("calling csoundCompile()...\n");
  int result=csoundCompile(csound, argc, argv); 
  if (result != 0)  {
    csoundDestroy(csound);
    csound=NULL;
    printf("csoundCompile() failed, returning false\n");
    return false;
  }
#endif
  printf("csoundCompile() succeeded, returning true\n");
  return true;
}  

void CsoundConnection::run () { 
  /* the performance loop. calls csoundPerformKsmps()   */ 

  printf("csound thread running!\n");

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
  printf("csound thread stopped!\n");
}

//
// Csound Port
//

CsoundPort::CsoundPort (ConsoleWindow *win) 
  : options (String::empty),
    csdfile (String::empty),
    console (NULL),
    running (false),
    connection (NULL)
{
  console=win;
}

CsoundPort::~CsoundPort () {
  if (connection != NULL) {
    if (connection->isThreadRunning())
      connection->stopThread(1000);
    delete connection;
  }
}

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

  // HARDWIRED ~/test.csd file for now...
  csdfile = File::getSpecialLocation(File::userHomeDirectory).getChildFile("test.csd").getFullPathName();
  if (! File(csdfile).existsAsFile()) {
    console->printError( T("Can't open Csound port: ~/test.csd does not exist!\n") );
    return false;
  }
  // Parse options and file into initargs passed to libCsound:
  String input = "csound" ;
  if ( options != String::empty )
    input << " " << options;
  if ( csdfile != String::empty )
    input << " " << csdfile;
  console->printMessage(T("Opening Csound with \"") + input + T("\" ... ") );
  if ( ! connection->init(input) ) {
    console->printError( T(":(\n") );
    printf("connection to csound failed, aborting open!\n");    
    delete connection;
    connection = NULL;
    return false;
  }
  console->printValues( T(":)\n") );
  printf("starting csound thread...\n");
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
  printf("csound closed!\n");
}

void CsoundPort::sendNote(String data) {
  if ( isOpen() ) {
    printf("send note!\n");
  }
}

void CsoundPort::testNote() {
  if ( isOpen() ) {
#ifdef PORTCSOUND
    String test=T("i1 0 1 60 10000\n");
    console->printMessage(T("Sending: ") + test);
    csoundInputMessage(connection->csound, test.toUTF8() );
#else
    console->printError(T("Csound port not supported.\n"));
#endif
  }
}


void CsoundPort::configure() {
  printf("csound configure dialog!\n");
}
