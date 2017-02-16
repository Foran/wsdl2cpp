cc_library(
    name = "civetweb",
    srcs = [
      "src/civetweb.c",
    ],
    hdrs = [
      "include/civetweb.h",
    ],
    textual_hdrs = [
      "src/md5.inl",
      "src/mod_lua.inl",
    ],
    copts = [
      "-Iexternal/civetweb/include",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "civetserver",
    srcs = [
      "src/CivetServer.cpp",
    ],
    hdrs = [
        "include/CivetServer.h",
    ],
    visibility = ["//visibility:public"],
)
