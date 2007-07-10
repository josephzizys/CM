/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

#ifndef __LAYER__
#define __LAYER__

#include "juce.h"

// LayerPoint: a point with a (variable) number of plottable float fields.

class LayerPoint {
 public:
  float * vals;
 LayerPoint(int n) {vals=new float[n];}
  ~LayerPoint() {delete[] vals;}
  float getVal(int i) {return vals[i];}
  void setVal(int i, float f) {vals[i]=f;} 
  void incVal(int i, float f) {vals[i]+=f;} 
  void subVal(int i, float f) {vals[i]-=f;} 
  void mulVal(int i, float f) {vals[i]*=f;} 
  void divVal(int i, float f) {vals[i]/=f;} 
  String valToText(int field, int decimals=2,
		   String name=String::empty);
};

class comp00 {
  // compares field 0 in Layer points
 public:
  static int compareElements(LayerPoint* p1, LayerPoint* p2) {
    if ( p1->vals[0] < p2->vals[0] )
      return -1;
    else 
      return 1;
  }
};

class Axis {
 public:
  enum AxisType {
    normalized = 0,
    percentage,
    keynum,
    amplitude,
    seconds,
    frequency,
    hertz,        // log plotting (not implemented yet)
    mididata,     // 0-127 display
    unitcircle
  };
  String name;
  AxisType type; 
  double from;    // minimum value
  double to;      // maximum value
  double by;      // inc along axis
  int ticks;      // number of ticks per inc to draw
  int decimals;   // num decimals to show in labels

  void init (AxisType typ) {
    // init axis data according to common "templates"
    name=String::empty;
    decimals=2;
    type=typ;
    switch (typ) {
    case percentage :
      from=0.0; to=100.0; by=25.0; ticks=5;
      break;
    case keynum :
      from=0.0; to=127; by=12.0; ticks=12;
      break;
    case mididata :
      from=0.0; to=127; by=8.0; ticks=8;
      break;
    case seconds :
      from=0.0; to=60.0; by=1.0; ticks=4;
      break;
    case frequency :  // linear freq
      from=0.0; to=11025.0; by=1.0; ticks=2;
      break;
    case hertz :  // log freq
      from=8.175798; to=16744.035; by=2.0; ticks=6; 
      break;
    case unitcircle :
      from=-1.0; to=1.0; by=.25; ticks=4;
    case normalized :
    case amplitude :
    default :
      from=0.0; to=1.0; by=0.25; ticks=5;
      break;
    }
  }

  Axis (AxisType typ) {init(typ);}
  ~Axis () {}
  double getMinimum() {return from;}
  void setMinimum(double v) {from=v;}
  double getMaximum() {return to;}
  void setMaximum(double v) {to=v;}
  double getIncrement() {return by;}
  void setIncrement(double v) {by=v;}
  double getIncrements() {return (to-from)/by;}
  int getTicks() {return ticks;}
  int setTicks(int v) {ticks=v;}
  int getDecimals() {return decimals;}
  void setDecimals(int v) {decimals=v;}
  double getRange() {return to-from;}
  float rescale(float val, Axis* orig){
    return (getMinimum() + 
	    (getRange() * ((val - orig->getMinimum()) / 
			   orig->getRange())));
  }
};

class Layer {
 public:
  enum {      
    // drawing style info (or'd together) FIX this should be moved.
    line = 1,
    point = 2,
    bar = 4,
    box = 8,
    vertical = 16,
    horizontal = 32,
    lineandpoint = 3,
    vline = 17,
    vlineandpoint = 19,
    vbar = 20,
    hbox = 40
  };

  /* layer points kept in X sorted order. */

  OwnedArray <LayerPoint> _points;

  /* A preallocated point holding default field values that new points
     will be merged with to produce a fully specfifed point. */

  LayerPoint * _defaults; 

  /* _x _y and _z hold the point field indices used to graph x y and z
     point values. these indicies can be changed on the fly so that a
     layer can display differnet dimensions of data in the same set of
     points */

  int _x, _y, _z; 

  /* axis objects, one for each field in points  */
  OwnedArray <Axis> axes;
  Axis** paxis;
  StringArray fields;
  int* pstyle;

  int arity;        // number of fields in points
  String pclass;    // point class name
  String name;      // layer name
  int id;           // unique id
  Colour color;     // line and point color
  int style;        // drawing style

  bool transp;      // allow back plots to be visible. unused
  
  Layer(int ari, String nam, Colour col);
  ~Layer();

  int getLayerArity() {return arity;}
  void setLayerArity(int a) {arity=a;}
  int getLayerID(){return id;}
  void setLayerID(int i){id=i;}
  Colour getLayerColor(){return color;}
  void setLayerColor(Colour c){color=c;}
  String getLayerName(){return name;}
  void setLayerName(String n){name=n;}
  bool isTransparent() {return transp;}
  void setTransparent(bool b) {transp=b;}  
  //  int getLayerStyle(){return style;}
  //  void setLayerStyle(int s){style=s;}
  int getLayerStyle(){return pstyle[_y];}
  void setLayerStyle(int s){pstyle[_y]=s;}
  bool isDrawStyle(int i) {return (pstyle[_y] & i);}
  int numPoints() ;
  bool isPoints() ;
  void sortPoints () ;
  int addPoint(float x, float y) ;
  void initPoint(LayerPoint* p);

  String getPointClass() {return pclass;}
  void setPointClass(String c){pclass=c;}

  LayerPoint* getPoint(int i);
  int getPointIndex(LayerPoint* p);

  float getPointX(int i) ;
  float getPointX(LayerPoint* p) ;
  float getPointY(int i) ;
  float getPointY(LayerPoint* p) ;
  float getPointZ(int i) ; 
  float getPointZ(LayerPoint* p) ;

  void setPointX(int i, float f) ;
  void setPointX(LayerPoint* p, float f) ;
  void setPointY(int i, float f) ;
  void setPointY(LayerPoint* p, float f) ;
  void setPointZ(int i, float f) ;
  void setPointZ(LayerPoint* p, float f) ;

  void incPointX(int i, float f) ;
  void incPointX(LayerPoint* p, float f) ;
  void incPointY(int i, float f) ;
  void incPointY(LayerPoint* p, float f) ;
  void incPointZ(int i, float f) ;
  void incPointZ(LayerPoint* p, float f) ;

  void mulPointX(int i, float f) ;
  void mulPointX(LayerPoint* p, float f) ;
  void mulPointY(int i, float f) ;
  void mulPointY(LayerPoint* p, float f) ;
  void mulPointZ(int i, float f) ;
  void mulPointZ(LayerPoint* p, float f) ;

  void setPoint(int i, float x, float y) ;
  void setPoint(LayerPoint* p, float x, float y);

  void incPoint(int i, float x, float y) ;
  void incPoint(LayerPoint* p, float x, float y);

  void mulPoint(int i, float x, float y) ;
  void mulPoint(LayerPoint* p, float x, float y);

  void removePoint(int i) ;
  void removePoint(LayerPoint* p) ;

  void deletePoint(int i) ;
  void deletePoint(LayerPoint* p) ;

  //  Axis* getAxis(int i) {return axes[i];}
  //  void setAxis(int i, Axis* a){axes.set(i,a,false);} 
  Axis* getAxis(int i) {return paxis[i];}
  void setAxis(int i, Axis* a) {paxis[i]=a;}
  Axis* getXAxis() {return getAxis(_x);}
  Axis* getYAxis() {return getAxis(_y);}

  int getXField() {return _x;}
  int getYField() {return _y;}
  int getZField() {return _z;}
  void setXField(int f) {_x=f;}
  void setYField(int f) {_y=f;}
  void getZField(int f) {_z=f;}
  String getFieldName(int f) {return fields[f];}
  int getFieldIndex(String f) {return fields.indexOf(f, true);}
  void addFieldName(String n){fields.add(n);}
  String exportPoint(LayerPoint* p, int fmask, int fmat,
		     bool sal, int deci=2);
};

class XYLayer : public Layer {
 public:
  XYLayer(String s, Colour c);
  ~XYLayer() { }  // DOES THIS HAVE TO CALL ~LAYER ????
};

class MidiLayer : public Layer {
 public:
  MidiLayer(String s, Colour c) ;
  ~MidiLayer() ;
};


/*
class FomusLayer : public Layer {
 public:
  FomusLayer(String s, Colour c) ;
  ~FomusLayer() ;
};

class SpearLayer : public Layer {
 public:
  SpearLayer(String s, Colour c) ;
  ~SpearLayer() ;
  };

class VKeyLayer : public Layer {
 public:
  VKeyLayer(String s, Colour c) ;
  ~VKeyLayer() ;
};

*/


#endif
