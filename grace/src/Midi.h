#ifndef __MIDI__
#define __MIDI__

#include <juce.h>
#include <chicken.h>
#include "Console.h"

class MidiPort;

class MidiNode {
 public:
  enum {NODEON=1, NODEOFF, NODEPROG, NODECTRL} ;
  enum {ONCHAN=0, ONKEY=1, ONVEL=2,
	OFFCHAN=0, OFFKEY=1, OFFVEL=2,
	PROGCHAN=0, PROGNUM=1,
	CTRLCHAN=0, CTRLNUM=1, CTRLVAL=2};
  enum {ONSIZE=3, OFFSIZE=3, PROGSIZE=2, CTRLSIZE=3};
  int type;
  double time;
  int num;
  Array<float> values;
  MidiPort *midiport;
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

class MidiPort : public Thread
{
public:
  int indev, outdev;
  MidiOutput *output;
  MidiInput *input;
  OwnedArray<MidiNode, CriticalSection> outputNodes;
  
  MidiPort(String name, String out=String::empty, String in=String::empty);
  ~MidiPort();

  void openOutput(int id);
  void openOutput(String name);
  bool isOpenOutput(int id=-1) ;
  void testMidiOutput();

  void openInput(int id) {return;}
  void openInput(String name) {return;}
  bool isOpenInput(int id=-1) {return false;}

  bool isOutputQueueActive();
  String getDeviceName(int id, bool isOut=true);

  void run();
  void clear();

  void addNode(MidiNode *n);
  MidiNodeComparator comparator;

  void sendNote(double wait, double dur, float key, float vel, float chan);
  void sendOn(double wait, float key, float vel, float chan);
  void sendOff(double wait, float key, float vel, float chan);
  void sendProg(double wait, float prog, float chan);
  void sendCtrl(double wait, float ctrl, float val, float chan);
};

#endif
