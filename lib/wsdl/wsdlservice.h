/******************************************************************************
 * Project: wsdl2cpp
 * File: lib/wsdl/wsdlservice.h
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#ifndef LIB_WSDL_WSDLSERVICE_H_
#define LIB_WSDL_WSDLSERVICE_H_

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <string>
#include <vector>
#include <map>

#include "lib/wsdl/wsdlport.h"

namespace wsdl2cpp {
namespace lib {
namespace wsdl {

class WSDLService {
 public:
    explicit WSDLService(xmlNodePtr node);
    ~WSDLService();

    ::std::string get_Name() const;
    ::std::vector<::std::string> get_PortNames();

 protected:
    void Load(xmlNodePtr node);
    void LoadPorts(xmlNodePtr node);

 private:
    ::std::string mName;
    ::std::map<::std::string, WSDLPort *> mPorts;

    WSDLService() = delete;
    WSDLService(const WSDLService &source) = delete;
    WSDLService operator=(const WSDLService &source) = delete;
};

}  // namespace wsdl
}  // namespace lib
}  // namespace wsdl2cpp

#endif  // LIB_WSDL_WSDLSERVICE_H_
