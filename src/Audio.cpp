/*=======================================================================*
  Copyright (C) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#include "Audio.h"
#include <iostream>
#include "Console.h"

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
      std::cout << "AudioFilePlayer inited!\n";
    }
  if (audiofileplayer->isVisible())
    {
      std::cout << "AudioFilePlayer is visible\n";
      AudioFilePlayerWindow* win;
      win=(AudioFilePlayerWindow *)(audiofileplayer->getTopLevelComponent());
      win->grabKeyboardFocus();
      win->toFront(true);
    }
  else
    {
      std::cout << "Opening new AudioFilePlayer\n";
      new AudioFilePlayerWindow(audiofileplayer);
    }
  if (file!=File::nonexistent)
    {
      if (file.existsAsFile())
	{
	  AudioFormatManager formatManager;
	  formatManager.registerBasicFormats();
	  if (formatManager.findFormatForFileExtension(file.getFileExtension())!=NULL)
	    {
	      audiofileplayer->setFileToPlay(file, play);
	    }
	  else
	    {
	      String err=T("Unsupported audio file: ") + file.getFullPathName() + T("\n");
	      Console::getInstance()->printWarning(err);
	    }
	}
      else
	{
	  String err=T("File ") + file.getFullPathName() + T(" does not exist.\n");
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

AudioFilePlayerWindow::AudioFilePlayerWindow (AudioFilePlayer* comp)
  : DocumentWindow(T("Audio File Player"), Colour(0xffe5e5e5),
		   DocumentWindow::allButtons, true),
    player (NULL)
{
  player=comp;
  player->setSize(450, 350);
  player->setVisible(true);
  setContentComponent(player);
  //  setResizable(true, true); 
  setResizable(false, false); 
  setUsingNativeTitleBar(true);
  setDropShadowEnabled(true);
  centreWithSize(450, 10+24+10+24+10+48+10);
  setVisible(true);
}

AudioFilePlayerWindow::~AudioFilePlayerWindow()
{
  std::cout << "~AudioFilePlayerWindow()\n";
  setContentComponent(0, false); 
  player->setVisible(false);
}

void AudioFilePlayerWindow::closeButtonPressed()
{
  std::cout << "closeButtonPressed()\n";
  // tell manager no window open
  //  player->setVisible(false);
  // only one player for now so remove it before deleteing window!
  // removeContentComponent(player); 
  delete this;
}


/*=======================================================================*
                               Audio File Player
 *=======================================================================*/

AudioFilePlayer::AudioFilePlayer ()
  : waveformComponent (0)
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
  fileChooser->setBrowseButtonText(T("Open..."));
  playButton=new TextButton(T("Play"), T("Play the current audio file"));
  addAndMakeVisible (playButton);

  playButton->addButtonListener (this);
  playButton->setColour (TextButton::buttonColourId, Colours::lightgreen);
  playButton->setColour (TextButton::buttonOnColourId, Colours::lightgreen);
  playButton->setConnectedEdges (Button::ConnectedOnRight);

  stopButton=new TextButton(T("Stop"), T("Plays the current audio file"));
  addAndMakeVisible(stopButton);
  stopButton->addButtonListener (this);
  stopButton->setColour (TextButton::buttonColourId, Colours::red);
  stopButton->setColour (TextButton::buttonOnColourId, Colours::red);
  stopButton->setConnectedEdges (Button::ConnectedOnLeft);

  audioSettingsButton=new TextButton(T("Audio Settings..."),
				     T("Configure audio settings"));
  addAndMakeVisible (audioSettingsButton);
  audioSettingsButton->addButtonListener(this);
  ////  addAndMakeVisible (keyboardComponent = new MidiKeyboardComponent (synthSource.keyboardState,
  ////								    MidiKeyboardComponent::horizontalKeyboard));
  addAndMakeVisible (waveformComponent = new AudioInputWaveformDisplay());

  // register for start/stop messages from the transport source..
  transportSource.addChangeListener (this);
  if (AudioManager::getInstance()->isAudioReady())
    {
      // add the two audio sources to our mixer..
      mixerSource.addInputSource (&transportSource, false);
      ////      mixerSource.addInputSource (&synthSource, false);
      
      // ..and connect the mixer to our source player.
      audioSourcePlayer.setSource (&mixerSource);
      
      // start the IO device pulling its data from our callback..
      AudioManager::getInstance()->setAudioCallback (this);
      
      // and we need to send midi input to our synth for processing
      ////      audioDeviceManager.addMidiInputCallback (String::empty, &synthSource.midiCollector);
    }
  else
    {
      fileChooser->setEnabled(false);
      playButton->setEnabled(false);
      stopButton->setEnabled(false);
    }
}

AudioFilePlayer::~AudioFilePlayer()
{
  //audioDeviceManager.removeMidiInputCallback(&synthSource.midiCollector);
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

  fileChooser->setBounds(x, y, r-20, 24);
  y=fileChooser->getBottom()+10;
  playButton->setBounds(x, y, 100, 24);
  stopButton->setBounds(playButton->getRight(), y, 100, 24);
  audioSettingsButton->setBounds(r-120-10, y, 120, 24);
  y=playButton->getBottom()+10;
  waveformComponent->setBounds(x, y, r-10-10, b-y-10);
  updateButtons();
}

bool AudioFilePlayer::isPlaying()
{
  return false;
}

void AudioFilePlayer::startPlaying()
{
  playButton->triggerClick();
}

void AudioFilePlayer::stopPlaying()
{
  stopButton->triggerClick();
}

void AudioFilePlayer::setFileToPlay(File file, bool play)
{
  // stop any current source and clear out any existing file (so that
  // replaying the same file works)
  transportSource.stop();
  fileChooser->setCurrentFile(File::nonexistent, false, false);
  fileChooser->setCurrentFile(file, true, true);
  if (play)
    {
      startPlaying();
      //transportSource.setPosition (0.0);
      //transportSource.start();
    }
  //updateButtons();
}

void AudioFilePlayer::audioDeviceIOCallback (const float** inputChannelData,
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

void AudioFilePlayer::updateButtons()
{
  playButton->setEnabled(currentAudioFileSource != 0 && ! transportSource.isPlaying());
  stopButton->setEnabled(transportSource.isPlaying());
  //  repaint();
}

void AudioFilePlayer::buttonClicked (Button* button)
{
  if (button == playButton)
    {
      transportSource.setPosition (0.0);
      transportSource.start();
    }
  else if (button == stopButton)
    {
      transportSource.stop();
    }
  else if (button == audioSettingsButton)
    {
      AudioManager::getInstance()->openAudioSettings();
    }
}

void AudioFilePlayer::filenameComponentChanged (FilenameComponent*)
{
  // this is called when the user changes the filename in the file chooser box

  std::cout << "filenameComponentChanged\n";
  
  File audioFile (fileChooser->getCurrentFile());
  
  // unload the previous file source and delete it..
  transportSource.stop();
  transportSource.setSource (0);
  deleteAndZero (currentAudioFileSource);
  
  // create a new file source from the file..
  
  // get a format manager and set it up with the basic types (wav and aiff).
  AudioFormatManager formatManager;
  formatManager.registerBasicFormats();
  
  AudioFormatReader* reader = formatManager.createReaderFor (audioFile);
  
  if (reader != 0)
    {
      currentFile = audioFile;
      
      currentAudioFileSource = new AudioFormatReaderSource (reader, true);
      
      // ..and plug it into our transport source
      transportSource.setSource (currentAudioFileSource,
				 32768, // tells it to buffer this many samples ahead
				 reader->sampleRate);
    }
  
  updateButtons();
}

void AudioFilePlayer::changeListenerCallback (void*)
{
  // callback from the transport source to tell us that play has
  // started or stopped, so update our buttons..
  updateButtons();
}

