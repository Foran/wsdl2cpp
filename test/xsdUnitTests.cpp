// xsdUnitTests.cpp
#include "../xsd.h"
#include <gtest/gtest.h>

TEST(XSDTest, XSDLoadElementCount) { 
   XSD xsd("testData/basic.xsd");
   ASSERT_EQ(4, xsd.get_ElementNames().size());
}

TEST(XSDTest, XSDLoadSimpleTypeCount) { 
   XSD xsd("testData/basic.xsd");
   ASSERT_EQ(1, xsd.get_SimpleTypeNames().size());
}

int main(int argc, char **argv) {
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
