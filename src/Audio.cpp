/*=======================================================================*
  Copyright (C) 2008-2010 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#include "Audio.h"
#include <iostream>
#include "Console.h"
#include "Transport.h"
//#ifdef GRACE
#include "Preferences.h"
//#endif

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

void AudioManager::configureForUse()
{
  // this is called AFTER initialize() to configure the device for use
  AudioDeviceSetup setup;
  getAudioDeviceSetup(setup);
  int bufsize=Preferences::getInstance()->getIntProp(T("AudioPlaybackBufferSize"), 512);
  if (bufsize!=setup.bufferSize)
    {
      //std::cout << "device size: " << setup.bufferSize << " setting device size to " <<  bufsize << "\n";
      setup.bufferSize=bufsize;
      setAudioDeviceSetup(setup, true);      
    }
  isAudioReady(true);
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
	  if (audiofileplayer->formatManager.findFormatForFileExtension
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
  AudioDeviceSelectorComponent comp (*AudioManager::getInstance(), 0, 2, 0, 2, false, false, true, false);
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
  comp.setSize(r+10, b+20);
  DialogWindow::showModalDialog (T("Audio Settings"), &comp, NULL,
				 Colour(0xffe5e5e5), true);
  AudioDeviceSetup setup;
  getAudioDeviceSetup(setup);
  //std::cout << "setting preferences to " <<  setup.bufferSize << "\n";
  Preferences::getInstance()->setIntProp(T("AudioPlaybackBufferSize"), setup.bufferSize);
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
  player->setVisible(true);
  setContentComponent(player);
  setResizable(true, true); 
  setUsingNativeTitleBar(true);
  setDropShadowEnabled(true);
  centreWithSize(450, 200);
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
                      Waveform View (taken from Juce Demo)
 *=======================================================================*/

class AudioFilePlayer::WaveformComp : public Component, 
                                      public ChangeListener
{
public:
  WaveformComp()
    : thumbnailCache (5),
      thumbnail (512, formatManager, thumbnailCache)
  {
    startTime = endTime = 0;
    formatManager.registerBasicFormats();
    thumbnail.addChangeListener (this);
  }
  ~WaveformComp()
  {
    thumbnail.removeChangeListener (this);
  }
  void setFile (const File& file)
  {
    thumbnail.setSource (new FileInputSource (file));
    startTime = 0;
    endTime = thumbnail.getTotalLength();
  }
  void setZoomFactor (double amount)
  {
    if (thumbnail.getTotalLength() > 0)
      {
        double timeDisplayed = jmax (0.001, (thumbnail.getTotalLength() - startTime) * (1.0 - jlimit (0.0, 1.0, amount)));
        endTime = startTime + timeDisplayed;
        repaint();
      }
  }
  void mouseWheelMove (const MouseEvent& e, float wheelIncrementX, float wheelIncrementY)
  {
    if (thumbnail.getTotalLength() > 0)
      {
        double newStart = startTime + (wheelIncrementX + wheelIncrementY) * (endTime - startTime) / 10.0;
        newStart = jlimit (0.0, thumbnail.getTotalLength() - (endTime - startTime), newStart);
        endTime = newStart + (endTime - startTime);
        startTime = newStart;
        repaint();
        //std::cout << "startTime="<< startTime<< " endTime="<<endTime<<"\n";
      }
  }
  void mouseDoubleClick(const MouseEvent &e)
  {
    // reset display to full waveform, no zoom
    startTime=0;
    endTime=thumbnail.getTotalLength();
    repaint();
    // a bit gross but we have to reset the zoom slider somehow!
    AudioFilePlayer* p=(AudioFilePlayer*)getParentComponent();
    p->zoomSlider->setValue(0.0,false);
  }
  void paint (Graphics& g)
  {
    g.fillAll (Colours::white);
    g.setColour (Colours::mediumblue);
    if (thumbnail.getTotalLength() > 0)
      {
        int heightPerChannel = (getHeight() - 4) / thumbnail.getNumChannels();
        for (int i = 0; i < thumbnail.getNumChannels(); ++i)
          {
            thumbnail.drawChannel (g, 2, 2 + heightPerChannel * i,
                                   getWidth() - 4, heightPerChannel,
                                   startTime, endTime,
                                   i, 1.0f);
          }
      }
    else
      {
        g.setFont (14.0f);
        g.drawFittedText ("(No audio file selected)", 0, 0, getWidth(), getHeight(), Justification::centred, 2);
      }
  }
  void changeListenerCallback (void*)
  {
    // this method is called by the thumbnail when it has changed, so we should repaint it..
    repaint();
  }
  
  AudioFormatManager formatManager;
  AudioThumbnailCache thumbnailCache;
  AudioThumbnail thumbnail;
  double startTime, endTime;
};

/*=======================================================================*
                              Playback Cursor 
 *=======================================================================*/

class AudioFilePlayer::PlaybackCursor : public Component
  // the PlaybackCursor component is transparent and situate in FRONT
  // of the audio waveform view to isplay the cursor position while
  // the file is playing. this works pretty well except that the
  // component has to respond to the mousewheel and doubleClick events
  // that are actually meant for the waveform view behind it.
{

public:
  AudioFilePlayer::WaveformComp* waveform;
  double position;
  PlaybackCursor(WaveformComp* thumb) : position (-1.0) 
  {
    waveform=thumb;
  }
  ~PlaybackCursor(){}
  void paint (Graphics& g)
  {
    if (position>0)
      {
        double thisTime=position*waveform->thumbnail.getTotalLength();
        if (thisTime>=waveform->startTime && thisTime<=waveform->endTime) // portion of wave that is visible
          {
            double visibleDuration=waveform->endTime-waveform->startTime ;
            g.setColour (Colours::grey);
            g.drawVerticalLine(((thisTime-waveform->startTime)/visibleDuration)*getWidth(), 0, getHeight());
          }
      }
  }
  void setPosition(double pos)
  {
    position=pos;
    repaint();
  }  
  void mouseWheelMove (const MouseEvent& e, float dx, float dy)
  {
    waveform->mouseWheelMove(e, dx, dy);
  }
  void mouseDoubleClick(const MouseEvent &e)
  {
    waveform->mouseDoubleClick(e);
  } 
};

/*=======================================================================*
                             Audio Transport Widget
 *=======================================================================*/

class AudioFilePlayer::AudioTransport : public Transport
{
public:
  AudioFilePlayer* player;
  void play(double position)
  {
    player->getTransportSource().setPosition(player->getFileDuration()*position);
    player->getTransportSource().start();
    player->getSettings()->setEnabled(false);
  }
  
  void pause(void)
  {
    player->getTransportSource().stop();
    player->getSettings()->setEnabled(true);
  }
  
  void positionChanged(double position, bool isPlaying)
  {
    //'position' is normalized from 0 to 1.0 
    //if (isPlaying)
    double pos=player->getFileDuration()*position;
    player->getTransportSource().setPosition(player->getFileDuration()*position);
    player->playbackCursor->setPosition(pos);
    if(!player->getTransportSource().isPlaying() && isPlaying)
      {
        player->getTransportSource().start();
        player->getSettings()->setEnabled(false);
      }
  }
};

AudioFilePlayer::AudioFilePlayer ()
  : 
  fileChooser (0),
  audioSettingsButton (0),
  transport (0),
  zoomSlider (0),
  fileduration (0.0)
{
  setName(T("Audio File Player"));
  currentAudioFileSource = 0;
  //AudioFormatManager formatManager;
  formatManager.registerBasicFormats();
  fileChooser=new FilenameComponent(T("audiofile"),  File::nonexistent,
				    true, false, false, 
                                    formatManager.getWildcardForAllFormats(),
				    String::empty, T(""));
  addAndMakeVisible(fileChooser);
  fileChooser->addListener (this);
  fileChooser->setBrowseButtonText(T("File..."));
  audioSettingsButton=new TextButton(T("Audio Settings..."),
				     T("Configure audio settings"));
  addAndMakeVisible (audioSettingsButton);
  audioSettingsButton->addButtonListener(this);
  transport=new AudioTransport();
  transport->addAndMakeVisible(this);
  transport->player=this;

  addAndMakeVisible (waveform=new WaveformComp());
  addAndMakeVisible (playbackCursor=new PlaybackCursor(waveform));

  addAndMakeVisible (zoomSlider = new Slider (String::empty));
  zoomSlider->setRange (0, 1, 0);
  zoomSlider->setSliderStyle (Slider::LinearHorizontal);
  zoomSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
  zoomSlider->addListener (this);
  zoomSlider->setSkewFactor (2);

  transportSource.addChangeListener (this);
  if (AudioManager::getInstance()->isAudioReady())
    {
      audioSourcePlayer.setSource (&transportSource);
      AudioManager::getInstance()->addAudioCallback (this);
    }
  else
    {
      fileChooser->setEnabled(false);
    }
}

AudioFilePlayer::~AudioFilePlayer()
{
  audioDeviceManager.removeAudioCallback (this);
  transportSource.removeChangeListener (this);
  transportSource.setSource (0);
  deleteAndZero (currentAudioFileSource);
  audioSourcePlayer.setSource (0);
  deleteAllChildren();
}

void AudioFilePlayer::resized()
{
  float m=8, l=24;
  float x=m, y=m;
  float w=getWidth();
  float h=getHeight();
  fileChooser->setBounds(x, y, w-(m*2), l);
  y=y+l+m;
  // transport has 6 buttons, each 44px centered in window's width
  transport->setPositions((w/2)-(44*3), y, 44, 24);
  // transport consists of two lines
  y=y+l+l+m;
  // calculate zoom and setting's button from bottom of window
  audioSettingsButton->setBounds(w-m-124, h-m-l, 124, l);
  zoomSlider->setBounds(x, h-m-l, 124, l);
  // waveform takes remainder of space
  waveform->setBounds(x, y, w-(m*2), (audioSettingsButton->getY()-m)-y);
  playbackCursor->setBounds(x, y, w-m, (audioSettingsButton->getY()-m)-y);
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

void AudioFilePlayer::filenameComponentChanged (FilenameComponent*)
{
  // this is called when the user changes the file in the chooser
  File audioFile(fileChooser->getCurrentFile());
  
  // stop and unload the previous file source and delete it..
  transport->pause();
  transportSource.setSource(0);
  deleteAndZero(currentAudioFileSource);
  
  // get a format manager and init with the basic types (wav and aiff).
  //  AudioFormatManager formatManager;
  //  formatManager.registerBasicFormats();
  AudioFormatReader* reader = formatManager.createReaderFor(audioFile);

  if (reader != 0)
    {
      waveform->setFile(audioFile);
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
    const MessageManagerLock mmLock;
    transport->pushButton(Transport::StopButton);
    wasStreamFinished = !wasStreamFinished;
    playbackCursor->setPosition(-1);
  }

  if (counter==10) // downsample to avoid juce crash
  {
    if (transportSource.isPlaying())
      {
        const MessageManagerLock mmLock;
        double pos=transportSource.getCurrentPosition()/getFileDuration();
        transport->setPosition(pos);
        playbackCursor->setPosition(pos);
      }
    counter=0;
  }
  else 
    counter++;
}

void AudioFilePlayer::audioDeviceAboutToStart (AudioIODevice* device)
{
  audioSourcePlayer.audioDeviceAboutToStart(device);
  ////waveformComponent->audioDeviceAboutToStart(device);
}

void AudioFilePlayer::audioDeviceStopped()
{
  audioSourcePlayer.audioDeviceStopped();
  ////waveformComponent->audioDeviceStopped();
}

void AudioFilePlayer::buttonClicked (Button* button)
{
  if (button == audioSettingsButton)
    {
      AudioManager::getInstance()->openAudioSettings();
    }
}

void AudioFilePlayer::sliderValueChanged (Slider* slider)
{
  if (slider == zoomSlider)
    {
      waveform->setZoomFactor(zoomSlider->getValue());
    }
}

void AudioFilePlayer::changeListenerCallback (void*)
{
}

