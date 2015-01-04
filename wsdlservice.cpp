#include "wsdlservice.h"

WSDLService::~WSDLService()
{
	for (map<string, WSDLPort *>::iterator i = mPorts.begin(); i != mPorts.end(); i++) {
		delete i->second;
	}
}

vector<string> WSDLService::get_PortNames()
{
	vector<string> retval;

	for (map<string, WSDLPort *>::iterator i = mPorts.begin(); i != mPorts.end(); i++) {
		retval.push_back(i->first);
	}

	return retval;
}