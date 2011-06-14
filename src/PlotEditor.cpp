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
    //    std::cout << "window editor!\n";    
    break;
  case PlotEditor::AudioEditor:
    //    std::cout << "audio editor!\n";    
    break;
  case PlotEditor::AxisEditor:
    //    std::cout << "axis editor!\n";    
    break;
  case PlotEditor::LayerEditor:
    //    std::cout << "layer editor!\n";  
    {
      PlotLayerEditor* ple=(PlotLayerEditor*)editor;
      ple->deletebutton->setEnabled(ple->plotter->numLayers()>1);
      ple->plotter->setFocusLayer(ple->layer);
      ple->plotter->redrawAll();
    }
    break;
  case PlotEditor::ExportEditor:
    //    std::cout << "export editor!\n";    
    break;
  case PlotEditor::PointsEditor:
    //    std::cout << "points editor!\n";    
    break;
  default:
    //    std::cout << "unknown editor!\n";
    break;
  }
}

/*=======================================================================*
                                Window Editor
 *=======================================================================*/

PlotWindowEditor::PlotWindowEditor (Plotter* pltr, TopLevelWindow* win)
  : PlotEditor(pltr),
    namelabel(0),
    namebuffer (0),
    layerbutton (0),
    savebutton (0),
    bggroup (0),
    bggridcheckbox (0),
    bgplottingcheckbox (0),
    bgmouseablecheckbox (0),
    //    bgcolorlabel (0),
    bgcolorpicker (0),
    fieldgroup (0),
    fieldxlabel (0),
    fieldylabel (0),
    fieldxmenu (0),
    fieldymenu (0)
{
  tabType=WindowEditor;
  setName(T("Plot"));
  addAndMakeVisible(namelabel = new EditorLabel(T("Title:")));
  addAndMakeVisible(namebuffer = new EditorTextBox(win->getName()));
  namebuffer->addListener(this);
  addAndMakeVisible(layerbutton = new EditorButton (T("Add Layer")));
  layerbutton->addListener(this);
  addAndMakeVisible(savebutton = new EditorButton (T("Save...")));
  savebutton->addListener(this);

  addAndMakeVisible (bggroup = new GroupComponent(String::empty, T("Background")));
  addAndMakeVisible(bggridcheckbox = new EditorCheckBox(T("Draw grid")));
  bggridcheckbox->setToggleState(plotter->bgGrid, false);
  bggridcheckbox->addListener(this);
  addAndMakeVisible(bgplottingcheckbox = new EditorCheckBox(T("Plots visible")));
  bgplottingcheckbox->setToggleState(plotter->bgPlotting, false);
  bgplottingcheckbox->addListener(this);
  addAndMakeVisible(bgmouseablecheckbox = new EditorCheckBox(T("Plots mouseable")));
  bgmouseablecheckbox->setToggleState(plotter->bgMouseable, false);
  bgmouseablecheckbox->setEnabled(plotter->bgPlotting);
  bgmouseablecheckbox->addListener(this);

  //  addAndMakeVisible (bgcolorlabel = new EditorLabel( T("Color:")));
  addAndMakeVisible(bgcolorpicker = new ColourSelector( ColourSelector::showColourspace,4,0));
  bgcolorpicker->setCurrentColour(plotter->bgColor);
  bgcolorpicker->addChangeListener(this);

  addAndMakeVisible(fieldgroup=new GroupComponent(String::empty,T("Point Fields")));
  addAndMakeVisible(fieldxlabel = new EditorLabel(T("Horizontal:")));
  addAndMakeVisible (fieldxmenu = new ComboBox (String::empty));
  fieldxmenu->setEditableText (false);
  fieldxmenu->setJustificationType (Justification::centredLeft);
  addAndMakeVisible(fieldylabel = new EditorLabel(T("Vertical:")));
  addAndMakeVisible (fieldymenu = new ComboBox (String::empty));
  fieldymenu->setEditableText (false);
  fieldymenu->setJustificationType (Justification::centredLeft);
  for (int i=0; i<plotter->numFields(); i++)
    {
      if (plotter->getHorizontalAxis()==plotter->getFieldAxis(i))
      {
        fieldxmenu->addItem(plotter->getFieldName(i), i+1);
        if (plotter->isSharedField(i))
          fieldxmenu->setItemEnabled(i+1,false);
        else
          fieldxmenu->setSelectedId(i+1,false);
      }
      else
      {
        fieldymenu->addItem(plotter->getFieldName(i), i+1);
        if (plotter->isSharedField(i))
          fieldymenu->setItemEnabled(i+1,false);
        else if (plotter->getVerticalAxis()==plotter->getFieldAxis(i))
          fieldymenu->setSelectedId(i+1,false);
      }
    }
  fieldxmenu->addListener (this);
  fieldymenu->addListener (this);
  setVisible(true);
}

PlotWindowEditor::~PlotWindowEditor ()
{
  deleteAllChildren();
}

void PlotWindowEditor::resized ()
{
  int m=Dialog::Margin;
  int l=Dialog::LineHeight;
  int x=m;
  int y=m;
  int z=0;
  int s=Dialog::ItemSpacer;
  int w=0;
  namelabel->setTopLeftPosition(x, y);
  namebuffer->setBounds(namelabel->getRight()+z, y, 220, Dialog::LineHeight);
  layerbutton->setTopLeftPosition(namebuffer->getRight()+s, y);
  savebutton->setTopLeftPosition(layerbutton->getRight()+s, y);
  //  savebutton->setTopLeftPosition(getWidth()-savebutton->getWidth()-Dialog::Margin,
  //                                 getHeight()-lineheight-Dialog::Margin);
  x=m;
  y += Dialog::LineAndSpace;
  bggroup->setTopLeftPosition(x, y);
  y += Dialog::Margin*2;
  x += Dialog::Margin;
  bggridcheckbox->setTopLeftPosition(x, y);
  y += Dialog::Margin*2+3;//lineheight;
  bgplottingcheckbox->setTopLeftPosition(x, y);
  y += Dialog::Margin*2+3;//lineheight;
  bgmouseablecheckbox->setTopLeftPosition(x, y);
  bgcolorpicker->setBounds(bgmouseablecheckbox->getRight()+Dialog::ItemSpacer, bggridcheckbox->getY()-4,
                           120, lineheight*2+m*2); 
  bggroup->setSize(bgcolorpicker->getRight()-bggridcheckbox->getX()+(m*2), 
                   bgmouseablecheckbox->getBottom() - bggroup->getY() + Dialog::Margin - 6
                   );
  x=bggroup->getRight()+m;
  y=bggroup->getY();
  fieldgroup->setBounds(x, y, getWidth()-x-m, bggroup->getHeight());
  y += m*2;
  x += m;
  fieldxlabel->setTopLeftPosition(x,y);
  w=fieldgroup->getRight()-fieldxlabel->getRight()-m;
  fieldxmenu->setBounds(fieldxlabel->getRight()+z, y, w, l);
  y += Dialog::LineAndSpace;
  fieldylabel->setTopLeftPosition(x,y);
  fieldymenu->setBounds(fieldxlabel->getRight()+z, y, w, l);
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
    PlotTabbedEditor* editor=getPlotTabbedEditor();
    editor->addEditor(new PlotLayerEditor(plotter, layer));
  }
  else if (buttonThatWasClicked == bggridcheckbox)
  {
    plotter->bgGrid=bggridcheckbox->getToggleState();
    plotter->redrawBackView();
  }
  else if (buttonThatWasClicked == bgplottingcheckbox)
  {
    plotter->bgPlotting=bgplottingcheckbox->getToggleState();
    bgmouseablecheckbox->setEnabled(bgplottingcheckbox->getToggleState());
    plotter->redrawBackView();
  }
  else if (buttonThatWasClicked == bgmouseablecheckbox)
  {
    plotter->bgMouseable=bgmouseablecheckbox->getToggleState();
  }
}

void PlotWindowEditor::textEditorReturnKeyPressed(TextEditor& editor) 
{
  //std::cout << "PlotWindowEditor::textEditorReturnKeyPressed\n";
  EditorTextBox* ed=dynamic_cast<EditorTextBox*>(&editor);
  if (ed) ed->setTextChanged(false); else return;
  if (ed == namebuffer)
  {
    TopLevelWindow* w=(TopLevelWindow *)getTopLevelComponent();
    String n=namebuffer->getTrimmedText();
    if (n.isNotEmpty())
      w->setName(n);
  }
}

void PlotWindowEditor::changeListenerCallback (ChangeBroadcaster* source)
{
  if (source == bgcolorpicker)
  {
    Colour color=bgcolorpicker->getCurrentColour();
   plotter->bgColor=color;
   plotter->redrawBackView();
  }
}

void PlotWindowEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
  if (comboBoxThatHasChanged == fieldxmenu)
  {
    std::cout << "Horizontal field\n";
  }
  else if (comboBoxThatHasChanged == fieldymenu)
  {
    std::cout << "Vertical field\n";
  }
}

/*=======================================================================*
                                Audio Editor
 *=======================================================================*/

PlotAudioEditor::PlotAudioEditor(Plotter* pltr)
  : PlotEditor(pltr),
    ycheckbox (0),
    y0label (0),
    y0typein (0),
    y1label (0),
    y1typein (0),
    midioutmenu (0),
    tuninglabel (0),
    tuningmenu(0),
    transport (0)
{
  tabType=AudioEditor;
  setName(T("Audio"));

  addAndMakeVisible(ycheckbox = new EditorCheckBox(T("Vertical scaling")));
  ycheckbox->setToggleState(plotter->pbVerticalRescale, false);
  ycheckbox->addListener(this);
  ycheckbox->setColour(TextEditor::focusedOutlineColourId, Colour(0x00));

  addAndMakeVisible (y0label = new EditorLabel( T("min:")));
  addAndMakeVisible (y0typein = new EditorTextBox (String(plotter->pbMinKey)));
  y0typein->addListener(this);
  addAndMakeVisible (y1label = new EditorLabel( T("max:")));
  addAndMakeVisible (y1typein = new EditorTextBox (String(plotter->pbMaxKey)));
  y1typein->addListener(this);
  addAndMakeVisible (midioutmenu = new MidiOutPopupMenu (this, true, MidiOutPort::getInstance()->devid));

  addAndMakeVisible(tuninglabel = new EditorLabel(T("Tuning:")));
  addAndMakeVisible (tuningmenu = new ComboBox (String::empty));
  tuningmenu->setEditableText (false);
  tuningmenu->setJustificationType (Justification::centredLeft);
  tuningmenu->addItem (T("Semitone"), 1);
  tuningmenu->addItem (T("Quartertone"), 2);
  tuningmenu->setSelectedId(1, false);
  tuningmenu->addListener (this);
  // create a Transport for the Plotter
  double tempo= (plotter->getHorizontalAxis()->isType(Axis::percentage)) ? 500.0 : 60.0;
  addAndMakeVisible (transport = new Transport (plotter, tempo));
  transport->setTransportAspect(Transport::TempoMaximum, 600);
  transport->setTransportAspect(Transport::TempoSkewFactor, .5);
  // configure the playback thread for running
  plotter->pbThread->setTransport(transport);
  plotter->pbThread->setPlaybackLimit( plotter->getHorizontalAxis()->getMaximum());
  plotter->pbThread->startThread();
}

PlotAudioEditor::~PlotAudioEditor()
{
  deleteAndZero(ycheckbox);
  deleteAndZero(y0label);
  deleteAndZero(y0typein);
  deleteAndZero(y1label);
  deleteAndZero(y1typein);
  deleteAndZero(midioutmenu);
  deleteAndZero(tuninglabel);
  deleteAndZero(tuningmenu);
  deleteAndZero(transport);
}

void PlotAudioEditor::resized()
{
  int l=Dialog::LineHeight;
  int m=Dialog::Margin;
  int x=Dialog::Margin;
  int y=Dialog::Margin;
  int s=Dialog::LineAndSpace;
  int z=0;
  int h=Dialog::HalfMargin;
  int w=(int)y0typein->getFont().getStringWidthFloat(T("XXXXX"));
  int i=Dialog::ItemSpacer;

  midioutmenu->setBounds(x, y, 180, lineheight);
  x=midioutmenu->getRight()+l;
  ////transport->setTopLeftPosition((getWidth()/2)-(Transport::TransportWidthNoTempo/2), y);
  ycheckbox->setTopLeftPosition(x, y);
  x = ycheckbox->getRight()+0;
  y0label->setTopLeftPosition(x,y);
  x = y0label->getRight()+0;
  y0typein->setBounds(x,y,w,l);
  x = y0typein->getRight()+0;
  y1label->setTopLeftPosition(x,y);
  x = y1label->getRight()+0;
  y1typein->setBounds(x,y,w,l);  
  x = y1typein->getRight()+(Dialog::ItemSpacer*2);
  ////  y=midioutmenu->getBottom()+m;
  x=m;
  y += s;
  tuninglabel->setTopLeftPosition(x,y);
  x=tuninglabel->getRight()+h;
  tuningmenu->setBounds(x,y, 120, l);
  // transport display centered buttons
  y += s;
  transport->setTopLeftPosition((getWidth()/2)-(Transport::TransportWidthNoTempo/2), y);
}

void PlotAudioEditor::buttonClicked (Button* buttonThatWasClicked)
{
  if (buttonThatWasClicked == ycheckbox)
  {
    ScopedLock mylock (plotter->pbLock);
    bool state=ycheckbox->getToggleState();
    plotter->pbVerticalRescale=state;
    y0label->setEnabled(state);
    y0typein->setEnabled(state);
    y1label->setEnabled(state);
    y1typein->setEnabled(state);
  }
}

void PlotAudioEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
  if (comboBoxThatHasChanged == midioutmenu)
  {
    plotter->pbSetMidiOut(midioutmenu->getSelectedMidiOutputIndex());
  }
  else if (comboBoxThatHasChanged == tuningmenu)
  {
    ScopedLock mylock (plotter->pbLock);
    plotter->pbTuning=tuningmenu->getSelectedId();
    plotter->pbThread->sendMicrotuning(plotter->pbTuning);
  }
}

void PlotAudioEditor::textEditorReturnKeyPressed(TextEditor& editor)
{
  //std::cout << "PlotAudioEditor::textEditorReturnKeyPressed\n";
  EditorTextBox* ed=dynamic_cast<EditorTextBox*>(&editor);
  if (ed) ed->setTextChanged(false); else return;

  if (&editor == y0typein)
  {
    ScopedLock mylock (plotter->pbLock);
    double key=y0typein->getDoubleValue();
    if (y0typein->isNumericText() && (key >= 0.0) && (key <= 127.0))
      plotter->pbMinKey=key;
    else
      y0typein->setText(String(plotter->pbMinKey), false);      
  }
  else if (&editor == y1typein)
  {
    ScopedLock mylock (plotter->pbLock);
    double key=y1typein->getDoubleValue();
    if (y1typein->isNumericText() && (key >= 0.0) && (key <= 127.0))
      plotter->pbMaxKey=key;
    else
      y1typein->setText(String(plotter->pbMaxKey), false);
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
    setName(T("Horizontal"));
               
  else
    setName(T("Vertical"));
               
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
  zoomslider->setEnabled(!axisview->isFitInView());

  addAndMakeVisible(fitcheckbox = new EditorCheckBox(T("Fit in view")));
  fitcheckbox->setToggleState(axisview->isFitInView(), false);
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
  int x=Dialog::Margin;
  int y=Dialog::Margin;
  int z=0;
  int w=(int)namebuffer->getFont().getStringWidthFloat(T("XXXXX"));
  int h=Dialog::HalfMargin;
  int s=Dialog::Margin;
  int l=Dialog::LineHeight;
  namelabel->setTopLeftPosition(x, y);
  namebuffer->setBounds (namelabel->getRight()+z, y, 120, l);
  typelabel->setTopLeftPosition(namebuffer->getRight()+s, y);
  typemenu->setBounds (typelabel->getRight()+z, y, 96, l);
  decimalslabel->setTopLeftPosition(typemenu->getRight()+s, y);
  decimalsmenu->setBounds (decimalslabel->getRight()+z, y, w, l);
  // line 2
  y += Dialog::LineAndSpace;
  fromlabel->setTopLeftPosition(x, y);
  frombuffer->setBounds (fromlabel->getRight()+z, y, w, l);
  tolabel->setTopLeftPosition(frombuffer->getRight()+s, y);
  tobuffer->setBounds (tolabel->getRight()+z, y, w, l);
  bylabel->setTopLeftPosition(tobuffer->getRight()+s, y);
  bybuffer->setBounds (bylabel->getRight()+z, y, w, l);
  tickslabel->setTopLeftPosition(bybuffer->getRight()+s, y);
  ticksbuffer->setBounds(tickslabel->getRight()+z, y, w, l);
  // line 3
  y += Dialog::LineAndSpace;
  zoomlabel->setTopLeftPosition(x, y);
  zoomslider->setBounds (56, y, 280, 24);
  fitcheckbox->setBounds (zoomslider->getRight()+s, y, 180, 24);
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
    axisview->setSpread(sliderThatWasMoved->getValue());
    plotter->resizeForSpread();
    plotter->redrawAll();
  }
}

void PlotAxisEditor::buttonClicked (Button* buttonThatWasClicked)
{
  AxisView* axisview = plotter->getAxisView(orientation);
  if (buttonThatWasClicked == fitcheckbox)
  {
    if (fitcheckbox->getToggleState())
    {
      axisview->setFitInView(true);
      zoomlabel->setEnabled(false);
      zoomslider->setValue(axisview->getSpread(), false);
      zoomslider->setEnabled(false);
      plotter->fitInView(plotter->getWidth()-80, plotter->getWidth()-60);
      plotter->resized();
    }
    else
    {
      axisview->setFitInView(false);
      zoomlabel->setEnabled(true);
      zoomslider->setEnabled(true);
      zoomslider->setValue(axisview->getSpread(), false);
    }
  }
}

void PlotAxisEditor::textEditorReturnKeyPressed (TextEditor& editor)
{
  //std::cout << "PlotAxisEditor::textEditorReturnKeyPressed\n";
  EditorTextBox* ed=dynamic_cast<EditorTextBox*>(&editor);
  if (ed) ed->setTextChanged(false); else return;

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
    //    axisview->repaint();
    //    plotter->resizeForSpread();
    plotter->redrawAll();
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
    deletebutton (0),
    stylelabel (0),
    stylemenu (0),
    linelabel (0),
    linetextbox (0),
    pointlabel (0),
    pointtextbox (0),
    barlabel (0),
    bartextbox (0),
    audiogroup (0),
    durlabel (0),
    durtypein(0),
    amplabel (0),
    amptypein (0),
    chanlabel (0),
    chantypein (0),
    colorlabel (0),
    colorpicker (0)
{
  tabType=LayerEditor;
  setName(layer->getLayerName());
  addAndMakeVisible (namelabel = new EditorLabel( T("Name:")));
  addAndMakeVisible (namebuffer = new EditorTextBox (layer->getLayerName()));
  namebuffer->addListener(this);
  addAndMakeVisible (deletebutton = new EditorButton (T("Delete Layer...")));
  deletebutton->setEnabled(plotter->numLayers()>1);
  deletebutton->addListener(this);

  // point line bar editors need to exist when style menu configs
  addAndMakeVisible(linelabel = new EditorLabel( T("Line:")));
  addAndMakeVisible(linetextbox = new EditorTextBox (String(layer->lineWidth)));
  linetextbox->addListener(this);
  addAndMakeVisible(pointlabel = new EditorLabel( T("Point:")));
  addAndMakeVisible (pointtextbox = new EditorTextBox (String(layer->pointWidth)));
  pointtextbox->addListener(this);
  addAndMakeVisible(barlabel = new EditorLabel( T("Bar:")));
  addAndMakeVisible(bartextbox = new EditorTextBox (String(layer->barWidth)));
  bartextbox->addListener(this);

  addAndMakeVisible (stylelabel = new EditorLabel (T("Style:")));
  addAndMakeVisible(stylemenu = new ComboBox (String::empty));
  stylemenu->setEditableText(false);
  stylemenu->setJustificationType(Justification::centredLeft);
  stylemenu->addItem(T("Envelope"), Layer::lineandpoint);
  stylemenu->addItem(T("Line"), Layer::line);
  stylemenu->addItem(T("Point"), Layer::point);
  stylemenu->addItem(T("Impulse"), Layer::impulse);
  stylemenu->addItem(T("Aerial"), Layer::vlineandpoint);
  stylemenu->addItem(T("Bar"), Layer::vbar);
  //  stylemenu->addItem(T("Horizontal Bar"), Layer::hbar);
  stylemenu->addItem(T("Piano Roll"), Layer::hbox);
  //  stylemenu->addItem(T("Vertical Box"), Layer::vbox);
  if (plotter->numFields()<=2)
  {
    stylemenu->setItemEnabled(Layer::hbox, false);
    //stylemenu->setItemEnabled(Layer::vbox, false);
  } 
  // add the listener before choosing so the selection will update the
  // line, point and bar sizes
  stylemenu->addListener (this);
  stylemenu->setSelectedId(layer->getLayerStyle());

  addAndMakeVisible (audiogroup = new GroupComponent(String::empty, T("Audio Defaults")));
  addAndMakeVisible (durlabel = new EditorLabel( T("Dur:")));
  addAndMakeVisible (durtypein = new EditorTextBox (String(layer->pbDur)));
  durtypein->addListener(this);
  addAndMakeVisible (amplabel = new EditorLabel( T("Amp:")));
  addAndMakeVisible (amptypein = new EditorTextBox (String(layer->pbAmp)));
  amptypein->addListener(this);
  addAndMakeVisible (chanlabel = new EditorLabel( T("Chan:")));
  addAndMakeVisible (chantypein = new EditorTextBox (String(layer->pbChan)));
  chantypein->addListener(this);

  addAndMakeVisible (colorlabel = new EditorLabel( T("Point Color:")));
  addAndMakeVisible(colorpicker = new ColourSelector( ColourSelector::showColourspace,4,0));
  colorpicker->setCurrentColour(layer->getLayerColor());
  colorpicker->addChangeListener(this);
}

PlotLayerEditor::~PlotLayerEditor()
{
  deleteAndZero (namelabel);
  deleteAndZero (namebuffer);
  deleteAndZero (deletebutton);
  deleteAndZero (stylelabel);
  deleteAndZero (stylemenu);
  deleteAndZero(linelabel);
  deleteAndZero(linetextbox);
  deleteAndZero(pointlabel);
  deleteAndZero(pointtextbox);
  deleteAndZero(barlabel);
  deleteAndZero(bartextbox);
  deleteAndZero(audiogroup);
  deleteAndZero(durlabel);
  deleteAndZero(durtypein);
  deleteAndZero(amplabel);
  deleteAndZero(amptypein);
  deleteAndZero(chanlabel);
  deleteAndZero(chantypein);
  deleteAndZero (colorlabel);
  deleteAndZero (colorpicker);
  //std::cout << "deleted layer editor\n";
}

void PlotLayerEditor::resized()
{
  int space=150-(Dialog::Margin*5);
  int w=(int)namebuffer->getFont().getStringWidthFloat(T("XXXXX"));
  int x=Dialog::Margin;
  int y=Dialog::Margin;
  int h=Dialog::HalfMargin;
  int z=0;

  namelabel->setBounds(x, y, 48, lineheight);
  x=namelabel->getRight()+h;
  namebuffer->setBounds(x, y, 120, lineheight);
  x=namebuffer->getRight()+Dialog::Margin;
  deletebutton->setTopLeftPosition(x,y);

  //  line 2
  x = Dialog::Margin;
  y += Dialog::LineAndSpace;
  stylelabel->setTopLeftPosition(x,y);
  x = stylelabel->getRight()+h;
  stylemenu->setBounds(x, y, 120, lineheight);
 
  //  line 3
  x = stylemenu->getRight()+Dialog::Margin;
  linelabel->setTopLeftPosition(x,y);
  x = linelabel->getRight()+z;
  linetextbox->setBounds(x,y,w,lineheight);
  x = linetextbox->getRight()+h;
  pointlabel->setTopLeftPosition(x,y);
  x = pointlabel->getRight()+z;
  pointtextbox->setBounds(x,y,w,lineheight);
  x = pointtextbox->getRight()+h;  
  barlabel->setTopLeftPosition(x,y);
  x = barlabel->getRight()+z;
  bartextbox->setBounds(x,y,w,lineheight);
  x = bartextbox->getRight()+Dialog::ItemSpacer;

  //  line 3
  y+=Dialog::LineAndSpace;
  x=Dialog::Margin;
  audiogroup->setTopLeftPosition(x, y);
  x += Dialog::Margin;
  y += Dialog::Margin*2;
  // dur
  durlabel->setTopLeftPosition(x,y);
  x = durlabel->getRight()+z;
  durtypein->setBounds(x,y,w,lineheight);  
  x = durtypein->getRight()+(Dialog::Margin*1);
  // amp
  amplabel->setTopLeftPosition(x,y);
  x = amplabel->getRight()+z;
  amptypein->setBounds(x,y,w,lineheight);  
  x = amptypein->getRight()+(Dialog::Margin*1);
  // chan
  chanlabel->setTopLeftPosition(x,y);
  x = chanlabel->getRight()+z;
  chantypein->setBounds(x,y,w,lineheight);  
  x = chantypein->getRight()+(Dialog::Margin*1);
  audiogroup->setSize(x-audiogroup->getX(), lineheight+Dialog::Margin*3);
  colorlabel->setTopLeftPosition(audiogroup->getRight()+Dialog::Margin, chanlabel->getY());
  // point color picker is large squre and is itself in dented
  colorpicker->setBounds(370, audiogroup->getY()-h, 120, lineheight*2+Dialog::Margin); //170*.66, space*.66

}

void PlotLayerEditor::buttonClicked (Button* button)
{
  if (button==deletebutton)
  {
    String text=T("Really delete layer '") + layer->getLayerName() + T("'?");
    if (layer->numPoints()>0) text<<T("\nAll point data will be lost.");
    if (!AlertWindow::showOkCancelBox(AlertWindow::WarningIcon, T("Delete Layer"),
                                      text, T("Delete Layer"), T("Cancel"), this))
      return;
    PlotTabbedEditor* editor=getPlotTabbedEditor();
    int index=editor->getTabIndex(this);
    //std::cout << "deleting plotter layer\n";
    plotter->removeLayer(layer);
    plotter->redrawBackView();
    plotter->redrawPlotView();
    delete layer;
    // select main tab because this one is going away!
    //std::cout << "selecting main tab\n";
    editor->setCurrentTabIndex(0);
    // remove ourselves
    //std::cout << "removing ourselves\n";
    editor->removeTab(index);
    //std::cout << "updating layer editors\n";
    // delete ourselves!
    //std::cout << "deleting ourselves\n";
    delete this;
  }
}

void PlotLayerEditor::comboBoxChanged (ComboBox* cbox)
{
  if (cbox == stylemenu)
  {
    int style=stylemenu->getSelectedId();
    layer->setLayerStyle(style);

    linelabel->setEnabled((style & Layer::line) );
    linetextbox->setEnabled(linelabel->isEnabled() );
    pointlabel->setEnabled((style & Layer::point) );
    pointtextbox->setEnabled(pointlabel->isEnabled() );
    barlabel->setEnabled((style & (Layer::bar | Layer::box)));
    bartextbox->setEnabled(barlabel->isEnabled() );
    plotter->redrawPlotView();
  }
}

void PlotLayerEditor::changeListenerCallback (ChangeBroadcaster* source)
{
  if (source == colorpicker)
  {
    Colour color=colorpicker->getCurrentColour();
    layer->setLayerColor(color);
    if (layer->isPoints())
      plotter->redrawPlotView();
    plotter->redrawHorizontalAxisView();
    plotter->redrawVerticalAxisView();
  }
}

void PlotLayerEditor::textEditorReturnKeyPressed(TextEditor& editor)
{
  //std::cout << "PlotLayerEditor::textEditorReturnKeyPressed\n";
  EditorTextBox* ed=dynamic_cast<EditorTextBox*>(&editor);
  if (ed) ed->setTextChanged(false); else return;

  if (ed == namebuffer)
  {
    String name=namebuffer->getTrimmedText();
    if (name.isEmpty())
      namebuffer->setText(layer->getLayerName(), false);
    else
    {
      setName(name);
      layer->setLayerName(name);
      tabButton->setButtonText(name);
    }
  }
  else if (ed == linetextbox)
  {
    double val=linetextbox->getDoubleValue();
    //std::cout << "linetextbox, val=" << val << "\n";
    if (linetextbox->isNumericText() && (val > 0.0) && (val <= 16.0))
    {
      layer->lineWidth=val;
      plotter->redrawPlotView();
    }
    else
      linetextbox->setText(String(layer->lineWidth), false);
  }
  else if (ed == pointtextbox)
  {
    double val=pointtextbox->getDoubleValue();
    //std::cout << "linetextbox, val=" << val << "\n";
    if (pointtextbox->isNumericText() && (val > 0.0) && (val <= 24.0))
    {
      layer->pointWidth=val;
      plotter->redrawPlotView();
    }
    else
      pointtextbox->setText(String(layer->pointWidth), false);
  }
  else if (ed == bartextbox)
  {
    double val=bartextbox->getDoubleValue();
    //std::cout << "linetextbox, val=" << val << "\n";
    if (bartextbox->isNumericText() && (val > 0.0) && (val <= 48.0))
    {
      layer->barWidth=val;
      plotter->redrawPlotView();
    }
    else
      bartextbox->setText(String(layer->barWidth), false);
  }
  else if (ed == durtypein)
  {
    ScopedLock mylock(plotter->pbLock);
    double dur=durtypein->getDoubleValue();
    if (durtypein->isNumericText() && (dur > 0.0))
    {
      //std::cout << "setting layer dur to " << dur << "\n";
      layer->pbDur=dur;
    }
    else
      durtypein->setText(String(layer->pbDur), false);
  }
  else if (ed == amptypein)
  {
    ScopedLock mylock(plotter->pbLock);
    double amp=amptypein->getDoubleValue();
    if (amptypein->isNumericText() && (amp >= 0.0))
    {
      //std::cout << "setting layer amp to " << amp << "\n";

      layer->pbAmp=amp;
    }
    else
      amptypein->setText(String(layer->pbAmp), false);
  }
  else if (ed == chantypein)
  {
    ScopedLock mylock(plotter->pbLock);
    int chan=chantypein->getIntValue();
    if (chantypein->isNumericText(false) && (chan >= 0 && chan <= 15))
      layer->pbChan=chan;
    else
      chantypein->setText(String(layer->pbChan), false);
  }
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
  int x=Dialog::Margin;
  int y=Dialog::Margin;
  exportlabel->setTopLeftPosition (x, y);
  exportmenu->setBounds (exportlabel->getRight()+Dialog::Margin, y, 88, lineheight);
  syntaxlabel->setTopLeftPosition (exportmenu->getRight()+(Dialog::Margin*3), y);
  syntaxmenu->setBounds (syntaxlabel->getRight()+Dialog::Margin, y, 80, lineheight);
  fieldsbutton->setTopLeftPosition (syntaxmenu->getRight()+(Dialog::Margin*3), y);
  // line 2
  x=Dialog::Margin;
  y+=Dialog::LineAndSpace;
  formatlabel->setTopLeftPosition (x, y);
  formatmenu->setBounds (formatlabel->getRight()+Dialog::Margin, y, 150, lineheight);
  decimalslabel->setTopLeftPosition (formatmenu->getRight()+(Dialog::Margin*3), y);
  decimalsmenu->setBounds (decimalslabel->getRight()+Dialog::Margin, y, 80, lineheight);
  // line 3
  x=Dialog::Margin;
  y+=Dialog::LineAndSpace;
  destlabel->setTopLeftPosition (x, y);
  destmenu->setBounds (destlabel->getRight()+Dialog::Margin, y, 160, lineheight);
  exportbutton->setBounds (destmenu->getRight()+(Dialog::Margin*3), y, 150, lineheight);
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

