#include "xsd.h"

XSD::XSD(string filename)
{
	mPath = "";
	Load(filename);
}

XSD::XSD(xmlDocPtr document)
{
	char path[FILENAME_MAX];
	if (GetCurrentDir(path, sizeof(path)) > 0) {
		mPath = path;
	}
	else {
		mPath = "";
	}
	Load(document);
}

XSD::XSD(xmlNodePtr node)
{
	char path[FILENAME_MAX];
	if (GetCurrentDir(path, sizeof(path)) > 0) {
		mPath = path;
	}
	else {
		mPath = "";
	}
	Load(node);
}

XSD::XSD(xmlDocPtr document, string path)
{
	mPath = path;
	Load(document);
}

XSD::XSD(xmlNodePtr node, string path)
{
	mPath = path;
	Load(node);
}

XSD::~XSD()
{
	for (map<string, XSDElement *>::iterator p = mElements.begin(); p != mElements.end(); p++) {
		delete p->second;
	}
}

string XSD::get_Namespace() const
{
	return mNamespace;
}

vector<string> XSD::get_ElementNames() 
{
   vector<string> retval;
   
   return retval;
}

XSDElement &XSD::get_Element(string name) 
{
   XSDElement *retval = new XSDElement(nullptr);
   
   return *retval;
}

void XSD::Load(string filename)
{
	xmlDoc *doc = xmlReadFile(ResolvePath(filename).c_str(), nullptr, 0);
	if(doc != nullptr) {
		Load(doc);
		xmlFreeDoc(doc);
	}
}

void XSD::Load(xmlDocPtr document)
{
	if (document != nullptr) {
		Load(document->children);
	}
}

void XSD::Load(xmlNodePtr node)
{
	xmlChar *name = xmlGetProp(node, (const xmlChar *)"targetNamespace");
	if(name != nullptr) {
		mNamespace = (char *)name;
		xmlFree(name);
		LoadElements(node);
		LoadImports(node);
	}
}

void XSD::LoadElements(xmlNodePtr node)
{
	for(xmlNode *cur_node = node->children; cur_node != nullptr; cur_node = cur_node->next) {
		if(cur_node->type == XML_ELEMENT_NODE && !xmlStrcmp(cur_node->name, (const xmlChar *)"element")) {
			XSDElement *element = new XSDElement(cur_node);
			if(element != nullptr) {
				if(element->get_Name().length() > 0) {
					mElements[element->get_Name()] = element;
				}
				else {
					delete element;
				}
			}
		}
	}
}

void XSD::LoadImports(xmlNodePtr node)
{
	for(xmlNode *cur_node = node->children; cur_node != nullptr; cur_node = cur_node->next) {
		if(cur_node->type == XML_ELEMENT_NODE && !xmlStrcmp(cur_node->name, (const xmlChar *)"import")) {
			xmlChar *import = xmlGetProp(cur_node, (const xmlChar *)"schemaLocation");
			if(import != nullptr) {
				XSD temp(ResolvePath((char *)import));
				xmlFree(import);
			}
		}
	}
}

string XSD::ResolvePath(string filename)
{
	string retval = "";

	if(filename[0] != '/' && filename[0] != '\\' && filename[1] != ':') retval = mPath;
	if (retval.length() > 0) {
#ifdef _WIN32
		retval += '\\';
#else
		retval += '/';
#endif
	}
	retval += filename;

	return retval;
}
