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
#include "Fomus.h"
#include "Console.h"
#include "Syntax.h"

#define POWF(a,b)	(powf( (a) , (b) ))
#define LOGF(a)		(logf( (a) ))
#define EXPF(a)		(expf( (a) ))
#define SQRTF(a)	(sqrtf( (a) ))
#define TANF(a)		(tanf( (a) ))

#ifdef _MSC_VER
double log2(double n)
{
  return log(n)/log(2.0);
}

int round(double n)
{
  return (int)(n+.5);
}
#endif

void cm_quit()
{
  Scheme::getInstance()->signalThreadShouldExit();
  Scheme::getInstance()->notify();
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
  // normalize errors so they start with ">>> Error:" and end with
  // crlf.
  //  String err=String(str);
  //  if (!err.startsWith(T(">>> Error:")))
  //   err=T(">>> KoKoError: ") + err;
  // if (!err.endsWith(T("\n")))
  //   err << T("\n");
  Console::getInstance()->printError(str);
}

void cm_print_values(char* str)
{
  Console::getInstance()->printValues(str);
}

void cm_shell(char* str)
{
  system(str);
}

void cm_play(char* str)
{
  String path=String(str);
  File file=File(path);
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
  String vers=String("Common Music ");
  int n=CM_VERSION, a=0, b=0, c=0;
  a=n / 100;
  n=n % 100;
  b=n / 10;
  c=n % 10;
  vers << String(a) << T(".") << String(b) << T(".") + String(c);
  return vers ;
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

double cm_cents_to_scaler(int cents)
{
  double p = ((double)cents)/1200.0f;
  return POWF(2.0f,p);
}

int cm_scaler_to_cents(double scaler)
{
  return round((LOGF(scaler)/LOGF(2.0)) * 1200.0);
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
  File dir=File(String(path));
  if (! dir.isDirectory())
    return false;
  dir.setAsCurrentWorkingDirectory();
  return true;
}

char* cm_pathname_name(char* path)
{

  File f=File(String(path));
  String s=f.getFileNameWithoutExtension();
  return (char *)strdup(s.toUTF8());
}

char* cm_pathname_type(char* path)
{
  File f=File(String(path));
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
  File f=File(String(path));
  String s=f.getFullPathName();
#ifdef WINDOWS
  s=s.replaceCharacter('\\','/');
#endif
  return (char *)strdup(s.toUTF8());
}

bool cm_pathname_exists_p(char* path)
{
  File f=File(String(path));
  return f.exists();
}

bool cm_pathname_writable_p(char* path)
{
  File f=File(String(path));
  return f.hasWriteAccess();
}

bool cm_pathname_directory_p(char* path)
{
  File f=File(String(path));
  return f.isDirectory();
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

void fms_new()
{
  Fomus::getInstance()->newScore();
}

void fms_free()
{
  Fomus::getInstance()->deleteScore();
}

void fms_clear()
{
  Fomus::getInstance()->clearScore();
}

void fms_init()
{
  Fomus::getInstance()->initScore();
}

void fms_load(char* filename)
{
  Fomus::getInstance()->loadScore(String(filename));
}

void fms_run()
{
  Fomus::getInstance()->runScore();
}

void fms_xml(char* str)
{
  //XmlElement xml=XmlElement(String(str));
  //Fomus::getInstance()->sendXml(xml);
  Fomus::getInstance()->sendXml(String(str));
}  

void fms_ival(int par, int act, int val)
{
  Fomus::getInstance()->ival(par,act,val);
}

void fms_rval(int par, int act, int num, int den)
{
  Fomus::getInstance()->rval(par,act,num,den);
}

void fms_mval(int par, int act, int val, int num, int den)
{
  Fomus::getInstance()->mval(par,act,val,num,den);
}

void fms_fval(int par, int act, double val)
{
  Fomus::getInstance()->fval(par,act,val);
}

void fms_sval(int par, int act, char* val)
{
  Fomus::getInstance()->sval(par,act,String(val));
}

void fms_act(int par, int act)
{
  Fomus::getInstance()->act(par,act);
}

