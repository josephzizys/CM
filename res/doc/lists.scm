;
;; Working with lists
;

; A list holds data.  To create a list specify its elements inside '()
; or use the (list ) function. The following two commands create
; equivalent lists:

'(60 62 63 65 67)

(list 60 62 63 65 67)

; use the '() notation when you know the exact contents of the list.
; use the (list) function when some elements need to be calculated
; (evaluated) before being placed in the list. This example generates
; a variant three-element list each time its evaluated:

(list (random 100) (random 100) (random 100))

; empty lists are also possible:

'()

(list)

; lists can hold numbers, symbols, strings etc., even other lists!:

(define notes '(c d e f g a b))

notes

(define chords '((c e g) (d f a)))

chords

; 'length' tells you how many elemnts there are in a list:

(length notes)

(length chords)

; an empty list has zero elements:

(length '())

; 'append' concatenates input lists into a single list:

(append notes notes notes)

; append expects all its inputs to be proper lists. this next example
; produces an error because the second argument (60) is not a list:

(append notes 60 notes)

; this is correct:

(append notes '(60) notes)

; 'concat' will concatenate lists and non-lists together
; to form one large list

(concat -99 '(a b c) 60 70 '() '(x y z))

; 'first' ... 'tenth' returns the element at that position:

(first notes)

(third notes)

(seventh notes)

; you can nest calls to access sublist elements:

(third (second chords))

; 'nth' returns the element at the specified index. Note that the
; index is ZERO based, that is, the first element is at index 0, the
; last element in the list is at length()-1 index:

(nth notes 0)

(nth notes 1)

(nth notes (random 7))

(nth notes (- (length notes) 1))

; the 'reverse' function reverses the elements in a list (duh):

(reverse notes)

(define palin '(a     m a n   a   p l a n   p a n a m a))

(append palin (reverse palin))

; 'butlast' returns all but the last element

(butlast notes)

(append palin (reverse (butlast palin)))

; 'pick' randomly selects an element from a list:

(pick notes)

; 'shuffle' randomly scrambles the elements of a list:

(shuffle notes)
