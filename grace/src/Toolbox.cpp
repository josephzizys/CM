/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision: $
// $Date: $ 

#include "Toolbox.h"
#if (defined(PPC) && defined(MACOSX))
#define POWF(a,b)	(juce::powf( (a) , (b) ))
#define LOGF(a)		(juce::logf( (a) ))
#define EXPF(a)		(juce::expf( (a) ))
#define SQRTF(a)	(juce::sqrtf( (a) ))
#define TANF(a)		(juce::tanf( (a) ))
#else
#include <math.h>
#define POWF(a,b)	(powf( (a) , (b) ))
#define LOGF(a)		(logf( (a) ))
#define EXPF(a)		(expf( (a) ))
#define SQRTF(a)	(sqrtf( (a) ))
#define TANF(a)		(tanf( (a) ))
#endif

double Toolbox::log_ten(double num)
{
  if (num>0.0)
    return log10(num);
  else
    return 0.0;
}

double Toolbox::log_two(double num)
{
  if (num>0.0)
    return log2(num);
  else
    return 0.0;
}

// mapping, scaling and offsetting

float Toolbox::rescale (float x, float x1, float x2, float y1, float y2, float b) {
  if ( x >= x2 ) 
    return y2;
  else
    if ( x <= x1 )
      return y1;
    else
      if ( b == 1)
	return (((( y2 - y1) / (x2 - x1)) * (x - x1)) + y1);
      else {
	float p = (x - x1) / (x2 - x1);
	return y1 + ( ( (y2 - y1) / (b - 1.0)) * (POWF(b, p) - 1.0));
      }
}

int Toolbox::discrete (float x, float x1, float x2, int i1, int i2, float b) {
  // return integers from a to b as n goes from 0.0 to 1.0
  //  return (int)round(Toolbox::rescale(x,x1,x2,(float)i1, (float)i2, b));
  return (int)floor(Toolbox::rescale(x,x1,x2,(float)i1, (float)i2, b));
}

int Toolbox::float_to_fixnum (float f) {
  return (int)round(f);
}

float Toolbox::decimals(float val, int places) {
  float p10 = (float)(10 ^ places);
  return round(val*p10) / p10;
}

float Toolbox::quantize (float val, float step) {
  return floor( (val/step) + .5) * step;
}

float Toolbox::rhythm_to_seconds(float beats, float tempo, float beat) {
  return (float) ((beats / beat) * (60.0f / tempo)) ;
}

float Toolbox::cents_to_scaler(int cents) {
  float p = ((float)cents)/1200.0f;
  return POWF(2.0f,p);
}

int Toolbox::scaler_to_cents(float scaler) {
  return (int)((LOGF(scaler)/LOGF(2.0)) * 1200);
}

float Toolbox::expl(float powr, float y0, float y1, float base) {
  if (powr < 0) powr=0.0;
  else if (powr > 1) powr = 1.0;
  if (base == 1.0)
    return y0 + ( powr * (y1 - y0));
  return ( y0 + ( ( (y1 - y0) / (base - 1.0) ) *
		  ( pow(base, powr) - 1.0 )));
}

float Toolbox::explseg( int i, int len, float sum, float powr) {
  if (i >= len) i += -1;
  float x1 = ((float)(i+1)) / ((float)len);
  float x2 = ((float)i) / ((float)len);
  float f1 = expl( x1, 0.0, 1.0, powr);
  float f2 = (i <= 0) ? 0.0 : expl( x2, 0.0, 1.0, powr);
  return ( sum * (f1 - f2) );
}

float Toolbox::geoseg(int i, int len, float sum, float base) {
  if (len==0) return 0.0;
  return sum * ( (1.0 - base) / (1.0 - pow(base, len))) ;
}

#define A00	6.875   // keynum 0

float Toolbox::hertz_to_keynum (float hz) {
  // subtract 3 shifts to A
  return (((LOGF(hz) - LOGF(A00) ) / LOGF(2)) * 12) - 3;
}

float Toolbox::keynum_to_hertz (float kn) {
  return A00 * pow(2, ((kn + 3) / 12));
}

int Toolbox::keynum_to_pc (float kn) {
  return ((int)kn) % 12;
}

//
// Randomness
//

Random::Random ranstate (1000);

void Toolbox::ranstate_set(int64 s) {
  ranstate.setSeed(s);
}

float Toolbox::ran(float f) {
  if (f == 0.0 ) return 0.0;
  if (f == 1.0) return ranstate.nextFloat();
  return (ranstate.nextFloat() * f);
}

float Toolbox::ran(float f1, float f2) {
  if (f1 == f2) return f1;
  if (f1 < f2) return (f1 + (ranstate.nextFloat() * (f2-f1)));
  return (float) (f1 - (ranstate.nextFloat() * (f1-f2)));
}

int Toolbox::ran(int i) {
  if ( i > 0 ) return ranstate.nextInt(i);
  if ( i < 0 ) return 0 - ranstate.nextInt(abs(i));
  return 0;
}

int Toolbox::ran(int i1, int i2) {
  if (i1 == i2) return i1;
  if (i1 < i2) return (i1 + ranstate.nextInt(i2-i1));
  return i1 - ranstate.nextInt(i1-i2);
}

float Toolbox::ranlow() {
  return juce::jmin( ranstate.nextFloat(), ranstate.nextFloat());
}

float Toolbox::ranhigh() {
  return juce::jmax( ranstate.nextFloat(), ranstate.nextFloat());
}

float Toolbox::ranmiddle() {
  return (ranstate.nextFloat() + ranstate.nextFloat()) / 2.0f;
}

float Toolbox::ranbeta (float a, float b) {
  float ra=1.0/a, rb=1.0/b, r1, r2, y1, y2, sum;
  while (true) {
    r1 = ranstate.nextFloat();
    r2 = ranstate.nextFloat();
    y1 = POWF(r1,ra);
    y2 = POWF(r2,rb);
    sum=y1+y2;
    if ( sum <= 1.0) return (float) (y1 / sum);
  }
}

float Toolbox::ranexp (float lambda) {
  return (- LOGF(1.0f - ranstate.nextFloat())) / lambda;
}

float Toolbox::ranexp2 (float lambda) {
  float ee = (2 * EXPF(-1.0));
  float u, v;
  while ( true ) {
    u = 1.0 - ranstate.nextFloat();
    v = ee * ranstate.nextFloat();
    if ( v <= (ee * u * LOGF(u)) )
      return (v / u) / lambda;
  }
}

//float Toolbox::gauss() {
//  float a = ranstate.nextFloat();
//  float b = ranstate.nextFloat();
//  return (float)( SQRTF(-2.0 * LOGF(1.0-a)) *
//		  cosf(juce::float_Pi * 2 * b) );
//}

float Toolbox::rangauss (float sigma, float mu) {
  // sigma=stand dev, mu=mean
  float x, y, r2;
  do {
    x = -1 + 2 * ranstate.nextFloat();
    y = -1 + 2 * ranstate.nextFloat();
    r2 = x * x + y * y;
  } while (r2 > 1.0 || r2 == 0);
  return (sigma * y * SQRTF(-2.0 * LOGF(r2) / r2))+mu;
}

float Toolbox::rancauchy() {
  return(TANF(juce::float_Pi*(ranstate.nextFloat() - 0.5f)));
}

int Toolbox::ranpoisson (float lambda) {
  float b = EXPF( - lambda);
  int n = 0;
  float p = 1.0;
  while ( true ) {
    p = p * ranstate.nextFloat();
    n++;
    if ( p < b ) return n;
  }
}

float Toolbox::rangamma (float nu) {
  float r=1.0;
  int n=(int)round(nu);
  for (int i=0; i<n; i++)
    r = r * (1 - ranstate.nextFloat());
  return - LOGF(r);
}

//// http://home.earthlink.net/~ltrammell/tech/pinkalg.htm
//// this doesnt seem to work.. too bad as it would keep the load even
//#define NGEN 3
//float av[NGEN] = {0.0046306,  0.0059961,  0.0083586};
//float pv[NGEN] = {0.31878,  0.77686,  0.97785};
//
//// (loop for x in  '(0.0046306  0.0059961  0.0083586) collect (* x 2 (- (random 1.0) .5)))
//float randreg[NGEN] = {0.0018758787, -0.0027519993, 0.0025562837};
//float Toolbox::ranpink() {
//  // Update each generator state per probability schedule
//  float rv = ranstate.nextFloat();
//  for (int i=0; i<NGEN; i++)
//    if (rv > pv[i])
//      randreg[i] = av[i] * 2 * (ranstate.nextFloat()-0.5);
//  // sum the generators
//  return randreg[0] + randreg[1] + randreg[2];
//}

#define POW2 5
#define POWN 32
double pinking[POWN];

double Toolbox::one_over_f_aux(int n, double *r, double halfrange) {
  double sum=0.0;
  for (int i=0; i<POW2; i++) {
    double p = POWF(2.0, i);
    if ( ! ((n / p) == ((n - 1) / p)) )
      r[i]=( (ranstate.nextDouble() * 2 * halfrange) - halfrange) ;
    sum += r[i];
  }
  return sum;
}

double Toolbox::ranpink() {
  // Based on Gardner (1978) and Dick Moore (1988?)
  static int i=POWN;
  if ( i==POWN ) {
    double r[POW2];
    double h=1.0/POW2;
    for (int n=0; n<POWN; n++) {
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

double Toolbox::ranbrown() {
  // from http://vellocet.com/dsp/noise/VRand.h
  // but made to generate between -1 1

  static double b=0.0;
  while ( true ) {
    double  r = ranstate.nextDouble()*2-1;
    b += r;
    if (b<-16.0f || b>16.0f) b -= r;
      else break;
    }
  // return interval -1 1.
  return (b*0.0625);
}

