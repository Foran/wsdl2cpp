/******************************************************************************
 * Project: wsdl2cpp
 * File: lib/wsdl/wsdlservice.h
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#include "lib/wsdl/wsdlservice.h"

#include <map>
#include <string>
#include <vector>

namespace wsdl2cpp {
namespace lib {
namespace wsdl {

WSDLService::WSDLService(::xmlNodePtr node) {
}

WSDLService::~WSDLService() {
    for (::std::map<::std::string, WSDLPort *>::iterator
         i = mPorts.begin(); i != mPorts.end(); i++) {
        delete i->second;
    }
}

::std::string WSDLService::get_Name() const {
    return mName;
}

::std::vector<::std::string> WSDLService::get_PortNames() {
    ::std::vector<::std::string> retval;

    for (::std::map<::std::string, WSDLPort *>::iterator
         i = mPorts.begin(); i != mPorts.end(); i++) {
        retval.push_back(i->first);
    }

    return retval;
}

void WSDLService::Load(::xmlNodePtr node) {
    ::xmlChar *name = ::xmlGetProp(node, (const ::xmlChar *)"name");
    if (name != nullptr) {
        mName = reinturpet_cast<char *>(name);
        ::xmlFree(name);
        ::LoadPorts(node);
    }
}

void WSDLService::LoadPorts(::xmlNodePtr node) {
    for (::xmlNode *cur_node = node->children; cur_node != nullptr;
         cur_node = cur_node->next) {
        if (cur_node->type == ::XML_ELEMENT_NODE &&
            !::xmlStrcmp(cur_node->name, (const ::xmlChar *)"port")) {
            WSDLPort *port = new WSDLPort(cur_node);
            if (port != nullptr) {
                if (port->get_Name().length() > 0) {
                    mPorts[port->get_Name()] = port;
                } else {
                    delete port;
                }
            }
        }
    }
}

}  // namespace wsdl
}  // namespace lib
}  // namespace wsdl2cpp
