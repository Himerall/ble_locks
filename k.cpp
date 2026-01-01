#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <ctime>
#include <random>
#include <string>
#include "cpptotp/src/libcppotp/bytes.h"
#include "cpptotp/src/libcppotp/otp.h"
#include "cpp-base32/Base32.h"

uint32_t generateTotp(const CppTotp::Bytes::ByteString &key, uint64_t unixTime, size_t digits = 6) {
    using namespace CppTotp;
    uint64_t start = 0;
    uint64_t step  = 30;
    return totp(key, unixTime, start, step, digits, hmacSha1_64);
}

// std::string toB32(const CppTotp::Bytes::ByteString &bytes) {
//     std::string result;
//     Base32::Encode32(unsigned char *in, int inLen, unsigned char *out)
//     return result;
// }

std::string rand_nums(int len){
    using namespace std;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0,9);
    string digits;
    digits.reserve(len);
    for (int i = 0; i<len;i++){
        digits += '0' + dis(gen);
    }
    return digits;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << "Please, insert your key (or send '-' to generate new one): ";
    std::string choice = "";
    std::cin >> choice;
    CppTotp::Bytes::ByteString key;
    if (choice == "-"){
        // std::cout << "\n:";
        using namespace CppTotp;
        // std::cout << rand_nums(20) << "\n";
        std::string f = rand_nums(20);
        const char *secr = f.data(); 

        key.assign(
            reinterpret_cast<const uint8_t*>(secr),
            reinterpret_cast<const uint8_t*>(secr) + 20
        );
        
        std::string key_str = Bytes::toBase32(key);
        std::cout << key_str << "\n";
        // if (Bytes::fromBase32(Bytes::toBase32(key)) == key) std::cout << "-1\n"
        // ;
    } else {
        // std::cout << "\nL";
        key = CppTotp::Bytes::fromBase32(choice);
    }
    
    std::time_t now = std::time(nullptr);
    uint32_t code = 1;
    uint32_t last_code = 0;
    std::time_t not_now = -1;

    // int c = 0;

    while (true) {
        now = std::time(nullptr);
        if (now!=not_now){
            // if (c == 0) c++; continue;
            code = generateTotp(key, now);
            // std::cout << code << "\n";
            std::cout.fill('0');
            std::cout.width(6); 
            if (last_code!=code) std::cout << code  << "\n"; last_code = code;
        }
        not_now = now;
    }
    return 0;
}
