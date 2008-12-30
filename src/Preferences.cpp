/*=======================================================================*
  Copyright (C) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#include "Enumerations.h"
#include "Preferences.h"

juce_ImplementSingleton (Preferences);

Preferences::Preferences()
    : props (0)
{
  props=PropertiesFile::createDefaultAppPropertiesFile
    (JUCEApplication::getInstance()->getApplicationName(),
     T("xml"), String::empty, false, 3000, PropertiesFile::storeAsXML);
  recentlyOpened.setMaxNumberOfItems(16);
  recentlyOpened.restoreFromString(props->getValue(T("RecentlyOpenedFiles")));
  recentlyOpened.removeNonExistentFiles();
  recentlyLoaded.setMaxNumberOfItems(8);
  recentlyLoaded.restoreFromString(props->getValue(T("RecentlyLoadedFiles")));
  recentlyLoaded.removeNonExistentFiles();
  recentlyPlayed.setMaxNumberOfItems(8);
  recentlyPlayed.restoreFromString(props->getValue(T("RecentlyPlayedFiles")));
  recentlyPlayed.removeNonExistentFiles();
}

Preferences::~Preferences()
{
    flush();
    deleteAndZero (props);
    clearSingletonInstance();
}

PropertiesFile& Preferences::getProps()
{
  return *props;
}

void Preferences::flush()
{
  // flush exiting
  if (props != 0) 
    {
      props->setValue(T("RecentlyOpenedFiles"), recentlyOpened.toString());
      props->setValue(T("RecentlyLoadedFiles"), recentlyOpened.toString());
      props->setValue(T("RecentlyPlayedFiles"), recentlyPlayed.toString());
    }
}

// Bool Props

bool Preferences::getBoolProp(String name, bool def)
{
  return props->getBoolValue(name, def);
}

void Preferences::setBoolProp(String name, bool val)
{
  props->setValue(name, val);
}

// Int Props

int Preferences::getIntProp(String name, int def)
{
  return props->getIntValue(name, def);
}

void Preferences::setIntProp(String name, int val)
{
  props->setValue(name, val);
}

// String Props

float Preferences::getDoubleProp(String name, double def)
{
  return props->getDoubleValue(name, def);
}

void Preferences::setDoubleProp(String name, double val)
{
  props->setValue(name, val);
}

// String Props

String Preferences::getStringProp(String name, String def)
{
  return props->getValue(name, def);
}


void Preferences::setStringProp(String name, String val)
{
  props->setValue(name, val);
}

// XML Props

XmlElement* Preferences::getXmlProp(String name, XmlElement* def)
{
  XmlElement* val=props->getXmlValue(name);
  if (val==NULL)
    return (XmlElement *)NULL;
  else
    return def;
}

void Preferences::setXmlProp(String name, XmlElement* val)
{
  props->setValue(name, val);
}


