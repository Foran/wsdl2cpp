/******************************************************************************
 * Project: wsdl2cpp
 * File: lib/xsd/xsdcomplextype.h
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#include "lib/xsd/xsdcomplextype.h"

#include <string>

namespace wsdl2cpp {
namespace lib {
namespace xsd {

XSDComplexType::XSDComplexType(xmlNodePtr node) {
    Load(node);
}

XSDComplexType::XSDComplexType(const XSDComplexType &source) {
    *this = source;
}

XSDComplexType::~XSDComplexType() {
}

void XSDComplexType::Load(::xmlNodePtr node) {
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

::xmlNsPtr XSDComplexType::FindNamespace(::xmlNodePtr node) {
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

XSDComplexType &XSDComplexType::operator=(const XSDComplexType &source) {
    mName = source.mName;
    mNamespace = source.mNamespace;
    mPrefix = source.mPrefix;
    return *this;
}

::std::string XSDComplexType::get_Name() const {
    return mName;
}

::std::string XSDComplexType::get_Namespace() const {
    return mNamespace;
}

::std::string XSDComplexType::get_Prefix() const {
    return mPrefix;
}

}  // namespace xsd
}  // namespace lib
}  // namespace wsdl2cpp
