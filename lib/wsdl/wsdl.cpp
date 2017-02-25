#include "wsdl.h"

#include "curl/curl.h"
#include <iostream>

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

XSDElement& WSDL::get_Type(string name) const
{
	string elementName = name;
	string ns = "";
	size_t pos = name.find_first_of(':');
	if (pos != string::npos) {
		elementName = name.substr(pos + 1);
		ns = name.substr(0, pos);
	}
	for (auto& kv : mTypes) {
		for (string name : kv.second->get_ElementNames()) {
			if (name == elementName) {
				return kv.second->get_Element(elementName);
			}
		}
	}
	return (const_cast<WSDL *>(this)->mTypes[ns])->get_Element(name);
}

size_t WSDL::curl_write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	((string *)userdata)->append(ptr, size * nmemb);
	return size * nmemb;
}

string WSDL::FetchFile(const Path &unc) const
{
	string retval = "";
	CURL *ch = curl_easy_init();
	if (ch) {
	   std::cout << "Fetching " << unc.get_UNC() << "..." << endl;
		curl_easy_setopt(ch, CURLOPT_URL, unc.get_UNC().c_str());
		curl_easy_setopt(ch, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(ch, CURLOPT_SSL_VERIFYHOST, false);
		curl_easy_setopt(ch, CURLOPT_WRITEDATA, &retval);
		curl_easy_setopt(ch, CURLOPT_WRITEFUNCTION, WSDL::curl_write_callback);
		if (CURLE_OK != curl_easy_perform(ch)) {
			retval = "";
		}
		curl_easy_cleanup(ch);
	}

	return retval;
}

void WSDL::Load(string filename)
{
	Path path(filename);
	string buffer = FetchFile(path);
	xmlDoc *doc = xmlReadMemory(buffer.c_str(), buffer.length(), "noname.xml", nullptr, 0);
	if (doc != nullptr) {
		mPath = path.get_BasePath();
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
   cout << "Loading Imports..." << endl;
	LoadImports(node);
   cout << "Loading Types..." << endl;
	LoadTypes(node);
   cout << "Loading Messages..." << endl;
	LoadMessages(node);
   cout << "Loading PortTypes..." << endl;
	LoadPortTypes(node);
   cout << "Loading Bindings..." << endl;
	LoadBindings(node);
   cout << "Loading Ports..." << endl;
	LoadPorts(node);
   cout << "Loading Services..." << endl;
	LoadServices(node);
}

void WSDL::LoadImports(xmlNodePtr node)
{
	for (xmlNode *cur_node = node->children; cur_node != nullptr; cur_node = cur_node->next) {
		if (cur_node->type == XML_ELEMENT_NODE && !xmlStrcmp(cur_node->name, (const xmlChar *)"import")) {
			string location;
			xmlChar *xmlLocation = xmlGetProp(cur_node, (const xmlChar *)"location");
			if (xmlLocation != nullptr) {
				location = (char *)xmlLocation;
				xmlFree(xmlLocation);
			}
			WSDL wsdl(Path::ResolveRelative(mPath.get_BasePath(), location).get_UNC());
			for (string binding : wsdl.mBindings) {
				mBindings.push_back(binding);
			}
			wsdl.mBindings.clear();
			for (auto message_entry : wsdl.mMessages) {
				mMessages[message_entry.first] = message_entry.second;
			}
			wsdl.mMessages.clear();
			for (string port : wsdl.mPorts) {
				mPorts.push_back(port);
			}
			wsdl.mPorts.clear();
			for (auto porttype_entry : wsdl.mPortTypes) {
				mPortTypes[porttype_entry.first] = porttype_entry.second;
			}
			wsdl.mPortTypes.clear();
			for (string service : wsdl.mServices) {
				mServices.push_back(service);
			}
			wsdl.mServices.clear();
			for (auto type_entry : wsdl.mTypes) {
				mTypes[type_entry.first] = type_entry.second;
			}
			wsdl.mTypes.clear();
		}
	}
}

void WSDL::LoadTypes(xmlNodePtr node)
{
	for (xmlNode *cur_node = node->children; cur_node != nullptr; cur_node = cur_node->next) {
		if (cur_node->type == XML_ELEMENT_NODE && !xmlStrcmp(cur_node->name, (const xmlChar *)"types")) {
			for (xmlNode *sub_node = cur_node->children; sub_node != nullptr; sub_node = sub_node->next) {
				if (sub_node->type == XML_ELEMENT_NODE && !xmlStrcmp(sub_node->name, (const xmlChar *)"schema")) {
					XSD *schema = new XSD(sub_node, mPath.get_UNC());
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
