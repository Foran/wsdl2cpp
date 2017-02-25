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
    "-lcurl",
  ],
  deps = [
    "//lib/wsdl:libwsdl",
    "//lib/typegenerator:libtypegenerator",
  ],
)

