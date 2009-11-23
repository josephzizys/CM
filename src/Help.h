/*=======================================================================*
  Copyright (c) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify
  it under the terms of the Lisp Lesser Gnu Public License. The text
  of this agreement is available at http://www.cliki.net/LLGPL
 *=======================================================================*/

#ifndef HELP_H
#define HELP_H

#include "juce.h"

class Help
{
  File cmdocdir;
  File cminsdir;
  XmlElement* docTable;
  StringPairArray roots;
  StringPairArray sal;
  StringPairArray cm;
  StringPairArray clm;
  StringPairArray scheme;
  
  StringPairArray manuals;
  StringPairArray examples;
  StringPairArray tutorials;
  StringPairArray websites;

  String helpKey(StringPairArray& a, int i) {return a.getAllKeys()[i];}
  String helpValue(StringPairArray& a, int i) {return a.getAllValues()[i];}

  void addSalSymbolHelp();
  void addCommonMusicSymbolHelp();
  void addSndLibSymbolHelp();
  void addSchemeSymbolHelp();
  void restoreHelpFiles();

 public:
  Help ();
  ~Help();
  int getHelpSize(CommandID id);
  String getHelpName(CommandID id);
  void openHelp(CommandID id);
  void openHelpInBrowser(String url);
  void openHelpInEditor(String path, String code);  
  void symbolHelp(String sym, String helppath) ;

  String getHelpFileText(String filename);
  XmlElement* getXmlMenu(String title);
  XmlElement* getXmlMenuItem(String title, int index);
  void addHelpMenuItems(PopupMenu& menu, String menuname, CommandID cmdid, int maxitems, ApplicationCommandManager* manager);
  
  juce_DeclareSingleton (Help, true)

};

#endif
