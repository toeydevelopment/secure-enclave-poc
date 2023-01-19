//
// Created by Anirut Kamchai on 19/1/2023 AD.
//

#include "protection_util.h"

#include <cstdint>
#include <string>

#include "absl/strings/str_cat.h"
#include "asylo/client.h"
#include "asylo/enclave.pb.h"
#include "asylo/platform/primitives/sgx/loader.pb.h"
#include "asylo/util/status.h"
#include "asylo/util/status_macros.h"
#include "kx_enclave/kx_enclave_grpc_server_config.pb.h"


namespace kx {
    namespace protection {
        namespace {
            constexpr char kServerAddress[] = "0.0.0.0";
            constexpr char kEnclaveName[] = "protection_server";
        }

        asylo::Status LoadGrpcServerEnclave(const std::string &enclave_path,
                                            const std::string &address,
                                            int server_port, bool debug_enclave) {
            // The EnclaveLoadConfig contains all configurations passed to the enclave for
            // initialization.
            asylo::EnclaveLoadConfig load_config;
            load_config.set_name("kx_enclave_server");

            // The EnclaveConfig contains the address that the gRPC server will run on.
            asylo::EnclaveConfig *config = load_config.mutable_config();
            config->SetExtension(server_address, address);
            config->SetExtension(port, server_port);

            // The SgxLoadConfig sets up configuration specific to an SGX enclave,
            // including the location of the enclave binary and whether to run in debug
            // mode.
            asylo::SgxLoadConfig *sgx_config =
                    load_config.MutableExtension(asylo::sgx_load_config);
            sgx_config->mutable_file_enclave_config()->set_enclave_path(enclave_path);
            sgx_config->set_debug(debug_enclave);

            asylo::EnclaveManager *manager = nullptr;
            ASYLO_ASSIGN_OR_RETURN(manager, asylo::EnclaveManager::Instance());

            // Load the enclave. Calling LoadEnclave() triggers a call to the Initialize()
            // method of the TrustedApplication.
            return manager->LoadEnclave(load_config);
        }

        asylo::StatusOr<int> GrpcServerEnclaveGetPort() {
            asylo::EnclaveManager *manager = nullptr;
            ASYLO_ASSIGN_OR_RETURN(manager, asylo::EnclaveManager::Instance());

            asylo::EnclaveClient *client = manager->GetClient(kEnclaveName);
            if (!client) {
                return asylo::Status(asylo::error::FAILED_PRECONDITION,
                                     absl::StrCat(kEnclaveName, " not running"));
            }

            asylo::EnclaveInput enclave_input;
            asylo::EnclaveOutput enclave_output;
            ASYLO_RETURN_IF_ERROR(client->EnterAndRun(enclave_input, &enclave_output));
            if (!enclave_output.HasExtension(actual_server_port)) {
                return asylo::Status(asylo::error::INTERNAL,
                                     "Server output missing server_port extension");
            }
            return enclave_output.GetExtension(actual_server_port);
        }


        asylo::Status DestroyGrpcServerEnclave() {
            asylo::EnclaveManager *manager = nullptr;
            ASYLO_ASSIGN_OR_RETURN(manager, asylo::EnclaveManager::Instance());

            asylo::EnclaveClient *client = manager->GetClient(kEnclaveName);
            if (!client) {
                return asylo::Status(asylo::error::FAILED_PRECONDITION,
                                     absl::StrCat(kEnclaveName, " not running"));
            }

            asylo::EnclaveFinal final_input;
            return manager->DestroyEnclave(client, final_input);
        }
    }
}