/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision: $
// $Date: $ 

#ifndef __TOOLBOX__
#define __TOOLBOX__

#include "juce.h"

namespace Toolbox {

  float rescale (float x, float x1, float x2, float y1, float y2, float b=1.0) ;
  int discrete (float x, float x1, float x2, int y1, int y2, float b=1.0);
  int float_to_fixnum(float f) ;
  float decimals(float val, int places) ;
  float quantize(float val, float step);
  float rhythm_to_seconds(float beats, float tempo=60.0, float beat=.25) ;
  float cents_to_scaler(int cents) ;
  int scaler_to_cents(float scaler);
  float keynum_to_hertz (float kn) ;
  int keynum_to_pc (float kn) ;
  float hertz_to_keynum (float hz) ;

  void ranstate_set(int64 s) ;
  int ran(int i) ;
  float ran(float f) ;
  int ran(int i1, int i2) ;
  float ran(float f1, float f2) ;

  float ranlow() ;
  float ranhigh() ;
  float ranmid() ;
  float ranbeta (float a, float b) ;
  float ranexp (float lambda) ;
  float ranexp2 (float lambda) ;
  float rangauss(float sigma=1, float mu=0) ;
  float rancauchy() ;
  int ranpoisson (float lambda) ;
  float rangamma (float nu) ;
  float ranpink() ;
  float ranbrown() ; 
}


//namespace tb = Toolbox;

#endif
