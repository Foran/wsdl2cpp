#include "typegenerator.h"

#include <fstream>

TypeGenerator::TypeGenerator()
{

}

void TypeGenerator::Generate(const string outputPath, const XSDElement &element)
{
	ofstream header(outputPath + "\\" + element.get_Name() + ".h", ios::out);
	header << "#ifndef __" << element.get_Name() << "__" << endl;
	header << "#define __" << element.get_Name() << "__" << endl;
	header << endl << "class " << element.get_Name() << " : public foo" << endl;
	header << "{" << endl;
	header << "};" << endl;
	header.close();
}
