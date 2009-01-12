#ifndef Transport_h
#define Transport_h

#include "juce.h"

class Transport
{
  //--------------------------------------//
  //All you need to know is in these lines//
  //--------------------------------------//
 public:
  //The following need to be overridden in a subclass.
  virtual void play(double position) = 0;
  virtual void pause(void) = 0;
  virtual void positionChanged(double position, bool isPlaying) = 0;
  
  enum {RewindButton=1, BackButton, PlayFromBeginningButton, PlayPauseButton, 
	StopButton, ForwardButton, PlayRepeatsButton};

  void pushButton(int buttonId)
  {
    switch (buttonId)
      {
      case RewindButton :
	buttonRewind->triggerClick();
	break;
      case BackButton :
	buttonBack->triggerClick();
	break;
      case PlayFromBeginningButton :
	buttonPlayFromBeginning->triggerClick();
	break;
      case PlayPauseButton :
	buttonPlayPause->triggerClick();
	break;
      case StopButton :
	buttonStop->triggerClick();
	break;
      case ForwardButton :
	buttonForward->triggerClick();
	break;
      case PlayRepeatsButton :
	buttonPlayRepeats->triggerClick();
	break;
      default:
	break;
      }
  }
  //----------------------------------------//
  //You can ignore the rest of the internals//
  //----------------------------------------//
 private:
  Slider*         sliderPosition; //Ignore this...
 public:
  //Sets the position of the slider on a scale 0.0 to 1.0
  //(does not trigger positionChanged to be called).
  void setPosition(double position){sliderPosition->setValue(position,false);}
  //Gets the position of the slider on a scale 0.0 to 1.0.
  double getPosition(void){return sliderPosition->getValue();}
 public:
  //Forward declarations for subclasses...
  class Listener;
  class PlaybackListener;
 private:
  DrawableButton* buttonRewind;
  DrawableButton* buttonBack;
  DrawableButton* buttonPlayFromBeginning;
  DrawableButton* buttonPlayPause;
  DrawableButton* buttonStop;
  DrawableButton* buttonForward;
  DrawableButton* buttonPlayRepeats;

  Listener* buttonListener;
  PlaybackListener* playbackListener;
  
  Colour buttonColor;
  Colour toggleColor;
  
  void drawRewind(DrawableButton* b)
  {
    DrawablePath imageRewind;
    Path pathRewind;
    pathRewind.addRectangle(-1.8f,0,0.3f,2.0f);
    pathRewind.addTriangle(0,0,0,2.0f,-1.2f,1.0f);
    imageRewind.setPath(pathRewind);
    imageRewind.setSolidFill(Colours::white);
    b->setImages(&imageRewind);
  }
  
  void drawBack(DrawableButton* b)
  {
    DrawablePath imageBack;
    Path pathBack;
    pathBack.addTriangle(0,0,0,2.0f,-1.2f,1.0f);
    pathBack.addTriangle(1.2f,0,1.2f,2.0f,0,1.0f);
    imageBack.setPath(pathBack);
    imageBack.setSolidFill(Colours::white);
      b->setImages(&imageBack);
  }
  
  void drawPlayFromBeginning(DrawableButton* b)
  {
    DrawablePath imagePlayFromBeginning;
    Path pathPlayFromBeginning;
    pathPlayFromBeginning.addTriangle(0,0,0,2.0f,1.2f,1.0f);
    pathPlayFromBeginning.addRectangle(-0.6f,0,0.3f,2.0f);
    imagePlayFromBeginning.setPath(pathPlayFromBeginning);
    imagePlayFromBeginning.setSolidFill(Colours::white);
    b->setImages(&imagePlayFromBeginning);
  }
  
  void drawPlay(DrawableButton* b)
  {
    DrawablePath imagePlay;
    Path pathPlay;
    pathPlay.addTriangle(0,0,0,2.0f,1.2f,1.0f);
    imagePlay.setPath(pathPlay);
    imagePlay.setSolidFill(Colours::white);
    b->setImages(&imagePlay);
  }
  
  void drawPause(DrawableButton* b)
  {
    DrawablePath imagePause;
    Path pathPause;
    pathPause.addRectangle(0,0,0.3f,1.0f);
    pathPause.addRectangle(0.6f,0,0.3f,1.0f);
    imagePause.setPath(pathPause);
    imagePause.setSolidFill(Colours::white);
    b->setImages(&imagePause);
  }
  
  void drawStop(DrawableButton* b)
  {
    DrawablePath imageStop;
    Path pathStop;
    pathStop.addRectangle(0,0,1.0f,1.0f);
    imageStop.setPath(pathStop);
    imageStop.setSolidFill(Colours::white);
    b->setImages(&imageStop);
  }
  
  void drawForward(DrawableButton* b)
  {
    DrawablePath imageForward;
    Path pathForward;
    pathForward.addTriangle(0,0,0,2.0f,1.2f,1.0f);
    pathForward.addTriangle(-1.2f,0,-1.2f,2.0f,0,1.0f);
    imageForward.setPath(pathForward);
    imageForward.setSolidFill(Colours::white);
    b->setImages(&imageForward);
  }
  
  void drawPlayRepeats(DrawableButton* b)
  {
    DrawablePath imagePlayRepeats;
    Path pathPlayRepeats;
    pathPlayRepeats.addRectangle(0,0,0.1f,1.0f);
    pathPlayRepeats.addRectangle(0.2f,0,0.2f,1.0f);
    pathPlayRepeats.addEllipse(-0.4f,0.25f,0.2f,0.2f);
    pathPlayRepeats.addEllipse(-0.4f,0.75f,0.2f,0.2f);
    imagePlayRepeats.setPath(pathPlayRepeats);
    imagePlayRepeats.setSolidFill(Colours::white);
    b->setImages(&imagePlayRepeats);
  }
  
 public:
  
  void setPositions(int x, int y, int buttonWidth, int height)
  {
    int buttonLeft = x;
    buttonRewind->setBounds(buttonLeft, y, buttonWidth, height);      
    buttonBack->setBounds(buttonLeft += buttonWidth, y, buttonWidth, height);      
    buttonPlayFromBeginning->setBounds(buttonLeft += buttonWidth, y, 
				       buttonWidth, height);      
    buttonPlayPause->setBounds(buttonLeft += buttonWidth, y, buttonWidth,
			       height);
    buttonStop->setBounds(buttonLeft += buttonWidth, y, buttonWidth, height);
    buttonForward->setBounds(buttonLeft += buttonWidth, y, buttonWidth,
			     height);
    
    sliderPosition->setBounds(x, y + height, (buttonLeft += buttonWidth) - x, 
			      height);
    sliderPosition->setRange(0, 1.0);
  }
  
  void addAndMakeVisible(Component* parent)
  {
    parent->addAndMakeVisible(buttonRewind);
    parent->addAndMakeVisible(buttonBack);
    parent->addAndMakeVisible(buttonPlayFromBeginning);
    parent->addAndMakeVisible(buttonPlayPause);
    parent->addAndMakeVisible(buttonStop);
    parent->addAndMakeVisible(buttonForward);
    parent->addAndMakeVisible(buttonPlayRepeats);
    parent->addAndMakeVisible(sliderPosition);
  }
  
 Transport() : buttonRewind(0), buttonBack(0), buttonPlayFromBeginning(0), 
    buttonPlayPause(0), buttonStop(0), buttonForward(0), buttonPlayRepeats(0), 
    sliderPosition(0)
      {
	buttonListener = new Listener(this);
	playbackListener = new PlaybackListener(this);
	
	buttonColor = Colour(90,90,120);
	toggleColor = Colour(60,60,180);
	
	int connectLeft = Button::ConnectedOnLeft;
	int connectBoth = Button::ConnectedOnLeft | 
	  Button::ConnectedOnRight;
	int connectRight = Button::ConnectedOnRight;
	
	DrawableButton::ButtonStyle buttonStyle = 
	  DrawableButton::ImageOnButtonBackground;
	
	buttonRewind = new DrawableButton(String("Rewind"), buttonStyle);
	buttonRewind->setBackgroundColours(buttonColor, toggleColor);
	buttonRewind->setConnectedEdges(connectRight);
	drawRewind(buttonRewind);
	buttonRewind->addButtonListener(buttonListener);
	
	buttonBack = new DrawableButton(String("Back"), buttonStyle);
	buttonBack->setBackgroundColours(buttonColor, toggleColor);
	buttonBack->setConnectedEdges(connectBoth);
	drawBack(buttonBack);
	buttonBack->addButtonListener(buttonListener);
	
	buttonPlayFromBeginning = new DrawableButton(String("PlayFromBeginning"),
						     buttonStyle);
	buttonPlayFromBeginning->setBackgroundColours(buttonColor, toggleColor);
	buttonPlayFromBeginning->setConnectedEdges(connectBoth);
	drawPlayFromBeginning(buttonPlayFromBeginning);
	buttonPlayFromBeginning->addButtonListener(buttonListener);
	
	buttonPlayPause = new DrawableButton(String("PlayPause"), buttonStyle);
	buttonPlayPause->setBackgroundColours(buttonColor, toggleColor);
	buttonPlayPause->setConnectedEdges(connectBoth);
	drawPlay(buttonPlayPause);
	buttonPlayPause->addButtonListener(buttonListener);
	
	buttonStop = new DrawableButton(String("Stop"), buttonStyle);
	buttonStop->setBackgroundColours(buttonColor, toggleColor);
	buttonStop->setConnectedEdges(connectBoth);
	drawStop(buttonStop);
	buttonStop->addButtonListener(buttonListener);
	
	buttonForward = new DrawableButton(String("Forward"), buttonStyle);
	buttonForward->setBackgroundColours(buttonColor, toggleColor);
	buttonForward->setConnectedEdges(connectLeft);
	drawForward(buttonForward);
	buttonForward->addButtonListener(buttonListener);
	
	sliderPosition = new Slider(String("Position"));
	sliderPosition->setSliderStyle(Slider::LinearHorizontal);
	sliderPosition->setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	sliderPosition->setColour(Slider::thumbColourId,buttonColor);
	sliderPosition->addListener(playbackListener);
      }
  
  ~Transport()
    {
      delete buttonListener;
      delete playbackListener;
      
      delete buttonRewind;
      delete buttonBack;
      delete buttonPlayFromBeginning;
      delete buttonPlayPause;
      delete buttonStop;
      delete buttonForward;
      delete buttonPlayRepeats;
      delete sliderPosition;
    }

  friend class PlaybackListener;
  class PlaybackListener : public SliderListener
  {
    Transport* transport;
  public:
  PlaybackListener(Transport* parent) : transport(parent) {}
    
    virtual void sliderValueChanged(Slider *slider)
    {
      //'percentage' will be a value from 0 to 1.0, so you just have to
      //multiply it by the length of whatever you have to get the sample.
      double percentage = slider->getValue();
      
      if(slider->getName() == String("Position"))
	transport->positionChanged(percentage,
				   transport->buttonListener->isPlaying());
    }
  };
  
  friend class Listener;
  class Listener : public ButtonListener
  {
    Transport* transport;
    bool playing;
  public:
  Listener(Transport* parent) : transport(parent), playing(false) {}
    virtual void buttonStateChanged(Button *button) {}
    bool isPlaying(void) {return playing;}
    
    virtual void buttonClicked(Button* button)
    {
      static bool isShowingPlayNotPause = true;
      
      if(button->getName() == String("PlayPause"))
        {
          //Toggle the play/pause button.
          isShowingPlayNotPause = !isShowingPlayNotPause;
	  
          if(isShowingPlayNotPause)
	    {
	      //Change the graphic to a play button.
	      transport->drawPlay(transport->buttonPlayPause);
	      playing=false; // hkt: isPlaying() => false
	      //Trigger pause event.
	      transport->pause();
	    }
          else
	    {
	      //Change the graphic to a pause button.
	      transport->drawPause(transport->buttonPlayPause);
	      playing=true; // hkt: isPlaying() => true
	      //Trigger play event.
	      transport->play(transport->getPosition());
	    }
        }
      else if(button->getName() == String("Stop"))
        {
          //Instead of repeating logic/graphics code, just call the button click
          //events to get the desired result.
          if(!isShowingPlayNotPause)
            transport->buttonPlayPause->triggerClick(); //Pause playback.
          if(transport->sliderPosition->getValue() != 0)
            transport->buttonRewind->triggerClick(); //Rewind.
        }
      else if(button->getName() == String("Rewind"))
        {
          transport->sliderPosition->setValue(0);
        }
      else if(button->getName() == String("Back"))
        {
          transport->sliderPosition->setValue(
					      transport->sliderPosition->getValue() - 0.05);
        }
      else if(button->getName() == String("Forward"))
        {
          transport->sliderPosition->setValue(
					      transport->sliderPosition->getValue() + 0.05);
        }
      else if(button->getName() == String("PlayFromBeginning"))
        {
          //Instead of repeating logic/graphics code, just call the button click
          //events to get the desired result.
          if(transport->sliderPosition->getValue() != 0)
            transport->buttonRewind->triggerClick(); //Rewind.
          if(isShowingPlayNotPause)
            transport->buttonPlayPause->triggerClick(); //Resume playback.
        }
    }
  };
};

#endif
