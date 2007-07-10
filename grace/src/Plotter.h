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
class BackView;
class PlotViewport;
class FocusView;

enum PlotType {
  XYPlot = 1,
  XYZPlot,
  MidiPlot,
  VKeyPlot,
  FomusPlot,
  SpearPlot,
  CLMPlot};

///
/// Axis View
///

class AxisView : public Component {

public:
  Axis * axis;
  double _spread; // expansion factor for "zooming" space on axis
  double _ppi;    // pixels per increment (distance between labels)
  double _offset; // pixel position of axis origin
  int orient;     // orientation (horizontal, vertical)
  PlotViewport * viewport;  // back pointer to viewport

 AxisView (PlotViewport* vp, int o)
   : _spread (1.0), _ppi (120.0), _offset (0.0), viewport (0), axis (0) {
    viewport=vp;
    orient=o;
  }
  bool isVertical();
  bool isHorizontal();
  double getSpread() {return _spread;}
  void setSpread(double v) {_spread=v; }
  double getOrigin() {return _offset;}
  void setOrigin(double v) {_offset=v; }  

  bool hasAxis() {return axis != (Axis *)NULL;}
  Axis* getAxis() {return axis;}
  void setAxis(Axis* a) {axis=a;}

  double axisMinimum() {return axis->getMinimum();}
  double axisMaximum() {return axis->getMaximum();}
  int numTicks(){return axis->getTicks();}

  double incrementSize () {
    // size of pixels per increment at current spread
    return( _ppi * _spread);
  }

  double tickSize () {
    // pixel distance between graduals 
    return incrementSize() / axis->getTicks();
  }

  double extent () {
    // size of axis in pixels at current spread. may not be integer
    return incrementSize() * axis->getIncrements();
  }

  double toValue (double pix) {
    // convert pixel position to value in axis coords
    double p = extent() * ( isVertical() ) ? _offset - pix : pix - _offset;
    return axis->getMinimum() + (axis->getRange() * ( p / extent()));
  }
    
  double toPixel (double val) {
    // convert value in axis coords to pixel position
    double p = extent() * ( (val - axis->getMinimum()) / axis->getRange());
    return ( isVertical() ) ? _offset - p : _offset + p;
  }

  void paint (Graphics& g) ;

};

///
/// Plotter
///

class PointClipboard {
 public:
  OwnedArray <LayerPoint> points;
  Layer* layer;
  PointClipboard() {}
  ~PointClipboard() {}
  int size() {return points.size();}
  bool isEmpty() {return (size()==0);}
  LayerPoint* getPoint(int i) {return points[i];}
  Layer* getLayer() {return layer;}
  void set(Layer* layr, SelectedItemSet<LayerPoint*> * sel) {
    layer=layr;
    points.clear();
    for (int i=0;i<sel->getNumSelected(); i++)
      points.add(sel->getSelectedItem(i));
  }
  void clear() {layer=0; points.clear(false);}
  void add(LayerPoint* p) {points.add(p);}
};

class Plotter  : public Component, 
  public SliderListener ,    // for callback from spread slider
  public ScrollBarListener   // for callback from scrollbars
{

 public:
  enum BGStyle {bgSolid = 1, bgGrid, bgTiled };
  enum Orientation {horizontal = 1, vertical };

  // ENUMS define in grace.lisp

  enum PlotterCommand {
    cmdPlotterNew = 98176,
    cmdPlotterOpen = 98432,
    cmdPlotterSave = 98688,
    cmdPlotterSaveAs = 98944,
    cmdPlotterImport = 99200,
    cmdPlotterExport = 99456,
    cmdEditUndo = 99712,
    cmdEditRedo = 99968,
    cmdEditCut = 100224,
    cmdEditCopy = 100480,
    cmdEditPaste = 100736,
    cmdEditSelectAll = 100992,
    cmdEditClear = 101248,
    cmdEditFind = 101504,
    cmdLayerAdd = 101760,
    cmdLayerDelete = 102016,
    cmdLayerSelect = 102272,
    cmdViewStyle = 102528,
    cmdViewVertical = 102784,
    cmdViewBgStyle = 103040,
    cmdViewBgColor = 103296,
    cmdViewBgPlotting = 103552,
    cmdViewBgMousing = 103808,
    cmdViewMouseGuide = 104064,
    cmdComposeDistributions = 104320,
    cmdComposeGenerate = 104576,
    cmdAnalyzeHistogram = 104832,
    cmdAnalyzeDeviation = 105088};

  Axis* shared;
  AxisView * haxview;
  AxisView * vaxview;
  Slider * xspread;
  Slider * yspread;
  PlotViewport * viewport;
  PlotView * plotview;
  BackView * backview;
  FocusView * focusview;
  OwnedArray <Layer> layers;
  UndoManager actions;
  Font font;
  Random * rand; // a private random state
  double zoom;
  double ppp;  // point size (pixels per point)
  int flags;
  PlotType plottype;

  Plotter (PlotType pt) ;
  ~Plotter () ;
  double getZoom() {return zoom;}
  void setZoom(double z) {zoom=z;}
  double getPointSize(){return ppp;}
  void setPointSize(double siz){ppp=siz;}
  PlotType getPlotType() {return plottype;}

  Axis* getSharedAxis() {return shared;}

  //  void setAxisView(Axis* a, Orientation o) ;
  void setHorizontalAxis(Axis* a);
  void setVerticalAxis(Axis* a);


  AxisView * getHorizontalAxisView();
  AxisView * getVerticalAxisView();
  BackView * getBackView();
  PlotView * getPlotView();
  FocusView * getFocusView();
  PlotViewport * getPlotViewport();

  // layers
  int numLayers();
  Layer* getLayer(int i);
  Layer* findLayer(int id);
  Layer* getFocusLayer();
  bool isFocusLayer(Layer* l);
  void setFocusLayer(Layer* l);
  void setFocusVerticalField(int i);
  void addLayer(Layer* l);
  Layer* newLayer(PlotType pt);
  void removeLayer(Layer* l);

  void resized () ;
  void redrawPlotView();
  void redrawBackView();
  void redrawHorizontalAxisView();
  void redrawVerticalAxisView();
  void redrawFocusView();
  BGStyle getBackViewStyle();
  void setBackViewStyle(BGStyle style);
  bool isBackViewPlotting();
  void setBackViewPlotting(bool val);
  void sliderValueChanged (Slider *slider) ;
  void sliderDragStarted (Slider *slider) ;
  void sliderDragEnded (Slider *slider) ;
  void scrollBarMoved (ScrollBar * sb, const double nrs) ;

  void selectAll();
  void deselectAll();
  void clearSelection();
  void moveSelection();

};

///
/// Plotter Window
///

class PlotterWindow : public DocumentWindow,
  public MenuBarModel {

public:
  Plotter * plotter;
  MenuBarComponent * menubar;
  PlotterWindow (PlotType pt) ;
  ~PlotterWindow () ;
  const StringArray getMenuBarNames ();
  const PopupMenu getMenuForIndex (int idx, 
				   const String &name);
  void menuItemSelected (int id, int idx);
  void closeButtonPressed () ;
};

#endif

