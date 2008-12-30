/*=======================================================================*
  Copyright (c) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify
  it under the terms of the Lisp Lesser Gnu Public License. The text
  of this agreement is available at http://www.cliki.net/LLGPL
 *=======================================================================*/

#ifndef COMMANDS_H
#define COMMANDS_H

#include "juce.h"

// a global command mananger for holding app-wide commands. component
// windows have their own managers as well...

class CommandManager : public ApplicationCommandManager
{
 public:
  CommandManager();
  ~CommandManager();
  juce_DeclareSingleton (CommandManager, true)
};

#endif
