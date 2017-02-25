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
    "//external:gflags_nothreads",
  ],
)

cc_library(
  name = "libwsdl2cpp",
  srcs = [
    "typegenerator.cpp",
  ],
  hdrs = [
    "typegenerator.h",
  ],
  deps = [
    "//external:gflags",
    "@civetweb//:civetweb",
    "//lib/path:libpath",
    "//lib/xsd:libxsd",
    "//lib/wsdl:libwsdl",
  ],
  copts = [
    "-I/usr/include/libxml2",
  ],
)
