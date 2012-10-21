#include "wsdloperation.h"

WSDLOperation::WSDLOperation(xmlNodePtr node)
{
	Load(node);
}

WSDLOperation::~WSDLOperation()
{
}

string WSDLOperation::get_Name() const
{
	return mName;
}

void WSDLOperation::Load(xmlNodePtr node)
{
	xmlChar *name = xmlGetProp(node, (const xmlChar *)"name");
	if(name != NULL) {
		mName = (char *)name;
		xmlFree(name);
	}
}