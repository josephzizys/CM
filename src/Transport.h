#ifndef Transport_h
#define Transport_h

#include "juce.h"

class Transport : public AsyncUpdater,
  public ButtonListener,
  public SliderListener

{
 public:

  enum 
  {
    RewindButton=1, BackButton, PlayPauseButton, ForwardButton, GoToEndButton,
    PlayButton, StopButton, SliderButton,
    SetPlaying, SetPausing, SetSliderPosition
  };

  //The following need to be overridden in a subclass.

  virtual void play(double position) = 0;
  virtual void pause(void) = 0;
  virtual void positionChanged(double position, bool isPlaying) = 0;
  
 Transport()
   : buttonRewind(0), buttonBack(0), buttonPlayPause(0), buttonForward(0), buttonGoToEnd(0),
    sliderPosition(0), playing(false)
  {
    buttonColor = Colour(90,90,120);
    toggleColor = Colour(60,60,180);
	
    int connectLeft = Button::ConnectedOnLeft;
    int connectBoth = Button::ConnectedOnLeft | Button::ConnectedOnRight;
    int connectRight = Button::ConnectedOnRight;
      
    DrawableButton::ButtonStyle buttonStyle = DrawableButton::ImageOnButtonBackground;
      
    buttonRewind = new DrawableButton(String("Rewind"), buttonStyle);
    buttonRewind->setBackgroundColours(buttonColor, toggleColor);
    buttonRewind->setConnectedEdges(connectRight);
    drawRewind(buttonRewind);
    buttonRewind->addListener(this);
	
    buttonBack = new DrawableButton(String("Back"), buttonStyle);
    buttonBack->setBackgroundColours(buttonColor, toggleColor);
    buttonBack->setConnectedEdges(connectBoth);
    drawBack(buttonBack);
    buttonBack->addListener(this);
	
    buttonPlayPause = new DrawableButton(String("PlayPause"), buttonStyle);
    buttonPlayPause->setBackgroundColours(buttonColor, toggleColor);
    buttonPlayPause->setConnectedEdges(connectBoth);
    drawPlay(buttonPlayPause);
    buttonPlayPause->addListener(this);
	
    buttonForward = new DrawableButton(String("Forward"), buttonStyle);
    buttonForward->setBackgroundColours(buttonColor, toggleColor);
    buttonForward->setConnectedEdges(connectBoth);
    drawForward(buttonForward);
    buttonForward->addListener(this);

    buttonGoToEnd = new DrawableButton(String("GoToEnd"), buttonStyle);
    buttonGoToEnd->setBackgroundColours(buttonColor, toggleColor);
    buttonGoToEnd->setConnectedEdges(connectLeft);
    drawGoToEnd(buttonGoToEnd);
    buttonGoToEnd->addListener(this);
	
    sliderPosition = new Slider(String("Position"));
    sliderPosition->setSliderStyle(Slider::LinearHorizontal);
    sliderPosition->setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    sliderPosition->setColour(Slider::thumbColourId,buttonColor);
    sliderPosition->addListener(this);
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

  /** push tranport buttons using code. this method is not thread
      safe, use Transport::sendMessage() for that.
   **/

  void pushButton(int buttonId, double data=0.0)
  {
    switch (buttonId)
    {
    case RewindButton :
      buttonRewind->triggerClick();
      break;
    case BackButton :
      buttonBack->triggerClick();
      break;
    case PlayPauseButton : // toggles PlayPauseButton
      buttonPlayPause->triggerClick();
      break;
    case PlayButton :      // sets PlayPauseButton to play
      setPlaying(true);
      break;
    case StopButton :      // sets PlayPause Button to pause
      setPausing(true);
      break;
    case ForwardButton :
      buttonForward->triggerClick();
      break;
    case GoToEndButton :
      buttonGoToEnd->triggerClick();
      break;
    case SetSliderPosition :
      setSliderPosition(data,true);
      break;
    default:
      break;
    }
  }

  /** Posts an asynchronous message to control the transport from
      another thread. Typ is one of the button enums defined at the
      top of this file. The rest af the args are any data you need to
      pass. **/ 

  void sendMessage(int typ, double d=0.0, int i=0, bool b=false)
  {
    ScopedLock mylock(messages.getLock());
    messages.add(new TransportMessage(typ, d, i, b));
    triggerAsyncUpdate();
  }

  /** Returns true if the transport thinks it is playing otherwiswe
      false. This method is not thread safe. **/

  bool isPlaying()
  {
    return playing;
  }

  /** Sets the position of the slider on a scale 0.0 to 1.0. If
      triggerAction is true then the positionChanged() method will be
      called (via setValue) with the position and a boolean flag
      indicating if the transport is currently playing or not. This
      method is not thread safe, use sendMessage() for that. **/

  void setSliderPosition(double position, bool triggerAction=true)
  {
    sliderPosition->setValue(position, triggerAction, false);
  }

  /** Gets the position of the slider on a scale 0.0 to 1.0. this is
      not thread safe **/

  double getPosition(void)
  {
    return sliderPosition->getValue();
  }

  /** Marks transport as playing, displays the "pause" icon for the
      user and calls the play() method if triggerAction is true and
      the transport is not currently playing. This method is not
      thread safe, use sendMessage() for that. **/

  void setPlaying(bool triggerAction=true)
  {
    //std::cout << "in setPlaying, trigger action is " << triggerAction << " playing status was " << playing << "\n";
    bool toggled=(playing==false);
    playing=true;
    drawPause(buttonPlayPause);
    if (triggerAction && toggled)
    {
      //      std::cout << "triggering play...\n";
      play(getPosition());
    }
  }
  
  /** Marks transport as pausing, displays the "play" icon for the
      user and calls the pause() method if triggerAction is true and
      the transport is currently playing. This method is not thread
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
      pause();
    }
  }

  /** Positions the transport buttons. **/

  void setPositions(int x, int y, int buttonWidth, int height)
  {
    int buttonLeft = x;
    buttonRewind->setBounds(buttonLeft, y, buttonWidth, height);      
    buttonBack->setBounds(buttonLeft += buttonWidth, y, buttonWidth, height);      
    buttonPlayPause->setBounds(buttonLeft += buttonWidth, y, buttonWidth, height);
    buttonForward->setBounds(buttonLeft += buttonWidth, y, buttonWidth, height);
    buttonGoToEnd->setBounds(buttonLeft += buttonWidth, y, buttonWidth, height);    
    sliderPosition->setBounds(x, y + height, (buttonLeft += buttonWidth) - x, height);
    sliderPosition->setRange(0, 1.0);
  }
  
  void addAndMakeVisible(Component* parent)
  {
    parent->addAndMakeVisible(buttonRewind);
    parent->addAndMakeVisible(buttonBack);
    parent->addAndMakeVisible(buttonPlayPause);
    parent->addAndMakeVisible(buttonForward);
    parent->addAndMakeVisible(buttonGoToEnd);
    parent->addAndMakeVisible(sliderPosition);
  }

 private:

  bool playing;
  DrawableButton* buttonPlayPause;
  DrawableButton* buttonRewind;
  DrawableButton* buttonBack;
  DrawableButton* buttonForward;
  DrawableButton* buttonGoToEnd;
  Slider*         sliderPosition;
  Colour buttonColor;
  Colour toggleColor;

  /** Support for async messaging from other threads **/

  class TransportMessage
  {
  public:
    int type;
    double double1;
    int int1;
    bool bool1;
    TransportMessage (int typ, double d1, int i1, bool b1)
      : type(typ), double1 (d1), int1 (i1), bool1 (b1)
    {} 
    ~TransportMessage()
    {}
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
      case SetSliderPosition:
        //std::cout << "TransportMessage: SetPosition pos=" << msg->double1 << "\n";
        setSliderPosition(msg->double1, msg->bool1);
        break;
      default:
        break;
      }
    }
    if (size>0)
      messages.clear();
  }

  virtual void buttonClicked(Button* button)
  {
    static bool isShowingPlayNotPause = true;
    
    if(button->getName() == String("PlayPause"))
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
    else if(button->getName() == String("Rewind"))
    {
      sliderPosition->setValue(0);
    }
    else if(button->getName() == String("Back"))
    {
      sliderPosition->setValue(sliderPosition->getValue() - 0.10);
    }
    else if(button->getName() == String("Forward"))
    {
      sliderPosition->setValue(sliderPosition->getValue() + 0.10);
    }
    else if(button->getName() == String("GoToEnd"))
    {
      sliderPosition->setValue(1);
    }
  }
  
  virtual void sliderValueChanged(Slider *slider)
  {
    //'percentage' will be a value from 0 to 1.0, so you just have to
    //multiply it by the length of whatever you have to get the sample.
    double percentage = slider->getValue();
    
    if(slider->getName() == String("Position"))
      positionChanged(percentage, isPlaying());
  }
 
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

  // unused
  void drawStop(DrawableButton* b)
  {
    DrawablePath imageStop;
    Path pathStop;
    pathStop.addRectangle(0,0,1.0f,1.0f);
    imageStop.setPath(pathStop);
    {
      FillType ft (Colours::white);
      imageStop.setFill(ft);
    }
    b->setImages(&imageStop);
  }

};


#endif
