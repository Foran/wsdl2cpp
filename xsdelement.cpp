#include "xsdelement.h"

XSDElement::XSDElement(xmlNodePtr node)
{
	Load(node);
}

XSDElement::XSDElement(const XSDElement &source)
{
	*this = source;
}

XSDElement::~XSDElement()
{
}

void XSDElement::Load(xmlNodePtr node)
{
	if (node != nullptr) {
		xmlChar *name = xmlGetProp(node, (const xmlChar *)"name");
		if (name != nullptr) {
			mName = (char *)name;
			xmlFree(name);
		}
		xmlChar *type = xmlGetProp(node, (const xmlChar *)"type");
		if (type != nullptr) {
			mType = (char *)type;
			xmlFree(type);
		}
	}
}

XSDElement &XSDElement::operator=(const XSDElement &source)
{
	mName = source.mName;
	mType = source.mType;
	return *this;
}

string XSDElement::get_Name() const
{
	return mName;
}

string XSDElement::get_Type() const
{
	return mType;
}
