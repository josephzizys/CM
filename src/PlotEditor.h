/*=======================================================================*
  Copyright (C) 2011 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#ifndef PLOTTERTABS_H
#define PLOTTERTABS_H

#include "juce.h"
#include <iostream>

class Plotter;
class Layer;

/** the base class for tabbed plotter components. subclasses override
    whichever listener definitions they need to implement **/

class PlotterTab : public Component,
  public Button::Listener, public TextEditor::Listener,
  public Slider::Listener, public ComboBox::Listener
{
 public:
  static const int margin=8;
  static const int lineheight=24;
  static const int fontsize=15;
  Plotter* plotter;
  PlotterTab (Plotter* pltr) : plotter (pltr) {}
  ~PlotterTab () {}
  void textEditorReturnKeyPressed(TextEditor& editor) {/*std::cout << "return key pressed\n";*/}
  void textEditorTextChanged(TextEditor& editor) {/*std::cout << "text changed\n";*/}
  void textEditorEscapeKeyPressed(TextEditor& editor) {/*std::cout << "escape key pressed\n";*/}
  void textEditorFocusLost(TextEditor& editor) {/*std::cout << "lost focus\n";*/}
  void buttonClicked (Button* buttonThatWasClicked) {/*std::cout << "button clicked\n";*/}
  void sliderValueChanged (Slider* sliderThatWasMoved) {/*std::cout << "slider moved\n";*/}
  void comboBoxChanged(ComboBox* combo) {/*std::cout << "combo box changed\n";*/}
};

class TabLabel : public Label
{
 public:
 TabLabel(String text) : Label(String::empty, text)
  {
    Font font (PlotterTab::fontsize, Font::plain);
    setFont (font);
    setJustificationType (Justification::centredLeft);
    setEditable (false, false, false);
    setColour (Label::textColourId, Colours::black);
    setColour (Label::backgroundColourId, Colour(0x0)); // Colours::red
    setSize((int)(font.getStringWidthFloat(getText())+10.0), PlotterTab::lineheight);
  }
  ~TabLabel()
  {
  }
};

class TabButton : public TextButton
{
 public:

 TabButton(String text, int width=0, int height=0) : TextButton(text)
  {
    if (height==0)
      height=PlotterTab::lineheight;
    if (width==0)
    {
      changeWidthToFitText(height);
      // add a bit more width to what Juce otherwise does
      width=getWidth() + 16; 
    }
    setSize(width, height);
  }

  ~TabButton()
  {
  }
};

/** a one-line text buffer component with some extra methods for text handling **/

class TabEditor : public TextEditor
{

 public:

 TabEditor(String text=String::empty)
   : TextEditor()
  {
    setText(text);
    setMultiLine(false);
    setReturnKeyStartsNewLine(false);
    setReadOnly(false);
    setScrollbarsShown (false);
    setCaretVisible(true);
    setPopupMenuEnabled(true);
    setFont(Font(15.0000f, Font::plain));
  }

  ~TabEditor()
  {
  }

  String getTrimmedText()
  {
    String txt=getText();
    if (txt.isEmpty()) return txt;
    int siz=txt.length();
    if (txt[0]==T(' ') || txt[0]==T('\t') )
      txt=txt.trim();
    else if (siz>1 && (txt[siz-1]==T(' ') || txt[siz-1]==T('\t') ))
      txt=txt.trim();
    return txt;
  }

  bool isNumericalText()
  {
    const String num=getTrimmedText();
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
};

class PlotWindowTab : public PlotterTab
{
 public:
  PlotWindowTab (Plotter* pltr, TopLevelWindow* win);
  ~PlotWindowTab();
 private:
  TabLabel* namelabel;
  TabEditor* namebuffer;
  TabButton* savebutton;
  TabButton* layerbutton;
  void resized ();
  void buttonClicked (Button* buttonThatWasClicked);
  void textEditorReturnKeyPressed(TextEditor& editor);
};

class PlotterAxisTab : public PlotterTab 
{
 private:
  int orientation;
  bool axistypechanged;
 public:
  PlotterAxisTab (Plotter* pl, int orient);
  ~PlotterAxisTab();
  void resized();
  void comboBoxChanged(ComboBox* combo);
  void textEditorReturnKeyPressed(TextEditor& editor);
  void sliderValueChanged (Slider* sliderThatWasMoved);
  void buttonClicked (Button* buttonThatWasClicked);
 private:
  TabLabel* namelabel;
  TabLabel* fromlabel;
  TabLabel* tolabel;
  TabLabel* bylabel;
  TabLabel* typelabel;
  TabLabel* decimalslabel;
  TabLabel* tickslabel;
  ComboBox* typemenu;
  TabEditor* namebuffer;
  TabEditor* frombuffer;
  TabEditor* tobuffer;
  TabEditor* bybuffer;
  TabEditor* ticksbuffer;
  ComboBox* decimalsmenu;
  TabLabel* zoomlabel;
  Slider* zoomslider;
  ToggleButton* fitcheckbox;
};

class LayerTab : public PlotterTab, public ChangeListener
{
 public:
  LayerTab (Plotter* pltr, Layer* layr);
  ~LayerTab();
 private:
  Layer* layer;
  TabLabel* namelabel;
  TabEditor* namebuffer;
  TabLabel* stylelabel;
  ComboBox* stylemenu;
  ColourSelector* colorpicker;
  void resized();
  void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
  //  void buttonClicked (Button* buttonThatWasClicked);
  void changeListenerCallback(ChangeBroadcaster* source);
  void textEditorReturnKeyPressed(TextEditor& editor);
};
#endif

