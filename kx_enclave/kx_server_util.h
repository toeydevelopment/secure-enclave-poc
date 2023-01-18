//
// Created by Anirut Kamchai on 18/1/2023 AD.
//

#ifndef ASYLO_EXAMPLES_KX_SERVER_UTIL_H
#define ASYLO_EXAMPLES_KX_SERVER_UTIL_H

#include <string>

#include "asylo/util/status.h"
#include "asylo/util/statusor.h"

namespace kx
{
    namespace kx_enclave
    {
        asylo::Status
        LoadGrpcServerEnclave(const std::string &enclave_path, const std::string &address, int server_port,
                              bool debug_enclave);

        // Retrieves the port of the server inside the GrpcServerEnclave. Returns a
        // non-OK Status if the GrpcServerEnclave is not running.
        asylo::StatusOr<int> GrpcServerEnclaveGetPort();

        asylo::StatusOr<int> GrpcServerEnclaveGetAddress();

        // Destroys the GrpcServerEnclave and returns its finalization Status. Returns a
        // non-OK Status if the GrpcServerEnclave is not running.
        asylo::Status DestroyGrpcServerEnclave();
    }
}
#endif // ASYLO_EXAMPLES_KX_SERVER_UTIL_H
