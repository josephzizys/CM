/* Generated from src/ChickenBridge.scm by the CHICKEN compiler
   http://www.call-with-current-continuation.org
   2007-10-15 19:56
   Version 2.724 - macosx-unix-gnu-x86 - [ manyargs dload ptables applyhook ]
(c)2000-2007 Felix L. Winkelmann | compiled 2007-10-12 on todd-ingalls-computer-2.local (Darwin)
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

void insert_midi_note(double time, float k, float v, float c)
{
 float *vals = new float[3];
 vals[0] = k;
 vals[1] = v;
 vals[2] = c;
 ((GraceApp *)GraceApp::getInstance())->queue->addNode(0, time, vals, 3, 0);

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

static C_TLS C_word lf[130];


/* from now in k214 in k211 in k208 in k205 */
#define return(x) C_cblock C_r = (C_flonum(&C_a,(x))); goto C_ret; C_cblockend
static C_word C_fcall stub41(C_word C_buf) C_regparm;
C_regparm static C_word C_fcall stub41(C_word C_buf){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
 C_return(Time::getMillisecondCounterHiRes());
C_ret:
#undef return

return C_r;}

/* from k275 */
static C_word C_fcall stub28(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2,C_word C_a3) C_regparm;
C_regparm static C_word C_fcall stub28(C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2,C_word C_a3){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
double t0=(double )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
float t2=(float )C_c_double(C_a2);
float t3=(float )C_c_double(C_a3);
insert_midi_note(t0,t1,t2,t3);
return C_r;}

/* from k256 */
static C_word C_fcall stub20(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub20(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
double t0=(double )C_c_double(C_a0);
C_word t1=(C_word )(C_a1);
insert_closure(t0,t1);
return C_r;}

/* from k249 */
static C_word C_fcall stub14(C_word C_buf,C_word C_a0,C_word C_a1) C_regparm;
C_regparm static C_word C_fcall stub14(C_word C_buf,C_word C_a0,C_word C_a1){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
double t0=(double )C_c_double(C_a0);
C_word t1=(C_word )(C_a1);
insert_process(t0,t1);
return C_r;}

/* from k235 in print-error in k214 in k211 in k208 in k205 */
static C_word C_fcall stub7(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub7(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_error(t0);
return C_r;}

/* from k221 in print-message in k214 in k211 in k208 in k205 */
static C_word C_fcall stub1(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub1(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_mess(t0);
return C_r;}

C_noret_decl(C_grace_toplevel)
C_externexport void C_ccall C_grace_toplevel(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_207)
static void C_ccall f_207(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_210)
static void C_ccall f_210(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_213)
static void C_ccall f_213(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_216)
static void C_ccall f_216(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_369)
static void C_ccall f_369(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1021)
static void C_ccall f_1021(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_1068)
static void C_ccall f_1068(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1058)
static void C_ccall f_1058(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1025)
static void C_ccall f_1025(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_372)
static void C_ccall f_372(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1015)
static void C_ccall f_1015(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_1015)
static void C_ccall f_1015r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_611)
static void C_ccall f_611(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_669)
static void C_ccall f_669(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_672)
static void C_ccall f_672(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_675)
static void C_ccall f_675(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_678)
static void C_ccall f_678(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_681)
static void C_ccall f_681(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_684)
static void C_ccall f_684(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_687)
static void C_ccall f_687(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_690)
static void C_ccall f_690(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_998)
static void C_ccall f_998(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_998)
static void C_ccall f_998r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_1002)
static void C_fcall f_1002(C_word t0,C_word t1) C_noret;
C_noret_decl(f_693)
static void C_ccall f_693(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_992)
static void C_ccall f_992(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_992)
static void C_ccall f_992r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_696)
static void C_ccall f_696(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_990)
static void C_ccall f_990(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_698)
static void C_ccall f_698(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_711)
static void C_ccall f_711(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_714)
static void C_ccall f_714(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_827)
static void C_fcall f_827(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_935)
static void C_ccall f_935(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_847)
static void C_fcall f_847(C_word t0,C_word t1) C_noret;
C_noret_decl(f_856)
static void C_fcall f_856(C_word t0,C_word t1) C_noret;
C_noret_decl(f_860)
static void C_ccall f_860(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_864)
static void C_ccall f_864(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_872)
static void C_fcall f_872(C_word t0,C_word t1) C_noret;
C_noret_decl(f_868)
static void C_ccall f_868(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_837)
static void C_ccall f_837(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_717)
static void C_ccall f_717(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_720)
static void C_ccall f_720(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_723)
static void C_ccall f_723(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_726)
static void C_ccall f_726(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_781)
static void C_ccall f_781(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_769)
static void C_ccall f_769(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_765)
static void C_ccall f_765(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_662)
static void C_ccall f_662(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_656)
static void C_ccall f_656(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_650)
static void C_ccall f_650(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_644)
static void C_ccall f_644(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_638)
static void C_ccall f_638(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_632)
static void C_ccall f_632(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_626)
static void C_ccall f_626(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_613)
static void C_ccall f_613(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_617)
static void C_ccall f_617(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_384)
static void C_ccall f_384(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_388)
static void C_ccall f_388(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_601)
static void C_ccall f_601(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_391)
static void C_ccall f_391(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_394)
static void C_ccall f_394(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_406)
static void C_ccall f_406(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_454)
static void C_fcall f_454(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_470)
static void C_ccall f_470(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_480)
static void C_ccall f_480(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_579)
static void C_ccall f_579(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_575)
static void C_ccall f_575(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_524)
static void C_ccall f_524(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_530)
static void C_ccall f_530(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_464)
static void C_fcall f_464(C_word t0,C_word t1) C_noret;
C_noret_decl(f_409)
static void C_ccall f_409(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_414)
static void C_fcall f_414(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_427)
static void C_fcall f_427(C_word t0,C_word t1) C_noret;
C_noret_decl(f_374)
static void C_fcall f_374(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_382)
static void C_ccall f_382(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_349)
static void C_ccall f_349(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_358)
static void C_ccall f_358(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_362)
static void C_ccall f_362(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_353)
static void C_ccall f_353(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_313)
static void C_ccall f_313(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_319)
static void C_fcall f_319(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_329)
static void C_ccall f_329(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_332)
static void C_ccall f_332(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_294)
static void C_ccall f_294(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_296)
static void C_ccall f_296(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_300)
static void C_ccall f_300(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_307)
static void C_fcall f_307(C_word t0,C_word t1) C_noret;
C_noret_decl(f_291)
static void C_ccall f_291(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_285)
static void C_ccall f_285(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_279)
static void C_ccall f_279(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_260)
static void C_ccall f_260(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_253)
static void C_ccall f_253(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_246)
static void C_ccall f_246(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_232)
static void C_ccall f_232(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_237)
static void C_ccall f_237(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_218)
static void C_ccall f_218(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_223)
static void C_ccall f_223(C_word c,C_word t0,C_word t1) C_noret;

C_noret_decl(trf_1002)
static void C_fcall trf_1002(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_1002(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_1002(t0,t1);}

C_noret_decl(trf_827)
static void C_fcall trf_827(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_827(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_827(t0,t1,t2);}

C_noret_decl(trf_847)
static void C_fcall trf_847(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_847(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_847(t0,t1);}

C_noret_decl(trf_856)
static void C_fcall trf_856(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_856(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_856(t0,t1);}

C_noret_decl(trf_872)
static void C_fcall trf_872(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_872(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_872(t0,t1);}

C_noret_decl(trf_454)
static void C_fcall trf_454(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_454(void *dummy){
C_word t4=C_pick(0);
C_word t3=C_pick(1);
C_word t2=C_pick(2);
C_word t1=C_pick(3);
C_word t0=C_pick(4);
C_adjust_stack(-5);
f_454(t0,t1,t2,t3,t4);}

C_noret_decl(trf_464)
static void C_fcall trf_464(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_464(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_464(t0,t1);}

C_noret_decl(trf_414)
static void C_fcall trf_414(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_414(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_414(t0,t1,t2);}

C_noret_decl(trf_427)
static void C_fcall trf_427(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_427(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_427(t0,t1);}

C_noret_decl(trf_374)
static void C_fcall trf_374(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_374(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_374(t0,t1,t2);}

C_noret_decl(trf_319)
static void C_fcall trf_319(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_319(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_319(t0,t1,t2);}

C_noret_decl(trf_307)
static void C_fcall trf_307(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_307(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_307(t0,t1);}

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
if(!C_demand_2(1084)){
C_save(t1);
C_rereclaim2(1084*sizeof(C_word), 1);
t1=C_restore;}
a=C_alloc(3);
C_initialize_lf(lf,130);
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
lf[10]=C_static_lambda_info(C_heaptop,42,"(insert-midi-note a2730 a2631 a2532 a2433)");
lf[11]=C_h_intern(&lf[11],12,"make-note-on");
lf[12]=C_static_lambda_info(C_heaptop,30,"(make-note-on t34 k35 v36 c37)");
lf[13]=C_h_intern(&lf[13],13,"make-note-off");
lf[14]=C_flonum(C_heaptop,0.0);
lf[15]=C_static_lambda_info(C_heaptop,27,"(make-note-off t38 k39 c40)");
lf[16]=C_h_intern(&lf[16],3,"now");
lf[17]=C_static_lambda_info(C_heaptop,5,"(now)");
lf[18]=C_h_intern(&lf[18],12,"make-process");
lf[19]=C_flonum(C_heaptop,-1.0);
lf[20]=C_static_lambda_info(C_heaptop,7,"(f_296)");
lf[21]=C_static_lambda_info(C_heaptop,35,"(make-process p44 num45 interval46)");
lf[22]=C_h_intern(&lf[22],6,"runran");
lf[23]=C_flonum(C_heaptop,0.0);
lf[24]=C_static_lambda_info(C_heaptop,10,"(do55 i57)");
lf[25]=C_static_lambda_info(C_heaptop,16,"(runran n52 d53)");
lf[26]=C_h_intern(&lf[26],7,"runproc");
lf[27]=C_flonum(C_heaptop,0.0);
lf[28]=C_flonum(C_heaptop,90.0);
lf[29]=C_flonum(C_heaptop,0.0);
lf[30]=C_static_lambda_info(C_heaptop,6,"(a357)");
lf[31]=C_static_lambda_info(C_heaptop,21,"(runproc k62 n63 d64)");
lf[34]=C_h_intern(&lf[34],5,"error");
lf[35]=C_h_intern(&lf[35],7,"sprintf");
lf[36]=C_static_lambda_info(C_heaptop,21,"(ferror str73 args74)");
lf[37]=C_h_intern(&lf[37],11,"expand-send");
lf[38]=C_static_lambda_info(C_heaptop,15,"(do102 tail104)");
lf[39]=C_static_string(C_heaptop,37,"~S found duplicate keyword \047~S\047 in ~S");
lf[40]=C_static_string(C_heaptop,33,"~S missing value for keyword \047~S\047");
lf[41]=C_static_string(C_heaptop,53,"~S found invalid keyword \047~S\047~%Available keywords: ~S");
lf[42]=C_h_intern(&lf[42],7,"\003sysmap");
lf[43]=C_h_intern(&lf[43],3,"car");
lf[44]=C_static_string(C_heaptop,32,"~S expected keyword but got \047~S\047");
lf[45]=C_h_intern(&lf[45],8,"keyword\077");
lf[46]=C_static_string(C_heaptop,35,"~S expected ~A arguments but got ~A");
lf[47]=C_static_lambda_info(C_heaptop,24,"(do85 key87 arg88 pos89)");
lf[48]=C_h_intern(&lf[48],6,"append");
lf[49]=C_static_string(C_heaptop,24,"~S is an invalid message");
lf[50]=C_static_lambda_info(C_heaptop,6,"(a600)");
lf[51]=C_h_intern(&lf[51],14,"hash-table-ref");
lf[52]=C_h_intern(&lf[52],14,"symbol->string");
lf[53]=C_static_lambda_info(C_heaptop,27,"(expand-send mesg75 data76)");
lf[54]=C_h_intern(&lf[54],7,"mp:note");
lf[55]=C_static_lambda_info(C_heaptop,46,"(mp:note time111 dur112 key113 amp114 chan115)");
lf[56]=C_h_intern(&lf[56],5,"mp:on");
lf[57]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[58]=C_static_lambda_info(C_heaptop,37,"(mp:on time117 key118 vel119 chan120)");
lf[59]=C_h_intern(&lf[59],6,"mp:off");
lf[60]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[61]=C_static_lambda_info(C_heaptop,38,"(mp:off time121 key122 vel123 chan124)");
lf[62]=C_h_intern(&lf[62],7,"mp:prog");
lf[63]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[64]=C_static_lambda_info(C_heaptop,33,"(mp:prog time125 prog126 chan127)");
lf[65]=C_h_intern(&lf[65],7,"mp:ctrl");
lf[66]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[67]=C_static_lambda_info(C_heaptop,40,"(mp:ctrl time128 ctrl129 val130 chan131)");
lf[68]=C_h_intern(&lf[68],9,"mp:alloff");
lf[69]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[70]=C_static_lambda_info(C_heaptop,11,"(mp:alloff)");
lf[71]=C_h_intern(&lf[71],8,"mp:micro");
lf[72]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[73]=C_static_lambda_info(C_heaptop,18,"(mp:micro divs132)");
lf[74]=C_h_intern(&lf[74],9,"mp:inhook");
lf[75]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[76]=C_static_lambda_info(C_heaptop,19,"(mp:inhook func133)");
lf[77]=C_h_intern(&lf[77],9,"expand-go");
lf[78]=C_h_intern(&lf[78],6,"lambda");
lf[79]=C_h_intern(&lf[79],1,"n");
lf[80]=C_h_intern(&lf[80],4,"set!");
lf[81]=C_h_intern(&lf[81],4,"wait");
lf[82]=C_h_intern(&lf[82],7,"elapsed");
lf[83]=C_h_intern(&lf[83],4,"else");
lf[84]=C_h_intern(&lf[84],4,"cond");
lf[85]=C_h_intern(&lf[85],4,"let*");
lf[86]=C_h_intern(&lf[86],10,"\003sysappend");
lf[87]=C_h_intern(&lf[87],6,"gensym");
lf[88]=C_h_intern(&lf[88],5,"\000null");
lf[89]=C_static_string(C_heaptop,43,"binding clause not a list (var init [step])");
lf[90]=C_static_lambda_info(C_heaptop,15,"(do146 tail148)");
lf[91]=C_static_string(C_heaptop,36,"go stopping clause missing test form");
lf[92]=C_static_string(C_heaptop,29,"go stopping clause not a list");
lf[93]=C_static_string(C_heaptop,22,"go bindings not a list");
lf[94]=C_static_lambda_info(C_heaptop,44,"(expand-go bindings140 terminate141 body142)");
lf[95]=C_h_intern(&lf[95],14,"return-to-host");
lf[96]=C_static_lambda_info(C_heaptop,41,"(a991 bindings137 terminate138 . body139)");
lf[97]=C_h_intern(&lf[97],18,"\003sysregister-macro");
lf[98]=C_h_intern(&lf[98],2,"go");
lf[99]=C_flonum(C_heaptop,0.0);
lf[100]=C_static_lambda_info(C_heaptop,24,"(a997 proc134 . time135)");
lf[101]=C_h_intern(&lf[101],6,"sprout");
lf[102]=C_h_intern(&lf[102],15,"hash-table-set!");
lf[103]=C_static_string(C_heaptop,9,"mp:inhook");
tmp=C_intern(C_heaptop,9,"mp:inhook");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000func");
C_save(tmp);
tmp=C_SCHEME_FALSE;
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[104]=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
lf[105]=C_static_string(C_heaptop,8,"mp:micro");
tmp=C_intern(C_heaptop,8,"mp:micro");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000divs");
C_save(tmp);
tmp=C_fix(1);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[106]=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
lf[107]=C_static_string(C_heaptop,9,"mp:alloff");
tmp=C_intern(C_heaptop,9,"mp:alloff");
C_save(tmp);
tmp=C_SCHEME_END_OF_LIST;
lf[108]=C_h_pair(C_restore,tmp);
lf[109]=C_static_string(C_heaptop,7,"mp:ctrl");
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
lf[110]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[111]=C_static_string(C_heaptop,7,"mp:prog");
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
lf[112]=C_h_list(4,C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(4);
lf[113]=C_static_string(C_heaptop,6,"mp:off");
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
lf[114]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[115]=C_static_string(C_heaptop,5,"mp:on");
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
lf[116]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[117]=C_static_string(C_heaptop,7,"mp:note");
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
lf[118]=C_h_list(6,C_pick(5),C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(6);
lf[119]=C_static_lambda_info(C_heaptop,25,"(a1014 mess109 . data110)");
lf[120]=C_h_intern(&lf[120],4,"send");
lf[121]=C_h_intern(&lf[121],5,"quote");
lf[122]=C_h_intern(&lf[122],10,"*messages*");
lf[123]=C_h_intern(&lf[123],14,"string->symbol");
lf[124]=C_static_string(C_heaptop,51,"message function not string, symbol or list of both");
lf[125]=C_static_lambda_info(C_heaptop,21,"(a1020 func67 info68)");
lf[126]=C_h_intern(&lf[126],19,"define-send-message");
lf[127]=C_h_intern(&lf[127],15,"make-hash-table");
lf[128]=C_h_intern(&lf[128],6,"equal\077");
lf[129]=C_static_lambda_info(C_heaptop,10,"(toplevel)");
C_register_lf2(lf,130,create_ptable());
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_207,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_library_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k205 */
static void C_ccall f_207(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_207,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_210,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_eval_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k208 in k205 */
static void C_ccall f_210(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_210,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_213,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k211 in k208 in k205 */
static void C_ccall f_213(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_213,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_216,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k214 in k211 in k208 in k205 */
static void C_ccall f_216(C_word c,C_word t0,C_word t1){
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
C_word ab[36],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_216,2,t0,t1);}
t2=C_mutate((C_word*)lf[0]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_218,a[2]=lf[2],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[3]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_232,a[2]=lf[4],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate((C_word*)lf[5]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_246,a[2]=lf[6],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate((C_word*)lf[7]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_253,a[2]=lf[8],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[9]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_260,a[2]=lf[10],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate((C_word*)lf[11]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_279,a[2]=lf[12],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate((C_word*)lf[13]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_285,a[2]=lf[15],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate((C_word*)lf[16]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_291,a[2]=lf[17],tmp=(C_word)a,a+=3,tmp));
t10=C_mutate((C_word*)lf[18]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_294,a[2]=lf[21],tmp=(C_word)a,a+=3,tmp));
t11=C_mutate((C_word*)lf[22]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_313,a[2]=lf[25],tmp=(C_word)a,a+=3,tmp));
t12=C_mutate((C_word*)lf[26]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_349,a[2]=lf[31],tmp=(C_word)a,a+=3,tmp));
t13=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_369,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("src/ChickenBridge.scm: 110  make-hash-table");
t14=C_retrieve(lf[127]);
((C_proc3)C_retrieve_proc(t14))(3,t14,t13,*((C_word*)lf[128]+1));}

/* k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_369(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_369,2,t0,t1);}
t2=C_mutate(&lf[32],t1);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_372,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1021,a[2]=lf[125],tmp=(C_word)a,a+=3,tmp);
C_trace("src/ChickenBridge.scm: 112  ##sys#register-macro");
t5=C_retrieve(lf[97]);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,lf[126],t4);}

/* a1020 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_1021(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_1021,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_1025,a[2]=t6,a[3]=t1,a[4]=t3,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t4)[1]))){
t8=(C_word)C_i_car(((C_word*)t4)[1]);
t9=C_set_block_item(t6,0,t8);
t10=(C_word)C_i_cadr(((C_word*)t4)[1]);
t11=C_set_block_item(t4,0,t10);
t12=t7;
f_1025(2,t12,t11);}
else{
if(C_truep((C_word)C_i_stringp(((C_word*)t4)[1]))){
t8=C_set_block_item(t6,0,((C_word*)t4)[1]);
t9=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1058,a[2]=t7,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
C_trace("src/ChickenBridge.scm: 119  string->symbol");
t10=*((C_word*)lf[123]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)t4)[1]);}
else{
if(C_truep((C_word)C_i_symbolp(((C_word*)t4)[1]))){
t8=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1068,a[2]=t7,a[3]=t6,tmp=(C_word)a,a+=4,tmp);
C_trace("src/ChickenBridge.scm: 121  symbol->string");
t9=*((C_word*)lf[52]+1);
((C_proc3)C_retrieve_proc(t9))(3,t9,t8,((C_word*)t4)[1]);}
else{
C_trace("src/ChickenBridge.scm: 123  error");
t8=*((C_word*)lf[34]+1);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,lf[124]);}}}}

/* k1066 in a1020 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_1068(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_1025(2,t3,t2);}

/* k1056 in a1020 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_1058(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_1025(2,t3,t2);}

/* k1023 in a1020 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_1025(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1025,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[4]);
t3=(C_word)C_a_i_list(&a,2,lf[121],t2);
t4=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_a_i_list(&a,4,lf[102],lf[122],((C_word*)((C_word*)t0)[2])[1],t3));}

/* k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_372(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_372,2,t0,t1);}
t2=C_mutate(&lf[33],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_374,a[2]=lf[36],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[37]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_384,a[2]=lf[53],tmp=(C_word)a,a+=3,tmp));
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_611,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1015,a[2]=lf[119],tmp=(C_word)a,a+=3,tmp);
C_trace("src/ChickenBridge.scm: 199  ##sys#register-macro");
t6=C_retrieve(lf[97]);
((C_proc4)C_retrieve_proc(t6))(4,t6,t4,lf[120],t5);}

/* a1014 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_1015(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr3r,(void*)f_1015r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_1015r(t0,t1,t2,t3);}}

static void C_ccall f_1015r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_trace("src/ChickenBridge.scm: 200  expand-send");
t4=C_retrieve(lf[37]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t1,t2,t3);}

/* k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_611(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_611,2,t0,t1);}
t2=C_mutate((C_word*)lf[54]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_613,a[2]=lf[55],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[56]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_626,a[2]=lf[58],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate((C_word*)lf[59]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_632,a[2]=lf[61],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate((C_word*)lf[62]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_638,a[2]=lf[64],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[65]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_644,a[2]=lf[67],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate((C_word*)lf[68]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_650,a[2]=lf[70],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate((C_word*)lf[71]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_656,a[2]=lf[73],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate((C_word*)lf[74]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_662,a[2]=lf[76],tmp=(C_word)a,a+=3,tmp));
t10=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_669,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("src/ChickenBridge.scm: 225  hash-table-set!");
t11=C_retrieve(lf[102]);
((C_proc5)C_retrieve_proc(t11))(5,t11,t10,lf[32],lf[117],lf[118]);}

/* k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_669(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_669,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_672,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("src/ChickenBridge.scm: 226  hash-table-set!");
t3=C_retrieve(lf[102]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[32],lf[115],lf[116]);}

/* k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_672(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_672,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_675,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("src/ChickenBridge.scm: 227  hash-table-set!");
t3=C_retrieve(lf[102]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[32],lf[113],lf[114]);}

/* k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_675(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_675,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_678,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("src/ChickenBridge.scm: 228  hash-table-set!");
t3=C_retrieve(lf[102]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[32],lf[111],lf[112]);}

/* k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_678(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_678,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_681,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("src/ChickenBridge.scm: 229  hash-table-set!");
t3=C_retrieve(lf[102]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[32],lf[109],lf[110]);}

/* k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_681(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_681,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_684,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("src/ChickenBridge.scm: 230  hash-table-set!");
t3=C_retrieve(lf[102]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[32],lf[107],lf[108]);}

/* k682 in k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_684(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_684,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_687,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("src/ChickenBridge.scm: 231  hash-table-set!");
t3=C_retrieve(lf[102]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[32],lf[105],lf[106]);}

/* k685 in k682 in k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_687(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_687,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_690,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("src/ChickenBridge.scm: 232  hash-table-set!");
t3=C_retrieve(lf[102]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[32],lf[103],lf[104]);}

/* k688 in k685 in k682 in k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_690(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_690,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_693,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_998,a[2]=lf[100],tmp=(C_word)a,a+=3,tmp);
C_trace("src/ChickenBridge.scm: 235  ##sys#register-macro");
t4=C_retrieve(lf[97]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,lf[101],t3);}

/* a997 in k688 in k685 in k682 in k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_998(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+7)){
C_save_and_reclaim((void*)tr3r,(void*)f_998r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_998r(t0,t1,t2,t3);}}

static void C_ccall f_998r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word *a=C_alloc(7);
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_1002,a[2]=t2,a[3]=t4,a[4]=t1,tmp=(C_word)a,a+=5,tmp);
if(C_truep((C_word)C_i_nullp(((C_word*)t4)[1]))){
t6=C_set_block_item(t4,0,lf[99]);
t7=t5;
f_1002(t7,t6);}
else{
t6=(C_word)C_i_car(((C_word*)t4)[1]);
t7=C_set_block_item(t4,0,t6);
t8=t5;
f_1002(t8,t7);}}

/* k1000 in a997 in k688 in k685 in k682 in k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_fcall f_1002(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("src/ChickenBridge.scm: 239  insert-process");
t2=*((C_word*)lf[5]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[4],((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]);}

/* k691 in k688 in k685 in k682 in k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_693(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_693,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_696,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_992,a[2]=lf[96],tmp=(C_word)a,a+=3,tmp);
C_trace("src/ChickenBridge.scm: 258  ##sys#register-macro");
t4=C_retrieve(lf[97]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,lf[98],t3);}

/* a991 in k691 in k688 in k685 in k682 in k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_992(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr4r,(void*)f_992r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest(a,C_rest_count(0));
f_992r(t0,t1,t2,t3,t4);}}

static void C_ccall f_992r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_trace("src/ChickenBridge.scm: 259  expand-go");
t5=C_retrieve(lf[77]);
((C_proc5)C_retrieve_proc(t5))(5,t5,t1,t2,t3,t4);}

/* k694 in k691 in k688 in k685 in k682 in k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_696(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_696,2,t0,t1);}
t2=C_mutate((C_word*)lf[77]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_698,a[2]=lf[94],tmp=(C_word)a,a+=3,tmp));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_990,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("src/ChickenBridge.scm: 310  return-to-host");
t4=C_retrieve(lf[95]);
((C_proc2)C_retrieve_proc(t4))(2,t4,t3);}

/* k988 in k694 in k691 in k688 in k685 in k682 in k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_990(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_UNDEFINED);}

/* expand-go in k694 in k691 in k688 in k685 in k682 in k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_698(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word t12;
C_word ab[15],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_698,5,t0,t1,t2,t3,t4);}
t5=C_SCHEME_END_OF_LIST;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=C_SCHEME_END_OF_LIST;
t8=(*a=C_VECTOR_TYPE|1,a[1]=t7,tmp=(C_word)a,a+=2,tmp);
t9=C_SCHEME_END_OF_LIST;
t10=(*a=C_VECTOR_TYPE|1,a[1]=t9,tmp=(C_word)a,a+=2,tmp);
t11=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_711,a[2]=t2,a[3]=t10,a[4]=t4,a[5]=t8,a[6]=t1,a[7]=t6,a[8]=t3,tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(t2))){
t12=t11;
f_711(2,t12,C_SCHEME_UNDEFINED);}
else{
C_trace("src/ChickenBridge.scm: 267  error");
t12=*((C_word*)lf[34]+1);
((C_proc4)C_retrieve_proc(t12))(4,t12,t11,lf[93],t2);}}

/* k709 in expand-go in k694 in k691 in k688 in k685 in k682 in k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_711(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_711,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_714,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(((C_word*)t0)[8]))){
if(C_truep((C_word)C_i_nullp(((C_word*)t0)[8]))){
C_trace("src/ChickenBridge.scm: 271  error");
t3=*((C_word*)lf[34]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,lf[91]);}
else{
t3=t2;
f_714(2,t3,C_SCHEME_UNDEFINED);}}
else{
C_trace("src/ChickenBridge.scm: 269  error");
t3=*((C_word*)lf[34]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t2,lf[92],((C_word*)t0)[8]);}}

/* k712 in k709 in expand-go in k694 in k691 in k688 in k685 in k682 in k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_714(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_714,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_717,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],tmp=(C_word)a,a+=8,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_827,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[7],a[5]=t4,a[6]=lf[90],tmp=(C_word)a,a+=7,tmp));
t6=((C_word*)t4)[1];
f_827(t6,t2,((C_word*)t0)[2]);}

/* do146 in k712 in k709 in expand-go in k694 in k691 in k688 in k685 in k682 in k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_fcall f_827(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_827,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_837,a[2]=t1,a[3]=((C_word*)t0)[5],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_847,a[2]=t3,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=t2,tmp=(C_word)a,a+=7,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_935,a[2]=t4,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t7=(C_word)C_i_car(t2);
t8=(C_word)C_i_length(t7);
C_trace("src/ChickenBridge.scm: 275  <");
C_lessp(5,0,t6,C_fix(0),t8,C_fix(4));}
else{
t6=t4;
f_847(t6,C_SCHEME_FALSE);}}}

/* k933 in do146 in k712 in k709 in expand-go in k694 in k691 in k688 in k685 in k682 in k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_935(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=(C_word)C_i_car(t2);
t4=((C_word*)t0)[2];
f_847(t4,(C_word)C_i_symbolp(t3));}
else{
t2=((C_word*)t0)[2];
f_847(t2,C_SCHEME_FALSE);}}

/* k845 in do146 in k712 in k709 in expand-go in k694 in k691 in k688 in k685 in k682 in k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_fcall f_847(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_847,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[6]);
t3=(C_word)C_i_car(t2);
t4=(C_word)C_i_car(((C_word*)t0)[6]);
t5=(C_word)C_i_cadr(t4);
t6=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_856,a[2]=t5,a[3]=t3,a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[5],tmp=(C_word)a,a+=8,tmp);
t7=(C_word)C_i_car(((C_word*)t0)[6]);
t8=(C_word)C_i_cddr(t7);
if(C_truep((C_word)C_i_nullp(t8))){
t9=t6;
f_856(t9,lf[88]);}
else{
t9=(C_word)C_i_car(((C_word*)t0)[6]);
t10=t6;
f_856(t10,(C_word)C_i_caddr(t9));}}
else{
t2=(C_word)C_i_car(((C_word*)t0)[6]);
C_trace("src/ChickenBridge.scm: 288  error");
t3=*((C_word*)lf[34]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[2],lf[89],t2);}}

/* k854 in k845 in do146 in k712 in k709 in expand-go in k694 in k691 in k688 in k685 in k682 in k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_fcall f_856(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_856,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_860,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t3=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
C_trace("src/ChickenBridge.scm: 283  append");
t4=*((C_word*)lf[48]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,((C_word*)((C_word*)t0)[7])[1],t3);}

/* k858 in k854 in k845 in do146 in k712 in k709 in expand-go in k694 in k691 in k688 in k685 in k682 in k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_860(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_860,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_864,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
t4=(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]);
C_trace("src/ChickenBridge.scm: 284  append");
t5=*((C_word*)lf[48]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,((C_word*)((C_word*)t0)[7])[1],t4);}

/* k862 in k858 in k854 in k845 in do146 in k712 in k709 in expand-go in k694 in k691 in k688 in k685 in k682 in k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_864(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_864,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_868,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_872,a[2]=((C_word*)t0)[5],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_eqp(((C_word*)t0)[3],lf[88]);
if(C_truep(t5)){
t6=t4;
f_872(t6,C_SCHEME_END_OF_LIST);}
else{
t6=(C_word)C_a_i_list(&a,3,lf[80],((C_word*)t0)[2],((C_word*)t0)[3]);
t7=t4;
f_872(t7,(C_word)C_a_i_list(&a,1,t6));}}

/* k870 in k862 in k858 in k854 in k845 in do146 in k712 in k709 in expand-go in k694 in k691 in k688 in k685 in k682 in k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_fcall f_872(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("src/ChickenBridge.scm: 285  append");
t2=*((C_word*)lf[48]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k866 in k862 in k858 in k854 in k845 in do146 in k712 in k709 in expand-go in k694 in k691 in k688 in k685 in k682 in k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_868(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_837(2,t3,t2);}

/* k835 in do146 in k712 in k709 in expand-go in k694 in k691 in k688 in k685 in k682 in k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_837(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_827(t3,((C_word*)t0)[2],t2);}

/* k715 in k712 in k709 in expand-go in k694 in k691 in k688 in k685 in k682 in k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_717(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_717,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_720,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("src/ChickenBridge.scm: 290  gensym");
t3=C_retrieve(lf[87]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k718 in k715 in k712 in k709 in expand-go in k694 in k691 in k688 in k685 in k682 in k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_720(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_720,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_723,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=t1,tmp=(C_word)a,a+=9,tmp);
C_trace("src/ChickenBridge.scm: 291  gensym");
t3=C_retrieve(lf[87]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k721 in k718 in k715 in k712 in k709 in expand-go in k694 in k691 in k688 in k685 in k682 in k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_723(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_723,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_726,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=t1,a[9]=((C_word*)t0)[8],tmp=(C_word)a,a+=10,tmp);
C_trace("src/ChickenBridge.scm: 292  gensym");
t3=C_retrieve(lf[87]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k724 in k721 in k718 in k715 in k712 in k709 in expand-go in k694 in k691 in k688 in k685 in k682 in k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_726(C_word c,C_word t0,C_word t1){
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
C_word ab[95],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_726,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,2,((C_word*)t0)[9],((C_word*)t0)[8]);
t3=(C_word)C_a_i_list(&a,2,t1,C_fix(0));
t4=(C_word)C_a_i_list(&a,3,lf[78],C_SCHEME_END_OF_LIST,((C_word*)t0)[9]);
t5=(C_word)C_a_i_list(&a,2,lf[16],t4);
t6=(C_word)C_a_i_list(&a,1,lf[79]);
t7=(C_word)C_a_i_list(&a,3,lf[80],t1,lf[79]);
t8=(C_word)C_a_i_list(&a,3,lf[78],t6,t7);
t9=(C_word)C_a_i_list(&a,2,lf[81],t8);
t10=(C_word)C_a_i_list(&a,3,lf[78],C_SCHEME_END_OF_LIST,((C_word*)t0)[8]);
t11=(C_word)C_a_i_list(&a,2,lf[82],t10);
t12=(C_word)C_a_i_list(&a,4,t3,t5,t9,t11);
t13=(C_word)C_i_car(((C_word*)t0)[7]);
t14=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_781,a[2]=((C_word*)t0)[2],a[3]=t1,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=t2,a[9]=t12,a[10]=t13,tmp=(C_word)a,a+=11,tmp);
t15=(C_word)C_i_cdr(((C_word*)t0)[7]);
t16=(C_word)C_a_i_list(&a,1,C_fix(-1));
C_trace("##sys#append");
t17=*((C_word*)lf[86]+1);
((C_proc4)(void*)(*((C_word*)t17+1)))(4,t17,t14,t15,t16);}

/* k779 in k724 in k721 in k718 in k715 in k712 in k709 in expand-go in k694 in k691 in k688 in k685 in k682 in k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_781(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[18],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_781,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[10],t1);
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_765,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],a[5]=((C_word*)t0)[8],a[6]=((C_word*)t0)[9],a[7]=t2,tmp=(C_word)a,a+=8,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_769,a[2]=((C_word*)t0)[4],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
C_trace("##sys#append");
t6=*((C_word*)lf[86]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t4,((C_word*)((C_word*)t0)[2])[1],t5);}

/* k767 in k779 in k724 in k721 in k718 in k715 in k712 in k709 in expand-go in k694 in k691 in k688 in k685 in k682 in k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_769(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("##sys#append");
t2=*((C_word*)lf[86]+1);
((C_proc4)(void*)(*((C_word*)t2+1)))(4,t2,((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k763 in k779 in k724 in k721 in k718 in k715 in k712 in k709 in expand-go in k694 in k691 in k688 in k685 in k682 in k679 in k676 in k673 in k670 in k667 in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_765(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[42],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_765,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,lf[83],t1);
t3=(C_word)C_a_i_list(&a,3,lf[84],((C_word*)t0)[7],t2);
t4=(C_word)C_a_i_list(&a,3,lf[85],((C_word*)t0)[6],t3);
t5=(C_word)C_a_i_list(&a,3,lf[78],((C_word*)t0)[5],t4);
t6=(C_word)C_a_i_list(&a,3,lf[78],((C_word*)((C_word*)t0)[4])[1],t5);
t7=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)C_a_i_cons(&a,2,t6,((C_word*)((C_word*)t0)[2])[1]));}

/* mp:inhook in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_662(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_662,3,t0,t1,t2);}
C_trace("src/ChickenBridge.scm: 221  error");
t3=*((C_word*)lf[34]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[75]);}

/* mp:micro in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_656(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_656,3,t0,t1,t2);}
C_trace("src/ChickenBridge.scm: 219  error");
t3=*((C_word*)lf[34]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[72]);}

/* mp:alloff in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_650(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_650,2,t0,t1);}
C_trace("src/ChickenBridge.scm: 217  error");
t2=*((C_word*)lf[34]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,t1,lf[69]);}

/* mp:ctrl in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_644(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_644,6,t0,t1,t2,t3,t4,t5);}
C_trace("src/ChickenBridge.scm: 215  error");
t6=*((C_word*)lf[34]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[66]);}

/* mp:prog in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_638(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_638,5,t0,t1,t2,t3,t4);}
C_trace("src/ChickenBridge.scm: 213  error");
t5=*((C_word*)lf[34]+1);
((C_proc3)C_retrieve_proc(t5))(3,t5,t1,lf[63]);}

/* mp:off in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_632(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_632,6,t0,t1,t2,t3,t4,t5);}
C_trace("src/ChickenBridge.scm: 211  error");
t6=*((C_word*)lf[34]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[60]);}

/* mp:on in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_626(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_626,6,t0,t1,t2,t3,t4,t5);}
C_trace("src/ChickenBridge.scm: 209  error");
t6=*((C_word*)lf[34]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[57]);}

/* mp:note in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_613(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
C_word tmp;
C_word t7;
C_word t8;
C_word ab[7],*a=ab;
if(c!=7) C_bad_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr7,(void*)f_613,7,t0,t1,t2,t3,t4,t5,t6);}
t7=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_617,a[2]=t6,a[3]=t4,a[4]=t1,a[5]=t3,a[6]=t2,tmp=(C_word)a,a+=7,tmp);
C_trace("src/ChickenBridge.scm: 205  make-note-on");
t8=*((C_word*)lf[11]+1);
((C_proc6)C_retrieve_proc(t8))(6,t8,t7,t2,t4,t5,t6);}

/* k615 in mp:note in k609 in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_617(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_617,2,t0,t1);}
t2=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[6],((C_word*)t0)[5]);
C_trace("src/ChickenBridge.scm: 206  make-note-off");
t3=*((C_word*)lf[13]+1);
((C_proc5)C_retrieve_proc(t3))(5,t3,((C_word*)t0)[4],t2,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* expand-send in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_384(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word ab[6],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_384,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_388,a[2]=t1,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_symbolp(t2))){
C_trace("src/ChickenBridge.scm: 130  symbol->string");
t6=*((C_word*)lf[52]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t5,t2);}
else{
t6=t5;
f_388(2,t6,t2);}}

/* k386 in expand-send in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_388(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_388,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_391,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_601,a[2]=lf[50],tmp=(C_word)a,a+=3,tmp);
C_trace("src/ChickenBridge.scm: 131  hash-table-ref");
t4=*((C_word*)lf[51]+1);
((C_proc5)C_retrieve_proc(t4))(5,t4,t2,lf[32],t1,t3);}

/* a600 in k386 in expand-send in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_601(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_601,2,t0,t1);}
t2=t1;
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}

/* k389 in k386 in expand-send in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_391(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_391,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_394,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=t1;
if(C_truep(t3)){
t4=t2;
f_394(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("src/ChickenBridge.scm: 132  ferror");
f_374(t2,lf[49],(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]));}}

/* k392 in k389 in k386 in expand-send in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_394(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_394,2,t0,t1);}
t2=((C_word*)((C_word*)t0)[5])[1];
t3=(C_word)C_i_car(((C_word*)t0)[4]);
t4=(C_word)C_i_cdr(((C_word*)t0)[4]);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(C_word)C_i_length(t4);
t8=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_406,a[2]=t7,a[3]=t2,a[4]=((C_word*)t0)[2],a[5]=t6,a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[3],a[8]=t4,a[9]=t3,tmp=(C_word)a,a+=10,tmp);
C_trace("src/ChickenBridge.scm: 139  append");
t9=*((C_word*)lf[48]+1);
((C_proc4)C_retrieve_proc(t9))(4,t9,t8,t4,C_SCHEME_END_OF_LIST);}

/* k404 in k392 in k389 in k386 in expand-send in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_406(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[19],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_406,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_409,a[2]=((C_word*)t0)[7],a[3]=((C_word*)t0)[8],a[4]=t1,a[5]=((C_word*)t0)[9],tmp=(C_word)a,a+=6,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_454,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[5],a[8]=t4,a[9]=((C_word*)t0)[6],a[10]=lf[47],tmp=(C_word)a,a+=11,tmp));
t6=((C_word*)t4)[1];
f_454(t6,t2,C_SCHEME_FALSE,C_SCHEME_FALSE,C_fix(0));}

/* do85 in k404 in k392 in k389 in k386 in expand-send in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_fcall f_454(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
C_save_and_reclaim((void*)trf_454,NULL,5,t0,t1,t2,t3,t4);}
t5=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[9])[1]))){
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,C_SCHEME_FALSE);}
else{
t8=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_464,a[2]=t7,a[3]=t6,a[4]=t5,a[5]=t1,a[6]=((C_word*)t0)[8],tmp=(C_word)a,a+=7,tmp);
t9=(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_470,a[2]=((C_word*)t0)[2],a[3]=t7,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=t6,a[8]=((C_word*)t0)[6],a[9]=t5,a[10]=((C_word*)t0)[9],a[11]=t8,a[12]=((C_word*)t0)[7],tmp=(C_word)a,a+=13,tmp);
t10=((C_word*)((C_word*)t0)[7])[1];
if(C_truep(t10)){
t11=t9;
f_470(2,t11,C_SCHEME_FALSE);}
else{
t11=(C_word)C_i_car(((C_word*)((C_word*)t0)[9])[1]);
C_trace("src/ChickenBridge.scm: 150  keyword?");
t12=C_retrieve(lf[45]);
((C_proc3)C_retrieve_proc(t12))(3,t12,t9,t11);}}}

/* k468 in do85 in k404 in k392 in k389 in k386 in expand-send in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_470(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_470,2,t0,t1);}
if(C_truep(t1)){
t2=C_set_block_item(((C_word*)t0)[12],0,C_SCHEME_TRUE);
t3=((C_word*)t0)[11];
f_464(t3,t2);}
else{
t2=((C_word*)((C_word*)t0)[12])[1];
if(C_truep(t2)){
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[10])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[9])+1,t3);
t5=(C_word)C_i_assoc(((C_word*)((C_word*)t0)[9])[1],((C_word*)t0)[8]);
t6=C_mutate(((C_word *)((C_word*)t0)[7])+1,t5);
t7=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[10])[1]);
t8=C_mutate(((C_word *)((C_word*)t0)[10])+1,t7);
t9=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_524,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[9],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[11],a[6]=((C_word*)t0)[10],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t10=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_579,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[9],a[5]=((C_word*)t0)[5],a[6]=t9,a[7]=((C_word*)t0)[10],tmp=(C_word)a,a+=8,tmp);
C_trace("src/ChickenBridge.scm: 170  keyword?");
t11=C_retrieve(lf[45]);
((C_proc3)C_retrieve_proc(t11))(3,t11,t10,((C_word*)((C_word*)t0)[9])[1]);}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_480,a[2]=((C_word*)t0)[11],a[3]=((C_word*)t0)[10],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[6],tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_nequalp(((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]))){
t4=(C_word)C_i_length(((C_word*)t0)[4]);
C_trace("src/ChickenBridge.scm: 160  ferror");
f_374(t3,lf[46],(C_word)C_a_i_list(&a,3,((C_word*)t0)[5],((C_word*)t0)[2],t4));}
else{
t4=t3;
f_480(2,t4,C_SCHEME_UNDEFINED);}}}}

/* k478 in k468 in do85 in k404 in k392 in k389 in k386 in expand-send in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_480(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_480,2,t0,t1);}
t2=(C_word)C_i_list_tail(((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]);
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
t4=(C_word)C_i_set_car(t2,t3);
t5=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[3])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t5);
t7=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[4])[1],C_fix(1));
t8=C_mutate(((C_word *)((C_word*)t0)[4])+1,t7);
t9=((C_word*)t0)[2];
f_464(t9,t8);}

/* k577 in k468 in do85 in k404 in k392 in k389 in k386 in expand-send in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_579(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_579,2,t0,t1);}
if(C_truep(t1)){
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[7])[1]))){
C_trace("src/ChickenBridge.scm: 174  ferror");
f_374(((C_word*)t0)[6],lf[40],(C_word)C_a_i_list(&a,2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]));}
else{
t2=((C_word*)((C_word*)t0)[3])[1];
if(C_truep(t2)){
t3=((C_word*)t0)[6];
f_524(2,t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_575,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
C_trace("map");
t4=*((C_word*)lf[42]+1);
((C_proc4)(void*)(*((C_word*)t4+1)))(4,t4,t3,*((C_word*)lf[43]+1),((C_word*)t0)[2]);}}}
else{
C_trace("src/ChickenBridge.scm: 171  ferror");
f_374(((C_word*)t0)[6],lf[44],(C_word)C_a_i_list(&a,2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]));}}

/* k573 in k577 in k468 in do85 in k404 in k392 in k389 in k386 in expand-send in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_575(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_575,2,t0,t1);}
C_trace("src/ChickenBridge.scm: 177  ferror");
f_374(((C_word*)t0)[4],lf[41],(C_word)C_a_i_list(&a,3,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1));}

/* k522 in k468 in do85 in k404 in k392 in k389 in k386 in expand-send in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_524(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[14],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_524,2,t0,t1);}
t2=(C_word)C_i_member(((C_word*)((C_word*)t0)[8])[1],((C_word*)t0)[7]);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_530,a[2]=((C_word*)t0)[5],a[3]=t2,a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
if(C_truep(t2)){
t4=t3;
f_530(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("src/ChickenBridge.scm: 184  ferror");
f_374(t3,lf[39],(C_word)C_a_i_list(&a,3,((C_word*)t0)[4],((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]));}}

/* k528 in k522 in k468 in do85 in k404 in k392 in k389 in k386 in expand-send in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_530(C_word c,C_word t0,C_word t1){
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
f_464(t6,t5);}

/* k462 in do85 in k404 in k392 in k389 in k386 in expand-send in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_fcall f_464(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[6])[1];
f_454(t2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k407 in k404 in k392 in k389 in k386 in expand-send in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_409(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_409,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_414,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=lf[38],tmp=(C_word)a,a+=7,tmp));
t5=((C_word*)t3)[1];
f_414(t5,((C_word*)t0)[2],((C_word*)t0)[4]);}

/* do102 in k407 in k404 in k392 in k389 in k386 in expand-send in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_fcall f_414(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_414,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[5],((C_word*)t0)[4]));}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_427,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_member(t4,((C_word*)t0)[2]))){
t5=(C_word)C_i_car(t2);
t6=(C_word)C_i_cadr(t5);
t7=t3;
f_427(t7,(C_word)C_i_set_car(t2,t6));}
else{
t5=t3;
f_427(t5,C_SCHEME_UNDEFINED);}}}

/* k425 in do102 in k407 in k404 in k392 in k389 in k386 in expand-send in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_fcall f_427(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_414(t3,((C_word*)t0)[2],t2);}

/* ferror in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_fcall f_374(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_374,NULL,3,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_382,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_apply(5,0,t4,C_retrieve(lf[35]),t2,t3);}

/* k380 in ferror in k370 in k367 in k214 in k211 in k208 in k205 */
static void C_ccall f_382(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("src/ChickenBridge.scm: 127  error");
t2=*((C_word*)lf[34]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* runproc in k214 in k211 in k208 in k205 */
static void C_ccall f_349(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[7],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_349,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_353,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_358,a[2]=t2,a[3]=lf[30],tmp=(C_word)a,a+=4,tmp);
C_trace("src/ChickenBridge.scm: 101  make-process");
t7=*((C_word*)lf[18]+1);
((C_proc5)C_retrieve_proc(t7))(5,t7,t5,t6,t3,t4);}

/* a357 in runproc in k214 in k211 in k208 in k205 */
static void C_ccall f_358(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_358,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_362,a[2]=((C_word*)t0)[2],a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("src/ChickenBridge.scm: 103  insert-midi-note");
t3=*((C_word*)lf[9]+1);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[29],((C_word*)t0)[2],C_fix(100));}

/* k360 in a357 in runproc in k214 in k211 in k208 in k205 */
static void C_ccall f_362(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("src/ChickenBridge.scm: 104  insert-midi-note");
t2=*((C_word*)lf[9]+1);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[3],lf[28],((C_word*)t0)[2],C_fix(0));}

/* k351 in runproc in k214 in k211 in k208 in k205 */
static void C_ccall f_353(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("src/ChickenBridge.scm: 106  insert-process");
t2=*((C_word*)lf[5]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[2],lf[27],t1);}

/* runran in k214 in k211 in k208 in k205 */
static void C_ccall f_313(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_313,4,t0,t1,t2,t3);}
t4=lf[23];
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_SCHEME_UNDEFINED;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=C_set_block_item(t7,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_319,a[2]=t7,a[3]=t3,a[4]=t5,a[5]=t2,a[6]=lf[24],tmp=(C_word)a,a+=7,tmp));
t9=((C_word*)t7)[1];
f_319(t9,t1,C_fix(0));}

/* do55 in runran in k214 in k211 in k208 in k205 */
static void C_fcall f_319(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_319,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_greaterp(t2,((C_word*)t0)[5]))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_329,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=t2,a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],tmp=(C_word)a,a+=7,tmp);
C_trace("src/ChickenBridge.scm: 96   insert-midi-note");
t4=*((C_word*)lf[9]+1);
((C_proc5)C_retrieve_proc(t4))(5,t4,t3,((C_word*)((C_word*)t0)[4])[1],C_fix(60),C_fix(100));}}

/* k327 in do55 in runran in k214 in k211 in k208 in k205 */
static void C_ccall f_329(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_329,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_332,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
t3=(C_word)C_a_i_plus(&a,2,C_fix(200),((C_word*)((C_word*)t0)[6])[1]);
C_trace("src/ChickenBridge.scm: 97   insert-midi-note");
t4=*((C_word*)lf[9]+1);
((C_proc5)C_retrieve_proc(t4))(5,t4,t2,t3,C_fix(60),C_fix(0));}

/* k330 in k327 in do55 in runran in k214 in k211 in k208 in k205 */
static void C_ccall f_332(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_332,2,t0,t1);}
t2=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[6])[1],((C_word*)t0)[5]);
t3=C_mutate(((C_word *)((C_word*)t0)[6])+1,t2);
t4=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[4],C_fix(1));
t5=((C_word*)((C_word*)t0)[3])[1];
f_319(t5,((C_word*)t0)[2],t4);}

/* make-process in k214 in k211 in k208 in k205 */
static void C_ccall f_294(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
C_save_and_reclaim((void*)tr5,(void*)f_294,5,t0,t1,t2,t3,t4);}
t5=t4;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=C_fix(0);
t8=(*a=C_VECTOR_TYPE|1,a[1]=t7,tmp=(C_word)a,a+=2,tmp);
t9=t1;
((C_proc2)(void*)(*((C_word*)t9+1)))(2,t9,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_296,a[2]=t2,a[3]=t3,a[4]=t6,a[5]=t8,a[6]=lf[20],tmp=(C_word)a,a+=7,tmp));}

/* f_296 in make-process in k214 in k211 in k208 in k205 */
static void C_ccall f_296(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_296,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_300,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=t1,a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
t3=((C_word*)t0)[2];
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k298 */
static void C_ccall f_300(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_300,2,t0,t1);}
t2=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[5])[1],C_fix(1));
t3=C_mutate(((C_word *)((C_word*)t0)[5])+1,t2);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_307,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_greaterp(((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[2]))){
t5=C_mutate(((C_word *)((C_word*)t0)[3])+1,lf[19]);
t6=t4;
f_307(t6,t5);}
else{
t5=t4;
f_307(t5,C_SCHEME_UNDEFINED);}}

/* k305 in k298 */
static void C_fcall f_307(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,((C_word*)((C_word*)t0)[2])[1]);}

/* now in k214 in k211 in k208 in k205 */
static void C_ccall f_291(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_291,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(4));
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)stub41(t2));}

/* make-note-off in k214 in k211 in k208 in k205 */
static void C_ccall f_285(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_285,5,t0,t1,t2,t3,t4);}
C_trace("src/ChickenBridge.scm: 73   insert-midi-note");
t5=*((C_word*)lf[9]+1);
((C_proc6)C_retrieve_proc(t5))(6,t5,t1,t2,t3,lf[14],t4);}

/* make-note-on in k214 in k211 in k208 in k205 */
static void C_ccall f_279(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_279,6,t0,t1,t2,t3,t4,t5);}
C_trace("src/ChickenBridge.scm: 69   insert-midi-note");
t6=*((C_word*)lf[9]+1);
((C_proc6)C_retrieve_proc(t6))(6,t6,t1,t2,t3,t4,t5);}

/* insert-midi-note in k214 in k211 in k208 in k205 */
static void C_ccall f_260(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_260,6,t0,t1,t2,t3,t4,t5);}
t6=(C_word)C_i_foreign_flonum_argumentp(t2);
t7=(C_word)C_i_foreign_flonum_argumentp(t3);
t8=(C_word)C_i_foreign_flonum_argumentp(t4);
t9=(C_word)C_i_foreign_flonum_argumentp(t5);
t10=t1;
((C_proc2)(void*)(*((C_word*)t10+1)))(2,t10,(C_word)stub28(C_SCHEME_UNDEFINED,t6,t7,t8,t9));}

/* insert-closure in k214 in k211 in k208 in k205 */
static void C_ccall f_253(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word *a;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_253,4,t0,t1,t2,t3);}
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub20(C_SCHEME_UNDEFINED,t4,t3));}

/* insert-process in k214 in k211 in k208 in k205 */
static void C_ccall f_246(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word *a;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_246,4,t0,t1,t2,t3);}
t4=(C_word)C_i_foreign_flonum_argumentp(t2);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,(C_word)stub14(C_SCHEME_UNDEFINED,t4,t3));}

/* print-error in k214 in k211 in k208 in k205 */
static void C_ccall f_232(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_232,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_237,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[1]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_237(2,t4,C_SCHEME_FALSE);}}

/* k235 in print-error in k214 in k211 in k208 in k205 */
static void C_ccall f_237(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub7(C_SCHEME_UNDEFINED,t1));}

/* print-message in k214 in k211 in k208 in k205 */
static void C_ccall f_218(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_218,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_223,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[1]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_223(2,t4,C_SCHEME_FALSE);}}

/* k221 in print-message in k214 in k211 in k208 in k205 */
static void C_ccall f_223(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub1(C_SCHEME_UNDEFINED,t1));}

#ifdef C_ENABLE_PTABLES
static C_PTABLE_ENTRY ptable[97] = {
{"toplevelsrc/ChickenBridge.scm",(void*)C_grace_toplevel},
{"f_207src/ChickenBridge.scm",(void*)f_207},
{"f_210src/ChickenBridge.scm",(void*)f_210},
{"f_213src/ChickenBridge.scm",(void*)f_213},
{"f_216src/ChickenBridge.scm",(void*)f_216},
{"f_369src/ChickenBridge.scm",(void*)f_369},
{"f_1021src/ChickenBridge.scm",(void*)f_1021},
{"f_1068src/ChickenBridge.scm",(void*)f_1068},
{"f_1058src/ChickenBridge.scm",(void*)f_1058},
{"f_1025src/ChickenBridge.scm",(void*)f_1025},
{"f_372src/ChickenBridge.scm",(void*)f_372},
{"f_1015src/ChickenBridge.scm",(void*)f_1015},
{"f_611src/ChickenBridge.scm",(void*)f_611},
{"f_669src/ChickenBridge.scm",(void*)f_669},
{"f_672src/ChickenBridge.scm",(void*)f_672},
{"f_675src/ChickenBridge.scm",(void*)f_675},
{"f_678src/ChickenBridge.scm",(void*)f_678},
{"f_681src/ChickenBridge.scm",(void*)f_681},
{"f_684src/ChickenBridge.scm",(void*)f_684},
{"f_687src/ChickenBridge.scm",(void*)f_687},
{"f_690src/ChickenBridge.scm",(void*)f_690},
{"f_998src/ChickenBridge.scm",(void*)f_998},
{"f_1002src/ChickenBridge.scm",(void*)f_1002},
{"f_693src/ChickenBridge.scm",(void*)f_693},
{"f_992src/ChickenBridge.scm",(void*)f_992},
{"f_696src/ChickenBridge.scm",(void*)f_696},
{"f_990src/ChickenBridge.scm",(void*)f_990},
{"f_698src/ChickenBridge.scm",(void*)f_698},
{"f_711src/ChickenBridge.scm",(void*)f_711},
{"f_714src/ChickenBridge.scm",(void*)f_714},
{"f_827src/ChickenBridge.scm",(void*)f_827},
{"f_935src/ChickenBridge.scm",(void*)f_935},
{"f_847src/ChickenBridge.scm",(void*)f_847},
{"f_856src/ChickenBridge.scm",(void*)f_856},
{"f_860src/ChickenBridge.scm",(void*)f_860},
{"f_864src/ChickenBridge.scm",(void*)f_864},
{"f_872src/ChickenBridge.scm",(void*)f_872},
{"f_868src/ChickenBridge.scm",(void*)f_868},
{"f_837src/ChickenBridge.scm",(void*)f_837},
{"f_717src/ChickenBridge.scm",(void*)f_717},
{"f_720src/ChickenBridge.scm",(void*)f_720},
{"f_723src/ChickenBridge.scm",(void*)f_723},
{"f_726src/ChickenBridge.scm",(void*)f_726},
{"f_781src/ChickenBridge.scm",(void*)f_781},
{"f_769src/ChickenBridge.scm",(void*)f_769},
{"f_765src/ChickenBridge.scm",(void*)f_765},
{"f_662src/ChickenBridge.scm",(void*)f_662},
{"f_656src/ChickenBridge.scm",(void*)f_656},
{"f_650src/ChickenBridge.scm",(void*)f_650},
{"f_644src/ChickenBridge.scm",(void*)f_644},
{"f_638src/ChickenBridge.scm",(void*)f_638},
{"f_632src/ChickenBridge.scm",(void*)f_632},
{"f_626src/ChickenBridge.scm",(void*)f_626},
{"f_613src/ChickenBridge.scm",(void*)f_613},
{"f_617src/ChickenBridge.scm",(void*)f_617},
{"f_384src/ChickenBridge.scm",(void*)f_384},
{"f_388src/ChickenBridge.scm",(void*)f_388},
{"f_601src/ChickenBridge.scm",(void*)f_601},
{"f_391src/ChickenBridge.scm",(void*)f_391},
{"f_394src/ChickenBridge.scm",(void*)f_394},
{"f_406src/ChickenBridge.scm",(void*)f_406},
{"f_454src/ChickenBridge.scm",(void*)f_454},
{"f_470src/ChickenBridge.scm",(void*)f_470},
{"f_480src/ChickenBridge.scm",(void*)f_480},
{"f_579src/ChickenBridge.scm",(void*)f_579},
{"f_575src/ChickenBridge.scm",(void*)f_575},
{"f_524src/ChickenBridge.scm",(void*)f_524},
{"f_530src/ChickenBridge.scm",(void*)f_530},
{"f_464src/ChickenBridge.scm",(void*)f_464},
{"f_409src/ChickenBridge.scm",(void*)f_409},
{"f_414src/ChickenBridge.scm",(void*)f_414},
{"f_427src/ChickenBridge.scm",(void*)f_427},
{"f_374src/ChickenBridge.scm",(void*)f_374},
{"f_382src/ChickenBridge.scm",(void*)f_382},
{"f_349src/ChickenBridge.scm",(void*)f_349},
{"f_358src/ChickenBridge.scm",(void*)f_358},
{"f_362src/ChickenBridge.scm",(void*)f_362},
{"f_353src/ChickenBridge.scm",(void*)f_353},
{"f_313src/ChickenBridge.scm",(void*)f_313},
{"f_319src/ChickenBridge.scm",(void*)f_319},
{"f_329src/ChickenBridge.scm",(void*)f_329},
{"f_332src/ChickenBridge.scm",(void*)f_332},
{"f_294src/ChickenBridge.scm",(void*)f_294},
{"f_296src/ChickenBridge.scm",(void*)f_296},
{"f_300src/ChickenBridge.scm",(void*)f_300},
{"f_307src/ChickenBridge.scm",(void*)f_307},
{"f_291src/ChickenBridge.scm",(void*)f_291},
{"f_285src/ChickenBridge.scm",(void*)f_285},
{"f_279src/ChickenBridge.scm",(void*)f_279},
{"f_260src/ChickenBridge.scm",(void*)f_260},
{"f_253src/ChickenBridge.scm",(void*)f_253},
{"f_246src/ChickenBridge.scm",(void*)f_246},
{"f_232src/ChickenBridge.scm",(void*)f_232},
{"f_237src/ChickenBridge.scm",(void*)f_237},
{"f_218src/ChickenBridge.scm",(void*)f_218},
{"f_223src/ChickenBridge.scm",(void*)f_223},
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
