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

(defpackage cm 
  (:use common-lisp #+clm clm #+midishare midishare)
  #+clm (:shadow "IO" "RAN" "DEFINSTRUMENT")
  #+clm (:import-from clm 
                      mus-next
                      mus-bshort
                      mus-aifc
                      mus-riff
                      mus-lshort
                      *clm-with-sound-depth*
                      wsdat-play
                      init-with-sound
                      finish-with-sound
                      *clm-channels*
                      *clm-srate*
                      ;definstrument
                      )
  #+midishare
  (:import-from midishare
                midishare midiGetVersion MidiOpen MidiClose MidiCountAppls
                MidiGetNamedAppl MidiGetIndAppl MidiErrIndex MidiGetName
                MidiConnect MidiGetTime MidiIsConnected 
                MidiSendIm MidiSend MidiSendAt
                typeNote typeKeyOn typeKeyOff typeKeyPress typeCtrlChange 
                typeProgChange typeChanPress typePitchWheel typePitchBend
                typeSongPos typeSongSel typeClock typeStart typeContinue
                typeStop typeTune typeActiveSens typeReset typeSysEx
                typeStream typePrivate typeSeqNum typeTextual
                typeCopyright typeSeqName typeInstrName typeLyric
                typeMarker typeCuePoint typeChanPrefix typeEndTrack
                typeTempo typeSMPTEOffset typePortPrefix typeKeySign
                typeTimeSign MidiNewEv port chan field bend text port)
  #+(and midishare player)
  (:import-from midishare
                OpenPlayer ClosePlayer midiNewSeq
                StartPlayer ContPlayer StopPlayer PausePlayer
                kMuteOn kMuteOff kSoloOn kSoloOff kMute kSolo 
                kExternalSync kInternalSync kClockSync kSMPTESync
                GetAllTrackPlayer SetAllTrackPlayer
                GetTrackPlayer SetTrackPlayer 
                SetParamPlayer SetTempoPlayer
                TicksPerQuarterNote
                SetSynchroInPlayer MidiNewMidiFileInfos
                MidiFileLoad MidiFileSave mf-clicks mf-format mf-timedef
                )
  (:shadow make-load-form)
  )

#+cmn
(import '(cmn::init-clm-input cmn::*exact-rhythms* cmn::score
          cmn::staff-descriptors cmn::stfdat-staff cmn::staff-data 
          cmn::set-staff-number cmn::set-staff-clef cmn::set-staff-meter
          cmn::finish-clm-input cmn::find-staff cmn::add-staff 
          cmn::add-data-1 cmn::add-note-to-staff)
        :cm)