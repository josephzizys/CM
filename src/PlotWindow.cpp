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
  static const int tabviewheight=150;
  PlotWindowComponent (PlotWindow* win) : plotwin (win) {}
  ~PlotWindowComponent () 
  {
    // this deletes the Plotter and the TabbedEditor
    deleteAllChildren();
  }
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
  tabview = new PlotEditor();
  plotter->editor=tabview;
  init();
}

PlotWindow::PlotWindow(String title, MidiFile& midifile)
  : DocumentWindow (title, Colours::white, 
		    DocumentWindow::allButtons, true)
{
  listener.window=this;
  setName(title);
  plotter=new Plotter(midifile);
  tabview = new PlotEditor();
  plotter->editor=tabview;
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
  tabview->addTab(T("Audio"), Colour(0xffe5e5e5), new PlotAudioEditor(plotter), false);
  tabview->addTab(T("Export"), Colour(0xffe5e5e5), new ExportPointsEditor(plotter), false);
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
    PlotWindow::openPlayPlotDialog ();
    break;

  case CommandIDs::PlotterZoomReset:
    PlotWindow::openRescalePointsDialog (CommandIDs::PlotterRescalePoints);
    break;

  case CommandIDs::PlotterZoomToFit:
    PlotWindow::openRescalePointsDialog (CommandIDs::PlotterShiftPoints);
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

