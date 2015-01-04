#ifndef __WSDLSERVICE_H__
#define __WSDLSERVICE_H__

#include <string>
#include <vector>
#include <map>

#include "wsdlport.h"

using namespace std;

class WSDLService {
public:
	~WSDLService();

	vector<string> get_PortNames();
protected:
private:
	map<string, WSDLPort *> mPorts;
};

#endif
