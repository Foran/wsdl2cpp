#ifndef __XSD_H__
#define __XSD_H__

#include <string>
#include <vector>

#include <libxml/parser.h>
#include <libxml/tree.h>

using namespace std;

class XSD
{
	public:
		XSD(string filename);
		XSD(xmlDocPtr document);
		XSD(xmlNodePtr node);
		~XSD();

	protected:
	private:
		XSD();
		XSD(const XSD &source);
		XSD operator=(const XSD &source) const;
};

#endif
