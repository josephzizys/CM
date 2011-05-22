/*=======================================================================*
  Copyright (C) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#ifndef Main_h
#define Main_h

#include "Libraries.h"

class Grace : public JUCEApplication
{
  LookAndFeel* lookandfeel;
public:
  
  Grace() {}
  ~Grace() {}
  void initialise (const juce::String& commandLine);
  void shutdown();

  /** flush any musical processes currently running, interrupt any lisp
      eval taking place and silence any audio/midi output **/

  void reset();
  void systemRequestedQuit();
  void anotherInstanceStarted(const String& commandLine);
  const String getApplicationName();
  const String getApplicationVersion();
  bool moreThanOneInstanceAllowed();
  void showWorkingDirectory();
  void chooseWorkingDirectory();

  // these are implemented in Command.cpp
  ApplicationCommandTarget* getNextCommandTarget();
  void getAllCommands(Array<CommandID>& commands);
  void getCommandInfo(CommandID id, ApplicationCommandInfo& info);
  bool perform(const ApplicationCommandTarget::InvocationInfo& info);
  void openFile(File file=File::nonexistent);
  int getNumUnsavedWindows();
  bool queryUnsavedWindows();
};

class CommandArg
{
 public:
  String name;
  String expr;

  CommandArg(String nam, String str)
    {
      name=nam;
      expr=str;
    }
  CommandArg(){}
};

class CommandArgs : public OwnedArray<CommandArg>
{
 public:
  StringArray cmds, help, args;
  CommandArgs() {}
  ~CommandArgs () {}

  void addCommand(String _name, String _help, String _args=String::empty)
  {
    cmds.add(_name);
    help.add(_help);
    args.add(_args);
  }
  int getCommand(String str)
  {
    for (int i=0; i<cmds.size(); i++)
      if (cmds[i]==str)
	return i;
    return -1;
  }
  CommandArg* getCommandArg(String str)
  {
    for (int i=0; i<size(); i++)
      if (getUnchecked(i)->name==str)
	return getUnchecked(i);
    return NULL;
  }
  String init(StringArray& input)
  {
    int i=0;
    while (i<input.size())
      {
	String c=input[i];
	String s=String::empty;
	int j=getCommand(c);
	if (j>=0)
	  {
	    if (!args[j].isEmpty()) // command requires arg
	      {
		if (i+1<input.size())
		  s=input[i+1];
		else
		  return c + ": missing " + args[j];
		if (s.startsWith(T("-")))
		  return c + ": missing " + args[j];
		i+=1;
	      }
	    i+=1;
	    add(new CommandArg(c,s));	    
	  }
	else
	  return c + T(" is not a valid command.");	  
      }
    return String::empty;
  }
  
  String getHelp()
  {
    String str=String::empty;
    for (int i=0; i<cmds.size(); i++)
      {
	str << T("  ") << cmds[i] ;
	if (!args[i].isEmpty()) str << T(" ") << args[i] ;
	str << T("\t") << help[i] << T("\n");
      }
    return str;
  }
};

#endif
