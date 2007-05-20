/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

#include "Layer.h"
#include <iostream>
using namespace std;


Layer::Layer (String nam, Colour col) 
  : transp(true),
    _x (0),
    _y (1),
    _z (2),
    _defaults ( (LayerPoint *)NULL),
    arity (2),
    name (String::empty),
    style(lineandpoint)
{
  static int layerid=100;
  name=nam;
  color=col;
  id=++layerid;
}
  
Layer::~Layer() {
  _points.clear(true);
};

int Layer::numPoints() {
  return _points.size();
}

bool Layer::isPoints() {
  return (_points.size()>0);
}

void Layer::sortPoints(SelectedItemSet<int> * sel) {
  comp00 comp;
  // have to recalculate selection array after sort
  // mark each point in selection as being selected
  for (int i=0;i < sel->getNumSelected(); i++) {
    int h=sel->getSelectedItem(i);
    _points[h]->flags=LayerPoint::selected;
  }
  // sort array
  _points.sort(comp);
  // update selection with new handles
  if (sel->getNumSelected() > 0) {
    sel->deselectAll();
    for (int h=0; h < _points.size(); h++) {
      if ( _points[h]->flags == LayerPoint::selected ) {
	_points[h]->flags=0;
	sel->addToSelection(h);
      }
    }
  }
}

int Layer::addPoint(float x, float y) {
  comp00 comp;
  LayerPoint * p =  new LayerPoint(arity);
  initPoint(p);
  p->setVal(_x,x);
  p->setVal(_y,y);
  _points.addSorted(comp, p);
  return _points.indexOf(p);
}

void Layer::initPoint(LayerPoint * p) {
  // init new point with layer's default point values
  if (_defaults != (LayerPoint *)NULL)
    for (int i=0; i<arity; i++)
      p->vals[i]=_defaults->vals[i];
}

float Layer::getPointX(int i) {return _points[i]->getVal(_x);}
float Layer::getPointY(int i) {return _points[i]->getVal(_y);}
float Layer::getPointZ(int i) {return _points[i]->getVal(_z);}

void Layer::setPointX(int i, float f) {_points[i]->setVal(_x, f);}
void Layer::setPointY(int i, float f) {_points[i]->setVal(_y, f);}
void Layer::setPointZ(int i, float f) {_points[i]->setVal(_z, f);}

void Layer::incPointX(int i, float f) {_points[i]->incVal(_x, f);}
void Layer::incPointY(int i, float f) {_points[i]->incVal(_y, f);}
void Layer::incPointZ(int i, float f) {_points[i]->incVal(_z, f);}

void Layer::mulPointX(int i, float f) {_points[i]->mulVal(_x, f);}
void Layer::mulPointY(int i, float f) {_points[i]->mulVal(_y, f);}
void Layer::mulPointZ(int i, float f) {_points[i]->mulVal(_z, f);}

void Layer::setPoint(int i, float x, float y) {
  _points[i]->setVal(_x, x);
  _points[i]->setVal(_y, y);
}

void Layer::incPoint(int i, float x, float y) {
  _points[i]->incVal(_x, x);
  _points[i]->incVal(_y, y);
}

void Layer::mulPoint(int i, float x, float y) {
  _points[i]->mulVal(_x, x);
  _points[i]->mulVal(_y, y);
}

void Layer::removePoint(int i) {
  _points.remove(i, false);
}

void Layer::deletePoint(int i) {
  _points.remove(i, true);
}

/*
 * Point Layers
 */

XYLayer::XYLayer(String s, Colour c) 
  : Layer(s, c)
{
  arity=2;
  _x=0;
  _y=1;
  style=Layer::lineandpoint;
}

/*
 * Midi Layers
 */

MidiLayer::MidiLayer(String s, Colour c) 
  : Layer(s, c)
{
  arity=5;
  _x=0;
  _y=2;   // Y is keynum field
  _z=1;   // Z is duration field
  _defaults= new LayerPoint(arity);
  _defaults->setVal(0, 0.0);
  _defaults->setVal(1, 0.5);
  _defaults->setVal(2, 60.0);
  _defaults->setVal(3, 0.5);
  _defaults->setVal(4, 0.0);

  style=Layer::hbox;
  //style=Layer::lineandpoint;
}

MidiLayer::~MidiLayer() {
  // DOES THE CALL TO ~Layer() HAPPEN IF THIS METHOD IS HERE?
  delete _defaults;
}

