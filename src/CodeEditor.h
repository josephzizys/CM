/*=======================================================================*
   Copyright (C) 2010 Rick Taube.
   This program is free software; you can redistribute it and/or modify  
   it under the terms of the Lisp Lesser Gnu Public License. The text of 
   this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#ifndef CmCodeEditor_h
#define CmCodeEditor_h

#include "juce.h"

class Syntax;
class SynTok;

/*=======================================================================*/

class ScanFlags
{
 public:
  static const int Empty=0;
  static const int MoveExpressions=1;
  static const int MoveTokens=2;
  static const int MoveWhiteAndComments=3;
  enum
  {
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
  static const String scanResultToString(int res)
  {
    switch (res)
      {
      case SCAN_MISMATCH: return T("mismatch");
      case SCAN_UNMATCHED: return T("unmatched");
      case SCAN_UNLEVEL: return T("unlevel");
      case SCAN_EMPTY: return T("empty");
      case SCAN_TOKEN: return T("token");
      case SCAN_STRING: return T("string");
      case SCAN_LIST: return T("list");
      case SCAN_COMMENT: return T("comment");
      case SCAN_OPEN: return T("open");
      case SCAN_CLOSE: return T("close");
      case SCAN_PUNCT: return T("puctuation");
      default: return T("unknown");
      }
  }
};

class CodeBuffer : public CodeEditorComponent //,   public Timer
{
 public:
  Syntax* syntax;
  ApplicationCommandManager* manager;
  CodeDocument& document;
  CodeBuffer(CodeDocument& _document, Syntax* _tokenizer, ApplicationCommandManager* commands, XmlElement* custom);
  ~CodeBuffer() ;
  KeyPress prevkey;
  int fontsize;
  int tabwidth;
  int columns;
  int lines;
  bool emacsmode;
  bool parensmatching;
  bool changed;
  bool keyPressed (const KeyPress& key);
  void mouseDoubleClick (const MouseEvent &e);
  int getTextType();
  bool isTextType(int type);
  int getFontSize();
  void setFontSize(int size);
  int getTabWidth();
  void setTabWidth(int siz);

  int getColumns();
  void setColumns(int num, bool redisplay=true);

  int getLines();
  void setLines(int num, bool redisplay=true);

  bool isChanged();
  void isChanged(bool changed);
  bool isParensMatching();
  void isParensMatching(bool match);
  bool isEmacsMode();
  void isEmacsMode(bool mode);
  void timerCallback(){}

  // cursor postion functions
  CodeDocument::Position getBOB();
  CodeDocument::Position getEOB();
  CodeDocument::Position getBOL(); 
  CodeDocument::Position getEOL();
  CodeDocument::Position getBOL(const CodeDocument::Position pos); 
  CodeDocument::Position getEOL(const CodeDocument::Position pos);
  bool lookingAt(const CodeDocument::Position pos, const String text, const bool forward, const bool delimited);
  bool isBOB();
  bool isEOB();
  bool isBOL();
  bool isEOL();
  CodeDocument::Position gotoBOL();
  CodeDocument::Position gotoEOL();
  CodeDocument::Position gotoBOB();
  CodeDocument::Position gotoEOB();
  void moveCharForward();
  void moveCharBackward();
  void moveWordForward();
  void moveWordBackward();
  void moveLineForward();
  void moveLineBackward();
  void movePageForward();
  void movePageBackward();
  void moveExprForward();
  void moveExprBackward();
  // Emacs editing
  void killCharForward();
  void killCharBackward();
  void killWordForward();
  void killWordBackward();
  void killExprForward();
  void killExprBackward();
  void killLine();
  void killWhite();
  void killRegion();
  void changeCase(int change);
  void openLine();

  bool scanEOL(CodeDocument::Position& pos);
  bool scanBOL(CodeDocument::Position& pos);
  bool scanToken(CodeDocument::Position& pos, const int dir, const CodeDocument::Position end);
  bool scanPrefix(CodeDocument::Position& pos, const int dir, const CodeDocument::Position end);
  bool scanCharacter(tchar chr, CodeDocument::Position& pos, const int dir, const CodeDocument::Position end);
  int scanCode(CodeDocument::Position& pos, bool forward, int mode, int limit=-1);

  void eval(bool expandonly);
  void evalLisp(const CodeDocument::Position start, const CodeDocument::Position end, bool expand, bool region);
  void evalSal2(const CodeDocument::Position start, const CodeDocument::Position end, bool expand, bool region);
  int backwardLispExpr(CodeDocument::Position& from, CodeDocument::Position& to);
  int backwardSal2Expr(CodeDocument::Position& from, CodeDocument::Position& to);
  void indent();
  int indentLisp();
  int indentSal2();
  int lastIndented(Array<int>& ary, bool index);
  bool isCommaTerminatedLine(int line);
  bool tokenizeSal(const CodeDocument::Position start, const CodeDocument::Position end,
                   OwnedArray<SynTok>& tokens);
  int isNumberToken(const String str);

  // testing
  void test(bool forward);
  void posInfo(const CodeDocument::Position pos);
};
 
/*=======================================================================*/

class CodeEditorWindow : public DocumentWindow, public MenuBarModel,
  public ApplicationCommandTarget
{
  ApplicationCommandManager commands;
  class EditorComponent : public Component 
  {
    void resized () 
    {
      if (buffer)
        buffer->setBounds(0, 0, getWidth(), getHeight());
    }
  public:
    CodeBuffer* buffer;
    EditorComponent (CodeBuffer* buf)
      {
        setCodeBuffer(buf);
      }
    ~EditorComponent()
      {
	//delete buffer;
        deleteAllChildren();
      }
    CodeBuffer* getCodeBuffer() 
    {
      return buffer;
    }
    void setCodeBuffer(CodeBuffer* buf) 
    {
      buffer=buf;
      buffer->setTopLeftPosition(0,0);
      addChildComponent(buffer, -1);
    }
    void deleteCodeBuffer()
    {
      CodeBuffer* buf=buffer;
      buffer=0;
      removeChildComponent(buf);
      delete buf;
    }
  };

 public:
  CodeDocument document;
  File sourcefile;

  CodeEditorWindow(File file, String text=String::empty, int synt=0, String title=String::empty) ;
  ~CodeEditorWindow () ;
  void closeButtonPressed () ;
  void getAllCommands(Array<CommandID>& commands);
  ApplicationCommandTarget* getNextCommandTarget();
  void getCommandInfo(const CommandID id, ApplicationCommandInfo& info);
  bool perform(const ApplicationCommandTarget::InvocationInfo& info);
  const StringArray getMenuBarNames ();
  const PopupMenu getMenuForIndex(int menuIndex, const String& menuName);
  void menuItemSelected (int menuItemID, int topLevelMenuIndex);

  void setWindowTitle(String title=String::empty);
  void resizeForColumnsAndLines();
  CodeBuffer* getCodeBuffer();

  bool isCustomComment();
  XmlElement* getCustomizations();
  void writeCustomComment(bool select);
  void applyCustomComment();
  void switchBufferSyntax(int newtype);
  //  void saveFile();
  void saveFile(bool saveas);
  void saveFileAs();
  static void openFile(File file=File::nonexistent);
  static void newFile(String title=String::empty, int synt=TextIDs::Empty, String content=String::empty);
};

#endif
