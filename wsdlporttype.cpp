#include "wsdlporttype.h"

WSDLPortType::WSDLPortType(xmlNodePtr node)
{
	Load(node);
}

WSDLPortType::~WSDLPortType()
{
	for(map<string, WSDLOperation *>::iterator i = mOperations.begin(); i != mOperations.end(); i++) {
		delete i->second;
	}
}

string WSDLPortType::get_Name() const
{
	return mName;
}

void WSDLPortType::Load(xmlNodePtr node)
{
	xmlChar *name = xmlGetProp(node, (const xmlChar *)"name");
	if(name != NULL) {
		mName = (char *)name;
		xmlFree(name);
	}
}