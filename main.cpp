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
			}
		}
	}

	return retval;
}
