/******************************************************************************
 * Project: wsdl2cpp
 * File: lib/wsdl/wsdl.h
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#ifndef LIB_WSDL_WSDL_H_
#define LIB_WSDL_WSDL_H_

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <map>
#include <string>
#include <vector>

#include "lib/wsdl/wsdlmessage.h"
#include "lib/wsdl/wsdlporttype.h"
#include "lib/xsd/xsd.h"

namespace wsdl2cpp {
namespace lib {
namespace wsdl {

class WSDL {
 public:
    explicit WSDL(::std::string filename);
    explicit WSDL(xmlDocPtr document);
    explicit WSDL(xmlNodePtr node);
    ~WSDL();

    ::std::vector<::std::string> get_MessageNames();
    ::std::vector<::std::string> get_PortTypeNames();
    ::std::vector<::std::string> get_TypeNamespaces();
    WSDLMessage& get_Message(::std::string name) const;
    WSDLPortType& get_PortType(::std::string name) const;
    XSDElement& get_Type(::std::string name) const;

 protected:
    void Load(::std::string filename);
    void Load(xmlDocPtr document);
    void Load(xmlNodePtr node);
    void LoadImports(xmlNodePtr node);
    void LoadTypes(xmlNodePtr node);
    void LoadMessages(xmlNodePtr node);
    void LoadPortTypes(xmlNodePtr node);
    void LoadBindings(xmlNodePtr node);
    void LoadPorts(xmlNodePtr node);
    void LoadServices(xmlNodePtr node);
    ::std::string FetchFile(const Path &unc) const;

 private:
    ::std::map<::std::string, XSD *> mTypes;
    ::std::map<::std::string, WSDLMessage *> mMessages;
    ::std::map<::std::string, WSDLPortType *> mPortTypes;
    ::std::vector<::std::string> mBindings;
    ::std::vector<::std::string> mPorts;
    ::std::vector<::std::string> mServices;
    Path mPath;

    WSDL();
    WSDL(const WSDL &source);
    WSDL operator=(const WSDL &source) const;
    ::std::string ResolvePath(::std::string filename);
    static size_t curl_write_callback(char *ptr, size_t size, size_t nmemb,
                                      void *userdata);
};

}  // namespace wsdl
}  // namespace lib
}  // namespace wsdl2cpp

#endif  // LIB_WSDL_WSDL_H_
