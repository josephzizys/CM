/*=======================================================================*
  Copyright (C) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#include <iostream>
#include <string>
#include <math.h>
#include "juce.h"
#include "Enumerations.h"
#include "CmSupport.h"
#include "Midi.h"
#include "Csound.h"
#include "Console.h"
#include "Syntax.h"

#ifdef WITHFOMUS
#define FOMUS_TYPESONLY
#include "Fomus.h"
#include "fomus/infoapi.h"
#endif

#ifdef GRACE
#include "Plot.h"
#include "Cells.h"
#endif

#ifdef LIBLO
#include "Osc.h"
#endif

#define POWF(a,b)	(powf( (a) , (b) ))
#define LOGF(a)		(logf( (a) ))
#define EXPF(a)		(expf( (a) ))
#define SQRTF(a)	(sqrtf( (a) ))
#define TANF(a)		(tanf( (a) ))

#ifdef _MSC_VER
#define strdup _strdup
#define jn _jn
double log2(double n) {return log(n)/log(2.0);}
int round(double n) {return (int)(n+.5);}
#endif

void cm_quit()
{
#ifdef GRACE
  Console::getInstance()->printError(T(">>> Error: You cannot quit Grace from inside Lisp. Use Console>File>Quit to quit the application.\n"));
#else
  Scheme::getInstance()->quit();
#endif
}

void cm_print_output(char* str, bool quote)
{
  if (quote)
    Console::getInstance()->printOutput(String(str).quoted());    
  else
    Console::getInstance()->printOutput(str);
}

void cm_print_error(char* str)
{
  //std::cout << "print_error: '" << str << "'\n";
  Console::getInstance()->printError(String(str));
}

void cm_print_values(char* str)
{
  Console::getInstance()->printValues(str);
}

void cm_print_stdout(char* str)
{
  std::cout << str;
}



void cm_shell(char* str)
{
  system(str);
}

void cm_play(char* str)
{
  String path=String(str);
  File file=completeFile(path);

  if (file.hasFileExtension(T("mid")))
    {
    }
  else
    {
      Console::getInstance()->postAsyncMessage(CommandIDs::AudioOpenFilePlayer,
					       path, true);
    }
}
  
String cm_version()
{
  return SysInfo::getCMVersion();
}

String cm_logo ()
{
  String crlf=String("\n");
  String vers=cm_version();
  String logo = String::empty;
  logo << String(" /\\\\\\") << crlf
       << String("---\\\\\\---------") << crlf
       << String("----\\\\\\--------") << crlf
       << String("----/\\\\\\-------") << String(" ") << vers << crlf
       << String("---/--\\\\\\------") << crlf
       << String("--/----\\\\\\-----") << crlf
       << String(" /      \\\\\\/");
  return logo;
}


void cm_load_sal_file(char *path)
{
  //SalSyntax::getInstance()->loadFile( String(path) );  
}

//#if (defined(PPC) && defined(MACOSX))
//#define POWF(a,b)	(juce::powf( (a) , (b) ))
//#define LOGF(a)		(juce::logf( (a) ))
//#define EXPF(a)		(juce::expf( (a) ))
//#define SQRTF(a)	(juce::sqrtf( (a) ))
//#define TANF(a)		(juce::tanf( (a) ))
//#else
//#endif

double cm_log_ten(double num)
{
  if (num>0.0)
    return log10(num);
  else
    return 0.0;
}

double cm_log_two(double num)
{
  if (num>0.0)
    return log2(num);
  else
    return 0.0;
}

// mapping, scaling and offsetting

double cm_rescale(double x, double x1, double x2, double y1, double y2, double b)
{
  if (x >= x2) 
    return y2;
  else if (x <= x1)
    return y1;
  else if (b == 1)
    return (((( y2 - y1) / (x2 - x1)) * (x - x1)) + y1);
  else
    {
      double p = (x - x1) / (x2 - x1);
      return y1 + ( ( (y2 - y1) / (b - 1.0)) * (POWF(b, p) - 1.0));
    }
}

int cm_discrete(double x, double x1, double x2, int i1, int i2, double b)
{
  // return integers from a to b as n goes from 0.0 to 1.0
  //  return (int)round(cm_rescale(x,x1,x2,(double)i1, (double)i2, b));
  return (int)floor(cm_rescale(x,x1,x2,(double)i1, (double)i2, b));
}

int cm_float_to_fixnum(double f)
{
  return (int)round(f);
}

double cm_decimals(double val, int places)
{
  double p10 = (double)(10 ^ places);
  return round(val*p10) / p10;
}

double cm_quantize(double val, double step)
{
  return floor( (val/step) + .5) * step;
}

double cm_rhythm_to_seconds(double beats, double tempo, double beat)
{
  return (double) ((beats / beat) * (60.0f / tempo)) ;
}

double cm_cents_to_scaler(double cents)
{
  double p = ((double)cents)/1200.0f;
  return POWF(2.0f,p);
}

double cm_scaler_to_cents(double scaler)
{
  return (LOGF(scaler)/LOGF(2.0)) * 1200.0;
}

double cm_scaler_to_steps(double scaler)
{
  return cm_scaler_to_cents(scaler)/100.0;
}

double cm_expl(double powr, double y0, double y1, double base)
{
  if (powr < 0)
    powr=0.0;
  else if (powr > 1) powr = 1.0;
  if (base == 1.0)
    return y0 + ( powr * (y1 - y0));
  return ( y0 + ( ( (y1 - y0) / (base - 1.0) ) *
		  ( pow(base, powr) - 1.0 )));
}

double cm_explseg( int i, int len, double sum, double powr)
{
  if (i >= len)
    i += -1;
  double x1 = ((double)(i+1)) / ((double)len);
  double x2 = ((double)i) / ((double)len);
  double f1 = cm_expl( x1, 0.0, 1.0, powr);
  double f2 = (i <= 0) ? 0.0 : cm_expl( x2, 0.0, 1.0, powr);
  return ( sum * (f1 - f2) );
}

double cm_geoseg(int i, int len, double sum, double base) 
{
  if (len==0)
    return 0.0;
  double a=sum * ((1.0 - base) / (1.0 - pow(base, len)));
  return  a * pow(base, i);
}

#define A00 6.875   // keynum 0

double cm_hertz_to_keynum (double hz)
{
  // subtract 3 shifts to A
  return (((LOGF(hz) - LOGF(A00) ) / LOGF(2)) * 12) - 3;
}

double cm_keynum_to_hertz(double kn)
{
  return A00 * pow(2, ((kn + 3) / 12));
}

int cm_keynum_to_pc (double kn)
{
  return ((int)kn) % 12;
}

//
// Randomness
//

Random ranstate (1000);

void cm_ranseed(long s)
{
  ranstate.setSeed((int64)s);
}

double cm_ranfloat(double f)
{
  if (f == 0.0)
    return 0.0;
  if (f == 1.0)
    return ranstate.nextDouble();
  return (ranstate.nextDouble() * f);
}

double cm_ranfloat2(double f1, double f2)
{
  if (f1 == f2)
    return f1;
  if (f1 < f2)
    return (f1 + (ranstate.nextDouble() * (f2-f1)));
  return (double) (f1 - (ranstate.nextDouble() * (f1-f2)));
}

int cm_ranint(int i)
{
  if (i > 0 )
    return ranstate.nextInt(i);
  if (i < 0)
    return 0 - ranstate.nextInt(abs(i));
  return 0;
}

int cm_ranint2(int i1, int i2)
{
  if (i1 == i2)
    return i1;
  if (i1 < i2)
    return (i1 + ranstate.nextInt(i2-i1));
  return i1 - ranstate.nextInt(i1-i2);
}

double cm_ranlow()
{
  return juce::jmin( ranstate.nextDouble(), ranstate.nextDouble());
}

double cm_ranhigh()
{
  return juce::jmax( ranstate.nextDouble(), ranstate.nextDouble());
}

double cm_ranmiddle()
{
  return (ranstate.nextDouble() + ranstate.nextDouble()) / 2.0f;
}

double cm_ranbeta (double a, double b)
{
  double ra=1.0/a, rb=1.0/b, r1, r2, y1, y2, sum;
  while (true) {
    r1 = ranstate.nextDouble();
    r2 = ranstate.nextDouble();
    y1 = POWF(r1,ra);
    y2 = POWF(r2,rb);
    sum=y1+y2;
    if ( sum <= 1.0) return (double) (y1 / sum);
  }
}

double cm_ranexp (double lambda)
{
  return (- LOGF(1.0f - ranstate.nextDouble())) / lambda;
}

double cm_ranexp2 (double lambda)
{
  double ee = (2 * EXPF(-1.0));
  double u, v;
  while ( true ) {
    u = 1.0 - ranstate.nextDouble();
    v = ee * ranstate.nextDouble();
    if ( v <= (ee * u * LOGF(u)) )
      return (v / u) / lambda;
  }
}

//double cm_gauss() {
//  double a = ranstate.nextDouble();
//  double b = ranstate.nextDouble();
//  return (double)( SQRTF(-2.0 * LOGF(1.0-a)) *
//		  cosf(juce::double_Pi * 2 * b) );
//}

double cm_rangauss (double sigma, double mu)
{
  // sigma=stand dev, mu=mean
  double x, y, r2;
  do
    {
      x = -1 + 2 * ranstate.nextDouble();
      y = -1 + 2 * ranstate.nextDouble();
      r2 = x * x + y * y;
    }
  while (r2 > 1.0 || r2 == 0);
  return (sigma * y * SQRTF(-2.0 * LOGF(r2) / r2))+mu;
}

double cm_rancauchy()
{
  return(TANF(juce::double_Pi*(ranstate.nextDouble() - 0.5f)));
}

int cm_ranpoisson (double lambda)
{
  double b = EXPF( - lambda);
  int n = 0;
  double p = 1.0;
  while (true)
    {
      p = p * ranstate.nextDouble();
      n++;
      if ( p < b ) return n;
    }
}

double cm_rangamma (double nu)
{
  double r=1.0;
  int n=(int)round(nu);
  for (int i=0; i<n; i++)
    r = r * (1 - ranstate.nextDouble());
  return - LOGF(r);
}

//// http://home.earthlink.net/~ltrammell/tech/pinkalg.htm
//// this doesnt seem to work.. too bad as it would keep the load even
//#define NGEN 3
//double av[NGEN] = {0.0046306,  0.0059961,  0.0083586};
//double pv[NGEN] = {0.31878,  0.77686,  0.97785};
//
//// (loop for x in  '(0.0046306  0.0059961  0.0083586) collect (* x 2 (- (random 1.0) .5)))
//double randreg[NGEN] = {0.0018758787, -0.0027519993, 0.0025562837};
//double cm_ranpink() {
//  // Update each generator state per probability schedule
//  double rv = ranstate.nextDouble();
//  for (int i=0; i<NGEN; i++)
//    if (rv > pv[i])
//      randreg[i] = av[i] * 2 * (ranstate.nextDouble()-0.5);
//  // sum the generators
//  return randreg[0] + randreg[1] + randreg[2];
//}

#define POW2 5
#define POWN 32
double pinking[POWN];

double one_over_f_aux(int n, double *r, double halfrange)
{
  double sum=0.0;
  for (int i=0; i<POW2; i++) 
    {
      double p = POWF(2.0, i);
      if (! ((n / p) == ((n - 1) / p)))
	r[i]=( (ranstate.nextDouble() * 2 * halfrange) - halfrange) ;
      sum += r[i];
    }
  return sum;
}

double cm_ranpink()
{
  // Based on Gardner (1978) and Dick Moore (1988?)
  static int i=POWN;
  if (i==POWN )
    {
      double r[POW2];
      double h=1.0/POW2;
      for (int n=0; n<POWN; n++)
	{
	  pinking[n]=one_over_f_aux(n, r, h);
	}
      i=0;
      //    for (int j=0;j<32;j++)
      //      printf(" %f", pinking[j]);
      //    printf("\n");
    }
  else i++;
  return pinking[i];
}

double cm_ranbrown()
{
  // from http://vellocet.com/dsp/noise/VRand.h
  // but made to generate between -1 1
  
  static double b=0.0;
  while (true) 
    {
      double  r = ranstate.nextDouble()*2-1;
      b += r;
      if (b<-16.0f || b>16.0f) b -= r;
      else break;
    }
  // return interval -1 1.
  return (b*0.0625);
}

double cm_bes_jn(int a, double b)
{
  return jn(a,b);
}

//
// scheduler and processes
//

double cm_now() 
{
  return Time::getMillisecondCounterHiRes() / 1000.0;
}

void cm_sched_sprout(SCHEMEPROC proc, double time, int id)
{
  // if score capture is true AND we are under a process callback then
  // scoretime will be >= 0 else it will be 0
  Scheme* scm=Scheme::getInstance();
  // if (scm->scoremode)
  //    time=time+scm->scoretime;
  scm->sprout(time, proc, id);
}

bool cm_sched_paused_p()
{
  return Scheme::getInstance()->isPaused();
}

void cm_sched_pause() 
{
  Scheme::getInstance()->setPaused(true);
}

void cm_sched_continue()
{
  Scheme::getInstance()->setPaused(false);
}

void cm_sched_stop(int id)
{
  Scheme::getInstance()->stop(id);
}

void cm_sched_hush() 
{
  Scheme::getInstance()->stop(-1);
}

bool cm_sched_busy_p()
{
  //return !Scheme::getInstance()->isQueueEmpty();
  return Scheme::getInstance()->sprouted;
}

void cm_sched_set_score_mode(int val)
{
  // this must only be called if scheduler is empty!
  Scheme::getInstance()->setScoreMode(val);
}

bool cm_sched_score_mode_p()
{
  return Scheme::getInstance()->isScoreMode();
}

double cm_sched_score_time()
{
  // should only be called under score mode
  return Scheme::getInstance()->getScoreTime();
}

//
// file system and pathname support. CONVERT THESE TO STRINGS or MOve to Lisp
//

File completeFile(String path)
{
  if (File::isAbsolutePath(path))
    return File(path);
  else
    return File::getCurrentWorkingDirectory().getChildFile(path).getFullPathName();
}
char* cm_user_home_directory()
{
  File f=File::getSpecialLocation(File::userHomeDirectory);
  String s=f.getFullPathName();
#ifdef WINDOWS
  s=s.replaceCharacter('\\','/');
#endif
  if (! s.endsWithChar('/'))
    s << String("/"); 
  return (char *)strdup(s.toUTF8());  // return copy
}

char* cm_temp_directory()
{
  File f=File::getSpecialLocation(File::tempDirectory);
  String s=f.getFullPathName();
#ifdef WINDOWS
  s=s.replaceCharacter('\\','/');
#endif
  if (! s.endsWithChar('/'))
    s << String("/");
  return (char *)strdup(s.toUTF8());
}

char* cm_current_directory() 
{
  String s=File::getCurrentWorkingDirectory().getFullPathName();
  return (char *)strdup(s.toUTF8());
}

bool cm_set_current_directory(char *path) 
{
  File dir=completeFile(String(path));
  if (! dir.isDirectory())
    return false;
  dir.setAsCurrentWorkingDirectory();
  return true;
}

char* cm_pathname_name(char* path)
{

  File f=completeFile(String(path));
  String s=f.getFileNameWithoutExtension();
  return (char *)strdup(s.toUTF8());
}

char* cm_pathname_type(char* path)
{
  File f=completeFile(String(path));
  String s=f.getFileExtension();
  if (s.startsWithChar('.'))
    s=s.substring(1);
  return (char *)strdup(s.toUTF8());
}

char* cm_pathname_directory(char* path)
{
  String s=String(path);
#ifdef WINDOWS
  s=s.replaceCharacter('\\','/');
#endif
  int p=s.lastIndexOfChar('/');
  if (p<0)
    return "";
  else 
    return (char *)strdup(s.substring(0,p+1).toUTF8());
}

char* cm_full_pathname(char* path)
{
  File f=completeFile(String(path));
  String s=f.getFullPathName();
#ifdef WINDOWS
  s=s.replaceCharacter('\\','/');
#endif
  return (char *)strdup(s.toUTF8());
}

bool cm_pathname_exists_p(char* path)
{
  File f=completeFile(String(path));
  return f.exists();
}

bool cm_pathname_writable_p(char* path)
{
  File f=completeFile(String(path));
  return f.hasWriteAccess();
}

bool cm_pathname_directory_p(char* path)
{
  File f=completeFile(String(path));
  return f.isDirectory();
}

char* cm_directory(char* path, bool recurse)
{
  File f=completeFile(String(path));
  if (f.existsAsFile())
    {
      String s=T("(\"") + f.getFullPathName() + T("\")");
      return (char*)strdup(s.toUTF8());
    }
  String s=T("*");
  if (!f.isDirectory())
    {
      s=f.getFileName();
      f=f.getParentDirectory();
    }
  OwnedArray<File> a;
  int i=(recurse) ? File::findFiles : File::findFilesAndDirectories;
  int n=f.findChildFiles(a, (i | File::ignoreHiddenFiles), recurse, s);
  if (n==0)
    return (char*)NULL;
  s=T("(");
  for (int j=0; j<n; j++)
    s << T(" \"") << a[j]->getFullPathName() << T("\"");
  s<<T(")");
  return (char*)strdup(s.toUTF8());
}

// Sal support

char* sal_tokenize(char* str)
{
  String toks=SalSyntax::getInstance()->tokenize(String(str));
  if (toks.isEmpty())
    return (char *)NULL;
  return (char *)strdup(toks.toUTF8());  // return copy
}


/*
 * port information
 */

char* cm_port_info()
{
  // return a string that Scheme can (read) to create a list
  // containing port information

  String info="(";
  StringArray devs=MidiOutput::getDevices();
  info << String("(\"midi.port\"");
  for (int i=0; i<devs.size(); i++)
    {
      info << String(" (")
	   << String(i) << String(" -> ")
	   << String("\"") << devs[i] << String("\"");
      if (MidiOutPort::getInstance()->isOpen(i))
	info << String(" #t)");
      else
	info << String(" #f)");
    }
  devs=MidiInput::getDevices();
  for (int i=0; i<devs.size(); i++)
    {
      info << String(" (")
	   << String(i) << String(" <- ")
	   << String("\"") << devs[i] << String("\"");
      if (MidiInPort::getInstance()->isOpen(i))
	info << String(" #t)");
      else
	info << String(" #f)");
    }
  info << String(")");

  info << String(")"); // end of port list
  return (char*)strdup(info.toUTF8());
}

/*
 * Midi port
 */

bool mp_open_output(int dev)
{
  return MidiOutPort::getInstance()->open(dev);
}

bool mp_open_input(int dev)
{
  return MidiInPort::getInstance()->open(dev);
}

void mp_close_output(int dev)
{
  MidiOutPort::getInstance()->close(dev);
}

void mp_close_input(int dev)
{
  MidiInPort::getInstance()->close(dev);
}

void mp_set_output_file(char* path)
{
  MidiOutPort::getInstance()->
    performCommand(CommandIDs::MidiSeqSetFile, 0, String(path));
}

void mp_send_note(double time, double dur, double key, double vel, double chn) 
{
  Scheme* scm=Scheme::getInstance();
  if (scm->scoremode)
    {
      // if score capture is true AND we are under a process callback then
      // scoretime will be >= 0 else it will be 0
      time+=scm->scoretime;
      MidiOutPort::getInstance()->
	sendNote(time, dur, key, vel, chn, true);
    }
  else
    MidiOutPort::getInstance()->
      sendNote(time, dur, key, vel, chn, false);
}

void mp_send_data(int type, double time, double chan, 
		  double data1, double  data2)
{
  Scheme* scm=Scheme::getInstance();
  if (scm->scoremode)
    {
      // if score capture is true AND we are under a process callback then
      // scoretime will be >= 0 else it will be 0
      time=time+scm->scoretime;
      MidiOutPort::getInstance()->
	sendData(type, time, chan, data1, data2, true) ;
    }
  else
    {
      MidiOutPort::getInstance()->
	sendData(type, time, chan, data1, data2, false) ;
    }
}

void mp_set_tuning(int div)
{
  MidiOutPort::getInstance()->performCommand(CommandIDs::MidiOutTuning,
					     div);
}

void mp_set_instruments(int a,int b,int c,int d,int e,int f,int g,int h,
			int i,int j,int k,int l,int m,int n,int o,int p)
{
  if (a>=0) MidiOutPort::getInstance()->setInstrument(0,a);
  if (b>=0) MidiOutPort::getInstance()->setInstrument(1,b);
  if (c>=0) MidiOutPort::getInstance()->setInstrument(2,c);
  if (d>=0) MidiOutPort::getInstance()->setInstrument(3,d);
  if (e>=0) MidiOutPort::getInstance()->setInstrument(4,e);
  if (f>=0) MidiOutPort::getInstance()->setInstrument(5,f);
  if (g>=0) MidiOutPort::getInstance()->setInstrument(6,g);
  if (h>=0) MidiOutPort::getInstance()->setInstrument(7,h);
  if (i>=0) MidiOutPort::getInstance()->setInstrument(8,i);
  if (j>=0) MidiOutPort::getInstance()->setInstrument(9,j);
  if (k>=0) MidiOutPort::getInstance()->setInstrument(10,k);
  if (l>=0) MidiOutPort::getInstance()->setInstrument(11,l);
  if (m>=0) MidiOutPort::getInstance()->setInstrument(12,m);
  if (n>=0) MidiOutPort::getInstance()->setInstrument(13,n);
  if (o>=0) MidiOutPort::getInstance()->setInstrument(14,o);
  if (p>=0) MidiOutPort::getInstance()->setInstrument(15,p);
  MidiOutPort::getInstance()->sendInstruments();
}

void mp_play_seq()
{
  MidiOutPort::getInstance()->performCommand(CommandIDs::MidiSeqPlay);
}

void mp_save_seq()
{
  MidiOutPort::getInstance()->performCommand(CommandIDs::MidiSeqSave);
}

void mp_copy_seq()
{
  MidiOutPort::getInstance()->performCommand(CommandIDs::MidiSeqCopyToTrack);
}

void mp_plot_seq()
{
  MidiOutPort::getInstance()->performCommand(CommandIDs::MidiSeqPlot);
}

void mp_clear_seq()
{
  //Console::getInstance()->postAsyncMessage(CommandIDs::MidiSeqClear, true);
  MidiOutPort::getInstance()->performCommand(CommandIDs::MidiSeqClear);
}

void mp_set_channel_mask(int mask)
{
  MidiInPort::getInstance()->setChannelMask(mask);
}

void mp_set_message_mask(int mask)
{
  MidiInPort::getInstance()->setOpcodeMask(mask);
}

void mp_set_midi_input_hook(SCHEMEPROC proc)
{
  Scheme::getInstance()->setMidiInputHook(proc);
}

void mp_clear_midi_input_hook()
{
  Scheme::getInstance()->clearMidiInputHook();
}

// Csound support

void cs_init_score(char* args)
{
  //  std::cout << "cm_init_score " << args << "\n";
  Csound::getInstance()->initScore(String(args));
}

void cs_send_score(int typ, int num, double time, char* pars)
{
  //std::cout << "cs_send_score " << typ << " " << num << " "  << time << " " << pars << "\n";
  Csound::getInstance()->addToScore(typ,num,time,String(pars));
}

//
// FOMUS Support
//

#ifdef WITHFOMUS // defined(WITHFOMUS) && defined(GRACE)

int fms_open_score(char* scorename, char* scoreargs)
{
  if (!check_fomus_exists()) return 0;
  return Fomus::getInstance()->openScore(String(scorename), String(scoreargs), true);
}

void fms_close_score()
{
  if (!check_fomus_exists()) return;
  Fomus::getInstance()->closeScore();
}

void fms_save(const char* name)
{
  if (!check_fomus_exists()) return;
  Fomus::getInstance()->saveScore(name, true);
}

void fms_xml(char* str)
{
  if (!check_fomus_exists()) return;
  double now=(Scheme::getInstance()->scoremode) 
    ? Scheme::getInstance()->scoretime : 0.0;
  // if score capture is true AND we are under a process callback then
  // scoretime will be >= 0 else it will be 0
  Fomus::getInstance()->sendXml(String(str), now);
}  

void fms_new(const char* name)
{
  if (!check_fomus_exists()) return;
  Fomus::getInstance()->newScore(name, true);
}

void fms_select(const char* name)
{
  if (!check_fomus_exists()) return;
  Fomus::getInstance()->selectScore(name, true);
}

void fms_free()
{
  if (!check_fomus_exists()) return;
  Fomus::getInstance()->deleteScore();
}

void fms_clear()
{
  if (!check_fomus_exists()) return;
  Fomus::getInstance()->clearScore();
}

// void fms_init()
// {
//   Fomus::getInstance()->initScore();
// }

void fms_load(char* filename)
{
  if (!check_fomus_exists()) return;
  Fomus::getInstance()->loadScore(String(filename));
}

void fms_run()
{
  if (!check_fomus_exists()) return;
  fomuserr = false;
  Fomus::getInstance()->runScore(true);
}

int fms_isfiletype(const char* ext) 
{
  if (!check_fomus_exists()) return 0;
  String x(ext);
  if (!x.isEmpty() && x[0] == '.') x = x.substring(1);
  info_extslist f(fapi_info_list_exts());
  String mid("mid"), midi("midi");
  for (const char **i = f.exts, **ie = (f.exts + f.n); i < ie; ++i) 
    {
      if (mid == String(*i) || midi == String(*i)) continue;
      if (x == String(*i)) return 1;
    }
  return 0;
}

#else
int fms_isfiletype(const char* ext) {return 0;}
int fms_open_score(char* a, char* b){return 0;}
void fms_close_score(){}
void fms_new(const char* name){}
void fms_select(const char* name) {}
void fms_free(){}
void fms_clear(){}
void fms_load(char* filename){}
void fms_run(){}
void fms_save(const char* name) {}
void fms_xml(char* str){}  
#endif

#ifdef GRACE
void plot_xml(char* text)
{
  // open new window in message thread. we dont copy Lisp string
  // because this function is blocked until callback returns so string
  // is still valid.
  MessageManager::getInstance()->
    callFunctionOnMessageThread((MessageCallbackFunction*)
				&PlotterWindow::openWindowFromXml,
				(void*)text);
} 

void plot_add_xml_points(char* title, char* points)
{
  String wtitle (title);
  PlotterWindow* w=PlotterWindow::getPlotWindow(wtitle);
  if (w)
    {
      // copy string to avoid Lisp gc'ing before message is processed
      // listener explicitly deletes it
      w->listener.postMessage(new Message(CommandIDs::PlotterAddXmlPoints,
					  0,
					  0,
					  (void*)strdup(points)));
    }
  else
    Console::getInstance()->
      printError(T(">> Error: no plot named ")+wtitle.quoted()+T(".\n"));
} 

char* plot_data(char* title, int all)
{
  String text=String::empty;
  String wtitle (title);
  PlotterWindow* w=PlotterWindow::getPlotWindow(wtitle);
  if (w!=NULL)
    {
      int nlayer=w->plotter->numLayers();
      int nfield=w->plotter->numFields();
      if ((nlayer>1) && all)
	{
	  text<<T("(");
	  for (int i=0; i<nlayer; i++)
	    text<<w->plotter->getLayer(i)->toString(TextIDs::Lisp,
						    2,
						    (nfield>2),
						    0xFF);
	  text<<T(")");
	}
      else
	text=w->plotter->getFocusLayer()->toString(TextIDs::Lisp,
						   2,
						   (nfield>2),
						   0xFF);
    }
  else
    {
      text=T("()");
      Console::getInstance()->
	printError(T(">> Error: no plot named ")+wtitle.quoted()+T(".\n"));
    }
  return (char *)strdup(text.toUTF8());  
}

bool sw_open_from_xml(char* text)
{
  String tmp=String(text);
  XmlDocument doc (tmp);
  XmlElement* xml=doc.getDocumentElement();
  bool ok=true;
  if (xml)
    {
      std::cout << "xml=" << xml->createDocument(String::empty, true, false).toUTF8() << "\n";
      if (xml->hasTagName(T("statewindow")))
	{
	  StateWindow* sw=StateWindow::findStateWindow(xml->getStringAttribute(T("title")));
	  if (sw) 
	    ok=false;
	  else
	    MessageManager::getInstance()->
	      callFunctionOnMessageThread((MessageCallbackFunction*)
					  &StateWindow::openWindowFromXml,
					  (void*)xml
					  );
	}
      delete xml;
    }
  else
    {
      String err=T(">>> Error: ") + doc.getLastParseError() + T("\n");
      Console::getInstance()->printError(err);
      ok=false;
    }
  return ok;
}

void sw_draw(char* title, SCHEMEOBJECT obj, int data1, int data2)
{
  // if obj is a list then data1 is its length and data2 is the row
  // if obj is an integer then data1 is the row and data2 is the column
  StateWindow* sw=StateWindow::findStateWindow(String(title));
  if (sw==NULL) return; // no cell window open

  if (s7_is_integer(obj))
    {
      int state=(int)s7_integer(obj);
      // pass column value in the pointer parameter. 
      sw->listener.postMessage(new Message(CommandIDs::StateWindowSetCell,
					   state, data1, (void*)data2));
    }
  else if (s7_is_pair(obj))
    {
      SCHEMEOBJECT p,x;
      int i;
      int* data=new int[data1];
      //std::cout << "sw_show (list): length=" <<data1<<"\n";
      for (i=0, p=obj; i<data1; i++, p=s7_cdr(p)) 
	{
	  x=s7_car(p);
	  if (s7_is_integer(x))
	    data[i]=(int)s7_integer(x);
	  else
	    data[i]=0;
	  //std::cout << "  data["<<i<<"]: "<<data[i]<<"\n";
	}
      sw->listener.postMessage(new Message(CommandIDs::StateWindowSetCells,
					   data1, data2, (void*)data));
    }
  /*  else if (s7_is_vector(obj))
    {
      s7_pointer *vector_elements=s7_vector_elements(obj);
      if (s7_vector_rank(obj)==1)
	{
	  for (int x = 0; x < s7_vector_length(obj); x++)
	    std::cout << " x: " << x << ", (1dvec x): " 
		      << (int)s7_integer(vector_elements[x])
		      << "\n";	  
	}
      else if (s7_vector_rank(obj)==2) 
	{
	  s7_Int *offsets, *dimensions;
	  dimensions = s7_vector_dimensions(obj);
	  offsets = s7_vector_offsets(obj);
	  for (int y = 0; y < dimensions[0]; y++)
	    for (int x = 0; x < dimensions[1]; x++)
	      std::cout << "y: " << y << ", x: " << x << ", (2dvec y x): " 
			<< (int)s7_integer(vector_elements[y * offsets[0] + 
							   x * offsets[1]])
			<< "\n";
	}
      else if (s7_vector_rank(obj)==3)
	{
	  s7_Int *offsets, *dimensions;
	  dimensions = s7_vector_dimensions(obj);
	  offsets = s7_vector_offsets(obj);
	  int zind=data1;
	  int size=dimensions[1] * dimensions[2];
	  int* data=new int[size];
	  int i=0;
	  for (int y = 0; y < dimensions[1]; y++)
	    for (int x = 0; x < dimensions[2]; x++)
	      data[i++]=(int)s7_integer(vector_elements[zind * offsets[0] + 
							y * offsets[1] +
							x * offsets[2]]);
	  sw->listener.postMessage(new Message(CommandIDs::StateWindowSetCells,
					       size,
					       0,
					       (void*)data
					       ));
	}
    }  */
}

#else

void plot_xml(char* text){}
void plot_add_xml_points(char* title, char* points){}
char* plot_data(char* text, int layer) {return (char *)NULL;}

bool sw_open_from_xml(char* s){return false;}
void sw_draw(char* w, SCHEMEOBJECT obj, int a, int b){}

#endif

#ifdef LIBLO

int osc_open(char* port, char* targ)
{
  return OscPort::getInstance()->open(String(port), String(targ));
}

bool osc_open_p()
{
  return OscPort::getInstance()->isOpen;
}

int osc_close()
{
  return OscPort::getInstance()->close();
}

void osc_set_hook(bool hook)
{
  OscPort::getInstance()->isHookActive=hook;
}

int osc_send(char* path, SCHEMEOBJECT list, SCHEMEOBJECT s7false)
{
  Array<int>ints;
  Array<double>flos;
  StringArray strs;
  
  SCHEMEOBJECT p;
  int len=0;
  String types=String::empty;
  for (p=list; s7_is_pair(p); p=s7_cdr(p))
    {
      SCHEMEOBJECT x=s7_car(p);
      char t=0;
      if (s7_is_keyword(x))
        {
          String s (s7_symbol_name(x));
          if (s.length()==2 && String("ifsbhtdScmTFNI").containsChar(s[1]))
            {
              types << s[1];
              if (String("TFNI").containsChar(s[1]))
                continue;
              p=s7_cdr(p);
              if (s7_is_pair(p))
                x=s7_car(p);
              else
                return -3;
              t=s[1];
            }
          else
            return -2;
        }
      if (s7_is_integer(x))
        {
          s7_Int i=s7_integer(x);
          switch (t)
            {
            case 0 :
              types << T("i");
            case 'i' :
            case 'h' :
              ints.add(i);
              break;
            case 't' :
              flos.add((double)i);
              break;
            default:
              return -5;
            }
        }
      else if (s7_is_real(x))
        {
          s7_Double d = s7_real(x);
          switch (t)
            {
            case 0 :
              types << T("f");
            case 'd' :
            case 't' :
            case 'f' :
              flos.add((double)d);
              break;
            default:
              return -5;
            }            }
      else if (s7_is_string(x))
        {
          const char* s=s7_string(x);
          switch (t)
            {
            case 0 :
              types << T("s");
            case 's' :
            case 'S' :
              strs.add(String(s));
              break;
            default:
              return -5;
            }
        }
      else if (s7_is_symbol(x))
        {
          const char* s=s7_symbol_name(x);
          switch (t)
            {
            case 0 :
              types << T("S");
            case 'S' :
            case 's' :
              strs.add(String(s));
              break;
            default:
              return -5;
            }           
        }
      else if (s7_is_character(x))
        {
          char c=s7_character(x);
          switch (t)
            {
            case 0 :
              types << T("c");
            case 'c' :
              strs.add(String(c));
              break;
            default:
              return -5;
            }
        }
      else if (s7_is_boolean(x))
        {
          if (t!=0) return -5;
          if (x==s7false)
            types<<T("F");
          else
            types<<T("T");
        }          
      else if (s7_is_pair(x))
        {
          if (t=='m')
            {
              int j=0;
              SCHEMEOBJECT m;
              for (m=x; s7_is_pair(m); m=s7_cdr(m), j++)
                if (s7_is_integer(s7_car(m)))
                  {
                    juce::uint32 x=(juce::uint32)s7_integer(s7_car(m));
                    ints.add(x & 0xff);
                  }
                else 
                  return -5;
              if (j!=4)
                return -5;
            }
          else if (t=='b')
            {
              // blobs are stored: [size data...]
              int i=ints.size();
              int j=0;
              ints.add(j);
              SCHEMEOBJECT m;
              for (m=x; s7_is_pair(m); m=s7_cdr(m), j++)
                if (s7_is_integer(s7_car(m)))
                  {
                    juce::uint32 x=(juce::uint32)s7_integer(s7_car(m));
                    ints.add(x & 0xff);
                  }
                else 
                  return -5;
              ints.setUnchecked(i,j);
            }
          else
            return -5;
        }
      else
        {
          //std::cout << "osc_send: aborting on unknown message value\n";
          return -5;
        }
    }
  return OscPort::getInstance()->sendMessage(path,types,ints,flos,strs,-1);
}

#else
int osc_open(char* port, char* targ){return -1;}
bool osc_open_p(){return false;}
int osc_close(){return -1;}
int osc_send(char* path, SCHEMEOBJECT alist, SCHEMEOBJECT scmfalse){return -1;}
void osc_set_hook(bool hook){}
#endif
