/******************************************************************************
 * Project: wsdl2cpp
 * File: lib/xsd/xsdsimpletype.h
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#ifndef LIB_XSD_XSDSIMPLETYPE_H_
#define LIB_XSD_XSDSIMPLETYPE_H_

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <string>
#include <vector>

namespace wsdl2cpp {
namespace lib {
namespace xsd {

class XSDSimpleType {
 public:
    explicit XSDSimpleType(::xmlNodePtr node);
    XSDSimpleType(const XSDSimpleType &source);
    ~XSDSimpleType();

    XSDSimpleType &operator=(const XSDSimpleType &source);

    ::std::string get_Name() const;
    ::std::string get_Namespace() const;
    ::std::string get_Prefix() const;

 protected:
    void Load(::xmlNodePtr node);

 private:
    ::std::string mName;
    ::std::string mNamespace;
    ::std::string mPrefix;
    XSDSimpleType();
    ::xmlNsPtr FindNamespace(::xmlNodePtr node);
};

}  // namespace xsd
}  // namespace lib
}  // namespace wsdl2cpp

#endif  // LIB_XSD_XSDSIMPLETYPE_H_
