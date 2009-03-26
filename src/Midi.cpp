/*=======================================================================*
  Copyright (c) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify
  it under the terms of the Lisp Lesser Gnu Public License. The text
  of this agreement is available at http://www.cliki.net/LLGPL
 *=======================================================================*/

#include "Enumerations.h"
#include "CmSupport.h"
#include "Scheme.h"
#include "Console.h"
#include "Midi.h"
#ifdef GRACE
#include "Preferences.h"
#include "TextEditor.h"
#endif
#include <iostream>

juce_ImplementSingleton(MidiOutPort)

juce_ImplementSingleton(MidiInPort)


//
//  Nodes
//

MidiNode::MidiNode(int typ, double wait, double *vals, int num_vals)
  : type (0), time (0.0), message (NULL), midiOutPort (NULL)
{ 
  type=typ;
  time=wait;
  for (int i=0;i<num_vals;i++)
    values.add(vals[i]);
}

MidiNode::MidiNode(int typ, double wait, double chan, double data1) 
  : type (0), time (0.0), message (NULL), midiOutPort (NULL)
{
  type=typ;
  time=wait;
  values.add(chan);
  values.add(data1);
}

MidiNode::MidiNode(int typ, double wait, double chan, double data1,
		   double data2) 
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
	  float vel=(values[DATA2]>1.0) ? 
	    (values[DATA2]/127.0) : values[DATA2] ;
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
	//msg.setChannel(msg.getChannel()+1);
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
  // WARNING: this should only be called by process().  SHOULD THIS
  // CHECK DEVICE?
  device->sendMessageNow(msg);
  if ( isRecordMode(CaptureModes::RecordMidiOut) )
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
      // convert millisecond timestamps from output queue to seconds
      // before adding messages to the capture sequence
      double sec=(msg.getTimeStamp()-recordTimeOffset)/1000.0;
      captureSequence.addEvent( MidiMessage(msg,sec) );
    }
}

////////////////////////////////////////////////////////////////////
/// MIDI OUT PORT
///

MidiOutPort::MidiOutPort()
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
    recordmode(CaptureModes::Off),
    console (NULL)
{	
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
  String name=String::empty;
#ifdef GRACE
  Preferences* prefs=Preferences::getInstance();
  name=prefs->getStringProp(T("MidiOutDevice"));
#endif
  if (name != String::empty)
    open(name);
}


MidiOutPort::~MidiOutPort()
{
  if ( device != NULL ) delete device;
  outputNodes.clear();
  captureSequence.clear();
  tracks.clear();
}

bool MidiOutPort::open(String name) 
{
  StringArray devices = MidiOutput::getDevices ();
  int id=-1;
  for (int i=0;i<devices.size();i++)
    if (devices[i] == name) 
      {
	id=i;
	break;
      }
  if (id==-1)
    {
      Console::getInstance()->
	printWarning(T("Warning: Midi output device ") + 
		     name + T(" does not exist.\n"));
      return false;
    }
  else
    return open(id);
}

bool MidiOutPort::open(int id)
{
  // dont do anything if opening same port
  if (id == devid) 
    return true;

  // delete current port. IS THIS CORRECT?
  if (device != NULL)
    {
      delete device;
      devid=-1;
    }
  device = MidiOutput::openDevice(id);
  if (device==NULL)
    {
      String str= T(">>> Error: Failed to open midi output device ");
      str << String(id) << T(".\n");
      Console::getInstance()->printError(str);
      return false;
    }
  else
    {
      devid=id;
      // send current tuning automatically if its microtonal
      if (getTuning()>1)
	sendTuning();
#ifdef GRACE
      // update Preferences with current port's name;
      StringArray devices = MidiOutput::getDevices();
      Preferences* prefs=Preferences::getInstance();
      prefs->setStringProp(T("MidiOutDevice"), devices[id]);
#endif
      return true;
    }
}

bool MidiOutPort::isOpen(int id) {
  if ( device == NULL )
    return false;
  else if ( id == -1) // asking if ANY output device is open
    return true;
  else
    return (id == devid); // asking if specific dev is open
}

void MidiOutPort::close(int id)
{
  if (device!=NULL)
    {
      delete device;
      device=NULL;
      devid=-1;
    }
}

int MidiOutPort::performCommand(CommandID id, int data, String text)
{
  // lower eight bits of id encode command information
  CommandID cmd = CommandIDs::getCommand(id);
  int arg = CommandIDs::getCommandData(id);  
  int res=0;

  switch (cmd)
    {
    case CommandIDs::MidiOutOpen:
      open(arg);
      break;

    case CommandIDs::MidiOutTest:
      testOutput();
      break;

    case CommandIDs::MidiOutHush :
      Scheme::getInstance()->stop();
      clear();
      break;


    case CommandIDs::SchedulerScoreComplete :
      if (isSequenceData())
	{
	  saveSequence(false);
	  clearSequence();
	}
      break;

    case CommandIDs::MidiOutTuning :
      setTuning(data, true);
      break;

    case CommandIDs::MidiOutPitchBend :
      setPitchBendWidth(arg);
      break;

    case CommandIDs::MidiOutDrumTrack :
      setAvoidDrumTrack(! avoidDrumTrack());
      break;

    case CommandIDs::MidiOutInstruments :
      /***  showInstrumentsWindow(); ***/
      break;

    case CommandIDs::MidiSeqSetFile :
      setOutputFile(text);
      break;

    case CommandIDs::MidiSeqClear :
      clearSequence();
      break;
      
    case CommandIDs::MidiSeqResetRecordingStart :
      resetRecordingStart();
      break;
      
    case CommandIDs::MidiSeqRecordMidiOut :
      setRecordMode(arg);
      break;
      
    case CommandIDs::MidiSeqCopyToTrack :
      copySequenceToTrack(-1);
      break;
      
    case CommandIDs::MidiSeqReplaceTrack :
      copySequenceToTrack(arg);
      break;
      
    case CommandIDs::MidiSeqPlay :
      playSequence();
      break;
      
    case CommandIDs::MidiSeqPlot :
      plotSequence();
      break;
      
    case CommandIDs::MidiSeqPrintInfo :
      printSequence();
      break;
      
    case CommandIDs::MidiSeqRenameTrack :
      renameTrack( arg);
      break;
      
    case CommandIDs::MidiSeqDeleteTrack :
      deleteTrack( arg);
      break;
      
    case CommandIDs::MidiSeqRestoreTrack :
      restoreTrack( arg);
      break;

    case CommandIDs::MidiSeqMixTrack :
      mixTrack( arg);
      break;
      
    case CommandIDs::MidiSeqSave :
      saveSequence();
      break;                 
      
    case CommandIDs::MidiSeqSaveAs :
      saveSequence(true);
      break;                 
      
    case CommandIDs::MidiSeqImport :
      importTracks();
      break;                 

    default:
      break;
    }
  return res;
}

///
/// Sequence capturing
///

int MidiOutPort::getRecordMode()
{
  return recordmode;
}

void MidiOutPort::setRecordMode(int mode)
{
  switch (mode)
    {
    case CaptureModes::RecordMidiOut :
      recordTimeOffset=-1;
      recordmode=mode;
      break;
    case CaptureModes::RecordMidiIn :
      recordmode=mode;
      break;
    default:
      recordmode=CaptureModes::Off;
      break;
    }
}

bool MidiOutPort::isRecordMode(int mode)
{
  return (recordmode==mode);
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
  if (isSequenceEmpty() || (! isOpen()))
    return;
  captureSequence.updateMatchedPairs();
  for (int i=0; i< captureSequence.getNumEvents(); i++)
    {
      MidiMessageSequence::MidiEventHolder* h =
	captureSequence.getEventPointer(i);
      if (h->message.isNoteOn())
	{
	  if (h->noteOffObject != NULL)
	    {
	      sendMessage(new MidiMessage(h->message), false);
	      sendMessage(new MidiMessage(h->noteOffObject->message), false);
	    }
	}
      else
	sendMessage(new MidiMessage(h->message), false);
    }
}

void MidiOutPort::plotSequence()
{
  //captureSequence.updateMatchedPairs();
}

void MidiOutPort::printSequence()
{
  captureSequence.updateMatchedPairs();
  String text=T("Midi Seq: ");
  int size=captureSequence.getNumEvents();
  text << String(size) << T(" event");
  if (size!=1)
    text << T("s");
  text << T(", ") << String(captureSequence.getEndTime())
       << T(" seconds\n");
  /***  console->printMessage(text);
   ***/
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
      String str;
      /***      str=TextDialogComponent::ShowTextDialog(T("Rename Track"),
						     T("Track Name:"),
						     getTrackName(index),
						     T("Rename"));
      ***/
      if (str != String::empty)
	{
	  tracks.getUnchecked(index)->name=str;
	}
    }
}

void MidiOutPort::deleteTrack(int index)
{
  if ((index>=0) && (index<tracks.size()))
    {
      tracks.remove(index);
    }
}

void MidiOutPort::restoreTrack(int index)
{
  copyTrackToSequence( index, false, 0.0);
}

void MidiOutPort::mixTrack(int index)
{
  String abort=T("abort");
  String str;
  /*** str=TextDialogComponent::ShowTextDialog(T("Mix Track"),
						 T("Start Time:"),
						 T("0.0"),
						 T("Mix"),
						 abort);
  ***/
  if (str != abort)
    {
      double start=str.getDoubleValue();
      if (start<0.0)
	start=0.0;
      copyTrackToSequence( index, true, start);
    }
}

void MidiOutPort::copyTrackToSequence(int index, bool add, double shift)
{
  if ((index>=0) && (index<tracks.size()))
    {
      if (!add) 
	captureSequence.clear();
      bool update=(captureSequence.getNumEvents()>0);
      captureSequence.
	addSequence( *(tracks.getUnchecked(index)->sequence),
		     shift,
		     0.0,
		     tracks.getUnchecked(index)->sequence->getEndTime()+shift+1
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

void MidiOutPort::sendNote(double wait, double duration, double keynum, 
			   double amplitude, double channel, bool toseq) 
{
  //  std::cout << "channel=" << channel << "\n";

  jlimit( 0.0, 15.0, channel);

  //  std::cout << "after jlimit channel=" << channel << "\n";

  // only microtune if current tuning is not semitonal and user's
  // channel is a microtonal channel.
  if ( (getTuning() > 1) && (channel < microchanblock) ) 
    {
      // insure user's channel a valid microtonal channel, ie a channel
      // within the first zone of microtuned channels and then shift to
      // actual physical channel
      int chan=(((int)channel) % microchancount) * microdivisions;
      // calculate integer midi key quantize user's keynum to microtonal
      // resolution size. this may round up to the next keynum
      double foo=keynum;
      // quantize keynumber to tuning resolution. if it rounds up (or
      // down) to an integer keynum then we dont need to microtune
      keynum = cm_quantize( keynum, microincrement);

      ///keynum = floor((keynum/microincrement)+.5)*microincrement;

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
	channel=chan;
	keynum=key;
      }
    }
  
  if (toseq)
    {
      // JUCE channel message constructors are 1-based channels
      float amp=((amplitude>1.0) ? (amplitude/127) : amplitude);
      captureSequence.
	addEvent(MidiMessage::noteOn((int)channel+1, (int)keynum, amp),
		 wait);
      captureSequence.
	addEvent(MidiMessage::noteOff((int)channel+1, (int)keynum),
		 wait+duration);
      // don't call updatematchedpairs until the seq is used
    }
  // otherwise add it to the output queue, but dont do anything if
  // there is no open output port (is this right?)
  else if ( device != NULL )
    {
      addNode( new MidiNode(MidiNode::MM_ON, wait, channel, 
			    keynum, amplitude) );
      addNode( new MidiNode(MidiNode::MM_OFF, wait+duration, channel,
			    keynum) );
    }
}

void MidiOutPort::sendData(int type, double wait, double chan, 
			   double data1, double data2, bool toseq)
{
  if (toseq)
    {
      int ch=(int)chan;
      int d1=(int)data1;
      int d2=(int)data2;
      // JUCE channel message constructors are 1 based
      if (type==MidiNode::MM_OFF)
	captureSequence.addEvent(MidiMessage::noteOff(ch+1, d1),
				 wait);
      else if (type==MidiNode::MM_ON)
	captureSequence.
	  addEvent(MidiMessage::noteOn(ch+1, d1, (float)data2),
		   wait);
      else if (type==MidiNode::MM_TOUCH)
	captureSequence.
	  addEvent(MidiMessage::aftertouchChange(ch+1, d1, d2),
		   wait);
      else if (type==MidiNode::MM_CTRL)
	captureSequence.
	  addEvent(MidiMessage::controllerEvent(ch+1, d1, d2),
		   wait);
      else if (type==MidiNode::MM_PROG)
	captureSequence.
	  addEvent(MidiMessage::programChange(ch+1, d1),
		   wait);
      else if (type==MidiNode::MM_PRESS)
	captureSequence.
	  addEvent(MidiMessage::channelPressureChange(ch+1, d1), 
		   wait);
      else if (type==MidiNode::MM_BEND)
	captureSequence.addEvent(MidiMessage::pitchWheel(ch+1, d1),
				 wait);
    }
  else if ( device != NULL )
    {
      addNode( new MidiNode(type, wait, chan, data1, data2) );
    }
}

void MidiOutPort::sendMessage(MidiMessage *message, bool toseq)
{
  if (toseq)
    {
      captureSequence.addEvent(MidiMessage(*message));
      delete message; // hmm is this right?
    } 
  else if ( device != NULL )
    {
      addNode( new MidiNode(message) );
    }
}

/*
void MidiOutPort::sendOn(double wait, double key, double vel, double chan) {
  // dont do anything if there is no open output port!
  if ( device == NULL ) return;
  addNode( new MidiNode(MidiNode::MM_ON, wait, chan, key, vel) );
}

void MidiOutPort::sendOff(double wait, double key, double vel, double chan) {
  // dont do anything if there is no open output port!
  if ( device == NULL ) return;
  addNode( new MidiNode(MidiNode::MM_OFF, wait, chan, key) );
}

void MidiOutPort::sendProg(double wait, double prog, double chan) {
  // dont do anything if there is no open output port!
  if ( device == NULL ) return;
  addNode( new MidiNode(MidiNode::MM_PROG, wait, chan, prog) );
}

void MidiOutPort::sendCtrl(double wait, double ctrl, double val, double chan) {
  // dont do anything if there is no open output port!
  if ( device == NULL ) return;
  addNode( new MidiNode(MidiNode::MM_CTRL, wait, chan, ctrl, val) );
}

void MidiOutPort::sendBend(double wait, double bend, double chan) {
  // dont do anything if there is no open output port!
  if ( device == NULL ) return;
  addNode( new MidiNode(MidiNode::MM_BEND, wait, chan, bend) );
}

*/

void MidiOutPort::testOutput () 
{
  // Tobias Kunze's little testing algo from cm 1.4
  double time = 0;
  for (int x=0; x<12; x++) {
    // vals[0]=keynum, [1]=velocity, [2]=channel
    double key = x + (12 * (3 + Random::getSystemRandom().nextInt(5) )) ;
    double vel = 32.0 + Random::getSystemRandom().nextInt(64);
    double dur = .1 + (Random::getSystemRandom().nextInt(5) * .1);
    // add jiggle for microtuning testing...
    double jig= Random::getSystemRandom().nextDouble();
    sendNote(time, dur, key + jig, vel, 0.0, false);
    time += ((Random::getSystemRandom().nextInt(5) ^ 2) * (60.0 / 1000.0));
  }
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

double MidiOutPort::channeltunings[16][16] =
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
  microchancount=(int)(16.0/((double)microdivisions)); // num user addressable microchans
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
  return (int)(16.0/((double)t));
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

void MidiOutPort::sendTuning() 
{
  if (! isOpen() )
    return;
  int tunerow=getTuning()-1;
  for (int c=0; c<16; c++)
    {
      int b=(int)round(cm_rescale( channeltunings[tunerow] [c], 
				   -pitchbendwidth, pitchbendwidth,
				   0, 
				   16383,
				   1));
      //device->sendMessageNow( MidiMessage::pitchWheel(c+1,bendval));
      MidiMessage* m=new MidiMessage((0xe0 | c), (b & 127), ((b >> 7) & 127));
      addNode(new MidiNode(m));
    }
}

void MidiOutPort::getTuningValues(Array<int>& vals)
{
  int tunerow=getTuning()-1;
  for (int chan=0; chan<16; chan++)
    vals.add( (int)round(cm_rescale( channeltunings[tunerow] [chan], 
				     -pitchbendwidth, 
				     pitchbendwidth,
				     0,
				     16383,
				     1)));
}		

/*=======================================================================*
                               Instrument Assignment
 *=======================================================================*/

int MidiOutPort::getInstrument(int chan) 
{
  return programchanges[chan];
}


void MidiOutPort::getInstruments(Array<int>& vals)
{
  for (int chan=0; chan<16; chan++)
    vals.add(getInstrument(chan));
}

void MidiOutPort::setInstrument(int chan, int pc, bool send) 
{
  programchanges[chan]=pc;
}

void MidiOutPort::resetInstruments()
{
  for (int c=0; c<16; c++)
    programchanges[c]=0;
}

bool MidiOutPort::isInstrumentChannel(int chan)
{
  // true if physical chan accepts instruments (ie is not a channel
  // claimed by microtuning)
  return (0.0 == channeltunings[getTuning()-1][chan]);
}

void MidiOutPort::sendInstruments() 
{
  if (isOpen())
    {
      for (int c=0; c<16; c++)
	{
	  MidiMessage* m=new MidiMessage((0xc0 | c), programchanges[c]);
	  addNode(new MidiNode(m));
	}
    }
}

/*=======================================================================*
                               Midifile Writing
 *=======================================================================*/

void MidiOutPort::setOutputFile(String filename)
{
  //  std::cout << "ouputfile=" << filename.toUTF8() << "\n";
  sequenceFile.file=File(filename);
}

void MidiOutPort::saveSequence(bool ask)
{
  if (isSequenceEmpty()) 
    return;
  sequenceFile.bends=(getTuning()>1) ? true : false;

  if (ask || (sequenceFile.file==File::nonexistent))
    {
      String title;
  /*** 
      MidiFileInfoComponent* comp=new MidiFileInfoComponent(&sequenceFile);
      title=(ask) ? T("Save As") : T("Save");
      bool flag = DialogWindow::showModalDialog( title, comp, NULL,
						 Colour(0xffe5e5e5),
						 true, false, false);
      delete comp;
      if (!flag) return;
  ***/
    }

  captureSequence.updateMatchedPairs();
  if (sequenceFile.file.existsAsFile())
    sequenceFile.file.deleteFile();

  FileOutputStream outputStream(sequenceFile.file);
  MidiFile* midifile = new MidiFile();

  if (sequenceFile.ismsec)
    midifile->setSmpteTimeFormat(25, 40); // set to 1 msec resolution
  else
    midifile->setTicksPerQuarterNote(sequenceFile.qticks);

  MidiMessageSequence track0;
  track0.addEvent( sequenceFile.getTempoMessage(), 0);
  track0.addEvent( sequenceFile.getTimeSigMessage(), 0);
  track0.addEvent( sequenceFile.getKeySigMessage(), 0);

  // add optional tuning data to track 0
  Array<int> data;
  if (sequenceFile.bends)
    {
      getTuningValues(data);
      for (int c=0; c<data.size(); c++)
	track0.addEvent(MidiMessage((0xe0 | c), (data[c] & 127), 
				    ((data[c] >> 7) & 127)));
    }
  // add optional program changes to track 0
  if (sequenceFile.insts)
    {
      data.clear();
      getInstruments(data);
      for (int c=0; c<data.size(); c++)
	track0.addEvent(MidiMessage::programChange(c, data[c]));
    }  

  midifile->addTrack(track0);
  midifile->addTrack(captureSequence);

  const MidiMessageSequence* seq=midifile->getTrack(1);
  if (sequenceFile.ismsec)
    {
      // If writing milliseconds then convert the file's data from
      // seconds to milliseconds to match our smpte time format
      for (int i=0; i<seq->getNumEvents(); i++)
	{
	  MidiMessageSequence::MidiEventHolder* h=seq->getEventPointer(i);
	  h->message.setTimeStamp(h->message.getTimeStamp()*1000.0);
	}
    }
  else
    {
      // otherwise convert seconds to division per quarter
      double divs=(float)sequenceFile.qticks;
      for (int i=0; i<seq->getNumEvents(); i++)
	{
	  MidiMessageSequence::MidiEventHolder* h=seq->getEventPointer(i);
	  h->message.setTimeStamp(h->message.getTimeStamp()*divs);
	}
    }

  // optional clear after save
  //midifile->writeTo(outputStream) && sequenceFile.clear
  if (midifile->writeTo(outputStream)) 
    {
      Console::getInstance()->
	printOutput((T("Midifile: ") + 
		     sequenceFile.file.getFullPathName() +
		     T("\n")));
      captureSequence.clear();
    }
}

/*=======================================================================*
                               Midi In Port
 *=======================================================================*/

MidiInPort::MidiInPort()
  : devid (-1),
    device (NULL),
    tracing (0),
    channelMask(0),
    opcodeMask(0)
{
  String name=String::empty;
#ifdef GRACE
  Preferences* pref=Preferences::getInstance();
  name=pref->getStringProp(T("MidiInDevice"));
  channelMask=pref->getIntProp(T("MidiInChannelMask"), AllChannels);
  opcodeMask=pref->getIntProp(T("MidiInOpcodeMask"), AllOpcodes);
#endif
  if (name != String::empty)
    open(name);
}

MidiInPort::~MidiInPort() 
{
  close();
}

bool MidiInPort::open(String name) 
{
  StringArray devices = MidiInput::getDevices();
  int id=-1;
  for (int i=0;i<devices.size();i++)
    if (devices[i] == name)
      {
	id=i;
	break;
      }
  if (id == -1)
    {
      Console::getInstance()->
	printWarning(T("Warning: Midi input device ") + 
		     name + T(" does not exist.\n"));
      return false;
    }
  else
    return open(id);
}

bool MidiInPort::open(int id)
{
  // dont do anything if opening same port
  if (id==devid)
    return true;
  if (device != NULL)
    close();
  device = MidiInput::openDevice(id, this);
  if (device == NULL)
    {
      Console::getInstance()->
	printError(T(">>> Error: Failed to open midi input device ")
		   + String(id) + T(".\n"));
      return false;
    }
  else
    {
      devid=id;
      device->start();
#ifdef GRACE
      StringArray devices = MidiInput::getDevices();
      Preferences* pref=Preferences::getInstance();
      pref->setStringProp(T("MidiInDevice"), devices[id]);
#endif
      return true;
    }
}

bool MidiInPort::isOpen(int id)
{
  if (device == NULL)
    return false;
  else if (id == -1) // asking if ANY output device is open
    return true;
  else
    return (id == devid); // asking if specific dev is open
}

void MidiInPort::close(int id)
{
  if (device!=NULL)
    {
      device->stop();
      delete device;
      device=NULL;
      devid=-1;
    }
}

//
/// Channel Masking
//

int MidiInPort::getChannelMask()
{
  return channelMask;
}

void MidiInPort::setChannelMask(int mask)
{
  channelMask=mask;
#ifdef GRACE
  Preferences::getInstance()->setIntProp(T("MidiInChannelMask"),
					 channelMask);
#endif
}

//
/// Channel Testing
//

bool MidiInPort::isChannelActive(int chan)
{
  chan=jlimit(0, 15, chan);
  int mask=1 << chan;
  return Flags::test(channelMask, mask);
}

void MidiInPort::setChannelActive(int chan, bool active)
{
  chan=jlimit(0, 15, chan);  
  int mask=1 << chan;
  if (active)
    Flags::setOn(channelMask, mask);
  else
    Flags::setOff(channelMask, mask);
#ifdef GRACE
  Preferences::getInstance()->setIntProp(T("MidiInChannelMask"),
					 channelMask);
#endif
}

void MidiInPort::toggleChannelActive(int chan)
{
  chan=jlimit(0, 15, chan);
  int mask=1 << chan;
  Flags::toggle(channelMask, mask);
#ifdef GRACE
  Preferences::getInstance()->setIntProp(T("MidiInChannelMask"),
					 channelMask);
#endif
}

//
/// Opcode Masking
//

int MidiInPort::getOpcodeMask()
{
  return opcodeMask;
}

void MidiInPort::setOpcodeMask(int mask)
{
  opcodeMask=mask;
#ifdef GRACE
  Preferences::getInstance()->setIntProp(T("MidiInOpcodeMask"),
					 opcodeMask);
#endif
}

//
/// Opcode Testing
//

bool MidiInPort::isOpcodeActive(int val, bool isop)
{
  if (isop)
    val=MidiNode::opcodeToIndex(val);
  int index=jlimit(0, 6, val);
  int mask=1 << index;
  return Flags::test(opcodeMask, mask);
}

void MidiInPort::toggleOpcodeActive(int index)
{
  index=jlimit(0, 6, index);
  int mask=1 << index;
  Flags::toggle(opcodeMask, mask);
#ifdef GRACE
  Preferences::getInstance()->setIntProp(T("MidiInOpcodeMask"),
					 opcodeMask);
#endif
}

void MidiInPort::setOpcodeActive(int index, bool active)
{
  index=jlimit(0, 6, index);
  int mask=1 << index;
  if (active)
    Flags::setOn(opcodeMask, mask);
  else
    Flags::setOff(opcodeMask, mask);
#ifdef GRACE
  Preferences::getInstance()->setIntProp(T("MidiInOpcodeMask"),
					 opcodeMask);
#endif
}

//
/// Traceing
//

bool MidiInPort::isTracing()
{
  return tracing;
}

void MidiInPort::toggleTracing()
{
  tracing=!tracing;
}

void MidiInPort::setTracing(bool trace)
{
  tracing=trace;
}

//
/// Receiving
//

bool MidiInPort::isMessageActive(const MidiMessage &msg)
{
  int ch=msg.getChannel(); // JUCE: channel messages are >0
  return ((ch>0) && 
	  isChannelActive(ch-1) &&
	  ((msg.isNoteOn() && 
	    isOpcodeActive(MidiNode::MM_ON, true)) ||
	   (msg.isNoteOff() && 
	    isOpcodeActive(MidiNode::MM_OFF, true)) ||
	   (msg.isController() && 
	    isOpcodeActive(MidiNode::MM_CTRL, true)) ||
	   (msg.isProgramChange() && 
	    isOpcodeActive(MidiNode::MM_PROG, true)) ||
	   (msg.isPitchWheel() && 
	    isOpcodeActive(MidiNode::MM_BEND, true)) ||
	   (msg.isAftertouch() && 
	    isOpcodeActive(MidiNode::MM_TOUCH, true)) ||
	   (msg.isChannelPressure() && 
	    isOpcodeActive(MidiNode::MM_PRESS, true))));
}

void MidiInPort::handleIncomingMidiMessage(MidiInput *dev,
					   const MidiMessage &msg) 
{
  if (isMessageActive(msg))
    {
      //      std::cout << "handleIncomingMidiMessage()\n";
      Scheme::getInstance()->midiin(msg);
      if (isTracing())
	{
	  int op=(msg.getRawData()[0] & 0xf0)>>4;
	  // JUCE: channel messages are >0
	  int ch=msg.getChannel()-1;
	  int sz=msg.getRawDataSize();
	  int d1=msg.getRawData()[1] & 0x7f;
	  int d2=0;
	  if (sz>2)
	    d2=msg.getRawData()[2] & 0x7f;
	  String msg=MidiNode::opcodeToString(op);
	  msg << T(" ") << String(ch)
	      << T(" ") << String(d1)
	      << T(" ") << String(d2)
	      << T("\n");
	  Console::getInstance()->printOutput(msg);
	}
    }
}

void MidiInPort::handlePartialSysexMessage(MidiInput *dev,
					   const juce::uint8 *data, 
					   const int num, 
					   const double time)
{
}

// 
// Importing
//

bool MidiInPort::readMidifile(File path, MidiFile& midifile)
{
  FileInputStream* input=path.createInputStream();
  if (input==NULL)
    return false;
  bool ok=midifile.readFrom(*input);
  delete input;
  if (!ok)
    return false;
  int numtracks=midifile.getNumTracks();
  if (numtracks<1) 
    return false;

  int format=midifile.getTimeFormat();
  double smptetps=0.0; // smpte ticks per second
  // juce time format is postive for beats and negative for SMTPE
  if (format>0)
    midifile.convertTimestampTicksToSeconds();    
  else
    {
      // The juce function convertTimestampTicksToSeconds doesnt seem
      // to work for SMPTE ticks so we do it by hand.
      // juce smpte frames per second is negative upper byte
      int fps=0xFF-((format & 0xFF00) >> 8)+1;
      int tpf=format & 0xFF;
      smptetps=fps*tpf;
      // start importing at track 1 in level 1 file
      //  int track=((numtracks==1) ? 0 : 1);
      for (int track=0; track<numtracks; track++)
	{
	  const MidiMessageSequence* seq=midifile.getTrack(track);
	  // convert SMPTE ticks to seconds. The juce function
	  // convertTimestampTicksToSeconds doesnt seem to work for SMPTE
	  // ticks.
	  for (int i=0; i<seq->getNumEvents(); i++)
	    {
	      MidiMessageSequence::MidiEventHolder* h=
		seq->getEventPointer(i);
	      double t=h->message.getTimeStamp();
	      h->message.setTimeStamp(t/smptetps);
	    }
	}
    }
  return true;
}

void MidiInPort::importMidifile(File pathname, int track,
				double start, double endtime, 
				int chanmask, int typemask,
				int where, int format)
{
  MidiFile midifile;
  if (!readMidifile(pathname, midifile))
    {
      String err=T(">>> Error: ");
      err << pathname.getFullPathName()
	  << T(" is not a valid MIDI file.\n");
      Console::getInstance()->printError(err);
      return;
    }

  std::cout << "importing " << pathname.getFullPathName().toUTF8()
	    << " tracks=" << track 
	    << " start=" << start 
	    << " endtime=" << endtime 
	    << " chanmask=" << chanmask
	    << " opmask=" << typemask 
	    << " where=" << where 
	    << " format=" << format 
	    << "/n";

}

void MidiInPort::exportMidiMessageSequence(MidiMessageSequence* seq,
					   String name,
					   double start,
					   double endtime,
					   int chanmask,
					   int opmask,
					   int where, 
					   int format)
{
  // seq->updateMatchedPairs();
  bool donote=Flags::test(opmask, MidiFlags::OnMask);
  bool dotouch=Flags::test(opmask, MidiFlags::TouchMask);
  bool doctrl=Flags::test(opmask, MidiFlags::CtrlMask);
  bool doprog=Flags::test(opmask, MidiFlags::ProgMask);
  bool dobend=Flags::test(opmask, MidiFlags::BendMask);
  bool dopress=Flags::test(opmask, MidiFlags::PressMask);

  bool dometa=Flags::test(opmask, MidiFlags::MetaMask);

  std::cout << opmask << " "<< MidiFlags::MetaMask << "dometas=" << dometa << "\n";


  int count[7]={0,0,0,0,0,0,0};
  String prefix, indent, spacer, ending;
  String opener, closer;
  String outstr=String::empty;
  bool sending=false;
  int index;

  switch (format) 
    {
    case ExportIDs::SalData :
      prefix=String::empty;
      indent=T("   "); 
      spacer=T(" ");
      opener=T("{");
      closer=T("}\n");
      ending=T("  }\n");
      break;
    case ExportIDs::LispData :
      prefix=String::empty;
      indent=T("    "); 
      spacer=T(" ");
      opener=T("(");
      closer=T(")\n");
      ending=T("  ))\n");
      break;
    case ExportIDs::LispSend :
      prefix=T("(begin\n");
      indent=T("  ");
      opener=T("(send ");
      closer=T(")\n");
      spacer=T(" ");
      ending=T("  )\n");
      sending=true;
      break;
    case ExportIDs::SalSend :
      prefix=T("begin\n"); 
      indent=T("  "); 
      spacer=T(", ");
      opener=T("send ");
      closer=T("\n");
      ending=T("end\n");
      sending=true;
      break;
    }

  StringArray outstrs;
  if (!sending)
    if (format==ExportIDs::SalData)
      {
	outstrs.add(T("define variable ") + name + T("-notes = \n  {\n"));
	outstrs.add(T("define variable ") + name + T("-progs = \n  {\n"));
	outstrs.add(T("define variable ") + name + T("-bends = \n  {\n"));
	outstrs.add(T("define variable ") + name + T("-ctrls = \n  {\n"));
	outstrs.add(T("define variable ") + name + T("-touch = \n  {\n"));
	outstrs.add(T("define variable ") + name + T("-press = \n  {\n"));
	outstrs.add(T("define variable ") + name + T("-metas = \n  {\n"));
      }
    else
      {
	outstrs.add(T("(define ") + name + T("-notes\n  '(\n"));
	outstrs.add(T("(define ") + name + T("-progs\n  '(\n"));
	outstrs.add(T("(define ") + name + T("-bends\n  '(\n"));
	outstrs.add(T("(define ") + name + T("-ctrls\n  '(\n"));
	outstrs.add(T("(define ") + name + T("-touch\n  '(\n"));
	outstrs.add(T("(define ") + name + T("-press\n  '(\n"));
	outstrs.add(T("(define ") + name + T("-metas\n  '(\n"));
      }

  for (int i=0; i< seq->getNumEvents(); i++)
    {
      MidiMessageSequence::MidiEventHolder*
	ev=seq->getEventPointer(i);
      // skip if less than start time
      if ((start>0) && (ev->message.getTimeStamp()<start))
	continue;
      // stop if greater than end time
      if ((endtime>0) && (ev->message.getTimeStamp()>endtime))
	break;
      int chan=ev->message.getChannel();
      String line=String::empty;
      String time=String::formatted(T("%.03f"),
				    ((float)ev->message.getTimeStamp()));
      // is channel message and wants this channel
      if (chan>0 && Flags::test(chanmask,1<<(chan-1)))
	{
	  chan--;  // Juce channel values are 1 based!
	  if (donote && ev->message.isNoteOn())
	    {
	      double dur;
	      if (ev->noteOffObject)
		dur=(ev->noteOffObject->message.getTimeStamp() -
		     ev->message.getTimeStamp());
	      else
		dur=.5; // can a missing note off happen??
	      line << indent 
		   << opener
		   << ((sending) ? T("\"mp:note\" ") : T(""))
		   << time
		   << spacer << String::formatted(T("%.03f"), (float)dur)
		   << spacer << String(ev->message.getNoteNumber())
		   << spacer << String(ev->message.getVelocity())
		   << spacer << String(chan)
		   << closer;
	      index=0;
	      count[index] += 1;
	    }
	  else if (doprog && ev->message.isProgramChange())
	    {
	      line << indent
		   << opener
		   << ((sending) ? T("\"mp:prog\" ") : T(""))
		   << time
		   << spacer << String(ev->message.getProgramChangeNumber())
		   << spacer << String(chan)
		   << closer;
	      index=1;
	      count[index] += 1;
	    }
	  else if (dobend && ev->message.isPitchWheel())
	    {
	      line << indent
		   << opener
		   << ((sending) ? T("\"mp:bend\" ") : T(""))
		   << time
		   << spacer << String(ev->message.getPitchWheelValue())
		   << spacer << String(chan)
		   << closer;
	      index=2;
	      count[index] += 1;
	    }
	  else if (doctrl && ev->message.isController())
	    {
	      line << indent
		   << opener
		   << ((sending) ? T("\"mp:ctrl\" ") : T(""))
		   << time
		   << spacer << String(ev->message.getControllerNumber())
		   << spacer << String(ev->message.getControllerValue())
		   << spacer << String(chan)
		   << closer;
	      index=3;
	      count[index] += 1;
	    }
	  else if (dotouch && ev->message.isAftertouch())
	    {
	      line << indent
		   << opener
		   << ((sending) ? T("\"mp:touch\" ") : T(""))
		   << time
		   << spacer << String(ev->message.getAfterTouchValue())
		   << spacer << String(chan)
		   << closer;
	      index=4;
	      count[index] += 1;
	    }
	  else if (dopress && ev->message.isChannelPressure())
	    {
	      line << indent
		   << opener
		   << ((sending) ? T("\"mp:press\" ") : T(""))
		   << spacer << time
		   << spacer<< String(ev->message.getChannelPressureValue())
		   << spacer << String(chan)
		   << closer;
	      index=5;
	      count[index] += 1;
	    }	  
	  if (sending)
	    outstr << line;
	  else
	    outstrs.set(index,outstrs[index]+line);
	} // end channel messages
      else if (dometa && ev->message.isMetaEvent())
	{
	  String name=String::toHexString(ev->message.getMetaEventType());
	  line << indent << opener;
	  if (sending) line << T("\"mp:meta\" ") ;
	  line << time << spacer << T("#x") << name << spacer;
	  if (ev->message.isTrackMetaEvent() || 
	      ev->message.isMidiChannelMetaEvent() &&
	      (ev->message.getMetaEventLength()>0))
	    {
	      line << ev->message.getMetaEventData()[0];
	    }
	  else if (ev->message.isTextMetaEvent() ||
		   ev->message.isTrackNameEvent() )
	    {
	      line << ev->message.getTextFromTextMetaEvent().quoted();
	    }
	  else if (ev->message.isTempoMetaEvent())
	    {
	      line << 60.0 / ev->message.getTempoSecondsPerQuarterNote();
	    }
	  else if (ev->message.isTimeSignatureMetaEvent())
	    {
	      int n,d;
	      ev->message.getTimeSignatureInfo(n,d);
	      line << n << spacer << d;
	    }
	  else if (ev->message.isKeySignatureMetaEvent())
	    {
	      line << ev->message.getKeySignatureNumberOfSharpsOrFlats();
	    }
	  else
	    continue;
	  line << closer;
	  index=6;
	  count[index] += 1;
	  
	  if (sending)
	    outstr << line;
	  else
	    outstrs.set(index,outstrs[index]+line);
	}
      
    }  // end for loop
  
  if (sending)
    {
      outstr = prefix + outstr + ending;
    }
  else
    {
      for (int i=0; i< 7; i++)
	if (count[i]>0)
	  outstr << outstrs[i] << ending;
    }

  if (where==ExportIDs::ToConsole)
    Console::getInstance()->printOutput(outstr);
  else if (where==ExportIDs::ToClipboard)
    SystemClipboard::copyTextToClipboard(outstr);
#ifdef GRACE
  else if (where==ExportIDs::ToEditor)
    new TextEditorWindow(File::nonexistent,
			 outstr,
			 ExportIDs::getTextID(format),
			 T("Untitled") );
#endif
}


/*=======================================================================*
                            GRACE GUI CODE
 *=======================================================================*/

#ifdef GRACE

/*=======================================================================*
                           Instrument Dialog
 *=======================================================================*/

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
    instruments[chan]=inst;
    chan++;
    // now set all the microtuned channels to the same instrument!
    while ( (chan<16) && !port->isInstrumentChannel(chan) )
      {
	instruments[chan]=inst;
	chan++;
      }
  }

  int rowToChannel(int r)
  {
    // return physical channel number of row
    int t=port->getTuning();
    if ( r < port->getTuningChannels(t) )
      return r * port->getTuningDivisions(t);
    else
      return port->getTuningChannelsClaimed(t) +
	(r - port->getTuningChannels(t));
  }

  int getNumRows()
  {
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
      //g.fillAll(Colours::lightgoldenrodyellow); 
      g.fillAll(Colour::fromString(T("401111ee")));
    g.setColour (Colours::black);
    g.setFont (height * 0.7f);
    
    int tune=port->getTuning(), chan;
    String chantext, tunetext, insttext;
    // set chantext to microchannel number or to physcial channel number
    // if channel is above them
    if (rowNumber < port->getTuningChannels(tune))
      {
	chantext=String(rowNumber);
	tunetext=port->getTuningName(tune);
	// actual channel number
	chan=rowNumber*port->getTuningDivisions(tune);
      }
    else 
      { 
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
    g.drawText (chantext, 5, 0, 56, height, Justification::centred,true);
    g.drawText (tunetext, 70-5, 0, 80, height, Justification::centredLeft,
		true);
    g.drawText (insttext, 156, 0, width-156, height, 
		Justification::centredLeft,true);
  }

  void revertInstruments()
  {
    for (int c=0;c<16;c++)
      instruments[c]=port->programchanges[c];
  }
  
  void saveInstruments()
  {
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
      //      g.fillAll(Colours::lightgoldenrodyellow);
      g.fillAll(Colour::fromString(T("401111ee")));

    g.setColour (Colours::black);
    g.setFont (height * 0.7f);
    g.drawText (MidiMessage::getGMInstrumentName(rowNumber) ,
		5, 0, width, height,
		Justification::centredLeft, true);
  }
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
    label1=new Label(String::empty, T("Channel"));
    label2=new Label(String::empty, T("Tuning"));
    label3=new Label(String::empty, T("Instrument"));
    label4=new Label(String::empty, T("Instruments"));
    Font f=label1->getFont();
    f.setBold(true);
    label1->setFont(f);
    label2->setFont(f);
    label3->setFont(f);
    label4->setFont(f);
    addAndMakeVisible(label1 );
    addAndMakeVisible(label2 );
    addAndMakeVisible(label3 );
    addAndMakeVisible(label4 );
    addAndMakeVisible(assignments=new GMAssignmentList(p));
    assignments->setColour(ListBox::outlineColourId, Colours::black);
    assignments->setOutlineThickness(1);
    addAndMakeVisible(instruments=new GMInstrumentList(assignments));
    instruments->setColour(ListBox::outlineColourId, Colours::black);
    instruments->setOutlineThickness(1);
    //    addAndMakeVisible(button1=new TextButton(T("Revert")) );
    //    button1->addButtonListener(this);
    // revert button initially disabled
    //    button1->setEnabled(false);
    addAndMakeVisible(button2=new TextButton(T("Send")) );
    button2->addButtonListener(this);
    setSize(10 + 320 + 10 + 170 + 10, 450);
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
    //    deleteAndZero(button1);
    deleteAndZero(button2);
  }

  void resized() 
  {
    int asslistwidth=320;
    int inslistwidth=170;
    // 
    label1->setBounds(10, 10, 56, 24); // Channel
    label2->setBounds(70, 10, 72, 24); // Tuning
    label3->setBounds(160, 10, 78, 24); // Instrument
    label4->setBounds(10+320+10, 8, inslistwidth, 24);
    // list boxes
    assignments->setBounds(10, 30, asslistwidth, 
			   assignments->getRowHeight()*16);
    instruments->setBounds(10 + 320 + 10,
			   30,
			   inslistwidth,
			   instruments->getRowHeight()*16);
    int mid=getWidth()/2;
    //    button1->setSize(60,24);
    //    button1->setTopLeftPosition(mid - button1->getWidth() - 16,
    //				assignments->getBottom() + 24);
    button2->setSize(100,24);
    button2->setTopLeftPosition(mid-50, assignments->getBottom() + 20);
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
  assignments->setInstrument(chan,inst);
  assignments->repaintRow(arow);
  // Mark assignment list as changed and enable Revert button
  assignments->setChanged(true);
  //  ((InstrumentView *)getParentComponent())->button1->setEnabled(true);
}

void InstrumentView::buttonClicked (Button *button) 
{
  if ( button->getName() == T("Send") ) 
    {
      //printf("SENDING!\n");
      // copy/send program changes, clear changed flag, deselect all
      // rows in list boxes and disable Revert button
      assignments->saveInstruments();
      port->sendInstruments();
      assignments->setChanged(false);
      assignments->deselectAllRows();
      instruments->deselectAllRows();
      //      button1->setEnabled(false);
    }
  else if ( button->getName() == T("Revert") )
    {
      // restore Midi Port's program changes, clear changed flag,
      // deselect all rows in list boxes and disable Revert button
      assignments->revertInstruments();
      assignments->setChanged(false);
      assignments->deselectAllRows();
      //assignments->updateContent();
      for (int r=0;r<assignments->getNumRows(); r++)
	assignments->repaintRow(r);
      instruments->deselectAllRows();
      //      button1->setEnabled(false);
    }
}

class MidiInstrumentsWindow : public DocumentWindow
{
public:
  void closeButtonPressed() {delete this;}
  MidiInstrumentsWindow(InstrumentView* comp) :
    DocumentWindow(String("Instruments"), Colour(0xffe5e5e5),
		   DocumentWindow::closeButton, true)
  {
    centreWithSize(comp->getWidth(),comp->getHeight());
    setContentComponent(comp);
    setResizable(false, false); 
    setUsingNativeTitleBar(true);
    setDropShadowEnabled(true);
    setVisible(true);
  }
  ~MidiInstrumentsWindow() {}
};

void MidiOutPort::openInstrumentsDialog ()
{
  new MidiInstrumentsWindow(new InstrumentView(this));
}

/*=======================================================================*
                         MidiFile Settings Dialog
 *=======================================================================*/

class MidiFileInfoComponent : public Component,
			      public FilenameComponentListener,
			      public ComboBoxListener,
			      public SliderListener,
			      public ButtonListener
{
public:
  MidiFileInfoComponent (MidiFileInfo* info, bool saveing=false);
  ~MidiFileInfoComponent();
  //  void paint (Graphics& g);
  void resized();
  void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
  void sliderValueChanged (Slider* sliderThatWasMoved);
  void buttonClicked (Button* buttonThatWasClicked);
  bool parseTimeSig(int& numer, int& denom);
  void filenameComponentChanged(FilenameComponent* f) ;
private:
  MidiFileInfo* midifileinfo;
  FilenameComponent* fileeditor;
  Label* timelabel;
  ToggleButton* millibutton;
  ToggleButton* ticksbutton;
  Slider* ticksslider;
  ComboBox* keysigmenu;
  Label* keysiglabel;
  Label* filelabel;
  Slider* temposlider;
  Label* timesiglabel;
  Label* tempolabel;
  TextButton* cancelbutton;
  TextButton* savebutton;
  TextEditor* timesigeditor;
  ToggleButton* tuningbutton;
  ToggleButton* instrumentbutton;
  ToggleButton* clearbutton;
  MidiFileInfoComponent (const MidiFileInfoComponent&);
  const MidiFileInfoComponent& operator= (const MidiFileInfoComponent&);
};

bool MidiFileInfoComponent::parseTimeSig (int& n, int& d)
{
  String str=timesigeditor->getText();
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

MidiFileInfoComponent::MidiFileInfoComponent(MidiFileInfo* info,
					     bool saveing)
  : midifileinfo (0),
    fileeditor (0),
    timelabel (0),
    millibutton (0),
    ticksbutton (0),
    ticksslider (0),
    keysigmenu (0),
    keysiglabel (0),
    filelabel (0),
    temposlider (0),
    timesiglabel (0),
    tempolabel (0),
    cancelbutton (0),
    savebutton (0),  // remains null if dialog is for settings
    timesigeditor (0),
    tuningbutton (0),
    instrumentbutton (0),
    clearbutton (0)
{
  midifileinfo=info;
  File file=midifileinfo->file;
  if (file==File::nonexistent)
    file=File::getSpecialLocation(File::userHomeDirectory).
      getChildFile(T("test.mid"));

  // if dialog is for saving then add a top line with file info
  // and a botton line with save and cancel buttons
  if (saveing)
    {
      addAndMakeVisible (filelabel = new Label (T("filelabel"),
						T("Midifile:")));
      filelabel->setFont (Font (15.0000f, Font::plain));
      filelabel->setJustificationType (Justification::centredLeft);
      filelabel->setEditable (false, false, false);
      filelabel->setColour (TextEditor::textColourId, Colours::black);
      filelabel->setColour (TextEditor::backgroundColourId, Colour(0x0));
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
      addAndMakeVisible(fileeditor);
      addAndMakeVisible(clearbutton =
			new ToggleButton (T("clearbutton")));
      clearbutton->setButtonText(T("Clear Seq after save"));
      clearbutton->setToggleState(midifileinfo->clear, false);
      clearbutton->addButtonListener (this);
      addAndMakeVisible(cancelbutton = new TextButton(T("cancelbutton")));
      cancelbutton->setButtonText (T("Cancel"));
      cancelbutton->addButtonListener (this);
      addAndMakeVisible (savebutton = new TextButton (T("savebutton")));
      savebutton->setButtonText(T("Save"));
      savebutton->addButtonListener(this);
    }
  else 
    savebutton=NULL;
  
  // time format row
  addAndMakeVisible(timelabel = new Label(T(""), T("Time format:")));
  timelabel->setFont(Font (15.0000f, Font::plain));
  timelabel->setJustificationType(Justification::centredLeft);
  timelabel->setEditable(false, false, false);
  timelabel->setColour(TextEditor::textColourId, Colours::black);
  timelabel->setColour(TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible(millibutton = new ToggleButton (T("")));
  millibutton->setButtonText(T("Milliseconds"));
  millibutton->setRadioGroupId(1);
  
  millibutton->addButtonListener(this);
  
  addAndMakeVisible(ticksbutton = new ToggleButton (T("")));
  ticksbutton->setButtonText(T("Ticks per Quarter:"));
  ticksbutton->setRadioGroupId(1);
  ticksbutton->addButtonListener(this);
  
  addAndMakeVisible(ticksslider = new Slider (T("")));
  ticksslider->setRange (0, 4000, 2);
  ticksslider->setSliderStyle (Slider::LinearHorizontal);
  ticksslider->setTextBoxStyle (Slider::TextBoxLeft, false, 40, 24);
  ticksslider->setValue(info->qticks);
  ticksslider->addListener(this);
  
  if (info->ismsec)
    {
      millibutton->setToggleState(true, false);
      ticksbutton->setToggleState(false, false);
      ticksslider->setEnabled(false);
    }
  else
    {
      millibutton->setToggleState(false, false);
      ticksbutton->setToggleState(true, false);
      ticksslider->setEnabled(true);
    }  
  
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
  
  addAndMakeVisible(timesigeditor = new TextEditor (T("timesigeditor")));
  timesigeditor->setMultiLine (false);
  timesigeditor->setReturnKeyStartsNewLine (false);
  timesigeditor->setReadOnly (false);
  timesigeditor->setScrollbarsShown (true);
  timesigeditor->setCaretVisible (true);
  timesigeditor->setPopupMenuEnabled (true);
  String text=String(info->tsig1) + T("/") + String(info->tsig2);
  timesigeditor->setText (text);

  addAndMakeVisible(tuningbutton = new ToggleButton (T("tuningbutton")));
  tuningbutton->setButtonText (T("Include Current Tuning"));
  tuningbutton->setToggleState(midifileinfo->bends, false);
  tuningbutton->addButtonListener (this);
  
  addAndMakeVisible(instrumentbutton =
		    new ToggleButton (T("instrumentbutton")));
  instrumentbutton->setToggleState(midifileinfo->insts, false);
  instrumentbutton->setButtonText (T("Include Current Instruments"));
  instrumentbutton->addButtonListener (this);
  
  setSize (600, (saveing) ? 200 : 120);
}

MidiFileInfoComponent::~MidiFileInfoComponent()
{
  deleteAndZero(fileeditor);
  deleteAndZero(millibutton);
  deleteAndZero(ticksbutton);
  deleteAndZero(ticksslider);
  deleteAndZero(keysigmenu);
  deleteAndZero(keysiglabel);
  deleteAndZero(filelabel);
  deleteAndZero(temposlider);
  deleteAndZero(timesiglabel);
  deleteAndZero(tempolabel);
  deleteAndZero(cancelbutton);
  deleteAndZero(savebutton);
  deleteAndZero(timesigeditor);
  deleteAndZero(tuningbutton);
  deleteAndZero(instrumentbutton);
  deleteAndZero(clearbutton);
}

void MidiFileInfoComponent::resized()
{
  int y=12;
  // only active is saving file
  if (savebutton)
    {

      filelabel->setBounds(    12, y,  56, 24);
      fileeditor->setBounds(   76, y, 295, 24);
      clearbutton->setBounds( 392, y, 200, 24); 
      y += 36;
    }
  timelabel->setBounds(         12, y,  88, 24);
  millibutton->setBounds(      128, y, 104, 24);
  ticksbutton->setBounds(      268, y, 136, 24);
  ticksslider->setBounds(      412, y, 120, 24);

  y += 36;
  tempolabel->setBounds(        12, y,  56, 24);
  temposlider->setBounds(       76, y, 120, 24);
  timesiglabel->setBounds(     217, y, 104, 24);
  timesigeditor->setBounds(    329, y,  40, 24);
  keysigmenu->setBounds(       496, y,  80, 24);
  keysiglabel->setBounds(      392, y,  96, 24);

  y += 36;
  tuningbutton->setBounds(     120, y, 168, 24);
  instrumentbutton->setBounds( 328, y, 200, 24);  

  // only active is saving file
  if (savebutton)
    {
      y += 36;
      cancelbutton->setBounds( 200, 156, 88, 24);
      savebutton->setBounds(   320, 156, 88, 24);
    }
}

void MidiFileInfoComponent::filenameComponentChanged(FilenameComponent* f) 
{
  if (f == fileeditor)
    {
      midifileinfo->file=fileeditor->getCurrentFile();
    }
}

void MidiFileInfoComponent::comboBoxChanged (ComboBox* combobox)
{
  if (combobox == keysigmenu)
    {
      midifileinfo->keysig=combobox->getSelectedId();
    }
}

void MidiFileInfoComponent::sliderValueChanged (Slider* slider)
{
  if (slider == ticksslider)
    {
      midifileinfo->qticks=(int)slider->getValue();
    }
  else if (slider == temposlider)
    {
      midifileinfo->tempo=(int)slider->getValue();
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
	  if (! AlertWindow::showOkCancelBox(AlertWindow::QuestionIcon, 
					     T("Save"), msg,
					     T("Overwrite"),
					     T("Cancel")))
	    return;
	}


      ((DialogWindow *)getTopLevelComponent())->exitModalState(true);
    }
  else if (button == millibutton)
    {
      midifileinfo->ismsec=button->getToggleState();
      if (button->getToggleState())
	{
	  ticksslider->setEnabled(false);
	}
      else
	{
	  ticksslider->setEnabled(true);
	}
    }
  else if (button == ticksbutton)
    {
      midifileinfo->ismsec=!button->getToggleState();
      if (button->getToggleState())
	{
	  ticksslider->setEnabled(true);
	}
      else
	{
	  midifileinfo->ismsec=true;
	  ticksslider->setEnabled(true);
	}
    }
  else if (button == tuningbutton)
    {
      midifileinfo->bends=button->getToggleState();
    }
  else if (button == instrumentbutton)
    {
      midifileinfo->insts=button->getToggleState();
    }
  else if (button == clearbutton)
    {
      midifileinfo->clear=button->getToggleState();
    }
}

void MidiOutPort::openFileSettingsDialog ()
{
  MidiFileInfoComponent* comp=new MidiFileInfoComponent(&sequenceFile);
  DialogWindow::showModalDialog(T("Midifile Settings"), 
				comp,
				NULL,
				Colour(0xffe5e5e5),
				true, 
				false,
				false);
  int numer,denom;
  if (comp->parseTimeSig(numer, denom))
    {
      sequenceFile.tsig1=numer;
      sequenceFile.tsig2=denom;
    }
  delete comp;
}

/*=======================================================================*
                         MidiFile Import Dialog
 *=======================================================================*/

class MidiFileImportComponent : public Component,
                                public ComboBoxListener,
                                public LabelListener,
                                public ButtonListener
{
public:
  
  MidiFileImportComponent (File path, MidiFile* file);
  ~MidiFileImportComponent();
  void doImport();
  //  void paint (Graphics& g);
  void resized();
  void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
  void labelTextChanged (Label* labelThatHasChanged);
  void buttonClicked (Button* buttonThatWasClicked);
  
  String channelMessageImportText(MidiMessage msg, double offtime, 
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
  ToggleButton* metabutton;
  ComboBox* channelmenu;
  ToggleButton* consolebutton;
  ToggleButton* clipboardbutton;
  ToggleButton* neweditorbutton;
  ToggleButton* salbutton;
  ComboBox* dataformatmenu;
private:
  MidiFile* midifile;
  File pathname;
  GroupComponent* messagegroup;
  GroupComponent* midifilegroup;
  Label* tracklabel;
  Label* fromlabel;
  Label* tolabel;
  Label* channellabel;
  GroupComponent* exporttogroup;
  TextButton* exportbutton;
  Label* dataformatlabel;
};

class MidifileImportWindow : public DocumentWindow
{
public:
  void closeButtonPressed() {delete this;}
  MidifileImportWindow(String title, MidiFileImportComponent* comp) :
    DocumentWindow(title, 
		   Colour(0xffe5e5e5),
		   DocumentWindow::closeButton,
		   true)
  {
    comp->setVisible(true);
    centreWithSize(comp->getWidth(),comp->getHeight());
    setContentComponent(comp);
    setResizable(false, false); 
    setUsingNativeTitleBar(true);
    setDropShadowEnabled(true);
    setVisible(true);
  }
  ~MidifileImportWindow()
  {
    // dont have to delete content component
  }
};

MidiFileImportComponent::MidiFileImportComponent (File path, MidiFile* midi)
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
      metabutton (0),
      channellabel (0),
      channelmenu (0),
      exporttogroup (0),
      consolebutton (0),
      clipboardbutton (0),
      neweditorbutton (0),
      dataformatlabel (0),
      dataformatmenu (0),
      salbutton (0),
      exportbutton (0),
      midifile (0),
      pathname (File::nonexistent)
{
  pathname=path;
  midifile=midi;
  
  addAndMakeVisible (midifilegroup =
		     new GroupComponent (T("midifilegroup"),
					 T("Import")));
  
  addAndMakeVisible (tracklabel = new Label (T("tracklabel"),
					     T("Track:")));
  tracklabel->setFont (Font (15.0000f, Font::plain));
  tracklabel->setJustificationType (Justification::centredLeft);
  tracklabel->setEditable (false, false, false);
  tracklabel->setColour (TextEditor::textColourId, Colours::black);
  tracklabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

  addAndMakeVisible (trackmenu = new ComboBox (T("trackmenu")));
  trackmenu->setEditableText (false);
  trackmenu->setJustificationType (Justification::centredLeft);
  trackmenu->setTextWhenNothingSelected (String::empty);
  trackmenu->setTextWhenNoChoicesAvailable (T("(no choices)"));
  for (int i=0; i<midifile->getNumTracks(); i++)
    trackmenu->addItem(String(i), i+1); // juce: Id can't be 0
  trackmenu->addListener (this);
  // set the selected track to the first data track. in Level 0 files
  // this is track 0 and in Level 1 files its track 1. then we have to
  // add 1 to the actual track number to avoid a 0 id value.
  if (midifile->getNumTracks()==1) // is level 0 file
    trackmenu->setSelectedId(0 + 1);  
  else
    trackmenu->setSelectedId(1 + 1);

  addAndMakeVisible(channellabel = new Label(String::empty, T("Channel:")));
  channellabel->setFont (Font (15.0000f, Font::plain));
  channellabel->setJustificationType (Justification::centredLeft);
  channellabel->setEditable (false, false, false);
  channellabel->setColour (TextEditor::textColourId, Colours::black);
  channellabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible(channelmenu = new ComboBox(String::empty));
  channelmenu->setEditableText (false);
  channelmenu->setJustificationType (Justification::centredLeft);
  channelmenu->setTextWhenNothingSelected (String::empty);
  channelmenu->setTextWhenNoChoicesAvailable (T("(no choices)"));
  channelmenu->addItem (T("All"), MidiFlags::AllChannelsMask);
  channelmenu->addItem (T("0"), 1<<0);
  channelmenu->addItem (T("1"), 1<<1);
  channelmenu->addItem (T("2"), 1<<2);
  channelmenu->addItem (T("3"), 1<<3);
  channelmenu->addItem (T("4"), 1<<4);
  channelmenu->addItem (T("5"), 1<<5);
  channelmenu->addItem (T("6"), 1<<6);
  channelmenu->addItem (T("7"), 1<<7);
  channelmenu->addItem (T("8"), 1<<8);
  channelmenu->addItem (T("9"), 1<<9);
  channelmenu->addItem (T("10"), 1<<10);
  channelmenu->addItem (T("11"), 1<<11);
  channelmenu->addItem (T("12"), 1<<12);
  channelmenu->addItem (T("13"), 1<<13);
  channelmenu->addItem (T("14"), 1<<14);
  channelmenu->addItem (T("15"), 1<<15);
  channelmenu->setSelectedId(MidiFlags::AllChannelsMask);
  channelmenu->addListener (this);
  
  addAndMakeVisible(fromlabel = new Label(String::empty, T("Start:")));
  fromlabel->setFont (Font (15.0000f, Font::plain));
  fromlabel->setJustificationType (Justification::centredLeft);
  fromlabel->setEditable (false, false, false);
  fromlabel->setColour (TextEditor::textColourId, Colours::black);
  fromlabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible(frombuffer = new Label(String::empty, String::empty));
  frombuffer->setFont (Font (15.0000f, Font::plain));
  frombuffer->setJustificationType (Justification::centredLeft);
  frombuffer->setEditable (true, true, false);
  frombuffer->setColour (Label::backgroundColourId, Colours::white);
  frombuffer->setColour (Label::outlineColourId, Colour (0xb2808080));
  frombuffer->setColour (TextEditor::textColourId, Colours::black);
  frombuffer->setColour (TextEditor::backgroundColourId, Colour (0x0));
  frombuffer->addListener (this);
  
  addAndMakeVisible(tolabel = new Label(String::empty, T("End Time:")));
  tolabel->setFont (Font (15.0000f, Font::plain));
  tolabel->setJustificationType (Justification::centredLeft);
  tolabel->setEditable (false, false, false);
  tolabel->setColour (TextEditor::textColourId, Colours::black);
  tolabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible(tobuffer = new Label(String::empty, String::empty));
  tobuffer->setFont (Font (15.0000f, Font::plain));
  tobuffer->setJustificationType (Justification::centredLeft);
  tobuffer->setEditable (true, true, false);
  tobuffer->setColour (Label::backgroundColourId, Colours::white);
  tobuffer->setColour (Label::outlineColourId, Colour (0xb2808080));
  tobuffer->setColour (TextEditor::textColourId, Colours::black);
  tobuffer->setColour (TextEditor::backgroundColourId, Colour (0x0));
  tobuffer->addListener (this);
  
  // Include group

  addAndMakeVisible(messagegroup =
		    new GroupComponent (String::empty, T("Include")));

  addAndMakeVisible(notesbutton = new ToggleButton(String::empty));
  notesbutton->setButtonText (T("Notes"));
  notesbutton->addButtonListener (this);
  notesbutton->setToggleState (true, false);
  
  addAndMakeVisible(programchangebutton = new ToggleButton(String::empty));
  programchangebutton->setButtonText (T("Program Changes"));
  programchangebutton->addButtonListener (this);
  programchangebutton->setToggleState (true, false);
  
  addAndMakeVisible(pitchbendbutton = new ToggleButton(String::empty));
  pitchbendbutton->setButtonText (T("Pitch Bends"));
  pitchbendbutton->addButtonListener (this);
  pitchbendbutton->setToggleState (true, false);
   
  addAndMakeVisible(controlchangebutton = new ToggleButton(String::empty));
  controlchangebutton->setButtonText (T("Control Changes"));
  controlchangebutton->addButtonListener (this);
  controlchangebutton->setToggleState (true, false);
  
  addAndMakeVisible(aftertouchbutton = new ToggleButton(String::empty));
  aftertouchbutton->setButtonText (T("Aftertouch"));
  aftertouchbutton->addButtonListener (this);
  aftertouchbutton->setToggleState (true, false);
  
  addAndMakeVisible(pressurebutton = new ToggleButton(String::empty));
  pressurebutton->setButtonText (T("Channel Pressure"));
  pressurebutton->addButtonListener (this);
  pressurebutton->setToggleState (true, false);

  addAndMakeVisible(metabutton = new ToggleButton(String::empty));
  metabutton->setButtonText (T("Meta Messages"));
  metabutton->addButtonListener (this);
  metabutton->setToggleState (true, false);

  // Import To group

  addAndMakeVisible (exporttogroup = new GroupComponent (String::empty,
							 T("Import To")));
  addAndMakeVisible(consolebutton = new ToggleButton(String::empty));
  consolebutton->setButtonText (T("Console"));
  consolebutton->setRadioGroupId (1);
  consolebutton->addButtonListener (this);
  consolebutton->setToggleState (true, false);
  
  addAndMakeVisible(clipboardbutton = new ToggleButton(String::empty));
  clipboardbutton->setButtonText (T("Clipboard"));
  clipboardbutton->setRadioGroupId (1);
  clipboardbutton->addButtonListener (this);
  
  addAndMakeVisible(neweditorbutton = new ToggleButton(String::empty));
  neweditorbutton->setButtonText (T("Editor"));
  neweditorbutton->setRadioGroupId (1);
  neweditorbutton->addButtonListener (this);
  
  dataformatlabel=new Label(String::empty, T("Format:"));
  addAndMakeVisible(dataformatlabel);
  dataformatlabel->setFont (Font (15.0000f, Font::plain));
  dataformatlabel->setJustificationType (Justification::centredLeft);
  dataformatlabel->setEditable (false, false, false);
  dataformatlabel->setColour (TextEditor::textColourId, Colours::black);
  dataformatlabel->setColour (TextEditor::backgroundColourId,
			      Colour (0x0));

  addAndMakeVisible(dataformatmenu = new ComboBox(String::empty));
  dataformatmenu->setEditableText (false);
  dataformatmenu->setJustificationType (Justification::centredLeft);
  dataformatmenu->addItem (T("Midi values"), ExportIDs::Data);
  dataformatmenu->addItem (T("Send messages"), ExportIDs::Send);
  dataformatmenu->setSelectedId(ExportIDs::Data);
  dataformatmenu->addListener (this);

  addAndMakeVisible(salbutton = new ToggleButton(String::empty));
  salbutton->setButtonText(T("SAL"));
		    
  addAndMakeVisible(exportbutton = new TextButton(String::empty));
  exportbutton->setButtonText (T("Import"));
  exportbutton->addButtonListener (this);
  
  setSize (320, 412);
}

MidiFileImportComponent::~MidiFileImportComponent()
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
  deleteAndZero (metabutton);
  deleteAndZero (channellabel);
  deleteAndZero (channelmenu);
  deleteAndZero (exporttogroup);
  deleteAndZero (consolebutton);
  deleteAndZero (clipboardbutton);
  deleteAndZero (neweditorbutton);
  deleteAndZero (dataformatlabel);
  deleteAndZero (dataformatmenu);
  deleteAndZero (salbutton);
  deleteAndZero (exportbutton);
  deleteAndZero (midifile);
}

//void MidiFileImportComponent::paint (Graphics& g)
//{
//  g.fillAll (Colours::white);
//}

void MidiFileImportComponent::resized()
{
  midifilegroup->setBounds (8, 8, 304, 96);
  tracklabel->setBounds (16, 32, 48, 24);
  trackmenu->setBounds (72, 32, 50, 24);
  channellabel->setBounds (152, 32, 64, 24);
  channelmenu->setBounds (224, 32, 50, 24);
  fromlabel->setBounds (16, 68, 47, 24);
  frombuffer->setBounds (72, 68, 50, 24);
  tolabel->setBounds (152, 68, 64, 24);
  tobuffer->setBounds (224, 68, 50, 24);

  messagegroup->setBounds (8, 112, 304, 160);
  notesbutton->setBounds (16, 136, 136, 24);
  controlchangebutton->setBounds (168, 136, 128, 24);
  programchangebutton->setBounds (16, 168, 136, 24);
  aftertouchbutton->setBounds (168, 168, 128, 24);
  pitchbendbutton->setBounds (16, 200, 136, 24);
  pressurebutton->setBounds (168, 200, 128, 24);
  metabutton->setBounds (160-64, 232, 128, 24);

  exporttogroup->setBounds (8, 280, 304, 88);
  consolebutton->setBounds (16, 300, 88, 24);
  clipboardbutton->setBounds (109, 300, 88, 24);
  neweditorbutton->setBounds (208, 300, 88, 24);

  //  dataformatlabel->setBounds (40, 292, 88, 24);
  //dataformatmenu->setBounds (136, 292, 136, 24);
  dataformatlabel->setBounds (16, 332, 88, 24);
  dataformatmenu->setBounds (70, 332, 126, 24);
  salbutton->setBounds (208, 332, 136, 24);
  exportbutton->setBounds (160-52, 376, 104, 24);
}

void MidiFileImportComponent::comboBoxChanged (ComboBox* comboBox)
{
}

void MidiFileImportComponent::labelTextChanged (Label* label)
{
}

void MidiFileImportComponent::buttonClicked (Button* button)
{
  if (button == exportbutton)
    {
      doImport();
    }
}

void MidiFileImportComponent::doImport()
{
  int track=trackmenu->getSelectedId() - 1;
  double start=frombuffer->getText().getDoubleValue();
  double endtime=tobuffer->getText().getDoubleValue();
  int chanmask=channelmenu->getSelectedId();
  int typemask=0;
  if (notesbutton->getToggleState())
    typemask += MidiFlags::OnMask;
  if (aftertouchbutton->getToggleState())
    typemask += MidiFlags::TouchMask;
  if (controlchangebutton->getToggleState())
    typemask += MidiFlags::CtrlMask;
  if (programchangebutton->getToggleState())
    typemask += MidiFlags::ProgMask;
  if (pressurebutton->getToggleState())
    typemask += MidiFlags::PressMask;
  if (pitchbendbutton->getToggleState())
    typemask += MidiFlags::BendMask;
  if (metabutton->getToggleState())
    typemask += MidiFlags::MetaMask;

  int format=dataformatmenu->getSelectedId();
  if (salbutton->getToggleState())
    format=ExportIDs::toExportID(TextIDs::Sal, format);
  else
    format=ExportIDs::toExportID(TextIDs::Lisp, format);

  int where=0;
  if (consolebutton->getToggleState())
    where=ExportIDs::ToConsole;
  else if (clipboardbutton->getToggleState())
    where=ExportIDs::ToClipboard;
  else if (neweditorbutton->getToggleState() )
    where=ExportIDs::ToEditor;      

  std::cout << "importing " << pathname.getFullPathName().toUTF8()
	    << " track=" << track 
	    << " start=" << start 
	    << " endtime=" << endtime 
	    << " chanmask=" << chanmask
	    << " typemask=" << typemask 
	    << " where=" << where 
	    << " format=" << format 
	    << "\n";
  MidiMessageSequence* seq=(MidiMessageSequence*)midifile->getTrack(track);
  String name=pathname.getFileNameWithoutExtension();
  name << T("-track") << track;
  MidiInPort::getInstance()->
    exportMidiMessageSequence(seq, name, start, endtime,
			      chanmask, typemask, where, format);
}

void MidiInPort::openImportMidifileDialog()
{
  FileChooser chooser (T("Choose MIDI file"),
		       File::getSpecialLocation (File::userHomeDirectory),
		       "*.mid");
  if (!chooser.browseForFileToOpen())
    return;
  File file=chooser.getResult();
  MidiFile* midi=new MidiFile();
  if (!readMidifile(file, *midi))
    {
      String err=T(">>> Error: ");
      err << file.getFullPathName()
	  << T(" is not a valid MIDI file.\n");
      Console::getInstance()->printError(err);
      delete midi;
      return;
    }
  MidiFileImportComponent* c=new MidiFileImportComponent(file,midi);
  String t=T("Import ");
  t << file.getFileName();
  new MidifileImportWindow(t,c);
}


#endif
