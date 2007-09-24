/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision: 1312 $
// $Date: 2007-07-10 18:25:53 -0500 (Tue, 10 Jul 2007) $ 

#ifndef __POINTS__
#define __POINTS__

#include "juce.h"

// A PointField is basically a named index (offset) into a float*
// point array. It also provides axis information used in plotting.
// A PointDef defines its own collection of PointFields.

class PointField {
  enum FieldType {
    Float=0,
    Integer,
    Normalized,
    Percentage,
    Keynum,
    Amplitude,
    Seconds,
  };
  String name;   // name of field
  int index;     // value index into a float *point array
  FieldType type; // what type of values field represents.
  float dval;    // default value for point creation.
  double from;   // lower value bound (used by plotter axis)
  double to;     // upper value bound (plotter)
  double by;     // tick increment along axis (plotter)
  int ticks;     // number of sub ticks

 public:

  PointField(XmlElement *xml) ;
  ~PointField() {}
  String getName() {return name;}
  void setName(String n) {name=n;}
  FieldType getType() {return type;}
  void setType(FieldType t) {type=t;}
  int getIndex() {return index;}
  void setIndex(int i) {index=i;}
  String getTypeName();
  float getDefault() {return dval;}
  void setDefault(float d) {dval=d;}
  double getMinimum() {return from;}
  void setMinimum(double m) {from=m;}
  double getMaximum() {return to;}
  void setMaximum(double m) {to=m;}
  double getIncrement() {return by;}
  void setIncrement(double i) {by=i;}
  double getIncrements() {return (to-from)/by;}
  int getTicks() {return ticks;}
  int setTicks(int t) {ticks=t;}
  double getRange() {return to-from;}
  XmlElement* toXml();
};

class SoundMap;

//
// A PointDef holds infomation about user defined points. They are
// imported/exported as xml text.
//

class PointDef {
  String name;
  OwnedArray<PointField> fields;
  SoundMap *soundmap;
 public:
  PointDef(XmlElement *xml);
  PointDef(PointDef &pd);  // deep copier
  ~PointDef() {};

  String getName() {return name; }
  void setName(String n) {name=n; }
  SoundMap *getSoundMap() {return soundmap;}
  void *setSoundMap(SoundMap *s) {soundmap=s;}
  PointField *getField(int i) { return fields[i]; }
  PointField *findField(String n) {
    for (int i=0; i<fields.size(); i++) {
      PointField *f=getField(i);
      if (f->getName() == n) 
	return f;
    }
    return NULL;
  }
};


//
// Point->Sound Interface: SoundParameters and SoundMaps
//

// A SoundParameter transforms a user value (the Source) into a
// value for a sound map: value=Source*Scaler+Offset. The Source
// can be a point field (F) or a constant (C). Scaler and Offsets
// are optional ie they are unused (X), Constant (C) or Field (F).

class SoundParameter {

  // Constant values of Source Scaler and Offset are kept in the 'C'
  // array; field indexes are kept in the 'F' array. Each array is
  // rank 3, where array[0] is the Source, array[1] is the Scaler, and
  // array[2] is the Offset.

  float C[3]; // C[0]=Source, C[1]=Scaler C[2]=Offset
  int F[3];   // F[0]=Source, F[1]=Scaler F[2]=Offset

  // The VSO enums are the indexes into the C and F arrays: index V
  // references the Source, S the Scaler and O the Offset, ie
  // C[V]=Source constant, C[S]=Scaler constant, C[O]=Offset constant;
  // F[V]=Source field, F[S]=Scaler field, F[O]=Offset field

  enum VSO {V=0, S, O}; 

  // The CalcModes name all possible ways in which the value can be
  // calculated from a Source Scaler and Offset. Each mode name
  // consists of three letters: the first letter represents Source,
  // the second the Scaler and the third the Offset. Letter meaning is
  // C=constant, F=field, X=unused

  enum CalcMode {
    FXX=1, FXC, FXF, FCX, FCC, FCF, FFX, FFC, FFF,
    CXX,   CXC, CXF, CCX, CCC, CCF, CFX, CFC, CFF,
  };

  // The specific CalcMode of the Soundparameter is determined when the
  // SoundMap is parsed from its Xml entity.

  CalcMode mode;

public:

  float getValue(float *point) ;
};

// A SoundMap is reponsible for transforming and writing point values
// to some sound destination. Here is what a Table interface might
// look like for a point called MIDI using a SoundMap called Midi:Note
// _____________________________________________
//                     Point: MIDI
//              Source      Scaler     Offset
// Midi:Note    --------------------------------
//    time      [time ]
//    dur       [duration]
//    chan      [channel]
//    key       [keynum]
//    vel       [amplitude]  127.0
// _____________________________________________

class SoundMap {} ;

class MidiMap : public SoundMap {
  SoundParameter time;
  SoundParameter chan;
  //  virtual void writePoint(MidiMessageSequence seq, float *poi);
  //  virtual void writePoint(MidiOutput port, float *poi);
};

class MidiNoteMap : public MidiMap {
  SoundParameter dur;
  SoundParameter key;
  SoundParameter vel;
};

class MidiOnMap : public MidiMap {
  SoundParameter key;
  SoundParameter vel;
};

class MidiOffMap : public MidiMap {
  SoundParameter key;
  SoundParameter vel;
};

class MidiProgMap : public MidiMap {
  SoundParameter prog;
};

class MidiCtrlMap : public MidiMap  {
  SoundParameter ctrl;
  SoundParameter val;
};

#endif
