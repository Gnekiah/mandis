#include "../include/hashlib.h"

#include <boost/uuid/sha1.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>


namespace hashlib {

    Sha1::Sha1(const char *msg, size_t len) {
        boost::uuids::detail::sha1 s;
        std::stringstream convertor;
        s.process_bytes(msg, len);
        s.get_digest(sha1_);

        for (int i = 0; i < 5; i++)
            convertor << std::hex << std::setw(8) << std::setfill('0') << sha1_[i];
        memcpy(sha1_str_, convertor.str().c_str(), 40);
        sha1_str_[40] = '\0';
    }

    Sha1::Sha1(const std::string &str) {
        boost::uuids::detail::sha1 s;
        std::stringstream convertor;
        s.process_bytes(str.c_str(), str.length());
        s.get_digest(sha1_);

        for (int i = 0; i < 5; i++)
            convertor << std::hex << std::setw(8) << std::setfill('0') << sha1_[i];
        memcpy(sha1_str_, convertor.str().c_str(), 40);
        sha1_str_[40] = '\0';
    }

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
}
