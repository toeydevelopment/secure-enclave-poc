/*
 *
 * Copyright 2020 Asylo authors
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

#ifndef ASYLO_IDENTITY_ATTESTATION_SGX_SGX_INTEL_ECDSA_QE_REMOTE_ASSERTION_VERIFIER_H_
#define ASYLO_IDENTITY_ATTESTATION_SGX_SGX_INTEL_ECDSA_QE_REMOTE_ASSERTION_VERIFIER_H_

#include <memory>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "asylo/crypto/certificate_interface.h"
#include "asylo/identity/additional_authenticated_data_generator.h"
#include "asylo/identity/attestation/enclave_assertion_verifier.h"
#include "asylo/identity/attestation/sgx/sgx_intel_ecdsa_qe_remote_assertion_authority_config.pb.h"
#include "asylo/identity/enclave_assertion_authority.h"
#include "asylo/identity/identity.pb.h"
#include "asylo/identity/identity_acl.pb.h"
#include "asylo/identity/platform/sgx/internal/code_identity_constants.h"
#include "asylo/identity/platform/sgx/sgx_identity.pb.h"
#include "asylo/platform/common/static_map.h"
#include "asylo/util/mutex_guarded.h"
#include "asylo/util/status.h"
#include "asylo/util/statusor.h"

namespace asylo {

/// Implementation of `EnclaveAssertionVerifier` that verifiers assertions
/// generated by the Intel ECDSA quoting enclave. These assertions attest,
/// to a remote party, properties about both an enclave's code as well as
/// the Intel platform properties.
class SgxIntelEcdsaQeRemoteAssertionVerifier : public EnclaveAssertionVerifier {
 public:
  /// Constructs a new `SgxIntelEcdsaQeAssertionVerifier` that generates
  /// assertions suitable for use with EKEP.
  SgxIntelEcdsaQeRemoteAssertionVerifier();

  /// Constructs a new `SgxIntelEcdsaQeAssertionVerifier` that uses
  /// `aad_generator` to generate the expected additional authenticated data to
  /// be matched with quotes.
  explicit SgxIntelEcdsaQeRemoteAssertionVerifier(
      std::unique_ptr<AdditionalAuthenticatedDataGenerator> aad_generator);

  Status Initialize(const std::string &serialized_config) override;

  bool IsInitialized() const override;

  EnclaveIdentityType IdentityType() const override;

  std::string AuthorityType() const override;

  Status CreateAssertionRequest(AssertionRequest *request) const override;

  StatusOr<bool> CanVerify(const AssertionOffer &offer) const override;

  Status Verify(const std::string &user_data, const Assertion &assertion,
                EnclaveIdentity *peer_identity) const override;

 private:
  // Type that holds members for mutex-synchronized access.
  struct Members {
    explicit Members(
        std::unique_ptr<AdditionalAuthenticatedDataGenerator> generator)
        : aad_generator(std::move(generator)) {}

    bool is_initialized = false;
    std::vector<std::unique_ptr<CertificateInterface>> root_certificates;
    std::unique_ptr<AdditionalAuthenticatedDataGenerator> aad_generator;
    IdentityAclPredicate qe_identity_expectation;
  };

  Status CheckInitialization(absl::string_view caller) const;

  MutexGuarded<Members> members_;
};

}  // namespace asylo

#endif  // ASYLO_IDENTITY_ATTESTATION_SGX_SGX_INTEL_ECDSA_QE_REMOTE_ASSERTION_VERIFIER_H_
