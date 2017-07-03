#include "lib/wsdl/wsdlmessage.h"

#include <map>
#include <string>
#include <vector>

WSDLMessage::WSDLMessage(xmlNodePtr node) {
    Load(node);
}

WSDLMessage::~WSDLMessage() {
    for (::std::map<::std::string, WSDLMessagePart *>::iterator
         i = mParts.begin(); i != mParts.end(); i++) {
        delete i->second;
    }
}

::std::string WSDLMessage::get_Name() const {
    return mName;
}

::std::vector<::std::string> WSDLMessage::get_PartNames() {
    ::std::vector<::std::string> retval;

    for (::std::map<::std::string, WSDLMessagePart *>::iterator
         i = mParts.begin(); i != mParts.end(); i++) {
        retval.push_back(i->first);
    }

    return retval;
}

WSDLMessagePart &WSDLMessage::get_Part(::std::string name) const {
    return *(const_cast<WSDLMessage *>(this)->mParts[name]);
}

void WSDLMessage::Load(xmlNodePtr node) {
    xmlChar *name = xmlGetProp(node, (const xmlChar *)"name");
    if (name != nullptr) {
        mName = reinterpret_cast<char *>(name);
        xmlFree(name);
        LoadParts(node);
    }
}

void WSDLMessage::LoadParts(xmlNodePtr node) {
    for (xmlNode *cur_node = node->children; cur_node != nullptr;
         cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE &&
            !xmlStrcmp(cur_node->name, (const xmlChar *)"part")) {
            WSDLMessagePart *part = new WSDLMessagePart(cur_node);
            if (part != nullptr) {
                if (part->get_Name().length() > 0) {
                    mParts[part->get_Name()] = part;
                } else {
                    delete part;
                }
            }
        }
    }
}
