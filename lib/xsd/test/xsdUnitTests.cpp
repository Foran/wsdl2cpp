// xsdUnitTests.cpp
#include "lib/xsd/xsd.h"
#include "gtest/gtest.h"

TEST(XSDTest, XSDLoadElementCount) { 
   XSD xsd("lib/xsd/test/data/basic.xsd");

   EXPECT_EQ((unsigned int)4, xsd.get_ElementNames().size());
}

TEST(XSDTest, XSDLoadSimpleTypeCount) { 
   XSD xsd("lib/xsd/test/data/basic.xsd");

   EXPECT_EQ((unsigned int)1, xsd.get_SimpleTypeNames().size());
}

TEST(XSDTest, XSDLoadComplexTypeCount) { 
   XSD xsd("lib/xsd/test/data/basic.xsd");

   EXPECT_EQ((unsigned int)2, xsd.get_ComplexTypeNames().size());
}
