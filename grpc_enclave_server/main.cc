#include <iostream>
#include <ethash/keccak.h>
// #include <ethash/progpow.h>
#include <ethash/ethash.h>

int main(int argc, char **argv) {
    std::vector<uint8_t> private_key = generateRandomBytes(32);

    std::cout << "Hello, world!" << std::endl;
    return 0;
}