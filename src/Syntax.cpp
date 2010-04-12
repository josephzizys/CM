/*=======================================================================*
  Copyright (c) 2008-2010 Rick Taube.                                        
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

Syntax::Syntax() 
  : numtoks (0),
    maxtoklen (0),
    type (TextIDs::Empty)
{
  // initialize table to WHITE
  for (int i=0; i<128; i++) syntab[i]=ScanIDs::SYN_WHITE;
  // alpha and digits default to WORD
  for (int i='0'; i<='9'; i++) syntab[i]=ScanIDs::SYN_WORD;
  for (int i='A'; i<='Z'; i++) syntab[i]=ScanIDs::SYN_WORD;
  for (int i='a'; i<='z'; i++) syntab[i]=ScanIDs::SYN_WORD;
  // initialize colors to black
  for (int i=0; i<ColorThemeIDs::MAXTOKENCOLORS; i++)
    colors[i]=Colours::black;
}

Syntax::~Syntax()
{
}

void Syntax::addSynTok (const String n, int t, int a, int b, int c) 
{
  numtoks++;
  int l=n.length();
  if (l>maxtoklen) maxtoklen=l;
  tokens[n] = new SynTok(n, t, a, b, c);
}

Syntax::SynTok* Syntax::getSynTok (String n) 
{
  SynTokMap::iterator iter = tokens.find(n);
  if ( iter == tokens.end() )
    return NULL;
  return iter->second;
}

//
///  Char Syntax Methods
//

void Syntax::setCharSyntax (const String chrs, const int syn)
{
  for (int i=0; i<chrs.length(); i++)
    if (chrs[i]<128)
      syntab[chrs[i]] = syn;
    else
      std::cout << "setCharSyntax: WARNING: index [" << i << "] in \"" << chrs.toUTF8() << "\" is > 127!\n";
}

bool Syntax::isWhiteChar (const char c)
{
  return (syntab[(c & 0x7f)] == ScanIDs::SYN_WHITE);
}

bool Syntax::isWordChar (const char c)
{
  return (syntab[(c & 0x7f)] == ScanIDs::SYN_WORD);
}

bool Syntax::isSymbolChar (const char c)
{
  return (syntab[(c & 0x7f)] == ScanIDs::SYN_SYMBOL);
}

bool Syntax::isTokenChar (const char c)
{
  int s=syntab[(c & 0x7f)];
  return (s == ScanIDs::SYN_WORD || s == ScanIDs::SYN_SYMBOL || s == ScanIDs::SYN_ESCAPE);
}

bool Syntax::isCommentChar (const char c)
{
  return (syntab[(c & 0x7f)] == ScanIDs::SYN_COMMENT);
}

bool Syntax::isPrefixChar (const char c)
{
  return (syntab[(c & 0x7f)] == ScanIDs::SYN_PREFIX);
}

bool Syntax::isStringChar (const char c)
{
  return (syntab[(c & 0x7f)] == ScanIDs::SYN_STRING);
}

bool Syntax::isOpenChar (const char c)
{
  return (syntab[(c & 0x7f)] == ScanIDs::SYN_OPEN);
}

bool Syntax::isCloseChar (const char c)
{
  return (syntab[(c & 0x7f)] == ScanIDs::SYN_CLOSE);
}

bool Syntax::isPunctuationChar (const char c)
{
  return (syntab[(c & 0x7f)] == ScanIDs::SYN_PUNCT);
}

bool Syntax::isEscapeChar (const char c)
{
  return (syntab[(c & 0x7f)] == ScanIDs::SYN_ESCAPE);
}

/*=======================================================================*
                              Syntactic Text Scanning
 *=======================================================================*/

bool Syntax::lookingAt(const CodeDocument::Position pos, const String text, const bool forward, const bool delimited)
{
  // return true if document matches text starting at pos, which must
  // be ON the first char to check. if delimited is true then the text
  // must match as a delimited word.
  CodeDocument::Position at (pos);
  int len=text.length();
  if (forward)
    {
      CodeDocument::Position end(pos);
      end.setPosition(INT_MAX);
      int i=0;
      for ( ; i<len && at!=end; i++)
        {
          //String str=T("comparing ");
          //str << at.getCharacter() << T("&") << text[i] << T("\n");
          //std::cout << str.toUTF8();
        if (at.getCharacter() != text[i])
          return false;
        else
          at.moveBy(1);
        }
      //std::cout << "done, i==len: " << (i==len) << " at==end: "  << (at==end) << "\n";
      if (i==len)
        return (delimited) ? ((at==end) || !isTokenChar(at.getCharacter())) : true;
      return false;
    }
  else
    {
      CodeDocument::Position end (pos);
      end.setPosition(0);
      bool b=false;
      int i=len-1;
      for ( ; i>=0; i--)
        if (at.getCharacter() != text[i])
          return false;
        // at this point we've matched at position i
        else if (at==end)
          {
            i--;    // still increment i
            b=true; // note we matched at bob
            break;
          }
        else at.moveBy(-1);

      if (i<0 )
        return (delimited) ? (b || !isTokenChar(at.getCharacter())) : true;
      return false;
    }
}

bool Syntax::isCommaTerminatedLine(CodeDocument& document, int line)
{
  // quick and dirty test for line ending with comma. doesnt check for
  // () or "" nesting etc
  CodeDocument::Position b (&document, line, 0);
  CodeDocument::Position e (&document, line, INT_MAX);
  bool x=false;
  while (b != e)
    {
      const tchar c=b.getCharacter();
      if (c==T(',')) x=true;
      else if (isCommentChar(c)) break;
      else if (isWhiteChar(c)) ;
      else x=false;
      b.moveBy(1);
    }
  return x;
}  

int Syntax::isNumberToken(const String str) 
{
  // returns 0==nan, 1==int, 2==float, 3==ratio
  int len=str.length();
  int typ=0, dot=0, div=0, dig=0;
  for (int pos=0; pos<len; pos++) 
    switch ( str[pos] )
      {
      case T('-') :
      case T('+') :
        if (pos>0) return 0; // not in leading position
        break;
      case T('.') :
        if (dot>0) return 0; // too many dots
        if (div>0) return 0; // in ratio
        dot++;
        break;
      case T('/') :
        if (div>0) return 0; // too many divs
        if (dig==0) return 0; // no digit yet
        if (dot>0) return 0;  // float already
        if (pos==len-1) return 0; // at end
        div++;
        break;
      case T('0') :
      case T('1') :
      case T('2') :
      case T('3') :
      case T('4') :
      case T('5') :
      case T('6') :
      case T('7') :
      case T('8') :
      case T('9') :
        dig++;
        break;
      default:
        return 0;
      }
  if (div) return 3;
  if (dot) return 2; 
  return 1;
}

int Syntax::lastIndented(CodeDocument& document, Array<int>& starts, bool index)
{
  // search array of ordered expression start positions to return the
  // indentation column (OR array index) of the LATEST postion that is
  // the first expression in its line. otherwise return the position
  // of the very first expr if there isn't a latest one
  int size=starts.size();
  if (size==0) return -1; // -1 for error either way
  else if (size==1) // if only one expr use it
    {
      CodeDocument::Position a (&document, starts[0]);
      return (index) ? 0 : a.getIndexInLine();
    }
  else
    // compare line numbers of each start to find latest expr that
    // starts a line
    {
      int i=0;
      for (i=starts.size()-1; i>0; i--)
        {
          CodeDocument::Position a (&document, starts[i-1]);
          CodeDocument::Position b (&document, starts[i]);
          // if the i-1 expr is on an earlier line then THIS expr
          // starts a line
          if (a.getLineNumber() < b.getLineNumber())
            break;
        }
      CodeDocument::Position a (&document, starts[i]);
      return (index) ? i : a.getIndexInLine();
    }
}

bool Syntax::scanToken(CodeDocument::Position& pos, const int dir, const CodeDocument::Position end)
{
  // scan while position is on a token
  bool token=false;
  bool atend=false;
  while (!atend && isTokenChar(pos.getCharacter()))
    {
      token=true;
      pos.moveBy(dir);
      if (pos==end) atend=true;
    }
  // pos is now on delim or at End. If not at end then check to see if
  // the delim is escaped. if it is then continue searching
  if (atend)
    return token;
  if (isEscapeChar(pos.movedBy(-1).getCharacter()))
    {
      pos.moveBy(dir);
      return scanToken(pos,dir, end);
    }
  else
    return token;
}

bool Syntax::scanCharacter(tchar chr, CodeDocument::Position& pos, const int dir, 
                           const CodeDocument::Position end)
{
  // scan for character, if found leave pos on the char's position and
  // return true otherwise return false
  bool found=false;
  bool atend=false;
  CodeDocument::Position check (pos);
  while (!atend)
    {
      if (check.getCharacter()==chr)
        {
          if (check.movedBy(-1).getCharacter()==T('\\'))
            check.moveBy(dir);
          else
            {
              found=true;
              atend=true;
            }
        }
      else if (check==end)
        atend=true;
      else
        check.moveBy(dir);
    }
  if (found)
    pos.setLineAndIndex(check.getLineNumber(),check.getIndexInLine());
  return found;
}

bool Syntax::scanPrefix(CodeDocument::Position& pos, const int dir, 
                        const CodeDocument::Position end)
{
  bool prefix=false;
  while (isPrefixChar(pos.getCharacter()))
    {
      prefix=true;
      if (pos==end) break;
      pos.moveBy(dir);
    }
  return prefix;
}

int Syntax::scanCode(CodeDocument& document, CodeDocument::Position& pos,
                     bool forward, int mode, int limit)
{
  #define ISLEVEL(a,b,c,d) (((a)==0)&&((b)==0)&&((c)==0)&&((d)==0))
  #define CURLY_CHAR_P(c) (( (c) == T('{')) || ( (c) == T('}')))
  #define SQUARE_CHAR_P(c) (( (c) == T('[')) || ( (c) == T(']')))
  #define PAREN_CHAR_P(c) (( (c) == T('(')) || ( (c) == T(')')))

  int typ = ScanIDs::SCAN_EMPTY;
  int dir=(forward) ? 1 : -1;
  int par=0, sqr=0, cur=0, ang=0;
  bool atfirst=false;
  CodeDocument::Position end (&document,0);  // Initialize to start of buffer
  if (limit==-1)
    {
      if (forward)
        end.setPosition(INT_MAX);
    }
  else
    end.setPosition(limit);

  while (true)
    {
      if (pos==end)
        {
          if (forward) // we've moved past the last char
            break;
          else if (!atfirst) // we're checking the first char
            atfirst=true;
          else // we've already checked the first char
            break;
        }
      tchar chr=pos.getCharacter();
      // WHITE SPACE. advance one position
      if (isWhiteChar(chr))
        {  
          pos.moveBy(dir);
        }
      // COMMENT CHAR. advance forward eol or backward one char
      else if (isCommentChar(chr))
        {
          if (forward)
            //scanEOL(pos);
            pos.setLineAndIndex(pos.getLineNumber(),INT_MAX);

          else
            pos.moveBy(dir);
        }
      // MAYBE MOVING BACKWARD IN A COMMENT LINE
      else if ((!forward) &&
               scanCharacter(T(';'), // FIXME!
                             pos, dir, 
                             CodeDocument::Position(&document, 
                                                    pos.getLineNumber(),
                                                    0)))
        {
          pos.moveBy(dir); // move one beyond the comment character
        }
      // SKIP WHITE/COMMENTS. char now not white or part of comment
      else if (mode==ScanIDs::MoveWhiteAndComments)
        {
          break;
        }
      // TOKEN CHAR. scan out token
      else if (isTokenChar(chr))
        {
          scanToken(pos,dir,end);
          // pos is now either one beyond token or at BOB and on
          // the token start. quit scanning if at top level
          if (ISLEVEL(par,cur,sqr,ang) )
            {
              if (!forward) scanPrefix(pos,dir,end); // include any prefix chars
              typ = ScanIDs::SCAN_TOKEN;
              break;
            }
        }
      // STRING START.  scan for end of string char
      else if (isStringChar(chr))
        {
          CodeDocument::Position check=pos.movedBy(dir);
          if (check==end)
            {
              typ=ScanIDs::SCAN_MISMATCH;
              break;
            }
          pos.moveBy(dir); // advance position one beyond first "
          if (scanCharacter(T('\"'), pos, dir, end))
            {
              // now on end of string advance pos one past that char
              // 
              if (/*!forward &&*/ (pos!=end))  pos.moveBy(dir);
              if (ISLEVEL(par,cur,sqr,ang)) 
                {
                  typ = ScanIDs::SCAN_STRING;
                  break;
                }
            }
          else
            {
              // missing end of string char, return error
              typ=ScanIDs::SCAN_UNMATCHED;
              break;
            }
        }
      // PUNCTUATION. keep going unless toplevel (was token mode)
      else if (isPunctuationChar(chr))
        {
          pos.moveBy(dir);
          if (ISLEVEL(par,cur,sqr,ang)) //(mode==ScanIDs::MoveTokens) 
            {
              typ=ScanIDs::SCAN_PUNCT;
              break;
            }
        }
      // PREFIX. keep going
      else if (isPrefixChar(chr) ) 
        {
          pos.moveBy(dir);
        }
      // OPEN PARENS TOKEN
      else if ((mode==ScanIDs::MoveTokens) && isOpenChar(chr) )
        {
          pos.moveBy(dir);
          typ=ScanIDs::SCAN_OPEN;
          break;
        }
      // CLOSE PARENS TOKEN
      else if ((mode==ScanIDs::MoveTokens) && isCloseChar(chr) )
        {
          pos.moveBy(dir);
          typ=ScanIDs::SCAN_CLOSE;
          break;
        }
      // OPEN PARENS EXPRESSION. increment level of paren.
      else if ((forward && isOpenChar(chr) ) ||
               (!forward && isCloseChar(chr)))
        {
          if ( PAREN_CHAR_P(chr) ) par++;
          else if ( CURLY_CHAR_P(chr) ) cur++;
          else if ( SQUARE_CHAR_P(chr) ) sqr++;
          pos.moveBy(dir);
        }
      // CLOSE PARENS EXPRESSION. decrement level, stop if level zero
      else if ((forward && isCloseChar(chr)) ||
               (!forward && isOpenChar(chr))) 
        {
          if (PAREN_CHAR_P(chr)) 
            if (par==0) typ = ScanIDs::SCAN_UNLEVEL; else par--;
          else if (CURLY_CHAR_P(chr)) 
            if (cur==0) typ = ScanIDs::SCAN_UNLEVEL; else cur--;
          else if (SQUARE_CHAR_P(chr)) 
            if (sqr==0) typ = ScanIDs::SCAN_UNLEVEL; else sqr--;
          if (typ==ScanIDs::SCAN_UNLEVEL)
            {
              break;
            }
          else if (ISLEVEL(par,cur,sqr,ang))
            {
              pos.moveBy(dir);
              if (!forward) scanPrefix(pos,dir,end); // include any prefix chars
              typ = ScanIDs::SCAN_LIST;
              break;
            }
          else
            {
              pos.moveBy(dir);
            }
        }
      else
        {
          typ=ScanIDs::SCAN_MISMATCH;
          break;
        } 
    } // end while

  //std::cout << "pos="<<pos.getPosition()<< ",typ="<<typ<<",isfirst="<<atfirst<<"\n";
  //std::cout << "after scan, par=" << par << "\n";
  // move pos back to the first char if backward scan

  if (typ<0) 
    ;
  else if (ISLEVEL(par,cur,sqr,ang))
    {
      // if we are moving backwards then our position is now either
      // one BEFORE the start of the expression OR we are on the first
      // character and that character is part of the expression
      if //(!forward && !atfirst && typ>0) //pos!=end
        (!forward &&  typ>0 &&
         ((pos==end && isWhiteChar(pos.getCharacter())) ||
          (pos!=end )    )      
         )
        {
          //std::cout << "incrementing pos\n";
          pos.moveBy(1);
        }
    }
  else
    typ=ScanIDs::SCAN_UNMATCHED;
  return typ;
}

/*=======================================================================*
                              Text Syntax
 *=======================================================================*/

TextSyntax::TextSyntax () 
  : Syntax()
{
  type=TextIDs::Text;

  setCharSyntax(T("~@#$%^&*-_=+|<>/"), ScanIDs::SYN_SYMBOL);
  setCharSyntax(T("\""), ScanIDs::SYN_STRING);
  setCharSyntax(T("([{"), ScanIDs::SYN_OPEN);
  setCharSyntax(T(")]}"), ScanIDs::SYN_CLOSE);
  setCharSyntax(T(",.!?;:'`\\"), ScanIDs::SYN_PUNCT);
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
  // for attributes see ColorThemeIDs class in Enumerations.h

  StringArray names;

  // Color Theme Attribute       Token Type
  //-------------------------------------------
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

int TextSyntax::getIndentation(CodeDocument& document, int line)
{
  // -1 means no special syntactic indentation (normal tabbing)
  return -1;
}

int TextSyntax::backwardExpr(CodeDocument& document, CodeDocument::Position& start, CodeDocument::Position& end)
{
  // 0 means no backward expression parsing
  return 0;
}
void TextSyntax::eval(CodeDocument& document, const CodeDocument::Position start, const CodeDocument::Position end, bool expand, bool region)
{
  // no expression evaluation or macro expansion
}

/*=======================================================================*
                              Lisp Syntax
 *=======================================================================*/

LispSyntax::LispSyntax () 
  : Syntax()
{
  type=TextIDs::Lisp;

  setCharSyntax(T("~!@$%^&*-_=+[{]}|:<.>/?"), ScanIDs::SYN_SYMBOL);
  setCharSyntax(T(";"), ScanIDs::SYN_COMMENT);
  setCharSyntax(T("`#',"), ScanIDs::SYN_PREFIX);
  setCharSyntax(T("\""), ScanIDs::SYN_STRING);
  setCharSyntax(T("("), ScanIDs::SYN_OPEN);
  setCharSyntax(T(")"), ScanIDs::SYN_CLOSE);
  setCharSyntax(T(","), ScanIDs::SYN_PUNCT);
  setCharSyntax(T("\\"), ScanIDs::SYN_ESCAPE);

  //  addSynTok(T("and"), numtoks, 0, 2);
  addSynTok(T("begin"), numtoks, 1, 1000);
  addSynTok(T("cond"), numtoks, 0, 2);
  addSynTok(T("define"), numtoks, 1, 1);
  addSynTok(T("define*"), numtoks, 1, 1);
  addSynTok(T("define-process"), numtoks, 1, 1);
  addSynTok(T("definstrument"), numtoks, 1, 1);
  addSynTok(T("do"), numtoks, 1, 2);
  addSynTok(T("if"), numtoks, 0, 1);
  addSynTok(T("lambda"), numtoks, 1, 1);
  addSynTok(T("let"), numtoks, 1, 1);
  addSynTok(T("let*"), numtoks, 1, 1);
  addSynTok(T("letrec"), numtoks, 1, 1);
  addSynTok(T("loop"), numtoks, 0, 1000);
  //addSynTok(T("or"), numtoks, 0, 2);
  addSynTok(T("process"), numtoks, 0, 1000);
  addSynTok(T("run"), numtoks, 0, 1000);
  addSynTok(T("send"), numtoks, 0, 1);
  //  addSynTok(T("unless"), numtoks, 1, 1);
  //  addSynTok(T("when"), numtoks, 1, 1);
  addSynTok(T("with-csound"), numtoks, 1, 1);
  addSynTok(T("with-fomus"), numtoks, 1, 1);
  addSynTok(T("with-midi"), numtoks, 1, 1);
  addSynTok(T("with-sound"), numtoks, 1, 1);
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
  // for attributes see ColorThemeIDs class in Enumerations.h

  StringArray names;

  // Color Theme Attribute       Token Type
  //-------------------------------------------
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
  static int par = 0;
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
      if (isTokenChar(source.peekNextChar())) // #x #? #t #f etc
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
      par=source.getPosition();
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
          } while (isTokenChar(source.peekNextChar()));
        // i is now one beyond last constituent character
        if (chr==':') // first char was lisp keyword 
          typ=TokenLispKeyword;
        else if (i<=maxtoklen) // check for special word
          {
            // highlight only if symbol immediately follows a '('
            bool func=(par+1==source.getPosition()-i);
            if (func && getSynTok(check) )
              {
                //std::cout << "par=" << par << ",i=" << i << ", pos=" << source.getPosition() -i << "\n";
                typ=TokenLispSpecialForm;
              }
            else
              typ=TokenPlaintext;              
          }
        else
          typ=TokenPlaintext;              
      }
    }
  return typ;
}

int LispSyntax::getIndentation(CodeDocument& document, int line)
{
  CodeDocument::Position pos (&document, line, 0);
  Array<int> subtypes;
  Array<int> substarts;
  int scan=0;

  // if no lines above point indent 0 else move cursor to end of
  // previous line and scan backward until either unlevel OR a
  // balanced expression in column 0. record types and starting
  // positions of subexpressions traversed

  if (line==0) return 0;
  pos.setLineAndIndex(line-1, INT_MAX); // goto eol of previous line
  while (true)
    {
      scan=scanCode(document, pos, false, ScanIDs::MoveExpressions);
      if (scan>0)
        if (pos.getIndexInLine()==0)
          {
            break;
          }
        else
          {
            // prepend since moving backward
            subtypes.insert(0, scan);
            substarts.insert(0, pos.getPosition());
            // arrrgh! the 1st position problem
            pos.moveBy(-1); 
          }
      else
        {
          break;
        }
    }
  //std::cout << "after loop, scan="<<scan<< ", pos=" << pos.getPosition() << ", col=" << pos.getIndexInLine() << "\n";
  // stopped on a balanced expr in column 0 so indent to whatever
  // position the very LATEST subexpr is or use column 0
  if (scan!=ScanIDs::SCAN_UNLEVEL)
    {
      if (substarts.size()==0)
        {
          ////          std::cout << "balanced indent: 0\n";
          return 0;
        }
      CodeDocument::Position sub (&document, substarts.getLast());
      ////std::cout << "balanced indent: " << sub.getIndexInLine() << "\n";
      return sub.getIndexInLine();
    }
  // otherwise we've stopped on an unbalanced open parens.

  //  std::cout << "unlevel: (" << pos.getPosition() << ") -> '" 
  //            << document.getTextBetween(pos, pos.movedBy(1)).toUTF8() 
  //           << "'\nsubexprs:\n";
  //  for (int i=0; i<subtypes.size(); i++)
  //    std::cout << "  " << substarts[i] << ": " << ScanIDs::scanResultToString(subtypes[i]).toUTF8() << "\n";

  // if no subexprs indent 1 position beyond open parens
  if (subtypes.size()==0)
    {
      ////std::cout << "nothing forward, indent column=" << pos.getIndexInLine()+1 << "\n";
      return pos.getIndexInLine()+1;
    }

  // if first subexpr is NOT a token indent to its column position
  if (subtypes.getFirst()!=ScanIDs::SCAN_TOKEN)
    {
      CodeDocument::Position sub (&document, substarts.getFirst());
      ////std::cout << "not a token, indent column=" << sub.getIndexInLine() << "\n";
      return sub.getIndexInLine();
    }

  // first expr after the open parens is a token, get its name and
  // check for special indentation rules
  CodeDocument::Position tokbeg (&document, substarts.getFirst());
  CodeDocument::Position tokend (&document, substarts.getFirst());
  CodeDocument::Position tokeol (&document, tokbeg.getLineNumber(), INT_MAX);
  scanToken(tokend, 1, tokeol);
  String name=document.getTextBetween(tokbeg,tokend);
  int nargs=substarts.size()-1;    // num subexpr args after token

  //std::cout << "num exprs=" << subtypes.size() << ", numstarts=" << substarts.size() << "\n";

  if (Syntax::SynTok* syntok=getSynTok(name)) // is special form
    {
      // car of list is a special form. get num distinguished args to
      // see if we do a body indent
      int body=syntok->getIndent(); // num distinguished args
 
      // if we have no args or exactly body args then do a body indent
      // otherwise indent to the column of the last subexpr.

      ////std::cout << "special form: '" << name.toUTF8() << "', nargs="<< nargs << ", body=" << body;

      //std::cout << "special nargs=" << nargs << "\n";

      if (nargs==0 || nargs==body)
        {
          ////std::cout << "body indent, indent column=" << pos.movedBy(2).getIndexInLine() << "\n";
          return pos.movedBy(2).getIndexInLine();
        }
      else
        {
          //**  CodeDocument::Position sub (&document, substarts.getLast());
          //**//std::cout << "indent to last expr, indent column=" << sub.getIndexInLine() << "\n";
          //** return sub.getIndexInLine();
          substarts.remove(0);  
          int x=lastIndented(document, substarts, false);
          //std::cout << "returning indent col=" << x << "\n";
          return x;
        }
    }
  else // token not special, indent to last expr or to pos+1 if none
    {
      //std::cout << "no special nargs=" << nargs << "\n";
      if (nargs==0)
        {
          ////std::cout << "normal token with no args, indent column=" << pos.movedBy(1).getIndexInLine() << "\n";
          return pos.movedBy(1).getIndexInLine();
        }
      else
        {
          //** CodeDocument::Position sub (&document, substarts.getLast());
          //**//std::cout << "normal token (args), indent column=" << sub.getIndexInLine() << "\n";
          //return sub.getIndexInLine();
          substarts.remove(0);
          int x=lastIndented(document, substarts, false);
          //std::cout << "returning indent col=" << x << "\n";
          return x;
        }
    }
}

int LispSyntax::backwardExpr(CodeDocument& document, CodeDocument::Position& from, CodeDocument::Position& to)
{
  CodeDocument::Position pos (to);
  // when moving backwards cursor is always one char after scan start
  pos.moveBy(-1);
  // skip over trailing comments and whitespace
  scanCode(document, pos, false, ScanIDs::MoveWhiteAndComments);
  // pos is now ON ending char of expr (or at eob if only white) so
  // set end to one position beyond last char in expr
  CodeDocument::Position end (pos.movedBy(1));
  // scan backwords to locate start of expr
  int scan=scanCode(document, pos, false, ScanIDs::MoveExpressions);
  from.setPosition(pos.getPosition());
  to.setPosition(end.getPosition());
  return scan;
}

void LispSyntax::eval(CodeDocument& document, const CodeDocument::Position start, const CodeDocument::Position end, bool expand, bool region)
{
  String code=document.getTextBetween(start, end);
  //std::cout << "eval='" << code.toUTF8() << "'\n";
  if (expand)
    code=T("(macroexpand ") + code + T(")");
  if (region)
    code=T("(begin ") + code + T(")");
  SchemeThread::getInstance()->eval(code);
}

/*=======================================================================*
                               Sal Syntax
 *=======================================================================*/

SalSyntax::SalSyntax (bool ini) 
  : Syntax()
{
  if (ini) 
    init();
}

void SalSyntax::init()
{
  type=TextIDs::Sal;

  setCharSyntax(T("~!@$%^&*-_=+|:<.>/?"), ScanIDs::SYN_SYMBOL);
  setCharSyntax(T(";"), ScanIDs::SYN_COMMENT);
  setCharSyntax(T("#"), ScanIDs::SYN_PREFIX);
  setCharSyntax(T("\""), ScanIDs::SYN_STRING);
  setCharSyntax(T("([{"), ScanIDs::SYN_OPEN);
  setCharSyntax(T(")]})"), ScanIDs::SYN_CLOSE);
  setCharSyntax(T(","), ScanIDs::SYN_PUNCT);
  setCharSyntax(T("\\"), ScanIDs::SYN_ESCAPE);

  addSynTok( T("begin"), SalIDs::SalBegin, 1, 0); // 1 = #b01 = indent
  addSynTok( T("chdir"), SalIDs::SalChdir);
  addSynTok( T("define"), SalIDs::SalDefine, 0, 3);
  addSynTok( T("else"), SalIDs::SalElse, 3, 0);  // 3 = #b11 = undent/indent
  addSynTok( T("end"), SalIDs::SalEnd, 2, 0);      // 2 = #10 = undent
  addSynTok( T("exec"), SalIDs::SalExec);
  addSynTok( T("fomusfile"), SalIDs::SalFomusFile, 1, 2);
  addSynTok( T("if"), SalIDs::SalIf);
  addSynTok( T("load"), SalIDs::SalLoad);
  addSynTok( T("loop"), SalIDs::SalLoop);
  addSynTok( T("plot"), SalIDs::SalPlot);
  addSynTok( T("print"), SalIDs::SalPrint);
  addSynTok( T("return"), SalIDs::SalReturn);
  addSynTok( T("run"), SalIDs::SalRun, 1, 0);
  addSynTok( T("send"), SalIDs::SalSend);
  addSynTok( T("set"), SalIDs::SalSet);
  addSynTok( T("soundfile"), SalIDs::SalSoundFile, 1, 2);
  addSynTok( T("sprout"), SalIDs::SalSprout);
  addSynTok( T("then"), SalIDs::SalThen);
  addSynTok( T("unless"), SalIDs::SalUnless);
  addSynTok( T("until"), SalIDs::SalUntil);
  addSynTok( T("wait"), SalIDs::SalWait);
  addSynTok( T("when"), SalIDs::SalWhen);
  addSynTok( T("while"), SalIDs::SalWhile);
  addSynTok( T("with"), SalIDs::SalWith);
  addSynTok( T("process"), SalIDs::SalProcess);
  addSynTok( T("function"), SalIDs::SalFunction);
  addSynTok( T("variable"), SalIDs::SalVariable);
  
  addSynTok( T("above"), SalIDs::SalAbove);
  addSynTok( T("below"), SalIDs::SalBelow);
  addSynTok( T("by"), SalIDs::SalBy);
  addSynTok( T("downto"), SalIDs::SalDownto);
  addSynTok( T("finally"), SalIDs::SalFinally);
  addSynTok( T("for"), SalIDs::SalFor);
  addSynTok( T("from"), SalIDs::SalFrom);
  addSynTok( T("in"), SalIDs::SalIn);
  addSynTok( T("over"), SalIDs::SalOver);
  addSynTok( T("repeat"), SalIDs::SalRepeat);
  addSynTok( T("to"), SalIDs::SalTo);
  
  //  Operators, data field is op weight
  addSynTok( T("|"), SalIDs::SalOr);
  addSynTok( T("&"), SalIDs::SalAnd);
  addSynTok( T("!"), SalIDs::SalNot);
  addSynTok( T("="), SalIDs::SalEqual); // relation and op
  addSynTok( T("!="), SalIDs::SalNotEqual);  
  addSynTok( T("<"), SalIDs::SalLess);
  addSynTok( T(">"), SalIDs::SalGreater);
  addSynTok( T("<="), SalIDs::SalLessEqual); // relation and op
  addSynTok( T(">="), SalIDs::SalGreaterEqual); // relation and op
  addSynTok( T("~="), SalIDs::SalGeneralEqual);  
  addSynTok( T("+"), SalIDs::SalPlus);
  addSynTok( T("-"), SalIDs::SalMinus);
  addSynTok( T("%"), SalIDs::SalMod);
  addSynTok( T("*"), SalIDs::SalTimes);  
  addSynTok( T("/"), SalIDs::SalDivide);
  addSynTok( T("^"), SalIDs::SalExpt);
  // assignment (also: = <= >=)
  addSynTok( T("+="), SalIDs::SalInc);
  addSynTok( T("*="), SalIDs::SalMul);
  addSynTok( T("&="), SalIDs::SalCol);
  addSynTok( T("@="), SalIDs::SalPre);  
  addSynTok( T("^="), SalIDs::SalApp);
  // hash tokens
  addSynTok( T("#t"), SalIDs::SalTrue);
  addSynTok( T("#f"), SalIDs::SalFalse);
  addSynTok( T("#?"), SalIDs::SalQMark);
  addSynTok( T("#$"), SalIDs::SalUnquote);
  addSynTok( T("#^"), SalIDs::SalSplice);
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
  // for attributes see ColorThemeIDs class in Enumerations.h

  StringArray names;

  // Color Theme Attribute       Token Type
  //-------------------------------------------
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
  int typ=SalIDs::TokenError;
  tchar chr=0;
  while (source.peekNextChar() && isWhiteChar(source.peekNextChar()))
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
      if (isTokenChar(source.peekNextChar())) // #x #? #t #f etc
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
        while (isTokenChar(source.peekNextChar()));

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

int SalSyntax::getIndentation(CodeDocument& document, int line)
// THIS METHOD IS SAL2 BUT WORKS OK FOR SAL SO DEFINED HERE
{
  CodeDocument::Position pos (&document, line, 0);
  Array<int> subtypes;
  Array<int> substarts;
  Syntax::SynTok* cmdtoken=0;
  int scan=0;
  int col=0;

  // if no lines above point indent 0
  if (line==0) return 0;
  // move to EOL of line above cursor
  line--;
  pos.setLineAndIndex(line, INT_MAX);

  // scan backwards until either unlevel OR a command or a balanced
  // expr in column 0. record types and starting positions of
  // subexpressions traversed
  while (true)
    {
      scan=scanCode(document, pos, false, ScanIDs::MoveExpressions);
      if (scan>0)
        {
          // prepend expr type since moving backward
          subtypes.insert(0, scan);
          substarts.insert(0, pos.getPosition());
          if (scan==ScanIDs::SCAN_TOKEN)
            {
              CodeDocument::Position end (pos);
              CodeDocument::Position eol (&document, pos.getLineNumber(), INT_MAX);
              scanToken(end, 1, eol);
              String str=document.getTextBetween(pos,end);
              if (Syntax::SynTok* tok=getSynTok(str))
                {
                  // update subtype with actual sal type. if type is a
                  // command, 'end' or 'else' then break
                  int type=tok->getType();
                  subtypes.set(0,type);
                  if (SalIDs::isSalCommandType(type) )
                    {
                      cmdtoken=tok;
                      break;
                    }
                }
              else if (pos.getIndexInLine()==0)
                break;
            }
          else if (pos.getIndexInLine()==0)
            break;
          pos.moveBy(-1); 
        }
      else
        break;
    }

  if (scan<0) // scan stopped on unlevel parens
    {
      if (substarts.size()>0) // use last subexpr indentation
        {
          col=lastIndented(document, substarts, false);
          //std::cout << "UNLEVEL indent (last expr), column=" << col << "\n";
          return col;
        }
      else
        {
          col=pos.movedBy(1).getIndexInLine();
          //std::cout << "UNLEVEL indent (no exprs), column=" << col << "\n";
          return col;
        }
    }
  else if (subtypes.size()==0) // no expressions encountered (only white space)
    {
      //std::cout << "EMPTY indent, column=0\n" ;
      return 0;
    }  

  // at this point we have at least one subexpr and may have stopped
  // on a sal type

  if (!SalIDs::isSalType(subtypes[0]))     // stopped on a non-sal expression
    {
      col=lastIndented(document,substarts, false);
      //std::cout << "SEXPR indent, column=" << col << "\n";
    }
  else // types[0] is sal entity, hopefully a command
    {
      if (cmdtoken)  // we stopped on a command
        {
          int cmdline=pos.getLineNumber(); // num of line with cmd
          // last is INDEX of last indented or command we stopped on
          int last=lastIndented(document, substarts, true);
          // IF the VERY last line ends with comma then indent 1 past
          // command name or a subexpr 'with' (if found)
          if (isCommaTerminatedLine(document, line))
            {
              for (last=subtypes[subtypes.size()-1]; last>=0; last--)
                if (subtypes[last]==SalIDs::SalWith)
                  break;
              if (last<0) // reached command
                col=pos.getIndexInLine()+cmdtoken->getName().length()+1;
              else // indent relative to 'with'
                {
                  CodeDocument::Position p (&document, substarts[last]);
                  col=p.getIndexInLine()+4+1;
                }
              //std::cout << "COMMA indent, column=" << col << "\n";
            }
          // ELSE (the very last line does NOT end with comma) if
          // line-1 is >= cmdline and DOES end with comma then we are
          // done with comma indenting so intent to body or pos
          else if ((cmdline<=line-1) && isCommaTerminatedLine(document, line-1))
            {
              if (cmdtoken->getData1()>0)
                {
                  col=pos.getIndexInLine()+2;
                  //std::cout << "BODY indent (after comma stop), column=" << col << "\n";
                }
              else
                {
                  col=pos.getIndexInLine();
                  //std::cout << "RESET indent (after comma stop), column=" << col << "\n";
                }
            }
          // ELSE if the last indented is 'else' then body indent
          // based on position of 'else'
          else if (subtypes[last]==SalIDs::SalElse)
            {
              CodeDocument::Position p (&document, substarts[last]);
              col=p.getIndexInLine()+2;
              //std::cout << "ELSE indent, column=" << col << "\n";
            }          
          // else if the command is a body indent, indent to the last
          // expression or to 2 past the first (command) expr
          else if (cmdtoken->getData1()>0)
            {
              if (last==0) // the command, no subexprs on own line
                {
                  col=pos.getIndexInLine()+2;
                  //std::cout << "BODY indent, column=" << col << "\n";
                }
              // else indent to the last expression
              else
                {
                  CodeDocument::Position p (&document, substarts[last]);
                  col=p.getIndexInLine();
                  //std::cout << "LAST indent (body), column=" << col << "\n";
                }
            }
          // else indent to the last expression
          else
            {
              CodeDocument::Position p (&document, substarts[last]);
              col=p.getIndexInLine();
              //std::cout << "LAST indent, column=" << col << "\n";
            }
        }
      else
        {
          col=lastIndented(document, substarts, false);
          //std::cout << "non-standard sal indent, column=" << col << "\n";
        }
    }

  // if we are looking at an 'end' or an 'else' in the cursor line
  // then adjust -2

  CodeDocument::Position bol (&document, line, 0);
  CodeDocument::Position eol (&document, line, INT_MAX); 
  while (bol!=eol && (bol.getCharacter()==T(' ') || bol.getCharacter()==T('\t'))) 
    bol.moveBy(1);
  if (lookingAt(bol, T("end"), true, true) || lookingAt(bol, T("else"), true, true))
    {
      col-=2;
      //std::cout << "cursor is looking at end or else\n";
    }
  return jmax(col,0);
}

int SalSyntax::backwardExpr(CodeDocument& document, CodeDocument::Position& from, CodeDocument::Position& to)
{
  // in sal1 backward expression finds the nearest command literal
  // that start in 0th column position of a line
  // moving backwards the cursor is always one char past scan start
  to.moveBy(-1);
  // skip trailing comments and whitespace
  scanCode(document, to, false, ScanIDs::MoveWhiteAndComments);
  // to is now ON ending char of expr (or at eob if only white) so set
  // end to one beyond ending char of expr
  to.moveBy(1);
  int line=to.getLineNumber();
  while (line>=0)
    {
      from.setLineAndIndex(line, 0);
      CodeDocument::Position t (from);
      CodeDocument::Position e (&document, line, INT_MAX); // end of current line
      if (scanToken(t, 1, e))
        {
          if (Syntax::SynTok* tok=getSynTok(document.getTextBetween(from, t)))
            {
              if (SalIDs::isSalCommandType(tok->getType()))
                {
                  //std::cout << "command=" << tok->getName().toUTF8() << "\n";
                  return 1;
                }
            }
        }
      line-=1;
    }
  return 0;
}

const String& SalSyntax::getLastParseError()
{
  return errormessage;
}

bool SalSyntax::tokenize(String str, OwnedArray<SynTok>& toks)
{
  CodeDocument doc;
  doc.replaceAllContent(str);
  CodeDocument::Position start (&doc,0);
  CodeDocument::Position end (&doc,INT_MAX);
  return tokenize(doc,start,end,toks);
}

bool SalSyntax::tokenize(CodeDocument& document, const CodeDocument::Position start, const CodeDocument::Position end,
                         OwnedArray<SynTok>& tokens)
{
  // forward scan sal tokens and call sal on result. if region is true
  // then surround the add 'begin' and 'end' to the string and token
  // array adjust string positions accordingly
 
  //String code=document.getTextBetween(start, end);
  //std::cout << "expr='" << code.toUTF8() << "', start=" << start.getPosition() 
  //          << ", end=" << end.getPosition() << "\n";
  errormessage=String::empty;
  CodeDocument::Position pos (start);
  int beg=pos.getPosition();  // offset of string in document
  int lev=0, par=0, cur=0, squ=0;
  int scan=scanCode(document, pos,true,ScanIDs::MoveWhiteAndComments, end.getPosition());
  while (pos!=end)
    {
      CodeDocument::Position far(pos);
      scan=scanCode(document, far, true, ScanIDs::MoveTokens, end.getPosition());
      if (scan<=0) break;
      int loc=pos.getPosition()-beg;
      if (scan==ScanIDs::SCAN_OPEN)
        {
          tchar c=pos.getCharacter();
          if (c==T('('))
            {
              par++;
              tokens.add(new Syntax::SynTok(T("("), SalIDs::SalLParen, loc));
            }
          else if (c==T('{'))
            {
              cur++;
              tokens.add(new Syntax::SynTok(T("{"), SalIDs::SalLCurly, loc));
            }
          else if (c==T('['))
            {
              squ++;
              tokens.add(new Syntax::SynTok(T("["), SalIDs::SalLBrace, loc));
            }
        }
      else if (scan==ScanIDs::SCAN_CLOSE)
        {
          tchar c=pos.getCharacter();
          if (c==T(')'))
            {
              if (--par < 0) break;
              tokens.add(new Syntax::SynTok(T(")"), SalIDs::SalRParen, loc));
            }
          else if (c==T('}'))
            {
              if (--cur < 0) break;
              tokens.add(new Syntax::SynTok(T("}"), SalIDs::SalRCurly, loc));
            }
          else if (c==T(']'))
            {
              if (--squ < 0) break;
              tokens.add(new Syntax::SynTok(T("]"), SalIDs::SalRBrace, loc));
            }
        }
      else if (scan==ScanIDs::SCAN_PUNCT)
        tokens.add(new Syntax::SynTok(T(","), SalIDs::SalComma, loc));
      else if (scan==ScanIDs::SCAN_STRING)
        {
          tokens.add(new Syntax::SynTok(document.getTextBetween(pos,far).unquoted(), SalIDs::SalString, loc));
        }
      else if (scan==ScanIDs::SCAN_TOKEN)
        {
          String s=document.getTextBetween(pos,far);
          if (Syntax::SynTok* t=getSynTok(s))
            {
              int x=t->getType();
              tokens.add(new Syntax::SynTok(s, x, loc));
              if (SalIDs::isSalBlockOpen(x))
                lev++;
              else if (SalIDs::isSalBlockClose(x))
                {
                  if (--lev < 0) break;
                }
            }
          else if (int t=isNumberToken(s))
            {
              int typs[] = {SalIDs::SalInteger, SalIDs::SalFloat, SalIDs::SalRatio};
              tokens.add(new Syntax::SynTok(s, typs[t-1], loc));
            }
          else // is still a valid token!
            {
              if (s.getLastCharacter()==T(':'))
                tokens.add(new Syntax::SynTok(s.dropLastCharacters(1), SalIDs::SalKeyparam, loc));
              else if (s[0]==T(':'))
                tokens.add(new Syntax::SynTok(s.substring(1), SalIDs::SalKeyword, loc));
              else
                tokens.add(new Syntax::SynTok(s, SalIDs::SalIdentifier, loc));
            }
        }
      pos=far;
      scan=scanCode(document, pos,true,ScanIDs::MoveWhiteAndComments, end.getPosition());
    }

  //std::cout << "tokens="; for (int i=0; i<tokens.size(); i++) std::cout << " " << tokens[i]->toString().toUTF8(); std::cout << "\n";

  if (scan<0)
    {
      errormessage << T(">>> Error: illegal token, line: ") //<< pos.getLineNumber() 
                   << T("\n") << pos.getLineText() << T("\n");
      return false;
    }
  else if (lev!=0 || par!=0 || cur!=0 || squ!=0)
    {
      Syntax::SynTok* tok=NULL;
      if (lev<0) // too many ends
        errormessage << T(">>> Error: extraneous 'end', line: ");
      else if (par<0)
        errormessage << T(">>> Error: extraneous ')', line: ");
      else if (cur<0)
        errormessage << T(">>> Error: extraneous '}', line: ");
      else if (squ<0)
        errormessage << T(">>> Error: extraneous ']', line: ");
      else if (lev>0)
        {
          errormessage << T(">>> Error: missing 'end'");
          for (int i=tokens.size()-1, n=0; i>-1; i--)
            {
              int x=SalIDs::SalTypeDataBits(tokens[i]->getType());
              if (x==SalIDs::SalBlockOpen)
                if (n==lev) {tok=tokens[i]; break;} else n--;
              else if (x==SalIDs::SalBlockClose) n++;
            }
          if (tok) errormessage << " for " << tok->getName();
          errormessage << T(", line: ");
        }
      else if (par>0)
        {
          errormessage << T(">>> Error: missing ')', line: ");
          for (int i=tokens.size()-1, n=0; i>-1; i--)
            if (tokens[i]->getType()==SalIDs::SalLParen) 
              if (n==par) {tok=tokens[i]; break;} else n--;
            else if (tokens[i]->getType()==SalIDs::SalRParen) n++;
        }
      else if (cur>0)
        {
          errormessage << T(">>> Error: missing '}', line: ");
          for (int i=tokens.size()-1, n=0; i>-1; i--)
            if (tokens[i]->getType()==SalIDs::SalLCurly) 
              if (n==cur) {tok=tokens[i]; break;} else n--;
            else if (tokens[i]->getType()==SalIDs::SalRCurly) n++;
        }
      else if (squ>0)
        {
          errormessage << T(">>> Error: missing ']', line: ");
          for (int i=tokens.size()-1, n=0; i>-1; i--)
            if (tokens[i]->getType()==SalIDs::SalLBrace) 
              if (n==cur) {tok=tokens[i]; break;} else n--;
            else if (tokens[i]->getType()==SalIDs::SalRBrace) n++;
       }
      if (tok) pos.setPosition(beg+tok->getData1());
      errormessage // << pos.getLineNumber() 
        << T("\n")  << pos.getLineText() << T("\n");
      return false;
    }
  return true;
}

void SalSyntax::eval(CodeDocument& document, const CodeDocument::Position start, const CodeDocument::Position end, bool expand, bool region)
{
  OwnedArray<Syntax::SynTok> tokens;
  if (tokenize(document, start, end, tokens))
    {
      String text=document.getTextBetween(start, end);
      XSalNode* node=new XSalNode(0.0, text, getTextType(), expand, region);
      // swapping moves tokens from the local array to the evalnode's
      // array AND clears the local array in a single
      // operation. swapping must be done or the tokens will be
      // deleted when the local array goes out of scope!
      node->toks.swapWithArray(tokens);
      //std::cout << "tokens=";
      //for (int i=0; i<node->toks.size(); i++)
      //  std::cout << " " << node->toks[i]->toString().toUTF8();
      //std::cout << "\n";
      SchemeThread::getInstance()->addNode(node);
    }
  else
    Console::getInstance()->printError(getLastParseError());
}

/*=======================================================================*
                               Sal2 Syntax
 *=======================================================================*/

Sal2Syntax::Sal2Syntax () 
  : SalSyntax(false)
{
  type=TextIDs::Sal2;

  setCharSyntax(T("~!@$%^&*-_=+|:<.>/?"), ScanIDs::SYN_SYMBOL);
  setCharSyntax(T(";"), ScanIDs::SYN_COMMENT);
  setCharSyntax(T("#"), ScanIDs::SYN_PREFIX);
  setCharSyntax(T("\""), ScanIDs::SYN_STRING);
  setCharSyntax(T("([{"), ScanIDs::SYN_OPEN);
  setCharSyntax(T("}])"), ScanIDs::SYN_CLOSE);
  setCharSyntax(T(","), ScanIDs::SYN_PUNCT);
  setCharSyntax(T("\\"), ScanIDs::SYN_ESCAPE);

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
  // for attributes see ColorThemeIDs class in Enumerations.h

  StringArray names;

  // Color Theme Attribute       Token Type
  //-------------------------------------------
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
      if (isTokenChar(source.peekNextChar())) // #x #? #t #f etc
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
        while (isTokenChar(source.peekNextChar()));
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

int Sal2Syntax::backwardExpr(CodeDocument& document, CodeDocument::Position& from, CodeDocument::Position& to)
{
  //CodeDocument::Position pos (getCaretPos());
  CodeDocument::Position pos (to);
  CodeDocument::Position bob (&document, 0);  // beginning of buffer
  int scan=0, last=0, here=-1, level=0;
  #define SCAN_CURLY (ScanIDs::SCAN_PUNCT+1)
  #define SCAN_SQUARE (ScanIDs::SCAN_PUNCT+2)

  // cursor always 1 past start of backward scan
  pos.moveBy(-1);
  // move backward over white and comments
  scanCode(document, pos, false, ScanIDs::MoveWhiteAndComments);
  // pos now on last constituent char for backward scan (or at
  // bob). set scan's exclusive upper bound to 1 above pos
  CodeDocument::Position top (pos.movedBy(1));

  if (lookingAt(pos, T("end"), false, true)) // at block end
    while (true)
      {
        // now on last constituent char for scan (or at bob). set the
        // exclusive upper bound of expr to 1 above that
        CodeDocument::Position end (pos.movedBy(1)); 
        scan=scanCode(document, pos, false, ScanIDs::MoveExpressions);
        // quit if error or only white space
        if (scan<=0)
          break;
        String code=document.getTextBetween(pos, end);
        //std::cout << "Code ("<<from.getPosition()<<","<<to.getPosition()<<"): '" << code.toUTF8() << "'\n";
        if (scan==ScanIDs::SCAN_TOKEN)
          {
            if (Syntax::SynTok* tok=getSynTok(code))
              {
                // token is a literal (e.g. statement, op)
                int typ=tok->getType();
                if (SalIDs::isSalBlockClose(typ))
                  level++; 
                else if (SalIDs::isSalBlockOpen(typ))
                  level--; 
                // stop on a blockopen word with no pending end. this
                // doesn't mean the statement is actually balanced
                // since the word could be reached without seeing a
                // balancing end (in which case level is negative)
                if (level<=0)
                  {
                    here=pos.getPosition();
                    break;
                  }
              }
          }
        if (pos==bob) break;
        pos.moveBy(-1);
        scanCode(document, pos, false, ScanIDs::MoveWhiteAndComments);
      }
  else   
    // else parse expr back, possibly to a command (set or variable)
    // but stopping before any clausal
    while (true)
      {
        // pos is on last consitute char of backwards expr (or at bol)
        // set exclusive end of current expr and scan backwards
        CodeDocument::Position end (pos.movedBy(1)); 
        scan=scanCode(document, pos, false, ScanIDs::MoveExpressions);
        // quit if scan error or only white space
        if (scan<=0)
          {
            //std::cout << "breaking with scan <= 0: " << scan << "\n";;
            break;
          }
        String code=document.getTextBetween(pos,end);
        //std::cout << "Code ("<<pos.getPosition()<<","<<end.getPosition()<<"): '" << code.toUTF8() << "'\n";
        if (scan==ScanIDs::SCAN_TOKEN)
          {
            Syntax::SynTok* tok=getSynTok(code);
            if (tok && !SalIDs::isSalBoolType(tok->getType()))  // booleans are values...
              {
                // token is a literal. stop if its the first thing
                // encountered or if its a clausal
                if (last==0 || SalIDs::isSalClausalType(tok->getType()))
                  {
                    //std::cout<<"literal breaking with last==0"<<code.toUTF8()<<"\n";
                    break;
                  }
                scan=tok->getType();
                // if its a command then include and stop
                if (SalIDs::isSalCommandType(scan))
                  {
                    //std::cout << "stopping on command '"<<code.toUTF8()<<"'\n";
                    here=pos.getPosition();
                    break;
                  }
                // otherwise (its a op or comma? ) keep going...
                here=pos.getPosition();
              }
            else 
              {
                // token is a variable or constant.  if its the first
                // expr or if the last was a literal then include it
                // and keep going
                if ((last==0) || SalIDs::isSalType(last))
                  here=pos.getPosition();
                // otherwise if its a constant then stop (because last
                // is an expr)
                else if (code.containsOnly(T("0123456789+-./")) ||
                         code.startsWith(T("#")) ||
                         code.startsWith(T(":")) ||
                         code.endsWith(T(":")) )
                  {
                    //std::cout<<"breaking with constant="<<code.toUTF8()<<"\n";
                    break;
                  }
                // otherwise its a variable, if last was a () expr its
                // a function call, if last was a [] its a aref
                // otherwise stop
                else if (last==ScanIDs::SCAN_LIST || last==SCAN_SQUARE)
                  here=pos.getPosition();
                else
                  {
                    //std::cout << "token breaking with code='"<<code.toUTF8()<<"'\n";
                    break;
                  }
              }
          }
        else if (scan==ScanIDs::SCAN_PUNCT)
          {
            // its a comma, stop if last not an expression
            if (last==0 || SalIDs::isSalType(last))
              {
                //std::cout << "breaking on SCAN_PUNCT=\n";
                break;
              }
            scan=SalIDs::SalComma;
          }
        // otherwise its a {[( or string expression. stop unless this
        // expr its the first or the previous thing was not an expr
        else if (last==0 || SalIDs::isSalType(last))
          {
            if (pos.getCharacter()==T('{'))
              scan=SCAN_CURLY;
            else if (pos.getCharacter()==T('['))
              scan=SCAN_SQUARE;
            here=pos.getPosition();
          }
        else
          {
            //std::cout << "breaking with scan=" << ScanIDs::scanResultToString(scan).toUTF8() << "\n";
            break;
          }
        if (pos==bob) break;
        // move one below first expr char, skip comments and white
        last=scan;
        pos.moveBy(-1);
        scanCode(document, pos, false, ScanIDs::MoveWhiteAndComments);
      }
  //std::cout << "_______________\n";

  if (scan<0) 
    {
      //std::cout << "returning: " << scan << "\n";
      return scan;
    }
  //std::cout << "after loop, here=" << here << "scan=" << scan << "\n";
  from.setPosition(here);
  //std::cout << "setting from position="<< here << "\n";
  to.setPosition(top.getPosition());
  //std::cout << "setting to position=" << top.getPosition() << "\n";
  
  // stopped without lower bound means no expr encountered
  if (here<0) 
    {
      scan=ScanIDs::SCAN_EMPTY;
      here=pos.getPosition();
    }
  //std::cout << "returning: "  << ((here>-1) ? 1 : scan) << "\n";
  return (here>-1) ? 1 : scan;
}
