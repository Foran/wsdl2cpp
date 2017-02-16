// pathUnitTests.cpp
#include "path.h"
#include <gtest/gtest.h>

TEST(PATHTest, PathAbsolute) {
   Path path("foo");
   ASSERT_EQ(Path::CurrentDirectory() + "foo", path.get_Absolute());
}

TEST(PATHTest, PathRelative) 
{
   ASSERT_EQ(string("file:///home/user/foo.txt"), Path::ResolveRelative("file:///home/media/music", "../../user/foo.txt").get_UNC());
}

int main(int argc, char **argv) {
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
