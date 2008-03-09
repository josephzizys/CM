;;; **********************************************************************
;;; Copyright (C) 2007, 2008 Todd Ingalls, Rick Taube.
;;; This program is free software; you can redistribute it and/or modify
;;; it under the terms of the Lisp Lesser Gnu Public License. The text of
;;; this agreement is available at http://www.cliki.net/LLGPL            
;;; **********************************************************************

; (require-extension srfi-17)

#>

void mp_note(double time, double dur, float key, float vel, float chan) {
 ((GraceApp *)GraceApp::getInstance())->midiOutPort->sendNote(time, dur, key, vel, chan); 
}

void mp_data(int type, double time, float chan, float data1, float data2) {
 ((GraceApp *)GraceApp::getInstance())->midiOutPort->sendData(type, time, chan, data1, data2) ;
}

void mp_message(MidiMessage *m) {
 ((GraceApp *)GraceApp::getInstance())->midiOutPort->sendMessage(m) ;
}

/// MidiMessage accessors

MidiMessage *mm_make(int type, double time, int chan, 
		     int data1, int data2 ) {
  MidiMessage *m;
  chan++; // juce channels are 1 based
  switch (type) {
  case MidiNode::MM_OFF :
    m=new MidiMessage(MidiMessage::noteOff(chan, data1));
    break;
  case MidiNode::MM_ON :
    m=new MidiMessage(MidiMessage::noteOn(chan, data1, (juce::uint8)data2));
    break;
  case MidiNode::MM_TOUCH :
    m=new MidiMessage(MidiMessage::aftertouchChange(chan, data1, data2));
    break;
  case MidiNode::MM_CTRL :
    m=new MidiMessage(MidiMessage::controllerEvent(chan, data1, data2));
    break;
  case MidiNode::MM_PROG :
    m=new MidiMessage(MidiMessage::programChange(chan, data1));
    break;
  case MidiNode::MM_PRESS :
    m=new MidiMessage(MidiMessage::channelPressureChange(chan, data1));
    break;
  case MidiNode::MM_BEND :
    m=new MidiMessage(MidiMessage::pitchWheel(chan, data1));
    break;
  default:
    return NULL;
  }
  return m;
}

MidiMessage *mm_copy(MidiMessage *m) {
  return new MidiMessage(*m);
}

void mm_free(MidiMessage *m) {
  delete m;
}

bool mm_is_type(MidiMessage *m, int typ) {
  switch (typ) {
  case MidiNode::MM_OFF :
    return m->isNoteOff();
    break;
  case MidiNode::MM_ON :
    return m->isNoteOn();
    break;
  case MidiNode::MM_TOUCH :
    return m->isAftertouch();
    break;
  case MidiNode::MM_CTRL :
    return m->isController();
    break;
  case MidiNode::MM_PROG :
    return m->isProgramChange();
    break;
  case MidiNode::MM_PRESS :
    return m->isChannelPressure();
    break;
  case MidiNode::MM_BEND :
    return m->isPitchWheel();
    break;
  default:
    return false;
  }
}

double mm_time(MidiMessage *m) {
  return m->getTimeStamp();
}

void mm_set_time(MidiMessage *m, double t) {
  m->setTimeStamp(t);
  return ;		
}

int mm_chan(MidiMessage *m) {
  // juce channels are 1 based
  return m->getChannel()-1;
}

void mm_set_chan(MidiMessage *m, int chan) {
  // juce channels are 1 based
  m->setChannel(chan+1);
}

int mm_data(MidiMessage *m, int n ) {
  juce::uint8 *data=m->getRawData();
  return (int)data[n];
}

void mm_set_data(MidiMessage *m, int n, int v ) {
  juce::uint8 *data=m->getRawData();
  data[n]=(v & 0x7f);
}

//INput Hook Code
void set_input_hook( C_word proc )
{
 // FIX
 ((GraceApp *)GraceApp::getInstance())->schemeProcess->setInputHook( proc);
}

<#

(define mm:off    #x8)
(define mm:on     #x9)
(define mm:touch  #xA)
(define mm:ctrl   #xB)
(define mm:prog   #xC)
(define mm:press  #xD)
(define mm:bend   #xE)

(define (mm:make type #!key (time 0) (chan 0) 
		 (key 60) (vel 64) (num 0) 
		 (val 0) )
  (cond ((<= mm:off type mm:on)
	 ((foreign-lambda (c-pointer "MidiMessage") "mm_make"
			  int double int int int)
	  type time chan key vel))
	((= type mm:ctrl)
	 ((foreign-lambda (c-pointer "MidiMessage") "mm_make"
			  int double int int int)
	  type time chan num val))
	((= type mm:touch)
	 ((foreign-lambda (c-pointer "MidiMessage") "mm_make"
			  int double int int int)
	  type time chan key val))
	((<= mm:prog type mm:bend)
	 ((foreign-lambda (c-pointer "MidiMessage") "mm_make"
			  int double int int int)
	  type time chan val 0))
	(else
	 (error "Unknown MidiMessage type:" type))))

(define (mm:free m)
  ( (foreign-lambda void "mm_free" (c-pointer "MidiMessage"))
    m)
  (values))

(define (mm:copy m)
  ( (foreign-lambda (c-pointer "MidiMessage") "mm_copy"
		    (c-pointer "MidiMessage"))  
    m))

(define (mm:type? m t)
  ( (foreign-lambda bool "mm_is_type" (c-pointer "MidiMessage") int)
    m t))

(define (mm:time m)
  ( (foreign-lambda double "mm_time" (c-pointer "MidiMessage"))
    m))

(define (mm:time-set! m t)
  ( (foreign-lambda void "mm_set_time" (c-pointer "MidiMessage") double)
    m t)
  t)

(define (mm:chan m)
  ( (foreign-lambda int "mm_chan" (c-pointer "MidiMessage"))
    m))

(define (mm:chan-set! m c)
  ( (foreign-lambda void "mm_set_chan" (c-pointer "MidiMessage") int)
    m c)
  c)

(define (mm:key m)
   ( (foreign-lambda int "mm_data" (c-pointer "MidiMessage") int)
     m 1))

(define (mm:key-set! m k)
  ( (foreign-lambda void "mm_set_data" (c-pointer "MidiMessage") int int)
     m 1 k)
  k)

(define (mm:vel m)
  ( (foreign-lambda int "mm_data" (c-pointer "MidiMessage") int)
    m 2))

(define (mm:vel-set! m v)
  ( (foreign-lambda void "mm_set_data" (c-pointer "MidiMessage") int int)
     m 2 v)
  v)

(define (mm:val m)
  (cond ((or (mm:type? m mm:ctrl) (mm:type? m mm:touch))
	 ;; controlChange: 
	 ( (foreign-lambda int "mm_data" (c-pointer "MidiMessage") int)
	   m 2))
	(else
	 ;; programChange channelPressure pitchBend
	 ( (foreign-lambda int "mm_data" (c-pointer "MidiMessage") int)
	   m 1))))	 

(define (mm:val-set! m v)
  (cond ((or (mm:type? m mm:ctrl) (mm:type? m mm:touch) )
	 ( (foreign-lambda void "mm_set_data" (c-pointer "MidiMessage")
			   int int)
	   m 2 v))
	(else
	 ( (foreign-lambda void "mm_set_data" (c-pointer "MidiMessage")
			   int int)
	   m 1 k)))
  v)

(define (mm:num m)
  ;; program change
  ( (foreign-lambda int "mm_data" (c-pointer "MidiMessage") int)
    m 1))

(define (mm:num-set! m v)
  ( (foreign-lambda void "mm_set_data" (c-pointer "MidiMessage") int int)
     m 1 v)
  v)


#|
(define-getter-with-setter mm:time mm:time-set!)
(define-getter-with-setter mm:chan mm:chan-set!)
(define-getter-with-setter mm:key mm:key-set!)
(define-getter-with-setter mm:vel mm:vel-set!)
(define-getter-with-setter mm:val mm:val-set!)
(define-getter-with-setter mm:num mm:num-set!)
|#

;;
;; midi port
;;

(define (mp:note time dur key amp chan)
  ( (foreign-lambda void "mp_note" double double float float float)
    time dur key amp chan))

(define (mp:midi time dur key amp chan)
  ( (foreign-lambda void "mp_note" double double float float float)
    time dur key amp chan))

(define (mp:off time key chan)
  ( (foreign-lambda void "mp_data" int double float float float)
    mm:off time chan key 0))

(define (mp:on time key vel chan)
  ( (foreign-lambda void "mp_data" int double float float float)
    mm:on time chan key vel))

(define (mp:touch time key val chan)
  ( (foreign-lambda void "mp_data" int double float float float)
    mm:touch time chan key val))

(define (mp:ctrl time num val chan)
  ( (foreign-lambda void "mp_data" int double float float float)
    mm:ctrl time chan num val))

(define (mp:prog time val chan)
  ( (foreign-lambda void "mp_data" int double float float float)
    mm:prog time chan val 0))

(define (mp:press time val chan)
  ( (foreign-lambda void "mp_data" int double float float float)
    mm:press time chan val 0))

(define (mp:bend time val chan)
  ( (foreign-lambda void "mp_data" int double float float float)
    mm:bend time chan val 0))

(define (mp:mm ptr)
  ( (foreign-lambda void "mp_message" (c-pointer "MidiMessage"))
    ptr))

(define (mp:inhook %hook)
  ( (foreign-lambda void "set_input_hook" scheme-object )
    ;; hook closure wraps a call to user's hook inside error protection
    (lambda (%msg)
      (call-with-current-continuation
       (lambda (%cont)
	 (with-exception-handler
	  (lambda (%err)
	    (print-error
	     (sprintf ">>> Error: ~A~%    Aborting MIDI inhook.~%"
		      ((condition-property-accessor 'exn 'message) %err)
		      ))
	    (%cont -1)  ; -1 means error
	    )
	  (lambda () 
	    ( %hook %msg)  ;; call users hook with the received message
	    0 ; 0 means success
	    )))))))

;; message definitions

(define-send-message mp:note ((#:time 0) (#:dur .5) (#:key 60) (#:amp .5) (#:chan 0)))
(define-send-message mp:midi ((#:time 0) (#:dur .5) (#:key 60) (#:amp .5) (#:chan 0)))
(define-send-message mp:off ((#:time 0) (#:key 60) (#:chan 0)))
(define-send-message mp:on ((#:time 0) (#:key 60) (#:vel 64) (#:chan 0)))
(define-send-message mp:touch ((#:time 0) (#:key 0) (#:val 0) (#:chan 0)))
(define-send-message mp:ctrl ((#:time 0) (#:num 0) (#:val 0) (#:chan 0)))
(define-send-message mp:prog ((#:time 0) (#:val 0) (#:chan 0)))
(define-send-message mp:press ((#:time 0) (#:val 0) (#:chan 0)))
(define-send-message mp:bend ((#:time 0) (#:val 8192) (#:chan 0)))
(define-send-message mp:mm ((#:mm #f) ))
(define-send-message mp:inhook ((#:func #f) ))

;;; eof

