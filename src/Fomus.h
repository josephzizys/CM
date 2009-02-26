/*=======================================================================*
  Copyright (C) 2009 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#include <juce.h>

class Fomus
{
 private:
  File scorefile;
  File application;
  String commandargs;
  bool playafter;
 public:
  Fomus();
  ~Fomus();

  void openSettings();
  void openDocumentation();
  void execute();
  juce_DeclareSingleton(Fomus, true)
};
