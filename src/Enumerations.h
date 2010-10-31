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

  static const int CM_VERSION = 370;
  static const int GRACE_VERSION = CM_VERSION;

  /*======================================================================*
                                Version Info
   *======================================================================*/

  static const String getCMVersion()
  {
    String str= T("Common Music ") + getVersionString(CM_VERSION);

    return str;
  }

  static const String getCMSvnRevision()
  {
    String str=String::empty;
    str << T("[svn:")
#ifdef SVNVERSION
	<< String(SVNVERSION)
#else
	<< T("none")
#endif
	<< T("]");
    return str;
  }

  static const String getGraceVersion()
  {
    String str=getVersionString(GRACE_VERSION);
    return str;
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
  static const TextID Sal2=4;
  static const TextID Fomus=5;
  static const TextID Csound=6;
  static const TextID Xml=7;
  static const int fromString(const String id)
  {
    if (id.equalsIgnoreCase(T("text"))) return Text;
    if (id.equalsIgnoreCase(T("lisp"))) return Lisp;
    if (id.equalsIgnoreCase(T("sal1"))) return Sal;
    if (id.equalsIgnoreCase(T("sal"))) return Sal2;
    if (id.equalsIgnoreCase(T("sal2"))) return Sal2;
    if (id.equalsIgnoreCase(T("fomus"))) return Fomus;
    if (id.equalsIgnoreCase(T("csound"))) return Csound;
    if (id.equalsIgnoreCase(T("xml"))) return Xml;
    return Empty;
  }
  static const String toString(const int id)
  {
    switch (id)
      {
      case Text:
	return T("Text");
      case Lisp:
	return T("Lisp");
      case Sal:
	return T("Sal1");
      case Sal2:
	return T("Sal2");
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
  static const int fromFileType(const String ext)
  {
    if (String(T(".lisp.lsp.scm.cm.clm.cmn.ins")).contains(ext))
      return Lisp;
    else if (ext.equalsIgnoreCase(T(".sal2")))
      return Sal2;
    else if (ext.equalsIgnoreCase(T(".sal"))) 
      return Sal2;
    else if (ext.equalsIgnoreCase(T(".sal1"))) 
      return Sal;
    else if (ext.equalsIgnoreCase(T(".fms"))) 
      return Fomus;
    else if (ext.equalsIgnoreCase(T(".sco")))
      return Csound;
    else if (ext.equalsIgnoreCase(T(".xml")))
      return Xml;
    else if (String(T(".text.txt")).contains(ext))
      return Text;
    return Empty;
  }

  static const bool canExecute(const int ttyp)
  {
    return ((ttyp==Lisp) || (ttyp==Sal2) || (ttyp==Sal) || (ttyp==Fomus));
  }

  static const bool canExpand(const int ttyp)
  {
    return ((ttyp==Lisp) || (ttyp==Sal2) || (ttyp==Sal));
  }
};

class ColorThemeIDs
{
 public:
  static const int Empty=-1;
  static const int Plaintext=0;
  static const int Keyword1=1;
  static const int Keyword2=2;
  static const int Keyword3=3;
  static const int Literal1=4;
  static const int Literal2=5;
  static const int Literal3=6;
  static const int Comment=7;
  static const int Stryng=8;
  static const int Error=9;
  static const int MAXTOKENCOLORS=10; // from Plaintext to Error
  static const int Warning=10;
  static const int Output=11;
  static const int Values=12;
  static const int Cursor=13;
  static const int Region=14;
  static const int Background=15;
  static const int Name=16;
  
  static const juce::String toString(int id)
  {
    switch (id)
      {
      case Name: return String(T("name"));
      case Background: return String(T("background"));
      case Cursor: return String(T("cursor"));
      case Region: return String(T("region"));
      case Values: return String(T("values"));
      case Error: return String(T("error"));
      case Warning: return String(T("warning"));
      case Output: return String(T("output"));
      case Comment: return String(T("comment"));
      case Stryng: return String(T("string"));
      case Plaintext: return String(T("plaintext"));
      case Keyword1: return String(T("keyword1"));  // scheme sharp #foo
      case Keyword2: return String(T("keyword2"));  // scheme keyword :foo
      case Keyword3: return String(T("keyword3"));  // sal keyword foo
      case Literal1: return String(T("literal1"));  // special form/reserved
      case Literal2: return String(T("literal2"));  // sal classname
      case Literal3: return String(T("literal3"));  // sal command
      case Empty: return String(T("Empty"));   
      }
  }

  static const int fromString(const String s)
  {
    if (s.equalsIgnoreCase(T("name"))) return Name;
    if (s.equalsIgnoreCase(T("background"))) return Background;
    if (s.equalsIgnoreCase(T("cursor"))) return Cursor;
    if (s.equalsIgnoreCase(T("region"))) return Region;
    if (s.equalsIgnoreCase(T("values"))) return Values;
    if (s.equalsIgnoreCase(T("error"))) return Error;
    if (s.equalsIgnoreCase(T("warning"))) return Warning;
    if (s.equalsIgnoreCase(T("output"))) return Output;
    if (s.equalsIgnoreCase(T("comment"))) return Comment;
    if (s.equalsIgnoreCase(T("string"))) return Stryng;
    if (s.equalsIgnoreCase(T("plaintext"))) return Plaintext;
    if (s.equalsIgnoreCase(T("keyword1"))) return Keyword1;
    if (s.equalsIgnoreCase(T("keyword2"))) return Keyword2;
    if (s.equalsIgnoreCase(T("keyword3"))) return Keyword3;
    if (s.equalsIgnoreCase(T("literal1"))) return Literal1;
    if (s.equalsIgnoreCase(T("literal2"))) return Literal2;
    if (s.equalsIgnoreCase(T("literal3"))) return Literal3;
    return Empty;
  }

  static const String toHtmlColorString(const Colour color)
  {
    switch (color.getARGB())  // hacked for standard grace colors
      {
      case 0xff000000 : return String(T("black"));
      case 0xffffffff : return String(T("white"));
      case 0xff808080 : return String(T("grey"));
      case 0xff0000ff : return String(T("blue"));
      case 0xff008000 : return String(T("green"));
      case 0xffff0000 : return String(T("red"));
      case 0xffffff00 : return String(T("yellow"));
      case 0xff228b22 : return String(T("forestgreen"));
      case 0xffb22222 : return String(T("firebrick"));
      case 0xffff8c00 : return String(T("darkorange"));
      case 0xffffa07a : return String(T("lightsalmon"));
      case 0xff5f9ea0 : return String(T("cadetblue"));
      case 0xffbc8f8f : return String(T("rosybrown"));
      case 0xffda70d6 : return String(T("orchid"));
      default: break;
      }
    String h=T("#");
    int i;
    if ((i=color.getRed())<16) h<< T("0");
    h << String::toHexString(i);
    if ((i=color.getGreen())<16) h<< T("0");
    h << String::toHexString(i);
    if ((i=color.getBlue())<16) h<< T("0");
    h << String::toHexString(i);
    return h;
  }

  static const Colour fromHtmlColorString(String html, const Colour defc=Colours::black)
  {
    if (html.isQuotedString())
      html=html.unquoted();
    if (html.isEmpty())
      return defc;
    if (html[0]==T('#') )
      {
        String num=html.substring(1);
        if ((num.length()==6) && num.containsOnly(T("0123456789abcdefABCDEF")))
          {
            uint32 coln=0xff000000+num.getHexValue32();
            return Colour(coln);
          }
        else return defc;
      }
    else return Colours::findColourForName(html, defc);
  }

  static const String getColorThemeName (XmlElement* theme)
  {
    return theme->getStringAttribute(T("name"));
  }

  static const Colour getColorThemeColor (XmlElement* theme, const int id, const Colour defc=Colours::black)
  {
    return fromHtmlColorString(theme->getStringAttribute(toString(id)),defc);
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

  static const ExportID SalData = (TextIDs::Sal2 << SHIFT) + Data;
  static const ExportID SalSend = (TextIDs::Sal2 << SHIFT) + Send;
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
  static const int CodeEditor = 2;
  static const int PlotWindow = 3;
  static const int StateWindow = 4;
  static const bool isWindowType(TopLevelWindow* w, int typ)
  {
    if (w!=NULL)
      return (w->getProperties()[ var::identifier(T("WindowType")) ]==var(typ));
    // return (w->getComponentPropertyInt(T("WindowType"), false) == typ);
    else 
      return false;
  }
  static const void setWindowType(TopLevelWindow* w, int typ)
  {
    // w->setComponentProperty(T("WindowType"), typ);
    w->getProperties().set(var::identifier(T("WindowType")), var(typ));
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
  static const int Cells = 18;
  static const int Osc = 19;

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
  static const CommandID ConsoleIsEvaling     = COMID(Console, 133);

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
  static const CommandID EditorDelete = COMID(Editor, 18);
  static const CommandID EditorCut = COMID(Editor, 19);
  static const CommandID EditorCopy = COMID(Editor, 20);
  static const CommandID EditorPaste = COMID(Editor, 21);  
  static const CommandID EditorSelectAll = COMID(Editor, 22);
  static const CommandID EditorUnselectAll = COMID(Editor, 23);
  static const CommandID EditorFind = COMID(Editor, 24);
  static const CommandID EditorReplace = COMID(Editor, 25);

  static const CommandID EditorSyntax = COMID(Editor, 32);
  static const CommandID EditorFontSize = COMID(Editor, 33);
  static const CommandID EditorFontLarger = COMID(Editor, 34);
  static const CommandID EditorFontSmaller = COMID(Editor, 35);
  static const CommandID EditorParensMatching = COMID(Editor, 36);
  static const CommandID EditorEmacsMode = COMID(Editor, 37);
  static const CommandID EditorReadCustom = COMID(Editor, 38);
  static const CommandID EditorSaveCustom = COMID(Editor, 39);
  static const CommandID EditorTheme = COMID(Editor, 40);
  static const CommandID EditorDefaultFontSize = COMID(Editor, 41);
  static const CommandID EditorDefaultSyntax = COMID(Editor, 42);
  static const CommandID EditorDefaultTheme = COMID(Editor, 43);

  static const CommandID EditorExecute = COMID(Editor, 48);
  static const CommandID EditorExpand = COMID(Editor, 49);
  static const CommandID EditorIndent = COMID(Editor, 50);
  static const CommandID EditorCommentOut = COMID(Editor, 51);
  static const CommandID EditorUncommentOut = COMID(Editor, 52);
  static const CommandID EditorFormatComments = COMID(Editor, 53);
  static const CommandID EditorSymbolHelp = COMID(Editor, 54);

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

  static const CommandID MidiOutRecording = COMID(MidiOut, 10);
  static const CommandID MidiOutRecordingDelete = COMID(MidiOut, 11);
  static const CommandID MidiOutRecordingPlay = COMID(MidiOut, 12);
  static const CommandID MidiOutRecordingSave = COMID(MidiOut, 13);
  static const CommandID MidiOutRecordingImport = COMID(MidiOut, 14);

  // MidiIn Port
  static const CommandID MidiInOpen = COMID(MidiIn, 1);
  static const CommandID MidiInTrace = COMID(MidiIn, 2);
  static const CommandID MidiInChannelFilter = COMID(MidiIn, 3);
  static const CommandID MidiInOpcodeFilter = COMID(MidiIn, 4);
  static const CommandID MidiInConfigure = COMID(MidiIn, 5);
  static const CommandID MidiInImportFile = COMID(MidiIn, 6);
  static const CommandID MidiInThrough = COMID(MidiIn, 7);

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
  static const CommandID AudioSamplerSettings = COMID(Audio, 5);

  // SndLib
  static const CommandID SndLibSrate = COMID(SndLib, 1);
  static const CommandID SndLibChannels = COMID(SndLib, 2);
  static const CommandID SndLibAudioFormat = COMID(SndLib, 3);
  static const CommandID SndLibAutoPlay = COMID(SndLib, 4);
  static const CommandID SndLibInsDialog = COMID(SndLib, 5);
  static const CommandID SndLibAutoLoad = COMID(SndLib, 6);
  static const CommandID SndLibInsRestore = COMID(SndLib, 7);

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
  static const CommandID HelpGUI = COMID(Help, 3);
  static const CommandID HelpSalTutorial = COMID(Help, 4);
  static const CommandID HelpSchemeTutorial = COMID(Help, 5);
  static const CommandID HelpSalExample = COMID(Help, 6);
  static const CommandID HelpSchemeExample = COMID(Help, 7);
  static const CommandID HelpWebSite = COMID(Help, 8);
  static const CommandID HelpShowDirectory = COMID(Help, 9);

  static const CommandID HelpSalTutorialsRestore = COMID(Help, 10);  
  static const CommandID HelpSchemeTutorialsRestore = COMID(Help, 11);  
  static const CommandID HelpSalExamplesRestore = COMID(Help, 12);  
  static const CommandID HelpSchemeExamplesRestore = COMID(Help, 13);  

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

  static const CommandID StateWindowSetCells = COMID(Cells, 1);
  static const CommandID StateWindowSetCell = COMID(Cells, 2);
  static const CommandID StateWindowSetStatesAndColors = COMID(Cells, 2);
  static const CommandID StateWindowSetRowsAndColumns= COMID(Cells, 3);
  static const CommandID StateWindowSetCellSize= COMID(Cells, 4);

  // Osc commands

  static const CommandID OscOpen = COMID(Osc, 1);
  static const CommandID OscTraceInput = COMID(Osc, 2);
  static const CommandID OscTraceOutput = COMID(Osc, 3);
  static const CommandID OscShowStatus = COMID(Osc, 4);
  static const CommandID OscSetHook = COMID(Osc, 5);
  static const CommandID OscClearHook = COMID(Osc, 6);

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

class ChannelIDs
{
 public:
  static const int NumChannels = 4;
  static const int Mono = 0;  
  static const int Stereo = 1;  
  static const int Quad= 2;  
  static const int Eight = 3;  
  static const int toChannels(int id)
  {
    switch (id)
      {
      case Mono: return 1;
      case Stereo: return 2;
      case Quad: return 4;
      case Eight: return 8;
      default: return 1;
      }
  } 
  static const String toString(int id)
  {
    return String(toChannels(id));
  }
};

class AudioFormatIDs
{
 public:
  static const int NumAudioFormats = 3;
  static const int WAV = 0;
  static const int AIFF = 1;
  static const int SND = 2;
  static const String toString(int id)
  {
    switch (id)
      {
      case WAV: return String("WAV");
      case AIFF: return String("AIFF");
      case SND: return String("SND");
      default: 
        return String("No Audio Format");
      }
  }
};

class MidiValues
{
 public:
  static const int Empty = 0;
  static const int MidiValueTime = 1;
  static const int MidiValueDelta = 2;
  static const int MidiValueOp = 3;
  static const int MidiValueChannel = 4;
  static const int MidiValueRhythm = 5;
  static const int MidiValueDuration = 6;
  static const int MidiValueKeyNumber = 7;
  static const int MidiValueAmplitude = 8;
  static const int MidiValueVelocity = 9;
  static const int MidiValueTouch = 10;
  static const int MidiValueControlNumber = 11;
  static const int MidiValueControlValue = 12;
  static const int MidiValueProgram = 13;
  static const int MidiValuePressure = 14;
  static const int MidiValueBend = 15;
  // meta message values
  static const int MidiValueSeqNum = 16;
  static const int MidiValueText = 17;
  static const int MidiValueChanPrefix = 18;
  static const int MidiValueTempo = 19;
  static const int MidiValueTimeSig = 20;
  static const int MidiValueKeySig = 21;

  static const bool isOpForValue(int value, int op)
  {
    // return true if the message's opcode is valid for the midivalue
    // if 8<op<16 its a channel message (no offs) else its a meta message
    switch (value)
      {
        // all messages
      case MidiValueTime: 
      case MidiValueDelta:
      case MidiValueOp:            return true;
        // channel events
      case MidiValueChannel:       return ((op>0x08) && (op<0x0F)); // dont recognize offs
      case MidiValueRhythm:
      case MidiValueDuration:
      case MidiValueKeyNumber:
      case MidiValueAmplitude:
      case MidiValueVelocity:      return (op==0x9);
      case MidiValueTouch:         return (op==0xA);
      case MidiValueControlNumber:
      case MidiValueControlValue:  return (op==0xB);
      case MidiValueProgram:       return (op==0xC);
      case MidiValuePressure:      return (op==0xD);
      case MidiValueBend:          return (op==0xE);
        // meta events
      case MidiValueSeqNum:        return (op==0x00);
      case MidiValueText:          return ((op>0x00) && (op<0x08));
      case MidiValueChanPrefix:    return (op==0x20);
      case MidiValueTempo:         return (op==0x51);
      case MidiValueTimeSig:       return (op==0x58);
      case MidiValueKeySig:        return (op==0x59);
      default:                     return false;
      }      
  }
};

class TriggerIDs
{
 public:
  static const int Empty=0;
  static const int ButtonTrigger=1;
  static const int CounterTrigger=2;
  static const int SliderTrigger=3;
  static const int MidiKeyboardTrigger=4;
  static const int MidiInTrigger=5;
  static const int NumTriggers=5;
  static const String toString(int id)
  {
    switch (id)
      {
      case ButtonTrigger:
	return T("button");
      case CounterTrigger:
	return T("counter");
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
      case CounterTrigger:
	return  T("Counter");
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
    if (str.equalsIgnoreCase(T("counter")))
      return CounterTrigger;
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

class ScanIDs
{
 public:

  // Syntax Char Types
  enum 
  {
    SYN_WHITE = 1,
    SYN_WORD,
    SYN_SYMBOL,
    SYN_COMMENT, 
    SYN_PREFIX,
    SYN_STRING,
    SYN_OPEN,
    SYN_CLOSE,
    SYN_PUNCT,
    SYN_ESCAPE
  };

  // Scan Types
  static const int Empty=0;
  static const int MoveExpressions=1;
  static const int MoveTokens=2;
  static const int MoveWhiteAndComments=3;

  // Scan Results
  enum
  {
    SCAN_MISMATCH = -3,   // Shouldn't happen
    SCAN_UNMATCHED,
    SCAN_UNLEVEL,
    SCAN_EMPTY,    // must be zero
    SCAN_TOKEN,
    SCAN_STRING,
    SCAN_LIST,
    SCAN_COMMENT,
    SCAN_OPEN,
    SCAN_CLOSE,
    SCAN_PUNCT
  };
  static const String scanResultToString(int res)
  {
    switch (res)
      {
      case SCAN_MISMATCH: return T("mismatch");
      case SCAN_UNMATCHED: return T("unmatched");
      case SCAN_UNLEVEL: return T("unlevel");
      case SCAN_EMPTY: return T("empty");
      case SCAN_TOKEN: return T("token");
      case SCAN_STRING: return T("string");
      case SCAN_LIST: return T("list");
      case SCAN_COMMENT: return T("comment");
      case SCAN_OPEN: return T("open");
      case SCAN_CLOSE: return T("close");
      case SCAN_PUNCT: return T("puctuation");
      default: return T("unknown");
      }
  }
};

class SalIDs
{
 public:
  enum SalTypeData // Type data (encoded in lower 8 bits)
  {
    // generated by (sal-enums )
    SalBlockOpen = 0x10,
    SalBlockClose = 0x11
  };

  enum SalTypes 
  {
    // generated by (sal-enums )
    SalUntyped = 0x0,
    SAL_TOKEN_BEG = 0x0,
    SAL_DELIM_BEG = 0x0,
    SalComma = 0x100,
    SalLParen = 0x200,
    SalRParen = 0x300,
    SalLCurly = 0x400,
    SalRCurly = 0x500,
    SalLBrace = 0x600,
    SalRBrace = 0x700,
    SAL_DELIM_END = 0x800,
    SAL_DATA_BEG = 0x800,
    SalString = 0x900,
    SAL_NUMBER_BEG = 0xa00,
    SalInteger = 0xb00,
    SalRatio = 0xc00,
    SalFloat = 0xd00,
    SAL_NUMBER_END = 0xe00,
    SalKeyword = 0xf00,
    SAL_BOOL_BEG = 0x1000,
    SAL_HASH_BEG = 0x1000,
    SalTrue = 0x1100,
    SalFalse = 0x1200,
    SAL_BOOL_END = 0x1300,
    SalQMark = 0x1400,
    SalUnquote = 0x1500,
    SalSplice = 0x1600,
    SAL_HASH_END = 0x1700,
    SAL_DATA_END = 0x1700,
    SalKeyparam = 0x1800,
    SalClass = 0x1900,
    SAL_OP_BEG = 0x1a00,
    SalPlus = 0x1b05,
    SalMinus = 0x1c05,
    SalTimes = 0x1d06,
    SalDivide = 0x1e06,
    SalMod = 0x1f05,
    SalExpt = 0x2007,
    SalAnd = 0x2102,
    SalOr = 0x2201,
    SalNot = 0x2303,
    SAL_RELATION_BEG = 0x2400,
    SalLess = 0x2504,
    SalGreater = 0x2604,
    SalNotEqual = 0x2704,
    SalGeneralEqual = 0x2804,
    SAL_ASSIGNMENT_BEG = 0x2900,
    SalEqual = 0x2a04,
    SalLessEqual = 0x2b04,
    SalGreaterEqual = 0x2c04,
    SAL_RELATION_END = 0x2d00,
    SAL_OP_END = 0x2d00,
    SalInc = 0x2e00,
    SalMul = 0x2f00,
    SalCol = 0x3000,
    SalPre = 0x3100,
    SalApp = 0x3200,
    SAL_ASSIGNMENT_END = 0x3300,
    SAL_LITERAL_BEG = 0x3300,
    SAL_STATEMENT_BEG = 0x3300,
    SAL_COMMAND_BEG = 0x3300,
    SalBegin = 0x3410,
    SalChdir = 0x3500,
    SalDefine = 0x3600,
    SalExec = 0x3700,
    SalIf = 0x3800,
    SalLoad = 0x3900,
    SalLoop = 0x3a10,
    SalPlot = 0x3b00,
    SalPrint = 0x3c00,
    SalRun = 0x3d10,
    SalSend = 0x3e00,
    SalSet = 0x3f00,
    SalSoundFile = 0x4010,
    SalFomusFile = 0x4110,
    SalSprout = 0x4200,
    Sal2Variable = 0x4300,
    Sal2Function = 0x4410,
    Sal2Process = 0x4510,
    Sal2If = 0x4610,
    Sal2File = 0x4710,
    Sal2Wait = 0x4800,
    SAL_COMMAND_END = 0x4900,
    SAL_CONSTITUENT_BEG = 0x4900,
    SalElse = 0x4a00,
    SalEnd = 0x4b11,
    SalReturn = 0x4c00,
    SalThen = 0x4d00,
    SalUnless = 0x4e00,
    SalUntil = 0x4f00,
    SalWait = 0x5000,
    SalWhen = 0x5100,
    SalWhile = 0x5200,
    SalWith = 0x5300,
    SalOptKey = 0x5400,
    SAL_CONSTITUENT_END = 0x5500,
    SAL_STATEMENT_END = 0x5500,
    SAL_CLAUSAL_BEG = 0x5500,
    SalAbove = 0x5600,
    SalBelow = 0x5700,
    SalBy = 0x5800,
    SalDownto = 0x5900,
    SalFinally = 0x5a00,
    SalFor = 0x5b00,
    SalFrom = 0x5c00,
    SalIn = 0x5d00,
    SalOver = 0x5e00,
    SalRepeat = 0x5f00,
    SalTo = 0x6000,
    SAL_CLAUSAL_END = 0x6100,
    SAL_LITERAL_END = 0x6100,
    SAL_DEFINE_BEG = 0x6100,
    SalFunction = 0x6200,
    SalProcess = 0x6300,
    SalVariable = 0x6400,
    SAL_DEFINE_END = 0x6500,
    SAL_IDENTIFIER_BEG = 0x6500,
    SalIdentifier = 0x6600,
    SalSlotRef = 0x6700,
    SAL_IDENTIFIER_END = 0x6800,
    SAL_TOKEN_END = 0x6800,
    SAL_RULE_BEG = 0x6800,
    SalNumberRule = 0x6900,
    SalBoolRule = 0x6a00,
    SalAtomRule = 0x6b00,
    SalListRule = 0x6c00,
    SalEltRule = 0x6d00,
    SalArefRule = 0x6e00,
    SalIfExprRule = 0x6f00,
    SalUnquoteRule = 0x7000,
    SalFuncallRule = 0x7100,
    SalFunargsRule = 0x7200,
    SalPargsRule = 0x7300,
    SalKargsRule = 0x7400,
    SalOpRule = 0x7500,
    SalMexprRule = 0x7600,
    SalTermRule = 0x7700,
    SalSexprRule = 0x7800,
    SalBindingsRule = 0x7900,
    SalBindRule = 0x7a00,
    SalAssignmentRule = 0x7b00,
    SalAssignRule = 0x7c00,
    SalAssignerRule = 0x7d00,
    SalSetRule = 0x7e00,
    SalFunctionReturnRule = 0x7f00,
    SalProcessWaitRule = 0x8000,
    SalBlockRule = 0x8100,
    SalConditionalRule = 0x8200,
    SalLoopStatementRule = 0x8300,
    SalRunStatementRule = 0x8400,
    SalSteppingRule = 0x8500,
    SalTerminationRule = 0x8600,
    SalPrintStatementRule = 0x8700,
    SalExecStatementRule = 0x8800,
    SalSendStatementRule = 0x8900,
    SalSoundFileStatementRule = 0x8a00,
    SalFomusFileStatementRule = 0x8b00,
    SalSproutStatementRule = 0x8c00,
    SalLoadStatementRule = 0x8d00,
    SalChdirStatementRule = 0x8e00,
    SalPlotStatementRule = 0x8f00,
    SalDefineStatementRule = 0x9000,
    SalStatementRule = 0x9100,
    SalStatementSequenceRule = 0x9200,
    SalDeclarationRule = 0x9300,
    SalVarDeclRule = 0x9400,
    SalFunDeclRule = 0x9500,
    SalProcDeclRule = 0x9600,
    SalProcessBodyRule = 0x9700,
    Sal2FormalsRule = 0x9800,
    Sal2BeginStatementRule = 0x9900,
    Sal2IfStatementRule = 0x9a00,
    Sal2FunctionStatementRule = 0x9b00,
    Sal2VariableStatementRule = 0x9c00,
    Sal2WithStatementRule = 0x9d00,
    Sal2LoopStatementRule = 0x9e00,
    Sal2ProcessStatementRule = 0x9f00,
    Sal2ProcessWaitRule = 0xa000,
    Sal2FileStatementRule = 0xa100,
    Sal2StatementRule = 0xa200,
    Sal2StatementSequenceRule = 0xa300,
    SAL_RULE_END = 0xa400,
    SAL_TYPE_END = 0xa400
  };

  // sal tokenizer values
  static const int TokenError = 0;
  static const int TokenPlaintext = 1;
  static const int TokenComment = 2;
  static const int TokenString = 3;
  static const int TokenSharpSign = 4;
  static const int TokenLispKeyword = 5;
  static const int TokenSalKeyword = 6;
  static const int TokenSalReserved = 7;
  static const int TokenSalClassname = 8;
  static const int TokenSalCommand = 9;

  static const bool isSalType(int i) {return (0x100 <= i) && (i < SAL_TYPE_END);}
  static const bool isSalTokenType(int i) {return (SAL_TOKEN_BEG < i) && (i < SAL_TOKEN_END);}
  static const bool isSalDelimType(int i) {return (SAL_DELIM_BEG < i) && (i < SAL_DELIM_END);}
  static const bool isSalNumberType(int i) {return (SAL_NUMBER_BEG < i) && (i < SAL_NUMBER_END);}
  static const bool isSalBoolType(int i) {return (SAL_BOOL_BEG < i) && (i < SAL_BOOL_END);}
  static const bool isSalOpType(int i) {return (SAL_OP_BEG < i) && (i < SAL_OP_END);}
  static const int  salOpWeight(int i) {return (i & 0xFF);}
  static const bool isSalRelationType(int i) {return (SAL_RELATION_BEG < i) && (i < SAL_RELATION_END);}
  static const bool isSalAssignmentType(int i) {return (SAL_ASSIGNMENT_BEG < i) && (i < SAL_ASSIGNMENT_END);}
  static const bool isSalLiteralType(int i) {return (SAL_LITERAL_BEG < i) && (i < SAL_LITERAL_END);}
  static const bool isSalDefineType(int i) {return (SAL_DEFINE_BEG < i) && (i < SAL_DEFINE_END);}
  static const bool isSalStatementType(int i) {return (SAL_STATEMENT_BEG < i) && (i < SAL_STATEMENT_END);}
  static const bool isSalCommandType(int i) {return (SAL_COMMAND_BEG < i) && (i < SAL_COMMAND_END);}
  static const bool isSalConstituentType(int i) {return (SAL_CONSTITUENT_BEG < i) && (i < SAL_CONSTITUENT_END);}
  static const bool isSalClausalType(int i) {return (SAL_CONSTITUENT_BEG < i) && (i < SAL_CLAUSAL_END);}
  static const bool isSalRuleType(int i) {return (SAL_RULE_BEG < i) && (i < SAL_RULE_END);}
  static const bool isSalTypeEqual( int a, int b) {return ((a >> 8) == (b >> 8));}
  static const int  SalTypeDataBits(int t) {return (t & 0xff);}
  static const bool isSalBlockOpen(int t) {return SalTypeDataBits(t)==SalBlockOpen;}
  static const bool isSalBlockClose(int t) {return SalTypeDataBits(t)==SalBlockClose;}
};

#endif
