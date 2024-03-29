/*=======================================================================*
  Copyright (c) 2011 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#ifndef Plot_h
#define Plot_h

#include "Libraries.h"
#include "MidiPlaybackThread.h"

// forward pointers

class PlotView;         
class BackView;
class PlotViewport;
class PlotTabbedEditor;

/** An axis contains all the non-gui data for a graphical axis
    display. **/

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

  Axis (AxisType t) 
  {
    type=t;
    init(t);
  }

  Axis (AxisType t, double f, double e) 
  {
    type=t;
    init(t);
    from=f;
    to=e;
  }

  Axis (XmlElement* ax) 
    : name (String::empty),
    decimals (2),
    type (unspecified),
    from (0),
    to (1.0),
    by (.25),
    ticks (5)
    {
      StringArray range;
      String str=(ax) ? ax->getStringAttribute(T("axis")) : String::empty;
      //std::cout << "axis str=" << str << "\n";
      range.addTokens(str,false);
      if (range.size()>0)
      {
	int arg=1;
	if (range[0]==T("percent") || range[0]==T("percentage") || range[0]==T("pct"))
	  init(percentage);
	else if (range[0]==T("keynum"))
	  init(keynum);
	else if (range[0]==T("seconds"))
	  init(seconds);
	else if (range[0]==T("unitcircle") || range[0]==T("circle"))
	  init(circle);
	else if (range[0]==T("ordinal"))
	  init(ordinal);
	else if (range[0]==T("unit") || range[0]==T("normalized") || range[0]==T("normal"))
	  init(normalized);
	else if (range[0]==T("midi"))
	  init(midi);
	else if (('0' <= str[0]) && ( str[0] <= '9')) // is number
	  arg--;
	// parse out optional <from> <to> <by> <ticks> these can
	// appear with or without axis type specifier
	int num=range.size()-arg;
	if (num>=2)
        {
          double f, t, b, k;
          if (num==2)
	  {
	    f=range[arg].getFloatValue();
	    t=range[arg+1].getFloatValue();
	    if (type==unspecified)
	    {
	      b=t-f;
	      k=5;
	    }
            else 
            {
              b=by;
              k=ticks;
            }
	  }
          else if (num==3)
	  {
	    f=range[arg].getFloatValue();
	    t=range[arg+1].getFloatValue();
	    b=range[arg+2].getFloatValue();
	    if (type==unspecified)
	    {
	      k=5;
	    }
            else
            {
              k=ticks;
            }
	  }
          else if (num==4)
	  {
	    f=range[arg].getFloatValue();
	    t=range[arg+1].getFloatValue();
	    b=range[arg+2].getFloatValue();
	    k=range[arg+3].getIntValue();
	  }
          
          if ((f<t) && (b>0) && (k>-1))
	  {
	    from=f; to=t; by=b; ticks=(int)k;
	    if (type==unspecified)
	      type=generic;
	  }
        }
      }
    }

  void init (AxisType typ) 
  {
    // init axis data according to common "templates"
    name=String::empty;
    decimals=2;
    type=typ;
    switch (typ)
    {
    case percentage :
      from=0.0; to=100.0; by=25.0; ticks=5; decimals=0;
      break;
    case keynum :
      from=0.0; to=127; by=12.0; ticks=12; decimals=0;
      break;
    case seconds :
      from=0.0; to=60.0; by=1.0; ticks=4;
      break;
    case hertz :  // log freq
      from=8.175798; to=16744.035; by=2.0; ticks=6; 
      break;
    case circle :
      from=-1.0; to=1.0; by=.25; ticks=4;
      break;
    case ordinal :
      from=0; to=1; by=1; ticks=1; decimals=0;
      break;
    case normalized :
      from=0.0; to=1.0; by=0.25; ticks=5;
      break;
    case midi :
      from=0.0; to=127.0; by=16; ticks=2; decimals=0;
      break;
    default :
      break;
    }
    //    std::cout << "init: " << toString().toUTF8() << "\n";
  }

  ~Axis () {}

  //  void init (AxisType typ) ;
  int getType() {return type;}
  void setType(int n) {type=(AxisType)n;}
  bool isType(int typ){return type==typ;}
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
  String getLabel(double val)
  {
    if (getType()==keynum)
    {
      static const char* pcs[12]={"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
      int key=(int)val;
      int let=(key % 12);
      int oct=key/12;
      return String(pcs[let]) + ((oct==0) ? String("00") : String(oct-1));
    }
    else
      return String(val,getDecimals());
  }
  double rescale(const double val, const double newMin, const double newMax)
  {
    if (newMin == from && newMax == to) return val;
    if (val >= to) return newMax;
    if (val <= from) return newMin;
    return newMin + (((newMax - newMin) / (to - from)) * (val - from));
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
  
/** A layer contains all the non-gui data for a graphical plot
    display. **/

class Layer 
{
 public:
  enum 
  { // drawing style info (or'd together) FIX this should be moved.
    unspecified = 0,
    line = 1,
    point = 2,
    bar = 4,   // Bars are 2D and start at the origin
    box = 8,   // Boxes are triples x y z with z sharing an axis
    vertical = 16,
    horizontal = 32,
    //-------
    lineandpoint = line + point,
    vline = vertical + line,
    impulse = vline,
    vlineandpoint = vertical + line + point,
    histogram = vlineandpoint,
    vbar = vertical + bar,
    vbox = vertical + box,
    hbar = horizontal + bar,
    hbox = horizontal + box
  };

  // NPoint: a point with n plottable fields.
  class NPoint
  {
  public:
    double* vals;
    NPoint(int n) {vals=new double[n];}
    ~NPoint() {delete[] vals;}
    double getVal(int i) {return vals[i];}
    void setVal(int i, const double f) {vals[i]=f;} 
    void incVal(int i, const double f) {vals[i]+=f;} 
    void subVal(int i, const double f) {vals[i]-=f;} 
    void mulVal(int i, const double f) {vals[i]*=f;} 
    void divVal(int i, const double f) {vals[i]/=f;} 
  };

  static const int toLayerType(const String s, const int def=unspecified)
  {
    if (s==T("lineandpoint") || s==T("envelope")) return lineandpoint;
    if (s==T("line") || s==T("lines")) return line;
    if (s==T("point") || s==T("points")) return point;
    if (s==T("hbox") || s==T("box") || s==T("pianoroll")) return hbox;
    if (s==T("vbox")) return vbox;
    if (s==T("vlineandpoint") || s==("aerial")) return histogram;
    if (s==T("impulse") || s==T("impulses") ) return impulse;
    if (s==T("hbar")) return hbar;
    if (s==T("vbar") || s==T("bar")) return vbar;
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
  
  OwnedArray<NPoint> points;
  bool changed;



  /** _x _y and _z are the field indices for graphing x y and z point
      values. Indicies can be changed on the fly so a layer with more
      than 2 fields can display these other "dimensions" of data. **/

  int _x, _y, _z; 
  int arity;        /// arity of points in layer (number of fields in points)
  String name;      /// layer name
  int id;           /// unique id

  //------------------//
  //Drawing variables//
  //------------------//
  Colour color;           /// line and point color
  int style;              /// drawing style
  double lineWidth;       /// width of plot lines
  double pointWidth;      /// diameter of plot points
  double barWidth;        /// width of bars and boxes

  //------------------//
  //Playback variables//
  //------------------//
  int pbIndex;      /// point index during playback
  double pbDur;     /// default note duration
  double pbAmp;     /// default amplitude 
  int pbChan;       /// default channel

  Layer (int ari, String nam, Colour col, int sty=lineandpoint)
    : _x (0),
    _y (1),
    _z (2),
    arity (ari),
    name (nam),
    style (sty),
    lineWidth (1.0),
    pointWidth (8.0),
    barWidth (8.0),
    pbIndex(-1),
    pbDur (0.25),
    pbAmp (1.0),
    pbChan (0),
    changed (false)
    {
      static int layerid=1;
      color=col;
      id=layerid++;
      if (name.isEmpty())
        name=T("Layer ")+String(id);
    }
  
  ~Layer()
  {
    points.clear(true);
  };

  bool hasUnsavedChanges() {return changed;}
  void setUnsavedChanges(bool isChanged) {changed=isChanged;}
  int getLayerArity() {return arity;}
  void setLayerArity(int a) {arity=a;}
  int getLayerID(){return id;}
  void setLayerID(int i){id=i;}
  Colour getLayerColor(){return color;}
  void setLayerColor(Colour c){color=c;}
  String getLayerName(){return name;}
  void setLayerName(String n){name=n;}
  int getLayerStyle(){return style;}
  void setLayerStyle(int s){style=s;}
  bool isDrawStyle(int i) {return (getLayerStyle() & i) != 0;}
  int numPoints() {return points.size();}
  bool isPoints() {return (points.size()>0);}
  void sortPoints () {points.sort(*this);}

  int addPoint(double x, double y, NPoint* defaults) 
  {
    //    std::cout << "addPoint("<<x<<","<<y<<")\n";
    changed=true;
    NPoint* p =  new NPoint(arity);
    // point defaults
    if (defaults && arity>2)
      for (int i=0; i<arity; i++)
      {
	p->vals[i]=defaults->vals[i];
        p->vals[i]=.5;
        //        std::cout << "init field[" << i << "]=" << p->vals[i] << "\n";
      }
    // set X and Y fields to mouse values
    p->setVal(_x, x);
    p->setVal(_y, y);
    //    std::cout << "set x field[" << _x << "]=" << p->vals[_x] << "\n";
    //    std::cout << "set y field[" << _y << "]=" << p->vals[_y] << "\n";
    points.addSorted(*this, p);
    return points.indexOf(p);
  }

  void addXmlPoints(XmlElement* xmlpoints)
  {
    StringArray pts;
    int ind=0;
    int cur=points.size();
    forEachXmlChildElement(*xmlpoints, p)
    {
      NPoint* f=new NPoint(arity);
      pts.addTokens(p->getAllSubText(), false);
      if (pts.size()==1) // just provided a Y value
      {
        f->setVal(0, ind);
        f->setVal(1, pts[0].getFloatValue());
      }
      else
	for (int i=0; i<pts.size() && i<arity; i++)
	  f->setVal(i,pts[i].getFloatValue());
      // init unspecified fields with 0.0
      for (int i=pts.size(); i<arity; i++) 
	f->setVal(i, 0.0);
      points.addSorted(*this,f);
      cur++;
      pts.clear();
    }
    if (cur > points.size())
      changed=true;
  }

  NPoint* getPoint(int i) {return points[i];}
  NPoint* getFirstPoint() {return points.getFirst();}
  NPoint* getLastPoint() {return points.getLast();}

  int getPointIndex(NPoint* p) {return points.indexOf(p);}

  double getPointX(int i) {return points[i]->getVal(_x);}
  double getPointX(NPoint* p) {return p->getVal(_x);}
  double getPointY(int i) {return points[i]->getVal(_y);}
  double getPointY(NPoint* p) {return p->getVal(_y);}
  double getPointZ(int i) {return points[i]->getVal(_z);} 
  double getPointZ(NPoint* p) {return p->getVal(_z);}

  void setPointX(int i, double f) {changed=true; points[i]->setVal(_x, f);}
  void setPointX(NPoint* p, double f) {changed=true; p->setVal(_x, f);}
  void setPointY(int i, double f) {changed=true; points[i]->setVal(_y, f);}
  void setPointY(NPoint* p, double f) {changed=true; p->setVal(_y, f);}
  void setPointZ(int i, double f) {changed=true; points[i]->setVal(_z, f);}
  void setPointZ(NPoint* p, double f) {changed=true; p->setVal(_z, f);}

  void incPointX(int i, double f) {changed=true; points[i]->incVal(_x, f);}
  void incPointX(NPoint* p, double f) {changed=true; p->incVal(_x, f);}
  void incPointY(int i, double f) {changed=true; points[i]->incVal(_y, f);}
  void incPointY(NPoint* p, double f) {changed=true; p->incVal(_y, f);}
  void incPointZ(int i, double f) {changed=true; points[i]->incVal(_z, f);}
  void incPointZ(NPoint* p, double f) {changed=true; p->incVal(_z, f);}

  void mulPointX(int i, double f) {changed=true; points[i]->mulVal(_x, f);}
  void mulPointX(NPoint* p, double f) {changed=true; p->mulVal(_x, f);}
  void mulPointY(int i, double f) {changed=true; points[i]->mulVal(_y, f);}
  void mulPointY(NPoint* p, double f) {changed=true; p->mulVal(_y, f);}
  void mulPointZ(int i, double f) {changed=true; points[i]->mulVal(_z, f);}
  void mulPointZ(NPoint* p, double f) {changed=true; p->mulVal(_z, f);}

  void setPoint(int i, double x, double y) 
  {
    changed=true; 
    points[i]->setVal(_x, x);
    points[i]->setVal(_y, y);
  }
  void setPoint(NPoint* p, double x, double y)
  {
    changed=true; 
    p->setVal(_x, x);
    p->setVal(_y, y);
  }
  
  void incPoint(int i, double x, double y) 
  {
    changed=true; 
    points[i]->incVal(_x, x);
    points[i]->incVal(_y, y);
  }
  void incPoint(NPoint* p, double x, double y) 
  {
    changed=true; 
    p->incVal(_x, x);
    p->incVal(_y, y);
  }
  
  void mulPoint(int i, double x, double y)
  {
    changed=true; 
    points[i]->mulVal(_x, x);
    points[i]->mulVal(_y, y);
  }
  void mulPoint(NPoint* p, double x, double y)
  {
    changed=true; 
    p->mulVal(_x, x);
    p->mulVal(_y, y);
  }
  
  void removePoint(int i)
  {
    changed=true; 
    points.remove(i, false);
  }
  void removePoint(NPoint* p)
  {
    changed=true; 
    points.removeObject(p, false);
  }
  
  void deletePoint(int i) 
  {
    changed=true; 
    points.remove(i, true);
  }
  void deletePoint(NPoint* p) 
  {
    changed=true; 
    points.removeObject(p, true);
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
  static int compareElements(NPoint* p1, NPoint* p2) {
    if ( p1->vals[0] < p2->vals[0] )
      return -1;
    else 
      return 1;
  }
  String exportPoint(NPoint* p, int fmask=0xFF, int deci=2)
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

  String toString(int exportid, int decimals, bool asrecords, int parammask) 
  {
    String text=String::empty;
    String lpar=String::empty;
    String rpar=String::empty;
    String done=String::empty;
    String spce=T(" ");
    if (exportid==TextIDs::Lisp)
    {
      text=T("(");
      if (asrecords)
      {
        lpar=T("(");
        rpar=T(")");
      }
      done=T(")");
    }
    else if (exportid==TextIDs::Sal2)
    {
      text=T("{");
      if (asrecords)
      {
        lpar=T("{");
        rpar=T("}");
      }
      done=T("}");
    }
    else if (exportid==TextIDs::Xml)
    {
      text << T("<points title=")
	   << getLayerName().quoted()
	   << T(" style=")
	   << toLayerTypeString(getLayerStyle()).quoted()
	   << T(" color=")
	   << getLayerColor().toString().quoted();
      // add non-default access
      if (getXField()!=0 || getYField()!=1 ||
	  (getLayerArity()>2 && getYField()!=2))
	text << T(" access=\"")
	     << getXField() << T(" ") << getYField()
	     << T(" ") << getZField() << T("\"");
      text << T(">");
      lpar=T("<point>");
      rpar=T("</point>");
      done=T("</points>\n");
      spce=String::empty;
    }
    NPoint* point;
    int length=numPoints();
    for (int i=0; i<length; i++)
    {
      point=getPoint(i);
      if (i>0 && spce!=String::empty) text << spce;
      text << lpar
	   << exportPoint(point, parammask, decimals)
	   << rpar;
    }
    // add appropriate close parens...
    text << done ;
    //std::cout << text.toUTF8() << "\n";
    return text;
  }


  /** Returns the index of the first point that contains the given
      mouse coordinate, or -1 if no index was found. **/

  int findPointContaining(double mousex, double mousey, double halfx, double halfy);

  ///-------------///
  ///Midi Playback///
  ///-------------///

  void pbInitialize();

  /** Returns the index of the first X value at or later than the
      given beat time or -1 if no index is found for the beat.  **/

  int pbFindNextIndexForBeat (const double beat)
  {
    const int n = points.size();
    for (int i = 0; i < n; i++)
      if (getPointX(i) >= beat)
        return i;
    return -1;
  }

};

///
/// Axis View
///

class AxisView : public Component 
{
  
 public:
  Axis* axis;

  double spread; /// expansion factor for "zooming" space on axis
  double ppi;    // pixels per increment (distance between labels)
  double pad;     /// pixel margin on either side of axis line
  double offset; /// pixel position for start of axis line
  int orient;     /// orientation (horizontal, vertical)
  PlotViewport* viewport;  /// back pointer to viewport
  double sweep;
  bool fit;       /// if true then the axis is autosized to fit maximally in the view

  AxisView (PlotViewport* vp, int o)
    : spread (1.0),
    offset (0.0),
    viewport (0),
    axis (0),
    ppi (90.0),
    pad (8.0),
    fit (true),
    sweep (0.0)
    {
      viewport=vp;
      orient=o;
      setVisible(true);
    }
  ~AxisView () {}

  bool isVertical();
  bool isHorizontal();
  int getOrientation(){return orient;}
  double getSpread() {return spread;}
  void setSpread(double v) {spread=v; }

  bool isFitInView() {return fit;}
  void setFitInView(bool b) {fit=b;}




  /** getPad returns the pixel margin that exists on either side of
      axis line so that points at the start or end of end of the are
      not clipped. so for a horizonal axis the pixel width of the view
      is pad+axisextent+pad **/

  double getPad() {return pad;}
  void setPad(double val) {pad=val;}

  /** getOrigin returns the pixel position of the start of the axis line in the
      view. for horizontal axis the offset is the pad, for a vertical
      axis its the height of the view minus the pad (because the
      origin of the axis is at the bottom of the view). **/

  double getOrigin() {return offset;}
  void setOrigin(double v) {offset=v; }  
  
  bool hasAxis() {return axis != 0;}
  Axis* getAxis() {return axis;}
  void setAxis(Axis* a) {axis=a;}
  
  double axisMinimum() {return axis->getMinimum();}
  double axisMaximum() {return axis->getMaximum();}
  double axisIncrements() {return axis->getIncrements();}
  int numTicks(){return axis->getTicks();}
  
  /** Returns the size of pixels per increment at current spread **/

  double incrementSize () 
  {
    return( ppi * spread);
  }
  
  /** Returns the pixel distance between graduals **/

  double tickSize () 
  {
    return incrementSize() / axis->getTicks();
  }
  
  /** Returns the length (horizontal width for a horiztonal axis and
      vertical height for a vertical axis) of the axis line in pixels
      at the current spread. this is not the same as the size of the
      view and does not include any padding. **/
  
  double extent () 
  {
    // size of axis in pixels at current spread. may not be integer
    return incrementSize() * axis->getIncrements();
  }
  
  /** Sets the axis spread factor such that the axis maximally fits in
      the window without any scrollbars. Size will be the view width
      for a horizonal axis and the view height for a vertical
      axis. **/

  void setSpreadToFit(double size)
  {
    // get the normalized length of the axis line when spread equals 1
    double nonspreadsize = ppi * axis->getIncrements();
    // the available room for the axis line is the width of the view
    // minus the padding before and after axis line
    double availablesize = size - (getPad()*2);
    setSpread(availablesize/nonspreadsize);
  }

  /** Converts a pixel position to a value in axis coordinates. **/

  double toValue (double pix) 
  {
    double p = extent() * ( isVertical() ) ? offset - pix : pix - offset;
    return axis->getMinimum() + (axis->getRange() * ( p / extent()));
  }
  
  /** Converts an axis value to a pixel position in an axis view. **/

  double toPixel (double val) 
  {
    // convert value in axis coords to pixel position
    double p = extent() * ( (val - axis->getMinimum()) / axis->getRange());
    return ( isVertical() ) ? offset - p : offset + p;
  }

  void paint (Graphics& g) ;

};

///
/// Plotter
///

class PointClipboard
{
 public:
  OwnedArray <Layer::NPoint> points;
  Layer* layer;
  PointClipboard() {}
  ~PointClipboard() {}
  int size() {return points.size();}
  bool isEmpty() {return (size()==0);}
  Layer::NPoint* getPoint(int i) {return points[i];}
  Layer* getLayer() {return layer;}
  void set(Layer* layr, SelectedItemSet<Layer::NPoint*> * sel)
  {
    layer=layr;
    points.clear();
    for (int i=0;i<sel->getNumSelected(); i++)
      points.add(sel->getSelectedItem(i));
  }
  void clear() {layer=0; points.clear(false);}
  void add(Layer::NPoint* p) {points.add(p);}
};

class Plotter : public Component,
  public ScrollBarListener,
  public Transport::Listener,
  public MidiPlaybackThread::MidiMessageSource
{
 private:
  class Field
  {
  public:
    String name;
    Axis* axis;
    int shared;
    double initval; 
  Field(String n, Axis* a, int s=-1, double d=0.0)
    : name (n),
      axis (a),
      shared (s),
      initval (d)
      {
      }
    ~Field()
    {
      if (!isSharedAxis()) delete axis;
    }
    bool isSharedAxis() {return (shared>=0);}
  };
  
 public:
  enum Orientation {horizontal = 1, vertical };
  enum PlaybackParam {PlaybackMinKey=0, PlaybackMaxKey, PlaybackDuration, PlaybackAmplitude, PlaybackChannel, NumPlaybackParams=5};

  AxisView* haxview;
  AxisView* vaxview;
  PlotViewport* viewport;
  PlotView* plotview;
  BackView* backview;
  PlotTabbedEditor* editor;

  MidiPlaybackThread* pbThread;
  bool pbVerticalRescale;
  MidiOutput* pbMidiOut;
  double pbMinKey;
  double pbMaxKey;
  int pbTuning;
  CriticalSection pbLock;

  OwnedArray <Layer> layers;
  OwnedArray <Axis> axes;
  OwnedArray <Field> fields;

  Layer::NPoint* defaults; 
  UndoManager actions;
  Font font;
  double zoom;
  double ppp;  // point size (pixels per point)

  //-------------------//
  //Background controls//
  //-------------------//
  Colour bgColor;
  bool bgGrid;
  bool bgPlotting;
  bool bgMouseable;

  bool changed;
  //  int flags;
  //  bool playing;

  Plotter (int pt) ;
  Plotter (XmlElement* plot) ;
  Plotter (MidiFile& midifile);
  ~Plotter () ;

  bool hasUnsavedChanges ();
  void setUnsavedChanges(bool isUnsaved);
  void createPlottingComponents();
  void setPlottingFields(int xax, int yax);

  double getZoom() {return zoom;}
  void setZoom(double z) {zoom=z;}
  double getPointSize(){return ppp;}
  void setPointSize(double siz){ppp=siz;}

  void setHorizontalAxis(Axis* a);
  void setVerticalAxis(Axis* a);
  void insureAxisValues(int index);

  AxisView* getHorizontalAxisView();
  AxisView* getVerticalAxisView();

  /** returns the axis view for the specified orientation, either Plotter::horizontal or Plotter:vertical **/

  AxisView* getAxisView(int orient);
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
  void addLayer(Layer* l);
  Layer* newLayer(XmlElement* e, bool redraw=false);
  void removeLayer(Layer* l);

  /** Check if autosizing makes the axis increment too small and, if
      so, turn off autosizing. **/

  void checkFitInView();
  
  void resized () ;
  void resizeForSpread();
  void redrawPlotView();
  void redrawBackView();
  void redrawHorizontalAxisView();
  void redrawVerticalAxisView();

  /** triggers a repaint of all plotter components **/

  void redrawAll();
  void fitInView(double width=0.0, double height=0.0);
  int getViewportViewingHeight();
  int getViewportViewingWidth();
  void setBackViewCaching(bool caching);
  void sliderValueChanged (Slider *slider) ;
  void sliderDragStarted (Slider *slider) ;
  void sliderDragEnded (Slider *slider) ;
  void scrollBarMoved (ScrollBar * sb, double nrs) ;

  void selectAll();
  void deleteSelection(bool cut=false);
  bool isSelection();
  int numSelected();
  Layer::NPoint* getSelected(int index);
  void getSelectionRange(int orient, double& low, double& high);
  void shiftSelection(int orient, double delta);
  void rescaleSelection (int orient, double newlow, double newhigh);

  void deselectAll();
  void clearSelection();
  void moveSelection();
  void insurePointsVisible();

  //------//
  //Fields//
  //------//

  void setVerticalField(int fnum);
  void getVerticalField();
  int numFields() {return fields.size();}
  String getFieldName(int f) {return fields[f]->name;}
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
  void paint(Graphics& g); 

  //----------------------//
  //Midi Playback Methods//
  //----------------------//

  /** Creates playback thread and initializes playback variables.
      (Transport is responsible for starting playback thread and
      managing midi output port.) **/

  void pbInitialize();

  /** Opens the given device id and assigns it to the playback
      thread. If the id is less than zero the current device is closed
      and cleared in the thread. **/
  void pbSetMidiOut(int id);

  /** Called by Transport to stop thread playing. **/
  void pause();

  /** Called by the Transport to start thread playing. **/
  void play(double pos);

  /** Called by Transport to change the playback beat position. **/
  void positionChanged(double position, bool isPlaying);

  /** Called by Transport to change the playback tempo. **/
  void tempoChanged(double tempo, bool isPlaying);

  /** Traverses all layers adding midi messages to the playback
      thread. **/
  void addMidiPlaybackMessages(MidiPlaybackThread::MidiMessageQueue& queue, MidiPlaybackThread::PlaybackPosition& position);

};

#endif

