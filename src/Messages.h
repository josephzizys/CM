/*=======================================================================*
  Copyright (c) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify
  it under the terms of the Lisp Lesser Gnu Public License. The text
  of this agreement is available at http://www.cliki.net/LLGPL
 *=======================================================================*/

#ifndef MESSAGES_H
#define MESSAGES_H

#include "Libraries.h"

class AsyncMessage
{
 public:
  int type;
  String text;
  int data;
  AsyncMessage(int typ)
  {
    type=typ;
    text=String::empty;
    data=0;
  }
  AsyncMessage(int typ, int dat)
  {
    type=typ;
    data=dat;
    text=String::empty;
  }
  AsyncMessage(int typ, String txt)
  {
    type=typ;
    text=txt;
    data=0;
  }
  AsyncMessage(int typ, int dat, String txt)
  {
    type=typ;
    text=txt;
    data=dat;
  }
  ~AsyncMessage() {}
};

#endif
