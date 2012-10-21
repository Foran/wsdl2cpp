#ifndef __WSDLPORTTYPE_H__
#define __WSDLPORTTYPE_H__

#include <string>
#include <vector>
#include <map>

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "wsdloperation.h"

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
		map<string, WSDLOperation *> mOperations;
		WSDLPortType();
		WSDLPortType(const WSDLPortType &source);
		WSDLPortType operator=(const WSDLPortType &source) const;
};

#endif
