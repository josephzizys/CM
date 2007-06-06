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

 AxisView (Axis::AxisType typ)
    : _spread (1.0), _ppi (120.0), _offset (0.0), viewport (0)  {
    axis=new Axis(typ);
  }

  bool isVertical();
  bool isHorizontal();
  double getSpread() {return _spread;}
  void setSpread(double v) {_spread=v; }
  double getOrigin() {return _offset;}
  void setOrigin(double v) {_offset=v; }  

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

(enums 2 "PlotterCommand" "PlotterNew" "PlotterOpen" "PlotterSave" 
         "PlotterSaveAs" "PlotterImport" "PlotterExport"
	 "EditUndo" "EditRedo" "EditCut" "EditCopy" "EditPaste"
	 "EditSelectAll" "EditClear" "EditFind"
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
    cmdEditUndo = 67072,
    cmdEditRedo = 67328,
    cmdEditCut = 67584,
    cmdEditCopy = 67840,
    cmdEditPaste = 68096,
    cmdEditSelectAll = 68352,
    cmdEditClear = 68608,
    cmdEditFind = 68864,
    cmdLayerAdd = 69120,
    cmdLayerDelete = 69376,
    cmdLayerSelect = 69632,
    cmdViewStyle = 69888,
    cmdViewBgStyle = 70144,
    cmdViewBgColor = 70400,
    cmdViewBgPlotting = 70656,
    cmdViewBgMousing = 70912,
    cmdViewMouseGuide = 71168,
    cmdComposeDistributions = 71424,
    cmdComposeGenerate = 71680,
    cmdAnalyzeHistogram = 71936,
    cmdAnalyzeDeviation = 72192,
    cmdHelpCommands = 72448};

  AxisView * xaxis;
  AxisView * yaxis;
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

  AxisView * getAxisView(Orientation o);
  void setAxisView(AxisView * a, Orientation o) ;

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
  void addLayer(Layer* l);
  Layer* newLayer(PlotType pt);
  void removeLayer(Layer* l);

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
  const StringArray getMenuBarNames (MenuBarComponent* mbar);
  const PopupMenu getMenuForIndex (MenuBarComponent* mbar, int idx, 
				   const String &name);
  void menuItemSelected (MenuBarComponent* mbar, int id, int idx);
  void closeButtonPressed () ;
};

#endif

