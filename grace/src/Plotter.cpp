/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

#include "Plotter.h"
#include <iostream>
#include <limits>
#include "Resources.h"

using namespace std;

//
// PlotViewport (scrolling)
//

class PlotViewport : public Viewport {
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
    // setOpaque(true);
  }
  ~PlotViewport () {}
  //void paint(Graphics& g) {g.fillAll(Colours::white);}
};

///
/// AxisView methods
///

bool AxisView::isVertical() {
  return (orient==Plotter::vertical);
}

bool AxisView::isHorizontal() {
  return (orient==Plotter::horizontal);
}

void AxisView::paint (Graphics& g) {
  g.fillAll (Colours::white); 
  // lightly shade lower half to match pretty scrollbars
  g.setColour(Colour(0xf7, 0xf7, 0xf7)); 
  if (!hasAxis() ) return;
  int w=getWidth();
  int h=getHeight();

  if ( isVertical() )
    g.fillRect(w/2, 0, w/2, h);
  else  
    g.fillRect(0, h/2, w, h/2);
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
  Font font=viewport->plotter->font;
  String labl;
  double lhei=font.getHeight(), lwid, just;
  double pval=getOrigin(); 
  double aval=axis->getMinimum();   
  double save;
  double by=axis->getIncrement();

  g.setFont(font);

  if ( isHorizontal() ) {
    int left=viewport->getViewPositionX();  // plot's visible left
    int width=viewport->getViewWidth();
    int height=getHeight();   // height of axis view

    // determine first visible label that is >= plot's visible left
    while ( pval<left ) {
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
    while ( pval<=width ) {
      g.setColour(col1);
      g.drawVerticalLine((int)pval,height*.5, height);
      labl=String(aval,axis->getDecimals());
      lwid=font.getStringWidthFloat(labl);
      just=(int)(-lwid*(pval/width));  // twiddle label justification
      g.drawText(labl,(int)(pval+just),0,(int)lwid,(int)lhei, 
		 Justification::topLeft, false);
      // draw minor ticks above each major tick
      g.setColour(col2);
      for (int i=1;i<numTicks();i++)
	g.drawVerticalLine((int)(pval+(tsiz*i)), height*.75, height);
      pval+=isiz;
      aval+=by;
    }
    // now draw any ticks left of first increment
    pval=save-tsiz;
    g.setColour(col2);
    while (pval > 0) {
      g.drawVerticalLine((int)pval, height*.75, height);
      pval-=tsiz;
    }
  }
  else {
    int height=viewport->getViewHeight();
    int top=viewport->getViewPositionY();
    int bottom=height+top;
    int width=getWidth();   // width of axis view
    float tx,ty;

    while (pval>bottom) {
      pval-=isiz;
      aval+=by;
    }

    save=pval-top;
    pval=save;
    while (pval>=0) {
     g.setColour(col1);
     g.drawHorizontalLine((int)pval,width*.5, width);
     labl=String(aval,axis->getDecimals());
     lwid=font.getStringWidthFloat(labl);

     // METHOD1: justify vertically, but now the view has to be wider.
     just=(int)(lhei*(pval/height));  // twiddle label justification
     g.drawText(labl, 0, (int)(pval-just),(int)lwid,(int)lhei,
		Justification::topLeft, false);

     // METHOD2: rotate 90 and then jusitfy width like th X
     // axis. arrrrrgghh i cant figure this out!!

     // g.drawTextAsPath(labl, AffineTransform::identity.rotated(float_Pi*2*-.25,width,pval));

     g.setColour(col2);
     for (int i=1;i<numTicks();i++)
       g.drawHorizontalLine((int)(pval-(tsiz*i)), width*.75, width);
      pval-=isiz;
      aval+=by;
    }
    // now draw any ticks below first increment
    pval=save+tsiz;
    g.setColour(col2);
    while (pval < height) {
      g.drawHorizontalLine((int)pval, width*.75, width);
      pval+=tsiz;
    }
  }
  g.setColour(Colours::black);
}


/***********************************************************************
 *
 * Region and selection, sweeping and editing
 *
 **********************************************************************/

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


/***********************************************************************
 *
 * BackView: view to hold grid and background plots.
 * PlotView: the focus layer's drawing canvas
 *
 **********************************************************************/

void drawLayer(Graphics& g, Layer * layer, AxisView * haxview, AxisView * vaxview, 
	       double ppp, double spread, bool isFoc, 
	       SelectedItemSet<LayerPoint*> * sel);

void drawGrid(Graphics& g, AxisView * haxview, AxisView * vaxview, 
	      Colour c1, Colour c2) ;

class BackView : public Component {
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

/***********************************************************************
 *
 * PlotView: the focus layer's drawing canvas
 *
 **********************************************************************/

class PlotView : public Component {
 public:
  Plotter * plotter;
  BackView * backview;
  double pad; // pix per inc, pix per point, margin pad
  Point mousedown, mousemove;
  Label * xvalue;  // pointers to focus view's point display
  Label * yvalue;
  SelectedItemSet<LayerPoint*> selection;
  Region region;
  Layer * focuslayer; // cached focus layer for fast acesss

  PlotView (Plotter * p) 
    : pad (8.0) {
    plotter=p;
  }

  ~PlotView () { }

  void paint (Graphics& g);
  void repaintFocusPlot() {repaint();}
  void resized() {plotter->backview->setSize(getWidth(),getHeight());}
  void mouseDown(const MouseEvent &e) ;
  void mouseDrag(const MouseEvent &e) ;
  void mouseUp(const MouseEvent &e) ;
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

  void setPointBuffers(float x, float y);
  void setPointBuffers(LayerPoint* p) {
    setPointBuffers(focuslayer->getPointX(p),
		    focuslayer->getPointY(p));
  }

  void clearPointBuffers();

  bool isSelection() {return (selection.getNumSelected() > 0);}
  int numSelected() {return selection.getNumSelected();}

  bool isSelected(LayerPoint* p) {return selection.isSelected(p);}
  bool isSelected(int h) {return isSelected(focuslayer->getPoint(h));}

  void selectAll () {
    int i;
    printf("plotview selectall\n");

    selection.deselectAll();
    for (i=0; i<focuslayer->numPoints(); i++)
      selection.addToSelection(focuslayer->getPoint(i));
    if (i==1) 
      setPointBuffers(focuslayer->getPoint(i));
    else clearPointBuffers();
  }

  void deselectAll() {
    selection.deselectAll();
    clearPointBuffers();
  }

  void removeSelection(LayerPoint* p) {selection.deselect(p);}
  void removeSelection(int h) {removeSelection(focuslayer->getPoint(h));}

  void setSelection(LayerPoint* p) ;
  void setSelection(int h) {setSelection(focuslayer->getPoint(h));}

  void addSelection(LayerPoint* p) {
    selection.addToSelection(p);
    if (numSelected()==1) {
    }
    else clearPointBuffers();

  }
  void addSelection(int h) {addSelection(focuslayer->getPoint(h));}
  void deleteSelection () ;

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

void PlotView::setPointBuffers(float x, float y) {
  xvalue->setText(String(x,2), false);
  yvalue->setText(String(y,2), false);
}

void PlotView::clearPointBuffers() {
  xvalue->setText(String::empty, false);
  yvalue->setText(String::empty, false);
}  

void PlotView::setSelection(LayerPoint* p) {
  selection.selectOnly(p);
  setPointBuffers(focuslayer->getPointX(p),
		  focuslayer->getPointY(p));
}

float PlotView::getSelectionMin(Plotter::Orientation orient) {
  numeric_limits<float> info;
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
  if (n==1) {
    LayerPoint* p=getSelected(0);
    setPointBuffers(focuslayer->getPointX(p),
		    focuslayer->getPointY(p));
  }
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

void drawLayer(Graphics& g, Layer * layer, AxisView * haxview, AxisView * vaxview, 
	       double ppp, double zoom, bool isFoc, 
	       SelectedItemSet<LayerPoint*> * sel) {
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

void PlotView::paint (Graphics& g) {
  // erase with white
  drawLayer(g, focuslayer,
	    plotter->getHorizontalAxisView(),
	    plotter->getVerticalAxisView(),
	    plotter->getPointSize(),
	    1.0,
	    true,
	    &selection);
}

void drawGrid(Graphics& g, AxisView * haxview, AxisView * vaxview, 
	      Colour c1, Colour c2) {
  double left=haxview->getOrigin();
  double right=left+haxview->extent();
  double bottom=vaxview->getOrigin();
  double top=bottom-vaxview->extent();
  double v,p,t,d;
  //std::cout << "drawgrid "<<left<<" "<<top<<" "<<bottom<<" "<<right<<"\n";
  p=haxview->getOrigin();
  d=haxview->incrementSize();
  t=haxview->tickSize();
  while (p <= right) {
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
  while (p >= top) {
    g.setColour(c1);
    g.drawHorizontalLine((int)p, left, right);
    g.setColour(c2);
    for (int i=1;i<vaxview->numTicks();i++) 
      g.drawHorizontalLine((int)(p-(t*i)), left, right);
    p -= d;
  }
  g.setColour(c1);
}

bool PlotView::isInside(float x, float y, float left, float top, 
			float right, float bottom) {
  if ( (left <= x) && (x <= right)  &&
       (bottom <= y) && (y <= top) )
    return true;
  else return false;
}

void PlotView::selectPointsInside(float left, float top, float right, float bottom){
  //printf("looking in region: left=%f top=%f, right=%f, bottom=%f\n",x1, y2, x2, y1);
  //deselectAll();
  for (int i=0; i<focuslayer->numPoints(); i++) {
    double x=focuslayer->getPointX(i);
    double y=focuslayer->getPointY(i);
    if ( isInside(x, y, left, top, right, bottom) ) {
      addSelection(i);
    }
    else if (x > right) break; // stop looking
  }
}

void PlotView::mouseDown (const MouseEvent &e) {
  // shoudnt happen
  if (focuslayer==(Layer *)NULL) return;

  int mxp=e.getMouseDownX();
  int myp=e.getMouseDownY();
  AxisView * haxview=plotter->getHorizontalAxisView();
  AxisView * vaxview=plotter->getVerticalAxisView();

  // cache mouse down position  FIX THIS ISNT NEEDED
  mousedown.setXY(mxp, myp);
  mousemove.setXY(mxp, myp);
  
  // Control-Click: add point make selection
  // Control-Shift-Click: add point add selection.
  if ( e.mods.isCtrlDown() ) {
    int i = focuslayer->addPoint(haxview->toValue(mxp),
				 vaxview->toValue(myp));
    if ( e.mods.isShiftDown() )
      addSelection( i);
    else setSelection(i);
    repaintFocusPlot();
    return;
  }

  double half=plotter->getPointSize()/2;
  int h=-1;
  double left, top, right, bottom, x, y;

  if ( focuslayer->isDrawStyle(Layer::hbox) ) {
    // speed: since box height is constant check point y againt a
    // (constant) vertical box height centered on mouse y
    top=vaxview->toValue( myp - half);
    bottom=vaxview->toValue( myp + half);
    x=haxview->toValue( mxp);
    for (int i=0; i < focuslayer->numPoints(); i++) {
      left=focuslayer->getPointX(i);
      right=left+focuslayer->getPointZ(i);
      y=focuslayer->getPointY(i);
      if ( isInside(x, y, left, top, right, bottom) ) {
	h=i;
	break;
      }
      // give up when points are rightward of mouse x
      else if (left > x)
	break;
    }
  }
  else {
    // calc a constant "point" around mouse x and y and try to
    // find a point thats inside it
    left=haxview->toValue( mxp - half);
    top=vaxview->toValue( myp - half);
    right=haxview->toValue( mxp + half);
    bottom=vaxview->toValue( myp + half);

    for (int i=0; i < focuslayer->numPoints(); i++) {
      x=focuslayer->getPointX(i);
      y=focuslayer->getPointY(i);
      if ( isInside(x, y, left, top , right, bottom) ) {
	h=i;
	break;
      } 
      // give up when points are rightward of mouse x
      else if (x > right) 
	break;
    }
  }

  if ( h<0 ) {
    // Mouse down on empty space . Add to selection if shift is down
    if ( isSelection() ) {
      if ( ! e.mods.isShiftDown() ) {
	deselectAll();
	repaintFocusPlot();
      }
    }
    addChildComponent (&region);
    region.beginSweep(e, haxview, vaxview);
  }
  else if ( isSelected(h) ) {
    // point is already selected.
    // Mouse-shift-click remove Point from selection
    if ( e.mods.isShiftDown() ) {
      removeSelection(h);
      repaintFocusPlot();
    }
  }
  else {
    // point is not selected.
    // Mouse-Click: set point as (single) selection
    // Mouse-shift-click:   add Point from selection
    if ( e.mods.isShiftDown() ) 
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

void PlotView::mouseUp(const MouseEvent &e) {
  if ( isSelection() ) {
    if (mousedown.getX() != mousemove.getX() ) {
      printf("sorting after move\n");
      focuslayer->sortPoints();
      printSelection();
    }
    repaintFocusPlot();
  }
  else if ( e.getDistanceFromDragStart() == 0) {
    // clicked without drag
  }
  else {
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

/***********************************************************************
 *
 * FocusView: controls for working with the top-most (focus) plot
 *
 **********************************************************************/

class FocusView  : public Component,
		   public LabelListener {
public:
  Plotter * plotter;
  Layer * focuslayer;
  Label* nlabel;
  Label* layername;
  Label* xlabel;
  Label* xvalue;
  Label* ylabel;
  Label* yvalue;

  FocusView (Plotter* p);
  ~FocusView();

  void setFocusLayer(Layer* l);
  Layer* getFocusLayer() { return focuslayer;}
  void resized();
  void labelTextChanged(Label * label);
  void updateFieldLabels();
  void setNameBuffer(String name, bool act=false) {
    layername->setText(name, act);
  }
  void setXBuffer(String name, bool act=false) {
    xvalue->setText(name, act);
  }
  void setYBuffer(String name, bool act=false) {
    yvalue->setText(name, act);
  }
};

FocusView::FocusView (Plotter * p)
  : plotter (0),
    focuslayer (0),
    nlabel (0),
    layername (0),
    xlabel (0),
    xvalue (0),
    ylabel (0),
    yvalue (0) {
  plotter=p;
  Font font=Font( 14.0, Font::bold);

  int width=font.getStringWidth(T("Layer: "));
  addAndMakeVisible(nlabel = new Label(String::empty, T("Layer:")));
  nlabel->setFont (font);
  nlabel->setJustificationType (Justification::centredRight);
  nlabel->setColour (Label::backgroundColourId, Colour(230, 230, 0xff) );
  nlabel->setEditable (false, false, false);
  nlabel->setSize(width,24);

  addAndMakeVisible (layername = new Label(T("layername"),
					   String::empty));
  layername->setFont(font);
  layername->setJustificationType(Justification::centredLeft);
  layername->setEditable(true);
  layername->setColour(Label::backgroundColourId, Colours::white);
  layername->setBounds(width, 0, 100,24);
  layername->addListener(this);
  nlabel->attachToComponent(layername, true);


  width=font.getStringWidth(T("X:"));
  addAndMakeVisible(xlabel = new Label(T("xlabel"), T("X:")));
  xlabel->setFont (font);
  xlabel->setJustificationType (Justification::centredRight);
  xlabel->setColour (Label::backgroundColourId, Colour(230, 230, 0xff) );
  xlabel->setEditable (false, false, false);
  xlabel->setSize(width,24);

  addAndMakeVisible (xvalue = new Label (T("xvalue"), String::empty));
  xvalue->setFont (font);
  xvalue->setJustificationType (Justification::centredRight);
  xvalue->setEditable (true);
  xvalue->setColour (Label::backgroundColourId, Colours::white);
  xvalue->setBounds(layername->getRight()+30, 0, 60, 24);
  xvalue->addListener(this);

  addAndMakeVisible (ylabel = new Label (String::empty, T("Y:")));
  ylabel->setFont(font);
  ylabel->setJustificationType (Justification::centredRight);
  ylabel->setColour (Label::backgroundColourId, Colour(230, 230, 0xff) );
  ylabel->setEditable (false, false, false);
  ylabel->setSize(width,24);

  addAndMakeVisible (yvalue = new Label (T("yvalue"), String::empty));
  yvalue->setFont (font);
  yvalue->setJustificationType (Justification::centredRight);
  yvalue->setEditable (true);
  yvalue->setColour (Label::backgroundColourId, Colours::white);
  yvalue->setBounds(xvalue->getRight()+30, 0, 60,24);
  xvalue->addListener(this);

  setSize(440,24);
}

void FocusView::updateFieldLabels() {
  String xstr=focuslayer->getFieldName(focuslayer->getXField()) + T(": ");
  String ystr=focuslayer->getFieldName(focuslayer->getYField()) + T(": ");
  xlabel->setText(xstr, false);
  xlabel->setBounds(layername->getRight()+25, xlabel->getY(),
		    xlabel->getFont().getStringWidth(xstr),
		    xlabel->getHeight());
  xvalue->setTopLeftPosition(xlabel->getRight(),xvalue->getY());
  ylabel->setText(ystr, false);
  ylabel->setBounds(xvalue->getRight()+25, ylabel->getY(),
		    ylabel->getFont().getStringWidth(ystr), 
		    ylabel->getHeight());
  yvalue->setTopLeftPosition(ylabel->getRight(), yvalue->getY());
}  
		  
FocusView::~FocusView() {
  deleteAndZero(nlabel);
  deleteAndZero(layername);
  deleteAndZero(xlabel);
  deleteAndZero(xvalue);
  deleteAndZero(ylabel);
  deleteAndZero(yvalue);
}

void FocusView::setFocusLayer(Layer * l) {
  focuslayer=l;
  plotter->getPlotView()->deselectAll();
  plotter->getPlotView()->focuslayer=l;

  plotter->setHorizontalAxis(focuslayer->getXAxis());
  plotter->setVerticalAxis(focuslayer->getYAxis());

  Colour c = l->getLayerColor();
  layername->setColour(Label::textColourId, c);
  layername->setText(l->getLayerName(), false);
  //  xlabel->setColour(Label::textColourId, c);
  //  ylabel->setColour(Label::textColourId, c);
  xvalue->setColour(Label::textColourId, c);
  yvalue->setColour(Label::textColourId, c);
  updateFieldLabels();
}


void FocusView::resized() {
}

void FocusView::labelTextChanged(Label * label) {
  String str;
  float val, min;
  if ( label->getName() == T("xvalue") ) {
    str=label->getText();
    val=str.getFloatValue(); // this really nees parsing!
    printf("float is %f\n", val);
    //plotter->plotview->moveSelection(val, Plotter::horizontal);
  }
  else if ( label->getName() == T("yvalue") ) {
  }
  else if ( label->getName() == T("layername") ) {
    // FIX: convert this to undoable rename
    focuslayer->setLayerName(label->getText());
  }
}

/***********************************************************************
 *
 * Plotter: contains all the subcomponents for plotting
 *
 **********************************************************************/

PointClipboard pointClipboard;

Plotter::Plotter (PlotType pt) 
  : ppp (8.0),
    zoom (1.0),
    flags (0)
{

  plottype=pt;
  font=Font(Font::getDefaultSansSerifFontName(), 10.0, Font::bold);
  rand=new Random(Time::currentTimeMillis());
  focusview=new FocusView(this);
  plotview=new PlotView (this);
  // cache xy buffers in plot vuew for fast updating.
  plotview->xvalue=focusview->xvalue;
  plotview->yvalue=focusview->yvalue;

  backview=new BackView(this);
  // plot view is child of backview so that it is in front
  backview->addChildComponent(plotview);
  plotview->setTopLeftPosition(0,0);
  viewport=new PlotViewport (this);

  Axis::AxisType xtyp, ytyp;
  switch (pt) {
  case MidiPlot :
    xtyp=Axis::seconds;
    ytyp=Axis::keynum;
    break;
  case XYPlot :
  default :
    xtyp=ytyp=Axis::normalized;
  }
    
  // set shared X axis and create Axis views...
  shared=new Axis(xtyp);
  haxview=new AxisView(viewport, horizontal);
  vaxview=new AxisView(viewport, vertical);

  newLayer(pt);

  addChildComponent(haxview);  
  addChildComponent(vaxview);  
  plotview->resizeForDrawing();  // calc plots width/height

  // add the backview to the viewport. the plotview is a child of the
  // backview and so it will scroll with it
  viewport->setViewedComponent(backview);
  viewport->setScrollBarsShown (true, true);
  addChildComponent(viewport);
  addChildComponent(focusview);

  xspread=new Slider(T("xspread"));
  xspread->setSliderStyle(Slider::LinearHorizontal);
  xspread->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
  xspread->addListener(this);
  xspread->setRange(-2.0, 2.0, .1);
  xspread->setValue(0.0);
  xspread->setSize(100,20);
  addChildComponent(xspread);
  yspread=new Slider(T("yspread"));
  yspread->setSliderStyle(Slider::LinearVertical);
  yspread->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
  yspread->addListener(this);
  yspread->setRange(-2.0, 2.0, .1);
  yspread->setValue(0.0);
  yspread->setSize(20,100);
  addChildComponent(yspread);
  // i was hoping that delaying visibility would limit paint() to 1
  // call but this doesnt seem to help.
  xspread->setVisible(true);
  yspread->setVisible(true);
  // scroll to origin of axis
  //this doenst work >:(
  //viewport->getVerticalScrollBar()->scrollToBottom();
  viewport->setViewPositionProportionately(0.0,1.0);
  viewport->setVisible(true);
  backview->setVisible(true);
  plotview->setVisible(true);
  focusview->setVisible(true);
  haxview->setVisible(true);
  vaxview->setVisible(true);
}

Plotter::~Plotter() {
  // zero out shared axis before deleting
  for (int i=0; i<numLayers(); i++) {
    Layer* l=getLayer(i);
    for (int j=0; j<l->getLayerArity(); j++)
      if (l->getAxis(j)==getSharedAxis()) {
	printf("unlink axis=%d\n",j); 
	l->setAxis(j, (Axis *)NULL);
      }
  }
  deleteAndZero(haxview);
  deleteAndZero(vaxview);
  deleteAndZero(xspread);
  deleteAndZero(yspread);
  deleteAndZero(plotview);
  deleteAndZero(backview);
  deleteAndZero(viewport);
  deleteAndZero(focusview);
  layers.clear(true);
  delete shared;
  delete rand;
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

void Plotter::setFocusVerticalField(int i) {
  Layer* layer=getFocusLayer();
  layer->setYField(i);
  setVerticalAxis(layer->getAxis(i));
  redrawVerticalAxisView();
  redrawPlotView();
  focusview->updateFieldLabels();
  redrawFocusView();  
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

Plotter::BGStyle Plotter::getBackViewStyle() {
  return backview->getBackViewStyle();
}

void Plotter::setBackViewStyle( BGStyle b) {
  backview->setBackViewStyle(b);
}

PlotView * Plotter::getPlotView() {
  return plotview;
}

FocusView * Plotter::getFocusView() {
  return focusview;
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

void Plotter::redrawFocusView() {
  focusview->repaint();
}


///
/// layers
///

Layer * Plotter::getLayer(int i) {
  return layers[i];
}

Layer * Plotter::findLayer(int id) {
  Layer * l;
  for (int i=0; i< layers.size(); i++) {
    l=layers[i];
    if (id == l->getLayerID()) return l;
  }
  return (Layer *)NULL;
}

int Plotter::numLayers() {
  return layers.size();
}

Layer * Plotter::getFocusLayer() {
  //return plotview->focus;
  return focusview->getFocusLayer();
}

bool Plotter::isFocusLayer(Layer * l) {
  return (l == getFocusLayer()); 
}

void Plotter::setFocusLayer(Layer * l) {
  focusview->setFocusLayer(l);
}

Layer* Plotter::newLayer(PlotType pt) {
  String nam = T("Layer") + String(layers.size()+1);
  // lets use GnuPlot's default colors:
  static Colour cols[8] = { Colours::red, Colours::green, Colours::blue, 
			    Colours::magenta, Colours::cyan, Colours::sienna,
			    Colours::orange, Colours::coral};
  Colour col = cols[layers.size() % 8];
  Layer * layer;

  if (pt==MidiPlot)
    layer = new MidiLayer(nam,col);
  else 
    layer = new XYLayer(nam,col);
  addLayer(layer);
  return layer;
}

void Plotter::addLayer(Layer* layer) {
  // axis[0] unfilled axis will be set to Plotter's shared axis
  for (int i=0; i < layer->getLayerArity(); i++)
    if (layer->getAxis(i) == (Axis *)NULL) {
      printf("axis[%d]=shared\n", i);
	layer->setAxis(i, getSharedAxis());
    }
  layers.add(layer);
  setFocusLayer(layer);
}

void Plotter::removeLayer(Layer* layer) {
  // THIS CHECK SHOULDNT BE NECESSARY (MENU CHECKS)
  if ( numLayers() < 2 ) return;
  // if removing focus layer then switch focus to other layer.
  if ( isFocusLayer(layer) ) {
    for (int i=0; i<numLayers(); i++) {
      Layer* l=getLayer(i);
      if (l != layer) {
	setFocusLayer(l);
	break;
      }
    }
  }
  for (int i=0; i<layer->getLayerArity(); i++)
    if (layer->getAxis(i) == getSharedAxis()) 
      layer->setAxis(i, (Axis *)NULL);
  layers.removeObject(layer,false);
}

void Plotter::selectAll() {
  getPlotView()->selectAll();
}

void Plotter::deselectAll() {
  getPlotView()->deselectAll();
}

///
/// plotter gui
///

void Plotter::resized () {
  xspread->setCentrePosition(getWidth()/2, getHeight()-20);
  yspread->setCentrePosition(getWidth()-20, getHeight()/2);
  // insets: left=60 top=60 right=40 bottom=40 (scrollers take 20)
  viewport->setBounds(60, 60, getWidth()-100, getHeight()-150);

  haxview->setBounds(60, 30, viewport->getViewWidth(), 26); 
  vaxview->setBounds(30, 60, 26, viewport->getViewHeight());
  focusview->setBounds(30, viewport->getBottom()+4,
		       viewport->getWidth()+34, // axis+spacer
		       focusview->getHeight());
}

/// Spread slider

void Plotter::sliderDragStarted (Slider *slider) {
  // turn off image caching while slider is moving to speed up the
  // continuous drawing.  perhaps this should turn off back plot
  // drawing altogether and just show the focus plot and grid?
  getBackView()->setBackViewCaching(false);
}

void Plotter::sliderDragEnded (Slider *slider) {
  getBackView()->setBackViewCaching(true);
}

void Plotter::sliderValueChanged (Slider *slider) {
  double z = pow(2.0, slider->getValue());
  String name = slider->getName();

  if ( name == T("xspread") )
    haxview->setSpread(z);
  else
    vaxview->setSpread(z);
  plotview->resizeForDrawing();
  // now have to update the size of the Axis' view -- this is NOT the
  // size of the axis! Note that if spread has gotten larger then the
  // size of the axis view doenst actually change, in which case we
  // have to force a repaint to see the axis content drawn at the new
  // spread.
  if ( name == T("xspread") ) {
    int old=getWidth();
    haxview->setSize(viewport->getViewWidth(), haxview->getHeight());
    if (old==getWidth()) 
      haxview->repaint();
  }  
  else {
    int old=getHeight();
    vaxview->setSize(vaxview->getWidth(), viewport->getViewHeight()) ;
    if (old==getHeight()) 
      vaxview->repaint();
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

/***********************************************************************
 * Actions
 **********************************************************************/

class DeleteLayerAction : public UndoableAction {
  // this should probably only be applicable on the focus layer

  Layer* layer;
  Plotter* plotter;
public:
  DeleteLayerAction(Plotter* p, Layer* l) {
    plotter=p;
    layer=l;
  }
  ~DeleteLayerAction() {delete layer;}
  bool perform() {
    // plotter must hold (at least) 1 layer.
    if (plotter->numLayers() == 1) return false;
    plotter->removeLayer(layer);
    plotter->redrawBackView();
    plotter->redrawPlotView();
    return true;
  }
  bool undo () {
    plotter->addLayer(layer);
    plotter->redrawBackView();
    plotter->redrawPlotView();
    return true;
  }
  int getSizeInUnits(){return 1;}
};

class RenameLayerAction : public UndoableAction {
  String name;
  Layer* layer;
  Plotter* plotter;
  void rename() {
    String s=layer->getLayerName();
    layer->setLayerName(name);
    if ( plotter->isFocusLayer(layer) )
      plotter->getFocusView()->setNameBuffer(name);
    name=s;   // cache old name
  }
public:
  RenameLayerAction(Plotter* p, Layer* l, String n) {
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



/***********************************************************************
 * PlotterWindow: top level window for plotting
 **********************************************************************/

const StringArray PlotterWindow::getMenuBarNames () {
  const tchar* 
    const menuNames[] = { T("Plotter"), T("Edit"), T("Layer"), T("View"), 
			  // T("Compose"),T("Analyze"),
			  T("Windows"), T("Help"), 0 };
  return StringArray((const tchar**) menuNames);
}

const PopupMenu PlotterWindow::getMenuForIndex (int idx, 
						const String &name) {
  PopupMenu menu;
  PopupMenu sub1, sub2, sub3;
  int val;
  PlotType type=plotter->getPlotType();
  switch (idx) {
  case 0 :
    // File Menu
    sub1.addItem( Plotter::cmdPlotterNew + XYPlot, T("XY"));
    sub1.addItem( Plotter::cmdPlotterNew + MidiPlot, T("Midi"));
    sub1.addItem( Plotter::cmdPlotterNew + VKeyPlot, T("Fomus"), false);
    sub1.addItem( Plotter::cmdPlotterNew + FomusPlot, T("Vkey"), false);
    sub1.addItem( Plotter::cmdPlotterNew + SpearPlot, T("Spear"), false);
    sub1.addItem( Plotter::cmdPlotterNew + CLMPlot, T("CLM"), false);
    menu.addSubMenu(T("New"), sub1, true);    
    menu.addItem( Plotter::cmdPlotterOpen, T("Open..."), false);
    menu.addItem( Plotter::cmdPlotterSave, T("Save"), false);
    menu.addItem( Plotter::cmdPlotterImport, T("Import..."), false);
    menu.addItem( Plotter::cmdPlotterExport, T("Export..."), true);
    break;
  case 1 :
    // Edit Menu
    menu.addItem( Plotter::cmdEditUndo, T("Undo"),
		  plotter->actions.canUndo());
    menu.addItem( Plotter::cmdEditUndo, T("Redo"),
		  plotter->actions.canRedo());
    menu.addSeparator();
    menu.addItem( Plotter::cmdEditCut, T("Cut"));
    menu.addItem( Plotter::cmdEditCopy, T("Copy"));
    menu.addItem( Plotter::cmdEditPaste, T("Paste"),
		  !pointClipboard.isEmpty());
    menu.addSeparator();
    menu.addItem( Plotter::cmdEditSelectAll, T("Select All"));
    menu.addItem( Plotter::cmdEditClear, T("Clear Selection"));
    menu.addSeparator();
    menu.addItem( Plotter::cmdEditFind, T("Find..."), false);
    break;
  case 2 :
    // Layer Menu
    if (type == MidiPlot) {
      sub1.addItem( Plotter::cmdLayerAdd + MidiPlot, T("Midi"));
      sub1.addItem( Plotter::cmdLayerAdd + MidiPlot, T("Program Change"),
		    false);
      sub1.addItem( Plotter::cmdLayerAdd + MidiPlot, T("Controller"), 
		    false);
      menu.addSubMenu(T("Add"), sub1, true);          
    }
    else menu.addItem( Plotter::cmdLayerAdd + type, T("New"));
    menu.addItem(Plotter::cmdLayerDelete, T("Delete"),
		 (plotter->numLayers() > 1));
    menu.addSeparator(); 
    // append existing layers to end of menu in plotting color :)
    for (int i=0; i<plotter->numLayers(); i++) {
      Layer * layer=plotter->getLayer(i);
      menu.addColouredItem( Plotter::cmdLayerSelect + layer->getLayerID(),
			    layer->getLayerName(),
			    layer->getLayerColor(),
			    true,
			    plotter->isFocusLayer(layer));
	}
    break;
  case 3 :
    {
      Layer * layer=plotter->getFocusLayer();
      // add these with focus colored items to make it clear that the
      // styling change only affects the focus plot
      menu.addColouredItem( Plotter::cmdViewStyle + Layer::line, T("Line"),
			    layer->getLayerColor(),
			    true, (val==Layer::line));
      menu.addColouredItem( Plotter::cmdViewStyle + Layer::point, T("Point"),
			    layer->getLayerColor(),
			    true, (val==Layer::point));
      menu.addColouredItem( Plotter::cmdViewStyle + Layer::lineandpoint,
			    T("Line and Point"),
			    layer->getLayerColor(),
			    true, (val==Layer::lineandpoint));
      menu.addColouredItem( Plotter::cmdViewStyle + Layer::hbox, 
			    T("Horizontal Box"),
			    layer->getLayerColor(),
			    (type > XYPlot), (val==Layer::hbox));
      menu.addColouredItem( Plotter::cmdViewStyle + Layer::vline, 
			    T("Vertical Line"),
			    layer->getLayerColor(),
			    true, (val==Layer::vline));
      menu.addColouredItem( Plotter::cmdViewStyle + Layer::vlineandpoint, 
			    T("Vertical Line and Point"),
			    layer->getLayerColor(),
			    true, (val==Layer::vlineandpoint));
      menu.addColouredItem( Plotter::cmdViewStyle + Layer::vbar, 
			    T("Vertical Bar"),
			    layer->getLayerColor(),
			    false, (val==Layer::vbar));
      menu.addSeparator(); 
      // 0'th field is hardwired to x axis.
      for (int i=1; i<layer->getLayerArity(); i++)
	sub2.addItem( Plotter::cmdViewVertical + i,
		      layer->getFieldName(i),
		      true,
		      (layer->getYField()==i));
      menu.addSubMenu(T("Vertical Display"), sub2, true);
    }
    menu.addSeparator();
    val=plotter->getBackViewStyle();
    sub1.addItem( Plotter::cmdViewBgStyle + Plotter::bgGrid, T("Grid"),
		  true, (val==Plotter::bgGrid));
    sub1.addItem( Plotter::cmdViewBgStyle + Plotter::bgTiled, T("Tiled"),
		  true, (val==Plotter::bgTiled));
    sub1.addItem( Plotter::cmdViewBgStyle + Plotter::bgSolid, T("Solid"),
		  true, (val==Plotter::bgSolid));
    sub1.addSeparator();
    sub1.addItem( Plotter::cmdViewBgColor, T("Colors..."), false);
    sub1.addSeparator();
    sub1.addItem( Plotter::cmdViewBgPlotting, T("Show All Layers"), true, 
		  plotter->isBackViewPlotting() );
    sub1.addItem( Plotter::cmdViewBgMousing, T("Back Layer Mousing"), 
		  false, false);
    menu.addSubMenu(T("Background"), sub1, true);    
    menu.addSeparator();
    menu.addItem( Plotter::cmdViewMouseGuide, T("Mouse Guide"), false);
    break;
    /*  case 4 :
    menu.addItem( Plotter::cmdComposeDistributions, T("Distributions..."),
		  false);
    menu.addItem( Plotter::cmdComposeGenerate, T("Generate..."), 
		  false);
    break;
  case 5 :
    menu.addItem( Plotter::cmdAnalyzeHistogram, T("Histogram..."), false);
    menu.addItem( Plotter::cmdAnalyzeDeviation, T("Deviation..."), false);
    break;
    */
  case 4 :
    addCommonWindowItems(&menu, winPlotter);
    break;
  case 5 :
    addCommonHelpItems(&menu, winPlotter);
    break;
  }
  return menu;
}

void PlotterWindow::menuItemSelected (int id, 
				      int idx) {
  // commandIDs reserve lower 8 bits for command-specific information
  // lower seven bits may encode command information
  int arg = id & 0x0000007F;
  int cmd = id & 0xFFFFFF80;
  bool tog;
  switch (cmd) {
  case Plotter::cmdPlotterNew :
    new PlotterWindow( (PlotType)arg);
    break;
  case Plotter::cmdPlotterOpen :
  case Plotter::cmdPlotterSave :
  case Plotter::cmdPlotterSaveAs :
  case Plotter::cmdPlotterImport :
    break;
  case Plotter::cmdPlotterExport :
    showExportPointsDialog();
    break;
  case Plotter::cmdEditUndo :
    plotter->actions.undo();
    break;
  case Plotter::cmdEditRedo :
    plotter->actions.redo();
    break;
  case Plotter::cmdEditCut :
  case Plotter::cmdEditCopy :
  case Plotter::cmdEditPaste :
    break;
  case Plotter::cmdEditSelectAll :
    printf("menu selectall\n");
    plotter->selectAll();
    plotter->redrawPlotView();
    break;
  case Plotter::cmdEditClear :
    plotter->deselectAll();
    plotter->redrawPlotView();
    break;
  case Plotter::cmdEditFind :
    break;
  case Plotter::cmdLayerAdd :
    plotter->newLayer( (PlotType)arg);
    // redraw back view to include old
    plotter->redrawBackView();
    break;
  case Plotter::cmdLayerDelete :
    plotter->actions.perform
      (new DeleteLayerAction(plotter,
			     plotter->getFocusLayer()),
       T("Delete Layer"));
    break;
  case Plotter::cmdLayerSelect :
    plotter->setFocusLayer(plotter->findLayer(arg));
    plotter->redrawBackView();
    plotter->redrawPlotView();
    break;
  case Plotter::cmdViewStyle :
    plotter->getFocusLayer()->setLayerStyle(arg);
    plotter->redrawPlotView();
    break;
  case Plotter::cmdViewVertical :
    plotter->setFocusVerticalField(arg);
    break;
  case Plotter::cmdViewBgStyle :
    plotter->setBackViewStyle( (Plotter::BGStyle)arg);
    plotter->redrawBackView();
    break;
  case Plotter::cmdViewBgColor :
    break;
  case Plotter::cmdViewBgPlotting :
    plotter->setBackViewPlotting( ! plotter->isBackViewPlotting()); 
    plotter->redrawBackView();
    break;
  case Plotter::cmdViewBgMousing :
  case Plotter::cmdViewMouseGuide :
  default :
    if (idx==4)
      commonWindowItemSelected(cmd,arg);
    else if (idx==5)
      commonHelpItemSelected(cmd,arg);
    break;
  }
}

PlotterWindow::PlotterWindow (PlotType pt)
  : DocumentWindow (String::empty , Colours::silver, 
		    DocumentWindow::allButtons, true ) {
  String title;

  plotter = new Plotter( pt ) ;
  menubar = new MenuBarComponent(this);
  setMenuBar(this);

  GracePreferences* p=GracePreferences::getInstance();
  setUsingNativeTitleBar(p->isNativeTitleBars());

  switch (pt) {
  case MidiPlot :
    title = T("MIDI Plotter");
    break;
  case XYPlot :
  default:
    title = T("Plotter");    
  }
  setName(title);
  setContentComponent(plotter);
  plotter->setSize(510,580);
  plotter->setVisible(true);
  centreWithSize (510, 580);
  setResizable(true, true); 
  setVisible(true);
}

PlotterWindow::~PlotterWindow () {
  plotter->~Plotter();
}

void PlotterWindow::closeButtonPressed () {
  this->~PlotterWindow();
}

 
//
// Export Dialog
//


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
  formatmenu->addItem(T("Object Definitions"), 3);
  formatmenu->addItem(T("Pattern Definitions"), 4);
  formatmenu->addItem(T("Process Definition"), 5);
  formatmenu->setItemEnabled(4, false);
  formatmenu->setItemEnabled(5, false);

  // default export for XY is envelope else objects
  if (plotter->getPlotType()==XYPlot) {
    formatmenu->setSelectedId(1);
    formatmenu->setItemEnabled(3, false); 
  }
  else 
    formatmenu->setSelectedId(3);

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
    int i;
    PopupMenu m;
    for (i=0; i<numfields; i++)
      m.addItem(i+1, plotter->getFocusLayer()->getFieldName(i),
		true, include[i]);
    i=m.showAt(button);
    if (i != 0) include[i-1]=(!include[i-1]);
  }
}

void PlotterWindow::showExportPointsDialog () {
  DialogWindow::showModalDialog(T("Export Points to Clipboard"),
				new ExportPointsDialog(plotter),
				this,
				Colour(0xffe5e5e5),
				true);
}
