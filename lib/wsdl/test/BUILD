
cc_test(
  name = "wsdl_tests",
  size = "small",
  srcs = [
    "wsdlUnitTests.cpp",
  ],
  deps = [
    "@gtest//:gtest_main",
    "//lib/wsdl:libwsdl",
  ],
  data = [
    "data/basic.wsdl",
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
