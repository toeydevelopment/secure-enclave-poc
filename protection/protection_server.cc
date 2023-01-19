//
// Created by Anirut Kamchai on 19/1/2023 AD.
//

#include "protection_server.h"
#include "absl/strings/ascii.h"
#include "absl/strings/str_cat.h"
#include "include/grpcpp/grpcpp.h"

namespace kx {
    namespace protection {
        ProtectionServer::ProtectionServer() : Service() {
        }

        ::grpc::Status ProtectionServer::GenerateKeyPair(
                ::grpc::ServerContext *context, const GenerateKeyPairRequest *request,
                GenerateKeyPairReply *response) {

            return ::grpc::Status::OK;
        }

        ::grpc::Status ProtectionServer::SignMessage(::grpc::ServerContext *context,
                                                     const SignMessageRequest *request,
                                                     SignMessageReply *response) {
            return ::grpc::Status::OK;
        }

        ::grpc::Status ProtectionServer::SignTransaction(::grpc::ServerContext *context,
                                                         const SignTransactionRequest *request,
                                                         SignTransactionReply *response) {
            return ::grpc::Status::OK;
        }

        ::grpc::Status ProtectionServer::SignTransactionLegacy(::grpc::ServerContext *context,
                                                               const SignTransactionLegacyRequest *request,
                                                               SignTransactionLegacyReply *response) {
            return ::grpc::Status::OK;
        }
    }
}