/******************************************************************************
 * Project: wsdl2cpp
 * File: lib/wsdl/wsdlporttype.cpp
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#include "lib/wsdl/wsdlporttype.h"

#include <map>
#include <string>
#include <vector>

namespace wsdl2cpp {
namespace lib {
namespace wsdl {

WSDLPortType::WSDLPortType(::xmlNodePtr node) {
    Load(node);
}

WSDLPortType::~WSDLPortType() {
    for (::std::map<::std::string, WSDLOperation *>::iterator
         i = mOperations.begin(); i != mOperations.end(); i++) {
        delete i->second;
    }
}

::std::string WSDLPortType::get_Name() const {
    return mName;
}

::std::vector<::std::string> WSDLPortType::get_OperationNames() {
    ::std::vector<::std::string> retval;

    for (::std::map<::std::string, WSDLOperation *>::iterator
         i = mOperations.begin(); i != mOperations.end(); i++) {
        retval.push_back(i->first);
    }

    return retval;
}

WSDLOperation& WSDLPortType::get_Operation(::std::string name) const {
    return *(const_cast<WSDLPortType *>(this)->mOperations[name]);
}

void WSDLPortType::Load(::xmlNodePtr node) {
    ::xmlChar *name = ::xmlGetProp(node, (const ::xmlChar *)"name");
    if (name != nullptr) {
        mName = reinterpret_cast<char *>(name);
        ::xmlFree(name);
        LoadOperations(node);
    }
}

void WSDLPortType::LoadOperations(::xmlNodePtr node) {
    for (::xmlNode *cur_node = node->children; cur_node != nullptr;
         cur_node = cur_node->next) {
        if (cur_node->type == ::XML_ELEMENT_NODE &&
            !::xmlStrcmp(cur_node->name, (const ::xmlChar *)"operation")) {
            WSDLOperation *operation = new WSDLOperation(cur_node);
            if (operation != nullptr) {
                if (operation->get_Name().length() > 0) {
                    mOperations[operation->get_Name()] = operation;
                } else {
                    delete operation;
                }
            }
        }
    }
}

}  // namespace wsdl
}  // namespace lib
}  // namespace wsdl2cpp
