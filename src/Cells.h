/*=======================================================================*
  Copyright (c) 2009 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#ifndef CELLS_H
#define CELLS_H

#include "juce.h"

class CellView : public Component 
{
 public:
  int cellRows;
  int cellColumns;
  int cellSize;
  int cellBorderSize;
  Array<int> states;
  Array<Colour> colors;
  CellView(int rows, int cols, int cellsize, int bordersize);
  ~CellView();
  void resized();
  void paint(Graphics& g);
  void drawCell(int row, int col, int state);
  static int XY(int x, int y=0);
  static int XY_X(int xy);
  static int XY_Y(int xy);
  static int XY_ADD(int xy1, int xy2);
};

class CellWindow : public DocumentWindow 
{
 public:
  class CellWindowListener : public MessageListener
  {
    CellWindow* window;
  public:
    CellWindowListener(CellWindow* w);
    ~CellWindowListener();
    void handleMessage (const Message &message);  
  };
  CellWindowListener listener;
  CellWindow (String title, String states, String colors, int rows, int cols, int cellsize, int bordersize) ;
  ~CellWindow () ;
  void initCellWindow(String title, String states, String colors, int rows, int cols, int cellsize, int bordersize);
  void closeButtonPressed();
  static CellWindow* findCellWindow(String title);

};

#endif

