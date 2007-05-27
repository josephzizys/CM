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

/*

;; Grace menu command IDS are organized in "menubar blocks" and have
;; their lower 7 bits available for encoding command information. each
;; menubar block has max 128 commands. Use this lisp code to generate
;; the enum definition for a menubar:

(in-package :cm)

(defun enums (block enumname &rest names)
  (let* ((cmdinfo #xFF)
         (blockwidth (* 128 cmdinfo))
	 (blockstart (* blockwidth block)))
  (format t "  enum ~A {~%" enumname)
  (loop with m = (length names)
     for n in names for i from 1
     do (if (= i 128) (error "too many commands, block size = 128"))
     (format t "    cmd~A = ~D~:[,~;};~]~%" n
	     (+ (ash i 8) blockstart)
	     (= i m)))))

(enums 1 "ConsoleCommand" "GraceEditorNew" "GraceEditorOpen" 
         "GracePlotterNew" "GracePreferences" "GraceQuit"
	 "EditCopy" "EditSelectAll"
	 "ViewFonts"  "ViewThemes"
	 "AudioMidiSetup" "AudioAudioSetup"
	 "LispRestart" "LispInputTracing" "LispErrorTracing"
	 "HelpConsole" "HelpAboutGrace")

(enums 2 "PlotterCommand" "PlotterNew" "PlotterOpen" "PlotterSave" "PlotterSaveAs"
         "PlotterImport" "PlotterExport"
         "EditCut" "EditCopy" "EditPaste" "EditClear" "EditSelectAll" "EditFind"
         "LayerAdd" "LayerDelete" 
	 "LayerSelect" "ViewStyle" "ViewBgStyle" "ViewBgColor" "ViewBgPlotting"
	 "ViewBgMousing" "ViewMouseGuide" 
	 "ComposeDistributions" "ComposeGenerate"
	 "AnalyzeHistogram" "AnalyzeDeviation"
	 "HelpCommands")



   */

  enum PlotterCommand {
    cmdPlotterNew = 65536,
    cmdPlotterOpen = 65792,
    cmdPlotterSave = 66048,
    cmdPlotterSaveAs = 66304,
    cmdPlotterImport = 66560,
    cmdPlotterExport = 66816,
    cmdEditCut = 67072,
    cmdEditCopy = 67328,
    cmdEditPaste = 67584,
    cmdEditClear = 67840,
    cmdEditSelectAll = 68096,
    cmdEditFind = 68352,
    cmdLayerAdd = 68608,
    cmdLayerDelete = 68864,
    cmdLayerSelect = 69120,
    cmdViewStyle = 69376,
    cmdViewBgStyle = 69632,
    cmdViewBgColor = 69888,
    cmdViewBgPlotting = 70144,
    cmdViewBgMousing = 70400,
    cmdViewMouseGuide = 70656,
    cmdComposeDistributions = 70912,
    cmdComposeGenerate = 71168,
    cmdAnalyzeHistogram = 71424,
    cmdAnalyzeDeviation = 71680,
    cmdHelpCommands = 71936};

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
  void addLayer(PlotType pt);
  int numLayers();
  Layer * getLayer(int i);
  Layer * findLayer(int id);
  Layer * getFocusLayer();
  bool isFocusLayer(Layer * l);
  void setFocusLayer(Layer * l);
  void deleteFocusLayer();

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

  void selectAll();
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
  const StringArray getMenuBarNames (MenuBarComponent* mbar);
  const PopupMenu getMenuForIndex (MenuBarComponent* mbar, int idx, 
				   const String &name);
  void menuItemSelected (MenuBarComponent* mbar, int id, int idx);
  void closeButtonPressed () ;
};

#endif

