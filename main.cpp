#include "main.h"

int main (int argc, char **argv)
{
	int retval = 0;

	for(int c = 1; c < argc; c++) {
		WSDL wsdl(argv[c]);
		vector<string> portTypeNames = wsdl.get_PortTypeNames();
		for(vector<string>::iterator i = portTypeNames.begin(); i != portTypeNames.end(); i++) {
			cout << "Generating Interface " << *i << ".h..." << endl;
			vector<string> operationNames = wsdl.get_PortType(*i).get_OperationNames();
			for(vector<string>::iterator o = operationNames.begin(); o != operationNames.end(); o++) {
				cout << "Found Operation " << wsdl.get_PortType(*i).get_Operation(*o).get_OutputMessageName() << " " << *o << "(" << wsdl.get_PortType(*i).get_Operation(*o).get_InputMessageName() << ")" << endl;
			}
		}
	}

	return retval;
}
