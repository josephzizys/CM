/*=======================================================================*
  Copyright (C) 2011 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#include "Enumerations.h"
#include "Plot.h"
#include "PlotEditor.h"
#include "PlotWindow.h"
#include "CodeEditor.h"
#include "Midi.h"

/*=======================================================================*
                                Plot Editor
 *=======================================================================*/

PlotTabbedEditor::PlotTabbedEditor()
  : TabbedComponent(TabbedButtonBar::TabsAtTop) 
{
  bgcolor=Colour(0xffe5e5e5);
}

PlotTabbedEditor::~PlotTabbedEditor()
{
}
  
void PlotTabbedEditor::currentTabChanged (int newCurrentTabIndex, const String &newCurrentTabName)
{
  PlotEditor* editor=(PlotEditor*)getTabContentComponent(newCurrentTabIndex);
  switch (editor->tabType)
  {
  case PlotEditor::WindowEditor:
    std::cout << "window editor!\n";    
    break;
  case PlotEditor::AudioEditor:
    std::cout << "audio editor!\n";    
    break;
  case PlotEditor::AxisEditor:
    std::cout << "axis editor!\n";    
    break;
  case PlotEditor::LayerEditor:
    std::cout << "layer editor!\n";    
    break;
  case PlotEditor::ExportEditor:
    std::cout << "export editor!\n";    
    break;
  case PlotEditor::PointsEditor:
    std::cout << "points editor!\n";    
    break;
  default:
    std::cout << "unknown editor!\n";
  }
}

/*=======================================================================*
                                Window Editor
 *=======================================================================*/

PlotWindowEditor::PlotWindowEditor (Plotter* pltr, TopLevelWindow* win)
  : PlotEditor(pltr),
    namelabel(0),
    namebuffer (0),
    savebutton (0),
    layerbutton (0)
{
  tabType=WindowEditor;
  setName(T("Window"));
  addAndMakeVisible(namelabel = new EditorLabel(T("Title:")));
  addAndMakeVisible(namebuffer = new EditorTextBox(win->getName()));
  namebuffer->addListener(this);
  addAndMakeVisible(layerbutton = new EditorButton (T("New Layer")));
  layerbutton->addListener(this);
  addAndMakeVisible(savebutton = new EditorButton (T("Save...")));
  savebutton->addListener(this);
  setVisible(true);
}

PlotWindowEditor::~PlotWindowEditor ()
{
  deleteAllChildren();
}

void PlotWindowEditor::resized ()
{
  int y=margin;
  namelabel->setTopLeftPosition(margin, y);
  namebuffer->setBounds(namelabel->getRight()+margin, y, 220, lineheight);
  layerbutton->setTopLeftPosition(namebuffer->getRight()+(margin*2), y);
  //  y += (lineheight + margin);
  savebutton->setTopLeftPosition(layerbutton->getRight()+(margin*2), y);

  }

void PlotWindowEditor::buttonClicked (Button* buttonThatWasClicked)
{
  if (buttonThatWasClicked == savebutton)
  {
    PlotWindow* window=(PlotWindow *)getTopLevelComponent();
    window->save();
  }
  else if (buttonThatWasClicked == layerbutton)
  {
    Layer* layer=plotter->newLayer(NULL, true);
    getPlotTabbedEditor()->addEditor(new PlotLayerEditor(plotter, layer));
  }
}

void PlotWindowEditor::textEditorReturnKeyPressed(TextEditor& editor) 
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

PlotAxisEditor::PlotAxisEditor (Plotter* pl, int orient)
  : PlotEditor(pl),
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
  tabType=AxisEditor;
  if (orientation==Plotter::horizontal)
    setName(T("X Axis"));
  else
    setName(T("Y Axis"));
  AxisView* axisview = plotter->getAxisView(orientation);
  Axis* axis=axisview->getAxis();
  addAndMakeVisible(namelabel = new EditorLabel(T("Name:")));

  addAndMakeVisible(namebuffer = new EditorTextBox(String(axis->getName())));
  namebuffer->addListener(this);

  addAndMakeVisible(fromlabel = new EditorLabel(T("From:")));
  
  addAndMakeVisible(frombuffer = new EditorTextBox(String(axis->getMinimum())));
  frombuffer->addListener(this);

  addAndMakeVisible(tolabel = new EditorLabel(T("To:")));
  
  addAndMakeVisible(tobuffer = new EditorTextBox(String(axis->getMaximum())));
  tobuffer->addListener(this);

  addAndMakeVisible (bylabel = new EditorLabel (T("By:")));
  
  addAndMakeVisible (bybuffer = new EditorTextBox(String(axis->getIncrement())));
  bybuffer->addListener(this);

  addAndMakeVisible(typelabel = new EditorLabel(T("Type:")));
  
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

  addAndMakeVisible(tickslabel = new EditorLabel(T("Ticks:")));
  
  addAndMakeVisible(ticksbuffer = new EditorTextBox(String(axis->getTicks())));
  ticksbuffer->addListener(this);
  
  addAndMakeVisible(decimalslabel=new EditorLabel(T("Decimals:")));
  
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

  addAndMakeVisible(zoomlabel = new EditorLabel (T("Zoom:")));
  
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

PlotAxisEditor::~PlotAxisEditor()
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

void PlotAxisEditor::resized()
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

void PlotAxisEditor::comboBoxChanged (ComboBox* cbox)
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

void PlotAxisEditor::sliderValueChanged (Slider* sliderThatWasMoved)
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

void PlotAxisEditor::buttonClicked (Button* buttonThatWasClicked)
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

void PlotAxisEditor::textEditorReturnKeyPressed (TextEditor& editor)
{
  double val;
  AxisView* axisview = plotter->getAxisView(orientation);
  Axis* axis=axisview->getAxis();
  bool redraw=false;

  // pressing return in any box after the axis type has been reset by
  // the user updates all fields!
  if (axistypechanged)
  {
    axis->setName(namebuffer->getTrimmedText());
    if (frombuffer->isNumericText())
      axis->setMinimum(frombuffer->getDoubleValue());
    if (tobuffer->isNumericText())
      axis->setMaximum(tobuffer->getDoubleValue());
    if (bybuffer->isNumericText())
      axis->setIncrement(bybuffer->getDoubleValue());
    if (ticksbuffer->isNumericText())
      axis->setTicks(ticksbuffer->getIntValue());
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

PlotLayerEditor::PlotLayerEditor (Plotter* pltr, Layer* layr)
  : PlotEditor(pltr),
    layer (layr),
    namelabel (0),
    namebuffer (0),
    stylelabel (0),
    stylemenu (0),
    colorpicker (0)
{
  tabType=LayerEditor;
  setName(layer->getLayerName());
  addAndMakeVisible (namelabel = new EditorLabel( T("Name:")));
  addAndMakeVisible (namebuffer = new EditorTextBox (String::empty));
  ////  namebuffer->setColour(TextEditor::textColourId, layer->getLayerColor());
  ////namebuffer->setColour (TextEditor::backgroundColourId, layer->getLayerColor());
  // have to add text AFTER the color changes.
  ////  namebuffer->setText(layer->getLayerName(), false);
  namebuffer->addListener(this);
  
  addAndMakeVisible (stylelabel = new EditorLabel (T("Style:")));
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

  addAndMakeVisible(colorpicker = new ColourSelector( ColourSelector::showColourspace,4,0));
  colorpicker->setCurrentColour(layer->getLayerColor());
  colorpicker->addChangeListener(this);
}

PlotLayerEditor::~PlotLayerEditor()
{
  deleteAndZero (namelabel);
  deleteAndZero (namebuffer);
  deleteAndZero (stylelabel);
  deleteAndZero (stylemenu);
  deleteAndZero (colorpicker);
}

void PlotLayerEditor::resized()
{
  int space=150-(margin*5);
  int y=margin;
  namelabel->setBounds(margin, y, 48, lineheight);
  namebuffer->setBounds(56, y, 120, lineheight);
  colorpicker->setBounds(320, y-4, 170, space);

  y+=(lineheight+margin);
  stylelabel->setBounds(margin, y, 48, lineheight);
  stylemenu->setBounds(56, y, 120, lineheight);
}

void PlotLayerEditor::comboBoxChanged (ComboBox* cbox)
{
  if (cbox == stylemenu)
  {
    layer->setLayerStyle(stylemenu->getSelectedId());
    plotter->redrawPlotView();
  }
}

void PlotLayerEditor::changeListenerCallback (ChangeBroadcaster* source)
{
  if (source == colorpicker)
  {
    Colour color=colorpicker->getCurrentColour();
    //namebuffer->setColour (TextEditor::backgroundColourId, color);
    String name=namebuffer->getText();
    // have to re-add text after color change :(
    ////    namebuffer->setText(String::empty, false);
    ////    namebuffer->setColour(TextEditor::textColourId, color);
    ////    namebuffer->setText(name, false); 
    layer->setLayerColor(color);
    if (layer->isPoints())
      plotter->redrawPlotView();
  }
}

void PlotLayerEditor::textEditorReturnKeyPressed(TextEditor& editor)
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

/*=======================================================================*
                                Audio Editor
 *=======================================================================*/

PlotAudioEditor::PlotAudioEditor(Plotter* pltr)
  : PlotEditor(pltr),
    y0label (0),
    y0typein (0),
    y1label (0),
    y1typein (0),
    tempolabel (0),
    tempotypein (0),
    durlabel (0),
    durtypein(0),
    amplabel (0),
    amptypein (0),
    midioutmenu (0),
    transport (0),
    ismidiplot (false)
{
  tabType=AudioEditor;
  setName(T("Audio"));
  addAndMakeVisible (y0label = new EditorLabel( T("Y(0) Key:")));
  addAndMakeVisible (y0typein = new EditorTextBox (String(plotter->getPlaybackParameter(Plotter::PlaybackMinKey))));
  y0typein->addListener(this);
  addAndMakeVisible (y1label = new EditorLabel( T("Y(1) Key:")));
  addAndMakeVisible (y1typein = new EditorTextBox (String(plotter->getPlaybackParameter(Plotter::PlaybackMaxKey))));
  y1typein->addListener(this);
  addAndMakeVisible (durlabel = new EditorLabel( T("Dur:")));
  addAndMakeVisible (durtypein = new EditorTextBox (String(plotter->getPlaybackParameter(Plotter::PlaybackDuration))));
  durtypein->addListener(this);
  addAndMakeVisible (amplabel = new EditorLabel( T("Amp:")));
  addAndMakeVisible (amptypein = new EditorTextBox (String(plotter->getPlaybackParameter(Plotter::PlaybackAmplitude))));
  amptypein->addListener(this);
  addAndMakeVisible (midioutmenu = new MidiOutPopupMenu (this, true, MidiOutPort::getInstance()->devid));
  // create a Transport for the Plotter
  addAndMakeVisible (transport = new Transport (plotter, 60.0));
  // create a Transport for the Plotter
  plotter->pbthread->setTransport(transport);
  plotter->pbthread->startThread();
  plotter->pbthread->setPlaybackLimit( plotter->getHorizontalAxis()->getMaximum());
}

PlotAudioEditor::~PlotAudioEditor()
{
  deleteAndZero(y0label);
  deleteAndZero(y0typein);
  deleteAndZero(y1label);
  deleteAndZero(y1typein);
  deleteAndZero(durlabel);
  deleteAndZero(durtypein);
  deleteAndZero(amplabel);
  deleteAndZero(amptypein);
  deleteAndZero(midioutmenu);
  deleteAndZero(transport);
}

void PlotAudioEditor::resized()
{
  int x=margin;
  int y=margin;
  int z=0;
  int w=y0typein->getFont().getStringWidthFloat(T("XXXXX"));

  y0label->setTopLeftPosition(x,y);
  x = y0label->getRight()+z;
  y0typein->setBounds(x,y,w,lineheight);  
  x = y0typein->getRight()+(margin*1);
  // Y(1)
  y1label->setTopLeftPosition(x,y);
  x = y1label->getRight()+z;
  y1typein->setBounds(x,y,w,lineheight);  
  x = y1typein->getRight()+(margin*1);
  // dur
  durlabel->setTopLeftPosition(x,y);
  x = durlabel->getRight()+z;
  durtypein->setBounds(x,y,w,lineheight);  
  x = durtypein->getRight()+(margin*1);
  // amp
  amplabel->setTopLeftPosition(x,y);
  x = amplabel->getRight()+z;
  amptypein->setBounds(x,y,w,lineheight);  

  x=margin;
  y=y0label->getBottom()+margin;
  // center transport buttons (ignore width of tempo display)
  transport->setTopLeftPosition((getWidth()/2)-(Transport::TransportWidthNoTempo/2), y);
  y=getHeight()-(lineheight+margin);
  midioutmenu->setBounds(x, y, 200, lineheight);
}

void PlotAudioEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
  if (comboBoxThatHasChanged == midioutmenu)
  {
    plotter->setMidiOut(midioutmenu->getSelectedMidiOutputIndex());
  }
}

void PlotAudioEditor::textEditorReturnKeyPressed(TextEditor& editor)
{
  if (&editor == y0typein)
  {
    setPlaybackParam(Plotter::PlaybackMinKey, y0typein);
  }
  else if (&editor == y1typein)
  {
    setPlaybackParam(Plotter::PlaybackMaxKey, y1typein);
  }
  else if (&editor == durtypein)
  {
    setPlaybackParam(Plotter::PlaybackDuration, durtypein);
  }
  else if (&editor == amptypein)
  {
    setPlaybackParam(Plotter::PlaybackAmplitude, amptypein);
  }
}

void PlotAudioEditor::setPlaybackParam(int param, EditorTextBox* editor)
{
  bool ok=false;
  double doub;
  if (editor->isNumericText())
  {
    doub=editor->getDoubleValue();
    switch(param)
    {
    case Plotter::PlaybackMinKey:
    case Plotter::PlaybackMaxKey:
      ok=(doub >= 0.0 && doub <= 127.0);
      break;
    case Plotter::PlaybackDuration:
      ok=(doub > 0.0);
      break;
    case Plotter::PlaybackAmplitude:
      ok=(doub > 0.0 && doub <= 1.0);
      break;
    default:
      break;
    }
  }
  if (ok)
    plotter->setPlaybackParameter((Plotter::PlaybackParam)param, doub);
  else
    editor->setText(String(plotter->getPlaybackParameter((Plotter::PlaybackParam)param)), false);
}

/*=======================================================================*
                                Export Editor
 *=======================================================================*/

PlotExportEditor::PlotExportEditor (Plotter* pltr)
  : PlotEditor(pltr),
    exportlabel (0),
    exportmenu (0),
    syntaxlabel (0),
    syntaxmenu (0),
    fieldsbutton (0),
    formatlabel (0),
    formatmenu (0),
    decimalslabel (0),
    decimalsmenu (0),
    destlabel (0),
    destmenu (0),
    exportbutton (0),
    include(0)
{
  tabType=ExportEditor;
  setName(T("Export"));
  numfields=plotter->numFields();
  include=new bool[numfields];
  for (int i=0;i<numfields; i++) include[i]=true;

  addAndMakeVisible(exportlabel = new EditorLabel( T("Export:")));

  addAndMakeVisible (exportmenu = new ComboBox (String::empty));
  exportmenu->setEditableText (false);
  exportmenu->addItem (T("Points"), 1);
  exportmenu->addItem (T("Plot"), 2);
  exportmenu->setSelectedId(1);
  exportmenu->addListener(this);

  addAndMakeVisible(syntaxlabel=new EditorLabel(T("Syntax:")));

  addAndMakeVisible(syntaxmenu = new ComboBox (String::empty));
  syntaxmenu->setEditableText(false);
  syntaxmenu->addItem(T("Lisp"), TextIDs::Lisp);
  syntaxmenu->addItem(T("SAL"), TextIDs::Sal2);
  syntaxmenu->addItem(T("XML"), TextIDs::Xml);
  syntaxmenu->setSelectedId(TextIDs::Lisp);

  addAndMakeVisible(fieldsbutton = new EditorButton (T("Fields...")));
  fieldsbutton->addListener(this);

  addAndMakeVisible(formatlabel = new EditorLabel(T("Format:")));

  addAndMakeVisible(formatmenu = new ComboBox(String::empty));
  formatmenu->setEditableText (false);
  formatmenu->addItem(T("Envelope List"), 1);
  formatmenu->addItem(T("Point Records"), 2);
  formatmenu->setSelectedId(1);

  addAndMakeVisible(decimalslabel=new EditorLabel(T("Precision:")));
  addAndMakeVisible(decimalsmenu = new ComboBox(String::empty));
  decimalsmenu->addItem(T("Integer"), 1);
  decimalsmenu->addItem(T("0.0"), 2);
  decimalsmenu->addItem(T("0.00"), 3);
  decimalsmenu->addItem(T("0.000"), 4);
  decimalsmenu->setSelectedId(3);

  addAndMakeVisible(destlabel=new EditorLabel(T("Destination:")));

  addAndMakeVisible(destmenu = new ComboBox(String::empty));
  destmenu->addItem(T("New Edit Window"), 1);
  destmenu->addItem(T("Current Edit Window"), 2);
  destmenu->addItem(T("Clipboard"), 3);
  destmenu->setSelectedId(1);

  addAndMakeVisible(exportbutton = new EditorButton(T("Export")));
  exportbutton->addListener(this);
}

PlotExportEditor::~PlotExportEditor()
{
  delete[] include;
  deleteAndZero (exportlabel);
  deleteAndZero (exportmenu);
  deleteAndZero (syntaxlabel);
  deleteAndZero (syntaxmenu);
  deleteAndZero (fieldsbutton);
  deleteAndZero (formatlabel);
  deleteAndZero (formatmenu);
  deleteAndZero (decimalslabel);
  deleteAndZero (decimalsmenu);
  deleteAndZero (destlabel);
  deleteAndZero (destmenu);
  deleteAndZero (exportbutton);
}

void PlotExportEditor::resized()
{
  int x=margin;
  int y=margin;
  exportlabel->setTopLeftPosition (x, y);
  exportmenu->setBounds (exportlabel->getRight()+margin, y, 88, lineheight);
  syntaxlabel->setTopLeftPosition (exportmenu->getRight()+(margin*3), y);
  syntaxmenu->setBounds (syntaxlabel->getRight()+margin, y, 80, lineheight);
  fieldsbutton->setTopLeftPosition (syntaxmenu->getRight()+(margin*3), y);
  // line 2
  x=margin;
  y+=(lineheight+margin);
  formatlabel->setTopLeftPosition (x, y);
  formatmenu->setBounds (formatlabel->getRight()+margin, y, 150, lineheight);
  decimalslabel->setTopLeftPosition (formatmenu->getRight()+(margin*3), y);
  decimalsmenu->setBounds (decimalslabel->getRight()+margin, y, 80, lineheight);
  // line 3
  x=margin;
  y+=(lineheight+margin);
  destlabel->setTopLeftPosition (x, y);
  destmenu->setBounds (destlabel->getRight()+margin, y, 160, lineheight);
  exportbutton->setBounds (destmenu->getRight()+(margin*3), y, 150, lineheight);
}


void PlotExportEditor::buttonClicked (Button* button)
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

void PlotExportEditor::comboBoxChanged(ComboBox* cbox)
{
  if (cbox==exportmenu)
  {
    int id=cbox->getSelectedId();
    if (id==1) // export layer
    {
      syntaxlabel->setEnabled(true);
      syntaxmenu->setEnabled(true);
      fieldsbutton->setEnabled(true);
      formatlabel->setEnabled(true);
      formatmenu->setEnabled(true);
      decimalslabel->setEnabled(true);
      decimalsmenu->setEnabled(true);
    }
    else // export plot as xml
    {
      syntaxlabel->setEnabled(false);
      syntaxmenu->setEnabled(false);
      fieldsbutton->setEnabled(false);
      formatlabel->setEnabled(false);
      formatmenu->setEnabled(false);
      decimalslabel->setEnabled(false);
      decimalsmenu->setEnabled(false);
    }
  }
  else
  {
  }      
}

void PlotExportEditor::exportPlot() 
{
  PlotWindow* p=(PlotWindow*)plotter->getTopLevelComponent();
  String text=p->toXmlString();
  int destination=destmenu->getSelectedId();
  if (destination==1) // to new edit window
    new CodeEditorWindow(File::nonexistent, text, TextIDs::Text);
  else if (destination==2) // to existing edit window
    {
      CodeEditorWindow* e=CodeEditorWindow::getFocusCodeEditor();
      if (e)
	e->getCodeBuffer()->insertTextAtCaret(text);
      else
	new CodeEditorWindow(File::nonexistent, text, TextIDs::Text);
    }
  else if (destination==3) // to clipboard
    SystemClipboard::copyTextToClipboard(text);
}

void PlotExportEditor::exportPoints() 
{
  bool layerexport=true; //(exportmenu->getSelectedId()==1);
  int exportid=syntaxmenu->getSelectedId();
  int decimals=decimalsmenu->getSelectedId()-1;
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
    new CodeEditorWindow(File::nonexistent, text, exportid);
  else if (destination==2) // to existing edit window
    {
      CodeEditorWindow* w=CodeEditorWindow::getFocusCodeEditor();
      if (w)
	w->getCodeBuffer()->insertTextAtCaret(text);
      else
	new CodeEditorWindow(File::nonexistent, text, exportid);
    }
  else if (destination==3) // to clipboard
    SystemClipboard::copyTextToClipboard(text);
}
