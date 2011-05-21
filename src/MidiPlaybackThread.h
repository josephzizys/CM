/*=======================================================================*
  Copyright (c) 2011 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify
  it under the terms of the Lisp Lesser Gnu Public License. The text
  of this agreement is available at http://www.cliki.net/LLGPL
 *=======================================================================*/

#ifndef MIDI_PLAYBACK_THREAD_H
#define MIDI_PLAYBACK_THREAD_H


#ifndef COMMONMUSIC
#include "Libraries.h"
#endif

#include "Transport.h"

/** A thread that plays midi messages out a midi port in real
    time. Calls its MidiMessageSource every tick per beat to fill a
    playback queue and then sends the queued messages to a MidiOut
    port at the appropriate real time. To use a MidiPlaybackThread
    first create it and then set its playback limit using
    setPlaybackLimit(). Call play() to start the thread running,
    pause() to pause it, and setPlaybackPosition() and setTempo() to
    modify playback as its running. For easy controls add a Transport
    object so that the user control midi playback with buttons and
    sliders. **/

class MidiPlaybackThread : public juce::Thread
{

 public:

/** Holds the thread's current playback time in beats and an index
    value that the caller can use as a running position into its
    sequence of midi data. The PlaybackPostion is owned by the thread
    but the caller can safely read/write the beat, index, and stop
    values within its addMessagesToQueue() function. Playback
    automatically stops as soon as the position's beat is greater than
    its endbeat, or the index is equal to its length, or the stop flag
    value is set to true. The beat value is incremeted by the thread,
    the caller is responsible for incrementing the playback index if
    it is using it. **/

  class PlaybackPosition
  {

  public:

    /** The thread's current playback position expressed in 'beat
        time' without regard to tempo. The beat is incremented a
        tick's worth of beat time on each iteration. See
        setTicksPerBeat() for more information. **/

    double beat;

    /** A position index for the caller to use if it wants to maintain
        a running position in its sequence of data while its
        addMessagesToQueue() is repeatedly called during
        playback. Caller is reponsible for incrementing the index if
        it is using it. Playback will stop once this index is equal to
        or greater than the position's length value (and the length is
        greater than 0.) **/

    int index;

    /** Specifies the ending time for playback expressed in
        beats. Playback is automatically stopped as soon as the
        position's beat exceeds this value. **/

    double endbeat; 

    /** Specifies the maximum number of positions the source has in
        its sequenence of midi data. if length is greater than 0 then
        playback is stopped as soon as the index is equal to or
        exceeeds this value. **/

    int length;

    /** If true playback will stop. **/

    bool stop;

    /** Internal PlaybackPosition constructor */

  PlaybackPosition()
    : beat (0.0),
      index (0),
      endbeat (0.0),
      length (0),
      stop (false)
      {
      }
  
    /** Internal PlaybackPosition destructor */

    ~PlaybackPosition()
    {
    }
  
    /** Internal function returns true if stop is true, or the
        postion's beat is greater than its endbeat, or its index is
        not less than the length and length is greater than 0. **/

    bool isAtEnd()
    {
      return (stop || (beat > endbeat) || ((length > 0) && (index >= length)) );
    }
    
    /** Internal function resets the position back to its starting
        values. **/

    void rewind()
    {
      beat=0.0;
      index=0;
      stop=false;
    }
  
  };

  /** A queue of time sorted midi messages. The queue automatically
      sorts itself according to the time stamps of the added messages
      but insures that noteOffs are placed before noteOns with the
      same time stamp. The queue is owned by the thread but is passed
      to the caller's addMessageToQueue function so that the caller
      can add messages to it using the addMessage() method.  Once
      messages are added they are owned by the queue and are
      automatically deleted once they have been sent out the MidiOut
      port. **/

  class MidiMessageQueue : public juce::OwnedArray<juce::MidiMessage>
  {

  public:

    /** Internal MidiMessageQueue constuctor. **/

     MidiMessageQueue(){}

    /** Internal MidiMessageQueue destructor. **/

    ~MidiMessageQueue(){}

   /** Adds a MidiMessage to the playback queue. Once messages are
       added they are owned by the queue and will be automaticall
       deleted once they are sent out the midi port. Added messages
       are inserted at the appopriate position in the queue according
       to the message time stamp. Time stamps are in beats, not
       seconds, and this beat time is automatically scaled by a tempo
       factor during playback. Once a message has been sent out the
       midiport it is deleted by the thread. **/
  
    void addMessage(juce::MidiMessage* msg)
    {
      addSorted(*this, msg);
    }

    /** Comparator keeps the queue in time sorted order but places
        note offs before anything else at the same time stamp to avoid
        note clipping. All other message types are added at the last
        possible position for their time. **/

    static int compareElements(juce::MidiMessage* a, juce::MidiMessage* b)
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

  /** A class to receive callbacks from a MidiPlaybackThread to add
      midi message to its playback queue. Messages should be added at
      or later than the current beat time of the thread. **/

  class MidiMessageSource
  {
  public:

    /** Called by the MidiPlaybackThread at every tick to add midi
        messages to the thread's MidiMessageQueue. Time stamps in the
        added messages should be at or later than the current time
        value in PlaybackPosition.beat.  PlaybackPosition.index is a
        read/write variable the caller can use to maintain a running
        index into its midi data -- the caller is responsible for
        incremeting the index if it is using it. callbacks to
        addMidiPlaybackMessages() cease once the position's beat or
        index values exceed the playback limits established by the
        thread's setPlaybackLimits() method. **/

    virtual void addMidiPlaybackMessages(MidiMessageQueue& queue, PlaybackPosition& position) = 0;

  };

 private:

  MidiMessageQueue messages; // midi message queue, time is in beats
  PlaybackPosition position; // playback position with current beat and user index
  MidiMessageSource* source; // called every tick to add messages to the queue
  juce::MidiOutput* port;          // the midi output port to receive messages
  Transport* transport;      // transport to update while running
  juce::CriticalSection pblock; // playback lock for accessing thread state
  bool paused;               // true if thread is paused false if its running
  double tempo;              // metronome speed of beat
  int ticks;                 // number of times per beat the source is called

 public:

  /** Creates a MidiPlaybackThread that plays midi messages out a midi
      port in real time. Midisource is the source that will provide
      midi messages. TicksPerBeat is the number of times per beat the
      source will called to add its messages. BeatsPerMinute is the
      initial metronome tempo for playback. Midiout is the MIDI device
      to send MIDI messages to. If Transport is not null the thread
      will periodically send messages during playback to update its
      sliders an buttons. **/

 MidiPlaybackThread(MidiMessageSource* midiSource, int ticksPerBeat, double beatsPerMinute=60.0, juce::MidiOutput* midiOut=NULL, Transport* transprt=NULL)
   : juce::Thread (juce::String("Midi Playback Thread")),
    source (midiSource),
    tempo (beatsPerMinute),
    ticks (ticksPerBeat),
    port (midiOut),
    transport (transprt),
    paused (true)
    {   
    }
  
  ~MidiPlaybackThread()
  {
    messages.clear();
    std::cout << "deleted MidiPlaybackThread\n";
  }

  /** Sets the maximum beat and index range for playback. playback
      will autopause when beat>endBeat or index is >= length. **/

  void setPlaybackLimit(double endbeat, int length=0)
  {
    juce::ScopedLock mylock(pblock);
    position.endbeat=endbeat;
    position.length=length;
  }

  /** Sets the playback position to the specified beat. To update the
      position's index as well specify an index value 0 or larger. **/

  void setPlaybackPosition(double beat, int index=-1)
  {
    juce::ScopedLock mylock(pblock);
    position.beat=beat;
    if (index>-1)
      position.index=index;      
  }

  /** Sets the midi output port that will receive MIDI messages from
      the thread. **/

  void setMidiOutputPort(juce::MidiOutput* midiport)
  {
    juce::ScopedLock mylock(pblock);
    port=midiport;
  }

  /** Sets the thread's playback tempo in beats per minute. This value
      is used to convert playback beat time into seconds. **/

  void setTempo(double bpm)
  {
    juce::ScopedLock mylock(pblock);
    if (bpm<=0) bpm=60;
    tempo=bpm;
  }

  /** Specifies the the number of times per beat that the thread calls
      its MidiMessageSource to add midi messages to the
      queue. TicksPerBeat is converted into a time delta (a tick) that
      is scaled by the thread's tempo value to determine the actual
      amount of time the thread waits between interations. **/

  void setTicksPerBeat(double tpb)
  {
    juce::ScopedLock mylock(pblock);
    if (tpb<1) tpb=1;
    ticks=tpb;
  }

  /** Returns true if the thread is currently paused. **/

  bool isPaused()
  {
    juce::ScopedLock mylock(pblock);
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
    juce::ScopedLock mylock(pblock);
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

  /** Clears the queue of pending messages. Don't call this unless the
      thread is currently paused or you will pobably have dangling
      midi notes to deal with!  **/

  void clear()
  {
    messages.clear();
  }

 private:

  /** Main loop for the MidiPlaybackTread. On each iteration it calls
      the source's addMidiPlaybackMessages() to get more Midi message
      to play and then plays them out the midi port. The run loop can
      be paused and resumed using the thread's play() and pause()
      methods. If a transport is associate with the thread then the
      transport will be messaged periodically to update its slider
      position to reflect the current playback beat. **/

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
      double bpm=tempo;
      // 'ticks' is the number of ticks per beat and 'tick' is the
      // wait time expressed in beats, without regard to tempo
      double tick = 1.0/ticks;
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
            double now=position.beat;
            pos=now/position.endbeat;
            juce::MidiMessage* msg=0; 
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
            position.beat += tick;
            pblock.exit();
          }
        }
        else
        {
          // if we are here then the playback position is still valid
          // so we call source function to add messages to the queue
          // and then process the messages for the current beat
          pblock.enter();
          double now=position.beat;
          pos=now/position.endbeat;
          // call sources's routine to get more messages
          source->addMidiPlaybackMessages(messages, position);
          juce::MidiMessage* msg=messages.getFirst();          
          while (msg && msg->getTimeStamp() <= now)
          {
            messages.remove(0, false); // pop message off queue
            processMessage(msg);       // send message out port
            msg=messages.getFirst();   // increment to next
          }
          position.beat += tick;      // increment beat
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
        // calculate the amount of time to wait between iterations
        // by converting ticks to milliseconds at the current tempo
        // e.g  wait(1000 * tick * (60/bpm));
        wait((int)(60000*(tick/bpm)));
      }
    }
    // send all notes off if user closed the window without stopping
    // the playback!

    // FIXME: if this thread was killed indirectly by user quitting
    // the app during playback the midi port might already be deleted!! 
    /*
    if (!paused)
      sendAllNotesOff();
    */
    std::cout << "exiting MidiPlaybackThread\n";
  }
  
  /** Internal function that sends a message out the midi port. **/

  void processMessage(juce::MidiMessage* msg)
  {
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
    if (port)
    {
      std::cout << "sending AllNotesOff...\n";
      for(int i = 1; i <= 16; i++)
      {
        port->sendMessageNow(juce::MidiMessage::allSoundOff(i));
      }
    }
  }

  static const void printMidiMessage(juce::MidiMessage& msg)
  {
    int op=(msg.getRawData()[0] & 0xf0)>>4;
    int ch=msg.getChannel()-1;
    int d1=msg.getRawData()[1] & 0x7f;
    int d2=(msg.getRawDataSize() > 2) ? (msg.getRawData()[2] & 0x7f) : 0;
    if (op==9 && d2==0) op=8; // show as note off
    juce::String text=juce::String(msg.getTimeStamp());
    text << juce::String(" op=") << juce::String(op) << " ch=" << juce::String(ch) << juce::String(" d1=") << juce::String(d1) << juce::String(" d2=") << juce::String(d2);

    const char* wtf = text.toUTF8();
    std::cout << wtf << "\n" << std::flush;
  }
  
};

#endif
