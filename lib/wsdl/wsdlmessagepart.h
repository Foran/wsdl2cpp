/******************************************************************************
 * Project: wsdl2cpp
 * File: lib/wsdl/wsdlmessagepart.h
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#ifndef LIB_WSDL_WSDLMESSAGEPART_H_
#define LIB_WSDL_WSDLMESSAGEPART_H_

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string.h>

#include <string>
#include <vector>

namespace wsdl2cpp {
namespace lib {
namespace wsdl {

class WSDLMessagePart {
 public:
    explicit WSDLMessagePart(xmlNodePtr node);
    ~WSDLMessagePart();

    ::std::string get_Name() const;
    ::std::string get_Element() const;

 protected:
    void Load(xmlNodePtr node);

 private:
    ::std::string mName;
    ::std::string mElement;
    WSDLMessagePart();
    WSDLMessagePart(const WSDLMessagePart &source);
    WSDLMessagePart operator=(const WSDLMessagePart &source) const;
};

}  // namespace wsdl
}  // namespace lib
}  // namespace wsdl2cpp

#endif  // LIB_WSDL_WSDLMESSAGEPART_H_
