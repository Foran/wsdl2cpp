/******************************************************************************
 * Project: wsdl2cpp
 * File: lib/wsdl/wsdloperation.cpp
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#include "lib/wsdl/wsdloperation.h"

#include <string>

namespace wsdl2cpp {
namespace lib {
namespace wsdl {

WSDLOperation::WSDLOperation(::xmlNodePtr node) {
    Load(node);
}

WSDLOperation::~WSDLOperation() {
}

::std::string WSDLOperation::get_Name() const {
    return mName;
}

::std::string WSDLOperation::get_InputMessageName() const {
    return mInput;
}

::std::string WSDLOperation::get_InputAction() const {
    return mInputAction;
}

::std::string WSDLOperation::get_OutputMessageName() const {
    return mOutput;
}

::std::string WSDLOperation::get_OutputAction() const {
    return mOutputAction;
}

void WSDLOperation::Load(::xmlNodePtr node) {
    ::xmlChar *name = ::xmlGetProp(node, (const ::xmlChar *)"name");
    if (name != nullptr) {
        mName = reinterpret_cast<char *>(name);
        ::xmlFree(name);
        LoadInput(node);
        LoadOutput(node);
    }
}

void WSDLOperation::LoadInput(::xmlNodePtr node) {
    int count = 0;
    for (::xmlNode *cur_node = node->children; cur_node != nullptr;
         cur_node = cur_node->next) {
        if (cur_node->type == ::XML_ELEMENT_NODE &&
            !::xmlStrcmp(cur_node->name, (const ::xmlChar *)"input")) {
            count++;
            ::xmlChar *message = ::xmlGetProp(cur_node,
                                              (const ::xmlChar *)"message");
            if (message != nullptr) {
                char *ch = ::strstr(reinterpret_cast<char *>(message), ":");
                if (ch == nullptr) {
                    ch = reinterpret_cast<char *>(message);
                } else {
                    ch++;
                }
                mInput = ch;
                ::xmlFree(message);
            }
            ::xmlChar *action = ::xmlGetProp(cur_node,
                                             (const ::xmlChar *)"Action");
            if (action != nullptr) {
                mInputAction = reinterpret_cast<char *>(action);
                ::xmlFree(action);
            }
        }
    }
}

void WSDLOperation::LoadOutput(::xmlNodePtr node) {
    int count = 0;
    for (::xmlNode *cur_node = node->children; cur_node != nullptr;
         cur_node = cur_node->next) {
        if (cur_node->type == ::XML_ELEMENT_NODE &&
            !::xmlStrcmp(cur_node->name, (const ::xmlChar *)"output")) {
            count++;
            ::xmlChar *message = ::xmlGetProp(cur_node,
                                              (const ::xmlChar *)"message");
            if (message != nullptr) {
                char *ch = ::strstr(reinterpret_cast<char *>(message), ":");
                if (ch == nullptr) {
                    ch = reinterpret_cast<char *>(message);
                } else {
                    ch++;
                }
                mOutput = ch;
                ::xmlFree(message);
            }
            ::xmlChar *action = ::xmlGetProp(cur_node,
                                             (const ::xmlChar *)"Action");
            if (action != nullptr) {
                mOutputAction = reinterpret_cast<char *>(action);
                ::xmlFree(action);
            }
        }
    }
}

}  // namespace wsdl
}  // namespace lib
}  // namespace wsdl2cpp
