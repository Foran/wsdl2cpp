#include "main.h"

int main (int argc, char **argv)
{
	int retval = 0;

	if(argc > 1) {
		WSDL wsdl(argv[1]);
		vector<string> portTypeNames = wsdl.get_PortTypeNames();
		for(vector<string>::iterator i = portTypeNames.begin(); i != portTypeNames.end(); i++) {
			cout << "Generating Interface " << *i << ".h..." << endl;
		}
	}

	return retval;
}
