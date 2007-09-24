#include "Points.h"
#include <string>
#include <sstream>
#include <iostream>

String PointField::getTypeName() {
  static char *axisnames[] = { T("float"), T("integer"),
			       T("normalized"), T("percentage"),
			       T("keynum"), T("amplitude"),
			       T("seconds") };
  return String(axisnames[ getType() ]) ;
}

PointField::PointField(XmlElement *xml) {
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

