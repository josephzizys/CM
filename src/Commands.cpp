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
#include "Console.h"
#include "Help.h"
#include "Main.h"
#include "Preferences.h"
#include "Audio.h"
#include "Csound.h"
#include "PlotWindow.h"
#include "CodeEditor.h"
#include "SndLib.h"
#ifdef WITH_FOMUS
#include "Fomus.h"
#endif
#ifdef WITH_LIBLO
#include "Osc.h"
#endif
#include "Cells.h"
#ifdef GRACECL
#include "CommonLisp.h"
#endif

/*=======================================================================*
                     Application wide commands             
 *=======================================================================*/

ApplicationCommandTarget* Grace::getNextCommandTarget()
{
  //return 0;
  return Grace::getInstance();
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
    CommandIDs::MidiOutRecording,
    CommandIDs::MidiOutRecordingDelete,
    CommandIDs::MidiOutRecordingPlay,
    CommandIDs::MidiOutRecordingSave,
    CommandIDs::MidiOutRecordingImport,

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
    CommandIDs::MidiInThrough,

    // Audio
    CommandIDs::AudioFilePlayer,
    CommandIDs::MidiFilePlayer,
    CommandIDs::MidiPlotPlayer,
    CommandIDs::AudioSettings,
    CommandIDs::AudioHush,

    CommandIDs::SndLibSrate + 0,
    CommandIDs::SndLibSrate + 1,
    CommandIDs::SndLibSrate + 2,
    CommandIDs::SndLibSrate + 3,

    CommandIDs::SndLibChannels + 0,
    CommandIDs::SndLibChannels + 1,
    CommandIDs::SndLibChannels + 2,
    CommandIDs::SndLibChannels + 3,

    CommandIDs::SndLibAudioFormat + 0,
    CommandIDs::SndLibAudioFormat + 1,
    CommandIDs::SndLibAudioFormat + 2,
    CommandIDs::SndLibAudioFormat + 3,

    CommandIDs::SndLibAutoPlay,
    CommandIDs::SndLibInsDialog,
    CommandIDs::SndLibInsRestore,

    CommandIDs::CsoundPrefWriteAfter,
    CommandIDs::CsoundPrefPlayAfter,
    CommandIDs::CsoundExportScore,
    CommandIDs::CsoundClearScore,
    CommandIDs::CsoundOpenSettings,

#ifdef WITH_FOMUS
    CommandIDs::FomusNewScore,
    CommandIDs::FomusRenameScore,
    CommandIDs::FomusDeleteScore,
    CommandIDs::FomusClearScore,
    CommandIDs::FomusSaveScore,
    CommandIDs::FomusSaveScoreAs,
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

#ifdef WITH_LIBLO
    CommandIDs::OscOpen,
    CommandIDs::OscTraceInput,
    CommandIDs::OscTraceOutput,
    CommandIDs::OscShowStatus,
    //    CommandIDs::OscClearHook,
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

    CommandIDs::HelpGUI + 0,
    CommandIDs::HelpGUI + 1,
    CommandIDs::HelpGUI + 2,
    CommandIDs::HelpGUI + 3,
    CommandIDs::HelpGUI + 4,
    CommandIDs::HelpGUI + 5,
    CommandIDs::HelpGUI + 6,
    CommandIDs::HelpGUI + 7,

    CommandIDs::HelpSalExample + 0,
    CommandIDs::HelpSalExample + 1,
    CommandIDs::HelpSalExample + 2,
    CommandIDs::HelpSalExample + 3,
    CommandIDs::HelpSalExample + 4,
    CommandIDs::HelpSalExample + 5,
    CommandIDs::HelpSalExample + 6,
    CommandIDs::HelpSalExample + 7,
    CommandIDs::HelpSalExample + 8,
    CommandIDs::HelpSalExample + 9,
    CommandIDs::HelpSalExample + 10,
    CommandIDs::HelpSalExample + 11,
    CommandIDs::HelpSalExample + 12,
    CommandIDs::HelpSalExample + 13,
    CommandIDs::HelpSalExample + 14,
    CommandIDs::HelpSalExample + 15,
    CommandIDs::HelpSalExample + 16,
    CommandIDs::HelpSalExample + 17,
    CommandIDs::HelpSalExample + 18,
    CommandIDs::HelpSalExample + 19,
    CommandIDs::HelpSalExample + 20,
    CommandIDs::HelpSalExample + 21,
    CommandIDs::HelpSalExample + 22,
    CommandIDs::HelpSalExample + 23,
    CommandIDs::HelpSalExample + 24,
    CommandIDs::HelpSalExample + 25,
    CommandIDs::HelpSalExample + 26,
    CommandIDs::HelpSalExample + 27,
    CommandIDs::HelpSalExample + 28,
    CommandIDs::HelpSalExample + 29,
    CommandIDs::HelpSalExample + 30,
    CommandIDs::HelpSalExample + 31,

    CommandIDs::HelpSchemeExample + 0,
    CommandIDs::HelpSchemeExample + 1,
    CommandIDs::HelpSchemeExample + 2,
    CommandIDs::HelpSchemeExample + 3,
    CommandIDs::HelpSchemeExample + 4,
    CommandIDs::HelpSchemeExample + 5,
    CommandIDs::HelpSchemeExample + 6,
    CommandIDs::HelpSchemeExample + 7,
    CommandIDs::HelpSchemeExample + 8,
    CommandIDs::HelpSchemeExample + 9,
    CommandIDs::HelpSchemeExample + 10,
    CommandIDs::HelpSchemeExample + 11,
    CommandIDs::HelpSchemeExample + 12,
    CommandIDs::HelpSchemeExample + 13,
    CommandIDs::HelpSchemeExample + 14,
    CommandIDs::HelpSchemeExample + 15,
    CommandIDs::HelpSchemeExample + 16,
    CommandIDs::HelpSchemeExample + 17,
    CommandIDs::HelpSchemeExample + 18,
    CommandIDs::HelpSchemeExample + 19,
    CommandIDs::HelpSchemeExample + 20,
    CommandIDs::HelpSchemeExample + 21,
    CommandIDs::HelpSchemeExample + 22,
    CommandIDs::HelpSchemeExample + 23,
    CommandIDs::HelpSchemeExample + 24,
    CommandIDs::HelpSchemeExample + 25,
    CommandIDs::HelpSchemeExample + 26,
    CommandIDs::HelpSchemeExample + 27,
    CommandIDs::HelpSchemeExample + 28,
    CommandIDs::HelpSchemeExample + 29,
    CommandIDs::HelpSchemeExample + 30,
    CommandIDs::HelpSchemeExample + 31,

    CommandIDs::HelpSalTutorial + 0,
    CommandIDs::HelpSalTutorial + 1,
    CommandIDs::HelpSalTutorial + 2,
    CommandIDs::HelpSalTutorial + 3,
    CommandIDs::HelpSalTutorial + 4,
    CommandIDs::HelpSalTutorial + 5,
    CommandIDs::HelpSalTutorial + 6,
    CommandIDs::HelpSalTutorial + 7,
    CommandIDs::HelpSalTutorial + 8,
    CommandIDs::HelpSalTutorial + 9,
    CommandIDs::HelpSalTutorial + 10,
    CommandIDs::HelpSalTutorial + 11,
    CommandIDs::HelpSalTutorial + 12,
    CommandIDs::HelpSalTutorial + 13,
    CommandIDs::HelpSalTutorial + 14,
    CommandIDs::HelpSalTutorial + 15,

    CommandIDs::HelpSchemeTutorial + 0,
    CommandIDs::HelpSchemeTutorial + 1,
    CommandIDs::HelpSchemeTutorial + 2,
    CommandIDs::HelpSchemeTutorial + 3,
    CommandIDs::HelpSchemeTutorial + 4,
    CommandIDs::HelpSchemeTutorial + 5,
    CommandIDs::HelpSchemeTutorial + 6,
    CommandIDs::HelpSchemeTutorial + 7,
    CommandIDs::HelpSchemeTutorial + 8,
    CommandIDs::HelpSchemeTutorial + 9,
    CommandIDs::HelpSchemeTutorial + 10,
    CommandIDs::HelpSchemeTutorial + 11,
    CommandIDs::HelpSchemeTutorial + 12,
    CommandIDs::HelpSchemeTutorial + 13,
    CommandIDs::HelpSchemeTutorial + 14,
    CommandIDs::HelpSchemeTutorial + 15,

    CommandIDs::HelpWebSite + 0,
    CommandIDs::HelpWebSite + 1,
    CommandIDs::HelpWebSite + 2,
    CommandIDs::HelpWebSite + 3,
    CommandIDs::HelpWebSite + 4,
    CommandIDs::HelpWebSite + 5,
    CommandIDs::HelpWebSite + 6,
    CommandIDs::HelpWebSite + 7,

    CommandIDs::HelpSalTutorialsRestore,  
    CommandIDs::HelpSchemeTutorialsRestore,
    CommandIDs::HelpSalExamplesRestore,
    CommandIDs::HelpSchemeExamplesRestore

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
#ifdef GRACECL
      if (CommonLisp::getInstance()->isLispRunning())
	info.shortName=T("Stop Lisp");
      else 
	info.shortName=T("Start Lisp");
      info.setActive(CommonLisp::getInstance()->isLispStartable());
#else
      info.shortName=T("Start Lisp");
      info.setActive(false);
#endif
      break;
    case CommandIDs::LispConfigure:
      info.shortName=T("Configure Lisp...");
      info.setActive(SysInfo::isGraceCL());
      break;
    case CommandIDs::LispLoadFile:
      info.shortName=T("Load File...");
#ifdef GRACECL
      info.setActive(CommonLisp::getInstance()->isLispRunning());
#else
      info.setActive(true);
#endif
      break;
    case CommandIDs::LispCompileFile:
      info.shortName=T("Compile File...");
#ifdef GRACECL
      info.setActive(CommonLisp::getInstance()->isLispRunning());
#else
      info.setActive(false);
#endif
      break;

    case CommandIDs::PrefsSetInitFile:
      info.shortName=T("Set Init File...");
      break;
    case CommandIDs::PrefsClearInitFile:
      info.shortName=T("Clear Init File");
      info.setActive(pref->getStringProp(T("LispInitFile"))!=String::empty);
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
	  info.shortName=T("No MIDI Device");
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
      info.shortName=T("MIDI Instruments...");
      info.setActive(MidiOutPort::getInstance()->isOpen());
      break;
    case CommandIDs::MidiOutFileSettings:
      info.shortName=T("Midifile Settings...");
      break;
    case CommandIDs::MidiOutRecording:
      if (MidiOutPort::getInstance()->isRecordMode(CaptureModes::RecordMidiOut) )
        info.shortName=T("Stop Recording");
      else if (MidiOutPort::getInstance()->isSequenceData() )
        info.shortName=T("Overdub Recording");
      else 
        info.shortName=T("Start Recording");
      break;
    case CommandIDs::MidiOutRecordingDelete:
      info.shortName=T("Delete");
      info.setActive(MidiOutPort::getInstance()->isRecordingAvailable());
      break;
    case CommandIDs::MidiOutRecordingPlay:
      info.shortName=T("Play");
      info.setActive(MidiOutPort::getInstance()->isRecordingAvailable());
      break;
    case CommandIDs::MidiOutRecordingSave:
      info.shortName=T("Save...");
      info.setActive(MidiOutPort::getInstance()->isRecordingAvailable());
      break;
    case CommandIDs::MidiOutRecordingImport:
      info.shortName=T("Import...");
      info.setActive(MidiOutPort::getInstance()->isRecordingAvailable());
      break;
      //    case CommandIDs::MidiOutRecordingSaveAs:
      //      info.shortName=T("Save As...");
      //      info.setActive(MidiOutPort::getInstance()->isRecordingAvailable());
      //      break;
      //    case CommandIDs::MidiOutRecordingConfigure:
      //      info.shortName=T("Configure...");
      //      info.setActive(MidiOutPort::getInstance()->isRecordingAvailable());
      //      break;

      //
      // Midi Input
      //
    case CommandIDs::MidiInOpen:
      {
	StringArray devices = MidiInput::getDevices();
	if (data<devices.size())
	  info.shortName=devices[data];
	else
	  info.shortName=T("No MIDI Device");
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

    case CommandIDs::MidiInThrough:
      info.shortName=T("Copy To Output");
      info.setActive(MidiInPort::getInstance()->isOpen() &&
                     MidiOutPort::getInstance()->isOpen() );
      info.setTicked(MidiInPort::getInstance()->isThroughActive());
      break;
      
    // SndLib

    case CommandIDs::SndLibSrate:
      info.shortName=SrateIDs::toString(data);
      info.setTicked(SrateIDs::toSrate(data)==SndLib::getInstance()->getSrate());
      break;
    case CommandIDs::SndLibChannels:
      info.shortName=ChannelIDs::toString(data);
      info.setTicked(ChannelIDs::toChannels(data)==SndLib::getInstance()->getChannels());
      break;
    case CommandIDs::SndLibAudioFormat:
      {
        String name=AudioFormatIDs::toString(data);
        info.shortName=name;
        info.setTicked(name==SndLib::getInstance()->getAudioFormat());
      }
      break;
    case CommandIDs::SndLibAutoPlay:
      info.shortName=T("Auto Play");
      info.setTicked(pref->getBoolProp(T("SndLibAutoPlay"), true));
      break;
    case CommandIDs::SndLibInsDialog:
      info.addDefaultKeypress('I', comk);
      info.shortName=T("Instrument Browser..");
      break;
    case CommandIDs::SndLibInsRestore:
      //info.shortName=T("Restore To Directory...");
      info.shortName=T("Export Instruments...");
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
#ifdef WITH_FOMUS
    case CommandIDs::FomusNewScore:
      info.shortName=T("New Score...");
      break;
    case CommandIDs::FomusRenameScore:
      info.shortName=T("Rename Score...");
      break;
    case CommandIDs::FomusDeleteScore:
      info.shortName=T("Delete Score");      
      if (fomus_exists) info.setActive(Fomus::getInstance()->numScores()>1);
      break;
    case CommandIDs::FomusClearScore:
      info.shortName=T("Clear Score");      
      break;      
    case CommandIDs::FomusSaveScore:
      info.shortName=T("Save Score...");      
      break;      
    case CommandIDs::FomusSaveScoreAs:
      info.shortName=T("Save Score As...");      
      info.setActive((fomus_exists && data<Fomus::getInstance()->numScores()));
      break;      
    case CommandIDs::FomusSelectScore:
      if (fomus_exists && data<Fomus::getInstance()->numScores())
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

      // OSC

#ifdef WITH_LIBLO
    case CommandIDs::OscOpen:
      if (OscPort::getInstance()->isOpen)
        info.shortName=T("Close Connection");
      else
        info.shortName=T("Open Connection...");
      break;
    case CommandIDs::OscTraceInput:
      info.shortName=T("Trace Input");
      info.setTicked(OscPort::getInstance()->traceInput);
      //if (!OscPort::getInstance()->isOpen)
      //  info.setActive(false);
      break;
    case CommandIDs::OscTraceOutput:
      info.shortName=T("Trace Output");
      info.setTicked(OscPort::getInstance()->traceOutput);
      //if (!OscPort::getInstance()->isOpen)
      //  info.setActive(false);
      break;
    case CommandIDs::OscShowStatus:
      info.shortName=T("Show Status");
      break;
      //    case CommandIDs::OscClearHook:
      //      info.shortName=T("Clear Hook");
      //      if (!OscPort::getInstance()->isHookActive)
      //        info.setActive(false);
      //      break;

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
    case CommandIDs::AudioFilePlayer:
      info.shortName=T("Play Audio File...");
      break;
    case CommandIDs::MidiFilePlayer:
      info.shortName=T("Play Midi File...");
      info.setActive(true);
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

    case CommandIDs::AudioHush:
      {
      info.shortName=T("Hush");
      //      const KeyPress kp=KeyPress::createFromDescription(T("command + ."));
      //      info.defaultKeypresses.add(kp);
      info.addDefaultKeypress('K', comk);
      }
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
	  {
	    info.shortName=T("<Unknown Window>");
	    info.setActive(false);
	  }
	info.addDefaultKeypress(digit, comk);
      }
      break;

      /** HELP COMMANDS **/

    case CommandIDs::HelpSymbolLookup:
      info.shortName=T("Symbol Help");
      break;
    case CommandIDs::HelpManual:
      info.shortName=T("Help Manual ")+String(data);
      break;
    case CommandIDs::HelpGUI:
      info.shortName=T("Help GUI ")+String(data);
      break;
    case CommandIDs::HelpWebSite:
      info.shortName=T("Web Site ")+String(data);
      break;

    case CommandIDs::HelpSalExample:
      info.shortName=T("Sal Example ")+String(data);
      break;
    case CommandIDs::HelpSchemeExample:
       info.shortName=T("Scheme Example ")+String(data);
      break;
    case CommandIDs::HelpSalTutorial:
      info.shortName=T("Sal Tutorial ")+String(data);
      break;
    case CommandIDs::HelpSchemeTutorial:
      info.shortName=T("Scheme Tutorial ")+String(data);
      break;

    case CommandIDs::HelpSalTutorialsRestore:
    case CommandIDs::HelpSchemeTutorialsRestore:
      info.shortName=T("Export Tutorials...");
      break;
    case CommandIDs::HelpSalExamplesRestore:
    case CommandIDs::HelpSchemeExamplesRestore:
      info.shortName=T("Export Examples...");
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
  //std::cout << "In Grace::perform -> comm=" << comm << " data=" << data << "\n";
  switch (comm)
    {
    case CommandIDs::AppQuit:
      //((ConsoleWindow *)Console::getInstance()->getTopLevelComponent())->closeButtonPressed();
      JUCEApplication::getInstance()->systemRequestedQuit();
      break;

      //
      // Lisp Commands

    case CommandIDs::LispStart:
#ifdef GRACECL
      if (CommonLisp::getInstance()->isLispRunning())
	CommonLisp::getInstance()->stopLisp();	
      else
	CommonLisp::getInstance()->startLisp();
#endif
      break;

    case CommandIDs::LispConfigure:
#ifdef GRACECL
      CommonLisp::getInstance()->showConfigureLispWindow();
#endif
      break;

    case CommandIDs::LispLoadFile:
#ifdef GRACECL
	CommonLisp::getInstance()->load(File::nonexistent,true);
#else
	SchemeThread::getInstance()->load(File::nonexistent,true);	
#endif
      break;
    case CommandIDs::PrefsLoadRecent:
      SchemeThread::getInstance()->load(pref->recentlyLoaded.getFile(data), true);
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
      SchemeThread::getInstance()->stop(-1);
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
    case CommandIDs::MidiOutRecording:
      // toggle output recording On or Off
      if (MidiOutPort::getInstance()->isRecordMode(CaptureModes::RecordMidiOut) )
        MidiOutPort::getInstance()->setRecordMode(CaptureModes::Off);
      else
        MidiOutPort::getInstance()->setRecordMode(CaptureModes::RecordMidiOut);
      break;
    case CommandIDs::MidiOutRecordingDelete:
      MidiOutPort::getInstance()->clearSequence();
      break;
    case CommandIDs::MidiOutRecordingPlay:
      MidiOutPort::getInstance()->playSequence();
      break;
    case CommandIDs::MidiOutRecordingSave:
      MidiOutPort::getInstance()->saveSequence(true);
      break;
    case CommandIDs::MidiOutRecordingImport:
      MidiOutPort::getInstance()->openImportRecordingDialog();
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

    case CommandIDs::MidiInThrough:
      MidiInPort::getInstance()->setThroughActive(!MidiInPort::getInstance()->isThroughActive());
      break;

      /** AUDIO COMMANDS **/
    case CommandIDs::AudioFilePlayer:
      AudioManager::getInstance()->openAudioFilePlayer();
      break;
    case CommandIDs::MidiFilePlayer:
      MidiOutPort::getInstance()->openMidiFilePlayer();
      break;
    case CommandIDs::MidiPlotPlayer:
      {
	TopLevelWindow* w=TopLevelWindow::getActiveTopLevelWindow();
	if (WindowTypes::isWindowType(w,WindowTypes::PlotWindow))
	  ((PlotWindow*)w)->openPlayPlotDialog();
      }
      break;

    case CommandIDs::AudioSettings:
      AudioManager::getInstance()->openAudioSettings();
      break;

    case CommandIDs::AudioHush:
      // Stop all scheme processes
      SchemeThread::getInstance()->stop(-1);
      // Flush midi output queue
      MidiOutPort::getInstance()->clear();
      // Stop any sound file playing
      AudioManager::getInstance()->stopAudioPlayback();
      // Interrupt any scheme eval
      SchemeThread::getInstance()->setSchemeInterrupt(true);
      std::cout << "END AUDIO HUSH!\n";
      break;

      //
      // Sndlib Commands
      //

#ifdef WITH_SNDLIB

    case CommandIDs::SndLibSrate:
      SndLib::getInstance()->setSrate(SrateIDs::toSrate(data));
      break;

    case CommandIDs::SndLibChannels:
      SndLib::getInstance()->setChannels(ChannelIDs::toChannels(data));
      break;

    case CommandIDs::SndLibAudioFormat:
      SndLib::getInstance()->setAudioFormat(AudioFormatIDs::toString(data));
      break;

    case CommandIDs::SndLibAutoPlay:
      if (SndLib::getInstance()->getAutoPlay())
        SndLib::getInstance()->setAutoPlay(false);
      else
        SndLib::getInstance()->setAutoPlay(true);
      break;

    case CommandIDs::SndLibInsDialog:
      SndLib::getInstance()->openInstrumentBrowser();
      break;

    case CommandIDs::SndLibInsRestore:
      //SndLib::getInstance()->restoreInstruments();
      SndLib::getInstance()->openInstrumentBrowser(true);
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

#ifdef WITH_FOMUS
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
      Fomus::getInstance()->clearScore(true);
      break;
    case CommandIDs::FomusSaveScore:
      Fomus::getInstance()->saveScore(T(""), false);
      break;
    case CommandIDs::FomusSaveScoreAs:
      Fomus::getInstance()->saveScoreAs(String::empty);
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
    case CommandIDs::FomusRunCurr:
      {
	CodeEditorWindow* w = CodeEditorWindow::getFocusCodeEditor();
	if (w) {
	  CodeBuffer* buf=w->getCodeBuffer();
	  if (buf->isTextType( TextIDs::Fomus))
	    ((FomusSyntax*)buf->syntax)->eval(buf->document,
					      CodeDocument::Position(&buf->document, 0),
					      CodeDocument::Position(&buf->document, std::numeric_limits<int>::max()),
					      false, false);
	}
      }
      break;
#endif

      //
      // OSC Commands
      //

#ifdef WITH_LIBLO

    case CommandIDs::OscOpen:
      if (OscPort::getInstance()->isOpen)
        OscPort::getInstance()->close();
      else
        OscPort::getInstance()->openDialog();
      break;

    case CommandIDs::OscTraceInput:
      OscPort::getInstance()->traceInput = !OscPort::getInstance()->traceInput;
      break;

    case CommandIDs::OscTraceOutput:
      OscPort::getInstance()->traceOutput = !OscPort::getInstance()->traceOutput;
      break;

    case CommandIDs::OscShowStatus:
      OscPort::getInstance()->showStatus();
      break;

      //    case CommandIDs::OscClearHook:
      //      if (OscPort::getInstance()->isHookActive)
      //        SchemeThread::getInstance()->eval(T("(osc:hook #f)"));
      //      break;

#endif

      //
      // Plotting Commands
      //

    case CommandIDs::PlotterNew:
      new PlotWindow(NULL);
      break;
    case CommandIDs::PlotterOpen:
    case CommandIDs::PlotterOpenMidiFile:
      PlotWindow::browseForFileToOpen(comm);
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
      CodeEditorWindow::openFile(Preferences::getInstance()->recentlyOpened.getFile(data));
      break;
    case CommandIDs::PrefsClearOpenRecent:
      Preferences::getInstance()->recentlyOpened.clear();
      break;
    case CommandIDs::HelpManual:
    case CommandIDs::HelpGUI:
    case CommandIDs::HelpSalExample:
    case CommandIDs::HelpSchemeExample:
    case CommandIDs::HelpSalTutorial:
    case CommandIDs::HelpSchemeTutorial:
    case CommandIDs::HelpWebSite:
      Help::getInstance()->openHelp(info.commandID);
      break;
    case CommandIDs::HelpSalTutorialsRestore:
    case CommandIDs::HelpSchemeTutorialsRestore:
    case CommandIDs::HelpSalExamplesRestore:
    case CommandIDs::HelpSchemeExamplesRestore:
      Help::getInstance()->restoreToDirectory(comm);
      break;
    default:
      return false;
    }
  return true;
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
      info.shortName=Console::getInstance()->getThemeName(data);
      info.setTicked(Console::getInstance()->isCurrentTheme(data));
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
      info.setActive(buffer->getHighlightedRegion().getLength()>0);
      break;
    case CommandIDs::ConsoleClearSelection:
      info.shortName=T("Clear Selection");
      info.setActive(buffer->getHighlightedRegion().getLength()>0);
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
  //std::cout << "perform (Console)\n";
  int comm = CommandIDs::getCommand(info.commandID);
  int data = CommandIDs::getCommandData(info.commandID);
  Grace* app=(Grace *)JUCEApplication::getInstance();
  Preferences* pref=Preferences::getInstance();
  
  switch (comm)
    {
    case CommandIDs::ConsoleNewEditor:
      CodeEditorWindow::newFile();
      break;
    case CommandIDs::ConsoleOpen:
      //app->openFile(File::nonexistent);
      CodeEditorWindow::openFile();
      break;
    case CommandIDs::ConsoleSetDirectory:
      app->chooseWorkingDirectory();
      break;
    case CommandIDs::ConsoleShowDirectory:
      app->showWorkingDirectory();
      break;
    case CommandIDs::ConsoleTheme:      
      Console::getInstance()->setTheme(data);
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
      buffer->setHighlightedRegion(Range<int>(0,1000000));
      break;
    case CommandIDs::ConsoleBeepOnError:
      setBeepOnError(!getBeepOnError());
      break;
    case CommandIDs::ConsoleClearSelection:
      //      buffer->setHighlightedRegion(buffer->getCaretPosition(),0);
      buffer->setHighlightedRegion(Range<int>::emptyRange(buffer->getCaretPosition()));
      buffer->setCaretPosition(1000000);
      break;
    case CommandIDs::ConsoleClearConsole:
      buffer->clear();
      SchemeThread::getInstance()->printBanner();
      break;
    default:
      app->invoke(info, false);
      break;
    }
  return true;
}

juce_ImplementSingleton(CommandManager)

CommandManager::CommandManager()
{
  setFirstCommandTarget(Grace::getInstance());
}

CommandManager::~CommandManager()
{
}

