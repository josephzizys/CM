(define-method* (make-byte-vector (int <integer>))
  (u8vector (ash (logand int #xff000000) -24) 
            (ash (logand int #xff0000) -16) 
            (ash (logand int #xff00) -8)
            (logand int #xff)))

; (make-byte-vector #x4030201)
; #(4 3 2 1)

(define-method* (make-byte-vector (flo <real>))
  (multiple-value-bind (significand exponent sign)
      (integer-decode-float flo)
    (make-byte-vector (dpb (if (< sign 0) 1 0)
                           (byte 1 31)
                           (dpb (+ (- exponent 1) 127) 
                                (byte 8 23)
                                significand)))))

; (define foo '(2353.4402 19497.84 1709.3262 1157.6047 786.9287 -8034.8916 -6878.1816 6363.0913 -10773.487 -16749.674))
; (loop for x in foo collect (make-byte-vector x))
; (#(57 19 23 11) #(58 152 83 174) #(56 213 170 112) #(56 144 179 90) #(56 68 187 112) #(185 251 23 34) #(185 214 241 116) #(57 198 216 187) #(186 40 85 243) #(186 130 219 89))

(define-method* (make-byte-vector (str <string>))
  (let* ((len (string-length str))
	 (pad (- 4 (modulo len 4)))
	 (vec (make-u8vector (+ len pad) 0)))
    (do ((i 0 (+ i 1)))
        ((= i len) vec)
      (u8vector-set! vec i (char->integer (string-ref str i))))))

; (make-byte-vector "Hello, world!")
;#(72 101 108 108 111 44 32 119 111 114 108 100 33 0 0 0)

(define-method* (make-byte-vector (sym <symbol>))
  (let ((str (string-downcase (symbol->string sym))))
    (make-byte-vector str)))

; (make-byte-vector 'zippy)
; #(122 105 112 112 121 0 0 0)

;;; for osc files. don't care about universal time

(define (make-file-timetag offset)
  (multiple-value-bind (int rem) (clfloor offset)
    (u8vector-append (make-byte-vector int)
                     (make-byte-vector
                      (inexact->exact (floor (* rem #xffffff)))))))

;;as part of an OSC message the types of each token are sent

(define-method* (return-type-code (int <integer>))
  (char->integer #\i))

(define-method* (return-type-code (flo <real>))
  (char->integer #\f))

(define-method* (return-type-code (str <string>))
  (char->integer #\s))

(define-method* (return-type-code (sym <symbol>))
  (char->integer #\s))

; (loop for x in '(1 1.0 "foo" foo) collect (return-type-code x))
; (105 102 115 115)

(define (make-type-array message)
  (let* ((mes (cdr message))
         (len (length mes))
         (pad (- 4 (mod len 4)))
         (vec (make-u8vector (+ len (if (= pad 1) (+ pad 4) pad)))))
    (u8vector-set! vec 0 (char->integer #\,))
    (do ((i 0 (+ i 1)))
        ((= i len) vec)
      (u8vector-set! vec (+ i 1)
                     (return-type-code (list-ref mes i))))))

; (make-type-array (list "/c_fill" 1 2.0 'z))
; #(44 105 102 115 0 0 0 0)

;;;;the first token in an osc message is always a string. the following
;;;;methods convert tokens to a string and then to a byte vector

(define-method* (get-first-obj (num <number>))
  (make-byte-vector (format #f "~s" num)))

(define-method* (get-first-obj (str <string>))
  (make-byte-vector str))

(define-method* (get-first-obj (sym <symbol>))
  (make-byte-vector (string-downcase (symbol->string sym))))

;;; formatting for standard OSC message. concatenates each separate
;;; byte vector for each token and returns array and array length as
;;; values

(define (format-osc message)
  (let ((arr (apply (function u8vector-append)
                    (get-first-obj (car message))
                    (make-type-array message)
                    (loop for m in (cdr message) 
                       collect (make-byte-vector m)))))
    (values arr (u8vector-length arr))))

(define (write-bundle offset message fd)
  (let ((arr #f))
    (multiple-value-bind (mess len) (format-osc message)
      (set! len (+ len 8 8 4))
      (set! arr (u8vector-append (make-byte-vector len)
                                 (make-byte-vector "#bundle")
                                 (make-file-timetag offset)
                                 (make-byte-vector len)
                                 mess))
      (u8vector-write arr fd))))


