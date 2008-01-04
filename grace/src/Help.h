/*************************************************************************
 * Copyright (C) 2007, 2008 Todd Ingalls, Rick Taube.                    *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision: 1520 $
// $Date: 2008-01-03 09:51:00 -0600 (Thu, 03 Jan 2008) $ 

#ifndef __HELP__
#define __HELP_

#include "juce.h"///

/// Symbol Help. 


class SymbolHelp {
public:
  StringPairArray maproots;
  StringPairArray salmap;
  StringPairArray graceschememap;
  StringPairArray schememap;
  StringPairArray cmmap;
  StringPairArray clmmap;
  StringPairArray fomusmap;
  StringPairArray clmap;
  SymbolHelp () ;
  ~SymbolHelp() ;

  String getHelpRoot(String help) ;
  void setHelpRoot(String help, String root) ;

  String lookupHelp(String sym, String helppath) ;
  StringPairArray matchingHelp(String match, String help) ;
  void openHelpInBrowser(String help) ;

  void addSalHelp();
  void addGraceSchemeHelp();
  void addSchemeHelp();
  void addCommonMusicHelp();
  void addCommonLispMusicHelp();
  void addFomusHelp();  
  void addCommonLispHelp();
  juce_DeclareSingleton (SymbolHelp, true)
};

#endif
