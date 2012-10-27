#ifndef __XSDELEMENT_H__
#define __XSDELEMENT_H__

#include <string>
#include <vector>

#include <libxml/parser.h>
#include <libxml/tree.h>

using namespace std;

class XSDElement
{
	public:
		XSDElement(xmlNodePtr node);
		XSDElement(const XSDElement &source);
		~XSDElement();

		XSDElement &operator=(const XSDElement &source);

		string get_Name() const;
	protected:
		void Load(xmlNodePtr node);
	private:
		string mName;
		XSDElement();
};

#endif
