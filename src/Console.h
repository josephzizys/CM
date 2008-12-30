/*=======================================================================*
  Copyright (C) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#ifndef CONSOLE_H
#define CONSOLE_H

#include "juce.h"
#include "Messages.h"
#include <iostream>

class ConsoleTheme
{
  static const int NUMCOLORS=9;
  String name;
  Colour colors[NUMCOLORS];
  
 public:
  enum {bgColor, inputColor, outputColor, errorColor, warningColor,
	valuesColor, hiliteColor, hiliteTextColor, caretColor};
  ConsoleTheme(String n, Colour b, Colour i, Colour o, Colour e,
	       Colour w, Colour v, Colour h, Colour t, Colour c)
    {
      name=n;
      colors[bgColor]=b;
      colors[inputColor]=i;
      colors[outputColor]=o;
      colors[errorColor]=e;
      colors[warningColor]=w;
      colors[valuesColor]=v;
      colors[hiliteColor]=h;
      colors[hiliteTextColor]=t;
      colors[caretColor]=c;
    }
  ~ConsoleTheme() 
    {
    }
  String getName()
  {
    return name;
  }
  Colour getColor(int i)
  {
    return colors[i];
  }
};

class Console :
#ifdef GRACE
    public Component, public ApplicationCommandTarget ,
#endif
    public AsyncUpdater
{
 private:

  class ConsoleMessage
  {
  public:
    int type;
    String text;
    int data;
    ConsoleMessage(int typ)
      {
	type=typ;
	text=String::empty;
	data=0;
    }
    ConsoleMessage(int typ, int dat)
      {
	type=typ;
	data=dat;
	text=String::empty;
      }
    ConsoleMessage(int typ, String txt)
      {
	type=typ;
	text=txt;
	data=0;
      }
    ConsoleMessage(int typ, int dat, String txt)
      {
	type=typ;
	text=txt;
	data=dat;
      }
    ~ConsoleMessage() {}
  };
  
  ConsoleTheme* theme;
  CriticalSection lock;
  String prompt;
  OwnedArray<AsyncMessage, CriticalSection> messages;
 public:

 Console();
  ~Console();

  TextEditor* buffer;  // ONLY USED IN GRACE
  ApplicationCommandManager* manager;

  void display(String str, Colour color);
  void printPrompt(bool trigger=true);
  void setPrompt(String str);
  void setTheme(ConsoleTheme* theme);
  void printOutput(String str, bool trigger=true);
  void printOutput(char* str, bool trigger=true);
  void printValues(String str, bool trigger=true); 
  void printValues(char* str, bool trigger=true); 
  void printWarning(String str, bool trigger=true);
  void printWarning(char* str, bool trigger=true);
  void printError(String str, bool trigger=true);
  void printError(char* str, bool trigger=true);
  void printPrompt(String str, bool trigger=true);
  void printPrompt(char* str, bool trigger=true);
  void postAsyncMessage(int typ, bool trigger);
  void postAsyncMessage(int typ, String msg, bool trigger);
  void postAsyncMessage(int typ, int msg,  bool trigger);
  void handleAsyncUpdate() ;

#ifdef GRACE
  Font getFont();
  void setFont(Font font);
  int getFontSize();
  void setFontSize(int size);
  void resized() {buffer->setSize(getWidth(),getHeight());}
  void paint (Graphics& g) {g.fillAll (Colours::transparentBlack); }
  // these are implemented in Command.cpp
  ApplicationCommandTarget* getNextCommandTarget();
  void getAllCommands(Array<CommandID>& commands);
  void getCommandInfo(const CommandID id, ApplicationCommandInfo& info);
  bool perform(const ApplicationCommandTarget::InvocationInfo& info);
#endif

  juce_DeclareSingleton (Console, true)

};

#ifdef GRACE
class ConsoleWindow : public DocumentWindow , public MenuBarModel
{

  /**  class Splash : public Component
  {
    Image* logo;
  public:
    Splash::Splash (Image* img)
      {
	logo=img;
      }
    ~Splash()
      {
	delete logo;
      }
    void paint(Graphics& g)
    {
      g.fillAll(Colours::black);
      g.drawImage(logo,0,0,getWidth(), getHeight(),
		  0, 0, getWidth(), getHeight(), false);
    }
    void close() 
    {
      setVisible(false);
      setSize(0,0);
      getParentComponent()->removeChildComponent(this);
    }    
    void mouseDown (const MouseEvent &e)
    {
      close();
    }
  };

  Splash* splash; **/

 public:
  ConsoleWindow () ;
  ~ConsoleWindow () ;
  void closeButtonPressed () ;
  const StringArray getMenuBarNames ();
  const PopupMenu getMenuForIndex (int idx, const String &name);
  void menuItemSelected (int id, int idx);
};
#endif

#endif

