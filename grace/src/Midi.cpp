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
#include "Editor.h"

#include <iostream>;


//
//  Nodes
//

MidiNode::MidiNode(int typ, double wait, float *vals, int num_vals)
  : type (0), time (0.0), message (NULL), midiOutPort (NULL)
{ 
  type=typ;
  time=wait;
  for (int i=0;i<num_vals;i++)
    values.add(vals[i]);

}

MidiNode::MidiNode(int typ, double wait, float chan, float data1) 
  : type (0), time (0.0), message (NULL), midiOutPort (NULL)
{
  type=typ;
  time=wait;
  values.add(chan);
  values.add(data1);
}

MidiNode::MidiNode(int typ, double wait, float chan, float data1,
		   float data2) 
  : type (0), time (0.0), message (NULL), midiOutPort (NULL)
{
  type=typ;
  time=wait;
  values.add(chan);
  values.add(data1);
  values.add(data2);
}

MidiNode::MidiNode(MidiMessage *msg)
  : type (0), time (0.0), message (NULL), midiOutPort (NULL)
{
  type=MM_MESSAGE;
  time=msg->getTimeStamp();
  message=msg;
}

MidiNode::~MidiNode() { 
  values.clear();
}


void MidiNode::process()
{
  switch (type)
    {
      
    case MM_ON:
      if ( values[DATA2] > 0.0 )
	{
	  // handle velocity ranges 0.0-1.0 or 0.0-127.0
	  float vel=(values[DATA2]>1.0) ? (values[DATA2]/127.0f) : values[DATA2] ;
	  MidiMessage msg=MidiMessage::noteOn((int)values[DATA0]+1, 
					      (int)values[DATA1], 
					      vel);
	  msg.setTimeStamp(time);
	  midiOutPort->sendOut(msg);
	}
      else 
	{
	  MidiMessage msg=MidiMessage::noteOff( (int)values[DATA0]+1,
						(int)values[DATA1]);
	  msg.setTimeStamp(time);
	  midiOutPort->sendOut(msg);
	}
      break;
    case MM_OFF:
      {
	MidiMessage msg=MidiMessage::noteOff( (int)values[DATA0]+1,
					      (int)values[DATA1]);
	msg.setTimeStamp(time);
	midiOutPort->sendOut(msg);
      }
      break;
      
    case MM_PROG :
      {
	MidiMessage msg=MidiMessage::programChange( (int)values[DATA0]+1,
						    (int)values[DATA1]);
	msg.setTimeStamp(time);
	midiOutPort->sendOut(msg);
      }
      break;
      
    case MM_CTRL :
      {
	MidiMessage msg=MidiMessage::controllerEvent((int)values[DATA0]+1,
						     (int)values[DATA1],
						     (int)values[DATA2]);
	msg.setTimeStamp(time);
	midiOutPort->sendOut(msg);
      }
      break;
      
    case MM_BEND :
      {
	MidiMessage msg=MidiMessage::pitchWheel((int)values[DATA0]+1,
						(int)values[DATA1]) ;
	msg.setTimeStamp(time);
	midiOutPort->sendOut(msg);
      }
      break;
      
    case MM_TOUCH :
      {
	MidiMessage msg=MidiMessage::aftertouchChange((int)values[DATA0]+1,
						      (int)values[DATA1],
						      (int)values[DATA2] );
	msg.setTimeStamp(time);
	midiOutPort->sendOut(msg);
      }
      break;
      
    case MM_PRESS :
      {
	MidiMessage msg=
	  MidiMessage::channelPressureChange((int)values[DATA0]+1,
					     (int)values[DATA1]);
	msg.setTimeStamp(time);
	midiOutPort->sendOut(msg);
      }
      break;
      
    case MM_MESSAGE :
      {
	MidiMessage msg=*message;
	msg.setTimeStamp(time);
	midiOutPort->sendOut(msg);
      }      
      break;

    default:
      break;
    }
}

//
// Queue
//

void MidiOutPort::sendOut(MidiMessage& msg)
{
  // WARNING: SHOULD THIS CHECK DEVICE?
  device->sendMessageNow(msg);
  if ( isCaptureMode(CaptureModeMidiOut) )
    {

      // if this is the first recorded note cache its time offset so
      // we can subtract this value from the subsequence messages (we
      // want the capture sequence timeline to be in zero-based
      // seconds.)

      if (recordTimeOffset<0)
	{
	  recordTimeOffset=msg.getTimeStamp();
	  std::cout << "Record time offset=" << recordTimeOffset << "\n";
	}
      /** WARNING: TIMESTAMPS ARE MILLISECONDS **/
      /* captureSequence.addEvent( MidiMessage(msg),
				-recordTimeOffset 
				); */
      // convert millisecond timestamps from output queue to seconds
      // before adding messages to the capture sequence

      double sec=(msg.getTimeStamp()-recordTimeOffset)/1000.0;
      captureSequence.addEvent( MidiMessage(msg,sec) );
    }
}

MidiOutPort::MidiOutPort(ConsoleWindow *win)
  : Thread(T("Midi Out Port")),
    device(0),
    devid (-1),
    microdivisions (1),  // micro initialized for semitone
    microincrement (1.0),
    microchancount (16),
    microchanblock (16),
    avoiddrumtrack (true),
    pitchbendwidth (2),
    recordTimeOffset (-1.0),
    capturemode(CaptureModeOff)
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
  captureSequence.clear();
}

MidiOutPort::~MidiOutPort()
{
  if ( device != NULL ) delete device;
  outputNodes.clear();
  captureSequence.clear();
  tracks.clear();
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

///
/// Sequence capturing
///

int MidiOutPort::getCaptureMode()
{
  return capturemode;
}

void MidiOutPort::setCaptureMode(int mode)
{
  switch (mode)
    {
    case CaptureModeMidiOut :
      recordTimeOffset=-1;
      capturemode=mode;
      break;
    case CaptureModeMidiIn :
      capturemode=mode;
      break;
    case CaptureModeScore :
      capturemode=mode;
      break;
    default:
      capturemode=CaptureModeOff;
      break;
    }
}

bool MidiOutPort::isCaptureMode(int mode)
{
  return (capturemode==mode);
}

bool MidiOutPort::isSequenceEmpty()
{
  return (captureSequence.getNumEvents()==0);
}

bool MidiOutPort::isSequenceData()
{
  return (captureSequence.getNumEvents()>0);
}

void MidiOutPort::resetRecordingStart()
{
  recordTimeOffset=-1;
}

void MidiOutPort::clearSequence()
{
  captureSequence.clear();
  recordTimeOffset=-1;
}

void MidiOutPort::copySequenceToTrack(int index)
{
  // add a new track if index is -1 else replace track at index
  if (isSequenceData())
    {
      captureSequence.updateMatchedPairs();
      String name;
      if (index>=0 && index<tracks.size())
	{
	  name=getTrackName(index);
	  tracks.set(index, new MidiTrack( name, captureSequence));
	}
      else
	{
	  name=T("Untitled Track ") + String(tracks.size()+1);
	  tracks.add(new MidiTrack( name, captureSequence));
	}
    }
}

void MidiOutPort::playSequence()
{
  captureSequence.updateMatchedPairs();
  for (int i=0; i< captureSequence.getNumEvents(); i++)
    {
      MidiMessageSequence::MidiEventHolder* h =
	captureSequence.getEventPointer(i);
      if (h->message.isNoteOn())
	{
	  if (h->noteOffObject != NULL)
	    {
	      sendMessage(new MidiMessage(h->message));
	      sendMessage(new MidiMessage(h->noteOffObject->message));
	    }
	}
      else
	sendMessage(new MidiMessage(h->message));
    }
}

void MidiOutPort::plotSequence()
{
  captureSequence.updateMatchedPairs();
}

void MidiOutPort::printSequence()
{
  captureSequence.updateMatchedPairs();
  String text=T("Seq");
  int size=captureSequence.getNumEvents();
  text << T(": ") << String(size) << T(" event");
  if (size!=1)
    text << T("s");
  text << T(", ") << String(captureSequence.getEndTime())
       << T(" seconds.\n");
  console->printMessage(text);
}

///
/// tracks
///

int MidiOutPort::getNumTracks()
{
  return tracks.size();
}

String MidiOutPort::getTrackName(int index)
{
  return tracks.getUnchecked(index)->name;
}

void MidiOutPort::setTrackName(int index, String nam)
{
  tracks.getUnchecked(index)->name=nam;
}

void MidiOutPort::renameTrack(int index)
{
  if ((index>=0) && (index<tracks.size()))
    {
    }
}

void MidiOutPort::deleteTrack(int index)
{
  if ((index>=0) && (index<tracks.size()))
    {
      tracks.remove(index);
    }
}

void MidiOutPort::copyTrackToSequence(int index, bool add)
{
  if ((index>=0) && (index<tracks.size()))
    {
      if (!add) 
	captureSequence.clear();
      bool update=(captureSequence.getNumEvents()>0);
      captureSequence.
	addSequence( *(tracks.getUnchecked(index)->sequence),
		     0.0,
		     0.0,
		     tracks.getUnchecked(index)->sequence->getEndTime()+1
		     );
      // delete all events that are not Channel messages...
      for (int i=captureSequence.getNumEvents()-1; i>=0; i--)
	if (captureSequence.getEventPointer(i)->message.getChannel()==0)
	  captureSequence.deleteEvent(i, false);
      if (update)
	captureSequence.updateMatchedPairs();
    }
}

void MidiOutPort::importTracks()
{
  FileChooser chooser (T("Import Midi File"),
		       File::getSpecialLocation (File::userHomeDirectory),
		       "*.mid");
  if (!chooser.browseForFileToOpen())
    return;
  File import=chooser.getResult();
  String name=import.getFileNameWithoutExtension();
  FileInputStream* input=import.createInputStream();
  MidiFile midifile;
  midifile.readFrom(*input);
  int numtracks=midifile.getNumTracks();
  if (numtracks<1) 
    return;

  int format=midifile.getTimeFormat();
  double smptetps=0.0; // smpte ticks per second
  // juce time format is postive for beats and negative for SMTPE
  if (format>0)
    {
      midifile.convertTimestampTicksToSeconds();    
    }
  else
    {
      // juce smpte frames per second is negative upper byte
      int fps=0xFF-((format & 0xFF00) >> 8)+1;
      int tpf=format & 0xFF;
      smptetps=fps*tpf;
    }
  // start importing at track 1 in level 1 file
  int track=((numtracks==1) ? 0 : 1);
  int count=1;
  while (track<numtracks)
    {
      const MidiMessageSequence* seq=midifile.getTrack(track);
      // convert SMPTE ticks to seconds. The juce function
      // convertTimestampTicksToSeconds doesnt seem to work for SMPTE
      // ticks.
      if (format<0)
	{
	  for (int i=0; i<seq->getNumEvents(); i++)
	    {
	      MidiMessageSequence::MidiEventHolder* h=
		seq->getEventPointer(i);
	      double t=h->message.getTimeStamp();
	      h->message.setTimeStamp(t/smptetps);
	    }
	}
      tracks.add(new MidiTrack( (name + T(" ") + String(count)), *seq));
      track++;
      count++;
    }
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
  jlimit( (float)0.0, (float)15.0, channel);
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

  if (isCaptureMode(CaptureModeScore))
    {
    }
  // dont do anything if there is no open output port!
  else if ( device != NULL )
    {
      addNode( new MidiNode(MidiNode::MM_ON, wait, channel, keynum, amplitude) );
      addNode( new MidiNode(MidiNode::MM_OFF, wait+duration, channel, keynum) );
    }
}

void MidiOutPort::sendData(int type, double wait, float chan, float data1, float data2)
{
  if (isCaptureMode(CaptureModeScore))
    {
    } 
  else if ( device != NULL )
    {
      addNode( new MidiNode(type, wait, chan, data1, data2) );
    }
}

void MidiOutPort::sendMessage(MidiMessage *message)
{
  if (isCaptureMode(CaptureModeScore))
    {
    } 
  else if ( device != NULL )
    {
      addNode( new MidiNode(message) );
    }
}

/*
void MidiOutPort::sendOn(double wait, float key, float vel, float chan) {
  // dont do anything if there is no open output port!
  if ( device == NULL ) return;
  addNode( new MidiNode(MidiNode::MM_ON, wait, chan, key, vel) );
}

void MidiOutPort::sendOff(double wait, float key, float vel, float chan) {
  // dont do anything if there is no open output port!
  if ( device == NULL ) return;
  addNode( new MidiNode(MidiNode::MM_OFF, wait, chan, key) );
}

void MidiOutPort::sendProg(double wait, float prog, float chan) {
  // dont do anything if there is no open output port!
  if ( device == NULL ) return;
  addNode( new MidiNode(MidiNode::MM_PROG, wait, chan, prog) );
}

void MidiOutPort::sendCtrl(double wait, float ctrl, float val, float chan) {
  // dont do anything if there is no open output port!
  if ( device == NULL ) return;
  addNode( new MidiNode(MidiNode::MM_CTRL, wait, chan, ctrl, val) );
}

void MidiOutPort::sendBend(double wait, float bend, float chan) {
  // dont do anything if there is no open output port!
  if ( device == NULL ) return;
  addNode( new MidiNode(MidiNode::MM_BEND, wait, chan, bend) );
}

*/

void MidiOutPort::testMidiOutput () {
  // Tobias Kunze's little testing algo from cm 1.4
  double time = 0;
  for (int x=0; x<12; x++) {
    // vals[0]=keynum, [1]=velocity, [2]=channel
    float key = x + (12 * (3 + Random::getSystemRandom().nextInt(5) )) ;
    float vel = 32.0 + Random::getSystemRandom().nextInt(64);
    // MILLI
    // float dur = ((( 2 + Random::getSystemRandom().nextInt(6)) ^ 2) * (60.0 / 1000.0));
    float dur = .1 + (Random::getSystemRandom().nextInt(5) * .1);
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
    runmode (STOPPED),
    trace (false),
    noteOn(true),
    noteOff(true),
    controlChange(true),
    programChange(true),
    pitchBend(true),
    aftertouch(true),
    channelPressure(true),
    activeSense(true),
    allChannels(true),
    singleChannel(0)
{
  console=win;
  receiveComponent = new MidiReceiveComponent();
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

void MidiInPort::startSchemeInput() {
  // SET UP THE SCHEME HOOK FOR CALLBACK BEFORE STARTING
  start(SCHEMEHOOK);
}

void MidiInPort::stopSchemeInput() {
  if ( !isActive(SCHEMEHOOK) ) {
    return;
  }
  stop();
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

  trace=t;
}

bool MidiInPort::isTracing() {
  return trace;
}

void MidiInPort::handleIncomingMidiMessage (MidiInput *dev, 
					    const MidiMessage &msg) {
  // JUCE: chan>0 means channel message, 0 means not a channel message 
  int chan=msg.getChannel();
  String info=String::empty;

  if ( msg.isActiveSense() && !activeSense )
      return;
  if ( allChannels || msg.isForChannel(singleChannel) ) {     
    if ( msg.isNoteOn() && !noteOn) 
      return;
    else if ( msg.isNoteOff() && !noteOff ) 
      return;
    else if ( msg.isController() && !controlChange )
      return;
    else if ( msg.isProgramChange() && !programChange )
      return;
    else if ( msg.isPitchWheel() && !pitchBend )
      return;
    else if ( msg.isAftertouch() && !aftertouch )
      return;
    else if ( msg.isChannelPressure() && !channelPressure )
      return;
  }
  
#ifdef SCHEME  
  // AT THIS POINT CALL RECORDING CODE OR SCHEMEHOOK COE
  if ( isActive(SCHEMEHOOK) ) {
    ((GraceApp *)GraceApp::getInstance())->schemeProcess->
      addNode((int)SchemeNode::INHOOK, 0.0, msg);
  }
#endif
  if ( isActive(RECORDING) ) {
    printf("Recording message!\n");
  }
  
  if (trace) {
    printMidiMessageTrace(msg);
  }
}

void MidiInPort::printMidiMessageTrace (const MidiMessage &msg) {
  int chan=msg.getChannel();
  String info;
  if ( allChannels || msg.isForChannel(singleChannel) ) {  
    if ( msg.isNoteOn() )
      info=T("on chan: ") + String(chan-1) + T(" key: ")
	+ String(msg.getNoteNumber()) + T(" vel: ")
	+ String(msg.getVelocity());
    else if ( msg.isNoteOff() ) 
      info=T("off chan: ") + String(chan-1) + T(" key: ")
	+ String(msg.getNoteNumber());
    else if ( msg.isController() )
      info=T("ctrl chan: ") + String(chan-1) + T(" ctrl: ") 
	+ MidiMessage::getControllerName(msg.getControllerNumber())
	+ T(" value: ") + String(msg.getControllerValue());  
    else if ( msg.isProgramChange() )
      info=T("prog chan: ") + String(chan-1) + T(" prog: ")
	+ MidiMessage::getGMInstrumentName(msg.getProgramChangeNumber());
    else if ( msg.isPitchWheel())
      info=T("bend chan: ") + String(chan-1) + T(" val: ")
	+ String(msg.getPitchWheelValue());
    else if ( msg.isAftertouch() )
      info=T("touch chan: ") + String(chan-1) + T(" val: ")
	+ String(msg.getAfterTouchValue());
    else if ( msg.isChannelPressure() )
      info=T("press chan: ") + String(chan-1) + T(" val: ")
	+ String(msg.getChannelPressureValue());
    else if ( msg.isActiveSense() )
      info=T("sense time: ") + String(msg.getTimeStamp(), 3);
    //String(msg.getTimeStamp(), 3) +  T(" ") +
    console->postConsoleTextMessage( info + T("\n"), ConsoleMessage::TEXT, true);
  }
}

void MidiInPort::handlePartialSysexMessage (MidiInput *dev,
					    const juce::uint8 *data, 
					    const int num, 
					    const double time) {
}

void MidiInPort::setTrace(bool n) {
  trace = n;
}

void MidiInPort::setActiveSense(bool n) {
  activeSense = n;
}

void MidiInPort::setNoteOn(bool n) {
  noteOn = n;
}
void MidiInPort::setNoteOff(bool n) {
  noteOff = n;
}

void MidiInPort::setControlChange(bool n) {
  controlChange = n;
}

void MidiInPort::setProgramChange(bool n) {
  programChange = n;
}

void MidiInPort::setPitchBend(bool n) {
  pitchBend = n;
}

void MidiInPort::setAftertouch(bool n) {
  aftertouch = n;
}

void MidiInPort::setChannelPressure(bool n) {
  channelPressure = n;
}

void MidiInPort::setSingleChannel(int n) {
  singleChannel = n;
  allChannels = false;
}

void MidiInPort::setAllChannels(bool n) {
  singleChannel = 0;
  allChannels = n;
}

void MidiInPort::showMidiInDialog() {
  if ( noteOn && noteOff && controlChange && programChange && pitchBend &&
      aftertouch && channelPressure && activeSense)
    receiveComponent->allMessages->setToggleState(true, true);
  else {
    receiveComponent->allMessages->setToggleState(false, false);
    receiveComponent->noteOn->setToggleState(noteOn, false);
    receiveComponent->noteOff->setToggleState(noteOff, false);
    receiveComponent->controlChange->setToggleState(controlChange, false);
    receiveComponent->programChange->setToggleState(programChange, false);
    receiveComponent->pitchBend->setToggleState(pitchBend, false);
    receiveComponent->aftertouch->setToggleState(aftertouch, false);
    receiveComponent->channelPressure->setToggleState(channelPressure, false);
    receiveComponent->activeSense->setToggleState(activeSense, false);
  }

  if (singleChannel) {
    receiveComponent->singleChannel->setToggleState(true, true);
    receiveComponent->channelIncrementor->setValue((double)singleChannel);
  } else
    receiveComponent->allChannels->setToggleState(true, true);
  
  DialogWindow::showModalDialog(T("Midi Receive Settings"), 
				receiveComponent,
				console, 
				Colour(0xffe5e5e5),
				true,
				false,
				false);
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
  jlimit(1,16,tune);
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
  jlimit(1,16,t);
  return (microdivisions==t);
}

int MidiOutPort::getTuningDivisions(int t) {
  jlimit(1,16,t);
  return t;
}

int MidiOutPort::getTuningChannels(int t) {
  // return number of addressable channels
  //return microchancount;
  jlimit(1,16,t);
  return (int)(16.0/((float)t));
}

int MidiOutPort::getTuningChannelsClaimed(int t) {
  // return total number of physical channels claimed by tuning
  jlimit(1,16,t);
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

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
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

///
/// MidiFileInfoDialog
///

class MidiFileInfoComponent  : public Component,
                               public FilenameComponentListener,
                               public ComboBoxListener,
                               public SliderListener,
                               public ButtonListener
{
public:
  MidiFileInfoComponent (MidiFileInfo* info);
  ~MidiFileInfoComponent();
  void paint (Graphics& g);
  void resized();
  void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
  void sliderValueChanged (Slider* sliderThatWasMoved);
  void buttonClicked (Button* buttonThatWasClicked);
  bool parseTimeSig(String str, int& numer, int& denom);
  void filenameComponentChanged(FilenameComponent* f) ;
private:
  MidiFileInfo* midifileinfo;
  FilenameComponent* fileeditor;
  ComboBox* keysigmenu;
  Label* keysiglabel;
  Label* filelabel;
  Slider* temposlider;
  Label* timesiglabel;
  Label* tempolabel;
  TextButton* cancelbutton;
  TextButton* savebutton;
  TextEditor* timesigeditor;
  MidiFileInfoComponent (const MidiFileInfoComponent&);
  const MidiFileInfoComponent& operator= (const MidiFileInfoComponent&);
};

bool MidiFileInfoComponent::parseTimeSig (String str, int& n, int& d)
{
  int pos=str.indexOfChar('/');
  if (pos<0) return false;
  int a = str.substring(0,pos).getIntValue();
  if (a<1) return false;
  int b = str.substring(pos+1).getIntValue();
  if (b<1) return false;
  n=a;
  d=b;
  return true;
}

MidiFileInfoComponent::MidiFileInfoComponent (MidiFileInfo* info)
    : midifileinfo (0),
      fileeditor (0),
      keysigmenu (0),
      keysiglabel (0),
      filelabel (0),
      temposlider (0),
      timesiglabel (0),
      tempolabel (0),
      cancelbutton (0),
      savebutton (0),
      timesigeditor (0)
{
  midifileinfo=info;
  File file=midifileinfo->file;
  if (file==File::nonexistent)
    file=File::getSpecialLocation(File::userHomeDirectory).
      getChildFile(T("test.mid"));
  fileeditor = new FilenameComponent(String::empty, 
				     file,
				     true, 
				     false, 
				     true, 
				     T("*.mid"),
				     String::empty,
				     T("Midi File..."));
  fileeditor->setCurrentFile(file, false, false);
  fileeditor->addListener(this);
  
  //  StringArray files=port->orcfiles.getAllFilenames() ;
  //  orcfile->setRecentlyUsedFilenames(files);
  //  if ( files.size() > 0 )
  //    orcfile->setCurrentFile(port->orcfiles.getFile(0), false, false);
  addAndMakeVisible(fileeditor);

    addAndMakeVisible (keysigmenu = new ComboBox (T("keysigmenu")));
    keysigmenu->setEditableText (false);
    keysigmenu->setJustificationType (Justification::centredLeft);
    keysigmenu->setTextWhenNothingSelected (String::empty);
    keysigmenu->setTextWhenNoChoicesAvailable (T("(no choices)"));
    keysigmenu->addItem (T("7 Flats"), 1);
    keysigmenu->addItem (T("6 Flats"), 2);
    keysigmenu->addItem (T("5 Flats"), 3);
    keysigmenu->addItem (T("4 Flats"), 4);
    keysigmenu->addItem (T("3 Flats"), 5);
    keysigmenu->addItem (T("2 Flats"), 6);
    keysigmenu->addItem (T("1 Flat"), 7);
    keysigmenu->addItem (T("None"), 8);
    keysigmenu->addItem (T("1 Sharp"), 9);
    keysigmenu->addItem (T("2 Sharps"), 10);
    keysigmenu->addItem (T("3 Sharps"), 11);
    keysigmenu->addItem (T("4 Sharps"), 12);
    keysigmenu->addItem (T("5 Sharps"), 13);
    keysigmenu->addItem (T("6 Sharps"), 14);
    keysigmenu->addItem (T("7 Sharps"), 15);
    keysigmenu->setSelectedId(info->keysig);
    keysigmenu->addListener (this);

    addAndMakeVisible (keysiglabel = new Label (T("keysiglabel"),
                                                T("Key Signature:")));
    keysiglabel->setFont (Font (15.0000f, Font::plain));
    keysiglabel->setJustificationType (Justification::centredLeft);
    keysiglabel->setEditable (false, false, false);
    keysiglabel->setColour (TextEditor::textColourId, Colours::black);
    keysiglabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (filelabel = new Label (T("filelabel"),
                                              T("Midifile:")));
    filelabel->setFont (Font (15.0000f, Font::plain));
    filelabel->setJustificationType (Justification::centredLeft);
    filelabel->setEditable (false, false, false);
    filelabel->setColour (TextEditor::textColourId, Colours::black);
    filelabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (temposlider = new Slider (T("temposlider")));
    temposlider->setRange (40, 208, 2);
    temposlider->setSliderStyle (Slider::LinearHorizontal);
    temposlider->setTextBoxStyle (Slider::TextBoxLeft, false, 40, 24);
    temposlider->setValue(info->tempo);
    temposlider->addListener (this);

    addAndMakeVisible (timesiglabel = new Label (T("timesiglabel"),
                                                 T("Time Signature:")));
    timesiglabel->setFont (Font (15.0000f, Font::plain));
    timesiglabel->setJustificationType (Justification::centredLeft);
    timesiglabel->setEditable (false, false, false);
    timesiglabel->setColour (TextEditor::textColourId, Colours::black);
    timesiglabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (tempolabel = new Label (T("tempolabel"),
                                               T("Tempo:")));
    tempolabel->setFont (Font (15.0000f, Font::plain));
    tempolabel->setJustificationType (Justification::centredLeft);
    tempolabel->setEditable (false, false, false);
    tempolabel->setColour (TextEditor::textColourId, Colours::black);
    tempolabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (cancelbutton = new TextButton (T("cancelbutton")));
    cancelbutton->setButtonText (T("Cancel"));
    cancelbutton->addButtonListener (this);

    addAndMakeVisible (savebutton = new TextButton (T("savebutton")));
    savebutton->setButtonText (T("Save"));
    savebutton->addButtonListener (this);

    addAndMakeVisible (timesigeditor = new TextEditor (T("timesigeditor")));
    timesigeditor->setMultiLine (false);
    timesigeditor->setReturnKeyStartsNewLine (false);
    timesigeditor->setReadOnly (false);
    timesigeditor->setScrollbarsShown (true);
    timesigeditor->setCaretVisible (true);
    timesigeditor->setPopupMenuEnabled (true);
    String text=String(info->tsig1) + T("/") + String(info->tsig2);
    timesigeditor->setText (text);

    setSize (600, 200);
}

MidiFileInfoComponent::~MidiFileInfoComponent()
{
    deleteAndZero (fileeditor);
    deleteAndZero (keysigmenu);
    deleteAndZero (keysiglabel);
    deleteAndZero (filelabel);
    deleteAndZero (temposlider);
    deleteAndZero (timesiglabel);
    deleteAndZero (tempolabel);
    deleteAndZero (cancelbutton);
    deleteAndZero (savebutton);
    deleteAndZero (timesigeditor);
}

void MidiFileInfoComponent::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

void MidiFileInfoComponent::resized()
{
    fileeditor->setBounds (188, 24, 235, 24);
    keysigmenu->setBounds (496, 80, 80, 24);
    keysiglabel->setBounds (392, 80, 96, 24);
    filelabel->setBounds (128, 24, 56, 24);
    temposlider->setBounds (76, 80, 120, 24);
    timesiglabel->setBounds (217, 80, 104, 24);
    tempolabel->setBounds (12, 80, 56, 24);
    cancelbutton->setBounds (200, 144, 88, 24);
    savebutton->setBounds (320, 144, 88, 24);
    timesigeditor->setBounds (329, 80, 40, 24);
}

void MidiFileInfoComponent::filenameComponentChanged(FilenameComponent* f) 
{
}

void MidiFileInfoComponent::comboBoxChanged (ComboBox* combobox)
{
  if (combobox == keysigmenu)
    {
    }
}

void MidiFileInfoComponent::sliderValueChanged (Slider* slider)
{
  if (slider == temposlider)
    {
    }
}

void MidiFileInfoComponent::buttonClicked (Button* button)
{
  if (button == cancelbutton)
    {
      ((DialogWindow *)getTopLevelComponent())->exitModalState(false);
    }
  else if (button == savebutton)
    {
      if (fileeditor->getCurrentFile().existsAsFile())
	{
	  String msg= T("File ") + 
	    fileeditor->getCurrentFile().getFullPathName() + 
	    T(" exists.\nOverwrite?");
	  // WARNING: JUCE dialog puts the OK button on the left,
	  // which is backwards from Mac style...
	  if (! AlertWindow::showOkCancelBox(AlertWindow::QuestionIcon, 
					     T("Save"), msg,
					     T("   OK   "),
					     T("Cancel")))
	    return;
	}
      midifileinfo->file=fileeditor->getCurrentFile();
      midifileinfo->tempo=temposlider->getValue();
      midifileinfo->keysig=keysigmenu->getSelectedId();
      int a,b;
      if (parseTimeSig(timesigeditor->getText(), a, b))
	{
	  midifileinfo->tsig1=a;
	  midifileinfo->tsig2=b;
	}
      ((DialogWindow *)getTopLevelComponent())->exitModalState(true);
    }
}

void MidiOutPort::saveSequence(bool ask)
{
  if (isSequenceEmpty()) 
    return;
  if (ask || (sequenceFile.file==File::nonexistent))
    {
      MidiFileInfoComponent* comp=new MidiFileInfoComponent(&sequenceFile);
      String title=(ask) ? T("Save As") : T("Save");
      bool flag = DialogWindow::showModalDialog( title, comp, NULL,
						 Colour(0xffe5e5e5),
						 true, false, false);
      delete comp;
      if (!flag) return;
    }
  captureSequence.updateMatchedPairs();
  // BUG: if file already exits this seems to merge data into the old
  // file instead of overwriting it...
  FileOutputStream outputStream(sequenceFile.file);
  MidiFile* midifile = new MidiFile();
  //midifile->setTicksPerQuarterNote(960);
  midifile->setSmpteTimeFormat(25, 40); // equals 1 millisecond resolution
  MidiMessageSequence track0;
  track0.addEvent( sequenceFile.getTempoMessage(), 0);
  track0.addEvent( sequenceFile.getTimeSigMessage(), 0);
  track0.addEvent( sequenceFile.getKeySigMessage(), 0);
  midifile->addTrack(track0);
  midifile->addTrack(captureSequence);
  // Convert the file's data from seconds to milliseconds to match the
  // smpte time format
  const MidiMessageSequence* seq=midifile->getTrack(1);
  for (int i=0; i<seq->getNumEvents(); i++)
    {
      MidiMessageSequence::MidiEventHolder* h=seq->getEventPointer(i);
      h->message.setTimeStamp(h->message.getTimeStamp()*1000.0);
    }
  midifile->writeTo(outputStream );
  captureSequence.clear();
}

///
/// Export Dialog
///

class MidiFileExportComponent  : public Component,
                                 public ComboBoxListener,
                                 public LabelListener,
                                 public ButtonListener
{
public:
  static const int FormatSalData=1;
  static const int FormatSalSend=2;
  static const int FormatLispData=3;
  static const int FormatLispSend=4;
  
  MidiFileExportComponent ();
  ~MidiFileExportComponent();
  void paint (Graphics& g);
  void resized();
  void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
  void labelTextChanged (Label* labelThatHasChanged);
  void buttonClicked (Button* buttonThatWasClicked);
  
  String channelMessageExportText(MidiMessage msg, double offtime, 
				  int format, bool addtag) ;
  
  ComboBox* trackmenu;
  Label* frombuffer;
  Label* tobuffer;
  ToggleButton* notesbutton;
  ToggleButton* controlchangebutton;
  ToggleButton* programchangebutton;
  ToggleButton* pitchbendbutton;
  ToggleButton* aftertouchbutton;
  ToggleButton* pressurebutton;
  ComboBox* channelmenu;
  ToggleButton* consolebutton;
  ToggleButton* clipboardbutton;
    ToggleButton* neweditorbutton;
  ComboBox* dataformatmenu;
private:
  GroupComponent* messagegroup;
  GroupComponent* midifilegroup;
  Label* tracklabel;
  Label* fromlabel;
  Label* tolabel;
  Label* channellabel;
  GroupComponent* exporttogroup;
  TextButton* cancelbutton;
  TextButton* exportbutton;
  Label* dataformatlabel;
  MidiFileExportComponent (const MidiFileExportComponent&);
  const MidiFileExportComponent& operator= (const MidiFileExportComponent&);
};

MidiFileExportComponent::MidiFileExportComponent ()
    : messagegroup (0),
      midifilegroup (0),
      tracklabel (0),
      trackmenu (0),
      fromlabel (0),
      frombuffer (0),
      tolabel (0),
      tobuffer (0),
      notesbutton (0),
      controlchangebutton (0),
      programchangebutton (0),
      pitchbendbutton (0),
      aftertouchbutton (0),
      pressurebutton (0),
      channellabel (0),
      channelmenu (0),
      exporttogroup (0),
      consolebutton (0),
      clipboardbutton (0),
      neweditorbutton (0),
      cancelbutton (0),
      exportbutton (0),
      dataformatlabel (0),
      dataformatmenu (0)
{
  addAndMakeVisible (messagegroup =
		     new GroupComponent (T("messagegroup"),
					 T("Include")));
  
  addAndMakeVisible (midifilegroup =
		     new GroupComponent (T("midifilegroup"),
					 T("Export")));
  
  addAndMakeVisible (tracklabel = new Label (T("tracklabel"),
					     T("Track:")));
  tracklabel->setFont (Font (15.0000f, Font::plain));
  tracklabel->setJustificationType (Justification::centredLeft);
  tracklabel->setEditable (false, false, false);
  tracklabel->setColour (TextEditor::textColourId, Colours::black);
  tracklabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  tracklabel->setEnabled(false); // track not active

  addAndMakeVisible (trackmenu = new ComboBox (T("trackmenu")));
  trackmenu->setEditableText (false);
  trackmenu->setJustificationType (Justification::centredLeft);
  trackmenu->setTextWhenNothingSelected (String::empty);
  trackmenu->setTextWhenNoChoicesAvailable (T("(no choices)"));
  trackmenu->addItem (T("1"), 1);
  trackmenu->addItem (T("2"), 2);
  trackmenu->addListener (this);
  trackmenu->setSelectedId(1);
  trackmenu->setEnabled(false);
  
  addAndMakeVisible (fromlabel = new Label (T("fromlabel"),
					    T("From:")));
  fromlabel->setFont (Font (15.0000f, Font::plain));
  fromlabel->setJustificationType (Justification::centredLeft);
  fromlabel->setEditable (false, false, false);
  fromlabel->setColour (TextEditor::textColourId, Colours::black);
  fromlabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (frombuffer = new Label (T("frombuffer"),
					     String::empty));
  frombuffer->setFont (Font (15.0000f, Font::plain));
  frombuffer->setJustificationType (Justification::centredLeft);
  frombuffer->setEditable (true, true, false);
  frombuffer->setColour (Label::backgroundColourId, Colours::white);
  frombuffer->setColour (Label::outlineColourId, Colour (0xb2808080));
  frombuffer->setColour (TextEditor::textColourId, Colours::black);
  frombuffer->setColour (TextEditor::backgroundColourId, Colour (0x0));
  frombuffer->addListener (this);
  
  addAndMakeVisible (tolabel = new Label (T("tolabel"),
					  T("To:")));
  tolabel->setFont (Font (15.0000f, Font::plain));
  tolabel->setJustificationType (Justification::centredLeft);
  tolabel->setEditable (false, false, false);
  tolabel->setColour (TextEditor::textColourId, Colours::black);
  tolabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (tobuffer = new Label (T("tobuffer"),
					   String::empty));
  tobuffer->setFont (Font (15.0000f, Font::plain));
  tobuffer->setJustificationType (Justification::centredLeft);
  tobuffer->setEditable (true, true, false);
  tobuffer->setColour (Label::backgroundColourId, Colours::white);
  tobuffer->setColour (Label::outlineColourId, Colour (0xb2808080));
  tobuffer->setColour (TextEditor::textColourId, Colours::black);
  tobuffer->setColour (TextEditor::backgroundColourId, Colour (0x0));
  tobuffer->addListener (this);
  
  addAndMakeVisible (notesbutton = new ToggleButton (T("notesbutton")));
  notesbutton->setButtonText (T("Notes"));
  notesbutton->addButtonListener (this);
  notesbutton->setToggleState (true, false);
  
  addAndMakeVisible (controlchangebutton =
		     new ToggleButton (T("controlchangebutton")));
  controlchangebutton->setButtonText (T("Control Changes"));
  controlchangebutton->addButtonListener (this);
  
  addAndMakeVisible (programchangebutton =
		     new ToggleButton (T("programchangebutton")));
  programchangebutton->setButtonText (T("Program Changes"));
  programchangebutton->addButtonListener (this);
  
  addAndMakeVisible (pitchbendbutton = 
		     new ToggleButton (T("pitchbendbutton")));
  pitchbendbutton->setButtonText (T("Pitch Bends"));
  pitchbendbutton->addButtonListener (this);
  
  addAndMakeVisible (aftertouchbutton =
		     new ToggleButton (T("aftertouchbutton")));
  aftertouchbutton->setButtonText (T("Aftertouch"));
  aftertouchbutton->addButtonListener (this);
  
  addAndMakeVisible (pressurebutton =
		       new ToggleButton (T("pressurebutton")));
  pressurebutton->setButtonText (T("Channel Pressure"));
  pressurebutton->addButtonListener (this);
  
  addAndMakeVisible (channellabel = new Label (T("channellabel"),
					       T("Channel:")));
  channellabel->setFont (Font (15.0000f, Font::plain));
  channellabel->setJustificationType (Justification::centredLeft);
  channellabel->setEditable (false, false, false);
  channellabel->setColour (TextEditor::textColourId, Colours::black);
  channellabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (channelmenu = new ComboBox (T("channelmenu")));
  channelmenu->setEditableText (false);
  channelmenu->setJustificationType (Justification::centredLeft);
  channelmenu->setTextWhenNothingSelected (String::empty);
  channelmenu->setTextWhenNoChoicesAvailable (T("(no choices)"));
  channelmenu->addItem (T("All"), 17);
  channelmenu->addItem (T("1"), 1);
  channelmenu->addItem (T("2"), 2);
  channelmenu->addItem (T("3"), 3);
  channelmenu->addItem (T("4"), 4);
  channelmenu->addItem (T("5"), 5);
  channelmenu->addItem (T("6"), 6);
  channelmenu->addItem (T("7"), 7);
  channelmenu->addItem (T("8"), 8);
  channelmenu->addItem (T("9"), 9);
  channelmenu->addItem (T("10"), 10);
  channelmenu->addItem (T("11"), 11);
  channelmenu->addItem (T("12"), 12);
  channelmenu->addItem (T("13"), 13);
  channelmenu->addItem (T("14"), 14);
  channelmenu->addItem (T("15"), 15);
  channelmenu->addItem (T("16"), 16);
  channelmenu->setSelectedId(17);
  channelmenu->addListener (this);
  
  addAndMakeVisible (exporttogroup = 
		     new GroupComponent (T("exporttogroup"),
					 T("Export To")));
  
  addAndMakeVisible (consolebutton = 
		       new ToggleButton (T("consolebutton")));
  consolebutton->setButtonText (T("Console"));
  consolebutton->setRadioGroupId (1);
  consolebutton->addButtonListener (this);
  consolebutton->setToggleState (true, false);
  
  addAndMakeVisible (clipboardbutton = 
		     new ToggleButton (T("clipboardbutton")));
  clipboardbutton->setButtonText (T("Clipboard"));
  clipboardbutton->setRadioGroupId (1);
  clipboardbutton->addButtonListener (this);
  
  addAndMakeVisible (neweditorbutton =
		     new ToggleButton (T("neweditorbutton")));
  neweditorbutton->setButtonText (T("New Editor"));
  neweditorbutton->setRadioGroupId (1);
  neweditorbutton->addButtonListener (this);
  
  addAndMakeVisible (cancelbutton = new TextButton (T("cancelbutton")));
  cancelbutton->setButtonText (T("Cancel"));
  cancelbutton->addButtonListener (this);
  
  addAndMakeVisible (exportbutton = new TextButton (T("exportbutton")));
  exportbutton->setButtonText (T("Export"));
  exportbutton->addButtonListener (this);
  
  addAndMakeVisible (dataformatlabel = new Label (T("dataformatlabel"),
						  T("Data Format:")));
  dataformatlabel->setFont (Font (15.0000f, Font::plain));
  dataformatlabel->setJustificationType (Justification::centredLeft);
  dataformatlabel->setEditable (false, false, false);
  dataformatlabel->setColour (TextEditor::textColourId, Colours::black);
  dataformatlabel->setColour (TextEditor::backgroundColourId,
			      Colour (0x0));
  
  addAndMakeVisible (dataformatmenu = 
		     new ComboBox (T("dataformatmenu")));
  dataformatmenu->setEditableText (false);
  dataformatmenu->setJustificationType (Justification::centredLeft);
  dataformatmenu->setTextWhenNothingSelected (String::empty);
  dataformatmenu->setTextWhenNoChoicesAvailable (T("(no choices)"));
  dataformatmenu->addItem (T("SAL Data"), FormatSalData);
  dataformatmenu->addItem (T("Lisp Data"), FormatLispData);
  dataformatmenu->addItem (T("SAL Sends"), FormatSalSend);
  dataformatmenu->addItem (T("Lisp Sends"), FormatLispSend);
  dataformatmenu->setSelectedId(FormatSalData);
  dataformatmenu->addListener (this);
  setSize (320, 374);
}

MidiFileExportComponent::~MidiFileExportComponent()
{
    deleteAndZero (messagegroup);
    deleteAndZero (midifilegroup);
    deleteAndZero (tracklabel);
    deleteAndZero (trackmenu);
    deleteAndZero (fromlabel);
    deleteAndZero (frombuffer);
    deleteAndZero (tolabel);
    deleteAndZero (tobuffer);
    deleteAndZero (notesbutton);
    deleteAndZero (controlchangebutton);
    deleteAndZero (programchangebutton);
    deleteAndZero (pitchbendbutton);
    deleteAndZero (aftertouchbutton);
    deleteAndZero (pressurebutton);
    deleteAndZero (channellabel);
    deleteAndZero (channelmenu);
    deleteAndZero (exporttogroup);
    deleteAndZero (consolebutton);
    deleteAndZero (clipboardbutton);
    deleteAndZero (neweditorbutton);
    deleteAndZero (cancelbutton);
    deleteAndZero (exportbutton);
    deleteAndZero (dataformatlabel);
    deleteAndZero (dataformatmenu);
}

void MidiFileExportComponent::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

void MidiFileExportComponent::resized()
{
    messagegroup->setBounds (8, 104, 304, 128);
    midifilegroup->setBounds (8, 0, 304, 96);
    tracklabel->setBounds (16, 24, 48, 24);
    trackmenu->setBounds (72, 24, 50, 24);
    fromlabel->setBounds (16, 60, 47, 24);
    frombuffer->setBounds (72, 60, 50, 24);
    tolabel->setBounds (184, 60, 32, 24);
    tobuffer->setBounds (224, 60, 50, 24);
    notesbutton->setBounds (16, 128, 136, 24);
    controlchangebutton->setBounds (16, 160, 136, 24);
    programchangebutton->setBounds (16, 192, 136, 24);
    pitchbendbutton->setBounds (168, 128, 128, 24);
    aftertouchbutton->setBounds (168, 160, 128, 24);
    pressurebutton->setBounds (168, 192, 128, 24);
    channellabel->setBounds (152, 24, 64, 24);
    channelmenu->setBounds (224, 24, 50, 24);
    exporttogroup->setBounds (8, 240, 304, 88);
    consolebutton->setBounds (16, 260, 88, 24);
    clipboardbutton->setBounds (109, 260, 88, 24);
    neweditorbutton->setBounds (208, 260, 88, 24);
    cancelbutton->setBounds (40, 340, 112, 24);
    exportbutton->setBounds (176, 340, 104, 24);
    dataformatlabel->setBounds (40, 292, 88, 24);
    dataformatmenu->setBounds (136, 292, 136, 24);
}

void MidiFileExportComponent::comboBoxChanged (ComboBox* comboBox)
{
    if (comboBox == trackmenu)
    {
    }
    else if (comboBox == channelmenu)
    {
    }
    else if (comboBox == dataformatmenu)
    {
    }
}

void MidiFileExportComponent::labelTextChanged (Label* label)
{
    if (label == frombuffer)
    {
    }
    else if (label == tobuffer)
    {
    }
}

void MidiFileExportComponent::buttonClicked (Button* button)
{
    if (button == notesbutton)
    {
    }
    else if (button == controlchangebutton)
    {
    }
    else if (button == programchangebutton)
    {
    }
    else if (button == pitchbendbutton)
    {
    }
    else if (button == aftertouchbutton)
    {
    }
    else if (button == pressurebutton)
    {
    }
    else if (button == consolebutton)
    {
    }
    else if (button == clipboardbutton)
    {
    }
    else if (button == neweditorbutton)
    {
    }
    else if (button == cancelbutton)
    {
      ((DialogWindow *)getTopLevelComponent())->exitModalState(false);

    }
    else if (button == exportbutton)
    {
      ((DialogWindow *)getTopLevelComponent())->exitModalState(true);
    }
}

String MidiFileExportComponent::channelMessageExportText
(MidiMessage msg,  double offtime, int fmat, bool addtag)
{
  // MESSAGE TIMES ARE IN MILLISECONDS
  int chan=msg.getChannel()-1; 
  String time=String::formatted(T("%.03f"),
				((float)msg.getTimeStamp()));
  String text=String::empty;
  String prep=String::empty;
  String sepr = ((fmat==FormatSalSend) ? T(", ") : T(" "));
  bool note=false;
  if ( msg.isNoteOn() )
    {
      note=true;
      prep=T("mp:note");
      double dur=offtime-msg.getTimeStamp();
      text << time
	   << sepr << String::formatted(T("%.03f"), (float)dur)
	   << sepr << String(msg.getNoteNumber())
	   << sepr << String(msg.getVelocity())
	   << sepr << chan
	;
    }
  else if ( msg.isController() )
    {
      prep=T("mp:ctrl");
      text << time
	   << sepr << String(msg.getControllerNumber())
	   << sepr << String(msg.getControllerValue())
	   << sepr << chan;
    }
  else if ( msg.isProgramChange() )
    {
      prep=T("mp:ctrl");
      text << time
	   << sepr << String(msg.getProgramChangeNumber())
	   << sepr << chan;
    }
  else if ( msg.isPitchWheel())
    {
      prep=T("mp:pitch");
      text << time
	   << sepr << String(msg.getPitchWheelValue())
	   << sepr << chan;
    }
  else if ( msg.isAftertouch() )
    {
      prep=T("mp:after");
      text << time
	   << sepr << String(msg.getAfterTouchValue())
	   << sepr << chan;
    }
  else if ( msg.isChannelPressure() )
    {
      prep=T("mp:press");
      text << time
	   << sepr << String(msg.getChannelPressureValue())
	   << sepr << chan;
    }
  else return T("");

  switch (fmat)
    {
    case FormatSalData :
      text=T("{") + text + T("}");
      // tag non-note data with a comment showing its data type
      if (!note && addtag) text << T("\t;") << prep;
      break;
    case FormatLispData :
      text=T("(") + text + T(")");
      // tag non-note data with a comment showing its data type
      if (!note && addtag) text << T("\t;") << prep;
      break;
    case FormatSalSend :
      text=T("send ") + prep.quoted() + sepr + text;
      break;
    case FormatLispSend :
      text=String("(send ") + prep.quoted() + sepr + text + T(")");
      break;
    }
  return text;
}

void MidiOutPort::exportSequence()
{
  MidiFileExportComponent* dialog=new MidiFileExportComponent();
  String title=T("Export Sequence");
  bool flag = DialogWindow::showModalDialog(title, dialog, NULL,
					    Colour(0xffe5e5e5),
					    true, false, false);
  if (!flag)
    {
      delete dialog;
      return;
    }
  captureSequence.updateMatchedPairs();
  double start=dialog->frombuffer->getText().getDoubleValue();
  double endtime=dialog->tobuffer->getText().getDoubleValue();
  bool donote=dialog->notesbutton->getToggleState();
  bool doctrl=dialog->controlchangebutton->getToggleState();
  bool doprog=dialog->programchangebutton->getToggleState();
  bool dobend=dialog->pitchbendbutton->getToggleState();
  bool dotouch=dialog->aftertouchbutton->getToggleState();
  bool dopress=dialog->pressurebutton->getToggleState();
  int chans=dialog->channelmenu->getSelectedId();
  int format=dialog->dataformatmenu->getSelectedId();

  String text, indent, after;
  switch (format) 
    {
    case MidiFileExportComponent::FormatLispData :
      text=T("(define midi-export\n  '(\n");
      indent=T("    "); 
      after=T("  ))\n");
      break;
    case MidiFileExportComponent::FormatSalData :
      text=T("define variable midi-export = \n  {\n");
      indent=T("   "); 
      after=T("  }\n");
      break;
    case MidiFileExportComponent::FormatLispSend :
      text=T("(begin\n");
      indent=T("  ");
      after=T("  )\n");
      break;
    case MidiFileExportComponent::FormatSalSend :
      text=T("begin\n"); 
      indent=T("  "); 
      after=T("end\n");
      break;
    }

  for (int i=0; i< captureSequence.getNumEvents(); i++)
    {
      MidiMessageSequence::MidiEventHolder*
	ev=captureSequence.getEventPointer(i);
      // skip if less than start time
      if ((start>0) && (ev->message.getTimeStamp()<start))
	continue;
      // stop if greater than end time
      if ((endtime>0) && (ev->message.getTimeStamp()>endtime))
	break;
      // skip if not channel message or not selected channel
      if ((ev->message.getChannel() == 0) ||
	  ((chans<17) && (ev->message.getChannel() != chans)))
	continue;
      if (donote && ev->message.isNoteOn())
	{
	  double off;
	  if (ev->noteOffObject)
	    off=ev->noteOffObject->message.getTimeStamp();
	  else 
	    off=500.0; // missing note off???
	  text << indent 
	       << dialog->channelMessageExportText(ev->message, off, 
						   format, true)
	       << T("\n");
	}
      else if (doctrl && ev->message.isController())
	text << indent
	     << dialog->channelMessageExportText(ev->message, 0,
						 format, true)
	     << T("\n");
      else if (doprog && ev->message.isProgramChange())
	text << indent
	     << dialog->channelMessageExportText(ev->message, 0,
						 format, true)
	     << T("\n");
      else if (dobend && ev->message.isPitchWheel())
	text << indent
	     << dialog->channelMessageExportText(ev->message, 0,
						 format, true)
	     << T("\n");
      else if (dotouch && ev->message.isAftertouch())
	text << indent
	     << dialog->channelMessageExportText(ev->message, 0,
						 format, true)
	     << T("\n");
      else if (dopress && ev->message.isChannelPressure())
	text << indent
	     << dialog->channelMessageExportText(ev->message, 0,
						 format, true)
	     << T("\n");	  
    }
  text << after;
  //std::cout << text.toUTF8();

  if (dialog->consolebutton->getToggleState())
    {
    console->printMessage(text);
    }
  else if (dialog->clipboardbutton->getToggleState())
    {
      SystemClipboard::copyTextToClipboard(text);
    }
  else if (dialog->neweditorbutton->getToggleState() )
    {
      int synt;
      if ((format==MidiFileExportComponent::FormatSalData) ||
	  (format==MidiFileExportComponent::FormatSalSend))
	synt=syntaxSal;
      else
	synt=syntaxLisp;
      new EditorWindow(synt, TextBuffer::needsave, String::empty, T("Untitled"), text);
    }

  delete dialog;
}

