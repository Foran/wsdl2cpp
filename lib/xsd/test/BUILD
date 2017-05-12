cc_test(
  name = "xsd_test",
  size = "small",
  srcs = [
    "xsdUnitTests.cpp",
  ],
  deps = [
    "@gtest//:gtest_main",
    "//lib/xsd:libxsd",
  ],
  data = [
    "data/basic.xsd",
  ],
  copts = [
    "-I/usr/include/libxml2",
    "-Iexternal/gtest/include",
  ],
  linkopts = [
    "-lxml2",
    "-ldl",
    "-lpthread",
    "-lcurl",
  ],
)
