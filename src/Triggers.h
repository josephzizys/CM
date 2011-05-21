/*=======================================================================*
   Copyright (C) 2009 Rick Taube.                                        
   This program is free software; you can redistribute it and/or modify  
   it under the terms of the Lisp Lesser Gnu Public License. The text of 
   this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#ifndef TRIGGERS_H
#define TRIGGERS_H

#include "Libraries.h"

class Trigger  : public Component,
  public SliderListener,
  public ButtonListener,
  public MidiKeyboardStateListener
{
public:
  Trigger(int typ);
  ~Trigger();
  void initFromXml(XmlElement* xml);
  String toXml();

  void paint (Graphics& g);
  void resized();
  void sliderValueChanged (Slider* sliderThatWasMoved);
  void buttonClicked (Button* buttonThatWasClicked);
  void handleNoteOn (MidiKeyboardState* state, int chan,
		     int key, float vel);
  void handleNoteOff (MidiKeyboardState* state, int chan, int key);

  void doTrigger();
  void configureTrigger();
  // private:
  StringArray vars; // pairs of strings: <var> <val> ...
  int triggertype;
  int valuetype;
  int height;

  TextButton* button;
  Slider* slider;
  TextButton* configure;
  TextButton* close;
  MidiKeyboardState keyboardState;
  MidiKeyboardComponent* keyboard;

};

#endif
