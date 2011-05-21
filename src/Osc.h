/*=======================================================================*
  Copyright (c) 2009 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#ifndef OSC_H
#define OSC_H

#include "Libraries.h"
#include "Scheme.h"

class OscPort 
{
 private:
  CriticalSection lock;
 public:
  OscPort();
  ~OscPort();
  bool isOpen;
  bool traceInput;
  bool traceOutput;
  int getServerPort();
  String getTargetHost();
  int getTargetPort();
  void openDialog();
  void showStatus();
  int open(String inport, String target);
  int close(bool force=false);

  int sendMessage(String path, lo_message msg);
  int sendBundle(lo_bundle bndl);
  void handleMessage(const char *path, const char *types, int argc, void **data);

  static bool isValidPort(String p);
  static bool isValidHost(String h);
  juce_DeclareSingleton(OscPort, true)
};

#endif
