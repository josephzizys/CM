#include "Fomus.h"
#include "Enumerations.h"
#include <iostream>

FomusPort::FomusPort (ConsoleWindow* win)
{
  console=win;
}

FomusPort::~FomusPort ()
{
}

const PopupMenu FomusPort::getFomusMenu()
{
  PopupMenu fomusmenu, submenu;
  fomusmenu.addItem(CommandIDs::toID(CommandIDs::Fomus, 1, 0),
		    T("Foo"));
  fomusmenu.addItem(CommandIDs::toID(CommandIDs::Fomus, 2, 0), 
		    T("Bar"));
  submenu.addItem(CommandIDs::toID(CommandIDs::Fomus, 3, 0), 
		  T("Buz"));
  submenu.addItem(CommandIDs::toID(CommandIDs::Fomus, 4, 0), 
		  T("Bif"));
  fomusmenu.addSubMenu(T("Baz"), submenu);
  fomusmenu.addSeparator();
  fomusmenu.addItem(CommandIDs::toID(CommandIDs::Fomus, 5, 0),
		    T("Quux")
		    );
  return fomusmenu;
}

void FomusPort::performFomusCommand(CommandID id)
{
  int typ=CommandIDs::getCommandType(id);
  int num=CommandIDs::getCommandNumber(id);
  int arg=CommandIDs::getCommandData(id);  
  String str=String::empty;
  str << T("Fomus command: type=") << String(typ )
      << T(" number=")  << String(num)
      << T(" data=") << String(arg) << T("\n");
  console->printMessage(str);
}



