/* Generated from ChickenBridge.scm by the CHICKEN compiler
   http://www.call-with-current-continuation.org
   2007-10-21 20:32
   Version 2.724 - macosx-unix-gnu-x86 - [ manyargs dload ptables applyhook ]
(c)2000-2007 Felix L. Winkelmann | compiled 2007-10-12 on todd-ingalls-computer-2.local (Darwin)
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


/* from k291 */
C_noret_decl(stub32)
static void C_ccall stub32(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2,C_word C_a3) C_noret;
static void C_ccall stub32(C_word C_c,C_word C_self,C_word C_k,C_word C_buf,C_word C_a0,C_word C_a1,C_word C_a2,C_word C_a3){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
double t0=(double )C_c_double(C_a0);
float t1=(float )C_c_double(C_a1);
float t2=(float )C_c_double(C_a2);
float t3=(float )C_c_double(C_a3);
int C_level=C_save_callback_continuation(&C_a,C_k);
insert_midi_note(t0,t1,t2,t3);
C_k=C_restore_callback_continuation2(C_level);
C_kontinue(C_k,C_r);}

/* from k266 */
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

/* from k253 */
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

/* from k233 in print-error in k212 in k209 in k206 in k203 */
static C_word C_fcall stub7(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub7(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_error(t0);
return C_r;}

/* from k219 in print-message in k212 in k209 in k206 in k203 */
static C_word C_fcall stub1(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub1(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_mess(t0);
return C_r;}

C_noret_decl(C_grace_toplevel)
C_externexport void C_ccall C_grace_toplevel(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_205)
static void C_ccall f_205(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_208)
static void C_ccall f_208(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_211)
static void C_ccall f_211(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_214)
static void C_ccall f_214(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_382)
static void C_ccall f_382(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1014)
static void C_ccall f_1014(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_1061)
static void C_ccall f_1061(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1051)
static void C_ccall f_1051(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1018)
static void C_ccall f_1018(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_385)
static void C_ccall f_385(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1008)
static void C_ccall f_1008(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_1008)
static void C_ccall f_1008r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_624)
static void C_ccall f_624(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_682)
static void C_ccall f_682(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_685)
static void C_ccall f_685(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_688)
static void C_ccall f_688(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_691)
static void C_ccall f_691(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_694)
static void C_ccall f_694(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_697)
static void C_ccall f_697(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_700)
static void C_ccall f_700(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_703)
static void C_ccall f_703(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1002)
static void C_ccall f_1002(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_1002)
static void C_ccall f_1002r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_706)
static void C_ccall f_706(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1000)
static void C_ccall f_1000(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_708)
static void C_ccall f_708(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_721)
static void C_ccall f_721(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_724)
static void C_ccall f_724(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_837)
static void C_fcall f_837(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_945)
static void C_ccall f_945(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_857)
static void C_fcall f_857(C_word t0,C_word t1) C_noret;
C_noret_decl(f_866)
static void C_fcall f_866(C_word t0,C_word t1) C_noret;
C_noret_decl(f_870)
static void C_ccall f_870(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_874)
static void C_ccall f_874(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_882)
static void C_fcall f_882(C_word t0,C_word t1) C_noret;
C_noret_decl(f_878)
static void C_ccall f_878(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_847)
static void C_ccall f_847(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_727)
static void C_ccall f_727(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_730)
static void C_ccall f_730(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_733)
static void C_ccall f_733(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_736)
static void C_ccall f_736(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_791)
static void C_ccall f_791(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_779)
static void C_ccall f_779(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_775)
static void C_ccall f_775(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_675)
static void C_ccall f_675(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_669)
static void C_ccall f_669(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_663)
static void C_ccall f_663(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_657)
static void C_ccall f_657(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_651)
static void C_ccall f_651(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_645)
static void C_ccall f_645(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_639)
static void C_ccall f_639(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_626)
static void C_ccall f_626(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_630)
static void C_ccall f_630(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_397)
static void C_ccall f_397(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_401)
static void C_ccall f_401(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_614)
static void C_ccall f_614(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_404)
static void C_ccall f_404(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_407)
static void C_ccall f_407(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_419)
static void C_ccall f_419(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_467)
static void C_fcall f_467(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_483)
static void C_ccall f_483(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_493)
static void C_ccall f_493(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_592)
static void C_ccall f_592(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_588)
static void C_ccall f_588(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_537)
static void C_ccall f_537(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_543)
static void C_ccall f_543(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_477)
static void C_fcall f_477(C_word t0,C_word t1) C_noret;
C_noret_decl(f_422)
static void C_ccall f_422(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_427)
static void C_fcall f_427(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_440)
static void C_fcall f_440(C_word t0,C_word t1) C_noret;
C_noret_decl(f_387)
static void C_fcall f_387(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_395)
static void C_ccall f_395(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_362)
static void C_ccall f_362(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_371)
static void C_ccall f_371(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_375)
static void C_ccall f_375(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_366)
static void C_ccall f_366(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_326)
static void C_ccall f_326(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_332)
static void C_fcall f_332(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_342)
static void C_ccall f_342(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_345)
static void C_ccall f_345(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_307)
static void C_ccall f_307(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_309)
static void C_ccall f_309(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_313)
static void C_ccall f_313(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_320)
static void C_fcall f_320(C_word t0,C_word t1) C_noret;
C_noret_decl(f_301)
static void C_ccall f_301(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_295)
static void C_ccall f_295(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_270)
static void C_ccall f_270(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_274)
static void C_ccall f_274(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_257)
static void C_ccall f_257(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_261)
static void C_ccall f_261(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_244)
static void C_ccall f_244(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_248)
static void C_ccall f_248(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_230)
static void C_ccall f_230(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_235)
static void C_ccall f_235(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_216)
static void C_ccall f_216(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_221)
static void C_ccall f_221(C_word c,C_word t0,C_word t1) C_noret;

C_noret_decl(trf_837)
static void C_fcall trf_837(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_837(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_837(t0,t1,t2);}

C_noret_decl(trf_857)
static void C_fcall trf_857(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_857(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_857(t0,t1);}

C_noret_decl(trf_866)
static void C_fcall trf_866(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_866(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_866(t0,t1);}

C_noret_decl(trf_882)
static void C_fcall trf_882(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_882(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_882(t0,t1);}

C_noret_decl(trf_467)
static void C_fcall trf_467(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_467(void *dummy){
C_word t4=C_pick(0);
C_word t3=C_pick(1);
C_word t2=C_pick(2);
C_word t1=C_pick(3);
C_word t0=C_pick(4);
C_adjust_stack(-5);
f_467(t0,t1,t2,t3,t4);}

C_noret_decl(trf_477)
static void C_fcall trf_477(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_477(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_477(t0,t1);}

C_noret_decl(trf_427)
static void C_fcall trf_427(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_427(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_427(t0,t1,t2);}

C_noret_decl(trf_440)
static void C_fcall trf_440(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_440(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_440(t0,t1);}

C_noret_decl(trf_387)
static void C_fcall trf_387(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_387(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_387(t0,t1,t2);}

C_noret_decl(trf_332)
static void C_fcall trf_332(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_332(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_332(t0,t1,t2);}

C_noret_decl(trf_320)
static void C_fcall trf_320(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_320(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_320(t0,t1);}

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
if(!C_demand_2(1080)){
C_save(t1);
C_rereclaim2(1080*sizeof(C_word), 1);
t1=C_restore;}
a=C_alloc(3);
C_initialize_lf(lf,130);
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
lf[14]=C_static_lambda_info(C_heaptop,42,"(insert-midi-note a3134 a3035 a2936 a2837)");
lf[15]=C_h_intern(&lf[15],12,"make-note-on");
lf[16]=C_static_lambda_info(C_heaptop,30,"(make-note-on t40 k41 v42 c43)");
lf[17]=C_h_intern(&lf[17],13,"make-note-off");
lf[18]=C_flonum(C_heaptop,0.0);
lf[19]=C_static_lambda_info(C_heaptop,27,"(make-note-off t44 k45 c46)");
lf[20]=C_h_intern(&lf[20],12,"make-process");
lf[21]=C_flonum(C_heaptop,-1.0);
lf[22]=C_static_lambda_info(C_heaptop,7,"(f_309)");
lf[23]=C_static_lambda_info(C_heaptop,35,"(make-process p47 num48 interval49)");
lf[24]=C_h_intern(&lf[24],6,"runran");
lf[25]=C_flonum(C_heaptop,0.0);
lf[26]=C_static_lambda_info(C_heaptop,10,"(do58 i60)");
lf[27]=C_static_lambda_info(C_heaptop,16,"(runran n55 d56)");
lf[28]=C_h_intern(&lf[28],7,"runproc");
lf[29]=C_flonum(C_heaptop,0.0);
lf[30]=C_flonum(C_heaptop,90.0);
lf[31]=C_flonum(C_heaptop,0.0);
lf[32]=C_static_lambda_info(C_heaptop,6,"(a370)");
lf[33]=C_static_lambda_info(C_heaptop,21,"(runproc k65 n66 d67)");
lf[36]=C_h_intern(&lf[36],5,"error");
lf[37]=C_h_intern(&lf[37],7,"sprintf");
lf[38]=C_static_lambda_info(C_heaptop,21,"(ferror str76 args77)");
lf[39]=C_h_intern(&lf[39],11,"expand-send");
lf[40]=C_static_lambda_info(C_heaptop,15,"(do105 tail107)");
lf[41]=C_static_string(C_heaptop,37,"~S found duplicate keyword \047~S\047 in ~S");
lf[42]=C_static_string(C_heaptop,33,"~S missing value for keyword \047~S\047");
lf[43]=C_static_string(C_heaptop,53,"~S found invalid keyword \047~S\047~%Available keywords: ~S");
lf[44]=C_h_intern(&lf[44],7,"\003sysmap");
lf[45]=C_h_intern(&lf[45],3,"car");
lf[46]=C_static_string(C_heaptop,32,"~S expected keyword but got \047~S\047");
lf[47]=C_h_intern(&lf[47],8,"keyword\077");
lf[48]=C_static_string(C_heaptop,35,"~S expected ~A arguments but got ~A");
lf[49]=C_static_lambda_info(C_heaptop,24,"(do88 key90 arg91 pos92)");
lf[50]=C_h_intern(&lf[50],6,"append");
lf[51]=C_static_string(C_heaptop,24,"~S is an invalid message");
lf[52]=C_static_lambda_info(C_heaptop,6,"(a613)");
lf[53]=C_h_intern(&lf[53],14,"hash-table-ref");
lf[54]=C_h_intern(&lf[54],14,"symbol->string");
lf[55]=C_static_lambda_info(C_heaptop,27,"(expand-send mesg78 data79)");
lf[56]=C_h_intern(&lf[56],7,"mp:note");
lf[57]=C_static_lambda_info(C_heaptop,46,"(mp:note time114 dur115 key116 amp117 chan118)");
lf[58]=C_h_intern(&lf[58],5,"mp:on");
lf[59]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[60]=C_static_lambda_info(C_heaptop,37,"(mp:on time120 key121 vel122 chan123)");
lf[61]=C_h_intern(&lf[61],6,"mp:off");
lf[62]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[63]=C_static_lambda_info(C_heaptop,38,"(mp:off time124 key125 vel126 chan127)");
lf[64]=C_h_intern(&lf[64],7,"mp:prog");
lf[65]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[66]=C_static_lambda_info(C_heaptop,33,"(mp:prog time128 prog129 chan130)");
lf[67]=C_h_intern(&lf[67],7,"mp:ctrl");
lf[68]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[69]=C_static_lambda_info(C_heaptop,40,"(mp:ctrl time131 ctrl132 val133 chan134)");
lf[70]=C_h_intern(&lf[70],9,"mp:alloff");
lf[71]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[72]=C_static_lambda_info(C_heaptop,11,"(mp:alloff)");
lf[73]=C_h_intern(&lf[73],8,"mp:micro");
lf[74]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[75]=C_static_lambda_info(C_heaptop,18,"(mp:micro divs135)");
lf[76]=C_h_intern(&lf[76],9,"mp:inhook");
lf[77]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[78]=C_static_lambda_info(C_heaptop,19,"(mp:inhook func136)");
lf[79]=C_h_intern(&lf[79],9,"expand-go");
lf[80]=C_h_intern(&lf[80],6,"lambda");
lf[81]=C_h_intern(&lf[81],3,"now");
lf[82]=C_h_intern(&lf[82],1,"n");
lf[83]=C_h_intern(&lf[83],4,"set!");
lf[84]=C_h_intern(&lf[84],4,"wait");
lf[85]=C_h_intern(&lf[85],7,"elapsed");
lf[86]=C_h_intern(&lf[86],4,"else");
lf[87]=C_h_intern(&lf[87],4,"cond");
lf[88]=C_h_intern(&lf[88],4,"let*");
lf[89]=C_h_intern(&lf[89],10,"\003sysappend");
lf[90]=C_h_intern(&lf[90],6,"gensym");
lf[91]=C_h_intern(&lf[91],5,"\000null");
lf[92]=C_static_string(C_heaptop,43,"binding clause not a list (var init [step])");
lf[93]=C_static_lambda_info(C_heaptop,15,"(do146 tail148)");
lf[94]=C_static_string(C_heaptop,36,"go stopping clause missing test form");
lf[95]=C_static_string(C_heaptop,29,"go stopping clause not a list");
lf[96]=C_static_string(C_heaptop,22,"go bindings not a list");
lf[97]=C_static_lambda_info(C_heaptop,44,"(expand-go bindings140 terminate141 body142)");
lf[98]=C_h_intern(&lf[98],14,"return-to-host");
lf[99]=C_static_lambda_info(C_heaptop,42,"(a1001 bindings137 terminate138 . body139)");
lf[100]=C_h_intern(&lf[100],18,"\003sysregister-macro");
lf[101]=C_h_intern(&lf[101],2,"go");
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
lf[119]=C_static_lambda_info(C_heaptop,25,"(a1007 mess112 . data113)");
lf[120]=C_h_intern(&lf[120],4,"send");
lf[121]=C_h_intern(&lf[121],5,"quote");
lf[122]=C_h_intern(&lf[122],10,"*messages*");
lf[123]=C_h_intern(&lf[123],14,"string->symbol");
lf[124]=C_static_string(C_heaptop,51,"message function not string, symbol or list of both");
lf[125]=C_static_lambda_info(C_heaptop,21,"(a1013 func70 info71)");
lf[126]=C_h_intern(&lf[126],19,"define-send-message");
lf[127]=C_h_intern(&lf[127],15,"make-hash-table");
lf[128]=C_h_intern(&lf[128],6,"equal\077");
lf[129]=C_static_lambda_info(C_heaptop,10,"(toplevel)");
C_register_lf2(lf,130,create_ptable());
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_205,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_library_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k203 */
static void C_ccall f_205(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_205,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_208,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_eval_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k206 in k203 */
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

/* k209 in k206 in k203 */
static void C_ccall f_211(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_211,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_214,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k212 in k209 in k206 in k203 */
static void C_ccall f_214(C_word c,C_word t0,C_word t1){
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
C_word ab[33],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_214,2,t0,t1);}
t2=C_mutate((C_word*)lf[0]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_216,a[2]=lf[2],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[3]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_230,a[2]=lf[4],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate((C_word*)lf[5]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_244,a[2]=lf[8],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate((C_word*)lf[9]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_257,a[2]=lf[11],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[12]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_270,a[2]=lf[14],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate((C_word*)lf[15]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_295,a[2]=lf[16],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate((C_word*)lf[17]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_301,a[2]=lf[19],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate((C_word*)lf[20]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_307,a[2]=lf[23],tmp=(C_word)a,a+=3,tmp));
t10=C_mutate((C_word*)lf[24]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_326,a[2]=lf[27],tmp=(C_word)a,a+=3,tmp));
t11=C_mutate((C_word*)lf[28]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_362,a[2]=lf[33],tmp=(C_word)a,a+=3,tmp));
t12=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_382,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 114  make-hash-table");
t13=C_retrieve(lf[127]);
((C_proc3)C_retrieve_proc(t13))(3,t13,t12,*((C_word*)lf[128]+1));}

/* k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_382(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_382,2,t0,t1);}
t2=C_mutate(&lf[34],t1);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_385,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1014,a[2]=lf[125],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 116  ##sys#register-macro");
t5=C_retrieve(lf[100]);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,lf[126],t4);}

/* a1013 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_1014(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_1014,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_1018,a[2]=t6,a[3]=t1,a[4]=t3,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t4)[1]))){
t8=(C_word)C_i_car(((C_word*)t4)[1]);
t9=C_set_block_item(t6,0,t8);
t10=(C_word)C_i_cadr(((C_word*)t4)[1]);
t11=C_set_block_item(t4,0,t10);
t12=t7;
f_1018(2,t12,t11);}
else{
if(C_truep((C_word)C_i_stringp(((C_word*)t4)[1]))){
t8=C_set_block_item(t6,0,((C_word*)t4)[1]);
t9=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1051,a[2]=t7,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 123  string->symbol");
t10=*((C_word*)lf[123]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)t4)[1]);}
else{
if(C_truep((C_word)C_i_symbolp(((C_word*)t4)[1]))){
t8=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1061,a[2]=t7,a[3]=t6,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 125  symbol->string");
t9=*((C_word*)lf[54]+1);
((C_proc3)C_retrieve_proc(t9))(3,t9,t8,((C_word*)t4)[1]);}
else{
C_trace("ChickenBridge.scm: 127  error");
t8=*((C_word*)lf[36]+1);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,lf[124]);}}}}

/* k1059 in a1013 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_1061(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_1018(2,t3,t2);}

/* k1049 in a1013 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_1051(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_1018(2,t3,t2);}

/* k1016 in a1013 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_1018(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1018,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[4]);
t3=(C_word)C_a_i_list(&a,2,lf[121],t2);
t4=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_a_i_list(&a,4,lf[102],lf[122],((C_word*)((C_word*)t0)[2])[1],t3));}

/* k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_385(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_385,2,t0,t1);}
t2=C_mutate(&lf[35],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_387,a[2]=lf[38],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[39]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_397,a[2]=lf[55],tmp=(C_word)a,a+=3,tmp));
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_624,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1008,a[2]=lf[119],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 203  ##sys#register-macro");
t6=C_retrieve(lf[100]);
((C_proc4)C_retrieve_proc(t6))(4,t6,t4,lf[120],t5);}

/* a1007 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_1008(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr3r,(void*)f_1008r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_1008r(t0,t1,t2,t3);}}

static void C_ccall f_1008r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_trace("ChickenBridge.scm: 204  expand-send");
t4=C_retrieve(lf[39]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t1,t2,t3);}

/* k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_624(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_624,2,t0,t1);}
t2=C_mutate((C_word*)lf[56]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_626,a[2]=lf[57],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[58]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_639,a[2]=lf[60],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate((C_word*)lf[61]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_645,a[2]=lf[63],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate((C_word*)lf[64]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_651,a[2]=lf[66],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[67]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_657,a[2]=lf[69],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate((C_word*)lf[70]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_663,a[2]=lf[72],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate((C_word*)lf[73]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_669,a[2]=lf[75],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate((C_word*)lf[76]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_675,a[2]=lf[78],tmp=(C_word)a,a+=3,tmp));
t10=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_682,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 229  hash-table-set!");
t11=C_retrieve(lf[102]);
((C_proc5)C_retrieve_proc(t11))(5,t11,t10,lf[34],lf[117],lf[118]);}

/* k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_682(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_682,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_685,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 230  hash-table-set!");
t3=C_retrieve(lf[102]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[34],lf[115],lf[116]);}

/* k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_685(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_685,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_688,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 231  hash-table-set!");
t3=C_retrieve(lf[102]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[34],lf[113],lf[114]);}

/* k686 in k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_688(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_688,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_691,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 232  hash-table-set!");
t3=C_retrieve(lf[102]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[34],lf[111],lf[112]);}

/* k689 in k686 in k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_691(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_691,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_694,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 233  hash-table-set!");
t3=C_retrieve(lf[102]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[34],lf[109],lf[110]);}

/* k692 in k689 in k686 in k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_694(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_694,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_697,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 234  hash-table-set!");
t3=C_retrieve(lf[102]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[34],lf[107],lf[108]);}

/* k695 in k692 in k689 in k686 in k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_697(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_697,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_700,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 235  hash-table-set!");
t3=C_retrieve(lf[102]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[34],lf[105],lf[106]);}

/* k698 in k695 in k692 in k689 in k686 in k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_700(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_700,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_703,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 236  hash-table-set!");
t3=C_retrieve(lf[102]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[34],lf[103],lf[104]);}

/* k701 in k698 in k695 in k692 in k689 in k686 in k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_703(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_703,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_706,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1002,a[2]=lf[99],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 258  ##sys#register-macro");
t4=C_retrieve(lf[100]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,lf[101],t3);}

/* a1001 in k701 in k698 in k695 in k692 in k689 in k686 in k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_1002(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr4r,(void*)f_1002r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest(a,C_rest_count(0));
f_1002r(t0,t1,t2,t3,t4);}}

static void C_ccall f_1002r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_trace("ChickenBridge.scm: 259  expand-go");
t5=C_retrieve(lf[79]);
((C_proc5)C_retrieve_proc(t5))(5,t5,t1,t2,t3,t4);}

/* k704 in k701 in k698 in k695 in k692 in k689 in k686 in k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_706(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_706,2,t0,t1);}
t2=C_mutate((C_word*)lf[79]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_708,a[2]=lf[97],tmp=(C_word)a,a+=3,tmp));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1000,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 309  return-to-host");
t4=C_retrieve(lf[98]);
((C_proc2)C_retrieve_proc(t4))(2,t4,t3);}

/* k998 in k704 in k701 in k698 in k695 in k692 in k689 in k686 in k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_1000(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_UNDEFINED);}

/* expand-go in k704 in k701 in k698 in k695 in k692 in k689 in k686 in k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_708(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
C_save_and_reclaim((void*)tr5,(void*)f_708,5,t0,t1,t2,t3,t4);}
t5=C_SCHEME_END_OF_LIST;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=C_SCHEME_END_OF_LIST;
t8=(*a=C_VECTOR_TYPE|1,a[1]=t7,tmp=(C_word)a,a+=2,tmp);
t9=C_SCHEME_END_OF_LIST;
t10=(*a=C_VECTOR_TYPE|1,a[1]=t9,tmp=(C_word)a,a+=2,tmp);
t11=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_721,a[2]=t2,a[3]=t10,a[4]=t4,a[5]=t8,a[6]=t1,a[7]=t6,a[8]=t3,tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(t2))){
t12=t11;
f_721(2,t12,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 267  error");
t12=*((C_word*)lf[36]+1);
((C_proc4)C_retrieve_proc(t12))(4,t12,t11,lf[96],t2);}}

/* k719 in expand-go in k704 in k701 in k698 in k695 in k692 in k689 in k686 in k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_721(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_721,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_724,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(((C_word*)t0)[8]))){
if(C_truep((C_word)C_i_nullp(((C_word*)t0)[8]))){
C_trace("ChickenBridge.scm: 271  error");
t3=*((C_word*)lf[36]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,lf[94]);}
else{
t3=t2;
f_724(2,t3,C_SCHEME_UNDEFINED);}}
else{
C_trace("ChickenBridge.scm: 269  error");
t3=*((C_word*)lf[36]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t2,lf[95],((C_word*)t0)[8]);}}

/* k722 in k719 in expand-go in k704 in k701 in k698 in k695 in k692 in k689 in k686 in k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_724(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_724,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_727,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],tmp=(C_word)a,a+=8,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_837,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[7],a[5]=t4,a[6]=lf[93],tmp=(C_word)a,a+=7,tmp));
t6=((C_word*)t4)[1];
f_837(t6,t2,((C_word*)t0)[2]);}

/* do146 in k722 in k719 in expand-go in k704 in k701 in k698 in k695 in k692 in k689 in k686 in k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_fcall f_837(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_837,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_847,a[2]=t1,a[3]=((C_word*)t0)[5],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_857,a[2]=t3,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=t2,tmp=(C_word)a,a+=7,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_945,a[2]=t4,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t7=(C_word)C_i_car(t2);
t8=(C_word)C_i_length(t7);
C_trace("ChickenBridge.scm: 275  <");
C_lessp(5,0,t6,C_fix(0),t8,C_fix(4));}
else{
t6=t4;
f_857(t6,C_SCHEME_FALSE);}}}

/* k943 in do146 in k722 in k719 in expand-go in k704 in k701 in k698 in k695 in k692 in k689 in k686 in k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_945(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=(C_word)C_i_car(t2);
t4=((C_word*)t0)[2];
f_857(t4,(C_word)C_i_symbolp(t3));}
else{
t2=((C_word*)t0)[2];
f_857(t2,C_SCHEME_FALSE);}}

/* k855 in do146 in k722 in k719 in expand-go in k704 in k701 in k698 in k695 in k692 in k689 in k686 in k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_fcall f_857(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_857,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[6]);
t3=(C_word)C_i_car(t2);
t4=(C_word)C_i_car(((C_word*)t0)[6]);
t5=(C_word)C_i_cadr(t4);
t6=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_866,a[2]=t5,a[3]=t3,a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[5],tmp=(C_word)a,a+=8,tmp);
t7=(C_word)C_i_car(((C_word*)t0)[6]);
t8=(C_word)C_i_cddr(t7);
if(C_truep((C_word)C_i_nullp(t8))){
t9=t6;
f_866(t9,lf[91]);}
else{
t9=(C_word)C_i_car(((C_word*)t0)[6]);
t10=t6;
f_866(t10,(C_word)C_i_caddr(t9));}}
else{
t2=(C_word)C_i_car(((C_word*)t0)[6]);
C_trace("ChickenBridge.scm: 288  error");
t3=*((C_word*)lf[36]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[2],lf[92],t2);}}

/* k864 in k855 in do146 in k722 in k719 in expand-go in k704 in k701 in k698 in k695 in k692 in k689 in k686 in k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_fcall f_866(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_866,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_870,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t3=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 283  append");
t4=*((C_word*)lf[50]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,((C_word*)((C_word*)t0)[7])[1],t3);}

/* k868 in k864 in k855 in do146 in k722 in k719 in expand-go in k704 in k701 in k698 in k695 in k692 in k689 in k686 in k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_870(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_870,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_874,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
t4=(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 284  append");
t5=*((C_word*)lf[50]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,((C_word*)((C_word*)t0)[7])[1],t4);}

/* k872 in k868 in k864 in k855 in do146 in k722 in k719 in expand-go in k704 in k701 in k698 in k695 in k692 in k689 in k686 in k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_874(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_874,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_878,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_882,a[2]=((C_word*)t0)[5],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_eqp(((C_word*)t0)[3],lf[91]);
if(C_truep(t5)){
t6=t4;
f_882(t6,C_SCHEME_END_OF_LIST);}
else{
t6=(C_word)C_a_i_list(&a,3,lf[83],((C_word*)t0)[2],((C_word*)t0)[3]);
t7=t4;
f_882(t7,(C_word)C_a_i_list(&a,1,t6));}}

/* k880 in k872 in k868 in k864 in k855 in do146 in k722 in k719 in expand-go in k704 in k701 in k698 in k695 in k692 in k689 in k686 in k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_fcall f_882(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 285  append");
t2=*((C_word*)lf[50]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k876 in k872 in k868 in k864 in k855 in do146 in k722 in k719 in expand-go in k704 in k701 in k698 in k695 in k692 in k689 in k686 in k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_878(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_847(2,t3,t2);}

/* k845 in do146 in k722 in k719 in expand-go in k704 in k701 in k698 in k695 in k692 in k689 in k686 in k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_847(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_837(t3,((C_word*)t0)[2],t2);}

/* k725 in k722 in k719 in expand-go in k704 in k701 in k698 in k695 in k692 in k689 in k686 in k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_727(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_727,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_730,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 290  gensym");
t3=C_retrieve(lf[90]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k728 in k725 in k722 in k719 in expand-go in k704 in k701 in k698 in k695 in k692 in k689 in k686 in k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_730(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_730,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_733,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=t1,tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 291  gensym");
t3=C_retrieve(lf[90]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k731 in k728 in k725 in k722 in k719 in expand-go in k704 in k701 in k698 in k695 in k692 in k689 in k686 in k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_733(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_733,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_736,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=t1,a[9]=((C_word*)t0)[8],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 292  gensym");
t3=C_retrieve(lf[90]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k734 in k731 in k728 in k725 in k722 in k719 in expand-go in k704 in k701 in k698 in k695 in k692 in k689 in k686 in k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_736(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_736,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,2,((C_word*)t0)[9],((C_word*)t0)[8]);
t3=(C_word)C_a_i_list(&a,2,t1,C_fix(0));
t4=(C_word)C_a_i_list(&a,3,lf[80],C_SCHEME_END_OF_LIST,((C_word*)t0)[9]);
t5=(C_word)C_a_i_list(&a,2,lf[81],t4);
t6=(C_word)C_a_i_list(&a,1,lf[82]);
t7=(C_word)C_a_i_list(&a,3,lf[83],t1,lf[82]);
t8=(C_word)C_a_i_list(&a,3,lf[80],t6,t7);
t9=(C_word)C_a_i_list(&a,2,lf[84],t8);
t10=(C_word)C_a_i_list(&a,3,lf[80],C_SCHEME_END_OF_LIST,((C_word*)t0)[8]);
t11=(C_word)C_a_i_list(&a,2,lf[85],t10);
t12=(C_word)C_a_i_list(&a,4,t3,t5,t9,t11);
t13=(C_word)C_i_car(((C_word*)t0)[7]);
t14=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_791,a[2]=((C_word*)t0)[2],a[3]=t1,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=t2,a[9]=t12,a[10]=t13,tmp=(C_word)a,a+=11,tmp);
t15=(C_word)C_i_cdr(((C_word*)t0)[7]);
t16=(C_word)C_a_i_list(&a,1,C_fix(-1));
C_trace("##sys#append");
t17=*((C_word*)lf[89]+1);
((C_proc4)(void*)(*((C_word*)t17+1)))(4,t17,t14,t15,t16);}

/* k789 in k734 in k731 in k728 in k725 in k722 in k719 in expand-go in k704 in k701 in k698 in k695 in k692 in k689 in k686 in k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_791(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[18],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_791,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[10],t1);
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_775,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],a[5]=((C_word*)t0)[8],a[6]=((C_word*)t0)[9],a[7]=t2,tmp=(C_word)a,a+=8,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_779,a[2]=((C_word*)t0)[4],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
C_trace("##sys#append");
t6=*((C_word*)lf[89]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t4,((C_word*)((C_word*)t0)[2])[1],t5);}

/* k777 in k789 in k734 in k731 in k728 in k725 in k722 in k719 in expand-go in k704 in k701 in k698 in k695 in k692 in k689 in k686 in k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_779(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("##sys#append");
t2=*((C_word*)lf[89]+1);
((C_proc4)(void*)(*((C_word*)t2+1)))(4,t2,((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k773 in k789 in k734 in k731 in k728 in k725 in k722 in k719 in expand-go in k704 in k701 in k698 in k695 in k692 in k689 in k686 in k683 in k680 in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_775(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_775,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,lf[86],t1);
t3=(C_word)C_a_i_list(&a,3,lf[87],((C_word*)t0)[7],t2);
t4=(C_word)C_a_i_list(&a,3,lf[88],((C_word*)t0)[6],t3);
t5=(C_word)C_a_i_list(&a,3,lf[80],((C_word*)t0)[5],t4);
t6=(C_word)C_a_i_list(&a,3,lf[80],((C_word*)((C_word*)t0)[4])[1],t5);
t7=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)C_a_i_cons(&a,2,t6,((C_word*)((C_word*)t0)[2])[1]));}

/* mp:inhook in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_675(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_675,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 225  error");
t3=*((C_word*)lf[36]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[77]);}

/* mp:micro in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_669(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_669,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 223  error");
t3=*((C_word*)lf[36]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[74]);}

/* mp:alloff in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_663(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_663,2,t0,t1);}
C_trace("ChickenBridge.scm: 221  error");
t2=*((C_word*)lf[36]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,t1,lf[71]);}

/* mp:ctrl in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_657(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_657,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 219  error");
t6=*((C_word*)lf[36]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[68]);}

/* mp:prog in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_651(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_651,5,t0,t1,t2,t3,t4);}
C_trace("ChickenBridge.scm: 217  error");
t5=*((C_word*)lf[36]+1);
((C_proc3)C_retrieve_proc(t5))(3,t5,t1,lf[65]);}

/* mp:off in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_645(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_645,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 215  error");
t6=*((C_word*)lf[36]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[62]);}

/* mp:on in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_639(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_639,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 213  error");
t6=*((C_word*)lf[36]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[59]);}

/* mp:note in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_626(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
C_word tmp;
C_word t7;
C_word t8;
C_word ab[7],*a=ab;
if(c!=7) C_bad_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr7,(void*)f_626,7,t0,t1,t2,t3,t4,t5,t6);}
t7=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_630,a[2]=t6,a[3]=t4,a[4]=t1,a[5]=t3,a[6]=t2,tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 209  make-note-on");
t8=*((C_word*)lf[15]+1);
((C_proc6)C_retrieve_proc(t8))(6,t8,t7,t2,t4,t5,t6);}

/* k628 in mp:note in k622 in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_630(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_630,2,t0,t1);}
t2=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[6],((C_word*)t0)[5]);
C_trace("ChickenBridge.scm: 210  make-note-off");
t3=*((C_word*)lf[17]+1);
((C_proc5)C_retrieve_proc(t3))(5,t3,((C_word*)t0)[4],t2,((C_word*)t0)[3],((C_word*)t0)[2]);}

/* expand-send in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_397(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word ab[6],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_397,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_401,a[2]=t1,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_symbolp(t2))){
C_trace("ChickenBridge.scm: 134  symbol->string");
t6=*((C_word*)lf[54]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t5,t2);}
else{
t6=t5;
f_401(2,t6,t2);}}

/* k399 in expand-send in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_401(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_401,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_404,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_614,a[2]=lf[52],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 135  hash-table-ref");
t4=*((C_word*)lf[53]+1);
((C_proc5)C_retrieve_proc(t4))(5,t4,t2,lf[34],t1,t3);}

/* a613 in k399 in expand-send in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_614(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_614,2,t0,t1);}
t2=t1;
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}

/* k402 in k399 in expand-send in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_404(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_404,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_407,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=t1;
if(C_truep(t3)){
t4=t2;
f_407(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 136  ferror");
f_387(t2,lf[51],(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]));}}

/* k405 in k402 in k399 in expand-send in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_407(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_407,2,t0,t1);}
t2=((C_word*)((C_word*)t0)[5])[1];
t3=(C_word)C_i_car(((C_word*)t0)[4]);
t4=(C_word)C_i_cdr(((C_word*)t0)[4]);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(C_word)C_i_length(t4);
t8=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_419,a[2]=t7,a[3]=t2,a[4]=((C_word*)t0)[2],a[5]=t6,a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[3],a[8]=t4,a[9]=t3,tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 143  append");
t9=*((C_word*)lf[50]+1);
((C_proc4)C_retrieve_proc(t9))(4,t9,t8,t4,C_SCHEME_END_OF_LIST);}

/* k417 in k405 in k402 in k399 in expand-send in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_419(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[19],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_419,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_422,a[2]=((C_word*)t0)[7],a[3]=((C_word*)t0)[8],a[4]=t1,a[5]=((C_word*)t0)[9],tmp=(C_word)a,a+=6,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_467,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[5],a[8]=t4,a[9]=((C_word*)t0)[6],a[10]=lf[49],tmp=(C_word)a,a+=11,tmp));
t6=((C_word*)t4)[1];
f_467(t6,t2,C_SCHEME_FALSE,C_SCHEME_FALSE,C_fix(0));}

/* do88 in k417 in k405 in k402 in k399 in expand-send in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_fcall f_467(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
C_save_and_reclaim((void*)trf_467,NULL,5,t0,t1,t2,t3,t4);}
t5=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[9])[1]))){
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,C_SCHEME_FALSE);}
else{
t8=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_477,a[2]=t7,a[3]=t6,a[4]=t5,a[5]=t1,a[6]=((C_word*)t0)[8],tmp=(C_word)a,a+=7,tmp);
t9=(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_483,a[2]=((C_word*)t0)[2],a[3]=t7,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=t6,a[8]=((C_word*)t0)[6],a[9]=t5,a[10]=((C_word*)t0)[9],a[11]=t8,a[12]=((C_word*)t0)[7],tmp=(C_word)a,a+=13,tmp);
t10=((C_word*)((C_word*)t0)[7])[1];
if(C_truep(t10)){
t11=t9;
f_483(2,t11,C_SCHEME_FALSE);}
else{
t11=(C_word)C_i_car(((C_word*)((C_word*)t0)[9])[1]);
C_trace("ChickenBridge.scm: 154  keyword?");
t12=C_retrieve(lf[47]);
((C_proc3)C_retrieve_proc(t12))(3,t12,t9,t11);}}}

/* k481 in do88 in k417 in k405 in k402 in k399 in expand-send in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_483(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_483,2,t0,t1);}
if(C_truep(t1)){
t2=C_set_block_item(((C_word*)t0)[12],0,C_SCHEME_TRUE);
t3=((C_word*)t0)[11];
f_477(t3,t2);}
else{
t2=((C_word*)((C_word*)t0)[12])[1];
if(C_truep(t2)){
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[10])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[9])+1,t3);
t5=(C_word)C_i_assoc(((C_word*)((C_word*)t0)[9])[1],((C_word*)t0)[8]);
t6=C_mutate(((C_word *)((C_word*)t0)[7])+1,t5);
t7=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[10])[1]);
t8=C_mutate(((C_word *)((C_word*)t0)[10])+1,t7);
t9=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_537,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[9],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[11],a[6]=((C_word*)t0)[10],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t10=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_592,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[9],a[5]=((C_word*)t0)[5],a[6]=t9,a[7]=((C_word*)t0)[10],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 174  keyword?");
t11=C_retrieve(lf[47]);
((C_proc3)C_retrieve_proc(t11))(3,t11,t10,((C_word*)((C_word*)t0)[9])[1]);}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_493,a[2]=((C_word*)t0)[11],a[3]=((C_word*)t0)[10],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[6],tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_nequalp(((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]))){
t4=(C_word)C_i_length(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 164  ferror");
f_387(t3,lf[48],(C_word)C_a_i_list(&a,3,((C_word*)t0)[5],((C_word*)t0)[2],t4));}
else{
t4=t3;
f_493(2,t4,C_SCHEME_UNDEFINED);}}}}

/* k491 in k481 in do88 in k417 in k405 in k402 in k399 in expand-send in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_493(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_493,2,t0,t1);}
t2=(C_word)C_i_list_tail(((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]);
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
t4=(C_word)C_i_set_car(t2,t3);
t5=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[3])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t5);
t7=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[4])[1],C_fix(1));
t8=C_mutate(((C_word *)((C_word*)t0)[4])+1,t7);
t9=((C_word*)t0)[2];
f_477(t9,t8);}

/* k590 in k481 in do88 in k417 in k405 in k402 in k399 in expand-send in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_592(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_592,2,t0,t1);}
if(C_truep(t1)){
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[7])[1]))){
C_trace("ChickenBridge.scm: 178  ferror");
f_387(((C_word*)t0)[6],lf[42],(C_word)C_a_i_list(&a,2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]));}
else{
t2=((C_word*)((C_word*)t0)[3])[1];
if(C_truep(t2)){
t3=((C_word*)t0)[6];
f_537(2,t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_588,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
C_trace("map");
t4=*((C_word*)lf[44]+1);
((C_proc4)(void*)(*((C_word*)t4+1)))(4,t4,t3,*((C_word*)lf[45]+1),((C_word*)t0)[2]);}}}
else{
C_trace("ChickenBridge.scm: 175  ferror");
f_387(((C_word*)t0)[6],lf[46],(C_word)C_a_i_list(&a,2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]));}}

/* k586 in k590 in k481 in do88 in k417 in k405 in k402 in k399 in expand-send in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_588(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_588,2,t0,t1);}
C_trace("ChickenBridge.scm: 181  ferror");
f_387(((C_word*)t0)[4],lf[43],(C_word)C_a_i_list(&a,3,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1));}

/* k535 in k481 in do88 in k417 in k405 in k402 in k399 in expand-send in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_537(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[14],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_537,2,t0,t1);}
t2=(C_word)C_i_member(((C_word*)((C_word*)t0)[8])[1],((C_word*)t0)[7]);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_543,a[2]=((C_word*)t0)[5],a[3]=t2,a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
if(C_truep(t2)){
t4=t3;
f_543(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 188  ferror");
f_387(t3,lf[41],(C_word)C_a_i_list(&a,3,((C_word*)t0)[4],((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]));}}

/* k541 in k535 in k481 in do88 in k417 in k405 in k402 in k399 in expand-send in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_543(C_word c,C_word t0,C_word t1){
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
f_477(t6,t5);}

/* k475 in do88 in k417 in k405 in k402 in k399 in expand-send in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_fcall f_477(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[6])[1];
f_467(t2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k420 in k417 in k405 in k402 in k399 in expand-send in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_422(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_422,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_427,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=lf[40],tmp=(C_word)a,a+=7,tmp));
t5=((C_word*)t3)[1];
f_427(t5,((C_word*)t0)[2],((C_word*)t0)[4]);}

/* do105 in k420 in k417 in k405 in k402 in k399 in expand-send in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_fcall f_427(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_427,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[5],((C_word*)t0)[4]));}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_440,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_member(t4,((C_word*)t0)[2]))){
t5=(C_word)C_i_car(t2);
t6=(C_word)C_i_cadr(t5);
t7=t3;
f_440(t7,(C_word)C_i_set_car(t2,t6));}
else{
t5=t3;
f_440(t5,C_SCHEME_UNDEFINED);}}}

/* k438 in do105 in k420 in k417 in k405 in k402 in k399 in expand-send in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_fcall f_440(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_427(t3,((C_word*)t0)[2],t2);}

/* ferror in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_fcall f_387(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_387,NULL,3,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_395,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_apply(5,0,t4,C_retrieve(lf[37]),t2,t3);}

/* k393 in ferror in k383 in k380 in k212 in k209 in k206 in k203 */
static void C_ccall f_395(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 131  error");
t2=*((C_word*)lf[36]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* runproc in k212 in k209 in k206 in k203 */
static void C_ccall f_362(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[7],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_362,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_366,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_371,a[2]=t2,a[3]=lf[32],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 105  make-process");
t7=*((C_word*)lf[20]+1);
((C_proc5)C_retrieve_proc(t7))(5,t7,t5,t6,t3,t4);}

/* a370 in runproc in k212 in k209 in k206 in k203 */
static void C_ccall f_371(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[4],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_371,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_375,a[2]=((C_word*)t0)[2],a[3]=t1,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 107  insert-midi-note");
t3=*((C_word*)lf[12]+1);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[31],((C_word*)t0)[2],C_fix(100));}

/* k373 in a370 in runproc in k212 in k209 in k206 in k203 */
static void C_ccall f_375(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 108  insert-midi-note");
t2=*((C_word*)lf[12]+1);
((C_proc5)C_retrieve_proc(t2))(5,t2,((C_word*)t0)[3],lf[30],((C_word*)t0)[2],C_fix(0));}

/* k364 in runproc in k212 in k209 in k206 in k203 */
static void C_ccall f_366(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 110  insert-process");
t2=*((C_word*)lf[5]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[2],lf[29],t1);}

/* runran in k212 in k209 in k206 in k203 */
static void C_ccall f_326(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_326,4,t0,t1,t2,t3);}
t4=lf[25];
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_SCHEME_UNDEFINED;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=C_set_block_item(t7,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_332,a[2]=t7,a[3]=t3,a[4]=t5,a[5]=t2,a[6]=lf[26],tmp=(C_word)a,a+=7,tmp));
t9=((C_word*)t7)[1];
f_332(t9,t1,C_fix(0));}

/* do58 in runran in k212 in k209 in k206 in k203 */
static void C_fcall f_332(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word ab[7],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_332,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_greaterp(t2,((C_word*)t0)[5]))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_342,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=t2,a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],tmp=(C_word)a,a+=7,tmp);
C_trace("ChickenBridge.scm: 100  insert-midi-note");
t4=*((C_word*)lf[12]+1);
((C_proc5)C_retrieve_proc(t4))(5,t4,t3,((C_word*)((C_word*)t0)[4])[1],C_fix(60),C_fix(100));}}

/* k340 in do58 in runran in k212 in k209 in k206 in k203 */
static void C_ccall f_342(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_342,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_345,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],tmp=(C_word)a,a+=7,tmp);
t3=(C_word)C_a_i_plus(&a,2,C_fix(200),((C_word*)((C_word*)t0)[6])[1]);
C_trace("ChickenBridge.scm: 101  insert-midi-note");
t4=*((C_word*)lf[12]+1);
((C_proc5)C_retrieve_proc(t4))(5,t4,t2,t3,C_fix(60),C_fix(0));}

/* k343 in k340 in do58 in runran in k212 in k209 in k206 in k203 */
static void C_ccall f_345(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_345,2,t0,t1);}
t2=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[6])[1],((C_word*)t0)[5]);
t3=C_mutate(((C_word *)((C_word*)t0)[6])+1,t2);
t4=(C_word)C_a_i_plus(&a,2,((C_word*)t0)[4],C_fix(1));
t5=((C_word*)((C_word*)t0)[3])[1];
f_332(t5,((C_word*)t0)[2],t4);}

/* make-process in k212 in k209 in k206 in k203 */
static void C_ccall f_307(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
C_save_and_reclaim((void*)tr5,(void*)f_307,5,t0,t1,t2,t3,t4);}
t5=t4;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=C_fix(0);
t8=(*a=C_VECTOR_TYPE|1,a[1]=t7,tmp=(C_word)a,a+=2,tmp);
t9=t1;
((C_proc2)(void*)(*((C_word*)t9+1)))(2,t9,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_309,a[2]=t2,a[3]=t3,a[4]=t6,a[5]=t8,a[6]=lf[22],tmp=(C_word)a,a+=7,tmp));}

/* f_309 in make-process in k212 in k209 in k206 in k203 */
static void C_ccall f_309(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[6],*a=ab;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_309,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_313,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=t1,a[5]=((C_word*)t0)[5],tmp=(C_word)a,a+=6,tmp);
t3=((C_word*)t0)[2];
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k311 */
static void C_ccall f_313(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_313,2,t0,t1);}
t2=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[5])[1],C_fix(1));
t3=C_mutate(((C_word *)((C_word*)t0)[5])+1,t2);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_320,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_greaterp(((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[2]))){
t5=C_mutate(((C_word *)((C_word*)t0)[3])+1,lf[21]);
t6=t4;
f_320(t6,t5);}
else{
t5=t4;
f_320(t5,C_SCHEME_UNDEFINED);}}

/* k318 in k311 */
static void C_fcall f_320(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,((C_word*)((C_word*)t0)[2])[1]);}

/* make-note-off in k212 in k209 in k206 in k203 */
static void C_ccall f_301(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_301,5,t0,t1,t2,t3,t4);}
C_trace("ChickenBridge.scm: 77   insert-midi-note");
t5=*((C_word*)lf[12]+1);
((C_proc6)C_retrieve_proc(t5))(6,t5,t1,t2,t3,lf[18],t4);}

/* make-note-on in k212 in k209 in k206 in k203 */
static void C_ccall f_295(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_295,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 73   insert-midi-note");
t6=*((C_word*)lf[12]+1);
((C_proc6)C_retrieve_proc(t6))(6,t6,t1,t2,t3,t4,t5);}

/* insert-midi-note in k212 in k209 in k206 in k203 */
static void C_ccall f_270(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word t7;
C_word ab[7],*a=ab;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_270,6,t0,t1,t2,t3,t4,t5);}
t6=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_274,a[2]=t1,a[3]=t5,a[4]=t4,a[5]=t3,a[6]=t2,tmp=(C_word)a,a+=7,tmp);
C_trace("##sys#gc");
t7=C_retrieve(lf[7]);
((C_proc3)C_retrieve_proc(t7))(3,t7,t6,C_SCHEME_FALSE);}

/* k272 in insert-midi-note in k212 in k209 in k206 in k203 */
static void C_ccall f_274(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_274,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[6]);
t4=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[5]);
t5=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[4]);
t6=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[3]);
t7=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub32,a[2]=lf[13],tmp=(C_word)a,a+=3,tmp);
((C_proc7)C_retrieve_proc(t7))(7,t7,((C_word*)t0)[2],t2,t3,t4,t5,t6);}

/* insert-closure in k212 in k209 in k206 in k203 */
static void C_ccall f_257(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_257,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_261,a[2]=t3,a[3]=t1,a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("##sys#gc");
t5=C_retrieve(lf[7]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,C_SCHEME_FALSE);}

/* k259 in insert-closure in k212 in k209 in k206 in k203 */
static void C_ccall f_261(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_261,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[4]);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub22,a[2]=lf[10],tmp=(C_word)a,a+=3,tmp);
((C_proc5)C_retrieve_proc(t4))(5,t4,((C_word*)t0)[3],t2,t3,((C_word*)t0)[2]);}

/* insert-process in k212 in k209 in k206 in k203 */
static void C_ccall f_244(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_244,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_248,a[2]=t3,a[3]=t1,a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("##sys#gc");
t5=C_retrieve(lf[7]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,C_SCHEME_FALSE);}

/* k246 in insert-process in k212 in k209 in k206 in k203 */
static void C_ccall f_248(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_248,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[4]);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub14,a[2]=lf[6],tmp=(C_word)a,a+=3,tmp);
((C_proc5)C_retrieve_proc(t4))(5,t4,((C_word*)t0)[3],t2,t3,((C_word*)t0)[2]);}

/* print-error in k212 in k209 in k206 in k203 */
static void C_ccall f_230(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_230,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_235,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[1]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_235(2,t4,C_SCHEME_FALSE);}}

/* k233 in print-error in k212 in k209 in k206 in k203 */
static void C_ccall f_235(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub7(C_SCHEME_UNDEFINED,t1));}

/* print-message in k212 in k209 in k206 in k203 */
static void C_ccall f_216(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_216,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_221,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[1]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_221(2,t4,C_SCHEME_FALSE);}}

/* k219 in print-message in k212 in k209 in k206 in k203 */
static void C_ccall f_221(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub1(C_SCHEME_UNDEFINED,t1));}

#ifdef C_ENABLE_PTABLES
static C_PTABLE_ENTRY ptable[96] = {
{"toplevelChickenBridge.scm",(void*)C_grace_toplevel},
{"f_205ChickenBridge.scm",(void*)f_205},
{"f_208ChickenBridge.scm",(void*)f_208},
{"f_211ChickenBridge.scm",(void*)f_211},
{"f_214ChickenBridge.scm",(void*)f_214},
{"f_382ChickenBridge.scm",(void*)f_382},
{"f_1014ChickenBridge.scm",(void*)f_1014},
{"f_1061ChickenBridge.scm",(void*)f_1061},
{"f_1051ChickenBridge.scm",(void*)f_1051},
{"f_1018ChickenBridge.scm",(void*)f_1018},
{"f_385ChickenBridge.scm",(void*)f_385},
{"f_1008ChickenBridge.scm",(void*)f_1008},
{"f_624ChickenBridge.scm",(void*)f_624},
{"f_682ChickenBridge.scm",(void*)f_682},
{"f_685ChickenBridge.scm",(void*)f_685},
{"f_688ChickenBridge.scm",(void*)f_688},
{"f_691ChickenBridge.scm",(void*)f_691},
{"f_694ChickenBridge.scm",(void*)f_694},
{"f_697ChickenBridge.scm",(void*)f_697},
{"f_700ChickenBridge.scm",(void*)f_700},
{"f_703ChickenBridge.scm",(void*)f_703},
{"f_1002ChickenBridge.scm",(void*)f_1002},
{"f_706ChickenBridge.scm",(void*)f_706},
{"f_1000ChickenBridge.scm",(void*)f_1000},
{"f_708ChickenBridge.scm",(void*)f_708},
{"f_721ChickenBridge.scm",(void*)f_721},
{"f_724ChickenBridge.scm",(void*)f_724},
{"f_837ChickenBridge.scm",(void*)f_837},
{"f_945ChickenBridge.scm",(void*)f_945},
{"f_857ChickenBridge.scm",(void*)f_857},
{"f_866ChickenBridge.scm",(void*)f_866},
{"f_870ChickenBridge.scm",(void*)f_870},
{"f_874ChickenBridge.scm",(void*)f_874},
{"f_882ChickenBridge.scm",(void*)f_882},
{"f_878ChickenBridge.scm",(void*)f_878},
{"f_847ChickenBridge.scm",(void*)f_847},
{"f_727ChickenBridge.scm",(void*)f_727},
{"f_730ChickenBridge.scm",(void*)f_730},
{"f_733ChickenBridge.scm",(void*)f_733},
{"f_736ChickenBridge.scm",(void*)f_736},
{"f_791ChickenBridge.scm",(void*)f_791},
{"f_779ChickenBridge.scm",(void*)f_779},
{"f_775ChickenBridge.scm",(void*)f_775},
{"f_675ChickenBridge.scm",(void*)f_675},
{"f_669ChickenBridge.scm",(void*)f_669},
{"f_663ChickenBridge.scm",(void*)f_663},
{"f_657ChickenBridge.scm",(void*)f_657},
{"f_651ChickenBridge.scm",(void*)f_651},
{"f_645ChickenBridge.scm",(void*)f_645},
{"f_639ChickenBridge.scm",(void*)f_639},
{"f_626ChickenBridge.scm",(void*)f_626},
{"f_630ChickenBridge.scm",(void*)f_630},
{"f_397ChickenBridge.scm",(void*)f_397},
{"f_401ChickenBridge.scm",(void*)f_401},
{"f_614ChickenBridge.scm",(void*)f_614},
{"f_404ChickenBridge.scm",(void*)f_404},
{"f_407ChickenBridge.scm",(void*)f_407},
{"f_419ChickenBridge.scm",(void*)f_419},
{"f_467ChickenBridge.scm",(void*)f_467},
{"f_483ChickenBridge.scm",(void*)f_483},
{"f_493ChickenBridge.scm",(void*)f_493},
{"f_592ChickenBridge.scm",(void*)f_592},
{"f_588ChickenBridge.scm",(void*)f_588},
{"f_537ChickenBridge.scm",(void*)f_537},
{"f_543ChickenBridge.scm",(void*)f_543},
{"f_477ChickenBridge.scm",(void*)f_477},
{"f_422ChickenBridge.scm",(void*)f_422},
{"f_427ChickenBridge.scm",(void*)f_427},
{"f_440ChickenBridge.scm",(void*)f_440},
{"f_387ChickenBridge.scm",(void*)f_387},
{"f_395ChickenBridge.scm",(void*)f_395},
{"f_362ChickenBridge.scm",(void*)f_362},
{"f_371ChickenBridge.scm",(void*)f_371},
{"f_375ChickenBridge.scm",(void*)f_375},
{"f_366ChickenBridge.scm",(void*)f_366},
{"f_326ChickenBridge.scm",(void*)f_326},
{"f_332ChickenBridge.scm",(void*)f_332},
{"f_342ChickenBridge.scm",(void*)f_342},
{"f_345ChickenBridge.scm",(void*)f_345},
{"f_307ChickenBridge.scm",(void*)f_307},
{"f_309ChickenBridge.scm",(void*)f_309},
{"f_313ChickenBridge.scm",(void*)f_313},
{"f_320ChickenBridge.scm",(void*)f_320},
{"f_301ChickenBridge.scm",(void*)f_301},
{"f_295ChickenBridge.scm",(void*)f_295},
{"f_270ChickenBridge.scm",(void*)f_270},
{"f_274ChickenBridge.scm",(void*)f_274},
{"f_257ChickenBridge.scm",(void*)f_257},
{"f_261ChickenBridge.scm",(void*)f_261},
{"f_244ChickenBridge.scm",(void*)f_244},
{"f_248ChickenBridge.scm",(void*)f_248},
{"f_230ChickenBridge.scm",(void*)f_230},
{"f_235ChickenBridge.scm",(void*)f_235},
{"f_216ChickenBridge.scm",(void*)f_216},
{"f_221ChickenBridge.scm",(void*)f_221},
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
