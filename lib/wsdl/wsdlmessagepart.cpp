/******************************************************************************
 * Project: wsdl2cpp
 * File: lib/wsdl/wsdlmessagepart.cpp
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#include "lib/wsdl/wsdlmessagepart.h"

#include <string>

namespace wsdl2cpp {
namespace lib {
namespace wsdl {

WSDLMessagePart::WSDLMessagePart(xmlNodePtr node) {
    Load(node);
}

WSDLMessagePart::~WSDLMessagePart() {
}

::std::string WSDLMessagePart::get_Name() const {
    return mName;
}

::std::string WSDLMessagePart::get_Element() const {
    return mElement;
}

void WSDLMessagePart::Load(xmlNodePtr node) {
    xmlChar *name = xmlGetProp(node, (const xmlChar *)"name");
    if (name != nullptr) {
        mName = reinterpret_cast<char *>(name);
        xmlFree(name);
    }
    xmlChar *element = xmlGetProp(node, (const xmlChar *)"element");
    if (element != nullptr) {
        mElement = reinterpret_cast<char *>(element);
        xmlFree(element);
    }
}

}  // namespace wsdl
}  // namespace lib
}  // namespace wsdl2cpp
