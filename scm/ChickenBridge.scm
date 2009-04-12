;;; **********************************************************************
;;; Copyright (c) 2008 Rick Taube.
;;; This program is free software; you can redistribute it and/or modify
;;; it under the terms of the Lisp Lesser Gnu Public License. The text of
;;; this agreement is available at http://www.cliki.net/LLGPL            
;;; **********************************************************************

;;
;; Loading
;;


(declare
 (unit cm)
 (run-time-macros)
 (uses extras )
 (usual-integrations)
 (export

  ;; chicken
  ash logand lognot logxor logior logtest 
  most-positive-fixnum most-negative-fixnum
  list-set! 
  make-equal-hash-table make-eq-hash-table hash-set! hash-ref

  ;; ffi
  ffi_sched_score_mode_p ffi_sched_score_time

  ;; utilities
  print-output print-error print-value shell quit
  first second third fourth fifth sixth seventh eighth
  ninth tenth nth rest last butlast find position
  tail concat make-list with-optkeys expand-optkeys

  ;; loop
  loop process

  ;; toolbox
  quit cwd chdir shell rescale discrete int float
  pi plus times minus divide quantize decimals rhythm->seconds
  cents->ratio log10 log2 ratio->cents interp tendency fit segs scale
  random ran-set! ran between pick pdds vary shuffle shuffle! ranlow
  ranhigh ranmiddle ranbeta ranexp rangauss rancauchy ranpoisson
  rangamma ranbrown ranpink
  note key hz pc transpose invert retrograde
  scale-order scale-order!
  rhythm in-tempo *beat* *tempo*

  ;; patterns
  make-cycle make-line make-palindrome make-heap make-rotation
  make-weighting make-markov make-graph markov-analyze next eop? eod?
  promise

  ;; spectral
  rm-spectrum fm-spectrum spectrum-copy spectrum-time spectrum-size
  spectrum-freqs spectrum-amps spectrum-keys spectrum-pairs
  spectrum-minfreq spectrum-maxfreq spectrum-minamp spectrum-maxamp
  spectrum-add! spectrum-flip!  spectrum-rescale! import-spear-frames
  export-spear-frames

  ;; sal
  sal sal:print sal:chdir sal:load sal:open load-sal-file !=

  ;; ports
  ports send expand-send
  mp:open mp:midi mp:off mp:on mp:touch mp:ctrl mp:prog 
  mp:press mp:bend mp:tuning 
  mp:playseq mp:saveseq mp:copyseq mp:plotseq mp:clearseq mp:recordseq
  mm:off mm:on mm:touch mm:ctrl mm:prog mm:press mm:bend
  mp:inhook mp:inchans mp:inops
  cs:i cs:f cs:open-output-file

  ;; processes
  
  define-process define-send-message process now sprout pause paused? continue stop hush

  ))


(include "chicken.scm")
(include "chicken-foreign.scm")
(include "utilities.scm")
(include "loop.scm")
(include "patterns.scm")
(include "toolbox.scm")
(include "spectral.scm")
(include "sal.scm")
(include "ports.scm")
(include "processes.scm")

;; HORRIBLE HACK allows these define-syntax items to be exported for
;; runtime


(return-to-host)

;; csc -c++ -embedded -t ChickenBridge.scm 
;; mv ChickenBridge.cpp ../src
