/*=======================================================================*
  Copyright (C) 2008 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#ifndef CMSUPPORT_H
#define CMSUPPORT_H

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

double cm_rescale(double x, double x1, double x2, double y1, double y2, double b1) ;
int cm_discrete(double x, double x1, double x2, int y1, int y2, double b=1.0);
int cm_float_to_fixnum(double f) ;
double cm_log_ten(double num);
double cm_log_two(double num);

double cm_expl(double powr, double y0, double y1, double base);
double cm_explseg(int i, int len, double sum, double base);
double cm_geoseg(int i, int len, double sum, double base);

double cm_decimals(double val, int places); //places=3
double cm_quantize(double val, double step);
//tempo=60 beat=.25
double cm_rhythm_to_seconds(double beats, double tempo, double beat);
double cm_cents_to_scaler(double cents);
double cm_scaler_to_cents(double scaler);
double cm_scaler_to_steps(double scaler);
double cm_keynum_to_hertz (double kn);
int cm_keynum_to_pc (double kn);
double cm_hertz_to_keynum (double hz);

void cm_ranseed(long s);
int cm_ranint(int i);
double cm_ranfloat(double f);
int cm_ranint2(int i1, int i2);
double cm_ranfloat2(double f1, double f2);

double cm_ranlow();
double cm_ranhigh();
double cm_ranmiddle();
double cm_ranbeta(double a5, double b); //a=b=.5
double cm_ranexp(double lambda); //lambda=1
double cm_ranexp2(double lambda);
double cm_rangauss(double sigma, double mu); // sigma=1 mu=0
double cm_rancauchy();
int cm_ranpoisson(double lambda);
double cm_rangamma(double k); // k=1
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
char* cm_directory(char* path, bool recurse=true);

// sal support

char* sal_tokenize(char* str);

// midi ports

char* cm_port_info();

File completeFile(String path);
bool mp_open_output(int dev);
bool mp_open_input(int dev);
void mp_close_output(int dev);
void mp_close_input(int dev);
void mp_set_output_file(char* file);

void mp_send_note(double time, double dur, double key, double vel, double chan);
void mp_send_data(int type, double time, double chan, double data1, double data2);

void mp_play_seq();
void mp_save_seq();
void mp_copy_seq();
void mp_plot_seq();
void mp_clear_seq();

void mp_set_tuning(int div);
void mp_set_instruments(int a,int b,int c,int d,int e,int f,int g,int h,
			int i,int j,int k,int l,int m,int n,int o,int p);
void mp_set_channel_mask(int m);
void mp_set_message_mask(int m);
void mp_set_midi_input_hook(SCHEMEPROC proc);
void mp_clear_midi_input_hook();

void cs_init_score(char* args);
void cs_send_score(int typ, int inst, double time, char* pars);

// fomus

int fms_open_score(char* a, char* b);
void fms_close_score();
void fms_save(const char* name);
/* void fms_init(); */
int fms_isfiletype(const char* ext);
void fms_new(const char* name);
void fms_select(const char* name);
void fms_free();
void fms_clear();
/* void fms_ival(int par, int act, int val); */
/* void fms_rval(int par, int act, int num, int den); */
/* void fms_mval(int par, int act, int val, int num, int den); */
/* void fms_fval(int par, int act, double val); */
/* void fms_sval(int par, int act, char* val); */
/* void fms_act(int par, int act); */
void fms_load(char* filename);
void fms_run();
void fms_xml(char* str);

// plotting

void plot_xml(char* str);
char* plot_data(char* window, int layer);

#endif

