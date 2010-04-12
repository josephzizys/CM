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

class CodeBuffer : public CodeEditorComponent //, public Timer
{
 public:
  Syntax* syntax;
  ApplicationCommandManager* manager;
  CodeDocument& document;

  CodeBuffer(CodeDocument& _document, Syntax* _tokenizer, ApplicationCommandManager* commands, XmlElement* custom);
  ~CodeBuffer() ;
  bool keyPressed (const KeyPress& key);
  void mouseDoubleClick (const MouseEvent &e);
  void focusGained(Component::FocusChangeType cause);

  KeyPress prevkey;
  int matchpos;
  int fontsize;
  int tabwidth;
  int columns;
  int lines;
  bool emacsmode;
  bool changed;
  bool parensmatching;
  XmlElement* colortheme;
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
  void setColorTheme(XmlElement* theme);
  XmlElement* getColorTheme();

  bool isChanged();
  void isChanged(bool changed);
  bool isEmacsMode();
  void isEmacsMode(bool mode);

  bool isParensMatching();
  void isParensMatching(bool matching);
  bool isParensMatchingActive();
  void matchParens();
  void startParensMatching(const CodeDocument::Position pos1, const CodeDocument::Position pos2);
  void stopParensMatching();
  void timerCallback();

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
  CodeDocument::Position gotoBOL(bool sel=false);
  CodeDocument::Position gotoEOL(bool sel=false);
  CodeDocument::Position gotoBOB(bool sel=false);
  CodeDocument::Position gotoEOB(bool sel=false);
  void moveCharForward(bool sel=false);
  void moveCharBackward(bool sel=false);
  void moveWordForward(bool sel=false);
  void moveWordBackward(bool sel=false);
  void moveExprForward(bool sel=false);
  void moveExprBackward(bool sel=false);
  void moveLineForward(bool sel=false);
  void moveLineBackward(bool sel=false);
  void movePageForward(bool sel=false);
  void movePageBackward(bool sel=false);
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
  // Find/Replace
  bool replaceAll(String str, String rep);
  bool replace(String rep);
  bool replaceAndFind(String str, String rep);
  bool findPrevious(String str, bool wrap=true);
  bool findNext(String str, bool wrap=true);

  void eval(bool expandonly);
  void evalLisp(const CodeDocument::Position start, const CodeDocument::Position end, bool expand, bool region);
  void evalSal(const CodeDocument::Position start, const CodeDocument::Position end, bool expand, bool region);
  void indent();
  //  int lastIndented(Array<int>& ary, bool index);
  //  bool isCommaTerminatedLine(int line);
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

  // window's content component
  class EditorComponent : public Component 
  {
    void resized () 
    {
      if (buffer)
        buffer->setBounds(0, 0, getWidth(), getHeight());
    }
  public:
    CodeBuffer* buffer;
    EditorComponent ()
      : buffer (NULL)
      {
      }
    ~EditorComponent()
      {
        //deleteAllChildren();
        //deleteCodeBuffer();
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
  void updateKeyPressesForEditMode();
  void isEmacsMode(bool mode);
  bool isEmacsMode();

  void saveFile(bool saveas);
  void saveFileAs();
  // static methods
  static void openFile(File file=File::nonexistent);
  static void newFile(String title=String::empty, int synt=TextIDs::Empty, String content=String::empty);
  static CodeEditorWindow* getFocusCodeEditor();
  static void openFindAndReplaceDialog();

};

#endif
