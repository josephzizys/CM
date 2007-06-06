/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

#ifndef __LISP__
#define __LISP__

#include "juce.h"

class LispConnection : public InterprocessConnection {
 public:
  enum LispFlavor {SBCL=1, OpenMCL, CLisp, Gauche, Guile, Custom};
  StringArray commands;
  String lisp;
  String args;
  int port;
  int lpid;
  String host;

 LispConnection () 
   : host (T("localhost")),
    port (8000),
    lpid (-1),
    lisp (T("/usr/local/bin/openmcl")),
    args (String::empty)
    {
    }

  ~LispConnection () { }

    bool startLisp();
    bool killLisp();
    bool isLispRunning();
    void connectionMade ();
    void connectionLost ();
    void messageReceived (const MemoryBlock &message);
};

#endif

