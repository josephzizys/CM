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
  int getTypeData() {return (type & 0xff);}
  void setType(int t) {type=t;}
  HiliteID getHilite() {return (HiliteID)data1;}
  int getStart() {return data1;}
  int getIndent() {return data2;}
  int getLiteralClass() {return data3;}
  void print(bool lisp=true) ;
};

typedef std::map <String, SynTok*> SynTokMap;

class Syntax 
{
 public:
  SynTab syntab;
  Colour hilites[HiliteIDs::NUMHILITES];
  SynTokMap tokens;
  int type;
  bool coloring;
  int tabwidth;
  int numtoks;

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
  SynTok * getSynTok (String n) ;
  bool isWhiteBetween (const String txt, int lb, int ub);
  Colour getHiliteColour(HiliteID id) {return hilites[id];}

};

/************************************************************************
 * Text Syntax                                                          *
 ************************************************************************/

class TextSyntax : public Syntax
{
 public:
  TextSyntax();
  ~TextSyntax() ;

  bool isTopLevel(String line) ;
  int getIndent (const String text, int bot, int top, int beg) ;
  HiliteID getHilite (const String text, int start, int end) ;
  void eval(String text, bool isRegion=false, bool expand=false) {}
  juce_DeclareSingleton (TextSyntax, true)
};

/************************************************************************
 * Lisp Syntax                                                          *
 ************************************************************************/

class LispSyntax : public Syntax
{
 public:
  LispSyntax();
  ~LispSyntax() ;
  void addLispTok(const String n, int t, HiliteID h, int i) ;

  bool isTopLevel(String line) ;
  int getIndent (const String text, int bot, int top, int beg) ;
  HiliteID getHilite (const String text, int start, int end) ;
  void eval(String text, bool isRegion=false, bool expand=false) ;
  juce_DeclareSingleton (LispSyntax, true)
};

/************************************************************************
 * SAL Syntax                                                           *
 ************************************************************************/

class SalSyntax : public Syntax
{
 public:

  enum SalErrors {
    SalUnknown = -100,  // allow room for scan errors
    MissingEnd,
    UnmatchedEnd,
    SalBadIdentifier,
    SalBadSlot,
    SalBadClass,
    SalBadNumber,
    SalBadSpecial
  };

  // Sal Types, lower 8 bits reserved for associating data
  // with the type, ie operator weight 1-7 for Sal operators,
  // Open/Close tags on literals begin|loop|run ... end etc.
  enum SalTypeData {
    // 1-7 are operator weights
    SalBlockOpen=16,
    SalBlockClose};

  enum SalTypes {
    // generated by (sal-enums )
    SalUntyped = 0x0,
    SAL_TOKEN_BEG = 0x0,
    SAL_DELIM_BEG = 0x0,
    SalComma = 0x100,
    SalLParen = 0x200,
    SalRParen = 0x300,
    SalLCurly = 0x400,
    SalRCurly = 0x500,
    SalLBrace = 0x600,
    SalRBrace = 0x700,
    SAL_DELIM_END = 0x800,
    SAL_DATA_BEG = 0x800,
    SalString = 0x900,
    SAL_NUMBER_BEG = 0xa00,
    SalInteger = 0xb00,
    SalRatio = 0xc00,
    SalFloat = 0xd00,
    SAL_NUMBER_END = 0xe00,
    SalKeyword = 0xf00,
    SAL_BOOL_BEG = 0x1000,
    SAL_HASH_BEG = 0x1000,
    SalTrue = 0x1100,
    SalFalse = 0x1200,
    SAL_BOOL_END = 0x1300,
    SalQMark = 0x1400,
    SalUnquote = 0x1500,
    SalSplice = 0x1600,
    SAL_HASH_END = 0x1700,
    SAL_DATA_END = 0x1700,
    SalKeyparam = 0x1800,
    SalClass = 0x1900,
    SAL_OP_BEG = 0x1a00,
    SalPlus = 0x1b05,
    SalMinus = 0x1c05,
    SalTimes = 0x1d06,
    SalDivide = 0x1e06,
    SalMod = 0x1f05,
    SalExpt = 0x2007,
    SalAnd = 0x2102,
    SalOr = 0x2201,
    SalNot = 0x2303,
    SAL_RELATION_BEG = 0x2400,
    SalLess = 0x2504,
    SalGreater = 0x2604,
    SalNotEqual = 0x2704,
    SalGeneralEqual = 0x2804,
    SAL_ASSIGNMENT_BEG = 0x2900,
    SalEqual = 0x2a04,
    SalLessEqual = 0x2b04,
    SalGreaterEqual = 0x2c04,
    SAL_RELATION_END = 0x2d00,
    SAL_OP_END = 0x2d00,
    SalInc = 0x2e00,
    SalMul = 0x2f00,
    SalCol = 0x3000,
    SalPre = 0x3100,
    SalApp = 0x3200,
    SAL_ASSIGNMENT_END = 0x3300,
    SAL_LITERAL_BEG = 0x3300,
    SAL_STATEMENT_BEG = 0x3300,
    SAL_COMMAND_BEG = 0x3300,
    SalBegin = 0x3410,
    SalChdir = 0x3500,
    SalDefine = 0x3600,
    SalExec = 0x3700,
    SalIf = 0x3800,
    SalLoad = 0x3900,
    SalLoop = 0x3a10,
    SalOpen = 0x3b00,
    SalPlay = 0x3c00,
    SalPlot = 0x3d00,
    SalPlotHook = 0x3e00,
    SalPrint = 0x3f00,
    SalRun = 0x4010,
    SalSend = 0x4100,
    SalSet = 0x4200,
    SalSprout = 0x4300,
    SalSystem = 0x4400,
    SalUse = 0x4500,
    SAL_COMMAND_END = 0x4600,
    SAL_CONSTITUENT_BEG = 0x4600,
    SalElse = 0x4700,
    SalEnd = 0x4811,
    SalOutput = 0x4900,
    SalReturn = 0x4a00,
    SalThen = 0x4b00,
    SalUnless = 0x4c00,
    SalUntil = 0x4d00,
    SalWait = 0x4e00,
    SalWhen = 0x4f00,
    SalWhile = 0x5000,
    SalWith = 0x5100,
    SAL_CONSTITUENT_END = 0x5200,
    SAL_STATEMENT_END = 0x5200,
    SAL_CLAUSAL_BEG = 0x5200,
    SalAbove = 0x5300,
    SalBelow = 0x5400,
    SalBy = 0x5500,
    SalDownto = 0x5600,
    SalFinally = 0x5700,
    SalFor = 0x5800,
    SalFrom = 0x5900,
    SalIn = 0x5a00,
    SalOver = 0x5b00,
    SalRepeat = 0x5c00,
    SalTo = 0x5d00,
    SAL_CLAUSAL_END = 0x5e00,
    SAL_LITERAL_END = 0x5e00,
    SAL_DEFINE_BEG = 0x5e00,
    SalFunction = 0x5f00,
    SalProcess = 0x6000,
    SalVariable = 0x6100,
    SAL_DEFINE_END = 0x6200,
    SAL_IDENTIFIER_BEG = 0x6200,
    SalIdentifier = 0x6300,
    SalSlotRef = 0x6400,
    SAL_IDENTIFIER_END = 0x6500,
    SAL_TOKEN_END = 0x6500,
    SAL_RULE_BEG = 0x6500,
    SalNumberRule = 0x6600,
    SalBoolRule = 0x6700,
    SalAtomRule = 0x6800,
    SalListRule = 0x6900,
    SalEltRule = 0x6a00,
    SalArefRule = 0x6b00,
    SalIfExprRule = 0x6c00,
    SalUnquoteRule = 0x6d00,
    SalFuncallRule = 0x6e00,
    SalFunargsRule = 0x6f00,
    SalPargsRule = 0x7000,
    SalKargsRule = 0x7100,
    SalOpRule = 0x7200,
    SalMexprRule = 0x7300,
    SalTermRule = 0x7400,
    SalSexprRule = 0x7500,
    SalBindingsRule = 0x7600,
    SalBindRule = 0x7700,
    SalAssignmentRule = 0x7800,
    SalAssignRule = 0x7900,
    SalAssignerRule = 0x7a00,
    SalSetRule = 0x7b00,
    SalFunctionReturnRule = 0x7c00,
    SalProcessWaitRule = 0x7d00,
    SalBlockRule = 0x7e00,
    SalConditionalRule = 0x7f00,
    SalLoopStatementRule = 0x8000,
    SalRunStatementRule = 0x8100,
    SalSteppingRule = 0x8200,
    SalTerminationRule = 0x8300,
    SalPrintStatementRule = 0x8400,
    SalExecStatementRule = 0x8500,
    SalOpenStatementRule = 0x8600,
    SalSendStatementRule = 0x8700,
    SalSproutStatementRule = 0x8800,
    SalOutputStatementRule = 0x8900,
    SalLoadStatementRule = 0x8a00,
    SalSystemStatementRule = 0x8b00,
    SalChdirStatementRule = 0x8c00,
    SalPlayStatementRule = 0x8d00,
    SalPlotStatementRule = 0x8e00,
    SalPlotHookStatementRule = 0x8f00,
    SalDefineStatementRule = 0x9000,
    SalStatementRule = 0x9100,
    SalStatementSequenceRule = 0x9200,
    SalDeclarationRule = 0x9300,
    SalVarDeclRule = 0x9400,
    SalFunDeclRule = 0x9500,
    SalProcDeclRule = 0x9600,
    SalProcessBodyRule = 0x9700,
    SAL_RULE_END = 0x9800,
    SAL_TYPE_END = 0x9800
  };

  SalSyntax();
  ~SalSyntax() ;
  void addSalTok (const String n, int t, HiliteID c) ;

  // Type predicates

  bool isSalType(int i) {
    return (0x100 <= i) && (i < SAL_TYPE_END);
  }
  bool isSalTokenType(int i) {
    return (SAL_TOKEN_BEG < i) && (i < SAL_TOKEN_END);
  }
  bool isSalDelimType(int i) {
    return (SAL_DELIM_BEG < i) && (i < SAL_DELIM_END);
  }
  bool isSalNumberType(int i) {
    return (SAL_NUMBER_BEG < i) && (i < SAL_NUMBER_END);
  }
  bool isSalBoolType(int i) {
    return (SAL_BOOL_BEG < i) && (i < SAL_BOOL_END);
  }
  bool isSalOpType(int i) {
    return (SAL_OP_BEG < i) && (i < SAL_OP_END);
  }
  int salOpWeight(int i) {
    return (i & 0xFF);
  }
  bool isSalRelationType(int i) {
    return (SAL_RELATION_BEG < i) && (i < SAL_RELATION_END);
  }
  bool isSalAssignmentType(int i) {
    return (SAL_ASSIGNMENT_BEG < i) && (i < SAL_ASSIGNMENT_END);
  }
  // SAL literals (reserved words)
  bool isSalLiteralType(int i) {
    return (SAL_LITERAL_BEG < i) && (i < SAL_LITERAL_END);
  }
  bool isSalStatementType(int i) {
    return (SAL_STATEMENT_BEG < i) && (i < SAL_STATEMENT_END);
  }
  bool isSalCommandType(int i) {
    return (SAL_COMMAND_BEG < i) && (i < SAL_COMMAND_END);
  }
  bool isSalConstituentType(int i) {
    return (SAL_CONSTITUENT_BEG < i) && (i < SAL_CONSTITUENT_END);
  }
  bool isSalClausalType(int i) {
    return (SAL_CLAUSAL_BEG < i) && (i < SAL_CLAUSAL_END);
  }
  // sal rule types
  bool isSalRuleType(int i) {
    return (SAL_RULE_BEG < i) && (i < SAL_RULE_END);
  }

  bool isSalTypeEqual( int a, int b) {
    return ((a >> 8) == (b >> 8));
  }

  int SalTypeDataBits(int t) {
    return (t & 0xff);
  }

  bool isTopLevel(String line) ;
  int getIndent (const String text, int bot, int top, int beg) ;
  int isSalStatement(const String str);
  int backwardSal(const String text, int bot, int top, int *poz, int *sal);
  HiliteID getHilite (const String text, int start, int end) ;
  void eval(String text, bool isRegion=false, bool expand=false) ;

  String getSymbolHelp(int type);

  // SAL lexer
  String tokenize(String str);
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

#endif






