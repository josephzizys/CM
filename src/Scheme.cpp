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
#ifdef GRACE
#include "Preferences.h"
#endif
#include "Scanner.h"
#include "Syntax.h"
#include <iostream>
#include <string>

juce_ImplementSingleton(SchemeThread)

//
// Execution Nodes for Scheme Thread's queue
//

XSchemeNode::XSchemeNode(double qtime)
  : time (qtime),
    userid (-1)
{
  static CriticalSection protect;
  const ScopedLock lock (protect);
  static int nodecounter=0;
  nodeid=++nodecounter;
}

// XControlNode

XControlNode::XControlNode(double qtime, int control, int ident)
: XSchemeNode(qtime),
  type (control)
{
  userid=ident;
}

XControlNode::~XControlNode()
{
}

bool XControlNode::applyNode(SchemeThread* schemethread, double curtime)
{
  switch (type)
    {
    case QueueStop:
      schemethread->stopProcesses(userid);
      break;
    case QueueQuit:
      schemethread->signalThreadShouldExit();
      break;
    default:
      break;
    }
  return false;
}

// XEvalNode

XEvalNode::XEvalNode(double qtime, String sexpr)
  : XSchemeNode(qtime),
    expr (sexpr)
{
}

XEvalNode::~XEvalNode()
{
}

bool XEvalNode::applyNode(SchemeThread* schemethread, double curtime) 
{
  s7_scheme* sc=schemethread->scheme;
  s7_pointer val=s7_eval_c_string(sc, (char *)expr.toUTF8());
  if (val != schemethread->schemeError)
    {
      String str=String(s7_object_to_c_string(sc, val));
#ifdef GRACE
      str << T("\n");
#endif
      Console::getInstance()->printValues(str);
    }
  return false; 
}

// XProcessNode

XProcessNode::XProcessNode(double qtime, s7_pointer proc, int qid)
  : XSchemeNode(qtime),
    elapsed (0.0)
{
  userid = qid;
  time = qtime;
  start = qtime;
  schemeproc=proc;
}

XProcessNode::~XProcessNode()
{
}

/**
bool XProcessNode::applyNode(SchemeThread* schemethread, double curtime)
{
  bool more=false;
  double runtime, delta;
  if (schemethread->isScoreMode())
    {
      // in score mode the scheduler runs in non-real time and
      // node times are in seconds. the node's current time
      // becomes the score time under the callback an is used to
      // set the timestamps of data sent to ports
      runtime=elapsed;
      schemethread->scoretime=time;
    }
  else
    {
      runtime=(time-start)/1000.0;
    }
  
  delta=applyProcessNode(schemethread, runtime);
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
      if (schemethread->isScoreMode())
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
  schemethread->scoretime=0.0;
  return more;
}
**/

bool XProcessNode::applyNode(SchemeThread* schemethread, double curtime)
{
  s7_scheme* sc=schemethread->scheme;
  bool more=false;
  double runtime, delta;
  if (schemethread->isScoreMode())
    {
      // in score mode the scheduler runs in non-real time and
      // node times are in seconds. the node's current time
      // becomes the score time under the callback an is used to
      // set the timestamps of data sent to ports
      runtime=elapsed;
      schemethread->scoretime=time;
    }
  else
    {
      runtime=(time-start)/1000.0;
    }
  
  //delta=applyProcessNode(runtime);
  s7_pointer args = s7_cons(sc,
                            s7_make_real(sc, runtime),
                            s7_NIL(sc));
  int prot = s7_gc_protect(sc, args);
  delta=s7_number_to_real(s7_call(sc, 
                                  schemeproc, 
                                  args
                                  )
                          );
  s7_gc_unprotect_at(sc, prot);
  //std::cout << "after callback, delta is " << delta << "\n";

  // a delta value less than 0 means that the process is done running,
  // where -1 is normal exit, -2 is error exit. in this case gc the
  // proc pointer and do not reschedule the node
  if (delta<0.0)
    {
      s7_gc_unprotect(sc,schemeproc);
      more=false;
    }
  else
    {
      // update the time of the node to the next runttime. the
      // values is in milliseconds if scheduler is running in
      // real time
      more=true;
      if (schemethread->isScoreMode())
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
  schemethread->scoretime=0.0;
  return more;
}

// XMidiNode

XMidiNode::XMidiNode(double qtime, const MidiMessage &mess)
  : XSchemeNode(qtime),
    mmess (mess)
{
}

XMidiNode::~XMidiNode()
{
}

bool XMidiNode::applyNode(SchemeThread* schemethread, double curtime)
{
  if (schemethread->isMidiInputHook())
    {
      // called on Midi message nodes if an input hook is set
      //std::cout << "applyMidiInputHookNode()\n";
      s7_scheme* sc=schemethread->scheme;
      int op=(mmess.getRawData()[0] & 0xf0)>>4;
      int ch=mmess.getChannel()-1;
      int d1=mmess.getRawData()[1] & 0x7f;
      int d2=0;
      if (mmess.getRawDataSize()>2)
        d2=mmess.getRawData()[2] & 0x7f;
      // convert MidiOns with zero velocity to MidiOff
      if ((op==MidiFlags::On) && (d2==0))
        op=MidiFlags::Off;
      s7_pointer args=s7_cons(sc,
                              s7_make_integer(sc, op),
                              s7_cons(sc,					  
                                      s7_make_integer(sc, ch),
                                      s7_cons(sc,
                                              s7_make_integer(sc, d1),
                                              s7_cons(sc,
                                                      s7_make_integer(sc, d2),
                                                      s7_NIL(sc)))));
      int prot = s7_gc_protect(sc, args);
      int res=(int)s7_integer(s7_call(sc, schemethread->midiinhook, args));
      s7_gc_unprotect_at(sc, prot);
      if (res!=0)
        {
          schemethread->clearMidiInputHook();
          Console::getInstance()->printError(T(" Clearing Midi input hook.\n"));
        }
    }
  return false;
}

// XOscNode

XOscNode::XOscNode(double qtime, String oscpath, String osctypes)
  : XSchemeNode(qtime),
    path (oscpath),
    types (osctypes)
{
}

XOscNode::~XOscNode()
{
  flos.clear();
}

bool XOscNode::applyNode(SchemeThread* st, double curtime)
{
  //std::cout << "Osc message: "<< path.toUTF8() << " " << types.toUTF8();
  ////st->lockOscHook();
  if (st->oscHook != NULL)
    {
      //std::cout << "Osc hook!\n";
      s7_scheme* sc=st->scheme;
      // the osc message data starts with the string path
      s7_pointer data = s7_cons(sc, s7_make_string(sc, path.toUTF8()), s7_nil(sc));
      s7_pointer tail = data;
      // iterate types adding floats and ints to message data
      int F=0;
      int I=0;
      for (int i=0; i<types.length(); i++)
        {
          switch (types[i])
            {
            case 'i':  // LO_INT32
            case 'h':  // LO_INT64
              //std::cout << "int="<< ints[I] << "\n";
              s7_set_cdr(tail, s7_cons(sc, s7_make_integer(sc, ints[I++]), s7_nil(sc)));
              break;
            case 'f':  // LO_FLOAT32
            case 'd':  // LO_FLOAT64
              //std::cout << "flo="<< flos[F] << "\n";
              s7_set_cdr(tail, s7_cons(sc, s7_make_real(sc, flos[F++]), s7_nil(sc)));
              break;
            }
          tail=s7_cdr(tail);
        }
      // create the function args
      s7_pointer args=s7_cons(sc, data, s7_nil(sc));
      int prot = s7_gc_protect(sc, args);
      s7_pointer res=s7_call(sc, st->oscHook, args);
      s7_gc_unprotect_at(sc, prot);
      if (res == st->schemeError)
        {
          st->clearOscHook();
          Console::getInstance()->printError(">>> Cancelled OSC hook.\n");
        }
    }
  ////st->unlockOscHook();
  return false;
}

void SchemeThread::setOscHook(s7_pointer hook)
{
  oscLock.enter();
  oscHook=hook;
  s7_gc_protect(scheme, oscHook);
  oscLock.exit();
}

void SchemeThread::clearOscHook()
{
  oscLock.enter();
  s7_gc_unprotect(scheme, oscHook);
  oscHook=NULL;
  oscLock.exit();
}

bool SchemeThread::isOscHook()
{
  oscLock.enter();
  bool hook = (oscHook != NULL);
  oscLock.exit();
  return hook;
}

void SchemeThread::lockOscHook()
{
  oscLock.enter();
}

void SchemeThread::unlockOscHook()
{
  oscLock.exit();
}

//
// Scheduler
//

SchemeThread::SchemeThread() 
  : Thread( "Scheme Thread"),
    pausing (false),
    scoremode (ScoreTypes::Empty),
    sprouted (false),
    showvoid (false),
    voidstring (String::empty),
    scoretime (0.0),
    nextid (0),
    quiet (false),
    midiinhook (NULL),
    oscHook (NULL),
    schemeFalse (NULL),
    schemeTrue (NULL),
    schemeNil (NULL),
    schemeError (NULL),
    schemeVoid (NULL),
    scheme (NULL)
{
#ifdef GRACE
  showvoid=Preferences::getInstance()->
    getBoolProp(T("SchemeShowVoidValues"), true);
#endif
  voidstring=T("<ok>\n");
}

SchemeThread::~SchemeThread()
{
  schemeNodes.clear();
}

void SchemeThread::signalSchemeError(String text)
{
  // use this function to signal errors in C code called by Scheme
  s7_error(scheme,
           schemeError, //s7_make_symbol(scheme, "scheme-error"), 
           s7_make_string(scheme, text.toUTF8())
           );
}


void SchemeThread::setScoreMode(int mode)
{
  scoremode=mode;
}

bool SchemeThread::isScoreMode()
{
  // true if any score is in progress
  return (scoremode > ScoreTypes::Empty);
}

bool SchemeThread::isScoreMode(int mode)
{
  return (scoremode == mode);
}

double SchemeThread::getScoreTime()
{
  return scoretime;
}

/// void value printing

bool SchemeThread::showVoidValues()
{
  return showvoid;
}

void SchemeThread::setShowVoidValues(bool b)
{
  showvoid=b;
}

void SchemeThread::printVoidValue(String input)
{
  if (showVoidValues())
    Console::getInstance()->printValues(voidstring);
}

// loading

void SchemeThread::load(File file, bool addtorecent)
{
  //std::cout << "SchemeThread::load()\n";
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
      String path=file.getFullPathName().quoted();
      if (SysInfo::isWindows())
	path=path.replace(T("\\"),T("\\\\"));
      if (file.hasFileExtension(T(".sal")))
	{
	  text << T("(sal:load ") << path << T(")");
	}
      else
	{
	  text << T("(load ") << path << T(")");
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

void SchemeThread::read()
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

void SchemeThread::run()
{
  double qtime, utime;
  XSchemeNode* node;

  if (!init())
      return;
  if (!isQuiet())
    {
      String banner=String::empty;
      banner << SystemStats::getJUCEVersion()
	     << T(" ") << SysInfo::getCopyright(T("Julian Storer")) << T("\n")
	     << getLispVersion() << T("\n");
#ifdef WITHFOMUS
      if (fomus_exists) banner << Fomus::getFomusVersion() << T("\n");
#endif
      banner << SysInfo::getCMLogo() << T("\n" );
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
	      bool keep=node->applyNode(this, 0.0);
	      lock.exit();
	      if ( keep )
		{
		  schemeNodes.lockArray();
		  schemeNodes.addSorted(comparator,node);
		  //          schemeNodes.remove(0, false);
		  schemeNodes.unlockArray();
		}
	      else
		{
		  delete node;
		}
	    }
	  node=NULL;
	}
      // queue is now empty. 
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

void SchemeThread::clear()
{
  // this should NEVER be called from scheme code (an EVAL node) or
  // else the run() loop will bomb since it assumes index[0] exists
  schemeNodes.lockArray();
  schemeNodes.clear();
  schemeNodes.unlockArray();
}

void SchemeThread::addNode(XSchemeNode* node)
{
  schemeNodes.lockArray();
  schemeNodes.addSorted(comparator, node);
  schemeNodes.unlockArray();
  notify();
}

// addNode for processes

void SchemeThread::sprout(double _time, SCHEMEPROC proc, int _id)
{
  // this method is only called by scheme code via sprout() under an
  // eval node.  this means that a lock.enter() is in effect so we
  // dont need to lock anything to reference scoremode.
  if (!isScoreMode())
    _time = (_time * 1000) + Time::getMillisecondCounterHiRes();
  else
    _time += scoretime; // shift process to current scoretime under callback

  s7_gc_protect(scheme, proc); // don't let gc touch it
  sprouted=true;  // tell scheduler that we have a process running
  schemeNodes.lockArray();
  schemeNodes.addSorted(comparator, new XProcessNode( _time, proc, _id));
  schemeNodes.unlockArray();
  notify();
}

void SchemeThread::eval(char* str)
{
  eval(String(str));
}

void SchemeThread::eval(String s)
{
  schemeNodes.lockArray();
  schemeNodes.addSorted(comparator, new XEvalNode(0.0, s));
  schemeNodes.unlockArray();
  notify();
}

void SchemeThread::quit()
{
  schemeNodes.lockArray();
  schemeNodes.addSorted(comparator, new XControlNode(0.0, XControlNode::QueueQuit));
  schemeNodes.unlockArray();
  notify();
}

void SchemeThread::midiin(const MidiMessage &msg)
{
  if (!isMidiInputHook())
      return;
  schemeNodes.lockArray();
  schemeNodes.addSorted(comparator, new XMidiNode(0.0, msg));
  schemeNodes.unlockArray();
  notify();
}

void SchemeThread::setPaused(bool p) {}

void SchemeThread::stop(int ident)
{
  // always add stop nodes to the front of the queue.
  schemeNodes.lockArray();
  schemeNodes.insert(0, new XControlNode (0.0, XControlNode::QueueStop, ident));
  schemeNodes.unlockArray();
  notify();
}

void SchemeThread::stopProcesses(int ident)
{
  // this is called by a STOP node from process().  stop all processes
  // with id from running. if id=-1 then stop all processes. iterate
  // queue in reverse order so removal index remains valid.  NOTE: POP
  // removed the (STOP) node that got us here so this deletes up to
  // and including index 0. otherwise dont include index 0
  schemeNodes.lockArray();
  if (ident<0)
    {
      for (int i=schemeNodes.size()-1; i>=0; i--)
        if (dynamic_cast<XProcessNode*>(schemeNodes[i]) != NULL)
          schemeNodes.remove(i,true);
    }
  else 
    {
      // else selectively remove all nodes with id process queue in
      // reverse order so removal index always valid
      for (int i=schemeNodes.size()-1; i>=0; i--)
        if (XProcessNode* n = dynamic_cast<XProcessNode*>(schemeNodes[i]))
          if (n->userid == ident) 
            schemeNodes.remove(i, true);
    }
  schemeNodes.unlockArray();
  // if stopped all processes also clear any pending messages and send
  // all notes off
  // GET RID OF THIS!
  if (ident<0)
    MidiOutPort::getInstance()->clear();
}

bool SchemeThread::isQueueEmpty()
{
  schemeNodes.lockArray();
  int size=schemeNodes.size();
  schemeNodes.unlockArray();
  return (size == 0);
}

