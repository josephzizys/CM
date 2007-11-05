/* Generated from ChickenBridge.scm by the CHICKEN compiler
   http://www.call-with-current-continuation.org
   2007-11-05 15:59
   Version 2.731 - macosx-unix-gnu-ppc - [ manyargs dload ptables applyhook ]
(c)2000-2007 Felix L. Winkelmann | compiled 2007-10-29 on galen.local (Darwin)
   command line: ChickenBridge.scm -output-file ChickenBridge.cpp -quiet
   unit: grace
*/

#include "chicken.h"


#include "Grace.h"
#include "Scheme.h"
#include "OutputQueue.h"

void print_mess(char * st)
{
// ((GraceApp *)GraceApp::getInstance())->getConsole()->printMessage( String(st));
   printf("%s", st);
}

void print_error(char * st)
{
// ((GraceApp *)GraceApp::getInstance())->getConsole()->printError( String(st));
   printf("%s", st);
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

static C_TLS C_word lf[134];


/* from current-time-hi-res in k209 in k206 in k203 in k200 */
#define return(x) C_cblock C_r = (C_flonum(&C_a,(x))); goto C_ret; C_cblockend
static C_word C_fcall stub53(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub53(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
 C_return(Time::getMillisecondCounterHiRes());
C_ret:
#undef return

return C_r;}

/* from k292 */
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

/* from k263 */
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

/* from k250 */
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

/* from k230 in print-error in k209 in k206 in k203 in k200 */
static C_word C_fcall stub7(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub7(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_error(t0);
return C_r;}

/* from k216 in print-message in k209 in k206 in k203 in k200 */
static C_word C_fcall stub1(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub1(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_mess(t0);
return C_r;}

C_noret_decl(C_grace_toplevel)
C_externexport void C_ccall C_grace_toplevel(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_202)
static void C_ccall f_202(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_205)
static void C_ccall f_205(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_208)
static void C_ccall f_208(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_211)
static void C_ccall f_211(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_323)
static void C_ccall f_323(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1109)
static void C_ccall f_1109(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_1156)
static void C_ccall f_1156(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1146)
static void C_ccall f_1146(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1113)
static void C_ccall f_1113(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_326)
static void C_ccall f_326(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1103)
static void C_ccall f_1103(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_1103)
static void C_ccall f_1103r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_565)
static void C_ccall f_565(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_616)
static void C_ccall f_616(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_619)
static void C_ccall f_619(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_622)
static void C_ccall f_622(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_625)
static void C_ccall f_625(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_628)
static void C_ccall f_628(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_631)
static void C_ccall f_631(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_634)
static void C_ccall f_634(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_637)
static void C_ccall f_637(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1097)
static void C_ccall f_1097(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_1097)
static void C_ccall f_1097r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_640)
static void C_ccall f_640(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1095)
static void C_ccall f_1095(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_642)
static void C_ccall f_642(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_655)
static void C_ccall f_655(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_658)
static void C_ccall f_658(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_932)
static void C_fcall f_932(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_1040)
static void C_ccall f_1040(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_952)
static void C_fcall f_952(C_word t0,C_word t1) C_noret;
C_noret_decl(f_961)
static void C_fcall f_961(C_word t0,C_word t1) C_noret;
C_noret_decl(f_965)
static void C_ccall f_965(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_969)
static void C_ccall f_969(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_977)
static void C_fcall f_977(C_word t0,C_word t1) C_noret;
C_noret_decl(f_973)
static void C_ccall f_973(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_942)
static void C_ccall f_942(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_661)
static void C_ccall f_661(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_664)
static void C_ccall f_664(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_667)
static void C_ccall f_667(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_670)
static void C_ccall f_670(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_673)
static void C_ccall f_673(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_926)
static void C_ccall f_926(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_825)
static void C_fcall f_825(C_word t0,C_word t1) C_noret;
C_noret_decl(f_832)
static void C_ccall f_832(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_834)
static void C_fcall f_834(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_906)
static void C_ccall f_906(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_858)
static void C_fcall f_858(C_word t0,C_word t1) C_noret;
C_noret_decl(f_861)
static void C_ccall f_861(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_882)
static void C_ccall f_882(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_848)
static void C_ccall f_848(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_676)
static void C_ccall f_676(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_814)
static void C_ccall f_814(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_802)
static void C_ccall f_802(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_798)
static void C_ccall f_798(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_683)
static void C_fcall f_683(C_word t0,C_word t1) C_noret;
C_noret_decl(f_609)
static void C_ccall f_609(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_603)
static void C_ccall f_603(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_597)
static void C_ccall f_597(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_591)
static void C_ccall f_591(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_585)
static void C_ccall f_585(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_579)
static void C_ccall f_579(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_573)
static void C_ccall f_573(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_567)
static void C_ccall f_567(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_338)
static void C_ccall f_338(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_342)
static void C_ccall f_342(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_555)
static void C_ccall f_555(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_345)
static void C_ccall f_345(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_348)
static void C_ccall f_348(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_360)
static void C_ccall f_360(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_408)
static void C_fcall f_408(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_424)
static void C_ccall f_424(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_434)
static void C_ccall f_434(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_533)
static void C_ccall f_533(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_529)
static void C_ccall f_529(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_478)
static void C_ccall f_478(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_484)
static void C_ccall f_484(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_418)
static void C_fcall f_418(C_word t0,C_word t1) C_noret;
C_noret_decl(f_363)
static void C_ccall f_363(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_368)
static void C_fcall f_368(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_381)
static void C_fcall f_381(C_word t0,C_word t1) C_noret;
C_noret_decl(f_328)
static void C_fcall f_328(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_336)
static void C_ccall f_336(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_318)
static void C_ccall f_318(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_308)
static void C_ccall f_308(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_302)
static void C_ccall f_302(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_296)
static void C_ccall f_296(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_267)
static void C_ccall f_267(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_271)
static void C_ccall f_271(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_254)
static void C_ccall f_254(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_258)
static void C_ccall f_258(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_241)
static void C_ccall f_241(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_245)
static void C_ccall f_245(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_227)
static void C_ccall f_227(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_232)
static void C_ccall f_232(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_213)
static void C_ccall f_213(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_218)
static void C_ccall f_218(C_word c,C_word t0,C_word t1) C_noret;

/* from run_process */
 double  run_process(C_word t0,double t1){
C_word x, *a=C_alloc(0+3);
C_callback_adjust_stack_limits(a);
x=((C_word)t0);
C_save(x);
x=C_flonum(&a,t1);
C_save(x);
return C_c_double(C_callback_wrapper((void *)f_308,2));}

C_noret_decl(trf_932)
static void C_fcall trf_932(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_932(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_932(t0,t1,t2);}

C_noret_decl(trf_952)
static void C_fcall trf_952(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_952(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_952(t0,t1);}

C_noret_decl(trf_961)
static void C_fcall trf_961(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_961(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_961(t0,t1);}

C_noret_decl(trf_977)
static void C_fcall trf_977(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_977(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_977(t0,t1);}

C_noret_decl(trf_825)
static void C_fcall trf_825(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_825(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_825(t0,t1);}

C_noret_decl(trf_834)
static void C_fcall trf_834(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_834(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_834(t0,t1,t2);}

C_noret_decl(trf_858)
static void C_fcall trf_858(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_858(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_858(t0,t1);}

C_noret_decl(trf_683)
static void C_fcall trf_683(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_683(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_683(t0,t1);}

C_noret_decl(trf_408)
static void C_fcall trf_408(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_408(void *dummy){
C_word t4=C_pick(0);
C_word t3=C_pick(1);
C_word t2=C_pick(2);
C_word t1=C_pick(3);
C_word t0=C_pick(4);
C_adjust_stack(-5);
f_408(t0,t1,t2,t3,t4);}

C_noret_decl(trf_418)
static void C_fcall trf_418(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_418(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_418(t0,t1);}

C_noret_decl(trf_368)
static void C_fcall trf_368(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_368(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_368(t0,t1,t2);}

C_noret_decl(trf_381)
static void C_fcall trf_381(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_381(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_381(t0,t1);}

C_noret_decl(trf_328)
static void C_fcall trf_328(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_328(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_328(t0,t1,t2);}

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
if(!C_demand_2(1150)){
C_save(t1);
C_rereclaim2(1150*sizeof(C_word), 1);
t1=C_restore;}
a=C_alloc(3);
C_initialize_lf(lf,134);
lf[0]=C_h_intern(&lf[0],13,"print-message");
lf[1]=C_h_intern(&lf[1],17,"\003sysmake-c-string");
lf[2]=C_static_lambda_info(C_heaptop,19,"(print-message a04)");
lf[3]=C_h_intern(&lf[3],11,"print-error");
lf[4]=C_static_lambda_info(C_heaptop,18,"(print-error a610)");
lf[5]=C_h_intern(&lf[5],14,"insert-process");
lf[6]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[7]=C_h_intern(&lf[7],6,"\003sysgc");
lf[8]=C_static_lambda_info(C_heaptop,28,"(insert-process a1316 a1217)");
lf[9]=C_h_intern(&lf[9],14,"insert-closure");
lf[10]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
lf[11]=C_static_lambda_info(C_heaptop,28,"(insert-closure a2124 a2025)");
lf[12]=C_h_intern(&lf[12],16,"insert-midi-note");
lf[13]=C_static_lambda_info(C_heaptop,3,"\000\000\000");
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
lf[43]=C_static_lambda_info(C_heaptop,6,"(a554)");
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
lf[79]=C_h_intern(&lf[79],5,"quote");
lf[80]=C_h_intern(&lf[80],3,"exn");
lf[81]=C_h_intern(&lf[81],7,"message");
lf[82]=C_h_intern(&lf[82],27,"condition-property-accessor");
lf[83]=C_h_intern(&lf[83],6,"printf");
lf[84]=C_static_string(C_heaptop,47,">>> Aborting process at time ~S:~%    Error: ~S");
lf[85]=C_h_intern(&lf[85],22,"with-exception-handler");
lf[86]=C_h_intern(&lf[86],30,"call-with-current-continuation");
lf[87]=C_h_intern(&lf[87],10,"\003sysappend");
lf[88]=C_h_intern(&lf[88],6,"safety");
lf[89]=C_h_intern(&lf[89],4,"cdar");
lf[90]=C_static_string(C_heaptop,19,"unknown declaration");
lf[91]=C_h_intern(&lf[91],4,"caar");
lf[92]=C_static_string(C_heaptop,31,"declaration not list (decl val)");
lf[93]=C_static_lambda_info(C_heaptop,15,"(do147 decl149)");
lf[94]=C_h_intern(&lf[94],7,"declare");
lf[95]=C_h_intern(&lf[95],6,"gensym");
lf[96]=C_h_intern(&lf[96],5,"\000null");
lf[97]=C_static_string(C_heaptop,41,"binding clause not list (var init [step])");
lf[98]=C_static_lambda_info(C_heaptop,15,"(do131 tail133)");
lf[99]=C_static_string(C_heaptop,36,"go stopping clause missing test form");
lf[100]=C_static_string(C_heaptop,29,"go stopping clause not a list");
lf[101]=C_static_string(C_heaptop,22,"go bindings not a list");
lf[102]=C_static_lambda_info(C_heaptop,44,"(expand-go bindings125 terminate126 body127)");
lf[103]=C_h_intern(&lf[103],14,"return-to-host");
lf[104]=C_static_lambda_info(C_heaptop,42,"(a1096 bindings122 terminate123 . body124)");
lf[105]=C_h_intern(&lf[105],18,"\003sysregister-macro");
lf[106]=C_h_intern(&lf[106],2,"go");
lf[107]=C_h_intern(&lf[107],15,"hash-table-set!");
lf[108]=C_static_string(C_heaptop,9,"mp:inhook");
tmp=C_intern(C_heaptop,9,"mp:inhook");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000func");
C_save(tmp);
tmp=C_SCHEME_FALSE;
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[109]=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
lf[110]=C_static_string(C_heaptop,8,"mp:micro");
tmp=C_intern(C_heaptop,8,"mp:micro");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000divs");
C_save(tmp);
tmp=C_fix(1);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[111]=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
lf[112]=C_static_string(C_heaptop,9,"mp:alloff");
tmp=C_intern(C_heaptop,9,"mp:alloff");
C_save(tmp);
tmp=C_SCHEME_END_OF_LIST;
lf[113]=C_h_pair(C_restore,tmp);
lf[114]=C_static_string(C_heaptop,7,"mp:ctrl");
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
lf[115]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[116]=C_static_string(C_heaptop,7,"mp:prog");
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
lf[117]=C_h_list(4,C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(4);
lf[118]=C_static_string(C_heaptop,6,"mp:off");
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
lf[119]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[120]=C_static_string(C_heaptop,5,"mp:on");
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
lf[121]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[122]=C_static_string(C_heaptop,7,"mp:note");
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
lf[123]=C_h_list(6,C_pick(5),C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(6);
lf[124]=C_static_lambda_info(C_heaptop,23,"(a1102 mess98 . data99)");
lf[125]=C_h_intern(&lf[125],4,"send");
lf[126]=C_h_intern(&lf[126],10,"*messages*");
lf[127]=C_h_intern(&lf[127],14,"string->symbol");
lf[128]=C_static_string(C_heaptop,51,"message function not string, symbol or list of both");
lf[129]=C_static_lambda_info(C_heaptop,21,"(a1108 func56 info57)");
lf[130]=C_h_intern(&lf[130],19,"define-send-message");
lf[131]=C_h_intern(&lf[131],15,"make-hash-table");
lf[132]=C_h_intern(&lf[132],6,"equal\077");
lf[133]=C_static_lambda_info(C_heaptop,10,"(toplevel)");
C_register_lf2(lf,134,create_ptable());
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_202,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_library_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k200 */
static void C_ccall f_202(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_202,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_205,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_eval_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k203 in k200 */
static void C_ccall f_205(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_205,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_208,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k206 in k203 in k200 */
static void C_ccall f_208(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_208,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_211,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k209 in k206 in k203 in k200 */
static void C_ccall f_211(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_211,2,t0,t1);}
t2=C_mutate((C_word*)lf[0]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_213,a[2]=lf[2],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[3]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_227,a[2]=lf[4],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate((C_word*)lf[5]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_241,a[2]=lf[8],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate((C_word*)lf[9]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_254,a[2]=lf[11],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[12]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_267,a[2]=lf[14],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate((C_word*)lf[15]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_296,a[2]=lf[17],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate((C_word*)lf[18]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_302,a[2]=lf[20],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate((C_word*)lf[21]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_308,a[2]=lf[22],tmp=(C_word)a,a+=3,tmp));
t10=C_mutate((C_word*)lf[23]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_318,a[2]=lf[24],tmp=(C_word)a,a+=3,tmp));
t11=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_323,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 99   make-hash-table");
t12=C_retrieve(lf[131]);
((C_proc3)C_retrieve_proc(t12))(3,t12,t11,*((C_word*)lf[132]+1));}

/* k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_323(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_323,2,t0,t1);}
t2=C_mutate(&lf[25],t1);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_326,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1109,a[2]=lf[129],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 101  ##sys#register-macro");
t5=C_retrieve(lf[105]);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,lf[130],t4);}

/* a1108 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_1109(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_1109,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_1113,a[2]=t6,a[3]=t1,a[4]=t3,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t4)[1]))){
t8=(C_word)C_i_car(((C_word*)t4)[1]);
t9=C_set_block_item(t6,0,t8);
t10=(C_word)C_i_cadr(((C_word*)t4)[1]);
t11=C_set_block_item(t4,0,t10);
t12=t7;
f_1113(2,t12,t11);}
else{
if(C_truep((C_word)C_i_stringp(((C_word*)t4)[1]))){
t8=C_set_block_item(t6,0,((C_word*)t4)[1]);
t9=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1146,a[2]=t7,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 108  string->symbol");
t10=*((C_word*)lf[127]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)t4)[1]);}
else{
if(C_truep((C_word)C_i_symbolp(((C_word*)t4)[1]))){
t8=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1156,a[2]=t7,a[3]=t6,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 110  symbol->string");
t9=*((C_word*)lf[45]+1);
((C_proc3)C_retrieve_proc(t9))(3,t9,t8,((C_word*)t4)[1]);}
else{
C_trace("ChickenBridge.scm: 112  error");
t8=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,lf[128]);}}}}

/* k1154 in a1108 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_1156(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_1113(2,t3,t2);}

/* k1144 in a1108 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_1146(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_1113(2,t3,t2);}

/* k1111 in a1108 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_1113(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1113,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[4]);
t3=(C_word)C_a_i_list(&a,2,lf[79],t2);
t4=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_a_i_list(&a,4,lf[107],lf[126],((C_word*)((C_word*)t0)[2])[1],t3));}

/* k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_326(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_326,2,t0,t1);}
t2=C_mutate(&lf[26],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_328,a[2]=lf[29],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[30]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_338,a[2]=lf[46],tmp=(C_word)a,a+=3,tmp));
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_565,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1103,a[2]=lf[124],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 188  ##sys#register-macro");
t6=C_retrieve(lf[105]);
((C_proc4)C_retrieve_proc(t6))(4,t6,t4,lf[125],t5);}

/* a1102 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_1103(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr3r,(void*)f_1103r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_1103r(t0,t1,t2,t3);}}

static void C_ccall f_1103r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_trace("ChickenBridge.scm: 189  expand-send");
t4=C_retrieve(lf[30]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t1,t2,t3);}

/* k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_565(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_565,2,t0,t1);}
t2=C_mutate((C_word*)lf[47]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_567,a[2]=lf[48],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[49]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_573,a[2]=lf[51],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate((C_word*)lf[52]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_579,a[2]=lf[54],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate((C_word*)lf[55]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_585,a[2]=lf[57],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[58]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_591,a[2]=lf[60],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate((C_word*)lf[61]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_597,a[2]=lf[63],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate((C_word*)lf[64]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_603,a[2]=lf[66],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate((C_word*)lf[67]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_609,a[2]=lf[69],tmp=(C_word)a,a+=3,tmp));
t10=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_616,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 216  hash-table-set!");
t11=C_retrieve(lf[107]);
((C_proc5)C_retrieve_proc(t11))(5,t11,t10,lf[25],lf[122],lf[123]);}

/* k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_616(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_616,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_619,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 217  hash-table-set!");
t3=C_retrieve(lf[107]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[25],lf[120],lf[121]);}

/* k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_619(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_619,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_622,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 218  hash-table-set!");
t3=C_retrieve(lf[107]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[25],lf[118],lf[119]);}

/* k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_622(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_622,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_625,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 219  hash-table-set!");
t3=C_retrieve(lf[107]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[25],lf[116],lf[117]);}

/* k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_625(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_625,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_628,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 220  hash-table-set!");
t3=C_retrieve(lf[107]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[25],lf[114],lf[115]);}

/* k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_628(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_628,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_631,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 221  hash-table-set!");
t3=C_retrieve(lf[107]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[25],lf[112],lf[113]);}

/* k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_631(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_631,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_634,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 222  hash-table-set!");
t3=C_retrieve(lf[107]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[25],lf[110],lf[111]);}

/* k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_634(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_634,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_637,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 223  hash-table-set!");
t3=C_retrieve(lf[107]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[25],lf[108],lf[109]);}

/* k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_637(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_637,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_640,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1097,a[2]=lf[104],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 245  ##sys#register-macro");
t4=C_retrieve(lf[105]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,lf[106],t3);}

/* a1096 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_1097(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr4r,(void*)f_1097r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest(a,C_rest_count(0));
f_1097r(t0,t1,t2,t3,t4);}}

static void C_ccall f_1097r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_trace("ChickenBridge.scm: 246  expand-go");
t5=C_retrieve(lf[70]);
((C_proc5)C_retrieve_proc(t5))(5,t5,t1,t2,t3,t4);}

/* k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_640(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_640,2,t0,t1);}
t2=C_mutate((C_word*)lf[70]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_642,a[2]=lf[102],tmp=(C_word)a,a+=3,tmp));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1095,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 342  return-to-host");
t4=C_retrieve(lf[103]);
((C_proc2)C_retrieve_proc(t4))(2,t4,t3);}

/* k1093 in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_1095(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_UNDEFINED);}

/* expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_642(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
C_save_and_reclaim((void*)tr5,(void*)f_642,5,t0,t1,t2,t3,t4);}
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_SCHEME_END_OF_LIST;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=C_SCHEME_END_OF_LIST;
t9=(*a=C_VECTOR_TYPE|1,a[1]=t8,tmp=(C_word)a,a+=2,tmp);
t10=C_SCHEME_END_OF_LIST;
t11=(*a=C_VECTOR_TYPE|1,a[1]=t10,tmp=(C_word)a,a+=2,tmp);
t12=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_655,a[2]=t2,a[3]=t11,a[4]=t5,a[5]=t9,a[6]=t1,a[7]=t7,a[8]=t3,tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(t2))){
t13=t12;
f_655(2,t13,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 254  error");
t13=*((C_word*)lf[27]+1);
((C_proc4)C_retrieve_proc(t13))(4,t13,t12,lf[101],t2);}}

/* k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_655(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_655,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_658,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(((C_word*)t0)[8]))){
if(C_truep((C_word)C_i_nullp(((C_word*)t0)[8]))){
C_trace("ChickenBridge.scm: 258  error");
t3=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,lf[99]);}
else{
t3=t2;
f_658(2,t3,C_SCHEME_UNDEFINED);}}
else{
C_trace("ChickenBridge.scm: 256  error");
t3=*((C_word*)lf[27]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t2,lf[100],((C_word*)t0)[8]);}}

/* k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_658(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_658,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_661,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],tmp=(C_word)a,a+=8,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_932,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[7],a[5]=t4,a[6]=lf[98],tmp=(C_word)a,a+=7,tmp));
t6=((C_word*)t4)[1];
f_932(t6,t2,((C_word*)t0)[2]);}

/* do131 in k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_fcall f_932(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_932,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_942,a[2]=t1,a[3]=((C_word*)t0)[5],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_952,a[2]=t3,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=t2,tmp=(C_word)a,a+=7,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1040,a[2]=t4,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t7=(C_word)C_i_car(t2);
t8=(C_word)C_i_length(t7);
C_trace("ChickenBridge.scm: 262  <");
C_lessp(5,0,t6,C_fix(0),t8,C_fix(4));}
else{
t6=t4;
f_952(t6,C_SCHEME_FALSE);}}}

/* k1038 in do131 in k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_1040(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=(C_word)C_i_car(t2);
t4=((C_word*)t0)[2];
f_952(t4,(C_word)C_i_symbolp(t3));}
else{
t2=((C_word*)t0)[2];
f_952(t2,C_SCHEME_FALSE);}}

/* k950 in do131 in k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_fcall f_952(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_952,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[6]);
t3=(C_word)C_i_car(t2);
t4=(C_word)C_i_car(((C_word*)t0)[6]);
t5=(C_word)C_i_cadr(t4);
t6=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_961,a[2]=t5,a[3]=t3,a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[5],tmp=(C_word)a,a+=8,tmp);
t7=(C_word)C_i_car(((C_word*)t0)[6]);
t8=(C_word)C_i_cddr(t7);
if(C_truep((C_word)C_i_nullp(t8))){
t9=t6;
f_961(t9,lf[96]);}
else{
t9=(C_word)C_i_car(((C_word*)t0)[6]);
t10=t6;
f_961(t10,(C_word)C_i_caddr(t9));}}
else{
t2=(C_word)C_i_car(((C_word*)t0)[6]);
C_trace("ChickenBridge.scm: 275  error");
t3=*((C_word*)lf[27]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[2],lf[97],t2);}}

/* k959 in k950 in do131 in k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_fcall f_961(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_961,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_965,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t3=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 270  append");
t4=*((C_word*)lf[41]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,((C_word*)((C_word*)t0)[7])[1],t3);}

/* k963 in k959 in k950 in do131 in k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_965(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_965,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_969,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
t4=(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 271  append");
t5=*((C_word*)lf[41]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,((C_word*)((C_word*)t0)[7])[1],t4);}

/* k967 in k963 in k959 in k950 in do131 in k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_969(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_969,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_973,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_977,a[2]=((C_word*)t0)[5],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_eqp(((C_word*)t0)[3],lf[96]);
if(C_truep(t5)){
t6=t4;
f_977(t6,C_SCHEME_END_OF_LIST);}
else{
t6=(C_word)C_a_i_list(&a,3,lf[76],((C_word*)t0)[2],((C_word*)t0)[3]);
t7=t4;
f_977(t7,(C_word)C_a_i_list(&a,1,t6));}}

/* k975 in k967 in k963 in k959 in k950 in do131 in k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_fcall f_977(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 272  append");
t2=*((C_word*)lf[41]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k971 in k967 in k963 in k959 in k950 in do131 in k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_973(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_942(2,t3,t2);}

/* k940 in do131 in k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_942(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_932(t3,((C_word*)t0)[2],t2);}

/* k659 in k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_661(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_661,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_664,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 277  gensym");
t3=C_retrieve(lf[95]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k662 in k659 in k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_664(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_664,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_667,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 278  gensym");
t3=C_retrieve(lf[95]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k665 in k662 in k659 in k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_667(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_667,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_670,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 279  gensym");
t3=C_retrieve(lf[95]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k668 in k665 in k662 in k659 in k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_670(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_670,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_673,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],a[10]=((C_word*)t0)[9],tmp=(C_word)a,a+=11,tmp);
C_trace("ChickenBridge.scm: 280  gensym");
t3=C_retrieve(lf[95]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k671 in k668 in k665 in k662 in k659 in k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_673(C_word c,C_word t0,C_word t1){
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
C_word ab[26],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_673,2,t0,t1);}
t2=C_SCHEME_TRUE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_SCHEME_END_OF_LIST;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_676,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=t3,a[7]=((C_word*)t0)[5],a[8]=((C_word*)t0)[6],a[9]=((C_word*)t0)[7],a[10]=((C_word*)t0)[8],a[11]=((C_word*)t0)[9],a[12]=t5,a[13]=((C_word*)t0)[10],tmp=(C_word)a,a+=14,tmp);
t7=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_825,a[2]=t6,a[3]=t3,a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)((C_word*)t0)[3])[1]))){
t8=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
if(C_truep((C_word)C_i_pairp(t8))){
t9=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_926,a[2]=t7,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 286  caar");
t10=*((C_word*)lf[91]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)((C_word*)t0)[3])[1]);}
else{
t9=t7;
f_825(t9,C_SCHEME_FALSE);}}
else{
t8=t7;
f_825(t8,C_SCHEME_FALSE);}}

/* k924 in k671 in k668 in k665 in k662 in k659 in k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_926(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_825(t2,(C_word)C_eqp(t1,lf[94]));}

/* k823 in k671 in k668 in k665 in k662 in k659 in k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_fcall f_825(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_825,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_832,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 287  cdar");
t3=*((C_word*)lf[89]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)((C_word*)t0)[4])[1]);}
else{
t2=((C_word*)t0)[2];
f_676(2,t2,C_SCHEME_UNDEFINED);}}

/* k830 in k823 in k671 in k668 in k665 in k662 in k659 in k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_832(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_832,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_834,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=lf[93],tmp=(C_word)a,a+=6,tmp));
t5=((C_word*)t3)[1];
f_834(t5,((C_word*)t0)[2],t1);}

/* do147 in k830 in k823 in k671 in k668 in k665 in k662 in k659 in k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_fcall f_834(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_834,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[4])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[4])+1,t3);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,t4);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_848,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_858,a[2]=t2,a[3]=((C_word*)t0)[2],a[4]=t3,tmp=(C_word)a,a+=5,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_906,a[2]=t4,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 291  cdar");
t7=*((C_word*)lf[89]+1);
((C_proc3)C_retrieve_proc(t7))(3,t7,t6,t2);}
else{
t6=t4;
f_858(t6,C_SCHEME_FALSE);}}}

/* k904 in do147 in k830 in k823 in k671 in k668 in k665 in k662 in k659 in k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_906(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_858(t2,(C_word)C_i_pairp(t1));}

/* k856 in do147 in k830 in k823 in k671 in k668 in k665 in k662 in k659 in k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_fcall f_858(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_858,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_861,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 292  caar");
t3=*((C_word*)lf[91]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)t0)[2]);}
else{
t2=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 298  error");
t3=*((C_word*)lf[27]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[4],lf[92],t2);}}

/* k859 in k856 in do147 in k830 in k823 in k671 in k668 in k665 in k662 in k659 in k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_861(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_861,2,t0,t1);}
t2=(C_word)C_eqp(t1,lf[88]);
if(C_truep(t2)){
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_882,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 294  cdar");
t4=*((C_word*)lf[89]+1);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)t0)[2]);}
else{
t3=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 297  error");
t4=*((C_word*)lf[27]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,((C_word*)t0)[4],lf[90],t3);}}

/* k880 in k859 in k856 in do147 in k830 in k823 in k671 in k668 in k665 in k662 in k659 in k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_882(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep((C_word)C_i_car(t1))){
t2=((C_word*)t0)[3];
f_848(2,t2,C_SCHEME_UNDEFINED);}
else{
t2=C_set_block_item(((C_word*)t0)[2],0,C_SCHEME_FALSE);
t3=((C_word*)t0)[3];
f_848(2,t3,t2);}}

/* k846 in do147 in k830 in k823 in k671 in k668 in k665 in k662 in k659 in k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_848(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_834(t3,((C_word*)t0)[2],t2);}

/* k674 in k671 in k668 in k665 in k662 in k659 in k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_676(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_676,2,t0,t1);}
t2=(C_word)C_i_car(((C_word*)t0)[13]);
t3=(*a=C_CLOSURE_TYPE|13,a[1]=(C_word)f_814,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],a[10]=((C_word*)t0)[10],a[11]=((C_word*)t0)[11],a[12]=((C_word*)t0)[12],a[13]=t2,tmp=(C_word)a,a+=14,tmp);
t4=(C_word)C_i_cdr(((C_word*)t0)[13]);
t5=(C_word)C_a_i_list(&a,1,C_fix(-1));
C_trace("ChickenBridge.scm: 249  ##sys#append");
t6=*((C_word*)lf[87]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t3,t4,t5);}

/* k812 in k674 in k671 in k668 in k665 in k662 in k659 in k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_814(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[22],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_814,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[13],t1);
t3=(*a=C_CLOSURE_TYPE|11,a[1]=(C_word)f_798,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],a[8]=((C_word*)t0)[10],a[9]=((C_word*)t0)[11],a[10]=((C_word*)t0)[12],a[11]=t2,tmp=(C_word)a,a+=12,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_802,a[2]=((C_word*)t0)[3],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_a_i_list(&a,1,((C_word*)t0)[10]);
C_trace("ChickenBridge.scm: 249  ##sys#append");
t6=*((C_word*)lf[87]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t4,((C_word*)((C_word*)t0)[2])[1],t5);}

/* k800 in k812 in k674 in k671 in k668 in k665 in k662 in k659 in k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_802(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 249  ##sys#append");
t2=*((C_word*)lf[87]+1);
((C_proc4)(void*)(*((C_word*)t2+1)))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k796 in k812 in k674 in k671 in k668 in k665 in k662 in k659 in k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_798(C_word c,C_word t0,C_word t1){
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
C_word t16;
C_word t17;
C_word t18;
C_word t19;
C_word t20;
C_word ab[116],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_798,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,lf[71],t1);
t3=(C_word)C_a_i_list(&a,3,lf[72],((C_word*)t0)[11],t2);
t4=C_mutate(((C_word *)((C_word*)t0)[10])+1,t3);
t5=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_683,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],a[5]=((C_word*)t0)[10],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],tmp=(C_word)a,a+=8,tmp);
if(C_truep(((C_word*)((C_word*)t0)[4])[1])){
t6=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
t7=(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]);
t8=(C_word)C_a_i_list(&a,2,lf[79],lf[80]);
t9=(C_word)C_a_i_list(&a,2,lf[79],lf[81]);
t10=(C_word)C_a_i_list(&a,3,lf[82],t8,t9);
t11=(C_word)C_a_i_list(&a,2,t10,((C_word*)t0)[2]);
t12=(C_word)C_a_i_list(&a,4,lf[83],lf[84],((C_word*)t0)[9],t11);
t13=(C_word)C_a_i_list(&a,2,((C_word*)t0)[3],C_fix(-2));
t14=(C_word)C_a_i_list(&a,4,lf[73],t7,t12,t13);
t15=(C_word)C_a_i_list(&a,3,lf[73],C_SCHEME_END_OF_LIST,((C_word*)((C_word*)t0)[10])[1]);
t16=(C_word)C_a_i_list(&a,3,lf[85],t14,t15);
t17=(C_word)C_a_i_list(&a,3,lf[73],t6,t16);
t18=(C_word)C_a_i_list(&a,2,lf[86],t17);
t19=C_mutate(((C_word *)((C_word*)t0)[10])+1,t18);
t20=t5;
f_683(t20,t19);}
else{
t6=t5;
f_683(t6,C_SCHEME_UNDEFINED);}}

/* k681 in k796 in k812 in k674 in k671 in k668 in k665 in k662 in k659 in k656 in k653 in expand-go in k638 in k635 in k632 in k629 in k626 in k623 in k620 in k617 in k614 in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_fcall f_683(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_683,NULL,2,t0,t1);}
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

/* mp:inhook in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_609(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_609,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 212  error");
t3=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[68]);}

/* mp:micro in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_603(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_603,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 210  error");
t3=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[65]);}

/* mp:alloff in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_597(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_597,2,t0,t1);}
C_trace("ChickenBridge.scm: 208  error");
t2=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,t1,lf[62]);}

/* mp:ctrl in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_591(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_591,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 206  error");
t6=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[59]);}

/* mp:prog in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_585(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_585,5,t0,t1,t2,t3,t4);}
C_trace("ChickenBridge.scm: 204  error");
t5=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t5))(3,t5,t1,lf[56]);}

/* mp:off in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_579(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_579,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 202  error");
t6=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[53]);}

/* mp:on in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_573(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_573,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 200  error");
t6=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[50]);}

/* mp:note in k563 in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_567(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
C_word tmp;
C_word t7;
C_word *a;
if(c!=7) C_bad_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr7,(void*)f_567,7,t0,t1,t2,t3,t4,t5,t6);}
C_trace("ChickenBridge.scm: 196  insert-midi-note");
t7=*((C_word*)lf[12]+1);
((C_proc7)C_retrieve_proc(t7))(7,t7,t1,t2,t3,t4,t5,t6);}

/* expand-send in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_338(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word ab[6],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_338,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_342,a[2]=t1,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_symbolp(t2))){
C_trace("ChickenBridge.scm: 119  symbol->string");
t6=*((C_word*)lf[45]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t5,t2);}
else{
t6=t5;
f_342(2,t6,t2);}}

/* k340 in expand-send in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_342(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_342,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_345,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_555,a[2]=lf[43],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 120  hash-table-ref");
t4=*((C_word*)lf[44]+1);
((C_proc5)C_retrieve_proc(t4))(5,t4,t2,lf[25],t1,t3);}

/* a554 in k340 in expand-send in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_555(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_555,2,t0,t1);}
t2=t1;
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}

/* k343 in k340 in expand-send in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_345(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_345,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_348,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=t1;
if(C_truep(t3)){
t4=t2;
f_348(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 121  ferror");
f_328(t2,lf[42],(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]));}}

/* k346 in k343 in k340 in expand-send in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_348(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_348,2,t0,t1);}
t2=((C_word*)((C_word*)t0)[5])[1];
t3=(C_word)C_i_car(((C_word*)t0)[4]);
t4=(C_word)C_i_cdr(((C_word*)t0)[4]);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(C_word)C_i_length(t4);
t8=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_360,a[2]=t7,a[3]=t2,a[4]=((C_word*)t0)[2],a[5]=t6,a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[3],a[8]=t4,a[9]=t3,tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 128  append");
t9=*((C_word*)lf[41]+1);
((C_proc4)C_retrieve_proc(t9))(4,t9,t8,t4,C_SCHEME_END_OF_LIST);}

/* k358 in k346 in k343 in k340 in expand-send in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_360(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[19],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_360,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_363,a[2]=((C_word*)t0)[7],a[3]=((C_word*)t0)[8],a[4]=t1,a[5]=((C_word*)t0)[9],tmp=(C_word)a,a+=6,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_408,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[5],a[8]=t4,a[9]=((C_word*)t0)[6],a[10]=lf[40],tmp=(C_word)a,a+=11,tmp));
t6=((C_word*)t4)[1];
f_408(t6,t2,C_SCHEME_FALSE,C_SCHEME_FALSE,C_fix(0));}

/* do74 in k358 in k346 in k343 in k340 in expand-send in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_fcall f_408(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
C_save_and_reclaim((void*)trf_408,NULL,5,t0,t1,t2,t3,t4);}
t5=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[9])[1]))){
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,C_SCHEME_FALSE);}
else{
t8=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_418,a[2]=t7,a[3]=t6,a[4]=t5,a[5]=t1,a[6]=((C_word*)t0)[8],tmp=(C_word)a,a+=7,tmp);
t9=(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_424,a[2]=((C_word*)t0)[2],a[3]=t7,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=t6,a[8]=((C_word*)t0)[6],a[9]=t5,a[10]=((C_word*)t0)[9],a[11]=t8,a[12]=((C_word*)t0)[7],tmp=(C_word)a,a+=13,tmp);
t10=((C_word*)((C_word*)t0)[7])[1];
if(C_truep(t10)){
t11=t9;
f_424(2,t11,C_SCHEME_FALSE);}
else{
t11=(C_word)C_i_car(((C_word*)((C_word*)t0)[9])[1]);
C_trace("ChickenBridge.scm: 139  keyword?");
t12=C_retrieve(lf[38]);
((C_proc3)C_retrieve_proc(t12))(3,t12,t9,t11);}}}

/* k422 in do74 in k358 in k346 in k343 in k340 in expand-send in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_424(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_424,2,t0,t1);}
if(C_truep(t1)){
t2=C_set_block_item(((C_word*)t0)[12],0,C_SCHEME_TRUE);
t3=((C_word*)t0)[11];
f_418(t3,t2);}
else{
t2=((C_word*)((C_word*)t0)[12])[1];
if(C_truep(t2)){
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[10])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[9])+1,t3);
t5=(C_word)C_i_assoc(((C_word*)((C_word*)t0)[9])[1],((C_word*)t0)[8]);
t6=C_mutate(((C_word *)((C_word*)t0)[7])+1,t5);
t7=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[10])[1]);
t8=C_mutate(((C_word *)((C_word*)t0)[10])+1,t7);
t9=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_478,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[9],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[11],a[6]=((C_word*)t0)[10],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t10=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_533,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[9],a[5]=((C_word*)t0)[5],a[6]=t9,a[7]=((C_word*)t0)[10],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 159  keyword?");
t11=C_retrieve(lf[38]);
((C_proc3)C_retrieve_proc(t11))(3,t11,t10,((C_word*)((C_word*)t0)[9])[1]);}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_434,a[2]=((C_word*)t0)[11],a[3]=((C_word*)t0)[10],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[6],tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_nequalp(((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]))){
t4=(C_word)C_i_length(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 149  ferror");
f_328(t3,lf[39],(C_word)C_a_i_list(&a,3,((C_word*)t0)[5],((C_word*)t0)[2],t4));}
else{
t4=t3;
f_434(2,t4,C_SCHEME_UNDEFINED);}}}}

/* k432 in k422 in do74 in k358 in k346 in k343 in k340 in expand-send in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_434(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_434,2,t0,t1);}
t2=(C_word)C_i_list_tail(((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]);
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
t4=(C_word)C_i_set_car(t2,t3);
t5=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[3])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t5);
t7=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[4])[1],C_fix(1));
t8=C_mutate(((C_word *)((C_word*)t0)[4])+1,t7);
t9=((C_word*)t0)[2];
f_418(t9,t8);}

/* k531 in k422 in do74 in k358 in k346 in k343 in k340 in expand-send in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_533(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_533,2,t0,t1);}
if(C_truep(t1)){
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[7])[1]))){
C_trace("ChickenBridge.scm: 163  ferror");
f_328(((C_word*)t0)[6],lf[33],(C_word)C_a_i_list(&a,2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]));}
else{
t2=((C_word*)((C_word*)t0)[3])[1];
if(C_truep(t2)){
t3=((C_word*)t0)[6];
f_478(2,t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_529,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
C_trace("map");
t4=*((C_word*)lf[35]+1);
((C_proc4)(void*)(*((C_word*)t4+1)))(4,t4,t3,*((C_word*)lf[36]+1),((C_word*)t0)[2]);}}}
else{
C_trace("ChickenBridge.scm: 160  ferror");
f_328(((C_word*)t0)[6],lf[37],(C_word)C_a_i_list(&a,2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]));}}

/* k527 in k531 in k422 in do74 in k358 in k346 in k343 in k340 in expand-send in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_529(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_529,2,t0,t1);}
C_trace("ChickenBridge.scm: 166  ferror");
f_328(((C_word*)t0)[4],lf[34],(C_word)C_a_i_list(&a,3,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1));}

/* k476 in k422 in do74 in k358 in k346 in k343 in k340 in expand-send in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_478(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[14],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_478,2,t0,t1);}
t2=(C_word)C_i_member(((C_word*)((C_word*)t0)[8])[1],((C_word*)t0)[7]);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_484,a[2]=((C_word*)t0)[5],a[3]=t2,a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
if(C_truep(t2)){
t4=t3;
f_484(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 173  ferror");
f_328(t3,lf[32],(C_word)C_a_i_list(&a,3,((C_word*)t0)[4],((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]));}}

/* k482 in k476 in k422 in do74 in k358 in k346 in k343 in k340 in expand-send in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_484(C_word c,C_word t0,C_word t1){
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
f_418(t6,t5);}

/* k416 in do74 in k358 in k346 in k343 in k340 in expand-send in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_fcall f_418(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[6])[1];
f_408(t2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k361 in k358 in k346 in k343 in k340 in expand-send in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_363(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_363,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_368,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=lf[31],tmp=(C_word)a,a+=7,tmp));
t5=((C_word*)t3)[1];
f_368(t5,((C_word*)t0)[2],((C_word*)t0)[4]);}

/* do91 in k361 in k358 in k346 in k343 in k340 in expand-send in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_fcall f_368(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_368,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[5],((C_word*)t0)[4]));}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_381,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_member(t4,((C_word*)t0)[2]))){
t5=(C_word)C_i_car(t2);
t6=(C_word)C_i_cadr(t5);
t7=t3;
f_381(t7,(C_word)C_i_set_car(t2,t6));}
else{
t5=t3;
f_381(t5,C_SCHEME_UNDEFINED);}}}

/* k379 in do91 in k361 in k358 in k346 in k343 in k340 in expand-send in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_fcall f_381(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_368(t3,((C_word*)t0)[2],t2);}

/* ferror in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_fcall f_328(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_328,NULL,3,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_336,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_apply(5,0,t4,C_retrieve(lf[28]),t2,t3);}

/* k334 in ferror in k324 in k321 in k209 in k206 in k203 in k200 */
static void C_ccall f_336(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 116  error");
t2=*((C_word*)lf[27]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* current-time-hi-res in k209 in k206 in k203 in k200 */
static void C_ccall f_318(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_318,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub53(t2));}

/* run_process in k209 in k206 in k203 in k200 */
static void C_ccall f_308(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_308,4,t0,t1,t2,t3);}
t4=(C_word)C_a_i_list(&a,1,t3);
C_apply(4,0,t1,t2,t4);}

/* make-note-off in k209 in k206 in k203 in k200 */
static void C_ccall f_302(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_302,5,t0,t1,t2,t3,t4);}
C_trace("ChickenBridge.scm: 87   insert-midi-on");
t5=C_retrieve(lf[16]);
((C_proc6)C_retrieve_proc(t5))(6,t5,t1,t2,t3,lf[19],t4);}

/* make-note-on in k209 in k206 in k203 in k200 */
static void C_ccall f_296(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_296,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 83   insert-midi-on");
t6=C_retrieve(lf[16]);
((C_proc6)C_retrieve_proc(t6))(6,t6,t1,t2,t3,t4,t5);}

/* insert-midi-note in k209 in k206 in k203 in k200 */
static void C_ccall f_267(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
C_word tmp;
C_word t7;
C_word t8;
C_word ab[8],*a=ab;
if(c!=7) C_bad_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr7,(void*)f_267,7,t0,t1,t2,t3,t4,t5,t6);}
t7=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_271,a[2]=t1,a[3]=t6,a[4]=t5,a[5]=t4,a[6]=t3,a[7]=t2,tmp=(C_word)a,a+=8,tmp);
C_trace("##sys#gc");
t8=C_retrieve(lf[7]);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,C_SCHEME_FALSE);}

/* k269 in insert-midi-note in k209 in k206 in k203 in k200 */
static void C_ccall f_271(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_271,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[7]);
t4=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[6]);
t5=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[5]);
t6=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[4]);
t7=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[3]);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub33,a[2]=lf[13],tmp=(C_word)a,a+=3,tmp);
((C_proc8)C_retrieve_proc(t8))(8,t8,((C_word*)t0)[2],t2,t3,t4,t5,t6,t7);}

/* insert-closure in k209 in k206 in k203 in k200 */
static void C_ccall f_254(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_254,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_258,a[2]=t3,a[3]=t1,a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("##sys#gc");
t5=C_retrieve(lf[7]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,C_SCHEME_FALSE);}

/* k256 in insert-closure in k209 in k206 in k203 in k200 */
static void C_ccall f_258(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_258,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[4]);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub22,a[2]=lf[10],tmp=(C_word)a,a+=3,tmp);
((C_proc5)C_retrieve_proc(t4))(5,t4,((C_word*)t0)[3],t2,t3,((C_word*)t0)[2]);}

/* insert-process in k209 in k206 in k203 in k200 */
static void C_ccall f_241(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_241,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_245,a[2]=t3,a[3]=t1,a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("##sys#gc");
t5=C_retrieve(lf[7]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,C_SCHEME_FALSE);}

/* k243 in insert-process in k209 in k206 in k203 in k200 */
static void C_ccall f_245(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_245,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[4]);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub14,a[2]=lf[6],tmp=(C_word)a,a+=3,tmp);
((C_proc5)C_retrieve_proc(t4))(5,t4,((C_word*)t0)[3],t2,t3,((C_word*)t0)[2]);}

/* print-error in k209 in k206 in k203 in k200 */
static void C_ccall f_227(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_227,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_232,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[1]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_232(2,t4,C_SCHEME_FALSE);}}

/* k230 in print-error in k209 in k206 in k203 in k200 */
static void C_ccall f_232(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub7(C_SCHEME_UNDEFINED,t1));}

/* print-message in k209 in k206 in k203 in k200 */
static void C_ccall f_213(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_213,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_218,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[1]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_218(2,t4,C_SCHEME_FALSE);}}

/* k216 in print-message in k209 in k206 in k203 in k200 */
static void C_ccall f_218(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub1(C_SCHEME_UNDEFINED,t1));}

#ifdef C_ENABLE_PTABLES
static C_PTABLE_ENTRY ptable[97] = {
{"toplevelChickenBridge.scm",(void*)C_grace_toplevel},
{"f_202ChickenBridge.scm",(void*)f_202},
{"f_205ChickenBridge.scm",(void*)f_205},
{"f_208ChickenBridge.scm",(void*)f_208},
{"f_211ChickenBridge.scm",(void*)f_211},
{"f_323ChickenBridge.scm",(void*)f_323},
{"f_1109ChickenBridge.scm",(void*)f_1109},
{"f_1156ChickenBridge.scm",(void*)f_1156},
{"f_1146ChickenBridge.scm",(void*)f_1146},
{"f_1113ChickenBridge.scm",(void*)f_1113},
{"f_326ChickenBridge.scm",(void*)f_326},
{"f_1103ChickenBridge.scm",(void*)f_1103},
{"f_565ChickenBridge.scm",(void*)f_565},
{"f_616ChickenBridge.scm",(void*)f_616},
{"f_619ChickenBridge.scm",(void*)f_619},
{"f_622ChickenBridge.scm",(void*)f_622},
{"f_625ChickenBridge.scm",(void*)f_625},
{"f_628ChickenBridge.scm",(void*)f_628},
{"f_631ChickenBridge.scm",(void*)f_631},
{"f_634ChickenBridge.scm",(void*)f_634},
{"f_637ChickenBridge.scm",(void*)f_637},
{"f_1097ChickenBridge.scm",(void*)f_1097},
{"f_640ChickenBridge.scm",(void*)f_640},
{"f_1095ChickenBridge.scm",(void*)f_1095},
{"f_642ChickenBridge.scm",(void*)f_642},
{"f_655ChickenBridge.scm",(void*)f_655},
{"f_658ChickenBridge.scm",(void*)f_658},
{"f_932ChickenBridge.scm",(void*)f_932},
{"f_1040ChickenBridge.scm",(void*)f_1040},
{"f_952ChickenBridge.scm",(void*)f_952},
{"f_961ChickenBridge.scm",(void*)f_961},
{"f_965ChickenBridge.scm",(void*)f_965},
{"f_969ChickenBridge.scm",(void*)f_969},
{"f_977ChickenBridge.scm",(void*)f_977},
{"f_973ChickenBridge.scm",(void*)f_973},
{"f_942ChickenBridge.scm",(void*)f_942},
{"f_661ChickenBridge.scm",(void*)f_661},
{"f_664ChickenBridge.scm",(void*)f_664},
{"f_667ChickenBridge.scm",(void*)f_667},
{"f_670ChickenBridge.scm",(void*)f_670},
{"f_673ChickenBridge.scm",(void*)f_673},
{"f_926ChickenBridge.scm",(void*)f_926},
{"f_825ChickenBridge.scm",(void*)f_825},
{"f_832ChickenBridge.scm",(void*)f_832},
{"f_834ChickenBridge.scm",(void*)f_834},
{"f_906ChickenBridge.scm",(void*)f_906},
{"f_858ChickenBridge.scm",(void*)f_858},
{"f_861ChickenBridge.scm",(void*)f_861},
{"f_882ChickenBridge.scm",(void*)f_882},
{"f_848ChickenBridge.scm",(void*)f_848},
{"f_676ChickenBridge.scm",(void*)f_676},
{"f_814ChickenBridge.scm",(void*)f_814},
{"f_802ChickenBridge.scm",(void*)f_802},
{"f_798ChickenBridge.scm",(void*)f_798},
{"f_683ChickenBridge.scm",(void*)f_683},
{"f_609ChickenBridge.scm",(void*)f_609},
{"f_603ChickenBridge.scm",(void*)f_603},
{"f_597ChickenBridge.scm",(void*)f_597},
{"f_591ChickenBridge.scm",(void*)f_591},
{"f_585ChickenBridge.scm",(void*)f_585},
{"f_579ChickenBridge.scm",(void*)f_579},
{"f_573ChickenBridge.scm",(void*)f_573},
{"f_567ChickenBridge.scm",(void*)f_567},
{"f_338ChickenBridge.scm",(void*)f_338},
{"f_342ChickenBridge.scm",(void*)f_342},
{"f_555ChickenBridge.scm",(void*)f_555},
{"f_345ChickenBridge.scm",(void*)f_345},
{"f_348ChickenBridge.scm",(void*)f_348},
{"f_360ChickenBridge.scm",(void*)f_360},
{"f_408ChickenBridge.scm",(void*)f_408},
{"f_424ChickenBridge.scm",(void*)f_424},
{"f_434ChickenBridge.scm",(void*)f_434},
{"f_533ChickenBridge.scm",(void*)f_533},
{"f_529ChickenBridge.scm",(void*)f_529},
{"f_478ChickenBridge.scm",(void*)f_478},
{"f_484ChickenBridge.scm",(void*)f_484},
{"f_418ChickenBridge.scm",(void*)f_418},
{"f_363ChickenBridge.scm",(void*)f_363},
{"f_368ChickenBridge.scm",(void*)f_368},
{"f_381ChickenBridge.scm",(void*)f_381},
{"f_328ChickenBridge.scm",(void*)f_328},
{"f_336ChickenBridge.scm",(void*)f_336},
{"f_318ChickenBridge.scm",(void*)f_318},
{"f_308ChickenBridge.scm",(void*)f_308},
{"f_302ChickenBridge.scm",(void*)f_302},
{"f_296ChickenBridge.scm",(void*)f_296},
{"f_267ChickenBridge.scm",(void*)f_267},
{"f_271ChickenBridge.scm",(void*)f_271},
{"f_254ChickenBridge.scm",(void*)f_254},
{"f_258ChickenBridge.scm",(void*)f_258},
{"f_241ChickenBridge.scm",(void*)f_241},
{"f_245ChickenBridge.scm",(void*)f_245},
{"f_227ChickenBridge.scm",(void*)f_227},
{"f_232ChickenBridge.scm",(void*)f_232},
{"f_213ChickenBridge.scm",(void*)f_213},
{"f_218ChickenBridge.scm",(void*)f_218},
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
