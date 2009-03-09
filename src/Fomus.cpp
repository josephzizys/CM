/*=======================================================================*
  Copyright (C) 2009 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#include "Enumerations.h"
#include "Fomus.h"
#include "Console.h"

// FIXME: TEMP STUBS 

FomusScore* fomus_new() {return new FomusScore();}
void fomus_init() {};
void fomus_free(FomusScore* ptr) {delete ptr;}
void fomus_clear(void* ptr) {}
void fomus_ival(void* ptr, int par, int act, int val) {}
void fomus_rval(void* ptr, int par, int act, int num, int den) {}
void fomus_mval(void* ptr, int par, int act, int val, int num, int den) {}
void fomus_fval(void* ptr, int par, int act, double val) {}
void fomus_sval(void* ptr, int par, int act, char* val) {}
void fomus_act(void* ptr, int par, int act) {}
void fomus_run(void* ptr) {}
void fomus_load(void* ptr, char* filename) {}

/*=======================================================================*
                             Fomus Instance
 *=======================================================================*/

juce_ImplementSingleton(Fomus);

Fomus::Fomus () 
  : current (-1)
{
  // always insist on one score
  newScore();
}

Fomus::~Fomus ()
{
  scores.clear();
}

int Fomus::numScores()
{
  return scores.size();
}

String Fomus::getScoreName(int i)
{
  return scores[i]->name;
}

bool Fomus::isScoreActive(int i)
{
  return current==i;
}

void Fomus::setScoreActive(int i)
{
  current=i;
}

void Fomus::initScore()
{
  fomus_init();
}

void Fomus::newScore()
{
  FomusScore* score=fomus_new();
  score->name=T("Untitled");
  if (scores.size()>0)
    score->name << T("-") << String(scores.size()+1);
  scores.add(score);
  current=scores.size()-1;
}

void Fomus::deleteScore()
{
  // insist on at least one score
  if (scores.size()>0)
    {
      FomusScore* fms=scores[current];
      scores.removeObject(fms, false);
      fomus_free(fms);
      current=scores.size()-1;
    }
}

void Fomus::clearScore()
{
  fomus_clear(scores[current]);
}

void Fomus::loadScore(String filename)
{
  fomus_load(scores.getUnchecked(current), (char*)filename.toUTF8());  
}

void Fomus::runScore()
{
  fomus_run(scores.getUnchecked(current));  
}

void Fomus::ival(int par, int act, int val)
{
  fomus_ival(scores.getUnchecked(current), par, act, val);
}

void Fomus::rval(int par, int act, int num, int den)
{
  fomus_rval(scores.getUnchecked(current), par, act, num, den);
}

void Fomus::mval(int par, int act, int val, int num, int den)
{
  fomus_mval(scores.getUnchecked(current), par, act, val, num, den);
}

void Fomus::fval(int par, int act, double val)
{
  fomus_fval(scores.getUnchecked(current), par, act, val);
}

void Fomus::sval(int par, int act, String val)
{
  fomus_sval(scores.getUnchecked(current), par, act, (char*)val.toUTF8());
}

void Fomus::act(int par, int act)
{
  fomus_act(scores.getUnchecked(current), par, act);
}

void Fomus::sendXml(String xml)
{
  Console::getInstance()->printOutput(xml + T("\n"));
}

void Fomus::sendXml(XmlElement& xml, int lev)
{
  /**
  String trace=String::empty;
  for (int i=0; i< lev; i++) trace<<T(" ");

  // top-level enties <fms:note> , <fms:rest> etc
  if (xml.hasTagName(T("fms:note")))
    {
      Console::getInstance()->printOutput(trace+xml.getTagName()+T("\n"));
      forEachXmlChildElement (xml, e)
	sendXml(*e, lev+1);
    }
  else if (xml.hasTagName(T("fms:mark")))
    {
      Console::getInstance()->printOutput(trace+xml.getTagName()+T("\n"));
      forEachXmlChildElement (xml, e)
	sendXml(*e, lev+1);
    }
  else if (xml.hasTagName(T("fms:rest")))
    {
      Console::getInstance()->printOutput(trace+xml.getTagName()+T("\n"));
      forEachXmlChildElement (xml, e)
	sendXml(*e, lev+1);
    }
  else if (xml.hasTagName(T("fms:part")))
    {
      Console::getInstance()->printOutput(trace+xml.getTagName()+T("\n"));
      forEachXmlChildElement (xml, e)
	sendXml(*e, lev+1);
    }
  else if (xml.hasTagName(T("fms:meas")))
    {
      Console::getInstance()->printOutput(trace+xml.getTagName()+T("\n"));
      forEachXmlChildElement (xml, e)
	sendXml(*e, lev+1);
    }
  else if (xml.hasTagName(T("fms:inst")))
    {
      Console::getInstance()->printOutput(trace+xml.getTagName()+T("\n"));
      forEachXmlChildElement (xml, e)
	sendXml(*e, lev+1);
    }
  else if (xml.hasTagName(T("fms:percinst")))
    {
      Console::getInstance()->printOutput(trace+xml.getTagName()+T("\n"));
      forEachXmlChildElement (xml, e)
	sendXml(*e, lev+1);
    }
  else if (xml.hasTagName(T("fms:setting")))
    {
      Console::getInstance()->printOutput(trace+xml.getTagName()+T("\n"));
      forEachXmlChildElement (xml, e)
	sendXml(*e, lev+1);
    }
  // sub-elements that are lists
  else if (xml.hasTagName(T("marks")))
    {
      forEachXmlChildElement(xml, e)
	sendXml(*e, lev+1);
    }
  else if (xml.hasTagName(T("voices")))
    {
      forEachXmlChildElement(xml, e)
	sendXml(*e, lev+1);
    }
  else if (xml.hasTagName(T("settings")))
    {
      forEachXmlChildElement(xml, e)
	sendXml(*e, lev+1);
    }
  // sub-elements (lev>0)
  else if (xml.hasTagName(T("time")))
    {
      trace<<xml.getTagName()<< T("=")<<xml.getAllSubText()<<T("\n");
      Console::getInstance()->printOutput(trace);
    }
  else if (xml.hasTagName(T("dur")))
    {
      trace<<xml.getTagName()<< T("=")<<xml.getAllSubText()<<T("\n");
      Console::getInstance()->printOutput(trace);
    }
  else if (xml.hasTagName(T("dyn")))
    {
      trace<<xml.getTagName()<< T("=")<<xml.getAllSubText()<<T("\n");
      Console::getInstance()->printOutput(trace);
    }
  else if (xml.hasTagName(T("mark")) ) // top-level mark
    {
      trace<<xml.getTagName()<< T("=")<<xml.getAllSubText()<<T("\n");
      Console::getInstance()->printOutput(trace);
    }
  else if (xml.hasTagName(T("voice")))
    {
      trace<<xml.getTagName()<< T("=")<<xml.getAllSubText()<<T("\n");
      Console::getInstance()->printOutput(trace);
    }
  else if (xml.hasTagName(T("setting")))
    {
      trace<<xml.getTagName()<< T("=")<<xml.getAllSubText()<<T("\n");
      Console::getInstance()->printOutput(trace);
    }
  **/
}


/*=======================================================================*
  Remainder of file is Grace GUI code, not part of the console CM app
 *=======================================================================*/

#ifdef GRACE


void Fomus::settingsWindow()
{
  AlertWindow::showMessageBox(AlertWindow::InfoIcon, T("Fomus Settings"),
			      T("FIXME: Fomus settings dialog."));
}

void Fomus::documentationWindow()
{
  AlertWindow::showMessageBox(AlertWindow::InfoIcon, T("Fomus Documentation"),
			      T("FIXME: Fomus documentation dialog."));
}

void Fomus::loadScoreDialog()
{
  AlertWindow::showMessageBox(AlertWindow::InfoIcon, T("Load Score"),
			      T("FIXME: Load SCore."));
}

void Fomus::renameScoreDialog()
{
  AlertWindow::showMessageBox(AlertWindow::InfoIcon, T("Rename Score"),
			      T("FIXME: Rename."));
}



#endif
