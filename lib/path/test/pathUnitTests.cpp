// pathUnitTests.cpp
#include "lib/path/path.h"
#include <gtest/gtest.h>

TEST(PATHTest, PathConstructor) {
   Path a, b("foo.txt");
   
   EXPECT_EQ(string(""), a.get_Raw());
   EXPECT_EQ(string("foo.txt"), b.get_Raw());
}

TEST(PATHTest, PathAssignment) {
   Path a, b("foo.txt");
   
   EXPECT_EQ(string(""), a.get_Raw());
   a = b;
   EXPECT_EQ(string("foo.txt"), a.get_Raw());
   a = "bar.txt";
   EXPECT_EQ(string("bar.txt"), a.get_Raw());
}

TEST(PATHTest, PathEquality) {
   Path a("foo.txt"), b("bar.txt"), c("bar.txt");
   
   EXPECT_FALSE(a == b);
   EXPECT_TRUE(b == c);
   EXPECT_TRUE(a == "foo.txt");
   EXPECT_FALSE(b == "foo.txt");
}

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