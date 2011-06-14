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
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

//----------//
//Namespaces//
//----------//
using namespace juce;

#endif
