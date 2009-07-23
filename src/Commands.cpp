/*=======================================================================*
  Copyright (c) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify
  it under the terms of the Lisp Lesser Gnu Public License. The text
  of this agreement is available at http://www.cliki.net/LLGPL
 *=======================================================================*/

#include "Enumerations.h"
#include "Commands.h"
#include "Midi.h"
#include "Scheme.h"
#include "Syntax.h"
#include "TextEditor.h"
#include "Console.h"
#include "Help.h"
#include "Main.h"
#include "Preferences.h"
#include "Audio.h"
#include "Csound.h"
#include "Plot.h"

#include "CommonLisp.h"

#ifdef WITHFOMUS
#include "Fomus.h"
#include "Plot.h"
#endif


#ifdef SNDLIB
#include "SndLib.h"
#endif

#include <iostream>

/*=======================================================================*
                     Application wide commands             
 *=======================================================================*/

ApplicationCommandTarget* Grace::getNextCommandTarget()
{
  return 0;
}

void Grace::getAllCommands(juce::Array<juce::CommandID>& commands)
{
  const CommandID ids[] = 
  {
    // File Commands

    CommandIDs::AppQuit,

    CommandIDs::LispLoadFile,
    CommandIDs::LispCompileFile,
    CommandIDs::LispConfigure,
    CommandIDs::LispStart,

    CommandIDs::PrefsOpenRecent + 0,
    CommandIDs::PrefsOpenRecent + 1,
    CommandIDs::PrefsOpenRecent + 2,
    CommandIDs::PrefsOpenRecent + 3,
    CommandIDs::PrefsOpenRecent + 4,
    CommandIDs::PrefsOpenRecent + 5,
    CommandIDs::PrefsOpenRecent + 6,
    CommandIDs::PrefsOpenRecent + 7,
    CommandIDs::PrefsOpenRecent + 8,
    CommandIDs::PrefsOpenRecent + 9,
    CommandIDs::PrefsOpenRecent + 10,
    CommandIDs::PrefsOpenRecent + 11,
    CommandIDs::PrefsOpenRecent + 12,
    CommandIDs::PrefsOpenRecent + 13,
    CommandIDs::PrefsOpenRecent + 14,
    CommandIDs::PrefsOpenRecent + 15,
    CommandIDs::PrefsClearOpenRecent,


    CommandIDs::PrefsLoadRecent + 0,
    CommandIDs::PrefsLoadRecent + 1,
    CommandIDs::PrefsLoadRecent + 2,
    CommandIDs::PrefsLoadRecent + 3,
    CommandIDs::PrefsLoadRecent + 4,
    CommandIDs::PrefsLoadRecent + 5,
    CommandIDs::PrefsLoadRecent + 6,
    CommandIDs::PrefsLoadRecent + 7,
    CommandIDs::PrefsLoadRecent + 8,
    CommandIDs::PrefsLoadRecent + 9,
    CommandIDs::PrefsLoadRecent + 10,
    CommandIDs::PrefsLoadRecent + 11,
    CommandIDs::PrefsLoadRecent + 12,
    CommandIDs::PrefsLoadRecent + 13,
    CommandIDs::PrefsLoadRecent + 14,
    CommandIDs::PrefsLoadRecent + 15,
    CommandIDs::PrefsClearLoadRecent,
    CommandIDs::PrefsSetInitFile,
    CommandIDs::PrefsClearInitFile,  

    // MidiOut Port
    CommandIDs::MidiOutOpen + 0,
    CommandIDs::MidiOutOpen + 1,
    CommandIDs::MidiOutOpen + 2,
    CommandIDs::MidiOutOpen + 3,
    CommandIDs::MidiOutOpen + 4,
    CommandIDs::MidiOutOpen + 5,
    CommandIDs::MidiOutOpen + 6,
    CommandIDs::MidiOutOpen + 7,
    CommandIDs::MidiOutOpen + 8,
    CommandIDs::MidiOutOpen + 9,
    CommandIDs::MidiOutOpen + 10,
    CommandIDs::MidiOutOpen + 11,
    CommandIDs::MidiOutOpen + 12,
    CommandIDs::MidiOutOpen + 13,
    CommandIDs::MidiOutOpen + 14,
    CommandIDs::MidiOutOpen + 15,
    CommandIDs::MidiOutTest,
    CommandIDs::MidiOutHush,
    CommandIDs::MidiOutTuning + 1, // tuning nums are 1-16 inclusive
    CommandIDs::MidiOutTuning + 2,
    CommandIDs::MidiOutTuning + 3,
    CommandIDs::MidiOutTuning + 4,
    CommandIDs::MidiOutTuning + 5,
    CommandIDs::MidiOutTuning + 6,
    CommandIDs::MidiOutTuning + 7,
    CommandIDs::MidiOutTuning + 8,
    CommandIDs::MidiOutTuning + 9,
    CommandIDs::MidiOutTuning + 10,
    CommandIDs::MidiOutTuning + 11,
    CommandIDs::MidiOutTuning + 12,
    CommandIDs::MidiOutTuning + 13,
    CommandIDs::MidiOutTuning + 14,
    CommandIDs::MidiOutTuning + 15,
    CommandIDs::MidiOutTuning + 16,
    CommandIDs::MidiOutDrumTrack,
    CommandIDs::MidiOutPitchBend,
    CommandIDs::MidiOutInstruments,
    CommandIDs::MidiOutFileSettings,

    // Midi In Port
    CommandIDs::MidiInOpen + 0,
    CommandIDs::MidiInOpen + 1,
    CommandIDs::MidiInOpen + 2,
    CommandIDs::MidiInOpen + 3,
    CommandIDs::MidiInOpen + 4,
    CommandIDs::MidiInOpen + 5,
    CommandIDs::MidiInOpen + 6,
    CommandIDs::MidiInOpen + 7,
    CommandIDs::MidiInOpen + 8,
    CommandIDs::MidiInOpen + 9,
    CommandIDs::MidiInOpen + 10,
    CommandIDs::MidiInOpen + 11,
    CommandIDs::MidiInOpen + 12,
    CommandIDs::MidiInOpen + 13,
    CommandIDs::MidiInOpen + 14,
    CommandIDs::MidiInOpen + 15,
    CommandIDs::MidiInTrace,
    CommandIDs::MidiInChannelFilter + 0,
    CommandIDs::MidiInChannelFilter + 1,
    CommandIDs::MidiInChannelFilter + 2,
    CommandIDs::MidiInChannelFilter + 3,
    CommandIDs::MidiInChannelFilter + 4,
    CommandIDs::MidiInChannelFilter + 5,
    CommandIDs::MidiInChannelFilter + 6,
    CommandIDs::MidiInChannelFilter + 7,
    CommandIDs::MidiInChannelFilter + 8,
    CommandIDs::MidiInChannelFilter + 9,
    CommandIDs::MidiInChannelFilter + 10,
    CommandIDs::MidiInChannelFilter + 11,
    CommandIDs::MidiInChannelFilter + 12,
    CommandIDs::MidiInChannelFilter + 13,
    CommandIDs::MidiInChannelFilter + 14,
    CommandIDs::MidiInChannelFilter + 15,
    CommandIDs::MidiInChannelFilter + 16, // All
    CommandIDs::MidiInOpcodeFilter + 0,
    CommandIDs::MidiInOpcodeFilter + 1,
    CommandIDs::MidiInOpcodeFilter + 2,
    CommandIDs::MidiInOpcodeFilter + 3,
    CommandIDs::MidiInOpcodeFilter + 4,
    CommandIDs::MidiInOpcodeFilter + 5,
    CommandIDs::MidiInOpcodeFilter + 6,
    CommandIDs::MidiInOpcodeFilter + 7, // All
    CommandIDs::MidiInImportFile,

    // Audio
    CommandIDs::AudioOpenFilePlayer,
    CommandIDs::MidiFilePlayer,
    CommandIDs::MidiPlotPlayer,
    CommandIDs::AudioSettings,

    CommandIDs::SndLibSrate + 0,
    CommandIDs::SndLibSrate + 1,
    CommandIDs::SndLibSrate + 2,
    CommandIDs::SndLibSrate + 3,
    CommandIDs::SndLibChannels + 1,
    CommandIDs::SndLibChannels + 2,
    CommandIDs::SndLibAutoPlay,
    CommandIDs::SndLibInsDialog,

    CommandIDs::CsoundPrefWriteAfter,
    CommandIDs::CsoundPrefPlayAfter,
    CommandIDs::CsoundExportScore,
    CommandIDs::CsoundClearScore,
    CommandIDs::CsoundOpenSettings,

#ifdef WITHFOMUS
    CommandIDs::FomusNewScore,
    CommandIDs::FomusRenameScore,
    CommandIDs::FomusDeleteScore,
    CommandIDs::FomusClearScore,
    CommandIDs::FomusSaveScore,
    CommandIDs::FomusSelectScore + 0,
    CommandIDs::FomusSelectScore + 1,
    CommandIDs::FomusSelectScore + 2,
    CommandIDs::FomusSelectScore + 3,
    CommandIDs::FomusSelectScore + 4,
    CommandIDs::FomusSelectScore + 5,
    CommandIDs::FomusSelectScore + 6,
    CommandIDs::FomusSelectScore + 7,
    CommandIDs::FomusLoadScore,
    CommandIDs::FomusRunScore,    
    CommandIDs::FomusSettings,
    CommandIDs::FomusDocumentation,
    CommandIDs::FomusRunCurr,
#endif

    CommandIDs::PlotterNew,
    CommandIDs::PlotterOpen,
    CommandIDs::PlotterOpenMidiFile,

    // Window Menu
    CommandIDs::WindowSelect + 0,  // 0==Select Console
    CommandIDs::WindowSelect + 1,
    CommandIDs::WindowSelect + 2,
    CommandIDs::WindowSelect + 3,
    CommandIDs::WindowSelect + 4,
    CommandIDs::WindowSelect + 5,
    CommandIDs::WindowSelect + 6,
    CommandIDs::WindowSelect + 7,
    // Help Menu
    CommandIDs::HelpSymbolLookup,
    CommandIDs::HelpManual + 0,
    CommandIDs::HelpManual + 1,
    CommandIDs::HelpManual + 2,
    CommandIDs::HelpManual + 3,
    CommandIDs::HelpManual + 4,
    CommandIDs::HelpManual + 5,
    CommandIDs::HelpManual + 6,
    CommandIDs::HelpManual + 7,

    CommandIDs::HelpExample + 0,
    CommandIDs::HelpExample + 1,
    CommandIDs::HelpExample + 2,
    CommandIDs::HelpExample + 3,
    CommandIDs::HelpExample + 4,
    CommandIDs::HelpExample + 5,
    CommandIDs::HelpExample + 6,
    CommandIDs::HelpExample + 7,
    CommandIDs::HelpExample + 8,
    CommandIDs::HelpExample + 9,
    CommandIDs::HelpExample + 10,
    CommandIDs::HelpExample + 11,
    CommandIDs::HelpExample + 12,
    CommandIDs::HelpExample + 13,
    CommandIDs::HelpExample + 14,
    CommandIDs::HelpExample + 15,
    CommandIDs::HelpExample + 16,
    CommandIDs::HelpExample + 17,
    CommandIDs::HelpExample + 18,
    CommandIDs::HelpExample + 19,
    CommandIDs::HelpExample + 20,
    CommandIDs::HelpExample + 21,
    CommandIDs::HelpExample + 22,
    CommandIDs::HelpExample + 23,
    CommandIDs::HelpExample + 24,
    CommandIDs::HelpExample + 25,
    CommandIDs::HelpExample + 26,
    CommandIDs::HelpExample + 27,
    CommandIDs::HelpExample + 28,
    CommandIDs::HelpExample + 29,
    CommandIDs::HelpExample + 30,
    CommandIDs::HelpExample + 31,

    CommandIDs::HelpTutorial + 0,
    CommandIDs::HelpTutorial + 1,
    CommandIDs::HelpTutorial + 2,
    CommandIDs::HelpTutorial + 3,
    CommandIDs::HelpTutorial + 4,
    CommandIDs::HelpTutorial + 5,
    CommandIDs::HelpTutorial + 6,
    CommandIDs::HelpTutorial + 7,

    CommandIDs::HelpWebSite + 0,
    CommandIDs::HelpWebSite + 1,
    CommandIDs::HelpWebSite + 2,
    CommandIDs::HelpWebSite + 3,
    CommandIDs::HelpWebSite + 4,
    CommandIDs::HelpWebSite + 5,
    CommandIDs::HelpWebSite + 6,
    CommandIDs::HelpWebSite + 7,
  };
  commands.addArray(ids, sizeof(ids) / sizeof(CommandID));
}

void Grace::getCommandInfo(const CommandID id, ApplicationCommandInfo& info)
{
  int comm = CommandIDs::getCommand(id);
  int data = CommandIDs::getCommandData(id);
  Preferences* pref=Preferences::getInstance();

  bool ismac=SysInfo::isMac();
  int ctrl=ModifierKeys::ctrlModifier;
  int meta=ModifierKeys::altModifier;
  int comk=ModifierKeys::commandModifier;

  //Set default values for the menu flags.
  info.setActive(true);
  info.setTicked(false);

  switch (comm)
    {
    case CommandIDs::AppQuit:
      info.shortName=T("Quit");
      info.addDefaultKeypress('Q', comk);
      break;
    case CommandIDs::PrefsOpenRecent:
      {
	File f=pref->recentlyOpened.getFile(data);
	if (f==File::nonexistent)
	  info.shortName=T("<Unknown File>");
	else
	  info.shortName=f.getFileName();
      }
      break;
    case CommandIDs::PrefsClearOpenRecent:
      info.shortName=T("Clear Menu");
      break;
    case CommandIDs::PrefsLoadRecent:
      {
	File f=pref->recentlyLoaded.getFile(data);
	if (f==File::nonexistent)
	  info.shortName=T("<Unknown File>");
	else
	  info.shortName=f.getFileName();
      }
      break;
    case CommandIDs::PrefsClearLoadRecent:
      info.shortName=T("Clear Menu");
      break;
      //
      // Lisp Commands
      //
    case CommandIDs::LispStart:
      if (SysInfo::isGraceCL() && 
	  CommonLisp::getInstance()->isLispRunning())
	info.shortName=T("Stop Lisp");
      else 
	info.shortName=T("Start Lisp");
      info.setActive(SysInfo::isGraceCL() && 
		     CommonLisp::getInstance()->isLispStartable());
      break;
    case CommandIDs::LispConfigure:
      info.shortName=T("Configure Lisp...");
      info.setActive(SysInfo::isGraceCL());
      break;
    case CommandIDs::LispLoadFile:
      info.shortName=T("Load File...");
      info.setActive(!SysInfo::isGraceCL() || 
		     CommonLisp::getInstance()->isLispRunning());
      break;
    case CommandIDs::LispCompileFile:
      info.shortName=T("Compile File...");
      info.setActive(SysInfo::isGraceCL() && 
		     CommonLisp::getInstance()->isLispRunning());
      break;
    case CommandIDs::PrefsSetInitFile:
      info.shortName=T("Set Init File...");
      break;
    case CommandIDs::PrefsClearInitFile:
      info.shortName=T("Clear Init File");
      info.setActive(pref->getStringProp(T("LispInitFile"))!=NULL);
      break;
            
      //
      // Midi Output
      //

    case CommandIDs::MidiOutOpen:
      {
	StringArray devices = MidiOutput::getDevices();
	if (data<devices.size())
	  info.shortName=devices[data];
	else
	  info.shortName=T("<Unknown MIDI Device>");
	info.setTicked(MidiOutPort::getInstance()->isOpen(data));
      }
      break;
    case CommandIDs::MidiOutTest:
      info.shortName=T("Test Output");
      info.setActive(MidiOutPort::getInstance()->isOpen());
      info.addDefaultKeypress('T', comk);
      break;
    case CommandIDs::MidiOutHush:
      info.shortName=T("Hush");
      info.setActive(MidiOutPort::getInstance()->isOpen());
      break;
    case CommandIDs::MidiOutTuning:
      {
	MidiOutPort* port=MidiOutPort::getInstance();
	info.shortName=port->getTuningName(data);
	info.setActive(port->isOpen());
	info.setTicked(port->isTuning(data));
      }
      break;
    case CommandIDs::MidiOutDrumTrack:
      info.shortName=T("Avoid Drum Track");
      break;
    case CommandIDs::MidiOutPitchBend:
      info.shortName=T("Pitch Bend Size");
      break;
    case CommandIDs::MidiOutInstruments:
      info.shortName=T("Instruments...");
      info.setActive(MidiOutPort::getInstance()->isOpen());
      break;
    case CommandIDs::MidiOutFileSettings:
      info.shortName=T("Midifile Settings...");
      break;
      //
      // Midi Input
      //
    case CommandIDs::MidiInOpen:
      {
	StringArray devices = MidiInput::getDevices();
	if (data<devices.size())
	  info.shortName=devices[data];
	else
	  info.shortName=T("<Unknown MIDI Device>");
	info.setTicked(MidiInPort::getInstance()->isOpen(data));
      }
      break;
    case CommandIDs::MidiInTrace:
      info.shortName=T("Trace Device Input");
      info.setActive(MidiInPort::getInstance()->isOpen());
      info.setTicked(MidiInPort::getInstance()->isTracing());
      break;
     case CommandIDs::MidiInChannelFilter:
       {
	 MidiInPort* p=MidiInPort::getInstance();
	 if (data==16)
	   {
	     info.shortName=T("All");
	     if (p->getChannelMask()==MidiInPort::AllChannels)
	       info.setTicked(true);
	   }
	 else
	   {
	     info.shortName= String(data);
	     if ((p->getChannelMask()!=MidiInPort::AllChannels) &&
		 p->isChannelActive(data))
	       info.setTicked(true);
	   }
       }
      break;
     case CommandIDs::MidiInOpcodeFilter:
       {
	 MidiInPort* p=MidiInPort::getInstance();
	 if (data==7)
	   {
	     info.shortName=T("All");
	     if (p->getOpcodeMask()==MidiInPort::AllOpcodes)
	       info.setTicked(true);
	   }
	 else
	   {
	     info.shortName=MidiNode::indexToString(data, true);
	     if ((p->getOpcodeMask()!=MidiInPort::AllOpcodes) &&
		 p->isOpcodeActive(data))
	       info.setTicked(true);
	   }
       }
      break;
    case CommandIDs::MidiInImportFile:
      info.shortName=T("Import Midifile...");
      break;
      
    // SndLib
    case CommandIDs::SndLibSrate:
      info.shortName=SrateIDs::toString(data);
      info.setTicked(SrateIDs::toSrate(data) ==
		     pref->getIntProp(T("SndLibSrate"), 44100));
      break;
    case CommandIDs::SndLibChannels:
      info.shortName=String(data);
      info.setTicked(data==pref->getIntProp(T("SndLibChannels"), 1));
      break;
    case CommandIDs::SndLibAutoPlay:
      info.shortName=T("Auto Play");
      info.setTicked(pref->getBoolProp(T("SndLibAutoPlay"), true));
      break;
    case CommandIDs::SndLibInsDialog:
      info.shortName=T("Instruments...");
      break;
      //
      // Csound Commands
      //
    case CommandIDs::CsoundPrefWriteAfter:
      info.shortName=T("Write Scorefiles");
      info.setTicked(Csound::getInstance()->getWriteAfter());
      break;
    case CommandIDs::CsoundPrefPlayAfter:
      info.shortName=T("Play Scorefiles");
      info.setTicked(Csound::getInstance()->getPlayAfter());
      // can't play unless you first write!
      info.setActive(Csound::getInstance()->getWriteAfter());
      break;
    case CommandIDs::CsoundExportScore:
      info.shortName=T("Export Score...");
      info.setActive(!Csound::getInstance()->isScoreEmpty());
      break;
    case CommandIDs::CsoundClearScore:
      info.shortName=T("Clear Score");
      info.setActive(!Csound::getInstance()->isScoreEmpty());
      break;
    case CommandIDs::CsoundOpenSettings:
      info.shortName=T("Settings...");
      break;
      //
      // Fomus Commands
      //
#ifdef WITHFOMUS
    case CommandIDs::FomusNewScore:
      info.shortName=T("New Score...");
      break;
    case CommandIDs::FomusRenameScore:
      info.shortName=T("Rename Score...");
      break;
    case CommandIDs::FomusDeleteScore:
      info.shortName=T("Delete Score");      
      info.setActive(Fomus::getInstance()->numScores()>1);
      break;
    case CommandIDs::FomusClearScore:
      info.shortName=T("Clear Score");      
      break;      
    case CommandIDs::FomusSaveScore:
      info.shortName=T("Save Score...");      
      break;      
    case CommandIDs::FomusSelectScore:
      if (data<Fomus::getInstance()->numScores())
	{
	  info.shortName=Fomus::getInstance()->getScoreName(data);
	  info.setTicked(Fomus::getInstance()->isScoreActive(data));
	}
      else
	{
	  info.shortName=T("<Undefined Score>");
	  info.setActive(false);
	}
      break;
    case CommandIDs::FomusLoadScore:
      info.shortName=T("Load Score...");
      break;
    case CommandIDs::FomusRunScore:
      info.shortName=T("Run FOMUS");
      break;
    case CommandIDs::FomusSettings:
      info.shortName=T("Settings...");
      break;
    case CommandIDs::FomusDocumentation:
      info.shortName=T("Documentation...");
      break;
    case CommandIDs::FomusRunCurr:
      info.shortName=T("Run FOMUS");
      break;
#endif

      //
      // Plot Settings
      //

    case CommandIDs::PlotterNew:
      info.shortName=T("New Plot");
      break;

    case CommandIDs::PlotterOpen:
      info.shortName=T("Open Plot...");
      break;

    case CommandIDs::PlotterOpenMidiFile:
      info.shortName=T("Open Midi Plot...");
      break;

      //
      // Audio Settings
      //
    case CommandIDs::AudioOpenFilePlayer:
      info.shortName=T("Play Audio File...");
      break;
    case CommandIDs::MidiFilePlayer:
      info.shortName=T("Play Midi File...");
      info.setActive(false);
      break;
    case CommandIDs::MidiPlotPlayer:
      info.shortName=T("Play Plot...");
      info.setActive(WindowTypes::isWindowType
		     (TopLevelWindow::getActiveTopLevelWindow(),
		      WindowTypes::PlotWindow)
		     && MidiOutPort::getInstance()->isOpen()
		     );
      break;

    case CommandIDs::AudioSettings:
      info.shortName=T("Audio Settings...");
      break;
      /** WINDOW COMMANDS **/
    case CommandIDs::WindowSelect:
      {
	int n=TopLevelWindow::getNumTopLevelWindows();
	int digit=48+data+1;
	if (data<n)
	  info.shortName=
	    TopLevelWindow::getTopLevelWindow(data)->getName();
	else
	  info.shortName=T("<Unknown Window>");
	info.addDefaultKeypress(digit, comk);
      }
      break;
      /** HELP COMMANDS **/
    case CommandIDs::HelpSymbolLookup:
      info.shortName=T("Symbol Help");
      break;
    case CommandIDs::HelpManual:
    case CommandIDs::HelpExample:
    case CommandIDs::HelpTutorial:
    case CommandIDs::HelpWebSite:
      if (data<Help::getInstance()->getHelpSize(id))
	info.shortName=Help::getInstance()->getHelpName(id);
      else
	info.shortName=T("<Unknown Help>");
      break;
    default:
      //      std::cout << "Grace commands: missing info for " << 
      //	CommandIDs::toString(id, true).toUTF8() << "\n";
      break;
    }
}

bool Grace::perform(const ApplicationCommandTarget::InvocationInfo& info)
{
  int comm = CommandIDs::getCommand(info.commandID);
  int data = CommandIDs::getCommandData(info.commandID);
  Preferences* pref=Preferences::getInstance();
  switch (comm)
    {
    case CommandIDs::AppQuit:
      ((ConsoleWindow *)Console::getInstance()->getTopLevelComponent())->
	closeButtonPressed();
      break;

      //
      // Lisp Commands

    case CommandIDs::LispStart:
      if (CommonLisp::getInstance()->isLispRunning())
	CommonLisp::getInstance()->stopLisp();	
      else
	CommonLisp::getInstance()->startLisp();
      break;

    case CommandIDs::LispConfigure:
      CommonLisp::getInstance()->showConfigureLispWindow();
      break;

    case CommandIDs::LispLoadFile:
      if (SysInfo::isGraceCL())
	CommonLisp::getInstance()->load(File::nonexistent,true);
      else
	Scheme::getInstance()->load(File::nonexistent,true);	
      break;
    case CommandIDs::PrefsLoadRecent:
      Scheme::getInstance()->load(pref->recentlyLoaded.getFile(data), true);
      break;
    case CommandIDs::PrefsSetInitFile:
      {
	FileChooser choose
	  (T("Select lisp file to load at startup."),
	   File::getCurrentWorkingDirectory());
	if (choose.browseForFileToOpen())
	  {
	    String path=choose.getResult().getFullPathName();
	    pref->setStringProp(T("LispInitFile"), path);
	  }
      }
      break;
    case CommandIDs::PrefsClearInitFile:
      pref->setStringProp(T("LispInitFile"), String::empty);
      break;
      //
      // Midi Out Port
      //
    case CommandIDs::MidiOutOpen:
      MidiOutPort::getInstance()->open(data);
      break;
    case CommandIDs::MidiOutTest:
      MidiOutPort::getInstance()->testOutput();
      break;
    case CommandIDs::MidiOutHush:
      Scheme::getInstance()->stop(-1);
      //      MidiOutPort::getInstance()->clear();
      break;
    case CommandIDs::MidiOutTuning:
      MidiOutPort::getInstance()->setTuning(data);
      break;
    case CommandIDs::MidiOutInstruments:
     MidiOutPort::getInstance()->openInstrumentsDialog();
     break;
    case CommandIDs::MidiOutFileSettings:
      MidiOutPort::getInstance()->openFileSettingsDialog();
      break;
     //
     // Midi In Port
     //
    case CommandIDs::MidiInOpen:
      MidiInPort::getInstance()->open(data);
      break;
    case CommandIDs::MidiInTrace:
      MidiInPort::getInstance()->toggleTracing();
      break;
    case CommandIDs::MidiInChannelFilter:
      {
	MidiInPort* p=MidiInPort::getInstance();
	if (data==16)
	  if (p->getChannelMask()==MidiInPort::AllChannels)
	    p->setChannelMask(0);
	  else
	    p->setChannelMask(MidiInPort::AllChannels);
	else
	  if (p->getChannelMask()==MidiInPort::AllChannels)
	    p->setChannelMask(1<<data);
	  else
	    p->toggleChannelActive(data);
      }
      break;
    case CommandIDs::MidiInOpcodeFilter:
      {
	MidiInPort* p=MidiInPort::getInstance();
	if (data==7)
	  if (p->getOpcodeMask()==MidiInPort::AllOpcodes)
	    p->setOpcodeMask(0);
	  else
	    p->setOpcodeMask(MidiInPort::AllOpcodes);
	else
	  if (p->getOpcodeMask()==MidiInPort::AllOpcodes)
	    p->setOpcodeMask(1<<data);
	  else
	    p->toggleOpcodeActive(data);
      } 
      break;

    case CommandIDs::MidiInImportFile:
      MidiInPort::getInstance()->openImportMidifileDialog();
      break;

      /** AUDIO COMMANDS **/
    case CommandIDs::AudioOpenFilePlayer:
      AudioManager::getInstance()->openAudioFilePlayer();
      break;
    case CommandIDs::MidiFilePlayer:
      break;
    case CommandIDs::MidiPlotPlayer:
      {
	TopLevelWindow* w=TopLevelWindow::getActiveTopLevelWindow();
	if (WindowTypes::isWindowType(w,WindowTypes::PlotWindow))
	  ((PlotterWindow*)w)->openPlayPlotDialog();
      }
      break;

    case CommandIDs::AudioSettings:
      AudioManager::getInstance()->openAudioSettings();
      break;
#ifdef SNDLIB
    case CommandIDs::SndLibSrate:
      {
	int sr=SrateIDs::toSrate(data);
	String st=T("(begin (set! *clm-srate* ") + 
	  String(sr) + T(") (void))");
	pref->setIntProp(T("SndLibSrate"), sr);
	Scheme::getInstance()->eval(st);
      }
      break;
    case CommandIDs::SndLibChannels:
      {
	int ch=data;
	String st=T("(begin (set! *clm-channels* ") + 
	  String(ch) + T(") (void))");
	Preferences::getInstance()->setIntProp(T("SndLibChannels"), ch);
	Scheme::getInstance()->eval(st);
      }
      break;
    case CommandIDs::SndLibAutoPlay:
      {
	bool ap=!Preferences::getInstance()->
	  getBoolProp(T("SndLibAutoPlay"));
	String b=((ap) ? T("#t") : T("#f"));
	String st=T("(begin (set! *clm-play* ") + b + T(") (void))");
	Preferences::getInstance()->setIntProp(T("SndLibAutoPlay"), ap);
	Scheme::getInstance()->eval(st);
      }
      break;
    case CommandIDs::SndLibInsDialog:
      SndLib::getInstance()->openInstrumentBrowser();
      break;
#endif
      //
      // Csound Commands
      //
    case CommandIDs::CsoundPrefWriteAfter:
      Csound::getInstance()->
	setWriteAfter(!Csound::getInstance()->getWriteAfter());
      break;
    case CommandIDs::CsoundPrefPlayAfter:
      Csound::getInstance()->
	setPlayAfter(!Csound::getInstance()->getPlayAfter());
      break;
    case CommandIDs::CsoundExportScore:
      Csound::getInstance()->exportScore();
      break;
    case CommandIDs::CsoundClearScore:
      Csound::getInstance()->clearScore();
      break;
    case CommandIDs::CsoundOpenSettings:
      Csound::getInstance()->openSettings();
      break;

      //
      // Fomus Commands
      //

#ifdef WITHFOMUS
    case CommandIDs::FomusSelectScore:
      Fomus::getInstance()->setScoreActive(data);
      break;
    case CommandIDs::FomusNewScore:
      Fomus::getInstance()->newScore(T(""), false);
      break;
    case CommandIDs::FomusRenameScore:
      Fomus::getInstance()->renameScoreDialog();
      break;
    case CommandIDs::FomusDeleteScore:
      Fomus::getInstance()->deleteScore();
      break;
    case CommandIDs::FomusClearScore:
      Fomus::getInstance()->clearScore();
      break;
    case CommandIDs::FomusSaveScore:
      Fomus::getInstance()->saveScore(T(""), false);
      break;
    case CommandIDs::FomusLoadScore:
      Fomus::getInstance()->loadScoreDialog();
      break;
    case CommandIDs::FomusRunScore:
      Fomus::getInstance()->runScore(false);
      break;
    case CommandIDs::FomusSettings:
      Fomus::getInstance()->settingsWindow();
      break;
    case CommandIDs::FomusDocumentation:
      Fomus::getInstance()->documentationWindow();
      break;
#endif

      //
      // Plotting Commands
      //

    case CommandIDs::PlotterNew:
      new PlotterWindow(NULL);
      break;
    case CommandIDs::PlotterOpen:
    case CommandIDs::PlotterOpenMidiFile:
      PlotterWindow::browseForFileToOpen(comm);
      break;

      //
      // Window Commands
      //

    case CommandIDs::WindowSelect:
      {
	TopLevelWindow* w = TopLevelWindow::getTopLevelWindow(data);
	w->grabKeyboardFocus();
	w->toFront(true);
      }
      break;
    case CommandIDs::PrefsOpenRecent:
      openFile(Preferences::getInstance()->recentlyOpened.getFile(data));
      break;
    case CommandIDs::PrefsClearOpenRecent:
      Preferences::getInstance()->recentlyOpened.clear();
      break;
    case CommandIDs::HelpManual:
    case CommandIDs::HelpExample:
    case CommandIDs::HelpTutorial:
    case CommandIDs::HelpWebSite:
      Help::getInstance()->openHelp(info.commandID);
      break;
    default:
      return false;
    }
  return true;
}

void Grace::openFile(File file)
{
  // File can be null, a directory look in, or file to open
  bool doit=true;
  if (! file.existsAsFile())
    {
      File dir;
      if (file.isDirectory())
	dir=file;
      else
	dir=File::getSpecialLocation(File::userHomeDirectory);
      FileChooser choose (T("Open File"), dir, String::empty, true);
      if (choose.browseForFileToOpen())
	file=choose.getResult();
      else
	doit=false;
    }
  if (doit)
    {
      new TextEditorWindow(file);
      Preferences::getInstance()->recentlyOpened.addFile(file);
    }
}

/*=======================================================================*
                             Console Commands
 *=======================================================================*/

ApplicationCommandTarget* Console::getNextCommandTarget()
{
  //return (Grace *)JUCEApplication::getInstance(); 
  return 0;
}

void Console::getAllCommands(Array<CommandID>& commands)
{
  const CommandID ids[] = 
    {
      CommandIDs::ConsoleNewEditor,
      CommandIDs::ConsoleOpen,
      CommandIDs::ConsoleShowDirectory,
      CommandIDs::ConsoleSetDirectory,  
      CommandIDs::ConsoleFont + 0,
      CommandIDs::ConsoleFont + 1,
      CommandIDs::ConsoleFontSize + 0,
      CommandIDs::ConsoleFontSize + 1,
      CommandIDs::ConsoleFontSize + 2,
      CommandIDs::ConsoleFontSize + 3,
      CommandIDs::ConsoleFontSize + 4,
      CommandIDs::ConsoleFontSize + 5,
      CommandIDs::ConsoleFontSize + 6,
      CommandIDs::ConsoleFontSize + 7,
      CommandIDs::ConsoleFontSize + 8,
      CommandIDs::ConsoleFontSize + 9,
      CommandIDs::ConsoleFontSize + 10,
      CommandIDs::ConsoleFontSize + 11,
      CommandIDs::ConsoleFontSize + 12,
      CommandIDs::ConsoleFontSize + 13,
      CommandIDs::ConsoleFontSize + 14,
      CommandIDs::ConsoleFontSize + 15,
      CommandIDs::ConsoleFontSize + 16,
      CommandIDs::ConsoleFontSize + 17,
      CommandIDs::ConsoleFontSize + 18,
      CommandIDs::ConsoleFontSize + 19,
      CommandIDs::ConsoleFontSize + 20,
      CommandIDs::ConsoleFontSize + 21,
      CommandIDs::ConsoleFontSize + 22,
      CommandIDs::ConsoleFontSize + 23,
      CommandIDs::ConsoleTheme + 0,
      CommandIDs::ConsoleTheme + 1,
      CommandIDs::ConsoleTheme + 2,
      CommandIDs::ConsoleTheme + 3,
      CommandIDs::ConsoleTheme + 4,
      CommandIDs::ConsoleTheme + 5,
      CommandIDs::ConsoleTheme + 6,
      CommandIDs::ConsoleTheme + 7,
      CommandIDs::ConsoleSelectAll,
      CommandIDs::ConsoleCopy,
      CommandIDs::ConsoleClearSelection,
      CommandIDs::ConsoleBeepOnError,
      CommandIDs::ConsoleClearConsole
    };
  commands.addArray(ids, sizeof(ids) / sizeof(CommandID));
}

void Console::getCommandInfo(const CommandID id, 
			     ApplicationCommandInfo& info)
{
  
  int comm = CommandIDs::getCommand(info.commandID);
  int data = CommandIDs::getCommandData(info.commandID);
  bool ismac=SysInfo::isMac();
  int ctrl=ModifierKeys::ctrlModifier;
  int meta=ModifierKeys::altModifier;
  int comk=ModifierKeys::commandModifier;

  Preferences* pref=Preferences::getInstance();
  // Set default values for the menu flags.
  info.setActive(true);
  info.setTicked(false);
  switch (comm)
    {
    case CommandIDs::ConsoleNewEditor:
      info.shortName=T("New Editor");
      info.addDefaultKeypress('N', comk);
      break;
    case CommandIDs::ConsoleOpen:
      info.shortName=T("Open...");
      info.addDefaultKeypress('O', comk);
      break;
    case CommandIDs::ConsoleShowDirectory:
      info.shortName=T("Show Working Directory");
      break;
    case CommandIDs::ConsoleSetDirectory:
      info.shortName=T("Set Working Directory...");
      break;
    case CommandIDs::ConsoleTheme:
      info.shortName=T("<Unknown Theme");
      break;
    case CommandIDs::ConsoleFont:
      if (data==0)
	info.shortName=Font::getDefaultMonospacedFontName();
      else 
	info.shortName=T("<Unknown Font>");
      break;
    case CommandIDs::ConsoleFontSize:
      {
	int fontsize=data+9;
	info.shortName=String(fontsize);
	info.setTicked(getFontSize()==fontsize);
      }   
      break;

    case CommandIDs::ConsoleSelectAll:
      info.shortName=T("Select All");
      break;
    case CommandIDs::ConsoleCopy:
      info.shortName=T("Copy");
      info.setActive(buffer->getHighlightedRegionLength()>0);
      break;
    case CommandIDs::ConsoleClearSelection:
      info.shortName=T("Clear Selection");
      info.setActive(buffer->getHighlightedRegionLength()>0);
      break;
    case CommandIDs::ConsoleBeepOnError:
      info.shortName=T("Beep On Error");
      info.setTicked(getBeepOnError());
      break;
    case CommandIDs::ConsoleClearConsole:
      info.shortName=T("Clear Console");
      break;

    default:
      //      std::cout << "Console commands: missing info for " << 
      //	CommandIDs::toString(id, true).toUTF8() << "\n";
      break;
    }
}

bool Console::perform(const ApplicationCommandTarget::InvocationInfo& info)
{
  //  std::cout << "perform (Console)\n";
  int comm = CommandIDs::getCommand(info.commandID);
  int data = CommandIDs::getCommandData(info.commandID);
  Grace* app=(Grace *)JUCEApplication::getInstance();
  Preferences* pref=Preferences::getInstance();
  
  switch (comm)
    {
    case CommandIDs::ConsoleNewEditor:
      new TextEditorWindow();
      break;
    case CommandIDs::ConsoleOpen:
      app->openFile(File::nonexistent);
      break;
    case CommandIDs::ConsoleSetDirectory:
      app->chooseWorkingDirectory();
      break;
    case CommandIDs::ConsoleShowDirectory:
      app->showWorkingDirectory();
      break;
    case CommandIDs::ConsoleFontSize:
      {
	int fontsize=9+data;
	setFontSize(fontsize);
	pref->setIntProp(T("ConsoleFontSize"), fontsize); 
      }
      break;
    case CommandIDs::ConsoleCopy:
      buffer->copy();
      break;
    case CommandIDs::ConsoleSelectAll:
      buffer->setHighlightedRegion(0,1000000);
      break;
    case CommandIDs::ConsoleBeepOnError:
      setBeepOnError(!getBeepOnError());
      break;
    case CommandIDs::ConsoleClearSelection:
      buffer->setHighlightedRegion(buffer->getCaretPosition(),0);
      buffer->setCaretPosition(1000000);
      break;
    case CommandIDs::ConsoleClearConsole:
      buffer->clear();
      break;
    default:
      app->invoke(info, false);
      break;
    }
  return true;
}

/*=======================================================================*
                             TextBuffer Commands
 *=======================================================================*/

/*
               COMMAND KEY CONFLICTS ON WINDOWS/LINUX
KEYPRESS             STANDARD                  EMACS
"ctrl + 1"           CommandIDs::WindowSelect  CommandIDs::Empty
"ctrl + Q"           CommandIDs::AppQuit       CommandIDs::Empty
"ctrl + T"         CommandIDs::MidiTestOutput  CommandIDs::Empty
"ctrl + A"       CommandIDs::EditorSelectAll   CommandIDs::EmacsGotoBOL
"ctrl + B"           CommandIDs::Empty         CommandIDs::EmacsCharBackward
"ctrl + C"           CommandIDs::EditorCopy    CommandIDs::Empty
"ctrl + D"           CommandIDs::Empty         CommandIDs::EmacsKillChar
"ctrl + E"           CommandIDs::Empty,        CommandIDs::EmacsGotoEOL
"ctrl + F"           CommandIDs::EditorFind    CommandIDs::EmacsCharForward
"ctrl + K"           CommandIDs::Empty         CommandIDs::EmacsKillLine
"ctrl + N"           CommandIDs::EditorNew     CommandIDs::EmacsLineForward
"ctrl + O"           CommandIDs::Empty         CommandIDs::EmacsOpenLine
"ctrl + P"           CommandIDs::EditorPrint   CommandIDs::EmacsLineBackward
"ctrl + S"           CommandIDs::EditorSave    CommandIDs::Empty
"ctrl + V"           CommandIDs::EditorPaste   CommandIDs::EmacsPageForward
"ctrl + W"           CommandIDs::EditorClose   CommandIDs::EmacsKillRegion
"ctrl + X"           CommandIDs::EditorCut     CommandIDs::EmacsControlX
"ctrl + Y"           CommandIDs::Empty         CommandIDs::EmacsYank
"ctrl + Z"           CommandIDs::EditorUndo    CommandIDs::Empty
"ctrl + shift + Z"   CommandIDs::EditorRedo    CommandIDs::Empty
"option + B"         CommandIDs::Empty         CommandIDs::EmacsWordBackward
"option + C"         CommandIDs::Empty         CommandIDs::EmacsUppercase
"option + D"         CommandIDs::Empty         CommandIDs::EmacsKillWord
"option + F"         CommandIDs::Empty         CommandIDs::EmacsWordForward
"option + L"         CommandIDs::Empty         CommandIDs::EmacsLowercase
"option + Q"         CommandIDs::Empty        CommandIDs::EmacsFormatComments
"option + U"         CommandIDs::Empty         CommandIDs::EmacsUppercase
"option + V"         CommandIDs::Empty         CommandIDs::EmacsPageBackward
"option + spacebar"  CommandIDs::Empty         CommandIDs::EmacsKillWhite
"shift + option + ," CommandIDs::Empty         CommandIDs::EmacsGotoBOB
"shift + option + ." CommandIDs::Empty         CommandIDs::EmacsGotoEOB
"ctrl + option + B"  CommandIDs::Empty         CommandIDs::EmacsExprBackward
"ctrl + option + F"  CommandIDs::Empty         CommandIDs::EmacsExprForward
"ctrl + option + K"  CommandIDs::Empty         CommandIDs::EmacsKillExpr
*/

ApplicationCommandTarget* TextBuffer::getNextCommandTarget()
{
  //return (Grace *)JUCEApplication::getInstance();
  return 0;
}

void TextBuffer::getAllCommands(Array<CommandID>& commands)
{
  const CommandID ids[] = 
  {
    // File menu
    CommandIDs::EditorNew,
    CommandIDs::EditorOpen,
    CommandIDs::EditorSave,
    CommandIDs::EditorSaveAs,
    CommandIDs::EditorRevert,
    CommandIDs::EditorShowDirectory,
    CommandIDs::EditorSetDirectory,
    CommandIDs::EditorPrint,
    CommandIDs::EditorClose,
    // Edit menu
    CommandIDs::EditorUndo,
    CommandIDs::EditorRedo,
    CommandIDs::EditorCut,
    CommandIDs::EditorCopy,
    CommandIDs::EditorPaste,
    CommandIDs::EditorSelectAll,
    CommandIDs::EditorFind,
    // Options menu
    CommandIDs::EditorSyntax + TextIDs::Text,
    CommandIDs::EditorSyntax + TextIDs::Lisp,
    CommandIDs::EditorSyntax + TextIDs::Sal,
    CommandIDs::EditorFontSize + 0,
    CommandIDs::EditorFontSize + 1,
    CommandIDs::EditorFontSize + 2,
    CommandIDs::EditorFontSize + 3,
    CommandIDs::EditorFontSize + 4,
    CommandIDs::EditorFontSize + 5,
    CommandIDs::EditorFontSize + 6,
    CommandIDs::EditorFontSize + 7,
    CommandIDs::EditorFontSize + 8,
    CommandIDs::EditorFontSize + 9,
    CommandIDs::EditorFontSize + 10,
    CommandIDs::EditorFontSize + 11,
    CommandIDs::EditorFontSize + 12,
    CommandIDs::EditorFontSize + 13,
    CommandIDs::EditorFontSize + 14,
    CommandIDs::EditorFontSize + 15,
    CommandIDs::EditorFontSize + 16,
    CommandIDs::EditorFontSize + 17,
    CommandIDs::EditorFontSize + 18,
    CommandIDs::EditorFontSize + 19,
    CommandIDs::EditorFontSize + 20,
    CommandIDs::EditorFontSize + 21,
    CommandIDs::EditorFontSize + 22,
    CommandIDs::EditorFontSize + 23,

    CommandIDs::EditorTabWidth + 0,
    CommandIDs::EditorTabWidth + 1,
    CommandIDs::EditorTabWidth + 2,
    CommandIDs::EditorTabWidth + 3,
    CommandIDs::EditorParensMatching,
    CommandIDs::EditorHighlighting,
    CommandIDs::EditorEmacsMode,
    // Eval menu
    CommandIDs::EditorExecute,
    CommandIDs::EditorExpand,
    CommandIDs::EditorIndent,
    CommandIDs::EditorCommentOut,
    CommandIDs::EditorUncommentOut,
    CommandIDs::EditorFormatComments,
    CommandIDs::EditorSymbolHelp,
    // Emacs commands (no menu)
    CommandIDs::EmacsCharForward,
    CommandIDs::EmacsCharBackward,
    CommandIDs::EmacsWordForward,
    CommandIDs::EmacsWordBackward,
    CommandIDs::EmacsExprForward,
    CommandIDs::EmacsExprBackward,
    CommandIDs::EmacsLineForward,
    CommandIDs::EmacsLineBackward,
    CommandIDs::EmacsPageForward,
    CommandIDs::EmacsPageBackward,
    CommandIDs::EmacsGotoEOL,
    CommandIDs::EmacsGotoBOL,
    CommandIDs::EmacsGotoEOB,
    CommandIDs::EmacsGotoBOB,
    CommandIDs::EmacsKillChar,
    CommandIDs::EmacsKillWord,
    CommandIDs::EmacsKillExpr,
    CommandIDs::EmacsKillWhite,
    CommandIDs::EmacsKillLine,
    CommandIDs::EmacsKillRegion,
    CommandIDs::EmacsOpenLine,
    CommandIDs::EmacsYank,
    CommandIDs::EmacsCapitalize,
    CommandIDs::EmacsUppercase,    
    CommandIDs::EmacsLowercase,
    CommandIDs::EmacsFormatComments,
    CommandIDs::EmacsControlX
  };
  commands.addArray(ids, sizeof(ids) / sizeof(CommandID));
}

void TextBuffer::updateEditorCommands(bool emacs)
{
  // remove all commands and then add them back. re-registering them
  // will call getCommandInfo(), which will then cause menu and
  // command manager to refect the new state of the EmacsMode flag...
  Array<CommandID> cmds;
  getAllCommands(cmds);
  for (int i=0; i<cmds.size(); i++)
    manager->removeCommand(cmds.getUnchecked(i));
  manager->registerAllCommandsForTarget(this);
}

const KeyPress getEmacsKeyPress(CommandID id)
{
  int comm = CommandIDs::getCommand(id);
  int data = CommandIDs::getCommandData(id);
  switch (comm)
    {
    case CommandIDs::EmacsCharForward:
      return KeyPress::createFromDescription(T("ctrl + F"));
    case CommandIDs::EmacsCharBackward:
      return KeyPress::createFromDescription(T("ctrl + B"));
    case CommandIDs::EmacsWordForward:
      return KeyPress::createFromDescription(T("option + F"));
    case CommandIDs::EmacsWordBackward:
      return KeyPress::createFromDescription(T("option + B"));
    case CommandIDs::EmacsExprForward:
      return KeyPress::createFromDescription(T("ctrl + option + F"));
    case CommandIDs::EmacsExprBackward:
      return KeyPress::createFromDescription(T("ctrl + option + B"));
    case CommandIDs::EmacsLineForward:
      return KeyPress::createFromDescription(T("ctrl + N"));
    case CommandIDs::EmacsLineBackward:
      return KeyPress::createFromDescription(T("ctrl + P"));
    case CommandIDs::EmacsPageForward:
      return KeyPress::createFromDescription(T("ctrl + V"));
    case CommandIDs::EmacsPageBackward:
      return KeyPress::createFromDescription(T("option + V"));
    case CommandIDs::EmacsGotoEOL:
      return KeyPress::createFromDescription(T("ctrl + E"));
    case CommandIDs::EmacsGotoBOL:
      return KeyPress::createFromDescription(T("ctrl + A"));
    case CommandIDs::EmacsGotoEOB:
      return KeyPress::createFromDescription(T("shift + option + ."));
    case CommandIDs::EmacsGotoBOB:
      return KeyPress::createFromDescription(T("shift + option + ,"));
    case CommandIDs::EmacsKillChar:
      return KeyPress::createFromDescription(T("ctrl + D"));
    case CommandIDs::EmacsKillWord:
      return KeyPress::createFromDescription(T("option + D"));
    case CommandIDs::EmacsKillExpr:
      return KeyPress::createFromDescription(T("ctrl + option + K"));
    case CommandIDs::EmacsKillWhite:
      return KeyPress::createFromDescription(T("option + spacebar"));
    case CommandIDs::EmacsKillLine:
      return KeyPress::createFromDescription(T("ctrl + K"));
    case CommandIDs::EmacsKillRegion:
      return KeyPress::createFromDescription(T("ctrl + W"));
    case CommandIDs::EmacsOpenLine:
      return KeyPress::createFromDescription(T("ctrl + O"));
    case CommandIDs::EmacsYank:
      return KeyPress::createFromDescription(T("ctrl + Y"));
    case CommandIDs::EmacsCapitalize:
      return KeyPress::createFromDescription(T("option + C"));
    case CommandIDs::EmacsUppercase:
      return KeyPress::createFromDescription(T("option + U"));
    case CommandIDs::EmacsLowercase:
      return KeyPress::createFromDescription(T("option + L"));
    case CommandIDs::EmacsFormatComments:
      return KeyPress::createFromDescription(T("option + Q"));
    case CommandIDs::EmacsControlX:
      return KeyPress::createFromDescription(T("ctrl + X"));
    default:
      return KeyPress(); // return invalid keypress
    }
}
 
void TextBuffer::getCommandInfo(const CommandID id, 
				 ApplicationCommandInfo& info)
{
  int comm = CommandIDs::getCommand(info.commandID);
  int data = CommandIDs::getCommandData(info.commandID);
  bool ismac=SysInfo::isMac();
  bool emacs=testFlag(EditFlags::EmacsMode);
  int ctrl=ModifierKeys::ctrlModifier;
  int meta=ModifierKeys::altModifier;
  int comk=ModifierKeys::commandModifier;
  Preferences* pref=Preferences::getInstance();

  info.setActive(true);
  info.setTicked(false);

  switch (comm)
    {
    case CommandIDs::EditorNew:
      info.shortName=T("New");
      if (ismac || !emacs)
	info.addDefaultKeypress('N', comk);
      break;
    case CommandIDs::EditorOpen:
      info.shortName=T("Open...");
      if (ismac || !emacs)
	info.addDefaultKeypress('O', comk);
      break;
    case CommandIDs::EditorSave:
      info.shortName=T("Save");
      if (ismac || !emacs)
	info.addDefaultKeypress('S', comk);
      info.setActive(testFlag(EditFlags::NeedsSave));
      break;
    case CommandIDs::EditorSaveAs:
      info.shortName=T("Save As...");
      break;
    case CommandIDs::EditorRevert:
      info.shortName=T("Revert");
      info.setActive((getFile() != File::nonexistent) && 
		     testFlag(EditFlags::NeedsSave));
      break;
    case CommandIDs::EditorShowDirectory:
      info.shortName=T("Show Working Directory");
      break;
    case CommandIDs::EditorSetDirectory:
      info.shortName=T("Set Working Directory...");
      break;
    case CommandIDs::EditorPrint:
      info.shortName=T("Print...");
      if (ismac || !emacs)
	info.addDefaultKeypress('P', comk);
      info.setActive(false);
      break;
    case CommandIDs::EditorClose:
      info.shortName=T("Close");
      if (ismac || !emacs)
	info.addDefaultKeypress('W', comk);
      break;
    case CommandIDs::EditorUndo:
      info.shortName=T("Undo");
      if (ismac || !emacs)
	info.addDefaultKeypress('Z', comk);
      //info.setActive(false); // DISABLED DUE TO HILIGHTING
      break;
    case CommandIDs::EditorRedo:
      info.shortName=T("Redo");
      if (ismac || !emacs)
	info.addDefaultKeypress('Z', comk | ModifierKeys::shiftModifier);
      //info.setActive(false); // DISABLED DUE TO HILIGHTING
      break;
    case CommandIDs::EditorCut:
      info.shortName=T("Cut");
      if (ismac || !emacs)
	info.addDefaultKeypress('X', comk);
      info.setActive(getHighlightedRegionLength()>0);
      break;
    case CommandIDs::EditorCopy:
      info.shortName=T("Copy");
      if (ismac || !emacs)
	info.addDefaultKeypress('C', comk);
      info.setActive(getHighlightedRegionLength()>0);
      break;
    case CommandIDs::EditorPaste:
      info.shortName=T("Paste");
      if (ismac || !emacs)
	info.addDefaultKeypress('V', comk);
      info.setActive(SystemClipboard::getTextFromClipboard().length()>0);
      break;
    case CommandIDs::EditorSelectAll:
      info.shortName=T("Select All");
      if (ismac || !emacs)
	info.addDefaultKeypress('A', comk);
      info.setActive(!isEmpty());
      break;
    case CommandIDs::EditorFind:
      info.shortName=T("Find...");
      if (ismac || !emacs)
	info.addDefaultKeypress('F', comk);
      info.setActive(!isEmpty());
      break;
    case CommandIDs::EditorIndent:
      info.shortName=T("Indent");
      info.addDefaultKeypress('\t', 0);
      break;
    case CommandIDs::EditorCommentOut:
      info.shortName=T("Comment Out Region");
      info.setActive(getHighlightedRegionLength()>0);
      break;
    case CommandIDs::EditorUncommentOut:
      info.shortName=T("Uncomment Region");
      info.setActive(getHighlightedRegionLength()>0);
      break;
    case CommandIDs::EditorFormatComments:
      info.shortName=T("Format Comments");
      info.setActive(getHighlightedRegionLength()>0);
      break;


      //
      // Options Menu
      //
    case CommandIDs::EditorSyntax:
      info.shortName=TextIDs::toString(data);
      info.setTicked(isSyntax(data));
      break;
    case CommandIDs::EditorFontSize:
      {
	int fontsize=data+9;
	info.shortName=String(fontsize);
	info.setTicked(getFontSize()==fontsize);
      }
      break;
    case CommandIDs::EditorTabWidth:
      {
	int tabw=2+(data*2); // 2, 4, 6, 8
	info.shortName=String(tabw);
	info.setTicked(tabw==syntax->getTabWidth());
      }
      break;
    case CommandIDs::EditorParensMatching:
      info.shortName=T("Parens Matching");
      info.setTicked(!testFlag(EditFlags::MatchingOff));
      break;
    case CommandIDs::EditorHighlighting:
      info.shortName=T("Highlighting");
      info.setTicked(!testFlag(EditFlags::HiliteOff));
      break;
    case CommandIDs::EditorEmacsMode:
      info.shortName=T("Emacs Mode");
      info.setTicked(testFlag(EditFlags::EmacsMode));
      break;
      //
      // Eval Menu
      //
    case CommandIDs::EditorExecute:
      info.shortName=T("Execute");
      info.addDefaultKeypress(KeyPress::returnKey, comk);
      break;
    case CommandIDs::EditorExpand:
      info.shortName=T("Expand");
      info.setActive(false);
      break;
      // Help Item
    case CommandIDs::EditorSymbolHelp:
      info.shortName=T("Lookup Symbol");
      // 'H' is not possible on mac, Finder claims it for Hide
      if (ismac || !emacs)
	info.addDefaultKeypress('D', comk);
      break;
      //
      // Emacs Keyboard Commands
      //
    case CommandIDs::EmacsCharForward:
    case CommandIDs::EmacsCharBackward:
    case CommandIDs::EmacsWordForward:
    case CommandIDs::EmacsWordBackward:
    case CommandIDs::EmacsExprForward:
    case CommandIDs::EmacsExprBackward:
    case CommandIDs::EmacsLineForward:
    case CommandIDs::EmacsLineBackward:
    case CommandIDs::EmacsPageForward:
    case CommandIDs::EmacsPageBackward:
    case CommandIDs::EmacsGotoEOL:
    case CommandIDs::EmacsGotoBOL:
    case CommandIDs::EmacsGotoEOB:
    case CommandIDs::EmacsGotoBOB:
    case CommandIDs::EmacsKillChar:
    case CommandIDs::EmacsKillWord:
    case CommandIDs::EmacsKillExpr:
    case CommandIDs::EmacsKillWhite:
    case CommandIDs::EmacsKillLine:
    case CommandIDs::EmacsKillRegion:
    case CommandIDs::EmacsOpenLine:
    case CommandIDs::EmacsYank:
    case CommandIDs::EmacsCapitalize:
    case CommandIDs::EmacsUppercase:
    case CommandIDs::EmacsLowercase:
    case CommandIDs::EmacsFormatComments:
    case CommandIDs::EmacsControlX:
      {
	KeyPress kp=getEmacsKeyPress(id);
	info.shortName=T("Emacs ") + kp.getTextDescription();
	info.setActive(emacs);
	if (emacs)
	  info.defaultKeypresses.add(kp);
      }
      break;
    default:
      //      std::cout << "TextBuffer commands: missing info for " << 
      //	CommandIDs::toString(id, true).toUTF8() << "\n";
      break;
    }
}

bool TextBuffer::perform(const ApplicationCommandTarget::InvocationInfo&
			 info)
{
  int comm = CommandIDs::getCommand(info.commandID);
  int data = CommandIDs::getCommandData(info.commandID);
  Preferences* pref=Preferences::getInstance();
  Grace* app=(Grace *)JUCEApplication::getInstance();
  // command invocation cancels a running parens match
  if (isMatching()) 
    stopMatching();
  switch (comm)
    {
      //
      // File Menu
      //
    case CommandIDs::EditorNew:
      new TextEditorWindow();
      break;
    case CommandIDs::EditorOpen:
      app->openFile(File::nonexistent);
      break;
    case CommandIDs::EditorSave:
      saveFile();
      break;
    case CommandIDs::EditorSaveAs:
      saveFileAs();
      break;
    case CommandIDs::EditorRevert:
      revertFile();
      break;
    case CommandIDs::EditorSetDirectory:
      app->chooseWorkingDirectory();
      break;
    case CommandIDs::EditorShowDirectory:
      app->showWorkingDirectory();
      break;
    case CommandIDs::EditorPrint:
      std::cout << "EditorPrint\n";
      break;
    case CommandIDs::EditorClose:
      ((TextEditorWindow *)getTopLevelComponent())->closeButtonPressed();
      return true; // dont colorize!
      break;
      //
      // Edit Menu
      //
    case CommandIDs::EditorUndo:
      doUndoRedo(false);
      setFlag(EditFlags::NeedsSave);
      break;
    case CommandIDs::EditorRedo:
      doUndoRedo(true);
      setFlag(EditFlags::NeedsSave);
      break;
    case CommandIDs::EditorCut:
      cut();
      break;
    case CommandIDs::EditorCopy:
      copy();
      break;
    case CommandIDs::EditorPaste:
      paste();
      break;
    case CommandIDs::EditorSelectAll:
      selectAll();
      break;
    case CommandIDs::EditorFind:
      TextEditorWindow::openFindAndReplaceDialog();
      break;
      //
      // Options Menu
      //
    case CommandIDs::EditorSyntax:
      setSyntax(data);
      pref->setIntProp(T("EditorSyntax"), data);
      updateWindowTitle();
      break;
    case CommandIDs::EditorFontSize:
      {
	int fontsize=9+data;
	setFontSize(fontsize);
	pref->setIntProp(T("EditorFontSize"), fontsize); 
      }
      break;
   case CommandIDs::EditorTabWidth:
      {
	int tabw=2+(data*2); // 2, 4, 6, 8
	syntax->setTabWidth(tabw);
      }
      break;
    case CommandIDs::EditorHighlighting:
      toggleFlag(EditFlags::HiliteOff);
      break;
    case CommandIDs::EditorParensMatching:
      toggleFlag(EditFlags::MatchingOff);
      break;
    case CommandIDs::EditorEmacsMode:
      {
	bool b=toggleFlag(EditFlags::EmacsMode);
	pref->setBoolProp(T("EditorEmacsMode"), b); 
	updateEditorCommands(b);
      }
      break;
      //
      // Eval Menu
      //
    case CommandIDs::EditorExecute:
      eval();
      break;
    case CommandIDs::FomusRunCurr:
      eval();
      break;
    case CommandIDs::EditorExpand:
      eval(true);
      break;
    case CommandIDs::EditorIndent:
      syntacticIndent();
      break;
    case CommandIDs::EditorFormatComments:
      std::cout << "EditorFormatComments\n";
      break;
    case CommandIDs::EditorSymbolHelp:
      lookupHelpAtPoint();
      break;
      //
      //Emacs Keyboard Commands
      //
    case CommandIDs::EmacsCharForward:
     // Emacs: C-xC-f is OpenFile, C-f is forward char
      if (prev==CommandIDs::EmacsControlX)
	app->openFile(File::nonexistent);
      else
	forwardChar();
      break;
    case CommandIDs::EmacsCharBackward:
      backwardChar();
      break;
    case CommandIDs::EmacsWordForward:
      forwardWord();
      break;
    case CommandIDs::EmacsWordBackward:
      backwardWord();
      break;
    case CommandIDs::EmacsExprForward:
      forwardExpr();
      break;
    case CommandIDs::EmacsExprBackward:
      backwardExpr();
      break;
    case CommandIDs::EmacsLineForward:
      forwardLine();
      break;
    case CommandIDs::EmacsLineBackward:
      backwardLine();
      break;
    case CommandIDs::EmacsPageForward:
      forwardPage();
      break;
    case CommandIDs::EmacsPageBackward:
      backwardPage();
      break;
    case CommandIDs::EmacsGotoEOL:
      // Emacs: C-xC-e is eval, C-e is eol
      if (prev==CommandIDs::EmacsControlX)
	eval();
      else
	gotoEOL();
      break;
    case CommandIDs::EmacsGotoBOL:
      gotoBOL();
      break;
    case CommandIDs::EmacsGotoEOB:
      gotoEOB();
      break;
    case CommandIDs::EmacsGotoBOB:
      gotoBOB();
      break;
    case CommandIDs::EmacsKillChar:
      killChar();
      break;
    case CommandIDs::EmacsKillWord:
      killWord();
      break;
    case CommandIDs::EmacsKillExpr:
      killExpr();
      break;
    case CommandIDs::EmacsKillWhite:
      killWhite();
      break;
    case CommandIDs::EmacsKillLine:
      killLine();
      break;
    case CommandIDs::EmacsKillRegion:
      if (getHighlightedRegionLength()>0)
	killRegion();
      break;
    case CommandIDs::EmacsOpenLine:
      openLine();
      break;
    case CommandIDs::EmacsYank:
      paste();
      break;
    case CommandIDs::EmacsLowercase:
      changeCase(0);
      break;
    case CommandIDs::EmacsUppercase:
      changeCase(1);
      break;
    case CommandIDs::EmacsCapitalize:
      changeCase(2);
      break;
    case CommandIDs::EmacsFormatComments:
      std::cout << "EmacsFormatCommments\n";
      break;
    case CommandIDs::EmacsControlX:
      //std::cout << "EmacsControlX\n";
      break;
      // 
      // try Global App Commands (???)
      //
    default:
      app->invoke(info, false);
      break;
    }
  // a few commands need to know what the previous comman was
  prev=comm; 
  colorizeAfterChange(comm);
  return true;
}

/*=======================================================================*
                     Application Command Manager            
 *=======================================================================*/

juce_ImplementSingleton(CommandManager)

CommandManager::CommandManager()
{
}

CommandManager::~CommandManager()
{
}

