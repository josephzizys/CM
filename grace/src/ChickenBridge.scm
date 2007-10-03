
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
 printf("length of node before %i, ", ((GraceApp *)GraceApp::getInstance())->queue->nodes.size());
  ((GraceApp *)GraceApp::getInstance())->queue->addNode(1, time, 0, 0, proc);
   printf("length of node after %i, ", ((GraceApp *)GraceApp::getInstance())->queue->nodes.size());
}
 
<#

(declare
 (unit grace)
 (export print-message print-error G_apply_process  insert-process now insert-midi-note runran runproc))

(define print-message
  (foreign-lambda void "print_mess" c-string))

(define print-error
  (foreign-lambda void "print_error" c-string))

(define insert-process
  (foreign-lambda void "insert_process" double scheme-object))

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
  (insert-process 0.0
                  (make-process
                   (lambda ()
                     (insert-midi-note 0.0 k 100)
                     (insert-midi-note 200.0 k 0))
                   n d)))



;;(define (runproc n d)
 ;; (insert-process 0.0 (lambda () 0.0)))

 
(define-external (G_apply_process (scheme-object closure)) double
  (apply closure '()))



(return-to-host)

;;csc -c++ -embedded -t ChickenBridge.scm
