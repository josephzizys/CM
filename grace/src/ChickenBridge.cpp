/* Generated from ChickenBridge.scm by the CHICKEN compiler
   http://www.call-with-current-continuation.org
   2007-10-23 06:08
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

static C_TLS C_word lf[116];


/* from k270 */
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

/* from k241 */
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

/* from k228 */
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

/* from k208 in print-error in k187 in k184 in k181 in k178 */
static C_word C_fcall stub7(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub7(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_error(t0);
return C_r;}

/* from k194 in print-message in k187 in k184 in k181 in k178 */
static C_word C_fcall stub1(C_word C_buf,C_word C_a0) C_regparm;
C_regparm static C_word C_fcall stub1(C_word C_buf,C_word C_a0){
C_word C_r=C_SCHEME_UNDEFINED,*C_a=(C_word*)C_buf;
char * t0=(char * )C_string_or_null(C_a0);
print_mess(t0);
return C_r;}

C_noret_decl(C_grace_toplevel)
C_externexport void C_ccall C_grace_toplevel(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_180)
static void C_ccall f_180(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_183)
static void C_ccall f_183(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_186)
static void C_ccall f_186(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_189)
static void C_ccall f_189(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_288)
static void C_ccall f_288(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_905)
static void C_ccall f_905(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_952)
static void C_ccall f_952(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_942)
static void C_ccall f_942(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_909)
static void C_ccall f_909(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_291)
static void C_ccall f_291(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_899)
static void C_ccall f_899(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_899)
static void C_ccall f_899r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;
C_noret_decl(f_530)
static void C_ccall f_530(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_581)
static void C_ccall f_581(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_584)
static void C_ccall f_584(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_587)
static void C_ccall f_587(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_590)
static void C_ccall f_590(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_593)
static void C_ccall f_593(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_596)
static void C_ccall f_596(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_599)
static void C_ccall f_599(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_602)
static void C_ccall f_602(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_893)
static void C_ccall f_893(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...) C_noret;
C_noret_decl(f_893)
static void C_ccall f_893r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t5) C_noret;
C_noret_decl(f_605)
static void C_ccall f_605(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_891)
static void C_ccall f_891(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_607)
static void C_ccall f_607(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_620)
static void C_ccall f_620(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_623)
static void C_ccall f_623(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_728)
static void C_fcall f_728(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_836)
static void C_ccall f_836(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_748)
static void C_fcall f_748(C_word t0,C_word t1) C_noret;
C_noret_decl(f_757)
static void C_fcall f_757(C_word t0,C_word t1) C_noret;
C_noret_decl(f_761)
static void C_ccall f_761(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_765)
static void C_ccall f_765(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_773)
static void C_fcall f_773(C_word t0,C_word t1) C_noret;
C_noret_decl(f_769)
static void C_ccall f_769(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_738)
static void C_ccall f_738(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_626)
static void C_ccall f_626(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_629)
static void C_ccall f_629(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_632)
static void C_ccall f_632(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_635)
static void C_ccall f_635(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_690)
static void C_ccall f_690(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_678)
static void C_ccall f_678(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_674)
static void C_ccall f_674(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_574)
static void C_ccall f_574(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_568)
static void C_ccall f_568(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_562)
static void C_ccall f_562(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_556)
static void C_ccall f_556(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_550)
static void C_ccall f_550(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_544)
static void C_ccall f_544(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_538)
static void C_ccall f_538(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_532)
static void C_ccall f_532(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_303)
static void C_ccall f_303(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_307)
static void C_ccall f_307(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_520)
static void C_ccall f_520(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_310)
static void C_ccall f_310(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_313)
static void C_ccall f_313(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_325)
static void C_ccall f_325(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_373)
static void C_fcall f_373(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_389)
static void C_ccall f_389(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_399)
static void C_ccall f_399(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_498)
static void C_ccall f_498(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_494)
static void C_ccall f_494(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_443)
static void C_ccall f_443(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_449)
static void C_ccall f_449(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_383)
static void C_fcall f_383(C_word t0,C_word t1) C_noret;
C_noret_decl(f_328)
static void C_ccall f_328(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_333)
static void C_fcall f_333(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_346)
static void C_fcall f_346(C_word t0,C_word t1) C_noret;
C_noret_decl(f_293)
static void C_fcall f_293(C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_301)
static void C_ccall f_301(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_280)
static void C_ccall f_280(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_274)
static void C_ccall f_274(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5) C_noret;
C_noret_decl(f_245)
static void C_ccall f_245(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6) C_noret;
C_noret_decl(f_249)
static void C_ccall f_249(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_232)
static void C_ccall f_232(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_236)
static void C_ccall f_236(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_219)
static void C_ccall f_219(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_223)
static void C_ccall f_223(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_205)
static void C_ccall f_205(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_210)
static void C_ccall f_210(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_191)
static void C_ccall f_191(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_196)
static void C_ccall f_196(C_word c,C_word t0,C_word t1) C_noret;

C_noret_decl(trf_728)
static void C_fcall trf_728(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_728(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_728(t0,t1,t2);}

C_noret_decl(trf_748)
static void C_fcall trf_748(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_748(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_748(t0,t1);}

C_noret_decl(trf_757)
static void C_fcall trf_757(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_757(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_757(t0,t1);}

C_noret_decl(trf_773)
static void C_fcall trf_773(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_773(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_773(t0,t1);}

C_noret_decl(trf_373)
static void C_fcall trf_373(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_373(void *dummy){
C_word t4=C_pick(0);
C_word t3=C_pick(1);
C_word t2=C_pick(2);
C_word t1=C_pick(3);
C_word t0=C_pick(4);
C_adjust_stack(-5);
f_373(t0,t1,t2,t3,t4);}

C_noret_decl(trf_383)
static void C_fcall trf_383(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_383(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_383(t0,t1);}

C_noret_decl(trf_333)
static void C_fcall trf_333(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_333(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_333(t0,t1,t2);}

C_noret_decl(trf_346)
static void C_fcall trf_346(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_346(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_346(t0,t1);}

C_noret_decl(trf_293)
static void C_fcall trf_293(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_293(void *dummy){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
f_293(t0,t1,t2);}

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
if(!C_demand_2(1030)){
C_save(t1);
C_rereclaim2(1030*sizeof(C_word), 1);
t1=C_restore;}
a=C_alloc(3);
C_initialize_lf(lf,116);
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
lf[39]=C_static_lambda_info(C_heaptop,6,"(a519)");
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
lf[67]=C_h_intern(&lf[67],6,"lambda");
lf[68]=C_h_intern(&lf[68],7,"elapsed");
lf[69]=C_h_intern(&lf[69],1,"x");
lf[70]=C_h_intern(&lf[70],4,"set!");
lf[71]=C_h_intern(&lf[71],4,"wait");
lf[72]=C_h_intern(&lf[72],4,"else");
lf[73]=C_h_intern(&lf[73],4,"cond");
lf[74]=C_h_intern(&lf[74],4,"let*");
lf[75]=C_h_intern(&lf[75],10,"\003sysappend");
lf[76]=C_h_intern(&lf[76],6,"gensym");
lf[77]=C_h_intern(&lf[77],5,"\000null");
lf[78]=C_static_string(C_heaptop,43,"binding clause not a list (var init [step])");
lf[79]=C_static_lambda_info(C_heaptop,15,"(do124 tail126)");
lf[80]=C_static_string(C_heaptop,36,"go stopping clause missing test form");
lf[81]=C_static_string(C_heaptop,29,"go stopping clause not a list");
lf[82]=C_static_string(C_heaptop,22,"go bindings not a list");
lf[83]=C_static_lambda_info(C_heaptop,44,"(expand-go bindings118 terminate119 body120)");
lf[84]=C_h_intern(&lf[84],14,"return-to-host");
lf[85]=C_static_lambda_info(C_heaptop,41,"(a892 bindings115 terminate116 . body117)");
lf[86]=C_h_intern(&lf[86],18,"\003sysregister-macro");
lf[87]=C_h_intern(&lf[87],2,"go");
lf[88]=C_h_intern(&lf[88],15,"hash-table-set!");
lf[89]=C_static_string(C_heaptop,9,"mp:inhook");
tmp=C_intern(C_heaptop,9,"mp:inhook");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000func");
C_save(tmp);
tmp=C_SCHEME_FALSE;
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[90]=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
lf[91]=C_static_string(C_heaptop,8,"mp:micro");
tmp=C_intern(C_heaptop,8,"mp:micro");
C_save(tmp);
tmp=C_intern(C_heaptop,5,"\000divs");
C_save(tmp);
tmp=C_fix(1);
C_save(tmp);
tmp=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
C_save(tmp);
lf[92]=C_h_list(2,C_pick(1),C_pick(0));
C_drop(2);
lf[93]=C_static_string(C_heaptop,9,"mp:alloff");
tmp=C_intern(C_heaptop,9,"mp:alloff");
C_save(tmp);
tmp=C_SCHEME_END_OF_LIST;
lf[94]=C_h_pair(C_restore,tmp);
lf[95]=C_static_string(C_heaptop,7,"mp:ctrl");
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
lf[96]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[97]=C_static_string(C_heaptop,7,"mp:prog");
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
lf[98]=C_h_list(4,C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(4);
lf[99]=C_static_string(C_heaptop,6,"mp:off");
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
lf[100]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[101]=C_static_string(C_heaptop,5,"mp:on");
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
lf[102]=C_h_list(5,C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(5);
lf[103]=C_static_string(C_heaptop,7,"mp:note");
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
lf[104]=C_h_list(6,C_pick(5),C_pick(4),C_pick(3),C_pick(2),C_pick(1),C_pick(0));
C_drop(6);
lf[105]=C_static_lambda_info(C_heaptop,22,"(a898 mess91 . data92)");
lf[106]=C_h_intern(&lf[106],4,"send");
lf[107]=C_h_intern(&lf[107],5,"quote");
lf[108]=C_h_intern(&lf[108],10,"*messages*");
lf[109]=C_h_intern(&lf[109],14,"string->symbol");
lf[110]=C_static_string(C_heaptop,51,"message function not string, symbol or list of both");
lf[111]=C_static_lambda_info(C_heaptop,20,"(a904 func49 info50)");
lf[112]=C_h_intern(&lf[112],19,"define-send-message");
lf[113]=C_h_intern(&lf[113],15,"make-hash-table");
lf[114]=C_h_intern(&lf[114],6,"equal\077");
lf[115]=C_static_lambda_info(C_heaptop,10,"(toplevel)");
C_register_lf2(lf,116,create_ptable());
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_180,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_library_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k178 */
static void C_ccall f_180(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_180,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_183,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_eval_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k181 in k178 */
static void C_ccall f_183(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_183,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_186,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k184 in k181 in k178 */
static void C_ccall f_186(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_186,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_189,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k187 in k184 in k181 in k178 */
static void C_ccall f_189(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_189,2,t0,t1);}
t2=C_mutate((C_word*)lf[0]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_191,a[2]=lf[2],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[3]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_205,a[2]=lf[4],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate((C_word*)lf[5]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_219,a[2]=lf[8],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate((C_word*)lf[9]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_232,a[2]=lf[11],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[12]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_245,a[2]=lf[14],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate((C_word*)lf[15]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_274,a[2]=lf[17],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate((C_word*)lf[18]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_280,a[2]=lf[20],tmp=(C_word)a,a+=3,tmp));
t9=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_288,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 117  make-hash-table");
t10=C_retrieve(lf[113]);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,*((C_word*)lf[114]+1));}

/* k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_288(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_288,2,t0,t1);}
t2=C_mutate(&lf[21],t1);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_291,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_905,a[2]=lf[111],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 119  ##sys#register-macro");
t5=C_retrieve(lf[86]);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,lf[112],t4);}

/* a904 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_905(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
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
C_save_and_reclaim((void*)tr4,(void*)f_905,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_909,a[2]=t6,a[3]=t1,a[4]=t3,a[5]=t4,tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_pairp(((C_word*)t4)[1]))){
t8=(C_word)C_i_car(((C_word*)t4)[1]);
t9=C_set_block_item(t6,0,t8);
t10=(C_word)C_i_cadr(((C_word*)t4)[1]);
t11=C_set_block_item(t4,0,t10);
t12=t7;
f_909(2,t12,t11);}
else{
if(C_truep((C_word)C_i_stringp(((C_word*)t4)[1]))){
t8=C_set_block_item(t6,0,((C_word*)t4)[1]);
t9=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_942,a[2]=t7,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 126  string->symbol");
t10=*((C_word*)lf[109]+1);
((C_proc3)C_retrieve_proc(t10))(3,t10,t9,((C_word*)t4)[1]);}
else{
if(C_truep((C_word)C_i_symbolp(((C_word*)t4)[1]))){
t8=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_952,a[2]=t7,a[3]=t6,tmp=(C_word)a,a+=4,tmp);
C_trace("ChickenBridge.scm: 128  symbol->string");
t9=*((C_word*)lf[41]+1);
((C_proc3)C_retrieve_proc(t9))(3,t9,t8,((C_word*)t4)[1]);}
else{
C_trace("ChickenBridge.scm: 130  error");
t8=*((C_word*)lf[23]+1);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,lf[110]);}}}}

/* k950 in a904 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_952(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_909(2,t3,t2);}

/* k940 in a904 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_942(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_909(2,t3,t2);}

/* k907 in a904 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_909(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_909,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)((C_word*)t0)[5])[1],((C_word*)t0)[4]);
t3=(C_word)C_a_i_list(&a,2,lf[107],t2);
t4=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,(C_word)C_a_i_list(&a,4,lf[88],lf[108],((C_word*)((C_word*)t0)[2])[1],t3));}

/* k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_291(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_291,2,t0,t1);}
t2=C_mutate(&lf[22],(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_293,a[2]=lf[25],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[26]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_303,a[2]=lf[42],tmp=(C_word)a,a+=3,tmp));
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_530,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_899,a[2]=lf[105],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 206  ##sys#register-macro");
t6=C_retrieve(lf[86]);
((C_proc4)C_retrieve_proc(t6))(4,t6,t4,lf[106],t5);}

/* a898 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_899(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr3r,(void*)f_899r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_899r(t0,t1,t2,t3);}}

static void C_ccall f_899r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_trace("ChickenBridge.scm: 207  expand-send");
t4=C_retrieve(lf[26]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t1,t2,t3);}

/* k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_530(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_530,2,t0,t1);}
t2=C_mutate((C_word*)lf[43]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_532,a[2]=lf[44],tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[45]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_538,a[2]=lf[47],tmp=(C_word)a,a+=3,tmp));
t4=C_mutate((C_word*)lf[48]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_544,a[2]=lf[50],tmp=(C_word)a,a+=3,tmp));
t5=C_mutate((C_word*)lf[51]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_550,a[2]=lf[53],tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[54]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_556,a[2]=lf[56],tmp=(C_word)a,a+=3,tmp));
t7=C_mutate((C_word*)lf[57]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_562,a[2]=lf[59],tmp=(C_word)a,a+=3,tmp));
t8=C_mutate((C_word*)lf[60]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_568,a[2]=lf[62],tmp=(C_word)a,a+=3,tmp));
t9=C_mutate((C_word*)lf[63]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_574,a[2]=lf[65],tmp=(C_word)a,a+=3,tmp));
t10=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_581,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 234  hash-table-set!");
t11=C_retrieve(lf[88]);
((C_proc5)C_retrieve_proc(t11))(5,t11,t10,lf[21],lf[103],lf[104]);}

/* k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_581(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_581,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_584,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 235  hash-table-set!");
t3=C_retrieve(lf[88]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[21],lf[101],lf[102]);}

/* k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_584(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_584,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_587,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 236  hash-table-set!");
t3=C_retrieve(lf[88]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[21],lf[99],lf[100]);}

/* k585 in k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_587(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_587,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_590,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 237  hash-table-set!");
t3=C_retrieve(lf[88]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[21],lf[97],lf[98]);}

/* k588 in k585 in k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_590(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_590,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_593,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 238  hash-table-set!");
t3=C_retrieve(lf[88]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[21],lf[95],lf[96]);}

/* k591 in k588 in k585 in k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_593(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_593,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_596,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 239  hash-table-set!");
t3=C_retrieve(lf[88]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[21],lf[93],lf[94]);}

/* k594 in k591 in k588 in k585 in k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_596(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_596,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_599,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 240  hash-table-set!");
t3=C_retrieve(lf[88]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[21],lf[91],lf[92]);}

/* k597 in k594 in k591 in k588 in k585 in k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_599(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_599,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_602,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 241  hash-table-set!");
t3=C_retrieve(lf[88]);
((C_proc5)C_retrieve_proc(t3))(5,t3,t2,lf[21],lf[89],lf[90]);}

/* k600 in k597 in k594 in k591 in k588 in k585 in k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_602(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_602,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_605,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_893,a[2]=lf[85],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 263  ##sys#register-macro");
t4=C_retrieve(lf[86]);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,lf[87],t3);}

/* a892 in k600 in k597 in k594 in k591 in k588 in k585 in k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_893(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,...){
C_word tmp;
C_word t4;
va_list v;
C_word *a,c2=c;
C_save_rest(t3,c2,4);
if(c<4) C_bad_min_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr4r,(void*)f_893r,4,t0,t1,t2,t3);}
else{
a=C_alloc((c-4)*3);
t4=C_restore_rest(a,C_rest_count(0));
f_893r(t0,t1,t2,t3,t4);}}

static void C_ccall f_893r(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_trace("ChickenBridge.scm: 264  expand-go");
t5=C_retrieve(lf[66]);
((C_proc5)C_retrieve_proc(t5))(5,t5,t1,t2,t3,t4);}

/* k603 in k600 in k597 in k594 in k591 in k588 in k585 in k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_605(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_605,2,t0,t1);}
t2=C_mutate((C_word*)lf[66]+1,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_607,a[2]=lf[83],tmp=(C_word)a,a+=3,tmp));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_891,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 313  return-to-host");
t4=C_retrieve(lf[84]);
((C_proc2)C_retrieve_proc(t4))(2,t4,t3);}

/* k889 in k603 in k600 in k597 in k594 in k591 in k588 in k585 in k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_891(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_UNDEFINED);}

/* expand-go in k603 in k600 in k597 in k594 in k591 in k588 in k585 in k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_607(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
C_save_and_reclaim((void*)tr5,(void*)f_607,5,t0,t1,t2,t3,t4);}
t5=C_SCHEME_END_OF_LIST;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=C_SCHEME_END_OF_LIST;
t8=(*a=C_VECTOR_TYPE|1,a[1]=t7,tmp=(C_word)a,a+=2,tmp);
t9=C_SCHEME_END_OF_LIST;
t10=(*a=C_VECTOR_TYPE|1,a[1]=t9,tmp=(C_word)a,a+=2,tmp);
t11=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_620,a[2]=t2,a[3]=t10,a[4]=t4,a[5]=t8,a[6]=t1,a[7]=t6,a[8]=t3,tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(t2))){
t12=t11;
f_620(2,t12,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 272  error");
t12=*((C_word*)lf[23]+1);
((C_proc4)C_retrieve_proc(t12))(4,t12,t11,lf[82],t2);}}

/* k618 in expand-go in k603 in k600 in k597 in k594 in k591 in k588 in k585 in k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_620(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_620,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_623,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=((C_word*)t0)[8],tmp=(C_word)a,a+=9,tmp);
if(C_truep((C_word)C_i_listp(((C_word*)t0)[8]))){
if(C_truep((C_word)C_i_nullp(((C_word*)t0)[8]))){
C_trace("ChickenBridge.scm: 276  error");
t3=*((C_word*)lf[23]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t2,lf[80]);}
else{
t3=t2;
f_623(2,t3,C_SCHEME_UNDEFINED);}}
else{
C_trace("ChickenBridge.scm: 274  error");
t3=*((C_word*)lf[23]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,t2,lf[81],((C_word*)t0)[8]);}}

/* k621 in k618 in expand-go in k603 in k600 in k597 in k594 in k591 in k588 in k585 in k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_623(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_623,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_626,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],a[7]=((C_word*)t0)[8],tmp=(C_word)a,a+=8,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_728,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[7],a[5]=t4,a[6]=lf[79],tmp=(C_word)a,a+=7,tmp));
t6=((C_word*)t4)[1];
f_728(t6,t2,((C_word*)t0)[2]);}

/* do124 in k621 in k618 in expand-go in k603 in k600 in k597 in k594 in k591 in k588 in k585 in k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_fcall f_728(C_word t0,C_word t1,C_word t2){
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
C_save_and_reclaim((void*)trf_728,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,C_SCHEME_FALSE);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_738,a[2]=t1,a[3]=((C_word*)t0)[5],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_748,a[2]=t3,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=t2,tmp=(C_word)a,a+=7,tmp);
t5=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_pairp(t5))){
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_836,a[2]=t4,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t7=(C_word)C_i_car(t2);
t8=(C_word)C_i_length(t7);
C_trace("ChickenBridge.scm: 280  <");
C_lessp(5,0,t6,C_fix(0),t8,C_fix(4));}
else{
t6=t4;
f_748(t6,C_SCHEME_FALSE);}}}

/* k834 in do124 in k621 in k618 in expand-go in k603 in k600 in k597 in k594 in k591 in k588 in k585 in k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_836(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[3]);
t3=(C_word)C_i_car(t2);
t4=((C_word*)t0)[2];
f_748(t4,(C_word)C_i_symbolp(t3));}
else{
t2=((C_word*)t0)[2];
f_748(t2,C_SCHEME_FALSE);}}

/* k746 in do124 in k621 in k618 in expand-go in k603 in k600 in k597 in k594 in k591 in k588 in k585 in k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_fcall f_748(C_word t0,C_word t1){
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
C_save_and_reclaim((void*)trf_748,NULL,2,t0,t1);}
if(C_truep(t1)){
t2=(C_word)C_i_car(((C_word*)t0)[6]);
t3=(C_word)C_i_car(t2);
t4=(C_word)C_i_car(((C_word*)t0)[6]);
t5=(C_word)C_i_cadr(t4);
t6=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_757,a[2]=t5,a[3]=t3,a[4]=((C_word*)t0)[2],a[5]=((C_word*)t0)[3],a[6]=((C_word*)t0)[4],a[7]=((C_word*)t0)[5],tmp=(C_word)a,a+=8,tmp);
t7=(C_word)C_i_car(((C_word*)t0)[6]);
t8=(C_word)C_i_cddr(t7);
if(C_truep((C_word)C_i_nullp(t8))){
t9=t6;
f_757(t9,lf[77]);}
else{
t9=(C_word)C_i_car(((C_word*)t0)[6]);
t10=t6;
f_757(t10,(C_word)C_i_caddr(t9));}}
else{
t2=(C_word)C_i_car(((C_word*)t0)[6]);
C_trace("ChickenBridge.scm: 293  error");
t3=*((C_word*)lf[23]+1);
((C_proc4)C_retrieve_proc(t3))(4,t3,((C_word*)t0)[2],lf[78],t2);}}

/* k755 in k746 in do124 in k621 in k618 in expand-go in k603 in k600 in k597 in k594 in k591 in k588 in k585 in k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_fcall f_757(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[12],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_757,NULL,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_761,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t3=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
C_trace("ChickenBridge.scm: 288  append");
t4=*((C_word*)lf[37]+1);
((C_proc4)C_retrieve_proc(t4))(4,t4,t2,((C_word*)((C_word*)t0)[7])[1],t3);}

/* k759 in k755 in k746 in do124 in k621 in k618 in expand-go in k603 in k600 in k597 in k594 in k591 in k588 in k585 in k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_761(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_761,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[8])+1,t1);
t3=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_765,a[2]=((C_word*)t0)[3],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[6],a[6]=((C_word*)t0)[7],tmp=(C_word)a,a+=7,tmp);
t4=(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]);
C_trace("ChickenBridge.scm: 289  append");
t5=*((C_word*)lf[37]+1);
((C_proc4)C_retrieve_proc(t5))(4,t5,t3,((C_word*)((C_word*)t0)[7])[1],t4);}

/* k763 in k759 in k755 in k746 in do124 in k621 in k618 in expand-go in k603 in k600 in k597 in k594 in k591 in k588 in k585 in k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_765(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_765,2,t0,t1);}
t2=C_mutate(((C_word *)((C_word*)t0)[6])+1,t1);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_769,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],tmp=(C_word)a,a+=4,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_773,a[2]=((C_word*)t0)[5],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_eqp(((C_word*)t0)[3],lf[77]);
if(C_truep(t5)){
t6=t4;
f_773(t6,C_SCHEME_END_OF_LIST);}
else{
t6=(C_word)C_a_i_list(&a,3,lf[70],((C_word*)t0)[2],((C_word*)t0)[3]);
t7=t4;
f_773(t7,(C_word)C_a_i_list(&a,1,t6));}}

/* k771 in k763 in k759 in k755 in k746 in do124 in k621 in k618 in expand-go in k603 in k600 in k597 in k594 in k591 in k588 in k585 in k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_fcall f_773(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 290  append");
t2=*((C_word*)lf[37]+1);
((C_proc4)C_retrieve_proc(t2))(4,t2,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1);}

/* k767 in k763 in k759 in k755 in k746 in do124 in k621 in k618 in expand-go in k603 in k600 in k597 in k594 in k591 in k588 in k585 in k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_769(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=C_mutate(((C_word *)((C_word*)t0)[3])+1,t1);
t3=((C_word*)t0)[2];
f_738(2,t3,t2);}

/* k736 in do124 in k621 in k618 in expand-go in k603 in k600 in k597 in k594 in k591 in k588 in k585 in k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_738(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_728(t3,((C_word*)t0)[2],t2);}

/* k624 in k621 in k618 in expand-go in k603 in k600 in k597 in k594 in k591 in k588 in k585 in k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_626(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_626,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_629,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 295  gensym");
t3=C_retrieve(lf[76]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k627 in k624 in k621 in k618 in expand-go in k603 in k600 in k597 in k594 in k591 in k588 in k585 in k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_629(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_629,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_632,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 296  gensym");
t3=C_retrieve(lf[76]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k630 in k627 in k624 in k621 in k618 in expand-go in k603 in k600 in k597 in k594 in k591 in k588 in k585 in k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_632(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_632,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_635,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=((C_word*)t0)[6],a[7]=((C_word*)t0)[7],a[8]=t1,tmp=(C_word)a,a+=9,tmp);
C_trace("ChickenBridge.scm: 297  gensym");
t3=C_retrieve(lf[76]);
((C_proc2)C_retrieve_proc(t3))(2,t3,t2);}

/* k633 in k630 in k627 in k624 in k621 in k618 in expand-go in k603 in k600 in k597 in k594 in k591 in k588 in k585 in k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_635(C_word c,C_word t0,C_word t1){
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
C_word ab[74],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_635,2,t0,t1);}
t2=(C_word)C_a_i_list(&a,1,((C_word*)t0)[8]);
t3=(C_word)C_a_i_list(&a,2,t1,C_fix(0));
t4=(C_word)C_a_i_list(&a,3,lf[67],C_SCHEME_END_OF_LIST,((C_word*)t0)[8]);
t5=(C_word)C_a_i_list(&a,2,lf[68],t4);
t6=(C_word)C_a_i_list(&a,1,lf[69]);
t7=(C_word)C_a_i_list(&a,3,lf[70],t1,lf[69]);
t8=(C_word)C_a_i_list(&a,3,lf[67],t6,t7);
t9=(C_word)C_a_i_list(&a,2,lf[71],t8);
t10=(C_word)C_a_i_list(&a,3,t3,t5,t9);
t11=(C_word)C_i_car(((C_word*)t0)[7]);
t12=(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_690,a[2]=((C_word*)t0)[2],a[3]=t1,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[6],a[8]=t2,a[9]=t10,a[10]=t11,tmp=(C_word)a,a+=11,tmp);
t13=(C_word)C_i_cdr(((C_word*)t0)[7]);
t14=(C_word)C_a_i_list(&a,1,C_fix(-1));
C_trace("##sys#append");
t15=*((C_word*)lf[75]+1);
((C_proc4)(void*)(*((C_word*)t15+1)))(4,t15,t12,t13,t14);}

/* k688 in k633 in k630 in k627 in k624 in k621 in k618 in expand-go in k603 in k600 in k597 in k594 in k591 in k588 in k585 in k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_690(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[18],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_690,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,((C_word*)t0)[10],t1);
t3=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_674,a[2]=((C_word*)t0)[5],a[3]=((C_word*)t0)[6],a[4]=((C_word*)t0)[7],a[5]=((C_word*)t0)[8],a[6]=((C_word*)t0)[9],a[7]=t2,tmp=(C_word)a,a+=8,tmp);
t4=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_678,a[2]=((C_word*)t0)[4],a[3]=t3,tmp=(C_word)a,a+=4,tmp);
t5=(C_word)C_a_i_list(&a,1,((C_word*)t0)[3]);
C_trace("##sys#append");
t6=*((C_word*)lf[75]+1);
((C_proc4)(void*)(*((C_word*)t6+1)))(4,t6,t4,((C_word*)((C_word*)t0)[2])[1],t5);}

/* k676 in k688 in k633 in k630 in k627 in k624 in k621 in k618 in expand-go in k603 in k600 in k597 in k594 in k591 in k588 in k585 in k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_678(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("##sys#append");
t2=*((C_word*)lf[75]+1);
((C_proc4)(void*)(*((C_word*)t2+1)))(4,t2,((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k672 in k688 in k633 in k630 in k627 in k624 in k621 in k618 in expand-go in k603 in k600 in k597 in k594 in k591 in k588 in k585 in k582 in k579 in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_674(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_674,2,t0,t1);}
t2=(C_word)C_a_i_cons(&a,2,lf[72],t1);
t3=(C_word)C_a_i_list(&a,3,lf[73],((C_word*)t0)[7],t2);
t4=(C_word)C_a_i_list(&a,3,lf[74],((C_word*)t0)[6],t3);
t5=(C_word)C_a_i_list(&a,3,lf[67],((C_word*)t0)[5],t4);
t6=(C_word)C_a_i_list(&a,3,lf[67],((C_word*)((C_word*)t0)[4])[1],t5);
t7=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t7+1)))(2,t7,(C_word)C_a_i_cons(&a,2,t6,((C_word*)((C_word*)t0)[2])[1]));}

/* mp:inhook in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_574(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_574,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 230  error");
t3=*((C_word*)lf[23]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[64]);}

/* mp:micro in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_568(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_568,3,t0,t1,t2);}
C_trace("ChickenBridge.scm: 228  error");
t3=*((C_word*)lf[23]+1);
((C_proc3)C_retrieve_proc(t3))(3,t3,t1,lf[61]);}

/* mp:alloff in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_562(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_562,2,t0,t1);}
C_trace("ChickenBridge.scm: 226  error");
t2=*((C_word*)lf[23]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,t1,lf[58]);}

/* mp:ctrl in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_556(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_556,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 224  error");
t6=*((C_word*)lf[23]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[55]);}

/* mp:prog in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_550(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_550,5,t0,t1,t2,t3,t4);}
C_trace("ChickenBridge.scm: 222  error");
t5=*((C_word*)lf[23]+1);
((C_proc3)C_retrieve_proc(t5))(3,t5,t1,lf[52]);}

/* mp:off in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_544(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_544,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 220  error");
t6=*((C_word*)lf[23]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[49]);}

/* mp:on in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_538(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_538,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 218  error");
t6=*((C_word*)lf[23]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t1,lf[46]);}

/* mp:note in k528 in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_532(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
C_word tmp;
C_word t7;
C_word *a;
if(c!=7) C_bad_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr7,(void*)f_532,7,t0,t1,t2,t3,t4,t5,t6);}
C_trace("ChickenBridge.scm: 214  insert-midi-note");
t7=*((C_word*)lf[12]+1);
((C_proc7)C_retrieve_proc(t7))(7,t7,t1,t2,t3,t4,t5,t6);}

/* expand-send in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_303(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word ab[6],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_303,4,t0,t1,t2,t3);}
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_307,a[2]=t1,a[3]=t4,tmp=(C_word)a,a+=4,tmp);
if(C_truep((C_word)C_i_symbolp(t2))){
C_trace("ChickenBridge.scm: 137  symbol->string");
t6=*((C_word*)lf[41]+1);
((C_proc3)C_retrieve_proc(t6))(3,t6,t5,t2);}
else{
t6=t5;
f_307(2,t6,t2);}}

/* k305 in expand-send in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_307(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_307,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_310,a[2]=t1,a[3]=((C_word*)t0)[2],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_520,a[2]=lf[39],tmp=(C_word)a,a+=3,tmp);
C_trace("ChickenBridge.scm: 138  hash-table-ref");
t4=*((C_word*)lf[40]+1);
((C_proc5)C_retrieve_proc(t4))(5,t4,t2,lf[21],t1,t3);}

/* a519 in k305 in expand-send in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_520(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(c!=2) C_bad_argc_2(c,2,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_520,2,t0,t1);}
t2=t1;
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_FALSE);}

/* k308 in k305 in expand-send in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_310(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_310,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_313,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=t1,a[5]=((C_word*)t0)[4],tmp=(C_word)a,a+=6,tmp);
t3=t1;
if(C_truep(t3)){
t4=t2;
f_313(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 139  ferror");
f_293(t2,lf[38],(C_word)C_a_i_list(&a,1,((C_word*)t0)[2]));}}

/* k311 in k308 in k305 in expand-send in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_313(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_313,2,t0,t1);}
t2=((C_word*)((C_word*)t0)[5])[1];
t3=(C_word)C_i_car(((C_word*)t0)[4]);
t4=(C_word)C_i_cdr(((C_word*)t0)[4]);
t5=C_SCHEME_FALSE;
t6=(*a=C_VECTOR_TYPE|1,a[1]=t5,tmp=(C_word)a,a+=2,tmp);
t7=(C_word)C_i_length(t4);
t8=(*a=C_CLOSURE_TYPE|9,a[1]=(C_word)f_325,a[2]=t7,a[3]=t2,a[4]=((C_word*)t0)[2],a[5]=t6,a[6]=((C_word*)t0)[5],a[7]=((C_word*)t0)[3],a[8]=t4,a[9]=t3,tmp=(C_word)a,a+=10,tmp);
C_trace("ChickenBridge.scm: 146  append");
t9=*((C_word*)lf[37]+1);
((C_proc4)C_retrieve_proc(t9))(4,t9,t8,t4,C_SCHEME_END_OF_LIST);}

/* k323 in k311 in k308 in k305 in expand-send in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_325(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[19],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_325,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_328,a[2]=((C_word*)t0)[7],a[3]=((C_word*)t0)[8],a[4]=t1,a[5]=((C_word*)t0)[9],tmp=(C_word)a,a+=6,tmp);
t3=C_SCHEME_UNDEFINED;
t4=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t5=C_set_block_item(t4,0,(*a=C_CLOSURE_TYPE|10,a[1]=(C_word)f_373,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],a[4]=((C_word*)t0)[4],a[5]=t1,a[6]=((C_word*)t0)[8],a[7]=((C_word*)t0)[5],a[8]=t4,a[9]=((C_word*)t0)[6],a[10]=lf[36],tmp=(C_word)a,a+=11,tmp));
t6=((C_word*)t4)[1];
f_373(t6,t2,C_SCHEME_FALSE,C_SCHEME_FALSE,C_fix(0));}

/* do67 in k323 in k311 in k308 in k305 in expand-send in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_fcall f_373(C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
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
C_save_and_reclaim((void*)trf_373,NULL,5,t0,t1,t2,t3,t4);}
t5=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t6=(*a=C_VECTOR_TYPE|1,a[1]=t3,tmp=(C_word)a,a+=2,tmp);
t7=(*a=C_VECTOR_TYPE|1,a[1]=t4,tmp=(C_word)a,a+=2,tmp);
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[9])[1]))){
t8=t1;
((C_proc2)(void*)(*((C_word*)t8+1)))(2,t8,C_SCHEME_FALSE);}
else{
t8=(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_383,a[2]=t7,a[3]=t6,a[4]=t5,a[5]=t1,a[6]=((C_word*)t0)[8],tmp=(C_word)a,a+=7,tmp);
t9=(*a=C_CLOSURE_TYPE|12,a[1]=(C_word)f_389,a[2]=((C_word*)t0)[2],a[3]=t7,a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[4],a[6]=((C_word*)t0)[5],a[7]=t6,a[8]=((C_word*)t0)[6],a[9]=t5,a[10]=((C_word*)t0)[9],a[11]=t8,a[12]=((C_word*)t0)[7],tmp=(C_word)a,a+=13,tmp);
t10=((C_word*)((C_word*)t0)[7])[1];
if(C_truep(t10)){
t11=t9;
f_389(2,t11,C_SCHEME_FALSE);}
else{
t11=(C_word)C_i_car(((C_word*)((C_word*)t0)[9])[1]);
C_trace("ChickenBridge.scm: 157  keyword?");
t12=C_retrieve(lf[34]);
((C_proc3)C_retrieve_proc(t12))(3,t12,t9,t11);}}}

/* k387 in do67 in k323 in k311 in k308 in k305 in expand-send in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_389(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_389,2,t0,t1);}
if(C_truep(t1)){
t2=C_set_block_item(((C_word*)t0)[12],0,C_SCHEME_TRUE);
t3=((C_word*)t0)[11];
f_383(t3,t2);}
else{
t2=((C_word*)((C_word*)t0)[12])[1];
if(C_truep(t2)){
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[10])[1]);
t4=C_mutate(((C_word *)((C_word*)t0)[9])+1,t3);
t5=(C_word)C_i_assoc(((C_word*)((C_word*)t0)[9])[1],((C_word*)t0)[8]);
t6=C_mutate(((C_word *)((C_word*)t0)[7])+1,t5);
t7=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[10])[1]);
t8=C_mutate(((C_word *)((C_word*)t0)[10])+1,t7);
t9=(*a=C_CLOSURE_TYPE|8,a[1]=(C_word)f_443,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[9],a[4]=((C_word*)t0)[5],a[5]=((C_word*)t0)[11],a[6]=((C_word*)t0)[10],a[7]=((C_word*)t0)[6],a[8]=((C_word*)t0)[7],tmp=(C_word)a,a+=9,tmp);
t10=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_498,a[2]=((C_word*)t0)[8],a[3]=((C_word*)t0)[7],a[4]=((C_word*)t0)[9],a[5]=((C_word*)t0)[5],a[6]=t9,a[7]=((C_word*)t0)[10],tmp=(C_word)a,a+=8,tmp);
C_trace("ChickenBridge.scm: 177  keyword?");
t11=C_retrieve(lf[34]);
((C_proc3)C_retrieve_proc(t11))(3,t11,t10,((C_word*)((C_word*)t0)[9])[1]);}
else{
t3=(*a=C_CLOSURE_TYPE|5,a[1]=(C_word)f_399,a[2]=((C_word*)t0)[11],a[3]=((C_word*)t0)[10],a[4]=((C_word*)t0)[3],a[5]=((C_word*)t0)[6],tmp=(C_word)a,a+=6,tmp);
if(C_truep((C_word)C_i_nequalp(((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]))){
t4=(C_word)C_i_length(((C_word*)t0)[4]);
C_trace("ChickenBridge.scm: 167  ferror");
f_293(t3,lf[35],(C_word)C_a_i_list(&a,3,((C_word*)t0)[5],((C_word*)t0)[2],t4));}
else{
t4=t3;
f_399(2,t4,C_SCHEME_UNDEFINED);}}}}

/* k397 in k387 in do67 in k323 in k311 in k308 in k305 in expand-send in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_399(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_399,2,t0,t1);}
t2=(C_word)C_i_list_tail(((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]);
t3=(C_word)C_i_car(((C_word*)((C_word*)t0)[3])[1]);
t4=(C_word)C_i_set_car(t2,t3);
t5=(C_word)C_i_cdr(((C_word*)((C_word*)t0)[3])[1]);
t6=C_mutate(((C_word *)((C_word*)t0)[3])+1,t5);
t7=(C_word)C_a_i_plus(&a,2,((C_word*)((C_word*)t0)[4])[1],C_fix(1));
t8=C_mutate(((C_word *)((C_word*)t0)[4])+1,t7);
t9=((C_word*)t0)[2];
f_383(t9,t8);}

/* k496 in k387 in do67 in k323 in k311 in k308 in k305 in expand-send in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_498(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[17],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_498,2,t0,t1);}
if(C_truep(t1)){
if(C_truep((C_word)C_i_nullp(((C_word*)((C_word*)t0)[7])[1]))){
C_trace("ChickenBridge.scm: 181  ferror");
f_293(((C_word*)t0)[6],lf[29],(C_word)C_a_i_list(&a,2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]));}
else{
t2=((C_word*)((C_word*)t0)[3])[1];
if(C_truep(t2)){
t3=((C_word*)t0)[6];
f_443(2,t3,C_SCHEME_UNDEFINED);}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_494,a[2]=((C_word*)t0)[4],a[3]=((C_word*)t0)[5],a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
C_trace("map");
t4=*((C_word*)lf[31]+1);
((C_proc4)(void*)(*((C_word*)t4+1)))(4,t4,t3,*((C_word*)lf[32]+1),((C_word*)t0)[2]);}}}
else{
C_trace("ChickenBridge.scm: 178  ferror");
f_293(((C_word*)t0)[6],lf[33],(C_word)C_a_i_list(&a,2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1]));}}

/* k492 in k496 in k387 in do67 in k323 in k311 in k308 in k305 in expand-send in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_494(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_494,2,t0,t1);}
C_trace("ChickenBridge.scm: 184  ferror");
f_293(((C_word*)t0)[4],lf[30],(C_word)C_a_i_list(&a,3,((C_word*)t0)[3],((C_word*)((C_word*)t0)[2])[1],t1));}

/* k441 in k387 in do67 in k323 in k311 in k308 in k305 in expand-send in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_443(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[14],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_443,2,t0,t1);}
t2=(C_word)C_i_member(((C_word*)((C_word*)t0)[8])[1],((C_word*)t0)[7]);
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_449,a[2]=((C_word*)t0)[5],a[3]=t2,a[4]=((C_word*)t0)[6],tmp=(C_word)a,a+=5,tmp);
if(C_truep(t2)){
t4=t3;
f_449(2,t4,C_SCHEME_UNDEFINED);}
else{
C_trace("ChickenBridge.scm: 191  ferror");
f_293(t3,lf[28],(C_word)C_a_i_list(&a,3,((C_word*)t0)[4],((C_word*)((C_word*)t0)[3])[1],((C_word*)t0)[2]));}}

/* k447 in k441 in k387 in do67 in k323 in k311 in k308 in k305 in expand-send in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_449(C_word c,C_word t0,C_word t1){
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
f_383(t6,t5);}

/* k381 in do67 in k323 in k311 in k308 in k305 in expand-send in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_fcall f_383(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)((C_word*)t0)[6])[1];
f_373(t2,((C_word*)t0)[5],((C_word*)((C_word*)t0)[4])[1],((C_word*)((C_word*)t0)[3])[1],((C_word*)((C_word*)t0)[2])[1]);}

/* k326 in k323 in k311 in k308 in k305 in expand-send in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_328(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_328,2,t0,t1);}
t2=C_SCHEME_UNDEFINED;
t3=(*a=C_VECTOR_TYPE|1,a[1]=t2,tmp=(C_word)a,a+=2,tmp);
t4=C_set_block_item(t3,0,(*a=C_CLOSURE_TYPE|6,a[1]=(C_word)f_333,a[2]=((C_word*)t0)[3],a[3]=t3,a[4]=((C_word*)t0)[4],a[5]=((C_word*)t0)[5],a[6]=lf[27],tmp=(C_word)a,a+=7,tmp));
t5=((C_word*)t3)[1];
f_333(t5,((C_word*)t0)[2],((C_word*)t0)[4]);}

/* do84 in k326 in k323 in k311 in k308 in k305 in expand-send in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_fcall f_333(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[8],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_333,NULL,3,t0,t1,t2);}
if(C_truep((C_word)C_i_nullp(t2))){
t3=t1;
((C_proc2)(void*)(*((C_word*)t3+1)))(2,t3,(C_word)C_a_i_cons(&a,2,((C_word*)t0)[5],((C_word*)t0)[4]));}
else{
t3=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_346,a[2]=t1,a[3]=((C_word*)t0)[3],a[4]=t2,tmp=(C_word)a,a+=5,tmp);
t4=(C_word)C_i_car(t2);
if(C_truep((C_word)C_i_member(t4,((C_word*)t0)[2]))){
t5=(C_word)C_i_car(t2);
t6=(C_word)C_i_cadr(t5);
t7=t3;
f_346(t7,(C_word)C_i_set_car(t2,t6));}
else{
t5=t3;
f_346(t5,C_SCHEME_UNDEFINED);}}}

/* k344 in do84 in k326 in k323 in k311 in k308 in k305 in expand-send in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_fcall f_346(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
t2=(C_word)C_i_cdr(((C_word*)t0)[4]);
t3=((C_word*)((C_word*)t0)[3])[1];
f_333(t3,((C_word*)t0)[2],t2);}

/* ferror in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_fcall f_293(C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)trf_293,NULL,3,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_301,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_apply(5,0,t4,C_retrieve(lf[24]),t2,t3);}

/* k299 in ferror in k289 in k286 in k187 in k184 in k181 in k178 */
static void C_ccall f_301(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("ChickenBridge.scm: 134  error");
t2=*((C_word*)lf[23]+1);
((C_proc3)C_retrieve_proc(t2))(3,t2,((C_word*)t0)[2],t1);}

/* make-note-off in k187 in k184 in k181 in k178 */
static void C_ccall f_280(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word *a;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_280,5,t0,t1,t2,t3,t4);}
C_trace("ChickenBridge.scm: 85   insert-midi-on");
t5=C_retrieve(lf[16]);
((C_proc6)C_retrieve_proc(t5))(6,t5,t1,t2,t3,lf[19],t4);}

/* make-note-on in k187 in k184 in k181 in k178 */
static void C_ccall f_274(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5){
C_word tmp;
C_word t6;
C_word *a;
if(c!=6) C_bad_argc_2(c,6,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr6,(void*)f_274,6,t0,t1,t2,t3,t4,t5);}
C_trace("ChickenBridge.scm: 81   insert-midi-on");
t6=C_retrieve(lf[16]);
((C_proc6)C_retrieve_proc(t6))(6,t6,t1,t2,t3,t4,t5);}

/* insert-midi-note in k187 in k184 in k181 in k178 */
static void C_ccall f_245(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4,C_word t5,C_word t6){
C_word tmp;
C_word t7;
C_word t8;
C_word ab[8],*a=ab;
if(c!=7) C_bad_argc_2(c,7,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr7,(void*)f_245,7,t0,t1,t2,t3,t4,t5,t6);}
t7=(*a=C_CLOSURE_TYPE|7,a[1]=(C_word)f_249,a[2]=t1,a[3]=t6,a[4]=t5,a[5]=t4,a[6]=t3,a[7]=t2,tmp=(C_word)a,a+=8,tmp);
C_trace("##sys#gc");
t8=C_retrieve(lf[7]);
((C_proc3)C_retrieve_proc(t8))(3,t8,t7,C_SCHEME_FALSE);}

/* k247 in insert-midi-note in k187 in k184 in k181 in k178 */
static void C_ccall f_249(C_word c,C_word t0,C_word t1){
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
C_save_and_reclaim((void*)tr2,(void*)f_249,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[7]);
t4=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[6]);
t5=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[5]);
t6=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[4]);
t7=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[3]);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub33,a[2]=lf[13],tmp=(C_word)a,a+=3,tmp);
((C_proc8)C_retrieve_proc(t8))(8,t8,((C_word*)t0)[2],t2,t3,t4,t5,t6,t7);}

/* insert-closure in k187 in k184 in k181 in k178 */
static void C_ccall f_232(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_232,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_236,a[2]=t3,a[3]=t1,a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("##sys#gc");
t5=C_retrieve(lf[7]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,C_SCHEME_FALSE);}

/* k234 in insert-closure in k187 in k184 in k181 in k178 */
static void C_ccall f_236(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_236,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[4]);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub22,a[2]=lf[10],tmp=(C_word)a,a+=3,tmp);
((C_proc5)C_retrieve_proc(t4))(5,t4,((C_word*)t0)[3],t2,t3,((C_word*)t0)[2]);}

/* insert-process in k187 in k184 in k181 in k178 */
static void C_ccall f_219(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_219,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_223,a[2]=t3,a[3]=t1,a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("##sys#gc");
t5=C_retrieve(lf[7]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t4,C_SCHEME_FALSE);}

/* k221 in insert-process in k187 in k184 in k181 in k178 */
static void C_ccall f_223(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[11],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_223,2,t0,t1);}
t2=(C_word)C_a_i_bytevector(&a,1,C_fix(6));
t3=(C_word)C_i_foreign_flonum_argumentp(((C_word*)t0)[4]);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)stub14,a[2]=lf[6],tmp=(C_word)a,a+=3,tmp);
((C_proc5)C_retrieve_proc(t4))(5,t4,((C_word*)t0)[3],t2,t3,((C_word*)t0)[2]);}

/* print-error in k187 in k184 in k181 in k178 */
static void C_ccall f_205(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_205,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_210,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[1]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_210(2,t4,C_SCHEME_FALSE);}}

/* k208 in print-error in k187 in k184 in k181 in k178 */
static void C_ccall f_210(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub7(C_SCHEME_UNDEFINED,t1));}

/* print-message in k187 in k184 in k181 in k178 */
static void C_ccall f_191(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word ab[3],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_191,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_196,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
if(C_truep(t2)){
t4=(C_word)C_i_foreign_string_argumentp(t2);
C_trace("##sys#make-c-string");
t5=C_retrieve(lf[1]);
((C_proc3)C_retrieve_proc(t5))(3,t5,t3,t4);}
else{
t4=t3;
f_196(2,t4,C_SCHEME_FALSE);}}

/* k194 in print-message in k187 in k184 in k181 in k178 */
static void C_ccall f_196(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_word)stub1(C_SCHEME_UNDEFINED,t1));}

#ifdef C_ENABLE_PTABLES
static C_PTABLE_ENTRY ptable[83] = {
{"toplevelChickenBridge.scm",(void*)C_grace_toplevel},
{"f_180ChickenBridge.scm",(void*)f_180},
{"f_183ChickenBridge.scm",(void*)f_183},
{"f_186ChickenBridge.scm",(void*)f_186},
{"f_189ChickenBridge.scm",(void*)f_189},
{"f_288ChickenBridge.scm",(void*)f_288},
{"f_905ChickenBridge.scm",(void*)f_905},
{"f_952ChickenBridge.scm",(void*)f_952},
{"f_942ChickenBridge.scm",(void*)f_942},
{"f_909ChickenBridge.scm",(void*)f_909},
{"f_291ChickenBridge.scm",(void*)f_291},
{"f_899ChickenBridge.scm",(void*)f_899},
{"f_530ChickenBridge.scm",(void*)f_530},
{"f_581ChickenBridge.scm",(void*)f_581},
{"f_584ChickenBridge.scm",(void*)f_584},
{"f_587ChickenBridge.scm",(void*)f_587},
{"f_590ChickenBridge.scm",(void*)f_590},
{"f_593ChickenBridge.scm",(void*)f_593},
{"f_596ChickenBridge.scm",(void*)f_596},
{"f_599ChickenBridge.scm",(void*)f_599},
{"f_602ChickenBridge.scm",(void*)f_602},
{"f_893ChickenBridge.scm",(void*)f_893},
{"f_605ChickenBridge.scm",(void*)f_605},
{"f_891ChickenBridge.scm",(void*)f_891},
{"f_607ChickenBridge.scm",(void*)f_607},
{"f_620ChickenBridge.scm",(void*)f_620},
{"f_623ChickenBridge.scm",(void*)f_623},
{"f_728ChickenBridge.scm",(void*)f_728},
{"f_836ChickenBridge.scm",(void*)f_836},
{"f_748ChickenBridge.scm",(void*)f_748},
{"f_757ChickenBridge.scm",(void*)f_757},
{"f_761ChickenBridge.scm",(void*)f_761},
{"f_765ChickenBridge.scm",(void*)f_765},
{"f_773ChickenBridge.scm",(void*)f_773},
{"f_769ChickenBridge.scm",(void*)f_769},
{"f_738ChickenBridge.scm",(void*)f_738},
{"f_626ChickenBridge.scm",(void*)f_626},
{"f_629ChickenBridge.scm",(void*)f_629},
{"f_632ChickenBridge.scm",(void*)f_632},
{"f_635ChickenBridge.scm",(void*)f_635},
{"f_690ChickenBridge.scm",(void*)f_690},
{"f_678ChickenBridge.scm",(void*)f_678},
{"f_674ChickenBridge.scm",(void*)f_674},
{"f_574ChickenBridge.scm",(void*)f_574},
{"f_568ChickenBridge.scm",(void*)f_568},
{"f_562ChickenBridge.scm",(void*)f_562},
{"f_556ChickenBridge.scm",(void*)f_556},
{"f_550ChickenBridge.scm",(void*)f_550},
{"f_544ChickenBridge.scm",(void*)f_544},
{"f_538ChickenBridge.scm",(void*)f_538},
{"f_532ChickenBridge.scm",(void*)f_532},
{"f_303ChickenBridge.scm",(void*)f_303},
{"f_307ChickenBridge.scm",(void*)f_307},
{"f_520ChickenBridge.scm",(void*)f_520},
{"f_310ChickenBridge.scm",(void*)f_310},
{"f_313ChickenBridge.scm",(void*)f_313},
{"f_325ChickenBridge.scm",(void*)f_325},
{"f_373ChickenBridge.scm",(void*)f_373},
{"f_389ChickenBridge.scm",(void*)f_389},
{"f_399ChickenBridge.scm",(void*)f_399},
{"f_498ChickenBridge.scm",(void*)f_498},
{"f_494ChickenBridge.scm",(void*)f_494},
{"f_443ChickenBridge.scm",(void*)f_443},
{"f_449ChickenBridge.scm",(void*)f_449},
{"f_383ChickenBridge.scm",(void*)f_383},
{"f_328ChickenBridge.scm",(void*)f_328},
{"f_333ChickenBridge.scm",(void*)f_333},
{"f_346ChickenBridge.scm",(void*)f_346},
{"f_293ChickenBridge.scm",(void*)f_293},
{"f_301ChickenBridge.scm",(void*)f_301},
{"f_280ChickenBridge.scm",(void*)f_280},
{"f_274ChickenBridge.scm",(void*)f_274},
{"f_245ChickenBridge.scm",(void*)f_245},
{"f_249ChickenBridge.scm",(void*)f_249},
{"f_232ChickenBridge.scm",(void*)f_232},
{"f_236ChickenBridge.scm",(void*)f_236},
{"f_219ChickenBridge.scm",(void*)f_219},
{"f_223ChickenBridge.scm",(void*)f_223},
{"f_205ChickenBridge.scm",(void*)f_205},
{"f_210ChickenBridge.scm",(void*)f_210},
{"f_191ChickenBridge.scm",(void*)f_191},
{"f_196ChickenBridge.scm",(void*)f_196},
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
