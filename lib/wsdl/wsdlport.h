#ifndef LIB_WSDL_WSDLPORT_H_
#define LIB_WSDL_WSDLPORT_H_

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

#endif  // LIB_WSDL_WSDLPORT_H_
