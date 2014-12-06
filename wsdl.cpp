#include "wsdl.h"

WSDL::WSDL(string filename)
{
	Load(filename);
}

WSDL::WSDL(xmlDocPtr document)
{
	Load(document);
}

WSDL::WSDL(xmlNodePtr node)
{
	Load(node);
}

WSDL::~WSDL()
{
	for(map<string, WSDLMessage *>::iterator i = mMessages.begin(); i != mMessages.end(); i++) {
		delete i->second;
	}
	for(map<string, XSD *>::iterator i = mTypes.begin(); i != mTypes.end(); i++) {
		delete i->second;
	}
	for(map<string, WSDLPortType *>::iterator i = mPortTypes.begin(); i != mPortTypes.end(); i++) {
		delete i->second;
	}
}

vector<string> WSDL::get_MessageNames()
{
	vector<string> retval;

	for(map<string, WSDLMessage *>::iterator i = mMessages.begin(); i != mMessages.end(); i++) {
		retval.push_back(i->first);
	}

	return retval;
}

vector<string> WSDL::get_PortTypeNames()
{
	vector<string> retval;

	for (map<string, WSDLPortType *>::iterator i = mPortTypes.begin(); i != mPortTypes.end(); i++) {
		retval.push_back(i->first);
	}

	return retval;
}

vector<string> WSDL::get_TypeNamespaces()
{
	vector<string> retval;

	for (map<string, XSD *>::iterator i = mTypes.begin(); i != mTypes.end(); i++) {
		retval.push_back(i->first);
	}

	return retval;
}

WSDLMessage& WSDL::get_Message(string name) const
{
	return *(const_cast<WSDL *>(this)->mMessages[name]);
}

WSDLPortType& WSDL::get_PortType(string name) const
{
	return *(const_cast<WSDL *>(this)->mPortTypes[name]);
}

XSD& WSDL::get_Type(string ns) const
{
	return *(const_cast<WSDL *>(this)->mTypes[ns]);
}

void WSDL::Load(string filename)
{
	xmlDoc *doc = xmlReadFile(filename.c_str(), nullptr, 0);
	if(doc != nullptr) {
		mPath = ResolvePath(filename);
		Load(doc);
		xmlFreeDoc(doc);
	}
}

void WSDL::Load(xmlDocPtr document)
{
	xmlNode *node = xmlDocGetRootElement(document);
	if(node != nullptr) {
		Load(node);
	}
}

void WSDL::Load(xmlNodePtr node)
{
	LoadTypes(node);
	LoadMessages(node);
	LoadPortTypes(node);
	LoadBindings(node);
	LoadPorts(node);
	LoadServices(node);
}

void WSDL::LoadTypes(xmlNodePtr node)
{
	for(xmlNode *cur_node = node->children; cur_node != nullptr; cur_node = cur_node->next) {
		if (cur_node->type == XML_ELEMENT_NODE && !xmlStrcmp(cur_node->name, (const xmlChar *)"types")) {
			for (xmlNode *sub_node = cur_node->children; sub_node != nullptr; sub_node = sub_node->next) {
				if (sub_node->type == XML_ELEMENT_NODE && !xmlStrcmp(sub_node->name, (const xmlChar *)"schema")) {
					XSD *schema = new XSD(sub_node, mPath);
					if (schema != nullptr) {
						if (schema->get_Namespace().length() > 0) {
							mTypes[schema->get_Namespace()] = schema;
						}
						else {
							delete schema;
						}
					}
				}
			}
		}
	}
}

void WSDL::LoadMessages(xmlNodePtr node)
{
	for(xmlNode *cur_node = node->children; cur_node != nullptr; cur_node = cur_node->next) {
		if(cur_node->type == XML_ELEMENT_NODE && !xmlStrcmp(cur_node->name, (const xmlChar *)"message")) {
			WSDLMessage *message = new WSDLMessage(cur_node);
			if(message != nullptr) {
				if(message->get_Name().length() > 0) {
					mMessages[message->get_Name()] = message;
				}
				else {
					delete message;
				}
			}
		}
	}
}

void WSDL::LoadPortTypes(xmlNodePtr node)
{
	for(xmlNode *cur_node = node->children; cur_node != nullptr; cur_node = cur_node->next) {
		if(cur_node->type == XML_ELEMENT_NODE && !xmlStrcmp(cur_node->name, (const xmlChar *)"portType")) {
			WSDLPortType *portType = new WSDLPortType(cur_node);
			if(portType != nullptr) {
				if(portType->get_Name().length() > 0) {
					mPortTypes[portType->get_Name()] = portType;
				}
				else {
					delete portType;
				}
			}
		}
	}
}

void WSDL::LoadBindings(xmlNodePtr node)
{

}

void WSDL::LoadPorts(xmlNodePtr node)
{

}

void WSDL::LoadServices(xmlNodePtr node)
{

}

string WSDL::ResolvePath(string filename)
{
	return filename.substr(0, filename.find_last_of("/\\"));
}
