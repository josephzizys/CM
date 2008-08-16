/*************************************************************************
 * Copyright (C) 2008 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

#ifndef GRACEENUMERATIONS
#define GRACEENUMERATIONS

#include "juce.h"

/** TextIds enumerate the varous code syntaxes, the first three of
    which are also supported by a code syntax in the Editor **/

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

/** EditFlags enumerate various editing states **/

class EditFlags
{
 public:
  static const int Empty = 0;
  static const int NeedSave  = 1 << 0;
  static const int ReadOnly  = 1 << 1;
  static const int HiliteOff = 1 << 2;
  static const int ParensOff = 1 << 3;
  static const int Load      = 1 << 4;
  static const int NoSave    = 1 << 5;
  static const int EmacsMode = 1 << 6;
};

/** ExportIDs enumerate the various ways of exporting music data to
    editors and other windows. Upper nibble holds the export type (a
    TextID), lower nibble holds the format of the output (ie lists of
    event data, send expressions) **/

typedef int ExportID;

class ExportIDs
{
 private:
  static const int SHIFT=4;
  static const int UMASK=0xf0;
  static const int LMASK=0x0f;
 public:
  static const int Empty = 0;

  static const int Data = 1;  // event data exported as lists
  static const int Send = 2;  // event data exported as send exprs
  static const int Score = 3; // score file format

  static const ExportID SalData = (TextIDs::Sal << SHIFT) + Data;
  static const ExportID SalSend = (TextIDs::Sal << SHIFT) + Send;
  static const ExportID LispData = (TextIDs::Lisp << SHIFT) + Data;
  static const ExportID LispSend = (TextIDs::Lisp << SHIFT) + Send;
  static const ExportID CsoundScore = (TextIDs::Csound << SHIFT) + Score;
  static const ExportID XmlData = (TextIDs::Xml << SHIFT) + Data ;

  static const TextID getTextID(ExportID f)
  {
    return (TextID)((f & UMASK) >> SHIFT);
  }

  static const int getFormat(ExportID f)
  {
    return (f & LMASK);
  }
};


/** WindowIDs enumerate windows. Upper byte holds the type of window,
    lower byte holds user data, for example its index in the Windows
    menu **/

typedef int WindowID;

class WindowIDs
{
 private:
  static const int SHIFT=8;
  static const int UMASK=0xff00;
  static const int LMASK=0x00ff;

 public:
  static const int Empty = 0;
  static const int Console = 1;
  static const int Editor = 2;
  static const int Plotter = 3;

  static const WindowID toID(WindowID w, int d)
  {
    return (w << SHIFT) + d;
  }

  static const int getWindowType(WindowID id)
  {
    return ((id & UMASK) >> SHIFT);
  }

  static const int getData(WindowID id)
  {
    return (id & LMASK);
  }
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
  static const int Gui = 2;
  static const int File = 3;
  static const int Edit = 4;
  static const int Emacs = 5;
  static const int View = 6;
  static const int Options = 7;
  static const int Eval = 8;
  static const int CommonLisp = 9;
  static const int Scheme = 10;
  static const int MidiOut = 11;
  static const int MidiIn = 12;
  static const int MidiSeq = 13;
  static const int Csound = 14;
  static const int Audio = 15;
  static const int Fomus = 16;
  static const int Plotter = 17;
  static const int Window = 18;
  static const int Help = 19;

  static const CommandID Empty=0;

  // Application
  static const CommandID AppQuit = COMID(App, 1);
  static const CommandID AppPreferences = COMID(App, 2);
  // Opening GUI windows
  static const CommandID NewConsole = COMID(Gui, 1); // not used..
  static const CommandID NewEditor = COMID(Gui, 2);
  static const CommandID NewPlotter = COMID(Gui, 3);
  // File Commands
  static const CommandID FileOpen = COMID(File, 1);
  static const CommandID FileOpenRecent = COMID(File, 2);
  static const CommandID FileClearRecent = COMID(File, 3);
  static const CommandID FileSave = COMID(File, 4);
  static const CommandID FileSaveAs = COMID(File, 5);
  static const CommandID FileRevert = COMID(File, 6);
  static const CommandID FileClose = COMID(File, 7);
  static const CommandID FileImport = COMID(File, 8);
  static const CommandID FileExport = COMID(File, 9);
  // Edit Commands
  static const CommandID EditUndo = COMID(Edit, 1);
  static const CommandID EditRedo = COMID(Edit, 2);
  static const CommandID EditCut = COMID(Edit, 3);
  static const CommandID EditCopy = COMID(Edit, 4);
  static const CommandID EditPaste = COMID(Edit, 5);
  static const CommandID EditClear = COMID(Edit, 6);
  static const CommandID EditSelectAll = COMID(Edit, 7);
  static const CommandID EditSearch = COMID(Edit, 8);
  static const CommandID EditReplace = COMID(Edit, 9);
  static const CommandID EditParens = COMID(Edit, 10);
  static const CommandID EditHilite = COMID(View, 11);
  static const CommandID EditEmacsMode = COMID(Edit, 12);
  // Emacs Commands
  static const CommandID EmacsCharForward = COMID(Emacs, 1);
  static const CommandID EmacsCharBackward = COMID(Emacs, 2);
  static const CommandID EmacsWordForward = COMID(Emacs, 3);
  static const CommandID EmacsWordBackward = COMID(Emacs, 4);
  static const CommandID EmacsSexprForward = COMID(Emacs, 5);
  static const CommandID EmacsSexprBackward = COMID(Emacs, 6);
  static const CommandID EmacsLineForward = COMID(Emacs, 7);
  static const CommandID EmacsLineBackward = COMID(Emacs, 8);
  static const CommandID EmacsPageForward = COMID(Emacs, 9);
  static const CommandID EmacsPageBackward = COMID(Emacs, 10);
  static const CommandID EmacsGotoEOL = COMID(Emacs, 11);
  static const CommandID EmacsGotoBOL = COMID(Emacs, 12);
  static const CommandID EmacsGotoEOB = COMID(Emacs, 13);
  static const CommandID EmacsGotoBOB = COMID(Emacs, 14);
  static const CommandID EmacsGotoColumn = COMID(Emacs, 15);
  static const CommandID EmacsGotoLine = COMID(Emacs, 16);
  static const CommandID EmacsBackspace = COMID(Emacs, 17);
  static const CommandID EmacsDelete = COMID(Emacs, 18);
  static const CommandID EmacsKillWord = COMID(Emacs, 19);
  static const CommandID EmacsKillSexpr = COMID(Emacs, 20);
  static const CommandID EmacsKillWhite = COMID(Emacs, 21);
  static const CommandID EmacsKillLine = COMID(Emacs, 22);
  static const CommandID EmacsInsertChar = COMID(Emacs, 23);
  static const CommandID EmacsInsertLine = COMID(Emacs, 24);
  static const CommandID EmacsOpenLine = COMID(Emacs, 25);
  static const CommandID EmacsComplete = COMID(Emacs, 26);
  static const CommandID EmacsIndent = COMID(Emacs, 27);
  static const CommandID EmacsToggleReadWrite = COMID(Emacs, 28);
  // MidiOut Port
  static const CommandID MidiOutOpen = COMID(MidiOut, 1);
  static const CommandID MidiOutTest = COMID(MidiOut, 2);
  static const CommandID MidiOutHush = COMID(MidiOut, 3);
  static const CommandID MidiOutAllNotesOff = COMID(MidiOut, 4);
  static const CommandID MidiOutTuning = COMID(MidiOut, 5);
  static const CommandID MidiOutDrumTrack = COMID(MidiOut, 6);
  static const CommandID MidiOutPitchBend = COMID(MidiOut, 7);
  static const CommandID MidiOutInstruments = COMID(MidiOut, 8);
  // MidiIn Port
  static const CommandID MidiInOpen = COMID(MidiIn, 1);
  static const CommandID MidiInTest = COMID(MidiIn, 2);
  static const CommandID MidiInHook = COMID(MidiIn, 3);
  static const CommandID MidiInRecord = COMID(MidiIn, 4);
  static const CommandID MidiInConfigure = COMID(MidiIn, 5);
  // MidiSeq Port
  static const CommandID MidiSeqCaptureMidiOut = COMID(MidiSeq, 1);
  static const CommandID MidiSeqCaptureMidiIn = COMID(MidiSeq, 2);
  static const CommandID MidiSeqCaptureScore = COMID(MidiSeq, 3);
  static const CommandID MidiSeqResetRecordingStart = COMID(MidiSeq, 4);
  static const CommandID MidiSeqClear = COMID(MidiSeq, 5);
  static const CommandID MidiSeqPlay = COMID(MidiSeq, 6);
  static const CommandID MidiSeqPlotter = COMID(MidiSeq, 7);
  static const CommandID MidiSeqPrintInfo = COMID(MidiSeq, 8);
  static const CommandID MidiSeqCopyToTrack = COMID(MidiSeq, 9);
  static const CommandID MidiSeqRenameTrack = COMID(MidiSeq, 10);
  static const CommandID MidiSeqRestoreTrack = COMID(MidiSeq, 11);
  static const CommandID MidiSeqMixTrack = COMID(MidiSeq, 12);
  static const CommandID MidiSeqReplaceTrack = COMID(MidiSeq, 13);
  static const CommandID MidiSeqDeleteTrack = COMID(MidiSeq, 14);
  static const CommandID MidiSeqImport = COMID(MidiSeq, 15);
  static const CommandID MidiSeqExport = COMID(MidiSeq, 16);
  static const CommandID MidiSeqSave = COMID(MidiSeq, 17);
  static const CommandID MidiSeqSaveAs = COMID(MidiSeq, 18);
  // Csound Port
  static const CommandID CsoundOpen = COMID(Csound, 1);
  static const CommandID CsoundClose = COMID(Csound, 2);
  static const CommandID CsoundWrite = COMID(Csound, 3);
  static const CommandID CsoundAbortWrite = COMID(Csound, 4);
  static const CommandID CsoundPlay = COMID(Csound, 5);
  static const CommandID CsoundImport = COMID(Csound, 6);
  static const CommandID CsoundExport = COMID(Csound, 7);
  static const CommandID CsoundPrint = COMID(Csound, 8);
  static const CommandID CsoundDisplay = COMID(Csound, 9);
  static const CommandID CsoundClear = COMID(Csound, 10);
  static const CommandID CsoundScoreMode = COMID(Csound, 11);
  static const CommandID CsoundRecordMode = COMID(Csound, 12);
  static const CommandID CsoundTraceMode = COMID(Csound, 13);
  // Audio Port
  static const CommandID AudioSetup = COMID(Audio, 1);
  // Common Lisp Commands
  static const CommandID CommonLispConnect = COMID(CommonLisp, 1);
  static const CommandID CommonLispLoadSystem = COMID(CommonLisp, 2);
  static const CommandID CommonLispLoadRecentSystem = COMID(CommonLisp, 3);
  static const CommandID CommonLispClearRecentSystems=COMID(CommonLisp, 4);
  static const CommandID CommonLispLoadFile = COMID(CommonLisp, 5);
  static const CommandID CommonLispLoadRecentFile = COMID(CommonLisp, 6);
  static const CommandID CommonLispCompileFile = COMID(CommonLisp, 7);
  static const CommandID CommonLispClearRecentLoaded=COMID(CommonLisp, 8);
  static const CommandID CommonLispConfigure = COMID(CommonLisp, 9);
  // View Commands
  static const CommandID ViewFontList = COMID(View, 1);
  static const CommandID ViewFontSize = COMID(View, 2);
  static const CommandID ViewSelectTheme = COMID(View, 3);
  static const CommandID ViewOpacity = COMID(View, 4);
  static const CommandID ViewZoomIn = COMID(View, 10);
  static const CommandID ViewZoomOut = COMID(View, 11);
  static const CommandID ViewScrollVertical = COMID(View, 12);
  static const CommandID ViewScrollHorizontal = COMID(View, 13);

  // Common Window Commands
  static const CommandID WindowConsole = COMID(Window, 1);
  static const CommandID WindowSelect = COMID(Window, 2);

  // Lisp Eval
  static const CommandID EvalExecute = COMID(Eval, 1);
  static const CommandID EvalExpand = COMID(Eval, 2);
  static const CommandID EvalLoadFile = COMID(Eval, 3);
  static const CommandID EvalCompileFile = COMID(Eval, 4);
  static const CommandID EvalShowDirectory = COMID(Eval, 5);
  static const CommandID EvalSetDirectory = COMID(Eval, 6);
  static const CommandID EvalSetPackage = COMID(Eval, 7);
  static const CommandID EvalSymbolHelp = COMID(Eval, 8);
  // Common Help Menu
  static const CommandID HelpTopic = COMID(Help, 1);
  static const CommandID HelpTutorial = COMID(Help, 3);
  static const CommandID HelpExample = COMID(Help, 4);
  static const CommandID HelpWebSite = COMID(Help, 5);
  // Plotter commands
  static const CommandID PlotterLayerAdd = COMID(Plotter, 1);
  static const CommandID PlotterLayerDelete = COMID(Plotter, 2);
  static const CommandID PlotterLayerSelect = COMID(Plotter, 3);
  static const CommandID PlotterStyle = COMID(Plotter, 4);
  static const CommandID PlotterBgStyle = COMID(Plotter, 5);
  static const CommandID PlotterBgColor = COMID(Plotter, 6);
  static const CommandID PlotterBgPlotting = COMID(Plotter, 7);
  static const CommandID PlotterBgMousing = COMID(Plotter, 8);
  static const CommandID PlotterVertical = COMID(Plotter, 9);
  static const CommandID PlotterHorizontal = COMID(Plotter, 10);

};

#undef COMID
  
/** PlotIDs enumerate different types of Plots that Plotter can
    deal with. Currently only XY and Midi are valid. **/

typedef int PlotID;

class PlotIDs
{
 public:
  // WARNING: dont change until old PlotType enum is removed
  static const PlotID Empty = 0;
  static const PlotID XYPlot = 1;
  static const PlotID MidiPlot = 3;

};

#endif

