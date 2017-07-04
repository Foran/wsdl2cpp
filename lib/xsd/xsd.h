/******************************************************************************
 * Project: wsdl2cpp
 * File: lib/xsd/xsd.h
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#ifndef LIB_XSD_XSD_H_
#define LIB_XSD_XSD_H_

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <map>
#include <string>
#include <vector>

#include "lib/path/path.h"
#include "lib/xsd/xsdelement.h"
#include "lib/xsd/xsdsimpletype.h"
#include "lib/xsd/xsdcomplextype.h"

namespace wsdl2cpp {
namespace lib {
namespace xsd {

class XSD {
 public:
    explicit XSD(::std::string filename);
    explicit XSD(::xmlDocPtr document);
    explicit XSD(::xmlNodePtr node);
    XSD(::xmlDocPtr document, ::wsdl2cpp::lib::path::Path path);
    XSD(::xmlNodePtr node, ::wsdl2cpp::lib::path::Path path);
    ~XSD();

    ::std::string get_Namespace() const;
    ::std::vector<::std::string> get_ElementNames();
    XSDElement &get_Element(::std::string name);
    ::std::vector<::std::string> get_SimpleTypeNames();
    XSDSimpleType &get_SimpleType(::std::string name);
    ::std::vector<::std::string> get_ComplexTypeNames();
    XSDComplexType &get_ComplexType(::std::string name);

 protected:
    void Load(::std::string filename);
    void Load(::xmlDocPtr document);
    void Load(::xmlNodePtr node);
    void LoadElements(::xmlNodePtr node);
    void LoadSimpleTypes(::xmlNodePtr node);
    void LoadComplexTypes(::xmlNodePtr node);
    void LoadImports(::xmlNodePtr node);
    ::std::string FetchFile(const ::wsdl2cpp::lib::path::Path &unc) const;

 private:
    ::wsdl2cpp::lib::path::Path mPath;
    ::std::string mNamespace;
    ::std::string mPrefix;
    ::std::map<::std::string, XSDElement *> mElements;
    ::std::map<::std::string, XSDSimpleType *> mSimpleTypes;
    ::std::map<::std::string, XSDComplexType *> mComplexTypes;
    XSD();
    XSD(const XSD &source);
    XSD operator=(const XSD &source) const;
    static size_t curl_write_callback(char *ptr, size_t size, size_t nmemb,
                                      void *userdata);
};

}  // namespace xsd
}  // namespace lib
}  // namespace wsdl2cpp

#endif  // LIB_XSD_XSD_H_
