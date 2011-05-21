/*=======================================================================*
  This program is free software; you can redistribute it and/or modify
  it under the terms of the Lisp Lesser Gnu Public License. The text
  of this agreement is available at http://www.cliki.net/LLGPL
 *=======================================================================*/

#ifndef Transport_h
#define Transport_h

#include "Libraries.h"

/** A component for controlling audio/midi playback. Based on Andrew
    Burnson's original Transport class in Chorale Composer I. A
    Transport provides 5 buttons: Rewind, Back, Play/Pause, Forward,
    GoToEnd, a slider for scrolling through the playback sequence and
    an optional tempo slider. To create a Transport just pass it a
    Transport::Listener with the required play(), pause() ,
    positionChanged() and tempoChanged() callbacks implemented. These
    methods will be triggered whenever the user clicks on the
    Transport's components.  The Transport can be controlled from
    other objects in the main message thread by calling the underlying
    setPlaying(), setPausing() and setPlaybackPosition() and
    setTempo() methods.  To trigger transport actions from other
    threads use the asynchronous sendMessage() method. **/

class Transport : public juce::Component, 
  public juce::AsyncUpdater,
  public juce::ButtonListener,
  public juce::SliderListener
{
 public:

  /** Transport button ids. **/

  enum TransportButtonIds
  {
    RewindButton=1, BackButton, PlayPauseButton, ForwardButton, GoToEndButton, SliderButton
  };

  /** Transport message ids. Use these with sendMessage to control the
      transport from other threads.  **/

  enum TransportMessageIds
  {
    SetPlaying, SetPausing, SetPlaybackPosition, SetPlaybackTempo
  };

  /** A class for receiving callbacks from a Transport. **/

  class Listener
  {
  public:

    /** Called when the user presses the transport's Play button. The
        playback position is a normalized value 0.0 to 1.0. **/

    virtual void play(double position) = 0;

    /** Called when the user presses the transport's Pause button. **/

    virtual void pause(void) = 0;

    /** Called when the user moves the transport's slider button. The
        playback position is a normalized value 0.0 to 1.0 and
        isPlaying is true if the transport is currently marked as
        playing. **/

    virtual void positionChanged(double position, bool isPlaying) = 0;

    /** Called when the user moves the tempo slider. Tempo is the new
        tempo that was just set and and isPlaying is true if the
        transport is currently marked as playing. **/

    virtual void tempoChanged(double tempo, bool isPlaying) = 0;

  };
  
  /** A component for controlling audio playback. When the user clicks
      on a Transport's components the Transport::Listener's methods
      are called to implement the underlying changes in playback
      state. If tempo is > 0.0 the transport component will provide a
      tempo slider for conrolling the speed of playback while audio is
      running. **/

  Transport (Listener* transportListener, double tempo=0.0)
   : listener(transportListener),
    buttonRewind(0),
    buttonBack(0),
    buttonPlayPause(0),
    buttonForward(0),
    buttonGoToEnd(0),
    sliderPosition(0),
    sliderTempo(0),
    labelTempo(0),
    buttonWidth(44),
    buttonHeight(24),
    buttonColor (juce::Colour(90,90,120)),
    toggleColor (juce::Colour(60,60,180)),
    playing(false)
    {
      int connectLeft = juce::Button::ConnectedOnLeft;
      int connectBoth = juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight;
      int connectRight = juce::Button::ConnectedOnRight;     
      juce::DrawableButton::ButtonStyle buttonStyle = juce::DrawableButton::ImageOnButtonBackground;
      
      addAndMakeVisible(buttonRewind = new juce::DrawableButton(juce::String("Rewind"), buttonStyle));
      buttonRewind->setBackgroundColours(buttonColor, toggleColor);
      buttonRewind->setConnectedEdges(connectRight);
      drawRewind(buttonRewind);
      buttonRewind->addListener(this);
	
      addAndMakeVisible(buttonBack = new juce::DrawableButton(juce::String("Back"), buttonStyle));
      buttonBack->setBackgroundColours(buttonColor, toggleColor);
      buttonBack->setConnectedEdges(connectBoth);
      drawBack(buttonBack);
      buttonBack->addListener(this);
	
      addAndMakeVisible(buttonPlayPause = new juce::DrawableButton(juce::String("PlayPause"), buttonStyle));
      buttonPlayPause->setBackgroundColours(buttonColor, toggleColor);
      buttonPlayPause->setConnectedEdges(connectBoth);
      drawPlay(buttonPlayPause);
      buttonPlayPause->addListener(this);
	
      addAndMakeVisible(buttonForward = new juce::DrawableButton(juce::String("Forward"), buttonStyle));
      buttonForward->setBackgroundColours(buttonColor, toggleColor);
      buttonForward->setConnectedEdges(connectBoth);
      drawForward(buttonForward);
      buttonForward->addListener(this);

      addAndMakeVisible(buttonGoToEnd = new juce::DrawableButton(juce::String("GoToEnd"), buttonStyle));
      buttonGoToEnd->setBackgroundColours(buttonColor, toggleColor);
      buttonGoToEnd->setConnectedEdges(connectLeft);
      drawGoToEnd(buttonGoToEnd);
      buttonGoToEnd->addListener(this);
	
      addAndMakeVisible(sliderPosition = new juce::Slider(juce::String("Position")));
      sliderPosition->setSliderStyle(juce::Slider::LinearHorizontal);
      sliderPosition->setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
      sliderPosition->setColour(juce::Slider::thumbColourId,buttonColor);
      sliderPosition->setRange(0, 1.0);
      sliderPosition->addListener(this);
 
      // size the transport to width of 5 buttons and height of 2
      // lines with 4px margins all around
      int width = 4 + (buttonWidth*5)  + 4;
      int height = 4 + (buttonHeight*2) + 4;
      if (tempo>0)
      {
        // add extra width if we have a tempo slider
        //width += (buttonHeight + (buttonHeight*2) + (buttonHeight*2));
        width += ((buttonHeight/2) + (buttonHeight*2) + (buttonHeight*2));
        addAndMakeVisible(labelTempo = new juce::Label(juce::String::empty,juce::String(tempo) + juce::String(" BPM")));
        labelTempo->setColour(juce::Label::textColourId, buttonColor);
        addAndMakeVisible(sliderTempo = new juce::Slider(juce::String("Tempo")));
        sliderTempo->setSliderStyle(juce::Slider::Rotary);
        sliderTempo->setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        sliderTempo->setColour(juce::Slider::thumbColourId, buttonColor);
        sliderTempo->setColour(juce::Slider::rotarySliderFillColourId, buttonColor);
        sliderTempo->setColour(juce::Slider::rotarySliderOutlineColourId, buttonColor);
        // FIXME: tempo max and min should be customizable!
        sliderTempo->setRange(6.0, 208.0, 1.0);
        sliderTempo->setValue(tempo, true, true);
        sliderTempo->addListener(this);
      }
      setVisible(true);
      setSize(width, height);
    }
  
  ~Transport()
  {
    deleteAllChildren();
  }

 /** Returns true if the transport' state is set to playing otherwise
     false. This method is not thread safe. **/

  bool isPlaying()
  {
    return playing;
  }

  /** Marks transport as playing, flips to the "pause" icon for the
      user and calls the play() method if triggerAction is true (and
      the transport is not already playing). This method is not thread
      safe, use sendMessage() for that. **/

  void setPlaying(bool triggerAction=true)
  {
    //std::cout << "in setPlaying, trigger action is " << triggerAction << " playing status was " << playing << "\n";
    bool toggled=(playing==false);
    playing=true;
    drawPause(buttonPlayPause);
    if (triggerAction && toggled)
    {
      //      std::cout << "triggering play...\n";
      listener->play(getPlaybackPosition());
    }
  }
  
  /** Marks transport as pausing, displays the "play" icon for the
      user and calls the pause() method if triggerAction is true (and
      the transport is currently playing). This method is not thread
      safe, use sendMessage() for that. **/

  void setPausing(bool triggerAction=true)
  { 
    //std::cout << "in setPausing, trigger action is " << triggerAction << " playing status was " << playing << "\n";
    bool toggled=(playing==true);
    playing=false;
    drawPlay(buttonPlayPause);
    if (triggerAction && toggled)
    {
      //      std::cout << "triggering pause...\n";
      listener->pause();
    }
  }

  /** Sets the playback position as a normalized value 0.0 to 1.0. If
      triggerAction is true then the positionChanged() callback will
      be triggred. This method is not thread safe, use sendMessage()
      for that. **/

  void setPlaybackPosition(double position, bool triggerAction=true)
  {
    sliderPosition->setValue(position, triggerAction, false);
  }

  /** Increments the playback position by the specified delta. If
      triggerAction is true then the positionChanged() callback will
      be triggred. This method is not thread safe, use sendMessage()
      for that. **/

  void incrementPlaybackPosition(double delta, bool triggerAction=true)
  {
    setPlaybackPosition(sliderPosition->getValue()+delta, triggerAction);
  }

  /** Returns the position of the playback position slider on a
      normalized scale 0.0 to 1.0. This function is not thread
      safe. **/

  double getPlaybackPosition(void)
  {
    return sliderPosition->getValue();
  }

  /** Sets the current playback tempo in BPM. If triggerAction is true
      then the tempoChanged() callback will be triggered. This function
      is not thread safe. **/

  void setPlaybackTempo(double tempo, bool triggerAction=true)
  {
    // tempo components are optional
    if (sliderTempo)
    {
      sliderTempo->setValue(tempo, triggerAction, false);
      // if we are not triggering the update label display by hand
      if (!triggerAction)
        labelTempo->setText(juce::String(tempo)+juce::String(" BPM"), false);
    }
  }

  /** Returns the current playback tempo. This function is not thread safe. **/

  double getPlaybackTempo(void)
  {
    if (sliderTempo)
      return sliderTempo->getValue();
    return 0.0;
  }

  /** Implements thread-safe transport control. id
      is a message id, one of the button enums defined at the top of
      this file. The rest af the args are any data you need to
      pass. **/ 

  void sendMessage(int id, double d=0.0, int i=0, bool b=false)
  {
    juce::ScopedLock mylock(messages.getLock());
    messages.add(new TransportMessage(id, d, i, b));
    triggerAsyncUpdate();
  }

 private:

  bool playing;
  Listener* listener; 
  juce::DrawableButton* buttonPlayPause;
  juce::DrawableButton* buttonRewind;
  juce::DrawableButton* buttonBack;
  juce::DrawableButton* buttonForward;
  juce::DrawableButton* buttonGoToEnd;
  juce::Slider*         sliderPosition;
  juce::Slider*         sliderTempo;
  juce::Label*          labelTempo;
  int buttonWidth;
  int buttonHeight;
  juce::Colour buttonColor;
  juce::Colour toggleColor;

  /** Internal support for messaging from other threads **/

  class TransportMessage
  {
  public:
    int type;
    double double1;
    int int1;
    bool bool1;
    TransportMessage (int typ, double d1, int i1, bool b1) : type(typ), double1 (d1), int1 (i1), bool1 (b1) {} 
    ~TransportMessage() {}
  };

  juce::OwnedArray<TransportMessage, juce::CriticalSection> messages;

  void handleAsyncUpdate ()
  {
    juce::ScopedLock mylock(messages.getLock());
    int size=messages.size();
    for (int i=0; i<size; i++)
    {
      TransportMessage* msg=messages.getUnchecked(i);
      switch (msg->type)
      {
      case SetPausing:
        //std::cout << "TransportMessage: SetPausing\n";
        setPausing(msg->bool1); // false means dont trigger action
        break;
      case SetPlaying:
        //std::cout << "TransportMessage: SetPlaying\n";
        setPlaying(msg->bool1); // false means dont trigger action
        break;
      case SetPlaybackPosition:
        //std::cout << "TransportMessage: SetPosition pos=" << msg->double1 << "\n";
        setPlaybackPosition(msg->double1, msg->bool1);
        break;
      case SetPlaybackTempo:
        //std::cout << "TransportMessage: SetPosition pos=" << msg->double1 << "\n";
        setPlaybackTempo(msg->double1, msg->bool1);
        break;
      default:
        break;
      }
    }
    if (size>0)
      messages.clear();
  }

  /** Centers the transport controls within the horizontal and
      vertical area of the Transport. **/

  void resized()
  {
    int viewWidth=getWidth();
    int viewHeight=getHeight();
    int buttonLeft=(viewWidth/2)-(buttonWidth*2.5);  // total of 5 buttons
    // a tempo slider adds an extra 4.5 lineHeight's of width
    if (sliderTempo)
      buttonLeft -= (buttonHeight*2.25);

    int buttonTop=(viewHeight/2)-buttonHeight;
    buttonRewind->setBounds(buttonLeft, buttonTop, buttonWidth, buttonHeight);
    buttonBack->setBounds(buttonLeft + buttonWidth, buttonTop, buttonWidth, buttonHeight);      
    buttonPlayPause->setBounds(buttonLeft + (buttonWidth*2), buttonTop, buttonWidth, buttonHeight);
    buttonForward->setBounds(buttonLeft + (buttonWidth*3), buttonTop, buttonWidth, buttonHeight);
    buttonGoToEnd->setBounds(buttonLeft + (buttonWidth*4), buttonTop, buttonWidth, buttonHeight);    
    sliderPosition->setBounds(buttonLeft, buttonTop + buttonHeight, (buttonWidth*5), buttonHeight);
    if (sliderTempo)
    {
      // the optional tempo components are squares of 2 lineheights
      // per side positioned one lineheight to the right of the
      // rightmost transport button.
      sliderTempo->setBounds(buttonGoToEnd->getRight()+(buttonHeight/2), buttonTop , buttonHeight*2,  buttonHeight*2);
      labelTempo->setBounds(sliderTempo->getRight(), sliderTempo->getY(), buttonHeight*2,  buttonHeight*2);
    }
  }

  /** Internal function implements button clicked actions. **/

  virtual void buttonClicked(juce::Button* button)
  {
    static bool isShowingPlayNotPause = true;
    
    if(button == buttonPlayPause)
    {
      //Toggle the play/pause button.
      isShowingPlayNotPause = !isShowingPlayNotPause;
      
      if(isPlaying())
      {
        setPausing();
      }
      else
      {
        setPlaying();
      }
    }
    else if(button == buttonRewind)
    {
      sliderPosition->setValue(0);
    }
    else if(button == buttonBack)
    {
      sliderPosition->setValue(sliderPosition->getValue() - 0.10);
    }
    else if(button == buttonForward)
    {
      sliderPosition->setValue(sliderPosition->getValue() + 0.10);
    }
    else if(button == buttonGoToEnd)
    {
      sliderPosition->setValue(1);
    }
  }
  
  /** Internal slider function invokes the source's postionChanged()
      or tempoChanged() method. **/

  virtual void sliderValueChanged(juce::Slider *slider)
  {
    if (slider == sliderPosition)
      listener->positionChanged(sliderPosition->getValue(), isPlaying());
    else if (slider == sliderTempo)
    {
      double val=sliderTempo->getValue();
      labelTempo->setText(juce::String(val)+juce::String(" BPM"), false);
      listener->tempoChanged(val, isPlaying());
    }
  }
 
  /** Internal button drawing. **/

  void drawRewind(juce::DrawableButton* b)
  {
    juce::DrawablePath imageRewind;
    juce::Path pathRewind;
    pathRewind.addRectangle(-1.8f,0,0.3f,2.0f);
    pathRewind.addTriangle(0,0, 0,2.0f, -1.2f,1.0f);
    imageRewind.setPath(pathRewind);
    juce::FillType ft (juce::Colours::white);
    imageRewind.setFill(ft);
    b->setImages(&imageRewind);
  }

  /** Internal button drawing. **/

  void drawBack(juce::DrawableButton* b)
  {
    juce::DrawablePath imageBack;
    juce::Path pathBack;
    pathBack.addTriangle(0,0,0,2.0f,-1.2f,1.0f);
    pathBack.addTriangle(1.2f,0,1.2f,2.0f,0,1.0f);
    imageBack.setPath(pathBack);
    juce::FillType ft (juce::Colours::white);
    imageBack.setFill(ft);
    b->setImages(&imageBack);
  }
  
  /** Internal button drawing. **/

  void drawPlay(juce::DrawableButton* b)
  {
    juce::DrawablePath imagePlay;
    juce::Path pathPlay;
    pathPlay.addTriangle(0,0,0,2.0f,1.2f,1.0f);
    imagePlay.setPath(pathPlay);
    juce::FillType ft (juce::Colours::white);
    imagePlay.setFill(ft);
    b->setImages(&imagePlay);
  }
  
  /** Internal button drawing. **/

  void drawPause(juce::DrawableButton* b)
  {
    juce::DrawablePath imagePause;
    juce::Path pathPause;
    pathPause.addRectangle(0,0,0.3f,1.0f);
    pathPause.addRectangle(0.6f,0,0.3f,1.0f);
    imagePause.setPath(pathPause);
    juce::FillType ft (juce::Colours::white);
    imagePause.setFill(ft);
    b->setImages(&imagePause);
  }
  
  /** Internal button drawing. **/

  void drawForward(juce::DrawableButton* b)
  {
    juce::DrawablePath imageForward;
    juce::Path pathForward;
    pathForward.addTriangle(0,0,0,2.0f,1.2f,1.0f);
    pathForward.addTriangle(-1.2f,0,-1.2f,2.0f,0,1.0f);
    imageForward.setPath(pathForward);
    juce::FillType ft (juce::Colours::white);
    imageForward.setFill(ft);
    b->setImages(&imageForward);
  }
    
  /** Internal button drawing. **/

  void drawGoToEnd(juce::DrawableButton* b)
  {
    juce::DrawablePath imageGoToEnd;
    juce::Path pathGoToEnd;
    pathGoToEnd.addTriangle(-1.4f, 0, -1.4f,2.0f, -0.2f,1.0f);
    pathGoToEnd.addRectangle(0.1f, 0, 0.3f, 2.0f);
    imageGoToEnd.setPath(pathGoToEnd);
    juce::FillType ft (juce::Colours::white);
    imageGoToEnd.setFill(ft);
    b->setImages(&imageGoToEnd);
  }

};

#endif
