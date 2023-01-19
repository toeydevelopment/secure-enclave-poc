//
// Created by Anirut Kamchai on 19/1/2023 AD.
//

#ifndef THEPROTECTOR_PROTECTION_SERVER_H
#define THEPROTECTOR_PROTECTION_SERVER_H

#include <string>

#include "absl/base/thread_annotations.h"
#include "absl/container/flat_hash_map.h"
#include "absl/synchronization/mutex.h"
#include "absl/synchronization/notification.h"
#include "protection/protection.grpc.pb.h"
#include "include/grpcpp/grpcpp.h"
#include "include/grpcpp/server.h"

namespace kx {
    namespace protection {
        class ProtectionServer final : KxProtection::Service {
        public:
            explicit ProtectionServer();

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


#endif //THEPROTECTOR_PROTECTION_SERVER_H
