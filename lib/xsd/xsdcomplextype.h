#ifndef __XSDCOMPLEXTYPE_H__
#define __XSDCOMPLEXTYPE_H__

#include <string>
#include <vector>

#include <libxml/parser.h>
#include <libxml/tree.h>

using namespace std;

class XSDComplexType
{
public:
	XSDComplexType(xmlNodePtr node);
	XSDComplexType(const XSDComplexType &source);
	~XSDComplexType();

	XSDComplexType &operator=(const XSDComplexType &source);

	string get_Name() const;
	string get_Namespace() const;
	string get_Prefix() const;
protected:
	void Load(xmlNodePtr node);
private:
	string mName;
	string mNamespace;
	string mPrefix;
	XSDComplexType();
	xmlNsPtr FindNamespace(xmlNodePtr node);
};

#endif
