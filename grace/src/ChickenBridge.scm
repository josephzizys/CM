
#>
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


 
<#

(declare
 (unit grace)
 (uses extras)
 (export print-message print-error insert-process make-process
         now insert-closure insert-midi-note runran runproc))

(define print-message
  (foreign-lambda void "print_mess" c-string))

(define print-error
  (foreign-lambda void "print_error" c-string))

(define insert-process
  (foreign-lambda void "insert_process" double scheme-object))

(define insert-closure
  (foreign-lambda void "insert_closure" double scheme-object))

(define insert-midi-note
  (foreign-lambda void "insert_midi_note" double float float));

(define now
  (foreign-lambda* double ()
     " C_return(Time::getMillisecondCounterHiRes());"))


(define (make-process p num interval)
  (let ((t interval) (c 0))
    (lambda ()
      (apply p '())
      (set! c (+ c 1))
      (if (> c num)
          (set! t -1.0))
      t)))


(define (runran n d)
  (let ((r 0.0))
    (do ((i 0 (+ i 1)))
        ((> i n))
      (insert-midi-note r 60 100)
      (insert-midi-note (+ 200 r) 60  0)
      (set! r (+ r d)))))

(define (runproc k n d)
  (let ((proc (make-process
               (lambda ()
                 (insert-midi-note 0.0 k 100)
                 (insert-midi-note 90.0 k 0))
               n d)))
    (insert-process 0.0 proc)))

 

(return-to-host)

;;csc -c++ -embedded -t ChickenBridge.scm
