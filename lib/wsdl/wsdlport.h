/******************************************************************************
 * Project: wsdl2cpp
 * File: lib/wsdl/wsdlport.h
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#ifndef LIB_WSDL_WSDLPORT_H_
#define LIB_WSDL_WSDLPORT_H_

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <string>

namespace wsdl2cpp {
namespace lib {
namespace wsdl {

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

}  // namespace wsdl
}  // namespace lib
}  // namespace wsdl2cpp

#endif  // LIB_WSDL_WSDLPORT_H_
