/*
 *
 * Copyright 2019 Asylo authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef ASYLO_KX_GRPC_ENCLAVE_SERVER_UTIL_H_
#define ASYLO_KX_GRPC_ENCLAVE_SERVER_UTIL_H_

#include <string>

#include "asylo/util/status.h"
#include "asylo/util/statusor.h"

namespace kx {
    namespace grpc_enclave_server {

        // Each of the following functions assume that the asylo::EnclaveManager
        // instance has been configured using asylo::EnclaveManager::Configure().

        // Loads the GrpcServerEnclave from |enclave_path|. If |debug_enclave| is true,
        // then the enclave is started in debug mode. Starts the enclave's server on
        // |server_port| and configures the server to refer requests to the
        // GetTranslation RPC.
        asylo::Status LoadGrpcServerEnclave(const std::string &enclave_path, const std::string &address,
                                            int server_port, bool debug_enclave);

        // Retrieves the port of the server inside the GrpcServerEnclave. Returns a
        // non-OK Status if the GrpcServerEnclave is not running.
        asylo::StatusOr<int> GrpcServerEnclaveGetPort();

        // Destroys the GrpcServerEnclave and returns its finalization Status. Returns a
        // non-OK Status if the GrpcServerEnclave is not running.
        asylo::Status DestroyGrpcServerEnclave();

    } // namespace grpc_enclave_server
} // namespace examples

#endif // ASYLO_KX_GRPC_ENCLAVE_SERVER_UTIL_H_
