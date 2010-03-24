;;; -*- syntax: Lisp; font-size: 16; theme: "Emacs" -*-

; A Lisp program consists of comments and expressions.  Comments start
; with a semi-colon and last until the end of the line. You are
; reading a block of comments.  An expression is something you execute
; to produce a result. To execute an expression place your cursor at
; the end of the line and press Command-enter. (On Windows and Linux
; the Control key is the Command key.)  Look in the Console window to
; see the result.

123

; Operators MUST be delimited by spaces in math expressions:

(+ 1 (* 2 3))

; You can use parentheses to group and nest terms as you like.

(* (+ 1 2) 3)

; Function calls look like this:

(print "Hello, world!")

; You can nest function calls and function arguments are separated by
; commas. Execute this command several times to see what it does:

(print "My key number: " (between 60 90))

; Errors: when you execute somethin that contains a mistake you will
; see an error message printed in the Console window. Sometimes this
; message is helpful, sometimes its not so useful. Such is life.  Many
; mistakes involve syntax errors or undefined terms as shown in these
; two examples:

(+ 1 (* 2 3)))

(print foo)

; Expressions can become quite complex and often span more than one
; line.  Here is an example of a moderately complex expression. To
; execute it, place your cursor just after the last ')' and press
; COMMAND-Enter to see what it does.

(let* ((root (between 60 90))
       (third (+ root (pick 3 4)))
       (fifth (+ root 7)))
  (print "My random chord: " (note (list root third fifth))))


