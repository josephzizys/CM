/*=======================================================================*
  Copyright (C) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/
#ifndef AUDIO_H
#define AUDIO_H

#include "juce.h"

class AudioFilePlayer;

class AudioManager : public AudioDeviceManager
{
  bool audioready;
  AudioFilePlayer* audiofileplayer;

 public:
  AudioManager();
  ~AudioManager();
  bool isAudioReady(){return audioready;}
  bool isAudioReady(bool r){audioready=r;}
  void openAudioFilePlayer(File file=File::nonexistent, bool play=false);
  //  void initAudioFilePlayer();
  AudioFilePlayer* getAudioFilePlayerComponent() {return audiofileplayer;}
  void openAudioSettings();
  juce_DeclareSingleton (AudioManager, true)
};

class AudioFilePlayer : public Component,
		    public FilenameComponentListener,
		    public ButtonListener,
		    public ChangeListener,
		    public AudioIODeviceCallback
{
  FilenameComponent* fileChooser;
  TextButton* playButton;
  TextButton* stopButton;
  TextButton* audioSettingsButton;
  
  ////MidiKeyboardComponent* keyboardComponent;
  ////  AudioInputWaveformDisplay* waveformComponent;
  // this wraps the actual audio device
  AudioDeviceManager audioDeviceManager;
  // this allows an audio source to be streamed to the IO device
  AudioSourcePlayer audioSourcePlayer;
  // this controls the playback of a positionable audio stream, handling the
  // starting/stopping and sample-rate conversion
  AudioTransportSource transportSource;
  // this source contains our synth, and generates its output
  ////  SynthAudioSource synthSource;
  // this source is used to mix together the output from our synth source
  // and wave player source
  MixerAudioSource mixerSource;
  // this is the actual stream that's going to read from the audio file.
  AudioFormatReaderSource* currentAudioFileSource;
  File currentFile;

public:
  AudioFilePlayer();
  ~AudioFilePlayer();

  bool isPlaying();
  void startPlaying();
  void stopPlaying();
  void setFileToPlay(File file, bool play=false);

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
  void filenameComponentChanged (FilenameComponent*);
  void changeListenerCallback (void*);
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
