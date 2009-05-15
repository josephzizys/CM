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

void initfomus();

class FomusScore
{
 private:
  FOMUS fom;
 public:
  String name, filename;

  FomusScore()
    {
      initfomus();
      fom = fomus_new();
      std::cout << fom << std::endl;
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
    wh_measattr,
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
      newScore();
      Console::getInstance()->printOutput("FOMUS " + String(fomus_version()) +
					  " (c) 2009 David Psenicka\n");
    }
  ~Fomus() 
    {
      scores.clear();
    }

  int numScores() {return scores.size();}
  String getScoreName(int i) {return scores[i]->name;}
  bool isScoreActive(int i) {return current==i;}
  void setScoreActive(int i) {current=i;}

  void initScore() {}
  void newScore();
  void deleteScore();
  void clearScore();
  void loadScore(String filename);
  void runScore();

  void sendXml(XmlElement& xml, fomus_param par, fomus_action act);
  void sendXml(const String& xml);
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

//#endif
