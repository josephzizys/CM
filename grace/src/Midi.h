/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision: 1495 $
// $Date: 2007-11-25 19:01:22 -0600 (Sun, 25 Nov 2007) $ 

#ifndef __MIDI__
#define __MIDI__

#include <juce.h>
#include <chicken.h>
#include "Console.h"
#include "MidiReceiveComponent.h"
class MidiOutPort;
class ConsoleWindow;
class MidiReceiveComponent;
class MidiNode {
 public:

  enum {MM_MESSAGE=1, 
	MM_OFF=0x8, MM_ON, MM_TOUCH, MM_CTRL, MM_PROG, MM_PRESS, MM_BEND
  } ;
  enum {DATA0=0, DATA1=1, DATA2=2};
  int type;
  double time;
  MidiMessage *message;
  Array<float> values;
  MidiOutPort *midiOutPort;
  MidiNode(int typ, double wait, float *vals=0, int num_vals=0) ;		
  MidiNode(int typ, double wait, float chan, float data1);
  MidiNode(int typ, double wait, float chan, float data1, float data2);
  MidiNode(MidiMessage *msg);
  ~MidiNode();
  void process();
  void print();
};

class MidiNodeComparator
{
public:
  static int compareElements(MidiNode* e1, MidiNode* e2)
  {
    if( e1->time <= e2->time)
      return -1;
    else 
      return 1;
  }
};


/*
       addAndMakeVisible (depthSlider = new Slider (T("toolbar depth:")));
        depthSlider->setRange (10.0, 200.0, 1.0);
        depthSlider->setValue (50, false);
        depthSlider->setSliderStyle (Slider::LinearHorizontal);
        depthSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
        depthSlider->addListener (this);
        depthSlider->setBounds (80, 210, 300, 22);
        (new Label (depthSlider->getName(), depthSlider->getName()))->attachToComponent (depthSlider, false);

*/

class MidiFileInfo
{
 public:
  File file;  // output file name
  int keysig; // 1 to 15 (1=7Flats, 8=CMajor, 15=7Sharps
  int tempo;  // beats per minute
  int tsig1;  // timesig numerator
  int tsig2;  // timesig denominator
  
 MidiFileInfo() 
   : file (File::nonexistent), keysig (8), tempo (120), tsig1(4), tsig2(4)
    {
    }      
  
  ~MidiFileInfo() {}
  
  MidiMessage getTempoMessage()
  {
    double micro=1000000.0*(60.0/(double)tempo);
    return MidiMessage::tempoMetaEvent((int)micro);
  }

  MidiMessage getTimeSigMessage()
  {
    return MidiMessage::timeSignatureMetaEvent(tsig1, tsig2);
  }

  MidiMessage getKeySigMessage()
  {
    int sf=keysig-8;  // sf -7 to 7
    //	if (sf<0) sf+=256;
    // WTF? juce is missing a keysig constructor...
    juce::uint8 d[8];
    d[0] = 0xff; // is meta event
    d[1] = 89;   // meta event opcode for keysig
    d[2] = 0x02; // meta event data length
    d[3] = sf;   // two's complement of -7 to 7
    d[4] = 0;    // major mode
    return MidiMessage(d, 5, 0.0); 
  }
};


class MidiOutPort : public Thread 
{
 public:
  int devid;
  MidiOutput *device;
  ConsoleWindow *console;
  OwnedArray<MidiNode, CriticalSection> outputNodes;
  
  MidiOutPort(ConsoleWindow *win);
  ~MidiOutPort();

  void open(int id);
  void open(String name);
  bool isOpen(int id=-1) ;
  void testMidiOutput();
  bool isOutputQueueActive();

  void run();
  void clear();

  void addNode(MidiNode *n);
  MidiNodeComparator comparator;

  void sendNote(double wait, double dur, float key, float vel, float chan);
  void sendData(int type, double wait, float chan, float data1, float data2);
  void sendMessage(MidiMessage *message);

  // microtuning support
  static float channeltunings [16][16] ;
  int   microdivisions;  // divisions per semitone: 1-16
  float microincrement; // size of tuning's division (1.0=semitone)
  int   microchancount; // number of addressable channels in tuning
  int   microchanblock; // total number of channels used by tuning
  bool  avoiddrumtrack; // if true then avoid channel 9
  int   pitchbendwidth;
  StringArray tuningnames ; // string name for each tuning
  int getTuning() ;
  void setTuning(int tune, bool send=true) ;
  bool isTuning(int tune);
  String getTuningName(int tune);
  int getTuningDivisions(int tune); // number of division
  int getTuningChannels(int tune); // number of addressable chans
  int getTuningChannelsClaimed(int tune); // total chans used
  bool avoidDrumTrack();
  void setAvoidDrumTrack(bool b);
  int getPitchBendWidth();
  void setPitchBendWidth(int w);
  void sendTuning();

  // instruments
  int programchanges[16];
  int getInstrument(int chan);
  void setInstrument(int chan, int pc, bool send=false);
  bool isInstrumentChannel(int chan);
  void sendInstruments();
  void resetInstruments();
  void showInstrumentsWindow();
  
  void sendOut(MidiMessage& msg);
  //for recording output
  MidiMessageSequence captureSequence;
  MidiFileInfo sequenceFile;
  bool isSequenceEmpty();
  bool isSequenceData();
  bool recording;
  double recordTimeOffset;
  void setRecording(bool r);
  bool isRecording();
  void clearSequence();
  void writeSequence(bool ask=false);
};

class MidiInPort : public MidiInputCallback {
 public:
  ConsoleWindow *console;
  int devid;
  MidiInput *device;

  MidiReceiveComponent *receiveComponent;

  enum {STOPPED, TESTING, SCHEMEHOOK, RECORDING}; // running mode
  int runmode;
  bool trace;
  
  int singleChannel;
  bool allChannels;
  bool noteOn;
  bool noteOff;
  bool controlChange;
  bool programChange;
  bool pitchBend;
  bool aftertouch;
  bool channelPressure;
  bool activeSense;

  //C_word schemehook;
  MidiInPort(ConsoleWindow *win);
  ~MidiInPort();
  void open(int id);
  void open(String name);
  bool isOpen(int id=-1);
  bool start(int mode);
  void stop();
  bool isActive(int mode=-1);
  
  //hook is set in SchemeThread and only passing mask and filt
  // can use these to determine whether an INHOOK node needs to be
  // created in Scheme Thread
  void startSchemeInput();
  void stopSchemeInput() ;
  
  bool isTracing();
  void setTracing(bool t);
  void startTestInput();
  void stopTestInput();
  void startRecordInput() ;
  void stopRecordInput() ;
  bool isChannelActive(int chan);
  void isMessageWanted(int m);
  void handleIncomingMidiMessage (MidiInput *dev, const MidiMessage &msg) ;
  void handlePartialSysexMessage (MidiInput *dev, const juce::uint8 *data, 
				  const int num, const double time);
  
  void setNoteOn(bool n);
  void setNoteOff(bool n);
  void setControlChange(bool n);
  void setProgramChange(bool n);
  void setPitchBend(bool n);
  void setAftertouch(bool n);
  void setChannelPressure(bool n);
  void setSingleChannel(int n);
  void setAllChannels(bool n);
  void setTrace(bool n);
  void setActiveSense(bool n);
  void printMidiMessageTrace (const MidiMessage &msg);
  void showMidiInDialog();
};
#endif
