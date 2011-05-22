/*=======================================================================*
  Copyright (C) 2011 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#ifndef PlotEditor_h
#define PlotEditor_h

#include "Libraries.h"

class Plotter;
class Layer;
class Transport;

/** A TabbedComponent that holds various editors for working with plot data. **/

class PlotTabbedEditor : public TabbedComponent
{
 public:
  PlotTabbedEditor();
  ~PlotTabbedEditor();
  void currentTabChanged (int newCurrentTabIndex, const String &newCurrentTabName);
};

/** the base class for tabbed plot editors. subclasses override
    whichever listener definitions they need to implement **/

class PlotEditor : public Component,
  public Button::Listener, public TextEditor::Listener,
  public Slider::Listener, public ComboBox::Listener
{
 public:
  static const int margin=8;
  static const int lineheight=24;
  static const int fontsize=15;
  enum TabTypes {TabEmpty=0, TabWindow, TabAudio, TabExport, TabAxis, TabLayer, TabPoints};
  int tabType;
  Plotter* plotter;
  PlotEditor (Plotter* pltr) : plotter (pltr), tabType(TabEmpty) {}
  ~PlotEditor () {}
  void textEditorReturnKeyPressed(TextEditor& editor) {/*std::cout << "return key pressed\n";*/}
  void textEditorTextChanged(TextEditor& editor) {/*std::cout << "text changed\n";*/}
  void textEditorEscapeKeyPressed(TextEditor& editor) {/*std::cout << "escape key pressed\n";*/}
  void textEditorFocusLost(TextEditor& editor) {/*std::cout << "lost focus\n";*/}
  void buttonClicked (Button* buttonThatWasClicked) {/*std::cout << "button clicked\n";*/}
  void sliderValueChanged (Slider* sliderThatWasMoved) {/*std::cout << "slider moved\n";*/}
  void comboBoxChanged(ComboBox* combo) {/*std::cout << "combo box changed\n";*/}
  TabbedComponent* getTabbedComponent() {return (TabbedComponent*)getParentComponent();}
};

// GUI componets used in the various editors

class EditorLabel : public Label
{
 public:
 EditorLabel(String text) : Label(String::empty, text)
  {
    Font font (PlotEditor::fontsize, Font::plain);
    setFont (font);
    setJustificationType (Justification::centredLeft);
    setEditable (false, false, false);
    setColour (Label::textColourId, Colours::black);
    setColour (Label::backgroundColourId, Colour(0x0)); // Colours::red  
    setSize((int)(font.getStringWidthFloat(getText()+T("  "))), PlotEditor::lineheight);
  }
  ~EditorLabel()
  {
  }
};

class EditorButton : public TextButton
{
 public:

 EditorButton(String text, int width=0, int height=0) : TextButton(text)
  {
    if (height==0)
      height=PlotEditor::lineheight;
    if (width==0)
    {
      changeWidthToFitText(height);
      // add a bit more width to what Juce otherwise does
      width=getWidth() + 16; 
    }
    setSize(width, height);
  }

  ~EditorButton()
  {
  }
};

/** a one-line text buffer component with some extra methods for text handling **/

class EditorTextBox : public TextEditor
{

 public:

 EditorTextBox(String text=String::empty)
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

  ~EditorTextBox()
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

  double getDoubleValue()
  {
    return getTrimmedText().getDoubleValue();
  }

  int getIntValue()
  {
    return getTrimmedText().getIntValue();
  }

  bool isNumericText()
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

class PlotWindowEditor : public PlotEditor
{
 public:
  PlotWindowEditor (Plotter* pltr, TopLevelWindow* win);
  ~PlotWindowEditor();
 private:
  EditorLabel* namelabel;
  EditorTextBox* namebuffer;
  EditorButton* savebutton;
  EditorButton* layerbutton;
  void resized ();
  void buttonClicked (Button* buttonThatWasClicked);
  void textEditorReturnKeyPressed(TextEditor& editor);
};

class PlotAxisEditor : public PlotEditor 
{
 private:
  int orientation;
  bool axistypechanged;
 public:
  PlotAxisEditor (Plotter* pl, int orient);
  ~PlotAxisEditor();
  void resized();
  void comboBoxChanged(ComboBox* combo);
  void textEditorReturnKeyPressed(TextEditor& editor);
  void sliderValueChanged (Slider* sliderThatWasMoved);
  void buttonClicked (Button* buttonThatWasClicked);
 private:
  EditorLabel* namelabel;
  EditorLabel* fromlabel;
  EditorLabel* tolabel;
  EditorLabel* bylabel;
  EditorLabel* typelabel;
  EditorLabel* decimalslabel;
  EditorLabel* tickslabel;
  ComboBox* typemenu;
  EditorTextBox* namebuffer;
  EditorTextBox* frombuffer;
  EditorTextBox* tobuffer;
  EditorTextBox* bybuffer;
  EditorTextBox* ticksbuffer;
  ComboBox* decimalsmenu;
  EditorLabel* zoomlabel;
  Slider* zoomslider;
  ToggleButton* fitcheckbox;
};

class PlotLayerEditor : public PlotEditor, public ChangeListener
{
 public:
  PlotLayerEditor (Plotter* pltr, Layer* layr);
  ~PlotLayerEditor();
 private:
  Layer* layer;
  EditorLabel* namelabel;
  EditorTextBox* namebuffer;
  EditorLabel* stylelabel;
  ComboBox* stylemenu;
  ColourSelector* colorpicker;
  void resized();
  void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
  void changeListenerCallback(ChangeBroadcaster* source);
  void textEditorReturnKeyPressed(TextEditor& editor);
};

class PlotExportEditor : public PlotEditor
{
 public:
  int numfields;
  bool* include;
  EditorLabel* exportlabel;
  ComboBox* exportmenu;
  EditorLabel* syntaxlabel;
  ComboBox* syntaxmenu;
  TextButton* fieldsbutton;
  EditorLabel* formatlabel;
  ComboBox* formatmenu;
  EditorLabel* decimalslabel;
  ComboBox* decimalsmenu;
  EditorLabel* destlabel;
  ComboBox* destmenu;
  EditorButton* exportbutton;
  PlotExportEditor(Plotter* plotter);
  ~PlotExportEditor();
  void resized();
  void buttonClicked (Button* button);
  void comboBoxChanged (ComboBox* combobox);
  void exportPoints();
  void exportPlot();
};

class PlotAudioEditor : public PlotEditor
{
 public:
  PlotAudioEditor(Plotter* pltr);
  ~PlotAudioEditor();
 private:
  EditorLabel* y0label;
  EditorTextBox* y0typein;
  EditorLabel* y1label;
  EditorTextBox* y1typein;
  EditorLabel* tempolabel;
  EditorTextBox* tempotypein;
  EditorLabel* durlabel;
  EditorTextBox* durtypein;
  EditorLabel* amplabel;
  EditorTextBox* amptypein;
  Transport* transport;
  bool ismidiplot;
  void resized();
  void textEditorReturnKeyPressed(TextEditor& editor);
  void setPlaybackParam(int id, EditorTextBox* editor);
};


#endif

