/* Generated from src/ChickenBridge.scm by the CHICKEN compiler
   http://www.call-with-current-continuation.org
   2007-10-08 14:27
   Version 2.6 - macosx-unix-gnu-x86 - [ symbolgc libffi dload ptables gchooks extraslot ]
   command line: src/ChickenBridge.scm -output-file src/ChickenBridge.cpp -quiet
   unit: grace
*/

#include "chicken.h"


#include "Grace.h"
#include "Scheme.h"
#include "Nodes.h"

void print_mess(char * st)
{
  ((GraceApp *)GraceApp::getInstance())->getConsole()->printMessage( String(st));
}

void print_error(char * st)
{
  ((GraceApp *)GraceApp::getInstance())->getConsole()->printError( String(st));
}

void insert_midi_note(double time, float k, float v)
{
 float vals[2];
 vals[0] = k;
 vals[1] = v;
 ((GraceApp *)GraceApp::getInstance())->queue->addNode(0, time, vals, 2, 0);

}

void insert_process( double time, C_word proc )
{
  ((GraceApp *)GraceApp::getInstance())->queue->addNode(1, time, 0, 0, proc);
}

void insert_closure( double time, C_word proc )
{
  ((GraceApp *)GraceApp::getInstance())->queue->addNode(2, time, 0, 0, proc);
}


 


static C_PTABLE_ENTRY *create_ptable(void);
C_noret_decl(C_library_toplevel)
C_externimport void C_ccall C_library_toplevel(C_word c,C_word d,C_word k) C_noret;
C_noret_decl(C_eval_toplevel)
C_externimport void C_ccall C_eval_toplevel(C_word c,C_word d,C_word k) C_noret;
C_noret_decl(C_extras_toplevel)
C_externimport void C_ccall C_extras_toplevel(C_word c,C_word d,C_word k) C_noret;
C_noret_decl(C_extras_toplevel)
C_externimport void C_ccall C_extras_toplevel(C_word c,C_word d,C_word k) C_noret;

static C_TLS C_word lf[29];


/* from now in k84 in k81 in k78 in k75 */
#define return(x) C_cblock C_r = (C_flonum(&C_a,(x))); goto C_return; C_cblockend
static C_word C_fcall stub32(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub32(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
 C_return(Time::getMillisecondCounterHiRes());
C_return:
#undef return

return C_r;}

/* from k141 */
static C_word C_fcall stub27(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2) C_regparm;
C_regparm static C_word C_fcall stub27(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
double t0=(double )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
float t2=(float )C_c_double(C_a2);
insert_midi_note(t0,t1,t2);
return C_r;}

/* from k126 */
static C_word C_fcall stub20(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub20(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
double t0=(double )C_c_double(C_a0);
C_word t1=(C_word )(C_a1);
insert_closure(t0,t1);
return C_r;}

/* from k119 */
static C_word C_fcall stub14(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub14(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
double t0=(double )C_c_double(C_a0);
C_word t1=(C_word )(C_a1);
insert_process(t0,t1);
return C_r;}

/* from k105 in print-error in k84 in k81 in k78 in k75 */
static C_word C_fcall stub7(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub7(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_error(t0);
return C_r;}

/* from k91 in print-message in k84 in k81 in k78 in k75 */
static C_word C_fcall stub1(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub1(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_mess(t0);
return C_r;}

C_noret_decl(C_grace_toplevel)
C_externexport void C_ccall C_grace_toplevel(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_77)
static void C_ccall f_77(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_80)
static void C_ccall f_80(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_83)
static void C_ccall f_83(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_86)
static void C_ccall f_86(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_222)
static void C_ccall f_222(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_203)
static void C_ccall f_203(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_212)
static void C_ccall f_212(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_216)
static void C_ccall f_216(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_207)
static void C_ccall f_207(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_167)
static void C_ccall f_167(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_173)
static void C_fcall f_173(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_183)
static void C_ccall f_183(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_186)
static void C_ccall f_186(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_148)
static void C_ccall f_148(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_150)
static void C_ccall f_150(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_154)
static void C_ccall f_154(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_161)
static void C_fcall f_161(C_word t0,C_word t1) C_noret;
C_noret_decl(f_145)
static void C_ccall f_145(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_130)
static void C_ccall f_130(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_123)
static void C_ccall f_123(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_116)
static void C_ccall f_116(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_102)
static void C_ccall f_102(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_107)
static void C_ccall f_107(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_88)
static void C_ccall f_88(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_93)
static void C_ccall f_93(C_word c,C_word t0,C_word t1) C_noret;

C_noret_decl(trf_173)
static void C_fcall trf_173(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_173(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_173(t0,t1,t2);}

C_noret_decl(trf_161)
static void C_fcall trf_161(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_161(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_161(t0,t1);}

C_noret_decl(tr3)
static void C_fcall tr3(C_proc3 k) C_regparm C_noret;
C_regparm static void C_fcall tr3(C_proc3 k){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
(k)(3,t0,t1,t2);}

C_noret_decl(tr4)
static void C_fcall tr4(C_proc4 k) C_regparm C_noret;
C_regparm static void C_fcall tr4(C_proc4 k){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
(k)(4,t0,t1,t2,t3);}

C_noret_decl(tr5)
static void C_fcall tr5(C_proc5 k) C_regparm C_noret;
C_regparm static void C_fcall tr5(C_proc5 k){
C_word t4=C_pick(0);
C_word t3=C_pick(1);
C_word t2=C_pick(2);
C_word t1=C_pick(3);
C_word t0=C_pick(4);
C_adjust_stack(-5);
(k)(5,t0,t1,t2,t3,t4);}

C_noret_decl(tr2)
static void C_fcall tr2(C_proc2 k) C_regparm C_noret;
C_regparm static void C_fcall tr2(C_proc2 k){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
(k)(2,t0,t1);}

/* toplevel */
static C_TLS int toplevel_initialized=0;
C_noret_decl(toplevel_trampoline)
static void C_fcall toplevel_trampoline(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall toplevel_trampoline(void *dummy){
C_grace_toplevel(2,C_SCHEME_UNDEFINED,C_restore);}

void C_ccall C_grace_toplevel(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(toplevel_initialized) C_kontinue(t1,C_SCHEME_UNDEFINED);
else C_toplevel_entry(C_text("grace_toplevel"));
C_check_nursery_minimum(3);
if(!C_demand(3)){
C_save(t1);
C_reclaim((void*)toplevel_trampoline,NULL);}
toplevel_initialized=1;
if(!C_demand_2(130)){
C_save(t1);
C_rereclaim2(130*sizeof(C_word), 1);
t1=C_restore;}
a=C_alloc(3);
C_initialize_lf(lf,29);
lf[0]=C_h_intern(&lf[0],13,"print-message");
lf[1]=C_h_intern(&lf[1],17,"\003sysmake-c-string");
lf[2]=C_static_lambda_info(C_heaptop,19,"(print-message a04)");
lf[3]=C_h_intern(&lf[3],11,"print-error");
lf[4]=C_static_lambda_info(C_heaptop,18,"(print-error a610)");
lf[5]=C_h_intern(&lf[5],14,"insert-process");
lf[6]=C_static_lambda_info(C_heaptop,28,"(insert-process a1316 a1217)");
lf[7]=C_h_intern(&lf[7],14,"insert-closure");
lf[8]=C_static_lambda_info(C_heaptop,28,"(insert-closure a1922 a1823)");
lf[9]=C_h_intern(&lf[9],16,"insert-midi-note");
lf[10]=C_static_lambda_info(C_heaptop,36,"(insert-midi-note a2629 a2530 a2431)");
lf[11]=C_h_intern(&lf[11],3,"now");
lf[12]=C_static_lambda_info(C_heaptop,5,"(now)");
lf[13]=C_h_intern(&lf[13],12,"make-process");
lf[14]=C_flonum(C_heaptop,-1.0);
lf[15]=C_static_lambda_info(C_heaptop,7,"(f_150)");
lf[16]=C_static_lambda_info(C_heaptop,35,"(make-process p35 num36 interval37)");
lf[17]=C_h_intern(&lf[17],6,"runran");
lf[18]=C_flonum(C_heaptop,0.0);
lf[19]=C_static_lambda_info(C_heaptop,10,"(do46 i48)");
lf[20]=C_static_lambda_info(C_heaptop,16,"(runran n43 d44)");
lf[21]=C_h_intern(&lf[21],7,"runproc");
lf[22]=C_flonum(C_heaptop,0.0);
lf[23]=C_flonum(C_heaptop,90.0);
lf[24]=C_flonum(C_heaptop,0.0);
lf[25]=C_static_lambda_info(C_heaptop,6,"(a211)");
lf[26]=C_static_lambda_info(C_heaptop,21,"(runproc k53 n54 d55)");
lf[27]=C_h_intern(&lf[27],14,"return-to-host");
lf[28]=C_static_lambda_info(C_heaptop,10,"(toplevel)");
C_register_lf2(lf,29,create_ptable());
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_77,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_library_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k75 */
static void C_ccall f_77(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_77,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_80,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_eval_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k78 in k75 */
static void C_ccall f_80(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_80,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_83,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k81 in k78 in k75 */
static void C_ccall f_83(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_83,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_86,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k84 in k81 in k78 in k75 */
static void C_ccall f_86(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word t12;
C_word ab[30],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_86,2,t0,t1);}
t2=C_mutate((C_word*)lf[0]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_88,a[2]=lf[2],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[3]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_102,a[2]=lf[4],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate((C_word*)lf[5]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_116,a[2]=lf[6],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate((C_word*)lf[7]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_123,a[2]=lf[8],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[9]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_130,a[2]=lf[10],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate((C_word*)lf[11]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_145,a[2]=lf[12],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate((C_word*)lf[13]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_148,a[2]=lf[16],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate((C_word*)lf[17]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_167,a[2]=lf[20],tmp=(C_word)a,a+=3,tmp));
t10=C_mutate((C_word*)lf[21]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_203,a[2]=lf[26],tmp=(C_word)a,a+=3,tmp));
t11=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_222,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("src/ChickenBridge.scm: 94   return-to-host");
t12=C_retrieve(lf[27]);
((C_proc2)C_retrieve_proc(t12))(2,t12,t11);}

/* k220 in k84 in k81 in k78 in k75 */
static void C_ccall f_222(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_UNDEFINED);}

/* runproc in k84 in k81 in k78 in k75 */
static void C_ccall f_203(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[7],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_203,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_207,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_212,a[2]=t2,a[3]=lf[25],tmp=(C_word)a,a+=4,tmp);
C_trace("src/ChickenBridge.scm: 85   make-process");
t7=*((C_word*)lf[13]+1);
((C_proc5)C_retrieve_proc(t7))(5,t7,t5,t6,t3,t4);}

/* a211 in runproc in k84 in k81 in k78 in k75 */
static void C_ccall f_212(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_212,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_216,a[2]=((C_word*)t0)[2],a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("src/ChickenBridge.scm: 87   insert-midi-note");
t3=*((C_word*)lf[9]+1);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[24],((C_word*)t0)[2],C_fix(100));}

/* k214 in a211 in runproc in k84 in k81 in k78 in k75 */
static void C_ccall f_216(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("src/ChickenBridge.scm: 88   insert-midi-note");
t2=*((C_word*)lf[9]+1);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[3],lf[23],((C_word*)t0)[2],C_fix(0));}

/* k205 in runproc in k84 in k81 in k78 in k75 */
static void C_ccall f_207(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("src/ChickenBridge.scm: 90   insert-process");
t2=*((C_word*)lf[5]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[2],lf[22],t1);}

/* runran in k84 in k81 in k78 in k75 */
static void C_ccall f_167(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[11],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_167,4,t0,t1,t2,t3);}
t4=lf[18];
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_SCHEME_UNDEFINED;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=C_set_block_item(t7,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_173,a[2]=t7,a[3]=t3,a[4]=t5,a[5]=t2,a[6]=lf[19],tmp=(C_word)a,a+=7,tmp));
t9=((C_word*)t7)[1];
f_173(t9,t1,C_fix(0));}

/* do46 in runran in k84 in k81 in k78 in k75 */
static void C_fcall f_173(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_173,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_greaterp(t2,((C_word*)t0)[5]))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_183,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=t2,a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],tmp=(C_word)a,a+=7,tmp);
C_trace("src/ChickenBridge.scm: 80   insert-midi-note");
t4=*((C_word*)lf[9]+1);
((C_proc5)C_retrieve_proc(t4))(5,t4,t3,((C_word*)((C_word*)t0)[4])[1],C_fix(60),C_fix(100));}}

/* k181 in do46 in runran in k84 in k81 in k78 in k75 */
static void C_ccall f_183(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_183,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_186,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
t3=(C_word)C_a_i_plus(&a,2,C_fix(200),((C_word*)((C_word*)t0)[6])[1]);
C_trace("src/ChickenBridge.scm: 81   insert-midi-note");
t4=*((C_word*)lf[9]+1);
((C_proc5)C_retrieve_proc(t4))(5,t4,t2,t3,C_fix(60),C_fix(0));}

/* k184 in k181 in do46 in runran in k84 in k81 in k78 in k75 */
static void C_ccall f_186(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_186,2,t0,t1);}
t2=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[6])[1],((C_word*)t0)[5]);
t3=C_mutate(((C_word *)((C_word*)t0)[6])+1,t2);
t4=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[4],C_fix(1));
t5=((C_word*)((C_word*)t0)[3])[1];
f_173(t5,((C_word*)t0)[2],t4);}

/* make-process in k84 in k81 in k78 in k75 */
static void C_ccall f_148(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[11],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_148,5,t0,t1,t2,t3,t4);}
t5=t4;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=C_fix(0);
t8=(*a=C_VECTOR_TYPE|1,a[1]=t7,tmp=(C_word)a,a+=2,tmp);
t9=t1;
((C_proc2)(void*)(*((C_word*)t9+1)))(2,t9,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_150,a[2]=t2,a[3]=t3,a[4]=t6,a[5]=t8,a[6]=lf[15],tmp=(C_word)a,a+=7,tmp));}

/* f_150 in make-process in k84 in k81 in k78 in k75 */
static void C_ccall f_150(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_150,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_154,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=t1,a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
t3=((C_word*)t0)[2];
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k152 */
static void C_ccall f_154(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_154,2,t0,t1);}
t2=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[5])[1],C_fix(1));
t3=C_mutate(((C_word *)((C_word*)t0)[5])+1,t2);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_161,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_greaterp(((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[2]))){
t5=C_mutate(((C_word *)((C_word*)t0)[3])+1,lf[14]);
t6=t4;
f_161(t6,t5);}
else{
t5=t4;
f_161(t5,C_SCHEME_UNDEFINED);}}

/* k159 in k152 */
static void C_fcall f_161(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,((C_word*)((C_word*)t0)[2])[1]);}

/* now in k84 in k81 in k78 in k75 */
static void C_ccall f_145(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_145,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub32(t2));}

/* insert-midi-note in k84 in k81 in k78 in k75 */
static void C_ccall f_130(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_130,5,t0,t1,t2,t3,t4);}
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_flonum_argumentp(t3);
t7=(C_word)C_i_foreign_flonum_argumentp(t4);
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,(C_word)stub27(C_SCHEME_UNDEFINED,t5,t6,t7));}

/* insert-closure in k84 in k81 in k78 in k75 */
static void C_ccall f_123(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word *a;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_123,4,t0,t1,t2,t3);}
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub20(C_SCHEME_UNDEFINED,t4,t3));}

/* insert-process in k84 in k81 in k78 in k75 */
static void C_ccall f_116(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word *a;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_116,4,t0,t1,t2,t3);}
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub14(C_SCHEME_UNDEFINED,t4,t3));}

/* print-error in k84 in k81 in k78 in k75 */
static void C_ccall f_102(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_102,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_107,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[1]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_107(2,t4,C_SCHEME_FALSE);}}

/* k105 in print-error in k84 in k81 in k78 in k75 */
static void C_ccall f_107(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub7(C_SCHEME_UNDEFINED,t1));}

/* print-message in k84 in k81 in k78 in k75 */
static void C_ccall f_88(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_88,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_93,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[1]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_93(2,t4,C_SCHEME_FALSE);}}

/* k91 in print-message in k84 in k81 in k78 in k75 */
static void C_ccall f_93(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub1(C_SCHEME_UNDEFINED,t1));}

#ifdef C_ENABLE_PTABLES
static C_PTABLE_ENTRY ptable[27] = {
{"toplevelsrc/ChickenBridge.scm",(void*)C_grace_toplevel},
{"f_77src/ChickenBridge.scm",(void*)f_77},
{"f_80src/ChickenBridge.scm",(void*)f_80},
{"f_83src/ChickenBridge.scm",(void*)f_83},
{"f_86src/ChickenBridge.scm",(void*)f_86},
{"f_222src/ChickenBridge.scm",(void*)f_222},
{"f_203src/ChickenBridge.scm",(void*)f_203},
{"f_212src/ChickenBridge.scm",(void*)f_212},
{"f_216src/ChickenBridge.scm",(void*)f_216},
{"f_207src/ChickenBridge.scm",(void*)f_207},
{"f_167src/ChickenBridge.scm",(void*)f_167},
{"f_173src/ChickenBridge.scm",(void*)f_173},
{"f_183src/ChickenBridge.scm",(void*)f_183},
{"f_186src/ChickenBridge.scm",(void*)f_186},
{"f_148src/ChickenBridge.scm",(void*)f_148},
{"f_150src/ChickenBridge.scm",(void*)f_150},
{"f_154src/ChickenBridge.scm",(void*)f_154},
{"f_161src/ChickenBridge.scm",(void*)f_161},
{"f_145src/ChickenBridge.scm",(void*)f_145},
{"f_130src/ChickenBridge.scm",(void*)f_130},
{"f_123src/ChickenBridge.scm",(void*)f_123},
{"f_116src/ChickenBridge.scm",(void*)f_116},
{"f_102src/ChickenBridge.scm",(void*)f_102},
{"f_107src/ChickenBridge.scm",(void*)f_107},
{"f_88src/ChickenBridge.scm",(void*)f_88},
{"f_93src/ChickenBridge.scm",(void*)f_93},
{NULL,NULL}};
#endif

static C_PTABLE_ENTRY *create_ptable(void){
#ifdef C_ENABLE_PTABLES
return ptable;
#else
return NULL;
#endif
}
/* end of file */
