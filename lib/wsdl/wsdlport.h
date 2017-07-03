#ifndef LIB_WSDL_WSDLPORT_H_
#define LIB_WSDL_WSDLPORT_H_

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <string>

class WSDLPort {
 public:
    explicit WSDLPort(xmlNodePtr node);
    ~WSDLPort();

    string get_Name() const;
 protected:
    void Load(xmlNodePtr node);
 private:
    ::std::string mName;

    WSDLPort() = delete;
    WSDLPort(const WSDLPort &source) = delete;

    WSDLPort &operator=(const WSDLPort &source) = delete;
};

#endif  // LIB_WSDL_WSDLPORT_H_
