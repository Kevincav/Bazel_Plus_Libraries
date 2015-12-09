package(default_visibility = ["//visibility:public"])

# Libraries

cc_library(
    name = "trie",
    srcs = ["trie.cc"],
    hdrs = ["trie.h"],
    deps = ["//googleapis:library"],
)

# Tests

cc_test(
    name = "trie_test",
    srcs = ["trie_test.cc"],
    deps = [
        ":trie",
        "//googleapis:library",
        "//third_party/glog",
        "//third_party/gtest",
    ],
)
