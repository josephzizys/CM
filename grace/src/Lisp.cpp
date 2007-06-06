/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

#include "Lisp.h"
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

bool LispConnection::startLisp () {
  String command = lisp + T(" ") + args;
  char* const argv[4] = { "/bin/sh", "-c", (char*) (const char*) command, 0 };
  const int cpid = fork();

  printf("Starting lisp with: '%s'\n", command.toUTF8() );
  if (cpid == 0)  {
    // Child process
    if (execve(argv[0], argv, 0) < 0)
      exit (0);
  }
  else if (cpid < 0) {
    printf("Failed to start Lisp.\n");
    lpid=-1;
    return false;
  }
  else {
    // Parent process
    lpid=cpid;
    printf("Lisp started, pid=%d\n", lpid);
  }
  return true;
}

bool LispConnection::isLispRunning () {
  return (lpid != -1);
}

bool LispConnection::killLisp () {
  if ( isLispRunning() ) {
    kill(lpid, SIGKILL);
    lpid=-1;
    return true;
  }
  return false;
}

void LispConnection::connectionMade () {
  printf("Lisp connected.\n");
}

void LispConnection::connectionLost () {
  printf("Lisp connection lost.\n");
}

void LispConnection::messageReceived (const MemoryBlock &message) {
  printf("Message received!\n");
}
