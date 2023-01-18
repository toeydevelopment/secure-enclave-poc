//
// Created by Anirut Kamchai on 18/1/2023 AD.
//

#include <cstdint>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/time/clock.h"
#include "asylo/enclave_manager.h"
#include "asylo/util/logging.h"
#include "asylo/util/status.h"
#include "asylo/util/statusor.h"
#include "kx_enclave/kx_server_util.h"

ABSL_FLAG(std::string, enclave_path,
"", "Path to enclave to load");
ABSL_FLAG(std::string, address,
"", "Address that the server listens to");
// By default, let the server run for five minutes.
ABSL_FLAG(int32_t, server_max_lifetime,
300,
"The longest amount of time (in seconds) that the server should be "
"allowed to run");

// Default value 0 is used to indicate that the system should choose an
// available port.
ABSL_FLAG(int32_t, port,
0, "Port that the server listens to");

ABSL_FLAG(bool, debug,

true, "Whether to use a debug enclave");


int main(int argc, char *argv[]) {
    // Parse command-line arguments.
    absl::ParseCommandLine(argc, argv);

    std::string address = absl::GetFlag(FLAGS_enclave_path);
    LOG_IF(QFATAL, address.empty()) << "--address cannot be empty";

    std::string enclave_path = absl::GetFlag(FLAGS_enclave_path);
    LOG_IF(QFATAL, enclave_path.empty()) << "--enclave_path cannot be empty";

    asylo::Status status =
            asylo::EnclaveManager::Configure(asylo::EnclaveManagerOptions());
    LOG_IF(QFATAL, !status.ok())
            << "Failed to configure EnclaveManager: " << status;

    status = kx::kx_enclave::LoadGrpcServerEnclave(
            enclave_path, address, absl::GetFlag(FLAGS_port), absl::GetFlag(FLAGS_debug));
    LOG_IF(QFATAL, !status.ok())
            << "Loading " << enclave_path << " failed: " << status;
    asylo::StatusOr<int> port_result =
            kx::kx_enclave::GrpcServerEnclaveGetPort();
    LOG_IF(QFATAL, !port_result.ok())
            << "Retrieving port failed: " << port_result.status();

    std::cout << "Server started on address " << port_result.value() << std::endl;
    std::cout << "Server started on port " << port_result.value() << std::endl;

}