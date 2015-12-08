package(default_visibility = ["//visibility:public"])

# Libraries

cc_library(
    name = "trie",
    srcs = ["trie.cc"],
    hdrs = ["trie.h"],
    deps = [],
)

# Tests

cc_test(
    name = "trie_test",
    srcs = ["trie_test"],
    deps = [
        ":trie",
        "//third_party/gtest",
    ],
)
