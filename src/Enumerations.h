/*=======================================================================*
  Copyright (C) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#ifndef ENUMERATIONS_H
#define ENUMERATIONS_H

#include "juce.h"

class SysInfo
{
 public: 

  /*======================================================================*
                                Versioning
   *======================================================================*/

  static const int CM_VERSION = 330;
  static const int GRACE_VERSION = CM_VERSION;

  /*======================================================================*
                                Version Info
   *======================================================================*/

  static const String getCMVersion()
  {
    return T("Common Music ") + getVersionString(CM_VERSION);
  }
  static const String getGraceVersion()
  {
    return getVersionString(GRACE_VERSION);
  }

  static const String getApplicationName()
  {
#ifdef CM
    return String(T("cm"));
#else
#ifdef GRACECL
    return String(T("GraceCL"));
#else
    return String(T("Grace"));
#endif
#endif
  }

  static const String getCMLogo()
  {
    String crlf=String("\n");
    String vers=getCMVersion();
    String logo = String::empty;
    logo << String(" /\\\\\\") << crlf
	 << String("---\\\\\\---------") << crlf
	 << String("----\\\\\\--------") << crlf
	 << String("----/\\\\\\-------") << String(" ") << vers << crlf
	 << String("---/--\\\\\\------") << crlf
	 << String("--/----\\\\\\-----") << crlf
	 << String(" /      \\\\\\/");
    return logo;
  }

  static const String getCopyright(const String pers)
  {
    int year=Time::getCurrentTime().getYear();
    return String("(c) ") + String(year) + T(" ") + pers;
  }

  static const String getVersionString(int vers)
  {
    int a, b, c;
    a=vers / 100;
    vers=vers % 100;
    b=vers / 10;
    c=vers % 10;
    return String(a) + T(".") + String(b) + T(".") + String(c);
  }

  /*======================================================================*
                                 OS Info
   *======================================================================*/

 static bool isWindows()
  {
#ifdef JUCE_WIN32
    return true;
#else
    return false;
#endif
  }
  
  static bool isMac()
  {
#ifdef JUCE_MAC
    return true;
#else
    return false;
#endif
  }
  
  static bool isLinux()
  {
#ifdef JUCE_LINUX
    return true;
#else
    return false;
#endif
  }

  /*======================================================================*
                                 Target Info
   *======================================================================*/

  static bool isGraceCL()
  {
#ifdef GRACECL
    return true;
#else
    return false;
#endif
  }

};

/*
 * TextIds enumerate text syntaxes, the first three are supported by a
 * code syntax in the Editor
 */

typedef int TextID;

class TextIDs
{
 public:
  static const TextID Empty=0;
  static const TextID Text=1;
  static const TextID Lisp=2;
  static const TextID Sal=3;
  static const TextID Fomus=4;
  static const TextID Csound=5;
  static const TextID Xml=6;
  static const String toString(TextID id)
  {
    switch (id)
      {
      case Text:
	return T("Text");
      case Lisp:
	return T("Lisp");
      case Sal:
	return T("Sal");
      case Fomus:
	return T("Fomus");
      case Csound:
	return T("Csound");
      case Xml:
	return T("Xml");
      default:
	return T("Empty");
      }
  }
};

/** HiliteIDs enumerate logical categories for syntax highlighting **/

typedef int HiliteID;

class HiliteIDs
{
 public:
  static const int NUMHILITES=8;
  static const HiliteID None=0;
  static const HiliteID String=1;
  static const HiliteID Comment=2;
  static const HiliteID Hilite4=3;  
  static const HiliteID Hilite5=4;  
  static const HiliteID Hilite6=5;  
  static const HiliteID Hilite7=6;  
  static const HiliteID Hilite8=7;  
};

/* 
 * ExportIDs describe ways to decode data into text. Upper nibble
 * holds a TextID, lower nibble holds the format of the output
 * (e.g. lists of data, send expressions, score statements, etc)
 */

typedef int ExportID;

class ExportIDs
{
 private:
  static const int SHIFT=4;
  static const int UMASK=0xf0;
  static const int LMASK=0x0f;
 public:
  
  static ExportID toExportID(TextID textid, int format)
  {
    return (ExportID)(((textid & LMASK) << SHIFT) + (format & LMASK));
  }

  static const TextID getTextID(ExportID f)
  {
    return (TextID)((f & UMASK) >> SHIFT);
  }

  static const int getFormat(ExportID f)
  {
    return (f & LMASK);
  }

  static const int Empty = 0;
  static const int Data = 1;  // event data exported as lists
  static const int Send = 2;  // event data exported as send exprs
  static const int Score = 3; // score file format

  // export destinaions
  static const int ToFile = 1;
  static const int ToConsole = 2;
  static const int ToEditor = 3;
  static const int ToClipboard= 4;

  static const ExportID SalData = (TextIDs::Sal << SHIFT) + Data;
  static const ExportID SalSend = (TextIDs::Sal << SHIFT) + Send;
  static const ExportID LispData = (TextIDs::Lisp << SHIFT) + Data;
  static const ExportID LispSend = (TextIDs::Lisp << SHIFT) + Send;
  static const ExportID CsoundScore = (TextIDs::Csound << SHIFT) + Score;
  static const ExportID XmlData = (TextIDs::Xml << SHIFT) + Data ;
};

class CaptureModes
{
 public:
  static const int Empty=0;
  static const int Off=0;
  static const int CaptureModeOff=0;
  static const int RecordMidiOut=1;
  static const int RecordMidiIn=2;
  static const int CaptureModeScore=3;
};

class MidiFlags
{
 public:
  static const int Off=0x8;
  static const int On=0x9;
  static const int Touch=0xA;
  static const int Ctrl=0xB;
  static const int Prog=0xC;
  static const int Press=0xD;
  static const int Bend=0xE;
  static const int Meta=0xF;
  static const int MaxChannelOpcode = Bend;
  static const int AllChannelsMask = 0xFFFF;
  static const int AllOpcodesMask = 0xFF;

  static const int OffMask=1<<(Off-Off);
  static const int OnMask=1<<(On-Off);
  static const int TouchMask=1<<(Touch-Off);
  static const int CtrlMask=1<<(Ctrl-Off);
  static const int ProgMask=1<<(Prog-Off);
  static const int PressMask=1<<(Press-Off);
  static const int BendMask=1<<(Bend-Off);
  static const int MetaMask=1<<(Meta-Off);
};

class ScoreTypes
{
 public:
  static const int Any=-1;
  static const int Empty=0;
  static const int Midi=1;
  static const int SndLib=2;
  static const int Csound=3;
  static const int Fomus=4;
};

class WindowTypes
{
 public: 
  static const int Empty = 0;
  static const int Console = 1;
  static const int TextEditor = 2;
  static const int PlotWindow = 3;
  static const bool isWindowType(TopLevelWindow* w, int typ)
  {
    if (w!=NULL)
      return (w->getComponentPropertyInt(T("WindowType"), false) == typ);
    else 
      return false;
  }
  static const void setWindowType(TopLevelWindow* w, int typ)
  {
    w->setComponentProperty(T("WindowType"), typ);
  }
};

class Prefs
{
 public:
  static const int Empty = 0;
  static const int ConsoleFontSize = 1;
  static const int EmacsMode = 2;
  static const int EditorFontSize = 3;
  static const int EditorFont = 4;
  static const int MidiOutDevice = 5;
  static const int MidiInDevice = 6;
};

/** CommandIDs enumerate all the menu and keyboard commands. Each ID
    consists of a command type or'ed with a command number. The lowest
    8 bits are left free to encode data into the handle **/

#define COMID(a, b) \
  (((a) << 16) + ((b) << 8))

class CommandIDs
{
 public:

  static const CommandID toID(int cmd, int data)
  {
    return (cmd + data);
  }

  static const CommandID toID(int typ, int num, int data)
  {
    return ((typ << 16) + (num << 8) + data);
  }

  static const CommandID getCommand(CommandID id)
  {
    // return command id with data stripped off
    return (id & 0xffff00);
  }

  static const int getCommandType(CommandID id)
  {
    // return just the type info in the command
    return (id & 0xff0000) >> 16;
  }

  static const int getCommandNumber(CommandID id)
  {
    // return just the type info in the command
    return (id & 0x00ff00) >> 8;
  }

  static const int getCommandData(CommandID id)
  {
    return (id & 0x0000ff) ;
  }

  static const bool isCommand(CommandID id, CommandID cmd)
  {
    return (getCommand(id)==cmd);
  }

  static const bool isCommandType(CommandID id, int type)
  {
    return (getCommandType(id)==type);
  }

  //
  // Command IDs
  //

  /** Command Types are generic command categories, generally
      correspond to menu names **/

  static const int App = 1;
  static const int Console = 2;
  static const int Editor = 3;
  static const int Emacs = 4;
  static const int Plotter = 5;
  static const int MidiOut = 6;
  static const int MidiIn = 7;
  static const int MidiSeq = 8;
  static const int Csound = 9;
  static const int SndLib = 10;
  static const int Fomus = 11;
  static const int Audio = 12;
  static const int Window = 13;
  static const int Help = 14;
  static const int Scheduler = 15;
  static const int Scheme = 16;
  static const int Prefs = 17;

  static const String getCommandTypeName(CommandID id)
  {
    switch (getCommandType(id))
      {
      case Empty: return T("Empty");
      case App: return T("App");
      case Console: return T("Console");
      case Editor: return T("Editor");
      case Emacs: return T("Emacs");
      case Plotter: return T("Plotter");
      case MidiOut: return T("MidiOut");
      case MidiIn: return T("MidiIn");
      case MidiSeq: return T("MidiSeq");
      case Csound: return T("Csound");
      case Fomus: return T("Fomus");
      case SndLib: return T("SndLib");
      case Audio: return T("Audio");
      case Window: return T("Window");
      case Help: return T("Help");
      case Scheduler: return T("Scheduler");
      case Scheme: return T("Scheme");
      case Prefs: return T("Prefs");
      default: return T("Unkown Type");
      }
  }

  static const String toString(CommandID id, bool data=false)
  {
    String str=getCommandTypeName(id);
    int num=getCommandNumber(id);
    if (num>0)
      {
	str << T(" ") << String(num);
	if (data)
	  str << T(" ") << String(getCommandData(id));
      }
    return str;
  }
  
  static const CommandID Empty=0;

  static const CommandID AppQuit = COMID(App, 1);

  static const CommandID PrefsOpenRecent = COMID(Prefs, 1);
  static const CommandID PrefsClearOpenRecent = COMID(Prefs, 2);
  static const CommandID PrefsEditorEmacsMode = COMID(Prefs, 3);
  static const CommandID PrefsEditorFont = COMID(Prefs, 4);
  static const CommandID PrefsEditorFontSize = COMID(Prefs, 5);
  static const CommandID PrefsLoadRecent = COMID(Prefs, 6);
  static const CommandID PrefsClearLoadRecent = COMID(Prefs, 7);
  static const CommandID PrefsSetInitFile = COMID(Prefs, 8);
  static const CommandID PrefsClearInitFile = COMID(Prefs, 9);

  static const CommandID LispLoadFile = COMID(Scheme, 1);
  static const CommandID LispCompileFile = COMID(Scheme, 2);
  static const CommandID LispConfigure = COMID(Scheme, 3);
  static const CommandID LispStart = COMID(Scheme, 4);

  // Console File
  static const CommandID ConsoleNewEditor = COMID(Console, 1);
  static const CommandID ConsoleOpen = COMID(Console, 2);
  static const CommandID ConsoleShowDirectory = COMID(Console, 3);
  static const CommandID ConsoleSetDirectory = COMID(Console, 4);
  static const CommandID ConsoleQuit = COMID(Console, 5);

  // Console Edit
  static const CommandID ConsoleFont = COMID(Console, 16);
  static const CommandID ConsoleFontSize = COMID(Console, 17);
  static const CommandID ConsoleTheme = COMID(Console, 18);

  static const CommandID ConsoleSelectAll = COMID(Console, 19);
  static const CommandID ConsoleCopy = COMID(Console, 20);
  static const CommandID ConsoleClearSelection = COMID(Console, 21);
  static const CommandID ConsoleBeepOnError = COMID(Console, 22);
  static const CommandID ConsoleClearConsole = COMID(Console, 23);

  // console MESSAGES (async)
  static const CommandID ConsolePrintOutput   = COMID(Console, 128);
  static const CommandID ConsolePrintValues   = COMID(Console, 129);
  static const CommandID ConsolePrintWarning  = COMID(Console, 130);
  static const CommandID ConsolePrintError    = COMID(Console, 131);
  static const CommandID ConsolePrintPrompt   = COMID(Console, 132);

  static const CommandID EditorNew = COMID(Editor, 1);
  static const CommandID EditorOpen = COMID(Editor, 2);
  static const CommandID EditorSave = COMID(Editor, 3);
  static const CommandID EditorSaveAs = COMID(Editor, 4);
  static const CommandID EditorRevert = COMID(Editor, 5);
  static const CommandID EditorShowDirectory = COMID(Editor, 6);
  static const CommandID EditorSetDirectory = COMID(Editor, 7);
  static const CommandID EditorPrint = COMID(Editor, 8);
  static const CommandID EditorClose = COMID(Editor, 9);

  static const CommandID EditorUndo = COMID(Editor, 16);
  static const CommandID EditorRedo = COMID(Editor, 17);
  static const CommandID EditorCut = COMID(Editor, 18);
  static const CommandID EditorCopy = COMID(Editor, 19);
  static const CommandID EditorPaste = COMID(Editor, 20);
  
  static const CommandID EditorSelectAll = COMID(Editor, 21);
  static const CommandID EditorUnselectAll = COMID(Editor, 22);
  static const CommandID EditorFind = COMID(Editor, 23);
  static const CommandID EditorReplace = COMID(Editor, 24);

  static const CommandID EditorSyntax = COMID(Editor, 32);
  static const CommandID EditorFont = COMID(Editor, 33);
  static const CommandID EditorFontSize = COMID(Editor, 34);
  static const CommandID EditorTabWidth = COMID(Editor, 35);
  static const CommandID EditorParensMatching = COMID(Editor, 36);
  static const CommandID EditorHighlighting = COMID(Editor, 37);
  static const CommandID EditorEmacsMode = COMID(Editor, 38);

  static const CommandID EditorExecute = COMID(Editor, 48);
  static const CommandID EditorExpand = COMID(Editor, 49);
  static const CommandID EditorIndent = COMID(Editor, 50);
  static const CommandID EditorCommentOut = COMID(Editor, 51);
  static const CommandID EditorUncommentOut = COMID(Editor, 52);
  static const CommandID EditorFormatComments = COMID(Editor, 53);
  static const CommandID EditorSymbolHelp = COMID(Editor, 54);

  static const CommandID EditorAddTrigger = COMID(Editor, 55);
  static const CommandID EditorRemoveTrigger = COMID(Editor, 56);
  static const CommandID EditorLoadTrigger = COMID(Editor, 57);
  static const CommandID EditorSaveTrigger = COMID(Editor, 58);
  static const CommandID EditorImportTrigger = COMID(Editor, 59);
  static const CommandID EditorExportTrigger = COMID(Editor, 60);
  static const CommandID EditorConfigureTrigger = COMID(Editor, 61);

  // these are messages for coloration not commands
  static const CommandID EditorDelete = COMID(Editor, 64);
  static const CommandID EditorBackspace = COMID(Editor, 65);
  static const CommandID EditorNewline = COMID(Editor, 66);
  static const CommandID EditorTextChanged= COMID(Emacs, 67);

  // Emacs Commands
  static const CommandID EmacsCharForward = COMID(Emacs, 1);
  static const CommandID EmacsCharBackward = COMID(Emacs, 2);
  static const CommandID EmacsWordForward = COMID(Emacs, 3);
  static const CommandID EmacsWordBackward = COMID(Emacs, 4);
  static const CommandID EmacsExprForward = COMID(Emacs, 5);
  static const CommandID EmacsExprBackward = COMID(Emacs, 6);
  static const CommandID EmacsLineForward = COMID(Emacs, 7);
  static const CommandID EmacsLineBackward = COMID(Emacs, 8);
  static const CommandID EmacsPageForward = COMID(Emacs, 9);
  static const CommandID EmacsPageBackward = COMID(Emacs, 10);
  static const CommandID EmacsGotoEOL = COMID(Emacs, 11);
  static const CommandID EmacsGotoBOL = COMID(Emacs, 12);
  static const CommandID EmacsGotoEOB = COMID(Emacs, 13);
  static const CommandID EmacsGotoBOB = COMID(Emacs, 14);
  static const CommandID EmacsKillChar = COMID(Emacs, 15);
  static const CommandID EmacsKillWord = COMID(Emacs, 16);
  static const CommandID EmacsKillExpr = COMID(Emacs, 17);
  static const CommandID EmacsKillWhite = COMID(Emacs, 18);
  static const CommandID EmacsKillLine = COMID(Emacs, 19);
  static const CommandID EmacsKillRegion = COMID(Emacs, 20);
  static const CommandID EmacsOpenLine = COMID(Emacs, 21);
  static const CommandID EmacsYank = COMID(Emacs, 22);
  static const CommandID EmacsCapitalize = COMID(Emacs, 23);
  static const CommandID EmacsUppercase = COMID(Emacs, 24);
  static const CommandID EmacsLowercase = COMID(Emacs, 25);
  static const CommandID EmacsFormatComments = COMID(Emacs, 26);
  static const CommandID EmacsControlX = COMID(Emacs, 27);

  // MidiOut Port
  static const CommandID MidiOutOpen = COMID(MidiOut, 1);
  static const CommandID MidiOutTest = COMID(MidiOut, 2);
  static const CommandID MidiOutHush = COMID(MidiOut, 3);
  static const CommandID MidiOutAllNotesOff = COMID(MidiOut, 4);
  static const CommandID MidiOutTuning = COMID(MidiOut, 5);
  static const CommandID MidiOutDrumTrack = COMID(MidiOut, 6);
  static const CommandID MidiOutPitchBend = COMID(MidiOut, 7);
  static const CommandID MidiOutInstruments = COMID(MidiOut, 8);
  static const CommandID MidiOutFileSettings = COMID(MidiOut, 9);

  // MidiIn Port
  static const CommandID MidiInOpen = COMID(MidiIn, 1);
  static const CommandID MidiInTrace = COMID(MidiIn, 2);
  static const CommandID MidiInChannelFilter = COMID(MidiIn, 3);
  static const CommandID MidiInOpcodeFilter = COMID(MidiIn, 4);
  static const CommandID MidiInConfigure = COMID(MidiIn, 5);
  static const CommandID MidiInImportFile = COMID(MidiIn, 6);


  // MidiSeq Port
  static const CommandID MidiSeqRecordMidiOut = COMID(MidiSeq, 1);
  static const CommandID MidiSeqRecordMidiIn = COMID(MidiSeq, 2);
  static const CommandID MidiSeqCaptureScore = COMID(MidiSeq, 3);
  static const CommandID MidiSeqResetRecordingStart = COMID(MidiSeq, 4);
  static const CommandID MidiSeqClear = COMID(MidiSeq, 5);
  static const CommandID MidiSeqPlay = COMID(MidiSeq, 6);
  static const CommandID MidiSeqPlot = COMID(MidiSeq, 7);
  static const CommandID MidiSeqPrintInfo = COMID(MidiSeq, 8);
  static const CommandID MidiSeqCopyToTrack = COMID(MidiSeq, 9);
  static const CommandID MidiSeqRenameTrack = COMID(MidiSeq, 10);
  static const CommandID MidiSeqRestoreTrack = COMID(MidiSeq, 11);
  static const CommandID MidiSeqMixTrack = COMID(MidiSeq, 12);
  static const CommandID MidiSeqReplaceTrack = COMID(MidiSeq, 13);
  static const CommandID MidiSeqDeleteTrack = COMID(MidiSeq, 14);
  static const CommandID MidiSeqImport = COMID(MidiSeq, 15);
  static const CommandID MidiSeqExport = COMID(MidiSeq, 16);
  static const CommandID MidiSeqSetFile = COMID(MidiSeq, 17);
  static const CommandID MidiSeqSave = COMID(MidiSeq, 18);
  static const CommandID MidiSeqSaveAs = COMID(MidiSeq, 19);
  static const CommandID MidiSeqOpenFile = COMID(MidiSeq, 20);

  // Csound
  static const CommandID CsoundPrefWriteAfter = COMID(Csound, 1);
  static const CommandID CsoundPrefPlayAfter = COMID(Csound, 2);
  static const CommandID CsoundExportScore = COMID(Csound, 3);
  static const CommandID CsoundClearScore = COMID(Csound, 4);
  static const CommandID CsoundOpenSettings = COMID(Csound, 5);

  // Fomus
  static const CommandID FomusNewScore = COMID(Fomus, 1);
  static const CommandID FomusRenameScore = COMID(Fomus, 2);
  static const CommandID FomusDeleteScore = COMID(Fomus, 3);
  static const CommandID FomusSelectScore = COMID(Fomus, 4);
  static const CommandID FomusLoadScore = COMID(Fomus, 5);
  static const CommandID FomusRunScore = COMID(Fomus, 6);
  static const CommandID FomusSettings = COMID(Fomus, 7);
  static const CommandID FomusDocumentation = COMID(Fomus, 8);
  static const CommandID FomusRunCurr = COMID(Fomus, 9);
  static const CommandID FomusClearScore = COMID(Fomus, 10);
  static const CommandID FomusSaveScore = COMID(Fomus, 11);

  // Audio Menu
  static const CommandID AudioOpenFilePlayer = COMID(Audio, 1);
  static const CommandID MidiFilePlayer = COMID(Audio, 2);
  static const CommandID MidiPlotPlayer = COMID(Audio, 3);
  static const CommandID AudioSettings = COMID(Audio, 4);

  // SndLib
  static const CommandID SndLibSrate = COMID(SndLib, 1);
  static const CommandID SndLibChannels = COMID(SndLib, 2);
  static const CommandID SndLibAutoPlay = COMID(SndLib, 3);
  static const CommandID SndLibInsDialog = COMID(SndLib, 4);
  static const CommandID SndLibAutoLoad = COMID(SndLib, 4);

  // Scheduler
  static const CommandID SchedulerStop = COMID(Scheduler, 1);
  static const CommandID SchedulerPause = COMID(Scheduler, 2);
  static const CommandID SchedulerError = COMID(Scheduler, 3);
  static const CommandID SchedulerScoreMode = COMID(Scheduler, 4);
  static const CommandID SchedulerScoreComplete = COMID(Scheduler, 5);

  // Common Window Commands
  static const CommandID WindowSelect = COMID(Window, 1);

  // Help Menu
  static const CommandID HelpSymbolLookup = COMID(Help, 1);
  static const CommandID HelpManual = COMID(Help, 2);
  static const CommandID HelpExample = COMID(Help, 3);
  static const CommandID HelpTutorial = COMID(Help, 4);
  static const CommandID HelpWebSite = COMID(Help, 5);
  static const CommandID HelpShowDirectory = COMID(Help, 6);

  // Plotter commands
  static const CommandID PlotterNew = COMID(Plotter, 1);
  static const CommandID PlotterOpen = COMID(Plotter, 2);
  static const CommandID PlotterOpenMidiFile = COMID(Plotter, 3);
  static const CommandID PlotterSaveAs = COMID(Plotter, 4);
  static const CommandID PlotterSave = COMID(Plotter, 5);
  static const CommandID PlotterRename = COMID(Plotter, 6);
  static const CommandID PlotterExport = COMID(Plotter, 7);
  static const CommandID PlotterClose = COMID(Plotter, 8);
  static const CommandID PlotterLayerAdd = COMID(Plotter, 9);
  static const CommandID PlotterLayerDelete = COMID(Plotter, 10);
  static const CommandID PlotterLayerEdit = COMID(Plotter, 11);
  static const CommandID PlotterAxisEdit = COMID(Plotter, 12);
  static const CommandID PlotterLayerRename = COMID(Plotter, 13);
  static const CommandID PlotterLayerSelect = COMID(Plotter, 14);
  static const CommandID PlotterStyle = COMID(Plotter, 15);
  static const CommandID PlotterBgStyle = COMID(Plotter, 16);
  static const CommandID PlotterBgColor = COMID(Plotter, 17);
  static const CommandID PlotterBgPlotting = COMID(Plotter, 18);
  static const CommandID PlotterBgMousing = COMID(Plotter, 19);
  static const CommandID PlotterVertical = COMID(Plotter, 20);
  static const CommandID PlotterHorizontal = COMID(Plotter, 21);
  static const CommandID PlotterEditPoints = COMID(Plotter, 22);
  static const CommandID PlotterShiftPoints = COMID(Plotter, 23);
  static const CommandID PlotterRescalePoints = COMID(Plotter, 24);
  static const CommandID PlotterAddXmlPoints = COMID(Plotter, 25);
};

#undef COMID
 
class Flags 
{  
 public:
  static const int get(int flags, int f)
  {
    return (flags & f);
  }
  static const bool test(int flags, int f)
  {
    return (get(flags, f) == f);
  }
  static const void setOn(int& flags, int f)
  {
    flags |= f; 
  }
  static const void setOff(int& flags, int f) 
  {
    flags &= ~f; 
  }
  static const bool toggle(int& flags, int f)
  {
    flags ^= f; 
    return test(flags, f);
  }
};

class EditFlags
{
 public:
  static const int Empty = 0;
  static const int NeedsSave = 1 << 0;
  static const int ReadOnly  = 1 << 1;
  static const int HiliteOff = 1 << 2;
  static const int MatchingOff = 1 << 3;
  static const int EmacsMode = 1 << 4;
  static const int Coloring  = 1 << 5;
};

class SrateIDs
{
 public:
  static const int NumSrates = 4;
  static const int Srate0 = 22050;  
  static const int Srate1 = 44100;  
  static const int Srate2 = 48000;  
  static const int Srate3 = 96000;  
  static const int toSrate(int id)
  {
    switch (id)
      {
      case 0: return Srate0;
      case 1: return Srate1;
      case 2: return Srate2;
      case 3: return Srate3;
      default: return Srate1;
      }
  }
  
  static const String toString(int id)
  {
    return String(toSrate(id));
  }
};

class TriggerIDs
{
 public:
  static const int Empty=0;
  static const int ButtonTrigger=1;
  static const int SliderTrigger=2;
  static const int MidiKeyboardTrigger=3;
  static const int MidiInTrigger=4;
  static const int NumTriggers=4;
  static const String toString(int id)
  {
    switch (id)
      {
      case ButtonTrigger:
	return T("button");
      case SliderTrigger:
	return T("slider");
      case MidiKeyboardTrigger:
	return T("keyboard");
      case MidiInTrigger:
	return T("midiin");
      default:
	return String::empty;
      }
  }
  static const String toPrettyString(int id)
  {
    switch (id)
      {
      case ButtonTrigger:
	return  T("Button");
      case SliderTrigger:
	return T("Slider");
      case MidiKeyboardTrigger:
	return  T("Keyboard");
      case MidiInTrigger:
	return T("Midi In");
      default:
	return T("Empty");
      }  
  }
  
  static int fromString(const String str)
  {
    if (str.equalsIgnoreCase(T("button")))
      return ButtonTrigger;
    if (str.equalsIgnoreCase(T("slider")))
      return SliderTrigger;
    if (str.equalsIgnoreCase(T("keyboard")))
      return MidiKeyboardTrigger;
    if (str.removeCharacters(T(" ")).equalsIgnoreCase(T("midiin")))
      return MidiInTrigger;
    else
      return Empty;
  }
};


#endif
