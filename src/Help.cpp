/*=======================================================================*
  Copyright (c) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify
  it under the terms of the Lisp Lesser Gnu Public License. The text
  of this agreement is available at http://www.cliki.net/LLGPL
 *=======================================================================*/

#include "Enumerations.h"
#include "Help.h"
#include "Console.h"
//#include "TextEditor.h"
#include "CodeEditor.h"
#include "Documentation.h"
#include "Preferences.h"
#include "Resources.h"
#include <iostream>

juce_ImplementSingleton (Help) ;

Help::Help()
  : docTable(0),
    cminsdir (File::nonexistent),
    cmdocdir (File::nonexistent)
{
  // Create Help Table
  XmlDocument dataDoc (String((const char*)Resources::doc_xml)); 
  docTable=dataDoc.getDocumentElement();

  // locate Grace directory, include version info in name
  cmdocdir=File::getSpecialLocation(File::userApplicationDataDirectory).
    getChildFile(SysInfo::getApplicationName()+T("/")+SysInfo::getGraceVersion()+T("/doc/"));

  // create Symbol help
  addSalSymbolHelp();
  addCommonMusicSymbolHelp();
  addSndLibSymbolHelp();
  addSchemeSymbolHelp();
 
  restoreHelpFiles();
}

Help::~Help()
{
  deleteAndZero(docTable);
  roots.clear();
  sal.clear();
  cm.clear();
  scheme.clear();
  clearSingletonInstance();
}

String Help::getHelpFileText(String filename)
{
  MemoryInputStream zipstream (Resources::doc_zip,
                               Resources::doc_zipSize,
                               false);
  ZipFile archive (&zipstream, false);
  String text=String::empty;
  InputStream* inst=NULL;
  int index=archive.getIndexOfFileName(filename);
  if (index>=0)
    inst=archive.createStreamForEntry(index);
  if (inst)
    {
      text << inst->readEntireStreamAsString();
      delete inst;
    }
  inst=NULL;
  return text;
}

void Help::restoreHelpFiles()
{
  using namespace Documentation;
  File htm=cmdocdir.getChildFile(T("cm.html"));
  File css=cmdocdir.getChildFile(T("cm.css"));
  File log=cmdocdir.getChildFile(T("changelog.html"));
  if (!cmdocdir.isDirectory())
    if (!cmdocdir.createDirectory())
      {
	Console::getInstance()->printWarning(T("Warning: couldn't restore documents to ") + cmdocdir.getFullPathName() + T("\n"));
	return;
      }
  if (!htm.replaceWithText(getHelpFileText(T("cm.html"))))
    Console::getInstance()->printWarning(T("Warning: couldn't restore ") + htm.getFullPathName() + T("\n"));
  if (!css.replaceWithText(getHelpFileText(T("cm.css"))))
    Console::getInstance()->printWarning(T("Warning: couldn't restore ") + css.getFullPathName() + T("\n"));
  if (!log.replaceWithText(getHelpFileText(T("changelog.html"))))
    Console::getInstance()->printWarning(T("Warning: couldn't restore ") + log.getFullPathName() + T("\n"));
}
  
XmlElement* Help::getXmlMenu(String title)
{
  forEachXmlChildElementWithTagName(*docTable, menu, T("menu"))
    {
      if (menu->getStringAttribute(T("name"))==title)
        return menu;
    }
  return NULL;
}

XmlElement* Help::getXmlMenuItem(String title, int index)
{
  XmlElement* menu=getXmlMenu(title);
  return (menu) ? menu->getChildElement(index) : NULL;
}

void Help::addHelpMenuItems(PopupMenu& menu, String menuname, CommandID cmdid, int maxitems, ApplicationCommandManager* manager)
{
  XmlElement* xmlmenu=getXmlMenu(menuname);
  if (!xmlmenu) return ;

  int i=0;
  forEachXmlChildElement(*xmlmenu, xmlitem)
    {
      if (i<maxitems)
        {
          menu.addCommandItem(manager, cmdid + i, xmlitem->getStringAttribute(T("name")));
          i++;
        }
    }
}

void Help::openHelp(CommandID id)
{
  int comm=CommandIDs::getCommand(id);
  int data=CommandIDs::getCommandData(id);
  XmlElement* help=NULL;
  if (comm==CommandIDs::HelpManual)
    {
      if (help=getXmlMenuItem(T("Manuals"), data))
        {
          String url=help->getStringAttribute(T("url"));
          openHelpInBrowser(url);
        }
    }
  else if (comm==CommandIDs::HelpWebSite)
    {
      if (help=getXmlMenuItem(T("Web Sites"), data))
        {
          String url=help->getStringAttribute(T("url"));
          openHelpInBrowser(url);
        }
    }
  else if (comm==CommandIDs::HelpSalExample)
    {
      if (help=getXmlMenuItem(T("Sal Examples"), data))
        {
          String file=help->getStringAttribute(T("file"));
          openHelpInEditor(file, getHelpFileText(file));
        }
    }
  else if (comm==CommandIDs::HelpSchemeExample)
    {
      if (help=getXmlMenuItem(T("Scheme Examples"), data))
        {
          String file=help->getStringAttribute(T("file"));
          openHelpInEditor(file, getHelpFileText(file));
        }
    }
  else if (comm==CommandIDs::HelpSalTutorial)
    {
      if (help=getXmlMenuItem(T("Sal Tutorials"), data))
        {
          String file=help->getStringAttribute(T("file"));
          openHelpInEditor(file, getHelpFileText(file));
        }
    }
  else if (comm==CommandIDs::HelpSchemeTutorial)
    {
      if (help=getXmlMenuItem(T("Scheme Tutorials"), data))
        {
          String file=help->getStringAttribute(T("file"));
          openHelpInEditor(file, getHelpFileText(file));
        }
    }
}

void Help::openHelpInBrowser(String url)
{
  // a local url to the resourced document directory
  if (url.startsWith(T("$DOCDIR:")))
    {
      url=url.replaceSection(0, 8, T("file://")+cmdocdir.getFullPathName());
    }
  if (url.startsWith(T("file:")))
    { 
      if (false) //(SysInfo::isLinux())
	{
	  File fox=File(T("/usr/bin/firefox"));
	  if (fox.existsAsFile())
	    fox.startAsProcess(url.quoted());
	  else
	    {
	      String msg=T(">> Error: Can't open local html help file because /usr/bin/firefox does not exist.");
	      Console::getInstance()->printWarning(msg);
	    }
	}
      else if (SysInfo::isWindows())
	{
	  // Chrome lives in a weird place in the application data directory.
	  String chromePath = File::getSpecialLocation(File::userDesktopDirectory).getFullPathName();
	  // Trim out "Desktop" from the path name to get the user directory...
	  chromePath = chromePath.substring(0, chromePath.length() - 8);
	  chromePath << "\\Local Settings\\Application Data\\";
	  chromePath << "Google\\Chrome\\Application\\chrome.exe";
	  //Web browser executables
	  File ie("C:\\Program Files\\Internet Explorer\\iexplore.exe");
	  File firefox("C:\\Program Files\\Mozilla Firefox\\firefox.exe");
	  File chrome(chromePath);
	  //Try each web browser until something works (priority: Firefox, Chrome, IE).
	  if (firefox.exists())
	    firefox.startAsProcess(url.quoted());
	  else if (chrome.exists())
	    chrome.startAsProcess(url.quoted());
	  else if (ie.exists())
	    ie.startAsProcess(url.quoted());
	  else
	    {
	      String msg=T("Can't open local html help file because none of these browsers exist:\n");
	      msg << T("\n  ") << firefox.getFullPathName()
		  << T("\n  ") << chrome.getFullPathName()
		  << T("\n  ") << ie.getFullPathName() << T("\n");
	      Console::getInstance()->printWarning(msg);
	    }
	}
      else
	URL(url).launchInDefaultBrowser();
    }
  else
    {
      URL(url).launchInDefaultBrowser();
    }
}

void Help::openHelpInEditor(String path, String code)
{
  int ttyp=TextIDs::fromFileType(path.fromLastOccurrenceOf(T("."), true, true));
  new CodeEditorWindow(File::nonexistent, code, ttyp, path);
}

void Help::restoreToDirectory(CommandID command)
{
  String title=T("Choose Directory for ");
  String name;
  switch (command)
    {
    case CommandIDs::HelpSalTutorialsRestore:
      name=T("Sal Tutorials");
      title << T("Tutorials");
      break;
    case CommandIDs::HelpSchemeTutorialsRestore:
      name=T("Scheme Tutorials");
      title << T("Tutorials");
      break;
    case CommandIDs::HelpSalExamplesRestore:
      name=T("Sal Examples");
      title << T("Examples");
      break;
    case CommandIDs::HelpSchemeExamplesRestore:
      name=T("Scheme Examples");
      title << T("Examples");
      break;
    default:
      return;
    }

  XmlElement* menu=getXmlMenu(name);
  if (!menu) return;
  FileChooser chooser (title, File::getSpecialLocation (File::userHomeDirectory));
  if (!chooser.browseForDirectory() )
    return;
  File directory (chooser.getResult());
  forEachXmlChildElement(*menu, item)
    {
      String file=item->getStringAttribute(T("file"));
      String text=getHelpFileText(file);
      directory.getChildFile(file).replaceWithText(text);
    }
  Console::getInstance()->printOutput(name + T(" saved in ") + directory.getFullPathName() + T(".\n"));
}

/*=======================================================================*
                               Symbol Help
 *=======================================================================*/

void Help::symbolHelp(String symbol, String helppath)
{
  //std::cout << "symbolHelp: '" << symbol.toUTF8() << "' (\""
  //<< helppath.toUTF8() << "\")\n";

  // search for symbol help in colon delimited help path.
  int i, p=0, l=helppath.length();
  String s, h, r, x;
  while (helppath != String::empty)
    {
      x=String::empty;
      i=helppath.indexOfChar(':');
      if (i==-1) 
	{
	  h=helppath;
	  helppath=String::empty;
	}
      else 
	{
	  h=helppath.substring(0,i);
	  helppath=helppath.substring(i+1);
	}
      if (h==T("Sal"))
	x=sal[symbol];
      else if (h==T("CM"))
	x=cm[symbol];
      else if (h==T("SndLib"))
	x=clm[symbol];
      else if (h==T("Scheme"))
	x=scheme[symbol];
      else
	return;
      if (x!=String::empty)
	{
	  //	  openHelp(roots[h] + x);
	  openHelpInBrowser(roots[h] + x);
	  return;
	}
    }
}

void Help::addSalSymbolHelp()
{
  roots.set(T("Sal"), T("file://")+cmdocdir.getFullPathName()+T("/"));
  sal.set(T("begin"), T("cm.html#begin"));
  sal.set(T("chdir"), T("cm.html#chdir"));
  sal.set(T("define"), T("cm.html#define"));
  sal.set(T("end"), T("cm.html#begin"));
  sal.set(T("exec"), T("cm.html#exec"));
  sal.set(T("if"), T("cm.html#if"));
  sal.set(T("load"), T("cm.html#load"));
  sal.set(T("loop"), T("cm.html#loop"));
  sal.set(T("print"), T("cm.html#print"));
  sal.set(T("return"), T("cm.html#return"));
  sal.set(T("run"), T("cm.html#run"));
  sal.set(T("send"), T("cm.html#send"));
  sal.set(T("set"), T("cm.html#set"));
  sal.set(T("="), T("cm.html#set"));
  sal.set(T("&="), T("cm.html#set"));
  sal.set(T("^="), T("cm.html#set"));
  sal.set(T("*="), T("cm.html#set"));
  sal.set(T("+="), T("cm.html#set"));
  sal.set(T(">="), T("cm.html#set"));
  sal.set(T("<="), T("cm.html#set"));
  sal.set(T("sprout"), T("cm.html#sprout"));
  sal.set(T("unless"), T("cm.html#unless"));
  sal.set(T("wait"), T("cm.html#run"));
  sal.set(T("while"), T("cm.html#loop"));
  sal.set(T("until"), T("cm.html#loop"));
  sal.set(T("when"), T("cm.html#loop"));
  sal.set(T("with"), T("cm.html#loop"));
}

void Help::addCommonMusicSymbolHelp() 
{
  roots.set(T("CM"), T("file://")+cmdocdir.getFullPathName()+T("/"));
  cm.set(T("between"), T("cm.html#between"));
  cm.set(T("butlast"), T("cm.html#butlast"));
  cm.set(T("cell-state"), T("cm.html#cell-state"));
  cm.set(T("cents->ratio"), T("cm.html#cents-_ratio"));
  cm.set(T("chdir"), T("cm.html#chdir"));
  cm.set(T("cont"), T("cm.html#cont"));
  cm.set(T("concat"), T("cm.html#concat"));
  cm.set(T("cs:i"), T("cm.html#cs:i"));
  cm.set(T("cs:f"), T("cm.html#cs:f"));
  cm.set(T("cs:clear"), T("cm.html#cs:clear"));
  cm.set(T("cwd"), T("cm.html#cwd"));
  cm.set(T("decimals"), T("cm.html#decimals"));
  cm.set(T("discrete"), T("cm.html#discrete"));
  cm.set(T("divide"), T("cm.html#divide"));
  cm.set(T("drunk"), T("cm.html#drunk"));
  cm.set(T("eighth"), T("cm.html#eighth"));
  cm.set(T("eod?"), T("cm.html#eod_"));
  cm.set(T("eop?"), T("cm.html#eop_"));
  cm.set(T("elapsed"), T("cm.html#elapsed"));
  cm.set(T("fifth"), T("cm.html#fifth"));
  cm.set(T("first"), T("cm.html#first"));
  cm.set(T("fit"), T("cm.html#fit"));
  cm.set(T("float"), T("cm.html#float"));
  cm.set(T("fm-spectrum"), T("cm.html#fm-spectrum"));

  cm.set(T("fms:note"), T("cm.html#fms:note"));
  cm.set(T("fms:rest"), T("cm.html#fms:rest"));
  cm.set(T("fms:mark"), T("cm.html#fms:mark"));
  cm.set(T("fms:meas"), T("cm.html#fms:meas"));
  cm.set(T("fms:part"), T("cm.html#fms:part"));
  cm.set(T("fms:inst"), T("cm.html#fms:inst"));
  cm.set(T("fms:percinst"), T("cm.html#fms:percinst"));
  cm.set(T("fms:metapart"), T("cm.html#fms:metapart"));
  cm.set(T("fms:setting"), T("cm.html#fms:setting"));
  cm.set(T("fms:measdef"), T("cm.html#fms:measdef"));
  cm.set(T("fms:new-score"), T("cm.html#fms:new-score"));
  cm.set(T("fms:load-score"), T("cm.html#fms:load-score"));
  cm.set(T("fms:select-score"), T("cm.html#fms:select-score"));
  cm.set(T("fms:run-score"), T("cm.html#fms:run-score"));
  cm.set(T("fms:save-score"), T("cm.html#fms:save-score"));
  cm.set(T("fms:clear-score"), T("cm.html#fms:clear-score"));
  cm.set(T("fms:delete-score"), T("cm.html#fms:delete-score"));

  cm.set(T("fourth"), T("cm.html#fourth"));
  cm.set(T("hz"), T("cm.html#hz"));
  //  cm.set(T("hush"), T("cm.html#hush"));
  cm.set(T("int"), T("cm.html#int"));
  cm.set(T("import-spear-frames"), T("cm.html#import-spear-frames"));
  cm.set(T("key"), T("cm.html#key"));
  cm.set(T("interp"), T("cm.html#interp"));
  cm.set(T("invert"), T("cm.html#ivert"));
  cm.set(T("last"), T("cm.html#last"));
  cm.set(T("list-set!"), T("cm.html#list-set_"));
  cm.set(T("log2"), T("cm.html#log2"));
  cm.set(T("log10"), T("cm.html#log10"));
  cm.set(T("loop"), T("cm.html#loop"));
  cm.set(T("make-automata"), T("cm.html#make-automata"));
  cm.set(T("make-cycle"), T("cm.html#make-cycle"));
  cm.set(T("make-graph"), T("cm.html#make-graph"));
  cm.set(T("make-heap"), T("cm.html#make-heap"));
  cm.set(T("make-line"), T("cm.html#make-line"));
  //  cm.set(T("make-list"), T("cm.html#make-list"));
  cm.set(T("make-markov"), T("cm.html#make-markov"));
  cm.set(T("make-palindrome"), T("cm.html#make-palindrome"));
  cm.set(T("make-repeater"), T("cm.html#make-repeater"));
  cm.set(T("make-rotation"), T("cm.html#make-rotation"));
  cm.set(T("make-spectrum"), T("cm.html#make-spectrum"));
  cm.set(T("make-weighting"), T("cm.html#make-weighting"));
  cm.set(T("markov-analyze"), T("cm.html#markov-analyze"));
  cm.set(T("minus"), T("cm.html#minus"));
  cm.set(T("mm:bend?"), T("cm.html#mm:bend_"));
  cm.set(T("mm:ctrl?"), T("cm.html#mm:ctrl_"));
  cm.set(T("mm:prog?"), T("cm.html#mm:prog_"));
  cm.set(T("mm:press?"), T("cm.html#mm:press_"));
  cm.set(T("mm:off?"), T("cm.html#mm:off_"));
  cm.set(T("mm:on?"), T("cm.html#mm:on_"));
  cm.set(T("mm:touch?"), T("cm.html#mm:touch_"));
  cm.set(T("mm:chan"), T("cm.html#mm:chan"));
  cm.set(T("mm:chan-set!"), T("cm.html#mm:chan-set_"));
  cm.set(T("mm:key"), T("cm.html#mm:key"));
  cm.set(T("mm:key-set!"), T("cm.html#mm:key-set_"));
  cm.set(T("mm:num"), T("cm.html#mm:num"));
  cm.set(T("mm:num-set!"), T("cm.html#mm:num-set_"));
  cm.set(T("mm:time"), T("cm.html#mm:time"));
  cm.set(T("mm:time-set!"), T("cm.html#mm:time-set_"));
  cm.set(T("mm:val"), T("cm.html#mm:val"));
  cm.set(T("mm:val-set!"), T("cm.html#mm:val-set_"));
  cm.set(T("mm:vel"), T("cm.html#mm:vel"));
  cm.set(T("mm:vel-set!"), T("cm.html#mm:vel-set_"));
  cm.set(T("mm:make-bend"), T("cm.html#mm:make-bend"));
  cm.set(T("mm:make-ctrl"), T("cm.html#mm:make-ctrl"));
  cm.set(T("mm:make-prog"), T("cm.html#mm:make-prog"));
  cm.set(T("mm:make-press"), T("cm.html#mm:make-press"));
  cm.set(T("mm:make-off"), T("cm.html#mm:make-off"));
  cm.set(T("mm:make-on"), T("cm.html#mm:make-on"));
  cm.set(T("mm:make-touch"), T("cm.html#mm:make-touch"));
  cm.set(T("most-positive-fixnum"), T("cm.html#most-positive-fixnum"));
  cm.set(T("most-negative-fixnum"), T("cm.html#most-negative-fixnum"));
  cm.set(T("mp:midi"), T("cm.html#mp:midi"));
  cm.set(T("mp:on"), T("cm.html#mp:on"));
  cm.set(T("mp:off"), T("cm.html#mp:off"));
  cm.set(T("mp:prog"), T("cm.html#mp:prog"));
  cm.set(T("mp:crtl"), T("cm.html#mp:ctrl"));
  cm.set(T("mp:alloff"), T("cm.html#mp:alloff"));
  cm.set(T("mp:inhook"), T("cm.html#mp:inhook"));
  cm.set(T("multiply"), T("cm.html#multiply"));
  cm.set(T("next"), T("cm.html#next"));
  cm.set(T("ninth"), T("cm.html#ninth"));
  cm.set(T("nth"), T("cm.html#nth"));
  cm.set(T("now"), T("cm.html#now"));
  cm.set(T("note"), T("cm.html#note"));
  cm.set(T("note?"), T("cm.html#note_"));
  cm.set(T("odds"), T("cm.html#odds"));
  cm.set(T("osc:close"), T("cm.html#osc:close"));
  cm.set(T("osc:hook"), T("cm.html#osc:hook"));
  cm.set(T("osc:message"), T("cm.html#osc:message"));
  cm.set(T("osc:open"), T("cm.html#osc:open"));

  cm.set(T("pause"), T("cm.html#pause"));
  cm.set(T("pc"), T("cm.html#pc"));
  cm.set(T("pi"), T("cm.html#pi"));
  cm.set(T("pick"), T("cm.html#pick"));
  cm.set(T("plot"), T("cm.html#plot"));
  cm.set(T("plot-data"), T("cm.html#plot-data"));
  cm.set(T("plot-hook"), T("cm.html#plot-hook"));
  cm.set(T("plus"), T("cm.html#plus"));
  cm.set(T("promise"), T("cm.html#promise"));
  cm.set(T("quantize"), T("cm.html#quantize"));
  cm.set(T("ran"), T("cm.html#ran"));
  cm.set(T("ranbeta"), T("cm.html#ranbeta"));
  cm.set(T("ranbrown"), T("cm.html#ranbrown"));
  cm.set(T("ranchauchy"), T("cm.html#ranchauchy"));
  cm.set(T("ranexp"), T("cm.html#ranexp"));
  cm.set(T("rangamma"), T("cm.html#rangamma"));
  cm.set(T("rangauss"), T("cm.html#rangauss"));
  cm.set(T("ranhigh"), T("cm.html#ranhigh"));
  cm.set(T("ranlow"), T("cm.html#ranlow"));
  cm.set(T("ranmid"), T("cm.html#ranmid"));
  cm.set(T("ranpink"), T("cm.html#ranpink"));
  cm.set(T("ranpoisson"), T("cm.html#ranpoisson"));
  cm.set(T("ran-set!"), T("cm.html#ran-set_"));
  cm.set(T("ratio->cents"), T("cm.html#ratio-_cents"));
  cm.set(T("rescale"), T("cm.html#rescale"));
  cm.set(T("rest"), T("cm.html#rest"));
  cm.set(T("retrograde"), T("cm.html#retrograde"));
  cm.set(T("rm-spectrum"), T("cm.html#rm-spectrum"));
  cm.set(T("run"), T("cm.html#run"));

  cm.set(T("scale"), T("cm.html#scale"));
  cm.set(T("scale-order"), T("cm.html#scale-order"));
  cm.set(T("second"), T("cm.html#second"));
  cm.set(T("segs"), T("cm.html#segs"));
  cm.set(T("send"), T("cm.html#send"));
  cm.set(T("seventh"), T("cm.html#seventh"));
  cm.set(T("shuffle"), T("cm.html#shuffle"));  
  cm.set(T("sixth"), T("cm.html#sixth"));  
  cm.set(T("sort"), T("cm.html#sort"));
  cm.set(T("sort!"), T("cm.html#sort_"));
  cm.set(T("spectrum-add!"), T("cm.html#spectrum-add_"));  
  cm.set(T("spectrum-copy"), T("cm.html#spectrum-copy"));
  cm.set(T("spectrum-flip!"), T("cm.html#spectrum-flip_"));  
  cm.set(T("spectrum-freqs"), T("cm.html#spectrum-freqs"));  
  cm.set(T("spectrum-invert!"), T("cm.html#spectrum-invert_"));  
  cm.set(T("spectrum-keys"), T("cm.html#spectrum-keys"));  
  cm.set(T("spectrum-maxamp"), T("cm.html#spectrum-maxamp"));  
  cm.set(T("spectrum-maxfreq"), T("cm.html#spectrum-maxfreq"));  
  cm.set(T("spectrum-minamp"), T("cm.html#spectrum-minamp"));  
  cm.set(T("spectrum-minfreq"), T("cm.html#spectrum-minfreq"));  
  cm.set(T("spectrum-pairs"), T("cm.html#spectrum-pairs"));  
  cm.set(T("spectrum-rescale!"), T("cm.html#spectrum-rescale_"));  
  cm.set(T("spectrum-size"), T("cm.html#spectrum-size"));  
  cm.set(T("spectrum-time"), T("cm.html#spectrum-time"));  
  cm.set(T("sprout"), T("cm.html#sprout"));
  cm.set(T("state"), T("cm.html#state"));
  cm.set(T("stop"), T("cm.html#stop"));
  cm.set(T("times"), T("cm.html#times"));
  cm.set(T("tail"), T("cm.html#tail"));
  cm.set(T("tendency"), T("cm.html#tendency"));
  cm.set(T("tenth"), T("cm.html#tenth"));
  cm.set(T("third"), T("cm.html#third"));
  cm.set(T("transpose"), T("cm.html#transpose"));
  cm.set(T("unique"), T("cm.html#unique"));
  cm.set(T("vary"), T("cm.html#vary"));
  cm.set(T("wait"), T("cm.html#wait"));
  cm.set(T("xy"), T("cm.html#xy"));
}

void Help::addSchemeSymbolHelp() 
{
  roots.set(T("Scheme"), T("http://www.schemers.org/Documents/Standards/R5RS/HTML/"));
  scheme.set(T("*"), T("r5rs-Z-H-9.html#%25_idx_280"));
  scheme.set(T("+"), T("r5rs-Z-H-9.html#%25_idx_278"));
  scheme.set(T("-"), T("r5rs-Z-H-9.html#%25_idx_282"));
  scheme.set(T("/"), T("r5rs-Z-H-9.html#%25_idx_284"));
  scheme.set(T("<"), T("r5rs-Z-H-9.html#%25_idx_256"));
  scheme.set(T("<="), T("r5rs-Z-H-9.html#%25_idx_260"));
  scheme.set(T("="), T("r5rs-Z-H-9.html#%25_idx_254"));
  scheme.set(T("=>"), T("r5rs-Z-H-7.html#%25_idx_110"));
  scheme.set(T(">"), T("r5rs-Z-H-9.html#%25_idx_258"));
  scheme.set(T(">="), T("r5rs-Z-H-9.html#%25_idx_262"));
  scheme.set(T("abs"), T("r5rs-Z-H-9.html#%25_idx_286"));
  scheme.set(T("acos"), T("r5rs-Z-H-9.html#%25_idx_326"));
  scheme.set(T("and"), T("r5rs-Z-H-7.html#%25_idx_118"));
  scheme.set(T("angle"), T("r5rs-Z-H-9.html#%25_idx_344"));
  scheme.set(T("append"), T("r5rs-Z-H-9.html#%25_idx_420"));
  scheme.set(T("apply"), T("r5rs-Z-H-9.html#%25_idx_556"));
  scheme.set(T("asin"), T("r5rs-Z-H-9.html#%25_idx_324"));
  scheme.set(T("assoc"), T("r5rs-Z-H-9.html#%25_idx_438"));
  scheme.set(T("assq"), T("r5rs-Z-H-9.html#%25_idx_434"));
  scheme.set(T("assv"), T("r5rs-Z-H-9.html#%25_idx_436"));
  scheme.set(T("atan"), T("r5rs-Z-H-9.html#%25_idx_328"));
  scheme.set(T("#b"), T("r5rs-Z-H-9.html#%25_idx_228"));
  scheme.set(T("begin"), T("r5rs-Z-H-7.html#%25_idx_136"));
  scheme.set(T("boolean?"), T("r5rs-Z-H-6.html#%25_idx_46"));
  scheme.set(T("caar"), T("r5rs-Z-H-9.html#%25_idx_402"));
  scheme.set(T("cadr"), T("r5rs-Z-H-9.html#%25_idx_404"));
  scheme.set(T("call-with-current-continuation"), T("r5rs-Z-H-9.html#%25_idx_566"));
  scheme.set(T("call-with-input-file"), T("r5rs-Z-H-9.html#%25_idx_588"));
  scheme.set(T("call-with-output-file"), T("r5rs-Z-H-9.html#%25_idx_590"));
  scheme.set(T("call-with-values"), T("r5rs-Z-H-9.html#%25_idx_574"));
  scheme.set(T("car"), T("r5rs-Z-H-9.html#%25_idx_392"));
  scheme.set(T("case"), T("r5rs-Z-H-7.html#%25_idx_114"));
  scheme.set(T("cdddar"), T("r5rs-Z-H-9.html#%25_idx_406"));
  scheme.set(T("cddddr"), T("r5rs-Z-H-9.html#%25_idx_408"));
  scheme.set(T("cdr"), T("r5rs-Z-H-9.html#%25_idx_396"));
  scheme.set(T("ceiling"), T("r5rs-Z-H-9.html#%25_idx_304"));
  scheme.set(T("char->integer"), T("r5rs-Z-H-9.html#%25_idx_480"));
  scheme.set(T("char-alphabetic?"), T("r5rs-Z-H-9.html#%25_idx_470"));
  scheme.set(T("char-ci<=?"), T("r5rs-Z-H-9.html#%25_idx_466"));
  scheme.set(T("char-ci<?"), T("r5rs-Z-H-9.html#%25_idx_462"));
  scheme.set(T("char-ci=?"), T("r5rs-Z-H-9.html#%25_idx_460"));
  scheme.set(T("char-ci>=?"), T("r5rs-Z-H-9.html#%25_idx_468"));
  scheme.set(T("char-ci>?"), T("r5rs-Z-H-9.html#%25_idx_464"));
  scheme.set(T("char-downcase"), T("r5rs-Z-H-9.html#%25_idx_486"));
  scheme.set(T("char-lower-case?"), T("r5rs-Z-H-9.html#%25_idx_478"));
  scheme.set(T("char-numeric?"), T("r5rs-Z-H-9.html#%25_idx_472"));
  scheme.set(T("char-ready?"), T("r5rs-Z-H-9.html#%25_idx_620"));
  scheme.set(T("char-upcase"), T("r5rs-Z-H-9.html#%25_idx_484"));
  scheme.set(T("char-upper-case?"), T("r5rs-Z-H-9.html#%25_idx_476"));
  scheme.set(T("char-whitespace?"), T("r5rs-Z-H-9.html#%25_idx_474"));
  scheme.set(T("char<=?"), T("r5rs-Z-H-9.html#%25_idx_456"));
  scheme.set(T("char<?"), T("r5rs-Z-H-9.html#%25_idx_452"));
  scheme.set(T("char=?"), T("r5rs-Z-H-9.html#%25_idx_450"));
  scheme.set(T("char>=?"), T("r5rs-Z-H-9.html#%25_idx_458"));
  scheme.set(T("char>?"), T("r5rs-Z-H-9.html#%25_idx_454"));
  scheme.set(T("char?"), T("r5rs-Z-H-6.html#%25_idx_54"));
  scheme.set(T("close-input-port"), T("r5rs-Z-H-9.html#%25_idx_608"));
  scheme.set(T("close-output-port"), T("r5rs-Z-H-9.html#%25_idx_610"));
  scheme.set(T("complex?"), T("r5rs-Z-H-9.html#%25_idx_242"));
  scheme.set(T("cond"), T("r5rs-Z-H-7.html#%25_idx_106"));
  scheme.set(T("cons"), T("r5rs-Z-H-9.html#%25_idx_390"));
  scheme.set(T("cos"), T("r5rs-Z-H-9.html#%25_idx_320"));
  scheme.set(T("current-input-port"), T("r5rs-Z-H-9.html#%25_idx_596"));
  scheme.set(T("current-output-port"), T("r5rs-Z-H-9.html#%25_idx_598"));
  scheme.set(T("#d"), T("r5rs-Z-H-9.html#%25_idx_232"));
  scheme.set(T("define"), T("r5rs-Z-H-8.html#%25_idx_190"));
  scheme.set(T("define-syntax"), T("r5rs-Z-H-8.html#%25_idx_198"));
  scheme.set(T("delay"), T("r5rs-Z-H-7.html#%25_idx_142"));
  scheme.set(T("denominator"), T("r5rs-Z-H-9.html#%25_idx_300"));
  scheme.set(T("display"), T("r5rs-Z-H-9.html#%25_idx_624"));
  scheme.set(T("do"), T("r5rs-Z-H-7.html#%25_idx_138"));
  scheme.set(T("dynamic-wind"), T("r5rs-Z-H-9.html#%25_idx_576"));
  scheme.set(T("#e"), T("r5rs-Z-H-9.html#%25_idx_236"));
  scheme.set(T("else"), T("r5rs-Z-H-7.html#%25_idx_108"));
  scheme.set(T("eof-object?"), T("r5rs-Z-H-9.html#%25_idx_618"));
  scheme.set(T("eq?"), T("r5rs-Z-H-9.html#%25_idx_216"));
  scheme.set(T("equal?"), T("r5rs-Z-H-9.html#%25_idx_218"));
  scheme.set(T("eqv?"), T("r5rs-Z-H-9.html#%25_idx_210"));
  scheme.set(T("eval"), T("r5rs-Z-H-9.html#%25_idx_578"));
  scheme.set(T("even?"), T("r5rs-Z-H-9.html#%25_idx_272"));
  scheme.set(T("exact->inexact"), T("r5rs-Z-H-9.html#%25_idx_346"));
  scheme.set(T("exact?"), T("r5rs-Z-H-9.html#%25_idx_250"));
  scheme.set(T("exp"), T("r5rs-Z-H-9.html#%25_idx_314"));
  scheme.set(T("expt"), T("r5rs-Z-H-9.html#%25_idx_332"));
  scheme.set(T("#f"), T("r5rs-Z-H-9.html#%25_idx_356"));
  scheme.set(T("floor"), T("r5rs-Z-H-9.html#%25_idx_302"));
  scheme.set(T("for-each"), T("r5rs-Z-H-9.html#%25_idx_560"));
  scheme.set(T("force"), T("r5rs-Z-H-9.html#%25_idx_562"));
  scheme.set(T("gcd"), T("r5rs-Z-H-9.html#%25_idx_294"));
  scheme.set(T("#i"), T("r5rs-Z-H-9.html#%25_idx_238"));
  scheme.set(T("if"), T("r5rs-Z-H-7.html#%25_idx_98"));
  scheme.set(T("imag-part"), T("r5rs-Z-H-9.html#%25_idx_340"));
  scheme.set(T("inexact->exact"), T("r5rs-Z-H-9.html#%25_idx_348"));
  scheme.set(T("inexact?"), T("r5rs-Z-H-9.html#%25_idx_252"));
  scheme.set(T("input-port?"), T("r5rs-Z-H-9.html#%25_idx_592"));
  scheme.set(T("integer->char"), T("r5rs-Z-H-9.html#%25_idx_482"));
  scheme.set(T("integer?"), T("r5rs-Z-H-9.html#%25_idx_248"));
  scheme.set(T("interaction-environment"), T("r5rs-Z-H-9.html#%25_idx_584"));
  scheme.set(T("lambda"), T("r5rs-Z-H-7.html#%25_idx_96"));
  scheme.set(T("lcm"), T("r5rs-Z-H-9.html#%25_idx_296"));
  scheme.set(T("length"), T("r5rs-Z-H-9.html#%25_idx_418"));
  scheme.set(T("let"), T("r5rs-Z-H-7.html#%25_idx_124"));
  scheme.set(T("let*"), T("r5rs-Z-H-7.html#%25_idx_128"));
  scheme.set(T("let-syntax"), T("r5rs-Z-H-7.html#%25_idx_180"));
  scheme.set(T("letrec"), T("r5rs-Z-H-7.html#%25_idx_132"));
  scheme.set(T("letrec-syntax"), T("r5rs-Z-H-7.html#%25_idx_182"));
  scheme.set(T("list"), T("r5rs-Z-H-9.html#%25_idx_416"));
  scheme.set(T("list->string"), T("r5rs-Z-H-9.html#%25_idx_528"));
  scheme.set(T("list->vector"), T("r5rs-Z-H-9.html#%25_idx_550"));
  scheme.set(T("list-ref"), T("r5rs-Z-H-9.html#%25_idx_426"));
  scheme.set(T("list-tail"), T("r5rs-Z-H-9.html#%25_idx_424"));
  scheme.set(T("list?"), T("r5rs-Z-H-9.html#%25_idx_414"));
  scheme.set(T("load"), T("r5rs-Z-H-9.html#%25_idx_630"));
  scheme.set(T("log"), T("r5rs-Z-H-9.html#%25_idx_316"));
  scheme.set(T("magnitude"), T("r5rs-Z-H-9.html#%25_idx_342"));
  scheme.set(T("make-polar"), T("r5rs-Z-H-9.html#%25_idx_336"));
  scheme.set(T("make-rectangular"), T("r5rs-Z-H-9.html#%25_idx_334"));
  scheme.set(T("make-string"), T("r5rs-Z-H-9.html#%25_idx_492"));
  scheme.set(T("make-vector"), T("r5rs-Z-H-9.html#%25_idx_538"));
  scheme.set(T("map"), T("r5rs-Z-H-9.html#%25_idx_558"));
  scheme.set(T("max"), T("r5rs-Z-H-9.html#%25_idx_274"));
  scheme.set(T("member"), T("r5rs-Z-H-9.html#%25_idx_432"));
  scheme.set(T("memq"), T("r5rs-Z-H-9.html#%25_idx_428"));
  scheme.set(T("memv"), T("r5rs-Z-H-9.html#%25_idx_430"));
  scheme.set(T("min"), T("r5rs-Z-H-9.html#%25_idx_276"));
  scheme.set(T("modulo"), T("r5rs-Z-H-9.html#%25_idx_292"));
  scheme.set(T("negative?"), T("r5rs-Z-H-9.html#%25_idx_268"));
  scheme.set(T("newline"), T("r5rs-Z-H-9.html#%25_idx_626"));
  scheme.set(T("not"), T("r5rs-Z-H-9.html#%25_idx_368"));
  scheme.set(T("null-environment"), T("r5rs-Z-H-9.html#%25_idx_582"));
  scheme.set(T("null?"), T("r5rs-Z-H-9.html#%25_idx_410"));
  scheme.set(T("number->string"), T("r5rs-Z-H-9.html#%25_idx_350"));
  scheme.set(T("number?"), T("r5rs-Z-H-9.html#%_idx_240"));
  scheme.set(T("numerator"), T("r5rs-Z-H-9.html#%25_idx_298"));
  scheme.set(T("#o"), T("r5rs-Z-H-9.html#%25_idx_230"));
  scheme.set(T("odd?"), T("r5rs-Z-H-9.html#%25_idx_270"));
  scheme.set(T("open-input-file"), T("r5rs-Z-H-9.html#%25_idx_604"));
  scheme.set(T("open-output-file"), T("r5rs-Z-H-9.html#%25_idx_606"));
  scheme.set(T("or"), T("r5rs-Z-H-7.html#%25_idx_120"));
  scheme.set(T("output-port?"), T("r5rs-Z-H-9.html#%25_idx_594"));
  scheme.set(T("pair?"), T("r5rs-Z-H-6.html#%25_idx_48"));
  scheme.set(T("peek-char"), T("r5rs-Z-H-9.html#%25_idx_616"));
  scheme.set(T("port?"), T("r5rs-Z-H-6.html#%25_idx_60"));
  scheme.set(T("positive?"), T("r5rs-Z-H-9.html#%25_idx_266"));
  scheme.set(T("procedure?"), T("r5rs-Z-H-6.html#%25_idx_62"));
  scheme.set(T("quasiquote"), T("r5rs-Z-H-7.html#%25_idx_150"));
  scheme.set(T("quote"), T("r5rs-Z-H-7.html#%25_idx_86"));
  scheme.set(T("quotient"), T("r5rs-Z-H-9.html#%25_idx_288"));
  scheme.set(T("rational?"), T("r5rs-Z-H-9.html#%25_idx_246"));
  scheme.set(T("rationalize"), T("r5rs-Z-H-9.html#%25_idx_310"));
  scheme.set(T("read"), T("r5rs-Z-H-9.html#%25_idx_612"));
  scheme.set(T("read-char"), T("r5rs-Z-H-9.html#%25_idx_614"));
  scheme.set(T("real-part"), T("r5rs-Z-H-9.html#%25_idx_338"));
  scheme.set(T("real?"), T("r5rs-Z-H-9.html#%25_idx_244"));
  scheme.set(T("remainder"), T("r5rs-Z-H-9.html#%25_idx_290"));
  scheme.set(T("reverse"), T("r5rs-Z-H-9.html#%25_idx_422"));
  scheme.set(T("round"), T("r5rs-Z-H-9.html#%25_idx_308"));
  scheme.set(T("scheme-report-environment"), T("r5rs-Z-H-9.html#%25_idx_580"));
  scheme.set(T("set!"), T("r5rs-Z-H-7.html#%25_idx_102"));
  scheme.set(T("set-car!"), T("r5rs-Z-H-9.html#%25_idx_398"));
  scheme.set(T("set-cdr!"), T("r5rs-Z-H-9.html#%25_idx_400"));
  scheme.set(T("setcar"), T("r5rs-Z-H-10.html#%25_idx_644"));
  scheme.set(T("sin"), T("r5rs-Z-H-9.html#%25_idx_318"));
  scheme.set(T("sqrt"), T("r5rs-Z-H-9.html#%25_idx_330"));
  scheme.set(T("string"), T("r5rs-Z-H-9.html#%25_idx_494"));
  scheme.set(T("string->list"), T("r5rs-Z-H-9.html#%25_idx_526"));
  scheme.set(T("string->number"), T("r5rs-Z-H-9.html#%25_idx_352"));
  scheme.set(T("string->symbol"), T("r5rs-Z-H-9.html#%25_idx_446"));
  scheme.set(T("string-append"), T("r5rs-Z-H-9.html#%25_idx_524"));
  scheme.set(T("string-ci<=?"), T("r5rs-Z-H-9.html#%25_idx_518"));
  scheme.set(T("string-ci<?"), T("r5rs-Z-H-9.html#%25_idx_514"));
  scheme.set(T("string-ci=?"), T("r5rs-Z-H-9.html#%25_idx_504"));
  scheme.set(T("string-ci>=?"), T("r5rs-Z-H-9.html#%25_idx_520"));
  scheme.set(T("string-ci>?"), T("r5rs-Z-H-9.html#%25_idx_516"));
  scheme.set(T("string-copy"), T("r5rs-Z-H-9.html#%25_idx_530"));
  scheme.set(T("string-fill!"), T("r5rs-Z-H-9.html#%25_idx_532"));
  scheme.set(T("string-length"), T("r5rs-Z-H-9.html#%25_idx_496"));
  scheme.set(T("string-ref"), T("r5rs-Z-H-9.html#%25_idx_498"));
  scheme.set(T("string-set!"), T("r5rs-Z-H-9.html#%25_idx_500"));
  scheme.set(T("string<=?"), T("r5rs-Z-H-9.html#%25_idx_510"));
  scheme.set(T("string<?"), T("r5rs-Z-H-9.html#%25_idx_506"));
  scheme.set(T("string=?"), T("r5rs-Z-H-9.html#%25_idx_502"));
  scheme.set(T("string>=?"), T("r5rs-Z-H-9.html#%25_idx_512"));
  scheme.set(T("string>?"), T("r5rs-Z-H-9.html#%25_idx_508"));
  scheme.set(T("string?"), T("r5rs-Z-H-9.html#%_idx_490"));
  scheme.set(T("substring"), T("r5rs-Z-H-9.html#%25_idx_522"));
  scheme.set(T("symbol->string"), T("r5rs-Z-H-9.html#%25_idx_444"));
  scheme.set(T("symbol?"), T("r5rs-Z-H-6.html#%25_idx_50"));
  scheme.set(T("syntax-rules"), T("r5rs-Z-H-7.html#%25_idx_184"));
  scheme.set(T("#t"), T("r5rs-Z-H-9.html#%25_idx_354"));
  scheme.set(T("tan"), T("r5rs-Z-H-9.html#%25_idx_322"));
  scheme.set(T("transcript-off"), T("r5rs-Z-H-9.html#%25_idx_634"));
  scheme.set(T("transcript-on"), T("r5rs-Z-H-9.html#%25_idx_632"));
  scheme.set(T("truncate"), T("r5rs-Z-H-9.html#%25_idx_306"));
  scheme.set(T("values"), T("r5rs-Z-H-9.html#%25_idx_572"));
  scheme.set(T("vector"), T("r5rs-Z-H-9.html#%25_idx_540"));
  scheme.set(T("vector->list"), T("r5rs-Z-H-9.html#%25_idx_548"));
  scheme.set(T("vector-fill!"), T("r5rs-Z-H-9.html#%25_idx_552"));
  scheme.set(T("vector-length"), T("r5rs-Z-H-9.html#%25_idx_542"));
  scheme.set(T("vector-ref"), T("r5rs-Z-H-9.html#%25_idx_544"));
  scheme.set(T("vector-set!"), T("r5rs-Z-H-9.html#%25_idx_546"));
  scheme.set(T("vector?"), T("r5rs-Z-H-6.html#%25_idx_58"));
  scheme.set(T("with-input-from-file"), T("r5rs-Z-H-9.html#%25_idx_600"));
  scheme.set(T("with-output-to-file"), T("r5rs-Z-H-9.html#%25_idx_602"));
  scheme.set(T("write"), T("r5rs-Z-H-9.html#%25_idx_622"));
  scheme.set(T("write-char"), T("r5rs-Z-H-9.html#%25_idx_628"));
  scheme.set(T("#x"), T("r5rs-Z-H-9.html#%25_idx_234"));
  scheme.set(T("zero?"), T("r5rs-Z-H-9.html#%25_idx_264"));
}

void Help::addSndLibSymbolHelp ()
{
  roots.set(T("SndLib"), T("http://ccrma.stanford.edu/software/snd/snd/"));
  clm.set(T("make-pulse-train"), T("sndclm.html#make-pulse-train"));
  clm.set(T("make-rand"), T("sndclm.html#make-rand"));
  clm.set(T("make-rand-interp"), T("sndclm.html#make-rand-interp"));
  clm.set(T("make-readin"), T("sndclm.html#make-readin"));
  clm.set(T("enveloped-mix"), T("sndscm.html#envelopedmix"));
  clm.set(T("snd-debug"), T("sndscm.html#snddebug"));
  clm.set(T("make-region-frame-reader"), T("sndscm.html#makeregionframereader"));
  clm.set(T("make-sample->file"), T("sndclm.html#make-sampletofile"));
  clm.set(T("make-sawtooth-wave"), T("sndclm.html#make-sawtooth-wave"));
  clm.set(T("oscil"), T("sndclm.html#oscil"));
  clm.set(T("make-scalar-mixer"), T("sndclm.html#make-scalar-mixer"));
  clm.set(T("oscil?"), T("sndclm.html#oscil?"));
  clm.set(T("out-any"), T("sndclm.html#out-any"));
  clm.set(T("make-sine-summation"), T("sndclm.html#make-sine-summation"));
  clm.set(T("outa"), T("sndclm.html#outa"));
  clm.set(T("*output*"), T("sndclm.html#*output*"));
  clm.set(T("make-square-wave"), T("sndclm.html#make-square-wave"));
  clm.set(T("make-src"), T("sndclm.html#make-src"));
  clm.set(T("make-ssb-am"), T("sndclm.html#make-ssb-am"));
  clm.set(T("make-sum-of-cosines"), T("sndclm.html#make-sum-of-cosines"));
  clm.set(T("make-sum-of-sines"), T("sndclm.html#make-sum-of-sines"));
  clm.set(T("pan-mix"), T("sndscm.html#panmix"));
  clm.set(T("explode-sf2"), T("sndscm.html#explodesf2"));
  clm.set(T("pan-mix-vct"), T("sndscm.html#panmixvct"));
  clm.set(T("exponentially-weighted-moving-average"), T("sndscm.html#exponentiallyweightedmovingaverage"));
  clm.set(T("make-table-lookup"), T("sndclm.html#make-table-lookup"));
  clm.set(T("partials->polynomial"), T("sndclm.html#partialstopolynomial"));
  clm.set(T("sndwarp"), T("sndscm.html#sndwarp"));
  clm.set(T("make-triangle-wave"), T("sndclm.html#make-triangle-wave"));
  clm.set(T("partials->wave"), T("sndclm.html#partialstowave"));
  clm.set(T("make-two-pole"), T("sndclm.html#make-two-pole"));
  clm.set(T("partials->waveshape"), T("sndclm.html#partialstowaveshape"));
  clm.set(T("sound->amp-env"), T("sndscm.html#soundtoamp_env"));
  clm.set(T("make-two-zero"), T("sndclm.html#make-two-zero"));
  clm.set(T("sound->frame"), T("sndscm.html#soundtoframe"));
  clm.set(T("all-pass"), T("sndclm.html#all-pass"));
  clm.set(T("sound->sound-data"), T("sndscm.html#soundtosounddata"));
  clm.set(T("all-pass?"), T("sndclm.html#all-pass?"));
  clm.set(T("make-wave-train"), T("sndclm.html#make-wave-train"));
  clm.set(T("fft-smoother"), T("sndscm.html#fftsmoother"));
  clm.set(T("make-waveshape"), T("sndclm.html#make-waveshape"));
  clm.set(T("phase-partials->wave"), T("sndclm.html#phase-partialstowave"));
  clm.set(T("sound-data->file"), T("sndscm.html#sounddatatofile"));
  clm.set(T("amplitude-modulate"), T("sndclm.html#amplitude-modulate"));
  clm.set(T("fft-squelch"), T("sndscm.html#fftsquelch"));
  clm.set(T("phase-vocoder"), T("sndclm.html#phase-vocoder"));
  clm.set(T("sound-data->frame"), T("sndscm.html#sounddatatoframe"));
  clm.set(T("analyse-ladspa"), T("grfsnd.html#analyseladspa"));
  clm.set(T("map-sound"), T("sndscm.html#mapsound"));
  clm.set(T("phase-vocoder?"), T("sndclm.html#phase-vocoder?"));
  clm.set(T("sound-data->sound"), T("sndscm.html#sounddatatosound"));
  clm.set(T("any-env-channel"), T("sndscm.html#anyenvchannel"));
  clm.set(T("map-sound-files"), T("sndscm.html#mapsoundfiles"));
  clm.set(T("place-sound"), T("sndscm.html#placesound"));
  clm.set(T("apply-ladspa"), T("grfsnd.html#applyladspa"));
  clm.set(T("array->file"), T("sndclm.html#arraytofile"));
  clm.set(T("array-interp"), T("sndclm.html#array-interp"));
  clm.set(T("file->array"), T("sndclm.html#filetoarray"));
  clm.set(T("file->frame"), T("sndclm.html#filetoframe"));
  clm.set(T("file->frame?"), T("sndclm.html#filetoframe?"));
  clm.set(T("file->sample"), T("sndclm.html#filetosample"));
  clm.set(T("asymmetric-fm?"), T("sndclm.html#asymmetric-fm?"));
  clm.set(T("file->sample?"), T("sndclm.html#filetosample?"));
  clm.set(T("play-mixes"), T("sndscm.html#playmixes"));
  clm.set(T("file->sound-data"), T("sndscm.html#filetosounddata"));
  clm.set(T("file->vct"), T("sndscm.html#filetovct"));
  clm.set(T("mark-name->id"), T("sndscm.html#marknametoid"));
  clm.set(T("play-sines"), T("sndscm.html#playsines"));
  clm.set(T("filter"), T("sndclm.html#filter"));
  clm.set(T("autocorrelate"), T("sndclm.html#autocorrelate"));
  clm.set(T("pluck"), T("sndscm.html#pluck"));
  clm.set(T("sound-interp"), T("sndscm.html#soundinterp"));
  clm.set(T("sound-let"), T("sndscm.html#sound-let"));
  clm.set(T("polar->rectangular"), T("sndclm.html#polartorectangular"));
  clm.set(T("bagpipe"), T("sndscm.html#bagpipe"));
  clm.set(T("match-sound-files"), T("sndscm.html#matchsoundfiles"));
  clm.set(T("polynomial"), T("sndclm.html#polynomial"));
  clm.set(T("polynomial operations"), T("sndscm.html#polydoc"));
  clm.set(T("sound-property"), T("sndscm.html#soundproperty"));
  clm.set(T("max-envelope"), T("sndscm.html#maxenvelope"));
  clm.set(T("polyshape"), T("sndclm.html#polyshape"));
  clm.set(T("polyshape?"), T("sndclm.html#polyshape?"));
  clm.set(T("filter?"), T("sndclm.html#filter?"));
  clm.set(T("filtered-comb"), T("sndclm.html#filtered-comb"));
  clm.set(T("filtered-comb?"), T("sndclm.html#filtered-comb?"));
  clm.set(T("power-env"), T("sndscm.html#powerenv"));
  clm.set(T("spectral-polynomial"), T("sndscm.html#spectralpolynomial"));
  clm.set(T("bessel filters"), T("sndscm.html#analogfilterdoc"));
  clm.set(T("previous-frame"), T("sndscm.html#previousframe"));
  clm.set(T("bigbird"), T("sndscm.html#bigbird"));
  clm.set(T("find-mix"), T("sndscm.html#findmix"));
  clm.set(T("bird"), T("sndscm.html#bird"));
  clm.set(T("fir-filter"), T("sndclm.html#fir-filter"));
  clm.set(T("mix->vct"), T("sndscm.html#mixtovct"));
  clm.set(T("brownian-noise"), T("sndscm.html#browniannoise"));
  clm.set(T("fir-filter?"), T("sndclm.html#fir-filter?"));
  clm.set(T("butterworth filters"), T("sndscm.html#analogfilterdoc"));
  clm.set(T("fm-bell"), T("sndscm.html#fmbell"));
  clm.set(T("mix-channel"), T("sndscm.html#mixchannel"));
  clm.set(T("pulse-train"), T("sndclm.html#pulse-train"));
  clm.set(T("spectrum"), T("sndclm.html#spectrum"));
  clm.set(T("fm-drum"), T("sndscm.html#fmdrum"));
  clm.set(T("pulse-train?"), T("sndclm.html#pulse-train?"));
  clm.set(T("spectrum->coeffs"), T("sndscm.html#spectrumtocoeffs"));
  clm.set(T("fm-noise"), T("sndscm.html#fmnoise"));
  clm.set(T("cascade->canonical"), T("sndscm.html#cascadetocanonical"));
  clm.set(T("fm-talker"), T("sndscm.html#fmvox"));
  clm.set(T("chain-dsps"), T("sndscm.html#chaindsps"));
  clm.set(T("fm-trumpet"), T("sndscm.html#fmtrumpet"));
  clm.set(T("radians->degrees"), T("sndclm.html#radianstodegrees"));
  clm.set(T("fm-violin"), T("sndscm.html#vdoc"));
  clm.set(T("radians->hz"), T("sndclm.html#radianstohz"));
  clm.set(T("fm-voice"), T("sndscm.html#reson"));
  clm.set(T("mix-frame"), T("sndscm.html#mixframe"));
  clm.set(T("square-wave"), T("sndclm.html#square-wave"));
  clm.set(T("focus-follows-mouse"), T("sndscm.html#focusfollowsmouse"));
  clm.set(T("rand"), T("sndclm.html#rand"));
  clm.set(T("square-wave?"), T("sndclm.html#square-wave?"));
  clm.set(T("channel-envelope"), T("sndscm.html#channelenvelope"));
  clm.set(T("rand-interp"), T("sndclm.html#rand-interp"));
  clm.set(T("channel-polynomial"), T("sndscm.html#channelpolynomial"));
  clm.set(T("mix-maxamp"), T("sndscm.html#mixmaxamp"));
  clm.set(T("rand-interp?"), T("sndclm.html#rand-interp?"));
  clm.set(T("squelch-vowels"), T("sndscm.html#squelchvowels"));
  clm.set(T("for-each-child"), T("sndscm.html#foreachchild"));
  clm.set(T("rand?"), T("sndclm.html#rand?"));
  clm.set(T("channel-property"), T("sndscm.html#channelproperty"));
  clm.set(T("for-each-sound-file"), T("sndscm.html#foreachsoundfile"));
  clm.set(T("src"), T("sndclm.html#src"));
  clm.set(T("channel-rms"), T("sndscm.html#channelrms"));
  clm.set(T("mix-name->id"), T("sndscm.html#mixnametoid"));
  clm.set(T("read-frame"), T("sndscm.html#readframe"));
  clm.set(T("src-duration"), T("sndscm.html#srcduration"));
  clm.set(T("channel-sync"), T("sndscm.html#channelsync"));
  clm.set(T("src-mixes"), T("sndscm.html#srcmixes"));
  clm.set(T("formant"), T("sndclm.html#formant"));
  clm.set(T("mix-property"), T("sndscm.html#mixproperty"));
  clm.set(T("formant?"), T("sndclm.html#formant?"));
  clm.set(T("channels-equal?"), T("sndscm.html#channelsequal"));
  clm.set(T("src?"), T("sndclm.html#src?"));
  clm.set(T("ssb-am"), T("sndclm.html#ssb-am"));
  clm.set(T("channels=?"), T("sndscm.html#channels="));
  clm.set(T("fractional-fourier-transform"), T("sndscm.html#fractionalfouriertransform"));
  clm.set(T("readin"), T("sndclm.html#readin"));
  clm.set(T("ssb-am?"), T("sndclm.html#ssb-am?"));
  clm.set(T("frame*"), T("sndclm.html#frame*"));
  clm.set(T("mix-sound"), T("sndscm.html#mixsound"));
  clm.set(T("readin?"), T("sndclm.html#readin?"));
  clm.set(T("ssb-bank"), T("sndscm.html#ssbbank"));
  clm.set(T("chebyshev filters"), T("sndscm.html#analogfilterdoc"));
  clm.set(T("frame+"), T("sndclm.html#frame+"));
  clm.set(T("mix-sound-data"), T("sndscm.html#mixsounddata"));
  clm.set(T("ssb-bank-env"), T("sndscm.html#ssbbankenv"));
  clm.set(T("check-for-unsaved-edits"), T("sndscm.html#checkforunsavededits"));
  clm.set(T("frame->file"), T("sndclm.html#frametofile"));
  clm.set(T("ssb-fm"), T("sndscm.html#ssbfm"));
  clm.set(T("clean-channel"), T("sndscm.html#cleanchannel"));
  clm.set(T("frame->file?"), T("sndclm.html#frametofile?"));
  clm.set(T("rectangular->polar"), T("sndclm.html#rectangulartopolar"));
  clm.set(T("clean-sound"), T("sndscm.html#cleansound"));
  clm.set(T("frame->frame"), T("sndclm.html#frametoframe"));
  clm.set(T("clear-array"), T("sndclm.html#clear-array"));
  clm.set(T("frame->list"), T("sndclm.html#frametolist"));
  clm.set(T("frame->sample"), T("sndclm.html#frametosample"));
  clm.set(T("frame->sound"), T("sndscm.html#frametosound"));
  clm.set(T("region->frame"), T("sndscm.html#regiontoframe"));
  clm.set(T("clear-selection"), T("sndscm.html#clearselection"));
  clm.set(T("frame->sound-data"), T("sndscm.html#frametosounddata"));
  clm.set(T("region->sound-data"), T("sndscm.html#regiontosounddata"));
  clm.set(T("frame->vct"), T("sndscm.html#frametovct"));
  clm.set(T("stereo->mono"), T("sndscm.html#stereotomono"));
  clm.set(T("frame-copy"), T("sndscm.html#framecopy"));
  clm.set(T("frame-reader-at-end?"), T("sndscm.html#framereaderatendQ"));
  clm.set(T("mixer*"), T("sndclm.html#mixermultiply"));
  clm.set(T("clm-load"), T("sndscm.html#clmload"));
  clm.set(T("frame-reader-chans"), T("sndscm.html#framereaderchans"));
  clm.set(T("mixer as matrix"), T("sndscm.html#mixerdoc"));
  clm.set(T("frame-reader-home"), T("sndscm.html#framereaderhome"));
  clm.set(T("mixer+"), T("sndclm.html#mixeradd"));
  clm.set(T("frame-reader-position"), T("sndscm.html#framereaderposition"));
  clm.set(T("mixer-copy"), T("sndscm.html#mixercopy"));
  clm.set(T("frame-reader?"), T("sndscm.html#framereaderQ"));
  clm.set(T("mixer-determinant"), T("sndscm.html#mixer-determinant"));
  clm.set(T("stretch-envelope"), T("sndscm.html#stretchenvelope"));
  clm.set(T("frame-ref"), T("sndclm.html#frame-ref"));
  clm.set(T("mixer-inverse"), T("sndscm.html#mixer-inverse"));
  clm.set(T("region-play-list"), T("sndscm.html#regionplaylist"));
  clm.set(T("sum-of-cosines"), T("sndclm.html#sum-of-cosines"));
  clm.set(T("frame-reverse!"), T("sndscm.html#framereverse"));
  clm.set(T("mixer-poly"), T("sndscm.html#mixer-poly"));
  clm.set(T("sum-of-cosines?"), T("sndclm.html#sum-of-cosines?"));
  clm.set(T("frame-set!"), T("sndclm.html#frame-set!"));
  clm.set(T("mixer-ref"), T("sndclm.html#mixer-ref"));
  clm.set(T("sum-of-sines"), T("sndclm.html#sum-of-sines"));
  clm.set(T("frame?"), T("sndclm.html#frame?"));
  clm.set(T("mixer-set!"), T("sndclm.html#mixer-set!"));
  clm.set(T("sum-of-sines?"), T("sndclm.html#sum-of-sines?"));
  clm.set(T("mixer-solve"), T("sndscm.html#mixer-solve"));
  clm.set(T("superimpose-ffts"), T("sndscm.html#superimposeffts"));
  clm.set(T("color-mixes"), T("sndscm.html#colormixes"));
  clm.set(T("mixer-transpose"), T("sndscm.html#mixer-transpose"));
  clm.set(T("free-frame-reader"), T("sndscm.html#freeframereader"));
  clm.set(T("mixer?"), T("sndclm.html#mixer?"));
  clm.set(T("swap-selection-channels"), T("sndscm.html#swapselectionchannels"));
  clm.set(T("remember-sound-state"), T("sndscm.html#remembersoundstate"));
  clm.set(T("sync-all"), T("sndscm.html#sync-all"));
  clm.set(T("freeverb"), T("sndscm.html#freeverb"));
  clm.set(T("mono->stereo"), T("sndscm.html#monotostereo"));
  clm.set(T("fullmix"), T("sndscm.html#fullmix"));
  clm.set(T("moog-filter"), T("sndscm.html#moogfilter"));
  clm.set(T("table-lookup"), T("sndclm.html#table-lookup"));
  clm.set(T("table-lookup?"), T("sndclm.html#table-lookup?"));
  clm.set(T("tap"), T("sndclm.html#tap"));
  clm.set(T("comb"), T("sndclm.html#comb"));
  clm.set(T("telephone"), T("sndscm.html#telephone"));
  clm.set(T("comb?"), T("sndclm.html#comb?"));
  clm.set(T("compand-channel"), T("sndscm.html#compandchannel"));
  clm.set(T("goertzel"), T("sndscm.html#goertzel"));
  clm.set(T("*reverb*"), T("sndclm.html#*reverb*"));
  clm.set(T("compand-sound"), T("sndscm.html#compandsound"));
  clm.set(T("concatenate-envelopes"), T("sndscm.html#concatenateenvelopes"));
  clm.set(T("grani"), T("sndscm.html#grani"));
  clm.set(T("continue-frame->file"), T("sndclm.html#continue-frametofile"));
  clm.set(T("continue-sample->file"), T("sndclm.html#continue-sampletofile"));
  clm.set(T("granulate"), T("sndclm.html#granulate"));
  clm.set(T("contrast-channel"), T("sndscm.html#contrastchannel"));
  clm.set(T("granulate?"), T("sndclm.html#granulate?"));
  clm.set(T("move-locsig"), T("sndclm.html#move-locsig"));
  clm.set(T("granulated-sound-interp"), T("sndscm.html#granulatedsoundinterp"));
  clm.set(T("move-mixes"), T("sndscm.html#movemixes"));
  clm.set(T("move-sound"), T("sndclm.html#move-sound"));
  clm.set(T("move-sound?"), T("sndclm.html#move-sound?"));
  clm.set(T("moving-average"), T("sndclm.html#moving-average"));
  clm.set(T("contrast-enhancement"), T("sndclm.html#contrast-enhancement"));
  clm.set(T("moving-average?"), T("sndclm.html#moving-average?"));
  clm.set(T("contrast-sound"), T("sndscm.html#contrastsound"));
  clm.set(T("moving-length"), T("sndscm.html#movinglength"));
  clm.set(T("reverse-envelope"), T("sndscm.html#reverseenvelope"));
  clm.set(T("moving-max"), T("sndscm.html#movingmax"));
  clm.set(T("moving-rms"), T("sndscm.html#movingrms"));
  clm.set(T("convolution"), T("sndclm.html#convolution"));
  clm.set(T("moving-sum"), T("sndscm.html#movingsum"));
  clm.set(T("graphic equalizer"), T("sndscm.html#grapheq"));
  clm.set(T("mpg"), T("sndscm.html#mpg"));
  clm.set(T("convolve"), T("sndclm.html#convolve"));
  clm.set(T("multiply-arrays"), T("sndclm.html#multiply-arrays"));
  clm.set(T("transpose-mixes"), T("sndscm.html#transposemixes"));
  clm.set(T("convolve-files"), T("sndclm.html#convolvefiles"));
  clm.set(T("ring-modulate"), T("sndclm.html#ring-modulate"));
  clm.set(T("harmonicizer"), T("sndscm.html#harmonicizer"));
  clm.set(T("rms"), T("sndscm.html#rmsgain"));
  clm.set(T("triangle-wave"), T("sndclm.html#triangle-wave"));
  clm.set(T("triangle-wave?"), T("sndclm.html#triangle-wave?"));
  clm.set(T("convolve?"), T("sndclm.html#convolve?"));
  clm.set(T("rms-envelope"), T("sndscm.html#rmsenvelope"));
  clm.set(T("two-pole"), T("sndclm.html#two-pole"));
  clm.set(T("copy-frame-reader"), T("sndscm.html#copyframereader"));
  clm.set(T("hello-dentist"), T("sndscm.html#hellodentist"));
  clm.set(T("rubber-sound"), T("sndscm.html#rubbersound"));
  clm.set(T("two-pole?"), T("sndclm.html#two-pole?"));
  clm.set(T("mus-array-print-length"), T("sndclm.html#musarrayprintlength"));
  clm.set(T("two-zero"), T("sndclm.html#two-zero"));
  clm.set(T("run"), T("sndscm.html#run"));
  clm.set(T("two-zero?"), T("sndclm.html#two-zero?"));
  clm.set(T("correlate"), T("sndclm.html#correlate"));
  clm.set(T("unclip-channel"), T("sndscm.html#unclipchannel"));
  clm.set(T("create-ssb-dialog"), T("sndscm.html#createssbdialog"));
  clm.set(T("cross-fade (amplitude)"), T("sndscm.html#mixdoc"));
  clm.set(T("hilbert-transform"), T("sndscm.html#hilberttransform"));
  clm.set(T("sample->file"), T("sndclm.html#sampletofile"));
  clm.set(T("cross-fade (frequency domain)"), T("sndscm.html#fadedoc"));
  clm.set(T("hook-member"), T("sndscm.html#hookmember"));
  clm.set(T("sample->file?"), T("sndclm.html#sampletofile?"));
  clm.set(T("cross-synthesis"), T("sndscm.html#crosssynthesis"));
  clm.set(T("sample->frame"), T("sndclm.html#sampletoframe"));
  clm.set(T("hz->radians"), T("sndclm.html#hztoradians"));
  clm.set(T("iir-filter"), T("sndclm.html#iir-filter"));
  clm.set(T("mus-channel"), T("sndclm.html#mus-channel"));
  clm.set(T("iir-filter?"), T("sndclm.html#iir-filter?"));
  clm.set(T("mus-channels"), T("sndclm.html#mus-channels"));
  clm.set(T("in-any"), T("sndclm.html#in-any"));
  clm.set(T("mus-close"), T("sndclm.html#mus-close"));
  clm.set(T("samples->seconds"), T("sndclm.html#samplestoseconds"));
  clm.set(T("ina"), T("sndclm.html#ina"));
  clm.set(T("mus-cosines"), T("sndclm.html#mus-cosines"));
  clm.set(T("inb"), T("sndclm.html#inb"));
  clm.set(T("mus-data"), T("sndclm.html#mus-data"));
  clm.set(T("variable-display"), T("sndscm.html#variabledisplay"));
  clm.set(T("init-ladspa"), T("grfsnd.html#initladspa"));
  clm.set(T("mus-describe"), T("sndclm.html#mus-describe"));
  clm.set(T("insert-channel"), T("sndscm.html#insertchannel"));
  clm.set(T("vct->file"), T("sndscm.html#vcttofile"));
  clm.set(T("insert-frame"), T("sndscm.html#insertframe"));
  clm.set(T("mus-feedback"), T("sndclm.html#mus-feedback"));
  clm.set(T("save-mark-properties"), T("sndscm.html#savemarkproperties"));
  clm.set(T("vct->frame"), T("sndscm.html#vcttoframe"));
  clm.set(T("mus-feedforward"), T("sndclm.html#mus-feedforward"));
  clm.set(T("save-mix"), T("sndscm.html#savemix"));
  clm.set(T("mus-file-buffer-size"), T("sndclm.html#musfilebuffersize"));
  clm.set(T("save-mixes"), T("sndscm.html#savemixes"));
  clm.set(T("db->linear"), T("sndclm.html#dbtolinear"));
  clm.set(T("mus-file-name"), T("sndclm.html#mus-file-name"));
  clm.set(T("insert-sound-data"), T("sndscm.html#insertsounddata"));
  clm.set(T("mus-float-equal-fudge-factor"), T("sndclm.html#musfloatequalfudgefactor"));
  clm.set(T("insert-vct"), T("sndscm.html#insertvct"));
  clm.set(T("mus-formant-radius"), T("sndclm.html#mus-formant-radius"));
  clm.set(T("mus-frequency"), T("sndclm.html#mus-frequency"));
  clm.set(T("mus-generator?"), T("sndclm.html#musgeneratorp"));
  clm.set(T("def-clm-struct"), T("sndscm.html#def-clm-struct"));
  clm.set(T("instruments"), T("sndclm.html#instruments"));
  clm.set(T("integrate-envelope"), T("sndscm.html#integrateenvelope"));
  clm.set(T("jc-reverb"), T("sndscm.html#jcreverb"));
  clm.set(T("mus-hop"), T("sndclm.html#mus-hop"));
  clm.set(T("vct-polynomial"), T("sndscm.html#vctpolynomial"));
  clm.set(T("jc-reverb"), T("sndscm.html#jcrevdoc"));
  clm.set(T("mus-increment"), T("sndclm.html#mus-increment"));
  clm.set(T("savitzky-golay-filter"), T("sndscm.html#sgfilter"));
  clm.set(T("mus-input?"), T("sndclm.html#mus-input?"));
  clm.set(T("sawtooth-wave"), T("sndclm.html#sawtooth-wave"));
  clm.set(T("define-selection-via-marks"), T("sndscm.html#defineselectionviamarks"));
  clm.set(T("kalman-filter-channel"), T("sndscm.html#kalmanfilterchannel"));
  clm.set(T("mus-interp-type"), T("sndclm.html#mus-interp-type"));
  clm.set(T("sawtooth-wave?"), T("sndclm.html#sawtooth-wave?"));
  clm.set(T("definstrument"), T("sndscm.html#definstrument"));
  clm.set(T("mus-interpolate"), T("sndclm.html#mus-interpolate"));
  clm.set(T("mus-length"), T("sndclm.html#mus-length"));
  clm.set(T("degrees->radians"), T("sndclm.html#degreestoradians"));
  clm.set(T("mus-location"), T("sndclm.html#mus-location"));
  clm.set(T("scale-envelope"), T("sndscm.html#scaleenvelope"));
  clm.set(T("delay"), T("sndclm.html#delay"));
  clm.set(T("mus-mix"), T("sndscm.html#musmix"));
  clm.set(T("scale-mixes"), T("sndscm.html#scalemixes"));
  clm.set(T("delay-channel-mixes"), T("sndscm.html#delaychannelmixes"));
  clm.set(T("ladspa-descriptor"), T("grfsnd.html#ladspadescriptor"));
  clm.set(T("mus-name"), T("sndclm.html#mus-name"));
  clm.set(T("delay-tick"), T("sndclm.html#delaytick"));
  clm.set(T("delay?"), T("sndclm.html#delay?"));
  clm.set(T("mus-offset"), T("sndclm.html#mus-offset"));
  clm.set(T("scale-sound"), T("sndscm.html#scalesound"));
  clm.set(T("mus-order"), T("sndclm.html#mus-order"));
  clm.set(T("scale-tempo"), T("sndscm.html#scaletempo"));
  clm.set(T("linear->db"), T("sndclm.html#lineartodb"));
  clm.set(T("linear-src-channel"), T("sndscm.html#linearsrcchannel"));
  clm.set(T("mus-output?"), T("sndclm.html#mus-output?"));
  clm.set(T("scan-sound"), T("sndscm.html#scansound"));
  clm.set(T("mus-phase"), T("sndclm.html#mus-phase"));
  clm.set(T("scentroid"), T("sndscm.html#scentroid"));
  clm.set(T("mus-ramp"), T("sndclm.html#mus-ramp"));
  clm.set(T("list-ladspa"), T("grfsnd.html#listladspa"));
  clm.set(T("mus-random"), T("sndclm.html#mus-random"));
  clm.set(T("delete-selection-and-smooth"), T("sndscm.html#deleteselectionandsmooth"));
  clm.set(T("mus-reset"), T("sndclm.html#mus-reset"));
  clm.set(T("mus-run"), T("sndclm.html#mus-run"));
  clm.set(T("mus-scaler"), T("sndclm.html#mus-scaler"));
  clm.set(T("seconds->samples"), T("sndclm.html#secondstosamples"));
  clm.set(T("describe-hook"),  T("sndscm.html#describehook"));
  clm.set(T("describe-mark"), T("sndscm.html#describemark"));
  clm.set(T("voiced->unvoiced"), T("sndscm.html#voicedtounvoiced"));
  clm.set(T("disable-control-panel"), T("sndscm.html#disablecontrolpanel"));
  clm.set(T("locsig"), T("sndclm.html#locsig"));
  clm.set(T("volterra-filter"), T("sndscm.html#volterrafilter"));
  clm.set(T("display-bark-fft"), T("sndscm.html#displaybarkfft"));
  clm.set(T("locsig-ref"), T("sndclm.html#locsig-ref"));
  clm.set(T("wave-train"), T("sndclm.html#wave-train"));
  clm.set(T("display-db"), T("sndscm.html#displaydb"));
  clm.set(T("locsig-reverb-ref"), T("sndclm.html#locsig-reverb-ref"));
  clm.set(T("wave-train?"), T("sndclm.html#wave-train?"));
  clm.set(T("locsig-reverb-set!"), T("sndclm.html#locsig-reverb-set!"));
  clm.set(T("display-scanned-synthesis"), T("sndscm.html#displayscannedsynthesis"));
  clm.set(T("locsig-set!"), T("sndclm.html#locsig-set!"));
  clm.set(T("waveshape"), T("sndclm.html#waveshape"));
  clm.set(T("dissolve-fade"), T("sndscm.html#dissolvefade"));
  clm.set(T("locsig-type"), T("sndclm.html#locsig-type"));
  clm.set(T("waveshape?"), T("sndclm.html#waveshape?"));
  clm.set(T("dither-channel"), T("sndscm.html#ditherchannel"));
  clm.set(T("locsig?"), T("sndclm.html#locsig?"));
  clm.set(T("selection->sound-data"), T("sndscm.html#selectiontosounddata"));
  clm.set(T("waveshaping voice"), T("sndscm.html#pqwvox"));
  clm.set(T("dither-sound"), T("sndscm.html#dithersound"));
  clm.set(T("dlocsig"), T("sndscm.html#dlocsig"));
  clm.set(T("loop-between-marks"), T("sndscm.html#loopbetweenmarks"));
  clm.set(T("do?"), T("sndscm.html#dop"));
  clm.set(T("lpc-coeffs"), T("sndscm.html#lpccoeffs"));
  clm.set(T("weighted-moving-average"), T("sndscm.html#weightedmovingaverage"));
  clm.set(T("lpc-predict"), T("sndscm.html#lpcpredict"));
  clm.set(T("dot-product"), T("sndclm.html#dot-product"));
  clm.set(T("make-all-pass"), T("sndclm.html#make-all-pass"));
  clm.set(T("make-asymmetric-fm"), T("sndclm.html#make-asymmetric-fm"));
  clm.set(T("make-bandpass"), T("sndscm.html#makebandpass"));
  clm.set(T("selection-members"), T("sndscm.html#selectionmembers"));
  clm.set(T("make-bandstop"), T("sndscm.html#makebandstop"));
  clm.set(T("make-biquad"), T("sndscm.html#makebiquad"));
  clm.set(T("window-samples"), T("sndscm.html#windowsamples"));
  clm.set(T("make-birds"), T("sndscm.html#makebirds"));
  clm.set(T("make-comb"), T("sndclm.html#make-comb"));
  clm.set(T("make-convolve"), T("sndclm.html#make-convolve"));
  clm.set(T("set-global-sync"), T("sndscm.html#setglobalsync"));
  clm.set(T("make-current-window-display"), T("sndscm.html#makecurrentwindowdisplay"));
  clm.set(T("make-delay"), T("sndclm.html#make-delay"));
  clm.set(T("shepard-tone"), T("sndscm.html#shepardtone"));
  clm.set(T("make-differentiator"), T("sndscm.html#makedifferentiator"));
  clm.set(T("mus-srate"), T("sndclm.html#mussrate"));
  clm.set(T("with-local-hook"), T("sndscm.html#withlocalhook"));
  clm.set(T("make-env"), T("sndclm.html#make-env"));
  clm.set(T("with-mix"), T("sndscm.html#with-mix"));
  clm.set(T("make-fft-window"), T("sndclm.html#make-fft-window"));
  clm.set(T("mus-width"), T("sndclm.html#mus-width"));
  clm.set(T("make-file->frame"), T("sndclm.html#make-filetoframe"));
  clm.set(T("mus-xcoeff"), T("sndclm.html#mus-xcoeff"));
  clm.set(T("make-file->sample"), T("sndclm.html#make-filetosample"));
  clm.set(T("mus-xcoeffs"), T("sndclm.html#mus-xcoeffs"));
  clm.set(T("show-disk-space"), T("sndscm.html#showdiskspace"));
  clm.set(T("with-reopen-menu"), T("sndscm.html#withreopenmenu"));
  clm.set(T("make-filter"), T("sndclm.html#make-filter"));
  clm.set(T("mus-ycoeff"), T("sndclm.html#mus-ycoeff"));
  clm.set(T("with-sound"), T("sndscm.html#withsound"));
  clm.set(T("make-filtered-comb"), T("sndclm.html#make-filtered-comb"));
  clm.set(T("mus-ycoeffs"), T("sndclm.html#mus-ycoeffs"));
  clm.set(T("with-temp-sound"), T("sndscm.html#withtempsound"));
  clm.set(T("make-fir-filter"), T("sndclm.html#make-fir-filter"));
  clm.set(T("with-temporary-selection"), T("sndscm.html#withtemporaryselection"));
  clm.set(T("edit-property"), T("sndscm.html#editproperty"));
  clm.set(T("make-formant"), T("sndclm.html#make-formant"));
  clm.set(T("make-frame"), T("sndclm.html#make-frame"));
  clm.set(T("make-frame!"), T("sndclm.html#make-frame!"));
  clm.set(T("show-selection"), T("sndscm.html#showselection"));
  clm.set(T("edot-product"), T("sndclm.html#edot-product"));
  clm.set(T("make-frame->file"), T("sndclm.html#make-frametofile"));
  clm.set(T("ws-interrupt?"), T("sndscm.html#wsinterrupt"));
  clm.set(T("make-frame-reader"), T("sndscm.html#makeframereader"));
  clm.set(T("next-frame"), T("sndscm.html#nextframe"));
  clm.set(T("show-smpte-label"), T("sndscm.html#showsmptelabel"));
  clm.set(T("make-granulate"), T("sndclm.html#make-granulate"));
  clm.set(T("env"), T("sndclm.html#env"));
  clm.set(T("make-highpass"), T("sndscm.html#makehighpass"));
  clm.set(T("normalize-envelope"), T("sndscm.html#normalizeenvelope"));
  clm.set(T("make-hilbert-transform"), T("sndscm.html#makehilberttransform"));
  clm.set(T("normalize-sound"), T("sndscm.html#normalizesound"));
  clm.set(T("silence-all-mixes"), T("sndscm.html#silenceallmixes"));
  clm.set(T("env-expt-channel"), T("sndscm.html#envexptchannel"));
  clm.set(T("make-iir-filter"), T("sndclm.html#make-iir-filter"));
  clm.set(T("normalized-mix"), T("sndscm.html#normalizedmix"));
  clm.set(T("silence-mixes"), T("sndscm.html#silencemixes"));
  clm.set(T("env-interp"), T("sndclm.html#env-interp"));
  clm.set(T("make-locsig"), T("sndclm.html#make-locsig"));
  clm.set(T("notch"), T("sndclm.html#notch"));
  clm.set(T("env-mixes"), T("sndscm.html#envmixes"));
  clm.set(T("make-lowpass"), T("sndscm.html#makelowpass"));
  clm.set(T("notch-channel"), T("sndscm.html#notchchannel"));
  clm.set(T("sine-bank"), T("sndclm.html#sine-bank"));
  clm.set(T("notch-out-rumble-and-hiss"), T("sndscm.html#notchoutrumbleandhiss"));
  clm.set(T("sine-env-channel"), T("sndscm.html#sineenvchannel"));
  clm.set(T("make-mixer"), T("sndclm.html#make-mixer"));
  clm.set(T("notch-selection"), T("sndscm.html#notchselection"));
  clm.set(T("sine-ramp"), T("sndscm.html#sineramp"));
  clm.set(T("env-sound-interp"), T("sndscm.html#envsoundinterp"));
  clm.set(T("make-mixer!"), T("sndclm.html#make-mixer!"));
  clm.set(T("notch-sound"), T("sndscm.html#notchsound"));
  clm.set(T("sine-summation"), T("sndclm.html#sine-summation"));
  clm.set(T("env?"), T("sndclm.html#env?"));
  clm.set(T("make-move-sound"), T("sndclm.html#make-move-sound"));
  clm.set(T("notch?"), T("sndclm.html#notch?"));
  clm.set(T("sine-summation?"), T("sndclm.html#sine-summation?"));
  clm.set(T("z-transform"), T("sndscm.html#ztransform"));
  clm.set(T("make-moving-average"), T("sndclm.html#make-moving-average"));
  clm.set(T("nrev"), T("sndscm.html#nrev"));
  clm.set(T("singer"), T("sndscm.html#singerdoc"));
  clm.set(T("make-notch"), T("sndclm.html#make-notch"));
  clm.set(T("offset-channel"), T("sndscm.html#offsetchannel"));
  clm.set(T("zip-sound"), T("sndscm.html#zipsound"));
  clm.set(T("make-one-pole"), T("sndclm.html#make-one-pole"));
  clm.set(T("offset-sound"), T("sndscm.html#offsetsound"));
  clm.set(T("zipper"), T("sndscm.html#zipper"));
  clm.set(T("make-one-zero"), T("sndclm.html#make-one-zero"));
  clm.set(T("one-pole"), T("sndclm.html#one-pole"));
  clm.set(T("make-oscil"), T("sndclm.html#make-oscil"));
  clm.set(T("one-pole?"), T("sndclm.html#one-pole?"));
  clm.set(T("make-phase-vocoder"), T("sndclm.html#make-phase-vocoder"));
  clm.set(T("one-zero"), T("sndclm.html#one-zero"));
  clm.set(T("smoothing-filter"), T("sndscm.html#smoothingfilter"));
  clm.set(T("make-pixmap"), T("sndscm.html#makepixmap"));
  clm.set(T("one-zero?"), T("sndclm.html#one-zero?"));
  clm.set(T("SMS synthesis"), T("sndscm.html#pins"));
  clm.set(T("snap-mark-to-beat"), T("sndscm.html#snapmarktobeat"));
  clm.set(T("make-polyshape"), T("sndclm.html#make-polyshape"));
  clm.set(T("snap-mix-to-beat"), T("sndscm.html#snapmixtobeat"));
}

