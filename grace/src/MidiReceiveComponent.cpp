/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision: 1543 $
// $Date: 2008-01-15 21:00:35 -0700 (Tue, 15 Jan 2008) $ 



#include "MidiReceiveComponent.h"
#include "Enumerations.h"
#include "Grace.h"
#include <iostream>

//==============================================================================
MidiReceiveComponent::MidiReceiveComponent ()
  : groupComponent (0),
    allMessages (0),
    noteOn (0),
    noteOff (0),
    controlChange (0),
    programChange (0),
    pitchBend (0),
    aftertouch (0),
    channelPressure(0),
    //    activeSense (0),
    groupComponent2 (0),

    allChannels (0),
    channelIncrementor (0),
    singleChannel (0)
{
  addAndMakeVisible (groupComponent = 
		     new GroupComponent (T(""), T("Receive Messages")));
  addAndMakeVisible (allMessages = new ToggleButton (T("All Messages Button")));
  allMessages->setButtonText (T("All Messages"));
  allMessages->addButtonListener (this);
  
  addAndMakeVisible (noteOn = new ToggleButton (T("Note On Button")));
  noteOn->setButtonText (T("Note On"));
  noteOn->addButtonListener (this);
  
  addAndMakeVisible (noteOff = new ToggleButton (T("Note Off Button")));
  noteOff->setButtonText (T("Note Off"));
  noteOff->addButtonListener (this);
  
  addAndMakeVisible (controlChange = 
		     new ToggleButton (T("Control Change Button")));
  controlChange->setButtonText (T("Control Change"));
  controlChange->addButtonListener (this);
  
  addAndMakeVisible (programChange = 
		     new ToggleButton (T("Program Change Button")));
  programChange->setButtonText (T("Program Change"));
  programChange->addButtonListener (this);
  
  addAndMakeVisible (pitchBend = new ToggleButton (T("Pitch Bend Button")));
  pitchBend->setButtonText (T("Pitch Bend"));
  pitchBend->addButtonListener (this);
  
  addAndMakeVisible (aftertouch = new ToggleButton (T("Aftertouch Button")));
  aftertouch->setButtonText (T("Aftertouch"));
  aftertouch->addButtonListener (this);
  
  addAndMakeVisible (channelPressure = 
		     new ToggleButton (T("Channel Pressure Button")));
  channelPressure->setButtonText (T("Channel Pressure"));
  channelPressure->addButtonListener (this);
  
  //  addAndMakeVisible (activeSense = new ToggleButton (T("Active Sensing")));
  //  activeSense->setButtonText (T("Active Sensing"));
  //  activeSense->addButtonListener (this);

  // CHANNELS

  addAndMakeVisible (groupComponent2 = 
		     new GroupComponent (T(""), T("Receive Channels")));
  
  addAndMakeVisible (allChannels = new ToggleButton (T("")));
  allChannels->setButtonText (T("All Channels"));
  allChannels->addButtonListener (this);
  for (int c=0; c<16; c++)
    {
      channels.add(new ToggleButton( T("")));
      addAndMakeVisible(channels[c]);
      channels[c]->setButtonText( String(c) );
      channels[c]->addButtonListener(this);
    }
  setSize(480, 272);
}

MidiReceiveComponent::~MidiReceiveComponent()
{
  
  deleteAndZero (groupComponent);
  deleteAndZero (allMessages);
  deleteAndZero (noteOn);
  deleteAndZero (noteOff);
  deleteAndZero (controlChange);
  deleteAndZero (programChange);
  deleteAndZero (pitchBend);
  deleteAndZero (aftertouch);
  deleteAndZero (channelPressure);
  deleteAndZero (groupComponent2);
  //  deleteAndZero (groupComponent3);
  deleteAndZero (allChannels);
  deleteAndZero (channelIncrementor);
  deleteAndZero (singleChannel);
  //deleteAndZero (hookField);
  //deleteAndZero (setHook);
  //deleteAndZero (clearHook);
  //  deleteAndZero (activeSense);
  //deleteAndZero (doneButton);
  //deleteAndZero (cancelButton);
  channels.clear();
}

//==============================================================================
//void MidiReceiveComponent::paint (Graphics& g)
//{
//  g.fillAll (Colours::white);
//}

void MidiReceiveComponent::resized()
{
  groupComponent->setBounds(16, 16, 216, 240);
  allMessages->setBounds (24, 32, 150, 24);
  noteOn->setBounds (40, 56, 150, 24);
  noteOff->setBounds (40, 80, 150, 24);
  controlChange->setBounds (40, 104, 150, 24);
  programChange->setBounds (40, 128, 150, 24);
  pitchBend->setBounds (40, 152, 150, 24);
  aftertouch->setBounds (40, 176, 150, 24);
  channelPressure->setBounds (40, 200, 150, 24);
  //  activeSense->setBounds (40, 224, 150, 24);

  groupComponent2->setBounds(248, 16, 216, 240);
  allChannels->setBounds(248+8, 32, 150, 24);
  int x=248;
  int y=32+24;
  for (int c=0; c<8; c++)
    {
      channels[c]->setBounds(x+24, y, 48, 24);
      channels[c+8]->setBounds(x+108, y, 48, 24);      
      y+=24;
    }
}

void MidiReceiveComponent::buttonClicked (Button* button)
{
  GraceApp* app = (GraceApp*)JUCEApplication::getInstance();
  bool tog=button->getToggleState();

  if ( button == allMessages )
  {
    noteOn->setToggleState(tog, false);
    noteOff->setToggleState(tog, false);
    controlChange->setToggleState(tog, false);
    programChange->setToggleState(tog, false);
    pitchBend->setToggleState(tog, false);
    aftertouch->setToggleState(tog, false);
    channelPressure->setToggleState(tog, false);

    app->midiInPort->setMessageActive(MidiFlags::Off, tog);
    app->midiInPort->setMessageActive(MidiFlags::On, tog);
    app->midiInPort->setMessageActive(MidiFlags::Touch, tog);
    app->midiInPort->setMessageActive(MidiFlags::Ctrl, tog);
    app->midiInPort->setMessageActive(MidiFlags::Prog, tog);
    app->midiInPort->setMessageActive(MidiFlags::Press, tog);
    app->midiInPort->setMessageActive(MidiFlags::Bend, tog);
  }
  else if (button == noteOn)
    {
      allMessages->setToggleState(false, false);
      app->midiInPort->setMessageActive(MidiFlags::On, tog);
    }
  else if (button == noteOff)
    {
      allMessages->setToggleState(false, false);
      app->midiInPort->setMessageActive(MidiFlags::Off, tog);
    }
  else if (button == controlChange)
    {
      allMessages->setToggleState(false, false);
      app->midiInPort->setMessageActive(MidiFlags::Ctrl, tog);
    }
  else if (button == programChange)
    {
      allMessages->setToggleState(false, false);
      app->midiInPort->setMessageActive(MidiFlags::Prog, tog);
    }
  else if (button == pitchBend)
    {
      allMessages->setToggleState(false, false);
      app->midiInPort->setMessageActive(MidiFlags::Bend, tog);
    }
  else if (button == aftertouch)
    {
      allMessages->setToggleState(false, false);
      app->midiInPort->setMessageActive(MidiFlags::Touch, tog);
    }
  else if (button == channelPressure)
    {
      allMessages->setToggleState(false, false);
      app->midiInPort->setMessageActive(MidiFlags::Press, tog);
    }
  else if (button == allChannels)
    {
      for (int c=0; c<16; c++)
	{
	  channels[c]->setToggleState(tog, false);
	  app->midiInPort->setChannelActive(c, tog);	  
	}
    }
  else 
    {
      allChannels->setToggleState(false, false);
      for (int c=0; c<16; c++)
	{
	  if (button == channels[c])
	    {
	      channels[c]->setToggleState(tog, false);
	      app->midiInPort->setChannelActive(c, tog);	  
	      break;
	    }
	}
    }
}

void MidiReceiveComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{

}

