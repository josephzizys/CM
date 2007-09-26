#include "Points.h"
#include <string>
#include <sstream>
#include <iostream>

struct fieldprototype {
  // global name->field prototype mapping.
  String name;
  int type;
  float from, to, by;
  int ticks;
} fieldprototypes[] = 
  {
    {T("float"), PointField::Float, 0.0, 1.0, 0.1, 10},
    {T("integer"), PointField::Integer, 0.0, 100.0, 10.0, 10},
    {T("normalized"), PointField::Normalized, 0.0, 1.0, .25, 5},
    {T("percentage"), PointField::Percentage, 0.0, 100.0, 25.0, 5},
    {T("keynum"), PointField::Keynum, 0.0, 127.0, 12.0, 12},
    {T("amplitude"), PointField::Amplitude, 0.0, 1.0, .25, 5},
    {T("seconds"), PointField::Seconds, 0.0, 60.0, 1.0, 4},
    {T(""), 0, 0.0, 0.0, 0.0, 0}
  }; 

fieldprototype *findfieldprototype (String n) {
  int i=0;
  while (fieldprototypes[i].name != String::empty) 
    if (fieldprototypes[i].name.equalsIgnoreCase(n))
      return &fieldprototypes[i];
  return NULL;
}

PointField::PointField(PointField *pf) {
  name=String(pf->name);
  index=pf->index;
  type=pf->type;
  dval=pf->dval;
  from=pf->from;
  to=pf->to;
  by=pf->by;
  ticks=pf->ticks;
}

PointField::PointField(XmlElement *xml) {
}

String PointField::getTypeName() {
  static char *axisnames[] = { T("float"), T("integer"),
			       T("normalized"), T("percentage"),
			       T("keynum"), T("amplitude"),
			       T("seconds") };
  return String(axisnames[ getType() ]) ;
}

XmlElement * PointField::toXml() {
  XmlElement *top=new XmlElement( T("field"));
  XmlElement *nam=new XmlElement( T("name") );
  XmlElement *typ=new XmlElement( T("type") );
  XmlElement *val=new XmlElement( T("default") );

  nam->addTextElement( getName() );
  String str = getTypeName();
  str << T(" ") << from << T(" ") << to << T(" ") << by ;
  typ->addTextElement(str);
  val->addTextElement( String(getDefault()) );

  top->addChildElement(nam);
  top->addChildElement(typ);
  top->addChildElement(val);
  return top;
}

float SoundParameter::getValue(float *point) {
  switch (mode) {
  case FXX:
    return point[F[V]] ;
    break;
  case FXC:
    return point[F[V]] + C[O] ;
  case FXF:
    return point[F[V]] + point[F[O]] ;
  case FCX:
    return point[F[V]] * C[S] ;
  case FCC:
    return point[F[V]] * C[S] + C[O] ;
  case FCF:
    return point[F[V]] * C[S] + point[F[O]] ;
  case FFX:
    return point[F[V]] * point[F[S]] ;
  case FFC:
    return point[F[V]] * point[F[S]] + C[O] ;
  case FFF:
    return point[F[V]] * point[F[S]] + point[F[O]] ;
    break;
  case CXX:
    return C[V];
  case CXC:
    return C[V] + C[O] ;
    break;
  case CXF:
    return C[V] + point[F[O]] ;
    break;
  case CCX:
    return C[V] * C[S] ;
    break;
  case CCC:
    return C[V] * C[S] + C[O] ;
    break;
  case CCF:
    return C[V] * C[S] + point[F[O]];
    break;
  case CFX:
    return C[V] * point[F[S]] ;
    break;
  case CFC:
    return C[V] * point[F[S]] + C[O] ;
    break;
  case CFF:
    return C[V] * point[F[S]] + point[F[O]] ;
    break;
  }
}

