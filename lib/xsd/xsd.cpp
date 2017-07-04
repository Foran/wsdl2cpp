/******************************************************************************
 * Project: wsdl2cpp
 * File: lib/xsd/xsd.cpp
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#include "lib/xsd/xsd.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "curl/curl.h"

namespace wsdl2cpp {
namespace lib {
namespace xsd {

using ::wsdl2cpp::lib::path::Path;

XSD::XSD(::std::string filename) {
    mPath = "";
    Load(filename);
}

XSD::XSD(::xmlDocPtr document) {
    mPath = Path::CurrentDirectory();
    Load(document);
}

XSD::XSD(::xmlNodePtr node) {
    mPath = Path::CurrentDirectory();
    Load(node);
}

XSD::XSD(::xmlDocPtr document, Path path) {
    mPath = path;
    Load(document);
}

XSD::XSD(::xmlNodePtr node, Path path) {
    mPath = path;
    Load(node);
}

XSD::~XSD() {
    for (::std::map<::std::string, XSDElement *>::iterator
         p = mElements.begin(); p != mElements.end(); p++) {
        delete p->second;
    }
    for (::std::map<::std::string, XSDSimpleType *>::iterator
         p = mSimpleTypes.begin(); p != mSimpleTypes.end(); p++) {
        delete p->second;
    }
    for (::std::map<::std::string, XSDComplexType *>::iterator
         p = mComplexTypes.begin(); p != mComplexTypes.end(); p++) {
        delete p->second;
    }
}

::std::string XSD::get_Namespace() const {
    return mNamespace;
}

::std::vector<::std::string> XSD::get_ElementNames() {
    ::std::vector<::std::string> retval;

    for (auto entry : mElements) {
        retval.push_back(entry.first);
    }

    return retval;
}

XSDElement &XSD::get_Element(::std::string name) {
    XSDElement *retval = new XSDElement(*mElements[name]);

    return *retval;
}

::std::vector<::std::string> XSD::get_SimpleTypeNames() {
    ::std::vector<::std::string> retval;

    for (auto entry : mSimpleTypes) {
        retval.push_back(entry.first);
    }

    return retval;
}

XSDSimpleType &XSD::get_SimpleType(::std::string name) {
    XSDSimpleType *retval = new XSDSimpleType(*mSimpleTypes[name]);

    return *retval;
}

::std::vector<::std::string> XSD::get_ComplexTypeNames() {
    ::std::vector<::std::string> retval;

    for (auto entry : mComplexTypes) {
        retval.push_back(entry.first);
    }

    return retval;
}

XSDComplexType &XSD::get_ComplexType(::std::string name) {
    XSDComplexType *retval = new XSDComplexType(*mComplexTypes[name]);

    return *retval;
}

void XSD::Load(::std::string filename) {
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

void XSD::Load(::xmlDocPtr document) {
    if (document != nullptr) {
        Load(document->children);
    }
}

void XSD::Load(::xmlNodePtr node) {
    ::std::cout << "Loading Schema..." << ::std::endl;
    if (node != nullptr) {
        ::xmlChar *ns = ::xmlGetProp(node,
                                     (const ::xmlChar *)"targetNamespace");
        if (ns != nullptr) {
            mNamespace = reinterpret_cast<char *>(ns);
            ::xmlFree(ns);
            ::xmlNsPtr nsptr = node->nsDef;
            while (nsptr != nullptr) {
                if (nsptr->href != nullptr &&
                    mNamespace == reinterpret_cast<const char *>(nsptr->href)) {
                    if (nsptr->prefix != nullptr) {
                        mPrefix = reinterpret_cast<const char *>(nsptr->prefix);
                    }
                    break;
                }
                nsptr = nsptr->next;
            }
            LoadElements(node);
            LoadSimpleTypes(node);
            LoadImports(node);
        }
    }
}

void XSD::LoadElements(::xmlNodePtr node) {
    for (::xmlNode *cur_node = node->children; cur_node != nullptr;
         cur_node = cur_node->next) {
        if (cur_node->type == ::XML_ELEMENT_NODE &&
            !::xmlStrcmp(cur_node->name, (const ::xmlChar *)"element")) {
            XSDElement *element = new XSDElement(cur_node);
            if (element != nullptr) {
                if (element->get_Name().length() > 0) {
                    mElements[element->get_Name()] = element;
                    LoadComplexTypes(cur_node);
                } else {
                    delete element;
                }
            }
        }
    }
}

void XSD::LoadSimpleTypes(::xmlNodePtr node) {
    for (::xmlNode *cur_node = node->children; cur_node != nullptr;
         cur_node = cur_node->next) {
        if (cur_node->type == ::XML_ELEMENT_NODE &&
            !::xmlStrcmp(cur_node->name, (const ::xmlChar *)"simpleType")) {
            XSDSimpleType *simpleType = new XSDSimpleType(cur_node);
            if (simpleType != nullptr) {
                if (simpleType->get_Name().length() > 0) {
                    mSimpleTypes[simpleType->get_Name()] = simpleType;
                } else {
                    delete simpleType;
                }
            }
        }
    }
}

void XSD::LoadComplexTypes(::xmlNodePtr node) {
    for (::xmlNode *cur_node = node->children; cur_node != nullptr;
         cur_node = cur_node->next) {
        if (cur_node->type == ::XML_ELEMENT_NODE &&
            !::xmlStrcmp(cur_node->name, (const ::xmlChar *)"complexType")) {
            XSDComplexType *complexType = new XSDComplexType(cur_node);
            if (complexType != nullptr) {
                if (complexType->get_Name().length() > 0) {
                    mComplexTypes[complexType->get_Name()] = complexType;
                } else {
                    // TODO(foran): Clean this up
                    char buf[1024];
                    ::snprintf(buf, sizeof(buf), "[complexType]:%lu",
                               mComplexTypes.size());
                    mComplexTypes[buf] = complexType;
                }
            }
        }
    }
}

void XSD::LoadImports(::xmlNodePtr node) {
    for (::xmlNode *cur_node = node->children; cur_node != nullptr;
         cur_node = cur_node->next) {
        if (cur_node->type == ::XML_ELEMENT_NODE &&
            !::xmlStrcmp(cur_node->name, (const ::xmlChar *)"import")) {
            ::xmlChar *import =
              ::xmlGetProp(cur_node, (const ::xmlChar *)"schemaLocation");
            if (import != nullptr) {
                Path path(reinterpret_cast<char *>(import));
                if (Path::is_Relative(reinterpret_cast<char *>(import))) {
                    path =
                      mPath.ResolveRelative(reinterpret_cast<char *>(import));
                }
                XSD temp(path.get_UNC());
                ::xmlFree(import);
                for (::std::string element : temp.get_ElementNames()) {
                    mElements[element] =
                      new XSDElement(temp.get_Element(element));
                }
                for (::std::string simpleType : temp.get_SimpleTypeNames()) {
                    mSimpleTypes[simpleType] =
                      new XSDSimpleType(temp.get_SimpleType(simpleType));
                }
            }
        }
    }
}

size_t XSD::curl_write_callback(char *ptr, size_t size, size_t nmemb,
                                void *userdata) {
    ((::std::string *)userdata)->append(ptr, size * nmemb);
    return size * nmemb;
}

::std::string XSD::FetchFile(const Path &unc) const {
    ::std::string retval = "";
    ::CURL *ch = ::curl_easy_init();

    if (ch) {
        ::std::cout << "Fetching " << unc.get_UNC() << "..." << ::std::endl;
        ::curl_easy_setopt(ch, ::CURLOPT_URL, unc.get_UNC().c_str());
        ::curl_easy_setopt(ch, ::CURLOPT_SSL_VERIFYPEER, false);
        ::curl_easy_setopt(ch, ::CURLOPT_SSL_VERIFYHOST, false);
        ::curl_easy_setopt(ch, ::CURLOPT_WRITEDATA, &retval);
        ::curl_easy_setopt(ch, ::CURLOPT_WRITEFUNCTION,
                           XSD::curl_write_callback);
        ::CURLcode result = ::curl_easy_perform(ch);
        if (::CURLE_OK != result) {
            retval = "";
        }
        ::curl_easy_cleanup(ch);
    }

    return retval;
}

}  // namespace xsd
}  // namespace lib
}  // namespace wsdl2cpp
