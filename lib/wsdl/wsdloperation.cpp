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

string WSDLOperation::get_InputAction() const
{
	return mInputAction;
}

string WSDLOperation::get_OutputMessageName() const
{
	return mOutput;
}

string WSDLOperation::get_OutputAction() const
{
	return mOutputAction;
}

void WSDLOperation::Load(xmlNodePtr node)
{
	xmlChar *name = xmlGetProp(node, (const xmlChar *)"name");
	if(name != nullptr) {
		mName = (char *)name;
		xmlFree(name);
		LoadInput(node);
		LoadOutput(node);
	}
}

void WSDLOperation::LoadInput(xmlNodePtr node)
{
	int count = 0;
	for(xmlNode *cur_node = node->children; cur_node != nullptr; cur_node = cur_node->next) {
		if(cur_node->type == XML_ELEMENT_NODE && !xmlStrcmp(cur_node->name, (const xmlChar *)"input")) {
			count++;
			xmlChar *message = xmlGetProp(cur_node, (const xmlChar *)"message");
			if(message != nullptr) {
				char *ch;
				if((ch = strstr((char *)message, ":")) == nullptr) ch = (char *)message;
				else ch++;
				mInput = ch;
				xmlFree(message);
			}
			xmlChar *action = xmlGetProp(cur_node, (const xmlChar *)"Action");
			if(action != nullptr) {
				mInputAction = (char *)action;
				xmlFree(action);
			}
		}
	}
}

void WSDLOperation::LoadOutput(xmlNodePtr node)
{
	int count = 0;
	for(xmlNode *cur_node = node->children; cur_node != nullptr; cur_node = cur_node->next) {
		if(cur_node->type == XML_ELEMENT_NODE && !xmlStrcmp(cur_node->name, (const xmlChar *)"output")) {
			count++;
			xmlChar *message = xmlGetProp(cur_node, (const xmlChar *)"message");
			if(message != nullptr) {
				char *ch;
				if((ch = strstr((char *)message, ":")) == nullptr) ch = (char *)message;
				else ch++;
				mOutput = ch;
				xmlFree(message);
			}
			xmlChar *action = xmlGetProp(cur_node, (const xmlChar *)"Action");
			if(action != nullptr) {
				mOutputAction = (char *)action;
				xmlFree(action);
			}
		}
	}
}
