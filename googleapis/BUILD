licenses(["notice"])

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "library",
    srcs = glob([
        "base/*.cc",
        "strings/*.cc",
        "util/*.cc"],
        exclude=["util/file.cc"]),
    hdrs = glob([
        "config.h",
        "base/*.h",
        "strings/*.h",
        "util/*.h"],
        exclude=["util/file.h"]),
    deps = [
        "//third_party/glog",
    ],
    linkstatic = 1,
)
