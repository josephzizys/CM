/* Generated from ChickenBridge.scm by the CHICKEN compiler
   http://www.call-with-current-continuation.org
   2007-10-02 23:47
   Version 2.6 - macosx-unix-gnu-x86 - [ symbolgc libffi dload ptables gchooks extraslot ]
   command line: ChickenBridge.scm -output-file ChickenBridge.cpp -quiet
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
 printf("length of node before %i, ", ((GraceApp *)GraceApp::getInstance())->queue->nodes.size());
  ((GraceApp *)GraceApp::getInstance())->queue->addNode(1, time, 0, 0, proc);
   printf("length of node after %i, ", ((GraceApp *)GraceApp::getInstance())->queue->nodes.size());
}
 


C_externexport  double  G_apply_process(C_word t0);

static C_PTABLE_ENTRY *create_ptable(void);
C_noret_decl(C_library_toplevel)
C_externimport void C_ccall C_library_toplevel(C_word c,C_word d,C_word k) C_noret;
C_noret_decl(C_eval_toplevel)
C_externimport void C_ccall C_eval_toplevel(C_word c,C_word d,C_word k) C_noret;
C_noret_decl(C_extras_toplevel)
C_externimport void C_ccall C_extras_toplevel(C_word c,C_word d,C_word k) C_noret;

static C_TLS C_word lf[27];


/* from now in k75 in k72 in k69 */
#define return(x) C_cblock C_r = (C_flonum(&C_a,(x))); goto C_return; C_cblockend
static C_word C_fcall stub26(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub26(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
 C_return(Time::getMillisecondCounterHiRes());
C_return:
#undef return

return C_r;}

/* from k125 */
static C_word C_fcall stub21(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2) C_regparm;
C_regparm static C_word C_fcall stub21(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
double t0=(double )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
float t2=(float )C_c_double(C_a2);
insert_midi_note(t0,t1,t2);
return C_r;}

/* from k110 */
static C_word C_fcall stub14(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub14(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
double t0=(double )C_c_double(C_a0);
C_word t1=(C_word )(C_a1);
insert_process(t0,t1);
return C_r;}

/* from k96 in print-error in k75 in k72 in k69 */
static C_word C_fcall stub7(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub7(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_error(t0);
return C_r;}

/* from k82 in print-message in k75 in k72 in k69 */
static C_word C_fcall stub1(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub1(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_mess(t0);
return C_r;}

C_noret_decl(C_grace_toplevel)
C_externexport void C_ccall C_grace_toplevel(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_71)
static void C_ccall f_71(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_74)
static void C_ccall f_74(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_77)
static void C_ccall f_77(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_213)
static void C_ccall f_213(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_206)
static void C_ccall f_206(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_187)
static void C_ccall f_187(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_134)
static void C_ccall f_134(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_138)
static void C_ccall f_138(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_145)
static void C_fcall f_145(C_word t0,C_word t1) C_noret;
C_noret_decl(f_197)
static void C_fcall f_197(C_word t0,C_word t1) C_noret;
C_noret_decl(f_201)
static void C_ccall f_201(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_151)
static void C_ccall f_151(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_157)
static void C_fcall f_157(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_167)
static void C_ccall f_167(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_170)
static void C_ccall f_170(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_129)
static void C_ccall f_129(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_114)
static void C_ccall f_114(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_107)
static void C_ccall f_107(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_93)
static void C_ccall f_93(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_98)
static void C_ccall f_98(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_79)
static void C_ccall f_79(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_84)
static void C_ccall f_84(C_word c,C_word t0,C_word t1) C_noret;

/* from G_apply_process */
 double  G_apply_process(C_word t0){
C_word x, *a=C_alloc(0);
C_callback_adjust_stack_limits(a);
x=((C_word)t0);
C_save(x);
return C_c_double(C_callback_wrapper((void *)f_206,1));}

C_noret_decl(trf_145)
static void C_fcall trf_145(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_145(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_145(t0,t1);}

C_noret_decl(trf_197)
static void C_fcall trf_197(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_197(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_197(t0,t1);}

C_noret_decl(trf_157)
static void C_fcall trf_157(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_157(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_157(t0,t1,t2);}

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

C_noret_decl(tr3)
static void C_fcall tr3(C_proc3 k) C_regparm C_noret;
C_regparm static void C_fcall tr3(C_proc3 k){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
(k)(3,t0,t1,t2);}

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
if(!C_demand_2(120)){
C_save(t1);
C_rereclaim2(120*sizeof(C_word), 1);
t1=C_restore;}
a=C_alloc(3);
C_initialize_lf(lf,27);
lf[0]=C_h_intern(&lf[0],13,"print-message");
lf[1]=C_h_intern(&lf[1],17,"\003sysmake-c-string");
lf[2]=C_static_lambda_info(C_heaptop,19,"(print-message a04)");
lf[3]=C_h_intern(&lf[3],11,"print-error");
lf[4]=C_static_lambda_info(C_heaptop,18,"(print-error a610)");
lf[5]=C_h_intern(&lf[5],14,"insert-process");
lf[6]=C_static_lambda_info(C_heaptop,28,"(insert-process a1316 a1217)");
lf[7]=C_h_intern(&lf[7],16,"insert-midi-note");
lf[8]=C_static_lambda_info(C_heaptop,36,"(insert-midi-note a2023 a1924 a1825)");
lf[9]=C_h_intern(&lf[9],3,"now");
lf[10]=C_static_lambda_info(C_heaptop,5,"(now)");
lf[11]=C_h_intern(&lf[11],6,"runran");
lf[12]=C_flonum(C_heaptop,0.0);
lf[13]=C_static_lambda_info(C_heaptop,10,"(do40 i42)");
lf[14]=C_static_lambda_info(C_heaptop,16,"(runran n37 d38)");
lf[15]=C_h_intern(&lf[15],7,"runproc");
lf[16]=C_flonum(C_heaptop,200.0);
lf[17]=C_flonum(C_heaptop,0.0);
lf[18]=C_static_lambda_info(C_heaptop,6,"(a196)");
lf[19]=C_flonum(C_heaptop,-1.0);
lf[20]=C_static_lambda_info(C_heaptop,7,"(f_134)");
lf[21]=C_flonum(C_heaptop,0.0);
lf[22]=C_static_lambda_info(C_heaptop,21,"(runproc k47 n48 d49)");
lf[23]=C_h_intern(&lf[23],15,"G_apply_process");
lf[24]=C_static_lambda_info(C_heaptop,27,"(G_apply_process closure51)");
lf[25]=C_h_intern(&lf[25],14,"return-to-host");
lf[26]=C_static_lambda_info(C_heaptop,10,"(toplevel)");
C_register_lf2(lf,27,create_ptable());
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_71,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_library_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k69 */
static void C_ccall f_71(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_71,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_74,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_eval_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k72 in k69 */
static void C_ccall f_74(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_74,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_77,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k75 in k72 in k69 */
static void C_ccall f_77(C_word c,C_word t0,C_word t1){
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
C_word ab[27],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_77,2,t0,t1);}
t2=C_mutate((C_word*)lf[0]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_79,a[2]=lf[2],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[3]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_93,a[2]=lf[4],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate((C_word*)lf[5]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_107,a[2]=lf[6],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate((C_word*)lf[7]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_114,a[2]=lf[8],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[9]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_129,a[2]=lf[10],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate((C_word*)lf[11]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_151,a[2]=lf[14],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate((C_word*)lf[15]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_187,a[2]=lf[22],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate((C_word*)lf[23]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_206,a[2]=lf[24],tmp=(C_word)a,a+=3,tmp));
t10=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_213,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 93   return-to-host");
t11=C_retrieve(lf[25]);
((C_proc2)C_retrieve_proc(t11))(2,t11,t10);}

/* k211 in k75 in k72 in k69 */
static void C_ccall f_213(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_UNDEFINED);}

/* G_apply_process in k75 in k72 in k69 */
static void C_ccall f_206(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_206,3,t0,t1,t2);}
t3=t2;
((C_proc2)C_retrieve_proc(t3))(2,t3,t1);}

/* runproc in k75 in k72 in k69 */
static void C_ccall f_187(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word ab[15],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_187,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_197,a[2]=t2,a[3]=lf[18],tmp=(C_word)a,a+=4,tmp);
t6=t4;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=C_fix(0);
t9=(*a=C_VECTOR_TYPE|1,a[1]=t8,tmp=(C_word)a,a+=2,tmp);
t10=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_134,a[2]=t5,a[3]=t3,a[4]=t7,a[5]=t9,a[6]=lf[20],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 75   insert-process");
t11=*((C_word*)lf[5]+1);
((C_proc4)C_retrieve_proc(t11))(4,t11,t1,lf[21],t10);}

/* f_134 in runproc in k75 in k72 in k69 */
static void C_ccall f_134(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_134,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_138,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=t1,a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
t3=((C_word*)t0)[2];
f_197(t3,t2);}

/* k136 */
static void C_ccall f_138(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_138,2,t0,t1);}
t2=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[5])[1],C_fix(1));
t3=C_mutate(((C_word *)((C_word*)t0)[5])+1,t2);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_145,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_greaterp(((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[2]))){
t5=C_mutate(((C_word *)((C_word*)t0)[3])+1,lf[19]);
t6=t4;
f_145(t6,t5);}
else{
t5=t4;
f_145(t5,C_SCHEME_UNDEFINED);}}

/* k143 in k136 */
static void C_fcall f_145(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,((C_word*)((C_word*)t0)[2])[1]);}

/* a196 in runproc in k75 in k72 in k69 */
static void C_fcall f_197(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_197,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_201,a[2]=((C_word*)t0)[2],a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 78   insert-midi-note");
t3=*((C_word*)lf[7]+1);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[17],((C_word*)t0)[2],C_fix(100));}

/* k199 in a196 in runproc in k75 in k72 in k69 */
static void C_ccall f_201(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 79   insert-midi-note");
t2=*((C_word*)lf[7]+1);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[3],lf[16],((C_word*)t0)[2],C_fix(0));}

/* runran in k75 in k72 in k69 */
static void C_ccall f_151(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_151,4,t0,t1,t2,t3);}
t4=lf[12];
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_SCHEME_UNDEFINED;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=C_set_block_item(t7,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_157,a[2]=t7,a[3]=t3,a[4]=t5,a[5]=t2,a[6]=lf[13],tmp=(C_word)a,a+=7,tmp));
t9=((C_word*)t7)[1];
f_157(t9,t1,C_fix(0));}

/* do40 in runran in k75 in k72 in k69 */
static void C_fcall f_157(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_157,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_greaterp(t2,((C_word*)t0)[5]))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_167,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=t2,a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 70   insert-midi-note");
t4=*((C_word*)lf[7]+1);
((C_proc5)C_retrieve_proc(t4))(5,t4,t3,((C_word*)((C_word*)t0)[4])[1],C_fix(60),C_fix(100));}}

/* k165 in do40 in runran in k75 in k72 in k69 */
static void C_ccall f_167(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_167,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_170,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
t3=(C_word)C_a_i_plus(&a,2,C_fix(200),((C_word*)((C_word*)t0)[6])[1]);
C_trace("ChickenBridge.scm: 71   insert-midi-note");
t4=*((C_word*)lf[7]+1);
((C_proc5)C_retrieve_proc(t4))(5,t4,t2,t3,C_fix(60),C_fix(0));}

/* k168 in k165 in do40 in runran in k75 in k72 in k69 */
static void C_ccall f_170(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_170,2,t0,t1);}
t2=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[6])[1],((C_word*)t0)[5]);
t3=C_mutate(((C_word *)((C_word*)t0)[6])+1,t2);
t4=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[4],C_fix(1));
t5=((C_word*)((C_word*)t0)[3])[1];
f_157(t5,((C_word*)t0)[2],t4);}

/* now in k75 in k72 in k69 */
static void C_ccall f_129(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_129,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub26(t2));}

/* insert-midi-note in k75 in k72 in k69 */
static void C_ccall f_114(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_114,5,t0,t1,t2,t3,t4);}
t5=(C_word)C_i_foreign_flonum_argumentp(t2);
t6=(C_word)C_i_foreign_flonum_argumentp(t3);
t7=(C_word)C_i_foreign_flonum_argumentp(t4);
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,(C_word)stub21(C_SCHEME_UNDEFINED,t5,t6,t7));}

/* insert-process in k75 in k72 in k69 */
static void C_ccall f_107(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word *a;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_107,4,t0,t1,t2,t3);}
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub14(C_SCHEME_UNDEFINED,t4,t3));}

/* print-error in k75 in k72 in k69 */
static void C_ccall f_93(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_93,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_98,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[1]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_98(2,t4,C_SCHEME_FALSE);}}

/* k96 in print-error in k75 in k72 in k69 */
static void C_ccall f_98(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub7(C_SCHEME_UNDEFINED,t1));}

/* print-message in k75 in k72 in k69 */
static void C_ccall f_79(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_79,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_84,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[1]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_84(2,t4,C_SCHEME_FALSE);}}

/* k82 in print-message in k75 in k72 in k69 */
static void C_ccall f_84(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub1(C_SCHEME_UNDEFINED,t1));}

#ifdef C_ENABLE_PTABLES
static C_PTABLE_ENTRY ptable[24] = {
{"toplevelChickenBridge.scm",(void*)C_grace_toplevel},
{"f_71ChickenBridge.scm",(void*)f_71},
{"f_74ChickenBridge.scm",(void*)f_74},
{"f_77ChickenBridge.scm",(void*)f_77},
{"f_213ChickenBridge.scm",(void*)f_213},
{"f_206ChickenBridge.scm",(void*)f_206},
{"f_187ChickenBridge.scm",(void*)f_187},
{"f_134ChickenBridge.scm",(void*)f_134},
{"f_138ChickenBridge.scm",(void*)f_138},
{"f_145ChickenBridge.scm",(void*)f_145},
{"f_197ChickenBridge.scm",(void*)f_197},
{"f_201ChickenBridge.scm",(void*)f_201},
{"f_151ChickenBridge.scm",(void*)f_151},
{"f_157ChickenBridge.scm",(void*)f_157},
{"f_167ChickenBridge.scm",(void*)f_167},
{"f_170ChickenBridge.scm",(void*)f_170},
{"f_129ChickenBridge.scm",(void*)f_129},
{"f_114ChickenBridge.scm",(void*)f_114},
{"f_107ChickenBridge.scm",(void*)f_107},
{"f_93ChickenBridge.scm",(void*)f_93},
{"f_98ChickenBridge.scm",(void*)f_98},
{"f_79ChickenBridge.scm",(void*)f_79},
{"f_84ChickenBridge.scm",(void*)f_84},
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
