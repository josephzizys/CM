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
  syntaxNone = 0,
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
  int type;          // token classification table (reverse mapping?)
  int data1;         // data fields (use is syntax specific)
  int data2;    
  int data3;

  SynTok(String n, int t, int d1=0, int d2=0, int d3=0) {
    name=n;
    type=t;
    data1=d1;
    data2=d2;
    data3=d3;
  }
  ~SynTok() {}
  String getName() {return name;}
  void setName(String n){name=n;}
  int getType() {return type;}
  void setType(int t) {type=t;}
  hiliteID getHilite() {return (hiliteID)data1;}
  int getStart() {return data1;}
  int getIndent() {return data2;}
  int getLiteralClass() {return data3;}
  void trace() {
    if (type==0) printf("<? %s> ",name.toUTF8());
    else printf("<%s> ",name.toUTF8());
  }
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

class SalSyntax : public Syntax
{
 public:
  enum SalLiteralType {
    SalStatement = 1,      // #b001
    SalClausal = 2,        // #b010
    SalCommand = 5};       // #b101  -- command is also statement

  enum SalErrors {
    SalUnknown = -100,  // allow room for scan errors
    SalBadIdentifier,
    SalBadSlot,
    SalBadClass,
    SalBadNumber,
    SalBadSpecial
  };

  enum SalTokType {
    SalUntyped = 0,
    // Delimiters
    SalComma = 100,
    SalLParen,
    SalRParen,
    SalLCurly,
    SalRCurly,
    SalLBrace,
    SalRBrace,
    // String
    SalString = 200,
    // Numbers
    SalInteger = 300,
    SalRatio,
    SalFloat,
    // Operators... (data: weight)
    SalPlus = 400,
    SalMinus,
    SalTimes,
    SalDivide,
    SalMod,
    SalExpt,
    // ...relations
    SalEqual = 425,
    SalNotEqual,
    SalLess,
    SalGreater,
    SalLessEqual,  
    SalGreaterEqual,  
    SalGeneralEqual,
    // ...logic
    SalAnd = 450,
    SalOr,
    SalNot,
    // ...assignment
    SalInc = 475,
    SalMul,
    SalCol,
    SalPre,
    SalApp,
    // Keywords
    SalKeyparam = 500,
    SalKeyword ,
    // Classes
    SalClass = 600,
    SalSlotRef,
    // Special (hash) Notations
    SalTrue = 700,
    SalFalse,
    SalQMark,
    // Literals... (data: statement=001, clausal=10, command=101)
    SalBegin = 800,
    SalChdir,
    SalDefine,
    SalExec, 
    SalIf,
    SalLoad,
    SalLoop,
    SalOpen,
    SalOutput,
    SalPlay,
    SalPlot,
    SalPrint, 
    SalReturn,
    SalRun,
    SalSet,
    SalSprout,
    SalSystem,
    // ...clausals
    SalAbove,
    SalBelow,
    SalBy,
    SalDownto,
    SalElse,
    SalEnd,
    SalFinally,
    SalFor,
    SalFrom,
    SalIn,
    SalOver,
    SalRepeat,
    SalTo,
    SalThen, 
    SalUnless,
    SalUntil,
    SalWait,
    SalWhen,
    SalWhile, 
    SalWith,
    // ...define types
    SalFunction,
    SalProcess,
    SalVariable,
    // Indetifiers
    SalIdentifier = 1000
  };

  SalSyntax();
  ~SalSyntax() {};
  void initSalToks();
  bool isTopLevel(String line) ;
  SynTok* getSynTok (String n) ;
  int getIndent (const String text, int bot, int top, int beg) ;
  int isSalStatement(const String str);
  int backwardSal(const String text, int bot, int top, int *poz, int *sal);
  hiliteID getHilite (const String text, int start, int end) ;
  void tokenize(String str);
};

#endif



