;
;; Defining Variables
; 

; A variable is a symbol that stands for a value. There are two types
; of variables: global variables are variables that you create using
; the define command; local variables are variables that you declare
; inside (let) or (let*) blocks or using a 'with' or 'for' statement
; in code blocks like 'loop'. More about local variables in just a
; bit...

;
;; Global variables
;

; A global variable is a variable that you define so that all your
; code can reference it. For example, if you were working on a
; twelve-tone composition you might want to create a global variable
; to hold the row on which the composition is based. That way all the
; code you develop could access that row by referencing global
; variable its stored int

; Use the (define) command to define global variables. Here
; is the definition of a global variable that holds a twelve-tone
; row. Put your cursor at the end of the line and press COMMAND-Enter
; to execute the definition:

(define row '(0 11 1 10 2 9 3 8 4 7 5 6))

(print "Prime row: "  row ", retrograde row: " 
       (reverse row))

; The 'define' command takes the name of the new global
; variable, followed by an initialization value.  If
; you don't provide an initial 'value' for global variable it gives
; an error.  Other facts: the 'value' can be any SCM expr.
; In this next example we define two globals, the first
; holds a row type we randomly choose from four possible row types
; (using a string to represent the prime retrograde inversion and
; retrograde-inversion row forms) and the second global to hold a
; transposition offset:

(define row-form (pick "p" "r" "i" "ri"))
(define row-transp (between 0 12))
  
;
;; Local variables
;

; Sometimes a variable is needed only for a particular set of
; statements.  A local variable is a temporary variable that is only
; defined within a specific block of code.
; Here is an example of two local variables x and
; y. Place your cursor after last ')' and press COMMAND-Enter
; several times:

(let* ((x (random 12))
       (y (+ x 12)))
  (list x 2))

; Its clear from the display statement that when the block
; executes the variables x and y have values (or else the display
; statement wouldn't
; work!). But notice that if you try to evaluate either x or y OUTSIDE
; the block an error occurs because those variables don't exist
; outside the block in which they were (locally) declared. Executing
; this next statement will trigger an error message because there is
; no global variable called x (unless you created one yourself!)

x

; Notice that a variable declared inside an inner block will shadow
; the same variable declared in an outer block. In this example, both
; blocks declare a variable 'x' but the print statements clearly show
; that they are different variables!

(let ((x 1))
  (print "outer block, x=" x)
  (let ((x 2))
    (print "inner block, x=" x))
  (print "outer block, x=" x))
  
;
;; Variable assignment: the 'set' command
;

; What if want to assign a differnt value to an existing variable?
; For global variables, on solution might be to re-execute the define
; commands with a different inital value. Another way is to ASSIGN the
; variable a new value using the SET command.

(define row '(11 10 9 8 7 6 5 4 3 2 1 0))
(define row-form "p")
(define row-transp 0 )

(print "row=" row
       " row-form=" row-form
       " row-transp=" row-transp)

(set! row '(0 1 2 3 4 5 6 7 8 9 10 11))
(set! row-form "r")
(set! row-transp (between 6 12))

(print "row=" row
       " row-form=" row-form
       " row-transp=" row-transp)

; On first appearance the 'set!' command looks very much like the
; define command. But there are actually several
; important differences between define and set. First, and most
; importatly, set does not actualy CREATE variables, it simply sets an
; existing one to a new value. Secondly, the 'set!' command
; can be used with some other operators to manipulate the variable.

; Here is an example of some operators which can be used with set!
; in action. In each example
; the set is placed inside a loop that repeats the assingment 5 times
; so that you can se the effect. More about the loop statement in
; another tutorial!

; increment a variable by a value:

(let ((var 0))
  (loop repeat 5 do (set! var (+ var 1)))
  var)

; scale a variable by a value

(let ((var 1))
  (loop repeat 5 do (set! var (* var 10)))
  var)

; concat appends anything to the end of anything

(let ((var '()))
  (loop repeat 5 do
        (set! var (concat var (list 1 2 (random 128)))))
  var)

; concat can also be used to add a value to the front of a list

(let ((var '(9999)))
  (loop repeat 5 do
        (set! var (concat (random 128) var)))
  var)

; minimize a value

(let ((var 128))
  (loop repeat 5 do (set! var (min (random 128) var)))
  var)

; maximize a value

(let ((var 0))
  (loop repeat 5 do (set! var (max (random 128) var)))
  var)

;
;; Defining Functions
;

; Your compositional work will require you to design and implement new
; functions to accomplish musical tasks. We have already learned how
; to use them (by calling them with input values) but we don't know
; anything about how they are actually implemented.

; Recall that a function works by receiving arguments (input values)
; in its parameters, which are special variables in which it receives
; the data you pass it. The function then executes uses these
; parmeters its internal code (statements) that calculate a result
; that it returns back to you as the 'value' of the function call.
; The statements that the function executes are called the 'body' of
; the function: this is where the work happens. Any SCM statement can
; be used as the function's body. The last expression in the body
; is returned back to the caller. If the function
; requires more than one statement use a (let) statement as
; the function's body and then sequence as many statements as
; necessary inside the block. A (let) can also be used to
; declare local local variables inside the function, if needed.

;; Using 'define' command to define a function

; Use the 'define' command to create a new function. The
; command requires three pieces of information: (1) the name of the
; new function, (2) what input parameters it will take (if any) and
; (3) the SCM statement the function will execute when it is
; called. Here is a first example of a function definition. The
; function is called 'knum->pc' because it converts an input keynum
; 0-127 into a pitch class 0-11. The function declares one input
; parameter (knum) and the statement the function executes is the
; modulo statement. The last statement inside a function
; definition returns a value back to the caller. The pitch class that
; our function calculates and returns is simply mod 12 of the input
; keynum.

; Put the cursor at the end of the second line and press COMMAND-Enter
; to execute the definition:

(define (key->pc k)
  (modulo k 12))

(key->pc 60)

(key->pc 59)

; Note that although a function's body consists of only one statement,
; that statement can be a (let) block, which means that they
; can execute any number of statements.  Here is a (not very useful)
; function that executes two print statements when you call it.

(define (knum-info knum)
  (print "my key number is " knum
         ", my pitch class is " (key->pc knum)))
                                                   
(knum-info (random 128))

; ...

; This next little function demonstrates how to declare more than one
; parameter. It performs the opposite calculation of the first
; function: it returns a key givein a pc and a octave offset. The
; function declares two parameters: pc is the pitch class and octace is
; the keynum offset. 

(define (pc->key pc oct)
  (+ pc (* 12 (+ oct 1))))

; note that the function adds 1 to the octave so that the middle-c
; octave number 4 produces key number 60...

(pc->key 0 4)

; it is very common for functions to call other functions to do some of the work. here we define

(define (pc->note pc oct)
  (let ((k (pc->key pc oct)))
    (note k)))

(pc->note 0 4)

(pc->note 6 2)

(pc->note (random 12) (between 2 8))

;
;; Predicate functions and conditional statements
;

; A 'predicate' is a function that returns true or false based on a
; test of its argument(s). Predicates often use what are called
; 'conditional statements' to accomplish their tasks.  The (if)
; statement is the most flexble conditional: it consists of
; three parts: a test is first evaluated, if the test is true (not #f)
; then a statement is executed, otherwise an optional 
; statement is executed. Here is the definition of a predicate
; function that returns true if its input key number is a black key,
; otherwise it returns false. Notice that the 'true' value that the
; function returns is the pitch class of the black key rather than
; boolean true. Since boolean logic says that any value that is not #f
; must, by definition, be true, the true value can be anything that is
; not stricly #f!  This is qute handy and allows our function to
; return useful information (the pitch class) when the key in question
; is actually a black key:

(define (black-key? knum)
  (let ((pc (key->pc knum)))
    (if (member pc '(1 3 6 9 10)) pc #f)))

(black-key? 1)

(let ((k (random 128)))
  (print "key: " k ", black?: " (black-key? k)))
