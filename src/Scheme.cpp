/*=======================================================================*
  Copyright (C) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#include "Enumerations.h"
#include "Scheme.h"
#include "Console.h"
#include "Midi.h"
#include "Csound.h"
#ifdef SNDLIB
#include "SndLib.h"
#endif
#ifdef WITHFOMUS
#include "Fomus.h"
#endif
#ifdef CHICKEN
#include "ChickenBridge.h"
#endif
#ifdef GRACE
#include "Preferences.h"
#endif
#include "Scanner.h"
#include "Syntax.h"
#include <iostream>
#include <string>

#define SCHEME_DEBUG 0

// 1 = trace scheme entry/exit points
// 2 = include gc info in trace
// 3 = include node creation/insertion/deletion info in tracce

juce_ImplementSingleton(Scheme)

//
//  Nodes
//


SchemeNode::SchemeNode(int _type, double _time)
  : type (0),
    start (0.0),
    elapsed (0.0),
    expr (String::empty),
    id (-1), 
    mmess (0xff)
{
  type = _type;
  time = _time;
}

SchemeNode::SchemeNode(int _type, double _time, String _expr)
  : time (0.0),
    start (0.0),
    elapsed (0.0),
    type (0),
    id (-1),
    mmess(0xff)
{
  // method for eval node
  type=_type; //  type = EVAL;
  expr=_expr;
  time = 0.0; // will always be ready to call
}

SchemeNode::SchemeNode(int _type, double _time, const MidiMessage &_mess)
  : time(0.0),
    elapsed (0.0),
    type(_type),
    mmess(_mess)
{
  // method for midi message callback from MidiIn port
}

SchemeNode::~SchemeNode()
{
}

bool SchemeNode::applyNode(double curtime) 
{
  bool more=false;

  switch (type)
    {

    case EVAL :
    case SAL :
      applyEvalNode();
      //      Console::getInstance()->printPrompt();
      break;

    case PROCESS:
      {
	double runtime, delta;
	if (schemeThread->isScoreMode())
	  {
	    // in score mode the scheduler runs in non-real time and
	    // node times are in seconds. the node's current time
	    // becomes the score time under the callback an is used to
	    // set the timestamps of data sent to ports
	    runtime=elapsed;
	    schemeThread->scoretime=time;
	  }
	else
	  {
	    runtime=(time-start)/1000.0;
	  }

	delta=applyProcessNode(runtime);
	//std::cout << "after callback, delta is " << delta << "\n";

	// a delta value less than 0 means that the process is done
	// running, where -1 is normal exit, -2 is error exit. in this
	// case applyProcesss has already gc'd the proc pointer and we
	// do not reschedule the node
	if (delta<0.0)
	  {
	    more=false;
	  }
	else
	  {
	    // update the time of the node to the next runttime. the
	    // values is in milliseconds if scheduler is running in
	    // real time
	    more=true;
	    if (schemeThread->isScoreMode())
	      {
		elapsed += delta;  // elapsed now user's next run time
		time += delta;
	      }
	    else
	      {
		elapsed += delta;  // elapsed now user's next run time
		// calculate delta to next runtime, the difference
		// between the last time stamp and the (future) one in
		// elapsed

		delta = elapsed-runtime;
		if (delta<0.0) delta=0.0;
		time=Time::getMillisecondCounterHiRes()+(delta*1000.0);
	      }
	  }
	schemeThread->scoretime=0.0;
      }
      break;

    case INHOOK:
      if (schemeThread->isMidiInputHook())
	applyMidiInputHookNode();
      break;

    case PAUSE :
      break;

    case STOP :
      schemeThread->stopProcesses(id);
      if ( SCHEME_DEBUG ) printf("...called stop node %d\n", nodeid);
      break;

    case QUIT :
      schemeThread->signalThreadShouldExit();
      if ( SCHEME_DEBUG ) printf("...called quit node %d\n", nodeid);
      break;

    default:
      break;
    }
  return more;
}

//
// Scheduler
//

Scheme::Scheme() 
  : Thread( "Scheme Thread"),
    pausing (false),
    scoremode (ScoreTypes::Empty),
    sprouted (false),
    showvoid (false),
    voidstring (String::empty),
    scoretime (0.0),
    nextid (0),
    quiet (false)
{
  evalBuffer = new char[8192];
  errorBuffer = new char[8192];  
#ifdef GRACE
  showvoid=Preferences::getInstance()->
    getBoolProp(T("SchemeShowVoidValues"), true);
#endif
  voidstring=T("<ok>\n");
}

Scheme::~Scheme()
{
  delete [] evalBuffer;
  delete [] errorBuffer;
  //  CHICKEN_delete_gc_root(inputClosureGCRoot);
  schemeNodes.clear();
}

void Scheme::setScoreMode(int mode)
{
  scoremode=mode;
}

bool Scheme::isScoreMode()
{
  // true if any score is in progress
  return (scoremode > ScoreTypes::Empty);
}

bool Scheme::isScoreMode(int mode)
{
  return (scoremode == mode);
}

double Scheme::getScoreTime()
{
  return scoretime;
}

/// void value printing

bool Scheme::showVoidValues()
{
  return showvoid;
}

void Scheme::setShowVoidValues(bool b)
{
  showvoid=b;
  //#ifdef GRACE
  //  Preferences::getInstance()->
  //    setBoolProp(T("SchemeShowVoidValues"), showvoid);
  //#endif
}

void Scheme::printVoidValue(String input)
{
  if (showVoidValues())
    Console::getInstance()->printValues(voidstring);
}

// loading

void Scheme::load(File file, bool addtorecent)
{
  //std::cout << "Scheme::load()\n";
  if (file==File::nonexistent)
    {
      FileChooser choose(T("Load"),
			 File::getCurrentWorkingDirectory());
      if (choose.browseForFileToOpen())
	{
	  file=choose.getResult();
	}
      else
	return;
    }
  String text=String::empty;
  if (file.existsAsFile())
    {
      //std::cout << "load file exists\n";
      if (file.hasFileExtension(T(".sal")))
	{
	  text << T("(sal \"")
	       << T("begin\n")
	       << file.loadFileAsString().replace(T("\""), T("\\\""))
	       << T("\nend")
	       << T("\")");
	}
      else
	{
	  text << T("(load ")
	       << file.getFullPathName().quoted()
	       << T(")");
	}
      //std::cout << "load text='" << text.toUTF8() << "'\n";
      eval(text);
      if (addtorecent)
	{
#ifdef GRACE
	  Preferences::getInstance()->recentlyLoaded.addFile(file);
#endif
	  //std::cout << "added to recently loaded\n";
	}
    }
  else
    {
      text << T(">>> Error: load file ")
	   << file.getFullPathName().quoted()
	   << T(" does not exist.");
      Console::getInstance()->printError(text);
    }
}

void Scheme::read()
{
  bool more=true;
  bool prompt=true;
  String text=String::empty;

  while (more && !threadShouldExit()) 
    {
      if (prompt)
	{
	  Console::getInstance()->printPrompt();
	  prompt=false;
	}
      std::string line="";
      getline(std::cin, line);
      if (!text.isEmpty())
	text << T("\n");
      text << String(line.c_str());
      int typ, loc;
      typ=scan_sexpr(LispSyntax::getInstance()->syntab,
		     text, 0, text.length(), SCAN_CODE, &loc, NULL);
      if (typ==SCAN_LIST || typ==SCAN_TOKEN || typ==SCAN_STRING)
	break;
      else if (typ==SCAN_UNLEVEL)
	break;  // allow too many parens to be passed to lisp?
    }
  if (!text.isEmpty())
    eval(text);
}

void Scheme::run()
{
  double qtime, utime;
  SchemeNode* node;

  if (!init())
      return;
  if (!isQuiet())
    {
      String banner=String::empty;
      banner << SystemStats::getJUCEVersion()
	     << T(" ") << SysInfo::getCopyright(T("Julian Storer")) << T("\n")
	     << getLispVersion() << T("\n")
	     << SysInfo::getCMLogo() << T("\n" );
      Console::getInstance()->printOutput(banner);
    }

  pausing=false;
  while (! threadShouldExit())
    {
      while ( true ) 
	{
	  schemeNodes.lockArray();
	  node=schemeNodes.getFirst();
	  schemeNodes.unlockArray();
	  if ( node == NULL )
	    {
	      break;
	    }
	  // if scoremode is true then qtime will be in seconds else
	  // milliseconds.
	  qtime=node->time;
	  utime = Time::getMillisecondCounterHiRes() ;
	  // this should probably test if the difference between qtime
	  // and utime is less that 1ms, if not then it probably
	  // shouldn't sleep (?)
	  if ( qtime > utime )
	    {
	      // if scoremode is true then qtime will be in seconds
	      // so this will not happen (which is what we want)
	      wait(1);
	    }
	  else
	    {
	      schemeNodes.lockArray();
	      schemeNodes.remove(0, false);
	      schemeNodes.unlockArray();
	      // NOTE: the node to process has now been popped from the
	      // queue.  i did this while trying to debug the random
	      // crashing. im not sure if this is the right thing to do or
	      // not since this means that flushing the queue, etc will have
	      // no effect on this node. Search for the word POP to see the
	      // places this affects...
	      lock.enter();
	      bool keep=node->applyNode(0.0);
	      lock.exit();
	      if ( keep )
		{
		  if ( SCHEME_DEBUG > 2)
		    printf("reinserting process node %d...\n",
			   node->nodeid);
		  schemeNodes.lockArray();
		  schemeNodes.addSorted(comparator,node);
		  //          schemeNodes.remove(0, false);
		  schemeNodes.unlockArray();
		  if ( SCHEME_DEBUG > 2)
		    printf("...done reinserting process node %d\n",
			   node->nodeid);
		}
	      else
		{
		  int myid=node->nodeid;
		  int mytyp=node->type;
		  delete node;
		  if ( SCHEME_DEBUG > 2)
		    {
		      if (mytyp==SchemeNode::PROCESS)
			printf("deleted process node %d\n", myid);
		      else
			printf("deleted eval node %d\n", myid);
		      schemeNodes.lockArray();
		      int mysize=schemeNodes.size();
		      printf ("Queue size: %d\n", mysize);
		      if (mysize>0)
			{
			  printf ("Remaining nodes: ");
			  for (int i=0;i<mysize;i++)
			    printf(" %d",schemeNodes[i]->nodeid);
			  printf("\n");
			}
		      schemeNodes.unlockArray();
		    }
		  //	  schemeNodes.lockArray();
		  //          schemeNodes.remove(0, true);
		  //mysize=schemeNodes.size();
		  //schemeNodes.unlockArray();
		  //printf("...removed %d, queue now %d\n", myid, mysize);
		}
	    }
	  node=NULL;
	}
      // queue is now empty. 
      /*if ( SCHEME_DEBUG>0 ) printf("scheduling queue is empty\n");*/

      if (sprouted && isScoreMode())
	{
	  // we just finished running a sprouted process in score
	  // mode, send a "score complete" message to the console for
	  // processing the file output
	  if (isScoreMode(ScoreTypes::Midi))
	    MidiOutPort::getInstance()->
	      performCommand(CommandIDs::SchedulerScoreComplete);
#ifdef SNDLIB
	  else if (isScoreMode(ScoreTypes::SndLib))
	    SndLib::getInstance()->
	      performCommand(CommandIDs::SchedulerScoreComplete);
#endif	  
#ifdef WITHFOMUS
	  else if (isScoreMode(ScoreTypes::Fomus))
	    Fomus::getInstance()->closeScore();
#endif	  
	  else if (isScoreMode(ScoreTypes::Csound))
	    Csound::getInstance()->saveScore();
	}
      sprouted=false;
      scoretime=0.0;
      setScoreMode(ScoreTypes::Empty);
#ifdef GRACE
      wait(-1);
#else
      read();
#endif
    }
  // leaving killed process....
}

void Scheme::clear()
{
  // this should NEVER be called from scheme code (an EVAL node) or
  // else the run() loop will bomb since it assumes index[0] exists
  schemeNodes.lockArray();
  schemeNodes.clear();
  schemeNodes.unlockArray();
}

void Scheme::printQueue(bool verbose)
{
  schemeNodes.lockArray();
  std::cout << "Queue["<< schemeNodes.size() << "]=";
  for (int i=0; i<schemeNodes.size(); i++)
    {
      String z;
      for (int i=0; i<schemeNodes.size(); i++)
	{
	  std::cout << z.toUTF8() << schemeNodes.getUnchecked(i)->nodeid;
	  if (verbose)
	    std::cout << "[time=" << schemeNodes.getUnchecked(i)->time
		      << ", type="<< schemeNodes.getUnchecked(i)->type
		      << "]";
	  z=T(", ");
	}
      std::cout << "\n";  
    }
  schemeNodes.unlockArray();
}

// addNode for processes

void Scheme::sprout(double _time, SCHEMEPROC c, int _id)
{
  // this method adds a musical process and is only called by scheme
  // code via sprout() under an eval node.  this means that a
  // lock.enter() is in effect so we dont need to lock anything to
  // reference scoremode.
  //  static int nextid=1000;
  if (!isScoreMode())
    _time = (_time * 1000) + Time::getMillisecondCounterHiRes();
  else
    _time += scoretime; // shift process to current scoretime under callback

  SchemeNode *n = new SchemeNode(SchemeNode::PROCESS, _time, c, _id);
  n->nodeid=++nextid;
  n->schemeThread = this;
  sprouted=true;  // tell scheduler that we have a process running
  schemeNodes.lockArray();
  schemeNodes.addSorted(comparator, n);
  schemeNodes.unlockArray();
  notify();
  if (SCHEME_DEBUG>2) printf("added process node %d\n", n->nodeid);
}

void Scheme::eval(char* str)
{
  eval(String(str));
}

void Scheme::eval(String s)
{
  //  static int nextid=000;
  SchemeNode *n = new SchemeNode(SchemeNode::EVAL, 0.0, s);
  n->nodeid=++nextid;
  n->schemeThread = this;
  schemeNodes.lockArray();
  schemeNodes.addSorted(comparator, n);
  schemeNodes.unlockArray();
  notify();
  if (SCHEME_DEBUG>2) printf("added eval node %d\n", n->nodeid);
}

void Scheme::quit()
{
  //  static int nextid=000;
  SchemeNode *n = new SchemeNode(SchemeNode::QUIT, 0.0);
  n->nodeid=++nextid;
  n->schemeThread = this;
  schemeNodes.lockArray();
  schemeNodes.addSorted(comparator, n);
  schemeNodes.unlockArray();
  notify();
  if (SCHEME_DEBUG>2) printf("added quit node %d\n", n->nodeid);
}

void Scheme::midiin(const MidiMessage &msg)
{
  if (!isMidiInputHook())
      return;
  //  static int nextid=2000;
  SchemeNode *n = new SchemeNode(SchemeNode::INHOOK, 0.0, msg);
  n->nodeid=++nextid;
  n->schemeThread = this;
  schemeNodes.lockArray();
  schemeNodes.addSorted(comparator, n);
  schemeNodes.unlockArray();
  notify();
  if (SCHEME_DEBUG>2) printf("added input hook node %d\n", n->nodeid);
}

void Scheme::setPaused(bool p) {
  if (p) {
    // pause the scheduler.
    // this cannot really pause the Thread or else evalling wont work.
    // so we effect a pause by hand inserting a PAUSE node at the
    // head of the queue with a 1hr future time stamp, which then
    // keeps any of nodes further down the line from being processed
    // by the scheduler
    if (pausing) return;
    double delta=Time::getMillisecondCounterHiRes();
    // calc time 1 hr in the future
    SchemeNode *n = new SchemeNode(SchemeNode::PAUSE,
				   delta + (1000.0 * 60.0 * 60));
    // cache start time of pause in node
    n->start=delta;
    schemeNodes.lockArray();
    // NOTE: POP removed the node that got us here so
    // we add pause node at index 0.
    // otherwise the eval node that got us here is at queu index 0 so add pause
    // at index 1 so that it becomes the head of the queue after the
    // eval node is popped
    schemeNodes.insert(0,n); // POP
    schemeNodes.unlockArray();
    pausing=true;
    notify();
  }
  else {
    // continue from a pause.
    // to stop the pause we add the pause delta (time-start) to every
    // node above the pause and then remove the pause node.
    if (! pausing) return;
    int i;
    schemeNodes.lockArray();
    // search for the pause node...
    for (i=0; i<schemeNodes.size(); i++) {
      //printf("node[%d].type=%d\n", i, schemeNodes[i]->type);
      if ( schemeNodes[i]->type == SchemeNode::PAUSE )
	break;
    }
    if (i == schemeNodes.size() ) {
      printf("FAILED TO FIND PAUSE NODE!\n");
      schemeNodes.unlockArray();
      return;
    }
    // now increment all nodes above the pause node by pause amount
    double delta=Time::getMillisecondCounterHiRes() - schemeNodes[i]->start;
    //printf("pause node at=%d, pause dur=%d\n", i, (int)delta);
    for (int j=i+1; j< schemeNodes.size(); j++) {
      schemeNodes[j]->start += delta;
      schemeNodes[j]->time += delta;
    }
    schemeNodes.remove(i, true);
    schemeNodes.unlockArray();
    pausing=false;
  }
}

void Scheme::stop(int id)
{
  // always add stop nodes to the front of the queue.
  SchemeNode *node = new SchemeNode (SchemeNode::STOP, 0.0);
  node->nodeid=++nextid;
  node->id=id;
  if ( SCHEME_DEBUG > 2)
    printf("adding stop node %d...\n", node->nodeid);
  node->schemeThread = this;
  schemeNodes.lockArray();
  schemeNodes.insert(0,node);
  schemeNodes.unlockArray();
  notify();
  if ( SCHEME_DEBUG > 2)
    printf("...done adding stop node %d\n", node->nodeid);
}

void Scheme::stopProcesses(int id) {
  // this is called by a STOP node from process().  stop all processes
  // with id from running. if id=-1 then stop all processes. iterate
  // queue in reverse order so removal index remains valid.  NOTE: POP
  // removed the (STOP) node that got us here so this deletes up to
  // and including index 0. otherwise dont include index 0
  schemeNodes.lockArray();
  if ( id<0 ) {
    for (int i=schemeNodes.size()-1; i>=0; i--)
      if (schemeNodes[i]->type == SchemeNode::PROCESS)
	schemeNodes.remove(i,true);
  }
  else {
    // else selectively remove all nodes with id process queue in
    // reverse order so removal index always valid
    for (int i=schemeNodes.size()-1; i>=0; i--)
      if ( (schemeNodes[i]->type == SchemeNode::PROCESS) &&
	   (schemeNodes[i]->id == id) )
	schemeNodes.remove(i,true);
  }
  schemeNodes.unlockArray();
  // if stopped all processes also clear any pending messages and send
  // all notes off
  if (id<0)
    MidiOutPort::getInstance()->clear();
}

bool Scheme::isQueueEmpty()
{
  schemeNodes.lockArray();
  int size=schemeNodes.size();
  schemeNodes.unlockArray();
  return (size == 0);
}

void Scheme::performSchedulerCommand(CommandID id)
{
  /*  GracePreferences* prefs=GracePreferences::getInstance();
  switch (id)
    {
    case CommandIDs::SchedulerScoreMode :
      lock.enter();
      scoremode=(!scoremode);
      lock.exit();
      prefs->setScoreCaptureMode(scoremode);
      break;
    default:
      break;
    }
  */
}

//
// Printing support
//

/*
void Scheme::printError(char* str)
{
  // call this to print error messages
  int len=strlen(str);
  if (len>0)
    {
      std::cout << str;
      if (str[len-1] != '\n')
	std::cout << std::endl;
    }
}

void Scheme::printValues(char* str)
{
  // call this to print REPL values
  int len=strlen(str);
  if (len>0)
    {
      std::cout << str;
      if (str[len-1] != '\n')
	std::cout << std::endl;
    }
}

void Scheme::printOutput(char* str)
{
  // call this to print format() and display() output
  int len=strlen(str);
  if (len>0)
    {
      std::cout << str;
      if (str[len-1] != '\n')
	std::cout << std::endl; 
    }
}

void Scheme::printPrompt()
{
  // call this to print optional prompt
  //  if (prompt != String::empty)
  //    std::cout << prompt.toUTF8() << std::flush;
  Console::getInstance()->printPrompt(prompt);
}

void Scheme::setPrompt(String str)
{
  prompt=str;
}


*/
