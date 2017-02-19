#ifndef __XSDSIMPLETYPE_H__
#define __XSDSIMPLETYPE_H__

#include <string>
#include <vector>

#include <libxml/parser.h>
#include <libxml/tree.h>

using namespace std;

class XSDSimpleType
{
public:
	XSDSimpleType(xmlNodePtr node);
	XSDSimpleType(const XSDSimpleType &source);
	~XSDSimpleType();

	XSDSimpleType &operator=(const XSDSimpleType &source);

	string get_Name() const;
	string get_Namespace() const;
	string get_Prefix() const;
protected:
	void Load(xmlNodePtr node);
private:
	string mName;
	string mNamespace;
	string mPrefix;
	XSDSimpleType();
	xmlNsPtr FindNamespace(xmlNodePtr node);
};

#endif
