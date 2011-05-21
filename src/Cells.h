/*=======================================================================*
  Copyright (c) 2009 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#ifndef CELLS_H
#define CELLS_H

#include "Libraries.h"

class CellView : public Component 
{
 public:
  int cellRows;
  int cellColumns;
  int cellSize;
  int cellBorderSize;
  Colour backgroundColor;
  int maxGenerations;
  int generation;
  int noState;
  Array<int, CriticalSection> data;
  Array<int> states;
  Array<Colour> colors;
  CellView(String statesandcolors, int rows, int cols, int cellsize, int bordersize, Colour bgcolor, int gens);
  ~CellView();

  void resized();
  void paint(Graphics& g);

  void drawStates(int numstates, int* states);
  void setStatesAndColors(String statesandcolors);
  void setRowsAndColumns(int rows, int cols);
  void setCellSize(int size, int bordersize=1);

  static int XY(int x, int y=0);
  static int XY_X(int xy);
  static int XY_Y(int xy);
  static int XY_ADD(int xy1, int xy2);
};

class StateWindow : public DocumentWindow 
{
 public:
  class StateWindowListener : public MessageListener
  {
  public:
    StateWindow* window;
    StateWindowListener();
    ~StateWindowListener();
    void handleMessage (const Message &message);  
  };
  StateWindowListener listener;
  StateWindow (String title, String statesandcolors, int rows, int cols, int cellsize=50, int bordersize=1, Colour bgcolor=Colours::white) ;
  ~StateWindow () ;
  void closeButtonPressed();
  static StateWindow* findStateWindow(String title);
  //static void openWindowFromXml(char* xml);
  static void openWindowFromXml(void* xml);
  CellView* getCellView();
};

#endif

