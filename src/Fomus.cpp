/*=======================================================================*
  Copyright (C) 2009 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

// OLD SVN REVISION OF THIS FILE = 1823

// NOTES:
// Make sure this line is in the ConsoleWindow class in Console.h:
// TooltipWindow xxx;

#include "juce.h"

#ifdef JUCE_WIN32
#include "loadlibrary.h"
#endif

#include <cstdlib>
#include <vector>
#include <sstream>
#include <limits>
#include <stack>
#include <cctype>

#include "Enumerations.h"
#include "Fomus.h"
#include "Console.h"
#include "Preferences.h"
#include "CmSupport.h"
#include "Alerts.h"

#define FOMUS_TYPESONLY
#include <fomus/infoapi.h>

// juce defines JUCE_LINUX, JUCE_MAC or JUCE_WIN32 already
#if defined(JUCE_LINUX) || defined(JUCE_MAC)
#include <dlfcn.h>
#endif

/*=======================================================================*
                             Fomus Instance
 *=======================================================================*/

juce_ImplementSingleton(FomusSyntax) ;
juce_ImplementSingleton(Fomus);

bool fomuserr = false;

// some default output file for people who hate dialogue boxes
#define DEFAULT_OUT "out.ly"

bool check_fomus_exists() {
#ifndef GRACE
  initfomus();
#endif  
  static bool fomus_printederr = false;
  if (fomus_exists) return true;
  if (!fomus_printederr) {
    fomus_printederr = true;
    Console::getInstance()->printError((char*)">>> Error: Fomus: can't find FOMUS library\n");
  }
  return false;
}

String getwildcards() {
  String r;
  info_extslist f(fapi_info_list_exts());
  bool fi = true;
  String mid("mid");
  for (const char **i = f.exts, **ie = (f.exts + f.n); i < ie; ++i) {
    if (*i == mid.toUTF8()) continue; // skip midi files
    if (fi) fi = false; else r += ';';
    r += String("*.") + *i;
  }
  return r;
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
    FileChooser choose(T("Save Score"), File::getCurrentWorkingDirectory(), "*.fms");
    if (choose.browseForFileToSave(true)) {
      fapi_fomus_save(fapi_fomus_copy(getfomusdata()), choose.getResult().getFullPathName().toUTF8());
    }
  } else
#endif
    {
      fapi_fomus_save(fapi_fomus_copy(getfomusdata()), fn.toUTF8());
    }
}

inline void spitout(const char* str) 
{
  Console::getInstance()->printOutput(String(";; ") + str);
}

fomus_err_type fapi_fomus_err;
fomus_version_type fapi_fomus_version;
fomus_init_type fapi_fomus_init;
fomus_new_type fapi_fomus_new;
fomus_free_type fapi_fomus_free;
fomus_clear_type fapi_fomus_clear;
fomus_ival_type fapi_fomus_ival;
fomus_rval_type fapi_fomus_rval;
fomus_fval_type fapi_fomus_fval;
fomus_sval_type fapi_fomus_sval;
fomus_act_type fapi_fomus_act;
fomus_load_type fapi_fomus_load;
fomus_parse_type fapi_fomus_parse;
fomus_run_type fapi_fomus_run;
fomus_copy_type fapi_fomus_copy;
fomus_save_type fapi_fomus_save;
fomus_set_outputs_type fapi_fomus_set_outputs;
fomus_get_ival_type fapi_fomus_get_ival;
fomus_get_rval_type fapi_fomus_get_rval;
fomus_get_fval_type fapi_fomus_get_fval;
fomus_get_sval_type fapi_fomus_get_sval;
info_list_exts_type fapi_info_list_exts;
info_infoapi_version_type fapi_info_infoapi_version;
fomus_api_version_type fapi_fomus_api_version;
fomus_merge_type fapi_fomus_merge;
#ifdef GRACE
info_list_modules_type fapi_info_list_modules;
info_list_settings_type fapi_info_list_settings;
info_list_marks_type fapi_info_list_marks;
info_getlastentry_type fapi_info_getlastentry;
info_list_percinsts_type fapi_info_list_percinsts;
info_list_insts_type fapi_info_list_insts;
info_list_parts_type fapi_info_list_parts;
info_list_metaparts_type fapi_info_list_metaparts;
info_list_measdefs_type fapi_info_list_measdefs;
settingloc_to_str_type fapi_settingloc_to_str;
module_id_type fapi_module_id;
modtype_to_str_type fapi_modtype_to_str;
#endif

struct dlerr {};
inline void* fdlsym(void *handle, const char *symbol) {
  void* ret = dlsym(handle, symbol);
  if (!ret) throw dlerr();
  return ret;
}

bool fomus_exists = false;

void initfomus() {
  static bool triedit = false;
  if (!fomus_exists) {
    if (triedit) return;
    triedit = true;
    try {
#if defined(JUCE_LINUX)
      void* ha = dlopen((String(FOMUSLIBPATH) + "/libfomus.so").toUTF8(), RTLD_LAZY | RTLD_GLOBAL);
      if (!ha) {
	ha = dlopen("libfomus.so", RTLD_LAZY | RTLD_GLOBAL);
	if (!ha) {
	  ha = dlopen("/usr/local/lib/libfomus.so", RTLD_LAZY | RTLD_GLOBAL);
	  if (!ha) {
	    ha = dlopen("/usr/lib/libfomus.so", RTLD_LAZY | RTLD_GLOBAL);
	    if (!ha) return;
	  }
	}
      }
#elif defined(JUCE_MAC)
      void* ha = dlopen((String(FOMUSLIBPATH) + "/libfomus.dylib").toUTF8(), RTLD_LAZY | RTLD_GLOBAL);
      if (!ha) {
	ha = dlopen("libfomus.dylib", RTLD_LAZY | RTLD_GLOBAL);
	if (!ha) {
	  ha = dlopen("/usr/local/lib/libfomus.dylib", RTLD_LAZY | RTLD_GLOBAL);
	  if (!ha) {
	    ha = dlopen("/usr/lib/libfomus.dylib", RTLD_LAZY | RTLD_GLOBAL);
	    if (!ha) return;
	  }
	}
      }
#elif defined(JUCE_WIN32)
     void* ha = dlopen();
     if (!ha) return;
#endif
      fapi_fomus_api_version = (fomus_api_version_type)fdlsym(ha, "fomus_api_version");
      fapi_info_infoapi_version = (info_infoapi_version_type)fdlsym(ha, "info_infoapi_version");
      if (FOMUS_API_VERSION < fapi_fomus_api_version() || FOMUS_INFOAPI_VERSION < fapi_info_infoapi_version()) {
	Console::getInstance()->printError((char*)">>> Error: Fomus: FOMUS library has changed--upgrade Grace to a newer version that is compatible\n");
	return;	
      }
      if (FOMUS_API_VERSION > fapi_fomus_api_version() || FOMUS_INFOAPI_VERSION > fapi_info_infoapi_version()) {
	Console::getInstance()->printError((char*)">>> Error: Fomus: FOMUS library is too old--upgrade FOMUS to a newer version that is compatible\n");
	return;	
      }
      fapi_fomus_err = (fomus_err_type)fdlsym(ha, "fomus_err");
      fapi_fomus_version = (fomus_version_type)fdlsym(ha, "fomus_version");
      fapi_fomus_init = (fomus_init_type)fdlsym(ha, "fomus_init");
      fapi_fomus_new = (fomus_new_type)fdlsym(ha, "fomus_new");
      fapi_fomus_free = (fomus_free_type)fdlsym(ha, "fomus_free");
      fapi_fomus_clear = (fomus_clear_type)fdlsym(ha, "fomus_clear");
      fapi_fomus_ival = (fomus_ival_type)fdlsym(ha, "fomus_ival");
      fapi_fomus_rval = (fomus_rval_type)fdlsym(ha, "fomus_rval");
      fapi_fomus_fval = (fomus_fval_type)fdlsym(ha, "fomus_fval");
      fapi_fomus_sval = (fomus_sval_type)fdlsym(ha, "fomus_sval");
      fapi_fomus_act = (fomus_act_type)fdlsym(ha, "fomus_act");
      fapi_fomus_load = (fomus_load_type)fdlsym(ha, "fomus_load");
      fapi_fomus_parse = (fomus_parse_type)fdlsym(ha, "fomus_parse");
      fapi_fomus_run = (fomus_run_type)fdlsym(ha, "fomus_run");
      fapi_fomus_copy = (fomus_copy_type)fdlsym(ha, "fomus_copy");
      fapi_fomus_save = (fomus_save_type)fdlsym(ha, "fomus_save");
      fapi_fomus_set_outputs = (fomus_set_outputs_type)fdlsym(ha, "fomus_set_outputs");
      fapi_fomus_get_ival = (fomus_get_ival_type)fdlsym(ha, "fomus_get_ival");
      fapi_fomus_get_rval = (fomus_get_rval_type)fdlsym(ha, "fomus_get_rval");
      fapi_fomus_get_fval = (fomus_get_fval_type)fdlsym(ha, "fomus_get_fval");
      fapi_fomus_get_sval = (fomus_get_sval_type)fdlsym(ha, "fomus_get_sval");
      fapi_info_list_exts = (info_list_exts_type)fdlsym(ha, "info_list_exts");
      fapi_fomus_merge = (fomus_merge_type)fdlsym(ha, "fomus_merge");
#ifdef GRACE
      fapi_info_list_modules = (info_list_modules_type)fdlsym(ha, "info_list_modules");
      fapi_info_list_settings = (info_list_settings_type)fdlsym(ha, "info_list_settings");
      fapi_info_list_marks = (info_list_marks_type)fdlsym(ha, "info_list_marks");
      fapi_info_getlastentry = (info_getlastentry_type)fdlsym(ha, "info_getlastentry");
      fapi_info_list_percinsts = (info_list_percinsts_type)fdlsym(ha, "info_get_percinsts");
      fapi_info_list_insts = (info_list_insts_type)fdlsym(ha, "info_get_insts");
      fapi_info_list_parts = (info_list_parts_type)fdlsym(ha, "info_get_parts");
      fapi_info_list_metaparts = (info_list_metaparts_type)fdlsym(ha, "info_get_metaparts");
      fapi_info_list_measdefs = (info_list_measdefs_type)fdlsym(ha, "info_get_measdefs");
      fapi_settingloc_to_str = (settingloc_to_str_type)fdlsym(ha, "info_settingloc_to_str");
      fapi_module_id = (module_id_type)fdlsym(ha, "module_id");
      fapi_modtype_to_str = (modtype_to_str_type)fdlsym(ha, "info_modtype_to_str");
#endif
    } catch (const dlerr& e) {e;
      Console::getInstance()->printError((char*)">>> Error: Fomus: error loading libfomus\n");      
      return;
    }
    fapi_fomus_init();
    fapi_fomus_set_outputs(&spitout, &spitout, true);
    fomus_exists = true;
  }
}


void Fomus::newScore(const String& nam, const bool fromscm)
{
  FomusScore* score = new FomusScore();
#ifdef GRACE
  if (!fromscm && nam.isEmpty() && scores.size() > 0) {
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
    String fn2(fapi_fomus_get_sval(scores.getUnchecked(i)->getfom(), "filename"));
    if (!fn2.isEmpty() && completeFile(fn2) == fn) { // find an exact match
      current = i;
      return;
    }
  }
  newScore(nam, fromscm); // selectScore is always from Scheme
}

void Fomus::mergeScore(const String& nam, fomus_int num, fomus_int den, fomus_float flt)
{
  File fn(completeFile(nam));
  for (int i = 0; i < scores.size(); ++i) {
    String fn2(fapi_fomus_get_sval(scores.getUnchecked(i)->getfom(), "filename"));
    if (!fn2.isEmpty() && completeFile(fn2) == fn) { // find an exact match
      switch (den) {
      case -1: fval(fomus_par_events, fomus_act_set, flt); break;
      case 0: ival(fomus_par_events, fomus_act_set, num); break;
      default: if (den > 0) rval(fomus_par_events, fomus_act_set, num, den); break;
      }
      fapi_fomus_merge(scores.getUnchecked(current)->getfom(), scores.getUnchecked(i)->getfom());
      return;
    }
  }
  Console::getInstance()->printError((char*)">>> Error: Fomus: merge source doesn't exist\n");        
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
  fapi_fomus_act(getfomusdata(), fomus_par_events, fomus_act_clear);
}

void Fomus::loadScore(String filename)
{
  fapi_fomus_load(getfomusdata(), (char*)filename.toUTF8());
  String fn(fapi_fomus_get_sval(getfomusdata(), "filename"));
  scores.getUnchecked(current)->name = (fn.isEmpty() ? String("(untitled)") : completeFile(fn).getFileName());
}

void Fomus::runScore(const bool fromscm)
{
  if (fomuserr) {
    Console::getInstance()->printError((char*)">>> Error: Fomus: run canceled due to input errors\n");
    return;
  }
#ifdef GRACE
  if (String(fapi_fomus_get_sval(getfomusdata(), "filename")).isEmpty()) {
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
  if (String(fapi_fomus_get_sval(getfomusdata(), "filename")).isEmpty()) {
    String fn0("out.ly");
    File fn(File::getCurrentWorkingDirectory().getFullPathName() + File::separator + fn0);
    scores.getUnchecked(current)->name = fn0;
    sval(fomus_par_setting, fomus_act_set, "filename");
    sval(fomus_par_settingval, fomus_act_set, fn.getFullPathName());
  }
#endif
#ifdef GRACE
  String pa(fapi_fomus_get_sval(getfomusdata(), "lily-exe-path"));
  if (File::isAbsolutePath(pa)) {
    if (!File(pa).existsAsFile()) {
      sval(fomus_par_setting, fomus_act_set, "lily-exe-path");
      sval(fomus_par_settingval, fomus_act_set, "");  
    }
  }
  String pa2(fapi_fomus_get_sval(getfomusdata(), "lily-view-exe-path"));
  if (File::isAbsolutePath(pa2)) {
    if (!File(pa2).existsAsFile()) {
      sval(fomus_par_setting, fomus_act_set, "lily-view-exe-path");
      sval(fomus_par_settingval, fomus_act_set, "");  
    }
  }
#endif  
  fapi_fomus_run(fapi_fomus_copy(getfomusdata()));
}

bool Fomus::proctime(int act) {
  if (act == fomus_act_n) {
    if (SchemeThread::getInstance()->isScoreMode()) {
      fapi_fomus_fval(getfomusdata(), fomus_par_time, fomus_act_set, SchemeThread::getInstance()->scoretime);
      if (fapi_fomus_err()) fomuserr = true;
    } else {
      fomuserr = true;
      Console::getInstance()->printError((char*)">>> Error: Fomus: need a time argument\n");
    }
    return true;
  }
  return false;
}

void Fomus::ival(int par, int act, fomus_int val)
{
  fapi_fomus_ival(getfomusdata(), par, act, val);
  if (fapi_fomus_err()) fomuserr = true;
}

void Fomus::rval(int par, int act, fomus_int num, fomus_int den)
{
  fapi_fomus_rval(getfomusdata(), par, act, num, den);
  if (fapi_fomus_err()) fomuserr = true;
}

void Fomus::fval(int par, int act, double val)
{
  fapi_fomus_fval(getfomusdata(), par, act, val);
  if (fapi_fomus_err()) fomuserr = true;
}

void Fomus::sval(int par, int act, const String& val) 
{
  fapi_fomus_sval(getfomusdata(), par, act, (char*)val.toUTF8());
  if (fapi_fomus_err()) fomuserr = true;
}

void Fomus::act(int par, int act) 
{
  if (proctime(act)) return;
  fapi_fomus_act(getfomusdata(), par, act);
  if (fapi_fomus_err()) fomuserr = true;
}

// SAVE ME!
// called by sprout to open and/or initialize a (possibly) new score
// instance for receiving data from processes.  scorename is either
// "fomus" or "*.{ly|fms|xml}". if its "fomus" maybe the current
// score instance should be used and if its a file name a new score
// with that output file and appropriate back end should become
// current?  scoreargs is a string containing whatever the user
// passed as to sprout arguments to the score

// SAVE ME!
// if scoretime > 0 then we are being called under a process and the
// user's xml time value needs to be shifted by that value to
// determine the true time of the note in the score. if scoretime is
// 0 then treat the xml time value as the absolute timestamp in the
// score.

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
  String getid() const {return id;}
  const String& getchangedstr() const {return chstr;}
  bool isdef() {
    if (kndef) return def;
    kndef = true;
    return (def = (chstr == defstr));
  }
  bool validate() {
    if (knvalid) return true;
    valid = valid_aux();
    knvalid = true;
    if (!valid) Alerts::showMessageBox(AlertWindow::WarningIcon,
                                       T("FOMUS Settings"),
                                       T("Error in ") + what() + T(" `") + String(id) + T("'."));
    return valid;
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
  virtual bool needsreset() const {return false;}
protected:
  virtual String what() const = 0;
  virtual bool valid_aux() = 0;
  //virtual void post_valid() {}
};

// settings
class fomusinfocont_sets;
class fomus_set:public fomusinfo {
  String descdoc, modname, loc, uselevel, typedoc;
  //const fomusinfocont_sets& cont;
  bool reset;
public:
  fomus_set(int c, FOMUS fom, struct info_setting& set, const String& def):fomusinfo(c, fom, set.name, def, set.valstr),
									   /*id(set.id),*/ descdoc(set.descdoc),
									   modname(set.modname), loc(fapi_settingloc_to_str(set.loc)),
									   typedoc(set.typedoc), reset(set.reset) {
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
  bool needsreset() const {return reset;}
private:
  bool valid_aux() {
    fapi_fomus_parse(fom, (id + " = " + (chstr.isEmpty() ? String("\"\"") : chstr)).toUTF8());
    return !fapi_fomus_err();
  }
  String what() const {return T("setting");}
  //void post_valid();
};

inline String rempar(const char* str0) {
  String str(str0);
  if (str.length() >= 2 && (str[0] == '(' || str[0] == '<')) {
    return str.substring(1, str.length() - 1);
  } else return str;
}
class fomus_other:public fomusinfo {
public:
  fomus_other(int c, FOMUS fom, const info_objinfo& obj, const char* nam):fomusinfo(c, fom, nam, rempar(obj.valstr)) {}
private:
  bool valid_aux();
  virtual String what0() const = 0;
};
bool fomus_other::valid_aux() {
  fapi_fomus_parse(fom, (what0() + String(" ") + (chstr.isEmpty() ? T("<>") : (chstr[0] != '(' && chstr[0] != '<' ? (T("<") + chstr + T(">")) : chstr))).toUTF8());
  if (fapi_fomus_err()) return false;
  struct info_objinfo x(fapi_info_getlastentry(fom));
  id = fapi_module_id(x.obj);
  return true;
}

class fomus_part:public fomus_other {
public:
  fomus_part(int c, FOMUS fom, const info_objinfo& obj, const char* nam):fomus_other(c, fom, obj, nam) {}
  String what() const {return T("part");}
  String what0() const {return T("part");}
  void remove() const {fapi_fomus_sval(fom, fomus_par_part, fomus_act_remove, id.toUTF8());}
};
class fomus_metapart:public fomus_other {
public:
  fomus_metapart(int c, FOMUS fom, const info_objinfo& obj, const char* nam):fomus_other(c, fom, obj, nam) {}
  String what() const {return T("metapart");}
  String what0() const {return T("metapart");}
  void remove() const {fapi_fomus_sval(fom, fomus_par_metapart, fomus_act_remove, id.toUTF8());}
};
class fomus_measdef:public fomus_other {
public:
  fomus_measdef(int c, FOMUS fom, const info_objinfo& obj, const char* nam):fomus_other(c, fom, obj, nam) {}
  String what() const {return T("measure definition");}  
  String what0() const {return T("measdef");}
  void remove() const {fapi_fomus_sval(fom, fomus_par_measdef, fomus_act_remove, id.toUTF8());}
};
class fomus_inst:public fomus_other {
public:
  fomus_inst(int c, FOMUS fom, const info_objinfo& obj, const char* nam):fomus_other(c, fom, obj, nam) {}
  String what() const {return T("instrument");}  
  String what0() const {return T("inst");}
  void remove() const {fapi_fomus_sval(fom, fomus_par_inst, fomus_act_remove, id.toUTF8());}
};
class fomus_percinst:public fomus_other {
public:
  fomus_percinst(int c, FOMUS fom, const info_objinfo& obj, const char* nam):fomus_other(c, fom, obj, nam) {}
  String what() const {return T("percussion instrument");}  
  String what0() const {return T("percinst");}
  void remove() const {fapi_fomus_sval(fom, fomus_par_percinst, fomus_act_remove, id.toUTF8());}
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
  int getn() const {return (int)stuff.size();}
  fomusinfo* get(int ind) const {return stuff[ind];}
  int getuselevel() const {return uselevel;}
  void setuselevel(int lvl) {
    uselevel = lvl;
    reset();
  }
  virtual bool issetting() const {return false;}
  virtual fomusinfo* createnew(const String& txt) {return 0;}
  void remove(int num) {
    stuff[num]->remove();
    for (std::vector<fomusinfo*>::iterator i(stuff.begin() + num); i != stuff.end(); ++i) (*i)->dec();
    stuff.erase(stuff.begin() + num);
  }
private:
  virtual void reset_aux() = 0;
};

class FOMUSSettings;
class fomusinfocont_sets:public fomusinfocont {
  std::vector<String> defs;
  FOMUSSettings *comp;
public:
  fomusinfocont_sets(FOMUS fom, int uselevel); // ***** pass and store component for refresh
  bool issetting() const {return true;}
  FOMUSSettings* setcomp(FOMUSSettings *c) {return comp = c;}
  void doreset() const;
private:
  void reset_aux();
};

fomusinfocont_sets::fomusinfocont_sets(FOMUS fom, int uselevel):fomusinfocont(fom, uselevel), comp(0) {
  struct info_setfilter se = {0, 0, 0, module_nomodtype, 0, module_noloc, 3, info_none}; 
  struct info_setfilterlist fi = {1, &se};
  info_setlist sets(fapi_info_list_settings(0, &fi, 0, 0, -1)); // config defaults
  int c = 0;
  defs.resize(sets.n);
  for (info_setting* s(sets.sets), *se(sets.sets + sets.n); s < se; ++s) {
    if (s->id < sets.n) defs[s->id] = s->valstr;
  }
}

void fomusinfocont_sets::reset_aux() {
  struct info_setfilter se = {0, 0, 0, module_nomodtype, 0, module_noloc, uselevel, info_none}; 
  struct info_setfilterlist fi = {1, &se};
  info_setlist sets(fapi_info_list_settings(fom, &fi, 0, 0, -1));
  int c = 0;
  for (info_setting* s(sets.sets), *se(sets.sets + sets.n); s < se; ++s) stuff.push_back(new fomus_set(c++, fom, *s, defs[s->id]));
}

class fomusinfocont_other:public fomusinfocont {
public:
  fomusinfocont_other(FOMUS fom):fomusinfocont(fom, 0) {}
private:
  void reset_aux();
  virtual info_objinfo_list getem() const = 0;
  virtual fomusinfo* getnew(int c, FOMUS fom, const info_objinfo& obj, const char* nam) = 0;
};
void fomusinfocont_other::reset_aux() {
  info_objinfo_list li(getem());
  int c = 0;
  for (info_objinfo *i(li.objs), *ie(li.objs + li.n); i < ie; ++i) {
    const char* nam = fapi_module_id(i->obj);
    if (nam[0]) stuff.push_back(getnew(c++, fom, *i, nam));
  }
}

class fomusinfocont_parts:public fomusinfocont_other {
public:
  fomusinfocont_parts(FOMUS fom):fomusinfocont_other(fom) {}
private:
  info_objinfo_list getem() const {return fapi_info_list_parts(fom);}
  fomusinfo* getnew(int c, FOMUS fom, const info_objinfo& obj, const char* nam) {return new fomus_part(c, fom, obj, nam);}
  fomusinfo* createnew(const String& txt);
};
fomusinfo* fomusinfocont_parts::createnew(const String& txt) 
{
  String str(T("part "));
  if (txt.isEmpty())
    str << T("<>");
  else if (txt[0] != '(' && txt[0] != '<' )
    str << T("<") << txt << T(">");
  else 
    str << txt;

  fapi_fomus_parse(fom, str.toUTF8());
  if (fapi_fomus_err()) {
    Alerts::showMessageBox(AlertWindow::WarningIcon,
				T("FOMUS Settings"),
				T("Error in part"));
    return 0;
  } else {
    struct info_objinfo x(fapi_info_getlastentry(fom));
    fomus_part* y;
    stuff.push_back(y = new fomus_part((int)stuff.size(), fom, x, fapi_module_id(x.obj)));
    return y;
  }
}

class fomusinfocont_metaparts:public fomusinfocont_other {
public:
  fomusinfocont_metaparts(FOMUS fom):fomusinfocont_other(fom) {}
private:
  info_objinfo_list getem() const {return fapi_info_list_metaparts(fom);}
  fomusinfo* getnew(int c, FOMUS fom, const info_objinfo& obj, const char* nam) {return new fomus_metapart(c, fom, obj, nam);}
  fomusinfo* createnew(const String& txt);
};
fomusinfo* fomusinfocont_metaparts::createnew(const String& txt) 
{
  String str (T("metapart "));
  if (txt.isEmpty())
    str << T("<>") ;
  else if (txt[0] != '(' && txt[0] != '<')
    str << T("<") << txt << T(">");
  else 
    str << txt;
  fapi_fomus_parse(fom, str.toUTF8());
  if (fapi_fomus_err()) {
    Alerts::showMessageBox(AlertWindow::WarningIcon,
				T("FOMUS Settings"),
				T("Error in metapart"));
    return 0;
  } else {
    struct info_objinfo x(fapi_info_getlastentry(fom));
    fomus_metapart* y;
    stuff.push_back(y = new fomus_metapart((int)stuff.size(), fom, x, fapi_module_id(x.obj)));
    return y;
  }
}

class fomusinfocont_measdefs:public fomusinfocont_other {
public:
  fomusinfocont_measdefs(FOMUS fom):fomusinfocont_other(fom) {}
private:
  info_objinfo_list getem() const {return fapi_info_list_measdefs(fom);}
  fomusinfo* getnew(int c, FOMUS fom, const info_objinfo& obj, const char* nam) {return new fomus_measdef(c, fom, obj, nam);}
  fomusinfo* createnew(const String& txt);
};
fomusinfo* fomusinfocont_measdefs::createnew(const String& txt) 
{
  String str (T("measdef "));
  if (txt.isEmpty())
    str << T("<>");
  else if (txt[0] != '(' && txt[0] != '<')
    str << T("<") << txt << T(">");
  else 
    str << txt;
  fapi_fomus_parse(fom, str.toUTF8());
  if (fapi_fomus_err()) {
    Alerts::showMessageBox(AlertWindow::WarningIcon,
				T("FOMUS Settings"),
				T("Error in measure definition"));
    return 0;
  } else {
    struct info_objinfo x(fapi_info_getlastentry(fom));
    fomus_measdef *y;
    stuff.push_back(y = new fomus_measdef((int)stuff.size(), fom, x, fapi_module_id(x.obj)));
    return y;
  }
}

class fomusinfocont_insts:public fomusinfocont_other {
public:
  fomusinfocont_insts(FOMUS fom):fomusinfocont_other(fom) {}
private:
  info_objinfo_list getem() const {return fapi_info_list_insts(fom);}
  fomusinfo* getnew(int c, FOMUS fom, const info_objinfo& obj, const char* nam) {return new fomus_inst(c, fom, obj, nam);}
  fomusinfo* createnew(const String& txt);
};
fomusinfo* fomusinfocont_insts::createnew(const String& txt) 
{
  String str (T("inst "));
  if (txt.isEmpty())
    str << T("<>");
  else if (txt[0] != '(' && txt[0] != '<')
    str << T("<") << txt << T(">");
  else
    str << txt;
  fapi_fomus_parse(fom, str.toUTF8());
  if (fapi_fomus_err()) {
    Alerts::showMessageBox(AlertWindow::WarningIcon,
				T("FOMUS Settings"),
				T("Error in instrument"));
    return 0;
  } else {
    struct info_objinfo x(fapi_info_getlastentry(fom));
    fomus_inst *y;
    stuff.push_back(y = new fomus_inst((int)stuff.size(), fom, x, fapi_module_id(x.obj)));
    return y;
  }
}

class fomusinfocont_percinsts:public fomusinfocont_other {
public:
  fomusinfocont_percinsts(FOMUS fom):fomusinfocont_other(fom) {}
private:
  info_objinfo_list getem() const {return fapi_info_list_percinsts(fom);}
  fomusinfo* getnew(int c, FOMUS fom, const info_objinfo& obj, const char* nam) {return new fomus_percinst(c, fom, obj, nam);}
  fomusinfo* createnew(const String& txt);
};
fomusinfo* fomusinfocont_percinsts::createnew(const String& txt) 
{
  String str (T("percinst "));
  if (txt.isEmpty())
    str << T("<>");
  else if (txt[0] != '(' && txt[0] != '<')
    str << T("<") << txt << T(">");
  else
    str << txt;
  fapi_fomus_parse(fom, str.toUTF8());
  if (fapi_fomus_err()) {
    Alerts::showMessageBox(AlertWindow::WarningIcon,
				T("FOMUS Settings"),
				T("Error in percussion instrument"));
    return 0;
  } else {
    struct info_objinfo x(fapi_info_getlastentry(fom));
    fomus_percinst *y;
    stuff.push_back(y = new fomus_percinst((int)stuff.size(), fom, x, fapi_module_id(x.obj)));
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
		      const tchar passwordCharacter = 0):TextEditor(componentName, passwordCharacter), inf(inf), boxmodel(boxmodel), lb(lb), dirty(false), invalid(false) {}
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
  bool invalid;
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
  void textEditorReturnKeyPressed(TextEditor&) {validate();}
  void textEditorEscapeKeyPressed(TextEditor&) {defon();}
  void textEditorFocusLost(TextEditor&) {}

  juce_UseDebuggingNewOperator

  //int getid() const {return ValueText->getid();}
  String getstoretext() const {return ValueText->getText();}
  bool getstoredef() const {return DefaultButton ? DefaultButton->getToggleState() : false;}
  
  void validate() {ValueText->validate();}
  int getnum() {return ValueText->getnum();}

  void setname(const String& str) {NameText->setText(str, false);}
private:
  Label* NameLabel;
  Label* NameText;
  //Label* ModuleLabel;
  //Label* ModuleText;
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
  }

  void defon() {
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
      //ModuleText->setText(((fomus_set*)set)->getmodname(), false);
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
												//ModuleLabel (0),
												//ModuleText (0),
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
    // addAndMakeVisible (ModuleLabel = new Label (T("Module Label"),
    // 						T("Module:")));
    // ModuleLabel->setFont (Font (13.0000f, Font::plain));
    // ModuleLabel->setJustificationType (Justification::centredLeft);
    // ModuleLabel->setEditable (false, false, false);
    // ModuleLabel->setColour (TextEditor::textColourId, Colours::black);
    // ModuleLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
    
    // addAndMakeVisible (ModuleText = new Label (T("Module Text"),
    // 					       String::empty));
    // ModuleText->setFont (Font (13.0000f, Font::plain));
    // ModuleText->setJustificationType (Justification::centredLeft);
    // ModuleText->setEditable (false, false, false);
    // ModuleText->setColour (TextEditor::textColourId, Colours::black);
    // ModuleText->setColour (TextEditor::backgroundColourId, Colour (0x0));
    
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
  ValueText->addListener(this);
  
  setSize (640 + 32, 16 + 72);
  
  updateset(inf);
}

FOMUSSettingsListBoxItem::~FOMUSSettingsListBoxItem() 
{
  deleteAndZero (NameLabel);
  deleteAndZero (NameText);
  //deleteAndZero (ModuleLabel);
  //deleteAndZero (ModuleText);
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
  //if (ModuleLabel) ModuleLabel->setBounds (8 + 232, 8 + 0, 56, 16);
  //if (ModuleText) ModuleText->setBounds (8 + 280, 8 + 0, 83, 16);
  if (LocationLabel) LocationLabel->setBounds (8 + 232, 8 + 0, 56, 16);
  if (LocationText) LocationText->setBounds (8 + 284, 8 + 0, 83, 16);
  if (UseLevelLabel) UseLevelLabel->setBounds (8 + 368, 8 + 0, 56, 16);
  if (UseLevelText) UseLevelText->setBounds (8 + 420, 8 + 0, 75, 16);
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
  bool hasnew;
public:
  fomusinfocont& infos;
  FOMUSListBoxModel(fomusinfocont& infos, FOMUSSettingsListBox* textlistener):ListBoxModel(), textlistener(textlistener), infos(infos), hasnew(false) {}
  int getNumRows() {return hasnew ? infos.getn() + 1 : infos.getn();}
  void paintListBoxItem(int rowNumber, Graphics &g, int width, int height, bool rowIsSelected) {}
  Component* refreshComponentForRow(int rowNumber, bool isRowSelected, Component *existingComponentToUpdate);
  void sethasnew();
  String createnew(const String& txt, fomusinfo* &inf);
  void deleteone(int id);
};

void FOMUSSettingsEditor::validate() {
  if (invalid) return;
  if (inf) {
    if (dirty) inf->change(getText().toUTF8());
    bool iv = inf->validate();
    if (iv && dirty && inf->needsreset()) {
      invalid = true;
      Alerts::showMessageBox(AlertWindow::InfoIcon,
			     T("FOMUS Settings"),
			     T("Other settings are being updated to reflect changes"));
      ((const fomusinfocont_sets&)boxmodel.infos).doreset();
      invalid = false;
    } else lb.setname(inf->getid());
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

class SetMessageListener:public MessageListener {
  void handleMessage(const Message &message);
};

// SETTINGS COMPONENT
class FOMUSSettings:public Component, public ButtonListener {
  fomusinfocont& infos;
public:
  SetMessageListener msg;
  FOMUSSettings (fomusinfocont& infos);
  ~FOMUSSettings();
  void resized();
  void buttonClicked (Button* buttonThatWasClicked);
  juce_UseDebuggingNewOperator
  void resetsets();
  private:
  void switchtouse(int lvl);
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

inline void fomusinfocont_sets::doreset() const {comp->msg.postMessage(new Message(0, 0, 0, comp));}
inline void SetMessageListener::handleMessage(const Message &message) {((FOMUSSettings*)message.pointerParameter)->resetsets();}

void FOMUSSettings::switchtouse(int lvl) {
  if (lvl != infos.getuselevel()) {
    removeChildComponent (component);
    delete component;
    infos.setuselevel(lvl);
    addAndMakeVisible (component = new FOMUSSettingsListBox(infos));
    component->setBounds (0, 16, getWidth(), getHeight() - 16);
  }
}

void FOMUSSettings::resetsets() {
  removeChildComponent (component);
  delete component;
  infos.reset();
  addAndMakeVisible (component = new FOMUSSettingsListBox(infos));
  component->setBounds (0, 16, getWidth(), getHeight() - 16);
}

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
    removeChildComponent (component);
    delete component;
    infos.reset();
    addAndMakeVisible (component = new FOMUSSettingsListBox (infos));
    component->setBounds (0, 0, getWidth(), getHeight() - 18);
  }
}

struct FileTabs:public TabbedComponent {
  fomusinfocont_sets sets;
  fomusinfocont_parts parts;
  fomusinfocont_metaparts metaparts;
  fomusinfocont_insts insts;
  fomusinfocont_percinsts percinsts;
  
  FileTabs(FOMUS fom):TabbedComponent(TabbedButtonBar::TabsAtTop), sets(fom, 0), parts(fom), metaparts(fom), /*measdefs(fom),*/ insts(fom), percinsts(fom) {
    sets.init();
    parts.init();
    metaparts.init();
    insts.init();
    percinsts.init();
    addTab(T("Settings"), Colours::white, sets.setcomp(new FOMUSSettings(sets)), true);
    addTab(T("Parts"), Colours::white, new FOMUSSettings(parts), true);
    addTab(T("Metaparts"), Colours::white, new FOMUSSettings(metaparts), true);
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
  return s;
}

void out_justify(std::ostream& f, String s, const int start = 0, bool va = true) {
  s.replace(T("\t"), T("        "));
  int i = 0;
  int je = s.length();
  const String exc("\"'`{}[]():;,.!?_");
  for (int j = (FILE_WIDTH - 1) - start; j < je; j += (FILE_WIDTH - 1) - start) {
    int js = i;
    while (js < j && s[js] != '\n') ++js;
    if (js < j) {
      f << (const char*)s.substring(i, ++js).toUTF8() << makenstring(start);
      i = j = js;
    } else {
      js = j;
      while (j > i && (va ? s[j] == ' ' : !(isalnum(s[j]) || exc.containsChar(s[j])))) --j;
      while (j > i && (va ? s[j - 1] != ' ' : isalnum(s[j - 1]) || exc.containsChar(s[j - 1]))) --j;
      if (j > i) {
	f << (const char*)s.substring(i, j).toUTF8() << "\n" << makenstring(start);
	i = j;
      } else {
	f << (const char*)s.substring(i, js).toUTF8() << "\n" << makenstring(start);
	i = j = js;
      }
    }
  }
  f << (const char*)s.substring(i).toUTF8();
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
  String fn(fapi_fomus_get_sval(getfomusdata(), "filename"));
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
  struct info_setlist lst(fapi_info_list_settings(0, &fff, &s, 0, 0));
  TextLayout& lay = ((FOMUSViewComponent*)(viewport->getViewedComponent()))->lay;
  lay.clear();
  Font no(13);
  Font ul(13, Font::underlined);
  Font bo(13, Font::bold);
  Font it(13, Font::italic);
  for (struct info_setting* i(lst.sets), *ie(lst.sets + lst.n); i < ie; ++i) {
    lay.appendText("name:", ul); lay.appendText(" ", no); lay.appendText(i->name, bo); lay.appendText("  ", no);
    lay.appendText("module:", ul); lay.appendText(" ", no); lay.appendText(i->modname, no); lay.appendText("  ", no);
    String lo(fapi_settingloc_to_str(i->loc));
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
  MedButton->setBounds (60, 0, 72, 16);
  AdvButton->setBounds (136, 0, 64, 16);
  GuruButton->setBounds (200, 0, 56, 16);
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
  struct info_marklist lst(fapi_info_list_marks(0, 0, &s, 0, 0));
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
  struct info_modlist lst(fapi_info_list_modules(0, &s, 0, 0));
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
    String ty(fapi_modtype_to_str(i->type));
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
  void currentTabChanged(int newCurrentTabIndex, const String &newCurrentTabName);
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
  Tabs->addTab (T("Settings"), Colours::white, new FOMUSSetsView(*textEditor, thebut), true);
  Tabs->addTab (T("Marks"), Colours::white, new FOMUSMarksView(), true);
  Tabs->addTab (T("Modules"), Colours::white, new FOMUSModsView(), true);
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
    textEditor->setBounds (56, getHeight() - 31, getWidth() - 200, 21);
    SearchName->setBounds (getWidth() - 142, getHeight() - 26, 48, 16);
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
  FileChooser choose(T("Load Score"), File::getCurrentWorkingDirectory(), "*.fms");  
  if (choose.browseForFileToOpen()) {
    loadScore(choose.getResult().getFullPathName());
  }
}

void Fomus::renameScoreDialog() 
{
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

FomusSyntax::FomusSyntax () // syntab
  : Syntax()
{
  type=TextIDs::Fomus;

  setCharSyntax(T("~!@#$%^&*-_.?/"), ScanIDs::SYN_SYMBOL);
  setCharSyntax(T("\"'"), ScanIDs::SYN_STRING);
  setCharSyntax(T("([{|"), ScanIDs::SYN_OPEN);
  setCharSyntax(T(")]}|"), ScanIDs::SYN_CLOSE);

  stickkeyword(T("voice"), TokenPartKeyword);
  stickkeyword(T("voi"), TokenPartKeyword);
  stickkeyword(T("vo"), TokenPartKeyword);
  stickkeyword(T("v"), TokenPartKeyword);
  stickkeyword(T("time"), TokenTimeKeyword);
  stickkeyword(T("tim"), TokenTimeKeyword);
  stickkeyword(T("ti"), TokenTimeKeyword);
  stickkeyword(T("t"), TokenTimeKeyword);
  stickkeyword(T("grace"), TokenTimeKeyword);
  stickkeyword(T("gra"), TokenTimeKeyword);
  stickkeyword(T("gr"), TokenTimeKeyword);
  stickkeyword(T("g"), TokenTimeKeyword);
  stickkeyword(T("dynamic"), TokenKeyword);
  stickkeyword(T("dyn"), TokenKeyword);
  stickkeyword(T("dy"), TokenKeyword);
  stickkeyword(T("y"), TokenKeyword);
  stickkeyword(T("duration"), TokenKeyword);
  stickkeyword(T("dur"), TokenKeyword);
  stickkeyword(T("du"), TokenKeyword);
  stickkeyword(T("d"), TokenKeyword);
  stickkeyword(T("part"), TokenPartKeyword);
  stickkeyword(T("par"), TokenPartKeyword);
  stickkeyword(T("pa"), TokenPartKeyword);
  stickkeyword(T("a"), TokenPartKeyword);
  stickkeyword(T("pitch"), TokenKeyword);
  stickkeyword(T("pit"), TokenKeyword);
  stickkeyword(T("pi"), TokenKeyword);
  stickkeyword(T("p"), TokenKeyword);
  
  stickkeyword(T("note"), TokenKeyword);
  stickkeyword(T("not"), TokenKeyword);
  stickkeyword(T("no"), TokenKeyword);
  stickkeyword(T("n"), TokenKeyword);
  stickkeyword(T("mark"), TokenKeyword);
  stickkeyword(T("mar"), TokenKeyword);
  stickkeyword(T("ma"), TokenKeyword);
  stickkeyword(T("m"), TokenKeyword);
  stickkeyword(T("rest"), TokenKeyword);
  stickkeyword(T("res"), TokenKeyword);
  stickkeyword(T("re"), TokenKeyword);
  stickkeyword(T("r"), TokenKeyword);
  
  stickkeyword(T("measure"), TokenTimeKeyword);
  stickkeyword(T("meas"), TokenTimeKeyword);
  stickkeyword(T("mea"), TokenTimeKeyword);
  stickkeyword(T("me"), TokenTimeKeyword);
  stickkeyword(T("e"), TokenTimeKeyword);
  // settings
  info_setfilter fi0 = {0, 0, 0, module_nomodtype, 0, module_noloc, 3, info_none};
  info_setfilterlist fi = {1, &fi0};
  info_setlist lst = fapi_info_list_settings(0, &fi, 0, 0, 0);
  for (info_setting* s = lst.sets, *se = lst.sets + lst.n; s < se; ++s) stickkeyword(s->name, TokenSetting);
  // built-in
  stickkeyword(T("template"), TokenKeyword);
  stickkeyword(T("id"), TokenKeyword);
  stickkeyword(T("imports"), TokenKeyword);
  stickkeyword(T("export"), TokenKeyword);
  stickkeyword(T("parts"), TokenKeyword);
  stickkeyword(T("metapart"), TokenPartKeyword);
  stickkeyword(T("percinsts"), TokenKeyword);
  stickkeyword(T("percinst"), TokenKeyword);
  stickkeyword(T("inst"), TokenPartKeyword);
  stickkeyword(T("clefs"), TokenKeyword);
  stickkeyword(T("staves"), TokenKeyword);
  stickkeyword(T("staff"), TokenKeyword);
  stickkeyword(T("measdef"), TokenPartKeyword);

  stickkeyword(T("include"), TokenKeyword);
  stickkeyword(T("macro"), TokenKeyword);
}

FomusSyntax::~FomusSyntax()
{
  clearSingletonInstance();
}

void FomusSyntax::stickkeyword(String str, const int hl) {
  addSynTok(str, hl);
  str[0] = toupper(str[0]);
  addSynTok(str, hl);
  for (int i = 1; i < str.length(); ++i) str[i] = toupper(str[i]);
  addSynTok(str, hl);
}

const StringArray FomusSyntax::getTokenTypes () 
{ 
  // FIXME FOR NEW CODE EDITOR

  // juce's CodeEditorComponent uses this array to name the
  // Tokenizer's tokenTypes, where each array index is a tokenType and
  // the string at that postion is its name. we use this array to map
  // tokenTypes to ColorTheme attribute names in the Xml ColorTheme.
  // for attributes see ColorThemeIDs class in Enumerations.h

  StringArray names;

  // Color Theme Attribute       Token Type
  //-------------------------------------------
  names.add(T("error"));      // TokenError
  names.add(T("plaintext"));  // TokenPlaintext
  names.add(T("comment"));    // TokenComment
  names.add(T("string"));     // TokenString
  names.add(T("keyword1"));   // TokenSharpsign
  names.add(T("keyword2"));   // TokenLispKeyword
  names.add(T("literal2"));   // TokenTimeKeyword
  names.add(T("literal3"));   // TokenPartKeyword
  return names;
}

const Colour FomusSyntax::getDefaultColour (int tokenType)
{
  switch (tokenType)
    {
    case TokenError: return Colours::red;
    case TokenPlaintext: return Colours::black;
    case TokenComment: return Colour(0xce, 0x00, 0x1a); //Colours::firebrick;
    case TokenString: return Colour(0xa1, 0x11, 0x53); //Colours::rosybrown;
    case TokenKeyword: return Colours::cadetblue; // Sharp Sign
    case TokenSetting: return Colour(0x8a, 0x2f, 0x8f); //Colours::orchid;Lisp KeywordColour(0x8a, 0x2f, 0x8f)
    case TokenTimeKeyword: return Colours::darkblue;
    default: return Colours::black;
    }
}

int FomusSyntax::readNextToken (CodeDocument::Iterator &source)
{
  static int par = 0;
  int typ = TokenError;
  source.skipWhitespace();
  tchar chr = source.peekNextChar();
  switch (chr)
    {
    case 0:
      source.skip();
      break;
    case T('/'): { // COMMENT
      CodeDocument::Iterator source1(source);
      source1.skip();
      switch (source1.peekNextChar()) {
      case T('/'): 
	source.skipToEndOfLine();
	typ = TokenComment;
	break;
      case T('-'):
	source.skip();
	source.skip();
	while (!source.isEOF()) {
	  if (source.nextChar() == T('-')) {
	    if (source.peekNextChar() == T('/')) break;
	  }
	}
	typ = TokenComment;
	break;
      default:
	source.skip();
	typ = TokenPlaintext;      
      }
      break;
    }
    case T('"'): // STRING
    case T('\''):
      {
        juce_wchar c, q = source.nextChar(); // pop quote char
        for (c = source.nextChar(); (c != q && c != 0); c = source.nextChar()) {
          if (c == T('\\')) source.skip(); // advance over \x
	}
        typ = TokenString;
      }
      break;
    default:
      {
        // advance to end of token, check for special words
        int i=0;
        String check;
        juce_wchar c, k=0;
        do 
          {
            c=source.nextChar();
            if (i<maxtoklen) // only gather maxtokenlen chars
              check<<c;
            i++;
            k=c;
          } while (isTokenChar(source.peekNextChar()));
        // i is now one beyond last constituent character
	if (i<=maxtoklen) // check for special word
          {
            SynTok* tok=getSynTok(check);
            if (tok)
	      {
		typ=tok->getType();
	      }
            else
              typ=SalIDs::TokenPlaintext;
          }
        else
          typ=SalIDs::TokenPlaintext;        
      }
    }
  return typ;
}

struct indpar {
  char wh;
  int i;
  indpar(const char wh, const int i):wh(wh), i(i) {}
  bool is(const char w) const {return w == wh;}
};

int FomusSyntax::getIndentation(CodeDocument& document, int line)
{
  int l = line;
  bool inbr = false;
  std::stack<indpar> sta;
  if (l <= 0) return -1;
  CodeDocument::Position st(&document, 0);
  while (true) {
    st.setLineAndIndex(--l, 0);
    if (l <= 0) break;
    switch (st.getCharacter()) {
    case T(' '):
    case T('\n'):
    case T('\t'):
      break;
    default:
      goto BREAK;
    }
  } 
 BREAK:
  CodeDocument::Position en(&document, line, 0);
  while (st != en) {
    juce_wchar ch(st.getCharacter());
    switch (ch) {
    case T('/'):
      switch (st.movedBy(1).getCharacter()) {
      case T('/'):
	do {
	  st.moveBy(1); if (st == en) goto DONE;
	} while (st.getCharacter() != T('\n'));
	break;
      case T('-'):
	st.moveBy(1); if (st == en) goto DONE;
	st.moveBy(1); if (st == en) goto DONE;
	while (true) {
	  if (st.getCharacter() == T('-')) {
	    if (st.movedBy(1).getCharacter() == T('/')) {
	      st.moveBy(1); if (st == en) goto DONE;
	      break;
	    }
	  } 
	  st.moveBy(1); if (st == en) goto DONE;
	}
	break;
      }
      break;
    case T('"'):
    case T('\''):
      {
	juce_wchar g = st.getCharacter();
	while (true) {
	  st.moveBy(1); if (st == en) goto DONE;
	  if (st.getCharacter() == g) break;
	  if (st.getCharacter() == '\\') {
	    st.moveBy(1); if (st == en) goto DONE;
	  }
	}
      }
      break;
    case '[':
      inbr = true; break;
    case ']':
      inbr = false; break; 
    case '(':
      if (!inbr) sta.push(indpar('(', st.getIndexInLine())); break;
    case '<':
      if (!inbr) sta.push(indpar('<', st.getIndexInLine())); break;
    case ')':
      if (!inbr) if (sta.top().is('(')) sta.pop(); break;
    case '>':
      if (!inbr) if (sta.top().is('>')) sta.pop(); break;
    }
    st.moveBy(1);
  }
 DONE:
  return (sta.empty() ? -1 : sta.top().i + 1);
}

int FomusSyntax::backwardExpr(CodeDocument& document, CodeDocument::Position& start, CodeDocument::Position& end)
{
  if (start.getPosition() >= end.getPosition()) {
    start.setPosition(0);
    end.setPosition(std::numeric_limits<int>::max());
  }
  return 1;
}
void FomusSyntax::eval(CodeDocument& document, const CodeDocument::Position start, const CodeDocument::Position end, 
                       bool expand, bool region) // region=true if a selection is made
{
  FOMUS f = fapi_fomus_new();
  fapi_fomus_parse(f, document.getTextBetween(start, end).toUTF8());
  if (fapi_fomus_err()) {
    fapi_fomus_free(f);
    return;
  }
  if (String(fapi_fomus_get_sval(f, "filename")).isEmpty()) {
    fapi_fomus_sval(f, fomus_par_setting, fomus_act_set, "filename");
    fapi_fomus_sval(f, fomus_par_settingval, fomus_act_set, DEFAULT_OUT);
  }
  fapi_fomus_run(f); // fomus destroys instance automatically
}

#endif
