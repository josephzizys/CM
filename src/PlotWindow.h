/*=======================================================================*
  Copyright (C) 2011 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#ifndef PlotWindow_h
#define PlotWindow_h

#include "Libraries.h"

///
/// Plot Window
///

class Plotter;
class PlotTabbedEditor;

class PlotWindow : public DocumentWindow //, public MenuBarModel
{

 public:

  class PlotWindowListener : public MessageListener
  {
  public:
    void handleMessage (const Message &message);//{std::cout << "message!\n";}
    PlotWindow* window;
  PlotWindowListener() : window(0) {}
  };
  PlotWindowListener listener;
  Plotter* plotter;
  PlotTabbedEditor* tabview;
  File plotfile;
  //  MenuBarComponent* menubar;
  PlotWindow (XmlElement* plot);
  PlotWindow (String title, MidiFile& midifile);
  void init();
  virtual ~PlotWindow ();
  const StringArray getMenuBarNames ();
  const PopupMenu getMenuForIndex (int idx, const String &name);
  void menuItemSelected (int id, int idx);
  void closeButtonPressed () ;
  void openExportDialog();
  void openLayerDialog();
  void openAxisDialog(int orient);
  void openPlayPlotDialog();
  void openEditPointsDialog();
  void openRescalePointsDialog(int cmd);
  //  static void openXml(String str);
  static void openWindowFromXml(void* str);
  static void browseForFileToOpen(int type);
  static void openXmlFile(File file);
  static void openMidiFile(File file);
  void addXmlPoints(String xml);
  bool save(bool saveas=false);
  bool hasUnsavedChanges();
  String toXmlString();
  String getPlotTitle() {return getName();}
  void setPlotTitle(String titl){setName(titl);}
  File getPlotFile() {return plotfile;}
  void setPlotFile(File fil) {plotfile=fil;}
  static PlotWindow* getPlotWindow(String title) ;
};

#endif

