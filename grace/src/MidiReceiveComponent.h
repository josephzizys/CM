/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision: 1543 $
// $Date: 2008-01-15 21:00:35 -0700 (Tue, 15 Jan 2008) $ 


#ifndef _MIDIRECEIVECOMPONENT_
#define _MIDIRECEIVECOMPONENT_

#include <juce.h>
#include "Midi.h"

class MidiReceiveComponent  : public Component,
                              public ButtonListener,
                              public SliderListener
{
public:
    //==============================================================================
    MidiReceiveComponent ();
    ~MidiReceiveComponent();

    //==============================================================================
    //    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void sliderValueChanged (Slider* sliderThatWasMoved);
    GroupComponent* groupComponent;
    ToggleButton* allMessages;
    ToggleButton* noteOn;
    ToggleButton* noteOff;
    ToggleButton* controlChange;
    ToggleButton* programChange;
    ToggleButton* pitchBend;
    ToggleButton* aftertouch;
    ToggleButton* channelPressure;
    ToggleButton* activeSense;
    GroupComponent* groupComponent2;
    //GroupComponent* groupComponent3;
    ToggleButton* allChannels;
    Slider* channelIncrementor;
    ToggleButton* singleChannel;
    //TextEditor* hookField;
    //TextButton* setHook;
    //TextButton* clearHook;
    //TextButton* doneButton;
    //TextButton* cancelButton;
    juce_UseDebuggingNewOperator
 private:
    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    MidiReceiveComponent (const MidiReceiveComponent&);
    const MidiReceiveComponent& operator= (const MidiReceiveComponent&);
};
#endif   //
