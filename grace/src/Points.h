/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision: 1312 $
// $Date: 2007-07-10 18:25:53 -0500 (Tue, 10 Jul 2007) $ 

#ifndef __POINTS__
#define __POINTS__

#include "juce.h"

class PointField {
  String name;
  int type;
  float dval;
  double from;  // used for displaying in plotte
  double to;
  double by;
  int ticks;

 public:
  enum AxisType {
    Float=0,
    Integer,
    Normalized,
    Percentage,
    Keynum,
    Amplitude,
    Seconds,
  };
  PointField(XmlElement *xml) ;
  ~PointField() {}
  String getName() {return name;}
  void setName(String n) {name=n;}
  int getType() {return type;}
  void setType(int t) {type=t;}
  String getTypeName();
  float getDefault() {return dval;}
  void setDefault(float d) {dval=d;}
  double getMinimum() {return from;}
  void setMinimum(double m) {from=m;}
  double getMaximum() {return to;}
  void setMaximum(double m) {to=m;}
  double getIncrement() {return by;}
  void setIncrement(double i) {by=i;}
  double getIncrements() {return (to-from)/by;}
  int getTicks() {return ticks;}
  int setTicks(int t) {ticks=t;}
  double getRange() {return to-from;}
  XmlElement* toXml();
};

#endif
