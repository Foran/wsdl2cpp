/******************************************************************************
 * Project: wsdl2cpp
 * File: lib/xsd/test/xsdUnitTests.cpp
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#include "gtest/gtest.h"
#include "lib/xsd/xsd.h"

TEST(XSDTest, XSDLoadElementCount) {
    ::wsdl2cpp::lib::xsd::XSD xsd("lib/xsd/test/data/basic.xsd");

    EXPECT_EQ((unsigned int)4, xsd.get_ElementNames().size());
}

TEST(XSDTest, XSDLoadSimpleTypeCount) {
    ::wsdl2cpp::lib::xsd::XSD xsd("lib/xsd/test/data/basic.xsd");

    EXPECT_EQ((unsigned int)1, xsd.get_SimpleTypeNames().size());
}

TEST(XSDTest, XSDLoadComplexTypeCount) {
    ::wsdl2cpp::lib::xsd::XSD xsd("lib/xsd/test/data/basic.xsd");

    EXPECT_EQ((unsigned int)2, xsd.get_ComplexTypeNames().size());
}
