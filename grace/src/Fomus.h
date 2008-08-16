/*************************************************************************
 * Copyright (C) 2008 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

#ifndef GRACEFOMUS
#define GRACEFOMUS

#include "juce.h"
#include "Console.h"

class FomusPort
{
  ConsoleWindow* console;
 public:
  FomusPort(ConsoleWindow* win);
  ~FomusPort();
  const PopupMenu getFomusMenu();
  void performFomusCommand(CommandID id);
};

#endif
