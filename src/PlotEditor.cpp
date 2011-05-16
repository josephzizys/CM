/*=======================================================================*
  Copyright (C) 2011 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#include "PlotEditor.h"
#include "Plot.h"

static bool isNumericalText(const String num)
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

PlotWindowTab::PlotWindowTab (Plotter* pltr, TopLevelWindow* win)
  : PlotterTab(pltr),
    namelabel(0),
    namebuffer (0),
    savebutton (0),
    layerbutton (0)
{
  addAndMakeVisible(namelabel = new TabLabel(T("Title:")));
  addAndMakeVisible(namebuffer = new TabEditor(win->getName()));
  namebuffer->addListener(this);
  addAndMakeVisible(savebutton = new TabButton (T("Save...")));
  addAndMakeVisible(layerbutton = new TabButton (T("Add Layer")));
  setVisible(true);
}

PlotWindowTab::~PlotWindowTab ()
{
  deleteAllChildren();
}

void PlotWindowTab::resized ()
{
  int y=margin;
  namelabel->setTopLeftPosition(margin, y);
  namebuffer->setBounds(namelabel->getRight()+margin, y, 220, lineheight);
  layerbutton->setTopLeftPosition(namebuffer->getRight()+24, y);
  y += (lineheight + margin);
  savebutton->setTopLeftPosition(margin, y);
}

void PlotWindowTab::buttonClicked (Button* buttonThatWasClicked)
{
  std::cout << "Button clicked\n";
}

void PlotWindowTab::textEditorReturnKeyPressed(TextEditor& editor) 
{
  if (&editor == namebuffer)
  {
    TopLevelWindow* w=(TopLevelWindow *)getTopLevelComponent();
    String n=namebuffer->getTrimmedText();
    if (n.isNotEmpty())
      w->setName(n);
  }
}


/*=======================================================================*
                                 Axis Tab
 *=======================================================================*/

PlotterAxisTab::PlotterAxisTab (Plotter* pl, int orient)
  : PlotterTab(pl),
    namelabel (0),
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
    zoomlabel (0),
    zoomslider (0),
    fitcheckbox (0),
    orientation(orient),
    axistypechanged (false)
{
  AxisView* axisview = plotter->getAxisView(orientation);
  Axis* axis=axisview->getAxis();
  addAndMakeVisible(namelabel = new TabLabel(T("Name:")));

  addAndMakeVisible(namebuffer = new TabEditor(String(axis->getName())));
  namebuffer->addListener(this);

  addAndMakeVisible(fromlabel = new TabLabel(T("From:")));
  
  addAndMakeVisible(frombuffer = new TabEditor(String(axis->getMinimum())));
  frombuffer->addListener(this);

  addAndMakeVisible(tolabel = new TabLabel(T("To:")));
  
  addAndMakeVisible(tobuffer = new TabEditor(String(axis->getMaximum())));
  tobuffer->addListener(this);

  addAndMakeVisible (bylabel = new TabLabel (T("By:")));
  
  addAndMakeVisible (bybuffer = new TabEditor(String(axis->getIncrement())));
  bybuffer->addListener(this);

  addAndMakeVisible(typelabel = new TabLabel(T("Type:")));
  
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
  typemenu->setSelectedId(axis->getType(), false);
  typemenu->addListener (this);

  addAndMakeVisible(tickslabel = new TabLabel(T("Ticks:")));
  
  addAndMakeVisible(ticksbuffer = new TabEditor(String(axis->getTicks())));
  ticksbuffer->addListener(this);
  
  addAndMakeVisible(decimalslabel=new TabLabel(T("Decimals:")));
  
  addAndMakeVisible (decimalsmenu = new ComboBox (String::empty));
  decimalsmenu->setEditableText (false);
  decimalsmenu->setJustificationType (Justification::centredLeft);
  decimalsmenu->setTextWhenNothingSelected (String::empty);
  decimalsmenu->setTextWhenNoChoicesAvailable (T("(no choices)"));
  decimalsmenu->addItem (T("0"), 1);
  decimalsmenu->addItem (T("1"), 2);
  decimalsmenu->addItem (T("2"), 3);
  decimalsmenu->addItem (T("3"), 4);
  decimalsmenu->setSelectedId(axis->getDecimals()+1, false);
  decimalsmenu->addListener (this);

  addAndMakeVisible(zoomlabel = new TabLabel (T("Zoom:")));
  
  addAndMakeVisible(zoomslider = new Slider (String::empty));
  zoomslider->setSliderStyle(Slider::LinearHorizontal);
  zoomslider->setRange (0.1, 10, .05);
  zoomslider->setValue(axisview->getSpread(), false);
  zoomslider->setTextBoxStyle(Slider::TextBoxLeft, false, 80, 20);
  zoomslider->addListener(this);
  zoomslider->setEnabled(!axisview->isAutosized());

  addAndMakeVisible(fitcheckbox = new ToggleButton(T("Autosize")));
  fitcheckbox->setToggleState(axisview->isAutosized(), false);
  fitcheckbox->addListener(this);
}

PlotterAxisTab::~PlotterAxisTab()
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
  deleteAndZero (zoomlabel);
  deleteAndZero (zoomslider);
  deleteAndZero (fitcheckbox);
}

void PlotterAxisTab::resized()
{
  // line 1
  int y=margin;
  namelabel->setTopLeftPosition(margin, y);
  namebuffer->setBounds (56, y, 120, lineheight);
  typelabel->setTopLeftPosition(184, y);
  typemenu->setBounds (232, y, 96, lineheight);
  decimalslabel->setTopLeftPosition(336, y);
  decimalsmenu->setBounds (408, y, 52, lineheight);
  // line 2
  y += (lineheight+margin);
  fromlabel->setTopLeftPosition(margin, y);
  frombuffer->setBounds (56, y, 56, 24);
  tolabel->setTopLeftPosition(136, y);
  tobuffer->setBounds (168, y, 56, 24);
  bylabel->setTopLeftPosition(248, y);
  bybuffer->setBounds (280, y, 56, 24);
  tickslabel->setTopLeftPosition(352, y);
  ticksbuffer->setBounds(408, y, 56, lineheight);
  // line 3
  y += (lineheight+margin);
  zoomlabel->setTopLeftPosition(margin, y);
  zoomslider->setBounds (56, y, 280, 24);
  fitcheckbox->setBounds (zoomslider->getRight()+margin, y, 180, 24);
}

void PlotterAxisTab::comboBoxChanged (ComboBox* cbox)
{
  if (cbox == typemenu)
  {
    Axis ax(0);
    ax.init((Axis::AxisType)cbox->getSelectedId());
    namebuffer->setText(String(ax.getName()), false);
    frombuffer->setText(String(ax.getMinimum()), false);
    tobuffer->setText(String(ax.getMaximum()), false);
    bybuffer->setText(String(ax.getIncrement()), false);
    ticksbuffer->setText(String(ax.getTicks()), false);
    decimalsmenu->setSelectedId(ax.getDecimals()+1, true);
    axistypechanged=true;
  }
  else if (cbox == decimalsmenu)
  {
    //    AxisView* axisview = (ishorizontal) ? plotter->getHorizontalAxisView() : plotter->getVerticalAxisView() ;
    AxisView* axisview = plotter->getAxisView(orientation);
    axisview->getAxis()->setDecimals(cbox->getSelectedId()-1);
    axisview->repaint();
  } 
}

void PlotterAxisTab::sliderValueChanged (Slider* sliderThatWasMoved)
{
  AxisView* axisview = plotter->getAxisView(orientation);
  if (sliderThatWasMoved == zoomslider)
  {
    std::cout << "slider changed\n";
    plotter->setBackViewCaching(false);
    axisview->setSpread(sliderThatWasMoved->getValue());
    plotter->resizeForSpread();
    int w=axisview->getWidth();
    int h=axisview->getHeight();
    if (orientation==Plotter::horizontal)
    {
      // now have to update the size of the axis view -- this is NOT
      // the size of the axis!
      axisview->setSize(plotter->getViewportViewingWidth(), h);
      // if spread has gotten larger then the size of the axis view
      // doenst actually change, in which case we have to force a
      // repaint to see the axis content drawn at the new spread.
      if (w==axisview->getWidth())
        axisview->repaint();
    }
    else
    {
      axisview->setSize(w, plotter->getViewportViewingHeight()) ;
      if (h==axisview->getHeight())
	repaint();
    }
    plotter->setBackViewCaching(true);
  }
}

void PlotterAxisTab::buttonClicked (Button* buttonThatWasClicked)
{
  AxisView* axisview = plotter->getAxisView(orientation);
  if (buttonThatWasClicked == fitcheckbox)
  {
    std::cout << "button on\n";
    if (fitcheckbox->getToggleState())
    {
      axisview->setAutosized(true);
      zoomlabel->setEnabled(false);
      zoomslider->setValue(axisview->getSpread(), false);
      zoomslider->setEnabled(false);
      plotter->resized();
    }
    else
    {
      std::cout << "button off\n";
      axisview->setAutosized(false);
      zoomlabel->setEnabled(true);
      zoomslider->setEnabled(true);
      zoomslider->setValue(axisview->getSpread(), false);
    }
  }
}

void PlotterAxisTab::textEditorReturnKeyPressed (TextEditor& editor)
{
  double val;
  AxisView* axisview = plotter->getAxisView(orientation);
  Axis* axis=axisview->getAxis();
  bool redraw=false;

  // pressing return in any box after the axis type has been reset by
  // the user updates all fields!
  if (axistypechanged)
  {
    String text=namebuffer->getText();
    axis->setName(text);
    if (isNumericalText(text=frombuffer->getText()))
      axis->setMinimum(text.getDoubleValue());
    if (isNumericalText(text=tobuffer->getText()))
      axis->setMaximum(text.getDoubleValue());
    if (isNumericalText(text=bybuffer->getText()))
      axis->setIncrement(text.getDoubleValue());
    if (isNumericalText(text=ticksbuffer->getText()))
      axis->setTicks(text.getIntValue());
    axis->setDecimals(decimalsmenu->getSelectedId()-1);
    redraw=true;
    axistypechanged=false;
  }
  else if (&editor == namebuffer)
  {
    axis->setName(editor.getText());
  }
  else if (&editor == frombuffer)
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
  else if (&editor == tobuffer)
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
  else if (&editor == bybuffer)
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
  else if (&editor == ticksbuffer)
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
    plotter->resizeForSpread();
  }
}

/*=======================================================================*

                                Layer Tab
 *=======================================================================*/

LayerTab::LayerTab (Plotter* pltr, Layer* layr)
  : PlotterTab(pltr),
    layer (layr),
    namelabel (0),
    namebuffer (0),
    stylelabel (0),
    stylemenu (0),
    colorpicker (0)
{
  addAndMakeVisible (namelabel = new TabLabel( T("Name:")));
  addAndMakeVisible (namebuffer = new TabEditor (layer->getLayerName()));
  namebuffer->addListener(this);
  //namebuffer->setColour (TextEditor::textColourId, Colours::black);
  //namebuffer->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (stylelabel = new TabLabel (T("Style:")));
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

  //addAndMakeVisible(colorpicker = new ColourSelector(ColourSelector::showSliders | ColourSelector::showColourAtTop,4,0));
  addAndMakeVisible(colorpicker = new ColourSelector( ColourSelector::showColourspace,4,0));
  colorpicker->setCurrentColour(layer->getLayerColor());
  colorpicker->addChangeListener(this);
}

LayerTab::~LayerTab()
{
  deleteAndZero (namelabel);
  deleteAndZero (namebuffer);
  deleteAndZero (stylelabel);
  deleteAndZero (stylemenu);
  deleteAndZero (colorpicker);
}

void LayerTab::resized()
{
  int space=150-(margin*5);
  int y=margin;
  namelabel->setBounds(margin, y, 48, lineheight);
  namebuffer->setBounds(56, y, 120, lineheight);
  //colorpicker->setBounds(320, margin-4, 170, 300);
  ////colorpicker->setBounds(320, 0, 170, 120);
  colorpicker->setBounds(320, y-4, 170, space);

  y+=(lineheight+margin);
  stylelabel->setBounds(margin, y, 48, lineheight);
  stylemenu->setBounds(56, y, 120, lineheight);
}

void LayerTab::comboBoxChanged (ComboBox* cbox)
{
  if (cbox == stylemenu)
  {
    layer->setLayerStyle(stylemenu->getSelectedId());
    plotter->redrawPlotView();
  }
}

void LayerTab::changeListenerCallback (ChangeBroadcaster* source)
{
  if (source == colorpicker)
  {
    layer->setLayerColor(colorpicker->getCurrentColour());
    plotter->redrawPlotView();
  }
}

void LayerTab::textEditorReturnKeyPressed(TextEditor& editor)
{
  if (&editor == namebuffer)
  {
    String name=namebuffer->getTrimmedText();
    if (name.isEmpty())
      namebuffer->setText(layer->getLayerName(), false);
    else
    {
      layer->setLayerName(name);
      TabbedComponent* tabber=(TabbedComponent*)getParentComponent();
      int index=tabber->getCurrentTabIndex();
      tabber->setTabName(index,name);
    }
  }
}






