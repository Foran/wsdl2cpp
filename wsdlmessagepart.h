#ifndef __WSDLMESSAGEPART_H__
#define __WSDLMESSAGEPART_H__

#include <string>
#include <vector>

#include <libxml/parser.h>
#include <libxml/tree.h>

using namespace std;

class WSDLMessagePart {
	public:
		WSDLMessagePart(xmlNodePtr node);
		~WSDLMessagePart();
		
		string get_Name() const;
		string get_Element() const;
	protected:
		void Load(xmlNodePtr node);
	private:
		string mName;
		string mElement;
		WSDLMessagePart();
		WSDLMessagePart(const WSDLMessagePart &source);
		WSDLMessagePart operator=(const WSDLMessagePart &source) const;
};

#endif
