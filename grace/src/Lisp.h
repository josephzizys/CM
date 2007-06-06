/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

#ifndef __LISP__
#define __LISP__

#include "juce.h"

class LispConnection : public InterprocessConnection {
 public:
  enum LispFlavor {SBCL=1, OpenMCL, CLisp, Gauche, Guile, Custom};
  StringArray commands;
  String lisp;
  String args;
  int port;
  int lpid;
  String host;

 LispConnection () 
   : host (T("localhost")),
    port (8000),
    lpid (-1),
    lisp (T("/usr/local/bin/sbcl")),
    args (String::empty)
    {
    }

  ~LispConnection () { }

    bool startLisp();
    bool killLisp();
    bool isLispRunning();
    void connectionMade ();
    void connectionLost ();
    void messageReceived (const MemoryBlock &message);
};


class ConfigureLispView  : public Component,
                           public ButtonListener,
                           public LabelListener,
                           public SliderListener
{
public:

    ConfigureLispView ();
    ~ConfigureLispView();
    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void labelTextChanged (Label* labelThatHasChanged);
    void sliderValueChanged (Slider* sliderThatWasMoved);
    juce_UseDebuggingNewOperator

private:
    GroupComponent* impgroup;
    ToggleButton* sbclbutton;
    ToggleButton* openmclbutton;
    ToggleButton* clispbutton;
    ToggleButton* custombutton;
    Label* programlabel;
    Label* argumentslabel;
    Label* programbuffer;
    Label* argsbuffer;
    GroupComponent* congroup;
    Label* hostlabel;
    Label* hostbuffer;
    Label* portlabel;
    Label* portbuffer;
    Slider* timeslider;
    Label* timelabel;
    Label* magiclabel;
    Label* magicbuffer;

    ConfigureLispView (const ConfigureLispView&);
    const ConfigureLispView& operator= (const ConfigureLispView&);
};




class ConfigureLispDialog  : public DialogWindow
{
public:
    ConfigureLispDialog ();
    ~ConfigureLispDialog();
    void paint (Graphics& g);
    void resized();
    juce_UseDebuggingNewOperator

private:
    ConfigureLispView* config;
    ConfigureLispDialog (const ConfigureLispDialog&);
    const ConfigureLispDialog& operator= (const ConfigureLispDialog&);
};





#endif

