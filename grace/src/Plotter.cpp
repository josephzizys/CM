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
using namespace std;

//
// PlotViewport (scrolling)
//

class PlotViewport : public Viewport {
 public:
  Plotter * plotter;
  PlotViewport (Plotter * p) {
    // cache parent plotter view and register plotter to receive
    // callbacks from the viewport's scollers. this will allow the
    // plotter to scroll the axis views whenever the plot is scrolled
    plotter=p;
    getHorizontalScrollBar()->setName(T("xscroll"));
    getHorizontalScrollBar()->addListener(p);
    getVerticalScrollBar()->setName(T("yscroll"));
    getVerticalScrollBar()->addListener(p);
  };
  ~PlotViewport () {

  };

  //  void visibleAreaChanged(int vx, int vy, int vw, int vh) {
  //    std::cout << "plot visible region: " << vx << " " << vy <<
  //      " " << vw << " " << vh <<  "\n";
  //  }

};

///
/// Axis methods
///

void AxisView::init (AxisType typ, AxisOrientation ori) {
  // init axis data according to common "templates"
  vert = (ori==horizontal) ? false : true;
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

void AxisView::paint (Graphics& g) {
  g.fillAll (Colours::white); 

  // lightly shade lower half like scollbars, pretty!
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
 * FocusView: holds controls for working with the top-most (focus) plot
 *
 **********************************************************************/

class FocusView  : public Component,
                   public ComboBoxListener,
                   public ButtonListener {
public:
  Plotter * plotter;
  Layer * focuslayer;
  ComboBox* layerMenu;
  ToggleButton* allButton;
  TextButton* colorButton;
  Label* label;
  TextEditor* xBuffer;
  Label* label2;
  TextEditor* yBuffer;
  ComboBox* drawMenu;
  Label* label3;
  TextEditor* zBuffer;
  ComboBox* bgMenu;
  ToggleButton* guideButton;

  FocusView (Plotter * p);
  ~FocusView();

  void setFocusLayer(Layer * l);
  Layer * getFocusLayer() { return focuslayer;}
  void resized();
  void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
  void buttonClicked (Button* buttonThatWasClicked);
  juce_UseDebuggingNewOperator
  
  FocusView (const FocusView&);
  const FocusView& operator= (const FocusView&);
};

FocusView::FocusView (Plotter * p)
  : plotter (0),
    focuslayer (0),
    layerMenu (0),
    allButton (0),
    colorButton (0),
    label (0),
    xBuffer (0),
    label2 (0),
    yBuffer (0),
    drawMenu (0),
    label3 (0),
    zBuffer (0),
    bgMenu (0),
    guideButton (0) {
  plotter=p;
  addAndMakeVisible (layerMenu = new ComboBox (String::empty));
  layerMenu->setEditableText (true);
  layerMenu->setJustificationType (Justification::centredLeft);
  layerMenu->setTextWhenNothingSelected (String::empty);
  layerMenu->setTextWhenNoChoicesAvailable (T("(no choices)"));
  layerMenu->addListener (this);

  addAndMakeVisible (allButton = new ToggleButton (String::empty));
  allButton->setButtonText (T("Transparent"));
  allButton->addButtonListener (this);

  addAndMakeVisible (colorButton = new TextButton (String::empty));
  colorButton->setButtonText (T("Color..."));
  colorButton->addButtonListener (this);

  addAndMakeVisible (label = new Label (String::empty, T("x:")));
  label->setFont (Font (15.0000f, Font::plain));
  label->setJustificationType (Justification::centredLeft);
  label->setEditable (false, false, false);
  label->setColour (Label::backgroundColourId, Colour (0x0));
  label->setColour (Label::textColourId, Colours::black);
  label->setColour (Label::outlineColourId, Colour (0x0));
  label->setColour (TextEditor::textColourId, Colours::black);
  label->setColour (TextEditor::backgroundColourId, Colour (0x0));

  addAndMakeVisible (xBuffer = new TextEditor (String::empty));
  xBuffer->setMultiLine (false);
  xBuffer->setReturnKeyStartsNewLine (false);
  xBuffer->setReadOnly (false);
  xBuffer->setScrollbarsShown (false);
  xBuffer->setCaretVisible (true);
  xBuffer->setPopupMenuEnabled (false);
  xBuffer->setText (T("1000.00"));

  addAndMakeVisible (label2 = new Label (String::empty, T("y:")));
  label2->setFont (Font (15.0000f, Font::plain));
  label2->setJustificationType (Justification::centredLeft);
  label2->setEditable (false, false, false);
  label2->setColour (Label::backgroundColourId, Colour (0x0));
  label2->setColour (Label::textColourId, Colours::black);
  label2->setColour (Label::outlineColourId, Colour (0x0));
  label2->setColour (TextEditor::textColourId, Colours::black);
  label2->setColour (TextEditor::backgroundColourId, Colour (0x0));

  addAndMakeVisible (yBuffer = new TextEditor (String::empty));
  yBuffer->setMultiLine (false);
  yBuffer->setReturnKeyStartsNewLine (false);
  yBuffer->setReadOnly (false);
  yBuffer->setScrollbarsShown (false);
  yBuffer->setCaretVisible (true);
  yBuffer->setPopupMenuEnabled (false);
  yBuffer->setText (T("1000.00"));

  addAndMakeVisible (drawMenu = new ComboBox (String::empty));
  drawMenu->setEditableText (false);
  drawMenu->setJustificationType (Justification::centredLeft);
  drawMenu->setTextWhenNothingSelected (String::empty);
  drawMenu->setTextWhenNoChoicesAvailable (T("(no choices)"));
  drawMenu->addItem (T("Line"), Layer::line);
  drawMenu->addItem (T("Point"), Layer::point);
  drawMenu->addItem (T("Line+Point"), Layer::lineandpoint);
  drawMenu->addItem (T("Horizontal Box"), Layer::hbox);
  drawMenu->setItemEnabled(Layer::hbox, false);
  drawMenu->addItem (T("Vertical"), Layer::vlineandpoint);
  drawMenu->addItem (T("Vertical Bar"), Layer::vbar);
  drawMenu->setItemEnabled(Layer::vbar, false);
  drawMenu->addListener (this);
  
  addAndMakeVisible (label3 = new Label (String::empty, T("z:")));
  label3->setFont (Font (15.0000f, Font::plain));
  label3->setJustificationType (Justification::centredLeft);
  label3->setEditable (false, false, false);
  label3->setColour (Label::backgroundColourId, Colour (0x0));
  label3->setColour (Label::textColourId, Colours::black);
  label3->setColour (Label::outlineColourId, Colour (0x0));
  label3->setColour (TextEditor::textColourId, Colours::black);
  label3->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (zBuffer = new TextEditor (String::empty));
  zBuffer->setMultiLine (false);
  zBuffer->setReturnKeyStartsNewLine (false);
  zBuffer->setReadOnly (false);
  zBuffer->setScrollbarsShown (false);
  zBuffer->setCaretVisible (true);
  zBuffer->setPopupMenuEnabled (false);
  zBuffer->setText (T("1000.00"));
  
  addAndMakeVisible (bgMenu = new ComboBox (String::empty));
  bgMenu->setEditableText (false);
  bgMenu->setJustificationType (Justification::centredLeft);
  bgMenu->setTextWhenNothingSelected (String::empty);
  bgMenu->setTextWhenNoChoicesAvailable (T("(no choices)"));
  bgMenu->addItem (T("Grid"), 2);   // bgGrid
  bgMenu->addItem (T("Tiled"), 3);  // bgTiled
  bgMenu->addItem (T("Solid"), 1);  // bgSolid
  bgMenu->setSelectedId(1); // do this before listener is hooked up
  bgMenu->addListener (this);
  
  addAndMakeVisible (guideButton = new ToggleButton (String::empty));
  guideButton->setButtonText (T("Guide"));
  guideButton->addButtonListener (this);
  
  setSize (440, 54);

}

FocusView::~FocusView() {
  deleteAndZero (layerMenu);
  deleteAndZero (allButton);
  deleteAndZero (colorButton);
  deleteAndZero (label);
  deleteAndZero (xBuffer);
  deleteAndZero (label2);
  deleteAndZero (yBuffer);
  deleteAndZero (drawMenu);
  deleteAndZero (label3);
  deleteAndZero (zBuffer);
  deleteAndZero (bgMenu);
  deleteAndZero (guideButton);
}

void FocusView::setFocusLayer(Layer * l) {
  focuslayer=l;
  bgMenu->setSelectedId(l->getLayerBGStyle(), true);
  layerMenu->setSelectedId(l->getLayerID(), true);
  layerMenu->setColour(ComboBox::textColourId,
		       l->getLayerColor());
  layerMenu->setText(l->getLayerName(), true);  
  drawMenu->setSelectedId(l->style, true);
  allButton->setToggleState(l->isTransparent(), true);
}

void FocusView::resized() {
  layerMenu->setBounds (0, 0, 176, 24);
  allButton->setBounds (179, 26, 92, 24);
  colorButton->setBounds (5, 26, 55, 24);
  label->setBounds (182, 0, 20, 24);
  xBuffer->setBounds (204, 0, 60, 24);
  label2->setBounds (273, 0, 20, 24);
  yBuffer->setBounds (295, 0, 60, 24);
  drawMenu->setBounds (64, 26, 112, 24);
  label3->setBounds (361, 0, 20, 24);
  zBuffer->setBounds (382, 0, 60, 24);
  bgMenu->setBounds (365, 26, 78, 24);
  guideButton->setBounds (269, 26, 63, 24);
}

void FocusView::comboBoxChanged (ComboBox* m) {
  Layer * foc = getFocusLayer();
  int sid=m->getSelectedId();  // item id = layer's id
  if (m == layerMenu) {
    if (sid==0) {
      // editied the text, rename the current layer.
      int fid = foc->getLayerID();
      cout << "focus id " << fid << endl;
      foc->setLayerName(m->getText());  // rename layer
      // rename layer's associated item in menu...
      for (int i=0;i<m->getNumItems(); i++)
	if (m->getItemId(i) == fid) {
	  m->changeItemText(fid,m->getText());
	  break;
	}
    }
    else {
      // currently the plotter's setfocus method is identical
      plotter->setFocusLayer(plotter->findLayer(sid));
      plotter->redrawPlotView();
    }
  }
  else if (m == drawMenu) {
    foc->setLayerStyle(m->getSelectedId());
    plotter->redrawPlotView();
  }
  else if (m == bgMenu) {
    foc->setLayerBGStyle( m->getSelectedId());
    plotter->redrawPlotView();
  }
}

void FocusView::buttonClicked (Button* b) {
  Layer * l;
    if (b == allButton) {
      l=getFocusLayer();
      l->setTransparent(b->getToggleState());
      plotter->redrawPlotView();
    }
    else if (b == colorButton) {
      ColourSelector cols();
    }
    else if (b == guideButton) {
    }
}

/***********************************************************************
 *
 * PlotView: the drawing canvas
 *
 **********************************************************************/

class PlotView  : public Component {
 public:
  enum BGStyle {
    // ids for drawing different backgrounds.
    bgSolid = 1,
    bgGrid,
    bgTiled
  };

  enum {
    drawNormal = 0,
    drawSel,
    moveSel,
    undoSel};

  Plotter * plotter;
  FocusView * focusview;
  double ppi, ppp, pad; // pix per inc, pix per point, margin pad
  AxisView * xaxis;
  AxisView * yaxis;
  Colour bgcolors[6];
  int drawmode;

  PlotView (Plotter * p, FocusView * f) 
    : ppi (60.0) , ppp (8.0) , pad (8.0) {
    plotter=p;
    focusview=f;
    xaxis=(AxisView *)NULL;
    yaxis=(AxisView *)NULL;
    ////    focus=(Layer *)NULL;
    // bgSolid colors
    bgcolors[0]=Colours::white;
    bgcolors[1]=Colours::lightyellow;
    // bgGrid colors
    bgcolors[2]=Colours::darkgrey;
    bgcolors[3]=Colours::lightgrey;
    // bgTiled colors
    bgcolors[4]=Colours::lavender;
    bgcolors[5]=Colour(0xf7, 0xf7, 0xf7);
  };

  void paint (Graphics& g);
  ~PlotView () {};

  Colour bgColor1(BGStyle t) {
    // each bgstyle has two colors associated with it.
    // style ids start at 1
    return bgcolors[(t-1)*2];  
  }

  Colour bgColor2(BGStyle t) {
    return bgcolors[((t-1)*2)+1];
  }

  bool isInside(float x, float y, float left, float top,
		float right, float bottom);
  void mouseDown(const MouseEvent &e) ;
  void mouseDrag(const MouseEvent &e) ;
  void mouseUp(const MouseEvent &e) ;
  void resizeForDrawing();
  void drawGrid(Graphics& g);
  void drawCheckerBoard(Graphics& g);
  void drawLayer(Graphics& g, Layer * l, int drawsel=0);
  void drawSelection (Graphics& g, Layer * layr, int mode);
  int visiblePixelLeft () { return plotter->viewport->getViewPositionX(); }
  int visiblePixelTop () { return plotter->viewport->getViewPositionY(); }
  int visiblePixelRight () { 
    return (plotter->viewport->getViewPositionX() +
	    plotter->viewport->getViewWidth());
  }
  int visiblePixelBottom () { 
    return (plotter->viewport->getViewPositionY() +
	    plotter->viewport->getViewHeight());
  }
  double visibleValueLeft() { return xaxis->toValue(visiblePixelLeft()); }
  double visibleValueRight() { return xaxis->toValue(visiblePixelRight()); }
  double visibleValueTop() { return yaxis->toValue(visiblePixelTop()); }
  double visibleValueBottom() { return yaxis->toValue(visiblePixelBottom()); }
};

void PlotView::resizeForDrawing() {
  // called when zoom value changes to reset total size of plotting view
  double xsiz, ysiz, xtot, ytot;
  // xpad and ypad are margins around the plotting area so points and
  // min/max positions arent clipped.

  xsiz=xaxis->size();
  ysiz=yaxis->size();
  xtot=pad+xsiz+pad;
  ytot=pad+ysiz+pad;
  xaxis->offset=pad;
  yaxis->offset=ytot-pad;
  setSize( (int)xtot, (int)ytot );
  //std::cout << "plotview: " << getWidth() << " " << getHeight() << "\n" ;
}

void PlotView::paint (Graphics& g) {
  // erase with white
  Layer * focus=focusview->getFocusLayer();

  if ((xaxis==(AxisView *)NULL) || (yaxis==(AxisView *)NULL) ||
      (focusview==(FocusView *)NULL))
    return;

  if (drawmode==undoSel) {
    drawLayer( g, focus, undoSel);
  }
  else if (drawmode==moveSel) {
    }
  else {
    g.fillAll (bgcolors[0]);
    // don't do anything unless axis and layer is set. is this necessary??
    if (focus->getLayerBGStyle()==bgGrid)
      drawGrid(g);
    else if (focus->getLayerBGStyle()==bgTiled)
      drawCheckerBoard(g);
    else if (focus->getLayerBGStyle()==bgSolid)
      g.fillAll(bgColor2(bgSolid));
    // if focus is transparent draw background plots.
    if (focus->isTransparent()) 
      for (int i=0; i < plotter->numLayers(); i++) {
	Layer * l = plotter->getLayer(i);
	if (focus != l) drawLayer(g, l);
      }
    drawLayer(g,focus);
    if ( focus->isSelection() ) {
      drawLayer( g, focus, drawSel);
    }
  }
}

void PlotView::drawLayer(Graphics& g, Layer * layer, int dmode) {
  double half=ppp/2;
  double ax, ay, px, py, lx, ly, ox, oy;
  Colour color, selcolor= Colours::grey;
  // Getters access either points or selection
  float (Layer::*xgetter)( int) ;
  float (Layer::*ygetter)( int) ;
  float (Layer::*zgetter)( int) ;
  int ndraw;
  bool fillp=true;

  if ( (dmode == drawNormal) || (dmode= moveSel) ) {
    // drawNormal: draw everything usng layer's color
    // moveSel: draw everything but selected points are grey
    color=layer->color;
    ndraw=layer->numPoints();
    xgetter = &Layer::getPointX;
    ygetter = &Layer::getPointY;
    zgetter = &Layer::getPointZ;
  }
  else {
    // drawSel: draw ONLY (selected) pointheads, grey no lines
    // undoSel: draw ONLY (selected) pointheads, layer color no lines
    if (dmode==undoSel)
      color=layer->color;
    else color=selcolor;
    ndraw=layer->numSelected();
    xgetter = &Layer::getSelPointX;
    ygetter = &Layer::getSelPointY;
    zgetter = &Layer::getSelPointZ;
  }

  // need pixel origins for vert/horiz lines/bars
  if (yaxis->from < 0.0 && yaxis->to >= 0.0)
    oy=yaxis->toPixel(0.0);
  else oy=yaxis->toPixel(yaxis->from);

  if (xaxis->from < 0.0 && xaxis->to >= 0.0)
    ox=xaxis->toPixel(0.0);
  else ox=xaxis->toPixel(xaxis->from);

  g.setColour(color);
  for (int i=0; i<ndraw; i++) {
    //ax=layer->getPointX(i);  // axis coords
    //ay=layer->getPointY(i);
    ax=(layer->*xgetter) (i);  
    ay=(layer->*ygetter) (i);  
    px=xaxis->toPixel(ax);   // pixel coords
    py=yaxis->toPixel(ay);

    if (layer->isDrawStyle(Layer::point)) {
      // if we are moving selection then draw selected point gray
      if ((dmode==moveSel ) && layer->isSelected(i) ) {
	g.setColour(selcolor);
	g.fillEllipse(px-half, py-half, ppp,ppp);
	g.setColour(color);
      }
      else
	g.fillEllipse(px-half, py-half, ppp,ppp);
    }

    // dont do lines if drawing/undrawing selection
    if ( layer->isDrawStyle(Layer::line) && 
	 ((dmode==drawNormal) || (dmode==moveSel)) ) {
      if (layer->isDrawStyle(Layer::vertical))
	g.drawLine( px, oy, px, py); // vertical line from orign
      else if (layer->isDrawStyle(Layer::horizontal) )
	g.drawLine( ox, py, px, py); // horizontal line from origin
      else if (i>0)  // normal line between points
	g.drawLine( lx, ly, px, py);
      }
    if (layer->isDrawStyle(Layer::hbox)) {
      // cant convert the relative Z directly to pixel because of axis
      // padding.  so to get pixel width of Z, get absolute axis
      // position of Z, convert to pixel and then subtract out px
      //double az = ax+layer->getPointZ(i);
      double az=ax + (layer->*zgetter) (i);  
      double pz = (int)xaxis->toPixel(az);
      // draw selected boxes gray if moving
      if ((dmode==moveSel ) && layer->isSelected(i) ) {
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

void PlotView::drawCheckerBoard(Graphics& g) {
  g.fillCheckerBoard((int)pad, (int)pad, 
		     (int)(getWidth()-pad*2), 
		     (int)(getHeight()-pad*2),
		     (int)xaxis->tickSize(), 
		     (int)yaxis->tickSize(),
		     bgColor1(bgTiled),
		     bgColor2(bgTiled));
}

void PlotView::drawGrid(Graphics& g) {
  // draw grid underneath plots
  Colour c1=bgColor1(bgGrid);
  Colour c2=bgColor2(bgGrid);
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

/*
selmode 0  1 draw 2 erase 3 move
Mouse-click - set selection
Mouse-shift-click add/remove selection
Mouse-control-click create point
Mouse-meta-click delete point
*/


void PlotView::mouseDown (const MouseEvent &e) {
  Layer * focus=focusview->getFocusLayer();
  // shoudnt happen
  if (focus==(Layer *)NULL) return;
  int mxp=e.getMouseDownX();
  int myp=e.getMouseDownY();

  if ( e.mods.isShiftDown() ) {
    int i = focus->addPoint(xaxis->toValue(mxp),
			    yaxis->toValue(myp));
    focus->addSelection( i);
    repaint();
    return;
    }

    double half=ppp/2;
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
	  //cout <<"Got POINT[" << i << "] x=" << x << " y=" << y << endl;
	  point=i;
	  break;
	}
	// give up when points are rightward of mouse x
	else if (left > x)
	  break;
      }
    }
    else {
      // speed: use a constant "point" around mouse x and y and try to
      // find a point thats inside it
      left=xaxis->toValue( mxp - half);
      top=yaxis->toValue( myp - half);
      right=xaxis->toValue( mxp + half);
      bottom=yaxis->toValue( myp + half);

      for (int i=0; i < focus->numPoints(); i++) {
	x=focus->getPointX(i);
	y=focus->getPointY(i);
	if ( isInside(x, y, left, top , right, bottom) ) {
	  //cout <<"Got POINT[" << i << "] x=" << x << " y=" << y << endl;
	  point=i;
	  break;
	} 
	// give up when points are rightward of mouse x
	else if (x > right) 
	  break;
      }
    }

    if ( point<0 ) {
      // only need to draw exising selection normal
      drawmode=undoSel;
      repaint();
      focus->clearSelection();
      printf("cleared selection\n");
      drawmode=drawNormal;
    }
    else if ( focus->isSelected(point) ) {
      printf("point already selected\n");
    }
    else {
      focus->addSelection(point);
      cout << "selecting POINT[" << point<<  "]" << endl;
      focus->printSelection();
      drawmode=drawSel;
      repaint();
      drawmode=drawNormal;
    }
}

void PlotView::mouseDrag(const MouseEvent &e) {
  Layer * focus=focusview->getFocusLayer();
  /*if (selection > -1) {
    double x=xaxis->toValue(e.x);
    double y=yaxis->toValue(e.y);
    focus->setPointXY(selection, x, y );
    repaint();
  }
  */
}

void PlotView::mouseUp(const MouseEvent &e) {
  Layer * focus=focusview->getFocusLayer();
}

/***********************************************************************
 *
 * Plotter: contains all the subcomponents for plotting
 *
 **********************************************************************/

Plotter::Plotter (PlotType pt) {
  Colour cols[8] = { Colours::red, Colours::green, Colours::blue, 
		     Colours::magenta, Colours::cyan, Colours::sienna,
		     Colours::orange, Colours::coral};
  font=Font(Font::getDefaultSansSerifFontName(), 10.0, Font::bold);
  rand=new Random(Time::currentTimeMillis());
  focusview=new FocusView(this);
  plotview=new PlotView (this, focusview );
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
  setAxisView( new AxisView(xtyp, AxisView::horizontal) );
  setAxisView( new AxisView(ytyp, AxisView::vertical) );

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

  viewport->setViewedComponent(plotview);
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
  deleteAndZero(viewport);
  deleteAndZero(focusview);
  layers.clear(true);
  delete rand;
}

void Plotter::setAxisView (AxisView * a) {
  // add axis to plotter (and to its plotview as well).
  a->viewport=this->viewport;
  if ( a->isVertical() ) {
      yaxis=a;
      plotview->yaxis=a;
    }
  else if ( a->isHorizontal() ) {
      xaxis=a;
      plotview->xaxis=a;
    }
}

void Plotter::redrawPlotView() {
  plotview->repaint();
}

Layer * Plotter::getFocusLayer() {
  //return plotview->focus;
  return focusview->getFocusLayer();
}

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

void Plotter::setFocusLayer(Layer * l) {
  //plotview->focus=l;
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

PlotterWindow::PlotterWindow (PlotType pt)
  : DocumentWindow (String::empty , Colours::silver, 
		    DocumentWindow::allButtons, true ) {
  String title;

  plotter = new Plotter( pt ) ;

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
