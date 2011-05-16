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
#include "Midi.h"
#include "Scheme.h"
#include <limits>
#include "CmSupport.h"
#include "Alerts.h"
#include <iostream>

/*=======================================================================*
           PlotWindowComponent: window's content component that
           contains the plotter and the tabview
 *=======================================================================*/

class PlotWindowComponent : public Component
{
  PlotWindow* plotwin;
public:
  static const int plotviewwidth=500;
  static const int tabviewheight=150;
  PlotWindowComponent (PlotWindow* win) : plotwin (win) {}
  ~PlotWindowComponent () {deleteAllChildren();}
  void resized ()
  {
    int w=getWidth();
    int h=getHeight();
    std::cout << "PlotWindowComponent: w=" << w << ", h=" << h << "\n";
    plotwin->plotter->setBounds(0,0,w,h-tabviewheight);
    plotwin->tabview->setBounds(0,h-tabviewheight,w,tabviewheight);
  }
};

/*=======================================================================*
                   PlotWindow: top level window for plotting
 *=======================================================================*/

PointClipboard pointClipboard;

PlotWindow::PlotWindow(XmlElement* plot)
  : DocumentWindow (String::empty, Colours::white, 
		    DocumentWindow::allButtons, true)
{
  listener.window=this;
  String title=(plot==NULL) ? T("Untitled Plot") :
    plot->getStringAttribute(T("title"), T("Untitled Plot"));
  setName(title);
  plotter = new Plotter(plot) ;
  tabview = new TabbedComponent(TabbedButtonBar::TabsAtTop);
  init();
}

PlotWindow::PlotWindow(String title, MidiFile& midifile)
  : DocumentWindow (title, Colours::white, 
		    DocumentWindow::allButtons, true)
{
  listener.window=this;
  setName(title);
  plotter=new Plotter(midifile);
  tabview = new TabbedComponent(TabbedButtonBar::TabsAtTop);
  init();
}

PlotWindow::~PlotWindow ()
{
  delete menubar;
  setMenuBar(0);
}

void PlotWindow::init()
{
  menubar = new MenuBarComponent(this);
  setMenuBar(this);
  setUsingNativeTitleBar(true);    
  plotter->setSize(PlotWindowComponent::plotviewwidth,PlotWindowComponent::plotviewwidth); // extra 24 in veritical because of menu
  tabview->addTab(T("Plot"), Colour(0xffe5e5e5), new PlotWindowTab(plotter, this), true);
  tabview->addTab(T("Audio"), Colour(0xffe5e5e5), NULL, false);
  tabview->addTab(T("Export"), Colour(0xffe5e5e5), NULL, false);
  tabview->addTab(T("X Axis"), Colour(0xffe5e5e5), new PlotterAxisTab(plotter, Plotter::horizontal), true);
  tabview->addTab(T("Y Axis"), Colour(0xffe5e5e5), new PlotterAxisTab(plotter, Plotter::vertical), true);

  for (int i=0; i<plotter->numLayers(); i++)
  {
    Layer* layer=plotter->getLayer(i);
    tabview->addTab(layer->getLayerName(), Colour(0xffe5e5e5), new LayerTab(plotter,layer), true);
  }

  PlotWindowComponent* content=new PlotWindowComponent(this);
  setContentComponent(content, true, true);
  content->addChildComponent(plotter);
  content->addChildComponent(tabview);
  plotter->setVisible(true);
  tabview->setVisible(true);
  content->setVisible(true);
  centreWithSize (PlotWindowComponent::plotviewwidth, PlotWindowComponent::plotviewwidth + PlotWindowComponent::tabviewheight + 24);
  setResizable(true, true); 
  setVisible(true);
  WindowTypes::setWindowType(this, WindowTypes::PlotWindow);
  plotter->insurePointsVisible();
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
  return (PlotWindow*)NULL;
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
  
  if (name==T("Plot"))
    {
      // File Menu
      menu.addItem(CommandIDs::PlotterNew, T("New Plot"));
      menu.addItem(CommandIDs::PlotterOpen, T("Open..."));
      menu.addItem(CommandIDs::PlotterOpenMidiFile,T("Plot Midi File..."));
      menu.addSeparator(); 
      menu.addItem(CommandIDs::PlotterLayerAdd, T("New Layer"));
      for (int i=0; i<plotter->numLayers(); i++)
	{
	  Layer* layer=plotter->getLayer(i);
	  sub1.addColouredItem(CommandIDs::PlotterLayerSelect +
			      layer->getLayerID(),
			      layer->getLayerName(),
			      layer->getLayerColor(),
			      true,
			      plotter->isFocusLayer(layer));
	}
      sub1.addSeparator(); 
      sub1.addItem(CommandIDs::PlotterLayerDelete, T("Delete"),
		   (plotter->numLayers() > 1));
      menu.addSubMenu(T("Layers"), sub1);
      menu.addSeparator();
      menu.addItem(CommandIDs::PlotterClose, T("Close"));
      menu.addItem(CommandIDs::PlotterSave, T("Save"));
      menu.addItem(CommandIDs::PlotterSaveAs, T("Save As..."),
		   (getPlotFile()!=File::nonexistent));
      menu.addSeparator();
      menu.addItem(CommandIDs::PlotterRename, T("Rename..."));
      menu.addItem(CommandIDs::PlotterExport, T("Export..."));
    }
  else if (name==T("Edit"))
    {
      int sel=plotter->numSelected();
      // Edit Menu
      menu.addItem(CommandIDs::EditorUndo, T("Undo"),
		   plotter->actions.canUndo());
      menu.addItem(CommandIDs::EditorUndo, T("Redo"),
		   plotter->actions.canRedo());
      menu.addSeparator();
      menu.addItem(CommandIDs::EditorCut, T("Cut"), (sel>0));
      menu.addItem(CommandIDs::EditorCopy, T("Copy"), (sel>0));
      menu.addItem(CommandIDs::EditorPaste, T("Paste"),
		   !pointClipboard.isEmpty());
      menu.addSeparator();
      menu.addItem(CommandIDs::EditorSelectAll, T("Select All"));
      menu.addItem(CommandIDs::EditorUnselectAll, T("Clear Selection"),
		   (sel>0));
      menu.addSeparator(); 
      menu.addItem(CommandIDs::PlotterEditPoints, T("Edit Points"),
		   (sel>0));
      menu.addItem(CommandIDs::PlotterShiftPoints, T("Shift Points"),
		   (sel>0));
      menu.addItem(CommandIDs::PlotterRescalePoints, T("Rescale Points"),
		   (sel>1));
    }
  else if (name==T("View"))
  {
    Layer* layer=plotter->getFocusLayer();
    val=layer->getLayerStyle();
    // add these with focus colored items to make it clear that the
    // styling change only affects the focus plot
    sub1.addItem(CommandIDs::PlotterStyle + Layer::line, 
                 T("Line"), true, (val==Layer::line));
    sub1.addItem(CommandIDs::PlotterStyle + Layer::point,
                 T("Point"), true, (val==Layer::point));
    sub1.addItem(CommandIDs::PlotterStyle + Layer::lineandpoint,
                 T("Envelope"), true, (val==Layer::lineandpoint));
    sub1.addItem(CommandIDs::PlotterStyle + Layer::hbox, 
                 T("Horizontal Box"),
                 (arity > 2), (val==Layer::hbox));
    sub1.addItem(CommandIDs::PlotterStyle + Layer::vbox,
                 T("Vertical Box"),
                 (arity > 2), (val==Layer::vbox));
    sub1.addItem(CommandIDs::PlotterStyle + Layer::impulse, 
                 T("Impulse"), true, (val==Layer::impulse));
    sub1.addItem(CommandIDs::PlotterStyle + Layer::histogram, 
                 T("Histogram"), true, (val==Layer::histogram));
    sub1.addItem(CommandIDs::PlotterStyle + Layer::vbar, 
                 T("Vertical Bar"), false, (val==Layer::vbar));
    menu.addSubMenu(T("Point Style"), sub1, true);
    menu.addSeparator();
    val=plotter->getBackViewStyle();
    sub2.addItem(CommandIDs::PlotterBgStyle + Plotter::bgGrid,
                 T("Grid"), true, (val==Plotter::bgGrid));
    sub2.addItem(CommandIDs::PlotterBgStyle + Plotter::bgTiled,
                 T("Tiled"), true, (val==Plotter::bgTiled));
    sub2.addItem(CommandIDs::PlotterBgStyle + Plotter::bgSolid,
                 T("Solid"), true, (val==Plotter::bgSolid));
    sub2.addSeparator();
    sub2.addItem(CommandIDs::PlotterBgColor, T("Colors..."), false);
    sub2.addSeparator();
    sub2.addItem(CommandIDs::PlotterBgPlotting,
                 T("Show All Layers"), 
                 true, 
                 plotter->isBackViewPlotting() );
    menu.addSubMenu(T("Background"), sub2, true);
    menu.addSeparator();
    menu.addItem(CommandIDs::PlotterZoomInX, T("Zoom In X"));
    menu.addItem(CommandIDs::PlotterZoomOutX, T("Zoom Out X"));
    menu.addItem(CommandIDs::PlotterZoomInY, T("Zoom In Y"));
    menu.addItem(CommandIDs::PlotterZoomOutY, T("Zoom Out Y"));
    menu.addSeparator();
    menu.addItem(CommandIDs::PlotterZoomToFit, T("Fit in Window"), true, true);
    menu.addItem(CommandIDs::PlotterZoomReset, T("Reset Zoom"));
  }
  else if (name==T("Audio"))
    menu=CommandMenus::getAudioMenu(false);
  else if (name==T("Window"))
    menu=CommandMenus::getWindowMenu();
  else if (name==T("Help")) 
    menu=CommandMenus::getHelpMenu(WindowTypes::PlotWindow, 0);
  return menu;
}

void PlotWindow::menuItemSelected (int id, int idx)
{
  CommandID cmd = CommandIDs::getCommand(id);
  int data = CommandIDs::getCommandData(id);  
  int type = CommandIDs::getCommandType(id);  
  
  switch (cmd)
  {
  case CommandIDs::PlotterNew :
    new PlotWindow((XmlElement*)NULL);
    break;
  case CommandIDs::PlotterOpen :
  case CommandIDs::PlotterOpenMidiFile :
    browseForFileToOpen(cmd);
    break;
  case CommandIDs::PlotterSave :
    save();
    break;
  case CommandIDs::PlotterSaveAs :
    save(true);
    break;
  case CommandIDs::PlotterRename :
    {
      AlertWindow w (T("Rename Plot"), String::empty, 
                     AlertWindow::NoIcon);
      w.addTextEditor(T("rename"), getName(), String::empty);
      w.addButton(T("Cancel"), 0, KeyPress(KeyPress::escapeKey, 0, 0));
      w.addButton(T("Rename"), 1, KeyPress(KeyPress::returnKey, 0, 0));
      if (w.runModalLoop() != 0) // picked 'ok'
        setName(w.getTextEditorContents(T("rename")));
    }
    break;
  case CommandIDs::PlotterExport :
    openExportDialog();
    break;
  case CommandIDs::PlotterClose :
    closeButtonPressed();
    break;
  case CommandIDs::EditorUndo :
    plotter->actions.undo();
    break;
  case CommandIDs::EditorRedo :
    plotter->actions.redo();
    break;
  case CommandIDs::EditorCut :
    plotter->deleteSelection(true);
    break;
  case CommandIDs::EditorSelectAll :
    plotter->selectAll();
    break;
  case CommandIDs::EditorUnselectAll :
    plotter->deselectAll();
    break;
  case CommandIDs::PlotterEditPoints :
    openEditPointsDialog();
    break;
  case CommandIDs::PlotterShiftPoints :
    openRescalePointsDialog(cmd);
    break;
  case CommandIDs::PlotterRescalePoints :
    openRescalePointsDialog(cmd);
    break;    
  case CommandIDs::PlotterLayerAdd :
    plotter->newLayer(NULL);
    plotter->redrawBackView();
    plotter->redrawHorizontalAxisView();
    plotter->redrawVerticalAxisView();
    break;
  case CommandIDs::PlotterLayerDelete :
    plotter->actions.perform
      (new DeleteLayerAction(plotter,
                             plotter->getFocusLayer()),
       T("Delete Layer"));
    break;
  case CommandIDs::PlotterLayerSelect :
    plotter->setFocusLayer(plotter->findLayer(data));
    plotter->redrawBackView();
    plotter->redrawPlotView();
    plotter->redrawHorizontalAxisView();
    plotter->redrawVerticalAxisView();
    break;
  case CommandIDs::PlotterStyle :
    plotter->getFocusLayer()->setLayerStyle(data);
    plotter->redrawPlotView();
    break;
  case CommandIDs::PlotterVertical :
    plotter->setFocusVerticalField(data);
    break;
  case CommandIDs::PlotterBgStyle :
    plotter->setBackViewStyle( (Plotter::BGStyle)data);
    plotter->redrawBackView();
    break;
  case CommandIDs::PlotterBgColor :
    break;
  case CommandIDs::PlotterBgPlotting :
    plotter->setBackViewPlotting( ! plotter->isBackViewPlotting()); 
    plotter->redrawBackView();
    break;

  case CommandIDs::PlotterZoomInX:
  case CommandIDs::PlotterZoomOutX:
  case CommandIDs::PlotterZoomInY:
  case CommandIDs::PlotterZoomOutY:
    break;

  case CommandIDs::PlotterZoomReset:
    break;

  case CommandIDs::PlotterZoomToFit:
    break;

  default :
    break;
  }
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

String Layer::toString(int exportid, int decimals,
		       bool asrecords, int parammask) 
{
  String text=String::empty;
  String lpar=String::empty;
  String rpar=String::empty;
  String done=String::empty;
  String spce=T(" ");
  if (exportid==TextIDs::Lisp)
    {
      text=T("(");
      if (asrecords)
	{
	  lpar=T("(");
	  rpar=T(")");
	}
      done=T(")");
    }
  else if (exportid==TextIDs::Sal2)
    {
      text=T("{");
      if (asrecords)
	{
	  lpar=T("{");
	  rpar=T("}");
	}
      done=T("}");
    }
  else if (exportid==TextIDs::Xml)
    {
      text << T("<points title=")
	   << getLayerName().quoted()
	   << T(" style=")
	   << toLayerTypeString(getLayerStyle()).quoted()
	   << T(" color=")
	   << getLayerColor().toString().quoted();
      // add non-default access
      if (getXField()!=0 || getYField()!=1 ||
	  (getLayerArity()>2 && getYField()!=2))
	text << T(" access=\"")
	     << getXField() << T(" ") << getYField()
	     << T(" ") << getZField() << T("\"");
      text << T(">");
      lpar=T("<point>");
      rpar=T("</point>");
      done=T("</points>\n");
      spce=String::empty;
    }
  LayerPoint* point;
  int length=numPoints();
  for (int i=0; i<length; i++)
    {
      point=getPoint(i);
      if (i>0 && spce!=String::empty) text << spce;
      text << lpar
	   << exportPoint(point, parammask, decimals)
	   << rpar;
    }
  // add appropriate close parens...
  text << done ;
  //std::cout << text.toUTF8() << "\n";
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

class ExportPointsDialog : 
  public Component, public ButtonListener, public ComboBoxListener
{
 public:
  Plotter* plotter;
  int numfields;
  bool* include;
  Label* exportlabel;
  ComboBox* exportmenu;
  Label* tolabel;
  ComboBox* tomenu;
  TextButton* fieldsbutton;
  Label* formatlabel;
  Label* valuelabel;
  Label* destlabel;
  ComboBox* valuemenu;
  ComboBox* formatmenu;
  ComboBox* destmenu;
  TextButton* exportbutton;
  ExportPointsDialog(Plotter* plotter);
  ~ExportPointsDialog();
  void resized();
  void buttonClicked (Button* button);
  void comboBoxChanged (ComboBox* combobox);
  void exportPoints();
  void exportPlot();
};

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
      destlabel (0),
      destmenu (0),
      exportbutton (0),
      plotter(0),
      include(0)
{
  plotter=p;
  numfields=plotter->numFields();
  include=new bool[numfields];

  for (int i=0;i<numfields; i++) include[i]=true;

  Font font=Font (15.0000f, Font::plain);
  addAndMakeVisible(exportlabel = new Label(String::empty, T("Export:")));
  exportlabel->setFont(font);

  addAndMakeVisible (exportmenu = new ComboBox (String::empty));
  exportmenu->setEditableText (false);
  exportmenu->addItem (T("Points"), 1);
  exportmenu->addItem (T("Plot"), 2);
  exportmenu->setSelectedId(1);
  exportmenu->addListener(this);

  addAndMakeVisible(tolabel=new Label(String::empty, T("Syntax:")));
  tolabel->setFont (font);

  addAndMakeVisible(tomenu = new ComboBox (String::empty));
  tomenu->setEditableText(false);
  tomenu->addItem(T("Lisp"), TextIDs::Lisp);
  tomenu->addItem(T("SAL"), TextIDs::Sal2);
  tomenu->addItem(T("XML"), TextIDs::Xml);
  tomenu->setSelectedId(TextIDs::Lisp);

  addAndMakeVisible(fieldsbutton = new TextButton (String::empty));
  fieldsbutton->setButtonText(T("Fields..."));
  fieldsbutton->addListener(this);

  addAndMakeVisible(formatlabel = new Label(String::empty, T("Format:")));
  formatlabel->setFont(font);

  addAndMakeVisible(formatmenu = new ComboBox(String::empty));
  formatmenu->setEditableText (false);
  formatmenu->addItem(T("Envelope List"), 1);
  formatmenu->addItem(T("Point Records"), 2);
  formatmenu->setSelectedId(1);

  addAndMakeVisible(valuelabel=new Label(String::empty, 
					 T("Precision:")));
  addAndMakeVisible(valuemenu = new ComboBox(String::empty));
  valuemenu->addItem(T("Integer"), 1);
  valuemenu->addItem(T("0.0"), 2);
  valuemenu->addItem(T("0.00"), 3);
  valuemenu->addItem(T("0.000"), 4);
  valuemenu->setSelectedId(3);

  addAndMakeVisible(destlabel=new Label(String::empty, 
					 T("Destination:")));
  addAndMakeVisible(destmenu = new ComboBox(String::empty));
  destmenu->addItem(T("New Edit Window"), 1);
  destmenu->addItem(T("Current Edit Window"), 2);
  destmenu->addItem(T("Clipboard"), 3);
  destmenu->setSelectedId(1);

  addAndMakeVisible(exportbutton = new TextButton(String::empty));
  exportbutton->setButtonText(T("Export"));
  exportbutton->addListener(this);
  setSize(440, 140);
}

ExportPointsDialog::~ExportPointsDialog()
{
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
  deleteAndZero (destlabel);
  deleteAndZero (destmenu);
}

void ExportPointsDialog::resized()
{
  exportlabel->setBounds (16, 16, 56, 24);
  exportmenu->setBounds (76, 16, 88, 24);
  tolabel->setBounds (176, 16, 34+16, 24);
  tomenu->setBounds (210+16, 16, 80, 24);
  fieldsbutton->setBounds (304+16, 16, 120-16, 26);
  formatlabel->setBounds (16, 56, 56, 24);
  formatmenu->setBounds (77, 56, 150, 24);
  valuelabel->setBounds (246+24, 56, 92, 24);
  valuemenu->setBounds (342, 56, 80, 24);
  exportbutton->setBounds (274, 96, 150, 24);
  destlabel->setBounds (16, 96, 100, 24);
  destmenu->setBounds (77+24, 96, 150+8, 24);
}

void ExportPointsDialog::exportPlot() 
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

void ExportPointsDialog::exportPoints() 
{
  bool layerexport=true; //(exportmenu->getSelectedId()==1);
  int exportid=tomenu->getSelectedId();
  int decimals=valuemenu->getSelectedId()-1;
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

void ExportPointsDialog::buttonClicked (Button* button)
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

void ExportPointsDialog::comboBoxChanged(ComboBox* cbox)
{
  if (cbox==exportmenu)
    {
      int id=cbox->getSelectedId();
      if (id==1) // Layer
	{
	  tomenu->setEnabled(true);
	  fieldsbutton->setEnabled(true);
	  formatmenu->setEnabled(true);
	  valuemenu->setEnabled(true);
	}
      else // Plot
	{
	  tomenu->setEnabled(false);
	  fieldsbutton->setEnabled(false);
	  formatmenu->setEnabled(false);
	  valuemenu->setEnabled(false);
	}
    }
  else
    {
    }      
}

void PlotWindow::openExportDialog ()
{
  DialogWindow::showModalDialog(T("Export Plot"),
				new ExportPointsDialog(plotter),
				this,
				Colour(0xffe5e5e5),
				true);
}

/*=======================================================================*
                              Layer Dialog
 *=======================================================================*/

class LayerDialog  : public Component,
                     public ComboBoxListener,
                     public ButtonListener,
                     public ChangeListener
{
private:
  Plotter* plotter;
public:
  LayerDialog (Plotter* pl);
  ~LayerDialog();
  void resized();
  void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
  void buttonClicked (Button* buttonThatWasClicked);
  void changeListenerCallback(ChangeBroadcaster* source);
private:
  Label* namelabel;
  TextEditor* namebuffer;
  Label* stylelabel;
  ComboBox* stylemenu;
  TextButton* colorbutton;
  // (prevent copy constructor and operator= being generated..)
  LayerDialog (const LayerDialog&);
  const LayerDialog& operator= (const LayerDialog&);
};

LayerDialog::LayerDialog (Plotter* pl)
  : namelabel (0),
    namebuffer (0),
    stylelabel (0),
    stylemenu (0),
    colorbutton (0),
    plotter (0)
{
  plotter=pl;
  Layer* layer=plotter->getFocusLayer();
  addAndMakeVisible (namelabel = new Label (String::empty,
					    T("Name:")));
  namelabel->setFont (Font (15.0000f, Font::plain));
  namelabel->setJustificationType (Justification::centredLeft);
  namelabel->setEditable (false, false, false);
  namelabel->setColour (TextEditor::textColourId, Colours::black);
  namelabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

  addAndMakeVisible (namebuffer = new TextEditor (String::empty));
  namebuffer->setMultiLine (false);
  namebuffer->setReturnKeyStartsNewLine (false);
  namebuffer->setReadOnly (false);
  namebuffer->setScrollbarsShown (true);
  namebuffer->setCaretVisible (true);
  namebuffer->setPopupMenuEnabled (true);
  namebuffer->setText (layer->getLayerName());
  
  addAndMakeVisible (stylelabel = new Label (String::empty,
                                               T("Style:")));
  stylelabel->setFont (Font (15.0000f, Font::plain));
  stylelabel->setJustificationType (Justification::centredLeft);
  stylelabel->setEditable (false, false, false);
  stylelabel->setColour (TextEditor::textColourId, Colours::black);
  stylelabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
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

  addAndMakeVisible(colorbutton = new TextButton(String::empty));
  colorbutton->setButtonText(T("Color..."));
  colorbutton->addListener(this);
  setSize(476, 76);
}

LayerDialog::~LayerDialog()
{
  deleteAndZero(namelabel);
  deleteAndZero(namebuffer);
  deleteAndZero(stylelabel);
  deleteAndZero(stylemenu);
  deleteAndZero(colorbutton);
}

void LayerDialog::resized()
{
  namelabel->setBounds(8, 24, 48, 24);
  namebuffer->setBounds(56, 24, 120, 24);
  stylelabel->setBounds(184, 24, 48, 24);
  stylemenu->setBounds(228, 24, 120, 24);
  colorbutton->setBounds(360, 24, 104, 24);
}

void LayerDialog::comboBoxChanged (ComboBox* cb)
{
  if (cb == stylemenu)
    {
      plotter->getFocusLayer()->setLayerStyle(cb->getSelectedId());
      plotter->redrawPlotView();
    }
}

void LayerDialog::buttonClicked (Button* buttonThatWasClicked)
{
  if (buttonThatWasClicked == colorbutton)
    {
      ColourSelector sel;
      sel.setCurrentColour(plotter->getFocusLayer()->getLayerColor());
      sel.setSize(200, 300);
      sel.addChangeListener(this);
      DialogWindow::showModalDialog(T("Layer Color"),
				    &sel, 
				    this,
				    Colour(0xffe5e5e5),
				    false);
    }
}

void LayerDialog::changeListenerCallback (juce::ChangeBroadcaster* source)
{
  ColourSelector* cs = (ColourSelector*)source;
  plotter->getFocusLayer()->setLayerColor(cs->getCurrentColour());
  plotter->redrawPlotView();
}

void PlotWindow::openLayerDialog ()
{
  DialogWindow::showModalDialog(T("Edit Layer"),
				new LayerDialog(plotter),
				this,
				Colour(0xffe5e5e5),
				false);
}

/*=======================================================================*
                              Axis Dialog
 *=======================================================================*/

class AxisDialog  : public Component,
                    public ComboBoxListener,
                    public TextEditorListener
{
private:
  Plotter* plotter;
  bool ishorizontal;
  AxisView* axisview;
  enum {setfrom=1,setto,setby,setticks,setdecimals};
  void setAxisValue(int field, double value, bool trig);
  void updateFields(Axis* ax);
  void updateAxis();
  // (prevent copy constructor and operator= being generated..)
  AxisDialog (const AxisDialog&);
  const AxisDialog& operator= (const AxisDialog&);
public:
  AxisDialog (Plotter* pl, int orient);
  ~AxisDialog();
  void resized();
  void comboBoxChanged(ComboBox* combo);
  void textEditorReturnKeyPressed(TextEditor& editor);
  void textEditorTextChanged(TextEditor& editor) {}
  void textEditorEscapeKeyPressed(TextEditor& editor) {}
  void textEditorFocusLost(TextEditor& editor) {}
private:
  Label* namelabel;
  Label* fromlabel;
  Label* tolabel;
  Label* bylabel;
  Label* typelabel;
  Label* decimalslabel;
  Label* tickslabel;
  ComboBox* typemenu;
  TextEditor* namebuffer;
  TextEditor* frombuffer;
  TextEditor* tobuffer;
  TextEditor* bybuffer;
  TextEditor* ticksbuffer;
  ComboBox* decimalsmenu;
  bool axistypechanged;
};

AxisDialog::AxisDialog (Plotter* pl, int orient)
    : namelabel (0),
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
      axistypechanged (false)
{
  plotter=pl;
  ishorizontal=(orient==Plotter::horizontal) ? true : false;
  axisview=(ishorizontal) ? plotter->getHorizontalAxisView()
    : plotter->getVerticalAxisView();
  addAndMakeVisible(namelabel = new Label(String::empty, T("Name:")));
  namelabel->setFont (Font (15.0000f, Font::plain));
  namelabel->setJustificationType (Justification::centredLeft);
  namelabel->setEditable (false, false, false);
  namelabel->setColour (TextEditor::textColourId, Colours::black);
  namelabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible(namebuffer = new TextEditor(T("namebuf")));
  namebuffer->setMultiLine (false);
  namebuffer->setReturnKeyStartsNewLine (false);
  namebuffer->setReadOnly (false);
  namebuffer->setScrollbarsShown (true);
  namebuffer->setCaretVisible (true);
  namebuffer->setPopupMenuEnabled (true);
  namebuffer->setText (String::empty);
  namebuffer->addListener(this);

  addAndMakeVisible(fromlabel = new Label(String::empty, T("From:")));
  fromlabel->setFont (Font (15.0000f, Font::plain));
  fromlabel->setJustificationType (Justification::centredLeft);
  fromlabel->setEditable (false, false, false);
  fromlabel->setColour (TextEditor::textColourId, Colours::black);
  fromlabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible(frombuffer = new TextEditor(T("frombuf")));
  frombuffer->setMultiLine (false);
  frombuffer->setReturnKeyStartsNewLine (false);
  frombuffer->setReadOnly (false);
  frombuffer->setScrollbarsShown (true);
  frombuffer->setCaretVisible (true);
  frombuffer->setPopupMenuEnabled (true);
  frombuffer->setText (String::empty);
  frombuffer->addListener(this);

  addAndMakeVisible(tolabel = new Label(String::empty, T("To:")));
  tolabel->setFont (Font (15.0000f, Font::plain));
  tolabel->setJustificationType (Justification::centredLeft);
  tolabel->setEditable (false, false, false);
  tolabel->setColour (TextEditor::textColourId, Colours::black);
  tolabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible(tobuffer = new TextEditor(T("tobuf")));
  tobuffer->setMultiLine (false);
  tobuffer->setReturnKeyStartsNewLine (false);
  tobuffer->setReadOnly (false);
  tobuffer->setScrollbarsShown (true);
  tobuffer->setCaretVisible (true);
  tobuffer->setPopupMenuEnabled (true);
  tobuffer->setText (String::empty);
  tobuffer->addListener(this);

  addAndMakeVisible (bylabel = new Label (String::empty, T("By:")));
  bylabel->setFont (Font (15.0000f, Font::plain));
  bylabel->setJustificationType (Justification::centredLeft);
  bylabel->setEditable (false, false, false);
  bylabel->setColour (TextEditor::textColourId, Colours::black);
  bylabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (bybuffer = new TextEditor(T("bybuf")));
  bybuffer->setMultiLine (false);
  bybuffer->setReturnKeyStartsNewLine (false);
  bybuffer->setReadOnly (false);
  bybuffer->setScrollbarsShown (true);
  bybuffer->setCaretVisible (true);
  bybuffer->setPopupMenuEnabled (true);
  bybuffer->setText (String::empty);
  bybuffer->addListener(this);

  addAndMakeVisible(typelabel = new Label(String::empty, T("Type:")));
  typelabel->setFont (Font (15.0000f, Font::plain));
  typelabel->setJustificationType (Justification::centredLeft);
  typelabel->setEditable (false, false, false);
  typelabel->setColour (TextEditor::textColourId, Colours::black);
  typelabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
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
  typemenu->addListener (this);

  addAndMakeVisible(tickslabel = new Label(String::empty, T("Ticks:")));
  tickslabel->setFont (Font (15.0000f, Font::plain));
  tickslabel->setJustificationType (Justification::centredLeft);
  tickslabel->setEditable (false, false, false);
  tickslabel->setColour (TextEditor::textColourId, Colours::black);
  tickslabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible(ticksbuffer = new TextEditor(T("ticksbuf")));
  ticksbuffer->setMultiLine (false);
  ticksbuffer->setReturnKeyStartsNewLine (false);
  ticksbuffer->setReadOnly (false);
  ticksbuffer->setScrollbarsShown (true);
  ticksbuffer->setCaretVisible (true);
  ticksbuffer->setPopupMenuEnabled (true);
  ticksbuffer->setText (String::empty);
  ticksbuffer->addListener(this);
  
  addAndMakeVisible(decimalslabel=new Label(String::empty, ("Decimals:")));
  decimalslabel->setFont (Font (15.0000f, Font::plain));
  decimalslabel->setJustificationType (Justification::centredLeft);
  decimalslabel->setEditable (false, false, false);
  decimalslabel->setColour (TextEditor::textColourId, Colours::black);
  decimalslabel->setColour(TextEditor::backgroundColourId, Colour(0x0));
  
  addAndMakeVisible (decimalsmenu = new ComboBox (String::empty));
  decimalsmenu->setEditableText (false);
  decimalsmenu->setJustificationType (Justification::centredLeft);
  decimalsmenu->setTextWhenNothingSelected (String::empty);
  decimalsmenu->setTextWhenNoChoicesAvailable (T("(no choices)"));
  decimalsmenu->addItem (T("0"), 1);
  decimalsmenu->addItem (T("1"), 2);
  decimalsmenu->addItem (T("2"), 3);
  decimalsmenu->addItem (T("3"), 4);
  decimalsmenu->addListener (this);
  updateFields(axisview->getAxis());
  setSize (476, 78);
}

AxisDialog::~AxisDialog()
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
}

void AxisDialog::resized()
{
  namelabel->setBounds (8, 8, 48, 24);
  fromlabel->setBounds (8, 40, 48, 24);
  tolabel->setBounds (136, 40, 32, 24);
  bylabel->setBounds (248, 40, 24, 24);
  typelabel->setBounds (184, 8, 48, 24);
  typemenu->setBounds (232, 8, 96, 24);
  namebuffer->setBounds (56, 8, 120, 24);
  tickslabel->setBounds (352, 40, 48, 24);
  frombuffer->setBounds (56, 40, 56, 24);
  tobuffer->setBounds (168, 40, 56, 24);
  bybuffer->setBounds (280, 40, 56, 24);
  ticksbuffer->setBounds (408, 40, 56, 24);
  decimalslabel->setBounds (336, 8, 72, 24);
  decimalsmenu->setBounds (408, 8, 55, 24);
}

void AxisDialog::updateFields(Axis* ax)
{
  namebuffer->setText(String(ax->getName()), false);
  frombuffer->setText(String(ax->getMinimum()), false);
  tobuffer->setText(String(ax->getMaximum()), false);
  bybuffer->setText(String(ax->getIncrement()), false);
  ticksbuffer->setText(String(ax->getTicks()), false);
  decimalsmenu->setSelectedId(ax->getDecimals()+1, true);
  typemenu->setSelectedId(ax->getType(), true);
}

void AxisDialog::comboBoxChanged (ComboBox* cbox)
{
  if (cbox == typemenu)
    {
      Axis a(0);
      a.init((Axis::AxisType)cbox->getSelectedId());
      updateFields(&a);
      axistypechanged=true;
    }
  else if (cbox == decimalsmenu)
    {
      axisview->getAxis()->setDecimals(cbox->getSelectedId()-1);
      axisview->repaint();
    } 
}

void AxisDialog::textEditorReturnKeyPressed (TextEditor& editor)
{
  double val;
  Axis* axis=axisview->getAxis();
  bool redraw=false;

  // pressing return in any box after the axis type has been reset by
  // the user sends all fields!
  if (axistypechanged)
    {
      String text=namebuffer->getText();
      axis->setName(text);
      if (isNumberText(text=frombuffer->getText()))
	axis->setMinimum(text.getDoubleValue());
      if (isNumberText(text=tobuffer->getText()))
	axis->setMaximum(text.getDoubleValue());
      if (isNumberText(text=bybuffer->getText()))
	axis->setIncrement(text.getDoubleValue());
      if (isNumberText(text=ticksbuffer->getText()))
	axis->setTicks(text.getIntValue());
      axis->setDecimals(decimalsmenu->getSelectedId()-1);
      redraw=true;
      axistypechanged=false;
    }
  else if (editor.getName()==T("namebuf"))
    {
      axis->setName(editor.getText());
    }
  else if (editor.getName()==T("frombuf"))
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
  else if (editor.getName()==T("tobuf"))
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
  else if (editor.getName()==T("bybuf"))
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
  else if (editor.getName()==T("ticksbuf"))
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

void PlotWindow::openAxisDialog (int orient)
{
  DialogWindow::showModalDialog(T("Edit Axis"),
				new AxisDialog(plotter, orient),
				this,
				Colour(0xffe5e5e5),
				false);
}

/*=======================================================================*
                              Sonify Plot Dialog
 *=======================================================================*/

class PlayPlotDialog : public Component,
			 public SliderListener,
			 public ButtonListener
{
public:
  PlayPlotDialog (Plotter* pl);
  ~PlayPlotDialog();
  void resized();
  void sliderValueChanged (Slider* sliderThatWasMoved);
  void buttonClicked (Button* buttonThatWasClicked);
  static void openPlayPlotDialog();
private:
  bool rescalex, rescaley;
  Plotter* plotter;
  GroupComponent* xgroup;
  GroupComponent* ygroup;
  GroupComponent* ogroup;
  GroupComponent* pgroup;
  GroupComponent* fgroup;
  Label* startlabel;
  Slider* startinc;
  Label* durlabel;
  Slider* durinc;
  Label* lowkeylabel;
  Slider* lowkeyinc;
  Label* highkeylabel;
  Slider* highkeyinc;
  Label* amplabel;
  Slider* ampinc;
  Label* chanlabel;
  Slider* chaninc;
  ToggleButton* layerbutton;
  TextButton* playbutton;
  TextButton* hushbutton;
  TextButton* writebutton;
  FilenameComponent* filebrowser;
  void playPlot(bool write);
};

PlayPlotDialog::PlayPlotDialog (Plotter* pl)
  :  plotter (0),
     rescalex(true),
     rescaley(true),
     xgroup (0),
     ygroup (0),
     ogroup (0),
     pgroup (0),
     fgroup (0),
     startlabel (0),
     startinc (0),
     durlabel (0),
     durinc (0),

     lowkeylabel (0),
     lowkeyinc (0),
     highkeyinc (0),
     highkeylabel (0),
     amplabel (0),
     ampinc (0),
     chanlabel (0),
     chaninc (0),
     layerbutton (0),
     playbutton (0),
     hushbutton (0),
     filebrowser (0),
     writebutton (0)
{
  plotter=pl;
  Slider::SliderStyle ss=Slider::LinearHorizontal;

  xgroup=new GroupComponent(String::empty, T("X Axis (seconds)"));
  addAndMakeVisible(xgroup);
  Axis* axis=plotter->getHorizontalAxisView()->getAxis();
  addAndMakeVisible(startlabel=new Label(String::empty,T("Play Length:")));
  startlabel->setFont (Font (15.0000f, Font::plain));
  startlabel->setJustificationType (Justification::centredLeft);
  startlabel->setEditable (false, false, false);
  startlabel->setColour (TextEditor::textColourId, Colours::black);
  startlabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

  addAndMakeVisible(startinc = new Slider (String::empty));
  startinc->setSliderStyle(ss);
  startinc->setPopupMenuEnabled(true);
  if (axis->getType()==Axis::seconds)
    startinc->setRange(1, axis->getMaximum()-axis->getMinimum(), .1);
  else
    startinc->setRange(1, 10, .1);
  startinc->setTextBoxStyle(Slider::TextBoxLeft, false, 80, 20);
  startinc->addListener(this);
  
  addAndMakeVisible(durlabel=new Label(String::empty, T("Note Duration:")));
  durlabel->setFont (Font (15.0000f, Font::plain));
  durlabel->setJustificationType (Justification::centredLeft);
  durlabel->setEditable (false, false, false);
  durlabel->setColour (TextEditor::textColourId, Colours::black);
  durlabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (durinc = new Slider (String::empty));
  durinc->setRange (0, 10, .05);
  durinc->setValue(.5);
  durinc->setSliderStyle (ss);
  durinc->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
  durinc->addListener (this);
  if (axis->getType()==Axis::seconds)
    {
      startlabel->setEnabled(false);
      startinc->setEnabled(false);
      durlabel->setEnabled(false);
      durinc->setEnabled(false);
      rescalex=false;
    }  

  // Y axis group
  ygroup=new GroupComponent(String::empty, T("Y Axis (key numbers)"));
  addAndMakeVisible(ygroup);
  axis=plotter->getVerticalAxisView()->getAxis();

  addAndMakeVisible(lowkeylabel=new Label(String::empty, T("Lowest note:")));
  lowkeylabel->setFont (Font (15.0000f, Font::plain));
  lowkeylabel->setJustificationType (Justification::centredLeft);
  lowkeylabel->setEditable (false, false, false);
  lowkeylabel->setColour (TextEditor::textColourId, Colours::black);
  lowkeylabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (lowkeyinc = new Slider(String::empty));
  lowkeyinc->setRange (0, 127, 1);
  lowkeyinc->setValue(0);
  lowkeyinc->setSliderStyle(ss);
  lowkeyinc->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
  lowkeyinc->addListener (this);
  
  addAndMakeVisible(highkeylabel=new Label(String::empty, T("Highest note:")));
  highkeylabel->setFont (Font (15.0000f, Font::plain));
  highkeylabel->setJustificationType (Justification::centredLeft);
  highkeylabel->setEditable (false, false, false);
  highkeylabel->setColour (TextEditor::textColourId, Colours::black);
  highkeylabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

  addAndMakeVisible (highkeyinc = new Slider(String::empty));
  highkeyinc->setRange (0, 127, 1);
  highkeyinc->setValue(127);
  highkeyinc->setSliderStyle(ss);
  highkeyinc->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
  highkeyinc->addListener (this);
  if (axis->getType()==Axis::keynum)
    {
      lowkeylabel->setEnabled(false);
      lowkeyinc->setEnabled(false);
      highkeylabel->setEnabled(false);
      highkeyinc->setEnabled(false);
      rescaley=false;
    }

  // Amplitude
  addAndMakeVisible(amplabel=new Label(String::empty, T("Amplitude:")));
  amplabel->setFont (Font (15.0000f, Font::plain));
  amplabel->setJustificationType (Justification::centredLeft);
  amplabel->setEditable (false, false, false);
  amplabel->setColour (TextEditor::textColourId, Colours::black);
  amplabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

  addAndMakeVisible(ampinc=new Slider(String::empty));
  ampinc->setRange (0, 1.0, 0.05);
  ampinc->setValue(.5);
  ampinc->setSliderStyle(ss);
  ampinc->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
  ampinc->addListener (this);
  
  // Channel
  addAndMakeVisible(chanlabel=new Label(String::empty, T("Channel:")));
  chanlabel->setFont (Font (15.0000f, Font::plain));
  chanlabel->setJustificationType (Justification::centredLeft);
  chanlabel->setEditable (false, false, false);
  chanlabel->setColour (TextEditor::textColourId, Colours::black);
  chanlabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible(chaninc=new Slider(String::empty));
  chaninc->setRange (0, 15, 1);
  chaninc->setSliderStyle(ss);
  chaninc->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
  chaninc->addListener (this);
  
  addAndMakeVisible(layerbutton=new ToggleButton(String::empty));
  layerbutton->setButtonText (T("All Layers"));
  layerbutton->setToggleState(true,false);
  layerbutton->addListener (this);

  addAndMakeVisible(playbutton=new TextButton(String::empty));
  playbutton->setButtonText (T("Play"));
  playbutton->setEnabled(MidiOutPort::getInstance()->isOpen());
  playbutton->addListener(this);
  addAndMakeVisible(hushbutton=new TextButton(String::empty));
  hushbutton->setButtonText (T("Hush"));
  hushbutton->setEnabled(MidiOutPort::getInstance()->isOpen());
  hushbutton->addListener (this);

  addAndMakeVisible(writebutton=new TextButton(String::empty));
  writebutton->setButtonText(T("Write"));
  writebutton->addListener(this);
  File path=completeFile(plotter->getPlotTitle()+T(".mid"));
  filebrowser=new FilenameComponent(String::empty,
				    path,
				    true,
				    false,
				    true,
				    T("*.mid"),
				    T(".mid"),
				    String::empty);
  addAndMakeVisible(filebrowser);
  setSize (550, 300);
}

PlayPlotDialog::~PlayPlotDialog()
{
  deleteAndZero (xgroup);
  deleteAndZero (ygroup);
  deleteAndZero (ogroup);
  deleteAndZero (pgroup);
  deleteAndZero (fgroup);
  deleteAndZero (startlabel);
  deleteAndZero (startinc);
  deleteAndZero (durlabel);
  deleteAndZero (durinc);
  deleteAndZero (lowkeylabel);
  deleteAndZero (lowkeyinc);
  deleteAndZero (highkeylabel);
  deleteAndZero (highkeyinc);
  deleteAndZero (amplabel);
  deleteAndZero (ampinc);
  deleteAndZero (chanlabel);
  deleteAndZero (chaninc);
  deleteAndZero (layerbutton);
  deleteAndZero (playbutton);
  deleteAndZero (hushbutton);
  deleteAndZero (filebrowser);
  deleteAndZero (writebutton);
}

void PlayPlotDialog::resized()
{
  int slwidth=138;
  int labelwidth=90;
  int slcol1=120;
  int slcol2=380;

  xgroup->setBounds (16, 8, 520, 64);
  startlabel->setBounds (32, 32, labelwidth, 24);
  startinc->setBounds (slcol1, 32, slwidth, 24);
  durlabel->setBounds (288, 32, labelwidth, 24); //72
  durinc->setBounds (380, 32, slwidth, 24); //(368, 32, 150, 24)
  ygroup->setBounds (16, 80, 520, 64);
  lowkeylabel->setBounds (32, 104, labelwidth, 24);
  lowkeyinc->setBounds (slcol1, 104, slwidth, 24);
  highkeylabel->setBounds (288, 104, labelwidth, 24);
  highkeyinc->setBounds (slcol2, 104, slwidth, 24);
  amplabel->setBounds (32, 160, labelwidth, 24);
  ampinc->setBounds (slcol1, 160, slwidth, 24);
  chanlabel->setBounds (288, 160, labelwidth, 24);
  chaninc->setBounds (slcol2, 160, slwidth, 24);
  layerbutton->setBounds (32, 200, 120, 24);
  filebrowser->setBounds (32, 240, 396, 24);
  writebutton->setBounds (440, 240, 87, 24);

  playbutton->setBounds (440, 280, 87, 24);
  hushbutton->setBounds (344, 280, 87, 24);


}

void PlayPlotDialog::sliderValueChanged (Slider* slider)
{
  if (slider == startinc)
    {
    }
  else if (slider == durinc)
    {
    }
  else if (slider == lowkeyinc)
    {
    }
  else if (slider == highkeyinc)
    {
    }
  else if (slider == ampinc)
    {
    }
  else if (slider == chaninc)
    {
    }
}

void PlayPlotDialog::buttonClicked (Button* button)
{
  if (button == playbutton)
    {
      playPlot(false);
    }
  else if (button == writebutton)
    {
      playPlot(true);
    }
  else if (button == hushbutton)
    {
      MidiOutPort::getInstance()->clear();
    }
  else if (button == layerbutton)
    {
    }
}

void PlayPlotDialog::playPlot(bool write)
{
  double len=startinc->getValue();
  double dur=durinc->getValue();
  double amp=ampinc->getValue();
  int chan=(int)chaninc->getValue();
  double key1=lowkeyinc->getValue();
  double key2=highkeyinc->getValue();
  Axis* axis=plotter->getHorizontalAxisView()->getAxis();
  double xmin=axis->getMinimum();
  double xmax=axis->getMaximum();
  axis=plotter->getVerticalAxisView()->getAxis();  
  double ymin=axis->getMinimum();
  double ymax=axis->getMaximum();

  if (write)
    MidiOutPort::getInstance()->clearSequence();
  for (int i=0;i<plotter->numLayers(); i++)
    {
      Layer* l=plotter->getLayer(i);
      if (layerbutton->getToggleState() || plotter->isFocusLayer(l))
	{
	  // only access a z value if arity>2 and hbox style
	  bool getz=(!rescalex && l->getLayerArity()>2 &&
		     l->isDrawStyle(Layer::hbox));
	  for (int j=0; j<l->numPoints(); j++)
	    {
	      LayerPoint* p=l->getPoint(j);
	      double x, z;
	      double y=l->getPointY(p);
	      if (rescalex) 
		{
		  x=cm_rescale(l->getPointX(p),xmin,xmax,0,len,1) ;
		  z=dur;
		}
	      else
		{
		  x=l->getPointX(p);
		  z=(getz) ? l->getPointZ(p) : dur;
		}
	      if (rescaley)
		y=cm_rescale(y,ymin,ymax,key1,key2,1);
	      MidiOutPort::getInstance()->sendNote(x,z,y,amp,chan,write);
	    }
	}
    }
  if (write)
    {
      String path=filebrowser->getCurrentFile().getFullPathName();
      MidiOutPort::getInstance()->setOutputFile(path);
      MidiOutPort::getInstance()->saveSequence(false);
    }
}

class PlayPlotWindow : public DocumentWindow 
{
public:
  PlayPlotWindow(PlotWindow* win)
    : DocumentWindow(String::empty, Colour(0xffe5e5e5),
		     DocumentWindow::closeButton, true)
  {
    PlayPlotDialog* comp=new PlayPlotDialog(win->plotter);
    setName(T("Play ")+win->getName());
    setContentComponent(comp,true,true);
    setUsingNativeTitleBar(true);
    setDropShadowEnabled(true);
    setVisible(true);
    centreAroundComponent(win->plotter, getWidth(), getHeight());
  }
  ~PlayPlotWindow()
  {
  }
  void closeButtonPressed()
  {
    delete this;
  }
};

void PlotWindow::openPlayPlotDialog ()
{
  new PlayPlotWindow(this);
  /*
  DialogWindow::showModalDialog(T("Play ")+getName(),
				new PlayPlotDialog(plotter),
				this,
				Colour(0xffe5e5e5),
				false);
  */
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
  StringArray fields;
  plotter->getFieldNames(fields);
  LayerPoint* p=(plotter->numSelected()==1)
    ? plotter->getSelected(0) : NULL ;
  for (int i=0; i<fields.size(); i++)
    {
      labels.add(new Label(String::empty, fields[i]));
      editors.add(new Label(fields[i], 
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
  int h=(fields.size()*lineheight)+((fields.size()+1)*margin);
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

