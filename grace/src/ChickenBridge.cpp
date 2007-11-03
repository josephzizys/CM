/* Generated from ChickenBridge.scm by the CHICKEN compiler
   http://www.call-with-current-continuation.org
   2007-11-03 16:31
   Version 2.724 - macosx-unix-gnu-x86 - [ manyargs dload ptables applyhook ]
(c)2000-2007 Felix L. Winkelmann | compiled 2007-10-21 on todd-ingalls-computer-2.local (Darwin)
   command line: ChickenBridge.scm -output-file ChickenBridge.cpp -quiet
   unit: grace
*/

#include "chicken.h"


#include "Grace.h"
#include "Scheme.h"
#include "OutputQueue.h"

void print_mess(char * st)
{
 ((GraceApp *)GraceApp::getInstance())->getConsole()->printMessage( String(st));
   // printf("%s", st);
}

void print_error(char * st)
{
 ((GraceApp *)GraceApp::getInstance())->getConsole()->printError( String(st));
 //   printf("%s", st);
}

void insert_midi_on(double time, float k, float v, float c) {
 float vals[3];
 vals[0] = k;
 vals[1] = v;
 vals[2] = c;
 ((GraceApp *)GraceApp::getInstance())->outputQueue->outputNodes.lockArray();
 ((GraceApp *)GraceApp::getInstance())->outputQueue->addNode(time, vals, 3);
 ((GraceApp *)GraceApp::getInstance())->outputQueue->outputNodes.unlockArray();
}

void insert_midi_note(double time, double dur, float k, float v, float c) {
 float on[3];
 float off[3];
 on[0] =  off[0] = k;
 on[1] = v;
 off[1] = 0.0;
 on[2] = off[2] =  c;
 ((GraceApp *)GraceApp::getInstance())->outputQueue->outputNodes.lockArray();
 ((GraceApp *)GraceApp::getInstance())->outputQueue->addNode(time, on, 3);
 ((GraceApp *)GraceApp::getInstance())->outputQueue->addNode(time+dur, off, 3); 
 ((GraceApp *)GraceApp::getInstance())->outputQueue->outputNodes.unlockArray();
}

void insert_process( double time, C_word proc )
{
  ((GraceApp *)GraceApp::getInstance())->schemeProcess->addNode(0, time, proc);
}

void insert_closure( double time, C_word proc )
{
  ((GraceApp *)GraceApp::getInstance())->schemeProcess->addNode(1, time, proc);
}

 


C_externexport  double  run_process(C_word t0,double t1);

static C_PTABLE_ENTRY *create_ptable(void);
C_noret_decl(C_library_toplevel)
C_externimport void C_ccall C_library_toplevel(C_word c,C_word d,C_word k) C_noret;
C_noret_decl(C_eval_toplevel)
C_externimport void C_ccall C_eval_toplevel(C_word c,C_word d,C_word k) C_noret;
C_noret_decl(C_extras_toplevel)
C_externimport void C_ccall C_extras_toplevel(C_word c,C_word d,C_word k) C_noret;
C_noret_decl(C_extras_toplevel)
C_externimport void C_ccall C_extras_toplevel(C_word c,C_word d,C_word k) C_noret;

static C_TLS C_word lf[133];


/* from current-time-hi-res in k208 in k205 in k202 in k199 */
#define return(x) C_cblock C_r = (C_flonum(&C_a,(x))); goto C_ret; C_cblockend
static C_word C_fcall stub53(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub53(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
 C_return(Time::getMillisecondCounterHiRes());
C_ret:
#undef return

return C_r;}

/* from k291 */
C_noret_decl(stub33)
static void C_ccall stub33(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2,C_word C_a3,C_word C_a4) C_noret;
static void C_ccall stub33(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2,C_word C_a3,C_word C_a4){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
double t0=(double )C_c_double(C_a0);
double t1=(double )C_c_double(C_a1);
float t2=(float )C_c_double(C_a2);
float t3=(float )C_c_double(C_a3);
float t4=(float )C_c_double(C_a4);
int C_level=C_save_callback_continuation(&C_a,C_k);
insert_midi_note(t0,t1,t2,t3,t4);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k262 */
C_noret_decl(stub22)
static void C_ccall stub22(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1) C_noret;
static void C_ccall stub22(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
double t0=(double )C_c_double(C_a0);
C_word t1=(C_word )(C_a1);
int C_level=C_save_callback_continuation(&C_a,C_k);
insert_closure(t0,t1);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k249 */
C_noret_decl(stub14)
static void C_ccall stub14(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1) C_noret;
static void C_ccall stub14(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
double t0=(double )C_c_double(C_a0);
C_word t1=(C_word )(C_a1);
int C_level=C_save_callback_continuation(&C_a,C_k);
insert_process(t0,t1);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k229 in print-error in k208 in k205 in k202 in k199 */
static C_word C_fcall stub7(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub7(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_error(t0);
return C_r;}

/* from k215 in print-message in k208 in k205 in k202 in k199 */
static C_word C_fcall stub1(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub1(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_mess(t0);
return C_r;}

C_noret_decl(C_grace_toplevel)
C_externexport void C_ccall C_grace_toplevel(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_201)
static void C_ccall f_201(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_204)
static void C_ccall f_204(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_207)
static void C_ccall f_207(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_210)
static void C_ccall f_210(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_322)
static void C_ccall f_322(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1085)
static void C_ccall f_1085(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_1132)
static void C_ccall f_1132(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1122)
static void C_ccall f_1122(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1089)
static void C_ccall f_1089(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_325)
static void C_ccall f_325(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1079)
static void C_ccall f_1079(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_1079)
static void C_ccall f_1079r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_564)
static void C_ccall f_564(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_615)
static void C_ccall f_615(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_618)
static void C_ccall f_618(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_621)
static void C_ccall f_621(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_624)
static void C_ccall f_624(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_627)
static void C_ccall f_627(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_630)
static void C_ccall f_630(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_633)
static void C_ccall f_633(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_636)
static void C_ccall f_636(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1073)
static void C_ccall f_1073(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_1073)
static void C_ccall f_1073r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_639)
static void C_ccall f_639(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1071)
static void C_ccall f_1071(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_641)
static void C_ccall f_641(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_654)
static void C_ccall f_654(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_657)
static void C_ccall f_657(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_908)
static void C_fcall f_908(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1016)
static void C_ccall f_1016(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_928)
static void C_fcall f_928(C_word t0,C_word t1) C_noret;
C_noret_decl(f_937)
static void C_fcall f_937(C_word t0,C_word t1) C_noret;
C_noret_decl(f_941)
static void C_ccall f_941(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_945)
static void C_ccall f_945(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_953)
static void C_fcall f_953(C_word t0,C_word t1) C_noret;
C_noret_decl(f_949)
static void C_ccall f_949(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_918)
static void C_ccall f_918(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_660)
static void C_ccall f_660(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_663)
static void C_ccall f_663(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_666)
static void C_ccall f_666(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_669)
static void C_ccall f_669(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_902)
static void C_ccall f_902(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_801)
static void C_fcall f_801(C_word t0,C_word t1) C_noret;
C_noret_decl(f_808)
static void C_ccall f_808(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_810)
static void C_fcall f_810(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_882)
static void C_ccall f_882(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_834)
static void C_fcall f_834(C_word t0,C_word t1) C_noret;
C_noret_decl(f_837)
static void C_ccall f_837(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_858)
static void C_ccall f_858(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_824)
static void C_ccall f_824(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_672)
static void C_ccall f_672(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_790)
static void C_ccall f_790(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_778)
static void C_ccall f_778(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_774)
static void C_ccall f_774(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_679)
static void C_fcall f_679(C_word t0,C_word t1) C_noret;
C_noret_decl(f_608)
static void C_ccall f_608(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_602)
static void C_ccall f_602(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_596)
static void C_ccall f_596(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_590)
static void C_ccall f_590(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_584)
static void C_ccall f_584(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_578)
static void C_ccall f_578(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_572)
static void C_ccall f_572(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_566)
static void C_ccall f_566(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_337)
static void C_ccall f_337(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_341)
static void C_ccall f_341(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_554)
static void C_ccall f_554(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_344)
static void C_ccall f_344(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_347)
static void C_ccall f_347(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_359)
static void C_ccall f_359(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_407)
static void C_fcall f_407(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_423)
static void C_ccall f_423(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_433)
static void C_ccall f_433(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_532)
static void C_ccall f_532(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_528)
static void C_ccall f_528(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_477)
static void C_ccall f_477(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_483)
static void C_ccall f_483(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_417)
static void C_fcall f_417(C_word t0,C_word t1) C_noret;
C_noret_decl(f_362)
static void C_ccall f_362(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_367)
static void C_fcall f_367(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_380)
static void C_fcall f_380(C_word t0,C_word t1) C_noret;
C_noret_decl(f_327)
static void C_fcall f_327(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_335)
static void C_ccall f_335(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_317)
static void C_ccall f_317(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_307)
static void C_ccall f_307(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_301)
static void C_ccall f_301(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_295)
static void C_ccall f_295(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_266)
static void C_ccall f_266(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_270)
static void C_ccall f_270(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_253)
static void C_ccall f_253(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_257)
static void C_ccall f_257(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_240)
static void C_ccall f_240(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_244)
static void C_ccall f_244(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_226)
static void C_ccall f_226(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_231)
static void C_ccall f_231(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_212)
static void C_ccall f_212(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_217)
static void C_ccall f_217(C_word c,C_word t0,C_word t1) C_noret;

/* from run_process */
 double  run_process(C_word t0,double t1){
C_word x, *a=C_alloc(0+3);
C_callback_adjust_stack_limits(a);
x=((C_word)t0);
C_save(x);
x=C_flonum(&a,t1);
C_save(x);
return C_c_double(C_callback_wrapper((void *)f_307,2));}

C_noret_decl(trf_908)
static void C_fcall trf_908(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_908(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_908(t0,t1,t2);}

C_noret_decl(trf_928)
static void C_fcall trf_928(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_928(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_928(t0,t1);}

C_noret_decl(trf_937)
static void C_fcall trf_937(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_937(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_937(t0,t1);}

C_noret_decl(trf_953)
static void C_fcall trf_953(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_953(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_953(t0,t1);}

C_noret_decl(trf_801)
static void C_fcall trf_801(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_801(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_801(t0,t1);}

C_noret_decl(trf_810)
static void C_fcall trf_810(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_810(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_810(t0,t1,t2);}

C_noret_decl(trf_834)
static void C_fcall trf_834(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_834(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_834(t0,t1);}

C_noret_decl(trf_679)
static void C_fcall trf_679(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_679(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_679(t0,t1);}

C_noret_decl(trf_407)
static void C_fcall trf_407(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_407(void *dummy){
C_word t4=C_pick(0);
C_word t3=C_pick(1);
C_word t2=C_pick(2);
C_word t1=C_pick(3);
C_word t0=C_pick(4);
C_adjust_stack(-5);
f_407(t0,t1,t2,t3,t4);}

C_noret_decl(trf_417)
static void C_fcall trf_417(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_417(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_417(t0,t1);}

C_noret_decl(trf_367)
static void C_fcall trf_367(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_367(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_367(t0,t1,t2);}

C_noret_decl(trf_380)
static void C_fcall trf_380(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_380(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_380(t0,t1);}

C_noret_decl(trf_327)
static void C_fcall trf_327(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_327(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_327(t0,t1,t2);}

C_noret_decl(tr7)
static void C_fcall tr7(C_proc7 k) C_regparm C_noret;
C_regparm static void C_fcall tr7(C_proc7 k){
C_word t6=C_pick(0);
C_word t5=C_pick(1);
C_word t4=C_pick(2);
C_word t3=C_pick(3);
C_word t2=C_pick(4);
C_word t1=C_pick(5);
C_word t0=C_pick(6);
C_adjust_stack(-7);
(k)(7,t0,t1,t2,t3,t4,t5,t6);}

C_noret_decl(tr6)
static void C_fcall tr6(C_proc6 k) C_regparm C_noret;
C_regparm static void C_fcall tr6(C_proc6 k){
C_word t5=C_pick(0);
C_word t4=C_pick(1);
C_word t3=C_pick(2);
C_word t2=C_pick(3);
C_word t1=C_pick(4);
C_word t0=C_pick(5);
C_adjust_stack(-6);
(k)(6,t0,t1,t2,t3,t4,t5);}

C_noret_decl(tr3)
static void C_fcall tr3(C_proc3 k) C_regparm C_noret;
C_regparm static void C_fcall tr3(C_proc3 k){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
(k)(3,t0,t1,t2);}

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

C_noret_decl(tr4)
static void C_fcall tr4(C_proc4 k) C_regparm C_noret;
C_regparm static void C_fcall tr4(C_proc4 k){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
(k)(4,t0,t1,t2,t3);}

C_noret_decl(tr2)
static void C_fcall tr2(C_proc2 k) C_regparm C_noret;
C_regparm static void C_fcall tr2(C_proc2 k){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
(k)(2,t0,t1);}

C_noret_decl(tr4r)
static void C_fcall tr4r(C_proc4 k) C_regparm C_noret;
C_regparm static void C_fcall tr4r(C_proc4 k){
int n;
C_word *a,t4;
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
n=C_rest_count(0);
a=C_alloc(n*3);
t4=C_restore_rest(a,n);
(k)(t0,t1,t2,t3,t4);}

C_noret_decl(tr3r)
static void C_fcall tr3r(C_proc3 k) C_regparm C_noret;
C_regparm static void C_fcall tr3r(C_proc3 k){
int n;
C_word *a,t3;
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
n=C_rest_count(0);
a=C_alloc(n*3);
t3=C_restore_rest(a,n);
(k)(t0,t1,t2,t3);}

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
if(!C_demand_2(1140)){
C_save(t1);
C_rereclaim2(1140*sizeof(C_word), 1);
t1=C_restore;}
a=C_alloc(3);
C_initialize_lf(lf,133);
lf[0]=C_h_intern(&lf[0],13,"print-message");
lf[1]=C_h_intern(&lf[1],17,"\003sysmake-c-string");
lf[2]=C_static_lambda_info(C_heaptop,19,"(print-message a04)");
lf[3]=C_h_intern(&lf[3],11,"print-error");
lf[4]=C_static_lambda_info(C_heaptop,18,"(print-error a610)");
lf[5]=C_h_intern(&lf[5],14,"insert-process");
lf[6]=C_static_lambda_info(C_heaptop,3,".\000\000");
lf[7]=C_h_intern(&lf[7],6,"\003sysgc");
lf[8]=C_static_lambda_info(C_heaptop,28,"(insert-process a1316 a1217)");
lf[9]=C_h_intern(&lf[9],14,"insert-closure");
lf[10]=C_static_lambda_info(C_heaptop,3,".\000\000");
lf[11]=C_static_lambda_info(C_heaptop,28,"(insert-closure a2124 a2025)");
lf[12]=C_h_intern(&lf[12],16,"insert-midi-note");
lf[13]=C_static_lambda_info(C_heaptop,3,".\000\000");
lf[14]=C_static_lambda_info(C_heaptop,48,"(insert-midi-note a3235 a3136 a3037 a2938 a2839)");
lf[15]=C_h_intern(&lf[15],12,"make-note-on");
lf[16]=C_h_intern(&lf[16],14,"insert-midi-on");
lf[17]=C_static_lambda_info(C_heaptop,30,"(make-note-on t42 k43 v44 c45)");
lf[18]=C_h_intern(&lf[18],13,"make-note-off");
lf[19]=C_flonum(C_heaptop,0.0);
lf[20]=C_static_lambda_info(C_heaptop,27,"(make-note-off t46 k47 c48)");
lf[21]=C_h_intern(&lf[21],11,"run_process");
lf[22]=C_static_lambda_info(C_heaptop,33,"(run_process closure49 elapsed50)");
lf[23]=C_h_intern(&lf[23],19,"current-time-hi-res");
lf[24]=C_static_lambda_info(C_heaptop,21,"(current-time-hi-res)");
lf[27]=C_h_intern(&lf[27],5,"error");
lf[28]=C_h_intern(&lf[28],7,"sprintf");
lf[29]=C_static_lambda_info(C_heaptop,21,"(ferror str62 args63)");
lf[30]=C_h_intern(&lf[30],11,"expand-send");
lf[31]=C_static_lambda_info(C_heaptop,13,"(do91 tail93)");
lf[32]=C_static_string(C_heaptop,37,"~S found duplicate keyword \047~S\047 in ~S");
lf[33]=C_static_string(C_heaptop,33,"~S missing value for keyword \047~S\047");
lf[34]=C_static_string(C_heaptop,53,"~S found invalid keyword \047~S\047~%Available keywords: ~S");
lf[35]=C_h_intern(&lf[35],7,"\003sysmap");
lf[36]=C_h_intern(&lf[36],3,"car");
lf[37]=C_static_string(C_heaptop,32,"~S expected keyword but got \047~S\047");
lf[38]=C_h_intern(&lf[38],8,"keyword\077");
lf[39]=C_static_string(C_heaptop,35,"~S expected ~A arguments but got ~A");
lf[40]=C_static_lambda_info(C_heaptop,24,"(do74 key76 arg77 pos78)");
lf[41]=C_h_intern(&lf[41],6,"append");
lf[42]=C_static_string(C_heaptop,24,"~S is an invalid message");
lf[43]=C_static_lambda_info(C_heaptop,6,"(a553)");
lf[44]=C_h_intern(&lf[44],14,"hash-table-ref");
lf[45]=C_h_intern(&lf[45],14,"symbol->string");
lf[46]=C_static_lambda_info(C_heaptop,27,"(expand-send mesg64 data65)");
lf[47]=C_h_intern(&lf[47],7,"mp:note");
lf[48]=C_static_lambda_info(C_heaptop,46,"(mp:note time100 dur101 key102 amp103 chan104)");
lf[49]=C_h_intern(&lf[49],5,"mp:on");
lf[50]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[51]=C_static_lambda_info(C_heaptop,37,"(mp:on time105 key106 vel107 chan108)");
lf[52]=C_h_intern(&lf[52],6,"mp:off");
lf[53]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[54]=C_static_lambda_info(C_heaptop,38,"(mp:off time109 key110 vel111 chan112)");
lf[55]=C_h_intern(&lf[55],7,"mp:prog");
lf[56]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[57]=C_static_lambda_info(C_heaptop,33,"(mp:prog time113 prog114 chan115)");
lf[58]=C_h_intern(&lf[58],7,"mp:ctrl");
lf[59]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[60]=C_static_lambda_info(C_heaptop,40,"(mp:ctrl time116 ctrl117 val118 chan119)");
lf[61]=C_h_intern(&lf[61],9,"mp:alloff");
lf[62]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[63]=C_static_lambda_info(C_heaptop,11,"(mp:alloff)");
lf[64]=C_h_intern(&lf[64],8,"mp:micro");
lf[65]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[66]=C_static_lambda_info(C_heaptop,18,"(mp:micro divs120)");
lf[67]=C_h_intern(&lf[67],9,"mp:inhook");
lf[68]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[69]=C_static_lambda_info(C_heaptop,19,"(mp:inhook func121)");
lf[70]=C_h_intern(&lf[70],9,"expand-go");
lf[71]=C_h_intern(&lf[71],4,"else");
lf[72]=C_h_intern(&lf[72],4,"cond");
lf[73]=C_h_intern(&lf[73],6,"lambda");
lf[74]=C_h_intern(&lf[74],7,"elapsed");
lf[75]=C_h_intern(&lf[75],1,"x");
lf[76]=C_h_intern(&lf[76],4,"set!");
lf[77]=C_h_intern(&lf[77],4,"wait");
lf[78]=C_h_intern(&lf[78],4,"let*");
lf[79]=C_h_intern(&lf[79],3,"exn");
lf[80]=C_h_intern(&lf[80],5,"quote");
lf[81]=C_h_intern(&lf[81],7,"message");
lf[82]=C_h_intern(&lf[82],27,"condition-property-accessor");
lf[83]=C_h_intern(&lf[83],6,"printf");
lf[84]=C_static_string(C_heaptop,47,">>> Aborting process at time ~S:~%    Error: ~S");
lf[85]=C_h_intern(&lf[85],14,"condition-case");
lf[86]=C_h_intern(&lf[86],10,"\003sysappend");
lf[87]=C_h_intern(&lf[87],6,"safety");
lf[88]=C_h_intern(&lf[88],4,"cdar");
lf[89]=C_static_string(C_heaptop,19,"unknown declaration");
lf[90]=C_h_intern(&lf[90],4,"caar");
lf[91]=C_static_string(C_heaptop,31,"declaration not list (decl val)");
lf[92]=C_static_lambda_info(C_heaptop,15,"(do146 decl148)");
lf[93]=C_h_intern(&lf[93],7,"declare");
lf[94]=C_h_intern(&lf[94],6,"gensym");
lf[95]=C_h_intern(&lf[95],5,"\000null");
lf[96]=C_static_string(C_heaptop,41,"binding clause not list (var init [step])");
lf[97]=C_static_lambda_info(C_heaptop,15,"(do131 tail133)");
lf[98]=C_static_string(C_heaptop,36,"go stopping clause missing test form");
lf[99]=C_static_string(C_heaptop,29,"go stopping clause not a list");
lf[100]=C_static_string(C_heaptop,22,"go bindings not a list");
lf[101]=C_static_lambda_info(C_heaptop,44,"(expand-go bindings125 terminate126 body127)");
lf[102]=C_h_intern(&lf[102],14,"return-to-host");
lf[103]=C_static_lambda_info(C_heaptop,42,"(a1072 bindings122 terminate123 . body124)");
lf[104]=C_h_intern(&lf[104],18,"\003sysregister-macro");
lf[105]=C_h_intern(&lf[105],2,"go");
lf[106]=C_h_intern(&lf[106],15,"hash-table-set!");
lf[107]=C_static_string(C_heaptop,9,"mp:inhook");
tmp=C_intern(C_heaptop,9,"mp:inhook");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000func");
C_save(tmp);
tmp=C_SCHEME_FALSE;
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[108]=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
lf[109]=C_static_string(C_heaptop,8,"mp:micro");
tmp=C_intern(C_heaptop,8,"mp:micro");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000divs");
C_save(tmp);
tmp=C_fix(1);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[110]=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
lf[111]=C_static_string(C_heaptop,9,"mp:alloff");
tmp=C_intern(C_heaptop,9,"mp:alloff");
C_save(tmp);
tmp=C_SCHEME_END_OF_LIST;
lf[112]=C_h_pair(C_restore,tmp);
lf[113]=C_static_string(C_heaptop,7,"mp:ctrl");
tmp=C_intern(C_heaptop,7,"mp:ctrl");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000time");
C_save(tmp);
tmp=C_fix(0);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000ctrl");
C_save(tmp);
tmp=C_fix(60);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,4,"\000val");
C_save(tmp);
tmp=C_fix(0);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000chan");
C_save(tmp);
tmp=C_fix(1);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[114]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[115]=C_static_string(C_heaptop,7,"mp:prog");
tmp=C_intern(C_heaptop,7,"mp:prog");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000time");
C_save(tmp);
tmp=C_fix(0);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000prog");
C_save(tmp);
tmp=C_fix(60);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000chan");
C_save(tmp);
tmp=C_fix(0);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[116]=C_h_list(4,C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(4);
lf[117]=C_static_string(C_heaptop,6,"mp:off");
tmp=C_intern(C_heaptop,6,"mp:off");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000time");
C_save(tmp);
tmp=C_fix(0);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,4,"\000key");
C_save(tmp);
tmp=C_fix(60);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,4,"\000vel");
C_save(tmp);
tmp=C_fix(64);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000chan");
C_save(tmp);
tmp=C_fix(1);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[118]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[119]=C_static_string(C_heaptop,5,"mp:on");
tmp=C_intern(C_heaptop,5,"mp:on");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000time");
C_save(tmp);
tmp=C_fix(0);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,4,"\000key");
C_save(tmp);
tmp=C_fix(60);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,4,"\000vel");
C_save(tmp);
tmp=C_fix(64);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000chan");
C_save(tmp);
tmp=C_fix(1);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[120]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[121]=C_static_string(C_heaptop,7,"mp:note");
tmp=C_intern(C_heaptop,7,"mp:note");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000time");
C_save(tmp);
tmp=C_fix(0);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,4,"\000dur");
C_save(tmp);
tmp=C_flonum(C_heaptop,0.5);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,4,"\000key");
C_save(tmp);
tmp=C_fix(60);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,4,"\000amp");
C_save(tmp);
tmp=C_fix(127);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000chan");
C_save(tmp);
tmp=C_fix(1);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[122]=C_h_list(6,C_pick(5),C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(6);
lf[123]=C_static_lambda_info(C_heaptop,23,"(a1078 mess98 . data99)");
lf[124]=C_h_intern(&lf[124],4,"send");
lf[125]=C_h_intern(&lf[125],10,"*messages*");
lf[126]=C_h_intern(&lf[126],14,"string->symbol");
lf[127]=C_static_string(C_heaptop,51,"message function not string, symbol or list of both");
lf[128]=C_static_lambda_info(C_heaptop,21,"(a1084 func56 info57)");
lf[129]=C_h_intern(&lf[129],19,"define-send-message");
lf[130]=C_h_intern(&lf[130],15,"make-hash-table");
lf[131]=C_h_intern(&lf[131],6,"equal\077");
lf[132]=C_static_lambda_info(C_heaptop,10,"(toplevel)");
C_register_lf2(lf,133,create_ptable());
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_201,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_library_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k199 */
static void C_ccall f_201(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_201,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_204,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_eval_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k202 in k199 */
static void C_ccall f_204(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_204,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_207,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k205 in k202 in k199 */
static void C_ccall f_207(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_207,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_210,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k208 in k205 in k202 in k199 */
static void C_ccall f_210(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_210,2,t0,t1);}
t2=C_mutate((C_word*)lf[0]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_212,a[2]=lf[2],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[3]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_226,a[2]=lf[4],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate((C_word*)lf[5]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_240,a[2]=lf[8],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate((C_word*)lf[9]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_253,a[2]=lf[11],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[12]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_266,a[2]=lf[14],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate((C_word*)lf[15]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_295,a[2]=lf[17],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate((C_word*)lf[18]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_301,a[2]=lf[20],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate((C_word*)lf[21]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_307,a[2]=lf[22],tmp=(C_word)a,a+=3,tmp));
t10=C_mutate((C_word*)lf[23]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_317,a[2]=lf[24],tmp=(C_word)a,a+=3,tmp));
t11=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_322,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 100  make-hash-table");
t12=C_retrieve(lf[130]);
((C_proc3)C_retrieve_proc(t12))(3,t12,t11,*((C_word*)lf[131]+1));}

/* k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_322(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_322,2,t0,t1);}
t2=C_mutate(&lf[25],t1);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_325,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1085,a[2]=lf[128],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 102  ##sys#register-macro");
t5=C_retrieve(lf[104]);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,lf[129],t4);}

/* a1084 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_1085(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word t12;
C_word t13;
C_word t14;
C_word t15;
C_word ab[18],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_1085,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_1089,a[2]=t6,a[3]=t1,a[4]=t3,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t4)[1]))){
t8=(C_word)C_i_car(((C_word*)t4)[1]);
t9=C_set_block_item(t6,0,t8);
t10=(C_word)C_i_cadr(((C_word*)t4)[1]);
t11=C_set_block_item(t4,0,t10);
t12=t7;
f_1089(2,t12,t11);}
else{
if(C_truep((C_word)C_i_stringp(((C_word*)t4)[1]))){
t8=C_set_block_item(t6,0,((C_word*)t4)[1]);
t9=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1122,a[2]=t7,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 109  string->symbol");
t10=*((C_word*)lf[126]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)t4)[1]);}
else{
if(C_truep((C_word)C_i_symbolp(((C_word*)t4)[1]))){
t8=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1132,a[2]=t7,a[3]=t6,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 111  symbol->string");
t9=*((C_word*)lf[45]+1);
((C_proc3)C_retrieve_proc(t9))(3,t9,t8,((C_word*)t4)[1]);}
else{
C_trace("ChickenBridge.scm: 113  error");
t8=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,lf[127]);}}}}

/* k1130 in a1084 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_1132(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_1089(2,t3,t2);}

/* k1120 in a1084 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_1122(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_1089(2,t3,t2);}

/* k1087 in a1084 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_1089(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1089,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[4]);
t3=(C_word)C_a_i_list(&a,2,lf[80],t2);
t4=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_a_i_list(&a,4,lf[106],lf[125],((C_word*)((C_word*)t0)[2])[1],t3));}

/* k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_325(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_325,2,t0,t1);}
t2=C_mutate(&lf[26],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_327,a[2]=lf[29],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[30]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_337,a[2]=lf[46],tmp=(C_word)a,a+=3,tmp));
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_564,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1079,a[2]=lf[123],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 189  ##sys#register-macro");
t6=C_retrieve(lf[104]);
((C_proc4)C_retrieve_proc(t6))(4,t6,t4,lf[124],t5);}

/* a1078 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_1079(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr3r,(void*)f_1079r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_1079r(t0,t1,t2,t3);}}

static void C_ccall f_1079r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_trace("ChickenBridge.scm: 190  expand-send");
t4=C_retrieve(lf[30]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t1,t2,t3);}

/* k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_564(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_564,2,t0,t1);}
t2=C_mutate((C_word*)lf[47]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_566,a[2]=lf[48],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[49]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_572,a[2]=lf[51],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate((C_word*)lf[52]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_578,a[2]=lf[54],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate((C_word*)lf[55]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_584,a[2]=lf[57],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[58]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_590,a[2]=lf[60],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate((C_word*)lf[61]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_596,a[2]=lf[63],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate((C_word*)lf[64]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_602,a[2]=lf[66],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate((C_word*)lf[67]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_608,a[2]=lf[69],tmp=(C_word)a,a+=3,tmp));
t10=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_615,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 217  hash-table-set!");
t11=C_retrieve(lf[106]);
((C_proc5)C_retrieve_proc(t11))(5,t11,t10,lf[25],lf[121],lf[122]);}

/* k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_615(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_615,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_618,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 218  hash-table-set!");
t3=C_retrieve(lf[106]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[25],lf[119],lf[120]);}

/* k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_618(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_618,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_621,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 219  hash-table-set!");
t3=C_retrieve(lf[106]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[25],lf[117],lf[118]);}

/* k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_621(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_621,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_624,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 220  hash-table-set!");
t3=C_retrieve(lf[106]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[25],lf[115],lf[116]);}

/* k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_624(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_624,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_627,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 221  hash-table-set!");
t3=C_retrieve(lf[106]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[25],lf[113],lf[114]);}

/* k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_627(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_627,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_630,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 222  hash-table-set!");
t3=C_retrieve(lf[106]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[25],lf[111],lf[112]);}

/* k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_630(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_630,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_633,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 223  hash-table-set!");
t3=C_retrieve(lf[106]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[25],lf[109],lf[110]);}

/* k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_633(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_633,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_636,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 224  hash-table-set!");
t3=C_retrieve(lf[106]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[25],lf[107],lf[108]);}

/* k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_636(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_636,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_639,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1073,a[2]=lf[103],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 246  ##sys#register-macro");
t4=C_retrieve(lf[104]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,lf[105],t3);}

/* a1072 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_1073(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr4r,(void*)f_1073r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest(a,C_rest_count(0));
f_1073r(t0,t1,t2,t3,t4);}}

static void C_ccall f_1073r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_trace("ChickenBridge.scm: 247  expand-go");
t5=C_retrieve(lf[70]);
((C_proc5)C_retrieve_proc(t5))(5,t5,t1,t2,t3,t4);}

/* k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_639(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_639,2,t0,t1);}
t2=C_mutate((C_word*)lf[70]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_641,a[2]=lf[101],tmp=(C_word)a,a+=3,tmp));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1071,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 356  return-to-host");
t4=C_retrieve(lf[102]);
((C_proc2)C_retrieve_proc(t4))(2,t4,t3);}

/* k1069 in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_1071(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_UNDEFINED);}

/* expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_641(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word t12;
C_word t13;
C_word ab[17],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_641,5,t0,t1,t2,t3,t4);}
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_SCHEME_END_OF_LIST;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=C_SCHEME_END_OF_LIST;
t9=(*a=C_VECTOR_TYPE|1,a[1]=t8,tmp=(C_word)a,a+=2,tmp);
t10=C_SCHEME_END_OF_LIST;
t11=(*a=C_VECTOR_TYPE|1,a[1]=t10,tmp=(C_word)a,a+=2,tmp);
t12=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_654,a[2]=t2,a[3]=t11,a[4]=t5,a[5]=t9,a[6]=t1,a[7]=t7,a[8]=t3,tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(t2))){
t13=t12;
f_654(2,t13,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 255  error");
t13=*((C_word*)lf[27]+1);
((C_proc4)C_retrieve_proc(t13))(4,t13,t12,lf[100],t2);}}

/* k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_654(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_654,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_657,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(((C_word*)t0)[8]))){
if(C_truep((C_word)C_i_nullp(((C_word*)t0)[8]))){
C_trace("ChickenBridge.scm: 259  error");
t3=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,lf[98]);}
else{
t3=t2;
f_657(2,t3,C_SCHEME_UNDEFINED);}}
else{
C_trace("ChickenBridge.scm: 257  error");
t3=*((C_word*)lf[27]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t2,lf[99],((C_word*)t0)[8]);}}

/* k655 in k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_657(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_657,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_660,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],tmp=(C_word)a,a+=8,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_908,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[7],a[5]=t4,a[6]=lf[97],tmp=(C_word)a,a+=7,tmp));
t6=((C_word*)t4)[1];
f_908(t6,t2,((C_word*)t0)[2]);}

/* do131 in k655 in k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_fcall f_908(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[16],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_908,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_918,a[2]=t1,a[3]=((C_word*)t0)[5],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_928,a[2]=t3,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=t2,tmp=(C_word)a,a+=7,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1016,a[2]=t4,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t7=(C_word)C_i_car(t2);
t8=(C_word)C_i_length(t7);
C_trace("ChickenBridge.scm: 263  <");
C_lessp(5,0,t6,C_fix(0),t8,C_fix(4));}
else{
t6=t4;
f_928(t6,C_SCHEME_FALSE);}}}

/* k1014 in do131 in k655 in k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_1016(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=(C_word)C_i_car(t2);
t4=((C_word*)t0)[2];
f_928(t4,(C_word)C_i_symbolp(t3));}
else{
t2=((C_word*)t0)[2];
f_928(t2,C_SCHEME_FALSE);}}

/* k926 in do131 in k655 in k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_fcall f_928(C_word t0,C_word t1){
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
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_928,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[6]);
t3=(C_word)C_i_car(t2);
t4=(C_word)C_i_car(((C_word*)t0)[6]);
t5=(C_word)C_i_cadr(t4);
t6=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_937,a[2]=t5,a[3]=t3,a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[5],tmp=(C_word)a,a+=8,tmp);
t7=(C_word)C_i_car(((C_word*)t0)[6]);
t8=(C_word)C_i_cddr(t7);
if(C_truep((C_word)C_i_nullp(t8))){
t9=t6;
f_937(t9,lf[95]);}
else{
t9=(C_word)C_i_car(((C_word*)t0)[6]);
t10=t6;
f_937(t10,(C_word)C_i_caddr(t9));}}
else{
t2=(C_word)C_i_car(((C_word*)t0)[6]);
C_trace("ChickenBridge.scm: 276  error");
t3=*((C_word*)lf[27]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[2],lf[96],t2);}}

/* k935 in k926 in do131 in k655 in k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_fcall f_937(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_937,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_941,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t3=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 271  append");
t4=*((C_word*)lf[41]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,((C_word*)((C_word*)t0)[7])[1],t3);}

/* k939 in k935 in k926 in do131 in k655 in k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_941(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_941,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_945,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
t4=(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 272  append");
t5=*((C_word*)lf[41]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,((C_word*)((C_word*)t0)[7])[1],t4);}

/* k943 in k939 in k935 in k926 in do131 in k655 in k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_945(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[20],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_945,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_949,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_953,a[2]=((C_word*)t0)[5],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_eqp(((C_word*)t0)[3],lf[95]);
if(C_truep(t5)){
t6=t4;
f_953(t6,C_SCHEME_END_OF_LIST);}
else{
t6=(C_word)C_a_i_list(&a,3,lf[76],((C_word*)t0)[2],((C_word*)t0)[3]);
t7=t4;
f_953(t7,(C_word)C_a_i_list(&a,1,t6));}}

/* k951 in k943 in k939 in k935 in k926 in do131 in k655 in k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_fcall f_953(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 273  append");
t2=*((C_word*)lf[41]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k947 in k943 in k939 in k935 in k926 in do131 in k655 in k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_949(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_918(2,t3,t2);}

/* k916 in do131 in k655 in k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_918(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_908(t3,((C_word*)t0)[2],t2);}

/* k658 in k655 in k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_660(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_660,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_663,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 278  gensym");
t3=C_retrieve(lf[94]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k661 in k658 in k655 in k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_663(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_663,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_666,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 279  gensym");
t3=C_retrieve(lf[94]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k664 in k661 in k658 in k655 in k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_666(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_666,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_669,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 280  gensym");
t3=C_retrieve(lf[94]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k667 in k664 in k661 in k658 in k655 in k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_669(C_word c,C_word t0,C_word t1){
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
C_word ab[25],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_669,2,t0,t1);}
t2=C_SCHEME_TRUE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_SCHEME_END_OF_LIST;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_672,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=t3,a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[5],a[8]=((C_word*)t0)[6],a[9]=((C_word*)t0)[7],a[10]=((C_word*)t0)[8],a[11]=t5,a[12]=((C_word*)t0)[9],tmp=(C_word)a,a+=13,tmp);
t7=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_801,a[2]=t6,a[3]=t3,a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)((C_word*)t0)[3])[1]))){
t8=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
if(C_truep((C_word)C_i_pairp(t8))){
t9=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_902,a[2]=t7,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 286  caar");
t10=*((C_word*)lf[90]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)((C_word*)t0)[3])[1]);}
else{
t9=t7;
f_801(t9,C_SCHEME_FALSE);}}
else{
t8=t7;
f_801(t8,C_SCHEME_FALSE);}}

/* k900 in k667 in k664 in k661 in k658 in k655 in k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_902(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_801(t2,(C_word)C_eqp(t1,lf[93]));}

/* k799 in k667 in k664 in k661 in k658 in k655 in k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_fcall f_801(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_801,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_808,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 287  cdar");
t3=*((C_word*)lf[88]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)((C_word*)t0)[4])[1]);}
else{
t2=((C_word*)t0)[2];
f_672(2,t2,C_SCHEME_UNDEFINED);}}

/* k806 in k799 in k667 in k664 in k661 in k658 in k655 in k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_808(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_808,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_810,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=lf[92],tmp=(C_word)a,a+=6,tmp));
t5=((C_word*)t3)[1];
f_810(t5,((C_word*)t0)[2],t1);}

/* do146 in k806 in k799 in k667 in k664 in k661 in k658 in k655 in k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_fcall f_810(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[13],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_810,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[4])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[4])+1,t3);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,t4);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_824,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_834,a[2]=t2,a[3]=((C_word*)t0)[2],a[4]=t3,tmp=(C_word)a,a+=5,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_882,a[2]=t4,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 291  cdar");
t7=*((C_word*)lf[88]+1);
((C_proc3)C_retrieve_proc(t7))(3,t7,t6,t2);}
else{
t6=t4;
f_834(t6,C_SCHEME_FALSE);}}}

/* k880 in do146 in k806 in k799 in k667 in k664 in k661 in k658 in k655 in k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_882(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_834(t2,(C_word)C_i_pairp(t1));}

/* k832 in do146 in k806 in k799 in k667 in k664 in k661 in k658 in k655 in k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_fcall f_834(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_834,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_837,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 292  caar");
t3=*((C_word*)lf[90]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)t0)[2]);}
else{
t2=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 298  error");
t3=*((C_word*)lf[27]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[4],lf[91],t2);}}

/* k835 in k832 in do146 in k806 in k799 in k667 in k664 in k661 in k658 in k655 in k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_837(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_837,2,t0,t1);}
t2=(C_word)C_eqp(t1,lf[87]);
if(C_truep(t2)){
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_858,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 294  cdar");
t4=*((C_word*)lf[88]+1);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)t0)[2]);}
else{
t3=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 297  error");
t4=*((C_word*)lf[27]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,((C_word*)t0)[4],lf[89],t3);}}

/* k856 in k835 in k832 in do146 in k806 in k799 in k667 in k664 in k661 in k658 in k655 in k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_858(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep((C_word)C_i_car(t1))){
t2=((C_word*)t0)[3];
f_824(2,t2,C_SCHEME_UNDEFINED);}
else{
t2=C_set_block_item(((C_word*)t0)[2],0,C_SCHEME_FALSE);
t3=((C_word*)t0)[3];
f_824(2,t3,t2);}}

/* k822 in do146 in k806 in k799 in k667 in k664 in k661 in k658 in k655 in k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_824(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_810(t3,((C_word*)t0)[2],t2);}

/* k670 in k667 in k664 in k661 in k658 in k655 in k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_672(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[16],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_672,2,t0,t1);}
t2=(C_word)C_i_car(((C_word*)t0)[12]);
t3=(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_790,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],a[10]=((C_word*)t0)[10],a[11]=((C_word*)t0)[11],a[12]=t2,tmp=(C_word)a,a+=13,tmp);
t4=(C_word)C_i_cdr(((C_word*)t0)[12]);
t5=(C_word)C_a_i_list(&a,1,C_fix(-1));
C_trace("ChickenBridge.scm: 250  ##sys#append");
t6=*((C_word*)lf[86]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t3,t4,t5);}

/* k788 in k670 in k667 in k664 in k661 in k658 in k655 in k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_790(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_790,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[12],t1);
t3=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_774,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],a[8]=((C_word*)t0)[10],a[9]=((C_word*)t0)[11],a[10]=t2,tmp=(C_word)a,a+=11,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_778,a[2]=((C_word*)t0)[3],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_a_i_list(&a,1,((C_word*)t0)[9]);
C_trace("ChickenBridge.scm: 250  ##sys#append");
t6=*((C_word*)lf[86]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t4,((C_word*)((C_word*)t0)[2])[1],t5);}

/* k776 in k788 in k670 in k667 in k664 in k661 in k658 in k655 in k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_778(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 250  ##sys#append");
t2=*((C_word*)lf[86]+1);
((C_proc4)(void*)(*((C_word*)t2+1)))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k772 in k788 in k670 in k667 in k664 in k661 in k658 in k655 in k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_774(C_word c,C_word t0,C_word t1){
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
C_word t13;
C_word t14;
C_word t15;
C_word ab[83],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_774,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,lf[71],t1);
t3=(C_word)C_a_i_list(&a,3,lf[72],((C_word*)t0)[10],t2);
t4=C_mutate(((C_word *)((C_word*)t0)[9])+1,t3);
t5=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_679,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[9],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],tmp=(C_word)a,a+=8,tmp);
if(C_truep(((C_word*)((C_word*)t0)[3])[1])){
t6=(C_word)C_a_i_list(&a,1,lf[79]);
t7=(C_word)C_a_i_list(&a,2,lf[80],lf[79]);
t8=(C_word)C_a_i_list(&a,2,lf[80],lf[81]);
t9=(C_word)C_a_i_list(&a,3,lf[82],t7,t8);
t10=(C_word)C_a_i_list(&a,2,t9,((C_word*)t0)[2]);
t11=(C_word)C_a_i_list(&a,4,lf[83],lf[84],((C_word*)t0)[8],t10);
t12=(C_word)C_a_i_list(&a,4,((C_word*)t0)[2],t6,t11,C_fix(-2));
t13=(C_word)C_a_i_list(&a,3,lf[85],((C_word*)((C_word*)t0)[9])[1],t12);
t14=C_mutate(((C_word *)((C_word*)t0)[9])+1,t13);
t15=t5;
f_679(t15,t14);}
else{
t6=t5;
f_679(t6,C_SCHEME_UNDEFINED);}}

/* k677 in k772 in k788 in k670 in k667 in k664 in k661 in k658 in k655 in k652 in expand-go in k637 in k634 in k631 in k628 in k625 in k622 in k619 in k616 in k613 in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_fcall f_679(C_word t0,C_word t1){
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
C_word t13;
C_word t14;
C_word ab[90],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_679,NULL,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,((C_word*)t0)[7]);
t3=(C_word)C_a_i_list(&a,2,((C_word*)t0)[6],C_fix(0));
t4=(C_word)C_a_i_list(&a,3,lf[73],C_SCHEME_END_OF_LIST,((C_word*)t0)[7]);
t5=(C_word)C_a_i_list(&a,2,lf[74],t4);
t6=(C_word)C_a_i_list(&a,1,lf[75]);
t7=(C_word)C_a_i_list(&a,3,lf[76],((C_word*)t0)[6],lf[75]);
t8=(C_word)C_a_i_list(&a,3,lf[73],t6,t7);
t9=(C_word)C_a_i_list(&a,2,lf[77],t8);
t10=(C_word)C_a_i_list(&a,3,t3,t5,t9);
t11=(C_word)C_a_i_list(&a,3,lf[78],t10,((C_word*)((C_word*)t0)[5])[1]);
t12=(C_word)C_a_i_list(&a,3,lf[73],t2,t11);
t13=(C_word)C_a_i_list(&a,3,lf[73],((C_word*)((C_word*)t0)[4])[1],t12);
t14=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t14+1)))(2,t14,(C_word)C_a_i_cons(&a,2,t13,((C_word*)((C_word*)t0)[2])[1]));}

/* mp:inhook in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_608(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_608,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 213  error");
t3=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[68]);}

/* mp:micro in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_602(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_602,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 211  error");
t3=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[65]);}

/* mp:alloff in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_596(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_596,2,t0,t1);}
C_trace("ChickenBridge.scm: 209  error");
t2=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,t1,lf[62]);}

/* mp:ctrl in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_590(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_590,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 207  error");
t6=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[59]);}

/* mp:prog in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_584(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_584,5,t0,t1,t2,t3,t4);}
C_trace("ChickenBridge.scm: 205  error");
t5=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t5))(3,t5,t1,lf[56]);}

/* mp:off in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_578(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_578,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 203  error");
t6=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[53]);}

/* mp:on in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_572(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_572,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 201  error");
t6=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[50]);}

/* mp:note in k562 in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_566(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
C_word tmp;
C_word t7;
C_word *a;
if(c!=7) C_bad_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr7,(void*)f_566,7,t0,t1,t2,t3,t4,t5,t6);}
C_trace("ChickenBridge.scm: 197  insert-midi-note");
t7=*((C_word*)lf[12]+1);
((C_proc7)C_retrieve_proc(t7))(7,t7,t1,t2,t3,t4,t5,t6);}

/* expand-send in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_337(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word ab[6],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_337,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_341,a[2]=t1,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_symbolp(t2))){
C_trace("ChickenBridge.scm: 120  symbol->string");
t6=*((C_word*)lf[45]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t5,t2);}
else{
t6=t5;
f_341(2,t6,t2);}}

/* k339 in expand-send in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_341(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_341,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_344,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_554,a[2]=lf[43],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 121  hash-table-ref");
t4=*((C_word*)lf[44]+1);
((C_proc5)C_retrieve_proc(t4))(5,t4,t2,lf[25],t1,t3);}

/* a553 in k339 in expand-send in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_554(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_554,2,t0,t1);}
t2=t1;
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}

/* k342 in k339 in expand-send in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_344(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_344,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_347,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=t1;
if(C_truep(t3)){
t4=t2;
f_347(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 122  ferror");
f_327(t2,lf[42],(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]));}}

/* k345 in k342 in k339 in expand-send in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_347(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_347,2,t0,t1);}
t2=((C_word*)((C_word*)t0)[5])[1];
t3=(C_word)C_i_car(((C_word*)t0)[4]);
t4=(C_word)C_i_cdr(((C_word*)t0)[4]);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(C_word)C_i_length(t4);
t8=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_359,a[2]=t7,a[3]=t2,a[4]=((C_word*)t0)[2],a[5]=t6,a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[3],a[8]=t4,a[9]=t3,tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 129  append");
t9=*((C_word*)lf[41]+1);
((C_proc4)C_retrieve_proc(t9))(4,t9,t8,t4,C_SCHEME_END_OF_LIST);}

/* k357 in k345 in k342 in k339 in expand-send in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_359(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[19],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_359,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_362,a[2]=((C_word*)t0)[7],a[3]=((C_word*)t0)[8],a[4]=t1,a[5]=((C_word*)t0)[9],tmp=(C_word)a,a+=6,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_407,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[5],a[8]=t4,a[9]=((C_word*)t0)[6],a[10]=lf[40],tmp=(C_word)a,a+=11,tmp));
t6=((C_word*)t4)[1];
f_407(t6,t2,C_SCHEME_FALSE,C_SCHEME_FALSE,C_fix(0));}

/* do74 in k357 in k345 in k342 in k339 in expand-send in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_fcall f_407(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word t12;
C_word ab[26],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_407,NULL,5,t0,t1,t2,t3,t4);}
t5=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[9])[1]))){
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,C_SCHEME_FALSE);}
else{
t8=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_417,a[2]=t7,a[3]=t6,a[4]=t5,a[5]=t1,a[6]=((C_word*)t0)[8],tmp=(C_word)a,a+=7,tmp);
t9=(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_423,a[2]=((C_word*)t0)[2],a[3]=t7,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=t6,a[8]=((C_word*)t0)[6],a[9]=t5,a[10]=((C_word*)t0)[9],a[11]=t8,a[12]=((C_word*)t0)[7],tmp=(C_word)a,a+=13,tmp);
t10=((C_word*)((C_word*)t0)[7])[1];
if(C_truep(t10)){
t11=t9;
f_423(2,t11,C_SCHEME_FALSE);}
else{
t11=(C_word)C_i_car(((C_word*)((C_word*)t0)[9])[1]);
C_trace("ChickenBridge.scm: 140  keyword?");
t12=C_retrieve(lf[38]);
((C_proc3)C_retrieve_proc(t12))(3,t12,t9,t11);}}}

/* k421 in do74 in k357 in k345 in k342 in k339 in expand-send in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_423(C_word c,C_word t0,C_word t1){
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
C_word t13;
C_word t14;
C_word ab[32],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_423,2,t0,t1);}
if(C_truep(t1)){
t2=C_set_block_item(((C_word*)t0)[12],0,C_SCHEME_TRUE);
t3=((C_word*)t0)[11];
f_417(t3,t2);}
else{
t2=((C_word*)((C_word*)t0)[12])[1];
if(C_truep(t2)){
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[10])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[9])+1,t3);
t5=(C_word)C_i_assoc(((C_word*)((C_word*)t0)[9])[1],((C_word*)t0)[8]);
t6=C_mutate(((C_word *)((C_word*)t0)[7])+1,t5);
t7=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[10])[1]);
t8=C_mutate(((C_word *)((C_word*)t0)[10])+1,t7);
t9=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_477,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[9],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[11],a[6]=((C_word*)t0)[10],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t10=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_532,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[9],a[5]=((C_word*)t0)[5],a[6]=t9,a[7]=((C_word*)t0)[10],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 160  keyword?");
t11=C_retrieve(lf[38]);
((C_proc3)C_retrieve_proc(t11))(3,t11,t10,((C_word*)((C_word*)t0)[9])[1]);}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_433,a[2]=((C_word*)t0)[11],a[3]=((C_word*)t0)[10],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[6],tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_nequalp(((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]))){
t4=(C_word)C_i_length(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 150  ferror");
f_327(t3,lf[39],(C_word)C_a_i_list(&a,3,((C_word*)t0)[5],((C_word*)t0)[2],t4));}
else{
t4=t3;
f_433(2,t4,C_SCHEME_UNDEFINED);}}}}

/* k431 in k421 in do74 in k357 in k345 in k342 in k339 in expand-send in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_433(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_433,2,t0,t1);}
t2=(C_word)C_i_list_tail(((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]);
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
t4=(C_word)C_i_set_car(t2,t3);
t5=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[3])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t5);
t7=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[4])[1],C_fix(1));
t8=C_mutate(((C_word *)((C_word*)t0)[4])+1,t7);
t9=((C_word*)t0)[2];
f_417(t9,t8);}

/* k530 in k421 in do74 in k357 in k345 in k342 in k339 in expand-send in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_532(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_532,2,t0,t1);}
if(C_truep(t1)){
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[7])[1]))){
C_trace("ChickenBridge.scm: 164  ferror");
f_327(((C_word*)t0)[6],lf[33],(C_word)C_a_i_list(&a,2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]));}
else{
t2=((C_word*)((C_word*)t0)[3])[1];
if(C_truep(t2)){
t3=((C_word*)t0)[6];
f_477(2,t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_528,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
C_trace("map");
t4=*((C_word*)lf[35]+1);
((C_proc4)(void*)(*((C_word*)t4+1)))(4,t4,t3,*((C_word*)lf[36]+1),((C_word*)t0)[2]);}}}
else{
C_trace("ChickenBridge.scm: 161  ferror");
f_327(((C_word*)t0)[6],lf[37],(C_word)C_a_i_list(&a,2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]));}}

/* k526 in k530 in k421 in do74 in k357 in k345 in k342 in k339 in expand-send in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_528(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_528,2,t0,t1);}
C_trace("ChickenBridge.scm: 167  ferror");
f_327(((C_word*)t0)[4],lf[34],(C_word)C_a_i_list(&a,3,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1));}

/* k475 in k421 in do74 in k357 in k345 in k342 in k339 in expand-send in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_477(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[14],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_477,2,t0,t1);}
t2=(C_word)C_i_member(((C_word*)((C_word*)t0)[8])[1],((C_word*)t0)[7]);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_483,a[2]=((C_word*)t0)[5],a[3]=t2,a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
if(C_truep(t2)){
t4=t3;
f_483(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 174  ferror");
f_327(t3,lf[32],(C_word)C_a_i_list(&a,3,((C_word*)t0)[4],((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]));}}

/* k481 in k475 in k421 in do74 in k357 in k345 in k342 in k339 in expand-send in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_483(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word *a;
t2=(C_word)C_i_car(((C_word*)((C_word*)t0)[4])[1]);
t3=(C_word)C_i_set_car(((C_word*)t0)[3],t2);
t4=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[4])[1]);
t5=C_mutate(((C_word *)((C_word*)t0)[4])+1,t4);
t6=((C_word*)t0)[2];
f_417(t6,t5);}

/* k415 in do74 in k357 in k345 in k342 in k339 in expand-send in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_fcall f_417(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[6])[1];
f_407(t2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k360 in k357 in k345 in k342 in k339 in expand-send in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_362(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_362,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_367,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=lf[31],tmp=(C_word)a,a+=7,tmp));
t5=((C_word*)t3)[1];
f_367(t5,((C_word*)t0)[2],((C_word*)t0)[4]);}

/* do91 in k360 in k357 in k345 in k342 in k339 in expand-send in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_fcall f_367(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_367,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[5],((C_word*)t0)[4]));}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_380,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_member(t4,((C_word*)t0)[2]))){
t5=(C_word)C_i_car(t2);
t6=(C_word)C_i_cadr(t5);
t7=t3;
f_380(t7,(C_word)C_i_set_car(t2,t6));}
else{
t5=t3;
f_380(t5,C_SCHEME_UNDEFINED);}}}

/* k378 in do91 in k360 in k357 in k345 in k342 in k339 in expand-send in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_fcall f_380(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_367(t3,((C_word*)t0)[2],t2);}

/* ferror in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_fcall f_327(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_327,NULL,3,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_335,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_apply(5,0,t4,C_retrieve(lf[28]),t2,t3);}

/* k333 in ferror in k323 in k320 in k208 in k205 in k202 in k199 */
static void C_ccall f_335(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 117  error");
t2=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* current-time-hi-res in k208 in k205 in k202 in k199 */
static void C_ccall f_317(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_317,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub53(t2));}

/* run_process in k208 in k205 in k202 in k199 */
static void C_ccall f_307(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_307,4,t0,t1,t2,t3);}
t4=(C_word)C_a_i_list(&a,1,t3);
C_apply(4,0,t1,t2,t4);}

/* make-note-off in k208 in k205 in k202 in k199 */
static void C_ccall f_301(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_301,5,t0,t1,t2,t3,t4);}
C_trace("ChickenBridge.scm: 88   insert-midi-on");
t5=C_retrieve(lf[16]);
((C_proc6)C_retrieve_proc(t5))(6,t5,t1,t2,t3,lf[19],t4);}

/* make-note-on in k208 in k205 in k202 in k199 */
static void C_ccall f_295(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_295,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 84   insert-midi-on");
t6=C_retrieve(lf[16]);
((C_proc6)C_retrieve_proc(t6))(6,t6,t1,t2,t3,t4,t5);}

/* insert-midi-note in k208 in k205 in k202 in k199 */
static void C_ccall f_266(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
C_word tmp;
C_word t7;
C_word t8;
C_word ab[8],*a=ab;
if(c!=7) C_bad_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr7,(void*)f_266,7,t0,t1,t2,t3,t4,t5,t6);}
t7=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_270,a[2]=t1,a[3]=t6,a[4]=t5,a[5]=t4,a[6]=t3,a[7]=t2,tmp=(C_word)a,a+=8,tmp);
C_trace("##sys#gc");
t8=C_retrieve(lf[7]);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,C_SCHEME_FALSE);}

/* k268 in insert-midi-note in k208 in k205 in k202 in k199 */
static void C_ccall f_270(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_270,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[7]);
t4=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[6]);
t5=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[5]);
t6=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[4]);
t7=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[3]);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub33,a[2]=lf[13],tmp=(C_word)a,a+=3,tmp);
((C_proc8)C_retrieve_proc(t8))(8,t8,((C_word*)t0)[2],t2,t3,t4,t5,t6,t7);}

/* insert-closure in k208 in k205 in k202 in k199 */
static void C_ccall f_253(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_253,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_257,a[2]=t3,a[3]=t1,a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("##sys#gc");
t5=C_retrieve(lf[7]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,C_SCHEME_FALSE);}

/* k255 in insert-closure in k208 in k205 in k202 in k199 */
static void C_ccall f_257(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_257,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[4]);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub22,a[2]=lf[10],tmp=(C_word)a,a+=3,tmp);
((C_proc5)C_retrieve_proc(t4))(5,t4,((C_word*)t0)[3],t2,t3,((C_word*)t0)[2]);}

/* insert-process in k208 in k205 in k202 in k199 */
static void C_ccall f_240(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_240,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_244,a[2]=t3,a[3]=t1,a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("##sys#gc");
t5=C_retrieve(lf[7]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,C_SCHEME_FALSE);}

/* k242 in insert-process in k208 in k205 in k202 in k199 */
static void C_ccall f_244(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_244,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[4]);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub14,a[2]=lf[6],tmp=(C_word)a,a+=3,tmp);
((C_proc5)C_retrieve_proc(t4))(5,t4,((C_word*)t0)[3],t2,t3,((C_word*)t0)[2]);}

/* print-error in k208 in k205 in k202 in k199 */
static void C_ccall f_226(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_226,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_231,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[1]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_231(2,t4,C_SCHEME_FALSE);}}

/* k229 in print-error in k208 in k205 in k202 in k199 */
static void C_ccall f_231(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub7(C_SCHEME_UNDEFINED,t1));}

/* print-message in k208 in k205 in k202 in k199 */
static void C_ccall f_212(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_212,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_217,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[1]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_217(2,t4,C_SCHEME_FALSE);}}

/* k215 in print-message in k208 in k205 in k202 in k199 */
static void C_ccall f_217(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub1(C_SCHEME_UNDEFINED,t1));}

#ifdef C_ENABLE_PTABLES
static C_PTABLE_ENTRY ptable[96] = {
{"toplevelChickenBridge.scm",(void*)C_grace_toplevel},
{"f_201ChickenBridge.scm",(void*)f_201},
{"f_204ChickenBridge.scm",(void*)f_204},
{"f_207ChickenBridge.scm",(void*)f_207},
{"f_210ChickenBridge.scm",(void*)f_210},
{"f_322ChickenBridge.scm",(void*)f_322},
{"f_1085ChickenBridge.scm",(void*)f_1085},
{"f_1132ChickenBridge.scm",(void*)f_1132},
{"f_1122ChickenBridge.scm",(void*)f_1122},
{"f_1089ChickenBridge.scm",(void*)f_1089},
{"f_325ChickenBridge.scm",(void*)f_325},
{"f_1079ChickenBridge.scm",(void*)f_1079},
{"f_564ChickenBridge.scm",(void*)f_564},
{"f_615ChickenBridge.scm",(void*)f_615},
{"f_618ChickenBridge.scm",(void*)f_618},
{"f_621ChickenBridge.scm",(void*)f_621},
{"f_624ChickenBridge.scm",(void*)f_624},
{"f_627ChickenBridge.scm",(void*)f_627},
{"f_630ChickenBridge.scm",(void*)f_630},
{"f_633ChickenBridge.scm",(void*)f_633},
{"f_636ChickenBridge.scm",(void*)f_636},
{"f_1073ChickenBridge.scm",(void*)f_1073},
{"f_639ChickenBridge.scm",(void*)f_639},
{"f_1071ChickenBridge.scm",(void*)f_1071},
{"f_641ChickenBridge.scm",(void*)f_641},
{"f_654ChickenBridge.scm",(void*)f_654},
{"f_657ChickenBridge.scm",(void*)f_657},
{"f_908ChickenBridge.scm",(void*)f_908},
{"f_1016ChickenBridge.scm",(void*)f_1016},
{"f_928ChickenBridge.scm",(void*)f_928},
{"f_937ChickenBridge.scm",(void*)f_937},
{"f_941ChickenBridge.scm",(void*)f_941},
{"f_945ChickenBridge.scm",(void*)f_945},
{"f_953ChickenBridge.scm",(void*)f_953},
{"f_949ChickenBridge.scm",(void*)f_949},
{"f_918ChickenBridge.scm",(void*)f_918},
{"f_660ChickenBridge.scm",(void*)f_660},
{"f_663ChickenBridge.scm",(void*)f_663},
{"f_666ChickenBridge.scm",(void*)f_666},
{"f_669ChickenBridge.scm",(void*)f_669},
{"f_902ChickenBridge.scm",(void*)f_902},
{"f_801ChickenBridge.scm",(void*)f_801},
{"f_808ChickenBridge.scm",(void*)f_808},
{"f_810ChickenBridge.scm",(void*)f_810},
{"f_882ChickenBridge.scm",(void*)f_882},
{"f_834ChickenBridge.scm",(void*)f_834},
{"f_837ChickenBridge.scm",(void*)f_837},
{"f_858ChickenBridge.scm",(void*)f_858},
{"f_824ChickenBridge.scm",(void*)f_824},
{"f_672ChickenBridge.scm",(void*)f_672},
{"f_790ChickenBridge.scm",(void*)f_790},
{"f_778ChickenBridge.scm",(void*)f_778},
{"f_774ChickenBridge.scm",(void*)f_774},
{"f_679ChickenBridge.scm",(void*)f_679},
{"f_608ChickenBridge.scm",(void*)f_608},
{"f_602ChickenBridge.scm",(void*)f_602},
{"f_596ChickenBridge.scm",(void*)f_596},
{"f_590ChickenBridge.scm",(void*)f_590},
{"f_584ChickenBridge.scm",(void*)f_584},
{"f_578ChickenBridge.scm",(void*)f_578},
{"f_572ChickenBridge.scm",(void*)f_572},
{"f_566ChickenBridge.scm",(void*)f_566},
{"f_337ChickenBridge.scm",(void*)f_337},
{"f_341ChickenBridge.scm",(void*)f_341},
{"f_554ChickenBridge.scm",(void*)f_554},
{"f_344ChickenBridge.scm",(void*)f_344},
{"f_347ChickenBridge.scm",(void*)f_347},
{"f_359ChickenBridge.scm",(void*)f_359},
{"f_407ChickenBridge.scm",(void*)f_407},
{"f_423ChickenBridge.scm",(void*)f_423},
{"f_433ChickenBridge.scm",(void*)f_433},
{"f_532ChickenBridge.scm",(void*)f_532},
{"f_528ChickenBridge.scm",(void*)f_528},
{"f_477ChickenBridge.scm",(void*)f_477},
{"f_483ChickenBridge.scm",(void*)f_483},
{"f_417ChickenBridge.scm",(void*)f_417},
{"f_362ChickenBridge.scm",(void*)f_362},
{"f_367ChickenBridge.scm",(void*)f_367},
{"f_380ChickenBridge.scm",(void*)f_380},
{"f_327ChickenBridge.scm",(void*)f_327},
{"f_335ChickenBridge.scm",(void*)f_335},
{"f_317ChickenBridge.scm",(void*)f_317},
{"f_307ChickenBridge.scm",(void*)f_307},
{"f_301ChickenBridge.scm",(void*)f_301},
{"f_295ChickenBridge.scm",(void*)f_295},
{"f_266ChickenBridge.scm",(void*)f_266},
{"f_270ChickenBridge.scm",(void*)f_270},
{"f_253ChickenBridge.scm",(void*)f_253},
{"f_257ChickenBridge.scm",(void*)f_257},
{"f_240ChickenBridge.scm",(void*)f_240},
{"f_244ChickenBridge.scm",(void*)f_244},
{"f_226ChickenBridge.scm",(void*)f_226},
{"f_231ChickenBridge.scm",(void*)f_231},
{"f_212ChickenBridge.scm",(void*)f_212},
{"f_217ChickenBridge.scm",(void*)f_217},
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
