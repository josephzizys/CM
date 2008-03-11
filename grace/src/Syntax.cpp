/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

#include "Syntax.h"
#include "Grace.h"
//#include <map>
#include <cctype>

//using namespace std;

juce_ImplementSingleton(TextSyntax) ;
juce_ImplementSingleton(LispSyntax) ;
juce_ImplementSingleton(SalSyntax) ;

Syntax::Syntax (String a, String b, String c, String d, String e, 
		String f, String g, String h, String i, String j) 
  : numtoks (0),
    type (syntaxNone)
{

  init_syntab(syntab, a, b, c, d, e, f, g, h, i, j);
  for (int i=0; i<MAXHILITE; i++) hilites[i]=Colours::black;
}

Syntax::~Syntax() {
}

SynTok * Syntax::getSynTok (String n) {
  SynTokMap::iterator iter = tokens.find(n);
  if ( iter == tokens.end() )
    return (SynTok *) NULL;
  return iter->second;
}

bool Syntax::isWhiteBetween(const String txt, int lb, int ub) {
  // return true if just white space between lb and ub
  // (exclusive). comments are white till eol. THIS SHOULD USE
  // SKIP_WHITE WHEN ITS FIXED.
  int end=skip_chars(txt, T(" \t"), lb, ub);
  if (end==ub) return true;
  if (char_comment_p(syntab, txt[end])) return true;
  return false;
}

/************************************************************************
 * Text Syntax                                                          *
 ************************************************************************/

TextSyntax::TextSyntax () 
  : Syntax( T(""), T(""), T("~@#$%^&*-_=+|<>/"),
	    T(""), T(""), T("\""), T("([{"), T(")]}"),
	    T(",.!?;:'`\\"), T("")) 
{
  type=syntaxText;
}

TextSyntax::~TextSyntax() {
  clearSingletonInstance();
}

bool TextSyntax::isTopLevel(String line) {
  // true if line is empty or white in column zero.
  if ( line == String::empty )
    return true;
  else if ( char_white_p(syntab, line[0]) )
    return true;
  else return false;
}

int TextSyntax::getIndent (const String text, int bot, int top, int beg) {
  return 4;
}

hiliteID TextSyntax::getHilite (const String text, int start, int end) {
  return hiliteNone;
}

/************************************************************************
 * Lisp Syntax                                                          *
 ************************************************************************/

LispSyntax::LispSyntax () 
  : Syntax( T(""),
	    T(""), 
	    T("~!@$%^&*-_=+[{]}|:<.>/?"),
	    T(";"), 
	    T("`#',"),
	    T("\""),
	    T("("),
	    T(")"),
	    T(","), T("\\"))
{
  type=syntaxLisp;
  // hilite4 = special forms
  // hilite5 = lisp keywords
  hilites[hiliteString]=Colours::rosybrown;
  hilites[hiliteComment]=Colours::firebrick;
  hilites[hilite4]=Colour(0xa0, 0x20, 0xf0); //Colours::purple;
  hilites[hilite5]=Colours::orchid;
  hilites[hilite6]=Colours::cadetblue;

  addLispTok( T("begin"), numtoks++, hilite4, 1);
  addLispTok( T("block"), numtoks++, hilite4, 1);
  addLispTok( T("defclass"), numtoks++, hilite4, 3);
  addLispTok( T("defconstant"), numtoks++, hilite4, 1);
  addLispTok( T("define"), numtoks++, hilite4, 1);
  addLispTok( T("definstrument"), numtoks++, hilite4, 2);
  addLispTok( T("defmethod"), numtoks++, hilite4, 3);
  addLispTok( T("defobject"), numtoks++, hilite4, 2);
  addLispTok( T("defparameter"), numtoks++, hilite4, 1);
  addLispTok( T("defprocess"), numtoks++, hilite4, 2);
  addLispTok( T("defun"), numtoks++, hilite4, 2);
  addLispTok( T("defvar"), numtoks++, hilite4, 1);
  addLispTok( T("do"), numtoks++, hilite4, 2);
  addLispTok( T("do*"), numtoks++, hilite4, 2);
  addLispTok( T("dolist"), numtoks++, hilite4, 1);
  addLispTok( T("dotimes"), numtoks++, hilite4, 1);
  addLispTok( T("eval-when"), numtoks++, hilite4, 1);
  addLispTok( T("flet"), numtoks++, hilite4, 1);
  addLispTok( T("go"), numtoks++, hilite4, 2);
  addLispTok( T("if"), numtoks++, hilite4, 1);
  addLispTok( T("labels"), numtoks++, hilite4, 1);
  addLispTok( T("lambda"), numtoks++, hilite4, 1);
  addLispTok( T("let"), numtoks++, hilite4, 1);
  addLispTok( T("let*"), numtoks++, hilite4, 1);
  addLispTok( T("loop"), numtoks++, hilite4, 0);
  addLispTok( T("process"), numtoks++, hilite4, 2);
  addLispTok( T("rlet"), numtoks++, hilite4, 1);
  addLispTok( T("unless"), numtoks++, hilite4, 1);
  addLispTok( T("with-sound"), numtoks++, hiliteNone, 1);
  addLispTok( T("when"), numtoks++, hilite4, 1);
}

LispSyntax::~LispSyntax() {
  clearSingletonInstance();
}

void LispSyntax::addLispTok (const String n, int t, hiliteID h, int i) {
  tokens[n] = new SynTok(n, t, h, i);
}

bool LispSyntax::isTopLevel(String line) {
  // True if line starts with ( in column zero.
  if ( line == String::empty )
    return false;
  else if ( line[0] == '(' )
    return true;
  else return false;
}

int LispSyntax::getIndent(const String text, int bot, int top, int beg) {
  // determine the standard Lisp indentation column for the line being
  // Tabbed. bot and top are exclusive limits for search. beg is
  // starting position of backwards scan
  int pos=beg;
  int loc, typ, col, far, sx1, sx2;
  int open, args, arg1, name;
  int standard_indent;
  SynTok * tok;

  // Search backwards for the closest (unbalanced) open paren
  while ( (pos != bot)  ) {
    typ = scan_sexpr(syntab, text, pos, bot, SCAN_CODE, &loc, NULL);
    pos = loc;
    if (typ == SCAN_UNLEVEL)
      break;
  }
  // if nothing is unbalanced then standard indent is column 0;
  if (typ != SCAN_UNLEVEL) {
    //printf("NOTHING UNLEVEL, TYP=%d\n", typ);
    return 0;
  }
  // otherwise pos is now 1 BEFORE nearest leftward open paren
  open=pos+1;
  // see if pos is Quote char. if it does then we are
  // inside a quoted list and the standard indent is open + 1
  if ((pos > bot) && (text[pos] == '\'' )) {
    //printf("QUOTED LIST, pos=%d\n", pos);
    standard_indent = column_of(text, open) + 1;
    return standard_indent;
  }
  // increment search 1 past open paren and search for the start of
  // first sexpr after open paren skipping comments
  pos=open+1;
  typ=parse_sexpr(syntab, text, bot, top, 1, SCAN_CODE, 
		  &pos, &sx1, &sx2);
  // if no sexpr or sexpr not tokenp then standard indent is open + 1
  if (typ != SCAN_TOKEN) {
    standard_indent = column_of(text, open) + 1;
    return standard_indent;
  }
  // at this point we have an open unquoted list with a token in the
  // first position, probably a function call. see if token has
  // distingished args. if > 0 we have to skip over that many args to
  // determine if we do a "body" indent
  args=-1; // -1 means token has no distinuished args
  tok=getSynTok(text.substring(sx1, sx2));
  if (tok != (SynTok *)NULL) args=tok->getIndent();
  //printf("lisp '%s' with %d distinguished args.\n",

  // args == 0 is immediate body indent (like loop)
  if (args == 0) {
    standard_indent = column_of(text, open) + 2;
    return standard_indent;
  }
  // we either have no special indentation or more than zero
  // distinguished args. in either case find the position of first arg
  // in function call. by default its one space after the name.
  // however this might not be a valid position in the line so we
  // calculate using the position of last char in the name + 2
  name=sx2-1; 
  typ=parse_sexpr(syntab, text, bot, top, 1, SCAN_CODE, 
		  &pos, &sx1, &sx2);
  // if there is no (first) arg then standard indent is default arg1
  if (typ < 1) {
    standard_indent = column_of(text, name) + 2;
    return standard_indent;
  } 
  // else sx1 now holds a valid starting pos for arg1. if token was
  // not a special form then standard indent is that position
  arg1=sx1;
  if (args < 0) {
    standard_indent = column_of(text, arg1);
    return standard_indent;
  }
  // otherwise we have 1 or more distingushed args. parse forward to
  // see if we have all the distinguished args. if not then standard
  // indent is arg1. if we have all args then standard indent is a
  // "body" indent of open paren + 2.
  for (int i = 1; i<args;i++) {
    typ=parse_sexpr(syntab, text, bot, top, 1, SCAN_CODE, 
		    &pos, &sx1, &sx2);    
    if (typ < 1) {
      standard_indent = column_of(text, arg1);
      return standard_indent;
    }
  }
  // special form had all its distinguished args, return body indent
  standard_indent = column_of(text, open) + 2;
  return standard_indent;
}

hiliteID LispSyntax::getHilite (const String text, int start, int end) {
  // determine color of token between start and end in text.
  // LISP:
  // hilite4 = special forms (syntax tokens)
  // hilite5 = lisp keywords
  // hilite6 = constants

#ifdef SCHEME 
  if (text[end-1] == ':')  // DSL style keywords (Chicken scheme)
    return hilite5;
  if (text[start] == '#') {
    if (((end-start)==2) && ((text[start+1]=='t') ||
			     (text[start+1]=='f') ) )
      return hilite6;
    if (((end-start)>2) && text[start+1]==':')
      return hilite5;
    return hiliteNone;
  }
#else
  if (text[start] == ':' )
    return hilite5;
#endif 

 SynTok * tok = getSynTok(text.substring(start,end));
  if (tok != (SynTok *)NULL)
    return tok->getHilite();
  return hiliteNone;
}

void LispSyntax::evalText(String text, bool isRegion, bool expand) {
  int typ=SCAN_EMPTY;
  int end=text.length();
  int pos=end-1;
  int old=pos;

  while (pos>-1) {
    typ = scan_sexpr( syntab, text, old, -1, SCAN_CODE, &pos, NULL);
    if (typ<=SCAN_EMPTY)
      break;
    old=pos;
  }

  if ( typ==SCAN_EMPTY ) {
    ((GraceApp *)GraceApp::getInstance())->getConsole()->
      printWarning( T("Lisp eval: empty selection.\n"));
  }
  else if (typ<SCAN_EMPTY) {
    int l1, l2;
    ((GraceApp *)GraceApp::getInstance())->getConsole()->
      printError( T(">>> Error: Lisp eval: unbalanced expression:\n"));
    // print line containing error with ^ marking offending position
    for (l2=old+1; l2<end; l2++)
      if (text[l2]=='\n') break;
    for (l1=old; l1>-1; l1--)
      if (text[l1]=='\n') break;
    l1++;
    ((GraceApp *)GraceApp::getInstance())->getConsole()->
      printError( text.substring(l1,l2) + T("\n"));
    String mark=String::empty;
    for (int i=l1; i<old; i++)
      mark += T(" ");
    mark += T("^\n");
    ((GraceApp *)GraceApp::getInstance())->getConsole()->
      printError( mark);
  }
  else {
    text=text.substring(pos+1);
    if (expand)
#ifdef SCHEME
      text=T("(pp (macroexpand (quote ") + text + T(")))");
#else
      text=T("(progn (pprint (macroexpand (quote ") + text + T("))) (values))");
#endif
    ((GraceApp *)GraceApp::getInstance())->getConsole()->
      consoleEval(text, false, isRegion);
  }
}

/************************************************************************
 * SAL Syntax                                                           *
 ************************************************************************/

SalSyntax::SalSyntax () 
  : Syntax( T(""), T(""), T("~!@$%^&*-_=+|:<.>/?"),
	    T(";"), T("#"), T("\""), T("([{"), T(")]})"),
	    T(","), T("\\")) 
{
  type=syntaxSal;
  // SAL Hilites:
  //  hilite4 = commands
  //  hilite5 = clausals/reserved
  //  hilite6 = classes
  //  hilite7 = keywords
  //  hilite8 = lispkeys/constants/#notation
  hilites[hiliteString]=Colours::rosybrown;
  hilites[hiliteComment]=Colours::firebrick;
  hilites[hilite4]=Colours::blue;
  hilites[hilite5]=Colour(0xa0, 0x20, 0xf0); //Colours::purple;
  hilites[hilite6]=Colours::forestgreen;
  hilites[hilite7]=Colours::orchid;
  hilites[hilite8]=Colours::cadetblue;

  addSalTok( T("begin"), SalBegin, hilite5);
  addSalTok( T("chdir"), SalChdir, hilite5);
  addSalTok( T("define"), SalDefine, hilite5);
  addSalTok( T("else"), SalElse, hilite5);
  addSalTok( T("end"), SalEnd, hilite5);
  addSalTok( T("exec"), SalExec, hilite5);
  addSalTok( T("if"), SalIf, hilite5);
  addSalTok( T("load"), SalLoad, hilite5);
  addSalTok( T("loop"), SalLoop, hilite5);
  addSalTok( T("open"), SalOpen, hilite5);
  addSalTok( T("output"), SalOutput, hilite5);
  addSalTok( T("play"), SalPlay, hilite5);
  addSalTok( T("plot"), SalPlot, hilite5);
  addSalTok( T("print"), SalPrint, hilite5);
  addSalTok( T("return"), SalReturn, hilite5);
  addSalTok( T("run"), SalRun, hilite5);
  addSalTok( T("send"), SalSend, hilite5);
  addSalTok( T("set"), SalSet, hilite5);
  addSalTok( T("sprout"), SalSprout, hilite5);
  addSalTok( T("system"), SalSystem, hilite5);
  addSalTok( T("then"), SalThen, hilite5);
  addSalTok( T("unless"), SalUnless, hilite5);
  addSalTok( T("until"), SalUntil, hilite5);
  addSalTok( T("wait"), SalWait, hilite5);
  addSalTok( T("when"), SalWhen, hilite5);
  addSalTok( T("while"), SalWhile, hilite5);
  addSalTok( T("with"), SalWith, hilite5);
  addSalTok( T("process"), SalProcess, hilite6);
  addSalTok( T("function"), SalFunction, hilite6);
  addSalTok( T("variable"), SalVariable, hilite6);
 
  addSalTok( T("above"), SalAbove, hilite5);
  addSalTok( T("below"), SalBelow, hilite5);
  addSalTok( T("by"), SalBy, hilite5);
  addSalTok( T("downto"), SalDownto, hilite5);
  addSalTok( T("finally"), SalFinally, hilite5);
  addSalTok( T("for"), SalFor, hilite5);
  addSalTok( T("from"), SalFrom, hilite5);
  addSalTok( T("in"), SalIn, hilite5);
  addSalTok( T("over"), SalOver, hilite5);
  addSalTok( T("repeat"), SalRepeat, hilite5);
  addSalTok( T("to"), SalTo, hilite5);

  //  Operators, data field is op weight
  addSalTok( T("|"), SalOr, hiliteNone);
  addSalTok( T("&"), SalAnd, hiliteNone);
  addSalTok( T("!"), SalNot, hiliteNone);
  addSalTok( T("="), SalEqual, hiliteNone); // relation and op
  addSalTok( T("!="), SalNotEqual, hiliteNone);  
  addSalTok( T("<"), SalLess, hiliteNone);
  addSalTok( T(">"), SalGreater, hiliteNone);
  addSalTok( T("<="), SalLessEqual, hiliteNone); // relation and op
  addSalTok( T(">="), SalGreaterEqual, hiliteNone); // relation and op
  addSalTok( T("~="), SalGeneralEqual, hiliteNone);  
  addSalTok( T("+"), SalPlus, hiliteNone);
  addSalTok( T("-"), SalMinus, hiliteNone);
  addSalTok( T("%"), SalMod, hiliteNone);
  addSalTok( T("*"), SalTimes, hiliteNone);  
  addSalTok( T("/"), SalDivide, hiliteNone);
  addSalTok( T("^"), SalExpt, hiliteNone);
  // assignment (also: = <= >=)
  addSalTok( T("+="), SalInc, hiliteNone);
  addSalTok( T("*="), SalMul, hiliteNone);
  addSalTok( T("&="), SalCol, hiliteNone);
  addSalTok( T("@="), SalPre, hiliteNone);  
  addSalTok( T("^="), SalApp, hiliteNone);
  // hash tokens
  addSalTok( T("#t"), SalTrue, hilite8);
  addSalTok( T("#f"), SalFalse, hilite8);
  addSalTok( T("#?"), SalQMark, hilite8);
  addSalTok( T("#$"), SalUnquote, hilite8);
  addSalTok( T("#^"), SalSplice, hilite8);
}

SalSyntax::~SalSyntax() {
  clearSingletonInstance();
}

void SalSyntax::addSalTok (const String n, int t, hiliteID c) {
  numtoks++;
  tokens[n] = new SynTok(n, t, c);
}

bool SalSyntax::isTopLevel(String line) {
  // true if line starts with a top level command.
  if ( line == String::empty )
    return false;
  int end=skip_syntax(syntab, line, T("w"), 0, line.length() );
  if ( end > 0 ) {
    SynTok * tok = getSynTok(line.substring(0,end));
    if ( (tok != (SynTok *)NULL) && isSalCommandType(tok->getType()) )
      return true;
    else return false;
  }
  else return false;
}

int lineIndent(const String str, int bot, int top, int pos) {
  int beg, ind;
  beg=move_bol(str, pos, bot);
  ind=skip_chars(str, T(" \t"), beg, top);
  return ind-beg;
}

int SalSyntax::isSalStatement(const String name) {
  SynTok * tok = getSynTok(name);
  if ( tok == (SynTok *)NULL ) return -1;
  if ( isSalStatementType(tok->getType()) )
    return tok->getType();
  return -1;
}

int SalSyntax::backwardSal(const String text, int bot, int top, int *poz, int *sal) {
  int pos=*poz;
  int typ=SCAN_EMPTY, sx1, sx2, loc, tst, lev=0;
  *sal=-1;
  while (pos>bot) {
    typ=parse_sexpr(syntab, text, bot, top, -1, SCAN_CODE, 
		    &pos, &sx1, &sx2);      
    if (typ < 1) {
      *poz=pos+1;
      *sal=-1;
      return typ;
    }
    else if (typ == SCAN_TOKEN) {
      tst = isSalStatement( text.substring(sx1,sx2) ) ;
      if ( tst > -1) {
	if (tst == SalEnd)
	  lev++;
	else if ( (tst == SalBegin) || (tst == SalLoop) ||  (tst == SalRun)) 
	  lev--;
	// stop if no pending "end"
	if (lev <= 0) {
	  *poz=sx1;
	  *sal=tst;
	  break;
	}
      }
    }
  }
  // begin, loop or run without balancing end is unlevel
  return (lev == 0) ? typ : SCAN_UNLEVEL;
}

int SalSyntax::getIndent(const String text, int bot, int top, int poz) {
  int typ, sx1, sx2, lev=0, pos=poz, old=poz, sal=-1, col;
  bool end=false;

  // notice if we are looking at an End in tabbed line.
  typ=parse_sexpr(syntab, text, pos-1, top, 1, SCAN_CODE, 
		  &pos, &sx1, &sx2); 
  if ( (typ==SCAN_TOKEN) && (sx2-sx1 == 3) &&
       (SalEnd==isSalStatement( text.substring(sx1,sx2) )) ) {
    end=true;
  }

  pos=poz;
  //printf("standardIndent, before loop\n");
  while (true) {
    typ=backwardSal(text,bot,top,&pos,&sal);
    //printf("after backwardsal, typ=%d, pos=%d, sal=%d\n", typ, pos, sal);
    if (sal==-1)  // no sal command
      if (typ==SCAN_UNLEVEL)
	// indent 1 past terminating open paren
	return column_of(text,pos)+1;
      else if (typ==SCAN_EMPTY) 
	return 0;
      else 
	pos--;
    else
      // have sal cmd. stop on Then or Else or cmd starts line
      if ( (sal==SalThen) || (sal==SalElse) )
	break;
      else if ( isWhiteBetween(text,move_bol(text,pos,bot),pos) )
	break;
      else
	pos--;
  }
  // reached a sal command that starts a line or is a Then or Else
  // anywhere in a line.  By default we indent to first non-white char
  // on that line.
  col=lineIndent(text, bot, top, pos);
  ///printf("default indent col is %d\n", *col);

  // Now check for the special indent cases:
  // 1. If command is Then or Else at END of line then indent=+2.
  // 2. If sexpr-1 is Then or Else then this command is an
  // (already) indented clause so indent=-2
  // 3. If command is Define, Loop or Run WITHOUT end indent=+2
  // 4. If Tab line is End then indent=-2. 
  // 5. If first token preceding original position is a comma then
  // indent to first arg position
  if ( ((sal==SalThen) || (sal==SalElse)) && 
       isWhiteBetween(text,pos+4, move_eol(text,pos,top)) ) {
    //printf("then/else at end\n");
    col+=2;
  }
  else if (sal==SalDefine)
    col+=2;
  else if ( (typ==SCAN_UNLEVEL) &&
	    ( (sal==SalLoop) || (sal==SalRun) || (sal==SalBegin)) ) {
    col+=2;
    //printf("loop/run: col set to %d\n", *col);
    if ( end ) col-=2;
  }
  else {
    // look if previous command is then or else if so reindent-2
    int tmp=pos-1; // pos is start index of current command
    int pre=-1;
    backwardSal(text,bot,top,&tmp,&pre);
    if ( (pre==SalThen) || (pre==SalElse) || (pre==SalDefine)) {
      col-=2;
      //printf("previous then/else: col set to %d\n", *col);      
    }
    if ( end ) col-=2;
  }
  // add check for negative column (shouldnt happen but...)
  return (col<0) ? 0 : col;
}

hiliteID SalSyntax::getHilite (const String text, int start, int end) {
  // determine color of token between start and end in text.
  // SAL Hilites:
  //  hilite4 = commands
  //  hilite5 = clausals/reserved
  //  hilite6 = classes
  //  hilite7 = keywords
  //  hilite8 = lispkeys/constants/#notation

  if ((text[start]=='<') && (text[end-1]=='>'))
    return hilite6;  // <foo>
  if (text[end-1] == ':')
    return hilite7;  // foo:
  if (text[start] == ':' )
    return hilite8;  // :foo
  if (text[start] == '#')
    return hilite8;  // #foo
  SynTok * tok = getSynTok(text.substring(start,end));
  if (tok == (SynTok *)NULL)
    return hiliteNone;
  if ( (isSalCommandType(tok->getType())) || (tok->getType()==SalEnd)) {
    // show commands at start of line as executable, allow balancing
    // End in col 0 to show blue too.
    if (start==0 || text[start-1] == '\n')
      return hilite4;
    else return hilite5;
  }
  else return tok->getHilite();
}

void SalSyntax::evalText(String text, bool isRegion, bool expand) {
  String tokens=tokenize(text);
  // if null then error was reported...
  if (tokens == String::empty)
    return ;
#ifdef SCHEME  
  int rule=(isRegion) ? SalSyntax::SalStatementSequenceRule : 0;
  String exp = (expand) ? T("#t") : T("#f");
  // quotify string chars in input text
  String input=text.replace(T("\""),T("\\\"") );
  // build call to sal function
  text=T("(sal \"") + input + T("\"") + T(" ") +
    String(rule) + T(" ") +
    T("(quote ") + tokens + T(") ") + exp + T(")");
#else
  text=(T("(cm::sal ") + String("\"") 
	+ text.replace(T("\""),T("\\\""))
	+ String("\"") );
  if ( isRegion )
    text << T(" :pattern :statement-sequence");
  if ( expand )
    text << T(" :expand t");
  text << T(")");
#endif
  ((GraceApp *)GraceApp::getInstance())->getConsole()->
    consoleEval(text, true, isRegion);
}

void SalSyntax::loadFile(String path) {
  File file = File(path);
  if (!file.existsAsFile()) {
    ((GraceApp *)GraceApp::getInstance())->getConsole()->
      printError( T(">>> Error: file ") + path + T(" does not exist.\n"));
    return;
  }
  evalText( file.loadFileAsString(), true);
}

/*
 * SAL Lexer
 */

String SalSyntax::tokenize(String str) {
  int old=0, len=str.length(), pos=0, beg=0, end=0, lev[]={0,0,0,0};
  int typ;
  SynTok *tok;
  OwnedArray<SynTok> tokenstream;
  String tokenstring=String::empty;

  while (true) {
    old=pos;
    typ=parse_sexpr(syntab,str,-1,len,1,SCAN_PARSER,&pos,&beg,&end);
    switch (typ) {
    case SCAN_EMPTY :
      tok=NULL;
      break;
    case SCAN_UNMATCHED:
      // this happens if we hit an unterminated string...
      // we need to find the starting char
      for (beg=old;beg<pos;beg++)
	if (str[beg]=='\"') break;
      tok=new SynTok(T("\""), SalString, beg);
      break;
    case SCAN_STRING :
      tok=new SynTok(str.substring(beg,end), SalString, beg);
      break;
    case SCAN_PUNCT :
      tok=new SynTok(T(","), SalComma, beg );
      break;
    case SCAN_OPEN :
      if ( paren_char_p(str[beg]) ) {
	lev[0]++;
	tok=new SynTok(T("("), SalLParen, beg);
      }
      else if ( curly_char_p(str[beg]) ) {
	lev[1]++;
	tok=new SynTok(T("{"), SalLCurly, beg);
      }
      else {
	lev[2]++;
	tok=new SynTok(T("["), SalLBrace, beg);
      }
      break;
    case SCAN_CLOSE :
      if ( paren_char_p(str[beg]) ) {
	if ( --lev[0]<0 ) typ=SCAN_UNLEVEL;
	tok=new SynTok(T(")"), SalRParen, beg);
      }
      else if ( curly_char_p(str[beg]) ) {
	if ( --lev[1]<0 ) typ=SCAN_UNLEVEL;
	tok=new SynTok(T("}"), SalRCurly, beg);
      }
      else {
	if ( --lev[2]<0 ) typ=SCAN_UNLEVEL;
	tok=new SynTok(T("]"), SalRBrace, beg);
      }
      break;
    case SCAN_TOKEN :
      tok=new SynTok(String::empty, SalUntyped, beg);
      typ=classifyToken(str.substring(beg,end), tok);
      // begin ... end block matching
      if (isSalType(typ))
	if (SalTypeDataBits(typ)==SalBlockClose) {
	  if (--lev[3]<0) {
	    typ=SalSyntax::UnmatchedEnd;
	  }
	  else ;
	  //	  printf("decrement level=%d: %s\n",lev[3],
	  //		 str.substring(beg,end).toUTF8());
	}
	else if (SalTypeDataBits(typ)==SalBlockOpen) {
	  lev[3]++;
	  //	  printf("increment level=%d: %s\n",lev[3],
	  //		 str.substring(beg,end).toUTF8());
	}
      // if (typ==SalUntyped) typ=SalUnknown;
      break;
    default:  
      // error code
      printf("error code=%d, tok=%s\n", typ, str.substring(beg,end).toUTF8());
      tok=new SynTok(str.substring(beg,end), SalUntyped, beg);
      break;
    } // end switch(typ)

    if (tok != NULL) tokenstream.add(tok);

    // stop if empty or error.
    if (typ<1)
      break;

  }  // end while(true)

  //  printf("typ=%d, lev[0]=%d,lev[1]=%d\n", typ, lev[0], lev[1]);

  // if no errors search for any unmatched delimiters
  if ( typ>=0 ) {
    if (lev[0] > 0) {
      tok=findUnbalanced(tokenstream, SalLParen, SalRParen, lev[0]);
      typ=SCAN_UNMATCHED;
    }
    else if (lev[1] > 0) {
      tok=findUnbalanced(tokenstream, SalLCurly, SalRCurly, lev[1]);
      typ=SCAN_UNMATCHED;
    }
    else if (lev[2] > 0) {
      tok=findUnbalanced(tokenstream, SalLBrace, SalRBrace, lev[2]);
      typ=SCAN_UNMATCHED;
    }
    else if (lev[3] > 0) {
      tok=findUnbalanced(tokenstream, SalBlockOpen, SalBlockClose,
			 lev[3]);
      typ=SalSyntax::MissingEnd;
    }
  }

  if (typ<0) {
    salError(str, typ, tok);
  }
  else {
    tokenstring=T("(");
    for (int i=0; i<tokenstream.size(); i++) {
      if (i>0) tokenstring << T(" ");
      // each token is triplet: (<saltype> <string> <position>)
      tokenstring << T("(#x") << String::toHexString( tokenstream[i]->type )
		  << T(" \"") << tokenstream[i]->name.unquoted() << T("\" ") 
		  << String(tokenstream[i]->data1) << T(")") ;
    }
    tokenstring << T(")");    
  }
  tokenstream.clear();
  return tokenstring;
}

void SynTok::print(bool lisp) {
  printf("(#x%x \"%s\" %d)", type, name.unquoted().toUTF8(), data1);
}

void SalSyntax::salError(String str, int err, SynTok *tok) {
  String errstr= T(">>> Error: ");
  switch (err) {

  case SCAN_UNMATCHED:
  case SCAN_UNLEVEL:
  case SalSyntax::UnmatchedEnd :
    errstr << T("Unmatched '") << tok->name << T("':\n");
    break;
  case SalSyntax::MissingEnd :
    errstr << T("'") << tok->name << T("' missing 'end':\n");
    break;
  case SalSyntax::SalUnknown :
  default:
    errstr << T("Invalid expression '") << tok->name << T("':\n");
    break;

  }
  // isolate line containing error position
  int len=str.length();
  int pos=tok->getStart();
  int beg=pos-1;
  for ( ; beg>-1; beg--)
    if (str[beg]=='\n') break;
  beg++;
  int end=pos;
  for ( ; end<len; end++)
    if ( str[end]=='\n') break;
  errstr << str.substring(beg,end) << T("\n");
  // indented "^" marks error position
  for (int i=beg;i<pos;i++)
    errstr << T(" ");
  errstr << T("^\n");
  ((GraceApp *)GraceApp::getInstance())->getConsole()->printError( errstr);
}

int addToken (String str, int start, int end) {
}

SynTok * SalSyntax::findUnbalanced(OwnedArray<SynTok> &tokenstream, int target,
				   int other, int level) {
  int n=level;

  //printf("target=%x, other=%x, level=%d\n", target, other, level);
  for (int i=tokenstream.size()-1; i>-1; i--) {
    int typ=tokenstream[i]->getType();
    //    printf("rawtype=%x\n", typ);
    //    printf("databits=%x\n", SalTypeDataBits(typ));
   // if target is not a type then its data (e.g. SalBlockOpen)
    if ( ! isSalType(target) )  {
      //      printf("data test!\n", typ);
      typ=SalTypeDataBits(typ);
      //      printf("data test, data=%d\n", typ);
    }
    //    else printf("not testing data!\n");
    if ( typ == target )
      if (n == level)
	return tokenstream[i];
      else
	n--;
    else if  ( typ == other )
      n++;
  }
  printf("WARNING: failed to find unbalanced!\n");
  return NULL;
}

int SalSyntax::classifyToken(String str, SynTok *tok) {
  // attempt to classify the token string by calling the various
  // predicates and returning the first predicate type>0 or type<0
  // (error) 
  int flag=isLiteralToken(str,tok);
  if (flag != SalSyntax::SalUntyped) return flag; 

  flag=isClassToken(str,tok);
  if (flag != SalSyntax::SalUntyped) return flag; 

  flag=isNumberToken(str, tok);
  if (flag != SalSyntax::SalUntyped) return flag; 

  flag=isIdentifierToken(str, tok);
  if (flag != SalSyntax::SalUntyped) return flag; 
  return SalSyntax::SalUnknown;
}

int SalSyntax::isLiteralToken(String str, SynTok *tok) {
  //String str=tok->getName()
  int typ=SalSyntax::SalUntyped;
  SynTokMap::iterator iter = tokens.find(str);
  if ( iter != tokens.end() ) {
    typ=iter->second->getType();
    tok->setType(typ);
    tok->setName(str);
  }
  return typ;
}

int SalSyntax::isClassToken(String str, SynTok *tok) {
  // isClassToken has to be called AFTER check for operator else the
  // check balancing <> wont work
  int typ=SalSyntax::SalUntyped;
  int len=str.length();
  //String str=tok->getName();
  if (str[0]=='<')
    if (str[len-1]=='>')
      if (true) {
	typ=SalSyntax::SalClass;
	tok->setType(typ);
	tok->setName(str.substring(1,len-2));
      }
      else typ=SalSyntax::SalUnknown;
    else if (str.length()-1=='>')
      typ=SalSyntax::SalUnknown;
  return typ;
}

int SalSyntax::isNumberToken(String str, SynTok *tok) {
  //String str=tok->getName();
  int len=str.length();
  int typ=SalSyntax::SalInteger;
  int dot=0, div=0, dig=0;
  for (int pos=0; pos<len; pos++) {
    if (typ <= SalSyntax::SalUntyped) return typ;
    switch ( str[pos] ) {
    case '+':
    case '-':
      if (pos>0) typ=SalSyntax::SalUntyped;
      break;
    case '.':
      if (dot>0) typ=SalSyntax::SalUntyped;
      if (div>0) typ=SalSyntax::SalUntyped;
      dot++;
      break;
    case '/':
      typ=SalSyntax::SalRatio;
      if (div>0) typ=SalSyntax::SalUntyped;
      if (dig==0) typ=SalSyntax::SalUntyped;
      if (dot>0) typ=SalSyntax::SalUntyped;
      if (pos==len-1) typ=SalSyntax::SalUntyped;
      div++;
      break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      dig++;
      if (dot>0) typ=SalSyntax::SalFloat;
      break;
    default:
      typ=SalSyntax::SalUntyped;
    }
  }
  tok->setType(typ);
  if (typ>SalSyntax::SalUntyped) {
    tok->setName(str);
  }
  return typ;
}

int SalSyntax::isIdentifierToken(String str, SynTok *tok) {
  //  String str=tok->getName();
  String sym=T("~!@$%^&*-_=+|:<.>/?");
  int len=str.length();
  int typ=SalSyntax::SalUntyped;
  int chr=0, dot=0, din=0, col=0;

  for (int pos=0; pos<len; pos++) {
    if ( typ<0 ) return typ;
    chr=str[pos];
    if ( chr=='.' ) {
      dot++;
      din=pos;
    }
    else if ( chr==':') {
      if (typ != SalSyntax::SalUntyped) typ=SalSyntax::SalUnknown;
      else if (col>0) typ=SalSyntax::SalUnknown;
      else if (pos==0) typ=SalSyntax::SalKeyword;
      else if (pos==len-1) typ=SalSyntax::SalKeyparam;
      col++;
    }
    else if ( isalnum(chr) || sym.containsChar(chr) )
      ;
    else typ=SalSyntax::SalUnknown;
  }
  if ( (typ==SalSyntax::SalUntyped) && dot==1 && din>0 && din<(len-1) )
    typ=SalSyntax::SalSlotRef;
  if (typ==SalSyntax::SalUntyped)
    typ=SalSyntax::SalIdentifier;
  if (typ>0) {
    tok->setType(typ);
    if (typ==SalSyntax::SalKeyparam)
      tok->setName(str.dropLastCharacters(1));
    else if (typ==SalSyntax::SalKeyword)
      tok->setName(str.substring(1));
    else
      tok->setName(str);
  }
  return typ;
}


