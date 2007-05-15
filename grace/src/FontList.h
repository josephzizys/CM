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
/*
This is a Singleton class which holds a list of font names available 
on the system. This would be created once, at app launch time, and could
then be used in subsequent calls to a font menu or some other kind 
of component that lists available fonts. 
*/

#ifndef __FONTLIST__
#define __FONTLIST__

#include "juce.h"


class FontList  : public DeletedAtShutdown
{
 public:
  static FontList* getInstance();
  StringArray fontNames;
  
 protected:
  FontList();
  FontList(const FontList&);
  FontList& operator= (const FontList&);
  ~FontList();
  
 private:
  static FontList* pinstance;
};






#endif

