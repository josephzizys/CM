#ifndef __MIDI__
#define __MIDI__


#include <juce.h>
#include <chicken.h>
#include "Console.h"

class MidiOutPort;
class ConsoleWindow;

class MidiNode {
 public:
  enum {NODEON=1, NODEOFF, NODEPROG, NODECTRL, NODEBEND} ;
  enum {ONCHAN=0, ONKEY=1, ONVEL=2,
	OFFCHAN=0, OFFKEY=1, OFFVEL=2,
	PROGCHAN=0, PROGNUM=1,
	CTRLCHAN=0, CTRLNUM=1, CTRLVAL=2,
        BENDCHAN=0, BENDVAL=1};
  enum {ONSIZE=3, OFFSIZE=3, PROGSIZE=2, CTRLSIZE=3, BENDSIZE=2};
  int type;
  double time;
  int num;
  Array<float> values;
  MidiOutPort *midiOutPort;
  MidiNode(int typ, double wait, float *vals=0, int num_vals=0) ;		
  MidiNode(int typ, double wait, float data1, float data2);
  MidiNode(int typ, double wait, float data1, float data2, float data3);
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

class MidiOutPort : public Thread {
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
  void sendOn(double wait, float key, float vel, float chan);
  void sendOff(double wait, float key, float vel, float chan);
  void sendProg(double wait, float prog, float chan);
  void sendCtrl(double wait, float ctrl, float val, float chan);
  void sendBend(double wait, float val, float chan);

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
};

class MidiInPort : public MidiInputCallback {
 public:
  ConsoleWindow *console;
  int devid;
  MidiInput *device;
  unsigned int channelmask;
  unsigned int messagefilt;
  enum {STOPPED, TESTING, SCHEMEHOOK, RECORDING}; // running mode
  int runmode;
  bool trace;
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
  void startSchemeInput(unsigned int chanmask=0, 
			unsigned int msgfilt=0);
  void stopSchemeInput() ;
  unsigned int getChannelMask();
  unsigned int getMessageFilter();
  void setChannelMask(unsigned int m);
  void setMessageFilter(unsigned int f);
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

};
#endif
