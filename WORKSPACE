workspace(
  name = "wsdl2cpp",
)

new_http_archive(
  name = "gtest",
  url = "https://github.com/google/googletest/archive/release-1.8.0.zip",
  sha256 = "f3ed3b58511efd272eb074a3a6d6fb79d7c2e6a0e374323d1e6bcbcc1ef141bf",
  build_file = "thirdparty/gtest.BUILD",
  strip_prefix = "googletest-release-1.8.0",
)

new_http_archive(
  name = "civetweb",
  url = "https://github.com/civetweb/civetweb/archive/v1.9.1.zip",
  sha256 = "c0ed531d8ab7a56dc3457eefdbb5568419446181303fd99b6bd9c94532cf85d5",
  build_file = "thirdparty/civetweb.BUILD",
  strip_prefix = "civetweb-1.9.1",
)

http_archive(
  name = "com_github_gflags_gflags",
  url = "https://github.com/gflags/gflags/archive/v2.2.0.zip",
  sha256 = "99f9e8b63ea53e4b23f0fd0f68a6f1e397d5512be36716c17cc75966a90f0d57",
  strip_prefix = "gflags-2.2.0",
)

bind(
  name = "gflags",
  actual = "@com_github_gflags_gflags//:gflags",
)

bind(
  name = "gflags_nothreads",
  actual = "@com_github_gflags_gflags//:gflags_nothreads",
)
