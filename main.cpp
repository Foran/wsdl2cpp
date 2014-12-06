#include "main.h"

int main (int argc, char **argv)
{
	int retval = 0;

	for(int c = 1; c < argc; c++) {
		WSDL wsdl(argv[c]);
		vector<string> portTypeNames = wsdl.get_PortTypeNames();
		for(vector<string>::iterator i = portTypeNames.begin(); i != portTypeNames.end(); i++) {
			cout << "Generating Interface " << *i << ".h..." << endl;
			cout << "Generating Types..." << endl;
			for (string ns : wsdl.get_TypeNamespaces()) {
				for (string name : wsdl.get_Type(ns).get_ElementNames()) {
					cout << wsdl.get_Type(ns).get_Element(name).get_Type() << " " << wsdl.get_Type(ns).get_Element(name).get_Name() << endl;
				}
			}
			cout << "Generating Operations..." << endl;
			vector<string> operationNames = wsdl.get_PortType(*i).get_OperationNames();
			for(vector<string>::iterator o = operationNames.begin(); o != operationNames.end(); o++) {
				WSDLMessage *output = &wsdl.get_Message(wsdl.get_PortType(*i).get_Operation(*o).get_OutputMessageName());
				vector<string> partNames;
				if(output == nullptr) partNames.push_back("void");
				else partNames = output->get_PartNames();
				WSDLMessage *input = &wsdl.get_Message(wsdl.get_PortType(*i).get_Operation(*o).get_InputMessageName());
				vector<string> partNames2;
				if (input == nullptr) partNames2.push_back("void");
				else partNames2 = input->get_PartNames();
				for(vector<string>::iterator op = partNames.begin(); op != partNames.end(); op++) {
					for(vector<string>::iterator ip = partNames2.begin(); ip != partNames2.end(); ip++) {
						cout << "Found Operation " << (*op == "void" ? *op : output->get_Part(*op).get_Element()) << " " << *o << "(" << (*ip == "void" ? "" : input->get_Part(*ip).get_Element()) << ")" << endl;
					}
				}
			}
		}
	}
	getchar();
	return retval;
}
