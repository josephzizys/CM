/*=======================================================================*
  Copyright (c) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify
  it under the terms of the Lisp Lesser Gnu Public License. The text
  of this agreement is available at http://www.cliki.net/LLGPL
 *=======================================================================*/

#include "Syntax.h"
#include "Console.h"
#include "Scheme.h"
#ifdef GRACE
#include "Preferences.h"
#include "CommonLisp.h"
#endif
#include <cctype>
#include <iostream>

juce_ImplementSingleton(TextSyntax) ;
juce_ImplementSingleton(LispSyntax) ;
juce_ImplementSingleton(SalSyntax) ;
juce_ImplementSingleton(Sal2Syntax) ;

Syntax::Syntax (String a, String b, String c, String d, String e, 
		String f, String g, String h, String i, String j) 
  : numtoks (0),
    maxtoklen (0),
    coloring (false),
    type (TextIDs::Empty),
    tabwidth (0)
{
  init_syntab(syntab, a, b, c, d, e, f, g, h, i, j);
  for (int i=0; i<HiliteIDs::NUMHILITES; i++)
    hilites[i]=Colours::black;
  for (int i=0; i<ColorThemeIDs::MAXTOKENCOLORS; i++)
    colors[i]=Colours::black;
}

Syntax::~Syntax()
{
}

// default methods for Syntax subclasses


void Syntax::addSynTok (const String n, int t, int a, int b, int c) 
{
  numtoks++;
  int l=n.length();
  if (l>maxtoklen) maxtoklen=l;
  tokens[n] = new SynTok(n, t, a, b, c);
}

SynTok* Syntax::getSynTok (String n) 
{
  SynTokMap::iterator iter = tokens.find(n);
  if ( iter == tokens.end() )
    return NULL;
  return iter->second;
}

bool Syntax::isWhiteBetween(const String txt, int lb, int ub) {
  // return true if just white space between lb and ub
  // (exclusive). comments are white till eol. THIS SHOULD USE
  // SKIP_WHITE WHEN ITS FIXED.
  int end=skip_chars(txt, T(" \t"), lb, ub);
  if (end==ub) return true;
  if (char_comment_p(syntab, (char)txt[end])) return true;
  return false;
}

void Syntax::setTabWidth(int n)
{
  tabwidth=n;
#ifdef GRACE
  String prop=TextIDs::toString(type)+T("TabWidth");
  Preferences::getInstance()->setIntProp(prop, tabwidth);
#endif
}

/*=======================================================================*
                              Text Syntax
 *=======================================================================*/

TextSyntax::TextSyntax () 
  : Syntax( T(""), T(""), T("~@#$%^&*-_=+|<>/"),
	    T(""), T(""), T("\""), T("([{"), T(")]}"),
	    T(",.!?;:'`\\"), T("")) 
{
  type=TextIDs::Text;
#ifdef GRACE
  tabwidth=Preferences::getInstance()->getIntProp(T("TextTabWidth"), 4);
#else
  tabwidth=4;
#endif
}

TextSyntax::~TextSyntax()
{
  clearSingletonInstance();
}

const StringArray TextSyntax::getTokenTypes ()
{ 
  // juce's CodeEditorComponent uses this array to name the
  // Tokenizer's tokenTypes, where each array index is a tokenType and
  // the string at that postion is its name. we use this array to map
  // tokenTypes to ColorTheme attribute names in the Xml ColorTheme.
  StringArray names;
  // ColorSchemeAttribute        TokenType
  names.add(T("error"));      // TokenError
  names.add(T("plaintext"));  // TokenPlaintext
  return names;
}

const Colour TextSyntax::getDefaultColour (const int tokenType)
{
  return Colours::black;
}

int TextSyntax::readNextToken (CodeDocument::Iterator &source)
{
  source.skipToEndOfLine(); 
  return TokenPlaintext;
}

bool TextSyntax::isTopLevel(String line)
{
  // true if line is empty or white in column zero.
  if ( line == String::empty )
    return true;
  else if ( char_white_p(syntab, (char)line[0]) )
    return true;
  else return false;
}

int TextSyntax::getIndent (const String text, int bot, int top, int beg)
{
  return tabwidth;
}

HiliteID TextSyntax::getHilite (const String text, int start, int end)
{
  return HiliteIDs::None;
}

/*=======================================================================*
                              Lisp Syntax
 *=======================================================================*/

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
  // HiliteIDs::Hilite4 = special forms
  // HiliteIDs::Hilite5 = lisp keywords
  coloring=true;
  type=TextIDs::Lisp;
#ifdef GRACE
  tabwidth=Preferences::getInstance()->getIntProp(T("LispTabWidth"), 2);
#else
  tabwidth=2;
#endif
  hilites[HiliteIDs::String]=Colours::rosybrown;
  hilites[HiliteIDs::Comment]=Colours::firebrick;
  hilites[HiliteIDs::Hilite4]=Colour(0xa0, 0x20, 0xf0); //Colours::purple;
  hilites[HiliteIDs::Hilite5]=Colours::orchid;
  hilites[HiliteIDs::Hilite6]=Colours::cadetblue;
  addSynTok(T("begin"), numtoks, HiliteIDs::Hilite4, 1000);
  addSynTok(T("define"), numtoks, HiliteIDs::Hilite4, 1);
  addSynTok(T("define*"), numtoks, HiliteIDs::Hilite4, 1);
  addSynTok(T("define-process"), numtoks, HiliteIDs::Hilite4, 1);
  addSynTok(T("definstrument"), numtoks, HiliteIDs::Hilite4, 1);
  addSynTok(T("defun"), numtoks, HiliteIDs::Hilite4, 1);
  addSynTok(T("defparameter"), numtoks, HiliteIDs::Hilite4, 1);
  addSynTok(T("defvar"), numtoks, HiliteIDs::Hilite4, 1);
  addSynTok(T("run"), numtoks, HiliteIDs::Hilite4, 1000);
  addSynTok(T("and"), numtoks, HiliteIDs::Hilite4, 2);
  addSynTok(T("cond"), numtoks, HiliteIDs::Hilite4, 2);
  addSynTok(T("do"), numtoks, HiliteIDs::Hilite4, 2);
  addSynTok(T("if"), numtoks, HiliteIDs::Hilite4, 1);
  addSynTok(T("lambda"), numtoks, HiliteIDs::Hilite4, 1);
  addSynTok(T("let"), numtoks, HiliteIDs::Hilite4, 1);
  addSynTok(T("let*"), numtoks, HiliteIDs::Hilite4, 1);
  addSynTok(T("letrec"), numtoks, HiliteIDs::Hilite4, 1);
  addSynTok(T("loop"), numtoks, HiliteIDs::Hilite4, 1000);
  addSynTok(T("or"), numtoks, HiliteIDs::Hilite4, 2);
  addSynTok(T("process"), numtoks, HiliteIDs::Hilite4, 1000);
  addSynTok(T("run"), numtoks, HiliteIDs::Hilite4, 1000);
  addSynTok(T("send"), numtoks, HiliteIDs::Hilite4, 1);
  addSynTok(T("unless"), numtoks, HiliteIDs::Hilite4, 1);
  addSynTok(T("when"), numtoks, HiliteIDs::Hilite4, 1);
  addSynTok(T("with-sound"), numtoks, HiliteIDs::Hilite4, 1);
  addSynTok(T("with-fomus"), numtoks, HiliteIDs::Hilite4, 1);
}

LispSyntax::~LispSyntax()
{
  clearSingletonInstance();
}

const StringArray LispSyntax::getTokenTypes ()
{
  // juce's CodeEditorComponent uses this array to name the
  // Tokenizer's tokenTypes, where each array index is a tokenType and
  // the string at that postion is its name. we use this array to map
  // tokenTypes to ColorTheme attribute names in the Xml ColorTheme.
  StringArray names;
  // ColorSchemeAttribute        TokenType
  names.add(T("error"));      // TokenError
  names.add(T("plaintext"));  // TokenPlaintext
  names.add(T("comment"));    // TokenComment
  names.add(T("string"));     // TokenString
  names.add(T("keyword1"));   // TokenSharpsign
  names.add(T("keyword2"));   // TokenLispKeyword
  names.add(T("literal1"));   // TokenLispSpecialForm
  return names;
}

const Colour LispSyntax::getDefaultColour (const int tokenType)
{
  ////  return Colours::black;
  switch (tokenType)
    {
    case TokenError: return Colours::red;
    case TokenComment: return Colour(0xce, 0x00, 0x1a); //Colours::firebrick;
    case TokenString: return Colour(0xa1, 0x11, 0x53); //Colours::rosybrown;
    case TokenPlaintext: return Colours::black;
    case TokenSharpsign: return Colours::cadetblue; // Sharp Sign
    case TokenLispKeyword: return Colour(0x8a, 0x2f, 0x8f); //Colours::orchid;Lisp KeywordColour(0x8a, 0x2f, 0x8f)
    case TokenLispSpecialForm: return Colour(0x95, 0x00, 0x83);  // Special Form/Reserved
    default: return Colours::black;
    }
}

int LispSyntax::readNextToken(CodeDocument::Iterator &source)
{
  ////  source.skipToEndOfLine(); 
  ////  return TokenPlaintext;
  int typ=TokenError;
  source.skipWhitespace();
  tchar chr=source.peekNextChar();
  switch (chr)
    {
    case 0:
      source.skip();
      break;
    case T(';'):
      source.skipToEndOfLine();
      typ=TokenComment;
      break;
    case T('"'):
      {
        juce_wchar c, q=source.nextChar(); // pop quote char
        for (c=source.nextChar(); (c!=q && c!=0); c=source.nextChar())
          if (c==T('\\')) source.skip(); // advance over \x
        typ=TokenString;
      }
      break;
    case T('#'):
      source.skip(); // pop sharp sign
      if (char_token_p(syntab, source.peekNextChar())) // #x #? #t #f etc
        source.skip(); // pop macro char
      typ=TokenSharpsign;
      break;
    case T(','):
    case T('\''):
    case T('`'):
      source.skip();
      typ=TokenPlaintext;
      break;
    case T('('):
    case T(')'):
    case T('{'):
    case T('}'):
    case T('['):
    case T(']'):
      source.skip();
      typ=typ=TokenPlaintext;
      break;
    default:
      {
        // advance to end of token, check for special words
        int i=0;
        String check;
        juce_wchar c, k=0;
        do 
          {
            c=source.nextChar();
            if (i<maxtoklen) // only gather maxtokenlen chars
              check<<c;
            i++;
            k=c;
          } while (char_token_p(syntab, source.peekNextChar()));
        // i is now one beyond last constituent character
        if (chr==':') // first char was lisp keyword 
          typ=TokenLispKeyword;
        else if (i<=maxtoklen) // check for special word
          {
            if (getSynTok(check))
              typ=TokenLispSpecialForm;
            else
              typ=TokenPlaintext;              
          }
        else
          typ=TokenPlaintext;              
      }
    }
  return typ;
}

bool LispSyntax::isTopLevel(String line) {
  // True if line starts with ( in column zero.
  if ( line == String::empty )
    return false;
  else if ( line[0] == '(' )
    return true;
  else return false;
}

int LispSyntax::getIndent(const String text, int bot, int top, int beg)
{
  // determine the standard Lisp indentation column for the line being
  // Tabbed. bot and top are exclusive limits for search. beg is
  // starting position of backwards scan
  int pos=beg;
  int loc, typ, sx1, sx2;
  int open, args, arg1, name;
  int standard_indent;
  SynTok * tok;
  
  // Search backwards for the closest (unbalanced) open paren
  while ( (pos != bot)  )
    {
      typ = scan_sexpr(syntab, text, pos, bot, SCAN_CODE, &loc, NULL);
      pos = loc;
      if (typ == SCAN_UNLEVEL)
	break;
    }
  // if nothing is unbalanced then standard indent is column 0;
  if (typ != SCAN_UNLEVEL)
    {
      //printf("NOTHING UNLEVEL, TYP=%d\n", typ);
      return 0;
    }
  // otherwise pos is now 1 BEFORE nearest leftward open paren
  open=pos+1;
  // see if pos is Quote char. if it does then we are
  // inside a quoted list and the standard indent is open + 1
  if ((pos > bot) && (text[pos] == '\'' )) 
    {
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
  if (typ != SCAN_TOKEN)
    {
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
  if (args == 0)
    {
      standard_indent = column_of(text, open) + tabwidth;
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
  if (typ < 1) 
    {
      standard_indent = column_of(text, name) + tabwidth;
      return standard_indent;
    } 
  // else sx1 now holds a valid starting pos for arg1. if token was
  // not a special form then standard indent is that position
  arg1=sx1;
  if (args < 0) 
    {
      standard_indent = column_of(text, arg1);
      return standard_indent;
    }
  // otherwise we have 1 or more distingushed args. parse forward to
  // see if we have all the distinguished args. if not then standard
  // indent is arg1. if we have all args then standard indent is a
  // "body" indent of open paren + 2.
  for (int i = 1; i<args;i++)
    {
      typ=parse_sexpr(syntab, text, bot, top, 1, SCAN_CODE, 
		      &pos, &sx1, &sx2);    
      if (typ < 1) 
	{
	  standard_indent = column_of(text, arg1);
	  return standard_indent;
	}
    }
  // special form had all its distinguished args, return body indent
  standard_indent = column_of(text, open) + tabwidth;
  return standard_indent;
}

HiliteID LispSyntax::getHilite (const String text, int start, int end)
{
  // determine color of token between start and end in text.
  // LISP:
  // HiliteIDs::Hilite4 = special forms (syntax tokens)
  // HiliteIDs::Hilite5 = lisp keywords
  // HiliteIDs::Hilite6 = constants
  
  if (text[end-1] == ':')  // DSL style keywords (Chicken scheme)
    return HiliteIDs::Hilite5;
  if (text[start] == '#')
    {
      if (((end-start)==2) && ((text[start+1]=='t') ||
			       (text[start+1]=='f') ) )
	return HiliteIDs::Hilite6;
      if (((end-start)>2) && text[start+1]==':')
	return HiliteIDs::Hilite5;
      return HiliteIDs::None;
    }
  else
    if (text[start] == ':' )
      return HiliteIDs::Hilite5;
  
 SynTok* tok = getSynTok(text.substring(start,end));
  if (tok != (SynTok *)NULL)
    return tok->getHilite();
  return HiliteIDs::None;
}

void LispSyntax::eval(String text, bool isRegion, bool expand) 
{
  int typ=SCAN_EMPTY;
  int end=text.length();
  int pos=end-1;
  int old=pos;

  while (pos>-1) 
    {
      typ = scan_sexpr( syntab, text, old, -1, SCAN_CODE, &pos, NULL);
      if (typ<=SCAN_EMPTY)
	break;
      old=pos;
    }
  
  if ( typ==SCAN_EMPTY )
    {
      Console::getInstance()->printWarning( T("Eval: empty selection.\n"));
    }
  else if (typ<SCAN_EMPTY)
    {
      int l1, l2;
      Console::getInstance()->
	printError( T(">>> Error: Lisp eval: unbalanced expression:\n"));
      // print line containing error with ^ marking offending position
      for (l2=old+1; l2<end; l2++)
	if (text[l2]=='\n') break;
      for (l1=old; l1>-1; l1--)
	if (text[l1]=='\n') break;
      l1++;
      Console::getInstance()->printError( text.substring(l1,l2) + T("\n"));
      String mark=String::empty;
      for (int i=l1; i<old; i++)
	mark += T(" ");
      mark += T("^\n");
      Console::getInstance()->printError(mark);
    }
  else
    {
      text=text.substring(pos+1);
      if (expand)
	text=T("(pp (macroexpand (quote ") + text + T(")))");
      if (isRegion)
	text= T("(begin ") + text + T(")");
#ifdef GRACECL
	CommonLisp::getInstance()->eval(text);
#else
	SchemeThread::getInstance()->eval(text);
#endif
    }
}

/*=======================================================================*
                               Sal Syntax
 *=======================================================================*/

SalSyntax::SalSyntax (bool fill) 
  : Syntax( T(""), T(""), T("~!@$%^&*-_=+|:<.>/?"),
	    T(";"), T("#"), T("\""), T("([{"), T(")]})"),
	    T(","), T("\\"))
{
  // SAL Hilites:
  //  HiliteIDs::Hilite4 = commands
  //  HiliteIDs::Hilite5 = clausals/reserved
  //  HiliteIDs::Hilite6 = classes
  //  HiliteIDs::Hilite7 = keywords
  //  HiliteIDs::Hilite8 = lispkeys/constants/#notation

  coloring=true;
  type=TextIDs::Sal;
#ifdef GRACE
  tabwidth=Preferences::getInstance()->getIntProp(T("SalTabWidth"), 2);
#else
  tabwidth=2;
#endif
  hilites[HiliteIDs::String]=Colours::rosybrown;
  hilites[HiliteIDs::Comment]=Colours::firebrick;
  hilites[HiliteIDs::Hilite4]=Colours::blue;
  hilites[HiliteIDs::Hilite5]=Colour(0xa0, 0x20, 0xf0); //Colours::purple;
  hilites[HiliteIDs::Hilite6]=Colours::forestgreen;
  hilites[HiliteIDs::Hilite7]=Colours::orchid;
  hilites[HiliteIDs::Hilite8]=Colours::cadetblue;
  if (fill)
    {
      addSynTok( T("begin"), SalIDs::SalBegin, HiliteIDs::Hilite5);
      addSynTok( T("chdir"), SalIDs::SalChdir, HiliteIDs::Hilite5);
      addSynTok( T("define"), SalIDs::SalDefine, HiliteIDs::Hilite5);
      addSynTok( T("else"), SalIDs::SalElse, HiliteIDs::Hilite5);
      addSynTok( T("end"), SalIDs::SalEnd, HiliteIDs::Hilite5);
      addSynTok( T("exec"), SalIDs::SalExec, HiliteIDs::Hilite5);
      addSynTok( T("fomusfile"), SalIDs::SalFomusFile, HiliteIDs::Hilite5);
      addSynTok( T("if"), SalIDs::SalIf, HiliteIDs::Hilite5);
      addSynTok( T("load"), SalIDs::SalLoad, HiliteIDs::Hilite5);
      addSynTok( T("loop"), SalIDs::SalLoop, HiliteIDs::Hilite5);
      addSynTok( T("plot"), SalIDs::SalPlot, HiliteIDs::Hilite5);
      addSynTok( T("print"), SalIDs::SalPrint, HiliteIDs::Hilite5);
      addSynTok( T("return"), SalIDs::SalReturn, HiliteIDs::Hilite5);
      addSynTok( T("run"), SalIDs::SalRun, HiliteIDs::Hilite5);
      addSynTok( T("send"), SalIDs::SalSend, HiliteIDs::Hilite5);
      addSynTok( T("set"), SalIDs::SalSet, HiliteIDs::Hilite5);
      addSynTok( T("soundfile"), SalIDs::SalSoundFile, HiliteIDs::Hilite5);
      addSynTok( T("sprout"), SalIDs::SalSprout, HiliteIDs::Hilite5);
      addSynTok( T("then"), SalIDs::SalThen, HiliteIDs::Hilite5);
      addSynTok( T("unless"), SalIDs::SalUnless, HiliteIDs::Hilite5);
      addSynTok( T("until"), SalIDs::SalUntil, HiliteIDs::Hilite5);
      addSynTok( T("wait"), SalIDs::SalWait, HiliteIDs::Hilite5);
      addSynTok( T("when"), SalIDs::SalWhen, HiliteIDs::Hilite5);
      addSynTok( T("while"), SalIDs::SalWhile, HiliteIDs::Hilite5);
      addSynTok( T("with"), SalIDs::SalWith, HiliteIDs::Hilite5);
      addSynTok( T("process"), SalIDs::SalProcess, HiliteIDs::Hilite6);
      addSynTok( T("function"), SalIDs::SalFunction, HiliteIDs::Hilite6);
      addSynTok( T("variable"), SalIDs::SalVariable, HiliteIDs::Hilite6);
 
      addSynTok( T("above"), SalIDs::SalAbove, HiliteIDs::Hilite5);
      addSynTok( T("below"), SalIDs::SalBelow, HiliteIDs::Hilite5);
      addSynTok( T("by"), SalIDs::SalBy, HiliteIDs::Hilite5);
      addSynTok( T("downto"), SalIDs::SalDownto, HiliteIDs::Hilite5);
      addSynTok( T("finally"), SalIDs::SalFinally, HiliteIDs::Hilite5);
      addSynTok( T("for"), SalIDs::SalFor, HiliteIDs::Hilite5);
      addSynTok( T("from"), SalIDs::SalFrom, HiliteIDs::Hilite5);
      addSynTok( T("in"), SalIDs::SalIn, HiliteIDs::Hilite5);
      addSynTok( T("over"), SalIDs::SalOver, HiliteIDs::Hilite5);
      addSynTok( T("repeat"), SalIDs::SalRepeat, HiliteIDs::Hilite5);
      addSynTok( T("to"), SalIDs::SalTo, HiliteIDs::Hilite5);

      //  Operators, data field is op weight
      addSynTok( T("|"), SalIDs::SalOr, HiliteIDs::None);
      addSynTok( T("&"), SalIDs::SalAnd, HiliteIDs::None);
      addSynTok( T("!"), SalIDs::SalNot, HiliteIDs::None);
      addSynTok( T("="), SalIDs::SalEqual, HiliteIDs::None); // relation and op
      addSynTok( T("!="), SalIDs::SalNotEqual, HiliteIDs::None);  
      addSynTok( T("<"), SalIDs::SalLess, HiliteIDs::None);
      addSynTok( T(">"), SalIDs::SalGreater, HiliteIDs::None);
      addSynTok( T("<="), SalIDs::SalLessEqual, HiliteIDs::None); // relation and op
      addSynTok( T(">="), SalIDs::SalGreaterEqual, HiliteIDs::None); // relation and op
      addSynTok( T("~="), SalIDs::SalGeneralEqual, HiliteIDs::None);  
      addSynTok( T("+"), SalIDs::SalPlus, HiliteIDs::None);
      addSynTok( T("-"), SalIDs::SalMinus, HiliteIDs::None);
      addSynTok( T("%"), SalIDs::SalMod, HiliteIDs::None);
      addSynTok( T("*"), SalIDs::SalTimes, HiliteIDs::None);  
      addSynTok( T("/"), SalIDs::SalDivide, HiliteIDs::None);
      addSynTok( T("^"), SalIDs::SalExpt, HiliteIDs::None);
      // assignment (also: = <= >=)
      addSynTok( T("+="), SalIDs::SalInc, HiliteIDs::None);
      addSynTok( T("*="), SalIDs::SalMul, HiliteIDs::None);
      addSynTok( T("&="), SalIDs::SalCol, HiliteIDs::None);
      addSynTok( T("@="), SalIDs::SalPre, HiliteIDs::None);  
      addSynTok( T("^="), SalIDs::SalApp, HiliteIDs::None);
      // hash tokens
      addSynTok( T("#t"), SalIDs::SalTrue, HiliteIDs::Hilite8);
      addSynTok( T("#f"), SalIDs::SalFalse, HiliteIDs::Hilite8);
      addSynTok( T("#?"), SalIDs::SalQMark, HiliteIDs::Hilite8);
      addSynTok( T("#$"), SalIDs::SalUnquote, HiliteIDs::Hilite8);
      addSynTok( T("#^"), SalIDs::SalSplice, HiliteIDs::Hilite8);
    }
}

SalSyntax::~SalSyntax()
{
  clearSingletonInstance();
}

const StringArray SalSyntax::getTokenTypes ()
{
  // juce's CodeEditorComponent uses this array to name the
  // Tokenizer's tokenTypes, where each array index is a tokenType and
  // the string at that postion is its name. we use this array to map
  // tokenTypes to ColorTheme attribute names in the Xml ColorTheme.
  StringArray names;
  // ColorSchemeAttribute        TokenType
  names.add(T("error"));      // TokenError
  names.add(T("plaintext"));  // TokenPlaintext
  names.add(T("comment"));    // TokenComment
  names.add(T("string"));     // TokenString
  names.add(T("keyword1"));   // TokenSharpsign
  names.add(T("keyword2"));   // TokenLispKeyword
  names.add(T("keyword3"));   // TokenSalKeyword
  names.add(T("literal1"));   // TokenSalReserved
  names.add(T("literal2"));   // TokenSalClassname
  names.add(T("literal3"));   // TokenSalCommand
  return names;
}

const Colour SalSyntax::getDefaultColour (const int tokenType)
{
  ////  return Colours::black;
  switch (tokenType)
    {
    case SalIDs::TokenError: return Colours::red;
    case SalIDs::TokenPlaintext: return Colours::black;
    case SalIDs::TokenComment: return Colour(0xce, 0x00, 0x1a); //Colours::firebrick;
    case SalIDs::TokenString: return Colour(0xa1, 0x11, 0x53); //Colours::rosybrown;
    case SalIDs::TokenSharpSign: return Colours::cadetblue; 
    case SalIDs::TokenLispKeyword: return Colour(0x8a, 0x2f, 0x8f); // Lisp Keyword Colours::cadetblue
    case SalIDs::TokenSalKeyword: return Colours::orchid; 
    case SalIDs::TokenSalReserved: return Colour(0x95, 0x00, 0x83);
    case SalIDs::TokenSalClassname: return Colours::forestgreen;
    case SalIDs::TokenSalCommand: return Colours::blue; 
    default: return Colours::black;
    }
}

int SalSyntax::readNextToken(CodeDocument::Iterator &source)
{
  ////  source.skipToEndOfLine(); 
  ////  return SalIDs::TokenPlaintext;
  int typ=SalIDs::TokenError;
  //source.skipWhitespace();
  tchar chr=0;
  while (source.peekNextChar() && char_white_p(syntab, source.peekNextChar()))
    chr=source.nextChar();
  bool newline=(chr==T('\n'));
  chr=source.peekNextChar();
  switch (chr)
    {
    case 0:
      source.skip();
      break;
    case T(';'):
      source.skipToEndOfLine();
      typ=SalIDs::TokenComment;
      break;
    case T('"'):
      {
        juce_wchar c, q=source.nextChar(); // pop quote char
        for (c=source.nextChar(); (c!=q && c!=0); c=source.nextChar())
          if (c==T('\\')) source.skip(); // advance over \x
        typ=SalIDs::TokenString;
      }
      break;
    case T('#'):
      source.skip(); // pop sharp sign
      if (char_token_p(syntab, source.peekNextChar())) // #x #? #t #f etc
        source.skip(); // pop macro char
      typ=SalIDs::TokenSharpSign;
      break;
    case T(','):
      source.skip();
      typ=SalIDs::TokenPlaintext;
      break;
    case T('('):
    case T(')'):
    case T('{'):
    case T('}'):
    case T('['):
    case T(']'):
      source.skip();
      typ=SalIDs::TokenPlaintext;
      break;
    case T('\''):
      source.skip();
      typ=SalIDs::TokenError;
      break;
    default:
      {
        int p=source.getPosition();
        int i=0;
        // check for special syntax words
        String check;
        juce_wchar c, k=0;
        // read until a non-constituent char is in next position
        // adding consituent chars to check as long as they fit
        do
          {
            c=source.nextChar();
            if (i<maxtoklen) // only gather maxtokenlen chars
              check<<c;
            i++;
            k=c;
          } 
        while (char_token_p(syntab, source.peekNextChar()));

        // i is now one beyond last constituent character
        if (chr==T(':')) // first char was lisp keyword 
          typ=SalIDs::TokenLispKeyword;
        else if (k==T(':')) // sal keyword 
          typ=SalIDs::TokenSalKeyword;
        else if (i<=maxtoklen) // check for special word
          {
            SynTok* tok=getSynTok(check);
            if (tok)
              {
                int ttyp=tok->getType();
                //std::cout << "linestart=" << newline << "literal=" << check.toUTF8() << "\n";
                if (newline && (SalIDs::isSalCommandType(ttyp) || ttyp==SalIDs::SalEnd))
                  {
                    typ=SalIDs::TokenSalCommand;                    
                  }
                else if (SalIDs::isSalDefineType(ttyp)) // classname
                  typ=SalIDs::TokenSalClassname;
                else if (SalIDs::isSalLiteralType(ttyp))
                  typ=SalIDs::TokenSalReserved;
                else
                  typ=SalIDs::TokenPlaintext;
              }
            else
              typ=SalIDs::TokenPlaintext;
          }
        else
          typ=SalIDs::TokenPlaintext;
      }
    }
  return typ;
}

bool SalSyntax::isTopLevel(String line) {
  // true if line starts with a top level command.
  if ( line == String::empty )
    return false;
  int end=skip_syntax(syntab, line, T("w"), 0, line.length() );
  if ( end > 0 ) {
    SynTok * tok = getSynTok(line.substring(0,end));
    if ( (tok != (SynTok *)NULL) && SalIDs::isSalCommandType(tok->getType()) )
      return true;
    else return false;
  }
  else return false;
}

int lineIndent(const String str, int bot, int top, int pos)
{
}

int SalSyntax::isSalStatement(const String name)
{return 0;}

int SalSyntax::backwardSal(const String text, int bot, int top,
			   int *poz, int *sal)
{return -1;}

int SalSyntax::getIndent(const String text, int bot, int top, int poz)
{return 0;}

HiliteID SalSyntax::getHilite (const String text, int start, int end)
{return 0;}

void SalSyntax::eval(String text, bool isRegion, bool expand)
{}

/*=======================================================================*
                               Sal2 Syntax
 *=======================================================================*/

Sal2Syntax::Sal2Syntax () 
  : Syntax( T(""), T(""), T("~!@$%^&*-_=+|:<.>/?"),
	    T(";"), T("#"), T("\""), T("([{"), T("}])"),
	    T(","), T("\\"))
{
  type=TextIDs::Sal2;
  //        NAME       TYPE              BLOCKINDENT?  NUMDISTINGUISHED
  addSynTok(T("begin"), SalIDs::SalBegin,        1, 0); // #b01 = +body indent
  addSynTok(T("end"), SalIDs::SalEnd,            2, 0); // #b10 = -body indent
  addSynTok(T("function"), SalIDs::Sal2Function, 1, 2);
  addSynTok(T("process"), SalIDs::Sal2Process,   1, 2);
  addSynTok(T("if"), SalIDs::Sal2If,             1, 2);
  addSynTok(T("loop"), SalIDs::SalLoop,          1, 0);
  addSynTok(T("file"), SalIDs::Sal2File,         1, 2);
  ////addSynTok(T("return"), SalIDs::SalReturn, HiliteIDs::Hilite4);
  addSynTok(T("run"), SalIDs::SalRun,            1, 0);
  ////addSynTok(T("send"), SalIDs::SalSet, HiliteIDs::Hilite4);
  addSynTok(T("set"), SalIDs::SalSet);
  addSynTok(T("variable"), SalIDs::Sal2Variable);
  addSynTok(T("wait"), SalIDs::Sal2Wait);
  // loop/run/if clausals
  addSynTok(T("above"), SalIDs::SalAbove);
  addSynTok(T("below"), SalIDs::SalBelow);
  addSynTok(T("by"), SalIDs::SalBy);
  addSynTok(T("downto"), SalIDs::SalDownto);
  addSynTok(T("else"), SalIDs::SalElse,          3, 0); // #b11= -this +next
  addSynTok(T("finally"), SalIDs::SalFinally);
  addSynTok(T("for"), SalIDs::SalFor);
  addSynTok(T("from"), SalIDs::SalFrom);
  addSynTok(T("in"), SalIDs::SalIn);
  addSynTok(T("over"), SalIDs::SalOver);
  addSynTok(T("repeat"), SalIDs::SalRepeat);
  addSynTok(T("then"), SalIDs::SalThen);
  addSynTok(T("to"), SalIDs::SalTo);
  addSynTok(T("unless"), SalIDs::SalUnless);
  addSynTok(T("until"), SalIDs::SalUntil);
  //  addSynTok(T("wait"), SalIDs::SalWait);
  addSynTok(T("when"), SalIDs::SalWhen);
  addSynTok(T("while"), SalIDs::SalWhile);
  addSynTok(T("with"), SalIDs::SalWith);
  addSynTok(T("&optkey"), SalIDs::SalOptKey);
  //  Operators, data field is op weight
  addSynTok(T("|"), SalIDs::SalOr);
  addSynTok(T("&"), SalIDs::SalAnd);
  addSynTok(T("!"), SalIDs::SalNot);
  addSynTok(T("="), SalIDs::SalEqual);
  addSynTok(T("!="), SalIDs::SalNotEqual);  
  addSynTok(T("<"), SalIDs::SalLess);
  addSynTok(T(">"), SalIDs::SalGreater);
  addSynTok(T("<="), SalIDs::SalLessEqual);
  addSynTok(T(">="), SalIDs::SalGreaterEqual);
  addSynTok(T("~="), SalIDs::SalGeneralEqual);  
  addSynTok(T("+"), SalIDs::SalPlus);
  addSynTok(T("-"), SalIDs::SalMinus);
  addSynTok(T("%"), SalIDs::SalMod);
  addSynTok(T("*"), SalIDs::SalTimes);  
  addSynTok(T("/"), SalIDs::SalDivide);
  addSynTok(T("^"), SalIDs::SalExpt);
  // assignment (also: = <= >=)
  addSynTok(T("+="), SalIDs::SalInc);
  addSynTok(T("*="), SalIDs::SalMul);
  addSynTok(T("&="), SalIDs::SalCol);
  addSynTok(T("@="), SalIDs::SalPre);  
  addSynTok(T("^="), SalIDs::SalApp);
  // hash tokens
  addSynTok(T("#t"), SalIDs::SalTrue);
  addSynTok(T("#f"), SalIDs::SalFalse);
  addSynTok(T("#?"), SalIDs::SalQMark);
  addSynTok(T("#$"), SalIDs::SalUnquote);
  addSynTok(T("#^"), SalIDs::SalSplice);
}

Sal2Syntax::~Sal2Syntax () 
{
  clearSingletonInstance();
}

const StringArray Sal2Syntax::getTokenTypes ()
{
  // juce's CodeEditorComponent uses this array to name the
  // Tokenizer's tokenTypes, where each array index is a tokenType and
  // the string at that postion is its name. we use this array to map
  // tokenTypes to ColorTheme attribute names in the Xml ColorTheme.
  StringArray names;
  // ColorSchemeAttribute        TokenType
  names.add(T("error"));      // TokenError
  names.add(T("plaintext"));  // TokenPlaintext
  names.add(T("comment"));    // TokenComment
  names.add(T("string"));     // TokenString
  names.add(T("keyword1"));   // TokenSharpsign
  names.add(T("keyword2"));   // TokenLispKeyword
  names.add(T("keyword3"));   // TokenSalKeyword
  names.add(T("literal1"));   // TokenSalReserved
  return names;
}

const Colour Sal2Syntax::getDefaultColour (const int tokenType)
{
  ////  return Colours::black;
  switch (tokenType)
    {
    case SalIDs::TokenError: return Colours::red;
    case SalIDs::TokenPlaintext: return Colours::black;
    case SalIDs::TokenComment: return Colour(0xce, 0x00, 0x1a); //Colours::firebrick;
    case SalIDs::TokenString: return Colour(0xa1, 0x11, 0x53); //Colours::rosybrown;
    case SalIDs::TokenSharpSign: return Colours::cadetblue; 
    case SalIDs::TokenLispKeyword: return Colour(0x8a, 0x2f, 0x8f); // Lisp Keyword Colours::cadetblue
    case SalIDs::TokenSalKeyword: return Colours::orchid; 
    case SalIDs::TokenSalReserved: return Colour(0x95, 0x00, 0x83);
    default: return Colours::black;
    }
}

int Sal2Syntax::readNextToken(CodeDocument::Iterator &source)
{
  ////  source.skipToEndOfLine(); 
  ////  return SalIDs::TokenPlaintext;
  int typ=SalIDs::TokenError;
  source.skipWhitespace();
  tchar chr=source.peekNextChar();
  switch (chr)
    {
    case 0:
      source.skip();
      break;
    case T(';'):
      source.skipToEndOfLine();
      typ=SalIDs::TokenComment;
      break;
    case T('"'):
      {
        juce_wchar c, q=source.nextChar(); // pop quote char
        for (c=source.nextChar(); (c!=q && c!=0); c=source.nextChar())
          if (c==T('\\')) source.skip(); // advance over \x
        typ=SalIDs::TokenString;
      }
      break;
    case T('#'):
      source.skip(); // pop sharp sign
      if (char_token_p(syntab, source.peekNextChar())) // #x #? #t #f etc
        source.skip(); // pop macro char
      typ=SalIDs::TokenSharpSign;
      break;
    case T(','):
      source.skip();
      typ=SalIDs::TokenPlaintext;
      break;
    case T('('):
    case T(')'):
    case T('{'):
    case T('}'):
    case T('['):
    case T(']'):
      source.skip();
      typ=SalIDs::TokenPlaintext;
      break;
    case T('\''):
      source.skip();
      typ=SalIDs::TokenError;
      break;
    default:
      {
        // at this point char is a token char. read until next
        // position is a non-token char, adding consituent chars to
        // check as long as position is not greater than the longest
        // literal to check
        int i=0;
        String check=String::empty;
        juce_wchar c, k=0;
        do
          {
            c=source.nextChar();
            if (i<maxtoklen) // only gather maxtokenlen chars
              check<<c;
            i++;
            k=c;
          } 
        while (char_token_p(syntab, source.peekNextChar()));
        // i is now one beyond last constituent character
        if (chr==T(':')) // lisp style (first char)
          typ=SalIDs::TokenLispKeyword;
        else if (k==T(':')) // sal style (last char)
          typ=SalIDs::TokenSalKeyword;
        else if (i<=maxtoklen)
          {
            SynTok* tok=getSynTok(check);
            if (tok && SalIDs::isSalLiteralType(tok->getType()))
              typ=SalIDs::TokenSalReserved;
            else
              typ=SalIDs::TokenPlaintext;              
          }
        else
          typ=SalIDs::TokenPlaintext;              
      }
    }
  return typ;
}
