/*=======================================================================*
  Copyright (C) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#ifndef PREFERENCES_H
#define PREFERENCES_H

#include "Libraries.h"

class Preferences
{
 private:
  PropertiesFile* props;
 public:
  Preferences();
  ~Preferences();
  PropertiesFile& getProps();

  bool getBoolProp(String name, bool def=false);
  void setBoolProp(String name, bool val);

  int getIntProp(String name, int def=0);
  void setIntProp(String name, int val);

  double getDoubleProp(String name, double def=0.0);
  void setDoubleProp(String name, double val);

  String getStringProp(String name, String def=T(""));
  void setStringProp(String name, String val);

  void removeProp(String name);

  XmlElement* getXmlProp(String name, XmlElement* xml=NULL);
  void setXmlProp(String name, XmlElement* val);

  void flush();

  RecentlyOpenedFilesList recentlyOpened;
  RecentlyOpenedFilesList recentlyLoaded;
  RecentlyOpenedFilesList recentlyPlayed;
  XmlElement* colorThemes;
  int numColorThemes();
  XmlElement* getColorTheme(int index);
  XmlElement* getColorTheme(const String name);
  juce_DeclareSingleton (Preferences, false);
};

#endif
