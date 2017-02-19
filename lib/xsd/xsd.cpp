#include "xsd.h"

#include "curl/curl.h"

XSD::XSD(string filename)
{
	mPath = "";
	Load(filename);
}

XSD::XSD(xmlDocPtr document)
{
	mPath = Path::CurrentDirectory();
	Load(document);
}

XSD::XSD(xmlNodePtr node)
{
	mPath = Path::CurrentDirectory();
	Load(node);
}

XSD::XSD(xmlDocPtr document, Path path)
{
	mPath = path;
	Load(document);
}

XSD::XSD(xmlNodePtr node, Path path)
{
	mPath = path;
	Load(node);
}

XSD::~XSD()
{
	for (map<string, XSDElement *>::iterator p = mElements.begin(); p != mElements.end(); p++) {
		delete p->second;
	}
	for (map<string, XSDSimpleType *>::iterator p = mSimpleTypes.begin(); p != mSimpleTypes.end(); p++) {
		delete p->second;
	}
	for (map<string, XSDComplexType *>::iterator p = mComplexTypes.begin(); p != mComplexTypes.end(); p++) {
		delete p->second;
	}
}

string XSD::get_Namespace() const
{
	return mNamespace;
}

vector<string> XSD::get_ElementNames()
{
	vector<string> retval;
	for (auto entry : mElements) {
		retval.push_back(entry.first);
	}
	return retval;
}

XSDElement &XSD::get_Element(string name)
{
	XSDElement *retval = new XSDElement(*mElements[name]);

	return *retval;
}

vector<string> XSD::get_SimpleTypeNames()
{
	vector<string> retval;
	for (auto entry : mSimpleTypes) {
		retval.push_back(entry.first);
	}
	return retval;
}

XSDSimpleType &XSD::get_SimpleType(string name)
{
	XSDSimpleType *retval = new XSDSimpleType(*mSimpleTypes[name]);

	return *retval;
}

vector<string> XSD::get_ComplexTypeNames()
{
	vector<string> retval;
	for (auto entry : mComplexTypes) {
		retval.push_back(entry.first);
	}
	return retval;
}

XSDComplexType &XSD::get_ComplexType(string name)
{
	XSDComplexType *retval = new XSDComplexType(*mComplexTypes[name]);

	return *retval;
}

void XSD::Load(string filename)
{
	Path path(filename);
	string buffer = FetchFile(path);
	xmlDoc *doc = xmlReadMemory(buffer.c_str(), buffer.length(), "noname.xml", nullptr, 0);
	if (doc != nullptr) {
		mPath = path.get_BasePath();
		Load(doc);
		xmlFreeDoc(doc);
	}
}

void XSD::Load(xmlDocPtr document)
{
	if (document != nullptr) {
		Load(document->children);
	}
}

void XSD::Load(xmlNodePtr node)
{
	if (node != nullptr) {
		xmlChar *ns = xmlGetProp(node, (const xmlChar *)"targetNamespace");
		if (ns != nullptr) {
			mNamespace = (char *)ns;
			xmlFree(ns);
			xmlNsPtr nsptr = node->nsDef;
			while (nsptr != nullptr) {
				if (nsptr->href != nullptr && mNamespace == (char *)nsptr->href) {
					if (nsptr->prefix != nullptr) {
						mPrefix = (char *)nsptr->prefix;
					}
					break;
				}
			}
			LoadElements(node);
			LoadImports(node);
		}
	}
}

void XSD::LoadElements(xmlNodePtr node)
{
	for (xmlNode *cur_node = node->children; cur_node != nullptr; cur_node = cur_node->next) {
		if (cur_node->type == XML_ELEMENT_NODE && !xmlStrcmp(cur_node->name, (const xmlChar *)"element")) {
			XSDElement *element = new XSDElement(cur_node);
			if (element != nullptr) {
				if (element->get_Name().length() > 0) {
					mElements[element->get_Name()] = element;
				}
				else {
					delete element;
				}
			}
		}
	}
}

void XSD::LoadSimpleTypes(xmlNodePtr node)
{
	for (xmlNode *cur_node = node->children; cur_node != nullptr; cur_node = cur_node->next) {
		if (cur_node->type == XML_ELEMENT_NODE && !xmlStrcmp(cur_node->name, (const xmlChar *)"simpleType")) {
			XSDSimpleType *simpleType = new XSDSimpleType(cur_node);
			if (simpleType != nullptr) {
				if (simpleType->get_Name().length() > 0) {
					mSimpleTypes[simpleType->get_Name()] = simpleType;
				}
				else {
					delete simpleType;
				}
			}
		}
	}
}

void XSD::LoadComplexTypes(xmlNodePtr node)
{
	for (xmlNode *cur_node = node->children; cur_node != nullptr; cur_node = cur_node->next) {
		if (cur_node->type == XML_ELEMENT_NODE && !xmlStrcmp(cur_node->name, (const xmlChar *)"complexType")) {
			XSDComplexType *complexType = new XSDComplexType(cur_node);
			if (complexType != nullptr) {
				if (complexType->get_Name().length() > 0) {
					mComplexTypes[complexType->get_Name()] = complexType;
				}
				else {
					delete complexType;
				}
			}
		}
	}
}

void XSD::LoadImports(xmlNodePtr node)
{
	for(xmlNode *cur_node = node->children; cur_node != nullptr; cur_node = cur_node->next) {
		if(cur_node->type == XML_ELEMENT_NODE && !xmlStrcmp(cur_node->name, (const xmlChar *)"import")) {
			xmlChar *import = xmlGetProp(cur_node, (const xmlChar *)"schemaLocation");
			if(import != nullptr) {
				Path path((char *)import);
				if (Path::is_Relative((char *)import)) path = mPath.ResolveRelative((char *)import);
				XSD temp(path.get_UNC());
				xmlFree(import);
				for (string element : temp.get_ElementNames()) {
					mElements[element] = new XSDElement(temp.get_Element(element));
				}
				for (string simpleType : temp.get_SimpleTypeNames()) {
					mSimpleTypes[simpleType] = new XSDSimpleType(temp.get_SimpleType(simpleType));
				}
			}
		}
	}
}

size_t XSD::curl_write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	((string *)userdata)->append(ptr, size * nmemb);
	return size * nmemb;
}

string XSD::FetchFile(const Path &unc) const
{
   string retval = "";
   CURL *ch = curl_easy_init();
   if (ch) {
      curl_easy_setopt(ch, CURLOPT_URL, unc.get_UNC().c_str());
      curl_easy_setopt(ch, CURLOPT_SSL_VERIFYPEER, false);
      curl_easy_setopt(ch, CURLOPT_SSL_VERIFYHOST, false);
      curl_easy_setopt(ch, CURLOPT_WRITEDATA, &retval);
      curl_easy_setopt(ch, CURLOPT_WRITEFUNCTION, XSD::curl_write_callback);
      CURLcode result = curl_easy_perform(ch);
      if (CURLE_OK != result) {
	 retval = "";
      }
      curl_easy_cleanup(ch);
   }
   
   return retval;
}
