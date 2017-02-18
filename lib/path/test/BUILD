cc_test(
  name = "path_tests",
  size = "small",
  srcs = [
    "pathUnitTests.cpp",
  ],
  deps = [
    "@gtest//:main",
    "//lib/path:libpath",
  ],
  copts = [
    "-Iexternal/gtest/include",
  ],
  linkopts = [
    "-lxml2",
    "-ldl",
    "-lpthread",
    "-lcurl",
  ],
)
