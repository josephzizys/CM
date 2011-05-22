/*=======================================================================*
  Copyright (c) 2011 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify
  it under the terms of the Lisp Lesser Gnu Public License. The text
  of this agreement is available at http://www.cliki.net/LLGPL
 *=======================================================================*/

#include "Enumerations.h"
#include "Menus.h"
#include "Console.h"
#include "CodeEditor.h"
#include "Plot.h"
#include "Midi.h"
#include "Scheme.h"
#include "CmSupport.h"
#include "Alerts.h"
#include "PlotEditor.h"

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
  //  g.fillAll(Colours::lightyellow); // **showregion

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
      g.drawLine(0.0, (float)(height-1), (float)getWidth(), (float)(height-1), 2.0);
      
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
	  g.drawVerticalLine((int)pval, (float)(height-majortick), (float)height);
	  labl=String(aval,axis->getDecimals());
	  lwid=font.getStringWidthFloat(labl);
	  just=(int)(-lwid*(pval/width));  // twiddle label justification
	  g.setColour(tcol);
	  g.drawText(labl,(int)(pval+just),0,(int)lwid,(int)lhei, 
		     Justification::topLeft, false);
	  // draw minor ticks above each major tick
	  g.setColour(col2);
	  for (int i=1;i<numTicks();i++)
	    g.drawVerticalLine((int)(pval+(tsiz*i)), (float)(height-minortick),
			       (float)height);
	  pval+=isiz;
	  aval+=by;
	}
      // now draw any ticks left of first increment
      pval=save-tsiz;
      g.setColour(col2);
      while (pval > 0)
	{
	  g.drawVerticalLine((int)pval, (float)(height-minortick), (float)height);
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
      g.drawLine((float)(width-1), 0.0, (float)(width-1), (float)getHeight(), 2.0);

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
	  g.drawHorizontalLine((int)pval, (float)(width-majortick), (float)width);
	  labl=String(aval, axis->getDecimals());
	  lwid=font.getStringWidthFloat(labl);
	  
	  // METHOD1: justify vertically, but now the view has to be wider.
	  just=(int)(lhei*(pval/height));  // twiddle label justification
	  g.setColour(tcol);
	  g.drawText(labl,
		     (int)(width-graywidth-4-lwid),
		     (int)(pval-just),
		     (int)lwid,
		     (int)lhei,
		     Justification::topLeft,
		     false);	  
	  g.setColour(col2);
	  for (int i=1;i<numTicks();i++)
	    g.drawHorizontalLine((int)(pval-(tsiz*i)), (float)(width-minortick),
				 (float)width);
	  pval-=isiz;
	  aval+=by;
	}
      // now draw any ticks below first increment
      pval=save+tsiz;
      g.setColour(col2);
      while (pval < height) 
	{
	  g.drawHorizontalLine((int)pval, (float)(width-minortick), (float)width);
	  pval+=tsiz;
	}
    }
  g.setColour(Colours::black);
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
	       SelectedItemSet<Layer::NPoint*> * sel);

void drawGrid(Graphics& g, AxisView * haxview, AxisView * vaxview, 
	      Colour c1, Colour c2) ;

class BackView : public Component 
{
public:
  Plotter* plotter;
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
    {
      Rectangle<int> r ((int)haxview->getOrigin(),
			 (int)(vaxview->getOrigin()-vaxview->extent()),
			 (int)haxview->extent(), 
			 (int)vaxview->extent()
			);
      g.fillCheckerBoard(r, /*(int)haxview->getOrigin(),
			 (int)(vaxview->getOrigin()-vaxview->extent()),
			 (int)haxview->extent(), 
			 (int)vaxview->extent(), */
			 (int)haxview->tickSize(), 
			 (int)vaxview->tickSize(),
			 bgcolors[4],bgcolors[5]);
    }
    else g.fillAll(bgcolors[1]);

    // draw non-focus plots
    if ( isBackViewPlotting() ) {
      double psize=plotter->getPointSize();
    for (int i=0; i < plotter->numLayers(); i++) {
      layer = plotter->getLayer(i);
      if (! plotter->isFocusLayer(layer) ) 
	drawLayer(g, layer, haxview, vaxview, psize, 1.0, false, 
		  (SelectedItemSet<Layer::NPoint*> *)NULL);
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
  Plotter* plotter;
  BackView* backview;
  double pad; // pix per inc, pix per point, margin pad
  juce::Point<float> mousedown, mousemove;
  SelectedItemSet<Layer::NPoint*> selection;
  Region region;
  Layer* focuslayer; // cached focus layer for fast acesss
  
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

  bool isSelected(Layer::NPoint* p) {return selection.isSelected(p);}
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

  void removeSelection(Layer::NPoint* p) {selection.deselect(p);}
  void removeSelection(int h) {removeSelection(focuslayer->getPoint(h));}

  void setSelection(Layer::NPoint* p) ;
  void setSelection(int h) {setSelection(focuslayer->getPoint(h));}

  void addSelection(Layer::NPoint* p) {
    selection.addToSelection(p);
  }
  void addSelection(int h) {addSelection(focuslayer->getPoint(h));}

  void deleteSelection (bool cut=false) 
  {
    for (int i=0; i<numSelected(); i++)
      focuslayer->deletePoint( getSelected(i));
    repaint();
  }

  Layer::NPoint* getSelected(int i) {return selection.getSelectedItem(i);}
  int getSelectedIndex(int i) {
    return focuslayer->getPointIndex(selection.getSelectedItem(i));
  }

  void dragSelection(double x, double y);
  void shiftSelection(int orient, double delta);
  void rescaleSelection (int orient, double newlow, double newhigh);

  void getSelectionRange(int orient, double& low, double& high);
  double getSelectionMin(Plotter::Orientation orient);

  bool isInside(double x, double y, double left, double top,
		double right, double bottom);

  // this shuold be a layer method...
  void selectPointsInside(double left, double top, double right, double bottom) ;

  void printSelection() {
    printf("#<Selection:");
    for (int i=0;i<numSelected(); i++)
      printf(" %d", getSelectedIndex(i));
    printf(">\n");
  }
};

void PlotView::setSelection(Layer::NPoint* p) {
  selection.selectOnly(p);
}

double PlotView::getSelectionMin(Plotter::Orientation orient)
{
  std::numeric_limits<double> info;
  double (Layer::*getter) (Layer::NPoint* p) ;
  double lim=info.max();
  info; // keep ms compiler from complaining

  if (orient == Plotter::horizontal)
    getter = &Layer::getPointX;
  else 
    getter = &Layer::getPointY;

  for (int i = 0; i< numSelected(); i++) {
    lim=jmin( lim, (focuslayer->*getter) (  getSelected(i) ) );
  }
  return lim;
}

void PlotView::getSelectionRange(int orient, double& low, double& high)
{
  std::numeric_limits<double> info;  
  low=info.max();
  high=info.min();
  double x;
  info; // keep ms compiler from complaining

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
   
void PlotView::dragSelection(double dx, double dy) 
{
  int n=numSelected();
  for (int i=0; i<n; i++)
    focuslayer->incPoint( getSelected(i), dx, dy);
}

void PlotView::shiftSelection(int orient, double delta) 
{
  if (delta==0.0) return;
  int n=numSelected();
  Layer::NPoint* p;
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

void PlotView::rescaleSelection (int orient, double newmin, double newmax)
{
  Layer::NPoint* p;
  double oldmin, oldmax;
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
	focuslayer->setPointY(p,(double)v);
      }
    else 
    {
      for (int i=0; i<numSelected(); i++)
	{
	  p=getSelected(i);
	  v=cm_rescale(focuslayer->getPointX(p), oldmin, oldmax,
		       newmin, newmax, 1);
	  focuslayer->setPointX(p,(double)v);
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
	       SelectedItemSet<Layer::NPoint*> * sel) 
{
  double half=(ppp/2);
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
    Layer::NPoint* p = layer->getPoint(i);
    ax=layer->getPointX(p);
    ay=layer->getPointY(p);  
    px=haxview->toPixel(ax);   // pixel coords
    py=vaxview->toPixel(ay);

    if ( layer->isDrawStyle(Layer::line)  ) {
      if (layer->isDrawStyle(Layer::vertical))
	g.drawLine( (float)px, (float)oy, (float)px, (float)py); // vertical line from orign
      else if (layer->isDrawStyle(Layer::horizontal) )
	g.drawLine( (float)ox, (float)py, (float)px, (float)py); // horizontal line from origin
      else if (i>0)  // normal line between points
	g.drawLine( (float)lx, (float)ly, (float)px, (float)py);
      }

    if (layer->isDrawStyle(Layer::point)) {
      // if we are moving selection then draw selected point gray
      if ( isFoc && sel->isSelected(p) ) {
	g.setColour(selcolor);
	g.fillEllipse((float)(px-half), (float)(py-half), (float)ppp, (float)ppp);
	g.setColour(color);
      }
      else
	g.fillEllipse((float)(px-half), (float)(py-half), (float)ppp, (float)ppp);
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
  //g.fillAll(Colours::lightseagreen);  // **showregion

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
  double p,t,d;
  p=haxview->getOrigin();
  d=haxview->incrementSize();
  t=haxview->tickSize();
  while (p <= right) 
    {
      g.setColour(c1);
      g.drawVerticalLine((int)p, (float)top, (float)bottom);
      g.setColour(c2);
      for (int i=1;i<haxview->numTicks();i++) 
	g.drawVerticalLine((int)(p+(t*i)), (float)top, (float)bottom);
      p += d;
    }
  p=vaxview->getOrigin();
  d=vaxview->incrementSize();
  t=vaxview->tickSize();
  while (p >= top)
    {
      g.setColour(c1);
      g.drawHorizontalLine((int)p, (float)left, (float)right);
      g.setColour(c2);
      for (int i=1;i<vaxview->numTicks();i++) 
	g.drawHorizontalLine((int)(p-(t*i)), (float)left, (float)right);
      p -= d;
    }
  g.setColour(c1);
}

bool PlotView::isInside(double x, double y, double l, double t, double r, double b) 
{
  if ((l <= x) && (x <= r) && (b <= y) && (y <= t))
    return true;
  else 
    return false;
}

void PlotView::selectPointsInside(double l, double t, double r, double b)
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
  mousedown.setXY((float)mxp, (float)myp);
  mousemove.setXY((float)mxp, (float)myp);
  
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
	SchemeThread::getInstance()->eval(str);
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
    double dx=haxview->toValue(e.x) - haxview->toValue(mousemove.getX()) ;
    double dy=vaxview->toValue(e.y) - vaxview->toValue(mousemove.getY()) ;
    //    for (int i=0; i<numSelected(); i++)
    //      focuslayer->incPoint( getSelected(i), dx, dy);
    dragSelection(dx, dy);
    repaintFocusPlot();
    mousemove.setXY((float)e.x, (float)e.y);
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
      double l = region.minX();
      double t = region.maxY();
      double r = region.maxX();
      double b = region.minY();
      region.endSweep(e);
      selectPointsInside(l,t,r,b);
      removeChildComponent(&region);
      repaintFocusPlot();
    }
}

void PlotView::mouseDoubleClick(const MouseEvent &e)
{
  /*  PlotWindow* w=(PlotWindow*)getTopLevelComponent();
  if (isSelection()) 
    w->openEditPointsDialog();
  else
    w->openLayerDialog();
  */
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


Plotter::Plotter (XmlElement* plot) 
  : ppp (8.0),
    zoom (1.0),
    haxview (0),
    vaxview (0),
    viewport (0),
    plotview (0),
    backview (0),
    editor (0),
    pbthread (0),
    changed (false),
    playing (false),
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
  //  bool haspoints=false;
  //  for (int i=0; i<numLayers(); i++)
  //    if (getLayer(i)->isChanged())

  autosizeAxes();
  xmlfields.clear(false);
  xmlplots.clear(false);
  plotview->resizeForDrawing();  // calc plots width/height
  setUnsavedChanges(false);
}

Plotter::Plotter(MidiFile& midifile)
  : ppp (8.0),
    zoom (1.0),
    haxview (0),
    vaxview (0),
    viewport (0),
    plotview (0),
    backview (0),
    editor (0),
    pbthread (0),
    changed(false),
    playing (false),
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
	      Layer::NPoint* p=new Layer::NPoint(arity);
	      p->setVal(0,t);
	      p->setVal(1,d);
	      p->setVal(2,k);
	      p->setVal(3,a);
	      p->setVal(4,c);
	      lay->points.add(p);  // add same order as seq
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
  setUnsavedChanges(false);
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
  playbackparams[PlaybackMinKey]=0;
  playbackparams[PlaybackMaxKey]=127;
  playbackparams[PlaybackDuration]=.25;
  playbackparams[PlaybackAmplitude]=.5;
  playbackparams[PlaybackChannel]=0;
  // NB: the Plotter owns the playback thread and creates it but the
  // Editor is responsible for providing a transport, an output device
  // and starting playback.
  pbthread = new MidiPlaybackThread(this,50,60);
}

void Plotter::setPlottingFields(int xax, int yax)
{
  setHorizontalAxis(fields[xax]->axis);
  setVerticalAxis(fields[yax]->axis);
  plotview->resizeForDrawing();  // calc plots width/height
}

Plotter::~Plotter()
{
  if (pbthread->isPlaying())
    pbthread->pause();
  pbthread->stopThread(-1);
  deleteAndZero(pbthread);
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

bool Plotter::hasUnsavedChanges()
{
  if (changed)
  {
    std::cout << "plotter has unsaved changes\n";
    return true;
  }
  for (int i=0; i<numLayers(); i++)
    if (getLayer(i)->hasUnsavedChanges())
    {
      std::cout << "layer " << i << " has unsaved changes\n";
      return true;
    }
  return false;
}

void Plotter::setUnsavedChanges(bool isChanged)
{
  changed=isChanged;
  if (!isChanged)
    for (int i=0; i<numLayers(); i++)
      getLayer(i)->setUnsavedChanges(false);
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

AxisView* Plotter::getHorizontalAxisView() 
{
  return haxview;
}
AxisView* Plotter::getVerticalAxisView() 
{
  return vaxview;
}

AxisView* Plotter::getAxisView(int orient) 
{
  if (orient==horizontal) return haxview;
  if (orient==vertical) return vaxview;
  return NULL;
}

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

int Plotter::getViewportViewingHeight()
{
  return viewport->getViewHeight();
}

int Plotter::getViewportViewingWidth()
{
  return viewport->getViewWidth();
}

void Plotter::redrawPlotView() 
{
  plotview->repaint();
}

void Plotter::redrawBackView() 
{
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
	  //else if (i==3) ; // TODO!
	}
    }
  else
    layer=new Layer(num, nam, col, sty);
  addLayer(layer);
  return layer;
}

void Plotter::addLayer(Layer* layer)
{
  changed=true;
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
  changed=true;
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

Layer::NPoint* Plotter::getSelected(int i) 
{
  return getPlotView()->getSelected(i);
}

void Plotter::getSelectionRange(int orient, double& low, double& high)
{
  plotview->getSelectionRange(orient, low, high);
}

void Plotter::shiftSelection(int orient, double delta)
{
  plotview->shiftSelection(orient, delta);
}

void Plotter::rescaleSelection (int orient, double newlow, double newhigh)
{
  plotview->rescaleSelection(orient,newlow,newhigh);
}

void Plotter::deleteSelection(bool cut) 
{
  getPlotView()->deleteSelection(cut);
}

void Plotter::paint(Graphics& g) 
{
  //  g.fillAll(Colours::lightcoral);  // **showregion
}

void Plotter::resized () 
{
  static const int scrollerwidth = 20;
  viewport->setBounds(70, 50, getWidth()-80, getHeight()-60);

  std::cout << "plotter: x=" << getX() << ", y=" << getY() << ", w=" << getWidth() << " h=" << getHeight() << "\n";
  //std::cout << "viewport: x=" << viewport->getX() << ", y=" << viewport->getY() << ", w=" << viewport->getWidth() << " h=" << viewport->getHeight() << ", vw=" << viewport->getViewWidth() << " vh=" << viewport->getViewHeight() << "\n";

  // if autosizing then set axis views to the full extent of the
  // viewport so that it will not show scrollerbars. otherwise just
  // set view sizes to the viewport's actual viewing region

  int haxsize = (haxview->isAutosized()) ? viewport->getWidth() : viewport->getViewWidth();
  int vaxsize = (vaxview->isAutosized()) ? viewport->getHeight() : viewport->getViewHeight();
  // reduce axis and plot areas by width of scrollbar 
  haxsize -= scrollerwidth;
  vaxsize -= scrollerwidth;
  haxview->setBounds(70, 20, haxsize, 26);
  vaxview->setBounds(2, 50, 64, vaxsize);
  if (haxview->isAutosized() || vaxview->isAutosized())
  {
    // calculate the spead factors that makes axes use all the available space
    if (haxview->isAutosized())
      haxview->setSpreadToFit(haxsize);
    if (vaxview->isAutosized())
      vaxview->setSpreadToFit(vaxsize);
    // resize the plot view
    resizeForSpread();
  }
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
                                Audio Playback
 *=======================================================================*/

bool Plotter::isPlaying()
{
  return playing;
}

void Plotter::setPlaying(bool p)
{
  playing=p;
}

void Plotter::setPlaybackParameter(PlaybackParam id, double value)
{
  ScopedLock mylock (pblock);
  std::cout << "Plotter::setPlaybackParameter(" << id << ", " << value << ")\n";
  playbackparams[id]=value;
}

double Plotter::getPlaybackParameter(PlaybackParam id)
{
  ScopedLock mylock (pblock);
  return playbackparams[id];
}

void Plotter::pause()
{
  std::cout << "Plotter::pause()\n";
  pbthread->setPaused(true);
}

void Plotter::play(double pos)
{
  std::cout << "Plotter::play(" << pos << ")\n";
  pbthread->setPaused(false);
}

void Plotter::tempoChanged(double tempo, bool isPlaying)
{
  std::cout << "Plotter::tempoChanged(" << tempo << ", " << isPlaying << ")\n";
  pbthread->setTempo(tempo);
}

void Plotter::positionChanged(double position, bool isPlaying)
{
  std::cout << "Plotter::positionChanged(" << position << ", " << isPlaying << ")\n";
  ScopedLock mylock (pblock);
  double tobeat = position * getHorizontalAxis()->getMaximum();
  setPlaybackIndexes(tobeat);
}

void Plotter::setPlaybackIndexes(const double beat)
{
  // FIXME: this could be optimized check for no points OR if the beat
  // is past the maximum X of the axis
  const int n=numLayers();
  for (int i=0; i<n; i++)
  {
    Layer* l=getLayer(i);
    l->pbindex=l->getNextPlaybackIndex(beat);
  }
}

void Plotter::addMidiPlaybackMessages(MidiPlaybackThread::MidiMessageQueue& queue,
                                      MidiPlaybackThread::PlaybackPosition& position)
{
  /*  double x=(position*getHorizontalAxis()->getAxisMaximum());
  Layer* focus=getFocusLayer();
  for (int i=0; i<getNumLayers(); i++)
  {
    Layer* layer=getLayer(i);
    if (layer!=focus && layer->isMuted()) continue;
    int index=layer->getStartingIndexforX(x);
    while (index<=layer->getNumPoints() && layer->getPointX(index)<=x)
    {
      ADDMIDI();
      index+=1;
    }
  }
  */
  std::cout << "plotter addMidiPlaybackMessages("<<position.beat<<")\n";
}


