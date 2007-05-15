/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

#ifndef __SYNTAX__
#define __SYNTAX__
#include <map>
using namespace std;
#include "Syntab.h"

// Syntax IDs, one for each syntax. 

enum syntaxID {
  syntaxNone = -1,
  syntaxConsole,
  syntaxText,
  syntaxLisp,
  syntaxSal
  };

// Hilite IDs, one for each hilite. currently allow 8

#define MAXHILITE 8

enum hiliteID {
  hiliteNone = 0,
  hiliteString,
  hiliteComment,
  hilite4,
  hilite5,
  hilite6,
  hilite7,
  hilite8
};

// Emacs Hilite colors (SAL):
// string: font-lock-string-case RosyBrown #bc8f8f 
// comment: font-lock-comment-face firebrick  #b22222
// keyword:  font-lock-builtin-face orchid #da70d6
// special:  font-lock-keyword-face purple #a020f0
// class: font-lock-type-case ForestGreen #228b22
// command: font-lock-function-name-face blue1 #0000ff
// #constants: font-lock-constant-face CadetBlue #5f9ea0 


// SynTok holds info about distinguished tokens for each syntax

class SynTok {
 public:
  String name;       // string to match
  int id;            // unique id in table (reverse mapping?)
  hiliteID hilite;   // hilite id for token
  int indent;        // indentation value (syntax specific)
  int toktype;       // token classification (syntax specific)

  SynTok(String n, int a, hiliteID b, int c, int d) {
    name=n;
    id=a;
    hilite=b;
    indent=c;
    toktype=d;
  }
  ~SynTok() {}

  void tyo() {
    printf("#<SynTok \"%s\",%d,%d,%d,%d>\n",
	   name.toUTF8(),id,hilite,indent,toktype);
  };

};

typedef std::map <String, SynTok*> SynTokMap;

class Syntax 
{
 public:
  SynTab syntab;
  Colour hilites[MAXHILITE];
  Syntax(String a, String b, String c, String d, String e, String f, 
	 String g, String h, String i, String j);
  ~Syntax() {};
  virtual bool isTopLevel(String line) =0;
  //  virtual void initSynToks() =0;
  //  virtual void addSynTok(const String n, int a, hiliteID b, int c, int d) =0;
  virtual SynTok* getSynTok (String n) =0;
  virtual int getIndent (const String text, int bot, int top, int beg) =0;
  virtual hiliteID getHilite (const String text, int start, int end) =0;

  bool isWhiteBetween (const String txt, int lb, int ub);
  Colour getHiliteColour(hiliteID id) {return hilites[id];}
};

class TextSyntax : public Syntax
{
 public:
  TextSyntax();
  ~TextSyntax() {};
  bool isTopLevel(String line) ;
  SynTok* getSynTok (String n);
  int getIndent (const String text, int bot, int top, int beg) ;
  hiliteID getHilite (const String text, int start, int end) ;
};

class LispSyntax : public Syntax
{
 public:
  LispSyntax();
  ~LispSyntax() {};
  bool isTopLevel(String line) ;
  SynTok* getSynTok (String n) ;
  int getIndent (const String text, int bot, int top, int beg) ;
  hiliteID getHilite (const String text, int start, int end) ;
};

enum salID {salBegin = 1, salChdir, salDefine, salElse, salEnd, salExec, 
	    salFunction, salIf, salLoad, salLoop, salOpen, salOutput,
	    salPlay, salPlot, salPrint, salProcess, salReturn, salRts, 
	    salRun, salSet, salSprout, salSystem, salThen, salUnless,
	    salUntil, salVariable, salWait, salWhen, salWhile, salWith};

enum salTyp {salCommand = 1,  // is toplevel command
	     salClausal,      // is part of command
	     salReserved};    // is (non-command) reserved word

class SalSyntax : public Syntax
{
 public:

  SalSyntax();
  ~SalSyntax() {};
  bool isTopLevel(String line) ;
  SynTok* getSynTok (String n) ;
  int getIndent (const String text, int bot, int top, int beg) ;
  int isSalStatement(const String str);
  int backwardSal(const String text, int bot, int top, int *poz, int *sal);
  hiliteID getHilite (const String text, int start, int end) ;
};

#endif



