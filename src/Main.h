/*=======================================================================*
  Copyright (C) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#ifndef MAIN_H
#define MAIN_H

#include "juce.h"

class Grace : public JUCEApplication
{
  LookAndFeel* lookandfeel;
public:
  
  Grace() {}
  ~Grace() {}
  void initialise (const juce::String& commandLine);
  void shutdown();
  void systemRequestedQuit();
  void anotherInstanceStarted(const String& commandLine);
  const String getApplicationName();
  const String getApplicationVersion();
  bool moreThanOneInstanceAllowed();
  void showWorkingDirectory();
  void chooseWorkingDirectory();

  // these are implemented in Command.cpp
  ApplicationCommandTarget* getNextCommandTarget();
  void getAllCommands(Array<CommandID>& commands);
  void getCommandInfo(const CommandID id, ApplicationCommandInfo& info);
  bool perform(const ApplicationCommandTarget::InvocationInfo& info);
  void openFile(File file=File::nonexistent);

};

#endif
