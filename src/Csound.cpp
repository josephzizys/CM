/*=======================================================================*
  Copyright (C) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#include "Enumerations.h"
#include "Csound.h"
#include "Console.h"
#include "Preferences.h"
#include "CmSupport.h"
#include "Alerts.h"

/*=======================================================================*
                             Csound Instance
 *=======================================================================*/

juce_ImplementSingleton (Csound);

Csound::Csound () 
  : scorefile (File::nonexistent),
    application (File::nonexistent),
    commandargs (0),
    scoreheader (String::empty),
    writeafter (true),
    playafter (false)
{
  orchestras.setMaxNumberOfItems(8);
  initPrefs();
  //for (int i=0;i<20;i++)
  //    addToScore(IStatement, 1, i, T("20 304 1"));
  //  std::cout << "score size=" << score.size() << "\n";
}

Csound::~Csound ()
{
  //flushPrefs();
  orchestras.clear();
  score.clear();
}

#ifndef GRACE
void Csound::initPrefs(){}
void Csound::savePrefs(){}
#else
void Csound::initPrefs()
{
  Preferences* pref=Preferences::getInstance();
  String path=pref->getStringProp(T("CsoundApplication"));
  if (!path.isEmpty())
    {
      File app=completeFile(path);
      if (!app.existsAsFile())
	{
	  String warn=T("Warning: Csound application ");
	  warn << path.quoted() << T(" does not exist.\n");
	  Console::getInstance()->printWarning(warn);
	}
      else
	application=app;
    }
  //pref->setStringProp(T("CsoundCommandArgs"), T("-W -o test.wav -d"));
  commandargs=pref->getXmlProp(T("CsoundCommandArgs"));
  if (!commandargs)
    {
      XmlElement* child=0;
      commandargs=new XmlElement(T("CsoundCommandArgs"));
      // index of currently selected args
      commandargs->setAttribute(T("index"), 0); 
      child=commandargs->createNewChildElement(T("CommandArgs"));
      child->setAttribute(T("text"),T("-W -odac -d"));
      child=commandargs->createNewChildElement(T("CommandArgs"));
      child->setAttribute(T("text"),T("-W -o test.wav -d"));
    }
  scoreheader=pref->getStringProp(T("CsoundScoreHeader"));
  orchestras.restoreFromString(pref->getStringProp(T("CsoundOrchestras")));
  playafter=pref->getBoolProp(T("CsoundPlayAfter"), false);
}

void Csound::savePrefs()
{
  Preferences* pref=Preferences::getInstance();
  pref->setStringProp(T("CsoundApplication"),  application.getFullPathName());
  pref->setXmlProp(T("CsoundCommandArgs"), commandargs);
  pref->setStringProp(T("CsoundOrchestras"), orchestras.toString());
  pref->setStringProp(T("CsoundScoreHeader"), scoreheader);
  pref->setBoolProp(T("CsoundPlayAfter"), playafter);
  // WriteAfter is NOT a preference
}
#endif

File Csound::getScoreFile()
{
  return scorefile;
}

void Csound::setScoreFile(File file)
{
  // NOT a preference
  scorefile=file;
}

File Csound::getApplication()
{
  return application;
}

void Csound::setApplication(File file)
{
  application=file;
  savePrefs();
}

XmlElement* Csound::getCommandArgs()
{
  return commandargs;
}

String Csound::getApplicationArgs()
{
  // return current application args
  int index=commandargs->getIntAttribute(T("index")); // index of current
  XmlElement* sub=commandargs->getChildElement(index);
  if (sub)
    return sub->getStringAttribute(T("text"));
  return String::empty;
}

int Csound::findApplicationArgs(String str)
{
  // return index of str or -1 if not there
  int index=0;
  forEachXmlChildElement (*commandargs, e)
    {
      if (e->getStringAttribute(T("text"))==str)
        return index;
      index++;
    }
  return -1;
}

void Csound::setApplicationArgs(String str)
{
  // add or select str as the application's command args
  int i=findApplicationArgs(str);
  if (i==-1) // add new command args
    {
      XmlElement* e=commandargs->createNewChildElement(T("CommandArgs"));
      e->setAttribute(T("text"), str);
      i=commandargs->getNumChildElements()-1;
    }
  // select str as current args
  commandargs->setAttribute(T("index"), i);
  savePrefs();
}

bool Csound::canRunApplication()
{
  return application.existsAsFile();
}

void Csound::runApplication()
{
  if (canRunApplication())
    {
      File app=getApplication();
      String orc=getOrcFile().getFullPathName().quoted();
      String sco=getScoreFile().getFullPathName().quoted();
      String args=getApplicationArgs();
      String msg=String::empty;
      args << T(" ") << orc
	   << T(" ") << sco;
      msg << T("Starting ") << app.getFullPathName()
	  << T(" ") << args << T("\n");
      Console::getInstance()->printOutput(msg);
      app.startAsProcess(args);
    }
  else
    Console::getInstance()->
      printError(">>> Error: Csound: application not set.");
}

String Csound::getScoreHeader()
{
  return scoreheader;
}

void Csound::setScoreHeader(String str)
{
  scoreheader=str;
  savePrefs();
}

File Csound::getOrcFile()
{
  if (orchestras.getNumFiles() > 0)
    return orchestras.getFile(0);
  else
    return File::nonexistent;
}

void Csound::setOrcFile(File file) 
{
  orchestras.addFile(file);
  savePrefs();
}

bool Csound::getPlayAfter()
{
  return playafter;
}

void Csound::setPlayAfter(bool b)
{
  playafter=b;
  savePrefs();
}

bool Csound::getWriteAfter()
{
  return writeafter;
}

void Csound::setWriteAfter(bool b)
{
  // NOT a preference
  writeafter=b;
}

/*=======================================================================*
                                Score Events
 *=======================================================================*/

CsoundScoreEv::CsoundScoreEv(int typ, int id, double tim, String vals)
{
  type=typ;
  name=id;
  time=tim;
  pars=vals;
}

CsoundScoreEv::~CsoundScoreEv()
{
}

String CsoundScoreEv::pfieldsToString(String delim)
{
  String text = String::empty;
  text << name
       << delim << String(time, 3);
  if (delim==T(" "))
    text << delim << pars;
  else
    text << delim << pars.replace(T(" "), delim);
  return text;
}

String CsoundScoreEv::toString(int fmat)
{
  String text = String::empty;
  String evid;
  if (type==Csound::IStatement)
    evid=T("i");
  else if (type==Csound::FStatement)
    evid=T("f");
  else
    return T("<unknown csound statement>");
  switch (fmat)
    {
    case ExportIDs::CsoundScore :
      text << evid << T(" ") << pfieldsToString( T(" ") );
      break;
    case ExportIDs::SalData :
      text << T("{") << pfieldsToString( T(" ") ) << T("}");
      break;
    case ExportIDs::LispData :
      text << T("(") << pfieldsToString( T(" ") ) << T(")");
      break;
    case ExportIDs::SalSend :
      text << T("send \"cs:") << evid << T("\", ") 
	   << pfieldsToString( T(", "));
      break;
    case ExportIDs::LispSend :
      text << T("(send \"cs:") << evid << T("\" ") 
	   << pfieldsToString( T(" ") ) << T(")");
      break;
    default:
      text=T("<unknown export format>");
      break;
    }
  return text;
}

/*=======================================================================*
                                Score Interface
 *=======================================================================*/

void Csound::initScore(String inits)
{
  StringArray array;
  array.addTokens(inits, true);
  if (array.size()==0)
    return;
  setScoreFile(completeFile(array[0].unquoted()));
  for (int i=1; i<array.size(); i+=2)
    {
      if (array[i]==T(":play"))
	setPlayAfter(array[i+1]==T("#t"));
      else if (array[i]==T(":write"))
	setWriteAfter(array[i+1]==T("#t"));
      else if (array[i]==T(":options"))
	setApplicationArgs(array[i+1].unquoted());
      else if (array[i]==T(":header"))
	setScoreHeader(array[i+1].unquoted());
      else if (array[i]==T(":orchestra"))
	setOrcFile(array[i+1].unquoted());
    }
}

void Csound::saveScore()
{
  if (getWriteAfter())
    {
      writeScore(ExportIDs::ToFile, ExportIDs::CsoundScore);
      clearScore();
      if (getPlayAfter())
	{
	  runApplication();
	}
    }
}

bool Csound::isScoreEmpty()
{
  return score.size() == 0;
}

void Csound::addToScore(int type, int name, double time, String pars)
{
  score.add(new CsoundScoreEv(type, name, time, pars));
}

void Csound::sortScore() {
  score.sort(comparator,true);
}

void Csound::clearScore() {
  score.clear();
}

void Csound::writeScore(int dest, int format, double start, double endtime,
			bool addi, bool addf)
{
  if (endtime<=0.0) endtime=3600.0*24.0;
  int i=0;
  String text, indent, after;
  switch (format)
    {
    case ExportIDs::CsoundScore :
      text=T("s\n");
      indent=String::empty;
      after=T("e\n");
      break;
    case ExportIDs::LispData :
      text=T("(define csound-score\n  '(\n");
      indent=T("    ");
      after=T("  ))\n");
      break;
    case ExportIDs::SalData :
      text=T("define variable csound-score = \n  {\n"); 
      indent=T("   ");
      after=T("  }\n");
      break;
    case ExportIDs::LispSend :
      text=T("(begin\n"); 
      indent=T("  "); 
      after=T("  )\n");
      break;
    case ExportIDs::SalSend :
      text=T("begin\n");
      indent=T("  ");
      after=T("end\n");
      break;
    }
  sortScore();

  if (start > 0.0)
    { 
      // fast forward to user's start time
      for ( ; i<score.size(); i++)
	if ( start <= (double)(score[i]->time) )
	  break;
    }
  for ( ; i<score.size(); i++)
    {
      if (score[i]->time > endtime)
	break;   // stop after endtime
      if ( (score[i]->type == Csound::IStatement && addi) || 
	   (score[i]->type == Csound::FStatement && addf) )
	text << indent << score[i]->toString(format) << T("\n");
    }
  text << after;
  // output to file, console or clipboard
  if (dest==ExportIDs::ToFile)
    {
      String comm="; Common Music output ";
      comm << Time::getCurrentTime().toString(true,true) 
	   << T("\n\n");
      if (!getScoreHeader().isEmpty())
	comm << getScoreHeader() << T("\n\n");
      scorefile.replaceWithText(comm+text);
      String msg=T("Scorefile: ");
      msg << scorefile.getFullPathName() << T("\n");
      Console::getInstance()->printOutput(msg);
    }
  else if (dest==ExportIDs::ToConsole)
    Console::getInstance()->printOutput(text);
  else if ( dest==ExportIDs::ToClipboard)
    SystemClipboard::copyTextToClipboard(text);
}

#ifdef GRACE

/*=======================================================================*
                                  Dialogs
 *=======================================================================*/

CsoundSettingsDialog::CsoundSettingsDialog ()
  : csolab (0),
    csound (0),
    optlab (0),
    options (0),
    orclab (0),
    orcfile (0),
    hdrlab (0),
    header (0)
{
  Csound* cs=Csound::getInstance();
  addAndMakeVisible(csolab = new Label(String::empty, T("Csound:")));
  csolab->setFont(Font(15.0000f, Font::plain));
  csolab->setJustificationType(Justification::centredRight);
  csolab->setEditable(false, false, false);
  csolab->setColour(TextEditor::textColourId, Colours::black);
  csolab->setColour(TextEditor::backgroundColourId, Colour (0x0));

  csound = new FilenameComponent(String::empty, 
				 cs->getApplication(),
				 true, 
				 false, 
				 false, 
				 String::empty,
				 String::empty,
				 T("(choose csound executable)"));
  addAndMakeVisible(csound);
  csound->setBrowseButtonText(T("Browse..."));
  csound->addListener(this);

  addAndMakeVisible(optlab = new Label(String::empty, T("Options:")));
  optlab->setFont(Font(15.0000f, Font::plain));
  optlab->setJustificationType(Justification::centredRight);
  optlab->setEditable(false, false, false);
  optlab->setColour(TextEditor::textColourId, Colours::black);
  optlab->setColour(TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible(options = new ComboBox(T("Options")));
  options->setEditableText(true);
  updateOptions();
  options->addListener(this);

  addAndMakeVisible(orclab = new Label(String::empty, T("Orchestra:")));
  orclab->setFont(Font (15.0000f, Font::plain));
  orclab->setJustificationType (Justification::centredRight);
  orclab->setEditable (false, false, false);

  orcfile = new FilenameComponent(String::empty, 
				  String::empty,
				  true, 
				  false, 
				  false, 
				  T("*.orc;*.csd"),
				  String::empty,
				  T("(choose .orc file)"));
  orcfile->setBrowseButtonText(T("Browse..."));
  orcfile->addListener(this);
  StringArray files=cs->orchestras.getAllFilenames();
  orcfile->setRecentlyUsedFilenames(files);
  if (files.size() > 0)
    orcfile->setCurrentFile(cs->orchestras.getFile(0), false, false);
  addAndMakeVisible(orcfile);

  addAndMakeVisible(hdrlab = new Label(String::empty, T("Header:")));
  hdrlab->setFont(Font(15.0000f, Font::plain));
  hdrlab->setJustificationType(Justification::centredRight);
  hdrlab->setEditable(false, false, false);
  hdrlab->setColour(TextEditor::textColourId, Colours::black);
  hdrlab->setColour(TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible(header = new TextEditor(String::empty));
  header->setColour(TextEditor::backgroundColourId, Colours::white);
  header->setColour(TextEditor::outlineColourId,  Colour (0xb2808080));
  header->setMultiLine(true);
  header->setReturnKeyStartsNewLine(true);
  header->setText(cs->getScoreHeader(), false);
  header->addListener(this);
  int m=8, l=24;
  //  setSize (600, 96 + 24 + 16);
  setSize (600,m+l+m+l+m+l+m+l+l+m);
}

CsoundSettingsDialog::~CsoundSettingsDialog()
{
  deleteAndZero(csolab);
  deleteAndZero(csound);
  deleteAndZero(optlab);
  deleteAndZero(options);
  deleteAndZero(orclab);
  deleteAndZero(orcfile);
  deleteAndZero(hdrlab);
  deleteAndZero(header);
}


void Csound::openSettings()
{
  CsoundSettingsDialog* dialog=new CsoundSettingsDialog();
  DialogWindow::showModalDialog(T("Csound Settings"),
				dialog,
				NULL,
				Colour(0xffe5e5e5),
				true,
				true,
				true);
  savePrefs();
  delete dialog;
}

void CsoundSettingsDialog::resized()
{

  int m=8;
  int x1=m;
  int m1=80;
  int x2=100;
  int y=m;
  int w=getRight();
  int h=getHeight();

  csolab->setBounds(x1, y, m1, 24);
  csound->setBounds(x2, y, w-x2-m, 24);

  y=y+24+m;
  optlab->setBounds (x1, y, m1, 24);
  options->setBounds(x2, y, w-x2-m, 24);

  y=y+24+m;
  orclab->setBounds(x1,  y, m1, 24);
  orcfile->setBounds(x2, y, w-x2-m, 24);

  y=y+24+m;
  hdrlab->setBounds(x1, y, m1, 24);
  header->setBounds(x2, y, w-x2-m, h-y-m);
}

void CsoundSettingsDialog::textEditorTextChanged(TextEditor& ed) {}

void CsoundSettingsDialog::textEditorReturnKeyPressed(TextEditor& ed) {}

void CsoundSettingsDialog::textEditorEscapeKeyPressed(TextEditor& ed) {}

void CsoundSettingsDialog::textEditorFocusLost(TextEditor& ed)
{
  // if NOT modal
  Csound::getInstance()->setScoreHeader(ed.getText());
}

void CsoundSettingsDialog::updateOptions()
{
  options->clear();
  XmlElement* args=Csound::getInstance()->getCommandArgs();
  int num=args->getNumChildElements();
  // create a combo item for each arg with id set to index+1;
  for (int index=0; index<num; index++)
    options->addItem(args->getChildElement(index)->getStringAttribute(T("text")), index+1);
  options->addSeparator();
  options->addItem(T("New"), 1000);
  options->addItem(T("Delete"), 1001);
  // disable Delete if only one item
  if (num<2)
    options->setItemEnabled(1001, false);
  int sel=args->getIntAttribute(T("index")); // selected arg
  options->setSelectedId(sel+1, true);
  options->setText(Csound::getInstance()->getApplicationArgs(), true);
  //  std::cout << "updateOptions: selected item is " << sel << " (id " << sel+1 << ")\n";
}

void CsoundSettingsDialog::comboBoxChanged(ComboBox* combobox)
{
  XmlElement* commandargs=Csound::getInstance()->getCommandArgs();
  int id=combobox->getSelectedId();
  if (id==1000) // New item
    {
      Csound::getInstance()->setApplicationArgs(T("(add text)"));
      updateOptions();
    }
  else if (id==1001) // Delete item
    {
      int ind=commandargs->getIntAttribute(T("index"));
      XmlElement* sel=commandargs->getChildElement(ind);
      commandargs->removeChildElement(sel, true);
      commandargs->setAttribute(T("index"), 0);
      updateOptions();
    }
  else if (id>0) // selected an arg
    {
      int index=combobox->indexOfItemId(id);
      commandargs->setAttribute(T("index"), index);
    }
  else // edited current arg
    {
      int index=commandargs->getIntAttribute(T("index"));
      if (XmlElement* xml=commandargs->getChildElement(index))
        {
          String text=combobox->getText();
          xml->setAttribute(T("text"), text);
          combobox->changeItemText(index+1, text);
        }
      else std::cout << "no CommandArgs xml element for index=" << index << "\n";
    }
}

void CsoundSettingsDialog::filenameComponentChanged(FilenameComponent* comp)
{
  if (comp==orcfile)
    Csound::getInstance()->setOrcFile(comp->getCurrentFile());
  else if (comp==csound)
    Csound::getInstance()->setApplication(comp->getCurrentFile());
}

void CsoundSettingsDialog::buttonClicked(Button* clicked) 
{
}

/*=======================================================================*
                             Export Score Dialog
 *=======================================================================*/

void Csound::exportScore()
{
  ExportCsoundDialog* dlg=new ExportCsoundDialog();
  int flag=DialogWindow::showModalDialog(T("Export Csound"), 
					 dlg,
					 NULL,
					 Colour(0xffe5e5e5),
					 true,
					 false,
					 false);
  if (flag != 1)
    {
      delete dlg;
      return;
    }
  double start=dlg->frombuffer->getText().getDoubleValue();
  double endtime=dlg->tobuffer->getText().getDoubleValue();
  int format=dlg->formatmenu->getSelectedId();
  bool addi=dlg->itoggle->getToggleState();
  bool addf=dlg->ftoggle->getToggleState();
  int dest;
  if (dlg->consoletoggle->getToggleState())
    dest=ExportIDs::ToConsole;
  else if (dlg->clipboardtoggle->getToggleState())
    dest=ExportIDs::ToClipboard;
  else 
    dest=ExportIDs::ToFile;
  delete dlg;
  writeScore(dest, format, start, endtime, addi, addf);
}

ExportCsoundDialog::ExportCsoundDialog ()
  : scoregroup (0),
    fromlabel (0),
    tolabel (0),
    frombuffer (0),
    tobuffer (0),
    formatlabel (0),
    formatmenu (0),
    exportgroup (0),
    consoletoggle (0),
    clipboardtoggle (0),
    filetoggle (0),
    itoggle (0),
    ftoggle (0),
    exportbutton (0),
    filechooser (0) 
{
  scoregroup = new GroupComponent (String::empty, T("Score"));
  addAndMakeVisible (scoregroup);
  addAndMakeVisible (fromlabel = new Label (String::empty, T("From:")));
  fromlabel->setFont (Font (15.0000f, Font::plain));
  fromlabel->setJustificationType (Justification::centredRight);
  fromlabel->setEditable (false, false, false);
  fromlabel->setColour (TextEditor::textColourId, Colours::black);
  fromlabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
 
  frombuffer = new Label (T("From"), String::empty);
  addAndMakeVisible (frombuffer);
  frombuffer->setFont (Font (15.0000f, Font::plain));
  frombuffer->setEditable (true, true, false);
  frombuffer->setColour (Label::outlineColourId,  Colour (0xb2808080));
  frombuffer->setColour (Label::backgroundColourId, Colours::white);
  frombuffer->addListener (this);

  tolabel = new Label (String::empty, T("To:"));
  addAndMakeVisible (tolabel);
  tolabel->setFont (Font (15.0000f, Font::plain));
  tolabel->setJustificationType (Justification::centredLeft);
  tolabel->setEditable (false, false, false);
  tolabel->setColour (TextEditor::textColourId, Colours::black);
  tolabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  tobuffer = new Label (T("To"), String::empty);
  addAndMakeVisible (tobuffer);
  tobuffer->setFont (Font (15.0000f, Font::plain));
  tobuffer->setJustificationType (Justification::centredLeft);
  tobuffer->setEditable (true, true, false);
  tobuffer->setColour (Label::outlineColourId, Colour (0xb2808080));
  tobuffer->setColour (Label::backgroundColourId, Colours::white);
  tobuffer->addListener (this);
  
  formatlabel = new Label (String::empty, T("Export Format:"));
  addAndMakeVisible (formatlabel);
  formatlabel->setFont (Font (15.0000f, Font::plain));
  formatlabel->setJustificationType (Justification::centredRight);
  formatlabel->setEditable (false, false, false);
  formatlabel->setColour (Label::textColourId, Colours::black);
  formatlabel->setColour (Label::backgroundColourId, Colour (0x0));
  
  formatmenu = new ComboBox (String::empty);
  addAndMakeVisible (formatmenu);
  formatmenu->setEditableText (false);
  formatmenu->setJustificationType (Justification::centredLeft);
  formatmenu->setTextWhenNothingSelected (String::empty);
  formatmenu->addItem (T("Csound score"), ExportIDs::CsoundScore);
  formatmenu->addItem (T("SAL data"), ExportIDs::SalData);
  formatmenu->addItem (T("Lisp data"), ExportIDs::LispData);
  formatmenu->addItem (T("SAL sends"), ExportIDs::SalSend);
  formatmenu->addItem (T("Lisp sends"), ExportIDs::LispSend);
  formatmenu->addListener (this);
  formatmenu->setSelectedId(ExportIDs::CsoundScore,false);
 
  exportgroup = new GroupComponent (String::empty, T("Export To"));
  addAndMakeVisible (exportgroup);
  
  consoletoggle = new ToggleButton (String::empty);
  addAndMakeVisible (consoletoggle);
  consoletoggle->setButtonText (T("Console"));
  consoletoggle->setRadioGroupId (1);
  consoletoggle->setToggleState (true, false);
  consoletoggle->addListener (this);

  clipboardtoggle = new ToggleButton (String::empty);
  addAndMakeVisible (clipboardtoggle);
  clipboardtoggle->setButtonText (T("Clipboard"));
  clipboardtoggle->setRadioGroupId (1);
  clipboardtoggle->addListener (this);
  
  filetoggle = new ToggleButton (String::empty);
  addAndMakeVisible (filetoggle);
  filetoggle->setButtonText (T("File:"));
  filetoggle->setRadioGroupId (1);
  filetoggle->addListener (this);
  
  itoggle = new ToggleButton (String::empty);
  addAndMakeVisible (itoggle);
  itoggle->setButtonText (T(" i statements"));
  itoggle->setToggleState (true, false);
  
  ftoggle = new ToggleButton (String::empty);
  addAndMakeVisible (ftoggle);
  ftoggle->setButtonText (T("f statements"));
  ftoggle->setToggleState (true, false);
  
  exportbutton = new TextButton (T("Export"));
  addAndMakeVisible (exportbutton);
  exportbutton->addListener (this);
  
  filechooser = new FilenameComponent(T("File"), 
				      File::getSpecialLocation(File::userHomeDirectory).getChildFile(T("test.sco")),
				       true, 
				       false, 
				       true, 
				       String::empty,
				       String::empty,
				       T("(choose file)"));
  filechooser->setEnabled(false);
  filechooser->addListener(this);
  addAndMakeVisible(filechooser);

  setSize (568, 248);
}

ExportCsoundDialog::~ExportCsoundDialog()
{
  deleteAndZero (scoregroup);
  deleteAndZero (fromlabel);
  deleteAndZero (tolabel);
  deleteAndZero (frombuffer);
  deleteAndZero (tobuffer);
  deleteAndZero (formatlabel);
  deleteAndZero (formatmenu);
  deleteAndZero (exportgroup);
  deleteAndZero (consoletoggle);
  deleteAndZero (clipboardtoggle);
  deleteAndZero (filetoggle);
  deleteAndZero (itoggle);
  deleteAndZero (ftoggle);
  deleteAndZero (exportbutton);
  deleteAndZero (filechooser);
}

void ExportCsoundDialog::resized()
{
  scoregroup->setBounds (16, 8, 536, 80);
  fromlabel->setBounds (25, 28, 48, 24);
  tolabel->setBounds (161, 28, 32, 24);
  frombuffer->setBounds (81, 28, 64, 24);
  tobuffer->setBounds (201, 28, 64, 24);
  formatlabel->setBounds (281, 28, 95, 24);
  formatmenu->setBounds (385, 28, 150, 24);
  exportgroup->setBounds (16, 101, 536, 80);
  consoletoggle->setBounds (32, 128, 80, 24);
  clipboardtoggle->setBounds (118, 128, 88, 24);
  filetoggle->setBounds (216, 128, 56, 24);
  itoggle->setBounds (32, 56, 104, 24);
  ftoggle->setBounds (144, 56, 104, 24);
  exportbutton->setBounds (216, 200, 150, 24);
  filechooser->setBounds (280, 128, 256, 24);
}

void ExportCsoundDialog::labelTextChanged (Label* labelThatHasChanged)
{
}

void ExportCsoundDialog::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
}

void ExportCsoundDialog::buttonClicked(Button* buttonThatWasClicked)
{
  if (buttonThatWasClicked == filetoggle)
    if ( filetoggle->getToggleState() )
      filechooser->setEnabled(true);
    else
      filechooser->setEnabled(false);
  else if (buttonThatWasClicked == exportbutton)
    ((DialogWindow *)getTopLevelComponent())->exitModalState(1);
  else
    filechooser->setEnabled(false);
}

void ExportCsoundDialog::filenameComponentChanged(FilenameComponent* comp)
{
}

#endif
