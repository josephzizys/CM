#include "Audio.h"
#include "Grace.h"


AudioMidiWindow::AudioMidiWindow ()
  : DocumentWindow(T("Audio Settings"), Colours::white, DocumentWindow::allButtons, true)
{
  //audioDevice is global in Grace.h
  GraceApp * app = (GraceApp*)JUCEApplication::getInstance();

  AudioDeviceSelectorComponent selectorControl(app->audioManager, 2, 16, 
					       2, 16, true);
  setContentComponent(&selectorControl);
  setResizable(true, true);
  setSize(400, 400);
  setTopLeftPosition(100, 100);
  setVisible (true);
}

AudioMidiWindow::~AudioMidiWindow()
{
}

void AudioMidiWindow::closeButtonPressed()
{
  delete this;
}
