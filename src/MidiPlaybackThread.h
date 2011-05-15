/*=======================================================================*
  Copyright (c) 2011 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify
  it under the terms of the Lisp Lesser Gnu Public License. The text
  of this agreement is available at http://www.cliki.net/LLGPL
 *=======================================================================*/

#ifndef MIDI_PLAYBACK_THREAD_H
#define MIDI_PLAYBACK_THREAD_H

#include <juce.h>
#include "Transport.h"


/** A thread that plays midi messages. Calls its MidiMessageSource
    repeatedly to fill a playback queue and the sends the queued
    messages to a MidiOut port at the appropriate time. **/

class MidiPlaybackThread : public Thread
{

 public:

/** The PlaybackPosition maintains the thread's playback time and
    index. The PlaybackPosition's time is managed by the thread but
    the MidiMessageSource is responsible for incrementing the playback
    index if it wants to use it. Playback stops once the position's
    time is greater than its endtime or the index is equal or greater
    than its length. Use setPlaybackLimits() to establish these
    limits. **/

  class PlaybackPosition
  {

  public:

    double time;
    int index;
    double endtime;  // no more source callbacks when time > endtime
    int length;      // no more source callbacks when index >= length
    int srate;       // times per second thread queries for notes from source
  
  PlaybackPosition()
    : time (0.0),
      index (0),
      endtime (0.0),
      length (0),
      srate (100) // by default source callback every 10ms
      {
      }
  
    ~PlaybackPosition()
    {
    }
  
    /** Returns true if position's index is equal or greater than its
        length or its tme is greater than its endtime. **/

    bool isAtEnd()
    {
      return ((index >= length) || (time > endtime));
    }
  
    /** Sets the maximum midinote time and the total number of events to
        play and optionally the number of times per second the source is
        called. **/

    void setRange(double endTime, int numEvents, int sampRate)
    {
      endtime=endTime;
      length=numEvents;
      srate=sampRate;
      std::cout << "PlaybackPosition: endtime=" << endtime << ", length=" << length << ", srate=" << srate << "\n";
    }
  
    /** Resets the position back to its start values **/

    void rewind()
    {
      time=0.0;
      index=0;
    }
  
    /** Moves the position's source index to a new value. Note that this
        index is not used by the thread at all, its only useful to the
        caller.  The caller is responsible for incrementing the index
        during the callback. **/

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

  /** A queue of time-sorted midi messages that the MidiMessageSource
       adds to using addMessage(). The queue automatically sorts
       itself and insures that noteOffs are placed before noteOns with
       the same time stamp. Note that once you add a message to this
       queue you no longer own it and the message will get deleteed
       automtatically once its sent out the MidiOut port. **/

  class MidiMessageQueue : public OwnedArray<MidiMessage>
  {

  public:

     MidiMessageQueue() {}

    ~MidiMessageQueue(){}

   /** Adds a midi message to the playback queue at the the proper
       position according to its time stamp and message type. Message
       is deleted after it has been sent out the midi port. **/
  
    void addMessage(MidiMessage* msg)
    {
      addSorted(*this, msg);
    }

    /** Comparator keeps the queue in time sorted order. Puts note
        offs before anyting else at the same time stamp to stop note
        clipping, other messages are added at the last possible
        position for their time. **/

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
  };

  /** A class for receiving callbacks from a MidiPlaybackThread to add
    midi messages to the thread's midi message queue. **/

  class MidiMessageSource
  {
  public:
    /** Called by the MidiPlaybackThread to add midi messages to the
        MidiMessageQueue for the PlaybackPosition's current time and
        index. Use the queue's addMessage() method to add midi
        messages at or later than the current time. The position's
        time is automatically incremented by the MidiPlaybackThread
        but the caller is responsible for incrementing the play index
        if it is being used. The callback will not be invoked after
        the position's time or index values exceed the limits
        established by setRange().
    **/
    virtual void addMidiPlaybackMessages(MidiMessageQueue& queue, PlaybackPosition& position) = 0;
  };

  MidiMessageQueue messages;
  PlaybackPosition position;

 private:

  MidiMessageSource& source;
  MidiOutput* port;
  Transport* transport;
  CriticalSection pblock;
  bool paused;
  double beat;
  double delta;
  int index;

 public:

  /** A thread that implements realtime midi playback for a source of
      midi messages. Midisource is the source that will provide midi
      messages whenever its addMidiPlaybackMessage() method is
      called. Midiout is the MIDI device to send MIDI messages to. Trans is
      an optional transport object. If provided the thread will
      periodically message the transport during playback to update its
      position slider. **/

 MidiPlaybackThread(MidiMessageSource& midisource, MidiOutput* midiout=0, Transport* transprt=0)
   : Thread(T("Midi Playback Thread")),
    paused(true),
    beat(0.0),
    delta(0.01),
    index(0),
    port(midiout),
    transport (transprt),
    source(midisource)
    {   
    }
  
  ~MidiPlaybackThread()
  {
    messages.clear();
    std::cout << "deleted MidiPlaybackThread\n";
  }

  /** Sets the playback position's maximum time and the number of
      events to play. addMidiPlaybackMessages() callback will not be
      called after either limit has been reached. **/

  void setPlaybackLimits(double endtime, int length, double srate=100)
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

  /** Returns true if the thread is currently paused. **/

  bool isPaused()
  {
    ScopedLock mylock(pblock);
    return paused;
  }

  /** Returns true if the thread is currently playing. **/

  bool isPlaying()
  {
    return !isPaused();
  }

  /** A wrapper that starts the thread running if it is paused. **/

  void play()
  {
    if (isPaused())
      setPaused(false);
  }

  /** A wrapper that pauses the thread if it is running. **/

  void pause()
  {
    if (isPlaying())
      setPaused(true);
  }

  /** Puts the thread in pause or play mode. **/

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

  /** the run method for midi playback. Runs at a specified rate per
      second, each time calling the source's addMidiPlaybackMessages()
      to get any Midi message to play and then playing the messages
      for the current time.  Thread can be pasued and resumed using
      the thread's play() and pause() methods. If a transport is
      associate with the thread then the transport will be messaged
      periodically to update its slider position to reflect the
      current playback time. **/

  void run ()
  {
    int transpcounter=0;  // send transport updates at a slower rate than the playback rate
    while (!threadShouldExit())
    {
      // lock thread variables and copy to locals
      pblock.enter();
      bool ispaused=paused;
      bool isatend=position.isAtEnd();
      int  pending=messages.size();
      // delta time to wait before next run 
      double delta = 1.0/position.srate;
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
        // if position has reached its limits then dont
        // try to get any more messages from the source
        if (isatend)
        {
          // we are at the end of the source but we may still have
          // pending messages in the queue if future ones were added
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
          source.addMidiPlaybackMessages(messages, position);
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
            transport->sendMessage(Transport::SetPlaybackPosition, pos, 0, false);
          else
            transpcounter = ((transpcounter + 1) % 10);
        }
        //if (position.time <= position.endtime)
        wait(1000*delta);
      }
    }
    std::cout << "exiting MidiPlaybackThread\n";
  }
  
  /** Internal function sends a message out the port. **/

  void processMessage(MidiMessage* msg)
  {
    //MidiOutput* port=MidiOutPort::getInstance()->device;
    if (port)
      port->sendMessageNow(*msg);
    if (1)
      printMidiMessage(*msg);
    delete msg; // DELETE MESSAGE AFTER USE
  }
  
  /** Internal function that sends an allNotesOff if we pause or move
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
