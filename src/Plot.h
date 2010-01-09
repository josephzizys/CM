/*=======================================================================*
  Copyright (c) 2009 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#ifndef PLOT_H
#define PLOT_H

#include "juce.h"

// LayerPoint: a point with a (variable) number of plottable double fields.

typedef int PlotID;

class PlotIDs
{
 public:
  // WARNING: dont change until old PlotType enum is removed
  static const PlotID Empty = 0;
  static const PlotID XYPlot = 1;
  static const PlotID MidiPlot = 3;
};

class LayerPoint
{
 public:
  double * vals;
  LayerPoint(int n) {vals=new double[n];}
  ~LayerPoint() {delete[] vals;}
  double getVal(int i) {return vals[i];}
  void setVal(int i, double f) {vals[i]=f;} 
  void incVal(int i, double f) {vals[i]+=f;} 
  void subVal(int i, double f) {vals[i]-=f;} 
  void mulVal(int i, double f) {vals[i]*=f;} 
  void divVal(int i, double f) {vals[i]/=f;} 
};

class Axis
{
 public:
  enum AxisType
  {
    unspecified,
    normalized,
    percentage,
    keynum,
    amplitude,
    seconds,
    hertz,        // log plotting (not implemented yet)
    circle,
    ordinal,
    midi,
    generic
  };
  String name;
  AxisType type; 
  double from;    // minimum value
  double to;      // maximum value
  double by;      // inc along axis
  int ticks;      // number of ticks per inc to draw
  int decimals;   // num decimals to show in labels

  Axis (AxisType t, double f, double e, double b, int x, int d) 
    : type(t), from(f), to(e), by(b), ticks(x), decimals(d), name(String::empty)
    {}

  Axis (AxisType t) ;    
  Axis (AxisType t, double f, double e) ;
  Axis (XmlElement* ax) ;
  ~Axis () {}

  void init (AxisType typ) ;
  int getType() {return type;}
  void setType(int n) {type=(AxisType)n;}
  String getName() {return name;}
  void setName(String n) {name=n;}
  double getMinimum() {return from;}
  void setMinimum(double v) {from=v;}
  double getMaximum() {return to;}
  void setMaximum(double v) {to=v;}
  double getIncrement() {return by;}
  void setIncrement(double v) {by=v;}
  double getIncrements() {return (to-from)/by;}
  int getTicks() {return ticks;}
  void setTicks(int v) {ticks=v;}
  int getDecimals() {return decimals;}
  void setDecimals(int v) {decimals=v;}
  double getRange() {return to-from;}
  double rescale(double val, Axis* orig){
    return (getMinimum() + 
	    (getRange() * ((val - orig->getMinimum()) / 
			   orig->getRange())));
  }

  const String toAxisTypeString()
  {
    switch (type)
      {
      case normalized : return T("unit");
      case percentage : return T("percent");
      case keynum : return T("keynum");
      case amplitude : return T("amplitude");
      case seconds : return T("seconds");
      case hertz : return T("hertz");
      case circle : return T("circle");
      case ordinal : return T("ordinal");
      case generic : return T("generic");
      case unspecified :
      default: return T("");
      } 
  }   
    
  String toString()
  {
    String text=toAxisTypeString();
    text << T(" ") << String(from)
	 << T(" ") << String(to)
	 << T(" ") << String(by)
	 << T(" ") << String(ticks);
    return text;
  }
};
  
class Layer 
{
 public:
  enum 
  { // drawing style info (or'd together) FIX this should be moved.
    unspecified = 0,
    line = 1,
    point = 2,
    bar = 4,
    box = 8,
    vertical = 16,
    horizontal = 32,
    lineandpoint = 3,
    vline = 17,
    impulse = 17,
    vlineandpoint = 19,
    histogram = 19,
    vbar = 20,
    vbox = 24,
    hbar = 36,
    hbox = 40
  };
  
  static const int toLayerType(const String s, const int def=unspecified)
  {
    if (s==T("lineandpoint") || s==T("envelope")) return lineandpoint;
    if (s==T("line") || s==T("lines")) return line;
    if (s==T("point") || s==T("points")) return point;
    if (s==T("hbox")) return hbox;
    if (s==T("vbox")) return vbox;
    if (s==T("histogram") || s==T("vlineandpoint")) return histogram;
    if (s==T("impulse") || s==T("impulses") ) return impulse;
    if (s==T("hbar")) return hbar;
    if (s==T("vbar")) return vbar;
    if (s==T("unspecified")) return unspecified;
    return def;
  }
  static const String toLayerTypeString(int typ)
  {
    switch (typ)
      {
      case lineandpoint: return T("lineandpoint");
      case line: return T("line");
      case point: return T("point");
      case hbox: return T("hbox");
      case vbox: return T("vbox");
      case hbar: return T("hbar");
      case vbar: return T("vbar");
      case histogram: return T("vlineandpoint");
      case impulse: return T("impulse");
	//case vlineandpoint: return T("vlineandpoint");
      case unspecified:
      default: return T("unspecified");
      }
  }    
  static Colour defaultColor(int i)
  {
    Colour cols[8] = {Colours::red, Colours::green, 
		      Colours::blue, Colours::magenta,
		      Colours::cyan, Colours::sienna,
		      Colours::orange, Colours::coral};
    return cols[i % 8];
  }

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
  int arity;        // number of fields in points

  String name;      // layer name
  int id;           // unique id
  Colour color;     // line and point color
  int style;        // drawing style

  bool transp;      // allow back plots to be visible. unused
  
  Layer (int ari, String nam, Colour col, int sty=lineandpoint)
    : transp(true),
    _x (0),
    _y (1),
    _z (2),
    _defaults (NULL)
    {
      static int layerid=1;
      arity=ari;
      name=nam;
      color=col;
      id=layerid++;
      style=sty;
    }
  
  ~Layer()
    {
      _points.clear(true);
      if (_defaults!=NULL)
	delete _defaults;
    };

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
  int getLayerStyle(){return style;}
  void setLayerStyle(int s){style=s;}
  bool isDrawStyle(int i) {return (getLayerStyle() & i) != 0;}
  int numPoints() {return _points.size();}
  LayerPoint* getLayerFieldDefaults(){return _defaults;}
  void setLayerFieldDefaults(LayerPoint* p){_defaults=p;}
  bool isPoints() {return (_points.size()>0);}
  void sortPoints () {_points.sort(*this);}
  int addPoint(double x, double y) 
  {
    LayerPoint* p =  new LayerPoint(arity);
    initPoint(p);
    p->setVal(_x,x);
    p->setVal(_y,y);
    _points.addSorted(*this, p);
    return _points.indexOf(p);
  }
  void initPoint(LayerPoint* p)
  {
    // init new point with layer's default point values
    if (_defaults != (LayerPoint *)NULL)
      for (int i=0; i<arity; i++)
	p->vals[i]=_defaults->vals[i];
  }
  
  void addXmlPoints(XmlElement* p);

  LayerPoint* getPoint(int i) {return _points[i];}
  LayerPoint* getFirstPoint() {return _points.getFirst();}
  LayerPoint* getLastPoint() {return _points.getLast();}

  int getPointIndex(LayerPoint* p) {return _points.indexOf(p);}

  double getPointX(int i) {return _points[i]->getVal(_x);}
  double getPointX(LayerPoint* p) {return p->getVal(_x);}
  double getPointY(int i) {return _points[i]->getVal(_y);}
  double getPointY(LayerPoint* p) {return p->getVal(_y);}
  double getPointZ(int i) {return _points[i]->getVal(_z);} 
  double getPointZ(LayerPoint* p) {return p->getVal(_z);}

  void setPointX(int i, double f) {_points[i]->setVal(_x, f);}
  void setPointX(LayerPoint* p, double f) {p->setVal(_x, f);}
  void setPointY(int i, double f) {_points[i]->setVal(_y, f);}
  void setPointY(LayerPoint* p, double f) {p->setVal(_y, f);}
  void setPointZ(int i, double f) {_points[i]->setVal(_z, f);}
  void setPointZ(LayerPoint* p, double f) {p->setVal(_z, f);}

  void incPointX(int i, double f) {_points[i]->incVal(_x, f);}
  void incPointX(LayerPoint* p, double f) {p->incVal(_x, f);}
  void incPointY(int i, double f) {_points[i]->incVal(_y, f);}
  void incPointY(LayerPoint* p, double f) {p->incVal(_y, f);}
  void incPointZ(int i, double f) {_points[i]->incVal(_z, f);}
  void incPointZ(LayerPoint* p, double f) {p->incVal(_z, f);}

  void mulPointX(int i, double f) {_points[i]->mulVal(_x, f);}
  void mulPointX(LayerPoint* p, double f) {p->mulVal(_x, f);}
  void mulPointY(int i, double f) {_points[i]->mulVal(_y, f);}
  void mulPointY(LayerPoint* p, double f) {p->mulVal(_y, f);}
  void mulPointZ(int i, double f) {_points[i]->mulVal(_z, f);}
  void mulPointZ(LayerPoint* p, double f) {p->mulVal(_z, f);}

  void setPoint(int i, double x, double y) 
  {
    _points[i]->setVal(_x, x);
    _points[i]->setVal(_y, y);
  }
  void setPoint(LayerPoint* p, double x, double y)
  {
    p->setVal(_x, x);
    p->setVal(_y, y);
  }
  
  void incPoint(int i, double x, double y) 
  {
    _points[i]->incVal(_x, x);
    _points[i]->incVal(_y, y);
  }
  void incPoint(LayerPoint* p, double x, double y) 
  {
    p->incVal(_x, x);
    p->incVal(_y, y);
  }
  
  void mulPoint(int i, double x, double y)
  {
    _points[i]->mulVal(_x, x);
    _points[i]->mulVal(_y, y);
  }
  void mulPoint(LayerPoint* p, double x, double y)
  {
    p->mulVal(_x, x);
    p->mulVal(_y, y);
  }
  
  void removePoint(int i)
  {
    _points.remove(i, false);
  }
  void removePoint(LayerPoint* p)
  {
    _points.removeObject(p, false);
  }
  
  void deletePoint(int i) 
  {
    _points.remove(i, true);
  }
  void deletePoint(LayerPoint* p) 
  {
    _points.removeObject(p, true);
  }
  int getXField() {return _x;}
  int getYField() {return _y;}
  int getZField() {return _z;}
  void setXField(int f) {_x=f;}
  void setYField(int f) {_y=f;}
  void setZField(int f) {_z=f;}
  bool isVisibleField(int f)
  {
    return (f==_x||f==_y||(f==_z&&style==hbox));
  }
  void setFieldAccess(int x, int y, int z=-1)
  {
    _x=x;
    _y=y;
    if (z>=0) _z=z;
  }
  static int compareElements(LayerPoint* p1, LayerPoint* p2) {
    if ( p1->vals[0] < p2->vals[0] )
      return -1;
    else 
      return 1;
  }
  String exportPoint(LayerPoint* p, int fmask=0xFF, int deci=2)
  {
  // p: the point to export
  // fmask: bit mask, each 1 bit means that field is included
  String text=String::empty;
  for (int i=0; i<arity; i++) 
    if ( fmask & (1 << i) )
      { // check field mask, add delimiter if not at start.
	if (text != String::empty)
	  text <<  T(" ");
	if (deci==0)
	  text << String( (int)(.5 + p->getVal(i)) );
	else 
	  text << String( p->getVal(i), deci );
      }
  return text;
  }

  String toString(int exportid, int decimals, bool asrec, int parammask) ;
};

class PlotView;         // defined in Plotter.cpp
class BackView;
class PlotViewport;

///
/// Axis View
///

class AxisView : public Component 
{
  
 public:
  Axis * axis;
  double _spread; // expansion factor for "zooming" space on axis
  double _ppi;    // pixels per increment (distance between labels)
  double _offset; // pixel position of axis origin
  int orient;     // orientation (horizontal, vertical)
  PlotViewport * viewport;  // back pointer to viewport
  double _sweep;
  AxisView (PlotViewport* vp, int o)
    : _spread (1.0),
    _ppi (90.0),
    _offset (0.0),
    viewport (0),
    axis (0),
    _sweep (0.0)
    {
      viewport=vp;
      orient=o;
    }
  ~AxisView () {}

  bool isVertical();
  bool isHorizontal();
  int getOrientation(){return orient;}
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
  
  double incrementSize () 
  {
    // size of pixels per increment at current spread
    return( _ppi * _spread);
  }
  
  double tickSize () 
  {
    // pixel distance between graduals 
    return incrementSize() / axis->getTicks();
  }
  
  double extent () 
  {
    // size of axis in pixels at current spread. may not be integer
    return incrementSize() * axis->getIncrements();
  }
  
  double toValue (double pix) 
  {
    // convert pixel position to value in axis coords
    double p = extent() * ( isVertical() ) ? _offset - pix : pix - _offset;
    return axis->getMinimum() + (axis->getRange() * ( p / extent()));
  }
  
  double toPixel (double val) 
  {
    // convert value in axis coords to pixel position
    double p = extent() * ( (val - axis->getMinimum()) / axis->getRange());
    return ( isVertical() ) ? _offset - p : _offset + p;
  }
  
  void paint (Graphics& g) ;
  void mouseDown(const MouseEvent &e) ;
  void mouseDrag(const MouseEvent &e) ;
  void mouseUp(const MouseEvent &e) ;
  void mouseDoubleClick(const MouseEvent &e) ;

};

///
/// Plotter
///

class PointClipboard
{
 public:
  OwnedArray <LayerPoint> points;
  Layer* layer;
  PointClipboard() {}
  ~PointClipboard() {}
  int size() {return points.size();}
  bool isEmpty() {return (size()==0);}
  LayerPoint* getPoint(int i) {return points[i];}
  Layer* getLayer() {return layer;}
  void set(Layer* layr, SelectedItemSet<LayerPoint*> * sel)
  {
    layer=layr;
    points.clear();
    for (int i=0;i<sel->getNumSelected(); i++)
      points.add(sel->getSelectedItem(i));
  }
  void clear() {layer=0; points.clear(false);}
  void add(LayerPoint* p) {points.add(p);}
};

class Plotter  : public Component, public ScrollBarListener 
{
 private:
  class Field
  {
  public:
    String name;
    Axis* axis;
    int shared;
    bool isSharedAxis() {return (shared>=0);}
    Field(String n, Axis* a, int s=-1)
      {
	name=n;
	axis=a;
	shared=s;
      }
    ~Field()
      {
	if (!isSharedAxis()) delete axis;
      }
  };
  
 public:
  enum BGStyle {bgSolid = 1, bgGrid, bgTiled };
  enum Orientation {horizontal = 1, vertical };

  AxisView* haxview;
  AxisView* vaxview;
  PlotViewport* viewport;
  PlotView* plotview;
  BackView* backview;
  OwnedArray <Layer> layers;
  OwnedArray <Axis> axes;
  OwnedArray <Field> fields;

  UndoManager actions;
  Font font;
  double zoom;
  double ppp;  // point size (pixels per point)
  int flags;
  PlotID plottype;

  Plotter (int pt) ;
  Plotter (XmlElement* plot) ;
  Plotter (MidiFile& midifile);
  ~Plotter () ;
  void createPlottingComponents();
  void setPlottingFields(int xax, int yax);

  double getZoom() {return zoom;}
  void setZoom(double z) {zoom=z;}
  double getPointSize(){return ppp;}
  void setPointSize(double siz){ppp=siz;}
  PlotID getPlotType() {return plottype;}

  //  void setAxisView(Axis* a, Orientation o) ;
  void setHorizontalAxis(Axis* a);
  void setVerticalAxis(Axis* a);
  void autosizeAxes();

  AxisView* getHorizontalAxisView();
  AxisView* getVerticalAxisView();
  Axis* getVerticalAxis();
  Axis* getHorizontalAxis();
  BackView* getBackView();
  PlotView* getPlotView();
  PlotViewport* getPlotViewport();

  // layers
  int numLayers();
  Layer* getLayer(int i);
  Layer* findLayer(int id);
  Layer* getFocusLayer();
  bool isFocusLayer(Layer* l);
  void setFocusLayer(Layer* l);
  void setFocusVerticalField(int i);
  void addLayer(Layer* l);
  Layer* newLayer(XmlElement* e);
  void removeLayer(Layer* l);

  void resized () ;
  void resizeForSpread();
  void redrawPlotView();
  void redrawBackView();
  void redrawHorizontalAxisView();
  void redrawVerticalAxisView();

  BGStyle getBackViewStyle();
  void setBackViewStyle(BGStyle style);
  bool isBackViewPlotting();
  void setBackViewPlotting(bool val);
  void setBackViewCaching(bool val);

  void sliderValueChanged (Slider *slider) ;
  void sliderDragStarted (Slider *slider) ;
  void sliderDragEnded (Slider *slider) ;
  void scrollBarMoved (ScrollBar * sb, const double nrs) ;

  void selectAll();
  void deleteSelection(bool cut=false);
  bool isSelection();
  int numSelected();
  void deselectAll();
  void clearSelection();
  void moveSelection();
  void insurePointsVisible();

  // Fields
  int numFields() {return fields.size();}
  String getFieldName(int f) {return fields[f]->name;}
  void getFieldNames(StringArray& ary)
  {
    for(int i=0;i<numFields();i++)
      ary.add(getFieldName(i));
  }
  Axis* getFieldAxis(int f) {return fields[f]->axis;}
  bool isSharedField(int f) {return fields[f]->isSharedAxis();}
  String getSharedFieldName(int f) 
  {
    if (fields[f]->isSharedAxis())
      return fields[fields[f]->shared]->name;
    else return String::empty;
  }

  String getPlotTitle()
  {
    Component* window=getTopLevelComponent(); // plotter window
    return (window) ? window->getName() : String::empty;
  } 

  //  void handleMessage (const Message &message);
};

///
/// Plotter Window
///

class PlotterWindow : public DocumentWindow,

  public MenuBarModel
{

 public:

  class PlotterWindowListener : public MessageListener
  {
  public:
    void handleMessage (const Message &message);//{std::cout << "message!\n";}
    PlotterWindow* window;
  PlotterWindowListener(PlotterWindow* w) : window(w) {}
  };
  PlotterWindowListener listener;

  Plotter* plotter;
  File plotfile;
  MenuBarComponent* menubar;
  PlotterWindow (XmlElement* plot);
  PlotterWindow (String title, MidiFile& midifile);
  void init();
  ~PlotterWindow ();
  const StringArray getMenuBarNames ();
  const PopupMenu getMenuForIndex (int idx, const String &name);
  void menuItemSelected (int id, int idx);
  void closeButtonPressed () ;
  void openExportDialog();
  void openLayerDialog();
  void openAxisDialog(int orient);
  void openPlayPlotDialog();
  void openEditPointsDialog();
  void openRescalePointsDialog(int cmd);
  //  static void openXml(String str);
  static void openWindowFromXml(void* str);
  static void browseForFileToOpen(int type);
  static void openXmlFile(File file);
  static void openMidiFile(File file);
  void addXmlPoints(String xml);
  bool save(bool saveas=false);
  String toXmlString();
  String getPlotTitle() {return getName();}
  void setPlotTitle(String titl){setName(titl);}
  File getPlotFile() {return plotfile;}
  void setPlotFile(File fil) {plotfile=fil;}
  static PlotterWindow* getPlotWindow(String title) ;
};

#endif

