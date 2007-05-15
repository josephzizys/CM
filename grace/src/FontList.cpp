/**********************************************************************
* Copyright (C) 2006 Todd Ingalls (testcase@asu.edu) 
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
**********************************************************************

$Name$
$Revision$
$Date$
**********************************************************************/

#include "FontList.h"



FontList* FontList::pinstance = 0;

FontList* FontList::getInstance() 
{
  if (pinstance == 0) 
    { 
      pinstance = new FontList; 
    }
  return pinstance; 
}

FontList::FontList() 
{
  OwnedArray<Font> fonts;
  //Font::findFonts (fonts);
  
  for (int i = 0; i < fonts.size(); ++i) {
    fontNames.add (fonts[i]->getTypefaceName());
  }
}

FontList::~FontList()	
{
  fontNames.clear();
}
