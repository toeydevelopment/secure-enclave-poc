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

#include "grpc_server/translator_server_impl.h"

#include "absl/strings/ascii.h"
#include "absl/strings/str_cat.h"
#include "include/grpcpp/grpcpp.h"

namespace examples {
    namespace grpc_server {

        TranslatorServerImpl::TranslatorServerImpl()
                : Service(),
                // Initialize the translation map with a few known translations.
                  translation_map_({{"asylo",      "sanctuary"},
                                    {"istio",      "sail"},
                                    {"kubernetes", "helmsman"}}) {
        }

        ::grpc::Status TranslatorServerImpl::GenerateKeyPair(
                ::grpc::ServerContext *context, const GenerateKeyPairRequest *request,
                GenerateKeyPairReply *response) {

            // Return the translation.
            response->set_encrypted_private_key("HELLO WORLD ENCRYPTED");

            return ::grpc::Status::OK;
        }

        ::grpc::Status TranslatorServerImpl::SignMessage(
                ::grpc::ServerContext *context, const SignMessageRequest *request,
                SignMessageReply *response) {
            // Confirm that |*request| has an |input_word| field.
            if (!request->has_message()) {
                return ::grpc::Status(::grpc::StatusCode::INVALID_ARGUMENT,
                                      "No message word given");
            }

            // Confirm that the translation map has a translation for the input word.
            auto response_iterator =
                    translation_map_.find(absl::AsciiStrToLower(request->message()));
            if (response_iterator == translation_map_.end()) {
                return ::grpc::Status(::grpc::StatusCode::INVALID_ARGUMENT,
                                      absl::StrCat("No known translation for \"",
                                                   request->message(), "\""));
            }

            // Return the translation.
            response->set_signature(response_iterator->second);
            return ::grpc::Status::OK;
        }

    } // namespace grpc_server
} // namespace examples
