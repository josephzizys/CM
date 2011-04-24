/*=======================================================================*
Copyright (C) 2008-2010 Rick Taube.                                        
This program is free software; you can redistribute it and/or modify  
it under the terms of the Lisp Lesser Gnu Public License. The text of 
this agreement is available at http://www.cliki.net/LLGPL             
*=======================================================================*/
#ifndef AUDIO_H
#define AUDIO_H

#include "juce.h"
#include "iostream"

class AudioFilePlayer;

class AudioManager : public AudioDeviceManager
{
  bool audioready;
  AudioFilePlayer* audiofileplayer;

public:
  AudioManager();
  ~AudioManager();
  void configureForUse();
  bool isAudioReady(){return audioready;}
  void isAudioReady(bool r){audioready=r;}
  void openAudioFilePlayer(File file=File::nonexistent, bool play=false);
  //  void initAudioFilePlayer();
  AudioFilePlayer* getAudioFilePlayerComponent() {return audiofileplayer;}
  void openAudioSettings();
  /** stop the audio file player if it is currently playing a sound file **/
  void stopAudioPlayback();
  juce_DeclareSingleton (AudioManager, true)
};

class AudioFilePlayer : public Component,
  public FilenameComponentListener,
  public ButtonListener,
  public SliderListener,
  public ChangeListener,
  public AudioIODeviceCallback
{
 
  class WaveformComp; // taken from JUCE Demo, added zoomFactor.
  class PlaybackCursor; // playback cursor
  class AudioTransport; // andrew's transport widget

  FilenameComponent* fileChooser;
  TextButton* audioSettingsButton;
  Slider* zoomSlider;
  Label* minTime;
  Label* maxTime;

  friend class AudioTransport;
  AudioTransport* transport;
  
  // this wraps the actual audio device
  AudioDeviceManager audioDeviceManager;

  // this allows an audio source to be streamed to the IO device
  AudioSourcePlayer audioSourcePlayer;

  // this controls the playback of a positionable audio stream, handling the
  // starting/stopping and sample-rate conversion
  AudioTransportSource transportSource;

  // this is the actual stream that's going to read from the audio file.
  AudioFormatReaderSource* currentAudioFileSource;
  File currentFile;
  double fileduration;
public:
  AudioFilePlayer();
  ~AudioFilePlayer();

  AudioFormatManager formatManager;
  WaveformComp* waveform;
  PlaybackCursor* playbackCursor;
  double getFileDuration();
  TextButton* getSettings();
  void setFileToPlay(File file, bool play=false);
  void stop();
  void pause();
  void rewind();
  AudioTransportSource& getTransportSource();
  void audioDeviceIOCallback (const float** inputChannelData,
    int totalNumInputChannels,
    float** outputChannelData,
    int totalNumOutputChannels,
    int numSamples);
  void audioDeviceAboutToStart (AudioIODevice* device);
  void audioDeviceStopped();
  void paint (Graphics& g){}
  void resized();
  void updateButtons();
  void buttonClicked (Button* button);
  void sliderValueChanged (Slider* slider);
  //  void mouseWheelMove (const MouseEvent& e, float wheelIncrementX, float wheelIncrementY);
  void filenameComponentChanged (FilenameComponent*);
  void changeListenerCallback (ChangeBroadcaster* source);
  bool keyPressed (const KeyPress& key);

};

class AudioFilePlayerWindow : public DocumentWindow 
{
  AudioFilePlayer* player;
public:
  AudioFilePlayerWindow(AudioFilePlayer* comp);
  ~AudioFilePlayerWindow();
  void closeButtonPressed();
};

#endif
