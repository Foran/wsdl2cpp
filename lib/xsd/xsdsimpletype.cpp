/******************************************************************************
 * Project: wsdl2cpp
 * File: lib/xsd/xsdsimpletype.cpp
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#include "lib/xsd/xsdsimpletype.h"

#include <string>

namespace wsdl2cpp {
namespace lib {
namespace xsd {

XSDSimpleType::XSDSimpleType(::xmlNodePtr node) {
    Load(node);
}

XSDSimpleType::XSDSimpleType(const XSDSimpleType &source) {
    *this = source;
}

XSDSimpleType::~XSDSimpleType() {
}

void XSDSimpleType::Load(::xmlNodePtr node) {
    if (node != nullptr) {
        ::xmlChar *name = ::xmlGetProp(node, (const ::xmlChar *)"name");
        if (name != nullptr) {
            mName = reinterpret_cast<char *>(name);
            ::xmlFree(name);
        }
        ::xmlNsPtr ns = FindNamespace(node);
        if (ns != nullptr) {
            if (ns->href != nullptr) {
                mNamespace = reinterpret_cast<const char *>(ns->href);
            }
            if (ns->prefix != nullptr) {
                mPrefix = reinterpret_cast<const char *>(ns->prefix);
            }
        }
    }
}

::xmlNsPtr XSDSimpleType::FindNamespace(::xmlNodePtr node) {
    ::xmlNsPtr retval = nullptr;
    ::xmlChar *nsTmp = ::xmlGetProp(node->doc->children,
                                    (const ::xmlChar *)"targetNamespace");
    if (nsTmp != nullptr) {
        ::std::string ns = reinterpret_cast<char *>(nsTmp);
        ::xmlFree(nsTmp);
        retval = node->doc->children->nsDef;
        while (retval != nullptr) {
            if (retval->href != nullptr &&
                ns == reinterpret_cast<const char *>(retval->href)) {
                break;
            }
            retval = retval->next;
        }
    }

    return retval;
}

XSDSimpleType &XSDSimpleType::operator=(const XSDSimpleType &source) {
    mName = source.mName;
    mNamespace = source.mNamespace;
    mPrefix = source.mPrefix;
    return *this;
}

::std::string XSDSimpleType::get_Name() const {
    return mName;
}

::std::string XSDSimpleType::get_Namespace() const {
    return mNamespace;
}

::std::string XSDSimpleType::get_Prefix() const {
    return mPrefix;
}

}  // namespace xsd
}  // namespace lib
}  // namespace wsdl2cpp
