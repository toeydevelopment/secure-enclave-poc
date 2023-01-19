load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")
load("@linux_sgx//:sgx_sdk.bzl", "sgx")
load("@rules_cc//cc:defs.bzl", "cc_library", "cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")
load(
    "@com_google_asylo//asylo/bazel:asylo.bzl",
    "ASYLO_ALL_BACKEND_TAGS",
    "cc_unsigned_enclave",
    "debug_sign_enclave",
    "enclave_loader",
    "enclave_test",
)

licenses(["notice"])  # Apache v2.0



package(
    default_visibility = ["//visibility:public"],
)


proto_library(
    name = "protection_proto",
    srcs = ["protection.proto"],
    tags = ASYLO_ALL_BACKEND_TAGS,
)

cc_proto_library(
    name = "protection_cc_proto",
    tags = ASYLO_ALL_BACKEND_TAGS,
    deps = [":protection_proto"],
)


cc_grpc_library(
    name = "protection",
    srcs = [":protection_proto"],
    grpc_only = True,
    tags = ASYLO_ALL_BACKEND_TAGS,
    deps = [":protection_cc_proto"],
)


# The implementation of the protection server.
cc_library(
    name = "protection_server",
    srcs = ["protection_server.cc"],
    hdrs = ["protection_server.h"],
    tags = ASYLO_ALL_BACKEND_TAGS,
    deps = [
        ":protection",
        "@com_github_grpc_grpc//:grpc++",
        "@com_google_absl//absl/base:core_headers",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/synchronization",
    ],
)

# Contains extensions to enclave protos.
proto_library(
    name = "protection_grpc_server_config_proto",
    srcs = ["protection_grpc_server_config.proto"],
    deps = ["@com_google_asylo//asylo:enclave_proto"],
)

cc_proto_library(
    name = "protection_grpc_server_config_cc_proto",
    deps = [":protection_grpc_server_config_proto"],
)


# The enclave hosting the translation server.
cc_unsigned_enclave(
    name = "protection_server_enclave_unsigned.so",
    srcs = ["protection_server_enclave.cc"],
    backends = sgx.backend_labels,
    deps = [
        ":protection_grpc_server_config_cc_proto",
        ":protection_server",
        "@com_github_grpc_grpc//:grpc++",
        "@com_github_grpc_grpc//:grpc++_reflection",
        "@com_google_absl//absl/base:core_headers",
        "@com_google_absl//absl/memory",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/synchronization",
        "@com_google_absl//absl/time",
        "@com_google_asylo//asylo:enclave_runtime",
        "@com_google_asylo//asylo/util:status",
    ],
)


debug_sign_enclave(
    name = "protection_server_enclave.so",
    backends = sgx.backend_labels,
    config = "@com_google_asylo//asylo/grpc/util:grpc_enclave_config",
    unsigned = "protection_server_enclave_unsigned.so",
)



# The driver for the gRPC server enclave.
enclave_loader(
    name = "protection_grpc_server",
    srcs = ["protection_grpc_server_driver.cc"],
    enclaves = {"enclave": ":protection_server_enclave.so"},
    loader_args = ["--enclave_path='{enclave}'"],
    deps = [
        ":protection_util",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/time",
        "@com_google_asylo//asylo:enclave_client",
        "@com_google_asylo//asylo/util:logging",
        "@com_google_asylo//asylo/util:status",
    ],
)



cc_library(
    name = "protection_util",
    srcs = ["protection_util.cc"],
    hdrs = ["protection_util.h"],
    deps = [
        ":protection_grpc_server_config_cc_proto",
        "@com_google_absl//absl/strings",
        "@com_google_asylo//asylo:enclave_cc_proto",
        "@com_google_asylo//asylo:enclave_client",
        "@com_google_asylo//asylo/platform/primitives/sgx:loader_cc_proto",
        "@com_google_asylo//asylo/util:status",
        "@com_google_protobuf//:protobuf",
    ],
)
