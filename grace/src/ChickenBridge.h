#ifndef __CHICKENBRIDGE__
#define __CHICKENBRIDGE__

extern "C" {
  void C_ccall C_grace_toplevel(C_word c,C_word t0,C_word t1) C_noret;
  C_externexport  double  run_process(C_word t0,double t1);
}

#endif
