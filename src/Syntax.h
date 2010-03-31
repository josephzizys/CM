/*=======================================================================*
  Copyright (c) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify
  it under the terms of the Lisp Lesser Gnu Public License. The text
  of this agreement is available at http://www.cliki.net/LLGPL
 *=======================================================================*/

#ifndef SYNTAX_H
#define SYNTAX_H

#include <map>
//using namespace std;
#include "Scanner.h"
#include "Enumerations.h"

// Hilite IDs, one for each hilite. currently allow 8
// Emacs Hilite colors:
//   string: font-lock-string-case RosyBrown #bc8f8f 
//   comment: font-lock-comment-face firebrick  #b22222
//   keyword:  font-lock-builtin-face orchid #da70d6
//   special:  font-lock-keyword-face purple #a020f0
//   class: font-lock-type-case ForestGreen #228b22
//   command: font-lock-function-name-face blue1 #0000ff
//   constants: font-lock-constant-face CadetBlue #5f9ea0 

// SynTok holds info about distinguished tokens for each syntax

class SynTok 
{
 public:
  String name;       // string to match
  int type;          // token classification table (reverse mapping?)
  int data1;         // data fields (use is syntax specific)
  int data2;    
  int data3;

  SynTok(String n, int t, int d1=0, int d2=0, int d3=0) 
    : name(n), type(t), data1(d1), data2(d2), data3(d3) {}
  ~SynTok() {}
  String getName() {return name;}
  void setName(String n){name=n;}
  int getType() {return type;}
  void setType(int t) {type=t;}
  int getTypeData() {return (type & 0xff);}
  int getData1(){return data1;}
  int getData2(){return data2;}
  int getData3(){return data3;}
  HiliteID getHilite() {return (HiliteID)data1;}
  int getStart() {return data1;}
  int getIndent() {return data2;}
  int getLiteralClass() {return data3;}
  void print(bool lisp=true) ;
  const String toString()
  {
    String str=T("#<");
    str<<getName() << T(" 0x") << String::toHexString(getType()) << T(">");
    return str;
  }
};

typedef std::map <String, SynTok*> SynTokMap;

class Syntax : public CodeTokeniser
{
 public:
  SynTab syntab;
  Colour hilites[HiliteIDs::NUMHILITES];
  Colour colors[ColorThemeIDs::MAXTOKENCOLORS];
  SynTokMap tokens;
  int type;
  bool coloring;
  int tabwidth;
  int numtoks;
  int maxtoklen;
  Syntax(String a, String b, String c, String d, String e, String f, 
	 String g, String h, String i, String j) ;
  ~Syntax();
  int getType() {return type;}
  int getTabWidth(){return tabwidth;}
  void setTabWidth(int n);
  bool highlighting() {return coloring;}

  virtual bool isTopLevel(String line) =0;
  virtual int getIndent (const String text, int bot, int top, int beg) =0;
  virtual HiliteID getHilite (const String text, int start, int end) =0;
  virtual void eval(String text, bool isRegion=false, bool expand=false) =0;
  void addSynTok (const String n, int t, int a=0, int b=0, int c=0) ;
  SynTok* getSynTok (String n) ;
  bool isWhiteBetween (const String txt, int lb, int ub);
  Colour getHiliteColour(HiliteID id) {return hilites[id];}
};

/*=======================================================================*
                                  Text Syntax
 *=======================================================================*/

class TextSyntax : public Syntax
{
 public:
  TextSyntax();
  ~TextSyntax() ;

  static const int TokenError = 0;
  static const int TokenPlaintext = 1;

  bool isTopLevel(String line) ;
  int getIndent (const String text, int bot, int top, int beg) ;
  HiliteID getHilite (const String text, int start, int end) ;
  void eval(String text, bool isRegion=false, bool expand=false) {}

  const StringArray getTokenTypes ();
  const Colour getDefaultColour (const int tokenType);
  int readNextToken (CodeDocument::Iterator &source);

  juce_DeclareSingleton (TextSyntax, true)
};

/*=======================================================================*
                                  Lisp Syntax
 *=======================================================================*/

class LispSyntax : public Syntax
{
 public:
  LispSyntax();
  ~LispSyntax() ;
  // juce syntax tokens start at 0 or the defaults dont work
  static const int TokenError = 0;
  static const int TokenPlaintext = 1;
  static const int TokenComment = 2;
  static const int TokenString = 3;
  static const int TokenSharpsign = 4;
  static const int TokenLispKeyword = 5;
  static const int TokenLispSpecialForm = 6;

  bool isTopLevel(String line) ;
  int getIndent (const String text, int bot, int top, int beg) ;
  HiliteID getHilite (const String text, int start, int end) ;
  void eval(String text, bool isRegion=false, bool expand=false) ;

  const StringArray getTokenTypes ();
  const Colour getDefaultColour (const int tokenType);
  int readNextToken (CodeDocument::Iterator &source);

  juce_DeclareSingleton (LispSyntax, true)
};

/*=======================================================================*
                                  SAL Syntax
 *=======================================================================*/

class SalSyntax : public Syntax
{
 public:

  SalSyntax(bool fill=true);
  ~SalSyntax() ;

  const StringArray getTokenTypes ();
  const Colour getDefaultColour (const int tokenType);
  int readNextToken (CodeDocument::Iterator &source);

  bool isTopLevel(String line) ;
  int getIndent (const String text, int bot, int top, int beg) ;
  int isSalStatement(const String str);
  int backwardSal(const String text, int bot, int top, int *poz, int *sal);
  HiliteID getHilite (const String text, int start, int end) ;
  void eval(String text, bool isRegion=false, bool expand=false) ;

  String getSymbolHelp(int type);

  // SAL lexer
  String tokenize(String str);
  bool tokenize(String str, OwnedArray<SynTok>& toks);

  void salError(String str, int err, SynTok *tok);
  SynTok *findUnbalanced(OwnedArray<SynTok> &tokens, int target, int other, int level);
  SynTok *findUnbalancedBlock(OwnedArray<SynTok> &tokens, int level);
  int classifyToken(String str, SynTok *tok);
  int isLiteralToken(String str, SynTok *tok);
  int isSpecialToken(String str, SynTok *tok);
  int isNumberToken(String str, SynTok *tok);
  int isClassToken(String str, SynTok *tok);
  int isSlotToken(String str, SynTok *tok);
  int isIdentifierToken(String str, SynTok *tok);

  juce_DeclareSingleton (SalSyntax, true)
};

/*=======================================================================*
                                  SAL2 Syntax
 *=======================================================================*/

class Sal2Syntax : public Syntax
{
 private:
  enum 
  {
    tt_error, tt_comment, tt_string, tt_parentheses, tt_punctuation,
    tt_sharpsign, tt_literal, tt_keyword1, tt_keyword2, tt_token
  };

 public:
  Sal2Syntax();
  ~Sal2Syntax();

  const StringArray getTokenTypes ();
  const Colour getDefaultColour (const int tokenType);
  int readNextToken (CodeDocument::Iterator &source);

  bool isTopLevel(String line) {return true;}
  int getIndent (const String text, int bot, int top, int beg) {return 0;}
  HiliteID getHilite (const String text, int start, int end) {return HiliteIDs::None;}
  void eval(String text, bool isRegion=false, bool expand=false){}
  String tokenize(String str) {return String::empty;}
  bool tokenize(String str, OwnedArray<SynTok>& toks) {return false;}

  juce_DeclareSingleton (Sal2Syntax, true)
};

#endif
