/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

#include "Layer.h"
//#include <iostream>
using namespace std;

String LayerPoint::valToText(int field, int decimals, String name) {
  String text;
  if (decimals==0)
    text = String( (int)(.5 + getVal(field)) );
  else 
    text = String( getVal(field), decimals );
  if (name == String::empty)
    return text;
  else
    return name + T(" ") + text;
}

Layer::Layer (int ari, String nam, Colour col) 
  : transp(true),
    _x (0),
    _y (1),
    _z (2),
    _defaults ( (LayerPoint *)NULL),
    name (String::empty),
    style (lineandpoint),
    pclass (String::empty)
{
  static int layerid=1;
  arity=ari;
  pstyle=new int[arity];
  for (int i=0;i<arity; i++)
    pstyle[i]=0;
  paxis= new Axis*[arity];
  for(int i=0;i<arity; i++)
    paxis[i]=(Axis *)NULL;
  name=nam;
  color=col;
  id=layerid++;
}
  
Layer::~Layer() {
  printf("in layer delete\n");
  _points.clear(true);

  for (int i=0;i<arity;i++)
    if (paxis[i] != (Axis *)NULL) delete paxis[i];
  delete[] paxis;
  delete[] pstyle;
  printf("leaving layer delete\n");
};

int Layer::numPoints() {
  return _points.size();
}

bool Layer::isPoints() {
  return (_points.size()>0);
}

void Layer::sortPoints() {
  comp00 comp;
  // sort array
  _points.sort(comp);
}

int Layer::addPoint(float x, float y) {
  comp00 comp;
  LayerPoint* p =  new LayerPoint(arity);
  initPoint(p);
  p->setVal(_x,x);
  p->setVal(_y,y);
  _points.addSorted(comp, p);
  return _points.indexOf(p);
}

void Layer::initPoint(LayerPoint* p) {
  // init new point with layer's default point values
  if (_defaults != (LayerPoint *)NULL)
    for (int i=0; i<arity; i++)
      p->vals[i]=_defaults->vals[i];
}

LayerPoint* Layer::getPoint(int i) {return _points[i]; }
int Layer::getPointIndex(LayerPoint* p) {return _points.indexOf(p);}

float Layer::getPointX(int i) {return _points[i]->getVal(_x);}
float Layer::getPointX(LayerPoint* p) {return p->getVal(_x);}

float Layer::getPointY(int i) {return _points[i]->getVal(_y);}
float Layer::getPointY(LayerPoint* p) {return p->getVal(_y);}

float Layer::getPointZ(int i) {return _points[i]->getVal(_z);}
float Layer::getPointZ(LayerPoint* p) {return p->getVal(_z);}

void Layer::setPointX(int i, float f) {_points[i]->setVal(_x, f);}
void Layer::setPointX(LayerPoint* p, float f) {p->setVal(_x, f);}

void Layer::setPointY(int i, float f) {_points[i]->setVal(_y, f);}
void Layer::setPointY(LayerPoint* p, float f) {p->setVal(_y, f);}

void Layer::setPointZ(int i, float f) {_points[i]->setVal(_z, f);}
void Layer::setPointZ(LayerPoint* p, float f) {p->setVal(_z, f);}

void Layer::incPointX(int i, float f) {_points[i]->incVal(_x, f);}
void Layer::incPointX(LayerPoint* p, float f) {p->incVal(_x, f);}

void Layer::incPointY(int i, float f) {_points[i]->incVal(_y, f);}
void Layer::incPointY(LayerPoint* p, float f) {p->incVal(_y, f);}

void Layer::incPointZ(int i, float f) {_points[i]->incVal(_z, f);}
void Layer::incPointZ(LayerPoint* p, float f) {p->incVal(_z, f);}

void Layer::mulPointX(int i, float f) {_points[i]->mulVal(_x, f);}
void Layer::mulPointX(LayerPoint* p, float f) {p->mulVal(_x, f);}

void Layer::mulPointY(int i, float f) {_points[i]->mulVal(_y, f);}
void Layer::mulPointY(LayerPoint* p, float f) {p->mulVal(_y, f);}

void Layer::mulPointZ(int i, float f) {_points[i]->mulVal(_z, f);}
void Layer::mulPointZ(LayerPoint* p, float f) {p->mulVal(_z, f);}

void Layer::setPoint(int i, float x, float y) {
  _points[i]->setVal(_x, x);
  _points[i]->setVal(_y, y);
}
void Layer::setPoint(LayerPoint* p, float x, float y) {
  p->setVal(_x, x);
  p->setVal(_y, y);
}

void Layer::incPoint(int i, float x, float y) {
  _points[i]->incVal(_x, x);
  _points[i]->incVal(_y, y);
}
void Layer::incPoint(LayerPoint* p, float x, float y) {
  p->incVal(_x, x);
  p->incVal(_y, y);
}

void Layer::mulPoint(int i, float x, float y) {
  _points[i]->mulVal(_x, x);
  _points[i]->mulVal(_y, y);
}
void Layer::mulPoint(LayerPoint* p, float x, float y) {
  p->mulVal(_x, x);
  p->mulVal(_y, y);
}

void Layer::removePoint(int i) {
  _points.remove(i, false);
}
void Layer::removePoint(LayerPoint* p) {
  _points.removeObject(p, false);
}

void Layer::deletePoint(int i) {
  _points.remove(i, true);
}
void Layer::deletePoint(LayerPoint* p) {
  _points.removeObject(p, true);
}

String Layer::exportPoint(LayerPoint* point, int fmask, int fmat,
			  bool sal, int deci) {
  // point: the point to export
  // fmask: bit mask, each 1 bit means that field is included
  // fmat: 1=envelope, 2=point record, 3=object definition
  String text=String::empty;

  for (int i=0; i<arity; i++) 
    if ( fmask & (1 << i) ) { // check field mask
      String name=String::empty;
      if (fmat==3)  // add field keyword for objects
	if (sal)
	  name=fields[i].toLowerCase() + T(":");
	else
	  name=T(":") + fields[i].toLowerCase();
      // add delimiter if not at start.
      if (text != String::empty)
	text += (sal && (fmat==3)) ? T(", ") : T(" ");
      text += point->valToText(i, deci, name);
    }

  if (fmat==2)    // point records are themselves lists
    if (sal) 
      text = T("{") + text + T("}");
    else
      text = T("(") + text + T(")"); 
  else if (fmat==3)
    if (sal)
      text = T("make(<") + getPointClass() + T(">, ") + text + T(")");
    else
      text = T("(make-instance '") + getPointClass() + T(" ") + text + T(")");
  return text;
}

/*
 * Point Layers
 */

XYLayer::XYLayer(String s, Colour c) 
  : Layer(2, s, c)
{
  //const tchar* const names [] = { T("X"), T("Y"), 0 };
  //  params=StringArray((const tchar**) menuNames);
  _x=0;
  _y=1;
  fields.add(T("X"));
  fields.add(T("Y"));
  setAxis(0, (Axis *)NULL); 
  setAxis(1, new Axis(Axis::normalized)); 
  pstyle[1]=Layer::lineandpoint;
}

/*
 * Midi Layers
 */

MidiLayer::MidiLayer(String s, Colour c) 
  : Layer(4, s, c) 
{
  pclass=T("midi");
  // Time Duration Keynum Amplitude
  fields.add(T("Time"));
  fields.add(T("Duration"));
  fields.add(T("Keynum"));
  fields.add(T("Amplitude"));

  setAxis(0, (Axis *)NULL); 
  setAxis(1, (Axis *)NULL); 
  setAxis(2, new Axis(Axis::keynum));
  setAxis(3, new Axis(Axis::normalized));

  pstyle[1]=Layer::vlineandpoint;
  pstyle[2]=Layer::hbox;
  pstyle[3]=Layer::vlineandpoint;

  _x=0;
  _y=2;   // Y is keynum field
  _z=1;   // Z is duration field
  _defaults= new LayerPoint(arity);
  _defaults->setVal(0, 0.0);
  _defaults->setVal(1, 0.5);
  _defaults->setVal(2, 60.0);
  _defaults->setVal(3, 0.5);
  style=Layer::hbox;
}

MidiLayer::~MidiLayer() {
  // DOES THE CALL TO ~Layer() HAPPEN IF THIS METHOD IS HERE?
  printf("in midilayer delete\n");
  delete _defaults;
}

