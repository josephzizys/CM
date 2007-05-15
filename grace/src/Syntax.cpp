/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

#include "Syntax.h"
#include <map>;
using namespace std;

Syntax::Syntax (String a, String b, String c, String d, String e, String f, 
		String g, String h, String i, String j) {
  init_syntab(syntab, a, b, c, d, e, f, g, h, i, j);
  for(int i=0; i<MAXHILITE; i++) hilites[i]=Colours::black;
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

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Lisp Syntax
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int lispTokCtr = 0;
SynTokMap lispTokMap;

void addLispTok (const String n, int a, hiliteID b, int c, int d) {
  if (a==0) 
    a=lispTokCtr;
  lispTokCtr++;
  lispTokMap[n] = new SynTok(n, a, b, c, d);
}

void initLispToks() {
  printf("initing lisp map\n");
  addLispTok( T("block"), 0, hilite4, 1, 0);
  addLispTok( T("defclass"), 0, hilite4, 3, 0);
  addLispTok( T("defconstant"), 0, hilite4, 1, 0);
  addLispTok( T("define"), 0, hilite4, 1, 0);
  addLispTok( T("definstrument"), 0, hilite4, 2, 0);
  addLispTok( T("defmethod"), 0, hilite4, 3, 0);
  addLispTok( T("defobject"), 0, hilite4, 2, 0);
  addLispTok( T("defparameter"), 0, hilite4, 1, 0);
  addLispTok( T("defprocess"), 0, hilite4, 2, 0);
  addLispTok( T("defun"), 0, hilite4, 2, 0);
  addLispTok( T("defvar"), 0, hilite4, 1, 0);
  addLispTok( T("do"), 0, hilite4, 2, 0);
  addLispTok( T("do*"), 0, hilite4, 2, 0);
  addLispTok( T("dolist"), 0, hilite4, 1, 0);
  addLispTok( T("dotimes"), 0, hilite4, 1, 0);
  addLispTok( T("eval-when"), 0, hilite4, 1, 0);
  addLispTok( T("flet"), 0, hilite4, 1, 0);
  addLispTok( T("if"), 0, hilite4, 1, 0);
  addLispTok( T("labels"), 0, hilite4, 1, 0);
  addLispTok( T("lambda"), 0, hilite4, 1, 0);
  addLispTok( T("let"), 0, hilite4, 1, 0);
  addLispTok( T("let*"), 0, hilite4, 1, 0);
  addLispTok( T("loop"), 0, hilite4, 0, 0);
  addLispTok( T("process"), 0, hilite4, 2, 0);
  addLispTok( T("rlet"), 0, hilite4, 1, 0);
  addLispTok( T("unless"), 0, hilite4, 1, 0);
  addLispTok( T("when"), 0, hilite4, 1, 0);
}

SynTok* LispSyntax::getSynTok (String n) {
  SynTokMap::iterator iter = lispTokMap.find(n);
  if ( iter == lispTokMap.end() )
    return (SynTok *) NULL;
  return iter->second;
}

LispSyntax::LispSyntax () 
  : Syntax( T(""), T(""), T("~!@$%^&*-_=+[{]}|:<.>/?"),
	    T(";"), T("`#',"), T("\""), T("("), T(")"),
	    T(","), T("\\")) {
  if ( lispTokCtr == 0 )
    initLispToks();
  // hilite4 = special forms
  // hilite5 = lisp keywords
  hilites[hiliteString]=Colours::rosybrown;
  hilites[hiliteComment]=Colours::firebrick;
  hilites[hilite4]=Colour(0xa0, 0x20, 0xf0); //Colours::purple;
  hilites[hilite5]=Colours::orchid;
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
    typ = scan_sexpr(syntab, text, pos, bot, SCAN_CODE, &loc);
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
  if (tok != (SynTok *)NULL) args=tok->indent;
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
  if (text[start] == ':' )
    return hilite5;
  SynTok * tok = getSynTok(text.substring(start,end));
  if (tok != (SynTok *)NULL)
    return tok->hilite;
  return hiliteNone;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Sal Syntax
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int salMapCtr = 0;
SynTokMap salTokMap;

void addSalTok (const String n, int a, hiliteID b, int c, int d) {
  salTokMap[n] = new SynTok(n, a, b, c, d);
}

void initSalToks() {
  printf("initing SAL map\n");
  salMapCtr=1;
  addSalTok( T("begin"), salBegin, hilite5, 1, salCommand);
  addSalTok( T("chdir"), salChdir, hilite5, 0,salCommand);
  addSalTok( T("define"), salDefine, hilite5, 1, salCommand);
  addSalTok( T("else"), salElse, hilite5, 1, salClausal);
  addSalTok( T("end"), salEnd, hilite5, -1, salClausal);
  addSalTok( T("exec"), salExec, hilite5, 0, salCommand);
  addSalTok( T("if"), salIf, hilite5, 0, salCommand);
  addSalTok( T("load"), salLoad, hilite5, 0, salCommand);
  addSalTok( T("loop"), salLoop, hilite5, 1, salCommand);
  addSalTok( T("open"), salOpen, hilite5, 0, salCommand);
  addSalTok( T("output"), salOutput, hilite5, 0, salClausal);
  addSalTok( T("play"), salPlay, hilite5, 0, salCommand);
  addSalTok( T("plot"), salPlot, hilite5, 0, salCommand);
  addSalTok( T("print"), salPrint, hilite5, 0, salCommand);
  addSalTok( T("return"), salReturn, hilite5, 0, salClausal);
  addSalTok( T("rts"), salRts, hilite5, 0, salCommand);
  addSalTok( T("run"), salRun, hilite5, 1, salCommand);
  addSalTok( T("set"), salSet, hilite5, 0, salCommand);
  addSalTok( T("sprout"), salSprout, hilite5, 0, salCommand);
  addSalTok( T("system"), salSystem, hilite5, 0, salCommand);
  addSalTok( T("then"), salThen, hilite5, 1, salClausal);
  addSalTok( T("unless"), salUnless, hilite5, 0, salClausal);
  addSalTok( T("until"), salUntil, hilite5, 0, salClausal);
  addSalTok( T("wait"), salWait, hilite5, 0, salClausal);
  addSalTok( T("when"), salWhen, hilite5, 0, salClausal);
  addSalTok( T("while"), salWhile, hilite5, 0, salClausal);
  addSalTok( T("with"), salWith, hilite5, 0, salClausal);

  addSalTok( T("process"), salProcess, hilite6, 0, salReserved);
  addSalTok( T("function"), salFunction, hilite6, 0, salReserved);
  addSalTok( T("variable"), salVariable, hilite6, 0, salReserved);
  
  int res=100;
  // should really have real ids for these too...
  addSalTok( T("above"), res++, hilite5, 0, salReserved);
  addSalTok( T("below"), res++, hilite5, 0, salReserved);
  addSalTok( T("by"), res++, hilite5, 0, salReserved);
  addSalTok( T("downto"), res++, hilite5, 0, salReserved);
  addSalTok( T("finally"), res++, hilite5, 0, salReserved);
  addSalTok( T("for"), res++, hilite5, 0, salReserved);
  addSalTok( T("from"), res++, hilite5, 0, salReserved);
  addSalTok( T("in"), res++, hilite5, 0, salReserved);
  addSalTok( T("over"), res++, hilite5, 0, salReserved);
  addSalTok( T("repeat"), res++, hilite5, 0, salReserved);
  addSalTok( T("to"), res++, hilite5, 0, salReserved);
}

SalSyntax::SalSyntax () 
  : Syntax( T(""), T(""), T("~!@#$%^&*-_=+|:<.>/?"),
	    T(";"), T("`'"), T("\""), T("([{"), T(")]})"),
	    T(","), T("\\")) {
  if ( salMapCtr == 0)
    initSalToks();
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
}

SynTok* SalSyntax::getSynTok (String n) {
  SynTokMap::iterator iter = salTokMap.find(n);
  if ( iter == salTokMap.end() )
    return (SynTok *) NULL;
  return iter->second;
}

bool SalSyntax::isTopLevel(String line) {
  // true if line starts with a top level command.
  if ( line == String::empty )
    return false;
  int end=skip_syntax(syntab, line, T("w"), 0, line.length() );
  if ( end > 0 ) {
    SynTok * tok = getSynTok(line.substring(0,end));
    if ( (tok != (SynTok *)NULL) && tok->toktype==salCommand )
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
  if ( tok->toktype < salReserved )
    return tok->id;
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
	if (tst == salEnd)
	  lev++;
	else if ( (tst == salBegin) || (tst == salLoop) ||  (tst == salRun)) 
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
       (salEnd==isSalStatement( text.substring(sx1,sx2) )) ) {
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
      if ( (sal==salThen) || (sal==salElse) )
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
  if ( ((sal==salThen) || (sal==salElse)) && 
       isWhiteBetween(text,pos+4, move_eol(text,pos,top)) ) {
    //printf("then/else at end\n");
    col+=2;
  }
  else if (sal==salDefine)
    col+=2;
  else if ( (typ==SCAN_UNLEVEL) &&
	    ( (sal==salLoop) || (sal==salRun) || (sal==salBegin)) ) {
    col+=2;
    //printf("loop/run: col set to %d\n", *col);
    if ( end ) col-=2;
  }
  else {
    // look if previous command is then or else if so reindent-2
    int tmp=pos-1; // pos is start index of current command
    int pre=-1;
    backwardSal(text,bot,top,&tmp,&pre);
    if ( (pre==salThen) || (pre==salElse) || (pre==salDefine)) {
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
  if ((tok->toktype==salCommand) || (tok->id==salEnd)) {
    // show commands at start of line as executable, allow balancing
    // End in col 0 to show blue too.
    if (start==0 || text[start-1] == '\n')
      return hilite4;
    else return hilite5;
  }
  else return tok->hilite;
}
    
/*
 * Text Syntax
 */

TextSyntax::TextSyntax () 
  : Syntax( T(""), T(""), T("~@#$%^&*-_=+|<>/"),
	    T(""), T(""), T("\""), T("([{"), T(")]}"),
	    T(",.!?;:'`\\"), T("")) {
}

bool TextSyntax::isTopLevel(String line) {
  // true if line is empty or white in column zero.
  if ( line == String::empty )
    return true;
  else if ( char_white_p(syntab, line[0]) )
    return true;
  else return false;
}

SynTok* TextSyntax::getSynTok (String n) {
  return (SynTok *) NULL;
}

int TextSyntax::getIndent (const String text, int bot, int top, int beg) {
  return 4;
}

hiliteID TextSyntax::getHilite (const String text, int start, int end) {
  return hiliteNone;
}
