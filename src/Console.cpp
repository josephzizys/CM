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
  #include "PlotWindow.h"
  #include "CodeEditor.h"
  #include "Alerts.h"
#endif

Console* Console::globalInstance = 0;

Console::Console() : 
  prompt (String::empty),
  theme (NULL),
  buffer (NULL),
  manager (NULL),
  isEvaling (false)
{
  // GUI initialization code is done by window
  supportedfiletypes=String(T(".scm.lisp.sal1.sal2.sal.ins.clm.fms.xml.mid.text.txt"));
#ifdef GRACE

  initThemes();
#endif
}

Console::~Console() 
{
  messages.clear();
  //deleteAndZero(theme);
  themes.clear();
  deleteAndZero(manager); 
}

String Console::getSupportedFileTypes()
{
  return supportedfiletypes;
}

bool Console::isSupportedFileType(File file)
{
  return supportedfiletypes.contains(file.getFileExtension());
}

bool Console::isSupportedFileType(String path)
{
  int dot=path.lastIndexOf(T("."));
  return (dot<0) ? false : supportedfiletypes.contains(path.substring(dot));
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
  // JUCE BUG: single \n does not get added to buffer so replace it with crlf.
  if ((str.length()==1) && (str[0]=='\n'))
    buffer->insertTextAtCaret(String("\r\n"));
  else
    buffer->insertTextAtCaret(str);
#else
  std::cout << str.toUTF8() <<  std::flush;
#endif
}

Colour Console::getConsoleColor(int id)
{
  return (theme) ? theme->getColor(id) : Colours::black;
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

// notify console we are under eval

void Console::setEvaling(bool evaling)
{
  isEvaling=evaling;
#ifdef GRACE
  repaint();
#endif
}

void Console::clearConsole()
{
#ifdef GRACE
  postAsyncMessage(CommandIDs::ConsoleClearConsole, String::empty, true);
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
  // messages.lock();
  const ScopedLock lock (messages.getLock());
  messages.add(new AsyncMessage(typ, msg));
  if (trigger)
    triggerAsyncUpdate();
}

void Console::postAsyncMessage(int typ, bool trigger)
{
  //  messages.lockArray();
  messages.add(new AsyncMessage(typ));
  // messages.unlockArray();
  if (trigger)
    triggerAsyncUpdate();
}

void Console::postAsyncMessage(int typ, int msg, bool trigger)
{
  // messages.lockArray();
  messages.add(new AsyncMessage(typ, msg));
  // messages.unlockArray();
  if (trigger)
    triggerAsyncUpdate();
}

void Console::handleAsyncUpdate()
{
  // THIS CALLBACK HAPPENS IN THE MAIN THREAD
  //std::cout << "Handling " << messages.size() << " messages\n";

  const ScopedLock lock (messages.getLock());
  int size=messages.size();

  // if we have many pending messages then we probably have an
  // infinite printing loop of some sort.  in this case just clear the
  // array to keep the message thread alive and hope that the user can
  // abort the lisp command that started it.

  for (int i=0; i<size && (size<1000); i++)
  {
    AsyncMessage* msg=messages.getUnchecked(i);
    int cid = msg->type;
    int cmd = CommandIDs::getCommand(cid);
    int arg = CommandIDs::getCommandData(cid);
    int dat = msg->data;
    switch (cmd) 
    {
    case CommandIDs::ConsolePrintOutput :
      display(msg->text, getConsoleColor(ConsoleTheme::outputColor));
      break;
    case CommandIDs::ConsoleIsEvaling :
      setEvaling(dat != 0);
      break;
    case CommandIDs::ConsolePrintValues :
      display(msg->text, getConsoleColor(ConsoleTheme::valuesColor));
      break;
    case CommandIDs::ConsolePrintWarning :
      display(msg->text, getConsoleColor(ConsoleTheme::warningColor));
      break;
    case CommandIDs::ConsolePrintError :
      display(msg->text, getConsoleColor(ConsoleTheme::errorColor));
#ifdef GRACE
      getTopLevelComponent()->toFront(true); 
      if (getBeepOnError() )
        PlatformUtilities::beep();
#endif
      break;
    case CommandIDs::ConsolePrintPrompt :
      if (prompt!=String::empty)
        display(prompt, getConsoleColor(ConsoleTheme::errorColor));
      break;
#ifdef GRACE
    case CommandIDs::AudioFilePlayer :
      {
        String path=msg->text;
        File file;
        if (File::isAbsolutePath(path))
          file=File(path);
        else
          file=File::getCurrentWorkingDirectory().
            getChildFile(path).getFullPathName();
        AudioManager::getInstance()->openAudioFilePlayer(file,true);
      }
      break;
    case CommandIDs::ConsoleClearConsole :
      std::cout << "clearing console\n";
      buffer->clear();
      break;
#endif
    default:
      {
        String text=T("Unimplemented message: ");
        text << CommandIDs::toString(cmd) << T("\n");
        display(text, getConsoleColor(ConsoleTheme::warningColor));
      }
      break;
    }
  }
  messages.clear();
}

#ifdef GRACE

String Console::getThemeName(int index)
{
  if (index<themes.size())
    return themes.getUnchecked(index)->getName();
  else
    return T("No Theme");
}      

int Console::numThemes()
{
  return themes.size();
}

bool Console::isCurrentTheme(int index)
{
  if (index < themes.size())
    return (theme == themes[index]);
  else
    return false;
}

void Console::setTheme(String name)
{
  for (int i=0; i<themes.size(); i++)
    if (name==themes.getUnchecked(i)->getName())
      {
        setTheme(i);
        break;
      }
}

void Console::setTheme(int index)
{
  if (index>=themes.size() )
    return;
  theme=themes[index];
  Preferences::getInstance()->setStringProp(T("ConsoleTheme"), theme->getName());
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

void printheme(ConsoleTheme* th)
{
  String str=T("<colortheme");
  str << " name=" << th->getName().quoted() 
      << T("\n           ")
      << " plaintext=" << ColorThemeIDs::toHtmlColorString(th->getColor(ConsoleTheme::inputColor)).quoted()
      << T(" comment=\"firebrick\"")
      << T(" string=\"rosybrown\"")
      << T("\n           ")
      << T(" keyword1=\"cadetblue\"")   // sharpsign
      << T(" keyword2=\"#8a2f8f\"")     // lisp keywords
      << T(" keyword3=\"orchid\"")      // sal keywords
      << T("\n           ")
      << T(" literal1=\"#950083\"")     // reserved/special
      << T(" literal2=\"forestgreen\"") // sal1 classnames
      << T(" literal3=\"blue\"")        // sal1 commands
      << T("\n           ")
      << " values=" << ColorThemeIDs::toHtmlColorString(th->getColor(ConsoleTheme::valuesColor)).quoted()
      << " output=" << ColorThemeIDs::toHtmlColorString(th->getColor(ConsoleTheme::outputColor)).quoted()
      << " warning=" << ColorThemeIDs::toHtmlColorString(th->getColor(ConsoleTheme::warningColor)).quoted()
      << T("\n           ")
      << " error=" << ColorThemeIDs::toHtmlColorString(th->getColor(ConsoleTheme::errorColor)).quoted()
      << " cursor=" << ColorThemeIDs::toHtmlColorString(th->getColor(ConsoleTheme::caretColor)).quoted()
      << " background=" << ColorThemeIDs::toHtmlColorString(th->getColor(ConsoleTheme::bgColor)).quoted()
      << T("/>");
  std::cout<<str.toUTF8()<<"\n";

  for (int i=ConsoleTheme::bgColor; i<=ConsoleTheme::caretColor; i++)
    {
      Colour c1=th->getColor(i);
      String st=ColorThemeIDs::toHtmlColorString(c1);
      Colour c2=ColorThemeIDs::fromHtmlColorString(st);
      if (c1!=c2) std::cout << th->getName().toUTF8() << "(" << i << ") failed! orig=" << c1.toString().toUTF8() << ", html="<< st.toUTF8() << ", back=" << c2.toString().toUTF8() << "\n" ;
    }
}

void Console::initThemes()
{
  Colour errc=Colour(0xffcd0000);
  Colour warn=Colours::darkorange;
  Colour vals=Colour(0xff00cd00);

  themes.add(new ConsoleTheme(T("Clarity and Beauty"), 
                              Colours::black, // background
                              Colours::white, // input
                              Colours::lightsalmon, // output
                              errc, // error
                              warn, // warning
                              vals, // values
                              Colour(0xffbebebe), // highlight
                              Colours::white, // highlightText
                              Colours::yellow)); // carat
 
  themes.add(new ConsoleTheme(T("Deep Blue"),
                              Colour(0xff102e4e), // background
                              Colour(0xffeeeeee), // input
                              Colour(0xffdeb887),  // output
                              errc, // error
                              warn, // warning
                              vals, // values
                              Colour(0xff008b8b), // highlight
                              Colour(0xffeeeeee), // highlightText
                              Colour(0xff00ff00)  // carat      
                              ));
  
  themes.add(new ConsoleTheme(T("Gnome"),
                              Colour(0xff2f4f4f),
                              Colour(0xfff5deb3),
                              Colour(0xffffa07a),
                              errc, // error
                              warn, // warning
                              vals, // values
                              Colour(0xff008b8b),
                              Colour(0xff00ffff), 
                              Colour(0xffd3d3d3)
                              ));
  themes.add(new ConsoleTheme(T("Snowish"),
                              Colour(0xffeee9e9), 
                              Colour(0xff2f4f4f),
                              Colour(0xff9400d3),
                              errc, // error
                              warn, // warning
                              vals, // values
                              Colour(0xffeedc82),
                              Colours::black,
                              Colour(0xffcd0000)
                              ));
  themes.add(new ConsoleTheme(T("Emacs"),
                              Colours::white,
                              Colours::black,
                              Colour(0xffbc8f8f),
                              errc, // error
                              warn, // warning
                              vals, // values
                              Colour(0xffeedc82),
                              Colours::black,
                              Colours::black
                              ));
  themes.add(new ConsoleTheme(T("XEmacs"),
                              Colour(0xffcccccc), 
                              Colours::black,
                              Colour(0xff008b00),
                              errc, // error
                              warn, // warning
                              vals, // values
                              Colour(0xffa6a6a6),
                              Colours::black,
                              Colour(0xffcd0000)
                              ));

  //for (int i=0; i<themes.size(); i++) { printheme(themes[i]); }
}


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
  std::cout << "in setFont\n";
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

bool Console::isInterestedInFileDrag(const StringArray &files)
{
  // return true if all the files are allowed
  for (int i=0; i<files.size(); i++)
    if (!isSupportedFileType(files[i]))
      return false;
  return true;
}

void Console::filesDropped(const StringArray &files, int x, int y)
{
  //std::cout << "filesDropped()\n";
  for (int i=0; i<files.size(); i++)
  {
    File file (files[i]);
    // this check probably not needed
    if (!isSupportedFileType(file)) continue; 
    String type=file.getFileExtension();
    if (type==T(".xml"))
      PlotWindow::openXmlFile(file);
    else if (type==T(".mid"))
      PlotWindow::openMidiFile(file);
    else
    {
      CodeEditorWindow* e=0;
      // cycle through open editor windows, if the file is already
      // open then re-focus that window else open the file in a
      // new editor window
      for (int j=0; j<TopLevelWindow::getNumTopLevelWindows(); j++)
      {
        TopLevelWindow* w=TopLevelWindow::getTopLevelWindow(j);
        if (WindowTypes::isWindowType(w, WindowTypes::CodeEditor))
        {
          e=(CodeEditorWindow*)w;
          if (e->sourcefile == file)
            break;
        }
        e=0;
      }
      if (e)
        e->toFront(false);
      else
      {
        CodeEditorWindow::openFile(file);
        Preferences::getInstance()->recentlyOpened.addFile(file);
      }
    }
  }
}

void Console::paint(Graphics& g)
{
  if (isEvaling)
    g.fillAll (Colours::black); //Colours::firebrick Colours::royalblue
  else
    g.fillAll (Colours::transparentBlack);
}

void Console::resized()
{
  //  buffer->setTopLeftPosition(4,3);
  //  buffer->setSize(getWidth()-8,getHeight()-7);
  buffer->setTopLeftPosition(3,1);
  buffer->setSize(getWidth()-6,getHeight()-4);
}

/*=======================================================================*
                                 Console Window
 *=======================================================================*/


ConsoleWindow::ConsoleWindow ()
  : DocumentWindow (String::empty , Colour (227,227,227), //Colours::silver,
                    DocumentWindow::allButtons, true )
{
  setName(SysInfo::getApplicationName());
  Preferences* prefs=Preferences::getInstance();
  setMenuBar(this);
  Console* cons=Console::getInstance();

  cons->buffer=new TextEditor(String::empty) ;
  cons->buffer->setMultiLine(true);
  cons->buffer->setScrollToShowCursor(true);
  cons->buffer->setReadOnly(true);
  cons->buffer->setCaretVisible(false);
  cons->buffer->setFont(Font(Font::getDefaultMonospacedFontName(),
			     (float)Preferences::getInstance()->getIntProp(T("ConsoleFontSize"), 16),
			     Font::plain));
  cons->buffer->setVisible(true);
  // add buffer to Console component
  cons->addChildComponent(cons->buffer);
  // set the theme after buffer exists
  cons->setTheme(prefs->getStringProp(T("ConsoleTheme"), T("Clarity and Beauty")));
  cons->manager=new ApplicationCommandManager();
  cons->addKeyListener(cons->manager->getKeyMappings());
  cons->addKeyListener(CommandManager::getInstance()->getKeyMappings());
  cons->manager->registerAllCommandsForTarget(cons);
  setApplicationCommandManagerToWatch(cons->manager);
  cons->setWantsKeyboardFocus(true);  
  cons->setVisible(true);
  cons->setSize(450,350);
  setContentComponent(cons, false, true);
  setResizable(true, true); 
  setUsingNativeTitleBar(true);
  setDropShadowEnabled(true);

  String wstate=prefs->getStringProp(T("ConsoleState"));
  if (wstate.isNotEmpty())
    restoreWindowStateFromString(wstate);
  else
    centreWithSize (450, 350);

  setWantsKeyboardFocus(false);  // Console component has it.
  setVisible(true);
}

ConsoleWindow::~ConsoleWindow ()
{
  setMenuBar(0);
  getContentComponent()->deleteAllChildren();
}

void ConsoleWindow::closeButtonPressed ()
{
  
      JUCEApplication::getInstance()->systemRequestedQuit();

  /*if (Alerts::showOkCancelBox
      (AlertWindow::QuestionIcon,
       T("Quit"),
       T("Quit Grace? Any unsaved work will be lost."),
       T("Quit"),
#ifdef WINDOWS
       T("Cancel")
#else
       T("Don't Quit")
#endif
       ))
    {
      JUCEApplication::getInstance()->quit();
    }
  */
}

#endif

