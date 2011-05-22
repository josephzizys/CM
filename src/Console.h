/*=======================================================================*
  Copyright (C) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#ifndef Console_h
#define Console_h

#include "Libraries.h"
#include "Messages.h"

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
  public Component, 
  public FileDragAndDropTarget,
  public ApplicationCommandTarget ,
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
  OwnedArray<ConsoleTheme> themes;
  CriticalSection lock;
  String prompt;
  OwnedArray<AsyncMessage, CriticalSection> messages;
 public:

 Console();
  ~Console();

  static Console* globalInstance;

  static Console* getInstance(void)
    {
      return globalInstance;
    }

  TextEditor* buffer;  // ONLY USED IN GRACE
  ApplicationCommandManager* manager;
  bool isEvaling;
  
  void display(String str, Colour color);
  void clearConsole();
  void printPrompt(bool trigger=true);
  void setPrompt(String str);
  Colour getConsoleColor(int id);
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
  String supportedfiletypes;
  String getSupportedFileTypes();
  bool isSupportedFileType(String path);
  bool isSupportedFileType(File file);
  void setEvaling(bool evaling);
#ifdef GRACE
  void initThemes();
  int numThemes();
  void setTheme(String name);
  void setTheme(int index);
  String getThemeName(int index);
  bool isCurrentTheme(int index);
  Font getFont();
  void setFont(Font font);
  int getFontSize();
  void setFontSize(int size);
  void resized(); //{buffer->setSize(getWidth(),getHeight());}
  void paint (Graphics& g);// {g.fillAll (Colours::transparentBlack); }
  // these are implemented in Command.cpp
  ApplicationCommandTarget* getNextCommandTarget();
  void getAllCommands(Array<CommandID>& commands);
  void getCommandInfo(CommandID id, ApplicationCommandInfo& info);
  bool perform(const ApplicationCommandTarget::InvocationInfo& info);
  bool getBeepOnError();
  void setBeepOnError(bool b);
  bool isInterestedInFileDrag (const StringArray &files);
  void filesDropped (const StringArray &files, int x, int y);
#endif
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

  // David Psenicka
  // This must be here for FOMUS's documentation to work!
  TooltipWindow xxx;

 public:
  ConsoleWindow () ;
  virtual ~ConsoleWindow () ;
  void closeButtonPressed () ;
  const StringArray getMenuBarNames ();
  const PopupMenu getMenuForIndex (int idx, const String &name);
  void menuItemSelected (int id, int idx);
};
#endif

#endif

