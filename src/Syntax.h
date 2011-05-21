/*=======================================================================*
  Copyright (c) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify
  it under the terms of the Lisp Lesser Gnu Public License. The text
  of this agreement is available at http://www.cliki.net/LLGPL
 *=======================================================================*/

#ifndef SYNTAX_H
#define SYNTAX_H

#include "Libraries.h"
#include "Enumerations.h"


class Syntax : public CodeTokeniser
{
 public:

  // SynToks hold info about distinguished tokens in each syntax

  class SynTok 
  {
   public:
    SynTok(String n, int t, int d1=0, int d2=0, int d3=0) 
      : name(n), type(t), data1(d1), data2(d2), data3(d3) 
    {
    }
    ~SynTok() {}
    String getName() {return name;}
    void setName(String n) {name=n;}
    int getType() {return type;}
    void setType(int t) {type=t;}
    int getTypeData() {return (type & 0xff);}
    int getData1() {return data1;}
    int getData2() {return data2;}
    int getData3() {return data3;}
    int getStart() {return data1;}
    int getIndent() {return data2;}
    int getLiteralClass() {return data3;}
    const String toString()
    {
      String str=T("#<");
      str<<getName() << T(" 0x") << String::toHexString(getType()) << T(">");
      return str;
    }
   private:
    String name;       // string to match
    int type;          // token classification table (reverse mapping?)
    int data1;         // data fields (use is syntax specific)
    int data2;    
    int data3;
  };

  typedef std::map <String, SynTok*> SynTokMap;

  Syntax() ;
  ~Syntax();
  int getTextType() {return type;}
  void addSynTok (const String n, int t, int a=0, int b=0, int c=0) ;
  SynTok* getSynTok (String n) ;

  void setCharSyntax(const String chrs, const int syn);
  bool isWhiteChar (const tchar c) ;
  bool isWordChar (const tchar c) ;
  bool isSymbolChar (const tchar c) ;
  bool isTokenChar (const tchar c) ;
  bool isCommentChar (const tchar c) ;
  bool isPrefixChar (const tchar c) ;
  bool isStringChar (const tchar c) ;
  bool isOpenChar (const tchar c) ;
  bool isCloseChar (const tchar c) ;
  bool isPunctuationChar (const tchar c) ;
  bool isEscapeChar (const tchar c) ;
  int  isNumberToken(const String str) ;

  bool scanToken(CodeDocument::Position& pos, const int dir, const CodeDocument::Position end);
  bool scanCharacter(tchar chr, CodeDocument::Position& pos, const int dir, const CodeDocument::Position end);
  bool scanPrefix(CodeDocument::Position& pos, const int dir, const CodeDocument::Position end);
  int  scanCode(CodeDocument& document, CodeDocument::Position& pos, bool forward, int mode, int limit=-1);
  int  lastIndented(CodeDocument& document, Array<int>& starts, bool index);
  bool lookingAt(const CodeDocument::Position pos, const String text, const bool forward, const bool delimited);
  bool isCommaTerminatedLine(CodeDocument& document, int line);
  
  virtual int getIndentation(CodeDocument& document, int line) =0;
  virtual int backwardExpr(CodeDocument& document, CodeDocument::Position& start, CodeDocument::Position& end) =0;
  virtual void eval(CodeDocument& document, const CodeDocument::Position start, const CodeDocument::Position end, bool expand, bool region) =0;

 protected:
  char syntab [128];
  Colour colors[ColorThemeIDs::MAXTOKENCOLORS];
  SynTokMap tokens;
  int type;
  int numtoks;
  int maxtoklen;
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

  const StringArray getTokenTypes ();
  const Colour getDefaultColour ( int tokenType);
  int readNextToken (CodeDocument::Iterator &source);

  int getIndentation(CodeDocument& document, int line);
  int backwardExpr(CodeDocument& document, CodeDocument::Position& start, CodeDocument::Position& end);
  void eval(CodeDocument& document, const CodeDocument::Position start, const CodeDocument::Position end, bool expand, bool region);

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

  const StringArray getTokenTypes ();
  const Colour getDefaultColour ( int tokenType);
  int readNextToken (CodeDocument::Iterator &source);

  int getIndentation(CodeDocument& document, int line) ;
  int backwardExpr(CodeDocument& document, CodeDocument::Position& start, CodeDocument::Position& end); 
  void eval(CodeDocument& document, const CodeDocument::Position start, const CodeDocument::Position end, bool expand, bool region);
  
  juce_DeclareSingleton (LispSyntax, true)
};

/*=======================================================================*
                                  SAL Syntax
 *=======================================================================*/

class SalSyntax : public Syntax
{
 private:
  String errormessage;
 public:

  SalSyntax(bool init=true);
  ~SalSyntax();
  void init();
  const StringArray getTokenTypes ();
  const Colour getDefaultColour ( int tokenType);
  int readNextToken (CodeDocument::Iterator &source);

  int getIndentation(CodeDocument& document, int line) ;
  int backwardExpr(CodeDocument& document, CodeDocument::Position& start, CodeDocument::Position& end); 
  void eval(CodeDocument& document, const CodeDocument::Position start, const CodeDocument::Position end, bool expand, bool region);

  // SAL/SAL2 lexer
  bool tokenize(String str, OwnedArray<SynTok>& toks);
  bool tokenize(CodeDocument& document, const CodeDocument::Position start, const CodeDocument::Position end,
                OwnedArray<SynTok>& tokens);
  const String& getLastParseError();
  juce_DeclareSingleton (SalSyntax, true)
};

/*=======================================================================*
                                  SAL2 Syntax
 *=======================================================================*/

class Sal2Syntax : public SalSyntax
{
 private:

 public:
  Sal2Syntax();
  ~Sal2Syntax();

  const StringArray getTokenTypes ();
  const Colour getDefaultColour ( int tokenType);
  int readNextToken (CodeDocument::Iterator &source);

  //  String tokenize(String str) {return String::empty;}
  //  bool tokenize(String str, OwnedArray<SynTok>& toks) {return false;}

  int backwardExpr(CodeDocument& document, CodeDocument::Position& start, CodeDocument::Position& end); 

  juce_DeclareSingleton (Sal2Syntax, true)
};

#endif
