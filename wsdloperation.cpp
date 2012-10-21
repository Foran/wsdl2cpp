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

string WSDLOperation::get_InputMessageName() const
{
	return mInput;
}

string WSDLOperation::get_OutputMessageName() const
{
	return mOutput;
}

void WSDLOperation::Load(xmlNodePtr node)
{
	xmlChar *name = xmlGetProp(node, (const xmlChar *)"name");
	if(name != NULL) {
		mName = (char *)name;
		xmlFree(name);
		LoadInput(node);
		LoadOutput(node);
	}
}

void WSDLOperation::LoadInput(xmlNodePtr node)
{
	int count = 0;
	for(xmlNode *cur_node = node->children; cur_node != NULL; cur_node = cur_node->next) {
		if(cur_node->type == XML_ELEMENT_NODE && !xmlStrcmp(cur_node->name, (const xmlChar *)"input")) {
			count++;
			xmlChar *name = xmlGetProp(node, (const xmlChar *)"name");
			if(name != NULL) {
				mInput = (char *)name;
				xmlFree(name);
			}
		}
	}
}

void WSDLOperation::LoadOutput(xmlNodePtr node)
{
	int count = 0;
	for(xmlNode *cur_node = node->children; cur_node != NULL; cur_node = cur_node->next) {
		if(cur_node->type == XML_ELEMENT_NODE && !xmlStrcmp(cur_node->name, (const xmlChar *)"output")) {
			count++;
			xmlChar *name = xmlGetProp(node, (const xmlChar *)"name");
			if(name != NULL) {
				mOutput = (char *)name;
				xmlFree(name);
			}
		}
	}
}
