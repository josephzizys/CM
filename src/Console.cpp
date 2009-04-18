/*=======================================================================*
  Copyright (C) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#include "Enumerations.h"
#include "Console.h"
#include "Scheme.h"
#include "Midi.h"
#include "Preferences.h"
#ifdef GRACE
#include "Commands.h"
#include "Audio.h"
#include "Images.h"
#endif

#include <iostream>

juce_ImplementSingleton(Console)

Console::Console()
  : prompt (String::empty),
    theme (NULL),
    buffer (NULL),
    manager (NULL)
{
  // GUI initialization code is done by window
}

Console::~Console() 
{
  messages.clear();
  // BUFFER ALREADY DELEATED BY WINDOW CLOSE
  if (theme!=NULL)
    {
      delete theme;
    }
  if (manager!=NULL)
    {
      delete manager; 
    }
}

void Console::setTheme(ConsoleTheme* th)
{
  theme=th;
  buffer->setColour(TextEditor::backgroundColourId, 
		    theme->getColor(ConsoleTheme::bgColor) );
  buffer->setColour( TextEditor::textColourId,
                    theme->getColor(ConsoleTheme::outputColor));
  buffer->setColour( TextEditor::highlightColourId,
                    theme->getColor(ConsoleTheme::hiliteColor));
  buffer->setColour( TextEditor::highlightedTextColourId,
                    theme->getColor(ConsoleTheme::hiliteTextColor));
  buffer->setColour( TextEditor::caretColourId,
                    theme->getColor(ConsoleTheme::caretColor));
  buffer->applyFontToAllText(buffer->getFont());
}

void Console::setPrompt(String str)
{
  prompt=str;
}

void Console::display(String str, Colour color)
{
#ifdef GRACE
  buffer->setCaretPosition(0xFFFFFF);
  buffer->setColour(TextEditor::textColourId, color);
  //std::cout<< "inserting '" << str.toUTF8() << "'\n";
  buffer->insertTextAtCursor(str);
#else
  std::cout << str.toUTF8() <<  std::flush;
#endif
}


/* 
 * Console text output methods are thread safe text printers -- call
 * them from other threads to print text to the console
 */

// call printOutput to print normal text output from lisp

void Console::printOutput(String s, bool t)
{
#ifdef GRACE
  postAsyncMessage(CommandIDs::ConsolePrintOutput, s, t);
#else
  std::cout << s.toUTF8() << std::flush;
#endif
}

void Console::printOutput(char* s, bool t)
{
#ifdef GRACE
  postAsyncMessage(CommandIDs::ConsolePrintOutput, String(s), t);
#else
  std::cout << s << std::flush;
#endif
}

void Console::printValues(String s, bool t)
{
#ifdef GRACE
  postAsyncMessage(CommandIDs::ConsolePrintValues, s, t);
#else
  std::cout << s.toUTF8() << std::flush;
#endif

}

void Console::printValues(char* s, bool t)
{
#ifdef GRACE
  postAsyncMessage(CommandIDs::ConsolePrintValues, String(s), t);
#else
  std::cout << s << std::flush;
#endif
}

// printWarning: call this method to print error messages

void Console::printWarning(String s, bool t)
{
#ifdef GRACE
  postAsyncMessage(CommandIDs::ConsolePrintWarning, s, t);
#else
  std::cout << s.toUTF8() << std::flush;
#endif
}

void Console::printWarning(char* s, bool t)
{
#ifdef GRACE
  postAsyncMessage(CommandIDs::ConsolePrintWarning, String(s), t);
#else
  std::cout << s << std::flush;
#endif
}

// printError: call this method to print error messages

void Console::printError(String s, bool t)
{
#ifdef GRACE
  postAsyncMessage(CommandIDs::ConsolePrintError, s, t);
#else
  std::cout << s.toUTF8() << std::flush;
#endif
}

void Console::printError(char* s, bool t)
{
#ifdef GRACE
  postAsyncMessage(CommandIDs::ConsolePrintError, String(s), t);
#else
  std::cout << s << std::flush;
#endif
}

//
// printPrompt: call this method to print the REPL prompt
//

void Console::printPrompt(bool t)
{
#ifdef GRACE
  if (prompt!=String::empty)
    postAsyncMessage(CommandIDs::ConsolePrintPrompt, String::empty, t);
#else
  if (prompt!=String::empty)
    std::cout << prompt.toUTF8() << std::flush;
#endif
}

/*
 * Async message handling
 */

void Console::postAsyncMessage(int typ, String msg, bool trigger)
{
  //  std::cout << "Posting console message " << msg.toUTF8() << "\n";
  messages.lockArray();
  messages.add(new AsyncMessage(typ, msg));
  messages.unlockArray();
  if (trigger)
    triggerAsyncUpdate();
}

void Console::postAsyncMessage(int typ, bool trigger)
{
  messages.lockArray();
  messages.add(new AsyncMessage(typ));
  messages.unlockArray();
  if (trigger)
    triggerAsyncUpdate();
}

void Console::postAsyncMessage(int typ, int msg, bool trigger)
{
  messages.lockArray();
  messages.add(new AsyncMessage(typ, msg));
  messages.unlockArray();
  if (trigger)
    triggerAsyncUpdate();
}

void Console::handleAsyncUpdate()
{
  // THIS CALLBACK HAPPENS IN THE MAIN THREAD
  Colour color=Colours::black;
  //std::cout << "Handling " << messages.size() << " messages\n";
  messages.lockArray(); // SHOULD THIS BE BEFORE LOOP?
  
  for (int i=0; i<messages.size(); i++)
    {
      int cid = messages[i]->type;
      int cmd = CommandIDs::getCommand(cid);
      int arg = CommandIDs::getCommandData(cid);
      int dat = messages[i]->data;
      switch (cmd) 
	{
	case CommandIDs::ConsolePrintOutput :
	  color=theme->getColor(ConsoleTheme::outputColor);
	  display(messages[i]->text, color);
	  break;
	case CommandIDs::ConsolePrintValues :
	  color=theme->getColor(ConsoleTheme::valuesColor);
	  display(messages[i]->text, color);
	  break;
	case CommandIDs::ConsolePrintWarning :
	  color=theme->getColor(ConsoleTheme::warningColor);
	  display(messages[i]->text, color);
	  break;
	case CommandIDs::ConsolePrintError :
	  {
	    color=theme->getColor(ConsoleTheme::errorColor);
	    display(messages[i]->text, color);
#ifdef GRACE
	    // sigh. s7 error printing is unbuffered so only print if
	    // we have a crlf in the string
	    if (getBeepOnError() || messages[i]->text.contains("\n"))
		
	      PlatformUtilities::beep();
#endif
	  }
	  break;
	case CommandIDs::ConsolePrintPrompt :
	  color=theme->getColor(ConsoleTheme::errorColor);
	  if (prompt!=String::empty)
	    display(prompt, color);
	  break;
#ifdef GRACE
	case CommandIDs::AudioOpenFilePlayer :
	  {
	    String path=messages[i]->text;
	    File file;
	    if (File::isAbsolutePath(path))
	      file=File(path);
	    else
	      file=File::getCurrentWorkingDirectory().
		getChildFile(path).getFullPathName();
	    AudioManager::getInstance()->openAudioFilePlayer(file,true);
	  }
	  break;
#endif
	default:
	  {
	    String text=T("Unimplemented message: ");
	    text << CommandIDs::toString(cmd) << T("\n");
	    color=theme->getColor(ConsoleTheme::warningColor);
	    display(text, color);
	  }
	  break;
	}
    }      
  
  messages.clear();
  messages.unlockArray();
}

#ifdef GRACE

int Console::getFontSize()
{
  return (int)buffer->getFont().getHeight();
}

void Console::setFontSize(int size)
{
  Font font=buffer->getFont();
  font.setHeight((float)size);
  buffer->applyFontToAllText(font);
}

Font Console::getFont()
{
  return buffer->getFont();
}

void Console::setFont(Font f)
{
  buffer->setFont(f);
}

void Console::setBeepOnError(bool b)
{
  Preferences::getInstance()->setBoolProp(T("ConsoleBeepOnError"),b);
}

bool Console::getBeepOnError()
{
  return Preferences::getInstance()->
    getBoolProp(T("ConsoleBeepOnError"), true);
}

/*=======================================================================*
                                 Console Window
 *=======================================================================*/

ConsoleWindow::ConsoleWindow ()
  : DocumentWindow ( T("Console") , Colours::white,
		     DocumentWindow::allButtons, true )
{
  Preferences* prefs=Preferences::getInstance();
  setMenuBar(this);
  Console* cons=Console::getInstance();
  setContentComponent(cons);
  //  cons->manager=new ApplicationCommandManager();
  //  cons->addKeyListener(cons->manager->getKeyMappings());
  //  cons->addKeyListener(CommandManager::getInstance()->getKeyMappings());
  //  cons->manager->registerAllCommandsForTarget(cons);
  //  setApplicationCommandManagerToWatch(cons->manager);

  cons->buffer=new TextEditor(String::empty) ;
  cons->buffer->setMultiLine(true);
  cons->buffer->setScrollToShowCursor(true);
  cons->buffer->setReadOnly(true);
  cons->buffer->setCaretVisible(false);    
  cons->buffer->setFont(Font(Font::getDefaultMonospacedFontName(),
			     Preferences::getInstance()->
			     getIntProp(T("ConsoleFontSize"), 17),
			     Font::plain));
  cons->buffer->setVisible(true);
  // in Grace the Console is a component, add the buffer to it
  cons->addChildComponent(cons->buffer);
  // add the theme after buffer exists
  // bg, input, output, error, warning, values, hilite, texthilite, cursor
  cons->setTheme
    (new ConsoleTheme(T("Clarity and Beauty"), 
		      Colours::black, Colours::white, Colours::lightsalmon,
	      Colour(0xffcd0000), Colours::darkorange, Colour(0xff00cd00), 
	      Colour(0xffbebebe), Colours::white, Colours::yellow));

  cons->manager=new ApplicationCommandManager();
  cons->addKeyListener(cons->manager->getKeyMappings());
  cons->addKeyListener(CommandManager::getInstance()->getKeyMappings());
  cons->manager->registerAllCommandsForTarget(cons);
  setApplicationCommandManagerToWatch(cons->manager);

  cons->setWantsKeyboardFocus(true);  
  cons->setVisible(true);
  setResizable(true, true); 
  setUsingNativeTitleBar(true);
  setDropShadowEnabled(true);
  centreWithSize (450, 350);
  setWantsKeyboardFocus(false);  // Console component has it.
  setVisible(true);
  /**
  splash=new Splash(ImageCache::getFromMemory(Images::grace_png,
					      Images::grace_pngSize));
  splash->setSize(cons->getWidth(), cons->getHeight());
  cons->addChildComponent(splash);
  splash->setVisible(true);
  splash->fadeOutComponent(5000);
  cons->removeChildComponent(splash);
  //splash->close(); 
  //delete splash;
  **/
}

ConsoleWindow::~ConsoleWindow ()
{
  getContentComponent()->deleteAllChildren();
  //  setContentComponent(NULL);
}

void ConsoleWindow::closeButtonPressed ()
{
  if (juce::AlertWindow::showOkCancelBox
      (juce::AlertWindow::QuestionIcon,
       T("Quit"),
       T("Quit Grace? Any unsaved work will be lost."),
       T("   Quit   "),
       T("Don't Quit")))
    {
      JUCEApplication::getInstance()->quit();
    }
}

#endif

