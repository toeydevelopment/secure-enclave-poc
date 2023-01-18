//
// Created by Anirut Kamchai on 18/1/2023 AD.
//

#include "kx_server_util.h"
#include <string>


namespace kx {
    namespace kx_enclave {
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

        asylo::StatusOr <string> GrpcServerEnclaveGetAddress() {
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
            if (!enclave_output.HasExtension(actual_server_address)) {
                return asylo::Status(asylo::error::INTERNAL,
                                     "Server output missing address extension");
            }
            return enclave_output.GetExtension(actual_server_address);
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