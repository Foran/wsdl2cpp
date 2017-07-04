/******************************************************************************
 * Project: wsdl2cpp
 * File: lib/typegenerator/test/typeGeneratorUnitTests.cpp
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#include "gtest/gtest.h"
#include "lib/typegenerator/typegenerator.h"

TEST(TYPEGENERATORTest, TypeGeneratorConstructor) {
    ::wsdl2cpp::lib::typegenerator::TypeGenerator a("codegen");
}
