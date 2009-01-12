/*=======================================================================*
  Copyright (C) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#ifndef CMSUPPORT_H
#define CMSUPPORT_H

#ifndef CM_VERSION
#define CM_VERSION 321
#endif

#include "Scheme.h"

void cm_quit();

void cm_print_output(char* str, bool quote=false);
void cm_print_error(char* str);
void cm_print_values(char* str);


//void cm_buffering_stdout( char c);
//void cm_buffering_stderr( char c);

void cm_shell(char* str);
void cm_play(char* str);
void cm_load_sal_file(char* path);

#ifdef _MSC_VER
int round(double n);
#endif

float cm_rescale(float x, float x1, float x2, float y1, float y2, float b1) ;
int cm_discrete(float x, float x1, float x2, int y1, int y2, float b=1.0);
int cm_float_to_fixnum(float f) ;
double cm_log_ten(double num);
double cm_log_two(double num);

float cm_expl(float powr, float y0, float y1, float base);
float cm_explseg(int i, int len, float sum, float base);
float cm_geoseg(int i, int len, float sum, float base);

float cm_decimals(float val, int places); //places=3
float cm_quantize(float val, float step);
//tempo=60 beat=.25
float cm_rhythm_to_seconds(float beats, float tempo, float beat);
float cm_cents_to_scaler(int cents);
int cm_scaler_to_cents(float scaler);
float cm_keynum_to_hertz (float kn);
int cm_keynum_to_pc (float kn);
float cm_hertz_to_keynum (float hz);

void cm_ranseed(long s);
int cm_ranint(int i);
float cm_ranfloat(float f);
int cm_ranint2(int i1, int i2);
float cm_ranfloat2(float f1, float f2);

float cm_ranlow();
float cm_ranhigh();
float cm_ranmiddle();
float cm_ranbeta(float a5, float b); //a=b=.5
float cm_ranexp(float lambda); //lambda=1
float cm_ranexp2(float lambda);
float cm_rangauss(float sigma, float mu); // sigma=1 mu=0
float cm_rancauchy();
int cm_ranpoisson(float lambda);
float cm_rangamma(float k); // k=1
double cm_ranpink();
double cm_ranbrown();
double cm_bes_jn(int a, double b);

// scheduling

double cm_now() ;
void cm_sched_sprout(SCHEMEPROC proc, double time, int id);
bool cm_sched_paused_p();
void cm_sched_pause();
void cm_sched_continue();
void cm_sched_stop(int id);
void cm_sched_hush();
bool cm_sched_busy_p();
bool cm_sched_score_mode_p();
void cm_sched_set_score_mode(int val);
double cm_sched_score_time();

// file system and pathname support

char* cm_user_home_directory();
char* cm_temp_directory();
char* cm_current_directory();
bool cm_set_current_directory (char *path);
char* cm_pathname_directory(char* path);
char* cm_pathname_name(char* path);
char* cm_pathname_type(char* path);
char* cm_full_pathname(char* path);
bool cm_pathname_exists_p(char* path);
bool cm_pathname_writable_p(char* path);
bool cm_pathname_directory_p(char* path);

// midi ports

char* cm_port_info();

bool mp_open_output(int dev);
bool mp_open_input(int dev);
void mp_close_output(int dev);
void mp_close_input(int dev);
void mp_set_output_file(char* file);

void mp_send_note(double time, double dur, float key, float vel, float chan);
void mp_send_data(int type, double time, float chan, float data1, float data2);

void mp_play_seq();
void mp_save_seq();
void mp_copy_seq();
void mp_plot_seq();
void mp_clear_seq();

void mp_set_tuning(int div);
void mp_set_channel_mask(int m);
void mp_set_message_mask(int m);
void mp_set_midi_input_hook(SCHEMEPROC proc);
void mp_clear_midi_input_hook();

void cs_init_score(char* args);
void cs_send_score(int typ, int inst, double time, char* pars);

char* sal_tokenize(char* str);

#endif
