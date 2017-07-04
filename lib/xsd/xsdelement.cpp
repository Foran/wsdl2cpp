/******************************************************************************
 * Project: wsdl2cpp
 * File: lib/xsd/xsdelement.cpp
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#include "lib/xsd/xsdelement.h"

#include <string>

namespace wsdl2cpp {
namespace lib {
namespace xsd {

XSDElement::XSDElement(::xmlNodePtr node) {
    Load(node);
}

XSDElement::XSDElement(const XSDElement &source) {
    *this = source;
}

XSDElement::~XSDElement() {
}

void XSDElement::Load(::xmlNodePtr node) {
    if (node != nullptr) {
        ::xmlChar *name = ::xmlGetProp(node, (const ::xmlChar *)"name");
        if (name != nullptr) {
            mName = reinterpret_cast<char *>(name);
            ::xmlFree(name);
        }
        ::xmlNsPtr ns = nullptr;
        ::xmlChar *type = ::xmlGetProp(node, (const ::xmlChar *)"type");
        if (type != nullptr) {
            mType = reinterpret_cast<char *>(type);
            ::xmlFree(type);
            ns = FindNamespace(node, mType);
        } else {
            ns = FindNamespace(node);
        }
        if (ns != nullptr) {
            if (ns->href != nullptr) {
                mNamespace = reinterpret_cast<const char *>(ns->href);
            }
            if (ns->prefix != nullptr) {
                mPrefix = reinterpret_cast<const char *>(ns->prefix);
                if (mType.length() > 0) {
                    mType = mType.substr(mPrefix.length() + 1);
                }
            }
        }
    }
}

::xmlNsPtr XSDElement::FindNamespace(::xmlNodePtr node, ::std::string type) {
    ::xmlNsPtr retval = nullptr;
    size_t pos = type.find_first_of(':');
    if (pos != ::std::string::npos) {
        ::std::string prefix = type.substr(0, pos);
        retval = node->doc->children->nsDef;
        while (retval != nullptr) {
            if (retval->prefix != nullptr &&
                prefix == reinterpret_cast<const char *>(retval->prefix)) {
                break;
            }
            retval = retval->next;
        }
    }

    return retval;
}

::xmlNsPtr XSDElement::FindNamespace(::xmlNodePtr node) {
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

XSDElement &XSDElement::operator=(const XSDElement &source) {
    mName = source.mName;
    mType = source.mType;
    mNamespace = source.mNamespace;
    mPrefix = source.mPrefix;
    return *this;
}

::std::string XSDElement::get_Name() const {
    return mName;
}

::std::string XSDElement::get_Type() const {
    return mType;
}

::std::string XSDElement::get_Namespace() const {
    return mNamespace;
}

::std::string XSDElement::get_Prefix() const {
    return mPrefix;
}

}  // namespace xsd
}  // namespace lib
}  // namespace wsdl2cpp
