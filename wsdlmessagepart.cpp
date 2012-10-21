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
	if(name != NULL) {
		mName = (char *)name;
		xmlFree(name);
	}
	xmlChar *element = xmlGetProp(node, (const xmlChar *)"element");
	if(name != NULL) {
		char *ch;
		if((ch = strstr((char *)element, ":")) == NULL) ch = (char *)element;
		else ch++;
		mElement = ch;
		xmlFree(element);
	}
}