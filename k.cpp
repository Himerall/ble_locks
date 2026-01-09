#include <chrono>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <ctime>
#include <map>
#include <random>
#include <string>
#include <thread>
#include "cpptotp/src/libcppotp/bytes.h"
#include "cpptotp/src/libcppotp/otp.h"
#include "cpp-base32/Base32.h"

uint64_t step = 0;

uint32_t generateTotp(const CppTotp::Bytes::ByteString &key, uint64_t unixTime, size_t digits = 12) {
    using namespace CppTotp;
    uint64_t start = 0;
    step = 1;
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

CppTotp::Bytes::ByteString key_generate(CppTotp::Bytes::ByteString &key, int len){
    using namespace CppTotp;
    // std::cout << rand_nums(20) << "\n";
    std::string f = rand_nums(len);
    const char *secr = f.data();
    key.assign(
        reinterpret_cast<const uint8_t*>(secr),
        reinterpret_cast<const uint8_t*>(secr) + 20
    );
    return key;
}
CppTotp::Bytes::ByteString key;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::map<uint32_t, std::string>uids;
    while (true) {
        std::cout << "Please, insert your key (or send '-' to generate new one): ";
        std::string choice = "";
        std::cin >> choice;
        if (choice == "-"){
            // std::cout << "\n:";
            using namespace CppTotp;
            // // std::cout << rand_nums(20) << "\n";
            // std::string f = rand_nums(30);
            // const char *secr = f.data(); 

            // key.assign(
            //     reinterpret_cast<const uint8_t*>(secr),
            //     reinterpret_cast<const uint8_t*>(secr) + 20
            // );
            key = key_generate(key, 20);
            std::string key_str = Bytes::toBase32(key);
            std::cout << "UID key: "<< key_str;
            uint32_t rand_totp_now = generateTotp(key, std::stoull(rand_nums(10)));
            while (true) {
                if (uids[rand_totp_now].empty()){
                    std::cout.fill('0'); std::cout.width(12);
                    std::cout << "\nUID: " << rand_totp_now;
                    std::cout.fill(' '); std::cout.width(0);
                    break;
                } else {
                    rand_totp_now = generateTotp(key, std::stoull(rand_nums(10)));
                }
            }
            // if (Bytes::fromBase32(Bytes::toBase32(key)) == key) std::cout << "-1\n"
            // ;
            key = key_generate(key, 20);
            key_str = Bytes::toBase32(key);
            std::cout << "\nKey: " << key_str;
            std::time_t now = std::time(nullptr);
            std::cout << "\nTime: " << now << "\nNum key: ";
            std::cout.fill('0'); std::cout.width(12);
            std::cout << generateTotp(key, now) << "\n";
            std::cout.fill(' '); std::cout.width(0);
        } else {
            // std::cout << "\nL";
            key = CppTotp::Bytes::fromBase32(choice);
            std::cout << "Please, insert UID: ";
            std::cout << "Please, insert time in unixstamp: ";
            std::time_t now = 0;
            std::cin >> now;
        }
        // uint32_t code = 1;
        // uint32_t last_code = 0;
        // std::time_t not_now = -1;

        // int c = 0;

        // while (true) {
        //     now = std::time(nullptr);
        //     std::cout << "x;";
        //     if (now!=not_now){
        //         std::cout << "m;";
        //         // if (c == 0) c++; continue;
        //         code = generateTotp(key, now);
        //         // std::cout << code << "\n";
        //         // std::cout << "!"<< last_code << ";?" << code << "\n";
        //         if (last_code!=code){
        //             std::cout.fill('0'); std::cout.width(6); std::cout << code  << "\n"; last_code = code;
        //         }
        //         std::this_thread::sleep_for(std::chrono::seconds(step-10));
        //     }
        //     not_now = now;
        // }
    }
    return 0;
}
