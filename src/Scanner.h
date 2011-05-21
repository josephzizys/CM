/*************************************************************************
 * Copyright (C) 2008, Rick Taube.                                       *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

#ifndef SCANNER_H
#define SCANNER_H



#ifndef NOJUCE
#include "Libraries.h"
#endif

#ifdef NOJUCE
typedef char * String;
char * T(char * s) {return s;};
#endif

/* 
   This file implements low level char scanning based on syntax tables
   a la emacs. scanning code does not need any JUCE classes except
   String and treats it is just a buffer of chars, ie as if it were
   "typedef char * String".


    0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15
00  NUL SOH STX ETX EOT ENQ ACK BEL BS  HT  LF  VT  FF  CR  SO  SI
16  DLE DC1 DC2 DC3 DC4 NAK SYN ETB CAN EM  SUB ESC FS  GS  RS  US
32   SP  !   "   #   $   %   &   '   (   )   *   +   ,   -   .   /
48   0   1   2   3   4   5   6   7   8   9   :   ;   <   =   >   ?
64   @   A   B   C   D   E   F   G   H   I   J   K   L   M   N   O
80   P   Q   R   S   T   U   V   W   X   Y   Z   [   \   ]   ^   _
96   `   a   b   c   d   e   f   g   h   i   j   k   l   m   n   o
112  p   q   r   s   t   u   v   w   x   y   z   {   |   }   ~ DEL  
*/

/* Scanning modes */

enum scanmode {
  SCAN_CODE = 1,    // skip over comments, parse list levels
  SCAN_COLOR,       // scan comments, dont parse list levels
  SCAN_PARSER
};


/*
 * Result codes for scanner, anomolies are < 1. Unmatched means the
 * scan ended with an open delimiter that was not matched by a closing
 * delimiter. Unlevel means the scanning could not advance backward
 * over an Open or forward over a Close. Empty measn nothing was
 * encounted (ie scan's start=end or scanned region contained only
 * white space). Types above 0 indicate what the scanning encounted:
 * tokens (things like numbers and symbols), lists or strings.
 */

enum scanresult  {
  SCAN_MISMATCH = -3,   // Shouldn't happen
  SCAN_UNMATCHED,
  SCAN_UNLEVEL,
  SCAN_EMPTY,    // must be zero
  SCAN_TOKEN,
  SCAN_STRING,
  SCAN_LIST,
  SCAN_COMMENT,
  SCAN_OPEN,
  SCAN_CLOSE,
  SCAN_PUNCT
};

/*
 * Emacs syntax classes. Types and names must be defined in same
 * order! For now types are disjoint. They will have to become bit
 * fields if scanning is to support 2 char comments, multiline
 * comments, etc.
 */

enum charsyntax {
  SYN_WHITE = 1,
  SYN_WORD,
  SYN_SYMBOL,
  SYN_COMMENT,     // only single char comment lasting to EOL for now
  SYN_PREFIX,
  SYN_STRING,
  SYN_OPEN,
  SYN_CLOSE,
  SYN_PUNCT,
  SYN_ESCAPE
};

#define NUMSYNTYPES 10

typedef char SynTab [128]; 

#define SYNTAB_LEN 128

// end of line char, fix for DOS!
#define EOLC 10

// forward scanning
#define FDIR 1

// backward scanning
#define BDIR -1

void set_syntax (SynTab tab, String chrs, charsyntax syn) ;
void init_syntab (SynTab tab, String whitechars, String wordchars, 
		  String symbolchars, String commentchars, 
		  String prefixchars, String stringchars,
		  String openchars, String closechars,
		  String punctchars, String escapechars) ;
char syntax_name (charsyntax s) ;
charsyntax syntax_type (char c) ;
charsyntax char_syntax (SynTab tab, char c) ;
int char_syntax_p (SynTab tab, char c, charsyntax syn) ;
int char_white_p (SynTab tab, char c) ;
int char_word_p (SynTab tab, char c) ;
int char_symbol_p (SynTab tab, char c) ;
int char_token_p (SynTab tab, char c) ;
int char_comment_p (SynTab tab, char c) ;
int char_prefix_p (SynTab tab, char c) ;
int char_string_p (SynTab tab, char c) ;
int char_open_p (SynTab tab, char c) ;
int char_close_p (SynTab tab, char c) ;
int char_punctuation_p (SynTab tab, char c) ;
int char_escape_p (SynTab tab, char c) ;
int angle_char_p (char c) ;
int curly_char_p (char c) ;
int square_char_p (char c) ;
int paren_char_p (char c) ;
int skip_syntax (SynTab tab, String str, const String syns, int pos, int end) ;

int skip_chars (String str, const String chars, int pos, int end) ;
int move_bol (String str, int pos, int end) ;
int move_eol (String str, int pos, int end) ;
int column_of(String str, int pos) ;

int check_backward_comment (SynTab tab, String buf, int pos, int end) ;
int skip_white(SynTab tab, String str, int pos, int end, int skcom) ;
int search_delim(SynTab tab, String str, int pos, int end, char del) ;
void substr(char * buf, String str, int beg, int end) ;
scanresult scan_sexpr(SynTab tab, String buf, int start, int end, int mode, 
		      int *stop, int *levs) ;
scanresult parse_sexpr(SynTab tab, String str, int bot, int top, int dir, 
		       int mode, int * poz, int * s1, int * s2) ;
#endif
