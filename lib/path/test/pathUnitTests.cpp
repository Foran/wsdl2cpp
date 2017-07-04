/******************************************************************************
 * Project: wsdl2cpp
 * File: lib/path/test/pathUnitTests.cpp
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#include <string>

#include "gtest/gtest.h"
#include "lib/path/path.h"

using ::wsdl2cpp::lib::path::Path;

TEST(PATHTest, PathConstructor) {
    Path a, b("foo.txt");

    EXPECT_EQ(::std::string(""), a.get_Raw());
    EXPECT_EQ(::std::string("foo.txt"), b.get_Raw());
}

TEST(PATHTest, PathAssignment) {
    Path a, b("foo.txt");

    EXPECT_EQ(::std::string(""), a.get_Raw());
    a = b;
    EXPECT_EQ(::std::string("foo.txt"), a.get_Raw());
    a = "bar.txt";
    EXPECT_EQ(::std::string("bar.txt"), a.get_Raw());
}

TEST(PATHTest, PathEquality) {
    Path a("foo.txt"), b("bar.txt"), c("bar.txt");

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(b == c);
    EXPECT_TRUE((a == "foo.txt"));
    EXPECT_FALSE((b == "foo.txt"));
}

TEST(PATHTest, PathUNC) {
    Path path("data/foo.txt");
    ASSERT_EQ(::std::string("file://") +
              Path::CurrentDirectory() +
              "data/foo.txt", path.get_UNC());
}

TEST(PATHTest, PathIsUNCNoPath) {
    Path path("foo.txt");
    EXPECT_FALSE(path.is_UNC()) << "\"foo.txt\" was an UNC";
    path = "data/foo.txt";
    EXPECT_FALSE(path.is_UNC()) << "\"data/foo.txt\" was an UNC";
    path = "/home/user/data/foo.txt";
    EXPECT_FALSE(path.is_UNC()) << "\"/home/user/data/foo.txt\" was an UNC";
    path = "file:///home/user/data/foo.txt";
    EXPECT_TRUE(path.is_UNC()) << "\"file:///home/user/data/foo.txt\" "
                                  "was not an UNC";
    path = "http://example.com/data/foo.txt";
    EXPECT_TRUE(path.is_UNC()) << "\"http://example.com/data/foo.txt\" "
                                  "was not an UNC";
    path = "https://example.com/data/foo.txt";
    EXPECT_TRUE(path.is_UNC()) << "\"https://example.com/data/foo.txt\" "
                                  "was not an UNC";
}

TEST(PATHTest, PathAbsolute) {
    Path path("foo");

    ASSERT_EQ(Path::CurrentDirectory() + "foo", path.get_Absolute());
}

TEST(PATHTest, PathRelative) {
    ASSERT_EQ(::std::string("file:///home/user/foo.txt"),
              Path::ResolveRelative("file:///home/media/music",
                                    "../../user/foo.txt").get_UNC());
}

TEST(PATHTest, PathCurrentDirectory) {
    ASSERT_NE(::std::string(""), Path::CurrentDirectory());
}

TEST(PATHTest, PathProtocol) {
    Path a("foo.txt");
    EXPECT_EQ(::std::string("file"), a.get_Protocol());
    a = "http://foo.com/bar.txt";
    EXPECT_EQ(::std::string("http"), a.get_Protocol());
}
