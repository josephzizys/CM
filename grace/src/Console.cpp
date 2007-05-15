/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

//#include "Editor.h"
#include "Console.h"

/* 
 * Console Window
 */

ConsoleWindow::ConsoleWindow ()
  : DocumentWindow (T("Console") , Colours::white, 
		    DocumentWindow::allButtons, true ) {
  // create underlying edit buffer
  console = new EditorComponent( T("console.log"), syntaxConsole) ;
  // IO colors are "Clarity and Beauty" by Richard Wellum
  inputColour = Colours::white;
  outputColour = Colours::lightsalmon;
  errorColour = Colours::red;
  warningColour = Colours::orange;

  console->buffer->setColour( TextEditor::backgroundColourId, Colours::black);
  console->buffer->setColour( TextEditor::textColourId, Colours::lightsalmon);
  console->buffer->setColour( TextEditor::highlightColourId, Colours::blue);
  console->buffer->setColour( TextEditor::highlightedTextColourId, 
			      Colours::lightsalmon);
  console->buffer->setColour( TextEditor::caretColourId, Colours::yellow);
  console->buffer->setVisible(true);
  console->setVisible(true);
  setContentComponent(console);
  console->setSize(450,340); //280
  centreWithSize (450, 340);
  setResizable(true, true); 
  setVisible(true);
}

ConsoleWindow::~ConsoleWindow () {
}

// arrrrg! this doesnt work when i click on the titlebar
//void ConsoleWindow::activeWindowStatusChanged () {
//  if ( isActiveWindow() ) 
//    console->buffer->grabKeyboardFocus();
//}

void ConsoleWindow::closeButtonPressed () {
  if (AlertWindow::showOkCancelBox
      (AlertWindow::QuestionIcon, T("Quit"),
       T("Really quit Grace? Any unsaved work will be lost."),
       String::empty, String::empty)
      )
    JUCEApplication::quit();
}

TextBuffer * ConsoleWindow::consoleBuffer() {
  return console->buffer;
}
void ConsoleWindow::toggleColourInput() {
  console->buffer->setColour( TextEditor::textColourId, inputColour);
}

void ConsoleWindow::toggleColourOutput() {
  console->buffer->setColour( TextEditor::textColourId, outputColour);
}

void ConsoleWindow::toggleColourError() {
  console->buffer->setColour( TextEditor::textColourId, errorColour);
}

void ConsoleWindow::toggleColourWarning() {
  console->buffer->setColour( TextEditor::textColourId, warningColour);
}

void ConsoleWindow::consolePrint(printType mode, String str) {
  int here = console->buffer->point();
  // (! console->buffer->isEmpty() )

  if (console->buffer->pointLineLength() != 0 ) {
    console->buffer->gotoEOL();
    console->buffer->insertText( T("\n") );
  }
  switch (mode) {
  case textWarning:
    toggleColourWarning();
    break;
  case textError:
    toggleColourError();
    break;
  case textMessage:
  default:
    toggleColourOutput();
    break;
  }
  console->buffer->insertText(str);
  console->buffer->setPoint(here); // move back to where we were
  toggleColourInput();
}

void ConsoleWindow::consoleFreshLine() {
  if ( ! console->buffer->isBOL() )
    console->buffer->insertText( T("\n") );
}

