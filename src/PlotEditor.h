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

/*=======================================================================*
                                 Editor Components
 *=======================================================================*/

class Dialog
{
 public:
  static const int Margin=8;
  static const int HalfMargin=Margin/2;
  static const int LineHeight=24;
  static const int LineAndSpace=LineHeight+Margin;
  static const int ItemSpacer=Margin;
  static const int FontSize=15;
};

/*=======================================================================*
                                 Label
 *=======================================================================*/

/** Label component with consistent self-sizing of label around
    text. **/

class EditorLabel : public Label
{
 public:
 EditorLabel(String text) : Label(String::empty, text)
  {
    Font font ((float)Dialog::FontSize, Font::plain);
    setFont (font);
    setJustificationType (Justification::centredLeft);
    setEditable (false, false, false);
    setColour (Label::textColourId, Colours::black);
    setColour (Label::backgroundColourId, Colour(0x0));
    setSize((int)(font.getStringWidthFloat(getText()+T("  "))), Dialog::LineHeight);
  }
  virtual ~EditorLabel()
  {
  }
};

/*=======================================================================*
                                 Button
 *=======================================================================*/

/** TextButton component with consistent self-sizing around text. **/

class EditorButton : public TextButton
{
 public:

 EditorButton(String text, int width=0, int height=0) : TextButton(text)
  {
    if (height==0)
      height=Dialog::LineHeight;
    if (width==0)
    {
      changeWidthToFitText(height);
      // add a bit more width to what Juce otherwise does
      width=getWidth() + 16; 
    }
    setSize(width, height);
  }

  virtual ~EditorButton(){}
};

/*=======================================================================*
                                 CheckBox
 *=======================================================================*/

/** ToggleButton component without focus outline. **/

class EditorCheckBox : public ToggleButton
{
 public:
  EditorCheckBox(String text)
    : ToggleButton(text)
  {
    Font font ((float)Dialog::FontSize, Font::plain);
    //setFont (font);
    setSize((int)(font.getStringWidthFloat(getButtonText()+T("     "))), Dialog::LineHeight);
    //changeWidthToFitText();
    setColour(TextEditor::focusedOutlineColourId, Colour(0x00));
  }
  virtual ~EditorCheckBox(){}
};

/*=======================================================================*
                                 TextBox
 *=======================================================================*/

/** A single line TextEditor with some extra methods for text
    handling **/

class EditorTextBox : public TextEditor
{
 private:

  bool textChanged;
  bool enterOnLoss;

 public:

 EditorTextBox(String text=String::empty)
   : TextEditor(),
    enterOnLoss(true),
    textChanged (false)
    {
      setWantsKeyboardFocus(true);
      setText(text);
      setMultiLine(false);
      setReturnKeyStartsNewLine(false);
      setReadOnly(false);
      setScrollbarsShown (false);
      setCaretVisible(true);
      setPopupMenuEnabled(true);
      setFont(Font(15.0000f, Font::plain));
    }

  virtual ~EditorTextBox() {}

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

  bool isEmpty()
  {
    return getTrimmedText().isEmpty();
  }

  /** Reimplemented juce method dims disabled text in edit box. **/

  void setEnabled(bool enabled)
  {
    TextEditor::setEnabled(enabled);
    setColour(TextEditor::textColourId, ((enabled) ? Colours::black :  Colours::grey));
    applyFontToAllText(getFont());
  }

  /** Returns a double value from the text box skipping white space. **/

  double getDoubleValue()
  {
    return getTrimmedText().getDoubleValue();
  }

  /** Returns an int value from the text box skipping white space. **/

  int getIntValue()
  {
    return getTrimmedText().getIntValue();
  }

  /** Returns true if editor text contains a valid int or a valid
      float (if floatOk is true.) **/

  bool isNumericText(bool floatOk=true)
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
        if (dots==0 && floatOk) dots++;
        else return false; // too many dots
      else if (num[i]<T('0') || num[i]>T('9')) 
        return false;
      else digi++;
    }
    return digi>0;
  }

  /** True if loss of focus enters text. **/

  bool doesLossOfFocusEnterText(){return enterOnLoss;}
  void setDoesLossOfFocusEnterText(bool enters){enterOnLoss=enters;}

  /** True if text marked as changed (set by a TextEditor::Listener). **/

  bool isTextChanged(){return textChanged;}

  /** Sets textChanged status in editor (used by TextEditor::Listener) methods. **/

  void setTextChanged(bool changed){textChanged=changed;}

};

/*=======================================================================*
                                 Midi Out Popup Menu
 *=======================================================================*/

/** A ComboBox menu containing all the avaliable MidiOut devices to
    choose from. See getSelectedMidiOut() for more information. **/

class MidiOutPopupMenu : public ComboBox
{
 public:

 MidiOutPopupMenu(ComboBox::Listener* listener, bool populate, int idToSelect=-1)
   : ComboBox(String::empty)
  {
    setEditableText(false);
    setTextWhenNoChoicesAvailable(T("No Midi Outs"));
    setTextWhenNothingSelected(T("Midi Outs"));
    if (listener)
      addListener(listener);
    if (populate)
      fill(idToSelect);
  }

  virtual ~MidiOutPopupMenu()
  {
    clear();
  }

  /** returns the MidiOut device index or -1 if no device is selected. **/

  int getSelectedMidiOutputIndex()
  {
    // subtract 1 because ComboBox ids always greater than zero.
    return getSelectedId() - 1;
  }

  /** Populates the menu with all the MidiOut devices. If idToSelect
      is greater than -1 it will become the selected device in the
      menu. **/

  void fill(int idToSelect=-1)
  {
    clear();
    StringArray devnames = MidiOutput::getDevices();    
    // add 1 to devnums because ComboBox ids must be greater than zero
    for (int i=0; i<devnames.size(); i++)
      addItem(devnames[i], i + 1);
    if (idToSelect>-1)
      setSelectedId(idToSelect + 1);     
  }
  // private:
  //mouseDown(const MouseEvent& e){} 	
};

/*=======================================================================*
                                 GraceEditor
 *=======================================================================*/

/** The base class for the various plot editors. Subclasses override
    the listener definitions they need to implement. **/

class PlotEditor : public Component,
  public Button::Listener, public TextEditor::Listener,
  public Slider::Listener, public ComboBox::Listener
{
 public:
  static const int margin=8;
  static const int lineheight=24;
  static const int fontsize=15;
  enum EditorType {Empty=0, WindowEditor, AudioEditor, ExportEditor, AxisEditor,
                   LayerEditor, PointsEditor};
  int tabType;
  Plotter* plotter;
  TabBarButton* tabButton;
  PlotEditor (Plotter* pltr) : plotter (pltr), tabType(Empty), tabButton (0)
  {
  }

  virtual ~PlotEditor ()
  {
  }

  void buttonClicked (Button* buttonThatWasClicked) {/*std::cout << "button clicked\n";*/}
  void comboBoxChanged(ComboBox* combo) {/*std::cout << "combo box changed\n";*/}
  void sliderValueChanged (Slider* sliderThatWasMoved) {/*std::cout << "slider moved\n";*/}
  void textEditorReturnKeyPressed(TextEditor& editor) {/*std::cout << "editor return key pressed\n";*/}

  /** The default text changed callback marks the textbox it was
      called from as 'changed'. **/

  void textEditorTextChanged(TextEditor& editor) 
  {
    //std::cout << "EditorTextBox::textEditorTextChanged\n";
    EditorTextBox* ed=dynamic_cast<EditorTextBox*>(&editor);
    if (ed)
      ed->setTextChanged(true);
  }

  void textEditorFocusLost(TextEditor& editor) 
  {
    //std::cout << "EditorTextBox::textEditorFocusLost\n";
    EditorTextBox* ed=dynamic_cast<EditorTextBox*>(&editor);
    if (ed  && ed->doesLossOfFocusEnterText() && ed->isTextChanged())
    {
      textEditorReturnKeyPressed(editor);
      ed->setTextChanged(false);
    }
  }

  void textEditorEscapeKeyPressed(TextEditor& editor) {/*std::cout << "editor escape key pressed\n";*/}

  PlotTabbedEditor* getPlotTabbedEditor()
  {
    return (PlotTabbedEditor*)getParentComponent();
  }

  TabBarButton* getTabButton()
  {
    return tabButton;
  }

};

/*=======================================================================*
                                PlotWindowEditor
 *=======================================================================*/

/** The Window tab editor **/

class PlotWindowEditor : public PlotEditor, public ChangeListener
{
 public:
  PlotWindowEditor (Plotter* pltr, TopLevelWindow* win);
  virtual ~PlotWindowEditor();
 private:
  EditorLabel* namelabel;
  EditorTextBox* namebuffer;
  EditorButton* savebutton;
  EditorButton* layerbutton;
  GroupComponent* bggroup;
  EditorCheckBox* bggridcheckbox;
  EditorCheckBox* bgplottingcheckbox;
  EditorCheckBox* bgmouseablecheckbox;
  //  EditorLabel* bgcolorlabel;
  ColourSelector* bgcolorpicker;

  GroupComponent* fieldgroup;
  EditorLabel* fieldxlabel;
  EditorLabel* fieldylabel;
  ComboBox* fieldxmenu;
  ComboBox* fieldymenu;
  void resized ();
  void buttonClicked (Button* buttonThatWasClicked);
  void textEditorReturnKeyPressed(TextEditor& editor);
  void changeListenerCallback (ChangeBroadcaster* source);
  void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
};

/*=======================================================================*
                                PlotAudioEditor
 *=======================================================================*/

/** The Audio tab editor. **/
 
class PlotAudioEditor : public PlotEditor
{
 public:
  PlotAudioEditor(Plotter* pltr);
  virtual  ~PlotAudioEditor();
 private:
  EditorCheckBox* ycheckbox;
  EditorLabel* y0label;
  EditorTextBox* y0typein;
  EditorLabel* y1label;
  EditorTextBox* y1typein;
  Transport* transport;
  MidiOutPopupMenu* midioutmenu;
  EditorLabel* tuninglabel;
  ComboBox* tuningmenu;
  void resized();
  void buttonClicked (Button* buttonThatWasClicked);
  void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
  void textEditorReturnKeyPressed(TextEditor& editor);
  //  void textEditorFocusLost(TextEditor& editor);
  //  void textEditorTextChanged(TextEditor& editor);
};

/*=======================================================================*
                                PlotAxisEditor
 *=======================================================================*/

/** The Axis tab editor **/

class PlotAxisEditor : public PlotEditor 
{
 private:
  int orientation;
  bool axistypechanged;
 public:
  PlotAxisEditor (Plotter* pl, int orient);
  virtual ~PlotAxisEditor();
  void resized();
  void buttonClicked (Button* buttonThatWasClicked);
  void comboBoxChanged(ComboBox* combo);
  void sliderValueChanged (Slider* sliderThatWasMoved);
  void textEditorReturnKeyPressed(TextEditor& editor);
  //  void textEditorFocusLost(TextEditor& editor);
  //  void textEditorTextChanged(TextEditor& editor);
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
  EditorCheckBox* fitcheckbox;
};

/*=======================================================================*
                                PlotLayerEditor
 *=======================================================================*/

/** The Layer tab editor **/

class PlotLayerEditor : public PlotEditor, public ChangeListener
{
 public:
  PlotLayerEditor (Plotter* pltr, Layer* layr);
  virtual ~PlotLayerEditor();
  EditorButton* deletebutton;  // for enable/disable 
  Layer* layer;
 private:
  EditorLabel* namelabel;
  EditorTextBox* namebuffer;
  EditorLabel* stylelabel;
  ComboBox* stylemenu;
  EditorLabel* linelabel;
  EditorTextBox* linetextbox;
  EditorLabel* pointlabel;
  EditorTextBox* pointtextbox;
  EditorLabel* barlabel;
  EditorTextBox* bartextbox;
  GroupComponent* audiogroup;
  EditorLabel* durlabel;
  EditorTextBox* durtypein;
  EditorLabel* amplabel;
  EditorTextBox* amptypein;
  EditorLabel* chanlabel;
  EditorTextBox* chantypein;
  EditorLabel* colorlabel;
  ColourSelector* colorpicker;
  void resized();
  void buttonClicked (Button* buttonThatWasClicked);
  void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
  void changeListenerCallback(ChangeBroadcaster* source);
  void textEditorReturnKeyPressed(TextEditor& editor);
  //  void textEditorFocusLost(TextEditor& editor);
  //  void textEditorTextChanged(TextEditor& editor);
};

/*=======================================================================*
                                PlotExportEditor
 *=======================================================================*/

/** The Export tab editor. **/

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
  virtual ~PlotExportEditor();
  void resized();
  void buttonClicked (Button* button);
  void comboBoxChanged (ComboBox* combobox);
  void exportPoints();
  void exportPlot();
};

/*=======================================================================*
                                 Tabbed Plot Editor
 *=======================================================================*/

/** A TabbedComponent that holds various editors for working with plot data. **/

class PlotTabbedEditor : public TabbedComponent
{
 public:
  Colour bgcolor;
  PlotTabbedEditor();
  virtual ~PlotTabbedEditor();

  void addEditor(PlotEditor* editor)
  {
    addTab(editor->getName(), bgcolor, editor, true);
    // cache the new editor's tab button in the editor
    for (int i=0; i<getNumTabs(); i++)
      if (editor == getTabContentComponent(i))
      {
        editor->tabButton=getTabbedButtonBar().getTabButton(i);
        break;
      }
  }

  void deleteEditor(PlotEditor* editor)
  {
  }


  int getTabIndex(Component* ed)
  {
    for (int i=0; i<getNumTabs(); i++)
      if (getTabContentComponent(i)==ed)
        return i;
    return -1;
  }

  void currentTabChanged (int newCurrentTabIndex, const String &newCurrentTabName);
};

#endif

