; A SCM program consists of comments, commands and expressions.
; Comments start with a semi-colon last until the end of the line. You
; are reading a comment block. A command is something that you
; execute to accomplish a task. To execute a command place
; your cursor at the end
; of the command line and press COMMAND-Enter. (On the Mac the COMMAND
; key is the APPLE key, on Windows and Linux it's the CONTROL key.)
; Look in the Console window to see the results of executing the
; command.

"Hello, world!"

(display "Hello, world!\n")

; Expressions are things that get evaluated when you execute a
; command.  Many expressions involve math:

(+ 1 (* 2 3))

; You can use parentheses to group and nest terms as you like.

(* (+ 1 2) 3)

; ...

(begin (display "my key number: ") (between 60 90))

; You can read help about commands and functions by placing your
; cursor on the word you want to look up and pressing COMMAND-D. Try
; this on the symbols 'display' and 'between' in the previous example.

; Errors: when you execute somethin that contains a mistake you will
; see an error message printed in the Console window. Sometimes this
; message is helpful, sometimes its not so useful. Such is life.  Many
; mistakes involve syntax errors or undefined terms as shown in these
; two examples:

(+ 1 (* 2 3)))

(display foo)

; Commands and expressions can become quite complex and often span
; more than one line.  Here is an example of a moderately complex
; command. To execute it, place your cursor just after the last ')'
; and press COMMAND-Enter to see what it does.

(let* ((root (between 60 90))
       (third (+ root (pick 3 4)))
       (fifth (+ root 7)))
  (display "My random chord: ")
  (display (note (list root third fifth)))
  (newline))