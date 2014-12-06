// tests.cpp
#include "../xsd.h"
#include <gtest/gtest.h>
  
TEST(XSDTest, BasicConstruct) { 
   //ASSERT_EQ(6, squareRoot(36.0));
   XSD xsd("foo");
}
                            
int main(int argc, char **argv) {
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}