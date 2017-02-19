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
		xmlNsPtr ns = nullptr;
		xmlChar *type = xmlGetProp(node, (const xmlChar *)"type");
		if (type != nullptr) {
			mType = (char *)type;
			xmlFree(type);
			ns = FindNamespace(node, mType);
		}
		else {
			ns = FindNamespace(node);
		}
		if (ns != nullptr) {
			if (ns->href != nullptr) {
				mNamespace = (char *)ns->href;
			}
			if (ns->prefix != nullptr) {
				mPrefix = (char *)ns->prefix;
				if(mType.length() > 0) mType = mType.substr(mPrefix.length() + 1);
			}
		}
	}
}

xmlNsPtr XSDElement::FindNamespace(xmlNodePtr node, string type)
{
	xmlNsPtr retval = nullptr;
	size_t pos = type.find_first_of(':');
	if (pos != string::npos) {
		string prefix = type.substr(0, pos);
		retval = node->doc->children->nsDef;
		while (retval != nullptr) {
			if (retval->prefix != nullptr && prefix == (char *)retval->prefix) {
				break;
			}
			retval = retval->next;
		}
	}

	return retval;
}

xmlNsPtr XSDElement::FindNamespace(xmlNodePtr node)
{
	xmlNsPtr retval = nullptr;
	xmlChar *nsTmp = xmlGetProp(node->doc->children, (const xmlChar *)"targetNamespace");
	if (nsTmp != nullptr) {
		string ns = (char *)nsTmp;
		xmlFree(nsTmp);
		retval = node->doc->children->nsDef;
		while (retval != nullptr) {
			if (retval->href != nullptr && ns == (char *)retval->href) {
				break;
			}
			retval = retval->next;
		}
	}

	return retval;
}

XSDElement &XSDElement::operator=(const XSDElement &source)
{
	mName = source.mName;
	mType = source.mType;
	mNamespace = source.mNamespace;
	mPrefix = source.mPrefix;
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

string XSDElement::get_Namespace() const
{
	return mNamespace;
}

string XSDElement::get_Prefix() const
{
	return mPrefix;
}
