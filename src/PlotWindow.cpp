/*=======================================================================*
  Copyright (c) 2011 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#include "Enumerations.h"
#include "Menus.h"
#include "Console.h"
#include "CodeEditor.h"
#include "Plot.h"
#include "PlotEditor.h"
#include "PlotWindow.h"
#include "Midi.h"
#include "Scheme.h"

#include "CmSupport.h"
#include "Alerts.h"

/*=======================================================================*
           PlotWindowComponent: window's content component that
           contains the plotter and the tabview
 *=======================================================================*/

class PlotWindowComponent : public Component
{
  PlotWindow* plotwin;
public:
  static const int plotviewwidth=500;

  // total height of tabbed editor is 5 lineheight plus 5 margins: tab
  // is 1 line, content is 4 lines and 5 margins
  static const int tabviewheight=(PlotEditor::lineheight*5)+(PlotEditor::margin*5);

  PlotWindowComponent (PlotWindow* win) : plotwin (win) {}

  virtual ~PlotWindowComponent () 
  {
    // this deletes the Plotter and the TabbedEditor
    std::cout << "deleting PlotWindowComponent\n";
    deleteAllChildren();
  }
  void resized ()
  {
    int w=getWidth();
    int h=getHeight();
    std::cout << "PlotWindowComponent::resized(" << w << ", " << h << ")\n";
    plotwin->plotter->fitInView(w-80,(h-tabviewheight)-60);
    plotwin->plotter->setBounds(0,0,w,(h-tabviewheight));
    plotwin->tabview->setBounds(0,h-tabviewheight,w,tabviewheight);
  }
};

/*=======================================================================*
                   PlotWindow: top level window for plotting
 *=======================================================================*/

PointClipboard pointClipboard;

PlotWindow::PlotWindow(XmlElement* plot)
  : DocumentWindow (String::empty, Colours::white, DocumentWindow::allButtons, true)
{
  listener.window=this;
  String title=(plot==NULL) ? T("Untitled Plot") :
    plot->getStringAttribute(T("title"), T("Untitled Plot"));
  setName(title);
  plotter = new Plotter(plot) ;
  tabview = new PlotTabbedEditor();
  plotter->editor=tabview;
  init();
}

PlotWindow::PlotWindow(String title, MidiFile& midifile)
  : DocumentWindow (title, Colours::white, DocumentWindow::allButtons, true)
{
  listener.window=this;
  setName(title);
  plotter=new Plotter(midifile);
  tabview = new PlotTabbedEditor();
  plotter->editor=tabview;
  init();
}

PlotWindow::~PlotWindow ()
{
  //  delete menubar;
  //  setMenuBar(0);
}

void PlotWindow::init()
{
  //  menubar = new MenuBarComponent(this);
  //  setMenuBar(this);
  setVisible(true);
  setUsingNativeTitleBar(true);    
  //  std::cout << "PlotWindow::init (sizing plotter)\n";
  //  plotter->setSize(PlotWindowComponent::plotviewwidth, PlotWindowComponent::plotviewwidth);
  std::cout << "PlotWindow::init (adding window tab)\n";
  tabview->addEditor(new PlotWindowEditor(plotter, this));
  //  std::cout << "PlotWindow::init (adding audio tab)\n";
  tabview->addEditor(new PlotAudioEditor(plotter));
  //  std::cout << "PlotWindow::init (adding export tab)\n";
  tabview->addEditor(new PlotExportEditor(plotter));
  //  std::cout << "PlotWindow::init (adding X Axis tab)\n";
  tabview->addEditor(new PlotAxisEditor(plotter, Plotter::horizontal));
  //  std::cout << "PlotWindow::init (adding Y Axis tab)\n";
  tabview->addEditor(new PlotAxisEditor(plotter, Plotter::vertical));

  for (int i=0; i<plotter->numLayers(); i++)
  {
    Layer* layer=plotter->getLayer(i);
    //    std::cout << "PlotWindow::init (adding layer tab)\n";
    tabview->addEditor(new PlotLayerEditor(plotter,layer));
  }
  //  std::cout << "PlotWindow::init (creating PlotWindowComponent)\n";
  PlotWindowComponent* content=new PlotWindowComponent(this);
  //  std::cout << "PlotWindow::init (set plotter visible)\n";
  plotter->setVisible(true);
  //  std::cout << "PlotWindow::init (set tabview visible)\n";
  tabview->setVisible(true);
  //  std::cout << "PlotWindow::init (set content visible)\n";
  content->setVisible(true);
  //  std::cout << "PlotWindow::init (add child plotter)\n";
  content->addChildComponent(plotter);
  //  std::cout << "PlotWindow::init (add child tabview)\n";
  content->addChildComponent(tabview);

  setResizable(true, true); 
  std::cout << "PlotWindow::init (setContentComponent)\n";  
  setContentComponent(content, false, false);
  std::cout << "PlotWindow::init (center with size)\n";
  //  std::cout << "PlotWindow::init (set resizable)\n";
  WindowTypes::setWindowType(this, WindowTypes::PlotWindow);
  std::cout << "PlotWindow::init (insure points visible)\n";
  plotter->insurePointsVisible();
  std::cout << "PlotWindow::init (resizeForSpread)\n";
  plotter->resizeForSpread();
  std::cout << "PlotWindow::init (checkFitInView)\n";
  plotter->checkFitInView();
  std::cout << "PlotWindow::init (fitInView)\n";
  plotter->fitInView();
  centreWithSize (PlotWindowComponent::plotviewwidth, PlotWindowComponent::plotviewwidth + PlotWindowComponent::tabviewheight);
  //  std::cout << "PlotWindow::init (DONE)\n";
}

PlotWindow* PlotWindow::getPlotWindow(String title)
{
  for (int i=0; i<TopLevelWindow::getNumTopLevelWindows(); i++)
    {
      TopLevelWindow* w=TopLevelWindow::getTopLevelWindow(i);
      if (WindowTypes::isWindowType(w, WindowTypes::PlotWindow) &&
	  w->getName()==title)
	return (PlotWindow*)w;
    }
  return NULL;
}

bool PlotWindow::hasUnsavedChanges()
{
  return plotter->hasUnsavedChanges();
}

// This is called from Scheme to open a new plot window.
// in this case we want to set it to changed if there
// are any points at all

void PlotWindow::openWindowFromXml(void* ptr) //(String str)
{
  //std::cout << str.toUTF8() << "\n";
  XmlDocument doc (String((char *)ptr));
  XmlElement* xml = doc.getDocumentElement();
  if (xml && xml->getChildByName(T("fields")) &&
      xml->getChildByName(T("layers")))
  {
    PlotWindow* w = new PlotWindow(xml);
    w->plotter->setUnsavedChanges(true);
    delete xml;
  }
  else
  {
    String err=T(">>> Error ");
    if (!xml)
      err << doc.getLastParseError() << T("\n");
    else
    {
      err << T("invalid xml plot data\n");
      delete xml;
    }
    Console::getInstance()->printError(err);
  }
}

void PlotWindow::browseForFileToOpen(int type)
{
  if (type==CommandIDs::PlotterOpenMidiFile)
    {
      FileChooser ch (T("Plot Midi File"),
		      File::getCurrentWorkingDirectory(),
		      T("*.mid"));
      if (ch.browseForFileToOpen())
	openMidiFile(ch.getResult());
    }
  else if (type==CommandIDs::PlotterOpen)
    {
      FileChooser ch (T("Open Plot"), 
		      File::getCurrentWorkingDirectory(),
		      T("*.xml"));
      if (ch.browseForFileToOpen())
	openXmlFile(ch.getResult());
    }
}

void PlotWindow::openXmlFile(File file)
{
  XmlDocument doc (file);
  XmlElement* xml = doc.getDocumentElement();
  if (xml && xml->getChildByName(T("fields")) &&
      xml->getChildByName(T("layers")))
  {
    PlotWindow* w=new PlotWindow(xml);
    w->setPlotFile(file);
    delete xml;
  }
  else
  {
    String err=T(">>> Error: ");
    if (!xml)
      err << doc.getLastParseError() << T("\n");
    else
    {
      err << file.getFullPathName() 
          << T(" is not a valid plot (xml) file.\n");
      delete xml;
    }
    Console::getInstance()->printError(err);
  }
}

void PlotWindow::openMidiFile(File file)
{
  String title=file.getFileNameWithoutExtension();
  FileInputStream* input=file.createInputStream();
  MidiFile midifile;
  if (midifile.readFrom(*input))
  {
    PlotWindow* w=new PlotWindow(title, midifile);
  }
  else
  {
    String err=T(">>> Error: ");
    err << file.getFullPathName() 
        << T(" is not a valid midi file.");
    Console::getInstance()->printError(err);
  }
}

bool PlotWindow::save(bool saveas)
{
  File f=getPlotFile();
  if (saveas || (f==File::nonexistent))
    {
      String t=((saveas) ? T("Save Plot As") : T("Save Plot"));
      if (f==File::nonexistent)
	f=File::getCurrentWorkingDirectory().getChildFile(getName() + T(".xml"));
      FileChooser ch (t, f, "*.xml");
      if (ch.browseForFileToSave(true))
	// std::cout << ch.getResult().getFullPathName().getUTF8() << "\n";
	setPlotFile(ch.getResult());
      else
	return false;
    }
  String text=toXmlString();
  if (!getPlotFile().replaceWithText(text))
    {
      text=T(">> Error: file ")+getPlotFile().getFullPathName() + T(" not writable.\n");
      Console::getInstance()->printError(text);
      return false;
    }
  plotter->setUnsavedChanges(false);
  return true;
}

void PlotWindow::closeButtonPressed () //{this->~PlotWindow();}
{
  int x=2;
  if (hasUnsavedChanges())
  {
    x=Alerts::showYesNoCancelBox(AlertWindow::QuestionIcon,
                                 T("Close"),
                                 T("Save changes before closing?"),
                                 T("Save"),
                                 T("Don't Save"),
                                 T("Cancel")
                                 );
  }
  if (x==0)
    return;
  if (x==2 || save())
    delete this;
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

const StringArray PlotWindow::getMenuBarNames ()
{
  const tchar* const menuNames[] =
    {T("Plot"), T("Edit"), T("View"), T("Audio"), T("Window"), T("Help"), 0};
  return StringArray((const tchar**) menuNames);
}

const PopupMenu PlotWindow::getMenuForIndex(int idx, const String &name)
{
  PopupMenu menu;
  PopupMenu sub1, sub2, sub3;
  int val;
  int arity=plotter->numFields();
  
  return menu;
}

void PlotWindow::menuItemSelected (int id, int idx)
{
  CommandID cmd = CommandIDs::getCommand(id);
  int data = CommandIDs::getCommandData(id);  
  int type = CommandIDs::getCommandType(id);  
  
  
}

void PlotWindow::PlotWindowListener::handleMessage(const Message &m)
{

  switch (m.intParameter1)
    {
    case CommandIDs::PlotterAddXmlPoints:
      if (m.pointerParameter!=NULL)
	{
	  char* str=(char*)m.pointerParameter;
	  String txt (str);//String((char*)m.pointerParameter)
	  XmlDocument doc (txt);
	  XmlElement* xml=doc.getDocumentElement();
	  std::cout << "Got a PlotterAddXmlPoints message,"
		    << " str=" << str << "\n";
	  if (xml)
	    std::cout << "XML=" << xml->createDocument(String::empty, true, false, T("UTF-8")).toUTF8() << "\n";
	  if (xml && xml->hasTagName(T("points")))
	    {
	      window->plotter->getFocusLayer()->addXmlPoints(xml);
	      window->plotter->repaint();
	      delete xml;
	    }
	  else
	    {
	      String err=T(">>> Error ");
	      if (!xml)
		err << doc.getLastParseError() << T("\n");
	      else
		{
		  err << T("invalid xml plot data\n");
		  delete xml;
		}
	      Console::getInstance()->printError(err);
	    }
	  delete str;
	}
      break;
    default:
      break;
    } 
}

/*=======================================================================*
                              FileIO and Exporting
 *=======================================================================*/

String PlotWindow::toXmlString()
{
  String text=String::empty;
  text << T("<plot title=") << getName().quoted() << T(">\n") ;
  // output axis definitions
  text << T("  <fields>\n");
  for (int i=0; i<plotter->numFields(); i++)
  {
    Axis* a=plotter->getFieldAxis(i);
    text << T("    ")
         << T("<field")
         << T(" name=") << plotter->getFieldName(i).quoted()
         << T(" axis=") ;
    if (plotter->isSharedField(i))
      text << plotter->getSharedFieldName(i).quoted();
    else
      text << a->toString().quoted();
    text << T("/>\n");
  }
  text << T("  </fields>\n");
  text << T("  <layers>\n");
  for (int i=0; i<plotter->numLayers(); i++)
    text << T("    ")
	 << plotter->getLayer(i)->toString(TextIDs::Xml, 2, false, 0xFF);
  text << T("\n");
  text << T("  </layers>\n");
  text<<T("</plot>\n");
  return text;
}



/*=======================================================================*

                             Plotting Dialogs
X Axis | Y axis | Audio | Export | Layer1 | Layer2 | Layer...

 *=======================================================================*/


static bool isNumberText(String num)
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



void PlotWindow::openExportDialog ()
{
}

void PlotWindow::openLayerDialog ()
{
}

/*=======================================================================*
                              Axis Dialog
 *=======================================================================*/

void PlotWindow::openAxisDialog (int orient)
{
}

/*=======================================================================*
                              Sonify Plot Dialog
 *=======================================================================*/

void PlotWindow::openPlayPlotDialog ()
{

}

/*=======================================================================*
                              Edit Point Dialog
 *=======================================================================*/

class EditPointsDialog : public Component, 
			public LabelListener
{
private:
  Plotter* plotter;
  OwnedArray<Label> labels;
  OwnedArray<Label> editors;
  enum{labelwidth=80, editorwidth=120, lineheight=24, margin=8};
  int getFieldIndex(String name)
  {
    for (int i=0; i<editors.size(); i++)
      if (editors[i]->getName()==name) return i;
    return -1;
  }
public:
  EditPointsDialog (Plotter* plotr);
  ~EditPointsDialog()
  {
    editors.clear();
    labels.clear();
  }
  void resized();
  void labelTextChanged(Label *label);
};

EditPointsDialog::EditPointsDialog(Plotter* plotr)
{
  plotter=plotr;
  int numfields=plotter->numFields();
  Layer::NPoint* p=(plotter->numSelected()==1)
    ? plotter->getSelected(0) : NULL ;
  for (int i=0; i<numfields; i++)
    {
      labels.add(new Label(String::empty, plotter->getFieldName(i)));
      editors.add(new Label( plotter->getFieldName(i), 
			    ((p) ? String(p->getVal(i)) : String::empty)));
      labels[i]->setFont(Font(15.0000f, Font::plain));
      editors[i]->setFont(Font(15.0000f, Font::plain));
      editors[i]->setEditable(true, false, true);
      editors[i]->setColour(Label::outlineColourId, Colours::black);
      editors[i]->addListener(this);
      addAndMakeVisible(labels[i]);
      addAndMakeVisible(editors[i]);
    }	 
  int w=margin+labelwidth+margin+editorwidth+margin;
  int h=(numfields*lineheight)+((numfields+1)*margin);
  setVisible(true);
  setSize(w, h);
}

void EditPointsDialog::resized()
{
  int x1=margin, x2=margin+labelwidth+margin;
  int y=margin;
  for(int i=0; i<labels.size(); i++)
  {
    labels[i]->setBounds(x1, y, labelwidth, lineheight);
    editors[i]->setBounds(x2, y, editorwidth, lineheight);
    y += lineheight + margin;
  }
}

void EditPointsDialog::labelTextChanged (Label *label)
{
  int index=getFieldIndex(label->getName());
  //std::cout << "text changed for " << label->getName().toUTF8()
  //	    << " field=" << index << "\n";
  if (index<0) return;
  String text=label->getText().trim();
  if ((index>=0) && text.isNotEmpty() &&
      text.containsOnly(T("0123456789.-"))) 
  {
    double value=text.getDoubleValue();
    // FIXME: undo/redo
    for (int i=0;i<plotter->numSelected(); i++)
      plotter->getSelected(i)->setVal(index,value);
    if (plotter->getFocusLayer()->isVisibleField(index))
      plotter->redrawPlotView();
  }
}

void PlotWindow::openEditPointsDialog ()
{
  DialogWindow::showModalDialog(T("Edit Points"), 
				new EditPointsDialog(plotter),
				this,
				Colour(0xffe5e5e5),
				false);
}


/*=======================================================================*
                              Rescale Points Dialog
 *=======================================================================*/

class RescalePointsDialog : public Component,
                           public ButtonListener,
			   public TextEditorListener
{
public:
  Plotter* plotter;
  int command;
  GroupComponent* axisgroup;
  ToggleButton* xbutton;
  ToggleButton* ybutton;
  Label* label1;
  TextEditor* editor1;
  Label* label2;
  TextEditor* editor2;
  static bool __yactive;
  bool isVertical(){return __yactive;}
  bool isHorizontal(){return !isVertical();}

  RescalePointsDialog (Plotter* pltr, int cmd);
  ~RescalePointsDialog();
  void resized();
  void buttonClicked (Button* buttonThatWasClicked);
  void textEditorReturnKeyPressed(TextEditor& editor);
  void textEditorTextChanged(TextEditor& editor) {}
  void textEditorEscapeKeyPressed(TextEditor& editor) {}
  void textEditorFocusLost(TextEditor& editor) {}
};

bool RescalePointsDialog::__yactive=true;

RescalePointsDialog::RescalePointsDialog (Plotter* pltr, int cmd)
  : plotter (0),
    command (0),
    axisgroup (0),
    xbutton (0),
    ybutton (0),
    label1 (0),
    editor1 (0),
    label2 (0),
    editor2 (0)
{
  plotter=pltr;
  command=cmd;
  addAndMakeVisible(axisgroup=new GroupComponent(String::empty,T("Axis")));
  
  addAndMakeVisible (xbutton = new ToggleButton (String::empty));
  xbutton->setButtonText (T("Horizontal"));
  xbutton->setRadioGroupId (1);
  xbutton->addListener (this);

  addAndMakeVisible (ybutton = new ToggleButton (String::empty));
  ybutton->setButtonText (T("Vertical"));
  ybutton->setRadioGroupId (1);
  ybutton->addListener (this);

  if (command==CommandIDs::PlotterShiftPoints)
    label1=new Label(String::empty, T("Amount to shift:"));
  else
    label1=new Label(String::empty, T("New minimum:"));
  addAndMakeVisible(label1);
  label1->setFont(Font (15.0000f, Font::plain));
  label1->setJustificationType(Justification::centredLeft);
  label1->setEditable(false, false, false);
  label1->setColour(TextEditor::textColourId, Colours::black);
  label1->setColour(TextEditor::backgroundColourId, Colour(0x0));
  
  addAndMakeVisible (editor1 = new TextEditor (String::empty));
  editor1->setMultiLine (false);
  editor1->setReturnKeyStartsNewLine (false);
  editor1->setReadOnly (false);
  editor1->setScrollbarsShown (true);
  editor1->setCaretVisible (true);
  editor1->setPopupMenuEnabled (true);
  editor1->setText(String::empty);
  editor1->addListener(this);

  if (command==CommandIDs::PlotterRescalePoints)
    {
      addAndMakeVisible(label2=new Label(String::empty,
					 T("New maximum:")));
      label2->setFont(Font(15.0000f, Font::plain));
      label2->setJustificationType(Justification::centredLeft);
      label2->setEditable(false, false, false);
      label2->setColour(TextEditor::textColourId, Colours::black);
      label2->setColour(TextEditor::backgroundColourId, Colour (0x0));
      
      addAndMakeVisible(editor2=new TextEditor(String::empty));
      editor2->setMultiLine(false);
      editor2->setReturnKeyStartsNewLine(false);
      editor2->setReadOnly(false);
      editor2->setScrollbarsShown(true);
      editor2->setCaretVisible(true);
      editor2->setPopupMenuEnabled(true);
      editor2->setText(String::empty);
      editor2->addListener(this);
    }
  if (isVertical())
    ybutton->setToggleState(true, true);
  else
    xbutton->setToggleState(true, true);
  if (command==CommandIDs::PlotterRescalePoints)
    setSize (272, 128);
  else
    setSize (272, 128-32);
}

RescalePointsDialog::~RescalePointsDialog()
{
  deleteAndZero (axisgroup);
  deleteAndZero (xbutton);
  deleteAndZero (ybutton);
  deleteAndZero (label1);
  deleteAndZero (editor1);
  deleteAndZero (label2);
  deleteAndZero (editor2);
}

void RescalePointsDialog::resized()
{
  axisgroup->setBounds (8, 8, 256, 48);
  xbutton->setBounds (24, 24, 96, 24);
  ybutton->setBounds (152, 24, 96, 24);
  label1->setBounds (16, 64, 112, 24);
  editor1->setBounds (136, 64, 120, 24);
  if (command==CommandIDs::PlotterRescalePoints)
    {
      label2->setBounds (16, 96, 112, 24);
      editor2->setBounds (136, 96, 120, 24);
    }
}

void RescalePointsDialog::buttonClicked (Button* button)
{
  Plotter::Orientation orient;
  if (button == xbutton)
    {
      __yactive=false;
      orient=Plotter::horizontal;
    }
  else if (button == ybutton)
    {
      __yactive=true;
      orient=Plotter::vertical;
    }
  if (command==CommandIDs::PlotterRescalePoints)
    {
      double low,high;
      plotter->getSelectionRange(orient,low,high);
      editor1->setText(String(low));
      editor2->setText(String(high));
    }
  else if (command==CommandIDs::PlotterShiftPoints)
    {
      editor1->setText(T("0.0"));
    }
}

void RescalePointsDialog::textEditorReturnKeyPressed (TextEditor& editor)
{
  String str=editor1->getText().trim();
  double num1, num2;
  if (!isNumberText(str))
    return;
  num1=str.getFloatValue();
  if (command==CommandIDs::PlotterShiftPoints)
    {
      if (isVertical())
	plotter->shiftSelection(Plotter::vertical, num1);
      else
	plotter->shiftSelection(Plotter::horizontal, num1);
    }
  else if (command==CommandIDs::PlotterRescalePoints)
    {
      str=editor2->getText().trim();
      if (!isNumberText(str))
	return;
      num2=str.getFloatValue();
      if (isVertical())
	plotter->rescaleSelection(Plotter::vertical, num1, num2);
      else
	plotter->rescaleSelection(Plotter::horizontal, num1, num2);
    }   
}

void PlotWindow::openRescalePointsDialog (int cmd)
{
  String title=String::empty;
  if (cmd==CommandIDs::PlotterRescalePoints)
    title=T("Rescale Points");
  else if (cmd==CommandIDs::PlotterShiftPoints)
    title=T("Shift Points");
  RescalePointsDialog* dialog=new RescalePointsDialog(plotter, cmd);
  DialogWindow::showModalDialog(title, dialog, this,
				Colour(0xffe5e5e5), false);
  delete dialog;
}

