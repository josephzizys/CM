/*=======================================================================*
  Copyright (C) 2009 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#include <juce.h>


// STUB FOMUS SCORE OBJECT

class FomusScore
{
 public:
  String name, filename;
  FomusScore() {}
  ~FomusScore() {}
};

class Fomus
{

 private:
  OwnedArray<FomusScore> scores;  
  int current;
 public:

  Fomus();
  ~Fomus();

  int numScores();
  String getScoreName(int i);
  bool isScoreActive(int i);
  void setScoreActive(int i);

  void initScore();
  void newScore();
  void deleteScore();
  void clearScore();
  void loadScore(String filename);
  void runScore();

  void sendXml(XmlElement& xml, int level=0);
  void sendXml(String xml);

  void ival(int par, int act, int val);
  void rval(int par, int act, int num, int den);
  void mval(int par, int act, int val, int num, int den);
  void fval(int par, int act, double val);
  void sval(int par, int act, String val);
  void act(int par, int act);

  void settingsWindow();
  void documentationWindow();
  void loadScoreDialog();
  void renameScoreDialog();

  juce_DeclareSingleton(Fomus, true)
};
