/*=======================================================================*
  Copyright (c) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify
  it under the terms of the Lisp Lesser Gnu Public License. The text
  of this agreement is available at http://www.cliki.net/LLGPL
 *=======================================================================*/

#include "Enumerations.h"
#include "Menus.h"
#include "Console.h"
#include "TextEditor.h"
#include "Plot.h"
#include "Midi.h"
#include "Scheme.h"
#include <limits>
#include "CmSupport.h"
#include "Alerts.h"
//#include <cmath>
#include <iostream>

/*=======================================================================*
                                    Axis
 *=======================================================================*/

Axis::Axis (AxisType t) 
{
  type=t;
  init(t);
}

Axis::Axis (AxisType t, double f, double e) 
{
  type=t;
  init(t);
  from=f;
  to=e;
}

Axis::Axis (XmlElement* ax) 
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
  range.addTokens(str,false);
  if (range.size()>0)
    {
      int arg=1;
      if (range[0]==T("percent") || range[0]==T("percentage") || range[0]==T("pct"))
        init(percentage);
      else if (range[0]==T("keynum") || range[0]==T("notes"))
        init(keynum);
      else if (range[0]==T("seconds"))
        init(seconds);
      else if (range[0]==T("hertz")) 
        init(hertz);
      else if (range[0]==T("unitcircle") || range[0]==T("circle"))
        init(circle);
      else if (range[0]==T("ordinal"))
        init(ordinal);
      else if (range[0]==T("unit") || range[0]==T("normalized") || 
               range[0]==T("normal"))
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
          float f, t, b, k;
          if (num==2)
            {
              f=range[arg].getFloatValue();
              t=range[arg+1].getFloatValue();
              if (type==unspecified)
                {
                  b=t-f;
                  k=5;
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
              from=f; to=t; by=b; ticks=k;
              if (type==unspecified)
                type=generic;
            }
        }
    }
}

void Axis::init (AxisType typ) 
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
}

/*=======================================================================*
                          Plot Viewport (scrolling)
 *=======================================================================*/

class PlotViewport : public Viewport 
{
 public:
  Plotter * plotter;
  PlotViewport (Plotter * p) {
    // register plotter to receive callbacks from the viewport's
    // scollers so plotter can scroll axis views whenever the plot is
    // scrolled
    plotter=p;
    getHorizontalScrollBar()->setName(T("xscroll"));
    getHorizontalScrollBar()->addListener(p);
    getVerticalScrollBar()->setName(T("yscroll"));
    getVerticalScrollBar()->addListener(p);
  }
  ~PlotViewport () {}
};

/*=======================================================================*
                             AxisView methods
 *=======================================================================*/

bool AxisView::isVertical()
{
  return (orient==Plotter::vertical);
}

bool AxisView::isHorizontal() 
{
  return (orient==Plotter::horizontal);
}

void AxisView::paint (Graphics& g) 
{
  #define graywidth 13
  #define majortick 12
  #define minortick 6
  g.fillAll (Colours::white); 
  // lightly shade lower half to match pretty scrollbars
  //  g.setColour(Colour(0xf7, 0xf7, 0xf7));
  if (!hasAxis() ) return;
  int w=getWidth();
  int h=getHeight();

  g.setColour(Colours::lightgrey);   
  if ( isVertical() )
    g.fillRect(w-graywidth, 0, graywidth, h);
  else  
    g.fillRect(0, graywidth, w, graywidth);

  g.setColour(Colours::black);  
  // not sure if juce would call this method before SetAxis happens
  // but no reason not to be safe!
  
  if ( viewport==(PlotViewport *)NULL ) 
    return;
  
  // drawing axis ticks: first determine the visible portion of the
  // plot display since this will determine what portion of the axis
  // gets drawn.  then we find the FIRST label position at or above
  // that pixl position and draw all the labels and ticks until the
  // end of the axis view. then we go back to the the first label and
  // REVERSE direction to fill in any ticks that are visible before
  // the first label.

  double isiz=incrementSize();
  double tsiz=tickSize();
  Colour col1=Colours::darkgrey;
  Colour col2=Colours::lightgrey;
  Colour tcol=Colours::black;  // text color
  col2=col1;
  Font font=viewport->plotter->font;
  String labl;
  double lhei=font.getHeight(), lwid, just;
  double pval=getOrigin(); 
  double aval=axis->getMinimum();   
  double save;
  double by=axis->getIncrement();
  
  if (viewport->plotter->numLayers()>1 &&
      viewport->plotter->isBackViewPlotting())
    tcol=viewport->plotter->getFocusLayer()->getLayerColor();

  g.setFont(font);
  
  if ( isHorizontal() ) 
    {
      int left=viewport->getViewPositionX();  // plot's visible left
      int width=viewport->getViewWidth();
      int height=getHeight();   // height of axis view
      
      //g.drawHorizontalLine(height-1,0, getWidth());
      g.drawLine(0, height-1, getWidth(),height-1,2);
      
      // determine first visible label that is >= plot's visible left
      while ( pval<left ) 
	{
	  pval+=isiz;
	  aval+=by;
	}
      // subtract out visible left position to make it position of the
      // first major tick+label in the axis view
      save=pval-left;  // save=first label tick
      pval=save;
      // draw labels and ticks till end of view. label drawing is
      // justified so that the text stays witin bounds. at start display
      // labels are Right, in the middle they are centered and at the
      // end they are left justified.
      while ( pval<=width )
	{
	  g.setColour(col1);
	  g.drawVerticalLine((int)pval, height-majortick, height);
	  labl=String(aval,axis->getDecimals());
	  lwid=font.getStringWidthFloat(labl);
	  just=(int)(-lwid*(pval/width));  // twiddle label justification
	  g.setColour(tcol);
	  g.drawText(labl,(int)(pval+just),0,(int)lwid,(int)lhei, 
		     Justification::topLeft, false);
	  // draw minor ticks above each major tick
	  g.setColour(col2);
	  for (int i=1;i<numTicks();i++)
	    g.drawVerticalLine((int)(pval+(tsiz*i)), height-minortick,
			       height);
	  pval+=isiz;
	  aval+=by;
	}
      // now draw any ticks left of first increment
      pval=save-tsiz;
      g.setColour(col2);
      while (pval > 0)
	{
	  g.drawVerticalLine((int)pval, height-minortick, height);
	  pval-=tsiz;
	}
    }
  else
    {
      int height=viewport->getViewHeight();
      int top=viewport->getViewPositionY();
      int bottom=height+top;
      int width=getWidth();   // width of axis view
//      float tx,ty;
      
      //g.drawVerticalLine(width-1, 0, getHeight());
      g.drawLine(width-1, 0, width-1, getHeight(), 2);

      while (pval>bottom)
	{
	  pval-=isiz;
	  aval+=by;
	}

      save=pval-top;
      pval=save;
      while (pval>=0) 
	{
	  g.setColour(col1);
	  g.drawHorizontalLine((int)pval, width-majortick, width);
	  labl=String(aval, axis->getDecimals());
	  lwid=font.getStringWidthFloat(labl);
	  
	  // METHOD1: justify vertically, but now the view has to be wider.
	  just=(int)(lhei*(pval/height));  // twiddle label justification
	  g.setColour(tcol);
	  g.drawText(labl,
		     width-graywidth-4-lwid,
		     (int)(pval-just),
		     (int)lwid,
		     (int)lhei,
		     Justification::topLeft,
		     false);	  
	  g.setColour(col2);
	  for (int i=1;i<numTicks();i++)
	    g.drawHorizontalLine((int)(pval-(tsiz*i)), width-minortick,
				 width);
	  pval-=isiz;
	  aval+=by;
	}
      // now draw any ticks below first increment
      pval=save+tsiz;
      g.setColour(col2);
      while (pval < height) 
	{
	  g.drawHorizontalLine((int)pval, width-minortick, width);
	  pval+=tsiz;
	}
    }
  g.setColour(Colours::black);
}

void AxisView::mouseDown(const MouseEvent &e) 
{
  viewport->plotter->setBackViewCaching(false);
  _sweep=_spread;
}

void AxisView::mouseDrag(const MouseEvent &e)
{
  double a,b;
  if (isHorizontal())
    {
      a=e.getDistanceFromDragStartX();
      b=getWidth();
      setSpread(jlimit(.25, 4.0, _sweep+((a/b)*1)));
      viewport->plotter->resizeForSpread();
      // now have to update the size of the Axis' view -- this is NOT
      // the size of the axis!
      setSize(viewport->getViewWidth(), getHeight());
      // if spread has gotten larger then the size of the axis view
      // doenst actually change, in which case we have to force a
      // repaint to see the axis content drawn at the new spread.
      if (b==getWidth())
	repaint();
    }
  else
    {
      a=e.getDistanceFromDragStartY();
      b=getHeight();
      setSpread(jlimit(.25, 4.0, _sweep+((a/b)*1)));
      viewport->plotter->resizeForSpread();
      setSize(getWidth(), viewport->getViewHeight()) ;
      if (b==getHeight())
	repaint();
    }
  //std::cout << "mousedrag=" << c << "\n";
}

void AxisView::mouseUp(const MouseEvent &e)
{
  //std::cout << "mouseup\n";
  viewport->plotter->setBackViewCaching(true);
}

void AxisView::mouseDoubleClick(const MouseEvent &e)
{
  PlotterWindow* w=(PlotterWindow*)getTopLevelComponent();
  w->openAxisDialog(getOrientation());
}

/*=======================================================================*
                    Region and selection, sweeping and editing
 *=======================================================================*/

class Region : public Component {
public:
  enum {selection = 1, horizontal, vertical};
  int type;
  Colour fillcolor, linecolor;
  int linewidth;
  AxisView * xa;
  AxisView * ya;
  Region ()
    : fillcolor(Colour(0x66dddddd )),
      linecolor(Colour(0x99111111)),
      linewidth(1),
      type(1)
     {
     }
  ~Region() { }
  bool isActive() { return isVisible(); }
  void setType(int t) {type=t;}

  void beginSweep (const MouseEvent& e, AxisView * x, AxisView * y) {
    xa=x;
    ya=y;
    setSize(0,0);
  }
  void sweep (const MouseEvent& e) {
    const int x1 = e.getMouseDownX();
    const int y1 = e.getMouseDownY();
    setBounds(jmin(x1, e.x), jmin(y1, e.y), abs(e.x - x1), abs (e.y - y1));
    setVisible(true);
  }
  void endSweep (const MouseEvent& e) {
    //printf("region: x1=%f x2=%f, y1=%f, y2=%f\n", minX(),  maxX(), minY(),  maxY());
    setSize(0,0);
    setVisible(false);
  }
  // NB: these cant be called after region has been closed!
  double minX() {return xa->toValue(getX());}
  double maxX() {return xa->toValue(getRight());}
  double minY() {return ya->toValue(getBottom());}
  double maxY() {return ya->toValue(getY());}

  void paint (Graphics& g) {
    g.fillAll(fillcolor);
    g.setColour (linecolor);
    g.drawRect (0, 0, getWidth(), getHeight(), linewidth);
    //printf("region: x=%d y=%d, w=%d, h=%d\n", getX(), getY(), getWidth(), getHeight());
   }
};

/*=======================================================================*
             BackView: view to hold grid and background plots.
 *=======================================================================*/

void drawLayer(Graphics& g, Layer* layer, AxisView* haxview, 
	       AxisView* vaxview, double ppp, double spread, bool isFoc, 
	       SelectedItemSet<LayerPoint*> * sel);

void drawGrid(Graphics& g, AxisView * haxview, AxisView * vaxview, 
	      Colour c1, Colour c2) ;

class BackView : public Component 
{
public:
  Plotter * plotter;
  Colour bgcolors[6];
  Plotter::BGStyle bgstyle;
  bool bgplots;
  BackView (Plotter * p) :
    bgstyle(Plotter::bgGrid),
    bgplots (true) 
  {
    plotter=p;
    bgcolors[0]=Colours::white;
    bgcolors[1]=Colours::lightyellow;
    bgcolors[2]=Colours::darkgrey;
    bgcolors[3]=Colours::lightgrey;
    bgcolors[4]=Colours::lavender;
    bgcolors[5]=Colour(0xf7, 0xf7, 0xf7);
    setBufferedToImage(true);
    //setInterceptsMouseClicks(false,false);
  }

  Plotter::BGStyle getBackViewStyle() {return bgstyle;}
  void setBackViewStyle( Plotter::BGStyle b) {bgstyle=b;}
  bool isBackViewPlotting() {return bgplots;}
  void setBackViewPlotting( bool b) {bgplots=b;}
  void setBackViewCaching(bool b) {setBufferedToImage(b);}
  void paint (Graphics& g) {
    g.fillAll(bgcolors[0]);
    AxisView * haxview = plotter->getHorizontalAxisView();
    AxisView * vaxview = plotter->getVerticalAxisView();
    Layer * layer;
    
    if (!vaxview->hasAxis() || !haxview->hasAxis()) return;

    // draw background grid
    if (bgstyle==Plotter::bgGrid)
      drawGrid(g, haxview, vaxview, bgcolors[2], bgcolors[3]);
    else if (bgstyle==Plotter::bgTiled)
      g.fillCheckerBoard((int)haxview->getOrigin(),
			 (int)(vaxview->getOrigin()-vaxview->extent()),
			 (int)haxview->extent(), 
			 (int)vaxview->extent(),
			 (int)haxview->tickSize(), 
			 (int)vaxview->tickSize(),
			 bgcolors[4],bgcolors[5]);
    else g.fillAll(bgcolors[1]);

    // draw non-focus plots
    if ( isBackViewPlotting() ) {
      double psize=plotter->getPointSize();
    for (int i=0; i < plotter->numLayers(); i++) {
      layer = plotter->getLayer(i);
      if (! plotter->isFocusLayer(layer) ) 
	drawLayer(g, layer, haxview, vaxview, psize, 1.0, false, 
		  (SelectedItemSet<LayerPoint*> *)NULL);
      }
    }
  }

  ~BackView () {};
};

/*=======================================================================*
              PlotView: the focus layer's drawing canvas
 *=======================================================================*/

class PlotView : public Component 
{
public:
  Plotter * plotter;
  BackView * backview;
  double pad; // pix per inc, pix per point, margin pad
  Point mousedown, mousemove;
  SelectedItemSet<LayerPoint*> selection;
  Region region;
  Layer * focuslayer; // cached focus layer for fast acesss
  
  PlotView (Plotter * p) : pad (8.0) 
  {
    plotter=p;
  }
  
  ~PlotView () { }
  
  void paint (Graphics& g);
  void repaintFocusPlot() {repaint();}
  void resized() {plotter->backview->setSize(getWidth(),getHeight());}
  void mouseDown(const MouseEvent &e) ;
  void mouseDrag(const MouseEvent &e) ;
  void mouseUp(const MouseEvent &e) ;
  void mouseDoubleClick(const MouseEvent &e) ;

  bool keyPressed (const KeyPress& key) ;

  void resizeForDrawing();
  /*
  int visiblePixelLeft () { return plotter->viewport->getViewPositionX();}
  int visiblePixelTop () { return plotter->viewport->getViewPositionY();}
  int visiblePixelRight () { 
    return (plotter->viewport->getViewPositionX() +
	    plotter->viewport->getViewWidth());
  }
  int visiblePixelBottom () { 
    return (plotter->viewport->getViewPositionY() +
	    plotter->viewport->getViewHeight());
  }
  double visibleValueLeft(){return haxview->toValue(visiblePixelLeft());}
  double visibleValueRight(){return haxview->toValue(visiblePixelRight());}
  double visibleValueTop(){return vaxview->toValue(visiblePixelTop()); }
  double visibleValueBottom(){return vaxview->toValue(visiblePixelBottom());}
  */

  bool isSelection() {return (selection.getNumSelected() > 0);}
  int numSelected() {return selection.getNumSelected();}

  bool isSelected(LayerPoint* p) {return selection.isSelected(p);}
  bool isSelected(int h) {return isSelected(focuslayer->getPoint(h));}

  void selectAll (bool redraw=true)
  {
    int i;
    selection.deselectAll();
    for (i=0; i<focuslayer->numPoints(); i++)
      selection.addToSelection(focuslayer->getPoint(i));
    if (redraw) repaintFocusPlot();
  }

  void deselectAll(bool redraw=true)
  {
    if (isSelection()) 
      {
	selection.deselectAll();
	if (redraw) repaintFocusPlot();
      }
  }

  void removeSelection(LayerPoint* p) {selection.deselect(p);}
  void removeSelection(int h) {removeSelection(focuslayer->getPoint(h));}

  void setSelection(LayerPoint* p) ;
  void setSelection(int h) {setSelection(focuslayer->getPoint(h));}

  void addSelection(LayerPoint* p) {
    selection.addToSelection(p);
  }
  void addSelection(int h) {addSelection(focuslayer->getPoint(h));}

  void deleteSelection (bool cut=false) 
  {
    for (int i=0; i<numSelected(); i++)
      focuslayer->deletePoint( getSelected(i));
    repaint();
  }

  LayerPoint* getSelected(int i) {return selection.getSelectedItem(i);}
  int getSelectedIndex(int i) {
    return focuslayer->getPointIndex(selection.getSelectedItem(i));
  }

  void dragSelection(float x, float y);
  void shiftSelection(int orient, float delta);
  void rescaleSelection (int orient, float newlow, float newhigh);

  void getSelectionRange(int orient, float& low, float& high);
  float getSelectionMin(Plotter::Orientation orient);

  bool isInside(float x, float y, float left, float top,
		float right, float bottom);

  // this shuold be a layer method...
  void selectPointsInside(float left, float top, float right, float bottom) ;

  void printSelection() {
    printf("#<Selection:");
    for (int i=0;i<numSelected(); i++)
      printf(" %d", getSelectedIndex(i));
    printf(">\n");
  }
};

void PlotView::setSelection(LayerPoint* p) {
  selection.selectOnly(p);
}

float PlotView::getSelectionMin(Plotter::Orientation orient)
{
  std::numeric_limits<float> info;
  float (Layer::*getter) (LayerPoint* p) ;
  float lim=info.max();

  if (orient == Plotter::horizontal)
    getter = &Layer::getPointX;
  else 
    getter = &Layer::getPointY;

  for (int i = 0; i< numSelected(); i++) {
    lim=jmin( lim, (focuslayer->*getter) (  getSelected(i) ) );
  }
  return lim;
}

void PlotView::getSelectionRange(int orient, float& low, float& high)
{
  std::numeric_limits<float> info;
  low=info.max();
  high=info.min();
  float x;
  if (orient==Plotter::horizontal)
    for (int i=0; i<numSelected(); i++) 
      {
	x=focuslayer->getPointX(getSelected(i)) ;
	low=jmin(low, x);
	high=jmax(high, x);
      }
  else  
    for (int i=0; i<numSelected(); i++) 
      {
	x=focuslayer->getPointY(getSelected(i)) ;
	low=jmin(low, x);
	high=jmax(high, x);
      }
}
   
void PlotView::dragSelection(float dx, float dy) 
{
  int n=numSelected();
  for (int i=0; i<n; i++)
    focuslayer->incPoint( getSelected(i), dx, dy);
}

void PlotView::shiftSelection(int orient, float delta) 
{
  if (delta==0.0) return;
  int n=numSelected();
  LayerPoint* p;
  if (orient==Plotter::vertical)
    for (int i=0; i<n; i++)
      {
	p=getSelected(i);
	focuslayer->incPointY(p, delta);
      }
  else
    {
      for (int i=0; i<n; i++)
      {
	p=getSelected(i);
	focuslayer->incPointX(p, delta);
      }
      focuslayer->sortPoints();
    }
  repaintFocusPlot();
}

void PlotView::rescaleSelection (int orient, float newmin, float newmax)
{
  LayerPoint* p;
  float oldmin, oldmax;
  double v;
  getSelectionRange(orient, oldmin, oldmax);
  if ((oldmin==newmin) && (oldmax==newmax))
    return;
  if (orient==Plotter::vertical)
    for (int i=0; i<numSelected(); i++)
      {
	p=getSelected(i);
	v=cm_rescale(focuslayer->getPointY(p), oldmin, oldmax,
		     newmin, newmax, 1);
	focuslayer->setPointY(p,(float)v);
      }
    else 
    {
      for (int i=0; i<numSelected(); i++)
	{
	  p=getSelected(i);
	  v=cm_rescale(focuslayer->getPointX(p), oldmin, oldmax,
		       newmin, newmax, 1);
	  focuslayer->setPointX(p,(float)v);
	}
      focuslayer->sortPoints();
    }      
  repaintFocusPlot();
}

// drawing and mouse

void PlotView::resizeForDrawing() {
  // called when spread value changes to reset total size of plotting view
  double xsiz, ysiz, xtot, ytot;
  AxisView * haxview=plotter->getHorizontalAxisView();
  AxisView * vaxview=plotter->getVerticalAxisView();
  // xpad and ypad are margins around the plotting area so points at
  // the edge aren't clipped
  xsiz=haxview->extent();
  ysiz=vaxview->extent();
  xtot=pad+xsiz+pad;
  ytot=pad+ysiz+pad;
  haxview->setOrigin(pad);
  vaxview->setOrigin(ytot-pad);
  setSize( (int)xtot, (int)ytot );
}

void drawLayer(Graphics& g, Layer* layer, AxisView* haxview, AxisView* vaxview, 
	       double ppp, double zoom, bool isFoc, 
	       SelectedItemSet<LayerPoint*> * sel) 
{
  double half=ppp/2;
  double ax, ay, px, py, lx, ly, ox, oy;
  Colour color, selcolor= Colours::grey;
  int ndraw;
  bool fillp=true;
  //printf("visible left=%f, right=%f\n", visibleValueLeft(), visibleValueRight());
  color=layer->color;
  ndraw=layer->numPoints();

  // need pixel origins for vert/horiz lines/bars
  if (vaxview->axisMinimum() < 0.0 && vaxview->axisMaximum() >= 0.0)
    oy=vaxview->toPixel(0.0);
  else oy=vaxview->toPixel(vaxview->axisMinimum());

  if (haxview->axisMinimum() < 0.0 && haxview->axisMaximum() >= 0.0)
    ox=haxview->toPixel(0.0);
  else ox=haxview->toPixel(haxview->axisMinimum());

  g.setColour(color);
  for (int i=0; i<ndraw; i++) {
    LayerPoint* p = layer->getPoint(i);
    ax=layer->getPointX(p);
    ay=layer->getPointY(p);  
    px=haxview->toPixel(ax);   // pixel coords
    py=vaxview->toPixel(ay);

    if ( layer->isDrawStyle(Layer::line)  ) {
      if (layer->isDrawStyle(Layer::vertical))
	g.drawLine( px, oy, px, py); // vertical line from orign
      else if (layer->isDrawStyle(Layer::horizontal) )
	g.drawLine( ox, py, px, py); // horizontal line from origin
      else if (i>0)  // normal line between points
	g.drawLine( lx, ly, px, py);
      }

    if (layer->isDrawStyle(Layer::point)) {
      // if we are moving selection then draw selected point gray
      if ( isFoc && sel->isSelected(p) ) {
	g.setColour(selcolor);
	g.fillEllipse(px-half, py-half, ppp,ppp);
	g.setColour(color);
      }
      else
	g.fillEllipse(px-half, py-half, ppp,ppp);
    } 
    else if (layer->isDrawStyle(Layer::hbox)) {
      // to get pixel width of Z, get absolute axis position of Z,
      // convert to pixel and then subtract out px
      double az=ax + layer->getPointZ(p);
      double pz = (int)haxview->toPixel(az);
      // draw selected boxes gray if moving
      if ( isFoc && sel->isSelected(p) ) {
	g.setColour(selcolor);
	g.fillRect((int)px, (int)(py-half), (int)(pz-px), (int)ppp);
	g.setColour(color);
      }
      else
	g.fillRect((int)px, (int)(py-half), (int)(pz-px), (int)ppp);
    }
    lx=px;
    ly=py;
  }
}

void PlotView::paint (Graphics& g) 
{
  // erase with white
  drawLayer(g, focuslayer,
	    plotter->getHorizontalAxisView(),
	    plotter->getVerticalAxisView(),
	    plotter->getPointSize(),
	    1.0,
	    true,
	    &selection);
}

void drawGrid(Graphics& g, AxisView* haxview, AxisView* vaxview, 
	      Colour c1, Colour c2) 
{
  double left=haxview->getOrigin();
  double right=left+haxview->extent();
  double bottom=vaxview->getOrigin();
  double top=bottom-vaxview->extent();
  double v,p,t,d;
  p=haxview->getOrigin();
  d=haxview->incrementSize();
  t=haxview->tickSize();
  while (p <= right) 
    {
      g.setColour(c1);
      g.drawVerticalLine((int)p, top, bottom);
      g.setColour(c2);
      for (int i=1;i<haxview->numTicks();i++) 
	g.drawVerticalLine((int)(p+(t*i)), top, bottom);
      p += d;
    }
  p=vaxview->getOrigin();
  d=vaxview->incrementSize();
  t=vaxview->tickSize();
  while (p >= top)
    {
      g.setColour(c1);
      g.drawHorizontalLine((int)p, left, right);
      g.setColour(c2);
      for (int i=1;i<vaxview->numTicks();i++) 
	g.drawHorizontalLine((int)(p-(t*i)), left, right);
      p -= d;
    }
  g.setColour(c1);
}

bool PlotView::isInside(float x, float y, float l, float t, float r, float b) 
{
  if ((l <= x) && (x <= r) && (b <= y) && (y <= t))
    return true;
  else 
    return false;
}

void PlotView::selectPointsInside(float l, float t, float r, float b)
{
  //printf("looking in region: left=%f top=%f, right=%f, bottom=%f\n",x1, y2, x2, y1);
  //deselectAll();
  for (int i=0; i<focuslayer->numPoints(); i++) 
    {
      double x=focuslayer->getPointX(i);
      double y=focuslayer->getPointY(i);
      if (isInside(x, y, l, t, r, b))
	addSelection(i);
      else
	if (x > r)
	  break; // stop looking
    }
}

void PlotView::mouseDown (const MouseEvent &e)
{
  // shoudnt happen
  if (focuslayer==(Layer *)NULL) return;

  int mxp=e.getMouseDownX();
  int myp=e.getMouseDownY();
  AxisView* haxview=plotter->getHorizontalAxisView();
  AxisView* vaxview=plotter->getVerticalAxisView();
  
  // cache mouse down position  FIX THIS ISNT NEEDED
  mousedown.setXY(mxp, myp);
  mousemove.setXY(mxp, myp);
  
  // Control-Click: add point make selection
  // Control-Shift-Click: add point add selection.
  // Control-Option-Click: call plot hook
  if (e.mods.isCtrlDown())
    if (e.mods.isAltDown())
      {
	String str=T("(call-plot-hook");
	str << T(" ") << plotter->getPlotTitle().quoted()
	    << T(" ") << haxview->toValue(mxp)
	    << T(" ") << vaxview->toValue(myp) 
	    << T(")") ; 
	Scheme::getInstance()->eval(str);
	return;
      }
    else
      {
	int i = focuslayer->addPoint(haxview->toValue(mxp),
				     vaxview->toValue(myp));
	if (e.mods.isShiftDown())
	  addSelection(i);
	else setSelection(i);
	repaintFocusPlot();
	return;
      }
  
  double half=plotter->getPointSize()/2;
  int h=-1;
  double left, top, right, bottom, x, y;
  
  if (focuslayer->isDrawStyle(Layer::hbox)) 
    {
      // speed: since box height is constant check point y againt a
      // (constant) vertical box height centered on mouse y
      top=vaxview->toValue( myp - half);
      bottom=vaxview->toValue( myp + half);
      x=haxview->toValue( mxp);
      for (int i=0; i < focuslayer->numPoints(); i++)
	{
	  left=focuslayer->getPointX(i);
	  right=left+focuslayer->getPointZ(i);
	  y=focuslayer->getPointY(i);
	  if ( isInside(x, y, left, top, right, bottom) )
	    {
	      h=i;
	      break;
	    }
	  // give up when points are rightward of mouse x
	  else if (left > x)
	    break;
	}
    }
  else
    {
      // calc a constant "point" around mouse x and y and try to
      // find a point thats inside it
      left=haxview->toValue( mxp - half);
      top=vaxview->toValue( myp - half);
      right=haxview->toValue( mxp + half);
      bottom=vaxview->toValue( myp + half);
      for (int i=0; i < focuslayer->numPoints(); i++)
	{
	  x=focuslayer->getPointX(i);
	  y=focuslayer->getPointY(i);
	  if (isInside(x, y, left, top , right, bottom)) 
	    {
	      h=i;
	      break;
	    } 
	  // give up when points are rightward of mouse x
	  else if (x > right) 
	    break;
	}
    }
  
  if (h<0) 
    {
      // Mouse down on empty space . Add to selection if shift is down
      if (isSelection())
	{
	  if (!e.mods.isShiftDown())
	    {
	      deselectAll();
	    }
	}
      addChildComponent (&region);
      region.beginSweep(e, haxview, vaxview);
    }
  else if (isSelected(h)) 
    {
      // point is already selected.
      // Mouse-shift-click remove Point from selection
      if (e.mods.isShiftDown())
	{
	  removeSelection(h);
	  repaintFocusPlot();
	}
    }
  else
    {
      // point is not selected.
      // Mouse-Click: set point as (single) selection
      // Mouse-shift-click:   add Point from selection
      if (e.mods.isShiftDown()) 
	addSelection(h);
      else setSelection(h);
      repaintFocusPlot();
    }
}

void PlotView::mouseDrag(const MouseEvent &e) {
  AxisView * haxview=plotter->getHorizontalAxisView();
  AxisView * vaxview=plotter->getVerticalAxisView();
  
  if ( isSelection() ) {
    float dx=haxview->toValue(e.x) - haxview->toValue(mousemove.getX()) ;
    float dy=vaxview->toValue(e.y) - vaxview->toValue(mousemove.getY()) ;
    //    for (int i=0; i<numSelected(); i++)
    //      focuslayer->incPoint( getSelected(i), dx, dy);
    dragSelection(dx, dy);
    repaintFocusPlot();
    mousemove.setXY(e.x,e.y);
  } 
  else {
    region.toFront(false);
    region.sweep(e);
  }
}

void PlotView::mouseUp(const MouseEvent &e)
{
  if ( isSelection() ) 
    {
      if (mousedown.getX() != mousemove.getX() ) 
	{
	  focuslayer->sortPoints();
	  //printSelection();
	}
      repaintFocusPlot();
    }
  else if ( e.getDistanceFromDragStart() == 0) 
    {
      // clicked without drag
    }
  else
    {
      // get region extent before closing region!
      float l = region.minX();
      float t = region.maxY();
      float r = region.maxX();
      float b = region.minY();
      region.endSweep(e);
      selectPointsInside(l,t,r,b);
      removeChildComponent(&region);
      repaintFocusPlot();
    }
}

void PlotView::mouseDoubleClick(const MouseEvent &e)
{
  PlotterWindow* w=(PlotterWindow*)getTopLevelComponent();
  if (isSelection()) 
    w->openEditPointsDialog();
  else
    w->openLayerDialog();
}

bool PlotView::keyPressed (const KeyPress& key)
{
  if ((key.isKeyCode(KeyPress::backspaceKey) ||
       key.isKeyCode(KeyPress::deleteKey)))
    {
      if (!key.getModifiers().isAnyModifierKeyDown() &&
	  isSelection())
	deleteSelection();
    }
  else if (key.isKeyCode('a') && 
	   key.getModifiers().isCommandDown())
    {
      selectAll();
    }


  return true;
}

/*=======================================================================*
             Plotter: contains all the subcomponents for plotting
 *=======================================================================*/

PointClipboard pointClipboard;

Plotter::Plotter (XmlElement* plot) 
  : ppp (8.0),
    zoom (1.0),
    haxview (NULL),
    vaxview (NULL),
    viewport (NULL),
    plotview (NULL),
    backview (NULL),
    flags (0)
{
  createPlottingComponents();
  OwnedArray<XmlElement> xmlfields;
  OwnedArray<XmlElement> xmlplots;
  if (plot!=NULL)
    {
      std::cout << plot->createDocument(T("")).toUTF8() << "\n";
      XmlElement* sub=plot->getChildByName(T("fields"));
      forEachXmlChildElement(*sub, e)
	if (e->hasTagName(T("field")))
	  xmlfields.add(e);
      sub=plot->getChildByName(T("layers"));
      forEachXmlChildElement(*sub, e)
        if (e->hasTagName(T("points")))
	  xmlplots.add(e);
    }  
  if (xmlfields.size()==0) // No axes specified
    {
      fields.add(new Field(T("Field 1"), new Axis(NULL)));
      fields.add(new Field(T("Field 2"), new Axis(NULL)));
    }
  else if (xmlfields.size()==1) // Just Y axis specified
    {
      fields.add(new Field(T("Field 1"), new Axis(Axis::ordinal)));
      String yname=xmlfields[0]->
	getStringAttribute(T("name"), T("Field 2"));
      fields.add(new Field(yname,new Axis(xmlfields[0])));
    }
  else
    for (int i=0; i<xmlfields.size(); i++)
      {
	String n=xmlfields[i]->
	  getStringAttribute(T("name"), T("Field ")+String(i+1));
	String r=xmlfields[i]->
	  getStringAttribute(T("axis"), String::empty);
	Axis* a=NULL;
	int s=-1;
	if (r.isNotEmpty())
	  for (int j=0; j<i && j<fields.size() && a==NULL; j++)
	    if (fields[j]->name==r)
	      {
		a=fields[j]->axis;	
		s=j;
	      }
	if (a)
	  ;
	else
	  a=new Axis(xmlfields[i]);
	fields.add(new Field(n, a, s));
      }
  if (xmlplots.size()>0)
    for (int i=0; i<xmlplots.size(); i++)
      newLayer(xmlplots[i]);
  else
    newLayer(NULL);
  autosizeAxes();
  xmlfields.clear(false);
  xmlplots.clear(false);
  plotview->resizeForDrawing();  // calc plots width/height
}

Plotter::Plotter(MidiFile& midifile)
  : ppp (8.0),
    zoom (1.0),
    haxview (NULL),
    vaxview (NULL),
    viewport (NULL),
    plotview (NULL),
    backview (NULL),
    flags (0)
{
  createPlottingComponents();
  // juce time format is postive for beats and negative for SMTPE
  int format=midifile.getTimeFormat();
  double scaler=1.0; // scale smpte to seconds
  if (format>0)
    midifile.convertTimestampTicksToSeconds();    
  else  // juce smpte frames per second is negative upper byte
    scaler=(0xFF-((format & 0xFF00) >> 8)+1) * (format & 0xFF);
  // start importing at track 1 in level 1 file (?)
  int numtracks=midifile.getNumTracks();
  int track=((numtracks==1) ? 0 : 1);
  int count=0;
  double maxend=0.0;
  double maxkey=-1.0;
  double minkey=128.0;
  OwnedArray<Layer>midilayers;
  int arity=5;
  for ( ; track<numtracks; track++)
    {
      MidiMessageSequence* seq=
	(MidiMessageSequence*)midifile.getTrack(track);
      seq->updateMatchedPairs();
      Layer* lay=new Layer(arity, T("Track ") + String(track),
			   Layer::defaultColor(count), Layer::hbox);
      //lay->setXField(0);
      //lay->setYField(2);
      //lay->setZField(1);
      lay->setFieldAccess(0,2,1);
      for (int i=0; i<seq->getNumEvents(); i++)
	{
	  MidiMessageSequence::MidiEventHolder* h=seq->getEventPointer(i);
	  if (h->message.isNoteOn())
	    {
	      double t=h->message.getTimeStamp()/scaler;
	      double d=.5;
	      if (h->noteOffObject!=NULL)
		d=(h->noteOffObject->message.getTimeStamp()/scaler)-t;
	      double k=h->message.getNoteNumber();
	      double a=(double)(h->message.getFloatVelocity());
	      double c=h->message.getChannel()-1;
	      LayerPoint* p=new LayerPoint(arity);
	      p->setVal(0,t);
	      p->setVal(1,d);
	      p->setVal(2,k);
	      p->setVal(3,a);
	      p->setVal(4,c);
	      lay->_points.add(p);  // add same order as seq
	      if (k<minkey) minkey=k;
	      if (k>maxkey) maxkey=k;
	      t+=d;
	      if (t>maxend) maxend=t;
	    }
	}
      if (lay->numPoints()==0)
	delete lay;
      else
	{
	  midilayers.add(lay);
	  count++;
	}
    }
  Axis* a=new Axis(Axis::seconds);
  if (maxend>0.0) a->setMaximum(maxend);
  fields.add(new Field(T("Time"), a));
  fields.add(new Field(T("Duration"), a, 0));
  fields.add(new Field(T("Keynum"), new Axis(Axis::keynum)));
  fields.add(new Field(T("Amplitude"), new Axis(Axis::normalized)));      
  fields.add(new Field(T("Channel"), new Axis(Axis::generic,0,15,1,1,0)));
  for (int i=0;i<midilayers.size();i++)
    addLayer(midilayers[i]);
  midilayers.clear(false);
  plotview->resizeForDrawing();  // calc plots width/height
}

void Plotter::createPlottingComponents()
{
  int II=0;
  font=Font(Font::getDefaultSansSerifFontName(), 10.0, Font::bold);
  plotview=new PlotView (this);
  backview=new BackView(this);
  // plot view is child of backview so that it is in front
  //std::cout << II++ << "\n"; //0
  backview->addChildComponent(plotview);
  //std::cout << II++ << "\n";
  plotview->setTopLeftPosition(0,0);
  //std::cout << II++ << "\n";
  plotview->setWantsKeyboardFocus(true);
  //std::cout << II++ << "\n";
  viewport=new PlotViewport (this);
  //std::cout << II++ << "\n";
  // add the backview to the viewport. the plotview is a child of the
  // backview and so it will scroll with it
  addChildComponent(viewport);
  //std::cout << II++ << "\n"; //5
  haxview=new AxisView(viewport, horizontal);
  //std::cout << II++ << "\n";
  vaxview=new AxisView(viewport, vertical);
  //std::cout << II++ << "\n";
  addChildComponent(haxview);  
  //std::cout << II++ << "\n";
  addChildComponent(vaxview);  
  //std::cout << II++ << "\n";
  viewport->setViewedComponent(backview);
  //std::cout << II++ << "\n"; //10
  viewport->setScrollBarsShown (true, true);
  // std::cout << II++ << "\n";
  viewport->setViewPositionProportionately(0.0,1.0);
  //std::cout << II++ << "\n";
  viewport->setVisible(true);
  //std::cout << II++ << "\n";
  backview->setVisible(true);
  //std::cout << II++ << "\n";
  plotview->setVisible(true);
  //std::cout << II++ << "\n";//15
  haxview->setVisible(true);
  //std::cout << II++ << "\n";
  vaxview->setVisible(true);
  ///std::cout << II++ << "\n";
}

void Plotter::setPlottingFields(int xax, int yax)
{
  setHorizontalAxis(fields[xax]->axis);
  setVerticalAxis(fields[yax]->axis);
  plotview->resizeForDrawing();  // calc plots width/height
}

Plotter::~Plotter()
{
  // zero out shared axis before deleting
  deleteAndZero(haxview);
  deleteAndZero(vaxview);
  deleteAndZero(plotview);
  deleteAndZero(backview);
  deleteAndZero(viewport);
  //actions.clear();
  layers.clear();
  fields.clear();
}

void Plotter::autosizeAxes()
{
  // look for unspecified axes to autosize
  for (int i=0;i<fields.size();i++)
    {
      if (fields[i]->isSharedAxis()) continue; // skip if shared
      Axis* ax=fields[i]->axis;
      if (ax->type==Axis::unspecified)
	{
	  double lo=0.0, hi=1.0;
	  for (int j=0; j<layers.size(); j++)
	    {
	      Layer* l=layers[j];
	      if (l->numPoints()==0) 
		continue;
	      if (i==0) // horizontal axis stored sorted
		{
		  lo=jmin(lo,(double)(l->getFirstPoint()->getVal(0)));
		  hi=jmax(hi,(double)(l->getLastPoint()->getVal(0)));
		}
	      else
		for (int k=0; k<l->numPoints(); k++)
		  {
		    double f=(double)(l->getPoint(k)->getVal(i));
		    lo=jmin(lo,f);
		    hi=jmax(hi,f);
		  }
	    }
	    ax->setMinimum(lo);

	  if (hi<=1.0)
	    {
	      ax->setMaximum(1.0);
	    }
	  else if (hi<=10.0)
	    {
	      ax->setMaximum(ceil(hi));
	      ax->setIncrement(1.0);
	    }
	  else if (hi<=100.0)
	    {
	      ax->setMaximum(ceil(hi));
	      ax->setIncrement(10.0);
	      ax->setTicks(2);
	    }
	  else if (hi<=1000)
	    {
	      ax->setMaximum(ceil(hi));
	      ax->setIncrement(10.0);
	      ax->setTicks(2);
	    }
	  ax->type=Axis::generic; // make it a generic axis
	  //std::cout << "autosized axis[" << i <<"]: min=" << ax->getMinimum() << " max=" << ax->getMaximum() << "\n";
	}
      else if (ax->type==Axis::ordinal)
	{
	  int siz=1;
	  for (int j=0; j<layers.size(); j++)
	    siz=jmax(siz,layers[j]->numPoints());
	  ax->setMaximum(siz-1);
	}
    }
}

void Plotter::insurePointsVisible()
{
  if (getPlotViewport()->isVerticalScrollBarShown())
    {
      // center on average of min max of first 8 notes
      Layer* l=getFocusLayer();
      double y=.5;
      if (l->numPoints()>0)
	{
	  Axis* a=getVerticalAxis();
	  double ymin=a->getMaximum();
	  double ymax=a->getMinimum();
	  for (int i=0;i<8 && i<l->numPoints(); i++)
	    {
	      y=l->getPointY(i);
	      if (y<ymin) ymin=y;
	      if (y>ymax) ymax=y;
	    }
	  y=1-((((ymin+ymax)/2)-a->getMinimum())/a->getRange());
	}
      getPlotViewport()->setViewPositionProportionately(0.0, y);
    }
}
 
///
/// Component View Accessing 
///

AxisView* Plotter::getHorizontalAxisView() {return haxview;}
AxisView* Plotter::getVerticalAxisView() {return vaxview;}

void Plotter::setHorizontalAxis (Axis* a) {haxview->setAxis(a);}
void Plotter::redrawHorizontalAxisView() {haxview->repaint();}

void Plotter::setVerticalAxis (Axis* a) {vaxview->setAxis(a);}
void Plotter::redrawVerticalAxisView() {vaxview->repaint();}

Axis* Plotter::getVerticalAxis(){return vaxview->getAxis();}
Axis* Plotter::getHorizontalAxis(){return haxview->getAxis();}
 
void Plotter::setFocusVerticalField(int i)
{
  /*  Layer* layer=getFocusLayer();
  layer->setYField(i);
  setVerticalAxis(layer->getAxis(i));
  redrawVerticalAxisView();
  redrawPlotView();
  */
}

BackView * Plotter::getBackView() {
  return backview;
}

bool Plotter::isBackViewPlotting() {
  return backview->isBackViewPlotting();
}

void Plotter::setBackViewPlotting( bool b) {
  backview->setBackViewPlotting(b);
}

void Plotter::setBackViewCaching(bool b)
{
  backview->setBackViewCaching(b);
}

void Plotter::resizeForSpread()
{
  plotview->resizeForDrawing();
}

Plotter::BGStyle Plotter::getBackViewStyle() {
  return backview->getBackViewStyle();
}

void Plotter::setBackViewStyle( BGStyle b) {
  backview->setBackViewStyle(b);
}

PlotView * Plotter::getPlotView() {
  return plotview;
}

PlotViewport * Plotter::getPlotViewport() {
  return viewport;
}

void Plotter::redrawPlotView() {
  plotview->repaint();
}

void Plotter::redrawBackView() {
  backview->repaint();
}

///
/// layers
///

Layer* Plotter::getLayer(int i) 
{
  return layers[i];
}

Layer* Plotter::findLayer(int id) 
{
  Layer* l;
  for (int i=0; i< layers.size(); i++)
    {
      l=layers[i];
    if (id == l->getLayerID()) return l;
    }
  return (Layer *)NULL;
}

int Plotter::numLayers() 
{
  return layers.size();
}

Layer* Plotter::getFocusLayer()
{
  return plotview->focuslayer;
}

bool Plotter::isFocusLayer(Layer * l)
{
  return (l == getFocusLayer()); 
}


void Plotter::setFocusLayer(Layer * layr)
{
  plotview->deselectAll(false);
  plotview->focuslayer=layr;
  Axis* oldx=getHorizontalAxisView()->getAxis();
  Axis* oldy=getVerticalAxisView()->getAxis();
  Axis* newx=getFieldAxis(layr->getXField());
  Axis* newy=getFieldAxis(layr->getYField());
  if ((oldx!=newx)||(oldy!=newy))
    {
      setHorizontalAxis(newx);
      setVerticalAxis(newy);
      // doesnt work here...
      //      plotview->resizeForDrawing();  // calc plots width/height
    }
}

void Layer::addXmlPoints(XmlElement* points)
{
  StringArray pts;
  int ind=0;
  forEachXmlChildElement(*points, p)
    {
      LayerPoint* f=new LayerPoint(arity);
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
      _points.addSorted(*this,f);
      pts.clear();
    }
}

Layer* Plotter::newLayer(XmlElement* points)
{
  Colour col = Layer::defaultColor(layers.size());
  int sty=Layer::lineandpoint;
  String nam = T("Layer ") + String(layers.size()+1);
  int num=numFields();
  Layer* layer=NULL;

  if (points)
    {
      String s=points->getStringAttribute(T("style"));
      if (s.isNotEmpty())
	sty=Layer::toLayerType(s, sty);
      s=points->getStringAttribute(T("color"));
      if (s.isNotEmpty())
	if (s.containsOnly(T("0123456789aAbBcCdDeEfF")))
	  col=Colour::fromString(s);	  
	col=Colours::findColourForName(s, col);
      nam=points->getStringAttribute(T("title"), nam);
      layer=new Layer(num, nam, col, sty);
      layer->addXmlPoints(points);
      // parse optional access fields
      StringArray access;
      access.addTokens(points->getStringAttribute(T("access")), false);
      for (int i=0; i<access.size() && i<4; i++)
	{
	  int j=access[i].getIntValue();
	  if (j>=layer->getLayerArity()) break;
	  else if (i==0) layer->setXField(j);
	  else if (i==1) layer->setYField(j);
	  else if (i==2) layer->setZField(j);
	  else if (i==3) ; // TODO!
	}
    }
  else
    layer=new Layer(num, nam, col, sty);
  addLayer(layer);
  return layer;
}

void Plotter::addLayer(Layer* layer)
{
  layers.add(layer);
  setFocusLayer(layer);
}

void Plotter::removeLayer(Layer* layer) 
{
  // THIS CHECK SHOULDNT BE NECESSARY (MENU CHECKS)
  if ( numLayers() < 2 ) return;
  // if removing focus layer then switch focus to other layer.
  if ( isFocusLayer(layer) ) 
    {
      for (int i=0; i<numLayers(); i++) 
	{
	  Layer* l=getLayer(i);
	  if (l != layer) 
	    {
	      setFocusLayer(l);
	      break;
	    }
	}
    }

  layers.removeObject(layer,false);
}

void Plotter::selectAll() 
{
  getPlotView()->selectAll();
}

void Plotter::deselectAll()
{
  getPlotView()->deselectAll();
}

bool Plotter::isSelection() 
{
  return getPlotView()->isSelection();
}

int Plotter::numSelected() 
{
  return getPlotView()->numSelected();
}

void Plotter::deleteSelection(bool cut) 
{
  getPlotView()->deleteSelection(cut);
}

void Plotter::resized () 
{
  //viewport->setBounds(60, 60, getWidth()-100, getHeight()-150);
  //vaxview->setBounds(30, 60, 26, viewport->getViewHeight());
  //haxview->setBounds(60, 30, viewport->getViewWidth(), 26); 
  viewport->setBounds(70, 50, getWidth()-80, getHeight()-60);
  vaxview->setBounds(2, 50, 64, viewport->getViewHeight());
  haxview->setBounds(70, 20, viewport->getViewWidth(), 26); 
  //std::cout << "width=" << getWidth() << " height=" << getHeight() << "\n";
}

void Plotter::scrollBarMoved (ScrollBar * sb, const double nrs) {
  // Scrolling callback. Used to scroll the axis views whenever
  // viewport's scrollbar is scrolled.
  String name = sb->getName();
  
  if ( name == T("xscroll") )
    haxview->repaint();
  else
    vaxview->repaint();
}

/*=======================================================================*
                                 Edit Actions
 *=======================================================================*/

class DeleteLayerAction : public UndoableAction 
{
  // this should probably only be applicable on the focus layer
  Layer* layer;
  Plotter* plotter;
public:
  DeleteLayerAction(Plotter* p, Layer* l) 
  {
    plotter=p;
    layer=l;
  }
  ~DeleteLayerAction() {delete layer;}
  bool perform() 
  {
    // plotter must hold (at least) 1 layer.
    if (plotter->numLayers() == 1) return false;
    plotter->removeLayer(layer);
    plotter->redrawBackView();
    plotter->redrawPlotView();
    return true;
  }
  bool undo () 
  {
    plotter->addLayer(layer);
    plotter->redrawBackView();
    plotter->redrawPlotView();
    return true;
  }
  int getSizeInUnits(){return 1;}
};

class RenameLayerAction : public UndoableAction 
{
  String name;
  Layer* layer;
  Plotter* plotter;
  void rename() {
    String s=layer->getLayerName();
    layer->setLayerName(name);
    name=s;   // cache old name
  }
public:
  RenameLayerAction(Plotter* p, Layer* l, String n) 
  {
    layer=l;
    name=n;
  }
  ~RenameLayerAction() {}
  bool perform() {rename(); return true; }
  bool undo () {rename(); return true; }
  int getSizeInUnits(){return 1;}
};

//class AddPointsAction : public UndoableAction {}
//class RemovePointsAction : public UndoableAction {}


/*=======================================================================*
                   PlotterWindow: top level window for plotting
 *=======================================================================*/

PlotterWindow::PlotterWindow(XmlElement* plot)
  : DocumentWindow (String::empty, Colours::white, 
		    DocumentWindow::allButtons, true),
    listener(this)
{
  String title=(plot==NULL) ? T("Untitled Plot") :
    plot->getStringAttribute(T("title"), T("Untitled Plot"));
  setName(title);
  plotter = new Plotter(plot) ;
  init();
}

PlotterWindow::PlotterWindow(String title, MidiFile& midifile)
  : DocumentWindow (title, Colours::white, 
		    DocumentWindow::allButtons, true),
    listener(this)
{
  setName(title);
  plotter=new Plotter(midifile);
  init();
}

PlotterWindow::~PlotterWindow ()
{
  delete menubar;
  setMenuBar(0);
}

void PlotterWindow::init()
{
  menubar = new MenuBarComponent(this);
  setMenuBar(this);
  setUsingNativeTitleBar(true);    
  plotter->setSize(500, 500);
  plotter->setVisible(true);
  setContentComponent(plotter,true,true);
  centreWithSize (plotter->getWidth(), plotter->getHeight());
  setResizable(true, true); 
  setVisible(true);
  setComponentProperty(T("WindowType"), WindowTypes::PlotWindow);
  plotter->insurePointsVisible();
}

PlotterWindow* PlotterWindow::getPlotWindow(String title)
{
  for (int i=0; i<TopLevelWindow::getNumTopLevelWindows(); i++)
    {
      TopLevelWindow* w=TopLevelWindow::getTopLevelWindow(i);
      if (WindowTypes::isWindowType(w, WindowTypes::PlotWindow) &&
	  w->getName()==title)
	return (PlotterWindow*)w;
    }
  return (PlotterWindow*)NULL;
}

void PlotterWindow::openWindowFromXml(void* ptr) //(String str)
{
  //std::cout << str.toUTF8() << "\n";
  XmlDocument doc (String((char *)ptr));
  XmlElement* xml = doc.getDocumentElement();
  if (xml && xml->getChildByName(T("fields")) &&
      xml->getChildByName(T("layers")))
    {
      new PlotterWindow(xml);
      delete xml;
    }
  else
    {
      String err=T(">>> Error ");
      if (!xml)
	err << doc.getLastParseError() << T("\n");
      else
	{
	  err << T("invalid xml plot data\n");
	  delete xml;
	}
      Console::getInstance()->printError(err);
    }
}

void PlotterWindow::browseForFileToOpen(int type)
{
  if (type==CommandIDs::PlotterOpenMidiFile)
    {
      FileChooser ch (T("Plot Midi File"),
		      File::getCurrentWorkingDirectory(),
		      T("*.mid"));
      if (ch.browseForFileToOpen())
	openMidiFile(ch.getResult());
    }
  else if (type==CommandIDs::PlotterOpen)
    {
      FileChooser ch (T("Open Plot"), 
		      File::getCurrentWorkingDirectory(),
		      T("*.xml"));
      if (ch.browseForFileToOpen())
	openXmlFile(ch.getResult());
    }
}

void PlotterWindow::openXmlFile(File file)
{
  XmlDocument doc (file);
  XmlElement* xml = doc.getDocumentElement();
  if (xml && xml->getChildByName(T("fields")) &&
      xml->getChildByName(T("layers")))
    {
      PlotterWindow* w=new PlotterWindow(xml);
      w->setPlotFile(file);
      delete xml;
    }
  else
    {
      String err=T(">>> Error: ");
      if (!xml)
	err << doc.getLastParseError() << T("\n");
      else
	{
	err << file.getFullPathName() 
	    << T(" is not a valid plot (xml) file.\n");
	delete xml;
	}
      Console::getInstance()->printError(err);
    }
}

void PlotterWindow::openMidiFile(File file)
{
  String title=file.getFileNameWithoutExtension();
  FileInputStream* input=file.createInputStream();
  MidiFile midifile;
  if (midifile.readFrom(*input))
    new PlotterWindow(title, midifile);
  else
    {
      String err=T(">>> Error: ");
      err << file.getFullPathName() 
	  << T(" is not a valid midi file.");
      Console::getInstance()->printError(err);
    }
}

bool PlotterWindow::save(bool saveas)
{
  File f=getPlotFile();
  if (saveas || (f==File::nonexistent))
    {
      String t=((saveas) ? T("Save Plot As") : T("Save Plot"));
      if (f==File::nonexistent)
	f=File::getCurrentWorkingDirectory().getChildFile(getName() + T(".xml"));
      FileChooser ch (t, f, "*.xml");
      if (ch.browseForFileToSave(true))
	// std::cout << ch.getResult().getFullPathName().getUTF8() << "\n";
	setPlotFile(ch.getResult());
      else
	return false;
    }
  String text=toXmlString();
  if (!getPlotFile().replaceWithText(text))
    {
      text=T(">> Error: file ")+getPlotFile().getFullPathName() + T(" not writable.\n");
      Console::getInstance()->printError(text);
      return false;
    }
  return true;
}

void PlotterWindow::closeButtonPressed () //{this->~PlotterWindow();}
{
  int x=Alerts::showYesNoCancelBox(AlertWindow::QuestionIcon,
					T("Close"),
					T("Save changes before closing?"),
#ifdef WINDOWS
					T("Yes"),
					T("No"),
				        T("Cancel"));
#else
					T("Save"),
					T("Don't Save"),
					T("Cancel"));
#endif

  if (x==0)
    return;
  if (x==2 || save())
    delete this;
}

const StringArray PlotterWindow::getMenuBarNames ()
{
  const tchar* const menuNames[] =
    {T("Plot"), T("Edit"), T("View"), T("Audio"), T("Window"), T("Help"), 0};
  return StringArray((const tchar**) menuNames);
}

const PopupMenu PlotterWindow::getMenuForIndex(int idx, const String &name)
{
  PopupMenu menu;
  PopupMenu sub1, sub2, sub3;
  int val;
  int arity=plotter->numFields();
  
  if (name==T("Plot"))
    {
      // File Menu
      menu.addItem(CommandIDs::PlotterNew, T("New Plot"));
      menu.addItem(CommandIDs::PlotterOpen, T("Open..."));
      menu.addItem(CommandIDs::PlotterOpenMidiFile,T("Plot Midi File..."));
      menu.addSeparator(); 
      menu.addItem(CommandIDs::PlotterLayerAdd, T("New Layer"));
      for (int i=0; i<plotter->numLayers(); i++)
	{
	  Layer* layer=plotter->getLayer(i);
	  sub1.addColouredItem(CommandIDs::PlotterLayerSelect +
			      layer->getLayerID(),
			      layer->getLayerName(),
			      layer->getLayerColor(),
			      true,
			      plotter->isFocusLayer(layer));
	}
      sub1.addSeparator(); 
      sub1.addItem(CommandIDs::PlotterLayerDelete, T("Delete"),
		   (plotter->numLayers() > 1));
      menu.addSubMenu(T("Layers"), sub1);
      menu.addSeparator();
      menu.addItem(CommandIDs::PlotterClose, T("Close"));
      menu.addItem(CommandIDs::PlotterSave, T("Save"));
      menu.addItem(CommandIDs::PlotterSaveAs, T("Save As..."),
		   (getPlotFile()!=File::nonexistent));
      menu.addSeparator();
      menu.addItem(CommandIDs::PlotterRename, T("Rename..."));
      menu.addItem(CommandIDs::PlotterExport, T("Export..."));
    }
  else if (name==T("Edit"))
    {
      int sel=plotter->numSelected();
      // Edit Menu
      menu.addItem(CommandIDs::EditorUndo, T("Undo"),
		   plotter->actions.canUndo());
      menu.addItem(CommandIDs::EditorUndo, T("Redo"),
		   plotter->actions.canRedo());
      menu.addSeparator();
      menu.addItem(CommandIDs::EditorCut, T("Cut"), (sel>0));
      menu.addItem(CommandIDs::EditorCopy, T("Copy"), (sel>0));
      menu.addItem(CommandIDs::EditorPaste, T("Paste"),
		   !pointClipboard.isEmpty());
      menu.addSeparator();
      menu.addItem(CommandIDs::EditorSelectAll, T("Select All"));
      menu.addItem(CommandIDs::EditorUnselectAll, T("Clear Selection"),
		   (sel>0));
      menu.addSeparator(); 
      menu.addItem(CommandIDs::PlotterEditPoints, T("Edit Points"),
		   (sel>0));
      menu.addItem(CommandIDs::PlotterShiftPoints, T("Shift Points"),
		   (sel>0));
      menu.addItem(CommandIDs::PlotterRescalePoints, T("Rescale Points"),
		   (sel>1));
    }

  else if (name==T("View"))
    {
      Layer* layer=plotter->getFocusLayer();
      val=layer->getLayerStyle();
      // add these with focus colored items to make it clear that the
      // styling change only affects the focus plot
      menu.addItem(CommandIDs::PlotterStyle + Layer::line, 
		   T("Line"), true,
		   (val==Layer::line));
      menu.addItem(CommandIDs::PlotterStyle + Layer::point,
		   T("Point"), true,
		   (val==Layer::point));
      menu.addItem(CommandIDs::PlotterStyle + Layer::lineandpoint,
		   T("Envelope"), true,
		   (val==Layer::lineandpoint));
      menu.addItem(CommandIDs::PlotterStyle + Layer::hbox, 
		   T("Horizontal Box"),
		   (arity > 2), 
		   (val==Layer::hbox));
      menu.addItem(CommandIDs::PlotterStyle + Layer::vbox,
		   T("Vertical Box"),
		   (arity > 2), 
		   (val==Layer::vbox));
      menu.addItem(CommandIDs::PlotterStyle + Layer::impulse, 
		   T("Impulse"),
		   true, (val==Layer::impulse));
      menu.addItem(CommandIDs::PlotterStyle + Layer::histogram, 
		   T("Histogram"),
		   true, 
		   (val==Layer::histogram));
      menu.addItem(CommandIDs::PlotterStyle + Layer::vbar, 
		   T("Vertical Bar"),
		   false,
		   (val==Layer::vbar));
      /*	menu.addSeparator(); 
		// 0'th field is hardwired to x axis.
		for (int i=1; i<layer->getLayerArity(); i++)
		sub2.addItem(CommandIDs::PlotterVertical + i,
		layer->getFieldName(i),
		true,
		(layer->getYField()==i));
		menu.addSubMenu(T("Vertical Display"), sub2, true);
      */
      menu.addSeparator();
      val=plotter->getBackViewStyle();
      sub1.addItem(CommandIDs::PlotterBgStyle + Plotter::bgGrid,
		   T("Grid"),
		   true, 
		   (val==Plotter::bgGrid));
      sub1.addItem(CommandIDs::PlotterBgStyle + Plotter::bgTiled,
		   T("Tiled"),
		   true, 
		   (val==Plotter::bgTiled));
      sub1.addItem(CommandIDs::PlotterBgStyle + Plotter::bgSolid,
		   T("Solid"),
		   true, 
		   (val==Plotter::bgSolid));
      sub1.addSeparator();
      sub1.addItem(CommandIDs::PlotterBgColor,
		   T("Colors..."), 
		   false);
      sub1.addSeparator();
      sub1.addItem(CommandIDs::PlotterBgPlotting,
		   T("Show All Layers"), 
		   true, 
		   plotter->isBackViewPlotting() );
      menu.addSubMenu(T("Background"), sub1, true);    
      menu.addSeparator();
    }
  else if (name==T("Audio"))
    menu=CommandMenus::getAudioMenu(false);
  else if (name==T("Window"))
    menu=CommandMenus::getWindowMenu();
  else if (name==T("Help")) 
    menu=CommandMenus::getHelpMenu(WindowTypes::PlotWindow, 0);
  return menu;
}

void PlotterWindow::menuItemSelected (int id, int idx)
{
  CommandID cmd = CommandIDs::getCommand(id);
  int data = CommandIDs::getCommandData(id);  
  int type = CommandIDs::getCommandType(id);  
  
  switch (cmd)
    {
    case CommandIDs::PlotterNew :
      new PlotterWindow((XmlElement*)NULL);
      break;
    case CommandIDs::PlotterOpen :
    case CommandIDs::PlotterOpenMidiFile :
      browseForFileToOpen(cmd);
      break;
    case CommandIDs::PlotterSave :
      save();
      break;
    case CommandIDs::PlotterSaveAs :
      save(true);
      break;
    case CommandIDs::PlotterRename :
      {
	AlertWindow w (T("Rename Plot"), String::empty, 
		       AlertWindow::NoIcon);
	w.addTextEditor(T("rename"), getName(), String::empty);
	w.addButton(T("Cancel"), 0, KeyPress(KeyPress::escapeKey, 0, 0));
	w.addButton(T("Rename"), 1, KeyPress(KeyPress::returnKey, 0, 0));
	if (w.runModalLoop() != 0) // picked 'ok'
	  setName(w.getTextEditorContents(T("rename")));
      }
      break;
    case CommandIDs::PlotterExport :
      openExportDialog();
      break;
    case CommandIDs::PlotterClose :
      closeButtonPressed();
      break;
    case CommandIDs::EditorUndo :
      plotter->actions.undo();
      break;
    case CommandIDs::EditorRedo :
      plotter->actions.redo();
      break;
    case CommandIDs::EditorCut :
      plotter->deleteSelection(true);
      break;
    case CommandIDs::EditorSelectAll :
      plotter->selectAll();
      break;
    case CommandIDs::EditorUnselectAll :
      plotter->deselectAll();
      break;
    case CommandIDs::PlotterEditPoints :
      openEditPointsDialog();
      break;
   case CommandIDs::PlotterShiftPoints :
      openRescalePointsDialog(cmd);
      break;
   case CommandIDs::PlotterRescalePoints :
      openRescalePointsDialog(cmd);
      break;    
    case CommandIDs::PlotterLayerAdd :
      plotter->newLayer(NULL);
      plotter->redrawBackView();
      plotter->redrawHorizontalAxisView();
      plotter->redrawVerticalAxisView();
      break;
    case CommandIDs::PlotterLayerDelete :
      plotter->actions.perform
	(new DeleteLayerAction(plotter,
			       plotter->getFocusLayer()),
	 T("Delete Layer"));
      break;
    case CommandIDs::PlotterLayerSelect :
      plotter->setFocusLayer(plotter->findLayer(data));
      plotter->redrawBackView();
      plotter->redrawPlotView();
      plotter->redrawHorizontalAxisView();
      plotter->redrawVerticalAxisView();
      break;
    case CommandIDs::PlotterStyle :
      plotter->getFocusLayer()->setLayerStyle(data);
      plotter->redrawPlotView();
      break;
    case CommandIDs::PlotterVertical :
      plotter->setFocusVerticalField(data);
      break;
    case CommandIDs::PlotterBgStyle :
      plotter->setBackViewStyle( (Plotter::BGStyle)data);
      plotter->redrawBackView();
      break;
    case CommandIDs::PlotterBgColor :
      break;
    case CommandIDs::PlotterBgPlotting :
      plotter->setBackViewPlotting( ! plotter->isBackViewPlotting()); 
      plotter->redrawBackView();
      break;
    default :
      break;
    }
}

void PlotterWindow::PlotterWindowListener::handleMessage(const Message &m)
{

  switch (m.intParameter1)
    {
    case CommandIDs::PlotterAddXmlPoints:
      if (m.pointerParameter!=NULL)
	{
	  char* str=(char*)m.pointerParameter;
	  String txt (str);//String((char*)m.pointerParameter)
	  XmlDocument doc (txt);
	  XmlElement* xml=doc.getDocumentElement();
	  std::cout << "Got a PlotterAddXmlPoints message,"
		    << " str=" << str << "\n";
	  if (xml)
	    std::cout << "XML=" << xml->createDocument(String::empty, true, false, T("UTF-8")).toUTF8() << "\n";
	  if (xml && xml->hasTagName(T("points")))
	    {
	      window->plotter->getFocusLayer()->addXmlPoints(xml);
	      window->plotter->repaint();
	      delete xml;
	    }
	  else
	    {
	      String err=T(">>> Error ");
	      if (!xml)
		err << doc.getLastParseError() << T("\n");
	      else
		{
		  err << T("invalid xml plot data\n");
		  delete xml;
		}
	      Console::getInstance()->printError(err);
	    }
	  delete str;
	}
      break;
    default:
      break;
    } 
}

/*=======================================================================*
                              FileIO and Exporting
 *=======================================================================*/

String PlotterWindow::toXmlString()
{
  String text=String::empty;
  text << T("<plot title=") << getName().quoted() << T(">\n") ;
  // output axis definitions
  text << T("  <fields>\n");
  for (int i=0; i<plotter->numFields(); i++)
    {
      Axis* a=plotter->getFieldAxis(i);
      text << T("    ")
	   << T("<field")
           << T(" name=") << plotter->getFieldName(i).quoted()
	   << T(" axis=") ;
      if (plotter->isSharedField(i))
	text << plotter->getSharedFieldName(i).quoted();
      else
	text << a->toString().quoted();
      text << T("/>\n");
    }
  text << T("  </fields>\n");
  text << T("  <layers>\n");
  for (int i=0; i<plotter->numLayers(); i++)
    text << T("    ")
	 << plotter->getLayer(i)->toString(TextIDs::Xml, 2, false, 0xFF);
  text << T("\n");
  text << T("  </layers>\n");
  text<<T("</plot>\n");
  return text;
}

String Layer::toString(int exportid, int decimals,
		       bool asrecords, int parammask) 
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
  else if (exportid==TextIDs::Sal)
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
  LayerPoint* point;
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

/*=======================================================================*

                             Plotting Dialogs

 *=======================================================================*/


static bool isNumberText(String num)
{
  int dots=0;
  int sign=0;
  int digi=0;
  int size=num.length();
  for (int i=0; i<size; i++)
    {
      if (num[i]==T('-')) 
	if (i==0) sign=1;
	else return false; // bad sign
      else if (num[i]==T('.'))
	if (dots==0) dots++;
	else return false; // too many dots
      else if (num[i]<T('0') || num[i]>T('9')) 
	return false;
      else digi++;
    }
  return digi>0;
}

class ExportPointsDialog : 
  public Component, public ButtonListener, public ComboBoxListener
{
 public:
  Plotter* plotter;
  int numfields;
  bool* include;
  Label* exportlabel;
  ComboBox* exportmenu;
  Label* tolabel;
  ComboBox* tomenu;
  TextButton* fieldsbutton;
  Label* formatlabel;
  Label* valuelabel;
  Label* destlabel;
  ComboBox* valuemenu;
  ComboBox* formatmenu;
  ComboBox* destmenu;
  TextButton* exportbutton;
  ExportPointsDialog(Plotter* plotter);
  ~ExportPointsDialog();
  void resized();
  void buttonClicked (Button* button);
  void comboBoxChanged (ComboBox* combobox);
  void exportPoints();
  void exportPlot();
};

ExportPointsDialog::ExportPointsDialog (Plotter* p)
    : exportlabel (0),
      exportmenu (0),
      tolabel (0),
      tomenu (0),
      fieldsbutton (0),
      formatlabel (0),
      formatmenu (0),
      valuelabel (0),
      valuemenu (0),
      destlabel (0),
      destmenu (0),
      exportbutton (0),
      plotter(0),
      include(0)
{
  plotter=p;
  numfields=plotter->numFields();
  include=new bool[numfields];

  for (int i=0;i<numfields; i++) include[i]=true;

  Font font=Font (15.0000f, Font::plain);
  addAndMakeVisible(exportlabel = new Label(String::empty, T("Export:")));
  exportlabel->setFont(font);

  addAndMakeVisible (exportmenu = new ComboBox (String::empty));
  exportmenu->setEditableText (false);
  exportmenu->addItem (T("Points"), 1);
  exportmenu->addItem (T("Plot"), 2);
  exportmenu->setSelectedId(1);
  exportmenu->addListener(this);

  addAndMakeVisible(tolabel=new Label(String::empty, T("Syntax:")));
  tolabel->setFont (font);

  addAndMakeVisible(tomenu = new ComboBox (String::empty));
  tomenu->setEditableText(false);
  tomenu->addItem(T("Lisp"), TextIDs::Lisp);
  tomenu->addItem(T("SAL"), TextIDs::Sal);
  tomenu->addItem(T("XML"), TextIDs::Xml);
  tomenu->setSelectedId(TextIDs::Lisp);

  addAndMakeVisible(fieldsbutton = new TextButton (String::empty));
  fieldsbutton->setButtonText(T("Fields..."));
  fieldsbutton->addButtonListener(this);

  addAndMakeVisible(formatlabel = new Label(String::empty, T("Format:")));
  formatlabel->setFont(font);

  addAndMakeVisible(formatmenu = new ComboBox(String::empty));
  formatmenu->setEditableText (false);
  formatmenu->addItem(T("Envelope List"), 1);
  formatmenu->addItem(T("Point Records"), 2);
  formatmenu->setSelectedId(1);

  addAndMakeVisible(valuelabel=new Label(String::empty, 
					 T("Precision:")));
  addAndMakeVisible(valuemenu = new ComboBox(String::empty));
  valuemenu->addItem(T("Integer"), 1);
  valuemenu->addItem(T("0.0"), 2);
  valuemenu->addItem(T("0.00"), 3);
  valuemenu->addItem(T("0.000"), 4);
  valuemenu->setSelectedId(3);

  addAndMakeVisible(destlabel=new Label(String::empty, 
					 T("Destination:")));
  addAndMakeVisible(destmenu = new ComboBox(String::empty));
  destmenu->addItem(T("New Edit Window"), 1);
  destmenu->addItem(T("Current Edit Window"), 2);
  destmenu->addItem(T("Clipboard"), 3);
  destmenu->setSelectedId(1);

  addAndMakeVisible(exportbutton = new TextButton(String::empty));
  exportbutton->setButtonText(T("Export"));
  exportbutton->addButtonListener(this);
  setSize(440, 140);
}

ExportPointsDialog::~ExportPointsDialog()
{
  delete[] include;
  deleteAndZero (exportlabel);
  deleteAndZero (formatlabel);
  deleteAndZero (valuelabel);
  deleteAndZero (exportbutton);
  deleteAndZero (tolabel);
  deleteAndZero (tomenu);
  deleteAndZero (fieldsbutton);
  deleteAndZero (valuemenu);
  deleteAndZero (formatmenu);
  deleteAndZero (exportmenu);
  deleteAndZero (destlabel);
  deleteAndZero (destmenu);
}

void ExportPointsDialog::resized()
{
  exportlabel->setBounds (16, 16, 56, 24);
  exportmenu->setBounds (76, 16, 88, 24);
  tolabel->setBounds (176, 16, 34+16, 24);
  tomenu->setBounds (210+16, 16, 80, 24);
  fieldsbutton->setBounds (304+16, 16, 120-16, 26);
  formatlabel->setBounds (16, 56, 56, 24);
  formatmenu->setBounds (77, 56, 150, 24);
  valuelabel->setBounds (246+24, 56, 92, 24);
  valuemenu->setBounds (342, 56, 80, 24);
  exportbutton->setBounds (274, 96, 150, 24);
  destlabel->setBounds (16, 96, 100, 24);
  destmenu->setBounds (77+24, 96, 150+8, 24);
}

void ExportPointsDialog::exportPlot() 
{
  PlotterWindow* p=(PlotterWindow*)plotter->getTopLevelComponent();
  String text=p->toXmlString();
  int destination=destmenu->getSelectedId();
  if (destination==1) // to new edit window
    new TextEditorWindow(File::nonexistent, text, TextIDs::Xml);
  else if (destination==2) // to existing edit window
    {
      TextEditorWindow* e=TextEditorWindow::getFocusTextEditor();
      if (e)
	e->getTextBuffer()->insertTextAtCursor(text);
      else
	new TextEditorWindow(File::nonexistent, text, TextIDs::Xml);
    }
  else if (destination==3) // to clipboard
    SystemClipboard::copyTextToClipboard(text);
}

void ExportPointsDialog::exportPoints() 
{
  bool layerexport=true; //(exportmenu->getSelectedId()==1);
  int exportid=tomenu->getSelectedId();
  int decimals=valuemenu->getSelectedId()-1;
  bool asrecords=(formatmenu->getSelectedId()==2);
  int destination=destmenu->getSelectedId();
  int numparams=0;
  int parammask=0;
  
  // turn included fields into bitmask
  for (int i=0; i<numfields; i++) 
    if ( include[i] )
      {
	parammask += 1<<i;
	numparams++;
      }
  // do nothing if user deselected all fields!
  if (numparams==0)
    return;
  
  String text=String::empty;
  if (layerexport)
    text=plotter->getFocusLayer()->toString(exportid, decimals,
					    asrecords, parammask);
  else
    {
      for (int i=0; i<plotter->numLayers(); i++)
	text << plotter->getFocusLayer()->toString(exportid, decimals,
						   asrecords, parammask);
    }
  if (destination==1) // to new edit window
    new TextEditorWindow(File::nonexistent, text, exportid);
  else if (destination==2) // to existing edit window
    {
      TextEditorWindow* w=TextEditorWindow::getFocusTextEditor();
      if (w)
	w->getTextBuffer()->insertTextAtCursor(text);
      else
	new TextEditorWindow(File::nonexistent, text, exportid);
    }
  else if (destination==3) // to clipboard
    SystemClipboard::copyTextToClipboard(text);
}

void ExportPointsDialog::buttonClicked (Button* button)
{
  if (button == exportbutton)
    {
      if (exportmenu->getSelectedId()==1)
	exportPoints();
      else
	exportPlot();

      DialogWindow* dw=findParentComponentOfClass((DialogWindow*) 0);
      if (dw != 0)
	dw->exitModalState(true);
    }
  else if (button == fieldsbutton)
    {
       int i;
       PopupMenu m;
       for (i=0; i<numfields; i++)
	 m.addItem(i+1, plotter->getFieldName(i),
		   true, include[i]);
       i=m.showAt(button);
       if (i != 0) include[i-1]=(!include[i-1]);
    }
}

void ExportPointsDialog::comboBoxChanged(ComboBox* cbox)
{
  if (cbox==exportmenu)
    {
      int id=cbox->getSelectedId();
      if (id==1) // Layer
	{
	  tomenu->setEnabled(true);
	  fieldsbutton->setEnabled(true);
	  formatmenu->setEnabled(true);
	  valuemenu->setEnabled(true);
	}
      else // Plot
	{
	  tomenu->setEnabled(false);
	  fieldsbutton->setEnabled(false);
	  formatmenu->setEnabled(false);
	  valuemenu->setEnabled(false);
	}
    }
  else
    {
    }      
}

void PlotterWindow::openExportDialog ()
{
  DialogWindow::showModalDialog(T("Export Plot"),
				new ExportPointsDialog(plotter),
				this,
				Colour(0xffe5e5e5),
				true);
}

/*=======================================================================*
                              Layer Dialog
 *=======================================================================*/

class LayerDialog  : public Component,
                     public ComboBoxListener,
                     public ButtonListener,
                     public ChangeListener
{
private:
  Plotter* plotter;
public:
  LayerDialog (Plotter* pl);
  ~LayerDialog();
  void resized();
  void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
  void buttonClicked (Button* buttonThatWasClicked);
  void changeListenerCallback(void*);
private:
  Label* namelabel;
  TextEditor* namebuffer;
  Label* stylelabel;
  ComboBox* stylemenu;
  TextButton* colorbutton;
  // (prevent copy constructor and operator= being generated..)
  LayerDialog (const LayerDialog&);
  const LayerDialog& operator= (const LayerDialog&);
};

LayerDialog::LayerDialog (Plotter* pl)
  : namelabel (0),
    namebuffer (0),
    stylelabel (0),
    stylemenu (0),
    colorbutton (0),
    plotter (0)
{
  plotter=pl;
  Layer* layer=plotter->getFocusLayer();
  addAndMakeVisible (namelabel = new Label (String::empty,
					    T("Name:")));
  namelabel->setFont (Font (15.0000f, Font::plain));
  namelabel->setJustificationType (Justification::centredLeft);
  namelabel->setEditable (false, false, false);
  namelabel->setColour (TextEditor::textColourId, Colours::black);
  namelabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

  addAndMakeVisible (namebuffer = new TextEditor (String::empty));
  namebuffer->setMultiLine (false);
  namebuffer->setReturnKeyStartsNewLine (false);
  namebuffer->setReadOnly (false);
  namebuffer->setScrollbarsShown (true);
  namebuffer->setCaretVisible (true);
  namebuffer->setPopupMenuEnabled (true);
  namebuffer->setText (layer->getLayerName());
  
  addAndMakeVisible (stylelabel = new Label (String::empty,
                                               T("Style:")));
  stylelabel->setFont (Font (15.0000f, Font::plain));
  stylelabel->setJustificationType (Justification::centredLeft);
  stylelabel->setEditable (false, false, false);
  stylelabel->setColour (TextEditor::textColourId, Colours::black);
  stylelabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible(stylemenu = new ComboBox (String::empty));
  stylemenu->setEditableText(false);
  stylemenu->setJustificationType(Justification::centredLeft);
  stylemenu->addItem(T("envelope"), Layer::lineandpoint);
  stylemenu->addItem(T("line"), Layer::line);
  stylemenu->addItem(T("point"), Layer::point);
  stylemenu->addItem(T("impulse"), Layer::impulse);
  stylemenu->addItem(T("histogram"), Layer::histogram);
  stylemenu->addItem(T("hbox"), Layer::hbox);
  stylemenu->addItem(T("vbox"), Layer::vbox);
  if (plotter->numFields()<=2)
    {
      stylemenu->setItemEnabled(Layer::hbox, false);
      stylemenu->setItemEnabled(Layer::vbox, false);
    } 
  stylemenu->setSelectedId(layer->getLayerStyle());
  stylemenu->addListener (this);

  addAndMakeVisible(colorbutton = new TextButton(String::empty));
  colorbutton->setButtonText(T("Color..."));
  colorbutton->addButtonListener(this);
  setSize(476, 76);
}

LayerDialog::~LayerDialog()
{
  deleteAndZero(namelabel);
  deleteAndZero(namebuffer);
  deleteAndZero(stylelabel);
  deleteAndZero(stylemenu);
  deleteAndZero(colorbutton);
}

void LayerDialog::resized()
{
  namelabel->setBounds(8, 24, 48, 24);
  namebuffer->setBounds(56, 24, 120, 24);
  stylelabel->setBounds(184, 24, 48, 24);
  stylemenu->setBounds(228, 24, 120, 24);
  colorbutton->setBounds(360, 24, 104, 24);
}

void LayerDialog::comboBoxChanged (ComboBox* cb)
{
  if (cb == stylemenu)
    {
      plotter->getFocusLayer()->setLayerStyle(cb->getSelectedId());
      plotter->redrawPlotView();
    }
}

void LayerDialog::buttonClicked (Button* buttonThatWasClicked)
{
  if (buttonThatWasClicked == colorbutton)
    {
      ColourSelector sel;
      sel.setCurrentColour(plotter->getFocusLayer()->getLayerColor());
      sel.setSize(200, 300);
      sel.addChangeListener(this);
      DialogWindow::showModalDialog(T("Layer Color"),
				    &sel, 
				    this,
				    Colour(0xffe5e5e5),
				    false);
    }
}

void LayerDialog::changeListenerCallback (void* source)
{
  ColourSelector* cs = (ColourSelector*)source;
  plotter->getFocusLayer()->setLayerColor(cs->getCurrentColour());
  plotter->redrawPlotView();
}

void PlotterWindow::openLayerDialog ()
{
  DialogWindow::showModalDialog(T("Edit Layer"),
				new LayerDialog(plotter),
				this,
				Colour(0xffe5e5e5),
				false);
}

/*=======================================================================*
                              Axis Dialog
 *=======================================================================*/

class AxisDialog  : public Component,
                    public ComboBoxListener,
                    public TextEditorListener
{
private:
  Plotter* plotter;
  bool ishorizontal;
  AxisView* axisview;
  enum {setfrom=1,setto,setby,setticks,setdecimals};
  void setAxisValue(int field, double value, bool trig);
  void updateFields(Axis* ax);
  void updateAxis();
  // (prevent copy constructor and operator= being generated..)
  AxisDialog (const AxisDialog&);
  const AxisDialog& operator= (const AxisDialog&);
public:
  AxisDialog (Plotter* pl, int orient);
  ~AxisDialog();
  void resized();
  void comboBoxChanged(ComboBox* combo);
  void textEditorReturnKeyPressed(TextEditor& editor);
  void textEditorTextChanged(TextEditor& editor) {}
  void textEditorEscapeKeyPressed(TextEditor& editor) {}
  void textEditorFocusLost(TextEditor& editor) {}
private:
  Label* namelabel;
  Label* fromlabel;
  Label* tolabel;
  Label* bylabel;
  Label* typelabel;
  Label* decimalslabel;
  Label* tickslabel;
  ComboBox* typemenu;
  TextEditor* namebuffer;
  TextEditor* frombuffer;
  TextEditor* tobuffer;
  TextEditor* bybuffer;
  TextEditor* ticksbuffer;
  ComboBox* decimalsmenu;
  bool axistypechanged;
};

AxisDialog::AxisDialog (Plotter* pl, int orient)
    : namelabel (0),
      fromlabel (0),
      tolabel (0),
      bylabel (0),
      typelabel (0),
      typemenu (0),
      namebuffer (0),
      tickslabel (0),
      frombuffer (0),
      tobuffer (0),
      bybuffer (0),
      ticksbuffer (0),
      decimalslabel (0),
      decimalsmenu (0),
      axistypechanged (false)
{
  plotter=pl;
  ishorizontal=(orient==Plotter::horizontal) ? true : false;
  axisview=(ishorizontal) ? plotter->getHorizontalAxisView()
    : plotter->getVerticalAxisView();
  addAndMakeVisible(namelabel = new Label(String::empty, T("Name:")));
  namelabel->setFont (Font (15.0000f, Font::plain));
  namelabel->setJustificationType (Justification::centredLeft);
  namelabel->setEditable (false, false, false);
  namelabel->setColour (TextEditor::textColourId, Colours::black);
  namelabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible(namebuffer = new TextEditor(T("namebuf")));
  namebuffer->setMultiLine (false);
  namebuffer->setReturnKeyStartsNewLine (false);
  namebuffer->setReadOnly (false);
  namebuffer->setScrollbarsShown (true);
  namebuffer->setCaretVisible (true);
  namebuffer->setPopupMenuEnabled (true);
  namebuffer->setText (String::empty);
  namebuffer->addListener(this);

  addAndMakeVisible(fromlabel = new Label(String::empty, T("From:")));
  fromlabel->setFont (Font (15.0000f, Font::plain));
  fromlabel->setJustificationType (Justification::centredLeft);
  fromlabel->setEditable (false, false, false);
  fromlabel->setColour (TextEditor::textColourId, Colours::black);
  fromlabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible(frombuffer = new TextEditor(T("frombuf")));
  frombuffer->setMultiLine (false);
  frombuffer->setReturnKeyStartsNewLine (false);
  frombuffer->setReadOnly (false);
  frombuffer->setScrollbarsShown (true);
  frombuffer->setCaretVisible (true);
  frombuffer->setPopupMenuEnabled (true);
  frombuffer->setText (String::empty);
  frombuffer->addListener(this);

  addAndMakeVisible(tolabel = new Label(String::empty, T("To:")));
  tolabel->setFont (Font (15.0000f, Font::plain));
  tolabel->setJustificationType (Justification::centredLeft);
  tolabel->setEditable (false, false, false);
  tolabel->setColour (TextEditor::textColourId, Colours::black);
  tolabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible(tobuffer = new TextEditor(T("tobuf")));
  tobuffer->setMultiLine (false);
  tobuffer->setReturnKeyStartsNewLine (false);
  tobuffer->setReadOnly (false);
  tobuffer->setScrollbarsShown (true);
  tobuffer->setCaretVisible (true);
  tobuffer->setPopupMenuEnabled (true);
  tobuffer->setText (String::empty);
  tobuffer->addListener(this);

  addAndMakeVisible (bylabel = new Label (String::empty, T("By:")));
  bylabel->setFont (Font (15.0000f, Font::plain));
  bylabel->setJustificationType (Justification::centredLeft);
  bylabel->setEditable (false, false, false);
  bylabel->setColour (TextEditor::textColourId, Colours::black);
  bylabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (bybuffer = new TextEditor(T("bybuf")));
  bybuffer->setMultiLine (false);
  bybuffer->setReturnKeyStartsNewLine (false);
  bybuffer->setReadOnly (false);
  bybuffer->setScrollbarsShown (true);
  bybuffer->setCaretVisible (true);
  bybuffer->setPopupMenuEnabled (true);
  bybuffer->setText (String::empty);
  bybuffer->addListener(this);

  addAndMakeVisible(typelabel = new Label(String::empty, T("Type:")));
  typelabel->setFont (Font (15.0000f, Font::plain));
  typelabel->setJustificationType (Justification::centredLeft);
  typelabel->setEditable (false, false, false);
  typelabel->setColour (TextEditor::textColourId, Colours::black);
  typelabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (typemenu = new ComboBox (String::empty));
  typemenu->setEditableText (false);
  typemenu->setJustificationType (Justification::centredLeft);
  typemenu->addItem (T("unit"), Axis::normalized);
  typemenu->addItem (T("percent"), Axis::percentage);
  typemenu->addItem (T("ordinal"), Axis::ordinal);
  typemenu->addItem (T("seconds"), Axis::seconds);
  typemenu->addItem (T("note"),  Axis::keynum);
  typemenu->addItem (T("circle"), Axis::circle);
  typemenu->addItem (T("midi"), Axis::midi);
  typemenu->addItem (T("generic"), Axis::generic);
  typemenu->addListener (this);

  addAndMakeVisible(tickslabel = new Label(String::empty, T("Ticks:")));
  tickslabel->setFont (Font (15.0000f, Font::plain));
  tickslabel->setJustificationType (Justification::centredLeft);
  tickslabel->setEditable (false, false, false);
  tickslabel->setColour (TextEditor::textColourId, Colours::black);
  tickslabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible(ticksbuffer = new TextEditor(T("ticksbuf")));
  ticksbuffer->setMultiLine (false);
  ticksbuffer->setReturnKeyStartsNewLine (false);
  ticksbuffer->setReadOnly (false);
  ticksbuffer->setScrollbarsShown (true);
  ticksbuffer->setCaretVisible (true);
  ticksbuffer->setPopupMenuEnabled (true);
  ticksbuffer->setText (String::empty);
  ticksbuffer->addListener(this);
  
  addAndMakeVisible(decimalslabel=new Label(String::empty, ("Decimals:")));
  decimalslabel->setFont (Font (15.0000f, Font::plain));
  decimalslabel->setJustificationType (Justification::centredLeft);
  decimalslabel->setEditable (false, false, false);
  decimalslabel->setColour (TextEditor::textColourId, Colours::black);
  decimalslabel->setColour(TextEditor::backgroundColourId, Colour(0x0));
  
  addAndMakeVisible (decimalsmenu = new ComboBox (String::empty));
  decimalsmenu->setEditableText (false);
  decimalsmenu->setJustificationType (Justification::centredLeft);
  decimalsmenu->setTextWhenNothingSelected (String::empty);
  decimalsmenu->setTextWhenNoChoicesAvailable (T("(no choices)"));
  decimalsmenu->addItem (T("0"), 1);
  decimalsmenu->addItem (T("1"), 2);
  decimalsmenu->addItem (T("2"), 3);
  decimalsmenu->addItem (T("3"), 4);
  decimalsmenu->addListener (this);
  updateFields(axisview->getAxis());
  setSize (476, 78);
}

AxisDialog::~AxisDialog()
{
  deleteAndZero (namelabel);
  deleteAndZero (fromlabel);
  deleteAndZero (tolabel);
  deleteAndZero (bylabel);
  deleteAndZero (typelabel);
  deleteAndZero (typemenu);
  deleteAndZero (namebuffer);
  deleteAndZero (tickslabel);
  deleteAndZero (frombuffer);
  deleteAndZero (tobuffer);
  deleteAndZero (bybuffer);
  deleteAndZero (ticksbuffer);
  deleteAndZero (decimalslabel);
  deleteAndZero (decimalsmenu);
}

void AxisDialog::resized()
{
  namelabel->setBounds (8, 8, 48, 24);
  fromlabel->setBounds (8, 40, 48, 24);
  tolabel->setBounds (136, 40, 32, 24);
  bylabel->setBounds (248, 40, 24, 24);
  typelabel->setBounds (184, 8, 48, 24);
  typemenu->setBounds (232, 8, 96, 24);
  namebuffer->setBounds (56, 8, 120, 24);
  tickslabel->setBounds (352, 40, 48, 24);
  frombuffer->setBounds (56, 40, 56, 24);
  tobuffer->setBounds (168, 40, 56, 24);
  bybuffer->setBounds (280, 40, 56, 24);
  ticksbuffer->setBounds (408, 40, 56, 24);
  decimalslabel->setBounds (336, 8, 72, 24);
  decimalsmenu->setBounds (408, 8, 55, 24);
}

void AxisDialog::updateFields(Axis* ax)
{
  namebuffer->setText(String(ax->getName()), false);
  frombuffer->setText(String(ax->getMinimum()), false);
  tobuffer->setText(String(ax->getMaximum()), false);
  bybuffer->setText(String(ax->getIncrement()), false);
  ticksbuffer->setText(String(ax->getTicks()), false);
  decimalsmenu->setSelectedId(ax->getDecimals()+1, true);
  typemenu->setSelectedId(ax->getType(), true);
}

void AxisDialog::comboBoxChanged (ComboBox* cbox)
{
  if (cbox == typemenu)
    {
      Axis a(0);
      a.init((Axis::AxisType)cbox->getSelectedId());
      updateFields(&a);
      axistypechanged=true;
    }
  else if (cbox == decimalsmenu)
    {
      axisview->getAxis()->setDecimals(cbox->getSelectedId()-1);
      axisview->repaint();
    } 
}

void AxisDialog::textEditorReturnKeyPressed (TextEditor& editor)
{
  double val;
  Axis* axis=axisview->getAxis();
  bool redraw=false;

  // pressing return in any box after the axis type has been reset by
  // the user sends all fields!
  if (axistypechanged)
    {
      String text=namebuffer->getText();
      axis->setName(text);
      if (isNumberText(text=frombuffer->getText()))
	axis->setMinimum(text.getDoubleValue());
      if (isNumberText(text=tobuffer->getText()))
	axis->setMaximum(text.getDoubleValue());
      if (isNumberText(text=bybuffer->getText()))
	axis->setIncrement(text.getDoubleValue());
      if (isNumberText(text=ticksbuffer->getText()))
	axis->setTicks(text.getIntValue());
      axis->setDecimals(decimalsmenu->getSelectedId()-1);
      redraw=true;
      axistypechanged=false;
    }
  else if (editor.getName()==T("namebuf"))
    {
      axis->setName(editor.getText());
    }
  else if (editor.getName()==T("frombuf"))
    {
      val=editor.getText().getDoubleValue();
      if (val<axis->getMaximum())
	{
	  axis->setMinimum(val);
	  redraw=true;
	}
      else
	editor.setText(String(axis->getMinimum()), true);
    }
  else if (editor.getName()==T("tobuf"))
    {
      val=editor.getText().getDoubleValue();
      if (val>axis->getMinimum())
	{
	  axis->setMaximum(val);
	  redraw=true;
	}
      else
	editor.setText(String(axis->getMaximum()), true);
    } 
  else if (editor.getName()==T("bybuf"))
    {
      val=editor.getText().getDoubleValue();
      if (val>0.0)
	{
	  axis->setIncrement(val);
	  redraw=true;
	}
      else
	editor.setText(String(axis->getIncrement()), true);
    } 
  else if (editor.getName()==T("ticksbuf"))
    {
      int num=editor.getText().getIntValue();
      if (num>=0)
	{
	  axis->setTicks(num);
	  redraw=true;
	}
      else
	editor.setText(String(axis->getTicks()), true);
    } 
  if (redraw)
    {
      axisview->repaint();
      plotter->plotview->resizeForDrawing();
    }
}

void PlotterWindow::openAxisDialog (int orient)
{
  DialogWindow::showModalDialog(T("Edit Axis"),
				new AxisDialog(plotter, orient),
				this,
				Colour(0xffe5e5e5),
				false);
}

/*=======================================================================*
                              Sonify Plot Dialog
 *=======================================================================*/

class PlayPlotDialog : public Component,
			 public SliderListener,
			 public ButtonListener
{
public:
  PlayPlotDialog (Plotter* pl);
  ~PlayPlotDialog();
  void resized();
  void sliderValueChanged (Slider* sliderThatWasMoved);
  void buttonClicked (Button* buttonThatWasClicked);
  static void openPlayPlotDialog();
private:
  bool rescalex, rescaley;
  Plotter* plotter;
  GroupComponent* xgroup;
  GroupComponent* ygroup;
  GroupComponent* ogroup;
  GroupComponent* pgroup;
  GroupComponent* fgroup;
  Label* startlabel;
  Slider* startinc;
  Label* durlabel;
  Slider* durinc;
  Label* lowkeylabel;
  Slider* lowkeyinc;
  Label* highkeylabel;
  Slider* highkeyinc;
  Label* amplabel;
  Slider* ampinc;
  Label* chanlabel;
  Slider* chaninc;
  ToggleButton* layerbutton;
  TextButton* playbutton;
  TextButton* hushbutton;
  TextButton* writebutton;
  FilenameComponent* filebrowser;
  void playPlot(bool write);
};

PlayPlotDialog::PlayPlotDialog (Plotter* pl)
  :  plotter (0),
     rescalex(true),
     rescaley(true),
     xgroup (0),
     ygroup (0),
     ogroup (0),
     pgroup (0),
     fgroup (0),
     startlabel (0),
     startinc (0),
     durlabel (0),
     durinc (0),

     lowkeylabel (0),
     lowkeyinc (0),
     highkeyinc (0),
     highkeylabel (0),
     amplabel (0),
     ampinc (0),
     chanlabel (0),
     chaninc (0),
     layerbutton (0),
     playbutton (0),
     hushbutton (0),
     filebrowser (0),
     writebutton (0)
{
  plotter=pl;
  Slider::SliderStyle ss=Slider::LinearHorizontal;

  xgroup=new GroupComponent(String::empty, T("X Axis (seconds)"));
  addAndMakeVisible(xgroup);
  Axis* axis=plotter->getHorizontalAxisView()->getAxis();
  addAndMakeVisible(startlabel=new Label(String::empty,T("Play Length:")));
  startlabel->setFont (Font (15.0000f, Font::plain));
  startlabel->setJustificationType (Justification::centredLeft);
  startlabel->setEditable (false, false, false);
  startlabel->setColour (TextEditor::textColourId, Colours::black);
  startlabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

  addAndMakeVisible(startinc = new Slider (String::empty));
  startinc->setSliderStyle(ss);
  startinc->setPopupMenuEnabled(true);
  if (axis->getType()==Axis::seconds)
    startinc->setRange(1, axis->getMaximum()-axis->getMinimum(), .1);
  else
    startinc->setRange(1, 10, .1);
  startinc->setTextBoxStyle(Slider::TextBoxLeft, false, 80, 20);
  startinc->addListener(this);
  
  addAndMakeVisible(durlabel=new Label(String::empty, T("Note Duration:")));
  durlabel->setFont (Font (15.0000f, Font::plain));
  durlabel->setJustificationType (Justification::centredLeft);
  durlabel->setEditable (false, false, false);
  durlabel->setColour (TextEditor::textColourId, Colours::black);
  durlabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (durinc = new Slider (String::empty));
  durinc->setRange (0, 10, .05);
  durinc->setValue(.5);
  durinc->setSliderStyle (ss);
  durinc->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
  durinc->addListener (this);
  if (axis->getType()==Axis::seconds)
    {
      startlabel->setEnabled(false);
      startinc->setEnabled(false);
      durlabel->setEnabled(false);
      durinc->setEnabled(false);
      rescalex=false;
    }  

  // Y axis group
  ygroup=new GroupComponent(String::empty, T("Y Axis (key numbers)"));
  addAndMakeVisible(ygroup);
  axis=plotter->getVerticalAxisView()->getAxis();

  addAndMakeVisible(lowkeylabel=new Label(String::empty, T("Lowest note:")));
  lowkeylabel->setFont (Font (15.0000f, Font::plain));
  lowkeylabel->setJustificationType (Justification::centredLeft);
  lowkeylabel->setEditable (false, false, false);
  lowkeylabel->setColour (TextEditor::textColourId, Colours::black);
  lowkeylabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (lowkeyinc = new Slider(String::empty));
  lowkeyinc->setRange (0, 127, 1);
  lowkeyinc->setValue(0);
  lowkeyinc->setSliderStyle(ss);
  lowkeyinc->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
  lowkeyinc->addListener (this);
  
  addAndMakeVisible(highkeylabel=new Label(String::empty, T("Highest note:")));
  highkeylabel->setFont (Font (15.0000f, Font::plain));
  highkeylabel->setJustificationType (Justification::centredLeft);
  highkeylabel->setEditable (false, false, false);
  highkeylabel->setColour (TextEditor::textColourId, Colours::black);
  highkeylabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

  addAndMakeVisible (highkeyinc = new Slider(String::empty));
  highkeyinc->setRange (0, 127, 1);
  highkeyinc->setValue(127);
  highkeyinc->setSliderStyle(ss);
  highkeyinc->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
  highkeyinc->addListener (this);
  if (axis->getType()==Axis::keynum)
    {
      lowkeylabel->setEnabled(false);
      lowkeyinc->setEnabled(false);
      highkeylabel->setEnabled(false);
      highkeyinc->setEnabled(false);
      rescaley=false;
    }

  // Amplitude
  addAndMakeVisible(amplabel=new Label(String::empty, T("Amplitude:")));
  amplabel->setFont (Font (15.0000f, Font::plain));
  amplabel->setJustificationType (Justification::centredLeft);
  amplabel->setEditable (false, false, false);
  amplabel->setColour (TextEditor::textColourId, Colours::black);
  amplabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

  addAndMakeVisible(ampinc=new Slider(String::empty));
  ampinc->setRange (0, 1.0, 0.05);
  ampinc->setValue(.5);
  ampinc->setSliderStyle(ss);
  ampinc->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
  ampinc->addListener (this);
  
  // Channel
  addAndMakeVisible(chanlabel=new Label(String::empty, T("Channel:")));
  chanlabel->setFont (Font (15.0000f, Font::plain));
  chanlabel->setJustificationType (Justification::centredLeft);
  chanlabel->setEditable (false, false, false);
  chanlabel->setColour (TextEditor::textColourId, Colours::black);
  chanlabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible(chaninc=new Slider(String::empty));
  chaninc->setRange (0, 15, 1);
  chaninc->setSliderStyle(ss);
  chaninc->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
  chaninc->addListener (this);
  
  addAndMakeVisible(layerbutton=new ToggleButton(String::empty));
  layerbutton->setButtonText (T("All Layers"));
  layerbutton->setToggleState(true,false);
  layerbutton->addButtonListener (this);

  addAndMakeVisible(playbutton=new TextButton(String::empty));
  playbutton->setButtonText (T("Play"));
  playbutton->setEnabled(MidiOutPort::getInstance()->isOpen());
  playbutton->addButtonListener(this);
  addAndMakeVisible(hushbutton=new TextButton(String::empty));
  hushbutton->setButtonText (T("Hush"));
  hushbutton->setEnabled(MidiOutPort::getInstance()->isOpen());
  hushbutton->addButtonListener (this);

  addAndMakeVisible(writebutton=new TextButton(String::empty));
  writebutton->setButtonText(T("Write"));
  writebutton->addButtonListener(this);
  File path=completeFile(plotter->getPlotTitle()+T(".mid"));
  filebrowser=new FilenameComponent(String::empty,
				    path,
				    true,
				    false,
				    true,
				    T("*.mid"),
				    T(".mid"),
				    String::empty);
  addAndMakeVisible(filebrowser);
  setSize (550, 300);
}

PlayPlotDialog::~PlayPlotDialog()
{
  deleteAndZero (xgroup);
  deleteAndZero (ygroup);
  deleteAndZero (ogroup);
  deleteAndZero (pgroup);
  deleteAndZero (fgroup);
  deleteAndZero (startlabel);
  deleteAndZero (startinc);
  deleteAndZero (durlabel);
  deleteAndZero (durinc);
  deleteAndZero (lowkeylabel);
  deleteAndZero (lowkeyinc);
  deleteAndZero (highkeylabel);
  deleteAndZero (highkeyinc);
  deleteAndZero (amplabel);
  deleteAndZero (ampinc);
  deleteAndZero (chanlabel);
  deleteAndZero (chaninc);
  deleteAndZero (layerbutton);
  deleteAndZero (playbutton);
  deleteAndZero (hushbutton);
  deleteAndZero (filebrowser);
  deleteAndZero (writebutton);
}

void PlayPlotDialog::resized()
{
  int slwidth=138;
  int labelwidth=90;
  int slcol1=120;
  int slcol2=380;

  xgroup->setBounds (16, 8, 520, 64);
  startlabel->setBounds (32, 32, labelwidth, 24);
  startinc->setBounds (slcol1, 32, slwidth, 24);
  durlabel->setBounds (288, 32, labelwidth, 24); //72
  durinc->setBounds (380, 32, slwidth, 24); //(368, 32, 150, 24)
  ygroup->setBounds (16, 80, 520, 64);
  lowkeylabel->setBounds (32, 104, labelwidth, 24);
  lowkeyinc->setBounds (slcol1, 104, slwidth, 24);
  highkeylabel->setBounds (288, 104, labelwidth, 24);
  highkeyinc->setBounds (slcol2, 104, slwidth, 24);
  amplabel->setBounds (32, 160, labelwidth, 24);
  ampinc->setBounds (slcol1, 160, slwidth, 24);
  chanlabel->setBounds (288, 160, labelwidth, 24);
  chaninc->setBounds (slcol2, 160, slwidth, 24);
  layerbutton->setBounds (32, 200, 120, 24);
  filebrowser->setBounds (32, 240, 396, 24);
  writebutton->setBounds (440, 240, 87, 24);

  playbutton->setBounds (440, 280, 87, 24);
  hushbutton->setBounds (344, 280, 87, 24);


}

void PlayPlotDialog::sliderValueChanged (Slider* slider)
{
  if (slider == startinc)
    {
    }
  else if (slider == durinc)
    {
    }
  else if (slider == lowkeyinc)
    {
    }
  else if (slider == highkeyinc)
    {
    }
  else if (slider == ampinc)
    {
    }
  else if (slider == chaninc)
    {
    }
}

void PlayPlotDialog::buttonClicked (Button* button)
{
  if (button == playbutton)
    {
      playPlot(false);
    }
  else if (button == writebutton)
    {
      playPlot(true);
    }
  else if (button == hushbutton)
    {
      MidiOutPort::getInstance()->clear();
    }
  else if (button == layerbutton)
    {
    }
}

void PlayPlotDialog::playPlot(bool write)
{
  double len=startinc->getValue();
  double dur=durinc->getValue();
  double amp=ampinc->getValue();
  int chan=chaninc->getValue();
  double key1=lowkeyinc->getValue();
  double key2=highkeyinc->getValue();
  Axis* axis=plotter->getHorizontalAxisView()->getAxis();
  double xmin=axis->getMinimum();
  double xmax=axis->getMaximum();
  axis=plotter->getVerticalAxisView()->getAxis();  
  double ymin=axis->getMinimum();
  double ymax=axis->getMaximum();

  if (write)
    MidiOutPort::getInstance()->clearSequence();
  for (int i=0;i<plotter->numLayers(); i++)
    {
      Layer* l=plotter->getLayer(i);
      if (layerbutton->getToggleState() || plotter->isFocusLayer(l))
	{
	  // only access a z value if arity>2 and hbox style
	  bool getz=(!rescalex && l->getLayerArity()>2 &&
		     l->isDrawStyle(Layer::hbox));
	  for (int j=0; j<l->numPoints(); j++)
	    {
	      LayerPoint* p=l->getPoint(j);
	      double x, z;
	      double y=l->getPointY(p);
	      if (rescalex) 
		{
		  x=cm_rescale(l->getPointX(p),xmin,xmax,0,len,1) ;
		  z=dur;
		}
	      else
		{
		  x=l->getPointX(p);
		  z=(getz) ? l->getPointZ(p) : dur;
		}
	      if (rescaley)
		y=cm_rescale(y,ymin,ymax,key1,key2,1);
	      MidiOutPort::getInstance()->sendNote(x,z,y,amp,chan,write);
	    }
	}
    }
  if (write)
    {
      String path=filebrowser->getCurrentFile().getFullPathName();
      MidiOutPort::getInstance()->setOutputFile(path);
      MidiOutPort::getInstance()->saveSequence(false);
    }
}

class PlayPlotWindow : public DocumentWindow 
{
public:
  PlayPlotWindow(PlotterWindow* win)
    : DocumentWindow(String::empty, Colour(0xffe5e5e5),
		     DocumentWindow::closeButton, true)
  {
    PlayPlotDialog* comp=new PlayPlotDialog(win->plotter);
    setName(T("Play ")+win->getName());
    setContentComponent(comp,true,true);
    setUsingNativeTitleBar(true);
    setDropShadowEnabled(true);
    setVisible(true);
    centreAroundComponent(win->plotter, getWidth(), getHeight());
  }
  ~PlayPlotWindow()
  {
  }
  void closeButtonPressed()
  {
    delete this;
  }
};

void PlotterWindow::openPlayPlotDialog ()
{
  new PlayPlotWindow(this);
  /*
  DialogWindow::showModalDialog(T("Play ")+getName(),
				new PlayPlotDialog(plotter),
				this,
				Colour(0xffe5e5e5),
				false);
  */
}

/*=======================================================================*
                              Edit Point Dialog
 *=======================================================================*/

class EditPointsDialog : public Component, 
			public LabelListener
{
private:
  Plotter* plotter;
  OwnedArray<Label> labels;
  OwnedArray<Label> editors;
  enum{labelwidth=80, editorwidth=120, lineheight=24, margin=8};
  int getFieldIndex(String name)
  {
    for (int i=0; i<editors.size(); i++)
      if (editors[i]->getName()==name) return i;
    return -1;
  }
public:
  EditPointsDialog (Plotter* plotr);
  ~EditPointsDialog()
  {
    editors.clear();
    labels.clear();
  }
  void resized();
  void labelTextChanged(Label *label);
};

EditPointsDialog::EditPointsDialog(Plotter* plotr)
{
  plotter=plotr;
  StringArray fields;
  plotter->getFieldNames(fields);
  LayerPoint* p=(plotter->getPlotView()->numSelected()==1)
    ? plotter->getPlotView()->getSelected(0) : NULL ;
  for (int i=0; i<fields.size(); i++)
    {
      labels.add(new Label(String::empty, fields[i]));
      editors.add(new Label(fields[i], 
			    ((p) ? String(p->getVal(i)) : String::empty)));
      labels[i]->setFont(Font(15.0000f, Font::plain));
      editors[i]->setFont(Font(15.0000f, Font::plain));
      editors[i]->setEditable(true, false, true);
      editors[i]->setColour(Label::outlineColourId, Colours::black);
      editors[i]->addListener(this);
      addAndMakeVisible(labels[i]);
      addAndMakeVisible(editors[i]);
    }	 
  int w=margin+labelwidth+margin+editorwidth+margin;
  int h=(fields.size()*lineheight)+((fields.size()+1)*margin);
  setVisible(true);
  setSize(w, h);
}

void EditPointsDialog::resized()
{
  int x1=margin, x2=margin+labelwidth+margin;
  int y=margin;
  for(int i=0; i<labels.size(); i++)
    {
      labels[i]->setBounds(x1, y, labelwidth, lineheight);
      editors[i]->setBounds(x2, y, editorwidth, lineheight);
      y += lineheight + margin;
    }
}

void EditPointsDialog::labelTextChanged (Label *label)
{
  int index=getFieldIndex(label->getName());
  //std::cout << "text changed for " << label->getName().toUTF8()
  //	    << " field=" << index << "\n";
  if (index<0) return;
  String text=label->getText().trim();
  if ((index>=0) && text.isNotEmpty() &&
      text.containsOnly(T("0123456789.-"))) 
    {
      double value=text.getDoubleValue();
      // FIXME: undo/redo
      for (int i=0;i<plotter->plotview->numSelected(); i++)
	plotter->plotview->getSelected(i)->setVal(index,value);
      if (plotter->getFocusLayer()->isVisibleField(index))
	plotter->plotview->repaintFocusPlot();
    }
}

void PlotterWindow::openEditPointsDialog ()
{
  DialogWindow::showModalDialog(T("Edit Points"), 
				new EditPointsDialog(plotter),
				this,
				Colour(0xffe5e5e5),
				false);
}


/*=======================================================================*
                              Rescale Points Dialog
 *=======================================================================*/

class RescalePointsDialog : public Component,
                           public ButtonListener,
			   public TextEditorListener
{
public:
  Plotter* plotter;
  int command;
  GroupComponent* axisgroup;
  ToggleButton* xbutton;
  ToggleButton* ybutton;
  Label* label1;
  TextEditor* editor1;
  Label* label2;
  TextEditor* editor2;
  static bool __yactive;
  bool isVertical(){return __yactive;}
  bool isHorizontal(){return !isVertical();}

  RescalePointsDialog (Plotter* pltr, int cmd);
  ~RescalePointsDialog();
  void resized();
  void buttonClicked (Button* buttonThatWasClicked);
  void textEditorReturnKeyPressed(TextEditor& editor);
  void textEditorTextChanged(TextEditor& editor) {}
  void textEditorEscapeKeyPressed(TextEditor& editor) {}
  void textEditorFocusLost(TextEditor& editor) {}
};

bool RescalePointsDialog::__yactive=true;

RescalePointsDialog::RescalePointsDialog (Plotter* pltr, int cmd)
  : plotter (0),
    command (0),
    axisgroup (0),
    xbutton (0),
    ybutton (0),
    label1 (0),
    editor1 (0),
    label2 (0),
    editor2 (0)
{
  plotter=pltr;
  command=cmd;
  addAndMakeVisible(axisgroup=new GroupComponent(String::empty,T("Axis")));
  
  addAndMakeVisible (xbutton = new ToggleButton (String::empty));
  xbutton->setButtonText (T("Horizontal"));
  xbutton->setRadioGroupId (1);
  xbutton->addButtonListener (this);

  addAndMakeVisible (ybutton = new ToggleButton (String::empty));
  ybutton->setButtonText (T("Vertical"));
  ybutton->setRadioGroupId (1);
  ybutton->addButtonListener (this);

  if (command==CommandIDs::PlotterShiftPoints)
    label1=new Label(String::empty, T("Amount to shift:"));
  else
    label1=new Label(String::empty, T("New minimum:"));
  addAndMakeVisible(label1);
  label1->setFont(Font (15.0000f, Font::plain));
  label1->setJustificationType(Justification::centredLeft);
  label1->setEditable(false, false, false);
  label1->setColour(TextEditor::textColourId, Colours::black);
  label1->setColour(TextEditor::backgroundColourId, Colour(0x0));
  
  addAndMakeVisible (editor1 = new TextEditor (String::empty));
  editor1->setMultiLine (false);
  editor1->setReturnKeyStartsNewLine (false);
  editor1->setReadOnly (false);
  editor1->setScrollbarsShown (true);
  editor1->setCaretVisible (true);
  editor1->setPopupMenuEnabled (true);
  editor1->setText(String::empty);
  editor1->addListener(this);

  if (command==CommandIDs::PlotterRescalePoints)
    {
      addAndMakeVisible(label2=new Label(String::empty,
					 T("New maximum:")));
      label2->setFont(Font(15.0000f, Font::plain));
      label2->setJustificationType(Justification::centredLeft);
      label2->setEditable(false, false, false);
      label2->setColour(TextEditor::textColourId, Colours::black);
      label2->setColour(TextEditor::backgroundColourId, Colour (0x0));
      
      addAndMakeVisible(editor2=new TextEditor(String::empty));
      editor2->setMultiLine(false);
      editor2->setReturnKeyStartsNewLine(false);
      editor2->setReadOnly(false);
      editor2->setScrollbarsShown(true);
      editor2->setCaretVisible(true);
      editor2->setPopupMenuEnabled(true);
      editor2->setText(String::empty);
      editor2->addListener(this);
    }
  if (isVertical())
    ybutton->setToggleState(true, true);
  else
    xbutton->setToggleState(true, true);
  if (command==CommandIDs::PlotterRescalePoints)
    setSize (272, 128);
  else
    setSize (272, 128-32);
}

RescalePointsDialog::~RescalePointsDialog()
{
  deleteAndZero (axisgroup);
  deleteAndZero (xbutton);
  deleteAndZero (ybutton);
  deleteAndZero (label1);
  deleteAndZero (editor1);
  deleteAndZero (label2);
  deleteAndZero (editor2);
}

void RescalePointsDialog::resized()
{
  axisgroup->setBounds (8, 8, 256, 48);
  xbutton->setBounds (24, 24, 96, 24);
  ybutton->setBounds (152, 24, 96, 24);
  label1->setBounds (16, 64, 112, 24);
  editor1->setBounds (136, 64, 120, 24);
  if (command==CommandIDs::PlotterRescalePoints)
    {
      label2->setBounds (16, 96, 112, 24);
      editor2->setBounds (136, 96, 120, 24);
    }
}

void RescalePointsDialog::buttonClicked (Button* button)
{
  Plotter::Orientation orient;
  if (button == xbutton)
    {
      __yactive=false;
      orient=Plotter::horizontal;
    }
  else if (button == ybutton)
    {
      __yactive=true;
      orient=Plotter::vertical;
    }
  if (command==CommandIDs::PlotterRescalePoints)
    {
      float low,high;
      plotter->plotview->getSelectionRange(orient,low,high);
      editor1->setText(String(low));
      editor2->setText(String(high));
    }
  else if (command==CommandIDs::PlotterShiftPoints)
    {
      editor1->setText(T("0.0"));
    }
}



void RescalePointsDialog::textEditorReturnKeyPressed (TextEditor& editor)
{
  String str=editor1->getText().trim();
  float num1, num2;
  if (!isNumberText(str))
    return;
  num1=str.getFloatValue();
  if (command==CommandIDs::PlotterShiftPoints)
    {
      if (isVertical())
	plotter->plotview->shiftSelection(Plotter::vertical, num1);
      else
	plotter->plotview->shiftSelection(Plotter::horizontal, num1);
    }
  else if (command==CommandIDs::PlotterRescalePoints)
    {
      str=editor2->getText().trim();
      if (!isNumberText(str))
	return;
      num2=str.getFloatValue();
      if (isVertical())
	plotter->plotview->rescaleSelection(Plotter::vertical, 
					    num1, num2);
      else
	plotter->plotview->rescaleSelection(Plotter::horizontal, 
					    num1, num2);
    }   
}

void PlotterWindow::openRescalePointsDialog (int cmd)
{
  String title=String::empty;
  if (cmd==CommandIDs::PlotterRescalePoints)
    title=T("Rescale Points");
  else if (cmd==CommandIDs::PlotterShiftPoints)
    title=T("Shift Points");
  RescalePointsDialog* dialog=new RescalePointsDialog(plotter, cmd);
  DialogWindow::showModalDialog(title, dialog, this,
				Colour(0xffe5e5e5), false);
  delete dialog;
}

