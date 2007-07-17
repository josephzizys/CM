/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

#ifndef RESOURCES
#define RESOURCES

#include "juce.h"

enum GraceWindowType {winConsole=1, winEditor, winPlotter};

// ENUMS defined in grace.lisp

enum SharedCommand {
  cmdWindowSelect = 130816,
  cmdWindowNative = 131072,
  cmdWindowConsole = 131328,
  cmdHelpWindow = 131584,
  cmdHelpSalTutorial = 131840,
  cmdHelpURL = 132096,
  cmdHelpAboutGrace = 132352};

void addCommonWindowItems(PopupMenu* menu, GraceWindowType w);
void addCommonHelpItems(PopupMenu* menu, GraceWindowType w);
void commonWindowItemSelected(int cmd, int arg);
void commonHelpItemSelected(int cmd, int arg);

File getGraceResourceDirectory ();
int getHostOS();
bool isHostWindows();
bool isHostLinux();
bool isHostMacOSX();

class SplashComponent : public Component {
 public:
  Image * logo;
  static const char* grace_png;
  static const int grace_pngSize;

  SplashComponent() {
    setName("splash");
    logo = ImageCache::getFromMemory(grace_png,grace_pngSize);
  }
  ~SplashComponent() {delete logo;}

  void paint(Graphics& g) {
    //g.fillAll(Colours::yellow);
    g.fillAll(Colours::black);
    g.drawImage(logo,0,0,getWidth(), getHeight(),
		0,0,getWidth(), getHeight(), false);
  }

  void close() {
    setVisible(false);
    setSize(0,0);
    getParentComponent()->removeChildComponent(this);
  }    

  void mouseDown (const MouseEvent &e) {
    close();
  }
};


class GraceSplash  : public SplashScreen
{
public:
  GraceSplash () {};
  ~GraceSplash();
  // Binary resources:
  static const char* grace_png;
  static const int grace_pngSize;

  //    void paint (Graphics& g);
  //    void resized();
  //    juce_UseDebuggingNewOperator
  //private:
  //    GraceSplash (const GraceSplash&);
  //    const GraceSplash& operator= (const GraceSplash&);
};

#endif 
