// pathUnitTests.cpp
#include "lib/typegenerator/typegenerator.h"
#include <gtest/gtest.h>

TEST(TYPEGENERATORTest, TypeGeneratorConstructor) {
   TypeGenerator a("codegen");
}

int main(int argc, char **argv) {
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
