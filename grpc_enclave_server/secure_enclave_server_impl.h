/*
 *
 * Copyright 2018 Asylo authors
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

#ifndef ASYLO_KX_GRPC_SERVER_TRANSLATOR_SERVER_IMPL_H_
#define ASYLO_KX_GRPC_SERVER_TRANSLATOR_SERVER_IMPL_H_

#include <string>

#include "absl/base/thread_annotations.h"
#include "absl/container/flat_hash_map.h"
#include "absl/synchronization/mutex.h"
#include "absl/synchronization/notification.h"
#include "grpc_enclave_server/secure_enclave_server.grpc.pb.h"
#include "include/grpcpp/grpcpp.h"
#include "include/grpcpp/server.h"

namespace kx {
namespace grpc_server {

class SecureEnclaveServerImpl final : public Translator::Service {
 public:
  // Configure the server.
  explicit SecureEnclaveServerImpl();

 private:
  ::grpc::Status GenerateKeyPair(::grpc::ServerContext *context,
                                const GenerateKeyPairRequest *request,
                                GenerateKeyPairReply *response) override;

  ::grpc::Status SignMessage(::grpc::ServerContext *context,
                                const SignMessageRequest *request,
                                SignMessageReply *response) override;

  // A map from words to their translations.
  absl::flat_hash_map<std::string, std::string> translation_map_;
};

}  // namespace grpc_server
}  // namespace kx

#endif  // ASYLO_KX_GRPC_SERVER_TRANSLATOR_SERVER_IMPL_H_
