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
