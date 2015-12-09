package(default_visibility = ["//visibility:public"])

# LIBRARIES

cc_library(
    name = "base",
    srcs = [
		"callback.cc",
		"once.cc",
		"strtoint.cc",
		"windows_compatability.cc",
    ],
    hdrs = [
		"callback.h",
		"callback-specializations.h",
		"callback-types.h",
		"int128.h",
		"integral_types.h",
		"macros.h",
		"mutex.h",
		"once.h",
		"port.h",
		"strtoint.h",
		"template_util.h",
		"thread_annotations.h",
		"windows_compatability.h",
    ],
    deps = ["//third_party/glog"],
)
