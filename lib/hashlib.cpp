#include "../include/hashlib.h"

#include <boost/uuid/sha1.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>


namespace hashlib {

    std::string Sha1::GetSha1(const char *msg, size_t len) {
        uint32_t sha1[5];
        boost::uuids::detail::sha1 s;
        std::stringstream convertor;
        s.process_bytes(msg, len);
        s.get_digest(sha1);

        for (int i = 0; i < 5; i++)
            convertor << std::hex << std::setw(8) << std::setfill('0') << sha1[i];
        return convertor.str();
    }

    std::string Sha1::GetSha1(const std::string &str) {
        return GetSha1(str.c_str(), str.length());
    }

    std::string Sha1::Bytes2Str(const DigestField &bytes) {
        std::stringstream convertor;
        for (int i = 0; i < 5; i++)
            convertor << std::hex << std::setw(8) << std::setfill('0') << bytes[i];
        return convertor.str();
    }

    int Sha1::GetSha1(const char *msg, size_t len, DigestField &bytes) {
        boost::uuids::detail::sha1 s;
        std::stringstream convertor;
        s.process_bytes(msg, len);
        s.get_digest(bytes);
        return 0;
    }

    int Sha1::GetSha1(const std::string &str, DigestField &bytes) {
        return GetSha1(str.c_str(), str.length(), bytes);
    }

    int Sha1::Str2Bytes(const std::string &str, DigestField &bytes) {
        std::stringstream convertor;
        convertor << std::hex;
        for (int i = 0; i < 5; i++) {
            convertor.clear();
            convertor << str.substr(i * 8, 8);
            std::string tmp;
            convertor >> bytes[i];
        }
        return 0;
    }
}
