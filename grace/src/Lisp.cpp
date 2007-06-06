/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

#include "Lisp.h"

// bool File::startAsProcess (const String &parameters = String::empty) const throw ()

void LispConnection::connectionMade () {
  printf("Lisp connected.\n");
}

void connectionLost () {
  printf("Lisp connection lost.\n");
}

void messageReceived () {
  printf("Message received!\n");
}
