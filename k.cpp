#include <iostream>
#include <ctime>
#include "cpptotp/src/libcppotp/bytes.h"
#include "cpptotp/src/libcppotp/otp.h"

uint32_t generateTotp(const CppTotp::Bytes::ByteString &key,
                      uint64_t unixTime,
                      size_t digits = 6) {
    using namespace CppTotp;
    uint64_t start = 0;
    uint64_t step  = 30;
    return totp(key, unixTime, start, step, digits, hmacSha1_64);
}

int main() {
    using namespace CppTotp;
    const char *secr = "12345678901234567890";
    Bytes::ByteString key(
        reinterpret_cast<const uint8_t*>(secr),
        reinterpret_cast<const uint8_t*>(secr) + 20
    );
    
    
    while (true) {
        std::time_t now = std::time(nullptr);
        uint32_t code = generateTotp(key, now);
        std::cout << code << "\n";  // Вывод 6-значного TOTP-кода
    }
    return 0;
}
