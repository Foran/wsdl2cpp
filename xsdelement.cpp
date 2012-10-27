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
}

XSDElement &XSDElement::operator=(const XSDElement &source)
{
	return *this;
}

string XSDElement::get_Name() const
{
	return mName;
}
