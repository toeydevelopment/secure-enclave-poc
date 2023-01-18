//
// Created by Anirut Kamchai on 18/1/2023 AD.
//

// #include "kx_server_impl.h"
#include "kx_enclave/kx_server_impl.h"

#include "absl/strings/ascii.h"
#include "absl/strings/str_cat.h"
#include "include/grpcpp/grpcpp.h"

namespace kx
{
    namespace kx_enclave
    {
        :

        KxServerImpl::KxServerImpl() : Service(),
        {
        }

        ::grpc::Status KxServerImpl::GenerateKeyPair(
                ::grpc::ServerContext *context, const GenerateKeyPairRequest *request,
                GenerateKeyPairReply *response)

        )
        {
        }

        ::grpc::Status KxServerImpl::SignMessage(::grpc::ServerContext *context,
                                                 const SignMessageRequest *request,
                                                 SignMessageReply *response)
        {
        }

        ::grpc::Status KxServerImpl::SignTransaction(::grpc::ServerContext *context,
                                                     const SignTransactionRequest *request,
                                                     SignTransactionReply *response)
        {
        }

        ::grpc::Status KxServerImpl::SignTransactionLegacy(::grpc::ServerContext *context,
                                                           const SignTransactionLegacyRequest *request,
                                                           SignTransactionLegacyReply *response)
        {
        }

    }
}