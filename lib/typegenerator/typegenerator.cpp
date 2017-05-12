#include "typegenerator.h"

#include <fstream>

#include "gflags/gflags.h"

DEFINE_string(output_postfix, "", "Postfix for all generated filenames (i.e. \"generated\" makes type.cpp become type.generated.cpp");

TypeGenerator::TypeGenerator(string outputPath)
{
	mOutputPath = outputPath;
	mNamespace = "";
}

TypeGenerator::TypeGenerator(string outputPath, string ns)
{
	mOutputPath = outputPath;
	mNamespace = ns;
}

TypeGenerator::TypeGenerator(const TypeGenerator &source)
{
	*this = source;
}

TypeGenerator::~TypeGenerator()
{

}

TypeGenerator &TypeGenerator::operator=(const TypeGenerator &source)
{
	mOutputPath = source.mOutputPath;
	mNamespace = source.mNamespace;

	return *this;
}

void TypeGenerator::Generate(const XSDElement &element)
{
	string typeName = element.get_Name();
	ofstream header(mOutputPath + 
#ifdef _WIN32
		"\\"
#else
		"/"
#endif
			+ typeName + (FLAGS_output_postfix.length() > 0 ? string(".") : "") + FLAGS_output_postfix + ".h", ios::out);
	header << "#ifndef __" << typeName << "__" << endl;
	header << "#define __" << typeName << "__" << endl << endl;
	if (mNamespace.length() > 0) header << "namespace " << mNamespace << endl << "{" << endl;
	header << "class " << typeName << " : public foo" << endl;
	header << "{" << endl;
	header << "public:" << endl;
	header << typeName << "();" << endl;
	header << typeName << "(const " << typeName << " &source);" << endl;
	header << "~" << typeName << "();" << endl << endl;
	header << typeName << " &operator=(const " << typeName << " &source);" << endl;
	header << "protected:" << endl;
	header << "private:" << endl;
	header << "};" << endl;
	if (mNamespace.length() > 0) header << "};" << endl;
	header.close();
}
