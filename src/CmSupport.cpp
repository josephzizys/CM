/*=======================================================================*
  Copyright (C) 2008-2010 Rick Taube.                                        
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
#include "SndLib.h"
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
  SchemeThread::getInstance()->quit();
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

void cm_print_markov_table(s7_pointer table, s7_pointer labels, int field, int rowLabelWidth)
{
  s7_scheme* sc=SchemeThread::getInstance()->scheme;
  String sp (" ");
  String ln;
  String port ("\n");
  for (int i=0; i<field; i++) ln<<T("-");
  for (int i=0; i<rowLabelWidth; i++) port << T("*");
  for (s7_pointer p=labels; s7_is_pair(p); p=s7_cdr(p))
    {
      port << sp;
      String s=String((char*)s7_object_to_string(sc, s7_car(p), true));
      int n=s.length();
      // write column pad
      for (int i=0, m=jmax(field-n, 0); i<m; i++) port << sp; // col separator
      port << s;
    }
  // print each row
  for (s7_pointer tail=table; s7_is_pair(tail); tail=s7_cdr(tail))
    {
      s7_pointer row=s7_car(tail);
      port << T("\n");
      String s; // liststring 
      s7_pointer l=s7_car(tail);
      if (l==s7_nil(sc))
        s<<T("");
      else
        {
        }

    }
}

void cm_prin1(s7_scheme* sc, s7_pointer ptr, bool sal, bool quo, String& str)
{
  if (ptr==s7_f(sc))
    {
      str << T("#f");
    }
  else if (ptr==s7_nil(sc))
    {
      if (sal) str << T("{}"); else str << T("()");
    }
  else if (s7_is_pair(ptr))
    {
      if (sal) str << T("{"); else str << T("(");
      for (s7_pointer p=ptr; s7_is_pair(p); p=s7_cdr(p))
        {
          if (p!=ptr)
            str<<T(" ");
          cm_prin1(sc, s7_car(p), sal, true, str);
        }
      if (sal) str << T("}"); else str << T(")");
    }
  else if (ptr==s7_t(sc))
    str << T("#t");
  else if (s7_is_number(ptr))
    str << String(s7_number_to_string(sc, ptr, 10));
  else if (s7_is_string(ptr))
    {
      if (quo)
        str << String(s7_string(ptr)).quoted();
      else
        str << String(s7_string(ptr));
    }
  else
    str << String(s7_object_to_c_string(sc, ptr));
}

s7_pointer cm_print(s7_pointer args)
{
  bool sal=SchemeThread::getInstance()->isSalEval();  // true if we are under a salEval
  s7_scheme* sc=SchemeThread::getInstance()->scheme;
  String text=String::empty;
  while (s7_is_pair(args))
    {
      cm_prin1(sc, s7_car(args), sal, false, text);
      args=s7_cdr(args);
    }
  text << T("\n");
  Console::getInstance()->printOutput(text);
  return s7_unspecified(sc);
}

/*=======================================================================*
 *=======================================================================*/

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

void cm_load(char *path)
{
  String name (path);
  File file=completeFile(name);
  if (file.hasFileExtension(T(".sal")) || file.hasFileExtension(T(".sal2")))
    {
      sal_load(path);
    }
  else
    {
#ifdef GRACE
      // allow embedded instrument files to be loaded if (1) the file
      // name has no directory component, (2) *load-path* is null and
      // (3) the file does not exist
      XmlElement* ins=NULL;
      if (
          // no directory component
          (! name.containsAnyOf(File::separatorString))
          // file does not exist
          && (! file.existsAsFile())
          // no load path set
          && (s7_load_path(SchemeThread::getInstance()->scheme) == SchemeThread::getInstance()->schemeNil)
          // is embedded instrument
          && ((ins=SndLib::getInstance()->getInstrumentElement(name)) != NULL)
          ) 
        {
          String str=SndLib::getInstance()->getInstrumentCode(name);
          s7_eval_c_string(SchemeThread::getInstance()->scheme, str.toUTF8());
          ins->setAttribute(T("Loaded"), "yes");
        }
      else
#endif
        s7_load (SchemeThread::getInstance()->scheme,path);
    }
}

void cm_edit(char *path)
{
  // REMOVE
}

/*=======================================================================*
 *=======================================================================*/

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
      return y1 + ( ( (y2 - y1) / (b - 1.0)) * (pow(b, p) - 1.0)); // POWF
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
  return (double) ((beats / beat) * (60.0 / tempo)) ;
}

double cm_cents_to_scaler(double cents)
{
  double p = cents/1200.0;
  return pow(2.0,p); //POWF
}

double cm_scaler_to_cents(double scaler)
{
  return (log(scaler)/log(2.0)) * 1200.0; // LOGF
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

static const double A00 = 6.875;   // keynum 0

double cm_hertz_to_keynum (double hz)
{
  // subtract 3 shifts to A
  return (((log(hz) - log(A00) ) / log(2.0)) * 12.0) - 3; // LOGF
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

void cm_ranseed(int64 s)
{
  ranstate.setSeed(s);
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
  return (ranstate.nextDouble() + ranstate.nextDouble()) / 2.0;
}

double cm_ranbeta (double a, double b)
{
  double ra=1.0/a, rb=1.0/b, r1, r2, y1, y2, sum;
  while (true) {
    r1 = ranstate.nextDouble();
    r2 = ranstate.nextDouble();
    y1 = pow(r1,ra); //POWF
    y2 = pow(r2,rb); //POWF
    sum=y1+y2;
    if ( sum <= 1.0) return (y1 / sum);
  }
}

double cm_ranexp (double lambda)
{
  return (- log(1.0 - ranstate.nextDouble())) / lambda; // LOGF
}

double cm_ranexp2 (double lambda)
{
  double ee = (2 * exp(-1.0)); // EXPF
  double u, v;
  while ( true ) {
    u = 1.0 - ranstate.nextDouble();
    v = ee * ranstate.nextDouble();
    if ( v <= (ee * u * log(u)) ) //LOGF
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
  return (sigma * y * sqrt(-2.0 * log(r2) / r2))+mu; //SQRTF LOGF
}

double cm_rancauchy()
{
  return(tan(juce::double_Pi*(ranstate.nextDouble() - 0.5))); //TANF
}

int cm_ranpoisson (double lambda)
{
  double b = exp( - lambda); // EXPF
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
  return - log(r); //LOGF
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
      double p = pow(2.0, i); //POWF
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
      if (b<-16.0 || b>16.0) b -= r;
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

void cm_sched_sprout(s7_pointer proc, double time, int id)
{
  // if score capture is true AND we are under a process callback then
  // scoretime will be >= 0 else it will be 0
  SchemeThread* scm=SchemeThread::getInstance();
  // if (scm->scoremode)
  //    time=time+scm->scoretime;
  scm->sprout(time, proc, id);
}

bool cm_sched_paused_p()
{
  return SchemeThread::getInstance()->isPaused();
}

void cm_sched_pause() 
{
  SchemeThread::getInstance()->setPaused(true);
}

void cm_sched_continue()
{
  SchemeThread::getInstance()->setPaused(false);
}

void cm_sched_stop(int id)
{
  SchemeThread::getInstance()->stop(id);
}

void cm_sched_hush() 
{
  SchemeThread::getInstance()->stop(-1);
}

bool cm_sched_busy_p()
{
  //return !SchemeThread::getInstance()->isQueueEmpty();
  return SchemeThread::getInstance()->sprouted;
}

void cm_sched_set_score_mode(int val)
{
  // this must only be called if scheduler is empty!
  SchemeThread::getInstance()->setScoreMode(val);
}

bool cm_sched_score_mode_p()
{
  return SchemeThread::getInstance()->isScoreMode();
}

double cm_sched_score_time()
{
  // should only be called under score mode
  return SchemeThread::getInstance()->getScoreTime();
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
  String string=String(path);
#ifdef WINDOWS
  string=string.replaceCharacter(T('\\'),T('/'));
#endif
  // start of name is after the last '/' else 0
  int start=string.lastIndexOfChar(T('/')) + 1;
  // end of name is before the last '.' else length
  int end=string.lastIndexOfChar(T('.'));
  // name can start with dot (position 0)
  if (end<=0) end=string.length();
  if (start<end)
    return (char *)strdup(string.substring(start,end).toUTF8());
  else
    return (char *)NULL;
}

char* cm_pathname_type(char* path)
{
  String string=String(path);
#ifdef WINDOWS
  string=string.replaceCharacter('\\','/');
#endif
  // file type after the last '.' unless dot belongs to the name
  int start=string.lastIndexOfChar(T('.'));
  if ((start<=0) || string[start-1]==T('/'))
    return (char *)NULL;
  return (char *)strdup(string.substring(start+1).toUTF8());
}

char* cm_pathname_directory(char* path)
{
  String string=String(path);
#ifdef WINDOWS
  string=string.replaceCharacter(T('\\'),T('/'));
#endif
  int end=string.lastIndexOfChar(T('/'));
  if (end<0)
    return (char *)NULL;
  else 
    return (char *)strdup(string.substring(0,end+1).toUTF8());
}

char* cm_full_pathname(char* path)
{
  String string=completeFile(String(path)).getFullPathName();
#ifdef WINDOWS
  string=string.replaceCharacter(T('\\'),T('/'));
#endif
  return (char *)strdup(string.toUTF8());
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

s7_pointer cm_directory(char* path, bool recurse)
{
  File f=completeFile(String(path));
  s7_scheme* sc=SchemeThread::getInstance()->scheme;
  if (f.existsAsFile())
    return s7_cons(sc, s7_make_string(sc, f.getFullPathName().toUTF8()),
                   SchemeThread::getInstance()->schemeNil);
  String s;
  if (f.isDirectory())
    s=T("*");
  else if (f.existsAsFile())
    return s7_cons(sc, s7_make_string(sc,f.getFullPathName().toUTF8()),
                   SchemeThread::getInstance()->schemeNil);                     
  else if (String(path).containsChar('*'))
    {
      s=f.getFileName();
      f=f.getParentDirectory();
    }
  else
    return SchemeThread::getInstance()->schemeNil;

  Array<File> a;
  int i=(recurse) ? File::findFiles : File::findFilesAndDirectories;
  int n=f.findChildFiles(a, (i | File::ignoreHiddenFiles), recurse, s);
  if (n==0)
    return SchemeThread::getInstance()->schemeNil;
  s7_pointer head=s7_cons(sc, s7_make_string(sc, a[0].getFullPathName().toUTF8()),
                          SchemeThread::getInstance()->schemeNil);
  s7_pointer tail=head;
  for (int j=1; j<n; j++)
    {
      String x=a[j].getFullPathName();
      s7_set_cdr(tail, s7_cons(sc, s7_make_string(sc, x.toUTF8()),
                               SchemeThread::getInstance()->schemeNil));
      tail=s7_cdr(tail);
    }  
  return head;
}

int cm_pathname_to_key(char* path)
{
  // parse filename for a note or key number at the end. returns
  // keynum or -1

  String name=String(path);
  // ignore file extension if it exists
  int len=name.lastIndexOfChar('.');
  if (len<0)
    len=name.length();
  String letts=String(T("AaBbCcDdEeFfGg#Ss"));
  String digis=String(T("0123456789"));
  int pos;
  bool let=false;
  // parse backwards as long as constituent is keynum or note name
  for (pos=len-1; pos>=0; pos--)
    {
      if (letts.containsChar(name[pos]))
        let=true; // have a note name letter
      else if (digis.containsChar(name[pos]))
        { // digit not constituent if note name reached
          if (let)
            break;
        }
      else
        break;
    }
  // pos now at end or start of possible note/keynum
  pos++;
  // set name to substring of possible note portion
  if (pos<len)
    name=name.substring(pos,len);
  else
    return -1;
  // name can be just a key number
  if (name.containsOnly(digis))
    return name.getIntValue();
  // otherwise a note must have a least a pitch class and octave
  if (name.length()<2)
    return -1;
  pos=0;
  int pc=0;
  // parse out required case-insensitive note name
  switch (name[pos])
    {
    case 'c': case 'C': pc=0;  break;
    case 'd': case 'D': pc=2;  break;
    case 'e': case 'E': pc=4;  break;
    case 'f': case 'F': pc=5;  break;
    case 'g': case 'G': pc=7;  break;
    case 'a': case 'A': pc=9;  break;
    case 'b': case 'B': pc=11; break;
    default: return -1;
    }
  pos++;
  // parse out optional case-insensitive accidental
  switch (name[pos])
    {
    case '#': case 's': case 'S': pc++; pos++; break;      
    case 'b': case 'f': case 'F': pc--; pos++; break;
    }
  // remainder of name must be octave token
  name=name.substring(pos,len);
  if (name==T("00"))
    return pc;
  else if (name==T("0"))
    return pc + 12;
  else if (name==T("1"))
    return pc + 24;
  else if (name==T("2"))
    return pc + 36;
  else if (name==T("3"))
    return pc + 48;
  else if (name==T("4"))
    return pc + 60;
  else if (name==T("5"))
    return pc + 72;
  else if (name==T("6"))
    return pc + 84;
  else if (name==T("7"))
    return pc + 96;
  else if (name==T("8"))
    return pc + 108;
  else if (name==T("9") && (pc < 8))
    return pc + 120;
  else
    return -1;
}

/*=======================================================================*
                                  SAL Support
 *=======================================================================*/

s7_pointer sal_allocate_tokens()
{
  s7_scheme* sc=SchemeThread::getInstance()->scheme;
  OwnedArray<Syntax::SynTok>* ary=new OwnedArray<Syntax::SynTok>;
  return s7_make_c_pointer(sc, ary);
}

s7_pointer sal_free_tokens(s7_pointer ptr)
{
  s7_scheme* sc=SchemeThread::getInstance()->scheme;
  OwnedArray<Syntax::SynTok>* ary=(OwnedArray<Syntax::SynTok>*)s7_c_pointer(ptr);
  delete ary;
  return s7_unspecified(sc);
}

s7_pointer sal_tokenize_string(s7_pointer str, s7_pointer ptr,  s7_pointer sal2)
{
  // str is the lisp string 
  String text (s7_string(str));
  // ptr is a C-pointer to an  OwnedArray<Syntax::SynTok>
  s7_scheme* sc=SchemeThread::getInstance()->scheme;
  OwnedArray<Syntax::SynTok>* ary=(OwnedArray<Syntax::SynTok>*)s7_c_pointer(ptr);
  // convert array to lisp list of C tokens  
  s7_pointer toks=SchemeThread::getInstance()->schemeNil;
  bool ok=false;

  //  //  if (s7_boolean(sc, sal2))
  //  //    {
  //  //    ok=Sal2Syntax::getInstance()->tokenize(text, *ary);
  //  //    }
  //  //  else
  //  //    ok=SalSyntax::getInstance()->tokenize(text, *ary);

  if (ok)
    {
      for (int i=ary->size()-1; i>=0; i--)
        toks=s7_cons(sc, s7_make_c_pointer(sc, ary->getUnchecked(i)), toks);
    }
 
  return toks;
}

s7_pointer sal_tokenize_file(s7_pointer fil, s7_pointer ptr, s7_pointer sal2)
{
  // fil is the lisp string holding a valid pathname
  // ptr is the C-pointer to an allocated OwnedArray<Syntax::SynTok>
  File file (String(s7_string(fil)));  // read sal file 
  String text=T("begin\n"); // wrap text in begin...end
  text << file.loadFileAsString()
       << T("\nend");
  s7_scheme* sc=SchemeThread::getInstance()->scheme;
  OwnedArray<Syntax::SynTok>* ary=(OwnedArray<Syntax::SynTok>*)s7_c_pointer(ptr);
  // convert array to lisp list of C tokens  
  s7_pointer toks=SchemeThread::getInstance()->schemeNil;
  bool ok=false;

  //  //  if (s7_boolean(sc, sal2))
  //  //    ok=Sal2Syntax::getInstance()->tokenize(text, *ary);
  //  //  else
  //  //    ok=SalSyntax::getInstance()->tokenize(text, *ary);

  if (ok)
    {
      for (int i=ary->size()-1; i>=0; i--)
        toks=s7_cons(sc, s7_make_c_pointer(sc, ary->getUnchecked(i)), toks);
      // sigh. return input string as first arg
      toks=s7_cons(sc, s7_make_string(sc, text.toUTF8()), toks);
    }
  return toks;
}

s7_pointer sal_load(char* path)
{
  // sal_load is always called under a scheme function and the file
  // type is guaranteed to be either .sal or .sal2
  String name (path);
  File file=completeFile(name);
  if (! file.existsAsFile())
    {
      SchemeThread::getInstance()->signalSchemeError(T("load: file does not exist: ") + file.getFullPathName());
    }
  String text=file.loadFileAsString();
  if (text.isEmpty())
    {
      SchemeThread::getInstance()->signalSchemeError(T("load: file is empty: ") + file.getFullPathName());
      //return SchemeThread::getInstance()->schemeFalse;
    }
  int type=TextIDs::fromFileType(file.getFileExtension());
  if (type==TextIDs::Sal)
    {
      // for a .sal file we have to check if custom comment has syntax
      String firstline=text.upToFirstOccurrenceOf(T("\n"), false, false);
      if (firstline[0]==T(';') && firstline.contains(T("-*-")))
        {
          firstline=firstline.fromFirstOccurrenceOf(T("syntax:"), false, true).trimStart();
          if (firstline.substring(0,4).equalsIgnoreCase(T("sal2")))
            type=TextIDs::Sal2;
        }
    }
  sal_eval(text, type);
  return SchemeThread::getInstance()->schemeVoid;
}

s7_pointer sal_eval(String text, int type)
{
  OwnedArray<Syntax::SynTok> tokens;
  s7_scheme* sc=SchemeThread::getInstance()->scheme;
  s7_pointer func;
  if (type==TextIDs::Sal)
    {
      std::cout << "load type=sal\n";
      if (!SalSyntax::getInstance()->tokenize(text, tokens))
        {
          tokens.clear();
          SchemeThread::getInstance()->signalSchemeError(SalSyntax::getInstance()->getLastParseError());
        }
      func=s7_name_to_value(sc, "sal");
    }
  else
    {
      std::cout << "load type=sal2\n";
      if (!Sal2Syntax::getInstance()->tokenize(text, tokens))
        {
          tokens.clear();
          SchemeThread::getInstance()->signalSchemeError(Sal2Syntax::getInstance()->getLastParseError());
        }
      func=s7_name_to_value(sc, "sal2");
    }
  // convert tokens to list
  s7_pointer toks=SchemeThread::getInstance()->schemeNil;
  for (int i=tokens.size()-1; i>=0; i--)
    toks=s7_cons(sc, s7_make_c_pointer(sc, tokens.getUnchecked(i)), toks);
  // ("string", (tokens...), false, true)
  s7_pointer args=s7_cons(sc, 
                          s7_make_string(sc, text.toUTF8()),
                          s7_cons(sc,
                                  toks,
                                  s7_cons(sc,
                                          SchemeThread::getInstance()->schemeFalse,
                                          s7_cons(sc,
                                                  SchemeThread::getInstance()->schemeTrue,
                                                  SchemeThread::getInstance()->schemeNil))));
  return s7_call(sc, func, args);
}


s7_pointer sal_token_type(s7_pointer ptr)
{
  Syntax::SynTok* tok=(Syntax::SynTok*)s7_c_pointer(ptr);
  return s7_make_integer(SchemeThread::getInstance()->scheme, tok->getType());
}

s7_pointer sal_token_string(s7_pointer ptr)
{
  Syntax::SynTok* tok=(Syntax::SynTok*)s7_c_pointer(ptr);
  return s7_make_string(SchemeThread::getInstance()->scheme, tok->getName().toUTF8());
}

s7_pointer sal_token_position(s7_pointer ptr)
{
  Syntax::SynTok* tok=(Syntax::SynTok*)s7_c_pointer(ptr);
  return s7_make_integer(SchemeThread::getInstance()->scheme, tok->getData1());
}

/*
 * port information
 */

char* cm_port_info()
{
  // return a string that SchemeThread can (read) to create a list
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

void mp_open_score(char* path, s7_pointer args)
{
  // args is () or a list of keyword options
  MidiOutPort::getInstance()->performCommand(CommandIDs::MidiSeqSetFile, 0, String(path));
}

void mp_close_score()
{
  MidiOutPort::getInstance()->performCommand(CommandIDs::SchedulerScoreComplete);
}

void mp_send_note(double time, double dur, double key, double vel, double chn) 
{
  SchemeThread* scm=SchemeThread::getInstance();
  if (scm->scoremode)
    {
      // if score capture is true AND we are under a process callback then
      // scoretime will be >= 0 else it will be 0
      time+=scm->scoretime;
      MidiOutPort::getInstance()->sendNote(time, dur, key, vel, chn, true);
      //std::cout << "sending score mode " << time << " " << key << "\n";
    }
  else
    MidiOutPort::getInstance()->sendNote(time, dur, key, vel, chn, false);
}

void mp_send_data(int type, double time, double chan, 
		  double data1, double  data2)
{
  SchemeThread* scm=SchemeThread::getInstance();
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

void mp_set_instruments(s7_pointer list)
{
  MidiOutPort* port=MidiOutPort::getInstance();
  SchemeThread* scm=SchemeThread::getInstance();
  for (int chan=0; s7_is_pair(list) && chan<16; list=s7_cdr(list), chan++)
    if (s7_is_integer(s7_car(list)))
      port->setInstrument(chan, (int)s7_integer(s7_car(list)) & 0x7f);      
    else if (s7_car(list) == scm->schemeFalse)
      ;
    else if (s7_is_string(s7_car(list)) || s7_is_symbol(s7_car(list)))
      {
        String name=(s7_is_string(s7_car(list))) ? String(s7_string(s7_car(list))) : String(s7_symbol_name(s7_car(list)));
        int prog=-1;
        for (int i=0; i<128 && prog==-1; i++)
          if (port->instrumentnames[i].containsIgnoreCase(name))
            prog=i;
        if (prog==-1)
          scm->signalSchemeError(T("mp:instruments: not an instrument name: ") + name);
        else 
          port->setInstrument(chan, prog);      
      }
    else
      scm->signalSchemeError(T("mp:instruments: not a valid program change: ") + 
                             String(s7_object_to_c_string(scm->scheme, s7_car(list))));
  port->sendInstruments();
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


s7_pointer getMidiValue(s7_scheme* sc, MidiMessageSequence::MidiEventHolder* hold, int midival, int opcode, 
                        double lasttime, double lastontime)
{
  switch (midival)
    {
    case MidiValues::MidiValueTime:
      return s7_make_real(sc, hold->message.getTimeStamp());
    case MidiValues::MidiValueDelta:
      return s7_make_real(sc, hold->message.getTimeStamp() - lasttime);
    case MidiValues::MidiValueOp:
      return s7_make_integer(sc, opcode);
    case MidiValues::MidiValueRhythm:
      return s7_make_real(sc, hold->message.getTimeStamp() - lastontime);
    case MidiValues::MidiValueDuration:
      if (hold->noteOffObject)
        return s7_make_real(sc, hold->noteOffObject->message.getTimeStamp() - hold->message.getTimeStamp());
      else // no dur if no paired off
        return SchemeThread::getInstance()->schemeFalse;
    case MidiValues::MidiValueKeyNumber:
      return s7_make_integer(sc, hold->message.getNoteNumber());
    case MidiValues::MidiValueAmplitude:
      return s7_make_real(sc, hold->message.getFloatVelocity());
    case MidiValues::MidiValueVelocity:
      return s7_make_integer(sc, hold->message.getVelocity());
    case MidiValues::MidiValueChannel:
      return s7_make_integer(sc, hold->message.getChannel()-1);
    case MidiValues::MidiValueTouch:
      return s7_make_integer(sc, hold->message.getAfterTouchValue());
    case MidiValues::MidiValueControlNumber:
      return s7_make_integer(sc, hold->message.getControllerNumber());
    case MidiValues::MidiValueControlValue:
      return s7_make_integer(sc, hold->message.getControllerValue());
    case MidiValues::MidiValueProgram:
      return s7_make_integer(sc, hold->message.getProgramChangeNumber());
    case MidiValues::MidiValuePressure:
      return s7_make_integer(sc, hold->message.getChannelPressureValue());
    case MidiValues::MidiValueBend:
      return s7_make_integer(sc, hold->message.getPitchWheelValue());
    case MidiValues::MidiValueSeqNum:
      {
        int num = -1;
        const uint8* data=hold->message.getMetaEventData();
        if (hold->message.getMetaEventLength()==2)
          num=(int)((data[0]<<8)+data[1]);
        return s7_make_integer(sc, hold->message.getPitchWheelValue());
      }
    case MidiValues::MidiValueText:
      return s7_make_string(sc, hold->message.getTextFromTextMetaEvent().toUTF8());
    case MidiValues::MidiValueChanPrefix:
      return s7_make_integer(sc, hold->message.getMidiChannelMetaEventChannel());
    case MidiValues::MidiValueTempo:
      return s7_make_real(sc, hold->message.getTempoSecondsPerQuarterNote());
    case MidiValues::MidiValueTimeSig:
      {
        int num, den;
        hold->message.getTimeSignatureInfo(num, den);
        return s7_cons(sc, s7_make_integer(sc, num),
                       s7_cons(sc, s7_make_integer(sc, den),
                               SchemeThread::getInstance()->schemeNil));
      }
    case MidiValues::MidiValueKeySig:
      return s7_make_integer(sc, hold->message.getKeySignatureNumberOfSharpsOrFlats());
    default:
      return SchemeThread::getInstance()->schemeFalse;
    }
}

s7_pointer cm_midifile_import(char* path, int track, s7_pointer midivalues)
{
  s7_scheme* scheme=SchemeThread::getInstance()->scheme;
  String name (path);
  File file=completeFile(name);
  if (!file.existsAsFile())
    SchemeThread::getInstance()->signalSchemeError(T("midifile-import: file does not exist: ") + 
                                                   file.getFullPathName());
  FileInputStream* input=file.createInputStream();
  MidiFile midifile;
  midifile.readFrom(*input);
  int numtracks=midifile.getNumTracks();
  if (numtracks<1) 
    SchemeThread::getInstance()->signalSchemeError(T("midifile-import: not a valid midifile: ") + 
                                                   file.getFullPathName());
  if (track<0 || track>=numtracks)
    SchemeThread::getInstance()->signalSchemeError(T("midifile-import: not a valid track: ") + 
                                                   String(track));
  int format=midifile.getTimeFormat();
  // get the track's midi data
  MidiMessageSequence* seq=(MidiMessageSequence*)midifile.getTrack(track);
  seq->updateMatchedPairs();
  // juce time format is postive for beats and negative for SMTPE
  if (format>0)
    midifile.convertTimestampTicksToSeconds();    
  else
    {
      // convert SMPTE ticks to seconds. The juce function
      // convertTimestampTicksToSeconds doesnt seem to work for SMPTE
      // ticks.
      int tpf=format & 0xFF;
      // juce smpte frames per second is negative upper byte
      int fps=0xFF-((format & 0xFF00) >> 8)+1;
      double smptetps=fps*tpf; // smpte ticks per second
      for (int i=0; i<seq->getNumEvents(); i++)
        {
          MidiMessageSequence::MidiEventHolder* h=seq->getEventPointer(i);
          h->message.setTimeStamp(h->message.getTimeStamp()/smptetps);
        }
    }

  // format of values list: 1=single value, 2=multiple values, 3=list
  // of lists eg: ("op"), ("op" "key") (("op" "key") ("op" "bend"))
  format=1;
  if (s7_is_pair(s7_car(midivalues)))
    format=3;
  else if (s7_list_length(scheme, midivalues)>1)
    format=2;
  // transfer midi values to array
  Array<int> vals;
  // if not format 3 then load the array just one time
  if (format<3)
    {
      for (s7_pointer p=midivalues; s7_is_pair(p); p=s7_cdr(p))
        vals.add((int)s7_integer(s7_car(p)));
    }
  // initialize return list for rplacd value appending
  s7_pointer empty=SchemeThread::getInstance()->schemeNil;
  s7_pointer head=s7_cons(scheme, SchemeThread::getInstance()->schemeFalse, empty);
  s7_pointer tail=head;  // tail now: (#f)
  double lasttime=0.0;
  double lastontime=0.0;
  // map all events in track
  for (int i=0; i<seq->getNumEvents(); i++)  
    {
      MidiMessageSequence::MidiEventHolder* e=seq->getEventPointer(i);
      int op=-1;
      // only handle channel or meta messages. get the midi opcode of
      // the event. for channel events opcode is in the upper nibble
      // of the status byte
      if (e->message.getChannel()>0)
        op=(e->message.getRawData()[0] & 0xF0)>>4;
      else if (e->message.isMetaEvent())
        op=e->message.getMetaEventType();
      else 
        continue;

      s7_pointer top=midivalues; // top only used by format 3
      // if format 3 set pointer to start of midivals and load the
      // vals array with the first sublist
      if (format==3)
        {
          vals.clear();
          // first values list is car of top
          for (s7_pointer p=s7_car(top); s7_is_pair(p); p=s7_cdr(p))
            vals.add((int)s7_integer(s7_car(p)));
          top=s7_cdr(top); // increment top
        }
      // process all the midivalues for the current message. if format
      // is 1 or 2 then this loop happens only one time
      while (true)
        {
          // check that all values are applicable to the current message.
          bool ok=true;
          for (int j=0; j<vals.size() && ok; j++) //((j<vals.size()) && (op > -1))
            if (!MidiValues::isOpForValue(vals[j], op))
              ok=false;
          // if all the values match then process them and add to return list
          if (ok)
            {
              //std::cout << "event [" << i << "] op=" << op << " values are applicable\n";
              s7_pointer add=NULL;
              if (format==1)
                add=getMidiValue(scheme, e, vals[0], op, lasttime, lastontime);
              else
                {
                  // process vals in reverse order to cons up adds
                  add=empty;
                  for (int j=vals.size(); --j>=0; )
                    add=s7_cons(scheme, getMidiValue(scheme, e, vals[j], op, lasttime, lastontime), add);
                }
              // add the new value (or list of values) onto tail.
              s7_set_cdr(tail, s7_cons(scheme, add, empty));
              tail=s7_cdr(tail);
            }
          // if just single value list or no more lists then quit loop
          // and move to next message
          if (format<3 || top == empty)
            break;
          // else format is 3 and more lists to process, increment to next values list
          vals.clear();
          // next values is car of top
          for (s7_pointer p=s7_car(top); s7_is_pair(p); p=s7_cdr(p))
            vals.add((int)s7_integer(s7_car(p)));
          top=s7_cdr(top);  // increment top 
        }

      lasttime=e->message.getTimeStamp();
      if (op==0x9)
        lastontime=lasttime;
    }
  return s7_cdr(head);
}

s7_pointer cm_midifile_header(char* path, s7_pointer midivalues)
{
  s7_scheme* scheme=SchemeThread::getInstance()->scheme;
  String name (path);
  File file=completeFile(name);
  if (!file.existsAsFile())
    SchemeThread::getInstance()->signalSchemeError(T("File does not exist: ") + file.getFullPathName());
  FileInputStream* input=file.createInputStream();
  MidiFile midifile;
  if (!midifile.readFrom(*input))
    SchemeThread::getInstance()->signalSchemeError(T("Invalid midi file: ") + file.getFullPathName());    
  int num=midifile.getNumTracks();
  if (num<1) 
    SchemeThread::getInstance()->signalSchemeError(T("Invalid midi file: ") + file.getFullPathName());
  // add num tracks
  s7_pointer head=s7_cons(scheme, s7_make_integer(scheme, num), s7_nil(scheme));
  s7_pointer data=head;
  // add time format (ticks/quarter or SMPTE)
  num=midifile.getTimeFormat();
  s7_set_cdr(data, s7_cons(scheme, s7_make_integer(scheme, num), s7_nil(scheme)));
  data=s7_cdr(data);
  // add tempo or #f
  MidiMessageSequence seq;
  midifile.convertTimestampTicksToSeconds();
  midifile.findAllTempoEvents(seq);
  if (seq.getNumEvents()>0)
    s7_set_cdr(data, s7_cons(scheme, s7_make_real(scheme, seq.getEventPointer(0)->message.getTempoSecondsPerQuarterNote()), s7_nil(scheme)));
  else
    s7_set_cdr(data, s7_cons(scheme, s7_f(scheme), s7_nil(scheme)));
  data=s7_cdr(data);
  // add max time in file
  s7_set_cdr(data, s7_cons(scheme, s7_make_real(scheme, midifile.getLastTimestamp()), s7_nil(scheme)));
  data=s7_cdr(data);
  return head;
}

//
/// Midi Hooks
//

bool mp_set_midi_hook(int op, s7_pointer proc)
{
  SchemeThread* st=SchemeThread::getInstance();
  if (s7_is_procedure(proc))
    {
      st->clearMidiHook(op);
      st->addMidiHook(op,proc);
      return true;
    }  
  else if (st->clearMidiHook(op))
    return true;
  else
    return false;
}

s7_pointer mp_is_midi_hook(int op)
{
  // 0=default, nnn=op, -1=any
  SchemeThread* st=SchemeThread::getInstance();
  if (op<0) // -1==return a list of all receivers
    {
      // cons up result in reverse order  
      s7_pointer args=st->schemeNil;
      for (int i=MidiFlags::Bend; i>=MidiFlags::Off; i--)
        if (st->isMidiHook(i))
          args=s7_cons(st->scheme, s7_make_integer(st->scheme, i), args);
      if (st->isMidiHook(0))
        args=s7_cons(st->scheme, s7_make_integer(st->scheme, 0), args);
      return args;
    }
  else
    return (st->isMidiHook(op)) ? s7_make_integer(st->scheme, op) : st->schemeFalse;
}

// Csound support

void cs_open_score(char* args)
{
  //  std::cout << "cm_init_score " << args << "\n";
  Csound::getInstance()->initScore(String(args));
}

void cs_send_score(int typ, int num, double time, char* pars)
{
  //std::cout << "cs_send_score " << typ << " " << num << " "  << time << " " << pars << "\n";
  Csound::getInstance()->addToScore(typ,num,time,String(pars));
}

void cs_close_score()
{
  Csound::getInstance()->saveScore();
}

//
// FOMUS Support
//

#ifdef WITHFOMUS // defined(WITHFOMUS) && defined(GRACE)

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

// SAVE ME!
//   double now=(SchemeThread::getInstance()->scoremode) 
//     ? SchemeThread::getInstance()->scoretime : 0.0;
//   // if score capture is true AND we are under a process callback then
//   // scoretime will be >= 0 else it will be 0

void fms_ival(int par, int act, long val) {
  if (!check_fomus_exists()) return;
  Fomus::getInstance()->ival(par, act, val);
}
void fms_rval(int par, int act, long num, long den) {
  if (!check_fomus_exists()) return;
  Fomus::getInstance()->rval(par, act, num, den);
}
void fms_fval(int par, int act, double val) {
  if (!check_fomus_exists()) return;
  Fomus::getInstance()->fval(par, act, val);
}
void fms_sval(int par, int act, const char* val) {
  if (!check_fomus_exists()) return;
  Fomus::getInstance()->sval(par, act, val);
}
void fms_act(int par, int act) {
  if (!check_fomus_exists()) return;
  Fomus::getInstance()->act(par, act);
}

void fms_err() {
  if (!check_fomus_exists()) return;
  fomuserr = true;
}

void fms_open_score(bool run) {
  if (!check_fomus_exists()) return;
  Fomus::getInstance()->setrunwhendone(run);
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
  fomuserr = false;
  Fomus::getInstance()->clearScore();
}

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
void fms_open_score(bool x){}
void fms_close_score(){}
void fms_new(const char* name){}
void fms_select(const char* name) {}
void fms_free(){}
void fms_clear(){}
void fms_load(char* filename){}
void fms_run(){}
void fms_save(const char* name) {}
void fms_ival(int par, int act, long val) {}
void fms_rval(int par, int act, long num, long den) {}
void fms_fval(int par, int act, double val) {}
void fms_sval(int par, int act, const char* val) {}
void fms_act(int par, int act) {}
void fms_err() {}
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

void sw_draw(char* title, s7_pointer obj, int data1, int data2)
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
      s7_pointer p,x;
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
}

#else

void plot_xml(char* text){}
void plot_add_xml_points(char* title, char* points){}
char* plot_data(char* text, int layer) {return (char *)NULL;}

bool sw_open_from_xml(char* s){return false;}
void sw_draw(char* w, s7_pointer obj, int a, int b){}

#endif

/*=======================================================================*
                             Open Sound Control
 *=======================================================================*/

#ifdef LIBLO

void toTimeTag(double ahead, lo_timetag& tag)
{
  if (ahead==0.0)
    tag=LO_TT_IMMEDIATE;
  else
    {
      #define JAN_1970 0x83aa7e80    
      juce::uint64 millis=(juce::uint64)(Time::currentTimeMillis() + ((juce::int64)(ahead * 1000)));
      juce::uint64 seconds=millis/1000;
      juce::uint64 remain=millis-(seconds*1000); // remainder in milliseconds
      tag.sec = seconds + JAN_1970;
      tag.frac = remain * 4294967.295;
    }
}

int osc_open(char* port, char* targ)
{
  return OscPort::getInstance()->open(String(port), String(targ));
}

int osc_close()
{
  return OscPort::getInstance()->close();
}

bool osc_is_open()
{
  return OscPort::getInstance()->isOpen;
}

s7_pointer osc_set_hook(char* oscpath, s7_pointer proc)
{
  String path(oscpath);
  SchemeThread* st=SchemeThread::getInstance();
  if (s7_is_procedure(proc))
    {
      st->clearOscHook(path);
      st->addOscHook(path,proc);
      return st->schemeTrue;
    }  
  else if (st->clearOscHook(path))
    return st->schemeTrue;
  else
    return st->schemeFalse;
}

s7_pointer osc_is_hook(char* oscpath)
{
  // 0=default, nnn=op, -1=any
  String path(oscpath);
  SchemeThread* st=SchemeThread::getInstance();
  if (path==T("*")) // * == return list of all receivers
    {
      // cons up result in reverse order  
      s7_pointer args=st->schemeNil;
      for (int i=st->oscHooks.size()-1; i>=0; i--)
        {
          String p = st->oscHooks[i]->path;
          if (p.isEmpty()) // display default path as "/"
            p=T("/");
          args=s7_cons(st->scheme, s7_make_string(st->scheme, p.toUTF8()), args);
        }
      return args;
    }
  else
    return (st->isOscHook(path)) ? st->schemeFalse : st->schemeFalse;
}

static const int oscerr_incomplete_message = 1;
static const int oscerr_invalid_type = 2;
static const int oscerr_invalid_data = 3;
static const int oscerr_not_message = 4;

lo_message osc_make_message(s7_pointer pair, String& errstr)
{
  // return an Osc message or NULL on error. if the latter, errstr
  // will hold the error string to report
  lo_message msg=lo_message_new();
  s7_pointer p;
  int errn=0;  // zero is success
  String errs=String::empty;

  for (p=pair; s7_is_pair(p) && (errn==0); p=s7_cdr(p))
    {
      char t=0;                 // message type
      s7_pointer x=s7_car(p);   // message data
      if (s7_is_keyword(x))     // have explicit type tag
        {
          String s (s7_symbol_name(x));
          if (s.length()==2 && String("ifsbhtdScmTFNI").containsChar(s[1]))
            {
              // a few OSC tags have no data
              switch (s[1])
                {
                case LO_TRUE:
                  errn=lo_message_add_true(msg);
                  continue;
                case LO_FALSE:
                  errn=lo_message_add_false(msg);
                  continue;
                case LO_NIL:
                  errn=lo_message_add_nil(msg);
                  continue;
                case LO_INFINITUM:
                  errn=lo_message_add_infinitum(msg);
                  continue;
                }
              // otherwise get the tagged data
              p=s7_cdr(p);
              if (s7_is_pair(p))
                x=s7_car(p);
              else
                {
                  errn=oscerr_incomplete_message;
                  break;
                }
              t=s[1];
            }
          else
            {
              errs=s;
              errn=oscerr_invalid_type;
              break;
            }
        }
      // at this point we have datum in 'x' and (possibly) a type in
      // 't'. now add t and x to message, possibly including a default
      // type if it was not explicity specified by the user
      if (s7_is_integer(x))
        {
          s7_Int i=s7_integer(x);
          switch (t)
            {
            case 0:
            case LO_INT32:
              errn=lo_message_add_int32(msg, i);
              break;
            case LO_INT64:
              errn=lo_message_add_int64(msg, (int64)i);
              break;
            case LO_TIMETAG:
              {
                lo_timetag tag;
                toTimeTag((double)i, tag);
                errn=lo_message_add_timetag(msg, tag);
              }
              break;
            default:
              errs << t << T(" and ") << String(i);
              errn=oscerr_invalid_data;
              break;
            }
        }
      else if (s7_is_real(x))
        {
          s7_Double d = s7_real(x);
          switch (t)
            {
            case 0:
            case LO_FLOAT:
              errn=lo_message_add_float(msg, (float)d);
              break;
            case LO_DOUBLE:
              errn=lo_message_add_double(msg, (double)d);
              break;
            case LO_TIMETAG:
              {
                lo_timetag tag;
                toTimeTag(d,tag);
                errn=lo_message_add_timetag(msg, tag);
              }
              break;
            default:
              errs << t << T(" and ") << d;
              errn=oscerr_invalid_data;
              break;
            }   
        }
      else if (s7_is_string(x))
        {
          const char* s=s7_string(x);
          if (*s=='\0') // empty string
            {
              errs=String("\"\"");
              errn=oscerr_invalid_data;
              break;
            }
          switch (t)
            {
            case 0:
            case LO_STRING:
              errn=lo_message_add_string(msg, s);
              break;
            case LO_SYMBOL:
              errn=lo_message_add_symbol(msg, s);
              break;
            case LO_CHAR:
              errn=lo_message_add_char(msg, s[0]);
              break; 
            default:
              errs << t << T(" and ") << String(s);
              errn=oscerr_invalid_data;
              break;
            }
        }
      else if (s7_is_symbol(x))
        {
          const char* s=s7_symbol_name(x);
          switch (t)
            {
            case 0 :
            case 'S' :
              errn=lo_message_add_symbol(msg, s);
              break;
            case 's' :
              errn=lo_message_add_string(msg, s);
              break;
            default:
              errs << t << T(" and ") << String(s);
              errn=oscerr_invalid_data;
              break;
            }           
        }
      else if (s7_is_character(x))
        {
          char c=s7_character(x);
          switch (t)
            {
            case 0 :
            case LO_CHAR:
              errn=lo_message_add_char(msg, c);
              break;
            default:
              errs << t << T(" and ") << String(c);
              errn=oscerr_invalid_data;
              break;
            }
        }
      else if (s7_is_boolean(x))
        {
          if (t!=0) 
            {
              errs << t << T(" with #t or #f");
              errn=oscerr_invalid_data;
            }
          else if (x==s7_f(SchemeThread::getInstance()->scheme))
            errn=lo_message_add_false(msg);
          else
              errn=lo_message_add_true(msg);
        }          
      // list is midi or blob, eg :m (a b c d) or :b (...)
      // EMPTY LIST WILL FAIL
      else if (s7_is_pair(x)) 
        {
          s7_scheme *sc=SchemeThread::getInstance()->scheme;
          int siz=s7_list_length(sc,x);
          if (t=='m')
            {
              if (siz!=4)
                {
                  errs=T("midi list not 4 bytes");
                  errn=oscerr_invalid_data;
                  break;
                }
              int j=0;
              s7_pointer m;
              juce::uint8 midi[4];
              for (m=x; s7_is_pair(m) && (errn==0); m=s7_cdr(m), j++)
                if (s7_is_integer(s7_car(m)))
                  {
                    juce::uint32 y=(juce::uint32)s7_integer(s7_car(m));
                    midi[j]=(juce::uint8)(y & 0xFF);
                  }
                else 
                  errn=oscerr_invalid_data;
              if (errn==0)
                errn=lo_message_add_midi(msg, midi);
              else
                errs=T("midi not four bytes");
            }
          else if (t=='b')
            {
              if (siz<1)
                {
                  errs=T("blob list not one or more bytes");
                  errn=oscerr_invalid_data;
                  break;
                }
              s7_pointer m;
              juce::uint8 data[siz];
              int j=0;
              // get size and check data.
              for (m=x; s7_is_pair(m) && (errn==0); m=s7_cdr(m), j++)
                if (s7_is_integer(s7_car(m)))
                  {
                    juce::uint32 y=(juce::uint32)s7_integer(s7_car(m));
                    data[j]=(juce::uint8)(y & 0xFF);
                  }
                else 
                  errn=oscerr_invalid_data;
              if (errn==0)
                {
                  lo_blob blob=lo_blob_new(siz, data);
                  errn=lo_message_add_blob(msg, blob);
                }
              else
                errs=T("blob list not one or more bytes");
            }
          else
            {
              errs=T("list without midi or blob tag");
              errn=oscerr_invalid_data;
            }
        }
      else
        {
          errs=T("unparsable message data");
          errn=oscerr_invalid_data;
          break;
        }
    }

  switch (errn)
    {
    case 0:  // success!
      return msg;
    case oscerr_incomplete_message:
      errstr=T("incomplete OSC message");
      break;
    case oscerr_invalid_type:
      errstr=T("invalid OSC type: ") + errs;
      break;
    case oscerr_invalid_data:
      errstr=T("invalid osc data: ") + errs;              
      break;
    default: // liblo error (< 1)
      errstr=T("lo_message_add failed with ") + String(errn);
      break;
    }
  lo_message_free(msg);
  return NULL;
}

void osc_send_message(char* path, s7_pointer list)
{
  int errn=0;
  String errs=String::empty;
  lo_message msg=osc_make_message(list, errs);
  if (msg)
    {
      errn=OscPort::getInstance()->sendMessage(path,msg);
      if (errn<0)
        {
          errs=T("OSC: sendMessage failed with ") + String(errn);
          SchemeThread::getInstance()->signalSchemeError(errs);
        }
    }
  else
    SchemeThread::getInstance()->signalSchemeError(errs);
}

void osc_send_bundle(double time, s7_pointer list)
{
  lo_timetag ttag;
  lo_bundle bndl;
  int errn=0;
  String errs=String::empty;

  toTimeTag(time, ttag);
  bndl=lo_bundle_new(ttag);
  // list is a list of messages each should be ("/path" . data)
  s7_pointer p;
  for (p=list; s7_is_pair(p) && (errn==0); p=s7_cdr(p))
    {
      s7_pointer x=s7_car(p);
      if (s7_is_pair(x) && s7_is_string(s7_car(x)))
        {
          lo_message msg=osc_make_message(s7_cdr(x), errs);
          if (msg)
            {
              char* str=(char*)s7_string(s7_car(x));
              errn=lo_bundle_add_message(bndl, str, msg);
              if (errn!=0)
                errs=T("lo_bundle_add_message failed with ") + String(errn);
            }
          else
            {
              errn=oscerr_not_message;
              break;
            }
        }
      else
        {
          errs=T("not an OSC message");
          errn=oscerr_not_message;
          break;
        }
    }
  
  if (errn==0)
    {
      errn=OscPort::getInstance()->sendBundle(bndl);
      if (errn<0)
        {
          errs=T("OSC: sendBundle failed with ") + String(errn);
          SchemeThread::getInstance()->signalSchemeError(errs);
        }
    }
  else
    {
      lo_bundle_free_messages(bndl);
      SchemeThread::getInstance()->signalSchemeError(errs);
    }
}

#else
int osc_open(char* port, char* targ){SchemeThread::getInstance()->signalSchemeError(T("OSC not available.")); return -1;}
int osc_close(){SchemeThread::getInstance()->signalSchemeError(T("OSC not available.")); return -1;}
bool osc_is_open(){SchemeThread::getInstance()->signalSchemeError(T("OSC not available.")); return false;}
s7_pointer osc_set_hook(char* oscpath, s7_pointer proc){SchemeThread::getInstance()->signalSchemeError(T("OSC not available.")); return 0;}
s7_pointer osc_is_hook(char* oscpath){SchemeThread::getInstance()->signalSchemeError(T("OSC not available.")); return 0;}
void osc_send_message(char* oscpath, s7_pointer list){SchemeThread::getInstance()->signalSchemeError(T("OSC not available."));}
void osc_send_bundle(double time, s7_pointer list){SchemeThread::getInstance()->signalSchemeError(T("OSC not available."));}
#endif


