/*=======================================================================*
  Copyright (c) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify
  it under the terms of the Lisp Lesser Gnu Public License. The text
  of this agreement is available at http://www.cliki.net/LLGPL
 *=======================================================================*/

#ifndef MIDI_H
#define MIDI_H

#include <juce.h>

class MidiOutPort;
class ConsoleWindow;
class MidiReceiveComponent;
class MidiNode
{
 public:

  enum
  {
    MM_MESSAGE=1, 
    MM_OFF=0x8,
    MM_ON,
    MM_TOUCH,
    MM_CTRL,
    MM_PROG,
    MM_PRESS,
    MM_BEND
  } ;

  enum
  {
    DATA0=0,
    DATA1=1,
    DATA2=2
  };

  int type;
  double time;
  MidiMessage *message;
  Array<double> values;
  MidiOutPort *midiOutPort;
  MidiNode(int typ, double wait, double *vals=0, int num_vals=0) ;
  MidiNode(int typ, double wait, double chan, double data1);
  MidiNode(int typ, double wait, double chan, double data1, double data2);
  MidiNode(MidiMessage *msg);
  ~MidiNode();
  void process();
  void print();

  static const int indexToOpcode(int index)
  {
    return jlimit(0, 7, index)+MM_OFF;
  }
    
  static const int opcodeToIndex(int opcode)
  {
    return opcode-MM_OFF;
  }
    
  static const String opcodeToString(int opcode, bool pretty=false)
  {
    switch (opcode)
      {
      case MM_OFF: return (pretty) ? T("Note Off") : T("off");
      case MM_ON: return (pretty) ? T("Note On") : T("on");
      case MM_TOUCH: return (pretty) ? T("After Touch") : T("touch");
      case MM_CTRL: return (pretty) ? T("Control Change") : T("ctrl");
      case MM_PROG: return (pretty) ? T("Program Change") : T("prog");
      case MM_PRESS: return (pretty) ? T("Channel Pressure") : T("press");
      case MM_BEND: return (pretty) ? T("Pitch Bend") : T("bend");
      default: return T("<unknown midi opcode>");
      }
  }
  static const String indexToString(int index, bool pretty=false)
  {
    return opcodeToString(index+MM_OFF, pretty);
  }
  
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

class MidiFileInfo
{
 public:
  File file;    // output file
  int keysig;   // 1 to 15 (1=7Flats, 8=CMajor, 15=7Sharps
  bool ismsec;  // if true file data is in milliseconds
  int qticks;   // ticks per quarter (if ismsec==false)
  int tempo;    // beats per minute
  int tsig1;    // timesig numerator
  int tsig2;    // timesig denominator
  bool insts;   // include current program change assigments
  bool bends;   // include current tuning info
  bool clear;   // clear seq after save
  
 MidiFileInfo() 
   : file (File::nonexistent), 
    ismsec(false), qticks (480), tempo (60), 
    //    ismsec(true), qticks(1000), tempo (120), 
    keysig (8), tsig1 (4), tsig2 (4)
    {
    }      
  
  ~MidiFileInfo()
    {
    }
  
  MidiMessage getTempoMessage()
  {
    double micro=1000000.0*(60.0/(double)tempo);
    return MidiMessage::tempoMetaEvent((int)micro);
  }
  
  MidiMessage getTimeSigMessage()
  {
    return MidiMessage::timeSignatureMetaEvent(tsig1, tsig2);
  }
  
  // arrrg JUCE is missing keysig meta message!
  MidiMessage getKeySigMessage()
  {
    int sf=keysig-8;  // sf -7 to 7
    juce::uint8 d[8];
    d[0] = 0xff; // is meta event
    d[1] = 89;   // meta event opcode for keysig
    d[2] = 0x02; // meta event data length
    d[3] = sf;   // two's complement of -7 to 7
    d[4] = 0;    // major mode
    return MidiMessage(d, 5, 0.0); 
  }
};

class MidiTrack
{
 public:
  String name;
  MidiMessageSequence* sequence;
  bool selected;
  MidiTrack (String nam, const MidiMessageSequence& from)
    : name (String::empty), sequence (NULL), selected (false)
    {
      name=nam;
      sequence=new MidiMessageSequence(from);
    }

  ~MidiTrack()
    {
      if (sequence) delete sequence;
    }
  bool isSelected()
  { 
    return selected;
  }
  void isSelected(bool b)
  {
    selected=b;
  }
};

class MidiOutPort : public Thread //, public AsyncUpdater
{
 public:
  int devid;
  MidiOutput *device;
  ConsoleWindow *console;
  OwnedArray<MidiNode, CriticalSection> outputNodes;
  
  MidiOutPort( );
  ~MidiOutPort();

  bool open(int id);
  bool open(String name);
  bool isOpen(int id=-1) ;
  void close(int id=-1);

  void testOutput();
  bool isOutputQueueActive();

  void run();
  void clear();

  void addNode(MidiNode *n);
  MidiNodeComparator comparator;

  void sendNote(double wait, double dur, double key, double vel, double chan,
		bool toseq);
  void sendData(int type, double wait, double chan, double data1, double data2,
		bool toseq);
  void sendMessage(MidiMessage *message, bool toseq);

  /** called by node process to send a message out the device and
      (possibly) record it in the capture sequence **/

  void sendOut(MidiMessage& msg);


  // microtuning support
  static double channeltunings [16][16] ;
  int   microdivisions;  // divisions per semitone: 1-16
  double microincrement; // size of tuning's division (1.0=semitone)
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
  void getTuningValues(Array<int>& vals);

  // instruments
  int programchanges[16];
  int getInstrument(int chan);
  void getInstruments(Array<int>& vals);
  void setInstrument(int chan, int pc, bool send=false);
  bool isInstrumentChannel(int chan);
  void sendInstruments();
  void resetInstruments();
  void openInstrumentsDialog();

  // CLEAN THIS UP!!!!!

  // Midi Sequence Capturing
  CriticalSection lock;
  /** the (current) capturing mode **/
  int automode;
  bool isAutoMode(int mode);
  void setAutoMode(int mode);
  void performAutoScoreActions();
  void scoreComplete();
  int recordmode;
  int getRecordMode();
  void setRecordMode(int mode);
  bool isRecordMode(int mode);
  /** the capture sequence. time stamps are seconds **/
  MidiMessageSequence captureSequence;
  MidiFileInfo sequenceFile;
  /** time offset subtracted from MidiOut events that are recorded to
      the zero based capture sequence. when recoding begins the offset
      is intialized to -1 which causes the first recorded event to
      cache its true time stamp as the offset value. this value is
      then subtracted from the subsequent captured events. **/
  double recordTimeOffset;
  /** predicates to test the status of the capture sequence **/
  bool isSequenceEmpty();
  bool isSequenceData();
  /** operations on the capture sequence **/
  void resetRecordingStart();
  void clearSequence();
  void playSequence();
  void plotSequence();
  void printSequence();
  void setOutputFile(String name);
  void openFileSettingsDialog();

  void saveSequence(bool ask=false);


  /** versions of the capture sequence can be saved to and restored
      from an array of "tracks" **/
  OwnedArray<MidiTrack> tracks;
  int getNumTracks();
  String getTrackName(int index);
  void setTrackName(int index, String name);
  /** copies the capture seqence to a track. if index is -1 a new
      track is added otherwise the track at index is replaced by the
      capture sequence **/
  void copySequenceToTrack(int index=-1);
  /** copy contents of track back to sequence. if add is true the
      track is mixed into the current contents otherwise the seqence
      is replaced by track **/
  void copyTrackToSequence(int index, bool add=false, double shift=0.0);
  void renameTrack(int index);
  void deleteTrack(int index);
  void restoreTrack(int index);
  void mixTrack(int index);
  void importTracks();

  const PopupMenu getMidiOutMenu();
  const PopupMenu getMidiSeqMenu();

  // async messaging
  //  OwnedArray<AsyncMessage, CriticalSection> messages;
  //  void postAsyncMessage(int typ, String str);
  //  void postAsyncMessage(int typ, int dat);
  //  void handleAsyncUpdate();
  int performCommand(CommandID id, int data=0, String text=String::empty);

  juce_DeclareSingleton (MidiOutPort, true)
};

class MidiInPort : public MidiInputCallback
{
 private:
  enum {Stopped, Testing, Receiving}; // running mode
  int devid;
  MidiInput *device;
  bool tracing;
  int channelMask;
  int opcodeMask;
 public:
  static const int AllOpcodes = 0x7F;
  static const int AllChannels = 0xFFFF;
  MidiInPort();
  ~MidiInPort();
  bool open(int id);
  bool open(String name);
  bool isOpen(int id=-1);
  void close(int id=-1);

  int getChannelMask();
  void setChannelMask(int mask);
  bool isChannelActive(int chan);
  void toggleChannelActive(int chan);
  void setChannelActive(int chan, bool active);

  int getOpcodeMask();
  void setOpcodeMask(int mask);
  bool isOpcodeActive(int code, bool isop=false);
  void toggleOpcodeActive(int code);
  void setOpcodeActive(int code, bool active);

  bool isTracing();
  void setTracing(bool trace);
  void toggleTracing();

  bool isMessageActive(const MidiMessage& msg);
  void handleIncomingMidiMessage (MidiInput *dev, const MidiMessage &msg) ;
  void handlePartialSysexMessage (MidiInput *dev, const juce::uint8 *data, 
				  const int num, const double time);

  // Importing
  void openImportMidifileDialog();
  void importMidifile(File pathname,
		      int track=-1,
		      double start=0.0,
		      double endtime=-1.0, 
		      int chanmask=MidiFlags::AllChannelsMask, 
		      int opmask=MidiFlags::AllOpcodesMask,
		      int where=ExportIDs::ToConsole,
		      int format=ExportIDs::LispData);
  void exportMidiMessageSequence(MidiMessageSequence* seq,
				 String name,
				 double start,
				 double endtime,
				 int chanmask,
				 int opmask,
				 int where,
				 int format);
  bool readMidifile(File pathname, MidiFile& midifile);

  juce_DeclareSingleton (MidiInPort, true)
};

#endif
