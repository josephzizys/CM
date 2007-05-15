/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

#ifndef RESOURCES
#define RESOURCES

#include "juce.h"

const char * getGraceSplashData() ;
int getGraceSplashSize();

class GraceSplash  : public SplashScreen
{
public:
  GraceSplash () {};
  ~GraceSplash();
  // Binary resources:
  static const char* grace_png;
  static const int grace_pngSize;

  //    void paint (Graphics& g);
  //    void resized();
  //    juce_UseDebuggingNewOperator
  //private:
  //    GraceSplash (const GraceSplash&);
  //    const GraceSplash& operator= (const GraceSplash&);
};

#endif 
