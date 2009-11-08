/*=======================================================================*
  Copyright (c) 2009 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify
  it under the terms of the Lisp Lesser Gnu Public License. The text
  of this agreement is available at http://www.cliki.net/LLGPL
 *=======================================================================*/

#include "Enumerations.h"
#include "Cells.h"
#include <iostream>

CellView::CellView(int rows, int cols, int cellsize, int bordersize)
  : cellRows(rows),
    cellColumns(cols),
    cellBorderSize (bordersize),
    cellSize (cellsize)
{ 
  setVisible(true);
}

void CellView::resized()
{
}

CellView::~CellView()
{
  colors.clear();
  states.clear();
}

int CellView::XY(int x, int y)
{
  if (x < 0) x += 0x10000;
  if (y < 0) y += 0x10000;
  return ((y & 0xffff) << 16) | (x & 0xffff);
}

int CellView::XY_X(int xy)
{
  int x = (xy & 0xffff);
  return (x >= 0x8000) ? (x - 0x10000) : x;
}

int CellView::XY_Y(int xy)
{
  int y = ((xy & 0xffff0000) >> 16);
  return (y >= 0x8000) ? (y - 0x10000) : y;
}

int CellView::XY_ADD(int xy1, int xy2)
{
  return XY(XY_X(xy1) + XY_X(xy2), XY_Y(xy1) + XY_Y(xy2));
}

void CellView::paint (Graphics& g)
{
  g.fillAll(Colours::azure);
  //  g.setColour (linecolor);
  //  g.drawRect (0, 0, getWidth(), getHeight(), linewidth);
  int x=0, y=0;
  int s=0;
  for (int r=0; r<cellRows; r++)
    {
      x=0;
      for (int c=0; c<cellColumns; c++)      
	{
	  g.setColour(colors[s % colors.size()]);
	  g.fillRect(x, y, cellSize, cellSize);
	  x += (cellSize+cellBorderSize);
	  s++;
	}
      y += (cellSize+cellBorderSize);

    }
}

CellWindow::CellWindow (String title, String states, String colors, int rows, int cols, int cellsize=8, int bordersize=1)
  : DocumentWindow (title, Colours::white, DocumentWindow::allButtons, true),
    listener(this)
{
  CellView* cv=new CellView(rows,cols,cellsize,bordersize);
  cv->colors.add(Colours::red);
  cv->colors.add(Colours::green);
  cv->colors.add(Colours::blue);
  setResizable(true, true); 
  setContentComponent(cv);
  int size=cellsize + bordersize;
  int width=size*cols;
  int height=size*rows;
  std::cout << "width=" << width << " height=" << height << "\n";
  //  cv->setSize(width,height);
  setContentComponentSize(width,height);
  centreWithSize(getWidth(), getHeight());
  //setComponentProperty(T("WindowType"), WindowTypes::PlotWindow);
  setVisible(true);
}

void CellWindow::initCellWindow(String title, String states, String colors, int rows, int cols, int cellsize, int bordersize)
{
}

CellWindow::~CellWindow ()
{
}

void CellWindow::closeButtonPressed()
{
  delete this;
}

CellWindow* CellWindow::findCellWindow(String title)
{
  return 0;
}

CellWindow::CellWindowListener::CellWindowListener(CellWindow* win) 
  : window (win)
{
}

CellWindow::CellWindowListener::~CellWindowListener()
{
}

void CellWindow::CellWindowListener::handleMessage(const Message &m)
{
  switch (m.intParameter1)
    {
    default:
      std::cout << "Cell Window message!\n";
    }
}

