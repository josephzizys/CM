/*=======================================================================*
  Copyright (c) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify
  it under the terms of the Lisp Lesser Gnu Public License. The text
  of this agreement is available at http://www.cliki.net/LLGPL
 *=======================================================================*/

#ifndef MENUS_H
#define MENUS_H

#include "Libraries.h"

class CommandMenus
{
 public:

  static const int NumPrefsOpenRecent = 16;
  static const int NumPrefsLoadRecent = 16;
  static const int NumMidiOutOpen = 16;
  static const int NumWindowSelect = 8;
  static const int NumMidiOutTuning = 16;
  static const int NumMidiInOpen = 16;
  static const int NumMidiInChannelFilter = 16;
  static const int NumMidiInOpcodeFilter = 7;
  static const int NumHelpManual = 8;
  static const int NumHelpExample = 32;
  static const int NumHelpTutorial = 16;
  static const int NumHelpWebSite = 8;
  static const int NumFont = 2;
  static const int NumFontSize = 24;
  static const int NumConsoleTheme = 8;  
  static const int NumTabWidth = 4;
  static const int NumSndLibSrate = 4;
  static const int NumSndLibChannel = 2;
  static const int NumFomusScore = 8;

  static const PopupMenu getWindowMenu();
  static const PopupMenu getHelpMenu(int win, ApplicationCommandManager* com);
  static const PopupMenu getAudioMenu(bool isfms);
  static const PopupMenu getFontSizeMenu(ApplicationCommandManager* comm,
					 CommandID rootid);
  static const PopupMenu getRecentlyOpenedMenu();
  static const PopupMenu getRecentlyLoadedMenu();
};



#endif

