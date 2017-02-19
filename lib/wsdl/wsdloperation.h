#ifndef __WSDLOPERATION_H__
#define __WSDLOPERATION_H__

#include <string>
#include <vector>

#include <string.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

using namespace std;

class WSDLOperation {
	public:
		WSDLOperation(xmlNodePtr node);
		~WSDLOperation();
		
		string get_Name() const;
		string get_InputMessageName() const;
		string get_InputAction() const;
		string get_OutputMessageName() const;
		string get_OutputAction() const;
	protected:
		void Load(xmlNodePtr node);
		void LoadInput(xmlNodePtr node);
		void LoadOutput(xmlNodePtr node);
	private:
		string mName;
		string mInput;
		string mInputAction;
		string mOutput;
		string mOutputAction;
		WSDLOperation();
		WSDLOperation(const WSDLOperation &source);
		WSDLOperation operator=(const WSDLOperation &source) const;
};

#endif
