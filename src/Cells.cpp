/*=======================================================================*
  Copyright (c) 2009 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify
  it under the terms of the Lisp Lesser Gnu Public License. The text
  of this agreement is available at http://www.cliki.net/LLGPL
 *=======================================================================*/

#include "Enumerations.h"
#include "Cells.h"
#include "Console.h"
#include <iostream>

CellView::CellView(String statesandcolors, int rows, int cols, int cellsize, int bordersize, Colour bgcolor, int gens)
  : cellRows (rows),
    cellColumns (cols),
    cellBorderSize (bordersize),
    cellSize (cellsize),
    maxGenerations (gens),
    generation (0),
    noState (-99),
    backgroundColor (bgcolor)
{ 
  setStatesAndColors(statesandcolors);
  setVisible(true);
  // determine a "noState" value by finding an integer that is not in
  // the state array
  while (states.contains(noState)) noState--;
  // fill the data array with noState
  for (int i=0; i<(rows*cols); i++)
    data.add(noState);
}
void CellView::resized()
{
}

CellView::~CellView()
{
  colors.clear();
  states.clear();
  data.clear();
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
  g.setColour(backgroundColor);
  g.fillAll();

  //data.lockArray();
  const ScopedLock lock (data.getLock());

  int  x, y, i=0, s=data.size();
  y=cellBorderSize;
  for (int r=0; r<cellRows; r++)
    {
      x=cellBorderSize;
      for (int c=0; c<cellColumns; c++)      
	{
	  if (i<s)
	    {
	      int q=data.getUnchecked(i);
	      if (q==noState)
		break;
	      else
		{
		  int j=states.indexOf(q);
		  if (j<0)
		    g.setColour(Colours::black);
		  else
		    g.setColour(colors.getUnchecked(j));
		}
	    }
	  else
	    break;
	  g.fillRect(x, y, cellSize, cellSize);
	  x += (cellSize+cellBorderSize);
	  i++;
	}
      y += (cellSize+cellBorderSize);
    }
  //data.unlockArray();
}

void CellView::setStatesAndColors(String statesandcolors)
{
  // parse state and color pairs and fill arrays
  states.clear();
  colors.clear();
  StringArray pairs;
  pairs.addTokens(statesandcolors, false);
  for (int i=0; i<pairs.size()-1; i+=2)
    {
      int state=pairs[i].getIntValue();
      Colour color=Colours::findColourForName( pairs[i+1], Colours::black);
      states.add(state);
      colors.add(color);
    }
  //std::cout << "CellView colormap: " << states.size() << "\n";
  //for (int i=0; i<states.size(); i++)
  //  std::cout <<  "  [" << i << "] " << states[i] << " -> " << colors[i].toString().toUTF8() << "\n";
}

StateWindow::StateWindow (String title, String statesandcolors, int rows, int cols, int cellsize, int bordersize, Colour bgcolor)
  : DocumentWindow (title, Colours::white, DocumentWindow::allButtons, true)

{
  listener.window=this;
  CellView* cv=new CellView(statesandcolors, rows, cols, cellsize, bordersize, bgcolor, 1);
  setResizable(true, true); 
  setContentComponent(cv);
  int width=(cellsize*cols) + (bordersize*(cols+1)) ;
  int height=(cellsize*rows) + (bordersize*(rows+1)) ;
  //std::cout << "width=" << width << " height=" << height << "\n";
  setContentComponentSize(width,height);
  setUsingNativeTitleBar(true);
  setDropShadowEnabled(true);
  centreWithSize(getWidth(), getHeight());
  //  setComponentProperty(T("WindowType"), WindowTypes::StateWindow);
  WindowTypes::setWindowType(this, WindowTypes::StateWindow);
  setVisible(true);
}

StateWindow::~StateWindow ()
{
}

void StateWindow::closeButtonPressed()
{
  delete this;
}

CellView* StateWindow::getCellView() 
{
  return (CellView*)getContentComponent();
}

StateWindow* StateWindow::findStateWindow(String title)
{
  for (int i=0; i<TopLevelWindow::getNumTopLevelWindows(); i++)
    {
      TopLevelWindow* w=TopLevelWindow::getTopLevelWindow(i);
      if (WindowTypes::isWindowType(w, WindowTypes::StateWindow) &&
	  w->getName()==title)
	return (StateWindow*)w;
    }
  return (StateWindow*)NULL;
}

StateWindow::StateWindowListener::StateWindowListener() 
  : window (0)
{
}

StateWindow::StateWindowListener::~StateWindowListener()
{
}

void StateWindow::openWindowFromXml(void* ptr)
{
  XmlElement* xml = (XmlElement *)ptr;  
  if (ptr==NULL) return;
  String title=xml->getStringAttribute(T("title"));
  String colormap=xml->getStringAttribute(T("colormap"));
  int rows=xml->getIntAttribute(T("rows"), 1);
  int columns=xml->getIntAttribute(T("columns"), 1);
  int cellsize=xml->getIntAttribute(T("cellsize"), 50);
  int cellbordersize=xml->getIntAttribute(T("cellbordersize"), 1);
  String bgcolor=xml->getStringAttribute(T("backgroundcolor"), T("white"));
  new StateWindow(title, colormap, rows, columns, cellsize, cellbordersize, Colours::findColourForName(bgcolor, Colours::white));
}

void StateWindow::StateWindowListener::handleMessage(const Message &m)
{
  CellView* cv=window->getCellView();
  if (!cv) return;
  switch (m.intParameter1)
    {

    case CommandIDs::StateWindowSetCell:
      {
	//std::cout << "StateWindowSetCell state=" << m.intParameter2 << " row=" << m.intParameter3 << " col=" << (int)m.pointerParameter << "\n";
        //	cv->data.lockArray();
	int val=m.intParameter2;
	int row=m.intParameter3;
#if defined JUCE_32BIT 	
        int col=(int)m.pointerParameter;
#elif defined JUCE_64BIT 
        int col=(long int)m.pointerParameter;
#else
#error "need JUCE_32BIT or JUCE_32BIT  macro"
#endif	
	int len=cv->data.size();
        row=row % cv->cellRows;
        col=col % cv->cellColumns;
        cv->data.setUnchecked((row*cv->cellColumns) + col, val);
        //        cv->data.unlockArray();
	cv->repaint();
	break;
      }

    case CommandIDs::StateWindowSetCells:
      {
	//std::cout << "StateWindowSetCells: length=" << m.intParameter2 << " row=" << m.intParameter3  << "\n";
	int  size=m.intParameter2;
	int* ints=(int *)m.pointerParameter;
        //	cv->data.lockArray();
	int len=cv->data.size();
        int row=m.intParameter3 % cv->cellRows;
        int ind=row*cv->cellColumns;
	for (int i=0; i<size; i++)
	  {
	    cv->data.setUnchecked((ind + i) % len, ints[i]);
	    //std::cout << "  data[" << (i % len) << "]: " << cv->data.getUnchecked(i % len) << "\n";
	  }
        //	cv->data.unlockArray();
	cv->repaint();
	delete [] ints;
	break;
      }

    default:
      break;
    }
}

