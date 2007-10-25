/* Generated from ChickenBridge.scm by the CHICKEN compiler
   http://www.call-with-current-continuation.org
   2007-10-25 06:35
   Version 2.726 - macosx-unix-gnu-ppc - [ manyargs dload ptables applyhook ]
(c)2000-2007 Felix L. Winkelmann | compiled 2007-10-22 on galen.local (Darwin)
   command line: ChickenBridge.scm -output-file ChickenBridge.cpp -quiet
   unit: grace
*/

#include "chicken.h"


#include "Grace.h"
#include "Scheme.h"
#include "Nodes.h"

void print_mess(char * st)
{
//  ((GraceApp *)GraceApp::getInstance())->getConsole()->printMessage( String(st));
    printf("%s", st);
}

void print_error(char * st)
{
 //((GraceApp *)GraceApp::getInstance())->getConsole()->printError( String(st));
    printf("%s", st);
}

void insert_midi_on(double time, float k, float v, float c) {
 float vals[3];
 vals[0] = k;
 vals[1] = v;
 vals[2] = c;
 ((GraceApp *)GraceApp::getInstance())->queue->addNode(0, time, (float *)vals, 3, 0);
}

void insert_midi_note(double time, double dur, float k, float v, float c) {
 float on[3];
 float off[3];
 on[0] = k;
 on[1] = v;
 on[2] = c;
 ((GraceApp *)GraceApp::getInstance())->queue->addNode(0, time, (float *)on, 3, 0);
 off[0] = k;
 off[1] = 0.0;
 off[2] = c;
 ((GraceApp *)GraceApp::getInstance())->queue->addNode(0, time+dur, (float *)off, 3, 0);
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

static C_TLS C_word lf[129];


/* from k282 */
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

/* from k253 */
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

/* from k240 */
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

/* from k220 in print-error in k199 in k196 in k193 in k190 */
static C_word C_fcall stub7(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub7(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_error(t0);
return C_r;}

/* from k206 in print-message in k199 in k196 in k193 in k190 */
static C_word C_fcall stub1(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub1(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_mess(t0);
return C_r;}

C_noret_decl(C_grace_toplevel)
C_externexport void C_ccall C_grace_toplevel(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_192)
static void C_ccall f_192(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_195)
static void C_ccall f_195(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_198)
static void C_ccall f_198(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_201)
static void C_ccall f_201(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_300)
static void C_ccall f_300(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1063)
static void C_ccall f_1063(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_1110)
static void C_ccall f_1110(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1100)
static void C_ccall f_1100(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1067)
static void C_ccall f_1067(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_303)
static void C_ccall f_303(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1057)
static void C_ccall f_1057(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_1057)
static void C_ccall f_1057r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_542)
static void C_ccall f_542(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_593)
static void C_ccall f_593(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_596)
static void C_ccall f_596(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_599)
static void C_ccall f_599(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_602)
static void C_ccall f_602(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_605)
static void C_ccall f_605(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_608)
static void C_ccall f_608(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_611)
static void C_ccall f_611(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_614)
static void C_ccall f_614(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1051)
static void C_ccall f_1051(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_1051)
static void C_ccall f_1051r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_617)
static void C_ccall f_617(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_1049)
static void C_ccall f_1049(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_619)
static void C_ccall f_619(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_632)
static void C_ccall f_632(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_635)
static void C_ccall f_635(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_886)
static void C_fcall f_886(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_994)
static void C_ccall f_994(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_906)
static void C_fcall f_906(C_word t0,C_word t1) C_noret;
C_noret_decl(f_915)
static void C_fcall f_915(C_word t0,C_word t1) C_noret;
C_noret_decl(f_919)
static void C_ccall f_919(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_923)
static void C_ccall f_923(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_931)
static void C_fcall f_931(C_word t0,C_word t1) C_noret;
C_noret_decl(f_927)
static void C_ccall f_927(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_896)
static void C_ccall f_896(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_638)
static void C_ccall f_638(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_641)
static void C_ccall f_641(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_644)
static void C_ccall f_644(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_647)
static void C_ccall f_647(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_880)
static void C_ccall f_880(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_779)
static void C_fcall f_779(C_word t0,C_word t1) C_noret;
C_noret_decl(f_786)
static void C_ccall f_786(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_788)
static void C_fcall f_788(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_860)
static void C_ccall f_860(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_812)
static void C_fcall f_812(C_word t0,C_word t1) C_noret;
C_noret_decl(f_815)
static void C_ccall f_815(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_836)
static void C_ccall f_836(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_802)
static void C_ccall f_802(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_650)
static void C_ccall f_650(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_768)
static void C_ccall f_768(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_756)
static void C_ccall f_756(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_752)
static void C_ccall f_752(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_657)
static void C_fcall f_657(C_word t0,C_word t1) C_noret;
C_noret_decl(f_586)
static void C_ccall f_586(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_580)
static void C_ccall f_580(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_574)
static void C_ccall f_574(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_568)
static void C_ccall f_568(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_562)
static void C_ccall f_562(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_556)
static void C_ccall f_556(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_550)
static void C_ccall f_550(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_544)
static void C_ccall f_544(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_315)
static void C_ccall f_315(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_319)
static void C_ccall f_319(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_532)
static void C_ccall f_532(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_322)
static void C_ccall f_322(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_325)
static void C_ccall f_325(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_337)
static void C_ccall f_337(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_385)
static void C_fcall f_385(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_401)
static void C_ccall f_401(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_411)
static void C_ccall f_411(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_510)
static void C_ccall f_510(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_506)
static void C_ccall f_506(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_455)
static void C_ccall f_455(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_461)
static void C_ccall f_461(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_395)
static void C_fcall f_395(C_word t0,C_word t1) C_noret;
C_noret_decl(f_340)
static void C_ccall f_340(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_345)
static void C_fcall f_345(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_358)
static void C_fcall f_358(C_word t0,C_word t1) C_noret;
C_noret_decl(f_305)
static void C_fcall f_305(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_313)
static void C_ccall f_313(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_292)
static void C_ccall f_292(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_286)
static void C_ccall f_286(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_257)
static void C_ccall f_257(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_261)
static void C_ccall f_261(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_244)
static void C_ccall f_244(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_248)
static void C_ccall f_248(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_231)
static void C_ccall f_231(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_235)
static void C_ccall f_235(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_217)
static void C_ccall f_217(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_222)
static void C_ccall f_222(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_203)
static void C_ccall f_203(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_208)
static void C_ccall f_208(C_word c,C_word t0,C_word t1) C_noret;

C_noret_decl(trf_886)
static void C_fcall trf_886(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_886(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_886(t0,t1,t2);}

C_noret_decl(trf_906)
static void C_fcall trf_906(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_906(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_906(t0,t1);}

C_noret_decl(trf_915)
static void C_fcall trf_915(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_915(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_915(t0,t1);}

C_noret_decl(trf_931)
static void C_fcall trf_931(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_931(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_931(t0,t1);}

C_noret_decl(trf_779)
static void C_fcall trf_779(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_779(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_779(t0,t1);}

C_noret_decl(trf_788)
static void C_fcall trf_788(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_788(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_788(t0,t1,t2);}

C_noret_decl(trf_812)
static void C_fcall trf_812(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_812(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_812(t0,t1);}

C_noret_decl(trf_657)
static void C_fcall trf_657(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_657(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_657(t0,t1);}

C_noret_decl(trf_385)
static void C_fcall trf_385(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_385(void *dummy){
C_word t4=C_pick(0);
C_word t3=C_pick(1);
C_word t2=C_pick(2);
C_word t1=C_pick(3);
C_word t0=C_pick(4);
C_adjust_stack(-5);
f_385(t0,t1,t2,t3,t4);}

C_noret_decl(trf_395)
static void C_fcall trf_395(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_395(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_395(t0,t1);}

C_noret_decl(trf_345)
static void C_fcall trf_345(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_345(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_345(t0,t1,t2);}

C_noret_decl(trf_358)
static void C_fcall trf_358(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_358(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_358(t0,t1);}

C_noret_decl(trf_305)
static void C_fcall trf_305(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_305(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_305(t0,t1,t2);}

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
if(!C_demand_2(1120)){
C_save(t1);
C_rereclaim2(1120*sizeof(C_word), 1);
t1=C_restore;}
a=C_alloc(3);
C_initialize_lf(lf,129);
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
lf[23]=C_h_intern(&lf[23],5,"error");
lf[24]=C_h_intern(&lf[24],7,"sprintf");
lf[25]=C_static_lambda_info(C_heaptop,21,"(ferror str55 args56)");
lf[26]=C_h_intern(&lf[26],11,"expand-send");
lf[27]=C_static_lambda_info(C_heaptop,13,"(do84 tail86)");
lf[28]=C_static_string(C_heaptop,37,"~S found duplicate keyword \047~S\047 in ~S");
lf[29]=C_static_string(C_heaptop,33,"~S missing value for keyword \047~S\047");
lf[30]=C_static_string(C_heaptop,53,"~S found invalid keyword \047~S\047~%Available keywords: ~S");
lf[31]=C_h_intern(&lf[31],7,"\003sysmap");
lf[32]=C_h_intern(&lf[32],3,"car");
lf[33]=C_static_string(C_heaptop,32,"~S expected keyword but got \047~S\047");
lf[34]=C_h_intern(&lf[34],8,"keyword\077");
lf[35]=C_static_string(C_heaptop,35,"~S expected ~A arguments but got ~A");
lf[36]=C_static_lambda_info(C_heaptop,24,"(do67 key69 arg70 pos71)");
lf[37]=C_h_intern(&lf[37],6,"append");
lf[38]=C_static_string(C_heaptop,24,"~S is an invalid message");
lf[39]=C_static_lambda_info(C_heaptop,6,"(a531)");
lf[40]=C_h_intern(&lf[40],14,"hash-table-ref");
lf[41]=C_h_intern(&lf[41],14,"symbol->string");
lf[42]=C_static_lambda_info(C_heaptop,27,"(expand-send mesg57 data58)");
lf[43]=C_h_intern(&lf[43],7,"mp:note");
lf[44]=C_static_lambda_info(C_heaptop,41,"(mp:note time93 dur94 key95 amp96 chan97)");
lf[45]=C_h_intern(&lf[45],5,"mp:on");
lf[46]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[47]=C_static_lambda_info(C_heaptop,35,"(mp:on time98 key99 vel100 chan101)");
lf[48]=C_h_intern(&lf[48],6,"mp:off");
lf[49]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[50]=C_static_lambda_info(C_heaptop,38,"(mp:off time102 key103 vel104 chan105)");
lf[51]=C_h_intern(&lf[51],7,"mp:prog");
lf[52]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[53]=C_static_lambda_info(C_heaptop,33,"(mp:prog time106 prog107 chan108)");
lf[54]=C_h_intern(&lf[54],7,"mp:ctrl");
lf[55]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[56]=C_static_lambda_info(C_heaptop,40,"(mp:ctrl time109 ctrl110 val111 chan112)");
lf[57]=C_h_intern(&lf[57],9,"mp:alloff");
lf[58]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[59]=C_static_lambda_info(C_heaptop,11,"(mp:alloff)");
lf[60]=C_h_intern(&lf[60],8,"mp:micro");
lf[61]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[62]=C_static_lambda_info(C_heaptop,18,"(mp:micro divs113)");
lf[63]=C_h_intern(&lf[63],9,"mp:inhook");
lf[64]=C_static_string(C_heaptop,33,"message function not implemented.");
lf[65]=C_static_lambda_info(C_heaptop,19,"(mp:inhook func114)");
lf[66]=C_h_intern(&lf[66],9,"expand-go");
lf[67]=C_h_intern(&lf[67],4,"else");
lf[68]=C_h_intern(&lf[68],4,"cond");
lf[69]=C_h_intern(&lf[69],6,"lambda");
lf[70]=C_h_intern(&lf[70],7,"elapsed");
lf[71]=C_h_intern(&lf[71],1,"x");
lf[72]=C_h_intern(&lf[72],4,"set!");
lf[73]=C_h_intern(&lf[73],4,"wait");
lf[74]=C_h_intern(&lf[74],4,"let*");
lf[75]=C_h_intern(&lf[75],3,"exn");
lf[76]=C_h_intern(&lf[76],5,"quote");
lf[77]=C_h_intern(&lf[77],7,"message");
lf[78]=C_h_intern(&lf[78],27,"condition-property-accessor");
lf[79]=C_h_intern(&lf[79],6,"printf");
lf[80]=C_static_string(C_heaptop,47,">>> Aborting process at time ~S:~%    Error: ~S");
lf[81]=C_h_intern(&lf[81],14,"condition-case");
lf[82]=C_h_intern(&lf[82],10,"\003sysappend");
lf[83]=C_h_intern(&lf[83],6,"safety");
lf[84]=C_h_intern(&lf[84],4,"cdar");
lf[85]=C_static_string(C_heaptop,19,"unknown declaration");
lf[86]=C_h_intern(&lf[86],4,"caar");
lf[87]=C_static_string(C_heaptop,31,"declaration not list (decl val)");
lf[88]=C_static_lambda_info(C_heaptop,15,"(do139 decl141)");
lf[89]=C_h_intern(&lf[89],7,"declare");
lf[90]=C_h_intern(&lf[90],6,"gensym");
lf[91]=C_h_intern(&lf[91],5,"\000null");
lf[92]=C_static_string(C_heaptop,41,"binding clause not list (var init [step])");
lf[93]=C_static_lambda_info(C_heaptop,15,"(do124 tail126)");
lf[94]=C_static_string(C_heaptop,36,"go stopping clause missing test form");
lf[95]=C_static_string(C_heaptop,29,"go stopping clause not a list");
lf[96]=C_static_string(C_heaptop,22,"go bindings not a list");
lf[97]=C_static_lambda_info(C_heaptop,44,"(expand-go bindings118 terminate119 body120)");
lf[98]=C_h_intern(&lf[98],14,"return-to-host");
lf[99]=C_static_lambda_info(C_heaptop,42,"(a1050 bindings115 terminate116 . body117)");
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
lf[119]=C_static_lambda_info(C_heaptop,23,"(a1056 mess91 . data92)");
lf[120]=C_h_intern(&lf[120],4,"send");
lf[121]=C_h_intern(&lf[121],10,"*messages*");
lf[122]=C_h_intern(&lf[122],14,"string->symbol");
lf[123]=C_static_string(C_heaptop,51,"message function not string, symbol or list of both");
lf[124]=C_static_lambda_info(C_heaptop,21,"(a1062 func49 info50)");
lf[125]=C_h_intern(&lf[125],19,"define-send-message");
lf[126]=C_h_intern(&lf[126],15,"make-hash-table");
lf[127]=C_h_intern(&lf[127],6,"equal\077");
lf[128]=C_static_lambda_info(C_heaptop,10,"(toplevel)");
C_register_lf2(lf,129,create_ptable());
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_192,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_library_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k190 */
static void C_ccall f_192(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_192,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_195,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_eval_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k193 in k190 */
static void C_ccall f_195(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_195,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_198,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k196 in k193 in k190 */
static void C_ccall f_198(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_198,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_201,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k199 in k196 in k193 in k190 */
static void C_ccall f_201(C_word c,C_word t0,C_word t1){
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
C_word ab[24],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_201,2,t0,t1);}
t2=C_mutate((C_word*)lf[0]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_203,a[2]=lf[2],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[3]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_217,a[2]=lf[4],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate((C_word*)lf[5]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_231,a[2]=lf[8],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate((C_word*)lf[9]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_244,a[2]=lf[11],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[12]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_257,a[2]=lf[14],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate((C_word*)lf[15]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_286,a[2]=lf[17],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate((C_word*)lf[18]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_292,a[2]=lf[20],tmp=(C_word)a,a+=3,tmp));
t9=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_300,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 117  make-hash-table");
t10=C_retrieve(lf[126]);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,*((C_word*)lf[127]+1));}

/* k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_300(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_300,2,t0,t1);}
t2=C_mutate(&lf[21],t1);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_303,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1063,a[2]=lf[124],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 119  ##sys#register-macro");
t5=C_retrieve(lf[100]);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,lf[125],t4);}

/* a1062 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_1063(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_1063,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_1067,a[2]=t6,a[3]=t1,a[4]=t3,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t4)[1]))){
t8=(C_word)C_i_car(((C_word*)t4)[1]);
t9=C_set_block_item(t6,0,t8);
t10=(C_word)C_i_cadr(((C_word*)t4)[1]);
t11=C_set_block_item(t4,0,t10);
t12=t7;
f_1067(2,t12,t11);}
else{
if(C_truep((C_word)C_i_stringp(((C_word*)t4)[1]))){
t8=C_set_block_item(t6,0,((C_word*)t4)[1]);
t9=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1100,a[2]=t7,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 126  string->symbol");
t10=*((C_word*)lf[122]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)t4)[1]);}
else{
if(C_truep((C_word)C_i_symbolp(((C_word*)t4)[1]))){
t8=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_1110,a[2]=t7,a[3]=t6,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 128  symbol->string");
t9=*((C_word*)lf[41]+1);
((C_proc3)C_retrieve_proc(t9))(3,t9,t8,((C_word*)t4)[1]);}
else{
C_trace("ChickenBridge.scm: 130  error");
t8=*((C_word*)lf[23]+1);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,lf[123]);}}}}

/* k1108 in a1062 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_1110(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_1067(2,t3,t2);}

/* k1098 in a1062 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_1100(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_1067(2,t3,t2);}

/* k1065 in a1062 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_1067(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_1067,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[4]);
t3=(C_word)C_a_i_list(&a,2,lf[76],t2);
t4=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_a_i_list(&a,4,lf[102],lf[121],((C_word*)((C_word*)t0)[2])[1],t3));}

/* k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_303(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_303,2,t0,t1);}
t2=C_mutate(&lf[22],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_305,a[2]=lf[25],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[26]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_315,a[2]=lf[42],tmp=(C_word)a,a+=3,tmp));
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_542,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1057,a[2]=lf[119],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 206  ##sys#register-macro");
t6=C_retrieve(lf[100]);
((C_proc4)C_retrieve_proc(t6))(4,t6,t4,lf[120],t5);}

/* a1056 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_1057(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr3r,(void*)f_1057r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_1057r(t0,t1,t2,t3);}}

static void C_ccall f_1057r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_trace("ChickenBridge.scm: 207  expand-send");
t4=C_retrieve(lf[26]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t1,t2,t3);}

/* k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_542(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_542,2,t0,t1);}
t2=C_mutate((C_word*)lf[43]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_544,a[2]=lf[44],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[45]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_550,a[2]=lf[47],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate((C_word*)lf[48]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_556,a[2]=lf[50],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate((C_word*)lf[51]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_562,a[2]=lf[53],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[54]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_568,a[2]=lf[56],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate((C_word*)lf[57]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_574,a[2]=lf[59],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate((C_word*)lf[60]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_580,a[2]=lf[62],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate((C_word*)lf[63]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_586,a[2]=lf[65],tmp=(C_word)a,a+=3,tmp));
t10=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_593,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 234  hash-table-set!");
t11=C_retrieve(lf[102]);
((C_proc5)C_retrieve_proc(t11))(5,t11,t10,lf[21],lf[117],lf[118]);}

/* k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_593(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_593,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_596,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 235  hash-table-set!");
t3=C_retrieve(lf[102]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[21],lf[115],lf[116]);}

/* k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_596(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_596,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_599,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 236  hash-table-set!");
t3=C_retrieve(lf[102]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[21],lf[113],lf[114]);}

/* k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_599(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_599,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_602,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 237  hash-table-set!");
t3=C_retrieve(lf[102]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[21],lf[111],lf[112]);}

/* k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_602(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_602,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_605,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 238  hash-table-set!");
t3=C_retrieve(lf[102]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[21],lf[109],lf[110]);}

/* k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_605(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_605,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_608,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 239  hash-table-set!");
t3=C_retrieve(lf[102]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[21],lf[107],lf[108]);}

/* k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_608(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_608,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_611,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 240  hash-table-set!");
t3=C_retrieve(lf[102]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[21],lf[105],lf[106]);}

/* k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_611(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_611,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_614,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 241  hash-table-set!");
t3=C_retrieve(lf[102]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[21],lf[103],lf[104]);}

/* k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_614(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_614,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_617,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1051,a[2]=lf[99],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 263  ##sys#register-macro");
t4=C_retrieve(lf[100]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,lf[101],t3);}

/* a1050 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_1051(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr4r,(void*)f_1051r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest(a,C_rest_count(0));
f_1051r(t0,t1,t2,t3,t4);}}

static void C_ccall f_1051r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_trace("ChickenBridge.scm: 264  expand-go");
t5=C_retrieve(lf[66]);
((C_proc5)C_retrieve_proc(t5))(5,t5,t1,t2,t3,t4);}

/* k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_617(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_617,2,t0,t1);}
t2=C_mutate((C_word*)lf[66]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_619,a[2]=lf[97],tmp=(C_word)a,a+=3,tmp));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_1049,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 358  return-to-host");
t4=C_retrieve(lf[98]);
((C_proc2)C_retrieve_proc(t4))(2,t4,t3);}

/* k1047 in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_1049(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_UNDEFINED);}

/* expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_619(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
C_save_and_reclaim((void*)tr5,(void*)f_619,5,t0,t1,t2,t3,t4);}
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=C_SCHEME_END_OF_LIST;
t7=(*a=C_VECTOR_TYPE|1,a[1]=t6,tmp=(C_word)a,a+=2,tmp);
t8=C_SCHEME_END_OF_LIST;
t9=(*a=C_VECTOR_TYPE|1,a[1]=t8,tmp=(C_word)a,a+=2,tmp);
t10=C_SCHEME_END_OF_LIST;
t11=(*a=C_VECTOR_TYPE|1,a[1]=t10,tmp=(C_word)a,a+=2,tmp);
t12=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_632,a[2]=t2,a[3]=t11,a[4]=t5,a[5]=t9,a[6]=t1,a[7]=t7,a[8]=t3,tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(t2))){
t13=t12;
f_632(2,t13,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 272  error");
t13=*((C_word*)lf[23]+1);
((C_proc4)C_retrieve_proc(t13))(4,t13,t12,lf[96],t2);}}

/* k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_632(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_632,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_635,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(((C_word*)t0)[8]))){
if(C_truep((C_word)C_i_nullp(((C_word*)t0)[8]))){
C_trace("ChickenBridge.scm: 276  error");
t3=*((C_word*)lf[23]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,lf[94]);}
else{
t3=t2;
f_635(2,t3,C_SCHEME_UNDEFINED);}}
else{
C_trace("ChickenBridge.scm: 274  error");
t3=*((C_word*)lf[23]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t2,lf[95],((C_word*)t0)[8]);}}

/* k633 in k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_635(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_635,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_638,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],tmp=(C_word)a,a+=8,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_886,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[7],a[5]=t4,a[6]=lf[93],tmp=(C_word)a,a+=7,tmp));
t6=((C_word*)t4)[1];
f_886(t6,t2,((C_word*)t0)[2]);}

/* do124 in k633 in k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_fcall f_886(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_886,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_896,a[2]=t1,a[3]=((C_word*)t0)[5],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_906,a[2]=t3,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=t2,tmp=(C_word)a,a+=7,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_994,a[2]=t4,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t7=(C_word)C_i_car(t2);
t8=(C_word)C_i_length(t7);
C_trace("ChickenBridge.scm: 280  <");
C_lessp(5,0,t6,C_fix(0),t8,C_fix(4));}
else{
t6=t4;
f_906(t6,C_SCHEME_FALSE);}}}

/* k992 in do124 in k633 in k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_994(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=(C_word)C_i_car(t2);
t4=((C_word*)t0)[2];
f_906(t4,(C_word)C_i_symbolp(t3));}
else{
t2=((C_word*)t0)[2];
f_906(t2,C_SCHEME_FALSE);}}

/* k904 in do124 in k633 in k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_fcall f_906(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_906,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[6]);
t3=(C_word)C_i_car(t2);
t4=(C_word)C_i_car(((C_word*)t0)[6]);
t5=(C_word)C_i_cadr(t4);
t6=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_915,a[2]=t5,a[3]=t3,a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[5],tmp=(C_word)a,a+=8,tmp);
t7=(C_word)C_i_car(((C_word*)t0)[6]);
t8=(C_word)C_i_cddr(t7);
if(C_truep((C_word)C_i_nullp(t8))){
t9=t6;
f_915(t9,lf[91]);}
else{
t9=(C_word)C_i_car(((C_word*)t0)[6]);
t10=t6;
f_915(t10,(C_word)C_i_caddr(t9));}}
else{
t2=(C_word)C_i_car(((C_word*)t0)[6]);
C_trace("ChickenBridge.scm: 293  error");
t3=*((C_word*)lf[23]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[2],lf[92],t2);}}

/* k913 in k904 in do124 in k633 in k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_fcall f_915(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_915,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_919,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t3=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 288  append");
t4=*((C_word*)lf[37]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,((C_word*)((C_word*)t0)[7])[1],t3);}

/* k917 in k913 in k904 in do124 in k633 in k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_919(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_919,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_923,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
t4=(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 289  append");
t5=*((C_word*)lf[37]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,((C_word*)((C_word*)t0)[7])[1],t4);}

/* k921 in k917 in k913 in k904 in do124 in k633 in k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_923(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_923,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_927,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_931,a[2]=((C_word*)t0)[5],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_eqp(((C_word*)t0)[3],lf[91]);
if(C_truep(t5)){
t6=t4;
f_931(t6,C_SCHEME_END_OF_LIST);}
else{
t6=(C_word)C_a_i_list(&a,3,lf[72],((C_word*)t0)[2],((C_word*)t0)[3]);
t7=t4;
f_931(t7,(C_word)C_a_i_list(&a,1,t6));}}

/* k929 in k921 in k917 in k913 in k904 in do124 in k633 in k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_fcall f_931(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 290  append");
t2=*((C_word*)lf[37]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k925 in k921 in k917 in k913 in k904 in do124 in k633 in k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_927(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_896(2,t3,t2);}

/* k894 in do124 in k633 in k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_896(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_886(t3,((C_word*)t0)[2],t2);}

/* k636 in k633 in k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_638(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_638,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_641,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 295  gensym");
t3=C_retrieve(lf[90]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k639 in k636 in k633 in k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_641(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_641,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_644,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 296  gensym");
t3=C_retrieve(lf[90]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k642 in k639 in k636 in k633 in k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_644(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_644,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_647,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=t1,a[8]=((C_word*)t0)[7],a[9]=((C_word*)t0)[8],tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 297  gensym");
t3=C_retrieve(lf[90]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k645 in k642 in k639 in k636 in k633 in k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_647(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_647,2,t0,t1);}
t2=C_SCHEME_TRUE;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_SCHEME_END_OF_LIST;
t5=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_650,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=t3,a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[5],a[8]=((C_word*)t0)[6],a[9]=((C_word*)t0)[7],a[10]=((C_word*)t0)[8],a[11]=t5,a[12]=((C_word*)t0)[9],tmp=(C_word)a,a+=13,tmp);
t7=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_779,a[2]=t6,a[3]=t3,a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)((C_word*)t0)[3])[1]))){
t8=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
if(C_truep((C_word)C_i_pairp(t8))){
t9=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_880,a[2]=t7,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 303  caar");
t10=*((C_word*)lf[86]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)((C_word*)t0)[3])[1]);}
else{
t9=t7;
f_779(t9,C_SCHEME_FALSE);}}
else{
t8=t7;
f_779(t8,C_SCHEME_FALSE);}}

/* k878 in k645 in k642 in k639 in k636 in k633 in k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_880(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_779(t2,(C_word)C_eqp(t1,lf[89]));}

/* k777 in k645 in k642 in k639 in k636 in k633 in k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_fcall f_779(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_779,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_786,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 304  cdar");
t3=*((C_word*)lf[84]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)((C_word*)t0)[4])[1]);}
else{
t2=((C_word*)t0)[2];
f_650(2,t2,C_SCHEME_UNDEFINED);}}

/* k784 in k777 in k645 in k642 in k639 in k636 in k633 in k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_786(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_786,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_788,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=lf[88],tmp=(C_word)a,a+=6,tmp));
t5=((C_word*)t3)[1];
f_788(t5,((C_word*)t0)[2],t1);}

/* do139 in k784 in k777 in k645 in k642 in k639 in k636 in k633 in k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_fcall f_788(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_788,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[4])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[4])+1,t3);
t5=t1;
((C_proc2)(void*)(*((C_word*)t5+1)))(2,t5,t4);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_802,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_812,a[2]=t2,a[3]=((C_word*)t0)[2],a[4]=t3,tmp=(C_word)a,a+=5,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_860,a[2]=t4,tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 308  cdar");
t7=*((C_word*)lf[84]+1);
((C_proc3)C_retrieve_proc(t7))(3,t7,t6,t2);}
else{
t6=t4;
f_812(t6,C_SCHEME_FALSE);}}}

/* k858 in do139 in k784 in k777 in k645 in k642 in k639 in k636 in k633 in k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_860(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
f_812(t2,(C_word)C_i_pairp(t1));}

/* k810 in do139 in k784 in k777 in k645 in k642 in k639 in k636 in k633 in k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_fcall f_812(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_812,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_815,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],tmp=(C_word)a,a+=5,tmp);
C_trace("ChickenBridge.scm: 309  caar");
t3=*((C_word*)lf[86]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,((C_word*)t0)[2]);}
else{
t2=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 315  error");
t3=*((C_word*)lf[23]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[4],lf[87],t2);}}

/* k813 in k810 in do139 in k784 in k777 in k645 in k642 in k639 in k636 in k633 in k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_815(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_815,2,t0,t1);}
t2=(C_word)C_eqp(t1,lf[83]);
if(C_truep(t2)){
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_836,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 311  cdar");
t4=*((C_word*)lf[84]+1);
((C_proc3)C_retrieve_proc(t4))(3,t4,t3,((C_word*)t0)[2]);}
else{
t3=(C_word)C_i_car(((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 314  error");
t4=*((C_word*)lf[23]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,((C_word*)t0)[4],lf[85],t3);}}

/* k834 in k813 in k810 in do139 in k784 in k777 in k645 in k642 in k639 in k636 in k633 in k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_836(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(C_truep((C_word)C_i_car(t1))){
t2=((C_word*)t0)[3];
f_802(2,t2,C_SCHEME_UNDEFINED);}
else{
t2=C_set_block_item(((C_word*)t0)[2],0,C_SCHEME_FALSE);
t3=((C_word*)t0)[3];
f_802(2,t3,t2);}}

/* k800 in do139 in k784 in k777 in k645 in k642 in k639 in k636 in k633 in k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_802(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_788(t3,((C_word*)t0)[2],t2);}

/* k648 in k645 in k642 in k639 in k636 in k633 in k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_650(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[16],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_650,2,t0,t1);}
t2=(C_word)C_i_car(((C_word*)t0)[12]);
t3=(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_768,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],a[9]=((C_word*)t0)[9],a[10]=((C_word*)t0)[10],a[11]=((C_word*)t0)[11],a[12]=t2,tmp=(C_word)a,a+=13,tmp);
t4=(C_word)C_i_cdr(((C_word*)t0)[12]);
t5=(C_word)C_a_i_list(&a,1,C_fix(-1));
C_trace("ChickenBridge.scm: 267  ##sys#append");
t6=*((C_word*)lf[82]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t3,t4,t5);}

/* k766 in k648 in k645 in k642 in k639 in k636 in k633 in k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_768(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_768,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[12],t1);
t3=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_752,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[7],a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[9],a[8]=((C_word*)t0)[10],a[9]=((C_word*)t0)[11],a[10]=t2,tmp=(C_word)a,a+=11,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_756,a[2]=((C_word*)t0)[3],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_a_i_list(&a,1,((C_word*)t0)[9]);
C_trace("ChickenBridge.scm: 267  ##sys#append");
t6=*((C_word*)lf[82]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t4,((C_word*)((C_word*)t0)[2])[1],t5);}

/* k754 in k766 in k648 in k645 in k642 in k639 in k636 in k633 in k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_756(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 267  ##sys#append");
t2=*((C_word*)lf[82]+1);
((C_proc4)(void*)(*((C_word*)t2+1)))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k750 in k766 in k648 in k645 in k642 in k639 in k636 in k633 in k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_752(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_752,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,lf[67],t1);
t3=(C_word)C_a_i_list(&a,3,lf[68],((C_word*)t0)[10],t2);
t4=C_mutate(((C_word *)((C_word*)t0)[9])+1,t3);
t5=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_657,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],a[5]=((C_word*)t0)[9],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],tmp=(C_word)a,a+=8,tmp);
if(C_truep(((C_word*)((C_word*)t0)[3])[1])){
t6=(C_word)C_a_i_list(&a,1,lf[75]);
t7=(C_word)C_a_i_list(&a,2,lf[76],lf[75]);
t8=(C_word)C_a_i_list(&a,2,lf[76],lf[77]);
t9=(C_word)C_a_i_list(&a,3,lf[78],t7,t8);
t10=(C_word)C_a_i_list(&a,2,t9,((C_word*)t0)[2]);
t11=(C_word)C_a_i_list(&a,4,lf[79],lf[80],((C_word*)t0)[8],t10);
t12=(C_word)C_a_i_list(&a,4,((C_word*)t0)[2],t6,t11,C_fix(-2));
t13=(C_word)C_a_i_list(&a,3,lf[81],((C_word*)((C_word*)t0)[9])[1],t12);
t14=C_mutate(((C_word *)((C_word*)t0)[9])+1,t13);
t15=t5;
f_657(t15,t14);}
else{
t6=t5;
f_657(t6,C_SCHEME_UNDEFINED);}}

/* k655 in k750 in k766 in k648 in k645 in k642 in k639 in k636 in k633 in k630 in expand-go in k615 in k612 in k609 in k606 in k603 in k600 in k597 in k594 in k591 in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_fcall f_657(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_657,NULL,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,((C_word*)t0)[7]);
t3=(C_word)C_a_i_list(&a,2,((C_word*)t0)[6],C_fix(0));
t4=(C_word)C_a_i_list(&a,3,lf[69],C_SCHEME_END_OF_LIST,((C_word*)t0)[7]);
t5=(C_word)C_a_i_list(&a,2,lf[70],t4);
t6=(C_word)C_a_i_list(&a,1,lf[71]);
t7=(C_word)C_a_i_list(&a,3,lf[72],((C_word*)t0)[6],lf[71]);
t8=(C_word)C_a_i_list(&a,3,lf[69],t6,t7);
t9=(C_word)C_a_i_list(&a,2,lf[73],t8);
t10=(C_word)C_a_i_list(&a,3,t3,t5,t9);
t11=(C_word)C_a_i_list(&a,3,lf[74],t10,((C_word*)((C_word*)t0)[5])[1]);
t12=(C_word)C_a_i_list(&a,3,lf[69],t2,t11);
t13=(C_word)C_a_i_list(&a,3,lf[69],((C_word*)((C_word*)t0)[4])[1],t12);
t14=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t14+1)))(2,t14,(C_word)C_a_i_cons(&a,2,t13,((C_word*)((C_word*)t0)[2])[1]));}

/* mp:inhook in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_586(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_586,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 230  error");
t3=*((C_word*)lf[23]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[64]);}

/* mp:micro in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_580(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_580,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 228  error");
t3=*((C_word*)lf[23]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[61]);}

/* mp:alloff in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_574(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_574,2,t0,t1);}
C_trace("ChickenBridge.scm: 226  error");
t2=*((C_word*)lf[23]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,t1,lf[58]);}

/* mp:ctrl in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_568(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_568,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 224  error");
t6=*((C_word*)lf[23]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[55]);}

/* mp:prog in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_562(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_562,5,t0,t1,t2,t3,t4);}
C_trace("ChickenBridge.scm: 222  error");
t5=*((C_word*)lf[23]+1);
((C_proc3)C_retrieve_proc(t5))(3,t5,t1,lf[52]);}

/* mp:off in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_556(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_556,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 220  error");
t6=*((C_word*)lf[23]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[49]);}

/* mp:on in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_550(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_550,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 218  error");
t6=*((C_word*)lf[23]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[46]);}

/* mp:note in k540 in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_544(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
C_word tmp;
C_word t7;
C_word *a;
if(c!=7) C_bad_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr7,(void*)f_544,7,t0,t1,t2,t3,t4,t5,t6);}
C_trace("ChickenBridge.scm: 214  insert-midi-note");
t7=*((C_word*)lf[12]+1);
((C_proc7)C_retrieve_proc(t7))(7,t7,t1,t2,t3,t4,t5,t6);}

/* expand-send in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_315(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word ab[6],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_315,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_319,a[2]=t1,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_symbolp(t2))){
C_trace("ChickenBridge.scm: 137  symbol->string");
t6=*((C_word*)lf[41]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t5,t2);}
else{
t6=t5;
f_319(2,t6,t2);}}

/* k317 in expand-send in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_319(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_319,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_322,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_532,a[2]=lf[39],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 138  hash-table-ref");
t4=*((C_word*)lf[40]+1);
((C_proc5)C_retrieve_proc(t4))(5,t4,t2,lf[21],t1,t3);}

/* a531 in k317 in expand-send in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_532(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_532,2,t0,t1);}
t2=t1;
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}

/* k320 in k317 in expand-send in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_322(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_322,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_325,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=t1;
if(C_truep(t3)){
t4=t2;
f_325(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 139  ferror");
f_305(t2,lf[38],(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]));}}

/* k323 in k320 in k317 in expand-send in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_325(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_325,2,t0,t1);}
t2=((C_word*)((C_word*)t0)[5])[1];
t3=(C_word)C_i_car(((C_word*)t0)[4]);
t4=(C_word)C_i_cdr(((C_word*)t0)[4]);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(C_word)C_i_length(t4);
t8=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_337,a[2]=t7,a[3]=t2,a[4]=((C_word*)t0)[2],a[5]=t6,a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[3],a[8]=t4,a[9]=t3,tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 146  append");
t9=*((C_word*)lf[37]+1);
((C_proc4)C_retrieve_proc(t9))(4,t9,t8,t4,C_SCHEME_END_OF_LIST);}

/* k335 in k323 in k320 in k317 in expand-send in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_337(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[19],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_337,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_340,a[2]=((C_word*)t0)[7],a[3]=((C_word*)t0)[8],a[4]=t1,a[5]=((C_word*)t0)[9],tmp=(C_word)a,a+=6,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_385,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[5],a[8]=t4,a[9]=((C_word*)t0)[6],a[10]=lf[36],tmp=(C_word)a,a+=11,tmp));
t6=((C_word*)t4)[1];
f_385(t6,t2,C_SCHEME_FALSE,C_SCHEME_FALSE,C_fix(0));}

/* do67 in k335 in k323 in k320 in k317 in expand-send in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_fcall f_385(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
C_save_and_reclaim((void*)trf_385,NULL,5,t0,t1,t2,t3,t4);}
t5=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[9])[1]))){
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,C_SCHEME_FALSE);}
else{
t8=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_395,a[2]=t7,a[3]=t6,a[4]=t5,a[5]=t1,a[6]=((C_word*)t0)[8],tmp=(C_word)a,a+=7,tmp);
t9=(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_401,a[2]=((C_word*)t0)[2],a[3]=t7,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=t6,a[8]=((C_word*)t0)[6],a[9]=t5,a[10]=((C_word*)t0)[9],a[11]=t8,a[12]=((C_word*)t0)[7],tmp=(C_word)a,a+=13,tmp);
t10=((C_word*)((C_word*)t0)[7])[1];
if(C_truep(t10)){
t11=t9;
f_401(2,t11,C_SCHEME_FALSE);}
else{
t11=(C_word)C_i_car(((C_word*)((C_word*)t0)[9])[1]);
C_trace("ChickenBridge.scm: 157  keyword?");
t12=C_retrieve(lf[34]);
((C_proc3)C_retrieve_proc(t12))(3,t12,t9,t11);}}}

/* k399 in do67 in k335 in k323 in k320 in k317 in expand-send in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_401(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_401,2,t0,t1);}
if(C_truep(t1)){
t2=C_set_block_item(((C_word*)t0)[12],0,C_SCHEME_TRUE);
t3=((C_word*)t0)[11];
f_395(t3,t2);}
else{
t2=((C_word*)((C_word*)t0)[12])[1];
if(C_truep(t2)){
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[10])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[9])+1,t3);
t5=(C_word)C_i_assoc(((C_word*)((C_word*)t0)[9])[1],((C_word*)t0)[8]);
t6=C_mutate(((C_word *)((C_word*)t0)[7])+1,t5);
t7=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[10])[1]);
t8=C_mutate(((C_word *)((C_word*)t0)[10])+1,t7);
t9=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_455,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[9],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[11],a[6]=((C_word*)t0)[10],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t10=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_510,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[9],a[5]=((C_word*)t0)[5],a[6]=t9,a[7]=((C_word*)t0)[10],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 177  keyword?");
t11=C_retrieve(lf[34]);
((C_proc3)C_retrieve_proc(t11))(3,t11,t10,((C_word*)((C_word*)t0)[9])[1]);}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_411,a[2]=((C_word*)t0)[11],a[3]=((C_word*)t0)[10],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[6],tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_nequalp(((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]))){
t4=(C_word)C_i_length(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 167  ferror");
f_305(t3,lf[35],(C_word)C_a_i_list(&a,3,((C_word*)t0)[5],((C_word*)t0)[2],t4));}
else{
t4=t3;
f_411(2,t4,C_SCHEME_UNDEFINED);}}}}

/* k409 in k399 in do67 in k335 in k323 in k320 in k317 in expand-send in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_411(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_411,2,t0,t1);}
t2=(C_word)C_i_list_tail(((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]);
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
t4=(C_word)C_i_set_car(t2,t3);
t5=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[3])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t5);
t7=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[4])[1],C_fix(1));
t8=C_mutate(((C_word *)((C_word*)t0)[4])+1,t7);
t9=((C_word*)t0)[2];
f_395(t9,t8);}

/* k508 in k399 in do67 in k335 in k323 in k320 in k317 in expand-send in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_510(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_510,2,t0,t1);}
if(C_truep(t1)){
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[7])[1]))){
C_trace("ChickenBridge.scm: 181  ferror");
f_305(((C_word*)t0)[6],lf[29],(C_word)C_a_i_list(&a,2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]));}
else{
t2=((C_word*)((C_word*)t0)[3])[1];
if(C_truep(t2)){
t3=((C_word*)t0)[6];
f_455(2,t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_506,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
C_trace("map");
t4=*((C_word*)lf[31]+1);
((C_proc4)(void*)(*((C_word*)t4+1)))(4,t4,t3,*((C_word*)lf[32]+1),((C_word*)t0)[2]);}}}
else{
C_trace("ChickenBridge.scm: 178  ferror");
f_305(((C_word*)t0)[6],lf[33],(C_word)C_a_i_list(&a,2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]));}}

/* k504 in k508 in k399 in do67 in k335 in k323 in k320 in k317 in expand-send in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_506(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_506,2,t0,t1);}
C_trace("ChickenBridge.scm: 184  ferror");
f_305(((C_word*)t0)[4],lf[30],(C_word)C_a_i_list(&a,3,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1));}

/* k453 in k399 in do67 in k335 in k323 in k320 in k317 in expand-send in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_455(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[14],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_455,2,t0,t1);}
t2=(C_word)C_i_member(((C_word*)((C_word*)t0)[8])[1],((C_word*)t0)[7]);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_461,a[2]=((C_word*)t0)[5],a[3]=t2,a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
if(C_truep(t2)){
t4=t3;
f_461(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 191  ferror");
f_305(t3,lf[28],(C_word)C_a_i_list(&a,3,((C_word*)t0)[4],((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]));}}

/* k459 in k453 in k399 in do67 in k335 in k323 in k320 in k317 in expand-send in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_461(C_word c,C_word t0,C_word t1){
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
f_395(t6,t5);}

/* k393 in do67 in k335 in k323 in k320 in k317 in expand-send in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_fcall f_395(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[6])[1];
f_385(t2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k338 in k335 in k323 in k320 in k317 in expand-send in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_340(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_340,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_345,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=lf[27],tmp=(C_word)a,a+=7,tmp));
t5=((C_word*)t3)[1];
f_345(t5,((C_word*)t0)[2],((C_word*)t0)[4]);}

/* do84 in k338 in k335 in k323 in k320 in k317 in expand-send in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_fcall f_345(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_345,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[5],((C_word*)t0)[4]));}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_358,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_member(t4,((C_word*)t0)[2]))){
t5=(C_word)C_i_car(t2);
t6=(C_word)C_i_cadr(t5);
t7=t3;
f_358(t7,(C_word)C_i_set_car(t2,t6));}
else{
t5=t3;
f_358(t5,C_SCHEME_UNDEFINED);}}}

/* k356 in do84 in k338 in k335 in k323 in k320 in k317 in expand-send in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_fcall f_358(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_345(t3,((C_word*)t0)[2],t2);}

/* ferror in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_fcall f_305(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_305,NULL,3,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_313,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_apply(5,0,t4,C_retrieve(lf[24]),t2,t3);}

/* k311 in ferror in k301 in k298 in k199 in k196 in k193 in k190 */
static void C_ccall f_313(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 134  error");
t2=*((C_word*)lf[23]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* make-note-off in k199 in k196 in k193 in k190 */
static void C_ccall f_292(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_292,5,t0,t1,t2,t3,t4);}
C_trace("ChickenBridge.scm: 85   insert-midi-on");
t5=C_retrieve(lf[16]);
((C_proc6)C_retrieve_proc(t5))(6,t5,t1,t2,t3,lf[19],t4);}

/* make-note-on in k199 in k196 in k193 in k190 */
static void C_ccall f_286(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_286,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 81   insert-midi-on");
t6=C_retrieve(lf[16]);
((C_proc6)C_retrieve_proc(t6))(6,t6,t1,t2,t3,t4,t5);}

/* insert-midi-note in k199 in k196 in k193 in k190 */
static void C_ccall f_257(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
C_word tmp;
C_word t7;
C_word t8;
C_word ab[8],*a=ab;
if(c!=7) C_bad_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr7,(void*)f_257,7,t0,t1,t2,t3,t4,t5,t6);}
t7=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_261,a[2]=t1,a[3]=t6,a[4]=t5,a[5]=t4,a[6]=t3,a[7]=t2,tmp=(C_word)a,a+=8,tmp);
C_trace("##sys#gc");
t8=C_retrieve(lf[7]);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,C_SCHEME_FALSE);}

/* k259 in insert-midi-note in k199 in k196 in k193 in k190 */
static void C_ccall f_261(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_261,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[7]);
t4=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[6]);
t5=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[5]);
t6=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[4]);
t7=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[3]);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub33,a[2]=lf[13],tmp=(C_word)a,a+=3,tmp);
((C_proc8)C_retrieve_proc(t8))(8,t8,((C_word*)t0)[2],t2,t3,t4,t5,t6,t7);}

/* insert-closure in k199 in k196 in k193 in k190 */
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

/* k246 in insert-closure in k199 in k196 in k193 in k190 */
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
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub22,a[2]=lf[10],tmp=(C_word)a,a+=3,tmp);
((C_proc5)C_retrieve_proc(t4))(5,t4,((C_word*)t0)[3],t2,t3,((C_word*)t0)[2]);}

/* insert-process in k199 in k196 in k193 in k190 */
static void C_ccall f_231(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_231,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_235,a[2]=t3,a[3]=t1,a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("##sys#gc");
t5=C_retrieve(lf[7]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,C_SCHEME_FALSE);}

/* k233 in insert-process in k199 in k196 in k193 in k190 */
static void C_ccall f_235(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_235,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[4]);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub14,a[2]=lf[6],tmp=(C_word)a,a+=3,tmp);
((C_proc5)C_retrieve_proc(t4))(5,t4,((C_word*)t0)[3],t2,t3,((C_word*)t0)[2]);}

/* print-error in k199 in k196 in k193 in k190 */
static void C_ccall f_217(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_217,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_222,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[1]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_222(2,t4,C_SCHEME_FALSE);}}

/* k220 in print-error in k199 in k196 in k193 in k190 */
static void C_ccall f_222(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub7(C_SCHEME_UNDEFINED,t1));}

/* print-message in k199 in k196 in k193 in k190 */
static void C_ccall f_203(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_203,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_208,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[1]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_208(2,t4,C_SCHEME_FALSE);}}

/* k206 in print-message in k199 in k196 in k193 in k190 */
static void C_ccall f_208(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub1(C_SCHEME_UNDEFINED,t1));}

#ifdef C_ENABLE_PTABLES
static C_PTABLE_ENTRY ptable[94] = {
{"toplevelChickenBridge.scm",(void*)C_grace_toplevel},
{"f_192ChickenBridge.scm",(void*)f_192},
{"f_195ChickenBridge.scm",(void*)f_195},
{"f_198ChickenBridge.scm",(void*)f_198},
{"f_201ChickenBridge.scm",(void*)f_201},
{"f_300ChickenBridge.scm",(void*)f_300},
{"f_1063ChickenBridge.scm",(void*)f_1063},
{"f_1110ChickenBridge.scm",(void*)f_1110},
{"f_1100ChickenBridge.scm",(void*)f_1100},
{"f_1067ChickenBridge.scm",(void*)f_1067},
{"f_303ChickenBridge.scm",(void*)f_303},
{"f_1057ChickenBridge.scm",(void*)f_1057},
{"f_542ChickenBridge.scm",(void*)f_542},
{"f_593ChickenBridge.scm",(void*)f_593},
{"f_596ChickenBridge.scm",(void*)f_596},
{"f_599ChickenBridge.scm",(void*)f_599},
{"f_602ChickenBridge.scm",(void*)f_602},
{"f_605ChickenBridge.scm",(void*)f_605},
{"f_608ChickenBridge.scm",(void*)f_608},
{"f_611ChickenBridge.scm",(void*)f_611},
{"f_614ChickenBridge.scm",(void*)f_614},
{"f_1051ChickenBridge.scm",(void*)f_1051},
{"f_617ChickenBridge.scm",(void*)f_617},
{"f_1049ChickenBridge.scm",(void*)f_1049},
{"f_619ChickenBridge.scm",(void*)f_619},
{"f_632ChickenBridge.scm",(void*)f_632},
{"f_635ChickenBridge.scm",(void*)f_635},
{"f_886ChickenBridge.scm",(void*)f_886},
{"f_994ChickenBridge.scm",(void*)f_994},
{"f_906ChickenBridge.scm",(void*)f_906},
{"f_915ChickenBridge.scm",(void*)f_915},
{"f_919ChickenBridge.scm",(void*)f_919},
{"f_923ChickenBridge.scm",(void*)f_923},
{"f_931ChickenBridge.scm",(void*)f_931},
{"f_927ChickenBridge.scm",(void*)f_927},
{"f_896ChickenBridge.scm",(void*)f_896},
{"f_638ChickenBridge.scm",(void*)f_638},
{"f_641ChickenBridge.scm",(void*)f_641},
{"f_644ChickenBridge.scm",(void*)f_644},
{"f_647ChickenBridge.scm",(void*)f_647},
{"f_880ChickenBridge.scm",(void*)f_880},
{"f_779ChickenBridge.scm",(void*)f_779},
{"f_786ChickenBridge.scm",(void*)f_786},
{"f_788ChickenBridge.scm",(void*)f_788},
{"f_860ChickenBridge.scm",(void*)f_860},
{"f_812ChickenBridge.scm",(void*)f_812},
{"f_815ChickenBridge.scm",(void*)f_815},
{"f_836ChickenBridge.scm",(void*)f_836},
{"f_802ChickenBridge.scm",(void*)f_802},
{"f_650ChickenBridge.scm",(void*)f_650},
{"f_768ChickenBridge.scm",(void*)f_768},
{"f_756ChickenBridge.scm",(void*)f_756},
{"f_752ChickenBridge.scm",(void*)f_752},
{"f_657ChickenBridge.scm",(void*)f_657},
{"f_586ChickenBridge.scm",(void*)f_586},
{"f_580ChickenBridge.scm",(void*)f_580},
{"f_574ChickenBridge.scm",(void*)f_574},
{"f_568ChickenBridge.scm",(void*)f_568},
{"f_562ChickenBridge.scm",(void*)f_562},
{"f_556ChickenBridge.scm",(void*)f_556},
{"f_550ChickenBridge.scm",(void*)f_550},
{"f_544ChickenBridge.scm",(void*)f_544},
{"f_315ChickenBridge.scm",(void*)f_315},
{"f_319ChickenBridge.scm",(void*)f_319},
{"f_532ChickenBridge.scm",(void*)f_532},
{"f_322ChickenBridge.scm",(void*)f_322},
{"f_325ChickenBridge.scm",(void*)f_325},
{"f_337ChickenBridge.scm",(void*)f_337},
{"f_385ChickenBridge.scm",(void*)f_385},
{"f_401ChickenBridge.scm",(void*)f_401},
{"f_411ChickenBridge.scm",(void*)f_411},
{"f_510ChickenBridge.scm",(void*)f_510},
{"f_506ChickenBridge.scm",(void*)f_506},
{"f_455ChickenBridge.scm",(void*)f_455},
{"f_461ChickenBridge.scm",(void*)f_461},
{"f_395ChickenBridge.scm",(void*)f_395},
{"f_340ChickenBridge.scm",(void*)f_340},
{"f_345ChickenBridge.scm",(void*)f_345},
{"f_358ChickenBridge.scm",(void*)f_358},
{"f_305ChickenBridge.scm",(void*)f_305},
{"f_313ChickenBridge.scm",(void*)f_313},
{"f_292ChickenBridge.scm",(void*)f_292},
{"f_286ChickenBridge.scm",(void*)f_286},
{"f_257ChickenBridge.scm",(void*)f_257},
{"f_261ChickenBridge.scm",(void*)f_261},
{"f_244ChickenBridge.scm",(void*)f_244},
{"f_248ChickenBridge.scm",(void*)f_248},
{"f_231ChickenBridge.scm",(void*)f_231},
{"f_235ChickenBridge.scm",(void*)f_235},
{"f_217ChickenBridge.scm",(void*)f_217},
{"f_222ChickenBridge.scm",(void*)f_222},
{"f_203ChickenBridge.scm",(void*)f_203},
{"f_208ChickenBridge.scm",(void*)f_208},
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
