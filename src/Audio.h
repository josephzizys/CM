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

class GRACETransport;

class AudioFilePlayer : public Component,
		    public FilenameComponentListener,
		    public ButtonListener,
		    public ChangeListener,
		    public AudioIODeviceCallback
{

  class AudioInputWaveformDisplay  : public Component,
    public Timer,
    public AudioIODeviceCallback
    {
    public:
      AudioInputWaveformDisplay()
	{
	  bufferPos = 0;
	  bufferSize = 2048;
	  circularBuffer = (float*) juce_calloc (sizeof (float) * bufferSize);
	  currentInputLevel = 0.0f;
	  numSamplesIn = 0;
	  
	  setOpaque (true);
	  startTimer (1000 / 50);  // repaint every 1/50 of a second
	}
      
      ~AudioInputWaveformDisplay()
	{
	  juce_free (circularBuffer);
	}
      
      void paint (Graphics& g)
      {
        g.fillAll (Colours::black);
        g.setColour (Colours::lightgreen);
	
        const float halfHeight = getHeight() * 0.5f;
	
        int bp = bufferPos;
	
        for (int x = getWidth(); --x >= 0;)
	  {
            const int samplesAgo = getWidth() - x;
            const float level = 
	      circularBuffer [(bp + bufferSize - samplesAgo) % bufferSize];
	    
            if (level > 0.01f)
	      g.drawLine ((float) x, halfHeight - halfHeight * level,
			  (float) x, halfHeight + halfHeight * level);
	  }
      }
      
      void timerCallback()
      {
        repaint();
      }
      
      void addSample (const float sample)
      {
        currentInputLevel += fabsf (sample);
	
        const int samplesToAverage = 128;
	
        if (++numSamplesIn > samplesToAverage)
	  {
            circularBuffer [bufferPos++ % bufferSize] =
	      currentInputLevel / samplesToAverage;
	    
            numSamplesIn = 0;
            currentInputLevel = 0.0f;
	  }
      }
      
      void audioDeviceIOCallback (const float** inputChannelData,
				  int totalNumInputChannels,
				  float** outputChannelData,
				  int totalNumOutputChannels,
				  int numSamples)
      {
        for (int i = 0; i < totalNumInputChannels; ++i)
	  {
            if (inputChannelData [i] != 0)
	      {
                for (int j = 0; j < numSamples; ++j)
		  addSample (inputChannelData [i][j]);
		
                break;
	      }
	  }
      }
      
      void audioDeviceAboutToStart (AudioIODevice*)
      {
        zeromem (circularBuffer, sizeof (float) * bufferSize);
      }
      
      void audioDeviceStopped()
      {
        zeromem (circularBuffer, sizeof (float) * bufferSize);
      }
      
    private:
      float* circularBuffer;
      float currentInputLevel;
      int volatile bufferPos, bufferSize, numSamplesIn;
    };
  
  FilenameComponent* fileChooser;
  TextButton* audioSettingsButton;
  GRACETransport* transport;

  ////MidiKeyboardComponent* keyboardComponent;
  AudioInputWaveformDisplay* waveformComponent;
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
  double fileduration;
public:
  AudioFilePlayer();
  ~AudioFilePlayer();

  double getFileDuration();
  TextButton* getSettings();
  void setFileToPlay(File file, bool play=false);
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
