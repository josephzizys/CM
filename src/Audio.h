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

class AudioFilePlayer;

class AudioFilePlayerWindow : public DocumentWindow 
{
  AudioFilePlayer* player;
public:
  AudioFilePlayerWindow(AudioFilePlayer* comp);
  ~AudioFilePlayerWindow();
  void closeButtonPressed();
};

#endif
