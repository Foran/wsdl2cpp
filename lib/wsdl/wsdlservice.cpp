#include "wsdlservice.h"

WSDLService::WSDLService(xmlNodePtr node)
{

}

WSDLService::~WSDLService()
{
	for (map<string, WSDLPort *>::iterator i = mPorts.begin(); i != mPorts.end(); i++) {
		delete i->second;
	}
}

string WSDLService::get_Name() const
{
	return mName;
}

vector<string> WSDLService::get_PortNames()
{
	vector<string> retval;

	for (map<string, WSDLPort *>::iterator i = mPorts.begin(); i != mPorts.end(); i++) {
		retval.push_back(i->first);
	}

	return retval;
}

void WSDLService::Load(xmlNodePtr node)
{
	xmlChar *name = xmlGetProp(node, (const xmlChar *)"name");
	if (name != nullptr) {
		mName = (char *)name;
		xmlFree(name);
		LoadPorts(node);
	}
}

void WSDLService::LoadPorts(xmlNodePtr node)
{
	for (xmlNode *cur_node = node->children; cur_node != nullptr; cur_node = cur_node->next) {
		if (cur_node->type == XML_ELEMENT_NODE && !xmlStrcmp(cur_node->name, (const xmlChar *)"port")) {
			WSDLPort *port = new WSDLPort(cur_node);
			if (port != nullptr) {
				if (port->get_Name().length() > 0) {
					mPorts[port->get_Name()] = port;
				}
				else {
					delete port;
				}
			}
		}
	}
}
