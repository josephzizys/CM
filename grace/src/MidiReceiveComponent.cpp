/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision: 1543 $
// $Date: 2008-01-15 21:00:35 -0700 (Tue, 15 Jan 2008) $ 



#include "MidiReceiveComponent.h"
#include "Grace.h"

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
    groupComponent2 (0),
    //groupComponent3 (0),
    allChannels (0),
    channelIncrementor (0),
    singleChannel (0),
    //    hookField (0),
    //setHook (0),
    //clearHook (0),
    traceInput (0)//,
    //doneButton (0),
    //cancelButton (0)
{
  
  
  addAndMakeVisible (groupComponent = new GroupComponent (T("Receive Messages Group"),
							  T("Receive Messages")));
  
  addAndMakeVisible (allMessages = new ToggleButton (T("All Messages Button")));
  allMessages->setButtonText (T("All Messages"));
  allMessages->addButtonListener (this);
  
  addAndMakeVisible (noteOn = new ToggleButton (T("Note On Button")));
  noteOn->setButtonText (T("Note On"));
  noteOn->addButtonListener (this);
  
  addAndMakeVisible (noteOff = new ToggleButton (T("Note Off Button")));
  noteOff->setButtonText (T("Note Off"));
  noteOff->addButtonListener (this);
  
  addAndMakeVisible (controlChange = new ToggleButton (T("Control Change Button")));
  controlChange->setButtonText (T("Control Change"));
  controlChange->addButtonListener (this);
  
  addAndMakeVisible (programChange = new ToggleButton (T("Program Change Button")));
  programChange->setButtonText (T("Program Change"));
  programChange->addButtonListener (this);
  
  addAndMakeVisible (pitchBend = new ToggleButton (T("Pitch Bend Button")));
  pitchBend->setButtonText (T("Pitch Bend"));
  pitchBend->addButtonListener (this);
  
  addAndMakeVisible (aftertouch = new ToggleButton (T("Aftertouch Button")));
  aftertouch->setButtonText (T("Aftertouch"));
  aftertouch->addButtonListener (this);
  
  addAndMakeVisible (channelPressure = new ToggleButton (T("Channel Pressure Button")));
  channelPressure->setButtonText (T("Channel Pressure"));
  channelPressure->addButtonListener (this);
  
  addAndMakeVisible (groupComponent2 = new GroupComponent (T("Receive Channel Group"),
							   T("Receive Channel")));
  
  //  addAndMakeVisible (groupComponent3 = new GroupComponent (T("new group"),
  //		   T("Hook")));
  
  addAndMakeVisible (allChannels = new ToggleButton (T("All Channels Button")));
  allChannels->setButtonText (T("All Channels"));
  allChannels->setRadioGroupId (1);
  allChannels->addButtonListener (this);
  
  addAndMakeVisible (channelIncrementor = new Slider (T("Channel Incrementor")));
  channelIncrementor->setRange (1, 16, 1);
  channelIncrementor->setSliderStyle (Slider::IncDecButtons);
  channelIncrementor->setTextBoxStyle (Slider::TextBoxLeft, false, 40, 20);
  channelIncrementor->addListener (this);
  
  addAndMakeVisible (singleChannel = new ToggleButton (T("Single Channel Button")));
  singleChannel->setExplicitFocusOrder (1);
  singleChannel->setButtonText (T("Single Channel"));
  singleChannel->setRadioGroupId (1);
  singleChannel->addButtonListener (this);
  /*
  addAndMakeVisible (hookField = new TextEditor (T("Hook Field")));
  hookField->setMultiLine (false);
  hookField->setReturnKeyStartsNewLine (false);
  hookField->setReadOnly (false);
  hookField->setScrollbarsShown (true);
  hookField->setCaretVisible (true);
  hookField->setPopupMenuEnabled (true);
  hookField->setText (String::empty);
  
  addAndMakeVisible (setHook = new TextButton (T("Set Hook Button")));
  setHook->setButtonText (T("Set"));
  setHook->addButtonListener (this);
  
  addAndMakeVisible (clearHook = new TextButton (T("Clear Hook Button")));
  clearHook->setButtonText (T("Clear"));
  clearHook->addButtonListener (this);
  */
  addAndMakeVisible (traceInput = new ToggleButton (T("Trace Input Button")));
  
  traceInput->setButtonText (T("Trace Input"));
  traceInput->addButtonListener (this);
  /*
  addAndMakeVisible (doneButton = new TextButton (T("Done Button")));
  doneButton->setButtonText (T("Done"));
  doneButton->addButtonListener (this);
  
  addAndMakeVisible (cancelButton = new TextButton (T("Cancel Button")));
  cancelButton->setButtonText (T("Cancel"));
  cancelButton->addButtonListener (this);
  */
  setSize (480, 260);
  
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
  deleteAndZero (traceInput);
  //deleteAndZero (doneButton);
  //deleteAndZero (cancelButton);

}

//==============================================================================
void MidiReceiveComponent::paint (Graphics& g)
{
  g.fillAll (Colours::white);
  
}

void MidiReceiveComponent::resized()
{
  groupComponent->setBounds (16, 16, 224, 212);
  allMessages->setBounds (24, 32, 150, 24);
  noteOn->setBounds (40, 56, 150, 24);
  noteOff->setBounds (40, 80, 150, 24);
  controlChange->setBounds (40, 104, 150, 24);
  programChange->setBounds (40, 128, 150, 24);
  pitchBend->setBounds (40, 152, 150, 24);
  aftertouch->setBounds (40, 176, 150, 24);
  channelPressure->setBounds (40, 200, 150, 24);
  groupComponent2->setBounds (264, 16, 200, 104);
  //groupComponent3->setBounds (264, 120, 200, 96);
  allChannels->setBounds (272, 32, 150, 24);
  channelIncrementor->setBounds (304, 80, 112, 24);
  singleChannel->setBounds (272, 56, 150, 24);
  //hookField->setBounds (280, 144, 150, 24);
  //setHook->setBounds (280, 176, 71, 24);
  //clearHook->setBounds (360, 176, 72, 24);
  traceInput->setBounds (24, 224, 150, 24);
  //doneButton->setBounds (288, 224, 71, 24);
  //cancelButton->setBounds (376, 224, 71, 24);
}

void MidiReceiveComponent::buttonClicked (Button* buttonThatWasClicked)
{
  GraceApp* app = (GraceApp*)JUCEApplication::getInstance();
  
  if (buttonThatWasClicked == allMessages)
    {
      if(buttonThatWasClicked->getToggleState()) {
        noteOn->setToggleState(false, false);
        noteOff->setToggleState(false, false);
        controlChange->setToggleState(false, false);
        programChange->setToggleState(false, false);
        pitchBend->setToggleState(false, false);
        aftertouch->setToggleState(false, false);
        channelPressure->setToggleState(false, false);
	
	app->midiInPort->setNoteOn(true);
	app->midiInPort->setNoteOff(true);
	app->midiInPort->setControlChange(true);
	app->midiInPort->setProgramChange(true);
	app->midiInPort->setPitchBend(true);
	app->midiInPort->setAftertouch(true);
	app->midiInPort->setChannelPressure(true);
	
      }
	
    }
  else if (buttonThatWasClicked == noteOn)
    {
      
      allMessages->setToggleState(false, true);
      app->midiInPort->setNoteOn( buttonThatWasClicked->getToggleState() );
    }
  else if (buttonThatWasClicked == noteOff)
    {
      allMessages->setToggleState(false, true);
      app->midiInPort->setNoteOff( buttonThatWasClicked->getToggleState() );
    }
  else if (buttonThatWasClicked == controlChange)
    {
      allMessages->setToggleState(false, true);
      app->midiInPort->setControlChange( buttonThatWasClicked->getToggleState() );
    }
  else if (buttonThatWasClicked == programChange)
    {
      allMessages->setToggleState(false, true);
      app->midiInPort->setProgramChange( buttonThatWasClicked->getToggleState() );
    }
  else if (buttonThatWasClicked == pitchBend)
    {
      allMessages->setToggleState(false, true);
      app->midiInPort->setPitchBend( buttonThatWasClicked->getToggleState() );
    }
  else if (buttonThatWasClicked == aftertouch)
    {
      allMessages->setToggleState(false, true);
      app->midiInPort->setAftertouch( buttonThatWasClicked->getToggleState() );
    }
  
  else if (buttonThatWasClicked == channelPressure)
    {
      allMessages->setToggleState(false, true);
      app->midiInPort->setChannelPressure( buttonThatWasClicked->getToggleState() );
    }
  else if (buttonThatWasClicked == allChannels)
    {
      if( buttonThatWasClicked->getToggleState() ) {
        app->midiInPort->setAllChannels(true );

        channelIncrementor->setEnabled(false);
      }

    }
  else if (buttonThatWasClicked == singleChannel)
    {
      if( buttonThatWasClicked->getToggleState() ) {

        channelIncrementor->setEnabled(true);
        app->midiInPort->setSingleChannel( (int)channelIncrementor->getValue());
      }
    }
  /*
  else if (buttonThatWasClicked == setHook)
    {
    }
  else if (buttonThatWasClicked == clearHook)
    {

    }
  */
  else if (buttonThatWasClicked == traceInput)
    {
      app->midiInPort->setTrace( buttonThatWasClicked->getToggleState() );
    }
  /*
  else if (buttonThatWasClicked == doneButton)
    {
      
    }
  else if (buttonThatWasClicked == cancelButton)
    {
      
    }
  */

}

void MidiReceiveComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{

  GraceApp* app = (GraceApp*)JUCEApplication::getInstance();

  
  if (sliderThatWasMoved == channelIncrementor)
    {
      app->midiInPort->setSingleChannel( (int)channelIncrementor->getValue());
    }
}

