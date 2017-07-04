/******************************************************************************
 * Project: wsdl2cpp
 * File: lib/typegenerator/typegenerator.cpp
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#include "lib/typegenerator/typegenerator.h"

#include <fstream>
#include <string>

#include "gflags/gflags.h"

DEFINE_string(output_postfix, "", "Postfix for all generated filenames "
                                  "(i.e. \"generated\" makes type.cpp become "
                                  "type.generated.cpp");

namespace wsdl2cpp {
namespace lib {
namespace typegenerator {

using ::wsdl2cpp::lib::xsd::XSDElement;

TypeGenerator::TypeGenerator(::std::string outputPath) {
    mOutputPath = outputPath;
    mNamespace = "";
}

TypeGenerator::TypeGenerator(::std::string outputPath, ::std::string ns) {
    mOutputPath = outputPath;
    mNamespace = ns;
}

TypeGenerator::TypeGenerator(const TypeGenerator &source) {
    *this = source;
}

TypeGenerator::~TypeGenerator() {
}

TypeGenerator &TypeGenerator::operator=(const TypeGenerator &source) {
    mOutputPath = source.mOutputPath;
    mNamespace = source.mNamespace;

    return *this;
}

void TypeGenerator::Generate(const XSDElement &element) {
    ::std::string typeName = element.get_Name();
    ::std::ofstream header(mOutputPath +
#ifdef _WIN32
        "\\" +
#else
        "/" +
#endif
        typeName +
        (FLAGS_output_postfix.length() > 0 ? ::std::string(".") : "") +
        FLAGS_output_postfix + ".h", ::std::ios::out);
    header << "#ifndef __" << typeName << "__" << ::std::endl;
    header << "#define __" << typeName << "__" << ::std::endl << ::std::endl;
    if (mNamespace.length() > 0) {
        header << "namespace " << mNamespace << ::std::endl << "{" <<
            ::std::endl;
    }
    header << "class " << typeName << " : public foo" << ::std::endl;
    header << "{" << ::std::endl;
    header << "public:" << ::std::endl;
    header << typeName << "();" << ::std::endl;
    header << typeName << "(const " << typeName << " &source);" << ::std::endl;
    header << "~" << typeName << "();" << ::std::endl << ::std::endl;
    header << typeName << " &operator=(const " << typeName << " &source);" <<
        ::std::endl;
    header << "protected:" << ::std::endl;
    header << "private:" << ::std::endl;
    header << "};" << ::std::endl;
    if (mNamespace.length() > 0) header << "};" << ::std::endl;
    header.close();
}

}  // namespace typegenerator
}  // namespace lib
}  // namespace wsdl2cpp
