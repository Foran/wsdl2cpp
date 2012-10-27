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

void XSD::Load(string filename)
{
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
	}
}

void XSD::LoadElements(xmlNodePtr node)
{
}
