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
    style(lineandpoint),
    bgstyle (2)    // 2=bgGrid. this should not be part of layers...
{
  static int layerid=100;
  name=nam;
  color=col;
  id=++layerid;
}
  
Layer::~Layer() {
  _selection.clear(false);
  _points.clear(true);
};

int Layer::numPoints() {
  return _points.size();
}

bool Layer::isPoints() {
  return (_points.size()>0);
}

void Layer::sortPoints() {
  comp00 comp;
  _points.sort(comp);
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

float Layer::getPointX(int i) {
  return _points[i]->getVal(_x);
}

float Layer::getPointY(int i) {
  return _points[i]->getVal(_y);
}

float Layer::getPointZ(int i) {
  return _points[i]->getVal(_z);
}

float Layer::getSelPointX(int i) {
  return _selection[i]->getVal(_x);
}

float Layer::getSelPointY(int i) {
  return _selection[i]->getVal(_y);
}

float Layer::getSelPointZ(int i) {
  return _selection[i]->getVal(_z);
}

void Layer::setPointX(int i, float f) {
  _points[i]->setVal(_x, f);
}

void Layer::setPointY(int i, float f) {
  _points[i]->setVal(_y, f);
}

void Layer::setPointZ(int i, float f) {
  _points[i]->setVal(_z, f);
}

void Layer::setPointXY(int i, float x, float y) {
  _points[i]->setVal(_x, x);
  _points[i]->setVal(_y, y);
}

void Layer::setSelPointXY(int i, float x, float y) {
  _selection[i]->setVal(_x, x);
  _selection[i]->setVal(_y, y);
}

void Layer::incSelPointXY(int i, float x, float y) {
  _selection[i]->incVal(_x, x);
  _selection[i]->incVal(_y, y);
}

void Layer::setPointXYZ(int i, float x, float y, float z) {
  _points[i]->setVal(_x, x);
  _points[i]->setVal(_y, y);
  _points[i]->setVal(_z, z);
}

void Layer::removePoint(int i) {
  _points.remove(i, false);
}

void Layer::deletePoint(int i) {
  _points.remove(i, true);
}

bool Layer::isSelection() {
  return (_selection.size() > 0);
}

int Layer::numSelected() {
  return _selection.size();
}

void Layer::clearSelection() {
  _selection.clear(false);   // DONT delete!
}

void Layer::removeSelection(int i) {
  _selection.removeObject(_points[i], false);
}

void Layer::setSelection(int i) {
  clearSelection();
  addSelection(i);
}

void Layer::addSelection(int i) {
  _selection.add(_points[i]);
}

bool Layer::isSelected(int i) {
  return _selection.contains(_points[i]);
}

void Layer::printSelection() {
  cout << "#<selection:";
  for (int i=0; i<numSelected() ; i++)
    cout << " " << _points.indexOf(_selection[i]) ;
  cout << ">" << endl;
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

