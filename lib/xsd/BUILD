cc_library(
  name = "libxsd",
  srcs = [
    "xsd.cpp",
    "xsdelement.cpp",
    "xsdsimpletype.cpp",
    "xsdcomplextype.cpp",
  ],
  hdrs = [
    "xsd.h",
    "xsdelement.h",
    "xsdsimpletype.h",
    "xsdcomplextype.h",
  ],
  deps = [
    "//lib/path:libpath",
  ],
  copts = [
    "-I/usr/include/libxml2",
  ],
  visibility = [
    "//visibility:public",
  ],
)
