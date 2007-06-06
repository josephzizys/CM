/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

#include "Lisp.h"
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>


//==============================================================================
ConfigureLispView::ConfigureLispView ()
    : impgroup (0),
      sbclbutton (0),
      openmclbutton (0),
      clispbutton (0),
      custombutton (0),
      programlabel (0),
      argumentslabel (0),
      programbuffer (0),
      argsbuffer (0),
      congroup (0),
      hostlabel (0),
      hostbuffer (0),
      portlabel (0),
      portbuffer (0),
      timeslider (0),
      timelabel (0),
      magiclabel (0),
      magicbuffer (0)
{
    addAndMakeVisible (impgroup = new GroupComponent (T("impgroup"),
                                                      T("Implementation")));

    addAndMakeVisible (sbclbutton = new ToggleButton (T("sbclbutton")));
    sbclbutton->setButtonText (T("SBCL"));
    sbclbutton->addButtonListener (this);
    sbclbutton->setToggleState (true, false);

    addAndMakeVisible (openmclbutton = new ToggleButton (T("openmclbutton")));
    openmclbutton->setButtonText (T("OpenMCL"));
    openmclbutton->addButtonListener (this);

    addAndMakeVisible (clispbutton = new ToggleButton (T("clispbutton")));
    clispbutton->setButtonText (T("CLisp"));
    clispbutton->addButtonListener (this);

    addAndMakeVisible (custombutton = new ToggleButton (T("custombutton")));
    custombutton->setButtonText (T("Custom"));
    custombutton->addButtonListener (this);

    addAndMakeVisible (programlabel = new Label (T("programlabel"),
                                                 T("Lisp program:")));
    programlabel->setFont (Font (15.0000f, Font::plain));
    programlabel->setJustificationType (Justification::centredRight);
    programlabel->setEditable (false, false, false);
    programlabel->setColour (TextEditor::textColourId, Colours::black);
    programlabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (argumentslabel = new Label (T("argumentslabel"),
                                                   T("Arguments:")));
    argumentslabel->setFont (Font (15.0000f, Font::plain));
    argumentslabel->setJustificationType (Justification::centredRight);
    argumentslabel->setEditable (false, false, false);
    argumentslabel->setColour (TextEditor::textColourId, Colours::black);
    argumentslabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (programbuffer = new Label (T("programbuffer"),
                                                  T("/usr/local/bin/sbcl")));
    programbuffer->setFont (Font (15.0000f, Font::plain));
    programbuffer->setJustificationType (Justification::centredLeft);
    programbuffer->setEditable (false, false, false);
    programbuffer->setColour (Label::outlineColourId, Colours::black);
    programbuffer->setColour (TextEditor::textColourId, Colours::black);
    programbuffer->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (argsbuffer = new Label (T("argsbuffer"),
                                               String::empty));
    argsbuffer->setFont (Font (15.0000f, Font::plain));
    argsbuffer->setJustificationType (Justification::centredLeft);
    argsbuffer->setEditable (true, true, false);
    argsbuffer->setColour (Label::outlineColourId, Colours::black);
    argsbuffer->setColour (TextEditor::textColourId, Colours::black);
    argsbuffer->setColour (TextEditor::backgroundColourId, Colour (0x0));
    argsbuffer->addListener (this);

    addAndMakeVisible (congroup = new GroupComponent (T("congroup"),
                                                      T("Connection")));

    addAndMakeVisible (hostlabel = new Label (T("hostlabel"),
                                              T("Host:")));
    hostlabel->setFont (Font (15.0000f, Font::plain));
    hostlabel->setJustificationType (Justification::centredRight);
    hostlabel->setEditable (false, false, false);
    hostlabel->setColour (TextEditor::textColourId, Colours::black);
    hostlabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (hostbuffer = new Label (T("hostbuffer"),
                                               T("localhost")));
    hostbuffer->setFont (Font (15.0000f, Font::plain));
    hostbuffer->setJustificationType (Justification::centredLeft);
    hostbuffer->setEditable (false, false, false);
    hostbuffer->setColour (Label::outlineColourId, Colours::black);
    hostbuffer->setColour (TextEditor::textColourId, Colours::black);
    hostbuffer->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (portlabel = new Label (T("portlabel"),
                                              T("Port:")));
    portlabel->setFont (Font (15.0000f, Font::plain));
    portlabel->setJustificationType (Justification::centredRight);
    portlabel->setEditable (false, false, false);
    portlabel->setColour (TextEditor::textColourId, Colours::black);
    portlabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (portbuffer = new Label (T("portbuffer"),
                                               T("8000")));
    portbuffer->setFont (Font (15.0000f, Font::plain));
    portbuffer->setJustificationType (Justification::centredLeft);
    portbuffer->setEditable (true, true, false);
    portbuffer->setColour (Label::outlineColourId, Colours::black);
    portbuffer->setColour (TextEditor::textColourId, Colours::black);
    portbuffer->setColour (TextEditor::backgroundColourId, Colour (0x0));
    portbuffer->addListener (this);

    addAndMakeVisible (timeslider = new Slider (T("timeslider")));
    timeslider->setRange (5, 60, 1);
    timeslider->setSliderStyle (Slider::LinearHorizontal);
    timeslider->setTextBoxStyle (Slider::TextBoxLeft, false, 30, 20);
    timeslider->addListener (this);

    addAndMakeVisible (timelabel = new Label (T("timelabel"),
                                              T("Timeout:")));
    timelabel->setFont (Font (15.0000f, Font::plain));
    timelabel->setJustificationType (Justification::centredRight);
    timelabel->setEditable (false, false, false);
    timelabel->setColour (TextEditor::textColourId, Colours::black);
    timelabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (magiclabel = new Label (T("magiclabel"),
                                               T("Magic #:")));
    magiclabel->setFont (Font (15.0000f, Font::plain));
    magiclabel->setJustificationType (Justification::centredRight);
    magiclabel->setEditable (false, false, false);
    magiclabel->setColour (TextEditor::textColourId, Colours::black);
    magiclabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (magicbuffer = new Label (T("magicbuffer"),
                                                T("4071923244")));
    magicbuffer->setFont (Font (15.0000f, Font::plain));
    magicbuffer->setJustificationType (Justification::centredLeft);
    magicbuffer->setEditable (true, true, false);
    magicbuffer->setColour (Label::outlineColourId, Colours::black);
    magicbuffer->setColour (TextEditor::textColourId, Colours::black);
    magicbuffer->setColour (TextEditor::backgroundColourId, Colour (0x0));
    magicbuffer->addListener (this);

    setSize (408, 250);

}

ConfigureLispView::~ConfigureLispView()
{
    deleteAndZero (impgroup);
    deleteAndZero (sbclbutton);
    deleteAndZero (openmclbutton);
    deleteAndZero (clispbutton);
    deleteAndZero (custombutton);
    deleteAndZero (programlabel);
    deleteAndZero (argumentslabel);
    deleteAndZero (programbuffer);
    deleteAndZero (argsbuffer);
    deleteAndZero (congroup);
    deleteAndZero (hostlabel);
    deleteAndZero (hostbuffer);
    deleteAndZero (portlabel);
    deleteAndZero (portbuffer);
    deleteAndZero (timeslider);
    deleteAndZero (timelabel);
    deleteAndZero (magiclabel);
    deleteAndZero (magicbuffer);
}

//==============================================================================
void ConfigureLispView::paint (Graphics& g)
{
    g.fillAll (Colours::white);

}

void ConfigureLispView::resized()
{
    impgroup->setBounds (8, 120, 392, 120);
    sbclbutton->setBounds (16, 136, 90, 24);
    openmclbutton->setBounds (112, 136, 90, 24);
    clispbutton->setBounds (208, 136, 90, 24);
    custombutton->setBounds (304, 136, 88, 24);
    programlabel->setBounds (16, 168, 96, 24);
    argumentslabel->setBounds (16, 200, 96, 24);
    programbuffer->setBounds (120, 168, 264, 24);
    argsbuffer->setBounds (120, 200, 264, 24);
    congroup->setBounds (8, 8, 392, 96);
    hostlabel->setBounds (24, 32, 40, 24);
    hostbuffer->setBounds (72, 32, 152, 24);
    portlabel->setBounds (240, 32, 40, 24);
    portbuffer->setBounds (288, 32, 96, 24);
    timeslider->setBounds (96, 64, 104, 24);
    timelabel->setBounds (24, 64, 64, 24);
    magiclabel->setBounds (216, 64, 64, 24);
    magicbuffer->setBounds (288, 64, 96, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ConfigureLispView::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == sbclbutton)
    {
    }
    else if (buttonThatWasClicked == openmclbutton)
    {
    }
    else if (buttonThatWasClicked == clispbutton)
    {
    }
    else if (buttonThatWasClicked == custombutton)
    {
    }

}

void ConfigureLispView::labelTextChanged (Label* labelThatHasChanged)
{

    if (labelThatHasChanged == argsbuffer)
    {
    }
    else if (labelThatHasChanged == portbuffer)
    {
    }
    else if (labelThatHasChanged == magicbuffer)
    {

    }

}

void ConfigureLispView::sliderValueChanged (Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == timeslider)
    {
    }
}

//==============================================================================
//==============================================================================
//==============================================================================


ConfigureLispDialog::ConfigureLispDialog () 
  : DialogWindow( T("Configure Lisp"), Colours::white, true)
{
    setSize (408, 250);
    setContentComponent( config = new ConfigureLispView() );
    config->setVisible(true);
    setVisible(true);
}

ConfigureLispDialog::~ConfigureLispDialog() {
  delete config;
}

void ConfigureLispDialog::paint (Graphics& g) {
    g.fillAll (Colours::white);
}

void ConfigureLispDialog::resized() {
}


//==============================================================================
//==============================================================================
//==============================================================================



bool LispConnection::startLisp () {
  String command = lisp + T(" ") + args;
  char* const argv[4] = { "/bin/sh", "-c", (char*) (const char*) command, 0 };
  const int cpid = fork();

  printf("Starting lisp with: '%s'\n", command.toUTF8() );
  if (cpid == 0)  {
    // Child process
    if (execve(argv[0], argv, 0) < 0)
      exit (0);
  }
  else if (cpid < 0) {
    printf("Failed to start Lisp.\n");
    lpid=-1;
    return false;
  }
  else {
    // Parent process
    lpid=cpid;
    printf("Lisp started, pid=%d\n", lpid);
  }
  return true;
}

bool LispConnection::isLispRunning () {
  return (lpid != -1);
}

bool LispConnection::killLisp () {
  if ( isLispRunning() ) {
    kill(lpid, SIGKILL);
    lpid=-1;
    return true;
  }
  return false;
}

void LispConnection::connectionMade () {
  printf("Lisp connected.\n");
}

void LispConnection::connectionLost () {
  printf("Lisp connection lost.\n");
}

void LispConnection::messageReceived (const MemoryBlock &message) {
  printf("Message received!\n");
}
