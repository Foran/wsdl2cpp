cc_binary(
  name = "wsdl2cpp",
  srcs = [
    "main.cpp",
    "main.h",
  ],
  copts = [
    "-I/usr/include/libxml2",
  ],
  linkopts = [
    "-lxml2",
    "-ldl",
    "-lpthread",
    "-lcurl",
  ],
  deps = [
    ":libwsdl2cpp",
  ],
)

cc_library(
  name = "libwsdl2cpp",
  srcs = [
    "wsdl.cpp",
    "wsdlmessage.cpp",
    "wsdlmessagepart.cpp",
    "wsdlporttype.cpp",
    "wsdloperation.cpp",
    "xsd.cpp",
    "xsdelement.cpp",
    "xsdsimpletype.cpp",
    "xsdcomplextype.cpp",
    "typegenerator.cpp",
  ],
  hdrs = [
    "wsdl.h",
    "wsdlmessage.h",
    "wsdlmessagepart.h",
    "wsdlporttype.h",
    "wsdloperation.h",
    "xsd.h",
    "xsdelement.h",
    "xsdsimpletype.h",
    "xsdcomplextype.h",
    "typegenerator.h",
  ],
  deps = [
    "//external:gflags",
    "@civetweb//:civetweb",
    "//lib/path:libpath",
  ],
  copts = [
    "-I/usr/include/libxml2",
  ],
)

cc_test(
  name = "wsdl_tests",
  size = "small",
  srcs = [
    "test/wsdlUnitTests.cpp",
  ],
  deps = [
    "@gtest//:main",
    ":libwsdl2cpp",
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

cc_test(
  name = "xsd_test",
  size = "small",
  srcs = [
    "test/xsdUnitTests.cpp",
  ],
  deps = [
    "@gtest//:main",
    ":libwsdl2cpp",
  ],
  data = [
    "test/testData/basic.wsdl",
    "test/testData/basic.xsd",
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
