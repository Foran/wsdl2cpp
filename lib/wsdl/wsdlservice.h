#ifndef __WSDLSERVICE_H__
#define __WSDLSERVICE_H__

#include <string>
#include <vector>
#include <map>

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "wsdlport.h"

using namespace std;

class WSDLService {
public:
	WSDLService(xmlNodePtr node);
	~WSDLService();

	string get_Name() const;
	vector<string> get_PortNames();
protected:
	void Load(xmlNodePtr node);
	void LoadPorts(xmlNodePtr node);
private:
	string mName;
	map<string, WSDLPort *> mPorts;

	WSDLService() = delete;
	WSDLService(const WSDLService &source) = delete;
	WSDLService operator=(const WSDLService &source) = delete;
};

#endif
