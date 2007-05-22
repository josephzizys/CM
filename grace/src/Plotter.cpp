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
/// Axis methods
///

void AxisView::init (AxisType typ) {
  // init axis data according to common "templates"
  logr = false;
  switch (typ) {
  case percentage :
    from=0.0; to=100.0; by=25.0; ticks=5;
    break;
  case keynum :
  case mididata :
    from=0.0; to=128; by=12.0; ticks=12;
    break;
  case seconds :
    from=0.0; to=60.0; by=1.0; ticks=4;
    break;
  case frequency :  // linear freq
    from=0.0; to=11025.0; by=1.0; ticks=2;
    break;
  case hertz :  // log freq
    from=8.175798; to=16744.035; by=2.0; ticks=6; logr=true;
    break;
  case unitcircle :
    from=-1.0; to=1.0; by=.25;
  case normalized :
  case amplitude :
  default :
    from=0.0; to=1.0; by=0.25; ticks=5;
    break;
  }
}

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
  double pval=offset; 
  double aval=from;   
  double save;

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
      labl=String(aval,decimals);
      lwid=font.getStringWidthFloat(labl);
      just=(int)(-lwid*(pval/width));  // twiddle label justification
      g.drawText(labl,(int)(pval+just),0,(int)lwid,(int)lhei, 
		 Justification::topLeft, false);
      // draw minor ticks above each major tick
      g.setColour(col2);
      for (int i=1;i<ticks;i++)
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
     labl=String(aval,decimals);
     lwid=font.getStringWidthFloat(labl);

     // METHOD1: justify vertically, but now the view has to be wider.
     just=(int)(lhei*(pval/height));  // twiddle label justification
     g.drawText(labl, 0, (int)(pval-just),(int)lwid,(int)lhei,
		Justification::topLeft, false);

     // METHOD2: rotate 90 and then jusitfy width like th X
     // axis. arrrrrgghh i cant figure this out!!

     // g.drawTextAsPath(labl, AffineTransform::identity.rotated(float_Pi*2*-.25,width,pval));

     g.setColour(col2);
     for (int i=1;i<ticks;i++)
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
 * FocusView: controls for working with the top-most (focus) plot
 *
 **********************************************************************/

class FocusView  : public Component,
                   public ComboBoxListener,
		   public LabelListener {
public:
  Plotter * plotter;
  Layer * focuslayer;
  ComboBox* layerMenu;
  Label* xlabel;
  Label* xvalue;
  Label* ylabel;
  Label* yvalue;

  FocusView (Plotter * p);
  ~FocusView();

  void setFocusLayer(Layer * l);
  Layer * getFocusLayer() { return focuslayer;}
  void resized();
  void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
  void labelTextChanged(Label * label);

  //  juce_UseDebuggingNewOperator
  //  FocusView (const FocusView&);
  //  const FocusView& operator= (const FocusView&);

  //void setSelectionPoint(float x, float y);
  
};

FocusView::FocusView (Plotter * p)
  : plotter (0),
    focuslayer (0),
    layerMenu (0),
    xlabel (0),
    xvalue (0),
    ylabel (0),
    yvalue (0) {
  plotter=p;
  Font font=Font( 14.0, Font::bold);
  int width=font.getStringWidth(T("X:"));

  addAndMakeVisible (layerMenu = new ComboBox (String::empty));
  layerMenu->setEditableText (true);
  layerMenu->setJustificationType (Justification::centredLeft);
  layerMenu->setTextWhenNothingSelected (String::empty);
  layerMenu->setTextWhenNoChoicesAvailable (T("(no choices)"));
  layerMenu->addListener (this);
  layerMenu->setBounds (0, 0, 100, 24);

  addAndMakeVisible (xlabel = new Label (T("xlabel"), T("X:")));
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
  xvalue->setBounds(130, 0, 60, 24);
  xvalue->addListener(this);
  xlabel->attachToComponent(xvalue, true);

  addAndMakeVisible (ylabel = new Label (String::empty, T("Y:")));
  ylabel->setFont(font);
  ylabel->setJustificationType (Justification::centredRight);
  ylabel->setColour (Label::backgroundColourId, Colour(230, 230, 0xff) );
  ylabel->setEditable (false, false, false);
  ylabel->setSize(width,24);

  addAndMakeVisible (yvalue = new Label (T("yvalue"), T("1000.00")));
  yvalue->setFont (font);
  yvalue->setJustificationType (Justification::centredRight);
  yvalue->setEditable (true);
  yvalue->setColour (Label::backgroundColourId, Colours::white);
  yvalue->setBounds(220, 0, 60,24);
  xvalue->addListener(this);
  ylabel->attachToComponent(yvalue, true);

  setSize(440,24);
}

FocusView::~FocusView() {
  deleteAndZero (layerMenu);
  deleteAndZero (xlabel);
  deleteAndZero (xvalue);
  deleteAndZero (ylabel);
  deleteAndZero (yvalue);
}

void FocusView::setFocusLayer(Layer * l) {
  focuslayer=l;
  Colour c = l->getLayerColor();
  layerMenu->setSelectedId(l->getLayerID(), true);
  layerMenu->setColour(ComboBox::textColourId, c);
  layerMenu->setText(l->getLayerName(), true);  

  xlabel->setColour(Label::textColourId, c);
  ylabel->setColour(Label::textColourId, c);
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
    min=


  }
  else {
  }
}

void FocusView::comboBoxChanged (ComboBox* m) {
  Layer * foc = getFocusLayer();
  int sid=m->getSelectedId();  // item id = layer's id
  if (m == layerMenu) {
    if (sid==0) {
      // renamed the current layer.
      int fid = foc->getLayerID();
      foc->setLayerName(m->getText());  // rename layer
      // rename layer's associated item in menu...
      for (int i=0;i<m->getNumItems(); i++)
	if (m->getItemId(i) == fid) {
	  m->changeItemText(fid,m->getText());
	  break;
	}
    }
    else {
      plotter->setFocusLayer(plotter->findLayer(sid));
      plotter->redrawBackView();
      plotter->redrawPlotView();
    }
  }
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

void drawLayer(Graphics& g, Layer * layer, AxisView * xaxis, AxisView * yaxis, 
	       double ppp, double zoom, bool isFoc, SelectedItemSet<int> * sel);

void drawGrid(Graphics& g, AxisView * xaxis, AxisView * yaxis, 
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

  void paint (Graphics& g) {
    printf("BACKPLOT PAINTING\n");
    g.fillAll(bgcolors[0]);
    AxisView * xaxis = plotter->getAxisView(Plotter::horizontal);
    AxisView * yaxis = plotter->getAxisView(Plotter::vertical);
    Layer * layer;

    // draw background grid
    if (bgstyle==Plotter::bgGrid)
      drawGrid(g, xaxis, yaxis, bgcolors[2], bgcolors[3]);
    else if (bgstyle==Plotter::bgTiled)
      g.fillCheckerBoard((int)xaxis->offset,
			 (int)(yaxis->offset-yaxis->size()),
			 (int)xaxis->size(), 
			 (int)yaxis->size(),
			 (int)xaxis->tickSize(), 
			 (int)yaxis->tickSize(),
			 bgcolors[4],bgcolors[5]);
    else g.fillAll(bgcolors[1]);

    // draw non-focus plots
    if ( isBackViewPlotting() ) {
      double psize=plotter->getPointSize();
    for (int i=0; i < plotter->numLayers(); i++) {
      layer = plotter->getLayer(i);
      if (! plotter->isFocusLayer(layer) ) 
	drawLayer(g, layer, xaxis, yaxis, psize, 1.0, false, 
		  (SelectedItemSet<int> *)NULL);
      }
    }
  }

  ~BackView () {};
};

class PlotView : public Component {
 public:
  Plotter * plotter;
  BackView * backview;
  double pad; // pix per inc, pix per point, margin pad
  Point mousedown, mousemove;
  SelectedItemSet<int> selection;
  Region region;

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
  double visibleValueLeft(){return xaxis->toValue(visiblePixelLeft());}
  double visibleValueRight(){return xaxis->toValue(visiblePixelRight());}
  double visibleValueTop(){return yaxis->toValue(visiblePixelTop()); }
  double visibleValueBottom(){return yaxis->toValue(visiblePixelBottom());}
  */
  bool isSelection() {return (selection.getNumSelected() > 0);}
  int numSelected() {return selection.getNumSelected();}
  bool isSelected(int h) {return selection.isSelected(h);}
  void clearSelection() {selection.deselectAll();}
  void removeSelection(int h) {selection.deselect(h);}
  void setSelection(int h) {selection.selectOnly(h);}
  void addSelection(int h) {selection.addToSelection(h);}
  int getSelected(int i) {return selection.getSelectedItem(i);}
  void moveSelection(int orient, float val);
  void incSelection(int orient, float val);
  float getSelectionMin(int orient);
  float getSelectionMax(int orient);

  bool isInside(float x, float y, float left, float top,
		float right, float bottom);

  // this shuold be a layer method...
  void selectPointsInside(float left, float top, float right, float bottom) ;

  void printSelection() {
    printf("#<Selection:");
    for (int i=0;i<numSelected(); i++) printf(" %d", getSelected(i));
    printf(">\n");
  }
};

float PlotView::getSelectionMin(int orient) {
  Layer * layer = plotter->getFocusLayer();
  numeric_limits<float> info;
  float (Layer::*getter)( int) ;
  float lim=info.max();

  if (orient == Plotter::horizontal)
    getter = &Layer::getPointX;
  else 
    getter = &Layer::getPointY;

  for (int i = 0; i< numSelected(); i++) {
    int h = getSelected(i);
    lim=jmin( lim, (layer->*getter) (i) );
  }
  return lim;
}
  
void PlotView::resizeForDrawing() {
  // called when zoom value changes to reset total size of plotting view
  double xsiz, ysiz, xtot, ytot;
  AxisView * xaxis=plotter->getAxisView(Plotter::horizontal);
  AxisView * yaxis=plotter->getAxisView(Plotter::vertical);
  // xpad and ypad are margins around the plotting area so points at
  // then edge aren't clipped
  xsiz=xaxis->size();
  ysiz=yaxis->size();
  xtot=pad+xsiz+pad;
  ytot=pad+ysiz+pad;
  xaxis->offset=pad;
  yaxis->offset=ytot-pad;
  setSize( (int)xtot, (int)ytot );
}

void drawLayer(Graphics& g, Layer * layer, AxisView * xaxis, AxisView * yaxis, 
	       double ppp, double zoom, bool isFoc, SelectedItemSet<int> * sel) {
  double half=ppp/2;
  double ax, ay, px, py, lx, ly, ox, oy;
  Colour color, selcolor= Colours::grey;
  int ndraw;
  bool fillp=true;
  //printf("visible left=%f, right=%f\n", visibleValueLeft(), visibleValueRight());
  color=layer->color;
  ndraw=layer->numPoints();

  // need pixel origins for vert/horiz lines/bars
  if (yaxis->from < 0.0 && yaxis->to >= 0.0)
    oy=yaxis->toPixel(0.0);
  else oy=yaxis->toPixel(yaxis->from);

  if (xaxis->from < 0.0 && xaxis->to >= 0.0)
    ox=xaxis->toPixel(0.0);
  else ox=xaxis->toPixel(xaxis->from);

  g.setColour(color);
  for (int i=0; i<ndraw; i++) {
    ax=layer->getPointX(i);  
    ay=layer->getPointY(i);  
    px=xaxis->toPixel(ax);   // pixel coords
    py=yaxis->toPixel(ay);

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
      if ( isFoc && sel->isSelected(i) ) {
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
      double az=ax + layer->getPointZ(i);  
      double pz = (int)xaxis->toPixel(az);
      // draw selected boxes gray if moving
      if ( isFoc && sel->isSelected(i) ) {
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
  Layer * focus=plotter->getFocusLayer();
  drawLayer(g, plotter->getFocusLayer(), 
	    plotter->getAxisView(Plotter::horizontal),
	    plotter->getAxisView(Plotter::vertical),
	    plotter->getPointSize(),
	    1.0,
	    true,
	    &selection);
}

void drawGrid(Graphics& g, AxisView * xaxis, AxisView * yaxis, 
	      Colour c1, Colour c2) {
  double left=xaxis->offset;
  double right=left+xaxis->size();
  double bottom=yaxis->offset;
  double top=bottom-yaxis->size();
  double v,p,t,d;
  //std::cout << "drawgrid "<<left<<" "<<top<<" "<<bottom<<" "<<right<<"\n";
  p=xaxis->offset;
  d=xaxis->incrementSize();
  t=xaxis->tickSize();
  while (p <= right) {
    g.setColour(c1);
    g.drawVerticalLine((int)p, top, bottom);
    g.setColour(c2);
    for (int i=1;i<xaxis->ticks;i++) 
      g.drawVerticalLine((int)(p+(t*i)), top, bottom);
    p += d;
  }
  p=yaxis->offset;
  d=yaxis->incrementSize();
  t=yaxis->tickSize();
  while (p >= top) {
    g.setColour(c1);
    g.drawHorizontalLine((int)p, left, right);
    g.setColour(c2);
    for (int i=1;i<yaxis->ticks;i++) 
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
  Layer * focus=plotter->getFocusLayer();
  //printf("looking in region: left=%f top=%f, right=%f, bottom=%f\n",x1, y2, x2, y1);
  //clearSelection();
  for (int i=0; i<focus->numPoints(); i++) {
    double x=focus->getPointX(i);
    double y=focus->getPointY(i);
    if ( isInside(x, y, left, top, right, bottom) ) {
      addSelection(i);
    }
    else if (x > right) break; // stop looking
  }
}

void PlotView::mouseDown (const MouseEvent &e) {
  Layer * focus=plotter->getFocusLayer();
  // shoudnt happen
  if (focus==(Layer *)NULL) return;

  int mxp=e.getMouseDownX();
  int myp=e.getMouseDownY();
  AxisView * xaxis=plotter->getAxisView(Plotter::horizontal);
  AxisView * yaxis=plotter->getAxisView(Plotter::vertical);

  // cache mouse down position  FIX THIS ISNT NEEDED
  mousedown.setXY(mxp, myp);
  mousemove.setXY(mxp, myp);
  
  // Control-Click: add point make selection
  // Control-Shift-Click: add point add selection.
  if ( e.mods.isCtrlDown() ) {
    int i = focus->addPoint(xaxis->toValue(mxp),
			    yaxis->toValue(myp));
    if ( e.mods.isShiftDown() )
      addSelection( i);
    else setSelection(i);
    repaintFocusPlot();
    return;
  }

  double half=plotter->getPointSize()/2;
  int point=-1;
  double left, top, right, bottom, x, y;

  if ( focus->isDrawStyle(Layer::hbox) ) {
    // speed: since box height is constant check point y againt a
    // (constant) vertical box height centered on mouse y
    top=yaxis->toValue( myp - half);
    bottom=yaxis->toValue( myp + half);
    x=xaxis->toValue( mxp);
    for (int i=0; i < focus->numPoints(); i++) {
      left=focus->getPointX(i);
      right=left+focus->getPointZ(i);
      y=focus->getPointY(i);
      if ( isInside(x, y, left, top, right, bottom) ) {
	point=i;
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
    left=xaxis->toValue( mxp - half);
    top=yaxis->toValue( myp - half);
    right=xaxis->toValue( mxp + half);
    bottom=yaxis->toValue( myp + half);

    for (int i=0; i < focus->numPoints(); i++) {
      x=focus->getPointX(i);
      y=focus->getPointY(i);
      if ( isInside(x, y, left, top , right, bottom) ) {
	point=i;
	break;
      } 
      // give up when points are rightward of mouse x
      else if (x > right) 
	break;
    }
  }

  if ( point<0 ) {
    // Mouse down on empty space . Add to selection if shift is down
    if ( isSelection() ) {
      if ( ! e.mods.isShiftDown() ) {
	clearSelection();
	repaintFocusPlot();
      }
    }
    addChildComponent (&region);
    region.beginSweep(e, xaxis, yaxis);
  }
  else if ( isSelected(point) ) {
    // point is already selected.
    // Mouse-shift-click remove Point from selection
    if ( e.mods.isShiftDown() ) {
      removeSelection(point);
      repaintFocusPlot();
    }
  }
  else {
    // point is not selected.
    // Mouse-Click: set point as (single) selection
    // Mouse-shift-click:   add Point from selection
    if ( e.mods.isShiftDown() ) 
      addSelection(point);
    else setSelection(point);
    repaintFocusPlot();
  }
}

void PlotView::mouseDrag(const MouseEvent &e) {
  Layer * focus=plotter->getFocusLayer();
  AxisView * xaxis=plotter->getAxisView(Plotter::horizontal);
  AxisView * yaxis=plotter->getAxisView(Plotter::vertical);
  
  if ( isSelection() ) {
    float dx=xaxis->toValue(e.x) - xaxis->toValue(mousemove.getX()) ;
    float dy=yaxis->toValue(e.y) - yaxis->toValue(mousemove.getY()) ;
    for (int i=0; i<numSelected(); i++)
      focus->incPoint( getSelected(i), dx, dy);
    repaintFocusPlot();
    mousemove.setXY(e.x,e.y);
  } 
  else {
    region.toFront(false);
    region.sweep(e);
  }
}

void PlotView::mouseUp(const MouseEvent &e) {
  Layer * focus=plotter->getFocusLayer();
  if ( isSelection() ) {
    if (mousedown.getX() != mousemove.getX() ) {
      printf("sorting after move\n");
      focus->sortPoints(&selection);
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
 * Plotter: contains all the subcomponents for plotting
 *
 **********************************************************************/

Plotter::Plotter (PlotType pt) 
  : ppp (8.0),
    zoom (1.0),
    flags (0)
{
  Colour cols[8] = { Colours::red, Colours::green, Colours::blue, 
		     Colours::magenta, Colours::cyan, Colours::sienna,
		     Colours::orange, Colours::coral};

  plottype=pt;
  font=Font(Font::getDefaultSansSerifFontName(), 10.0, Font::bold);
  rand=new Random(Time::currentTimeMillis());
  focusview=new FocusView(this);
  plotview=new PlotView (this);
  backview=new BackView(this);
  // plot view is child of backview so that it is in front
  backview->addChildComponent(plotview);
  plotview->setTopLeftPosition(0,0);
  viewport=new PlotViewport (this);

  AxisView::AxisType xtyp, ytyp;
  switch (pt) {
  case MidiPlot :
    xtyp=AxisView::seconds;
    ytyp=AxisView::keynum;
    break;
  case XYPlot :
  default :
    xtyp=ytyp=AxisView::normalized;
  }
    
  // set axis views...
  setAxisView( new AxisView(xtyp), horizontal );
  setAxisView( new AxisView(ytyp), vertical );

  // HACK: cobble up some demo layers.
  for (int i=0; i<3; i++) {
    String nam = T("Layer") + String(layers.size()+1);
    Colour col = cols[layers.size() % 8];
    if (pt==MidiPlot)
      addLayer( new MidiLayer(nam,col) );
    else 
      addLayer( new XYLayer(nam,col) );
  }

  addChildComponent(xaxis);  
  addChildComponent(yaxis);  
  plotview->resizeForDrawing();  // calc plots width/height

  // add the backview to the viewport. the plotview is a child of the
  // backview and so it will scroll with it
  viewport->setViewedComponent(backview);
  viewport->setScrollBarsShown (true, true);
  addChildComponent(viewport);
  addChildComponent(focusview);

  xzoom=new Slider(T("xzoom"));
  xzoom->setSliderStyle(Slider::LinearHorizontal);
  xzoom->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
  xzoom->addListener(this);
  xzoom->setRange(-2.0, 2.0, .1);
  xzoom->setValue(0.0);
  xzoom->setSize(100,20);
  addChildComponent(xzoom);
  yzoom=new Slider(T("yzoom"));
  yzoom->setSliderStyle(Slider::LinearVertical);
  yzoom->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
  yzoom->addListener(this);
  yzoom->setRange(-2.0, 2.0, .1);
  yzoom->setValue(0.0);
  yzoom->setSize(20,100);
  addChildComponent(yzoom);
  // i was hoping that delaying visibility would limit paint() to 1
  // call but this doesnt seem to help.
  xzoom->setVisible(true);
  yzoom->setVisible(true);
  // scroll to origin of axis
  //this doenst work >:(
  //viewport->getVerticalScrollBar()->scrollToBottom();
  viewport->setViewPositionProportionately(0.0,1.0);
  viewport->setVisible(true);
  backview->setVisible(true);
  plotview->setVisible(true);
  focusview->setVisible(true);
  xaxis->setVisible(true);
  yaxis->setVisible(true);
}

Plotter::~Plotter() {
  deleteAndZero(xaxis);
  deleteAndZero(yaxis);
  deleteAndZero(xzoom);
  deleteAndZero(yzoom);
  deleteAndZero(plotview);
  deleteAndZero(backview);
  deleteAndZero(viewport);
  deleteAndZero(focusview);
  layers.clear(true);
  delete rand;
}

///
/// Component View Accessing 
///

AxisView * Plotter::getAxisView(Orientation o) {
  if (o == horizontal) return xaxis;
  else return yaxis;
}

void Plotter::setAxisView (AxisView * a, Orientation o) {
  // add axis to plotter (and to its plotview as well).
  a->viewport=this->viewport;
  a->orient=o;
  if ( o==vertical )
    yaxis=a;
  else if ( o==horizontal )
    xaxis=a;
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
  plotview->clearSelection();  // flush any selection
  focusview->setFocusLayer(l);
}

void Plotter::addLayer(Layer * l) {
  layers.add(l);
  // HACK cobble up some points for demo!
  for (int i=0;i<=20; i++) 
    l->addPoint(xaxis->from + (rand->nextFloat() * xaxis->range()),
		yaxis->from + (rand->nextFloat() * yaxis->range()));

  focusview->layerMenu->addItem(l->getLayerName(),
				l->getLayerID());
  // make new plot the focus plot
  setFocusLayer(l);
}

///
/// plotter gui
///

void Plotter::resized () {
  xzoom->setCentrePosition(getWidth()/2, getHeight()-20);
  yzoom->setCentrePosition(getWidth()-20, getHeight()/2);
  // insets: left=60 top=60 right=40 bottom=40 (scrollers take 20)
  viewport->setBounds(60, 60, getWidth()-100, getHeight()-150);

  xaxis->setBounds(60, 30, viewport->getViewWidth(), 26); 
  yaxis->setBounds(30, 60, 26, viewport->getViewHeight());
  focusview->setBounds(30, viewport->getBottom()+4,
		       viewport->getWidth()+34, // axis+spacer
		       focusview->getHeight());
}

void Plotter::sliderValueChanged (Slider *slider) {
  double z = pow(2.0, slider->getValue());
  String name = slider->getName();

  if ( name == T("xzoom") )
    xaxis->setZoom(z);
  else
    yaxis->setZoom(z);
  plotview->resizeForDrawing();
  // now have to update the size of the Axis' view -- this is NOT the
  // size of the axis! Note that if zoom has gotten larger then the
  // size of the axis view doenst actually change, in which case we
  // have to force a repaint to see the axis content drawn at the new
  // zoom.
  if ( name == T("xzoom") ) {
    int old=getWidth();
    xaxis->setSize(viewport->getViewWidth(), xaxis->getHeight());
    if (old==getWidth()) 
      xaxis->repaint();
  }  
  else {
    int old=getHeight();
    yaxis->setSize(yaxis->getWidth(), viewport->getViewHeight()) ;
    if (old==getHeight()) 
      yaxis->repaint();
  }
} 

void Plotter::scrollBarMoved (ScrollBar * sb, const double nrs) {
  // Scrolling callback. Used to scroll the axis views whenever
  // viewport's scrollbar is scrolled.
  String name = sb->getName();
  
  if ( name == T("xscroll") )
    xaxis->repaint();
  else
    yaxis->repaint();
}

/***********************************************************************
 *
 * PlotterWindow: top level window for plotting
 *
 **********************************************************************/

const StringArray PlotterWindow::getMenuBarNames (MenuBarComponent* mbar) {
  const tchar* const menuNames[] = { T("File"), T("Edit"), T("Layer"), T("View"), T("Help"), 0 };
  return StringArray((const tchar**) menuNames);
}



const PopupMenu PlotterWindow::getMenuForIndex (MenuBarComponent* mbar, int idx, 
						const String &name) {
  PopupMenu menu;
  PopupMenu sub1, sub2, sub3;
  int val;
  PlotType type=plotter->getPlotType();
  switch (idx) {
  case 0 :
    // File Menu
    sub1.addItem( Plotter::cmdFileNew + XYPlot, T("XY Data"));
    sub1.addItem( Plotter::cmdFileNew + XYZPlot, T("XYZ Data"), false);
    sub1.addItem( Plotter::cmdFileNew + MidiPlot, T("Midi"));
    sub1.addItem( Plotter::cmdFileNew + VKeyPlot, T("Fomus"), false);
    sub1.addItem( Plotter::cmdFileNew + FomusPlot, T("Vkey"), false);
    sub1.addItem( Plotter::cmdFileNew + CLMPlot, T("CLM"), false);
    menu.addSubMenu(T("New"), sub1, true);    
    menu.addItem( Plotter::cmdFileOpen, T("Open..."), false);
    menu.addItem( Plotter::cmdFileSave, T("Save"), false);
    menu.addItem( Plotter::cmdFileImport, T("Import..."), false);
    menu.addItem( Plotter::cmdFileExport, T("Export..."), false);
    break;
  case 1 :
    // Edit Menu
    menu.addItem( Plotter::cmdEditCut, T("Cut"));
    menu.addItem( Plotter::cmdEditCopy, T("Copy"));
    menu.addItem( Plotter::cmdEditPaste, T("Paste"));
    menu.addItem( Plotter::cmdEditClear, T("Clear"));
    menu.addSeparator();
    menu.addItem( Plotter::cmdEditSelectAll, T("Select All"));
    menu.addSeparator();
    menu.addItem( Plotter::cmdEditFind, T("Find..."), false);
    break;
  case 2 :
    // Layer Menu
    if (type == MidiPlot) {
      sub1.addItem( Plotter::cmdLayerAdd + MidiPlot, T("Midi"));
      sub1.addItem( Plotter::cmdLayerAdd + MidiPlot, T("Program Change"), false);
      sub1.addItem( Plotter::cmdLayerAdd + MidiPlot, T("Controller"), false);
      menu.addSubMenu(T("Add"), sub1, true);          
    }
    else menu.addItem( Plotter::cmdLayerAdd + type, T("Add"));
    menu.addItem(Plotter::cmdLayerDelete, T("Delete"), (plotter->numLayers() > 1));
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
    val=plotter->getFocusLayer()->getLayerStyle();
    menu.addItem( Plotter::cmdViewStyle + Layer::line, T("Line"),
		  true, (val==Layer::line));
    menu.addItem( Plotter::cmdViewStyle + Layer::point, T("Point"),
		  true, (val==Layer::point));
    menu.addItem( Plotter::cmdViewStyle + Layer::lineandpoint, T("Line and Point"),
		  true, (val==Layer::lineandpoint));
    menu.addItem( Plotter::cmdViewStyle + Layer::hbox, T("Horizontal Box"),
		  (type > XYPlot), (val==Layer::hbox));
    menu.addItem( Plotter::cmdViewStyle + Layer::vline, T("Vertical Line"),
		  true, (val==Layer::vline));
    menu.addItem( Plotter::cmdViewStyle + Layer::vlineandpoint, T("Vertical Line and Point"),
		  true, (val==Layer::vlineandpoint));
    menu.addItem( Plotter::cmdViewStyle + Layer::vbar, T("Vertical Bar"),
		  false, (val==Layer::vbar));
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
    sub1.addItem( Plotter::cmdViewBgMousing, T("Back Layer Mousing"), false, false);
    menu.addSubMenu(T("Background"), sub1, true);    
    menu.addSeparator();
    menu.addItem( Plotter::cmdViewMouseGuide, T("Mouse Guide"), false);
    break;
  case 4 :
    menu.addItem( Plotter::cmdHelpCommands, T("Command Help"));
    break;
  }
  return menu;
}

void PlotterWindow::menuItemSelected (MenuBarComponent* mbar, int id, int idx) {
  // commandIDs reserve lower 8 bits for command-specific information
  int arg = id & 0x000000FF;
  int cmd = id & 0xFFFFFF00;
  bool tog;
  printf("menubar: command=%d data=%d\n", cmd, arg);
  switch (cmd) {
  case Plotter::cmdFileNew :
    new PlotterWindow( (PlotType)arg);
    break;
  case Plotter::cmdFileOpen :
  case Plotter::cmdFileSave :
  case Plotter::cmdFileSaveAs :
  case Plotter::cmdFileImport :
  case Plotter::cmdFileExport :
  case Plotter::cmdEditCut :
  case Plotter::cmdEditCopy :
  case Plotter::cmdEditPaste :
  case Plotter::cmdEditClear :
  case Plotter::cmdEditSelectAll :
  case Plotter::cmdEditFind :
    break;
  case Plotter::cmdLayerAdd :
    break;
  case Plotter::cmdLayerDelete :
    break;
  case Plotter::cmdLayerSelect :
    // FIX: make layer ids start at 1 to use all 8 bits
    plotter->setFocusLayer(plotter->findLayer(arg));
    plotter->redrawBackView();
    plotter->redrawPlotView();
    break;
  case Plotter::cmdViewStyle :
    plotter->getFocusLayer()->setLayerStyle(arg);
    plotter->redrawPlotView();
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
  case Plotter::cmdHelpCommands :
  default :
    break;
  }
}

PlotterWindow::PlotterWindow (PlotType pt)
  : DocumentWindow (String::empty , Colours::silver, 
		    DocumentWindow::allButtons, true ) {
  String title;

  plotter = new Plotter( pt ) ;
  menubar = new MenuBarComponent(this);
  setMenuBar(this, 0);
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
  //JUCEApplication::quit();
  this->~PlotterWindow();
}
