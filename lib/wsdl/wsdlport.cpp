/******************************************************************************
 * Project: wsdl2cpp
 * File: lib/wsdl/wsdlport.cpp
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#include "lib/wsdl/wsdlport.h"

#include <string>

namespace wsdl2cpp {
namespace lib {
namespace wsdl {

WSDLPort::WSDLPort(::xmlNodePtr node) {
    Load(node);
}

WSDLPort::~WSDLPort() {
}

::std::string WSDLPort::get_Name() const {
    return mName;
}

void WSDLPort::Load(::xmlNodePtr node) {
    ::xmlChar *name = ::xmlGetProp(node, (const ::xmlChar *)"name");
    if (name != nullptr) {
        mName = reinterpret_cast<char *>(name);
        ::xmlFree(name);
    }
}

}  // namespace wsdl
}  // namespace lib
}  // namespace wsdl2cpp
