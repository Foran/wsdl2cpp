cc_test(
  name = "typegenerator_tests",
  size = "small",
  srcs = [
    "typeGeneratorUnitTests.cpp",
  ],
  deps = [
    "@gtest//:main",
    "//lib/typegenerator:libtypegenerator",
  ],
  copts = [
    "-Iexternal/gtest/include",
    "-I/usr/include/libxml2",
  ],
  linkopts = [
    "-lxml2",
    "-lcurl",
  ],
)
