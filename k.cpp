#include <cstdint>
#include <iomanip>
#include <iostream>
#include <ctime>
#include "cpptotp/src/libcppotp/bytes.h"
#include "cpptotp/src/libcppotp/otp.h"

uint32_t generateTotp(const CppTotp::Bytes::ByteString &key, uint64_t unixTime, size_t digits = 6) {
    using namespace CppTotp;
    uint64_t start = 0;
    uint64_t step  = 10;
    return totp(key, unixTime, start, step, digits, hmacSha1_64);
}

int main() {
    using namespace CppTotp;
    const char *secr = "12345678901234567890";
    Bytes::ByteString key(
        reinterpret_cast<const uint8_t*>(secr),
        reinterpret_cast<const uint8_t*>(secr) + 20
    );
    
    std::cout << Bytes::toBase32(key);
    // if (Bytes::fromBase32(Bytes::toBase32(key)) == key) std::cout << "-1\n"
    // ;
    std::time_t now = std::time(nullptr);
    uint32_t code = 1;
    uint32_t last_code = 0;

    while (true) {
        now = std::time(nullptr);
        code = generateTotp(key, now);
        // std::cout << code << "\n";
        std::cout.fill('0');
        std::cout.width(6); 
        if (last_code!=code) std::cout << code  << "\n"; last_code = code;
    }
    return 0;
}
