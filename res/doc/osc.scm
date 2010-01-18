;
;; Sending and Receiving OSC Data
;

; Before you send or receive OSC messages you first need to open an
; OSC connection by specifying the input and output ports to osc:open.
; You can add a target hostname using a string "HOST:PORT" where HOST
; is a name or internet number, e.g. "localhost:7770" or
; "128.174.102.16:7770"

; This example opens a connection for liblo's example_server app,
; which listens for messages on port 7770. We tell CM to listen for
; incoming messages on port 7779:

(osc:open 7779 7770)

; Once a connection is established use "osc:message" to send messages
; to the running target app:

; Send just a path:

(osc:message "/Hello World!")

; Send some basic OSC data (ints, floats, booleans, strings)

(osc:message "/test/basic" 123 456.789 #t #f "Hello world!")

; You can send messages as lists too. Every message list must start
; with an OSC path (string):

(osc:message '("/test/basic" 123 456.789 #t #f "Hello world!"))

; To send midi and blobs you need to tag the data with :b or :m. This
; will send an OSC blob message:

(osc:message "/test/blob" :b '(0 2 4 6 8))

;; Send OSC's 4-byte midi message

(osc:message "/test/midi" :m '(144 60 127 0))

;; Send a NoteOff:

(osc:message "/test/midi" :m '(128 60 127 0))

; You can send bundles of messages using (osc:bundle time message...)
; A bundle lets you group multiple osc messages under one time tag.
; The timetag 0 means IMMEDIATE, to send a message in the future send
; an ahead factor, eg 3 means 2 second in the future:

(osc:bundle 0 '("/hi" 123) '("/ho" 4 5 6))

(osc:bundle 3 '("/stooges" "moe" "larry" "curley") ("/nyuk/nyuk/nyuk" #t))

; This will cause liblo's example_server app to exit cleanly:

(osc:message "/quit")

;
; Closing the OSC Port
;
; Close the OSC connection in CM when you are done!  IMPORTANT: Always
; close the target app's connection too, or else liblo will crash if
; you later attempt open a different target in the same CM session!

(osc:close)

;
; Receiving OSC Messages
;

; Open OSC with CM listening on port 7770, which is the hardwired port
; in liblo/examples/example_client. We use 7777 as the output port for
; no particular reason.

(osc:open 7770 7777)

; Define a hook to receive OSC messages as soon as they arrive at our
; input port. The hook function will be passed a single argument, a
; Lisp list containing the OSC message data that arrived at the port.

(define (myOscHook msg)
  (format #t "OSC message -> ~S~%" msg))

; Set the hook...

(osc:receive myOscHook)

; Now run your liblo/examples/example_client, you will see the
; messages appear in CM's console window as they arrive

; ...when you are done clear the hook

(osc:receive )

;; ...and close the Osc connection.

(osc:close )


