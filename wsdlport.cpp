#include "wsdlport.h"

WSDLPort::WSDLPort(xmlNodePtr node)
{
	Load(node);
}

WSDLPort::~WSDLPort()
{

}

string WSDLPort::get_Name() const
{
	return mName;
}

void WSDLPort::Load(xmlNodePtr node)
{
	xmlChar *name = xmlGetProp(node, (const xmlChar *)"name");
	if (name != nullptr) {
		mName = (char *)name;
		xmlFree(name);
	}
}
