// #include <exception>
// #include <iostream>
#include <ctime>
#include "cpptotp/src/libcppotp/bytes.h"
#include "cpptotp/src/libcppotp/otp.h"

uint32_t generateTotp(const CppTotp::Bytes::ByteString &key,
                      uint64_t unixTime,
                      size_t digits = 6) {
    using namespace CppTotp;
    uint64_t start = 0;      // начало отсчёта
    uint64_t step  = 30;     // длина окна (30 секунд)
    return totp(key, unixTime, start, step, digits, hmacSha1_64);
}

int main(){
    // using namespace std;
    // try {
    //     int m;
    //     bool v;
    //     cout << m/v;
    //     return 0;
    // } catch (exception ex) {
    //     cout << "ex";
    //     cout << ex.what();
    // }
    using namespace CppTotp;
    const char *secr = "12345678901234567890";
    Bytes::ByteString key(
        reinterpret_cast<const uint8_t*>(secr),
        reinterpret_cast<const uint8_t*>(secr)+20
    );
    return 0;
}

void cpp_otp(){
    return;
}
