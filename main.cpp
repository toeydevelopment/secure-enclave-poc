#include <iostream>
#include "./asylo/trusted_application.h"



class ProtectionEnclave final : public asylo::TrustedApplication {
public:
    asylo::Status Initialize()
};


int main() {

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
