/******************************************************************************
 * Project: wsdl2cpp
 * File: lib/xsd/xsdelement.h
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#ifndef LIB_XSD_XSDELEMENT_H_
#define LIB_XSD_XSDELEMENT_H_

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <string>

namespace wsdl2cpp {
namespace lib {
namespace xsd {

class XSDElement {
 public:
    explicit XSDElement(::xmlNodePtr node);
    XSDElement(const XSDElement &source);
    ~XSDElement();

    XSDElement &operator=(const XSDElement &source);

    ::std::string get_Name() const;
    ::std::string get_Type() const;
    ::std::string get_Namespace() const;
    ::std::string get_Prefix() const;

 protected:
    void Load(::xmlNodePtr node);

 private:
    ::std::string mName;
    ::std::string mType;
    ::std::string mNamespace;
    ::std::string mPrefix;
    XSDElement();
    ::xmlNsPtr FindNamespace(::xmlNodePtr node, ::std::string type);
    ::xmlNsPtr FindNamespace(::xmlNodePtr node);
};

}  // namespace xsd
}  // namespace lib
}  // namespace wsdl2cpp

#endif  // LIB_XSD_XSDELEMENT_H_
