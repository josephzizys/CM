/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

#ifndef CMSNDLIB_H
#define CMSNDLIB_H

#include "juce.h"

class SndLib
{
 public:
  SndLib();
  ~SndLib();
  XmlElement* instable;
  int performCommand(int type, int data=0, String text=String::empty);
  String getClmDefault(int id);
  String getInstrumentCode(String file);
  void loadInstrumentCode(XmlElement* ins);  
  void getInstrumentFilesToLoad(XmlElement* ins, StringArray& ary);
  XmlElement* getInstrumentTable(bool all=false);
  XmlElement* getInstrumentElement(String filename);
  bool isInstrumentLoaded(String filename);
  void updateAutoLoaded();
  void autoLoadInstruments();
  void openInstrumentBrowser();
  void restoreInstruments(String directory=String::empty);
  juce_DeclareSingleton (SndLib, true)
};

#endif

