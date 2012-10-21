#ifndef __WSDLPORTTYPE_H__
#define __WSDLPORTTYPE_H__

#include <string>
#include <vector>

#include <libxml/parser.h>
#include <libxml/tree.h>

using namespace std;

class WSDLPortType {
	public:
		WSDLPortType(xmlNodePtr node);
		~WSDLPortType();
		
		string get_Name() const;
	protected:
		void Load(xmlNodePtr node);
	private:
		string mName;
		WSDLPortType();
		WSDLPortType(const WSDLPortType &source);
		WSDLPortType operator=(const WSDLPortType &source) const;
};

#endif
