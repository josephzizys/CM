/*=======================================================================*
  Copyright (c) 2009 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#ifndef OSC_H
#define OSC_H

#include "juce.h"

class OscPort 
{
 public:
  bool isOpen;
  bool traceInput;
  bool traceOutput;
  bool isHookActive;
  OscPort();
  ~OscPort();
  int getServerPort();
  String getTargetHost();
  int getTargetPort();
  void openDialog();
  void showStatus();
  int open(String inport, String target);
  int close(bool force=false);
  int sendMessage(String path, String types, Array<int> &ints, Array<double> &flos, StringArray &strs, double time=0.0);
  void handleMessage(const char *path, const char *types, int argc, void **data);
  static bool isValidPort(String p);
  static bool isValidHost(String h);
  juce_DeclareSingleton(OscPort, true)
};

#endif
