#ifndef LIBRARIES_H
#define LIBRARIES_H

//----//
//JUCE//
//----//
#define DONT_SET_USING_JUCE_NAMESPACE 1
//#define JUCE_DONT_DEFINE_MACROS 1
#include "juce.h"

//---------------//
//Other Libraries//
//---------------//
#ifdef WITH_SDIF
  #include "sdif.h"
#endif

#ifdef WITH_LIBLO
  #include "lo/lo.h"
#endif

#ifdef WITH_FOMUS
  #define FOMUS_TYPESONLY
  #include <fomus/fomusapi.h>
  #include <fomus/infoapi.h>
#endif

#ifdef WITH_SNDLIB
  #include "s7.h"
#endif

//-----------------//
//Platform-Specific//
//-----------------//
#ifdef _MSC_VER
  #include <unistd.h>
  #define strdup _strdup
  #define jn _jn
  double log2(double n) {return log(n)/log(2.0);}
  int round(double n) {return (int)(n+.5);}
#endif

//----------------//
//Standard library//
//----------------//
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

//These should be eventually changed to <cmath>, <cstring>, etc.
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------//
//Namespaces//
//----------//
using namespace juce;

#endif
