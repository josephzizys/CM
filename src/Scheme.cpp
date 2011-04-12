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
#include "CmSupport.h"
#ifdef SNDLIB
#include "SndLib.h"
#endif
#ifdef WITHFOMUS
#include "Fomus.h"
#endif
#ifdef GRACE
#include "Preferences.h"
#endif
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
  Console* console=Console::getInstance();
  s7_scheme* sc=schemethread->scheme;
  //  console->setEvaling(true);
  ////  console->postAsyncMessage(CommandIDs::ConsoleIsEvaling, 1, true);

  // install the begin_hook that allows s7 to quit current eval
  schemethread->setSchemeInterrupt(false);
  s7_set_begin_hook(sc, cm_begin_hook);
  s7_pointer val=s7_eval_c_string(sc, (char *)expr.toUTF8());
  s7_set_begin_hook(sc,NULL);
  if (schemethread->isSchemeInterrupt()) 
  {
    console->printWarning(T("Scheme interrupted!\n"));
  }
  else if (val != schemethread->schemeError)
  {
    String str=String(s7_object_to_c_string(sc, val));
#ifdef GRACE
    str << T("\n");
#endif
    console->printValues(str);
  }
  //  console->setEvaling(false);
  ////  console->postAsyncMessage(CommandIDs::ConsoleIsEvaling, 0, true);
  return false; 
}

XSalNode::XSalNode(double qtime, String input, int id, bool xpand, bool mult )
  : XSchemeNode(qtime),
    expand (xpand),
    multi (mult),
    vers(id),
    expr (input)
{
}

XSalNode::~XSalNode()
{
  toks.clear();
}

bool XSalNode::applyNode(SchemeThread* st, double curtime) 
{
  s7_scheme* sc=st->scheme;
  s7_pointer data=st->schemeNil;
  Console* console=Console::getInstance();
  // cons up token list using reverse order of array
  for (int i=toks.size()-1; i>=0; i--)
    {
     data=s7_cons(sc, s7_make_c_pointer(sc, toks.getUnchecked(i)), data);
    }
  // turn data into arglist ("input" ({tok}*) [#t|#f]*)
  data=s7_cons(sc, 
               s7_make_string(sc, expr.toUTF8()),
               s7_cons(sc, 
                       data,
                       s7_cons(sc, 
                               s7_make_boolean(sc, expand),
                               s7_cons(sc, 
                                       s7_make_boolean(sc, multi),
                                       st->schemeNil)))
               );
  // gc protect data cobbled up on the C side
  int prot = s7_gc_protect(sc, data);
  s7_pointer retn;
  st->isSalEval(true);
  ////  console->postAsyncMessage(CommandIDs::ConsoleIsEvaling, 1, true);
  st->setSchemeInterrupt(false);
  s7_set_begin_hook(sc, cm_begin_hook);
  if (vers==TextIDs::Sal)
    {
      // sal only side effects so we never process return values
      retn=s7_call(sc, s7_name_to_value(sc, "sal"), data);
    }
  else
    {
      retn=s7_call(sc, s7_name_to_value(sc, "sal2"), data);
      if (retn != st->schemeError)
        {
          //cm_print(retn);
          String str=String(s7_object_to_c_string(sc, retn));
          str << T("\n");
          for (int i=0; i<str.length(); i++)
            if (str[i]==T('(')) str[i]=T('{');
            else if (str[i]==T(')')) str[i]=T('}');
          console->printValues(str);
        }
    }
  s7_gc_unprotect_at(sc, prot);
  s7_set_begin_hook(sc, NULL);
  if (st->isSchemeInterrupt()) 
  {
    console->printWarning(T("Scheme interrupted!\n"));
  }
  st->isSalEval(false);
  ///  console->postAsyncMessage(CommandIDs::ConsoleIsEvaling, 0, true);
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

bool XProcessNode::applyNode(SchemeThread* st, double curtime)
{
  s7_scheme* sc=st->scheme;
  bool more=false;
  double runtime, delta;
  if (st->isScoreMode())
    {
      // in score mode the scheduler runs in non-real time and
      // node times are in seconds. the node's current time
      // becomes the score time under the callback an is used to
      // set the timestamps of data sent to ports
      runtime=elapsed;
      st->scoretime=time;
    }
  else
    {
      runtime=(time-start)/1000.0;
    }
  
  s7_pointer args = s7_cons(sc,
                            s7_make_real(sc, runtime),
                            s7_NIL(sc));
  int prot = s7_gc_protect(sc, args);
  s7_pointer retn=s7_call(sc, schemeproc, args);
  /*delta=s7_number_to_real(s7_call(sc, 
                                  schemeproc, 
                                  args
                                  )
                                  );*/
  if (retn==st->schemeError)
    delta=-2;
  else
    delta=s7_number_to_real(retn);
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
      if (st->isScoreMode())
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
  st->scoretime=0.0;
  return more;
}

//
/// Midi Input Hooks
//


void SchemeThread::midiin(const MidiMessage &msg)
{
  int op=(msg.getRawData()[0] & 0xf0)>>4;
  // change NoteOn with 0 amp to NoteOff
  if (op==MidiFlags::On && msg.getRawData()[2]==0)
    {
      op=MidiFlags::Off;
      msg.getRawData()[0] = (MidiFlags::Off << 4) | (msg.getRawData()[0] & 0xF);
    }
  MidiHook* hook=getMidiHook(op);
  if (hook)
    {
      //schemeNodes.lockArray();
      schemeNodes.addSorted(comparator, new XMidiNode(0.0, msg, hook));
      //schemeNodes.unlockArray();
      notify();
    }
}

bool SchemeThread::isMidiHook(int opr)
{
  return (getMidiHook(opr,true)!=NULL) ;
}

void SchemeThread::addMidiHook(int op, s7_pointer proc)
{
  //midiHooks.lockArray();
  s7_gc_protect(scheme, proc);
  // the "default hook" is always at end
  if (op==0)
    midiHooks.add(new MidiHook(op,proc));
  else
    midiHooks.insert(0, new MidiHook(op,proc));
  //midiHooks.unlockArray();
}

MidiHook* SchemeThread::getMidiHook(int opr, bool strict)
{
  MidiHook* hook=NULL;
  //midiHooks.lockArray();
  for (int i=0; i<midiHooks.size() && !hook; i++)
    {
      MidiHook* h=midiHooks.getUnchecked(i);
      // hook matches oper if its the same or default hook set
      if (h->op==opr || (h->op==0 && !strict))
        hook=h;
    }
  //  midiHooks.unlockArray();
  return hook;
}

void SchemeThread::removeMidiHook(MidiHook* hook)
{
  // FIX: THIS MUST ALSO REMOVE ANY PENDING XMIDINODE WITH HOOK
  //  midiHooks.lockArray();
  s7_gc_unprotect(scheme, hook->proc);
  midiHooks.removeObject(hook);
  //  midiHooks.unlockArray();
}

bool SchemeThread::clearMidiHook(int op)
{
  // if there is a hook under Op remove it and return true
  // if op==-1 remove all hooks
  if (op<0) 
    {
      int s=midiHooks.size();
      for (int i=0;i<s; i++)
        removeMidiHook(midiHooks.getLast());
      return (s>0);
    }
  else
    {
      MidiHook* hook=getMidiHook(op, true);
      if (hook)
        {
          removeMidiHook(hook);
          return true;
        }
      return false;
    }
}

bool XMidiNode::applyNode(SchemeThread* st, double curtime)
{
  s7_scheme* sc=st->scheme;
  // called on Midi message nodes if an input hook is set
  int op=(mmess.getRawData()[0] & 0xf0)>>4;
  int ch=mmess.getChannel()-1;
  int d1=mmess.getRawData()[1] & 0x7f;
  int d2=0;
  if (mmess.getRawDataSize()>2)
    d2=mmess.getRawData()[2] & 0x7f;
  // convert MidiOns with zero velocity to MidiOff
  if ((op==MidiFlags::On) && (d2==0))
    op=MidiFlags::Off;
  // create list of message data
  s7_pointer args=s7_cons(sc, 
                          s7_make_integer(sc, ch),
                          s7_cons(sc,
                                  s7_make_integer(sc, d1),
                                  s7_cons(sc,
                                          s7_make_integer(sc, d2),
                                          st->schemeNil)));
  // ALWAYS PUSH OPCODE // push status opcode if default hook
  if (true) // (hook->op==0)
    args=s7_cons(sc, s7_make_integer(sc, op), args);

  // create funargs list holding data
  args=s7_cons(sc, args, st->schemeNil);
  int prot = s7_gc_protect(sc, args);
  s7_pointer res=s7_call(sc, hook->proc, args);
  s7_gc_unprotect_at(sc, prot);
  // stubbed out because a void return seems to be the same as schemeError ???????
  if (0)// (res == st->schemeError)
    {
      st->removeMidiHook(hook);
      Console::getInstance()->printError(T(">>> Removed Midi receiver.\n"));
   }
  return false;
}

/*=======================================================================*
                              Osc Receiving
 *=======================================================================*/

XOscNode::XOscNode(double qtime, String oscpath, String osctypes)
  : XSchemeNode(qtime),
    path (oscpath),
    types (osctypes)
{
}

XOscNode::~XOscNode()
{
  ints.clear();
  flos.clear();
  strs.clear();
}

bool SchemeThread::isOscHook(String path)
{
  return (getOscHook(path,true)!=NULL) ;
}

void SchemeThread::addOscHook(String path, s7_pointer proc)
{
  //oscHooks.lockArray();
  s7_gc_protect(scheme, proc);
  // the "default hook" is always at end
  if (path==String::empty)
    oscHooks.add(new OscHook(path,proc));
  else
    oscHooks.insert(0, new OscHook(path,proc));
  //  oscHooks.unlockArray();
}

OscHook* SchemeThread::getOscHook(String path, bool strict)
{
  OscHook* hook=NULL;
  //  oscHooks.lockArray();
  for (int i=0; i<oscHooks.size() && !hook; i++)
    {
      OscHook* h=oscHooks.getUnchecked(i);
      // hook matches oper if its the same or default hook set
      if (h->path==path || (h->path==String::empty && !strict))
        hook=h;
    }
  //  oscHooks.unlockArray();
  return hook;
}

void SchemeThread::removeOscHook(OscHook* hook)
{
  // FIX: THIS MUST ALSO REMOVE ANY PENDING XMIDINODE WITH HOOK
  //  oscHooks.lockArray();
  s7_gc_unprotect(scheme, hook->proc);
  oscHooks.removeObject(hook);
  //  oscHooks.unlockArray();
}

bool SchemeThread::clearOscHook(String path)
{
  // if there is a hook under Op remove it and return true
  // if op==* remove all hooks
  if (path==T("*")) 
    {
      int s=oscHooks.size();
      for (int i=0;i<s; i++)
        removeOscHook(oscHooks.getLast());
      return (s>0);
    }
  else
    {
      OscHook* hook=getOscHook(path, true);
      if (hook)
        {
          removeOscHook(hook);
          return true;
        }
      return false;
    }
}

bool XOscNode::applyNode(SchemeThread* st, double curtime)
{
  //std::cout << "Osc message: "<< path.toUTF8() << " " << types.toUTF8();
  ////st->lockOscHook();
  //std::cout << "Osc hook!\n";
  s7_scheme* sc=st->scheme;
  // the osc message data starts with the string path
  s7_pointer snil = st->schemeNil;
  s7_pointer data = s7_cons(sc, st->schemeFalse, snil) ; // (#f) placeholder
  s7_pointer tail = data;
  
  // iterate types adding floats and ints to message data
  int F=0;
  int I=0;
  int S=0;
  for (int i=0; i<types.length(); i++)
    {
      switch (types[i])
        {
        case 'i':  // LO_INT32
        case 'h':  // LO_INT64
          s7_set_cdr(tail, s7_cons(sc, s7_make_integer(sc, ints[I++]), snil));
          break;
        case 'f':  // LO_FLOAT32
        case 'd':  // LO_FLOAT64
        case 't':  // LO_TIMETAG
          s7_set_cdr(tail, s7_cons(sc, s7_make_real(sc, flos[F++]), snil));
          break;
        case 's':  // LO_STRING
          s7_set_cdr(tail, s7_cons(sc, s7_make_string(sc, strs[S++].toUTF8()), snil));
          break;
        case 'S':  // LO_SYMBOL
          s7_set_cdr(tail, s7_cons(sc, s7_make_symbol(sc, strs[S++].toUTF8()), snil));
          break;
        case 'T':  // LO_TRUE
          s7_set_cdr(tail, s7_cons(sc, s7_make_boolean(sc, true), snil));
          break;
        case 'F':  // LO_FALSE
          s7_set_cdr(tail, s7_cons(sc, s7_make_boolean(sc, false), snil));
          break;
        case 'N':  // LO_NIL
          s7_set_cdr(tail, s7_cons(sc, snil, snil));
          break;
        case 'I':  // LO_INFINITUM
          s7_set_cdr(tail, s7_cons(sc, s7_name_to_value(sc, "most-positive-fixnum"), snil));
          break;
        case 'c':  // LO_CHAR
          s7_set_cdr(tail, s7_cons(sc, s7_make_character(sc, (char)ints[I++]), snil));
          break;
        case 'm':  // LO_MIDI
          {
            s7_pointer m=s7_cons(sc, s7_make_integer(sc, ints[I+0]),
                                 s7_cons(sc, s7_make_integer(sc, ints[I+1]),
                                         s7_cons(sc, s7_make_integer(sc, ints[I+2]),
                                                 s7_cons(sc, s7_make_integer(sc, ints[I+3]), snil))));
            s7_set_cdr(tail, s7_cons(sc, s7_cons(sc, m, snil), snil));
            I+=4;
          }
          break;
        case 'b':  // LO_BLOB
          {
            int l=(int)ints[I++]; // length of blob
            s7_pointer m=snil;
            for (int j=I+l-1; i>=I; j--)
              m=s7_cons(sc, s7_make_integer(sc, ints[j]), m);
            s7_set_cdr(tail, s7_cons(sc, s7_cons(sc, m, snil), snil));
            I+=l;
          }
          break;
        default:
          break;
        }
      tail=s7_cdr(tail);
    }
  // data is now (#f x y ...) 
  int loc;
  s7_pointer args, res;
  if (hook->path==String::empty) // is default hook
    {
      // default hook includes path as first element
      // replace placeholder #f with path
      s7_set_car(data, s7_make_string(sc, path.toUTF8()));
      args=s7_cons(sc, data, snil);
      // args now ((x y ...))
      loc = s7_gc_protect(sc, args);
      res = s7_call(sc, hook->proc, args);
    }
  else
    {
      //      // no path so reuse placeholder's cons cell:
      //      s7_set_car(data, s7_cdr(data)); 
      //      // data now ((x y ...) x y ...)
      //      s7_set_cdr(data, snil); 
      //      // data now ((x y ...))
      //      loc = s7_gc_protect(sc, data);
      //      res=s7_call(sc, hook->proc, data);
      s7_set_car(data, s7_make_string(sc, hook->path.toUTF8()));
      args=s7_cons(sc, data, snil);
      loc = s7_gc_protect(sc, args);
      res = s7_call(sc, hook->proc, args);
    }
  s7_gc_unprotect_at(sc, loc);
  // stubbed out because a void return seems to be the same as schemeError ???????
  if (0) // (res == st->schemeError)
    {
      st->removeOscHook(hook);
      Console::getInstance()->printError(T(">>> Removed OSC receiver.\n"));
    }
  return false;
}

//
// Scheduler
//

SchemeThread::SchemeThread() 
  : Thread(T("Scheme Thread")),
    pausing (false),
    interrupted (false),
    scoremode (ScoreTypes::Empty),
    sprouted (false),
    showvoid (false),
    saleval (false),
    voidstring (String::empty),
    scoretime (0.0),
    nextid (0),
    quiet (false),
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
  midiHooks.clear();
  oscHooks.clear();
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

/// SalEval

bool SchemeThread::isSalEval()
{
  return saleval;
}

void SchemeThread::isSalEval(bool sal)
{
  saleval=sal;
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
      text << T("(load ") << path << T(")");
      //std::cout << "load text='" << text.toUTF8() << "'\n";
      eval(text);
      if (addtorecent)
	{
#ifdef GRACE
	  Preferences::getInstance()->recentlyLoaded.addFile(file);
#endif
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
  CodeDocument doc;
  CodeDocument::Position pos(&doc,0);
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
      int typ;
      doc.replaceAllContent(text);
      pos.setPosition(0);
      typ=LispSyntax::getInstance()->scanCode(doc, pos, true, ScanIDs::MoveExpressions);
      if (typ==ScanIDs::SCAN_LIST || typ==ScanIDs::SCAN_TOKEN || typ==ScanIDs::SCAN_STRING)
	break;
      else if (typ==ScanIDs::SCAN_UNLEVEL)
	break;  // allow too many parens to be passed to lisp?
    }
  if (!text.isEmpty())
    eval(text);
}

void SchemeThread::printBanner()
{
  String banner=String::empty;
  banner << SystemStats::getJUCEVersion()
         << T(" ") << SysInfo::getCopyright(T("Julian Storer")) << T("\n")
         << getLispVersion() 
         << T("\n");
#ifdef WITHFOMUS
  if (fomus_exists) 
    banner << Fomus::getFomusVersion() 
           << T("\n");
#endif
  banner << SysInfo::getCMLogo() 
         << T("\n" );
  Console::getInstance()->printOutput(banner);
}

void SchemeThread::run()
{
  double qtime, utime;
  XSchemeNode* node;

  if (!init())
      return;
  if (!isQuiet())
    printBanner();
  pausing=false;
  while (! threadShouldExit())
    {
      while ( true ) 
	{
          //	  schemeNodes.lockArray();
	  node=schemeNodes.getFirst();
          //	  schemeNodes.unlockArray();
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
              //	      schemeNodes.lockArray();
	      schemeNodes.remove(0, false);
              //	      schemeNodes.unlockArray();
	      // NOTE: the node to process has now been popped from the
	      // queue.  i did this while trying to debug the random
	      // crashing. im not sure if this is the right thing to do or
	      // not since this means that flushing the queue, etc will have
	      // no effect on this node. Search for the word POP to see the
	      // places this affects...
	      //lock.enter();
	      bool keep=node->applyNode(this, 0.0);
	      //lock.exit();
	      if (keep)
		{
                  //		  schemeNodes.lockArray();
		  schemeNodes.addSorted(comparator,node);
		  //          schemeNodes.remove(0, false);
                  //		  schemeNodes.unlockArray();
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
	closeScore();
      sprouted=false;
      scoretime=0.0;
      //      setScoreMode(ScoreTypes::Empty); only done in closeScore
#ifdef GRACE
      wait(-1);
#else
      read();
#endif
    }
  // leaving killed process....
}

void SchemeThread::closeScore()
{
  if (!isScoreMode()) return;
  // we just finished running a sprouted process in score
  // mode, send a "score complete" message to the console for
  // processing the file output
  if (isScoreMode(ScoreTypes::Midi))
    MidiOutPort::getInstance()->performCommand(CommandIDs::SchedulerScoreComplete);
#ifdef SNDLIB
  else if (isScoreMode(ScoreTypes::SndLib))
    SndLib::getInstance()->performCommand(CommandIDs::SchedulerScoreComplete);
#endif	  
#ifdef WITHFOMUS
  else if (isScoreMode(ScoreTypes::Fomus))
    Fomus::getInstance()->closeScore();
#endif	  
  else if (isScoreMode(ScoreTypes::Csound))
    Csound::getInstance()->saveScore();
  setScoreMode(ScoreTypes::Empty);
}

void SchemeThread::clear()
{
  // this should NEVER be called from scheme code (an EVAL node) or
  // else the run() loop will bomb since it assumes index[0] exists
  //  schemeNodes.lockArray();
  schemeNodes.clear();
  //  schemeNodes.unlockArray();
}

void SchemeThread::addNode(XSchemeNode* node)
{
  //  schemeNodes.lockArray();
  schemeNodes.addSorted(comparator, node);
  //  schemeNodes.unlockArray();
  notify();
}

// addNode for processes

void SchemeThread::sprout(double _time, s7_pointer proc, int _id)
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
  //  schemeNodes.lockArray();
  schemeNodes.addSorted(comparator, new XProcessNode( _time, proc, _id));
  //  schemeNodes.unlockArray();
  notify();
}

void SchemeThread::eval(char* str)
{
  eval(String(str));
}

void SchemeThread::eval(String s)
{
  //  schemeNodes.lockArray();
  schemeNodes.addSorted(comparator, new XEvalNode(0.0, s));
  //  schemeNodes.unlockArray();
  notify();
}

void SchemeThread::quit()
{
  //  schemeNodes.lockArray();
  schemeNodes.addSorted(comparator, new XControlNode(0.0, XControlNode::QueueQuit));
  //  schemeNodes.unlockArray();
  notify();
}

void SchemeThread::setPaused(bool p) {}

void SchemeThread::stop(int ident)
{
  // always add stop nodes to the front of the queue.
  //  schemeNodes.lockArray();
  schemeNodes.insert(0, new XControlNode (0.0, XControlNode::QueueStop, ident));
  //  schemeNodes.unlockArray();
  notify();
}

void SchemeThread::stopProcesses(int ident)
{
  // this is called by a STOP node from process().  stop all processes
  // with id from running. if id=-1 then stop all processes. iterate
  // queue in reverse order so removal index remains valid.  NOTE: POP
  // removed the (STOP) node that got us here so this deletes up to
  // and including index 0. otherwise dont include index 0

  //  schemeNodes.lockArray();
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
  //  schemeNodes.unlockArray();
  // if stopped all processes also clear any pending messages and send
  // all notes off
  // GET RID OF THIS!
  if (ident<0)
    MidiOutPort::getInstance()->clear();
}

bool SchemeThread::isQueueEmpty()
{
  //  schemeNodes.lockArray();
  int size=schemeNodes.size();
  //  schemeNodes.unlockArray();
  return (size == 0);
}

void SchemeThread::interruptScheme()
{
  schemeNodes.clear(); // remove any running nodes from scheduler
  clearMidiHook(-1);
  clearOscHook(juce::String("*"));
}
