cc_library(
  name = "libwsdl",
  srcs = [
    "wsdl.cpp",
    "wsdlmessage.cpp",
    "wsdlmessagepart.cpp",
    "wsdlporttype.cpp",
    "wsdloperation.cpp",
  ],
  hdrs = [
    "wsdl.h",
    "wsdlmessage.h",
    "wsdlmessagepart.h",
    "wsdlporttype.h",
    "wsdloperation.h",
  ],
  deps = [
    "//external:gflags_nothreads",
    "@civetweb//:civetweb",
    "//lib/path:libpath",
    "//lib/xsd:libxsd",
  ],
  copts = [
    "-I/usr/include/libxml2",
  ],
  visibility = [
    "//visibility:public",
  ]
)
