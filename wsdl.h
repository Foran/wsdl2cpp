#ifndef __WSDL_H__
#define __WSDL_H__

#include <string>
#include <vector>
#include <map>

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "wsdlmessage.h"
#include "wsdlporttype.h"
#include "xsd.h"

using namespace std;

class WSDL
{
	public:
		WSDL(string filename);
		WSDL(xmlDocPtr document);
		WSDL(xmlNodePtr node);
		~WSDL();

		vector<string> get_MessageNames();
		vector<string> get_PortTypeNames();
		vector<string> get_TypeNamespaces();
		WSDLMessage& get_Message(string name) const;
		WSDLPortType& get_PortType(string name) const;
		XSD& get_Type(string ns) const;
	protected:
		void Load(string filename);
		void Load(xmlDocPtr document);
		void Load(xmlNodePtr node);
		void LoadTypes(xmlNodePtr node);
		void LoadMessages(xmlNodePtr node);
		void LoadPortTypes(xmlNodePtr node);
		void LoadBindings(xmlNodePtr node);
		void LoadPorts(xmlNodePtr node);
		void LoadServices(xmlNodePtr node);
	private:
		map<string, XSD *> mTypes;
		map<string, WSDLMessage *> mMessages;
		map<string, WSDLPortType *> mPortTypes;
		vector<string> mBindings;
		vector<string> mPorts;
		vector<string> mServices;
		Path mPath;

		WSDL();
		WSDL(const WSDL &source);
		WSDL operator=(const WSDL &source) const;
		string ResolvePath(string filename);
};

#endif
