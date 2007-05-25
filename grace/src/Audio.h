#ifndef __AUDIO__
#define __AUDIO__

#include "juce.h"

class AudioMidiWindow : public DocumentWindow
{
public:
  
  AudioMidiWindow();
  ~AudioMidiWindow();
  
  void closeButtonPressed();
};

#endif
