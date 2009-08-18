/*=======================================================================*
  Copyright (C) 2009 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

//#ifndef FOMUS_H
//#define FOMUS_H

#include <juce.h>
#include <map>
#include <fomus/fomusapi.h>
#include <iostream>
#include "Console.h"
#include "Syntax.h"

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
      fom = fomus_new();
      //std::cout << fom << std::endl;
    }
  
  ~FomusScore()
    {
      fomus_free(fom);
    }
  
  FOMUS getfom() const
  {
    return fom;
  }
};

enum whichstruct
  {
    wh_none,
    wh_measdef,
    wh_part,
    wh_metapart,
    wh_partsref,
    wh_inst,
    wh_percinst,
    wh_clef,
    wh_staff,
    wh_import,
    wh_export,
    wh_voices
  };

struct sendpair
{
  fomus_param par;
  fomus_action act;
  whichstruct wh;
  bool inlist;
  sendpair(fomus_param par, fomus_action act, whichstruct wh,
	   bool inlist = false)
  : par(par),
    act(act),
    wh(wh),
    inlist(inlist)
  {}
};

typedef std::map<String, sendpair> excmap;

class Fomus
{
 private:
  OwnedArray<FomusScore> scores;  
  int current;
  FOMUS getfomusdata() const
  {
    return scores.getUnchecked(current)->getfom();
  }


 public:

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
    str << T(" ") << String(fomus_version())
	<< T(" ") << SysInfo::getCopyright(T("David Psenicka"));
    return str;
  }
  bool openScore(String scorename, String scoreargs, const bool fromscm);
  void closeScore();
  void saveScore(const String& fn, const bool fromscm);

  int numScores() {return scores.size();}
  String getScoreName(int i) {return scores[i]->name;}
  bool isScoreActive(int i) {return current==i;}
  void setScoreActive(int i) {current=i;}

  void initScore() {}
  void newScore(const String& nam, const bool fromscm);
  void selectScore(const String& nam, const bool fromscm);
  void deleteScore();
  void clearScore();
  void loadScore(String filename);
  void runScore(const bool fromscm);

  void sendXml(XmlElement& xml, fomus_param par, fomus_action act);
  void sendXml(const String& xml, double scoretime=0.0);
  void sendXmlEntry(XmlElement& xml);
  void sendXmlSets(XmlElement& xml, fomus_param par, fomus_action act, const excmap& exc = excmap(),  bool islist = false);
  void sendXmlVal(XmlElement& xml, fomus_param par, fomus_action act, whichstruct wh, bool listof = false);
  
  void ival(fomus_param par, fomus_action act, fomus_int val);
  void rval(fomus_param par, fomus_action act, fomus_int num, fomus_int den);
  void mval(fomus_param par, fomus_action act, fomus_int val, fomus_int num, fomus_int den);
  void fval(fomus_param par, fomus_action act, double val);
  void sval(fomus_param par, fomus_action act, const String& val);
  void act(fomus_param par, fomus_action act);
  
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

  bool isTopLevel(String line);
  int getIndent (const String fomus, int bot, int top, int beg);
  HiliteID getHilite (const String fomus, int start, int end);
  void eval(String text, bool isRegion=false, bool expand=false);
  void stickkeyword(String str, const int hl);
  juce_DeclareSingleton(FomusSyntax, true)
};

//void fomusSaveAndRun();

//#endif
