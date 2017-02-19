#ifndef __WSDLMESSAGE_H__
#define __WSDLMESSAGE_H__

#include <string>
#include <vector>
#include <map>

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "wsdlmessagepart.h"

using namespace std;

class WSDLMessage {
	public:
		WSDLMessage(xmlNodePtr node);
		~WSDLMessage();
		
		string get_Name() const;
		vector<string> get_PartNames();
		WSDLMessagePart &get_Part(string name) const;
	protected:
		void Load(xmlNodePtr node);
		void LoadParts(xmlNodePtr node);
	private:
		string mName;
		map<string, WSDLMessagePart *> mParts;
		WSDLMessage();
		WSDLMessage(const WSDLMessage &source);
		WSDLMessage operator=(const WSDLMessage &source) const;
};

#endif
