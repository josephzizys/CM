/*=======================================================================*
  Copyright (c) 2010 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify
  it under the terms of the Lisp Lesser Gnu Public License. The text
  of this agreement is available at http://www.cliki.net/LLGPL
 *=======================================================================*/

#ifndef MIDI_PLAYBACK_THREAD_H
#define MIDI_PLAYBACK_THREAD_H

#include <juce.h>
#include "Transport.h"

/** a queue of time-sorted midi messages. Your MidiPlaybackSource
    should use the addMessage() method to add midi messages to the
    queue for playback. the queue automatically sorts itself and
    insures that noteOffs are placed before noteOns with the same time
    stamp. **/

class MidiPlaybackQueue : public OwnedArray<MidiMessage>
{
 public: 

  MidiPlaybackQueue() {}

  ~MidiPlaybackQueue(){}

  /** queue comparator ensures noteOffs appear before anything else at
      the same time stamp. this is to avoid note clipping in the case
      where we have repeated notes with duration = rhythm. in this
      case you want to make sure that second note's NoteOn message is
      added to the queue AFTER the first note's NoteOff message, eg:

      time:    0      1       1       2
      good:    N1(on) N1(off) N2(on)  N2(off)
      bad:     N1(on) N2(on)  N1(off) N2(off)   **/

  static int compareElements(MidiMessage* a, MidiMessage* b)
  {
    if (a->getTimeStamp() < b->getTimeStamp())
      return -1;
    else if (b->getTimeStamp() < a->getTimeStamp())
      return 1;
    else
    {
      if (a->isNoteOff())
      {
        if (b->isNoteOff())
          return 0;
        else 
          return -1;
      }
      else
      {
        if (b->isNoteOff())
          return 1;
        else
          return 0;
      }
    }
  }
  
  /** adds a midi message to the playback queue.  message will be
       inserted in the queue the proper time stamp. message is deleted
       after its been sent out the midi port. **/
  
  void addMessage(MidiMessage* msg)
  {
    addSorted(*this, msg);
  }
  
};

/** a class that represents the midi thread's playback position. a
    position has two fields time (double) and index (int). the user
    sets the max ranges for both of these fields using the setRange()
    function and is responsible for incrementing the position's index
    and time values in the getPlaybackMessages callback.
**/

class MidiPlaybackPosition
{
 public:
  double time;
  int index;
  double endtime;  // no more notes after this time
  int length;      // no more notes at or after this index
  int srate;       // times per second thread queries for notes from source
  
 MidiPlaybackPosition()
   : time (0.0),
    index (0),
    endtime (0.0),
    length (0),
    srate (100) // by default source it queried evey 10mss
    {
    }
  
  ~MidiPlaybackPosition()
  {
  }
  
  /** returns true if the index is equal or greater than the length or
      the tme is beyond the endtime. **/

  bool isAtEnd()
  {
    return ((index >= length) || (time > endtime));
  }
  
  /** sets the maximum note time and total number of events to
      play **/

  void setRange(double endTime, int numEvents, int sampRate)
  {
    endtime=endTime;
    length=numEvents;
    srate=sampRate;
    std::cout << "PlaybackPosition: endtime=" << endtime << ", length=" << length << ", srate=" << srate << "\n";
  }
  
  /** moves the position back to the start **/

  void rewind()
  {
    time=0.0;
    index=0;
  }
  
  /** moves the user's source position (index) to a new position **/
  void setSourcePosition(int pos)
  {
    index=pos;
  }
  
  void moveTo(double nextTime, int nextIndex)
  {
    time = nextTime;
    index = nextIndex;
  }

};

/** A class that provides midi events for a MidiPlaybackThread to
    play. The source's getMidiPlaybackMessages callback is passed the
    playback queue and the current playback position and can add midi
    messages using the queue's addMessage() methods for the given time
    and index. future message can also be added to the queue. Callback
    is responsible for incrementing the position's time and
    (optionally) index for the next call. the callback will not be
    called once the position is past its range. **/

class MidiPlaybackSource
{
 public:
  virtual void getMidiPlaybackMessages(MidiPlaybackQueue& queue, MidiPlaybackPosition& position) = 0;
};

/** A thread that plays midi messages in real time out the midi
    port. calls the midi source's getMidiPlaybackMessages method to
    add playback messages. the thread will send position updates to a
    transport if one is provided.  **/

class MidiPlaybackThread : public Thread
{

 private:

  MidiPlaybackSource& source;
  MidiOutput* port;
  Transport* transport;
  CriticalSection pblock;
  bool paused;
  double beat;
  double delta;
  int index;

 public:

  MidiPlaybackQueue messages;

  MidiPlaybackPosition position;

  /** create a midi playback thread. src is the source of midi events
      that will be polled by getMidiPlaybackMessages. transport is an
      optional transport object whose state the thread will update if
      provided. **/

 MidiPlaybackThread(MidiPlaybackSource& src, MidiOutput* midiout=0, Transport* trans=0)
    : Thread(T("Midi Playback Thread")),
    paused(true),
    beat(0.0),
    delta(0.01),
    index(0),
    port(midiout),
    transport (trans),
    source(src)
    {
      
    }
  
  ~MidiPlaybackThread()
  {
    messages.clear();
    std::cout << "deleted MidiPlaybackThread\n";
  }

  /** sets the playback position's end time and number of events to
      play.  the getMidiPlaybackMessages callback will not happen
      after this end time or number has been reached **/

  void setPlaybackRange(double endtime, int length, double srate=100)
  {
    ScopedLock mylock(pblock);
    position.setRange(endtime, length, srate);
  }

  // FIXME start should be in srate quanta
  void setPlaybackPosition(double start, int index)
  {
    ScopedLock mylock(pblock);
    position.moveTo(start, index);
  }

  void setPlaybackPort(MidiOutput* midiport)
  {
    ScopedLock mylock(pblock);
    port=midiport;
  }

  void clear()
  {
    messages.clear();
  }

  /** returns true if the thread is currently paused **/

  bool isPaused()
  {
    ScopedLock mylock(pblock);
    return paused;
  }

  /** returns true if the thread is currently playing **/

  bool isPlaying()
  {
    return !isPaused();
  }

  /**  if called with true then pause the thread otherwise start the
       thread running.  has no effect if the state you specify is the
       same as the thread's current state.**/

  void play()
  {
    if (isPaused())
      setPaused(false);
  }

  void pause()
  {
    if (isPlaying())
    setPaused(true);
  }

  void setPaused(bool pause)
  {
    ScopedLock mylock(pblock);
    if (paused != pause) 
    {
      paused=pause;
      if (!paused) // wake up thread if we have stopped pausing
        notify();
      else
      {
        // send allNotesOff if pausing with messages still in queue.
        // not sure if we need to lock the queue to check its size...
        if (messages.size() > 0)
          sendAllNotesOff();
      }
    }
  }

 private:

  void run ()
  {
    int transpcounter=0;  // send transport updates at a slower rate than the playback rate
    while (!threadShouldExit())
    {
      // lock before testing variables other threads can affect
      pblock.enter();
      bool ispaused=paused;
      bool isatend=position.isAtEnd();
      int  pending=messages.size();
      double delta = 1.0/position.srate; // amount of time to wait between calls to getMidiPlayBackMessages
      pblock.exit();

      // if playback is paused then block until user unblocks us
      if (ispaused)
      {
        std::cout << "playback thread is paused\n";
        transpcounter=0;
        wait(-1);
      }
      else
      {
        double pos=0;
        // if our position is past the end of the sequence then dont
        // try to get any more messages from the source
        if (isatend)
        {
          // we are at the end of the source but we may still have
          // pending messages in the queue if the used spooled them
          // into the queue
          if (pending==0) 
          {
            // nothing in the queue, rewind the position and autopause
            pblock.enter();
            paused=true;
            position.rewind(); 
            pblock.exit();
            // display the transport in its pause mode, then continue
            // directly to the top of the loop for the thread pause
            if (transport)
              transport->sendMessage(Transport::SetPausing, 0.0, 0, false);
            continue;
          }
          else
          {
            // if we are here then the playback position is beyond the
            // end of the source there are still pending messages left
            // in the queue to process
            pblock.enter();
            double now=position.time;
            pos=now/position.endtime;
            MidiMessage* msg=0; 
            while (msg=messages.getFirst())
            {
              if (msg->getTimeStamp() <= now)              
              {
                messages.remove(0, false); // pop message off queue
                processMessage(msg);       // process message
              }
              else
              {
                break;
              }
            }
            position.time += delta;
            pblock.exit();
          }
        }
        else
        {
          // if we are here then the playback position is still valid
          // so we call source function to add messages to the queue
          // and then process the messages for the current time
          pblock.enter();
          double now=position.time;
          pos=now/position.endtime;
          // call sources's routine to get more messages
          source.getMidiPlaybackMessages(messages, position);
          MidiMessage* msg=messages.getFirst();          
          while (msg && msg->getTimeStamp() <= now)
          {
            messages.remove(0, false); // pop message off queue
            processMessage(msg);       // send message out port
            msg=messages.getFirst();   // increment to next
          }
          position.time += delta;      // increment time
          pblock.exit();
        }
        // update position of transport's slider at 1/10 the playback rate
        if (transport)
        {
          if (transpcounter==0)
            // update the transport's position slider without triggering its action
            transport->sendMessage(Transport::SetSliderPosition, pos, 0, false);
          else
            transpcounter = ((transpcounter + 1) % 10);
        }
        //if (position.time <= position.endtime)
        wait(1000*delta);
      }
    }
    std::cout << "exiting MidiPlaybackThread\n";
  }
  
  /** internal function sends a message out the port. if we are
      running dynamically then delete the message after we send it out
      the port **/

  void processMessage(MidiMessage* msg)
  {
    //MidiOutput* port=MidiOutPort::getInstance()->device;
    if (port)
      port->sendMessageNow(*msg);
    if (1)
      printMidiMessage(*msg);
    delete msg; // DELETE MESSAGE AFTER USE
  }
  
  /**  internal function that sends an allNotesOff if we pause or move
       the transport with pending messages in the queue. **/

  void sendAllNotesOff()
  {
    //MidiOutput* port=MidiOutPort::getInstance()->device;
    if (port)
    {
      std::cout << "sending AllNotesOff...\n";
      for(int i = 1; i <= 16; i++)
      {
        port->sendMessageNow(MidiMessage::allSoundOff(i));
      }
    }
  }

  static const void printMidiMessage(MidiMessage& msg)
  {
    int op=(msg.getRawData()[0] & 0xf0)>>4;
    int ch=msg.getChannel()-1;
    int d1=msg.getRawData()[1] & 0x7f;
    int d2=(msg.getRawDataSize() > 2) ? (msg.getRawData()[2] & 0x7f) : 0;
    if (op==9 && d2==0) op=8; // show as note off
    String text=String(msg.getTimeStamp());
    text << T(" op=") << String(op) << " ch=" << String(ch) << T(" d1=") << String(d1) << T(" d2=") << String(d2);
    std::cout << text.toUTF8() << "\n" << std::flush;
  }
  
};

#endif
