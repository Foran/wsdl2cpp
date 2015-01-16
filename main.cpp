#include "main.h"

void DisplayHelp(int argc, char **argv)
{
	cout << "Usage: " << argv[0] << " [options] filename" << endl;
	cout << "Options:" << endl;
	cout << "\t" << "-h, --help" << "\t" << "Display Help" << endl;
}

vector<string> Filenames;

bool ParseCmdLine(int argc, char **argv)
{
	bool retval = true;
	if (argc == 1) {
		DisplayHelp(argc, argv);
		retval = false;
	}
	else {
		bool lastArg = false;
		for (int i = 1; retval && i < argc; i++) {
			if (!lastArg && argv[i][0] == '-') {
				if (argv[i][1] != '\0' && argv[i][2] == '\0') {
					switch (argv[i][1]) {
						case 'h':
							DisplayHelp(argc, argv);
							retval = false;
							break;
						case '-':
							lastArg = true;
							break;
					}
				}
				else if (!strncmp("--help", argv[i], 7)) {
					DisplayHelp(argc, argv);
					retval = false;
				}
			}
			else {
				Filenames.push_back(Path::get_UNC(argv[i]));
			}
		}
	}
	return retval;
}

int main (int argc, char **argv)
{
	int retval = 0;

	if (ParseCmdLine(argc, argv)) {
		for(string filename : Filenames) {
			WSDL wsdl(filename);
			for (string portTypeName : wsdl.get_PortTypeNames()) {
				cout << "Generating codegen/" << wsdl.get_PortType(portTypeName).get_Name() << ".h ..." << endl;
				for (string operationName : wsdl.get_PortType(portTypeName).get_OperationNames()) {
					cout << "Generating Operation " << operationName << endl;
					string inputMessageName = wsdl.get_PortType(portTypeName).get_Operation(operationName).get_InputMessageName();
					string outputMessageName = wsdl.get_PortType(portTypeName).get_Operation(operationName).get_OutputMessageName();
					if (inputMessageName.length() > 0) {
						for (string partName : wsdl.get_Message(inputMessageName).get_PartNames()) {
							cout << "Generating Input Message Part " << partName << endl;
							string elementName = wsdl.get_Message(inputMessageName).get_Part(partName).get_Element();
							wsdl.get_Type(elementName);
						}
					}
					if (outputMessageName.length() > 0) {
						for (string partName : wsdl.get_Message(outputMessageName).get_PartNames()) {
							cout << "Generating Output Message Part " << partName << endl;
							string elementName = wsdl.get_Message(outputMessageName).get_Part(partName).get_Element();
							cout << "Generating codegen/" + wsdl.get_Type(elementName).get_Name() << ".h ..." << endl;
							TypeGenerator generator("codegen", wsdl.get_Type(elementName).get_Prefix());
							generator.Generate(wsdl.get_Type(elementName));
						}
					}
				}
			}
		}
	}

	return retval;
}
