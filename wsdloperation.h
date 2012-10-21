#ifndef __WSDLOPERATION_H__
#define __WSDLOPERATION_H__

#include <string>
#include <vector>

#include <libxml/parser.h>
#include <libxml/tree.h>

using namespace std;

class WSDLOperation {
	public:
		WSDLOperation(xmlNodePtr node);
		~WSDLOperation();
		
		string get_Name() const;
	protected:
		void Load(xmlNodePtr node);
	private:
		string mName;
		WSDLOperation();
		WSDLOperation(const WSDLOperation &source);
		WSDLOperation operator=(const WSDLOperation &source) const;
};

#endif
