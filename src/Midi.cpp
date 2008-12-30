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
#endif
#include <iostream>

juce_ImplementSingleton(MidiOutPort)

juce_ImplementSingleton(MidiInPort)

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
      
    case CommandIDs::MidiSeqExport :
      exportSequence();
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

void MidiOutPort::sendNote(double wait, double duration, float keynum, 
			   float amplitude, float channel, bool toseq) 
{
  //  std::cout << "channel=" << channel << "\n";

  jlimit( (float)0.0, (float)15.0, channel);

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
      float foo=keynum;
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

void MidiOutPort::sendData(int type, double wait, float chan, 
			   float data1, float data2, bool toseq)
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
	  addEvent(MidiMessage::noteOn(ch+1, d1, data2),
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

void MidiOutPort::testOutput () 
{
  // Tobias Kunze's little testing algo from cm 1.4
  double time = 0;
  for (int x=0; x<12; x++) {
    // vals[0]=keynum, [1]=velocity, [2]=channel
    float key = x + (12 * (3 + Random::getSystemRandom().nextInt(5) )) ;
    float vel = 32.0 + Random::getSystemRandom().nextInt(64);
    // MILLI
    // float dur = ((( 2 + Random::getSystemRandom().nextInt(6)) ^ 2) * (60.0 / 1000.0));
    float dur = .1 + (Random::getSystemRandom().nextInt(5) * .1);
    // add jiggle for microtuning testing...
    float jig= Random::getSystemRandom().nextFloat();
    sendNote(time, dur, key + jig, vel, 0.0, false);
    // MILLI
    time += ((Random::getSystemRandom().nextInt(5) ^ 2) * (60.0 / 1000.0));
  }
}

////////////////////////////////////////////////////////////////////////////
// MIDI Input port
////////////////////////////////////////////////////////////////////////////

MidiInPort::MidiInPort()
  : devid (-1),
    device (NULL),
    runmode (STOPPED),
    trace (false),
    channelMask(0),
    opcodeMask(0),
    console (NULL)
{

  /***  receiveComponent = new MidiReceiveComponent();
   ***/
  String name=String::empty;
#ifdef GRACE
  Preferences* prefs=Preferences::getInstance();
  name=prefs->getStringProp(T("MidiInDevice"));
  /*** channelMask=prefs->getMidiInChannelMask();
  opcodeMask=prefs->getMidiInMessageMask();
  ***/
#endif
  if (name != String::empty)
    open(name);
}

MidiInPort::~MidiInPort() 
{
  if (device != NULL) 
    {
      if ( isActive() )
	stop();
      delete device;
    }
}

bool MidiInPort::open(int id)
{
  // dont do anything if opening same port
  if (id==devid)
    return true;
  else if (isActive())
    {
      Console::getInstance()->
	printError(T(">>> Error: Midi input device ") +
		   String(id) + T(" is currently active.\n"));
      return false;
    }
  if (device != NULL)
    {
      stop();
      delete device;
      devid=-1;
    }
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
      // update Preferences with current input port's name;
#ifdef GRACE
      StringArray devices = MidiInput::getDevices();
      Preferences* prefs=Preferences::getInstance();
      prefs->setStringProp(T("MidiInDevice"), devices[id]);
#endif
      return true;
    }
}

bool MidiInPort::open(String name) 
{
  StringArray devices = MidiInput::getDevices ();
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


int MidiInPort::performCommand(CommandID id, int data, String text)
{
  // lower eight bits of id encode command information
  CommandID cmd = CommandIDs::getCommand(id);
  int arg = CommandIDs::getCommandData(id);  
  int res=0;

  switch (cmd)
    {
    case CommandIDs::MidiInOpen :
      open(arg);
      break;
    case CommandIDs::MidiInTest :
      if (isActive(MidiInPort::TESTING))
        stopTestInput();
      else 
        startTestInput();
      break;
    case CommandIDs::MidiInRecord :
      if (isActive(RECORDING))
        stopRecordInput();
      else 
        startRecordInput();
      break;
    case CommandIDs::MidiInChannelMask :
      setChannelMask(data);
      break;
    case CommandIDs::MidiInMessageMask :
      setMessageMask(data);
      break;
    case CommandIDs::MidiInConfigure:
      /*** showMidiInDialog(); ***/
      break;
    case CommandIDs::MidiInHook :
      if ( isActive(SCHEMEHOOK) )
        stopSchemeInput();
      break;
    default:
      break;
    }
}

bool MidiInPort::isMessageActive(MidiMessage msg)
{
  // return true is message is allowed as input
  int data=msg.getRawData()[0];  
  int type=(data & 0xF0)>>4;  // msg opcode
  int chan=(data & 0xF);      // msg channel
  
  //std::cout << "type=" << type << "data=" << data << "\n";

  if ( isMessageActive(type) )
    if ( isChannelActive(chan) )
      return true;
    else
      return false;
  else
    return false;
}

// Message and Channel Masking

void MidiInPort::setChannelMask(int mask)
{
  channelMask=mask;
  /*** GracePreferences* prefs=GracePreferences::getInstance();
  prefs->setMidiInChannelMask(channelMask);
  ***/
}

void MidiInPort::setMessageMask(int mask)
{
  opcodeMask=mask;
  /*** GracePreferences* prefs=GracePreferences::getInstance();
  prefs->setMidiInChannelMask(opcodeMask);
  ***/
}

bool MidiInPort::isMessageActive(int opcode)
{
  if ((opcode >= MidiFlags::Off) && (opcode<= MidiFlags::Bend))
    {
      int mask=1<<(opcode-MidiFlags::Off);
      //std::cout << "opcode=" << opcode << " shift=" << (opcode-MidiFlags::Off) << " bit=" << mask << " opcodeMask=" << opcodeMask << "\n";
      return ((opcodeMask & mask) == mask);
    }
  else
    return false;
}

bool MidiInPort::isChannelActive(int chan)
{
  int mask=1<<(chan & 0xF);
  return ((channelMask & mask) == mask);
}

void MidiInPort::setChannelActive(int chan, bool active)
{
  int mask=1<<(chan & 0xF);
  if (active)
    channelMask |= mask;
  else
    channelMask &= ~mask;
  /***
  GracePreferences* prefs=GracePreferences::getInstance();
  prefs->setMidiInChannelMask(channelMask);
  ***/
}

void MidiInPort::setMessageActive(int op, bool active)
{
  // convert opcode into left-shifted mask
  int mask=1<<op-MidiFlags::Off;
  if (active)
    opcodeMask |= mask;
  else
    opcodeMask &= ~mask;
  /***
  GracePreferences* prefs=GracePreferences::getInstance();
  prefs->setMidiInMessageMask(opcodeMask);
  ***/
}

bool MidiInPort::isOpen(int id)
{
  if (device==NULL)
    return false;
  else if (id == -1) // asking if ANY device is open
    return true;
  else
    return (id == devid); // asking if specific dev is open
}

void MidiInPort::close(int id)
{
  if (device!=NULL)
    {
      delete device;
      device=NULL;
      devid=-1;
    }
}

bool MidiInPort::start(int mode) {
  if ( !isOpen() )
    {
      /***    console->printError(T(">>> Error: Midi input port is not open.\n"));
       ***/
    return false;
    }
  else if ( isActive() )
    {
      /*** console->printError(T(">>> Error: Midi input port already active.\n"));
       ***/
      return true;
    }
  // NOW DO WHATEVER SETUP IS NEEDED FOR NEW RUNMODE
  runmode=mode;
  // start the device
  device->start();
  return true;
}

void MidiInPort::stop() {
  if ( !isOpen() )
    {
      /*** console->printError(T(">>> Error: Midi input port is not open.\n"));
       ***/
      return;
    }
  else if ( !isActive() )
    {
      /*** console->printError(T(">>> Error: Midi input not active.\n"));
       ***/
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

void MidiInPort::handleIncomingMidiMessage(MidiInput *dev,
					   const MidiMessage &msg) 
{
  if (! isMessageActive(msg) )
    return;
  
  // AT THIS POINT CALL RECORDING CODE OR SCHEMEHOOK COE
  if ( isActive(SCHEMEHOOK) )
    {
      Scheme::getInstance()->midiin(msg);
    }

  if ( isActive(RECORDING) )
    {
      
    }
  
  if (trace)
    {
      printMidiMessageTrace(msg);
    }
}

void MidiInPort::printMidiMessageTrace (const MidiMessage &msg)
{
  String info;
  int chan=msg.getChannel();
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

  /***  console->postAsyncMessage(CommandIDs::ConsolePrintText,
			      info + T("\n"), 
			      true);
  ***/
}

void MidiInPort::handlePartialSysexMessage (MidiInput *dev,
					    const juce::uint8 *data, 
					    const int num, 
					    const double time) {
}

void MidiInPort::setTrace(bool n) {
  trace = n;
}

/***
void MidiInPort::showMidiInDialog()
{
  if ( opcodeMask == MidiFlags::AllOpcodesMask )
    {
      receiveComponent->allMessages->setToggleState(true, true);
    }
  else
    {
      receiveComponent->allMessages->setToggleState(false, false);
      receiveComponent->noteOff->
	setToggleState(isMessageActive(MidiFlags::Off), false);
      receiveComponent->noteOn->
	setToggleState(isMessageActive(MidiFlags::On), false);
      receiveComponent->aftertouch->
	setToggleState(isMessageActive(MidiFlags::Touch), false);
      receiveComponent->controlChange->
	setToggleState(isMessageActive(MidiFlags::Ctrl), false);
      receiveComponent->programChange->
	setToggleState(isMessageActive(MidiFlags::Prog), false);
      receiveComponent->channelPressure->
	setToggleState(isMessageActive(MidiFlags::Press), false);
      receiveComponent->pitchBend->
	setToggleState(isMessageActive(MidiFlags::Bend), false);
      //receiveComponent->activeSense->setToggleState(activeSense,false);
    }
  
  if (channelMask == MidiFlags::AllChannelsMask)
    {
      receiveComponent->allChannels->setToggleState(true, true);
    }
  else
    {
      for (int c=0; c<16; c++)
	receiveComponent->channels[c]->
	  setToggleState(isChannelActive(c), false);
    }
  

  DialogWindow::showModalDialog(T("Midi Receive Settings"), 
				receiveComponent,
				console, 
				Colour(0xffe5e5e5),
				true,
				false,
				false);
}
***/


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

void MidiOutPort::getInstrumentValues(Array<int>& vals)
{
  for (int chan=0; chan<16; chan++)
    vals.add(getInstrument(chan));
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

void MidiOutPort::sendInstruments() 
{
  if (! isOpen() )
    return;
  
  for (int c=0; c<16; c++)
    {
      //device->sendMessageNow( MidiMessage::programChange(c+1,programchanges[c]));
      MidiMessage* m=new MidiMessage((0xc0 | c), programchanges[c]);
      addNode(new MidiNode(m));
    }
}

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
    midifile->setSmpteTimeFormat(25, 40); // equals 1 millisecond resolution
  else
    midifile->setTicksPerQuarterNote(sequenceFile.qticks);

  MidiMessageSequence track0;
  track0.addEvent( sequenceFile.getTempoMessage(), 0);
  track0.addEvent( sequenceFile.getTimeSigMessage(), 0);
  track0.addEvent( sequenceFile.getKeySigMessage(), 0);

  // optional tuning
  Array<int> data;
  if (sequenceFile.bends)
    {
      getTuningValues(data);
      for (int c=0; c<data.size(); c++)
	track0.addEvent(MidiMessage((0xe0 | c), (data[c] & 127), 
				    ((data[c] >> 7) & 127)));
    }
  // optional program changes
  if (sequenceFile.insts)
    {
      data.clear();
      getInstrumentValues(data);
      for (int c=0; c<data.size(); c++)
	track0.addEvent(MidiMessage::programChange(c, data[c]));
    }  
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
  // optional clear after save
  //midifile->writeTo(outputStream) && sequenceFile.clear
  if (midifile->writeTo(outputStream)) 
    {
      Console::getInstance()->
	printOutput((T("Midifile: ") + sequenceFile.file.getFullPathName() +
		     T("\n")));
      captureSequence.clear();
    }
}

void MidiOutPort::exportSequence()
{
  /***  MidiFileExportComponent* dialog=new MidiFileExportComponent();
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
  int index;
  int count[6]={0,0,0,0,0,0};
  String prefix, indent, spacer, ending;
  String opener, closer;
  String outstr=String::empty;
  bool sending=false;
  switch (format) 
    {
    case ExportIDs::SalData :
      prefix=T("define variable export-%s = \n  {\n");
      indent=T("   "); 
      spacer=T(" ");
      opener=T("{");
      closer=T("}\n");
      ending=T("  }\n");
      break;
    case ExportIDs::LispData :
      prefix=T("(define midi-%s\n  '(\n");
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
    {
      bool sal=(format==ExportIDs::SalData);
      outstrs.add(((sal) ? T("define variable export-notes = \n  {\n")
		   : T ("(define export-notes\n  '(\n")));
      outstrs.add(((sal) ? T("define variable export-progs = \n  {\n")
		   : T ("(define export-progs\n  '(\n")));
      outstrs.add(((sal) ? T("define variable export-bends = \n  {\n")
		   : T ("(define export-bends\n  '(\n")));
      outstrs.add(((sal) ? T("define variable export-ctrls = \n  {\n")
		   : T ("(define export-ctrls\n  '(\n")));
      outstrs.add(((sal) ? T("define variable export-touch = \n  {\n")
		   : T ("(define export-touch\n  '(\n")));
      outstrs.add(((sal) ? T("define variable export-press = \n  {\n")
		   : T ("(define export-press\n  '(\n")));
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
      int chan=ev->message.getChannel();
      // skip if not channel message or not selected channel
      if ((chan == 0) || ((chans<17) && (chan != chans)))
	continue;
      chan--;  // getChannel() is 1 based!
      String line=String::empty;
      String time=String::formatted(T("%.03f"),
				    ((float)ev->message.getTimeStamp()));
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
	       << spacer << String(ev->message.getChannelPressureValue())
	       << spacer << String(chan)
	       << closer;
	  index=5;
	  count[index] += 1;
	}

      if (sending)
	outstr << line;
      else
	outstrs.set(index,outstrs[index]+line);
    }

  if (sending)
    {
      outstr = prefix + outstr + ending;
    }
  else
    {
      for (int i=0; i< 6; i++)
	if (count[i]>0)
	  outstr << outstrs[i] << ending;
    }

  if (dialog->consolebutton->getToggleState())
    console->printMessage(outstr);
  else if (dialog->clipboardbutton->getToggleState())
    SystemClipboard::copyTextToClipboard(outstr);
  else if (dialog->neweditorbutton->getToggleState() )
      new EditorWindow(ExportIDs::getTextID(format),
		       EditFlags::NeedSave, 
		       String::empty, 
		       T("Untitled"), 
		       outstr);


  delete dialog;
  ***/
}

