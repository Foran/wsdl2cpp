#ifndef __XSD_H__
#define __XSD_H__

#include <algorithm>
#include <string>
#include <vector>
#include <map>

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "xsdelement.h"
#include "xsdsimpletype.h"
#include "xsdcomplextype.h"

#include "path.h"

using namespace std;

class XSD
{
	public:
		XSD(string filename);
		XSD(xmlDocPtr document);
		XSD(xmlNodePtr node);
		XSD(xmlDocPtr document, Path path);
		XSD(xmlNodePtr node, Path path);
		~XSD();

		string get_Namespace() const;
		vector<string> get_ElementNames();
		XSDElement &get_Element(string name);
		vector<string> get_SimpleTypeNames();
		XSDSimpleType &get_SimpleType(string name);
		vector<string> get_ComplexTypeNames();
		XSDComplexType &get_ComplexType(string name);
protected:
		void Load(string filename);
		void Load(xmlDocPtr document);
		void Load(xmlNodePtr node);
		void LoadElements(xmlNodePtr node);
		void LoadSimpleTypes(xmlNodePtr node);
		void LoadComplexTypes(xmlNodePtr node);
		void LoadImports(xmlNodePtr node);
		string FetchFile(const Path &unc) const;
private:
		Path mPath;
		string mNamespace;
		string mPrefix;
		map<string, XSDElement *> mElements;
		map<string, XSDSimpleType *> mSimpleTypes;
		map<string, XSDComplexType *> mComplexTypes;
		XSD();
		XSD(const XSD &source);
		XSD operator=(const XSD &source) const;
		static size_t curl_write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);
};

#endif
