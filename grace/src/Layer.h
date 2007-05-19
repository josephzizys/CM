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
  enum {selected = 1, muted = 2};
  int flags;
  float * vals;
 LayerPoint(int n) : flags(0) {vals=new float[n];}
  ~LayerPoint() {delete[] vals;}
  float getVal(int i) {return vals[i];}
  void setVal(int i, float f) {vals[i]=f;} 
  void incVal(int i, float f) {vals[i]+=f;} 
  void subVal(int i, float f) {vals[i]-=f;} 
  void mulVal(int i, float f) {vals[i]*=f;} 
  void divVal(int i, float f) {vals[i]/=f;} 
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

  /* The layer points kept in X sorted order. */
  OwnedArray <LayerPoint> _points;

  /* A preallocated point holding default field values that new points
     will be merged with to produce a fully specfifed point. */
  LayerPoint * _defaults;  // default values for new points

  /* _x _y and _z are point field indexes that the plotter will use to
     access values to plot. In other words, there is no hardwired X, Y
     or Z values, a layer can display ANY field (assuming of course
     that the current axis is correctly configured for the values. */

  int _x, _y, _z;   // indexes into point fields for X Y Z values

  int arity;        // arity of points
  String name;      // layer name
  int id;           // unique id
  Colour color;     // line and point color
  int style;        // drawing style
  int bgstyle;      // background style
  bool transp;      // allow back plots to be visible
  
  Layer(String nam, Colour col);
  ~Layer();

  int getLayerArity() {return arity;}
  void setLayerArity(int a) {arity=a;}
  int getLayerID(){return id;}
  void setLayerID(int i){id=i;}
  Colour getLayerColor(){return color;}
  void setLayerColor(Colour c){color=c;}
  String getLayerName(){return name;}
  void setLayerName(String n){name=n;}
  int getLayerBGStyle() {return bgstyle;}
  void setLayerBGStyle(int s) { bgstyle=s;}
  bool isTransparent() {return transp;}
  void setTransparent(bool b) {transp=b;}  
  int getLayerStyle(){return style;}
  void setLayerStyle(int s){style=s;}
  bool isDrawStyle(int i) {return (style & i);}
  int numPoints() ;
  bool isPoints() ;
  void sortPoints (SelectedItemSet<int> * sel) ;
  int addPoint(float x, float y) ;
  void initPoint(LayerPoint * p);
  float getPointX(int i) ;
  float getPointY(int i) ;
  float getPointZ(int i) ; 
  void setPointX(int i, float f) ;
  void setPointY(int i, float f) ;
  void setPointZ(int i, float f) ;
  void incPointX(int i, float f) ;
  void incPointY(int i, float f) ;
  void incPointZ(int i, float f) ;
  void mulPointX(int i, float f) ;
  void mulPointY(int i, float f) ;
  void mulPointZ(int i, float f) ;

  void setPoint(int i, float x, float y) ;
  void incPoint(int i, float x, float y) ;
  void mulPoint(int i, float x, float y) ;
  void removePoint(int i) ;
  void deletePoint(int i) ;
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
