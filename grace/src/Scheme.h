/*
 *  Scheme.h
 *  
 *
 *  Created by todd ingalls on 9/1/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __GRACESCHEME__
#define __GRACESCHEME__
#include "juce.h"
#include "chicken.h"

class ConsoleWindow;

#include "Console.h"


//extern "C" {
//  void C_ccall C_grace_toplevel(C_word c,C_word t0,C_word t1) C_noret;
//}
#include "Nodes.h"

class Node;

class SchemeMessage
{
 public:
  enum {SCHEME_STRING, SCHEME_NODE};
  SchemeMessage( String str ) ;
  SchemeMessage( Node* n ) ;
  ~SchemeMessage();
  int type;
  String string;
  Node *node;
};




class SchemeThread : public Thread
{
 public:
  enum {SCHEME_STRING, SCHEME_NODE};
  SchemeThread(String name, ConsoleWindow* win);
  ~SchemeThread();
  void run();
  void handleMessage(SchemeMessage* message);
  void insertMessage(SchemeMessage* message);
  OwnedArray<SchemeMessage, CriticalSection> messageBuffer;
  ConsoleWindow* console;
  String EvalString;
};

#endif
