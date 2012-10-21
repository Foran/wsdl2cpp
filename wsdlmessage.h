#ifndef __WSDLMESSAGE_H__
#define __WSDLMESSAGE_H__

#include <string>
#include <vector>
#include <map>

#include <libxml/parser.h>
#include <libxml/tree.h>

using namespace std;

class WSDLMessage {
	public:
		WSDLMessage(xmlNodePtr node);
		~WSDLMessage();
		
		string get_Name() const;
	protected:
		void Load(xmlNodePtr node);
	private:
		string mName;
		map<string, WSDLMessagePart *> mParts;
		WSDLMessage();
		WSDLMessage(const WSDLMessage &source);
		WSDLMessage operator=(const WSDLMessage &source) const;
};

#endif
