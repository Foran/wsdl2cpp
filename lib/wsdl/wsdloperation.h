/******************************************************************************
 * Project: wsdl2cpp
 * File: lib/wsdl/wsdloperation.h
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#ifndef LIB_WSDL_WSDLOPERATION_H_
#define LIB_WSDL_WSDLOPERATION_H_

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string.h>

#include <string>
#include <vector>

namespace wsdl2cpp {
namespace lib {
namespace wsdl {

class WSDLOperation {
 public:
    explicit WSDLOperation(::xmlNodePtr node);
    ~WSDLOperation();

    ::std::string get_Name() const;
    ::std::string get_InputMessageName() const;
    ::std::string get_InputAction() const;
    ::std::string get_OutputMessageName() const;
    ::std::string get_OutputAction() const;

 protected:
    void Load(::xmlNodePtr node);
    void LoadInput(::xmlNodePtr node);
    void LoadOutput(::xmlNodePtr node);

 private:
    ::std::string mName;
    ::std::string mInput;
    ::std::string mInputAction;
    ::std::string mOutput;
    ::std::string mOutputAction;
    WSDLOperation();
    WSDLOperation(const WSDLOperation &source);
    WSDLOperation operator=(const WSDLOperation &source) const;
};

}  // namespace wsdl
}  // namespace lib
}  // namespace wsdl2cpp

#endif  // LIB_WSDL_WSDLOPERATION_H_
