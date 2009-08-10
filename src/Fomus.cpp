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
#include <vector>
//#include <assert>
#include <iostream>
#include <sstream>
#include <limits>
#include "Console.h"
#include <memory>
#include <stack>
#include "Preferences.h"
#include <cctype>
#include <fomus/infoextapi.h>
#include <fomus/modnotes.h>
#include "CmSupport.h"
#include "Alerts.h"
//#include "TextEditor.h"

juce_ImplementSingleton(FomusSyntax) ;

bool fomuserr = false;

//#warning "get rid of debugging output"

// Notes:
// Make sure this is in the ConsoleWindow class in Console.h:
// TooltipWindow xxx;

// some default output file for people who hate dialogue boxes
#define DEFAULT_OUT "out.ly"

/*=======================================================================*
                             Fomus Instance
 *=======================================================================*/

juce_ImplementSingleton(Fomus);

String getwildcards() {
  String r;
  info_extslist f(info_list_exts());
  bool fi = true;
  String mid("mid");
  for (const char **i(f.exts), **ie(f.exts + f.n); i < ie; ++i) {
    if (*i == mid) continue; // skip midi files
    if (fi) fi = false; else r += ';';
    r += String("*.") + *i;
  }
  return r;
}

struct scopedxml {
  XmlDocument doc;
  std::auto_ptr<XmlElement> prs;
  scopedxml(const String& str):doc(str), prs(doc.getDocumentElement()) {}
  bool isvalid() const {return prs.get();}
  XmlElement* getel() {return prs.get();}
};

struct xmlerror
{
  String str;
  xmlerror(const String& str):str(str) {}
  void printerr() const
  {
    Console::getInstance()->printError(">>> Error: Fomus: " + str + T("\n"));
  }
};

bool Fomus::openScore(String scorename, String scoreargs, const bool fromscm)
{
  // called by sprout to open and/or initialize a (possibly) new score
  // instance for receiving data from processes.  scorename is either
  // "fomus" or "*.{ly|fms|xml}". if its "fomus" maybe the current
  // score instance should be used and if its a file name a new score
  // with that output file and appropriate back end should become
  // current?  scoreargs is a string containing whatever the user
  // passed as to sprout arguments to the score

  scores.getUnchecked(current)->runwhendone = false;
  StringArray userargs;
  //std::cout << '|' << scoreargs.toUTF8() << '|' << std::endl;
  userargs.addTokens(scoreargs, true);
  bool clrsc = false;
  bool newsc = false;
  bool dorun = false;
  //bool xmlerr = false;
  OwnedArray<scopedxml> els;
  fomuserr = false;
  for (int i=0; i<userargs.size(); ++i)
    {
      //std::cout << userargs[i].toUTF8() << std::endl;
      bool istr = true, eatnext = false;
      if (i + 1 < userargs.size()) {
	if (userargs[i + 1] == "#f" || userargs[i + 1] == "#F" || userargs[i + 1] == "nil" || userargs[i + 1] == "NIL") {
	  istr = false;
	  eatnext = true;
	} else if (userargs[i + 1] == "#t" || userargs[i + 1] == "#T" || userargs[i + 1] == "t" || userargs[i + 1] == "T") {
	  eatnext = true;
	}
      }
      if ((userargs[i] == ":run" || userargs[i] == "run:" || userargs[i] == "run" ||
	   userargs[i] == ":RUN" || userargs[i] == "RUN:" || userargs[i] == "RUN") && istr) {
	dorun = true;
      } else if ((userargs[i] == ":clear" || userargs[i] == "clear:" || userargs[i] == "clear" ||
		  userargs[i] == ":CLEAR" || userargs[i] == "CLEAR:" || userargs[i] == "CLEAR") && istr) {
	clrsc = true; //clearScore();
      } else if ((userargs[i] == ":new" || userargs[i] == "new:" || userargs[i] == "new" ||
		  userargs[i] == ":NEW" || userargs[i] == "NEW:" || userargs[i] == "NEW") && istr) {
	newsc = true;
      } else if (userargs[i] == ":err" && istr) {
	return true;
      } else { // try to parse XML
	//std::cout << "Trying to parse |" << userargs[i].toUTF8() << "|" << std::endl;
	scopedxml* x;
	els.add(x = new scopedxml(userargs[i]));
	if (!x) return true;
      }
      if (eatnext) ++i;
    }
  if (scorename != T("fomus")) { // if default score, do nothing
    if (newsc) newScore(scorename, fromscm); else selectScore(scorename, fromscm); // anything else = filename
  }
  if (clrsc) clearScore();
  scores.getUnchecked(current)->runwhendone = dorun;
  for (int i = 0; i < els.size(); ++i) {
    if (els[i]->getel()) {
      try {
	sendXml(*(els[i]->getel()), fomus_par_none, fomus_act_none);
      } catch (const xmlerror& e) {e.printerr();}
    } 
  }
  return false;
}

void Fomus::closeScore()
{
  // called by the scheduler after all processes outputting to the score have stopped.
  // presumably this triggers fomus' score parsing and output handling
  if (scores.getUnchecked(current)->runwhendone) {
    runScore(true);
  }
}

void Fomus::saveScore(const String& fn, const bool fromscm) {
#ifdef GRACE
  if (fn.isEmpty()) {
    if (fromscm) {
      Console::getInstance()->printError((char*)">>> Error: Fomus: no output filename specified\n");
      return;
    }
    //WildcardFileFilter wildcardFilter("*.fms", T("FOMUS Output File"));
    //FileBrowserComponent browser(FileBrowserComponent::saveFileMode, File::nonexistent, &wildcardFilter, 0);
    //FileChooserDialogBox dialogBox(T("Save Score"), T("Specify an output `.fms' file path..."),
    //browser, false, Colours::white);
    FileChooser choose(T("Save Score"), File::getCurrentWorkingDirectory(), "*.fms");
    if (choose.browseForFileToSave(true)) {
      fomus_save(fomus_copy(getfomusdata()), choose.getResult().getFullPathName().toUTF8());
    }
  } else
#endif
    {
      fomus_save(fomus_copy(getfomusdata()), fn.toUTF8());
    }
}

inline void spitout(const char* str) 
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

      // doesn't work      
// #ifdef MACOS
//       CFStringRef key = CFSTR("DialogType");
//       CFStringRef value = CFSTR("Server");
//       CFStringRef appID = CFSTR("com.apple.CrashReporter");
//       CFPreferencesSetAppValue(key, value, appID);
// #endif      
      
    }
}

void Fomus::newScore(const String& nam, const bool fromscm)
{
  FomusScore* score = new FomusScore();
#ifdef GRACE
  if (!fromscm && nam.isEmpty() && scores.size() > 0) {
    //WildcardFileFilter wildcardFilter(getwildcards(), T("FOMUS Output Files"));
    //FileBrowserComponent browser(FileBrowserComponent::saveFileMode, File::nonexistent, &wildcardFilter, 0);
    //FileChooserDialogBox dialogBox(T("New Score"), T("Specify an output file path (`filename' setting value)..."),
    //browser, false, Colours::white);
    FileChooser choose(T("New Score"), File::getCurrentWorkingDirectory(), getwildcards());    
    if (choose.browseForFileToSave(true)) {
      File fn(choose.getResult());
      String fn0(fn.getFileName());
      score->name = (fn0.isEmpty() ? "(untitled)" : fn0);
      scores.add(score);
      current=scores.size()-1;
      sval(fomus_par_setting, fomus_act_set, "filename");
      sval(fomus_par_settingval, fomus_act_set, fn.getFullPathName());
    }
  } else
#endif
    {
      score->name = (nam.isEmpty() ? String("(untitled)") : completeFile(nam).getFileName());
      scores.add(score);
      current=scores.size()-1;
      sval(fomus_par_setting, fomus_act_set, "filename");
      sval(fomus_par_settingval, fomus_act_set, nam);
    }
}

void Fomus::selectScore(const String& nam, const bool fromscm)
{
  File fn(completeFile(nam));
  for (int i = 0; i < scores.size(); ++i) {
    String fn2(fomus_get_sval(scores.getUnchecked(i)->getfom(), "filename"));
    if (!fn2.isEmpty() && completeFile(fn2) == fn) { // find an exact match
      current = i;
      return;
    }
  }
  newScore(nam, fromscm); // selectScore is always from Scheme
}

void Fomus::deleteScore()
{
  // insist on at least one score
  if (scores.size()>1)
    {
      FomusScore* fms=scores.getUnchecked(current);
      scores.removeObject(fms, false);
      current=scores.size()-1;
    }
}

void Fomus::clearScore()
{
  fomus_act(getfomusdata(), fomus_par_events, fomus_act_clear);
}

void Fomus::loadScore(String filename)
{
  fomus_load(getfomusdata(), (char*)filename.toUTF8());
  String fn(fomus_get_sval(getfomusdata(), "filename"));
  scores.getUnchecked(current)->name = (fn.isEmpty() ? String("(untitled)") : completeFile(fn).getFileName());
}

void Fomus::runScore(const bool fromscm)
{
  if (fomuserr) {
    Console::getInstance()->printError((char*)">>> Error: Fomus: run canceled due to input errors\n");
    return;
  }
#ifdef GRACE
  if (String(fomus_get_sval(getfomusdata(), "filename")).isEmpty()) {
    if (!fromscm) renameScoreDialog();
    else {
      String fn0("out.ly");
      File fn(File::getCurrentWorkingDirectory().getFullPathName() + File::separator + fn0);
      scores.getUnchecked(current)->name = fn0;
      sval(fomus_par_setting, fomus_act_set, "filename");
      sval(fomus_par_settingval, fomus_act_set, fn.getFullPathName());  
    }
  }
#else
  String fn0("out.ly");
  File fn(File::getCurrentWorkingDirectory().getFullPathName() + File::separator + fn0);
  scores.getUnchecked(current)->name = fn0;
  sval(fomus_par_setting, fomus_act_set, "filename");
  sval(fomus_par_settingval, fomus_act_set, fn.getFullPathName());  
#endif
  fomus_run(fomus_copy(getfomusdata()));
}


void Fomus::ival(fomus_param par, fomus_action act, fomus_int val)
{
  fomus_ival(getfomusdata(), par, act, val);
  if (fomus_err) fomuserr = true;
}

void Fomus::rval(fomus_param par, fomus_action act, fomus_int num, fomus_int den)
{
  fomus_rval(getfomusdata(), par, act, num, den);
  if (fomus_err) fomuserr = true;
}

void Fomus::mval(fomus_param par, fomus_action act, fomus_int val, fomus_int num, fomus_int den) 
{
  fomus_mval(getfomusdata(), par, act, val, num, den);
  if (fomus_err) fomuserr = true;
}

void Fomus::fval(fomus_param par, fomus_action act, double val)
{
  fomus_fval(getfomusdata(), par, act, val);
  if (fomus_err) fomuserr = true;
}

void Fomus::sval(fomus_param par, fomus_action act, const String& val) 
{
  fomus_sval(getfomusdata(), par, act, (char*)val.toUTF8());
  if (fomus_err) fomuserr = true;
}

void Fomus::act(fomus_param par, fomus_action act) 
{
  fomus_act(getfomusdata(), par, act);
  if (fomus_err) fomuserr = true;
}

struct scoped_timeshift {
  bool isreg;
  Fomus& score;
  scoped_timeshift(double sh, Fomus& score):isreg(sh != 0), score(score) {
    if (isreg) {
      score.fval(fomus_par_region_time, fomus_act_inc, sh);
      score.ival(fomus_par_region, fomus_act_start, 0);
    }
  }
  ~scoped_timeshift() {
    if (isreg) {
      score.ival(fomus_par_region, fomus_act_end, 0);
    }
  }
};

void Fomus::sendXml(const String& xml, double scoretime) 
{
  // if scoretime > 0 then we are being called under a process and the
  // user's xml time value needs to be shifted by that value to
  // determine the true time of the note in the score. if scoretime is
  // 0 then treat the xml time value as the absolute timestamp in the
  // score.

  try {
    //std::cout << xml.toUTF8() << std::endl;
    XmlDocument doc(xml);
    std::auto_ptr<XmlElement> docel(doc.getDocumentElement());
    scoped_timeshift xxx(scoretime, *this);
    sendXml(*docel, fomus_par_none, fomus_act_none);
  } catch (const xmlerror& e) {e.printerr();}
}

inline XmlElement* mustExist(XmlElement* x, const char* what)
{
  if (x) return x;
  throw xmlerror(String("expected ") + what);
}

// can be a struct, list, etc..

void Fomus::sendXmlSets(XmlElement& xml, fomus_param par, fomus_action act, 
			const excmap& exc, bool islist) // if islist = false, look for a "l" tag
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
	  if (!key.isEmpty()) {
	    if (key[0] == ':') {
	      key = key.substring(1);
	    } else if (key[key.length() - 1] == ':') {
	      key = key.substring(0, key.length() - 1);
	    }
	  }
	} else {
	  throw xmlerror("expected string id");
	}
      } else {
	excmap::const_iterator i(exc.find(key));
	if (i == exc.end()) {
	  sval(fomus_par_setting, fomus_act_set, key); // setting
	  sendXmlVal(*e, par, act, wh_none);
	} else { // a "special" slot
	  if (i->second.act != fomus_act_none)
	    sendXmlVal(*e, i->second.par, i->second.act, i->second.wh, i->second.inlist);
	  // special slot--parse XML expecting nested structs
	}
      }
      wh = !wh;
      //}
    }
    if (!wh) throw xmlerror("missing argument");
  } else throw xmlerror("expected list of string id/argument pairs");
}

void Fomus::sendXmlEntry(XmlElement& xml) // notes, rests and marks
{
  sendXmlVal(*mustExist(mustExist(xml.getChildByName(T("time")), "time value")->getChildElement(0), "time value"), fomus_par_time, fomus_act_set, wh_none); // mandatory in scheme functions
  sendXmlVal(*mustExist(mustExist(xml.getChildByName(T("dur")), "duration value")->getChildElement(0), "duration value"), fomus_par_duration, fomus_act_set, wh_none);
  XmlElement* d;
  d = xml.getChildByName(T("part")); if (d) sendXmlVal(*mustExist(d->getChildElement(0), "part id"), fomus_par_part, fomus_act_set, wh_none); //else sval(fomus_par_part, fomus_act_set, lprt);
  d = xml.getChildByName(T("voice")); if (d) {
    sendXmlVal(*mustExist(d->getChildElement(0), "voice number or list"), fomus_par_voice, fomus_act_set, wh_none);
  } else ival(fomus_par_voice, fomus_act_set, 1);
  d = xml.getChildByName(T("grtime")); if (d) sendXmlVal(*mustExist(d->getChildElement(0), "grace time value"), fomus_par_gracetime, fomus_act_set, wh_none);
  d = xml.getChildByName(T("marks")); if (d) {
    XmlElement* l0 = d->getChildByName(T("l"));
    if (!l0) throw xmlerror("expected list of marks");
    //std::cout << '|' << l0->createDocument().toUTF8() << '|' << std::endl;
    forEachXmlChildElement(*l0, l) {
      //std::cout << '|' << e->createDocument().toUTF8() << '|' << std::endl;
      //XmlElement* l = e->getChildByName(T("l"));
      if (l->hasTagName(T("s"))) {
	//XmlElement* s = e->getChildByName(T("s"));
	//if (!s) throw xmlerror("expected mark id or list");
	sendXmlVal(*l, fomus_par_markid, fomus_act_set, wh_none);
      } else if (l->hasTagName(T("l"))) {
	XmlElement* n = l->getChildElement(0);
	if (!n) throw xmlerror("expected mark id");
	sendXmlVal(*n, fomus_par_markid, fomus_act_set, wh_none);
	n = l->getChildElement(1);
	if (n) {
	  sendXmlVal(*n, fomus_par_markval, fomus_act_add, wh_none);
	  n = l->getChildElement(2);
	  if (n) {
	    sendXmlVal(*n, fomus_par_markval, fomus_act_add, wh_none);
	    if (l->getChildElement(3)) throw xmlerror("too many mark arguments");
	  }
	}
      } else throw xmlerror("expected mark id or list");
      act(fomus_par_mark, fomus_act_add);
    }
  }
  d = xml.getChildByName(T("sets")); if (d) sendXmlSets(*d, fomus_par_note_settingval, fomus_act_set);
}

// numbers, strings, lists, etc..
void Fomus::sendXmlVal(XmlElement& xml, fomus_param par, 
		       fomus_action act, whichstruct wh, // wh = what object are we expecting based on context
		       bool doeachinlist) 
{ // if tag, force that tag
  if (xml.hasTagName(T("i"))) {
    ival(par, act, atol(xml.getAllSubText()));
  } else if (xml.hasTagName(T("r"))) {
    rval(par, act, atol(mustExist(xml.getChildByName(T("n")), "numerator")->getAllSubText()),
	 atol(mustExist(xml.getChildByName(T("d")), "denominator")->getAllSubText()));
  } else if (xml.hasTagName(T("f"))) {
    fval(par, act, atof(xml.getAllSubText()));
  } else if (xml.hasTagName(T("s"))) {
    //#warning "switch (wh) ..."
    sval(par, act, xml.getAllSubText());
  } else if (xml.hasTagName(T("l"))) {
    if (wh != wh_none && !doeachinlist) {
      excmap exc;
      switch (wh) {
      case wh_measdef:
	exc.insert(excmap::value_type("id", sendpair(fomus_par_measdef_id,
						     fomus_act_set, wh_none)));
	sendXmlSets(xml, fomus_par_measdef_settingval, fomus_act_set, exc, true);
	Fomus::act(par, act);
	break;
      case wh_part:
	exc.insert(excmap::value_type("id", sendpair(fomus_par_part_id, 
						     fomus_act_set, wh_none)));
	exc.insert(excmap::value_type("inst", sendpair(fomus_par_part_inst,
						       fomus_act_set, wh_inst)));
	sendXmlSets(xml, fomus_par_part_settingval, fomus_act_set, exc, true);
	Fomus::act(par, act);
	break;
      case wh_metapart:
	exc.insert(excmap::value_type("id", sendpair(fomus_par_metapart_id,
						     fomus_act_set, wh_none)));
	exc.insert(excmap::value_type("parts", sendpair(fomus_par_metapart_partmaps,
							fomus_act_add, wh_part,
							true)));
	sendXmlSets(xml, fomus_par_metapart_settingval, fomus_act_set, exc, true);
	Fomus::act(par, act);
	break;
      case wh_inst:
	exc.insert(excmap::value_type("id", sendpair(fomus_par_inst_id, 
						     fomus_act_set, wh_none)));
	exc.insert(excmap::value_type("staves", sendpair(fomus_par_inst_staves,
							 fomus_act_add, wh_staff,
							 true)));
	exc.insert(excmap::value_type("imports", sendpair(fomus_par_inst_imports,
							  fomus_act_add, wh_import,
							  true)));
	exc.insert(excmap::value_type("export", sendpair(fomus_par_inst_export,
							 fomus_act_set, wh_export)));
	exc.insert(excmap::value_type("percinsts", sendpair(fomus_par_inst_percinsts,
							    fomus_act_add,
							    wh_percinst, true)));
	exc.insert(excmap::value_type("template", sendpair(fomus_par_inst_template,
							   fomus_act_set, wh_none)));
	sendXmlSets(xml, fomus_par_inst_settingval, fomus_act_set, exc, true);
	Fomus::act(par, act);
	break;
      case wh_percinst:
	exc.insert(excmap::value_type("id", sendpair(fomus_par_percinst_id,
						     fomus_act_set, wh_none)));
	exc.insert(excmap::value_type("imports", sendpair(fomus_par_percinst_imports,
							  fomus_act_add, wh_import,
							  true)));
	exc.insert(excmap::value_type("export", sendpair(fomus_par_percinst_export,
							 fomus_act_set, wh_export)));
	exc.insert(excmap::value_type("template", sendpair(fomus_par_percinst_template,
							   fomus_act_set, wh_none)));
	sendXmlSets(xml, fomus_par_percinst_settingval, fomus_act_set, exc, true);
	Fomus::act(par, act);
	break;
      case wh_clef:
	sendXmlSets(xml, fomus_par_clef_settingval, fomus_act_set, exc, true);
	Fomus::act(par, act);
	break;
      case wh_staff:
	exc.insert(excmap::value_type("clefs", sendpair(fomus_par_staff_clefs, 
							fomus_act_add, wh_clef,
							true))); // _add? check this!
	sendXmlSets(xml, fomus_par_staff_settingval, fomus_act_set, exc,  true);
	Fomus::act(par, act);
	break;
      case wh_import:
	sendXmlSets(xml, fomus_par_import_settingval, fomus_act_set, exc, true);
	Fomus::act(par, act);
	break;
      case wh_export:
	sendXmlSets(xml, fomus_par_export_settingval, fomus_act_set, exc, true);
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
    String v(xml.getAllSubText());
    if (v == "f" || v == "F" || v == "#f" || v == "false" || v == "nil" || v == "NIL") ival(par, act, 0);
    else if (v == "t" || v == "T" || v == "#t" || v == "true") ival(par, act, 1);
    else throw xmlerror("expected boolean value");
  } else {
    //std::cout << (char*)xml.getTagName().toUTF8() << std::endl;
    throw xmlerror("XML parse error");
  }
}

// Top level stuff
void Fomus::sendXml(XmlElement& xml, fomus_param par, fomus_action act)
{
  //std::cout << std::endl;
  if (xml.hasTagName(T("note"))) {
    sendXmlVal(*mustExist(mustExist(xml.getChildByName(T("pitch")), "pitch value")->getChildElement(0), "pitch value"), fomus_par_pitch, fomus_act_set, wh_none);
    XmlElement* d = xml.getChildByName(T("dyn"));
    if (d) 
      sendXmlVal(*mustExist(d->getChildElement(0), "dynamic value"), fomus_par_dynlevel,
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
    sendXmlVal(*mustExist(mustExist(xml.getChildByName(T("time")), "time value")->getChildElement(0), "time value"), 
	       fomus_par_time, fomus_act_set, wh_none);
    XmlElement* d = xml.getChildByName(T("dur"));
    if (d) sendXmlVal(*mustExist(d->getChildElement(0), "duration value"), fomus_par_duration, fomus_act_set, wh_none);
    d = xml.getChildByName(T("sets")); if (d) {
      d = mustExist(d->getChildByName(T("l")), "settings list");
      if (d->getChildElement(0)) {
	sendXmlVal(*d, fomus_par_meas_measdef, fomus_act_set, wh_measdef);
	//Fomus::act(fomus_par_meas_measdef, fomus_act_set);
      }
    }
    d = xml.getChildByName(T("measdef"));
    if (d) sendXmlVal(*mustExist(d->getChildElement(0), "measure definition id"), fomus_par_meas_measdef, fomus_act_set, wh_none);
    Fomus::act(fomus_par_meas, fomus_act_add);
  } else if (xml.hasTagName(T("measdef"))) {
    sendXmlVal(*mustExist(xml.getChildByName(T("l")), "measure definition"), fomus_par_measdef, 
	       fomus_act_add, wh_measdef);
  } else if (xml.hasTagName(T("part"))) {
    sendXmlVal(*mustExist(xml.getChildByName(T("l")), "part definition"), fomus_par_part,
	       fomus_act_add, wh_part);
  } else if (xml.hasTagName(T("metapart"))) {
    sendXmlVal(*mustExist(xml.getChildByName(T("l")), "metapart definition"), fomus_par_metapart,
	       fomus_act_add, wh_metapart);
//   } else if (xml.hasTagName(T("partsref"))) {
//     sendXmlVal(*mustExist(xml.getChildByName(T("l")), "parts reference definition"), fomus_par_partsref, 
// 	       fomus_act_add, wh_partsref);
  } else if (xml.hasTagName(T("inst"))) {
    sendXmlVal(*mustExist(xml.getChildByName(T("l")), "instrument definition"), fomus_par_inst,
	       fomus_act_add, wh_inst);
  } else if (xml.hasTagName(T("percinst"))) {
    sendXmlVal(*mustExist(xml.getChildByName(T("l")), "percussion instrument definition"), fomus_par_percinst,
	       fomus_act_add, wh_percinst);
  } else if (xml.hasTagName(T("set"))) {
    XmlElement* d = xml.getChildByName(T("app"));
    sendXmlSets(*mustExist(xml.getChildByName(T("l")), "settings list"), fomus_par_settingval, 
		(d ? fomus_act_append : fomus_act_set), excmap(), true);
  } else throw xmlerror("XML parse error");
}

/*=======================================================================*
  Remainder of file is Grace GUI code, not part of the console CM app
 *=======================================================================*/

#ifdef GRACE

class fomusinfo {
protected:
  int num;
  FOMUS fom;
  String id;
  String defstr, chstr;
  bool valid, knvalid, def, kndef;
public:
  fomusinfo(int c, FOMUS fom, const String& id, const String& str):num(c), fom(fom), id(id), defstr(str), chstr(str), valid(true), knvalid(true), kndef(false) {}
  fomusinfo(int c, FOMUS fom, const String& id, const String& defstr, const String& str):num(c), fom(fom), id(id), defstr(defstr), chstr(str),
											 valid(true), knvalid(true), kndef(false) {}
  //virtual ~fomusinfo() {validate();}
  String getid() const {return id;}
  const String& getchangedstr() const {return chstr;}
  bool isdef() {
    if (kndef) return def;
    kndef = true;
    return (def = (chstr == defstr));
  }
  void validate() {
    if (knvalid) return;
    valid = valid_aux();
    knvalid = true;
    if (!valid) Alerts::showMessageBox(AlertWindow::WarningIcon,
					    T("FOMUS Settings"),
					    String("Error in ") << what() << " `" << id << "'.");
  }
  int getnum() const {return num;}
  void reset() {
    chstr = defstr;
    kndef = def = true;
    knvalid = false; // maybe the default isn't valid
  }
  void change(const String& str) { // call this when focus is lost
    chstr = str;
    knvalid = kndef = false;
  }
  void dec() {--num;}
  virtual bool issetting() const {return false;}
  virtual void remove() const {};
protected:
  virtual String what() const = 0;
  virtual bool valid_aux() = 0;
};

// settings
class fomus_set:public fomusinfo {
  //int idnum;
  String descdoc, modname, loc, uselevel, typedoc;
public:
  fomus_set(int c, FOMUS fom, struct info_setting& set, const String& def):fomusinfo(c, fom, set.name, def, set.valstr), /*id(set.id),*/ descdoc(set.descdoc),
									   modname(set.modname), loc(settingloc_to_str(set.loc)), typedoc(set.typedoc) {
    switch (set.uselevel) {
    case 0: uselevel = "beginner"; break;
    case 1: uselevel = "intermediate"; break;
    case 2: uselevel = "advanced"; break;
    case 3: uselevel = "guru";      
    }
  }
  bool issetting() const {return true;}
  const String& getdescdoc() const {return descdoc;}
  const String& getmodname() const {return modname;}
  const String& getloctext() const {return loc;}
  const String& getuselevel() const {return uselevel;}
  const String& gettypedoc() const {return typedoc;}
private:
  bool valid_aux() {
    fomus_parse(fom, (id + " = " + (chstr.isEmpty() ? String("\"\"") : chstr)).toUTF8());
    return !fomus_err;
  }
  String what() const {return T("setting");}
};

inline String rempar(const char* str0) {
  String str(str0);
  if (str.length() >= 2 && (str[0] == '(' || str[0] == '<')) {
    return str.substring(1, str.length() - 1);
  } else return str;
}
class fomus_other:public fomusinfo {
public:
  fomus_other(int c, FOMUS fom, const infoext_objinfo& obj, const char* nam):fomusinfo(c, fom, nam, rempar(obj.valstr)) {}
private:
  bool valid_aux();
  virtual String what0() const = 0;
};
bool fomus_other::valid_aux() {
  //remove();
  fomus_parse(fom, (what0() + ' ' + (chstr.isEmpty() ? String("<>") : (chstr[0] != '(' && chstr[0] != '<' ? (String("<") << chstr << '>') : chstr))).toUTF8());
  if (fomus_err) return false;
  struct infoext_objinfo x(infoext_getlastentry(fom));
  id = module_id(x.obj);
  return true;
}

class fomus_part:public fomus_other {
public:
  fomus_part(int c, FOMUS fom, const infoext_objinfo& obj, const char* nam):fomus_other(c, fom, obj, nam) {}
  String what() const {return T("part");}
  String what0() const {return T("part");}
  void remove() const {fomus_sval(fom, fomus_par_part, fomus_act_remove, id.toUTF8());}
};
class fomus_metapart:public fomus_other {
public:
  fomus_metapart(int c, FOMUS fom, const infoext_objinfo& obj, const char* nam):fomus_other(c, fom, obj, nam) {}
  String what() const {return T("metapart");}
  String what0() const {return T("metapart");}
  void remove() const {fomus_sval(fom, fomus_par_metapart, fomus_act_remove, id.toUTF8());}
};
class fomus_measdef:public fomus_other {
public:
  fomus_measdef(int c, FOMUS fom, const infoext_objinfo& obj, const char* nam):fomus_other(c, fom, obj, nam) {}
  String what() const {return T("measure definition");}  
  String what0() const {return T("measdef");}
  void remove() const {fomus_sval(fom, fomus_par_measdef, fomus_act_remove, id.toUTF8());}
};
class fomus_inst:public fomus_other {
public:
  fomus_inst(int c, FOMUS fom, const infoext_objinfo& obj, const char* nam):fomus_other(c, fom, obj, nam) {}
  String what() const {return T("instrument");}  
  String what0() const {return T("inst");}
  void remove() const {fomus_sval(fom, fomus_par_inst, fomus_act_remove, id.toUTF8());}
};
class fomus_percinst:public fomus_other {
public:
  fomus_percinst(int c, FOMUS fom, const infoext_objinfo& obj, const char* nam):fomus_other(c, fom, obj, nam) {}
  String what() const {return T("percussion instrument");}  
  String what0() const {return T("percinst");}
  void remove() const {fomus_sval(fom, fomus_par_percinst, fomus_act_remove, id.toUTF8());}
};

// ------------------------------------------------------------------------------------------------------------------------

class fomusinfocont {
protected:
  FOMUS fom;
  int uselevel;
  std::vector<fomusinfo*> stuff;
public:
  fomusinfocont(FOMUS fom, int uselevel):fom(fom), uselevel(uselevel) {}
  ~fomusinfocont() {
    for (std::vector<fomusinfo*>::iterator i(stuff.begin()); i != stuff.end(); ++i) {(*i)->validate(); delete *i;}
  }
  void clearvect() {
    for (std::vector<fomusinfo*>::iterator i(stuff.begin()); i != stuff.end(); ++i) {(*i)->validate(); delete *i;}
    stuff.clear();
  }
  void reset() {
    clearvect();
    reset_aux();
  }
  void init() {reset_aux();}
  int getn() const {return stuff.size();}
  fomusinfo* get(int ind) const {return stuff[ind];}
  int getuselevel() const {return uselevel;}
  void setuselevel(int lvl) {
    uselevel = lvl;
    reset();
  }
  virtual bool issetting() const {return false;}
  virtual fomusinfo* createnew(const String& txt) {};
  void remove(int num) {
    stuff[num]->remove();
    for (std::vector<fomusinfo*>::iterator i(stuff.begin() + num); i != stuff.end(); ++i) (*i)->dec();
    stuff.erase(stuff.begin() + num);
  }
private:
  virtual void reset_aux() = 0;
};

class fomusinfocont_sets:public fomusinfocont {
  std::vector<String> defs;
public:
  fomusinfocont_sets(FOMUS fom, int uselevel);
  bool issetting() const {return true;}
private:
  void reset_aux();
};

fomusinfocont_sets::fomusinfocont_sets(FOMUS fom, int uselevel):fomusinfocont(fom, uselevel) {
  struct info_setfilter se = {0, 0, 0, module_nomodtype, 0, module_noloc, 3, info_none}; 
  struct info_setfilterlist fi = {1, &se};
  info_setlist sets(info_list_settings(0, &fi, 0, 0, -1)); // config defaults
  int c = 0;
  defs.resize(sets.n);
  for (info_setting* s(sets.sets), *se(sets.sets + sets.n); s < se; ++s) {
    if (s->id < sets.n) defs[s->id] = s->valstr;
  }
}

void fomusinfocont_sets::reset_aux() {
  struct info_setfilter se = {0, 0, 0, module_nomodtype, 0, module_noloc, uselevel, info_none}; 
  struct info_setfilterlist fi = {1, &se};
  info_setlist sets(info_list_settings(fom, &fi, 0, 0, -1));
  int c = 0;
  for (info_setting* s(sets.sets), *se(sets.sets + sets.n); s < se; ++s) stuff.push_back(new fomus_set(c++, fom, *s, defs[s->id]));
}

class fomusinfocont_other:public fomusinfocont {
public:
  fomusinfocont_other(FOMUS fom):fomusinfocont(fom, 0) {}
private:
  void reset_aux();
  virtual infoext_objinfo_list getem() const = 0;
  virtual fomusinfo* getnew(int c, FOMUS fom, const infoext_objinfo& obj, const char* nam) = 0;
};
void fomusinfocont_other::reset_aux() {
  infoext_objinfo_list li(getem());
  int c = 0;
  for (infoext_objinfo *i(li.objs), *ie(li.objs + li.n); i < ie; ++i) {
    const char* nam = module_id(i->obj);
    if (nam[0] /*&& !String(nam).equalsIgnoreCase("default")*/) stuff.push_back(getnew(c++, fom, *i, nam));
  }
}

class fomusinfocont_parts:public fomusinfocont_other {
public:
  fomusinfocont_parts(FOMUS fom):fomusinfocont_other(fom) {}
private:
  infoext_objinfo_list getem() const {return infoext_list_parts(fom);}
  fomusinfo* getnew(int c, FOMUS fom, const infoext_objinfo& obj, const char* nam) {return new fomus_part(c, fom, obj, nam);}
  fomusinfo* createnew(const String& txt);
};
fomusinfo* fomusinfocont_parts::createnew(const String& txt) {
  fomus_parse(fom, ("part " + (txt.isEmpty() ? String("<>") : (txt[0] != '(' && txt[0] != '<' ? (String("<") << txt << '>') : txt))).toUTF8());
  if (fomus_err) {
    Alerts::showMessageBox(AlertWindow::WarningIcon,
				T("FOMUS Settings"),
				T("Error in part"));
    return 0;
  } else {
    struct infoext_objinfo x(infoext_getlastentry(fom));
    fomus_part* y;
    stuff.push_back(y = new fomus_part(stuff.size(), fom, x, module_id(x.obj)));
    return y;
  }
}

class fomusinfocont_metaparts:public fomusinfocont_other {
public:
  fomusinfocont_metaparts(FOMUS fom):fomusinfocont_other(fom) {}
private:
  infoext_objinfo_list getem() const {return infoext_list_metaparts(fom);}
  fomusinfo* getnew(int c, FOMUS fom, const infoext_objinfo& obj, const char* nam) {return new fomus_metapart(c, fom, obj, nam);}
  fomusinfo* createnew(const String& txt);
};
fomusinfo* fomusinfocont_metaparts::createnew(const String& txt) {
  fomus_parse(fom, ("metapart " + (txt.isEmpty() ? String("<>") : (txt[0] != '(' && txt[0] != '<' ? (String("<") << txt << '>') : txt))).toUTF8());
  if (fomus_err) {
    Alerts::showMessageBox(AlertWindow::WarningIcon,
				T("FOMUS Settings"),
				T("Error in metapart"));
    return 0;
  } else {
    struct infoext_objinfo x(infoext_getlastentry(fom));
    fomus_metapart* y;
    stuff.push_back(y = new fomus_metapart(stuff.size(), fom, x, module_id(x.obj)));
    return y;
  }
}

class fomusinfocont_measdefs:public fomusinfocont_other {
public:
  fomusinfocont_measdefs(FOMUS fom):fomusinfocont_other(fom) {}
private:
  infoext_objinfo_list getem() const {return infoext_list_measdefs(fom);}
  fomusinfo* getnew(int c, FOMUS fom, const infoext_objinfo& obj, const char* nam) {return new fomus_measdef(c, fom, obj, nam);}
  fomusinfo* createnew(const String& txt);
};
fomusinfo* fomusinfocont_measdefs::createnew(const String& txt) {
  fomus_parse(fom, ("measdef " + (txt.isEmpty() ? String("<>") : (txt[0] != '(' && txt[0] != '<' ? (String("<") << txt << '>') : txt))).toUTF8());
  if (fomus_err) {
    Alerts::showMessageBox(AlertWindow::WarningIcon,
				T("FOMUS Settings"),
				T("Error in measure definition"));
    return 0;
  } else {
    struct infoext_objinfo x(infoext_getlastentry(fom));
    fomus_measdef *y;
    stuff.push_back(y = new fomus_measdef(stuff.size(), fom, x, module_id(x.obj)));
    return y;
  }
}

class fomusinfocont_insts:public fomusinfocont_other {
public:
  fomusinfocont_insts(FOMUS fom):fomusinfocont_other(fom) {}
private:
  infoext_objinfo_list getem() const {return infoext_list_insts(fom);}
  fomusinfo* getnew(int c, FOMUS fom, const infoext_objinfo& obj, const char* nam) {return new fomus_inst(c, fom, obj, nam);}
  fomusinfo* createnew(const String& txt);
};
fomusinfo* fomusinfocont_insts::createnew(const String& txt) {
  fomus_parse(fom, ("inst " + (txt.isEmpty() ? String("<>") : (txt[0] != '(' && txt[0] != '<' ? (String("<") << txt << '>') : txt))).toUTF8());
  if (fomus_err) {
    Alerts::showMessageBox(AlertWindow::WarningIcon,
				T("FOMUS Settings"),
				T("Error in instrument"));
    return 0;
  } else {
    struct infoext_objinfo x(infoext_getlastentry(fom));
    fomus_inst *y;
    stuff.push_back(y = new fomus_inst(stuff.size(), fom, x, module_id(x.obj)));
    return y;
  }
}

class fomusinfocont_percinsts:public fomusinfocont_other {
public:
  fomusinfocont_percinsts(FOMUS fom):fomusinfocont_other(fom) {}
private:
  infoext_objinfo_list getem() const {return infoext_list_percinsts(fom);}
  fomusinfo* getnew(int c, FOMUS fom, const infoext_objinfo& obj, const char* nam) {return new fomus_percinst(c, fom, obj, nam);}
  fomusinfo* createnew(const String& txt);
};
fomusinfo* fomusinfocont_percinsts::createnew(const String& txt) {
  fomus_parse(fom, ("percinst " + (txt.isEmpty() ? String("<>") : (txt[0] != '(' && txt[0] != '<' ? (String("<") << txt << '>') : txt))).toUTF8());
  if (fomus_err) {
    Alerts::showMessageBox(AlertWindow::WarningIcon,
				T("FOMUS Settings"),
				T("Error in percussion instrument"));
    return 0;
  } else {
    struct infoext_objinfo x(infoext_getlastentry(fom));
    fomus_percinst *y;
    stuff.push_back(y = new fomus_percinst(stuff.size(), fom, x, module_id(x.obj)));
    return y;
  }
}

/*=======================================================================*
  Windows
 *=======================================================================*/

class FOMUSListBoxModel;
class FOMUSSettingsListBoxItem;
class FOMUSSettingsEditor:public TextEditor {
public:
  FOMUSListBoxModel& boxmodel;
  fomusinfo* inf;
  FOMUSSettingsEditor(fomusinfo* inf, FOMUSListBoxModel& boxmodel, FOMUSSettingsListBoxItem& lb, const String &componentName = String::empty,
		      const tchar passwordCharacter = 0):TextEditor(componentName, passwordCharacter), inf(inf), boxmodel(boxmodel), lb(lb), dirty(false) {}
  juce_UseDebuggingNewOperator
  private:
  FOMUSSettingsEditor(const FOMUSSettingsEditor&);
  const FOMUSSettingsEditor& operator= (const FOMUSSettingsEditor&);
  bool dirty;
  FOMUSSettingsListBoxItem& lb;
  public:
  void focusLost(FocusChangeType cause) {
    validate();
    TextEditor::focusLost(cause);
  }
  void validate();
  void reset() {
    if (inf) {
      inf->reset();
      setText(inf->getchangedstr(), false);
    } else setText(T("id ..."), false);
    dirty = false;
  }
  void setinfo(fomusinfo* inf0) {
    inf = inf0;
    dirty = false;
  }
  bool isdef() const {return inf ? (bool)inf->isdef() : getText().isEmpty();}
  String getchangedstr() {return inf ? inf->getchangedstr() : String();}
  int getnum() const {return inf ? inf->getnum() : -1;}
  void setdirty() {dirty = true;}
};

// SETTINGS LISTBOX ITEM

class FOMUSSettingsListBox;
class FOMUSSettingsListBoxItem:public Component, public ButtonListener, public TextEditorListener {
  FOMUSListBoxModel& boxmodel;
public:
  FOMUSSettingsListBoxItem(fomusinfo* inf, FOMUSListBoxModel& boxmodel);
  ~FOMUSSettingsListBoxItem();

  void resized();
  void buttonClicked(Button* buttonThatWasClicked);

  void updateset(fomusinfo* set);
  
  void textEditorTextChanged(TextEditor&) {defoff(); ValueText->setdirty();}
  void textEditorReturnKeyPressed(TextEditor&) {
    //defoff();
    ValueText->validate();
  }
  void textEditorEscapeKeyPressed(TextEditor&) {defon();}
  void textEditorFocusLost(TextEditor&) {}

  juce_UseDebuggingNewOperator

  //int getid() const {return ValueText->getid();}
  String getstoretext() const {return ValueText->getText();}
  bool getstoredef() const {return DefaultButton ? DefaultButton->getToggleState() : false;}
  
  void validate() {ValueText->validate();}
  int getnum() {ValueText->getnum();}

  void setname(const String& str) {NameText->setText(str, false);}
private:
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
  TextButton* DelButton;
  FOMUSSettingsEditor* ValueText;

  FOMUSSettingsListBox* parent;
  
  FOMUSSettingsListBoxItem(const FOMUSSettingsListBoxItem&);
  const FOMUSSettingsListBoxItem& operator= (const FOMUSSettingsListBoxItem&);

  void defoff() {
    if (DefaultButton) DefaultButton->setToggleState(false, false); 
    //ValueText->change = true;
  }

  void defon() {
    //std::cout << "RESETTING TO DEFAULT" << std::endl;
    ValueText->reset();
    ValueText->setText(ValueText->getchangedstr(), false);
    if (DefaultButton) DefaultButton->setToggleState(ValueText->isdef(), false);
  }
};

void FOMUSSettingsListBoxItem::updateset(fomusinfo* set) {
  ValueText->setinfo(set);
  if (set) {
    NameText->setText(set->getid(), false);
    if (set->issetting()) {
      NameText->setTooltip(((fomus_set*)set)->getdescdoc());
      ModuleText->setText(((fomus_set*)set)->getmodname(), false);
      LocationText->setText(((fomus_set*)set)->getloctext(), false);
      UseLevelText->setText(((fomus_set*)set)->getuselevel(), false);
      TypeText->setText(((fomus_set*)set)->gettypedoc(), false);
    }
    ValueText->setText(set->getchangedstr(), false);
    if (DefaultButton) DefaultButton->setToggleState(set->isdef(), false);
  } else ValueText->setText(T("id ..."));
}

FOMUSSettingsListBoxItem::FOMUSSettingsListBoxItem(fomusinfo* inf, FOMUSListBoxModel& boxmodel):Component(T("FOMUS Settings ListBox Item")),
												boxmodel(boxmodel),
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
												ValueText (0) ,
												DelButton(0)
{
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

  if (inf && inf->issetting()) {
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
    
    addAndMakeVisible (DefaultButton = new ToggleButton (T("Default Button")));
    DefaultButton->setButtonText (T("Default"));
    DefaultButton->addButtonListener (this);
    //DefaultButton->setToggleState (true, false);
  } else {
    addAndMakeVisible (DelButton = new TextButton (T("Delete Button")));
    DelButton->setButtonText (T("Remove"));
    DelButton->addButtonListener (this);    
  }
  
  addAndMakeVisible (ValueLabel = new Label (T("Value Label"),
					     T("Value:")));
  ValueLabel->setFont (Font (13.0000f, Font::plain));
  ValueLabel->setJustificationType (Justification::centredLeft);
  ValueLabel->setEditable (false, false, false);
  ValueLabel->setColour (TextEditor::textColourId, Colours::black);
  ValueLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
  
  addAndMakeVisible (ValueText = new FOMUSSettingsEditor(inf, boxmodel, *this, T("Value Text")));
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
  
  updateset(inf);
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
  deleteAndZero (DelButton);
}

void FOMUSSettingsListBoxItem::resized() 
{
  NameLabel->setBounds (8 + 0, 8 + 0, 48, 16);
  NameText->setBounds (8 + 40, 8 + 0, 184, 16);
  if (ModuleLabel) ModuleLabel->setBounds (8 + 232, 8 + 0, 56, 16);
  if (ModuleText) ModuleText->setBounds (8 + 280, 8 + 0, 83, 16);
  if (LocationLabel) LocationLabel->setBounds (8 + 368, 8 + 0, 56, 16);
  if (LocationText) LocationText->setBounds (8 + 424, 8 + 0, 75, 16);
  if (UseLevelLabel) UseLevelLabel->setBounds (8 + 504, 8 + 0, 56, 16);
  if (UseLevelText) UseLevelText->setBounds (8 + 560, 8 + 0, 75, 16);
  if (TypeLabel) TypeLabel->setBounds (8 + 0, 8 + 16, 40, 16);
  if (TypeText) TypeText->setBounds (8 + 40, 8 + 16, getWidth() - 148, 16);
  if (DefaultButton) DefaultButton->setBounds (8 + getWidth() - 100, 8 + 16, 48, 16);
  if (DelButton) {
    ValueLabel->setBounds (8 + 0, 8 + 32 - 14, 40, 16);
    ValueText->setBounds (8 + 40, 8 + 32 - 14, getWidth() - 80, 40 + 14);
    DelButton->setBounds(8 + getWidth() - 90, 8 + 16 - 16, 40, 14);
  } else {
    ValueLabel->setBounds (8 + 0, 8 + 32, 40, 16);
    ValueText->setBounds (8 + 40, 8 + 32, getWidth() - 80, 40);
  }
}

// LIST BOX MODEL

class FOMUSSettingsListBox;
class FOMUSListBoxModel:public ListBoxModel {
private:
  FOMUSSettingsListBox* textlistener;
  fomusinfocont& infos;
  bool hasnew;
public:
  FOMUSListBoxModel(fomusinfocont& infos, FOMUSSettingsListBox* textlistener):ListBoxModel(), textlistener(textlistener), infos(infos), hasnew(false) {}
  int getNumRows() {return hasnew ? infos.getn() + 1 : infos.getn();}
  void paintListBoxItem(int rowNumber, Graphics &g, int width, int height, bool rowIsSelected) {}
  Component* refreshComponentForRow(int rowNumber, bool isRowSelected, Component *existingComponentToUpdate);
  void sethasnew();
  String createnew(const String& txt, fomusinfo* &inf);
  void deleteone(int id);
};

void FOMUSSettingsEditor::validate() {
  if (inf) {
    if (dirty) inf->change(getText().toUTF8());
    inf->validate();
    lb.setname(inf->getid());
  } else lb.setname(boxmodel.createnew(getText(), inf));
  dirty = false;
}

// SETTINGS LISTBOX

class FOMUSSettingsListBox:public ListBox {
  fomusinfocont& infos;
public:
  FOMUSSettingsListBox(fomusinfocont& infos):ListBox(T("FOMUS ListBox"), new FOMUSListBoxModel(infos, this)), infos(infos) {setRowHeight(16 + 72);}
  ~FOMUSSettingsListBox() {delete getModel();}

  juce_UseDebuggingNewOperator

  void addnew() {((FOMUSListBoxModel*)getModel())->sethasnew();}
private:
  FOMUSSettingsListBox (const FOMUSSettingsListBox&);
  const FOMUSSettingsListBox& operator= (const FOMUSSettingsListBox&);
};

inline void FOMUSListBoxModel::sethasnew() {
  hasnew = true;
  textlistener->updateContent();
}
String FOMUSListBoxModel::createnew(const String& txt, fomusinfo* &inf) {
  inf = infos.createnew(txt);
  if (inf) { // success!
    hasnew = false; // inf is now at the end of the list in infos
    textlistener->updateContent();
    return inf->getid();
  }
  return T("");
}
void FOMUSListBoxModel::deleteone(int id) {
  if (id < 0) {
    hasnew = false;
  } else {
    infos.remove(id);
  }
  textlistener->updateContent();
}

void FOMUSSettingsListBoxItem::buttonClicked(Button* buttonThatWasClicked) {
  if (buttonThatWasClicked == DefaultButton) {
    if (DefaultButton->getToggleState()) defon();
  } else if (buttonThatWasClicked == DelButton) {
    boxmodel.deleteone(ValueText->getnum());
  }
}

Component* FOMUSListBoxModel::refreshComponentForRow(int rowNumber, bool isRowSelected, Component *existingComponentToUpdate) {
  if (hasnew && rowNumber == getNumRows() - 1) {
    return new FOMUSSettingsListBoxItem(0, *this);
  }
  if (rowNumber >= getNumRows()) { // out of range, delete it
    if (existingComponentToUpdate) {
      ((FOMUSSettingsListBoxItem*)existingComponentToUpdate)->validate();
      if (((FOMUSSettingsListBoxItem*)existingComponentToUpdate)->hasKeyboardFocus(true)) textlistener->grabKeyboardFocus();
      delete existingComponentToUpdate;
    }
    return 0;
  }
  if (existingComponentToUpdate) {
    if (((FOMUSSettingsListBoxItem*)existingComponentToUpdate)->getnum() != rowNumber) { // switching to different row
      ((FOMUSSettingsListBoxItem*)existingComponentToUpdate)->validate();
      if (((FOMUSSettingsListBoxItem*)existingComponentToUpdate)->hasKeyboardFocus(true)) textlistener->grabKeyboardFocus();
      ((FOMUSSettingsListBoxItem*)existingComponentToUpdate)->updateset(infos.get(rowNumber));
    } // otherwise it's the same one, reuse it
    return existingComponentToUpdate;
  } else { // completely new one
    return new FOMUSSettingsListBoxItem(infos.get(rowNumber), *this);
  }
}

// SETTINGS COMPONENT
class FOMUSSettings:public Component, public ButtonListener {
  fomusinfocont& infos;
public:
  FOMUSSettings (fomusinfocont& infos);
  ~FOMUSSettings();
  void resized();
  void buttonClicked (Button* buttonThatWasClicked);
  juce_UseDebuggingNewOperator
  private:
  void switchtouse(int lvl) {
    if (lvl != infos.getuselevel()) {
      removeChildComponent (component);
      delete component;
      infos.setuselevel(lvl);
      addAndMakeVisible (component = new FOMUSSettingsListBox(infos));
      component->setBounds (0, 16, getWidth(), getHeight() - 16);
    }
  }
  FOMUSSettingsListBox* component;
  ToggleButton* BeginnerButton;
  ToggleButton* IntermediateButton;
  ToggleButton* AdvancedButton;
  ToggleButton* GuruButton;
  TextButton* AddButton;
  TextButton* RefreshButton;
  FOMUSSettings (const FOMUSSettings&);
  const FOMUSSettings& operator= (const FOMUSSettings&);
};

FOMUSSettings::FOMUSSettings(fomusinfocont& infos)
  :Component(T("FOMUSSettings") ),
   infos(infos), 
   component (0),
   BeginnerButton (0),
   IntermediateButton (0),
   AdvancedButton (0),
   GuruButton (0),
   AddButton (0),
   RefreshButton (0)
{
  addAndMakeVisible (component = new FOMUSSettingsListBox (infos));
  if (infos.issetting()) {
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
  } else {
    addAndMakeVisible (AddButton = new TextButton (T("New Button")));
    AddButton->setButtonText (T("New"));
    AddButton->addButtonListener (this);    
    addAndMakeVisible (RefreshButton = new TextButton (T("Refresh Button")));
    RefreshButton->setButtonText (T("Refresh"));
    RefreshButton->addButtonListener (this);    
  }
  //setSize (640 + 32, 400);
}

FOMUSSettings::~FOMUSSettings() {
  deleteAndZero (component);
  deleteAndZero (BeginnerButton);
  deleteAndZero (IntermediateButton);
  deleteAndZero (AdvancedButton);
  deleteAndZero (GuruButton);
  deleteAndZero (AddButton);
  deleteAndZero (RefreshButton);
}

void FOMUSSettings::resized() {
  if (infos.issetting()) {
    component->setBounds (0, 16, getWidth(), getHeight() - 16);
    BeginnerButton->setBounds (0, 0, 56, 16);
    IntermediateButton->setBounds (56, 0, 72, 16);
    AdvancedButton->setBounds (128, 0, 64, 16);
    GuruButton->setBounds (184, 0, 56, 16);
  } else {
    component->setBounds (0, 0, getWidth(), getHeight() - 18);
    AddButton->setBounds(8, getHeight() - 16, 40, 14);
    RefreshButton->setBounds(60, getHeight() - 16, 40, 14);
  }
}

void FOMUSSettings::buttonClicked (Button* buttonThatWasClicked) {
  if (buttonThatWasClicked == BeginnerButton) {
    switchtouse(0);
  } else if (buttonThatWasClicked == IntermediateButton) {
    switchtouse(1);
  } else if (buttonThatWasClicked == AdvancedButton) {
    switchtouse(2);
  } else if (buttonThatWasClicked == GuruButton) {
    switchtouse(3);
  } else if (buttonThatWasClicked == AddButton) {
    component->addnew();
  } else if (buttonThatWasClicked == RefreshButton) {
    deleteAndZero(component);
    infos.reset();
    addAndMakeVisible (component = new FOMUSSettingsListBox (infos));
    component->setBounds (0, 0, getWidth(), getHeight() - 18);
  }
}

struct FileTabs:public TabbedComponent {
  fomusinfocont_sets sets;
  fomusinfocont_parts parts;
  fomusinfocont_metaparts metaparts;
  //fomusinfocont_measdefs measdefs;
  fomusinfocont_insts insts;
  fomusinfocont_percinsts percinsts;
  
  FileTabs(FOMUS fom ):TabbedComponent(TabbedButtonBar::TabsAtTop), sets(fom, 0), parts(fom), metaparts(fom), /*measdefs(fom),*/ insts(fom), percinsts(fom) {
    sets.init();
    parts.init();
    metaparts.init();
    //measdefs.init();
    insts.init();
    percinsts.init();
    addTab(T("Settings"), Colours::white, new FOMUSSettings(sets), true);
    addTab(T("Parts"), Colours::white, new FOMUSSettings(parts), true);
    addTab(T("Metaparts"), Colours::white, new FOMUSSettings(metaparts), true);
    //addTab(T("Measure Definitions"), Colours::white, new FOMUSSettings(measdefs), true);
    addTab(T("Instruments"), Colours::white, new FOMUSSettings(insts), true);
    addTab(T("Percussion Instruments"), Colours::white, new FOMUSSettings(percinsts), true);

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
  String fn(fomus_get_sval(getfomusdata(), "filename"));
  scores.getUnchecked(current)->name = (fn.isEmpty() ? "(untitled)" : completeFile(fn).getFileName());
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
    lay.appendText("arguments:", ul); lay.appendText(" ", no); lay.appendText(i->argsdoc, no); lay.appendText("\n", no);
    std::ostringstream ou;
    out_justify(ou, i->descdoc, 0, false);
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
  SearchDoc->setButtonText (T("Doc Text"));
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
  //WildcardFileFilter wildcardFilter(T("*.fms"), T("FOMUS Input Files"));
  //FileBrowserComponent browser(FileBrowserComponent::loadFileMode, 
  //File::nonexistent, &wildcardFilter, 0);
  //FileChooserDialogBox dialogBox(T("Load Score"),
  //T("Specify path to `.fms' input file..."),
  //browser, false, Colours::white);
  FileChooser choose(T("Load Score"), File::getCurrentWorkingDirectory(), "*.fms");  
  if (choose.browseForFileToOpen()) {
    loadScore(choose.getResult().getFullPathName());
  }
}

void Fomus::renameScoreDialog() 
{
  //WildcardFileFilter wildcardFilter(getwildcards(), T("FOMUS Output Files"));
  //FileBrowserComponent browser(FileBrowserComponent::saveFileMode, File::nonexistent, &wildcardFilter, 0);
  //FileChooserDialogBox dialogBox(T("Rename Score"), T("Specify an output file path (`filename' setting value)..."),
  //browser, false, Colours::white);
  FileChooser choose(T("Rename Score"), File::getCurrentWorkingDirectory(), getwildcards());
  if (choose.browseForFileToSave(true)) {
    File fn(choose.getResult());
    String fn0(fn.getFileName());
    scores.getUnchecked(current)->name = (fn0.isEmpty() ? "(untitled)" : fn0);
    sval(fomus_par_setting, fomus_act_set, "filename");
    sval(fomus_par_settingval, fomus_act_set, fn.getFullPathName());
  }
}

// ------------------------------------------------------------------------------------------------------------------------
// EDITOR
// ------------------------------------------------------------------------------------------------------------------------

void FomusSyntax::stickkeyword(String str, const int hl) {
  tokens.insert(SynTokMap::value_type(str, new SynTok(str, 0, hl)));
  str[0] = toupper(str[0]);
  tokens.insert(SynTokMap::value_type(str, new SynTok(str, 0, hl)));
  for (int i = 1; i < str.length(); ++i) str[i] = toupper(str[i]);
  tokens.insert(SynTokMap::value_type(str, new SynTok(str, 0, hl)));
}

FomusSyntax::FomusSyntax () // syntab
  :Syntax(T(" "), // whitechars
	  T("" /*"qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890"*/), // wordchars 
	  T("~!@#$%^&*-_?/'\"\\[]"), // symbolchars
	  T(""), // commentchars
	  T(""), // prefixchars
	  T("" /*"\"'"*/), // stringchars
	  T("" /*"(<{["*/), // openchars
	  T("" /*")>}]"*/), // closechars
	  T("" /*",.!?;:'`\\"*/), // punctchars
	  T("" /*"\\"*/)) // escapechars
{
  coloring = true;
  type=TextIDs::Fomus;
#ifdef GRACE
  tabwidth=Preferences::getInstance()->getIntProp(T("FomusTabWidth"), 2);
#else
  tabwidth=2;
#endif
  hilites[HiliteIDs::String]=Colours::darkgreen;
  hilites[HiliteIDs::Comment]=Colours::darkcyan;
  hilites[HiliteIDs::Hilite4]=Colours::darkorange; // settings
  hilites[HiliteIDs::Hilite5]=Colours::darkred; // built-in
  
  hilites[HiliteIDs::Hilite6]=Colours::darkgreen;
  hilites[HiliteIDs::Hilite7]=Colours::darkblue; 
  hilites[HiliteIDs::Hilite8]=Colours::darkmagenta;
//   hilites[HiliteIDs::Hilite9]=Colours::darkseagreen; // dyn
//   hilites[HiliteIDs::Hilite10]=Colours::darkkhaki; // duration
//   hilites[HiliteIDs::Hilite11]=Colours::darkmagenta; // part
//   hilites[HiliteIDs::Hilite12]=Colours::darkolivegreen; // pitch
//   hilites[HiliteIDs::Hilite13]=Colours::darkgrey; // note/mark/rest
//   hilites[HiliteIDs::Hilite14]=Colours::black; // meas
//   hilites[HiliteIDs::Hilite15]=Colours::darkslateblue; // meas
  // keywords
  stickkeyword(T("voice"), HiliteIDs::Hilite7);
  stickkeyword(T("voi"), HiliteIDs::Hilite7);
  stickkeyword(T("vo"), HiliteIDs::Hilite7);
  stickkeyword(T("v"), HiliteIDs::Hilite7);
  stickkeyword(T("time"), HiliteIDs::Hilite6);
  stickkeyword(T("tim"), HiliteIDs::Hilite6);
  stickkeyword(T("ti"), HiliteIDs::Hilite6);
  stickkeyword(T("t"), HiliteIDs::Hilite6);
  stickkeyword(T("grace"), HiliteIDs::Hilite6);
  stickkeyword(T("gra"), HiliteIDs::Hilite6);
  stickkeyword(T("gr"), HiliteIDs::Hilite6);
  stickkeyword(T("g"), HiliteIDs::Hilite6);
  stickkeyword(T("dynamic"), HiliteIDs::Hilite7);
  stickkeyword(T("dyn"), HiliteIDs::Hilite7);
  stickkeyword(T("dy"), HiliteIDs::Hilite7);
  stickkeyword(T("y"), HiliteIDs::Hilite7);
  stickkeyword(T("duration"), HiliteIDs::Hilite6);
  stickkeyword(T("dur"), HiliteIDs::Hilite6);
  stickkeyword(T("du"), HiliteIDs::Hilite6);
  stickkeyword(T("d"), HiliteIDs::Hilite6);
  stickkeyword(T("part"), HiliteIDs::Hilite5);
  stickkeyword(T("par"), HiliteIDs::Hilite5);
  stickkeyword(T("pa"), HiliteIDs::Hilite5);
  stickkeyword(T("a"), HiliteIDs::Hilite5);
  stickkeyword(T("pitch"), HiliteIDs::Hilite7);
  stickkeyword(T("pit"), HiliteIDs::Hilite7);
  stickkeyword(T("pi"), HiliteIDs::Hilite7);
  stickkeyword(T("p"), HiliteIDs::Hilite7);
  stickkeyword(T("note"), HiliteIDs::Hilite5);
  stickkeyword(T("mark"), HiliteIDs::Hilite5);
  stickkeyword(T("rest"), HiliteIDs::Hilite5);
  stickkeyword(T("measure"), HiliteIDs::Hilite5);
  stickkeyword(T("meas"), HiliteIDs::Hilite5);
  // settings
  info_setfilter fi0 = {0, 0, 0, module_nomodtype, 0, module_noloc, 3, info_none};
  info_setfilterlist fi = {1, &fi0};
  info_setlist lst = info_list_settings(0, &fi, 0, 0, 0);
  for (info_setting* s = lst.sets, *se = lst.sets + lst.n; s < se; ++s) stickkeyword(s->name, HiliteIDs::Hilite4);
  // built-in
  stickkeyword(T("template"), HiliteIDs::Hilite5);
  stickkeyword(T("id"), HiliteIDs::Hilite5);
  stickkeyword(T("imports"), HiliteIDs::Hilite5);
  stickkeyword(T("export"), HiliteIDs::Hilite5);
  stickkeyword(T("parts"), HiliteIDs::Hilite5);
  //stickkeyword(T("partsref"), HiliteIDs::Hilite5);
  stickkeyword(T("metapart"), HiliteIDs::Hilite5);
  stickkeyword(T("percinsts"), HiliteIDs::Hilite5);
  stickkeyword(T("percinst"), HiliteIDs::Hilite5);
  stickkeyword(T("inst"), HiliteIDs::Hilite5);
  stickkeyword(T("clefs"), HiliteIDs::Hilite5);
  stickkeyword(T("staves"), HiliteIDs::Hilite5);
  stickkeyword(T("staff"), HiliteIDs::Hilite5);
  stickkeyword(T("measdef"), HiliteIDs::Hilite5);
}

FomusSyntax::~FomusSyntax()
{
  clearSingletonInstance();
}

bool FomusSyntax::isTopLevel(String line)
{
  // true if line is not white in column zero.
  if ( line == String::empty )
    return false;
  else if ( !char_white_p(syntab, line[0]) )
    return true;
  else return false;
}

int FomusSyntax::getIndent (const String text, int i, int top, int beg)
{
  std::stack<int> sta;
  //std::cout << "|" << text.toUTF8() << "| " << bot << " " << top << std::endl;
  bool lc = false, cc = false, dq = false, sq = false, br = false;
  int col = 0;
  for (++i; i < beg; ++i) {
    char x0 = i >= 1 ? text[i - 1] : 0;
    char x = text[i];
    ++col;
    if (x0 == '/' && x == '/') {lc = true; continue;}
    if (x == '\n') {lc = false; col = -1; continue;}
    if (lc) continue;
    if (x0 == '/' && x == '-') {cc = true; continue;}
    if (x0 == '-' && x == '/') {cc = false; continue;}
    if (cc) continue;
    if (x == '"' && x0 != '\\' && !sq) {dq = !dq; continue;}
    if (x == '\'' && x0 != '\\' && !dq) {sq = !sq; continue;}
    if (dq || sq) continue;
    if (x == '[') {sta.push(col + 1); br = true; continue;}
    if (x == ']') {if (!sta.empty()) sta.pop(); br = false; continue;}
    if (br) continue;
    if (x == '{') {sta.push(sta.empty() ? tabwidth : sta.top() + tabwidth); continue;}
    if (x == '}') {if (!sta.empty()) sta.pop(); continue;}
    if (x == '(' || x == '<') {sta.push(col + 1); continue;}
    if (x == ')' || x == '>') {if (!sta.empty()) sta.pop(); continue;}
  }
  return sta.empty() ? 0 : sta.top();
}

HiliteID FomusSyntax::getHilite (const String text, int start, int end)
{
  //std::cout << '|' << text.toUTF8() << '|' << std::endl << '|' << text.substring(start, end).toUTF8() << '|' << std::endl << std::endl;
  bool lc = false, cc = false, dq = false, sq = false, br = false;
  for (int i = 0; i <= start; ++i) {
    char x0 = i >= 1 ? text[i - 1] : 0;
    char x = text[i];
    char x1 = i + 1 < end ? text[i + 1] : 0; // assuming start is always a valid string pos
    if (x == '/' && x1 == '/') {lc = true; continue;}
    if (x == '\n') {lc = false; continue;}
    if (lc) continue;
    if (x0 == '-' && x == '/') {cc = false; continue;}
    if (x == '/' && x1 == '-') {cc = true; continue;}
    if (cc) continue;
    if (x == '"' && x0 != '\\' && !sq) {dq = !dq; continue;}
    if (x == '\'' && x0 != '\\' && !dq) {sq = !sq; continue;}
    if (dq || sq) continue;
    if (x == '[') {br = true; continue;}
    if (x == ']') {br = false; continue;}
    if (br) continue;
  }
  if (lc || cc) return HiliteIDs::Comment;
  if (dq || sq) return HiliteIDs::String;
  if (br) return HiliteIDs::Hilite4; // mark
  String str(text.substring(start, end));
  SynTokMap::const_iterator f(tokens.find(str));
  if (f != tokens.end()) return f->second->data1;
  return HiliteIDs::None;
} 

void FomusSyntax::eval(String text, bool isRegion, bool expand) {
  FOMUS f = fomus_new();
  fomus_parse(f, text.toUTF8());
  if (fomus_err) {
    fomus_free(f);
    return;
  }
  // *** SAVE THIS ***
  //   if (String(fomus_get_sval(f, "filename")).isEmpty()) {
  //     WildcardFileFilter wildcardFilter(getwildcards(), T("FOMUS Output Files"));
  //     FileBrowserComponent browser(FileBrowserComponent::saveFileMode, File::nonexistent, &wildcardFilter, 0);
  //     FileChooserDialogBox dialogBox(T("Run FOMUS"), T("Specify an output file path (`filename' setting value)..."),
  // 				   browser, false, Colours::white);
  //     if (dialogBox.show()) {
  //       fomus_sval(f, fomus_par_setting, fomus_act_set, "filename");
  //       fomus_sval(f, fomus_par_settingval, fomus_act_set, browser.getCurrentFile().getFullPathName().toUTF8());
  //     }
  //   }
  if (String(fomus_get_sval(f, "filename")).isEmpty()) {
    fomus_sval(f, fomus_par_setting, fomus_act_set, "filename");
    fomus_sval(f, fomus_par_settingval, fomus_act_set, DEFAULT_OUT);
  }
  fomus_run(f); // fomus destroys instance automatically
}

#endif
