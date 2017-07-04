/******************************************************************************
 * Project: wsdl2cpp
 * File: lib/xsd/xsdcomplextype.h
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#ifndef LIB_XSD_XSDCOMPLEXTYPE_H_
#define LIB_XSD_XSDCOMPLEXTYPE_H_

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <string>

namespace wsdl2cpp {
namespace lib {
namespace xsd {

class XSDComplexType {
 public:
    explicit XSDComplexType(::xmlNodePtr node);
    XSDComplexType(const XSDComplexType &source);
    ~XSDComplexType();

    XSDComplexType &operator=(const XSDComplexType &source);

    ::std::string get_Name() const;
    ::std::string get_Namespace() const;
    ::std::string get_Prefix() const;

 protected:
    void Load(::xmlNodePtr node);

 private:
    ::std::string mName;
    ::std::string mNamespace;
    ::std::string mPrefix;
    XSDComplexType();
    ::xmlNsPtr FindNamespace(::xmlNodePtr node);
};

}  // namespace xsd
}  // namespace lib
}  // namespace wsdl2cpp

#endif  // LIB_XSD_XSDCOMPLEXTYPE_H_
