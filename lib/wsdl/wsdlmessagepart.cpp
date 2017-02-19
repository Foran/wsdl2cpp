#include "wsdlmessagepart.h"

WSDLMessagePart::WSDLMessagePart(xmlNodePtr node)
{
	Load(node);
}

WSDLMessagePart::~WSDLMessagePart()
{
}

string WSDLMessagePart::get_Name() const
{
	return mName;
}

string WSDLMessagePart::get_Element() const
{
	return mElement;
}

void WSDLMessagePart::Load(xmlNodePtr node)
{
	xmlChar *name = xmlGetProp(node, (const xmlChar *)"name");
	if(name != nullptr) {
		mName = (char *)name;
		xmlFree(name);
	}
	xmlChar *element = xmlGetProp(node, (const xmlChar *)"element");
	if(element != nullptr) {
		mElement = (char *)element;
		xmlFree(element);
	}
}