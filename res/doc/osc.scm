;
;; Sending and Receiving OSC messages.
;

; Note: these examples were tested using liblo's example programs
; 'example_server' and 'example_client' located in
; liblo/examples/. Both of these demo apps are hardwired to use port
; 7770. To run the examples with some other OSC app specify the
; appropiate target port when you open the OSC connection.

;
;; Opening connections and sending messages
;

; To open an OSC connection you specify CM's input port and the target
; output port to send data to. You can optionally provide a target
; host by passing a string "hostip:port" as the target, for example
; "localhost:57120" or "128.174.102.16:57110"

; Let's open a connection for liblo's examples/example_server app
; which listens for messages on port 7770. We tell CM to listen for
; incoming messages on port 7779:

(osc:open 7779 7770)

; [Start up liblo/examples/client_server...]

; Now that your OSC app is running and listening on your target port
; you can send messages to it using "osc:message" :

; Send just a path

(osc:message "/Hello World!")

; Send some basic OSC data (ints, floats, booleans, strings)

(osc:message "/test/basic" 123 456.789 #t #f "Hello world!")

; Send an osc blob message:

(osc:message "/test/blob" :b '(0 2 4 6 8))

;; Send a 4-byte osc midi message (NoteOn chan 0, key 60, vel 127)

(osc:message "/test/midi" :m '(144 60 127 0))

;; Send a NoteOff:

(osc:message "/test/midi" :m '(128 60 127 0))

; This will cause liblo's example_server app to exit cleanly:

(osc:message "/quit")

; Close the OSC connection in CM when you are done!  IMPORTANT: Always
; close the target app's connection too, or else liblo will crash if
; you later attempt open a different target in the same CM session...

(osc:close)

;
; Receiving OSC Messages
;

; Open OSC with CM listening on port 1170, which is the hardwired port
; in liblo/examples/example_client. We use 7777 as the output port.

(osc:open 7770 7777)

; Define a hook to receive OSC messages as soon as they arrive at our
; input port. The hook function will be passed a single argument, a
; Lisp list containing the OSC message data that arrived at the port.

(define (myOscHook msg)
  (format #t "OSC message -> ~S~%" msg))

; Set the hook...

(osc:hook myOscHook)

; Now run your liblo/examples/example_client, you will see the
; messages appear in CM's console window as they arrive

; ...when you are done clear the hook

(osc:hook #f)

;; ...and close the Osc connection.

(osc:close )


