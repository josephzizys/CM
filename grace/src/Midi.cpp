#include "Midi.h"
#include "Grace.h"
//#include "Chicken.h"

//
//  Nodes
//

MidiNode::MidiNode(int typ, double wait, float *vals, int num_vals)
  : type (0), time (0.0), num (0) { 
  type=typ;
  num=num_vals;
  time=wait;
  for (int i=0;i<num_vals;i++)
    values.add( vals[i]);

}

MidiNode::MidiNode(int typ, double wait, float data1, float data2) {
  type=typ;
  num=2;
  time=wait;
  values.add(data1);
  values.add(data2);
}

MidiNode::MidiNode(int typ, double wait, float data1, float data2, float data3) {
  type=typ;
  num=3;
  time=wait;
  values.add(data1);
  values.add(data2);
  values.add(data3);
}

MidiNode::~MidiNode() { 
  values.clear();
}

void MidiNode::process() {
  switch (type) {
  case NODEON:
    if ( values[ONVEL] > 0.0 ) {
      // note on velocity range either 0.0-1.0 or 0.0-127.0
      float vel=(values[ONVEL]>1.0) ? (values[ONVEL]/127.0f) : values[ONVEL] ;
      midiOutPort->device->
	sendMessageNow( MidiMessage::noteOn((int)values[ONCHAN]+1, 
					    (int)values[ONKEY], 
					    vel));
    }
    else
      midiOutPort->device->
	sendMessageNow( MidiMessage::noteOff( (int)values[ONCHAN]+1,
					      (int)values[ONKEY]) );
    break;
  case NODEOFF:
    midiOutPort->device->
      sendMessageNow( MidiMessage::noteOff( (int)values[OFFCHAN]+1,
					    (int)values[OFFKEY]) );
    break;
  case NODEPROG :
    midiOutPort->device->
      sendMessageNow( MidiMessage::programChange( (int)values[PROGCHAN]+1,
						  (int)values[PROGNUM]) );
    break;
  case NODECTRL :
    midiOutPort->device->
      sendMessageNow( MidiMessage::controllerEvent( (int)values[CTRLCHAN]+1,
						    (int)values[CTRLNUM],
						    (int)values[CTRLVAL]) );
    break;
  default:
    break;
  }
}

//
// Queue
//

MidiOutPort::MidiOutPort(ConsoleWindow *win)
  : Thread(T("Midi Out Port")),
    device(0),
    devid (-1) {	
  console=win;
}

MidiOutPort::~MidiOutPort()
{
  printf("deleting MidiOutPort\n");
  if ( device != NULL ) delete device;
  outputNodes.clear();
}

void MidiOutPort::open(String name) {
  StringArray devices = MidiOutput::getDevices ();
  int id=-1;
  for (int i=0;i<devices.size();i++)
    if (devices[i] == name) {
      id=i;
      break;
    }
  if ( id == -1 )
    console->printWarning(T("Warning: Midi output device ") + 
			  name + T(" does not exist.\n"));
  else
    open(id);
}

void MidiOutPort::open(int id) {
  // dont do anything if opening same port
  if ( id == devid ) return;
  // delete current port. IS THIS CORRECT?
  if ( device != NULL ) {
    delete device;
    devid=-1;
  }
  device = MidiOutput::openDevice(id);
  if ( device == NULL )
    console->printError(T(">>> Error: Failed to open midi device (dev=") + 
			String(id) + T(").\n"));
  else
    devid=id;
  printf("Midi out: dev=%d\n", id);
}

bool MidiOutPort::isOpen(int id) {
  if ( device == NULL )
    return false;
  else if ( id == -1) // asking if ANY output device is open
    return true;
  else
    return (id == devid); // asking if specific dev is open
}

//
// output queue 
//

void MidiOutPort::run() {
  double qtime, utime;
  MidiNode* node;
  while ( true ) {
    if ( threadShouldExit() )
      break;
    while ( true ) {     
      outputNodes.lockArray();
      node=outputNodes.getFirst();
      if ( node == NULL ) {
	outputNodes.unlockArray();      
	break;
      }
      qtime=node->time;
      utime=Time::getMillisecondCounterHiRes() ;
      // this should probably test if the difference between qtime and
      // utime is less that 1ms, if not then it probably shouldn't
      // sleep (?)
      if ( qtime > utime ) {
	outputNodes.unlockArray();
	wait(1);
      }
      else {
      node->process();
      outputNodes.remove(0, true);
      outputNodes.unlockArray();      
      }
    }
    wait(-1);
  }
}

/*** THIS VERSIONS WORKS
void MidiOutPort::run() {
  double curr;
  while( !threadShouldExit() ) {
    while(outputNodes.size() > 0) {     
      curr = Time::getMillisecondCounterHiRes() ;
      while ( outputNodes.getFirst()->time <= curr ) {       
        outputNodes.lockArray();
	outputNodes.getFirst()->process();
        outputNodes.remove(0, true);
        if(outputNodes.size() == 0) {
          outputNodes.unlockArray();
          break;
        }
        outputNodes.unlockArray();
	// im not sure that we want to do this, it
        //curr = Time::getMillisecondCounterHiRes() ;
      }
      wait(1);
    }
    wait(-1);
  }
}
***/

bool MidiOutPort::isOutputQueueActive() { 
  outputNodes.lockArray(); 
  int n=outputNodes.size();
  outputNodes.unlockArray();
  return (n > 0);
}

void MidiOutPort::clear()
{
  outputNodes.lockArray();
  outputNodes.clear();
  // avoid hanging notes
  if ( device != 0 )
    for ( int i=0; i< 16; i++ )
      device->sendMessageNow( MidiMessage::allSoundOff(i) );
  outputNodes.unlockArray();
}

void MidiOutPort::addNode(MidiNode *n) {
  outputNodes.lockArray();
  n->midiOutPort = this;
  // MILLI
  n->time = (n->time * 1000.0) + Time::getMillisecondCounterHiRes();
  outputNodes.addSorted(comparator, n);
  outputNodes.unlockArray();
  /*  printf("added type=%d, at %f pos=%d of %d\n", 
	 n->type,
	 n->time,
	 outputNodes.indexOf(n),
	 outputNodes.size()
	 ); */
  notify();
}

void MidiOutPort::sendNote(double wait, double dur, float key, float vel, float chan) {
  // dont do anything if there is no open output port!
  if ( device == NULL ) return;
  addNode( new MidiNode(MidiNode::NODEON, wait, chan, key, vel) );
  addNode( new MidiNode(MidiNode::NODEOFF, wait+dur, chan, key) );
}

void MidiOutPort::sendOn(double wait, float key, float vel, float chan) {
  // dont do anything if there is no open output port!
  if ( device == NULL ) return;
  addNode( new MidiNode(MidiNode::NODEON, wait, chan, key, vel) );
}

void MidiOutPort::sendOff(double wait, float key, float vel, float chan) {
  // dont do anything if there is no open output port!
  if ( device == NULL ) return;
  addNode( new MidiNode(MidiNode::NODEOFF, wait, chan, key) );
}

void MidiOutPort::sendProg(double wait, float prog, float chan) {
  // dont do anything if there is no open output port!
  if ( device == NULL ) return;
  addNode( new MidiNode(MidiNode::NODEPROG, wait, chan, prog) );
}

void MidiOutPort::sendCtrl(double wait, float ctrl, float val, float chan) {
  // dont do anything if there is no open output port!
  if ( device == NULL ) return;
  addNode( new MidiNode(MidiNode::NODECTRL, wait, chan, ctrl, val) );
}

void MidiOutPort::testMidiOutput () {
  // Tobias Kunze's little testing algo from cm 1.4
  double time = 0;
  for (int x=0; x<12; x++) {
    // vals[0]=keynum, [1]=velocity, [2]=channel
    float key = x + (12 * (3 + Random::getSystemRandom().nextInt(5) )) ;
    float vel = 32.0 + Random::getSystemRandom().nextInt(64);
    // MILLI
    float dur = ((( 2 + Random::getSystemRandom().nextInt(6)) ^ 2) * (60.0 / 1000.0));
    sendNote(time, dur, key, vel, 0.0);
    // MILLI
    time += ((Random::getSystemRandom().nextInt(5) ^ 2) * (60.0 / 1000.0));
  }
}

//
// MIDI Input
//

MidiInPort::MidiInPort(ConsoleWindow *win)
  : devid (-1),
    device (NULL),
    channelmask (0xFFFFFFFF),
    messagefilt (0),
    runmode (STOPPED),
    trace (false),
    schemehook (0) {
  console=win;
}

MidiInPort::~MidiInPort() {
  if (device != NULL) {
    if ( isActive() )
      stop();
    delete device;
  }
}

void MidiInPort::open(int id) {
  // dont do anything if opening same port
  if ( id == devid )
    return;
  else if ( isActive() ) {
    console->printError(T(">>> Error: Midi input device ") +
			String(id) + T(" is currently active.\n"));
    return;
  }
  if ( device != NULL ) {
    stop();
    delete device;
    devid=-1;
  }
  device = MidiInput::openDevice(id, this);
  if ( device == NULL )
    console->printError(T(">>> Error: Failed to open midi input device ") + 
			String(id) + T(".\n"));
  else
    devid=id;
  printf("Opened midi input device %d\n", id);
}

void MidiInPort::open(String name) {
  StringArray devices = MidiInput::getDevices ();
  int id=-1;
  for (int i=0;i<devices.size();i++)
    if (devices[i] == name) {
      id=i;
      break;
    }
  if ( id == -1 )
    console->printWarning(T("Warning: Midi input device ") + 
			  name + T(" does not exist.\n"));
  else
    open(id);
}

bool MidiInPort::isOpen(int id) {
  if ( device == NULL )
    return false;
  else if ( id == -1) // asking if ANY device is open
    return true;
  else
    return (id == devid); // asking if specific dev is open
}

bool MidiInPort::start(int mode) {
  if ( !isOpen() ) {
    console->printError(T(">>> Error: Midi input port is not open.\n"));
    return false;
  }
  else if ( isActive() ) {
    console->printError(T(">>> Error: Midi input port already active.\n"));
    return true;
  }
  // NOW DO WHATEVER SETUP IS NEEDED FOR NEW RUNMODE
  runmode=mode;
  // start the device
  device->start();
  return true;
}

void MidiInPort::stop() {
  if ( !isOpen() ) {
    console->printError(T(">>> Error: Midi input port is not open.\n"));
    return;
  }
  else if ( !isActive() ) {
    //console->printError(T(">>> Error: Midi input not active.\n"));
    return;
  }
  // stop the device
  device->stop();
  // NOW DO WHATEVER CLEANUP IS NEEDED FOR CURRENT RUNMODE
  runmode=STOPPED;
}

bool MidiInPort::isActive(int mode) {
  if ( runmode==STOPPED )
    return false;
  else if ( mode == -1 ) // test if anything is active
    return true;
  else
    return (runmode == mode); // test specific run mode
}

void MidiInPort::startSchemeInput(C_word func, unsigned int chanmask, 
				     unsigned int msgfilt) {
  // SET UP THE SCHEME HOOK FOR CALLBACK BEFORE STARTING
  start(SCHEMEHOOK);
}

void MidiInPort::stopSchemeInput() {
  if ( !isActive(SCHEMEHOOK) ) {
    //console->printError(T(">>> Error: Midi input port has no hook.\n"));
    return;
  }
  stop();
  // CLEAR SCHEME HOOK AFTER STOPPING
}

void MidiInPort::startTestInput() {
  if (! start(TESTING) )
    return;
  trace=true;
}

void MidiInPort::stopTestInput() {
  if ( !isActive(TESTING) ) {
    return;
  }
  stop();
  trace=false;
}

void MidiInPort::startRecordInput() {
  if ( ! start(RECORDING) )
    return;
}

void MidiInPort::stopRecordInput() {
  if ( ! isActive(RECORDING) )
    return;
  stop();
}





void MidiInPort::setTracing(bool t) {
  printf("tracing set to %d\n", t);
  trace=t;
}

bool MidiInPort::isTracing() {
  return trace;
}

unsigned int MidiInPort::getChannelMask() {
  return channelmask;
}

unsigned int MidiInPort::getMessageFilter() {
  return messagefilt;
}  

void MidiInPort::setChannelMask(unsigned int m) {
  if (m==0) m=0xFFFFFFFF;
  channelmask=m;
}

void MidiInPort::setMessageFilter(unsigned int f) {
  messagefilt=f;
}

void MidiInPort::handleIncomingMidiMessage (MidiInput *dev, const MidiMessage &msg) {
  // JUCE: chan>0 means channel message, 0 means not a channel message 
  int chan=msg.getChannel();
  String info=String::empty;

  if ( chan>0 ) { 
    chan--;  // we are zero based folk
    // test if channel message is wanted
    if ( (channelmask && (1 << chan)) ) {
      // FIXME: REPLACE TRUES WITH MESSAGEFILT TEST...
      if ( msg.isNoteOn() && true ) {
	if ( trace )
	  info=T("On: chan=") + String(chan) + T(" key=") + 
	    String(msg.getNoteNumber()) +
	    T(" vel=") + String(msg.getVelocity());
	// now handle note off message...
      }
      else if ( msg.isNoteOff() && true ) {
	if ( trace )
	  info=T("Off: chan=") + String(chan) + 
	    T(" key=") + String(msg.getNoteNumber());
	// now handle note off message...
     }
      else if ( msg.isProgramChange() && true ) {
	if ( trace )
	  info=T("Prog: chan=") + String(chan) + 
	    T(" prog=") + 
	    MidiMessage::getGMInstrumentName(msg.getProgramChangeNumber());
	// now handle program change message...
      }
      else if ( msg.isController() && true ) {
	if ( trace )
	  info=T("Ctrl: chan=") + String(chan) + 
	    T(" ctrl=") + 
	    MidiMessage::getControllerName(msg.getControllerNumber()) +
	    T(" value=") + String(msg.getControllerValue());
	// now handle control change message
      }
      else if ( msg.isPitchWheel() && true ) {
	if ( trace )
	  info=T("Pw: chan=") + String(chan) + T(" value=") +
	    String(msg.getPitchWheelValue());
	// now handle pitch wheel message...
      }
      else if ( msg.isChannelPressure() && true ) {
	if ( trace )
	  info=T("Cp: chan=") + String(chan) + T(" value=") +
	    String(msg.getChannelPressureValue());
	// now handle channel pressure message...

      }
      else if ( msg.isAftertouch() && true ) {
	if ( trace )
	  info=T("At: chan=") + String(chan) + T(" value=") +
	    String(msg.getAfterTouchValue());
      // now handle aftertouch message...
      }
      else {
	// drop unwanted type of message
	return;
      }
    }
    else {
      // drop unwanted channel message
      return;
    }
  }
  else {
    // message is either sysex or meta, drop for now in either case
    return;
  }

  // AT THIS POINT CALL RECORDING CODE OR SCHEMEHOOK COE
  if ( isActive(SCHEMEHOOK) ) {
    printf("Calling scheme hook!\n");
  }
  else if ( isActive(RECORDING) ) {
    printf("Recording message!\n");
  }

  if (trace) {
    // i think this was crashing Grace because this callback is not
    // happening in the main thread (?)
    //console->printMessage(String(msg.getTimeStamp(), 3) + T(" ") + info + T("\n"));
    console->postConsoleTextMessage(String(msg.getTimeStamp(), 3) +
				    T(" ") + info + T("\n"), 
				    ConsoleMessage::TEXT, true);
  }
}

void MidiInPort::handlePartialSysexMessage (MidiInput *dev, const uint8 *data, 
					       const int num, const double time) {
  printf("in MIDI sysex callback\n");  
}
