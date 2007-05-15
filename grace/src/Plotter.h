/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 


#ifndef __PLOTTER__
#define __PLOTTER__
#include "juce.h"
#include "Layer.h"

class PlotView;         // defined in Plotter.cpp
class PlotViewport;
class FocusView;

enum PlotType {
  XYPlot = 1,
  XYZPlot,
  MidiPlot,
  VKeyPlot,
  FomusPlot,
  SpearPlot
  };

///
/// Axis View
///

class AxisView : public Component {

public:

  enum AxisOrientation {
    // could add others: point color, Z axis, etc
    horizontal = 1,
    vertical  
  };

  enum AxisType {
    untyped = 0,
    normalized,
    percentage,
    keynum,
    amplitude,
    seconds,
    frequency,
    hertz,        // log plotting (not implemented yet)
    mididata,     // 0-127 display
    unitcircle
 };
  int type; 
  double from;    // minimum value
  double to;      // maximum value
  double by;      // inc along axis
  int ticks;      // number of ticks per inc to draw
  int decimals;   // num decimals to show in labels
  double zoom;    // zoom factor
  double ppi;     // pixels per increment (distance between labels)
  double ppp;     // pixels per point (point size)
  double offset;  // pixel position of axis origin
  bool vert;      // axis is vertical
  bool logr;      // axis is logarithmic
  PlotViewport * viewport;  // back pointer to viewport

  AxisView (AxisType typ, AxisOrientation ori)
    : type(0), from (0.0), to (1.0), by (.25), ticks (4), zoom (1.0),
    ppi (120.0), ppp (8.0), offset (0.0), decimals (2), 
    viewport ((PlotViewport *)NULL)  {

    init(typ, ori);
  }

  void init(AxisType a, AxisOrientation b);
  bool isVertical() { return vert; }
  bool isHorizontal() { return !vert; }
  bool isLinear() { return !logr; }
  bool isLogarithmic() { return logr; }
  double getZoom() { return zoom; }
  double setZoom(double z) { return zoom=z; }
  int getTicks() { return ticks; }
  int setTicks(int t) { return ticks=t; }
  void setRange(double a, double b, double c) {
    from=a; to=b; by=c;
  }

  double range () {
    // range between axis min and max
    return to-from;
  }

  double increments() {
    // total number of divisions along axis. may not be integer
    return (to-from)/by;
  }

  double tickSize () {
  // pixel distance between graduals 
    return (ppi * zoom) / ticks;
  }

  double incrementSize () {
  // size of pixels per increment at current zoom
    return( ppi * zoom);
  }

  double size () {
    // size of axis in pixels at current zoom. may not be integer
    return (ppi * zoom) * increments();
  }

  double toValue (double pix) {
    // convert pixel position to value in axis coords
    double p = size() * ( isVertical() ) ? offset - pix : pix - offset;
    return from + (range() * ( p / size()));
  }
    
  double toPixel (double val) {
    // convert value in axis coords to pixel position
    double p = size() * ( (val-from) / range());
    return ( isVertical() ) ? offset - p : offset + p;
  }

  void paint (Graphics& g) ;

};

///
/// Plotter
///

class Plotter  : public Component, 
  public SliderListener ,    // for callback from zoom slider
  public ScrollBarListener   // for callback from scrollbars
{

 public:
  AxisView * xaxis;
  AxisView * yaxis;
  Slider * xzoom;
  Slider * yzoom;
  PlotViewport * viewport;
  PlotView * plotview;
  FocusView * focusview;
  OwnedArray <Layer> layers;
  Font font;
  Random * rand; // a private random state

  Plotter (PlotType pt) ;
  ~Plotter () ;
  void setAxisView(AxisView * a) ;
  void addLayer(Layer * l);
  int numLayers();
  Layer * getLayer(int i);
  Layer * findLayer(int id);
  Layer * getFocusLayer();
  void setFocusLayer(Layer * l);

  void resized () ;
  void redrawPlotView();
  void sliderValueChanged (Slider *slider) ;
  void sliderDragStarted (Slider *slider) {};
  void sliderDragEnded (Slider *slider) {};
  void scrollBarMoved (ScrollBar * sb, const double nrs) ;

};

///
/// Plotter Window
///

class PlotterWindow  : public DocumentWindow {

public:
  Plotter * plotter;
  PlotterWindow (PlotType pt) ;
  ~PlotterWindow () ;
  void closeButtonPressed () ;
};

#endif

