#include "wsdlmessage.h"

WSDLMessage::WSDLMessage(xmlNodePtr node)
{
	Load(node);
}

WSDLMessage::~WSDLMessage()
{
}

string WSDLMessage::get_Name() const
{
	return mName;
}

void WSDLMessage::Load(xmlNodePtr node)
{
	xmlChar *name = xmlGetProp(node, (const xmlChar *)"name");
	if(name != NULL) {
		mName = (char *)name;
		xmlFree(name);
	}
}