//
// Created by Anirut Kamchai on 18/1/2023 AD.
//

#ifndef ASYLO_EXAMPLES_KX_SERVER_IMPL_H
#define ASYLO_EXAMPLES_KX_SERVER_IMPL_H

#include <string>

#include "absl/base/thread_annotations.h"
#include "absl/container/flat_hash_map.h"
#include "absl/synchronization/mutex.h"
#include "absl/synchronization/notification.h"
#include "kx_enclave/kx_server.grpc.pb.h"
#include "include/grpcpp/grpcpp.h"
#include "include/grpcpp/server.h"

namespace kx {
    namespace kx_enclave {
        class KxServerImpl final : KxEnclave::Service {
        public:
            explicit KxServerImpl();

        private:
            ::grpc::Status GenerateKeyPair(::grpc::ServerContext *context,
                                           const GenerateKeyPairRequest *request,
                                           GenerateKeyPairReply *response) override;

            ::grpc::Status SignMessage(::grpc::ServerContext *context,
                                       const SignMessageRequest *request,
                                       SignMessageReply *response) override;

            ::grpc::Status SignTransaction(::grpc::ServerContext *context,
                                           const SignTransactionRequest *request,
                                           SignTransactionReply *response) override;

            ::grpc::Status SignTransactionLegacy(::grpc::ServerContext *context,
                                                 const SignTransactionLegacyRequest *request,
                                                 SignTransactionLegacyReply *response) override;

        };
    }
}

#endif //ASYLO_EXAMPLES_KX_SERVER_IMPL_H
