/*=======================================================================*
  Copyright (C) 2009 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#include "Libraries.h"
#include "Console.h"
#include "Syntax.h"

extern bool fomus_exists;

bool check_fomus_exists();

typedef int (*fomus_err_type)();
typedef const char* (*fomus_version_type)();
typedef void (*fomus_init_type)();
typedef FOMUS (*fomus_new_type)();
typedef void (*fomus_free_type)(FOMUS f);
typedef void (*fomus_clear_type)(FOMUS f);
typedef void (*fomus_ival_type)(FOMUS f, int par, int act, fomus_int val);
typedef void (*fomus_rval_type)(FOMUS f, int par, int act, fomus_int num, fomus_int den);
typedef void (*fomus_fval_type)(FOMUS f, int par, int act, fomus_float val);
typedef void (*fomus_sval_type)(FOMUS f, int par, int act, const char* str);
typedef void (*fomus_act_type)(FOMUS f, int par, int act);
typedef void (*fomus_load_type)(FOMUS f, const char* filename);
typedef void (*fomus_parse_type)(FOMUS f, const char* input);
typedef void (*fomus_run_type)(FOMUS f);
typedef FOMUS (*fomus_copy_type)(FOMUS f);
typedef void (*fomus_save_type)(FOMUS f, const char* filename);
typedef void (*fomus_set_outputs_type)(fomus_output out, fomus_output err, int newline);
typedef fomus_int (*fomus_get_ival_type)(FOMUS f, const char* set);
typedef struct fomus_rat (*fomus_get_rval_type)(FOMUS f, const char* set);
typedef fomus_float (*fomus_get_fval_type)(FOMUS f, const char* set);
typedef const char* (*fomus_get_sval_type)(FOMUS f, const char* set);
typedef const struct info_extslist (*info_list_exts_type)();
typedef int (*info_infoapi_version_type)();
typedef int (*fomus_api_version_type)();
typedef int (*fomus_merge_type)(FOMUS to, FOMUS from);
#ifdef GRACE
typedef const struct info_modlist (*info_list_modules_type)(struct info_modfilterlist* filter, struct info_modsearch* sim, struct info_sortlist* sortlst, int limit);
typedef const struct info_setlist (*info_list_settings_type)(FOMUS fom, struct info_setfilterlist* filter, struct info_setsearch* sim, struct info_sortlist* sortlst, int limit);
typedef const struct info_marklist (*info_list_marks_type)(FOMUS fom, struct info_markfilterlist* filter, struct info_marksearch* sim, struct info_sortlist* sortlst, int limit);
typedef struct info_objinfo (*info_getlastentry_type)(FOMUS f);
typedef const struct info_objinfo_list (*info_list_percinsts_type)(FOMUS f);
typedef const struct info_objinfo_list (*info_list_insts_type)(FOMUS f);
typedef const struct info_objinfo_list (*info_list_parts_type)(FOMUS f);
typedef const struct info_objinfo_list (*info_list_metaparts_type)(FOMUS f);
typedef const struct info_objinfo_list (*info_list_measdefs_type)(FOMUS f);
typedef const char* (*settingloc_to_str_type)(enum module_setting_loc loc);
typedef const char* (*module_id_type)(module_obj obj);
typedef const char* (*modtype_to_str_type)(enum module_type type);
#endif

extern fomus_err_type fapi_fomus_err;
extern fomus_version_type fapi_fomus_version;
extern fomus_init_type fapi_fomus_init;
extern fomus_new_type fapi_fomus_new;
extern fomus_free_type fapi_fomus_free;
extern fomus_clear_type fapi_fomus_clear;
extern fomus_ival_type fapi_fomus_ival;
extern fomus_rval_type fapi_fomus_rval;
extern fomus_fval_type fapi_fomus_fval;
extern fomus_sval_type fapi_fomus_sval;
extern fomus_act_type fapi_fomus_act;
extern fomus_load_type fapi_fomus_load;
extern fomus_parse_type fapi_fomus_parse;
extern fomus_run_type fapi_fomus_run;
extern fomus_copy_type fapi_fomus_copy;
extern fomus_save_type fapi_fomus_save;
extern fomus_set_outputs_type fapi_fomus_set_outputs;
extern fomus_get_ival_type fapi_fomus_get_ival;
extern fomus_get_rval_type fapi_fomus_get_rval;
extern fomus_get_fval_type fapi_fomus_get_fval;
extern fomus_get_sval_type fapi_fomus_get_sval;
extern info_list_exts_type fapi_info_list_exts;
extern info_infoapi_version_type fapi_info_infoapi_version;
extern fomus_api_version_type fapi_fomus_api_version;
#ifdef GRACE
extern info_list_modules_type fapi_info_list_modules;
extern info_list_settings_type fapi_info_list_settings;
extern info_list_marks_type fapi_info_list_marks;
extern info_getlastentry_type fapi_info_getlastentry;
extern info_list_percinsts_type fapi_info_list_percinsts;
extern info_list_insts_type fapi_info_list_insts;
extern info_list_parts_type fapi_info_list_parts;
extern info_list_metaparts_type fapi_info_list_metaparts;
extern info_list_measdefs_type fapi_info_list_measdefs;
extern settingloc_to_str_type fapi_settingloc_to_str;
extern module_id_type fapi_module_id;
extern modtype_to_str_type fapi_modtype_to_str;
#endif

extern bool fomuserr;

void initfomus();

class FomusScore
{
 private:
  FOMUS fom;
 public:
  String name; //, filename; used?
  bool runwhendone;

  FomusScore()
    {
      initfomus();
      if (!check_fomus_exists()) {fom = 0; return;}
      fom = fapi_fomus_new();
    }
  
  ~FomusScore()
    {
      if (!check_fomus_exists()) return;
      fapi_fomus_free(fom);
    }
  
  FOMUS getfom() const
  {
    return fom;
  }
};

class Fomus
{
 private:
  OwnedArray<FomusScore> scores;  
  int current;


 public:

  FOMUS getfomusdata() const
  {
    return scores.getUnchecked(current)->getfom();
  }

 Fomus () : current(-1) 
    {
      newScore(T(""), false);
    }
  ~Fomus() 
    {
      scores.clear();
    }
  static const String getFomusVersion()
  {
    String str=T("FOMUS");
    str << T(" ") << String(fapi_fomus_version())
	<< T(" ") << SysInfo::getCopyright(T("David Psenicka"));
    return str;
  }
  bool openScore(String scorename, String scoreargs, const bool fromscm);
  void closeScore();
  void saveScore(const String& fn, const bool fromscm);
  void saveScoreAs(String filename);

  int numScores() {return scores.size();}
  String getScoreName(int i) {return scores[i]->name;}
  bool isScoreActive(int i) {return current==i;}
  void setScoreActive(int i) {current=i;}

  void initScore() {}
  void newScore(const String& nam, const bool fromscm);
  void selectScore(const String& nam, const bool fromscm);
  void mergeScore(const String& nam, fomus_int num, fomus_int den, fomus_float flt);
  void deleteScore();
  void clearScore(const bool all);
  void loadScore(String filename);
  void runScore(const bool fromscm);

  bool proctime(int act);
  void ival(int par, int act, fomus_int val);
  void rval(int par, int act, fomus_int num, fomus_int den);
  void fval(int par, int act, double val);
  void sval(int par, int act, const String& val);
  void act(int par, int act);

  void setrunwhendone(bool x) {scores.getUnchecked(current)->runwhendone = x;}
  
#ifdef GRACE
  void settingsWindow();
  void documentationWindow();
  void loadScoreDialog();
  void renameScoreDialog();
#endif
  
  juce_DeclareSingleton(Fomus, true)
};

class FomusSyntax : public Syntax
{
 public:
  FomusSyntax();
  ~FomusSyntax() ;
  // juce syntax tokens start at 0 or the defaults dont work
  enum fomustoks {
    TokenError,
    TokenPlaintext,
    TokenComment,
    TokenString,
    TokenKeyword,
    TokenSetting,
    TokenTimeKeyword,
    TokenPartKeyword
  };

  const StringArray getTokenTypes () ;
  const Colour getDefaultColour (int tokenType);
  int readNextToken (CodeDocument::Iterator &source);

  int getIndentation(CodeDocument& document, int line);
  int backwardExpr(CodeDocument& document, CodeDocument::Position& start, CodeDocument::Position& end);
  void eval(CodeDocument& document, const CodeDocument::Position start, const CodeDocument::Position end, bool expand, bool region);

  void stickkeyword(String str, const int hl);

  juce_DeclareSingleton(FomusSyntax, true)
};

