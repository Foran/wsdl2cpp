/******************************************************************************
 * Project: wsdl2cpp
 * File: lib/typegenerator/typegenerator.h
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#ifndef LIB_TYPEGENERATOR_TYPEGENERATOR_H_
#define LIB_TYPEGENERATOR_TYPEGENERATOR_H_

#include <string>

#include "lib/xsd/xsdelement.h"

namespace wsdl2cpp {
namespace lib {
namespace typegenerator {

using ::wsdl2cpp::lib::xsd::XSDElement;

class TypeGenerator {
 public:
    explicit TypeGenerator(::std::string outputPath);
    TypeGenerator(::std::string outputPath, ::std::string ns);
    TypeGenerator(const TypeGenerator &source);
    ~TypeGenerator();

    TypeGenerator &operator=(const TypeGenerator &source);

    void Generate(const XSDElement &element);

 private:
    ::std::string mOutputPath;
    ::std::string mNamespace;
    TypeGenerator() = delete;
};

}  // namespace typegenerator
}  // namespace lib
}  // namespace wsdl2cpp

#endif  // LIB_TYPEGENERATOR_TYPEGENERATOR_H_
