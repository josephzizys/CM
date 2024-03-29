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
#include "Commands.h"
#include "Help.h"
#include "Scheme.h"
#ifdef WITH_FOMUS
#include "Fomus.h"
#endif
#ifdef WITH_LIBLO
#include "Osc.h"
#endif

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
  PopupMenu recout;

  // Midi Out
  StringArray outdevs = MidiOutput::getDevices();
  int size = jlimit(0,CommandMenus::NumMidiOutOpen-1, outdevs.size());
  if (size>0)
    for (int i=0; i<size; i++)
      outmenu.addCommandItem(comm, CommandIDs::MidiOutOpen + i);
  else
    outmenu.addItem(CommandIDs::MidiOutOpen, T("<no devices>"), false);
  outmenu.addSeparator();
  outmenu.addCommandItem(comm, CommandIDs::MidiOutTest);
  //  outmenu.addCommandItem(comm, CommandIDs::MidiOutHush);
  outmenu.addSeparator();

  recout.addCommandItem(comm, CommandIDs::MidiOutRecording);
  recout.addCommandItem(comm, CommandIDs::MidiOutRecordingDelete);
  recout.addSeparator();
  recout.addCommandItem(comm, CommandIDs::MidiOutRecordingSave);
  recout.addCommandItem(comm, CommandIDs::MidiOutRecordingPlay);
  recout.addCommandItem(comm, CommandIDs::MidiOutRecordingImport);
  outmenu.addSubMenu(T("Recording"), recout);
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

#ifdef WITH_LIBLO
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

#ifdef WITH_SNDLIB
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
#ifdef WITH_FOMUS
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
      fomus.addCommandItem(comm, CommandIDs::FomusSaveScoreAs);
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
  menu.addCommandItem(comm, CommandIDs::SndLibInsDialog);
  menu.addCommandItem(comm, CommandIDs::SndLibInsRestore);
  menu.addSeparator();
  menu.addCommandItem(comm, CommandIDs::AudioFilePlayer);
  menu.addCommandItem(comm, CommandIDs::MidiFilePlayer);
  menu.addCommandItem(comm, CommandIDs::MidiInImportFile);
  menu.addSeparator();
  menu.addCommandItem(comm, CommandIDs::AudioSettings);
  menu.addCommandItem(comm, CommandIDs::MidiOutFileSettings);
  menu.addSeparator();
  menu.addCommandItem(comm, CommandIDs::AudioHush);
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
  PopupMenu menu, mans, gui, saltuts, scmtuts, salexamps, scmexamps, sites;
  Help* help=Help::getInstance();

  // Manuals
  help->addHelpMenuItems(mans, T("Reference"), CommandIDs::HelpManual, 8, comm);
  menu.addSubMenu(T("Reference"), mans);
  // GUI
  help->addHelpMenuItems(gui, T("GUI"), CommandIDs::HelpGUI, 8, comm);
  menu.addSubMenu(T("GUI"), gui);

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
