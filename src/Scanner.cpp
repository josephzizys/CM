/*************************************************************************
 * Copyright (C) 2008, Rick Taube.                                       *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

/*
  TEST using (CHAR *):

  g++ -DNOJUCE -DSCANTEST Scanner.cpp
  date; ./a.out -c /Lisp/cm/src/midi1.lisp > char.txt ; date

  TEST using JUCE STRINGS:

  g++ -c -I/Lisp/juce -DSCANTEST Syntab.cpp
  g++ -v -L/Lisp/juce/bin -framework Carbon -ljuce Syntab.o 
  date; ./a.out -c /Lisp/cm/src/midi1.lisp > String.txt ; date
*/

#include "Scanner.h"

using namespace std;

// these should be macros but im a total C weenie...

int EOL_P (char c) {
  //return (c == EOLC) ? 1 : 0;
  // this is what juce textEditor uses:
  return (c == '\r') || (c == '\n');
}

int FDIR_P (int d) {
  return (d == FDIR) ? 1 : 0;
}

int BDIR_P (int d) {
  return (d == BDIR) ? 1 : 0;
}

int GETDIR (int p, int e) {
  if (p > e) return BDIR;
  else if (p < e) return FDIR;
  else return 0;
}

void set_syntax (SynTab tab, String chrs, charsyntax syn) {
#ifdef NOJUCE
  int l = strlen(chrs);
#endif
#ifndef NOJUCE
  int l = chrs.length();
#endif
  int i;
  for (i=0; i< l; i++)
    tab[chrs[i]] = syn;
}

void init_syntab (SynTab syntab, String whitechars, String wordchars, 
		  String symbolchars, String commentchars, 
		  String prefixchars, String stringchars,
		  String openchars, String closechars,
		  String punctchars, String escapechars) {
  int i;
  // initialize whole table to WHITE.
  for (i=0; i<SYNTAB_LEN; i++) syntab[i]=SYN_WHITE;
  // alphadigits are WORD by default
  for (i='0'; i<='9'; i++) syntab[i]=SYN_WORD;
  for (i='A'; i<='Z'; i++) syntab[i]=SYN_WORD;
  for (i='a'; i<='z'; i++) syntab[i]=SYN_WORD;
  // user inits
  set_syntax(syntab, whitechars, SYN_WHITE);
  set_syntax(syntab, wordchars, SYN_WORD);
  set_syntax(syntab, symbolchars, SYN_SYMBOL);
  set_syntax(syntab, commentchars, SYN_COMMENT);
  set_syntax(syntab, prefixchars, SYN_PREFIX);
  set_syntax(syntab, stringchars, SYN_STRING);
  set_syntax(syntab, openchars, SYN_OPEN);
  set_syntax(syntab, closechars, SYN_CLOSE);
  set_syntax(syntab, punctchars, SYN_PUNCT);
  set_syntax(syntab, escapechars, SYN_ESCAPE); 
}


// Emacs character syntax names. 
char syntax_names[NUMSYNTYPES]  = {'-', 'w', '_', '<', '\'', '"', '(', ')', '.', '\\'};

char syntax_name (charsyntax s) {
  return syntax_names[s-1];
}

charsyntax syntax_type (char c) {
  // char syntax names array is zero based, add 1 to found names's
  // postion to convert to char syntax type
  unsigned i;
  for (i = 0; i < NUMSYNTYPES; i++)
    if (syntax_names[i] == c) return (charsyntax)(i+1);
  return (charsyntax)0;
}

charsyntax char_syntax (SynTab tab, char c) {
  // TODO: this needs to handle unicode at some point!
  return (charsyntax) tab[ (c & 0x7f)] ;
}

int char_syntax_p (SynTab tab, char c, charsyntax syn) {
  return (syn == char_syntax(tab,c)) ? 1 : 0 ;
}

int char_white_p (SynTab tab, char c) {
  return char_syntax_p(tab,c,SYN_WHITE);
}

int char_word_p (SynTab tab, char c) {
  return char_syntax_p(tab,c,SYN_WORD) ;
}

int char_symbol_p (SynTab tab, char c) {
  return char_syntax_p(tab,c,SYN_SYMBOL) ;
}

int char_token_p (SynTab tab, char c) {
  int s = char_syntax(tab,c) ;
  return (s == SYN_WORD || s == SYN_SYMBOL || s == SYN_ESCAPE) ? 1 : 0 ;
}

int char_comment_p (SynTab tab, char c) {
  return char_syntax_p(tab,c,SYN_COMMENT) ;
}

int char_prefix_p (SynTab tab, char c) {
  return char_syntax_p(tab,c,SYN_PREFIX);
}

int char_string_p (SynTab tab, char c) {
  return char_syntax_p(tab,c,SYN_STRING) ;
}

int char_open_p (SynTab tab, char c) {
  return char_syntax_p(tab,c,SYN_OPEN) ;
}

int char_close_p (SynTab tab, char c) {
  return char_syntax_p(tab,c,SYN_CLOSE) ;
}

int char_punctuation_p (SynTab tab, char c) {
  return char_syntax_p(tab,c,SYN_PUNCT) ;
}

int char_escape_p (SynTab tab, char c) {
  return char_syntax_p(tab,c,SYN_ESCAPE) ;
} 

int angle_char_p (char c) {
  return ((c == '<') || (c == '>')) ? 1 : 0;
}

int curly_char_p (char c) {
  return ((c == '{') || (c == '}')) ? 1 : 0;
}

int square_char_p (char c) {
  return ((c == '[') || (c == ']')) ? 1 : 0;
}

int paren_char_p (char c) {
  return ((c == '(') || (c == ')')) ? 1 : 0;
}

int skip_syntax (SynTab tab, String str, const String syns, int pos, int end) {
  // advance forward or backward in str as long as char syntaxes
  // are in syns. if syns starts with ^ the search is NOT syns.
  // example "-" moves over whites, "^-" not whites, "w_" word or
  // symbol chars, "^w_" NOT word or symbol chars, etc.
#ifdef NOJUCE
  int len = strlen(syns);
#endif
#ifndef NOJUCE
  int len = syns.length();
#endif
  int neg = 0; 
  int dir = GETDIR(pos,end) , loc ;

  // ^ is negation search
  if (syns[0] == '^') neg = 1;
  //printf("inskip, dir=%d end=%d pos=%d\n", dir, end, pos);
  while (pos != end) {
    loc = neg; // starting char offset into syns
    while (loc < len) {
      //printf("str[%d]='%c'", pos, str[pos]);
      if ( char_syntax_p(tab, (char)str[pos],
			 syntax_type( (char)syns[loc])) )
	break;
      else loc++;
      //printf("skip\n");
    }
    if (neg == 0)                   // regular search
      if (loc < len) pos += dir;    // matched syntax
      else break;
    else                            // negation search
      if (loc == len) pos += dir;   // no match
      else break;
  }
  return pos;
}

int skip_chars (String str, const String chars, int pos, int end) {
  // advance forward or backward in str as long as current char in chars
  // if chars[0] is ^ then a negation search is performed
#ifdef NOJUCE
  int len = strlen(chars);
#endif
#ifndef NOJUCE
  int len = chars.length();
#endif
  int neg = 0; 
  int dir = GETDIR(pos,end) , loc ;

  // ^ is negation search
  if (chars[0] == '^') neg = 1;
  while (pos != end) {
    loc = neg; // starting char offset into chars
    while (loc < len) {
      if (  str[pos] == chars[loc] )
	break;
      else loc++;
    }
    if (neg == 0)                   // regular search
      if (loc < len) pos += dir;    // matched syntax
      else break;
    else                            // negation search
      if (loc == len) pos += dir;   // no match
      else break;
  }
  return pos;
}

int move_eol (String str, int pos, int end) {
  // move pos to end of line. str[pos] is on #\Newline 
  while (pos != end) {
    if ( EOL_P((char)str[pos]) )
      break;
    else pos++;
  }
  return pos;
}
  
int move_bol (String str, int pos, int end) {
  // move pos to start of line. str[pos-1] is #\Newline 
  pos--;
  while (pos > end) {
    if ( EOL_P((char)str[pos]) )
      break;
    else pos--;
  }
  //  return pos+1;
  return pos+1;
}

int column_of (const String str, int pos) {
  // count chars between pos and closest bol in str.
  int beg=move_bol(str, pos, -1);  
  return pos-beg;
}
  
int check_backward_comment (SynTab tab, String buf, int pos, int end) {
  // check backwards for comment start in current line and skip if
  // found. make sure comment is not a string that starts earlier in
  // the line. NOTE: the current check will lose if string begins on
  // an earlier line in buffer!
  int str = -1, com = -1, old = pos;
  while (pos != end) {
    if ( EOL_P((char)buf[pos]) )
      break;
    if ( char_comment_p(tab, (char)buf[pos]) )
      com = pos;
    else if ( char_string_p(tab, (char)buf[pos]) )
      str = pos;
    pos--;
  }
  if ( com > -1 )
    if ( (str == -1) || (str > com) ) // no str or str starts after com
      return com - 1;
    else return old;
  else return old;
}

int skip_white(SynTab tab, String str, int pos, int end, int skcom) {
  // if skcom is true then we skip over comments and continue trying
  // to skip whites
  int dir = GETDIR(pos, end), eol = 0;
  if ( dir == 0 ) return end;
  while ( (pos != end) && char_white_p(tab, (char)str[pos]) ) {
    if ( EOL_P( (char)str[pos]) )
      eol = 1;
    pos += dir;
  }
  // pos is now on nonwhite or at end. if skcom? and we are moving
  // backwards over a line break then check for comment and skip over
  // if it exists
  if ( (skcom == 0) || (pos == end) )
    return pos;
  else
    if ( (eol == 1) && BDIR_P(dir) ) {
      int p = check_backward_comment(tab, str, pos, end);
      if ( p != pos ) // a comment found, p is 1 before it
	if (skcom) // keep searching
	  return skip_white(tab, str, p, end, skcom);
	else
	  return p+1; //return pos of comment char
      else return pos;
    }
    else if ( skcom && FDIR_P(dir) && char_comment_p(tab, (char)str[pos]) ) {
      return skip_white(tab, str, move_eol(str,pos,end), end, skcom);
    }
    else return pos;
}

int search_delim(SynTab tab, String str, int pos, int end, char del) {
  int dir = GETDIR(pos, end);
  if (dir == 0) return end;
  if (del == 0)
    while ( (pos != end) && char_token_p(tab, (char)str[pos]) )
      pos += dir;
  else
    while ( (pos != end) && (str[pos] != del) )
      pos += dir;
  // pos is now on delim or at End. If not at end then check to see
  // if the delim is escaped. if it is then continue searching
  if ( FDIR_P(dir) )
    if ( (pos < end) &&      // didnt reach end
	 (pos > 0) &&        // 0=start of string
	 char_escape_p(tab, (char)str[pos-1]) )
      return search_delim(tab, str, pos+1, end, del);
    else return pos;
  else
    if ( ((pos - end) > 1) &&  // above first search pos
	 char_escape_p(tab, (char)str[pos-1])) 
      return search_delim(tab, str, pos-2, end, del);
    else return pos;
}

void substr(char * buf, String str, int beg, int end) {
  int i = 0;
  while (beg < end) {
    buf[i++]=(char)str[beg++];
  }
  buf[i]=(char)NULL;
}

int level_scan_p (int l, int a, int b, int c, int d) {
  return ( (l == a) && (l == b) && (l == c) && (l == d) ) ? 1 : 0;
}

//#define SCAN_COMMENTS 1

scanresult scan_sexpr(SynTab tab, String buf, int pos, int end, int mode,
		      int *stop, int *levs) {
  /* scan forward/backward in string advancing position pos 1 BEYOND the
   * next balanced sexpr in string, according to mode. End is the
   * EXCLUDING position at which scanning will stop. so to scan
   * backwards to the start of string, end should be -1, to scan
   * forwards to end of the string end should be length of str. The
   * final position of the scan is return in stop, and will never be a
   * constituent position of what was scanned.  Direction of scan is
   * controlled by pos relative to end: pos<end scans forward otherwise
   * the scan is backward. Returns a scantype indicating was scanned.
   */
  int typ = SCAN_EMPTY;
  int dir = GETDIR(pos, end), loc=0, par=0, sqr=0, cur=0, ang=0;
  bool skcom=true, skpar=false;

  if (mode==SCAN_COLOR) {
    skcom=false;
    skpar=true;
  }
  else if (mode==SCAN_PARSER) {
    skcom=true;
    skpar=false;
  }

  while (1) {
    pos = skip_white(tab, buf, pos, end, skcom);
    // pos is now on non-white char or at End
    if ( pos == end ) break;
    // now search for next delim
    loc = search_delim(tab, buf, pos, end, 0);
    // loc is now on next delim or at End. if loc actually moved (ie
    // is not equal to pos) then we've scanned over non-delim,
    // non-white chars (a token).
    if ( loc != pos ) {
      // advance past token, quit if at toplevel
      if ( level_scan_p(0, par, cur, sqr, ang) ) {
	pos = loc;
	typ = SCAN_TOKEN;
	break;
      }
      else pos = loc;
    }
    else {
      // pos is on delim (non-token)
      // handle the various syntax cases.
      char chr = (char)buf[loc];
      // STRING START. re-seach for end string char
      if ( char_string_p(tab, chr) ) {
	loc = search_delim(tab, buf, pos+dir, end, 34); //34='"'
	if ( loc == end ) {
	  // reached end without terminating
	  pos = end;
	  typ = SCAN_UNMATCHED;
	  break;
	}
	else if ( level_scan_p(0, par, cur, sqr, ang) ) {
	  pos = loc + dir;
	  typ = SCAN_STRING;
	  break;
	}
	else pos = loc + dir;
      }
      // FORWARD COMMENT. move to eol (backward comment
      // handled by skip_white if it sees eol)
      else if ( char_comment_p(tab, chr) ) {
	if (skcom) {
	  if ( FDIR_P(dir) )
	    pos = move_eol(buf, pos, end);
	  else pos = loc + dir;
	}
	else {
	  // move forward past 1 comment
	  typ=SCAN_COMMENT;
	  pos=loc + dir;
	  break;
	}
      }
      // PUNCTUATION. keep going unless parser mode
      else if ( char_punctuation_p(tab,chr) ) {
	pos = loc + dir;
	if (mode==SCAN_PARSER) {
	  typ=SCAN_PUNCT;
	  break;
	}
      }
      // PREFIX. keep going
      else if ( char_prefix_p(tab, chr) ) {
	pos = loc + dir;
      }
      // PARENS
      else if (skpar) {
	// we are ignoring parens
	pos = loc + dir;
      }
      else if (mode==SCAN_PARSER) {
	// parens are tokens for parser
	pos=loc+dir;
	if ( char_open_p(tab,chr)) {
	  typ=SCAN_OPEN;
	  break;
	}
	else if ( char_close_p(tab,chr) ) {
	  typ=SCAN_CLOSE;
	  break;
	}
      }
      // OPEN PAREN. increment level of approproate paren.
      else if ( ( FDIR_P(dir) && char_open_p(tab, chr) ) ||
		( BDIR_P(dir) && char_close_p(tab, chr) ) ) {
	if ( paren_char_p(chr) ) par++;
	else if ( curly_char_p(chr) ) cur++;
	else if ( square_char_p(chr) ) sqr++;
	//	else if ( angle_char_p(chr) ) ang++;
	pos = loc + dir;
      }
      // CLOSE PAREN. if level is already zero we can't go further
      else if ( ( FDIR_P(dir) && char_close_p(tab, chr) ) ||
		( BDIR_P(dir) && char_open_p(tab, chr) ) ) {
	if ( paren_char_p(chr) ) 
	  if ( par == 0 ) typ = SCAN_UNLEVEL; else par--;
	else if ( curly_char_p(chr) ) 
	  if ( cur == 0 ) typ = SCAN_UNLEVEL; else cur--;
		else if ( square_char_p(chr) ) 
		  if ( sqr == 0 ) typ = SCAN_UNLEVEL; else sqr--;
	//	else if ( angle_char_p(chr) ) 
	//	  if ( ang == 0 ) typ = SCAN_UNLEVEL; else ang--;
	if ( typ < 0 ) {
	  pos = loc + dir;
	  break;
	}
	else if ( level_scan_p(0, par, cur, sqr, ang) ) {
	  pos = loc + dir;
	  typ = SCAN_LIST;
	  break;
	}
	else {
	  pos = loc + dir;
	}
      }
    }
  } // end while loop

  // set stop postion and return scanresult
  if ( typ < 0 ) {
    *stop = pos;
    return (scanresult) typ;
  }
  else if ( level_scan_p(0, par, cur, sqr, ang) ) {
    // include any prefix chars...
    if ( BDIR_P(dir) ) 
      pos = skip_syntax(tab, buf, T("\'"), pos, end);
    *stop = pos;
    return (scanresult) typ;
  }
  else {
    *stop = pos;
    return (scanresult) SCAN_UNMATCHED; 
  }
}

scanresult parse_sexpr(SynTab tab, String str, int bot, int top, int dir, 
		       int mode, int * poz, int * s1, int * s2) {
  // finds lower and upper bounds of the next sexpr before or after
  // poz. if there is a sexpr then s1 is set to its lower inclusive
  // bounds, s2 to its upper exclusive bounds, and poz to 1 char past
  // the far end of the sexpr. dir is the direction of the search and
  // should be 1 for forward or -1 for backward. if the scan fails
  // then poz, s1 and s2 are NOT updated. parse_sexpr returns the
  // status of the scan as its value.
  int typ;
  int pos = *poz, loc, chk, end, opp;

  if ( dir < 0 ) {
    end = bot;
    opp = top;
  }
  else {
    end = top;
    opp = bot;
  }
  typ = scan_sexpr(tab, str, pos, end, mode, &pos, NULL);
  chk=typ;
  if (typ < 1) {
    *poz=pos;
  }
  else if (typ==SCAN_COMMENT) {
    if (dir>0) 
      *s1=pos-1;
    else *s1=pos+1;
    *s2=move_eol(str, pos, end);
    *poz=*s2;
  }
  else {
    // now have the far side, reverse the scan back towards starting
    // position to find the near side. this skips whitespace and
    // comments
    chk = scan_sexpr(tab, str, pos-dir, opp, mode, &loc, NULL);
    if ( typ != chk ) {
      printf("Shouldn't: type mismatch %d and %d (pos=%d, end=%d).",
	     typ, chk, pos, opp);
      typ=SCAN_MISMATCH;  // metaerror??
    }
    else {
      if ( dir > 0 ) {
	*s1=loc+1;
	*s2=pos;
	*poz=pos; //update to 1 above the last char in sexpr
      }
      else {
        *s1=pos+1;
	*s2=loc;
	*poz=pos; //update to 1 below the first char in sexpr
      }
    }
  }  
  return (scanresult)typ;
}  

#ifdef SCANTEST

///
///                           Testing
///

#define TESTBUFLEN 150000
char buffer[TESTBUFLEN];

void show_words(SynTab tab, String str, int len, int dir, int pos) ;
void show_parse (SynTab tab, String str, int len, int dir, int poz, int mode) ;
//void show_sexprs(SynTab tab, String str, int len, int dir, int pos) ;

int main (int argc, char** argv) {
  FILE * fp;
  SynTab tab;
  char c;
  char file[256];
  int len = 0, i;
  int dir = FDIR;
  int tst = SCAN_CODE;
  int pos = -666;
  int sty = 0;
  
  if ( argc < 2 ) {
    printf("Usage:\na.out [-b -w -c -p] filename\n");
    printf("      default is FORWARD SEXPR scan\n");
    printf("      -b=BACKWARD, -w=WORD, -c=COLOR -t=TOKEN -p=PARSER\n"); // -p=starting postion
    return 0;
  }

  for (i = 1; i < argc; i++) 
    if (argv[i][0] == '-')
      switch (argv[i][1]) {
      case 'b' : 
	dir=BDIR;
	break;
      case 'f':
	dir=FDIR;
	break;
	//      case 'p':
	//	pos = atoi(argv[++i]) ;
	//	break;
      case 'w':
	tst = 0;
	break;
      case 'p':
	tst = SCAN_PARSER;
	break;
      case 's':
	tst = SCAN_CODE;
	break;
      case 'c':
	tst = SCAN_COLOR;
	break;
      default: 
	printf("Unknown switch %s\n", argv[i]);
      }

  strcpy(file, argv[argc-1] );
  if ( (strlen(file) > 6) && (0 == strcmp(".lisp", &file[strlen(file)-5]) )) {
    init_syntab(tab, T(""), T(""), T("~!@$%^&*-_=+[{]}|:<.>/?"),
		T(";"), T("`#',"), T("\""), T("("), T(")"), T(","), T("\\") ) ;
    sty=0;
  }
  else if ( (strlen(file) > 5) && (0 == strcmp(".sal", &file[strlen(file)-4])) ) {
    init_syntab(tab, T(""), T(""), T("~!@$%^&*-_=+|:<.>/?"),
	      T(";"), T("#`'"), T("\""), T("([{"), T(")]}"), T(","), T("\\") );
    sty=1;
  }
  else {
    printf("File '%s' not .sal or .lisp file.\n", file);
    return -1;
  }

  fp = fopen(file, "r");
  if (fp == NULL) {
    printf("Can't open file '%s'.\n", file);
    return -1;
  }

  while (1) {
    c = fgetc(fp);
    if ( (c == EOF) || (len == TESTBUFLEN) ) break;
    buffer[len] = c;
    len++;
  }

  if (len == TESTBUFLEN) {
    printf( "Fix me: input buffer length ~%d < filelength.",
	    len);
    fclose(fp);
    return -1;
  }
  buffer[len] = (char)NULL;
  fclose(fp);

  if (pos == -666)
    pos = (FDIR_P(dir)) ? 0 : len - 1;
  else
    if (pos < 0) 
      pos = len + pos + -1;

  //----------------------------------
  printf("----------------------------------\n");
  printf("Scanning '%s':\n", file);
  printf("  buffer=%d\n", len);
  if (sty == 0) printf("  syntax=LISP\n");
  else printf("  syntax=SAL\n");
  if (FDIR_P(dir) ) printf("  direction=FORWARD\n");
  else printf("  direction=BACKWARD\n");
  printf("  start=%d\n", pos);
  if (tst == 0 ) printf("  motion=WORD\n");
  else if (tst == SCAN_CODE ) printf("  motion=SEXPR\n");
  else if (tst == SCAN_PARSER ) printf("  motion=PARSER\n");
  else printf("  motion=COLOR\n");
  printf("\n");
  if (tst == 0 )
#ifdef NOJUCE
    show_words(tab, buffer, len, dir, pos);
#endif
#ifndef NOJUCE
  show_words(tab, String(buffer), len, dir, pos);
#endif
  else
#ifdef NOJUCE
    show_parse(tab,buffer,len,dir, pos, tst);
#endif
#ifndef NOJUCE
    show_parse(tab,String(buffer),len,dir,pos,tst);
#endif
  printf("----\nbye!\n");
  return 0;
}

void show_words(SynTab tab, String str, int len, int dir, int pos) {
  // scan forward/backward a la Emacs' M-f motion by skipping over any
  // non-word chars and then moving over word chars
  int end, loc;
  char sub[65536];
  end = ( FDIR_P(dir) ) ? len : -1;
  while (pos != end) {
    pos = skip_syntax(tab, str, T("^w_"), pos, end);
    // pos is at End or at first char of word. now scan over
    // WORD syntax to find far side of word
    if (pos != end) {
      loc = skip_syntax(tab, str, T("w_"), pos, end);
      // loc is at end or next char NOT word
      if ( FDIR_P(dir) )
	substr(sub, str, pos, loc);
      else substr(sub, str, loc+1, pos+1);
      printf("%s ", sub);
      pos = loc;
    }
  }
  printf("\n");
}

char * labl(int i) {
  if (i == -3) return "Mismatched";
  if (i == -2) return "Unmatched";
  if (i == -1) return "Unlevel";
  if (i == 0) return "Empty";
  if (i == 1) return "Token";
  if (i == 2) return "String";
  if (i == 3) return "List";
  if (i == 4) return "Comment";
  if (i == 5) return "Open";
  if (i == 6) return "Close";
  if (i == 7) return "Punct";
  return "UNKNOWN";
}

void show_parse (SynTab tab, String str, int len, int dir, int poz, int mode) {
  char sub[65536];
  int pos = poz, start, end;
  scanresult typ;

  while (1) {
    typ=parse_sexpr(tab,str,-1,len,dir,mode,&pos,&start,&end);
    if ( typ < 1  ) {
      if ( typ < 0 ) 
	printf("ERROR: \"%s\"\t(pos=%d)\n",labl(typ) , pos); 
      break;
    } 
    else {
      substr(sub, str, start, end);
      printf("%s:\t\"%s\"\n", labl(typ), sub);
    }
  }
}

/*
void show_sexprs (SynTab tab, String str, int len, int dir, int poz) {
  int num = 0, old, end, opp;
  char sub[65536];
  int pos = poz, loc;
  scanresult typ, chk;

  if ( FDIR_P(dir) ) {
    end = len;
    opp = -1;
  }
  else {
    end -1;
    opp = len;
  }

  old = pos;
  while (1) {
    typ = scan_sexpr(tab, str, old, end, SCAN_CODE, &pos, NULL);
    if ( typ < 1 ) {
      if ( typ < 0 ) 
	printf("\"%s\"\t(pos=%d)\n",labl(typ) , pos); //labs[typ + 2]
      break;
    }
    else {
      chk = scan_sexpr(tab, str, pos-dir, opp, SCAN_CODE, &loc, NULL);
      if ( typ != chk )
	printf("Shouldn't: type mismatch %d and %d (pos=%d, end=%d).",
	       typ, chk, loc, opp);
      else {
	if ( FDIR_P(dir) )
	  substr(sub, str, loc+1, pos);
	else substr(sub, str, pos+1, loc);
	printf("%s:\t\"%s\"\n", labl(typ), sub); //labs[typ+2]
      }
    }
    old = pos;
  }
  printf("\n");
}

*/

#endif
