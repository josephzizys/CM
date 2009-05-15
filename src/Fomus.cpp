/*=======================================================================*
  Copyright (C) 2009 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#include "juce.h"
#include "Enumerations.h"
#include "Fomus.h"
#include <fomus/infoapi.h>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <limits>
#include "Console.h"

#warning "get rid of debugging output"

// Notes:
// Make sure this is in the ConsoleWindow class in Console.h:
// TooltipWindow xxx;

/*=======================================================================*
                             Fomus Instance
 *=======================================================================*/

juce_ImplementSingleton(Fomus);

void spitout(const char* str) 
{
  Console::getInstance()->printOutput(String(";; ") + str);
}

void initfomus()
{
  static bool in = false;
  if (!in) 
    {
      fomus_init();
      fomus_set_outputs(&spitout, &spitout, true);
      in = true;
    }
}

void Fomus::newScore()
{
  FomusScore* score= new FomusScore(); 
  score->name=T("(untitled)");
  scores.add(score);
  current=scores.size()-1;
}

void Fomus::deleteScore()
{
  // insist on at least one score
  if (scores.size()>0)
    {
      FomusScore* fms=scores.getUnchecked(current);
      scores.removeObject(fms, false);
      current=scores.size()-1;
    }
}

void Fomus::clearScore()
{
  fomus_clear(getfomusdata());
}

void Fomus::loadScore(String filename)
{
  fomus_load(getfomusdata(), (char*)filename.toUTF8());
  scores.getUnchecked(current)->name 
    = File(fomus_get_sval(getfomusdata(), "filename")).getFileName();
}

void Fomus::runScore()
{
  if (String(fomus_get_sval(getfomusdata(), "filename")).isEmpty())
    {
#ifdef GRACE
      renameScoreDialog();
#endif
    }
  std::cout << "RUNNING" << std::endl;
  fomus_run(fomus_copy(getfomusdata()));
}


void Fomus::ival(fomus_param par, fomus_action act, fomus_int val)
{
  fomus_ival(getfomusdata(), par, act, val);
}

void Fomus::rval(fomus_param par, fomus_action act, fomus_int num, fomus_int den)
{
  fomus_rval(getfomusdata(), par, act, num, den);
}

void Fomus::mval(fomus_param par, fomus_action act, fomus_int val, fomus_int num, fomus_int den) 
{
  fomus_mval(getfomusdata(), par, act, val, num, den);
}

void Fomus::fval(fomus_param par, fomus_action act, double val)
{
  fomus_fval(getfomusdata(), par, act, val);
}

void Fomus::sval(fomus_param par, fomus_action act, const String& val) 
{
  fomus_sval(getfomusdata(), par, act, (char*)val.toUTF8());
}

void Fomus::act(fomus_param par, fomus_action act) 
{
  fomus_act(getfomusdata(), par, act);
}

struct xmlerror
{
  String str;
  xmlerror(const String& str):str(str) {}
  void printerr() const
  {
    Console::getInstance()->printOutput("; fomus: " + str + T("\n"));
  }
};

void Fomus::sendXml(const String& xml) 
{
  try {
    std::cout << '\n' << xml.toUTF8() << std::endl;
    XmlDocument doc (xml);
    sendXml(*doc.getDocumentElement(), fomus_par_none, fomus_act_none);
  } catch (const xmlerror& e) {e.printerr();}
}

inline XmlElement* mustExist(XmlElement* x)
{
  if (x) return x;
  throw xmlerror("XML parse error");
}

// can be a struct, list, etc..

void Fomus::sendXmlSets(XmlElement& xml, fomus_param par, fomus_action act, 
			const excmap& exc, bool islist) 
{
  XmlElement* l = islist ? &xml : xml.getChildByName(T("l"));
  if (l->hasTagName(T("l"))) {
    bool wh = true;
    String key;
    forEachXmlChildElement(*l, e) {
      //if (skipfirst) skipfirst = false; else {
      if (wh) {
	//XmlElement* d = e; //;xml.getChildByName(T("s"));
	if (e->hasTagName(T("s"))) {
	  key = e->getAllSubText();
	  if (!key.isEmpty() && key[0] == ':') {
	    key = key.substring(1);
	  } else throw xmlerror("expected keyword");
	} else {
	  throw xmlerror("expected keyword");
	}
      } else {
	excmap::const_iterator i(exc.find(key));
	if (i == exc.end()) {
	  sval(fomus_par_setting, fomus_act_set, key); // setting
	  sendXmlVal(*e, i->second.par, i->second.act, i->second.wh);
	} else { // a "special" slot
	  sendXmlVal(*e, i->second.par, i->second.act, i->second.wh, true);
	  // special slot--parse XML expecting nested structs
	}
      }
      wh = !wh;
      //}
    }
    if (!wh) throw xmlerror("missing argument");
  } else throw xmlerror("expected list of keyword/argument pairs");
}

void Fomus::sendXmlEntry(XmlElement& xml) 
{
  sendXmlVal(*mustExist(mustExist(xml.getChildByName(T("time")))->getChildElement(0)), fomus_par_time, fomus_act_set, wh_none); // mandatory in scheme functions
  sendXmlVal(*mustExist(mustExist(xml.getChildByName(T("dur")))->getChildElement(0)), fomus_par_duration, fomus_act_set, wh_none);
  XmlElement* d;
  d = xml.getChildByName(T("part")); if (d) sendXmlVal(*mustExist(d->getChildElement(0)), fomus_par_part, fomus_act_set, wh_none); //else sval(fomus_par_part, fomus_act_set, lprt);
  d = xml.getChildByName(T("voice")); if (d) {
    sendXmlVal(*mustExist(d->getChildElement(0)), fomus_par_voice, fomus_act_set, wh_none);
  } else ival(fomus_par_voice, fomus_act_set, 1);
  d = xml.getChildByName(T("grtime")); if (d) sendXmlVal(*mustExist(d->getChildElement(0)), fomus_par_gracetime, fomus_act_set, wh_none);
  d = xml.getChildByName(T("marks")); if (d) {
    XmlElement* l0 = d->getChildByName(T("l"));
    if (!l0) throw xmlerror("expected list of marks");
    forEachXmlChildElement(*l0, e) {
      XmlElement* l = l0->getChildByName(T("l"));
      if (!l) {
	XmlElement* s = l0->getChildByName(T("s"));
	if (!s) throw xmlerror("expected mark id or list");
	sendXmlVal(*s, fomus_par_mark, fomus_act_set, wh_none);
      } else {
	XmlElement* n = l->getChildElement(0);
	if (!n) throw xmlerror("expected mark id");
	sendXmlVal(*n, fomus_par_mark, fomus_act_set, wh_none);
	n = xml.getChildElement(1);
	if (n) {
	  sendXmlVal(*n, fomus_par_markval, fomus_act_add, wh_none);
	  n = xml.getChildElement(2);
	  if (n) {
	    sendXmlVal(*n, fomus_par_markval, fomus_act_add, wh_none);
	    if (xml.getChildElement(3)) throw xmlerror("too many mark arguments");
	  }
	}
      }
      act(fomus_par_marklist, fomus_act_add);
    }
  }
  d = xml.getChildByName(T("sets")); if (d) sendXmlSets(*d, fomus_par_note_settingval, fomus_act_add);
}

// numbers, strings, lists, etc..

void Fomus::sendXmlVal(XmlElement& xml, fomus_param par, 
		       fomus_action act, whichstruct wh,
		       bool doeachinlist ) 
{ // if tag, force that tag
  if (xml.hasTagName(T("i"))) {
    ival(par, act, atol(xml.getAllSubText()));
  } else if (xml.hasTagName(T("r"))) {
    rval(par, act, atol(mustExist(xml.getChildByName(T("n")))->getAllSubText()),
	 atol(mustExist(xml.getChildByName(T("d")))->getAllSubText()));
  } else if (xml.hasTagName(T("f"))) {
    fval(par, act, atof(xml.getAllSubText()));
  } else if (xml.hasTagName(T("s"))) {
    #warning "switch (wh) ..."
    sval(par, act, xml.getAllSubText());
  } else if (xml.hasTagName(T("l"))) {

    if (wh != wh_none && !doeachinlist) {
      excmap exc;
      switch (wh) {
      case wh_measattr:
	exc.insert(excmap::value_type("id", sendpair(fomus_par_measattr_id,
						     fomus_act_set, wh_none)));
	sendXmlSets(xml, fomus_par_measattr_settingval, fomus_act_add, exc, true);
	Fomus::act(par, act);
	break;
      case wh_part:
	exc.insert(excmap::value_type("id", sendpair(fomus_par_part_id, 
						     fomus_act_set, wh_none)));
	exc.insert(excmap::value_type("name", sendpair(fomus_par_part_name, 
						       fomus_act_set, wh_none)));
	exc.insert(excmap::value_type("abbr", sendpair(fomus_par_part_abbr,
						       fomus_act_set, wh_none)));
	exc.insert(excmap::value_type("inst", sendpair(fomus_par_part_inst,
						       fomus_act_set, wh_inst)));
	sendXmlSets(xml, fomus_par_part_settingval, fomus_act_add, exc, true);
	Fomus::act(par, act);
	break;
      case wh_metapart:
	exc.insert(excmap::value_type("id", sendpair(fomus_par_metapart_id,
						     fomus_act_set, wh_none)));
	exc.insert(excmap::value_type("parts", sendpair(fomus_par_metapart_partmaps,
							fomus_act_set, wh_part,
							true)));
	sendXmlSets(xml, fomus_par_metapart_settingval, fomus_act_add, exc, true);
	Fomus::act(par, act);
	break;
      case wh_partsref:
	exc.insert(excmap::value_type("id", sendpair(fomus_par_partsref_id,
						     fomus_act_set, wh_none)));
	exc.insert(excmap::value_type("parts", sendpair(fomus_par_partsref_parts,
							fomus_act_set, wh_part, 
							true)));
	Fomus::act(par, act);
	break;
      case wh_inst:
	exc.insert(excmap::value_type("id", sendpair(fomus_par_inst_id, 
						     fomus_act_set, wh_none)));
	exc.insert(excmap::value_type("name", sendpair(fomus_par_inst_name,
						       fomus_act_set, wh_none)));
	exc.insert(excmap::value_type("abbr", sendpair(fomus_par_inst_abbr,
						       fomus_act_set, wh_none)));
	exc.insert(excmap::value_type("staves", sendpair(fomus_par_inst_staves,
							 fomus_act_set, wh_staff,
							 true)));
	exc.insert(excmap::value_type("imports", sendpair(fomus_par_inst_imports,
							  fomus_act_set, wh_import,
							  true)));
	exc.insert(excmap::value_type("export", sendpair(fomus_par_inst_export,
							 fomus_act_set, wh_export)));
	exc.insert(excmap::value_type("percinsts", sendpair(fomus_par_inst_percinsts,
							    fomus_act_set,
							    wh_percinst, true)));
	sendXmlSets(xml, fomus_par_inst_settingval, fomus_act_add, exc, true);
	Fomus::act(par, act);
	break;
      case wh_percinst:
	exc.insert(excmap::value_type("id", sendpair(fomus_par_percinst_id,
						     fomus_act_set, wh_none)));
	exc.insert(excmap::value_type("name", sendpair(fomus_par_percinst_name,
						       fomus_act_set, wh_none)));
	exc.insert(excmap::value_type("abbr", sendpair(fomus_par_percinst_abbr,
						       fomus_act_set, wh_none)));
	exc.insert(excmap::value_type("imports", sendpair(fomus_par_percinst_imports,
							  fomus_act_set, wh_import,
							  true)));
	exc.insert(excmap::value_type("export", sendpair(fomus_par_percinst_export,
							 fomus_act_set, wh_export)));
	sendXmlSets(xml, fomus_par_percinst_settingval, fomus_act_add, exc, true);
	Fomus::act(par, act);
	break;
      case wh_clef:
	sendXmlSets(xml, fomus_par_clef_settingval, fomus_act_add, exc, true);
	Fomus::act(par, act);
	break;
      case wh_staff:
	exc.insert(excmap::value_type("clefs", sendpair(fomus_par_staff_clefs, 
							fomus_act_set, wh_clef,
							true))); // _add? check this!
	sendXmlSets(xml, fomus_par_staff_settingval, fomus_act_add, exc,  true);
	Fomus::act(par, act);
	break;
      case wh_import:
	sendXmlSets(xml, fomus_par_import_settingval, fomus_act_add, exc, true);
	Fomus::act(par, act);
	break;
      case wh_export:
	sendXmlSets(xml, fomus_par_export_settingval, fomus_act_add, exc, true);
	Fomus::act(par, act);
      } 
      //} else goto JUSTALIST;
    } else {
      //JUSTALIST:
      if (doeachinlist) {
	forEachXmlChildElement(xml, e) sendXmlVal(*e, par, act, wh);
      } else {
	if (wh == wh_voices) {
	  // expecting list of voices
	  Fomus::act(fomus_par_voice, fomus_act_clear);
	  forEachXmlChildElement(xml, e) sendXmlVal(*e, fomus_par_voice, 
						    fomus_act_add, wh_none);
	} else {
	  Fomus::act(fomus_par_list, fomus_act_start);
	  forEachXmlChildElement(xml, e) sendXmlVal(*e, fomus_par_list, 
						    fomus_act_add, wh_none);
	  Fomus::act(fomus_par_list, fomus_act_end);
	  Fomus::act(par, act);
	}
      }
    }
  } else if (xml.hasTagName(T("b"))) {
    ival(par, act, atol(xml.getAllSubText()));
  } else {
    std::cout << (char*)xml.getTagName().toUTF8() << std::endl;
    throw xmlerror("XML parse error");
  }
}

// Top level stuff

void Fomus::sendXml(XmlElement& xml, fomus_param par, fomus_action act)
{
  std::cout << std::endl;
  if (xml.hasTagName(T("note"))) {
    sendXmlVal(*mustExist(mustExist(xml.getChildByName(T("note")))->getChildElement(0)), fomus_par_pitch, fomus_act_set, wh_none);
    XmlElement* d = xml.getChildByName(T("dyn"));
    if (d) 
      sendXmlVal(*mustExist(d->getChildElement(0)), fomus_par_dynlevel,
		 fomus_act_set, wh_none);
    else
      ival(fomus_par_dynlevel, fomus_act_set, 0);
    sendXmlEntry(xml);
    Fomus::act(fomus_par_noteevent, fomus_act_add);
  } else if (xml.hasTagName(T("rest"))) {
    sendXmlEntry(xml);
    Fomus::act(fomus_par_restevent, fomus_act_add);
  } else if (xml.hasTagName(T("mark"))) {
    sendXmlEntry(xml);
    Fomus::act(fomus_par_markevent, fomus_act_add);
  } else if (xml.hasTagName(T("meas"))) {
    sendXmlVal(*mustExist(mustExist(xml.getChildByName(T("time")))->getChildElement(0)
			  ), 
	       fomus_par_time, fomus_act_set, wh_none);
    XmlElement* d = xml.getChildByName(T("dur"));
    if (d)
      sendXmlVal(*mustExist(d->getChildElement(0)), fomus_par_duration, 
		 fomus_act_set, wh_none);
    sendXmlSets(*mustExist(xml.getChildByName(T("sets"))),
		fomus_par_measattr_settingval, fomus_act_add, excmap() );
    Fomus::act(fomus_par_meas, fomus_act_add);
  } else if (xml.hasTagName(T("measattr"))) {
    sendXmlVal(*mustExist(xml.getChildByName(T("l"))), fomus_par_measattr, 
	       fomus_act_add, wh_measattr);
  } else if (xml.hasTagName(T("part"))) {
    sendXmlVal(*mustExist(xml.getChildByName(T("l"))), fomus_par_part,
	       fomus_act_add, wh_part);
  } else if (xml.hasTagName(T("metapart"))) {
    sendXmlVal(*mustExist(xml.getChildByName(T("l"))), fomus_par_metapart,
	       fomus_act_add, wh_metapart);
  } else if (xml.hasTagName(T("partsref"))) {
    sendXmlVal(*mustExist(xml.getChildByName(T("l"))), fomus_par_partsref, 
	       fomus_act_add, wh_partsref);
  } else if (xml.hasTagName(T("inst"))) {
    sendXmlVal(*mustExist(xml.getChildByName(T("l"))), fomus_par_inst,
	       fomus_act_add, wh_inst);
  } else if (xml.hasTagName(T("percinst"))) {
    sendXmlVal(*mustExist(xml.getChildByName(T("l"))), fomus_par_percinst,
	       fomus_act_add, wh_percinst);
  } else if (xml.hasTagName(T("setting"))) {
    sendXmlSets(*mustExist(xml.getChildByName(T("sets"))), fomus_par_settingval, 
		(mustExist(xml.getChildByName(T("app")))
		 ? fomus_act_append : fomus_act_set));
  }
}

/*=======================================================================*
  Remainder of file is Grace GUI code, not part of the console CM app
 *=======================================================================*/

#ifdef GRACE

class FOMUSSettingsEditor:public TextEditor 
{
public:
  int id; // id stored so FOMUSSettings can grab it
  String name;
  FOMUS fom;
  bool change;
  FOMUSSettingsEditor(FOMUS fom, const String &componentName = String::empty,
		      const tchar passwordCharacter = 0)
 : TextEditor(componentName, passwordCharacter), 
   fom(fom),
   change(false) 
  {
  }

  juce_UseDebuggingNewOperator

  private:

  FOMUSSettingsEditor(const FOMUSSettingsEditor&);
  const FOMUSSettingsEditor& operator= (const FOMUSSettingsEditor&);

  public:

  void docheckandenter()
  {
    std::cout << "sending setting to fomus" << std::endl;
    fomus_parse(fom, (name + " = " + getText()).toUTF8());
    if (fomus_err)
      {
	AlertWindow::showMessageBox(AlertWindow::WarningIcon,
				    T("FOMUS Settings"),
				    String("Error in setting `") << name << "'.");
      }
    change = false;
  }
  void focusLost(FocusChangeType cause) 
  {
    if (change) docheckandenter();
    TextEditor::focusLost(cause);
  }
};

// SETTINGS LISTBOX ITEM

class FOMUSSettingsListBox;
class FOMUSSettingsListBoxItem:public /*Group*/Component, 
			       public ButtonListener,
			       public TextEditorListener
{
public:
  FOMUSSettingsListBoxItem (FOMUS fom, int id, struct info_setting& set,
			    const String& val, bool def);
  ~FOMUSSettingsListBoxItem();

  void resized();
  void buttonClicked(Button* buttonThatWasClicked);

  void updateset(int id, struct info_setting& set, const String& val, bool def);
  
  void textEditorTextChanged(TextEditor&) {defoff();}
  void textEditorReturnKeyPressed(TextEditor&) 
  {
    defoff();
    ValueText->docheckandenter();
  }
  void textEditorEscapeKeyPressed(TextEditor&) {defon();}
  void textEditorFocusLost(TextEditor&) {}

  juce_UseDebuggingNewOperator

  int getid() const {return ValueText->id;}
  String getstoretext() const {return ValueText->getText();}
  bool getstoredef() const {return DefaultButton->getToggleState();}
  
private:
  String defval;
  
  Label* NameLabel;
  Label* NameText;
  Label* ModuleLabel;
  Label* ModuleText;
  Label* LocationLabel;
  Label* LocationText;
  Label* UseLevelLabel;
  Label* UseLevelText;
  Label* TypeLabel;
  Label* TypeText;
  Label* ValueLabel;
  ToggleButton* DefaultButton;
  FOMUSSettingsEditor* ValueText;

  FOMUSSettingsListBox* parent;
  
  FOMUSSettingsListBoxItem (const FOMUSSettingsListBoxItem&);
  const FOMUSSettingsListBoxItem& operator= (const FOMUSSettingsListBoxItem&);

  void defoff() 
  {
    DefaultButton->setToggleState(false, false); 
    ValueText->change = true;
  }

  void defon()
  {
    ValueText->setText(defval, false);
    DefaultButton->setToggleState(true, false);
    ValueText->change = false;
    std::cout << "resetting setting to default" << std::endl;
    fomus_ival(ValueText->fom, fomus_par_setting, fomus_act_set, ValueText->id);
    fomus_act(ValueText->fom, fomus_par_settingval, fomus_act_clear);
  }
};

void FOMUSSettingsListBoxItem::updateset(int id, struct info_setting& set, 
					 const String& val, bool def)
{
  NameText->setText(set.name, false);
  NameText->setTooltip(set.descdoc);
  ModuleText->setText(set.modname, false);
  const char* loctext;
  switch (set.loc) {
  case module_noloc: loctext = "(error)"; break;
  case module_locglobal: loctext = "global"; break;
  case module_locpart: loctext = "part"; break;
  case module_locinst: loctext = "inst"; break;
  case module_locpercinst: loctext = "percinst"; break;
  case module_locpartmap: loctext = "partmap"; break;
  case module_locmeasattr: loctext = "measattr"; break;
  case module_locimport: loctext = "import"; break;
  case module_locexport: loctext = "export"; break;
  case module_locstaff: loctext = "staff"; break;
  case module_locclef: loctext = "clef"; break;
  case module_locnote: loctext = "note";
  }
  LocationText->setText(loctext, false);
  const char* usetext;
  switch (set.uselevel) {
  case 0: usetext = "beginner"; break;
  case 1: usetext = "intermediate"; break;
  case 2: usetext = "advanced"; break;
  case 3: usetext = "guru";      
  }
  UseLevelText->setText(usetext, false);
  TypeText->setText(set.typedoc, false);
  ValueText->setText(val, false);
  ValueText->id = id;
  ValueText->name = set.name;

  defval = set.valstr;
  
  DefaultButton->setToggleState (def, false);
}

FOMUSSettingsListBoxItem::FOMUSSettingsListBoxItem(FOMUS fom, int id, 
						   struct info_setting& set, 
						   const String& val, bool def)
  : Component(T("FOMUS Settings ListBox Item") ),
   NameLabel (0),
   NameText (0),
   ModuleLabel (0),
   ModuleText (0),
   LocationLabel (0),
   LocationText (0),
   UseLevelLabel (0),
   UseLevelText (0),
   TypeLabel (0),
   TypeText (0),
   ValueLabel (0),
   DefaultButton (0),
   ValueText (0) 
{
  //std::cout << "C" << std::endl;
  addAndMakeVisible (NameLabel = new Label (T("Name Label"),
					    T("Name:")));
  NameLabel->setFont (Font (13.0000f, Font::plain));
  NameLabel->setJustificationType (Justification::centredLeft);
  NameLabel->setEditable (false, false, false);
  NameLabel->setColour (TextEditor::textColourId, Colours::black);
  NameLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (NameText = new Label (T("Name Text"),
					   String::empty));
  NameText->setFont (Font (13.0000f, Font::bold));
  NameText->setJustificationType (Justification::centredLeft);
  NameText->setEditable (false, false, false);
  NameText->setColour (TextEditor::textColourId, Colours::black);
  NameText->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (ModuleLabel = new Label (T("Module Label"),
					      T("Module:")));
  ModuleLabel->setFont (Font (13.0000f, Font::plain));
  ModuleLabel->setJustificationType (Justification::centredLeft);
  ModuleLabel->setEditable (false, false, false);
  ModuleLabel->setColour (TextEditor::textColourId, Colours::black);
  ModuleLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (ModuleText = new Label (T("Module Text"),
					     String::empty));
  ModuleText->setFont (Font (13.0000f, Font::plain));
  ModuleText->setJustificationType (Justification::centredLeft);
  ModuleText->setEditable (false, false, false);
  ModuleText->setColour (TextEditor::textColourId, Colours::black);
  ModuleText->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (LocationLabel = new Label (T("Location Label"),
						T("Location:")));
  LocationLabel->setFont (Font (13.0000f, Font::plain));
  LocationLabel->setJustificationType (Justification::centredLeft);
  LocationLabel->setEditable (false, false, false);
  LocationLabel->setColour (TextEditor::textColourId, Colours::black);
  LocationLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (LocationText = new Label (T("Location Text"),
					       String::empty));
  LocationText->setFont (Font (13.0000f, Font::plain));
  LocationText->setJustificationType (Justification::centredLeft);
  LocationText->setEditable (false, false, false);
  LocationText->setColour (TextEditor::textColourId, Colours::black);
  LocationText->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (UseLevelLabel = new Label (T("UseLevel Label"),
						T("Use Level:")));
  UseLevelLabel->setFont (Font (13.0000f, Font::plain));
  UseLevelLabel->setJustificationType (Justification::centredLeft);
  UseLevelLabel->setEditable (false, false, false);
  UseLevelLabel->setColour (TextEditor::textColourId, Colours::black);
  UseLevelLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (UseLevelText = new Label (T("UseLevel Text"),
					       String::empty));
  UseLevelText->setFont (Font (13.0000f, Font::plain));
  UseLevelText->setJustificationType (Justification::centredLeft);
  UseLevelText->setEditable (false, false, false);
  UseLevelText->setColour (TextEditor::textColourId, Colours::black);
  UseLevelText->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (TypeLabel = new Label (T("Type Label"),
					    T("Type:")));
  TypeLabel->setFont (Font (13.0000f, Font::plain));
  TypeLabel->setJustificationType (Justification::centredLeft);
  TypeLabel->setEditable (false, false, false);
  TypeLabel->setColour (TextEditor::textColourId, Colours::black);
  TypeLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (TypeText = new Label (T("Type Text"),
					   String::empty));
  TypeText->setFont (Font (13.0000f, Font::plain));
  TypeText->setJustificationType (Justification::centredLeft);
  TypeText->setEditable (false, false, false);
  TypeText->setColour (TextEditor::textColourId, Colours::black);
  TypeText->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (ValueLabel = new Label (T("Value Label"),
					     T("Value:")));
  ValueLabel->setFont (Font (13.0000f, Font::plain));
  ValueLabel->setJustificationType (Justification::centredLeft);
  ValueLabel->setEditable (false, false, false);
  ValueLabel->setColour (TextEditor::textColourId, Colours::black);
  ValueLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (DefaultButton = new ToggleButton (T("Default Button")));
  DefaultButton->setButtonText (T("Default"));
  DefaultButton->addButtonListener (this);
  //DefaultButton->setToggleState (true, false);
  
  addAndMakeVisible (ValueText = new FOMUSSettingsEditor(fom, T("Value Text")));
  ValueText->setMultiLine (true);
  ValueText->setReturnKeyStartsNewLine (false);
  ValueText->setReadOnly (false);
  ValueText->setScrollbarsShown (true);
  ValueText->setCaretVisible (true);
  ValueText->setPopupMenuEnabled (true);
  //ValueText->addListener(textlistener);
  ValueText->addListener(this);
  //ValueText->setText (set.valstr);
  
  setSize (640 + 32, 16 + 72);
  
  updateset(id, set, val, def);
}

FOMUSSettingsListBoxItem::~FOMUSSettingsListBoxItem() 
{
  deleteAndZero (NameLabel);
  deleteAndZero (NameText);
  deleteAndZero (ModuleLabel);
  deleteAndZero (ModuleText);
  deleteAndZero (LocationLabel);
  deleteAndZero (LocationText);
  deleteAndZero (UseLevelLabel);
  deleteAndZero (UseLevelText);
  deleteAndZero (TypeLabel);
  deleteAndZero (TypeText);
  deleteAndZero (ValueLabel);
  deleteAndZero (DefaultButton);
  deleteAndZero (ValueText);
}

void FOMUSSettingsListBoxItem::resized() 
{
  NameLabel->setBounds (0, 8 + 0, 48, 16);
  NameText->setBounds (40, 8 + 0, 184, 16);
  ModuleLabel->setBounds (232, 8 + 0, 56, 16);
  ModuleText->setBounds (280, 8 + 0, 83, 16);
  LocationLabel->setBounds (368, 8 + 0, 56, 16);
  LocationText->setBounds (424, 8 + 0, 75, 16);
  UseLevelLabel->setBounds (504, 8 + 0, 56, 16);
  UseLevelText->setBounds (560, 8 + 0, 75, 16);
  TypeLabel->setBounds (0, 8 + 16, 40, 16);
  TypeText->setBounds (40, 8 + 16, getWidth() - 148, 16);
  ValueLabel->setBounds (0, 8 + 32, 40, 16);
  DefaultButton->setBounds (getWidth() - 100, 8 + 16, 48, 16);
  ValueText->setBounds (40, 8 + 32, getWidth() - 80, 40);
}

// LIST BOX MODEL

class FOMUSSettingsListBox;
class FOMUSListBoxModel:public ListBoxModel
{
  FOMUS fom;
public:
  struct setval {
    String val;
    bool def;
    setval(const String& val, bool def):val(val), def(def) {}
    void store(const String& va, bool de) {val = va; def = de;}
  };
private:
  struct info_setlist sets;
  FOMUSSettingsListBox* textlistener;
  std::map<int, setval>& vals;
public:
  FOMUSListBoxModel(FOMUS fom, int uselvl, FOMUSSettingsListBox* textlistener, std::map<int, setval>& vals):
    ListBoxModel(), textlistener(textlistener), fom(fom), vals(vals) {
    getsettings(fom, uselvl);
  }
  int getNumRows() {return sets.n;}
  void paintListBoxItem(int rowNumber, Graphics &g, int width, int height, bool rowIsSelected) {}
  Component* refreshComponentForRow(int rowNumber, bool isRowSelected, Component *existingComponentToUpdate);
  void getsettings(FOMUS fom, int uselvl) {
    struct info_setfilter se = {0, 0, 0, module_nomodtype, 0, module_noloc, uselvl, info_none}; 
    struct info_setfilterlist fi = {1, &se};
    sets = info_list_settings(fom, &fi, 0, 0, -1);
  }
};

// SETTINGS LISTBOX

class FOMUSSettingsListBox:public ListBox
{
public:
  FOMUSSettingsListBox (FOMUS fom, int lvl )
    : ListBox(T("FOMUS ListBox"), 
	      new FOMUSListBoxModel(fom, lvl, this, vals)),
      fom(fom) 
  {
    setRowHeight(16 + 72);
  }
  ~FOMUSSettingsListBox() {delete getModel();}

  juce_UseDebuggingNewOperator

private:
  FOMUS fom;
  FOMUSSettingsListBox (const FOMUSSettingsListBox&);
  const FOMUSSettingsListBox& operator= (const FOMUSSettingsListBox&);

  std::map<int, FOMUSListBoxModel::setval> vals;
};

void FOMUSSettingsListBoxItem::buttonClicked(Button* buttonThatWasClicked) {
  if (buttonThatWasClicked == DefaultButton) {
    if (DefaultButton->getToggleState()) {
      ValueText->setText(defval, false);
      defon();
    }
  }
}

Component* FOMUSListBoxModel::refreshComponentForRow
(int rowNumber, bool isRowSelected, Component *existingComponentToUpdate) 
{
  if (rowNumber >= sets.n) 
    {
      if (existingComponentToUpdate) 
	{
	  int id = ((FOMUSSettingsListBoxItem*)existingComponentToUpdate)->getid();
	  vals.erase(id);
	  vals.insert(std::map<int, setval>::value_type(id, setval(((FOMUSSettingsListBoxItem*)existingComponentToUpdate)->getstoretext(),
							       ((FOMUSSettingsListBoxItem*)existingComponentToUpdate)->getstoredef())));
      if (((FOMUSSettingsListBoxItem*)existingComponentToUpdate)->hasKeyboardFocus(true)) textlistener->grabKeyboardFocus();
      delete existingComponentToUpdate;
    }
    return 0;
  }
  if (existingComponentToUpdate) {
    if (((FOMUSSettingsListBoxItem*)existingComponentToUpdate)->getid() != rowNumber) {
      int id = ((FOMUSSettingsListBoxItem*)existingComponentToUpdate)->getid();
      vals.erase(id);
      vals.insert(std::map<int, setval>::value_type(id, setval(((FOMUSSettingsListBoxItem*)existingComponentToUpdate)->getstoretext(),
							       ((FOMUSSettingsListBoxItem*)existingComponentToUpdate)->getstoredef())));
      std::map<int, setval>::iterator v(vals.find(rowNumber));
      if (((FOMUSSettingsListBoxItem*)existingComponentToUpdate)->hasKeyboardFocus(true)) textlistener->grabKeyboardFocus();
      if (v != vals.end()) { // got a stored value user was editing
	((FOMUSSettingsListBoxItem*)existingComponentToUpdate)->updateset(rowNumber, sets.sets[rowNumber], v->second.val, v->second.def);
	vals.erase(v);
      } else {
	((FOMUSSettingsListBoxItem*)existingComponentToUpdate)->updateset(rowNumber, sets.sets[rowNumber], sets.sets[rowNumber].valstr, /*true*/ sets.sets[rowNumber].where < info_config);
      }
    }
    return existingComponentToUpdate;
  } else {
    std::map<int, setval>::iterator v(vals.find(rowNumber));
    if (v != vals.end()) { // got a stored value user was editing
      FOMUSSettingsListBoxItem* r = new FOMUSSettingsListBoxItem(fom, rowNumber, sets.sets[rowNumber],  v->second.val, v->second.def);
      vals.erase(v);
      return r;
    } else {
      return new FOMUSSettingsListBoxItem(fom, rowNumber, sets.sets[rowNumber], 
					  sets.sets[rowNumber].valstr, 
					  sets.sets[rowNumber].where < info_config);
    }
  }
}

// SETTINGS COMPONENT
class FOMUSSettings:public Component, public ButtonListener
{
public:
  FOMUSSettings (FOMUS fom);
    ~FOMUSSettings();
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    juce_UseDebuggingNewOperator
private:
  int uselevel;
  void switchtouse(int lvl) {
    if (lvl != uselevel) {
      uselevel = lvl;
      removeChildComponent (component);
      addAndMakeVisible (component = new FOMUSSettingsListBox (fom, lvl ));
      component->setBounds (0, 16, getWidth(), getHeight() - 16);
    }
  }
  FOMUS fom;
  FOMUSSettingsListBox* component;
  ToggleButton* BeginnerButton;
  ToggleButton* IntermediateButton;
  ToggleButton* AdvancedButton;
  ToggleButton* GuruButton;
  FOMUSSettings (const FOMUSSettings&);
  const FOMUSSettings& operator= (const FOMUSSettings&);
};

FOMUSSettings::FOMUSSettings(FOMUS fom )
  : Component(T("FOMUSSettings") ),
    uselevel(0), fom(fom), 
    component (0),
    BeginnerButton (0),
    IntermediateButton (0),
    AdvancedButton (0),
    GuruButton (0)
{
  addAndMakeVisible (component = new FOMUSSettingsListBox (fom, 0 ));
  addAndMakeVisible (BeginnerButton = new ToggleButton (T("Beginner Button")));
  BeginnerButton->setButtonText (T("Beginner"));
  BeginnerButton->setRadioGroupId (1);
  BeginnerButton->addButtonListener (this);
  BeginnerButton->setToggleState (true, false);
  
  addAndMakeVisible(IntermediateButton = new ToggleButton (T("Intermediate Button")));
  IntermediateButton->setButtonText (T("Intermediate"));
  IntermediateButton->setRadioGroupId (1);
  IntermediateButton->addButtonListener (this);
  
  addAndMakeVisible (AdvancedButton = new ToggleButton (T("Advanced Button")));
  AdvancedButton->setButtonText (T("Advanced"));
  AdvancedButton->setRadioGroupId (1);
  AdvancedButton->addButtonListener (this);
  
  addAndMakeVisible (GuruButton = new ToggleButton (T("Guru Button")));
  GuruButton->setButtonText (T("Guru"));
  GuruButton->setRadioGroupId (1);
  GuruButton->addButtonListener (this);
  
  //setSize (640 + 32, 400);
}

FOMUSSettings::~FOMUSSettings() 
{
  deleteAndZero (component);
  deleteAndZero (BeginnerButton);
  deleteAndZero (IntermediateButton);
  deleteAndZero (AdvancedButton);
  deleteAndZero (GuruButton);
}

void FOMUSSettings::resized()
{
  component->setBounds (0, 16, getWidth(), getHeight() - 16);
  BeginnerButton->setBounds (0, 0, 56, 16);
  IntermediateButton->setBounds (56, 0, 72, 16);
  AdvancedButton->setBounds (128, 0, 64, 16);
  GuruButton->setBounds (184, 0, 56, 16);
}

void FOMUSSettings::buttonClicked (Button* buttonThatWasClicked)
{
  if (buttonThatWasClicked == BeginnerButton) {
    switchtouse(0);
  } else if (buttonThatWasClicked == IntermediateButton) {
    switchtouse(1);
  } else if (buttonThatWasClicked == AdvancedButton) {
    switchtouse(2);
  } else if (buttonThatWasClicked == GuruButton) {
    switchtouse(3);
  }
}

struct FileTabs:public TabbedComponent
{
  FileTabs(FOMUS fom ):TabbedComponent(TabbedButtonBar::TabsAtTop)
  {
    addTab(T("Settings"), Colours::white, new FOMUSSettings(fom ), true);
    addTab(T("Parts"), Colours::white, new Component(), true);
    addTab(T("Measure Attributes"), Colours::white, new Component(), true);
    addTab(T("Instruments"), Colours::white, new Component(), true);
    addTab(T("Percussion Instruments"), Colours::white, new Component(), true);

    setSize (900, 600);
  }
};

#define FILE_WIDTH 120


struct makenstring 
{
  int n;
  makenstring(const int n):n(n) {}
};

inline std::ostream& operator<<(std::ostream& s, const makenstring x) 
{
  for (int i = 0; i < x.n; ++i) s << ' ';
}

void out_justify(std::ostream& f, String s, const int start = 0, bool va = true) {
  //replace_all(s, "\t", string(8, ' '));
  s.replace(T("\t"), T("        "));
  int i = 0;
  int je = s.length();
  const String exc("\"'`{[(");
  for (int j = (FILE_WIDTH - 1) - start; j < je; j += (FILE_WIDTH - 1) - start) {
    int js = i;
    while (js < j && s[js] != '\n') ++js;
    if (js < j) {
      f << (const char*)s.substring(i, ++js) << makenstring(start);
      i = j = js;
    } else {
      js = j;
      while (j > i && (va ? s[j] == ' ' : !(isalnum(s[j]) || exc.containsChar(s[j])))) --j;
      while (j > i && (va ? s[j - 1] != ' ' : isalnum(s[j - 1]) || exc.containsChar(s[j - 1]))) --j;
      if (j > i) {
	f << (const char*)s.substring(i, j) << "\n" << makenstring(start);
	i = j;
      } else {
	f << (const char*)s.substring(i, js) << "\n" << makenstring(start);
	i = j = js;
      }
    }
  }
  f << (const char*)s.substring(i);
}


class FomusDialogWindow : public DocumentWindow
{
public:
  FomusDialogWindow(String title)
    : DocumentWindow(title, Colour(0xffe5e5e5), DocumentWindow::allButtons)
  {
    setUsingNativeTitleBar(true);
    setDropShadowEnabled(true);
    setWantsKeyboardFocus(false);
    setResizable(true, true);
  }
  ~FomusDialogWindow()
  {
  }
  void closeButtonPressed()
  {
    delete this;
  }
};


void Fomus::settingsWindow() 
{  
  /* THIS WOULD BE A NON-MODAL VERSION
  FileTabs* t=new FileTabs(getfomusdata());
  t->setVisible(true);
  FomusDialogWindow* w = new FomusDialogWindow(T("FOMUS Settings"));
  w->setContentComponent(t, true, true);
  w->setVisible(true);
  w->centreWithSize(t->getWidth(),t->getHeight());
  w->toFront(true); 
  */

  FileTabs* f=new FileTabs(getfomusdata());
  DialogWindow::showModalDialog(T("FOMUS Settings"), f, 0, 
				Colour(0xffe5e5e5), true, true, true);
  delete f;
  scores.getUnchecked(current)->name =
    File(fomus_get_sval(getfomusdata(), "filename")).getFileName();

}


struct FOMUSViewComponent:public Component 
{
  TextLayout lay;
  FOMUSViewComponent():Component() {}
  FOMUSViewComponent(const String &componentName):Component(componentName) {}
  void paint (Graphics& g) {lay.draw(g, 0, 0);}
};

struct FOMUSTabbedComp:public Component 
{
  FOMUSTabbedComp():Component() {}
  FOMUSTabbedComp(const String &componentName):Component(componentName)  {}
  virtual void doupdate(const String& sch, const int but) = 0;
};

class FOMUSSetsView:public FOMUSTabbedComp, public ButtonListener {
  int skill;
  TextEditor& textEditor;
  int& thebut;
public:
  FOMUSSetsView(TextEditor& textEditor, int& thebut);
  ~FOMUSSetsView();
  void paint (Graphics& g);
  void resized();
  void buttonClicked (Button* buttonThatWasClicked);
  juce_UseDebuggingNewOperator
  private:
  ToggleButton* BegButton;
  ToggleButton* MedButton;
  ToggleButton* AdvButton;
  ToggleButton* GuruButton;
  Viewport* viewport;
  FOMUSSetsView (const FOMUSSetsView&);
  const FOMUSSetsView& operator=(const FOMUSSetsView&);
  void doupdate(const String& sch, const int but);
};

void FOMUSSetsView::doupdate(const String& sch, const int but) {
  struct info_setfilter ff = {0, 0, 0, module_nomodtype, 0, module_noloc, skill, info_none};
  struct info_setfilterlist fff = {1, &ff};
  struct info_setsearch s = {0, 0, 0, 0, 0, 0};
  switch (but) {

  case 0: s.name = sch.toUTF8(); break;
  case 1: s.doc = sch.toUTF8();
  }
  struct info_setlist lst(info_list_settings(0, &fff, &s, 0, 0));
  TextLayout& lay = ((FOMUSViewComponent*)(viewport->getViewedComponent()))->lay;
  lay.clear();
  Font no(13);
  //Font no2(4);
  Font ul(13, Font::underlined);
  Font bo(13, Font::bold);
  Font it(13, Font::italic);
  for (struct info_setting* i(lst.sets), *ie(lst.sets + lst.n); i < ie; ++i) {
    lay.appendText("name:", ul); lay.appendText(" ", no); lay.appendText(i->name, bo); lay.appendText("  ", no);
    lay.appendText("module:", ul); lay.appendText(" ", no); lay.appendText(i->modname, no); lay.appendText("  ", no);
    String lo(settingloc_to_str(i->loc));
    lay.appendText("location:", ul); lay.appendText(" ", no); lay.appendText(lo, no); lay.appendText("  ", no);
    lay.appendText("use level:", ul); lay.appendText(" ", no);
    switch (i->uselevel) {
    case 0: lo = "0 beginner\n"; break;
    case 1: lo = "1 intermediate\n"; break;
    case 2: lo = "2 advanced\n"; break;
    case 3: lo = "3 guru\n";      
    }
    lay.appendText(lo, no);
    std::ostringstream ou0;
    lay.appendText("type:", ul); lay.appendText(" ", no);
    out_justify(ou0, i->typedoc, 6, true); 
    lay.appendText(ou0.str().c_str(), no); lay.appendText("\n", no);
    std::ostringstream ou;
    lay.appendText("default value:", ul); lay.appendText(" ", no);
    out_justify(ou, i->valstr, 15, true); 
    lay.appendText(ou.str().c_str(), no); lay.appendText("\n", no);
    std::ostringstream ou2;
    out_justify(ou2, i->descdoc, 0, false);
    lay.appendText(ou2.str().c_str(), it); lay.appendText("\n\n", no);
  }
  lay.layout(std::numeric_limits<int>::max() / 2, Justification::topLeft, false);
  viewport->getViewedComponent()->setSize(lay.getWidth(), lay.getHeight());
  viewport->setViewPosition(0, 0);
  viewport->repaint();
}

FOMUSSetsView::FOMUSSetsView(TextEditor& textEditor, int& thebut)
 : FOMUSTabbedComp( T("FOMUS Settings Documentation")),
   BegButton(0), 
   MedButton(0),
   AdvButton(0),
   GuruButton(0), 
   viewport(0), 
   skill(0), 
   textEditor(textEditor),
   thebut(thebut)
{
  addAndMakeVisible (BegButton = new ToggleButton (T("Beginner Button")));
  BegButton->setButtonText (T("Beginner"));
  BegButton->setRadioGroupId (2);
  BegButton->addButtonListener (this);
  BegButton->setToggleState (true, false);
  
  addAndMakeVisible (MedButton = new ToggleButton (T("Intermediate Button")));
  MedButton->setButtonText (T("Intermediate"));
  MedButton->setRadioGroupId (2);
  MedButton->addButtonListener (this);
  
  addAndMakeVisible (AdvButton = new ToggleButton (T("Advanced Button")));
  AdvButton->setButtonText (T("Advanced"));
  AdvButton->setRadioGroupId (2);
  AdvButton->addButtonListener (this);
  
  addAndMakeVisible (GuruButton = new ToggleButton (T("Guru Button")));
  GuruButton->setButtonText (T("Guru"));
  GuruButton->setRadioGroupId (2);
  GuruButton->addButtonListener (this);
  
  addAndMakeVisible (viewport = new Viewport (T("Viewport")));
  viewport->setViewedComponent(new FOMUSViewComponent(T("View Component")));
  
  //setSize (600, 400);
}

FOMUSSetsView::~FOMUSSetsView() 
{
  deleteAndZero (BegButton);
  deleteAndZero (MedButton);
  deleteAndZero (AdvButton);
  deleteAndZero (GuruButton);
  deleteAndZero (viewport);
}

inline void FOMUSSetsView::paint (Graphics& g) 
{
  g.fillAll (Colours::white);
}

void FOMUSSetsView::resized() 
{
  BegButton->setBounds (0, 0, 56, 16);
  MedButton->setBounds (56, 0, 72, 16);
  AdvButton->setBounds (128, 0, 64, 16);
  GuruButton->setBounds (184, 0, 56, 16);
  viewport->setBounds (8, 24, getWidth() - 14, getHeight() - 30);
}

void FOMUSSetsView::buttonClicked(Button* buttonThatWasClicked)
{
  if (buttonThatWasClicked == BegButton) {
    skill = 0; 
  } else if (buttonThatWasClicked == MedButton) {
    skill = 1;
  } else if (buttonThatWasClicked == AdvButton) {
    skill = 2;
  } else if (buttonThatWasClicked == GuruButton) {
    skill = 3;
  } else return;
  doupdate(textEditor.getText(), thebut);
}

class FOMUSDocView:public FOMUSTabbedComp
{
public:
  FOMUSDocView( );
  ~FOMUSDocView();
  void paint (Graphics& g);
  void resized();
  juce_UseDebuggingNewOperator
  Viewport* viewport;
private:
  FOMUSDocView(const FOMUSDocView&);
  const FOMUSDocView& operator=(const FOMUSDocView&);
};

inline FOMUSDocView::FOMUSDocView( )
 : FOMUSTabbedComp(T("FOMUS Documentation View")),
   viewport(0)
{
  addAndMakeVisible (viewport = new Viewport (T("new viewport")));
  viewport->setViewedComponent(new FOMUSViewComponent(T("View Component")));
}

inline FOMUSDocView::~FOMUSDocView()
{
  deleteAndZero (viewport);
}

inline void FOMUSDocView::paint(Graphics& g)
{
  g.fillAll (Colours::white);
}

inline void FOMUSDocView::resized() 
{
  viewport->setBounds (8, 8, getWidth() - 14, getHeight() - 14);
}

struct FOMUSMarksView:public FOMUSDocView 
{
  FOMUSMarksView():FOMUSDocView() {}
  void doupdate(const String& sch, const int but);
};

void FOMUSMarksView::doupdate(const String& sch, const int but) 
{
  struct info_marksearch s = {0, 0, 0, 0, 0, 0};
  switch (but) {
  case 0: s.name = sch.toUTF8(); break;
  case 1: s.doc = sch.toUTF8();
  }
  struct info_marklist lst(info_list_marks(0, 0, &s, 0, 0));
  TextLayout& lay = ((FOMUSViewComponent*)(viewport->getViewedComponent()))->lay;
  lay.clear();
  Font no(13);
  Font ul(13, Font::underlined);
  Font bo(13, Font::bold);
  Font it(13, Font::italic);
  for (struct info_mark* i(lst.marks), *ie(lst.marks + lst.n); i < ie; ++i) {
    lay.appendText("name:", ul); lay.appendText(" ", no); lay.appendText(i->name, bo); lay.appendText("  ", no);
    lay.appendText("arguments:", ul); lay.appendText(" ", no); lay.appendText("(fix me)", no); lay.appendText("\n", no);
    std::ostringstream ou;
    out_justify(ou, i->doc, 0, false);
    lay.appendText(ou.str().c_str(), it); lay.appendText("\n\n", no);
  }
  lay.layout(std::numeric_limits<int>::max() / 2, Justification::topLeft, false);
  viewport->getViewedComponent()->setSize(lay.getWidth(), lay.getHeight());
  viewport->setViewPosition(0, 0);
  viewport->repaint();
}

struct FOMUSModsView:public FOMUSDocView
{
  FOMUSModsView() : FOMUSDocView() {}
  void doupdate(const String& sch, const int but);
};

void FOMUSModsView::doupdate(const String& sch, const int but) 
{
  struct info_modsearch s = {0, 0, 0, 0};
  switch (but) {

  case 0: s.name = s.longname = sch.toUTF8(); break;
  case 1: s.doc = sch.toUTF8();
  }
  struct info_modlist lst(info_list_modules(0, &s, 0, 0));
  TextLayout& lay = ((FOMUSViewComponent*)(viewport->getViewedComponent()))->lay;
  lay.clear();
  Font no(13);
  Font ul(13, Font::underlined);
  Font bo(13, Font::bold);
  Font it(13, Font::italic);
  for (struct info_module* i(lst.mods), *ie(lst.mods + lst.n); i < ie; ++i) {
    lay.appendText("name:", ul); lay.appendText(" ", no); lay.appendText(i->name, bo); lay.appendText("  ", no);
    lay.appendText("long name:", ul); lay.appendText(" \"", no); lay.appendText(i->longname, no); lay.appendText("\"  ", no);
    lay.appendText("author:", ul); lay.appendText(" ", no); lay.appendText(i->author, no); lay.appendText("  ", no);
    String ty(modtype_to_str(i->type));
    lay.appendText("type:", ul); lay.appendText(" ", no); lay.appendText(ty, no); lay.appendText("\n", no);
    lay.appendText("directory:", ul); lay.appendText(" ", no); lay.appendText(i->filename, no); lay.appendText("\n", no);

    std::ostringstream ou;
    out_justify(ou, i->doc, 0, false);

    lay.appendText(ou.str().c_str(), it); lay.appendText("\n\n", no);
  }
  lay.layout(std::numeric_limits<int>::max() / 2, Justification::topLeft, false);
  viewport->getViewedComponent()->setSize(lay.getWidth(), lay.getHeight());
  viewport->setViewPosition(0, 0);
  viewport->repaint();
}

class FOMUSDocTabs;
struct MyTabbedComponent:public TabbedComponent
{
  FOMUSDocTabs& tt;
  MyTabbedComponent(FOMUSDocTabs& tt, const TabbedButtonBar::Orientation orientation)
 :TabbedComponent(orientation), tt(tt) {}
  void currentTabChanged(const int newCurrentTabIndex, 
			 const String &newCurrentTabName);
};

class FOMUSDocTabs : public Component,
		     public ButtonListener, 
		     public TextEditorListener,
		     public Timer
{
  int thebut;
public:
  FOMUSDocTabs();
  ~FOMUSDocTabs();
  void resized();
  void buttonClicked (Button* buttonThatWasClicked);
  juce_UseDebuggingNewOperator
  private:
  MyTabbedComponent* Tabs;
  Label* SearchLabel;
  TextEditor* textEditor;
  ToggleButton* SearchName;
  ToggleButton* SearchDoc;
  FOMUSDocTabs(const FOMUSDocTabs&);
  const FOMUSDocTabs& operator=(const FOMUSDocTabs&);
public:
  void updatedocs() {
    FOMUSTabbedComp* x = (FOMUSTabbedComp*)Tabs->getCurrentContentComponent();
    if (x) {
      x->doupdate(textEditor->getText(), thebut);
    }
  }
private:
  void textEditorTextChanged(TextEditor &editor) {
    stopTimer();
    startTimer(500);
  }
  void textEditorReturnKeyPressed (TextEditor &editor) {
    stopTimer();
    updatedocs();
  }
  void textEditorEscapeKeyPressed (TextEditor &editor) {}
  void textEditorFocusLost (TextEditor &editor) {
    stopTimer();
    updatedocs();
  }
  void timerCallback () {
    stopTimer();
    updatedocs();
  }
};

inline void MyTabbedComponent::currentTabChanged(const int newCurrentTabIndex, 
						 const String &newCurrentTabName) 
{
  tt.updatedocs();
}  

FOMUSDocTabs::FOMUSDocTabs() 
 : Component(T("FOMUS Documentation")),
   Tabs(0),
   SearchLabel(0),
   textEditor(0),
   SearchName(0),
   SearchDoc(0),
   thebut(0) 
{
  addAndMakeVisible (textEditor = new TextEditor (T("new text editor")));
  textEditor->setMultiLine (false);
  textEditor->setReturnKeyStartsNewLine (false);
  textEditor->setReadOnly (false);
  textEditor->setScrollbarsShown (false);
  textEditor->setCaretVisible (true);
  textEditor->setPopupMenuEnabled (true);
  textEditor->setText (String::empty);
  
  addAndMakeVisible(Tabs = new MyTabbedComponent (*this, TabbedButtonBar::TabsAtTop));
  Tabs->setTabBarDepth (30);
  Tabs->addTab (T("Settings"), Colours::white, new FOMUSSetsView(/*fom,*/ *textEditor, thebut), true);
  Tabs->addTab (T("Marks"), Colours::white, new FOMUSMarksView(/*fom*/), true);
  Tabs->addTab (T("Modules"), Colours::white, new FOMUSModsView(/*fom*/), true);
  Tabs->setCurrentTabIndex (0);
  textEditor->addListener(this);
  
  addAndMakeVisible (SearchLabel = new Label (T("Search Label"),
					      T("Search:")));
  SearchLabel->setFont (Font (13.0000f, Font::plain));
  SearchLabel->setJustificationType (Justification::centredLeft);
  SearchLabel->setEditable (false, false, false);
  SearchLabel->setColour (TextEditor::textColourId, Colours::black);
  SearchLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (SearchName = new ToggleButton (T("Search Name")));
  SearchName->setButtonText (T("Name"));
  SearchName->setRadioGroupId (1);
  SearchName->addButtonListener (this);
  SearchName->setToggleState (true, false);
  
  addAndMakeVisible (SearchDoc = new ToggleButton (T("Search Doc")));
  SearchDoc->setButtonText (T("Documentation"));
  SearchDoc->setRadioGroupId (1);
  SearchDoc->addButtonListener (this);
  
  setSize (900, 600);
}

FOMUSDocTabs::~FOMUSDocTabs() 
{
  deleteAndZero (Tabs);
  deleteAndZero (SearchLabel);
  deleteAndZero (textEditor);
  deleteAndZero (SearchName);
  deleteAndZero (SearchDoc);
}

void FOMUSDocTabs::resized() 
{
    Tabs->setBounds (0, 0, getWidth() - 0, getHeight() - 39);
    SearchLabel->setBounds (8, getHeight() - 26, 56, 16);
    textEditor->setBounds (56, getHeight() - 31, getWidth() - 194, 21);
    SearchName->setBounds (getWidth() - 130, getHeight() - 26, 48, 16);
    SearchDoc->setBounds (getWidth() - 90, getHeight() - 26, 80, 16);
}

void FOMUSDocTabs::buttonClicked(Button* buttonThatWasClicked) 
{
  if (buttonThatWasClicked == SearchName) {
    thebut = 0;
  } else if (buttonThatWasClicked == SearchDoc) {
    thebut = 1;
  }
  updatedocs();
}

void Fomus::documentationWindow() 
{

  FOMUSDocTabs* t=new FOMUSDocTabs();
  t->setVisible(true);
  FomusDialogWindow* w = new FomusDialogWindow(T("FOMUS Documentation"));
  w->setContentComponent(t, true, true);
  w->setVisible(true);
  w->centreWithSize(t->getWidth(),t->getHeight());
  w->toFront(true);
}

void Fomus::loadScoreDialog() 
{
  WildcardFileFilter wildcardFilter(T("*.fms"), T("FOMUS Input Files"));
  FileBrowserComponent browser(FileBrowserComponent::loadFileMode, 
			       File::nonexistent, &wildcardFilter, 0);
  FileChooserDialogBox dialogBox(T("Load Score"),
				 T("Specify path to `.fms' input file..."),
				 browser, false, Colours::white);
  if (dialogBox.show()) {
    loadScore(browser.getCurrentFile().getFullPathName());
  }
}

void Fomus::renameScoreDialog() 
{
  #warning "todo: wildcards should come from fomus infoapi function"
  WildcardFileFilter wildcardFilter(T("*.fms;*.ly;*.xml"), T("FOMUS Output Files"));
  FileBrowserComponent browser(FileBrowserComponent::saveFileMode, File::nonexistent, &wildcardFilter, 0);
  FileChooserDialogBox dialogBox(T("Rename Score"), T("Specify an output file path (`filename' setting value)..."),
				 browser, false, Colours::white);
  if (dialogBox.show()) {
    File fn = browser.getCurrentFile();
    scores.getUnchecked(current)->name = fn.getFileName();
    sval(fomus_par_setting, fomus_act_set, "filename");
    sval(fomus_par_settingval, fomus_act_set, fn.getFullPathName());
  }
}

#endif

