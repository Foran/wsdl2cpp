#include "xsd.h"

XSD::XSD(string filename)
{
	mPath = "";
	Load(filename);
}

XSD::XSD(xmlDocPtr document)
{
	char path[FILENAME_MAX];
	GetCurrentDir(path, sizeof(path));
	mPath = path;
	Load(document);
}

XSD::XSD(xmlNodePtr node)
{
	char path[FILENAME_MAX];
	GetCurrentDir(path, sizeof(path));
	mPath = path;
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
   XSDElement *retval = new XSDElement(NULL);
   
   return *retval;
}

void XSD::Load(string filename)
{
	xmlDoc *doc = xmlReadFile(ResolvePath(filename).c_str(), NULL, 0);
	if(doc != NULL) {
		Load(doc);
		xmlFreeDoc(doc);
	}
}

void XSD::Load(xmlDocPtr document)
{
}

void XSD::Load(xmlNodePtr node)
{
	xmlChar *name = xmlGetProp(node, (const xmlChar *)"targetNamespace");
	if(name != NULL) {
		mNamespace = (char *)name;
		xmlFree(name);
		LoadElements(node);
		LoadImports(node);
	}
}

void XSD::LoadElements(xmlNodePtr node)
{
	for(xmlNode *cur_node = node->children; cur_node != NULL; cur_node = cur_node->next) {
		if(cur_node->type == XML_ELEMENT_NODE && !xmlStrcmp(cur_node->name, (const xmlChar *)"element")) {
			XSDElement *element = new XSDElement(cur_node);
			if(element != NULL) {
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
	for(xmlNode *cur_node = node->children; cur_node != NULL; cur_node = cur_node->next) {
		if(cur_node->type == XML_ELEMENT_NODE && !xmlStrcmp(cur_node->name, (const xmlChar *)"import")) {
			xmlChar *import = xmlGetProp(node, (const xmlChar *)"schemaLocation");
			if(import != NULL) {
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
	retval += filename;

	return retval;
}
