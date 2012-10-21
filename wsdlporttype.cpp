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

vector<string> WSDLPortType::get_OperationNames()
{
	vector<string> retval;

	for(map<string, WSDLOperation *>::iterator i = mOperations.begin(); i != mOperations.end(); i++) {
		retval.push_back(i->first);
	}

	return retval;
}

WSDLOperation& WSDLPortType::get_Operation(string name) const
{
	return *(const_cast<WSDLPortType *>(this)->mOperations[name]);
}

void WSDLPortType::Load(xmlNodePtr node)
{
	xmlChar *name = xmlGetProp(node, (const xmlChar *)"name");
	if(name != NULL) {
		mName = (char *)name;
		xmlFree(name);
		LoadOperations(node);
	}
}

void WSDLPortType::LoadOperations(xmlNodePtr node)
{
	for(xmlNode *cur_node = node->children; cur_node != NULL; cur_node = cur_node->next) {
		if(cur_node->type == XML_ELEMENT_NODE && !xmlStrcmp(cur_node->name, (const xmlChar *)"operation")) {
			WSDLOperation *operation = new WSDLOperation(cur_node);
			if(operation != NULL) {
				if(operation->get_Name().length() > 0) {
					mOperations[operation->get_Name()] = operation;
				}
				else {
					delete operation;
				}
			}
		}
	}
}
