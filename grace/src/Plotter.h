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
  CLMPlot};

///
/// Axis View
///

class AxisView : public Component {

public:
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
  double offset;  // pixel position of axis origin
  int orient;     // orientation (horizontal, vertical)
  bool logr;      // axis is logarithmic
  PlotViewport * viewport;  // back pointer to viewport

  AxisView (AxisType typ)
    : type(0), from (0.0), to (1.0), by (.25), ticks (4), zoom (1.0),
    ppi (120.0), offset (0.0), decimals (2), 
    viewport (0)  {
    init(typ);
  }

  void init(AxisType t);
  bool isVertical();
  bool isHorizontal();
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
  enum BGStyle {bgSolid = 1, bgGrid, bgTiled };
  enum Orientation {horizontal = 1, vertical };

  /*  Plotter Command IDs have lower 8 bits available for encoding
      command information. Use this Lisp code to generate the C
      declaration:

(defun plotter-enums(start &rest names)
  (format t "  enum PlotterCommand {~%")
  (loop with m = (1- (length names))
     for n in names for i from 0
     do (format t "    cmd~A = ~D~:[,~;};~]~%" n (ash (+ start i) 8) (= i m))))
(plotter-enums 0 "FileNew" "FileOpen" "FileSave" "FileSaveAs" "FileImport" "FileExport" "EditCut" "EditCopy" "EditPaste" "EditClear" "EditSelectAll" "EditFind" "LayerAdd" "LayerDelete" "LayerSelect" "ViewStyle" "ViewBgStyle" "ViewBgColor" "ViewBgPlotting" "ViewBgMousing" "ViewMouseGuide" "HelpCommands")

   */

  enum PlotterCommand {
    cmdFileNew = 0,
    cmdFileOpen = 256,
    cmdFileSave = 512,
    cmdFileSaveAs = 768,
    cmdFileImport = 1024,
    cmdFileExport = 1280,
    cmdEditCut = 1536,
    cmdEditCopy = 1792,
    cmdEditPaste = 2048,
    cmdEditClear = 2304,
    cmdEditSelectAll = 2560,
    cmdEditFind = 2816,
    cmdLayerAdd = 3072,
    cmdLayerDelete = 3328,
    cmdLayerSelect = 3584,
    cmdViewStyle = 3840,
    cmdViewBgStyle = 4096,
    cmdViewBgColor = 4352,
    cmdViewBgPlotting = 4608,
    cmdViewBgMousing = 4864,
    cmdViewMouseGuide = 5120,
    cmdHelpCommands = 5376};

  AxisView * xaxis;
  AxisView * yaxis;
  Slider * xzoom;
  Slider * yzoom;
  PlotViewport * viewport;
  PlotView * plotview;
  BackView * backview;
  FocusView * focusview;
  OwnedArray <Layer> layers;
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

  AxisView * getAxisView(Orientation o);
  void setAxisView(AxisView * a, Orientation o) ;

  BackView * getBackView();
  PlotView * getPlotView();
  FocusView * getFocusView();
  PlotViewport * getPlotViewport();

  // layers
  void addLayer(Layer * l);
  int numLayers();
  Layer * getLayer(int i);
  Layer * findLayer(int id);
  Layer * getFocusLayer();
  bool isFocusLayer(Layer * l);
  void setFocusLayer(Layer * l);

  void resized () ;
  void redrawPlotView();
  void redrawBackView();
  BGStyle getBackViewStyle();
  void setBackViewStyle(BGStyle style);
  bool isBackViewPlotting();
  void setBackViewPlotting(bool val);
  void sliderValueChanged (Slider *slider) ;
  void sliderDragStarted (Slider *slider) {};
  void sliderDragEnded (Slider *slider) {};
  void scrollBarMoved (ScrollBar * sb, const double nrs) ;

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
  const StringArray getMenuBarNames (MenuBarComponent* mbar);
  const PopupMenu getMenuForIndex (MenuBarComponent* mbar, int idx, 
				   const String &name);
  void menuItemSelected (MenuBarComponent* mbar, int id, int idx);
  void closeButtonPressed () ;
};

#endif

