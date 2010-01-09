/*=======================================================================*
  Copyright (c) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify
  it under the terms of the Lisp Lesser Gnu Public License. The text
  of this agreement is available at http://www.cliki.net/LLGPL
 *=======================================================================*/

#include "Enumerations.h"
#include "Preferences.h"
#include "Menus.h"
#include "Console.h"
#include "TextEditor.h"
#include "Commands.h"
#include "Help.h"
#include "Scheme.h"
#ifdef WITHFOMUS
#include "Fomus.h"
#endif
#include <iostream>

/*=======================================================================*
                             Global Menu Building
 *=======================================================================*/

const PopupMenu CommandMenus::getRecentlyOpenedMenu()
{
  ApplicationCommandManager* comm=CommandManager::getInstance();
  Preferences* pref=Preferences::getInstance();
  PopupMenu menu;
  int size = jlimit(0, CommandMenus::NumPrefsOpenRecent-1,
		    pref->recentlyOpened.getNumFiles());
  for (int i=0; i<size; i++)
    menu.addCommandItem(comm, CommandIDs::PrefsOpenRecent + i);  
  menu.addSeparator();
  menu.addCommandItem(comm, CommandIDs::PrefsClearOpenRecent);  
  return menu;
}

const PopupMenu CommandMenus::getRecentlyLoadedMenu()
{
  ApplicationCommandManager* comm=CommandManager::getInstance();
  Preferences* pref=Preferences::getInstance();
  PopupMenu menu;
  int size = jlimit(0, CommandMenus::NumPrefsLoadRecent-1,
		    pref->recentlyLoaded.getNumFiles());
  for (int i=0; i<size; i++)
    menu.addCommandItem(comm, CommandIDs::PrefsLoadRecent + i);  
  menu.addSeparator();
  menu.addCommandItem(comm, CommandIDs::PrefsClearLoadRecent);  
  return menu;
}

const juce::PopupMenu CommandMenus::getAudioMenu(bool isfms)
{
  ApplicationCommandManager* comm=CommandManager::getInstance();
  PopupMenu menu;
  PopupMenu outmenu;
  PopupMenu inmenu;
  PopupMenu tunings;
  PopupMenu chfilt;
  PopupMenu opfilt;

  // Midi Out
  StringArray outdevs = MidiOutput::getDevices();
  int size = jlimit(0,CommandMenus::NumMidiOutOpen-1,
		    outdevs.size());
  if (size>0)
    for (int i=0; i<size; i++)
      outmenu.addCommandItem(comm, CommandIDs::MidiOutOpen + i);
  else
    outmenu.addItem(CommandIDs::MidiOutOpen, 
		    T("<no devices>"), false);
  outmenu.addSeparator();
  outmenu.addCommandItem(comm, CommandIDs::MidiOutTest);
  outmenu.addCommandItem(comm, CommandIDs::MidiOutHush);
  outmenu.addSeparator();
  for (int i=1; i<=NumMidiOutTuning; i++) // tunings 1 based!
    tunings.addCommandItem(comm, CommandIDs::MidiOutTuning + i);
  outmenu.addSubMenu(T("Tuning"), tunings);
  outmenu.addCommandItem(comm, CommandIDs::MidiOutInstruments);  
  menu.addSubMenu(T("Midi Out"), outmenu);

  // Midi In
  StringArray indevs = MidiInput::getDevices();
  size = jlimit(0,CommandMenus::NumMidiInOpen-1, indevs.size());
  if (size>0)
    for (int i=0; i<size; i++)
      inmenu.addCommandItem(comm, CommandIDs::MidiInOpen + i);
  else
    inmenu.addItem(CommandIDs::MidiInOpen, T("<no devices>"), false);
  inmenu.addSeparator();
  inmenu.addCommandItem(comm, CommandIDs::MidiInTrace);
  inmenu.addCommandItem(comm, CommandIDs::MidiInThrough);
  chfilt.addCommandItem(comm, CommandIDs::MidiInChannelFilter +
			NumMidiInChannelFilter);
  chfilt.addSeparator();
  for (int i=0; i<NumMidiInChannelFilter; i++)
    chfilt.addCommandItem(comm, CommandIDs::MidiInChannelFilter+i);
  inmenu.addSubMenu(T("Channel Filter"), chfilt);

  opfilt.addCommandItem(comm, CommandIDs::MidiInOpcodeFilter +
			NumMidiInOpcodeFilter);
  opfilt.addSeparator();
  for (int i=0; i<NumMidiInOpcodeFilter; i++)
    opfilt.addCommandItem(comm, CommandIDs::MidiInOpcodeFilter+i);
  inmenu.addSubMenu(T("Message Filter"), opfilt);
  menu.addSubMenu(T("Midi In"), inmenu);

#ifdef LIBLO
  {
    PopupMenu osc;
    osc.addCommandItem(comm, CommandIDs::OscOpen);
    osc.addSeparator();
    osc.addCommandItem(comm, CommandIDs::OscShowStatus);
    osc.addSeparator();
    osc.addCommandItem(comm, CommandIDs::OscClearHook);
    //    osc.addSeparator();
    osc.addCommandItem(comm, CommandIDs::OscTraceInput);
    // osc.addCommandItem(comm, CommandIDs::OscTraceOutput);
    menu.addSubMenu(T("OSC"), osc);
  }
#endif

#ifdef SNDLIB
  PopupMenu sndlib,chans,srate, fmats;
  for (int i=0; i<SrateIDs::NumSrates; i++)
    srate.addCommandItem(comm, CommandIDs::SndLibSrate+i);
  sndlib.addSubMenu(T("Srate"), srate);
  for (int i=0; i<ChannelIDs::NumChannels; i++) 
    chans.addCommandItem(comm, CommandIDs::SndLibChannels+i);
  sndlib.addSubMenu(T("Channels"), chans);
  for (int i=0; i<AudioFormatIDs::NumAudioFormats; i++)
    fmats.addCommandItem(comm, CommandIDs::SndLibAudioFormat+i);
  sndlib.addSubMenu(T("Audio Formats"), fmats);

  sndlib.addCommandItem(comm, CommandIDs::SndLibAutoPlay);
  sndlib.addSeparator();
  sndlib.addCommandItem(comm, CommandIDs::SndLibInsDialog);
  sndlib.addCommandItem(comm, CommandIDs::SndLibInsRestore);
  menu.addSubMenu(T("SndLib"),sndlib);
#endif
  PopupMenu csound;
  csound.addCommandItem(comm, CommandIDs::CsoundPrefWriteAfter);
  csound.addCommandItem(comm, CommandIDs::CsoundPrefPlayAfter);
  csound.addSeparator();
  csound.addCommandItem(comm, CommandIDs::CsoundExportScore);
  csound.addCommandItem(comm, CommandIDs::CsoundClearScore);
  csound.addSeparator();
  csound.addCommandItem(comm, CommandIDs::CsoundOpenSettings);
  menu.addSubMenu(T("Csound"), csound);
#ifdef WITHFOMUS
  if (fomus_exists) {
    PopupMenu fomus;
    if (isfms) {
      fomus.addCommandItem(comm, CommandIDs::FomusRunCurr);
    } else {
      size = jlimit(0, CommandMenus::NumFomusScore-1,
		    Fomus::getInstance()->numScores());
      for (int i=0; i<size; i++)
	fomus.addCommandItem(comm, CommandIDs::FomusSelectScore + i);
      fomus.addSeparator();
      fomus.addCommandItem(comm, CommandIDs::FomusRunScore);
      fomus.addSeparator();
      fomus.addCommandItem(comm, CommandIDs::FomusNewScore);
      fomus.addCommandItem(comm, CommandIDs::FomusLoadScore);
      fomus.addCommandItem(comm, CommandIDs::FomusRenameScore);
      fomus.addCommandItem(comm, CommandIDs::FomusSaveScore);
      fomus.addCommandItem(comm, CommandIDs::FomusClearScore);
      fomus.addCommandItem(comm, CommandIDs::FomusDeleteScore);
      fomus.addSeparator();
      fomus.addCommandItem(comm, CommandIDs::FomusSettings);
      fomus.addCommandItem(comm, CommandIDs::FomusDocumentation);
    }
    menu.addSubMenu(T("Fomus"), fomus);
  }
#endif

  menu.addSeparator();
  menu.addCommandItem(comm, CommandIDs::MidiPlotPlayer);
  menu.addCommandItem(comm, CommandIDs::MidiFilePlayer);
  menu.addCommandItem(comm, CommandIDs::MidiOutFileSettings);
  menu.addCommandItem(comm, CommandIDs::MidiInImportFile);
  menu.addSeparator();
  menu.addCommandItem(comm, CommandIDs::AudioOpenFilePlayer);
  menu.addCommandItem(comm, CommandIDs::AudioSettings);
  return menu;
}

const PopupMenu CommandMenus::getWindowMenu()
{
  ApplicationCommandManager* comm=CommandManager::getInstance();
  PopupMenu menu;
  int size=jlimit(0, CommandMenus::NumWindowSelect-1,
		  TopLevelWindow::getNumTopLevelWindows());
  // Console Window is always at zero.
  menu.addCommandItem(comm, CommandIDs::WindowSelect + 0);
  for (int i=1; i<size; i++)
    {
      TopLevelWindow* w = TopLevelWindow::getTopLevelWindow(i);
      menu.addCommandItem(comm, CommandIDs::WindowSelect + i);
    }
  return menu;
}

const PopupMenu CommandMenus::getFontSizeMenu(ApplicationCommandManager*
					      comm, CommandID rootid)
{
  // called by Console and Editor to set their font sizes
  PopupMenu menu;
  for (int i=0; i<NumFontSize; i++)
    menu.addCommandItem(comm, rootid + i);
  return menu;
}

const PopupMenu CommandMenus::getHelpMenu(int wtype,
					  ApplicationCommandManager* com2)
{
  ApplicationCommandManager* comm=CommandManager::getInstance();
  PopupMenu menu, mans, saltuts, scmtuts, salexamps, scmexamps, sites;
  Help* help=Help::getInstance();

  // Manuals
  help->addHelpMenuItems(mans, T("Manuals"), CommandIDs::HelpManual, 8, comm);
  if (wtype==WindowTypes::TextEditor)
    {
      mans.addSeparator();
      mans.addCommandItem(com2, CommandIDs::EditorSymbolHelp);
    }

  menu.addSubMenu(T("Manuals"), mans);
  if (!SysInfo::isGraceCL())
    {
      PopupMenu tutorials, examples;
      help->addHelpMenuItems(salexamps, T("Sal Examples"), CommandIDs::HelpSalExample, 32, comm);
      salexamps.addSeparator();
      salexamps.addCommandItem(comm, CommandIDs::HelpSalExamplesRestore);

      help->addHelpMenuItems(scmexamps, T("Scheme Examples"), CommandIDs::HelpSchemeExample, 32, comm);
      scmexamps.addSeparator();
      scmexamps.addCommandItem(comm, CommandIDs::HelpSchemeExamplesRestore);

      help->addHelpMenuItems(saltuts, T("Sal Tutorials"), CommandIDs::HelpSalTutorial, 16, comm);
      saltuts.addSeparator();
      saltuts.addCommandItem(comm, CommandIDs::HelpSalTutorialsRestore);

      help->addHelpMenuItems(scmtuts, T("Scheme Tutorials"), CommandIDs::HelpSchemeTutorial, 16, comm);
      scmtuts.addSeparator();
      scmtuts.addCommandItem(comm, CommandIDs::HelpSchemeTutorialsRestore);

      tutorials.addSubMenu(T("Sal"), saltuts);
      tutorials.addSubMenu(T("Scheme"), scmtuts);
      menu.addSubMenu(T("Tutorials"), tutorials);

      examples.addSubMenu(T("Sal"), salexamps);
      examples.addSubMenu(T("Scheme"), scmexamps);
      menu.addSubMenu(T("Examples"), examples);
    }
  help->addHelpMenuItems(sites, T("Web Sites"), CommandIDs::HelpWebSite, 8, comm);
  menu.addSubMenu(T("Web Sites"), sites);

  //  menu.addSeparator();
  //  menu.addCommandItem(comm, CommandIDs::HelpShowDirectory);

  return menu;
}

/*=======================================================================*
                             Console Menus
 *=======================================================================*/

const StringArray ConsoleWindow::getMenuBarNames ()
{
  const tchar* const names[]={
    T("File"), T("Console"),
#ifndef GRACECL
    T("Audio"),
#endif
    T("Window"), T("Help"), 0
  }; 
  return StringArray((const tchar**) names);
}

const PopupMenu ConsoleWindow::getMenuForIndex (int idx, const String &name)
{
  PopupMenu menu;
  PopupMenu prefmenu;
  ApplicationCommandManager* manager=Console::getInstance()->manager;
  // global command manager
  ApplicationCommandManager* gmanager=CommandManager::getInstance();
  Preferences* pref=Preferences::getInstance();
  if (name==T("File"))
    {
      menu.addCommandItem(manager, CommandIDs::ConsoleNewEditor);
      menu.addCommandItem(manager, CommandIDs::ConsoleOpen);
      if (pref->recentlyOpened.getNumFiles()>0)
	menu.addSubMenu(T("Open Recent"), 
			CommandMenus::getRecentlyOpenedMenu());
      menu.addSeparator();
      menu.addCommandItem(gmanager, CommandIDs::PlotterNew);
      menu.addCommandItem(gmanager, CommandIDs::PlotterOpen);
      menu.addCommandItem(gmanager, CommandIDs::PlotterOpenMidiFile);
#ifdef GRACECL
      menu.addSeparator();
      menu.addCommandItem(gmanager, CommandIDs::LispStart);
      menu.addCommandItem(gmanager, CommandIDs::LispConfigure);
#endif
      menu.addSeparator();
      menu.addCommandItem(gmanager,CommandIDs::LispCompileFile);
      menu.addCommandItem(gmanager,CommandIDs::LispLoadFile);
      if (pref->recentlyLoaded.getNumFiles()>0)
	menu.addSubMenu(T("Load Recent"), 
			CommandMenus::getRecentlyLoadedMenu());
      menu.addSeparator();

      menu.addCommandItem(gmanager,CommandIDs::PrefsSetInitFile);
      menu.addCommandItem(gmanager,CommandIDs::PrefsClearInitFile);
      menu.addSeparator();
      menu.addCommandItem(manager, CommandIDs::ConsoleShowDirectory);
      menu.addCommandItem(manager, CommandIDs::ConsoleSetDirectory);  
      menu.addSeparator();
      menu.addCommandItem(CommandManager::getInstance(), 
			  CommandIDs::AppQuit);
    }
  else if (name==T("Console"))
    {
      PopupMenu themes;
      for (int i=0; i<Console::getInstance()->numThemes(); i++)
        themes.addCommandItem(manager, CommandIDs::ConsoleTheme + i);
      menu.addSubMenu(T("Themes"), themes);
      menu.addSubMenu(T("Font Size"),
		      CommandMenus::getFontSizeMenu(manager,
						    CommandIDs::ConsoleFontSize
						    ));
      //      menu.addSeparator();
      //      menu.addCommandItem(manager, CommandIDs::SchemeShowVoidValues);
      menu.addSeparator();
      menu.addCommandItem(manager, CommandIDs::ConsoleCopy);
      menu.addCommandItem(manager, CommandIDs::ConsoleSelectAll);
      menu.addCommandItem(manager, CommandIDs::ConsoleClearSelection);
      menu.addSeparator();
      menu.addCommandItem(manager, CommandIDs::ConsoleBeepOnError);
      menu.addSeparator();
      menu.addCommandItem(manager, CommandIDs::ConsoleClearConsole);
    }
  else if (name==T("Audio"))
    {
      menu=CommandMenus::getAudioMenu(false);
    }
  else if (name==T("Window"))
    {
      menu=CommandMenus::getWindowMenu();
    }
  else if (name==T("Help"))
    {
      menu=CommandMenus::getHelpMenu(WindowTypes::Console, NULL);
    }
  return menu;
}

void ConsoleWindow::menuItemSelected (int comid, int index)
{
}

/*=======================================================================*
                             Text Editor Menus
 *=======================================================================*/

const StringArray TextEditorWindow::getMenuBarNames()
{
  const tchar* const menubar [] = 
    {T("File"), T("Edit"), T("Options"), T("Eval"),
#ifndef GRACECL
     T("Audio"),
#endif
     T("Windows"), T("Help"), 0};
  return StringArray((const tchar**)menubar);
}

const PopupMenu TextEditorWindow::getMenuForIndex(int index, 
						  const String& menuname)
{
  PopupMenu menu;
  Preferences* pref=Preferences::getInstance();
  ApplicationCommandManager* manager=getTextBuffer()->manager;
  ApplicationCommandManager* gmanager=CommandManager::getInstance();
  if (menuname==T("File")) 
    {
      menu.addCommandItem(manager, CommandIDs::EditorNew);
      menu.addCommandItem(manager, CommandIDs::EditorOpen);
      if (pref->recentlyOpened.getNumFiles()>0)
	menu.addSubMenu(T("Open Recent"), 
			CommandMenus::getRecentlyOpenedMenu());

      menu.addSeparator();
      menu.addCommandItem(manager, CommandIDs::EditorSave);
      menu.addCommandItem(manager, CommandIDs::EditorSaveAs);
      menu.addCommandItem(manager, CommandIDs::EditorRevert);
      menu.addSeparator();
      menu.addSeparator();
      menu.addCommandItem(gmanager, CommandIDs::PlotterNew);

      menu.addCommandItem(gmanager,CommandIDs::LispLoadFile);
      if (pref->recentlyLoaded.getNumFiles()>0)
	menu.addSubMenu(T("Load Recent"), 
			CommandMenus::getRecentlyLoadedMenu());

      menu.addSeparator();
      menu.addCommandItem(gmanager,CommandIDs::PrefsSetInitFile);
      menu.addCommandItem(gmanager,CommandIDs::PrefsClearInitFile);

      menu.addSeparator();
      menu.addCommandItem(manager, CommandIDs::EditorShowDirectory);
      menu.addCommandItem(manager, CommandIDs::EditorSetDirectory);  

      //      menu.addSeparator();
      //      menu.addCommandItem(manager, CommandIDs::EditorPrint);
      menu.addSeparator();
      menu.addCommandItem(manager, CommandIDs::EditorClose);
    }
  else if (menuname==T("Edit"))
    {
      menu.addCommandItem(manager, CommandIDs::EditorUndo);
      menu.addCommandItem(manager, CommandIDs::EditorRedo);
      menu.addSeparator();
      menu.addCommandItem(manager, CommandIDs::EditorCut);
      menu.addCommandItem(manager, CommandIDs::EditorCopy);
      menu.addCommandItem(manager, CommandIDs::EditorPaste);
      menu.addCommandItem(manager, CommandIDs::EditorSelectAll);

      menu.addSeparator();
      menu.addCommandItem(manager, CommandIDs::EditorIndent);
      menu.addCommandItem(manager, CommandIDs::EditorCommentOut);
      menu.addCommandItem(manager, CommandIDs::EditorUncommentOut);
      menu.addCommandItem(manager, CommandIDs::EditorFormatComments);

      menu.addSeparator();
      menu.addCommandItem(manager, CommandIDs::EditorFind);
    }
  else if (menuname==T("Options")) 
    {
      PopupMenu synt, tabs;
      synt.addCommandItem(manager,CommandIDs::EditorSyntax+TextIDs::Text);
      synt.addCommandItem(manager,CommandIDs::EditorSyntax+TextIDs::Sal);
      synt.addCommandItem(manager,CommandIDs::EditorSyntax+TextIDs::Lisp);
      menu.addSubMenu(T("Syntax"), synt);
      menu.addSeparator();
      menu.addSubMenu(T("Font Size"),
		      CommandMenus::getFontSizeMenu(manager,
						    CommandIDs::EditorFontSize
						    ));
      for (int i=0; i<CommandMenus::NumTabWidth; i++)
	tabs.addCommandItem(manager,CommandIDs::EditorTabWidth+i);
      menu.addSubMenu(T("Tab Width"), tabs);
      menu.addSeparator();
      menu.addCommandItem(manager,CommandIDs::EditorParensMatching);
      menu.addCommandItem(manager,CommandIDs::EditorHighlighting);
      menu.addCommandItem(manager,CommandIDs::EditorEmacsMode);
      
    }
  else if (menuname==T("Eval"))
    {
      menu.addCommandItem(manager, CommandIDs::EditorExecute);
      menu.addCommandItem(manager, CommandIDs::EditorExpand);
      PopupMenu proc;
      proc.addCommandItem(manager, CommandIDs::SchedulerPause);
      proc.addCommandItem(manager, CommandIDs::SchedulerStop);
      menu.addSubMenu(T("Scheduler"), proc);

     // Trigger submenu belongs to the window NOT the buffer.
      PopupMenu trigs;
      bool trigp=hasTrigger();
      for (int i=TriggerIDs::ButtonTrigger; i<=TriggerIDs::NumTriggers; i++)
	trigs.addItem(CommandIDs::EditorAddTrigger+i,
		      String("New ") + TriggerIDs::toPrettyString(i),
		      // HACK disable MidiIn.
		      ((!trigp) && (i!=TriggerIDs::MidiInTrigger)));
      trigs.addItem(CommandIDs::EditorImportTrigger,
		    T("New from Region (XML)"),
		    (!trigp) && getTextBuffer()->isRegion()
		    );
      //      trigs.addSeparator();
      //      trigs.addItem(CommandIDs::EditorLoadTrigger,
      //		    T("Load Trigger..."), !trigp);
      //      trigs.addItem(CommandIDs::EditorSaveTrigger,
      //		    T("Save Trigger..."), trigp);
      trigs.addSeparator();
      //      trigs.addItem(CommandIDs::EditorRemoveTrigger,
      //		    T("Remove Trigger"), trigp);
      //      trigs.addSeparator();
      trigs.addItem(CommandIDs::EditorExportTrigger,
		    T("Export to Buffer (XML)"), trigp);
      //      trigs.addSeparator();
      //      trigs.addItem(CommandIDs::EditorConfigureTrigger,
      //		    T("Configure Trigger..."), trigp);
      menu.addSeparator();
      menu.addSubMenu(T("Triggers"), trigs);

    }      
  else if (menuname==T("Audio"))
    {
      menu=CommandMenus::getAudioMenu(isfms);
    }
  else if (menuname==T("Windows"))
    {
      menu=CommandMenus::getWindowMenu();
    }
  else if (menuname==T("Help"))
    {
      menu=CommandMenus::getHelpMenu(WindowTypes::TextEditor,
				    manager );
    }
  return menu;
}

void TextEditorWindow::menuItemSelected (int comid, int idex)
{
  int comm = CommandIDs::getCommand(comid);
  int data = CommandIDs::getCommandData(comid);
  switch (comm)
    {
    case CommandIDs::EditorAddTrigger :
      addTrigger(data);
      break;
    case CommandIDs::EditorRemoveTrigger :
      removeTrigger();
      break;
    case CommandIDs::EditorLoadTrigger :
      loadTrigger();
      break;
    case CommandIDs::EditorSaveTrigger :
      saveTrigger();
      break;
    case CommandIDs::EditorImportTrigger :
      importTrigger();
      break;
    case CommandIDs::EditorExportTrigger :
      exportTrigger();
      break;
    case CommandIDs::EditorConfigureTrigger :
      configureTrigger();
      break;
    default:
      break;
    }
}


