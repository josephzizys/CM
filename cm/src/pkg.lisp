;;; **********************************************************************
;;; Copyright (C) 2003 Heinrich Taube (taube@uiuc.edu) 
;;; 
;;; This program is free software; you can redistribute it and/or
;;; modify it under the terms of the GNU General Public License
;;; as published by the Free Software Foundation; either version 2
;;; of the License, or (at your option) any later version.
;;; 
;;; This program is distributed in the hope that it will be useful,
;;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;;; GNU General Public License for more details.
;;; 
;;; **********************************************************************

;;; $Name$
;;; $Revision$
;;; $Date$

(in-package :cl-user)

;;;
;;; The CM package definition. Keywords are used so that the names
;;; will reflect the inplementation's read-case sensitivity but will
;;; not pollute the current package's name space with any new symbols.
;;;
;;; The CLM, CMN, and MidiShare packages must exist when this file is
;;; loaded, either by loading the systems or their stubs files.
;;;

(defpackage :cm
  (:shadow :make-load-form #+lispworks :random #+lispworks :funcall
           ;; have to block these from CLM
           :io :ran :exit :quit :play :graph )
  (:use :common-lisp )
  ;; use keywords instead of strings for case sensitive lisps.
  (:import-from :clm 
                :mus-next
                :mus-bshort
                :mus-aifc
                :mus-riff
                :mus-lshort
                :*clm-with-sound-depth*
                :wsdat-play
                :init-with-sound
                :finish-with-sound
                :*clm-channels*
                :*clm-srate*
                :*clm-file-name*
                :clm-load
                :dac
                :*definstrument-hook*
                ;; these are also used by CM but defs don't conflict.
                ;#+(and clm2 (not clm3)) :graph 
                :spectrum :env :src 
                )
  (:import-from :cmn 
                :init-clm-input
                :*exact-rhythms*
                :score
                :staff-descriptors
                :stfdat-staff
                :staff-data 
                :set-staff-number
                :set-staff-clef
                :finish-clm-input
                :find-staff
                :add-staff
                :add-data-1
                :add-note-to-staff)
  (:import-from :midishare
		:midishare :midiGetVersion :MidiOpen :MidiClose :MidiCountAppls
		:MidiGetNamedAppl :MidiGetIndAppl :MidiErrIndex :MidiGetName
		:MidiConnect :MidiGetTime :MidiIsConnected
		:MidiSendIm :MidiSend :MidiSendAt :MidiAddSeq
		:typeNote :typeKeyOn :typeKeyOff :typeKeyPress :typeCtrlChange
		:typeProgChange :typeChanPress :typePitchWheel :typePitchBend
		:typeSongPos :typeSongSel :typeClock :typeStart :typeContinue
		:typeStop :typeTune :typeActiveSens :typeReset :typeSysEx
		:typeStream :typePrivate :typeSeqNum :typeTextual
		:typeCopyright :typeSeqName :typeInstrName :typeLyric
		:typeMarker :typeCuePoint :typeChanPrefix :typeEndTrack
		:typeTempo :typeSMPTEOffset :typePortPrefix :typeKeySign
		:typeTimeSign :MidiNewEv :port :chan :field :bend :text :port
		:ref :date :evtype :MidiCopyEv :MidiFreeEv :MidiAddField
                :midiTask :midiGetEv :MidiSetRcvAlarm
                :nullptr :nullptrp :MidiFlushEvs 
                ;;:MidiShareSync :MidiOpenSync :MidiCloseSync :MidiGetSyncEv
                
		:OpenPlayer :ClosePlayer :midiNewSeq
		:StartPlayer :ContPlayer :StopPlayer :PausePlayer
		:kMuteOn :kMuteOff :kSoloOn :kSoloOff :kMute :kSolo
		:kExternalSync :kInternalSync :kClockSync :kSMPTESync
		:GetAllTrackPlayer :SetAllTrackPlayer
		:GetTrackPlayer :SetTrackPlayer
		:SetParamPlayer :SetTempoPlayer
		:TicksPerQuarterNote
		:SetSynchroInPlayer :MidiNewMidiFileInfos
		:MidiFileLoad :MidiFileSave :mf-clicks :mf-format :mf-timedef)
  (:import-from :fomus
                :fomus :part-id :part-events
                :base-event :event-off :event-id :timesig :keysig
                :fomus-newpart)
  (:export :accumulation :amplitude :append-object :audio-file :axis
           :*beat* :best-normal-form :between :cd :cents->scaler
           :chord :*chromatic-scale* :clm-file :cm :cm-version :cmio
           :cmn :cmn-file :copier :copy-object :cycle :date-and-time
           :decimals :decode-interval :defaxis :defobject :defprocess
           :doeach :drunk :dumposc :eod? :eop? :events :expl :explseg
           :explsegs :f :false :find-object :fit :fm-spectrum
           :fold-objects :funcall :graph :heap :hertz :histogram :i
           :import-events :input :insert-object :interp :interpl
           :interval :invert :io :join :keynum :line
           :list-named-objects :list-subobjects :log-axis :lookup
           :*loudest* :make-cm :map-objects :map-pattern-data
           :map-subcontainers :map-subobjects :markov-analyze :markov
           :midi-chan-event :midi-channel-map :midi-channel-pressure
           :midi :midi-connections :midi-control-change :midi-eot
           :midi-file :midi-file-print :midi-key-pressure
           :midi-key-signature :midi-note-off :midi-note-on
           :midi-pitch-bend :midi-port-event :midi-program-change
           :midi-sequence-number :midi-sequencer-event
           :midi-smpte-offset :midi-stream :midi-system-event
           :midi-tempo-change :midi-text-event :midi-time-signature
           :midishare-stream :mode :new :next :note-accidental :note
           :note-name :now :object->cmn :object-name
           :object-parameters :object-time :octave-number :odds
           :output :palindrome :pattern-state :pattern-value :pattern?
           :pick :pickl :pitch-class :play :player-cont
           :player-load-midifile :player-mute :player-pause
           :player-save-midifile :player-set-tempo :player-solo
           :player-start :player-stop :player-stream :player-unmute
           :player-unsolo :plotter-add-layer :plotter-close
           :plotter-data :plotter :plotter-front-styling
           :plotter-property :plotter-redraw :plotter-scroll
           :plotter-zoom :point :power :prime-form :process :pval
           :pval :pwd :quantize :ran :random :range :ransegs
           :remove-object :remove-subobjects :rescale-envelope
           :rescale :rewrite :rewrite-generation :rhythm :rm-spectrum
           :rotation :save-object :sc-file :scale-max :scale-min
           :scale-mod :scale-order :*scale* :scale= :scale> :scale>=
           :scale< :scale<= :scaler->cents :sco-file :seq
           :set-clm-output-hook! :set-midi-output-hook!
           :set-sco-output-hook! :shell :shuffle :*softest* :sprout
           :stop :subcontainers :subobjects :sv :sv+ :sv* :*tempo*
           :tendency :*time-slots* :transpose :transposer :true
           :tuning :vary :wait :wait-until)
  )

;;;
;;; intern and export ms:new and ms:MidiPrintEv
;;;

(let ((syms '(#:new  #:MidiPrintEv)))
  (map nil (lambda (s) (intern (symbol-name s) :midishare)) syms)
  (export (mapcar #'(lambda (x) (find-symbol (symbol-name x) :midishare))
                  syms)
          :midishare))
