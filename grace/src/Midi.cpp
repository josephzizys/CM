/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision: 1495 $
// $Date: 2007-11-25 19:01:22 -0600 (Sun, 25 Nov 2007) $ 

#include "Midi.h"
#include "Grace.h"
#include "Toolbox.h"

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

MidiNode::MidiNode(int typ, double wait, float data1, float data2,
		   float data3) {
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
      float vel=(values[ONVEL]>1.0) ? (values[ONVEL]/127.0f)
	: values[ONVEL] ;
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
  case NODEBEND :
    midiOutPort->device->
      sendMessageNow( MidiMessage::pitchWheel( (int)values[BENDCHAN]+1,
					       (int)values[BENDVAL]) );
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
    devid (-1),
    // micro initialized for semitone
    microdivisions (1),
    microincrement (1.0),
    microchancount (16),
    microchanblock (16),
    avoiddrumtrack (true),
    pitchbendwidth (2)
{	
  console=win;
  for(int i=0;i<16;i++)
    programchanges[i]=0;
  tuningnames.add(T("Semitone"));
  tuningnames.add(T("Quartertone"));
  tuningnames.add(T("33 Cent"));
  tuningnames.add(T("25 Cent"));
  tuningnames.add(T("20 Cent"));
  tuningnames.add(T("17 Cent" ));
  tuningnames.add(T("14 Cent"));
  tuningnames.add(T("12 Cent"));
  tuningnames.add(T("11 Cent"));
  tuningnames.add(T("10 Cent"));
  tuningnames.add(T("9 Cent"));
  tuningnames.add(T("8 Cent"));
  tuningnames.add(T("7.7 Cent" ));
  tuningnames.add(T("7.1 Cent"));
  tuningnames.add(T("6.6 Cent"));
  tuningnames.add(T("6.25 Cent"));
}

MidiOutPort::~MidiOutPort()
{
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
  //printf("Midi out: dev=%d\n", id);
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

void MidiOutPort::sendNote(double wait, double duration, float keynum, 
			   float amplitude, float channel) {
  // dont do anything if there is no open output port!
  if ( device == NULL ) return;
  jlimit(channel, (float)0.0, (float)15.0);
  // only microtune if current tuning is not semitonal and user's
  // channel is a microtonal channel.
  if ( (getTuning() > 1) && (channel < microchanblock) ) {
    // insure user's channel a valid microtonal channel, ie a channel
    // within the first zone of microtuned channels and then shift to
    // actual physical channel
    int chan=(((int)channel) % microchancount) * microdivisions;
    // calculate integer midi key quantize user's keynum to microtonal
    // resolution size. this may round up to the next keynum
    float foo=keynum;
    // quantize keynumber to tuning resolution. if it rounds up (or
    // down) to an integer keynum then we dont need to microtune
    keynum = Toolbox::quantize( keynum, microincrement);
    int key=(int)keynum;
    // only microtune if we have a fractional keynum
    if ( keynum > key ) {
      // divide the fractional portion of keynum by the resolution size
      // to see which zone of channels its in
      int zone=(int)((keynum-key)/microincrement);
      // shift channel to the appropriate zone and set keynum to integer
      chan += zone;
      if ( (chan == 9) && avoiddrumtrack ) {
	chan--;
      }
      //      printf("keynum=%f, quant=%f, chan=%d -> zone=%d, chan=%d, key=%d\n",
      //	     foo, keynum, (int)channel, zone, chan, key);
      channel=chan;
      keynum=key;
    }
  }
  addNode( new MidiNode(MidiNode::NODEON, wait, channel, keynum, amplitude) );
  addNode( new MidiNode(MidiNode::NODEOFF, wait+duration, channel, keynum) );
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

void MidiOutPort::sendBend(double wait, float bend, float chan) {
  // dont do anything if there is no open output port!
  if ( device == NULL ) return;
  addNode( new MidiNode(MidiNode::NODEBEND, wait, chan, bend) );
}

void MidiOutPort::testMidiOutput () {
  // Tobias Kunze's little testing algo from cm 1.4
  double time = 0;
  for (int x=0; x<12; x++) {
    // vals[0]=keynum, [1]=velocity, [2]=channel
    float key = x + (12 * (3 + Random::getSystemRandom().nextInt(5) )) ;
    float vel = 32.0 + Random::getSystemRandom().nextInt(64);
    // MILLI
    float dur = ((( 2 + Random::getSystemRandom().nextInt(6)) ^ 2) *
		 (60.0 / 1000.0));
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
  //printf("Opened midi input device %d\n", id);
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
  //printf("tracing set to %d\n", t);
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

void MidiInPort::handleIncomingMidiMessage (MidiInput *dev, 
					    const MidiMessage &msg) {
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
    console->postConsoleTextMessage(String(msg.getTimeStamp(), 3) +
				    T(" ") + info + T("\n"), 
				    ConsoleMessage::TEXT, true);
  }
}

void MidiInPort::handlePartialSysexMessage (MidiInput *dev,
					    const juce::uint8 *data, 
					    const int num, 
					    const double time) {
}

///
/// Microtuning
///

/* tuning array (in cents, tunings X channels)

    0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
    ----------------------------------------------
 1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 2  0 50  0 50  0 50  0 50  0 50  0 50  0 50  0 50
 3  0 33 66  0 33 66  0 33 66  0 33 66  0 33 66  0
 4  0 25 50 75  0 25 50 75  0 25 50 75  0 25 50 75
 5  0 20 40 60 80  0 20 40 60 80  0 20 40 60 80  0
 6  0 16 33 50 66 83  0 16 33 50 66 83  0  0  0  0
 7  0 14 28 42 57 71 85  0 14 28 42 57 71 85  0  0
 8  0 12 25 37 50 62 75 87  0 12 25 37 50 62 75 87
 9  0 11 22 33 44 55 66 77 88  0  0  0  0  0  0  0
10  0 10 20 30 40 50 60 70 80 90  0  0  0  0  0  0
11  0  9 18 27 36 45 54 63 72 81 90  0  0  0  0  0
12  0  8 16 25 33 41 50 58 66 75 83 91  0  0  0  0
13  0  7 15 23 30 38 46 53 61 69 76 84 92  0  0  0
14  0  7 14 21 28 35 42 50 57 64 71 78 85 92  0  0
15  0  6 13 20 26 33 42 46 53 60 66 73 80 86 93  0
16  0  6 12 18 25 31 37 43 50 56 62 68 75 81 87 93

;; this calculates the array contents
(loop for div from 1 to 16 
   for zones = div
   for width = (floor (/ 16 div))
   for uses = (* width zones)
   do
     (let ((a (/ 1.0 div)))
       (format t "~:[{~;{{~]" (= div 1))
       (loop for c below uses by zones
	  do (loop for z below zones 
	        do (format t "~:[, ~;~]~f" (= z c 0) (* z a))))
       (loop repeat (- 16 uses) do (format t ", ~f" 0.0))
       (format t "}~:[,~%~;};~%~]" (= div 16))))
*/

float MidiOutPort::channeltunings[16][16] =
{{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{0.0, 0.5, 0.0, 0.5, 0.0, 0.5, 0.0, 0.5, 0.0, 0.5, 0.0, 0.5, 0.0, 0.5, 0.0, 0.5},
{0.0, 0.33333334, 0.6666667, 0.0, 0.33333334, 0.6666667, 0.0, 0.33333334, 0.6666667, 0.0, 0.33333334, 0.6666667, 0.0, 0.33333334, 0.6666667, 0.0},
{0.0, 0.25, 0.5, 0.75, 0.0, 0.25, 0.5, 0.75, 0.0, 0.25, 0.5, 0.75, 0.0, 0.25, 0.5, 0.75},
{0.0, 0.2, 0.4, 0.6, 0.8, 0.0, 0.2, 0.4, 0.6, 0.8, 0.0, 0.2, 0.4, 0.6, 0.8, 0.0},
{0.0, 0.16666667, 0.33333334, 0.5, 0.6666667, 0.8333334, 0.0, 0.16666667, 0.33333334, 0.5, 0.6666667, 0.8333334, 0.0, 0.0, 0.0, 0.0},
{0.0, 0.14285715, 0.2857143, 0.42857146, 0.5714286, 0.71428573, 0.8571429, 0.0, 0.14285715, 0.2857143, 0.42857146, 0.5714286, 0.71428573, 0.8571429, 0.0, 0.0},
{0.0, 0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 0.875, 0.0, 0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 0.875},
{0.0, 0.11111111, 0.22222222, 0.33333334, 0.44444445, 0.5555556, 0.6666667, 0.7777778, 0.8888889, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.90000004, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{0.0, 0.09090909, 0.18181819, 0.27272728, 0.36363637, 0.45454547, 0.54545456, 0.6363636, 0.72727275, 0.8181819, 0.90909094, 0.0, 0.0, 0.0, 0.0, 0.0},
{0.0, 0.083333336, 0.16666667, 0.25, 0.33333334, 0.4166667, 0.5, 0.5833334, 0.6666667, 0.75, 0.8333334, 0.9166667, 0.0, 0.0, 0.0, 0.0},
{0.0, 0.07692308, 0.15384616, 0.23076925, 0.30769232, 0.3846154, 0.4615385, 0.53846157, 0.61538464, 0.6923077, 0.7692308, 0.84615386, 0.923077, 0.0, 0.0, 0.0},
{0.0, 0.071428575, 0.14285715, 0.21428573, 0.2857143, 0.35714287, 0.42857146, 0.5, 0.5714286, 0.6428572, 0.71428573, 0.7857143, 0.8571429, 0.92857146, 0.0, 0.0},
{0.0, 0.06666667, 0.13333334, 0.20000002, 0.26666668, 0.33333334, 0.40000004, 0.4666667, 0.53333336, 0.6, 0.6666667, 0.73333335, 0.8000001, 0.86666673, 0.9333334, 0.0},
{0.0, 0.0625, 0.125, 0.1875, 0.25, 0.3125, 0.375, 0.4375, 0.5, 0.5625, 0.625, 0.6875, 0.75, 0.8125, 0.875, 0.9375}};

int MidiOutPort::getTuning() {
  return microdivisions;
}

void MidiOutPort::setTuning(int tune, bool send) {
  // valid tunings are 1-16, interpreted as divisions per semitone.
  // each division of a tuning claims a physical midi channel tuned to
  // the division's cent value by sending a pitch bend. channels with
  // 0 cents are assignable by users.
  jlimit(tune,1,16);
  microdivisions=tune;  // tuning (1-16) = divisions per semitone.
  microincrement=1.0/tune; // size of microdivision as fraction of 1
  microchancount=(int)(16.0/((float)microdivisions)); // num user addressable microchans
  microchanblock=microchancount*microdivisions; // total num chans claimed
  //  printf("Tuning=%d, size=%f, chans=%d, claim=%d\n", microdivisions,
	 //	 microincrement, microchancount, microchanblock);
  if (send)
    sendTuning();
}

bool MidiOutPort::isTuning(int t) {
  // return true if current tuning
  jlimit(t,1,16);
  return (microdivisions==t);
}

int MidiOutPort::getTuningDivisions(int t) {
  jlimit(t,1,16);
  return t;
}

int MidiOutPort::getTuningChannels(int t) {
  // return number of addressable channels
  //return microchancount;
  jlimit(t,1,16);
  return (int)(16.0/((float)t));
}

int MidiOutPort::getTuningChannelsClaimed(int t) {
  // return total number of physical channels claimed by tuning
  jlimit(t,1,16);
  return getTuningChannels(t) * getTuningDivisions(t);
}

String MidiOutPort::getTuningName (int t) {
  // jlimit(tune,1,16);
  return tuningnames[t-1];
}

bool MidiOutPort::avoidDrumTrack() {
  return avoiddrumtrack;
}

void MidiOutPort::setAvoidDrumTrack(bool b) {
  avoiddrumtrack=b;
}

int MidiOutPort::getPitchBendWidth() {
  return pitchbendwidth;
}

void MidiOutPort::setPitchBendWidth(int b) {
  if (b<1) b=1;
  pitchbendwidth=b;
}

void MidiOutPort::sendTuning() {
 if ( ! isOpen() )
    return;
 //  printf("Sending tuning %d:\n", getTuning());
  int tunerow=getTuning()-1, channel, bendval;
  for (channel=0;channel<16; channel++) {
    bendval=(int)round(Toolbox::rescale( channeltunings[tunerow] [channel], 
					 -pitchbendwidth, 
					 pitchbendwidth,
					 0,
					 16383));
    //    printf("chan %d: %f, %d\n", channel,channeltunings[tunerow] [channel], bendval);
    // IS THIS THREAD SAFE?
    device->sendMessageNow( MidiMessage::pitchWheel(channel+1,bendval));    
  }
}

int MidiOutPort::getInstrument(int chan) {
  return programchanges[chan];
}

void MidiOutPort::setInstrument(int chan, int pc, bool send) {
  programchanges[chan]=pc;
}

void MidiOutPort::resetInstruments() {
  for (int c=0; c<16; c++)
    programchanges[c]=0;
}

bool MidiOutPort::isInstrumentChannel(int chan) {
  // true if physical chan accepts instruments (ie is not a channel
  // claimed by microtuning)
  return (0.0 == channeltunings[getTuning()-1][chan]);
}

void MidiOutPort::sendInstruments() {
 if ( ! isOpen() )
    return;
 // IS THIS THREAD SAFE?
  for (int c=0; c<16; c++)
    device->sendMessageNow( MidiMessage::programChange(c+1,programchanges[c]));
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/// Instrument Dialog
//

class GMInstrumentView;

class GMAssignmentList : public ListBox,
			 public ListBoxModel
{
public:
  MidiOutPort *port;
  int instruments[16];
  bool changed;

  GMAssignmentList(MidiOutPort *p) 
    : ListBox( T("Assignment List"), 0),
      port (0),
      changed(false)
  {
    port=p;
    setModel(this);
    for (int c=0;c<16;c++)
      instruments[c]=port->programchanges[c];
  }

  ~GMAssignmentList() {}

  bool isChanged() {return changed;}

  bool setChanged(bool b) {changed=b;}

  void setInstrument(int chan, int inst) 
  {
    // chan is a physcial channel 0-15
    //    printf("assignment: chan=%d, inst=%d\n", chan, inst);
    instruments[chan]=inst;
    chan++;
    // now set all the microtuned channels to the same instrument!
    while ( (chan<16) && !port->isInstrumentChannel(chan) ) {
      instruments[chan]=inst;
      //      printf("assignment: chan=%d, inst=%d\n", chan, inst);
      chan++;
    }
    //    for (chan=0;chan<16;chan++) printf(" %d:%d", chan, instruments[chan]);
    //    printf("\n");
  }

  int rowToChannel(int r) {
    // return physical channel number of row
    int t=port->getTuning();
    if ( r < port->getTuningChannels(t) )
      return r * port->getTuningDivisions(t);
    else
      return port->getTuningChannelsClaimed(t) +
	(r - port->getTuningChannels(t));
  }

  int getNumRows() {
    int num=0;
    // any channel with a zero tuning value is an assignable channel
    for (int c=0; c<16; c++)
      if ( port->isInstrumentChannel(c) )
	num++;
    return num;
  }
  
  void paintListBoxItem (int rowNumber, Graphics& g, int width, int height,
			 bool rowIsSelected)
  {
    if (rowIsSelected)
      g.fillAll( Colours::lightblue ); //Colours::lightblue  Colour(0x1000202)
    g.setColour (Colours::black);
    g.setFont (height * 0.7f);
    
    int tune=port->getTuning(), chan;
    String chantext, tunetext, insttext;
    // set chantext to microchannel number or to physcial channel number
    // if channel is above them
    if ( rowNumber < port->getTuningChannels(tune) ) {
      chantext=String(rowNumber);
      tunetext=port->getTuningName(tune);
      // actual channel number
      chan=rowNumber*port->getTuningDivisions(tune);
    }
    else { 
      // row is above microchannels, show its physical channel number
      // and semitonal tuning. physical channels start after the last
      // micochannel used.
      chan=port->getTuningChannelsClaimed(tune) +
	(rowNumber - port->getTuningChannels(tune));
      chantext=String(chan);
      tunetext=port->getTuningName(1);
    }    
    insttext=MidiMessage::getGMInstrumentName(instruments[chan]);
    // these positions need to be kept in same position as the labels
    // in component view

    //    printf("drawing row %d, inst=%s\n", rowNumber, insttext.toUTF8() );

    g.drawText (chantext, 5, 0, 56, height, Justification::centred,true);
    g.drawText (tunetext, 70-5, 0, 80, height, Justification::centredLeft,true);
    g.drawText (insttext, 156, 0, width-156, height, 
		Justification::centredLeft,true);
  }

  void revertInstruments() {
    for (int c=0;c<16;c++)
      instruments[c]=port->programchanges[c];
  }
  
  void saveInstruments() {
    for (int c=0;c<16;c++)
      port->programchanges[c]=instruments[c];
  }
};

class GMInstrumentList : public ListBox, 
			 public ListBoxModel
{
public:
  GMAssignmentList *assignments;

  GMInstrumentList(GMAssignmentList *list)
    : ListBox( T("GM Instrument List"), 0),
    assignments (0)
  {
    assignments=list;
    setModel(this);
  }

  ~GMInstrumentList() {} 

  int getNumRows() {return 128;}

  void paintListBoxItem (int rowNumber, Graphics& g, int width, int height,
			 bool rowIsSelected)
  {
    if (rowIsSelected)
      g.fillAll ( Colours::lightblue ); //  Colours::lightblue Colour(0x1000202)
    g.setColour (Colours::black);
    g.setFont (height * 0.7f);
    g.drawText (MidiMessage::getGMInstrumentName(rowNumber) ,
		5, 0, width, height,
		Justification::centredLeft, true);
  }

  //void listBoxItemDoubleClicked(int row, const MouseEvent &e);

  void listBoxItemClicked(int row, const MouseEvent &e) ;

};

//
// Instrument Dialog View
//

class InstrumentView : public Component, public ButtonListener
{
public:
  MidiOutPort *port;
  Label *label1, *label2, *label3, *label4;
  GMAssignmentList *assignments;
  GMInstrumentList *instruments;
  TextButton *button1, *button2;

  InstrumentView(MidiOutPort *p)
  {
    port=p;
    addAndMakeVisible(label1=new Label(String::empty, T("Channel")) );
    addAndMakeVisible(label2=new Label(String::empty, T("Tuning")) );
    addAndMakeVisible(label3=new Label(String::empty, T("Instrument")) );
    addAndMakeVisible(label4=new Label(String::empty, T("GM Instruments")) );
    addAndMakeVisible(assignments=new GMAssignmentList(p));
    addAndMakeVisible(instruments=new GMInstrumentList(assignments));
    addAndMakeVisible(button1=new TextButton(T("Revert")) );
    button1->addButtonListener(this);
    // revert button initially disabled
    button1->setEnabled(false);
    addAndMakeVisible(button2=new TextButton(T("Send")) );
    button2->addButtonListener(this);
    setSize(8 + 310 + 32 + 170 + 8, 456);
    setVisible(true);
  }

  ~InstrumentView() 
  {
    port=0;
    deleteAndZero(label1);
    deleteAndZero(label2);
    deleteAndZero(label3);
    deleteAndZero(label4);
    deleteAndZero(instruments);
    deleteAndZero(assignments);
    deleteAndZero(button1);
    deleteAndZero(button2);
  }

  void resized() 
  {
    int asslistwidth=310;
    int inslistwidth=170;
    // 
    label1->setBounds(8, 8, 56, 24); // Channel
    label2->setBounds(70, 8, 72, 24); // Tuning
    label3->setBounds(160, 8, 78, 24); // Instrument
    label4->setBounds((getWidth()-inslistwidth-8), 8, inslistwidth, 24);
    // list boxes
    assignments->setBounds(8, 32, asslistwidth, assignments->getRowHeight()*16);
    instruments->setBounds((getWidth()-inslistwidth-8),
			   32,
			   inslistwidth,
			   instruments->getRowHeight()*16);
    int mid=getWidth()/2;
    button1->setSize(60,24);
    button1->setTopLeftPosition(mid - button1->getWidth() - 16,
				assignments->getBottom() + 24);
    button2->setSize(60,24);
    button2->setTopLeftPosition(mid+16, button1->getY());
  }

  void buttonClicked (Button *button) ;

};

// these are the mouse down functions

void GMInstrumentList::listBoxItemClicked(int row, const MouseEvent &e) 
{
  // row == GM instrument number
  int inst=row;
  int arow=assignments->getSelectedRow(); // selected row in assignments list
  if (arow<0) return;
  int chan=assignments->rowToChannel(arow);
  // printf("assigning row=%d (physical channel %d) to %d\n", arow, chan, inst);
  assignments->setInstrument(chan,inst);
  assignments->repaintRow(arow);
  // Mark assignment list as changed and enable Revert button
  assignments->setChanged(true);
  ((InstrumentView *)getParentComponent())->button1->setEnabled(true);
}

void InstrumentView::buttonClicked (Button *button) 
{
  if ( button->getName() == T("Send") ) {
    //printf("SENDING!\n");
    // copy/send program changes, clear changed flag, deselect all
    // rows in list boxes and disable Revert button
    assignments->saveInstruments();
    port->sendInstruments();
    assignments->setChanged(false);
    assignments->deselectAllRows();
    instruments->deselectAllRows();
    button1->setEnabled(false);
  }
  else if ( button->getName() == T("Revert") ) {
    // restore Midi Port's program changes, clear changed flag,
    // deselect all rows in list boxes and disable Revert button
    assignments->revertInstruments();
    assignments->setChanged(false);
    assignments->deselectAllRows();
    //assignments->updateContent();
    for (int r=0;r<assignments->getNumRows(); r++)
      assignments->repaintRow(r);
    instruments->deselectAllRows();
    button1->setEnabled(false);
  }
}

void MidiOutPort::showInstrumentsWindow () {
  DialogWindow::showModalDialog (T("Instruments"),
				 new InstrumentView(this),
				 0,
				 Colour(0xffe5e5e5),
				 true);
}

