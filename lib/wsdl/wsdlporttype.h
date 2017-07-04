/******************************************************************************
 * Project: wsdl2cpp
 * File: lib/wsdl/wsdlporttype.h
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#ifndef LIB_WSDL_WSDLPORTTYPE_H_
#define LIB_WSDL_WSDLPORTTYPE_H_

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <string>
#include <vector>
#include <map>

#include "lib/wsdl/wsdloperation.h"

namespace wsdl2cpp {
namespace lib {
namespace wsdl {

class WSDLPortType {
 public:
    explicit WSDLPortType(xmlNodePtr node);
    ~WSDLPortType();

    ::std::string get_Name() const;
    ::std::vector<::std::string> get_OperationNames();
    WSDLOperation& get_Operation(::std::string name) const;

 protected:
    void Load(xmlNodePtr node);
    void LoadOperations(xmlNodePtr node);

 private:
    ::std::string mName;
    ::std::map<::std::string, WSDLOperation *> mOperations;
    WSDLPortType();
    WSDLPortType(const WSDLPortType &source);
    WSDLPortType operator=(const WSDLPortType &source) const;
};

}  // namespace wsdl
}  // namespace lib
}  // namespace wsdl2cpp

#endif  // LIB_WSDL_WSDLPORTTYPE_H_
