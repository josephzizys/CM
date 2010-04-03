;
;; Expressions
;

; Scheme programs are built out of expressions.  An expression, or
; expr, is anything that produces a value. The most common types exprs
; you will work with are numbers, arithmetic expressions, booleans,
; strings, symbols (variables and function names) and lists.

;
;; Execution and Evaluation
;

; An expression becomes a value through a process called evaluation:
; every time you execute a command by pressing COMMAND-Enter you
; trigger evaluation. Simple expressions like numbers are called
; 'self-evaluating expressions' because they evaluate to themselves:
; 100 evaluates to 100. Most exprs are not self-evaluating, that is
; they produce values that are not identical to themselves: '1 + 2 *
; 3' evaluates to 7:

(+ 1 (* 2 3))

;
;; Numbers
;

; Numbers lies at the heart of music composition.  We will work with
; three different types of numbers as we design compositional
; algorithms: integers, floats and ratios.

;
;; Integers 
;

; Integers are whole numbers like 1, 2, 3, -6 and so on. Digits can be
; optionally preceded by a + or - sign. Integers are ubiquitous in
; computer composition, they are used as values, as counters, as
; enumerations of possible states an as index. An index is a special
; usage, it describes a position (location) where some data is stored
; in a list or array (vector). Indexes always start from zero, that
; is, the first element in the data is always index 0.

;; Musical integers: MIDI key numbers

; In terms of common musical integers you will encounter, MIDI
; represents note information as the integers 0 to 127. For example,
; 60 is C4 (Middle-C), 59 is B3, 72 is C5, 21 is the lowest A on the
; piano (A1) and 108 is the highest C on the piano (C8), and so on.
; We will be working with MIDI key number a great deal in this class,
; take the time to become familiar with them!

;
;; Floating point numbers
;

; Floating point numbers, or 'floats', are a way to represent real
; numbers.  Floats contain two parts: an integer portion (significand)
; is to the left of the dot and the fractional part (mantissa) is to
; the right of the dot:

123.456

; It is important to understand that floats can only approximate some
; real numbers.  For example .333 only approximates 1/3 to three
; places and 3.141592653589793 approximates pi to 15 places.  Realize
; that when you calculate with an approximation you introduce an error
; (however small) into your work.

;; Musical floats: floating point key numbers

; Recall that MIDI represents key numbers as integer values 0 < 128.
; Common Music extends MIDI's notion of key numbers to include
; floating point key numbers as well. A floating point keynum is
; interpreted as 'kkk.cc' where kkk is a MIDI keynum and cc is a CENT
; value above it. Since each semi tone has 100 cents, the float keynum
; 60.5 sounds one quarter tone above Middle C, the value 59.1 would
; sound 10 cents above B3 and so on. The smallest cent value humans
; can discriminate between is approximately 5 cents so two places is
; more than enough to represent microtonal adjustments.

;; Musical floats: amplitude

; We will also use floating point numbers 0.0 to 1.0 to represent
; amplitude values, where 0.0 is silence and 1.0 means "as loud as
; possible". The range of numbers 0.0 to 1.0 are sometimes referred to
; as 'normalized numbers' which means that they represent proportion
; and so have no scale, or size. This makes perfect sense for thinking
; about amplitude because the actual loudness of the sound will depend
; on environmental factors (computer output levels, stereo amplifier
; levels etc) more than the actual sound source. But you can still
; think of the values as absolute if you like: .1 = pppp, .5 = mp .7 =
; f and 1.0 = ffff for example.

;
;; Ratios
;

; A ratio is a quotient of two integers written n/d, where n is the
; numerator and d is the denominator. no spaces are allowed between
; the numbers or slash. A ratio is one way to represent a real number,
; i.e. a number that lies in between two integers. For example 5/3
; lies between the integers 1 and 2. Ratios are useful for expressing
; exact proportional relations such as 1/3

1/3

(* 2/7 17/9)

;
;; Arithmetic Expressions
;

; Arithmetic expressions consist of numbers joined together by math
; operators:

;  +   addition
;  -   subtraction
;  *   multiplication
;  /   division
;  modulo   modulus (remainder after division)
;  exptr   exponentiation

(+ (expt 10 2) 1)

(+ 1 (* 3 4))

(* (+ 1 3) 4)

(+ (* 2 3) (* 4 5))

(= 2 (+ 1 1))

(modulo 13 12)

; in this next example the first minus is subtraction, the second
; minus is part of a number:

(- 2 -1)

;
;; Mixed Expressions
;

; Since you will work with different types of numbers it is important
; to understand how they interact if they are combined in a single
; expression. If an expression contains only integer numbers and
; produces an results then the entire expression result in an integer:

(+ 10 1)

; If an expression contains or results in any floating point number
; the entire expression will produce a floating point value:

(* 10 0.5)

; It is sometimes necessary to convert one type of number into
; another. We will learn how to do this in the next chapter when we
; learn about the common math functions.

;
;; Arithmetic Relations
;

;  =   equal
;  !=  not equal
;  >   greater than
;  <   less than
;  >=  greater than or equal
;  <=  less than or equal
;  equal?  general equality (true if operands "look" the same)

; Relations evaluate to true (#t) or #f (false). See the section on
; Boolean values for more information about this.

(= 2 (+ 1 1))

(!= 2 1)

(< 2 (+ 1 1))

(<= 2 (+ 1 1))

(> 2 1)

(>= 2 1)

(equal? "Hi" "Hi")

(equal? "Hi" "Ho")

(equal? 1 1)

(equal? 1 1.0)

(equal? '(c e g) '(c e g))

;; relations are used to test an expression in order to do something.
;; for example, the 'if' statement uses relations to determine which
;; command it will execute

(if (= (random 3) 0)
  "winner!"
  "loser!")

; we will talk much more about 'if' and conditional evaluation in a
; later tutorial!

;
;; Symbols (variables and function names)
; 

; Symbols are words that name variables and functions (procedures).
; When a symbol appears as a variable in an expression the variable's
; value replaces the symbol's name when the expression is evaluated.
; For example we can define a symbol 'pi' to hold an approximation of
; the the number Pi.  This means that you can use the name 'pi' in a
; math expression rather than having to type the actual number

(* 2 pi)

(define 2pi (* 2 pi))

; More about defining variables later...

; You can access any ELEMENT in the list using the notation
; (list-ref xxx n) OR (nth xxx n) where xxx is the
; name of the variable and n is the element's position (zero based) in
; the list. for example:

(define var '(a b c d e f g))

(list-ref var 0)

(nth var 6)

(print "my random scale degree=" (list-ref var (random 7)))

;
;; Symbols as command and function names
;

; Commands and functions have symbol names too. For example the symbol
; 'display' is the name of the command that displays values,
; the symbol 'random' is the name of a function that 
; returns a random value each time it is evaluated:

(random 100)

;
;; Function calls
; 

; You can tell the difference between a symbol used as a function name
; and a symbol used as a variable name by the fact that function call
; symbols ALWAYS come after a '('. Input expressions passed to the
; function come after the function name. Parenthesis must 
; appear even if there are no inputs to the function:

(list)

(list 1)

; Use white space to separate inputs if there is more than one:

(list 1 2 3)

; Function calls can be nested to any level:

(list 1 (list 2 (list 3)) 4)

; Much more about this later...

; Notice that the symbol 'list' can be used as a function name as well
; as a variable. Be careful not to define a global variable with the
; same name as a function or that function's definition will be lost!

(print list)

;
;; Boolean Values: #t and #f
;

; A boolean value denotes truth or falsity. In SCM #t means true and
; #f means false:

(print #t)

(print #f)

; A 'boolean expression' is an expression that returns either true or
; false. For example all arithmetic relations are boolean expressions:

(= 1 2)

(< 1 2)

; Functions that return boolean values are called 'predicates'. For
; example, the functions 'even?' and 'odd?' return true or false based
; on a test of their inputs. Note that the names of almost all
; predicate functions end with '?' to mark them as functions that
; return true or false.

(odd? 1)

(odd? 2)

(even? 1)

(even? 2)

(string? "Hi Ho!")

;
;; Logical Expressions
;

; SCM provides three logical operators that can be used together to
; form boolean expressions:
;   and   logical AND 
;   or    logical OR
;   not   logical NOT

; Like arithmetic relations, the logical operators return true or
;  false based on a test of their arguments.

; The and operator (logical AND) is true only if BOTH its operands are
; true:

(and #t #t)

(and #t #f)

(and #f #t)

(and #f #f)

; of course, operands can be expressions:

(and (> 1 0) (< 1 2))

; the or operator (logical OR) is true if EITHER of its operands are
; true:

(or #t #t)

(or #t #f)

(or #f #t)

(or #f #f)

; the ! operator (logical NOT) is the boolean opposite of its operand:

(not #t)

(not #f)

(not (not #t))

; The logical operators can be combined with the arithmetic relations
; to test a series of expressions. Theses sorts of test expressions are
; called 'predicate tests' are most commonly found in th 'if'
; command. To see how this works, consider this next example that
; mimics rolling two dice. The "snake eyes" message only appears if
; both dice land on side 1. Put the cursor at the end of the last line
; and press Enter repeatedly.  You may have to execute the statement
; many times to get a snake eyes!

(if (and (= (random 6) 1) (= (random 6) 1))
  "snake eyes!"
  "loser >:(")

;
;; ...
;

(if (< 0 1) 100 #f)

(if (> 0 1) 100 #f)

(if (> 0 1) 100 (random 30))

;
;; Strings
; 

; Strings are text delimited by "".

"Hello, world!"

; Strings are not evaluated, that is, SCM does not look inside strings
; to evaluate what they contain. You can see this in the following
; examples:

(= 1 1)

"(= 1 1)"

(random 127)

"(random 127)"

;
;; Lists
;

; Lists are structures that can be used to group zero or more elements
; together. A list can hold anything, including other lists.
; none. Lists are written by delimiting the individual elements that
; make up the list within paranthesis '() or using the list command :

'(1 2 3 4 5)

(list 1 2 3 4 5)

; elements inside '() are NOT EVALUATED so symbols will not be treated
; as variables or function names when they are inside lists:

'(bach is a great composer)

; the empty list (a list of no elements) is a special case: 

'()

; When you define a list using paranthesis, every open bracket MUST be
; balanced by a corresponding right bracket: this is correct:

'(1 2 3 (4 5))

; this is an error:

'(1 2 3 (4 5)

; lists can hold any type of data, including other lists. This
; 'recursive' feature (lists inside lists) makes the list an extremely
; versatile structure: there is practically no limit to complexity of
; information that they can represent. What does this list represent?

'(("3-9*" (0 2 7) (0 1 0 0 2 0) "Quartal Trichord")
 ("3-10*" (0 3 6) (0 0 2 0 0 1) "Diminished Chord")
 ("F3-11" (0 3 7) (0 0 1 1 1 0) "Minor Chord")
 ("3-11B" (0 4 7) (0 0 1 1 1 0) "Major Chord"))

; if you want to evaluate an expression in an otherwise constant list
; of data can use the special ` marker instead of ' and
; the marker , just before the thing you want
; to evaluate:

`(1 2 ,(pick 3 33 333 3333) 4 5)

; you can 'splice in' a LIST of values using ,@

`(1 2 ,@(list (ran) (ran) (ran)))

;; Musical lists:  sequences

; Lists are the most natural way to represent musical 'sequences',
; that is, data to be performed in left-to-right order.

;;  here is a twelve tone row

'(0 8 3 2 11 10 1 7 9 4 6 5)

;; here is a non-retrogradable rhythm:

'(1 2 3/4 5/4 3/4 2 1)

;; here are three major chords:

'((60 64 65) (62 66 69) (64 68 71))

;
;; Note lists
;

; Perhaps the most common musical use of lists is to hold a series of
; notes or key numbers. We already know about integer and floating
; point key numbers. A note name is a letter: c d e f g a b plus an
; optional sharp or flat letters: s f n ss ff (Sharp Flat Natural
; double sharp, double flat plut an optional quarter-tone inflection
; sign (< >). plus an optional octave number -1 ... 10. Examples:

; c5    C in the 5th octave
; c>4   C plus 1 quarter tone in the 4th octave
; dn2   D natural in the 2nd octave
; eff4  E double flat in the fourth octave
; bf<0  Bf minus 1 quarter tone in the 0th octave.

; The 'note' and 'key' and 'hz' functions  convert one form into
; another. These functions can handle lists as well as individual
; notes and key numbers. For example here is another way of defining
; the list of chords shown in the last example but in 
; terms of keynumbers

(key '((c4 e g) (d4 fs a) (e4 gs b)))

(note 69)

(note (key 440))

; Note that octave numbers are sticky inside note lists, i.e. they
; only have to be written when they change:

(key '(c4 d ef f gs g3 a bf c ds5 e fs g))

(hz '(c4 d ef f gs g3 a bf c ds5 e fs g))




