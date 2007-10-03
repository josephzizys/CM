
#>
#include "Grace.h"
#include "Scheme.h"

void print_mess(char * st)
{
  ((GraceApp *)GraceApp::getInstance())->getConsole()->printMessage( String(st));
}

void print_error(char * st)
{
  ((GraceApp *)GraceApp::getInstance())->getConsole()->printError( String(st));
}

 
<#

(declare
 (unit grace)
 (export print-message print-error ))

(define print-message
  (foreign-lambda void "print_mess" c-string))

(define print-error
  (foreign-lambda void "print_error" c-string))

(return-to-host)

;;csc -c++ -embedded -t ChickenBridge.scm
