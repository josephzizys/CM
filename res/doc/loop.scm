;
;; Iteration
;

; here is one way execute a statement five times:

(begin (display "a random keynum: ") (display (random 128)) (newline)
       (display "a random keynum: ") (display (random 128)) (newline)
       (display "a random keynum: ") (display (random 128)) (newline)
       (display "a random keynum: ") (display (random 128)) (newline)
       (display "a random keynum: ") (display (random 128)) (newline))

; Here is a much better way of accomplishing the same thing!

(loop repeat 5 do
      (display "a random keynum: ") (display (random 128)) (newline))

; note that with a loop you can double the amount of work done without
; adding any additional code:

(loop repeat 10 do
      (display "a random keynum: ") (display (random 128)) (newline))

; The 'loop' statement performs iteration: it repeatedly executes an
; action statement some number of times. The simplest way to tell a
; loop how many times to iterate is to use its 'repeat' clause. the
; repeat value can a number or any sexpr that evaluates to a number:

(loop repeat (random 10) do
      (display "a random keynum: ") (display (random 128)) (newline))
  

; loop's 'do' tag makes it an implicit block so you can execute more
; than one action statement

(loop repeat 4 do
      (display "a random keynum: ") (display (random 128)) (newline)
      (display "approximately one beat: ") (display (vary 1 0.5)) (newline)
      (display "a random dead composer: ") (display (pick '(bach schoenberg berg mozart))) (newline)
      (display "----------------------------") (newline))


; the loop's action can be any SCM statement:

(loop with foo = '()
      repeat 4
      do
      (set! foo (append foo (list (random 128))))
      finally (display foo)) 

(loop repeat 4
      collect (random 128)) ; better ???

; the 'finally' clause lets you associate an single action with the
; END of the iteration. if given, the finally statement is executed
; one time only, immediately after the iteration has stopped. note
; that a finally clause will execute even if no iteration occurs!:

(loop repeat 0 do
      (display "a random keynum: ") (display (random 128)) (newline)
      finally (display "All done!"))

; Use a (begin ...) OR (let ...) block if you want
; to execute more than one finally statement:

(loop for x = (random 128)
      with foo = '() and tot = 0
      repeat 10
      do
      (set! foo (append foo (list x)))
      (set! tot (+ tot x))
      finally (let ((avr (/ tot 10.0)))
                (display "keys: ") (display foo) (newline)
                (display "average: ") (display avr) (newline)
                (display "All done!\n")))

;
;; Stepping statements
; 

; You can specify any number of 'for' clauses that increment stepping
; variables each time through the loop.  All stepping clauses must
; appear before the action statement. In this example the stepping
; variable i is set to a new random key number each time through the
; loop

; general stepping:  'for <var> = <sexpr>' ...

(loop repeat 10
      for i = (random 128)
      do
      (display "a random major chord: ")
      (display i) (display " ")
      (display (+ i 4)) (display " ")
      (display (+ i 7)) (newline)
      finally (display "All done!\n"))
               
; You can have any number of 'for statements'. This example uses three
; stepping variables: key rhy and amp. Notice that the amp's 'then'
; clause causes it to be randomly chosen only on the FIRST iteration
; and then incremented by .05 each time after that.

(loop repeat 10
      for key = (random 128)
      for rhy = (pick 1/4 1/2 3/4 1)
      for amp = (pick .1 .3 .5) then (+ amp 0.05)
      do
      (display "key=") (display key) (display " ")
      (display "amp=") (display amp) (display " ")
      (display "rhy=") (display rhy) (newline))


; The value of one 'for <var> = ...' variable can depend on
; another. in this example we declare the stepping variable key to
; hold a random keynum and 'maj' to hold a list representing a major
; chord built on whatever keynum was chosen

(loop repeat 10
      for key = (random 128)
      for maj = (list key (+ key 4) (+ key 7))
      do
      (display "a random major chord: ") (display maj) (newline)
      finally (display "All done!\n"))

; TODO: change the preceding loop to include printing random minor,
; diminished and augmented chords. rememeber that you need to use a
; begin ... end block for more than one action!

;
;; List stepping: 'for <var> in <list>'
;

; you can step a variable over a list of elements using the 'in'
; clause. the iteration stops once all the elements in the list have
; been accessed

(loop for c in '(a b c d e f g)
      do
      (display c) (newline))

(loop for c in '(bach beethoven mozart berg webern schoenberg)
      for q = (pick '(great fantastic wonderful))
      do
      (display c) (display " is a ") (display q) (display " composer.\n"))

;
;; Numerical stepping: 'for <var> from <num> to <num> by <num> ...'
; 

; Numerical stepping clauses automatically increment stepping
; variables by counting. both the starting and stopping bounds for the
; counting can be provided

; Use 'from' to specify the starting value. if 'from' value is not
; provided the variable starts at 0.  the stopping value is specified
; using one of: 'to', 'below', 'downto', 'above'.  

; The 'to' and 'downto' boundary stops iteration just after the
; variable reaches the value

(loop for x from 1 to 10
      do
      (display "x=") (display x) (newline))

(loop for x from 10 downto 1
      do
      (display "x=") (display x) (newline))

; If you omit the 'from' it defaults to 0

(loop for x to 10
      do
      (display "x=") (display x) (newline))
  
; The 'by' clause lets you specify the increment value for the variable

(loop for x from 0 to 20 by 2
      for y from 100 downto 10 by 10
      do
      (display "x=") (display x) (display " y=") (display y)(newline))

; You can increment by floating point values too

(loop for x from 2.5 to 8 by .1
      do
      (display "x=") (display x) (newline))

; The 'below' and 'above' boundaries stop iteration just before the
; variable reaches the value

(loop for x below 10
      do
      (display "x=") (display x) (newline))

(loop for x from 10 above 0
      do
      (display "x=") (display x) (newline))

; If more than one stepping clause is provided the loop stops after
; shortest path is reached

(loop for x from 0 to 1000 by 10
      for y to 10 by pi
      do
      (display "x=") (display x) (display " y=") (display y)(newline))

; You can also specify a numerical iteration without a stepping
; boundary. but some clause better stop the iteration or it will run
; forever!

(loop repeat 10
      for x from 0 by 10
      for y from 0
      for e = (expt y x)
      do
      (display "e=") (display e) (newline))

;
;; Accumulating results
;

; One of the most useful things you can with loop is to accumulate
; results in local variables you declare using the 'with' clause. One
; important point: be sure to initialize your variables when you
; declare them to a starting value appropriate for the
; accumulation. For example, if you want to collect values into a
; list, initialize the list to the empty list {} when you declare
; it. If you want to incrementally sum or scale stepping values then
; initialize the local variable to 0 or 1 respectively. If you want to
; minimize values, initialize the minimum to a value larger than any
; minimum value you will iterate and do the opposite when you use
; maximize.

; This example collect all the values of a stepping variable into a
; local variable. the variable is initialized to the empty list when
; it is declared. the set operator &= appends elements to a list.

(loop with res = '()
      for i from 1 to 10
      do
      (set! res (append res (list i)))
      finally (display res))

(loop for i from 1 to 10
      collect i)

; Reverse collect all the value of a stepping variable into a list:

(loop with res = '()
      for i from 1 to 10
      do
      (set! res (cons i res))
      finally (display res))

(reverse (loop for i from 1 to 10
               collect i))

; Sum all the values of a stepping variable into a local variable. The
; local variable is initialized to 0 when it is declared. Recall that
; the (set! res (+ res i)) expression increments the variable
; by a value.

(loop with res = 0
      for i from 1 to 10
      do
      (set! res (+ res i))
      finally (display res))

(loop for i from 1 to 10
      sum i)

; Multiply all the values of a stepping variable into a local
; variable. The local variable is initialized to 1 when it is
; declared. Recall that the set operator *= scales a variable by a
; value.

(loop with res = 1
      for i from 1 to 10
      do
      (set! res (* res i))
      finally (display res))

(apply * (loop for i from 1 to 10
                     collect i))

; This loop both sums and collects random key numbers. It then prints
; the results, along with the average value found:

(loop with tot = 0.0 and res = '()
      repeat 10
      for j = (random 128)
      do
      (set! tot (+ tot j))
      (set! res (append res (list j)))
      finally (begin (display "res=") (display res)
                     (display " avr=") (display (/ tot (length res))) (newline)))

(let ((res (loop repeat 10
                 for j = (random 128)
                 collect j)))
  (begin (display "res=") (display res)
         (display " avr=") (display (/ (apply + res) (length res))) (newline)))

(make-list 10 random 128)

; This example minimizes random values. The variable is initially set
; to a value greater than any possible values we will minimize:

(loop with val = 129
      repeat 10
      for rnd = (random 128)
      do
      (set! val (if (<= val rnd) val rnd))
      finally (begin (display "minimum random value: ")
                     (display val) (newline)))

(loop repeat 10
      for rnd = (random 128)
      minimize rnd)

; Do the opposite if you maximize:

(loop with val = -1
      repeat 10
      for rnd = (random 128)
      do
      (set! val (if (>= val rnd) val rnd))
      finally (begin (display "maximum random value: ")
                     (display val) (newline)))

(loop repeat 10
      for rnd = (random 128)
      maximize rnd)

;
;; Using loop inside functions
;

; Loop is really useful for designing all sorts of musical
; functions. The finally clause can be a 'return' statement to return
; the loop's result from the function!

; One very common type of function transforms an input list into an
; output list. The general form of these function is to decalare a new
; an empty list, then iterate over each element in the old list and
; use append command to append the transformed element
; onto the new list and finally returning the new list:

; Example: transpose a list of key numbers by a specified interval.

(define (list-transp old int)
  (loop with new = '()
        for k in old
        do
        (set! new (append new (list (+ k int))))
        finally (return new)))
(list-transp '(60 61 62 63) -12)

(define (list-transp2 old int)
  (map (lambda (x) (+ x int)) old))
(list-transp2 '(60 61 62 63) -12)
  

(define (makechords mel)
  (loop with res = '()
        for root in mel
        for third = (pick 3 4)
        for fifth = (pick 6 7 8)
        do
        (set! res (append res (list (list root (+ root third) (+ root fifth)))))
        finally (return res)))
(makechords '(60 62 63 65 67 68 70 72))

(define (makechords2 mel)
  (map (lambda (x) (list x 
                         (+ x (pick 3 4))
                         (+ x (pick 6 7 8)))) mel))
(makechords2 '(60 62 63 65 67 68 70 72))


;
;; Stopping iteration using while and until
;

; You can use 'while' or 'until' clauses to halt iteration based on a
; test of some condition. while stops iteration as soon as the
; condition is false. until stops iteration when the test is true:


; Iterate random numbers until a '9' is found:

(loop for x = (random 10)
      until (= x 9)
      do
      (display x) (newline)
      finally (display "all done!\n"))

; Collect 10 random keynumbers in pentatonic scale:

(loop with l = '()
      for x = (random 128)
      for p = (modulo x 12)
      until (= (length l) 10)
      when (member p '(1 3 6 8 10))
      do
      (set! l (append l (list x)))
      finally (display l))

(map (lambda (x) (+ x (* 12 (random 10))))
     (make-list 10 pick 1 3 6 8 10))



; Iterate random numbers until the same value is picked consecutively:

(loop with old = -1
      for new = (random 20)
      until (= old new)
      do
      (display "new=") (display new)
      (display " old=") (display old) (newline)
      (set! old new)
      finally (display "all done!\n"))