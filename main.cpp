#include "main.h"

string getAttribute(xmlNodePtr node, string name)
{
   xmlChar *value = xmlGetProp(node, (const xmlChar *)name.c_str());
   string retval = "";
   
   if(value != NULL) retval = (char *)value;
   
   return retval;
}

xmlNodePtr getChildNode(xmlNodePtr node, string name)
{
   xmlNodePtr retval = NULL;
   
   if(node != NULL && node->children != NULL) {
      for(xmlNode *cur_node = node->children; cur_node; cur_node = cur_node->next) {
	 if(cur_node->type == XML_ELEMENT_NODE && name == (char *)cur_node->name) {
	    retval = cur_node;
	    break;
	 }
      }
   }
   
   return retval;
}

vector<string> getInterfaces(xmlDocPtr doc)
{
   vector<string> retval;
   
   xmlNode *node = xmlDocGetRootElement(doc);
   if(node != NULL) {
      node = getChildNode(node, "portType");
      if(node != NULL) {
	 retval.push_back(getAttribute(node, "name"));
	 for(xmlNode *cur_node = node->children; cur_node; cur_node = cur_node->next) {
	    if(cur_node->type == XML_ELEMENT_NODE && !xmlStrcmp(cur_node->name, (const xmlChar *)"portType")) {
	       retval.push_back(getAttribute(cur_node, "name"));
	    }
	 }
      }
   }
   
   return retval;
}

xmlNodePtr getInterface(xmlDocPtr doc, string name)
{
   xmlNodePtr retval = NULL;
   
   xmlNode *node = xmlDocGetRootElement(doc);
   if(node != NULL) {
      node = getChildNode(node, "portType");
      while(node != NULL) {
	 if(node->type == XML_ELEMENT_NODE && !xmlStrcmp(node->name, (const xmlChar *)"portType") && getAttribute(node, "name") == name) {
	    retval = node;
	    break;
	 }
	 node = node->next;
      }
   }

   return retval;
}

vector<string> getOperations(xmlDocPtr doc, string interface)
{
   vector<string> retval;
   
   xmlNode *node = getInterface(doc, interface);
   if(node != NULL) {
      node = getChildNode(node, "operation");
      while(node != NULL) {
	 if(node->type == XML_ELEMENT_NODE && !xmlStrcmp(node->name, (const xmlChar *)"operation")) {
	    retval.push_back(getAttribute(node, "name"));
	 }
	 node = node->next;
      }
   }
   
   return retval;
}

int main(int argc, char **argv) 
{
   int retval = 0;
   
   if(argc > 1) {
      xmlDoc *doc = xmlReadFile(argv[1], NULL, 0);
      if(doc != NULL) {
	 vector<string> interfaces = getInterfaces(doc);
	 for(vector<string>::iterator i = interfaces.begin(); i != interfaces.end(); i++) {
	    if(i->length() > 0) {
	       FILE *fp = fopen((*i + ".h").c_str(), "w");
	       if(fp != NULL) {
		  fputs((((string)"#ifndef __") + *i + "_H__\r\n").c_str(), fp);
		  fputs((((string)"#define __") + *i + "_H__\r\n").c_str(), fp);
		  fputs("\r\n", fp);
		  fprintf(fp, "typedef struct %s {\r\n", i->c_str());
		  vector<string> operations = getOperations(doc, *i);
		  for(vector<string>::iterator o = operations.begin(); o != operations.end(); o++) {
		     fprintf(fp, "\tvirtual void %s() = 0;\r\n", o->c_str());
		  }
		  fprintf(fp, "} %s;\r\n", i->c_str());
		  fputs("\r\n", fp);
		  fputs("#endif", fp);
		  fclose(fp);
	       }
	    }
	 }
	 xmlFreeDoc(doc);
      }
   }
      
   return retval;
}
