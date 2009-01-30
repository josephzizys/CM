/*=======================================================================*
  Copyright (C) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#include "Audio.h"
#include <iostream>
#include "Console.h"
#include "Transport.h"

/*=======================================================================*
                            Global Audio Manager
 *=======================================================================*/
 
juce_ImplementSingleton(AudioManager)

AudioManager::AudioManager()
  : audioready (false),
    audiofileplayer (NULL)
{
}

AudioManager::~AudioManager()
{
  // if a window is open on the player then just delete the window and
  // the audio player component will be deleted when the window
  // deletes its content component. otherwise delete the component
  closeAudioDevice();
  if (audiofileplayer!=NULL)
    {
      delete audiofileplayer;
    }
}

void AudioManager::openAudioFilePlayer(File file, bool play)
{
  // only one player supported until i look into mixing
  if (audiofileplayer==NULL)
    {
      audiofileplayer=new AudioFilePlayer();
      // set invisible until a window opens on it.
      audiofileplayer->setVisible(false);      
    }
  if (audiofileplayer->isVisible())
    {
      AudioFilePlayerWindow* win;
      win=(AudioFilePlayerWindow*)
	(audiofileplayer->getTopLevelComponent());
      win->grabKeyboardFocus();
      win->toFront(true);
    }
  else
    {
      new AudioFilePlayerWindow(audiofileplayer);
    }
  if (file!=File::nonexistent)
    {
      if (file.existsAsFile())
	{
	  AudioFormatManager formatManager;
	  formatManager.registerBasicFormats();
	  if (formatManager.findFormatForFileExtension
	      (file.getFileExtension())!=NULL)
	    {
	      audiofileplayer->setFileToPlay(file, play);
	    }
	  else
	    {
	      String err=T("Unsupported audio file: ") + 
		file.getFullPathName() + T("\n");
	      Console::getInstance()->printWarning(err);
	    }
	}
      else
	{
	  String err=T("File ") + file.getFullPathName() +
	    T(" does not exist.\n");
	  Console::getInstance()->printWarning(err);
	}
    }
}

void AudioManager::openAudioSettings()
{
  // Open an AudioDeviceSelectorComponent
  AudioDeviceSelectorComponent comp
    (*AudioManager::getInstance(), 0, 0, 2, 2, true, false);
  // ...and show it in a DialogWindow...
  comp.setSize(400, 200);
  int b=0, r=0;
  for (int i=0; i<comp.getNumChildComponents(); i++)
    {
      Component* c=comp.getChildComponent(i);
      if (b < c->getBottom())
	b=c->getBottom();
      if (r < c->getRight())
	r=c->getRight();
    }
  //std::cout << "max bottom " << b << " max right " << r << "\n";
  comp.setSize(r+10, b+20);
  DialogWindow::showModalDialog (T("Audio Settings"), &comp, NULL,
				 Colour(0xffe5e5e5), true);
}

/*=======================================================================*
                            Audio File Player Window
 *=======================================================================*/

class GRACETransport : public Transport
{
public:
  AudioFilePlayer* player;
  virtual void play(double position);
  virtual void pause(void);
  virtual void positionChanged(double position, bool isPlaying);
};

AudioFilePlayerWindow::AudioFilePlayerWindow (AudioFilePlayer* comp)
  : DocumentWindow(T("Audio File Player"), Colour(0xffe5e5e5),
		   DocumentWindow::allButtons, true),
    player (NULL)
{
  player=comp;
  player->setSize(450, 350);
  player->setVisible(true);
  setContentComponent(player);
  setResizable(true, true); 
  //setResizable(false, false); 
  setUsingNativeTitleBar(true);
  setDropShadowEnabled(true);
  centreWithSize(450, 10+24+10+24+10+72+10);
  setVisible(true);
}

AudioFilePlayerWindow::~AudioFilePlayerWindow()
{
  setContentComponent(0, false); 
  player->setVisible(false);
}

void AudioFilePlayerWindow::closeButtonPressed()
{
  delete this;
}

/*=======================================================================*
                               Audio File Player
 *=======================================================================*/

AudioFilePlayer::AudioFilePlayer ()
  : waveformComponent (0),
    fileduration (0.0)
{
  setName(T("Audio File Player"));
  currentAudioFileSource = 0;
  AudioFormatManager formatManager;
  formatManager.registerBasicFormats();
  fileChooser=new FilenameComponent(T("audiofile"),  File::nonexistent,
				    true, false, false, 
			    formatManager.getWildcardForAllFormats(),
				    String::empty, T(""));
  addAndMakeVisible(fileChooser);
  fileChooser->addListener (this);
  fileChooser->setBrowseButtonText(T("File..."));
  audioSettingsButton=new TextButton(T("Settings..."),
				     T("Configure audio settings"));
  addAndMakeVisible (audioSettingsButton);
  audioSettingsButton->addButtonListener(this);
  transport=new GRACETransport();
  transport->addAndMakeVisible(this);
  transport->player=this;
  addAndMakeVisible (waveformComponent = new AudioInputWaveformDisplay());
  // register for start/stop messages from the transport source..
  transportSource.addChangeListener (this);
  if (AudioManager::getInstance()->isAudioReady())
    {
      mixerSource.addInputSource (&transportSource, false);
      // ..and connect the mixer to our source player.
      audioSourcePlayer.setSource (&mixerSource);
      // start the IO device pulling its data from our callback..
      AudioManager::getInstance()->setAudioCallback (this);
    }
  else
    {
      fileChooser->setEnabled(false);
    }
}

AudioFilePlayer::~AudioFilePlayer()
{
  audioDeviceManager.setAudioCallback (0);
  transportSource.removeChangeListener (this);
  transportSource.setSource (0);
  deleteAndZero (currentAudioFileSource);
  audioSourcePlayer.setSource (0);
  deleteAllChildren();
}

void AudioFilePlayer::resized()
{
  float x=10, y=10;
  float r=getWidth();
  float b=getHeight();
  audioSettingsButton->setBounds(r-80-10, y, 80, 24);
  fileChooser->setBounds(x, y, audioSettingsButton->getX()-10-x, 24);
  y=audioSettingsButton->getBottom()+10;
  // center transport in window's width (6 buttons each 44px)
  transport->setPositions((r/2)-(44*3), y, 44, 24);
  // transport has two lines
  y=y+24+24+10;
  waveformComponent->setBounds(x, y, r-10-10, b-y-10);
}

AudioTransportSource& AudioFilePlayer::getTransportSource()
{
  return transportSource;
}

void AudioFilePlayer::setFileToPlay(File file, bool play)
{
  // stop any current source
  transportSource.stop();
  // have to clear out any existing file or chooser doesnt register
  // change if its adding the same file
  fileChooser->setCurrentFile(File::nonexistent, false, false);
  fileChooser->setCurrentFile(file, true, true);
  if (play)
    {
      //transport->play(0.0); // THIS DOESNT WORK
      transport->pushButton(Transport::PlayFromBeginningButton);
    }
}

double AudioFilePlayer::getFileDuration()
{
  return fileduration;
}

TextButton* AudioFilePlayer::getSettings()
{
  return audioSettingsButton;
}

void GRACETransport::play(double position)
{
  player->getTransportSource().
    setPosition(player->getFileDuration()*position);
  player->getTransportSource().start();
  player->getSettings()->setEnabled(false);
  player->waveformComponent->audioDeviceAboutToStart(0);
}

void GRACETransport::pause(void)
{
  player->getTransportSource().stop();
  player->getSettings()->setEnabled(true);
  player->waveformComponent->audioDeviceStopped();
}

void GRACETransport::positionChanged(double position, bool isPlaying)
{
  //'position' is normalized from 0 to 1.0 
  //if (isPlaying)
  player->getTransportSource().
      setPosition(player->getFileDuration()*position);
  if(!player->getTransportSource().isPlaying() && isPlaying)
  {
    player->getTransportSource().start();
    player->getSettings()->setEnabled(false);
  }
}

void AudioFilePlayer::filenameComponentChanged (FilenameComponent*)
{
  // this is called when the user changes the file in the chooser
  File audioFile(fileChooser->getCurrentFile());
  
  // stop and unload the previous file source and delete it..
  transport->pause();
  transportSource.setSource(0);
  deleteAndZero(currentAudioFileSource);
  
  // get a format manager and init with the basic types (wav and aiff).
  AudioFormatManager formatManager;
  formatManager.registerBasicFormats();
  AudioFormatReader* reader = formatManager.createReaderFor(audioFile);
  
  if (reader != 0)
    {
      currentFile = audioFile;
      currentAudioFileSource = new AudioFormatReaderSource (reader, true);
      // ..and plug it into our transport source
      transportSource.setSource (currentAudioFileSource,
				 32768, // buffer this many samples ahead
				 reader->sampleRate);
      fileduration=(double)
	(reader->lengthInSamples/reader->sampleRate) ;
      //std::cout <<"File Duration=" << fileduration << "\n";;
    }
}

void AudioFilePlayer::audioDeviceIOCallback(const float** inputChannelData,
					    int totalNumInputChannels,
					    float** outputChannelData,
					    int totalNumOutputChannels,
					    int numSamples)
{

  // pass the audio callback on to our player source, and also the
  // waveform display comp
  audioSourcePlayer.audioDeviceIOCallback(inputChannelData, 
					  totalNumInputChannels,
					  outputChannelData,
					  totalNumOutputChannels, 
					  numSamples);
  waveformComponent->audioDeviceIOCallback(inputChannelData,
					   totalNumInputChannels,
					   outputChannelData,
					   totalNumOutputChannels,
					   numSamples);
  // update transport slider to make it move left to right during
  // playback. this not as straightforward as is should be because (1)
  // juce is triggering this callback even if a file is not playing
  // and (2) sending updates to the slider every time this method is
  // called will cause the app to crash, at least on mac
  static int counter=0;
  static bool wasStreamFinished = false;

  if(wasStreamFinished && !transportSource.hasStreamFinished())
  {
    wasStreamFinished = !wasStreamFinished;
  }
  else if(!wasStreamFinished && transportSource.hasStreamFinished())
  {
    transport->pushButton(Transport::StopButton);
    wasStreamFinished = !wasStreamFinished;
  }

  if (counter==100) // downsample to avoid juce crash
  {
    if (transportSource.isPlaying())
      transport->setPosition(transportSource.getCurrentPosition() /
      getFileDuration());

    counter=0;
  }
  else 
    counter++;
}

void AudioFilePlayer::audioDeviceAboutToStart (AudioIODevice* device)
{
  audioSourcePlayer.audioDeviceAboutToStart(device);
  waveformComponent->audioDeviceAboutToStart(device);
}

void AudioFilePlayer::audioDeviceStopped()
{
  audioSourcePlayer.audioDeviceStopped();
  waveformComponent->audioDeviceStopped();
}

void AudioFilePlayer::buttonClicked (Button* button)
{
  if (button == audioSettingsButton)
    {
      AudioManager::getInstance()->openAudioSettings();
    }
}
void AudioFilePlayer::changeListenerCallback (void*)
{
}

