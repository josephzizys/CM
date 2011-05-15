/*=======================================================================*
  This program is free software; you can redistribute it and/or modify
  it under the terms of the Lisp Lesser Gnu Public License. The text
  of this agreement is available at http://www.cliki.net/LLGPL
 *=======================================================================*/

#ifndef Transport_h
#define Transport_h

#include "juce.h"

/** A component for controlling audio/midi playback. Based on Andrew
    Burnson's original Transport class in Chorale Composer I. A
    Tranport provides 5 buttons: Rewind, Back, Play/Pause, Forward,
    GoToEnd and a slider for scrolling through the playback
    sequence. To create a Transport just pass it a Transport::Listener
    with the required play() pause() and positionChanged() callbacks
    implemented. These methods will be called whenever the user clicks
    on the Transport's components.  The Transport can also be trigger
    procedurally from other objects running in the main message thread
    by calling the underlying setPlaying(), setPausing() and
    setPlaybackPosition() methods.  To trigger transport actions from other
    threads use the sendMessage() method. **/

class Transport : public Component, 
  public AsyncUpdater,
  public ButtonListener,
  public SliderListener
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
    SetPlaying, SetPausing, SetPlaybackPosition
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
  };
  
 Transport (Listener& transportListener)
   : listener(transportListener),
    buttonRewind(0),
    buttonBack(0),
    buttonPlayPause(0),
    buttonForward(0),
    buttonGoToEnd(0),
    sliderPosition(0),
    buttonWidth(44),
    buttonHeight(24),
    buttonColor (Colour(90,90,120)),
    toggleColor (Colour(60,60,180)),
    playing(false)
    {
      int connectLeft = Button::ConnectedOnLeft;
      int connectBoth = Button::ConnectedOnLeft | Button::ConnectedOnRight;
      int connectRight = Button::ConnectedOnRight;     
      DrawableButton::ButtonStyle buttonStyle = DrawableButton::ImageOnButtonBackground;
      
      addAndMakeVisible(buttonRewind = new DrawableButton(String("Rewind"), buttonStyle));
      buttonRewind->setBackgroundColours(buttonColor, toggleColor);
      buttonRewind->setConnectedEdges(connectRight);
      drawRewind(buttonRewind);
      buttonRewind->addListener(this);
	
      addAndMakeVisible(buttonBack = new DrawableButton(String("Back"), buttonStyle));
      buttonBack->setBackgroundColours(buttonColor, toggleColor);
      buttonBack->setConnectedEdges(connectBoth);
      drawBack(buttonBack);
      buttonBack->addListener(this);
	
      addAndMakeVisible(buttonPlayPause = new DrawableButton(String("PlayPause"), buttonStyle));
      buttonPlayPause->setBackgroundColours(buttonColor, toggleColor);
      buttonPlayPause->setConnectedEdges(connectBoth);
      drawPlay(buttonPlayPause);
      buttonPlayPause->addListener(this);
	
      addAndMakeVisible(buttonForward = new DrawableButton(String("Forward"), buttonStyle));
      buttonForward->setBackgroundColours(buttonColor, toggleColor);
      buttonForward->setConnectedEdges(connectBoth);
      drawForward(buttonForward);
      buttonForward->addListener(this);

      addAndMakeVisible(buttonGoToEnd = new DrawableButton(String("GoToEnd"), buttonStyle));
      buttonGoToEnd->setBackgroundColours(buttonColor, toggleColor);
      buttonGoToEnd->setConnectedEdges(connectLeft);
      drawGoToEnd(buttonGoToEnd);
      buttonGoToEnd->addListener(this);
	
      addAndMakeVisible(sliderPosition = new Slider(String("Position")));
      sliderPosition->setSliderStyle(Slider::LinearHorizontal);
      sliderPosition->setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
      sliderPosition->setColour(Slider::thumbColourId,buttonColor);
      sliderPosition->setRange(0, 1.0);
      sliderPosition->addListener(this);
      setVisible(true);
      // autosize the transport to width of 5 buttons and height of 2
      // lines with 4px margins all around
      setSize((buttonWidth*5)+8, (buttonHeight*2)+8);
    }
  
  ~Transport()
  {
    delete buttonRewind;
    delete buttonBack;
    delete buttonPlayPause;
    delete buttonForward;
    delete buttonGoToEnd;
    delete sliderPosition;
  }

 /** Returns true if the transport' state is set to playing otherwise
     false. This method is not thread safe. **/

  bool isPlaying()
  {
    return playing;
  }

  /** Sets the playback position as a normalized value 0.0 to 1.0. If
      triggerAction is true then the positionChanged() callback will
      be triggred. This method is not thread safe, use sendMessage()
      for that. **/

  void setPlaybackPosition(double position, bool triggerAction=true)
  {
    if (position<0.0) position=0.0;
    else if (position>1.0) position=1.0;
    sliderPosition->setValue(position, triggerAction, false);
  }

  void incrementPlaybackPosition(double delta, bool triggerAction=true)
  {
    setPlaybackPosition(sliderPosition->getValue()+delta);
  }

  /** Returns the position of the slider on a normalized scale 0.0 to
      1.0. This function is not thread safe. **/

  double getPlaybackPosition(void)
  {
    return sliderPosition->getValue();
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
      listener.play(getPlaybackPosition());
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
      listener.pause();
    }
  }

  /** Implements thread-safe transport control. id
      is a message id, one of the button enums defined at the top of
      this file. The rest af the args are any data you need to
      pass. **/ 

  void sendMessage(int id, double d=0.0, int i=0, bool b=false)
  {
    ScopedLock mylock(messages.getLock());
    messages.add(new TransportMessage(id, d, i, b));
    triggerAsyncUpdate();
  }

 private:

  bool playing;
  Listener& listener; 
  DrawableButton* buttonPlayPause;
  DrawableButton* buttonRewind;
  DrawableButton* buttonBack;
  DrawableButton* buttonForward;
  DrawableButton* buttonGoToEnd;
  Slider*         sliderPosition;
  int buttonWidth;
  int buttonHeight;
  Colour buttonColor;
  Colour toggleColor;

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

  OwnedArray<TransportMessage, CriticalSection> messages;

  void handleAsyncUpdate ()
  {
    ScopedLock mylock(messages.getLock());
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
    int buttonTop=(viewHeight/2)-buttonHeight;
    buttonRewind->setBounds(buttonLeft, buttonTop, buttonWidth, buttonHeight);
    buttonBack->setBounds(buttonLeft + buttonWidth, buttonTop, buttonWidth, buttonHeight);      
    buttonPlayPause->setBounds(buttonLeft + (buttonWidth*2), buttonTop, buttonWidth, buttonHeight);
    buttonForward->setBounds(buttonLeft + (buttonWidth*3), buttonTop, buttonWidth, buttonHeight);
    buttonGoToEnd->setBounds(buttonLeft + (buttonWidth*4), buttonTop, buttonWidth, buttonHeight);    
    sliderPosition->setBounds(buttonLeft, buttonTop + buttonHeight, (buttonWidth*5), buttonHeight);
  }

  /** Internal function implements button clicked actions. **/

  virtual void buttonClicked(Button* button)
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
  
  /** Internal function implements slider moved actions by calling the
      source's postionChanged() method. **/

  virtual void sliderValueChanged(Slider *slider)
  {
    if (slider == sliderPosition)
      listener.positionChanged(sliderPosition->getValue(), isPlaying());
  }
 
  /** Internal button drawing. **/

  void drawRewind(DrawableButton* b)
  {
    DrawablePath imageRewind;
    Path pathRewind;
    pathRewind.addRectangle(-1.8f,0,0.3f,2.0f);
    pathRewind.addTriangle(0,0, 0,2.0f, -1.2f,1.0f);
    imageRewind.setPath(pathRewind);
    FillType ft (Colours::white);
    imageRewind.setFill(ft);
    b->setImages(&imageRewind);
  }

  /** Internal button drawing. **/

  void drawBack(DrawableButton* b)
  {
    DrawablePath imageBack;
    Path pathBack;
    pathBack.addTriangle(0,0,0,2.0f,-1.2f,1.0f);
    pathBack.addTriangle(1.2f,0,1.2f,2.0f,0,1.0f);
    imageBack.setPath(pathBack);
    FillType ft (Colours::white);
    imageBack.setFill(ft);
    b->setImages(&imageBack);
  }
  
  /** Internal button drawing. **/

  void drawPlay(DrawableButton* b)
  {
    DrawablePath imagePlay;
    Path pathPlay;
    pathPlay.addTriangle(0,0,0,2.0f,1.2f,1.0f);
    imagePlay.setPath(pathPlay);
    FillType ft (Colours::white);
    imagePlay.setFill(ft);
    b->setImages(&imagePlay);
  }
  
  /** Internal button drawing. **/

  void drawPause(DrawableButton* b)
  {
    DrawablePath imagePause;
    Path pathPause;
    pathPause.addRectangle(0,0,0.3f,1.0f);
    pathPause.addRectangle(0.6f,0,0.3f,1.0f);
    imagePause.setPath(pathPause);
    FillType ft (Colours::white);
    imagePause.setFill(ft);
    b->setImages(&imagePause);
  }
  
  /** Internal button drawing. **/

  void drawForward(DrawableButton* b)
  {
    DrawablePath imageForward;
    Path pathForward;
    pathForward.addTriangle(0,0,0,2.0f,1.2f,1.0f);
    pathForward.addTriangle(-1.2f,0,-1.2f,2.0f,0,1.0f);
    imageForward.setPath(pathForward);
    FillType ft (Colours::white);
    imageForward.setFill(ft);
    b->setImages(&imageForward);
  }
    
  /** Internal button drawing. **/

  void drawGoToEnd(DrawableButton* b)
  {
    DrawablePath imageGoToEnd;
    Path pathGoToEnd;
    pathGoToEnd.addTriangle(-1.4f,0, -1.4f,2.0f, -0.2,1.0f);
    pathGoToEnd.addRectangle(0.1f,0, 0.3f,2.0f);
    imageGoToEnd.setPath(pathGoToEnd);
    FillType ft (Colours::white);
    imageGoToEnd.setFill(ft);
    b->setImages(&imageGoToEnd);
  }

};

#endif
