/******************************************************************************
 * Project: wsdl2cpp
 * File: lib/wsdl/wsdlmessage.h
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#ifndef __WSDLMESSAGE_H__
#define __WSDLMESSAGE_H__

#include <string>
#include <vector>
#include <map>

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "lib/wsdl/wsdlmessagepart.h"

namespace wsdl2cpp {
namespace lib {
namespace wsdl {

class WSDLMessage {
 public:
    explicit WSDLMessage(xmlNodePtr node);
    ~WSDLMessage();

    ::std::string get_Name() const;
    ::std::vector<::std::string> get_PartNames();
    WSDLMessagePart &get_Part(::std::string name) const;

 protected:
    void Load(xmlNodePtr node);
    void LoadParts(xmlNodePtr node);

 private:
    ::std::string mName;
    ::std::map<::std::string, WSDLMessagePart *> mParts;
    WSDLMessage();
    WSDLMessage(const WSDLMessage &source);
    WSDLMessage operator=(const WSDLMessage &source) const;
};

}  // namespace wsdl
}  // namespace lib
}  // namespace wsdl2cpp

#endif
