/*=======================================================================*
  Copyright (c) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify
  it under the terms of the Lisp Lesser Gnu Public License. The text
  of this agreement is available at http://www.cliki.net/LLGPL
 *=======================================================================*/

#include "Enumerations.h"
#include "Menus.h"
#include "Console.h"
#include "Plot.h"
#include <limits>
//#include <cmath>
#include <iostream>

/*=======================================================================*
                             PlotViewport (scrolling)
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
  col2=col1;
  Font font=viewport->plotter->font;
  String labl;
  double lhei=font.getHeight(), lwid, just;
  double pval=getOrigin(); 
  double aval=axis->getMinimum();   
  double save;
  double by=axis->getIncrement();
  
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
	  g.drawText(labl,(int)(pval+just),0,(int)lwid,(int)lhei, 
		     Justification::topLeft, false);
	  // draw minor ticks above each major tick
	  g.setColour(col2);
	  for (int i=1;i<numTicks();i++)
	    g.drawVerticalLine((int)(pval+(tsiz*i)), height-minortick, height);
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
      float tx,ty;
      
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
	  g.drawText(labl,
		     width-graywidth-4-lwid,
		     (int)(pval-just),
		     (int)lwid,
		     (int)lhei,
		     Justification::topLeft,
		     false);	  
	  g.setColour(col2);
	  for (int i=1;i<numTicks();i++)
	    g.drawHorizontalLine((int)(pval-(tsiz*i)), width-minortick, width);
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
  double a,b,c;
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

  void selectAll ()
  {
    int i;
    selection.deselectAll();
    for (i=0; i<focuslayer->numPoints(); i++)
      selection.addToSelection(focuslayer->getPoint(i));
  }

  void deselectAll() {
    selection.deselectAll();
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

  void moveSelection(float val, Plotter::Orientation orient);
  void moveSelection(float x, float y);

  void shiftSelection(float val, Plotter::Orientation orient);
  void shiftSelection(float x, float y);

  void scaleSelection (float val, Plotter::Orientation orient);
  void rescaleSelection (float val, Plotter::Orientation orient);
  void reorderSelection (float val, Plotter::Orientation orient);

  float getSelectionMin(Plotter::Orientation orient);
  float getSelectionMax(Plotter::Orientation orient);

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

float PlotView::getSelectionMin(Plotter::Orientation orient) {
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
  
void PlotView::shiftSelection(float dx, float dy) {
  int n=numSelected();
  for (int i=0; i<n; i++)
    focuslayer->incPoint( getSelected(i), dx, dy);
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
  //std::cout << "drawgrid "<<left<<" "<<top<<" "<<bottom<<" "<<right<<"\n";
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
  if (e.mods.isCtrlDown())
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
	      repaintFocusPlot();
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
    shiftSelection(dx, dy);
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
	  printSelection();
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

bool PlotView::keyPressed (const KeyPress& key)
{
  if ((key.isKeyCode(KeyPress::backspaceKey) ||
       key.isKeyCode(KeyPress::deleteKey)))
    {
      if (!key.getModifiers().isAnyModifierKeyDown() &&
	  isSelection())
	deleteSelection();
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
  OwnedArray<XmlElement> xmlaxes;
  OwnedArray<XmlElement> xmlplots;
  if (plot!=NULL)
    {
      std::cout << plot->createDocument(T("")).toUTF8() << "\n";
      forEachXmlChildElement(*plot, e)
	if (e->hasTagName(T("axis")))
	  xmlaxes.add(e);
	else if (e->hasTagName(T("points")))
	  xmlplots.add(e);
    }  
  std::cout << "xmlaxes=" << xmlaxes.size() << " xmlplots=" << xmlplots.size() << "\n";

  if (xmlaxes.size()==0) // No axes specified
    {
      axes.add(new Axis(NULL));
      fields.add(new Field(T("Field 1"), axes[0]));
      axes.add(new Axis(NULL));
      fields.add(new Field(T("Field 2"), axes[1]));
    }
  else if (xmlaxes.size()==1) // Just Y axis specified
    {
      axes.add(new Axis(NULL));
      axes[0]->init(Axis::ordinal);
      fields.add(new Field(T("Field 1"), axes[0]));
      axes.add(new Axis(xmlaxes[0]));
      fields.add(new Field(xmlaxes[0]->getStringAttribute(T("name"),
							  T("Field 2")),
			   axes[1]));
    }
  else
    for (int i=0; i<xmlaxes.size(); i++)
      {
	String n=xmlaxes[i]->getStringAttribute(T("name"), 
						T("Field ") + String(i+1));
	String r=xmlaxes[i]->getStringAttribute(T("range"), String::empty);
	Axis* a=NULL;
	if (r.isNotEmpty())
	  for (int j=0; j<i && j<fields.size() && a==NULL; j++)
	    if (fields[j]->name==r)
	      a=fields[j]->axis;	
	if (a)
	  std::cout << "found shared!\n";
	else
	  {
	    a=new Axis(xmlaxes[i]);
	    axes.add(a);	      
	  }
	fields.add(new Field(n, a));
      }
  
  font=Font(Font::getDefaultSansSerifFontName(), 10.0, Font::bold);
  plotview=new PlotView (this);
  backview=new BackView(this);
  // plot view is child of backview so that it is in front
  backview->addChildComponent(plotview);
  plotview->setTopLeftPosition(0,0);
  plotview->setWantsKeyboardFocus(true);

  viewport=new PlotViewport (this);
  
  haxview=new AxisView(viewport, horizontal);
  vaxview=new AxisView(viewport, vertical);
  setHorizontalAxis(axes[0]);
  setVerticalAxis(axes[1]);

  if (xmlplots.size()>0)
    {
      for (int i=0; i<xmlplots.size(); i++)
	newLayer(xmlplots[i]);
    }
  else
    newLayer(NULL);

  autosizeAxes();
  
  xmlaxes.clear(false);
  xmlplots.clear(false);

  addChildComponent(haxview);  
  addChildComponent(vaxview);  
  plotview->resizeForDrawing();  // calc plots width/height

  // add the backview to the viewport. the plotview is a child of the
  // backview and so it will scroll with it
  viewport->setViewedComponent(backview);
  viewport->setScrollBarsShown (true, true);
  addChildComponent(viewport);

  // scroll to origin of axis
  //this doenst work >:(
  //viewport->getVerticalScrollBar()->scrollToBottom();
  viewport->setViewPositionProportionately(0.0,1.0);
  viewport->setVisible(true);
  backview->setVisible(true);
  plotview->setVisible(true);
  haxview->setVisible(true);
  vaxview->setVisible(true);
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
  axes.clear();
}

void Plotter::autosizeAxes()
{
  // look for unspecified axes to autosize
  for (int i=0;i<axes.size();i++)
    {
      if (axes[i]->type==Axis::unspecified)
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
	    axes[i]->setMinimum(lo);

	  if (hi<=1.0)
	    {
	      axes[i]->setMaximum(1.0);
	    }
	  else if (hi<=10.0)
	    {
	      axes[i]->setMaximum(ceil(hi));
	      axes[i]->setIncrement(1.0);
	    }
	  else if (hi<=100.0)
	    {
	      axes[i]->setMaximum(ceil(hi));
	      axes[i]->setIncrement(10.0);
	      axes[i]->setTicks(2);
	    }
	  else if (hi<=1000)
	    {
	      axes[i]->setMaximum(ceil(hi));
	      axes[i]->setIncrement(10.0);
	      axes[i]->setTicks(2);
	    }

	  std::cout << "autosized axis[" << i
		    <<"]: min=" << axes[i]->getMinimum() 
		    << " max=" << axes[i]->getMaximum() << "\n";
	}
      else if (axes[i]->type==Axis::ordinal)
	{
	  int siz=1;
	  for (int j=0; j<layers.size(); j++)
	    siz=jmax(siz,layers[j]->numPoints());
	  axes[i]->setMaximum(siz);
	}
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
  plotview->deselectAll();
  plotview->focuslayer=layr;
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
  static Colour cols[8] = {Colours::red, Colours::green, 
			   Colours::blue, Colours::magenta,
			   Colours::cyan, Colours::sienna,
			   Colours::orange, Colours::coral};
  Colour col = cols[layers.size() % 8];
  int sty=Layer::lineandpoint;
  String nam = T("Layer ") + String(layers.size()+1);
  int num=getNumFields();
  Layer* layer=NULL;

  if (points)
    {
      std::cout << "newlayer has " << points->getNumChildElements() 
		<< " points\n";
      String s=points->getStringAttribute(T("style"));
      if (s.isNotEmpty())
	sty=Layer::toLayerType(s, sty);
      s=points->getStringAttribute(T("color"));
      if (s.isNotEmpty())
	col=Colours::findColourForName(s, col);
      nam=points->getStringAttribute(T("title"), nam);
      layer=new Layer(num, nam, col, sty);
      layer->addXmlPoints(points);
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

  std::cout << "width=" << getWidth() << " height=" << getHeight() << "\n";
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
  : DocumentWindow (String::empty , Colours::white, 
		    DocumentWindow::allButtons, true ) 
{
  String title=(plot==NULL) ? T("Untitled Plot") :
    plot->getStringAttribute(T("title"), T("Untitled Plot"));
  plotter = new Plotter(plot) ;
  menubar = new MenuBarComponent(this);
  setMenuBar(this);
  setUsingNativeTitleBar(true);    
  setName(title);
  //plotter->setSize(600,600);
  plotter->setSize(500, 500);
  plotter->setVisible(true);
  setContentComponent(plotter,true,true);
  centreWithSize (plotter->getWidth(), plotter->getHeight());
  setResizable(true, true); 
  setVisible(true);
}

PlotterWindow::~PlotterWindow ()
{
  plotter->~Plotter();
}

void PlotterWindow::openXml(String str)
{
  std::cout << str.toUTF8() << "\n";
  XmlDocument doc (str);
  XmlElement* xml = doc.getDocumentElement();
  if (xml)
    {
      new PlotterWindow::PlotterWindow(xml);
      delete xml;
    }
  else
    {
      String err=T(">>> Error ");
      err << doc.getLastParseError() << T("\n");
      Console::getInstance()->printError(err);
    }
}

void PlotterWindow::closeButtonPressed () 
{
  this->~PlotterWindow();
}

const StringArray PlotterWindow::getMenuBarNames ()
{
  const tchar* const menuNames[] =
    { T("File"), T("Edit"), T("Layer"), T("View"), T("Window"),
      T("Help"), 0 };
  return StringArray((const tchar**) menuNames);
}

const PopupMenu PlotterWindow::getMenuForIndex(int idx, const String &name) 
{
  PopupMenu menu;
  PopupMenu sub1, sub2, sub3;
  int val;
  
  if (name==T("File"))
    {
      // File Menu
      menu.addItem(CommandIDs::PlotterNew, T("New"));
      menu.addSeparator();
      menu.addItem(CommandIDs::PlotterLoad, T("Load..."), false);
      menu.addItem(CommandIDs::PlotterExport, T("Export..."), false);
    }
  else if (name==T("Edit"))
    {
      // Edit Menu
      menu.addItem(CommandIDs::EditorUndo, T("Undo"),
		   plotter->actions.canUndo());
      menu.addItem(CommandIDs::EditorUndo, T("Redo"),
		   plotter->actions.canRedo());
      menu.addSeparator();
      menu.addItem(CommandIDs::EditorCut, T("Cut"),
		   plotter->isSelection() );
      menu.addItem(CommandIDs::EditorCopy, T("Copy"));
      menu.addItem(CommandIDs::EditorPaste, T("Paste"),
		   !pointClipboard.isEmpty());
      menu.addSeparator();
      menu.addItem(CommandIDs::EditorSelectAll, 
		   T("Select All"));
      menu.addItem(CommandIDs::EditorUnselectAll, T("Clear Selection"));
    }
  else if (name==T("Layer"))
    {
      menu.addItem(CommandIDs::PlotterLayerAdd, T("New"));
      menu.addItem(CommandIDs::PlotterLayerDelete, T("Delete"),
		   (plotter->numLayers() > 1));
      menu.addSeparator(); 
      // append existing layers to end of menu in plotting color :)
      for (int i=0; i<plotter->numLayers(); i++)
	{
	  Layer * layer=plotter->getLayer(i);
	  menu.addColouredItem(CommandIDs::PlotterLayerSelect +
			       layer->getLayerID(),
			       layer->getLayerName(),
			       layer->getLayerColor(),
			       true,
			       plotter->isFocusLayer(layer));
	}
    }
  else if (name==T("View"))
    {
      Layer * layer=plotter->getFocusLayer();
      // add these with focus colored items to make it clear that the
      // styling change only affects the focus plot
      menu.addColouredItem(CommandIDs::PlotterStyle + Layer::line, 
			   T("Line"),
			   layer->getLayerColor(),
			   true,
			   (val==Layer::line));
      menu.addColouredItem(CommandIDs::PlotterStyle + Layer::point,
			   T("Point"),
			   layer->getLayerColor(),
			   true,
			   (val==Layer::point));
      menu.addColouredItem(CommandIDs::PlotterStyle + Layer::lineandpoint,
			   T("Envelope"),
			   layer->getLayerColor(),
			   true,
			   (val==Layer::lineandpoint));
	/*	menu.addColouredItem(CommandIDs::PlotterStyle + Layer::hbox, 
		T("Horizontal Box"),
		layer->getLayerColor(),
		(type > PlotIDs::XYPlot), 
		(val==Layer::hbox));
	*/
      menu.addColouredItem(CommandIDs::PlotterStyle + Layer::impulse, 
			   T("Impulse"),
			   layer->getLayerColor(),
			   true, (val==Layer::impulse));
      menu.addColouredItem(CommandIDs::PlotterStyle + Layer::histogram, 
			   T("Histogram"),
			   layer->getLayerColor(),
			   true, 
			   (val==Layer::histogram));
      menu.addColouredItem(CommandIDs::PlotterStyle + Layer::vbar, 
			   T("Vertical Bar"),
			   layer->getLayerColor(),
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
  else if (name==T("Window"))
    menu=CommandMenus::getWindowMenu();
  else if (name==T("Help")) 
    menu=CommandMenus::getHelpMenu(WindowTypes::Plotter, 0);

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
    case CommandIDs::PlotterExport :
      showExportPointsDialog();
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
      plotter->redrawPlotView();
      break;
    case CommandIDs::EditorUnselectAll :
      plotter->deselectAll();
      plotter->redrawPlotView();
      break;
      
    case CommandIDs::PlotterLayerAdd :
      plotter->newLayer(NULL);
      plotter->redrawBackView();
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
      break;
    case CommandIDs::CommandIDs::PlotterStyle :
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

/*=======================================================================*
                               Export Dialog
 *=======================================================================*/

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
      exportbutton (0),
      plotter(0),
      include(0)
{
  plotter=p;
  numfields=plotter->getFocusLayer()->getLayerArity();
  include=new bool[numfields];

  for (int i=0;i<numfields; i++) include[i]=true;

  Font font=Font (15.0000f, Font::plain);
  addAndMakeVisible(exportlabel = new Label(String::empty, T("Export:")));
  exportlabel->setFont(font);

  addAndMakeVisible (exportmenu = new ComboBox (String::empty));
  exportmenu->setEditableText (false);
  exportmenu->addItem (T("Layer"), 1);
  exportmenu->addItem (T("Selection"), 2);
  exportmenu->setSelectedId(1);
  exportmenu->setItemEnabled(2, plotter->getPlotView()->isSelection());

  addAndMakeVisible(tolabel=new Label(String::empty, T("For:")));
  tolabel->setFont (font);

  addAndMakeVisible(tomenu = new ComboBox (String::empty));
  tomenu->setEditableText(false);
  tomenu->addItem(T("SAL"), 1);
  tomenu->addItem(T("Lisp"), 2);
  tomenu->setSelectedId(1);

  addAndMakeVisible(fieldsbutton = new TextButton (String::empty));
  fieldsbutton->setButtonText(T("Included Fields..."));
  fieldsbutton->addButtonListener (this);

  addAndMakeVisible(formatlabel = new Label(String::empty, T("Format:")));
  formatlabel->setFont(font);

  addAndMakeVisible(formatmenu = new ComboBox(String::empty));
  formatmenu->setEditableText (false);
  formatmenu->addItem(T("Envelope List"), 1);
  formatmenu->addItem(T("Point Records"), 2);
  formatmenu->setSelectedId(1);

  addAndMakeVisible(valuelabel=new Label(String::empty, 
					 T("Value format:")));
  addAndMakeVisible(valuemenu = new ComboBox(String::empty));
  valuemenu->addItem(T("0"), 1);
  valuemenu->addItem(T("0.0"), 2);
  valuemenu->addItem(T("0.00"), 3);
  valuemenu->addItem(T("0.000"), 4);
  valuemenu->addItem(T("0.0000"), 5);
  valuemenu->setSelectedId(3);

  addAndMakeVisible(exportbutton = new TextButton(String::empty));
  exportbutton->setButtonText(T("Export"));
  exportbutton->addButtonListener(this);
  setSize(440, 140);
}

ExportPointsDialog::~ExportPointsDialog() {
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
}

void ExportPointsDialog::resized() {
  exportlabel->setBounds (16, 16, 56, 24);
  exportmenu->setBounds (76, 16, 88, 24);
  tolabel->setBounds (176, 16, 34, 24);
  tomenu->setBounds (210, 16, 80, 24);
  fieldsbutton->setBounds (304, 16, 120, 26);
  formatlabel->setBounds (16, 56, 56, 24);
  formatmenu->setBounds (77, 56, 150, 24);
  valuelabel->setBounds (246, 56, 92, 24);
  valuemenu->setBounds (342, 56, 80, 24);
  exportbutton->setBounds (274, 96, 150, 24);
}

void ExportPointsDialog::exportPoints() {
  Layer* layer=plotter->getFocusLayer();
  PlotView* plotview=plotter->getPlotView();
  if (layer->numPoints() == 0)
    return;
  bool layerexport=(exportmenu->getSelectedId()==1);
  bool salexport=(tomenu->getSelectedId()==1);
  int decimals=valuemenu->getSelectedId()-1;
  int format=formatmenu->getSelectedId();
  int numparams=0;
  int parammask=0;

  // turn included fields into parameter strings for sal or lisp
  for (int i=0; i<numfields; i++) 
    if ( include[i] ) {
      parammask += 1<<i;
      numparams++;
    }
  // do nothing if user deselected all fields!
  if (numparams==0) return;

  String text = (salexport) ? T("define variable exported = ")
    : T("(defparameter exported ");
  int indent,column;
  String spaces;

  if ((format==1) || (format==2)) {
    // static number exporting
    text += (salexport) ? T("{") : T("'(");
    indent=text.length();
  }
  else {
    // exports require eval form
    String line = (salexport) ? T("  list(") : T("  (list ");
    text += T("\n") + line;
    indent=line.length();
  }
  spaces=String::repeatedString(T(" "), indent);
  column=indent;

  LayerPoint* point;
  int length=(layerexport) ? layer->numPoints() : plotview->numSelected();
  for (int i=0; i<length; i++) {
    point=(layerexport) ? layer->getPoint(i) : plotview->getSelected(i);
    String one=layer->exportPoint(point, parammask, format,
				  salexport, decimals);
    int len=one.length();
    if (format==3) {
      column=indent;
      if (i>0) {
	text += (salexport) ? T(",\n") : T("\n");
	text += spaces;
      }
    }
    else if ((column+len) > 73) {
	column=indent;
	text += T("\n") + spaces;
    }
    else if (i>0)
      text += T(" ");
    text+=one;
    column+=len;
  }
  // add appropriate close parens...
  if (format==3)
    text += T("\n") + spaces + ((salexport) ? T(")\n") : T("))\n"));
  else
    text += (salexport) ? T("}\n") : T("))\n");
  //  printf("%s\n",text.toUTF8());
  SystemClipboard::copyTextToClipboard(text);
}

void ExportPointsDialog::buttonClicked (Button* button) {
  if (button == exportbutton) {
    PlotterWindow* win=(PlotterWindow*)getTopLevelComponent();
    exportPoints();
    win->getCloseButton()->triggerClick();
  }
  else if (button == fieldsbutton) {
    /*    int i;
    PopupMenu m;
    for (i=0; i<numfields; i++)
      m.addItem(i+1, plotter->getFocusLayer()->getFieldName(i),
		true, include[i]);
    i=m.showAt(button);
    if (i != 0) include[i-1]=(!include[i-1]);
    */
  }
}

void PlotterWindow::showExportPointsDialog () {
  DialogWindow::showModalDialog(T("Export Points to Clipboard"),
				new ExportPointsDialog(plotter),
				this,
				Colour(0xffe5e5e5),
				true);
}
