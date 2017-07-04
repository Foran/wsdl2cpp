/******************************************************************************
 * Project: wsdl2cpp
 * File: lib/wsdl/wsdl.cpp
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#include "lib/wsdl/wsdl.h"

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "curl/curl.h"

namespace wsdl2cpp {
namespace lib {
namespace wsdl {

using ::wsdl2cpp::lib::path::Path;
using ::wsdl2cpp::lib::xsd::XSD;

WSDL::WSDL(::std::string filename) {
    Load(filename);
}

WSDL::WSDL(::xmlDocPtr document) {
    Load(document);
}

WSDL::WSDL(::xmlNodePtr node) {
    Load(node);
}

WSDL::~WSDL() {
    for (::std::map<::std::string, WSDLMessage *>::iterator
         i = mMessages.begin(); i != mMessages.end(); i++) {
        delete i->second;
    }
    for (::std::map<::std::string, XSD *>::iterator
         i = mTypes.begin(); i != mTypes.end(); i++) {
        delete i->second;
    }
    for (::std::map<::std::string, WSDLPortType *>::iterator
         i = mPortTypes.begin(); i != mPortTypes.end(); i++) {
        delete i->second;
    }
}

::std::vector<::std::string> WSDL::get_MessageNames() {
    ::std::vector<::std::string> retval;

    for (::std::map<::std::string, WSDLMessage *>::iterator
         i = mMessages.begin(); i != mMessages.end(); i++) {
        retval.push_back(i->first);
    }

    return retval;
}

::std::vector<::std::string> WSDL::get_PortTypeNames() {
    ::std::vector<::std::string> retval;

    for (::std::map<::std::string, WSDLPortType *>::iterator
         i = mPortTypes.begin(); i != mPortTypes.end(); i++) {
        retval.push_back(i->first);
    }

    return retval;
}

::std::vector<::std::string> WSDL::get_TypeNamespaces() {
    ::std::vector<::std::string> retval;

    for (::std::map<::std::string, ::wsdl2cpp::lib::xsd::XSD *>::iterator
         i = mTypes.begin(); i != mTypes.end(); i++) {
        retval.push_back(i->first);
    }

    return retval;
}

WSDLMessage& WSDL::get_Message(::std::string name) const {
    return *(const_cast<WSDL *>(this)->mMessages[name]);
}

WSDLPortType& WSDL::get_PortType(::std::string name) const {
    return *(const_cast<WSDL *>(this)->mPortTypes[name]);
}

::wsdl2cpp::lib::xsd::XSDElement& WSDL::get_Type(::std::string name) const {
    ::std::string elementName = name;
    ::std::string ns = "";
    size_t pos = name.find_first_of(':');
    if (pos != ::std::string::npos) {
        elementName = name.substr(pos + 1);
        ns = name.substr(0, pos);
    }
    for (auto& kv : mTypes) {
        for (::std::string name : kv.second->get_ElementNames()) {
            if (name == elementName) {
                return kv.second->get_Element(elementName);
            }
        }
    }
    return (const_cast<WSDL *>(this)->mTypes[ns])->get_Element(name);
}

size_t WSDL::curl_write_callback(char *ptr, size_t size, size_t nmemb,
                                 void *userdata) {
    ((::std::string *)userdata)->append(ptr, size * nmemb);
    return size * nmemb;
}

::std::string WSDL::FetchFile(const Path &unc) const {
    ::std::string retval = "";
    CURL *ch = curl_easy_init();
    if (ch) {
        ::std::cout << "Fetching " << unc.get_UNC() << "..." << ::std::endl;
        ::curl_easy_setopt(ch, ::CURLOPT_URL, unc.get_UNC().c_str());
        ::curl_easy_setopt(ch, ::CURLOPT_SSL_VERIFYPEER, false);
        ::curl_easy_setopt(ch, ::CURLOPT_SSL_VERIFYHOST, false);
        ::curl_easy_setopt(ch, ::CURLOPT_WRITEDATA, &retval);
        ::curl_easy_setopt(ch, ::CURLOPT_WRITEFUNCTION,
                           WSDL::curl_write_callback);
        if (::CURLE_OK != ::curl_easy_perform(ch)) {
            retval = "";
        }
        ::curl_easy_cleanup(ch);
    }

    return retval;
}

void WSDL::Load(::std::string filename) {
    Path path(filename);
    ::std::string buffer = FetchFile(path);
    ::xmlDoc *doc = ::xmlReadMemory(buffer.c_str(), buffer.length(),
                                    "noname.xml", nullptr, 0);
    if (doc != nullptr) {
        mPath = path.get_BasePath();
        Load(doc);
        ::xmlFreeDoc(doc);
    }
}

void WSDL::Load(::xmlDocPtr document) {
    ::xmlNode *node = ::xmlDocGetRootElement(document);
    if (node != nullptr) {
        Load(node);
    }
}

void WSDL::Load(::xmlNodePtr node) {
    ::std::cout << "Loading Imports..." << ::std::endl;
    LoadImports(node);
    ::std::cout << "Loading Types..." << ::std::endl;
    LoadTypes(node);
    ::std::cout << "Loading Messages..." << ::std::endl;
    LoadMessages(node);
    ::std::cout << "Loading PortTypes..." << ::std::endl;
    LoadPortTypes(node);
    ::std::cout << "Loading Bindings..." << ::std::endl;
    LoadBindings(node);
    ::std::cout << "Loading Ports..." << ::std::endl;
    LoadPorts(node);
    ::std::cout << "Loading Services..." << ::std::endl;
    LoadServices(node);
}

void WSDL::LoadImports(::xmlNodePtr node) {
    for (::xmlNode *cur_node = node->children; cur_node != nullptr;
         cur_node = cur_node->next) {
        if (cur_node->type == ::XML_ELEMENT_NODE &&
            !::xmlStrcmp(cur_node->name, (const ::xmlChar *)"import")) {
            ::std::string location;
            ::xmlChar *xmlLocation =
              ::xmlGetProp(cur_node, (const ::xmlChar *)"location");
            if (xmlLocation != nullptr) {
                location = reinterpret_cast<char *>(xmlLocation);
                ::xmlFree(xmlLocation);
            }
            WSDL wsdl(Path::ResolveRelative(mPath.get_BasePath(),
                                            location).get_UNC());
            for (::std::string binding : wsdl.mBindings) {
                mBindings.push_back(binding);
            }
            wsdl.mBindings.clear();
            for (auto message_entry : wsdl.mMessages) {
                mMessages[message_entry.first] = message_entry.second;
            }
            wsdl.mMessages.clear();
            for (::std::string port : wsdl.mPorts) {
                mPorts.push_back(port);
            }
            wsdl.mPorts.clear();
            for (auto porttype_entry : wsdl.mPortTypes) {
                mPortTypes[porttype_entry.first] = porttype_entry.second;
            }
            wsdl.mPortTypes.clear();
            for (::std::string service : wsdl.mServices) {
                mServices.push_back(service);
            }
            wsdl.mServices.clear();
            for (auto type_entry : wsdl.mTypes) {
                mTypes[type_entry.first] = type_entry.second;
            }
            wsdl.mTypes.clear();
        }
    }
}

void WSDL::LoadTypes(::xmlNodePtr node) {
    for (::xmlNode *cur_node = node->children; cur_node != nullptr;
         cur_node = cur_node->next) {
        if (cur_node->type == ::XML_ELEMENT_NODE &&
            !::xmlStrcmp(cur_node->name, (const ::xmlChar *)"types")) {
            for (::xmlNode *sub_node = cur_node->children; sub_node != nullptr;
                 sub_node = sub_node->next) {
                if (sub_node->type == ::XML_ELEMENT_NODE &&
                    !::xmlStrcmp(sub_node->name,
                                 (const ::xmlChar *)"schema")) {
                    XSD *schema = new XSD(sub_node, Path(mPath.get_UNC()));
                    if (schema != nullptr) {
                        if (schema->get_Namespace().length() > 0) {
                            mTypes[schema->get_Namespace()] = schema;
                        } else {
                            delete schema;
                        }
                    }
                }
            }
        }
    }
}

void WSDL::LoadMessages(::xmlNodePtr node) {
    for (::xmlNode *cur_node = node->children; cur_node != nullptr;
         cur_node = cur_node->next) {
        if (cur_node->type == ::XML_ELEMENT_NODE &&
            !::xmlStrcmp(cur_node->name, (const ::xmlChar *)"message")) {
            WSDLMessage *message = new WSDLMessage(cur_node);
            if (message != nullptr) {
                if (message->get_Name().length() > 0) {
                    mMessages[message->get_Name()] = message;
                } else {
                    delete message;
                }
            }
        }
    }
}

void WSDL::LoadPortTypes(::xmlNodePtr node) {
    for (::xmlNode *cur_node = node->children; cur_node != nullptr;
         cur_node = cur_node->next) {
        if (cur_node->type == ::XML_ELEMENT_NODE &&
            !::xmlStrcmp(cur_node->name, (const ::xmlChar *)"portType")) {
            WSDLPortType *portType = new WSDLPortType(cur_node);
            if (portType != nullptr) {
                if (portType->get_Name().length() > 0) {
                    mPortTypes[portType->get_Name()] = portType;
                } else {
                    delete portType;
                }
            }
        }
    }
}

void WSDL::LoadBindings(::xmlNodePtr node) {
}

void WSDL::LoadPorts(::xmlNodePtr node) {
}

void WSDL::LoadServices(::xmlNodePtr node) {
}

::std::string WSDL::ResolvePath(::std::string filename) {
    return filename.substr(0, filename.find_last_of("/\\"));
}

}  // namespace wsdl
}  // namespace lib
}  // namespace wsdl2cpp

