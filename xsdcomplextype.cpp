#include "xsdcomplextype.h"

XSDComplexType::XSDComplexType(xmlNodePtr node)
{
	Load(node);
}

XSDComplexType::XSDComplexType(const XSDComplexType &source)
{
	*this = source;
}

XSDComplexType::~XSDComplexType()
{
}

void XSDComplexType::Load(xmlNodePtr node)
{
	if (node != nullptr) {
		xmlChar *name = xmlGetProp(node, (const xmlChar *)"name");
		if (name != nullptr) {
			mName = (char *)name;
			xmlFree(name);
		}
		xmlNsPtr ns = FindNamespace(node);
		if (ns != nullptr) {
			if (ns->href != nullptr) {
				mNamespace = (char *)ns->href;
			}
			if (ns->prefix != nullptr) {
				mPrefix = (char *)ns->prefix;
			}
		}
	}
}

xmlNsPtr XSDComplexType::FindNamespace(xmlNodePtr node)
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

XSDComplexType &XSDComplexType::operator=(const XSDComplexType &source)
{
	mName = source.mName;
	mNamespace = source.mNamespace;
	mPrefix = source.mPrefix;
	return *this;
}

string XSDComplexType::get_Name() const
{
	return mName;
}

string XSDComplexType::get_Namespace() const
{
	return mNamespace;
}

string XSDComplexType::get_Prefix() const
{
	return mPrefix;
}
