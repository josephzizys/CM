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
  void restoreFile(const char* code, int size, String file);

 public:
  Help ();
  ~Help();
  File getHelpDirectory();
  File getHelpFile(String fil);
  int getHelpSize(CommandID id);
  String getHelpName(CommandID id);
  String getHelpEntry(CommandID id);
  void symbolHelp(String sym, String helppath) ;
  void openHelp(CommandID id);
  void openHelp(String entry);
  void openHelpInBrowser(String url);
  void openHelpInEditor(String file);  

  juce_DeclareSingleton (Help, true)

};

#endif
