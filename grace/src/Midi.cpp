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
      midiport->output->
	sendMessageNow( MidiMessage::noteOn((int)values[ONCHAN]+1, 
					    (int)values[ONKEY], 
					    vel));
    }
    else
      midiport->output->
	sendMessageNow( MidiMessage::noteOff( (int)values[ONCHAN]+1,
					      (int)values[ONKEY]) );
    break;
  case NODEOFF:
    midiport->output->
      sendMessageNow( MidiMessage::noteOff( (int)values[OFFCHAN]+1,
					    (int)values[OFFKEY]) );
    break;
  case NODEPROG :
    midiport->output->
      sendMessageNow( MidiMessage::programChange( (int)values[PROGCHAN]+1,
						  (int)values[PROGNUM]) );
    break;
  case NODECTRL :
    midiport->output->
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

MidiPort::MidiPort(String name, String out, String in)
  : Thread(name) , output(0), input(0), outdev (-1), indev (-1)
{	
  if ( out != String::empty )
    openOutput(out);
  if ( in != String::empty )
    openInput(in);
}

MidiPort::~MidiPort()
{
  if ( output != NULL ) delete output;
  if ( input != NULL ) delete input;
}

void MidiPort::openOutput(String name) {
  StringArray devices = MidiOutput::getDevices ();
  int id=-1;
  for (int i=0;i<devices.size();i++)
    if (devices[i] == name) {
      id=i;
      break;
    }
  if ( id == -1 )
    ((GraceApp *)GraceApp::getInstance())->getConsole()
      ->printWarning(T("Warning: Midi output device ") + 
		     name + T(" does not exist.\n"));
  else
    openOutput(id);
}

void MidiPort::openOutput(int id) {
  // dont do anything if opening same port
  if ( id == outdev ) return;
  // delete current port. IS THIS CORRECT?
  if ( output != NULL ) {
    delete output;
    outdev=-1;
  }
  output = MidiOutput::openDevice(id);
  if ( output == NULL )
    ((GraceApp *)GraceApp::getInstance())->getConsole()
      ->printError(T(">>> Error: Failed to open midi output (dev=") + 
		   String(id) + T(").\n"));
  else
    outdev=id;
  printf("Midi out: dev=%d\n", id);
}

bool MidiPort::isOpenOutput(int id) {
  if ( output == NULL )
    return false;
  else if ( id == -1)
    return true;
  else
    return (id == outdev);
}

String MidiPort::getDeviceName(int id, bool isOut) {
  StringArray devices = (isOut) ? MidiOutput::getDevices() :
    MidiInput::getDevices();
  for (int i=0; i<devices.size(); i++)
    if ( i == id )
      return devices[i];
  return String::empty;
}

//
// output queue 
//

void MidiPort::run() {
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
void MidiPort::run() {
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

bool MidiPort::isOutputQueueActive() { 
  outputNodes.lockArray(); 
  int n=outputNodes.size();
  outputNodes.unlockArray();
  return (n > 0);
}

void MidiPort::clear()
{
  outputNodes.lockArray();
  outputNodes.clear();
  // avoid hanging notes
  if ( output != 0 )
    for ( int i=0; i< 16; i++ )
      output->sendMessageNow( MidiMessage::allSoundOff(i) );
  outputNodes.unlockArray();
}

void MidiPort::addNode(MidiNode *n) {
  outputNodes.lockArray();
  n->midiport = this;
  n->time += Time::getMillisecondCounterHiRes();
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

void MidiPort::sendNote(double wait, double dur, float key, float vel, float chan) {
  // dont do anything if there is no open output port!
  if ( output == NULL ) return;
  addNode( new MidiNode(MidiNode::NODEON, wait, chan, key, vel) );
  addNode( new MidiNode(MidiNode::NODEOFF, wait+dur, chan, key) );
}

void MidiPort::sendOn(double wait, float key, float vel, float chan) {
  // dont do anything if there is no open output port!
  if ( output == NULL ) return;
  addNode( new MidiNode(MidiNode::NODEON, wait, chan, key, vel) );
}

void MidiPort::sendOff(double wait, float key, float vel, float chan) {
  // dont do anything if there is no open output port!
  if ( output == NULL ) return;
  addNode( new MidiNode(MidiNode::NODEOFF, wait, chan, key) );
}

void MidiPort::sendProg(double wait, float prog, float chan) {
  // dont do anything if there is no open output port!
  if ( output == NULL ) return;
  addNode( new MidiNode(MidiNode::NODEPROG, wait, chan, prog) );
}

void MidiPort::sendCtrl(double wait, float ctrl, float val, float chan) {
  // dont do anything if there is no open output port!
  if ( output == NULL ) return;
  addNode( new MidiNode(MidiNode::NODECTRL, wait, chan, ctrl, val) );
}

void MidiPort::testMidiOutput () {
  // Tobias Kunze's little testing algo from cm 1.4
  double time = 0;
  for (int x=0; x<12; x++) {
    // vals[0]=keynum, [1]=velocity, [2]=channel
    float key = x + (12 * (3 + Random::getSystemRandom().nextInt(5) )) ;
    float vel = 32.0 + Random::getSystemRandom().nextInt(64);
    float dur = ((( 2 + Random::getSystemRandom().nextInt(6)) ^ 2) * 30.0);
    sendNote(time, dur, key, vel, 0.0);
    time += ((Random::getSystemRandom().nextInt(5) ^ 2) * 30.0);
  }
}


