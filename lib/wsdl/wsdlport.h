#ifndef __WSDLPORT_H__
#define __WSDLPORT_H__

#include <string>

#include <libxml/parser.h>
#include <libxml/tree.h>

using namespace std;

class WSDLPort {
public:
	WSDLPort(xmlNodePtr node);
	~WSDLPort();

	string get_Name() const;
protected:
	void Load(xmlNodePtr node);
private:
	string mName;

	WSDLPort() = delete;
	WSDLPort(const WSDLPort &source) = delete;

	WSDLPort &operator=(const WSDLPort &source) = delete;
};

#endif
