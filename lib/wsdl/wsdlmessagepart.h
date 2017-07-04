#ifndef __WSDLMESSAGEPART_H__
#define __WSDLMESSAGEPART_H__

#include <string>
#include <vector>

#include <string.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

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

#endif
